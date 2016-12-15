
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
  val x3631 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x3632 = new Store[SEntry3_III](3, x3631);
  val x730 = x3632.index(0, IHash, true, -1)
  val x731 = x3632.index(1, ISliceHeapMin, false, 2)
  val x732 = x3632.index(2, INone, false, -1)
  val x3831 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x3832 = new Store[SEntry8_IIIIITDS](1, x3831);
  val x737 = x3832.index(0, IList, false, -1)
  val x3850 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x3851 = new Store[SEntry9_ISSSSSSDD](1, x3850);
  val x742 = x3851.index(0, IDirect, true, 1)
  val x3869 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x3870 = new Store[SEntry5_IISDS](1, x3869);
  val x747 = x3870.index(0, IDirect, true, 100000)
  val x4093 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4094 = new Store[SEntry8_IIIITIIB](3, x4093);
  val x754 = x4094.index(0, IHash, true, -1)
  val x755 = x4094.index(1, ISliceHeapMax, false, 2)
  val x756 = x4094.index(2, INone, false, -1)
  val x4120 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4121 = new Store[SEntry11_IISSSSSSDDI](1, x4120);
  val x761 = x4121.index(0, IDirect, true, 10)
  val x4292 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x4293 = new Store[SEntry10_IIIIIITIDS](2, x4292);
  val x766 = x4293.index(0, IHash, true, -1)
  val x767 = x4293.index(1, IHash, false, -1)
  val x4398 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x4399 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4398);
  val x773 = x4399.index(0, IDirect, true, 30000)
  val x774 = x4399.index(1, IHash, false, -1)
  val x4424 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x4425 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4424);
  val x779 = x4425.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x3632
  val historyTbl = x3832
  val warehouseTbl = x3851
  val itemTbl = x3870
  val orderTbl = x4094
  val districtTbl = x4121
  val orderLineTbl = x4293
  val customerTbl = x4399
  val stockTbl = x4425
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4124 : SEntry10_IIIIIITIDS) = {
      var x4125: Int = -889275714;
      val x4126 = x4124._1;
      val x4127 = x4126.hashCode();
      val x4128 = -862048943.*(x4127);
      val x4129 = x4128.<<(15);
      val x4130 = x4128.>>>(-15);
      val x4131 = x4129.|(x4130);
      val x4132 = x4131.*(461845907);
      val x4133 = x4125;
      val x4134 = x4132.^(x4133);
      val x4135 = x4134.<<(13);
      val x4136 = x4134.>>>(-13);
      val x4137 = x4135.|(x4136);
      val x4138 = x4137.*(5);
      val x4139 = x4138.+(-430675100);
      x4125 = x4139
      val x4141 = x4124._2;
      val x4142 = x4141.hashCode();
      val x4143 = -862048943.*(x4142);
      val x4144 = x4143.<<(15);
      val x4145 = x4143.>>>(-15);
      val x4146 = x4144.|(x4145);
      val x4147 = x4146.*(461845907);
      val x4148 = x4125;
      val x4149 = x4147.^(x4148);
      val x4150 = x4149.<<(13);
      val x4151 = x4149.>>>(-13);
      val x4152 = x4150.|(x4151);
      val x4153 = x4152.*(5);
      val x4154 = x4153.+(-430675100);
      x4125 = x4154
      val x4156 = x4124._3;
      val x4157 = x4156.hashCode();
      val x4158 = -862048943.*(x4157);
      val x4159 = x4158.<<(15);
      val x4160 = x4158.>>>(-15);
      val x4161 = x4159.|(x4160);
      val x4162 = x4161.*(461845907);
      val x4163 = x4125;
      val x4164 = x4162.^(x4163);
      val x4165 = x4164.<<(13);
      val x4166 = x4164.>>>(-13);
      val x4167 = x4165.|(x4166);
      val x4168 = x4167.*(5);
      val x4169 = x4168.+(-430675100);
      x4125 = x4169
      val x4171 = x4124._4;
      val x4172 = x4171.hashCode();
      val x4173 = -862048943.*(x4172);
      val x4174 = x4173.<<(15);
      val x4175 = x4173.>>>(-15);
      val x4176 = x4174.|(x4175);
      val x4177 = x4176.*(461845907);
      val x4178 = x4125;
      val x4179 = x4177.^(x4178);
      val x4180 = x4179.<<(13);
      val x4181 = x4179.>>>(-13);
      val x4182 = x4180.|(x4181);
      val x4183 = x4182.*(5);
      val x4184 = x4183.+(-430675100);
      x4125 = x4184
      val x4186 = x4125;
      val x4187 = x4186.^(2);
      val x4188 = x4187.>>>(16);
      val x4189 = x4187.^(x4188);
      val x4190 = x4189.*(-2048144789);
      val x4191 = x4190.>>>(13);
      val x4192 = x4190.^(x4191);
      val x4193 = x4192.*(-1028477387);
      val x4194 = x4193.>>>(16);
      val x4195 = x4193.^(x4194);
      x4195
    }
    override def cmp(x4197 : SEntry10_IIIIIITIDS , x4198 : SEntry10_IIIIIITIDS) = {
      val x4199 = x4197._1;
      val x4200 = x4198._1;
      val x4201 = x4199.==(x4200);
      val x4205 = x4201.&&({
        val x4202 = x4197._2;
        val x4203 = x4198._2;
        val x4204 = x4202.==(x4203);
        x4204
      });
      val x4209 = x4205.&&({
        val x4206 = x4197._3;
        val x4207 = x4198._3;
        val x4208 = x4206.==(x4207);
        x4208
      });
      val x4213 = x4209.&&({
        val x4210 = x4197._4;
        val x4211 = x4198._4;
        val x4212 = x4210.==(x4211);
        x4212
      });
      val x4214 = if(x4213) 0 else 1;
      x4214
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4018 : SEntry8_IIIITIIB) = {
      var x4019: Int = -889275714;
      val x4020 = x4018._2;
      val x4021 = x4020.hashCode();
      val x4022 = -862048943.*(x4021);
      val x4023 = x4022.<<(15);
      val x4024 = x4022.>>>(-15);
      val x4025 = x4023.|(x4024);
      val x4026 = x4025.*(461845907);
      val x4027 = x4019;
      val x4028 = x4026.^(x4027);
      val x4029 = x4028.<<(13);
      val x4030 = x4028.>>>(-13);
      val x4031 = x4029.|(x4030);
      val x4032 = x4031.*(5);
      val x4033 = x4032.+(-430675100);
      x4019 = x4033
      val x4035 = x4018._3;
      val x4036 = x4035.hashCode();
      val x4037 = -862048943.*(x4036);
      val x4038 = x4037.<<(15);
      val x4039 = x4037.>>>(-15);
      val x4040 = x4038.|(x4039);
      val x4041 = x4040.*(461845907);
      val x4042 = x4019;
      val x4043 = x4041.^(x4042);
      val x4044 = x4043.<<(13);
      val x4045 = x4043.>>>(-13);
      val x4046 = x4044.|(x4045);
      val x4047 = x4046.*(5);
      val x4048 = x4047.+(-430675100);
      x4019 = x4048
      val x4050 = x4018._4;
      val x4051 = x4050.hashCode();
      val x4052 = -862048943.*(x4051);
      val x4053 = x4052.<<(15);
      val x4054 = x4052.>>>(-15);
      val x4055 = x4053.|(x4054);
      val x4056 = x4055.*(461845907);
      val x4057 = x4019;
      val x4058 = x4056.^(x4057);
      val x4059 = x4058.<<(13);
      val x4060 = x4058.>>>(-13);
      val x4061 = x4059.|(x4060);
      val x4062 = x4061.*(5);
      val x4063 = x4062.+(-430675100);
      x4019 = x4063
      val x4065 = x4019;
      val x4066 = x4065.^(2);
      val x4067 = x4066.>>>(16);
      val x4068 = x4066.^(x4067);
      val x4069 = x4068.*(-2048144789);
      val x4070 = x4069.>>>(13);
      val x4071 = x4069.^(x4070);
      val x4072 = x4071.*(-1028477387);
      val x4073 = x4072.>>>(16);
      val x4074 = x4072.^(x4073);
      x4074
    }
    override def cmp(x4076 : SEntry8_IIIITIIB , x4077 : SEntry8_IIIITIIB) = {
      val x4078 = x4076._2;
      val x4079 = x4077._2;
      val x4080 = x4078.==(x4079);
      val x4084 = x4080.&&({
        val x4081 = x4076._3;
        val x4082 = x4077._3;
        val x4083 = x4081.==(x4082);
        x4083
      });
      val x4088 = x4084.&&({
        val x4085 = x4076._4;
        val x4086 = x4077._4;
        val x4087 = x4085.==(x4086);
        x4087
      });
      val x4089 = if(x4088) 0 else 1;
      x4089
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3448 : SEntry3_III) = {
      var x3449: Int = -889275714;
      val x3450 = x3448._1;
      val x3451 = x3450.hashCode();
      val x3452 = -862048943.*(x3451);
      val x3453 = x3452.<<(15);
      val x3454 = x3452.>>>(-15);
      val x3455 = x3453.|(x3454);
      val x3456 = x3455.*(461845907);
      val x3457 = x3449;
      val x3458 = x3456.^(x3457);
      val x3459 = x3458.<<(13);
      val x3460 = x3458.>>>(-13);
      val x3461 = x3459.|(x3460);
      val x3462 = x3461.*(5);
      val x3463 = x3462.+(-430675100);
      x3449 = x3463
      val x3465 = x3448._2;
      val x3466 = x3465.hashCode();
      val x3467 = -862048943.*(x3466);
      val x3468 = x3467.<<(15);
      val x3469 = x3467.>>>(-15);
      val x3470 = x3468.|(x3469);
      val x3471 = x3470.*(461845907);
      val x3472 = x3449;
      val x3473 = x3471.^(x3472);
      val x3474 = x3473.<<(13);
      val x3475 = x3473.>>>(-13);
      val x3476 = x3474.|(x3475);
      val x3477 = x3476.*(5);
      val x3478 = x3477.+(-430675100);
      x3449 = x3478
      val x3480 = x3448._3;
      val x3481 = x3480.hashCode();
      val x3482 = -862048943.*(x3481);
      val x3483 = x3482.<<(15);
      val x3484 = x3482.>>>(-15);
      val x3485 = x3483.|(x3484);
      val x3486 = x3485.*(461845907);
      val x3487 = x3449;
      val x3488 = x3486.^(x3487);
      val x3489 = x3488.<<(13);
      val x3490 = x3488.>>>(-13);
      val x3491 = x3489.|(x3490);
      val x3492 = x3491.*(5);
      val x3493 = x3492.+(-430675100);
      x3449 = x3493
      val x3495 = x3449;
      val x3496 = x3495.^(2);
      val x3497 = x3496.>>>(16);
      val x3498 = x3496.^(x3497);
      val x3499 = x3498.*(-2048144789);
      val x3500 = x3499.>>>(13);
      val x3501 = x3499.^(x3500);
      val x3502 = x3501.*(-1028477387);
      val x3503 = x3502.>>>(16);
      val x3504 = x3502.^(x3503);
      x3504
    }
    override def cmp(x3506 : SEntry3_III , x3507 : SEntry3_III) = {
      val x3508 = x3506._1;
      val x3509 = x3507._1;
      val x3510 = x3508.==(x3509);
      val x3514 = x3510.&&({
        val x3511 = x3506._2;
        val x3512 = x3507._2;
        val x3513 = x3511.==(x3512);
        x3513
      });
      val x3518 = x3514.&&({
        val x3515 = x3506._3;
        val x3516 = x3507._3;
        val x3517 = x3515.==(x3516);
        x3517
      });
      val x3519 = if(x3518) 0 else 1;
      x3519
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4217 : SEntry10_IIIIIITIDS) = {
      var x4218: Int = -889275714;
      val x4219 = x4217._1;
      val x4220 = x4219.hashCode();
      val x4221 = -862048943.*(x4220);
      val x4222 = x4221.<<(15);
      val x4223 = x4221.>>>(-15);
      val x4224 = x4222.|(x4223);
      val x4225 = x4224.*(461845907);
      val x4226 = x4218;
      val x4227 = x4225.^(x4226);
      val x4228 = x4227.<<(13);
      val x4229 = x4227.>>>(-13);
      val x4230 = x4228.|(x4229);
      val x4231 = x4230.*(5);
      val x4232 = x4231.+(-430675100);
      x4218 = x4232
      val x4234 = x4217._2;
      val x4235 = x4234.hashCode();
      val x4236 = -862048943.*(x4235);
      val x4237 = x4236.<<(15);
      val x4238 = x4236.>>>(-15);
      val x4239 = x4237.|(x4238);
      val x4240 = x4239.*(461845907);
      val x4241 = x4218;
      val x4242 = x4240.^(x4241);
      val x4243 = x4242.<<(13);
      val x4244 = x4242.>>>(-13);
      val x4245 = x4243.|(x4244);
      val x4246 = x4245.*(5);
      val x4247 = x4246.+(-430675100);
      x4218 = x4247
      val x4249 = x4217._3;
      val x4250 = x4249.hashCode();
      val x4251 = -862048943.*(x4250);
      val x4252 = x4251.<<(15);
      val x4253 = x4251.>>>(-15);
      val x4254 = x4252.|(x4253);
      val x4255 = x4254.*(461845907);
      val x4256 = x4218;
      val x4257 = x4255.^(x4256);
      val x4258 = x4257.<<(13);
      val x4259 = x4257.>>>(-13);
      val x4260 = x4258.|(x4259);
      val x4261 = x4260.*(5);
      val x4262 = x4261.+(-430675100);
      x4218 = x4262
      val x4264 = x4218;
      val x4265 = x4264.^(2);
      val x4266 = x4265.>>>(16);
      val x4267 = x4265.^(x4266);
      val x4268 = x4267.*(-2048144789);
      val x4269 = x4268.>>>(13);
      val x4270 = x4268.^(x4269);
      val x4271 = x4270.*(-1028477387);
      val x4272 = x4271.>>>(16);
      val x4273 = x4271.^(x4272);
      x4273
    }
    override def cmp(x4275 : SEntry10_IIIIIITIDS , x4276 : SEntry10_IIIIIITIDS) = {
      val x4277 = x4275._1;
      val x4278 = x4276._1;
      val x4279 = x4277.==(x4278);
      val x4283 = x4279.&&({
        val x4280 = x4275._2;
        val x4281 = x4276._2;
        val x4282 = x4280.==(x4281);
        x4282
      });
      val x4287 = x4283.&&({
        val x4284 = x4275._3;
        val x4285 = x4276._3;
        val x4286 = x4284.==(x4285);
        x4286
      });
      val x4288 = if(x4287) 0 else 1;
      x4288
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3575 : SEntry3_III) = {
      var x3576: Int = -889275714;
      val x3577 = x3575._2;
      val x3578 = x3577.hashCode();
      val x3579 = -862048943.*(x3578);
      val x3580 = x3579.<<(15);
      val x3581 = x3579.>>>(-15);
      val x3582 = x3580.|(x3581);
      val x3583 = x3582.*(461845907);
      val x3584 = x3576;
      val x3585 = x3583.^(x3584);
      val x3586 = x3585.<<(13);
      val x3587 = x3585.>>>(-13);
      val x3588 = x3586.|(x3587);
      val x3589 = x3588.*(5);
      val x3590 = x3589.+(-430675100);
      x3576 = x3590
      val x3592 = x3575._3;
      val x3593 = x3592.hashCode();
      val x3594 = -862048943.*(x3593);
      val x3595 = x3594.<<(15);
      val x3596 = x3594.>>>(-15);
      val x3597 = x3595.|(x3596);
      val x3598 = x3597.*(461845907);
      val x3599 = x3576;
      val x3600 = x3598.^(x3599);
      val x3601 = x3600.<<(13);
      val x3602 = x3600.>>>(-13);
      val x3603 = x3601.|(x3602);
      val x3604 = x3603.*(5);
      val x3605 = x3604.+(-430675100);
      x3576 = x3605
      val x3607 = x3576;
      val x3608 = x3607.^(2);
      val x3609 = x3608.>>>(16);
      val x3610 = x3608.^(x3609);
      val x3611 = x3610.*(-2048144789);
      val x3612 = x3611.>>>(13);
      val x3613 = x3611.^(x3612);
      val x3614 = x3613.*(-1028477387);
      val x3615 = x3614.>>>(16);
      val x3616 = x3614.^(x3615);
      x3616
    }
    override def cmp(x3618 : SEntry3_III , x3619 : SEntry3_III) = {
      val x3620 = x3618._2;
      val x3621 = x3619._2;
      val x3622 = x3620.==(x3621);
      val x3626 = x3622.&&({
        val x3623 = x3618._3;
        val x3624 = x3619._3;
        val x3625 = x3623.==(x3624);
        x3625
      });
      val x3627 = if(x3626) 0 else 1;
      x3627
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3637 : SEntry8_IIIIITDS) = {
      var x3638: Int = -889275714;
      val x3639 = x3637._1;
      val x3640 = x3639.hashCode();
      val x3641 = -862048943.*(x3640);
      val x3642 = x3641.<<(15);
      val x3643 = x3641.>>>(-15);
      val x3644 = x3642.|(x3643);
      val x3645 = x3644.*(461845907);
      val x3646 = x3638;
      val x3647 = x3645.^(x3646);
      val x3648 = x3647.<<(13);
      val x3649 = x3647.>>>(-13);
      val x3650 = x3648.|(x3649);
      val x3651 = x3650.*(5);
      val x3652 = x3651.+(-430675100);
      x3638 = x3652
      val x3654 = x3637._2;
      val x3655 = x3654.hashCode();
      val x3656 = -862048943.*(x3655);
      val x3657 = x3656.<<(15);
      val x3658 = x3656.>>>(-15);
      val x3659 = x3657.|(x3658);
      val x3660 = x3659.*(461845907);
      val x3661 = x3638;
      val x3662 = x3660.^(x3661);
      val x3663 = x3662.<<(13);
      val x3664 = x3662.>>>(-13);
      val x3665 = x3663.|(x3664);
      val x3666 = x3665.*(5);
      val x3667 = x3666.+(-430675100);
      x3638 = x3667
      val x3669 = x3637._3;
      val x3670 = x3669.hashCode();
      val x3671 = -862048943.*(x3670);
      val x3672 = x3671.<<(15);
      val x3673 = x3671.>>>(-15);
      val x3674 = x3672.|(x3673);
      val x3675 = x3674.*(461845907);
      val x3676 = x3638;
      val x3677 = x3675.^(x3676);
      val x3678 = x3677.<<(13);
      val x3679 = x3677.>>>(-13);
      val x3680 = x3678.|(x3679);
      val x3681 = x3680.*(5);
      val x3682 = x3681.+(-430675100);
      x3638 = x3682
      val x3684 = x3637._4;
      val x3685 = x3684.hashCode();
      val x3686 = -862048943.*(x3685);
      val x3687 = x3686.<<(15);
      val x3688 = x3686.>>>(-15);
      val x3689 = x3687.|(x3688);
      val x3690 = x3689.*(461845907);
      val x3691 = x3638;
      val x3692 = x3690.^(x3691);
      val x3693 = x3692.<<(13);
      val x3694 = x3692.>>>(-13);
      val x3695 = x3693.|(x3694);
      val x3696 = x3695.*(5);
      val x3697 = x3696.+(-430675100);
      x3638 = x3697
      val x3699 = x3637._5;
      val x3700 = x3699.hashCode();
      val x3701 = -862048943.*(x3700);
      val x3702 = x3701.<<(15);
      val x3703 = x3701.>>>(-15);
      val x3704 = x3702.|(x3703);
      val x3705 = x3704.*(461845907);
      val x3706 = x3638;
      val x3707 = x3705.^(x3706);
      val x3708 = x3707.<<(13);
      val x3709 = x3707.>>>(-13);
      val x3710 = x3708.|(x3709);
      val x3711 = x3710.*(5);
      val x3712 = x3711.+(-430675100);
      x3638 = x3712
      val x3714 = x3637._6;
      val x3715 = x3714.hashCode();
      val x3716 = -862048943.*(x3715);
      val x3717 = x3716.<<(15);
      val x3718 = x3716.>>>(-15);
      val x3719 = x3717.|(x3718);
      val x3720 = x3719.*(461845907);
      val x3721 = x3638;
      val x3722 = x3720.^(x3721);
      val x3723 = x3722.<<(13);
      val x3724 = x3722.>>>(-13);
      val x3725 = x3723.|(x3724);
      val x3726 = x3725.*(5);
      val x3727 = x3726.+(-430675100);
      x3638 = x3727
      val x3729 = x3637._7;
      val x3730 = x3729.hashCode();
      val x3731 = -862048943.*(x3730);
      val x3732 = x3731.<<(15);
      val x3733 = x3731.>>>(-15);
      val x3734 = x3732.|(x3733);
      val x3735 = x3734.*(461845907);
      val x3736 = x3638;
      val x3737 = x3735.^(x3736);
      val x3738 = x3737.<<(13);
      val x3739 = x3737.>>>(-13);
      val x3740 = x3738.|(x3739);
      val x3741 = x3740.*(5);
      val x3742 = x3741.+(-430675100);
      x3638 = x3742
      val x3744 = x3637._8;
      val x3745 = x3744.hashCode();
      val x3746 = -862048943.*(x3745);
      val x3747 = x3746.<<(15);
      val x3748 = x3746.>>>(-15);
      val x3749 = x3747.|(x3748);
      val x3750 = x3749.*(461845907);
      val x3751 = x3638;
      val x3752 = x3750.^(x3751);
      val x3753 = x3752.<<(13);
      val x3754 = x3752.>>>(-13);
      val x3755 = x3753.|(x3754);
      val x3756 = x3755.*(5);
      val x3757 = x3756.+(-430675100);
      x3638 = x3757
      val x3759 = x3638;
      val x3760 = x3759.^(2);
      val x3761 = x3760.>>>(16);
      val x3762 = x3760.^(x3761);
      val x3763 = x3762.*(-2048144789);
      val x3764 = x3763.>>>(13);
      val x3765 = x3763.^(x3764);
      val x3766 = x3765.*(-1028477387);
      val x3767 = x3766.>>>(16);
      val x3768 = x3766.^(x3767);
      x3768
    }
    override def cmp(x3770 : SEntry8_IIIIITDS , x3771 : SEntry8_IIIIITDS) = {
      val x3772 = x3770._1;
      val x3773 = x3771._1;
      val x3774 = x3772.==(-1);
      val x3776 = x3774.||({
        val x3775 = x3773.==(-1);
        x3775
      });
      val x3778 = x3776.||({
        val x3777 = x3772.==(x3773);
        x3777
      });
      val x3786 = x3778.&&({
        val x3779 = x3770._2;
        val x3780 = x3771._2;
        val x3781 = x3779.==(-1);
        val x3783 = x3781.||({
          val x3782 = x3780.==(-1);
          x3782
        });
        val x3785 = x3783.||({
          val x3784 = x3779.==(x3780);
          x3784
        });
        x3785
      });
      val x3794 = x3786.&&({
        val x3787 = x3770._3;
        val x3788 = x3771._3;
        val x3789 = x3787.==(-1);
        val x3791 = x3789.||({
          val x3790 = x3788.==(-1);
          x3790
        });
        val x3793 = x3791.||({
          val x3792 = x3787.==(x3788);
          x3792
        });
        x3793
      });
      val x3802 = x3794.&&({
        val x3795 = x3770._4;
        val x3796 = x3771._4;
        val x3797 = x3795.==(-1);
        val x3799 = x3797.||({
          val x3798 = x3796.==(-1);
          x3798
        });
        val x3801 = x3799.||({
          val x3800 = x3795.==(x3796);
          x3800
        });
        x3801
      });
      val x3810 = x3802.&&({
        val x3803 = x3770._5;
        val x3804 = x3771._5;
        val x3805 = x3803.==(-1);
        val x3807 = x3805.||({
          val x3806 = x3804.==(-1);
          x3806
        });
        val x3809 = x3807.||({
          val x3808 = x3803.==(x3804);
          x3808
        });
        x3809
      });
      val x3818 = x3810.&&({
        val x3811 = x3770._6;
        val x3812 = x3771._6;
        val x3813 = x3811.==(null);
        val x3815 = x3813.||({
          val x3814 = x3812.==(null);
          x3814
        });
        val x3817 = x3815.||({
          val x3816 = x3811.==(x3812);
          x3816
        });
        x3817
      });
      val x3826 = x3818.&&({
        val x3819 = x3770._7;
        val x3820 = x3771._7;
        val x3821 = x3819.==(-1.0);
        val x3823 = x3821.||({
          val x3822 = x3820.==(-1.0);
          x3822
        });
        val x3825 = x3823.||({
          val x3824 = x3819.==(x3820);
          x3824
        });
        x3825
      });
      val x3827 = if(x3826) 0 else 1;
      x3827
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4323 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4324: Int = -889275714;
      val x4325 = x4323._2;
      val x4326 = x4325.hashCode();
      val x4327 = -862048943.*(x4326);
      val x4328 = x4327.<<(15);
      val x4329 = x4327.>>>(-15);
      val x4330 = x4328.|(x4329);
      val x4331 = x4330.*(461845907);
      val x4332 = x4324;
      val x4333 = x4331.^(x4332);
      val x4334 = x4333.<<(13);
      val x4335 = x4333.>>>(-13);
      val x4336 = x4334.|(x4335);
      val x4337 = x4336.*(5);
      val x4338 = x4337.+(-430675100);
      x4324 = x4338
      val x4340 = x4323._3;
      val x4341 = x4340.hashCode();
      val x4342 = -862048943.*(x4341);
      val x4343 = x4342.<<(15);
      val x4344 = x4342.>>>(-15);
      val x4345 = x4343.|(x4344);
      val x4346 = x4345.*(461845907);
      val x4347 = x4324;
      val x4348 = x4346.^(x4347);
      val x4349 = x4348.<<(13);
      val x4350 = x4348.>>>(-13);
      val x4351 = x4349.|(x4350);
      val x4352 = x4351.*(5);
      val x4353 = x4352.+(-430675100);
      x4324 = x4353
      val x4355 = x4323._6;
      val x4356 = x4355.hashCode();
      val x4357 = -862048943.*(x4356);
      val x4358 = x4357.<<(15);
      val x4359 = x4357.>>>(-15);
      val x4360 = x4358.|(x4359);
      val x4361 = x4360.*(461845907);
      val x4362 = x4324;
      val x4363 = x4361.^(x4362);
      val x4364 = x4363.<<(13);
      val x4365 = x4363.>>>(-13);
      val x4366 = x4364.|(x4365);
      val x4367 = x4366.*(5);
      val x4368 = x4367.+(-430675100);
      x4324 = x4368
      val x4370 = x4324;
      val x4371 = x4370.^(2);
      val x4372 = x4371.>>>(16);
      val x4373 = x4371.^(x4372);
      val x4374 = x4373.*(-2048144789);
      val x4375 = x4374.>>>(13);
      val x4376 = x4374.^(x4375);
      val x4377 = x4376.*(-1028477387);
      val x4378 = x4377.>>>(16);
      val x4379 = x4377.^(x4378);
      x4379
    }
    override def cmp(x4381 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4382 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4383 = x4381._2;
      val x4384 = x4382._2;
      val x4385 = x4383.==(x4384);
      val x4389 = x4385.&&({
        val x4386 = x4381._3;
        val x4387 = x4382._3;
        val x4388 = x4386.==(x4387);
        x4388
      });
      val x4393 = x4389.&&({
        val x4390 = x4381._6;
        val x4391 = x4382._6;
        val x4392 = x4390.==(x4391);
        x4392
      });
      val x4394 = if(x4393) 0 else 1;
      x4394
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3876 : SEntry8_IIIITIIB) = {
      var x3877: Int = -889275714;
      val x3878 = x3876._1;
      val x3879 = x3878.hashCode();
      val x3880 = -862048943.*(x3879);
      val x3881 = x3880.<<(15);
      val x3882 = x3880.>>>(-15);
      val x3883 = x3881.|(x3882);
      val x3884 = x3883.*(461845907);
      val x3885 = x3877;
      val x3886 = x3884.^(x3885);
      val x3887 = x3886.<<(13);
      val x3888 = x3886.>>>(-13);
      val x3889 = x3887.|(x3888);
      val x3890 = x3889.*(5);
      val x3891 = x3890.+(-430675100);
      x3877 = x3891
      val x3893 = x3876._2;
      val x3894 = x3893.hashCode();
      val x3895 = -862048943.*(x3894);
      val x3896 = x3895.<<(15);
      val x3897 = x3895.>>>(-15);
      val x3898 = x3896.|(x3897);
      val x3899 = x3898.*(461845907);
      val x3900 = x3877;
      val x3901 = x3899.^(x3900);
      val x3902 = x3901.<<(13);
      val x3903 = x3901.>>>(-13);
      val x3904 = x3902.|(x3903);
      val x3905 = x3904.*(5);
      val x3906 = x3905.+(-430675100);
      x3877 = x3906
      val x3908 = x3876._3;
      val x3909 = x3908.hashCode();
      val x3910 = -862048943.*(x3909);
      val x3911 = x3910.<<(15);
      val x3912 = x3910.>>>(-15);
      val x3913 = x3911.|(x3912);
      val x3914 = x3913.*(461845907);
      val x3915 = x3877;
      val x3916 = x3914.^(x3915);
      val x3917 = x3916.<<(13);
      val x3918 = x3916.>>>(-13);
      val x3919 = x3917.|(x3918);
      val x3920 = x3919.*(5);
      val x3921 = x3920.+(-430675100);
      x3877 = x3921
      val x3923 = x3877;
      val x3924 = x3923.^(2);
      val x3925 = x3924.>>>(16);
      val x3926 = x3924.^(x3925);
      val x3927 = x3926.*(-2048144789);
      val x3928 = x3927.>>>(13);
      val x3929 = x3927.^(x3928);
      val x3930 = x3929.*(-1028477387);
      val x3931 = x3930.>>>(16);
      val x3932 = x3930.^(x3931);
      x3932
    }
    override def cmp(x3934 : SEntry8_IIIITIIB , x3935 : SEntry8_IIIITIIB) = {
      val x3936 = x3934._1;
      val x3937 = x3935._1;
      val x3938 = x3936.==(x3937);
      val x3942 = x3938.&&({
        val x3939 = x3934._2;
        val x3940 = x3935._2;
        val x3941 = x3939.==(x3940);
        x3941
      });
      val x3946 = x3942.&&({
        val x3943 = x3934._3;
        val x3944 = x3935._3;
        val x3945 = x3943.==(x3944);
        x3945
      });
      val x3947 = if(x3946) 0 else 1;
      x3947
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3522 : SEntry3_III) = {
      var x3523: Int = -889275714;
      val x3524 = x3522._2;
      val x3525 = x3524.hashCode();
      val x3526 = -862048943.*(x3525);
      val x3527 = x3526.<<(15);
      val x3528 = x3526.>>>(-15);
      val x3529 = x3527.|(x3528);
      val x3530 = x3529.*(461845907);
      val x3531 = x3523;
      val x3532 = x3530.^(x3531);
      val x3533 = x3532.<<(13);
      val x3534 = x3532.>>>(-13);
      val x3535 = x3533.|(x3534);
      val x3536 = x3535.*(5);
      val x3537 = x3536.+(-430675100);
      x3523 = x3537
      val x3539 = x3522._3;
      val x3540 = x3539.hashCode();
      val x3541 = -862048943.*(x3540);
      val x3542 = x3541.<<(15);
      val x3543 = x3541.>>>(-15);
      val x3544 = x3542.|(x3543);
      val x3545 = x3544.*(461845907);
      val x3546 = x3523;
      val x3547 = x3545.^(x3546);
      val x3548 = x3547.<<(13);
      val x3549 = x3547.>>>(-13);
      val x3550 = x3548.|(x3549);
      val x3551 = x3550.*(5);
      val x3552 = x3551.+(-430675100);
      x3523 = x3552
      val x3554 = x3523;
      val x3555 = x3554.^(2);
      val x3556 = x3555.>>>(16);
      val x3557 = x3555.^(x3556);
      val x3558 = x3557.*(-2048144789);
      val x3559 = x3558.>>>(13);
      val x3560 = x3558.^(x3559);
      val x3561 = x3560.*(-1028477387);
      val x3562 = x3561.>>>(16);
      val x3563 = x3561.^(x3562);
      x3563
    }
    override def cmp(x3565 : SEntry3_III , x3566 : SEntry3_III) = {
      val x3567 = x3565._1;
      val x3568 = x3566._1;
      val x3569 = x3567.==(x3568);
      val x3570 = x3567.>(x3568);
      val x3571 = if(x3570) 1 else -1;
      val x3572 = if(x3569) 0 else x3571;
      x3572
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3950 : SEntry8_IIIITIIB) = {
      var x3951: Int = -889275714;
      val x3952 = x3950._2;
      val x3953 = x3952.hashCode();
      val x3954 = -862048943.*(x3953);
      val x3955 = x3954.<<(15);
      val x3956 = x3954.>>>(-15);
      val x3957 = x3955.|(x3956);
      val x3958 = x3957.*(461845907);
      val x3959 = x3951;
      val x3960 = x3958.^(x3959);
      val x3961 = x3960.<<(13);
      val x3962 = x3960.>>>(-13);
      val x3963 = x3961.|(x3962);
      val x3964 = x3963.*(5);
      val x3965 = x3964.+(-430675100);
      x3951 = x3965
      val x3967 = x3950._3;
      val x3968 = x3967.hashCode();
      val x3969 = -862048943.*(x3968);
      val x3970 = x3969.<<(15);
      val x3971 = x3969.>>>(-15);
      val x3972 = x3970.|(x3971);
      val x3973 = x3972.*(461845907);
      val x3974 = x3951;
      val x3975 = x3973.^(x3974);
      val x3976 = x3975.<<(13);
      val x3977 = x3975.>>>(-13);
      val x3978 = x3976.|(x3977);
      val x3979 = x3978.*(5);
      val x3980 = x3979.+(-430675100);
      x3951 = x3980
      val x3982 = x3950._4;
      val x3983 = x3982.hashCode();
      val x3984 = -862048943.*(x3983);
      val x3985 = x3984.<<(15);
      val x3986 = x3984.>>>(-15);
      val x3987 = x3985.|(x3986);
      val x3988 = x3987.*(461845907);
      val x3989 = x3951;
      val x3990 = x3988.^(x3989);
      val x3991 = x3990.<<(13);
      val x3992 = x3990.>>>(-13);
      val x3993 = x3991.|(x3992);
      val x3994 = x3993.*(5);
      val x3995 = x3994.+(-430675100);
      x3951 = x3995
      val x3997 = x3951;
      val x3998 = x3997.^(2);
      val x3999 = x3998.>>>(16);
      val x4000 = x3998.^(x3999);
      val x4001 = x4000.*(-2048144789);
      val x4002 = x4001.>>>(13);
      val x4003 = x4001.^(x4002);
      val x4004 = x4003.*(-1028477387);
      val x4005 = x4004.>>>(16);
      val x4006 = x4004.^(x4005);
      x4006
    }
    override def cmp(x4008 : SEntry8_IIIITIIB , x4009 : SEntry8_IIIITIIB) = {
      val x4010 = x4008._1;
      val x4011 = x4009._1;
      val x4012 = x4010.==(x4011);
      val x4013 = x4010.>(x4011);
      val x4014 = if(x4013) 1 else -1;
      val x4015 = if(x4012) 0 else x4014;
      x4015
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3838 : SEntry9_ISSSSSSDD) = {
      var x3839: Int = 0;
      val x3840 = x3838._1;
      val x3841 = x3840.-(1);
      val x3842 = x3839;
      val x3843 = x3842.*(1);
      val x3844 = x3843.+(x3841);
      x3839 = x3844
      val x3846 = x3839;
      x3846
    }
    override def cmp(x3835 : SEntry9_ISSSSSSDD , x3836 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3857 : SEntry5_IISDS) = {
      var x3858: Int = 0;
      val x3859 = x3857._1;
      val x3860 = x3859.-(1);
      val x3861 = x3858;
      val x3862 = x3861.*(100000);
      val x3863 = x3862.+(x3860);
      x3858 = x3863
      val x3865 = x3858;
      x3865
    }
    override def cmp(x3854 : SEntry5_IISDS , x3855 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4102 : SEntry11_IISSSSSSDDI) = {
      var x4103: Int = 0;
      val x4104 = x4102._1;
      val x4105 = x4104.-(1);
      val x4106 = x4103;
      val x4107 = x4106.*(10);
      val x4108 = x4107.+(x4105);
      x4103 = x4108
      val x4110 = x4102._2;
      val x4111 = x4110.-(1);
      val x4112 = x4103;
      val x4113 = x4112.*(1);
      val x4114 = x4113.+(x4111);
      x4103 = x4114
      val x4116 = x4103;
      x4116
    }
    override def cmp(x4099 : SEntry11_IISSSSSSDDI , x4100 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4300 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4301: Int = 0;
      val x4302 = x4300._1;
      val x4303 = x4302.-(1);
      val x4304 = x4301;
      val x4305 = x4304.*(3000);
      val x4306 = x4305.+(x4303);
      x4301 = x4306
      val x4308 = x4300._2;
      val x4309 = x4308.-(1);
      val x4310 = x4301;
      val x4311 = x4310.*(10);
      val x4312 = x4311.+(x4309);
      x4301 = x4312
      val x4314 = x4300._3;
      val x4315 = x4314.-(1);
      val x4316 = x4301;
      val x4317 = x4316.*(1);
      val x4318 = x4317.+(x4315);
      x4301 = x4318
      val x4320 = x4301;
      x4320
    }
    override def cmp(x4297 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4298 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4406 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4407: Int = 0;
      val x4408 = x4406._1;
      val x4409 = x4408.-(1);
      val x4410 = x4407;
      val x4411 = x4410.*(100000);
      val x4412 = x4411.+(x4409);
      x4407 = x4412
      val x4414 = x4406._2;
      val x4415 = x4414.-(1);
      val x4416 = x4407;
      val x4417 = x4416.*(1);
      val x4418 = x4417.+(x4415);
      x4407 = x4418
      val x4420 = x4407;
      x4420
    }
    override def cmp(x4403 : SEntry17_IIISSSSSSSSSSIIIS , x4404 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x7379 = SEntry3_III(-1, -1, -1);
  val x7970 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0);
  val x7966 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7785 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7769 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7554 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null);
  val x7997 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null);
  val x7945 = SEntry5_IISDS(-1, -1, null, -1.0, null);
  val x7404 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7973 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7391 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false);
  val x7531 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null);
  val x7726 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7720 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0);
  val x7518 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7607 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7401 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null);
  val x7595 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false);
  val x7623 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  class DeliveryTx(x3632: Store[SEntry3_III], x3832: Store[SEntry8_IIIIITDS], x3851: Store[SEntry9_ISSSSSSDD], x3870: Store[SEntry5_IISDS], x4094: Store[SEntry8_IIIITIIB], x4121: Store[SEntry11_IISSSSSSDDI], x4293: Store[SEntry10_IIIIIITIDS], x4399: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4425: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val x14 = new Array[Int](10);
      var x15: Int = 1;
      while({
        val x16 = x15;
        (x16.<=(10))
      })
      {
        val x22 = x15;
        x7379._2_=(x22)
        x7379._3_=(x12)
        val x12294 = x731.get(x7379);
        if((x12294.!=(null))) 
        {
          val x7385 = x12294._1;
          val x29 = x15;
          x14.update((x29.-(1)), x7385)
          x3632.delete(x12294)
          val x33 = x15;
          x7391._1_=(x7385)
          x7391._2_=(x33)
          x7391._3_=(x12)
          val x12307 = x754.get(x7391);
          val x7394 = x12307._4;
          x12307._6_=(x13)
          var x40: Double = 0.0;
          val x41 = x15;
          x7401._1_=(x7385)
          x7401._2_=(x41)
          x7401._3_=(x12)
          x767.slice(x7401, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              orderLineEntry._7_=(x11)
              val x46 = x40;
              val x7446 = orderLineEntry._9;
              x40 = (x46.+(x7446))
              ()
            }
          }))
          val x53 = x15;
          x7404._1_=(x7394)
          x7404._2_=(x53)
          x7404._3_=(x12)
          val x12328 = x773.get(x7404);
          val x56 = x40;
          x12328._17 +=(x56)
          x12328._20 +=(1)
          ()
        }
        else
        {
          val x60 = x15;
          x14.update((x60.-(1)), 0)
          ()
        }
        
        val x64 = x15;
        x15 = (x64.+(1))
        ()
      }
      1
    }
  }
  class StockLevelTx(x3632: Store[SEntry3_III], x3832: Store[SEntry8_IIIIITDS], x3851: Store[SEntry9_ISSSSSSDD], x3870: Store[SEntry5_IISDS], x4094: Store[SEntry8_IIIITIIB], x4121: Store[SEntry11_IISSSSSSDDI], x4293: Store[SEntry10_IIIIIITIDS], x4399: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4425: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x68 : Boolean, x69 : Date, x70 : Int, x71 : Int, x72 : Int, x73 : Int) =     {
      x7518._1_=(x72)
      x7518._2_=(x71)
      val x12397 = x761.get(x7518);
      val x7522 = x12397._11;
      var x79: Int = (x7522.-(20));
      val x80 = Set.apply[Int]();
      while({
        val x81 = x79;
        (x81.<(x7522))
      })
      {
        val x83 = x79;
        x7531._1_=(x83)
        x7531._2_=(x72)
        x7531._3_=(x71)
        x767.slice(x7531, ({ x86: SEntry10_IIIIIITIDS => {
            val x7553 = x86._5;
            x7554._1_=(x7553)
            x7554._2_=(x71)
            val x12415 = x779.get(x7554);
            val x7556 = x12415._3;
            if((x7556.<(x73))) 
            {
              val x92 = x80.+=(x7553);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x96 = x79;
        x79 = (x96.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(x3632: Store[SEntry3_III], x3832: Store[SEntry8_IIIIITDS], x3851: Store[SEntry9_ISSSSSSDD], x3870: Store[SEntry5_IISDS], x4094: Store[SEntry8_IIIITIIB], x4121: Store[SEntry11_IISSSSSSDDI], x4293: Store[SEntry10_IIIIIITIDS], x4399: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4425: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x101 : Boolean, x102 : Date, x103 : Int, x104 : Int, x105 : Int, x106 : Int, x107 : Int, x108 : String) =     {
      val x7592 = if((x106.>(0))) 
      {
        val x7604 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7607._2_=(x105)
        x7607._3_=(x104)
        x7607._6_=(x108)
        x774.slice(x7607, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7604.append(custEntry)
            ()
          }
        }))
        val x119 = x7604.size;
        var x121: Int = (x119./(2));
        val x123 = x7604.size;
        if(((x123.%(2)).==(0))) 
        {
          val x126 = x121;
          x121 = (x126.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x137 = x7604.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7651 = c1._4;
            val x7652 = c2._4;
            ((StringExtra.StringCompare(x7651, x7652)).<(0))
          }
        }));
        val x138 = x121;
        val x7622 = x137.apply(x138);
        x7622
      }
      else
      {
        x7623._1_=(x107)
        x7623._2_=(x105)
        x7623._3_=(x104)
        val x12491 = x773.get(x7623);
        x12491
      }
      ;
      val x7593 = x7592._3;
      x7595._2_=(x105)
      x7595._3_=(x104)
      x7595._4_=(x7593)
      val x12499 = x755.get(x7595);
      var x153: Int = 0;
      val x7600 = x12499._1;
      x153 = x7600
      1
    }
  }
  class PaymentTx(x3632: Store[SEntry3_III], x3832: Store[SEntry8_IIIIITDS], x3851: Store[SEntry9_ISSSSSSDD], x3870: Store[SEntry5_IISDS], x4094: Store[SEntry8_IIIITIIB], x4121: Store[SEntry11_IISSSSSSDDI], x4293: Store[SEntry10_IIIIIITIDS], x4399: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4425: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x156 : Boolean, x157 : Date, x158 : Int, x159 : Int, x160 : Int, x161 : Int, x162 : Int, x163 : Int, x164 : Int, x165 : String, x166 : Double) =     {
      x7720._1_=(x159)
      val x12554 = x742.get(x7720);
      x12554._9 +=(x166)
      x7726._1_=(x160)
      x7726._2_=(x159)
      val x12559 = x761.get(x7726);
      x12559._10 +=(x166)
      val x7732 = if((x161.>(0))) 
      {
        val x7766 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7769._2_=(x163)
        x7769._3_=(x162)
        x7769._6_=(x165)
        x774.slice(x7769, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7766.append(custEntry)
            ()
          }
        }))
        val x187 = x7766.size;
        var x189: Int = (x187./(2));
        val x191 = x7766.size;
        if(((x191.%(2)).==(0))) 
        {
          val x194 = x189;
          x189 = (x194.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x205 = x7766.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7834 = c1._4;
            val x7835 = c2._4;
            ((StringExtra.StringCompare(x7834, x7835)).<(0))
          }
        }));
        val x206 = x189;
        val x7784 = x205.apply(x206);
        x7784
      }
      else
      {
        x7785._1_=(x164)
        x7785._2_=(x163)
        x7785._3_=(x162)
        val x12596 = x773.get(x7785);
        x12596
      }
      ;
      val x7733 = x7732._21;
      val x7734 = x7732._14;
      val x214 = x7734.contains("BC");
      if(x214) 
      {
        val x7737 = x7732._1;
        var x218 = "%d %d %d %d %d $%f %s | %s".format(x7737,x163,x162,x160,x159,x166,(x157.toString()),x7733)
        if(x218.size > 500) 
          x218 = x218.substring(0, 500)
        x7732._17 +=(x166)
        x7732._21_=(x218)
        ()
      }
      else
      {
        x7732._17 +=(x166)
        ()
      }
      
      val x7745 = x12554._2;
      val x7746 = x12559._3;
      var x227 = "%.10s    %.10s".format(x7745,x7746)
      if(x227.size > 24) 
        x227 = x227.substring(0, 24)
      val x7749 = x7732._1;
      x3832.insert((SEntry8_IIIIITDS(x7749, x163, x162, x160, x159, x157, x166, x227)))
      1
    }
  }
  class NewOrderTx(x3632: Store[SEntry3_III], x3832: Store[SEntry8_IIIIITDS], x3851: Store[SEntry9_ISSSSSSDD], x3870: Store[SEntry5_IISDS], x4094: Store[SEntry8_IIIITIIB], x4121: Store[SEntry11_IISSSSSSDDI], x4293: Store[SEntry10_IIIIIITIDS], x4399: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4425: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x232 : Boolean, x233 : Date, x234 : Int, x235 : Int, x236 : Int, x237 : Int, x238 : Int, x239 : Int, x240 : Array[Int], x241 : Array[Int], x242 : Array[Int], x243 : Array[Double], x244 : Array[String], x245 : Array[Int], x246 : Array[String], x247 : Array[Double]) =     {
      var x248: Int = 0;
      var x249: Boolean = false;
      val x250 = new Array[String](x238);
      var x251: Boolean = true;
      while({
        val x252 = x248;
        ((x252.<(x238)).&&({
          val x254 = x251;
          x254
        }))
      })
      {
        val x257 = x248;
        val x258 = x240.apply(x257);
        x7945._1_=(x258)
        val x12695 = x747.get(x7945);
        if((x12695.==(null))) 
        {
          x251 = false
          ()
        }
        else
        {
          val x264 = x248;
          val x7953 = x12695._3;
          x244.update(x264, x7953)
          val x267 = x248;
          val x7956 = x12695._4;
          x243.update(x267, x7956)
          val x270 = x248;
          val x7959 = x12695._5;
          x250.update(x270, x7959)
          ()
        }
        
        val x274 = x248;
        x248 = (x274.+(1))
        ()
      }
      val x278 = x251;
      if(x278) 
      {
        x7966._1_=(x237)
        x7966._2_=(x236)
        x7966._3_=(x235)
        val x12718 = x773.get(x7966);
        x7970._1_=(x235)
        val x12721 = x742.get(x7970);
        x7973._1_=(x236)
        x7973._2_=(x235)
        val x12725 = x761.get(x7973);
        val x7976 = x12725._11;
        x12725._11 +=(1)
        x4094.insert((SEntry8_IIIITIIB(x7976, x236, x235, x237, x233, -1, x238, (x239.>(0)))))
        x3632.insert((SEntry3_III(x7976, x236, x235)))
        var x298: Double = 0.0;
        x248 = 0
        while({
          val x300 = x248;
          (x300.<(x238))
        })
        {
          val x302 = x248;
          val x303 = x241.apply(x302);
          val x304 = x248;
          val x305 = x240.apply(x304);
          val x306 = x248;
          val x307 = x242.apply(x306);
          x7997._1_=(x305)
          x7997._2_=(x303)
          val x12748 = x779.get(x7997);
          val x337 = if((x236.==(1))) 
          {
            val x8001 = x12748._4;
            x8001
          }
          else
          {
            val x336 = if((x236.==(2))) 
            {
              val x8004 = x12748._5;
              x8004
            }
            else
            {
              val x335 = if((x236.==(3))) 
              {
                val x8007 = x12748._6;
                x8007
              }
              else
              {
                val x334 = if((x236.==(4))) 
                {
                  val x8010 = x12748._7;
                  x8010
                }
                else
                {
                  val x333 = if((x236.==(5))) 
                  {
                    val x8013 = x12748._8;
                    x8013
                  }
                  else
                  {
                    val x332 = if((x236.==(6))) 
                    {
                      val x8016 = x12748._9;
                      x8016
                    }
                    else
                    {
                      val x331 = if((x236.==(7))) 
                      {
                        val x8019 = x12748._10;
                        x8019
                      }
                      else
                      {
                        val x330 = if((x236.==(8))) 
                        {
                          val x8022 = x12748._11;
                          x8022
                        }
                        else
                        {
                          val x329 = if((x236.==(9))) 
                          {
                            val x8025 = x12748._12;
                            x8025
                          }
                          else
                          {
                            val x8026 = x12748._13;
                            x8026
                          }
                          ;
                          x329
                        }
                        ;
                        x330
                      }
                      ;
                      x331
                    }
                    ;
                    x332
                  }
                  ;
                  x333
                }
                ;
                x334
              }
              ;
              x335
            }
            ;
            x336
          }
          ;
          val x8027 = x12748._3;
          val x339 = x248;
          x245.update(x339, x8027)
          val x8030 = x12718._14;
          val x342 = x8030.contains("original");
          if((x342.&&({
            val x8033 = x12748._17;
            val x344 = x8033.contains("original");
            x344
          }))) 
          {
            val x346 = x248;
            x246.update(x346, "B")
            ()
          }
          else
          {
            val x348 = x248;
            x246.update(x348, "G")
            ()
          }
          
          x12748._3_=((x8027.-(x307)))
          val x355 = if((x8027.<=(x307))) 
          {
            x12748._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x356: Int = 0;
          if((x303.!=(x235))) 
          {
            x356 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8050 = x12718._16;
          val x8051 = x12721._8;
          val x8052 = x12725._9;
          val x364 = x248;
          val x365 = x243.apply(x364);
          val x372 = (((x307.toDouble).*(x365)).*(((1.0.+(x8051)).+(x8052)))).*((1.0.-(x8050)));
          val x373 = x248;
          x247.update(x373, x372)
          val x375 = x298;
          x298 = (x375.+(x372))
          val x378 = x248;
          x4293.insert((SEntry10_IIIIIITIDS(x7976, x236, x235, (x378.+(1)), x305, x303, null, x307, x372, x337)))
          val x383 = x248;
          x248 = (x383.+(1))
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
