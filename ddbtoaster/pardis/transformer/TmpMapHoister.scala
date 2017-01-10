package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.{PardisStruct, PardisStructArg}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 21/12/16.
  */
class TmpMapHoister(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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

  val tmpArrays = collection.mutable.HashSet[Sym[_]]()
  val tmpMaps = collection.mutable.HashMap[Sym[_], collection.mutable.ArrayBuffer[Sym[_]]]()
  var globalMaps: List[Sym[_]] = null
  analysis += statement {
    case sym -> (StoreNew3(_, ops: Sym[_])) if !globalMaps.contains(sym) => tmpMaps += (sym -> collection.mutable.ArrayBuffer[Sym[_]]()); tmpArrays += ops; ()
    case sym -> (i@StoreIndex(self: Sym[_], _, _, _, _)) if tmpMaps.contains(self) => tmpMaps(self) += sym; ()
  }
  rewrite += statement {
    case sym -> (s: StoreNew3[_]) if tmpMaps.contains(sym) => storeClear(sym.asInstanceOf[Rep[Store[ddbt.lib.store.Entry]]])(s.typeE.asInstanceOf[TypeRep[ddbt.lib.store.Entry]]); sym
    case sym -> (StoreIndex(self: Sym[_], _, _, _, _)) if tmpMaps.contains(self) => sym
    case sym -> (ArrayApplyObject(Def(LiftedSeq(ei)))) if tmpArrays contains (sym) => ei.foreach(e => tmpArrays += e.asInstanceOf[Sym[_]]); sym
    case sym -> rhs if tmpArrays contains (sym) =>  sym
  }


}
