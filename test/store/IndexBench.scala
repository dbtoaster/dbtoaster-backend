package ddbt.lib.store // faking
import ddbt.test.store._
import ddbt.Utils._
import java.io._

// S = number of samples
// N = number of elements
// M = elements per slice
// lf = load factor

object IndexBench {
  // Create new stores
  def store(list:Boolean,lf_u:Double=0.75,lf_nu:Double=4) = {
    val s = new Store[E](3,Array[EntryIdx[E]](E_I0,E_I1,E_I2))
    if (list) {
      s.index(0,new IdxHashL(s,0,true,lf_u.toFloat))
      s.index(1,new IdxHashL(s,1,false,lf_nu.toFloat))
      s.index(2,new IdxHashL(s,2,false,lf_nu.toFloat))
    } else {
      s.index(0,new IdxHash(s,0,true,lf_u.toFloat))
      s.index(1,new IdxHash(s,1,false,lf_nu.toFloat))
      s.index(2,new IdxHash(s,2,false,lf_nu.toFloat))
    }
    s
  }
  // Keep elements in an array (reduces GC?)
  def array(N:Int,M:Int) = {
    val a = new Array[E](N)
    val L = N/M
    var i=0; while (i<N) { a(i)=E(i%L,i,i); i+=1; }
    a
  }
  // Assumes 80% read / 20% write workload
  def work(s:Store[E], a:Array[E], M:Int) = { s.clear; System.gc(); ns(()=>{
    val N = a.size; s.clear
    var i=0
    var e:E=null.asInstanceOf[E]
    i=0; while(i<N) { s.insert(a(i)); i+=1; } // 10% insert
    i=0; while(i<N) { e=s.get(0,s.get(1,s.get(2,a(i)))); i+=1 } // 30% get
    i=0; val L=N/M;
    while(i<L) {
      s.slice(0,a(i),x => e=x) // ~50% slicing (well a bit less with slice 0)
      s.slice(2,a(i),x => e=x)
      s.slice(2,a(i),x => e=x)
      s.slice(1,a(i),x => e=x)
      s.slice(1,a(i),x => e=x)
      s.slice(1,a(i),x => e=x)
      s.slice(1,a(i),x => e=x)
      i+=1
    }
    i=0; while(i<N) { s.delete(a(i)); i+=1; } // 10% delete
  })._1 }

  def test(S:Int,N:Int,M:Int,list:Boolean,lf_u:Double,lf_nu:Double,out:PrintStream=null) {
    val s = store(list,lf_u,lf_nu)
    val a = array(N,M)
    val ts = (0 until S).map { x => work(s,a,M) }.sorted
    val med=if (S%2==1) ts(S/2) else (ts(S/2)+ts(S/2-1))/2
    val str = List(S,N,M,if (list) 1 else 0,lf_u,lf_nu,time(ts(0)),time(med),time(ts(S-1))).mkString(",")
    println(str); if (out!=null) out.println(str);
  }

  def main(args:Array[String]) {
    val S = 10
    val N = 100000
    val out = new PrintStream(new File("test/store/out.txt"))

    var f=.3; while (f<3) { test(S,N,10,false,f,4,out); f+=.05 }
    out.close ();

    //val s2 = store(true)




    //class Store[E<:Entry](val idxs:Array[Idx[E]], val ops:Array[EntryIdx[E]]=null)(implicit cE:ClassTag[E]) {
  }
}
