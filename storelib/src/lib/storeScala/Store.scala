package ddbt.lib.storeScala

import scala.reflect.ClassTag

/**
  * The store is the main structure to store entries. It requires at least one
  * index. Index usually retain all the data according to their specialization.
  * Index 0 should retain all data (and possibly be one of the fastest index).
  * Indices data structure can be dynamically adapted using the index() function.
  */
abstract sealed class IndexType

case object INone extends IndexType

// no index
case object IHash extends IndexType

// hash index, does not support range/min/max/median operations
case object IDirect extends IndexType

// [!IDU] direct index where e<e2 <=> e.hash<e2.hash, can be m
case object IArray extends IndexType

// [!IDU] sorted array, binary search, min/max/median and range
case object IBTree extends IndexType

// B-Tree index
case object IList extends IndexType

// Single-linked list
case object ISliceMin extends IndexType

// Operate over a slicing index and memorizes min/max [get()]
case object ISliceMax extends IndexType

// O(1) to delete any, O(N) to delete min/max
case object ISliceHeapMin extends IndexType

// Operate over a slicing index and store all elements in a heap
case object ISliceHeapMax extends IndexType

case object ISlicedHeapMed extends IndexType
abstract class EntryIdx[E <: Entry] {
  def cmp(e1: E, e2: E): Int;
  def hash(e: E): Int; // hash function for Hash, index for Array
  // Note: The hash function must take care of shuffling LSBs enough, no
  // re-shuffling is done in the Store. Some indices (IdxDirect) require
  // order(entries)=order(hash(entries)) to work correctly.
}
case class GenericOps(val cols: Seq[Int]) extends EntryIdx[GenericEntry] {
  def hash(e: GenericEntry): Int = {
    if (cols == Nil)
      throw new Exception("Cols should not be empty for GenOps")
    var h = 0;
    cols.foreach(i => h = h ^ (0x9e3779b9 + (h << 6) + (h >> 2) + e.map(i).hashCode()))
    h
  }

  def cmp(e1: GenericEntry, e2: GenericEntry): Int = {
    val colsToCompare = if (e1.map.size > e2.map.size) //e2 is sampleEntry
      e2.map.keysIterator
    else if (e1.map.size < e2.map.size) //e1 is sampleEntry
      e1.map.keysIterator
    else if (cols != Nil) //both are full entries. Cannot be slice
      cols.iterator //TPCC has the keys given(except for History) and will stop here
    else
      throw new Exception("Cols should not be empty for GenOps")
    for (i <- colsToCompare) {
      if (e1.map.get(i).get != e2.map.get(i).get) {
        return 1
      }
    }
    0
  }
}

case class GenericFixedRangeOps(val colsRange: Seq[(Int, Int, Int)]) extends EntryIdx[GenericEntry] {
  def hash(e: GenericEntry): Int = {
    if (colsRange == Nil)
      throw new Exception("Cols should not be empty for GenFixedOps")
    colsRange.foldLeft((0))((acc, cur) => (acc * (cur._3 - cur._2) + e.get[Int](cur._1) - cur._2))
    //Acc = (hash, weight)
    //Cur = (column_no, lower_bound, upper_bound)
    //hash' = hash * weight + (e[column_no] - lower_bound)
    //weight' = upper_bound - lower_bound
  }

  def cmp(e1: GenericEntry, e2: GenericEntry) = 0
}

case class GenericCmp[R](val cols: Seq[Int], val f: GenericEntry => R)(implicit order: Ordering[R]) extends EntryIdx[GenericEntry] {
  def hash(e: GenericEntry): Int = {
    var h = 16;
    cols.foreach(i => h = h * 41 + e.map(i).hashCode())
    h
  }

  def cmp(e1: GenericEntry, e2: GenericEntry): Int = {
    val v = order.compare(f(e1), f(e2))
    if (v < 0) -1 else if (v > 0) 1 else 0
  }
}

object EntryIdx {
  def apply[E <: Entry](h: (E => Int), c: ((E, E) => Int), name: String = ""): EntryIdx[E] = new EntryIdx[E] {
    override def cmp(e1: E, e2: E): Int = c(e1, e2)

    override def hash(e: E): Int = h(e)
  }

  def genericOps(cols: Seq[Int]): EntryIdx[GenericEntry] = GenericOps(cols)

  def genericFixedRangeOps(colsRange: Seq[(Int, Int, Int)]): EntryIdx[GenericEntry] = GenericFixedRangeOps(colsRange)

  def genericCmp[R: Ordering](cols: Seq[Int], f: GenericEntry => R): EntryIdx[GenericEntry] = GenericCmp(cols, f)
}
class Store[E <: Entry](val idxs: Array[Idx[E]], val ops: Array[EntryIdx[E]] = null)(implicit cE: ClassTag[E]) {
  def setInitialSizes(s: List[Int]): Unit = {
    var i = 0;
    while (i < n) {
      idxs(i) match {
        case hi: IdxHash[_] => hi._resize(s(i))
        //case shi: IdxSlicedHeap[_] => shi._resize(s(i))//GS
        case _ => ()
      }
      i += 1
    }
  }

  @inline private def time[R](f: String)(block: => R): R = {
    block
  }

  @inline private def time[R](f: String, idx: Int)(block: => R): R = {
    block
  }

  def this(n: Int)(implicit cE: ClassTag[E]) = this(new Array[Idx[E]](n), null)(cE)

  def this()(implicit cE: ClassTag[E]) = {
    this(0)(cE)
  }

  def this(n: Int, ops: Array[EntryIdx[E]])(implicit cE: ClassTag[E]) = this(new Array[Idx[E]](n), ops)(cE)

  private val n = idxs.length
  private val modified = new Array[Boolean](n)


  def filter(f: E => Boolean): Store[E] = ???

  def map[U <: Entry](f: E => U): Store[U] = ???

  def fold[U](zero: U)(f: (U, E) => U): U = ???

  //  def join[U <: Entry](s:Store[U],t:(U,E)=>Boolean):Store[TupleEntry[T,U]]

  def groupBy[K](p: E => K, f: (E, E) => E): Store[E] = ???

  def union(s: Store[E]): Store[E] = ???

  def unsafeInsert(ec: E): Unit = time("unsafeInsert") {
    if (ec == null) return;
    val e = ec.copy().asInstanceOf[E]
    var i = 0
    while (i < n) {
      if (idxs(i) != null) idxs(i).unsafeInsert(e)
      i += 1
    }
  }

  def insert(ec: E): Unit = time("insert") {
    if (ec == null) return;
    val orig = idxs(0).get(ec)
    if (orig == null) {
      val e = ec.copy().asInstanceOf[E]
      var i = 0
      while (i < n) {
        if (idxs(i) != null) idxs(i).unsafeInsert(e);
        i += 1;
      }
    } else {
      var i = 0
      while (i < n) {
        if (idxs(i).hashDiffers(orig, ec)) {
          idxs(i).delete(orig)
          modified(i) = true
        }
        i += 1
      }
      orig.copyFrom(ec)
      i = 0
      while (i < n) {
        if (modified(i)) {
          idxs(i).unsafeInsert(orig)
          modified(i) = false
        }
        i += 1
      }

    }
  }

  def update(e: E): Unit = time("update") {
    if (e == null) return;
    var i = 0;
    while (i < n) {
      if (idxs(i) != null) idxs(i).update(e);
      i += 1;
    }
  }

  def updateCopyDependent(e: E): Unit = time("update") {
    if (e == null) return;
    var i = 0;
    val ref = idxs(0).get(e)
    while (i < n) {
      if (idxs(i) != null) idxs(i).updateCopyDependent(e, ref);
      i += 1;
    }
  }

  def updateCopy(e: E): Unit = time("update") {
    if (e == null) return;
    var i = n - 1;
    while (i >= 0) {
      if (idxs(i) != null) idxs(i).updateCopy(e, idxs(0));
      i -= 1;
    }
  }

  // e already in the Store, update in foreach is _NOT_ supported

  def delete(e: E): Unit = time("delete") {
    if (e == null) return;
    var i = 0;
    while (i < n) {
      if (idxs(i) != null) idxs(i).delete(e);
      i += 1;
    }
  }

  def deleteCopy(e: E): Unit = time("delete") {
    if (e == null) return;
    var i = n - 1;
    while (i >= 0) {
      if (idxs(i) != null) idxs(i).deleteCopy(e, idxs(0));
      i -= 1;
    }
  }

  def deleteCopyDependent(e: E): Unit = time("delete") {
    if (e == null) return;
    var i = 0;
    val ref = idxs(0).get(e)
    while (i < n) {
      if (idxs(i) != null) idxs(i).deleteCopyDependent(ref);
      i += 1;
    }
  }

  // e already in the Store
  def get(idx: Int, key: E): E = time("get", idx) {
    if (key == null) return key;
    idxs(idx).get(key)
  }

  def getCopy(idx: Int, key: E): E = time("getCopy", idx) {
    if (key == null) return key;
    idxs(idx).getCopy(key)
  }

  def getCopyDependent(idx: Int, key: E): E = {
    if (key == null) return key;
    idxs(idx).getCopyDependent(key)
  }


  // assumes idxs(0) is the most efficient index
  def foreach(f: E => Unit): Unit = time("foreach") {
    idxs(0).foreach(f)
  }

  def foreachCopy(f: E => Unit): Unit = time("foreach") {
    idxs(0).foreachCopy(f)
  }


  def slice(idx: Int, key: E, f: E => Unit) = time("slice", idx) {
    if (key != null) {
      idxs(idx).slice(key, f)
    }
  }

  def sliceCopy(idx: Int, key: E, f: E => Unit) = time("slice", idx) {
    if (key != null) {
      idxs(idx).sliceCopy(key, f)
    }
  }

  def sliceCopyDependent(idx: Int, key: E, f: E => Unit) = time("slice", idx) {
    if (key != null) {
      idxs(idx).sliceCopyDependent(key, f)
    }
  }

  def range(idx: Int, min: E, max: E, withMin: Boolean = true, withMax: Boolean = true, f: E => Unit) = time("range", idx) {
    idxs(idx).range(min, max, withMin, withMax, f)
  }

  def delete(idx: Int, key: E): Unit = time("delete", idx) {
    slice(idx, key, e => delete(e))
  }

  def clear = time("clear") {
    var i = 0;
    while (i < n) {
      if (idxs(i) != null) idxs(i).clear;
      i += 1;
    }
  }

  def compact = time("compact") {
    var i = 0;
    while (i < n) {
      if (idxs(i) != null) idxs(i).compact;
      i += 1;
    }
  }

  def size = idxs(0).size

  def index(idx: Int, i: Idx[E]) {
    idxs(idx) = i
  }

  def index(idx: Int, tp: IndexType, unique: Boolean = false, sliceIdx: Int = -10) = {
    // sliceIdx is the underlying slice index for IBound
    val i: Idx[E] = tp match {
      case INone => null.asInstanceOf[Idx[E]]
      case IHash => new IdxHash[E](this, idx, unique)
      //        case IDirect | IArray =>
      //          //        if (idxs(0) == null) new Array[E](0)
      //          //      else {
      //          val data = new Array[E](sliceIdx); //SBJ: FIXME Using sliceIdx as size for now
      //          //        var x = 0;
      //          //        idxs(0).foreach { e => d(x) = e; x += 1 };

      case _=> ???
      //TODO: Will implement others later
      //          if (tp == IDirect) new IdxDirect[E](this, idx, unique, data) else new IdxArray[E](this, idx, unique, data)
      //        case IBTree => new IdxBTree(this, idx, unique)
      //        case IList => new IdxList(this, idx, unique)
      //        case ISliceMin => new IdxSliced(this, idx, sliceIdx, false)
      //        case ISliceMax => new IdxSliced(this, idx, sliceIdx, true)
      //        case ISliceHeapMin => new IdxSlicedHeap(this, idx, sliceIdx, false)
      //        case ISliceHeapMax => new IdxSlicedHeap(this, idx, sliceIdx, true)
      //        case ISlicedHeapMed => new IdxMedianHeap[E](this, idx, sliceIdx)
    }
    if (idxs(0) != null) tp match {
      case INone | IDirect | IArray => // nothing to do
      case _ => idxs(0).foreach(i.unsafeInsert(_))
    }
    idxs(idx) = i
    i
  }
  //TODO
  //    def getInfoStr: String = {
  //      val res = new StringBuilder("MapInfo => {\n")
  //      res.append("  size => ").append(if (idxs(0) == null) idxs(1).size else size).append("\n")
  //      res.append("  idxs => [\n")
  //      // totalTimers.foreach{ case (f,(t,count)) =>
  //      //   val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
  //      //   res.append("    time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
  //      // }
  //      idxs.zipWithIndex.foreach {
  //        case (idx, idxID) =>
  ////          if (idx == null) res.append(ind(ind("INone"))).append(",\n")
  ////          else {
  ////            res.append(ind(ind(idx.info)))
  ////            // res.append(" --> {\n")
  ////            // timersPerIndex.foreach{ case (f,fMap) =>
  ////            //   if(fMap.contains(idxID)) {
  ////            //     val (t,count) = fMap(idxID)
  ////            //     val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
  ////            //     res.append("      time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
  ////            //   }
  ////            // }
  ////            // res.append("    }\n")
  ////          }
  //      }
  //      res.append("]")
  //      res.append("}").toString
  //    }
}

