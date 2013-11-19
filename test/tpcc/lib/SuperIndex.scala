
package ddbt.tpcc.lib

import SIndex._

object SIndex {
  val EMPTY_INDEX_ENTRY = new SIndexEntry[Any,Any]
}

class SIndexEntry[K,V] {
  val s:SHSet[SEntry[K,V]] = new SHSet[SEntry[K,V]]

  def foreach(f: ((K, V)) => Unit): Unit = s.foreach(e => f(e.key, e.value))

  def foreachEntry(f: SEntry[SEntry[K,V], Boolean] => Unit): Unit = s.foreachEntry(e => f(e))
}

class SIndex[P,K,V](val proj:(K,V)=>P, loadFactor: Float, initialCapacity: Int) {

  val idx = new SHMap[P,SIndexEntry[K,V]](loadFactor, initialCapacity)

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
    case null => EMPTY_INDEX_ENTRY.asInstanceOf[SIndexEntry[K,V]]
    case s=>s
  }

  def clear:Unit = idx.clear
}
