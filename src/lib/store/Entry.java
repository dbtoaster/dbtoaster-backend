package ddbt.lib.store;

/**
 * Abstract entry that is specialized for each map.
 * There is no key/value distinction as it is encoded by the indices.
 * Functions cmp() and hash() operate over the projection #i of the tuple;
 * this projection is actually never materialized.
 *
 * @author TCK
 */
public abstract class Entry {
  final Object[] data;
  public Entry(int n) { data=new Object[n]; }
  abstract public Entry copy(); // returns a copy of the entry, for B-Trees only
  abstract public Object[] elements();
  //abstract public boolean zero(); // the tuple can safely be deleted from the map
  //abstract public void merge(Entry e); // combine e in this (some kine of aggregation)

  // backward compatibility
  //public boolean zero() { return false; }
  //public void merge(Entry e) {} // again we create typing issues here
}
