
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
  val x914 = { x18: SEntry3_III => {
      val x6169 = x18._1
      x6169
    }
  }
  val x4388 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x4389 = new Store[SEntry3_III](2, x4388)
  val x920 = x4389.index(0, ISliceHeapMin, false, 1)
  val x921 = x4389.index(1, INone, false, -1)
  val x4467 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4468 = new Store[SEntry8_IIIIITDS](1, x4467)
  val x926 = x4468.index(0, IList, false, -1)
  val x4508 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1)
  val x4509 = new Store[SEntry9_ISSSSSSDD](1, x4508)
  val x931 = x4509.index(0, IHash, true, -1)
  val x4548 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1)
  val x4549 = new Store[SEntry5_IISDS](1, x4548)
  val x934 = x4549.index(0, IHash, true, -1)
  val x936 = { x210: SEntry8_IIIITIIB => {
      val x6445 = x210._1
      x6445
    }
  }
  val x4772 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4773 = new Store[SEntry8_IIIITIIB](3, x4772)
  val x942 = x4773.index(0, IHash, true, -1)
  val x943 = x4773.index(1, ISliceHeapMax, false, 2)
  val x944 = x4773.index(2, INone, false, -1)
  val x4834 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx12)
  val x4835 = new Store[SEntry11_IISSSSSSDDI](1, x4834)
  val x949 = x4835.index(0, IHash, true, -1)
  val x5006 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x5007 = new Store[SEntry10_IIIIIITIDS](2, x5006)
  val x954 = x5007.index(0, IHash, true, -1)
  val x955 = x5007.index(1, IHash, false, -1)
  val x5160 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x5161 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x5160)
  val x960 = x5161.index(0, IHash, true, -1)
  val x961 = x5161.index(1, IHash, false, -1)
  val x5220 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx12)
  val x5221 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x5220)
  val x964 = x5221.index(0, IHash, true, -1)
  
  val newOrderTbl = x4389
  val historyTbl = x4468
  val warehouseTbl = x4509
  val itemTbl = x4549
  val orderTbl = x4773
  val districtTbl = x4835
  val orderLineTbl = x5007
  val customerTbl = x5161
  val stockTbl = x5221
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4838 : SEntry10_IIIIIITIDS) = {
      var x4839: Int = -889275714
      val x4840 = x4838._1
      val x4842 = -862048943.*((x4840.hashCode()))
      val x4847 = x4839
      val x4848 = (((x4842.<<(15)).|((x4842.>>>(-15)))).*(461845907)).^(x4847)
      x4839 = ((((x4848.<<(13)).|((x4848.>>>(-13)))).*(5)).+(-430675100))
      val x4855 = x4838._2
      val x4857 = -862048943.*((x4855.hashCode()))
      val x4862 = x4839
      val x4863 = (((x4857.<<(15)).|((x4857.>>>(-15)))).*(461845907)).^(x4862)
      x4839 = ((((x4863.<<(13)).|((x4863.>>>(-13)))).*(5)).+(-430675100))
      val x4870 = x4838._3
      val x4872 = -862048943.*((x4870.hashCode()))
      val x4877 = x4839
      val x4878 = (((x4872.<<(15)).|((x4872.>>>(-15)))).*(461845907)).^(x4877)
      x4839 = ((((x4878.<<(13)).|((x4878.>>>(-13)))).*(5)).+(-430675100))
      val x4885 = x4838._4
      val x4887 = -862048943.*((x4885.hashCode()))
      val x4892 = x4839
      val x4893 = (((x4887.<<(15)).|((x4887.>>>(-15)))).*(461845907)).^(x4892)
      x4839 = ((((x4893.<<(13)).|((x4893.>>>(-13)))).*(5)).+(-430675100))
      val x4900 = x4839
      val x4901 = x4900.^(2)
      val x4904 = (x4901.^((x4901.>>>(16)))).*(-2048144789)
      val x4907 = (x4904.^((x4904.>>>(13)))).*(-1028477387)
      (x4907.^((x4907.>>>(16))))
    }
    override def cmp(x4911 : SEntry10_IIIIIITIDS , x4912 : SEntry10_IIIIIITIDS) = {
      val x4913 = x4911._1
      val x4914 = x4912._1
      (if(((((x4913.==(x4914)).&&({
        val x4916 = x4911._2
        val x4917 = x4912._2
        (x4916.==(x4917))
      })).&&({
        val x4920 = x4911._3
        val x4921 = x4912._3
        (x4920.==(x4921))
      })).&&({
        val x4924 = x4911._4
        val x4925 = x4912._4
        (x4924.==(x4925))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4697 : SEntry8_IIIITIIB) = {
      var x4698: Int = -889275714
      val x4699 = x4697._2
      val x4701 = -862048943.*((x4699.hashCode()))
      val x4706 = x4698
      val x4707 = (((x4701.<<(15)).|((x4701.>>>(-15)))).*(461845907)).^(x4706)
      x4698 = ((((x4707.<<(13)).|((x4707.>>>(-13)))).*(5)).+(-430675100))
      val x4714 = x4697._3
      val x4716 = -862048943.*((x4714.hashCode()))
      val x4721 = x4698
      val x4722 = (((x4716.<<(15)).|((x4716.>>>(-15)))).*(461845907)).^(x4721)
      x4698 = ((((x4722.<<(13)).|((x4722.>>>(-13)))).*(5)).+(-430675100))
      val x4729 = x4697._4
      val x4731 = -862048943.*((x4729.hashCode()))
      val x4736 = x4698
      val x4737 = (((x4731.<<(15)).|((x4731.>>>(-15)))).*(461845907)).^(x4736)
      x4698 = ((((x4737.<<(13)).|((x4737.>>>(-13)))).*(5)).+(-430675100))
      val x4744 = x4698
      val x4745 = x4744.^(2)
      val x4748 = (x4745.^((x4745.>>>(16)))).*(-2048144789)
      val x4751 = (x4748.^((x4748.>>>(13)))).*(-1028477387)
      (x4751.^((x4751.>>>(16))))
    }
    override def cmp(x4755 : SEntry8_IIIITIIB , x4756 : SEntry8_IIIITIIB) = {
      val x4757 = x4755._2
      val x4758 = x4756._2
      (if((((x4757.==(x4758)).&&({
        val x4760 = x4755._3
        val x4761 = x4756._3
        (x4760.==(x4761))
      })).&&({
        val x4764 = x4755._4
        val x4765 = x4756._4
        (x4764.==(x4765))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5011 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5012: Int = -889275714
      val x5013 = x5011._1
      val x5015 = -862048943.*((x5013.hashCode()))
      val x5020 = x5012
      val x5021 = (((x5015.<<(15)).|((x5015.>>>(-15)))).*(461845907)).^(x5020)
      x5012 = ((((x5021.<<(13)).|((x5021.>>>(-13)))).*(5)).+(-430675100))
      val x5028 = x5011._2
      val x5030 = -862048943.*((x5028.hashCode()))
      val x5035 = x5012
      val x5036 = (((x5030.<<(15)).|((x5030.>>>(-15)))).*(461845907)).^(x5035)
      x5012 = ((((x5036.<<(13)).|((x5036.>>>(-13)))).*(5)).+(-430675100))
      val x5043 = x5011._3
      val x5045 = -862048943.*((x5043.hashCode()))
      val x5050 = x5012
      val x5051 = (((x5045.<<(15)).|((x5045.>>>(-15)))).*(461845907)).^(x5050)
      x5012 = ((((x5051.<<(13)).|((x5051.>>>(-13)))).*(5)).+(-430675100))
      val x5058 = x5012
      val x5059 = x5058.^(2)
      val x5062 = (x5059.^((x5059.>>>(16)))).*(-2048144789)
      val x5065 = (x5062.^((x5062.>>>(13)))).*(-1028477387)
      (x5065.^((x5065.>>>(16))))
    }
    override def cmp(x5069 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5070 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5071 = x5069._1
      val x5072 = x5070._1
      (if((((x5071.==(x5072)).&&({
        val x5074 = x5069._2
        val x5075 = x5070._2
        (x5074.==(x5075))
      })).&&({
        val x5078 = x5069._3
        val x5079 = x5070._3
        (x5078.==(x5079))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4931 : SEntry10_IIIIIITIDS) = {
      var x4932: Int = -889275714
      val x4933 = x4931._1
      val x4935 = -862048943.*((x4933.hashCode()))
      val x4940 = x4932
      val x4941 = (((x4935.<<(15)).|((x4935.>>>(-15)))).*(461845907)).^(x4940)
      x4932 = ((((x4941.<<(13)).|((x4941.>>>(-13)))).*(5)).+(-430675100))
      val x4948 = x4931._2
      val x4950 = -862048943.*((x4948.hashCode()))
      val x4955 = x4932
      val x4956 = (((x4950.<<(15)).|((x4950.>>>(-15)))).*(461845907)).^(x4955)
      x4932 = ((((x4956.<<(13)).|((x4956.>>>(-13)))).*(5)).+(-430675100))
      val x4963 = x4931._3
      val x4965 = -862048943.*((x4963.hashCode()))
      val x4970 = x4932
      val x4971 = (((x4965.<<(15)).|((x4965.>>>(-15)))).*(461845907)).^(x4970)
      x4932 = ((((x4971.<<(13)).|((x4971.>>>(-13)))).*(5)).+(-430675100))
      val x4978 = x4932
      val x4979 = x4978.^(2)
      val x4982 = (x4979.^((x4979.>>>(16)))).*(-2048144789)
      val x4985 = (x4982.^((x4982.>>>(13)))).*(-1028477387)
      (x4985.^((x4985.>>>(16))))
    }
    override def cmp(x4989 : SEntry10_IIIIIITIDS , x4990 : SEntry10_IIIIIITIDS) = {
      val x4991 = x4989._1
      val x4992 = x4990._1
      (if((((x4991.==(x4992)).&&({
        val x4994 = x4989._2
        val x4995 = x4990._2
        (x4994.==(x4995))
      })).&&({
        val x4998 = x4989._3
        val x4999 = x4990._3
        (x4998.==(x4999))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4332 : SEntry3_III) = {
      var x4333: Int = -889275714
      val x4334 = x4332._2
      val x4336 = -862048943.*((x4334.hashCode()))
      val x4341 = x4333
      val x4342 = (((x4336.<<(15)).|((x4336.>>>(-15)))).*(461845907)).^(x4341)
      x4333 = ((((x4342.<<(13)).|((x4342.>>>(-13)))).*(5)).+(-430675100))
      val x4349 = x4332._3
      val x4351 = -862048943.*((x4349.hashCode()))
      val x4356 = x4333
      val x4357 = (((x4351.<<(15)).|((x4351.>>>(-15)))).*(461845907)).^(x4356)
      x4333 = ((((x4357.<<(13)).|((x4357.>>>(-13)))).*(5)).+(-430675100))
      val x4364 = x4333
      val x4365 = x4364.^(2)
      val x4368 = (x4365.^((x4365.>>>(16)))).*(-2048144789)
      val x4371 = (x4368.^((x4368.>>>(13)))).*(-1028477387)
      (x4371.^((x4371.>>>(16))))
    }
    override def cmp(x4375 : SEntry3_III , x4376 : SEntry3_III) = {
      val x4377 = x4375._2
      val x4378 = x4376._2
      (if(((x4377.==(x4378)).&&({
        val x4380 = x4375._3
        val x4381 = x4376._3
        (x4380.==(x4381))
      }))) 0 else 1)
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx12 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5164 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5165: Int = -889275714
      val x5166 = x5164._1
      val x5168 = -862048943.*((x5166.hashCode()))
      val x5173 = x5165
      val x5174 = (((x5168.<<(15)).|((x5168.>>>(-15)))).*(461845907)).^(x5173)
      x5165 = ((((x5174.<<(13)).|((x5174.>>>(-13)))).*(5)).+(-430675100))
      val x5181 = x5164._2
      val x5183 = -862048943.*((x5181.hashCode()))
      val x5188 = x5165
      val x5189 = (((x5183.<<(15)).|((x5183.>>>(-15)))).*(461845907)).^(x5188)
      x5165 = ((((x5189.<<(13)).|((x5189.>>>(-13)))).*(5)).+(-430675100))
      val x5196 = x5165
      val x5197 = x5196.^(2)
      val x5200 = (x5197.^((x5197.>>>(16)))).*(-2048144789)
      val x5203 = (x5200.^((x5200.>>>(13)))).*(-1028477387)
      (x5203.^((x5203.>>>(16))))
    }
    override def cmp(x5207 : SEntry17_IIISSSSSSSSSSIIIS , x5208 : SEntry17_IIISSSSSSSSSSIIIS) = {
      val x5209 = x5207._1
      val x5210 = x5208._1
      (if(((x5209.==(x5210)).&&({
        val x5212 = x5207._2
        val x5213 = x5208._2
        (x5212.==(x5213))
      }))) 0 else 1)
    }
  }
   object SEntry5_IISDS_Idx1 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4511 : SEntry5_IISDS) = {
      var x4512: Int = -889275714
      val x4513 = x4511._1
      val x4515 = -862048943.*((x4513.hashCode()))
      val x4520 = x4512
      val x4521 = (((x4515.<<(15)).|((x4515.>>>(-15)))).*(461845907)).^(x4520)
      x4512 = ((((x4521.<<(13)).|((x4521.>>>(-13)))).*(5)).+(-430675100))
      val x4528 = x4512
      val x4529 = x4528.^(2)
      val x4532 = (x4529.^((x4529.>>>(16)))).*(-2048144789)
      val x4535 = (x4532.^((x4532.>>>(13)))).*(-1028477387)
      (x4535.^((x4535.>>>(16))))
    }
    override def cmp(x4539 : SEntry5_IISDS , x4540 : SEntry5_IISDS) = {
      val x4541 = x4539._1
      val x4542 = x4540._1
      (if((x4541.==(x4542))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4393 : SEntry8_IIIIITDS) = {
      var x4394: Int = -889275714
      val x4395 = x4394
      val x4396 = x4395.^(2)
      val x4399 = (x4396.^((x4396.>>>(16)))).*(-2048144789)
      val x4402 = (x4399.^((x4399.>>>(13)))).*(-1028477387)
      (x4402.^((x4402.>>>(16))))
    }
    override def cmp(x4406 : SEntry8_IIIIITDS , x4407 : SEntry8_IIIIITDS) = {
      val x4408 = x4406._1
      val x4409 = x4407._1
      (if((((((((((x4408.==(-1)).||({
        (x4409.==(-1))
      })).||({
        (x4408.==(x4409))
      })).&&({
        val x4415 = x4406._2
        val x4416 = x4407._2
        (((x4415.==(-1)).||({
          (x4416.==(-1))
        })).||({
          (x4415.==(x4416))
        }))
      })).&&({
        val x4423 = x4406._3
        val x4424 = x4407._3
        (((x4423.==(-1)).||({
          (x4424.==(-1))
        })).||({
          (x4423.==(x4424))
        }))
      })).&&({
        val x4431 = x4406._4
        val x4432 = x4407._4
        (((x4431.==(-1)).||({
          (x4432.==(-1))
        })).||({
          (x4431.==(x4432))
        }))
      })).&&({
        val x4439 = x4406._5
        val x4440 = x4407._5
        (((x4439.==(-1)).||({
          (x4440.==(-1))
        })).||({
          (x4439.==(x4440))
        }))
      })).&&({
        val x4447 = x4406._6
        val x4448 = x4407._6
        (((x4447.==(null)).||({
          (x4448.==(null))
        })).||({
          (x4447.==(x4448))
        }))
      })).&&({
        val x4455 = x4406._7
        val x4456 = x4407._7
        (((x4455.==(-1.0)).||({
          (x4456.==(-1.0))
        })).||({
          (x4455.==(x4456))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry11_IISSSSSSDDI_Idx12 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4778 : SEntry11_IISSSSSSDDI) = {
      var x4779: Int = -889275714
      val x4780 = x4778._1
      val x4782 = -862048943.*((x4780.hashCode()))
      val x4787 = x4779
      val x4788 = (((x4782.<<(15)).|((x4782.>>>(-15)))).*(461845907)).^(x4787)
      x4779 = ((((x4788.<<(13)).|((x4788.>>>(-13)))).*(5)).+(-430675100))
      val x4795 = x4778._2
      val x4797 = -862048943.*((x4795.hashCode()))
      val x4802 = x4779
      val x4803 = (((x4797.<<(15)).|((x4797.>>>(-15)))).*(461845907)).^(x4802)
      x4779 = ((((x4803.<<(13)).|((x4803.>>>(-13)))).*(5)).+(-430675100))
      val x4810 = x4779
      val x4811 = x4810.^(2)
      val x4814 = (x4811.^((x4811.>>>(16)))).*(-2048144789)
      val x4817 = (x4814.^((x4814.>>>(13)))).*(-1028477387)
      (x4817.^((x4817.>>>(16))))
    }
    override def cmp(x4821 : SEntry11_IISSSSSSDDI , x4822 : SEntry11_IISSSSSSDDI) = {
      val x4823 = x4821._1
      val x4824 = x4822._1
      (if(((x4823.==(x4824)).&&({
        val x4826 = x4821._2
        val x4827 = x4822._2
        (x4826.==(x4827))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5085 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5086: Int = -889275714
      val x5087 = x5085._2
      val x5089 = -862048943.*((x5087.hashCode()))
      val x5094 = x5086
      val x5095 = (((x5089.<<(15)).|((x5089.>>>(-15)))).*(461845907)).^(x5094)
      x5086 = ((((x5095.<<(13)).|((x5095.>>>(-13)))).*(5)).+(-430675100))
      val x5102 = x5085._3
      val x5104 = -862048943.*((x5102.hashCode()))
      val x5109 = x5086
      val x5110 = (((x5104.<<(15)).|((x5104.>>>(-15)))).*(461845907)).^(x5109)
      x5086 = ((((x5110.<<(13)).|((x5110.>>>(-13)))).*(5)).+(-430675100))
      val x5117 = x5085._6
      val x5119 = -862048943.*((x5117.hashCode()))
      val x5124 = x5086
      val x5125 = (((x5119.<<(15)).|((x5119.>>>(-15)))).*(461845907)).^(x5124)
      x5086 = ((((x5125.<<(13)).|((x5125.>>>(-13)))).*(5)).+(-430675100))
      val x5132 = x5086
      val x5133 = x5132.^(2)
      val x5136 = (x5133.^((x5133.>>>(16)))).*(-2048144789)
      val x5139 = (x5136.^((x5136.>>>(13)))).*(-1028477387)
      (x5139.^((x5139.>>>(16))))
    }
    override def cmp(x5143 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5144 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5145 = x5143._2
      val x5146 = x5144._2
      (if((((x5145.==(x5146)).&&({
        val x5148 = x5143._3
        val x5149 = x5144._3
        (x5148.==(x5149))
      })).&&({
        val x5152 = x5143._6
        val x5153 = x5144._6
        (x5152.==(x5153))
      }))) 0 else 1)
    }
  }
   object SEntry9_ISSSSSSDD_Idx1 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4471 : SEntry9_ISSSSSSDD) = {
      var x4472: Int = -889275714
      val x4473 = x4471._1
      val x4475 = -862048943.*((x4473.hashCode()))
      val x4480 = x4472
      val x4481 = (((x4475.<<(15)).|((x4475.>>>(-15)))).*(461845907)).^(x4480)
      x4472 = ((((x4481.<<(13)).|((x4481.>>>(-13)))).*(5)).+(-430675100))
      val x4488 = x4472
      val x4489 = x4488.^(2)
      val x4492 = (x4489.^((x4489.>>>(16)))).*(-2048144789)
      val x4495 = (x4492.^((x4492.>>>(13)))).*(-1028477387)
      (x4495.^((x4495.>>>(16))))
    }
    override def cmp(x4499 : SEntry9_ISSSSSSDD , x4500 : SEntry9_ISSSSSSDD) = {
      val x4501 = x4499._1
      val x4502 = x4500._1
      (if((x4501.==(x4502))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4555 : SEntry8_IIIITIIB) = {
      var x4556: Int = -889275714
      val x4557 = x4555._1
      val x4559 = -862048943.*((x4557.hashCode()))
      val x4564 = x4556
      val x4565 = (((x4559.<<(15)).|((x4559.>>>(-15)))).*(461845907)).^(x4564)
      x4556 = ((((x4565.<<(13)).|((x4565.>>>(-13)))).*(5)).+(-430675100))
      val x4572 = x4555._2
      val x4574 = -862048943.*((x4572.hashCode()))
      val x4579 = x4556
      val x4580 = (((x4574.<<(15)).|((x4574.>>>(-15)))).*(461845907)).^(x4579)
      x4556 = ((((x4580.<<(13)).|((x4580.>>>(-13)))).*(5)).+(-430675100))
      val x4587 = x4555._3
      val x4589 = -862048943.*((x4587.hashCode()))
      val x4594 = x4556
      val x4595 = (((x4589.<<(15)).|((x4589.>>>(-15)))).*(461845907)).^(x4594)
      x4556 = ((((x4595.<<(13)).|((x4595.>>>(-13)))).*(5)).+(-430675100))
      val x4602 = x4556
      val x4603 = x4602.^(2)
      val x4606 = (x4603.^((x4603.>>>(16)))).*(-2048144789)
      val x4609 = (x4606.^((x4606.>>>(13)))).*(-1028477387)
      (x4609.^((x4609.>>>(16))))
    }
    override def cmp(x4613 : SEntry8_IIIITIIB , x4614 : SEntry8_IIIITIIB) = {
      val x4615 = x4613._1
      val x4616 = x4614._1
      (if((((x4615.==(x4616)).&&({
        val x4618 = x4613._2
        val x4619 = x4614._2
        (x4618.==(x4619))
      })).&&({
        val x4622 = x4613._3
        val x4623 = x4614._3
        (x4622.==(x4623))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4279 : SEntry3_III) = {
      var x4280: Int = -889275714
      val x4281 = x4279._2
      val x4283 = -862048943.*((x4281.hashCode()))
      val x4288 = x4280
      val x4289 = (((x4283.<<(15)).|((x4283.>>>(-15)))).*(461845907)).^(x4288)
      x4280 = ((((x4289.<<(13)).|((x4289.>>>(-13)))).*(5)).+(-430675100))
      val x4296 = x4279._3
      val x4298 = -862048943.*((x4296.hashCode()))
      val x4303 = x4280
      val x4304 = (((x4298.<<(15)).|((x4298.>>>(-15)))).*(461845907)).^(x4303)
      x4280 = ((((x4304.<<(13)).|((x4304.>>>(-13)))).*(5)).+(-430675100))
      val x4311 = x4280
      val x4312 = x4311.^(2)
      val x4315 = (x4312.^((x4312.>>>(16)))).*(-2048144789)
      val x4318 = (x4315.^((x4315.>>>(13)))).*(-1028477387)
      (x4318.^((x4318.>>>(16))))
    }
    override def cmp(x4322 : SEntry3_III , x4323 : SEntry3_III) = {
      val x4324 = x914.apply(x4322)
      val x4325 = x914.apply(x4323)
      val x4328 = if((x4324.>(x4325))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4324.==(x4325))) 0 else x4328)
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4629 : SEntry8_IIIITIIB) = {
      var x4630: Int = -889275714
      val x4631 = x4629._2
      val x4633 = -862048943.*((x4631.hashCode()))
      val x4638 = x4630
      val x4639 = (((x4633.<<(15)).|((x4633.>>>(-15)))).*(461845907)).^(x4638)
      x4630 = ((((x4639.<<(13)).|((x4639.>>>(-13)))).*(5)).+(-430675100))
      val x4646 = x4629._3
      val x4648 = -862048943.*((x4646.hashCode()))
      val x4653 = x4630
      val x4654 = (((x4648.<<(15)).|((x4648.>>>(-15)))).*(461845907)).^(x4653)
      x4630 = ((((x4654.<<(13)).|((x4654.>>>(-13)))).*(5)).+(-430675100))
      val x4661 = x4629._4
      val x4663 = -862048943.*((x4661.hashCode()))
      val x4668 = x4630
      val x4669 = (((x4663.<<(15)).|((x4663.>>>(-15)))).*(461845907)).^(x4668)
      x4630 = ((((x4669.<<(13)).|((x4669.>>>(-13)))).*(5)).+(-430675100))
      val x4676 = x4630
      val x4677 = x4676.^(2)
      val x4680 = (x4677.^((x4677.>>>(16)))).*(-2048144789)
      val x4683 = (x4680.^((x4680.>>>(13)))).*(-1028477387)
      (x4683.^((x4683.>>>(16))))
    }
    override def cmp(x4687 : SEntry8_IIIITIIB , x4688 : SEntry8_IIIITIIB) = {
      val x4689 = x936.apply(x4687)
      val x4690 = x936.apply(x4688)
      val x4693 = if((x4689.>(x4690))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4689.==(x4690))) 0 else x4693)
    }
  }
  val x8913 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8598 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8081 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x8889 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8090 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8094 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8368 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8883 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8886 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8494 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8583 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8863 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  val x8070 = SEntry3_III(-1, -1, -1)
  val x8616 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8476 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8380 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8413 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8588 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  class DeliveryTx(x4389: Store[SEntry3_III], x4468: Store[SEntry8_IIIIITDS], x4509: Store[SEntry9_ISSSSSSDD], x4549: Store[SEntry5_IISDS], x4773: Store[SEntry8_IIIITIIB], x4835: Store[SEntry11_IISSSSSSDDI], x5007: Store[SEntry10_IIIIIITIDS], x5161: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5221: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x8070._2_=(x22)
        x8070._3_=(x12)
        val x13305 = x920.get(x8070)
        if((x13305.!=(null))) 
        {
          val x8075 = x13305._1
          val x29 = x15
          x14.update((x29.-(1)), x8075)
          x920.delete(x13305)
          val x33 = x15
          x8081._1_=(x8075)
          x8081._2_=(x33)
          x8081._3_=(x12)
          val x13318 = x942.get(x8081)
          val x8084 = x13318._4
          x13318._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x8090._1_=(x8075)
          x8090._2_=(x41)
          x8090._3_=(x12)
          x955.slice(x8090, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x8192 = x44._9
              x40 = (x46.+(x8192))
              ()
            }
          }))
          val x53 = x15
          x8094._1_=(x8084)
          x8094._2_=(x53)
          x8094._3_=(x12)
          val x13339 = x960.get(x8094)
          val x56 = x40
          x13339._17 +=(x56)
          x13339._20 +=(1)
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
  class StockLevelTx(x4389: Store[SEntry3_III], x4468: Store[SEntry8_IIIIITDS], x4509: Store[SEntry9_ISSSSSSDD], x4549: Store[SEntry5_IISDS], x4773: Store[SEntry8_IIIITIIB], x4835: Store[SEntry11_IISSSSSSDDI], x5007: Store[SEntry10_IIIIIITIDS], x5161: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5221: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) =     {
      x8368._1_=(x126)
      x8368._2_=(x125)
      val x13514 = x949.get(x8368)
      val x8371 = x13514._11
      var x133: Int = (x8371.-(20))
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        (x135.<(x8371))
      })
      {
        val x137 = x133
        x8380._1_=(x137)
        x8380._2_=(x126)
        x8380._3_=(x125)
        x955.slice(x8380, ({ x140: SEntry10_IIIIIITIDS => {
            val x8412 = x140._5
            x8413._1_=(x8412)
            x8413._2_=(x125)
            val x13532 = x964.get(x8413)
            val x8415 = x13532._3
            if((x8415.<(x127))) 
            {
              val x146 = x134.+=(x8412)
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
  class OrderStatusTx(x4389: Store[SEntry3_III], x4468: Store[SEntry8_IIIIITDS], x4509: Store[SEntry9_ISSSSSSDD], x4549: Store[SEntry5_IISDS], x4773: Store[SEntry8_IIIITIIB], x4835: Store[SEntry11_IISSSSSSDDI], x5007: Store[SEntry10_IIIIIITIDS], x5161: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5221: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) =     {
      var x8471: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x170.>(0))) 
      {
        val x8474 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8476._2_=(x169)
        x8476._3_=(x168)
        x8476._6_=(x172)
        x961.slice(x8476, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8474.append(x178)
            ()
          }
        }))
        val x182 = x8474.size
        var x184: Int = (x182./(2))
        val x185 = x8474.size
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
        
        val x199 = x8474.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8526 = x192._4
            val x8527 = x193._4
            val x196 = x8526.compareToIgnoreCase(x8527)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x201 = x199.apply(x200)
        x8471 = x201
        ()
      }
      else
      {
        x8494._1_=(x171)
        x8494._2_=(x169)
        x8494._3_=(x168)
        val x13630 = x960.get(x8494)
        x8471 = x13630
        ()
      }
      
      val x208 = x8471
      val x8499 = x208._3
      val x215 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x169, x168, x8499)
      var x218: Int = 0
      1
    }
  }
  class PaymentTx(x4389: Store[SEntry3_III], x4468: Store[SEntry8_IIIIITDS], x4509: Store[SEntry9_ISSSSSSDD], x4549: Store[SEntry5_IISDS], x4773: Store[SEntry8_IIIITIIB], x4835: Store[SEntry11_IISSSSSSDDI], x5007: Store[SEntry10_IIIIIITIDS], x5161: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5221: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) =     {
      x8583._1_=(x222)
      val x13683 = x931.get(x8583)
      x13683._9 +=(x229)
      x8588._1_=(x223)
      x8588._2_=(x222)
      val x13688 = x949.get(x8588)
      x13688._10 +=(x229)
      var x8593: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x224.>(0))) 
      {
        val x8596 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8598._2_=(x226)
        x8598._3_=(x225)
        x8598._6_=(x228)
        x961.slice(x8598, ({ x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8596.append(x245)
            ()
          }
        }))
        val x249 = x8596.size
        var x251: Int = (x249./(2))
        val x252 = x8596.size
        if(((x252.%(2)).==(0))) 
        {
          val x255 = x251
          x251 = (x255.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x266 = x8596.sortWith(({ (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8699 = x259._4
            val x8700 = x260._4
            val x263 = x8699.compareToIgnoreCase(x8700)
            (x263.<(0))
          }
        }))
        val x267 = x251
        val x268 = x266.apply(x267)
        x8593 = x268
        ()
      }
      else
      {
        x8616._1_=(x227)
        x8616._2_=(x226)
        x8616._3_=(x225)
        val x13727 = x960.get(x8616)
        x8593 = x13727
        ()
      }
      
      val x275 = x8593
      val x8621 = x275._21
      var x277: String = x8621
      val x278 = x8593
      val x8624 = x278._14
      val x280 = x8624.contains("BC")
      if(x280) 
      {
        val x281 = x8593
        val x8628 = x281._1
        val x283 = x277
        val x285 = "%d %d %d %d %d $%f %s | %s".format(x8628,x226,x225,x223,x222,x229,x220,x283)
        x277 = x285
        val x287 = x277
        val x288 = x287.length
        if((x288.>(500))) 
        {
          val x290 = x277
          val x291 = x290.substring(0, 500)
          x277 = x291
          ()
        }
        else
        {
          ()
        }
        
        val x294 = x8593
        x294._17 +=(x229)
        val x296 = x8593
        val x297 = x277
        x296._21_=(x297)
        ()
      }
      else
      {
        val x299 = x8593
        x299._17 +=(x229)
        ()
      }
      
      val x302 = x8593
      x961.update(x302)
      x960.update(x302)
      val x8649 = x13683._2
      val x8650 = x13688._3
      val x306 = x8649.length
      val x309 = if((x306.>(10))) 
      {
        val x308 = x8649.substring(0, 10)
        x308
      }
      else
      {
        x8649
      }
      
      val x310 = x309.+("    ")
      val x311 = x8650.length
      val x314 = if((x311.>(10))) 
      {
        val x313 = x8650.substring(0, 10)
        x313
      }
      else
      {
        x8650
      }
      
      val x315 = x310.+(x314)
      val x316 = x8593
      val x8662 = x316._1
      x4468.insert((SEntry8_IIIIITDS(x8662, x226, x225, x223, x222, x220, x229, x315)))
      1
    }
  }
  class NewOrderTx(x4389: Store[SEntry3_III], x4468: Store[SEntry8_IIIIITDS], x4509: Store[SEntry9_ISSSSSSDD], x4549: Store[SEntry5_IISDS], x4773: Store[SEntry8_IIIITIIB], x4835: Store[SEntry11_IISSSSSSDDI], x5007: Store[SEntry10_IIIIIITIDS], x5161: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5221: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x321: Boolean, x322: Date, x323: Int, x324: Int, x325: Int, x326: Int, x327: Int, x328: Int, x329: Array[Int], x330: Array[Int], x331: Array[Int], x332: Array[Double], x333: Array[String], x334: Array[Int], x335: Array[String], x336: Array[Double]) =     {
      if(x321) 
      {
        val x338 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x324,x325,x326)
        println(x338)
        ()
      }
      else
      {
        ()
      }
      
      var x341: Int = 0
      var x342: Boolean = false
      val x343 = new Array[String](x327)
      var x344: Boolean = true
      while({
        val x345 = x341
        ((x345.<(x327)).&&({
          val x347 = x344
          x347
        }))
      })
      {
        val x349 = x341
        val x350 = x329.apply(x349)
        x8863._1_=(x350)
        val x13888 = x934.get(x8863)
        if((x13888.==(null))) 
        {
          x344 = false
          ()
        }
        else
        {
          val x356 = x341
          val x8870 = x13888._3
          x333.update(x356, x8870)
          val x359 = x341
          val x8873 = x13888._4
          x332.update(x359, x8873)
          val x362 = x341
          val x8876 = x13888._5
          x343.update(x362, x8876)
          ()
        }
        
        val x366 = x341
        x341 = (x366.+(1))
        ()
      }
      val x370 = x344
      if(x370) 
      {
        x8883._1_=(x326)
        x8883._2_=(x325)
        x8883._3_=(x324)
        val x13910 = x960.get(x8883)
        x8886._1_=(x324)
        val x13913 = x931.get(x8886)
        x8889._1_=(x325)
        x8889._2_=(x324)
        val x13917 = x949.get(x8889)
        val x8892 = x13917._11
        x13917._11 +=(1)
        x4773.insert((SEntry8_IIIITIIB(x8892, x325, x324, x326, x322, -1, x327, (x328.>(0)))))
        x4389.insert((SEntry3_III(x8892, x325, x324)))
        var x390: Double = 0.0
        x341 = 0
        while({
          val x392 = x341
          (x392.<(x327))
        })
        {
          val x394 = x341
          val x395 = x330.apply(x394)
          val x396 = x341
          val x397 = x329.apply(x396)
          val x398 = x341
          val x399 = x331.apply(x398)
          x8913._1_=(x397)
          x8913._2_=(x395)
          val x13940 = x964.get(x8913)
          val x429 = if((x325.==(1))) 
          {
            val x8917 = x13940._4
            x8917
          }
          else
          {
            val x428 = if((x325.==(2))) 
            {
              val x8920 = x13940._5
              x8920
            }
            else
            {
              val x427 = if((x325.==(3))) 
              {
                val x8923 = x13940._6
                x8923
              }
              else
              {
                val x426 = if((x325.==(4))) 
                {
                  val x8926 = x13940._7
                  x8926
                }
                else
                {
                  val x425 = if((x325.==(5))) 
                  {
                    val x8929 = x13940._8
                    x8929
                  }
                  else
                  {
                    val x424 = if((x325.==(6))) 
                    {
                      val x8932 = x13940._9
                      x8932
                    }
                    else
                    {
                      val x423 = if((x325.==(7))) 
                      {
                        val x8935 = x13940._10
                        x8935
                      }
                      else
                      {
                        val x422 = if((x325.==(8))) 
                        {
                          val x8938 = x13940._11
                          x8938
                        }
                        else
                        {
                          val x421 = if((x325.==(9))) 
                          {
                            val x8941 = x13940._12
                            x8941
                          }
                          else
                          {
                            val x8942 = x13940._13
                            x8942
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
          
          val x8943 = x13940._3
          val x431 = x341
          x334.update(x431, x8943)
          val x8946 = x13910._14
          val x434 = x8946.contains("original")
          if((x434.&&({
            val x8949 = x13940._17
            val x436 = x8949.contains("original")
            x436
          }))) 
          {
            val x438 = x341
            x335.update(x438, "B")
            ()
          }
          else
          {
            val x440 = x341
            x335.update(x440, "G")
            ()
          }
          
          x13940._3_=((x8943.-(x399)))
          if((x8943.<=(x399))) 
          {
            x13940._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x448: Int = 0
          if((x395.!=(x324))) 
          {
            x448 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8966 = x13910._16
          val x8967 = x13913._8
          val x8968 = x13917._9
          val x456 = x341
          val x457 = x332.apply(x456)
          val x464 = (((x399.toDouble).*(x457)).*(((1.0.+(x8967)).+(x8968)))).*((1.0.-(x8966)))
          val x465 = x341
          x336.update(x465, x464)
          val x467 = x390
          x390 = (x467.+(x464))
          val x470 = x341
          x5007.insert((SEntry10_IIIIIITIDS(x8892, x325, x324, (x470.+(1)), x397, x395, null, x399, x464, x429)))
          val x475 = x341
          x341 = (x475.+(1))
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
