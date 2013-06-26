package ddbt.tests
import ddbt.lib._
import org.scalatest._

// This is the generic interface but as we have only one inheriting class,
// we ignore it in the K3Map implementation.
trait K3Collection[K,V] {
  def contains(key:K):Boolean
  def get(key:K):V
  def set(key:K,value:V):Unit
  def add(key:K,value:V):Unit
  def foreach(f:(K,V)=>Unit):Unit
  def slice[P](part:Int, partKey:P):K3Collection[K,V]
}

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

// Maintains only keys in secondary indices. This is actually slower than
// maintaining full map for types (Long,Long),Long and 2 secondary indices !!!
// Also it is expected that values lookup will be much slower.
case class K3Map1[K,V](v0:V,idxs:List[K3Index1[_,K]]=Nil) extends K3Collection[K,V] {
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
  def add(key:K) { val p=proj(key); if (!idx.containsKey(p)) idx.put(p,new java.util.HashSet[K]()); idx.get(p).add(key) }
  def del(key:K) { val p=proj(key); idx.get(p).remove(key); if (idx.get(p).size==0) idx.remove(p) }
  def slice(part:P) = idx.get(part) match { case null => Set[K]() case s=>scala.collection.JavaConversions.asScalaSet[K](s) }
}

// Run this test with:
// sbt 'test:run-main ddbt.tests.MapsPerf'
object MapsPerf extends FunSpec {
  val N = 10000; // insertions
  val K = 10000; // foreach mapping
  val S = 7; // number of samples

  def main(args:Array[String]) {
    println("Estimating running time for (Long,Long) => Long")
    println("- "+N+" random insertions")
    println("- "+K+"x2 slicing/enumerations (first and second subkeys)")
    println("- median of "+S+" samples")
    
    val m = sMap(K3Map.createIdx[(Long,Long),Long](0,List(0,1)))
    println("==> K3Map  : %6d".format(m)+"ms (current)")

    val m2 = sColl(new K3Map2[Long,Long,Long](0))
    println("==> K3Map2 : %6d".format(m2)+"ms (recursive map)")

    val m2first = sColl(new K3Map2[Long,Long,Long](0),List(0,0))
    println("==> K3Map2 : %6d".format(m2first)+"ms (recursive map, first index only)")

    val m1 = sColl(new K3Map1[(Long,Long),Long](0,List(
                   K3Index1((x:(Long,Long))=>{x._1}) , K3Index1((x:(Long,Long))=>{x._2}) )))
    println("==> K3Map1 : %6d".format(m1)+"ms (sets for secondary indices)")

    val j = jMap(new java.util.HashMap[(Long,Long),Long]())
    println("==> Java HashMap : "+j+"ms") 
  }

  def r = (1000*Math.random).toLong
  def time(f:()=>Unit):Long = (0 until S).map{ x=> val t0=System.currentTimeMillis; f(); val t=System.currentTimeMillis()-t0; System.gc; t }.sorted.apply(S/2)

  def jMap(m:java.util.HashMap[(Long,Long),Long]) = time{()=> var i:Long=0
    i=0; while(i<N) { m.put((r,r),r); m.put((r,r),r); m.remove((r,r)); i=i+1; }
    i=0; while(i<2*K) { val z=r; scala.collection.JavaConversions.mapAsScalaMap[(Long,Long),Long](m).filter{case (x,y)=>x==z}.foreach(k=>()); i=i+1 }
  }
  def sMap(m:K3Map[(Long,Long),Long],l:List[Int]=List(0,1)) = time{()=> var i:Long=0
    while (i<N) { m.add((r,r),r); m.add((r,r),r); m.set((r,r),r); i=i+1; }
    l.foreach{s=> i=0; while(i<K) { m.slice(0,r).foreach( (k,v)=>()); i=i+1 } }
  }
  def sColl(m:K3Collection[(Long,Long),Long],l:List[Int]=List(0,1)) = time{()=> var i:Long=0
    while (i<N) { m.add((r,r),r); m.add((r,r),r); m.set((r,r),r); i=i+1; }
    l.foreach{s=> i=0; while(i<K) { m.slice(s,r).foreach( (k,v)=>()); i=i+1 } }
  }
}

/*
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

