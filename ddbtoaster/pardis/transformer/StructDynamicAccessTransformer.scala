package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.{StoreDSL, StructDynamicFieldAccess}

/**
  * Created by sachin on 23/3/17.
  */
class StructDynamicAccessTransformer(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  rewrite += rule {
    case StructDynamicFieldAccess(struct, _, Def(Int$plus2(Constant(i), v))) =>
      StructDynamicFieldAccess(struct, (i + 1).toString, v)
  }

}
