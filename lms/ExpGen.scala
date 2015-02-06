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

trait LMSExpGen extends M3OpsExp 
                   with ScalaOpsPkgExpOpt 
                   with ExtendedExpressions 
                   with Effects { self =>

  trait MyGenericCodegen extends GenericCodegen 
                            with oltp.opt.lifters.GenericGenStore {
    val IR: self.type = self

    def storeEntryType(sym: Exp[_]): String

    def storeType(sym: Exp[_]): String
  }

  val codegen: MyGenericCodegen

  override def reset = { storeSyms = Nil; super.reset }
  
  def emit[T: Manifest](sym: => Exp[T]): String
  
  def emit[T: Manifest](blk: Block[T]): String
  
  def emitTrigger[T: Manifest](sblk: Block[T], name: String, params: String): String
}

/*
 * The ExpGen objects instrument the LMS code generation such that we can
 * convert a Rep[T] into its String representation in the target code.
 */
object ScalaExpGen extends LMSExpGen { self =>
  
  class MyCodeGen extends ScalaCodeGenPkg 
                     with ScalaConciseCodegen 
                     with ScalaGenSEntry 
                     with ScalaGenStore 
                     with MyGenericCodegen 
                     with ScalaGenM3Ops {

    override val IR: self.type = self
    
    def emitSource[T: Manifest](sym: => Exp[T]): String = 
      emitSource(reifyBlock(sym))

    def emitSource[T: Manifest](body: Block[T]): String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T] != manifest[Unit]) {
          stream.println(quote(getBlockResult(transformedBody)))
        }
      }
      // reset // reset the whole LMS subsystem

      val unformattedScala = outStream.toString
      try {
        ScalaFormatter.format(unformattedScala)
      } catch {
        case e: ScalaParserException => unformattedScala
      }
    }

    def emitTriggerSource[T: Manifest](body: Block[T], name: String, params: String): String = {
      val funDef = 
        "def on" + name + "(" + params + ") {\n" + 
        ddbt.Utils.ind(emitSource(body)) + "\n}"

      var staticFieldsStr = ""
      staticFields.map { case (key, staticFldDef) => 
        staticFieldsStr += staticFldDef.trim + "\n"
      }
      staticFields.clear
      staticFieldsStr + "\n" + funDef
    }
  }

  val codegen = new MyCodeGen
  
  override def emit[T: Manifest](sym: => Exp[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(sym) 
  }

  override def emit[T: Manifest](blk: Block[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(blk) 
  }

  override def emitTrigger[T: Manifest](blk: Block[T], name: String, params: String): String = { 
    assert(codegen ne null)
    codegen.emitTriggerSource(blk, name, params) 
  }
}


object SparkExpGen extends LMSExpGen { self =>

  class MyCodeGen extends ScalaCodeGenPkg 
                     with ScalaConciseCodegen 
                     with ScalaGenSEntry 
                     with SparkGenStore 
                     with MyGenericCodegen 
                     with SparkGenM3Ops {

    override val IR: self.type = self
    
    def emitSource[T: Manifest](sym: => Exp[T]): String = 
      emitSource(reifyBlock(sym))

    def emitSource[T: Manifest](body: Block[T]): String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T] != manifest[Unit]) {
          stream.println(quote(getBlockResult(transformedBody)))
        }
      }
      // reset // reset the whole LMS subsystem

      val unformattedScala = outStream.toString
      try {
        ScalaFormatter.format(unformattedScala)
      } catch {
        case e: ScalaParserException => unformattedScala
      }
    }

    def emitTriggerSource[T: Manifest](body: Block[T], name: String, params: String): String = {
      val sBody = emitSource(body)

      var staticFieldsStr = 
        staticFields.map { case (key, staticFldDef) =>
          staticFldDef.trim
        }.mkString("\n")

      staticFields.clear      
      if (staticFieldsStr == "") sBody + "\n"
      else staticFieldsStr + "\n" + sBody + "\n"
    }
  }

  val codegen = new MyCodeGen

  override def emit[T: Manifest](sym: => Exp[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(sym) 
  }

  override def emit[T: Manifest](blk: Block[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(blk) 
  }

  override def emitTrigger[T: Manifest](blk: Block[T], name: String, params: String): String = {
    assert(codegen ne null)
    codegen.emitTriggerSource(blk, name, params)
  }
}

object CppExpGen extends LMSExpGen 
                    with COpsPkgExpOpt { self =>

  class MyCodeGen extends CCodeGenPkg 
                     with CCodegen 
                     with CConciseCodegen 
                     with CGenSEntry 
                     with CGenStore 
                     with MyGenericCodegen 
                     with CGenM3Ops {

    override val IR: self.type = self

    def emitSource[T: Manifest](sym: => Exp[T]): String = 
      emitSource(reifyBlock(sym))

    def emitSource[T: Manifest](body: Block[T]): String = {
      val outStream = new java.io.StringWriter
      val outWriter = new java.io.PrintWriter(outStream)
      withStream(outWriter) {
        val transformedBody = performTransformations(body)
        emitBlock(transformedBody)
        if (manifest[T] != manifest[Unit]) {
          stream.println(quote(getBlockResult(transformedBody)))
        }
      }
      // reset // reset the whole LMS subsystem

      val unformattedScala = outStream.toString
      try {
        ScalaFormatter.format(unformattedScala)
      } catch {
        case e: ScalaParserException => unformattedScala
      }
    }

    def emitTriggerSource[T: Manifest](body: Block[T], name: String, params: String): String = {
      val funDef = 
        "def on" + name + "(" + params + ") {\n" + 
        ddbt.Utils.ind(emitSource(body)) + "\n}"

      var staticFieldsStr = ""
      staticFields.map { case (key, staticFldDef) =>
        staticFieldsStr += staticFldDef.trim + "\n"
      }
      staticFields.clear
      staticFieldsStr + "\n" + funDef
    }
  }

  val codegen = new MyCodeGen
  
  override def emit[T: Manifest](sym: => Exp[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(sym) 
  }

  override def emit[T: Manifest](blk: Block[T]): String = { 
    assert(codegen ne null)
    codegen.emitSource(blk) 
  }

  override def emitTrigger[T: Manifest](blk: Block[T], name: String, params: String): String = {
    assert(codegen ne null)
    codegen.emitTriggerSource(blk, name, params) 
  }
}