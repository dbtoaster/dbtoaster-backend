package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types._
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.StoreDSL


class StoreScalaCodeGenerator(override val IR: StoreDSL) extends ScalaCodeGenerator with StoreCodeGenerator {

  import IR._


  def blockToDocumentNoBraces(block: Block[_]): Document = {
    mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)
  }

  override def expToDocument(exp: Expression[_]): Document = exp match {
    case c@Constant(q) if c.tp == UnitType => Document.empty
    case Constant(b: Boolean) => s"$b"
    case Constant(l: List[Any]) =>
      val tp = exp.tp.typeArguments(0).asInstanceOf[TypeRep[Any]]
      l.map(x => Constant(x)(tp)).mkDocument(doc"List(", doc", ", doc")")
    case Constant(t@(a, b, c)) => t.toString
    case _ => super.expToDocument(exp)
  }

  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if (sym.tp == UnitType)
      doc"()"
    else {
      if (sym.name != "x") {
        Document.text(sym.name.stripSuffix("_$"))
      } else {
        super.symToDocument(sym)
      }
    }
  }

  val SEntryDefToDocument = new StructDefToDocument {
    override def signature(structDef: PardisStructDef[_]): Document = {
      val name = structDef.tag.typeName
      val count = name.split("_")(1).length

      signatureMod(structDef) :: " class " :: name :: "(" :: fieldsDef(structDef) :: ")" :: " extends " :: s"Entry($count)"
    }

    override def fieldDef(field: StructElemInformation): Document =
     "var " :: field.name :: ": " :: tpeToDocument(field.tpe)

    override def body(structDef: PardisStructDef[_]): Document = {
      val constructor = doc"def this() = " :: structDef.fields.map(x => nullValue(x.tpe)).mkDocument("this(", ", ", ")")

      val argList = if (Optimizer.secondaryIndex)
        (1 to structDef.fields.size).map("_" + _)
      else
        "isSE" :: (1 to structDef.fields.size - 1).map("_" + _).toList
      val copyFromFn = doc"override def copyFrom(e: Entry) = { val that = e.asInstanceOf[${structDef.tag.typeName}]; " :: argList.map(a => s"$a = that.$a").mkString("", ";", "}")
      doc" {$constructor ; def copy = ${structDef.tag.typeName}(${argList.mkString(", ")}); $copyFromFn }"
    }
  }

  override def getStruct(structDef: PardisStructDef[_]): Document = SEntryDefToDocument(structDef)


  override def nodeToDocument(node: PardisNode[_]): Document = node match {
    case IfThenElse(c, ift, iff) =>
      def blkToDoc(b: Block[_]) = Document.nest(NEST_COUNT, mergeDocs(b.stmts.map(s => stmtToDocument(s)), true))
      "if(" :: expToDocument(c) :: ") {" :: blkToDoc(ift) :: (if (ift.tp == UnitType) Document.empty else "" :/: expToDocument(ift.res)) :/: "} else {" :: blkToDoc(iff) :: (if (iff.tp == UnitType) Document.empty else "" :/: expToDocument(iff.res)) :/: "}"
    case BooleanExtraConditionalObject(cond, ift, iff) => doc"if($cond) $ift else $iff"
    case EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]), Constant(name)) => doc" object $name extends EntryIdx[${h.i.tp}] {" :/: Document.nest(NEST_COUNT,
      doc"override def hash(${h.i} : ${h.i.tp}) = ${blockToDocument(h.o)}" :/:
        doc"override def cmp(${c.i1} : ${c.i1.tp} , ${c.i2} : ${c.i2.tp}) = ${blockToDocument(c.o)}") :/: doc"}"
    case StoreCopyIntoPool(_, _) => Document.empty
    case s@SetApplyObject1(Def(LiftedSeq(e))) => doc"Set.apply[${s.typeT}](${e.mkDocument(", ")}) //Apply1"
    case s@SetApplyObject2() => doc"Set.apply[${s.typeT}]() //Apply2"
    case _ => super.nodeToDocument(node)
  }

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StoreIndex(self, idx, Constant(tp: String), uniq, other)) => doc"val $sym = $self.index($idx, $tp, $uniq, $other)"
    case Statement(sym, node) if sym.tp == UnitType => nodeToDocument(node)
    //    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"
    case Statement(sym, StringExtraStringPrintfObject(size, f, Def(LiftedSeq(args)))) =>
      doc"var $sym = $f.format(${args.mkDocument(",")})" :\\:
        doc"if($sym.size > $size) " :\\: Document.nest(NEST_COUNT, doc"$sym = $sym.substring(0, $size)")
    case Statement(sym, StoreGetCopy(self, idx, key)) => doc"val $sym = $self.getCopy($idx, $key)"
    case Statement(sym, arr@ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"val $sym = Array[${arr.typeT}](" :: ops.collect {
      case Def(EntryIdxApplyObject(_, _, Constant(name))) => Document.text(name)
      case Def(node) => nodeToDocument(node)
      case e => expToDocument(e)
    }.mkDocument(", ") :: doc")"
    case _ => super.stmtToDocument(stmt)
  }

}
