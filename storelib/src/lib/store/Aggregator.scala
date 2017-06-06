package ddbt.lib.store

import ddbt.lib.store.Entry

import scala.collection.mutable.ArrayBuffer

/**
  * Created by sachin on 21.03.16.
  */
trait Aggregator[E <: Entry] extends (E => Unit) {
  def apply(e: E): Unit //TODO: Have a pure functional version

  def result: E

  def resultForUpdate: E
}

object Aggregator {
  def min[E <: Entry, R](f: E => R)(implicit order: Ordering[R]): Aggregator[E] = new MinAggregator[E, R](f)

  def max[E <: Entry, R](f: E => R)(implicit order: Ordering[R]): Aggregator[E] = new MaxAggregator[E, R](f)

  def median[E <: Entry, R](f: E => R)(implicit order: Ordering[R]): Aggregator[E] = new MedianAggregator[E, R](f)
}

class MinAggregator[E <: Entry, R](val f: E => R)(implicit order: Ordering[R]) extends Aggregator[E] {
  var minRes: R = 0.asInstanceOf[R]
  var minEntry: E = null.asInstanceOf[E]
  var first = true

  override def apply(e: E): Unit = if (first) {
    minRes = f(e)
    minEntry = e
    first = false
  } else if (order.compare(minRes, f(e)) > 0) {
    minRes = f(e)
    minEntry = e
  }

  override def result: E = minEntry

  override def resultForUpdate: E = ???
}

class MaxAggregator[E <: Entry, R](val f: E => R)(implicit order: Ordering[R]) extends Aggregator[E] {
  var maxRes: R = 0.asInstanceOf[R]
  var maxEntry: E = null.asInstanceOf[E]
  var first = true

  override def apply(e: E): Unit = if (first) {
    maxRes = f(e)
    maxEntry = e
    first = false
  } else if (order.compare(maxRes, f(e)) < 0) {
    maxRes = f(e)
    maxEntry = e
  }

  override def resultForUpdate: E = ???

  override def result: E = maxEntry
}

class MedianAggregator[E <: Entry, R](val f: E => R)(implicit order: Ordering[R]) extends Aggregator[E] {
  val results = ArrayBuffer[E]()

  override def apply(e: E): Unit = results.append(e)

  override def resultForUpdate: E = ???

  override def result: E = {
    val s = results.size
    var i = s / 2
    if (s % 2 == 0)
      i -= 1
    results.sortBy(f)(order)(i)
  }
}


