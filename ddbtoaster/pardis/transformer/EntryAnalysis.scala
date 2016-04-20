package transformer

import ch.epfl.data.sc.pardis.property.{TypedPropertyFlag, Property}
import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ch.epfl.data.sc.pardis.types.{AnyType, RecordType, PardisType}
import ddbt.lib.store.deep.DateIRs.DateType


import ddbt.lib.store.deep._

import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.ir._

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

    case sym -> (StoreGet(store, _, key@Def(SteNewSEntry(_, _)), _)) => add(key, store); add(sym, store); ()
    case sym -> (StoreGet(store, _, key@Def(SteSampleSEntry(_, _)), _)) => add(key, store); add(sym, store); ()
    case sym -> (StoreGet(store, _, key@Def(GenericEntryApplyObject(_, _)), _)) => add(key, store); add(sym, store); ()

    case sym -> (StoreInsert(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (StoreInsert(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()

    case sym -> (StoreUpdate(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (StoreUpdate(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()


    case sym -> (StoreDelete1(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()


    case sym -> (StoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(AggregatorMaxObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (StoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(AggregatorMinObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (StoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()
    case sym -> (StoreSlice(store, _, key@Def(SteSampleSEntry(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()

    case sym -> (StoreForeach(store, f@Def(PardisLambda(_, i, _)))) => add(i, store); add(f, store); ()

    case sym -> (StoreRange(store, _, key1@Def(GenericEntryApplyObject(_, _)), key2@Def(GenericEntryApplyObject(_, _)), _, _, _)) => add(key1, store); add(key2, store); ()

    case sym -> (StoreDelete2(store, _, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()


    case sym -> (AggregatorResult(agg)) => addVar(sym, agg); ()
    case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) if EntryTypes.contains(rhs) => addVar(lhs, rhs); ()
    case sym -> (PardisReadVar(PardisVar(v@Sym(_, _)))) if EntryTypes.contains(v) => addVar(sym, v); ()
    case sym -> (ArrayBufferAppend(ab, el)) => addVar(ab, el); ()
    case sym -> (ArrayBufferSortWith(ab@Sym(_, _), f@Def(PardisLambda2(_, i1, i2, _)))) => addVar(f, ab); addVar(i1, ab); addVar(i2, ab); ()
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

  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val res = super.optimize(node)
    ruleApplied()
    res
  }

  def changeGlobal(global: List[Sym[_]]) = global.map(x => apply(x.asInstanceOf[Sym[Any]])(AnyType).asInstanceOf[Sym[_]])

  def hashfn(cols: Seq[Int], s: SEntry): Rep[SEntry => Int] = {
    //System.err.println(s"Generating hash function for ${s.tp} with cols $cols")
    implicit val entryTp = s.tp
    __lambda((e: Rep[SEntry]) => {
      val hash = __newVar(unit(0xcafebabe))
      val mix = __newVar(unit(0))
      cols.foreach(c => {
        implicit val tp = s.sch(c - 1).asInstanceOf[TypeRep[Any]]
        //System.err.println(s"Getting field $c of $e in hash")
        __assign(mix, unit(0xcc9e2d51) * infix_hashCode(fieldGetter(e, "_" + c)(tp)))
        __assign(mix, __readVar(mix) << unit(15) | __readVar(mix) >>> unit(-15))
        __assign(mix, __readVar(mix) * unit(0x1b873593))
        __assign(mix, __readVar(mix) ^ __readVar(hash))
        __assign(mix, __readVar(mix) << unit(13) | __readVar(mix) >>> unit(-13))
        __assign(hash, __readVar(mix) * unit(5) + unit(0xe6546b64))
      })
      __assign(hash, __readVar(hash) ^ unit(2))
      __assign(hash, __readVar(hash) ^ (__readVar(hash) >>> unit(16)))
      __assign(hash, __readVar(hash) * unit(0x85ebca6b))
      __assign(hash, __readVar(hash) ^ (__readVar(hash) >>> unit(13)))
      __assign(hash, __readVar(hash) * unit(0xc2b2ae35))
      __assign(hash, __readVar(hash) ^ (__readVar(hash) >>> unit(16)))
      __readVar(hash)
    })
  }

  def equal_cmp(cols: Seq[Int], s: SEntry): Rep[(SEntry, SEntry) => Int] = {
    if (cols == Nil) {
      //No index Analysis
      implicit val entryTp = s.tp
      __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
        val allCols = (1 until s.sch.size).toList
        val allConds = allCols.map(i => {
          implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]
          val v1 = fieldGetter(e1, "_" + i)(tp)
          val v2 = fieldGetter(e2, "_" + i)(tp)
          val vNull = nullValue(s.sch(i - 1))
          (v1 __== vNull) || (v2 __== vNull) || (v1 __== v2)
        }).reduce(_ && _)
        __ifThenElse(allConds, unit(0), unit(1))
      })
    } else {
      implicit val entryTp = s.tp
      __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
        val allConds: Rep[Boolean] = cols.map(i => {
          implicit val tp = s.sch(i - 1).asInstanceOf[TypeRep[Any]]
          val v1 = fieldGetter(e1, "_" + i)(tp)
          val v2 = fieldGetter(e2, "_" + i)(tp)
          val vNull = nullValue(s.sch(i - 1))
          v1 __== v2
        }).reduce(_ && _)
        __ifThenElse(allConds, unit(0), unit(1))
      })
    }
  }

  def order_cmp[R: TypeRep](f: Rep[(GenericEntry => R)], s: SEntry): Rep[(SEntry, SEntry) => Int] = {
    implicit val entryTp = s.tp
    val fdef = Def.unapply(f).get.asInstanceOf[PardisLambda[_, _]]
    entryTypes += fdef.i.asInstanceOf[Sym[_]] -> s.sch
    __lambda((e1: Rep[SEntry], e2: Rep[SEntry]) => {
      val f_ = f.asInstanceOf[Rep[SEntry => R]]
      val r1 = __app(f_).apply(e1)
      val r2 = __app(f_).apply(e2)
      __ifThenElse(Equal(r1, r2), unit(0), __ifThenElse(ordering_gt(r1, r2), unit(1), unit(-1)))
    })
  }

  def schema(s: ExpressionSymbol[_]): List[TypeRep[_]] = entryTypes(s) match {
    case TypeVar(ref) => schema(ref)
    case sch: List[TypeRep[_]] => sch
  }

  rewrite += statement {
    case sym -> (GenericEntryApplyObject(Constant("SteNewSEntry"), Def(LiftedSeq(args)))) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      __new[SEntry](args.zipWithIndex.map(t => ("_" + (t._2 + 1), true, t._1)): _*)
    }
    case sym -> (GenericEntryApplyObject(Constant("SteSampleSEntry"), Def(LiftedSeq(args)))) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      val cols = args.zipWithIndex.collect {
        case (Constant(v: Int), i) if i < args.size / 2 => v -> (args(i + args.size / 2))
      }.toMap
      implicit val entTp = SEntry(sch).tp
      val allargs = (1 until (sch.size + 1)).map(c => ("_" + c, cols getOrElse(c, nullValue(sch(c - 1)))))
      __new[SEntry](allargs.map(a => (a._1, true, a._2)): _*)
    }

    case sym -> (SteNewSEntry(_, args)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      implicit val entTp = SEntry(sch).tp
      __new[SEntry](args.zipWithIndex.map(t => ("_" + (t._2 + 1), true, t._1)): _*)
    }
    case sym -> (SteSampleSEntry(_, args)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      val cols = args.toMap
      implicit val entTp = SEntry(sch).tp
      val allargs = (1 until (sch.size + 1)).map(c => ("_" + c, cols getOrElse(c, nullValue(sch(c - 1)))))
      __new[SEntry](allargs.map(a => (a._1, true, a._2)): _*)
    }
    case sym -> (PardisNewVar(v)) if entryTypes.contains(sym) => {
      val sch = schema(sym)
      //System.err.println(s"Changing var $sym")
      implicit val entTp = SEntry(sch).tp
      __newVarNamed[SEntry](v.asInstanceOf[Rep[SEntry]], sym.name).e.asInstanceOf[Rep[Any]]
    }
    case sym -> (ab: ArrayBufferNew2[_]) if ab.typeA == GenericEntryType => {
      val sch = schema(sym)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      __newArrayBuffer[SEntry]()
    }
    case sym -> (StoreNew3(n, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) if ops.size > 0 && !Def.unapply(ops(0)).get.isInstanceOf[EntryIdxApplyObject[_]] => {
      val sch = schema(sym)
      val entry = SEntry(sch)
      implicit val entryTp = entry.tp
      val ops_ = ops.collect {
        case Def(node: EntryIdxGenericCmpObject[_]) => {
          implicit val typeR = node.typeR

          val cols = node.cols.asInstanceOf[Constant[Seq[_]]].underlying.asInstanceOf[Seq[Int]]
          val hl = hashfn(cols, entry)
          val cl = order_cmp(node.f, entry)
          EntryIdx.apply(hl, cl)
        }
        case Def(node: EntryIdxGenericOpsObject) => {

          val cols = node.cols.asInstanceOf[Constant[Seq[_]]].underlying.asInstanceOf[Seq[Int]]
          val hl = hashfn(cols, entry)
          val cl = equal_cmp(cols, entry)
          EntryIdx.apply(hl, cl)
        }
      }
      val newS = __newStore(n, Array.apply(ops_ : _*))
      val ssym = newS.asInstanceOf[Sym[_]]
      //System.err.println(s"Changed ops for $sym to $ssym  with new OPS as $ops_")
      entryTypes += ssym -> TypeVar(sym)
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
      fieldSetter(ent, col, numeric_minus(fieldGetter(ent, col)(tp), v)(tp))(tp)
    }
    case GenericEntryDecrease(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldSetter(ent, col, numeric_minus(fieldGetter(ent, col)(tp), v)(tp))(tp)
    }
    case GenericEntryIncrease(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldSetter(ent, col, numeric_plus(fieldGetter(ent, col)(tp), v)(tp))(tp)
    }
    case GenericEntry$plus$eq(ent: Sym[_], Constant(i: Int), v@_) if entryTypes.contains(ent) => {
      val sch = schema(ent)
      val col = "_" + i
      implicit val tp = sch(i - 1).asInstanceOf[TypeRep[Any]]
      fieldSetter(ent, col, numeric_plus(fieldGetter(ent, col)(tp), v)(tp))(tp)
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
      val i_ = Sym[SEntry](i.id)

      val f_ = (e: Rep[SEntry]) => f(e.asInstanceOf[Rep[Nothing]])
      PardisLambda(f_, i_, o)(entTp, l.typeS)

    }
    case l@PardisLambda2(f, i1: Sym[GenericEntry], i2: Sym[GenericEntry], o) if entryTypes.contains(i1) && i1.tp == GenericEntryType => {
      val sch = schema(i1)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      val i1_ = Sym[SEntry](i1.id)
      val i2_ = Sym[SEntry](i2.id)
      val f_ = (e1: Rep[SEntry], e2: Rep[SEntry]) => f(e1.asInstanceOf[Rep[Nothing]], e2.asInstanceOf[Rep[Nothing]])
      PardisLambda2(f_, i1_, i2_, o)(entTp, entTp, l.typeS)

    }
  }
  rewrite += remove {
    case n: EntryIdxGenericCmpObject[_] => ()
    case n: EntryIdxGenericOpsObject => ()
    case ArrayApplyObject(Def(LiftedSeq(args))) if (args.foldLeft(false)((res, arg) => {
      val argdef = Def.unapply(arg).get
      res || argdef.isInstanceOf[EntryIdxGenericCmpObject[_]] || argdef.isInstanceOf[EntryIdxGenericOpsObject]
    })) => ()
  }

}
