package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RuleBasedTransformer, RecursiveRuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL

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
  analysis += statement {
    case sym -> (StoreIndex(st, Constant(idx), _, _, _)) => indexMap += (st, idx) -> sym.asInstanceOf[Rep[Idx[Entry]]]; ()
  }
  rewrite += rule {
    case StoreGet(store, Constant(idx), e, _) => indexMap((store, idx)).get(e)
    case StoreForeach(store, f) => indexMap((store, 0)).foreach(f)
    case StoreSlice(store, Constant(idx), e, f) => indexMap((store, idx)).slice(e, f)

  }
}
