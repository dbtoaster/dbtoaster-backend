package ddbt.tpcc.lib
import java.util._
import BinaryHeap._

object BinaryHeap {
  private final val DEFAULT_CAPACITY: Int = 16
}

class BinaryHeap[T:Manifest](reverse: Boolean=false)(implicit ord1: Ordering[T]) /*extends PriorityQueue[T]*/ {
  /**
   * Adds a value to the min-heap.
   */
  /*override*/ def add(value: T): Boolean = {
    if (size >= array.length - 1) {
      array = this.resize
    }
    size += 1
    val index: Int = size
    array(index) = value
    bubbleUp
    return true
  }

  /**
   * Returns true if the heap has no elements; false otherwise.
   */
  /*override*/ def isEmpty: Boolean = {
    return size == 0
  }

  /**
   * Returns (but does not remove) the minimum element in the heap.
   */
  /*override*/ def peek: T = {
    if (this.isEmpty) {
      throw new IllegalStateException
    }
    return array(1)
  }

  /**
   * Removes and returns the minimum element in the heap.
   */
  /*override*/ def remove: T = {
    val result: T = peek
    array(1) = array(size)
    array(size) = null.asInstanceOf[T]
    size -= 1
    bubbleDown
    return result
  }

  /**
   * Returns a String representation of BinaryHeap with values stored with
   * heap structure and order properties.
   */
  override def toString: String = {
    val res = new StringBuilder("(")
    var i = 0
    while(i < size) {
      res.append(array(i))
      i += 1
      if(i < size) res.append(", ")
    }
    res.append(")")
    return res.toString
  }

  override def equals(o: Any): Boolean = {
    //if (!(o.isInstanceOf[T])) return false
    val e: T = o.asInstanceOf[T]
    var i = 0
    while(i < size) {
      if(ord.compare(array(i), e) != 0) return false
      i+=1
    }
    true
  }

  /**
   * Performs the "bubble down" operation to place the element that is at the
   * root of the heap in its correct place so that the heap maintains the
   * min-heap order property.
   */
  protected def bubbleDown {
    var index: Int = 1
    while (hasLeftChild(index)) {
      var smallerChild: Int = leftIndex(index)
      if (hasRightChild(index) && ord.compare(array(leftIndex(index)), array(rightIndex(index))) > 0) {
        smallerChild = rightIndex(index)
      }
      if (ord.compare(array(index), array(smallerChild)) > 0) {
        swap(index, smallerChild)
      }
      else {
        return;
      }
      index = smallerChild
    }
  }

  /**
   * Performs the "bubble up" operation to place a newly inserted element
   * (i.e. the element that is at the size index) in its correct place so
   * that the heap maintains the min-heap order property.
   */
  protected def bubbleUp {
    var index: Int = this.size
    while (hasParent(index) && ord.compare(parent(index), array(index)) > 0) {
      swap(index, parentIndex(index))
      index = parentIndex(index)
    }
  }

  protected def hasParent(i: Int): Boolean = {
    i > 1
  }

  protected def leftIndex(i: Int): Int = {
    i * 2
  }

  protected def rightIndex(i: Int): Int = {
    i * 2 + 1
  }

  protected def hasLeftChild(i: Int): Boolean = {
    leftIndex(i) <= size
  }

  protected def hasRightChild(i: Int): Boolean = {
    rightIndex(i) <= size
  }

  protected def parent(i: Int): T = {
    array(parentIndex(i))
  }

  protected def parentIndex(i: Int): Int = {
    i / 2
  }

  protected def resize: Array[T] = {
    val tmpArr = array
    array = new Array[T](array.length * 2)
    var i = 0
    while(i < size) {
      array(i) = tmpArr(i)
      i += 1
    }
    array
  }

  protected def swap(index1: Int, index2: Int) {
    val tmp: T = array(index1)
    array(index1) = array(index2)
    array(index2) = tmp
  }

  protected var array: Array[T] = new Array[T](DEFAULT_CAPACITY)
  protected var size: Int = 0
  val ord: Ordering[T] = if(reverse) ord1.reverse else ord1
}