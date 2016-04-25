package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{read, write, reflect, deep}

/**
  * Created by khayyam on 4/13/15.
  */

@deep
@reflect[GenericEntry]
class MirrorGenericEntry {
  @write
  def update(i: Int, v: Any): Unit = ???

  def increase(i: Int, v: Any): Unit = ???

  def +=(i: Int, v: Any): Unit = ???

  def decrease(i: Int, v: Any): Unit = ???

  def -=(i: Int, v: Any): Unit = ???

  @read
  def get[E](i: Int): E = ???


  //  def copy:Entry = ???
}

object MirrorGenericEntry {
  def apply(ignore: Any, elems: Any*): MirrorGenericEntry = ???
}