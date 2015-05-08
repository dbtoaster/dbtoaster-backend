package ddbt.lib.spark.store;

/**
 * Abstract entry that is specialized for each map. There is no key/value
 * distinction as it is encoded by the indices. 
 * 
 * @author TCK, Milos Nikolic
 */
public abstract class MapEntry {
	   
	final Object[] indexRefs;

	public MapEntry(int n) {
		indexRefs = new Object[n];
	}
}