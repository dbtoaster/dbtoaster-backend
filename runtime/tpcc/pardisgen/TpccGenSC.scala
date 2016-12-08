
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
  val x3624 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val x3625 = new Store[SEntry3_III](3, x3624);
  val x723 = x3625.index(0, IHash, true, -1)
  val x724 = x3625.index(1, ISliceHeapMin, false, 2)
  val x725 = x3625.index(2, INone, false, -1)
  val x3824 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val x3825 = new Store[SEntry8_IIIIITDS](1, x3824);
  val x730 = x3825.index(0, IList, false, -1)
  val x3843 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val x3844 = new Store[SEntry9_ISSSSSSDD](1, x3843);
  val x735 = x3844.index(0, IDirect, true, 1)
  val x3862 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val x3863 = new Store[SEntry5_IISDS](1, x3862);
  val x740 = x3863.index(0, IDirect, true, 100000)
  val x4086 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val x4087 = new Store[SEntry8_IIIITIIB](3, x4086);
  val x747 = x4087.index(0, IHash, true, -1)
  val x748 = x4087.index(1, ISliceHeapMax, false, 2)
  val x749 = x4087.index(2, INone, false, -1)
  val x4113 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val x4114 = new Store[SEntry11_IISSSSSSDDI](1, x4113);
  val x754 = x4114.index(0, IDirect, true, 10)
  val x4285 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val x4286 = new Store[SEntry10_IIIIIITIDS](2, x4285);
  val x759 = x4286.index(0, IHash, true, -1)
  val x760 = x4286.index(1, IHash, false, -1)
  val x4391 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val x4392 = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4391);
  val x766 = x4392.index(0, IDirect, true, 30000)
  val x767 = x4392.index(1, IHash, false, -1)
  val x4417 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val x4418 = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4417);
  val x772 = x4418.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x3625
  val historyTbl = x3825
  val warehouseTbl = x3844
  val itemTbl = x3863
  val orderTbl = x4087
  val districtTbl = x4114
  val orderLineTbl = x4286
  val customerTbl = x4392
  val stockTbl = x4418
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4117 : SEntry10_IIIIIITIDS) = {
      var x4118: Int = -889275714;
      val x4119 = x4117._1;
      val x4120 = x4119.hashCode();
      val x4121 = -862048943.*(x4120);
      val x4122 = x4121.<<(15);
      val x4123 = x4121.>>>(-15);
      val x4124 = x4122.|(x4123);
      val x4125 = x4124.*(461845907);
      val x4126 = x4118;
      val x4127 = x4125.^(x4126);
      val x4128 = x4127.<<(13);
      val x4129 = x4127.>>>(-13);
      val x4130 = x4128.|(x4129);
      val x4131 = x4130.*(5);
      val x4132 = x4131.+(-430675100);
      x4118 = x4132
      val x4134 = x4117._2;
      val x4135 = x4134.hashCode();
      val x4136 = -862048943.*(x4135);
      val x4137 = x4136.<<(15);
      val x4138 = x4136.>>>(-15);
      val x4139 = x4137.|(x4138);
      val x4140 = x4139.*(461845907);
      val x4141 = x4118;
      val x4142 = x4140.^(x4141);
      val x4143 = x4142.<<(13);
      val x4144 = x4142.>>>(-13);
      val x4145 = x4143.|(x4144);
      val x4146 = x4145.*(5);
      val x4147 = x4146.+(-430675100);
      x4118 = x4147
      val x4149 = x4117._3;
      val x4150 = x4149.hashCode();
      val x4151 = -862048943.*(x4150);
      val x4152 = x4151.<<(15);
      val x4153 = x4151.>>>(-15);
      val x4154 = x4152.|(x4153);
      val x4155 = x4154.*(461845907);
      val x4156 = x4118;
      val x4157 = x4155.^(x4156);
      val x4158 = x4157.<<(13);
      val x4159 = x4157.>>>(-13);
      val x4160 = x4158.|(x4159);
      val x4161 = x4160.*(5);
      val x4162 = x4161.+(-430675100);
      x4118 = x4162
      val x4164 = x4117._4;
      val x4165 = x4164.hashCode();
      val x4166 = -862048943.*(x4165);
      val x4167 = x4166.<<(15);
      val x4168 = x4166.>>>(-15);
      val x4169 = x4167.|(x4168);
      val x4170 = x4169.*(461845907);
      val x4171 = x4118;
      val x4172 = x4170.^(x4171);
      val x4173 = x4172.<<(13);
      val x4174 = x4172.>>>(-13);
      val x4175 = x4173.|(x4174);
      val x4176 = x4175.*(5);
      val x4177 = x4176.+(-430675100);
      x4118 = x4177
      val x4179 = x4118;
      val x4180 = x4179.^(2);
      val x4181 = x4180.>>>(16);
      val x4182 = x4180.^(x4181);
      val x4183 = x4182.*(-2048144789);
      val x4184 = x4183.>>>(13);
      val x4185 = x4183.^(x4184);
      val x4186 = x4185.*(-1028477387);
      val x4187 = x4186.>>>(16);
      val x4188 = x4186.^(x4187);
      x4188
    }
    override def cmp(x4190 : SEntry10_IIIIIITIDS , x4191 : SEntry10_IIIIIITIDS) = {
      val x4192 = x4190._1;
      val x4193 = x4191._1;
      val x4194 = x4192.==(x4193);
      val x4198 = x4194.&&({
        val x4195 = x4190._2;
        val x4196 = x4191._2;
        val x4197 = x4195.==(x4196);
        x4197
      });
      val x4202 = x4198.&&({
        val x4199 = x4190._3;
        val x4200 = x4191._3;
        val x4201 = x4199.==(x4200);
        x4201
      });
      val x4206 = x4202.&&({
        val x4203 = x4190._4;
        val x4204 = x4191._4;
        val x4205 = x4203.==(x4204);
        x4205
      });
      val x4207 = if(x4206) 0 else 1;
      x4207
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4011 : SEntry8_IIIITIIB) = {
      var x4012: Int = -889275714;
      val x4013 = x4011._2;
      val x4014 = x4013.hashCode();
      val x4015 = -862048943.*(x4014);
      val x4016 = x4015.<<(15);
      val x4017 = x4015.>>>(-15);
      val x4018 = x4016.|(x4017);
      val x4019 = x4018.*(461845907);
      val x4020 = x4012;
      val x4021 = x4019.^(x4020);
      val x4022 = x4021.<<(13);
      val x4023 = x4021.>>>(-13);
      val x4024 = x4022.|(x4023);
      val x4025 = x4024.*(5);
      val x4026 = x4025.+(-430675100);
      x4012 = x4026
      val x4028 = x4011._3;
      val x4029 = x4028.hashCode();
      val x4030 = -862048943.*(x4029);
      val x4031 = x4030.<<(15);
      val x4032 = x4030.>>>(-15);
      val x4033 = x4031.|(x4032);
      val x4034 = x4033.*(461845907);
      val x4035 = x4012;
      val x4036 = x4034.^(x4035);
      val x4037 = x4036.<<(13);
      val x4038 = x4036.>>>(-13);
      val x4039 = x4037.|(x4038);
      val x4040 = x4039.*(5);
      val x4041 = x4040.+(-430675100);
      x4012 = x4041
      val x4043 = x4011._4;
      val x4044 = x4043.hashCode();
      val x4045 = -862048943.*(x4044);
      val x4046 = x4045.<<(15);
      val x4047 = x4045.>>>(-15);
      val x4048 = x4046.|(x4047);
      val x4049 = x4048.*(461845907);
      val x4050 = x4012;
      val x4051 = x4049.^(x4050);
      val x4052 = x4051.<<(13);
      val x4053 = x4051.>>>(-13);
      val x4054 = x4052.|(x4053);
      val x4055 = x4054.*(5);
      val x4056 = x4055.+(-430675100);
      x4012 = x4056
      val x4058 = x4012;
      val x4059 = x4058.^(2);
      val x4060 = x4059.>>>(16);
      val x4061 = x4059.^(x4060);
      val x4062 = x4061.*(-2048144789);
      val x4063 = x4062.>>>(13);
      val x4064 = x4062.^(x4063);
      val x4065 = x4064.*(-1028477387);
      val x4066 = x4065.>>>(16);
      val x4067 = x4065.^(x4066);
      x4067
    }
    override def cmp(x4069 : SEntry8_IIIITIIB , x4070 : SEntry8_IIIITIIB) = {
      val x4071 = x4069._2;
      val x4072 = x4070._2;
      val x4073 = x4071.==(x4072);
      val x4077 = x4073.&&({
        val x4074 = x4069._3;
        val x4075 = x4070._3;
        val x4076 = x4074.==(x4075);
        x4076
      });
      val x4081 = x4077.&&({
        val x4078 = x4069._4;
        val x4079 = x4070._4;
        val x4080 = x4078.==(x4079);
        x4080
      });
      val x4082 = if(x4081) 0 else 1;
      x4082
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3441 : SEntry3_III) = {
      var x3442: Int = -889275714;
      val x3443 = x3441._1;
      val x3444 = x3443.hashCode();
      val x3445 = -862048943.*(x3444);
      val x3446 = x3445.<<(15);
      val x3447 = x3445.>>>(-15);
      val x3448 = x3446.|(x3447);
      val x3449 = x3448.*(461845907);
      val x3450 = x3442;
      val x3451 = x3449.^(x3450);
      val x3452 = x3451.<<(13);
      val x3453 = x3451.>>>(-13);
      val x3454 = x3452.|(x3453);
      val x3455 = x3454.*(5);
      val x3456 = x3455.+(-430675100);
      x3442 = x3456
      val x3458 = x3441._2;
      val x3459 = x3458.hashCode();
      val x3460 = -862048943.*(x3459);
      val x3461 = x3460.<<(15);
      val x3462 = x3460.>>>(-15);
      val x3463 = x3461.|(x3462);
      val x3464 = x3463.*(461845907);
      val x3465 = x3442;
      val x3466 = x3464.^(x3465);
      val x3467 = x3466.<<(13);
      val x3468 = x3466.>>>(-13);
      val x3469 = x3467.|(x3468);
      val x3470 = x3469.*(5);
      val x3471 = x3470.+(-430675100);
      x3442 = x3471
      val x3473 = x3441._3;
      val x3474 = x3473.hashCode();
      val x3475 = -862048943.*(x3474);
      val x3476 = x3475.<<(15);
      val x3477 = x3475.>>>(-15);
      val x3478 = x3476.|(x3477);
      val x3479 = x3478.*(461845907);
      val x3480 = x3442;
      val x3481 = x3479.^(x3480);
      val x3482 = x3481.<<(13);
      val x3483 = x3481.>>>(-13);
      val x3484 = x3482.|(x3483);
      val x3485 = x3484.*(5);
      val x3486 = x3485.+(-430675100);
      x3442 = x3486
      val x3488 = x3442;
      val x3489 = x3488.^(2);
      val x3490 = x3489.>>>(16);
      val x3491 = x3489.^(x3490);
      val x3492 = x3491.*(-2048144789);
      val x3493 = x3492.>>>(13);
      val x3494 = x3492.^(x3493);
      val x3495 = x3494.*(-1028477387);
      val x3496 = x3495.>>>(16);
      val x3497 = x3495.^(x3496);
      x3497
    }
    override def cmp(x3499 : SEntry3_III , x3500 : SEntry3_III) = {
      val x3501 = x3499._1;
      val x3502 = x3500._1;
      val x3503 = x3501.==(x3502);
      val x3507 = x3503.&&({
        val x3504 = x3499._2;
        val x3505 = x3500._2;
        val x3506 = x3504.==(x3505);
        x3506
      });
      val x3511 = x3507.&&({
        val x3508 = x3499._3;
        val x3509 = x3500._3;
        val x3510 = x3508.==(x3509);
        x3510
      });
      val x3512 = if(x3511) 0 else 1;
      x3512
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4210 : SEntry10_IIIIIITIDS) = {
      var x4211: Int = -889275714;
      val x4212 = x4210._1;
      val x4213 = x4212.hashCode();
      val x4214 = -862048943.*(x4213);
      val x4215 = x4214.<<(15);
      val x4216 = x4214.>>>(-15);
      val x4217 = x4215.|(x4216);
      val x4218 = x4217.*(461845907);
      val x4219 = x4211;
      val x4220 = x4218.^(x4219);
      val x4221 = x4220.<<(13);
      val x4222 = x4220.>>>(-13);
      val x4223 = x4221.|(x4222);
      val x4224 = x4223.*(5);
      val x4225 = x4224.+(-430675100);
      x4211 = x4225
      val x4227 = x4210._2;
      val x4228 = x4227.hashCode();
      val x4229 = -862048943.*(x4228);
      val x4230 = x4229.<<(15);
      val x4231 = x4229.>>>(-15);
      val x4232 = x4230.|(x4231);
      val x4233 = x4232.*(461845907);
      val x4234 = x4211;
      val x4235 = x4233.^(x4234);
      val x4236 = x4235.<<(13);
      val x4237 = x4235.>>>(-13);
      val x4238 = x4236.|(x4237);
      val x4239 = x4238.*(5);
      val x4240 = x4239.+(-430675100);
      x4211 = x4240
      val x4242 = x4210._3;
      val x4243 = x4242.hashCode();
      val x4244 = -862048943.*(x4243);
      val x4245 = x4244.<<(15);
      val x4246 = x4244.>>>(-15);
      val x4247 = x4245.|(x4246);
      val x4248 = x4247.*(461845907);
      val x4249 = x4211;
      val x4250 = x4248.^(x4249);
      val x4251 = x4250.<<(13);
      val x4252 = x4250.>>>(-13);
      val x4253 = x4251.|(x4252);
      val x4254 = x4253.*(5);
      val x4255 = x4254.+(-430675100);
      x4211 = x4255
      val x4257 = x4211;
      val x4258 = x4257.^(2);
      val x4259 = x4258.>>>(16);
      val x4260 = x4258.^(x4259);
      val x4261 = x4260.*(-2048144789);
      val x4262 = x4261.>>>(13);
      val x4263 = x4261.^(x4262);
      val x4264 = x4263.*(-1028477387);
      val x4265 = x4264.>>>(16);
      val x4266 = x4264.^(x4265);
      x4266
    }
    override def cmp(x4268 : SEntry10_IIIIIITIDS , x4269 : SEntry10_IIIIIITIDS) = {
      val x4270 = x4268._1;
      val x4271 = x4269._1;
      val x4272 = x4270.==(x4271);
      val x4276 = x4272.&&({
        val x4273 = x4268._2;
        val x4274 = x4269._2;
        val x4275 = x4273.==(x4274);
        x4275
      });
      val x4280 = x4276.&&({
        val x4277 = x4268._3;
        val x4278 = x4269._3;
        val x4279 = x4277.==(x4278);
        x4279
      });
      val x4281 = if(x4280) 0 else 1;
      x4281
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3568 : SEntry3_III) = {
      var x3569: Int = -889275714;
      val x3570 = x3568._2;
      val x3571 = x3570.hashCode();
      val x3572 = -862048943.*(x3571);
      val x3573 = x3572.<<(15);
      val x3574 = x3572.>>>(-15);
      val x3575 = x3573.|(x3574);
      val x3576 = x3575.*(461845907);
      val x3577 = x3569;
      val x3578 = x3576.^(x3577);
      val x3579 = x3578.<<(13);
      val x3580 = x3578.>>>(-13);
      val x3581 = x3579.|(x3580);
      val x3582 = x3581.*(5);
      val x3583 = x3582.+(-430675100);
      x3569 = x3583
      val x3585 = x3568._3;
      val x3586 = x3585.hashCode();
      val x3587 = -862048943.*(x3586);
      val x3588 = x3587.<<(15);
      val x3589 = x3587.>>>(-15);
      val x3590 = x3588.|(x3589);
      val x3591 = x3590.*(461845907);
      val x3592 = x3569;
      val x3593 = x3591.^(x3592);
      val x3594 = x3593.<<(13);
      val x3595 = x3593.>>>(-13);
      val x3596 = x3594.|(x3595);
      val x3597 = x3596.*(5);
      val x3598 = x3597.+(-430675100);
      x3569 = x3598
      val x3600 = x3569;
      val x3601 = x3600.^(2);
      val x3602 = x3601.>>>(16);
      val x3603 = x3601.^(x3602);
      val x3604 = x3603.*(-2048144789);
      val x3605 = x3604.>>>(13);
      val x3606 = x3604.^(x3605);
      val x3607 = x3606.*(-1028477387);
      val x3608 = x3607.>>>(16);
      val x3609 = x3607.^(x3608);
      x3609
    }
    override def cmp(x3611 : SEntry3_III , x3612 : SEntry3_III) = {
      val x3613 = x3611._2;
      val x3614 = x3612._2;
      val x3615 = x3613.==(x3614);
      val x3619 = x3615.&&({
        val x3616 = x3611._3;
        val x3617 = x3612._3;
        val x3618 = x3616.==(x3617);
        x3618
      });
      val x3620 = if(x3619) 0 else 1;
      x3620
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3630 : SEntry8_IIIIITDS) = {
      var x3631: Int = -889275714;
      val x3632 = x3630._1;
      val x3633 = x3632.hashCode();
      val x3634 = -862048943.*(x3633);
      val x3635 = x3634.<<(15);
      val x3636 = x3634.>>>(-15);
      val x3637 = x3635.|(x3636);
      val x3638 = x3637.*(461845907);
      val x3639 = x3631;
      val x3640 = x3638.^(x3639);
      val x3641 = x3640.<<(13);
      val x3642 = x3640.>>>(-13);
      val x3643 = x3641.|(x3642);
      val x3644 = x3643.*(5);
      val x3645 = x3644.+(-430675100);
      x3631 = x3645
      val x3647 = x3630._2;
      val x3648 = x3647.hashCode();
      val x3649 = -862048943.*(x3648);
      val x3650 = x3649.<<(15);
      val x3651 = x3649.>>>(-15);
      val x3652 = x3650.|(x3651);
      val x3653 = x3652.*(461845907);
      val x3654 = x3631;
      val x3655 = x3653.^(x3654);
      val x3656 = x3655.<<(13);
      val x3657 = x3655.>>>(-13);
      val x3658 = x3656.|(x3657);
      val x3659 = x3658.*(5);
      val x3660 = x3659.+(-430675100);
      x3631 = x3660
      val x3662 = x3630._3;
      val x3663 = x3662.hashCode();
      val x3664 = -862048943.*(x3663);
      val x3665 = x3664.<<(15);
      val x3666 = x3664.>>>(-15);
      val x3667 = x3665.|(x3666);
      val x3668 = x3667.*(461845907);
      val x3669 = x3631;
      val x3670 = x3668.^(x3669);
      val x3671 = x3670.<<(13);
      val x3672 = x3670.>>>(-13);
      val x3673 = x3671.|(x3672);
      val x3674 = x3673.*(5);
      val x3675 = x3674.+(-430675100);
      x3631 = x3675
      val x3677 = x3630._4;
      val x3678 = x3677.hashCode();
      val x3679 = -862048943.*(x3678);
      val x3680 = x3679.<<(15);
      val x3681 = x3679.>>>(-15);
      val x3682 = x3680.|(x3681);
      val x3683 = x3682.*(461845907);
      val x3684 = x3631;
      val x3685 = x3683.^(x3684);
      val x3686 = x3685.<<(13);
      val x3687 = x3685.>>>(-13);
      val x3688 = x3686.|(x3687);
      val x3689 = x3688.*(5);
      val x3690 = x3689.+(-430675100);
      x3631 = x3690
      val x3692 = x3630._5;
      val x3693 = x3692.hashCode();
      val x3694 = -862048943.*(x3693);
      val x3695 = x3694.<<(15);
      val x3696 = x3694.>>>(-15);
      val x3697 = x3695.|(x3696);
      val x3698 = x3697.*(461845907);
      val x3699 = x3631;
      val x3700 = x3698.^(x3699);
      val x3701 = x3700.<<(13);
      val x3702 = x3700.>>>(-13);
      val x3703 = x3701.|(x3702);
      val x3704 = x3703.*(5);
      val x3705 = x3704.+(-430675100);
      x3631 = x3705
      val x3707 = x3630._6;
      val x3708 = x3707.hashCode();
      val x3709 = -862048943.*(x3708);
      val x3710 = x3709.<<(15);
      val x3711 = x3709.>>>(-15);
      val x3712 = x3710.|(x3711);
      val x3713 = x3712.*(461845907);
      val x3714 = x3631;
      val x3715 = x3713.^(x3714);
      val x3716 = x3715.<<(13);
      val x3717 = x3715.>>>(-13);
      val x3718 = x3716.|(x3717);
      val x3719 = x3718.*(5);
      val x3720 = x3719.+(-430675100);
      x3631 = x3720
      val x3722 = x3630._7;
      val x3723 = x3722.hashCode();
      val x3724 = -862048943.*(x3723);
      val x3725 = x3724.<<(15);
      val x3726 = x3724.>>>(-15);
      val x3727 = x3725.|(x3726);
      val x3728 = x3727.*(461845907);
      val x3729 = x3631;
      val x3730 = x3728.^(x3729);
      val x3731 = x3730.<<(13);
      val x3732 = x3730.>>>(-13);
      val x3733 = x3731.|(x3732);
      val x3734 = x3733.*(5);
      val x3735 = x3734.+(-430675100);
      x3631 = x3735
      val x3737 = x3630._8;
      val x3738 = x3737.hashCode();
      val x3739 = -862048943.*(x3738);
      val x3740 = x3739.<<(15);
      val x3741 = x3739.>>>(-15);
      val x3742 = x3740.|(x3741);
      val x3743 = x3742.*(461845907);
      val x3744 = x3631;
      val x3745 = x3743.^(x3744);
      val x3746 = x3745.<<(13);
      val x3747 = x3745.>>>(-13);
      val x3748 = x3746.|(x3747);
      val x3749 = x3748.*(5);
      val x3750 = x3749.+(-430675100);
      x3631 = x3750
      val x3752 = x3631;
      val x3753 = x3752.^(2);
      val x3754 = x3753.>>>(16);
      val x3755 = x3753.^(x3754);
      val x3756 = x3755.*(-2048144789);
      val x3757 = x3756.>>>(13);
      val x3758 = x3756.^(x3757);
      val x3759 = x3758.*(-1028477387);
      val x3760 = x3759.>>>(16);
      val x3761 = x3759.^(x3760);
      x3761
    }
    override def cmp(x3763 : SEntry8_IIIIITDS , x3764 : SEntry8_IIIIITDS) = {
      val x3765 = x3763._1;
      val x3766 = x3764._1;
      val x3767 = x3765.==(-1);
      val x3769 = x3767.||({
        val x3768 = x3766.==(-1);
        x3768
      });
      val x3771 = x3769.||({
        val x3770 = x3765.==(x3766);
        x3770
      });
      val x3779 = x3771.&&({
        val x3772 = x3763._2;
        val x3773 = x3764._2;
        val x3774 = x3772.==(-1);
        val x3776 = x3774.||({
          val x3775 = x3773.==(-1);
          x3775
        });
        val x3778 = x3776.||({
          val x3777 = x3772.==(x3773);
          x3777
        });
        x3778
      });
      val x3787 = x3779.&&({
        val x3780 = x3763._3;
        val x3781 = x3764._3;
        val x3782 = x3780.==(-1);
        val x3784 = x3782.||({
          val x3783 = x3781.==(-1);
          x3783
        });
        val x3786 = x3784.||({
          val x3785 = x3780.==(x3781);
          x3785
        });
        x3786
      });
      val x3795 = x3787.&&({
        val x3788 = x3763._4;
        val x3789 = x3764._4;
        val x3790 = x3788.==(-1);
        val x3792 = x3790.||({
          val x3791 = x3789.==(-1);
          x3791
        });
        val x3794 = x3792.||({
          val x3793 = x3788.==(x3789);
          x3793
        });
        x3794
      });
      val x3803 = x3795.&&({
        val x3796 = x3763._5;
        val x3797 = x3764._5;
        val x3798 = x3796.==(-1);
        val x3800 = x3798.||({
          val x3799 = x3797.==(-1);
          x3799
        });
        val x3802 = x3800.||({
          val x3801 = x3796.==(x3797);
          x3801
        });
        x3802
      });
      val x3811 = x3803.&&({
        val x3804 = x3763._6;
        val x3805 = x3764._6;
        val x3806 = x3804.==(null);
        val x3808 = x3806.||({
          val x3807 = x3805.==(null);
          x3807
        });
        val x3810 = x3808.||({
          val x3809 = x3804.==(x3805);
          x3809
        });
        x3810
      });
      val x3819 = x3811.&&({
        val x3812 = x3763._7;
        val x3813 = x3764._7;
        val x3814 = x3812.==(-1.0);
        val x3816 = x3814.||({
          val x3815 = x3813.==(-1.0);
          x3815
        });
        val x3818 = x3816.||({
          val x3817 = x3812.==(x3813);
          x3817
        });
        x3818
      });
      val x3820 = if(x3819) 0 else 1;
      x3820
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4316 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4317: Int = -889275714;
      val x4318 = x4316._2;
      val x4319 = x4318.hashCode();
      val x4320 = -862048943.*(x4319);
      val x4321 = x4320.<<(15);
      val x4322 = x4320.>>>(-15);
      val x4323 = x4321.|(x4322);
      val x4324 = x4323.*(461845907);
      val x4325 = x4317;
      val x4326 = x4324.^(x4325);
      val x4327 = x4326.<<(13);
      val x4328 = x4326.>>>(-13);
      val x4329 = x4327.|(x4328);
      val x4330 = x4329.*(5);
      val x4331 = x4330.+(-430675100);
      x4317 = x4331
      val x4333 = x4316._3;
      val x4334 = x4333.hashCode();
      val x4335 = -862048943.*(x4334);
      val x4336 = x4335.<<(15);
      val x4337 = x4335.>>>(-15);
      val x4338 = x4336.|(x4337);
      val x4339 = x4338.*(461845907);
      val x4340 = x4317;
      val x4341 = x4339.^(x4340);
      val x4342 = x4341.<<(13);
      val x4343 = x4341.>>>(-13);
      val x4344 = x4342.|(x4343);
      val x4345 = x4344.*(5);
      val x4346 = x4345.+(-430675100);
      x4317 = x4346
      val x4348 = x4316._6;
      val x4349 = x4348.hashCode();
      val x4350 = -862048943.*(x4349);
      val x4351 = x4350.<<(15);
      val x4352 = x4350.>>>(-15);
      val x4353 = x4351.|(x4352);
      val x4354 = x4353.*(461845907);
      val x4355 = x4317;
      val x4356 = x4354.^(x4355);
      val x4357 = x4356.<<(13);
      val x4358 = x4356.>>>(-13);
      val x4359 = x4357.|(x4358);
      val x4360 = x4359.*(5);
      val x4361 = x4360.+(-430675100);
      x4317 = x4361
      val x4363 = x4317;
      val x4364 = x4363.^(2);
      val x4365 = x4364.>>>(16);
      val x4366 = x4364.^(x4365);
      val x4367 = x4366.*(-2048144789);
      val x4368 = x4367.>>>(13);
      val x4369 = x4367.^(x4368);
      val x4370 = x4369.*(-1028477387);
      val x4371 = x4370.>>>(16);
      val x4372 = x4370.^(x4371);
      x4372
    }
    override def cmp(x4374 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4375 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4376 = x4374._2;
      val x4377 = x4375._2;
      val x4378 = x4376.==(x4377);
      val x4382 = x4378.&&({
        val x4379 = x4374._3;
        val x4380 = x4375._3;
        val x4381 = x4379.==(x4380);
        x4381
      });
      val x4386 = x4382.&&({
        val x4383 = x4374._6;
        val x4384 = x4375._6;
        val x4385 = x4383.==(x4384);
        x4385
      });
      val x4387 = if(x4386) 0 else 1;
      x4387
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3869 : SEntry8_IIIITIIB) = {
      var x3870: Int = -889275714;
      val x3871 = x3869._1;
      val x3872 = x3871.hashCode();
      val x3873 = -862048943.*(x3872);
      val x3874 = x3873.<<(15);
      val x3875 = x3873.>>>(-15);
      val x3876 = x3874.|(x3875);
      val x3877 = x3876.*(461845907);
      val x3878 = x3870;
      val x3879 = x3877.^(x3878);
      val x3880 = x3879.<<(13);
      val x3881 = x3879.>>>(-13);
      val x3882 = x3880.|(x3881);
      val x3883 = x3882.*(5);
      val x3884 = x3883.+(-430675100);
      x3870 = x3884
      val x3886 = x3869._2;
      val x3887 = x3886.hashCode();
      val x3888 = -862048943.*(x3887);
      val x3889 = x3888.<<(15);
      val x3890 = x3888.>>>(-15);
      val x3891 = x3889.|(x3890);
      val x3892 = x3891.*(461845907);
      val x3893 = x3870;
      val x3894 = x3892.^(x3893);
      val x3895 = x3894.<<(13);
      val x3896 = x3894.>>>(-13);
      val x3897 = x3895.|(x3896);
      val x3898 = x3897.*(5);
      val x3899 = x3898.+(-430675100);
      x3870 = x3899
      val x3901 = x3869._3;
      val x3902 = x3901.hashCode();
      val x3903 = -862048943.*(x3902);
      val x3904 = x3903.<<(15);
      val x3905 = x3903.>>>(-15);
      val x3906 = x3904.|(x3905);
      val x3907 = x3906.*(461845907);
      val x3908 = x3870;
      val x3909 = x3907.^(x3908);
      val x3910 = x3909.<<(13);
      val x3911 = x3909.>>>(-13);
      val x3912 = x3910.|(x3911);
      val x3913 = x3912.*(5);
      val x3914 = x3913.+(-430675100);
      x3870 = x3914
      val x3916 = x3870;
      val x3917 = x3916.^(2);
      val x3918 = x3917.>>>(16);
      val x3919 = x3917.^(x3918);
      val x3920 = x3919.*(-2048144789);
      val x3921 = x3920.>>>(13);
      val x3922 = x3920.^(x3921);
      val x3923 = x3922.*(-1028477387);
      val x3924 = x3923.>>>(16);
      val x3925 = x3923.^(x3924);
      x3925
    }
    override def cmp(x3927 : SEntry8_IIIITIIB , x3928 : SEntry8_IIIITIIB) = {
      val x3929 = x3927._1;
      val x3930 = x3928._1;
      val x3931 = x3929.==(x3930);
      val x3935 = x3931.&&({
        val x3932 = x3927._2;
        val x3933 = x3928._2;
        val x3934 = x3932.==(x3933);
        x3934
      });
      val x3939 = x3935.&&({
        val x3936 = x3927._3;
        val x3937 = x3928._3;
        val x3938 = x3936.==(x3937);
        x3938
      });
      val x3940 = if(x3939) 0 else 1;
      x3940
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3515 : SEntry3_III) = {
      var x3516: Int = -889275714;
      val x3517 = x3515._2;
      val x3518 = x3517.hashCode();
      val x3519 = -862048943.*(x3518);
      val x3520 = x3519.<<(15);
      val x3521 = x3519.>>>(-15);
      val x3522 = x3520.|(x3521);
      val x3523 = x3522.*(461845907);
      val x3524 = x3516;
      val x3525 = x3523.^(x3524);
      val x3526 = x3525.<<(13);
      val x3527 = x3525.>>>(-13);
      val x3528 = x3526.|(x3527);
      val x3529 = x3528.*(5);
      val x3530 = x3529.+(-430675100);
      x3516 = x3530
      val x3532 = x3515._3;
      val x3533 = x3532.hashCode();
      val x3534 = -862048943.*(x3533);
      val x3535 = x3534.<<(15);
      val x3536 = x3534.>>>(-15);
      val x3537 = x3535.|(x3536);
      val x3538 = x3537.*(461845907);
      val x3539 = x3516;
      val x3540 = x3538.^(x3539);
      val x3541 = x3540.<<(13);
      val x3542 = x3540.>>>(-13);
      val x3543 = x3541.|(x3542);
      val x3544 = x3543.*(5);
      val x3545 = x3544.+(-430675100);
      x3516 = x3545
      val x3547 = x3516;
      val x3548 = x3547.^(2);
      val x3549 = x3548.>>>(16);
      val x3550 = x3548.^(x3549);
      val x3551 = x3550.*(-2048144789);
      val x3552 = x3551.>>>(13);
      val x3553 = x3551.^(x3552);
      val x3554 = x3553.*(-1028477387);
      val x3555 = x3554.>>>(16);
      val x3556 = x3554.^(x3555);
      x3556
    }
    override def cmp(x3558 : SEntry3_III , x3559 : SEntry3_III) = {
      val x3560 = x3558._1;
      val x3561 = x3559._1;
      val x3562 = x3560.==(x3561);
      val x3563 = x3560.>(x3561);
      val x3564 = if(x3563) 1 else -1;
      val x3565 = if(x3562) 0 else x3564;
      x3565
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3943 : SEntry8_IIIITIIB) = {
      var x3944: Int = -889275714;
      val x3945 = x3943._2;
      val x3946 = x3945.hashCode();
      val x3947 = -862048943.*(x3946);
      val x3948 = x3947.<<(15);
      val x3949 = x3947.>>>(-15);
      val x3950 = x3948.|(x3949);
      val x3951 = x3950.*(461845907);
      val x3952 = x3944;
      val x3953 = x3951.^(x3952);
      val x3954 = x3953.<<(13);
      val x3955 = x3953.>>>(-13);
      val x3956 = x3954.|(x3955);
      val x3957 = x3956.*(5);
      val x3958 = x3957.+(-430675100);
      x3944 = x3958
      val x3960 = x3943._3;
      val x3961 = x3960.hashCode();
      val x3962 = -862048943.*(x3961);
      val x3963 = x3962.<<(15);
      val x3964 = x3962.>>>(-15);
      val x3965 = x3963.|(x3964);
      val x3966 = x3965.*(461845907);
      val x3967 = x3944;
      val x3968 = x3966.^(x3967);
      val x3969 = x3968.<<(13);
      val x3970 = x3968.>>>(-13);
      val x3971 = x3969.|(x3970);
      val x3972 = x3971.*(5);
      val x3973 = x3972.+(-430675100);
      x3944 = x3973
      val x3975 = x3943._4;
      val x3976 = x3975.hashCode();
      val x3977 = -862048943.*(x3976);
      val x3978 = x3977.<<(15);
      val x3979 = x3977.>>>(-15);
      val x3980 = x3978.|(x3979);
      val x3981 = x3980.*(461845907);
      val x3982 = x3944;
      val x3983 = x3981.^(x3982);
      val x3984 = x3983.<<(13);
      val x3985 = x3983.>>>(-13);
      val x3986 = x3984.|(x3985);
      val x3987 = x3986.*(5);
      val x3988 = x3987.+(-430675100);
      x3944 = x3988
      val x3990 = x3944;
      val x3991 = x3990.^(2);
      val x3992 = x3991.>>>(16);
      val x3993 = x3991.^(x3992);
      val x3994 = x3993.*(-2048144789);
      val x3995 = x3994.>>>(13);
      val x3996 = x3994.^(x3995);
      val x3997 = x3996.*(-1028477387);
      val x3998 = x3997.>>>(16);
      val x3999 = x3997.^(x3998);
      x3999
    }
    override def cmp(x4001 : SEntry8_IIIITIIB , x4002 : SEntry8_IIIITIIB) = {
      val x4003 = x4001._1;
      val x4004 = x4002._1;
      val x4005 = x4003.==(x4004);
      val x4006 = x4003.>(x4004);
      val x4007 = if(x4006) 1 else -1;
      val x4008 = if(x4005) 0 else x4007;
      x4008
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3831 : SEntry9_ISSSSSSDD) = {
      var x3832: Int = 0;
      val x3833 = x3831._1;
      val x3834 = x3833.-(1);
      val x3835 = x3832;
      val x3836 = x3835.*(1);
      val x3837 = x3836.+(x3834);
      x3832 = x3837
      val x3839 = x3832;
      x3839
    }
    override def cmp(x3828 : SEntry9_ISSSSSSDD , x3829 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3850 : SEntry5_IISDS) = {
      var x3851: Int = 0;
      val x3852 = x3850._1;
      val x3853 = x3852.-(1);
      val x3854 = x3851;
      val x3855 = x3854.*(100000);
      val x3856 = x3855.+(x3853);
      x3851 = x3856
      val x3858 = x3851;
      x3858
    }
    override def cmp(x3847 : SEntry5_IISDS , x3848 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4095 : SEntry11_IISSSSSSDDI) = {
      var x4096: Int = 0;
      val x4097 = x4095._1;
      val x4098 = x4097.-(1);
      val x4099 = x4096;
      val x4100 = x4099.*(10);
      val x4101 = x4100.+(x4098);
      x4096 = x4101
      val x4103 = x4095._2;
      val x4104 = x4103.-(1);
      val x4105 = x4096;
      val x4106 = x4105.*(1);
      val x4107 = x4106.+(x4104);
      x4096 = x4107
      val x4109 = x4096;
      x4109
    }
    override def cmp(x4092 : SEntry11_IISSSSSSDDI , x4093 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4293 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4294: Int = 0;
      val x4295 = x4293._1;
      val x4296 = x4295.-(1);
      val x4297 = x4294;
      val x4298 = x4297.*(3000);
      val x4299 = x4298.+(x4296);
      x4294 = x4299
      val x4301 = x4293._2;
      val x4302 = x4301.-(1);
      val x4303 = x4294;
      val x4304 = x4303.*(10);
      val x4305 = x4304.+(x4302);
      x4294 = x4305
      val x4307 = x4293._3;
      val x4308 = x4307.-(1);
      val x4309 = x4294;
      val x4310 = x4309.*(1);
      val x4311 = x4310.+(x4308);
      x4294 = x4311
      val x4313 = x4294;
      x4313
    }
    override def cmp(x4290 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4291 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4399 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4400: Int = 0;
      val x4401 = x4399._1;
      val x4402 = x4401.-(1);
      val x4403 = x4400;
      val x4404 = x4403.*(100000);
      val x4405 = x4404.+(x4402);
      x4400 = x4405
      val x4407 = x4399._2;
      val x4408 = x4407.-(1);
      val x4409 = x4400;
      val x4410 = x4409.*(1);
      val x4411 = x4410.+(x4408);
      x4400 = x4411
      val x4413 = x4400;
      x4413
    }
    override def cmp(x4396 : SEntry17_IIISSSSSSSSSSIIIS , x4397 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
  val x7990 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null);
  val x7384 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false);
  val x7511 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7599 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7966 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7778 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7938 = SEntry5_IISDS(-1, -1, null, -1.0, null);
  val x7372 = SEntry3_III(-1, -1, -1);
  val x7524 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null);
  val x7959 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7719 = SEntry11_IISSSSSSDDI(-1, -1, null, null, null, null, null, null, -1.0, -1.0, -1);
  val x7393 = SEntry10_IIIIIITIDS(-1, -1, -1, -1, -1, -1, null, -1, -1.0, null);
  val x7761 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7588 = SEntry8_IIIITIIB(-1, -1, -1, -1, null, -1, -1, false);
  val x7713 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0);
  val x7616 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7397 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, null, -1.0, -1.0, -1.0, -1.0, -1, -1, null);
  val x7963 = SEntry9_ISSSSSSDD(-1, null, null, null, null, null, null, -1.0, -1.0);
  val x7547 = SEntry17_IIISSSSSSSSSSIIIS(-1, -1, -1, null, null, null, null, null, null, null, null, null, null, -1, -1, -1, null);
  class DeliveryTx(x3625: Store[SEntry3_III], x3825: Store[SEntry8_IIIIITDS], x3844: Store[SEntry9_ISSSSSSDD], x3863: Store[SEntry5_IISDS], x4087: Store[SEntry8_IIIITIIB], x4114: Store[SEntry11_IISSSSSSDDI], x4286: Store[SEntry10_IIIIIITIDS], x4392: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4418: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10);
      var x15: Int = 1;
      while({
        val x16 = x15;
        (x16.<=(10))
      })
      {
        val x22 = x15;
        x7372._2_=(x22)
        x7372._3_=(x12)
        val x12287 = x724.get(x7372);
        if((x12287.!=(null))) 
        {
          val x7378 = x12287._1;
          val x29 = x15;
          x14.update((x29.-(1)), x7378)
          x3625.delete(x12287)
          val x33 = x15;
          x7384._1_=(x7378)
          x7384._2_=(x33)
          x7384._3_=(x12)
          val x12300 = x747.get(x7384);
          val x7387 = x12300._4;
          x12300._6_=(x13)
          var x40: Double = 0.0;
          val x41 = x15;
          x7393._1_=(x7378)
          x7393._2_=(x41)
          x7393._3_=(x12)
          x760.slice(x7393, ({ x44: SEntry10_IIIIIITIDS => {
              x44._7_=(x11)
              val x46 = x40;
              val x7442 = x44._9;
              x40 = (x46.+(x7442))
              ()
            }
          }))
          val x53 = x15;
          x7397._1_=(x7387)
          x7397._2_=(x53)
          x7397._3_=(x12)
          val x12321 = x766.get(x7397);
          val x56 = x40;
          x12321._17 +=(x56)
          x12321._20 +=(1)
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
  class StockLevelTx(x3625: Store[SEntry3_III], x3825: Store[SEntry8_IIIIITDS], x3844: Store[SEntry9_ISSSSSSDD], x3863: Store[SEntry5_IISDS], x4087: Store[SEntry8_IIIITIIB], x4114: Store[SEntry11_IISSSSSSDDI], x4286: Store[SEntry10_IIIIIITIDS], x4392: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4418: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x68: Boolean, x69: Date, x70: Int, x71: Int, x72: Int, x73: Int) =     {
      x7511._1_=(x72)
      x7511._2_=(x71)
      val x12390 = x754.get(x7511);
      val x7515 = x12390._11;
      var x79: Int = (x7515.-(20));
      val x80 = Set.apply[Int]();
      while({
        val x81 = x79;
        (x81.<(x7515))
      })
      {
        val x83 = x79;
        x7524._1_=(x83)
        x7524._2_=(x72)
        x7524._3_=(x71)
        x760.slice(x7524, ({ x86: SEntry10_IIIIIITIDS => {
            val x7546 = x86._5;
            x7547._1_=(x7546)
            x7547._2_=(x71)
            val x12408 = x772.get(x7547);
            val x7549 = x12408._3;
            if((x7549.<(x73))) 
            {
              val x92 = x80.+=(x7546);
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
  class OrderStatusTx(x3625: Store[SEntry3_III], x3825: Store[SEntry8_IIIIITDS], x3844: Store[SEntry9_ISSSSSSDD], x3863: Store[SEntry5_IISDS], x4087: Store[SEntry8_IIIITIIB], x4114: Store[SEntry11_IISSSSSSDDI], x4286: Store[SEntry10_IIIIIITIDS], x4392: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4418: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x101: Boolean, x102: Date, x103: Int, x104: Int, x105: Int, x106: Int, x107: Int, x108: String) =     {
      val x7585 = if((x106.>(0))) 
      {
        val x7597 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7599._2_=(x105)
        x7599._3_=(x104)
        x7599._6_=(x108)
        x767.slice(x7599, ({ x113: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7597.append(x113)
            ()
          }
        }))
        val x117 = x7597.size;
        var x119: Int = (x117./(2));
        val x120 = x7597.size;
        if(((x120.%(2)).==(0))) 
        {
          val x123 = x119;
          x119 = (x123.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x134 = x7597.sortWith(({ (x127: SEntry21_IIISSSSSSSSSTSDDDDIIS, x128: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7651 = x127._4;
            val x7652 = x128._4;
            val x131 = x7651.compareToIgnoreCase(x7652)
            (x131.<(0))
          }
        }));
        val x135 = x119;
        val x7615 = x134.apply(x135);
        x7615
      }
      else
      {
        x7616._1_=(x107)
        x7616._2_=(x105)
        x7616._3_=(x104)
        val x12484 = x766.get(x7616);
        x12484
      }
      ;
      val x7586 = x7585._3;
      x7588._2_=(x105)
      x7588._3_=(x104)
      x7588._4_=(x7586)
      val x12492 = x748.get(x7588);
      var x150: Int = 0;
      val x7593 = x12492._1;
      x150 = x7593
      1
    }
  }
  class PaymentTx(x3625: Store[SEntry3_III], x3825: Store[SEntry8_IIIIITDS], x3844: Store[SEntry9_ISSSSSSDD], x3863: Store[SEntry5_IISDS], x4087: Store[SEntry8_IIIITIIB], x4114: Store[SEntry11_IISSSSSSDDI], x4286: Store[SEntry10_IIIIIITIDS], x4392: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4418: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x153: Boolean, x154: Date, x155: Int, x156: Int, x157: Int, x158: Int, x159: Int, x160: Int, x161: Int, x162: String, x163: Double) =     {
      x7713._1_=(x156)
      val x12547 = x735.get(x7713);
      x12547._9 +=(x163)
      x7719._1_=(x157)
      x7719._2_=(x156)
      val x12552 = x754.get(x7719);
      x12552._10 +=(x163)
      val x7725 = if((x158.>(0))) 
      {
        val x7759 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7761._2_=(x160)
        x7761._3_=(x159)
        x7761._6_=(x162)
        x767.slice(x7761, ({ x178: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7759.append(x178)
            ()
          }
        }))
        val x182 = x7759.size;
        var x184: Int = (x182./(2));
        val x185 = x7759.size;
        if(((x185.%(2)).==(0))) 
        {
          val x188 = x184;
          x184 = (x188.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x199 = x7759.sortWith(({ (x192: SEntry21_IIISSSSSSSSSTSDDDDIIS, x193: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7834 = x192._4;
            val x7835 = x193._4;
            val x196 = x7834.compareToIgnoreCase(x7835)
            (x196.<(0))
          }
        }));
        val x200 = x184;
        val x7777 = x199.apply(x200);
        x7777
      }
      else
      {
        x7778._1_=(x161)
        x7778._2_=(x160)
        x7778._3_=(x159)
        val x12589 = x766.get(x7778);
        x12589
      }
      ;
      val x7726 = x7725._21;
      val x7727 = x7725._14;
      val x208 = x7727.contains("BC");
      if(x208) 
      {
        val x7730 = x7725._1;
        var x212 = "%d %d %d %d %d $%f %s | %s".format(x7730,x160,x159,x157,x156,x163,(x154.toString()),x7726)
        if(x212.size > 500) 
          x212 = x212.substring(0, 500)
        x7725._17 +=(x163)
        x7725._21_=(x212)
        ()
      }
      else
      {
        x7725._17 +=(x163)
        ()
      }
      
      val x7738 = x12547._2;
      val x7739 = x12552._3;
      var x221 = "%.10s    %.10s".format(x7738,x7739)
      if(x221.size > 24) 
        x221 = x221.substring(0, 24)
      val x7742 = x7725._1;
      x3825.insert((SEntry8_IIIIITDS(x7742, x160, x159, x157, x156, x154, x163, x221)))
      1
    }
  }
  class NewOrderTx(x3625: Store[SEntry3_III], x3825: Store[SEntry8_IIIIITDS], x3844: Store[SEntry9_ISSSSSSDD], x3863: Store[SEntry5_IISDS], x4087: Store[SEntry8_IIIITIIB], x4114: Store[SEntry11_IISSSSSSDDI], x4286: Store[SEntry10_IIIIIITIDS], x4392: Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], x4418: Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x226: Boolean, x227: Date, x228: Int, x229: Int, x230: Int, x231: Int, x232: Int, x233: Int, x234: Array[Int], x235: Array[Int], x236: Array[Int], x237: Array[Double], x238: Array[String], x239: Array[Int], x240: Array[String], x241: Array[Double]) =     {
      var x242: Int = 0;
      var x243: Boolean = false;
      val x244 = new Array[String](x232);
      var x245: Boolean = true;
      while({
        val x246 = x242;
        ((x246.<(x232)).&&({
          val x248 = x245;
          x248
        }))
      })
      {
        val x250 = x242;
        val x251 = x234.apply(x250);
        x7938._1_=(x251)
        val x12688 = x740.get(x7938);
        if((x12688.==(null))) 
        {
          x245 = false
          ()
        }
        else
        {
          val x257 = x242;
          val x7946 = x12688._3;
          x238.update(x257, x7946)
          val x260 = x242;
          val x7949 = x12688._4;
          x237.update(x260, x7949)
          val x263 = x242;
          val x7952 = x12688._5;
          x244.update(x263, x7952)
          ()
        }
        
        val x267 = x242;
        x242 = (x267.+(1))
        ()
      }
      val x271 = x245;
      if(x271) 
      {
        x7959._1_=(x231)
        x7959._2_=(x230)
        x7959._3_=(x229)
        val x12711 = x766.get(x7959);
        x7963._1_=(x229)
        val x12714 = x735.get(x7963);
        x7966._1_=(x230)
        x7966._2_=(x229)
        val x12718 = x754.get(x7966);
        val x7969 = x12718._11;
        x12718._11 +=(1)
        x4087.insert((SEntry8_IIIITIIB(x7969, x230, x229, x231, x227, -1, x232, (x233.>(0)))))
        x3625.insert((SEntry3_III(x7969, x230, x229)))
        var x291: Double = 0.0;
        x242 = 0
        while({
          val x293 = x242;
          (x293.<(x232))
        })
        {
          val x295 = x242;
          val x296 = x235.apply(x295);
          val x297 = x242;
          val x298 = x234.apply(x297);
          val x299 = x242;
          val x300 = x236.apply(x299);
          x7990._1_=(x298)
          x7990._2_=(x296)
          val x12741 = x772.get(x7990);
          val x330 = if((x230.==(1))) 
          {
            val x7994 = x12741._4;
            x7994
          }
          else
          {
            val x329 = if((x230.==(2))) 
            {
              val x7997 = x12741._5;
              x7997
            }
            else
            {
              val x328 = if((x230.==(3))) 
              {
                val x8000 = x12741._6;
                x8000
              }
              else
              {
                val x327 = if((x230.==(4))) 
                {
                  val x8003 = x12741._7;
                  x8003
                }
                else
                {
                  val x326 = if((x230.==(5))) 
                  {
                    val x8006 = x12741._8;
                    x8006
                  }
                  else
                  {
                    val x325 = if((x230.==(6))) 
                    {
                      val x8009 = x12741._9;
                      x8009
                    }
                    else
                    {
                      val x324 = if((x230.==(7))) 
                      {
                        val x8012 = x12741._10;
                        x8012
                      }
                      else
                      {
                        val x323 = if((x230.==(8))) 
                        {
                          val x8015 = x12741._11;
                          x8015
                        }
                        else
                        {
                          val x322 = if((x230.==(9))) 
                          {
                            val x8018 = x12741._12;
                            x8018
                          }
                          else
                          {
                            val x8019 = x12741._13;
                            x8019
                          }
                          ;
                          x322
                        }
                        ;
                        x323
                      }
                      ;
                      x324
                    }
                    ;
                    x325
                  }
                  ;
                  x326
                }
                ;
                x327
              }
              ;
              x328
            }
            ;
            x329
          }
          ;
          val x8020 = x12741._3;
          val x332 = x242;
          x239.update(x332, x8020)
          val x8023 = x12711._14;
          val x335 = x8023.contains("original");
          if((x335.&&({
            val x8026 = x12741._17;
            val x337 = x8026.contains("original");
            x337
          }))) 
          {
            val x339 = x242;
            x240.update(x339, "B")
            ()
          }
          else
          {
            val x341 = x242;
            x240.update(x341, "G")
            ()
          }
          
          x12741._3_=((x8020.-(x300)))
          if((x8020.<=(x300))) 
          {
            x12741._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x349: Int = 0;
          if((x296.!=(x229))) 
          {
            x349 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8043 = x12711._16;
          val x8044 = x12714._8;
          val x8045 = x12718._9;
          val x357 = x242;
          val x358 = x237.apply(x357);
          val x365 = (((x300.toDouble).*(x358)).*(((1.0.+(x8044)).+(x8045)))).*((1.0.-(x8043)));
          val x366 = x242;
          x241.update(x366, x365)
          val x368 = x291;
          x291 = (x368.+(x365))
          val x371 = x242;
          x4286.insert((SEntry10_IIIIIITIDS(x7969, x230, x229, (x371.+(1)), x298, x296, null, x300, x365, x330)))
          val x376 = x242;
          x242 = (x376.+(1))
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
