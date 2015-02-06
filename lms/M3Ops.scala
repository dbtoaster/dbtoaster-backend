package ddbt.codegen.lms

import ddbt.ast._
import ddbt.lib.ManifestHelper
import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in m3apply)
 *
 * @author Mohammad Dashti, TCK
 */

// M3StoreOps / M3MapOps are interchangeable

trait M3Ops extends M3StoreOps {
  // Function application
  def m3apply(fn: String, args: List[Rep[_]], tp: Type): Rep[_]
}

trait M3OpsExp extends BaseExp with EffectExp 
                               with M3Ops 
                               with Equal 
                               with NumericOps 
                               with MathOps
                               with DateOps 
                               with StringOps 
                               with PrimitiveOps 
                               with IfThenElseExp 
                               with M3StoreOpsExp 
                               with CastingOps 
                               with OrderingOps {
  import ManifestHelper.man



  def div(x: Rep[Double]): Rep[Double] = x match {
    case Const(v) if x.tp.toString == "Int" => // unit(1/x.toDouble)
      div(Const(scala.runtime.BoxesRunTime.unboxToInt(v).toDouble))     
    case Const(v) if x.tp.toString == "Long" => // unit(1L/x.toDouble)
      div(Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)) 
    case _ => 
      __ifThenElse(equals(x, unit(0.0)), unit(0.0), numeric_divide(unit(1.0), x))
  }

  def mulLong(l: Rep[Long], r: Rep[Long]): Rep[Long] = {
    val ll = (l match {
      case Const(v) if l.tp.toString == "Double" => 
        Const(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => l
    }).asInstanceOf[Rep[Long]]
    val rr = (r match {
      case Const(v) if r.tp.toString == "Double" => 
        Const(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => r
    }).asInstanceOf[Rep[Long]]
    numeric_times[Long](ll, rr)
  }

  def mulDouble(l: Rep[Double], r: Rep[Double]): Rep[Double] = {
    val ll = (l match {
      case Const(v) if l.tp.toString == "Long" => 
        Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => l
    }).asInstanceOf[Rep[Double]]
    val rr = (r match {
      case Const(v) if r.tp.toString == "Long" => 
        Const(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => r
    }).asInstanceOf[Rep[Double]]
    numeric_times[Double](ll, rr)
  }

  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = 
    if (v1 > v2) v1 else v2
  
  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = 
    if (v1 < v2) v1 else v2
  
  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] =
    infix_substring(str, 
      rep_asinstanceof[Long, Int](start, manifest[Long], manifest[Int]), 
      rep_asinstanceof[Long, Int](start + length, manifest[Long], manifest[Int]))

  def m3apply(fn: String, args: List[Exp[_]], tp: Type) = fn match {
    case "div" => div(args(0).asInstanceOf[Rep[Double]])
    case "mul" => tp match {
      case TypeLong => 
        mulLong(args(0).asInstanceOf[Rep[Long]], args(1).asInstanceOf[Rep[Long]])
      case TypeDouble => 
        mulDouble(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
      case _ => M3Apply(fn, args, man(tp))
    }
    case "listmax" => 
      max(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
    case "listmin" => 
      min(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
    case "substring" => 
      substring(args(0).asInstanceOf[Rep[String]], 
                args(1).asInstanceOf[Rep[Long]],
                args(2).asInstanceOf[Rep[Long]])
    //case "regexp_match" => regexp_match(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[String]])
    //case "date_part" => date_part(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[java.util.Date]])
    case "date" => args(0) match {
      case Const(strDate) => Const(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
      case _ => M3Apply(fn, args, man(tp))
    }
    case _ => M3Apply(fn, args, man(tp)) // fallback for large or unknown functions
  }

  case class M3Apply[T](name: String, args: List[Exp[_]], mT: Manifest[T]) extends Def[T]
}

trait ScalaGenM3Ops extends ScalaGenBase with ScalaGenEffect 
                                         with ScalaGenIfThenElse 
                                         with ScalaGenM3StoreOps {
  val IR: M3OpsExp with ExtendedExpressions
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    // case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        // stream.println("if (" + quote(c) + ") {") // there is only one branch (initialization)
        // stream.println(getBlockContents(a))
        //stream.println("  "+quote(getBlockResult(a))) // useless undeclared Unit symbols
        // stream.println("}")

    case M3Apply(fn, args, _) => 
      emitValDef(sym, "U" + fn + "(" + (args map quote).mkString(",") + ")")
    case _ => super.emitNode(sym, rhs)
  }
}

trait SparkGenM3Ops extends ScalaGenBase with ScalaGenEffect 
                                         with ScalaGenIfThenElse 
                                         with SparkGenM3StoreOps {
  val IR: M3OpsExp with ExtendedExpressions
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    // case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        // stream.println("if (" + quote(c) + ") {") // there is only one branch (initialization)
        // stream.println(getBlockContents(a))
        //stream.println("  "+quote(getBlockResult(a))) // useless undeclared Unit symbols
        // stream.println("}")

    case M3Apply(fn, args, _) => 
      emitValDef(sym, "U" + fn + "(" + (args map quote).mkString(",") + ")")
    case _ => super.emitNode(sym, rhs)
  }
}

trait CGenM3Ops extends CGenBase with CGenEffect with CGenIfThenElse with CGenM3StoreOps {
  val IR: M3OpsExp with ExtendedExpressions
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    // case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        // stream.println("if (" + quote(c) + ") {") // there is only one branch (initialization)
        // stream.println(getBlockContents(a))
        //stream.println("  "+quote(getBlockResult(a))) // useless undeclared Unit symbols
        // stream.println("}")

    case M3Apply(fn, args, _) => 
      emitValDef(sym, "U" + fn + "(" + (args map quote).mkString(",") + ")")
    case _ => super.emitNode(sym,rhs)
  }
}

/*
 * Lifter Classes for StdFunctions
 * Copied from package toasterbooster.lifters
 * @author Mohammad Dashti
 *

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._

trait StdFunctionsOps extends IfThenElse with OrderingOps with NumericOps
  with StringOps with PrimitiveOps with MathOps with CastingOps
  with ObjectOps with SimpleDateFormatOps with Equal{

  def div(x: Rep[Double]): Rep[Double] = __ifThenElse(equals(x,unit(0.0)),unit(0.0),numeric_divide(unit(1.0),x))

  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = if(v1 > v2) v1 else v2
  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = if(v1 < v2) v1 else v2

  def listmax(v1: Rep[Long], v2: Rep[Long])(implicit o: Overloaded1): Rep[Double] = if(v1 > v2) rep_asinstanceof[Long, Double](v1, manifest[Long], manifest[Double]) else rep_asinstanceof[Long, Double](v2, manifest[Long], manifest[Double])
  def listmax(v1: Rep[Double], v2: Rep[Long])(implicit o: Overloaded2): Rep[Double] = if(v1 > v2.asInstanceOf[Rep[Double]]) v1 else rep_asinstanceof[Long, Double](v2, manifest[Long], manifest[Double])
  def listmax(v1: Rep[Long], v2: Rep[Double])(implicit o: Overloaded3): Rep[Double] = if(v1.asInstanceOf[Rep[Double]] > v2) rep_asinstanceof[Long, Double](v1, manifest[Long], manifest[Double]) else v2
  def listmax(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = if(v1 > v2) v1 else v2

  def year_part(date: Rep[java.util.Date]): Rep[Long]
  def month_part(date: Rep[java.util.Date]): Rep[Long]
  def day_part(date: Rep[java.util.Date]): Rep[Long]
  def date_part(field: Rep[String], date: Rep[java.util.Date]): Rep[Long]
  def regexp_match(regexp: Rep[String], str: Rep[String]): Rep[Int]
  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] =
    infix_substring (str, rep_asinstanceof[Long, Int](start, manifest[Long], manifest[Int]), rep_asinstanceof[Long, Int](start + length, manifest[Long], manifest[Int]))

  def vec_length(x: Rep[Double], y: Rep[Double], z: Rep[Double]): Rep[Double] = Math.sqrt(x*x + y*y + z*z)
  def vec_dot(x1: Rep[Double], y1: Rep[Double], z1: Rep[Double],
                x2: Rep[Double], y2: Rep[Double], z2: Rep[Double]): Rep[Double] = x1*x2 + y1*y2 + z1*z2

  def vector_angle(x1: Rep[Double], y1: Rep[Double], z1: Rep[Double],
                x2: Rep[Double], y2: Rep[Double], z2: Rep[Double]): Rep[Double] =
    Math.acos (
      vec_dot(x1,y1,z1,x2,y2,z2) / (
        vec_length(x1,y1,z1) * vec_length(x2,y2,z2)
      )
    )

  def dihedral_angle(x1: Rep[Double], y1: Rep[Double], z1: Rep[Double],
                       x2: Rep[Double], y2: Rep[Double], z2: Rep[Double],
                       x3: Rep[Double], y3: Rep[Double], z3: Rep[Double],
                       x4: Rep[Double], y4: Rep[Double], z4: Rep[Double]): Rep[Double] = {
    val v1x = x2 - x1
    val v1y = y2 - y1
    val v1z = z2 - z1

    val v2x = x3 - x2
    val v2y = y3 - y2
    val v2z = z3 - z2

    val v3x = x4 - x3
    val v3y = y4 - y3
    val v3z = z4 - z3

    val n1x = (v1y * v2z - v1z * v2y)
    val n1y = (v1z * v2x - v1x * v2z)
    val n1z = (v1x * v2y - v1y * v2x)

    val n2x = (v2y * v3z - v2z * v3y)
    val n2y = (v2z * v3x - v2x * v3z)
    val n2z = (v2x * v3y - v2y * v3x)

    Math.atan2 ( vec_length(v2x,v2y,v2z) *  vec_dot(v1x,v1y,v1z, n2x,n2y,n2z), vec_dot(n1x,n1y,n1z, n2x,n2y,n2z))
  }

  def hash(number: Rep[Long]): Rep[Long] = {
    val v1 = number * unit(3935559000370003845L + 2691343689449507681L)
    val v2 = long_binaryxor(v1, (v1 >> unit(21)))
    val v3 = long_binaryxor(v2, (v2 << unit(37)))
    val v4 = long_binaryxor(v3, (v3 >> unit(4)))
    val v5 = v4 * unit(4768777413237032717L)
    val v6 = long_binaryxor(v5, (v5 >> unit(20)))
    val v7 = long_binaryxor(v6, (v6 << unit(41)))
    val v8 = long_binaryxor(v7, (v7 >> unit(5)))
    v8
  }

  def PI: Rep[Double] = unit(3.141592653589793238462643383279502884)
  def radians(degree: Rep[Double]): Rep[Double] = (degree * PI) / unit(180.0)
  def degrees(radian: Rep[Double]): Rep[Double] = (radian * unit(180.0)) / PI
  def pow(x: Rep[Double], y: Rep[Double]): Rep[Double] = Math.pow(x, y)
  def sqrt(x: Rep[Double]): Rep[Double] = Math.sqrt(x)
  def cos(x: Rep[Double]): Rep[Double] = Math.cos(x)

  / * Type conversion functions * /
  def cast_int(l: Rep[Long]): Rep[Long] = l
  def cast_int(d: Rep[Double])(implicit o: Overloaded1): Rep[Long] = rep_asinstanceof[Double, Long](d, manifest[Double], manifest[Long])
  def cast_int(s: Rep[String])(implicit o: Overloaded2): Rep[Long] = s.toLong

  def cast_float(l: Rep[Long])(implicit o: Overloaded1): Rep[Double] = rep_asinstanceof[Long, Double](l, manifest[Long], manifest[Double])
  def cast_float(d: Rep[Double]): Rep[Double] = d
  def cast_float(s: Rep[String])(implicit o: Overloaded2): Rep[Double] = s.toDouble

  def cast_string(a: Rep[Any]): Rep[String] = object_tostring(a)
  def cast_string(d: Rep[java.util.Date])(implicit o: Overloaded1): Rep[String] = {
    val dateFormat = newSimpleDateFormat(unit("yyyy-MM-dd"))
    dateFormat.format(d)
  }

  def cast_date(d: Rep[java.util.Date]): Rep[java.util.Date] = d
  def cast_date (s: Rep[String])(implicit o: Overloaded1): Rep[java.util.Date] = {
    val dateFormat = newSimpleDateFormat(unit("yyyy-MM-dd"))
    dateFormat.parse(s)
  }
}

trait StdFunctionsExp extends StdFunctionsOps with BaseExp {
  case class StdYearPart(x: Exp[java.util.Date]) extends Def[Long]
  case class StdMonthPart(x: Exp[java.util.Date]) extends Def[Long]
  case class StdDayPart(x: Exp[java.util.Date]) extends Def[Long]
  case class StdDatePart(field: Exp[String], x: Exp[java.util.Date]) extends Def[Long]

  case class StdRegexpMatch(regexp: Exp[String], str: Exp[String]) extends Def[Int]

  def year_part(date: Exp[java.util.Date]) = StdYearPart(date)
  def month_part(date: Exp[java.util.Date]) = StdMonthPart(date)
  def day_part(date: Exp[java.util.Date]) = StdDayPart(date)
  def date_part(field: Exp[String], date: Exp[java.util.Date]) = StdDatePart(field, date)

  def regexp_match(regexp: Exp[String], str: Exp[String]) = StdRegexpMatch(regexp, str)

  //////////////
  // mirroring
  override def mirror[A:Manifest](e: Def[A], f: Transformer)(implicit pos: scala.reflect.SourceContext): Exp[A] = (e match {
    case StdYearPart(x) => year_part(f(x))
    case StdMonthPart(x) => month_part(f(x))
    case StdDayPart(x) => day_part(f(x))
    case StdDatePart(field, x) => date_part(f(field), f(x))

    case StdRegexpMatch(regexp, str) => regexp_match(f(regexp), f(str))

    case _ => super.mirror(e,f)
  }).asInstanceOf[Exp[A]] // why??
}

trait StdFunctionsExpOpt extends StdFunctionsExp {
  override def year_part(x: Exp[java.util.Date]): Exp[Long] = x match {
    case Const(d: java.util.Date) => unit({
      val c = java.util.Calendar.getInstance
      c.setTime(d)
      c.get(java.util.Calendar.YEAR)
    })
    case _ => super.year_part(x)
  }

  override def month_part(x: Exp[java.util.Date]): Exp[Long] = x match {
    case Const(d: java.util.Date) => unit({
      val c = java.util.Calendar.getInstance
      c.setTime(d)
      c.get(java.util.Calendar.MONTH)
    })
    case _ => super.month_part(x)
  }

  override def day_part(x: Exp[java.util.Date]): Exp[Long] = x match {
    case Const(d: java.util.Date) => unit({
      val c = java.util.Calendar.getInstance
      c.setTime(d)
      c.get(java.util.Calendar.DAY_OF_MONTH)
    })
    case _ => super.day_part(x)
  }

  / *override def date_part(field: Exp[String], date: Exp[java.util.Date]): Exp[Long] = field match {
    case Const(fld) => date match {
      case Const(dt) => unit({
        val c = java.util.Calendar.getInstance
        c.setTime(dt)
        fld.toUpperCase() match {
          case "YEAR"  => c.get(java.util.Calendar.YEAR)
          case "MONTH" => c.get(java.util.Calendar.MONTH)
          case "DAY"   => c.get(java.util.Calendar.DAY_OF_MONTH)
          case _ => throw new DBToasterExceptions.DBTFatalError(
                                  "Invalid date part.")
        }
      })
      case _ => super.date_part(field, date)
    }
    case _ => super.date_part(field, date)
  }* /
}

trait ScalaGenStdFunctions extends ScalaGenBase {
  val IR: StdFunctionsExp
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case StdYearPart(x) => emitValDef(sym, "year_part(%s)".format(quote(x)))
    case StdMonthPart(x) => emitValDef(sym, "month_part(%s)".format(quote(x)))
    case StdDayPart(x) => emitValDef(sym, "day_part(%s)".format(quote(x)))
    case StdDatePart(field, date) => emitValDef(sym, "Udate_part(%s, %s)".format(quote(field), quote(date)))

    case StdRegexpMatch(regexp, str) => emitValDef(sym, "Uregexp_match(%s, %s)".format(quote(regexp), quote(str)))

    case _ => super.emitNode(sym, rhs)
  }
}
*/
