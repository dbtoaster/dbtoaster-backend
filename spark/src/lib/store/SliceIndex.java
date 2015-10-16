package ddbt.lib.spark.store;

import scala.Function1;
import scala.Unit;

/**
  * SliceIndex maintains 1 element (min or max) for each slice.
  *
  * Slicing is provided by cmpIndex which correspond to another implemented 
  * index supporting slice op.
  * When min/max is deleted, a new min/max is looked up in the cmpIndex index.
  *
  * Use case: min/max is rarely deleted.
  *
  * Supported operations:
  * + insert,delete,update = O(1)/O(N) if min/max / get=O(1)
  * + clear,size
  */
@SuppressWarnings("unchecked")
public abstract class SliceIndex<E extends MapEntry> extends HashIndex<E> {
    
    private int cmpOutcome;
    private Index<E> cmpIndex;
    private E cmpCandidate;

    SliceIndex(int indexId, Index<E> cmpIndex, boolean max) { 
        super(indexId, true); 
        this.cmpIndex = cmpIndex;
        this.cmpOutcome = (max ? 1 : -1);
        this.cmpCandidate = null;
    }

    @Override 
    public void insert(E e) {
        if (size == threshold) { _resize(); }
        int h = hash(e), b = h & (entries.length - 1);
        HashIndexEntry<E> p = entries[b], i = new HashIndexEntry<E>(h, e);
        e.indexRefs[indexId] = i;
        if (p == null) { 
            entries[b] = i; 
            size += 1; 
            return; 
        } else 
            do {
                if (p.hash == h && cmp(e, p.data) == 0) {
                    if (cmpIndex.cmp(e, p.data) == cmpOutcome) { 
                        p.data = e; 
                        e.indexRefs[indexId] = p; 
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
        @SuppressWarnings("unchecked")
        HashIndexEntry<E> i = (HashIndexEntry<E>) e.indexRefs[indexId]; 
        if (i == null || !_del(e, i)) return;
        e.indexRefs[indexId] = null;
        // Find a replacement candidate
        cmpCandidate = null;
        Function1<E, Unit> f = new JFun1<E, Unit>() { 
            @Override 
            public Unit apply(E e) { 
                if (cmpCandidate == null || 
                    cmpIndex.cmp(e, cmpCandidate) == cmpOutcome) {
                    cmpCandidate = e; 
                }
                return (Unit)null; 
            } 
        };
        cmpIndex.slice(e, f); 
        if (cmpCandidate != null) { insert(cmpCandidate); }
        else size -= 1; 
    }
}
