package ddbt.lib.store2

/**
 * Conflict handling semantics:
 * Insert:
 * - tab: fail if there is some conflict.
 * - map: get the first conflicting entry (iterating over all uniques) and update it, else insert
 * Update:
 * - tab: fail if there is some conflict (!= from current entry)
 * - map: if conflict, delete conflicting entry and update current one
 */
abstract class IndexType
object INone extends IndexType
object IHash extends IndexType

class Store[E<:Entry[E]](var idxs:Array[Idx[E]]) {
  //def this(idxs:Idx[E]*) = this(idxs.toArray)
  idxs.foreach(i=>i.store=this)
  assert(idxs.size>0)
  @inline private def time[R](f:String)(block: => R):R = { block }
  @inline private def time[R](f:String,idx:Int)(block: => R):R = { block }

  // Map's put() semantics
  // op is a function that operates on conflicting tuples in unique indexes: it
  // applies to conflicting tuples (unique indexes) which will then be deleted.
  def insert(e:E,op:E=>Boolean=null):Unit = time("insert") { if (e==null) return; var i=0; val n=idxs.size; do { idxs(i).insert(e,op); i+=1; } while(i<n) }
  def update(e:E,op:E=>Boolean=null):Unit = time("update") { if (e==null) return; var i=0; val n=idxs.size; do { idxs(i).update(e,op); i+=1; } while(i<n) } // assumes e is in the store already

  // DBMS uniqueness constraints check/fail semantics
  @inline private def chk(e:E):Boolean = { var i=0; val n=idxs.size; do { val ix=idxs(i); if (ix.unique && ix.get(e)!=null) return false; i+=1; } while(i<n); true }
  def chkInsert(e:E):Boolean = time("chkInsert") { val r=chk(e); if (r) insert(e); r }
  def chkUpdate(e:E):Boolean = time("chkUpdate") { val r=chk(e); if (r) update(e); r } // rollback yourself if it fails!

  def delete(e:E):Unit = time("delete") { if (e==null) return; var i=0; val n=idxs.size; do { idxs(i).delete(e); i+=1; } while(i<n) } // e already in the Store
  def get(idx:Int,key:E):E = time("get",idx) { if (key==null) return key; idxs(idx).get(key) }
  def foreach(f:E=>Unit) = time("foreach") { idxs(0).foreach(f) } // assumes idxs(0) is the most efficient index
  def slice(idx:Int,key:E,f:E=>Unit) = time("slice",idx) { if (key!=null) idxs(idx).slice(key,f) }
  def range(idx:Int,min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) = time("range",idx) { idxs(idx).range(min,max,withMin,withMax,f) }
  def delete(idx:Int,key:E):Unit = time("delete", idx) { slice(idx,key,e=>delete(e)) }
  def clear = time("clear") { var i=0; val n=idxs.size; while(i<n) { if (idxs(i)!=null) idxs(i).clear; i+=1; } }
  def compact = time("compact") { var i=0; val n=idxs.size; while(i<n) { if (idxs(i)!=null) idxs(i).compact; i+=1; } }
  def size = idxs(0).size

  def index(idx:Int,i:Idx[E]) { val n=idxs.size; if (idx==n) { val is=idxs; idxs = new Array[Idx[E]](n+1); System.arraycopy(is,0,idxs,0,n); idxs(n)=i; } else idxs(idx)=i }
/*
  def index(idx:Int,tp:IndexType,unique:Boolean=false,sliceIdx:Int= -1) { // sliceIdx is the underlying slice index for IBound
    val i:Idx[E] = tp match {
      case INone => new IdxNone[E]
      case IHash => new IdxHash[E](unique)
      / *
      case IDirect|IArray => val data = if (idxs(0)==null) new Array[E](0) else { val d=new Array[E](idxs(0).size); var x=0; idxs(0).foreach{e=>d(x)=e; x+=1}; d }
                             if (tp==IDirect) new IdxDirect[E](this,idx,unique,data) else new IdxArray[E](this,idx,unique,data)
      case IBTree => new IdxBTree(this,idx,unique)
      case IList => new IdxList(this,idx,unique)
      case ISliceMin => new IdxSliced(this,idx,sliceIdx,false)
      case ISliceMax => new IdxSliced(this,idx,sliceIdx,true)
      case ISliceHeapMin => new IdxSlicedHeap(this,idx,sliceIdx,false)
      case ISliceHeapMax => new IdxSlicedHeap(this,idx,sliceIdx,true)
    * /
    }
    if (idxs(0)!=null) tp match {
      //case IDirect|IArray => // nothing to do
      case _ => idxs(0).foreach(i.insert(_,null))
    }
    i.store=this; index(idx,i)
  }
*/
  def info:String = {
    "MapInfo => {\n"+idxs.map(i=>i.info).mkString(",\n")+"\n}"
/*
    res.append("  size => ").append(if(idxs(0) == null) idxs(1).size else size).append("\n")
    res.append("  idxs => [\n")
    // totalTimers.foreach{ case (f,(t,count)) =>
    //   val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
    //   res.append("    time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
    // }
    idxs.zipWithIndex.foreach { case (idx, idxID) =>
      if(idx == null) res.append(ind(ind("INone"))).append(",\n")
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
*/
  }
}





/*

/**
 * The store is the main structure to store entries. It requires at least one
 * index. Index usually retain all the data according to their specialization.
 * Index 0 should retain all data (and possibly be one of the fastest index).
 * Indices data structure can be dynamically adapted using the index() function.
 */
class Store[E<:Entry](val idxs:Array[Idx[E]])(implicit cE:ClassTag[E]) {
  def this(n:Int)(implicit cE:ClassTag[E]) = this(new Array[Idx[E]](n),null)(cE)
  def this(n:Int,ops:Array[EntryIdx[E]])(implicit cE:ClassTag[E]) = this(new Array[Idx[E]](n),ops)(cE)
  private val n = idxs.length
  def unsafeInsert(idx:Int,e:E):Unit = time("unsafeInsert") { if (e==null) return; idxs(idx).unsafeInsert(e); var i=0; while(i < n) { if (idx!=i && idxs(i)!=null) idxs(i).insert(e); i+=1; } }
  def insert(e:E):Unit = time("insert") { if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).insert(e); i+=1; } }
  def update(e:E):Unit = time("update") { if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).update(e); i+=1; } } // e already in the Store, update in foreach is _NOT_ supported
  def delete(e:E):Unit = time("delete") { if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).delete(e); i+=1; } } // e already in the Store
  def get(idx:Int,key:E):E = time("get",idx) { if (key==null) return key; idxs(idx).get(key) }
  def foreach(f:E=>Unit):Unit = time("foreach") { idxs(0).foreach(f) } // assumes idxs(0) is the most efficient index
  def slice(idx:Int,key:E,f:E=>Unit) = time("slice",idx) { if (key!=null) idxs(idx).slice(key,f) }
  def range(idx:Int,min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) = time("range", idx) { idxs(idx).range(min,max,withMin,withMax,f) }
  def delete(idx:Int,key:E):Unit = time("delete", idx) { slice(idx,key,e=>delete(e)) }
  def clear = time("clear") { var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).clear; i+=1; } }
  def compact = time("compact") { var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).compact; i+=1; } }
  def size = idxs(0).size
  def index(idx:Int,i:Idx[E]) { idxs(idx) = i }
  def index(idx:Int,tp:IndexType,unique:Boolean=false,sliceIdx:Int= -1) { // sliceIdx is the underlying slice index for IBound
    val i:Idx[E] = tp match {
      case INone => null.asInstanceOf[Idx[E]]
      case IHash => new IdxHash[E](this,idx,unique)
      case IDirect|IArray => val data = if (idxs(0)==null) new Array[E](0) else { val d=new Array[E](idxs(0).size); var x=0; idxs(0).foreach{e=>d(x)=e; x+=1}; d }
                             if (tp==IDirect) new IdxDirect[E](this,idx,unique,data) else new IdxArray[E](this,idx,unique,data)
      case IBTree => new IdxBTree(this,idx,unique)
      case IList => new IdxList(this,idx,unique)
      case ISliceMin => new IdxSliced(this,idx,sliceIdx,false)
      case ISliceMax => new IdxSliced(this,idx,sliceIdx,true)
      case ISliceHeapMin => new IdxSlicedHeap(this,idx,sliceIdx,false)
      case ISliceHeapMax => new IdxSlicedHeap(this,idx,sliceIdx,true)
    }
    if (idxs(0)!=null) tp match {
      case INone|IDirect|IArray => // nothing to do
      case _ => idxs(0).foreach(i.insert(_))
    }
    idxs(idx) = i
  }

  def getInfoStr:String = {
    val res = new StringBuilder("MapInfo => {\n")
    res.append("  size => ").append(if(idxs(0) == null) idxs(1).size else size).append("\n")
    res.append("  idxs => [\n")
    // totalTimers.foreach{ case (f,(t,count)) =>
    //   val avg = (t.asInstanceOf[Double] / count.asInstanceOf[Double]).asInstanceOf[Int]
    //   res.append("    time in ").append(f).append(" => (").append(t/1000000).append(".").append((t/1000)%1000).append(" ms spent for ").append(count).append(" calls) in average -> ").append(avg).append(" ns per call").append("\n")
    // }
    idxs.zipWithIndex.foreach { case (idx, idxID) =>
      if(idx == null) res.append(ind(ind("INone"))).append(",\n")
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
*/
