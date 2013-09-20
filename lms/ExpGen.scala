package ddbt.codegen.lms

import scala.virtualization.lms.internal._
import scala.virtualization.lms.common._
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
object ScalaExpGen extends ScalaOpsPkgExp with M3OpsExp /*with ExpGen with K3MapExp with K3VarExp*/ { self =>
  class MyCodeGen extends ScalaCodeGenPkg with ScalaGenM3Ops /*with ScalaGenK3Map with ScalaGenK3Var*/ {
    val IR: self.type = self
    def emitSource[T:Manifest](sym: => Exp[T]) : String = emitSource(reifyBlock(sym))
    def emitSource[T:Manifest](body: Block[T]) : String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T]!=manifest[Unit]) stream.println(quote(getBlockResult(transformedBody)))
      }
      outStream.toString
    }
  }
  val codegen = new MyCodeGen
  def emit[T:Manifest](sym:Exp[T]) = { assert(codegen ne null); codegen.emitSource(sym) }
  def emit[T:Manifest](blk:Block[T]) = { assert(codegen ne null); codegen.emitSource(blk) }
  
}

// XXX: implement the counterpart for C/C++
