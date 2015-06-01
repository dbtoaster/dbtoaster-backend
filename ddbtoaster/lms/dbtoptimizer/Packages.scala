package dbtoptimizer

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import dbtoptimizer._
import dbtoptimizer.lifters._
import oltp.opt.lifters._
import ddbt.lib.store._
import scala.reflect.SourceContext

trait ToasterBoosterOpsPkg extends ScalaOpsPkg with ExtendedExpressions
  with SimpleValOps with ImplicitConversionLifters /*with ListContainerOps*/
  /*with K3PersistentCollectionOps*/ with StdFunctionsOps with StoreOps with SEntryOps

trait ToasterBoosterOpsPkgExp extends ScalaOpsPkgExp with ToasterBoosterOpsPkg
  with SimpleValExp /*with ListContainerExp with K3PersistentCollectionExp*/
  with StdFunctionsExp with StoreExp with SEntryExp

trait ToasterBoosterOpsPkgExpOpt extends ScalaOpsPkgExpOpt with ToasterBoosterOpsPkgExp
  /*with K3PersistentCollectionExpOpt*/ with StdFunctionsExpOpt with StoreExpOpt with SEntryExpOpt

trait ToasterBoosterScalaCodeGenPkg extends ScalaCodeGenPkg with ScalaGenSimpleVal
  /*with ScalaGenK3PersistentCollection*/ with ToasterBoosterScalaCodegen with ScalaGenStdFunctions
   with ScalaGenSEntry with ScalaGenStore {
    val IR: ToasterBoosterOpsPkgExp
    import IR._
}

trait ToasterBoosterCCodeGenPkg extends ToasterBoosterScalaCodeGenPkg

trait DSL extends DSLBase with ScalaOpsPkg
  with LiftPrimitives with LiftString with LiftVariables
  with ToasterBoosterOpsPkg {
    var classArgs: List[Sym[_]] = Nil

    def newSStore[E<:Entry:Manifest]():Rep[Store[E]] = { val s = fresh[Store[E]]; collectStore[E](s); classArgs = classArgs :+ s; s }
}
