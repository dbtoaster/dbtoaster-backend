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

case class SEntry(val sch: List[PardisType[_]] = List()) extends Property {

  import ddbt.lib.store.deep.GenericEntryIRs.GenericEntryType

  val flag = SEntryFlag
  val name = if (sch == Nil) "GenericEntry" else s"SEntry" + sch.size + "_" + sch.map(c => if (c == DateType) 'T' else pardisTypeToString(c).charAt(0)).mkString("")
  val tp = if (sch == Nil) GenericEntryType.asInstanceOf[PardisType[SEntry]] else new RecordType[SEntry](StructTags.ClassTag(name), None)

}

//  override def toString = if (sch == Nil) ""
//  else
//    s"""
//       |case class $name(${sch.zipWithIndex.map(t => "var _" + (t._2 + 1) + ": " + pardisTypeToString(t._1)).mkString(", ")})  extends Entry(${sch.size}){
//       |   def copy = $name(${sch.zipWithIndex.map(t => "_" + (t._2 + 1)).mkString(", ")})
//       | }
//       |
//      """.stripMargin
//}

class EntryAnalysis(override val IR: StoreDSL, val schema: Map[ExpressionSymbol[_], List[PardisType[_]]]) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  def add(key: Any, store: Rep[MStore[_]]) = {
    System.err.println(s"Adding $key from store $store")
    EntryTypes += key.asInstanceOf[Sym[_]] -> schema(store.asInstanceOf[Sym[_]])
  }

  def addVar(key: Any, other: Any) = {
    System.err.println(s"Adding $key from var $other")
    EntryTypes += key.asInstanceOf[Sym[_]] -> TypeVar(other.asInstanceOf[Sym[_]])
  }

  val EntryTypes = collection.mutable.HashMap[Sym[_], Any]()
  EntryTypes ++= schema
  analysis += statement {
    //      case sym -> (GenericEntryApplyObject(_, _)) => EntryTypes += sym -> EntryTypeRef; ()

    case sym -> (MStoreGet(store, _, key@Def(SteNewSEntry(_, _)), _)) => add(key, store); add(sym, store); ()
    case sym -> (MStoreGet(store, _, key@Def(SteSampleSEntry(_, _)), _)) => add(key, store); add(sym, store); ()
    case sym -> (MStoreGet(store, _, key@Def(GenericEntryApplyObject(_, _)), _)) => add(key, store); add(sym, store); ()

    case sym -> (MStoreInsert(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (MStoreInsert(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()

    case sym -> (MStoreUpdate(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()
    case sym -> (MStoreUpdate(store, key@Def(SteNewSEntry(_, _)))) => add(key, store); ()


    case sym -> (MStoreDelete1(store, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()


    case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(MirrorAggregatorMaxObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), agg@Def(MirrorAggregatorMinObject(f@Def(PardisLambda(_, i, _)))))) => add(key, store); add(agg, store); add(i, store); add(f, store); ()
    case sym -> (MStoreSlice(store, _, key@Def(GenericEntryApplyObject(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()
    case sym -> (MStoreSlice(store, _, key@Def(SteSampleSEntry(_, _)), f@Def(PardisLambda(_, i, _)))) => add(key, store); add(i, store); add(f, store); ()

    case sym -> (MStoreForeach(store, f@Def(PardisLambda(_, i, _)))) => add(i, store); add(f, store); ()

    case sym -> (MStoreRange(store, _, key1@Def(GenericEntryApplyObject(_, _)), key2@Def(GenericEntryApplyObject(_, _)), _, _, _)) => add(key1, store); add(key2, store); ()

    case sym -> (MStoreDelete2(store, _, key@Def(GenericEntryApplyObject(_, _)))) => add(key, store); ()


    case sym -> (MirrorAggregatorResult(agg)) => addVar(sym, agg); ()
    case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) if EntryTypes.contains(rhs) => addVar(lhs, rhs); ()
    case sym -> (PardisReadVar(PardisVar(v@Sym(_, _)))) if EntryTypes.contains(v) => addVar(sym, v); ()
    case sym -> (ArrayBufferAppend(ab, el)) => addVar(ab, el); ()
    case sym -> (ArrayBufferSortWith(ab@Sym(_, _), f@Def(PardisLambda2(_, i1, i2, _)))) => addVar(f, ab); addVar(i1, ab); addVar(i2, ab); ()
    case s -> (MStoreNew2()) => {
      val sch = schema(s)
      s.attributes += SEntry(sch)
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
      System.err.println(s"Changing var $sym")
      implicit val entTp = SEntry(sch).tp
      __newVarNamed[SEntry](v.asInstanceOf[Rep[SEntry]], sym.name).e.asInstanceOf[Rep[Any]]
    }
    case sym ->(ab:ArrayBufferNew2[_]) if ab.typeA == GenericEntryType => {
      val sch = schema(sym)
      implicit val entTp: TypeRep[SEntry] = SEntry(sch).tp
      __newArrayBuffer[SEntry]()
    }

    //    case sym -> (MStoreNew1(idx,ops)) =>{
    //      val sch = schema(sym)
    //      implicit val entTp: TypeRep[SEntry] = new RecordType[SEntry](getClassTag(sch), None)
    //    }
  }
  rewrite += rule {
    case GenericEntryGet(ent: Sym[_], Constant(i: Int)) if entryTypes.contains(ent) => {
      System.err.println(s"Changed GenericEntryGet $ent $i")
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
    case l@PardisLambda(f, i: Sym[GenericEntry], o) if entryTypes.contains(i) && i.tp == GenericEntryType => {
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
}
