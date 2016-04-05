package ddbt.codegen.prettyprinter

import java.io.PrintWriter

import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.types.{NothingType, Lambda1Type, AnyType, PardisType}
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

  case class Index(val idxNum: Int, val cols: List[Int], tp: IndexType, unique: Boolean = false, sliceIdx: Int = -1, val f: PardisLambda[GenericEntry, _] = null) {
    override def toString = idxNum + ", " + tp + ", " + unique + ", " + sliceIdx
  }


  case class TypeVar(val ref: Sym[_]) {}

  case class Entry(val sch: List[String] = List()) {
    val name = if (sch == Nil) "GenericEntry" else s"SEntry" + sch.size + "_" + sch.map(c => if (c == "Date") 'T' else c.charAt(0)).mkString("")

    override def toString = if (sch == Nil) ""
    else
      s"""
         |case class $name(${sch.zipWithIndex.map(t => "var _" + (t._2 + 1) + ": " + t._1).mkString(", ")})  extends Entry(${sch.size}){
         |   def copy = $name(${sch.zipWithIndex.map(t => "_" + (t._2 + 1)).mkString(", ")})
         | }
         |
      """.stripMargin
  }

  case class EntryIndex(val entry: Entry, val idx: Index, val id: Int) {
    val name = if (entry.name == "GenericEntry")
      if (idx.f == null) "GenericOps" else "GenericCmp"
    else s"${entry.name}_Idx$id"
    val instance = name + (if (name == "GenericOps") s"(List(${idx.cols.mkString(", ")}))" else if (name == "GenericCmp") doc"(${nodeToDocument(idx.f)})" else "")

    override def toString = if (entry.name == "GenericEntry") ""
    else {

      val cmpfn = if (idx.f == null) {
        if (idx.cols == Nil) {
          val cols = (1 until (entry.sch.size + 1))
          s"override def cmp(e1: ${entry.name}, e2: ${entry.name}) = if(${cols.map(c => s"(e1._$c == null.asInstanceOf[${entry.sch(c - 1)}] || e2._$c == null.asInstanceOf[${entry.sch(c - 1)}] || e1._$c == e2._$c)").mkString(" && ")}) 0 else 1"
        }
        else
          s"override def cmp(e1: ${entry.name}, e2: ${entry.name}) = if(${idx.cols.map(c => s"e1._$c == e2._$c").mkString(" && ")}) 0 else 1"
      } else {
        val e1 = fresh[GenericEntry]
        val e2 = fresh[GenericEntry]
        EntryAnalysis.EntryTypes +=(e1 -> entry, e2 -> entry)
        val compareBlock = reifyBlock {

          implicit val tpR = idx.f.typeS.asInstanceOf[TypeRep[Any]]
          val r1 = idx.f.f(e1)
          val r2 = idx.f.f(e2)
          __ifThenElse(Equal(r1, r2), unit(0), __ifThenElse(ordering_gt(r1, r2), unit(1), unit(-1)))
        }

        doc"override def cmp($e1:${entry.name}, $e2: ${entry.name}) = ${blockToDocument(compareBlock)}"
      }

      s"""
         |object $name extends EntryIdx[${entry.name}] {
         |   $cmpfn
         |   override def hash(e: ${entry.name}) = {
         |      var hash:Int = 0xcafebabe
         |      var mix:Int = 0
         |${
        idx.cols.map(c =>
          s"""|      mix = e._$c.hashCode * 0xcc9e2d51
              |      mix = (mix << 15) | (mix >>> -15)
              |      mix *= 0x1b873593
              |      mix ^= hash
              |      mix = (mix << 13) | (mix >>> -13)
              |      hash = mix * 5 + 0xe6546b64
                     """.stripMargin).mkString("\n")
      }
         |      hash ^= 2
         |      hash ^= hash >>> 16
         |      hash *= 0x85ebca6b
         |      hash ^= hash >>> 13
         |      hash *= 0xc2b2ae35
         |      hash ^= hash >>> 16
         |      hash
         |      }
         |}
         |
                """.stripMargin
    }

  }

  val indexes = collection.mutable.HashMap[Sym[_], collection.mutable.ArrayBuffer[Index]]()
  val schema = collection.mutable.HashMap[Sym[_], List[String]]()
  val entries = collection.mutable.HashMap[Sym[_], Entry]()

  object EntryAnalysis extends RuleBasedTransformer[StoreDSL](IR) {
    var typeName = "GenericEntry"

    //    case class EntryTypeRef(var e: Entry = null) {}
    def apply(s: Sym[_]): Entry = EntryTypes(s) match {
      case z@TypeVar(ref) => apply(ref)
      case e@Entry(_) => e

    }

    val EntryTypes = collection.mutable.HashMap[Sym[_], Any]()
    analysis += statement {
      //      case sym -> (GenericEntryApplyObject(_, _)) => EntryTypes += sym -> EntryTypeRef; ()
      case sym -> (MStoreGet(store, _, key@Def(GenericEntryApplyObject(_, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += sym -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreInsert(store, key@Def(GenericEntryApplyObject(_, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreUpdate(store, key@Def(GenericEntryApplyObject(_, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreDelete1(store, key@Def(GenericEntryApplyObject(_, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(MirrorAggregatorMaxObject(f@Def(PardisLambda(_, i, _)))))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += agg.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += i.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += f.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(MirrorAggregatorMinObject(f@Def(PardisLambda(_, i, _)))))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += agg.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += i.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += f.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), f@Def(PardisLambda(_, i, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += i.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += f.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreRange(store, _, key1@Def(GenericEntryApplyObject(_, _)), key2@Def(GenericEntryApplyObject(_, _)), _, _, _)) => EntryTypes += key1.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); EntryTypes += key2.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()
      case sym -> (MStoreDelete2(store, _, key@Def(GenericEntryApplyObject(_, _)))) => EntryTypes += key.asInstanceOf[Sym[_]] -> Entry(schema(store.asInstanceOf[Sym[_]])); ()


      case sym -> (MirrorAggregatorResult(agg)) => EntryTypes += (sym -> EntryTypes(agg.asInstanceOf[Sym[_]])); ()
      case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) if EntryTypes.contains(rhs) => EntryTypes += lhs.asInstanceOf[Sym[_]] -> EntryAnalysis(rhs); ()
      case sym -> (PardisReadVar(PardisVar(v@Sym(_, _)))) if EntryTypes.contains(v) => EntryTypes += sym -> EntryAnalysis(v); ()
      case sym -> (ArrayBufferAppend(ab, el)) => EntryTypes += ab.asInstanceOf[Sym[_]] -> TypeVar(el.asInstanceOf[Sym[_]]); ()
      case sym -> (ArrayBufferSortWith(ab@Sym(_, _), f@Def(PardisLambda2(_, i1, i2, _)))) => EntryTypes += f.asInstanceOf[Sym[_]] -> TypeVar(ab); EntryTypes += i1.asInstanceOf[Sym[_]] -> TypeVar(ab); EntryTypes += i2.asInstanceOf[Sym[_]] -> TypeVar(ab); ()

    }
  }

  object IndexAnalysis extends RuleBasedTransformer[StoreDSL](IR) {
    var enabled = false
    val primaryIndex = collection.mutable.HashMap[Rep[_], Seq[Int]]()
    val secondaryIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[Seq[Int]]]()
    val minSliceIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[(Seq[Int], PardisLambda[GenericEntry, _])]]()
    val maxSliceIndex = collection.mutable.HashMap[Rep[_], collection.mutable.Set[(Seq[Int], PardisLambda[GenericEntry, _])]]()

    analysis += statement {
      case sym -> (node@MStoreGet(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))))) => primaryIndex += (store.asInstanceOf[Rep[_]] -> args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }); ()
      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(MirrorAggregatorMaxObject(Def(f@PardisLambda(_, _, _)))))) => maxSliceIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[(Seq[Int], PardisLambda[GenericEntry, _])]()) += ((args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }) -> f.asInstanceOf[Lambda[GenericEntry, _]]); ()
      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(MirrorAggregatorMinObject(Def(f@PardisLambda(_, _, _)))))) => minSliceIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[(Seq[Int], PardisLambda[GenericEntry, _])]()) += ((args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }) -> f.asInstanceOf[Lambda[GenericEntry, _]]); ()
      case sym -> (node@MStoreSlice(store, _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), z@_)) => secondaryIndex.getOrElseUpdate(store.asInstanceOf[Rep[_]], collection.mutable.HashSet[Seq[Int]]()) += (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }); ()
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
    entries.foreach {
      case (sym, entry) => {
        stream.println(entry)
        indexes(sym).zipWithIndex.map(t => EntryIndex(entry, t._1, t._2)).foreach(stream.println)
      }
    }

    allBlocks.foreach {
      case (className, BlockWithSymbols(body, args)) =>
        val genCode = "class " + className + "(" + global.collect {
          case s: Sym[Any] => s.name + s.id + ": MStore[" + entries(s).name + "]"
        }.mkString(", ") + ") extends ((" + args.map(s => tpeToDocument(s.tp)).mkString(", ") + ") => " + tpeToDocument(body.typeT) + ") {\n" +
          "def apply(" + args.map(s => s + ": " + tpeToDocument(s.tp)).mkString(", ") + ") = "
        val cgDoc = blockToDocument(body)
        stream.println(genCode + cgDoc + "\n}")
    }


  }

  //TODO: SBJ: Bug in ScalaCodeGen
  override def blockToDocument(block: Block[_]): Document = {
    Document.text("{") :: Document.nest(NEST_COUNT,
      mergeDocs(block.stmts.map(s => stmtToDocument(s)), true) :\\: expToDocument(block.res)) :/: "}"
  }


  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if (sym.name != "x") {
      Document.text(sym.name)
    } else {
      super.symToDocument(sym)
    }
  }

  //TODO: SBJ: FixMe: This is a hack. Would fail in cases with different EntryTypes (such as Join)
  override def tpeToDocument[T](tp: TypeRep[T]): Document = if (tp == GenericEntryType)
    Document.text(EntryAnalysis.typeName)
  else super.tpeToDocument(tp)

  val aggResultMap = collection.mutable.HashMap[Sym[_], Document]()

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
    case Statement(sym, MStoreNew2()) => generateNewStore(sym, None)
    case Statement(sym, StringDiff(str1, str2)) => doc"val $sym = $str1.compareToIgnoreCase($str2)"
    case Statement(sym, StringFormat(self, _, Def(LiftedSeq(args)))) => doc"val $sym = $self.format(${args.map(expToDocument).mkDocument(",")})"

    case Statement(sym, MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(MirrorAggregatorMaxObject(_)))) if IndexAnalysis.enabled => {
      val cols = args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }
      val idx = indexes(store.asInstanceOf[Sym[_]]).find(i => i.cols == cols && i.f != null && (i.tp == ISliceMax || i.tp == ISliceHeapMax)) match {
        case Some(Index(id, _, _, _, _, _)) => id
      }
      aggResultMap += agg.asInstanceOf[Sym[_]] -> doc"$store.get($idx, $key)"
      Document.empty
    }


    case Statement(sym, MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(MirrorAggregatorMinObject(_)))) if IndexAnalysis.enabled => {
      val cols = args.zipWithIndex.collect {
        case (Constant(v: Int), i) if i < args.size / 2 => v
      }
      val idx = indexes(store.asInstanceOf[Sym[_]]).find(i => i.cols == cols && i.f != null && (i.tp == ISliceMin || i.tp == ISliceHeapMin)) match {
        case Some(Index(id, _, _, _, _, _)) => id
      }
      aggResultMap += agg.asInstanceOf[Sym[_]] -> doc"$store.get($idx, $key)"
      Document.empty
    }

    case Statement(sym, MirrorAggregatorResult(agg@Sym(_, _))) if aggResultMap.contains(agg) => doc"val $sym = ${aggResultMap(agg)}"

    case Statement(sym, MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), f@_)) if IndexAnalysis.enabled => {
      val cols = args.zipWithIndex.collect {
        case (Constant(v: Int), i) if i < args.size / 2 => v
      }
      val idx = indexes(store.asInstanceOf[Sym[_]]).find(_.cols == cols) match {
        case Some(Index(id, _, _, _, _, _)) => id
      }
      doc"val $sym = $store.slice($idx, $key, $f)"
    }


    case Statement(sym, GenericEntryApplyObject(Constant("SteNewSEntry"), Def(LiftedSeq(args)))) if EntryAnalysis.EntryTypes.contains(sym) => {
      doc"val $sym = ${
        EntryAnalysis(sym).name
      }(${
        args.map(expToDocument).mkDocument(",")
      })"
    }


    case Statement(sym, GenericEntryApplyObject(Constant("SteSampleSEntry"), Def(LiftedSeq(args)))) if EntryAnalysis.EntryTypes.contains(sym) => {
      val entry = EntryAnalysis(sym)
      val cols = args.zipWithIndex.collect {
        case (Constant(v: Int), i) if i < args.size / 2 => v -> expToDocument(args(i + args.size / 2))
      }.toMap
      val allargs = (1 until (entry.sch.size + 1)).map(c => cols getOrElse(c, s"null.asInstanceOf[${entry.sch(c - 1)}]"))
      doc"val $sym = ${entry.name}(${allargs.mkString(", ")})"
    }
    case Statement(sym, GenericEntryGet(ent: Sym[_], Constant(i: Int))) if EntryAnalysis.EntryTypes.contains(ent) => {
      //      if (i > EntryAnalysis.EntryTypes(ent).sch.size || i<=0)
      //        throw new IllegalArgumentException("Accessing a column which is not in schema")
      doc"val $sym = $ent._$i"
    }
    case Statement(sym, GenericEntry$minus$eq(ent: Sym[_], Constant(i: Int), v@_)) if EntryAnalysis.EntryTypes.contains(ent) => {
      doc"val $sym = $ent._$i -= ${expToDocument(v)}"
    }
    case Statement(sym, GenericEntryDecrease(ent: Sym[_], Constant(i: Int), v@_)) if EntryAnalysis.EntryTypes.contains(ent) => {
      doc"val $sym = $ent._$i -= ${expToDocument(v)}"
    }
    case Statement(sym, GenericEntry$plus$eq(ent: Sym[_], Constant(i: Int), v@_)) if EntryAnalysis.EntryTypes.contains(ent) => {
      doc"val $sym = $ent._$i += ${expToDocument(v)}"
    }

    case Statement(sym, GenericEntryIncrease(ent: Sym[_], Constant(i: Int), v@_)) if EntryAnalysis.EntryTypes.contains(ent) => {
      doc"val $sym = $ent._$i += ${expToDocument(v)}"
    }
    case Statement(sym, GenericEntryUpdate(ent: Sym[_], Constant(i: Int), v@_)) if EntryAnalysis.EntryTypes.contains(ent) => {
      doc"val $sym = $ent._$i = ${expToDocument(v)}"
    }
    case Statement(sym, _) if EntryAnalysis.EntryTypes.contains(sym) => {
      val typeName = EntryAnalysis.typeName
      EntryAnalysis.typeName = EntryAnalysis(sym).name
      val doc = super.stmtToDocument(stmt)
      EntryAnalysis.typeName = typeName
      doc
    }
    case _ => super.stmtToDocument(stmt)
  }

  def analyzeIndices = {
    IndexAnalysis.enabled = true
    allBlocks.foreach(b => IndexAnalysis.optimize[Any](b._2.body)(AnyType))
    java.lang.System.out.println("Primary Index")
    IndexAnalysis.primaryIndex.foreach {
      case (s: Sym[_], l: Seq[_]) => java.lang.System.out.println(s.name + s.id + " -> " + l.mkString("{", ", ", "}"))
    }
    java.lang.System.out.println("\nSecondary Index")
    IndexAnalysis.secondaryIndex.foreach {
      case (s: Sym[_], l: collection.mutable.Set[Seq[Int]]) => java.lang.System.out.println(s.name + s.id + " -> " + l.map(_.mkString("{", ",", "}")).mkString("{", ", ", "}"))
    }


  }

  def analyzeEntries(sch: List[(Sym[_], List[String])]) = {
    schema ++= sch
    allBlocks.foreach(b => EntryAnalysis.optimize[Any](b._2.body)(AnyType))
  }

  def generateNewStore(c: Sym[_], mname: Option[String]): String = {
    val sch = schema getOrElse(c, List[String]())
    val entry = Entry(sch)
    if (!IndexAnalysis.enabled)
      indexes += c -> collection.mutable.ArrayBuffer(Index(0, List(), IHash, true))
    else {
      var count = 0
      IndexAnalysis.primaryIndex.get(c) match {
        case Some(l) => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) += Index(count, l.toList, IHash, true);
          count = count + 1
        case _ =>
      }
      IndexAnalysis.secondaryIndex.get(c) match {
        case Some(ll) => ll.foreach(l => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) += Index(count, l.toList, IHash, false));
          count = count + 1
        case _ =>
      }

      IndexAnalysis.maxSliceIndex.get(c) match {
        case Some(ll) => ll.foreach { case (l, f) => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) +=(Index(count, l.toList, ISliceHeapMax, false, count + 1, f), Index(count + 1, l.toList, INone, false)); count = count + 2 }
        case _ =>
      }
      IndexAnalysis.minSliceIndex.get(c) match {
        case Some(ll) => ll.foreach { case (l, f) => indexes getOrElseUpdate(c, collection.mutable.ArrayBuffer[Index]()) +=(Index(count, l.toList, ISliceHeapMin, false, count + 1, f), Index(count + 1, l.toList, INone, false)); count = count + 2 }
        case _ =>
      }

      if (!indexes.contains(c))
        indexes += c -> collection.mutable.ArrayBuffer(Index(0, List(), IList, false))
    }
    val entryidxes = indexes(c).zipWithIndex.map(t => EntryIndex(entry, t._1, t._2))
    def generateNew: String = s"new MStore[${entry.name}]" + s"(" + indexes(c).size + s", Array[EntryIdx[${entry.name}]](${entryidxes.map(_.instance).mkString(", ")}))"
    entries += c -> entry
    val symbolName = c.name + c.id
    val mapAlias = mname match {
      case Some(mapName) =>
        s"val $mapName = $symbolName"
      case None =>
        s""
    }
    s"\nval $symbolName = $generateNew \n" +
      indexes(c).map(i => symbolName + s".index($i)").mkString("\n") +
      s"\n$mapAlias"
  }
}
