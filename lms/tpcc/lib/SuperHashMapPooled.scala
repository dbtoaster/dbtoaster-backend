package ddbt.tpcc.lib

import SHMap._
import dbtoptimizer.Utils.ind

class SHMapPooled[K,V](initialCapacity: Int, loadFactor: Float, lfInitIndex: List[(Float,Int)], projs:Seq[(K,V)=>_]) extends SHMap[K,V](initialCapacity, loadFactor, lfInitIndex, projs) {

  def this(loadFactor: Float, initialCapacity: Int, lfInitIndex: List[(Float,Int)], projs:(K,V)=>_ *) {
    this(initialCapacity, loadFactor, lfInitIndex, projs)
  }

  def this(loadFactor: Float, initialCapacity: Int, projs:(K,V)=>_ *) {
    this(initialCapacity, loadFactor, projs.map{p => ((DEFAULT_LOAD_FACTOR, DEFAULT_INITIAL_CAPACITY))}.toList, projs)
  }

  def this(initialCapacity: Int, projs:(K,V)=>_ *) {
    this(initialCapacity, DEFAULT_LOAD_FACTOR, projs.map{p => ((DEFAULT_LOAD_FACTOR, DEFAULT_INITIAL_CAPACITY))}.toList, projs)
  }

  def this(projs:(K,V)=>_ *) {
    this(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR, projs.map{p => ((DEFAULT_LOAD_FACTOR, DEFAULT_INITIAL_CAPACITY))}.toList, projs)
  }

  val entryPool: Array[SEntry[K, V]] = new Array[SEntry[K, V]](initialCapacity)
  var entryPoolCurrIndex:Int = 0
  clearEntryPool

  def clearEntryPool:Unit = {
    var i = 0
    while(i < initialCapacity) {
      entryPool(i) = new SEntry[K, V]
      i += 1
    }
    entryPoolCurrIndex = 0
  }

  /**
   * Adds a new entry with the specified key, value and hash code to
   * the specified bucket.  It is the responsibility of this
   * method to resize the table if appropriate.
   *
   * Subclass overrides this to alter the behavior of put method.
   */
  override def addSEntry(hash: Int, key: K, value: V, bucketIndex: Int):SEntry[K, V] = {
    val tmp: SEntry[K, V] = table(bucketIndex)

    //val e = new SEntry[K, V](hash, key, value, tmp)
    val e = entryPool(entryPoolCurrIndex).setAll(hash, key, value, tmp)
    entryPool(entryPoolCurrIndex) = null.asInstanceOf[SEntry[K, V]]
    entryPoolCurrIndex += 1
    if(entryPoolCurrIndex >= initialCapacity) {
      clearEntryPool
    }

    table(bucketIndex) = e
    if (size >= threshold) resize(2 * table.length)
    size += 1
    e
  }
}
