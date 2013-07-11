package ddbt.lib
import scala.collection.immutable.HashMap

import spark.SparkContext
import spark.RDD
import SparkContext._
import scala.reflect.ClassTag


// Distributed map based on RDD of immutable K3Map
// Is there an issue with updating another element in the loop ?

// It seems that accessing external elements in Spark closure doesn't work
// XXX: implement feedback to master for all modifications ?
// XXX: make sure it is this problem

class KDMap[K,V:ClassTag](v0:V, partitions:Int, var rdd:RDD[(Any=>Boolean,KSMap[K,V])]) {
  // New operations

  // Issue with this approach is that tmp size must be relatively small to fit in memory
  type TMap = scala.collection.mutable.HashMap[K,V]
  def parOp[K2,V2](in:KDMap[K2,V2], sl:(Int,Any), f:(K2,V2)=>(K,V), add:Boolean=true) = {
    val tmp = in.rdd.aggregate(new scala.collection.mutable.HashMap[K,V]())(
      (r:TMap,x:(Any=>Boolean,KSMap[K2,V2])) => { (if (sl==null || sl._1<0) x._2 else x._2.slice(sl._1,sl._2)).foreach { case (k,v) => r + f(k,v) }; r },
      (r1:TMap,r2:TMap) => r1 ++ r2
    )
    rdd = rdd.map { case (h,m0) => var m=m0; tmp.foreach{ case (k,v) => if (h(k)) m=if (add) m.add(k,v) else m.set(k,v) }; (h,m) }
  }
  // TPCH-Q18-specific
  def clear() { rdd = rdd.map { case (h,m) => (h,m.empty) } }
  
  


  //def h(k:Any):Int = { val x = k.hashCode % partitions; if (x<0) x+partitions else x}
  // def contains(key:K) = false
  // def get(key:K) = null

  def get(k:K):V = {
    val z = v0
    rdd.aggregate[V](z)(
    (v1:V,p:(Any=>Boolean,KSMap[K,V]))=>if (v1!=v0) v1 else p._2.get(k),
    (v1:V,v2:V)=>if (v1!=v0) v1 else v2
  )}
  
  def set(k:K,v:V) { rdd = rdd.map{ case (h,m) => if (h(k)) (h,m.set(k,v)) else (h,m) } }
  def add(k:K,v:V) { rdd = rdd.map{ case (h,m) => if (h(k)) (h,m.add(k,v)) else (h,m) } }

  // XXX: get rid of functions below (?)
  def foreach(f:(K,V)=>Unit) { rdd.foreach{ case (h,m)=>m.foreach(f) } }
  def slice[P](part:Int, partKey:P) = new KDMap[K,V](v0,partitions,rdd.map{ case (h,m) => (h,m.slice(part,partKey)) })
  def collect(f:(K,V)=>Unit) { rdd.collect.foreach{ case (h,m)=> m.foreach(f) } }
  def toXML() = {
    var m = scala.collection.immutable.Map[K,V]()
    collect{case (k,v) => m = m+((k,v))}
    K3Map.toXML(m)
  }
}

object KDMap {
  def make[K,V:ClassTag](sc:SparkContext, partitions:Int=64, v0:V, projs:List[K=>_]=Nil) : KDMap[K,V] = {
    def idx[P](f:K=>P) = new KSIndex[P,K,V](f)
    def h(n:Int) = (o:Any) => (o.hashCode+n)%partitions == 0
    new KDMap[K,V](v0, partitions, sc.makeRDD((0 until partitions).map{x=>(h(x),new KSMap(v0,projs.map(idx(_))))},partitions))
  }
}

// This is very similar to K3 map but with Scala immutable maps
// This structure is intended to be used internally by SMap
class KSMap[K,V](v0:V,idxs:List[KSIndex[_,K,V]]=Nil) extends java.io.Serializable {
  val elems = HashMap[K,V]()
  def plus(v1:V,v2:V) = (v1,v2) match { // manual type conversion required
    case (n1:Long,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Long,n2:Double) => (n1+n2).toLong.asInstanceOf[V]
    case (n1:Double,n2:Long) => (n1+n2).asInstanceOf[V]
    case (n1:Double,n2:Double) => (n1+n2).asInstanceOf[V]
    case _ => throw new Exception("No addition property")
  }
  // Public interface
  // def contains(key:K) = elems.contains(key)
  def get(key:K) = elems.get(key) match { case None => v0 case Some(v)=>v }
  def set(key:K, value:V) : KSMap[K,V] = { val el0=elems; new KSMap[K,V](v0,idxs.map{ x=>x.set(key,value) }) { override val elems=el0+((key,value)) } }
  def add(key:K, value:V) : KSMap[K,V] = if (value==v0) this else elems.get(key) match {
    case None => set(key,value)
    case Some(vv) => val v1=plus(vv,value); if (v1!=v0) set(key,v1)
      else { val el0=elems; new KSMap[K,V](v0,idxs.map{ x=>x.del(key) }) { override val elems = el0 - key } }
  }
  def foreach(f:(K,V)=>Unit) = elems.foreach{ case (k,v)=>f(k,v) } 
  def slice[P](part:Int, partKey:P):KSMap[K,V] = {
    val ix=idxs(part); new KSSlice(elems,ix.asInstanceOf[KSIndex[P,K,V]].slice(partKey)) // type information P is erased anyway
  }
  class KSSlice(elems:HashMap[K,V], slice:HashMap[K,V]) extends KSMap[K,V](v0,idxs) {
    override def foreach(f:(K,V)=>Unit) = slice.foreach{ case (k,v)=>f(k,v) } 
  }
  // Debug
  def size = elems.size
  def dump = elems
  
  def empty : KSMap[K,V] = { val el0=elems.empty; new KSMap[K,V](v0,idxs.map{ x=>x.empty }) { override val elems = el0 } }
}

class KSIndex[P,K,V](proj:K=>P) extends java.io.Serializable {
  val idx = HashMap[P,HashMap[K,V]]()
  def set(key:K,value:V) = {
    val p=proj(key); val idx0=idx
    idx.get(p) match {
      case Some(m) => new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, m + ((key,value)))) }
      case None => new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, HashMap(((key,value))))) }
    }
  }
  def del(key:K) = {
    val p=proj(key);
    idx.get(p) match {
      case Some(m) => m.get(key) match {
        case Some(v) => val idx0=idx; new KSIndex[P,K,V](proj) { override val idx = idx0 + ((p, ((m - key)))) }
        case None => this
      }
      case None => this
    }
  }
  def slice(part:P):HashMap[K,V] = idx.get(part) match { case Some(m) => m case None => HashMap[K,V]() }
  
  def empty = { val idx0=idx.empty; new KSIndex[P,K,V](proj) { override val idx = idx0 } }
}
