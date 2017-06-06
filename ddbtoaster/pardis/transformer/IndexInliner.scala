package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.codegen.Optimizer

import ddbt.lib.store.deep.{StoreDSL, StructFieldDecr, StructFieldIncr}

import scala.collection.mutable

/**
  * Created by sachin on 02.05.16.
  */
class IndexInliner(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR.{EntryType => _, _}

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

  analysis += statement {
    case sym -> (StoreIndex(st, Constant(idx), Constant(idxType), _, _)) if idxType != "INone" => indexMap += (st, idx) -> sym.asInstanceOf[Rep[Idx[Entry]]]; ()
  }
  if (Optimizer.deadIndexUpdate)
  //SBJ: TODO:  Add check to ensure entry comes from a get or slice

    rewrite += rule {
      case StoreGetCopy(store, Constant(idx), e) => idxGetCopy(indexMap((store, idx)), e)(e.tp)
      case StoreGet(store, Constant(idx), e) => idxGet(indexMap((store, idx)), e)(e.tp)
      case StoreGetCopyDependent(store, Constant(idx), e) => idxGetCopyDependent(indexMap((store, idx)), e)(e.tp)
      case StoreForeach(store, f) => {
        implicit val entTp = store.tp.typeArguments(0).asInstanceOf[TypeRep[Entry]]
        indexMap((store, 0)).foreach(f)
      }
      case StoreForeachCopy(store, f) => {
        implicit val entTp = store.tp.typeArguments(0).asInstanceOf[TypeRep[Entry]]
        indexMap((store, 0)).foreachCopy(f)
      }
      case StoreSliceCopy(store, Constant(idx), e, f) =>
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        indexMap((store, idx)).sliceCopy(e, f)
      case StoreSliceCopyDependent(store, Constant(idx), e, f) =>
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        indexMap((store, idx)).sliceCopyDependent(e, f)
      case StoreSlice(store, Constant(idx), e, f) =>
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        indexMap((store, idx)).slice(e, f)
      case StoreUpdateCopyDependent(store, e) => {
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        val ref = indexMap((store, 0)).get(e)
        val e2 = if (Optimizer.cTransformer) store.copyIntoPool(e) else e
        indexMap.collect { case ((`store`, idx), sym) => sym.updateCopyDependent(e2, ref) }
        unit()
      }
      case StoreUpdateCopy(store, e) =>
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        val e2 = if (Optimizer.cTransformer) store.copyIntoPool(e) else e
        indexMap.toSeq.sortWith(_._1._2 > _._1._2).collect { case ((`store`, idx), sym) => sym.updateCopy(e2, indexMap((store, 0))) }
        unit()

      case StoreUpdate(store, e) =>
        implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
        indexMap.collect { case ((`store`, idx), sym) => sym.update(e) };
        unit()

      //SBJ : Cannot inline delete for CPP.
      //    case StoreDeleteCopyDependent(store, e) => val ref = indexMap((store, 0)).get(e); indexMap.collect { case ((`store`, idx), sym) => sym.deleteCopyDependent(ref) }; unit()
      //    case StoreDeleteCopy(store, e) => indexMap.toSeq.sortWith(_._1._2 > _._1._2).collect { case ((`store`, idx), sym) => sym.deleteCopy(e, indexMap((store, 0))) }; unit()
      //    case StoreDelete1(store, e) => indexMap.collect { case ((`store`, idx), sym) => sym.delete(e) }; unit()
    }

}
