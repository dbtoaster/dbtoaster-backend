package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations._

/**
  * Created by sachin on 18.03.16.
  */
@deep
@reflect[Aggregator[_]]
trait MirrorAggregator[E <: Entry] extends (E => Unit) {
  def apply(e: E): Unit
  def result: E
}
object MirrorAggregator {
  @pure
  def min[E <: Entry, R](f: E => R)(implicit order: Ordering[R]) : Aggregator[E] = ???
  @pure
  def max[E <: Entry, R](f: E => R)(implicit order: Ordering[R]) : Aggregator[E] = ???
}