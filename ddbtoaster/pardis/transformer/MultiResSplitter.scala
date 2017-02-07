package ddbt.transformer

import ch.epfl.data.sc.pardis.utils.TypeUtils._
import ddbt.lib.store.deep._
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.types.UnitType
import ddbt.codegen.Optimizer

class MultiResSplitter(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  rewrite += rule {
    case IdxSlice(self, key, f) =>
      val res = self.sliceRes(key)
      __ifThenElse(res.isEmpty, unit(), self.sliceResMap(key, f, res))(UnitType)
    case IdxForeach(self, f) =>
      val res = self.foreachRes()
      __ifThenElse(res.isEmpty, unit(), self.foreachResMap(f, res))(UnitType)
  }
}
