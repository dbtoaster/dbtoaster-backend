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
import ddbt.lib.store.deep.{StoreDSL, StringPrintf}
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
  
  override def expToDocument(exp: Expression[_]): Document = exp match {
    case Constant(b: Boolean) => s"$b"
    case _ => super.expToDocument(exp)
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


  override def nodeToDocument(node: PardisNode[_]): Document = node match {
    case BooleanExtraConditionalObject(cond, ift, iff) => doc"if($cond) $ift else $iff"
    case EntryIdxApplyObject(Def(h: PardisLambda[_, _]), Def(c: PardisLambda2[_, _, _]), Constant(name)) => doc" object $name extends EntryIdx[${h.i.tp}] {" :/: Document.nest(NEST_COUNT,
      doc"override def hash(${h.i} : ${h.i.tp}) = ${blockToDocument(h.o)}" :/:
        doc"override def cmp(${c.i1} : ${c.i1.tp} , ${c.i2} : ${c.i2.tp}) = ${blockToDocument(c.o)}") :/: doc"}"
    case _ => super.nodeToDocument(node)
  }

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, StoreIndex(self, idx, Constant(tp: String), uniq, other)) => doc"val $sym = $self.index($idx, $tp, $uniq, $other)"
    case Statement(sym, node) if sym.tp == UnitType => nodeToDocument(node)
    case Statement(sym, StringDiff(str1, str2)) => doc"val $sym = $str1.compareToIgnoreCase($str2)"
//    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"
    case Statement(sym, StringPrintf(size, f, Def(LiftedSeq(args)))) => doc"var $sym = $f.format(${args.map(expToDocument).mkDocument(",")})" :\\:
      doc"if($sym.size > $size) " :\\: Document.nest(NEST_COUNT, doc"$sym = $sym.substring(0, $size)")
    case Statement(sym, StoreGetCopy(self, idx, key, _)) => doc"val $sym = $self.getCopy($idx, $key)"
    case Statement(sym, arr@ArrayApplyObject(Def(LiftedSeq(ops)))) => doc"val $sym = Array[${arr.typeT}](" :: ops.collect {
      case Def(EntryIdxApplyObject(_, _, Constant(name))) => Document.text(name)
      case Def(node) => nodeToDocument(node)
      case e => expToDocument(e)
    }.mkDocument(", ") :: doc")"
    case _ => super.stmtToDocument(stmt)
  }

}
