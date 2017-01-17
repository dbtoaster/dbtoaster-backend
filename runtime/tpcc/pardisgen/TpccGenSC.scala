
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
  val x3763 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val newOrderTbl = new Store[SEntry3_III](3, x3763);
  val x3765 = newOrderTbl.index(0, IHash, true, -1)
  val x3766 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val x3767 = newOrderTbl.index(2, INone, false, -1)
  val x3963 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx)
  val historyTbl = new Store[SEntry8_IIIIITDS](1, x3963);
  val x3965 = historyTbl.index(0, IList, false, -1)
  val x3982 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val warehouseTbl = new Store[SEntry9_ISSSSSSDD](1, x3982);
  val x3984 = warehouseTbl.index(0, IDirect, true, 1)
  val x4001 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val itemTbl = new Store[SEntry5_IISDS](1, x4001);
  val x4003 = itemTbl.index(0, IDirect, true, 100000)
  val x4225 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val orderTbl = new Store[SEntry8_IIIITIIB](3, x4225);
  val x4227 = orderTbl.index(0, IHash, true, -1)
  val x4228 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val x4229 = orderTbl.index(2, INone, false, -1)
  val x4252 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val districtTbl = new Store[SEntry11_IISSSSSSDDI](1, x4252);
  val x4254 = districtTbl.index(0, IDirect, true, 10)
  val x4424 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val orderLineTbl = new Store[SEntry10_IIIIIITIDS](2, x4424);
  val x4426 = orderLineTbl.index(0, IHash, true, -1)
  val x4427 = orderLineTbl.index(1, IHash, false, -1)
  val x4530 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val customerTbl = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4530);
  val x4532 = customerTbl.index(0, IDirect, true, 30000)
  val x4533 = customerTbl.index(1, IHash, false, -1)
  val x4556 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val stockTbl = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4556);
  val x4558 = stockTbl.index(0, IDirect, true, 100000)
  

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4256 : SEntry10_IIIIIITIDS) = {
      var x4257: Int = -889275714;
      val x4258 = x4256._1;
      val x4259 = x4258.hashCode();
      val x4260 = -862048943.*(x4259);
      val x4261 = x4260.<<(15);
      val x4262 = x4260.>>>(-15);
      val x4263 = x4261.|(x4262);
      val x4264 = x4263.*(461845907);
      val x4265 = x4257;
      val x4266 = x4264.^(x4265);
      val x4267 = x4266.<<(13);
      val x4268 = x4266.>>>(-13);
      val x4269 = x4267.|(x4268);
      val x4270 = x4269.*(5);
      val x4271 = x4270.+(-430675100);
      x4257 = x4271
      val x4273 = x4256._2;
      val x4274 = x4273.hashCode();
      val x4275 = -862048943.*(x4274);
      val x4276 = x4275.<<(15);
      val x4277 = x4275.>>>(-15);
      val x4278 = x4276.|(x4277);
      val x4279 = x4278.*(461845907);
      val x4280 = x4257;
      val x4281 = x4279.^(x4280);
      val x4282 = x4281.<<(13);
      val x4283 = x4281.>>>(-13);
      val x4284 = x4282.|(x4283);
      val x4285 = x4284.*(5);
      val x4286 = x4285.+(-430675100);
      x4257 = x4286
      val x4288 = x4256._3;
      val x4289 = x4288.hashCode();
      val x4290 = -862048943.*(x4289);
      val x4291 = x4290.<<(15);
      val x4292 = x4290.>>>(-15);
      val x4293 = x4291.|(x4292);
      val x4294 = x4293.*(461845907);
      val x4295 = x4257;
      val x4296 = x4294.^(x4295);
      val x4297 = x4296.<<(13);
      val x4298 = x4296.>>>(-13);
      val x4299 = x4297.|(x4298);
      val x4300 = x4299.*(5);
      val x4301 = x4300.+(-430675100);
      x4257 = x4301
      val x4303 = x4256._4;
      val x4304 = x4303.hashCode();
      val x4305 = -862048943.*(x4304);
      val x4306 = x4305.<<(15);
      val x4307 = x4305.>>>(-15);
      val x4308 = x4306.|(x4307);
      val x4309 = x4308.*(461845907);
      val x4310 = x4257;
      val x4311 = x4309.^(x4310);
      val x4312 = x4311.<<(13);
      val x4313 = x4311.>>>(-13);
      val x4314 = x4312.|(x4313);
      val x4315 = x4314.*(5);
      val x4316 = x4315.+(-430675100);
      x4257 = x4316
      val x4318 = x4257;
      val x4319 = x4318.^(2);
      val x4320 = x4319.>>>(16);
      val x4321 = x4319.^(x4320);
      val x4322 = x4321.*(-2048144789);
      val x4323 = x4322.>>>(13);
      val x4324 = x4322.^(x4323);
      val x4325 = x4324.*(-1028477387);
      val x4326 = x4325.>>>(16);
      val x4327 = x4325.^(x4326);
      x4327
    }
    override def cmp(x4329 : SEntry10_IIIIIITIDS , x4330 : SEntry10_IIIIIITIDS) = {
      val x4331 = x4329._1;
      val x4332 = x4330._1;
      val x4333 = x4331.==(x4332);
      val x4337 = x4333.&&({
        val x4334 = x4329._2;
        val x4335 = x4330._2;
        val x4336 = x4334.==(x4335);
        x4336
      });
      val x4341 = x4337.&&({
        val x4338 = x4329._3;
        val x4339 = x4330._3;
        val x4340 = x4338.==(x4339);
        x4340
      });
      val x4345 = x4341.&&({
        val x4342 = x4329._4;
        val x4343 = x4330._4;
        val x4344 = x4342.==(x4343);
        x4344
      });
      val x4346 = if(x4345) 0 else 1;
      x4346
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4150 : SEntry8_IIIITIIB) = {
      var x4151: Int = -889275714;
      val x4152 = x4150._2;
      val x4153 = x4152.hashCode();
      val x4154 = -862048943.*(x4153);
      val x4155 = x4154.<<(15);
      val x4156 = x4154.>>>(-15);
      val x4157 = x4155.|(x4156);
      val x4158 = x4157.*(461845907);
      val x4159 = x4151;
      val x4160 = x4158.^(x4159);
      val x4161 = x4160.<<(13);
      val x4162 = x4160.>>>(-13);
      val x4163 = x4161.|(x4162);
      val x4164 = x4163.*(5);
      val x4165 = x4164.+(-430675100);
      x4151 = x4165
      val x4167 = x4150._3;
      val x4168 = x4167.hashCode();
      val x4169 = -862048943.*(x4168);
      val x4170 = x4169.<<(15);
      val x4171 = x4169.>>>(-15);
      val x4172 = x4170.|(x4171);
      val x4173 = x4172.*(461845907);
      val x4174 = x4151;
      val x4175 = x4173.^(x4174);
      val x4176 = x4175.<<(13);
      val x4177 = x4175.>>>(-13);
      val x4178 = x4176.|(x4177);
      val x4179 = x4178.*(5);
      val x4180 = x4179.+(-430675100);
      x4151 = x4180
      val x4182 = x4150._4;
      val x4183 = x4182.hashCode();
      val x4184 = -862048943.*(x4183);
      val x4185 = x4184.<<(15);
      val x4186 = x4184.>>>(-15);
      val x4187 = x4185.|(x4186);
      val x4188 = x4187.*(461845907);
      val x4189 = x4151;
      val x4190 = x4188.^(x4189);
      val x4191 = x4190.<<(13);
      val x4192 = x4190.>>>(-13);
      val x4193 = x4191.|(x4192);
      val x4194 = x4193.*(5);
      val x4195 = x4194.+(-430675100);
      x4151 = x4195
      val x4197 = x4151;
      val x4198 = x4197.^(2);
      val x4199 = x4198.>>>(16);
      val x4200 = x4198.^(x4199);
      val x4201 = x4200.*(-2048144789);
      val x4202 = x4201.>>>(13);
      val x4203 = x4201.^(x4202);
      val x4204 = x4203.*(-1028477387);
      val x4205 = x4204.>>>(16);
      val x4206 = x4204.^(x4205);
      x4206
    }
    override def cmp(x4208 : SEntry8_IIIITIIB , x4209 : SEntry8_IIIITIIB) = {
      val x4210 = x4208._2;
      val x4211 = x4209._2;
      val x4212 = x4210.==(x4211);
      val x4216 = x4212.&&({
        val x4213 = x4208._3;
        val x4214 = x4209._3;
        val x4215 = x4213.==(x4214);
        x4215
      });
      val x4220 = x4216.&&({
        val x4217 = x4208._4;
        val x4218 = x4209._4;
        val x4219 = x4217.==(x4218);
        x4219
      });
      val x4221 = if(x4220) 0 else 1;
      x4221
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3580 : SEntry3_III) = {
      var x3581: Int = -889275714;
      val x3582 = x3580._1;
      val x3583 = x3582.hashCode();
      val x3584 = -862048943.*(x3583);
      val x3585 = x3584.<<(15);
      val x3586 = x3584.>>>(-15);
      val x3587 = x3585.|(x3586);
      val x3588 = x3587.*(461845907);
      val x3589 = x3581;
      val x3590 = x3588.^(x3589);
      val x3591 = x3590.<<(13);
      val x3592 = x3590.>>>(-13);
      val x3593 = x3591.|(x3592);
      val x3594 = x3593.*(5);
      val x3595 = x3594.+(-430675100);
      x3581 = x3595
      val x3597 = x3580._2;
      val x3598 = x3597.hashCode();
      val x3599 = -862048943.*(x3598);
      val x3600 = x3599.<<(15);
      val x3601 = x3599.>>>(-15);
      val x3602 = x3600.|(x3601);
      val x3603 = x3602.*(461845907);
      val x3604 = x3581;
      val x3605 = x3603.^(x3604);
      val x3606 = x3605.<<(13);
      val x3607 = x3605.>>>(-13);
      val x3608 = x3606.|(x3607);
      val x3609 = x3608.*(5);
      val x3610 = x3609.+(-430675100);
      x3581 = x3610
      val x3612 = x3580._3;
      val x3613 = x3612.hashCode();
      val x3614 = -862048943.*(x3613);
      val x3615 = x3614.<<(15);
      val x3616 = x3614.>>>(-15);
      val x3617 = x3615.|(x3616);
      val x3618 = x3617.*(461845907);
      val x3619 = x3581;
      val x3620 = x3618.^(x3619);
      val x3621 = x3620.<<(13);
      val x3622 = x3620.>>>(-13);
      val x3623 = x3621.|(x3622);
      val x3624 = x3623.*(5);
      val x3625 = x3624.+(-430675100);
      x3581 = x3625
      val x3627 = x3581;
      val x3628 = x3627.^(2);
      val x3629 = x3628.>>>(16);
      val x3630 = x3628.^(x3629);
      val x3631 = x3630.*(-2048144789);
      val x3632 = x3631.>>>(13);
      val x3633 = x3631.^(x3632);
      val x3634 = x3633.*(-1028477387);
      val x3635 = x3634.>>>(16);
      val x3636 = x3634.^(x3635);
      x3636
    }
    override def cmp(x3638 : SEntry3_III , x3639 : SEntry3_III) = {
      val x3640 = x3638._1;
      val x3641 = x3639._1;
      val x3642 = x3640.==(x3641);
      val x3646 = x3642.&&({
        val x3643 = x3638._2;
        val x3644 = x3639._2;
        val x3645 = x3643.==(x3644);
        x3645
      });
      val x3650 = x3646.&&({
        val x3647 = x3638._3;
        val x3648 = x3639._3;
        val x3649 = x3647.==(x3648);
        x3649
      });
      val x3651 = if(x3650) 0 else 1;
      x3651
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4349 : SEntry10_IIIIIITIDS) = {
      var x4350: Int = -889275714;
      val x4351 = x4349._1;
      val x4352 = x4351.hashCode();
      val x4353 = -862048943.*(x4352);
      val x4354 = x4353.<<(15);
      val x4355 = x4353.>>>(-15);
      val x4356 = x4354.|(x4355);
      val x4357 = x4356.*(461845907);
      val x4358 = x4350;
      val x4359 = x4357.^(x4358);
      val x4360 = x4359.<<(13);
      val x4361 = x4359.>>>(-13);
      val x4362 = x4360.|(x4361);
      val x4363 = x4362.*(5);
      val x4364 = x4363.+(-430675100);
      x4350 = x4364
      val x4366 = x4349._2;
      val x4367 = x4366.hashCode();
      val x4368 = -862048943.*(x4367);
      val x4369 = x4368.<<(15);
      val x4370 = x4368.>>>(-15);
      val x4371 = x4369.|(x4370);
      val x4372 = x4371.*(461845907);
      val x4373 = x4350;
      val x4374 = x4372.^(x4373);
      val x4375 = x4374.<<(13);
      val x4376 = x4374.>>>(-13);
      val x4377 = x4375.|(x4376);
      val x4378 = x4377.*(5);
      val x4379 = x4378.+(-430675100);
      x4350 = x4379
      val x4381 = x4349._3;
      val x4382 = x4381.hashCode();
      val x4383 = -862048943.*(x4382);
      val x4384 = x4383.<<(15);
      val x4385 = x4383.>>>(-15);
      val x4386 = x4384.|(x4385);
      val x4387 = x4386.*(461845907);
      val x4388 = x4350;
      val x4389 = x4387.^(x4388);
      val x4390 = x4389.<<(13);
      val x4391 = x4389.>>>(-13);
      val x4392 = x4390.|(x4391);
      val x4393 = x4392.*(5);
      val x4394 = x4393.+(-430675100);
      x4350 = x4394
      val x4396 = x4350;
      val x4397 = x4396.^(2);
      val x4398 = x4397.>>>(16);
      val x4399 = x4397.^(x4398);
      val x4400 = x4399.*(-2048144789);
      val x4401 = x4400.>>>(13);
      val x4402 = x4400.^(x4401);
      val x4403 = x4402.*(-1028477387);
      val x4404 = x4403.>>>(16);
      val x4405 = x4403.^(x4404);
      x4405
    }
    override def cmp(x4407 : SEntry10_IIIIIITIDS , x4408 : SEntry10_IIIIIITIDS) = {
      val x4409 = x4407._1;
      val x4410 = x4408._1;
      val x4411 = x4409.==(x4410);
      val x4415 = x4411.&&({
        val x4412 = x4407._2;
        val x4413 = x4408._2;
        val x4414 = x4412.==(x4413);
        x4414
      });
      val x4419 = x4415.&&({
        val x4416 = x4407._3;
        val x4417 = x4408._3;
        val x4418 = x4416.==(x4417);
        x4418
      });
      val x4420 = if(x4419) 0 else 1;
      x4420
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3707 : SEntry3_III) = {
      var x3708: Int = -889275714;
      val x3709 = x3707._2;
      val x3710 = x3709.hashCode();
      val x3711 = -862048943.*(x3710);
      val x3712 = x3711.<<(15);
      val x3713 = x3711.>>>(-15);
      val x3714 = x3712.|(x3713);
      val x3715 = x3714.*(461845907);
      val x3716 = x3708;
      val x3717 = x3715.^(x3716);
      val x3718 = x3717.<<(13);
      val x3719 = x3717.>>>(-13);
      val x3720 = x3718.|(x3719);
      val x3721 = x3720.*(5);
      val x3722 = x3721.+(-430675100);
      x3708 = x3722
      val x3724 = x3707._3;
      val x3725 = x3724.hashCode();
      val x3726 = -862048943.*(x3725);
      val x3727 = x3726.<<(15);
      val x3728 = x3726.>>>(-15);
      val x3729 = x3727.|(x3728);
      val x3730 = x3729.*(461845907);
      val x3731 = x3708;
      val x3732 = x3730.^(x3731);
      val x3733 = x3732.<<(13);
      val x3734 = x3732.>>>(-13);
      val x3735 = x3733.|(x3734);
      val x3736 = x3735.*(5);
      val x3737 = x3736.+(-430675100);
      x3708 = x3737
      val x3739 = x3708;
      val x3740 = x3739.^(2);
      val x3741 = x3740.>>>(16);
      val x3742 = x3740.^(x3741);
      val x3743 = x3742.*(-2048144789);
      val x3744 = x3743.>>>(13);
      val x3745 = x3743.^(x3744);
      val x3746 = x3745.*(-1028477387);
      val x3747 = x3746.>>>(16);
      val x3748 = x3746.^(x3747);
      x3748
    }
    override def cmp(x3750 : SEntry3_III , x3751 : SEntry3_III) = {
      val x3752 = x3750._2;
      val x3753 = x3751._2;
      val x3754 = x3752.==(x3753);
      val x3758 = x3754.&&({
        val x3755 = x3750._3;
        val x3756 = x3751._3;
        val x3757 = x3755.==(x3756);
        x3757
      });
      val x3759 = if(x3758) 0 else 1;
      x3759
    }
  }
   object SEntry8_IIIIITDS_Idx extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3769 : SEntry8_IIIIITDS) = {
      var x3770: Int = -889275714;
      val x3771 = x3769._1;
      val x3772 = x3771.hashCode();
      val x3773 = -862048943.*(x3772);
      val x3774 = x3773.<<(15);
      val x3775 = x3773.>>>(-15);
      val x3776 = x3774.|(x3775);
      val x3777 = x3776.*(461845907);
      val x3778 = x3770;
      val x3779 = x3777.^(x3778);
      val x3780 = x3779.<<(13);
      val x3781 = x3779.>>>(-13);
      val x3782 = x3780.|(x3781);
      val x3783 = x3782.*(5);
      val x3784 = x3783.+(-430675100);
      x3770 = x3784
      val x3786 = x3769._2;
      val x3787 = x3786.hashCode();
      val x3788 = -862048943.*(x3787);
      val x3789 = x3788.<<(15);
      val x3790 = x3788.>>>(-15);
      val x3791 = x3789.|(x3790);
      val x3792 = x3791.*(461845907);
      val x3793 = x3770;
      val x3794 = x3792.^(x3793);
      val x3795 = x3794.<<(13);
      val x3796 = x3794.>>>(-13);
      val x3797 = x3795.|(x3796);
      val x3798 = x3797.*(5);
      val x3799 = x3798.+(-430675100);
      x3770 = x3799
      val x3801 = x3769._3;
      val x3802 = x3801.hashCode();
      val x3803 = -862048943.*(x3802);
      val x3804 = x3803.<<(15);
      val x3805 = x3803.>>>(-15);
      val x3806 = x3804.|(x3805);
      val x3807 = x3806.*(461845907);
      val x3808 = x3770;
      val x3809 = x3807.^(x3808);
      val x3810 = x3809.<<(13);
      val x3811 = x3809.>>>(-13);
      val x3812 = x3810.|(x3811);
      val x3813 = x3812.*(5);
      val x3814 = x3813.+(-430675100);
      x3770 = x3814
      val x3816 = x3769._4;
      val x3817 = x3816.hashCode();
      val x3818 = -862048943.*(x3817);
      val x3819 = x3818.<<(15);
      val x3820 = x3818.>>>(-15);
      val x3821 = x3819.|(x3820);
      val x3822 = x3821.*(461845907);
      val x3823 = x3770;
      val x3824 = x3822.^(x3823);
      val x3825 = x3824.<<(13);
      val x3826 = x3824.>>>(-13);
      val x3827 = x3825.|(x3826);
      val x3828 = x3827.*(5);
      val x3829 = x3828.+(-430675100);
      x3770 = x3829
      val x3831 = x3769._5;
      val x3832 = x3831.hashCode();
      val x3833 = -862048943.*(x3832);
      val x3834 = x3833.<<(15);
      val x3835 = x3833.>>>(-15);
      val x3836 = x3834.|(x3835);
      val x3837 = x3836.*(461845907);
      val x3838 = x3770;
      val x3839 = x3837.^(x3838);
      val x3840 = x3839.<<(13);
      val x3841 = x3839.>>>(-13);
      val x3842 = x3840.|(x3841);
      val x3843 = x3842.*(5);
      val x3844 = x3843.+(-430675100);
      x3770 = x3844
      val x3846 = x3769._6;
      val x3847 = x3846.hashCode();
      val x3848 = -862048943.*(x3847);
      val x3849 = x3848.<<(15);
      val x3850 = x3848.>>>(-15);
      val x3851 = x3849.|(x3850);
      val x3852 = x3851.*(461845907);
      val x3853 = x3770;
      val x3854 = x3852.^(x3853);
      val x3855 = x3854.<<(13);
      val x3856 = x3854.>>>(-13);
      val x3857 = x3855.|(x3856);
      val x3858 = x3857.*(5);
      val x3859 = x3858.+(-430675100);
      x3770 = x3859
      val x3861 = x3769._7;
      val x3862 = x3861.hashCode();
      val x3863 = -862048943.*(x3862);
      val x3864 = x3863.<<(15);
      val x3865 = x3863.>>>(-15);
      val x3866 = x3864.|(x3865);
      val x3867 = x3866.*(461845907);
      val x3868 = x3770;
      val x3869 = x3867.^(x3868);
      val x3870 = x3869.<<(13);
      val x3871 = x3869.>>>(-13);
      val x3872 = x3870.|(x3871);
      val x3873 = x3872.*(5);
      val x3874 = x3873.+(-430675100);
      x3770 = x3874
      val x3876 = x3769._8;
      val x3877 = x3876.hashCode();
      val x3878 = -862048943.*(x3877);
      val x3879 = x3878.<<(15);
      val x3880 = x3878.>>>(-15);
      val x3881 = x3879.|(x3880);
      val x3882 = x3881.*(461845907);
      val x3883 = x3770;
      val x3884 = x3882.^(x3883);
      val x3885 = x3884.<<(13);
      val x3886 = x3884.>>>(-13);
      val x3887 = x3885.|(x3886);
      val x3888 = x3887.*(5);
      val x3889 = x3888.+(-430675100);
      x3770 = x3889
      val x3891 = x3770;
      val x3892 = x3891.^(2);
      val x3893 = x3892.>>>(16);
      val x3894 = x3892.^(x3893);
      val x3895 = x3894.*(-2048144789);
      val x3896 = x3895.>>>(13);
      val x3897 = x3895.^(x3896);
      val x3898 = x3897.*(-1028477387);
      val x3899 = x3898.>>>(16);
      val x3900 = x3898.^(x3899);
      x3900
    }
    override def cmp(x3902 : SEntry8_IIIIITDS , x3903 : SEntry8_IIIIITDS) = {
      val x3904 = x3902._1;
      val x3905 = x3903._1;
      val x3906 = x3904.==(-2147483648);
      val x3908 = x3906.||({
        val x3907 = x3905.==(-2147483648);
        x3907
      });
      val x3910 = x3908.||({
        val x3909 = x3904.==(x3905);
        x3909
      });
      val x3918 = x3910.&&({
        val x3911 = x3902._2;
        val x3912 = x3903._2;
        val x3913 = x3911.==(-2147483648);
        val x3915 = x3913.||({
          val x3914 = x3912.==(-2147483648);
          x3914
        });
        val x3917 = x3915.||({
          val x3916 = x3911.==(x3912);
          x3916
        });
        x3917
      });
      val x3926 = x3918.&&({
        val x3919 = x3902._3;
        val x3920 = x3903._3;
        val x3921 = x3919.==(-2147483648);
        val x3923 = x3921.||({
          val x3922 = x3920.==(-2147483648);
          x3922
        });
        val x3925 = x3923.||({
          val x3924 = x3919.==(x3920);
          x3924
        });
        x3925
      });
      val x3934 = x3926.&&({
        val x3927 = x3902._4;
        val x3928 = x3903._4;
        val x3929 = x3927.==(-2147483648);
        val x3931 = x3929.||({
          val x3930 = x3928.==(-2147483648);
          x3930
        });
        val x3933 = x3931.||({
          val x3932 = x3927.==(x3928);
          x3932
        });
        x3933
      });
      val x3942 = x3934.&&({
        val x3935 = x3902._5;
        val x3936 = x3903._5;
        val x3937 = x3935.==(-2147483648);
        val x3939 = x3937.||({
          val x3938 = x3936.==(-2147483648);
          x3938
        });
        val x3941 = x3939.||({
          val x3940 = x3935.==(x3936);
          x3940
        });
        x3941
      });
      val x3950 = x3942.&&({
        val x3943 = x3902._6;
        val x3944 = x3903._6;
        val x3945 = x3943.==(null);
        val x3947 = x3945.||({
          val x3946 = x3944.==(null);
          x3946
        });
        val x3949 = x3947.||({
          val x3948 = x3943.==(x3944);
          x3948
        });
        x3949
      });
      val x3958 = x3950.&&({
        val x3951 = x3902._7;
        val x3952 = x3903._7;
        val x3953 = x3951.==(-1.7976931348623157E308);
        val x3955 = x3953.||({
          val x3954 = x3952.==(-1.7976931348623157E308);
          x3954
        });
        val x3957 = x3955.||({
          val x3956 = x3951.==(x3952);
          x3956
        });
        x3957
      });
      val x3959 = if(x3958) 0 else 1;
      x3959
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4455 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4456: Int = -889275714;
      val x4457 = x4455._2;
      val x4458 = x4457.hashCode();
      val x4459 = -862048943.*(x4458);
      val x4460 = x4459.<<(15);
      val x4461 = x4459.>>>(-15);
      val x4462 = x4460.|(x4461);
      val x4463 = x4462.*(461845907);
      val x4464 = x4456;
      val x4465 = x4463.^(x4464);
      val x4466 = x4465.<<(13);
      val x4467 = x4465.>>>(-13);
      val x4468 = x4466.|(x4467);
      val x4469 = x4468.*(5);
      val x4470 = x4469.+(-430675100);
      x4456 = x4470
      val x4472 = x4455._3;
      val x4473 = x4472.hashCode();
      val x4474 = -862048943.*(x4473);
      val x4475 = x4474.<<(15);
      val x4476 = x4474.>>>(-15);
      val x4477 = x4475.|(x4476);
      val x4478 = x4477.*(461845907);
      val x4479 = x4456;
      val x4480 = x4478.^(x4479);
      val x4481 = x4480.<<(13);
      val x4482 = x4480.>>>(-13);
      val x4483 = x4481.|(x4482);
      val x4484 = x4483.*(5);
      val x4485 = x4484.+(-430675100);
      x4456 = x4485
      val x4487 = x4455._6;
      val x4488 = x4487.hashCode();
      val x4489 = -862048943.*(x4488);
      val x4490 = x4489.<<(15);
      val x4491 = x4489.>>>(-15);
      val x4492 = x4490.|(x4491);
      val x4493 = x4492.*(461845907);
      val x4494 = x4456;
      val x4495 = x4493.^(x4494);
      val x4496 = x4495.<<(13);
      val x4497 = x4495.>>>(-13);
      val x4498 = x4496.|(x4497);
      val x4499 = x4498.*(5);
      val x4500 = x4499.+(-430675100);
      x4456 = x4500
      val x4502 = x4456;
      val x4503 = x4502.^(2);
      val x4504 = x4503.>>>(16);
      val x4505 = x4503.^(x4504);
      val x4506 = x4505.*(-2048144789);
      val x4507 = x4506.>>>(13);
      val x4508 = x4506.^(x4507);
      val x4509 = x4508.*(-1028477387);
      val x4510 = x4509.>>>(16);
      val x4511 = x4509.^(x4510);
      x4511
    }
    override def cmp(x4513 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4514 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      val x4515 = x4513._2;
      val x4516 = x4514._2;
      val x4517 = x4515.==(x4516);
      val x4521 = x4517.&&({
        val x4518 = x4513._3;
        val x4519 = x4514._3;
        val x4520 = x4518.==(x4519);
        x4520
      });
      val x4525 = x4521.&&({
        val x4522 = x4513._6;
        val x4523 = x4514._6;
        val x4524 = x4522.==(x4523);
        x4524
      });
      val x4526 = if(x4525) 0 else 1;
      x4526
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4008 : SEntry8_IIIITIIB) = {
      var x4009: Int = -889275714;
      val x4010 = x4008._1;
      val x4011 = x4010.hashCode();
      val x4012 = -862048943.*(x4011);
      val x4013 = x4012.<<(15);
      val x4014 = x4012.>>>(-15);
      val x4015 = x4013.|(x4014);
      val x4016 = x4015.*(461845907);
      val x4017 = x4009;
      val x4018 = x4016.^(x4017);
      val x4019 = x4018.<<(13);
      val x4020 = x4018.>>>(-13);
      val x4021 = x4019.|(x4020);
      val x4022 = x4021.*(5);
      val x4023 = x4022.+(-430675100);
      x4009 = x4023
      val x4025 = x4008._2;
      val x4026 = x4025.hashCode();
      val x4027 = -862048943.*(x4026);
      val x4028 = x4027.<<(15);
      val x4029 = x4027.>>>(-15);
      val x4030 = x4028.|(x4029);
      val x4031 = x4030.*(461845907);
      val x4032 = x4009;
      val x4033 = x4031.^(x4032);
      val x4034 = x4033.<<(13);
      val x4035 = x4033.>>>(-13);
      val x4036 = x4034.|(x4035);
      val x4037 = x4036.*(5);
      val x4038 = x4037.+(-430675100);
      x4009 = x4038
      val x4040 = x4008._3;
      val x4041 = x4040.hashCode();
      val x4042 = -862048943.*(x4041);
      val x4043 = x4042.<<(15);
      val x4044 = x4042.>>>(-15);
      val x4045 = x4043.|(x4044);
      val x4046 = x4045.*(461845907);
      val x4047 = x4009;
      val x4048 = x4046.^(x4047);
      val x4049 = x4048.<<(13);
      val x4050 = x4048.>>>(-13);
      val x4051 = x4049.|(x4050);
      val x4052 = x4051.*(5);
      val x4053 = x4052.+(-430675100);
      x4009 = x4053
      val x4055 = x4009;
      val x4056 = x4055.^(2);
      val x4057 = x4056.>>>(16);
      val x4058 = x4056.^(x4057);
      val x4059 = x4058.*(-2048144789);
      val x4060 = x4059.>>>(13);
      val x4061 = x4059.^(x4060);
      val x4062 = x4061.*(-1028477387);
      val x4063 = x4062.>>>(16);
      val x4064 = x4062.^(x4063);
      x4064
    }
    override def cmp(x4066 : SEntry8_IIIITIIB , x4067 : SEntry8_IIIITIIB) = {
      val x4068 = x4066._1;
      val x4069 = x4067._1;
      val x4070 = x4068.==(x4069);
      val x4074 = x4070.&&({
        val x4071 = x4066._2;
        val x4072 = x4067._2;
        val x4073 = x4071.==(x4072);
        x4073
      });
      val x4078 = x4074.&&({
        val x4075 = x4066._3;
        val x4076 = x4067._3;
        val x4077 = x4075.==(x4076);
        x4077
      });
      val x4079 = if(x4078) 0 else 1;
      x4079
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3654 : SEntry3_III) = {
      var x3655: Int = -889275714;
      val x3656 = x3654._2;
      val x3657 = x3656.hashCode();
      val x3658 = -862048943.*(x3657);
      val x3659 = x3658.<<(15);
      val x3660 = x3658.>>>(-15);
      val x3661 = x3659.|(x3660);
      val x3662 = x3661.*(461845907);
      val x3663 = x3655;
      val x3664 = x3662.^(x3663);
      val x3665 = x3664.<<(13);
      val x3666 = x3664.>>>(-13);
      val x3667 = x3665.|(x3666);
      val x3668 = x3667.*(5);
      val x3669 = x3668.+(-430675100);
      x3655 = x3669
      val x3671 = x3654._3;
      val x3672 = x3671.hashCode();
      val x3673 = -862048943.*(x3672);
      val x3674 = x3673.<<(15);
      val x3675 = x3673.>>>(-15);
      val x3676 = x3674.|(x3675);
      val x3677 = x3676.*(461845907);
      val x3678 = x3655;
      val x3679 = x3677.^(x3678);
      val x3680 = x3679.<<(13);
      val x3681 = x3679.>>>(-13);
      val x3682 = x3680.|(x3681);
      val x3683 = x3682.*(5);
      val x3684 = x3683.+(-430675100);
      x3655 = x3684
      val x3686 = x3655;
      val x3687 = x3686.^(2);
      val x3688 = x3687.>>>(16);
      val x3689 = x3687.^(x3688);
      val x3690 = x3689.*(-2048144789);
      val x3691 = x3690.>>>(13);
      val x3692 = x3690.^(x3691);
      val x3693 = x3692.*(-1028477387);
      val x3694 = x3693.>>>(16);
      val x3695 = x3693.^(x3694);
      x3695
    }
    override def cmp(x3697 : SEntry3_III , x3698 : SEntry3_III) = {
      val x3699 = x3697._1;
      val x3700 = x3698._1;
      val x3701 = x3699.==(x3700);
      val x3702 = x3699.>(x3700);
      val x3703 = if(x3702) 1 else -1;
      val x3704 = if(x3701) 0 else x3703;
      x3704
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x4082 : SEntry8_IIIITIIB) = {
      var x4083: Int = -889275714;
      val x4084 = x4082._2;
      val x4085 = x4084.hashCode();
      val x4086 = -862048943.*(x4085);
      val x4087 = x4086.<<(15);
      val x4088 = x4086.>>>(-15);
      val x4089 = x4087.|(x4088);
      val x4090 = x4089.*(461845907);
      val x4091 = x4083;
      val x4092 = x4090.^(x4091);
      val x4093 = x4092.<<(13);
      val x4094 = x4092.>>>(-13);
      val x4095 = x4093.|(x4094);
      val x4096 = x4095.*(5);
      val x4097 = x4096.+(-430675100);
      x4083 = x4097
      val x4099 = x4082._3;
      val x4100 = x4099.hashCode();
      val x4101 = -862048943.*(x4100);
      val x4102 = x4101.<<(15);
      val x4103 = x4101.>>>(-15);
      val x4104 = x4102.|(x4103);
      val x4105 = x4104.*(461845907);
      val x4106 = x4083;
      val x4107 = x4105.^(x4106);
      val x4108 = x4107.<<(13);
      val x4109 = x4107.>>>(-13);
      val x4110 = x4108.|(x4109);
      val x4111 = x4110.*(5);
      val x4112 = x4111.+(-430675100);
      x4083 = x4112
      val x4114 = x4082._4;
      val x4115 = x4114.hashCode();
      val x4116 = -862048943.*(x4115);
      val x4117 = x4116.<<(15);
      val x4118 = x4116.>>>(-15);
      val x4119 = x4117.|(x4118);
      val x4120 = x4119.*(461845907);
      val x4121 = x4083;
      val x4122 = x4120.^(x4121);
      val x4123 = x4122.<<(13);
      val x4124 = x4122.>>>(-13);
      val x4125 = x4123.|(x4124);
      val x4126 = x4125.*(5);
      val x4127 = x4126.+(-430675100);
      x4083 = x4127
      val x4129 = x4083;
      val x4130 = x4129.^(2);
      val x4131 = x4130.>>>(16);
      val x4132 = x4130.^(x4131);
      val x4133 = x4132.*(-2048144789);
      val x4134 = x4133.>>>(13);
      val x4135 = x4133.^(x4134);
      val x4136 = x4135.*(-1028477387);
      val x4137 = x4136.>>>(16);
      val x4138 = x4136.^(x4137);
      x4138
    }
    override def cmp(x4140 : SEntry8_IIIITIIB , x4141 : SEntry8_IIIITIIB) = {
      val x4142 = x4140._1;
      val x4143 = x4141._1;
      val x4144 = x4142.==(x4143);
      val x4145 = x4142.>(x4143);
      val x4146 = if(x4145) 1 else -1;
      val x4147 = if(x4144) 0 else x4146;
      x4147
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4538 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4539: Int = 0;
      val x4540 = x4538._1;
      val x4541 = x4540.-(1);
      val x4542 = x4539;
      val x4543 = x4542.*(100000);
      val x4544 = x4543.+(x4541);
      x4539 = x4544
      val x4546 = x4538._2;
      val x4547 = x4546.-(1);
      val x4548 = x4539;
      val x4549 = x4548.*(1);
      val x4550 = x4549.+(x4547);
      x4539 = x4550
      val x4552 = x4539;
      x4552
    }
    override def cmp(x4535 : SEntry17_IIISSSSSSSSSSIIIS , x4536 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4432 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4433: Int = 0;
      val x4434 = x4432._1;
      val x4435 = x4434.-(1);
      val x4436 = x4433;
      val x4437 = x4436.*(3000);
      val x4438 = x4437.+(x4435);
      x4433 = x4438
      val x4440 = x4432._2;
      val x4441 = x4440.-(1);
      val x4442 = x4433;
      val x4443 = x4442.*(10);
      val x4444 = x4443.+(x4441);
      x4433 = x4444
      val x4446 = x4432._3;
      val x4447 = x4446.-(1);
      val x4448 = x4433;
      val x4449 = x4448.*(1);
      val x4450 = x4449.+(x4447);
      x4433 = x4450
      val x4452 = x4433;
      x4452
    }
    override def cmp(x4429 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4430 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3989 : SEntry5_IISDS) = {
      var x3990: Int = 0;
      val x3991 = x3989._1;
      val x3992 = x3991.-(1);
      val x3993 = x3990;
      val x3994 = x3993.*(100000);
      val x3995 = x3994.+(x3992);
      x3990 = x3995
      val x3997 = x3990;
      x3997
    }
    override def cmp(x3986 : SEntry5_IISDS , x3987 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3970 : SEntry9_ISSSSSSDD) = {
      var x3971: Int = 0;
      val x3972 = x3970._1;
      val x3973 = x3972.-(1);
      val x3974 = x3971;
      val x3975 = x3974.*(1);
      val x3976 = x3975.+(x3973);
      x3971 = x3976
      val x3978 = x3971;
      x3978
    }
    override def cmp(x3967 : SEntry9_ISSSSSSDD , x3968 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4234 : SEntry11_IISSSSSSDDI) = {
      var x4235: Int = 0;
      val x4236 = x4234._1;
      val x4237 = x4236.-(1);
      val x4238 = x4235;
      val x4239 = x4238.*(10);
      val x4240 = x4239.+(x4237);
      x4235 = x4240
      val x4242 = x4234._2;
      val x4243 = x4242.-(1);
      val x4244 = x4235;
      val x4245 = x4244.*(1);
      val x4246 = x4245.+(x4243);
      x4235 = x4246
      val x4248 = x4235;
      x4248
    }
    override def cmp(x4231 : SEntry11_IISSSSSSDDI , x4232 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
  val x8134 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x7690 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x8107 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x7747 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7511 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x7534 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7657 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8120 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x7524 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7908 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7890 = SEntry8_IIIIITDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x7867 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x8117 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x8103 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8082 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x7538 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x8110 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x7925 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7764 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7861 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x7735 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x8207 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7670 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
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
        x7511._2_=(x27)
        x7511._3_=(x12)
        val x12519 = x3766.get(x7511);
        if((x12519.!=(null))) 
        {
          val x7517 = x12519._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x7517)
          newOrderTbl.delete(x12519)
          val x41 = x18;
          x7524._1_=(x7517)
          x7524._2_=(x41)
          x7524._3_=(x12)
          val x12533 = x4227.get(x7524);
          val x7527 = x12533._4;
          x12533._6_=(x13)
          var x51: Double = 0.0;
          val x53 = x18;
          x7534._1_=(x7517)
          x7534._2_=(x53)
          x7534._3_=(x12)
          x4427.slice(x7534, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              orderLineEntry._7_=(x11)
              val x58 = x51;
              val x7581 = orderLineEntry._9;
              x51 = (x58.+(x7581))
              ()
            }
          }))
          val x66 = x18;
          x7538._1_=(x7527)
          x7538._2_=(x66)
          x7538._3_=(x12)
          val x12555 = x4532.get(x7538);
          val x70 = x51;
          x12555._17 +=(x70)
          x12555._20 +=(1)
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
      1
    }
  }
  class StockLevelTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x82 : Boolean, x83 : Date, x84 : Int, x85 : Int, x86 : Int, x87 : Int) =     {
      x7657._1_=(x86)
      x7657._2_=(x85)
      val x12626 = x4254.get(x7657);
      val x7660 = x12626._11;
      var x97: Int = (x7660.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply2;
      while({
        val x101 = x97;
        (x101.<(x7660))
      })
      {
        val x103 = x97;
        x7670._1_=(x103)
        x7670._2_=(x86)
        x7670._3_=(x85)
        x4427.slice(x7670, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
            val x7688 = orderLineEntry._5;
            x7690._1_=(x7688)
            x7690._2_=(x85)
            val x12640 = x4558.get(x7690);
            val x7692 = x12640._3;
            if((x7692.<(x87))) 
            {
              val x116 = unique_ol_i_id.+=(x7688);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x120 = x97;
        x97 = (x120.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x126 : Boolean, x127 : Date, x128 : Int, x129 : Int, x130 : Int, x131 : Int, x132 : Int, x133 : String) =     {
      val x7732 = if((x131.>(0))) 
      {
        val x7744 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7747._2_=(x130)
        x7747._3_=(x129)
        x7747._6_=(x133)
        x4533.slice(x7747, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7744.append(custEntry)
            ()
          }
        }))
        val x145 = x7744.size;
        var x147: Int = (x145./(2));
        val x149 = x7744.size;
        if(((x149.%(2)).==(0))) 
        {
          val x152 = x147;
          x147 = (x152.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x163 = x7744.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7791 = c1._4;
            val x7792 = c2._4;
            ((StringExtra.StringCompare(x7791, x7792)).<(0))
          }
        }));
        val x164 = x147;
        val x7762 = x163.apply(x164);
        x7762
      }
      else
      {
        x7764._1_=(x132)
        x7764._2_=(x130)
        x7764._3_=(x129)
        val x12722 = x4532.get(x7764);
        x12722
      }
      ;
      val x7733 = x7732._3;
      x7735._2_=(x130)
      x7735._3_=(x129)
      x7735._4_=(x7733)
      val x12730 = x4228.get(x7735);
      var x184: Int = 0;
      val x7740 = x12730._1;
      x184 = x7740
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x188 : Boolean, x189 : Date, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : Int, x195 : Int, x196 : Int, x197 : String, x198 : Double) =     {
      x7861._1_=(x191)
      val x12785 = x3984.get(x7861);
      x12785._9 +=(x198)
      x7867._1_=(x192)
      x7867._2_=(x191)
      val x12790 = x4254.get(x7867);
      x12790._10 +=(x198)
      val x7872 = if((x193.>(0))) 
      {
        val x7905 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x7908._2_=(x195)
        x7908._3_=(x194)
        x7908._6_=(x197)
        x4533.slice(x7908, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
            x7905.append(custEntry)
            ()
          }
        }))
        val x223 = x7905.size;
        var x225: Int = (x223./(2));
        val x227 = x7905.size;
        if(((x227.%(2)).==(0))) 
        {
          val x230 = x225;
          x225 = (x230.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x241 = x7905.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x7972 = c1._4;
            val x7973 = c2._4;
            ((StringExtra.StringCompare(x7972, x7973)).<(0))
          }
        }));
        val x242 = x225;
        val x7923 = x241.apply(x242);
        x7923
      }
      else
      {
        x7925._1_=(x196)
        x7925._2_=(x195)
        x7925._3_=(x194)
        val x12827 = x4532.get(x7925);
        x12827
      }
      ;
      val x7873 = x7872._21;
      val x7874 = x7872._14;
      val x251 = x7874.contains("BC");
      if(x251) 
      {
        val x7877 = x7872._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x7877,x195,x194,x192,x191,x198,x189,x7873)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x7872._17 +=(x198)
        x7872._21_=(c_new_data)
        ()
      }
      else
      {
        x7872._17 +=(x198)
        ()
      }
      
      val x7884 = x12785._2;
      val x7885 = x12790._3;
      var h_data = "%.10s    %.10s".format(x7884,x7885)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x7888 = x7872._1;
      x7890._1_=(x7888)
      x7890._2_=(x195)
      x7890._3_=(x194)
      x7890._4_=(x192)
      x7890._5_=(x191)
      x7890._6_=(x189)
      x7890._7_=(x198)
      x7890._8_=(h_data)
      historyTbl.insert(x7890)
      1
    }
  }
  class NewOrderTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x272 : Boolean, x273 : Date, x274 : Int, x275 : Int, x276 : Int, x277 : Int, x278 : Int, x279 : Int, x280 : Array[Int], x281 : Array[Int], x282 : Array[Int], x283 : Array[Double], x284 : Array[String], x285 : Array[Int], x286 : Array[String], x287 : Array[Double]) =     {
      var x289: Int = 0;
      var x292: Int = 0;
      val idata = new Array[String](x278);
      var x297: Boolean = true;
      while({
        val x299 = x289;
        ((x299.<(x278)).&&({
          val x301 = x297;
          x301
        }))
      })
      {
        val x304 = x289;
        val x305 = x280.apply(x304);
        x8082._1_=(x305)
        val x12938 = x4003.get(x8082);
        if((x12938.==(null))) 
        {
          x297 = false
          ()
        }
        else
        {
          val x312 = x289;
          val x8089 = x12938._3;
          x284.update(x312, x8089)
          val x315 = x289;
          val x8092 = x12938._4;
          x283.update(x315, x8092)
          val x318 = x289;
          val x8095 = x12938._5;
          idata.update(x318, x8095)
          ()
        }
        
        val x322 = x289;
        x289 = (x322.+(1))
        ()
      }
      val x326 = x297;
      if(x326) 
      {
        x8103._1_=(x277)
        x8103._2_=(x276)
        x8103._3_=(x275)
        val x12961 = x4532.get(x8103);
        x8107._1_=(x275)
        val x12964 = x3984.get(x8107);
        x8110._1_=(x276)
        x8110._2_=(x275)
        val x12968 = x4254.get(x8110);
        val x8112 = x12968._11;
        x12968._11 +=(1)
        x8117._1_=(x8112)
        x8117._2_=(x276)
        x8117._3_=(x275)
        x8117._4_=(x277)
        x8117._5_=(x273)
        x8117._6_=(-1)
        x8117._7_=(x278)
        x8117._8_=((x279.>(0)))
        orderTbl.insert(x8117)
        x8120._1_=(x8112)
        x8120._2_=(x276)
        x8120._3_=(x275)
        newOrderTbl.insert(x8120)
        var x352: Double = 0.0;
        x289 = 0
        while({
          val x355 = x289;
          (x355.<(x278))
        })
        {
          val x358 = x289;
          val ol_supply_w_id = x281.apply(x358);
          val x361 = x289;
          val ol_i_id = x280.apply(x361);
          val x364 = x289;
          val ol_quantity = x282.apply(x364);
          x8134._1_=(ol_i_id)
          x8134._2_=(ol_supply_w_id)
          val x13001 = x4558.get(x8134);
          val ol_dist_info = if((x276.==(1))) 
          {
            val x8138 = x13001._4;
            x8138
          }
          else
          {
            val x397 = if((x276.==(2))) 
            {
              val x8141 = x13001._5;
              x8141
            }
            else
            {
              val x396 = if((x276.==(3))) 
              {
                val x8144 = x13001._6;
                x8144
              }
              else
              {
                val x395 = if((x276.==(4))) 
                {
                  val x8147 = x13001._7;
                  x8147
                }
                else
                {
                  val x394 = if((x276.==(5))) 
                  {
                    val x8150 = x13001._8;
                    x8150
                  }
                  else
                  {
                    val x393 = if((x276.==(6))) 
                    {
                      val x8153 = x13001._9;
                      x8153
                    }
                    else
                    {
                      val x392 = if((x276.==(7))) 
                      {
                        val x8156 = x13001._10;
                        x8156
                      }
                      else
                      {
                        val x391 = if((x276.==(8))) 
                        {
                          val x8159 = x13001._11;
                          x8159
                        }
                        else
                        {
                          val x390 = if((x276.==(9))) 
                          {
                            val x8162 = x13001._12;
                            x8162
                          }
                          else
                          {
                            val x8163 = x13001._13;
                            x8163
                          }
                          ;
                          x390
                        }
                        ;
                        x391
                      }
                      ;
                      x392
                    }
                    ;
                    x393
                  }
                  ;
                  x394
                }
                ;
                x395
              }
              ;
              x396
            }
            ;
            x397
          }
          ;
          val x8164 = x13001._3;
          val x401 = x289;
          x285.update(x401, x8164)
          val x8167 = x12961._14;
          val x404 = x8167.contains("original");
          if((x404.&&({
            val x8170 = x13001._17;
            val x406 = x8170.contains("original");
            x406
          }))) 
          {
            val x408 = x289;
            x286.update(x408, "B")
            ()
          }
          else
          {
            val x410 = x289;
            x286.update(x410, "G")
            ()
          }
          
          x13001._3_=((x8164.-(ol_quantity)))
          if((x8164.<=(ol_quantity))) 
          {
            x13001._3 +=(91)
            ()
          }
          else
          {
            ()
          }
          
          var x419: Int = 0;
          if((ol_supply_w_id.!=(x275))) 
          {
            x419 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x8187 = x12961._16;
          val x8188 = x12964._8;
          val x8189 = x12968._9;
          val x432 = x289;
          val x433 = x283.apply(x432);
          val ol_amount = (((ol_quantity.toDouble).*(x433)).*(((1.0.+(x8188)).+(x8189)))).*((1.0.-(x8187)));
          val x441 = x289;
          x287.update(x441, ol_amount)
          val x443 = x352;
          x352 = (x443.+(ol_amount))
          val x446 = x289;
          x8207._1_=(x8112)
          x8207._2_=(x276)
          x8207._3_=(x275)
          x8207._4_=((x446.+(1)))
          x8207._5_=(ol_i_id)
          x8207._6_=(ol_supply_w_id)
          x8207._8_=(ol_quantity)
          x8207._9_=(ol_amount)
          x8207._10_=(ol_dist_info)
          orderLineTbl.insert(x8207)
          val x451 = x289;
          x289 = (x451.+(1))
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
