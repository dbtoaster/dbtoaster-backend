package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{pure, deep, reflect}

/**
  * Created by sachin on 22.04.16.
  */
@deep
@reflect[BooleanExtra]
trait MirrorBooleanExtra

object MirrorBooleanExtra {
  @pure
  def conditional[T](cond: Boolean, ift: T, iff: T): T = ???
}