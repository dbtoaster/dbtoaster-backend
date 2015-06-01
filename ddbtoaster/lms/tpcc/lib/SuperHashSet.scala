package ddbt.tpcc.lib

import SHSet._

object SHSet {
  /**
   * Default value for inner SHMap in SHSet
   */
  val DEFAULT_PRESENT_VALUE: Boolean = true
}

class SHSet[K] {
  var map: SHMap[K,Boolean] = new SHMap[K,Boolean]

  // def this(initialCapacity: Int, lf: Float) {
  //   this()
  //   map = new SHMap[K,Boolean](initialCapacity, lf)
  // }

  // def this(initialCapacity: Int) {
  //   this(initialCapacity, DEFAULT_LOAD_FACTOR)
  // }

  /**
   * Initialization hook for subclasses. This method is called
   * in all constructors and pseudo-constructors (clone, readObject)
   * after SHMap has been initialized but before any entries have
   * been inserted.  (In the absence of this method, readObject would
   * require explicit knowledge of subclasses.)
   */
  // def init:Unit = {
  // }

  /**
   * Returns the number of key-value mappings in this map.
   *
   * @return the number of key-value mappings in this map
   */
  // def size: Int = size

  /**
   * Returns <tt>true</tt> if this map contains no key-value mappings.
   *
   * @return <tt>true</tt> if this map contains no key-value mappings
   */
  def isEmpty: Boolean = (map.size == 0)

  /**
   * Returns <tt>true</tt> if this map contains a mapping for the
   * specified key.
   *
   * @param   key   The key whose presence in this map is to be tested
   * @return <tt>true</tt> if this map contains a mapping for the specified
   *         key.
   */
  def contains(key: K): Boolean = map.contains(key)

  /**
   * Associates the specified value with the specified key in this map.
   * If the map previously contained a mapping for the key, the old
   * value is replaced.
   *
   * @param key key with which the specified value is to be associated
   * @param value value to be associated with the specified key
   * @return the previous value associated with <tt>key</tt>, or
   *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
   *         (A <tt>null</tt> return can also indicate that the map
   *         previously associated <tt>null</tt> with <tt>key</tt>.)
   */
  def add(key: K): Boolean = {
    val e: Boolean = map.put(key,DEFAULT_PRESENT_VALUE)
    (e == DEFAULT_PRESENT_VALUE)
  }

  def +=(key: K): Boolean = add(key)

  /**
   * Removes the mapping for the specified key from this map if present.
   *
   * @param  key key whose mapping is to be removed from the map
   * @return the previous value associated with <tt>key</tt>, or
   *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
   *         (A <tt>null</tt> return can also indicate that the map
   *         previously associated <tt>null</tt> with <tt>key</tt>.)
   */
  def remove(key: K): Boolean = {
    val e: Boolean = map.remove(key)
    (e == DEFAULT_PRESENT_VALUE)
  }

  def -=(key: K): Boolean = remove(key)

  /**
   * Removes all of the mappings from this map.
   * The map will be empty after this call returns.
   */
  def clear:Unit = map.clear

  def capacity: Int = map.table.length

  def size:Int = map.size

  // def loadFactor: Float = {
  //   return loadFactor
  // }

  def foreach(f: K => Unit): Unit = map.foreachEntry(e => f(e.key))

  def foreachEntry(f: SEntry[K, Boolean] => Unit): Unit = map.foreachEntry(e => f(e))

  override def toString: String = {
    var res = new StringBuilder("[")
    var first = true
    map.foreachEntry { e =>
      if(first) first = false
      else res.append(", ")
      res.append(e.key.toString)
    }
    res.append("]")
    res.toString
  }
}