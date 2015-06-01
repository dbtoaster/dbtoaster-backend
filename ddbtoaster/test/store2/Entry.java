package store2;

/**
 * Abstract entry that is specialized for each map.
 * @author TCK
 */
public abstract class Entry<E extends Entry> {
  abstract public E copy();
  abstract public void copy(E e);

  // combines 'e' in this, returns true if record can be deleted
  //public boolean op(E e, int mode) { return false; }
}

//public E copy() {}; // for B+Tree, but not for B-Trees
