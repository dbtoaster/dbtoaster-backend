package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RuleBasedTransformer, RecursiveRuleBasedTransformer}
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.{StructFieldDecr, StructFieldIncr, StoreDSL}
import scala.collection.mutable

/**
  * Created by sachin on 02.05.16.
  */
class IndexInliner(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR._

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

  val indexMap = collection.mutable.HashMap[(Rep[_], Int), Rep[Idx[Entry]]]()
  val updatedCols = collection.mutable.HashMap[Rep[_], collection.mutable.HashSet[Int]]()
  analysis += statement {
    case sym -> (StoreIndex(st, Constant(idx), Constant(idxType), _, _)) if idxType != "INone" => indexMap += (st, idx) -> sym.asInstanceOf[Rep[Idx[Entry]]]; ()
  }
  if (Optimizer.deadIndexUpdate)
  //SBJ: TODO:  Add check to ensure entry comes from a get or slice
    analysis += rule {
      case GenericEntryUpdate(e, Constant(i), _) => updatedCols.getOrElse(e, new mutable.HashSet[Int]()) += i; ()
      case GenericEntryIncrease(e, Constant(i), _) => updatedCols.getOrElse(e, new mutable.HashSet[Int]()) += i; ()
      case GenericEntryDecrease(e, Constant(i), _) => updatedCols.getOrElse(e, new mutable.HashSet[Int]()) += i; ()
      case GenericEntry$minus$eq(e, Constant(i), _) => updatedCols.getOrElse(e, new mutable.HashSet[Int]()) += i; ()
      case GenericEntry$plus$eq(e, Constant(i), _) => updatedCols.getOrElse(e, new mutable.HashSet[Int]()) += i; ()
      case StructFieldSetter(e, idx, _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
      case StructFieldIncr(e, idx, _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
      case StructFieldDecr(e, idx, _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
    }
  rewrite += rule {
    case StoreGetCopy(store, Constant(idx), e, _) => indexMap((store, idx)).getCopy(e)
    case StoreGet(store, Constant(idx), e) => indexMap((store, idx)).get(e)
    case StoreGetCopyDependent(store, Constant(idx), e) => indexMap((store, idx)).getCopyDependent(e)
    case StoreForeach(store, f) => indexMap((store, 0)).foreach(f)
    case StoreSlice(store, Constant(idx), e, f) => indexMap((store, idx)).slice(e, f)
    case StoreUpdateCopyDependent(store, e) => val ref = indexMap((store, 0)).get(e); indexMap.collect { case ((`store`, idx), sym) => sym.updateCopyDependent(e, ref) }; unit()
    case StoreUpdateCopy(store, e) => indexMap.toSeq.sortWith(_._1._2 > _._1._2).collect { case ((`store`, idx), sym) => sym.updateCopy(e, indexMap((store, 0))) }; unit()
    case StoreUpdate(store, e) if updatedCols contains e =>
       val idxes = store.asInstanceOf[Sym[_]].attributes.get(IndexesFlag).get.indexes
      indexMap.collect { case ((`store`, idx), sym) => {
        if (idx != 0 && !updatedCols(e).intersect(idxes(idx).cols.toSet).isEmpty) //SBJ: TODO: add checks for columns of min/max index too. What if idx0 is not primary
          sym.update(e)
      }
      }
      unit()

    case StoreUpdate(store, e) => indexMap.collect { case ((`store`, idx), sym) => sym.update(e) }; unit()
    case StoreDeleteCopyDependent(store, e) => val ref = indexMap((store, 0)).get(e); indexMap.collect { case ((`store`, idx), sym) => sym.deleteCopyDependent(ref) }; unit()
    case StoreDeleteCopy(store, e) => indexMap.toSeq.sortWith(_._1._2 > _._1._2).collect { case ((`store`, idx), sym) => sym.deleteCopy(e, indexMap((store, 0))) }; unit()
    case StoreDelete1(store, e) => indexMap.collect { case ((`store`, idx), sym) => sym.delete(e) }; unit()
  }

}
