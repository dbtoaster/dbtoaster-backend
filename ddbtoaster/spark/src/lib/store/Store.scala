package ddbt.lib.spark.store

import scala.annotation.elidable
import scala.annotation.elidable.ASSERTION
import scala.collection.mutable.HashMap
import scala.reflect.ClassTag

/**
 * A store contrains entries and allow access through multiple indices.
 * + The entries need extends Entry and specialize to define its fields and
 *   projections that will be used for indexing.
 * + A store operates over entries and can only retrieve data through indices,
 *   hence at least one index must exist.
 * + Indices can be modified from one implementation to another to dynamically
 *   support different workloads during the application lifecycle.
 * Note: to enforce proper inlining, compile with the '-optimize' option.
 *
 * @author TCK
 */

// XXX: throw an exception if update/delete/insert during foreach ?
// XXX: do we want/require the fallback to packed mode for IDirect ?
// XXX: ignore strict comparison [cmp] to use only hash comparison in IDirect?

/** Index types that can be defined over the data */
abstract sealed class IndexType
case object INone   extends IndexType // no index
case object IHash   extends IndexType // hash index, does not support range/min/max/median operations


object Store {
  val GATHER_STATISTICS=false
  // DBToaster: create n+1 hash indexes (n=# projections)
  //def apply[E<:Entry](n:Int,ops:EntryOps[E]=null)(implicit cE:ClassTag[E]) = new Store((0 to n).map(i=>new IdxHash[E](ops,i,i==0)).toArray.asInstanceOf[Array[Idx[E]]])

  def ind(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll("\n? *$","").replaceAll("\n","\n"+i) }
  
  val totalTimersForStores:HashMap[String,HashMap[String,(Long,Int)]] = new HashMap[String,HashMap[String,(Long,Int)]]()
  val timersPerIndexForStores:HashMap[String,HashMap[String,HashMap[Int,(Long,Int)]]] = new HashMap[String,HashMap[String,HashMap[Int,(Long,Int)]]]()
  def printTimersInfo = {
    val res = new StringBuilder
    totalTimersForStores.foreach { case (store,totalTimer) =>
      res.append(store).append(": {\n")
      totalTimer.foreach{ case (op, (time,count)) =>
        res.append("  ").append(op).append(" (total time, # of calls, average time): (%d,%d,%d)".format(time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
      }
      timersPerIndexForStores.get(store) match {
        case Some(timersPerIndex) => timersPerIndex.foreach { case (op, indexTimers) =>
          indexTimers.foreach { case (idx, (time,count)) =>
            res.append("  ").append(op).append("(%d) (total time, # of calls, average time): (%d,%d,%d)".format(idx,time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
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
            indexTimers.foreach { case (idx, (time,count)) =>
              res.append("  ").append(op).append("(%d) (total time, # of calls, average time): (%d,%d,%d)".format(idx,time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
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
    totalTimersForStores.foreach { case (store,totalTimer) =>
      totalTimer.foreach{ case (op, (time,count)) =>
        res.append(store).append(",").append(op).append(",-1,%d,%d,%d".format(time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
      }
      timersPerIndexForStores.get(store) match {
        case Some(timersPerIndex) => timersPerIndex.foreach { case (op, indexTimers) =>
          indexTimers.foreach { case (idx, (time,count)) =>
            res.append(store).append(",").append(op).append(",%d,%d,%d,%d".format(idx,time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
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
            indexTimers.foreach { case (idx, (time,count)) =>
              res.append(store).append(",").append(op).append(",%d,%d,%d,%d".format(idx,time,count,(time.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int])).append("\n")
            }
          }
        }
      }
    }
    ind(res.toString)+"\n"
  }
  def addTimersFromStore(storeName:String, totalTimer:HashMap[String,(Long,Int)], timersPerIndex:HashMap[String,HashMap[Int,(Long,Int)]]) = {
    totalTimersForStores.get(storeName) match {
      case Some(currentTotalTimer) => {
        currentTotalTimer.foreach{ case (op, (currentTime,currentCount)) =>
          totalTimer.get(op) match {
            case Some((time,count)) => currentTotalTimer.update(op, (time+currentTime,count+currentCount))
            case None => //don't care
          }
        }
        totalTimer.foreach{ case (op, timeCount) =>
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
        currentTimersPerIndex.foreach{ case (op, currentIndexTimers) =>
          timersPerIndex.get(op) match {
            case Some(indexTimers) => {
              currentIndexTimers.foreach{ case (idx, (currentTime,currentCount)) =>
                indexTimers.get(idx) match {
                  case Some((time,count)) => currentIndexTimers.update(idx, (time+currentTime,count+currentCount))
                  case None => //don't care
                }
              }
              indexTimers.foreach{ case (idx, timeCount) =>
                currentIndexTimers.get(idx) match {
                  case Some(_) => //don't care
                  case None => currentIndexTimers += (idx -> timeCount)
                }
              }
            }
            case None => //don't care
          }
        }

        timersPerIndex.foreach{ case (op, indexTimers) =>
          currentTimersPerIndex.get(op) match {
            case Some(_) => //don't care
            case None => {
              val currentIndexTimers = new HashMap[Int,(Long,Int)]
              indexTimers.foreach{ case (idx, timeCount) =>
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
class Store[E<:MapEntry](val indices: Vector[Index[E]])(implicit cE:ClassTag[E]) {
  assert(indices.size > 0)

  @inline private def time[R](f:String)(block: => R):R = { block }
  @inline private def time[R](f:String, idx:Int)(block: => R):R = { block }

  // Compatibility with the old version
  val idxs = indices

  private val numIndices = indices.length
  
  def unsafeInsert(idx:Int,e:E):Unit = time("unsafeInsert") { if (e==null) return; indices(idx).unsafeInsert(e); var i=0; while(i < numIndices) { if (idx!=i && indices(i)!=null) indices(i).insert(e); i+=1; } }
  def insert(e:E):Unit = time("insert") { if (e==null) return; var i=0; while(i < numIndices) { if (indices(i)!=null) indices(i).insert(e); i+=1; } }
  def update(e:E):Unit = time("update") { if (e==null) return; var i=0; while(i < numIndices) { if (indices(i)!=null) indices(i).update(e); i+=1; } } // e already in the Store, update in foreach is _NOT_ supported
  def delete(e:E):Unit = time("delete") { if (e==null) return; var i=0; while(i < numIndices) { if (indices(i)!=null) indices(i).delete(e); i+=1; } } // e already in the Store
  def get(idx:Int,key:E):E = time("get",idx) { if (key==null) return key; indices(idx).get(key) }
  def foreach(f:E=>Unit):Unit = time("foreach") { indices(0).foreach(f) } // assumes idxs(0) is the most efficient index
  def slice(idx:Int,key:E,f:E=>Unit) = time("slice",idx) { if (key!=null) indices(idx).slice(key,f) }
  def range(idx:Int,min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) = time("range", idx) { indices(idx).range(min,max,withMin,withMax,f) }
  def delete(idx:Int,key:E):Unit = time("delete", idx) { slice(idx,key,e=>delete(e)) }
  def clear = time("clear") { var i=0; while(i < numIndices) { if (indices(i)!=null) indices(i).clear; i+=1; } }
  def compact = time("compact") { var i=0; while(i < numIndices) { if (indices(i)!=null) indices(i).compact; i+=1; } }
  def size = indices(0).size
  def ++(other: Store[E]) = time("concatenate") { other.foreach (insert); this }

  def getInfoStr:String = {
    val res = new StringBuilder("MapInfo => {\n")
    res.append("  size => ").append(if(indices(0) == null) indices(1).size else size).append("\n")
    res.append("  idxs => [\n")
    // totalTimers.foreach{ case (f,(t,count)) =>
    //   val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
    //   res.append("    time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
    // }
    indices.zipWithIndex.foreach { case (idx, idxID) =>
      if(idx == null) res.append(Store.ind(Store.ind("INone"))).append(",\n")
      else {
        res.append(Store.ind(Store.ind(idx.info)))
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

// ------------------------------------------
// Single hash-index entries
abstract class Entry1[E<:Entry1[E]] {
  val hash:Int // hash function
  var next:E = null.asInstanceOf[E]
  def merge(e:E):Boolean // combine in this the value of e if keys are equal
}

class Store1[E<:Entry1[E]]()(implicit cE:ClassTag[E]) {
  private final val init_capacity = 16
  private final val max_capacity = 1 << 30
  private final val load_factor = 0.75f
  private var size = 0
  private var data = new Array[E](init_capacity)
  private var threshold = (init_capacity * load_factor).toInt
  def add(e:E) {
    // resize array if needed
    if (size==threshold) {
      val n=data.size; if (n==max_capacity) threshold=java.lang.Integer.MAX_VALUE
      else { val new_capacity = n << 1; val d=new Array[E](new_capacity)
        var i=0; while(i < n) { var e=data(i); while (e!=null) { val ne=e.next; val b=e.hash&(new_capacity-1); e.next=d(b); d(b)=e; e=ne }; i+=1 }
        data=d; threshold=Math.min((new_capacity*load_factor).toInt, max_capacity+1);
      }
    }
    // insert and merge equivalent entries
    val b=e.hash&(data.length-1);
    var p=data(b);
    if (p==null) { data(b)=e; size+=1; }
    else do {
      if (p.merge(e)) return
      var n=p.next; if (n==null) { p.next=e; size+=1; return; }; p=n;
    } while (p!=null)
  }
  def foreach(f:E=>Unit) { val n=data.length; var i=0; while(i < n) { var e=data(i); while (e!=null) { f(e); e=e.next }; i+=1 } }
  def clear() { data=new Array[E](init_capacity); size=0; threshold=(init_capacity * load_factor).toInt }
}
