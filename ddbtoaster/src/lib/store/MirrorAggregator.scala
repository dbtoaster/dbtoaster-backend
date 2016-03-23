package ddbt.lib.store

import scala.collection.mutable.ArrayBuffer
import scala.reflect._

import ch.epfl.data.sc.pardis.annotations._

/**
  * Created by sachin on 18.03.16.
  */
@deep
trait MirrorAggregator[E <: Entry] extends (E => Unit) {
  def apply(e: E): Unit
  def result: E
}
object MirrorAggregator {
  def min[E <: Entry, R](f: E => R)(implicit order: Ordering[R]) : MirrorAggregator[E] = ???
  def max[E <: Entry, R](f: E => R)(implicit order: Ordering[R]) : MirrorAggregator[E] = ???
}