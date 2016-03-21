package ddbt.codegen.prettyprinter

import java.io.PrintWriter

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types.{AnyType, PardisType}
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.utils.document._
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store._
import ddbt.lib.store.deep.MStoreIRs._
import ddbt.lib.store.deep.StoreDSL
import pardis.deep.scalalib.ScalaPredefOps

import scala.reflect.io.File


class StoreScalaCodeGenerator(val IR: StoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[StoreDSL] {

  import IR._

  case class Index(val cols: List[Int], tp: IndexType, unique: Boolean = false, sliceIdx: Int) {
    override def toString = sliceIdx + "," + tp + ", " + unique + ", " + sliceIdx
  }

  val indexes = collection.mutable.HashMap[Sym[_], collection.mutable.ArrayBuffer[Index]]()

  object IndexAnalysis extends RuleBasedTransformer[StoreDSL](IR) {
    var enabled = false
    val primaryIndex = collection.mutable.HashMap[Rep[_], Seq[Int]]()
    val secondaryIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[Seq[Int]]]()
    val minSliceIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[Seq[Int]]]()
    val maxSliceIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[Seq[Int]]]()

    analysis += statement {
      case sym -> (node@MStoreGet(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))))) => primaryIndex += (store.asInstanceOf[Rep[_]] -> args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
        ()
    }
    //    analysis += statement {
    //      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(MirrorAggregatorMax(_,_)))) => maxSliceIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[Seq[Int]]()) += (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
    //        ()
    //    }
    //    analysis += statement {
    //      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(MirrorAggregatorMin(_,_)))) => minSliceIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[Seq[Int]]()) += (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
    //        ()
    //    }
    analysis += statement {
      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), z@_)) => val cols = (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
        secondaryIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[Seq[Int]]()) += cols
        ()
    }


  }

  case class BlockWithSymbols(val body: Block[Any], val syms: List[Sym[Any]]) {}

  val allBlocks = collection.mutable.Map[String, BlockWithSymbols]()

  def emitSource4[T1, T2, T3, T4, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val body = reifyBlock(f(s1, s2, s3, s4))
    allBlocks += (className -> BlockWithSymbols(body.asInstanceOf[Block[Any]], List(s1, s2, s3, s4)))
  }


  def emitSource6[T1, T2, T3, T4, T5, T6, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6))
    allBlocks += (className -> BlockWithSymbols(body.asInstanceOf[Block[Any]], List(s1, s2, s3, s4, s5, s6)))
  }

  def emitSource8[T1, T2, T3, T4, T5, T6, T7, T8, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], er: TypeRep[R]) = {
    val s1 = fresh[T1]
    val s2 = fresh[T2]
    val s3 = fresh[T3]
    val s4 = fresh[T4]
    val s5 = fresh[T5]
    val s6 = fresh[T6]
    val s7 = fresh[T7]
    val s8 = fresh[T8]
    val body = reifyBlock(f(s1, s2, s3, s4, s5, s6, s7, s8))
    allBlocks += (className -> BlockWithSymbols(body.asInstanceOf[Block[Any]], List(s1, s2, s3, s4, s5, s6, s7, s8)))
  }

  def emitSource11[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], er: TypeRep[R]) = {
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
    allBlocks += (className -> BlockWithSymbols(body.asInstanceOf[Block[Any]], List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11)))
  }

  def emitSource16[T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, R](f: (Rep[T1], Rep[T2], Rep[T3], Rep[T4], Rep[T5], Rep[T6], Rep[T7], Rep[T8], Rep[T9], Rep[T10], Rep[T11], Rep[T12], Rep[T13], Rep[T14], Rep[T15], Rep[T16]) => Rep[R], className: String)(implicit e1: TypeRep[T1], e2: TypeRep[T2], e3: TypeRep[T3], e4: TypeRep[T4], e5: TypeRep[T5], e6: TypeRep[T6], e7: TypeRep[T7], e8: TypeRep[T8], e9: TypeRep[T9], e10: TypeRep[T10], e11: TypeRep[T11], e12: TypeRep[T12], e13: TypeRep[T13], e14: TypeRep[T14], e15: TypeRep[T15], e16: TypeRep[T16], er: TypeRep[R]) = {
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
    allBlocks += (className -> BlockWithSymbols(body.asInstanceOf[Block[Any]], List(s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16)))
  }

  def emitSource(global: List[Rep[Any]], stream: PrintWriter) = {

    allBlocks.foreach { case (className, BlockWithSymbols(body, args)) =>
      val genCode = "class " + className + "(" + global.collect { case s: Sym[Any] => s.name + s.id + ":" + tpeToDocument(s.tp) }.mkString(", ") + ") extends ((" + args.map(s => tpeToDocument(s.tp)).mkString(", ") + ") => " + tpeToDocument(body.typeT) + ") {\n" +
        "def apply(" + args.map(s => s + ": " + tpeToDocument(s.tp)).mkString(", ") + ") = "
      val cgDoc = blockToDocument(body)
      stream.println(genCode + cgDoc + "\n}")
    }


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
    case Statement(sym, n@MirrorAggregatorNew()) => doc"val $sym = new Aggregator[${n.typeE}]()"
    case Statement(sym, StringDiff(str1, str2)) => doc"val $sym = $str1.compareToIgnoreCase($str2)"
    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"
    case st@Statement(sym, MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), f@_)) if IndexAnalysis.enabled => {
      val cols = (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
      val idx = indexes(store.asInstanceOf[Sym[_]]).find(_.cols == cols) match {
        case Some(Index(_,_,_,id)) => id
      }
      doc"val $sym = $store.slice($idx, $key, $f)"
    }
    case _ => super.stmtToDocument(stmt)
  }

  def analyzeIndices = {
    IndexAnalysis.enabled = true
    allBlocks.foreach(b => IndexAnalysis.optimize[Any](b._2.body)(AnyType))
    java.lang.System.out.println("Primary Index")
    IndexAnalysis.primaryIndex.foreach { case (s: Sym[_], l: Seq[_]) => java.lang.System.out.println(s.name + s.id + " -> " + l.mkString("{", ",", "}")) }
    java.lang.System.out.println("\nSecondary Index")
    IndexAnalysis.secondaryIndex.foreach { case (s: Sym[_], l: collection.mutable.Set[Seq[Int]]) => java.lang.System.out.println(s.name + s.id + " -> " + l.map(_.mkString("{", ",", "}")).mkString("{", ",", "}")) }
    java.lang.System.out.println("\nMin Slice Index")
    IndexAnalysis.minSliceIndex.foreach { case (s: Sym[_], l: collection.mutable.Set[Seq[Int]]) => java.lang.System.out.println(s.name + s.id + " -> " + l.map(_.mkString("{", ",", "}")).mkString("{", ",", "}")) }
    java.lang.System.out.println("\nMax Slice Index")
    IndexAnalysis.maxSliceIndex.foreach { case (s: Sym[_], l: collection.mutable.Set[Seq[Int]]) => java.lang.System.out.println(s.name + s.id + " -> " + l.map(_.mkString("{", ",", "}")).mkString("{", ",", "}")) }

  }

  def generateNewStore(c: Sym[_], mname: Option[String]): String = {

    if (!IndexAnalysis.enabled)
      indexes += c -> collection.mutable.ArrayBuffer(Index(List(), IHash, true, 0))
    else {
      var count = 0
      IndexAnalysis.primaryIndex.get(c) match {
        case Some(l) => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) += Index(l.toList, IHash, true, count); count = count + 1
        case _ =>
      }
      IndexAnalysis.secondaryIndex.get(c) match {
        case Some(ll) => ll.foreach(l => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) += Index(l.toList, IHash, false, count)); count = count + 1
        case _ =>
      }
      if (!indexes.contains(c))
        indexes += c -> collection.mutable.ArrayBuffer(Index(List(), IList, false, 0))
    }

    def generateNew: String = "new MStore[GenericEntry](" + indexes(c).size + ", Array[EntryIdx[GenericEntry]](" + indexes(c).map(_.cols.mkString("new GenericOps(List(", ", ", "))")).mkString(", ") + "))"
    val symbolName = c.name + c.id
    val mapAlias = mname match {
      case Some(mapName) =>
        s"val $mapName = $symbolName"
      case None =>
        s""
    }
    s"\nval $symbolName = $generateNew \n" +
      indexes(c).map(i => symbolName + s".index($i)").mkString("\n") +
      s"$mapAlias"
  }
}
