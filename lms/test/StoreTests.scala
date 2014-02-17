package storage
import org.scalatest.FunSpec
import ddbt.lib.store._

case class E(var _1:Int, var _2:Int, var _3:String) extends Entry(2) {
  def cmp(i:Int, e0:Entry) = { val e=e0.asInstanceOf[E]; if (i==0) (if (_1<e._1) -1 else if (_1==e._1) 0 else 1) else if (i==1) (if (_2<e._2) -1 else if (_2==e._2) 0 else 1) else 0 }
  def hash(i:Int) = if (i==0) _1 else if (i==1) _2 else 0
  def copy = E(_1,_2,_3)
}

class StoreTests extends FunSpec {
  val N = 5
  val ks = (0 until N).map(x=>E(x,x,""))
  val ts = Array[IndexType](IHash, IDirect, IArray, IBTree)
  def test_access(s:Store[E],sl_n:Int) {
    assert(s.size==N*N,"size()")
    var n=0; s.foreach(x=>n+=1); assert(n==N*N,"foreach()")
    ks.foreach{k=> assert(s.get(0,k)!=null,"get()"); n=0; s.slice(0,k,x=>n+=1); assert(n==sl_n,"slice()") }
  }
  def test_insdel(s:Store[E],sl_n:Int,uniq:Boolean) {
    var es:List[E] = Nil
    //s.foreach{e=>es=e::es; s.delete(e) }; assert(s.size==0,"delete()")

    s.foreach{e=>es=e::es}
    es=scala.util.Random.shuffle(es)
    es.foreach{e=>s.delete(e)}; assert(s.size==0,"delete()")

    es.foreach(e=>s.insert(e)); assert(s.size==es.size,"insert()")
    es.foreach(e=>s.insert(e)); assert(s.size==(if (uniq) es.size else 2*es.size),"unique")
    s.clear; es.foreach(e=>s.insert(e))
    test_access(s,sl_n)
  }
  def test_update(s:Store[E],sl_n:Int) { var n=0
    var es:List[E] = Nil; s.foreach{e=>es=e::es} // WARNING: update in foreach not supported
    es.foreach{e=>e._1+=(N*N); s.update(e)}
    ks.foreach{k=>assert(s.get(0,k)==null); n=0; s.slice(0,k,x=>n+=1); assert(n==0,"update() 1") }
    es.foreach{e=>e._1=(N*N)+N-1-e._1; s.update(e)}
    ks.foreach{k=>assert(s.get(0,k)!=null); n=0; s.slice(0,k,x=>n+=1); assert(n==sl_n,"update() 2") }
  }
  def test_range(s:Store[E],sl_n:Int) {
    var n=0; if (N<4) { println("test_range skipped"); return; }
    n=0; s.range(0,ks(1),ks(4),true,true,e=>n+=1); assert(n==sl_n*4,"range(true,true)");
    n=0; s.range(0,ks(1),ks(4),false,true,e=>n+=1); assert(n==sl_n*3,"range(false,true)");
    n=0; s.range(0,ks(1),ks(4),true,false,e=>n+=1); assert(n==sl_n*3,"range(true,false)");
    n=0; s.range(0,ks(1),ks(4),false,false,e=>n+=1); assert(n==sl_n*2,"range(false,false)");
  }
  /*
  def test_min_max(s:Store[E],uniq:Boolean) {
    assert(s.getMin(0)._1==0,"getMin()")
    assert(s.getMax(0)._1==(if (uniq) N*N-1 else N-1),"getMax()")
  }
  */
  /*
  def test_median(s:Store[E]) {
    var vs = List[Int](); s.foreach(e=>vs=e._1::vs)
    val m = vs.sorted.apply(vs.size/2); assert(s.getMedian(0)._1==m)
  }
  */
  // XXX: test prev and next
  def text_prev_next(s:Store[E]) {}

  def store(t:IndexType,uniq:Boolean,n:Int=1) = {
    val s = new Store[E](n);
    s.index(0,t match { case IHash|IBTree=>t case _ => IHash } ,uniq)
    (0 until N*N) foreach { x => s.insert(if (uniq) E(x,x,"foo") else E(x%N,x/N,"foo")) }
    s.index(0,t,uniq); s
  }
  def test(uniq:Boolean) {
    ts.foreach{ t =>
      val s = store(t,uniq)
      val sl_n = if (uniq) 1 else N
      //if (t!=IBounds)
      it(t+" access") { test_access(s,sl_n) }
      if (t!=IHash) {
        //if (t!=IBounds)
        it(t+" range") { test_range(s,sl_n) }
        //it(t+" min_max") { test_min_max(s,uniq) }
      }
      //if (t==IArray) it(t+" median") { test_median(s) }
      t match { case IHash|IBTree /*|ISplay*/ =>
        it(t+" update") { test_update(s,sl_n) }
        it(t+" insdel") { test_insdel(s,sl_n,uniq) }
        case _ => }
    }
  }

  describe("Multi-key store") { test(false) }
  describe("Unique key store") { test(true) }
  describe("Slice min/max") {
    def sl(t:IndexType,ss:Int) {
      val s=store(IHash,false,2); s.index(1,t,true,0)
      (0 until N) foreach { x => s.delete(s.get(1,ks(x))) }
      (0 until N) foreach { x => assert(s.get(1,ks(x))._2==ss); }
    }
    it("Min") { sl(ISliceMin,1) }
    it("Max") { sl(ISliceMax,N-2) }
    it("HeapMin") { sl(ISliceHeapMin,1) }
    it("HeapMax") { sl(ISliceHeapMax,N-2) }
  }
  describe("List") {
    val s = new Store[E](1); s.index(0,IList,false);
    (0 until N*N) foreach { x => s.insert(E(x,x,"foo")) }
    var es:List[E]=Nil; (0 until N) foreach { x => es=s.get(0,ks(x))::es }; es.foreach { e=> s.delete(e) }
    var n=0; s.foreach{ x=>n+=1 }; assert(n==N*(N-1))
  }

  describe("Store2") {


/*
    val s = new Store[SEntry3_III](2);
    val x0 = new storage.Store[SEntry3_III](2)
    x0.index(0,IHash,false)
    x0.index(1,ISliceMin,false,0)
    (1 to 10) foreach { y=>
      (2101 to 3000) foreach { x=>
        s.insert(SEntry3_III(y,x,1))
      }
    }
    println("Ready")
    s.insert(SEntry3_III(3001,10,1))
    s.insert(SEntry3_III(3001,2,1))
    s.insert(SEntry3_III(3001,3,1))
    s.insert(SEntry3_III(3001,6,1))
    s.insert(SEntry3_III(3001,8,1))
    s.insert(SEntry3_III(3001,9,1))
    s.insert(SEntry3_III(3002,3,1))
    s.delete(SEntry3_III(3000,1,1))
    s.insert(SEntry3_III(2999,1,1))
    s.get(1,SEntry3_III(0,2,1))
    println("Done")
*/
  }

  /*
  describe("Store1") {
    val s = new Store[E](2);
    s.index(0,IHash);
    s.index(1,INone);
    (0 until 100) foreach { x => s.insert(E(x%10,x/10,"foo")) }
    s.index(1,IHash);
    it("Count elements") {
      assert(s.size==100)
      val e = s.get(0,ks(4)); assert(e!=null)
      s.delete(e); assert(s.size==99)
      s.insert(e); assert(s.size==100)
    }
    it("Hold elements") { var n=0; s.foreach{e=> n+=1 }; assert(n==100) }
    it("Slice elements") { var n=0; s.slice(0,ks(2),e=>n+=1); assert(n==10) }
    it("Converts elements") {
      s.index(0,IArray); assert(s.idxs(0).isInstanceOf[IdxArray[_]])
      var n=0; s.slice(0,ks(7),e=>n+=1); assert(n==10)
      s.index(0,IHash); assert(s.size==100)
    }
    it("Array min/max/range") {
      s.index(0,IArray); s.index(1,IArray);
      assert(s.getMin(0)._1==0)
      assert(s.getMax(0)._1==9)
      assert(s.getMin(1)._2==0)
      assert(s.getMax(1)._2==9)
      var n=0;
      n=0; s.range(0,ks(1),ks(4),true,true,x=>n+=1); assert(n==40)
      n=0; s.range(1,ks(7),ks(9),true,true,x=>n+=1); assert(n==30)
      s.index(0,IHash); s.index(1,IHash);
    }
  }
  */
}

/*
case class SEntry3_III(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0) extends storage.Entry(3) {
  def hash(i: Int):Int = if(i == 0) _2 * 0xcafebabe + _3 else if(i == 1) _1 else 0xcafebabe
  def cmp(i: Int, e0:Entry):Int = { val e=e0.asInstanceOf[SEntry3_III]
    if(i == 0) { if(_2 == e._2 && _3 == e._3) 0 else 1 }
    else if(i == 1) { if(_1 < e._1) 1 else if(_1 > e._1) -1 else 0 } else 0
  }
  def copy = SEntry3_III(_1, _2, _3)
}

object Test {
  def main(args:Array[String]) { //val t=new StoreTests
    val s = new storage.Store[SEntry3_III](2)
    s.index(0,IHash,false)
    s.index(1,ISliceMin,false,0)
    (1 to 10) foreach { y=> (2101 to 3000) foreach { x=> s.insert(SEntry3_III(x,y,1)) } }
    / *
    s.insert(SEntry3_III(3001,10,1))
    s.insert(SEntry3_III(3001,2,1))
    s.insert(SEntry3_III(3001,3,1))
    s.insert(SEntry3_III(3001,6,1))
    s.insert(SEntry3_III(3001,8,1))
    s.insert(SEntry3_III(3001,9,1))
    s.insert(SEntry3_III(3002,3,1))

    val e = s.get(1,SEntry3_III(3000,1,1))
    s.delete(e)
    //s.insert(SEntry3_III(2999,1,1))
    println(s.get(1,SEntry3_III(0,2,1))) // Blocking
    * /
    var i=0;
    var e = null.asInstanceOf[SEntry3_III]
    do {
      e = s.get(1,SEntry3_III(3000,1,1))
      if (e!=null) s.delete(e)
      println(i); i+=1
    } while(e!=null)

    println("Done")
  }
}
*/
object Test { def main(args:Array[String]) { val t=new StoreTests } }
