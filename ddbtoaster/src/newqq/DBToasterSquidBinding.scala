package ddbt.newqq

import ddbt.lib.store.deep.StoreDSL
import squid.scback._
import squid.utils._

class DBToasterSquidBinding[SC <: StoreDSL](val SC: SC) {

  object Sqd extends AutoboundPardisIR[SC.type](SC) with PardisBinding.DefaultRedirections[SC.type] {
    
    protected val GEApplySymbol = loadMtdSymbol(loadTypSymbol("ddbt.lib.store.GenericEntry$"), "apply", None)
    protected val WhileSymbol = loadMtdSymbol(loadTypSymbol("squid.lib.package$"), "While", None)
    protected val StrCmpSymbol = loadMtdSymbol(loadTypSymbol("ddbt.lib.store.StringExtra$"), "StringCompare", None)
    protected val StrPrintfSymbol = loadMtdSymbol(loadTypSymbol("ddbt.lib.store.StringExtra$"), "StringPrintf", None)
    /** Manual deep bindings for when the AutoBinder did not generate one.
      * */
    override def methodApp(self: Rep, mtd: MtdSymbol, targs: List[TypeRep], argss: List[ArgList], tp: TypeRep): Rep = mtd match {

      case GEApplySymbol =>
        val ArgsVarargs(Args(ign),Args(cols @ _*)) :: Nil = argss
        blockWithType(tp)( SC.GenericEntry(ign |> toExpr, cols map toExpr : _*) )
      case WhileSymbol =>
        val Args(cond, body: sc.Block[Any @unchecked])::Nil = argss
        blockWithType(tp)(SC.While(toBlock(cond).asInstanceOf[sc.Block[Boolean]] , toBlock(body).asInstanceOf[sc.Block[Unit]]))
      case StrCmpSymbol =>
        val Args(s1, s2)::Nil = argss
        blockWithType(tp)(SC.StringExtra.StringCompare(toExpr(s1).asInstanceOf[sc.Rep[String]], toExpr(s2).asInstanceOf[sc.Rep[String]]))
      case StrPrintfSymbol =>
        val ArgsVarargs(Args(s, f), Args(varargs @ _*)) :: Nil = argss
        blockWithType(tp)(SC.StringExtra.StringPrintf(toExpr(s).asInstanceOf[sc.Rep[Int]], toExpr(f).asInstanceOf[sc.Rep[String]], varargs map toExpr : _*))
      case _ => super.methodApp(self, mtd, targs, argss, tp)
    }
  }
  
  val base: Sqd.type = Sqd

  Sqd.ab = AutoBinder(SC, Sqd) // this is going to generate a big binding structure; it's in a separate class/file so it's not always recomputed and recompiled!

}

