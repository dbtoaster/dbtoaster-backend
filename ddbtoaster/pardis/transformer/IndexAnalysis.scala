package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.{Constant, PardisLambda}
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.property.{Property, TypedPropertyFlag}
import ch.epfl.data.sc.pardis.types.AnyType
import ddbt.codegen.Optimizer
import ddbt.lib.store._
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 12.04.16.
  */
object IndexedColsFlag extends TypedPropertyFlag[IndexedCols]

object IndexesFlag extends TypedPropertyFlag[Indexes]

case class Index(val idxNum: Int, val cols: List[Int], tp: IndexType, unique: Boolean = false, sliceIdx: Int = -1, val f: PardisLambda[_, _] = null, val colsRange: List[(Int, Int, Int)] = null) {
  override def toString = idxNum + ", " + tp + ", " + unique + ", " + sliceIdx
}

class IndexedCols extends Property {
  val flag = IndexedColsFlag
  var primary: Seq[Int] = Nil
  var fixedrange: Seq[(Int, Int, Int)] = Nil
  val secondary = collection.mutable.Set[Seq[Int]]()
  val min = collection.mutable.Set[(Seq[Int], PardisLambda[_, _])]()
  val max = collection.mutable.Set[(Seq[Int], PardisLambda[_, _])]()
}

object IndexedCols {
  def unapply(i: IndexedCols) = Some(i.primary, i.secondary, i.min, i.max)
}

class Indexes extends Property {
  val flag = IndexesFlag


  val indexes = collection.mutable.ArrayBuffer[Index]()

  def add(cols: IndexedCols) = {
    var count = 0

    val primaryIdxType = if (Optimizer.analyzeIndex) IHash else IList
    if (cols.primary != Nil) {
      if (cols.fixedrange == Nil || !Optimizer.fixedRange)
        indexes += Index(count, cols.primary.toList, primaryIdxType, Optimizer.analyzeIndex); //IdxList with unique = false  OR IdxHash with unique = true
      else {
        val size = cols.fixedrange.foldLeft(1)((acc, cur) => acc * (cur._3 - cur._2))
        indexes += Index(count, null, IDirect, true, size, null, cols.fixedrange.toList) //SBJ: Fixme:   Passing size as sliceIdx
      }
      count = count + 1
    } else {
      throw new Exception("Must have primary index")
    }
    //SBJ: FIXME: In the absence of gets, no primary assigned and the first secondary treated as primary. WIll cause problems if it is KV index. May cause problem otherwise too. Key is subset/superset of actual key, semantics might change
    // SBJ: FIXME: Also causes problems when IndexLookupFusion is disabled and no primary key is inferred.

    cols.secondary.foreach(l => {
      indexes += Index(count, l.toList, IHash, false)
      count = count + 1
    })
    cols.max.foreach({ case (l, f) => {
      indexes += Index(count, l.toList, ISliceHeapMax, false, count + 1, f)
      indexes += Index(count + 1, l.toList, INone, false)
      count = count + 2
    }
    })
    cols.min.foreach({ case (l, f) => {
      indexes += Index(count, l.toList, ISliceHeapMin, false, count + 1, f)
      indexes += Index(count + 1, l.toList, INone, false)
      count = count + 2
    }
    })

    if (count == 0) {
      indexes += Index(0, List(), IList, false)
    }
  }

  def getIdxForSlice(c: Seq[Int]): Int = indexes.find(i => i.cols == c && i.tp == IHash).map(_.idxNum).getOrElse(-1)

  def getIdxForMin(c: Seq[Int]): Int = indexes.find(i => i.cols == c && (i.tp == ISliceHeapMin || i.tp == ISliceMin)).map(_.idxNum).getOrElse(-1)

  def getIdxForMax(c: Seq[Int]): Int = indexes.find(i => i.cols == c && (i.tp == ISliceHeapMax || i.tp == ISliceMax)).map(_.idxNum).getOrElse(-1)
}

class IndexAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  analysis += rule {

    case StoreSliceCopy(sym: Sym[_], _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(AggregatorMaxObject(Def(f@PardisLambda(_, _, _))))) => {
      val idxes = sym.attributes.get[IndexedCols](IndexedColsFlag).getOrElse(new IndexedCols())
      idxes.max += ((args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }) -> f.asInstanceOf[Lambda[_, _]])
      sym.attributes += idxes

      ()
    }
    case StoreSliceCopy(sym: Sym[_], _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), Def(AggregatorMinObject(Def(f@PardisLambda(_, _, _))))) => {
      val idxes = sym.attributes.get[IndexedCols](IndexedColsFlag).getOrElse(new IndexedCols())
      idxes.min += ((args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }) -> f.asInstanceOf[Lambda[_, _]])
      sym.attributes += idxes

      ()
    }
    case StoreSliceCopy(sym: Sym[_], _, Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), z@_) => {
      val idxes = sym.attributes.get[IndexedCols](IndexedColsFlag).getOrElse(new IndexedCols())
      idxes.secondary += (args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v })
      sym.attributes += idxes

      ()
    }
    case StoreSliceCopy(sym: Sym[_], _, Def(SteSampleSEntry(_, args)), z@_) => {
      val idxes = sym.attributes.get[IndexedCols](IndexedColsFlag).getOrElse(new IndexedCols())
      idxes.secondary += (args.map(_._1))
      sym.attributes += idxes

      ()
    }
  }
}

class IndexDecider(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR.{entryRepToGenericEntryOps => _, _}

  val stores = collection.mutable.ArrayBuffer[Sym[_]]()

  val genOps = collection.mutable.HashMap[Seq[Int], Rep[EntryIdx[GenericEntry]]]()
  val genCmp = collection.mutable.HashMap[(Seq[Int], Int), Rep[EntryIdx[GenericEntry]]]()
  val genFixed = collection.mutable.HashMap[Seq[(Int, Int, Int)], Rep[EntryIdx[GenericEntry]]]()

  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val res = super_optimize(node)
    ruleApplied()
    res
  }

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

  rewrite += statement {
    case s -> (StoreNew2()) => {
      val cols = s.attributes.get[IndexedCols](IndexedColsFlag).getOrElse(new IndexedCols())
      val idxes = new Indexes()
      idxes.add(cols)
      //System.err.println(s"Deciding Index for $s")

      val entidxes = idxes.indexes.map(_ match {
        case Index(_, cols, IHash, _, _, _, _) =>
          val rep = EntryIdx.genericOps(unit[Seq[Int]](cols))
          if (!genOps.contains(cols))
            genOps += (cols -> rep)
          rep
        case Index(_, _, IDirect, _, _, _, colsRange) =>
          val rep = EntryIdx.genericFixedRangeOps(unit[Seq[(Int, Int, Int)]](colsRange))
          if (!genFixed.contains(colsRange))
            genFixed += (colsRange -> rep)
          rep
        case Index(_, cols, INone, _, _, _, _) =>
          val rep = EntryIdx.genericOps(unit[Seq[Int]](cols))
          if (!genOps.contains(cols))
            genOps += (cols -> rep)
          rep
        case Index(_, cols, ISliceHeapMax, _, _, f, _) => {
          implicit val tp = f.tp.asInstanceOf[TypeRep[(GenericEntry => Any)]]
          implicit val typeR = f.typeS.asInstanceOf[TypeRep[Any]]
          val ordCol = f.o.stmts(0).rhs match {
            case GenericEntryGet(_, Constant(i)) => i
          }
          val rep = EntryIdx.genericCmp(unit[Seq[Int]](cols), toAtom(f.asInstanceOf[PardisLambda[GenericEntry, Any]]))
          if (!genCmp.contains((cols, ordCol)))
            genCmp += ((cols, ordCol) -> rep)
          rep
        }
        case Index(_, cols, ISliceHeapMin, _, _, f, _) => {
          implicit val tp = f.tp.asInstanceOf[TypeRep[(GenericEntry => Any)]]
          implicit val typeR = f.typeS.asInstanceOf[TypeRep[Any]]
          val rep = EntryIdx.genericCmp(unit[Seq[Int]](cols), toAtom(f.asInstanceOf[PardisLambda[GenericEntry, Any]]))
          val ordCol = f.o.stmts(0).rhs match {
            case GenericEntryGet(_, Constant(i)) => i
          }
          if (!genCmp.contains((cols, ordCol)))
            genCmp += ((cols, ordCol) -> rep)
          rep
        }
        case Index(id, cols, IList, _, _, _, _) =>
          if (Optimizer.analyzeIndex || id != 0)
            throw new Exception("List index should be the only index")
          val rep = EntryIdx.genericOps(unit[Seq[Int]](cols))
          if (!genOps.contains(cols))
            genOps += (cols -> rep)
          rep
      })
      val newS = __newStoreNamed2(s.name, unit(entidxes.size), Array(entidxes: _*))
      idxes.indexes.foreach(i => newS.index(unit(i.idxNum), unit(i.tp.toString), unit(i.unique), unit(i.sliceIdx)))
      val ssym = newS.asInstanceOf[Sym[_]]
      ssym.attributes += idxes
      ssym.attributes += s.asInstanceOf[Sym[_]].attributes.get(SchemaFlag).getOrElse(StoreSchema())
      //System.err.println(s" $s -> $newS")
      newS
    }

  }

  def changeGlobal(global: List[Sym[_]]) = global.map(x => apply(x.asInstanceOf[Sym[Any]])(AnyType).asInstanceOf[Sym[_]])
}


class IndexTransformer(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  //  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
  //    val res = super.optimize(node)
  //    ruleApplied()
  //    res
  //  }
  val aggResultMap = collection.mutable.HashMap[Rep[_], (Rep[Store[_]], Rep[Int], Rep[_])]()
  analysis += rule {
    case StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(AggregatorMaxObject(_))) => {
      val idxes = store.asInstanceOf[Sym[_]].attributes.get[Indexes](IndexesFlag).get
      val cols = args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }
      val idx = idxes.getIdxForMax(cols)
      //System.err.println(s"Added $agg to AggResult")
      aggResultMap += (agg ->(store, unit(idx), key))
      ()
    }
    case StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(AggregatorMinObject(_))) => {
      //System.err.println(s"Looking for index of $store")
      val idxes = store.asInstanceOf[Sym[_]].attributes.get[Indexes](IndexesFlag).get
      val cols = args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }
      val idx = idxes.getIdxForMin(cols)
      //System.err.println(s"Added $agg to AggResult")
      aggResultMap += (agg ->(store, unit(idx), key))
      ()
    }
  }
  rewrite += remove {
    case StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(AggregatorMaxObject(_))) => {
      ()
    }
    case StoreSliceCopy(store, _, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), agg@Def(AggregatorMinObject(_))) => {
      ()
    }
  }
  rewrite += rule {
    case AggregatorResult(agg) => {
      val t = aggResultMap(agg)
      StoreGetCopy(t._1.asInstanceOf[Rep[Store[Entry]]], t._2, t._3.asInstanceOf[Rep[Entry]])
    }
  }
  rewrite += rule {
    case StoreSliceCopy(store, i, key@Def(GenericEntryApplyObject(_, Def(LiftedSeq(args)))), f@_) => {
      val idxes = store.asInstanceOf[Sym[_]].attributes.get[Indexes](IndexesFlag).get
      val cols = args.zipWithIndex.collect { case (Constant(v: Int), i) if i < args.size / 2 => v }
      val idx = idxes.getIdxForSlice(cols)
      StoreSliceCopy(store, unit(idx), key, f)
    }
    case StoreSliceCopy(store, i, key@Def(SteSampleSEntry(_, args)), f@_) => {
      val cols = args.map(_._1)
      val idxes = store.asInstanceOf[Sym[_]].attributes.get[Indexes](IndexesFlag).get
      val idx = idxes.getIdxForSlice(cols)
      StoreSliceCopy(store, unit(idx), key, f)
    }
  }
}

