package ddbt.lib.store
import ch.epfl.data.sc.pardis.annotations.{reflect, deep}

/**
 * Created by khayyam on 4/13/15.
 */

@deep
@reflect[GenericEntry]
class MirrorGenericEntry {
  def update(i: Int, v:Any): Unit = ???
  def increase(i: Int, v:Any): Unit = ???
  def +=(i: Int, v:Any): Unit = ???
  def decrease(i: Int, v:Any): Unit = ???
  def -=(i: Int, v:Any): Unit = ???
  def get[E](i: Int): E = ???
  def cmp(e: GenericEntry): Int = ???
//  def copy:Entry = ???
}

object MirrorGenericEntry {
  def apply(ignore: Any, elems: Any*): MirrorGenericEntry = ???
}