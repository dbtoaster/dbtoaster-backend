package ddbt.codegen.pardis

import ch.epfl.data.pardis.ir.Base
import ddbt.ast.{TypeDouble, TypeLong, Type}
import ddbt.lib.ManifestHelper

trait M3Ops extends M3StoreOps {
  // Function application
  def m3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends Base with M3Ops with M3StoreOpsExp {
  import ManifestHelper.man

  def div(x: Rep[Double]): Rep[Double] = x match {
    case Const(v) if x.tp.toString=="Long" => div(Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)) // unit(1.0/x.x.toDouble)
    case _ => __ifThenElse(infix_==(x,unit(0.0)),unit(0.0),numeric_divide(unit(1.0),x))
  }
  def mulLong(l: Rep[Long], r: Rep[Long]): Rep[Long] = {
    val ll = (l match {
      case Const(v) if l.tp.toString=="Double" => Const(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => l
    }).asInstanceOf[Rep[Long]]
    val rr = (r match {
      case Const(v) if r.tp.toString=="Double" => Const(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => r
    }).asInstanceOf[Rep[Long]]
    numeric_times[Long](ll,rr)
  }
  def mulDouble(l: Rep[Double], r: Rep[Double]): Rep[Double] = {
    val ll = (l match {
      case Const(v) if l.tp.toString=="Long" => Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => l
    }).asInstanceOf[Rep[Double]]
    val rr = (r match {
      case Const(v) if r.tp.toString=="Long" => Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => r
    }).asInstanceOf[Rep[Double]]
    numeric_times[Double](ll,rr)
  }
  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = if(v1 > v2) v1 else v2
  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = if(v1 < v2) v1 else v2
  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] =
    infix_substring (str, rep_asinstanceof[Long, Int](start, manifest[Long], manifest[Int]), rep_asinstanceof[Long, Int](start + length, manifest[Long], manifest[Int]))

  def m3apply(fn:String,args:List[Rep[_]],tp:Type) = {
    fn match {
      case "div" => div(args(0).asInstanceOf[Rep[Double]])
      case "mul" => tp match {
        case TypeLong => mulLong(args(0).asInstanceOf[Rep[Long]], args(1).asInstanceOf[Rep[Long]])
        case TypeDouble => mulDouble(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
        case _ => M3Apply(fn,args,man(tp))
      }
      case "listmax" => max(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "listmin" => min(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "substring" => substring(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[Long]],args(2).asInstanceOf[Rep[Long]])
      //case "regexp_match" => regexp_match(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[String]])
      //case "date_part" => date_part(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[java.util.Date]])
      case "date" => args(0) match {
        case Const(strDate) => Const(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
        case _ => M3Apply(fn,args,man(tp))
      }
      case _ => M3Apply(fn,args,man(tp)) // fallback for large or unknown functions
    }
  }

  case class M3Apply[T](name:String,args:List[Rep[_]],mT:Manifest[T]) extends Def[T]
}