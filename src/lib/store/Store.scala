package ddbt.lib.store
import scala.reflect._

import ddbt.Utils.ind

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
case object IDirect extends IndexType // [!IDU] direct index where e<e2 <=> e.hash<e2.hash, can be m
case object IArray  extends IndexType // [!IDU] sorted array, binary search, min/max/median and range
case object IBTree  extends IndexType // B-Tree index
case object IList   extends IndexType // Single-linked list
case object ISliceMin extends IndexType // Operate over a slicing index and memorizes min/max [get()]
case object ISliceMax extends IndexType // O(1) to delete any, O(N) to delete min/max
case object ISliceHeapMin extends IndexType // Operate over a slicing index and store all elements in a heap
case object ISliceHeapMax extends IndexType // O(N) to delete any, O(log N) to delete min/max

object Store {
  // DBToaster: create n+1 hash indexes (n=# projections)
  def apply[E<:Entry](n:Int)(implicit cE:ClassTag[E]) = new Store((0 to n).map(i=>new IdxHash[E](i,i==0)).toArray.asInstanceOf[Array[Idx[E]]])
}

/**
 * The store is the main structure to store entries. It requires at least one
 * index. Index usually retain all the data according to their specialization.
 * Index 0 should retain all data (and possibly be one of the fastest index).
 * Indices data structure can be dynamically adapted using the index() function.
 */
class Store[E<:Entry](val idxs:Array[Idx[E]])(implicit cE:ClassTag[E]) {
  assert(idxs.size > 0)
  def startPerfCounters = { perfMeasurement = true }
  def stopPerfCounters = { perfMeasurement = false }
  var perfMeasurement = true
  val totalTimers = new scala.collection.mutable.HashMap[String,Long]
  val timersPerIndex = new scala.collection.mutable.HashMap[String,scala.collection.mutable.HashMap[Int,Long]]
  def time[R](f: String)(block: => R): R = if(perfMeasurement) {
    val t0 = System.nanoTime()
    val result = block    // call-by-name
    val t1 = System.nanoTime()
    if(!totalTimers.contains(f)) {
      totalTimers += (f -> 0)
    }
    totalTimers.update(f, totalTimers(f)+(t1 - t0))
    result
  } else {
    block
  }
  def time[R](f: String, idx:Int)(block: => R): R = if(perfMeasurement) {
    val t0 = System.nanoTime()
    val result = block    // call-by-name
    val t1 = System.nanoTime()
    if(!timersPerIndex.contains(f)) {
      timersPerIndex += (f -> new scala.collection.mutable.HashMap[Int,Long])
    }
    val fMap = timersPerIndex(f)
    if(!fMap.contains(idx)) {
      fMap += (idx -> 0L)
    }
    fMap.update(idx, fMap(idx)+(t1 - t0))
    result
  } else {
    block
  }
  def this(n:Int)(implicit cE:ClassTag[E]) = this(new Array[Idx[E]](n))
  private val n = idxs.length
  def insert(e:E):Unit = {
    time("insert"){
      if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).insert(e); i+=1; }
    }
  }
  def update(e:E):Unit = {
    time("update"){
      if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).update(e); i+=1; } // e already in the Store, update in foreach is _NOT_ supported
    }
  }
  def delete(e:E):Unit = {
    time("delete"){
      if (e==null) return; var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).delete(e); i+=1; } // e already in the Store
    }
  }
  def get(idx:Int,key:E):E = {
    time("get",idx){
      if (key==null) return key; idxs(idx).get(key)
    }
  }
  def foreach(f:E=>Unit):Unit = {
    time("foreach"){
      idxs(0).foreach(f) // assumes idxs(0) is the most efficient index
    }
  }
  def slice(idx:Int,key:E,f:E=>Unit) = {
    time("slice",idx) {
      if (key!=null) idxs(idx).slice(key,f)
    }
  }
  def range(idx:Int,min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) = {
    time("range", idx) {
      idxs(idx).range(min,max,withMin,withMax,f)
    }
  }
  def delete(idx:Int,key:E):Unit = {
    time("delete", idx) {
      slice(idx,key,e=>delete(e))
    }
  }
  def clear = {
    time("clear"){
      var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).clear; i+=1; }
    }
  }
  def compact = {
    time("compact"){
      var i=0; while(i < n) { if (idxs(i)!=null) idxs(i).compact; i+=1; }
    }
  }
  def size = idxs(0).size
  def index(idx:Int,tp:IndexType,unique:Boolean=false,sliceIdx:Int= -1) { // sliceIdx is the underlying slice index for IBound
    val i:Idx[E] = tp match {
      case INone => null.asInstanceOf[Idx[E]]
      case IHash => new IdxHash[E](idx,unique)
      case IDirect|IArray => val data = if (idxs(0)==null) new Array[E](0) else { val d=new Array[E](idxs(0).size); var x=0; idxs(0).foreach{e=>d(x)=e; x+=1}; d }
                             if (tp==IDirect) new IdxDirect[E](idx,unique,data) else new IdxArray[E](idx,unique,data)
      case IBTree => new IdxBTree(idx,unique)
      case IList => new IdxList(idx,unique)
      case ISliceMin => new IdxSliced(idx,this.idxs,sliceIdx,false)
      case ISliceMax => new IdxSliced(idx,this.idxs,sliceIdx,true)
      case ISliceHeapMin => new IdxSlicedHeap(idx,this,sliceIdx,false)
      case ISliceHeapMax => new IdxSlicedHeap(idx,this,sliceIdx,true)
    }
    if (idxs(0)!=null) tp match {
      case INone|IDirect|IArray => // nothing to do
      case _ => idxs(0).foreach(i.insert(_))
    }
    idxs(idx) = i
  }

  def getInfoStr:String = {
    val res = new StringBuilder("MapInfo => {\n")
    //val perfStat = new StringBuilder("")
    res.append("  size => ").append(if(idxs(0) == null) idxs(1).size else size).append("\n")
    res.append("  idxs => [\n")
    totalTimers.foreach{ case (f,t) => 
      //perfStat.append(f).append(",").append(t/1000000).append(".").append((t/1000)%1000).append("\n")
      res.append("    time in ").append(f).append(" => ").append(t/1000000).append(".").append((t/1000)%1000).append(" ms").append("\n")
    }
    idxs.zipWithIndex.foreach { case (idx, idxID) =>
      if(idx == null) res.append(ind(ind("INone"))).append(",\n")
      else {
        res.append(ind(ind(idx.info))).append(" --> {\n")
        timersPerIndex.foreach{ case (f,fMap) =>
          if(fMap.contains(idxID)) {
            val t = fMap(idxID)
            res.append("      time in ").append(f).append(" => ").append(t/1000000).append(".").append((t/1000)%1000).append(" ms").append("\n")
            //perfStat.append(f).append(",").append(t/1000000).append(".").append((t/1000)%1000).append("\n")
          }
        }
        res.append("    }\n")//.append(ind(ind(perfStat.toString))).append(", \n")
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
class IdxDirect[E<:Entry](idx:Int,unique:Boolean,var data:Array[E])(implicit cE:ClassTag[E]) extends Idx[E](idx,unique) {
  private final val nil = null.asInstanceOf[E]
  private final val min_density = 0.2 // minimal array density to consider it for immediate election
  private var imm = false // immediate: hash=array_key
  private var off=0 // offset ajustement for minimal hash value in immediate mode
  private def prepare() { // O(n*log(n))
    size=data.length; if (size==0) return; data=data.sortWith((l:E,r:E)=>l.hash(idx) < r.hash(idx))
    imm = data(size-1).hash(idx)-data(0).hash(idx) < size/min_density; // compactness
    var i=1; while (i < size && imm) { imm &&= data(i-1).hash(idx) < data(i).hash(idx); i+=1 } // at most 1 element per cell
    if (imm) { off=data(0).hash(idx); val d=new Array[E](data(size-1).hash(idx)+1-off); data.foreach(e => d(e.hash(idx)-off)=e); data=d }
    else w("data is note dense, immediate mode")
  }
  prepare
  override def insert(e:E) { val h=e.hash(idx); if (imm && h>=off && h<=off+size-1) data(h-off)=e else w("insert") }
  override def delete(e:E) { val h=e.hash(idx); if (imm && h>=off && h<=off+size-1) data(h-off)=nil else w("delete") }
  override def get(key:E):E = if (data.length==0) nil else { val h=key.hash(idx)
    //println("(%s) data(%s-%s)".format(imm, h,off))
    if (imm) {
      val x = h-off
      if(x >= 0 && x < data.size) data(h-off) else nil
    }
    else { // binary search, finds position of leftmost element with the same hash
      val n=data.length; var s=0; var e=n; var m=0
      while (s < e) { m=(s+e)/2; val d=data(m); val h2=d.hash(idx)
        if (h2 < h) s=m+1; else if (h==h2 && key.cmp(idx,d)==0) return d; else e=m;
      }
      s+=1; // we already hit that element and failed
      while (s < data.size) { val d=data(s); if (d.hash(idx)!=h) return nil; else if (key.cmp(idx,d)==0) return d; s+=1 }
      nil
    }
  }
  override def foreach(f:E=>Unit) { val n=data.size; var i=0
    if (imm) while (i < n) { val e=data(i); if (e!=null) f(e); i+=1; }
    else while (i < n) { f(data(i)); i+=1; }
  }
  override def slice(key:E,f:E=>Unit) { val h=key.hash(idx)
    if (imm) { val d=data(h-off); if (d!=null) f(d) }
    else {
      val n=data.length; var s=0; var e=n; var m=0
      while (s < e) { m=(s+e)/2; val d=data(m); val h2=d.hash(idx); if (h2 < h) s=m+1; else e=m }
      do { val d=data(s); if (key.cmp(idx,d)!=0) return; f(d); s+=1 } while (s < size)
    }
  }
  override def range(min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) {
    val h0=min.hash(idx)+(if (withMin) 0 else 1); val h1=max.hash(idx)+(if (withMax) 1 else 0)
    if (imm) { var p=h0-off; val u=h1-off; while (p<u) { val d=data(p); if (d!=null) f(d); p+=1 } }
    else {
      val n=data.length; var s=0; var e=n; var m=0
      while (s < e) { m=(s+e)/2; val d=data(m); val h2=d.hash(idx); if (h2 < h0) s=m+1; else e=m }
      do { val d=data(s); if (d.hash(idx)>=h1) return; f(d); s+=1 } while (s < data.size)
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
class IdxArray[E<:Entry](idx:Int,unique:Boolean,var data:Array[E])(implicit cE:ClassTag[E]) extends Idx[E](idx,unique) {
  private final val nil = null.asInstanceOf[E]
  size=data.length
  data=data.sortWith((l:E,r:E)=>l.cmp(idx,r)<=0)
  override def get(key:E):E = if (size==0) nil else { var s=0; var e=size; var m=0
    while (s < e) { m=(s+e)/2; val d=data(m); val c=key.cmp(idx,d); if (c>0) s=m+1; else if (c==0) return d; else e=m; }; nil
  }
  override def foreach(f:E=>Unit) { val n=data.size; var i=0; while (i < n) { f(data(i)); i+=1; } }
  override def slice(key:E,f:E=>Unit) { var s=0; var e=size; var m=0
    while (s < e) { m=(s+e)/2; val c=key.cmp(idx,data(m)); if (c>0) s=m+1; else e=m }
    do { val d=data(s); if (key.cmp(idx,d)!=0) return; f(d); s+=1 } while (s < size)
  }
  override def range(min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) {
    var s=0; var e=size; var m=0
    while (s < e) { m=(s+e)/2; val c=min.cmp(idx,data(m)); if (c>0) s=m+1; else e=m }
    if (!withMin) while (s < size && min.cmp(idx,data(s))==0) s+=1
    val r=if (withMax) 0 else 1
    while (s < size) { val d=data(s); if (max.cmp(idx,d) < r) return; f(d); s+=1 }
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
class IdxBTree[E<:Entry](idx:Int,unique:Boolean)(implicit cE:ClassTag[E]) extends Idx[E](idx,unique) {
  private final val nil = null.asInstanceOf[E]
  private final val N = 8; assert(N>2) // N must be greater than two to make the split of two inner nodes sensible.
  private final val M = 8; assert(M>0) // Leaf nodes must be able to hold at least one element

  if (!unique) println("WARNING: BTree index only works with distinct keys")

  def dump() = root.dump("")
  abstract class Node() { var num=0; val data:Array[E]
    def dump(p:String="") {
      if (this.isInstanceOf[InnerNode]) {
        val cs = this.asInstanceOf[InnerNode].children
        cs(0).dump(p+"  ")
        var i=0; while (i < N) { println(p+data(i)); if (cs(i+1)!=null) cs(i+1).dump(p+"  "); i+=1 }
      } else {
        var i=0; while (i < M) { println(p+data(i)); i+=1 }
      }
    }
  }
  class LeafNode() extends Node { val data=new Array[E](M) } // Leaf nodes store values.
  class InnerNode() extends Node { val data=new Array[E](N); val children=new Array[Node](N+1) } // Inner nodes store pointers to other nodes interleaved with values
  case class Split(key:E, left:Node, right:Node) // Returned when insert splits the node at key

  private var root:Node = new LeafNode()

  // Simple linear search. Faster for small values of N or M
  // XXX: test with binary search

  // Leftmost element or next
  @inline private def _pos(e:E,n:Node,inner:Int):Int = { val data=n.data; val num=n.num; var k=0; while(k < num && data(k).cmp(idx,e) < inner) k+=1; k } // inner=0,1
  @inline private def leaf_insert_nonfull(node:LeafNode, e:E, index:Int) { // assert(index<=node.num); assert(node.num<M)
    if(index < M && node.data(index)!=null && unique && e.cmp(idx,node.data(index))==0) node.data(index)=e // Inserting a duplicate, overwrite the old one
    else { var i=node.num; while (i>index) { node.data(i)=node.data(i-1); i-=1 }; node.num+=1; size+=1; node.data(index)=e } // Inserted key is unique
    e.data(idx)=node
  }
  @inline private def inner_insert_nonfull(node:InnerNode,e:E) { //assert(node.num<N)
    val index=_pos(e,node,1)
    val split = _insert(node.children(index), e)
    if(split!=null) {
      if(index != node.num) { // Insertion not at the rightmost key
        node.children(node.num+1) = node.children(node.num);
        var i=node.num; while(i!=index) { node.children(i) = node.children(i-1); node.data(i) = node.data(i-1); i-=1 }
      }
      node.children(index) = split.left;
      node.children(index+1) = split.right;
      node.data(index) = split.key;
      node.num+=1;
    } // else the current node is not affected
  }

  @inline private def _insert(node:Node, e:E):Split = if (node.isInstanceOf[InnerNode]) {
    val n = node.asInstanceOf[InnerNode]
    // Early split if node is full. This is not the canonical algorithm for
    // B+ trees, but it is simpler and does not break the definition.
    if(n.num==N) {
      val treshold=(N+1)/2; val n2=new InnerNode()
      n2.num = n.num-treshold;
      var i=0; while(i < n2.num) {
        n2.data(i)=n.data(treshold+i);
        n2.children(i)=n.children(treshold+i); i+=1
      }
      n2.children(n2.num)=n.children(n.num)
      n.num=treshold-1
      // Set up the return variable
      val k=n.data(treshold-1);
      inner_insert_nonfull(if(e.cmp(idx,k) < 0) n else n2, e)
      Split(k,node,n2)
    } else { inner_insert_nonfull(n,e); null }
  } else { // leaf node
    val n = node.asInstanceOf[LeafNode]
    val i=_pos(e,node,0);
    if(n.num==M) { // The node was full. We must split it
      val treshold = (M+1)>>1;
      val n2=new LeafNode(); n2.num=n.num-treshold;
      var j=0; while(j < n2.num) { val x=n.data(treshold+j); x.data(idx)=n2; n2.data(j)=x; n.data(treshold+j)=nil; j+=1 }
      n.num=treshold;
      if(i < treshold) leaf_insert_nonfull(n,e,i) else leaf_insert_nonfull(n2,e,i-treshold)
      Split(n2.data(0).copy.asInstanceOf[E],node,n2) // Notify the parent about the split
    } else { leaf_insert_nonfull(n,e,i); null }
  }

  // Inserts a pair (key, value). If there is a previous pair with
  // the same key, the old value is overwritten with the new one.
  override def insert(e:E) {
    val split = _insert(root,e); if (split==null) return
    val r=new InnerNode(); r.num=1; r.data(0)=split.key
    r.children(0)=split.left; r.children(1)=split.right; root=r
  }
  override def get(key:E):E = { var n=root
    while (n.isInstanceOf[InnerNode]) { val ni=n.asInstanceOf[InnerNode]; n=ni.children(_pos(key,ni,1)) }
    val p=_pos(key,n,0); if(p < n.num && key.cmp(idx,n.data(p))==0) n.data(p) else nil
  }
  override def delete(e:E) {
    val n = e.data(idx).asInstanceOf[LeafNode]; if (n==null) return; var found=false; var i=0
    while (i < n.num) { if (n.data(i).eq(e)) found=true else if (found) n.data(i-1)=n.data(i); i+=1 }
    n.num-=1; n.data(n.num)=nil; size-=1 // assert(found)
  }
  override def update(e:E) {
    val n = e.data(idx).asInstanceOf[LeafNode]; if (n==null) return;
    if (!e.eq(n.data(0)) && !e.eq(n.data(n.num-1))) { // we might get lazy if the element is correctly positioned in the array
      var i=1; while(i < n.num-1 && !e.eq(n.data(i))) { i+=1 }; if (i==n.num-1) return; // not found, ignore
      if (n.data(i-1).cmp(idx,n.data(i)) < 1 && n.data(i).cmp(idx,n.data(i+1)) < 1) return; // well positionned
    }
    delete(e); insert(e)
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

  private def _for(f:E=>Unit,n:Node) {
    if (n.isInstanceOf[InnerNode]) { val cs=n.asInstanceOf[InnerNode].children; val num=n.num+1; var i=0; while(i < num) { _for(f,cs(i)); i+=1; } }
    else { val vs=n.data; val num=n.num; var i=0; while(i < num) { f(vs(i)); i+=1; } }
  }
  override def foreach(f:E=>Unit) = _for(f,root)

  private def _slice(key:E,f:E=>Unit,n:Node): Unit = if (n.isInstanceOf[InnerNode]) {
    val vs=n.data; val num=n.num; val cs=n.asInstanceOf[InnerNode].children
    var pc= -1; var nc=key.cmp(idx,vs(0)); if (nc<=0) _slice(key,f,cs(0))
    var i=0; while(i < num) { pc=nc; nc=key.cmp(idx,vs(i)); if (pc>=0 && nc<=0) _slice(key,f,cs(i)); i+=1 }
    if (nc>=0) _slice(key,f,cs(i))
  } else {
    val vs=n.data; val num=n.num; var i=0;
    while(i < num && key.cmp(idx,vs(i))>0) i+=1
    while(i < num && key.cmp(idx,vs(i))==0) { f(vs(i)); i+=1; }
  }
  override def slice(key:E,f:E=>Unit) = _slice(key,f,root)

  private def _range(min:E,max:E,cMin:Int,cMax:Int,f:E=>Unit,n:Node): Unit = if (n.isInstanceOf[InnerNode]) {
    val vs=n.data; val num=n.num; val cs=n.asInstanceOf[InnerNode].children
    if (min.cmp(idx,vs(0))<cMin) _range(min,max,cMin,cMax,f,cs(0));
    var i=1; while (i < num) { if (max.cmp(idx,vs(i-1))>cMax && min.cmp(idx,vs(i))<cMin) _range(min,max,cMin,cMax,f,cs(i)); i+=1; }
    if (max.cmp(idx,vs(i-1))>cMax) _range(min,max,cMin,cMax,f,cs(i));
  } else {
    val vs=n.data; val num=n.num; var i=0;
    while(i < num && min.cmp(idx,vs(i))>=cMin) i+=1
    while(i < num && max.cmp(idx,vs(i))>cMax) { f(vs(i)); i+=1; }
  }
  override def range(min:E,max:E,withMin:Boolean=true,withMax:Boolean=true,f:E=>Unit) = _range(min,max,if (withMin) 1 else 0,if (withMax) -1 else 0,f,root)
  override def clear() { root=new LeafNode(); size=0 }
}

/**
 * This is very similar to IdxSliced but has opposite performance. It's appropriate when most of the deletes are over min/max
 * Supported operations:
 * + insert,delete,update = O(log N) / get=O(1)
 * + clear,size
 */
class IdxSlicedHeap[E<:Entry](idx:Int,s:Store[E],sliceIdx:Int,max:Boolean)(implicit cE:ClassTag[E]) extends Idx[E](idx,true) {
  private final val nil = null.asInstanceOf[E]
  private final val default_capacity = 16
  private final val cRes = if (max) 1 else -1 // comparison result: "better"
  private final val hnil = null.asInstanceOf[Heap]
  @inline private def _meta(e:E):Heap = e.data(idx).asInstanceOf[Heap]

  // HashMap of Heap: for each partition of sliceIdx, we maintain one min/max heap
  private final val init_capacity = 128
  private final val max_capacity = 1 << 30
  private final val load_factor = 0.75f;
  private final val compact_factor = 0.05f
  private var data = new Array[Heap](init_capacity)
  private var threshold = (init_capacity * load_factor).toInt
  // Inlined functions
  @inline private def _hash(e:E) = { var h=e.hash(sliceIdx); h^=(h>>>20)^(h>>>12)^(h<<9); h^(h>>>7)^(h>>>4); }
  @inline private def _resize(new_capacity:Int) { val d=new Array[Heap](new_capacity)
    var i=0; val n=data.size; while(i < n) { var q=data(i); while (q!=null) { val nq=q.next; val b=q.hash&(new_capacity-1); q.next=d(b); d(b)=q; q=nq }; i+=1 }
    data=d; threshold=Math.min((new_capacity*load_factor).toInt, max_capacity+1);
  }
  //@inline
   private def _del(e:E): Boolean = {
    val q=_meta(e); q.remove(e)
    if (q.size==0) { // delete q
      val h=q.hash; val b=h&(data.length-1); var p=data(b); if (p.eq(q)) { data(b)=q.next; return true }
      else { while(!p.eq(null)) { if (p.next.eq(q)) { p.next=q.next; return true; } else p=p.next } }
    }
    false
  }

  override def insert(e:E) {
    if (size==threshold) { val n=data.length; if (n==max_capacity) threshold=java.lang.Integer.MAX_VALUE; else _resize(n << 1) }
    val h=_hash(e); val b = h&(data.length-1); var p=nil; var q=data(b);
    // add value to slice heap if exists
    while (q!=null) {
      if (q.hash==h && e.cmp(sliceIdx,q.get)==0) { q.add(e); return } // found slice's heap
      q=q.next
    }
    // new slice
    q = new Heap(); q.hash=h; q.next=data(b); q.add(e); data(b)=q; size+=1
  }
  override def delete(e:E) { if (_del(e)) size-=1 }
  override def update(e:E) {
    val q=_meta(e); val h=q.hash; val h2=_hash(e); if (h2==h) return; // did not change partition
    else if (_del(e)) { size-=1; insert(e) }
  }
  override def get(e:E):E = { val h=_hash(e); var q=data(h&(data.length-1)); while (q!=null) { if (q.hash==h && e.cmp(sliceIdx,q.get)==0) return q.get; q=q.next; }; nil }
  override def clear { var i=0; val n=data.length; while(i < n) { data(i)=hnil; i+=1; }; size=0 }
  override def compact = if (data.size*compact_factor>size) _resize(math.max(init_capacity,1 << (1+(math.log((size/load_factor))/math.log(2)).ceil.toInt)))

  class Heap { var hash:Int=0; var next:Heap=null.asInstanceOf[Heap] // Inherited as HashMap entry
    private var array = new Array[E](default_capacity + 1)
    var size = 0
    @inline private def _double { val tmp=array; array=new Array[E](array.length*2); System.arraycopy(tmp,0,array,0,tmp.length) }
    @inline private def _percolateDown(holeInput: Int) {
      var hole = holeInput; var child = hole << 1 // invariant: child = hole*2
      val tmp = array(hole)
      while (child <= size) {
        if (child!=size && array(child+1).cmp(idx,array(child))==cRes) child+=1
        if (array(child).cmp(idx,tmp)==cRes) array(hole)=array(child) else { array(hole)=tmp; return }
        hole=child; child=hole << 1
      }
      array(hole)=tmp
    }
    def get = array(1)
    def add(x:E) { if (size==array.length-1) _double; size+=1; x.data(idx)=this
      var hole=size; var h=hole>>1 // invariant: h = hole/2
      while (hole>1 && x.cmp(idx,array(h))==cRes) { array(hole)=array(h); hole=h; h=hole>>1 }
      array(hole)=x
    }
    def remove(x:E) {
      val p=if (x.eq(array(1))) 1 else array.indexOf(x); if (p== -1) return
      array(p)=array(size); array(size)=nil; size-=1; if (p < size) _percolateDown(p)
    }
    // def get = array(1)
  }
}

// ------------------------------------------
/*
// Temporary-only map
abstract class TempEntry[E<:TempEntry[_]] {
  final val hval = { var h=hash; h^=(h>>>20)^(h>>>12)^(h<<9); h^(h>>>7)^(h>>>4); }
  var next:E = null.asInstanceOf[E]
  def hash: Int // hash function
}
class TempStore[E<:TempEntry[E]](implicit cE:ClassTag[E]) {
  private final val init_capacity = 16
  private final val max_capacity = 1 << 30
  private final val load_factor = 0.75f;
  private var size = 0
  private var data = new Array[E](init_capacity)
  private var threshold = (init_capacity * load_factor).toInt
  def insert(e:E) {
    if (size==threshold) {
      val n=data.size;
      if (n==max_capacity) threshold=java.lang.Integer.MAX_VALUE
      else {
        val new_capacity = n << 1; val d=new Array[E](new_capacity)
        var i=0; while(i < n) { var e=data(i); while (e!=null) { val ne=e.next; val b=e.hval&(new_capacity-1); e.next=d(b); d(b)=e; e=ne }; i+=1 }
        data=d; threshold=Math.min((new_capacity*load_factor).toInt, max_capacity+1);
      }
    }
    val b=e.hval&(data.length-1); e.next=data(b); data(b)=e; size+=1;
  }
  def foreach(f:E=>Unit) { val n=data.length; var i=0; while(i < n) { var e=data(i); while (e!=null) { f(e); e=e.next }; i+=1 } }
}
*/
