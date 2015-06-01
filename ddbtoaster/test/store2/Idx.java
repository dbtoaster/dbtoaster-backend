package store2;
import scala.Function1;
import scala.Boolean;
import scala.Unit;

/**
 * Abstract index that get specialized for each map.
 * Functions cmp() and hash() operate over the projection of the tuple;
 * this projection is actually never materialized.
 *
 * @author TCK
 */
public abstract class Idx<E extends Entry<E>> {
  // function that must be implemented
  abstract protected int cmp(E e1, E e2);

  public Idx(boolean unique) { this.unique=unique; }
  protected final boolean unique;
  protected Store<E> store=null;
  protected int size;
  protected void w(String n) { System.out.println(this.getClass().getName()+": "+n+" not supported"); }
  public void insert(E e,Function1<E,Boolean> op) { size+=1; } // inserts, fails if uniqueness constraint is violated
  public void update(E e,Function1<E,Boolean> op) {} // reposition the entry if key/hash modified, fails if constraint is violated
  public void delete(E e) { size-=1; }
  public E get(E key) { return null; } // returns the first element only
  public void foreach(Function1<E,Unit> f) {} // on all elements; warning: what about reordering updates?
  public void slice(E key,Function1<E,Unit> f) {} // foreach on a slice
  public void range(E min, E max, boolean withMin, boolean withMax, Function1<E,Unit> f) {}
  public void clear() {}
  public void compact() {}
  public String info() { return this.toString()+" {\n  size => "+size+"\n}"; }
  @Override public String toString() { return this.getClass().getName()+"("+(unique?"unique":"multiple")+")"; }
}

class IdxNone<E extends Entry<E>> extends Idx<E> {
  IdxNone() { super(false); }
  protected int cmp(E e1, E e2) { return 1; }
}
