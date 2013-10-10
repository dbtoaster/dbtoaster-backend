package ddbt.test.perf;
import java.util.*;
import java.io.*;
//import scala.Function1;
//import scala.Function2;
interface Function1<T1,R> {  public R apply(T1 _1); }
interface Function2<T1,T2,R> {  public R apply(T1 _1, T2 _2); }

/** A M3Map is a HashMap with O(1) slicing operation (extracting a partition). */
interface M3Map<K,V> {
  public V get(K key);             // returns the value or zero if it is not present
  public void set(K key, V value); // inserts or set the value
  public void add(K key, V value); // combines new value with existing one using 'plus'
  //public void op(K key Function1<V,V> f); // generalized element modification
  public void foreach(Function2<K,V,scala.Unit> f); // iterates through all non-zero values of the map
  public M3Map<K,V> slice(int index, Object subKey); // returns the map partition where the key part is equal to subKey
  //public M3Map<K,V> slice(int part, Object subKey, K low, K high, boolean lowIn, boolean highIn);
  public void clear();             // erases all elements of the map or slice
  public int size();               // returns the number of key-value mappings in the map
  public void sum(M3Map<K,V> acc); // accumulate in acc: acc <- element_sum (this,acc)
  // public scala.collection.Map<K,V> toMap(); // returns the map content
  // public scala.List<scala.xml.Elem> toXML(); // returns the map content as XML
}

/** Basic map without secondary indices. */
@SuppressWarnings("unchecked")
class M3MapBase<K,V> implements M3Map<K,V>, Cloneable, Serializable {
  private static final int INITIAL_CAPACITY = 1024;
  private static final int MAXIMUM_CAPACITY = 1 << 30;
  private static final float LOAD_FACTOR = 0.75f;
  private transient Entry<K,V>[] data;
  private transient int size;
  private transient int threshold;
  private transient final V zero;
  private transient final Plus<V> plus; // inferred from zero
  private transient boolean skipZero = false;
  private transient final Index<?>[] indices;

  public M3MapBase() { this((V)new Long(0L),false,null); }
  public M3MapBase(V zero, boolean skipZero, Function1<K,?>[] projections) {
    threshold = (int)(INITIAL_CAPACITY * LOAD_FACTOR);
    data = new Entry[INITIAL_CAPACITY];
    this.zero=zero; this.skipZero = skipZero;
    if (projections==null) indices=null;
    else {
      indices = (Index<?>[])java.lang.reflect.Array.newInstance(Index.class, projections.length);
      for(int i=0;i<projections.length;++i) indices[i] = new Index(projections[i]);
    }
    if (zero instanceof Long) plus = (Plus<V>) new Plus<Long>() { Long apply(Long a, Long b) { return a+b; } };
    else if (zero instanceof Double) plus = (Plus<V>) new Plus<Double>() { Double apply(Double a, Double b) { return a+b; } };
    else if (zero instanceof String) plus = (Plus<V>) new Plus<String>() { String apply(String a, String b) { return a+b; } };
    else if (zero instanceof Date) plus = (Plus<V>) new Plus<Date>() { Date apply(Date a, Date b) { return new Date(a.getTime()+b.getTime()); } };
    else plus=null;
  }

  private abstract class Plus<T> { abstract T apply(T a, T b); }
  private static class Entry<K,V> implements Comparable<Entry> {
    private final int hash;
    public final K key;
    public V value;
    private Entry<K,V> next;
    private Entry(int h, K k, V v, Entry<K,V> n) { hash=h; key=k; value=v; next=n; }
    public boolean equals(Entry that) { return hash==that.hash && key.equals(that.key); }
    public int compareTo(Entry that) { return (key instanceof Comparable<?>) ? ((Comparable<K>)key).compareTo((K)that.key) : 0; }
  }

  private static final int hash(Object k) { int h = k.hashCode(); h^=(h>>>20)^(h>>>12); return h^(h>>>7)^(h>>>4); }
  private static final int indexFor(int h, int length) { return h & (length-1); }
  private final Entry<K,V> find(K key) { int h=hash(key); for(Entry<K,V> e:data) for(;e!=null;e=e.next) { if (h==e.hash && key.equals(e.key)) return e; } return null; }
  private void resize(int newCapacity) { if (data.length==MAXIMUM_CAPACITY) { threshold=Integer.MAX_VALUE; return; }
    Entry[] newData = new Entry[newCapacity];
    for (Entry<K,V> e:data) while(null!=e) { Entry<K,V> next=e.next; int i = indexFor(e.hash, newCapacity); e.next=newData[i]; newData[i]=e; e=next; }
    data = newData; threshold = (int)Math.min(newCapacity * LOAD_FACTOR, MAXIMUM_CAPACITY + 1);
  }
  private void createEntry(int hash, K key, V value, int bucketIndex) {
    Entry<K,V> e = new Entry<K,V>(hash, key, value, data[bucketIndex]); data[bucketIndex]=e; ++size;
    if (indices!=null) { for (Index<?> i : indices) i.add(e); }
  }
  private void putNoResize(K key, V value) {
    int h=hash(key); int i=indexFor(h,data.length);
    for (Entry<K,V> e=data[i]; e!=null; e=e.next) if (h==e.hash && key.equals(e.key)) { e.value = value; return; }
    createEntry(h, key, value, i);
  }

  // Traditional Map interface
  public int size() { return size; }
  public V get(K key) { Entry<K,V> e=find(key); return e==null ? null : e.value; }
  public void put(K key, V value) {
    int h = hash(key); int b = indexFor(h, data.length);
    for(Entry<K,V> e=data[b];e!=null;e=e.next) if (h==e.hash && key.equals(e.key)) { e.value=value; return; }
    if ((size >= threshold) && (data[b]!=null)) { resize(2*data.length); h=hash(key); b=indexFor(h,data.length); }
    createEntry(h,key,value,b);
  }
  public V remove(K key) {
    int h=hash(key); int b=indexFor(h, data.length);
    Entry<K,V> prev=data[b],e=prev;
    while (e!=null) {
      Entry<K,V> next=e.next;
      if (h==e.hash && key.equals(e.key)) {
        if (prev==e) data[b]=next; else prev.next=next; size--;
        if (indices!=null) { for (Index<?> i : indices) i.del(e); }
        return e.value;
      }
      prev=e; e=next;
    }
    return null;
  }
  
  // M3Map interface
  public void set(K key, V value) { if (skipZero && value.equals(zero)) remove(key); else put(key,value); }
  public void add(K key, V value) { if (skipZero && value.equals(zero)) return; Entry<K,V> e=find(key);
    if (e==null) put(key,value); else { e.value=plus.apply(e.value,value); if (skipZero && e.value.equals(zero)) remove(key); }
  }
  public M3Map<K,V> slice(int index, Object subKey) { return new Slice(indices[index].slice(subKey)); }
  public void sum(M3Map<K,V> acc) { for(Entry<K,V> e:data) for(;e!=null;e=e.next) acc.add(e.key,e.value); }
  public void clear() { for (int i=0;i<data.length;++i) data[i]=null; size=0; }
  public void foreach(Function2<K,V,scala.Unit> f) { for(Entry<K,V> e:data) for(;e!=null;e=e.next) { f.apply(e.key,e.value); } }

  public String toString() {
    StringBuilder sb=new StringBuilder();
    Entry[] l=(Entry[])new Object[size]; int i=0; for(Entry<K,V> e:data) for(;e!=null;e=e.next) { l[i]=e; ++i; }
    java.util.Arrays.sort(l); for(Entry e:l) { sb.append(e.key.toString()+" -> "+e.value.toString()+"\n"); }
    sb.setLength(sb.length()-1); return sb.toString();
  }

  // Serialization IGNORE INDICES as the main purpose is only to transfer efficiently
  // A more efficient serialization should however be adopted:
  // - http://code.google.com/p/fast-serialization/
  // - http://code.google.com/p/kryo/
  private static final long serialVersionUID = 631812653624988207L;
  private void writeObject(java.io.ObjectOutputStream s) throws IOException {
    s.defaultWriteObject(); s.writeInt(size);
    if (size>0) for(Entry<K,V> e:data) for(;e!=null;e=e.next) { s.writeObject(e.key); s.writeObject(e.value); }
  }
  private void readObject(java.io.ObjectInputStream s) throws IOException, ClassNotFoundException {
    s.defaultReadObject(); int num=s.readInt();
    int initialCapacity = (int) Math.min(num * Math.min(1 / LOAD_FACTOR, 4.0f), MAXIMUM_CAPACITY);
    int capacity=1; while (capacity<initialCapacity) { capacity <<= 1; }
    data = new Entry[capacity]; threshold=(int) Math.min(capacity * LOAD_FACTOR, MAXIMUM_CAPACITY + 1);
    for (int i=0;i<num;++i) { K key=(K) s.readObject(); V value=(V) s.readObject(); putNoResize(key, value); }
  }

  public Object clone() {
    Function1<K,?>[] ps=null;
    if (indices!=null) { ps=(Function1[])java.lang.reflect.Array.newInstance(Function1.class, indices.length);
      for (int i=0;i<indices.length;++i) ps[i] = indices[i].proj;
    }
    M3MapBase<K,V> result=new M3MapBase<K,V>(zero, skipZero, ps);
    result.data=new Entry[data.length]; result.threshold=threshold; // fast insertion
    for(Entry<K,V> e:data) for(;e!=null;e=e.next) { result.putNoResize(e.key,e.value); } return result;
  }

  /** A slice behaves mostly like the original map but only on its partition. */
  class Slice implements M3Map<K,V> {
    private final Set<Entry<K,V>> data;
    Slice(Set<Entry<K,V>> set) { data=set; }
    // Faked operations (to be better implemented)
    public void set(K key, V value) { M3MapBase.this.set(key,value); }
    public void add(K key, V value) { M3MapBase.this.add(key,value); }
    public M3Map<K,V> slice(int index, Object subKey) { return this; }
    // Slice-specific operations
    public V get(K key) { Entry<K,V> e=M3MapBase.this.find(key); if (e!=null && !data.contains(e)) e=null; return e!=null ? e.value : null; }
    public int size() { return data.size(); }
    public void clear() { for(Entry<K,V> e : data) M3MapBase.this.remove(e.key); }
    public void foreach(Function2<K,V,scala.Unit> f) { for(Entry<K,V> e : data) f.apply(e.key,e.value); }
    public void sum(M3Map<K,V> acc) { for(Entry<K,V> e : data) acc.add(e.key,e.value); }
  }

  /** Secondary index storage for slicing. Matching elements are stored in a Hash or a Tree. */
  class Index<P> {
    private final Function1<K,P> proj;        // 1st level (might map all at the same place)
    private final Comparator<Entry<K,V>> cmp; // 2nd level (hash or tree structure)
    private HashMap<P,Set<Entry<K,V>>> data;
    Index(Function1<K,P> projection) { this(projection,null); }
    Index(Function1<K,P> projection, Comparator<K> comparator) { proj=projection;
      final Comparator<K> c = comparator!=null ? comparator : ((projection instanceof Comparator<?>) ? (Comparator<K>)projection : null);
      cmp = c==null ? null : new Comparator<Entry<K,V>>() { public int compare(Entry<K,V> e1, Entry<K,V> e2) { return c.compare(e1.key,e2.key); } };
      data = new HashMap<P,Set<Entry<K,V>>>();
    }
    void add(Entry<K,V> e) { P p=proj.apply(e.key); Set<Entry<K,V>> s=data.get(p); if (s==null) s=cmp==null ? new HashSet<Entry<K,V>>() : new TreeSet<Entry<K,V>>(cmp); s.add(e); }
    void del(Entry<K,V> e) { P p=proj.apply(e.key); Set<Entry<K,V>> s=data.get(p); s.remove(e); if (s.size()==0) data.remove(p); }
    Set<Entry<K,V>> slice(Object part) { Set<Entry<K,V>> s=data.get((P)part); if (s==null) s=new HashSet<Entry<K,V>>(); return s; }
    Set<Entry<K,V>> slice(Object part, K low, K high, boolean lowIn, boolean highIn) { // assert(cmp!=null);
      TreeSet<Entry<K,V>> s=(TreeSet<Entry<K,V>>)data.get((P)part); Entry<K,V> l = new Entry<K,V>(0,low,zero,null); Entry<K,V> h = new Entry<K,V>(0,high,zero,null);
      if (s==null) s=new TreeSet<Entry<K,V>>(); return s.subSet(l, lowIn, h, highIn);
    }
  }
}

/*
Improvement in synthetic test:
Add       : 0.195390 -> 0.205076 = -5%
Clear     : 0.000761 -> 0.000791 
Aggr      : 0.016639 -> 0.014383 = 13%
Update    : 0.037031 -> 0.029665 = 20%
Update2   : 0.329532 -> 0.289414 = 12%
*/

//class Key { long _1,_2; String _3; Key(long l1_, long l2_, String s3_) { _1=l1_; _2=l2_; _3=s3_; } }
//class Val { double _1,_2; Val(double d1_, double d2_) { _1=d1_; _2=d2_; } }
class M3Perf {
  static final int N = 1000000;

  static long t() { return System.nanoTime(); }
  static void time(String n, long[] t) {
    java.util.Arrays.sort(t); long t0=t[3]; long us=t0/1000; // little bias towards minimum due to warm-up
    System.out.printf("%-10s: %d.%06d\n",n,us/1000000,us%1000000);
  }

  static M3MapBase<Key,Val> map = new M3MapBase<Key,Val>();
  static M3MapBase<Key,Val> map2 = new M3MapBase<Key,Val>();

  static void load() {
    for (long i=0;i<N;++i) {
      Key k = new Key(i,i+1,"Hello world");
      Val v = new Val(i*3.0,i*4.0);
      map.put(k,v);
    }
  }

  static double acc=0;
  static int z=0;

  @SuppressWarnings("unchecked")
  public static void main(String[] args) {
    // 1. Add/clear
    long[] t_add=new long[10];
    long[] t_clear= new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      load();
      long t1=t();
      map.clear();
      long t2=t();
      t_add[z]=t1-t0;
      t_clear[z]=t2-t1;
    }
    time("Add",t_add);
    time("Clear",t_clear);

    load();
    System.gc();

    // 2. Loop/aggregate
    long[] t_aggr=new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      map.foreach(new Function2<Key,Val,scala.Unit>() {
        public scala.Unit apply(Key k1, Val v1) {
          M3Perf.acc += v1._1*2.0+v1._2*0.5;
          return null;
        }
      });
      long t1=t();
      t_aggr[z]=t1-t0;
    }
    time("Aggr",t_aggr);
    System.gc();
    
    // 3. Loop update
    long[] t_updt=new long[10];
    for (int z=0;z<10;++z) {
      long t0=t();
      map.foreach(new Function2<Key,Val,scala.Unit>() {
        public scala.Unit apply(Key k1, Val v1) {
          Val v2 = new Val(v1._1*2.0,v1._2*0.5);
          map.put(k1,v2);
          return null;
        }
      });
      long t1=t();
      t_updt[z]=t1-t0;
    }
    time("Update",t_updt);
    System.gc();
    
    // 4. Loop add/delete
    long[] t_up2=new long[10];
    for (z=0;z<10;++z) {
      long t0=t();

      (z%2==0? map : map2).foreach(new Function2<Key,Val,scala.Unit>() {
        public scala.Unit apply(Key k1, Val v1) {
          Val v2 = new Val(v1._1*2.0,v1._2*0.5);
          Key k2 = new Key(k1._1-3,k1._2+3,"Hello world2");
          (z%2==0 ? map2 : map).put(k2,v2);
          (z%2==0? map : map2).remove(k1);
          return null;
        }
      });
      long t1=t();
      t_up2[z]=t1-t0;
    }
    time("Update2",t_up2);
  }
}

/*
class Serial {
  public static void main(String[] args) throws IOException, ClassNotFoundException {
    M3Map<int,int> o = null;
    M3Map<Integer,Integer> o = new M3Map<Integer,Integer>();
    o.a=2;
    o.b=3;
    o.c=4;
	    
	PipedOutputStream os = new PipedOutputStream();
    BufferedInputStream is = new BufferedInputStream(new PipedInputStream(os));
    ObjectOutputStream oos = new ObjectOutputStream(os);
    ObjectInputStream ois = new ObjectInputStream(is);
    
    oos.writeObject(o);
    o = (M3Map<Integer,Integer>)ois.readObject();
    
    System.out.println(o.a);
    System.out.println(o.b);
  }
}
*/
