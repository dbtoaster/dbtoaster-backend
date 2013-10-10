package ddbt.codegen.lms
import ddbt.ast._

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import toasterbooster.lifters._

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in k3apply)
 *
 * @author Mohammad Dashti, TCK
 */

trait M3Ops extends K3MapOps {
  // Function application
  def k3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends BaseExp with EffectExp with M3Ops
    with Equal with NumericOps with MathOps with DateOps with StringOps with PrimitiveOps with IfThenElseExp with StdFunctionsOps with K3MapOpsExp{
  import ManifestHelper.man

  def k3apply(fn:String,args:List[Exp[_]],tp:Type) = {
    fn match {
      case "div" => div(args(0).asInstanceOf[Rep[Double]])
      case "listmax" => max(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "listmin" => min(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "substring" => substring(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[Long]],args(2).asInstanceOf[Rep[Long]])
      case "regexp_match" => regexp_match(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[String]])
      case "date_part" => date_part(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[java.util.Date]])
      case "date" => args(0) match {
        case Const(strDate) => Const(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
        case _ => K3Apply(fn,args,man(tp))
      }
      case _ => K3Apply(fn,args,man(tp)) // fallback for large or unknown functions
    }
  }

  case class K3Apply[T](name:String,args:List[Exp[_]],mT:Manifest[T]) extends Def[T]
}

trait ScalaGenM3Ops extends ScalaGenBase with ScalaGenEffect with ScalaGenIfThenElse with ScalaGenK3MapOps {
  val IR: M3OpsExp with ExtendedExpressions
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        stream.println("if (" + quote(c) + ") {") // there is only one branch (initialization)
        stream.println(getBlockContents(a))
        //stream.println("  "+quote(getBlockResult(a))) // useless undeclared Unit symbols
        stream.println("}")

    case K3Apply(fn,args,_) => emitValDef(sym,"U"+fn+"("+(args map quote).mkString(",")+")")
    case _ => super.emitNode(sym,rhs)
  }
}
