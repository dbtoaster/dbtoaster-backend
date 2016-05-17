
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
      val x5965 = x18._1
      x5965
    }
  }
  val x4372 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x4373 = new Store[SEntry3_III](2, x4372)
  val x920 = x4373.index(0, ISliceHeapMin, false, 1)
  val x921 = x4373.index(1, INone, false, -1)
  val x4451 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4452 = new Store[SEntry8_IIIIITDS](1, x4451)
  val x926 = x4452.index(0, IList, false, -1)
  val x4492 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1)
  val x4493 = new Store[SEntry9_ISSSSSSDD](1, x4492)
  val x931 = x4493.index(0, IHash, true, -1)
  val x4532 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1)
  val x4533 = new Store[SEntry5_IISDS](1, x4532)
  val x934 = x4533.index(0, IHash, true, -1)
  val x936 = { x210: SEntry8_IIIITIIB => {
      val x6241 = x210._1
      x6241
    }
  }
  val x4756 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4757 = new Store[SEntry8_IIIITIIB](3, x4756)
  val x942 = x4757.index(0, IHash, true, -1)
  val x943 = x4757.index(1, ISliceHeapMax, false, 2)
  val x944 = x4757.index(2, INone, false, -1)
  val x4818 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx12)
  val x4819 = new Store[SEntry11_IISSSSSSDDI](1, x4818)
  val x949 = x4819.index(0, IHash, true, -1)
  val x4897 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx123)
  val x4898 = new Store[SEntry10_IIIIIITIDS](1, x4897)
  val x953 = x4898.index(0, IHash, false, -1)
  val x5050 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x5051 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x5050)
  val x958 = x5051.index(0, IHash, true, -1)
  val x959 = x5051.index(1, IHash, false, -1)
  val x5110 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx12)
  val x5111 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x5110)
  val x962 = x5111.index(0, IHash, true, -1)
  
  val newOrderTbl = x4373
  val historyTbl = x4452
  val warehouseTbl = x4493
  val itemTbl = x4533
  val orderTbl = x4757
  val districtTbl = x4819
  val orderLineTbl = x4898
  val customerTbl = x5051
  val stockTbl = x5111
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4681 : SEntry8_IIIITIIB) = {
      var x4682: Int = -889275714
      val x4683 = x4681._2
      val x4685 = -862048943.*((x4683.hashCode()))
      val x4690 = x4682
      val x4691 = (((x4685.<<(15)).|((x4685.>>>(-15)))).*(461845907)).^(x4690)
      x4682 = ((((x4691.<<(13)).|((x4691.>>>(-13)))).*(5)).+(-430675100))
      val x4698 = x4681._3
      val x4700 = -862048943.*((x4698.hashCode()))
      val x4705 = x4682
      val x4706 = (((x4700.<<(15)).|((x4700.>>>(-15)))).*(461845907)).^(x4705)
      x4682 = ((((x4706.<<(13)).|((x4706.>>>(-13)))).*(5)).+(-430675100))
      val x4713 = x4681._4
      val x4715 = -862048943.*((x4713.hashCode()))
      val x4720 = x4682
      val x4721 = (((x4715.<<(15)).|((x4715.>>>(-15)))).*(461845907)).^(x4720)
      x4682 = ((((x4721.<<(13)).|((x4721.>>>(-13)))).*(5)).+(-430675100))
      val x4728 = x4682
      val x4729 = x4728.^(2)
      val x4732 = (x4729.^((x4729.>>>(16)))).*(-2048144789)
      val x4735 = (x4732.^((x4732.>>>(13)))).*(-1028477387)
      (x4735.^((x4735.>>>(16))))
    }
    override def cmp(x4739 : SEntry8_IIIITIIB , x4740 : SEntry8_IIIITIIB) = {
      val x4741 = x4739._2
      val x4742 = x4740._2
      (if((((x4741.==(x4742)).&&({
        val x4744 = x4739._3
        val x4745 = x4740._3
        (x4744.==(x4745))
      })).&&({
        val x4748 = x4739._4
        val x4749 = x4740._4
        (x4748.==(x4749))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4901 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4902: Int = -889275714
      val x4903 = x4901._1
      val x4905 = -862048943.*((x4903.hashCode()))
      val x4910 = x4902
      val x4911 = (((x4905.<<(15)).|((x4905.>>>(-15)))).*(461845907)).^(x4910)
      x4902 = ((((x4911.<<(13)).|((x4911.>>>(-13)))).*(5)).+(-430675100))
      val x4918 = x4901._2
      val x4920 = -862048943.*((x4918.hashCode()))
      val x4925 = x4902
      val x4926 = (((x4920.<<(15)).|((x4920.>>>(-15)))).*(461845907)).^(x4925)
      x4902 = ((((x4926.<<(13)).|((x4926.>>>(-13)))).*(5)).+(-430675100))
      val x4933 = x4901._3
      val x4935 = -862048943.*((x4933.hashCode()))
      val x4940 = x4902
      val x4941 = (((x4935.<<(15)).|((x4935.>>>(-15)))).*(461845907)).^(x4940)
      x4902 = ((((x4941.<<(13)).|((x4941.>>>(-13)))).*(5)).+(-430675100))
      val x4948 = x4902
      val x4949 = x4948.^(2)
      val x4952 = (x4949.^((x4949.>>>(16)))).*(-2048144789)
      val x4955 = (x4952.^((x4952.>>>(13)))).*(-1028477387)
      (x4955.^((x4955.>>>(16))))
    }
    override def cmp(x4959 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4960 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4961 = x4959._1
      val x4962 = x4960._1
      (if((((x4961.==(x4962)).&&({
        val x4964 = x4959._2
        val x4965 = x4960._2
        (x4964.==(x4965))
      })).&&({
        val x4968 = x4959._3
        val x4969 = x4960._3
        (x4968.==(x4969))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4822 : SEntry10_IIIIIITIDS) = {
      var x4823: Int = -889275714
      val x4824 = x4822._1
      val x4826 = -862048943.*((x4824.hashCode()))
      val x4831 = x4823
      val x4832 = (((x4826.<<(15)).|((x4826.>>>(-15)))).*(461845907)).^(x4831)
      x4823 = ((((x4832.<<(13)).|((x4832.>>>(-13)))).*(5)).+(-430675100))
      val x4839 = x4822._2
      val x4841 = -862048943.*((x4839.hashCode()))
      val x4846 = x4823
      val x4847 = (((x4841.<<(15)).|((x4841.>>>(-15)))).*(461845907)).^(x4846)
      x4823 = ((((x4847.<<(13)).|((x4847.>>>(-13)))).*(5)).+(-430675100))
      val x4854 = x4822._3
      val x4856 = -862048943.*((x4854.hashCode()))
      val x4861 = x4823
      val x4862 = (((x4856.<<(15)).|((x4856.>>>(-15)))).*(461845907)).^(x4861)
      x4823 = ((((x4862.<<(13)).|((x4862.>>>(-13)))).*(5)).+(-430675100))
      val x4869 = x4823
      val x4870 = x4869.^(2)
      val x4873 = (x4870.^((x4870.>>>(16)))).*(-2048144789)
      val x4876 = (x4873.^((x4873.>>>(13)))).*(-1028477387)
      (x4876.^((x4876.>>>(16))))
    }
    override def cmp(x4880 : SEntry10_IIIIIITIDS , x4881 : SEntry10_IIIIIITIDS) = {
      val x4882 = x4880._1
      val x4883 = x4881._1
      (if((((x4882.==(x4883)).&&({
        val x4885 = x4880._2
        val x4886 = x4881._2
        (x4885.==(x4886))
      })).&&({
        val x4889 = x4880._3
        val x4890 = x4881._3
        (x4889.==(x4890))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4316 : SEntry3_III) = {
      var x4317: Int = -889275714
      val x4318 = x4316._2
      val x4320 = -862048943.*((x4318.hashCode()))
      val x4325 = x4317
      val x4326 = (((x4320.<<(15)).|((x4320.>>>(-15)))).*(461845907)).^(x4325)
      x4317 = ((((x4326.<<(13)).|((x4326.>>>(-13)))).*(5)).+(-430675100))
      val x4333 = x4316._3
      val x4335 = -862048943.*((x4333.hashCode()))
      val x4340 = x4317
      val x4341 = (((x4335.<<(15)).|((x4335.>>>(-15)))).*(461845907)).^(x4340)
      x4317 = ((((x4341.<<(13)).|((x4341.>>>(-13)))).*(5)).+(-430675100))
      val x4348 = x4317
      val x4349 = x4348.^(2)
      val x4352 = (x4349.^((x4349.>>>(16)))).*(-2048144789)
      val x4355 = (x4352.^((x4352.>>>(13)))).*(-1028477387)
      (x4355.^((x4355.>>>(16))))
    }
    override def cmp(x4359 : SEntry3_III , x4360 : SEntry3_III) = {
      val x4361 = x4359._2
      val x4362 = x4360._2
      (if(((x4361.==(x4362)).&&({
        val x4364 = x4359._3
        val x4365 = x4360._3
        (x4364.==(x4365))
      }))) 0 else 1)
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx12 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5054 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5055: Int = -889275714
      val x5056 = x5054._1
      val x5058 = -862048943.*((x5056.hashCode()))
      val x5063 = x5055
      val x5064 = (((x5058.<<(15)).|((x5058.>>>(-15)))).*(461845907)).^(x5063)
      x5055 = ((((x5064.<<(13)).|((x5064.>>>(-13)))).*(5)).+(-430675100))
      val x5071 = x5054._2
      val x5073 = -862048943.*((x5071.hashCode()))
      val x5078 = x5055
      val x5079 = (((x5073.<<(15)).|((x5073.>>>(-15)))).*(461845907)).^(x5078)
      x5055 = ((((x5079.<<(13)).|((x5079.>>>(-13)))).*(5)).+(-430675100))
      val x5086 = x5055
      val x5087 = x5086.^(2)
      val x5090 = (x5087.^((x5087.>>>(16)))).*(-2048144789)
      val x5093 = (x5090.^((x5090.>>>(13)))).*(-1028477387)
      (x5093.^((x5093.>>>(16))))
    }
    override def cmp(x5097 : SEntry17_IIISSSSSSSSSSIIIS , x5098 : SEntry17_IIISSSSSSSSSSIIIS) = {
      val x5099 = x5097._1
      val x5100 = x5098._1
      (if(((x5099.==(x5100)).&&({
        val x5102 = x5097._2
        val x5103 = x5098._2
        (x5102.==(x5103))
      }))) 0 else 1)
    }
  }
   object SEntry5_IISDS_Idx1 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4495 : SEntry5_IISDS) = {
      var x4496: Int = -889275714
      val x4497 = x4495._1
      val x4499 = -862048943.*((x4497.hashCode()))
      val x4504 = x4496
      val x4505 = (((x4499.<<(15)).|((x4499.>>>(-15)))).*(461845907)).^(x4504)
      x4496 = ((((x4505.<<(13)).|((x4505.>>>(-13)))).*(5)).+(-430675100))
      val x4512 = x4496
      val x4513 = x4512.^(2)
      val x4516 = (x4513.^((x4513.>>>(16)))).*(-2048144789)
      val x4519 = (x4516.^((x4516.>>>(13)))).*(-1028477387)
      (x4519.^((x4519.>>>(16))))
    }
    override def cmp(x4523 : SEntry5_IISDS , x4524 : SEntry5_IISDS) = {
      val x4525 = x4523._1
      val x4526 = x4524._1
      (if((x4525.==(x4526))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4377 : SEntry8_IIIIITDS) = {
      var x4378: Int = -889275714
      val x4379 = x4378
      val x4380 = x4379.^(2)
      val x4383 = (x4380.^((x4380.>>>(16)))).*(-2048144789)
      val x4386 = (x4383.^((x4383.>>>(13)))).*(-1028477387)
      (x4386.^((x4386.>>>(16))))
    }
    override def cmp(x4390 : SEntry8_IIIIITDS , x4391 : SEntry8_IIIIITDS) = {
      val x4392 = x4390._1
      val x4393 = x4391._1
      (if((((((((((x4392.==(-1)).||({
        (x4393.==(-1))
      })).||({
        (x4392.==(x4393))
      })).&&({
        val x4399 = x4390._2
        val x4400 = x4391._2
        (((x4399.==(-1)).||({
          (x4400.==(-1))
        })).||({
          (x4399.==(x4400))
        }))
      })).&&({
        val x4407 = x4390._3
        val x4408 = x4391._3
        (((x4407.==(-1)).||({
          (x4408.==(-1))
        })).||({
          (x4407.==(x4408))
        }))
      })).&&({
        val x4415 = x4390._4
        val x4416 = x4391._4
        (((x4415.==(-1)).||({
          (x4416.==(-1))
        })).||({
          (x4415.==(x4416))
        }))
      })).&&({
        val x4423 = x4390._5
        val x4424 = x4391._5
        (((x4423.==(-1)).||({
          (x4424.==(-1))
        })).||({
          (x4423.==(x4424))
        }))
      })).&&({
        val x4431 = x4390._6
        val x4432 = x4391._6
        (((x4431.==(null)).||({
          (x4432.==(null))
        })).||({
          (x4431.==(x4432))
        }))
      })).&&({
        val x4439 = x4390._7
        val x4440 = x4391._7
        (((x4439.==(-1.0)).||({
          (x4440.==(-1.0))
        })).||({
          (x4439.==(x4440))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry11_IISSSSSSDDI_Idx12 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4762 : SEntry11_IISSSSSSDDI) = {
      var x4763: Int = -889275714
      val x4764 = x4762._1
      val x4766 = -862048943.*((x4764.hashCode()))
      val x4771 = x4763
      val x4772 = (((x4766.<<(15)).|((x4766.>>>(-15)))).*(461845907)).^(x4771)
      x4763 = ((((x4772.<<(13)).|((x4772.>>>(-13)))).*(5)).+(-430675100))
      val x4779 = x4762._2
      val x4781 = -862048943.*((x4779.hashCode()))
      val x4786 = x4763
      val x4787 = (((x4781.<<(15)).|((x4781.>>>(-15)))).*(461845907)).^(x4786)
      x4763 = ((((x4787.<<(13)).|((x4787.>>>(-13)))).*(5)).+(-430675100))
      val x4794 = x4763
      val x4795 = x4794.^(2)
      val x4798 = (x4795.^((x4795.>>>(16)))).*(-2048144789)
      val x4801 = (x4798.^((x4798.>>>(13)))).*(-1028477387)
      (x4801.^((x4801.>>>(16))))
    }
    override def cmp(x4805 : SEntry11_IISSSSSSDDI , x4806 : SEntry11_IISSSSSSDDI) = {
      val x4807 = x4805._1
      val x4808 = x4806._1
      (if(((x4807.==(x4808)).&&({
        val x4810 = x4805._2
        val x4811 = x4806._2
        (x4810.==(x4811))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4975 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4976: Int = -889275714
      val x4977 = x4975._2
      val x4979 = -862048943.*((x4977.hashCode()))
      val x4984 = x4976
      val x4985 = (((x4979.<<(15)).|((x4979.>>>(-15)))).*(461845907)).^(x4984)
      x4976 = ((((x4985.<<(13)).|((x4985.>>>(-13)))).*(5)).+(-430675100))
      val x4992 = x4975._3
      val x4994 = -862048943.*((x4992.hashCode()))
      val x4999 = x4976
      val x5000 = (((x4994.<<(15)).|((x4994.>>>(-15)))).*(461845907)).^(x4999)
      x4976 = ((((x5000.<<(13)).|((x5000.>>>(-13)))).*(5)).+(-430675100))
      val x5007 = x4975._6
      val x5009 = -862048943.*((x5007.hashCode()))
      val x5014 = x4976
      val x5015 = (((x5009.<<(15)).|((x5009.>>>(-15)))).*(461845907)).^(x5014)
      x4976 = ((((x5015.<<(13)).|((x5015.>>>(-13)))).*(5)).+(-430675100))
      val x5022 = x4976
      val x5023 = x5022.^(2)
      val x5026 = (x5023.^((x5023.>>>(16)))).*(-2048144789)
      val x5029 = (x5026.^((x5026.>>>(13)))).*(-1028477387)
      (x5029.^((x5029.>>>(16))))
    }
    override def cmp(x5033 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5034 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5035 = x5033._2
      val x5036 = x5034._2
      (if((((x5035.==(x5036)).&&({
        val x5038 = x5033._3
        val x5039 = x5034._3
        (x5038.==(x5039))
      })).&&({
        val x5042 = x5033._6
        val x5043 = x5034._6
        (x5042.==(x5043))
      }))) 0 else 1)
    }
  }
   object SEntry9_ISSSSSSDD_Idx1 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4455 : SEntry9_ISSSSSSDD) = {
      var x4456: Int = -889275714
      val x4457 = x4455._1
      val x4459 = -862048943.*((x4457.hashCode()))
      val x4464 = x4456
      val x4465 = (((x4459.<<(15)).|((x4459.>>>(-15)))).*(461845907)).^(x4464)
      x4456 = ((((x4465.<<(13)).|((x4465.>>>(-13)))).*(5)).+(-430675100))
      val x4472 = x4456
      val x4473 = x4472.^(2)
      val x4476 = (x4473.^((x4473.>>>(16)))).*(-2048144789)
      val x4479 = (x4476.^((x4476.>>>(13)))).*(-1028477387)
      (x4479.^((x4479.>>>(16))))
    }
    override def cmp(x4483 : SEntry9_ISSSSSSDD , x4484 : SEntry9_ISSSSSSDD) = {
      val x4485 = x4483._1
      val x4486 = x4484._1
      (if((x4485.==(x4486))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4539 : SEntry8_IIIITIIB) = {
      var x4540: Int = -889275714
      val x4541 = x4539._1
      val x4543 = -862048943.*((x4541.hashCode()))
      val x4548 = x4540
      val x4549 = (((x4543.<<(15)).|((x4543.>>>(-15)))).*(461845907)).^(x4548)
      x4540 = ((((x4549.<<(13)).|((x4549.>>>(-13)))).*(5)).+(-430675100))
      val x4556 = x4539._2
      val x4558 = -862048943.*((x4556.hashCode()))
      val x4563 = x4540
      val x4564 = (((x4558.<<(15)).|((x4558.>>>(-15)))).*(461845907)).^(x4563)
      x4540 = ((((x4564.<<(13)).|((x4564.>>>(-13)))).*(5)).+(-430675100))
      val x4571 = x4539._3
      val x4573 = -862048943.*((x4571.hashCode()))
      val x4578 = x4540
      val x4579 = (((x4573.<<(15)).|((x4573.>>>(-15)))).*(461845907)).^(x4578)
      x4540 = ((((x4579.<<(13)).|((x4579.>>>(-13)))).*(5)).+(-430675100))
      val x4586 = x4540
      val x4587 = x4586.^(2)
      val x4590 = (x4587.^((x4587.>>>(16)))).*(-2048144789)
      val x4593 = (x4590.^((x4590.>>>(13)))).*(-1028477387)
      (x4593.^((x4593.>>>(16))))
    }
    override def cmp(x4597 : SEntry8_IIIITIIB , x4598 : SEntry8_IIIITIIB) = {
      val x4599 = x4597._1
      val x4600 = x4598._1
      (if((((x4599.==(x4600)).&&({
        val x4602 = x4597._2
        val x4603 = x4598._2
        (x4602.==(x4603))
      })).&&({
        val x4606 = x4597._3
        val x4607 = x4598._3
        (x4606.==(x4607))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4263 : SEntry3_III) = {
      var x4264: Int = -889275714
      val x4265 = x4263._2
      val x4267 = -862048943.*((x4265.hashCode()))
      val x4272 = x4264
      val x4273 = (((x4267.<<(15)).|((x4267.>>>(-15)))).*(461845907)).^(x4272)
      x4264 = ((((x4273.<<(13)).|((x4273.>>>(-13)))).*(5)).+(-430675100))
      val x4280 = x4263._3
      val x4282 = -862048943.*((x4280.hashCode()))
      val x4287 = x4264
      val x4288 = (((x4282.<<(15)).|((x4282.>>>(-15)))).*(461845907)).^(x4287)
      x4264 = ((((x4288.<<(13)).|((x4288.>>>(-13)))).*(5)).+(-430675100))
      val x4295 = x4264
      val x4296 = x4295.^(2)
      val x4299 = (x4296.^((x4296.>>>(16)))).*(-2048144789)
      val x4302 = (x4299.^((x4299.>>>(13)))).*(-1028477387)
      (x4302.^((x4302.>>>(16))))
    }
    override def cmp(x4306 : SEntry3_III , x4307 : SEntry3_III) = {
      val x4308 = x914.apply(x4306)
      val x4309 = x914.apply(x4307)
      val x4312 = if((x4308.>(x4309))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4308.==(x4309))) 0 else x4312)
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4613 : SEntry8_IIIITIIB) = {
      var x4614: Int = -889275714
      val x4615 = x4613._2
      val x4617 = -862048943.*((x4615.hashCode()))
      val x4622 = x4614
      val x4623 = (((x4617.<<(15)).|((x4617.>>>(-15)))).*(461845907)).^(x4622)
      x4614 = ((((x4623.<<(13)).|((x4623.>>>(-13)))).*(5)).+(-430675100))
      val x4630 = x4613._3
      val x4632 = -862048943.*((x4630.hashCode()))
      val x4637 = x4614
      val x4638 = (((x4632.<<(15)).|((x4632.>>>(-15)))).*(461845907)).^(x4637)
      x4614 = ((((x4638.<<(13)).|((x4638.>>>(-13)))).*(5)).+(-430675100))
      val x4645 = x4613._4
      val x4647 = -862048943.*((x4645.hashCode()))
      val x4652 = x4614
      val x4653 = (((x4647.<<(15)).|((x4647.>>>(-15)))).*(461845907)).^(x4652)
      x4614 = ((((x4653.<<(13)).|((x4653.>>>(-13)))).*(5)).+(-430675100))
      val x4660 = x4614
      val x4661 = x4660.^(2)
      val x4664 = (x4661.^((x4661.>>>(16)))).*(-2048144789)
      val x4667 = (x4664.^((x4664.>>>(13)))).*(-1028477387)
      (x4667.^((x4667.>>>(16))))
    }
    override def cmp(x4671 : SEntry8_IIIITIIB , x4672 : SEntry8_IIIITIIB) = {
      val x4673 = x936.apply(x4671)
      val x4674 = x936.apply(x4672)
      val x4677 = if((x4673.>(x4674))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4673.==(x4674))) 0 else x4677)
    }
  }
  val x7988 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8191 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8102 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7702 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8521 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8494 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x8021 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x8196 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8206 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8471 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  val x7678 = SEntry3_III(-1, -1, -1)
  val x7976 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x8491 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7698 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x8084 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x8497 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7689 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x8224 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  class DeliveryTx(x4373: Store[SEntry3_III], x4452: Store[SEntry8_IIIIITDS], x4493: Store[SEntry9_ISSSSSSDD], x4533: Store[SEntry5_IISDS], x4757: Store[SEntry8_IIIITIIB], x4819: Store[SEntry11_IISSSSSSDDI], x4898: Store[SEntry10_IIIIIITIDS], x5051: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5111: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x7678._2_=(x22)
        x7678._3_=(x12)
        val x10899 = x920.get(x7678)
        if((x10899.!=(null))) 
        {
          val x7683 = x10899._1
          val x29 = x15
          x14.update((x29.-(1)), x7683)
          x920.delete(x10899)
          x921.delete(x10899)
          val x33 = x15
          x7689._1_=(x7683)
          x7689._2_=(x33)
          x7689._3_=(x12)
          val x10913 = x942.get(x7689)
          val x7692 = x10913._4
          x10913._6_=(x13)
          x942.update(x10913)
          x943.update(x10913)
          x944.update(x10913)
          var x40: Double = 0.0
          val x41 = x15
          x7698._1_=(x7683)
          x7698._2_=(x41)
          x7698._3_=(x12)
          x953.slice(x7698, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x7800 = x44._9
              x40 = (x46.+(x7800))
              x953.update(x44)
              ()
            }
          }))
          val x53 = x15
          x7702._1_=(x7692)
          x7702._2_=(x53)
          x7702._3_=(x12)
          val x10938 = x958.get(x7702)
          val x56 = x40
          x10938._17 +=(x56)
          x10938._20 +=(1)
          x959.update(x10938)
          x958.update(x10938)
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
  class StockLevelTx(x4373: Store[SEntry3_III], x4452: Store[SEntry8_IIIIITDS], x4493: Store[SEntry9_ISSSSSSDD], x4533: Store[SEntry5_IISDS], x4757: Store[SEntry8_IIIITIIB], x4819: Store[SEntry11_IISSSSSSDDI], x4898: Store[SEntry10_IIIIIITIDS], x5051: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5111: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) =     {
      x7976._1_=(x126)
      x7976._2_=(x125)
      val x11122 = x949.get(x7976)
      val x7979 = x11122._11
      var x133: Int = (x7979.-(20))
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        (x135.<(x7979))
      })
      {
        val x137 = x133
        x7988._1_=(x137)
        x7988._2_=(x126)
        x7988._3_=(x125)
        x953.slice(x7988, ({ x140: SEntry10_IIIIIITIDS => {
            val x8020 = x140._5
            x8021._1_=(x8020)
            x8021._2_=(x125)
            val x11140 = x962.get(x8021)
            val x8023 = x11140._3
            if((x8023.<(x127))) 
            {
              val x146 = x134.+=(x8020)
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
  class OrderStatusTx(x4373: Store[SEntry3_III], x4452: Store[SEntry8_IIIIITDS], x4493: Store[SEntry9_ISSSSSSDD], x4533: Store[SEntry5_IISDS], x4757: Store[SEntry8_IIIITIIB], x4819: Store[SEntry11_IISSSSSSDDI], x4898: Store[SEntry10_IIIIIITIDS], x5051: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5111: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) =     {
      var x8079: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x170.>(0))) 
      {
        val x8082 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8084._2_=(x169)
        x8084._3_=(x168)
        x8084._6_=(x172)
        x959.slice(x8084, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8082.append(x178)
            ()
          }
        }))
        val x182 = x8082.size
        var x184: Int = (x182./(2))
        val x185 = x8082.size
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
        
        val x199 = x8082.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8134 = x192._4
            val x8135 = x193._4
            val x196 = x8134.compareToIgnoreCase(x8135)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x201 = x199.apply(x200)
        x8079 = x201
        ()
      }
      else
      {
        x8102._1_=(x171)
        x8102._2_=(x169)
        x8102._3_=(x168)
        val x11238 = x958.get(x8102)
        x8079 = x11238
        ()
      }
      
      val x208 = x8079
      val x8107 = x208._3
      val x215 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x169, x168, x8107)
      var x218: Int = 0
      1
    }
  }
  class PaymentTx(x4373: Store[SEntry3_III], x4452: Store[SEntry8_IIIIITDS], x4493: Store[SEntry9_ISSSSSSDD], x4533: Store[SEntry5_IISDS], x4757: Store[SEntry8_IIIITIIB], x4819: Store[SEntry11_IISSSSSSDDI], x4898: Store[SEntry10_IIIIIITIDS], x5051: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5111: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) =     {
      x8191._1_=(x222)
      val x11291 = x931.get(x8191)
      x11291._9 +=(x229)
      x931.update(x11291)
      x8196._1_=(x223)
      x8196._2_=(x222)
      val x11297 = x949.get(x8196)
      x11297._10 +=(x229)
      x949.update(x11297)
      var x8201: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x224.>(0))) 
      {
        val x8204 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8206._2_=(x226)
        x8206._3_=(x225)
        x8206._6_=(x228)
        x959.slice(x8206, ({ x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8204.append(x245)
            ()
          }
        }))
        val x249 = x8204.size
        var x251: Int = (x249./(2))
        val x252 = x8204.size
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
        
        val x266 = x8204.sortWith(({ (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8307 = x259._4
            val x8308 = x260._4
            val x263 = x8307.compareToIgnoreCase(x8308)
            (x263.<(0))
          }
        }))
        val x267 = x251
        val x268 = x266.apply(x267)
        x8201 = x268
        ()
      }
      else
      {
        x8224._1_=(x227)
        x8224._2_=(x226)
        x8224._3_=(x225)
        val x11337 = x958.get(x8224)
        x8201 = x11337
        ()
      }
      
      val x275 = x8201
      val x8229 = x275._21
      var x277: String = x8229
      val x278 = x8201
      val x8232 = x278._14
      val x280 = x8232.contains("BC")
      if(x280) 
      {
        val x281 = x8201
        val x8236 = x281._1
        val x283 = x277
        val x285 = "%d %d %d %d %d $%f %s | %s".format(x8236,x226,x225,x223,x222,x229,x220,x283)
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
        
        val x294 = x8201
        x294._17 +=(x229)
        val x296 = x8201
        val x297 = x277
        x296._21_=(x297)
        ()
      }
      else
      {
        val x299 = x8201
        x299._17 +=(x229)
        ()
      }
      
      val x302 = x8201
      x959.update(x302)
      x958.update(x302)
      val x8257 = x11291._2
      val x8258 = x11297._3
      val x306 = x8257.length
      val x309 = if((x306.>(10))) 
      {
        val x308 = x8257.substring(0, 10)
        x308
      }
      else
      {
        x8257
      }
      
      val x310 = x309.+("    ")
      val x311 = x8258.length
      val x314 = if((x311.>(10))) 
      {
        val x313 = x8258.substring(0, 10)
        x313
      }
      else
      {
        x8258
      }
      
      val x315 = x310.+(x314)
      val x316 = x8201
      val x8270 = x316._1
      x4452.insert((SEntry8_IIIIITDS(x8270, x226, x225, x223, x222, x220, x229, x315)))
      1
    }
  }
  class NewOrderTx(x4373: Store[SEntry3_III], x4452: Store[SEntry8_IIIIITDS], x4493: Store[SEntry9_ISSSSSSDD], x4533: Store[SEntry5_IISDS], x4757: Store[SEntry8_IIIITIIB], x4819: Store[SEntry11_IISSSSSSDDI], x4898: Store[SEntry10_IIIIIITIDS], x5051: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5111: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
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
        x8471._1_=(x350)
        val x11500 = x934.get(x8471)
        if((x11500.==(null))) 
        {
          x344 = false
          ()
        }
        else
        {
          val x356 = x341
          val x8478 = x11500._3
          x333.update(x356, x8478)
          val x359 = x341
          val x8481 = x11500._4
          x332.update(x359, x8481)
          val x362 = x341
          val x8484 = x11500._5
          x343.update(x362, x8484)
          ()
        }
        
        val x366 = x341
        x341 = (x366.+(1))
        ()
      }
      val x370 = x344
      if(x370) 
      {
        x8491._1_=(x326)
        x8491._2_=(x325)
        x8491._3_=(x324)
        val x11522 = x958.get(x8491)
        x8494._1_=(x324)
        val x11525 = x931.get(x8494)
        x8497._1_=(x325)
        x8497._2_=(x324)
        val x11529 = x949.get(x8497)
        val x8500 = x11529._11
        x11529._11 +=(1)
        x949.update(x11529)
        x4757.insert((SEntry8_IIIITIIB(x8500, x325, x324, x326, x322, -1, x327, (x328.>(0)))))
        x4373.insert((SEntry3_III(x8500, x325, x324)))
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
          x8521._1_=(x397)
          x8521._2_=(x395)
          val x11553 = x962.get(x8521)
          val x429 = if((x325.==(1))) 
          {
            val x8525 = x11553._4
            x8525
          }
          else
          {
            val x428 = if((x325.==(2))) 
            {
              val x8528 = x11553._5
              x8528
            }
            else
            {
              val x427 = if((x325.==(3))) 
              {
                val x8531 = x11553._6
                x8531
              }
              else
              {
                val x426 = if((x325.==(4))) 
                {
                  val x8534 = x11553._7
                  x8534
                }
                else
                {
                  val x425 = if((x325.==(5))) 
                  {
                    val x8537 = x11553._8
                    x8537
                  }
                  else
                  {
                    val x424 = if((x325.==(6))) 
                    {
                      val x8540 = x11553._9
                      x8540
                    }
                    else
                    {
                      val x423 = if((x325.==(7))) 
                      {
                        val x8543 = x11553._10
                        x8543
                      }
                      else
                      {
                        val x422 = if((x325.==(8))) 
                        {
                          val x8546 = x11553._11
                          x8546
                        }
                        else
                        {
                          val x421 = if((x325.==(9))) 
                          {
                            val x8549 = x11553._12
                            x8549
                          }
                          else
                          {
                            val x8550 = x11553._13
                            x8550
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
          
          val x8551 = x11553._3
          val x431 = x341
          x334.update(x431, x8551)
          val x8554 = x11522._14
          val x434 = x8554.contains("original")
          if((x434.&&({
            val x8557 = x11553._17
            val x436 = x8557.contains("original")
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
          
          x11553._3_=((x8551.-(x399)))
          if((x8551.<=(x399))) 
          {
            x11553._3 +=(91)
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
          
          x962.update(x11553)
          val x8574 = x11522._16
          val x8575 = x11525._8
          val x8576 = x11529._9
          val x456 = x341
          val x457 = x332.apply(x456)
          val x464 = (((x399.toDouble).*(x457)).*(((1.0.+(x8575)).+(x8576)))).*((1.0.-(x8574)))
          val x465 = x341
          x336.update(x465, x464)
          val x467 = x390
          x390 = (x467.+(x464))
          val x470 = x341
          x4898.insert((SEntry10_IIIIIITIDS(x8500, x325, x324, (x470.+(1)), x397, x395, null, x399, x464, x429)))
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
