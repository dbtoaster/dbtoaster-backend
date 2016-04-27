package ddbt.codegen.prettyprinter

import java.io.PrintWriter

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types._
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.utils.document._
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store._
import ddbt.lib.store.deep.StoreIRs._
import ddbt.lib.store.deep.StoreDSL
import pardis.deep.scalalib.ScalaPredefOps
import ddbt.transformer._

import scala.reflect.io.File


class StoreScalaCodeGenerator(override val IR: StoreDSL) extends ScalaCodeGenerator with StoreCodeGenerator {

  import IR._

  //TODO: SBJ: Bug in ScalaCodeGen
  override def blockToDocument(block: Block[_]): Document = {
    Document.text("{") :: Document.nest(NEST_COUNT,
      mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)) :/: "}"
  }

  def blockToDocumentNoBraces(block: Block[_]): Document = {
    mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)
  }

  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if (sym.tp == UnitType)
      doc"()"
    else {
      if (sym.name != "x") {
        Document.text(sym.name)
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

    override def body(structDef: PardisStructDef[_]): Document = doc" {def copy = ${structDef.tag.typeName}(${(1 to structDef.fields.size).map("_" + _).mkString(", ")}) }"
  }

  override def getStruct(structDef: PardisStructDef[_]): Document = SEntryDefToDocument(structDef)

  object EntryIdxHoister {
    val map = collection.mutable.HashMap[Rep[_], String]()
    var cnt = 0

    def getArrayType(sym: Rep[_]) = "EntryIdx[" + map(sym).split("_Idx")(0) + "]"

    def add(sym: Rep[_], s: String): String = {
      val name = (s + "_Idx" + cnt)
      map += sym -> name
      cnt = cnt + 1
      name
    }
  }

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StoreIndex(self, idx, tp, uniq, other)) => doc"$self.index($idx, ${tp.asInstanceOf[Constant[String]].underlying}, $uniq, $other)"
    case Statement(sym, node) if sym.tp == UnitType => nodeToDocument(node)
    case Statement(sym, StringDiff(str1, str2)) => doc"val $sym = $str1.compareToIgnoreCase($str2)"
    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"
    case Statement(sym, StoreGet(self, idx, key, _)) => doc"val $sym = $self.get($idx, $key)"
    case Statement(sym, EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]))) =>
      val name = EntryIdxHoister.add(sym, tpeToDocument(h.i.tp).toString)
      doc" object $name extends EntryIdx[${tpeToDocument(h.i.tp)}] {" :/: Document.nest(NEST_COUNT,
        doc"override def hash(${expToDocument(h.i)} : ${tpeToDocument(h.i.tp)}) = ${blockToDocument(h.o)}" :/:
          doc"override def cmp(${expToDocument(c.i1)} : ${tpeToDocument(c.i1.tp)} , ${expToDocument(c.i2)} : ${tpeToDocument(c.i2.tp)}) = ${blockToDocument(c.o)}") :/: doc"}"
    case Statement(sym, ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"val $sym = Array[${EntryIdxHoister.getArrayType(ops(0))}](" :: ops.map(s => Document.text(EntryIdxHoister.map(s))).mkDocument(", ") :: doc")"
    case Statement(sym, BooleanExtraConditionalObject(cond, ift, iff)) => doc"val $sym = if(${expToDocument(cond)}) ${expToDocument(ift)} else ${expToDocument(iff)}"
    case _ => super.stmtToDocument(stmt)
  }

}
