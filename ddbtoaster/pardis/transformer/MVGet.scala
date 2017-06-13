package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.PardisVar
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.StoreDSL

class MVGet(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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

  val upds = collection.mutable.HashSet[Sym[_]]()
  val alreadyTransformed = collection.mutable.HashSet[Sym[_]]()
  analysis += statement {
    case sym -> (IdxUpdate(_, e: Sym[_])) => upds += e; ()
    case sym -> (Assign(_, rhs: Sym[_])) if upds.contains(sym) => upds += rhs; ()
    case sym -> (IfThenElse(_, thenp, elsep)) if upds.contains(sym) => upds += (thenp.res.asInstanceOf[Sym[_]], elsep.res.asInstanceOf[Sym[_]]); ()
    case sym -> (StoreDelete1(_, e: Sym[_])) => upds += e; ()
  }
  rewrite += statement {
    case sym -> (IdxGet(idx, e)) if upds.contains(sym) && !alreadyTransformed.contains(sym) =>
      implicit val entTp = e.tp.asInstanceOf[TypeRep[Entry]]
      val news = idx.getForUpdate(e)
      alreadyTransformed += news.asInstanceOf[Sym[_]]
      news

    case sym -> (n@AggregatorResult(agg)) if upds.contains(sym) && !alreadyTransformed.contains(sym) =>
      implicit val entTp = n.typeE
      val news : Rep[_] = toAtom(AggregatorResultForUpdate(agg))
      alreadyTransformed += news.asInstanceOf[Sym[_]]
      news
  }
}
