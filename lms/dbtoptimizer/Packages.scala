package dbtoptimizer

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
import scalariform.formatter.preferences._
import scalariform.formatter.ScalaFormatter
import scalariform.parser.ScalaParserException
import dbtoptimizer._
import dbtoptimizer.lifters._
import oltp.opt.lifters._
import ddbt.lib.store._
import scala.reflect.SourceContext

trait ToasterBoosterOpsPkg extends ScalaOpsPkg with ExtendedExpressions
  with SimpleValOps with ImplicitConversionLifters with ListContainerOps
  with K3PersistentCollectionOps with StdFunctionsOps with StoreOps with SEntryOps

trait ToasterBoosterOpsPkgExp extends ScalaOpsPkgExp with ToasterBoosterOpsPkg
  with SimpleValExp with ListContainerExp with K3PersistentCollectionExp
  with StdFunctionsExp with StoreExp with SEntryExp

trait ToasterBoosterOpsPkgExpOpt extends ScalaOpsPkgExpOpt with ToasterBoosterOpsPkgExp
  with K3PersistentCollectionExpOpt with StdFunctionsExpOpt with StoreExpOpt with SEntryExpOpt

trait ToasterBoosterScalaCodeGenPkg extends ScalaCodeGenPkg with ScalaGenSimpleVal
  with ScalaGenK3PersistentCollection with ToasterBoosterScalaCodegen with ScalaGenStdFunctions
   with ScalaGenSEntry with ScalaGenStore {
    val IR: ToasterBoosterOpsPkgExp
    import IR._
}

trait DSL extends DSLBase with ScalaOpsPkg
  with LiftPrimitives with LiftString with LiftVariables
  with ToasterBoosterOpsPkg {
    var classArgs: List[Sym[_]] = Nil

//    def newStore[E<:Entry:Manifest]():Rep[Store[E]] = { val s = fresh[Store[E]]; checkOrInsertEntryClass[E](manifest[E]); classArgs = classArgs :+ s; s }
}
