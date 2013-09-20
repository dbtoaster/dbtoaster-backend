package ddbt.codegen.lms

import scala.virtualization.lms.internal._
import scala.virtualization.lms.common._
import toasterbooster._
import toasterbooster.lifters._

/* Helper to convert AST types into manifests */
object ManifestHelper {
  import ddbt.ast._
  def man(tp:Type):Manifest[_] = tp match {
    case TypeLong => manifest[Long]
    case TypeDouble => manifest[Double]
    case TypeString => manifest[String]
    case TypeDate => manifest[java.util.Date]
    case _ => sys.error("No manifest for "+tp)
  }
  def man(ts:List[Type]):Manifest[_] = ts.size match {
    case 1 => man(ts.head)
    case _ => val ms:List[Manifest[_]] = ts map man
      val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
      scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*)
  }
}

/*
 * The ExpGen objects instrument the LMS code generation such that we can
 * convert a Rep[T] into its String representation in the target code.
 */

//trait ExpGen extends DSLBase with ScalaOpsPkg {}

object ScalaExpGen extends ScalaOpsPkgExp with M3OpsExp with ToasterBoosterExpression /*with ExpGen with K3MapExp with K3VarExp*/ { self =>
  trait MyCodeGen extends ScalaCodeGenPkg with ScalaGenM3Ops with ToasterBoosterScalaCodegen /*with ScalaGenK3Map with ScalaGenK3Var*/ {
    val IR: ScalaOpsPkgExp with M3OpsExp with ToasterBoosterExpression

    def emitSource[T:Manifest](sym: => IR.Exp[T]) : String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      val body = reifyBlock(sym)
      //val staticData = getFreeDataBlock(body)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T]!=manifest[Unit])
          stream.println(quote(getBlockResult(transformedBody)))
      }
      //staticData
      outStream.toString
    }

    override def quote(x: IR.Exp[Any], forcePrintSymbol: Boolean) : String = x match {
      case IR.Const(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
      case IR.Const(c: Char) => "'"+c+"'"
      case IR.Const(f: Float) => "%1.10f".format(f) + "f"
      case IR.Const(l: Long) => l.toString + "L"
      case IR.Const(null) => "null"
      case IR.Const(z) => z.toString
      case s@IR.Sym(n) => infix_name(s.asInstanceOf[Sym[Any]]).getOrElse("x"+n)
      case _ => throw new RuntimeException("could not quote %s".format(x))
    }

    /*override def quote(x: IR.Exp[Any], forcePrintSymbol: Boolean) : String = {
      def printSym(s: IR.Sym[Any]): String = {
        if(infix_possibleToInline(s.asInstanceOf[Sym[Any]]) || infix_noReference(s.asInstanceOf[Sym[Any]])) {
          IR.Def.unapply(s) match {
            case Some(d: IR.Def[Any]) => {
              val strWriter: java.io.StringWriter = new java.io.StringWriter;
              val stream = new java.io.PrintWriter(strWriter);
              withStream(stream) { 
                emitNode(s, d)
              }
              strWriter.toString
            }
            case None =>  infix_name(s.asInstanceOf[Sym[Any]]).getOrElse("x"+s.id)
          }
        } else {
          infix_name(s.asInstanceOf[Sym[Any]]).getOrElse("x"+s.id)
        }
      }
      x match {
        case IR.Const(s: String) => "\""+s.replace("\"", "\\\"").replace("\n", "\\n")+"\"" // TODO: more escapes?
        case IR.Const(c: Char) => "'"+c+"'"
        case IR.Const(f: Float) => "%1.10f".format(f) + "f"
        case IR.Const(l: Long) => l.toString + "L"
        case IR.Const(null) => "null"
        case IR.Const(z) => z.toString
        case s@IR.Sym(n) => if (forcePrintSymbol) {
          printSym(s)
        } else { 
          isVoidType(s.tp) match {
            case true => "(" + /*"x" + n +*/ ")"
            case false => printSym(s)
          }
        }
        case _ => throw new RuntimeException("could not quote " + x)
      }
    }*/
  }
  val codegen = new MyCodeGen {val IR: self.type = self}
  def emit[T:Manifest](sym:Exp[T]) = { assert(codegen ne null); codegen.emitSource(sym) }
}

// XXX: implement the counterpart for C/C++
