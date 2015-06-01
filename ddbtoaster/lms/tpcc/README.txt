ddbt.tpcc.tx1: contains base implementation for TPC-C
ddbt.tpcc.tx2: implementation with indices on key (by adding slice operation on maps)
ddbt.tpcc.tx3: removing duplicate accesses to an element in the HashMap (for reading and then updating a tuple)
ddbt.tpcc.tx4: implementation with indices on the combination of key and value (for more efficient slice operations)
ddbt.tpcc.tx5: specific data-structures for Min-Max queries (using SortedSet instead of HashSet)