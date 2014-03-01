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
  public Entry(int n) { data = new Object[n]; }
  abstract public int cmp(int i, Entry e); // key comparison between entries
  abstract public int hash(int i); // hash function for Hash, index for Array
  abstract public Entry copy(); // returns a copy of the entry, for B-Trees only

  // Note: the hash function must take care of shuffling LSBs enough, no
  // re-shuffling is done in the store

  // Note: some indices may require order(entries)=order(hash(entries)) to work
  // correctly. Make sure you define it properly or don't use these indices.

  //abstract public boolean zero(); // the tuple can safely be deleted from the map
  //abstract public void combine(Entry e); // combine e in this (some kine of aggregation)

  // TODO: decouple cmp() and hash() such that the same Entry can be reused in maps with different indexes
}
