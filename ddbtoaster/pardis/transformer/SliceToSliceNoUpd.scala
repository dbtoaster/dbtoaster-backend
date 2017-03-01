package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisLambda, Statement}
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL


class SliceToSliceNoUpd(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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

  val noUpdSlices = collection.mutable.HashSet[Sym[_]]()
  analysis += statement {
    case sym -> IdxSlice(self, _, Def(PardisLambda(_, _, o))) =>
      var noUpdate = true
      o.stmts.collect({
        case Statement(s, IdxUpdate(_, _)) => noUpdate = false
      })
      if (noUpdate)
        noUpdSlices += sym
      ()
    case sym -> IdxSlice(self, _, f) => //other cases such as Aggregators are assumed to be read-only
      noUpdSlices += sym
      ()
  }

  rewrite += statement {
    case sym -> IdxSlice(self, key, f) if noUpdSlices.contains(sym) =>
      implicit val entTp = key.tp.asInstanceOf[TypeRep[Entry]]
      self.sliceNoUpdate(key, f)
  }

}