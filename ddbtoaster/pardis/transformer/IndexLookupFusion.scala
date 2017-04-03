package ddbt.transformer

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.types.RecordType
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 17.05.16.
  */
class IndexLookupFusion(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR._

  val storeGets = collection.mutable.ArrayBuffer[Rep[_]]()

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

  if (Optimizer.indexLookupFusion) {
    // full optimization
    analysis += statement {
      case sym -> (s: StoreGetCopy[_]) => storeGets += sym; ()
      case sym -> StoreSliceCopy(_, _, _, Def(PardisLambda(_, i, _))) => storeGets += i; ()
      case sym -> StoreForeachCopy(_, Def(PardisLambda(_, i, _))) => storeGets += i; ()
      case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) if storeGets.contains(rhs) => storeGets += lhs; ()
      case sym -> (PardisAssign(PardisVar(lhs), rhs@Sym(_, _))) => storeGets -= lhs; ()
      case sym -> (PardisReadVar(PardisVar(v@Sym(_, _)))) if storeGets contains v => storeGets += sym; ()
     //FIXME: SBJ: Trusting array buffer blindly. The entry from ArrayBuffer is from store , only if all elements appended to ArrayBuffer are from store.
      // Doing this requires inference logic similar to that of type inference in EntryAnalysis. Additionally, it also requires an "and" logic since all elements have to be from store
        // This might be better implemented as the dual problem, checking if any one of them DOES NOT come from store.
      case sym -> (ab@ArrayBufferApply(self, _)) if (ab.typeA == GenericEntryType  || ab.typeA.isInstanceOf[RecordType[SEntry]]) => storeGets += sym ; ()
      case sym -> PardisIfThenElse(_, t, e)  if (t.typeT == GenericEntryType  || t.typeT.isInstanceOf[RecordType[SEntry]]) =>
        if(storeGets.contains(t.res) && storeGets.contains(e.res))
          storeGets += sym ;()
      case sym -> AggregatorResult(_) => storeGets += sym; ()
    }
    rewrite += rule {
      case StoreGetCopy(store, idx, key) => val rep = storeGet(store, idx, key)(key.tp); storeGets += rep.asInstanceOf[Sym[_]]; rep
      case StoreSliceCopy(store, idx, key, f) => store.slice(idx, key, f)
        //SBJ : Two stage change to allow two rounds of analysis. Without this, the entries inside a nested block (eg. If then else) are not detected
      case StoreForeachCopy(store, f) => store.foreach(f)
      case StoreUpdateCopy(store, e) if storeGets contains e => store.update(e)
      case StoreUpdateCopyDependent(store, e) if storeGets contains e => store.update(e)
      case StoreUpdateCopy(store, e) =>  store.updateCopyDependent(e)
      case StoreDeleteCopy(store, e) if storeGets contains e => store.delete(e)
      case StoreDeleteCopyDependent(store, e) if storeGets contains e => store.delete(e)
      case StoreDeleteCopy(store, e) => store.deleteCopyDependent(e)
    }
  } else {
    //partial optimization
    rewrite += rule {
      case StoreGetCopy(store, idx, key) => storeGetCopyDependent(store, idx, key)(key.tp)
      case StoreSliceCopy(store, idx, key, f) => store.sliceCopyDependent(idx, key, f)
      case StoreUpdateCopy(store, e) => store.updateCopyDependent(e)
      case StoreDeleteCopy(store, e) => store.deleteCopyDependent(e)
    }
  }
}