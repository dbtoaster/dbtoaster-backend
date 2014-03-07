package ddbt.lib.store; // we pretend
import scala.Function1;
import scala.Unit;

/**
 * This is the single list version of ddbt.lib.store.IdxHash
 * Used only with tests to claim performance improvement
 */

class IdxHashLEntry<E extends Entry> {
  IdxHashLEntry(int h, E d) { hash=h; data=d; }
  int hash; E data; IdxHashLEntry<E> next;
}

@SuppressWarnings("unchecked")
class IdxHashL<E extends Entry> extends Idx<E> {
  private static final int init_capacity = 16;
  private static final int max_capacity = 1 << 30;
  private static final float compact_factor = 0.05f;
  private final float load_factor;
  protected IdxHashLEntry<E>[] data = new IdxHashLEntry[init_capacity];
  protected int threshold;

  IdxHashL(Store<E> st, int idx, boolean unique, float factor) {
    super(st,idx,unique); load_factor = factor;
    threshold = Math.round(init_capacity * load_factor);
  }
  IdxHashL(Store<E> st, int idx, boolean unique) {
    super(st,idx,unique); load_factor = unique ? 0.75f : 4.0f;
    threshold = Math.round(init_capacity * load_factor);
  }
  // Private/inlined functions
  private void _resize(int new_capacity) {
    IdxHashLEntry<E>[] d=new IdxHashLEntry[new_capacity];
    for (int i=0,n=data.length;i<n;++i) { IdxHashLEntry<E> e=data[i], en;
      while (e!=null) { en=e.next; int b=e.hash&(new_capacity-1); e.next=d[b]; d[b]=e; e=en; }
    }
    data=d; threshold=Math.min(Math.round(new_capacity*load_factor), max_capacity+1);
  }
  protected void _resize() { int n=data.length; if (n==max_capacity) threshold=Integer.MAX_VALUE; else _resize(n<<1); }
  protected boolean _del(E e,IdxHashLEntry<E> i) {
    IdxHashLEntry<E> p=i.next; if (p!=null) { i.hash=p.hash; i.next=p.next; i.data=p.data; p.data.data[idx]=i; return true; } // eat next child
    int h=i.hash, b=h&(data.length-1); p=data[b];
    if (i==p) { data[b]=null; return true; } // head of list
    else do { if (i==p.next) { p.next=null; return true; } p=p.next; } while(p!=null); // tail
    return false;
  }
  // Public
  @Override public void unsafeInsert(E e) {
    if (size==threshold) _resize();
    int h=ops.hash(e), b=h&(data.length-1);
    IdxHashLEntry<E> i=new IdxHashLEntry<E>(h,e); i.next=data[b]; data[b]=i; size+=1;
  }
  @Override public void insert(E e) {
    if (size==threshold) _resize();
    int h=ops.hash(e), b=h&(data.length-1);
    IdxHashLEntry<E> p=data[b], i=new IdxHashLEntry<E>(h,e); e.data[idx]=i;
    if (p==null) { data[b]=i; size+=1; return; }
    else if (!unique) { i.next=data[b]; data[b]=i; size+=1; return; }
    else do { // unique
      if (p.hash==h && ops.cmp(e,p.data)==0) { p.data=e; e.data[idx]=p; return; }
      if (p.next==null) { p.next=i; size+=1; return; }
      p=p.next;
    } while(p!=null);
  }
  @Override public void delete(E e) { IdxHashLEntry<E> i=(IdxHashLEntry<E>)e.data[idx]; if (i!=null && _del(e,i)) { e.data[idx]=null; size-=1; } }
  @Override public void update(E e) { IdxHashLEntry<E> i=(IdxHashLEntry<E>)e.data[idx]; if (i!=null && i.hash!=ops.hash(e) && _del(e,i)) { size-=1; insert(e); } }
  @Override public E get(E key) { int h=ops.hash(key); IdxHashLEntry<E> e=data[h&(data.length-1)];
    while (e!=null && (e.hash!=h || ops.cmp(key,e.data)!=0)) e=e.next; return e!=null ? e.data : null;
  }
  @Override public void foreach(Function1<E,Unit> f) { E d; IdxHashLEntry<E> e,en;
    for (int i=0,n=data.length;i<n;++i) { e=data[i];
      if (e!=null) do { en=e.next; d=e.data; f.apply(d); e=en; } while(e!=null);
    }
  }
  @Override public void slice(E key,Function1<E,Unit> f) { int h=ops.hash(key); IdxHashLEntry<E> e=data[h&(data.length-1)];
    if (e!=null) do { if (e.hash==h && ops.cmp(key,e.data)==0) f.apply(e.data); e=e.next; } while(e!=null);
  }
  @Override public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) {
    int cMin=withMin?-1:0; int cMax=withMax?1:0;
    for (int i=0,n=data.length;i<n;++i) { IdxHashLEntry<E> e=data[i],em,en;
      while (e!=null) { en=e.next; if (ops.cmp(e.data,min)>cMin && ops.cmp(e.data,max)<cMax) f.apply(e.data); e=en; }
    }
  }
  @Override public void clear() { IdxHashLEntry<E> z=null; for(int i=0,n=data.length;i<n;++i) { data[i]=z; } size=0; }
  @Override public void compact() { if (data.length*compact_factor>size) _resize(Math.max(init_capacity, 1 << ((int)Math.ceil(1+(Math.log((size/load_factor))/Math.log(2)))) )); }
  @Override public String info() { IdxHashLEntry<E> e,en; int max=0; int n=data.length;
    for (int i=0;i<n;++i) { e=data[i]; int c=0; if (e!=null) do { en=e.next; ++c; e=en; } while(e!=null); if (c>max) max=c; }
    return "IdxHashL("+idx+","+(unique?"unique":"multiple")+") {\n  elements => "+size+"\n  buckets => "+n+"\n  occupancy => "+(size*1.0/n)+"\n  occupancyMax => "+max+"\n  loadFactor => "+load_factor+"\n}";
  }
}

