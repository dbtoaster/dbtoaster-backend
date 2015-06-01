package store2;
import scala.Function1;
import scala.Boolean;
import scala.Unit;

@SuppressWarnings("unchecked")
abstract public class IdxHash<E extends Entry<E>> extends Idx<E> {
  // function that must be implemented
  abstract protected int hash(E e);
  // tuple accessors
  abstract protected E _n(E e); // next attribute
  abstract protected void _n(E e, E next); // hash attribute
  abstract protected int _h(E e);
  abstract protected void _h(E e, int hash);

  private static final int init_capacity = 16;
  private static final int max_capacity = 1 << 30;
  private static final float compact_factor = 0.05f;
  private final float load_factor = 0.75f;
  protected E[] data = (E[])new Entry[init_capacity];
  protected int threshold;

  IdxHash(boolean unique) { super(unique); threshold=Math.round(init_capacity * load_factor); }
  // Private functions
  private void _resize(int new_capacity) {
    E[] d=(E[]) new Entry[new_capacity];
    for (int i=0,n=data.length;i<n;++i) { E e=data[i], en;
      while (e!=null) { en=_n(e); int b=_h(e)&(new_capacity-1); _n(e,d[b]); d[b]=e; e=en; }
    }
    data=d; threshold=Math.min(Math.round(new_capacity*load_factor), max_capacity+1);
  }
  protected void _resize() { int n=data.length; if (n==max_capacity) threshold=Integer.MAX_VALUE; else _resize(n<<1); }
  private boolean _del(E e) { int h=_h(e), b=h&(data.length-1); E p=data[b]; if (e==p) { data[b]=_n(e); _n(e,null); size-=1; return true; }
    do { if (e==_n(p)) { _n(p,_n(e)); size-=1; return true; } p=_n(p); } while(p!=null); return false;
  }
  // Public
  @Override public void insert(E e, Function1<E,Boolean> op) {
    if (size==threshold) _resize();
    int h=hash(e), b=h&(data.length-1); _h(e,h); E p=data[b];
    if (p!=null && unique) do { if (_h(p)==h && cmp(e,p)==0) {
      if (op!=null) op.apply(p); else e.copy(p);
      store.update(p,null); return;
    } p=_n(p); } while (p!=null);
    _n(e,data[b]); data[b]=e; size+=1; // insert frontmost

    /*
    // Insert & delete strategy
    int h=hash(e), b=h&(data.length-1); _h(e,h); E p=data[b];
    _n(e,p); data[b]=e; size+=1; // insert frontmost
    if (p!=null && unique) do { if (_h(p)==h && cmp(e,p)==0) {
      if (op!=null) op.apply(p);
      store.delete(p); return;
    } p=_n(p); } while (p!=null);
    */
  }

  @Override public void update(E e, Function1<E,Boolean> op) { if (_h(e)!=hash(e) && _del(e)) insert(e,op); }
  @Override public void delete(E e) { _del(e); }
  @Override public E get(E key) { int h=hash(key); E e=data[h&(data.length-1)]; while (e!=null && (_h(e)!=h || cmp(key,e)!=0)) e=_n(e); return e; }
  @Override public void foreach(Function1<E,Unit> f) { E d; E e,en;
    for (int i=0,n=data.length;i<n;++i) { e=data[i]; if (e!=null) do { en=_n(e); f.apply(e); e=en; } while(e!=null); }
  }
  @Override public void slice(E key,Function1<E,Unit> f) { int h=hash(key); E e=data[h&(data.length-1)];
    if (e!=null) do { E en=_n(e); if (_h(e)==h && cmp(key,e)==0) f.apply(e); e=en; } while(e!=null);
  }
  @Override public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) {
    int cMin=withMin?-1:0; int cMax=withMax?1:0;
    for (int i=0,n=data.length;i<n;++i) { E e=data[i],em,en;
      while (e!=null) { en=_n(e); if (cmp(e,min)>cMin && cmp(e,max)<cMax) f.apply(e); e=en; }
    }
  }
  @Override public void clear() { E[] d=(E[]) new Entry[init_capacity]; size=0; }
  @Override public void compact() { if (data.length*compact_factor>size) _resize(Math.max(init_capacity, 1 << ((int)Math.ceil(1+(Math.log((size/load_factor))/Math.log(2)))) )); }
  @Override public String info() { E e,en; int max=0; int n=data.length;
    for (int i=0;i<n;++i) { e=data[i]; int c=0; if (e!=null) do { en=_n(e); ++c; e=en; } while(e!=null); if (c>max) max=c; }
    return super.toString()+" {\n  size => "+size+"\n  buckets => "+n+"\n  occupancy => "+(size*1.0/n)+"\n  occupancy_max => "+max+"\n  load_factor => "+load_factor+"\n}";
  }
}
