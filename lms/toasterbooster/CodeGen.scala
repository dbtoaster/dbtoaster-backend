package toasterbooster

import java.io._
import org.dbtoaster.dbtoasterlib.StreamAdaptor._
import org.dbtoaster.dbtoasterlib.K3Collection._
import org.dbtoaster.dbtoasterlib.Source._
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import org.dbtoaster.dbtoasterlib.ImplicitConversions._
import org.dbtoaster.dbtoasterlib.StdFunctions._
import org.dbtoaster.dbtoasterlib.QueryInterface._
import scala.collection.mutable.Map
import xml._
import scala.actors.Actor._
import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.virtualization.lms.util.ReflectionUtil
//import scalariform.formatter.preferences._
//import scalariform.formatter.ScalaFormatter
//import scalariform.parser.ScalaParserException
import toasterbooster._
import toasterbooster.lifters._
import scala.reflect.SourceContext

trait ToasterBoosterExpression extends ExtendedExpressions with Effects {
  val SymNameAttributeKey = "sn"

  def infix_setName(s: Sym[Any], name: String): Sym[Any] = {
    s.attributes.update(SymNameAttributeKey, name)
    s
  }

  def infix_name(s: Sym[Any]): Option[String] = {
    s.attributes.get(SymNameAttributeKey).asInstanceOf[Option[String]]
  }
}

trait ToasterBoosterScalaCodegen extends ScalaCodegen { self =>
  val IR: ToasterBoosterExpression
  import IR._

  var classArgs: List[Sym[_]] = Nil

  override def emitSource[A : Manifest](args: List[Sym[_]], body: Block[A], className: String, out: PrintWriter) = {

    val sA = remap(manifest[A])

    val staticData = getFreeDataBlock(body)

    withStream(out) {
      stream.println("/*****************************************\n"+
                     "  Emitting Generated Code                  \n"+
                     "*******************************************/")
      emitFileHeader()

      val transformedBody = performTransformations(body)

      // TODO: separate concerns, should not hard code "pxX" name scheme for static data here
      stream.println("class "+className+(if (staticData.isEmpty && classArgs.isEmpty) "" else "("+staticData.map(p=>"p"+quote(p._1, true)+":"+p._1.tp).mkString(", ")+(if(!staticData.isEmpty && !classArgs.isEmpty) ", " else "") +classArgs.map(a => quote(a, true) + ":" + remap(a.tp)).mkString(", ")+")")+" extends (("+args.map( a => remap(a.tp)).mkString(", ")+")=>("+sA+")) {")
      stream.println("def apply("+args.map(a => quote(a, true) + ":" + remap(a.tp)).mkString(", ")+"): "+sA+" = {")
      emitBlock(transformedBody)
      stream.println(quote(getBlockResult(transformedBody)))

      stream.println("}")

      stream.println("}")
      stream.println("/*****************************************\n"+
                     "  End of Generated Code                  \n"+
                     "*******************************************/")
    }

    staticData
  }
}

class Impl(val clsWriter: PrintWriter, val pkg: String, val closeWriterAtTheEnd: Boolean) extends DSL with ToasterBoosterOpsPkgExpOpt { self =>
  def this(path: String, thePkg: String) = this(new PrintWriter(new FileWriter(path, false)), thePkg, true)
  def this(outStream: PrintStream, thePkg: String) = this(new PrintWriter(outStream), thePkg, false)

  val codegen = new ToasterBoosterScalaCodeGenPkg { val IR: self.type = self }

  def emitSource(x: TopLevel, stream: java.io.PrintWriter): Unit = {
    assert(codegen ne null) //careful about initialization order
    codegen.classArgs = classArgs
    x match {
      case TopLevel1  (name, mA1, mB, f) => codegen.emitSource(f, name, stream)(mtype(mA1), mtype(mB))
      case TopLevel2  (name, mA1, mA2, mB, f) => codegen.emitSource2(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mB))
      case TopLevel3  (name, mA1, mA2, mA3, mB, f) => codegen.emitSource3(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mB))
      case TopLevel4  (name, mA1, mA2, mA3, mA4, mB, f) => codegen.emitSource4(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mB))
      case TopLevel5  (name, mA1, mA2, mA3, mA4, mA5, mB, f) => codegen.emitSource5(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mB))
      case TopLevel6  (name, mA1, mA2, mA3, mA4, mA5, mA6, mB, f) => codegen.emitSource6(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mB))
      case TopLevel7  (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mB, f) => codegen.emitSource7(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mB))
      case TopLevel8  (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mB, f) => codegen.emitSource8(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mB))
      case TopLevel9  (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mB, f) => codegen.emitSource9(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mB))
      case TopLevel10 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mB, f) => codegen.emitSource10(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mB))
      case TopLevel11 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mB, f) => codegen.emitSource11(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mB))
      case TopLevel12 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mB, f) => codegen.emitSource12(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mB))
      case TopLevel13 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mB, f) => codegen.emitSource13(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mB))
      case TopLevel14 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mB, f) => codegen.emitSource14(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mB))
      case TopLevel15 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mB, f) => codegen.emitSource15(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mB))
      case TopLevel16 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mB, f) => codegen.emitSource16(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mB))
      case TopLevel17 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mB, f) => codegen.emitSource17(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mB))
      case TopLevel18 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mA18, mB, f) => codegen.emitSource18(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mA18), mtype(mB))
      case TopLevel19 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mA18, mA19, mB, f) => codegen.emitSource19(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mA18), mtype(mA19), mtype(mB))
    }
  }

  def emitAll(): Unit = {
    assert(codegen ne null) //careful about initialization order

    clsWriter.println("import scala.collection.mutable.Map")
    clsWriter.println("import scala.collection.JavaConversions.mapAsScalaMap")
    clsWriter.println("import java.util.HashMap")
    clsWriter.println("import org.dbtoaster.dbtoasterlib.K3Collection._")
    clsWriter.println("import org.dbtoaster.dbtoasterlib.ImplicitConversions._")
    clsWriter.println("import org.dbtoaster.dbtoasterlib.StdFunctions._")
    clsWriter.println("package " + pkg + " {")
    rec.foreach {
      case (k, x) =>
        val strWriter: java.io.StringWriter = new java.io.StringWriter
        val stream = new PrintWriter(strWriter)
        stream.println()
        stream.println("/* Function: " + x.name + " */")

        emitSource(x, stream)

        val unformattedScala = strWriter.toString

        //try {
        //  val preferences = FormattingPreferences().setPreference(IndentSpaces, 3)
        //  val formattedScala = ScalaFormatter.format(unformattedScala, preferences)
          //System.out.println(formattedScala)
          clsWriter.println(unformattedScala)
        //} catch {
        //  case e: ScalaParserException => System.out.println(unformattedScala); clsWriter.println(unformattedScala)
        //}
    }
    clsWriter.println("}")
    if(closeWriterAtTheEnd) clsWriter.close else clsWriter.flush
  }
}


class ValDefImpl(val path: String, val pkg: String) extends DSL with ToasterBoosterOpsPkgExpOpt { self =>
  val codegen = new ScalaCodeGenPkg with ScalaGenK3Var
  with ScalaGenK3Map with ScalaGenDate
  with ScalaGenGregorianCalendar with ScalaGenStdFunctions with ScalaCodegen { val IR: self.type = self }

  def emitSource(x: TopLevel, stream: java.io.PrintWriter): Unit = {
    assert(codegen ne null) //careful about initialization order
    x match {
      case TopLevel1 (name, mA1, mB, f) => codegen.emitSource(f, name, stream)(mtype(mA1), mtype(mB))
      case TopLevel2 (name, mA1, mA2, mB, f) => codegen.emitSource2(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mB))
      case TopLevel3 (name, mA1, mA2, mA3, mB, f) => codegen.emitSource3(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mB))
      case TopLevel4 (name, mA1, mA2, mA3, mA4, mB, f) => codegen.emitSource4(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mB))
      case TopLevel5 (name, mA1, mA2, mA3, mA4, mA5, mB, f) => codegen.emitSource5(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mB))
      case TopLevel6 (name, mA1, mA2, mA3, mA4, mA5, mA6, mB, f) => codegen.emitSource6(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mB))
      case TopLevel7 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mB, f) => codegen.emitSource7(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mB))
      case TopLevel8 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mB, f) => codegen.emitSource8(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mB))
      case TopLevel9 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mB, f) => codegen.emitSource9(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mB))
      case TopLevel10 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mB, f) => codegen.emitSource10(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mB))
      case TopLevel11 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mB, f) => codegen.emitSource11(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mB))
      case TopLevel12 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mB, f) => codegen.emitSource12(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mB))
      case TopLevel13 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mB, f) => codegen.emitSource13(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mB))
      case TopLevel14 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mB, f) => codegen.emitSource14(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mB))
      case TopLevel15 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mB, f) => codegen.emitSource15(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mB))
      case TopLevel16 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mB, f) => codegen.emitSource16(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mB))
      case TopLevel17 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mB, f) => codegen.emitSource17(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mB))
      case TopLevel18 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mA18, mB, f) => codegen.emitSource18(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mA18), mtype(mB))
      case TopLevel19 (name, mA1, mA2, mA3, mA4, mA5, mA6, mA7, mA8, mA9, mA10, mA11, mA12, mA13, mA14, mA15, mA16, mA17, mA18, mA19, mB, f) => codegen.emitSource19(f, name, stream)(mtype(mA1), mtype(mA2), mtype(mA3), mtype(mA4), mtype(mA5), mtype(mA6), mtype(mA7), mtype(mA8), mtype(mA9), mtype(mA10), mtype(mA11), mtype(mA12), mtype(mA13), mtype(mA14), mtype(mA15), mtype(mA16), mtype(mA17), mtype(mA18), mtype(mA19), mtype(mB))
    }
  }

  def emitAll(): Unit = {
    assert(codegen ne null) //careful about initialization order

    val clsWriter: java.io.PrintWriter = new PrintWriter(new FileWriter(path, false))
    clsWriter.println("package " + pkg)
    clsWriter.println("import scala.collection.mutable.Map")
    clsWriter.println("import scala.collection.JavaConversions.mapAsScalaMap")
    clsWriter.println("import java.util.HashMap")
    clsWriter.println("import org.dbtoaster.dbtoasterlib.K3Collection._")
    clsWriter.println("import org.dbtoaster.dbtoasterlib.ImplicitConversions._")

    clsWriter.close()
    rec.foreach {
      case (k, x) =>
        val strWriter: java.io.StringWriter = new java.io.StringWriter
        val stream = new PrintWriter(strWriter)
        val clsWriter: java.io.PrintWriter = new PrintWriter(new FileWriter(path, true))
        stream.println()
        stream.println("/* Function: " + x.name + " */")

        emitSource(x, stream)

        val unformattedScala = strWriter.toString
        
        //try {
          //val preferences = FormattingPreferences().setPreference(IndentSpaces, 3)
          //val formattedScala = ScalaFormatter.format(unformattedScala, preferences)
          //System.out.println(formattedScala)
          clsWriter.println(unformattedScala)
        //} catch {
        //  case e: ScalaParserException => System.out.println(unformattedScala); clsWriter.println(unformattedScala)
        //}
        clsWriter.close
    }
  }
}