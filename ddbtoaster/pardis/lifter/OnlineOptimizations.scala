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
      case IntType if lhs.tp == IntType && rhs.tp == IntType =>
        val l = lhs.asInstanceOf[Rep[Int]]
        val r = rhs.asInstanceOf[Rep[Int]]
        implicit val tp = IntType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1),y) => intUnary_-(y)
          case (Constant(1), y) => y
          case (Constant(0), y) => unit(0)
          case (Def(Conditional(c,t,Constant(0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0))
          case (Def(Conditional(c,Constant(0),f)), y) => __ifThenElse(c,unit(0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x,Constant(-1)) => intUnary_-(x)
          case (x, Constant(1)) => x
          case (x, Constant(0)) => unit(0)
          case (x, Def(Conditional(c,t,Constant(0)))) => __ifThenElse(c,numeric_times(x,t),unit(0))
          case (x, Def(Conditional(c,Constant(0),f))) => __ifThenElse(c,unit(0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case LongType if lhs.tp == IntType && rhs.tp == LongType =>
        val l = lhs.asInstanceOf[Rep[Int]]
        val r = rhs.asInstanceOf[Rep[Long]] 
        implicit val tp = LongType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1),y) => longUnary_-(y)
          case (Constant(1), y) => y
          case (Constant(0), y) => unit(0L)
          case (Def(Conditional(c,t,Constant(0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0L))
          case (Def(Conditional(c,Constant(0),f)), y) => __ifThenElse(c,unit(0L),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          // case (x,Constant(-1L)) => longUnary_-(x)
          case (x, Constant(1L)) => x
          case (x, Constant(0L)) => unit(0L)
          case (x, Def(Conditional(c,t,Constant(0L)))) => __ifThenElse(c,numeric_times(x,t),unit(0L))
          case (x, Def(Conditional(c,Constant(0L),f))) => __ifThenElse(c,unit(0L),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1L)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1L),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case LongType if lhs.tp == LongType && rhs.tp == IntType =>
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Int]] 
        implicit val tp = LongType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          // case (Constant(-1L),y) => longUnary_-(y)
          case (Constant(1L), y) => y
          case (Constant(0L), y) => unit(0L)
          case (Def(Conditional(c,t,Constant(0L))), y) => __ifThenElse(c,numeric_times(t,y),unit(0L))
          case (Def(Conditional(c,Constant(0L),f)), y) => __ifThenElse(c,unit(0L),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1L))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1L),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x,Constant(-1)) => longUnary_-(x)
          case (x, Constant(1)) => x
          case (x, Constant(0)) => unit(0L)
          case (x, Def(Conditional(c,t,Constant(0)))) => __ifThenElse(c,numeric_times(x,t),unit(0L))
          case (x, Def(Conditional(c,Constant(0),f))) => __ifThenElse(c,unit(0L),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case LongType if lhs.tp == LongType && rhs.tp == LongType =>
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Long]]
        implicit val tp = LongType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1L),y) => longUnary_-(y)
          case (Constant(1L), y) => y
          case (Constant(0L), y) => unit(0L)
          case (Def(Conditional(c,t,Constant(0L))), y) => __ifThenElse(c,numeric_times(t,y),unit(0L))
          case (Def(Conditional(c,Constant(0L),f)), y) => __ifThenElse(c,unit(0L),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1L))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1L),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x, Constant(-1L)) => longUnary_-(x)
          case (x, Constant(1L)) => x
          case (x, Constant(0L)) => unit(0L)
          case (x, Def(Conditional(c,t,Constant(0L)))) => __ifThenElse(c,numeric_times(x,t),unit(0L))
          case (x, Def(Conditional(c,Constant(0L),f))) => __ifThenElse(c,unit(0L),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1L)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1L),f)))  => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case DoubleType if lhs.tp == IntType && rhs.tp == DoubleType =>
        val l = lhs.asInstanceOf[Rep[Int]]
        val r = rhs.asInstanceOf[Rep[Double]]
        implicit val tp = DoubleType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1),y) => doubleUnary_-(y)
          case (Constant(1), y) => y
          case (Constant(0), y) => unit(0.0)
          case (Def(Conditional(c,t,Constant(0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0.0))
          case (Def(Conditional(c,Constant(0),f)), y) => __ifThenElse(c,unit(0.0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          // case (x, Constant(-1.0)) => doubleUnary_-(x)
          case (x, Constant(1.0)) => x
          case (x, Constant(0.0)) => unit(0.0)
          case (x, Def(Conditional(c,t,Constant(0.0)))) => __ifThenElse(c,numeric_times(x,t),unit(0.0))
          case (x, Def(Conditional(c,Constant(0.0),f))) => __ifThenElse(c,unit(0.0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1.0)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1.0),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case DoubleType if lhs.tp == DoubleType && rhs.tp == IntType =>
        val l = lhs.asInstanceOf[Rep[Double]]
        val r = rhs.asInstanceOf[Rep[Int]]
        implicit val tp = DoubleType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          // case (Constant(-1.0),y) => doubleUnary_-(y)
          case (Constant(1.0), y) => y
          case (Constant(0.0), y) => unit(0.0)
          case (Def(Conditional(c,t,Constant(0.0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0.0))
          case (Def(Conditional(c,Constant(0.0),f)), y) => __ifThenElse(c,unit(0.0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1.0))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1.0),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x, Constant(-1)) => doubleUnary_-(x)
          case (x, Constant(1)) => x
          case (x, Constant(0)) => unit(0.0)
          case (x, Def(Conditional(c,t,Constant(0)))) => __ifThenElse(c,numeric_times(x,t),unit(0.0))
          case (x, Def(Conditional(c,Constant(0),f))) => __ifThenElse(c,unit(0.0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case DoubleType if lhs.tp == LongType && rhs.tp == DoubleType =>
        val l = lhs.asInstanceOf[Rep[Long]]
        val r = rhs.asInstanceOf[Rep[Double]]
        implicit val tp = DoubleType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1L),y) => doubleUnary_-(y)
          case (Constant(1L), y) => y
          case (Constant(0L), y) => unit(0.0)
          case (Def(Conditional(c,t,Constant(0L))), y) => __ifThenElse(c,numeric_times(t,y),unit(0.0))
          case (Def(Conditional(c,Constant(0L),f)), y) => __ifThenElse(c,unit(0.0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1L))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1L),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          // case (x, Constant(-1.0)) => doubleUnary_-(x)
          case (x, Constant(1.0)) => x
          case (x, Constant(0.0)) => unit(0.0)
          case (x, Def(Conditional(c,t,Constant(0.0)))) => __ifThenElse(c,numeric_times(x,t),unit(0.0))
          case (x, Def(Conditional(c,Constant(0.0),f))) => __ifThenElse(c,unit(0.0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1.0)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1.0),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case DoubleType if lhs.tp == DoubleType && rhs.tp == LongType =>
        val l = lhs.asInstanceOf[Rep[Double]]
        val r = rhs.asInstanceOf[Rep[Long]]
        implicit val tp = DoubleType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          // case (Constant(-1.0),y) => doubleUnary_-(y)
          case (Constant(1.0), y) => y
          case (Constant(0.0), y) => unit(0.0)
          case (Def(Conditional(c,t,Constant(0.0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0.0))
          case (Def(Conditional(c,Constant(0.0),f)), y) => __ifThenElse(c,unit(0.0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1.0))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1.0),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x, Constant(-1L)) => doubleUnary_-(x)
          case (x, Constant(1L)) => x
          case (x, Constant(0L)) => unit(0.0)
          case (x, Def(Conditional(c,t,Constant(0L)))) => __ifThenElse(c,numeric_times(x,t),unit(0.0))
          case (x, Def(Conditional(c,Constant(0L),f))) => __ifThenElse(c,unit(0.0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1L)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1L),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
        }

      case DoubleType if lhs.tp == DoubleType && rhs.tp == DoubleType =>
        val l = lhs.asInstanceOf[Rep[Double]]
        val r = rhs.asInstanceOf[Rep[Double]]
        implicit val tp = DoubleType.asInstanceOf[TypeRep[AnyVal]]

        (l,r) match {
          case (Constant(x), Constant(y)) => Constant(x*y)
          case (Constant(-1.0),y) => doubleUnary_-(y)
          case (Constant(1.0), y) => y
          case (Constant(0.0), y) => unit(0.0)
          case (Def(Conditional(c,t,Constant(0.0))), y) => __ifThenElse(c,numeric_times(t,y),unit(0.0))
          case (Def(Conditional(c,Constant(0.0),f)), y) => __ifThenElse(c,unit(0.0),numeric_times(f,y))
          case (Def(Conditional(c,t,Constant(1.0))), y) => __ifThenElse(c,numeric_times(t,y),y)
          case (Def(Conditional(c,Constant(1.0),f)), y) => __ifThenElse(c,y,numeric_times(f,y))
          case (x, Constant(-1.0)) => doubleUnary_-(x)
          case (x, Constant(1.0)) => x
          case (x, Constant(0.0)) => unit(0.0)
          case (x, Def(Conditional(c,t,Constant(0.0)))) => __ifThenElse(c,numeric_times(x,t),unit(0.0))
          case (x, Def(Conditional(c,Constant(0.0),f))) => __ifThenElse(c,unit(0.0),numeric_times(x,f))
          case (x, Def(Conditional(c,t,Constant(1.0)))) => __ifThenElse(c,numeric_times(x,t),x)
          case (x, Def(Conditional(c,Constant(1.0),f))) => __ifThenElse(c,x,numeric_times(x,f))
          case _ => super.numeric_times(lhs,rhs)
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
