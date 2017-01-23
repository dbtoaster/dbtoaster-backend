package ddbt.lib.store

import java.util

import scala.reflect._
import ddbt.Utils.ind

import scala.collection.mutable.{ArrayBuffer, HashMap}

/**
  * A store contrains entries and allow access through multiple indices.
  * + The entries need extends Entry and specialize to define its fields and
  * projections that will be used for indexing.
  * + A store operates over entries and can only retrieve data through indices,
  * hence at least one index must exist.
  * + Indices can be modified from one implementation to another to dynamically
  * support different workloads during the application lifecycle.
  * Note: to enforce proper inlining, compile with the '-optimize' option.
  *
  * @author TCK
  */

// XXX: throw an exception if update/delete/insert during foreach ?
// XXX: do we want/require the fallback to packed mode for IDirect ?
// XXX: ignore strict comparison [cmp] to use only hash comparison in IDirect?

/** Index types that can be defined over the data */
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

// O(N) to delete any, O(log N) to delete min/max

/** Map-specific operations on entries */
abstract class EntryIdx[E <: Entry] {
  def cmp(e1: E, e2: E): Int;

  // key comparison between entries
  def hash(e: E): Int; // hash function for Hash, index for Array
  // Note: The hash function must take care of shuffling LSBs enough, no
  // re-shuffling is done in the Store. Some indices (IdxDirect) require
  // order(entries)=order(hash(entries)) to work correctly.
}

case class GenericOps(val cols: Seq[Int]) extends EntryIdx[GenericEntry] {
  def hash(e: GenericEntry): Int = {
    if (cols == Nil)
      throw new Exception("Cols should not be empty for GenOps")
    var h = 16;
    cols.foreach(i => h = h * 41 + e.map(i).hashCode())
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
    order.compare(f(e1), f(e2))
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

object Store {
  val GATHER_STATISTICS = false
  // DBToaster: create n+1 hash indexes (n=# projections)
  //def apply[E<:Entry](n:Int,ops:EntryOps[E]=null)(implicit cE:ClassTag[E]) = new Store((0 to n).map(i=>new IdxHash[E](ops,i,i==0)).toArray.asInstanceOf[Array[Idx[E]]])

  val totalTimersForStores: HashMap[String, HashMap[String, (Long, Int)]] = new HashMap[String, HashMap[String, (Long, Int)]]()
  val timersPerIndexForStores: HashMap[String, HashMap[String, HashMap[Int, (Long, Int)]]] = new HashMap[String, HashMap[String, HashMap[Int, (Long, Int)]]]()

  def printTimersInfo = {
    val res = new StringBuilder
    totalTimersForStores.foreach { case (store, totalTimer) =>
      res.append(store).append(": {\n")
      totalTimer.foreach { case (op, (time, count)) =>
        res.append("  ").append(op).append(" (total time, # of calls, average time): (%d,%d,%d)".format(time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
      }
      timersPerIndexForStores.get(store) match {
        case Some(timersPerIndex) => timersPerIndex.foreach { case (op, indexTimers) =>
          indexTimers.foreach { case (idx, (time, count)) =>
            res.append("  ").append(op).append("(%d) (total time, # of calls, average time): (%d,%d,%d)".format(idx, time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
          }
        }
        case None => //don't care
      }
      res.append("}\n")
    }
    timersPerIndexForStores.foreach { case (store, timersPerIndex) =>
      totalTimersForStores.get(store) match {
        case Some(_) => //don't care
        case None => {
          res.append(store).append(": {\n")
          timersPerIndex.foreach { case (op, indexTimers) =>
            indexTimers.foreach { case (idx, (time, count)) =>
              res.append("  ").append(op).append("(%d) (total time, # of calls, average time): (%d,%d,%d)".format(idx, time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
            }
          }
          res.append("}\n")
        }
      }
    }
    ind(res.toString)
  }

  def printTimersInfoCSV = {
    val res = new StringBuilder
    totalTimersForStores.foreach { case (store, totalTimer) =>
      totalTimer.foreach { case (op, (time, count)) =>
        res.append(store).append(",").append(op).append(",-1,%d,%d,%d".format(time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
      }
      timersPerIndexForStores.get(store) match {
        case Some(timersPerIndex) => timersPerIndex.foreach { case (op, indexTimers) =>
          indexTimers.foreach { case (idx, (time, count)) =>
            res.append(store).append(",").append(op).append(",%d,%d,%d,%d".format(idx, time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
          }
        }
        case None => //don't care
      }
    }
    timersPerIndexForStores.foreach { case (store, timersPerIndex) =>
      totalTimersForStores.get(store) match {
        case Some(_) => //don't care
        case None => {
          timersPerIndex.foreach { case (op, indexTimers) =>
            indexTimers.foreach { case (idx, (time, count)) =>
              res.append(store).append(",").append(op).append(",%d,%d,%d,%d".format(idx, time, count, (time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
            }
          }
        }
      }
    }
    ind(res.toString) + "\n"
  }

  def addTimersFromStore(storeName: String, totalTimer: HashMap[String, (Long, Int)], timersPerIndex: HashMap[String, HashMap[Int, (Long, Int)]]) = {
    totalTimersForStores.get(storeName) match {
      case Some(currentTotalTimer) => {
        currentTotalTimer.foreach { case (op, (currentTime, currentCount)) =>
          totalTimer.get(op) match {
            case Some((time, count)) => currentTotalTimer.update(op, (time + currentTime, count + currentCount))
            case None => //don't care
          }
        }
        totalTimer.foreach { case (op, timeCount) =>
          currentTotalTimer.get(op) match {
            case Some(_) => //don't care
            case None => currentTotalTimer += (op -> timeCount)
          }
        }
      }
      case None => totalTimersForStores += (storeName -> totalTimer)
    }

    timersPerIndexForStores.get(storeName) match {
      case Some(currentTimersPerIndex) => {
        currentTimersPerIndex.foreach { case (op, currentIndexTimers) =>
          timersPerIndex.get(op) match {
            case Some(indexTimers) => {
              currentIndexTimers.foreach { case (idx, (currentTime, currentCount)) =>
                indexTimers.get(idx) match {
                  case Some((time, count)) => currentIndexTimers.update(idx, (time + currentTime, count + currentCount))
                  case None => //don't care
                }
              }
              indexTimers.foreach { case (idx, timeCount) =>
                currentIndexTimers.get(idx) match {
                  case Some(_) => //don't care
                  case None => currentIndexTimers += (idx -> timeCount)
                }
              }
            }
            case None => //don't care
          }
        }

        timersPerIndex.foreach { case (op, indexTimers) =>
          currentTimersPerIndex.get(op) match {
            case Some(_) => //don't care
            case None => {
              val currentIndexTimers = new HashMap[Int, (Long, Int)]
              indexTimers.foreach { case (idx, timeCount) =>
                currentIndexTimers += (idx -> timeCount)
              }
              currentTimersPerIndex += (op -> currentIndexTimers)
            }
          }
        }
      }
      case None => timersPerIndexForStores += (storeName -> timersPerIndex)
    }
  }
}

/**
  * The store is the main structure to store entries. It requires at least one
  * index. Index usually retain all the data according to their specialization.
  * Index 0 should retain all data (and possibly be one of the fastest index).
  * Indices data structure can be dynamically adapted using the index() function.
  */
class Store[E <: Entry](val idxs: Array[Idx[E]], val ops: Array[EntryIdx[E]] = null)(implicit cE: ClassTag[E]) {
  // assert(idxs.size > 0)
  // def startPerfCounters = { perfMeasurement = true }
  // def stopPerfCounters = { perfMeasurement = false }
  // var perfMeasurement = Store.GATHER_STATISTICS
  // val totalTimers = new HashMap[String,(Long,Int)]
  // val timersPerIndex = new HashMap[String,HashMap[Int,(Long,Int)]]
  // def time[R](f: String)(block: => R): R = if(perfMeasurement) {
  //   val t0 = System.nanoTime()
  //   val result = block    // call-by-name
  //   val t1 = System.nanoTime()
  //   if(!totalTimers.contains(f)) {
  //     totalTimers += (f -> (0L,0))
  //   }
  //   val (currentTime,currentCount) = totalTimers(f)
  //   totalTimers.update(f, (currentTime+(t1 - t0),currentCount+1))
  //   result
  // } else {
  //   block
  // }
  // def time[R](f: String, idx:Int)(block: => R): R = if(perfMeasurement) {
  //   val t0 = System.nanoTime()
  //   val result = block    // call-by-name
  //   val t1 = System.nanoTime()
  //   if(!timersPerIndex.contains(f)) {
  //     timersPerIndex += (f -> new HashMap[Int,(Long,Int)])
  //   }
  //   val fMap = timersPerIndex(f)
  //   if(!fMap.contains(idx)) {
  //     fMap += (idx -> (0L,0))
  //   }
  //   val (currentTime,currentCount) = fMap(idx)
  //   fMap.update(idx, (currentTime+(t1 - t0),currentCount+1))
  //   result
  // } else {
  //   block
  // }
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

  def unsafeInsert(idx: Int, ec: E): Unit = time("unsafeInsert") {
    if (ec == null) return;
    val e = ec.copy().asInstanceOf[E]
    idxs(idx).unsafeInsert(e);
    var i = 0;
    while (i < n) {
      if (idx != i && idxs(i) != null) idxs(i).insert(e);
      i += 1;
    }
  }

  def insert(ec: E): Unit = time("insert") {
    if (ec == null) return;
    val e = ec.copy().asInstanceOf[E]
    var i = 0;
    while (i < n) {
      if (idxs(i) != null) idxs(i).insert(e);
      i += 1;
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
      case IDirect | IArray =>
        //        if (idxs(0) == null) new Array[E](0)
        //      else {
        val data = new Array[E](sliceIdx); //SBJ: FIXME Using sliceIdx as size for now
        //        var x = 0;
        //        idxs(0).foreach { e => d(x) = e; x += 1 };


        if (tp == IDirect) new IdxDirect[E](this, idx, unique, data) else new IdxArray[E](this, idx, unique, data)
      case IBTree => new IdxBTree(this, idx, unique)
      case IList => new IdxList(this, idx, unique)
      case ISliceMin => new IdxSliced(this, idx, sliceIdx, false)
      case ISliceMax => new IdxSliced(this, idx, sliceIdx, true)
      case ISliceHeapMin => new IdxSlicedHeap(this, idx, sliceIdx, false)
      case ISliceHeapMax => new IdxSlicedHeap(this, idx, sliceIdx, true)
    }
    if (idxs(0) != null) tp match {
      case INone | IDirect | IArray => // nothing to do
      case _ => idxs(0).foreach(i.insert(_))
    }
    idxs(idx) = i
    i
  }

  def getInfoStr: String = {
    val res = new StringBuilder("MapInfo => {\n")
    res.append("  size => ").append(if (idxs(0) == null) idxs(1).size else size).append("\n")
    res.append("  idxs => [\n")
    // totalTimers.foreach{ case (f,(t,count)) =>
    //   val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
    //   res.append("    time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
    // }
    idxs.zipWithIndex.foreach { case (idx, idxID) =>
      if (idx == null) res.append(ind(ind("INone"))).append(",\n")
      else {
        res.append(ind(ind(idx.info)))
        // res.append(" --> {\n")
        // timersPerIndex.foreach{ case (f,fMap) =>
        //   if(fMap.contains(idxID)) {
        //     val (t,count) = fMap(idxID)
        //     val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
        //     res.append("      time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
        //   }
        // }
        // res.append("    }\n")
      }
    }
    res.append("]")
    res.append("}").toString
  }
}

// Hash index has been moved to Store.java

/**
  * IdxDirect is usually an index over an integer where the hash is equal to the value. It can be
  * + Immediate: data(hash(e)) = e, array may contain null elements, does not support multi-values
  * + Packed: use binary search on key hash, does not contain null values, supports multi-value
  * To increase performance, make sure that your data fit in the immedate mode
  * For min/max/range operations to be meaningful, you need order(index) = order(hash)
  * Supported operations:
  * + implicit update(key cannot be modified)=O(1) / get=O(1)[immediate]_O(log(N))[packed] / min,max=O(1),median=O(N)[immediate]_O(1)[packed]
  * + foreach,slice,range / size
  */
class IdxDirect[E <: Entry](st: Store[E], idx: Int, unique: Boolean, var data: Array[E])(implicit cE: ClassTag[E]) extends Idx[E](st, idx, unique) {
  private final val nil = null.asInstanceOf[E]
  private final val min_density = 0.2
  // minimal array density to consider it for immediate election
  private var imm = true
  //SBJ: Changed from false to true
  // immediate: hash=array_key
  private var off = 0

  // offset ajustement for minimal hash value in immediate mode
  private def prepare() {
    // O(n*log(n))
    size = data.length;
    if (size == 0) return;
    data = data.sortWith((l: E, r: E) => ops.hash(l) < ops.hash(r))
    imm = ops.hash(data(size - 1)) - ops.hash(data(0)) < size / min_density;
    // compactness
    var i = 1;
    while (i < size && imm) {
      imm &&= ops.hash(data(i - 1)) < ops.hash(data(i));
      i += 1
    } // at most 1 element per cell
    if (imm) {
      off = ops.hash(data(0));
      val d = new Array[E](ops.hash(data(size - 1)) + 1 - off);
      data.foreach(e => d(ops.hash(e) - off) = e);
      data = d
    }
    else w("data is note dense, immediate mode")
  }

  //  prepare
  size = data.length

  override def unsafeInsert(e: E) {
    insert(e)
  }

  override def insert(e: E) {
    val h = ops.hash(e);
    if (imm && h >= off && h <= off + size - 1)
      data(h - off) = e
    else w("insert")
  }

  override def delete(e: E) {
    val h = ops.hash(e);
    if (imm && h >= off && h <= off + size - 1) data(h - off) = nil else w("delete")
  }

  override def get(key: E): E = if (data.length == 0) nil
  else {
    val h = ops.hash(key)
    //println("(%s) data(%s-%s)".format(imm, h,off))
    if (imm) {
      val x = h - off
      if (x >= 0 && x < data.size) data(h - off) else nil
    }
    else {
      // binary search, finds position of leftmost element with the same hash
      val n = data.length;
      var s = 0;
      var e = n;
      var m = 0
      while (s < e) {
        m = (s + e) / 2;
        val d = data(m);
        val h2 = ops.hash(d)
        if (h2 < h) s = m + 1; else if (h == h2 && ops.cmp(key, d) == 0) return d; else e = m;
      }
      s += 1; // we already hit that element and failed
      while (s < data.size) {
        val d = data(s);
        if (ops.hash(d) != h) return nil; else if (ops.cmp(key, d) == 0) return d;
        s += 1
      }
      nil
    }
  }

  override def foreach(f: E => Unit) {
    val n = data.size;
    var i = 0
    if (imm) while (i < n) {
      val e = data(i);
      if (e != null) f(e);
      i += 1;
    }
    else while (i < n) {
      f(data(i));
      i += 1;
    }
  }

  override def slice(key: E, f: E => Unit) {
    val h = ops.hash(key)
    if (imm) {
      val d = data(h - off);
      if (d != null) f(d)
    }
    else {
      val n = data.length;
      var s = 0;
      var e = n;
      var m = 0
      while (s < e) {
        m = (s + e) / 2;
        val d = data(m);
        val h2 = ops.hash(d);
        if (h2 < h) s = m + 1; else e = m
      }
      do {
        val d = data(s);
        if (ops.cmp(key, d) != 0) return;
        f(d);
        s += 1
      } while (s < size)
    }
  }

  override def sliceCopy(key: E, f: E => Unit) {
    val h = ops.hash(key)
    if (imm) {
      val d = data(h - off);
      if (d != null) f(d.copy().asInstanceOf[E])
    }
    else {
      val n = data.length;
      val entries = new ArrayBuffer[E]()
      var s = 0;
      var e = n;
      var m = 0
      while (s < e) {
        m = (s + e) / 2;
        val d = data(m);
        val h2 = ops.hash(d);
        if (h2 < h) s = m + 1; else e = m
      }
      do {
        val d = data(s);
        if (ops.cmp(key, d) != 0) return;
        entries += (d.copy().asInstanceOf[E]);
        s += 1
      } while (s < size)
      entries.foreach(f)
    }
  }

  override def range(min: E, max: E, withMin: Boolean = true, withMax: Boolean = true, f: E => Unit) {
    val h0 = ops.hash(min) + (if (withMin) 0 else 1);
    val h1 = ops.hash(max) + (if (withMax) 1 else 0)
    if (imm) {
      var p = h0 - off;
      val u = h1 - off;
      while (p < u) {
        val d = data(p);
        if (d != null) f(d);
        p += 1
      }
    }
    else {
      val n = data.length;
      var s = 0;
      var e = n;
      var m = 0
      while (s < e) {
        m = (s + e) / 2;
        val d = data(m);
        val h2 = ops.hash(d);
        if (h2 < h0) s = m + 1; else e = m
      }
      do {
        val d = data(s);
        if (ops.hash(d) >= h1) return;
        f(d);
        s += 1
      } while (s < data.size)
    }
  }

}

/**
  * IdxArray is a sorted index using the cmp(idx,_) function. Contrary to IdxDirect, it does not rely on
  * hash function. It is otherwise very similar to a packed/direct index.
  * Supported operations:
  * + implicit update(key cannot be modified)=O(1) / get=O(log(N)) / min,max,median=O(1)
  * + foreach,slice,range / size
  */
class IdxArray[E <: Entry](st: Store[E], idx: Int, unique: Boolean, var data: Array[E])(implicit cE: ClassTag[E]) extends Idx[E](st, idx, unique) {
  private final val nil = null.asInstanceOf[E]
  size = data.length
  data = data.sortWith((l: E, r: E) => ops.cmp(l, r) <= 0)

  override def unsafeInsert(e: E) {
    insert(e)
  }

  override def get(key: E): E = if (size == 0) nil
  else {
    var s = 0;
    var e = size;
    var m = 0
    while (s < e) {
      m = (s + e) / 2;
      val d = data(m);
      val c = ops.cmp(key, d);
      if (c > 0) s = m + 1; else if (c == 0) return d; else e = m;
    };
    nil
  }

  override def foreach(f: E => Unit) {
    val n = data.size;
    var i = 0;
    while (i < n) {
      f(data(i));
      i += 1;
    }
  }

  override def slice(key: E, f: E => Unit) {
    var s = 0;
    var e = size;
    var m = 0
    while (s < e) {
      m = (s + e) / 2;
      val c = ops.cmp(key, data(m));
      if (c > 0) s = m + 1; else e = m
    }
    do {
      val d = data(s);
      if (ops.cmp(key, d) != 0) return;
      f(d);
      s += 1
    } while (s < size)
  }

  override def sliceCopy(key: E, f: E => Unit): Unit = {
    var s = 0;
    var e = size;
    var m = 0
    while (s < e) {
      m = (s + e) / 2;
      val c = ops.cmp(key, data(m));
      if (c > 0) s = m + 1; else e = m
    }
    val entries = new ArrayBuffer[E]()
    do {
      val d = data(s);
      if (ops.cmp(key, d) != 0) return;
      entries += (d.copy().asInstanceOf[E]);
      s += 1
    } while (s < size)
    entries.foreach(f)
  }

  override def range(min: E, max: E, withMin: Boolean = true, withMax: Boolean = true, f: E => Unit) {
    var s = 0;
    var e = size;
    var m = 0
    while (s < e) {
      m = (s + e) / 2;
      val c = ops.cmp(min, data(m));
      if (c > 0) s = m + 1; else e = m
    }
    if (!withMin) while (s < size && ops.cmp(min, data(s)) == 0) s += 1
    val r = if (withMax) 0 else 1
    while (s < size) {
      val d = data(s);
      if (ops.cmp(max, d) < r) return;
      f(d);
      s += 1
    }
  }

}

/**
  * B+Tree based on the original H-Store paper implementation.
  * Note: because we do not distinguish key and values, we count as 'valid' only the leaf elements.
  * Supported operations:
  * + insert,delete,update=log(N) / get,min,max=log(N)
  * + foreach,slice,range / size
  */
// XXX: use System.arraycopy
class IdxBTree[E <: Entry](st: Store[E], idx: Int, unique: Boolean)(implicit cE: ClassTag[E]) extends Idx[E](st, idx, unique) {
  private final val nil = null.asInstanceOf[E]
  private final val N = 8;
  assert(N > 2)
  // N must be greater than two to make the split of two inner nodes sensible.
  private final val M = 8;
  assert(M > 0) // Leaf nodes must be able to hold at least one element

  if (!unique) println("WARNING: BTree index only works with distinct keys")

  override def unsafeInsert(e: E) {
    insert(e)
  }

  def dump() = root.dump("")

  abstract class Node() {
    var num = 0;
    val data: Array[E]

    def dump(p: String = "") {
      if (this.isInstanceOf[InnerNode]) {
        val cs = this.asInstanceOf[InnerNode].children
        cs(0).dump(p + "  ")
        var i = 0;
        while (i < N) {
          println(p + data(i));
          if (cs(i + 1) != null) cs(i + 1).dump(p + "  ");
          i += 1
        }
      } else {
        var i = 0;
        while (i < M) {
          println(p + data(i));
          i += 1
        }
      }
    }
  }

  class LeafNode() extends Node {
    val data = new Array[E](M)
  }

  // Leaf nodes store values.
  class InnerNode() extends Node {
    val data = new Array[E](N);
    val children = new Array[Node](N + 1)
  }

  // Inner nodes store pointers to other nodes interleaved with values
  case class Split(key: E, left: Node, right: Node)

  // Returned when insert splits the node at key

  private var root: Node = new LeafNode()

  // Simple linear search. Faster for small values of N or M
  // XXX: test with binary search

  // Leftmost element or next
  @inline private def _pos(e: E, n: Node, inner: Int): Int = {
    val data = n.data;
    val num = n.num;
    var k = 0;
    while (k < num && ops.cmp(data(k), e) < inner) k += 1;
    k
  }

  // inner=0,1
  @inline private def leaf_insert_nonfull(node: LeafNode, e: E, index: Int) {
    // assert(index<=node.num); assert(node.num<M)
    if (index < M && node.data(index) != null && unique && ops.cmp(e, node.data(index)) == 0) node.data(index) = e // Inserting a duplicate, overwrite the old one
    else {
      var i = node.num;
      while (i > index) {
        node.data(i) = node.data(i - 1);
        i -= 1
      };
      node.num += 1;
      size += 1;
      node.data(index) = e
    } // Inserted key is unique
    e.data(idx) = node
  }

  @inline private def inner_insert_nonfull(node: InnerNode, e: E) {
    //assert(node.num<N)
    val index = _pos(e, node, 1)
    val split = _insert(node.children(index), e)
    if (split != null) {
      if (index != node.num) {
        // Insertion not at the rightmost key
        node.children(node.num + 1) = node.children(node.num);
        var i = node.num;
        while (i != index) {
          node.children(i) = node.children(i - 1);
          node.data(i) = node.data(i - 1);
          i -= 1
        }
      }
      node.children(index) = split.left;
      node.children(index + 1) = split.right;
      node.data(index) = split.key;
      node.num += 1;
    } // else the current node is not affected
  }

  @inline private def _insert(node: Node, e: E): Split = if (node.isInstanceOf[InnerNode]) {
    val n = node.asInstanceOf[InnerNode]
    // Early split if node is full. This is not the canonical algorithm for
    // B+ trees, but it is simpler and does not break the definition.
    if (n.num == N) {
      val treshold = (N + 1) / 2;
      val n2 = new InnerNode()
      n2.num = n.num - treshold;
      var i = 0;
      while (i < n2.num) {
        n2.data(i) = n.data(treshold + i);
        n2.children(i) = n.children(treshold + i);
        i += 1
      }
      n2.children(n2.num) = n.children(n.num)
      n.num = treshold - 1
      // Set up the return variable
      val k = n.data(treshold - 1);
      inner_insert_nonfull(if (ops.cmp(e, k) < 0) n else n2, e)
      Split(k, node, n2)
    } else {
      inner_insert_nonfull(n, e);
      null
    }
  } else {
    // leaf node
    val n = node.asInstanceOf[LeafNode]
    val i = _pos(e, node, 0);
    if (n.num == M) {
      // The node was full. We must split it
      val treshold = (M + 1) >> 1;
      val n2 = new LeafNode();
      n2.num = n.num - treshold;
      var j = 0;
      while (j < n2.num) {
        val x = n.data(treshold + j);
        x.data(idx) = n2;
        n2.data(j) = x;
        n.data(treshold + j) = nil;
        j += 1
      }
      n.num = treshold;
      if (i < treshold) leaf_insert_nonfull(n, e, i) else leaf_insert_nonfull(n2, e, i - treshold)
      Split(n2.data(0).copy.asInstanceOf[E], node, n2) // Notify the parent about the split
    } else {
      leaf_insert_nonfull(n, e, i);
      null
    }
  }

  // Inserts a pair (key, value). If there is a previous pair with
  // the same key, the old value is overwritten with the new one.
  override def insert(e: E) {
    val split = _insert(root, e);
    if (split == null) return
    val r = new InnerNode();
    r.num = 1;
    r.data(0) = split.key
    r.children(0) = split.left;
    r.children(1) = split.right;
    root = r
  }

  override def get(key: E): E = {
    var n = root
    while (n.isInstanceOf[InnerNode]) {
      val ni = n.asInstanceOf[InnerNode];
      n = ni.children(_pos(key, ni, 1))
    }
    val p = _pos(key, n, 0);
    if (p < n.num && ops.cmp(key, n.data(p)) == 0) n.data(p) else nil
  }

  override def delete(e: E) {
    val n = e.data(idx).asInstanceOf[LeafNode];
    if (n == null) return;
    var found = false;
    var i = 0
    while (i < n.num) {
      if (n.data(i).eq(e)) found = true else if (found) n.data(i - 1) = n.data(i);
      i += 1
    }
    n.num -= 1;
    n.data(n.num) = nil;
    size -= 1 // assert(found)
  }

  override def update(e: E) {
    val n = e.data(idx).asInstanceOf[LeafNode];
    if (n == null) return;
    if (!e.eq(n.data(0)) && !e.eq(n.data(n.num - 1))) {
      // we might get lazy if the element is correctly positioned in the array
      var i = 1;
      while (i < n.num - 1 && !e.eq(n.data(i))) {
        i += 1
      };
      if (i == n.num - 1) return; // not found, ignore
      if (ops.cmp(n.data(i - 1), n.data(i)) < 1 && ops.cmp(n.data(i), n.data(i + 1)) < 1) return; // well positionned
    }
    delete(e);
    insert(e)
  }

  // Delete the given key and returns true. If not found, returns false.
  /*
  override def delete(e:E) {
    var node:Node=root; var d=depth
    do { val inner=node.asInstanceOf[InnerNode] node=inner.children(_pos(e,inner,1)); d-=1; } while(d>0)
    val leaf = node.asInstanceOf[LeafNode]
    val index = _pos(e,leaf,0)
    if(e.cmp(idx,leaf.data(index))==0) { var i=index+1; while(i < leaf.num) { leaf.data(i-1)=leaf.data(i); i+=1; }; leaf.num-=1 }
    size-=1
  }
  */

  private def _for(f: E => Unit, n: Node) {
    if (n.isInstanceOf[InnerNode]) {
      val cs = n.asInstanceOf[InnerNode].children;
      val num = n.num + 1;
      var i = 0;
      while (i < num) {
        _for(f, cs(i));
        i += 1;
      }
    }
    else {
      val vs = n.data;
      val num = n.num;
      var i = 0;
      while (i < num) {
        f(vs(i));
        i += 1;
      }
    }
  }

  override def foreach(f: E => Unit) = _for(f, root)

  private def _slice(key: E, f: E => Unit, n: Node): Unit = if (n.isInstanceOf[InnerNode]) {
    val vs = n.data;
    val num = n.num;
    val cs = n.asInstanceOf[InnerNode].children
    var pc = -1;
    var nc = ops.cmp(key, vs(0));
    if (nc <= 0) _slice(key, f, cs(0))
    var i = 0;
    while (i < num) {
      pc = nc;
      nc = ops.cmp(key, vs(i));
      if (pc >= 0 && nc <= 0) _slice(key, f, cs(i));
      i += 1
    }
    if (nc >= 0) _slice(key, f, cs(i))
  } else {
    val vs = n.data;
    val num = n.num;
    var i = 0;
    while (i < num && ops.cmp(key, vs(i)) > 0) i += 1
    while (i < num && ops.cmp(key, vs(i)) == 0) {
      f(vs(i));
      i += 1;
    }
  }

  private def _sliceCopy(key: E, f: E => Unit, n: Node): Unit = if (n.isInstanceOf[InnerNode]) {
    val vs = n.data;
    val num = n.num;
    val cs = n.asInstanceOf[InnerNode].children
    var pc = -1;
    var nc = ops.cmp(key, vs(0));
    if (nc <= 0) _slice(key, f, cs(0))
    var i = 0;
    while (i < num) {
      pc = nc;
      nc = ops.cmp(key, vs(i));
      if (pc >= 0 && nc <= 0) _slice(key, f, cs(i));
      i += 1
    }
    if (nc >= 0) _slice(key, f, cs(i))
  } else {
    val vs = n.data;
    val num = n.num;
    var i = 0;
    while (i < num && ops.cmp(key, vs(i)) > 0) i += 1
    val entries = new ArrayBuffer[E]()
    while (i < num && ops.cmp(key, vs(i)) == 0) {
      entries += vs(i).copy().asInstanceOf[E];
      i += 1;
    }
    entries.foreach(f);
  }

  override def slice(key: E, f: E => Unit) = _slice(key, f, root)

  override def sliceCopy(key: E, f: E => Unit): Unit = _sliceCopy(key, f, root)

  private def _range(min: E, max: E, cMin: Int, cMax: Int, f: E => Unit, n: Node): Unit = if (n.isInstanceOf[InnerNode]) {
    val vs = n.data;
    val num = n.num;
    val cs = n.asInstanceOf[InnerNode].children
    if (ops.cmp(min, vs(0)) < cMin) _range(min, max, cMin, cMax, f, cs(0));
    var i = 1;
    while (i < num) {
      if (ops.cmp(max, vs(i - 1)) > cMax && ops.cmp(min, vs(i)) < cMin) _range(min, max, cMin, cMax, f, cs(i));
      i += 1;
    }
    if (ops.cmp(max, vs(i - 1)) > cMax) _range(min, max, cMin, cMax, f, cs(i));
  } else {
    val vs = n.data;
    val num = n.num;
    var i = 0;
    while (i < num && ops.cmp(min, vs(i)) >= cMin) i += 1
    while (i < num && ops.cmp(max, vs(i)) > cMax) {
      f(vs(i));
      i += 1;
    }
  }

  override def range(min: E, max: E, withMin: Boolean = true, withMax: Boolean = true, f: E => Unit) = _range(min, max, if (withMin) 1 else 0, if (withMax) -1 else 0, f, root)

  override def clear() {
    root = new LeafNode();
    size = 0
  }


}

/**
  * This is very similar to IdxSliced but has opposite performance. It's appropriate when most of the deletes are over min/max
  * Supported operations:
  * + insert,delete,update = O(log N) / get=O(1)
  * + clear,size
  */
class IdxSlicedHeap[E <: Entry](st: Store[E], idx: Int, sliceIdx: Int, max: Boolean)(implicit cE: ClassTag[E]) extends Idx[E](st, sliceIdx, true) {
  private final val ops2 = st.ops(idx)
  private final val nil = null.asInstanceOf[E]
  private final val default_capacity = 16
  private final val cRes = if (max) 1 else -1
  // comparison result: "better"
  private final val hnil = null.asInstanceOf[Heap]

  @inline private def _meta(e: E): Heap = e.data(idx).asInstanceOf[Heap]

  override def unsafeInsert(e: E) {
    insert(e)
  }

  override def foreach(f: (E) => Unit): Unit = {
    for (d <- data) {
      var h = d;
      while (h != null) {
        h.foreach(f)
        h = h.next
      }
    }
  }

  // HashMap of Heap: for each partition of sliceIdx, we maintain one min/max heap
  private final val init_capacity = 128
  private final val max_capacity = 1 << 30
  private final val load_factor = 0.75f;
  private final val compact_factor = 0.05f
  private var data = new Array[Heap](init_capacity)
  private var threshold = (init_capacity * load_factor).toInt

  // Inlined functions
  @inline private def _hash(e: E) = {
    var h = ops.hash(e);
    h ^= (h >>> 20) ^ (h >>> 12) ^ (h << 9);
    h ^ (h >>> 7) ^ (h >>> 4);
  }

  @inline private def _resize(new_capacity: Int) {
    val d = new Array[Heap](new_capacity)
    var i = 0;
    val n = data.size;
    while (i < n) {
      var q = data(i);
      while (q != null) {
        val nq = q.next;
        val b = q.hash & (new_capacity - 1);
        q.next = d(b);
        d(b) = q;
        q = nq
      };
      i += 1
    }
    data = d;
    threshold = Math.min((new_capacity * load_factor).toInt, max_capacity + 1);
  }

  //@inline
  private def _del(e: E): Boolean = {
    val q = _meta(e);
    q.remove(e)
    if (q.size == 0) {
      // delete q
      val h = q.hash;
      val b = h & (data.length - 1);
      var p = data(b);
      if (p.eq(q)) {
        data(b) = q.next;
        return true
      }
      else {
        while (!p.eq(null)) {
          if (p.next.eq(q)) {
            p.next = q.next;
            return true;
          } else p = p.next
        }
      }
    }
    false
  }

  override def insert(e: E) {
    if (size == threshold) {
      val n = data.length;
      if (n == max_capacity) threshold = java.lang.Integer.MAX_VALUE; else _resize(n << 1)
    }
    val h = _hash(e);
    val b = h & (data.length - 1);
    var p = nil;
    var q = data(b);
    // add value to slice heap if exists
    while (q != null) {
      if (q.hash == h && ops.cmp(e, q.get) == 0) {
        q.add(e);
        return
      } // found slice's heap
      q = q.next
    }
    // new slice
    q = new Heap();
    q.hash = h;
    q.next = data(b);
    q.add(e);
    data(b) = q;
    size += 1
  }

  override def delete(e: E) {
    if (_del(e)) size -= 1
  }

  override def update(e: E) {
    val q = _meta(e);
    val h = q.hash;
    val h2 = _hash(e);
    if (h2 == h) return; // did not change partition
    else if (_del(e)) {
      size -= 1;
      insert(e)
    }
  }

  override def get(e: E): E = {
    val h = _hash(e);
    var q = data(h & (data.length - 1));
    while (q != null) {
      if (q.hash == h && ops.cmp(e, q.get) == 0) return q.get;
      q = q.next;
    };
    nil
  }

  override def clear {
    var i = 0;
    val n = data.length;
    while (i < n) {
      data(i) = hnil;
      i += 1;
    };
    size = 0
  }

  override def compact = if (data.size * compact_factor > size) _resize(math.max(init_capacity, 1 << (1 + (math.log((size / load_factor)) / math.log(2)).ceil.toInt)))

  class Heap {
    def foreach(f: (E) => Unit): Unit = {
      array.foreach(e => if (e != null) f(e))
    }

    var hash: Int = 0;
    var next: Heap = null.asInstanceOf[Heap]
    // Inherited as HashMap entry
    private var array = new Array[E](default_capacity + 1)
    var size = 0

    @inline private def _double {
      val tmp = array;
      array = new Array[E](array.length * 2);
      System.arraycopy(tmp, 0, array, 0, tmp.length)
    }

    @inline private def _percolateDown(holeInput: Int) {
      var hole = holeInput;
      var child = hole << 1 // invariant: child = hole*2
      val tmp = array(hole)
      while (child <= size) {
        if (child != size && ops2.cmp(array(child + 1), array(child)) == cRes) child += 1
        if (ops2.cmp(array(child), tmp) == cRes) array(hole) = array(child)
        else {
          array(hole) = tmp;
          return
        }
        hole = child;
        child = hole << 1
      }
      array(hole) = tmp
    }

    def get = array(1)

    def add(x: E) {
      if (size == array.length - 1) _double;
      size += 1;
      x.data(idx) = this
      var hole = size;
      var h = hole >> 1 // invariant: h = hole/2
      while (hole > 1 && ops2.cmp(x, array(h)) == cRes) {
        array(hole) = array(h);
        hole = h;
        h = hole >> 1
      }
      array(hole) = x
    }

    def remove(x: E) {
      val p = if (x.eq(array(1))) 1 else array.indexOf(x);
      if (p == -1) return
      array(p) = array(size);
      array(size) = nil;
      size -= 1;
      if (p < size) _percolateDown(p)
    }

    // def get = array(1)
  }

}

// ------------------------------------------
// Single hash-index entries
abstract class Entry1[E <: Entry1[E]] {
  val hash: Int
  // hash function
  var next: E = null.asInstanceOf[E]

  def merge(e: E): Boolean // combine in this the value of e if keys are equal
}

class Store1[E <: Entry1[E]]()(implicit cE: ClassTag[E]) {
  private final val init_capacity = 16
  private final val max_capacity = 1 << 30
  private final val load_factor = 0.75f
  private var size = 0
  private var data = new Array[E](init_capacity)
  private var threshold = (init_capacity * load_factor).toInt

  def add(e: E) {
    // resize array if needed
    if (size == threshold) {
      val n = data.size;
      if (n == max_capacity) threshold = java.lang.Integer.MAX_VALUE
      else {
        val new_capacity = n << 1;
        val d = new Array[E](new_capacity)
        var i = 0;
        while (i < n) {
          var e = data(i);
          while (e != null) {
            val ne = e.next;
            val b = e.hash & (new_capacity - 1);
            e.next = d(b);
            d(b) = e;
            e = ne
          };
          i += 1
        }
        data = d;
        threshold = Math.min((new_capacity * load_factor).toInt, max_capacity + 1);
      }
    }
    // insert and merge equivalent entries
    val b = e.hash & (data.length - 1);
    var p = data(b);
    if (p == null) {
      data(b) = e;
      size += 1;
    }
    else do {
      if (p.merge(e)) return
      var n = p.next;
      if (n == null) {
        p.next = e;
        size += 1;
        return;
      };
      p = n;
    } while (p != null)
  }

  def foreach(f: E => Unit) {
    val n = data.length;
    var i = 0;
    while (i < n) {
      var e = data(i);
      while (e != null) {
        f(e);
        e = e.next
      };
      i += 1
    }
  }

  def clear() {
    data = new Array[E](init_capacity);
    size = 0;
    threshold = (init_capacity * load_factor).toInt
  }
}
