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
import toasterbooster._
import toasterbooster.lifters._
import scala.reflect.SourceContext

trait DependencyGraphExport extends GraphVizDependencyGraphExport {
  val IR: ExtendedExpressions with Effects
  import IR._

  override def getNodeLabel(s: Sym[_]): String = quote(s, true) + "("+s.refCount+")"
}

class DepGraphImpl(val path: String) extends DSL with ToasterBoosterOpsPkgExpOpt { self =>
  val codegen = new DependencyGraphExport { val IR: self.type = self }

  def emitSource(x: TopLevel, stream: java.io.PrintWriter): Unit = x match {
    case TopLevel1 (name, mA, mB, f) => codegen.emitSource(f, name, stream)(mtype(mA), mtype(mB))
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

  def emitAll(): Unit = {
    assert(codegen ne null) //careful about initialization order
    val stream: java.io.PrintWriter = new PrintWriter(new FileWriter(path, false))
    stream.println("digraph G {")
    stream.println("    graph [fontsize=10 fontname=\"Verdana\"];")
    stream.println("    node [fontsize=10 fontname=\"Verdana\"];")

    rec.foreach {
      case (k, x) => emitSource(x, stream)
    }
    stream.println("}")
    stream.close
  }
}