package ddbt.transformer
import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.StoreDSL
/**
  * Created by sachin on 21/12/16.
  */
class TmpMapHoister(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR){

  import IR._
  val tmpMaps = collection.mutable.HashMap[Sym[_], ConstructorDef[Store[_]]]()

}
