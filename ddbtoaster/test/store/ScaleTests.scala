package ddbt.test.store
import ddbt.lib.store._

object ScaleTests {
  import ddbt.Utils.{ns,time}

  val s = new Store[SEntry3_III](2,Array(SEntry3_III_Idx0,SEntry3_III_Idx1))
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
    val F=100000
    val n1 = (0 until H*2+1).map(x=>run(1*F)).sorted.apply(0)
    val n2 = (0 until H*2+1).map(x=>run(10*F)).sorted.apply(0)
    println("100K: "+time(n1)+" 1M: "+time(n2)+" => "+(n2/(10.0*n1)))
  }
}

  case class SEntry3_III(var _1:Int = 0, var _2:Int = 0, var _3:Int = 0) extends Entry(2) {
    def copy = SEntry3_III(_1, _2, _3)
  }

  object SEntry3_III_Idx0 extends EntryIdx[SEntry3_III] {
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
  object SEntry3_III_Idx1 extends EntryIdx[SEntry3_III] {
    override def cmp(e1:SEntry3_III,e2:SEntry3_III):Int = if(e1._1 < e2._1) { -1 } else if(e1._1 > e2._1) { 1 } else { 0 }
    override def hash(e:SEntry3_III):Int = e._1
  }
