package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 21/3/17.
  */
class StringFormatEvaluator(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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
  rewrite += rule {
    case StringExtraStringPrintfObject(size, Constant("%d %d %d %d %d $%f %s | %s"), Def(LiftedSeq(args))) =>
      val s1 = StringExtra.StringNew(size)
      StringExtra.StringAppend(s1, args(0))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, args(1))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, args(2))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, args(3))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, args(4))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, unit('$'))
      StringExtra.StringAppend(s1, args(5))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, args(6))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppend(s1, unit('|'))
      StringExtra.StringAppend(s1, unit(' '))
      StringExtra.StringAppendN(s1, args(7), unit(500))
      if (!Optimizer.cTransformer)
        __ifThenElse(s1.length > size, s1.substring(unit(0), size), infix_toString(s1))
      else
        s1
    case StringExtraStringPrintfObject(size, Constant("%.10s    %.10s"), Def(LiftedSeq(args))) =>
      val s1 = StringExtra.StringNew(size)
      StringExtra.StringAppendN(s1, args(0), unit(10))
      StringExtra.StringAppendN(s1, unit("    "), unit(4))
      StringExtra.StringAppendN(s1, args(1), unit(10))
      if (!Optimizer.cTransformer)
        __ifThenElse(s1.length > size, s1.substring(unit(0), size), infix_toString(s1))
      else
        s1

  }

}
