package ddbt.newqq

import ddbt.lib.store.deep.StoreDSL
import squid.scback._

class DBToasterSquidBinding[SC <: StoreDSL](val SC: SC) {

  object Sqd extends AutoboundPardisIR[SC.type](SC) with PardisBinding.DefaultRedirections[SC.type]
  val base: Sqd.type = Sqd

  Sqd.ab = AutoBinder(SC, Sqd) // this is going to generate a big binding structure; it's in a separate class/file so it's not always recomputed and recompiled!

}

