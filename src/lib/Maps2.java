package ddbt.lib;
import java.util.*;
import java.io.IOException;
import java.io.Serializable;
import scala.Function1;
import scala.Function2;

/**
 * This is the low-level Java implementation of M3Maps.
 * Interfaces and usage are described in the associated Scala file.
 *
 * Observations (set, add operations):
 * - Micro benchmark are very unstable with maps, use at least 20 rounds to test.
 * - Secondary indices are more efficiently maintained by a HashTree than a HashSet
 * - Fully key+value specialized Scala allows us to gain about 8% over non-specialized
 *   but Scala performs worse than Java when non-specialized (+7% set, +23% add).
 * - Specializing the interface functions (add/set) does not improve performance.
 *
 * Implementation notes:
 * - Partial support for range indices is included in the implementation.
 * - We need functions to access min, max and range slices.
 * - We might want to provide the following extensions to the M3Maps:
 *
 *   def op(key:K, f:V=>V);      // generalized element modification
 *   def slice[T](index:Int,subKey:T, low:K,high:K,lowIn:Boolean,highIn:Boolean):M3Map[K,V];
 *   def toMap:Map[K,V];         // returns the map content
 *   def toXML:List[xml.Elem];   // returns the map content as XML
 *
 * @author TCK
 */

/** Base implementation. */
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
  protected M3MapBase<K,V> acc() { return new M3MapBase<K,V>(zero,false,null); } // accumulator for Akka

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

  private static final int hash(Object k) { int h = k.hashCode(); h^=(h>>>20)^(h>>>12)^(h<<9); return h^(h>>>7)^(h>>>4); }
  private static final int indexFor(int h, int length) { return h & (length-1); }
  private final Entry<K,V> find(K key) {
    int h=hash(key); int b=indexFor(h,data.length); Entry<K,V> e=data[b];
    if (e!=null) do { if (h==e.hash && key.equals(e.key)) return e; } while ((e=e.next)!=null); return null;
  }
  private void resize(int newCapacity) { if (data.length==MAXIMUM_CAPACITY) { threshold=Integer.MAX_VALUE; return; }
    Entry[] newData=new Entry[newCapacity]; Entry<K,V> next=null;
    for (Entry<K,V> e:data) if (e!=null) do { next=e.next; int b=indexFor(e.hash, newCapacity); e.next=newData[b]; newData[b]=e; } while((e=next)!=null);
    data=newData; threshold=(int)Math.min(newCapacity * LOAD_FACTOR, MAXIMUM_CAPACITY + 1);
  }
  private void createEntry(int hash, K key, V value, int bucketIndex) {
    Entry<K,V> e = new Entry<K,V>(hash, key, value, data[bucketIndex]); data[bucketIndex]=e; ++size;
    if (indices!=null) { for (Index<?> i:indices) i.add(e); }
  }
  private void putNoResize(K key, V value) {
    int h=hash(key); int i=indexFor(h,data.length);
    for (Entry<K,V> e=data[i]; e!=null; e=e.next) if (h==e.hash && key.equals(e.key)) { e.value = value; return; }
    createEntry(h, key, value, i);
  }

  // Minimal conventional Map interface
  public int size() { return size; }
  public void put(K key, V value) {
    int h = hash(key); int b = indexFor(h, data.length);
    for(Entry<K,V> e=data[b];e!=null;e=e.next) if (h==e.hash && key.equals(e.key)) { e.value=value; return; }
    if ((size >= threshold) && (data[b]!=null)) { resize(2*data.length); b=indexFor(h,data.length); }
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
  public V get(K key) { Entry<K,V> e=find(key); return e==null ? zero : e.value; }
  public void set(K key, V value) { if (skipZero && value.equals(zero)) remove(key); else put(key,value); }
  public void add(K key, V value) { if (skipZero && value.equals(zero)) return; Entry<K,V> e=find(key);
    if (e==null) put(key,value); else { e.value=plus.apply(e.value,value); if (skipZero && e.value.equals(zero)) remove(key); }
  }
  public M3Map<K,V> slice(int index, Object subKey) { return new Slice(indices[index].slice(subKey)); }
  public void sum(M3Map<K,V> acc) { for(Entry<K,V> e:data) for(;e!=null;e=e.next) acc.add(e.key,e.value); }
  public void clear() { for (int i=0;i<data.length;++i) data[i]=null; size=0; if (indices!=null) for(Index<?> i:indices) { i.clear(); } }
  public void foreach(Function2<K,V,scala.runtime.BoxedUnit> f) { for(Entry<K,V> e:data) for(;e!=null;e=e.next) { f.apply(e.key,e.value); } }
  public scala.collection.immutable.Map<K,V> toMap() { // XXX: is this very efficient?
    scala.collection.immutable.HashMap<K,V> m = new scala.collection.immutable.HashMap<K,V>();
    for(Entry<K,V> e:data) for(;e!=null;e=e.next) { m=m.$plus(new scala.Tuple2<K,V>(e.key,e.value)); }
    return m;
  }

  public String toString() {
    StringBuilder sb=new StringBuilder();
    Entry[] l=(Entry[])new Entry[size]; int i=0; for(Entry<K,V> e:data) for(;e!=null;e=e.next) { l[i]=e; ++i; }
    java.util.Arrays.sort(l); for(Entry e:l) { sb.append(e.key.toString()+" -> "+e.value.toString()+"\n"); }
    int len=sb.length(); if (len>0) sb.setLength(len-1); return sb.toString();
  }

  // Serialization: INDICES are IGNORED as the main purpose is only to transfer efficiently
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
  public boolean equals(Object that) {
    if (that==null || !(that instanceof M3Map)) return false;
    return toMap().equals(((M3Map<K,V>)that).toMap()); // XXX: is this very efficient?
  }

  // A slice behaves mostly like the original map but only on 1 of its partition.
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
    public void foreach(Function2<K,V,scala.runtime.BoxedUnit> f) { for(Entry<K,V> e : data) f.apply(e.key,e.value); }
    public void sum(M3Map<K,V> acc) { for(Entry<K,V> e : data) acc.add(e.key,e.value); }
    public scala.collection.immutable.Map<K,V> toMap() {
      scala.collection.immutable.HashMap<K,V> m = new scala.collection.immutable.HashMap<K,V>();
      for(Entry<K,V> e:data) m=m.$plus(new scala.Tuple2<K,V>(e.key,e.value)); return m;
    }
  }

  // Secondary index storage for slicing. Matching elements are stored in a Hash or a Tree.
  class Index<P> {
    private final Function1<K,P> proj;        // 1st level (might map all at the same place)
    private final Comparator<Entry<K,V>> cmp; // 2nd level (tree structure)
    private HashMap<P,Set<Entry<K,V>>> data;
    Index(Function1<K,P> projection) { this(projection,null); }
    Index(Function1<K,P> projection, Comparator<K> comparator) { proj=projection;
      final Comparator<K> c = comparator!=null ? comparator : ((projection instanceof Comparator<?>) ? (Comparator<K>)projection : null);
      cmp = c==null ? null : new Comparator<Entry<K,V>>() { public int compare(Entry<K,V> e1, Entry<K,V> e2) { return c.compare(e1.key,e2.key); } };
      data = new HashMap<P,Set<Entry<K,V>>>();
    }
    void clear() { data.clear(); }
    void add(Entry<K,V> e) { P p=proj.apply(e.key); Set<Entry<K,V>> s=data.get(p); if (s==null) { s=(cmp!=null)?new TreeSet<Entry<K,V>>(cmp):new /*HashSet<Entry<K,V>>*/ HESet<K,V>(); data.put(p,s); } s.add(e); }
    void del(Entry<K,V> e) { P p=proj.apply(e.key); Set<Entry<K,V>> s=data.get(p); if (s!=null) { s.remove(e); if (s.size()==0) data.remove(s); } }
    Set<Entry<K,V>> slice(Object part) { Set<Entry<K,V>> s=data.get((P)part); if (s==null) s=new HashSet<Entry<K,V>>(); return s; }
    Set<Entry<K,V>> slice(Object part, K low, K high, boolean lowIn, boolean highIn) { // assert(cmp!=null);
      TreeSet<Entry<K,V>> s=(TreeSet<Entry<K,V>>)data.get((P)part); Entry<K,V> l = new Entry<K,V>(0,low,zero,null); Entry<K,V> h = new Entry<K,V>(0,high,zero,null);
      if (s==null) s=new TreeSet<Entry<K,V>>(); return s.subSet(l,lowIn,h,highIn);
    }
  }

  // Lightweight specialized HashSet<Entry<K,E>>, that reuses data structures from the enclosing M3MapBase
  static class HEntry<K,V> { Entry<K,V> e; HEntry<K,V> next; HEntry(Entry<K,V> e, HEntry<K,V> next) { this.e=e; this.next=next; } }
  static class HESet<K,V> extends AbstractSet<Entry<K,V>> implements Set<Entry<K,V>> {
    private static final int INITIAL_CAPACITY = 1024;
    private transient HEntry<K,V>[] data;
    private transient int size;
    private transient int threshold;
    public HESet() { threshold=(int)(INITIAL_CAPACITY * LOAD_FACTOR); data=new HEntry[INITIAL_CAPACITY]; }
    private final HEntry<K,V> find(Entry<K,V> key) {
      int h=hash(key); int b=indexFor(h,data.length); HEntry<K,V> he=data[b];
      if (he!=null) do { if (h==he.e.hash && key.equals(he.e.key)) return he; } while ((he=he.next)!=null); return null;
    }
    private void createEntry(Entry<K,V> e, int bucket) { data[bucket]=new HEntry<K,V>(e,data[bucket]); ++size; }
    private void resize(int newCapacity) { if (data.length==MAXIMUM_CAPACITY) { threshold=Integer.MAX_VALUE; return; }
      HEntry[] newData=new HEntry[newCapacity]; HEntry<K,V> next=null;
      for (HEntry<K,V> he:data) if (he!=null) do { next=he.next; int b=indexFor(he.e.hash, newCapacity); he.next=newData[b]; newData[b]=he; } while((he=next)!=null);
      data=newData; threshold=(int)Math.min(newCapacity * LOAD_FACTOR, MAXIMUM_CAPACITY + 1);
    }

    // Set methods
    public int size() { return size; }
    public boolean isEmpty() { return size==0; }
    public void clear() { for (int i=0;i<data.length;++i) data[i]=null; size=0; }
    public boolean contains(Object o) { return find((Entry<K,V>)o)!=null; }
    
    // Iterator
    public Iterator<Entry<K,V>> iterator() { return new HIterator(); }
    public boolean add(Entry<K,V> e) { int h=e.hash; int b=indexFor(h, data.length);
      for(HEntry<K,V> eh=data[b];eh!=null;eh=eh.next) if (h==eh.e.hash && e.key.equals(eh.e.key)) return false;
      if ((size >= threshold) && (data[b]!=null)) { resize(2*data.length); b=indexFor(h,data.length); }
      createEntry(e,b); return true;
    }
    public boolean remove(Object o) {
      Entry<K,V> e = (Entry<K,V>)o;
      int h=hash(e.key); int b=indexFor(h, data.length); HEntry<K,V> prev=data[b],he=prev;
      while (he!=null) { HEntry<K,V> next=he.next; if (h==he.e.hash && e.key.equals(he.e.key)) { if (prev==he) data[b]=next; else prev.next=next; size--; return true; } prev=he; he=next; }
      return false;
    }
    private final class HIterator implements Iterator<Entry<K,V>> {
      private int bucket=0;
      private HEntry<K,V> cur=null,next=null;
      HIterator() { while (bucket<data.length && (next=data[bucket])==null) ++bucket; }
      public final boolean hasNext() { return next!=null; }
      public void remove() { HESet.this.remove(cur.e); }
      public Entry<K,V> next() { cur=next; if (cur.next!=null) next=cur.next; else { next=null; ++bucket; while (bucket<data.length && (next=data[bucket])==null) ++bucket; } return cur.e; }
    }
  }
}
