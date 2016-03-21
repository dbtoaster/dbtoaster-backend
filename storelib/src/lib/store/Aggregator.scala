package ddbt.lib.store

import ddbt.lib.store.Entry

import scala.collection.mutable.ArrayBuffer

/**
  * Created by sachin on 21.03.16.
  */
trait Aggregator[E <: Entry] extends (E => Unit) {
  def apply(e: E): Unit

  def result: E
}

object Aggregator {

  def minBy[E <: Entry](st: Store[E], idx: Int,  col: Int) = new Aggregator[E] {
    val res = ArrayBuffer[E]()
    val ops = st.

    override def apply(e: E): Unit = res += e

    override def result: E = res.reduceLeft((r, e) => if (ops.compare(r, e) < 0) r else e)
  }
  def maxBy[E <: Entry](col: Int) = new Aggregator[E] {
    val res = ArrayBuffer[E]()
    val ops = new GenericOps(List(), col)

    override def apply(e: E): Unit = res += e

    override def result: E = res.reduceLeft((r, e) => if (ops.compare(r, e) > 0) r else e)
  }

}