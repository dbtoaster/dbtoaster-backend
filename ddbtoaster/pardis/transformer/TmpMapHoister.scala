package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 21/12/16.
  */
class TmpMapHoister(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  val tmpArrays = collection.mutable.HashSet[Sym[_]]()
  val tmpMaps = collection.mutable.HashMap[Sym[_], collection.mutable.ArrayBuffer[Sym[_]]]()
  var globalMaps: List[Sym[_]] = null
  analysis += statement {
    case sym -> (StoreNew3(_, ops: Sym[_])) if !globalMaps.contains(sym) => tmpMaps += (sym -> collection.mutable.ArrayBuffer[Sym[_]]()); tmpArrays += ops; ()
    case sym -> (i@StoreIndex(self: Sym[_], _, _, _, _)) if tmpMaps.contains(self) =>  tmpMaps(self) += sym; ()
  }
  rewrite += statement {
    case sym -> (s: StoreNew3[_]) if tmpMaps.contains(sym) => storeClear(sym.asInstanceOf[Rep[Store[ddbt.lib.store.Entry]]])(s.typeE.asInstanceOf[TypeRep[ddbt.lib.store.Entry]]); sym
    case sym -> (StoreIndex(self: Sym[_], _, _, _, _)) if tmpMaps.contains(self) => sym
    case sym -> (ArrayApplyObject(_)) if tmpArrays contains (sym) => sym
  }


}
