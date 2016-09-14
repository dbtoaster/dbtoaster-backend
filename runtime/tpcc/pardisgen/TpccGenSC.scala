
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def copy = SEntry5_IISDS(_1, _2, _3, _4, _5) }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def copy = SEntry3_III(_1, _2, _3) }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9) }
class SCExecutor 
{
  val x919 = { x18: SEntry3_III => {
      val x6075 = x18._1
      x6075
    }
  }
  val x4538 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x4539 = new Store[SEntry3_III](3, x4538)
  val x925 = x4539.index(0, IHash, true, -1)
  val x926 = x4539.index(1, ISliceHeapMin, false, 2)
  val x927 = x4539.index(2, INone, false, -1)
  val x4618 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4619 = new Store[SEntry8_IIIIITDS](1, x4618)
  val x932 = x4619.index(0, IList, false, -1)
  val x4637 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x4638 = new Store[SEntry9_ISSSSSSDD](1, x4637)
  val x937 = x4638.index(0, IDirect, true, 1)
  val x4656 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x4657 = new Store[SEntry5_IISDS](1, x4656)
  val x942 = x4657.index(0, IDirect, true, 100000)
  val x943 = { x210: SEntry8_IIIITIIB => {
      val x6383 = x210._1
      x6383
    }
  }
  val x4880 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4881 = new Store[SEntry8_IIIITIIB](3, x4880)
  val x949 = x4881.index(0, IHash, true, -1)
  val x950 = x4881.index(1, ISliceHeapMax, false, 2)
  val x951 = x4881.index(2, INone, false, -1)
  val x4907 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4908 = new Store[SEntry11_IISSSSSSDDI](1, x4907)
  val x956 = x4908.index(0, IDirect, true, 10)
  val x5079 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x5080 = new Store[SEntry10_IIIIIITIDS](2, x5079)
  val x961 = x5080.index(0, IHash, true, -1)
  val x962 = x5080.index(1, IHash, false, -1)
  val x5185 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x5186 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x5185)
  val x968 = x5186.index(0, IDirect, true, 30000)
  val x969 = x5186.index(1, IHash, false, -1)
  val x5211 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x5212 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x5211)
  val x974 = x5212.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x4539
  val historyTbl = x4619
  val warehouseTbl = x4638
  val itemTbl = x4657
  val orderTbl = x4881
  val districtTbl = x4908
  val orderLineTbl = x5080
  val customerTbl = x5186
  val stockTbl = x5212
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4911 : SEntry10_IIIIIITIDS) = {
      var x4912: Int = -889275714
      val x4913 = x4911._1
      val x4915 = -862048943.*((x4913.hashCode()))
      val x4920 = x4912
      val x4921 = (((x4915.<<(15)).|((x4915.>>>(-15)))).*(461845907)).^(x4920)
      x4912 = ((((x4921.<<(13)).|((x4921.>>>(-13)))).*(5)).+(-430675100))
      val x4928 = x4911._2
      val x4930 = -862048943.*((x4928.hashCode()))
      val x4935 = x4912
      val x4936 = (((x4930.<<(15)).|((x4930.>>>(-15)))).*(461845907)).^(x4935)
      x4912 = ((((x4936.<<(13)).|((x4936.>>>(-13)))).*(5)).+(-430675100))
      val x4943 = x4911._3
      val x4945 = -862048943.*((x4943.hashCode()))
      val x4950 = x4912
      val x4951 = (((x4945.<<(15)).|((x4945.>>>(-15)))).*(461845907)).^(x4950)
      x4912 = ((((x4951.<<(13)).|((x4951.>>>(-13)))).*(5)).+(-430675100))
      val x4958 = x4911._4
      val x4960 = -862048943.*((x4958.hashCode()))
      val x4965 = x4912
      val x4966 = (((x4960.<<(15)).|((x4960.>>>(-15)))).*(461845907)).^(x4965)
      x4912 = ((((x4966.<<(13)).|((x4966.>>>(-13)))).*(5)).+(-430675100))
      val x4973 = x4912
      val x4974 = x4973.^(2)
      val x4977 = (x4974.^((x4974.>>>(16)))).*(-2048144789)
      val x4980 = (x4977.^((x4977.>>>(13)))).*(-1028477387)
      (x4980.^((x4980.>>>(16))))
    }
    override def cmp(x4984 : SEntry10_IIIIIITIDS , x4985 : SEntry10_IIIIIITIDS) = {
      val x4986 = x4984._1
      val x4987 = x4985._1
      (if(((((x4986.==(x4987)).&&({
        val x4989 = x4984._2
        val x4990 = x4985._2
        (x4989.==(x4990))
      })).&&({
        val x4993 = x4984._3
        val x4994 = x4985._3
        (x4993.==(x4994))
      })).&&({
        val x4997 = x4984._4
        val x4998 = x4985._4
        (x4997.==(x4998))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4805 : SEntry8_IIIITIIB) = {
      var x4806: Int = -889275714
      val x4807 = x4805._2
      val x4809 = -862048943.*((x4807.hashCode()))
      val x4814 = x4806
      val x4815 = (((x4809.<<(15)).|((x4809.>>>(-15)))).*(461845907)).^(x4814)
      x4806 = ((((x4815.<<(13)).|((x4815.>>>(-13)))).*(5)).+(-430675100))
      val x4822 = x4805._3
      val x4824 = -862048943.*((x4822.hashCode()))
      val x4829 = x4806
      val x4830 = (((x4824.<<(15)).|((x4824.>>>(-15)))).*(461845907)).^(x4829)
      x4806 = ((((x4830.<<(13)).|((x4830.>>>(-13)))).*(5)).+(-430675100))
      val x4837 = x4805._4
      val x4839 = -862048943.*((x4837.hashCode()))
      val x4844 = x4806
      val x4845 = (((x4839.<<(15)).|((x4839.>>>(-15)))).*(461845907)).^(x4844)
      x4806 = ((((x4845.<<(13)).|((x4845.>>>(-13)))).*(5)).+(-430675100))
      val x4852 = x4806
      val x4853 = x4852.^(2)
      val x4856 = (x4853.^((x4853.>>>(16)))).*(-2048144789)
      val x4859 = (x4856.^((x4856.>>>(13)))).*(-1028477387)
      (x4859.^((x4859.>>>(16))))
    }
    override def cmp(x4863 : SEntry8_IIIITIIB , x4864 : SEntry8_IIIITIIB) = {
      val x4865 = x4863._2
      val x4866 = x4864._2
      (if((((x4865.==(x4866)).&&({
        val x4868 = x4863._3
        val x4869 = x4864._3
        (x4868.==(x4869))
      })).&&({
        val x4872 = x4863._4
        val x4873 = x4864._4
        (x4872.==(x4873))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x4355 : SEntry3_III) = {
      var x4356: Int = -889275714
      val x4357 = x4355._1
      val x4359 = -862048943.*((x4357.hashCode()))
      val x4364 = x4356
      val x4365 = (((x4359.<<(15)).|((x4359.>>>(-15)))).*(461845907)).^(x4364)
      x4356 = ((((x4365.<<(13)).|((x4365.>>>(-13)))).*(5)).+(-430675100))
      val x4372 = x4355._2
      val x4374 = -862048943.*((x4372.hashCode()))
      val x4379 = x4356
      val x4380 = (((x4374.<<(15)).|((x4374.>>>(-15)))).*(461845907)).^(x4379)
      x4356 = ((((x4380.<<(13)).|((x4380.>>>(-13)))).*(5)).+(-430675100))
      val x4387 = x4355._3
      val x4389 = -862048943.*((x4387.hashCode()))
      val x4394 = x4356
      val x4395 = (((x4389.<<(15)).|((x4389.>>>(-15)))).*(461845907)).^(x4394)
      x4356 = ((((x4395.<<(13)).|((x4395.>>>(-13)))).*(5)).+(-430675100))
      val x4402 = x4356
      val x4403 = x4402.^(2)
      val x4406 = (x4403.^((x4403.>>>(16)))).*(-2048144789)
      val x4409 = (x4406.^((x4406.>>>(13)))).*(-1028477387)
      (x4409.^((x4409.>>>(16))))
    }
    override def cmp(x4413 : SEntry3_III , x4414 : SEntry3_III) = {
      val x4415 = x4413._1
      val x4416 = x4414._1
      (if((((x4415.==(x4416)).&&({
        val x4418 = x4413._2
        val x4419 = x4414._2
        (x4418.==(x4419))
      })).&&({
        val x4422 = x4413._3
        val x4423 = x4414._3
        (x4422.==(x4423))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x5004 : SEntry10_IIIIIITIDS) = {
      var x5005: Int = -889275714
      val x5006 = x5004._1
      val x5008 = -862048943.*((x5006.hashCode()))
      val x5013 = x5005
      val x5014 = (((x5008.<<(15)).|((x5008.>>>(-15)))).*(461845907)).^(x5013)
      x5005 = ((((x5014.<<(13)).|((x5014.>>>(-13)))).*(5)).+(-430675100))
      val x5021 = x5004._2
      val x5023 = -862048943.*((x5021.hashCode()))
      val x5028 = x5005
      val x5029 = (((x5023.<<(15)).|((x5023.>>>(-15)))).*(461845907)).^(x5028)
      x5005 = ((((x5029.<<(13)).|((x5029.>>>(-13)))).*(5)).+(-430675100))
      val x5036 = x5004._3
      val x5038 = -862048943.*((x5036.hashCode()))
      val x5043 = x5005
      val x5044 = (((x5038.<<(15)).|((x5038.>>>(-15)))).*(461845907)).^(x5043)
      x5005 = ((((x5044.<<(13)).|((x5044.>>>(-13)))).*(5)).+(-430675100))
      val x5051 = x5005
      val x5052 = x5051.^(2)
      val x5055 = (x5052.^((x5052.>>>(16)))).*(-2048144789)
      val x5058 = (x5055.^((x5055.>>>(13)))).*(-1028477387)
      (x5058.^((x5058.>>>(16))))
    }
    override def cmp(x5062 : SEntry10_IIIIIITIDS , x5063 : SEntry10_IIIIIITIDS) = {
      val x5064 = x5062._1
      val x5065 = x5063._1
      (if((((x5064.==(x5065)).&&({
        val x5067 = x5062._2
        val x5068 = x5063._2
        (x5067.==(x5068))
      })).&&({
        val x5071 = x5062._3
        val x5072 = x5063._3
        (x5071.==(x5072))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4482 : SEntry3_III) = {
      var x4483: Int = -889275714
      val x4484 = x4482._2
      val x4486 = -862048943.*((x4484.hashCode()))
      val x4491 = x4483
      val x4492 = (((x4486.<<(15)).|((x4486.>>>(-15)))).*(461845907)).^(x4491)
      x4483 = ((((x4492.<<(13)).|((x4492.>>>(-13)))).*(5)).+(-430675100))
      val x4499 = x4482._3
      val x4501 = -862048943.*((x4499.hashCode()))
      val x4506 = x4483
      val x4507 = (((x4501.<<(15)).|((x4501.>>>(-15)))).*(461845907)).^(x4506)
      x4483 = ((((x4507.<<(13)).|((x4507.>>>(-13)))).*(5)).+(-430675100))
      val x4514 = x4483
      val x4515 = x4514.^(2)
      val x4518 = (x4515.^((x4515.>>>(16)))).*(-2048144789)
      val x4521 = (x4518.^((x4518.>>>(13)))).*(-1028477387)
      (x4521.^((x4521.>>>(16))))
    }
    override def cmp(x4525 : SEntry3_III , x4526 : SEntry3_III) = {
      val x4527 = x4525._2
      val x4528 = x4526._2
      (if(((x4527.==(x4528)).&&({
        val x4530 = x4525._3
        val x4531 = x4526._3
        (x4530.==(x4531))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4544 : SEntry8_IIIIITDS) = {
      var x4545: Int = -889275714
      val x4546 = x4545
      val x4547 = x4546.^(2)
      val x4550 = (x4547.^((x4547.>>>(16)))).*(-2048144789)
      val x4553 = (x4550.^((x4550.>>>(13)))).*(-1028477387)
      (x4553.^((x4553.>>>(16))))
    }
    override def cmp(x4557 : SEntry8_IIIIITDS , x4558 : SEntry8_IIIIITDS) = {
      val x4559 = x4557._1
      val x4560 = x4558._1
      (if((((((((((x4559.==(-1)).||({
        (x4560.==(-1))
      })).||({
        (x4559.==(x4560))
      })).&&({
        val x4566 = x4557._2
        val x4567 = x4558._2
        (((x4566.==(-1)).||({
          (x4567.==(-1))
        })).||({
          (x4566.==(x4567))
        }))
      })).&&({
        val x4574 = x4557._3
        val x4575 = x4558._3
        (((x4574.==(-1)).||({
          (x4575.==(-1))
        })).||({
          (x4574.==(x4575))
        }))
      })).&&({
        val x4582 = x4557._4
        val x4583 = x4558._4
        (((x4582.==(-1)).||({
          (x4583.==(-1))
        })).||({
          (x4582.==(x4583))
        }))
      })).&&({
        val x4590 = x4557._5
        val x4591 = x4558._5
        (((x4590.==(-1)).||({
          (x4591.==(-1))
        })).||({
          (x4590.==(x4591))
        }))
      })).&&({
        val x4598 = x4557._6
        val x4599 = x4558._6
        (((x4598.==(null)).||({
          (x4599.==(null))
        })).||({
          (x4598.==(x4599))
        }))
      })).&&({
        val x4606 = x4557._7
        val x4607 = x4558._7
        (((x4606.==(-1.0)).||({
          (x4607.==(-1.0))
        })).||({
          (x4606.==(x4607))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5110 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5111: Int = -889275714
      val x5112 = x5110._2
      val x5114 = -862048943.*((x5112.hashCode()))
      val x5119 = x5111
      val x5120 = (((x5114.<<(15)).|((x5114.>>>(-15)))).*(461845907)).^(x5119)
      x5111 = ((((x5120.<<(13)).|((x5120.>>>(-13)))).*(5)).+(-430675100))
      val x5127 = x5110._3
      val x5129 = -862048943.*((x5127.hashCode()))
      val x5134 = x5111
      val x5135 = (((x5129.<<(15)).|((x5129.>>>(-15)))).*(461845907)).^(x5134)
      x5111 = ((((x5135.<<(13)).|((x5135.>>>(-13)))).*(5)).+(-430675100))
      val x5142 = x5110._6
      val x5144 = -862048943.*((x5142.hashCode()))
      val x5149 = x5111
      val x5150 = (((x5144.<<(15)).|((x5144.>>>(-15)))).*(461845907)).^(x5149)
      x5111 = ((((x5150.<<(13)).|((x5150.>>>(-13)))).*(5)).+(-430675100))
      val x5157 = x5111
      val x5158 = x5157.^(2)
      val x5161 = (x5158.^((x5158.>>>(16)))).*(-2048144789)
      val x5164 = (x5161.^((x5161.>>>(13)))).*(-1028477387)
      (x5164.^((x5164.>>>(16))))
    }
    override def cmp(x5168 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5169 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5170 = x5168._2
      val x5171 = x5169._2
      (if((((x5170.==(x5171)).&&({
        val x5173 = x5168._3
        val x5174 = x5169._3
        (x5173.==(x5174))
      })).&&({
        val x5177 = x5168._6
        val x5178 = x5169._6
        (x5177.==(x5178))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4663 : SEntry8_IIIITIIB) = {
      var x4664: Int = -889275714
      val x4665 = x4663._1
      val x4667 = -862048943.*((x4665.hashCode()))
      val x4672 = x4664
      val x4673 = (((x4667.<<(15)).|((x4667.>>>(-15)))).*(461845907)).^(x4672)
      x4664 = ((((x4673.<<(13)).|((x4673.>>>(-13)))).*(5)).+(-430675100))
      val x4680 = x4663._2
      val x4682 = -862048943.*((x4680.hashCode()))
      val x4687 = x4664
      val x4688 = (((x4682.<<(15)).|((x4682.>>>(-15)))).*(461845907)).^(x4687)
      x4664 = ((((x4688.<<(13)).|((x4688.>>>(-13)))).*(5)).+(-430675100))
      val x4695 = x4663._3
      val x4697 = -862048943.*((x4695.hashCode()))
      val x4702 = x4664
      val x4703 = (((x4697.<<(15)).|((x4697.>>>(-15)))).*(461845907)).^(x4702)
      x4664 = ((((x4703.<<(13)).|((x4703.>>>(-13)))).*(5)).+(-430675100))
      val x4710 = x4664
      val x4711 = x4710.^(2)
      val x4714 = (x4711.^((x4711.>>>(16)))).*(-2048144789)
      val x4717 = (x4714.^((x4714.>>>(13)))).*(-1028477387)
      (x4717.^((x4717.>>>(16))))
    }
    override def cmp(x4721 : SEntry8_IIIITIIB , x4722 : SEntry8_IIIITIIB) = {
      val x4723 = x4721._1
      val x4724 = x4722._1
      (if((((x4723.==(x4724)).&&({
        val x4726 = x4721._2
        val x4727 = x4722._2
        (x4726.==(x4727))
      })).&&({
        val x4730 = x4721._3
        val x4731 = x4722._3
        (x4730.==(x4731))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4429 : SEntry3_III) = {
      var x4430: Int = -889275714
      val x4431 = x4429._2
      val x4433 = -862048943.*((x4431.hashCode()))
      val x4438 = x4430
      val x4439 = (((x4433.<<(15)).|((x4433.>>>(-15)))).*(461845907)).^(x4438)
      x4430 = ((((x4439.<<(13)).|((x4439.>>>(-13)))).*(5)).+(-430675100))
      val x4446 = x4429._3
      val x4448 = -862048943.*((x4446.hashCode()))
      val x4453 = x4430
      val x4454 = (((x4448.<<(15)).|((x4448.>>>(-15)))).*(461845907)).^(x4453)
      x4430 = ((((x4454.<<(13)).|((x4454.>>>(-13)))).*(5)).+(-430675100))
      val x4461 = x4430
      val x4462 = x4461.^(2)
      val x4465 = (x4462.^((x4462.>>>(16)))).*(-2048144789)
      val x4468 = (x4465.^((x4465.>>>(13)))).*(-1028477387)
      (x4468.^((x4468.>>>(16))))
    }
    override def cmp(x4472 : SEntry3_III , x4473 : SEntry3_III) = {
      val x4474 = x919.apply(x4472)
      val x4475 = x919.apply(x4473)
      val x4478 = if((x4474.>(x4475))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4474.==(x4475))) 0 else x4478)
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4737 : SEntry8_IIIITIIB) = {
      var x4738: Int = -889275714
      val x4739 = x4737._2
      val x4741 = -862048943.*((x4739.hashCode()))
      val x4746 = x4738
      val x4747 = (((x4741.<<(15)).|((x4741.>>>(-15)))).*(461845907)).^(x4746)
      x4738 = ((((x4747.<<(13)).|((x4747.>>>(-13)))).*(5)).+(-430675100))
      val x4754 = x4737._3
      val x4756 = -862048943.*((x4754.hashCode()))
      val x4761 = x4738
      val x4762 = (((x4756.<<(15)).|((x4756.>>>(-15)))).*(461845907)).^(x4761)
      x4738 = ((((x4762.<<(13)).|((x4762.>>>(-13)))).*(5)).+(-430675100))
      val x4769 = x4737._4
      val x4771 = -862048943.*((x4769.hashCode()))
      val x4776 = x4738
      val x4777 = (((x4771.<<(15)).|((x4771.>>>(-15)))).*(461845907)).^(x4776)
      x4738 = ((((x4777.<<(13)).|((x4777.>>>(-13)))).*(5)).+(-430675100))
      val x4784 = x4738
      val x4785 = x4784.^(2)
      val x4788 = (x4785.^((x4785.>>>(16)))).*(-2048144789)
      val x4791 = (x4788.^((x4788.>>>(13)))).*(-1028477387)
      (x4791.^((x4791.>>>(16))))
    }
    override def cmp(x4795 : SEntry8_IIIITIIB , x4796 : SEntry8_IIIITIIB) = {
      val x4797 = x943.apply(x4795)
      val x4798 = x943.apply(x4796)
      val x4801 = if((x4797.>(x4798))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4797.==(x4798))) 0 else x4801)
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4625 : SEntry9_ISSSSSSDD) = {
      var x4626: Int = 0
      val x4627 = x4625._1
      val x4629 = x4626
      x4626 = ((x4629.*(1)).+((x4627.-(1))))
      val x4633 = x4626
      x4633
    }
    override def cmp(x4622 : SEntry9_ISSSSSSDD , x4623 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4644 : SEntry5_IISDS) = {
      var x4645: Int = 0
      val x4646 = x4644._1
      val x4648 = x4645
      x4645 = ((x4648.*(100000)).+((x4646.-(1))))
      val x4652 = x4645
      x4652
    }
    override def cmp(x4641 : SEntry5_IISDS , x4642 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4889 : SEntry11_IISSSSSSDDI) = {
      var x4890: Int = 0
      val x4891 = x4889._1
      val x4893 = x4890
      x4890 = ((x4893.*(10)).+((x4891.-(1))))
      val x4897 = x4889._2
      val x4899 = x4890
      x4890 = ((x4899.*(1)).+((x4897.-(1))))
      val x4903 = x4890
      x4903
    }
    override def cmp(x4886 : SEntry11_IISSSSSSDDI , x4887 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5087 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5088: Int = 0
      val x5089 = x5087._1
      val x5091 = x5088
      x5088 = ((x5091.*(3000)).+((x5089.-(1))))
      val x5095 = x5087._2
      val x5097 = x5088
      x5088 = ((x5097.*(10)).+((x5095.-(1))))
      val x5101 = x5087._3
      val x5103 = x5088
      x5088 = ((x5103.*(1)).+((x5101.-(1))))
      val x5107 = x5088
      x5107
    }
    override def cmp(x5084 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5085 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5193 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5194: Int = 0
      val x5195 = x5193._1
      val x5197 = x5194
      x5194 = ((x5197.*(100000)).+((x5195.-(1))))
      val x5201 = x5193._2
      val x5203 = x5194
      x5194 = ((x5203.*(1)).+((x5201.-(1))))
      val x5207 = x5194
      x5207
    }
    override def cmp(x5190 : SEntry17_IIISSSSSSSSSSIIIS , x5191 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x7817 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x8346 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8336 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7826 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8116 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8637 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8631 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7830 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8661 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8104 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8237 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x8230 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8364 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8212 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8331 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x7806 = SEntry3_III(-1, -1, -1)
  val x8149 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8634 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8611 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  class DeliveryTx(x4539: Store[SEntry3_III], x4619: Store[SEntry8_IIIIITDS], x4638: Store[SEntry9_ISSSSSSDD], x4657: Store[SEntry5_IISDS], x4881: Store[SEntry8_IIIITIIB], x4908: Store[SEntry11_IISSSSSSDDI], x5080: Store[SEntry10_IIIIIITIDS], x5186: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5212: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x7806._2_=(x22)
        x7806._3_=(x12)
        val x12816 = x926.get(x7806)
        if((x12816.!=(null))) 
        {
          val x7811 = x12816._1
          val x29 = x15
          x14.update((x29.-(1)), x7811)
          x925.delete(x12816)
          x926.delete(x12816)
          val x33 = x15
          x7817._1_=(x7811)
          x7817._2_=(x33)
          x7817._3_=(x12)
          val x12830 = x949.get(x7817)
          val x7820 = x12830._4
          x12830._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x7826._1_=(x7811)
          x7826._2_=(x41)
          x7826._3_=(x12)
          x962.slice(x7826, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x7928 = x44._9
              x40 = (x46.+(x7928))
              ()
            }
          }))
          val x53 = x15
          x7830._1_=(x7820)
          x7830._2_=(x53)
          x7830._3_=(x12)
          val x12851 = x968.get(x7830)
          val x56 = x40
          x12851._17 +=(x56)
          x12851._20 +=(1)
          ()
        }
        else
        {
          val x60 = x15
          x14.update((x60.-(1)), 0)
          ()
        }
        
        val x64 = x15
        x15 = (x64.+(1))
        ()
      }
      if(x10) 
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
        while({
          val x77 = x76
          (x77.<=(10))
        })
        {
          val x79 = x76
          val x81 = x14.apply((x79.-(1)))
          if((x81.>=(0))) 
          {
            val x83 = x74
            val x84 = x83.+("  District ")
            val x85 = x76
            val x87 = if((x85.<(10))) 
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
            val x94 = x14.apply((x92.-(1)))
            val x95 = x91.+(x94)
            val x96 = x95.+(" was delivered.\n")
            x74 = x96
            ()
          }
          else
          {
            val x98 = x74
            val x99 = x98.+("  District ")
            val x100 = x76
            val x102 = if((x100.<(10))) 
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
            x74 = x106
            val x108 = x75
            x75 = (x108.+(1))
            ()
          }
          
          val x112 = x76
          x76 = (x112.+(1))
          ()
        }
        val x116 = x74
        val x117 = x116.+("+-----------------------------------------------------------------+\n\n")
        x74 = x117
        val x119 = x74
        println(x119)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class StockLevelTx(x4539: Store[SEntry3_III], x4619: Store[SEntry8_IIIIITDS], x4638: Store[SEntry9_ISSSSSSDD], x4657: Store[SEntry5_IISDS], x4881: Store[SEntry8_IIIITIIB], x4908: Store[SEntry11_IISSSSSSDDI], x5080: Store[SEntry10_IIIIIITIDS], x5186: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5212: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) =     {
      x8104._1_=(x126)
      x8104._2_=(x125)
      val x13027 = x956.get(x8104)
      val x8107 = x13027._11
      var x133: Int = (x8107.-(20))
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        (x135.<(x8107))
      })
      {
        val x137 = x133
        x8116._1_=(x137)
        x8116._2_=(x126)
        x8116._3_=(x125)
        x962.slice(x8116, ({ x140: SEntry10_IIIIIITIDS => {
            val x8148 = x140._5
            x8149._1_=(x8148)
            x8149._2_=(x125)
            val x13045 = x974.get(x8149)
            val x8151 = x13045._3
            if((x8151.<(x127))) 
            {
              val x146 = x134.+=(x8148)
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x150 = x133
        x133 = (x150.+(1))
        ()
      }
      val x154 = x134.size
      if(x122) 
      {
        val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x125)
        val x156 = x155.+("\n District:  ")
        val x157 = x156.+(x126)
        val x158 = x157.+("\n\n Stock Level Threshold: ")
        val x159 = x158.+(x127)
        val x160 = x159.+("\n Low Stock Count:       ")
        val x161 = x160.+(x154)
        val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
        println(x162)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class OrderStatusTx(x4539: Store[SEntry3_III], x4619: Store[SEntry8_IIIIITDS], x4638: Store[SEntry9_ISSSSSSDD], x4657: Store[SEntry5_IISDS], x4881: Store[SEntry8_IIIITIIB], x4908: Store[SEntry11_IISSSSSSDDI], x5080: Store[SEntry10_IIIIIITIDS], x5186: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5212: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) =     {
      var x8207: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x170.>(0))) 
      {
        val x8210 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8212._2_=(x169)
        x8212._3_=(x168)
        x8212._6_=(x172)
        x969.slice(x8212, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8210.append(x178)
            ()
          }
        }))
        val x182 = x8210.size
        var x184: Int = (x182./(2))
        val x185 = x8210.size
        if(((x185.%(2)).==(0))) 
        {
          val x188 = x184
          x184 = (x188.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x199 = x8210.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8266 = x192._4
            val x8267 = x193._4
            val x196 = x8266.compareToIgnoreCase(x8267)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x201 = x199.apply(x200)
        x8207 = x201
        ()
      }
      else
      {
        x8230._1_=(x171)
        x8230._2_=(x169)
        x8230._3_=(x168)
        val x13143 = x968.get(x8230)
        x8207 = x13143
        ()
      }
      
      val x208 = x8207
      val x8235 = x208._3
      x8237._2_=(x169)
      x8237._3_=(x168)
      x8237._4_=(x8235)
      val x13152 = x950.get(x8237)
      var x218: Int = 0
      val x8241 = x13152._1
      x218 = x8241
      1
    }
  }
  class PaymentTx(x4539: Store[SEntry3_III], x4619: Store[SEntry8_IIIIITDS], x4638: Store[SEntry9_ISSSSSSDD], x4657: Store[SEntry5_IISDS], x4881: Store[SEntry8_IIIITIIB], x4908: Store[SEntry11_IISSSSSSDDI], x5080: Store[SEntry10_IIIIIITIDS], x5186: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5212: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x221: Boolean, x222: Date, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: Int, x229: Int, x230: String, x231: Double) =     {
      x8331._1_=(x224)
      val x13208 = x937.get(x8331)
      x13208._9 +=(x231)
      x8336._1_=(x225)
      x8336._2_=(x224)
      val x13213 = x956.get(x8336)
      x13213._10 +=(x231)
      var x8341: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x226.>(0))) 
      {
        val x8344 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8346._2_=(x228)
        x8346._3_=(x227)
        x8346._6_=(x230)
        x969.slice(x8346, ({ x247: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8344.append(x247)
            ()
          }
        }))
        val x251 = x8344.size
        var x253: Int = (x251./(2))
        val x254 = x8344.size
        if(((x254.%(2)).==(0))) 
        {
          val x257 = x253
          x253 = (x257.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x268 = x8344.sortWith(({ (x261: SEntry21_IIISSSSSSSSSTSDDDDIIS, x262: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8447 = x261._4
            val x8448 = x262._4
            val x265 = x8447.compareToIgnoreCase(x8448)
            (x265.<(0))
          }
        }))
        val x269 = x253
        val x270 = x268.apply(x269)
        x8341 = x270
        ()
      }
      else
      {
        x8364._1_=(x229)
        x8364._2_=(x228)
        x8364._3_=(x227)
        val x13252 = x968.get(x8364)
        x8341 = x13252
        ()
      }
      
      val x277 = x8341
      val x8369 = x277._21
      var x279: String = x8369
      val x280 = x8341
      val x8372 = x280._14
      val x282 = x8372.contains("BC")
      if(x282) 
      {
        val x283 = x8341
        val x8376 = x283._1
        val x285 = x279
        val x287 = "%d %d %d %d %d $%f %s | %s".format(x8376,x228,x227,x225,x224,x231,x222,x285)
        x279 = x287
        val x289 = x279
        val x290 = x289.length
        if((x290.>(500))) 
        {
          val x292 = x279
          val x293 = x292.substring(0, 500)
          x279 = x293
          ()
        }
        else
        {
          ()
        }
        
        val x296 = x8341
        x296._17 +=(x231)
        val x298 = x8341
        val x299 = x279
        x298._21_=(x299)
        ()
      }
      else
      {
        val x301 = x8341
        x301._17 +=(x231)
        ()
      }
      
      val x304 = x8341
      x969.update(x304)
      x968.update(x304)
      val x8397 = x13208._2
      val x8398 = x13213._3
      val x308 = x8397.length
      val x311 = if((x308.>(10))) 
      {
        val x310 = x8397.substring(0, 10)
        x310
      }
      else
      {
        x8397
      }
      
      val x312 = x311.+("    ")
      val x313 = x8398.length
      val x316 = if((x313.>(10))) 
      {
        val x315 = x8398.substring(0, 10)
        x315
      }
      else
      {
        x8398
      }
      
      val x317 = x312.+(x316)
      val x318 = x8341
      val x8410 = x318._1
      x4619.insert((SEntry8_IIIIITDS(x8410, x228, x227, x225, x224, x222, x231, x317)))
      1
    }
  }
  class NewOrderTx(x4539: Store[SEntry3_III], x4619: Store[SEntry8_IIIIITDS], x4638: Store[SEntry9_ISSSSSSDD], x4657: Store[SEntry5_IISDS], x4881: Store[SEntry8_IIIITIIB], x4908: Store[SEntry11_IISSSSSSDDI], x5080: Store[SEntry10_IIIIIITIDS], x5186: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5212: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x323: Boolean, x324: Date, x325: Int, x326: Int, x327: Int, x328: Int, x329: Int, x330: Int, x331: Array[Int], x332: Array[Int], x333: Array[Int], x334: Array[Double], x335: Array[String], x336: Array[Int], x337: Array[String], x338: Array[Double]) =     {
      if(x323) 
      {
        val x340 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x326,x327,x328)
        println(x340)
        ()
      }
      else
      {
        ()
      }
      
      var x343: Int = 0
      var x344: Boolean = false
      val x345 = new Array[String](x329)
      var x346: Boolean = true
      while({
        val x347 = x343
        ((x347.<(x329)).&&({
          val x349 = x346
          x349
        }))
      })
      {
        val x351 = x343
        val x352 = x331.apply(x351)
        x8611._1_=(x352)
        val x13413 = x942.get(x8611)
        if((x13413.==(null))) 
        {
          x346 = false
          ()
        }
        else
        {
          val x358 = x343
          val x8618 = x13413._3
          x335.update(x358, x8618)
          val x361 = x343
          val x8621 = x13413._4
          x334.update(x361, x8621)
          val x364 = x343
          val x8624 = x13413._5
          x345.update(x364, x8624)
          ()
        }
        
        val x368 = x343
        x343 = (x368.+(1))
        ()
      }
      val x372 = x346
      if(x372) 
      {
        x8631._1_=(x328)
        x8631._2_=(x327)
        x8631._3_=(x326)
        val x13435 = x968.get(x8631)
        x8634._1_=(x326)
        val x13438 = x937.get(x8634)
        x8637._1_=(x327)
        x8637._2_=(x326)
        val x13442 = x956.get(x8637)
        val x8640 = x13442._11
        x13442._11 +=(1)
        x4881.insert((SEntry8_IIIITIIB(x8640, x327, x326, x328, x324, -1, x329, (x330.>(0)))))
        x4539.insert((SEntry3_III(x8640, x327, x326)))
        var x392: Double = 0.0
        x343 = 0
        while({
          val x394 = x343
          (x394.<(x329))
        })
        {
          val x396 = x343
          val x397 = x332.apply(x396)
          val x398 = x343
          val x399 = x331.apply(x398)
          val x400 = x343
          val x401 = x333.apply(x400)
          x8661._1_=(x399)
          x8661._2_=(x397)
          val x13465 = x974.get(x8661)
          val x431 = if((x327.==(1))) 
          {
            val x8665 = x13465._4
            x8665
          }
          else
          {
            val x430 = if((x327.==(2))) 
            {
              val x8668 = x13465._5
              x8668
            }
            else
            {
              val x429 = if((x327.==(3))) 
              {
                val x8671 = x13465._6
                x8671
              }
              else
              {
                val x428 = if((x327.==(4))) 
                {
                  val x8674 = x13465._7
                  x8674
                }
                else
                {
                  val x427 = if((x327.==(5))) 
                  {
                    val x8677 = x13465._8
                    x8677
                  }
                  else
                  {
                    val x426 = if((x327.==(6))) 
                    {
                      val x8680 = x13465._9
                      x8680
                    }
                    else
                    {
                      val x425 = if((x327.==(7))) 
                      {
                        val x8683 = x13465._10
                        x8683
                      }
                      else
                      {
                        val x424 = if((x327.==(8))) 
                        {
                          val x8686 = x13465._11
                          x8686
                        }
                        else
                        {
                          val x423 = if((x327.==(9))) 
                          {
                            val x8689 = x13465._12
                            x8689
                          }
                          else
                          {
                            val x8690 = x13465._13
                            x8690
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
              
              x429
            }
            
            x430
          }
          
          val x8691 = x13465._3
          val x433 = x343
          x336.update(x433, x8691)
          val x8694 = x13435._14
          val x436 = x8694.contains("original")
          if((x436.&&({
            val x8697 = x13465._17
            val x438 = x8697.contains("original")
            x438
          }))) 
          {
            val x440 = x343
            x337.update(x440, "B")
            ()
          }
          else
          {
            val x442 = x343
            x337.update(x442, "G")
            ()
          }
          
          x13465._3_=((x8691.-(x401)))
          if((x8691.<=(x401))) 
          {
            x13465._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x450: Int = 0
          if((x397.!=(x326))) 
          {
            x450 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8714 = x13435._16
          val x8715 = x13438._8
          val x8716 = x13442._9
          val x458 = x343
          val x459 = x334.apply(x458)
          val x466 = (((x401.toDouble).*(x459)).*(((1.0.+(x8715)).+(x8716)))).*((1.0.-(x8714)))
          val x467 = x343
          x338.update(x467, x466)
          val x469 = x392
          x392 = (x469.+(x466))
          val x472 = x343
          x5080.insert((SEntry10_IIIIIITIDS(x8640, x327, x326, (x472.+(1)), x399, x397, null, x401, x466, x431)))
          val x477 = x343
          x343 = (x477.+(1))
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

}
