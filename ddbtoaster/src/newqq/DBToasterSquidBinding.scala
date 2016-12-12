package ddbt.newqq

import ddbt.lib.store.deep.StoreDSL
import squid.scback._
import squid.utils._

class DBToasterSquidBinding[SC <: StoreDSL](val SC: SC) {

  object Sqd extends AutoboundPardisIR[SC.type](SC) with PardisBinding.DefaultRedirections[SC.type] {
    
    protected val GEApplySymbol = loadMtdSymbol(loadTypSymbol("ddbt.lib.store.GenericEntry$"), "apply", None)
    
    /** Manual deep bindings for when the AutoBinder did not generate one. */
    override def methodApp(self: Rep, mtd: MtdSymbol, targs: List[TypeRep], argss: List[ArgList], tp: TypeRep): Rep = mtd match {
        
      case GEApplySymbol =>
        val ArgsVarargs(Args(ign),Args(cols @ _*)) :: Nil = argss
        blockWithType(tp)( SC.GenericEntry(ign |> toExpr, cols map toExpr : _*) )
        
      case _ => super.methodApp(self, mtd, targs, argss, tp)
    }
  }
  
  val base: Sqd.type = Sqd

  Sqd.ab = AutoBinder(SC, Sqd) // this is going to generate a big binding structure; it's in a separate class/file so it's not always recomputed and recompiled!

}

