package ddbt.transformer

import ch.epfl.data.sc.pardis.optimization.{RuleBasedTransformer, RecursiveRuleBasedTransformer}
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 17.05.16.
  */
class IndexLookupFusion(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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

  val storeGets = collection.mutable.ArrayBuffer[Rep[_]]()

  if (Optimizer.indexLookupFusion) {
    // full optimization
    analysis += statement {
      case sym -> (s: StoreGetCopy[_]) => storeGets += sym; ()
        //SBJ: TODO: Add lambdas from slice/for each
        //SBJ: TODO: Handle assignment of ref obtained from get/slice/foreach to another ref
    }
    rewrite += rule {
      case StoreGetCopy(store, idx, key, _) => store.get(idx, key)
      case StoreUpdateCopy(store, e)  => store.update(e) //SBJ: hack for now
      case StoreUpdateCopy(store, e) if storeGets contains e => store.update(e)
	  case StoreUpdateCopy(store, e) => store.updateCopyDependent(e)
      case StoreDeleteCopy(store, e)  => store.delete(e) //SBJ: hack for now
      case StoreDeleteCopy(store, e) if storeGets contains e => store.delete(e)
	  case StoreDeleteCopy(store, e) => store.deleteCopyDependent(e)
    }
  } else {
    //partial optimization
    rewrite += rule {
      case StoreGetCopy(store, idx, key, _) => store.getCopyDependent(idx, key)
      case StoreUpdateCopy(store, e) => store.updateCopyDependent(e)
      case StoreDeleteCopy(store, e) => store.deleteCopyDependent(e)
    }
  }
}