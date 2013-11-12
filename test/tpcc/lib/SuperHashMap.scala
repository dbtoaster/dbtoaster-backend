package ddbt.tpcc.lib

import SHMap._

/**
 * Super Hash Map
 *
 * Java HashMap converted to Scala and optimized for high-performance
 * execution
 *
 * @author Mohammad Dashti
 */
object SHMap {
  /**
   * Applies a supplemental hash function to a given hashCode, which
   * defends against poor quality hash functions.  This is critical
   * because SHMap uses power-of-two length hash tables, that
   * otherwise encounter collisions for hashCodes that do not differ
   * in lower bits. Note: Null keys always map to hash 0, thus index 0.
   */
  def hash(hv: Int): Int = {
    var h = hv ^ (hv >>> 20) ^ (hv >>> 12)
    return h ^ (h >>> 7) ^ (h >>> 4)
  }

  /**
   * Returns index for hash code h.
   */
  def indexFor(h: Int, length: Int): Int = {
    return h & (length - 1)
  }

  /**
   * The default initial capacity - MUST be a power of two.
   */
  final val DEFAULT_INITIAL_CAPACITY: Int = 16
  /**
   * The maximum capacity, used if a higher value is implicitly specified
   * by either of the constructors with arguments.
   * MUST be a power of two <= 1<<30.
   */
  final val MAXIMUM_CAPACITY: Int = 1 << 30
  /**
   * The load factor used when none specified in constructor.
   */
  final val DEFAULT_LOAD_FACTOR: Float = 0.75f

  /**
   * Default value for inner SHMap in SHSet
   */
  val DEFAULT_PRESENT_VALUE: Boolean = true
}

class SEntry[K,V](final val hash: Int, final val key: K, var value: V, var next: SEntry[K, V]) {

  def getKey: K = {
    return key
  }

  def getValue: V = {
    return value
  }

  def setValue(newValue: V): V = {
    val oldValue: V = value
    value = newValue
    return oldValue
  }

  override def equals(o: Any): Boolean = {
    if (!(o.isInstanceOf[SEntry[K, V]])) return false
    val e: SEntry[K, V] = o.asInstanceOf[SEntry[K, V]]
    val k1: K = getKey
    val k2: K = e.getKey
    if (k1 == k2) {
      val v1: V = getValue
      val v2: V = e.getValue
      if (v1 == v2) return true
    }
    return false
  }

  override def hashCode: Int = getKey.hashCode

  override def toString: String = {
    return "(" + getKey + " -> " + getValue + ")"
  }
}

class SHMap[K,V](initialCapacity: Int, val loadFactor: Float,projs:Seq[(K,V)=>_]) {
  /**
   * Constructs an empty <tt>SHMap</tt> with the specified initial
   * capacity and load factor.
   *
   * @param  initialCapacity the initial capacity
   * @param  loadFactor      the load factor
   * @throws IllegalArgumentException if the initial capacity is negative
   *                                  or the load factor is nonpositive
   */
  // def this(initialCapacity: Int, lf: Float) {
  //   this()
  //   if (initialCapacity < 0) throw new RuntimeException("Illegal initial capacity: " + initialCapacity)
  //   var capacity: Int = 1
  //   if (initialCapacity > MAXIMUM_CAPACITY) {
  //     capacity = MAXIMUM_CAPACITY
  //   } else {
  //     while (capacity < initialCapacity) capacity <<= 1
  //   }
  //   if (lf <= 0 /*|| Float.isNaN(lf)*/) throw new RuntimeException("Illegal load factor: " + lf)
  //   loadFactor = lf
  //   threshold = (capacity * lf).asInstanceOf[Int]
  //   table = new Array[SEntry[K, V]](capacity)
  // }

  /**
   * Constructs an empty <tt>SHMap</tt> with the specified initial
   * capacity and the default load factor (0.75).
   *
   * @param  initialCapacity the initial capacity.
   * @throws IllegalArgumentException if the initial capacity is negative.
   */
  // def this(initialCapacity: Int) {
  //   this(initialCapacity, DEFAULT_LOAD_FACTOR)
  // }

  def this(loadFactor: Float, initialCapacity: Int, projs:(K,V)=>_ *) {
    this(initialCapacity, loadFactor, projs)
  }

  def this(initialCapacity: Int, projs:(K,V)=>_ *) {
    this(initialCapacity, DEFAULT_LOAD_FACTOR, projs)
  }

  def this(projs:(K,V)=>_ *) {
    this(DEFAULT_INITIAL_CAPACITY, DEFAULT_LOAD_FACTOR, projs)
  }

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
  def isEmpty: Boolean = (size == 0)

  /**
   * Returns the value to which the specified key is mapped,
   * or {@code null} if this map contains no mapping for the key.
   *
   * <p>More formally, if this map contains a mapping from a key
   * {@code k} to a value {@code v} such that {@code (key==null ? k==null :
     * key.equals(k))}, then this method returns {@code v}; otherwise
   * it returns {@code null}.  (There can be at most one such mapping.)
   *
   * <p>A return value of {@code null} does not <i>necessarily</i>
   * indicate that the map contains no mapping for the key; it's also
   * possible that the map explicitly maps the key to {@code null}.
   * The {@link #contains contains} operation may be used to
   * distinguish these two cases.
   *
   * @see #put(Object, Object)
   */
  def apply(key: K): V = {
    // if (key == null) return getForNullKey
    val hs: Int = hash(key.hashCode)
    var e: SEntry[K, V] = table(indexFor(hs, table.length))
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) return e.value
      e = e.next
    }
    throw new java.util.NoSuchElementException
  }
  // def get(key: K): V = apply(key)
  def getEntry(key: K): SEntry[K,V] = {
    // if (key == null) return getForNullKey
    val hs: Int = hash(key.hashCode)
    var e: SEntry[K, V] = table(indexFor(hs, table.length))
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) return e
      e = e.next
    }
    throw new java.util.NoSuchElementException
  }
  def getNullOnNotFound(key: K): V = {
    // if (key == null) return getForNullKey
    val hs: Int = hash(key.hashCode)
    var e: SEntry[K, V] = table(indexFor(hs, table.length))
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) return e.value
      e = e.next
    }
    null.asInstanceOf[V]
  }

  /**
   * Offloaded version of get() to look up null keys.  Null keys map
   * to index 0.  This null case is split out into separate methods
   * for the sake of performance in the two most commonly used
   * operations (get and put), but incorporated with conditionals in
   * others.
   */
  private def getForNullKey: V = {
    var e: SEntry[K, V] = table(0)
    while (e != null) {
      if (e.key == null) return e.value
      e = e.next
    }
    null.asInstanceOf[V]
  }

  /**
   * Returns <tt>true</tt> if this map contains a mapping for the
   * specified key.
   *
   * @param   key   The key whose presence in this map is to be tested
   * @return <tt>true</tt> if this map contains a mapping for the specified
   *         key.
   */
  def contains(key: K): Boolean = (getSEntry(key) != null)

  /**
   * Returns the entry associated with the specified key in the
   * SHMap.  Returns null if the SHMap contains no mapping
   * for the key.
   */
  def getSEntry(key: K): SEntry[K, V] = {
    val hs: Int = /*if ((key == null)) 0 else*/ hash(key.hashCode)
    var e: SEntry[K, V] = table(indexFor(hs, table.length))
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) return e
      e = e.next
    }
    null.asInstanceOf[SEntry[K, V]]
  }

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
  def put(key: K, value: V): V = {
    // if (key == null) return putForNullKey(value)
    val hs: Int = hash(key.hashCode)
    val i: Int = indexFor(hs, table.length)
    var e: SEntry[K, V] = table(i)
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) {
        val oldValue: V = e.value
        e.value = value
        if (idxs != Nil) idxs.foreach{ idx => {
            val pOld = idx.proj(k,oldValue)
            val pNew = idx.proj(k,value)
            if(pNew != pOld) {
              idx.del(e, oldValue)
              idx.set(e)
            }
          }
        }
        return oldValue
      }
      e = e.next
    }
    e = addSEntry(hs, key, value, i)
    if (idxs!=Nil) idxs.foreach(_.set(e))
    null.asInstanceOf[V]
  }

  def +=(key: K, value: V): V = put(key, value)

  def +=(kv: (K, V)): V = put(kv._1, kv._2)

  def updateVal(key: K, value: V): V = put(key, value)

  def update(key: K, valueUpdateFunc: V=>V): V = {
    // if (key == null) return putForNullKey(value)
    val hs: Int = hash(key.hashCode)
    val i: Int = indexFor(hs, table.length)
    var e: SEntry[K, V] = table(i)
    while (e != null) {
      val k: K = e.key
      if (e.hash == hs && key == k) {
        val oldValue: V = e.value
        val value:V = valueUpdateFunc(oldValue)
        e.value = value
        if (idxs != Nil) idxs.foreach{ idx => {
            val pOld = idx.proj(k,oldValue)
            val pNew = idx.proj(k,value)
            if(pNew != pOld) {
              idx.del(e, oldValue)
              idx.set(e)
            }
          }
        }
        return oldValue
      }
      e = e.next
    }
    null.asInstanceOf[V]
  }

  /**
   * Offloaded version of put for null keys
   */
  // private def putForNullKey(value: V): V = {
  //   var e: SEntry[K, V] = table(0)
  //   while (e != null) {
  //     if (e.key == null) {
  //       val oldValue: V = e.value
  //       e.value = value
  //       return oldValue
  //     }
  //     e = e.next
  //   }
  //   addSEntry(0, null, value, 0)
  //   null
  // }

  /**
   * This method is used instead of put by constructors and
   * pseudoconstructors (clone, readObject).  It does not resize the table,
   * check for comodification, etc.  It calls createSEntry rather than
   * addSEntry.
   */
  // private def putForCreate(key: K, value: V):Unit {
  //   val hash: Int = if ((key == null)) 0 else hash(key.hashCode)
  //   val i: Int = indexFor(hash, table.length)
  //   {
  //     var e: SEntry[K, V] = table(i)
  //     while (e != null) {
  //       {
  //         var k: K = null
  //         if (e.hash == hash && ((({
  //           k = e.key; k
  //         })) eq key || (key != null && (key == k)))) {
  //           e.value = value
  //           return
  //         }
  //       }
  //       e = e.next
  //     }
  //   }
  //   createSEntry(hash, key, value, i)
  // }
  //
  // private def putAllForCreate(m: Nothing):Unit {
  //   import scala.collection.JavaConversions._
  //   for (e <- m.entrySet) putForCreate(e.getKey, e.getValue)
  // }

  /**
   * Rehashes the contents of this map into a new array with a
   * larger capacity.  This method is called automatically when the
   * number of keys in this map reaches its threshold.
   *
   * If current capacity is MAXIMUM_CAPACITY, this method does not
   * resize the map, but sets threshold to Integer.MAX_VALUE.
   * This has the effect of preventing future calls.
   *
   * @param newCapacity the new capacity, MUST be a power of two;
   *                    must be greater than current capacity unless current
   *                    capacity is MAXIMUM_CAPACITY (in which case value
   *                    is irrelevant).
   */
  def resize(newCapacity: Int):Unit = {
    val oldTable: Array[SEntry[K, V]] = table
    val oldCapacity: Int = oldTable.length
    if (oldCapacity == MAXIMUM_CAPACITY) {
      threshold = Integer.MAX_VALUE
      return
    }
    val newTable: Array[SEntry[K, V]] = new Array[SEntry[K, V]](newCapacity)
    transfer(newTable)
    table = newTable
    threshold = (newCapacity * loadFactor).asInstanceOf[Int]
  }

  /**
   * Transfers all entries from current table to newTable.
   */
  def transfer(newTable: Array[SEntry[K, V]]) {
    val src: Array[SEntry[K, V]] = table
    val newCapacity: Int = newTable.length
    var j: Int = 0
    while (j < src.length) {
      var e: SEntry[K, V] = src(j)
      if (e != null) {
        src(j) = null
        do {
          val next: SEntry[K, V] = e.next
          val i: Int = indexFor(e.hash, newCapacity)
          e.next = newTable(i)
          newTable(i) = e
          e = next
        } while (e != null)
      }
      j += 1
    }
  }

  /**
   * Removes the mapping for the specified key from this map if present.
   *
   * @param  key key whose mapping is to be removed from the map
   * @return the previous value associated with <tt>key</tt>, or
   *         <tt>null</tt> if there was no mapping for <tt>key</tt>.
   *         (A <tt>null</tt> return can also indicate that the map
   *         previously associated <tt>null</tt> with <tt>key</tt>.)
   */
  def remove(key: K): V = {
    val e: SEntry[K, V] = removeSEntryForKey(key)
    (if (e == null) null.asInstanceOf[V] else e.value)
  }

  def -=(key: K): V = remove(key)

  /**
   * Removes and returns the entry associated with the specified key
   * in the SHMap.  Returns null if the SHMap contains no mapping
   * for this key.
   */
  def removeSEntryForKey(key: K): SEntry[K, V] = {
    val hs: Int = /*if ((key == null)) 0 else*/ hash(key.hashCode)
    val i: Int = indexFor(hs, table.length)
    var prev: SEntry[K, V] = table(i)
    var e: SEntry[K, V] = prev
    while (e != null) {
      val next: SEntry[K, V] = e.next
      var k: K = e.key
      if (e.hash == hs && key == k) {
        if (idxs!=Nil) idxs.foreach(_.del(e))
        size -= 1
        if (prev eq e) table(i) = next
        else prev.next = next
        return e
      }
      prev = e
      e = next
    }
    e
  }

  /**
   * Special version of remove for SEntrySet.
   */
  // def removeMapping(entry: SEntry[K, V]): SEntry[K, V] = {
  //   // if (!(o.isInstanceOf[Any])) return null
  //   // val entry: SEntry[K, V] = o.asInstanceOf[SEntry[K, V]]
  //   val key: K = entry.getKey
  //   val hs: Int = /*if ((key == null)) 0 else*/ hash(key.hashCode)
  //   val i: Int = indexFor(hs, table.length)
  //   var prev: SEntry[K, V] = table(i)
  //   var e: SEntry[K, V] = prev
  //   while (e != null) {
  //     val next: SEntry[K, V] = e.next
  //     if (e.hash == hs && e == entry) {
  //       size -= 1
  //       if (prev eq e) table(i) = next
  //       else prev.next = next
  //       return e
  //     }
  //     prev = e
  //     e = next
  //   }
  //   e
  // }

  /**
   * Removes all of the mappings from this map.
   * The map will be empty after this call returns.
   */
  def clear:Unit = {
    val tab: Array[SEntry[K, V]] = table
    var i: Int = 0
    while (i < tab.length) {
      tab(i) = null
      i += 1
    }
    size = 0
    if (idxs!=Nil) idxs.foreach(_.clear)
  }

  /**
   * Returns <tt>true</tt> if this map maps one or more keys to the
   * specified value.
   *
   * @param value value whose presence in this map is to be tested
   * @return <tt>true</tt> if this map maps one or more keys to the
   *         specified value
   */
  // def containsValue(value: V): Boolean = {
  //   if (value == null) return containsNullValue
  //   val tab: Array[SEntry[K, V]] = table
  //   var i: Int = 0
  //   while (i < tab.length) {
  //     var e: SEntry[K, V] = tab(i)
  //     while (e != null) {
  //       if (value == e.value) return true
  //       e = e.next
  //     }
  //     i += 1
  //   }
  //   false
  // }

  /**
   * Special-case code for containsValue with null argument
   */
  // private def containsNullValue: Boolean = {
  //   var i: Int = 0
  //   while (i < table.length) {
  //     var e: SEntry[K, V] = table(i)
  //     while (e != null) {
  //       if (e.value == null) return true
  //       e = e.next
  //     }
  //     i += 1
  //   }
  //   false
  // }

  /**
   * Adds a new entry with the specified key, value and hash code to
   * the specified bucket.  It is the responsibility of this
   * method to resize the table if appropriate.
   *
   * Subclass overrides this to alter the behavior of put method.
   */
  def addSEntry(hash: Int, key: K, value: V, bucketIndex: Int):SEntry[K, V] = {
    val tmp: SEntry[K, V] = table(bucketIndex)
    val e = new SEntry[K, V](hash, key, value, tmp)
    table(bucketIndex) = e
    if (size >= threshold) resize(2 * table.length)
    size += 1
    e
  }

  /**
   * Like addSEntry except that this version is used when creating entries
   * as part of Map construction or "pseudo-construction" (cloning,
   * deserialization).  This version needn't worry about resizing the table.
   *
   * Subclass overrides this to alter the behavior of SHMap(Map),
   * clone, and readObject.
   */
  // def createSEntry(hash: Int, key: K, value: V, bucketIndex: Int):Unit = {
  //   val e: SEntry[K, V] = table(bucketIndex)
  //   table(bucketIndex) = new SEntry[K, V](hash, key, value, e)
  //   size += 1
  // }

  def capacity: Int = table.length

  // def loadFactor: Float = {
  //   return loadFactor
  // }

  def foreach(f: ((K, V)) => Unit): Unit = foreachEntry(e => f(e.key, e.value))

  def foreachEntry(f: SEntry[K, V] => Unit): Unit = {
    var i: Int = 0
    while (i < table.length) {
      var e: SEntry[K, V] = table(i)
      while (e != null) {
        f(e)
        e = e.next
      }
      i += 1
    }
  }

  override def toString: String = {
    var res = new StringBuilder("[")
    var first = true
    foreachEntry { e =>
      if(first) first = false
      else res.append(", ")
      res.append(e.toString)
    }
    res.append("]")
    res.toString
  }

  /**
   * The table, resized as necessary. Length MUST Always be a power of two.
   */
  var table: Array[SEntry[K, V]] = new Array[SEntry[K, V]](initialCapacity)
  /**
   * The number of key-value mappings contained in this map.
   */
  var size: Int = 0
  /**
   * The next size value at which to resize (capacity * load factor).
   * @serial
   */
  var threshold: Int = (initialCapacity * loadFactor).asInstanceOf[Int]

  //init

  val idxs:List[SIndex[_,K,V]] = {
    def idx[P](f:(K,V)=>P) = new SIndex[P,K,V](f)
    projs.toList.map(idx(_))
  }

  def slice[P](part:Int, partKey:P):SIndexEntry[K,V] = {
    val ix=idxs(part)
    ix.asInstanceOf[SIndex[P,K,V]].slice(partKey) // type information P is erased anyway
  }

  def getInfoStr:String = {
    val res = new StringBuilder("MapInfo => {\n")
    res.append("\tsize => ").append(size).append("\n")
    .append("\tcapacity => ").append(capacity).append("\n")
    .append("\tthreshold => ").append(threshold).append("\n")
    var i = 0
    var elemCount = 0
    val contentSize = new Array[Int](table.length)
    while(i < table.length) {
      var counter = 0
      var e: SEntry[K, V] = table(i)
      while(e != null) {
        counter += 1
        e = e.next
      }
      elemCount += counter
      contentSize(i) = counter
      i += 1
    }
    res.append("\telemCount => ").append(elemCount).append("\n")
    .append("\tmaxElemsInCell => ").append(contentSize.max).append("\n")
    .append("\tavgElemsInCell => ").append("%.2f".format(elemCount/(table.length).asInstanceOf[Double])).append("\n")
    //.append("\tcontentSize => ").append(java.util.Arrays.toString(contentSize)).append("\n")
    .append("}").toString
  }
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

class SIndexEntry[K,V] {
  val s:SHSet[SEntry[K,V]] = new SHSet[SEntry[K,V]]

  def foreach(f: ((K, V)) => Unit): Unit = s.foreach(e => f(e.key, e.value))

  def foreachEntry(f: SEntry[SEntry[K,V], Boolean] => Unit): Unit = s.foreachEntry(e => f(e))
}

class SIndex[P,K,V](val proj:(K,V)=>P) {
  val idx = new SHMap[P,SIndexEntry[K,V]]

  def set(entry: SEntry[K,V]):Unit = {
    val p:P = proj(entry.key, entry.value)
    val s = idx.getNullOnNotFound(p)
    if (s==null) {
      val newIdx = new SIndexEntry[K,V]
      newIdx.s.add(entry)
      idx.put(p,newIdx)
    } else {
      s.s.add(entry)
    }
  }

  def del(entry: SEntry[K,V]):Unit = del(entry, entry.value)

  def del(entry: SEntry[K,V], v:V):Unit = {
    val p:P = proj(entry.key, v)
    val s=idx.getNullOnNotFound(p)
    if (s!=null) { 
      s.s.remove(entry)
      if (s.s.size==0) idx.remove(p)
    }
  }

  def slice(part:P):SIndexEntry[K,V] = idx.getNullOnNotFound(part) match { 
    case null => new SIndexEntry[K,V]
    case s=>s
  }

  def clear:Unit = idx.clear
}
