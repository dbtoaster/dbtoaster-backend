package ddbt.lib.store2 // faking
import ddbt.Utils._
import java.io._


case class E(var _1:Long, var _2:Long, var _3:Double) extends Entry[E] {
  var _h0=0; var _n0:E=null;
  var _h1=0; var _n1:E=null;
  var _h2=0; var _n2:E=null;
  def copy = E(_1,_2,_3)
  def copy(e:E) { e._1=_1; e._2=_2; e._3=_3; }
}

// S = number of samples
// N = total number of elements in the hash map
// M = elements per slice
// lf = load factor

object IndexBench {
  val i0:Idx[E] = new IdxHash[E](true) {
    def hash(e:E) = { var h:Int=0xcafebabe;
      var mix:Int=e._1.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
      mix=e._2.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
      h^=2; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
    }
    def cmp(e1:E,e2:E) = if (e1._1==e2._1 && e1._2==e2._2) 0 else 1
    def _h(e:E)=e._h0; def _h(e:E,h:Int) { e._h0=h }
    def _n(e:E)=e._n0; def _n(e:E,n:E) { e._n0=n }
  }

  val i1:Idx[E] = new IdxHash[E](false) {
    def hash(e:E) = { var h:Int=0xcafebabe;
      var mix:Int=e._1.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
      h^=1; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
    }
    def cmp(e1:E,e2:E) = if (e1._1==e2._1) 0 else 1
    def _h(e:E)=e._h1; def _h(e:E,h:Int) { e._h1=h }
    def _n(e:E)=e._n1; def _n(e:E,n:E) { e._n1=n }
  }

  val i2:Idx[E] = new IdxHash[E](false) {
    def hash(e:E) = { var h:Int=0xcafebabe;
      var mix:Int=e._2.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
      h^=1; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
    }
    def cmp(e1:E,e2:E) = if (e1._1==e2._1) 0 else 1
    def _h(e:E)=e._h2; def _h(e:E,h:Int) { e._h2=h }
    def _n(e:E)=e._n2; def _n(e:E,n:E) { e._n2=n }
  }


  // XXX: We should assume 80% read / 20% write workload
  def work(s:Store[E], N:Int, M:Int, S:Int) = {
    val L=N/M; var i=0
    var e:E=null.asInstanceOf[E]; s.clear; System.gc(); System.gc(); Thread.sleep(20);
    i=0; while(i<N) { s.insert(E(i%L,i,i)); i+=1; } // 10% insert
    // i=0; while(i<N) { e=s.get(0,s.get(1,s.get(2,E(i%L,i,i)))); i+=1 } // 30% get
    val ts = (0 until S).map { x => ns(()=>{
      (0 until 10).foreach { x => i=0; while(i<L) {
        val e0 = E(i%L,i,i)
        //s.slice(0,e0,x => e=x) // ~50% slicing (well a bit less with slice 0)
        //s.slice(2,e0,x => e=x)
        //s.slice(2,e0,x => e=x)
        s.slice(1,e0,x => e=x)
        /*
        s.slice(1,e0,x => e=x)
        s.slice(1,e0,x => e=x)
        s.slice(1,e0,x => e=x)
        s.slice(1,e0,x => e=x)
        */
        i+=1
      }}
    })._1 }
    //i=0; while(i<N) { s.delete(E(i%L,i,i)); i+=1; } // 10% delete
    ts.sorted
  }

  def test(S:Int,N:Int,M:Int,lf_u:Double,lf_nu:Double,out:PrintStream=null) {
    val L=N/M // Keep elements in an array (to refer after)
    //val a=new Array[E](N); var i=0; while (i<N) { a(i)=E(i%L,i,i); i+=1; }

    // Create new stores
    val s=new Store(Array(i0,i1,i2))
    val ts = work(s,N,M,S)
    val med=if (S%2==1) ts(S/2) else (ts(S/2)+ts(S/2-1))/2
    val str = List(S,N,M,lf_u,lf_nu,time(ts(0)),time(med),time(ts(S-1))).mkString(",")
    println(str)

    /*
    val s1 = new Store[E](3,Array[EtryIdx[E]](E_I0,E_I1,E_I2))
    //s1.index(0,new IdxHashT(s1,0,true,lf_u.toFloat))
    s1.index(1,new IdxHashT(s1,1,false,lf_nu.toFloat))
    //s1.index(2,new IdxHashT(s1,2,false,lf_nu.toFloat))

    val s2 = new Store[E](3,Array[EtryIdx[E]](E_I0,E_I1,E_I2))
    //s2.index(0,new IdxHash(s2,0,true,lf_u.toFloat))
    s2.index(1,new IdxHash(s2,1,false,lf_nu.toFloat))
    //s2.index(2,new IdxHash(s2,2,false,lf_nu.toFloat))

    val ts1 = work(s1,N,M,S)
    val ts2 = work(s2,N,M,S)
    val (med1,med2)=if (S%2==1) (ts1(S/2),ts2(S/2)) else (  (ts1(S/2)+ts1(S/2-1))/2,  (ts2(S/2)+ts2(S/2-1))/2  )
    val str = List(S,N,M,lf_u,lf_nu,
                   time(ts1(0)),time(med1),time(ts1(S-1)), // IdxHashTree
                   time(ts2(0)),time(med2),time(ts2(S-1))  // IdxHashList
              ).mkString(",")
    println(str); if (out!=null) out.println(str);
    */
  }

  def main(args:Array[String]) {
    val S = 10
    val N = 1000000
    val out = new PrintStream(new File("test/store/out.txt"))

    // lf_u is best in 0.7-1.5
    // lf_nu

    test(S*3,N,50,.75,.75,null); // warm-up

    for (M <- List(100,200,500,1000,2000,5000,10000,20000,50000,100000)) {
      test(S,N,M,.75,.75,out)
    }
    out.close;
  }
}
