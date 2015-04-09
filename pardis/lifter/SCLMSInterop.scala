package lifter

import ch.epfl.data.sc.pardis
import pardis.deep.scalalib.{IntComponent, LongComponent, DoubleComponent}
import pardis.ir._

/**
 * Created by khayyam on 4/9/15.
 */
trait SCLMSInterop extends Base with IntComponent with LongComponent with DoubleComponent {
  def var_plusequals[T/*: Numeric*/ : TypeRep](lhs: Var[T], rhs: Rep[T]): Rep[Unit] = {
    __assign(lhs, numeric_plus(__readVar(lhs), rhs))
  }

  def numeric_plus[T/*: Numeric*/ : TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[T] = {
      runtimeType[T] match {
        case IntType => lhs.asInstanceOf[Rep[Int]] + rhs.asInstanceOf[Rep[Int]]
        case LongType => lhs.asInstanceOf[Rep[Long]] + rhs.asInstanceOf[Rep[Long]]
        case DoubleType => lhs.asInstanceOf[Rep[Double]] + rhs.asInstanceOf[Rep[Double]]
      }
  }.asInstanceOf[Rep[T]]

  def numeric_times[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[T] = {
    runtimeType[T] match {
      case IntType => lhs.asInstanceOf[Rep[Int]] * rhs.asInstanceOf[Rep[Int]]
      case LongType => lhs.asInstanceOf[Rep[Long]] * rhs.asInstanceOf[Rep[Long]]
      case DoubleType => lhs.asInstanceOf[Rep[Double]] * rhs.asInstanceOf[Rep[Double]]
    }
  }.asInstanceOf[Rep[T]]

  def ordering_gt[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[Boolean] = {
    runtimeType[T] match {
      case IntType => lhs.asInstanceOf[Rep[Int]] > rhs.asInstanceOf[Rep[Int]]
      case LongType => lhs.asInstanceOf[Rep[Long]] > rhs.asInstanceOf[Rep[Long]]
      case DoubleType => lhs.asInstanceOf[Rep[Double]] > rhs.asInstanceOf[Rep[Double]]
    }
  }

  def ordering_gteq[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[Boolean] = {
    runtimeType[T] match {
      case IntType => lhs.asInstanceOf[Rep[Int]] >= rhs.asInstanceOf[Rep[Int]]
      case LongType => lhs.asInstanceOf[Rep[Long]] >= rhs.asInstanceOf[Rep[Long]]
      case DoubleType => lhs.asInstanceOf[Rep[Double]] >= rhs.asInstanceOf[Rep[Double]]
    }
  }
}
