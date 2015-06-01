package lib.store

import ddbt.lib.store._
import ch.epfl.data.sc.pardis.annotations.{reflect, noImplementation, deep}
import scala.reflect.ClassTag

/**
* Created by khayyam on 4/13/15.
*/
//@deep
//@noImplementation
//class GenericStore[E<:Entry] extends Store(1, Array(GenericEntry.asInstanceOf[EntryIdx[E]])) {
//
//  def slice(idx:String,key:E,f:E=>Unit) = if (key!=null) {
//    val fields = idx.split("_").map(_.toInt)
//    //foreach { e =>
//      //        if (e.equalsOn(fields, key))
//      //          f(e)
//    //}
//  }
//
//}
