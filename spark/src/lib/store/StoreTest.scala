package ddbt.lib.spark.store

import ddbt.lib.spark.store._

object StoreTest {

  // Time measurement
  def ns[T](f:()=>T) = { val t0=System.nanoTime; var r=f(); val t1=System.nanoTime; (t1-t0,r) }
  def time(ns:Long,p:Boolean=true) = if (p) { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) } else { val ms=math.round(ns/1000000.0); ("%d.%03d").format(ms/1000,ms%1000) }
  
  val s = new Store[SEntry3_III](Vector(
      new HashIndex[SEntry3_III](0, false) with SEntry3_III_Idx0,
      new HashIndex[SEntry3_III](1, false) with SEntry3_III_Idx1))
    
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
    val F=100000
    val n1 = (0 until H*2+1).map(x=>run(1*F)).sorted.apply(0)
    val n2 = (0 until H*2+1).map(x=>run(10*F)).sorted.apply(0)
    println("100K: "+time(n1)+" 1M: "+time(n2)+" => "+(n2/(10.0*n1)))
  }
}

  case class SEntry3_III(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0) extends MapEntry(2) {
    def copy = SEntry3_III(_1, _2, _3)
  }

  trait SEntry3_III_Idx0 extends IndexOperations[SEntry3_III] {
    override def cmp(e1:SEntry3_III,e2:SEntry3_III):Int = if(e1._2 == e2._2 && e1._3 == e2._3) 0 else 1
    override def hash(e:SEntry3_III):Int = {
      var hash:Int = 0xcafebabe
      var mix:Int = e._2.## * 0xcc9e2d51
      mix = (mix << 15) | (mix >>> -15)
      mix *= 0x1b873593
      mix ^= hash
      mix = (mix << 13) | (mix >>> -13)
      hash = mix * 5 + 0xe6546b64
      mix = e._3.## * 0xcc9e2d51
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
      hash
    }
  }
  
  trait SEntry3_III_Idx1 extends IndexOperations[SEntry3_III] {
    override def cmp(e1:SEntry3_III,e2:SEntry3_III):Int = if(e1._1 < e2._1) { -1 } else if(e1._1 > e2._1) { 1 } else { 0 }
    override def hash(e:SEntry3_III):Int = e._1
  }
