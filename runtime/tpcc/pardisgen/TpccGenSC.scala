
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
      val x4684 = x4683.hashCode()
      val x4685 = -862048943.*(x4684)
      val x4686 = x4685.<<(15)
      val x4687 = x4685.>>>(-15)
      val x4688 = x4686.|(x4687)
      val x4689 = x4688.*(461845907)
      val x4690 = x4682
      val x4691 = x4689.^(x4690)
      val x4692 = x4691.<<(13)
      val x4693 = x4691.>>>(-13)
      val x4694 = x4692.|(x4693)
      val x4695 = x4694.*(5)
      val x4696 = x4695.+(-430675100)
      x4682 = x4696
      val x4698 = x4681._3
      val x4699 = x4698.hashCode()
      val x4700 = -862048943.*(x4699)
      val x4701 = x4700.<<(15)
      val x4702 = x4700.>>>(-15)
      val x4703 = x4701.|(x4702)
      val x4704 = x4703.*(461845907)
      val x4705 = x4682
      val x4706 = x4704.^(x4705)
      val x4707 = x4706.<<(13)
      val x4708 = x4706.>>>(-13)
      val x4709 = x4707.|(x4708)
      val x4710 = x4709.*(5)
      val x4711 = x4710.+(-430675100)
      x4682 = x4711
      val x4713 = x4681._4
      val x4714 = x4713.hashCode()
      val x4715 = -862048943.*(x4714)
      val x4716 = x4715.<<(15)
      val x4717 = x4715.>>>(-15)
      val x4718 = x4716.|(x4717)
      val x4719 = x4718.*(461845907)
      val x4720 = x4682
      val x4721 = x4719.^(x4720)
      val x4722 = x4721.<<(13)
      val x4723 = x4721.>>>(-13)
      val x4724 = x4722.|(x4723)
      val x4725 = x4724.*(5)
      val x4726 = x4725.+(-430675100)
      x4682 = x4726
      val x4728 = x4682
      val x4729 = x4728.^(2)
      val x4730 = x4729.>>>(16)
      val x4731 = x4729.^(x4730)
      val x4732 = x4731.*(-2048144789)
      val x4733 = x4732.>>>(13)
      val x4734 = x4732.^(x4733)
      val x4735 = x4734.*(-1028477387)
      val x4736 = x4735.>>>(16)
      val x4737 = x4735.^(x4736)
      x4737
    }
    override def cmp(x4739 : SEntry8_IIIITIIB , x4740 : SEntry8_IIIITIIB) = {
      val x4741 = x4739._2
      val x4742 = x4740._2
      val x4743 = x4741.==(x4742)
      val x4747 = x4743.&&({
        val x4744 = x4739._3
        val x4745 = x4740._3
        val x4746 = x4744.==(x4745)
        x4746
      })
      val x4751 = x4747.&&({
        val x4748 = x4739._4
        val x4749 = x4740._4
        val x4750 = x4748.==(x4749)
        x4750
      })
      val x4752 = if(x4751) 0 else 1
      x4752
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4901 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4902: Int = -889275714
      val x4903 = x4901._1
      val x4904 = x4903.hashCode()
      val x4905 = -862048943.*(x4904)
      val x4906 = x4905.<<(15)
      val x4907 = x4905.>>>(-15)
      val x4908 = x4906.|(x4907)
      val x4909 = x4908.*(461845907)
      val x4910 = x4902
      val x4911 = x4909.^(x4910)
      val x4912 = x4911.<<(13)
      val x4913 = x4911.>>>(-13)
      val x4914 = x4912.|(x4913)
      val x4915 = x4914.*(5)
      val x4916 = x4915.+(-430675100)
      x4902 = x4916
      val x4918 = x4901._2
      val x4919 = x4918.hashCode()
      val x4920 = -862048943.*(x4919)
      val x4921 = x4920.<<(15)
      val x4922 = x4920.>>>(-15)
      val x4923 = x4921.|(x4922)
      val x4924 = x4923.*(461845907)
      val x4925 = x4902
      val x4926 = x4924.^(x4925)
      val x4927 = x4926.<<(13)
      val x4928 = x4926.>>>(-13)
      val x4929 = x4927.|(x4928)
      val x4930 = x4929.*(5)
      val x4931 = x4930.+(-430675100)
      x4902 = x4931
      val x4933 = x4901._3
      val x4934 = x4933.hashCode()
      val x4935 = -862048943.*(x4934)
      val x4936 = x4935.<<(15)
      val x4937 = x4935.>>>(-15)
      val x4938 = x4936.|(x4937)
      val x4939 = x4938.*(461845907)
      val x4940 = x4902
      val x4941 = x4939.^(x4940)
      val x4942 = x4941.<<(13)
      val x4943 = x4941.>>>(-13)
      val x4944 = x4942.|(x4943)
      val x4945 = x4944.*(5)
      val x4946 = x4945.+(-430675100)
      x4902 = x4946
      val x4948 = x4902
      val x4949 = x4948.^(2)
      val x4950 = x4949.>>>(16)
      val x4951 = x4949.^(x4950)
      val x4952 = x4951.*(-2048144789)
      val x4953 = x4952.>>>(13)
      val x4954 = x4952.^(x4953)
      val x4955 = x4954.*(-1028477387)
      val x4956 = x4955.>>>(16)
      val x4957 = x4955.^(x4956)
      x4957
    }
    override def cmp(x4959 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4960 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4961 = x4959._1
      val x4962 = x4960._1
      val x4963 = x4961.==(x4962)
      val x4967 = x4963.&&({
        val x4964 = x4959._2
        val x4965 = x4960._2
        val x4966 = x4964.==(x4965)
        x4966
      })
      val x4971 = x4967.&&({
        val x4968 = x4959._3
        val x4969 = x4960._3
        val x4970 = x4968.==(x4969)
        x4970
      })
      val x4972 = if(x4971) 0 else 1
      x4972
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4822 : SEntry10_IIIIIITIDS) = {
      var x4823: Int = -889275714
      val x4824 = x4822._1
      val x4825 = x4824.hashCode()
      val x4826 = -862048943.*(x4825)
      val x4827 = x4826.<<(15)
      val x4828 = x4826.>>>(-15)
      val x4829 = x4827.|(x4828)
      val x4830 = x4829.*(461845907)
      val x4831 = x4823
      val x4832 = x4830.^(x4831)
      val x4833 = x4832.<<(13)
      val x4834 = x4832.>>>(-13)
      val x4835 = x4833.|(x4834)
      val x4836 = x4835.*(5)
      val x4837 = x4836.+(-430675100)
      x4823 = x4837
      val x4839 = x4822._2
      val x4840 = x4839.hashCode()
      val x4841 = -862048943.*(x4840)
      val x4842 = x4841.<<(15)
      val x4843 = x4841.>>>(-15)
      val x4844 = x4842.|(x4843)
      val x4845 = x4844.*(461845907)
      val x4846 = x4823
      val x4847 = x4845.^(x4846)
      val x4848 = x4847.<<(13)
      val x4849 = x4847.>>>(-13)
      val x4850 = x4848.|(x4849)
      val x4851 = x4850.*(5)
      val x4852 = x4851.+(-430675100)
      x4823 = x4852
      val x4854 = x4822._3
      val x4855 = x4854.hashCode()
      val x4856 = -862048943.*(x4855)
      val x4857 = x4856.<<(15)
      val x4858 = x4856.>>>(-15)
      val x4859 = x4857.|(x4858)
      val x4860 = x4859.*(461845907)
      val x4861 = x4823
      val x4862 = x4860.^(x4861)
      val x4863 = x4862.<<(13)
      val x4864 = x4862.>>>(-13)
      val x4865 = x4863.|(x4864)
      val x4866 = x4865.*(5)
      val x4867 = x4866.+(-430675100)
      x4823 = x4867
      val x4869 = x4823
      val x4870 = x4869.^(2)
      val x4871 = x4870.>>>(16)
      val x4872 = x4870.^(x4871)
      val x4873 = x4872.*(-2048144789)
      val x4874 = x4873.>>>(13)
      val x4875 = x4873.^(x4874)
      val x4876 = x4875.*(-1028477387)
      val x4877 = x4876.>>>(16)
      val x4878 = x4876.^(x4877)
      x4878
    }
    override def cmp(x4880 : SEntry10_IIIIIITIDS , x4881 : SEntry10_IIIIIITIDS) = {
      val x4882 = x4880._1
      val x4883 = x4881._1
      val x4884 = x4882.==(x4883)
      val x4888 = x4884.&&({
        val x4885 = x4880._2
        val x4886 = x4881._2
        val x4887 = x4885.==(x4886)
        x4887
      })
      val x4892 = x4888.&&({
        val x4889 = x4880._3
        val x4890 = x4881._3
        val x4891 = x4889.==(x4890)
        x4891
      })
      val x4893 = if(x4892) 0 else 1
      x4893
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4316 : SEntry3_III) = {
      var x4317: Int = -889275714
      val x4318 = x4316._2
      val x4319 = x4318.hashCode()
      val x4320 = -862048943.*(x4319)
      val x4321 = x4320.<<(15)
      val x4322 = x4320.>>>(-15)
      val x4323 = x4321.|(x4322)
      val x4324 = x4323.*(461845907)
      val x4325 = x4317
      val x4326 = x4324.^(x4325)
      val x4327 = x4326.<<(13)
      val x4328 = x4326.>>>(-13)
      val x4329 = x4327.|(x4328)
      val x4330 = x4329.*(5)
      val x4331 = x4330.+(-430675100)
      x4317 = x4331
      val x4333 = x4316._3
      val x4334 = x4333.hashCode()
      val x4335 = -862048943.*(x4334)
      val x4336 = x4335.<<(15)
      val x4337 = x4335.>>>(-15)
      val x4338 = x4336.|(x4337)
      val x4339 = x4338.*(461845907)
      val x4340 = x4317
      val x4341 = x4339.^(x4340)
      val x4342 = x4341.<<(13)
      val x4343 = x4341.>>>(-13)
      val x4344 = x4342.|(x4343)
      val x4345 = x4344.*(5)
      val x4346 = x4345.+(-430675100)
      x4317 = x4346
      val x4348 = x4317
      val x4349 = x4348.^(2)
      val x4350 = x4349.>>>(16)
      val x4351 = x4349.^(x4350)
      val x4352 = x4351.*(-2048144789)
      val x4353 = x4352.>>>(13)
      val x4354 = x4352.^(x4353)
      val x4355 = x4354.*(-1028477387)
      val x4356 = x4355.>>>(16)
      val x4357 = x4355.^(x4356)
      x4357
    }
    override def cmp(x4359 : SEntry3_III , x4360 : SEntry3_III) = {
      val x4361 = x4359._2
      val x4362 = x4360._2
      val x4363 = x4361.==(x4362)
      val x4367 = x4363.&&({
        val x4364 = x4359._3
        val x4365 = x4360._3
        val x4366 = x4364.==(x4365)
        x4366
      })
      val x4368 = if(x4367) 0 else 1
      x4368
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx12 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5054 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5055: Int = -889275714
      val x5056 = x5054._1
      val x5057 = x5056.hashCode()
      val x5058 = -862048943.*(x5057)
      val x5059 = x5058.<<(15)
      val x5060 = x5058.>>>(-15)
      val x5061 = x5059.|(x5060)
      val x5062 = x5061.*(461845907)
      val x5063 = x5055
      val x5064 = x5062.^(x5063)
      val x5065 = x5064.<<(13)
      val x5066 = x5064.>>>(-13)
      val x5067 = x5065.|(x5066)
      val x5068 = x5067.*(5)
      val x5069 = x5068.+(-430675100)
      x5055 = x5069
      val x5071 = x5054._2
      val x5072 = x5071.hashCode()
      val x5073 = -862048943.*(x5072)
      val x5074 = x5073.<<(15)
      val x5075 = x5073.>>>(-15)
      val x5076 = x5074.|(x5075)
      val x5077 = x5076.*(461845907)
      val x5078 = x5055
      val x5079 = x5077.^(x5078)
      val x5080 = x5079.<<(13)
      val x5081 = x5079.>>>(-13)
      val x5082 = x5080.|(x5081)
      val x5083 = x5082.*(5)
      val x5084 = x5083.+(-430675100)
      x5055 = x5084
      val x5086 = x5055
      val x5087 = x5086.^(2)
      val x5088 = x5087.>>>(16)
      val x5089 = x5087.^(x5088)
      val x5090 = x5089.*(-2048144789)
      val x5091 = x5090.>>>(13)
      val x5092 = x5090.^(x5091)
      val x5093 = x5092.*(-1028477387)
      val x5094 = x5093.>>>(16)
      val x5095 = x5093.^(x5094)
      x5095
    }
    override def cmp(x5097 : SEntry17_IIISSSSSSSSSSIIIS , x5098 : SEntry17_IIISSSSSSSSSSIIIS) = {
      val x5099 = x5097._1
      val x5100 = x5098._1
      val x5101 = x5099.==(x5100)
      val x5105 = x5101.&&({
        val x5102 = x5097._2
        val x5103 = x5098._2
        val x5104 = x5102.==(x5103)
        x5104
      })
      val x5106 = if(x5105) 0 else 1
      x5106
    }
  }
   object SEntry5_IISDS_Idx1 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4495 : SEntry5_IISDS) = {
      var x4496: Int = -889275714
      val x4497 = x4495._1
      val x4498 = x4497.hashCode()
      val x4499 = -862048943.*(x4498)
      val x4500 = x4499.<<(15)
      val x4501 = x4499.>>>(-15)
      val x4502 = x4500.|(x4501)
      val x4503 = x4502.*(461845907)
      val x4504 = x4496
      val x4505 = x4503.^(x4504)
      val x4506 = x4505.<<(13)
      val x4507 = x4505.>>>(-13)
      val x4508 = x4506.|(x4507)
      val x4509 = x4508.*(5)
      val x4510 = x4509.+(-430675100)
      x4496 = x4510
      val x4512 = x4496
      val x4513 = x4512.^(2)
      val x4514 = x4513.>>>(16)
      val x4515 = x4513.^(x4514)
      val x4516 = x4515.*(-2048144789)
      val x4517 = x4516.>>>(13)
      val x4518 = x4516.^(x4517)
      val x4519 = x4518.*(-1028477387)
      val x4520 = x4519.>>>(16)
      val x4521 = x4519.^(x4520)
      x4521
    }
    override def cmp(x4523 : SEntry5_IISDS , x4524 : SEntry5_IISDS) = {
      val x4525 = x4523._1
      val x4526 = x4524._1
      val x4527 = x4525.==(x4526)
      val x4528 = if(x4527) 0 else 1
      x4528
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4377 : SEntry8_IIIIITDS) = {
      var x4378: Int = -889275714
      val x4379 = x4378
      val x4380 = x4379.^(2)
      val x4381 = x4380.>>>(16)
      val x4382 = x4380.^(x4381)
      val x4383 = x4382.*(-2048144789)
      val x4384 = x4383.>>>(13)
      val x4385 = x4383.^(x4384)
      val x4386 = x4385.*(-1028477387)
      val x4387 = x4386.>>>(16)
      val x4388 = x4386.^(x4387)
      x4388
    }
    override def cmp(x4390 : SEntry8_IIIIITDS , x4391 : SEntry8_IIIIITDS) = {
      val x4392 = x4390._1
      val x4393 = x4391._1
      val x4394 = x4392.==(-1)
      val x4396 = x4394.||({
        val x4395 = x4393.==(-1)
        x4395
      })
      val x4398 = x4396.||({
        val x4397 = x4392.==(x4393)
        x4397
      })
      val x4406 = x4398.&&({
        val x4399 = x4390._2
        val x4400 = x4391._2
        val x4401 = x4399.==(-1)
        val x4403 = x4401.||({
          val x4402 = x4400.==(-1)
          x4402
        })
        val x4405 = x4403.||({
          val x4404 = x4399.==(x4400)
          x4404
        })
        x4405
      })
      val x4414 = x4406.&&({
        val x4407 = x4390._3
        val x4408 = x4391._3
        val x4409 = x4407.==(-1)
        val x4411 = x4409.||({
          val x4410 = x4408.==(-1)
          x4410
        })
        val x4413 = x4411.||({
          val x4412 = x4407.==(x4408)
          x4412
        })
        x4413
      })
      val x4422 = x4414.&&({
        val x4415 = x4390._4
        val x4416 = x4391._4
        val x4417 = x4415.==(-1)
        val x4419 = x4417.||({
          val x4418 = x4416.==(-1)
          x4418
        })
        val x4421 = x4419.||({
          val x4420 = x4415.==(x4416)
          x4420
        })
        x4421
      })
      val x4430 = x4422.&&({
        val x4423 = x4390._5
        val x4424 = x4391._5
        val x4425 = x4423.==(-1)
        val x4427 = x4425.||({
          val x4426 = x4424.==(-1)
          x4426
        })
        val x4429 = x4427.||({
          val x4428 = x4423.==(x4424)
          x4428
        })
        x4429
      })
      val x4438 = x4430.&&({
        val x4431 = x4390._6
        val x4432 = x4391._6
        val x4433 = x4431.==(null)
        val x4435 = x4433.||({
          val x4434 = x4432.==(null)
          x4434
        })
        val x4437 = x4435.||({
          val x4436 = x4431.==(x4432)
          x4436
        })
        x4437
      })
      val x4446 = x4438.&&({
        val x4439 = x4390._7
        val x4440 = x4391._7
        val x4441 = x4439.==(-1.0)
        val x4443 = x4441.||({
          val x4442 = x4440.==(-1.0)
          x4442
        })
        val x4445 = x4443.||({
          val x4444 = x4439.==(x4440)
          x4444
        })
        x4445
      })
      val x4447 = if(x4446) 0 else 1
      x4447
    }
  }
   object SEntry11_IISSSSSSDDI_Idx12 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4762 : SEntry11_IISSSSSSDDI) = {
      var x4763: Int = -889275714
      val x4764 = x4762._1
      val x4765 = x4764.hashCode()
      val x4766 = -862048943.*(x4765)
      val x4767 = x4766.<<(15)
      val x4768 = x4766.>>>(-15)
      val x4769 = x4767.|(x4768)
      val x4770 = x4769.*(461845907)
      val x4771 = x4763
      val x4772 = x4770.^(x4771)
      val x4773 = x4772.<<(13)
      val x4774 = x4772.>>>(-13)
      val x4775 = x4773.|(x4774)
      val x4776 = x4775.*(5)
      val x4777 = x4776.+(-430675100)
      x4763 = x4777
      val x4779 = x4762._2
      val x4780 = x4779.hashCode()
      val x4781 = -862048943.*(x4780)
      val x4782 = x4781.<<(15)
      val x4783 = x4781.>>>(-15)
      val x4784 = x4782.|(x4783)
      val x4785 = x4784.*(461845907)
      val x4786 = x4763
      val x4787 = x4785.^(x4786)
      val x4788 = x4787.<<(13)
      val x4789 = x4787.>>>(-13)
      val x4790 = x4788.|(x4789)
      val x4791 = x4790.*(5)
      val x4792 = x4791.+(-430675100)
      x4763 = x4792
      val x4794 = x4763
      val x4795 = x4794.^(2)
      val x4796 = x4795.>>>(16)
      val x4797 = x4795.^(x4796)
      val x4798 = x4797.*(-2048144789)
      val x4799 = x4798.>>>(13)
      val x4800 = x4798.^(x4799)
      val x4801 = x4800.*(-1028477387)
      val x4802 = x4801.>>>(16)
      val x4803 = x4801.^(x4802)
      x4803
    }
    override def cmp(x4805 : SEntry11_IISSSSSSDDI , x4806 : SEntry11_IISSSSSSDDI) = {
      val x4807 = x4805._1
      val x4808 = x4806._1
      val x4809 = x4807.==(x4808)
      val x4813 = x4809.&&({
        val x4810 = x4805._2
        val x4811 = x4806._2
        val x4812 = x4810.==(x4811)
        x4812
      })
      val x4814 = if(x4813) 0 else 1
      x4814
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4975 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4976: Int = -889275714
      val x4977 = x4975._2
      val x4978 = x4977.hashCode()
      val x4979 = -862048943.*(x4978)
      val x4980 = x4979.<<(15)
      val x4981 = x4979.>>>(-15)
      val x4982 = x4980.|(x4981)
      val x4983 = x4982.*(461845907)
      val x4984 = x4976
      val x4985 = x4983.^(x4984)
      val x4986 = x4985.<<(13)
      val x4987 = x4985.>>>(-13)
      val x4988 = x4986.|(x4987)
      val x4989 = x4988.*(5)
      val x4990 = x4989.+(-430675100)
      x4976 = x4990
      val x4992 = x4975._3
      val x4993 = x4992.hashCode()
      val x4994 = -862048943.*(x4993)
      val x4995 = x4994.<<(15)
      val x4996 = x4994.>>>(-15)
      val x4997 = x4995.|(x4996)
      val x4998 = x4997.*(461845907)
      val x4999 = x4976
      val x5000 = x4998.^(x4999)
      val x5001 = x5000.<<(13)
      val x5002 = x5000.>>>(-13)
      val x5003 = x5001.|(x5002)
      val x5004 = x5003.*(5)
      val x5005 = x5004.+(-430675100)
      x4976 = x5005
      val x5007 = x4975._6
      val x5008 = x5007.hashCode()
      val x5009 = -862048943.*(x5008)
      val x5010 = x5009.<<(15)
      val x5011 = x5009.>>>(-15)
      val x5012 = x5010.|(x5011)
      val x5013 = x5012.*(461845907)
      val x5014 = x4976
      val x5015 = x5013.^(x5014)
      val x5016 = x5015.<<(13)
      val x5017 = x5015.>>>(-13)
      val x5018 = x5016.|(x5017)
      val x5019 = x5018.*(5)
      val x5020 = x5019.+(-430675100)
      x4976 = x5020
      val x5022 = x4976
      val x5023 = x5022.^(2)
      val x5024 = x5023.>>>(16)
      val x5025 = x5023.^(x5024)
      val x5026 = x5025.*(-2048144789)
      val x5027 = x5026.>>>(13)
      val x5028 = x5026.^(x5027)
      val x5029 = x5028.*(-1028477387)
      val x5030 = x5029.>>>(16)
      val x5031 = x5029.^(x5030)
      x5031
    }
    override def cmp(x5033 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5034 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5035 = x5033._2
      val x5036 = x5034._2
      val x5037 = x5035.==(x5036)
      val x5041 = x5037.&&({
        val x5038 = x5033._3
        val x5039 = x5034._3
        val x5040 = x5038.==(x5039)
        x5040
      })
      val x5045 = x5041.&&({
        val x5042 = x5033._6
        val x5043 = x5034._6
        val x5044 = x5042.==(x5043)
        x5044
      })
      val x5046 = if(x5045) 0 else 1
      x5046
    }
  }
   object SEntry9_ISSSSSSDD_Idx1 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4455 : SEntry9_ISSSSSSDD) = {
      var x4456: Int = -889275714
      val x4457 = x4455._1
      val x4458 = x4457.hashCode()
      val x4459 = -862048943.*(x4458)
      val x4460 = x4459.<<(15)
      val x4461 = x4459.>>>(-15)
      val x4462 = x4460.|(x4461)
      val x4463 = x4462.*(461845907)
      val x4464 = x4456
      val x4465 = x4463.^(x4464)
      val x4466 = x4465.<<(13)
      val x4467 = x4465.>>>(-13)
      val x4468 = x4466.|(x4467)
      val x4469 = x4468.*(5)
      val x4470 = x4469.+(-430675100)
      x4456 = x4470
      val x4472 = x4456
      val x4473 = x4472.^(2)
      val x4474 = x4473.>>>(16)
      val x4475 = x4473.^(x4474)
      val x4476 = x4475.*(-2048144789)
      val x4477 = x4476.>>>(13)
      val x4478 = x4476.^(x4477)
      val x4479 = x4478.*(-1028477387)
      val x4480 = x4479.>>>(16)
      val x4481 = x4479.^(x4480)
      x4481
    }
    override def cmp(x4483 : SEntry9_ISSSSSSDD , x4484 : SEntry9_ISSSSSSDD) = {
      val x4485 = x4483._1
      val x4486 = x4484._1
      val x4487 = x4485.==(x4486)
      val x4488 = if(x4487) 0 else 1
      x4488
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4539 : SEntry8_IIIITIIB) = {
      var x4540: Int = -889275714
      val x4541 = x4539._1
      val x4542 = x4541.hashCode()
      val x4543 = -862048943.*(x4542)
      val x4544 = x4543.<<(15)
      val x4545 = x4543.>>>(-15)
      val x4546 = x4544.|(x4545)
      val x4547 = x4546.*(461845907)
      val x4548 = x4540
      val x4549 = x4547.^(x4548)
      val x4550 = x4549.<<(13)
      val x4551 = x4549.>>>(-13)
      val x4552 = x4550.|(x4551)
      val x4553 = x4552.*(5)
      val x4554 = x4553.+(-430675100)
      x4540 = x4554
      val x4556 = x4539._2
      val x4557 = x4556.hashCode()
      val x4558 = -862048943.*(x4557)
      val x4559 = x4558.<<(15)
      val x4560 = x4558.>>>(-15)
      val x4561 = x4559.|(x4560)
      val x4562 = x4561.*(461845907)
      val x4563 = x4540
      val x4564 = x4562.^(x4563)
      val x4565 = x4564.<<(13)
      val x4566 = x4564.>>>(-13)
      val x4567 = x4565.|(x4566)
      val x4568 = x4567.*(5)
      val x4569 = x4568.+(-430675100)
      x4540 = x4569
      val x4571 = x4539._3
      val x4572 = x4571.hashCode()
      val x4573 = -862048943.*(x4572)
      val x4574 = x4573.<<(15)
      val x4575 = x4573.>>>(-15)
      val x4576 = x4574.|(x4575)
      val x4577 = x4576.*(461845907)
      val x4578 = x4540
      val x4579 = x4577.^(x4578)
      val x4580 = x4579.<<(13)
      val x4581 = x4579.>>>(-13)
      val x4582 = x4580.|(x4581)
      val x4583 = x4582.*(5)
      val x4584 = x4583.+(-430675100)
      x4540 = x4584
      val x4586 = x4540
      val x4587 = x4586.^(2)
      val x4588 = x4587.>>>(16)
      val x4589 = x4587.^(x4588)
      val x4590 = x4589.*(-2048144789)
      val x4591 = x4590.>>>(13)
      val x4592 = x4590.^(x4591)
      val x4593 = x4592.*(-1028477387)
      val x4594 = x4593.>>>(16)
      val x4595 = x4593.^(x4594)
      x4595
    }
    override def cmp(x4597 : SEntry8_IIIITIIB , x4598 : SEntry8_IIIITIIB) = {
      val x4599 = x4597._1
      val x4600 = x4598._1
      val x4601 = x4599.==(x4600)
      val x4605 = x4601.&&({
        val x4602 = x4597._2
        val x4603 = x4598._2
        val x4604 = x4602.==(x4603)
        x4604
      })
      val x4609 = x4605.&&({
        val x4606 = x4597._3
        val x4607 = x4598._3
        val x4608 = x4606.==(x4607)
        x4608
      })
      val x4610 = if(x4609) 0 else 1
      x4610
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4263 : SEntry3_III) = {
      var x4264: Int = -889275714
      val x4265 = x4263._2
      val x4266 = x4265.hashCode()
      val x4267 = -862048943.*(x4266)
      val x4268 = x4267.<<(15)
      val x4269 = x4267.>>>(-15)
      val x4270 = x4268.|(x4269)
      val x4271 = x4270.*(461845907)
      val x4272 = x4264
      val x4273 = x4271.^(x4272)
      val x4274 = x4273.<<(13)
      val x4275 = x4273.>>>(-13)
      val x4276 = x4274.|(x4275)
      val x4277 = x4276.*(5)
      val x4278 = x4277.+(-430675100)
      x4264 = x4278
      val x4280 = x4263._3
      val x4281 = x4280.hashCode()
      val x4282 = -862048943.*(x4281)
      val x4283 = x4282.<<(15)
      val x4284 = x4282.>>>(-15)
      val x4285 = x4283.|(x4284)
      val x4286 = x4285.*(461845907)
      val x4287 = x4264
      val x4288 = x4286.^(x4287)
      val x4289 = x4288.<<(13)
      val x4290 = x4288.>>>(-13)
      val x4291 = x4289.|(x4290)
      val x4292 = x4291.*(5)
      val x4293 = x4292.+(-430675100)
      x4264 = x4293
      val x4295 = x4264
      val x4296 = x4295.^(2)
      val x4297 = x4296.>>>(16)
      val x4298 = x4296.^(x4297)
      val x4299 = x4298.*(-2048144789)
      val x4300 = x4299.>>>(13)
      val x4301 = x4299.^(x4300)
      val x4302 = x4301.*(-1028477387)
      val x4303 = x4302.>>>(16)
      val x4304 = x4302.^(x4303)
      x4304
    }
    override def cmp(x4306 : SEntry3_III , x4307 : SEntry3_III) = {
      val x4308 = x914.apply(x4306)
      val x4309 = x914.apply(x4307)
      val x4310 = x4308.==(x4309)
      val x4311 = x4308.>(x4309)
      val x4312 = if(x4311) 
      {
        1
      }
      else
      {
        -1
      }
      
      val x4313 = if(x4310) 0 else x4312
      x4313
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4613 : SEntry8_IIIITIIB) = {
      var x4614: Int = -889275714
      val x4615 = x4613._2
      val x4616 = x4615.hashCode()
      val x4617 = -862048943.*(x4616)
      val x4618 = x4617.<<(15)
      val x4619 = x4617.>>>(-15)
      val x4620 = x4618.|(x4619)
      val x4621 = x4620.*(461845907)
      val x4622 = x4614
      val x4623 = x4621.^(x4622)
      val x4624 = x4623.<<(13)
      val x4625 = x4623.>>>(-13)
      val x4626 = x4624.|(x4625)
      val x4627 = x4626.*(5)
      val x4628 = x4627.+(-430675100)
      x4614 = x4628
      val x4630 = x4613._3
      val x4631 = x4630.hashCode()
      val x4632 = -862048943.*(x4631)
      val x4633 = x4632.<<(15)
      val x4634 = x4632.>>>(-15)
      val x4635 = x4633.|(x4634)
      val x4636 = x4635.*(461845907)
      val x4637 = x4614
      val x4638 = x4636.^(x4637)
      val x4639 = x4638.<<(13)
      val x4640 = x4638.>>>(-13)
      val x4641 = x4639.|(x4640)
      val x4642 = x4641.*(5)
      val x4643 = x4642.+(-430675100)
      x4614 = x4643
      val x4645 = x4613._4
      val x4646 = x4645.hashCode()
      val x4647 = -862048943.*(x4646)
      val x4648 = x4647.<<(15)
      val x4649 = x4647.>>>(-15)
      val x4650 = x4648.|(x4649)
      val x4651 = x4650.*(461845907)
      val x4652 = x4614
      val x4653 = x4651.^(x4652)
      val x4654 = x4653.<<(13)
      val x4655 = x4653.>>>(-13)
      val x4656 = x4654.|(x4655)
      val x4657 = x4656.*(5)
      val x4658 = x4657.+(-430675100)
      x4614 = x4658
      val x4660 = x4614
      val x4661 = x4660.^(2)
      val x4662 = x4661.>>>(16)
      val x4663 = x4661.^(x4662)
      val x4664 = x4663.*(-2048144789)
      val x4665 = x4664.>>>(13)
      val x4666 = x4664.^(x4665)
      val x4667 = x4666.*(-1028477387)
      val x4668 = x4667.>>>(16)
      val x4669 = x4667.^(x4668)
      x4669
    }
    override def cmp(x4671 : SEntry8_IIIITIIB , x4672 : SEntry8_IIIITIIB) = {
      val x4673 = x936.apply(x4671)
      val x4674 = x936.apply(x4672)
      val x4675 = x4673.==(x4674)
      val x4676 = x4673.>(x4674)
      val x4677 = if(x4676) 
      {
        1
      }
      else
      {
        -1
      }
      
      val x4678 = if(x4675) 0 else x4677
      x4678
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
        val x17 = x16.<=(10)
        x17
      })
      {
        val x22 = x15
        x7678._2_=(x22)
        x7678._3_=(x12)
        val x12631 = x920.get(x7678)
        val x27 = x12631.!=(null)
        if(x27) 
        {
          val x7683 = x12631._1
          val x29 = x15
          val x30 = x29.-(1)
          x14.update(x30, x7683)
          x920.delete(x12631)
          val x33 = x15
          x7689._1_=(x7683)
          x7689._2_=(x33)
          x7689._3_=(x12)
          val x12644 = x942.get(x7689)
          val x7692 = x12644._4
          x12644._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x7698._1_=(x7683)
          x7698._2_=(x41)
          x7698._3_=(x12)
          val x51 = { x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x7800 = x44._9
              val x48 = x46.+(x7800)
              x40 = x48
              ()
            }
          }
          x953.slice(x7698, x51)
          val x53 = x15
          x7702._1_=(x7692)
          x7702._2_=(x53)
          x7702._3_=(x12)
          val x12665 = x958.get(x7702)
          val x56 = x40
          x12665._17 +=(x56)
          x12665._20 +=(1)
          ()
        }
        else
        {
          val x60 = x15
          val x61 = x60.-(1)
          x14.update(x61, 0)
          ()
        }
        
        val x64 = x15
        val x65 = x64.+(1)
        x15 = x65
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
          val x78 = x77.<=(10)
          x78
        })
        {
          val x79 = x76
          val x80 = x79.-(1)
          val x81 = x14.apply(x80)
          val x82 = x81.>=(0)
          if(x82) 
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
            x74 = x96
            ()
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
            x74 = x106
            val x108 = x75
            val x109 = x108.+(1)
            x75 = x109
            ()
          }
          
          val x112 = x76
          val x113 = x112.+(1)
          x76 = x113
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
      val x12840 = x949.get(x7976)
      val x7979 = x12840._11
      val x132 = x7979.-(20)
      var x133: Int = x132
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        val x136 = x135.<(x7979)
        x136
      })
      {
        val x137 = x133
        x7988._1_=(x137)
        x7988._2_=(x126)
        x7988._3_=(x125)
        val x148 = { x140: SEntry10_IIIIIITIDS => {
            val x8020 = x140._5
            x8021._1_=(x8020)
            x8021._2_=(x125)
            val x12858 = x962.get(x8021)
            val x8023 = x12858._3
            val x145 = x8023.<(x127)
            if(x145) 
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
        }
        x953.slice(x7988, x148)
        val x150 = x133
        val x151 = x150.+(1)
        x133 = x151
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
      val x174 = x170.>(0)
      if(x174) 
      {
        val x8082 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8084._2_=(x169)
        x8084._3_=(x168)
        x8084._6_=(x172)
        val x180 = { x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8082.append(x178)
            ()
          }
        }
        x959.slice(x8084, x180)
        val x182 = x8082.size
        val x183 = x182./(2)
        var x184: Int = x183
        val x185 = x8082.size
        val x186 = x185.%(2)
        val x187 = x186.==(0)
        if(x187) 
        {
          val x188 = x184
          val x189 = x188.-(1)
          x184 = x189
          ()
        }
        else
        {
          ()
        }
        
        val x198 = { (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8134 = x192._4
            val x8135 = x193._4
            val x196 = x8134.compareToIgnoreCase(x8135)
            val x197 = x196.<(0)
            x197
          }
        }
        val x199 = x8082.sortWith(x198)
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
        val x12956 = x958.get(x8102)
        x8079 = x12956
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
      val x13009 = x931.get(x8191)
      x13009._9 +=(x229)
      x8196._1_=(x223)
      x8196._2_=(x222)
      val x13014 = x949.get(x8196)
      x13014._10 +=(x229)
      var x8201: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      val x241 = x224.>(0)
      if(x241) 
      {
        val x8204 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x8206._2_=(x226)
        x8206._3_=(x225)
        x8206._6_=(x228)
        val x247 = { x245: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8204.append(x245)
            ()
          }
        }
        x959.slice(x8206, x247)
        val x249 = x8204.size
        val x250 = x249./(2)
        var x251: Int = x250
        val x252 = x8204.size
        val x253 = x252.%(2)
        val x254 = x253.==(0)
        if(x254) 
        {
          val x255 = x251
          val x256 = x255.-(1)
          x251 = x256
          ()
        }
        else
        {
          ()
        }
        
        val x265 = { (x259: SEntry21_IIISSSSSSSSSTSDDDDIIS, x260: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8307 = x259._4
            val x8308 = x260._4
            val x263 = x8307.compareToIgnoreCase(x8308)
            val x264 = x263.<(0)
            x264
          }
        }
        val x266 = x8204.sortWith(x265)
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
        val x13053 = x958.get(x8224)
        x8201 = x13053
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
        val x289 = x288.>(500)
        if(x289) 
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
      val x8257 = x13009._2
      val x8258 = x13014._3
      val x306 = x8257.length
      val x307 = x306.>(10)
      val x309 = if(x307) 
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
      val x312 = x311.>(10)
      val x314 = if(x312) 
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
      val x8272 = SEntry8_IIIIITDS(x8270, x226, x225, x223, x222, x220, x229, x315)
      x4452.insert(x8272)
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
        x8471._1_=(x350)
        val x13214 = x934.get(x8471)
        val x354 = x13214.==(null)
        if(x354) 
        {
          x344 = false
          ()
        }
        else
        {
          val x356 = x341
          val x8478 = x13214._3
          x333.update(x356, x8478)
          val x359 = x341
          val x8481 = x13214._4
          x332.update(x359, x8481)
          val x362 = x341
          val x8484 = x13214._5
          x343.update(x362, x8484)
          ()
        }
        
        val x366 = x341
        val x367 = x366.+(1)
        x341 = x367
        ()
      }
      val x370 = x344
      if(x370) 
      {
        x8491._1_=(x326)
        x8491._2_=(x325)
        x8491._3_=(x324)
        val x13236 = x958.get(x8491)
        x8494._1_=(x324)
        val x13239 = x931.get(x8494)
        x8497._1_=(x325)
        x8497._2_=(x324)
        val x13243 = x949.get(x8497)
        val x8500 = x13243._11
        x13243._11 +=(1)
        val x383 = x328.>(0)
        val x8505 = SEntry8_IIIITIIB(x8500, x325, x324, x326, x322, -1, x327, x383)
        x4757.insert(x8505)
        val x8508 = SEntry3_III(x8500, x325, x324)
        x4373.insert(x8508)
        var x390: Double = 0.0
        x341 = 0
        while({
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
          x8521._1_=(x397)
          x8521._2_=(x395)
          val x13266 = x962.get(x8521)
          val x402 = x325.==(1)
          val x429 = if(x402) 
          {
            val x8525 = x13266._4
            x8525
          }
          else
          {
            val x404 = x325.==(2)
            val x428 = if(x404) 
            {
              val x8528 = x13266._5
              x8528
            }
            else
            {
              val x406 = x325.==(3)
              val x427 = if(x406) 
              {
                val x8531 = x13266._6
                x8531
              }
              else
              {
                val x408 = x325.==(4)
                val x426 = if(x408) 
                {
                  val x8534 = x13266._7
                  x8534
                }
                else
                {
                  val x410 = x325.==(5)
                  val x425 = if(x410) 
                  {
                    val x8537 = x13266._8
                    x8537
                  }
                  else
                  {
                    val x412 = x325.==(6)
                    val x424 = if(x412) 
                    {
                      val x8540 = x13266._9
                      x8540
                    }
                    else
                    {
                      val x414 = x325.==(7)
                      val x423 = if(x414) 
                      {
                        val x8543 = x13266._10
                        x8543
                      }
                      else
                      {
                        val x416 = x325.==(8)
                        val x422 = if(x416) 
                        {
                          val x8546 = x13266._11
                          x8546
                        }
                        else
                        {
                          val x418 = x325.==(9)
                          val x421 = if(x418) 
                          {
                            val x8549 = x13266._12
                            x8549
                          }
                          else
                          {
                            val x8550 = x13266._13
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
          
          val x8551 = x13266._3
          val x431 = x341
          x334.update(x431, x8551)
          val x8554 = x13236._14
          val x434 = x8554.contains("original")
          val x437 = x434.&&({
            val x8557 = x13266._17
            val x436 = x8557.contains("original")
            x436
          })
          if(x437) 
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
          
          val x443 = x8551.-(x399)
          x13266._3_=(x443)
          val x445 = x8551.<=(x399)
          if(x445) 
          {
            x13266._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x448: Int = 0
          val x449 = x395.!=(x324)
          if(x449) 
          {
            x448 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8574 = x13236._16
          val x8575 = x13239._8
          val x8576 = x13243._9
          val x456 = x341
          val x457 = x332.apply(x456)
          val x458 = x399.toDouble
          val x459 = x458.*(x457)
          val x460 = 1.0.+(x8575)
          val x461 = x460.+(x8576)
          val x462 = x459.*(x461)
          val x463 = 1.0.-(x8574)
          val x464 = x462.*(x463)
          val x465 = x341
          x336.update(x465, x464)
          val x467 = x390
          val x468 = x467.+(x464)
          x390 = x468
          val x470 = x341
          val x471 = x470.+(1)
          val x8594 = SEntry10_IIIIIITIDS(x8500, x325, x324, x471, x397, x395, null, x399, x464, x429)
          x4898.insert(x8594)
          val x475 = x341
          val x476 = x475.+(1)
          x341 = x476
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
