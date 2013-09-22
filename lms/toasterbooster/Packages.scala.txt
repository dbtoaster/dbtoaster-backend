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

trait ToasterBoosterOpsPkg extends ScalaOpsPkg with ExtendedExpressions 
  with K3VarOps with ImplicitConversionLifters with K3MapOps with StdFunctionsOps

trait ToasterBoosterOpsPkgExp extends ScalaOpsPkgExp with ToasterBoosterOpsPkg 
  with K3VarExp with K3MapExp with StdFunctionsExp with ToasterBoosterExpression

trait ToasterBoosterOpsPkgExpOpt extends ScalaOpsPkgExpOpt with ToasterBoosterOpsPkgExp
  with K3MapExpOpt with StdFunctionsExpOpt

trait ToasterBoosterScalaCodeGenPkg extends ScalaCodeGenPkg with ScalaGenK3Var 
  with ScalaGenK3Map with ToasterBoosterScalaCodegen with ScalaGenStdFunctions {
  	val IR: ToasterBoosterOpsPkgExp
  	import IR._
}

trait DSL extends DSLBase with ScalaOpsPkg 
  with LiftPrimitives with LiftString with LiftVariables 
  with ToasterBoosterOpsPkg {
  	var classArgs: List[Sym[_]] = Nil
}