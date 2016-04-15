/* Generated by Purgatory 2014-2016 */

package ddbt.lib.store.deep

import ch.epfl.data.sc.pardis
import pardis.ir._
import pardis.types.PardisTypeImplicits._
import pardis.effects._
import pardis.deep._
import pardis.deep.scalalib._
import pardis.deep.scalalib.collection._
import pardis.deep.scalalib.io._

trait MirrorAggregatorOps extends Base  {  
  // Type representation
  val MirrorAggregatorType = MirrorAggregatorIRs.MirrorAggregatorType
  type MirrorAggregatorType[E <: ddbt.lib.store.Entry] = MirrorAggregatorIRs.MirrorAggregatorType[E]
  implicit def typeMirrorAggregator[E <: ddbt.lib.store.Entry: TypeRep]: TypeRep[MirrorAggregator[E]] = MirrorAggregatorType(implicitly[TypeRep[E]])
  implicit class MirrorAggregatorRep[E <: ddbt.lib.store.Entry](self : Rep[MirrorAggregator[E]])(implicit typeE : TypeRep[E]) {
     def apply(e : Rep[E]) : Rep[Unit] = mirrorAggregatorApply[E](self, e)(typeE)
     def result : Rep[E] = mirrorAggregatorResult[E](self)(typeE)
     def compose[A](g : Rep[(A => E)])(implicit typeA : TypeRep[A]) : Rep[(A => Unit)] = mirrorAggregatorCompose[E, A](self, g)(typeE, typeA)
     def andThen[A](g : Rep[(Unit => A)])(implicit typeA : TypeRep[A]) : Rep[(E => A)] = mirrorAggregatorAndThen[E, A](self, g)(typeE, typeA)
  }
  object MirrorAggregator {
     def min[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit typeE : TypeRep[E], typeR : TypeRep[R], order : Ordering[R]) : Rep[MirrorAggregator[E]] = mirrorAggregatorMinObject[E, R](f)(typeE, typeR, order)
     def max[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit typeE : TypeRep[E], typeR : TypeRep[R], order : Ordering[R]) : Rep[MirrorAggregator[E]] = mirrorAggregatorMaxObject[E, R](f)(typeE, typeR, order)
  }
  // constructors

  // IR defs
  val MirrorAggregatorApply = MirrorAggregatorIRs.MirrorAggregatorApply
  type MirrorAggregatorApply[E <: ddbt.lib.store.Entry] = MirrorAggregatorIRs.MirrorAggregatorApply[E]
  val MirrorAggregatorResult = MirrorAggregatorIRs.MirrorAggregatorResult
  type MirrorAggregatorResult[E <: ddbt.lib.store.Entry] = MirrorAggregatorIRs.MirrorAggregatorResult[E]
  val MirrorAggregatorCompose = MirrorAggregatorIRs.MirrorAggregatorCompose
  type MirrorAggregatorCompose[E <: ddbt.lib.store.Entry, A] = MirrorAggregatorIRs.MirrorAggregatorCompose[E, A]
  val MirrorAggregatorAndThen = MirrorAggregatorIRs.MirrorAggregatorAndThen
  type MirrorAggregatorAndThen[E <: ddbt.lib.store.Entry, A] = MirrorAggregatorIRs.MirrorAggregatorAndThen[E, A]
  val MirrorAggregatorMinObject = MirrorAggregatorIRs.MirrorAggregatorMinObject
  type MirrorAggregatorMinObject[E <: ddbt.lib.store.Entry, R] = MirrorAggregatorIRs.MirrorAggregatorMinObject[E, R]
  val MirrorAggregatorMaxObject = MirrorAggregatorIRs.MirrorAggregatorMaxObject
  type MirrorAggregatorMaxObject[E <: ddbt.lib.store.Entry, R] = MirrorAggregatorIRs.MirrorAggregatorMaxObject[E, R]
  // method definitions
   def mirrorAggregatorApply[E <: ddbt.lib.store.Entry](self : Rep[MirrorAggregator[E]], e : Rep[E])(implicit typeE : TypeRep[E]) : Rep[Unit] = MirrorAggregatorApply[E](self, e)
   def mirrorAggregatorResult[E <: ddbt.lib.store.Entry](self : Rep[MirrorAggregator[E]])(implicit typeE : TypeRep[E]) : Rep[E] = MirrorAggregatorResult[E](self)
   def mirrorAggregatorCompose[E <: ddbt.lib.store.Entry, A](self : Rep[MirrorAggregator[E]], g : Rep[((A) => E)])(implicit typeE : TypeRep[E], typeA : TypeRep[A]) : Rep[(A => Unit)] = MirrorAggregatorCompose[E, A](self, g)
   def mirrorAggregatorAndThen[E <: ddbt.lib.store.Entry, A](self : Rep[MirrorAggregator[E]], g : Rep[((Unit) => A)])(implicit typeE : TypeRep[E], typeA : TypeRep[A]) : Rep[(E => A)] = MirrorAggregatorAndThen[E, A](self, g)
   def mirrorAggregatorMinObject[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit typeE : TypeRep[E], typeR : TypeRep[R], order : Ordering[R]) : Rep[MirrorAggregator[E]] = MirrorAggregatorMinObject[E, R](f)
   def mirrorAggregatorMaxObject[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit typeE : TypeRep[E], typeR : TypeRep[R], order : Ordering[R]) : Rep[MirrorAggregator[E]] = MirrorAggregatorMaxObject[E, R](f)
  type MirrorAggregator[E <: ddbt.lib.store.Entry] = ddbt.lib.store.MirrorAggregator[E]
}
object MirrorAggregatorIRs extends Base {
  // Type representation
  case class MirrorAggregatorType[E <: ddbt.lib.store.Entry](typeE: TypeRep[E]) extends TypeRep[MirrorAggregator[E]] {
    def rebuild(newArguments: TypeRep[_]*): TypeRep[_] = MirrorAggregatorType(newArguments(0).asInstanceOf[TypeRep[_ <: ddbt.lib.store.Entry]])
    val name = s"MirrorAggregator[${typeE.name}]"
    val typeArguments = List(typeE)
  }
      implicit def typeMirrorAggregator[E <: ddbt.lib.store.Entry: TypeRep]: TypeRep[MirrorAggregator[E]] = MirrorAggregatorType(implicitly[TypeRep[E]])
  // case classes
  case class MirrorAggregatorApply[E <: ddbt.lib.store.Entry](self : Rep[MirrorAggregator[E]], e : Rep[E])(implicit val typeE : TypeRep[E]) extends FunctionDef[Unit](Some(self), "apply", List(List(e))){
    override def curriedConstructor = (copy[E] _).curried
  }

  case class MirrorAggregatorResult[E <: ddbt.lib.store.Entry](self : Rep[MirrorAggregator[E]])(implicit val typeE : TypeRep[E]) extends FunctionDef[E](Some(self), "result", List()){
    override def curriedConstructor = (copy[E] _)
  }

  case class MirrorAggregatorCompose[E <: ddbt.lib.store.Entry, A](self : Rep[MirrorAggregator[E]], g : Rep[((A) => E)])(implicit val typeE : TypeRep[E], val typeA : TypeRep[A]) extends FunctionDef[(A => Unit)](Some(self), "compose", List(List(g))){
    override def curriedConstructor = (copy[E, A] _).curried
  }

  case class MirrorAggregatorAndThen[E <: ddbt.lib.store.Entry, A](self : Rep[MirrorAggregator[E]], g : Rep[((Unit) => A)])(implicit val typeE : TypeRep[E], val typeA : TypeRep[A]) extends FunctionDef[(E => A)](Some(self), "andThen", List(List(g))){
    override def curriedConstructor = (copy[E, A] _).curried
  }

  case class MirrorAggregatorMinObject[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit val typeE : TypeRep[E], val typeR : TypeRep[R], val order : Ordering[R]) extends FunctionDef[MirrorAggregator[E]](None, "MirrorAggregator.min", List(List(f))){
    override def curriedConstructor = (copy[E, R] _)
    override def isPure = true

    override def partiallyEvaluate(children: Any*): MirrorAggregator[E] = {
      val f = children(0).asInstanceOf[(E => R)]
      ddbt.lib.store.MirrorAggregator.min[E, R](f)
    }
    override def partiallyEvaluable: Boolean = true

  }

  case class MirrorAggregatorMaxObject[E <: ddbt.lib.store.Entry, R](f : Rep[(E => R)])(implicit val typeE : TypeRep[E], val typeR : TypeRep[R], val order : Ordering[R]) extends FunctionDef[MirrorAggregator[E]](None, "MirrorAggregator.max", List(List(f))){
    override def curriedConstructor = (copy[E, R] _)
    override def isPure = true

    override def partiallyEvaluate(children: Any*): MirrorAggregator[E] = {
      val f = children(0).asInstanceOf[(E => R)]
      ddbt.lib.store.MirrorAggregator.max[E, R](f)
    }
    override def partiallyEvaluable: Boolean = true

  }

  type MirrorAggregator[E <: ddbt.lib.store.Entry] = ddbt.lib.store.MirrorAggregator[E]
}
trait MirrorAggregatorImplicits extends MirrorAggregatorOps { 
  // Add implicit conversions here!
}
trait MirrorAggregatorComponent extends MirrorAggregatorOps with MirrorAggregatorImplicits {  }

trait MirrorAggregatorPartialEvaluation extends MirrorAggregatorComponent with BasePartialEvaluation {  
  // Immutable field inlining 

  // Mutable field inlining 
  // Pure function partial evaluation
}

