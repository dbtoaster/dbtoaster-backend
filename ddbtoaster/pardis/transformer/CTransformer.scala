package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.CTypes
import ch.epfl.data.sc.pardis.optimization.TopDownTransformerTraverser
import ddbt.lib.store.deep.StoreDSL

trait CTransformer extends TopDownTransformerTraverser[StoreDSL] {
  val IR: StoreDSL

  import IR._
  import ch.epfl.data.sc.pardis.ir.CNodes._

  implicit class PointerTypeOps[T](tp: TypeRep[T]) {
    def isPointerType: Boolean = tp match {
      case x: CTypes.PointerType[_] => true
      case _                        => false
    }
  }

  override def transformExp[T: TypeRep, S: TypeRep](exp: Rep[T]): Rep[S] = exp match {
    case t: typeOf[_] => typeOf()(apply(t.tp)).asInstanceOf[Rep[S]]
    case _            => super.transformExp[T, S](exp)
  }
}