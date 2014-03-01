package ddbt.lib.store;
import scala.Function1;
import scala.Unit;

/**
 * Index interface.
 * By default it emits a warning when an unsupported function is called.
 * Specific implementation are below.
 *
 * @author TCK
 */
abstract class Idx<E extends Entry> {
  Idx(int i,boolean u) { idx=i; unique=u; }
  protected final int idx;
  protected final boolean unique;
  protected int size;

  protected void w(String n) {}//println(this.getClass.getName+": "+n+" not supported")
  public void insert(E e) { w("insert"); }
  public void delete(E e) { w("delete"); }
  public void update(E e) { w("update"); } // reposition the entry if key/hash modified
  public E get(E key) { w("get"); return null; } // returns the first element only
  public void foreach(Function1<E,Unit> f) { w("foreach"); } // on all elements; warning: what about reordering updates?
  public void slice(E key,Function1<E,Unit> f) { w("slice"); } // foreach on a slice
  public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) { w("range"); }
  public void clear() { w("clear"); }
  public void compact() { w("compact"); }
  public String info() { return "Idx("+idx+","+(unique?"unique":"multiple")+"){\n  type => ?\n}"; }
}

class IdxHashEntry<E extends Entry> {
  IdxHashEntry(int h, E d) { hash=h; data=d; }
  int hash; E data; IdxHashEntry<E> same, diff;
}

/**
 * IdxHash is a hashed index.
 * Buckets elements are stored in a special tree (invariant: sub-nodes of a same
 * branch do not have diff children). A bucket can be seen of a list(diff) of
 * list(same) of identical elements (a.cmp(idx,b)==0).
 * - If unique, a bucket is a simple list along 'diff'
 * - If non-unique, all elements along the 'same' branch are equal.
 *
 * Supported operations:
 * + insert,delete,update,get = O(1)
 * + range = O(n)
 */
@SuppressWarnings("unchecked")
class IdxHash<E extends Entry> extends Idx<E> {
  private static final int init_capacity = 16;
  private static final int max_capacity = 1 << 30;
  private static final float compact_factor = 0.05f;
  private final float load_factor;
  private IdxHashEntry<E>[] data = new IdxHashEntry[init_capacity];
  private int threshold;

  IdxHash(int i, boolean u) { super(i,u);
    load_factor = u ? 0.75f : 4.0f;
    threshold = Math.round(init_capacity * load_factor);
  }
  // Private/inlined functions
  // @inline private def _hash(e:E) = { var h=e.hash(idx); h^=(h>>>20)^(h>>>12)^(h<<9); h^(h>>>7)^(h>>>4); }
  private void _resize(int new_capacity) {
    IdxHashEntry<E>[] d=new IdxHashEntry[new_capacity];
    for (int i=0,n=data.length;i<n;++i) { IdxHashEntry<E> e=data[i], en;
      while (e!=null) { en=e.diff; int b=e.hash&(new_capacity-1); e.diff=d[b]; d[b]=e; e=en; }
    }
    data=d; threshold=Math.min(Math.round(new_capacity*load_factor), max_capacity+1);
  }
  private boolean _del(E e,IdxHashEntry<E> i) {
    IdxHashEntry<E> p=i.same; if (p!=null) { i.same=p.same; i.data=p.data; p.data.data[idx]=i; return true; } // eat same child
    p=i.diff; if (p!=null) { i.hash=p.hash; i.same=p.same; i.diff=p.diff; i.data=p.data; p.data.data[idx]=i; return true; } // eat diff child
    // delete from parent (i is a leaf)
    int h=i.hash, b=h&(data.length-1); p=data[b];
    if (i==p) { data[b]=null; return true; } // it's the root
    else do {
      if (i==p.diff) { p.diff=null; return true; } // leaf of diff branch
      else if (p.hash==h && e.cmp(idx,p.data)==0) do { IdxHashEntry<E> s=p.same; if (i==s) { p.same=null; return true; }; p=s; } while (p!=null); // leaf of same branch
      p=p.diff;
    } while(p!=null);
    return false;
  }
  // Public
  @Override public void insert(E e) {
    if (size==threshold) { int n=data.length; if (n==max_capacity) threshold=Integer.MAX_VALUE; else _resize(n << 1); }
    int h=e.hash(idx), b=h&(data.length-1);
    IdxHashEntry<E> p=data[b], i=new IdxHashEntry<E>(h,e); e.data[idx]=i;
    if (p==null) { data[b]=i; size+=1; return; }
    else do {
      if (p.hash==h && e.cmp(idx,p.data)==0) {
        if (unique) { p.data=e; e.data[idx]=p; }
        else { i.same=p.same; p.same=i; size+=1; return; }
        return;
      }
      if (p.diff==null) { p.diff=i; size+=1; return; }
      p=p.diff;
    } while(p!=null);
  }
  @Override public void delete(E e) { IdxHashEntry<E> i=(IdxHashEntry<E>)e.data[idx]; if (i!=null && _del(e,i)) size-=1; }
  @Override public void update(E e) { IdxHashEntry<E> i=(IdxHashEntry<E>)e.data[idx]; if (i!=null && i.hash!=e.hash(idx) && _del(e,i)) { size-=1; insert(e); } }
  @Override public E get(E key) { int h=key.hash(idx); IdxHashEntry<E> e=data[h&(data.length-1)];
    while (e!=null && (e.hash!=h || key.cmp(idx,e.data)!=0)) e=e.diff; return e!=null ? e.data : null;
  }
  @Override public void foreach(Function1<E,Unit> f) { E d; IdxHashEntry<E> e,en;
    for (int i=0,n=data.length;i<n;++i) { e=data[i];
      if (e!=null) do { en=e.diff; do { d=e.data; e=e.same; f.apply(d); } while(e!=null); e=en; } while(e!=null);
    }
  }
  @Override public void slice(E key,Function1<E,Unit> f) { int h=key.hash(idx); IdxHashEntry<E> e=data[h&(data.length-1)];
    while (e!=null && (e.hash!=h || key.cmp(idx,e.data)!=0)) e=e.diff;
    if (e!=null) do { E d=e.data; e=e.same; f.apply(d); } while (e!=null);
  }
  @Override public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) {
    int cMin=withMin?-1:0; int cMax=withMax?1:0;
    for (int i=0,n=data.length;i<n;++i) { IdxHashEntry<E> e=data[i],em,en;
      while (e!=null) { en=e.diff; if (e.data.cmp(idx,min)>cMin && e.data.cmp(idx,max)<cMax) do { em=e.same; f.apply(e.data); e=em; } while (e!=null); e=en; }
    }
  }
  @Override public void clear() { IdxHashEntry<E> z=null; for(int i=0,n=data.length;i<n;++i) { data[i]=z; } size=0; }
  @Override public void compact() { if (data.length*compact_factor>size) _resize(Math.max(init_capacity, 1 << ((int)Math.ceil(1+(Math.log((size/load_factor))/Math.log(2)))) )); }
  @Override public String info() { IdxHashEntry<E> e,en; int max=0; int n=data.length;
    for (int i=0;i<n;++i) { e=data[i]; int c=0; if (e!=null) do { en=e.diff; do { ++c; e=e.same; } while(e!=null); e=en; } while(e!=null); if (c>max) max=c; }
    return "IdxHash("+idx+","+(unique?"unique":"multiple")+") {\n  elements => "+size+"\n  buckets => "+n+"\n  occupancy => "+(size*1.0/n)+"\n  occupancyMax => "+max+"\n  loadFactor => "+load_factor+"\n}";
  }
}
