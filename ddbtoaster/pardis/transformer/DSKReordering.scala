package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.PardisLambda
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 02.05.16.
  */


class DSKReordering(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR.{EntryType => _, typeNull => _, _}

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

  rewrite += rule {
    case StoreFilter(Def(sm@StoreMap(self, mlrep@Def(ml@PardisLambda(mapfn, _, _)))), Def(fl@PardisLambda(filterfn, _ , _))) =>
      //SBJ: TODO: Check if correct typereps are passed
      val filterfn_ = mapfn andThen filterfn
      val fl_ = doLambda(filterfn_)(ml.typeT, fl.typeS)
      val sf = toAtom(StoreFilter(self, fl_)(sm.typeE))(self.tp)
      StoreMap(sf, mlrep)(sm.typeE, sm.typeU)


//    case StoreMap(Def(StoreMap(self, Def(i@PardisLambda(inner, _, _)))), Def(o@PardisLambda(outer, _, _))) =>
    //      //SBJ: TODO: Check if correct typereps are passed
    //      val f = inner andThen outer
    //      val l = doLambda(f)(i.typeT, o.typeS)
    //      StoreMap(self, l)(i.typeT.asInstanceOf[TypeRep[Entry]], o.typeS)
    //    //    case StoreMap(Def(StoreMap(self: Sym[_], inner: Rep[Entry => Entry])), outer: Rep[Entry => Entry]) =>
    //    //      implicit val Etp = GenericEntryType.asInstanceOf[TypeRep[Entry]]
    //    //      StoreMap(self, __lambda{ x: Rep[Entry] => {__app[Entry, Entry](outer).apply(__app[Entry, Entry](inner).apply(x))}})
  }
}