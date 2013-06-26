package ddbt.lib

/**
 * K3Var encapsulates a mutable variable.
 * Specialization [@specialized(Long,Double) T] does not seem to help
 */
case class K3Var[V](v0:V) {
  var v=v0
  def get() = v
  def set(v1:V) { v=v1 }
  def add(v1:V) = v match {
    case v0:Long => v=(v0+v1.asInstanceOf[Long]).asInstanceOf[V]
    case v0:Double => v=(v0+v1.asInstanceOf[Double]).asInstanceOf[V]
    case _=> sys.error("Unsupported")
  }
  override def toString = v.toString
}

/**
 * A K3Map is a HashMap with O(1) slice operation.
 * - We may optimize secondary indices maintenance with LMS by deforesting K3Index
 *   In particular updating indexes and slice(x,y).foreach fusion.
 * - Cost is approximately proportional to maintaining 1+K HashMaps, where K is
 *   the number of indices on the map
 * - Micro benchmarks shows that it is faster to insert if secondary index contains
 *   value (and expected to be faster for slice access: avoids double lookup).
 */
case class K3Map[K,V](v0:V,idxs:List[K3Index[_,K,V]]=Nil) {
  private val elems = new java.util.HashMap[K,V]
  private def plus(v1:V,v2:V) = (v1,v2) match { // manual type conversion required
    case (n1:Long,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Long,n2:Double) => (n1+n2).toLong.asInstanceOf[V]
    case (n1:Double,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Double,n2:Double) => (n1+n2).asInstanceOf[V]
    case _ => throw new Exception("No addition property")
  }
  // Public interface
  def contains(key:K) = elems.containsKey(key)
  def get(key:K) = elems.get(key) match { case null=>v0 case v=>v }
  def set(key:K, value:V) { if (idxs!=Nil) idxs.foreach(_.set(key,value)); elems.put(key,value) }
  def add(key:K, value:V) = elems.get(key) match {
    case null => if (value!=v0) { elems.put(key,value); if (idxs!=Nil) idxs.foreach(_.set(key,value)) }
    case v => val v1=plus(v,value); if (v1!=v0) elems.put(key,v1); else elems.remove(key);
      if (idxs!=Nil) if (v1!=v0) idxs.foreach(_.set(key,v1)) else idxs.foreach(_.del(key))
  }
  def foreach(f:(K,V)=>Unit) = scala.collection.JavaConversions.mapAsScalaMap[K,V](elems).foreach{ case (k,v)=>f(k,v) } 
  def slice[P](part:Int, partKey:P):K3Map[K,V] = {
    val ix=idxs(part); new K3Slice(elems,ix.asInstanceOf[K3Index[P,K,V]].slice(partKey)) // type information P is erased anyway
  }
  // A slice share its state(elems,idxs) with the parent, only foreach differs
  // Note: Slice might become incoherent if was empty at creation or it has been emptied.
  //       This should not be a problem as no slice are maintained between map modifications in M3.
  class K3Slice(elems:java.util.HashMap[K,V], slice:java.util.HashMap[K,V]) extends K3Map[K,V](v0,idxs) {
    override def foreach(f:(K,V)=>Unit) = scala.collection.JavaConversions.mapAsScalaMap[K,V](slice).foreach{ case (k,v)=>f(k,v) } 
  }
  // Debug
  def size = elems.size

  // To be removed by LMS  
  // def groupFold[K2,V2](group:((K,V))=>K2, f:((K,V)=>V2):K3IntermediateMap[K,V]
  // def fold[@Specialized(Long,Double) T](f:((K,V),T)=>T):T
}

/** Helpers to simplify map creation */
object K3Map {
  /*
   * Create a map using arbitrary secondary indices.
   * Example:
   *   val map = K3Map.create[(Long,Long),Long](0,List[((Long,Long))=>_](
   *                           (x:(Long,Long))=>{x._1},
   *                           (x:(Long,Long))=>{x._2}
   *             ))
   */
  def create[K,V](v0:V,projs:List[K=>_]) = {
    def idx[P](f:K=>P) = new K3Index[P,K,V](f)
    new K3Map(v0,projs.map(idx(_)))
  }
  /*
   * Create a map using key parts as secondary indices. The parts are defined 
   * by their position in the original key
   * Example:
   *   val map = K3Map.createIdx[(Long,Long),Long](0,List(0,1))
   */
  def createIdx[K<:Product,V](v0:V,projs:List[Int]) = {
    def idx(i:Int) = new K3Index[Any,K,V]((k:K)=>k.productElement(i))
    new K3Map(v0,projs.map(idx(_)))
  }
}

/** Secondary index (partitions the K3Map with a key projection function) */
class K3Index[P,K,V](proj:K=>P) {
  val idx = new java.util.HashMap[P,java.util.HashMap[K,V]]()
  def set(key:K,value:V) {
    val p=proj(key)
    if (!idx.containsKey(p)) idx.put(p,new java.util.HashMap[K,V]())
    idx.get(p).put(key,value)
  }
  def del(key:K) { 
    val p=proj(key); val s=idx.get(p)
    if (s!=null) { s.remove(key); if (s.size==0) idx.remove(p) }
  }
  def slice(part:P):java.util.HashMap[K,V] = idx.get(part) match { case null => new java.util.HashMap[K,V]() case s=>s }
}
