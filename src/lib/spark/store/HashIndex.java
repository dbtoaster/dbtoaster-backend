package ddbt.lib.spark.store;

import scala.Function1;
import scala.Unit;

/**
 * Implements a hashed index.
 *
 * Buckets elements are stored in a list. 
 * Default index unless special operations are required.
 * 
 * Supported operations: + insert,delete,update,get = O(1) + range = O(n)
 */

class HashIndexEntry<E extends MapEntry> { 
	int hash;
	E data;
	HashIndexEntry<E> next;
	
	HashIndexEntry(int hash, E data) {
		this.hash = hash;
		this.data = data;
	}
}

public abstract class HashIndex<E extends MapEntry> extends Index<E>  {
	
	private static final int init_capacity = 16;
	private static final int max_capacity = 1 << 30;
	private static final float compact_factor = 0.05f;	
	private final float load_factor;

	@SuppressWarnings("unchecked")
	private HashIndexEntry<E>[] newArray(int size) {
		return new HashIndexEntry[size];
	}
	
	protected HashIndexEntry<E>[] entries = newArray(init_capacity);
	protected int threshold;

	public HashIndex(int indexId, boolean unique, float factor) {
		super(indexId, unique);
		load_factor = factor;
		threshold = Math.round(init_capacity * load_factor);
	}

	public HashIndex(int indexId, boolean unique) {
		super(indexId, unique);
		load_factor = unique ? 0.75f : 4.0f;
		threshold = Math.round(init_capacity * load_factor);
	}
	
	// Private/inlined functions
	private void _resize(int new_capacity) {
		HashIndexEntry<E>[] newEntries = newArray(new_capacity);
		for (int i = 0, n = entries.length; i < n; ++i) {
			HashIndexEntry<E> e = entries[i], en;
			while (e != null) {
				en = e.next;
				int b = e.hash & (new_capacity - 1);
				e.next = newEntries[b];
				newEntries[b] = e;
				e = en;
			}
		}
		entries = newEntries;
		threshold = Math.min(Math.round(new_capacity * load_factor), 
							 max_capacity + 1);
	}

	protected void _resize() {
		int n = entries.length;
		if (n == max_capacity)
			threshold = Integer.MAX_VALUE;
		else
			_resize(n << 1);
	}

	protected boolean _del(E e, HashIndexEntry<E> i) {
		HashIndexEntry<E> p = i.next;
		if (p != null) {
			i.hash = p.hash;
			i.next = p.next;
			i.data = p.data;
			p.data.indexRefs[indexId] = i;
			return true;
		} // eat next child
		int h = i.hash, b = h & (entries.length - 1);
		p = entries[b];
		if (i == p) {
			entries[b] = null;
			return true;
		} // head of list
		else
			do {
				if (i == p.next) {
					p.next = null;
					return true;
				}
				p = p.next;
			} while (p != null); // tail
		return false;
	}

	// Public
	@Override
	public void unsafeInsert(E e) {
		if (size == threshold)
			_resize();
		int h = hash(e), b = h & (entries.length - 1);
		HashIndexEntry<E> i = new HashIndexEntry<E>(h, e);
		e.indexRefs[indexId] = i;
		i.next = entries[b];
		entries[b] = i;
		size += 1;
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
		} else if (!unique) {
			i.next = entries[b];
			entries[b] = i;
			size += 1;
			return;
		} else
			do { // unique
				if (p.hash == h && cmp(e, p.data) == 0) {
					p.data = e;
					e.indexRefs[indexId] = p;
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
		if (i != null && _del(e, i)) {
			e.indexRefs[indexId] = null;
			size -= 1;
		}
	}

	@Override
	public void update(E e) {
		@SuppressWarnings("unchecked")
		HashIndexEntry<E> i = (HashIndexEntry<E>) e.indexRefs[indexId];
		if (i != null && i.hash != hash(e) && _del(e, i)) {
			size -= 1;
			insert(e);
		}
	}

	@Override
	public E get(E key) {
		int h = hash(key);
		HashIndexEntry<E> e = entries[h & (entries.length - 1)];
		while (e != null && (e.hash != h || cmp(key, e.data) != 0))
			e = e.next;
		return e != null ? e.data : null;
	}

	@Override
	public void foreach(Function1<E, Unit> f) {
		E d;
		HashIndexEntry<E> e, en;
		for (int i = 0, n = entries.length; i < n; ++i) {
			e = entries[i];
			if (e != null)
				do {
					en = e.next;
					d = e.data;
					f.apply(d);
					e = en;
				} while (e != null);
		}
	}

	@Override
	public void slice(E key, Function1<E, Unit> f) {
		int h = hash(key);
		HashIndexEntry<E> e = entries[h & (entries.length - 1)];
		if (e != null)
			do {
				if (e.hash == h && cmp(key, e.data) == 0)
					f.apply(e.data);
				e = e.next;
			} while (e != null);
	}

	@Override
	public void range(E min, E max, boolean withMin, boolean withMax,
			Function1<E, Unit> f) {
		int cMin = withMin ? -1 : 0;
		int cMax = withMax ? 1 : 0;
		for (int i = 0, n = entries.length; i < n; ++i) {
			HashIndexEntry<E> e = entries[i], en;
			while (e != null) {
				en = e.next;
				if (cmp(e.data, min) > cMin && cmp(e.data, max) < cMax)
					f.apply(e.data);
				e = en;
			}
		}
	}

	@Override
	public void clear() {
		HashIndexEntry<E> z = null;
		for (int i = 0, n = entries.length; i < n; ++i) {
			entries[i] = z;
		}
		size = 0;
	}

	@Override
	public void compact() {
		if (entries.length * compact_factor > size)
			_resize(Math.max(init_capacity, 1 << ((int) Math.ceil(1 + (Math
					.log((size / load_factor)) / Math.log(2))))));
	}

	@Override
	public String info() {
		HashIndexEntry<E> e, en;
		int max = 0;
		int n = entries.length;
		for (int i = 0; i < n; ++i) {
			e = entries[i];
			int c = 0;
			if (e != null)
				do {
					en = e.next;
					++c;
					e = en;
				} while (e != null);
			if (c > max)
				max = c;
		}
		return "HashIndex(" + indexId + "," + (unique ? "unique" : "multiple")
				+ ") {\n  elements => " + size + "\n  buckets => " + n
				+ "\n  occupancy => " + (size * 1.0 / n)
				+ "\n  occupancyMax => " + max + "\n  loadFactor => "
				+ load_factor + "\n}";
	}

}

