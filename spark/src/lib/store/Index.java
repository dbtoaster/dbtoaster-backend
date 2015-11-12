package ddbt.lib.spark.store;

import scala.Function1;
import scala.Unit;

/**
 * Index interface. By default it emits a warning when an unsupported function
 * is called. Specific implementation are below.
 * 
 * @author TCK, Milos Nikolic
 */
public abstract class Index<E extends MapEntry> implements IndexOperations<E> {
		
	protected final int indexId;
	protected final boolean unique;
	protected int size;

	Index(int indexId, boolean unique) {
		this.indexId = indexId;
		this.unique = unique;
		this.size = 0;
	}
	
	protected void w(String n) {
		System.out.println(
			this.getClass().getName() + ": " + n + " not supported");
	}

	public void unsafeInsert(E e) {
		w("unsafeInsert");
	}

	public void insert(E e) {
		w("insert");
	}

	public void delete(E e) {
		w("delete");
	}

	public void update(E e) {
		w("update");
	} // reposition the entry if key/hash modified

	public E get(E key) {
		w("get");
		return null;
	} // returns the first element only

	public void foreach(Function1<E, Unit> f) {
		w("foreach");
	} // on all elements; warning: what about reordering updates?

	public void slice(E key, Function1<E, Unit> f) {
		w("slice");
	} // foreach on a slice

	public void range(E min, E max, boolean withMin, boolean withMax,
			Function1<E, Unit> f) {
		w("range");
	}

	public void clear() {
		w("clear");
	}

	public void compact() {
		w("compact");
	}
	
	public String info() {
		return this.getClass().getName() + 
			"(" + indexId + "," + (unique ? "unique" : "multiple") + ")";
	}
}
