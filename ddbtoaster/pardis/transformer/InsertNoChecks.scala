package ddbt.transformer

import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.StoreDSL
import ddbt.lib.store.deep.StoreIRs.StoreIndex

class InsertNoChecks(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {
  import IR._
    rewrite += rule{
      case StoreInsert(self, e) => self.unsafeInsert(e)
    }
}
