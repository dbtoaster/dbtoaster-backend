package ddbt.transformer

import ch.epfl.data.sc.pardis.property.{Property, TypedPropertyFlag}
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.types.{AnyType, PardisType, RecordType, UnitType}
import ddbt.lib.store.deep.DateIRs.DateType
import ddbt.lib.store.deep._
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.ir._
import ddbt.codegen.Optimizer

/**
  * Created by sachin on 08.04.16.
  */

case class TypeVar(val ref: ExpressionSymbol[_]) {}

object SEntryFlag extends TypedPropertyFlag[SEntry]

object SchemaFlag extends TypedPropertyFlag[StoreSchema]

case class StoreSchema(val sch: List[PardisType[_]] = List()) extends Property {
  val flag = SchemaFlag
}

case class SEntry(val sch: List[PardisType[_]] = List()) extends ddbt.lib.store.Entry(0) with Property {
  def copy = ???

  override def copyFrom(sEntry: ddbt.lib.store.Entry) = ???

  import ddbt.lib.store.deep.GenericEntryIRs.GenericEntryType

  val flag = SEntryFlag
  val name = if (sch == Nil) "GenericEntry" else s"SEntry" + sch.size + "_" + sch.map(c => if (c == DateType) 'T' else pardisTypeToString(c).charAt(0)).mkString("")
  val tp = if (sch == Nil) GenericEntryType.asInstanceOf[PardisType[SEntry]] else new RecordType[SEntry](StructTags.ClassTag(name), None)

}

class EntryAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  def add(key: Any, store: Rep[Store[_]]) = {
    //System.err.println(s"Adding $key from store $store")
    EntryTypes += key.asInstanceOf[Sym[_]] -> TypeVar(store.asInstanceOf[Sym[_]])
  }

  def addVar(key: Any, other: Any) = {
    //System.err.println(s"Adding $key from var $other")
    EntryTypes += key.asInstanceOf[Sym[_]] -> TypeVar(other.asInstanceOf[Sym[_]])
  }

  val EntryTypes = collection.mutable.HashMap[Sym[_], Any]()

  analysis += statement {
    //      case sym -> (GenericEntryApplyObject(_, _)) => EntryTypes += sym -> EntryTypeRef; ()

    case sym -> (StoreGetCopy(store, _, key@Def(SteNewSEntry(_, _)))) => add(key, store); add(sym, store); ()
    case sym -> (StoreGetCopy(store, _, key@Def(SteSampleSEntry(_, _)))) => add(key, store); add(sym, store); ()
    case sym -> (StoreGetCopy(store, _, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); add(sym, store); ()

    case sym -> (StoreUnsafeInsert(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (StoreUnsafeInsert(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()
    case sym -> (StoreInsert(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (StoreInsert(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()

    case sym -> (StoreUpdateCopy(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (StoreUpdateCopy(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()


    case sym -> (StoreDeleteCopy(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()


    case sym -> (StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(AggregatorMaxObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(AggregatorMinObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(AggregatorMedianObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()
    case sym -> (StoreSliceCopy(store, _, key@Def(SteSampleSEntry(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()

    case sym -> (StoreForeach(store, f@Def(PardisLambda(_, i, _)))) => add(i, store); add(f, store); ()

    case sym -> (StoreRange(store, _, key1@Def(GenericEntryApplyObject(_, _)), key2@Def(GenericEntryApplyObject(_, _)), _, _, _)) => add(key1, store); add(key2, store); ()

    case sym -> (StoreDelete2(store, _, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (IfThenElse(_, t, e)) if t.typeT == GenericEntryType => addVar(sym, t.res); ()

    case sym -> (AggregatorResult(agg)) => addVar(sym, agg); ()
    case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) if EntryTypes.contains(rhs) => addVar(lhs, rhs); ()
    case sym -> (PardisReadVar(PardisVar(v@Sym(_, _)))) if EntryTypes.contains(v) => addVar(sym, v); ()
    case sym -> (ArrayBufferAppend(ab, el: Sym[_])) if el.tp == GenericEntryType => addVar(ab, el); ()
    case sym -> (ArrayBufferApply(ab: Sym[_], _)) if EntryTypes.contains(ab) => addVar(sym, ab); ()
    case sym -> (ArrayBufferSortWith(ab@Sym(_, _), f@Def(PardisLambda2(_, i1, i2, _)))) => addVar(f, ab); addVar(i1, ab); addVar(i2, ab); addVar(sym, ab); ()
    case s -> (StoreNew3(_, _)) => {
      val stype = s.attributes.get(SchemaFlag).getOrElse(StoreSchema())
      //System.err.println(s"Adding schema ${stype} for $s")
      EntryTypes += s -> stype.sch
      ()
    }

  }
}

class EntryTransformer(override val IR: StoreDSL, val entryTypes: collection.mutable.HashMap[ExpressionSymbol[_], Any]) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR._

  val structsDefMap = collection.mutable.HashMap.empty[StructTags.StructTag[SEntry], PardisStructDef[Any]]
  val genOps = collection.mutable.HashMap[(Seq[Int], SEntry), Rep[EntryIdx[SEntry]]]()
  val genCmp = collection.mutable.HashMap[(Seq[Int], Int, SEntry), Rep[EntryIdx[SEntry]]]()
  val genFixRngOps = collection.mutable.HashMap[(Seq[(Int, Int, Int)], SEntry), Rep[EntryIdx[SEntry]]]()

  def super_optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val analyseProgram = classOf[RuleBasedTransformer[StoreDSL]].getDeclaredMethod("analyseProgram", classOf[Block[T]], classOf[TypeRep[T]])
    analyseProgram.setAccessible(true)
    val isDone = classOf[RecursiveRuleBasedTransformer[StoreDSL]].getDeclaredField("isDone")
    isDone.setAccessible(true)
    var currentBlock = node
    var counter = 0
    while (isDone.get(this) == false && counter < THRESHOLD) {

      analyseProgram.invoke(this, currentBlock, implicitly[TypeRep[T]])
      postAnalyseProgram(currentBlock)
      isDone.set(this, true)
      currentBlock = transformProgram(currentBlock)
      counter += 1
    }
    if (counter >= THRESHOLD) {
      System.err.println(s"Recursive transformer ${getName} is not converted yet after [${scala.Console.RED}$counter${scala.Console.RESET}] rounds")
    }
    currentBlock
  }

  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val res = super_optimize(node)
    ruleApplied()
    res
  }

  def changeGlobal(global: List[Sym[_]]) = global.map(x => apply(x.asInstanceOf[Sym[Any]])(AnyType).asInstanceOf[Sym[_]])

  def hashFixedRangeFn(colsRange: Seq[(Int, Int, Int)], s: SEntry): Rep[SEntry => Int] = {
    implicit val entryTp = s.tp
    __lambda((e: Rep[SEntry]) => {
      val hash = __newVar(unit(0))
      colsRange.foreach(c => {
        val w = c._3 - c._2
        if(w > 1) {
          val weight = unit(w)
          val colval = fieldGetter(e, "_" + c._1)(IntType) - unit(c._2)
          __assign(hash, __readVar(hash) * weight + colval)
        }
      })
      __readVar(hash)
    })
  }

  def hashfn(cols: Seq[Int], s: SEntry): Rep[SEntry => Int] = {
    //System.err.println(s"Generating hash function for ${s.tp} with cols $cols")
    def elemhash(value: Rep[Any])(implicit tp: TypeRep[Any]): Rep[Int] = value match {
      //      case v: Rep[Long] => v.toInt
      //      case v: Rep[Int] => v
      case v => infix_hashCode(value)
    }
    implicit val entryTp = s.tp
    __lambda((e: Rep[SEntry]) => {
      val hash = __newVar(unit(0))
      if (cols == Nil)
        throw new Exception("Cols should not be empty for EntryIdx hash")
      cols.foreach(c => {
        implicit val tp = s.sch(c - 1).asInstanceOf[TypeRep[Any]]
        //System.err.println(s"Getting field $c of $e in hash")
        val temp = __readVar(hash)
        __assign(hash, temp ^ (elemhash(fieldGetter(e, "_" + c)(tp)) + unit(0x9e3779b9) + (temp << unit(6)) + (temp >> unit(2))))
      })
      __readVar(hash)
    })
  }

  /* OLD HASH FUNCTION. Could be possibly better, but takes more time (VERIFY!). Also change in GenericOps for C++ and Scala
  def hashfn(cols: Seq[Int], s: SEntry): Rep[SEntry => Int] = {
    //System.err.println(s"Generating hash function for ${s.tp} with cols $cols")
    def elemhash(value: Rep[Any])(implicit tp: TypeRep[Any]): Rep[Int] = value match {
      //      case v: Rep[Long] => v.toInt
      //      case v: Rep[Int] => v
      case v => infix_hashCode(value)
    }
    implicit val entryTp = s.tp
    __lambda((e: Rep[SEntry]) => {
      val hash = __newVar(unit(0xcafebabe))
      if (cols == Nil)
        throw new Exception("Cols should not be empty for EntryIdx hash")
      cols.foreach(c => {
        implicit val tp = s.sch(c - 1).asInstanceOf[TypeRep[Any]]
        //System.err.println(s"Getting field $c of $e in hash")
        val mix_1 = unit(0xcc9e2d51) * elemhash(fieldGetter(e, "_" + c)(tp))
        val mix_2 = (mix_1 << unit(15)) | (mix_1 >>> unit(-15))
        val mix_3 = mix_2 * unit(0x1b873593)
        val mix_4 = mix_3 ^ __readVar(hash)
        val mix_5 = (mix_4 << unit(13)) | (mix_4 >>> unit(-13))
        __assign(hash, mix_5 * unit(5) + unit(0xe6546b64))
      })
      val hash_0 = __readVar(hash) ^ unit(2)
      val hash_1 = hash_0 ^ (hash_0 >>> unit(16))
      val hash_2 = hash_1 * unit(0x85ebca6b)
      val hash_3 = hash_2 ^ (hash_2 >>> unit(13))
      val hash_4 = hash_3 * unit(0xc2b2ae35)
      val hash_5 = hash_4 ^ (hash_4 >>> unit(16))
      hash_5
    })
  }
*/
  def recurseCols(cols: Seq[Int], func: Int => Rep[Boolean], ret: Var[Int]): Rep[Unit] = cols match {
    case h :: Nil => __ifThenElse(func(h), __assign(ret, unit(0)), __assign(ret, unit(1)))(UnitType)
    case h :: tail => __ifThenElse(func(h), recurseCols(tail, func, ret), __assign(ret, unit(1)))(UnitType)
  }

  def equal_cmp(cols: Seq[Int], s: SEntry): Rep[(SEntry, SEntry) => Int] = {
    if (cols == Nil)
      throw new Exception("Cols should not be empty for EntryIdx cmp")
    if (!Optimizer.secondaryIndex) {
      //We might pass some cols (primary key) even if Index analysis is turned off. We dont want to consider them here
      //No index Analysis
      implicit val entryTp = s.tp
      __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
        //If either is sample entry, we want the cols of the sample entry
        val allConds = __newVar(unit(0))
        implicit val tpu = UnitType
        __ifThenElse(fieldGetter(e1, "isSE"), {
          val allCols = (1 to s.sch.size).toList
          val func = (i: Int) => {
            implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]
            val v1 = fieldGetter(e1, "_" + i)(tp)
            val v2 = fieldGetter(e2, "_" + i)(tp)
            val vNull = nullValue(s.sch(i - 1))
            (v1 __== vNull) || (v1 __== v2)
          }
          recurseCols(allCols, func, allConds)
        }, {
          __ifThenElse(fieldGetter(e2, "isSE"), {
            val allCols = (1 to s.sch.size).toList
            val func = (i: Int) => {
              implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]

              val v1 = fieldGetter(e1, "_" + i)(tp)
              val v2 = fieldGetter(e2, "_" + i)(tp)
              val vNull = nullValue(s.sch(i - 1))
              (v2 __== vNull) || (v1 __== v2)
            }
            recurseCols(allCols, func, allConds)
          }, {
            val func = (i: Int) => {
              implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]
              val v1 = fieldGetter(e1, "_" + i)(tp)
              val v2 = fieldGetter(e2, "_" + i)(tp)
              (v1 __== v2)
            }
            recurseCols(cols, func, allConds)
          })
        })
        __readVar(allConds)
      })
    } else {
      implicit val entryTp = s.tp
      __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
        val func = (i: Int) => {
          implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]
          val v1 = fieldGetter(e1, "_" + i)(tp)
          val v2 = fieldGetter(e2, "_" + i)(tp)
          (v1 __== v2)
        }
        val allConds = __newVar(unit(0))
        recurseCols(cols, func, allConds)
        __readVar(allConds)
      })
    }
  }

  def order_cmp[R: TypeRep](f: Rep[(GenericEntry => R)], s: SEntry): Rep[(SEntry, SEntry) => Int] = {
    implicit val entryTp = s.tp
    val fdef = Def.unapply(f).get.asInstanceOf[PardisLambda[_, _]]
    entryTypes += fdef.i.asInstanceOf[Sym[_]] -> s.sch

    def inlineFunction(func: PardisLambda[_, _], arg: Rep[SEntry]) = {
      val symMap = collection.mutable.HashMap[Sym[_], Sym[_]]()

      func.o.stmts.foreach {
        case Statement(sym, GenericEntryGet(self, Constant(i))) => val rep = fieldGetter(arg.asInstanceOf[Sym[_]], "_" + i)(s.sch(i - 1).asInstanceOf[TypeRep[Any]]); symMap += sym -> rep.asInstanceOf[Sym[_]]
      }
      symMap(func.o.res.asInstanceOf[Sym[_]]).asInstanceOf[Sym[R]]
    }
    __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
      val r1 = inlineFunction(fdef, e1)
      val r2 = inlineFunction(fdef, e2)
      if (r1.tp == StringType) {
        val v = IR.StringExtra.StringCompare(r1.asInstanceOf[Rep[String]], r2.asInstanceOf[Rep[String]])
        BooleanExtra.conditional(v > unit(0), unit(1), BooleanExtra.conditional(v < unit(0), unit(-1), unit(0)))
      }
      else
        BooleanExtra.conditional(Equal(r1, r2), unit(0), BooleanExtra.conditional(ordering_gt(r1, r2), unit(1), unit(-1)))
    })
  }

  def schema(s: ExpressionSymbol[_]): List[TypeRep[_]] = entryTypes(s) match {
    case TypeVar(ref) => schema(ref)
    case sch: List[TypeRep[_]] => sch
  }

  rewrite += statement {
    case sym -> (agg@AggregatorMaxObject(f)) if entryTypes.contains(sym) =>
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      Aggregator.max(f)(entTp, agg.typeR, agg.order)

    case sym -> (agg@AggregatorMinObject(f)) if entryTypes.contains(sym) =>
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      Aggregator.min(f)(entTp, agg.typeR, agg.order)

    case sym -> (agg@AggregatorMedianObject(f)) if entryTypes.contains(sym) =>
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      Aggregator.median(f)(entTp, agg.typeR, agg.order)

    case sym -> (res@AggregatorResult(self)) if entryTypes.contains(sym) =>
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp.asInstanceOf[TypeRep[Entry]]
      aggregatorResult(self)(entTp)

    case sym -> (StoreGetCopy(self, idx, key)) if !sym.tp.isInstanceOf[RecordType[_]] => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      self.asInstanceOf[Rep[Store[SEntry]]].getCopy(idx, key.asInstanceOf[Rep[SEntry]])
    }

    case sym -> (GenericEntryApplyObject(Constant("SteNewSEntry"), Def(LiftedSeq(args)))) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      val allargs: Seq[(String, Boolean, Expression[Any])] = (if (Optimizer.secondaryIndex) Nil else List(("isSE", true, unit(false)))) ++ args.zipWithIndex.map(t => ("_" + (t._2 + 1), true, t._1))
      __new[SEntry](allargs: _*)
    }
    case sym -> (GenericEntryApplyObject(Constant("SteSampleSEntry"), Def(LiftedSeq(args)))) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      val cols = args.zipWithIndex.collect {
        case (Constant(v: Int), i) if i < args.size / 2 => v -> (args(i + args.size / 2))
      }.toMap
      implicit val entTp = SEntry(sch).tp
      val allargs = (if (Optimizer.secondaryIndex) Nil else List(("isSE", true, unit(true)))) ++ (1 until (sch.size + 1)).map(c => ("_" + c, cols getOrElse(c, nullValue(sch(c - 1))))).map(a => (a._1, true, a._2))
      __new[SEntry](allargs: _*)
    }

    case sym -> (SteNewSEntry(_, args)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      val allargs = (if (Optimizer.secondaryIndex) Nil else List(("isSE", true, unit(false)))) ++ args.zipWithIndex.map(t => ("_" + (t._2 + 1), true, t._1))
      __new[SEntry](allargs: _*)
    }
    case sym -> (SteSampleSEntry(_, args)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      val cols = args.toMap
      implicit val entTp = SEntry(sch).tp
      val allargs = (if (Optimizer.secondaryIndex) Nil else List(("isSE", true, unit(true)))) ++ (1 until (sch.size + 1)).map(c => ("_" + c, cols getOrElse(c, nullValue(sch(c - 1))))).map(a => (a._1, true, a._2))
      __new[SEntry](allargs: _*)
    }
    case sym -> (PardisNewVar(v)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      //System.err.println(s"Changing var $sym")
      implicit val entTp = SEntry(sch).tp
      __newVarNamed[SEntry](v.asInstanceOf[Rep[SEntry]], sym.name).e.asInstanceOf[Rep[Any]]
    }
    case sym -> (PardisReadVar(v)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      __readVar(v.asInstanceOf[Var[SEntry]])
    }
    case sym -> (ab: ArrayBufferNew2[_]) if ab.typeA == GenericEntryType => {
      val sch = schema(sym)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      __newArrayBuffer[SEntry]()
    }
    case sym -> (ab@ArrayBufferApply(self, i)) if ab.typeA == GenericEntryType => {
      val sch = schema(self.asInstanceOf[Sym[_]])
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      self.asInstanceOf[Rep[ArrayBuffer[SEntry]]].apply(i)
    }
    case sym -> (ite@IfThenElse(c, t, e)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp.asInstanceOf[TypeRep[Any]]
      toAtom(PardisIfThenElse(c, t, e)(entTp))(entTp)
    }
    case sym -> (StoreIndex(self: Sym[_], idx, idxType, uniq, otherIdx)) if !sym.tp.asInstanceOf[IdxType[_]].typeE.isInstanceOf[RecordType[_]] => {
      val sch = schema(self)
      implicit val entTp = SEntry(sch).tp
      self.asInstanceOf[Rep[Store[SEntry]]].index(idx, idxType, uniq, otherIdx)
    }
    case sym -> (StoreNew3(n, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) if ops.size > 0 && !Def.unapply(ops(0)).get.isInstanceOf[EntryIdxApplyObject[_]] => {
      val sch = schema(sym)
      val entry = SEntry(sch)
      implicit val entryTp = entry.tp
      val tag = entryTp.asInstanceOf[RecordType[SEntry]].tag
      val allfields = (if (Optimizer.secondaryIndex) Nil else List(StructElemInformation("isSE", BooleanType.asInstanceOf[TypeRep[Any]], true))) ++ sch.zipWithIndex.map(t => StructElemInformation("_" + (t._2 + 1), t._1.asInstanceOf[TypeRep[Any]], true))
      structsDefMap += (tag -> PardisStructDef(tag, allfields, Nil).asInstanceOf[PardisStructDef[Any]])
      val ops_ = ops.collect {
        case Def(node: EntryIdxGenericCmpObject[_]) => {
          implicit val typeR = node.typeR
          //SBJ: TODO: Handle duplicity
          val cols = node.cols match {
            case Constant(seq: Seq[Int]) => seq
            //            case _ => Nil
          }
          val hl = hashfn(cols, entry)
          val cl = order_cmp(node.f, entry)
          val ordCol = Index.getColumnNumFromLambda(Def.unapply(node.f).get.asInstanceOf[PardisLambda[_, _]])
          lazy val rep = EntryIdx.apply(hl, cl, unit(entry.name + "_Idx" + cols.mkString("") + s"_$ordCol"))
          genCmp getOrElseUpdate((cols, ordCol, entry), rep)
        }
        case Def(node: EntryIdxGenericOpsObject) => {

          val cols = node.cols match {
            case Constant(seq: Seq[Int]) => seq
            //            case _ => Nil
          }
          lazy val news = EntryIdx.apply(hashfn(cols, entry), equal_cmp(cols, entry), unit(entry.name + "_Idx" + cols.mkString("")))
          genOps getOrElseUpdate((cols, entry), news)
        }
        case Def(node: EntryIdxGenericFixedRangeOpsObject) => {
          if (!Optimizer.fixedRange)
            throw new IllegalStateException("Fixed range ops object without fixed range optimization")
          val cmpFunc = __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => unit(0))
          val colsRange = node.colsRange.asInstanceOf[Constant[Seq[_]]].underlying.asInstanceOf[Seq[(Int, Int, Int)]]
          lazy val rep = EntryIdx.apply(hashFixedRangeFn(colsRange, entry), cmpFunc, unit(entry.name + "_Idx" + colsRange.map(t => s"${t._1}f${t._2}t${t._3}").mkString("_")))
          genFixRngOps getOrElseUpdate((colsRange, entry), rep)
        }
      }
      val newS = __newStoreNamed2(sym.name, n, Array.apply(ops_ : _*))
      val ssym = newS.asInstanceOf[Sym[_]]
      //System.err.println(s"Changed ops for $sym to $ssym  with new OPS as $ops_")
      entryTypes += ssym -> TypeVar(sym)
      ssym.attributes += sym.attributes.get(IndexesFlag).get
      ssym.attributes += entry
      newS
    }

  }
  rewrite += rule {
    case GenericEntryGet(ent: Sym[_], Constant(i: Int)) if entryTypes.contains(ent) => {
      //System.err.println(s"Changed GenericEntryGet $ent $i")
      val sch = schema(ent)
      if (i > sch.size || i <= 0)
        throw new IllegalArgumentException("Accessing a column which is not in schema")
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldGetter(ent, "_" + i)(tp)
    }
    case GenericEntry$minus$eq(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldDecr(ent, col, v)(tp)
    }
    case GenericEntryDecrease(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldDecr(ent, col, v)(tp)
    }
    case GenericEntryIncrease(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldIncr(ent, col, v)(tp)
    }
    case GenericEntry$plus$eq(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldIncr(ent, col, v)(tp)
    }
    case GenericEntryUpdate(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      val col = "_" + i
      fieldSetter(ent, col, v)(tp)
    }

  }
  rewrite += rule {
    case l@PardisLambda(f, i: Sym[GenericEntry], o) if entryTypes.contains(i) && (i.tp == GenericEntryType || i.tp == EntryType) => {
      val sch = schema(i)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      val i_ = Sym[SEntry](i.id, i.name)

      val f_ = (e: Rep[SEntry]) => f(e.asInstanceOf[Rep[Nothing]])
      PardisLambda(f_, i_, o)(entTp, l.typeS)

    }
    case l@PardisLambda2(f, i1: Sym[GenericEntry], i2: Sym[GenericEntry], o) if entryTypes.contains(i1) && i1.tp == GenericEntryType => {
      val sch = schema(i1)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      val i1_ = Sym[SEntry](i1.id, i1.name)
      val i2_ = Sym[SEntry](i2.id, i2.name)

      val f_ = (e1: Rep[SEntry], e2: Rep[SEntry]) => f(e1.asInstanceOf[Rep[Nothing]], e2.asInstanceOf[Rep[Nothing]])
      PardisLambda2(f_, i1_, i2_, o)(entTp, entTp, l.typeS)

    }
  }
  rewrite += remove {
    case n: EntryIdxGenericCmpObject[_] => ()
    case n: EntryIdxGenericOpsObject => ()
    case n: EntryIdxGenericFixedRangeOpsObject => ()
    case ArrayApplyObject(Def(LiftedSeq(args))) if {
      args match {
        case Def(EntryIdxGenericOpsObject(_)) :: xs => true
        case Def(EntryIdxGenericCmpObject(_, _)) :: xs => true
        case Def(EntryIdxGenericFixedRangeOpsObject(_)) :: xs => true
        case _ => false
      }
    } => ()
  }

}
