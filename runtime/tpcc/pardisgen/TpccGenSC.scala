
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
  val x783 = { x18: SEntry3_III => {
      val x5458 = x18._1
      x5458
    }
  }
  val x3921 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x3922 = new Store[SEntry3_III](3, x3921)
  val x789 = x3922.index(0, IHash, true, -1)
  val x790 = x3922.index(1, ISliceHeapMin, false, 2)
  val x791 = x3922.index(2, INone, false, -1)
  val x4001 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x4002 = new Store[SEntry8_IIIIITDS](1, x4001)
  val x796 = x4002.index(0, IList, false, -1)
  val x4020 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x4021 = new Store[SEntry9_ISSSSSSDD](1, x4020)
  val x801 = x4021.index(0, IDirect, true, 1)
  val x4039 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x4040 = new Store[SEntry5_IISDS](1, x4039)
  val x806 = x4040.index(0, IDirect, true, 100000)
  val x807 = { x146: SEntry8_IIIITIIB => {
      val x5766 = x146._1
      x5766
    }
  }
  val x4263 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4264 = new Store[SEntry8_IIIITIIB](3, x4263)
  val x813 = x4264.index(0, IHash, true, -1)
  val x814 = x4264.index(1, ISliceHeapMax, false, 2)
  val x815 = x4264.index(2, INone, false, -1)
  val x4290 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4291 = new Store[SEntry11_IISSSSSSDDI](1, x4290)
  val x820 = x4291.index(0, IDirect, true, 10)
  val x4462 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x4463 = new Store[SEntry10_IIIIIITIDS](2, x4462)
  val x825 = x4463.index(0, IHash, true, -1)
  val x826 = x4463.index(1, IHash, false, -1)
  val x4568 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x4569 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4568)
  val x832 = x4569.index(0, IDirect, true, 30000)
  val x833 = x4569.index(1, IHash, false, -1)
  val x4594 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x4595 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4594)
  val x838 = x4595.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x3922
  val historyTbl = x4002
  val warehouseTbl = x4021
  val itemTbl = x4040
  val orderTbl = x4264
  val districtTbl = x4291
  val orderLineTbl = x4463
  val customerTbl = x4569
  val stockTbl = x4595
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4294 : SEntry10_IIIIIITIDS) = {
      var x4295: Int = -889275714
      val x4296 = x4294._1
      val x4298 = -862048943.*((x4296.hashCode()))
      val x4303 = x4295
      val x4304 = (((x4298.<<(15)).|((x4298.>>>(-15)))).*(461845907)).^(x4303)
      x4295 = ((((x4304.<<(13)).|((x4304.>>>(-13)))).*(5)).+(-430675100))
      val x4311 = x4294._2
      val x4313 = -862048943.*((x4311.hashCode()))
      val x4318 = x4295
      val x4319 = (((x4313.<<(15)).|((x4313.>>>(-15)))).*(461845907)).^(x4318)
      x4295 = ((((x4319.<<(13)).|((x4319.>>>(-13)))).*(5)).+(-430675100))
      val x4326 = x4294._3
      val x4328 = -862048943.*((x4326.hashCode()))
      val x4333 = x4295
      val x4334 = (((x4328.<<(15)).|((x4328.>>>(-15)))).*(461845907)).^(x4333)
      x4295 = ((((x4334.<<(13)).|((x4334.>>>(-13)))).*(5)).+(-430675100))
      val x4341 = x4294._4
      val x4343 = -862048943.*((x4341.hashCode()))
      val x4348 = x4295
      val x4349 = (((x4343.<<(15)).|((x4343.>>>(-15)))).*(461845907)).^(x4348)
      x4295 = ((((x4349.<<(13)).|((x4349.>>>(-13)))).*(5)).+(-430675100))
      val x4356 = x4295
      val x4357 = x4356.^(2)
      val x4360 = (x4357.^((x4357.>>>(16)))).*(-2048144789)
      val x4363 = (x4360.^((x4360.>>>(13)))).*(-1028477387)
      (x4363.^((x4363.>>>(16))))
    }
    override def cmp(x4367 : SEntry10_IIIIIITIDS , x4368 : SEntry10_IIIIIITIDS) = {
      val x4369 = x4367._1
      val x4370 = x4368._1
      (if(((((x4369.==(x4370)).&&({
        val x4372 = x4367._2
        val x4373 = x4368._2
        (x4372.==(x4373))
      })).&&({
        val x4376 = x4367._3
        val x4377 = x4368._3
        (x4376.==(x4377))
      })).&&({
        val x4380 = x4367._4
        val x4381 = x4368._4
        (x4380.==(x4381))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4188 : SEntry8_IIIITIIB) = {
      var x4189: Int = -889275714
      val x4190 = x4188._2
      val x4192 = -862048943.*((x4190.hashCode()))
      val x4197 = x4189
      val x4198 = (((x4192.<<(15)).|((x4192.>>>(-15)))).*(461845907)).^(x4197)
      x4189 = ((((x4198.<<(13)).|((x4198.>>>(-13)))).*(5)).+(-430675100))
      val x4205 = x4188._3
      val x4207 = -862048943.*((x4205.hashCode()))
      val x4212 = x4189
      val x4213 = (((x4207.<<(15)).|((x4207.>>>(-15)))).*(461845907)).^(x4212)
      x4189 = ((((x4213.<<(13)).|((x4213.>>>(-13)))).*(5)).+(-430675100))
      val x4220 = x4188._4
      val x4222 = -862048943.*((x4220.hashCode()))
      val x4227 = x4189
      val x4228 = (((x4222.<<(15)).|((x4222.>>>(-15)))).*(461845907)).^(x4227)
      x4189 = ((((x4228.<<(13)).|((x4228.>>>(-13)))).*(5)).+(-430675100))
      val x4235 = x4189
      val x4236 = x4235.^(2)
      val x4239 = (x4236.^((x4236.>>>(16)))).*(-2048144789)
      val x4242 = (x4239.^((x4239.>>>(13)))).*(-1028477387)
      (x4242.^((x4242.>>>(16))))
    }
    override def cmp(x4246 : SEntry8_IIIITIIB , x4247 : SEntry8_IIIITIIB) = {
      val x4248 = x4246._2
      val x4249 = x4247._2
      (if((((x4248.==(x4249)).&&({
        val x4251 = x4246._3
        val x4252 = x4247._3
        (x4251.==(x4252))
      })).&&({
        val x4255 = x4246._4
        val x4256 = x4247._4
        (x4255.==(x4256))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3738 : SEntry3_III) = {
      var x3739: Int = -889275714
      val x3740 = x3738._1
      val x3742 = -862048943.*((x3740.hashCode()))
      val x3747 = x3739
      val x3748 = (((x3742.<<(15)).|((x3742.>>>(-15)))).*(461845907)).^(x3747)
      x3739 = ((((x3748.<<(13)).|((x3748.>>>(-13)))).*(5)).+(-430675100))
      val x3755 = x3738._2
      val x3757 = -862048943.*((x3755.hashCode()))
      val x3762 = x3739
      val x3763 = (((x3757.<<(15)).|((x3757.>>>(-15)))).*(461845907)).^(x3762)
      x3739 = ((((x3763.<<(13)).|((x3763.>>>(-13)))).*(5)).+(-430675100))
      val x3770 = x3738._3
      val x3772 = -862048943.*((x3770.hashCode()))
      val x3777 = x3739
      val x3778 = (((x3772.<<(15)).|((x3772.>>>(-15)))).*(461845907)).^(x3777)
      x3739 = ((((x3778.<<(13)).|((x3778.>>>(-13)))).*(5)).+(-430675100))
      val x3785 = x3739
      val x3786 = x3785.^(2)
      val x3789 = (x3786.^((x3786.>>>(16)))).*(-2048144789)
      val x3792 = (x3789.^((x3789.>>>(13)))).*(-1028477387)
      (x3792.^((x3792.>>>(16))))
    }
    override def cmp(x3796 : SEntry3_III , x3797 : SEntry3_III) = {
      val x3798 = x3796._1
      val x3799 = x3797._1
      (if((((x3798.==(x3799)).&&({
        val x3801 = x3796._2
        val x3802 = x3797._2
        (x3801.==(x3802))
      })).&&({
        val x3805 = x3796._3
        val x3806 = x3797._3
        (x3805.==(x3806))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4387 : SEntry10_IIIIIITIDS) = {
      var x4388: Int = -889275714
      val x4389 = x4387._1
      val x4391 = -862048943.*((x4389.hashCode()))
      val x4396 = x4388
      val x4397 = (((x4391.<<(15)).|((x4391.>>>(-15)))).*(461845907)).^(x4396)
      x4388 = ((((x4397.<<(13)).|((x4397.>>>(-13)))).*(5)).+(-430675100))
      val x4404 = x4387._2
      val x4406 = -862048943.*((x4404.hashCode()))
      val x4411 = x4388
      val x4412 = (((x4406.<<(15)).|((x4406.>>>(-15)))).*(461845907)).^(x4411)
      x4388 = ((((x4412.<<(13)).|((x4412.>>>(-13)))).*(5)).+(-430675100))
      val x4419 = x4387._3
      val x4421 = -862048943.*((x4419.hashCode()))
      val x4426 = x4388
      val x4427 = (((x4421.<<(15)).|((x4421.>>>(-15)))).*(461845907)).^(x4426)
      x4388 = ((((x4427.<<(13)).|((x4427.>>>(-13)))).*(5)).+(-430675100))
      val x4434 = x4388
      val x4435 = x4434.^(2)
      val x4438 = (x4435.^((x4435.>>>(16)))).*(-2048144789)
      val x4441 = (x4438.^((x4438.>>>(13)))).*(-1028477387)
      (x4441.^((x4441.>>>(16))))
    }
    override def cmp(x4445 : SEntry10_IIIIIITIDS , x4446 : SEntry10_IIIIIITIDS) = {
      val x4447 = x4445._1
      val x4448 = x4446._1
      (if((((x4447.==(x4448)).&&({
        val x4450 = x4445._2
        val x4451 = x4446._2
        (x4450.==(x4451))
      })).&&({
        val x4454 = x4445._3
        val x4455 = x4446._3
        (x4454.==(x4455))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3865 : SEntry3_III) = {
      var x3866: Int = -889275714
      val x3867 = x3865._2
      val x3869 = -862048943.*((x3867.hashCode()))
      val x3874 = x3866
      val x3875 = (((x3869.<<(15)).|((x3869.>>>(-15)))).*(461845907)).^(x3874)
      x3866 = ((((x3875.<<(13)).|((x3875.>>>(-13)))).*(5)).+(-430675100))
      val x3882 = x3865._3
      val x3884 = -862048943.*((x3882.hashCode()))
      val x3889 = x3866
      val x3890 = (((x3884.<<(15)).|((x3884.>>>(-15)))).*(461845907)).^(x3889)
      x3866 = ((((x3890.<<(13)).|((x3890.>>>(-13)))).*(5)).+(-430675100))
      val x3897 = x3866
      val x3898 = x3897.^(2)
      val x3901 = (x3898.^((x3898.>>>(16)))).*(-2048144789)
      val x3904 = (x3901.^((x3901.>>>(13)))).*(-1028477387)
      (x3904.^((x3904.>>>(16))))
    }
    override def cmp(x3908 : SEntry3_III , x3909 : SEntry3_III) = {
      val x3910 = x3908._2
      val x3911 = x3909._2
      (if(((x3910.==(x3911)).&&({
        val x3913 = x3908._3
        val x3914 = x3909._3
        (x3913.==(x3914))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3927 : SEntry8_IIIIITDS) = {
      var x3928: Int = -889275714
      val x3929 = x3928
      val x3930 = x3929.^(2)
      val x3933 = (x3930.^((x3930.>>>(16)))).*(-2048144789)
      val x3936 = (x3933.^((x3933.>>>(13)))).*(-1028477387)
      (x3936.^((x3936.>>>(16))))
    }
    override def cmp(x3940 : SEntry8_IIIIITDS , x3941 : SEntry8_IIIIITDS) = {
      val x3942 = x3940._1
      val x3943 = x3941._1
      (if((((((((((x3942.==(-1)).||({
        (x3943.==(-1))
      })).||({
        (x3942.==(x3943))
      })).&&({
        val x3949 = x3940._2
        val x3950 = x3941._2
        (((x3949.==(-1)).||({
          (x3950.==(-1))
        })).||({
          (x3949.==(x3950))
        }))
      })).&&({
        val x3957 = x3940._3
        val x3958 = x3941._3
        (((x3957.==(-1)).||({
          (x3958.==(-1))
        })).||({
          (x3957.==(x3958))
        }))
      })).&&({
        val x3965 = x3940._4
        val x3966 = x3941._4
        (((x3965.==(-1)).||({
          (x3966.==(-1))
        })).||({
          (x3965.==(x3966))
        }))
      })).&&({
        val x3973 = x3940._5
        val x3974 = x3941._5
        (((x3973.==(-1)).||({
          (x3974.==(-1))
        })).||({
          (x3973.==(x3974))
        }))
      })).&&({
        val x3981 = x3940._6
        val x3982 = x3941._6
        (((x3981.==(null)).||({
          (x3982.==(null))
        })).||({
          (x3981.==(x3982))
        }))
      })).&&({
        val x3989 = x3940._7
        val x3990 = x3941._7
        (((x3989.==(-1.0)).||({
          (x3990.==(-1.0))
        })).||({
          (x3989.==(x3990))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4493 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4494: Int = -889275714
      val x4495 = x4493._2
      val x4497 = -862048943.*((x4495.hashCode()))
      val x4502 = x4494
      val x4503 = (((x4497.<<(15)).|((x4497.>>>(-15)))).*(461845907)).^(x4502)
      x4494 = ((((x4503.<<(13)).|((x4503.>>>(-13)))).*(5)).+(-430675100))
      val x4510 = x4493._3
      val x4512 = -862048943.*((x4510.hashCode()))
      val x4517 = x4494
      val x4518 = (((x4512.<<(15)).|((x4512.>>>(-15)))).*(461845907)).^(x4517)
      x4494 = ((((x4518.<<(13)).|((x4518.>>>(-13)))).*(5)).+(-430675100))
      val x4525 = x4493._6
      val x4527 = -862048943.*((x4525.hashCode()))
      val x4532 = x4494
      val x4533 = (((x4527.<<(15)).|((x4527.>>>(-15)))).*(461845907)).^(x4532)
      x4494 = ((((x4533.<<(13)).|((x4533.>>>(-13)))).*(5)).+(-430675100))
      val x4540 = x4494
      val x4541 = x4540.^(2)
      val x4544 = (x4541.^((x4541.>>>(16)))).*(-2048144789)
      val x4547 = (x4544.^((x4544.>>>(13)))).*(-1028477387)
      (x4547.^((x4547.>>>(16))))
    }
    override def cmp(x4551 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4552 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4553 = x4551._2
      val x4554 = x4552._2
      (if((((x4553.==(x4554)).&&({
        val x4556 = x4551._3
        val x4557 = x4552._3
        (x4556.==(x4557))
      })).&&({
        val x4560 = x4551._6
        val x4561 = x4552._6
        (x4560.==(x4561))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4046 : SEntry8_IIIITIIB) = {
      var x4047: Int = -889275714
      val x4048 = x4046._1
      val x4050 = -862048943.*((x4048.hashCode()))
      val x4055 = x4047
      val x4056 = (((x4050.<<(15)).|((x4050.>>>(-15)))).*(461845907)).^(x4055)
      x4047 = ((((x4056.<<(13)).|((x4056.>>>(-13)))).*(5)).+(-430675100))
      val x4063 = x4046._2
      val x4065 = -862048943.*((x4063.hashCode()))
      val x4070 = x4047
      val x4071 = (((x4065.<<(15)).|((x4065.>>>(-15)))).*(461845907)).^(x4070)
      x4047 = ((((x4071.<<(13)).|((x4071.>>>(-13)))).*(5)).+(-430675100))
      val x4078 = x4046._3
      val x4080 = -862048943.*((x4078.hashCode()))
      val x4085 = x4047
      val x4086 = (((x4080.<<(15)).|((x4080.>>>(-15)))).*(461845907)).^(x4085)
      x4047 = ((((x4086.<<(13)).|((x4086.>>>(-13)))).*(5)).+(-430675100))
      val x4093 = x4047
      val x4094 = x4093.^(2)
      val x4097 = (x4094.^((x4094.>>>(16)))).*(-2048144789)
      val x4100 = (x4097.^((x4097.>>>(13)))).*(-1028477387)
      (x4100.^((x4100.>>>(16))))
    }
    override def cmp(x4104 : SEntry8_IIIITIIB , x4105 : SEntry8_IIIITIIB) = {
      val x4106 = x4104._1
      val x4107 = x4105._1
      (if((((x4106.==(x4107)).&&({
        val x4109 = x4104._2
        val x4110 = x4105._2
        (x4109.==(x4110))
      })).&&({
        val x4113 = x4104._3
        val x4114 = x4105._3
        (x4113.==(x4114))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3812 : SEntry3_III) = {
      var x3813: Int = -889275714
      val x3814 = x3812._2
      val x3816 = -862048943.*((x3814.hashCode()))
      val x3821 = x3813
      val x3822 = (((x3816.<<(15)).|((x3816.>>>(-15)))).*(461845907)).^(x3821)
      x3813 = ((((x3822.<<(13)).|((x3822.>>>(-13)))).*(5)).+(-430675100))
      val x3829 = x3812._3
      val x3831 = -862048943.*((x3829.hashCode()))
      val x3836 = x3813
      val x3837 = (((x3831.<<(15)).|((x3831.>>>(-15)))).*(461845907)).^(x3836)
      x3813 = ((((x3837.<<(13)).|((x3837.>>>(-13)))).*(5)).+(-430675100))
      val x3844 = x3813
      val x3845 = x3844.^(2)
      val x3848 = (x3845.^((x3845.>>>(16)))).*(-2048144789)
      val x3851 = (x3848.^((x3848.>>>(13)))).*(-1028477387)
      (x3851.^((x3851.>>>(16))))
    }
    override def cmp(x3855 : SEntry3_III , x3856 : SEntry3_III) = {
      val x3857 = x783.apply(x3855)
      val x3858 = x783.apply(x3856)
      val x3861 = if((x3857.>(x3858))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x3857.==(x3858))) 0 else x3861)
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4120 : SEntry8_IIIITIIB) = {
      var x4121: Int = -889275714
      val x4122 = x4120._2
      val x4124 = -862048943.*((x4122.hashCode()))
      val x4129 = x4121
      val x4130 = (((x4124.<<(15)).|((x4124.>>>(-15)))).*(461845907)).^(x4129)
      x4121 = ((((x4130.<<(13)).|((x4130.>>>(-13)))).*(5)).+(-430675100))
      val x4137 = x4120._3
      val x4139 = -862048943.*((x4137.hashCode()))
      val x4144 = x4121
      val x4145 = (((x4139.<<(15)).|((x4139.>>>(-15)))).*(461845907)).^(x4144)
      x4121 = ((((x4145.<<(13)).|((x4145.>>>(-13)))).*(5)).+(-430675100))
      val x4152 = x4120._4
      val x4154 = -862048943.*((x4152.hashCode()))
      val x4159 = x4121
      val x4160 = (((x4154.<<(15)).|((x4154.>>>(-15)))).*(461845907)).^(x4159)
      x4121 = ((((x4160.<<(13)).|((x4160.>>>(-13)))).*(5)).+(-430675100))
      val x4167 = x4121
      val x4168 = x4167.^(2)
      val x4171 = (x4168.^((x4168.>>>(16)))).*(-2048144789)
      val x4174 = (x4171.^((x4171.>>>(13)))).*(-1028477387)
      (x4174.^((x4174.>>>(16))))
    }
    override def cmp(x4178 : SEntry8_IIIITIIB , x4179 : SEntry8_IIIITIIB) = {
      val x4180 = x807.apply(x4178)
      val x4181 = x807.apply(x4179)
      val x4184 = if((x4180.>(x4181))) 
      {
        1
      }
      else
      {
        -1
      }
      
      (if((x4180.==(x4181))) 0 else x4184)
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x4008 : SEntry9_ISSSSSSDD) = {
      var x4009: Int = 0
      val x4010 = x4008._1
      val x4012 = x4009
      x4009 = ((x4012.*(1)).+((x4010.-(1))))
      val x4016 = x4009
      x4016
    }
    override def cmp(x4005 : SEntry9_ISSSSSSDD , x4006 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x4027 : SEntry5_IISDS) = {
      var x4028: Int = 0
      val x4029 = x4027._1
      val x4031 = x4028
      x4028 = ((x4031.*(100000)).+((x4029.-(1))))
      val x4035 = x4028
      x4035
    }
    override def cmp(x4024 : SEntry5_IISDS , x4025 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4272 : SEntry11_IISSSSSSDDI) = {
      var x4273: Int = 0
      val x4274 = x4272._1
      val x4276 = x4273
      x4273 = ((x4276.*(10)).+((x4274.-(1))))
      val x4280 = x4272._2
      val x4282 = x4273
      x4273 = ((x4282.*(1)).+((x4280.-(1))))
      val x4286 = x4273
      x4286
    }
    override def cmp(x4269 : SEntry11_IISSSSSSDDI , x4270 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4470 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4471: Int = 0
      val x4472 = x4470._1
      val x4474 = x4471
      x4471 = ((x4474.*(3000)).+((x4472.-(1))))
      val x4478 = x4470._2
      val x4480 = x4471
      x4471 = ((x4480.*(10)).+((x4478.-(1))))
      val x4484 = x4470._3
      val x4486 = x4471
      x4471 = ((x4486.*(1)).+((x4484.-(1))))
      val x4490 = x4471
      x4490
    }
    override def cmp(x4467 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4468 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4576 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4577: Int = 0
      val x4578 = x4576._1
      val x4580 = x4577
      x4577 = ((x4580.*(100000)).+((x4578.-(1))))
      val x4584 = x4576._2
      val x4586 = x4577
      x4577 = ((x4586.*(1)).+((x4584.-(1))))
      val x4590 = x4577
      x4590
    }
    override def cmp(x4573 : SEntry17_IIISSSSSSSSSSIIIS , x4574 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x7364 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x7838 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7214 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7835 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x7565 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7210 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x7531 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x7201 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x7328 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7862 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x7341 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x7189 = SEntry3_III(-1, -1, -1)
  val x7406 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7831 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7537 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7424 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7810 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  val x7432 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x7547 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  class DeliveryTx(x3922: Store[SEntry3_III], x4002: Store[SEntry8_IIIIITDS], x4021: Store[SEntry9_ISSSSSSDD], x4040: Store[SEntry5_IISDS], x4264: Store[SEntry8_IIIITIIB], x4291: Store[SEntry11_IISSSSSSDDI], x4463: Store[SEntry10_IIIIIITIDS], x4569: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4595: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x7189._2_=(x22)
        x7189._3_=(x12)
        val x11830 = x790.get(x7189)
        if((x11830.!=(null))) 
        {
          val x7195 = x11830._1
          val x29 = x15
          x14.update((x29.-(1)), x7195)
          x790.delete(x11830)
          x789.delete(x11830)
          val x33 = x15
          x7201._1_=(x7195)
          x7201._2_=(x33)
          x7201._3_=(x12)
          val x11844 = x813.get(x7201)
          val x7204 = x11844._4
          x11844._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x7210._1_=(x7195)
          x7210._2_=(x41)
          x7210._3_=(x12)
          x826.slice(x7210, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x7259 = x44._9
              x40 = (x46.+(x7259))
              ()
            }
          }))
          val x53 = x15
          x7214._1_=(x7204)
          x7214._2_=(x53)
          x7214._3_=(x12)
          val x11865 = x832.get(x7214)
          val x56 = x40
          x11865._17 +=(x56)
          x11865._20 +=(1)
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
      1
    }
  }
  class StockLevelTx(x3922: Store[SEntry3_III], x4002: Store[SEntry8_IIIIITDS], x4021: Store[SEntry9_ISSSSSSDD], x4040: Store[SEntry5_IISDS], x4264: Store[SEntry8_IIIITIIB], x4291: Store[SEntry11_IISSSSSSDDI], x4463: Store[SEntry10_IIIIIITIDS], x4569: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4595: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x68: Boolean, x69: Date, x70: Int, x71: Int, x72: Int, x73: Int) =     {
      x7328._1_=(x72)
      x7328._2_=(x71)
      val x11935 = x820.get(x7328)
      val x7332 = x11935._11
      var x79: Int = (x7332.-(20))
      val x80 = Set.apply[Int]()
      while({
        val x81 = x79
        (x81.<(x7332))
      })
      {
        val x83 = x79
        x7341._1_=(x83)
        x7341._2_=(x72)
        x7341._3_=(x71)
        x826.slice(x7341, ({ x86: SEntry10_IIIIIITIDS => {
            val x7363 = x86._5
            x7364._1_=(x7363)
            x7364._2_=(x71)
            val x11953 = x838.get(x7364)
            val x7366 = x11953._3
            if((x7366.<(x73))) 
            {
              val x92 = x80.+=(x7363)
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x96 = x79
        x79 = (x96.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(x3922: Store[SEntry3_III], x4002: Store[SEntry8_IIIIITDS], x4021: Store[SEntry9_ISSSSSSDD], x4040: Store[SEntry5_IISDS], x4264: Store[SEntry8_IIIITIIB], x4291: Store[SEntry11_IISSSSSSDDI], x4463: Store[SEntry10_IIIIIITIDS], x4569: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4595: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x101: Boolean, x102: Date, x103: Int, x104: Int, x105: Int, x106: Int, x107: Int, x108: String) =     {
      var x7401: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x106.>(0))) 
      {
        val x7404 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x7406._2_=(x105)
        x7406._3_=(x104)
        x7406._6_=(x108)
        x833.slice(x7406, ({ x114: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7404.append(x114)
            ()
          }
        }))
        val x118 = x7404.size
        var x120: Int = (x118./(2))
        val x121 = x7404.size
        if(((x121.%(2)).==(0))) 
        {
          val x124 = x120
          x120 = (x124.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x135 = x7404.sortWith(({ (x128: SEntry21_IIISSSSSSSSSTSDDDDIIS, x129: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7462 = x128._4
            val x7463 = x129._4
            val x132 = x7462.compareToIgnoreCase(x7463)
            (x132.<(0))
          }
        }))
        val x136 = x120
        val x7422 = x135.apply(x136)
        x7401 = x7422
        ()
      }
      else
      {
        x7424._1_=(x107)
        x7424._2_=(x105)
        x7424._3_=(x104)
        val x12031 = x832.get(x7424)
        x7401 = x12031
        ()
      }
      
      val x7429 = x7401
      val x7430 = x7429._3
      x7432._2_=(x105)
      x7432._3_=(x104)
      x7432._4_=(x7430)
      val x12041 = x814.get(x7432)
      var x154: Int = 0
      val x7437 = x12041._1
      x154 = x7437
      1
    }
  }
  class PaymentTx(x3922: Store[SEntry3_III], x4002: Store[SEntry8_IIIIITDS], x4021: Store[SEntry9_ISSSSSSDD], x4040: Store[SEntry5_IISDS], x4264: Store[SEntry8_IIIITIIB], x4291: Store[SEntry11_IISSSSSSDDI], x4463: Store[SEntry10_IIIIIITIDS], x4569: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4595: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x157: Boolean, x158: Date, x159: Int, x160: Int, x161: Int, x162: Int, x163: Int, x164: Int, x165: Int, x166: String, x167: Double) =     {
      x7531._1_=(x160)
      val x12100 = x801.get(x7531)
      x12100._9 +=(x167)
      x7537._1_=(x161)
      x7537._2_=(x160)
      val x12105 = x820.get(x7537)
      x12105._10 +=(x167)
      var x7542: SEntry21_IIISSSSSSSSSTSDDDDIIS = null
      if((x162.>(0))) 
      {
        val x7545 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x7547._2_=(x164)
        x7547._3_=(x163)
        x7547._6_=(x166)
        x833.slice(x7547, ({ x183: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7545.append(x183)
            ()
          }
        }))
        val x187 = x7545.size
        var x189: Int = (x187./(2))
        val x190 = x7545.size
        if(((x190.%(2)).==(0))) 
        {
          val x193 = x189
          x189 = (x193.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x204 = x7545.sortWith(({ (x197: SEntry21_IIISSSSSSSSSTSDDDDIIS, x198: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7649 = x197._4
            val x7650 = x198._4
            val x201 = x7649.compareToIgnoreCase(x7650)
            (x201.<(0))
          }
        }))
        val x205 = x189
        val x7563 = x204.apply(x205)
        x7542 = x7563
        ()
      }
      else
      {
        x7565._1_=(x165)
        x7565._2_=(x164)
        x7565._3_=(x163)
        val x12144 = x832.get(x7565)
        x7542 = x12144
        ()
      }
      
      val x7569 = x7542
      val x7570 = x7569._21
      var x215: String = x7570
      val x7572 = x7542
      val x7573 = x7572._14
      val x218 = x7573.contains("BC")
      if(x218) 
      {
        val x7576 = x7542
        val x7577 = x7576._1
        val x221 = x215
        val x223 = "%d %d %d %d %d $%f %s | %s".format(x7577,x164,x163,x161,x160,x167,x158,x221)
        x215 = x223
        val x225 = x215
        val x226 = x225.length
        if((x226.>(500))) 
        {
          val x228 = x215
          val x229 = x228.substring(0, 500)
          x215 = x229
          ()
        }
        else
        {
          ()
        }
        
        val x7589 = x7542
        x7589._17 +=(x167)
        val x7591 = x7542
        val x235 = x215
        x7591._21_=(x235)
        ()
      }
      else
      {
        val x7594 = x7542
        x7594._17 +=(x167)
        ()
      }
      
      val x7596 = x7542
      x833.update(x7596)
      x832.update(x7596)
      val x7598 = x12100._2
      val x7599 = x12105._3
      val x244 = x7598.length
      val x247 = if((x244.>(10))) 
      {
        val x246 = x7598.substring(0, 10)
        x246
      }
      else
      {
        x7598
      }
      
      val x248 = x247.+("    ")
      val x249 = x7599.length
      val x252 = if((x249.>(10))) 
      {
        val x251 = x7599.substring(0, 10)
        x251
      }
      else
      {
        x7599
      }
      
      val x253 = x248.+(x252)
      val x7610 = x7542
      val x7611 = x7610._1
      x4002.insert((SEntry8_IIIIITDS(x7611, x164, x163, x161, x160, x158, x167, x253)))
      1
    }
  }
  class NewOrderTx(x3922: Store[SEntry3_III], x4002: Store[SEntry8_IIIIITDS], x4021: Store[SEntry9_ISSSSSSDD], x4040: Store[SEntry5_IISDS], x4264: Store[SEntry8_IIIITIIB], x4291: Store[SEntry11_IISSSSSSDDI], x4463: Store[SEntry10_IIIIIITIDS], x4569: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4595: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x259: Boolean, x260: Date, x261: Int, x262: Int, x263: Int, x264: Int, x265: Int, x266: Int, x267: Array[Int], x268: Array[Int], x269: Array[Int], x270: Array[Double], x271: Array[String], x272: Array[Int], x273: Array[String], x274: Array[Double]) =     {
      var x275: Int = 0
      var x276: Boolean = false
      val x277 = new Array[String](x265)
      var x278: Boolean = true
      while({
        val x279 = x275
        ((x279.<(x265)).&&({
          val x281 = x278
          x281
        }))
      })
      {
        val x283 = x275
        val x284 = x267.apply(x283)
        x7810._1_=(x284)
        val x12303 = x806.get(x7810)
        if((x12303.==(null))) 
        {
          x278 = false
          ()
        }
        else
        {
          val x290 = x275
          val x7818 = x12303._3
          x271.update(x290, x7818)
          val x293 = x275
          val x7821 = x12303._4
          x270.update(x293, x7821)
          val x296 = x275
          val x7824 = x12303._5
          x277.update(x296, x7824)
          ()
        }
        
        val x300 = x275
        x275 = (x300.+(1))
        ()
      }
      val x304 = x278
      if(x304) 
      {
        x7831._1_=(x264)
        x7831._2_=(x263)
        x7831._3_=(x262)
        val x12326 = x832.get(x7831)
        x7835._1_=(x262)
        val x12329 = x801.get(x7835)
        x7838._1_=(x263)
        x7838._2_=(x262)
        val x12333 = x820.get(x7838)
        val x7841 = x12333._11
        x12333._11 +=(1)
        x4264.insert((SEntry8_IIIITIIB(x7841, x263, x262, x264, x260, -1, x265, (x266.>(0)))))
        x3922.insert((SEntry3_III(x7841, x263, x262)))
        var x324: Double = 0.0
        x275 = 0
        while({
          val x326 = x275
          (x326.<(x265))
        })
        {
          val x328 = x275
          val x329 = x268.apply(x328)
          val x330 = x275
          val x331 = x267.apply(x330)
          val x332 = x275
          val x333 = x269.apply(x332)
          x7862._1_=(x331)
          x7862._2_=(x329)
          val x12356 = x838.get(x7862)
          val x363 = if((x263.==(1))) 
          {
            val x7866 = x12356._4
            x7866
          }
          else
          {
            val x362 = if((x263.==(2))) 
            {
              val x7869 = x12356._5
              x7869
            }
            else
            {
              val x361 = if((x263.==(3))) 
              {
                val x7872 = x12356._6
                x7872
              }
              else
              {
                val x360 = if((x263.==(4))) 
                {
                  val x7875 = x12356._7
                  x7875
                }
                else
                {
                  val x359 = if((x263.==(5))) 
                  {
                    val x7878 = x12356._8
                    x7878
                  }
                  else
                  {
                    val x358 = if((x263.==(6))) 
                    {
                      val x7881 = x12356._9
                      x7881
                    }
                    else
                    {
                      val x357 = if((x263.==(7))) 
                      {
                        val x7884 = x12356._10
                        x7884
                      }
                      else
                      {
                        val x356 = if((x263.==(8))) 
                        {
                          val x7887 = x12356._11
                          x7887
                        }
                        else
                        {
                          val x355 = if((x263.==(9))) 
                          {
                            val x7890 = x12356._12
                            x7890
                          }
                          else
                          {
                            val x7891 = x12356._13
                            x7891
                          }
                          
                          x355
                        }
                        
                        x356
                      }
                      
                      x357
                    }
                    
                    x358
                  }
                  
                  x359
                }
                
                x360
              }
              
              x361
            }
            
            x362
          }
          
          val x7892 = x12356._3
          val x365 = x275
          x272.update(x365, x7892)
          val x7895 = x12326._14
          val x368 = x7895.contains("original")
          if((x368.&&({
            val x7898 = x12356._17
            val x370 = x7898.contains("original")
            x370
          }))) 
          {
            val x372 = x275
            x273.update(x372, "B")
            ()
          }
          else
          {
            val x374 = x275
            x273.update(x374, "G")
            ()
          }
          
          x12356._3_=((x7892.-(x333)))
          if((x7892.<=(x333))) 
          {
            x12356._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x382: Int = 0
          if((x329.!=(x262))) 
          {
            x382 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x7915 = x12326._16
          val x7916 = x12329._8
          val x7917 = x12333._9
          val x390 = x275
          val x391 = x270.apply(x390)
          val x398 = (((x333.toDouble).*(x391)).*(((1.0.+(x7916)).+(x7917)))).*((1.0.-(x7915)))
          val x399 = x275
          x274.update(x399, x398)
          val x401 = x324
          x324 = (x401.+(x398))
          val x404 = x275
          x4463.insert((SEntry10_IIIIIITIDS(x7841, x263, x262, (x404.+(1)), x331, x329, null, x333, x398, x363)))
          val x409 = x275
          x275 = (x409.+(1))
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
