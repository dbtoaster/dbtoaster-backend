package storage
import ddbt.lib.store._

object ScaleTests {
  // Time measurement
  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long,p:Boolean=true) = if (p) { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) } else { val ms=math.round(ns/1000000.0); ("%d.%03d").format(ms/1000,ms%1000) }

  val s = new Store[SEntry3_III](2)
  s.index(0,IHash,false)
  s.index(1,ISliceHeapMin,false,0)

  def run(N:Int):Long = {
    System.gc
    val r = ns{()=>
      var i=0; while (i<N) { i+=1; s.insert(SEntry3_III(1*i,2*i,3*i)); }
    }._1
    s.clear;
    System.gc
    r
  }

  def main(args: Array[String]) {
    val H=15
    val F=1000000
    val n1 = (0 until H*2+1).map(x=>run(1*F)).sorted.apply(0)
    val n2 = (0 until H*2+1).map(x=>run(10*F)).sorted.apply(0)
    println("1M: "+time(n1)+" 10M: "+time(n2)+" => "+(n2/(10.0*n1)))
  }
}

  case class SEntry3_III(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0) extends Entry(2) {
    def hash(i: Int):Int = {
      var hash:Int = 0xcafebabe
      if(i == 0) {
        var mix:Int = _2.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = mix * 5 + 0xe6546b64
        mix = _3.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = mix * 5 + 0xe6546b64
        hash ^= 2
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16
      } else if(i == 1) {
        var mix:Int = _1.## * 0xcc9e2d51
        mix = (mix << 15) | (mix >>> -15)
        mix *= 0x1b873593
        mix ^= hash
        mix = (mix << 13) | (mix >>> -13)
        hash = mix * 5 + 0xe6546b64
        hash ^= 1
        hash ^= hash >>> 16
        hash *= 0x85ebca6b
        hash ^= hash >>> 13
        hash *= 0xc2b2ae35
        hash ^= hash >>> 16

      }
      hash
    }
    def cmp(i: Int, e0:Entry):Int = {
      val e=e0.asInstanceOf[SEntry3_III]
      if(i == 0) {
        if(_2 == e._2 && _3 == e._3) 0 else 1
      } else if(i == 1) {
        if(_1 < e._1) { -1 } else if(_1 > e._1) { 1 } else { 0 }
      } else { 0 }
    }
    def copy = SEntry3_III(_1, _2, _3)
  }
