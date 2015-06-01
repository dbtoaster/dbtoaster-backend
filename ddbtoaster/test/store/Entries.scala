package ddbt.test.store
import ddbt.lib.store._

// We list here all the entries to reuse them across tests

case class E(var _1:Long, var _2:Long, var _3:Double) extends Entry(3) { def copy = E(_1,_2,_3) }
object E_I0 extends EntryIdx[E] {
  def hash(e:E) = { var h:Int=0xcafebabe;
    var mix:Int=e._1.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
    mix=e._2.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
    h^=2; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
  }
  def cmp(e1:E,e2:E) = if(e1._1==e2._1 && e1._2==e2._2) 0 else 1
}
object E_I1 extends EntryIdx[E] {
  def hash(e:E) = { var h:Int=0xcafebabe;
    var mix:Int=e._1.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
    h^=1; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
  }
  def cmp(e1:E,e2:E) = if(e1._1==e2._1) 0 else 1
}
object E_I2 extends EntryIdx[E] {
  def hash(e:E) = { var h:Int=0xcafebabe;
    var mix:Int=e._2.## * 0xcc9e2d51; mix=((mix << 15) | (mix >>> -15))*0x1b873593 ^ h; mix=(mix << 13) | (mix >>> -13); h=(mix << 1)+mix+0xe6546b64;
    h^=1; h^=h>>>16; h*=0x85ebca6b; h^=h >>> 13; h*=0xc2b2ae35; h ^ (h>>>16)
  }
  def cmp(e1:E,e2:E) = if(e1._2==e2._2) 0 else 1
}
