package ddbt.lib
import scala.reflect.ClassTag

/**
 * This file encloses all the logic related to internal maps being used in the
 * generated program. The main difference with regular HashMaps are:
 * - get(k) : a default 'zero' value is returned when element does not exist
 * - add(k,v) : 'add' v to previous existing value, set it to v otherwise
 * 'zero' and 'add' are defined according to the map's value type
 *
 * K3Temp behave otherwise as a regular map
 * K3Var has the same behavior but for a single value (map with 0-elements key)
 * K3Map additionally does not store 'zero'-valued elements (thus don't iterate
 * on them). Furthermore, secondary indices (key projections) can be set in K3Map
 * in order to iterate only on element contained in a single slice.
 *
 * Helpers to create these maps are found in the K3Map companion object.
 *
 * @author TCK
 */

/** K3Var encapsulates a mutable variable. */
case class K3Var[V:ClassTag]() {
  private val plus = K3Helper.make_plus[V]()
  var v = K3Helper.make_zero[V]()
  def get() = v
  def set(v1:V) { v=v1 }
  def add(v1:V) { v=plus(v,v1) }
  override def toString = v.toString
}

/** K3Map is a HashMap with O(1) slice operation. */
trait K3Map[K,V] {
  def get(key:K): V                // returns the value or zero if it is not present
  def set(key:K, value:V)          // inserts or set the value
  def add(key:K, value:V)          // combines new value with existing one using 'plus'
  def foreach(f:(K,V)=>Unit)       // iterates through all non-zero values of the map
  def aggr[R](f:(K,V)=>R)(implicit cR:ClassTag[R]):R // aggregate/sum the content of a map/slice
  def slice[P](part:Int, partKey:P):K3Map[K,V] // returns the map partition where the key part is equal to subKey
  def clear()                      // erases all elements of the map or slice
  // additional features
  def size: Int                    // returns the number of key-value mappings in the map
  def toMap: Map[K,V]              // returns the map content
  def toXML: List[xml.Elem]        // returns the map content as XML
  def toStr: String                // returns the map content as (comparable) String
}

/** An intermediate map that retains 0-multiplicity elements */
trait K3Temp[K,V] {
  def add(k:K,v:V)
  def set(k:K,v:V)
  def get(k:K):V
  def foreach(f:(K,V)=>Unit)
  def toMap:Map[K,V]
}

/** Helper object to construct maps. Examples:
 * val map1 = K3Map.makeIdx[(Long,Long),Long](0,List(0,1))
 * val map2 = K3Map.make[(Long,Long),Long](0,List[((Long,Long))=>_](
 *                       (x:(Long,Long))=>x._1, (x:(Long,Long))=>x._2) )
 */
object K3Map {
  def make[K,V:ClassTag](projs:List[K=>_]=Nil):K3Map[K,V] = {
    // XXX: switch implementation if there is only one projection or none
    def idx[P](f:K=>P) = new K3Index[P,K,V](f)
    new K3MapMult(projs.map(idx(_)))
  }
  def makeIdx[K<:Product,V:ClassTag](projs:List[Int]=Nil):K3Map[K,V] = {
    make[K,V](projs.map(i => (k:K)=>k.productElement(i)))
  }
  def temp[K,V:ClassTag]() = new K3TempImp[K,V]()
}

// -----------------------------------------------------------------------------
// Implementation

object K3Helper {
  // Implicit default 'zero' value
  def make_zero[T]()(implicit cT:ClassTag[T]) : T = (cT.toString match {
    case "Long" => 0L
    case "Double" => 0.0
    case "java.lang.String" => ""
    case _ => sys.error("No zero for "+cT)
  }).asInstanceOf[T]
  // Combinator for add function, must be idempotent if one argument is zero
  def make_plus[T]()(implicit cT:ClassTag[T]) : (T,T)=>T = (cT.toString match {
    case "Long" => (v0:Long,v1:Long)=>v0+v1
    case "Double" => (v0:Double,v1:Double)=>v0+v1
    case "java.lang.String" => (v0:String,v1:String)=>v0+v1
    case _ => sys.error("No additivity for "+cT)
  }).asInstanceOf[(T,T)=>T]
  // Convert a map into XML (for debug purposes)
  private val ft = new java.text.SimpleDateFormat("yyyyMMdd")
  private def str(v:Any) = v match {
    case p:Product => "("+(0 until p.productArity).map{x=>p.productElement(x)}.mkString(",")+")"
    case d:java.util.Date => ft.format(d)
    case x => x.toString
  }
  def toStr(o:Any):String = { if (o.isInstanceOf[Map[_,_]]) toStr(o.asInstanceOf[Map[_,_]]) else o.toString }
  def toStr[K,V](m:Map[K,V]):String = m.toList.map{case(k,v)=>(str(k),str(v))}.sortBy(x=>x._1).map{case(k,v)=>k+" -> "+v}.mkString("\n")
  def toXML[K,V](m:Map[K,V]): List[xml.Elem] = {
    var l = List[xml.Elem]()
    m.foreach{case (k,v) =>
      val key = try {
          (k.asInstanceOf[Product].productIterator.foldLeft((0,List[xml.Elem]())) {
                case ((i,l), k) => (i+1, <xml>{ str(k) }</xml>.copy(label=("__a" + i)) :: l)
          })._2.reverse
        } catch { case e:java.lang.ClassCastException => <__a0>{ str(k) }</__a0> }
      l = <item>{ key }<__av>{ str(v) }</__av></item> :: l
    }
    l.sortBy(_.toString)
  }

  // Local destructive union (Akka)
  def union[K,V:ClassTag](m1:Map[K,V],m2:Map[K,V]):K3Temp[K,V] = {
    val t=new K3TempImp[K,V]();
    m1.foreach{case (k,v)=>t.add(k,v)}
    m2.foreach{case (k,v)=>t.add(k,v)}
    t
  }
  def union[K,V:ClassTag](t1:K3Temp[K,V],m2:Map[K,V]):K3Temp[K,V] = { m2.foreach{case (k,v)=>t1.add(k,v)}; t1 }
  def union[K,V:ClassTag](m1:Map[K,V],t2:K3Temp[K,V]):K3Temp[K,V] = { m1.foreach{case (k,v)=>t2.add(k,v)}; t2 }
  def union[K,V:ClassTag](t1:K3Temp[K,V],t2:K3Temp[K,V]):K3Temp[K,V] = { t1.foreach{case (k,v)=>t2.add(k,v)}; t2 }
}

/** A regular HashMap with extra add and get-or-zero behaviors. */
class K3TempImp[K,V:ClassTag]() extends K3Temp[K,V] {
  private val v0 = K3Helper.make_zero[V]()
  private val plus = K3Helper.make_plus[V]()
  private val elems = new java.util.HashMap[K,V]
  def add(key:K,value:V) { val v=elems.get(key); elems.put(key,if (v!=null) plus(v,value) else value); }
  def set(key:K,value:V) { elems.put(key,value); }
  def get(key:K):V = { val v=elems.get(key); if (v==null) v0 else v }
  def foreach(f:(K,V)=>Unit) { scala.collection.JavaConversions.mapAsScalaMap[K,V](elems).foreach{ case (k,v)=> f(k,v) } }
  def toMap:Map[K,V] = scala.collection.JavaConversions.mapAsScalaMap[K,V](elems).toMap
};

/**
 * K3MapMult is implemented with Java HashMaps and supports an arbitrary
 * number of secondary indices for slicing.
 * - We may optimize secondary indices maintenance with LMS by deforesting K3Index
 *   In particular updating indexes and slice(x,y).foreach fusion.
 * - Cost is approximately proportional to maintaining 1+K HashMaps, where K is
 *   the number of indices on the map
 * - Micro benchmarks shows that it is faster to insert if secondary index contains
 *   duplicated (key,value) (and expected to be faster for slice access by avoiding double lookup).
 */
case class K3MapMult[K,V:ClassTag](idxs:List[K3Index[_,K,V]]=Nil) extends K3Map[K,V] {
  private val v0 = K3Helper.make_zero[V]()
  private val plus = K3Helper.make_plus[V]()
  private val elems = new java.util.HashMap[K,V]
  def get(key:K) = elems.get(key) match { case null=>v0 case v=>v }
  def set(key:K, value:V) {
    if (value==v0) { elems.remove(key); if (idxs!=Nil) idxs.foreach(_.del(key)) }
    else { elems.put(key,value); if (idxs!=Nil) idxs.foreach(_.set(key,value)) }
  }
  def add(key:K, value:V) { if (value!=v0) set(key, elems.get(key) match { case null => value case v => plus(v,value) }) }
  def foreach(f:(K,V)=>Unit) = scala.collection.JavaConversions.mapAsScalaMap[K,V](elems).foreach{ case (k,v)=>f(k,v) }
  def aggr[R](f:(K,V)=>R)(implicit cR:ClassTag[R]):R = { var r:R = K3Helper.make_zero[R](); val p = K3Helper.make_plus[R]()
    foreach{ case (k,v)=> r = p(r,f(k,v)) }; r
  }
  /*
  def group[K2,V2](f:(K,V)=>(K2,V2))(implicit cV2:ClassTag[V2]):Map[K2,V2] = {
    val res = new java.util.HashMap[K2,V2]()
    val p = K3Helper.make_plus[V2]()
    foreach { case (k,v)=> val (k2,v2)=f(k,v); val v0=res.get(k2); res.put(k2, if (v0!=null) p(v0,v2) else v2) }
    scala.collection.JavaConversions.mapAsScalaMap[K2,V2](res).toMap
  }
  */
  //def group[K2,V2](out:K3Temp[K2,V2])(f:(K,V)=>(K2,V2)) = foreach{(k,v)=>val r=f(k,v); out.add(r._1,r._2) }

  def clear() { elems.clear; if (idxs!=Nil) idxs.foreach(_.clear) }
  def slice[P](part:Int, partKey:P):K3MapMult[K,V] = {
    val ix=idxs(part); new K3Slice(elems,ix.asInstanceOf[K3Index[P,K,V]].slice(partKey)) // type information P is erased anyway
  }
  // A slice share its state(elems, idxs) with its parent.
  // Note: A slice might become incoherent if was empty at creation or if it has been emptied.
  //       This should not be a problem as no slice are maintained between operations.
  class K3Slice(elems:java.util.HashMap[K,V], slice:java.util.HashMap[K,V]) extends K3MapMult[K,V](idxs) {
    override def foreach(f:(K,V)=>Unit) = scala.collection.JavaConversions.mapAsScalaMap[K,V](slice).foreach{ case (k,v)=>f(k,v) } 
    override def clear() = foreach { case (k,v)=> elems.remove(k); idxs.foreach(_.del(k)) }
    // Debug
    override def toMap = scala.collection.JavaConversions.mapAsScalaMap(slice).toMap
    override def size = slice.size
  }

  // Debug
  def size = elems.size
  def toMap = scala.collection.JavaConversions.mapAsScalaMap(elems).toMap
  def toXML = K3Helper.toXML(toMap)
  def toStr = K3Helper.toStr(toMap)
  // def contains(key:K) = elems.containsKey(key)
}

/** Secondary index (partitions the K3Map with a key projection function) */
class K3Index[P,K,V](proj:K=>P) {
  val idx = new java.util.HashMap[P,java.util.HashMap[K,V]]()
  def set(key:K,value:V) { val p=proj(key);
    if (!idx.containsKey(p)) idx.put(p,new java.util.HashMap[K,V]())
    idx.get(p).put(key,value)
  }
  def del(key:K) { val p=proj(key); val s=idx.get(p); if (s!=null) { s.remove(key); if (s.size==0) idx.remove(p) } }
  def slice(part:P):java.util.HashMap[K,V] = idx.get(part) match { case null => new java.util.HashMap[K,V]() case s=>s }
  def clear() { idx.clear }
}
