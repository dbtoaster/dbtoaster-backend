package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{deep, pure, reflect}

@deep
@reflect[MultiRes]
class MMultiRes {
  @pure
  def isEmpty: Boolean = ???
}
