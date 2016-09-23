
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
  val x3615 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x3616 = new Store[SEntry3_III](3, x3615)
  val x721 = x3616.index(0, IHash, true, -1)
  val x722 = x3616.index(1, ISliceHeapMin, false, 2)
  val x723 = x3616.index(2, INone, false, -1)
  val x3695 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x3696 = new Store[SEntry8_IIIIITDS](1, x3695)
  val x728 = x3696.index(0, IList, false, -1)
  val x3714 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x3715 = new Store[SEntry9_ISSSSSSDD](1, x3714)
  val x733 = x3715.index(0, IDirect, true, 1)
  val x3733 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x3734 = new Store[SEntry5_IISDS](1, x3733)
  val x738 = x3734.index(0, IDirect, true, 100000)
  val x3957 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x3958 = new Store[SEntry8_IIIITIIB](3, x3957)
  val x745 = x3958.index(0, IHash, true, -1)
  val x746 = x3958.index(1, ISliceHeapMax, false, 2)
  val x747 = x3958.index(2, INone, false, -1)
  val x3984 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x3985 = new Store[SEntry11_IISSSSSSDDI](1, x3984)
  val x752 = x3985.index(0, IDirect, true, 10)
  val x4156 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x4157 = new Store[SEntry10_IIIIIITIDS](2, x4156)
  val x757 = x4157.index(0, IHash, true, -1)
  val x758 = x4157.index(1, IHash, false, -1)
  val x4262 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x4263 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4262)
  val x764 = x4263.index(0, IDirect, true, 30000)
  val x765 = x4263.index(1, IHash, false, -1)
  val x4288 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x4289 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4288)
  val x770 = x4289.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x3616
  val historyTbl = x3696
  val warehouseTbl = x3715
  val itemTbl = x3734
  val orderTbl = x3958
  val districtTbl = x3985
  val orderLineTbl = x4157
  val customerTbl = x4263
  val stockTbl = x4289
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x3988 : SEntry10_IIIIIITIDS) = {
      var x3989: Int = -889275714
      val x3990 = x3988._1
      val x3992 = -862048943.*((x3990.hashCode()))
      val x3997 = x3989
      val x3998 = (((x3992.<<(15)).|((x3992.>>>(-15)))).*(461845907)).^(x3997)
      x3989 = ((((x3998.<<(13)).|((x3998.>>>(-13)))).*(5)).+(-430675100))
      val x4005 = x3988._2
      val x4007 = -862048943.*((x4005.hashCode()))
      val x4012 = x3989
      val x4013 = (((x4007.<<(15)).|((x4007.>>>(-15)))).*(461845907)).^(x4012)
      x3989 = ((((x4013.<<(13)).|((x4013.>>>(-13)))).*(5)).+(-430675100))
      val x4020 = x3988._3
      val x4022 = -862048943.*((x4020.hashCode()))
      val x4027 = x3989
      val x4028 = (((x4022.<<(15)).|((x4022.>>>(-15)))).*(461845907)).^(x4027)
      x3989 = ((((x4028.<<(13)).|((x4028.>>>(-13)))).*(5)).+(-430675100))
      val x4035 = x3988._4
      val x4037 = -862048943.*((x4035.hashCode()))
      val x4042 = x3989
      val x4043 = (((x4037.<<(15)).|((x4037.>>>(-15)))).*(461845907)).^(x4042)
      x3989 = ((((x4043.<<(13)).|((x4043.>>>(-13)))).*(5)).+(-430675100))
      val x4050 = x3989
      val x4051 = x4050.^(2)
      val x4054 = (x4051.^((x4051.>>>(16)))).*(-2048144789)
      val x4057 = (x4054.^((x4054.>>>(13)))).*(-1028477387)
      (x4057.^((x4057.>>>(16))))
    }
    override def cmp(x4061 : SEntry10_IIIIIITIDS , x4062 : SEntry10_IIIIIITIDS) = {
      val x4063 = x4061._1
      val x4064 = x4062._1
      (if(((((x4063.==(x4064)).&&({
        val x4066 = x4061._2
        val x4067 = x4062._2
        (x4066.==(x4067))
      })).&&({
        val x4070 = x4061._3
        val x4071 = x4062._3
        (x4070.==(x4071))
      })).&&({
        val x4074 = x4061._4
        val x4075 = x4062._4
        (x4074.==(x4075))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3882 : SEntry8_IIIITIIB) = {
      var x3883: Int = -889275714
      val x3884 = x3882._2
      val x3886 = -862048943.*((x3884.hashCode()))
      val x3891 = x3883
      val x3892 = (((x3886.<<(15)).|((x3886.>>>(-15)))).*(461845907)).^(x3891)
      x3883 = ((((x3892.<<(13)).|((x3892.>>>(-13)))).*(5)).+(-430675100))
      val x3899 = x3882._3
      val x3901 = -862048943.*((x3899.hashCode()))
      val x3906 = x3883
      val x3907 = (((x3901.<<(15)).|((x3901.>>>(-15)))).*(461845907)).^(x3906)
      x3883 = ((((x3907.<<(13)).|((x3907.>>>(-13)))).*(5)).+(-430675100))
      val x3914 = x3882._4
      val x3916 = -862048943.*((x3914.hashCode()))
      val x3921 = x3883
      val x3922 = (((x3916.<<(15)).|((x3916.>>>(-15)))).*(461845907)).^(x3921)
      x3883 = ((((x3922.<<(13)).|((x3922.>>>(-13)))).*(5)).+(-430675100))
      val x3929 = x3883
      val x3930 = x3929.^(2)
      val x3933 = (x3930.^((x3930.>>>(16)))).*(-2048144789)
      val x3936 = (x3933.^((x3933.>>>(13)))).*(-1028477387)
      (x3936.^((x3936.>>>(16))))
    }
    override def cmp(x3940 : SEntry8_IIIITIIB , x3941 : SEntry8_IIIITIIB) = {
      val x3942 = x3940._2
      val x3943 = x3941._2
      (if((((x3942.==(x3943)).&&({
        val x3945 = x3940._3
        val x3946 = x3941._3
        (x3945.==(x3946))
      })).&&({
        val x3949 = x3940._4
        val x3950 = x3941._4
        (x3949.==(x3950))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3432 : SEntry3_III) = {
      var x3433: Int = -889275714
      val x3434 = x3432._1
      val x3436 = -862048943.*((x3434.hashCode()))
      val x3441 = x3433
      val x3442 = (((x3436.<<(15)).|((x3436.>>>(-15)))).*(461845907)).^(x3441)
      x3433 = ((((x3442.<<(13)).|((x3442.>>>(-13)))).*(5)).+(-430675100))
      val x3449 = x3432._2
      val x3451 = -862048943.*((x3449.hashCode()))
      val x3456 = x3433
      val x3457 = (((x3451.<<(15)).|((x3451.>>>(-15)))).*(461845907)).^(x3456)
      x3433 = ((((x3457.<<(13)).|((x3457.>>>(-13)))).*(5)).+(-430675100))
      val x3464 = x3432._3
      val x3466 = -862048943.*((x3464.hashCode()))
      val x3471 = x3433
      val x3472 = (((x3466.<<(15)).|((x3466.>>>(-15)))).*(461845907)).^(x3471)
      x3433 = ((((x3472.<<(13)).|((x3472.>>>(-13)))).*(5)).+(-430675100))
      val x3479 = x3433
      val x3480 = x3479.^(2)
      val x3483 = (x3480.^((x3480.>>>(16)))).*(-2048144789)
      val x3486 = (x3483.^((x3483.>>>(13)))).*(-1028477387)
      (x3486.^((x3486.>>>(16))))
    }
    override def cmp(x3490 : SEntry3_III , x3491 : SEntry3_III) = {
      val x3492 = x3490._1
      val x3493 = x3491._1
      (if((((x3492.==(x3493)).&&({
        val x3495 = x3490._2
        val x3496 = x3491._2
        (x3495.==(x3496))
      })).&&({
        val x3499 = x3490._3
        val x3500 = x3491._3
        (x3499.==(x3500))
      }))) 0 else 1)
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4081 : SEntry10_IIIIIITIDS) = {
      var x4082: Int = -889275714
      val x4083 = x4081._1
      val x4085 = -862048943.*((x4083.hashCode()))
      val x4090 = x4082
      val x4091 = (((x4085.<<(15)).|((x4085.>>>(-15)))).*(461845907)).^(x4090)
      x4082 = ((((x4091.<<(13)).|((x4091.>>>(-13)))).*(5)).+(-430675100))
      val x4098 = x4081._2
      val x4100 = -862048943.*((x4098.hashCode()))
      val x4105 = x4082
      val x4106 = (((x4100.<<(15)).|((x4100.>>>(-15)))).*(461845907)).^(x4105)
      x4082 = ((((x4106.<<(13)).|((x4106.>>>(-13)))).*(5)).+(-430675100))
      val x4113 = x4081._3
      val x4115 = -862048943.*((x4113.hashCode()))
      val x4120 = x4082
      val x4121 = (((x4115.<<(15)).|((x4115.>>>(-15)))).*(461845907)).^(x4120)
      x4082 = ((((x4121.<<(13)).|((x4121.>>>(-13)))).*(5)).+(-430675100))
      val x4128 = x4082
      val x4129 = x4128.^(2)
      val x4132 = (x4129.^((x4129.>>>(16)))).*(-2048144789)
      val x4135 = (x4132.^((x4132.>>>(13)))).*(-1028477387)
      (x4135.^((x4135.>>>(16))))
    }
    override def cmp(x4139 : SEntry10_IIIIIITIDS , x4140 : SEntry10_IIIIIITIDS) = {
      val x4141 = x4139._1
      val x4142 = x4140._1
      (if((((x4141.==(x4142)).&&({
        val x4144 = x4139._2
        val x4145 = x4140._2
        (x4144.==(x4145))
      })).&&({
        val x4148 = x4139._3
        val x4149 = x4140._3
        (x4148.==(x4149))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3559 : SEntry3_III) = {
      var x3560: Int = -889275714
      val x3561 = x3559._2
      val x3563 = -862048943.*((x3561.hashCode()))
      val x3568 = x3560
      val x3569 = (((x3563.<<(15)).|((x3563.>>>(-15)))).*(461845907)).^(x3568)
      x3560 = ((((x3569.<<(13)).|((x3569.>>>(-13)))).*(5)).+(-430675100))
      val x3576 = x3559._3
      val x3578 = -862048943.*((x3576.hashCode()))
      val x3583 = x3560
      val x3584 = (((x3578.<<(15)).|((x3578.>>>(-15)))).*(461845907)).^(x3583)
      x3560 = ((((x3584.<<(13)).|((x3584.>>>(-13)))).*(5)).+(-430675100))
      val x3591 = x3560
      val x3592 = x3591.^(2)
      val x3595 = (x3592.^((x3592.>>>(16)))).*(-2048144789)
      val x3598 = (x3595.^((x3595.>>>(13)))).*(-1028477387)
      (x3598.^((x3598.>>>(16))))
    }
    override def cmp(x3602 : SEntry3_III , x3603 : SEntry3_III) = {
      val x3604 = x3602._2
      val x3605 = x3603._2
      (if(((x3604.==(x3605)).&&({
        val x3607 = x3602._3
        val x3608 = x3603._3
        (x3607.==(x3608))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3621 : SEntry8_IIIIITDS) = {
      var x3622: Int = -889275714
      val x3623 = x3622
      val x3624 = x3623.^(2)
      val x3627 = (x3624.^((x3624.>>>(16)))).*(-2048144789)
      val x3630 = (x3627.^((x3627.>>>(13)))).*(-1028477387)
      (x3630.^((x3630.>>>(16))))
    }
    override def cmp(x3634 : SEntry8_IIIIITDS , x3635 : SEntry8_IIIIITDS) = {
      val x3636 = x3634._1
      val x3637 = x3635._1
      (if((((((((((x3636.==(-1)).||({
        (x3637.==(-1))
      })).||({
        (x3636.==(x3637))
      })).&&({
        val x3643 = x3634._2
        val x3644 = x3635._2
        (((x3643.==(-1)).||({
          (x3644.==(-1))
        })).||({
          (x3643.==(x3644))
        }))
      })).&&({
        val x3651 = x3634._3
        val x3652 = x3635._3
        (((x3651.==(-1)).||({
          (x3652.==(-1))
        })).||({
          (x3651.==(x3652))
        }))
      })).&&({
        val x3659 = x3634._4
        val x3660 = x3635._4
        (((x3659.==(-1)).||({
          (x3660.==(-1))
        })).||({
          (x3659.==(x3660))
        }))
      })).&&({
        val x3667 = x3634._5
        val x3668 = x3635._5
        (((x3667.==(-1)).||({
          (x3668.==(-1))
        })).||({
          (x3667.==(x3668))
        }))
      })).&&({
        val x3675 = x3634._6
        val x3676 = x3635._6
        (((x3675.==(null)).||({
          (x3676.==(null))
        })).||({
          (x3675.==(x3676))
        }))
      })).&&({
        val x3683 = x3634._7
        val x3684 = x3635._7
        (((x3683.==(-1.0)).||({
          (x3684.==(-1.0))
        })).||({
          (x3683.==(x3684))
        }))
      }))) 0 else 1)
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4187 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4188: Int = -889275714
      val x4189 = x4187._2
      val x4191 = -862048943.*((x4189.hashCode()))
      val x4196 = x4188
      val x4197 = (((x4191.<<(15)).|((x4191.>>>(-15)))).*(461845907)).^(x4196)
      x4188 = ((((x4197.<<(13)).|((x4197.>>>(-13)))).*(5)).+(-430675100))
      val x4204 = x4187._3
      val x4206 = -862048943.*((x4204.hashCode()))
      val x4211 = x4188
      val x4212 = (((x4206.<<(15)).|((x4206.>>>(-15)))).*(461845907)).^(x4211)
      x4188 = ((((x4212.<<(13)).|((x4212.>>>(-13)))).*(5)).+(-430675100))
      val x4219 = x4187._6
      val x4221 = -862048943.*((x4219.hashCode()))
      val x4226 = x4188
      val x4227 = (((x4221.<<(15)).|((x4221.>>>(-15)))).*(461845907)).^(x4226)
      x4188 = ((((x4227.<<(13)).|((x4227.>>>(-13)))).*(5)).+(-430675100))
      val x4234 = x4188
      val x4235 = x4234.^(2)
      val x4238 = (x4235.^((x4235.>>>(16)))).*(-2048144789)
      val x4241 = (x4238.^((x4238.>>>(13)))).*(-1028477387)
      (x4241.^((x4241.>>>(16))))
    }
    override def cmp(x4245 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4246 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4247 = x4245._2
      val x4248 = x4246._2
      (if((((x4247.==(x4248)).&&({
        val x4250 = x4245._3
        val x4251 = x4246._3
        (x4250.==(x4251))
      })).&&({
        val x4254 = x4245._6
        val x4255 = x4246._6
        (x4254.==(x4255))
      }))) 0 else 1)
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3740 : SEntry8_IIIITIIB) = {
      var x3741: Int = -889275714
      val x3742 = x3740._1
      val x3744 = -862048943.*((x3742.hashCode()))
      val x3749 = x3741
      val x3750 = (((x3744.<<(15)).|((x3744.>>>(-15)))).*(461845907)).^(x3749)
      x3741 = ((((x3750.<<(13)).|((x3750.>>>(-13)))).*(5)).+(-430675100))
      val x3757 = x3740._2
      val x3759 = -862048943.*((x3757.hashCode()))
      val x3764 = x3741
      val x3765 = (((x3759.<<(15)).|((x3759.>>>(-15)))).*(461845907)).^(x3764)
      x3741 = ((((x3765.<<(13)).|((x3765.>>>(-13)))).*(5)).+(-430675100))
      val x3772 = x3740._3
      val x3774 = -862048943.*((x3772.hashCode()))
      val x3779 = x3741
      val x3780 = (((x3774.<<(15)).|((x3774.>>>(-15)))).*(461845907)).^(x3779)
      x3741 = ((((x3780.<<(13)).|((x3780.>>>(-13)))).*(5)).+(-430675100))
      val x3787 = x3741
      val x3788 = x3787.^(2)
      val x3791 = (x3788.^((x3788.>>>(16)))).*(-2048144789)
      val x3794 = (x3791.^((x3791.>>>(13)))).*(-1028477387)
      (x3794.^((x3794.>>>(16))))
    }
    override def cmp(x3798 : SEntry8_IIIITIIB , x3799 : SEntry8_IIIITIIB) = {
      val x3800 = x3798._1
      val x3801 = x3799._1
      (if((((x3800.==(x3801)).&&({
        val x3803 = x3798._2
        val x3804 = x3799._2
        (x3803.==(x3804))
      })).&&({
        val x3807 = x3798._3
        val x3808 = x3799._3
        (x3807.==(x3808))
      }))) 0 else 1)
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3506 : SEntry3_III) = {
      var x3507: Int = -889275714
      val x3508 = x3506._2
      val x3510 = -862048943.*((x3508.hashCode()))
      val x3515 = x3507
      val x3516 = (((x3510.<<(15)).|((x3510.>>>(-15)))).*(461845907)).^(x3515)
      x3507 = ((((x3516.<<(13)).|((x3516.>>>(-13)))).*(5)).+(-430675100))
      val x3523 = x3506._3
      val x3525 = -862048943.*((x3523.hashCode()))
      val x3530 = x3507
      val x3531 = (((x3525.<<(15)).|((x3525.>>>(-15)))).*(461845907)).^(x3530)
      x3507 = ((((x3531.<<(13)).|((x3531.>>>(-13)))).*(5)).+(-430675100))
      val x3538 = x3507
      val x3539 = x3538.^(2)
      val x3542 = (x3539.^((x3539.>>>(16)))).*(-2048144789)
      val x3545 = (x3542.^((x3542.>>>(13)))).*(-1028477387)
      (x3545.^((x3545.>>>(16))))
    }
    override def cmp(x3549 : SEntry3_III , x3550 : SEntry3_III) = {
      val x3551 = x3549._1
      val x3552 = x3550._1
      (if((x3551.==(x3552))) 0 else (if((x3551.>(x3552))) 1 else -1))
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3814 : SEntry8_IIIITIIB) = {
      var x3815: Int = -889275714
      val x3816 = x3814._2
      val x3818 = -862048943.*((x3816.hashCode()))
      val x3823 = x3815
      val x3824 = (((x3818.<<(15)).|((x3818.>>>(-15)))).*(461845907)).^(x3823)
      x3815 = ((((x3824.<<(13)).|((x3824.>>>(-13)))).*(5)).+(-430675100))
      val x3831 = x3814._3
      val x3833 = -862048943.*((x3831.hashCode()))
      val x3838 = x3815
      val x3839 = (((x3833.<<(15)).|((x3833.>>>(-15)))).*(461845907)).^(x3838)
      x3815 = ((((x3839.<<(13)).|((x3839.>>>(-13)))).*(5)).+(-430675100))
      val x3846 = x3814._4
      val x3848 = -862048943.*((x3846.hashCode()))
      val x3853 = x3815
      val x3854 = (((x3848.<<(15)).|((x3848.>>>(-15)))).*(461845907)).^(x3853)
      x3815 = ((((x3854.<<(13)).|((x3854.>>>(-13)))).*(5)).+(-430675100))
      val x3861 = x3815
      val x3862 = x3861.^(2)
      val x3865 = (x3862.^((x3862.>>>(16)))).*(-2048144789)
      val x3868 = (x3865.^((x3865.>>>(13)))).*(-1028477387)
      (x3868.^((x3868.>>>(16))))
    }
    override def cmp(x3872 : SEntry8_IIIITIIB , x3873 : SEntry8_IIIITIIB) = {
      val x3874 = x3872._1
      val x3875 = x3873._1
      (if((x3874.==(x3875))) 0 else (if((x3874.>(x3875))) 1 else -1))
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3702 : SEntry9_ISSSSSSDD) = {
      var x3703: Int = 0
      val x3704 = x3702._1
      val x3706 = x3703
      x3703 = ((x3706.*(1)).+((x3704.-(1))))
      val x3710 = x3703
      x3710
    }
    override def cmp(x3699 : SEntry9_ISSSSSSDD , x3700 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3721 : SEntry5_IISDS) = {
      var x3722: Int = 0
      val x3723 = x3721._1
      val x3725 = x3722
      x3722 = ((x3725.*(100000)).+((x3723.-(1))))
      val x3729 = x3722
      x3729
    }
    override def cmp(x3718 : SEntry5_IISDS , x3719 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x3966 : SEntry11_IISSSSSSDDI) = {
      var x3967: Int = 0
      val x3968 = x3966._1
      val x3970 = x3967
      x3967 = ((x3970.*(10)).+((x3968.-(1))))
      val x3974 = x3966._2
      val x3976 = x3967
      x3967 = ((x3976.*(1)).+((x3974.-(1))))
      val x3980 = x3967
      x3980
    }
    override def cmp(x3963 : SEntry11_IISSSSSSDDI , x3964 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4164 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4165: Int = 0
      val x4166 = x4164._1
      val x4168 = x4165
      x4165 = ((x4168.*(3000)).+((x4166.-(1))))
      val x4172 = x4164._2
      val x4174 = x4165
      x4165 = ((x4174.*(10)).+((x4172.-(1))))
      val x4178 = x4164._3
      val x4180 = x4165
      x4165 = ((x4180.*(1)).+((x4178.-(1))))
      val x4184 = x4165
      x4184
    }
    override def cmp(x4161 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4162 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4270 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4271: Int = 0
      val x4272 = x4270._1
      val x4274 = x4271
      x4271 = ((x4274.*(100000)).+((x4272.-(1))))
      val x4278 = x4270._2
      val x4280 = x4271
      x4271 = ((x4280.*(1)).+((x4278.-(1))))
      val x4284 = x4271
      x4284
    }
    override def cmp(x4267 : SEntry17_IIISSSSSSSSSSIIIS , x4268 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x6883 = SEntry3_III(-1, -1, -1)
  val x7035 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x7219 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7427 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x7402 = SEntry5_IISDS(-1, -1, null, -1.0, null)
  val x7122 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  val x7454 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x7116 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7245 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7228 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7099 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x6904 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null)
  val x7058 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null)
  val x6908 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7022 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x7213 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0)
  val x7423 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null)
  val x7430 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1)
  val x6895 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false)
  class DeliveryTx(x3616: Store[SEntry3_III], x3696: Store[SEntry8_IIIIITDS], x3715: Store[SEntry9_ISSSSSSDD], x3734: Store[SEntry5_IISDS], x3958: Store[SEntry8_IIIITIIB], x3985: Store[SEntry11_IISSSSSSDDI], x4157: Store[SEntry10_IIIIIITIDS], x4263: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4289: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        x6883._2_=(x22)
        x6883._3_=(x12)
        val x11387 = x722.get(x6883)
        if((x11387.!=(null))) 
        {
          val x6889 = x11387._1
          val x29 = x15
          x14.update((x29.-(1)), x6889)
          x722.delete(x11387)
          x721.delete(x11387)
          val x33 = x15
          x6895._1_=(x6889)
          x6895._2_=(x33)
          x6895._3_=(x12)
          val x11401 = x745.get(x6895)
          val x6898 = x11401._4
          x11401._6_=(x13)
          var x40: Double = 0.0
          val x41 = x15
          x6904._1_=(x6889)
          x6904._2_=(x41)
          x6904._3_=(x12)
          x758.slice(x6904, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40
              val x6953 = x44._9
              x40 = (x46.+(x6953))
              ()
            }
          }))
          val x53 = x15
          x6908._1_=(x6898)
          x6908._2_=(x53)
          x6908._3_=(x12)
          val x11422 = x764.get(x6908)
          val x56 = x40
          x11422._17 +=(x56)
          x11422._20 +=(1)
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
  class StockLevelTx(x3616: Store[SEntry3_III], x3696: Store[SEntry8_IIIIITDS], x3715: Store[SEntry9_ISSSSSSDD], x3734: Store[SEntry5_IISDS], x3958: Store[SEntry8_IIIITIIB], x3985: Store[SEntry11_IISSSSSSDDI], x4157: Store[SEntry10_IIIIIITIDS], x4263: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4289: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x68: Boolean, x69: Date, x70: Int, x71: Int, x72: Int, x73: Int) =     {
      x7022._1_=(x72)
      x7022._2_=(x71)
      val x11492 = x752.get(x7022)
      val x7026 = x11492._11
      var x79: Int = (x7026.-(20))
      val x80 = Set.apply[Int]()
      while({
        val x81 = x79
        (x81.<(x7026))
      })
      {
        val x83 = x79
        x7035._1_=(x83)
        x7035._2_=(x72)
        x7035._3_=(x71)
        x758.slice(x7035, ({ x86: SEntry10_IIIIIITIDS => {
            val x7057 = x86._5
            x7058._1_=(x7057)
            x7058._2_=(x71)
            val x11510 = x770.get(x7058)
            val x7060 = x11510._3
            if((x7060.<(x73))) 
            {
              val x92 = x80.+=(x7057)
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
  class OrderStatusTx(x3616: Store[SEntry3_III], x3696: Store[SEntry8_IIIIITDS], x3715: Store[SEntry9_ISSSSSSDD], x3734: Store[SEntry5_IISDS], x3958: Store[SEntry8_IIIITIIB], x3985: Store[SEntry11_IISSSSSSDDI], x4157: Store[SEntry10_IIIIIITIDS], x4263: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4289: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x101: Boolean, x102: Date, x103: Int, x104: Int, x105: Int, x106: Int, x107: Int, x108: String) =     {
      val x140 = if((x106.>(0))) 
      {
        val x7097 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x7099._2_=(x105)
        x7099._3_=(x104)
        x7099._6_=(x108)
        x765.slice(x7099, ({ x113: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7097.append(x113)
            ()
          }
        }))
        val x117 = x7097.size
        var x119: Int = (x117./(2))
        val x120 = x7097.size
        if(((x120.%(2)).==(0))) 
        {
          val x123 = x119
          x119 = (x123.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x134 = x7097.sortWith(({ (x127: SEntry21_IIISSSSSSSSSTSDDDDIIS, x128: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7151 = x127._4
            val x7152 = x128._4
            val x131 = x7151.compareToIgnoreCase(x7152)
            (x131.<(0))
          }
        }))
        val x135 = x119
        val x7115 = x134.apply(x135)
        x7115
      }
      else
      {
        x7116._1_=(x107)
        x7116._2_=(x105)
        x7116._3_=(x104)
        val x11586 = x764.get(x7116)
        x11586
      }
      
      val x7120 = x140._3
      x7122._2_=(x105)
      x7122._3_=(x104)
      x7122._4_=(x7120)
      val x11594 = x746.get(x7122)
      var x150: Int = 0
      val x7127 = x11594._1
      x150 = x7127
      1
    }
  }
  class PaymentTx(x3616: Store[SEntry3_III], x3696: Store[SEntry8_IIIIITDS], x3715: Store[SEntry9_ISSSSSSDD], x3734: Store[SEntry5_IISDS], x3958: Store[SEntry8_IIIITIIB], x3985: Store[SEntry11_IISSSSSSDDI], x4157: Store[SEntry10_IIIIIITIDS], x4263: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4289: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x153: Boolean, x154: Date, x155: Int, x156: Int, x157: Int, x158: Int, x159: Int, x160: Int, x161: Int, x162: String, x163: Double) =     {
      x7213._1_=(x156)
      val x11649 = x733.get(x7213)
      x11649._9 +=(x163)
      x7219._1_=(x157)
      x7219._2_=(x156)
      val x11654 = x752.get(x7219)
      x11654._10 +=(x163)
      val x205 = if((x158.>(0))) 
      {
        val x7226 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]()
        x7228._2_=(x160)
        x7228._3_=(x159)
        x7228._6_=(x162)
        x765.slice(x7228, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7226.append(x178)
            ()
          }
        }))
        val x182 = x7226.size
        var x184: Int = (x182./(2))
        val x185 = x7226.size
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
        
        val x199 = x7226.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7300 = x192._4
            val x7301 = x193._4
            val x196 = x7300.compareToIgnoreCase(x7301)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x7244 = x199.apply(x200)
        x7244
      }
      else
      {
        x7245._1_=(x161)
        x7245._2_=(x160)
        x7245._3_=(x159)
        val x11691 = x764.get(x7245)
        x11691
      }
      
      val x7248 = x205._21
      val x7249 = x205._14
      val x208 = x7249.contains("BC")
      if(x208) 
      {
        val x7252 = x205._1
        var x211 = "%d %d %d %d %d $%f %s | %s".format(x7252,x160,x159,x157,x156,x163,x154,x7248)
        if(x211.size > 500) 
          x211 = x211.substring(0, 500)
        x205._17 +=(x163)
        x205._21_=(x211)
        ()
      }
      else
      {
        x205._17 +=(x163)
        ()
      }
      
      val x7259 = x11649._2
      val x7260 = x11654._3
      var x220 = "%.10s    %.10s".format(x7259,x7260)
      if(x220.size > 24) 
        x220 = x220.substring(0, 24)
      val x7263 = x205._1
      x3696.insert((SEntry8_IIIIITDS(x7263, x160, x159, x157, x156, x154, x163, x220)))
      1
    }
  }
  class NewOrderTx(x3616: Store[SEntry3_III], x3696: Store[SEntry8_IIIIITDS], x3715: Store[SEntry9_ISSSSSSDD], x3734: Store[SEntry5_IISDS], x3958: Store[SEntry8_IIIITIIB], x3985: Store[SEntry11_IISSSSSSDDI], x4157: Store[SEntry10_IIIIIITIDS], x4263: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4289: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x225: Boolean, x226: Date, x227: Int, x228: Int, x229: Int, x230: Int, x231: Int, x232: Int, x233: Array[Int], x234: Array[Int], x235: Array[Int], x236: Array[Double], x237: Array[String], x238: Array[Int], x239: Array[String], x240: Array[Double]) =     {
      var x241: Int = 0
      var x242: Boolean = false
      val x243 = new Array[String](x231)
      var x244: Boolean = true
      while({
        val x245 = x241
        ((x245.<(x231)).&&({
          val x247 = x244
          x247
        }))
      })
      {
        val x249 = x241
        val x250 = x233.apply(x249)
        x7402._1_=(x250)
        val x11788 = x738.get(x7402)
        if((x11788.==(null))) 
        {
          x244 = false
          ()
        }
        else
        {
          val x256 = x241
          val x7410 = x11788._3
          x237.update(x256, x7410)
          val x259 = x241
          val x7413 = x11788._4
          x236.update(x259, x7413)
          val x262 = x241
          val x7416 = x11788._5
          x243.update(x262, x7416)
          ()
        }
        
        val x266 = x241
        x241 = (x266.+(1))
        ()
      }
      val x270 = x244
      if(x270) 
      {
        x7423._1_=(x230)
        x7423._2_=(x229)
        x7423._3_=(x228)
        val x11811 = x764.get(x7423)
        x7427._1_=(x228)
        val x11814 = x733.get(x7427)
        x7430._1_=(x229)
        x7430._2_=(x228)
        val x11818 = x752.get(x7430)
        val x7433 = x11818._11
        x11818._11 +=(1)
        x3958.insert((SEntry8_IIIITIIB(x7433, x229, x228, x230, x226, -1, x231, (x232.>(0)))))
        x3616.insert((SEntry3_III(x7433, x229, x228)))
        var x290: Double = 0.0
        x241 = 0
        while({
          val x292 = x241
          (x292.<(x231))
        })
        {
          val x294 = x241
          val x295 = x234.apply(x294)
          val x296 = x241
          val x297 = x233.apply(x296)
          val x298 = x241
          val x299 = x235.apply(x298)
          x7454._1_=(x297)
          x7454._2_=(x295)
          val x11841 = x770.get(x7454)
          val x329 = if((x229.==(1))) 
          {
            val x7458 = x11841._4
            x7458
          }
          else
          {
            val x328 = if((x229.==(2))) 
            {
              val x7461 = x11841._5
              x7461
            }
            else
            {
              val x327 = if((x229.==(3))) 
              {
                val x7464 = x11841._6
                x7464
              }
              else
              {
                val x326 = if((x229.==(4))) 
                {
                  val x7467 = x11841._7
                  x7467
                }
                else
                {
                  val x325 = if((x229.==(5))) 
                  {
                    val x7470 = x11841._8
                    x7470
                  }
                  else
                  {
                    val x324 = if((x229.==(6))) 
                    {
                      val x7473 = x11841._9
                      x7473
                    }
                    else
                    {
                      val x323 = if((x229.==(7))) 
                      {
                        val x7476 = x11841._10
                        x7476
                      }
                      else
                      {
                        val x322 = if((x229.==(8))) 
                        {
                          val x7479 = x11841._11
                          x7479
                        }
                        else
                        {
                          val x321 = if((x229.==(9))) 
                          {
                            val x7482 = x11841._12
                            x7482
                          }
                          else
                          {
                            val x7483 = x11841._13
                            x7483
                          }
                          
                          x321
                        }
                        
                        x322
                      }
                      
                      x323
                    }
                    
                    x324
                  }
                  
                  x325
                }
                
                x326
              }
              
              x327
            }
            
            x328
          }
          
          val x7484 = x11841._3
          val x331 = x241
          x238.update(x331, x7484)
          val x7487 = x11811._14
          val x334 = x7487.contains("original")
          if((x334.&&({
            val x7490 = x11841._17
            val x336 = x7490.contains("original")
            x336
          }))) 
          {
            val x338 = x241
            x239.update(x338, "B")
            ()
          }
          else
          {
            val x340 = x241
            x239.update(x340, "G")
            ()
          }
          
          x11841._3_=((x7484.-(x299)))
          if((x7484.<=(x299))) 
          {
            x11841._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x348: Int = 0
          if((x295.!=(x228))) 
          {
            x348 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x7507 = x11811._16
          val x7508 = x11814._8
          val x7509 = x11818._9
          val x356 = x241
          val x357 = x236.apply(x356)
          val x364 = (((x299.toDouble).*(x357)).*(((1.0.+(x7508)).+(x7509)))).*((1.0.-(x7507)))
          val x365 = x241
          x240.update(x365, x364)
          val x367 = x290
          x290 = (x367.+(x364))
          val x370 = x241
          x4157.insert((SEntry10_IIIIIITIDS(x7433, x229, x228, (x370.+(1)), x297, x295, null, x299, x364, x329)))
          val x375 = x241
          x241 = (x375.+(1))
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
