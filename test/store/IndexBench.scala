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
      s.index(0,new IdxHashL(s,0,true,lf_u.toFloat))
      s.index(1,new IdxHash(s,1,false,lf_nu.toFloat))
      s.index(2,new IdxHash(s,2,false,lf_nu.toFloat))
    }
    s
  }
  // Assumes 80% read / 20% write workload
  def work(s:Store[E], a:Array[E], M:Int) = {
    s.clear; System.gc();
    ns(()=>{
      val N = a.size; s.clear
      var i=0
      var e:E=null.asInstanceOf[E]
      i=0; while(i<N) { s.insert(a(i)); i+=1; } // 10% insert
      i=0; while(i<N) { e=s.get(0,s.get(1,s.get(2,a(i)))); i+=1 } // 30% get
      i=0; val L=N/M;
      (0 until 10).foreach { x => while(i<L) {
        //s.slice(0,a(i),x => e=x) // ~50% slicing (well a bit less with slice 0)
        //s.slice(2,a(i),x => e=x)
        //s.slice(2,a(i),x => e=x)
        s.slice(1,a(i),x => e=x)
        s.slice(1,a(i),x => e=x)
        s.slice(1,a(i),x => e=x)
        s.slice(1,a(i),x => e=x)
        s.slice(1,a(i),x => e=x)
        i+=1
      }}
      i=0; while(i<N) { s.delete(a(i)); i+=1; } // 10% delete
    })._1
  }

  def test(S:Int,N:Int,M:Int,lf_u:Double,lf_nu:Double,out:PrintStream=null) {
    val L=N/M // Keep elements in an array (to refer after)
    val a=new Array[E](N); var i=0; while (i<N) { a(i)=E(i%L,i,i); i+=1; }

    val s1 = store(false,lf_u,lf_nu)
    val s2 = store(true,lf_u,lf_nu)
    val ts1 = (0 until S).map { x => work(s1,a,M) }.sorted
    val ts2 = (0 until S).map { x => work(s2,a,M) }.sorted
    val (med1,med2)=if (S%2==1) (ts1(S/2),ts2(S/2)) else (  (ts1(S/2)+ts1(S/2-1))/2,  (ts2(S/2)+ts2(S/2-1))/2  )
    val str = List(S,N,M,lf_u,lf_nu,
                   time(ts1(0)),time(med1),time(ts1(S-1)), // IdxHash
                   time(ts2(0)),time(med2),time(ts2(S-1))  // IdxHashL
              ).mkString(",")
    println(str); if (out!=null) out.println(str);
  }

  def main(args:Array[String]) {
    val S = 10
    val N = 1000000
    val out = new PrintStream(new File("test/store/out.txt"))

    // lf_u is best in 0.7-1.5
    // lf_nu

    test(S,N,50,.75,4,null); // warm-up

    var v=100; while (v<1000) { test(S,N,v,.75,4,out); v+=100 }
    out.close;

    //val s2 = store(true)


    //class Store[E<:Entry](val idxs:Array[Idx[E]], val ops:Array[EntryIdx[E]]=null)(implicit cE:ClassTag[E]) {
  }
}
