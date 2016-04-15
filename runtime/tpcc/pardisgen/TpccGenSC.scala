
package tpcc.sc
import ddbt.lib.store.{Store => MStore, Aggregator => MirrorAggregator, _}
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  
  val x1 = new MStore[SEntry3_III](2, Array[EntryIdx[SEntry3_III]](SplEntryOps((e: SEntry3_III) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
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
  }, (x3802:SEntry3_III, x3803: SEntry3_III) => {
    val x3804 = x3802._1//get[Int](1)
    val x3805 = x3803._1//get[Int](1)
    val x3806 = x3804.==(x3805)
    val x3809 = if(x3806) 
    {
      0
    }
    else
    {
      val x3807 = x3804.>(x3805)
      val x3808 = if(x3807) 
      {
        1
      }
      else
      {
        -1
      }
      
      x3808
    }
    
    x3809
  }), SplEntryOps((e: SEntry3_III) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry3_III, e2: SEntry3_III) => if(e1._2 == e2._2 && e1._3 == e2._3) 0 else 1))) 
  x1.index(0, ISliceHeapMin, false, 1)
  x1.index(1, INone, false, -1)
  
  
  val x2 = new MStore[SEntry8_IIIIITDS](1, Array[EntryIdx[SEntry8_IIIIITDS]](SplEntryOps((e: SEntry8_IIIIITDS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  
  hash ^= 2
  hash ^= hash >>> 16
  hash *= 0x85ebca6b
  hash ^= hash >>> 13
  hash *= 0xc2b2ae35
  hash ^= hash >>> 16
  hash
  }, (e1: SEntry8_IIIIITDS, e2: SEntry8_IIIIITDS) => if((e1._1 == -1 || e2._1 == -1 || e1._1 == e2._1) && (e1._2 == -1 || e2._2 == -1 || e1._2 == e2._2) && (e1._3 == -1 || e2._3 == -1 || e1._3 == e2._3) && (e1._4 == -1 || e2._4 == -1 || e1._4 == e2._4) && (e1._5 == -1 || e2._5 == -1 || e1._5 == e2._5) && (e1._6 == null || e2._6 == null || e1._6 == e2._6) && (e1._7 == -1.0 || e2._7 == -1.0 || e1._7 == e2._7)) 0 else 1))) 
  x2.index(0, IList, false, -1)
  
  
  val x3 = new MStore[SEntry9_ISSSSSSDD](1, Array[EntryIdx[SEntry9_ISSSSSSDD]](SplEntryOps((e: SEntry9_ISSSSSSDD) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry9_ISSSSSSDD, e2: SEntry9_ISSSSSSDD) => if(e1._1 == e2._1) 0 else 1))) 
  x3.index(0, IHash, true, -1)
  
  
  val x4 = new MStore[SEntry5_IISDS](1, Array[EntryIdx[SEntry5_IISDS]](SplEntryOps((e: SEntry5_IISDS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry5_IISDS, e2: SEntry5_IISDS) => if(e1._1 == e2._1) 0 else 1))) 
  x4.index(0, IHash, true, -1)
  
  
  val x5 = new MStore[SEntry8_IIIITIIB](3, Array[EntryIdx[SEntry8_IIIITIIB]](SplEntryOps((e: SEntry8_IIIITIIB) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry8_IIIITIIB, e2: SEntry8_IIIITIIB) => if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1), SplEntryOps((e: SEntry8_IIIITIIB) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._4.hashCode * 0xcc9e2d51
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
  }, (x3810:SEntry8_IIIITIIB, x3811: SEntry8_IIIITIIB) => {
    val x3812 = x3810._1//get[Int](1)
    val x3813 = x3811._1//get[Int](1)
    val x3814 = x3812.==(x3813)
    val x3817 = if(x3814) 
    {
      0
    }
    else
    {
      val x3815 = x3812.>(x3813)
      val x3816 = if(x3815) 
      {
        1
      }
      else
      {
        -1
      }
      
      x3816
    }
    
    x3817
  }), SplEntryOps((e: SEntry8_IIIITIIB) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._4.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry8_IIIITIIB, e2: SEntry8_IIIITIIB) => if(e1._2 == e2._2 && e1._3 == e2._3 && e1._4 == e2._4) 0 else 1))) 
  x5.index(0, IHash, true, -1)
  x5.index(1, ISliceHeapMax, false, 2)
  x5.index(2, INone, false, -1)
  
  
  val x6 = new MStore[SEntry11_IISSSSSSDDI](1, Array[EntryIdx[SEntry11_IISSSSSSDDI]](SplEntryOps((e: SEntry11_IISSSSSSDDI) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._2.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry11_IISSSSSSDDI, e2: SEntry11_IISSSSSSDDI) => if(e1._1 == e2._1 && e1._2 == e2._2) 0 else 1))) 
  x6.index(0, IHash, true, -1)
  
  
  val x7 = new MStore[SEntry10_IIIIIITIDS](1, Array[EntryIdx[SEntry10_IIIIIITIDS]](SplEntryOps((e: SEntry10_IIIIIITIDS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry10_IIIIIITIDS, e2: SEntry10_IIIIIITIDS) => if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1))) 
  x7.index(0, IHash, false, -1)
  
  
  val x8 = new MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SplEntryOps((e: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry21_IIISSSSSSSSSTSDDDDIIS, e2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1), SplEntryOps((e: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._2.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._3.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._6.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry21_IIISSSSSSSSSTSDDDDIIS, e2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => if(e1._2 == e2._2 && e1._3 == e2._3 && e1._6 == e2._6) 0 else 1))) 
  x8.index(0, IHash, true, -1)
  x8.index(1, IHash, false, -1)
  
  
  val x9 = new MStore[SEntry17_IIISSSSSSSSSSIIIS](1, Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SplEntryOps((e: SEntry17_IIISSSSSSSSSSIIIS) => {
  var hash:Int = 0xcafebabe
  var mix:Int = 0
  mix = e._1.hashCode * 0xcc9e2d51
  mix = (mix << 15) | (mix >>> -15)
  mix *= 0x1b873593
  mix ^= hash
  mix = (mix << 13) | (mix >>> -13)
  hash = mix * 5 + 0xe6546b64
  mix = e._2.hashCode * 0xcc9e2d51
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
  }, (e1: SEntry17_IIISSSSSSSSSSIIIS, e2: SEntry17_IIISSSSSSSSSSIIIS) => if(e1._1 == e2._1 && e1._2 == e2._2) 0 else 1))) 
  x9.index(0, IHash, true, -1)
  
  
    val newOrderTxInst = new NewOrderTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val paymentTxInst = new PaymentTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val orderStatusTxInst = new OrderStatusTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val deliveryTxInst = new DeliveryTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val stockLevelTxInst = new StockLevelTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
}
      
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def copy = SEntry5_IISDS(_1, _2, _3, _4, _5) }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def copy = SEntry3_III(_1, _2, _3) }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9) }
class DeliveryTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  val x67 = while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x22 = x15
    val x2227 = SEntry3_III(-1, x22, x12)
    val x26 = x1.get(0, x2227)
    val x27 = x26.!=(null)
    val x63 = if(x27) 
    {
      val x2232 = x26._1
      val x29 = x15
      val x30 = x29.-(1)
      val x31 = x14.update(x30, x2232)
      val x32 = x1.delete(x26)
      val x33 = x15
      val x2238 = SEntry8_IIIITIIB(x2232, x33, x12, -1, null, -1, -1, false)
      val x36 = x5.get(0, x2238)
      val x2241 = x36._4
      val x2242 = x36._6_=(x13)
      val x39 = x5.update(x36)
      var x40: Double = 0.0
      val x41 = x15
      val x2247 = SEntry10_IIIIIITIDS(x2232, x41, x12, -1, -1, -1, null, -1, -1.0, "")
      val x51 = { x44: SEntry10_IIIIIITIDS => {
          val x2355 = x44._7_=(x11)
          val x46 = x40
          val x2357 = x44._9
          val x48 = x46.+(x2357)
          val x49 = x40 = x48
          val x50 = x7.update(x44)
          x50
        }
      }
      val x52 = x7.slice(0, x2247, x51)
      val x53 = x15
      val x2251 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x2241, x53, x12, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
      val x55 = x8.get(0, x2251)
      val x56 = x40
      val x2254 = x55._17
      val x2255 = x2254.+(x56)
      val x2256 = x55._17_=(x2255)
      val x2257 = x55._20
      val x2258 = x2257.+(1)
      val x2259 = x55._20_=(x2258)
      val x59 = x8.update(x55)
      x59
    }
    else
    {
      val x60 = x15
      val x61 = x60.-(1)
      val x62 = x14.update(x61, 0)
      x62
    }
    
    val x64 = x15
    val x65 = x64.+(1)
    val x66 = x15 = x65
    x66
  }
  val x121 = if(x10) 
  {
    val x68 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
    val x69 = x68.+("\n\n Warehouse: ")
    val x70 = x69.+(x12)
    val x71 = x70.+("\n Carrier:   ")
    val x72 = x71.+(x13)
    val x73 = x72.+("\n\n Delivered Orders\n")
    var x74: String = x73
    var x75: Int = 0
    var x76: Int = 1
    val x115 = while({
      val x77 = x76
      val x78 = x77.<=(10)
      x78
    })
    {
      val x79 = x76
      val x80 = x79.-(1)
      val x81 = x14.apply(x80)
      val x82 = x81.>=(0)
      val x111 = if(x82) 
      {
        val x83 = x74
        val x84 = x83.+("  District ")
        val x85 = x76
        val x86 = x85.<(10)
        val x87 = if(x86) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x88 = x84.+(x87)
        val x89 = x76
        val x90 = x88.+(x89)
        val x91 = x90.+(": Order number ")
        val x92 = x76
        val x93 = x92.-(1)
        val x94 = x14.apply(x93)
        val x95 = x91.+(x94)
        val x96 = x95.+(" was delivered.\n")
        val x97 = x74 = x96
        x97
      }
      else
      {
        val x98 = x74
        val x99 = x98.+("  District ")
        val x100 = x76
        val x101 = x100.<(10)
        val x102 = if(x101) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x103 = x99.+(x102)
        val x104 = x76
        val x105 = x103.+(x104)
        val x106 = x105.+(": No orders to be delivered.\n")
        val x107 = x74 = x106
        val x108 = x75
        val x109 = x108.+(1)
        val x110 = x75 = x109
        x110
      }
      
      val x112 = x76
      val x113 = x112.+(1)
      val x114 = x76 = x113
      x114
    }
    val x116 = x74
    val x117 = x116.+("+-----------------------------------------------------------------+\n\n")
    val x118 = x74 = x117
    val x119 = x74
    val x120 = println(x119)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class StockLevelTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) = {
  val x2545 = SEntry11_IISSSSSSDDI(x126, x125, "", "", "", "", "", "", -1.0, -1.0, -1)
  val x130 = x6.get(0, x2545)
  val x2548 = x130._11
  val x132 = x2548.-(20)
  var x133: Int = x132
  val x134 = Set.apply[Int]()
  val x153 = while({
    val x135 = x133
    val x136 = x135.<(x2548)
    x136
  })
  {
    val x137 = x133
    val x2557 = SEntry10_IIIIIITIDS(x137, x126, x125, -1, -1, -1, null, -1, -1.0, "")
    val x148 = { x140: SEntry10_IIIIIITIDS => {
        val x2589 = x140._5
        val x2590 = SEntry17_IIISSSSSSSSSSIIIS(x2589, x125, -1, "", "", "", "", "", "", "", "", "", "", -1, -1, -1, "")
        val x143 = x9.get(0, x2590)
        val x2592 = x143._3
        val x145 = x2592.<(x127)
        val x147 = if(x145) 
        {
          val x146 = x134.+=(x2589)
          ()
        }
        else
        {
          ()
        }
        
        x147
      }
    }
    val x149 = x7.slice(0, x2557, x148)
    val x150 = x133
    val x151 = x150.+(1)
    val x152 = x133 = x151
    x152
  }
  val x154 = x134.size
  val x164 = if(x122) 
  {
    val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x125)
    val x156 = x155.+("\n District:  ")
    val x157 = x156.+(x126)
    val x158 = x157.+("\n\n Stock Level Threshold: ")
    val x159 = x158.+(x127)
    val x160 = x159.+("\n Low Stock Count:       ")
    val x161 = x160.+(x154)
    val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
    val x163 = println(x162)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class OrderStatusTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) = {
  var x2648: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x174 = x170.>(0)
  val x207 = if(x174) 
  {
    val x2651 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x2653 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, x169, x168, "", "", x172, "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x180 = { x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x179 = x2651.append(x178)
        x179
      }
    }
    val x181 = x8.slice(1, x2653, x180)
    val x182 = x2651.size
    val x183 = x182./(2)
    var x184: Int = x183
    val x185 = x2651.size
    val x186 = x185.%(2)
    val x187 = x186.==(0)
    val x191 = if(x187) 
    {
      val x188 = x184
      val x189 = x188.-(1)
      val x190 = x184 = x189
      x190
    }
    else
    {
      ()
    }
    
    val x198 = { (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x2709 = x192._4
        val x2710 = x193._4
        val x196 = x2709.compareToIgnoreCase(x2710)
        val x197 = x196.<(0)
        x197
      }
    }
    val x199 = x2651.sortWith(x198)
    val x200 = x184
    val x201 = x199.apply(x200)
    val x202 = x2648 = x201
    x202
  }
  else
  {
    val x2671 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x171, x169, x168, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x205 = x8.get(0, x2671)
    val x206 = x2648 = x205
    x206
  }
  
  val x208 = x2648
  val x2676 = x208._3
  val x2682 = SEntry8_IIIITIIB(-1, x169, x168, x2676, null, -1, -1, false)
  val x217 = x5.get(1, x2682)
  var x218: Int = 0
  1
}
}
class PaymentTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) = {
  val x2778 = SEntry9_ISSSSSSDD(x222, "", "", "", "", "", "", -1.0, -1.0)
  val x232 = x3.get(0, x2778)
  val x2781 = x232._9
  val x2782 = x2781.+(x229)
  val x2783 = x232._9_=(x2782)
  val x234 = x3.update(x232)
  val x2785 = SEntry11_IISSSSSSDDI(x223, x222, "", "", "", "", "", "", -1.0, -1.0, -1)
  val x237 = x6.get(0, x2785)
  val x2788 = x237._10
  val x2789 = x2788.+(x229)
  val x2790 = x237._10_=(x2789)
  val x239 = x6.update(x237)
  var x2792: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x241 = x224.>(0)
  val x274 = if(x241) 
  {
    val x2795 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x2797 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, x226, x225, "", "", x228, "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x247 = { x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x246 = x2795.append(x245)
        x246
      }
    }
    val x248 = x8.slice(1, x2797, x247)
    val x249 = x2795.size
    val x250 = x249./(2)
    var x251: Int = x250
    val x252 = x2795.size
    val x253 = x252.%(2)
    val x254 = x253.==(0)
    val x258 = if(x254) 
    {
      val x255 = x251
      val x256 = x255.-(1)
      val x257 = x251 = x256
      x257
    }
    else
    {
      ()
    }
    
    val x265 = { (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x2906 = x259._4
        val x2907 = x260._4
        val x263 = x2906.compareToIgnoreCase(x2907)
        val x264 = x263.<(0)
        x264
      }
    }
    val x266 = x2795.sortWith(x265)
    val x267 = x251
    val x268 = x266.apply(x267)
    val x269 = x2792 = x268
    x269
  }
  else
  {
    val x2815 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x227, x226, x225, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x272 = x8.get(0, x2815)
    val x273 = x2792 = x272
    x273
  }
  
  val x275 = x2792
  val x2820 = x275._21
  var x277: String = x2820
  val x278 = x2792
  val x2823 = x278._14
  val x280 = x2823.contains("BC")
  val x301 = if(x280) 
  {
    val x281 = x2792
    val x2827 = x281._1
    val x283 = x277
    val x285 = "%d %d %d %d %d $%f %s | %s".format(x2827,x226,x225,x223,x222,x229,x220,x283)
    val x286 = x277 = x285
    val x287 = x277
    val x288 = x287.length
    val x289 = x288.>(500)
    val x293 = if(x289) 
    {
      val x290 = x277
      val x291 = x290.substring(0, 500)
      val x292 = x277 = x291
      x292
    }
    else
    {
      ()
    }
    
    val x294 = x2792
    val x2840 = x294._17
    val x2841 = x2840.+(x229)
    val x2842 = x294._17_=(x2841)
    val x296 = x2792
    val x297 = x277
    val x2845 = x296._21_=(x297)
    ()
  }
  else
  {
    val x299 = x2792
    val x2847 = x299._17
    val x2848 = x2847.+(x229)
    val x2849 = x299._17_=(x2848)
    x2849
  }
  
  val x302 = x2792
  val x303 = x8.update(x302)
  val x2852 = x232._2
  val x2853 = x237._3
  val x306 = x2852.length
  val x307 = x306.>(10)
  val x309 = if(x307) 
  {
    val x308 = x2852.substring(0, 10)
    x308
  }
  else
  {
    x2852
  }
  
  val x310 = x309.+("    ")
  val x311 = x2853.length
  val x312 = x311.>(10)
  val x314 = if(x312) 
  {
    val x313 = x2853.substring(0, 10)
    x313
  }
  else
  {
    x2853
  }
  
  val x315 = x310.+(x314)
  val x316 = x2792
  val x2865 = x316._1
  val x2867 = SEntry8_IIIIITDS(x2865, x226, x225, x223, x222, x220, x229, x315)
  val x320 = x2.insert(x2867)
  1
}
}
class NewOrderTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x321: Boolean, x322: Date, x323: Int, x324: Int, x325: Int, x326: Int, x327: Int, x328: Int, x329: Array[Int], x330: Array[Int], x331: Array[Int], x332: Array[Double], x333: Array[String], x334: Array[Int], x335: Array[String], x336: Array[Double]) = {
  val x340 = if(x321) 
  {
    val x338 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x324,x325,x326)
    val x339 = println(x338)
    x339
  }
  else
  {
    ()
  }
  
  var x341: Int = 0
  var x342: Boolean = false
  val x343 = new Array[String](x327)
  var x344: Boolean = true
  val x369 = while({
    val x345 = x341
    val x346 = x345.<(x327)
    val x348 = x346.&&({
      val x347 = x344
      x347
    })
    x348
  })
  {
    val x349 = x341
    val x350 = x329.apply(x349)
    val x3082 = SEntry5_IISDS(x350, -1, "", -1.0, "")
    val x353 = x4.get(0, x3082)
    val x354 = x353.==(null)
    val x365 = if(x354) 
    {
      val x355 = x344 = false
      ()
    }
    else
    {
      val x356 = x341
      val x3089 = x353._3
      val x358 = x333.update(x356, x3089)
      val x359 = x341
      val x3092 = x353._4
      val x361 = x332.update(x359, x3092)
      val x362 = x341
      val x3095 = x353._5
      val x364 = x343.update(x362, x3095)
      x364
    }
    
    val x366 = x341
    val x367 = x366.+(1)
    val x368 = x341 = x367
    ()
  }
  val x370 = x344
  val x479 = if(x370) 
  {
    val x3102 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x326, x325, x324, "", "", "", "", "", "", "", "", "", null, "", -1.0, -1.0, -1.0, -1.0, -1, -1, "")
    val x373 = x8.get(0, x3102)
    val x3105 = SEntry9_ISSSSSSDD(x324, "", "", "", "", "", "", -1.0, -1.0)
    val x376 = x3.get(0, x3105)
    val x3108 = SEntry11_IISSSSSSDDI(x325, x324, "", "", "", "", "", "", -1.0, -1.0, -1)
    val x379 = x6.get(0, x3108)
    val x3111 = x379._11
    val x3112 = x379._11
    val x3113 = x3112.+(1)
    val x3114 = x379._11_=(x3113)
    val x382 = x6.update(x379)
    val x383 = x328.>(0)
    val x3118 = SEntry8_IIIITIIB(x3111, x325, x324, x326, x322, -1, x327, x383)
    val x386 = x5.insert(x3118)
    val x3121 = SEntry3_III(x3111, x325, x324)
    val x389 = x1.insert(x3121)
    var x390: Double = 0.0
    val x391 = x341 = 0
    val x478 = while({
      val x392 = x341
      val x393 = x392.<(x327)
      x393
    })
    {
      val x394 = x341
      val x395 = x330.apply(x394)
      val x396 = x341
      val x397 = x329.apply(x396)
      val x398 = x341
      val x399 = x331.apply(x398)
      val x3134 = SEntry17_IIISSSSSSSSSSIIIS(x397, x395, -1, "", "", "", "", "", "", "", "", "", "", -1, -1, -1, "")
      val x401 = x9.get(0, x3134)
      val x402 = x325.==(1)
      val x429 = if(x402) 
      {
        val x3138 = x401._4
        x3138
      }
      else
      {
        val x404 = x325.==(2)
        val x428 = if(x404) 
        {
          val x3141 = x401._5
          x3141
        }
        else
        {
          val x406 = x325.==(3)
          val x427 = if(x406) 
          {
            val x3144 = x401._6
            x3144
          }
          else
          {
            val x408 = x325.==(4)
            val x426 = if(x408) 
            {
              val x3147 = x401._7
              x3147
            }
            else
            {
              val x410 = x325.==(5)
              val x425 = if(x410) 
              {
                val x3150 = x401._8
                x3150
              }
              else
              {
                val x412 = x325.==(6)
                val x424 = if(x412) 
                {
                  val x3153 = x401._9
                  x3153
                }
                else
                {
                  val x414 = x325.==(7)
                  val x423 = if(x414) 
                  {
                    val x3156 = x401._10
                    x3156
                  }
                  else
                  {
                    val x416 = x325.==(8)
                    val x422 = if(x416) 
                    {
                      val x3159 = x401._11
                      x3159
                    }
                    else
                    {
                      val x418 = x325.==(9)
                      val x421 = if(x418) 
                      {
                        val x3162 = x401._12
                        x3162
                      }
                      else
                      {
                        val x3163 = x401._13
                        x3163
                      }
                      
                      x421
                    }
                    
                    x422
                  }
                  
                  x423
                }
                
                x424
              }
              
              x425
            }
            
            x426
          }
          
          x427
        }
        
        x428
      }
      
      val x3164 = x401._3
      val x431 = x341
      val x432 = x334.update(x431, x3164)
      val x3167 = x373._14
      val x434 = x3167.contains("original")
      val x437 = x434.&&({
        val x3170 = x401._17
        val x436 = x3170.contains("original")
        x436
      })
      val x442 = if(x437) 
      {
        val x438 = x341
        val x439 = x335.update(x438, "B")
        ()
      }
      else
      {
        val x440 = x341
        val x441 = x335.update(x440, "G")
        ()
      }
      
      val x443 = x3164.-(x399)
      val x3178 = x401._3_=(x443)
      val x445 = x3164.<=(x399)
      val x447 = if(x445) 
      {
        val x3181 = x401._3
        val x3182 = x3181.+(91)
        val x3183 = x401._3_=(x3182)
        x3183
      }
      else
      {
        ()
      }
      
      var x448: Int = 0
      val x449 = x395.!=(x324)
      val x451 = if(x449) 
      {
        val x450 = x448 = 1
        x450
      }
      else
      {
        ()
      }
      
      val x452 = x9.update(x401)
      val x3189 = x373._16
      val x3190 = x376._8
      val x3191 = x379._9
      val x456 = x341
      val x457 = x332.apply(x456)
      val x458 = x399.toDouble
      val x459 = x458.*(x457)
      val x460 = 1.0.+(x3190)
      val x461 = x460.+(x3191)
      val x462 = x459.*(x461)
      val x463 = 1.0.-(x3189)
      val x464 = x462.*(x463)
      val x465 = x341
      val x466 = x336.update(x465, x464)
      val x467 = x390
      val x468 = x467.+(x464)
      val x469 = x390 = x468
      val x470 = x341
      val x471 = x470.+(1)
      val x3209 = SEntry10_IIIIIITIDS(x3111, x325, x324, x471, x397, x395, null, x399, x464, x429)
      val x474 = x7.insert(x3209)
      val x475 = x341
      val x476 = x475.+(1)
      val x477 = x341 = x476
      ()
    }
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
