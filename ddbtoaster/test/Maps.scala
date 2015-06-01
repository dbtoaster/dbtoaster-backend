package ddbt.test
import ddbt.lib._
import org.scalatest._
import scala.reflect.ClassTag

// Testing the special case: (Long,Double) -> Long
// Specialized key
case class Key(_1:Long, _2:Double) extends Ordered[Key] {
  def compare(k:Key) = if (_1<k._1) -1 else if (_1>k._1) 1 else if (_2<k._2) -1 else if (_2>k._2) 1 else 0;
}

class Maps extends FunSpec {
  import java.io._
  def toB[T](obj:T) = {
    val bos=new ByteArrayOutputStream(); val out=new ObjectOutputStream(bos)
    out.writeObject(obj); val bytes=bos.toByteArray; out.close; bos.close; bytes
  }
  def fromB[T](bytes:Array[Byte]):T = {
    val bis=new ByteArrayInputStream(bytes); val in=new ObjectInputStream(bis)
    val obj=in.readObject(); bis.close; in.close; obj.asInstanceOf[T]
  }
  def srlz[T](obj:T) = fromB[T](toB(obj))

  describe("M3Maps") {
    val mm = M3Map.make[Key,Long]((k:Key)=>k._1,(k:Key)=>k._2)
    mm.set(Key(3L,4.0),8L); assert(mm.get(Key(3L,4.0))==8L)
    mm.set(Key(7L,2.0),5L); assert(mm.get(Key(7L,2.0))==5L)
    var a=0L;
    a=0; mm.foreach((k,v)=>a+=v); assert(a==13);
    a=0; mm.slice(0,3L).foreach((k,v)=>a+=v); assert(a==8L);
    a=0; mm.slice(1,2.0).foreach((k,v)=>a+=v); assert(a==5L);
    assert(mm.size==2); mm.clear; assert(mm.size==0)
    for (i <- 0 until 5; j <- 0 until 5) yield { mm.add(Key(i,j),1); mm.add(Key(j,i),-1) }; assert(mm.size==0)
    for (i <- 0 until 5; j <- 0 until 5) yield { mm.add(Key(i,j),1); mm.add(Key(j,i),1) }; assert(mm.size==25)
    a=0; mm.foreach((k,v)=>a+=v); assert(a==50);
    val m2=M3Map.make[Key,Long](); mm.sum(m2); assert(m2.size==25)
    a=0; m2.foreach((k,v)=>a+=v); assert(a==50);
    // Serialization and conversion
    assert(srlz(mm).toMap==mm.toMap)
    val m1=M3Map.temp[(Long,Long),Long](); m1.add((3,3),0); m1.add((3,5),1); m1.add((3,1),1)
    assert(srlz(m1).toMap==m1.toMap)
    println(srlz(m1))
    info("Passed")
  }
}

// Run this test with:
// sbt 'test:run-main ddbt.tests.MapsPerf'
object MapsPerf /*extends FunSpec*/ {
  import scala.collection.JavaConversions._
  val N = 1000000; // insertions
  val S = 25; // number of samples

  def t = System.nanoTime()
  def time(n:String, t0:Array[Long], t1:Array[Long]) { val ts=(t0 zip t1).map(x=>x._2-x._1); val us:Long=ts.sorted.apply(ts.size/2)/1000; printf("   %s:%4d.%03d",n,us/1000,us%1000); }
  def main(args:Array[String]) {
    //checks();
    //bench();
  //}

  //def bench() {
    val mj = new java.util.HashMap[Key,Long]()
    val mm = M3Map.make[Key,Long]((k:Key)=>k._1,(k:Key)=>k._2)
    val mm0 = M3Map.make[Key,Long]()
    val mk = K3Map.make[Key,Long](List[Key=>_]((k:Key)=>k._1,(k:Key)=>k._2));

    val m1 = new K3Map1[Key,Long](0L,List(new K3Index1[Long,Key]((k:Key)=>k._1),new K3Index1[Double,Key]((k:Key)=>k._2)));
    val m2 = new K3Map2[Long,Double,Long](0L)
    val mt = K3Map.temp[Key,Long]()
    val ms = new M3MapMin()

    var s=0; var i=0; var j=0; var a0:Long=0; var a1:Long=0;
    val t0 = new Array[Long](_length=S)
    val t1 = new Array[Long](_length=S)
    val t2 = new Array[Long](_length=S)

    println("Benchmarking (result in ms)")
    printf("M3Maps (new) :"); def mm_fill { var i=0; do { mm.set(Key(i/1000,i%1000),1); i+=1; } while (i<N); }
    s=0; do { t0(s)=t; i=0; do { mm.set(Key(i/1000,i%1000),i+1); i+=1 } while (i<N);
              t1(s)=t; i=0; do { mm.set(Key(i/1000,i%1000),0L);  i+=1 } while (i<N); t2(s)=t; mm.clear; System.gc; s+=1 } while (s<S); time("Set",t0,t1); time("Del",t1,t2); mm_fill
    s=0; do { t0(s)=t; i=0; do { mm.add(Key(i/1000,i%1000),i+1); i+=1 } while (i<N); t1(s)=t; s+=1 } while(s<S); time("Add",t0,t1); mm.clear; mm_fill
    s=0; do { t0(s)=t; i=0; a0=0; mm.foreach((k,v)=>a0+=v); t1(s)=t; s+=1 } while(s<S); time("Acc",t0,t1);
    s=0; do { t0(s)=t; i=0; a1=0; do { mm.slice(0,i.toLong).foreach((k,v)=>a1+=v); i+=1 } while(i<N/1000); t1(s)=t; s+=1 } while(s<S); time("SlAcc",t0,t1)
    mm.clear; System.gc; println

    printf("K3Maps (old) :"); def mk_fill { var i=0; do { mk.set(Key(i/1000,i%1000),1); i+=1; } while (i<N); }
    s=0; do { t0(s)=t; i=0; do { mk.set(Key(i/1000,i%1000),i+1); i+=1 } while (i<N);
              t1(s)=t; i=0; do { mk.set(Key(i/1000,i%1000),0L);  i+=1 } while (i<N); t2(s)=t; mk.clear; System.gc; s+=1 } while (s<S); time("Set",t0,t1); time("Del",t1,t2); mk_fill
    s=0; do { t0(s)=t; i=0; do { mk.add(Key(i/1000,i%1000),i+1); i+=1 } while (i<N); t1(s)=t; s+=1 } while(s<S); time("Add",t0,t1); mk.clear; mk_fill
    s=0; do { t0(s)=t; i=0; a0=0; mk.foreach((k,v)=>a0+=v); t1(s)=t; s+=1 } while(s<S); time("Acc",t0,t1);
    s=0; do { t0(s)=t; i=0; a1=0; do { mk.slice(0,i.toLong).foreach((k,v)=>a1+=v); i+=1 } while(i<N/1000); t1(s)=t; s+=1 } while(s<S); time("SlAcc",t0,t1)
    mk.clear; System.gc; println()

    printf("M3Maps noidx :"); def mm0_fill { var i=0; do { mm0.set(Key(i/1000,i%1000),1); i+=1; } while (i<N); }
    s=0; do { t0(s)=t; i=0; do { mm0.set(Key(i/1000,i%1000),i+1); i+=1 } while (i<N);
              t1(s)=t; i=0; do { mm0.set(Key(i/1000,i%1000),0L);  i+=1 } while (i<N); t2(s)=t; mm0.clear; System.gc; s+=1 } while (s<S); time("Set",t0,t1); time("Del",t1,t2); mm0_fill
    s=0; do { t0(s)=t; i=0; do { mm0.add(Key(i/1000,i%1000),i+1); i+=1 } while (i<N); t1(s)=t; s+=1 } while(s<S); time("Add",t0,t1); mm0.clear; mm0_fill
    s=0; do { t0(s)=t; i=0; a0=0; mm0.foreach((k,v)=>a0+=v); t1(s)=t; s+=1 } while(s<S); time("Acc",t0,t1);
    mm0.clear; System.gc; println

    printf("Java HashMaps:"); def mj_fill { var i=0; do { mj.put(Key(i/1000,i%1000),i+1); i+=1; } while (i<N); }
    s=0; do { t0(s)=t; i=0; do { mj.put(Key(i/1000,i%1000),i+1); i+=1 } while (i<N);
              t1(s)=t; i=0; do { mj.remove(Key(i/1000,i%1000));  i+=1 } while (i<N); t2(s)=t; mj.clear; System.gc; s+=1 } while (s<S); time("Set",t0,t1); time("Del",t1,t2); mj_fill
    s=0; do { t0(s)=t; i=0; do { val k=Key(i/1000,i%1000); val p=mj.get(k); mj.put(k,p+i+1); i+=1 } while (i<N); t1(s)=t; s+=1 } while(s<S); time("Add",t0,t1); mj.clear; mj_fill
    s=0; do { t0(s)=t; i=0; a0=0; mj.foreach(kv=>a0+=kv._2); t1(s)=t; s+=1 } while(s<S); time("Acc",t0,t1);
    mj.clear; System.gc; println

    printf("Scala special:"); def ms_fill { var i=0; do { ms.put(Key(i/1000,i%1000),i+1); i+=1; } while (i<N); }
    s=0; do { t0(s)=t; i=0; do { ms.put(Key(i/1000,i%1000),i+1); i+=1 } while (i<N);
              t1(s)=t; i=0; do { ms.remove(Key(i/1000,i%1000));  i+=1 } while (i<N); t2(s)=t; ms.clear; System.gc; s+=1 } while (s<S); time("Set",t0,t1); time("Del",t1,t2); ms_fill
    s=0; do { t0(s)=t; i=0; do { ms.add(Key(i/1000,i%1000),i+1); i+=1 } while (i<N); t1(s)=t; s+=1 } while(s<S); time("Add",t0,t1); ms.clear; ms_fill
    s=0; do { t0(s)=t; i=0; a0=0; ms.foreach((k,v)=>a0+=v.toLong); t1(s)=t; s+=1 } while(s<S); time("Acc",t0,t1);
    ms.clear; System.gc; println
  }
}

// -----------------------------------------------------------------------------

/*
Possible way towards Java specialization:
abstract class M3E<K,V> {
  protected int hash;
  abstract public K key();
  abstract public V value();
  M3E<K,V> next;
}

class M3EII extends M3E<Integer,Integer> {
  public Integer key() { return 0; }
  public Integer value() { return 0; }
  M3EII next;
}

@SuppressWarnings("unchecked")
abstract class M3T<K,V,E extends M3E> {
  E[] data;
  M3T(Class<E> cls) {
    data = (E[])java.lang.reflect.Array.newInstance(cls,5);
    for (int i=0;i<5;++i) data[i]=e();
    System.out.println(data[2].key());
  }
  abstract E e();
}

class M3TII extends M3T<Integer,Integer,M3EII> {
  M3TII() { super(M3EII.class); }
  M3EII e() { return new M3EII(); }
}
*/


// Scala specialized
abstract class M3Entry[K,@specialized(Long,Double) V] {
  def hash:Int
  def key:K
  var value:V
  var next:M3Entry[K,V]
}

abstract class M3MapBase2[K,@specialized(Long,Double) V,E<:M3Entry[K,V]:ClassTag] {
  private final val INITIAL_CAPACITY = 1024;
  private final val MAXIMUM_CAPACITY = 1 << 30;
  private final val LOAD_FACTOR = 0.75f;
  protected var data = new Array[E](INITIAL_CAPACITY);
  private var num = 0;
  private var threshold:Int = (INITIAL_CAPACITY * LOAD_FACTOR).toInt;
  private final def hash(k:Any):Int = { var h=k.hashCode(); h^=(h>>>20)^(h>>>12); h^(h>>>7)^(h>>>4); }
  private final def indexFor(h:Int,length:Int):Int = h & (length-1)
  protected final def find(key:K):E = {
    val h=hash(key); val b=indexFor(h,data.length); var e:M3Entry[K,V]=data(b);
    if (e!=null) do { if (h==e.hash && key.equals(e.key)) return e.asInstanceOf[E]; e=e.next; } while (e!=null);
    null.asInstanceOf[E];
  }
  private def resize(newCapacity:Int) {
    if (data.size==MAXIMUM_CAPACITY) { threshold=Integer.MAX_VALUE; return; }; val newData=new Array[E](newCapacity); var i=0;
    do { var e:E=data(i); if (e!=null) do { val next=e.next.asInstanceOf[E]; val b=indexFor(e.hash, newCapacity); e.next=newData(b); newData(b)=e; e=next; } while(e!=null); i+=1; } while(i<data.size);
    data=newData; threshold=Math.min((newCapacity * LOAD_FACTOR).toInt, MAXIMUM_CAPACITY + 1);
  }
  private def createEntry(hash:Int,key:K,value:V,bucket:Int) { val e=newEntry(hash,key,value,data(bucket)); data(bucket)=e; num+=1; }
  private def putNoResize(key:K,value:V) { val h=hash(key); val b=indexFor(h,data.length);
    var e:E=data(b); if (e!=null) do { if (h==e.hash && key.equals(e.key)) { e.value=value; return; }; e=e.next.asInstanceOf[E]; } while (e!=null); createEntry(h,key,value,b);
  }

  // To overload
  protected def newEntry(hash:Int,key:K,value:V,next:E):E // new Entry<K,V>(hash, key, value, data[bucketIndex]);
  protected def onAdd(e:E) {}
  protected def onDel(e:E) {}

  // Minimal conventional Map interface
  def size = num;
  def clear { var i=0; do { data(i)=null.asInstanceOf[E]; i=i+1; } while(i<data.length); }
  def put(key:K, value:V) {
    var h=hash(key); var b=indexFor(h, data.length);
    var e:E = data(b); if (e!=null) do { if (h==e.hash && key.equals(e.key)) { e.value=value; return; }; e=e.next.asInstanceOf[E]; } while (e!=null)
    if ((size >= threshold) && (data(b)!=null)) { resize(2*data.length); h=hash(key); b=indexFor(h,data.length); }
    createEntry(h,key,value,b);
  }
  def remove(key:K):V = {
    val h=hash(key); val b=indexFor(h, data.length);
    var prev:E=data(b); var e=prev;
    if (e!=null) do {
      val next:E=e.next.asInstanceOf[E];
      if (h==e.hash && key.equals(e.key)) {
        if (prev==e) data(b)=next; else prev.next=next; onDel(e); num-=1; return e.value;
      }
      prev=e; e=next;
    } while(e!=null);
    return null.asInstanceOf[V];
  }
}
// Scala End

class MyE(val hash:Int, val key:Key, var value:Double, var next:MyE) extends M3Entry[Key,Double] {
  def next_=(e:M3Entry[Key,Double]) { next=e.asInstanceOf[MyE]; }
}
class M3MapMin extends M3MapBase2[Key,Double,MyE] {
  protected def newEntry(hash:Int,key:Key,value:Double,next:MyE) = new MyE(hash,key,value,next)
  def get(key:Key):Double = { val e=find(key); if (e!=null) e.value else 0.0 }
  def foreach(f:(Key,Double)=>Unit) { var b=0; do { var e=data(b); if (e!=null) do { f(e.key, e.value); e=e.next } while (e!=null); b+=1 } while (b<data.size) }
  def add(key:Key,value:Double) { if (value==0.0) return; val e=find(key); if (e==null) put(key,value); else { e.value+=value; if (e.value==0.0) remove(key); } }
  //protected def onAdd(e:MyE) {}
  //protected def onDel(e:MyE) {}
}

// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// LEGACY MAP IMPLEMENTATION

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  @@                                                                        @@
  @@  THESE CLASS ARE DEPRECATED AND WILL BE REMOVED AS SOON ALL CODE       @@
  @@  DEPENDING ON THEM IS UPDATED. PLEASE USE THE FOLLOWING CONVERSION:    @@
  @@                                                                        @@
  @@  K3Var->Scala var,  K3Map->M3Map.make,  K3Temp->M3Map.temp             @@
  @@                                                                        @@
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

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

