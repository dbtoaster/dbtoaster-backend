
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def this() = this(-2147483648, -2147483648, null, -1.7976931348623157E308, null) ; def copy = SEntry5_IISDS(_1, _2, _3, _4, _5) }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def this() = this(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648) ; def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def this() = this(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null) ; def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21) }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false) ; def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def this() = this(-2147483648, -2147483648, -2147483648) ; def copy = SEntry3_III(_1, _2, _3) }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null) ; def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8) }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def this() = this(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null) ; def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null) ; def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def this() = this(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308) ; def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9) }
class SCExecutor 
{
  val x3708 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val newOrderTbl = new Store[SEntry3_III](3, x3708);
  val x3710 = newOrderTbl.index(0, IHash, true, -1)
  val x3711 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val x3712 = newOrderTbl.index(2, INone, false, -1)
  val x3895 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx12345678)
  val historyTbl = new Store[SEntry8_IIIIITDS](1, x3895);
  val x3897 = historyTbl.index(0, IHash, true, -1)
  val x3914 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val warehouseTbl = new Store[SEntry9_ISSSSSSDD](1, x3914);
  val x3916 = warehouseTbl.index(0, IDirect, true, 1)
  val x3933 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val itemTbl = new Store[SEntry5_IISDS](1, x3933);
  val x3935 = itemTbl.index(0, IDirect, true, 100000)
  val x4169 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val orderTbl = new Store[SEntry8_IIIITIIB](3, x4169);
  val x4171 = orderTbl.index(0, IHash, true, -1)
  val x4172 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val x4173 = orderTbl.index(2, INone, false, -1)
  val x4196 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val districtTbl = new Store[SEntry11_IISSSSSSDDI](1, x4196);
  val x4198 = districtTbl.index(0, IDirect, true, 10)
  val x4381 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val orderLineTbl = new Store[SEntry10_IIIIIITIDS](2, x4381);
  val x4383 = orderLineTbl.index(0, IHash, true, -1)
  val x4384 = orderLineTbl.index(1, IHash, false, -1)
  val x4493 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val customerTbl = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4493);
  val x4495 = customerTbl.index(0, IDirect, true, 30000)
  val x4496 = customerTbl.index(1, IHash, false, -1)
  val x4519 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val stockTbl = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4519);
  val x4521 = stockTbl.index(0, IDirect, true, 100000)
  

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4200 : SEntry10_IIIIIITIDS) = {
      var x4201: Int = -889275714;
      val x4202 = x4200._1;
      val x4203 = x4202.hashCode();
      val x4204 = -862048943.*(x4203);
      val x4205 = x4204.<<(15);
      val x4206 = x4204.>>>(-15);
      val x4207 = x4205.|(x4206);
      val x4208 = x4207.*(461845907);
      val x4209 = x4201;
      val x4210 = x4208.^(x4209);
      val x4211 = x4210.<<(13);
      val x4212 = x4210.>>>(-13);
      val x4213 = x4211.|(x4212);
      val x4214 = x4213.*(5);
      val x4215 = x4214.+(-430675100);
      x4201 = x4215
      val x4217 = x4200._2;
      val x4218 = x4217.hashCode();
      val x4219 = -862048943.*(x4218);
      val x4220 = x4219.<<(15);
      val x4221 = x4219.>>>(-15);
      val x4222 = x4220.|(x4221);
      val x4223 = x4222.*(461845907);
      val x4224 = x4201;
      val x4225 = x4223.^(x4224);
      val x4226 = x4225.<<(13);
      val x4227 = x4225.>>>(-13);
      val x4228 = x4226.|(x4227);
      val x4229 = x4228.*(5);
      val x4230 = x4229.+(-430675100);
      x4201 = x4230
      val x4232 = x4200._3;
      val x4233 = x4232.hashCode();
      val x4234 = -862048943.*(x4233);
      val x4235 = x4234.<<(15);
      val x4236 = x4234.>>>(-15);
      val x4237 = x4235.|(x4236);
      val x4238 = x4237.*(461845907);
      val x4239 = x4201;
      val x4240 = x4238.^(x4239);
      val x4241 = x4240.<<(13);
      val x4242 = x4240.>>>(-13);
      val x4243 = x4241.|(x4242);
      val x4244 = x4243.*(5);
      val x4245 = x4244.+(-430675100);
      x4201 = x4245
      val x4247 = x4200._4;
      val x4248 = x4247.hashCode();
      val x4249 = -862048943.*(x4248);
      val x4250 = x4249.<<(15);
      val x4251 = x4249.>>>(-15);
      val x4252 = x4250.|(x4251);
      val x4253 = x4252.*(461845907);
      val x4254 = x4201;
      val x4255 = x4253.^(x4254);
      val x4256 = x4255.<<(13);
      val x4257 = x4255.>>>(-13);
      val x4258 = x4256.|(x4257);
      val x4259 = x4258.*(5);
      val x4260 = x4259.+(-430675100);
      x4201 = x4260
      val x4262 = x4201;
      val x4263 = x4262.^(2);
      val x4264 = x4263.>>>(16);
      val x4265 = x4263.^(x4264);
      val x4266 = x4265.*(-2048144789);
      val x4267 = x4266.>>>(13);
      val x4268 = x4266.^(x4267);
      val x4269 = x4268.*(-1028477387);
      val x4270 = x4269.>>>(16);
      val x4271 = x4269.^(x4270);
      x4271
    }
    override def cmp(x4273 : SEntry10_IIIIIITIDS , x4274 : SEntry10_IIIIIITIDS) = {
      var x4275: Int = 0;
      val x4276 = x4273._1;
      val x4277 = x4274._1;
      val x4278 = x4276.==(x4277);
      if(x4278) 
      {
        val x4279 = x4273._2;
        val x4280 = x4274._2;
        val x4281 = x4279.==(x4280);
        if(x4281) 
        {
          val x4282 = x4273._3;
          val x4283 = x4274._3;
          val x4284 = x4282.==(x4283);
          if(x4284) 
          {
            val x4285 = x4273._4;
            val x4286 = x4274._4;
            val x4287 = x4285.==(x4286);
            if(x4287) 
            {
              x4275 = 0
              ()
            }
            else
            {
              x4275 = 1
              ()
            }
            
            ()
          }
          else
          {
            x4275 = 1
            ()
          }
          
          ()
        }
        else
        {
          x4275 = 1
          ()
        }
        
        ()
      }
      else
      {
        x4275 = 1
        ()
      }
      
      val x4297 = x4275;
      x4297
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4088 : SEntry8_IIIITIIB) = {
      var x4089: Int = -889275714;
      val x4090 = x4088._2;
      val x4091 = x4090.hashCode();
      val x4092 = -862048943.*(x4091);
      val x4093 = x4092.<<(15);
      val x4094 = x4092.>>>(-15);
      val x4095 = x4093.|(x4094);
      val x4096 = x4095.*(461845907);
      val x4097 = x4089;
      val x4098 = x4096.^(x4097);
      val x4099 = x4098.<<(13);
      val x4100 = x4098.>>>(-13);
      val x4101 = x4099.|(x4100);
      val x4102 = x4101.*(5);
      val x4103 = x4102.+(-430675100);
      x4089 = x4103
      val x4105 = x4088._3;
      val x4106 = x4105.hashCode();
      val x4107 = -862048943.*(x4106);
      val x4108 = x4107.<<(15);
      val x4109 = x4107.>>>(-15);
      val x4110 = x4108.|(x4109);
      val x4111 = x4110.*(461845907);
      val x4112 = x4089;
      val x4113 = x4111.^(x4112);
      val x4114 = x4113.<<(13);
      val x4115 = x4113.>>>(-13);
      val x4116 = x4114.|(x4115);
      val x4117 = x4116.*(5);
      val x4118 = x4117.+(-430675100);
      x4089 = x4118
      val x4120 = x4088._4;
      val x4121 = x4120.hashCode();
      val x4122 = -862048943.*(x4121);
      val x4123 = x4122.<<(15);
      val x4124 = x4122.>>>(-15);
      val x4125 = x4123.|(x4124);
      val x4126 = x4125.*(461845907);
      val x4127 = x4089;
      val x4128 = x4126.^(x4127);
      val x4129 = x4128.<<(13);
      val x4130 = x4128.>>>(-13);
      val x4131 = x4129.|(x4130);
      val x4132 = x4131.*(5);
      val x4133 = x4132.+(-430675100);
      x4089 = x4133
      val x4135 = x4089;
      val x4136 = x4135.^(2);
      val x4137 = x4136.>>>(16);
      val x4138 = x4136.^(x4137);
      val x4139 = x4138.*(-2048144789);
      val x4140 = x4139.>>>(13);
      val x4141 = x4139.^(x4140);
      val x4142 = x4141.*(-1028477387);
      val x4143 = x4142.>>>(16);
      val x4144 = x4142.^(x4143);
      x4144
    }
    override def cmp(x4146 : SEntry8_IIIITIIB , x4147 : SEntry8_IIIITIIB) = {
      var x4148: Int = 0;
      val x4149 = x4146._2;
      val x4150 = x4147._2;
      val x4151 = x4149.==(x4150);
      if(x4151) 
      {
        val x4152 = x4146._3;
        val x4153 = x4147._3;
        val x4154 = x4152.==(x4153);
        if(x4154) 
        {
          val x4155 = x4146._4;
          val x4156 = x4147._4;
          val x4157 = x4155.==(x4156);
          if(x4157) 
          {
            x4148 = 0
            ()
          }
          else
          {
            x4148 = 1
            ()
          }
          
          ()
        }
        else
        {
          x4148 = 1
          ()
        }
        
        ()
      }
      else
      {
        x4148 = 1
        ()
      }
      
      val x4165 = x4148;
      x4165
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3514 : SEntry3_III) = {
      var x3515: Int = -889275714;
      val x3516 = x3514._1;
      val x3517 = x3516.hashCode();
      val x3518 = -862048943.*(x3517);
      val x3519 = x3518.<<(15);
      val x3520 = x3518.>>>(-15);
      val x3521 = x3519.|(x3520);
      val x3522 = x3521.*(461845907);
      val x3523 = x3515;
      val x3524 = x3522.^(x3523);
      val x3525 = x3524.<<(13);
      val x3526 = x3524.>>>(-13);
      val x3527 = x3525.|(x3526);
      val x3528 = x3527.*(5);
      val x3529 = x3528.+(-430675100);
      x3515 = x3529
      val x3531 = x3514._2;
      val x3532 = x3531.hashCode();
      val x3533 = -862048943.*(x3532);
      val x3534 = x3533.<<(15);
      val x3535 = x3533.>>>(-15);
      val x3536 = x3534.|(x3535);
      val x3537 = x3536.*(461845907);
      val x3538 = x3515;
      val x3539 = x3537.^(x3538);
      val x3540 = x3539.<<(13);
      val x3541 = x3539.>>>(-13);
      val x3542 = x3540.|(x3541);
      val x3543 = x3542.*(5);
      val x3544 = x3543.+(-430675100);
      x3515 = x3544
      val x3546 = x3514._3;
      val x3547 = x3546.hashCode();
      val x3548 = -862048943.*(x3547);
      val x3549 = x3548.<<(15);
      val x3550 = x3548.>>>(-15);
      val x3551 = x3549.|(x3550);
      val x3552 = x3551.*(461845907);
      val x3553 = x3515;
      val x3554 = x3552.^(x3553);
      val x3555 = x3554.<<(13);
      val x3556 = x3554.>>>(-13);
      val x3557 = x3555.|(x3556);
      val x3558 = x3557.*(5);
      val x3559 = x3558.+(-430675100);
      x3515 = x3559
      val x3561 = x3515;
      val x3562 = x3561.^(2);
      val x3563 = x3562.>>>(16);
      val x3564 = x3562.^(x3563);
      val x3565 = x3564.*(-2048144789);
      val x3566 = x3565.>>>(13);
      val x3567 = x3565.^(x3566);
      val x3568 = x3567.*(-1028477387);
      val x3569 = x3568.>>>(16);
      val x3570 = x3568.^(x3569);
      x3570
    }
    override def cmp(x3572 : SEntry3_III , x3573 : SEntry3_III) = {
      var x3574: Int = 0;
      val x3575 = x3572._1;
      val x3576 = x3573._1;
      val x3577 = x3575.==(x3576);
      if(x3577) 
      {
        val x3578 = x3572._2;
        val x3579 = x3573._2;
        val x3580 = x3578.==(x3579);
        if(x3580) 
        {
          val x3581 = x3572._3;
          val x3582 = x3573._3;
          val x3583 = x3581.==(x3582);
          if(x3583) 
          {
            x3574 = 0
            ()
          }
          else
          {
            x3574 = 1
            ()
          }
          
          ()
        }
        else
        {
          x3574 = 1
          ()
        }
        
        ()
      }
      else
      {
        x3574 = 1
        ()
      }
      
      val x3591 = x3574;
      x3591
    }
  }
   object SEntry8_IIIIITDS_Idx12345678 extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3714 : SEntry8_IIIIITDS) = {
      var x3715: Int = -889275714;
      val x3716 = x3714._1;
      val x3717 = x3716.hashCode();
      val x3718 = -862048943.*(x3717);
      val x3719 = x3718.<<(15);
      val x3720 = x3718.>>>(-15);
      val x3721 = x3719.|(x3720);
      val x3722 = x3721.*(461845907);
      val x3723 = x3715;
      val x3724 = x3722.^(x3723);
      val x3725 = x3724.<<(13);
      val x3726 = x3724.>>>(-13);
      val x3727 = x3725.|(x3726);
      val x3728 = x3727.*(5);
      val x3729 = x3728.+(-430675100);
      x3715 = x3729
      val x3731 = x3714._2;
      val x3732 = x3731.hashCode();
      val x3733 = -862048943.*(x3732);
      val x3734 = x3733.<<(15);
      val x3735 = x3733.>>>(-15);
      val x3736 = x3734.|(x3735);
      val x3737 = x3736.*(461845907);
      val x3738 = x3715;
      val x3739 = x3737.^(x3738);
      val x3740 = x3739.<<(13);
      val x3741 = x3739.>>>(-13);
      val x3742 = x3740.|(x3741);
      val x3743 = x3742.*(5);
      val x3744 = x3743.+(-430675100);
      x3715 = x3744
      val x3746 = x3714._3;
      val x3747 = x3746.hashCode();
      val x3748 = -862048943.*(x3747);
      val x3749 = x3748.<<(15);
      val x3750 = x3748.>>>(-15);
      val x3751 = x3749.|(x3750);
      val x3752 = x3751.*(461845907);
      val x3753 = x3715;
      val x3754 = x3752.^(x3753);
      val x3755 = x3754.<<(13);
      val x3756 = x3754.>>>(-13);
      val x3757 = x3755.|(x3756);
      val x3758 = x3757.*(5);
      val x3759 = x3758.+(-430675100);
      x3715 = x3759
      val x3761 = x3714._4;
      val x3762 = x3761.hashCode();
      val x3763 = -862048943.*(x3762);
      val x3764 = x3763.<<(15);
      val x3765 = x3763.>>>(-15);
      val x3766 = x3764.|(x3765);
      val x3767 = x3766.*(461845907);
      val x3768 = x3715;
      val x3769 = x3767.^(x3768);
      val x3770 = x3769.<<(13);
      val x3771 = x3769.>>>(-13);
      val x3772 = x3770.|(x3771);
      val x3773 = x3772.*(5);
      val x3774 = x3773.+(-430675100);
      x3715 = x3774
      val x3776 = x3714._5;
      val x3777 = x3776.hashCode();
      val x3778 = -862048943.*(x3777);
      val x3779 = x3778.<<(15);
      val x3780 = x3778.>>>(-15);
      val x3781 = x3779.|(x3780);
      val x3782 = x3781.*(461845907);
      val x3783 = x3715;
      val x3784 = x3782.^(x3783);
      val x3785 = x3784.<<(13);
      val x3786 = x3784.>>>(-13);
      val x3787 = x3785.|(x3786);
      val x3788 = x3787.*(5);
      val x3789 = x3788.+(-430675100);
      x3715 = x3789
      val x3791 = x3714._6;
      val x3792 = x3791.hashCode();
      val x3793 = -862048943.*(x3792);
      val x3794 = x3793.<<(15);
      val x3795 = x3793.>>>(-15);
      val x3796 = x3794.|(x3795);
      val x3797 = x3796.*(461845907);
      val x3798 = x3715;
      val x3799 = x3797.^(x3798);
      val x3800 = x3799.<<(13);
      val x3801 = x3799.>>>(-13);
      val x3802 = x3800.|(x3801);
      val x3803 = x3802.*(5);
      val x3804 = x3803.+(-430675100);
      x3715 = x3804
      val x3806 = x3714._7;
      val x3807 = x3806.hashCode();
      val x3808 = -862048943.*(x3807);
      val x3809 = x3808.<<(15);
      val x3810 = x3808.>>>(-15);
      val x3811 = x3809.|(x3810);
      val x3812 = x3811.*(461845907);
      val x3813 = x3715;
      val x3814 = x3812.^(x3813);
      val x3815 = x3814.<<(13);
      val x3816 = x3814.>>>(-13);
      val x3817 = x3815.|(x3816);
      val x3818 = x3817.*(5);
      val x3819 = x3818.+(-430675100);
      x3715 = x3819
      val x3821 = x3714._8;
      val x3822 = x3821.hashCode();
      val x3823 = -862048943.*(x3822);
      val x3824 = x3823.<<(15);
      val x3825 = x3823.>>>(-15);
      val x3826 = x3824.|(x3825);
      val x3827 = x3826.*(461845907);
      val x3828 = x3715;
      val x3829 = x3827.^(x3828);
      val x3830 = x3829.<<(13);
      val x3831 = x3829.>>>(-13);
      val x3832 = x3830.|(x3831);
      val x3833 = x3832.*(5);
      val x3834 = x3833.+(-430675100);
      x3715 = x3834
      val x3836 = x3715;
      val x3837 = x3836.^(2);
      val x3838 = x3837.>>>(16);
      val x3839 = x3837.^(x3838);
      val x3840 = x3839.*(-2048144789);
      val x3841 = x3840.>>>(13);
      val x3842 = x3840.^(x3841);
      val x3843 = x3842.*(-1028477387);
      val x3844 = x3843.>>>(16);
      val x3845 = x3843.^(x3844);
      x3845
    }
    override def cmp(x3847 : SEntry8_IIIIITDS , x3848 : SEntry8_IIIIITDS) = {
      var x3849: Int = 0;
      val x3850 = x3847._1;
      val x3851 = x3848._1;
      val x3852 = x3850.==(x3851);
      if(x3852) 
      {
        val x3853 = x3847._2;
        val x3854 = x3848._2;
        val x3855 = x3853.==(x3854);
        if(x3855) 
        {
          val x3856 = x3847._3;
          val x3857 = x3848._3;
          val x3858 = x3856.==(x3857);
          if(x3858) 
          {
            val x3859 = x3847._4;
            val x3860 = x3848._4;
            val x3861 = x3859.==(x3860);
            if(x3861) 
            {
              val x3862 = x3847._5;
              val x3863 = x3848._5;
              val x3864 = x3862.==(x3863);
              if(x3864) 
              {
                val x3865 = x3847._6;
                val x3866 = x3848._6;
                val x3867 = x3865.==(x3866);
                if(x3867) 
                {
                  val x3868 = x3847._7;
                  val x3869 = x3848._7;
                  val x3870 = x3868.==(x3869);
                  if(x3870) 
                  {
                    val x3871 = x3847._8;
                    val x3872 = x3848._8;
                    val x3873 = x3871.==(x3872);
                    if(x3873) 
                    {
                      x3849 = 0
                      ()
                    }
                    else
                    {
                      x3849 = 1
                      ()
                    }
                    
                    ()
                  }
                  else
                  {
                    x3849 = 1
                    ()
                  }
                  
                  ()
                }
                else
                {
                  x3849 = 1
                  ()
                }
                
                ()
              }
              else
              {
                x3849 = 1
                ()
              }
              
              ()
            }
            else
            {
              x3849 = 1
              ()
            }
            
            ()
          }
          else
          {
            x3849 = 1
            ()
          }
          
          ()
        }
        else
        {
          x3849 = 1
          ()
        }
        
        ()
      }
      else
      {
        x3849 = 1
        ()
      }
      
      val x3891 = x3849;
      x3891
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4300 : SEntry10_IIIIIITIDS) = {
      var x4301: Int = -889275714;
      val x4302 = x4300._1;
      val x4303 = x4302.hashCode();
      val x4304 = -862048943.*(x4303);
      val x4305 = x4304.<<(15);
      val x4306 = x4304.>>>(-15);
      val x4307 = x4305.|(x4306);
      val x4308 = x4307.*(461845907);
      val x4309 = x4301;
      val x4310 = x4308.^(x4309);
      val x4311 = x4310.<<(13);
      val x4312 = x4310.>>>(-13);
      val x4313 = x4311.|(x4312);
      val x4314 = x4313.*(5);
      val x4315 = x4314.+(-430675100);
      x4301 = x4315
      val x4317 = x4300._2;
      val x4318 = x4317.hashCode();
      val x4319 = -862048943.*(x4318);
      val x4320 = x4319.<<(15);
      val x4321 = x4319.>>>(-15);
      val x4322 = x4320.|(x4321);
      val x4323 = x4322.*(461845907);
      val x4324 = x4301;
      val x4325 = x4323.^(x4324);
      val x4326 = x4325.<<(13);
      val x4327 = x4325.>>>(-13);
      val x4328 = x4326.|(x4327);
      val x4329 = x4328.*(5);
      val x4330 = x4329.+(-430675100);
      x4301 = x4330
      val x4332 = x4300._3;
      val x4333 = x4332.hashCode();
      val x4334 = -862048943.*(x4333);
      val x4335 = x4334.<<(15);
      val x4336 = x4334.>>>(-15);
      val x4337 = x4335.|(x4336);
      val x4338 = x4337.*(461845907);
      val x4339 = x4301;
      val x4340 = x4338.^(x4339);
      val x4341 = x4340.<<(13);
      val x4342 = x4340.>>>(-13);
      val x4343 = x4341.|(x4342);
      val x4344 = x4343.*(5);
      val x4345 = x4344.+(-430675100);
      x4301 = x4345
      val x4347 = x4301;
      val x4348 = x4347.^(2);
      val x4349 = x4348.>>>(16);
      val x4350 = x4348.^(x4349);
      val x4351 = x4350.*(-2048144789);
      val x4352 = x4351.>>>(13);
      val x4353 = x4351.^(x4352);
      val x4354 = x4353.*(-1028477387);
      val x4355 = x4354.>>>(16);
      val x4356 = x4354.^(x4355);
      x4356
    }
    override def cmp(x4358 : SEntry10_IIIIIITIDS , x4359 : SEntry10_IIIIIITIDS) = {
      var x4360: Int = 0;
      val x4361 = x4358._1;
      val x4362 = x4359._1;
      val x4363 = x4361.==(x4362);
      if(x4363) 
      {
        val x4364 = x4358._2;
        val x4365 = x4359._2;
        val x4366 = x4364.==(x4365);
        if(x4366) 
        {
          val x4367 = x4358._3;
          val x4368 = x4359._3;
          val x4369 = x4367.==(x4368);
          if(x4369) 
          {
            x4360 = 0
            ()
          }
          else
          {
            x4360 = 1
            ()
          }
          
          ()
        }
        else
        {
          x4360 = 1
          ()
        }
        
        ()
      }
      else
      {
        x4360 = 1
        ()
      }
      
      val x4377 = x4360;
      x4377
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3647 : SEntry3_III) = {
      var x3648: Int = -889275714;
      val x3649 = x3647._2;
      val x3650 = x3649.hashCode();
      val x3651 = -862048943.*(x3650);
      val x3652 = x3651.<<(15);
      val x3653 = x3651.>>>(-15);
      val x3654 = x3652.|(x3653);
      val x3655 = x3654.*(461845907);
      val x3656 = x3648;
      val x3657 = x3655.^(x3656);
      val x3658 = x3657.<<(13);
      val x3659 = x3657.>>>(-13);
      val x3660 = x3658.|(x3659);
      val x3661 = x3660.*(5);
      val x3662 = x3661.+(-430675100);
      x3648 = x3662
      val x3664 = x3647._3;
      val x3665 = x3664.hashCode();
      val x3666 = -862048943.*(x3665);
      val x3667 = x3666.<<(15);
      val x3668 = x3666.>>>(-15);
      val x3669 = x3667.|(x3668);
      val x3670 = x3669.*(461845907);
      val x3671 = x3648;
      val x3672 = x3670.^(x3671);
      val x3673 = x3672.<<(13);
      val x3674 = x3672.>>>(-13);
      val x3675 = x3673.|(x3674);
      val x3676 = x3675.*(5);
      val x3677 = x3676.+(-430675100);
      x3648 = x3677
      val x3679 = x3648;
      val x3680 = x3679.^(2);
      val x3681 = x3680.>>>(16);
      val x3682 = x3680.^(x3681);
      val x3683 = x3682.*(-2048144789);
      val x3684 = x3683.>>>(13);
      val x3685 = x3683.^(x3684);
      val x3686 = x3685.*(-1028477387);
      val x3687 = x3686.>>>(16);
      val x3688 = x3686.^(x3687);
      x3688
    }
    override def cmp(x3690 : SEntry3_III , x3691 : SEntry3_III) = {
      var x3692: Int = 0;
      val x3693 = x3690._2;
      val x3694 = x3691._2;
      val x3695 = x3693.==(x3694);
      if(x3695) 
      {
        val x3696 = x3690._3;
        val x3697 = x3691._3;
        val x3698 = x3696.==(x3697);
        if(x3698) 
        {
          x3692 = 0
          ()
        }
        else
        {
          x3692 = 1
          ()
        }
        
        ()
      }
      else
      {
        x3692 = 1
        ()
      }
      
      val x3704 = x3692;
      x3704
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4412 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4413: Int = -889275714;
      val x4414 = x4412._2;
      val x4415 = x4414.hashCode();
      val x4416 = -862048943.*(x4415);
      val x4417 = x4416.<<(15);
      val x4418 = x4416.>>>(-15);
      val x4419 = x4417.|(x4418);
      val x4420 = x4419.*(461845907);
      val x4421 = x4413;
      val x4422 = x4420.^(x4421);
      val x4423 = x4422.<<(13);
      val x4424 = x4422.>>>(-13);
      val x4425 = x4423.|(x4424);
      val x4426 = x4425.*(5);
      val x4427 = x4426.+(-430675100);
      x4413 = x4427
      val x4429 = x4412._3;
      val x4430 = x4429.hashCode();
      val x4431 = -862048943.*(x4430);
      val x4432 = x4431.<<(15);
      val x4433 = x4431.>>>(-15);
      val x4434 = x4432.|(x4433);
      val x4435 = x4434.*(461845907);
      val x4436 = x4413;
      val x4437 = x4435.^(x4436);
      val x4438 = x4437.<<(13);
      val x4439 = x4437.>>>(-13);
      val x4440 = x4438.|(x4439);
      val x4441 = x4440.*(5);
      val x4442 = x4441.+(-430675100);
      x4413 = x4442
      val x4444 = x4412._6;
      val x4445 = x4444.hashCode();
      val x4446 = -862048943.*(x4445);
      val x4447 = x4446.<<(15);
      val x4448 = x4446.>>>(-15);
      val x4449 = x4447.|(x4448);
      val x4450 = x4449.*(461845907);
      val x4451 = x4413;
      val x4452 = x4450.^(x4451);
      val x4453 = x4452.<<(13);
      val x4454 = x4452.>>>(-13);
      val x4455 = x4453.|(x4454);
      val x4456 = x4455.*(5);
      val x4457 = x4456.+(-430675100);
      x4413 = x4457
      val x4459 = x4413;
      val x4460 = x4459.^(2);
      val x4461 = x4460.>>>(16);
      val x4462 = x4460.^(x4461);
      val x4463 = x4462.*(-2048144789);
      val x4464 = x4463.>>>(13);
      val x4465 = x4463.^(x4464);
      val x4466 = x4465.*(-1028477387);
      val x4467 = x4466.>>>(16);
      val x4468 = x4466.^(x4467);
      x4468
    }
    override def cmp(x4470 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4471 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4472: Int = 0;
      val x4473 = x4470._2;
      val x4474 = x4471._2;
      val x4475 = x4473.==(x4474);
      if(x4475) 
      {
        val x4476 = x4470._3;
        val x4477 = x4471._3;
        val x4478 = x4476.==(x4477);
        if(x4478) 
        {
          val x4479 = x4470._6;
          val x4480 = x4471._6;
          val x4481 = x4479.==(x4480);
          if(x4481) 
          {
            x4472 = 0
            ()
          }
          else
          {
            x4472 = 1
            ()
          }
          
          ()
        }
        else
        {
          x4472 = 1
          ()
        }
        
        ()
      }
      else
      {
        x4472 = 1
        ()
      }
      
      val x4489 = x4472;
      x4489
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3940 : SEntry8_IIIITIIB) = {
      var x3941: Int = -889275714;
      val x3942 = x3940._1;
      val x3943 = x3942.hashCode();
      val x3944 = -862048943.*(x3943);
      val x3945 = x3944.<<(15);
      val x3946 = x3944.>>>(-15);
      val x3947 = x3945.|(x3946);
      val x3948 = x3947.*(461845907);
      val x3949 = x3941;
      val x3950 = x3948.^(x3949);
      val x3951 = x3950.<<(13);
      val x3952 = x3950.>>>(-13);
      val x3953 = x3951.|(x3952);
      val x3954 = x3953.*(5);
      val x3955 = x3954.+(-430675100);
      x3941 = x3955
      val x3957 = x3940._2;
      val x3958 = x3957.hashCode();
      val x3959 = -862048943.*(x3958);
      val x3960 = x3959.<<(15);
      val x3961 = x3959.>>>(-15);
      val x3962 = x3960.|(x3961);
      val x3963 = x3962.*(461845907);
      val x3964 = x3941;
      val x3965 = x3963.^(x3964);
      val x3966 = x3965.<<(13);
      val x3967 = x3965.>>>(-13);
      val x3968 = x3966.|(x3967);
      val x3969 = x3968.*(5);
      val x3970 = x3969.+(-430675100);
      x3941 = x3970
      val x3972 = x3940._3;
      val x3973 = x3972.hashCode();
      val x3974 = -862048943.*(x3973);
      val x3975 = x3974.<<(15);
      val x3976 = x3974.>>>(-15);
      val x3977 = x3975.|(x3976);
      val x3978 = x3977.*(461845907);
      val x3979 = x3941;
      val x3980 = x3978.^(x3979);
      val x3981 = x3980.<<(13);
      val x3982 = x3980.>>>(-13);
      val x3983 = x3981.|(x3982);
      val x3984 = x3983.*(5);
      val x3985 = x3984.+(-430675100);
      x3941 = x3985
      val x3987 = x3941;
      val x3988 = x3987.^(2);
      val x3989 = x3988.>>>(16);
      val x3990 = x3988.^(x3989);
      val x3991 = x3990.*(-2048144789);
      val x3992 = x3991.>>>(13);
      val x3993 = x3991.^(x3992);
      val x3994 = x3993.*(-1028477387);
      val x3995 = x3994.>>>(16);
      val x3996 = x3994.^(x3995);
      x3996
    }
    override def cmp(x3998 : SEntry8_IIIITIIB , x3999 : SEntry8_IIIITIIB) = {
      var x4000: Int = 0;
      val x4001 = x3998._1;
      val x4002 = x3999._1;
      val x4003 = x4001.==(x4002);
      if(x4003) 
      {
        val x4004 = x3998._2;
        val x4005 = x3999._2;
        val x4006 = x4004.==(x4005);
        if(x4006) 
        {
          val x4007 = x3998._3;
          val x4008 = x3999._3;
          val x4009 = x4007.==(x4008);
          if(x4009) 
          {
            x4000 = 0
            ()
          }
          else
          {
            x4000 = 1
            ()
          }
          
          ()
        }
        else
        {
          x4000 = 1
          ()
        }
        
        ()
      }
      else
      {
        x4000 = 1
        ()
      }
      
      val x4017 = x4000;
      x4017
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3594 : SEntry3_III) = {
      var x3595: Int = -889275714;
      val x3596 = x3594._2;
      val x3597 = x3596.hashCode();
      val x3598 = -862048943.*(x3597);
      val x3599 = x3598.<<(15);
      val x3600 = x3598.>>>(-15);
      val x3601 = x3599.|(x3600);
      val x3602 = x3601.*(461845907);
      val x3603 = x3595;
      val x3604 = x3602.^(x3603);
      val x3605 = x3604.<<(13);
      val x3606 = x3604.>>>(-13);
      val x3607 = x3605.|(x3606);
      val x3608 = x3607.*(5);
      val x3609 = x3608.+(-430675100);
      x3595 = x3609
      val x3611 = x3594._3;
      val x3612 = x3611.hashCode();
      val x3613 = -862048943.*(x3612);
      val x3614 = x3613.<<(15);
      val x3615 = x3613.>>>(-15);
      val x3616 = x3614.|(x3615);
      val x3617 = x3616.*(461845907);
      val x3618 = x3595;
      val x3619 = x3617.^(x3618);
      val x3620 = x3619.<<(13);
      val x3621 = x3619.>>>(-13);
      val x3622 = x3620.|(x3621);
      val x3623 = x3622.*(5);
      val x3624 = x3623.+(-430675100);
      x3595 = x3624
      val x3626 = x3595;
      val x3627 = x3626.^(2);
      val x3628 = x3627.>>>(16);
      val x3629 = x3627.^(x3628);
      val x3630 = x3629.*(-2048144789);
      val x3631 = x3630.>>>(13);
      val x3632 = x3630.^(x3631);
      val x3633 = x3632.*(-1028477387);
      val x3634 = x3633.>>>(16);
      val x3635 = x3633.^(x3634);
      x3635
    }
    override def cmp(x3637 : SEntry3_III , x3638 : SEntry3_III) = {
      val x3639 = x3637._1;
      val x3640 = x3638._1;
      val x3641 = x3639.==(x3640);
      val x3642 = x3639.>(x3640);
      val x3643 = if(x3642) 1 else -1;
      val x3644 = if(x3641) 0 else x3643;
      x3644
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4020 : SEntry8_IIIITIIB) = {
      var x4021: Int = -889275714;
      val x4022 = x4020._2;
      val x4023 = x4022.hashCode();
      val x4024 = -862048943.*(x4023);
      val x4025 = x4024.<<(15);
      val x4026 = x4024.>>>(-15);
      val x4027 = x4025.|(x4026);
      val x4028 = x4027.*(461845907);
      val x4029 = x4021;
      val x4030 = x4028.^(x4029);
      val x4031 = x4030.<<(13);
      val x4032 = x4030.>>>(-13);
      val x4033 = x4031.|(x4032);
      val x4034 = x4033.*(5);
      val x4035 = x4034.+(-430675100);
      x4021 = x4035
      val x4037 = x4020._3;
      val x4038 = x4037.hashCode();
      val x4039 = -862048943.*(x4038);
      val x4040 = x4039.<<(15);
      val x4041 = x4039.>>>(-15);
      val x4042 = x4040.|(x4041);
      val x4043 = x4042.*(461845907);
      val x4044 = x4021;
      val x4045 = x4043.^(x4044);
      val x4046 = x4045.<<(13);
      val x4047 = x4045.>>>(-13);
      val x4048 = x4046.|(x4047);
      val x4049 = x4048.*(5);
      val x4050 = x4049.+(-430675100);
      x4021 = x4050
      val x4052 = x4020._4;
      val x4053 = x4052.hashCode();
      val x4054 = -862048943.*(x4053);
      val x4055 = x4054.<<(15);
      val x4056 = x4054.>>>(-15);
      val x4057 = x4055.|(x4056);
      val x4058 = x4057.*(461845907);
      val x4059 = x4021;
      val x4060 = x4058.^(x4059);
      val x4061 = x4060.<<(13);
      val x4062 = x4060.>>>(-13);
      val x4063 = x4061.|(x4062);
      val x4064 = x4063.*(5);
      val x4065 = x4064.+(-430675100);
      x4021 = x4065
      val x4067 = x4021;
      val x4068 = x4067.^(2);
      val x4069 = x4068.>>>(16);
      val x4070 = x4068.^(x4069);
      val x4071 = x4070.*(-2048144789);
      val x4072 = x4071.>>>(13);
      val x4073 = x4071.^(x4072);
      val x4074 = x4073.*(-1028477387);
      val x4075 = x4074.>>>(16);
      val x4076 = x4074.^(x4075);
      x4076
    }
    override def cmp(x4078 : SEntry8_IIIITIIB , x4079 : SEntry8_IIIITIIB) = {
      val x4080 = x4078._1;
      val x4081 = x4079._1;
      val x4082 = x4080.==(x4081);
      val x4083 = x4080.>(x4081);
      val x4084 = if(x4083) 1 else -1;
      val x4085 = if(x4082) 0 else x4084;
      x4085
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4501 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4502: Int = 0;
      val x4503 = x4501._1;
      val x4504 = x4503.-(1);
      val x4505 = x4502;
      val x4506 = x4505.*(100000);
      val x4507 = x4506.+(x4504);
      x4502 = x4507
      val x4509 = x4501._2;
      val x4510 = x4509.-(1);
      val x4511 = x4502;
      val x4512 = x4511.*(1);
      val x4513 = x4512.+(x4510);
      x4502 = x4513
      val x4515 = x4502;
      x4515
    }
    override def cmp(x4498 : SEntry17_IIISSSSSSSSSSIIIS , x4499 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4389 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4390: Int = 0;
      val x4391 = x4389._1;
      val x4392 = x4391.-(1);
      val x4393 = x4390;
      val x4394 = x4393.*(3000);
      val x4395 = x4394.+(x4392);
      x4390 = x4395
      val x4397 = x4389._2;
      val x4398 = x4397.-(1);
      val x4399 = x4390;
      val x4400 = x4399.*(10);
      val x4401 = x4400.+(x4398);
      x4390 = x4401
      val x4403 = x4389._3;
      val x4404 = x4403.-(1);
      val x4405 = x4390;
      val x4406 = x4405.*(1);
      val x4407 = x4406.+(x4404);
      x4390 = x4407
      val x4409 = x4390;
      x4409
    }
    override def cmp(x4386 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4387 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3921 : SEntry5_IISDS) = {
      var x3922: Int = 0;
      val x3923 = x3921._1;
      val x3924 = x3923.-(1);
      val x3925 = x3922;
      val x3926 = x3925.*(100000);
      val x3927 = x3926.+(x3924);
      x3922 = x3927
      val x3929 = x3922;
      x3929
    }
    override def cmp(x3918 : SEntry5_IISDS , x3919 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3902 : SEntry9_ISSSSSSDD) = {
      var x3903: Int = 0;
      val x3904 = x3902._1;
      val x3905 = x3904.-(1);
      val x3906 = x3903;
      val x3907 = x3906.*(1);
      val x3908 = x3907.+(x3905);
      x3903 = x3908
      val x3910 = x3903;
      x3910
    }
    override def cmp(x3899 : SEntry9_ISSSSSSDD , x3900 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4178 : SEntry11_IISSSSSSDDI) = {
      var x4179: Int = 0;
      val x4180 = x4178._1;
      val x4181 = x4180.-(1);
      val x4182 = x4179;
      val x4183 = x4182.*(10);
      val x4184 = x4183.+(x4181);
      x4179 = x4184
      val x4186 = x4178._2;
      val x4187 = x4186.-(1);
      val x4188 = x4179;
      val x4189 = x4188.*(1);
      val x4190 = x4189.+(x4187);
      x4179 = x4190
      val x4192 = x4179;
      x4192
    }
    override def cmp(x4175 : SEntry11_IISSSSSSDDI , x4176 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
  val x7783 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8155 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x7585 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8131 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8138 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x8125 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7561 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x8105 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x8128 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x7710 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7933 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7893 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x7773 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7950 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7572 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x8141 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x8228 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7581 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7698 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x7916 = SEntry8_IIIIITDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x7729 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x7800 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7888 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  class DeliveryTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](123);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val x27 = x18;
        x7561._2_=(x27)
        x7561._3_=(x12)
        val x12592 = x3711.get(x7561);
        if((x12592.!=(null))) 
        {
          val x7565 = x12592._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x7565)
          newOrderTbl.delete(x12592)
          val x41 = x18;
          x7572._1_=(x7565)
          x7572._2_=(x41)
          x7572._3_=(x12)
          val x12605 = x4171.get(x7572);
          val x7574 = x12605._4;
          x12605._6_=(x13)
          var x50: Double = 0.0;
          val x52 = x18;
          x7581._1_=(x7565)
          x7581._2_=(x52)
          x7581._3_=(x12)
          x4384.slice(x7581, ({ orderLineEntry: Pointer[SEntry10_IIIIIITIDS] => {
              orderLineEntry._7_=(x11)
              val x57 = x50;
              val x7625 = orderLineEntry._9;
              x50 = (x57.+(x7625))
              ()
            }
          }))
          val x65 = x18;
          x7585._1_=(x7574)
          x7585._2_=(x65)
          x7585._3_=(x12)
          val x12627 = x4495.get(x7585);
          val x69 = x50;
          x12627._17 +=(x69)
          x12627._20 +=(1)
          ()
        }
        else
        {
          val x73 = x18;
          orderIDs.update((x73.-(1)), 0)
          ()
        }
        
        val x77 = x18;
        x18 = (x77.+(1))
        ()
      }
      1
    }
  }
  class StockLevelTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x81 : Boolean, x82 : Date, x83 : Int, x84 : Int, x85 : Int, x86 : Int) =     {
      x7698._1_=(x85)
      x7698._2_=(x84)
      val x12694 = x4198.get(x7698);
      val x7700 = x12694._11;
      var x95: Int = (x7700.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply2;
      while({
        val x99 = x95;
        (x99.<(x7700))
      })
      {
        val x101 = x95;
        x7710._1_=(x101)
        x7710._2_=(x85)
        x7710._3_=(x84)
        x4384.slice(x7710, ({ orderLineEntry: Pointer[SEntry10_IIIIIITIDS] => {
            val x7727 = orderLineEntry._5;
            x7729._1_=(x7727)
            x7729._2_=(x84)
            val x12708 = x4521.get(x7729);
            val x7731 = x12708._3;
            if((x7731.<(x86))) 
            {
              val x114 = unique_ol_i_id.+=(x7727);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x118 = x95;
        x95 = (x118.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x124 : Boolean, x125 : Date, x126 : Int, x127 : Int, x128 : Int, x129 : Int, x130 : Int, x131 : String) =     {
      var ite: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS] = null;
      if((x129.>(0))) 
      {
        val x17839 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7783._2_=(x128)
        x7783._3_=(x127)
        x7783._6_=(x131)
        x4496.slice(x7783, ({ custEntry: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS] => {
            x17839.append(custEntry)
            ()
          }
        }))
        val x17847 = x17839.size;
        var x17849: Int = (x17847./(2));
        val x17857 = x17839.size;
        if(((x17857.%(2)).==(0))) 
        {
          val x150 = x17849;
          x17849 = (x150.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x17864 = x17839.sortWith(({ (c1: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS], c2: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS]) => {
            val x7824 = c1._4;
            val x7825 = c2._4;
            ((StringExtra.StringCompare(x7824, x7825)).<(0))
          }
        }));
        val x17865 = x17849;
        val x17866 = x17864.apply(x17865);
        ite = x17866
        ()
      }
      else
      {
        x7800._1_=(x130)
        x7800._2_=(x128)
        x7800._3_=(x127)
        val x17871 = x4495.get(x7800);
        ite = x17871
        ()
      }
      
      val x7770 = ite;
      val x7771 = x7770._3;
      x7773._2_=(x128)
      x7773._3_=(x127)
      x7773._4_=(x7771)
      val x12794 = x4172.get(x7773);
      var x181: Int = 0;
      val x7776 = x12794._1;
      x181 = x7776
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x185 : Boolean, x186 : Date, x187 : Int, x188 : Int, x189 : Int, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : String, x195 : Double) =     {
      x7888._1_=(x188)
      val x12845 = x3916.get(x7888);
      x12845._9 +=(x195)
      x7893._1_=(x189)
      x7893._2_=(x188)
      val x12850 = x4198.get(x7893);
      x12850._10 +=(x195)
      var ite: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS] = null;
      if((x190.>(0))) 
      {
        val x17938 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7933._2_=(x192)
        x7933._3_=(x191)
        x7933._6_=(x194)
        x4496.slice(x7933, ({ custEntry: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS] => {
            x17938.append(custEntry)
            ()
          }
        }))
        val x17946 = x17938.size;
        var x17948: Int = (x17946./(2));
        val x17956 = x17938.size;
        if(((x17956.%(2)).==(0))) 
        {
          val x226 = x17948;
          x17948 = (x226.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x17963 = x17938.sortWith(({ (c1: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS], c2: Pointer[SEntry21_IIISSSSSSSSSTSDDDDIIS]) => {
            val x7996 = c1._4;
            val x7997 = c2._4;
            ((StringExtra.StringCompare(x7996, x7997)).<(0))
          }
        }));
        val x17964 = x17948;
        val x17965 = x17963.apply(x17964);
        ite = x17965
        ()
      }
      else
      {
        x7950._1_=(x193)
        x7950._2_=(x192)
        x7950._3_=(x191)
        val x17970 = x4495.get(x7950);
        ite = x17970
        ()
      }
      
      val x7898 = ite;
      val x7899 = x7898._21;
      val x7900 = x7898._14;
      val x19287 = strstr(x7900, "BC");
      if((x19287.!=(null))) 
      {
        val x7903 = x7898._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x7903,x192,x191,x189,x188,x195,x186,x7899)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x7898._17 +=(x195)
        x7898._21_=(c_new_data)
        ()
      }
      else
      {
        x7898._17 +=(x195)
        ()
      }
      
      val x7910 = x12845._2;
      val x7911 = x12850._3;
      var h_data = "%.10s    %.10s".format(x7910,x7911)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x7914 = x7898._1;
      x7916._1_=(x7914)
      x7916._2_=(x192)
      x7916._3_=(x191)
      x7916._4_=(x189)
      x7916._5_=(x188)
      x7916._6_=(x186)
      x7916._7_=(x195)
      x7916._8_=(h_data)
      historyTbl.insert(x7916)
      1
    }
  }
  class NewOrderTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x268 : Boolean, x269 : Date, x270 : Int, x271 : Int, x272 : Int, x273 : Int, x274 : Int, x275 : Int, x276 : Array[Int], x277 : Array[Int], x278 : Array[Int], x279 : Array[Double], x280 : Array[String], x281 : Array[Int], x282 : Array[String], x283 : Array[Double]) =     {
      var x285: Int = 0;
      var x288: Int = 0;
      val idata = new Array[String](x274);
      var x293: Boolean = true;
      while({
        val x295 = x285;
        var ite: Boolean = false;
        if((x295.<(x274))) 
        {
          val x18260 = {
            val x297 = x293;
            x297
          };
          ite = x18260
          ()
        }
        else
        {
          ite = false
          ()
        }
        
        val x18074 = ite;
        x18074
      })
      {
        val x300 = x285;
        val x301 = x276.apply(x300);
        x8105._1_=(x301)
        val x12996 = x3935.get(x8105);
        if((x12996.==(null))) 
        {
          x293 = false
          ()
        }
        else
        {
          val x307 = x285;
          val x8111 = x12996._3;
          x280.update(x307, x8111)
          val x310 = x285;
          val x8114 = x12996._4;
          x279.update(x310, x8114)
          val x313 = x285;
          val x8117 = x12996._5;
          idata.update(x313, x8117)
          ()
        }
        
        val x317 = x285;
        x285 = (x317.+(1))
        ()
      }
      val x321 = x293;
      if(x321) 
      {
        x8125._1_=(x273)
        x8125._2_=(x272)
        x8125._3_=(x271)
        val x13018 = x4495.get(x8125);
        x8128._1_=(x271)
        val x13021 = x3916.get(x8128);
        x8131._1_=(x272)
        x8131._2_=(x271)
        val x13025 = x4198.get(x8131);
        val x8133 = x13025._11;
        x13025._11 +=(1)
        x8138._1_=(x8133)
        x8138._2_=(x272)
        x8138._3_=(x271)
        x8138._4_=(x273)
        x8138._5_=(x269)
        x8138._6_=(-1)
        x8138._7_=(x274)
        x8138._8_=((x275.>(0)))
        orderTbl.insert(x8138)
        x8141._1_=(x8133)
        x8141._2_=(x272)
        x8141._3_=(x271)
        newOrderTbl.insert(x8141)
        var x346: Double = 0.0;
        x285 = 0
        while({
          val x349 = x285;
          (x349.<(x274))
        })
        {
          val x352 = x285;
          val ol_supply_w_id = x277.apply(x352);
          val x355 = x285;
          val ol_i_id = x276.apply(x355);
          val x358 = x285;
          val ol_quantity = x278.apply(x358);
          x8155._1_=(ol_i_id)
          x8155._2_=(ol_supply_w_id)
          val x13058 = x4521.get(x8155);
          var ite: String = null;
          if((x272.==(1))) 
          {
            val x18138 = x13058._4;
            ite = x18138
            ()
          }
          else
          {
            var ite: String = null;
            if((x272.==(2))) 
            {
              val x18143 = x13058._5;
              ite = x18143
              ()
            }
            else
            {
              var ite: String = null;
              if((x272.==(3))) 
              {
                val x18148 = x13058._6;
                ite = x18148
                ()
              }
              else
              {
                var ite: String = null;
                if((x272.==(4))) 
                {
                  val x18153 = x13058._7;
                  ite = x18153
                  ()
                }
                else
                {
                  var ite: String = null;
                  if((x272.==(5))) 
                  {
                    val x18158 = x13058._8;
                    ite = x18158
                    ()
                  }
                  else
                  {
                    var ite: String = null;
                    if((x272.==(6))) 
                    {
                      val x18163 = x13058._9;
                      ite = x18163
                      ()
                    }
                    else
                    {
                      var ite: String = null;
                      if((x272.==(7))) 
                      {
                        val x18168 = x13058._10;
                        ite = x18168
                        ()
                      }
                      else
                      {
                        var ite: String = null;
                        if((x272.==(8))) 
                        {
                          val x18173 = x13058._11;
                          ite = x18173
                          ()
                        }
                        else
                        {
                          var ite: String = null;
                          if((x272.==(9))) 
                          {
                            val x18178 = x13058._12;
                            ite = x18178
                            ()
                          }
                          else
                          {
                            val x18180 = x13058._13;
                            ite = x18180
                            ()
                          }
                          
                          val x18176 = ite;
                          ite = x18176
                          ()
                        }
                        
                        val x18171 = ite;
                        ite = x18171
                        ()
                      }
                      
                      val x18166 = ite;
                      ite = x18166
                      ()
                    }
                    
                    val x18161 = ite;
                    ite = x18161
                    ()
                  }
                  
                  val x18156 = ite;
                  ite = x18156
                  ()
                }
                
                val x18151 = ite;
                ite = x18151
                ()
              }
              
              val x18146 = ite;
              ite = x18146
              ()
            }
            
            val x18141 = ite;
            ite = x18141
            ()
          }
          
          val ol_dist_info = ite;
          val x8185 = x13058._3;
          val x395 = x285;
          x281.update(x395, x8185)
          val x8188 = x13018._14;
          val x19522 = strstr(x8188, "original");
          var ite: Boolean = false;
          if((x19522.!=(null))) 
          {
            val x18396 = {
              val x8191 = x13058._17;
              val x19528 = strstr(x8191, "original");
              (x19528.!=(null))
            };
            ite = x18396
            ()
          }
          else
          {
            ite = false
            ()
          }
          
          val x18205 = ite;
          if(x18205) 
          {
            val x402 = x285;
            x282.update(x402, "B")
            ()
          }
          else
          {
            val x404 = x285;
            x282.update(x404, "G")
            ()
          }
          
          x13058._3_=((x8185.-(ol_quantity)))
          if((x8185.<=(ol_quantity))) 
          {
            x13058._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x413: Int = 0;
          if((ol_supply_w_id.!=(x271))) 
          {
            x413 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8208 = x13018._16;
          val x8209 = x13021._8;
          val x8210 = x13025._9;
          val x426 = x285;
          val x427 = x279.apply(x426);
          val ol_amount = ((ol_quantity.*(x427)).*(((1.0.+(x8209)).+(x8210)))).*((1.0.-(x8208)));
          val x435 = x285;
          x283.update(x435, ol_amount)
          val x437 = x346;
          x346 = (x437.+(ol_amount))
          val x440 = x285;
          x8228._1_=(x8133)
          x8228._2_=(x272)
          x8228._3_=(x271)
          x8228._4_=((x440.+(1)))
          x8228._5_=(ol_i_id)
          x8228._6_=(ol_supply_w_id)
          x8228._8_=(ol_quantity)
          x8228._9_=(ol_amount)
          x8228._10_=(ol_dist_info)
          orderLineTbl.insert(x8228)
          val x445 = x285;
          x285 = (x445.+(1))
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
