package ddbt.lib.store; // we pretend
import scala.Function1;
import scala.Unit;

class IdxHashTEntry<E extends Entry> {
  IdxHashTEntry(int h, E d) { hash=h; data=d; }
  int hash; E data; IdxHashTEntry<E> same, diff;
}

/**
 * IdxHashT is a hashed index.
 * Buckets elements are stored in a special tree (invariant: sub-nodes of a same
 * branch do not have diff children). A bucket can be seen of a list(diff) of
 * list(same) of identical elements (a.cmp(idx,b)==0).
 * - If unique, a bucket is a simple list along 'diff'
 * - If non-unique, all elements along the 'same' branch are equal.
 * In non-unique hash maps, size has a slightly different semantics and means
 * number of distinguishable elements (vs total number of elements).
 *
 * Use case: default, unless special operations are required.
 *
 * Supported operations:
 * + insert,delete,update,get = O(1)
 * + range = O(n)
 */
@SuppressWarnings("unchecked")
class IdxHashT<E extends Entry> extends Idx<E> {
  private static final int init_capacity = 16;
  private static final int max_capacity = 1 << 30;
  private static final float compact_factor = 0.05f;
  private final float load_factor;
  protected IdxHashTEntry<E>[] data = new IdxHashTEntry[init_capacity];
  protected int threshold;

  IdxHashT(Store<E> st, int idx, boolean unique, float factor) {
    super(st,idx,unique); load_factor = factor;
    threshold = Math.round(init_capacity * load_factor);
  }
  IdxHashT(Store<E> st, int idx, boolean unique) {
    super(st,idx,unique); load_factor = 0.75f;
    threshold = Math.round(init_capacity * load_factor);
  }
  // Private/inlined functions
  // @inline private def _hash(e:E) = { var h=e.hash(idx); h^=(h>>>20)^(h>>>12)^(h<<9); h^(h>>>7)^(h>>>4); }
  private void _resize(int new_capacity) {
    IdxHashTEntry<E>[] d=new IdxHashTEntry[new_capacity];
    for (int i=0,n=data.length;i<n;++i) { IdxHashTEntry<E> e=data[i], en;
      while (e!=null) { en=e.diff; int b=e.hash&(new_capacity-1); e.diff=d[b]; d[b]=e; e=en; }
    }
    data=d; threshold=Math.min(Math.round(new_capacity*load_factor), max_capacity+1);
  }
  protected void _resize() { int n=data.length; if (n==max_capacity) threshold=Integer.MAX_VALUE; else _resize(n<<1); }
  protected boolean _del(E e,IdxHashTEntry<E> i) {
    IdxHashTEntry<E> p=i.same; if (p!=null) { i.same=p.same; i.data=p.data; p.data.data[idx]=i; /*size-=1;*/ return true; } // eat same child (keep size)
    p=i.diff; if (p!=null) { i.hash=p.hash; i.same=p.same; i.diff=p.diff; i.data=p.data; p.data.data[idx]=i; size-=1; return true; } // eat diff child (dec size)
    // delete from parent (i is a leaf)
    int h=i.hash, b=h&(data.length-1); p=data[b];
    if (i==p) { data[b]=null; size-=1; return true; } // it's the root
    else do {
      if (i==p.diff) { p.diff=null; size-=1; return true; } // leaf of diff branch (dec size)
      else if (p.hash==h && ops.cmp(e,p.data)==0) do { IdxHashTEntry<E> s=p.same; if (i==s) { p.same=null; /*size-=1;*/ return true; }; p=s; } while (p!=null); // leaf of same branch (keep size)
      p=p.diff;
    } while(p!=null);
    return false;
  }
  // Public
  @Override public void unsafeInsert(E e) {
    if (size==threshold) _resize();
    int h=ops.hash(e), b=h&(data.length-1);
    IdxHashTEntry<E> i=new IdxHashTEntry<E>(h,e); i.diff=data[b]; data[b]=i; size+=1;
  }
  public void insert(E e) {
    if (size==threshold) _resize();
    int h=ops.hash(e), b=h&(data.length-1);
    IdxHashTEntry<E> p=data[b], i=new IdxHashTEntry<E>(h,e); e.data[idx]=i;
    if (p==null) { data[b]=i; size+=1; return; } // add as root
    else do {
      if (p.hash==h && ops.cmp(e,p.data)==0) {
        if (unique) { p.data=e; e.data[idx]=p; }
        else { i.same=p.same; p.same=i; /*size+=1;*/ } // add in same (keep size)
        return;
      }
      if (p.diff==null) { p.diff=i; size+=1; return; } // add in diff
      p=p.diff;
    } while(p!=null);
  }
  @Override public void delete(E e) { IdxHashTEntry<E> i=(IdxHashTEntry<E>)e.data[idx]; if (i!=null && _del(e,i)) { e.data[idx]=null; /*size-=1;*/ } }
  @Override public void update(E e) { IdxHashTEntry<E> i=(IdxHashTEntry<E>)e.data[idx]; if (i!=null && i.hash!=ops.hash(e) && _del(e,i)) { /*size-=1;*/ insert(e); } }
  @Override public E get(E key) { int h=ops.hash(key); IdxHashTEntry<E> e=data[h&(data.length-1)];
    while (e!=null && (e.hash!=h || ops.cmp(key,e.data)!=0)) e=e.diff; return e!=null ? e.data : null;
  }
  @Override public void foreach(Function1<E,Unit> f) { E d; IdxHashTEntry<E> e,en;
    for (int i=0,n=data.length;i<n;++i) { e=data[i];
      if (e!=null) do { en=e.diff; do { d=e.data; e=e.same; f.apply(d); } while(e!=null); e=en; } while(e!=null);
    }
  }
  @Override public void slice(E key,Function1<E,Unit> f) {
    int h=ops.hash(key); IdxHashTEntry<E> e=data[h&(data.length-1)];
    if (e!=null && (e.hash!=h || ops.cmp(key,e.data)!=0)) do { e=e.diff; } while (e!=null && (e.hash!=h || ops.cmp(key,e.data)!=0));
    if (e!=null) do { E d=e.data; e=e.same; f.apply(d); } while (e!=null);
  }
  @Override public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) {
    int cMin=withMin?-1:0; int cMax=withMax?1:0;
    for (int i=0,n=data.length;i<n;++i) { IdxHashTEntry<E> e=data[i],em,en;
      while (e!=null) { en=e.diff; if (ops.cmp(e.data,min)>cMin && ops.cmp(e.data,max)<cMax) do { em=e.same; f.apply(e.data); e=em; } while (e!=null); e=en; }
    }
  }
  @Override public void clear() { IdxHashTEntry<E> z=null; for(int i=0,n=data.length;i<n;++i) { data[i]=z; } size=0; }
  @Override public void compact() { if (data.length*compact_factor>size) _resize(Math.max(init_capacity, 1 << ((int)Math.ceil(1+(Math.log((size/load_factor))/Math.log(2)))) )); }
  @Override public String info() { IdxHashTEntry<E> e,en; int max=0; int n=data.length;
    for (int i=0;i<n;++i) { e=data[i]; int c=0; if (e!=null) do { en=e.diff; do { ++c; e=e.same; } while(e!=null); e=en; } while(e!=null); if (c>max) max=c; }
    return "IdxHashT("+idx+","+(unique?"unique":"multiple")+") {\n  elements => "+size+"\n  buckets => "+n+"\n  occupancy => "+(size*1.0/n)+"\n  occupancyMax => "+max+"\n  loadFactor => "+load_factor+"\n}";
  }
}
