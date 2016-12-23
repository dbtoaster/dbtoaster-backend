
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
  val x4360 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x4361 = new Store[SEntry3_III](3, x4360);
  val x943 = x4361.index(0, IHash, true, -1)
  val x944 = x4361.index(1, ISliceHeapMin, false, 2)
  val x945 = x4361.index(2, INone, false, -1)
  val x4560 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4561 = new Store[SEntry8_IIIIITDS](1, x4560);
  val x950 = x4561.index(0, IList, false, -1)
  val x4579 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x4580 = new Store[SEntry9_ISSSSSSDD](1, x4579);
  val x955 = x4580.index(0, IDirect, true, 1)
  val x4598 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x4599 = new Store[SEntry5_IISDS](1, x4598);
  val x960 = x4599.index(0, IDirect, true, 100000)
  val x4822 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4823 = new Store[SEntry8_IIIITIIB](3, x4822);
  val x967 = x4823.index(0, IHash, true, -1)
  val x968 = x4823.index(1, ISliceHeapMax, false, 2)
  val x969 = x4823.index(2, INone, false, -1)
  val x4849 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4850 = new Store[SEntry11_IISSSSSSDDI](1, x4849);
  val x974 = x4850.index(0, IDirect, true, 10)
  val x5021 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x5022 = new Store[SEntry10_IIIIIITIDS](2, x5021);
  val x979 = x5022.index(0, IHash, true, -1)
  val x980 = x5022.index(1, IHash, false, -1)
  val x5127 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x5128 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x5127);
  val x986 = x5128.index(0, IDirect, true, 30000)
  val x987 = x5128.index(1, IHash, false, -1)
  val x5153 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x5154 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x5153);
  val x992 = x5154.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x4361
  val historyTbl = x4561
  val warehouseTbl = x4580
  val itemTbl = x4599
  val orderTbl = x4823
  val districtTbl = x4850
  val orderLineTbl = x5022
  val customerTbl = x5128
  val stockTbl = x5154
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4853 : SEntry10_IIIIIITIDS) = {
      var x4854: Int = -889275714;
      val x4855 = x4853._1;
      val x4856 = x4855.hashCode();
      val x4857 = -862048943.*(x4856);
      val x4858 = x4857.<<(15);
      val x4859 = x4857.>>>(-15);
      val x4860 = x4858.|(x4859);
      val x4861 = x4860.*(461845907);
      val x4862 = x4854;
      val x4863 = x4861.^(x4862);
      val x4864 = x4863.<<(13);
      val x4865 = x4863.>>>(-13);
      val x4866 = x4864.|(x4865);
      val x4867 = x4866.*(5);
      val x4868 = x4867.+(-430675100);
      x4854 = x4868
      val x4870 = x4853._2;
      val x4871 = x4870.hashCode();
      val x4872 = -862048943.*(x4871);
      val x4873 = x4872.<<(15);
      val x4874 = x4872.>>>(-15);
      val x4875 = x4873.|(x4874);
      val x4876 = x4875.*(461845907);
      val x4877 = x4854;
      val x4878 = x4876.^(x4877);
      val x4879 = x4878.<<(13);
      val x4880 = x4878.>>>(-13);
      val x4881 = x4879.|(x4880);
      val x4882 = x4881.*(5);
      val x4883 = x4882.+(-430675100);
      x4854 = x4883
      val x4885 = x4853._3;
      val x4886 = x4885.hashCode();
      val x4887 = -862048943.*(x4886);
      val x4888 = x4887.<<(15);
      val x4889 = x4887.>>>(-15);
      val x4890 = x4888.|(x4889);
      val x4891 = x4890.*(461845907);
      val x4892 = x4854;
      val x4893 = x4891.^(x4892);
      val x4894 = x4893.<<(13);
      val x4895 = x4893.>>>(-13);
      val x4896 = x4894.|(x4895);
      val x4897 = x4896.*(5);
      val x4898 = x4897.+(-430675100);
      x4854 = x4898
      val x4900 = x4853._4;
      val x4901 = x4900.hashCode();
      val x4902 = -862048943.*(x4901);
      val x4903 = x4902.<<(15);
      val x4904 = x4902.>>>(-15);
      val x4905 = x4903.|(x4904);
      val x4906 = x4905.*(461845907);
      val x4907 = x4854;
      val x4908 = x4906.^(x4907);
      val x4909 = x4908.<<(13);
      val x4910 = x4908.>>>(-13);
      val x4911 = x4909.|(x4910);
      val x4912 = x4911.*(5);
      val x4913 = x4912.+(-430675100);
      x4854 = x4913
      val x4915 = x4854;
      val x4916 = x4915.^(2);
      val x4917 = x4916.>>>(16);
      val x4918 = x4916.^(x4917);
      val x4919 = x4918.*(-2048144789);
      val x4920 = x4919.>>>(13);
      val x4921 = x4919.^(x4920);
      val x4922 = x4921.*(-1028477387);
      val x4923 = x4922.>>>(16);
      val x4924 = x4922.^(x4923);
      x4924
    }
    override def cmp(x4926 : SEntry10_IIIIIITIDS , x4927 : SEntry10_IIIIIITIDS) = {
      val x4928 = x4926._1;
      val x4929 = x4927._1;
      val x4930 = x4928.==(x4929);
      val x4934 = x4930.&&({
        val x4931 = x4926._2;
        val x4932 = x4927._2;
        val x4933 = x4931.==(x4932);
        x4933
      });
      val x4938 = x4934.&&({
        val x4935 = x4926._3;
        val x4936 = x4927._3;
        val x4937 = x4935.==(x4936);
        x4937
      });
      val x4942 = x4938.&&({
        val x4939 = x4926._4;
        val x4940 = x4927._4;
        val x4941 = x4939.==(x4940);
        x4941
      });
      val x4943 = if(x4942) 0 else 1;
      x4943
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4747 : SEntry8_IIIITIIB) = {
      var x4748: Int = -889275714;
      val x4749 = x4747._2;
      val x4750 = x4749.hashCode();
      val x4751 = -862048943.*(x4750);
      val x4752 = x4751.<<(15);
      val x4753 = x4751.>>>(-15);
      val x4754 = x4752.|(x4753);
      val x4755 = x4754.*(461845907);
      val x4756 = x4748;
      val x4757 = x4755.^(x4756);
      val x4758 = x4757.<<(13);
      val x4759 = x4757.>>>(-13);
      val x4760 = x4758.|(x4759);
      val x4761 = x4760.*(5);
      val x4762 = x4761.+(-430675100);
      x4748 = x4762
      val x4764 = x4747._3;
      val x4765 = x4764.hashCode();
      val x4766 = -862048943.*(x4765);
      val x4767 = x4766.<<(15);
      val x4768 = x4766.>>>(-15);
      val x4769 = x4767.|(x4768);
      val x4770 = x4769.*(461845907);
      val x4771 = x4748;
      val x4772 = x4770.^(x4771);
      val x4773 = x4772.<<(13);
      val x4774 = x4772.>>>(-13);
      val x4775 = x4773.|(x4774);
      val x4776 = x4775.*(5);
      val x4777 = x4776.+(-430675100);
      x4748 = x4777
      val x4779 = x4747._4;
      val x4780 = x4779.hashCode();
      val x4781 = -862048943.*(x4780);
      val x4782 = x4781.<<(15);
      val x4783 = x4781.>>>(-15);
      val x4784 = x4782.|(x4783);
      val x4785 = x4784.*(461845907);
      val x4786 = x4748;
      val x4787 = x4785.^(x4786);
      val x4788 = x4787.<<(13);
      val x4789 = x4787.>>>(-13);
      val x4790 = x4788.|(x4789);
      val x4791 = x4790.*(5);
      val x4792 = x4791.+(-430675100);
      x4748 = x4792
      val x4794 = x4748;
      val x4795 = x4794.^(2);
      val x4796 = x4795.>>>(16);
      val x4797 = x4795.^(x4796);
      val x4798 = x4797.*(-2048144789);
      val x4799 = x4798.>>>(13);
      val x4800 = x4798.^(x4799);
      val x4801 = x4800.*(-1028477387);
      val x4802 = x4801.>>>(16);
      val x4803 = x4801.^(x4802);
      x4803
    }
    override def cmp(x4805 : SEntry8_IIIITIIB , x4806 : SEntry8_IIIITIIB) = {
      val x4807 = x4805._2;
      val x4808 = x4806._2;
      val x4809 = x4807.==(x4808);
      val x4813 = x4809.&&({
        val x4810 = x4805._3;
        val x4811 = x4806._3;
        val x4812 = x4810.==(x4811);
        x4812
      });
      val x4817 = x4813.&&({
        val x4814 = x4805._4;
        val x4815 = x4806._4;
        val x4816 = x4814.==(x4815);
        x4816
      });
      val x4818 = if(x4817) 0 else 1;
      x4818
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x4177 : SEntry3_III) = {
      var x4178: Int = -889275714;
      val x4179 = x4177._1;
      val x4180 = x4179.hashCode();
      val x4181 = -862048943.*(x4180);
      val x4182 = x4181.<<(15);
      val x4183 = x4181.>>>(-15);
      val x4184 = x4182.|(x4183);
      val x4185 = x4184.*(461845907);
      val x4186 = x4178;
      val x4187 = x4185.^(x4186);
      val x4188 = x4187.<<(13);
      val x4189 = x4187.>>>(-13);
      val x4190 = x4188.|(x4189);
      val x4191 = x4190.*(5);
      val x4192 = x4191.+(-430675100);
      x4178 = x4192
      val x4194 = x4177._2;
      val x4195 = x4194.hashCode();
      val x4196 = -862048943.*(x4195);
      val x4197 = x4196.<<(15);
      val x4198 = x4196.>>>(-15);
      val x4199 = x4197.|(x4198);
      val x4200 = x4199.*(461845907);
      val x4201 = x4178;
      val x4202 = x4200.^(x4201);
      val x4203 = x4202.<<(13);
      val x4204 = x4202.>>>(-13);
      val x4205 = x4203.|(x4204);
      val x4206 = x4205.*(5);
      val x4207 = x4206.+(-430675100);
      x4178 = x4207
      val x4209 = x4177._3;
      val x4210 = x4209.hashCode();
      val x4211 = -862048943.*(x4210);
      val x4212 = x4211.<<(15);
      val x4213 = x4211.>>>(-15);
      val x4214 = x4212.|(x4213);
      val x4215 = x4214.*(461845907);
      val x4216 = x4178;
      val x4217 = x4215.^(x4216);
      val x4218 = x4217.<<(13);
      val x4219 = x4217.>>>(-13);
      val x4220 = x4218.|(x4219);
      val x4221 = x4220.*(5);
      val x4222 = x4221.+(-430675100);
      x4178 = x4222
      val x4224 = x4178;
      val x4225 = x4224.^(2);
      val x4226 = x4225.>>>(16);
      val x4227 = x4225.^(x4226);
      val x4228 = x4227.*(-2048144789);
      val x4229 = x4228.>>>(13);
      val x4230 = x4228.^(x4229);
      val x4231 = x4230.*(-1028477387);
      val x4232 = x4231.>>>(16);
      val x4233 = x4231.^(x4232);
      x4233
    }
    override def cmp(x4235 : SEntry3_III , x4236 : SEntry3_III) = {
      val x4237 = x4235._1;
      val x4238 = x4236._1;
      val x4239 = x4237.==(x4238);
      val x4243 = x4239.&&({
        val x4240 = x4235._2;
        val x4241 = x4236._2;
        val x4242 = x4240.==(x4241);
        x4242
      });
      val x4247 = x4243.&&({
        val x4244 = x4235._3;
        val x4245 = x4236._3;
        val x4246 = x4244.==(x4245);
        x4246
      });
      val x4248 = if(x4247) 0 else 1;
      x4248
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4946 : SEntry10_IIIIIITIDS) = {
      var x4947: Int = -889275714;
      val x4948 = x4946._1;
      val x4949 = x4948.hashCode();
      val x4950 = -862048943.*(x4949);
      val x4951 = x4950.<<(15);
      val x4952 = x4950.>>>(-15);
      val x4953 = x4951.|(x4952);
      val x4954 = x4953.*(461845907);
      val x4955 = x4947;
      val x4956 = x4954.^(x4955);
      val x4957 = x4956.<<(13);
      val x4958 = x4956.>>>(-13);
      val x4959 = x4957.|(x4958);
      val x4960 = x4959.*(5);
      val x4961 = x4960.+(-430675100);
      x4947 = x4961
      val x4963 = x4946._2;
      val x4964 = x4963.hashCode();
      val x4965 = -862048943.*(x4964);
      val x4966 = x4965.<<(15);
      val x4967 = x4965.>>>(-15);
      val x4968 = x4966.|(x4967);
      val x4969 = x4968.*(461845907);
      val x4970 = x4947;
      val x4971 = x4969.^(x4970);
      val x4972 = x4971.<<(13);
      val x4973 = x4971.>>>(-13);
      val x4974 = x4972.|(x4973);
      val x4975 = x4974.*(5);
      val x4976 = x4975.+(-430675100);
      x4947 = x4976
      val x4978 = x4946._3;
      val x4979 = x4978.hashCode();
      val x4980 = -862048943.*(x4979);
      val x4981 = x4980.<<(15);
      val x4982 = x4980.>>>(-15);
      val x4983 = x4981.|(x4982);
      val x4984 = x4983.*(461845907);
      val x4985 = x4947;
      val x4986 = x4984.^(x4985);
      val x4987 = x4986.<<(13);
      val x4988 = x4986.>>>(-13);
      val x4989 = x4987.|(x4988);
      val x4990 = x4989.*(5);
      val x4991 = x4990.+(-430675100);
      x4947 = x4991
      val x4993 = x4947;
      val x4994 = x4993.^(2);
      val x4995 = x4994.>>>(16);
      val x4996 = x4994.^(x4995);
      val x4997 = x4996.*(-2048144789);
      val x4998 = x4997.>>>(13);
      val x4999 = x4997.^(x4998);
      val x5000 = x4999.*(-1028477387);
      val x5001 = x5000.>>>(16);
      val x5002 = x5000.^(x5001);
      x5002
    }
    override def cmp(x5004 : SEntry10_IIIIIITIDS , x5005 : SEntry10_IIIIIITIDS) = {
      val x5006 = x5004._1;
      val x5007 = x5005._1;
      val x5008 = x5006.==(x5007);
      val x5012 = x5008.&&({
        val x5009 = x5004._2;
        val x5010 = x5005._2;
        val x5011 = x5009.==(x5010);
        x5011
      });
      val x5016 = x5012.&&({
        val x5013 = x5004._3;
        val x5014 = x5005._3;
        val x5015 = x5013.==(x5014);
        x5015
      });
      val x5017 = if(x5016) 0 else 1;
      x5017
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x4304 : SEntry3_III) = {
      var x4305: Int = -889275714;
      val x4306 = x4304._2;
      val x4307 = x4306.hashCode();
      val x4308 = -862048943.*(x4307);
      val x4309 = x4308.<<(15);
      val x4310 = x4308.>>>(-15);
      val x4311 = x4309.|(x4310);
      val x4312 = x4311.*(461845907);
      val x4313 = x4305;
      val x4314 = x4312.^(x4313);
      val x4315 = x4314.<<(13);
      val x4316 = x4314.>>>(-13);
      val x4317 = x4315.|(x4316);
      val x4318 = x4317.*(5);
      val x4319 = x4318.+(-430675100);
      x4305 = x4319
      val x4321 = x4304._3;
      val x4322 = x4321.hashCode();
      val x4323 = -862048943.*(x4322);
      val x4324 = x4323.<<(15);
      val x4325 = x4323.>>>(-15);
      val x4326 = x4324.|(x4325);
      val x4327 = x4326.*(461845907);
      val x4328 = x4305;
      val x4329 = x4327.^(x4328);
      val x4330 = x4329.<<(13);
      val x4331 = x4329.>>>(-13);
      val x4332 = x4330.|(x4331);
      val x4333 = x4332.*(5);
      val x4334 = x4333.+(-430675100);
      x4305 = x4334
      val x4336 = x4305;
      val x4337 = x4336.^(2);
      val x4338 = x4337.>>>(16);
      val x4339 = x4337.^(x4338);
      val x4340 = x4339.*(-2048144789);
      val x4341 = x4340.>>>(13);
      val x4342 = x4340.^(x4341);
      val x4343 = x4342.*(-1028477387);
      val x4344 = x4343.>>>(16);
      val x4345 = x4343.^(x4344);
      x4345
    }
    override def cmp(x4347 : SEntry3_III , x4348 : SEntry3_III) = {
      val x4349 = x4347._2;
      val x4350 = x4348._2;
      val x4351 = x4349.==(x4350);
      val x4355 = x4351.&&({
        val x4352 = x4347._3;
        val x4353 = x4348._3;
        val x4354 = x4352.==(x4353);
        x4354
      });
      val x4356 = if(x4355) 0 else 1;
      x4356
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x4366 : SEntry8_IIIIITDS) = {
      var x4367: Int = -889275714;
      val x4368 = x4366._1;
      val x4369 = x4368.hashCode();
      val x4370 = -862048943.*(x4369);
      val x4371 = x4370.<<(15);
      val x4372 = x4370.>>>(-15);
      val x4373 = x4371.|(x4372);
      val x4374 = x4373.*(461845907);
      val x4375 = x4367;
      val x4376 = x4374.^(x4375);
      val x4377 = x4376.<<(13);
      val x4378 = x4376.>>>(-13);
      val x4379 = x4377.|(x4378);
      val x4380 = x4379.*(5);
      val x4381 = x4380.+(-430675100);
      x4367 = x4381
      val x4383 = x4366._2;
      val x4384 = x4383.hashCode();
      val x4385 = -862048943.*(x4384);
      val x4386 = x4385.<<(15);
      val x4387 = x4385.>>>(-15);
      val x4388 = x4386.|(x4387);
      val x4389 = x4388.*(461845907);
      val x4390 = x4367;
      val x4391 = x4389.^(x4390);
      val x4392 = x4391.<<(13);
      val x4393 = x4391.>>>(-13);
      val x4394 = x4392.|(x4393);
      val x4395 = x4394.*(5);
      val x4396 = x4395.+(-430675100);
      x4367 = x4396
      val x4398 = x4366._3;
      val x4399 = x4398.hashCode();
      val x4400 = -862048943.*(x4399);
      val x4401 = x4400.<<(15);
      val x4402 = x4400.>>>(-15);
      val x4403 = x4401.|(x4402);
      val x4404 = x4403.*(461845907);
      val x4405 = x4367;
      val x4406 = x4404.^(x4405);
      val x4407 = x4406.<<(13);
      val x4408 = x4406.>>>(-13);
      val x4409 = x4407.|(x4408);
      val x4410 = x4409.*(5);
      val x4411 = x4410.+(-430675100);
      x4367 = x4411
      val x4413 = x4366._4;
      val x4414 = x4413.hashCode();
      val x4415 = -862048943.*(x4414);
      val x4416 = x4415.<<(15);
      val x4417 = x4415.>>>(-15);
      val x4418 = x4416.|(x4417);
      val x4419 = x4418.*(461845907);
      val x4420 = x4367;
      val x4421 = x4419.^(x4420);
      val x4422 = x4421.<<(13);
      val x4423 = x4421.>>>(-13);
      val x4424 = x4422.|(x4423);
      val x4425 = x4424.*(5);
      val x4426 = x4425.+(-430675100);
      x4367 = x4426
      val x4428 = x4366._5;
      val x4429 = x4428.hashCode();
      val x4430 = -862048943.*(x4429);
      val x4431 = x4430.<<(15);
      val x4432 = x4430.>>>(-15);
      val x4433 = x4431.|(x4432);
      val x4434 = x4433.*(461845907);
      val x4435 = x4367;
      val x4436 = x4434.^(x4435);
      val x4437 = x4436.<<(13);
      val x4438 = x4436.>>>(-13);
      val x4439 = x4437.|(x4438);
      val x4440 = x4439.*(5);
      val x4441 = x4440.+(-430675100);
      x4367 = x4441
      val x4443 = x4366._6;
      val x4444 = x4443.hashCode();
      val x4445 = -862048943.*(x4444);
      val x4446 = x4445.<<(15);
      val x4447 = x4445.>>>(-15);
      val x4448 = x4446.|(x4447);
      val x4449 = x4448.*(461845907);
      val x4450 = x4367;
      val x4451 = x4449.^(x4450);
      val x4452 = x4451.<<(13);
      val x4453 = x4451.>>>(-13);
      val x4454 = x4452.|(x4453);
      val x4455 = x4454.*(5);
      val x4456 = x4455.+(-430675100);
      x4367 = x4456
      val x4458 = x4366._7;
      val x4459 = x4458.hashCode();
      val x4460 = -862048943.*(x4459);
      val x4461 = x4460.<<(15);
      val x4462 = x4460.>>>(-15);
      val x4463 = x4461.|(x4462);
      val x4464 = x4463.*(461845907);
      val x4465 = x4367;
      val x4466 = x4464.^(x4465);
      val x4467 = x4466.<<(13);
      val x4468 = x4466.>>>(-13);
      val x4469 = x4467.|(x4468);
      val x4470 = x4469.*(5);
      val x4471 = x4470.+(-430675100);
      x4367 = x4471
      val x4473 = x4366._8;
      val x4474 = x4473.hashCode();
      val x4475 = -862048943.*(x4474);
      val x4476 = x4475.<<(15);
      val x4477 = x4475.>>>(-15);
      val x4478 = x4476.|(x4477);
      val x4479 = x4478.*(461845907);
      val x4480 = x4367;
      val x4481 = x4479.^(x4480);
      val x4482 = x4481.<<(13);
      val x4483 = x4481.>>>(-13);
      val x4484 = x4482.|(x4483);
      val x4485 = x4484.*(5);
      val x4486 = x4485.+(-430675100);
      x4367 = x4486
      val x4488 = x4367;
      val x4489 = x4488.^(2);
      val x4490 = x4489.>>>(16);
      val x4491 = x4489.^(x4490);
      val x4492 = x4491.*(-2048144789);
      val x4493 = x4492.>>>(13);
      val x4494 = x4492.^(x4493);
      val x4495 = x4494.*(-1028477387);
      val x4496 = x4495.>>>(16);
      val x4497 = x4495.^(x4496);
      x4497
    }
    override def cmp(x4499 : SEntry8_IIIIITDS , x4500 : SEntry8_IIIIITDS) = {
      val x4501 = x4499._1;
      val x4502 = x4500._1;
      val x4503 = x4501.==(-2147483648);
      val x4505 = x4503.||({
        val x4504 = x4502.==(-2147483648);
        x4504
      });
      val x4507 = x4505.||({
        val x4506 = x4501.==(x4502);
        x4506
      });
      val x4515 = x4507.&&({
        val x4508 = x4499._2;
        val x4509 = x4500._2;
        val x4510 = x4508.==(-2147483648);
        val x4512 = x4510.||({
          val x4511 = x4509.==(-2147483648);
          x4511
        });
        val x4514 = x4512.||({
          val x4513 = x4508.==(x4509);
          x4513
        });
        x4514
      });
      val x4523 = x4515.&&({
        val x4516 = x4499._3;
        val x4517 = x4500._3;
        val x4518 = x4516.==(-2147483648);
        val x4520 = x4518.||({
          val x4519 = x4517.==(-2147483648);
          x4519
        });
        val x4522 = x4520.||({
          val x4521 = x4516.==(x4517);
          x4521
        });
        x4522
      });
      val x4531 = x4523.&&({
        val x4524 = x4499._4;
        val x4525 = x4500._4;
        val x4526 = x4524.==(-2147483648);
        val x4528 = x4526.||({
          val x4527 = x4525.==(-2147483648);
          x4527
        });
        val x4530 = x4528.||({
          val x4529 = x4524.==(x4525);
          x4529
        });
        x4530
      });
      val x4539 = x4531.&&({
        val x4532 = x4499._5;
        val x4533 = x4500._5;
        val x4534 = x4532.==(-2147483648);
        val x4536 = x4534.||({
          val x4535 = x4533.==(-2147483648);
          x4535
        });
        val x4538 = x4536.||({
          val x4537 = x4532.==(x4533);
          x4537
        });
        x4538
      });
      val x4547 = x4539.&&({
        val x4540 = x4499._6;
        val x4541 = x4500._6;
        val x4542 = x4540.==(null);
        val x4544 = x4542.||({
          val x4543 = x4541.==(null);
          x4543
        });
        val x4546 = x4544.||({
          val x4545 = x4540.==(x4541);
          x4545
        });
        x4546
      });
      val x4555 = x4547.&&({
        val x4548 = x4499._7;
        val x4549 = x4500._7;
        val x4550 = x4548.==(-1.7976931348623157E308);
        val x4552 = x4550.||({
          val x4551 = x4549.==(-1.7976931348623157E308);
          x4551
        });
        val x4554 = x4552.||({
          val x4553 = x4548.==(x4549);
          x4553
        });
        x4554
      });
      val x4556 = if(x4555) 0 else 1;
      x4556
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5052 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5053: Int = -889275714;
      val x5054 = x5052._2;
      val x5055 = x5054.hashCode();
      val x5056 = -862048943.*(x5055);
      val x5057 = x5056.<<(15);
      val x5058 = x5056.>>>(-15);
      val x5059 = x5057.|(x5058);
      val x5060 = x5059.*(461845907);
      val x5061 = x5053;
      val x5062 = x5060.^(x5061);
      val x5063 = x5062.<<(13);
      val x5064 = x5062.>>>(-13);
      val x5065 = x5063.|(x5064);
      val x5066 = x5065.*(5);
      val x5067 = x5066.+(-430675100);
      x5053 = x5067
      val x5069 = x5052._3;
      val x5070 = x5069.hashCode();
      val x5071 = -862048943.*(x5070);
      val x5072 = x5071.<<(15);
      val x5073 = x5071.>>>(-15);
      val x5074 = x5072.|(x5073);
      val x5075 = x5074.*(461845907);
      val x5076 = x5053;
      val x5077 = x5075.^(x5076);
      val x5078 = x5077.<<(13);
      val x5079 = x5077.>>>(-13);
      val x5080 = x5078.|(x5079);
      val x5081 = x5080.*(5);
      val x5082 = x5081.+(-430675100);
      x5053 = x5082
      val x5084 = x5052._6;
      val x5085 = x5084.hashCode();
      val x5086 = -862048943.*(x5085);
      val x5087 = x5086.<<(15);
      val x5088 = x5086.>>>(-15);
      val x5089 = x5087.|(x5088);
      val x5090 = x5089.*(461845907);
      val x5091 = x5053;
      val x5092 = x5090.^(x5091);
      val x5093 = x5092.<<(13);
      val x5094 = x5092.>>>(-13);
      val x5095 = x5093.|(x5094);
      val x5096 = x5095.*(5);
      val x5097 = x5096.+(-430675100);
      x5053 = x5097
      val x5099 = x5053;
      val x5100 = x5099.^(2);
      val x5101 = x5100.>>>(16);
      val x5102 = x5100.^(x5101);
      val x5103 = x5102.*(-2048144789);
      val x5104 = x5103.>>>(13);
      val x5105 = x5103.^(x5104);
      val x5106 = x5105.*(-1028477387);
      val x5107 = x5106.>>>(16);
      val x5108 = x5106.^(x5107);
      x5108
    }
    override def cmp(x5110 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5111 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x5112 = x5110._2;
      val x5113 = x5111._2;
      val x5114 = x5112.==(x5113);
      val x5118 = x5114.&&({
        val x5115 = x5110._3;
        val x5116 = x5111._3;
        val x5117 = x5115.==(x5116);
        x5117
      });
      val x5122 = x5118.&&({
        val x5119 = x5110._6;
        val x5120 = x5111._6;
        val x5121 = x5119.==(x5120);
        x5121
      });
      val x5123 = if(x5122) 0 else 1;
      x5123
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4605 : SEntry8_IIIITIIB) = {
      var x4606: Int = -889275714;
      val x4607 = x4605._1;
      val x4608 = x4607.hashCode();
      val x4609 = -862048943.*(x4608);
      val x4610 = x4609.<<(15);
      val x4611 = x4609.>>>(-15);
      val x4612 = x4610.|(x4611);
      val x4613 = x4612.*(461845907);
      val x4614 = x4606;
      val x4615 = x4613.^(x4614);
      val x4616 = x4615.<<(13);
      val x4617 = x4615.>>>(-13);
      val x4618 = x4616.|(x4617);
      val x4619 = x4618.*(5);
      val x4620 = x4619.+(-430675100);
      x4606 = x4620
      val x4622 = x4605._2;
      val x4623 = x4622.hashCode();
      val x4624 = -862048943.*(x4623);
      val x4625 = x4624.<<(15);
      val x4626 = x4624.>>>(-15);
      val x4627 = x4625.|(x4626);
      val x4628 = x4627.*(461845907);
      val x4629 = x4606;
      val x4630 = x4628.^(x4629);
      val x4631 = x4630.<<(13);
      val x4632 = x4630.>>>(-13);
      val x4633 = x4631.|(x4632);
      val x4634 = x4633.*(5);
      val x4635 = x4634.+(-430675100);
      x4606 = x4635
      val x4637 = x4605._3;
      val x4638 = x4637.hashCode();
      val x4639 = -862048943.*(x4638);
      val x4640 = x4639.<<(15);
      val x4641 = x4639.>>>(-15);
      val x4642 = x4640.|(x4641);
      val x4643 = x4642.*(461845907);
      val x4644 = x4606;
      val x4645 = x4643.^(x4644);
      val x4646 = x4645.<<(13);
      val x4647 = x4645.>>>(-13);
      val x4648 = x4646.|(x4647);
      val x4649 = x4648.*(5);
      val x4650 = x4649.+(-430675100);
      x4606 = x4650
      val x4652 = x4606;
      val x4653 = x4652.^(2);
      val x4654 = x4653.>>>(16);
      val x4655 = x4653.^(x4654);
      val x4656 = x4655.*(-2048144789);
      val x4657 = x4656.>>>(13);
      val x4658 = x4656.^(x4657);
      val x4659 = x4658.*(-1028477387);
      val x4660 = x4659.>>>(16);
      val x4661 = x4659.^(x4660);
      x4661
    }
    override def cmp(x4663 : SEntry8_IIIITIIB , x4664 : SEntry8_IIIITIIB) = {
      val x4665 = x4663._1;
      val x4666 = x4664._1;
      val x4667 = x4665.==(x4666);
      val x4671 = x4667.&&({
        val x4668 = x4663._2;
        val x4669 = x4664._2;
        val x4670 = x4668.==(x4669);
        x4670
      });
      val x4675 = x4671.&&({
        val x4672 = x4663._3;
        val x4673 = x4664._3;
        val x4674 = x4672.==(x4673);
        x4674
      });
      val x4676 = if(x4675) 0 else 1;
      x4676
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x4251 : SEntry3_III) = {
      var x4252: Int = -889275714;
      val x4253 = x4251._2;
      val x4254 = x4253.hashCode();
      val x4255 = -862048943.*(x4254);
      val x4256 = x4255.<<(15);
      val x4257 = x4255.>>>(-15);
      val x4258 = x4256.|(x4257);
      val x4259 = x4258.*(461845907);
      val x4260 = x4252;
      val x4261 = x4259.^(x4260);
      val x4262 = x4261.<<(13);
      val x4263 = x4261.>>>(-13);
      val x4264 = x4262.|(x4263);
      val x4265 = x4264.*(5);
      val x4266 = x4265.+(-430675100);
      x4252 = x4266
      val x4268 = x4251._3;
      val x4269 = x4268.hashCode();
      val x4270 = -862048943.*(x4269);
      val x4271 = x4270.<<(15);
      val x4272 = x4270.>>>(-15);
      val x4273 = x4271.|(x4272);
      val x4274 = x4273.*(461845907);
      val x4275 = x4252;
      val x4276 = x4274.^(x4275);
      val x4277 = x4276.<<(13);
      val x4278 = x4276.>>>(-13);
      val x4279 = x4277.|(x4278);
      val x4280 = x4279.*(5);
      val x4281 = x4280.+(-430675100);
      x4252 = x4281
      val x4283 = x4252;
      val x4284 = x4283.^(2);
      val x4285 = x4284.>>>(16);
      val x4286 = x4284.^(x4285);
      val x4287 = x4286.*(-2048144789);
      val x4288 = x4287.>>>(13);
      val x4289 = x4287.^(x4288);
      val x4290 = x4289.*(-1028477387);
      val x4291 = x4290.>>>(16);
      val x4292 = x4290.^(x4291);
      x4292
    }
    override def cmp(x4294 : SEntry3_III , x4295 : SEntry3_III) = {
      val x4296 = x4294._1;
      val x4297 = x4295._1;
      val x4298 = x4296.==(x4297);
      val x4299 = x4296.>(x4297);
      val x4300 = if(x4299) 1 else -1;
      val x4301 = if(x4298) 0 else x4300;
      x4301
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4679 : SEntry8_IIIITIIB) = {
      var x4680: Int = -889275714;
      val x4681 = x4679._2;
      val x4682 = x4681.hashCode();
      val x4683 = -862048943.*(x4682);
      val x4684 = x4683.<<(15);
      val x4685 = x4683.>>>(-15);
      val x4686 = x4684.|(x4685);
      val x4687 = x4686.*(461845907);
      val x4688 = x4680;
      val x4689 = x4687.^(x4688);
      val x4690 = x4689.<<(13);
      val x4691 = x4689.>>>(-13);
      val x4692 = x4690.|(x4691);
      val x4693 = x4692.*(5);
      val x4694 = x4693.+(-430675100);
      x4680 = x4694
      val x4696 = x4679._3;
      val x4697 = x4696.hashCode();
      val x4698 = -862048943.*(x4697);
      val x4699 = x4698.<<(15);
      val x4700 = x4698.>>>(-15);
      val x4701 = x4699.|(x4700);
      val x4702 = x4701.*(461845907);
      val x4703 = x4680;
      val x4704 = x4702.^(x4703);
      val x4705 = x4704.<<(13);
      val x4706 = x4704.>>>(-13);
      val x4707 = x4705.|(x4706);
      val x4708 = x4707.*(5);
      val x4709 = x4708.+(-430675100);
      x4680 = x4709
      val x4711 = x4679._4;
      val x4712 = x4711.hashCode();
      val x4713 = -862048943.*(x4712);
      val x4714 = x4713.<<(15);
      val x4715 = x4713.>>>(-15);
      val x4716 = x4714.|(x4715);
      val x4717 = x4716.*(461845907);
      val x4718 = x4680;
      val x4719 = x4717.^(x4718);
      val x4720 = x4719.<<(13);
      val x4721 = x4719.>>>(-13);
      val x4722 = x4720.|(x4721);
      val x4723 = x4722.*(5);
      val x4724 = x4723.+(-430675100);
      x4680 = x4724
      val x4726 = x4680;
      val x4727 = x4726.^(2);
      val x4728 = x4727.>>>(16);
      val x4729 = x4727.^(x4728);
      val x4730 = x4729.*(-2048144789);
      val x4731 = x4730.>>>(13);
      val x4732 = x4730.^(x4731);
      val x4733 = x4732.*(-1028477387);
      val x4734 = x4733.>>>(16);
      val x4735 = x4733.^(x4734);
      x4735
    }
    override def cmp(x4737 : SEntry8_IIIITIIB , x4738 : SEntry8_IIIITIIB) = {
      val x4739 = x4737._1;
      val x4740 = x4738._1;
      val x4741 = x4739.==(x4740);
      val x4742 = x4739.>(x4740);
      val x4743 = if(x4742) 1 else -1;
      val x4744 = if(x4741) 0 else x4743;
      x4744
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4567 : SEntry9_ISSSSSSDD) = {
      var x4568: Int = 0;
      val x4569 = x4567._1;
      val x4570 = x4569.-(1);
      val x4571 = x4568;
      val x4572 = x4571.*(1);
      val x4573 = x4572.+(x4570);
      x4568 = x4573
      val x4575 = x4568;
      x4575
    }
    override def cmp(x4564 : SEntry9_ISSSSSSDD , x4565 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4586 : SEntry5_IISDS) = {
      var x4587: Int = 0;
      val x4588 = x4586._1;
      val x4589 = x4588.-(1);
      val x4590 = x4587;
      val x4591 = x4590.*(100000);
      val x4592 = x4591.+(x4589);
      x4587 = x4592
      val x4594 = x4587;
      x4594
    }
    override def cmp(x4583 : SEntry5_IISDS , x4584 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4831 : SEntry11_IISSSSSSDDI) = {
      var x4832: Int = 0;
      val x4833 = x4831._1;
      val x4834 = x4833.-(1);
      val x4835 = x4832;
      val x4836 = x4835.*(10);
      val x4837 = x4836.+(x4834);
      x4832 = x4837
      val x4839 = x4831._2;
      val x4840 = x4839.-(1);
      val x4841 = x4832;
      val x4842 = x4841.*(1);
      val x4843 = x4842.+(x4840);
      x4832 = x4843
      val x4845 = x4832;
      x4845
    }
    override def cmp(x4828 : SEntry11_IISSSSSSDDI , x4829 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x5029 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x5030: Int = 0;
      val x5031 = x5029._1;
      val x5032 = x5031.-(1);
      val x5033 = x5030;
      val x5034 = x5033.*(3000);
      val x5035 = x5034.+(x5032);
      x5030 = x5035
      val x5037 = x5029._2;
      val x5038 = x5037.-(1);
      val x5039 = x5030;
      val x5040 = x5039.*(10);
      val x5041 = x5040.+(x5038);
      x5030 = x5041
      val x5043 = x5029._3;
      val x5044 = x5043.-(1);
      val x5045 = x5030;
      val x5046 = x5045.*(1);
      val x5047 = x5046.+(x5044);
      x5030 = x5047
      val x5049 = x5030;
      x5049
    }
    override def cmp(x5026 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x5027 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x5135 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x5136: Int = 0;
      val x5137 = x5135._1;
      val x5138 = x5137.-(1);
      val x5139 = x5136;
      val x5140 = x5139.*(100000);
      val x5141 = x5140.+(x5138);
      x5136 = x5141
      val x5143 = x5135._2;
      val x5144 = x5143.-(1);
      val x5145 = x5136;
      val x5146 = x5145.*(1);
      val x5147 = x5146.+(x5144);
      x5136 = x5147
      val x5149 = x5136;
      x5149
    }
    override def cmp(x5132 : SEntry17_IIISSSSSSSSSSIIIS , x5133 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x8131 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x8556 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8429 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x8416 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8906 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8878 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x8930 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x8653 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x8121 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x8460 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x8903 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x8701 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8899 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8539 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8108 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x8718 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8135 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8659 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8527 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  class DeliveryTx(x4361: Store[SEntry3_III], x4561: Store[SEntry8_IIIIITDS], x4580: Store[SEntry9_ISSSSSSDD], x4599: Store[SEntry5_IISDS], x4823: Store[SEntry8_IIIITIIB], x4850: Store[SEntry11_IISSSSSSDDI], x5022: Store[SEntry10_IIIIIITIDS], x5128: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5154: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](123);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val x27 = x18;
        x8108._2_=(x27)
        x8108._3_=(x12)
        val x13435 = x944.get(x8108);
        if((x13435.!=(null))) 
        {
          val x8114 = x13435._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x8114)
          x4361.delete(x13435)
          val x41 = x18;
          x8121._1_=(x8114)
          x8121._2_=(x41)
          x8121._3_=(x12)
          val x13449 = x967.get(x8121);
          val x8124 = x13449._4;
          x13449._6_=(x13)
          var x51: Double = 0.0;
          val x53 = x18;
          x8131._1_=(x8114)
          x8131._2_=(x53)
          x8131._3_=(x12)
          x980.slice(x8131, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              orderLineEntry._7_=(x11)
              val x58 = x51;
              val x8232 = orderLineEntry._9;
              x51 = (x58.+(x8232))
              ()
            }
          }))
          val x66 = x18;
          x8135._1_=(x8124)
          x8135._2_=(x66)
          x8135._3_=(x12)
          val x13471 = x986.get(x8135);
          val x70 = x51;
          x13471._17 +=(x70)
          x13471._20 +=(1)
          ()
        }
        else
        {
          val x74 = x18;
          orderIDs.update((x74.-(1)), 0)
          ()
        }
        
        val x78 = x18;
        x18 = (x78.+(1))
        ()
      }
      if(x10) 
      {
        val x83 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11);
        val x84 = x83.+("\n\n Warehouse: ");
        val x85 = x84.+(x12);
        val x86 = x85.+("\n Carrier:   ");
        val x87 = x86.+(x13);
        val x88 = x87.+("\n\n Delivered Orders\n");
        var x89: String = x88;
        var x92: Int = 0;
        var x95: Int = 1;
        while({
          val x97 = x95;
          (x97.<=(10))
        })
        {
          val x99 = x95;
          val x101 = orderIDs.apply((x99.-(1)));
          if((x101.>=(0))) 
          {
            val x103 = x89;
            val x104 = x103.+("  District ");
            val x105 = x95;
            val x107 = if((x105.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x108 = x104.+(x107);
            val x109 = x95;
            val x110 = x108.+(x109);
            val x111 = x110.+(": Order number ");
            val x112 = x95;
            val x114 = orderIDs.apply((x112.-(1)));
            val x115 = x111.+(x114);
            val x116 = x115.+(" was delivered.\n");
            x89 = x116
            ()
          }
          else
          {
            val x118 = x89;
            val x119 = x118.+("  District ");
            val x120 = x95;
            val x122 = if((x120.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x123 = x119.+(x122);
            val x124 = x95;
            val x125 = x123.+(x124);
            val x126 = x125.+(": No orders to be delivered.\n");
            x89 = x126
            val x128 = x92;
            x92 = (x128.+(1))
            ()
          }
          
          val x132 = x95;
          x95 = (x132.+(1))
          ()
        }
        val x136 = x89;
        val x137 = x136.+("+-----------------------------------------------------------------+\n\n");
        x89 = x137
        val x139 = x89;
        println(x139)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class StockLevelTx(x4361: Store[SEntry3_III], x4561: Store[SEntry8_IIIIITDS], x4580: Store[SEntry9_ISSSSSSDD], x4599: Store[SEntry5_IISDS], x4823: Store[SEntry8_IIIITIIB], x4850: Store[SEntry11_IISSSSSSDDI], x5022: Store[SEntry10_IIIIIITIDS], x5128: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5154: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x142 : Boolean, x143 : Date, x144 : Int, x145 : Int, x146 : Int, x147 : Int) =     {
      x8416._1_=(x146)
      x8416._2_=(x145)
      val x13650 = x974.get(x8416);
      val x8419 = x13650._11;
      var x157: Int = (x8419.-(20));
      val unique_ol_i_id = Set.apply[Int]();
      while({
        val x161 = x157;
        (x161.<(x8419))
      })
      {
        val x163 = x157;
        x8429._1_=(x163)
        x8429._2_=(x146)
        x8429._3_=(x145)
        x980.slice(x8429, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
            val x8458 = orderLineEntry._5;
            x8460._1_=(x8458)
            x8460._2_=(x145)
            val x13664 = x992.get(x8460);
            val x8462 = x13664._3;
            if((x8462.<(x147))) 
            {
              val x176 = unique_ol_i_id.+=(x8458);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x180 = x157;
        x157 = (x180.+(1))
        ()
      }
      val stock_count = unique_ol_i_id.size;
      if(x142) 
      {
        val x187 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x145);
        val x188 = x187.+("\n District:  ");
        val x189 = x188.+(x146);
        val x190 = x189.+("\n\n Stock Level Threshold: ");
        val x191 = x190.+(x147);
        val x192 = x191.+("\n Low Stock Count:       ");
        val x193 = x192.+(stock_count);
        val output = x193.+("\n+-----------------------------------------------------------------+\n\n");
        println(output)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class OrderStatusTx(x4361: Store[SEntry3_III], x4561: Store[SEntry8_IIIIITDS], x4580: Store[SEntry9_ISSSSSSDD], x4599: Store[SEntry5_IISDS], x4823: Store[SEntry8_IIIITIIB], x4850: Store[SEntry11_IISSSSSSDDI], x5022: Store[SEntry10_IIIIIITIDS], x5128: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5154: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x197 : Boolean, x198 : Date, x199 : Int, x200 : Int, x201 : Int, x202 : Int, x203 : Int, x204 : String) =     {
      val x8524 = if((x202.>(0))) 
      {
        val x8536 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x8539._2_=(x201)
        x8539._3_=(x200)
        x8539._6_=(x204)
        x987.slice(x8539, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8536.append(custEntry)
            ()
          }
        }))
        val x216 = x8536.size;
        var x218: Int = (x216./(2));
        val x220 = x8536.size;
        if(((x220.%(2)).==(0))) 
        {
          val x223 = x218;
          x218 = (x223.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x234 = x8536.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8583 = c1._4;
            val x8584 = c2._4;
            ((StringExtra.StringCompare(x8583, x8584)).<(0))
          }
        }));
        val x235 = x218;
        val x8554 = x234.apply(x235);
        x8554
      }
      else
      {
        x8556._1_=(x203)
        x8556._2_=(x201)
        x8556._3_=(x200)
        val x13768 = x986.get(x8556);
        x13768
      }
      ;
      val x8525 = x8524._3;
      x8527._2_=(x201)
      x8527._3_=(x200)
      x8527._4_=(x8525)
      val x13776 = x968.get(x8527);
      var x255: Int = 0;
      val x8532 = x13776._1;
      x255 = x8532
      1
    }
  }
  class PaymentTx(x4361: Store[SEntry3_III], x4561: Store[SEntry8_IIIIITDS], x4580: Store[SEntry9_ISSSSSSDD], x4599: Store[SEntry5_IISDS], x4823: Store[SEntry8_IIIITIIB], x4850: Store[SEntry11_IISSSSSSDDI], x5022: Store[SEntry10_IIIIIITIDS], x5128: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5154: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x259 : Boolean, x260 : Date, x261 : Int, x262 : Int, x263 : Int, x264 : Int, x265 : Int, x266 : Int, x267 : Int, x268 : String, x269 : Double) =     {
      x8653._1_=(x262)
      val x13831 = x955.get(x8653);
      x13831._9 +=(x269)
      x8659._1_=(x263)
      x8659._2_=(x262)
      val x13836 = x974.get(x8659);
      x13836._10 +=(x269)
      val x8664 = if((x264.>(0))) 
      {
        val x8698 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x8701._2_=(x266)
        x8701._3_=(x265)
        x8701._6_=(x268)
        x987.slice(x8701, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x8698.append(custEntry)
            ()
          }
        }))
        val x294 = x8698.size;
        var x296: Int = (x294./(2));
        val x298 = x8698.size;
        if(((x298.%(2)).==(0))) 
        {
          val x301 = x296;
          x296 = (x301.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x312 = x8698.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x8766 = c1._4;
            val x8767 = c2._4;
            ((StringExtra.StringCompare(x8766, x8767)).<(0))
          }
        }));
        val x313 = x296;
        val x8716 = x312.apply(x313);
        x8716
      }
      else
      {
        x8718._1_=(x267)
        x8718._2_=(x266)
        x8718._3_=(x265)
        val x13873 = x986.get(x8718);
        x13873
      }
      ;
      val x8665 = x8664._21;
      val x8666 = x8664._14;
      val x322 = x8666.contains("BC");
      val x331 = if(x322) 
      {
        val x8669 = x8664._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x8669,x266,x265,x263,x262,x269,(x260.toString()),x8665)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x8664._17 +=(x269)
        x8664._21_=(c_new_data)
        ()
      }
      else
      {
        x8664._17 +=(x269)
        ()
      }
      ;
      val x8677 = x13831._2;
      val x8678 = x13836._3;
      var h_data = "%.10s    %.10s".format(x8677,x8678)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x8681 = x8664._1;
      x4561.insert((SEntry8_IIIIITDS(x8681, x266, x265, x263, x262, x260, x269, h_data)))
      1
    }
  }
  class NewOrderTx(x4361: Store[SEntry3_III], x4561: Store[SEntry8_IIIIITDS], x4580: Store[SEntry9_ISSSSSSDD], x4599: Store[SEntry5_IISDS], x4823: Store[SEntry8_IIIITIIB], x4850: Store[SEntry11_IISSSSSSDDI], x5022: Store[SEntry10_IIIIIITIDS], x5128: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x5154: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x344 : Boolean, x345 : Date, x346 : Int, x347 : Int, x348 : Int, x349 : Int, x350 : Int, x351 : Int, x352 : Array[Int], x353 : Array[Int], x354 : Array[Int], x355 : Array[Double], x356 : Array[String], x357 : Array[Int], x358 : Array[String], x359 : Array[Double]) =     {
      var x361: Int = 0;
      var x364: Int = 0;
      val idata = new Array[String](x350);
      var x369: Boolean = true;
      while({
        val x371 = x361;
        ((x371.<(x350)).&&({
          val x373 = x369;
          x373
        }))
      })
      {
        val x376 = x361;
        val x377 = x352.apply(x376);
        x8878._1_=(x377)
        val x13972 = x960.get(x8878);
        if((x13972.==(null))) 
        {
          x369 = false
          ()
        }
        else
        {
          val x384 = x361;
          val x8885 = x13972._3;
          x356.update(x384, x8885)
          val x387 = x361;
          val x8888 = x13972._4;
          x355.update(x387, x8888)
          val x390 = x361;
          val x8891 = x13972._5;
          idata.update(x390, x8891)
          ()
        }
        
        val x394 = x361;
        x361 = (x394.+(1))
        ()
      }
      val x398 = x369;
      if(x398) 
      {
        x8899._1_=(x349)
        x8899._2_=(x348)
        x8899._3_=(x347)
        val x13995 = x986.get(x8899);
        x8903._1_=(x347)
        val x13998 = x955.get(x8903);
        x8906._1_=(x348)
        x8906._2_=(x347)
        val x14002 = x974.get(x8906);
        val x8908 = x14002._11;
        x14002._11 +=(1)
        x4823.insert((SEntry8_IIIITIIB(x8908, x348, x347, x349, x345, -1, x350, (x351.>(0)))))
        x4361.insert((SEntry3_III(x8908, x348, x347)))
        var x424: Double = 0.0;
        x361 = 0
        while({
          val x427 = x361;
          (x427.<(x350))
        })
        {
          val x430 = x361;
          val ol_supply_w_id = x353.apply(x430);
          val x433 = x361;
          val ol_i_id = x352.apply(x433);
          val x436 = x361;
          val ol_quantity = x354.apply(x436);
          x8930._1_=(ol_i_id)
          x8930._2_=(ol_supply_w_id)
          val x14026 = x992.get(x8930);
          val ol_dist_info = if((x348.==(1))) 
          {
            val x8934 = x14026._4;
            x8934
          }
          else
          {
            val x469 = if((x348.==(2))) 
            {
              val x8937 = x14026._5;
              x8937
            }
            else
            {
              val x468 = if((x348.==(3))) 
              {
                val x8940 = x14026._6;
                x8940
              }
              else
              {
                val x467 = if((x348.==(4))) 
                {
                  val x8943 = x14026._7;
                  x8943
                }
                else
                {
                  val x466 = if((x348.==(5))) 
                  {
                    val x8946 = x14026._8;
                    x8946
                  }
                  else
                  {
                    val x465 = if((x348.==(6))) 
                    {
                      val x8949 = x14026._9;
                      x8949
                    }
                    else
                    {
                      val x464 = if((x348.==(7))) 
                      {
                        val x8952 = x14026._10;
                        x8952
                      }
                      else
                      {
                        val x463 = if((x348.==(8))) 
                        {
                          val x8955 = x14026._11;
                          x8955
                        }
                        else
                        {
                          val x462 = if((x348.==(9))) 
                          {
                            val x8958 = x14026._12;
                            x8958
                          }
                          else
                          {
                            val x8959 = x14026._13;
                            x8959
                          }
                          ;
                          x462
                        }
                        ;
                        x463
                      }
                      ;
                      x464
                    }
                    ;
                    x465
                  }
                  ;
                  x466
                }
                ;
                x467
              }
              ;
              x468
            }
            ;
            x469
          }
          ;
          val x8960 = x14026._3;
          val x473 = x361;
          x357.update(x473, x8960)
          val x8963 = x13995._14;
          val x476 = x8963.contains("original");
          if((x476.&&({
            val x8966 = x14026._17;
            val x478 = x8966.contains("original");
            x478
          }))) 
          {
            val x480 = x361;
            x358.update(x480, "B")
            ()
          }
          else
          {
            val x482 = x361;
            x358.update(x482, "G")
            ()
          }
          
          x14026._3_=((x8960.-(ol_quantity)))
          val x489 = if((x8960.<=(ol_quantity))) 
          {
            x14026._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x491: Int = 0;
          if((ol_supply_w_id.!=(x347))) 
          {
            x491 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8983 = x13995._16;
          val x8984 = x13998._8;
          val x8985 = x14002._9;
          val x504 = x361;
          val x505 = x355.apply(x504);
          val ol_amount = (((ol_quantity.toDouble).*(x505)).*(((1.0.+(x8984)).+(x8985)))).*((1.0.-(x8983)));
          val x513 = x361;
          x359.update(x513, ol_amount)
          val x515 = x424;
          x424 = (x515.+(ol_amount))
          val x518 = x361;
          x5022.insert((SEntry10_IIIIIITIDS(x8908, x348, x347, (x518.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info)))
          val x523 = x361;
          x361 = (x523.+(1))
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
