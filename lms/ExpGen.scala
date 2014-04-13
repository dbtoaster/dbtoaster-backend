package ddbt.codegen.lms

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import ddbt.ast._
import ddbt.lib.store._
import scalariform.formatter.preferences._
import scalariform.formatter.ScalaFormatter
import scalariform.parser.ScalaParserException
import oltp.opt.lifters._

/**
 * Helpers for LMS code generation
 *
 * @author Mohammad Dashti, TCK
 */

/* Helper to convert AST types into manifests */
object ManifestHelper {
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
  def manEntry(ts:List[Type]):Manifest[Entry] = {
    val ms:List[Manifest[_]] = ts map man
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.SEntry"+ts.size)
    scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*).asInstanceOf[Manifest[Entry]]
  }
  def manStore(ts:List[Type]):Manifest[Store[Entry]] = manStore(manEntry(ts))

  def manStore(entryMan:Manifest[Entry]):Manifest[Store[Entry]] = {
    val cls:java.lang.Class[_] = Class.forName("ddbt.lib.store.Store")
    scala.reflect.ManifestFactory.classType(cls,entryMan).asInstanceOf[Manifest[Store[Entry]]]
  }
  def zero(tp: Type) = tp match {
    case TypeLong => 0L
    case TypeDouble => 0.0
    case TypeString => ""
    case TypeDate => new java.util.Date()
  }
  def zero(m: Manifest[_]) = m.toString match {
    case "Long" => 0L
    case "Double" => 0.0
    case "String" => ""
    case "java.util.Date" => new java.util.Date()
    case _ => sys.error("Bad manifest")
  }
}


trait LMSExpGen extends M3OpsExp with ScalaOpsPkgExpOpt with ExtendedExpressions with Effects { self =>
  trait MyGenericCodegen extends GenericCodegen with oltp.opt.lifters.GenericGenStore {
    val IR: self.type = self
  }

  val codegen: MyGenericCodegen
  override def reset = { storeSyms = Nil; super.reset }
  def emit[T:Manifest](sym: => Exp[T])
  def emit[T:Manifest](blk:Block[T])
  def emitTrigger[T:Manifest](blk:Block[T],name:String,args:List[(String,Type)])
}

/*
 * The ExpGen objects instrument the LMS code generation such that we can
 * convert a Rep[T] into its String representation in the target code.
 */
object ScalaExpGen extends LMSExpGen { self =>
  class MyCodeGen extends ScalaCodeGenPkg with ScalaConciseCodegen with ScalaGenM3Ops with ScalaGenSEntryInlined with ScalaGenStoreInlined with MyGenericCodegen {
    override val IR: self.type = self
    def emitSource[T:Manifest](sym: => Exp[T]) : String = emitSource(reifyBlock(sym))
    def emitSource[T:Manifest](body: Block[T]) : String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T]!=manifest[Unit]) stream.println(quote(getBlockResult(transformedBody)))
      }
      // reset // reset the whole LMS subsystem

      val unformattedScala = outStream.toString
      try {
        ScalaFormatter.format(unformattedScala)
      } catch {
        case e: ScalaParserException => unformattedScala
      }
    }
    def emitTriggerSource[T:Manifest](body: Block[T],name:String,args:List[(String,Type)]) : String = {
      val funDef = "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ddbt.Utils.ind(emitSource(body))+"\n}"

      var staticFieldsStr = ""
      staticFields.map { case (key, staticFldDef) =>
        staticFieldsStr += staticFldDef.trim + "\n"
      }
      staticFields.clear

      staticFieldsStr + "\n" + funDef
    }
  }
  val codegen = new MyCodeGen
  override def emit[T:Manifest](sym: => Exp[T]) = { assert(codegen ne null); codegen.emitSource(sym) }
  override def emit[T:Manifest](blk:Block[T]) = { assert(codegen ne null); codegen.emitSource(blk) }
  override def emitTrigger[T:Manifest](blk:Block[T],name:String,args:List[(String,Type)]) = { assert(codegen ne null); codegen.emitTriggerSource(blk,name,args) }
}

object CppExpGen extends LMSExpGen with COpsPkgExpOpt { self =>
  class MyCodeGen extends CCodeGenPkg with CCodegen with CConciseCodegen with CGenM3Ops with CGenSEntryInlined with CGenStoreInlined with MyGenericCodegen {
    override val IR: self.type = self
    def emitSource[T:Manifest](sym: => Exp[T]) : String = emitSource(reifyBlock(sym))
    def emitSource[T:Manifest](body: Block[T]) : String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T]!=manifest[Unit]) stream.println(quote(getBlockResult(transformedBody)))
      }
      // reset // reset the whole LMS subsystem

      val unformattedScala = outStream.toString
      try {
        ScalaFormatter.format(unformattedScala)
      } catch {
        case e: ScalaParserException => unformattedScala
      }
    }
    def emitTriggerSource[T:Manifest](body: Block[T],name:String,args:List[(String,Type)]) : String = {
      val funDef = "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ddbt.Utils.ind(emitSource(body))+"\n}"

      var staticFieldsStr = ""
      staticFields.map { case (key, staticFldDef) =>
        staticFieldsStr += staticFldDef.trim + "\n"
      }
      staticFields.clear

      staticFieldsStr + "\n" + funDef
    }
  }
  val codegen = new MyCodeGen
  override def emit[T:Manifest](sym: => Exp[T]) = { assert(codegen ne null); codegen.emitSource(sym) }
  override def emit[T:Manifest](blk:Block[T]) = { assert(codegen ne null); codegen.emitSource(blk) }
  override def emitTrigger[T:Manifest](blk:Block[T],name:String,args:List[(String,Type)]) = { assert(codegen ne null); codegen.emitTriggerSource(blk,name,args) }
}

// XXX: implement the counterpart for C/C++
