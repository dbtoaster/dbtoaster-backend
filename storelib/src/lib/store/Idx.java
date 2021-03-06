package ddbt.lib.store;

import scala.Function1;
import scala.NotImplementedError;
import scala.Unit;


import java.util.ArrayList;

/**
 * Index interface.
 * By default it emits a warning when an unsupported function is called.
 * Specific implementation are below.
 *
 * @author TCK
 */
public abstract class Idx<E extends Entry> {
    static boolean allowResize = true;

    Idx(Store<E> st, int idx, boolean unique) {
        this.ops = st.ops()[idx];
        this.idx = idx;
        this.unique = unique;
    }

    protected Entry dataHead;
    protected final EntryIdx<E> ops;
    protected final int idx;
    protected final boolean unique;
    protected int size;

    protected void w(String n) {
        throw new NotImplementedError(this.getClass().getName() + ": " + n + " not supported");
    }

    public void unsafeInsert(E e) {
        w("unsafeInsert");
    }

    public String getSizeStat() {
        return "";
    }

    public void delete(E e) {
        w("delete");
    }

    public void deleteCopyDependent(E e) {
        delete(e);
    }

    public void deleteCopy(E e, Idx<E> primary) {
        E ref = primary.get(e);
        delete(ref);
    }

    public void update(E e) {
        w("update");
    } // reposition the entry if key/hash modified

    public void updateCopyDependent(E e, E ref) {
        delete(ref);
        unsafeInsert(e);
    }

    public void updateCopy(E e, Idx<E> primary) {
        E ref = primary.get(e);
        delete(ref);
        unsafeInsert(e);
    }

    public E get(E key) {
        w("get");
        return null;
    } // returns the first element only

    public E getCopy(E key) {
        E e = get(key);
        if (e != null)
            return (E) e.copy();
        return null;
    }

    public E getCopyDependent(E key) {
        E e = get(key);
        if (e != null)
            return (E) e.copy();
        return null;
    }
    public E getForUpdate(E key) {
        return get(key);
    }

    public void foreachResMap(Function1<E, Unit> f, MultiRes res) {
        //TODO :Fix later
        foreach(f);
    }

    public MultiRes foreachRes() {
        //TODO: Fix later
        return new ddbt.lib.store.ForEachRes<E>(null);
    }

    public void foreach(Function1<E, Unit> f) {
        w("foreach");
    } // on all elements; warning: what about reordering updates?

    public void foreachCopy(Function1<E, Unit> f) { w("foreachCopy"); }

    public void slice(E key, Function1<E, Unit> f) {
        w("slice");
    } // foreach on a slice

    public void sliceNoUpdate(E key, Function1<E, Unit> f) {
        w("sliceNoUpdate");
    }

    public MultiRes sliceRes(E key) {
        return null;
    }

    public void sliceResMap(E key, Function1<E, Unit> f, MultiRes res) {
        w("sliceResMap");
    }

    public void sliceResMapNoUpd(E key, Function1<E, Unit> f, MultiRes res) {
        w("sliceResMapNoUpd");
    }

    public void sliceCopy(E key, Function1<E, Unit> f) {
        w("sliceCopy");
    } // foreach on a slice

    public void sliceCopyDependent(E key, Function1<E, Unit> f) {
        sliceCopy(key, f);
    } // foreach on a slice

    public void range(E min, E max, boolean withMin, boolean withMax, Function1<E, Unit> f) {
        w("range");
    }

    public void clear() {
        w("clear");
    }

    public void compact() {
        w("compact");
    }

    public void getBucketStats() {
    }

    public boolean hashDiffers(E e1, E e2) {
        return ops.hash(e1) != ops.hash(e2);
    }

    public String info() {
        return this.getClass().getName() + "(" + idx + "," + (unique ? "unique" : "multiple") + ")";
    }
}

/**
 * IdxHash is a hashed index.
 * Buckets elements are stored in a list.
 * Use case: default, unless special operations are required.
 * <p>
 * Supported operations:
 * + insert,delete,update,get = O(1)
 * + range = O(n)
 */
class IdxHashEntry<E extends Entry> {
    IdxHashEntry(int h, E d) {
        hash = h;
        data = d;
    }

    int hash;
    E data;
    IdxHashEntry<E> next, prev;
}

@SuppressWarnings("unchecked")
class IdxHash<E extends Entry> extends Idx<E> {
    private static final int init_capacity = 16;
    private static final int max_capacity = 1 << 30;
    private static final float compact_factor = 0.05f;
    private final float load_factor;
    protected IdxHashEntry<E>[] data = new IdxHashEntry[init_capacity];
    protected int threshold;

    IdxHash(Store<E> st, int idx, boolean unique, float factor) {
        super(st, idx, unique);
        load_factor = factor;
        threshold = Math.round(init_capacity * load_factor);
    }

    IdxHash(Store<E> st, int idx, boolean unique) {
        super(st, idx, unique);
        load_factor = 0.75f;
        threshold = Math.round(init_capacity * load_factor);
    }

    @Override
    public String getSizeStat() {
        int numInArray = 0;
        for (int i = 0; i < data.length; ++i) {
            if (data[i] != null) {
                numInArray++;
            }
        }
        return "array length = " + data.length + "  numElements  = " + size + "  threshold = " + threshold + "   numInArray = " + numInArray;
    }

    // Private/inlined functions
    void _resize(int new_capacity) {
        IdxHashEntry<E>[] d = new IdxHashEntry[new_capacity];
        for (int i = 0, n = data.length; i < n; ++i) {
            IdxHashEntry<E> e = data[i], en;
            while (e != null) {
                en = e.next;
                int b = (e.hash > 0 ? e.hash : -e.hash) % new_capacity;
                e.next = d[b];
                if (d[b] != null)
                    d[b].prev = e;
                d[b] = e;
                e.prev = null;
                e = en;
            }
        }
        data = d;
        threshold = Math.min(Math.round(new_capacity * load_factor), max_capacity + 1);
    }

    protected void _resize() {
        int n = data.length;
        if (n == max_capacity) threshold = Integer.MAX_VALUE;
        else _resize(n << 1);
    }

    protected void _del(E e, IdxHashEntry<E> i) {
        if (idx == 0) {
            Entry elemPrev = e.prev, elemNext = e.next;
            if (elemPrev != null)
                elemPrev.next = elemNext;
            else
                dataHead = elemNext;

            if (elemNext != null) elemNext.prev = elemPrev;

            e.next = null;
            e.prev = null;
        }
        IdxHashEntry<E> nxt = i.next;
        IdxHashEntry<E> prv = i.prev;
        if (prv != null) { //not head
            prv.next = nxt;
            if (nxt != null)
                nxt.prev = prv;
        } else if (nxt != null) { //head and has other elements
            i.hash = nxt.hash;
            i.next = nxt.next;
            if (nxt.next != null)
                nxt.next.prev = i;
            i.data = nxt.data;
            nxt.data.data[idx] = i;
        } else { //head and the only element
            int h = i.hash, b = (h > 0 ? h : -h) % data.length;
            if (data[b] == i)
                data[b] = null;
            else
                throw new IllegalStateException();
        }
    }

    // Public
    @Override
    public void unsafeInsert(E e) {
        if (size == threshold) {
            _resize();
            if (!allowResize)
                throw new IllegalStateException("Heap resize");
        }
        int h = ops.hash(e), b = (h > 0 ? h : -h) % data.length;
        if (idx == 0) {
            e.prev = null;
            e.next = dataHead;
            if (dataHead != null)
                dataHead.prev = e;
            dataHead = e;
        }
        IdxHashEntry<E> i = new IdxHashEntry<E>(h, e);
        e.data[idx] = i;
        i.next = data[b];
        if (data[b] != null)
            data[b].prev = i;
        data[b] = i;
        size += 1;
    }

    @Override
    public void getBucketStats() {
        int maxEntries = 0;
        int maxSlices = 0;
        int numBuckets = 0;
        int numSlices = 0;
        int numEntries = 0;

        for (int b = 0; b < data.length; ++b) {
            IdxHashEntry<E> n1 = data[b];
            if (n1 == null)
                continue;
            numBuckets++;
            int ns = 0;
            int es = 0;
            IdxHashEntry<E> n2 = n1;
            do {
                do {
                    ++es;
                } while ((n2 = n2.next) != null && n2.hash == n1.hash && ops.cmp(n1.data, n2.data) == 0);
                ++ns;
            } while ((n1 = n2) != null);
            if (es > maxEntries)
                maxEntries = es;
            if (ns > maxSlices)
                maxSlices = ns;
            numEntries += es;
            numSlices += ns;
        }
        if (numBuckets == 0)
            System.err.println("Empty");
        else {
            String idxs = "IDX = " + idx;
            String ents = "    Entries : total = " + numEntries + "  avg = " + (numEntries / (1.0 * numBuckets)) + "  max = " + maxEntries;
            String slices = "    Slices : total = " + numBuckets + "  avg = " + (numSlices / (1.0 * numBuckets)) + "  max = " + maxSlices;
            System.err.println(idxs + ents + slices);
        }
    }


    @Override
    public void delete(E e) {
        IdxHashEntry<E> i = (IdxHashEntry<E>) e.data[idx];
        if (i != null) {
            _del(e, i);
            e.data[idx] = null;
            size -= 1;
        }
    }

    @Override
    public void update(E e) {
        IdxHashEntry<E> i = (IdxHashEntry<E>) e.data[idx];
        if (i != null && i.hash != ops.hash(e)) {
            _del(e, i);
            size -= 1;
            unsafeInsert(e);
        }
    }

    @Override
    public E get(E key) {
        int h = ops.hash(key);
        IdxHashEntry<E> e = data[(h > 0 ? h : -h) % data.length];
        while (e != null && (e.hash != h || ops.cmp(key, e.data) != 0))
            e = e.next;
        return e != null ? e.data : null;
    }

    @Override
    public void foreach(Function1<E, Unit> f) {
        Entry cur = dataHead;
        while (cur != null) {
            f.apply((E) cur);
            cur = cur.next;
        }
    }

    @Override
    public void foreachCopy(Function1<E, Unit> f) {
        ArrayList<E> entries = new ArrayList<E>();
        Entry cur = dataHead;
        while (cur != null) {
            entries.add((E) cur.copy());
            cur = cur.next;
        }
        for(E e_ : entries)
            f.apply(e_);
    }

    @Override
    public MultiRes sliceRes(E key) {
        if (idx == 0) {
            //Can't use primary hash fn for slice
            throw new NotImplementedError("slice res not implemented for primary idx");
        } else {
            int h = ops.hash(key);
            IdxHashEntry<E> e = data[(h > 0 ? h : -h) % data.length];
            if (e != null) do {
                if (e.hash == h && ops.cmp(key, e.data) == 0)
                    return new SliceRes<E>(e);
                e = e.next;
            } while (e != null);
            return new SliceRes<E>(null);
        }
    }

    @Override
    public void sliceResMapNoUpd(E key, Function1<E, Unit> f, MultiRes res) {
        if (idx == 0) {
            //Can't use primary hash fn for slice
            throw new NotImplementedError("sliceresMapNoUpd not implemented for primary idx");
        } else {
            IdxHashEntry<E> e = ((SliceRes<E>) res).sliceHead();
            int h = e.hash;
            do {
                if (e.hash == h && ops.cmp(key, e.data) == 0)
                    f.apply(e.data);
            } while ((e = e.next) != null);
        }
    }

    @Override
    public void sliceResMap(E key, Function1<E, Unit> f, MultiRes res) {
        if (idx == 0) {
            //Can't use primary hash fn for slice
            throw new NotImplementedError("sliceResMap not implemented for primary idx");
        } else {
            IdxHashEntry<E> e = ((SliceRes<E>) res).sliceHead();
            ArrayList<E> entries = new ArrayList<E>();
            int h = e.hash;
            do {
                if (e.hash == h && ops.cmp(key, e.data) == 0)
                    entries.add(e.data);
            } while ((e = e.next) != null);
            for (E e_ : entries) {
                f.apply(e_);
            }
        }
    }

    @Override
    public void sliceNoUpdate(E key, Function1<E, Unit> f) {
        if (idx == 0) {
            //Can't use primary hash fn for slice
            Entry e = dataHead;
            while(e != null) {
                if(ops.cmp(key, (E)e) == 0)
                    f.apply((E)e);
                e = e.next;
            }
        } else {
            int h = ops.hash(key);
            IdxHashEntry<E> e = data[(h > 0 ? h : -h) % data.length];
            if (e != null) do {
                if (e.hash == h && ops.cmp(key, e.data) == 0) f.apply(e.data);
                e = e.next;
            } while (e != null);
        }
    }

    @Override
    public void slice(E key, Function1<E, Unit> f) {
        ArrayList<E> entries = new ArrayList<E>();
        if (idx == 0) {
            //Can't use primary hash fn for slice
            Entry e = dataHead;
            while(e != null) {
                if(ops.cmp(key, (E)e) == 0)
                    entries.add((E) e);
                e = e.next;
            }
        } else {
            int h = ops.hash(key);
            IdxHashEntry<E> e = data[(h > 0 ? h : -h) % data.length];
            if (e != null) do {
                if (e.hash == h && ops.cmp(key, e.data) == 0) entries.add(e.data);
                e = e.next;
            } while (e != null);
        }
        for (E e_ : entries) {
            f.apply(e_);
        }
    }

    @Override
    public void sliceCopy(E key, Function1<E, Unit> f) {
        ArrayList<E> entries = new ArrayList<E>();
        if (idx == 0) {
            //Can't use primary hash fn for slice
            Entry e = dataHead;
            while(e != null) {
                if(ops.cmp(key, (E)e) == 0)
                    entries.add((E) e.copy());
                e = e.next;
            }
        } else {
            int h = ops.hash(key);
            IdxHashEntry<E> e = data[(h > 0 ? h : -h) % data.length];
            if (e != null) do {
                if (e.hash == h && ops.cmp(key, e.data) == 0)
                    entries.add((E) e.data.copy());
                e = e.next;
            } while (e != null);
        }
        for (E e_ : entries) {
            f.apply(e_);
        }
    }

    @Override
    public void range(E min, E max, boolean withMin, boolean withMax, Function1<E, Unit> f) {
        int cMin = withMin ? -1 : 0;
        int cMax = withMax ? 1 : 0;
        for (int i = 0, n = data.length; i < n; ++i) {
            IdxHashEntry<E> e = data[i], em, en;
            while (e != null) {
                en = e.next;
                if (ops.cmp(e.data, min) > cMin && ops.cmp(e.data, max) < cMax) f.apply(e.data);
                e = en;
            }
        }
    }

    @Override
    public void clear() {
        IdxHashEntry<E> z = null;
        dataHead = null;
        for (int i = 0, n = data.length; i < n; ++i) {
            data[i] = z;
        }
        size = 0;
    }

    @Override
    public void compact() {
        if (data.length * compact_factor > size)
            _resize(Math.max(init_capacity, 1 << ((int) Math.ceil(1 + (Math.log((size / load_factor)) / Math.log(2))))));
    }

    @Override
    public String info() {
        IdxHashEntry<E> e, en;
        int max = 0;
        int n = data.length;
        for (int i = 0; i < n; ++i) {
            e = data[i];
            int c = 0;
            if (e != null) do {
                en = e.next;
                ++c;
                e = en;
            } while (e != null);
            if (c > max) max = c;
        }
        return "IdxHash(" + idx + "," + (unique ? "unique" : "multiple") + ") {\n  elements => " + size + "\n  buckets => " + n + "\n  occupancy => " + (size * 1.0 / n) + "\n  occupancyMax => " + max + "\n  loadFactor => " + load_factor + "\n}";
    }
}

/**
 * IdxSliced maintains 1 element (min or max) for each slice.
 * IdxSliced maintains minimum or maximum of each slice. Slicing is provided by
 * sliceIdx which correspond to another _implemented_ index supporting slice op.
 * When min/max is deleted, a new min/max is looked up in the sliceIdx index.
 * <p>
 * Use case: min/max is rarely deleted.
 * <p>
 * Supported operations:
 * + insert,delete,update = O(1)/O(N) if min/max / get=O(1)
 * + clear,size
 */
@SuppressWarnings("unchecked")
class IdxSliced<E extends Entry> extends IdxHash<E> {
    private int cmpRes;
    private int cmpIdx;
    private E cmpE = null;
    private Idx<E>[] idxs;
    private EntryIdx<E> ops2;

    IdxSliced(Store<E> st, int cmpIdx, int sliceIdx, boolean max) {
        super(st, sliceIdx, true);
        ops2 = st.ops()[cmpIdx];
        this.idxs = st.idxs();
        cmpIdx = cmpIdx;
        cmpRes = max ? 1 : -1;
    }

    @Override
    //SBJ: TODO: Remove checks
    public void unsafeInsert(E e) {
        if (size == threshold) _resize();
        int h = ops.hash(e), b = (h > 0 ? h : -h) % data.length;
        IdxHashEntry<E> p = data[b], i = new IdxHashEntry<E>(h, e);
        e.data[idx] = i;
        if (p == null) {
            data[b] = i;
            size += 1;
            return;
        } else do {
            if (p.hash == h && ops.cmp(e, p.data) == 0) {
                if (ops2.cmp(e, p.data) == cmpRes) {
                    p.data = e;
                    e.data[idx] = p;
                }
                return;
            }
            if (p.next == null) {
                p.next = i;
                size += 1;
                return;
            }
            p = p.next;
        } while (p != null);
    }

    @Override
    public void delete(E e) {
        IdxHashEntry<E> i = (IdxHashEntry<E>) e.data[idx];
        if (i == null) return;
        _del(e, i);
        e.data[idx] = null;
        // Find a replacement candidate
        Function1<E, Unit> f = new JFun1<E, Unit>() {
            @Override
            public Unit apply(E e) {
                if (cmpE == null || ops.cmp(e, cmpE) == cmpRes) cmpE = e;
                return (Unit) null;
            }
        };
        idxs[idx].slice(e, f);
        if (cmpE != null) unsafeInsert(cmpE);
        else size -= 1;
        cmpE = null;
    }
}

/**
 * IdxList is a simple sequential storage reminiscent of the disk era.
 * Lightweight singe-linked list (head --> tail), unique should be disabled
 * for best insertion performance (avoid checking duplicates).
 * <p>
 * Use case: WAL log or temporary storage, sorted by least recently inserted.
 * <p>
 * Supported operations:
 * + insert O(1)/O(N),delete O(N),update O(1)/O(N) / get=O(1)
 * + clear,size
 */
@SuppressWarnings("unchecked")
class IdxList<E extends Entry> extends Idx<E> {
    IdxList(Store<E> st, int idx, boolean unique) {
        super(st, idx, unique);
    }

    private E head = null;
    private E tail = null;

    @Override
    //SBJ: TODO: Remove checks
    public void unsafeInsert(E e) {
        /*
        if (unique && head != null) {
            if (e == head) {
                head = (E) head.data[idx];
                if (e == tail) tail = null;
            } else {
                E p = head;
                do {
                    E n = (E) p.data[idx];
                    if (e == n) {
                        p.data[idx] = n.data[idx];
                        if (n == tail) tail = p;
                        break;
                    }
                    p = n;
                } while (p != null);
            }
        }
        */
        if (tail != null) {
            tail.data[idx] = e;
            tail = e;
        } else {
            head = e;
            tail = e;
        }
    }

    @Override
    public void delete(E e) {
        if (head == null) return;
        if (e == head) {
            head = (E) head.data[idx];
            if (e == tail) tail = null;
        } else {
            E p = head;
            do {
                E n = (E) p.data[idx];
                if (e == n) {
                    p.data[idx] = n.data[idx];
                    if (n == tail) tail = p;
                    break;
                } else p = n;
            } while (p != null);
        }
        e.data[idx] = null;
    }

    @Override
    public void update(E e) {
        delete(e);
        unsafeInsert(e);
    }

    @Override
    public E get(E key) {
        E p = head;
        if (p != null) do {
            if (ops.cmp(key, p) == 0) return p;
            p = (E) p.data[idx];
        } while (p != null);
        return null;
    }

    @Override
    public void foreach(Function1<E, Unit> f) {
        E p = head;
        if (p != null) do {
            E n = (E) p.data[idx];
            f.apply(p);
            p = n;
        } while (p != null);
    }
    @Override
    public void foreachCopy(Function1<E, Unit> f) {
        E p = head;
        ArrayList<E> entries = new ArrayList<E>();
        if (p != null) do {
            E n = (E) p.data[idx];
            entries.add((E) p.copy());
            p = n;
        } while (p != null);
        for(E e_ : entries)
            f.apply(e_);
    }
    @Override
    public void slice(E key, Function1<E, Unit> f) {
        E p = head;
        if (p != null) do {
            E n = (E) p.data[idx];
            if (ops.cmp(key, p) == 0) f.apply(p);
            p = n;
        } while (p != null);
    }

    @Override
    public void sliceCopy(E key, Function1<E, Unit> f) {
        E p = head;
        ArrayList<E> entries = new ArrayList<E>();
        if (p != null) do {
            E n = (E) p.data[idx];
            if (ops.cmp(key, p) == 0) entries.add((E) p.copy());
            p = n;
        } while (p != null);
        for (E e_ : entries)
            f.apply(e_);
    }

    @Override
    public void clear() {
        head = null;
        tail = null;
    }

    @Override
    public void compact() {
    } // nothing to do
}