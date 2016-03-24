
package tpcc.sc
import ddbt.lib.store.{Store => MStore, Aggregator => MirrorAggregator, _}
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  
  val x1 = new MStore[SEntry3_III](2, Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx0, SEntry3_III_Idx1)) 
  x1.index(0, IHash, false, -1)
  x1.index(1, ISliceHeapMin, false, 0)
  
  val x2 = new MStore[SEntry8_IIIIITDS](1, Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx0)) 
  x2.index(0, IHash, false, -1)
  
  val x3 = new MStore[SEntry9_ISSSSSSDD](1, Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx0)) 
  x3.index(0, IHash, true, -1)
  
  val x4 = new MStore[SEntry5_IISDS](1, Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx0)) 
  x4.index(0, IHash, true, -1)
  
  val x5 = new MStore[SEntry8_IIIITIIB](3, Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx0, SEntry8_IIIITIIB_Idx1, SEntry8_IIIITIIB_Idx2)) 
  x5.index(0, IHash, true, -1)
  x5.index(1, IHash, false, -1)
  x5.index(2, ISliceHeapMax, false, 1)
  
  val x6 = new MStore[SEntry11_IISSSSSSDDI](1, Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx0)) 
  x6.index(0, IHash, true, -1)
  
  val x7 = new MStore[SEntry10_IIIIIITIDS](1, Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx0)) 
  x7.index(0, IHash, false, -1)
  
  val x8 = new MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx0, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1)) 
  x8.index(0, IHash, true, -1)
  x8.index(1, IHash, false, -1)
  
  val x9 = new MStore[SEntry17_IIISSSSSSSSSSIIIS](1, Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx0)) 
  x9.index(0, IHash, true, -1)
  
    val newOrderTxInst = new NewOrderTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val paymentTxInst = new PaymentTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val orderStatusTxInst = new OrderStatusTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val deliveryTxInst = new DeliveryTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val stockLevelTxInst = new StockLevelTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
}
      

case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String)  extends Entry(21){
   def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21)
 }

      

object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx0 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
   override def cmp(e1: SEntry21_IIISSSSSSSSSTSDDDDIIS, e2: SEntry21_IIISSSSSSSSSTSDDDDIIS) = if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1
   override def hash(e: SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
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
      }
}

                

object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
   override def cmp(e1: SEntry21_IIISSSSSSSSSTSDDDDIIS, e2: SEntry21_IIISSSSSSSSSTSDDDDIIS) = if(e1._2 == e2._2 && e1._3 == e2._3 && e1._6 == e2._6) 0 else 1
   override def hash(e: SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
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
      }
}

                

case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String)  extends Entry(10){
   def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)
 }

      

object SEntry10_IIIIIITIDS_Idx0 extends EntryIdx[SEntry10_IIIIIITIDS] {
   override def cmp(e1: SEntry10_IIIIIITIDS, e2: SEntry10_IIIIIITIDS) = if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1
   override def hash(e: SEntry10_IIIIIITIDS) = {
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
      }
}

                

case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double)  extends Entry(9){
   def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9)
 }

      

object SEntry9_ISSSSSSDD_Idx0 extends EntryIdx[SEntry9_ISSSSSSDD] {
   override def cmp(e1: SEntry9_ISSSSSSDD, e2: SEntry9_ISSSSSSDD) = if(e1._1 == e2._1) 0 else 1
   override def hash(e: SEntry9_ISSSSSSDD) = {
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
      }
}

                

case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String)  extends Entry(5){
   def copy = SEntry5_IISDS(_1, _2, _3, _4, _5)
 }

      

object SEntry5_IISDS_Idx0 extends EntryIdx[SEntry5_IISDS] {
   override def cmp(e1: SEntry5_IISDS, e2: SEntry5_IISDS) = if(e1._1 == e2._1) 0 else 1
   override def hash(e: SEntry5_IISDS) = {
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
      }
}

                

case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int)  extends Entry(11){
   def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)
 }

      

object SEntry11_IISSSSSSDDI_Idx0 extends EntryIdx[SEntry11_IISSSSSSDDI] {
   override def cmp(e1: SEntry11_IISSSSSSDDI, e2: SEntry11_IISSSSSSDDI) = if(e1._1 == e2._1 && e1._2 == e2._2) 0 else 1
   override def hash(e: SEntry11_IISSSSSSDDI) = {
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
      }
}

                

case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String)  extends Entry(8){
   def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8)
 }

      

object SEntry8_IIIIITDS_Idx0 extends EntryIdx[SEntry8_IIIIITDS] {
   override def cmp(e1: SEntry8_IIIIITDS, e2: SEntry8_IIIIITDS) = if((e1._1 == null.asInstanceOf[Int] || e2._1 == null.asInstanceOf[Int] || e1._1 == e2._1) && (e1._2 == null.asInstanceOf[Int] || e2._2 == null.asInstanceOf[Int] || e1._2 == e2._2) && (e1._3 == null.asInstanceOf[Int] || e2._3 == null.asInstanceOf[Int] || e1._3 == e2._3) && (e1._4 == null.asInstanceOf[Int] || e2._4 == null.asInstanceOf[Int] || e1._4 == e2._4) && (e1._5 == null.asInstanceOf[Int] || e2._5 == null.asInstanceOf[Int] || e1._5 == e2._5) && (e1._6 == null.asInstanceOf[Date] || e2._6 == null.asInstanceOf[Date] || e1._6 == e2._6) && (e1._7 == null.asInstanceOf[Double] || e2._7 == null.asInstanceOf[Double] || e1._7 == e2._7) && (e1._8 == null.asInstanceOf[String] || e2._8 == null.asInstanceOf[String] || e1._8 == e2._8)) 0 else 1
   override def hash(e: SEntry8_IIIIITDS) = {
      var hash:Int = 0xcafebabe
      var mix:Int = 0

      hash ^= 2
      hash ^= hash >>> 16
      hash *= 0x85ebca6b
      hash ^= hash >>> 13
      hash *= 0xc2b2ae35
      hash ^= hash >>> 16
      hash
      }
}

                

case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int)  extends Entry(3){
   def copy = SEntry3_III(_1, _2, _3)
 }

      

object SEntry3_III_Idx0 extends EntryIdx[SEntry3_III] {
   override def cmp(e1: SEntry3_III, e2: SEntry3_III) = if(e1._2 == e2._2 && e1._3 == e2._3) 0 else 1
   override def hash(e: SEntry3_III) = {
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
      }
}

                

object SEntry3_III_Idx1 extends EntryIdx[SEntry3_III] {
   override def cmp(x1339:SEntry3_III, x1340: SEntry3_III) = {
  val x1341 = x1339._1
  val x1342 = x1340._1
  val x1343 = x1341.==(x1342)
  val x1346 = if(x1343) 
  {
    0
  }
  else
  {
    val x1344 = x1341.>(x1342)
    val x1345 = if(x1344) 
    {
      1
    }
    else
    {
      -1
    }
    
    x1345
  }
  
  x1346
}
   override def hash(e: SEntry3_III) = {
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
      }
}

                

case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String)  extends Entry(17){
   def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17)
 }

      

object SEntry17_IIISSSSSSSSSSIIIS_Idx0 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
   override def cmp(e1: SEntry17_IIISSSSSSSSSSIIIS, e2: SEntry17_IIISSSSSSSSSSIIIS) = if(e1._1 == e2._1 && e1._2 == e2._2) 0 else 1
   override def hash(e: SEntry17_IIISSSSSSSSSSIIIS) = {
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
      }
}

                

case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean)  extends Entry(8){
   def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8)
 }

      

object SEntry8_IIIITIIB_Idx0 extends EntryIdx[SEntry8_IIIITIIB] {
   override def cmp(e1: SEntry8_IIIITIIB, e2: SEntry8_IIIITIIB) = if(e1._1 == e2._1 && e1._2 == e2._2 && e1._3 == e2._3) 0 else 1
   override def hash(e: SEntry8_IIIITIIB) = {
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
      }
}

                

object SEntry8_IIIITIIB_Idx1 extends EntryIdx[SEntry8_IIIITIIB] {
   override def cmp(e1: SEntry8_IIIITIIB, e2: SEntry8_IIIITIIB) = if(e1._2 == e2._2 && e1._3 == e2._3 && e1._4 == e2._4) 0 else 1
   override def hash(e: SEntry8_IIIITIIB) = {
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
      }
}

                

object SEntry8_IIIITIIB_Idx2 extends EntryIdx[SEntry8_IIIITIIB] {
   override def cmp(x1347:SEntry8_IIIITIIB, x1348: SEntry8_IIIITIIB) = {
  val x1349 = x1347._1
  val x1350 = x1348._1
  val x1351 = x1349.==(x1350)
  val x1354 = if(x1351) 
  {
    0
  }
  else
  {
    val x1352 = x1349.>(x1350)
    val x1353 = if(x1352) 
    {
      1
    }
    else
    {
      -1
    }
    
    x1353
  }
  
  x1354
}
   override def hash(e: SEntry8_IIIITIIB) = {
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
      }
}

                
class NewOrderTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x323: Boolean, x324: Date, x325: Int, x326: Int, x327: Int, x328: Int, x329: Int, x330: Int, x331: Array[Int], x332: Array[Int], x333: Array[Int], x334: Array[Double], x335: Array[String], x336: Array[Int], x337: Array[String], x338: Array[Double]) = {
  val x342 = if(x323) 
  {
    val x340 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x326,x327,x328)
    val x341 = println(x340)
    x341
  }
  else
  {
    ()
  }
  
  var x343: Int = 0
  var x344: Boolean = false
  val x345 = new Array[String](x329)
  var x346: Boolean = true
  val x371 = while({
    val x347 = x343
    val x348 = x347.<(x329)
    val x350 = x348.&&({
      val x349 = x346
      x349
    })
    x350
  })
  {
    val x351 = x343
    val x352 = x331.apply(x351)
    val x354 = SEntry5_IISDS(x352, null.asInstanceOf[Int], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[String])
    val x355 = x4.get(0, x354)
    val x356 = x355.==(null)
    val x367 = if(x356) 
    {
      val x357 = x346 = false
      ()
    }
    else
    {
      val x358 = x343
      val x359 = x355._3
      val x360 = x335.update(x358, x359)
      val x361 = x343
      val x362 = x355._4
      val x363 = x334.update(x361, x362)
      val x364 = x343
      val x365 = x355._5
      val x366 = x345.update(x364, x365)
      x366
    }
    
    val x368 = x343
    val x369 = x368.+(1)
    val x370 = x343 = x369
    ()
  }
  val x372 = x346
  val x482 = if(x372) 
  {
    val x374 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x328, x327, x326, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
    val x375 = x8.get(0, x374)
    val x377 = SEntry9_ISSSSSSDD(x326, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double])
    val x378 = x3.get(0, x377)
    val x380 = SEntry11_IISSSSSSDDI(x327, x326, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int])
    val x381 = x6.get(0, x380)
    val x382 = x381._11
    val x383 = x381._11 += 1
    val x384 = x6.update(x381)
    val x385 = x330.>(0)
    val x387 = SEntry8_IIIITIIB(x382,x327,x326,x328,x324,-1,x329,x385)
    val x388 = x5.insert(x387)
    val x390 = SEntry3_III(x382,x327,x326)
    val x391 = x1.insert(x390)
    var x392: Double = 0.0
    val x393 = x343 = 0
    val x481 = while({
      val x394 = x343
      val x395 = x394.<(x329)
      x395
    })
    {
      val x396 = x343
      val x397 = x332.apply(x396)
      val x398 = x343
      val x399 = x331.apply(x398)
      val x400 = x343
      val x401 = x333.apply(x400)
      val x403 = SEntry17_IIISSSSSSSSSSIIIS(x399, x397, null.asInstanceOf[Int], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
      val x404 = x9.get(0, x403)
      val x405 = x327.==(1)
      val x432 = if(x405) 
      {
        val x406 = x404._4
        x406
      }
      else
      {
        val x407 = x327.==(2)
        val x431 = if(x407) 
        {
          val x408 = x404._5
          x408
        }
        else
        {
          val x409 = x327.==(3)
          val x430 = if(x409) 
          {
            val x410 = x404._6
            x410
          }
          else
          {
            val x411 = x327.==(4)
            val x429 = if(x411) 
            {
              val x412 = x404._7
              x412
            }
            else
            {
              val x413 = x327.==(5)
              val x428 = if(x413) 
              {
                val x414 = x404._8
                x414
              }
              else
              {
                val x415 = x327.==(6)
                val x427 = if(x415) 
                {
                  val x416 = x404._9
                  x416
                }
                else
                {
                  val x417 = x327.==(7)
                  val x426 = if(x417) 
                  {
                    val x418 = x404._10
                    x418
                  }
                  else
                  {
                    val x419 = x327.==(8)
                    val x425 = if(x419) 
                    {
                      val x420 = x404._11
                      x420
                    }
                    else
                    {
                      val x421 = x327.==(9)
                      val x424 = if(x421) 
                      {
                        val x422 = x404._12
                        x422
                      }
                      else
                      {
                        val x423 = x404._13
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
            
            x429
          }
          
          x430
        }
        
        x431
      }
      
      val x433 = x404._3
      val x434 = x343
      val x435 = x336.update(x434, x433)
      val x436 = x375._14
      val x437 = x436.contains("original")
      val x440 = x437.&&({
        val x438 = x404._17
        val x439 = x438.contains("original")
        x439
      })
      val x445 = if(x440) 
      {
        val x441 = x343
        val x442 = x337.update(x441, "B")
        ()
      }
      else
      {
        val x443 = x343
        val x444 = x337.update(x443, "G")
        ()
      }
      
      val x446 = x433.-(x401)
      val x447 = x404._3 = x446
      val x448 = x433.<=(x401)
      val x450 = if(x448) 
      {
        val x449 = x404._3 += 91
        x449
      }
      else
      {
        ()
      }
      
      var x451: Int = 0
      val x452 = x397.!=(x326)
      val x454 = if(x452) 
      {
        val x453 = x451 = 1
        x453
      }
      else
      {
        ()
      }
      
      val x455 = x9.update(x404)
      val x456 = x375._16
      val x457 = x378._8
      val x458 = x381._9
      val x459 = x343
      val x460 = x334.apply(x459)
      val x461 = x401.toDouble
      val x462 = x461.*(x460)
      val x463 = 1.0.+(x457)
      val x464 = x463.+(x458)
      val x465 = x462.*(x464)
      val x466 = 1.0.-(x456)
      val x467 = x465.*(x466)
      val x468 = x343
      val x469 = x338.update(x468, x467)
      val x470 = x392
      val x471 = x470.+(x467)
      val x472 = x392 = x471
      val x473 = x343
      val x474 = x473.+(1)
      val x476 = SEntry10_IIIIIITIDS(x382,x327,x326,x474,x399,x397,null,x401,x467,x432)
      val x477 = x7.insert(x476)
      val x478 = x343
      val x479 = x478.+(1)
      val x480 = x343 = x479
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
class StockLevelTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
def apply(x123: Boolean, x124: Date, x125: Int, x126: Int, x127: Int, x128: Int) = {
  val x130 = SEntry11_IISSSSSSDDI(x127, x126, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int])
  val x131 = x6.get(0, x130)
  val x132 = x131._11
  val x133 = x132.-(20)
  var x134: Int = x133
  val x135 = Set.apply[Int]()
  val x155 = while({
    val x136 = x134
    val x137 = x136.<(x132)
    x137
  })
  {
    val x138 = x134
    val x140 = SEntry10_IIIIIITIDS(x138, x127, x126, null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Date], null.asInstanceOf[Int], null.asInstanceOf[Double], null.asInstanceOf[String])
    val x150 = { x141: SEntry10_IIIIIITIDS => {
        val x142 = x141._5
        val x144 = SEntry17_IIISSSSSSSSSSIIIS(x142, x126, null.asInstanceOf[Int], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
        val x145 = x9.get(0, x144)
        val x146 = x145._3
        val x147 = x146.<(x128)
        val x149 = if(x147) 
        {
          val x148 = x135.+=(x142)
          ()
        }
        else
        {
          ()
        }
        
        x149
      }
    }
    val x151 = x7.slice(0, x140, x150)
    val x152 = x134
    val x153 = x152.+(1)
    val x154 = x134 = x153
    x154
  }
  val x156 = x135.size
  val x166 = if(x123) 
  {
    val x157 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x126)
    val x158 = x157.+("\n District:  ")
    val x159 = x158.+(x127)
    val x160 = x159.+("\n\n Stock Level Threshold: ")
    val x161 = x160.+(x128)
    val x162 = x161.+("\n Low Stock Count:       ")
    val x163 = x162.+(x156)
    val x164 = x163.+("\n+-----------------------------------------------------------------+\n\n")
    val x165 = println(x164)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class DeliveryTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  val x68 = while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x20 = { x18: SEntry3_III => {
        val x19 = x18._1
        x19
      }
    }
    val x21 = MirrorAggregator.min(x20)
    val x22 = x15
    val x24 = SEntry3_III(null.asInstanceOf[Int], x22, x12)
    val x26 = x1.get(1, x24)
    val x27 = x26.!=(null)
    val x64 = if(x27) 
    {
      val x28 = x26._1
      val x29 = x15
      val x30 = x29.-(1)
      val x31 = x14.update(x30, x28)
      val x32 = x1.delete(x26)
      val x33 = x15
      val x35 = SEntry8_IIIITIIB(x28, x33, x12, null.asInstanceOf[Int], null.asInstanceOf[Date], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Boolean])
      val x36 = x5.get(0, x35)
      val x37 = x36._4
      val x38 = x36._6 = x13
      val x39 = x5.update(x36)
      var x40: Double = 0.0
      val x41 = x15
      val x43 = SEntry10_IIIIIITIDS(x28, x41, x12, null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Date], null.asInstanceOf[Int], null.asInstanceOf[Double], null.asInstanceOf[String])
      val x51 = { x44: SEntry10_IIIIIITIDS => {
          val x45 = x44._7 = x11
          val x46 = x40
          val x47 = x44._9
          val x48 = x46.+(x47)
          val x49 = x40 = x48
          val x50 = x7.update(x44)
          x50
        }
      }
      val x52 = x7.slice(0, x43, x51)
      val x53 = x15
      val x55 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x37, x53, x12, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
      val x56 = x8.get(0, x55)
      val x57 = x40
      val x58 = x56._17 += x57
      val x59 = x56._20 += 1
      val x60 = x8.update(x56)
      x60
    }
    else
    {
      val x61 = x15
      val x62 = x61.-(1)
      val x63 = x14.update(x62, 0)
      x63
    }
    
    val x65 = x15
    val x66 = x65.+(1)
    val x67 = x15 = x66
    x67
  }
  val x122 = if(x10) 
  {
    val x69 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
    val x70 = x69.+("\n\n Warehouse: ")
    val x71 = x70.+(x12)
    val x72 = x71.+("\n Carrier:   ")
    val x73 = x72.+(x13)
    val x74 = x73.+("\n\n Delivered Orders\n")
    var x75: String = x74
    var x76: Int = 0
    var x77: Int = 1
    val x116 = while({
      val x78 = x77
      val x79 = x78.<=(10)
      x79
    })
    {
      val x80 = x77
      val x81 = x80.-(1)
      val x82 = x14.apply(x81)
      val x83 = x82.>=(0)
      val x112 = if(x83) 
      {
        val x84 = x75
        val x85 = x84.+("  District ")
        val x86 = x77
        val x87 = x86.<(10)
        val x88 = if(x87) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x89 = x85.+(x88)
        val x90 = x77
        val x91 = x89.+(x90)
        val x92 = x91.+(": Order number ")
        val x93 = x77
        val x94 = x93.-(1)
        val x95 = x14.apply(x94)
        val x96 = x92.+(x95)
        val x97 = x96.+(" was delivered.\n")
        val x98 = x75 = x97
        x98
      }
      else
      {
        val x99 = x75
        val x100 = x99.+("  District ")
        val x101 = x77
        val x102 = x101.<(10)
        val x103 = if(x102) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x104 = x100.+(x103)
        val x105 = x77
        val x106 = x104.+(x105)
        val x107 = x106.+(": No orders to be delivered.\n")
        val x108 = x75 = x107
        val x109 = x76
        val x110 = x109.+(1)
        val x111 = x76 = x110
        x111
      }
      
      val x113 = x77
      val x114 = x113.+(1)
      val x115 = x77 = x114
      x115
    }
    val x117 = x75
    val x118 = x117.+("+-----------------------------------------------------------------+\n\n")
    val x119 = x75 = x118
    val x120 = x75
    val x121 = println(x120)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class PaymentTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x221: Boolean, x222: Date, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: Int, x229: Int, x230: String, x231: Double) = {
  val x233 = SEntry9_ISSSSSSDD(x224, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double])
  val x234 = x3.get(0, x233)
  val x235 = x234._9 += x231
  val x236 = x3.update(x234)
  val x238 = SEntry11_IISSSSSSDDI(x225, x224, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int])
  val x239 = x6.get(0, x238)
  val x240 = x239._10 += x231
  val x241 = x6.update(x239)
  var x242: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x243 = x226.>(0)
  val x276 = if(x243) 
  {
    val x244 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x246 = SEntry21_IIISSSSSSSSSTSDDDDIIS(null.asInstanceOf[Int], x228, x227, null.asInstanceOf[String], null.asInstanceOf[String], x230, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
    val x249 = { x247: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x248 = x244.append(x247)
        x248
      }
    }
    val x250 = x8.slice(1, x246, x249)
    val x251 = x244.size
    val x252 = x251./(2)
    var x253: Int = x252
    val x254 = x244.size
    val x255 = x254.%(2)
    val x256 = x255.==(0)
    val x260 = if(x256) 
    {
      val x257 = x253
      val x258 = x257.-(1)
      val x259 = x253 = x258
      x259
    }
    else
    {
      ()
    }
    
    val x267 = { (x261: SEntry21_IIISSSSSSSSSTSDDDDIIS, x262: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x263 = x261._4
        val x264 = x262._4
        val x265 = x263.compareToIgnoreCase(x264)
        val x266 = x265.<(0)
        x266
      }
    }
    val x268 = x244.sortWith(x267)
    val x269 = x253
    val x270 = x268.apply(x269)
    val x271 = x242 = x270
    x271
  }
  else
  {
    val x273 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x229, x228, x227, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
    val x274 = x8.get(0, x273)
    val x275 = x242 = x274
    x275
  }
  
  val x277 = x242
  val x278 = x277._21
  var x279: String = x278
  val x280 = x242
  val x281 = x280._14
  val x282 = x281.contains("BC")
  val x303 = if(x282) 
  {
    val x283 = x242
    val x284 = x283._1
    val x285 = x279
    val x287 = "%d %d %d %d %d $%f %s | %s".format(x284,x228,x227,x225,x224,x231,x222,x285)
    val x288 = x279 = x287
    val x289 = x279
    val x290 = x289.length
    val x291 = x290.>(500)
    val x295 = if(x291) 
    {
      val x292 = x279
      val x293 = x292.substring(0, 500)
      val x294 = x279 = x293
      x294
    }
    else
    {
      ()
    }
    
    val x296 = x242
    val x297 = x296._17 += x231
    val x298 = x242
    val x299 = x279
    val x300 = x298._21 = x299
    ()
  }
  else
  {
    val x301 = x242
    val x302 = x301._17 += x231
    x302
  }
  
  val x304 = x242
  val x305 = x8.update(x304)
  val x306 = x234._2
  val x307 = x239._3
  val x308 = x306.length
  val x309 = x308.>(10)
  val x311 = if(x309) 
  {
    val x310 = x306.substring(0, 10)
    x310
  }
  else
  {
    x306
  }
  
  val x312 = x311.+("    ")
  val x313 = x307.length
  val x314 = x313.>(10)
  val x316 = if(x314) 
  {
    val x315 = x307.substring(0, 10)
    x315
  }
  else
  {
    x307
  }
  
  val x317 = x312.+(x316)
  val x318 = x242
  val x319 = x318._1
  val x321 = SEntry8_IIIIITDS(x319,x228,x227,x225,x224,x222,x231,x317)
  val x322 = x2.insert(x321)
  1
}
}
class OrderStatusTx(x1: MStore[SEntry3_III], x2: MStore[SEntry8_IIIIITDS], x3: MStore[SEntry9_ISSSSSSDD], x4: MStore[SEntry5_IISDS], x5: MStore[SEntry8_IIIITIIB], x6: MStore[SEntry11_IISSSSSSDDI], x7: MStore[SEntry10_IIIIIITIDS], x8: MStore[SEntry21_IIISSSSSSSSSTSDDDDIIS], x9: MStore[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x167: Boolean, x168: Date, x169: Int, x170: Int, x171: Int, x172: Int, x173: Int, x174: String) = {
  var x175: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
  val x176 = x172.>(0)
  val x209 = if(x176) 
  {
    val x177 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
    val x179 = SEntry21_IIISSSSSSSSSTSDDDDIIS(null.asInstanceOf[Int], x171, x170, null.asInstanceOf[String], null.asInstanceOf[String], x174, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
    val x182 = { x180: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
        val x181 = x177.append(x180)
        x181
      }
    }
    val x183 = x8.slice(1, x179, x182)
    val x184 = x177.size
    val x185 = x184./(2)
    var x186: Int = x185
    val x187 = x177.size
    val x188 = x187.%(2)
    val x189 = x188.==(0)
    val x193 = if(x189) 
    {
      val x190 = x186
      val x191 = x190.-(1)
      val x192 = x186 = x191
      x192
    }
    else
    {
      ()
    }
    
    val x200 = { (x194: SEntry21_IIISSSSSSSSSTSDDDDIIS, x195: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
        val x196 = x194._4
        val x197 = x195._4
        val x198 = x196.compareToIgnoreCase(x197)
        val x199 = x198.<(0)
        x199
      }
    }
    val x201 = x177.sortWith(x200)
    val x202 = x186
    val x203 = x201.apply(x202)
    val x204 = x175 = x203
    x204
  }
  else
  {
    val x206 = SEntry21_IIISSSSSSSSSTSDDDDIIS(x173, x171, x170, null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[String], null.asInstanceOf[Date], null.asInstanceOf[String], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Double], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[String])
    val x207 = x8.get(0, x206)
    val x208 = x175 = x207
    x208
  }
  
  val x210 = x175
  val x211 = x210._3
  val x214 = { x212: SEntry8_IIIITIIB => {
      val x213 = x212._1
      x213
    }
  }
  val x215 = MirrorAggregator.max(x214)
  val x217 = SEntry8_IIIITIIB(null.asInstanceOf[Int], x171, x170, x211, null.asInstanceOf[Date], null.asInstanceOf[Int], null.asInstanceOf[Int], null.asInstanceOf[Boolean])
  val x219 = x5.get(2, x217)
  var x220: Int = 0
  1
}
}
