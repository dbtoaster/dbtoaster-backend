package lib.storeScala

abstract class MultiRes {
  def isEmpty(): Boolean
}

class SliceRes[E <: Entry](val sliceHead: IdxHashEntry[E]) extends MultiRes {
  override def isEmpty(): Boolean = sliceHead == null
}

class ForEachRes[E <: Entry](val head: E) extends MultiRes {
  override def isEmpty(): Boolean = false  //TODO: Fix later
}
