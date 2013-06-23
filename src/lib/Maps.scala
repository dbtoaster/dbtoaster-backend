package ddbt.lib

/**
 * K3Var encapsulates a mutable variable.
 * Specialization [@specialized(Long,Double) T] does not seem to help
 */
case class K3Var[V](v0:V) {
  var v=v0
  def get = v
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
  private def plus(v1:V,v2:V) = v1 match {
    case v:Long => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
    case v:Double => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
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
  // To be removed by LMS  
  // def groupFold[K2,V2](group:((K,V))=>K2, f:((K,V)=>V2):K3IntermediateMap[K,V]
  // def fold[@Specialized(Long,Double) T](f:((K,V),T)=>T):T
}

// Helpers to simplify map creation
object K3Map {
  // Example: val map = K3Map.create[(Long,Long),Long](0,List[((Long,Long))=>_]((x:(Long,Long))=>{x._1},(x:(Long,Long))=>{x._2}))
  def create[K,V](v0:V,projs:List[K=>_]) = {
    def idx[P](f:K=>P) = new K3Index[P,K,V](f)
    new K3Map(v0,projs.map(idx(_)))
  }
  // Example: val map = K3Map.createIdx[(Long,Long),Long](0,List(1,2))
  def createIdx[K<:Product,V](v0:V,projs:List[Int]) = {
    def idx(i:Int) = new K3Index[Any,K,V]((k:K)=>k.productElement(i))
    new K3Map(v0,projs.map(idx(_)))
  }
}

// Secondary index (partitions the K3Map with a key projection function)
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













/*
trait K3Collection[K,V] {
  def contains(key:K):Boolean
  def get(key:K):V
  def set(key:K,value:V):Unit
  def add(key:K,value:V):Unit
  def foreach(f:(K,V)=>Unit):Unit
  def slice[P](part:Int, partKey:P):K3Collection[K,V]
}

// -----------------------------------------------------------------------------
// Specialized version for Tuple2 keys with indices on 1st and 2nd key
// Performance is heavily degraded whenever it comes to slicing on the 2nd key

class K3Map2[K1,K2,V](v0:V) extends K3Collection[(K1,K2),V] {
  private val elems = new java.util.HashMap[K1,java.util.HashMap[K2,V]]
  private def plus(v1:V,v2:V) = v1 match {
    case v:Long => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
    case v:Double => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
    case _ => throw new Exception("No addition property")
  }
  // Public interface
  def contains(key:(K1,K2)) = { val p1=elems.get(key._1); p1!=null && p1.containsKey(key._2) }
  def get(key:(K1,K2)) = elems.get(key._1) match { case null=>v0 case p=>p.get(key._2) match { case null=>v0 case v=>v } }
  def set(key:(K1,K2), value:V) { val k1=key._1
    if (!elems.containsKey(k1)) elems.put(k1,new java.util.HashMap[K2,V])
    elems.get(k1).put(key._2,value);
  }
  def add(key:(K1,K2), value:V) = {
    val k1=key._1; val k2=key._2
    if (!elems.containsKey(k1)) elems.put(k1,new java.util.HashMap[K2,V])
    val p=elems.get(k1)
    p.get(k2) match {
      case null => if (value!=v0) p.put(k2,value);
      case v => val v1=plus(v,value); if (v1!=v0) p.put(k2,v1); else { p.remove(key); if (p.size==0) elems.remove(k1); }
    }
  }
  def foreach(f:((K1,K2),V)=>Unit) = {
    scala.collection.JavaConversions.mapAsScalaMap[K1,java.util.HashMap[K2,V]](elems).foreach{ case (k1,m)=>
      scala.collection.JavaConversions.mapAsScalaMap[K2,V](m).foreach{ case (k2,v)=> f((k1,k2),v) }
    }
  }
  def slice[P](part:Int, partKey:P):K3Collection[(K1,K2),V] = {
    if (part==0) new Slice1(partKey.asInstanceOf[K1],elems)
    else if (part==1) new Slice2(partKey.asInstanceOf[K2],elems)
    else sys.error("Bad part")
  }
  class Slice1(k1:K1,elems:java.util.HashMap[K1,java.util.HashMap[K2,V]]) extends K3Map2[K1,K2,V](v0) {
    override def foreach(f:((K1,K2),V)=>Unit) = { val m=elems.get(k1);
      if (m!=null) scala.collection.JavaConversions.mapAsScalaMap[K2,V](m).foreach { case (k2,v)=>f((k1,k2),v) } 
    }
  }
  class Slice2(k2:K2,elems:java.util.HashMap[K1,java.util.HashMap[K2,V]]) extends K3Map2[K1,K2,V](v0) {
    override def foreach(f:((K1,K2),V)=>Unit) = {
      scala.collection.JavaConversions.mapAsScalaMap[K1,java.util.HashMap[K2,V]](elems).foreach {
        case (k1,m)=> val v=m.get(k2); if (v!=null) f((k1,k2),v)
      } 
    }
  }
}

object K3Perf {
  def r = (1000*Math.random).toLong
  def jMap(n:Long,k:Long) {
    val m = new java.util.HashMap[(Long,Long),Long]()
    var i:Long = 0; val t0=System.currentTimeMillis
    while (i<n) { m.put((r,r),r); m.put((r,r),r); m.remove((r,r)); i=i+1; }
    i=0; while(i<k) { scala.collection.JavaConversions.mapAsScalaMap[(Long,Long),Long](m).foreach(k=>()); i=i+1 }
    println("Hash time: "+(System.currentTimeMillis-t0)+"ms")
  }
  def sMap(n:Long,k:Long,m:K3Collection[(Long,Long),Long],name:String) {
    var i:Long = 0; val t0=System.currentTimeMillis
    while (i<n) { m.add((r,r),r); m.add((r,r),r); m.set((r,r),r); i=i+1; }
    i=0; while(i<k) { m.slice(0,r).foreach( (k,v)=>()); i=i+1 } // Slice 0
    //i=0; while(i<k) { m.slice(1,r).foreach( (k,v)=>()); i=i+1 } // Slice 1
    println(name+" time: "+(System.currentTimeMillis-t0)+"ms")
  }
  def main(args:Array[String]) {
    for (i<-0 to 10) {
      val n = 10000; // insertions
      val k = 10000; // foreach mapping
      //jMap(n,k); System.gc
      val m = K3Map.create[(Long,Long),Long](0,List[((Long,Long))=>_]((x:(Long,Long))=>{x._1},(x:(Long,Long))=>{x._2}))
      sMap(n,k,m,"K3Map"); System.gc
      val m2 = new K3Map2[Long,Long,Long](0)
      sMap(n,k,m2,"K3Map2"); System.gc
    }
  }
}
*/

/*
object K3Perf {
  def r = (10000*Math.random).toLong
  def mMap1(n:Long):Long = {
    val m = K3Map1[(Long,Long),Long](0,K3Index1((x:(Long,Long))=>{x._1}) :: K3Index1((x:(Long,Long))=>{x._2}) :: Nil)
    var i:Long = 0; val t0=System.currentTimeMillis
    while (i<n) { m.add((r,r),r); m.add((r,r),r); m.set((r,r),r); i=i+1; }
    val t=System.currentTimeMillis-t0; println("MMap1("+ix.size+") Time: "+t+"ms"); t
  }
  def mMap(n:Long):Long = {
    val m = K3Map[(Long,Long),Long](0,K3Index[Long,(Long,Long),Long]((x:(Long,Long))=>{x._1}) :: K3Index[Long,(Long,Long),Long]((x:(Long,Long))=>{x._2}) :: Nil)
    var i:Long = 0; val t0=System.currentTimeMillis
    while (i<n) { m.add((r,r),r); m.add((r,r),r); m.set((r,r),r); i=i+1; }
    val t=System.currentTimeMillis-t0; println("MMap2("+ix.size+") Time: "+t+"ms"); t
  }
  def main(args:Array[String]) {
    var l1:List[Long]=Nil
    var l2:List[Long]=Nil
    for (i<-0 to 20) {
      val n = 100000;
      l1=mMap1(n)::l1; System.gc
      l2=mMap2(n)::l2; System.gc
    }
    l1 = l1.sorted; println("Map1 time: "+l1(l1.size/2))
    l2 = l2.sorted; println("Map2 time: "+l2(l2.size/2))
  }
}

// IMPLEMENTATION 1:
// Maintain only Keys in secondary indices
// This is actually slower than maintaining full map for types (Long,Long),Long and 2 secondary indices

case class K3Map1[K,V](v0:V,idxs:List[K3Index1[_,K]]=Nil) {
  val elems = new java.util.HashMap[K,V]
  def contains(key: K) = elems.containsKey(key)
  def get(key: K) = elems.get(key) match { case null=>v0 case v=>v }
  def set(key:K, value:V) {
    if (idxs!=Nil && !elems.containsKey(key)) idxs.foreach(_.add(key))
    elems.put(key,value)
  }
  def add(key:K, value:V) = elems.get(key) match {
    case null => if (value!=v0) { elems.put(key,value); if (idxs!=Nil) idxs.foreach(_.add(key)) }
    case v => val v1=plus(v,value); if (v1!=v0) elems.put(key,v1); else { elems.remove(key); if (idxs!=Nil) idxs.foreach(_.del(key)) }
  }
  def plus(v1:V,v2:V) = v1 match {
    case v:Long => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
    case v:Double => (v+v2.asInstanceOf[Long]).asInstanceOf[V]
    case _ => throw new Exception("No addition property")
  }
  def foreach(f:(K,V)=>Unit) = scala.collection.JavaConversions.mapAsScalaMap[K,V](elems).foreach{ case (k,v)=>f(k,v) } 

  // a slice share its state(elems,idxs) with the parent, only foreach differs
  class K3Slice(elems:java.util.HashMap[K,V], slice:scala.collection.Set[K]) extends K3Map1[K,V](v0,idxs) {
    override def foreach(f:(K,V)=>Unit) = slice.foreach{ case k =>f(k,elems.get(k)) } 
  }

  def slice[P](part:Int, partKey:P):K3Map1[K,V] = {
    val ix=idxs(part); if (!ix.isInstanceOf[K3Index1[P,K]]) sys.error("slicing value mismatch")
    new K3Slice(elems,ix.asInstanceOf[K3Index1[P,K]].slice(partKey))
  }
}

case class K3Index1[P,K](proj:K=>P) {
  val idx = new java.util.HashMap[P,java.util.HashSet[K]]()
  def add(key:K) {
    val p=proj(key)
    if (!idx.containsKey(p)) idx.put(p,new java.util.HashSet[K]())
    idx.get(p).add(key)
  }
  def del(key:K) { 
    val p=proj(key)
    idx.get(p).remove(key)
    if (idx.get(p).size==0) idx.remove(p)
  }
  def slice(part:P) = idx.get(part) match { case null => Set[K]() case s=>scala.collection.JavaConversions.asScalaSet[K](s) }
}
*/

/*
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import xml._
import java.util.Date
import java.text.SimpleDateFormat

package org.dbtoaster.dbtoasterlib {
      / **
       * Generates an XML representation of the collection (similar to
       * the C++ backend) which is mostly used for debugging purposes
       *
       * @return The XML representing the collection
       * /
      def toXML(): List[Elem] = {
        toIterable().foldLeft(List[Elem]()) {
          case (l, (k, v)) =>
            (try {
              val keyXML: List[xml.Elem] = (
                k.asInstanceOf[Product].productIterator.foldLeft(
                        (0, List[xml.Elem]())) { 
                    case ((i, l), k) => 
                        (i + 1, <xml>{ valToStr(k) }</xml>.copy(
                            label = ("__a" + i)) :: l) 
                    })._2
              <item> { keyXML.reverse } <__av>{ valToStr(v) }</__av></item>
            } catch {
              case e: java.lang.ClassCastException => 
                <item><__a0>{ valToStr(k) }</__a0>
                <__av>{ valToStr(v) }</__av></item>
            }) :: l
        }
      }
    }
*/
