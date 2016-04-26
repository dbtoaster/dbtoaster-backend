package lifter

import ch.epfl.data.sc.pardis.deep.scalalib.{BooleanPartialEvaluation, BooleanComponent}
import ddbt.lib.store.deep.BooleanExtraComponent
import ddbt.lib.store.deep.BooleanExtraIRs.{BooleanExtraConditionalObject => Conditional}
import ch.epfl.data.sc.pardis.ir.{Constant, IfThenElseOptimization, ObjectOpsOptimization}

/**
  * Created by sachin on 22.04.16.
  */
trait OnlineOptimizations extends ObjectOpsOptimization with IfThenElseOptimization with SCLMSInterop with BooleanPartialEvaluation with BooleanExtraComponent{
  override def booleanExtraConditionalObject[T](cond : Rep[Boolean], ift : Rep[T], iff : Rep[T])(implicit typeT : TypeRep[T]) : Rep[T] = {
    cond match{
      case Constant(flag) => if(flag) ift else iff
      case _ => super.booleanExtraConditionalObject(cond, ift, iff)
    }
  }
  override def numeric_times[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[T] = {
    runtimeType[T] match {
      case LongType => {
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Long]]

        (l,r) match{
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(1L), y) => y
          case (Constant(0L), y) => unit(0L)
          case (x, Constant(1L)) => x
          case (x, Constant(0L)) => unit(0L)
          case (x, Def(Conditional(c,t,Constant(0L)))) => __ifThenElse(c,numeric_times(x,t),unit(0L))
          case (x, Def(Conditional(c,Constant(0L),f))) => __ifThenElse(c,unit(0L),numeric_times(x,f))
          case (Def(Conditional(c,t,Constant(0L))), y) => __ifThenElse(c,numeric_times(t,y),unit(0L))
          case (Def(Conditional(c,Constant(0L),f)), y) => __ifThenElse(c,unit(0L),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1L))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1L),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x, Def(Conditional(c,t,Constant(1L)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1L),f)))  => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }
      }
      case _ => super.numeric_times(lhs,rhs)
    }
  }.asInstanceOf[Rep[T]]

  override def ordering_gt[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[Boolean] = {
    runtimeType[T] match {
      case LongType => {
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Long]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x > y)
          case _ => super.ordering_gt(lhs, rhs)
        }
      }
      case _ => super.ordering_gt(lhs, rhs)
    }
  }

  override def ordering_gteq[T: TypeRep](lhs: Rep[T], rhs: Rep[T]): Rep[Boolean] = {
    runtimeType[T] match {
      case LongType => {
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Long]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x >= y)
          case _ => super.ordering_gteq(lhs, rhs)
        }
      }
      case _ => super.ordering_gteq(lhs, rhs)
    }
  }
}
