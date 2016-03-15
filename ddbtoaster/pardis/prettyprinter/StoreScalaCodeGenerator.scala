package ddbt.codegen.prettyprinter

import java.io.PrintWriter

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types.PardisType
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.utils.document.Document
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store.deep.MStoreIRs._
import ddbt.lib.store.deep.StoreDSL
import pardis.deep.scalalib.ScalaPredefOps

import scala.reflect.io.File


class StoreScalaCodeGenerator(val IR: StoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[StoreDSL] {

  import IR._

  def emitSource4[T1, T2, T3, T4, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4]) => Rep[R], global: List[Rep[Any]], className: String, stream: PrintWriter)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], er: TypeRep[R]) = {

    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val body = reifyBlock(f(s1, s2, s3, s4))
    emitSource[R](List(s1, s2, s3, s4), global, body, className, stream)
  }


  def emitSource6[T1, T2, T3, T4, T5, T6, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6]) => Rep[R], global: List[Rep[Any]], className: String, stream: PrintWriter)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6))
    emitSource[R](List(s1, s2, s3, s4, s5, s6), global, body, className, stream)
  }

  def emitSource8[T1, T2, T3, T4, T5, T6, T7, T8, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8]) => Rep[R], global: List[Rep[Any]], className: String, stream: PrintWriter)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8))
    emitSource[R](List(s1, s2, s3, s4, s5, s6, s7, s8), global, body, className, stream)
  }

  def emitSource11[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11]) => Rep[R], global: List[Rep[Any]], className: String, stream: PrintWriter)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11))
    emitSource[R](List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11), global, body, className, stream)
  }

  def emitSource16[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11], Rep[T12], Rep[T13], Rep[T14], Rep[T15], Rep[T16]) => Rep[R], global: List[Rep[Any]], className: String, stream: PrintWriter)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], e12: TypeRep[T12], e13: TypeRep[T13], e14: TypeRep[T14], e15: TypeRep[T15], e16: TypeRep[T16], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val s9 = fresh[T9]
    val s10 = fresh[T10]
    val s11 = fresh[T11]
    val s12 = fresh[T12]
    val s13 = fresh[T13]
    val s14 = fresh[T14]
    val s15 = fresh[T15]
    val s16 = fresh[T16]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16))
    emitSource[R](List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16), global, body, className, stream)
  }

  def emitSource[R](args: List[Sym[Any]], global: List[Rep[Any]], body: Block[R], className: String, stream: PrintWriter) = {

    //        class orderStatusTx(x0: Store[SEntry3_III], x1: Store[SEntry8_IIIIIAFS]) extends ((Boolean, java.util.Date, Int, Int, Int, Int, Int, java.lang.String) => (Int)) {
    val genCode = "class " + className + "(" + global.collect{case s: Sym[Any] => s.name + s.id + ":" + tpeToDocument(s.tp)}.mkString(", ") + ") extends ((" + args.map(s => tpeToDocument(s.tp)).mkString(", ") + ") => " + tpeToDocument(body.typeT) + ") {\n" +
      "def apply(" + args.map(s => s + ": " + tpeToDocument(s.tp)).mkString(", ") + ") = "

    val cgDoc = blockToDocument(body)
    stream.println(genCode + cgDoc + "\n}")

    ()
  }

  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if (sym.name != "x") {
      Document.text(sym.name)
    } else {
      super.symToDocument(sym)
    }
  }

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, MStoreNew2()) => generateNewStore(sym, None)
    case _ => super.stmtToDocument(stmt)
  }


  def generateNewStore(c: Sym[_], mname: Option[String]): String = {
    def generateNew: String = "new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))"
    val symbolName = c.name + c.id
    val mapAlias = mname match {
      case Some(mapName) =>
        s"val $mapName = $symbolName"
      case None =>
        s""
    }
    s"""val $symbolName = $generateNew
$symbolName.index(0,IHash,true)
$mapAlias"""
  }
}
