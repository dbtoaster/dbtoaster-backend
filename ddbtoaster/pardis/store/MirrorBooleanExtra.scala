package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{pure, deep}

/**
  * Created by sachin on 22.04.16.
  */
@deep
trait BooleanExtra

object BooleanExtra {
  @pure
  def conditional[T](cond: Boolean, ift: T, iff: T): T = ???
}