package ddbt.lib.spark.store;

import scala.Function1;
import scala.Unit;

/**
 * IdxList is a simple sequential storage reminiscent of the disk era.
 * Lightweight singe-linked list (head --> tail), unique should be disabled
 * for best insertion performance (avoid checking duplicates).
 *
 * Use case: WAL log or temporary storage, sorted by least recently inserted.
 *
 * Supported operations:
 * + insert O(1)/O(N),delete O(N),update O(1)/O(N) / get=O(1)
 * + clear,size
 */
@SuppressWarnings("unchecked")
public abstract class ListIndex<E extends MapEntry> extends Index<E>  {

    private E head = null;

    private E tail = null;

    public ListIndex(int indexId, boolean unique) {
        super(indexId, unique);
    }

    @Override 
    public void insert(E e) {
        if (unique && head != null) {             
            if (e == head) {  // delete head
                head = (E)head.indexRefs[indexId]; 
                if (e == tail) tail = null; 
            }
            else { 
                E p = head; 
                do { 
                    E n = (E)p.indexRefs[indexId]; 
                    if (e == n) { 
                        p.indexRefs[indexId] = n.indexRefs[indexId]; 
                        if (n == tail) tail = p; 
                        break; 
                    } 
                    p = n; 
                } 
                while (p != null); 
            }
        }
        e.indexRefs[indexId] = null;
        if (tail != null) { tail.indexRefs[indexId] = e; tail = e; } 
        else { head = e; tail = e; }
    }

    @Override 
    public void delete(E e) {
        if (head == null) return;
        if (e == head) { 
            head = (E)head.indexRefs[indexId]; 
            if (e == tail) tail = null; 
        }
        else { 
            E p = head; 
            do { 
                E n = (E)p.indexRefs[indexId]; 
                if (e == n) { 
                    p.indexRefs[indexId] = n.indexRefs[indexId]; 
                    if (n == tail) { tail = p; }
                    p = null; 
                } 
                else p = n; 
            }
            while (p != null); 
        }
        e.indexRefs[indexId] = null;
    }

    @Override 
    public void update(E e) { 
        if (unique) { 
            delete(e); 
            insert(e); 
        }
        else w("update non-unique list index");
    }

    @Override 
    public E get(E key) { 
        if (head == null) return null;
        E p = head;         
        do { 
            if (cmp(key, p) == 0) return p; 
            p = (E)p.indexRefs[indexId]; 
        } while (p != null); 
        return null; 
    }

    @Override 
    public void foreach(Function1<E, Unit> f) { 
        if (head == null) return;
        E p = head; 
        do { 
            E n = (E)p.indexRefs[indexId]; 
            f.apply(p); 
            p = n; 
        } while (p != null); 
    }

    @Override 
    public void slice(E key, Function1<E, Unit> f) { 
        if (head == null) return;
        E p = head;
        do { 
            E n = (E)p.indexRefs[indexId]; 
            if (cmp(key, p) == 0) { f.apply(p); }
            p = n; 
        } while (p != null); 
    }
    
    @Override 
    public void clear() { head = null; tail = null; }

    @Override 
    public void compact() { } // nothing to do
}
