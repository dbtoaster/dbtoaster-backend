package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{pure, deep}

/**
  * Created by sachin on 12.12.16.
  */
@deep
trait StringExtra


object StringExtra {
  @pure
  def StringCompare(str1 : String, str2 : String) : Int = str1.compareToIgnoreCase(str2)

}
