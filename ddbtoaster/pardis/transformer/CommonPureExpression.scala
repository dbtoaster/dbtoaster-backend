package ddbt.transformer

import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ddbt.lib.store.deep._
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.types.UnitType
import ddbt.codegen.Optimizer

class CommonPureExpression(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  override def optimize[T](node: IR.Block[T])(implicit evidence$1: IR.TypeRep[T]): IR.Block[T] = {
    val b = super.optimize(node)
    counts.filter(_._2 != 2).map( t => t._1 -> (t._2/2)).foreach(System.err.println)
    counts.clear()
    b
  }

  //TODO: Reset after each block. Otherwise global vars are captured
  val counts = collection.mutable.HashMap[Def[_], Int]()
  analysis += rule {
    case s if s.isPure && !s.isInstanceOf[PardisLambdaDef] =>
      val old = counts.getOrElse(s, 0)
//      System.err.println(s"$old    $s")
      counts += (s -> (old + 1))
      ()
  }

}
