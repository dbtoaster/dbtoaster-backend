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
