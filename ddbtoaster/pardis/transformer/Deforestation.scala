package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.{PardisLambda, PardisLambda2}
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.types.{PardisType, UnitType}
import ddbt.lib.store.deep.StoreDSL
import ddbt.lib.store.Entry

/**
  * Created by sachin on 02.05.16.
  */

abstract class Collector[T <: Entry](implicit val IR: StoreDSL, implicit val typeT : PardisType[T]) { self =>
  import IR._
  def apply(f: Rep[T] => Rep[Unit]) : Rep[Unit]
  def map[U <: Entry : TypeRep](g: Rep[T] => Rep[U]) = new Collector[U] {
    override def apply(f: Rep[U] => Rep[Unit]) = self.apply(g andThen f)
  }
  def filter(p : Rep[T] => Rep[Boolean]) = new Collector[T] {
    override def apply(f: (Rep[T]) => Rep[Unit]) = self.apply((x:Rep[T]) => __ifThenElse(p(x), f(x), unit())(UnitType))
  }
}

class Deforestation(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR.{EntryType => _, typeNull => _, _}

  def toCollector[T <: Entry](n : Rep[Store[T]])(implicit typeT: PardisType[T]) : Collector[T] = n match {
    case Def(sf@StoreFilter(self, Def(PardisLambda(f, _ ,_)))) => toCollector(self)(sf.typeE).filter(f)
    case Def(sm@StoreMap(self, Def(PardisLambda(f, _, _)))) => toCollector(self)(sm.typeE).map(f)
    case Def(st@StoreNew2()) => new Collector{
      override def apply(f: (Rep[T]) => Rep[Unit]) = n.foreachCopy(doLambda(f)(typeT, UnitType))
    }
  }
  rewrite += rule {
      case sf@StoreForeachCopy(self, Def(PardisLambda(f, _, _))) => toCollector(self)(sf.typeE).apply(f)
      case sf@StoreFold(self, zero, Def(PardisLambda2(f, _, _, _))) =>
        val res = __newVar(zero)(sf.typeU)
        toCollector(self)(sf.typeE).apply({
          x: Rep[Entry] => __assign(res, f(__readVar(res)(sf.typeU), x))(sf.typeU)
        })
      __readVar(res)(sf.typeU)
  }

}