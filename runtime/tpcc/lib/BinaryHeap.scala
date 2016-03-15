package ddbt.tpcc.lib
import java.util._
import BinaryHeap._

object BinaryHeap {
  private final val DEFAULT_CAPACITY: Int = 16
}

class BinaryHeap[T:Manifest](reverse: Boolean=false)(implicit ord1: Ordering[T]) /*extends PriorityQueue[T]*/ {
  /**
   * Insert into the priority queue, maintaining heap order.
   * Duplicates are allowed.
   * @param x the item to insert.
   * @exception Overflow if container is full.
   */
  def add(x: T) {
    if (isFull) doubleArray
    var hole: Int = ({
      currentSize += 1; currentSize
    })
    while (hole > 1 && ord.compare(x, array(hole / 2)) < 0) {
      array(hole) = array(hole / 2)
      hole /= 2
    }
    array(hole) = x
  }

  /**
   * Find the smallest item in the priority queue.
   * @return the smallest item, or null, if empty.
   */
  def peek: T = {
    if (isEmpty) throw new java.util.NoSuchElementException
    array(1)
  }

  /**
   * Remove the smallest item from the priority queue.
   * @return the smallest item, or null, if empty.
   */
  def remove: T = {
    if (isEmpty) new java.util.NoSuchElementException
    val minItem: T = peek
    array(1) = array(currentSize)
    currentSize -= 1
    percolateDown(1)
    return minItem
  }

  /**
   * Establish heap order property from an arbitrary
   * arrangement of items. Runs in linear time.
   */
  private def buildHeap {
    {
      var i: Int = currentSize / 2
      while (i > 0) {
        percolateDown(i)
        i -= 1
      }
    }
  }

  /**
   * Test if the priority queue is logically empty.
   * @return true if empty, false otherwise.
   */
  def isEmpty: Boolean = {
    return currentSize == 0
  }

  /**
   * Test if the priority queue is logically full.
   * @return true if full, false otherwise.
   */
  def isFull: Boolean = {
    return currentSize == array.length - 1
  }

  /**
   * Make the priority queue logically empty.
   */
  def makeEmpty {
    currentSize = 0
  }

  /**
   * Internal method to percolate down in the heap.
   * @param hole the index at which the percolate begins.
   */
  private def percolateDown(holeInput: Int) {
    var hole = holeInput
    var child: Int = 0
    val tmp: T = array(hole)
    while (hole * 2 <= currentSize) {
      child = hole * 2
      if (child != currentSize && ord.compare(array(child + 1), array(child)) < 0) {
        child += 1
      }
      if (ord.compare(array(child), tmp) < 0) array(hole) = array(child)
      else { 
        array(hole) = tmp
        return;
      }
      hole = child
    }
    array(hole) = tmp
  }

  private def doubleArray = {
    val tmpArray = array
    array = new Array[T]( array.length * 2 )
    var i = 0
    while(i < tmpArray.length) {
      array(i) = tmpArray(i)
      i += 1
    }
  }

  /**
   * Returns a String representation of BinaryHeap with values stored with
   * heap structure and order properties.
   */
  override def toString: String = {
    val res = new StringBuilder("(")
    val thisArr = array.clone
    val thisSize = currentSize
    while(!isEmpty) {
      res.append(remove)
      if(!isEmpty) res.append(", ")
    }
    array = thisArr
    currentSize = thisSize
    res.append(")")
    res.toString
  }

  override def equals(o: Any): Boolean = {
    //if (!(o.isInstanceOf[BinaryHeap[T]])) return false
    val e: BinaryHeap[T] = o.asInstanceOf[BinaryHeap[T]]
    if(currentSize != e.currentSize) return false
    val eArr = e.array.clone
    val thisArr = array.clone
    val eSize = e.currentSize
    val thisSize = currentSize
    while(!isEmpty) {
      val thisVal = remove
      val eVal = e.remove
      if(ord.compare(thisVal, eVal) != 0) {
        e.array = eArr
        array = thisArr
        return false
      }
    }
    e.array = eArr
    e.currentSize = eSize
    array = thisArr
    currentSize = thisSize
    true
  }

  private var currentSize: Int = 0
  private var array: Array[T] = new Array[T](DEFAULT_CAPACITY + 1)
  val ord: Ordering[T] = if(reverse) ord1.reverse else ord1
}