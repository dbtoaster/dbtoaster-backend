package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.types.UnitType
import ddbt.lib.store.deep.StoreDSL

/**
  * Converts core constructs of Scala into C.
  *
  * For example a block in Scala can have an arbitrary return type whereas in C
  * it should have a void (Unit) type. The following program:
  * {{{
  *     val x: Foo = if(cond) y else z
  * }}}
  * is converted into:
  * {{{
  *     Foo x;
  *     if(cond) {
  *       x = y;
  *     } else {
  *       x = z;
  *     }
  * }}}
  *
  * @param IR the polymorphic embedding trait which contains the reified program.
  * @param ifAgg specifies whether aggressive if rewriting optimization should be applied or not
  */
class ScalaConstructsToCTranformer(override val IR: StoreDSL, val ifAgg: Boolean) extends RecursiveRuleBasedTransformer[StoreDSL](IR) with CTransformer {
  import IR._
  import ch.epfl.data.sc.pardis.ir.CNodes._
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

  def blockIsPure[T](block: Block[T]): Boolean = {
    for (stm <- block.stmts) {
      val isPure = stm.rhs match {
        case b @ Block(_, _) => blockIsPure(b)
        case d               => d.isPure
      }
      if (!isPure)
        return false
    }
    true
  }

  def isNullCheck[T](exp: Rep[T]): Boolean = exp match {
    case Def(NotEqual(_, Constant(null))) => true
    case Def(Equal(_, Constant(null)))    => true
    case _                                => false
  }

  rewrite += rule {

    case IfThenElse(cond, thenp, elsep) if thenp.tp != UnitType =>
      val res = __newVarNamed[Int](unit(0), "ite")(thenp.tp.asInstanceOf[TypeRep[Int]])
      __ifThenElse(cond, {
        __assign(res, inlineBlock(thenp)(thenp.tp))(thenp.tp)
      }, {
        __assign(res, inlineBlock(elsep)(elsep.tp))(elsep.tp)
      })(UnitType)
      val t= res.tp
      ReadVar(res)(res.tp)
  }

  rewrite += rule {
    case and @ Boolean$bar$bar(case1, b) if ifAgg && blockIsPure(b) && !isNullCheck(case1) => {
      val resB = inlineBlock[Boolean](b)
      // NameAlias[Boolean](Some(case1), " or ", List(List(resB)))
      case1 | resB
    }
  }

  rewrite += rule {
    case and @ Boolean$amp$amp(case1, b) if ifAgg && blockIsPure(b) && !isNullCheck(case1) => {
      val resB = inlineBlock[Boolean](b)
      // NameAlias[Boolean](Some(case1), " and ", List(List(resB)))
      case1 & resB
    }
  }

  rewrite += rule {
    case or @ Boolean$bar$bar(case1, b) => {
      __ifThenElse(case1, unit(true), b)
    }
  }

  rewrite += rule {
    case and @ Boolean$amp$amp(case1, b) => {
      __ifThenElse(case1, b, unit(false))
    }
  }
  // rewrite += rule {
  //   case and @ Boolean$amp$amp(case1, b) if b.stmts.forall(stm => stm.rhs.isPure) && b.stmts.nonEmpty => {
  //     val rb = inlineBlock(b)
  //     case1 && rb
  //   }
  // }
  // rewrite += rule {
  //   case and @ Boolean$amp$amp(case1, b) if b.stmts.nonEmpty => {
  //     __ifThenElse(case1, b, unit(false))
  //   }
  // }
  rewrite += rule { case IntUnary_$minus(self) => unit(-1) * self }
  rewrite += rule { case IntToLong(x) => x }
  rewrite += rule { case ByteToInt(x) => x }
  rewrite += rule { case IntToDouble(x) => x }
  rewrite += rule { case DoubleToInt(x) => infix_asInstanceOf[Double](x) }
  rewrite += rule { case BooleanUnary_$bang(b) => NameAlias[Boolean](None, "!", List(List(b))) }
}