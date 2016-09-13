
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
  val x915 = { x18: SEntry3_III => {
      val x6047 = x18._1
      x6047
    }
  }
  val x4510 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x4511 = new Store[SEntry3_III](3, x4510)
  val x921 = x4511.index(0, IHash, true, -1)
  val x922 = x4511.index(1, ISliceHeapMin, false, 2)
  val x923 = x4511.index(2, INone, false, -1)
  val x4590 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4591 = new Store[SEntry8_IIIIITDS](1, x4590)
  val x928 = x4591.index(0, IList, false, -1)
  val x4609 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x4610 = new Store[SEntry9_ISSSSSSDD](1, x4609)
  val x933 = x4610.index(0, IDirect, true, 1)
  val x4628 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x4629 = new Store[SEntry5_IISDS](1, x4628)
  val x938 = x4629.index(0, IDirect, true, 100000)
  val x939 = { x210: SEntry8_IIIITIIB => {
      val x6355 = x210._1
      x6355
    }
  }
  val x4852 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4853 = new Store[SEntry8_IIIITIIB](3, x4852)
  val x945 = x4853.index(0, IHash, true, -1)
  val x946 = x4853.index(1, ISliceHeapMax, false, 2)
  val x947 = x4853.index(2, INone, false, -1)
  val x4879 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4880 = new Store[SEntry11_IISSSSSSDDI](1, x4879)
  val x952 = x4880.index(0, IDirect, true, 10)
  val x5051 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x5052 = new Store[SEntry10_IIIIIITIDS](2, x5051)
  val x957 = x5052.index(0, IHash, true, -1)
  val x958 = x5052.index(1, IHash, false, -1)
  val x5157 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x5158 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x5157)
  val x964 = x5158.index(0, IDirect, true, 30000)
  val x965 = x5158.index(1, IHash, false, -1)
  val x5183 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x5184 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x5183)
  val x970 = x5184.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x4511
  val historyTbl = x4591
  val warehouseTbl = x4610
  val itemTbl = x4629
  val orderTbl = x4853
  val districtTbl = x4880
  val orderLineTbl = x5052
  val customerTbl = x5158
  val stockTbl = x5184
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4883 : SEntry10_IIIIIITIDS) = {
      var x4884: Int = -889275714
      val x4885 = x4883._1
      val x4887 = -862048943.*((x4885.hashCode()))
      val x4892 = x4884
      val x4893 = (((x4887.<<(15)).|((x4887.>>>(-15)))).*(461845907)).^(x4892)
      x4884 = ((((x4893.<<(13)).|((x4893.>>>(-13)))).*(5)).+(-430675100))
      val x4900 = x4883._2
      val x4902 = -862048943.*((x4900.hashCode()))
      val x4907 = x4884
      val x4908 = (((x4902.<<(15)).|((x4902.>>>(-15)))).*(461845907)).^(x4907)
      x4884 = ((((x4908.<<(13)).|((x4908.>>>(-13)))).*(5)).+(-430675100))
      val x4915 = x4883._3
      val x4917 = -862048943.*((x4915.hashCode()))
      val x4922 = x4884
      val x4923 = (((x4917.<<(15)).|((x4917.>>>(-15)))).*(461845907)).^(x4922)
      x4884 = ((((x4923.<<(13)).|((x4923.>>>(-13)))).*(5)).+(-430675100))
      val x4930 = x4883._4
      val x4932 = -862048943.*((x4930.hashCode()))
      val x4937 = x4884
      val x4938 = (((x4932.<<(15)).|((x4932.>>>(-15)))).*(461845907)).^(x4937)
      x4884 = ((((x4938.<<(13)).|((x4938.>>>(-13)))).*(5)).+(-430675100))
      val x4945 = x4884
      val x4946 = x4945.^(2)
      val x4949 = (x4946.^((x4946.>>>(16)))).*(-2048144789)
      val x4952 = (x4949.^((x4949.>>>(13)))).*(-1028477387)
      (x4952.^((x4952.>>>(16))))
    }
    override def cmp(x4956 : SEntry10_IIIIIITIDS , x4957 : SEntry10_IIIIIITIDS) = {
      val x4958 = x4956._1
      val x4959 = x4957._1
      (if(((((x4958.==(x4959)).&&({
        val x4961 = x4956._2
        val x4962 = x4957._2
        (x4961.==(x4962))
      })).&&({
        val x4965 = x4956._3
        val x4966 = x4957._3
        (x4965.==(x4966))
      })).&&({
        val x4969 = x4956._4
        val x4970 = x4957._4
        (x4969.==(x4970))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4777 : SEntry8_IIIITIIB) = {
      var x4778: Int = -889275714
      val x4779 = x4777._2
      val x4781 = -862048943.*((x4779.hashCode()))
      val x4786 = x4778
      val x4787 = (((x4781.<<(15)).|((x4781.>>>(-15)))).*(461845907)).^(x4786)
      x4778 = ((((x4787.<<(13)).|((x4787.>>>(-13)))).*(5)).+(-430675100))
      val x4794 = x4777._3
      val x4796 = -862048943.*((x4794.hashCode()))
      val x4801 = x4778
      val x4802 = (((x4796.<<(15)).|((x4796.>>>(-15)))).*(461845907)).^(x4801)
      x4778 = ((((x4802.<<(13)).|((x4802.>>>(-13)))).*(5)).+(-430675100))
      val x4809 = x4777._4
      val x4811 = -862048943.*((x4809.hashCode()))
      val x4816 = x4778
      val x4817 = (((x4811.<<(15)).|((x4811.>>>(-15)))).*(461845907)).^(x4816)
      x4778 = ((((x4817.<<(13)).|((x4817.>>>(-13)))).*(5)).+(-430675100))
      val x4824 = x4778
      val x4825 = x4824.^(2)
      val x4828 = (x4825.^((x4825.>>>(16)))).*(-2048144789)
      val x4831 = (x4828.^((x4828.>>>(13)))).*(-1028477387)
      (x4831.^((x4831.>>>(16))))
    }
    override def cmp(x4835 : SEntry8_IIIITIIB , x4836 : SEntry8_IIIITIIB) = {
      val x4837 = x4835._2
      val x4838 = x4836._2
      (if((((x4837.==(x4838)).&&({
        val x4840 = x4835._3
        val x4841 = x4836._3
        (x4840.==(x4841))
      })).&&({
        val x4844 = x4835._4
        val x4845 = x4836._4
        (x4844.==(x4845))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x4327 : SEntry3_III) = {
      var x4328: Int = -889275714
      val x4329 = x4327._1
      val x4331 = -862048943.*((x4329.hashCode()))
      val x4336 = x4328
      val x4337 = (((x4331.<<(15)).|((x4331.>>>(-15)))).*(461845907)).^(x4336)
      x4328 = ((((x4337.<<(13)).|((x4337.>>>(-13)))).*(5)).+(-430675100))
      val x4344 = x4327._2
      val x4346 = -862048943.*((x4344.hashCode()))
      val x4351 = x4328
      val x4352 = (((x4346.<<(15)).|((x4346.>>>(-15)))).*(461845907)).^(x4351)
      x4328 = ((((x4352.<<(13)).|((x4352.>>>(-13)))).*(5)).+(-430675100))
      val x4359 = x4327._3
      val x4361 = -862048943.*((x4359.hashCode()))
      val x4366 = x4328
      val x4367 = (((x4361.<<(15)).|((x4361.>>>(-15)))).*(461845907)).^(x4366)
      x4328 = ((((x4367.<<(13)).|((x4367.>>>(-13)))).*(5)).+(-430675100))
      val x4374 = x4328
      val x4375 = x4374.^(2)
      val x4378 = (x4375.^((x4375.>>>(16)))).*(-2048144789)
      val x4381 = (x4378.^((x4378.>>>(13)))).*(-1028477387)
      (x4381.^((x4381.>>>(16))))
    }
    override def cmp(x4385 : SEntry3_III , x4386 : SEntry3_III) = {
      val x4387 = x4385._1
      val x4388 = x4386._1
      (if((((x4387.==(x4388)).&&({
        val x4390 = x4385._2
        val x4391 = x4386._2
        (x4390.==(x4391))
      })).&&({
        val x4394 = x4385._3
        val x4395 = x4386._3
        (x4394.==(x4395))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4976 : SEntry10_IIIIIITIDS) = {
      var x4977: Int = -889275714
      val x4978 = x4976._1
      val x4980 = -862048943.*((x4978.hashCode()))
      val x4985 = x4977
      val x4986 = (((x4980.<<(15)).|((x4980.>>>(-15)))).*(461845907)).^(x4985)
      x4977 = ((((x4986.<<(13)).|((x4986.>>>(-13)))).*(5)).+(-430675100))
      val x4993 = x4976._2
      val x4995 = -862048943.*((x4993.hashCode()))
      val x5000 = x4977
      val x5001 = (((x4995.<<(15)).|((x4995.>>>(-15)))).*(461845907)).^(x5000)
      x4977 = ((((x5001.<<(13)).|((x5001.>>>(-13)))).*(5)).+(-430675100))
      val x5008 = x4976._3
      val x5010 = -862048943.*((x5008.hashCode()))
      val x5015 = x4977
      val x5016 = (((x5010.<<(15)).|((x5010.>>>(-15)))).*(461845907)).^(x5015)
      x4977 = ((((x5016.<<(13)).|((x5016.>>>(-13)))).*(5)).+(-430675100))
      val x5023 = x4977
      val x5024 = x5023.^(2)
      val x5027 = (x5024.^((x5024.>>>(16)))).*(-2048144789)
      val x5030 = (x5027.^((x5027.>>>(13)))).*(-1028477387)
      (x5030.^((x5030.>>>(16))))
    }
    override def cmp(x5034 : SEntry10_IIIIIITIDS , x5035 : SEntry10_IIIIIITIDS) = {
      val x5036 = x5034._1
      val x5037 = x5035._1
      (if((((x5036.==(x5037)).&&({
        val x5039 = x5034._2
        val x5040 = x5035._2
        (x5039.==(x5040))
      })).&&({
        val x5043 = x5034._3
        val x5044 = x5035._3
        (x5043.==(x5044))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4454 : SEntry3_III) = {
      var x4455: Int = -889275714
      val x4456 = x4454._2
      val x4458 = -862048943.*((x4456.hashCode()))
      val x4463 = x4455
      val x4464 = (((x4458.<<(15)).|((x4458.>>>(-15)))).*(461845907)).^(x4463)
      x4455 = ((((x4464.<<(13)).|((x4464.>>>(-13)))).*(5)).+(-430675100))
      val x4471 = x4454._3
      val x4473 = -862048943.*((x4471.hashCode()))
      val x4478 = x4455
      val x4479 = (((x4473.<<(15)).|((x4473.>>>(-15)))).*(461845907)).^(x4478)
      x4455 = ((((x4479.<<(13)).|((x4479.>>>(-13)))).*(5)).+(-430675100))
      val x4486 = x4455
      val x4487 = x4486.^(2)
      val x4490 = (x4487.^((x4487.>>>(16)))).*(-2048144789)
      val x4493 = (x4490.^((x4490.>>>(13)))).*(-1028477387)
      (x4493.^((x4493.>>>(16))))
    }
    override def cmp(x4497 : SEntry3_III , x4498 : SEntry3_III) = {
      val x4499 = x4497._2
      val x4500 = x4498._2
      (if(((x4499.==(x4500)).&&({
        val x4502 = x4497._3
        val x4503 = x4498._3
        (x4502.==(x4503))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4516 : SEntry8_IIIIITDS) = {
      var x4517: Int = -889275714
      val x4518 = x4517
      val x4519 = x4518.^(2)
      val x4522 = (x4519.^((x4519.>>>(16)))).*(-2048144789)
      val x4525 = (x4522.^((x4522.>>>(13)))).*(-1028477387)
      (x4525.^((x4525.>>>(16))))
    }
    override def cmp(x4529 : SEntry8_IIIIITDS , x4530 : SEntry8_IIIIITDS) = {
      val x4531 = x4529._1
      val x4532 = x4530._1
      (if((((((((((x4531.==(-1)).||({
        (x4532.==(-1))
      })).||({
        (x4531.==(x4532))
      })).&&({
        val x4538 = x4529._2
        val x4539 = x4530._2
        (((x4538.==(-1)).||({
          (x4539.==(-1))
        })).||({
          (x4538.==(x4539))
        }))
      })).&&({
        val x4546 = x4529._3
        val x4547 = x4530._3
        (((x4546.==(-1)).||({
          (x4547.==(-1))
        })).||({
          (x4546.==(x4547))
        }))
      })).&&({
        val x4554 = x4529._4
        val x4555 = x4530._4
        (((x4554.==(-1)).||({
          (x4555.==(-1))
        })).||({
          (x4554.==(x4555))
        }))
      })).&&({
        val x4562 = x4529._5
        val x4563 = x4530._5
        (((x4562.==(-1)).||({
          (x4563.==(-1))
        })).||({
          (x4562.==(x4563))
        }))
      })).&&({
        val x4570 = x4529._6
        val x4571 = x4530._6
        (((x4570.==(null)).||({
          (x4571.==(null))
        })).||({
          (x4570.==(x4571))
        }))
      })).&&({
        val x4578 = x4529._7
        val x4579 = x4530._7
        (((x4578.==(-1.0)).||({
          (x4579.==(-1.0))
        })).||({
          (x4578.==(x4579))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5082 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5083: Int = -889275714
      val x5084 = x5082._2
      val x5086 = -862048943.*((x5084.hashCode()))
      val x5091 = x5083
      val x5092 = (((x5086.<<(15)).|((x5086.>>>(-15)))).*(461845907)).^(x5091)
      x5083 = ((((x5092.<<(13)).|((x5092.>>>(-13)))).*(5)).+(-430675100))
      val x5099 = x5082._3
      val x5101 = -862048943.*((x5099.hashCode()))
      val x5106 = x5083
      val x5107 = (((x5101.<<(15)).|((x5101.>>>(-15)))).*(461845907)).^(x5106)
      x5083 = ((((x5107.<<(13)).|((x5107.>>>(-13)))).*(5)).+(-430675100))
      val x5114 = x5082._6
      val x5116 = -862048943.*((x5114.hashCode()))
      val x5121 = x5083
      val x5122 = (((x5116.<<(15)).|((x5116.>>>(-15)))).*(461845907)).^(x5121)
      x5083 = ((((x5122.<<(13)).|((x5122.>>>(-13)))).*(5)).+(-430675100))
      val x5129 = x5083
      val x5130 = x5129.^(2)
      val x5133 = (x5130.^((x5130.>>>(16)))).*(-2048144789)
      val x5136 = (x5133.^((x5133.>>>(13)))).*(-1028477387)
      (x5136.^((x5136.>>>(16))))
    }
    override def cmp(x5140 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5141 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5142 = x5140._2
      val x5143 = x5141._2
      (if((((x5142.==(x5143)).&&({
        val x5145 = x5140._3
        val x5146 = x5141._3
        (x5145.==(x5146))
      })).&&({
        val x5149 = x5140._6
        val x5150 = x5141._6
        (x5149.==(x5150))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4635 : SEntry8_IIIITIIB) = {
      var x4636: Int = -889275714
      val x4637 = x4635._1
      val x4639 = -862048943.*((x4637.hashCode()))
      val x4644 = x4636
      val x4645 = (((x4639.<<(15)).|((x4639.>>>(-15)))).*(461845907)).^(x4644)
      x4636 = ((((x4645.<<(13)).|((x4645.>>>(-13)))).*(5)).+(-430675100))
      val x4652 = x4635._2
      val x4654 = -862048943.*((x4652.hashCode()))
      val x4659 = x4636
      val x4660 = (((x4654.<<(15)).|((x4654.>>>(-15)))).*(461845907)).^(x4659)
      x4636 = ((((x4660.<<(13)).|((x4660.>>>(-13)))).*(5)).+(-430675100))
      val x4667 = x4635._3
      val x4669 = -862048943.*((x4667.hashCode()))
      val x4674 = x4636
      val x4675 = (((x4669.<<(15)).|((x4669.>>>(-15)))).*(461845907)).^(x4674)
      x4636 = ((((x4675.<<(13)).|((x4675.>>>(-13)))).*(5)).+(-430675100))
      val x4682 = x4636
      val x4683 = x4682.^(2)
      val x4686 = (x4683.^((x4683.>>>(16)))).*(-2048144789)
      val x4689 = (x4686.^((x4686.>>>(13)))).*(-1028477387)
      (x4689.^((x4689.>>>(16))))
    }
    override def cmp(x4693 : SEntry8_IIIITIIB , x4694 : SEntry8_IIIITIIB) = {
      val x4695 = x4693._1
      val x4696 = x4694._1
      (if((((x4695.==(x4696)).&&({
        val x4698 = x4693._2
        val x4699 = x4694._2
        (x4698.==(x4699))
      })).&&({
        val x4702 = x4693._3
        val x4703 = x4694._3
        (x4702.==(x4703))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4401 : SEntry3_III) = {
      var x4402: Int = -889275714
      val x4403 = x4401._2
      val x4405 = -862048943.*((x4403.hashCode()))
      val x4410 = x4402
      val x4411 = (((x4405.<<(15)).|((x4405.>>>(-15)))).*(461845907)).^(x4410)
      x4402 = ((((x4411.<<(13)).|((x4411.>>>(-13)))).*(5)).+(-430675100))
      val x4418 = x4401._3
      val x4420 = -862048943.*((x4418.hashCode()))
      val x4425 = x4402
      val x4426 = (((x4420.<<(15)).|((x4420.>>>(-15)))).*(461845907)).^(x4425)
      x4402 = ((((x4426.<<(13)).|((x4426.>>>(-13)))).*(5)).+(-430675100))
      val x4433 = x4402
      val x4434 = x4433.^(2)
      val x4437 = (x4434.^((x4434.>>>(16)))).*(-2048144789)
      val x4440 = (x4437.^((x4437.>>>(13)))).*(-1028477387)
      (x4440.^((x4440.>>>(16))))
    }
    override def cmp(x4444 : SEntry3_III , x4445 : SEntry3_III) = {
      val x4446 = x915.apply(x4444)
      val x4447 = x915.apply(x4445)
      val x4450 = if((x4446.>(x4447))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4446.==(x4447))) 0 else x4450)
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4709 : SEntry8_IIIITIIB) = {
      var x4710: Int = -889275714
      val x4711 = x4709._2
      val x4713 = -862048943.*((x4711.hashCode()))
      val x4718 = x4710
      val x4719 = (((x4713.<<(15)).|((x4713.>>>(-15)))).*(461845907)).^(x4718)
      x4710 = ((((x4719.<<(13)).|((x4719.>>>(-13)))).*(5)).+(-430675100))
      val x4726 = x4709._3
      val x4728 = -862048943.*((x4726.hashCode()))
      val x4733 = x4710
      val x4734 = (((x4728.<<(15)).|((x4728.>>>(-15)))).*(461845907)).^(x4733)
      x4710 = ((((x4734.<<(13)).|((x4734.>>>(-13)))).*(5)).+(-430675100))
      val x4741 = x4709._4
      val x4743 = -862048943.*((x4741.hashCode()))
      val x4748 = x4710
      val x4749 = (((x4743.<<(15)).|((x4743.>>>(-15)))).*(461845907)).^(x4748)
      x4710 = ((((x4749.<<(13)).|((x4749.>>>(-13)))).*(5)).+(-430675100))
      val x4756 = x4710
      val x4757 = x4756.^(2)
      val x4760 = (x4757.^((x4757.>>>(16)))).*(-2048144789)
      val x4763 = (x4760.^((x4760.>>>(13)))).*(-1028477387)
      (x4763.^((x4763.>>>(16))))
    }
    override def cmp(x4767 : SEntry8_IIIITIIB , x4768 : SEntry8_IIIITIIB) = {
      val x4769 = x939.apply(x4767)
      val x4770 = x939.apply(x4768)
      val x4773 = if((x4769.>(x4770))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4769.==(x4770))) 0 else x4773)
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4597 : SEntry9_ISSSSSSDD) = {
      var x4598: Int = 0
      val x4599 = x4597._1
      val x4601 = x4598
      x4598 = ((x4601.*(1)).+((x4599.-(1))))
      val x4605 = x4598
      x4605
    }
    override def cmp(x4594 : SEntry9_ISSSSSSDD , x4595 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4616 : SEntry5_IISDS) = {
      var x4617: Int = 0
      val x4618 = x4616._1
      val x4620 = x4617
      x4617 = ((x4620.*(100000)).+((x4618.-(1))))
      val x4624 = x4617
      x4624
    }
    override def cmp(x4613 : SEntry5_IISDS , x4614 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4861 : SEntry11_IISSSSSSDDI) = {
      var x4862: Int = 0
      val x4863 = x4861._1
      val x4865 = x4862
      x4862 = ((x4865.*(10)).+((x4863.-(1))))
      val x4869 = x4861._2
      val x4871 = x4862
      x4862 = ((x4871.*(1)).+((x4869.-(1))))
      val x4875 = x4862
      x4875
    }
    override def cmp(x4858 : SEntry11_IISSSSSSDDI , x4859 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5059 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5060: Int = 0
      val x5061 = x5059._1
      val x5063 = x5060
      x5060 = ((x5063.*(3000)).+((x5061.-(1))))
      val x5067 = x5059._2
      val x5069 = x5060
      x5060 = ((x5069.*(10)).+((x5067.-(1))))
      val x5073 = x5059._3
      val x5075 = x5060
      x5060 = ((x5075.*(1)).+((x5073.-(1))))
      val x5079 = x5060
      x5079
    }
    override def cmp(x5056 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5057 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5165 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5166: Int = 0
      val x5167 = x5165._1
      val x5169 = x5166
      x5166 = ((x5169.*(100000)).+((x5167.-(1))))
      val x5173 = x5165._2
      val x5175 = x5166
      x5166 = ((x5175.*(1)).+((x5173.-(1))))
      val x5179 = x5166
      x5179
    }
    override def cmp(x5162 : SEntry17_IIISSSSSSSSSSIIIS , x5163 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x8184 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8291 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8076 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8597 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7778 = SEntry3_III(-1, -1, -1)
  val x8296 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8121 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8621 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x7789 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x8571 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  val x8324 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7802 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8594 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8306 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8591 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7798 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8202 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8088 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  class DeliveryTx(x4511: Store[SEntry3_III], x4591: Store[SEntry8_IIIIITDS], x4610: Store[SEntry9_ISSSSSSDD], x4629: Store[SEntry5_IISDS], x4853: Store[SEntry8_IIIITIIB], x4880: Store[SEntry11_IISSSSSSDDI], x5052: Store[SEntry10_IIIIIITIDS], x5158: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5184: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x7778._2_=(x22)
        x7778._3_=(x12)
        val x12758 = x922.get(x7778)
        if((x12758.!=(null))) 
        {
          val x7783 = x12758._1
          val x29 = x15
          x14.update((x29.-(1)), x7783)
          x922.delete(x12758)
          x921.delete(x12758)
          val x33 = x15
          x7789._1_=(x7783)
          x7789._2_=(x33)
          x7789._3_=(x12)
          val x12772 = x945.get(x7789)
          val x7792 = x12772._4
          x12772._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x7798._1_=(x7783)
          x7798._2_=(x41)
          x7798._3_=(x12)
          x958.slice(x7798, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x7900 = x44._9
              x40 = (x46.+(x7900))
              ()
            }
          }))
          val x53 = x15
          x7802._1_=(x7792)
          x7802._2_=(x53)
          x7802._3_=(x12)
          val x12793 = x964.get(x7802)
          val x56 = x40
          x12793._17 +=(x56)
          x12793._20 +=(1)
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
  class StockLevelTx(x4511: Store[SEntry3_III], x4591: Store[SEntry8_IIIIITDS], x4610: Store[SEntry9_ISSSSSSDD], x4629: Store[SEntry5_IISDS], x4853: Store[SEntry8_IIIITIIB], x4880: Store[SEntry11_IISSSSSSDDI], x5052: Store[SEntry10_IIIIIITIDS], x5158: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5184: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) =     {
      x8076._1_=(x126)
      x8076._2_=(x125)
      val x12969 = x952.get(x8076)
      val x8079 = x12969._11
      var x133: Int = (x8079.-(20))
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        (x135.<(x8079))
      })
      {
        val x137 = x133
        x8088._1_=(x137)
        x8088._2_=(x126)
        x8088._3_=(x125)
        x958.slice(x8088, ({ x140: SEntry10_IIIIIITIDS => {
            val x8120 = x140._5
            x8121._1_=(x8120)
            x8121._2_=(x125)
            val x12987 = x970.get(x8121)
            val x8123 = x12987._3
            if((x8123.<(x127))) 
            {
              val x146 = x134.+=(x8120)
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
  class OrderStatusTx(x4511: Store[SEntry3_III], x4591: Store[SEntry8_IIIIITDS], x4610: Store[SEntry9_ISSSSSSDD], x4629: Store[SEntry5_IISDS], x4853: Store[SEntry8_IIIITIIB], x4880: Store[SEntry11_IISSSSSSDDI], x5052: Store[SEntry10_IIIIIITIDS], x5158: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5184: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) =     {
      var x8179: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x170.>(0))) 
      {
        val x8182 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8184._2_=(x169)
        x8184._3_=(x168)
        x8184._6_=(x172)
        x965.slice(x8184, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8182.append(x178)
            ()
          }
        }))
        val x182 = x8182.size
        var x184: Int = (x182./(2))
        val x185 = x8182.size
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
        
        val x199 = x8182.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8234 = x192._4
            val x8235 = x193._4
            val x196 = x8234.compareToIgnoreCase(x8235)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x201 = x199.apply(x200)
        x8179 = x201
        ()
      }
      else
      {
        x8202._1_=(x171)
        x8202._2_=(x169)
        x8202._3_=(x168)
        val x13085 = x964.get(x8202)
        x8179 = x13085
        ()
      }
      
      val x208 = x8179
      val x8207 = x208._3
      val x215 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x169, x168, x8207)
      var x218: Int = 0
      1
    }
  }
  class PaymentTx(x4511: Store[SEntry3_III], x4591: Store[SEntry8_IIIIITDS], x4610: Store[SEntry9_ISSSSSSDD], x4629: Store[SEntry5_IISDS], x4853: Store[SEntry8_IIIITIIB], x4880: Store[SEntry11_IISSSSSSDDI], x5052: Store[SEntry10_IIIIIITIDS], x5158: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5184: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) =     {
      x8291._1_=(x222)
      val x13138 = x933.get(x8291)
      x13138._9 +=(x229)
      x8296._1_=(x223)
      x8296._2_=(x222)
      val x13143 = x952.get(x8296)
      x13143._10 +=(x229)
      var x8301: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x224.>(0))) 
      {
        val x8304 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8306._2_=(x226)
        x8306._3_=(x225)
        x8306._6_=(x228)
        x965.slice(x8306, ({ x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8304.append(x245)
            ()
          }
        }))
        val x249 = x8304.size
        var x251: Int = (x249./(2))
        val x252 = x8304.size
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
        
        val x266 = x8304.sortWith(({ (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8407 = x259._4
            val x8408 = x260._4
            val x263 = x8407.compareToIgnoreCase(x8408)
            (x263.<(0))
          }
        }))
        val x267 = x251
        val x268 = x266.apply(x267)
        x8301 = x268
        ()
      }
      else
      {
        x8324._1_=(x227)
        x8324._2_=(x226)
        x8324._3_=(x225)
        val x13182 = x964.get(x8324)
        x8301 = x13182
        ()
      }
      
      val x275 = x8301
      val x8329 = x275._21
      var x277: String = x8329
      val x278 = x8301
      val x8332 = x278._14
      val x280 = x8332.contains("BC")
      if(x280) 
      {
        val x281 = x8301
        val x8336 = x281._1
        val x283 = x277
        val x285 = "%d %d %d %d %d $%f %s | %s".format(x8336,x226,x225,x223,x222,x229,x220,x283)
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
        
        val x294 = x8301
        x294._17 +=(x229)
        val x296 = x8301
        val x297 = x277
        x296._21_=(x297)
        ()
      }
      else
      {
        val x299 = x8301
        x299._17 +=(x229)
        ()
      }
      
      val x302 = x8301
      x964.update(x302)
      x965.update(x302)
      val x8357 = x13138._2
      val x8358 = x13143._3
      val x306 = x8357.length
      val x309 = if((x306.>(10))) 
      {
        val x308 = x8357.substring(0, 10)
        x308
      }
      else
      {
        x8357
      }
      
      val x310 = x309.+("    ")
      val x311 = x8358.length
      val x314 = if((x311.>(10))) 
      {
        val x313 = x8358.substring(0, 10)
        x313
      }
      else
      {
        x8358
      }
      
      val x315 = x310.+(x314)
      val x316 = x8301
      val x8370 = x316._1
      x4591.insert((SEntry8_IIIIITDS(x8370, x226, x225, x223, x222, x220, x229, x315)))
      1
    }
  }
  class NewOrderTx(x4511: Store[SEntry3_III], x4591: Store[SEntry8_IIIIITDS], x4610: Store[SEntry9_ISSSSSSDD], x4629: Store[SEntry5_IISDS], x4853: Store[SEntry8_IIIITIIB], x4880: Store[SEntry11_IISSSSSSDDI], x5052: Store[SEntry10_IIIIIITIDS], x5158: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5184: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
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
        x8571._1_=(x350)
        val x13343 = x938.get(x8571)
        if((x13343.==(null))) 
        {
          x344 = false
          ()
        }
        else
        {
          val x356 = x341
          val x8578 = x13343._3
          x333.update(x356, x8578)
          val x359 = x341
          val x8581 = x13343._4
          x332.update(x359, x8581)
          val x362 = x341
          val x8584 = x13343._5
          x343.update(x362, x8584)
          ()
        }
        
        val x366 = x341
        x341 = (x366.+(1))
        ()
      }
      val x370 = x344
      if(x370) 
      {
        x8591._1_=(x326)
        x8591._2_=(x325)
        x8591._3_=(x324)
        val x13365 = x964.get(x8591)
        x8594._1_=(x324)
        val x13368 = x933.get(x8594)
        x8597._1_=(x325)
        x8597._2_=(x324)
        val x13372 = x952.get(x8597)
        val x8600 = x13372._11
        x13372._11 +=(1)
        x4853.insert((SEntry8_IIIITIIB(x8600, x325, x324, x326, x322, -1, x327, (x328.>(0)))))
        x4511.insert((SEntry3_III(x8600, x325, x324)))
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
          x8621._1_=(x397)
          x8621._2_=(x395)
          val x13395 = x970.get(x8621)
          val x429 = if((x325.==(1))) 
          {
            val x8625 = x13395._4
            x8625
          }
          else
          {
            val x428 = if((x325.==(2))) 
            {
              val x8628 = x13395._5
              x8628
            }
            else
            {
              val x427 = if((x325.==(3))) 
              {
                val x8631 = x13395._6
                x8631
              }
              else
              {
                val x426 = if((x325.==(4))) 
                {
                  val x8634 = x13395._7
                  x8634
                }
                else
                {
                  val x425 = if((x325.==(5))) 
                  {
                    val x8637 = x13395._8
                    x8637
                  }
                  else
                  {
                    val x424 = if((x325.==(6))) 
                    {
                      val x8640 = x13395._9
                      x8640
                    }
                    else
                    {
                      val x423 = if((x325.==(7))) 
                      {
                        val x8643 = x13395._10
                        x8643
                      }
                      else
                      {
                        val x422 = if((x325.==(8))) 
                        {
                          val x8646 = x13395._11
                          x8646
                        }
                        else
                        {
                          val x421 = if((x325.==(9))) 
                          {
                            val x8649 = x13395._12
                            x8649
                          }
                          else
                          {
                            val x8650 = x13395._13
                            x8650
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
          
          val x8651 = x13395._3
          val x431 = x341
          x334.update(x431, x8651)
          val x8654 = x13365._14
          val x434 = x8654.contains("original")
          if((x434.&&({
            val x8657 = x13395._17
            val x436 = x8657.contains("original")
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
          
          x13395._3_=((x8651.-(x399)))
          if((x8651.<=(x399))) 
          {
            x13395._3 +=(91)
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
          
          val x8674 = x13365._16
          val x8675 = x13368._8
          val x8676 = x13372._9
          val x456 = x341
          val x457 = x332.apply(x456)
          val x464 = (((x399.toDouble).*(x457)).*(((1.0.+(x8675)).+(x8676)))).*((1.0.-(x8674)))
          val x465 = x341
          x336.update(x465, x464)
          val x467 = x390
          x390 = (x467.+(x464))
          val x470 = x341
          x5052.insert((SEntry10_IIIIIITIDS(x8600, x325, x324, (x470.+(1)), x397, x395, null, x399, x464, x429)))
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
