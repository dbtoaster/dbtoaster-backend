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
  // Nodes creation
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  // Function application
  def k3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends BaseExp with EffectExp with M3Ops
    with Equal with NumericOps with MathOps with DateOps with StringOps with PrimitiveOps with IfThenElseExp with StdFunctionsOps with K3MapOpsExp{
  import ManifestHelper.man
  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }

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

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class K3Apply[T](name:String,args:List[Exp[_]],mT:Manifest[T]) extends Def[T]
}

trait ScalaGenM3Ops extends ScalaGenBase with ScalaGenEffect with ScalaGenIfThenElse with ScalaGenK3MapOps {
  val IR: M3OpsExp with ExtendedExpressions
  import IR._
  import ddbt.Utils.{ind,tup}

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        stream.println("if (" + quote(c) + ") {") // there is only one branch (initialization)
        stream.println(getBlockContents(a))
        //stream.println("  "+quote(getBlockResult(a))) // useless undeclared Unit symbols
        stream.println("}")
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)

    case K3Apply(fn,args,_) => emitValDef(sym,"U"+fn+"("+(args map quote).mkString(",")+")")
    case _ => super.emitNode(sym,rhs)
  }

  override def quote(x: Exp[Any], forcePrintSymbol: Boolean) : String = {
    def printSym(s: Sym[Any]): String = {
      if(s.possibleToInline || s.noReference) {
        Def.unapply(s) match {
          case Some(d: Def[Any]) => d match {
            case Named(n) => n
            case _ =>
              val strWriter: java.io.StringWriter = new java.io.StringWriter;
              val stream = new java.io.PrintWriter(strWriter);
              withStream(stream) { 
                emitNode(s, d)
              }
              strWriter.toString
          }
          case None => if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
        }
      } else {
        if (s.attributes.contains(nameAttr)) s.attributes(nameAttr).toString else "x"+s.id
      }
    }
    x match {
      case Const(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
      case Const(c: Char) => "'"+c+"'"
      case Const(f: Float) => "%1.10f".format(f) + "f"
      case Const(l: Long) => l.toString + "L"
      case Const(null) => "null"
      case Const(z) => z.toString
      case s@Sym(n) => if (forcePrintSymbol) {
        printSym(s)
      } else { 
        isVoidType(s.tp) match {
          case true => "(" + /*"x" + n +*/ ")"
          case false => printSym(s)
        }
      }
      case _ => throw new RuntimeException("could not quote %s".format(x))
    }
  }

  // 
  // override def quote(x: Exp[Any]) : String = x match {
  //   case sym@Sym(_) if sym.attributes.contains(nameAttr) => sym.attributes(nameAttr).toString
  //   case _ => super.quote(x)
  // }
}
