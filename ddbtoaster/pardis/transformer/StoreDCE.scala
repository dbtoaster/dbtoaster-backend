package ddbt.transformer


import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 25.04.16.
  */
class StoreDCE(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  val toRemove = collection.mutable.ArrayBuffer[Rep[_]]()
  analysis += rule {
    case EntryIdxApplyObject(h, c) => toRemove +=(h, c);()
  }
  rewrite += statement{
    case sym->st if (toRemove.contains(sym)) => ()
  }
}
