package ddbt.lib.spark.store;

public interface IndexOperations <E extends MapEntry> {
	public int cmp(E e1, E e2); // key comparison between entries
	public int hash(E e);       // hash function for Hash, index for Array
	
	// Note: The hash function must take care of shuffling LSBs enough, no
	// re-shuffling is done in the Store. Some indices (IdxDirect) require
    // order(entries)=order(hash(entries)) to work correctly.
}