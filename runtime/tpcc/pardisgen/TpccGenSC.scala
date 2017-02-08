
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 
case class SEntry5_IISDS(var _1: Int, var _2: Int, var _3: String, var _4: Double, var _5: String) extends Entry(5) {def this() = this(-2147483648, -2147483648, null, -1.7976931348623157E308, null) ; def copy = SEntry5_IISDS(_1, _2, _3, _4, _5); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry5_IISDS]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5} }
case class SEntry11_IISSSSSSDDI(var _1: Int, var _2: Int, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: Double, var _10: Double, var _11: Int) extends Entry(11) {def this() = this(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648) ; def copy = SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry11_IISSSSSSDDI]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8;_9 = that._9;_10 = that._10;_11 = that._11} }
case class SEntry21_IIISSSSSSSSSTSDDDDIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: Date, var _14: String, var _15: Double, var _16: Double, var _17: Double, var _18: Double, var _19: Int, var _20: Int, var _21: String) extends Entry(21) {def this() = this(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null) ; def copy = SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry21_IIISSSSSSSSSTSDDDDIIS]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8;_9 = that._9;_10 = that._10;_11 = that._11;_12 = that._12;_13 = that._13;_14 = that._14;_15 = that._15;_16 = that._16;_17 = that._17;_18 = that._18;_19 = that._19;_20 = that._20;_21 = that._21} }
case class SEntry8_IIIITIIB(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Date, var _6: Int, var _7: Int, var _8: Boolean) extends Entry(8) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false) ; def copy = SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry8_IIIITIIB]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8} }
case class SEntry3_III(var _1: Int, var _2: Int, var _3: Int) extends Entry(3) {def this() = this(-2147483648, -2147483648, -2147483648) ; def copy = SEntry3_III(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_III]; _1 = that._1;_2 = that._2;_3 = that._3} }
case class SEntry8_IIIIITDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Date, var _7: Double, var _8: String) extends Entry(8) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null) ; def copy = SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry8_IIIIITDS]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8} }
case class SEntry17_IIISSSSSSSSSSIIIS(var _1: Int, var _2: Int, var _3: Int, var _4: String, var _5: String, var _6: String, var _7: String, var _8: String, var _9: String, var _10: String, var _11: String, var _12: String, var _13: String, var _14: Int, var _15: Int, var _16: Int, var _17: String) extends Entry(17) {def this() = this(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null) ; def copy = SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry17_IIISSSSSSSSSSIIIS]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8;_9 = that._9;_10 = that._10;_11 = that._11;_12 = that._12;_13 = that._13;_14 = that._14;_15 = that._15;_16 = that._16;_17 = that._17} }
case class SEntry10_IIIIIITIDS(var _1: Int, var _2: Int, var _3: Int, var _4: Int, var _5: Int, var _6: Int, var _7: Date, var _8: Int, var _9: Double, var _10: String) extends Entry(10) {def this() = this(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null) ; def copy = SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry10_IIIIIITIDS]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8;_9 = that._9;_10 = that._10} }
case class SEntry9_ISSSSSSDD(var _1: Int, var _2: String, var _3: String, var _4: String, var _5: String, var _6: String, var _7: String, var _8: Double, var _9: Double) extends Entry(9) {def this() = this(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308) ; def copy = SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry9_ISSSSSSDD]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5;_6 = that._6;_7 = that._7;_8 = that._8;_9 = that._9} }
class SCExecutor 
{
  val x3646 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val newOrderTbl = new Store[SEntry3_III](3, x3646);
  val x3648 = newOrderTbl.index(0, IHash, true, -1)
  val x3649 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val x3650 = newOrderTbl.index(2, INone, false, -1)
  val x3784 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx12345678)
  val historyTbl = new Store[SEntry8_IIIIITDS](1, x3784);
  val x3786 = historyTbl.index(0, IHash, true, -1)
  val x3803 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val warehouseTbl = new Store[SEntry9_ISSSSSSDD](1, x3803);
  val x3805 = warehouseTbl.index(0, IDirect, true, 1)
  val x3822 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val itemTbl = new Store[SEntry5_IISDS](1, x3822);
  val x3824 = itemTbl.index(0, IDirect, true, 100000)
  val x3986 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val orderTbl = new Store[SEntry8_IIIITIIB](3, x3986);
  val x3988 = orderTbl.index(0, IHash, true, -1)
  val x3989 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val x3990 = orderTbl.index(2, INone, false, -1)
  val x4013 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val districtTbl = new Store[SEntry11_IISSSSSSDDI](1, x4013);
  val x4015 = districtTbl.index(0, IDirect, true, 10)
  val x4145 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val orderLineTbl = new Store[SEntry10_IIIIIITIDS](2, x4145);
  val x4147 = orderLineTbl.index(0, IHash, true, -1)
  val x4148 = orderLineTbl.index(1, IHash, false, -1)
  val x4233 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val customerTbl = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4233);
  val x4235 = customerTbl.index(0, IDirect, true, 30000)
  val x4236 = customerTbl.index(1, IHash, false, -1)
  val x4259 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val stockTbl = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4259);
  val x4261 = stockTbl.index(0, IDirect, true, 100000)
  

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4017 : SEntry10_IIIIIITIDS) = {
      var x4018: Int = 0;
      val x4019 = x4018;
      val x4020 = x4017._1;
      x4018 = (x4019.^(((((x4020.hashCode()).+(-1640531527)).+((x4019.<<(6)))).+((x4019.>>(2))))))
      val x4029 = x4018;
      val x4030 = x4017._2;
      x4018 = (x4029.^(((((x4030.hashCode()).+(-1640531527)).+((x4029.<<(6)))).+((x4029.>>(2))))))
      val x4039 = x4018;
      val x4040 = x4017._3;
      x4018 = (x4039.^(((((x4040.hashCode()).+(-1640531527)).+((x4039.<<(6)))).+((x4039.>>(2))))))
      val x4049 = x4018;
      val x4050 = x4017._4;
      x4018 = (x4049.^(((((x4050.hashCode()).+(-1640531527)).+((x4049.<<(6)))).+((x4049.>>(2))))))
      val x4059 = x4018;
      x4059
    }
    override def cmp(x4061 : SEntry10_IIIIIITIDS , x4062 : SEntry10_IIIIIITIDS) = {
      var x4063: Int = 0;
      val x4064 = x4061._1;
      val x4065 = x4062._1;
      if((x4064.==(x4065))) {
        val x4067 = x4061._2;
        val x4068 = x4062._2;
        if((x4067.==(x4068))) {
          val x4070 = x4061._3;
          val x4071 = x4062._3;
          if((x4070.==(x4071))) {
            val x4073 = x4061._4;
            val x4074 = x4062._4;
            if((x4073.==(x4074))) {
              x4063 = 0
            } else {
              x4063 = 1
            }
          } else {
            x4063 = 1
          }
        } else {
          x4063 = 1
        }
      } else {
        x4063 = 1
      }
      val x4085 = x4063;
      x4085
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3929 : SEntry8_IIIITIIB) = {
      var x3930: Int = 0;
      val x3931 = x3930;
      val x3932 = x3929._2;
      x3930 = (x3931.^(((((x3932.hashCode()).+(-1640531527)).+((x3931.<<(6)))).+((x3931.>>(2))))))
      val x3941 = x3930;
      val x3942 = x3929._3;
      x3930 = (x3941.^(((((x3942.hashCode()).+(-1640531527)).+((x3941.<<(6)))).+((x3941.>>(2))))))
      val x3951 = x3930;
      val x3952 = x3929._4;
      x3930 = (x3951.^(((((x3952.hashCode()).+(-1640531527)).+((x3951.<<(6)))).+((x3951.>>(2))))))
      val x3961 = x3930;
      x3961
    }
    override def cmp(x3963 : SEntry8_IIIITIIB , x3964 : SEntry8_IIIITIIB) = {
      var x3965: Int = 0;
      val x3966 = x3963._2;
      val x3967 = x3964._2;
      if((x3966.==(x3967))) {
        val x3969 = x3963._3;
        val x3970 = x3964._3;
        if((x3969.==(x3970))) {
          val x3972 = x3963._4;
          val x3973 = x3964._4;
          if((x3972.==(x3973))) {
            x3965 = 0
          } else {
            x3965 = 1
          }
        } else {
          x3965 = 1
        }
      } else {
        x3965 = 1
      }
      val x3982 = x3965;
      x3982
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3514 : SEntry3_III) = {
      var x3515: Int = 0;
      val x3516 = x3515;
      val x3517 = x3514._1;
      x3515 = (x3516.^(((((x3517.hashCode()).+(-1640531527)).+((x3516.<<(6)))).+((x3516.>>(2))))))
      val x3526 = x3515;
      val x3527 = x3514._2;
      x3515 = (x3526.^(((((x3527.hashCode()).+(-1640531527)).+((x3526.<<(6)))).+((x3526.>>(2))))))
      val x3536 = x3515;
      val x3537 = x3514._3;
      x3515 = (x3536.^(((((x3537.hashCode()).+(-1640531527)).+((x3536.<<(6)))).+((x3536.>>(2))))))
      val x3546 = x3515;
      x3546
    }
    override def cmp(x3548 : SEntry3_III , x3549 : SEntry3_III) = {
      var x3550: Int = 0;
      val x3551 = x3548._1;
      val x3552 = x3549._1;
      if((x3551.==(x3552))) {
        val x3554 = x3548._2;
        val x3555 = x3549._2;
        if((x3554.==(x3555))) {
          val x3557 = x3548._3;
          val x3558 = x3549._3;
          if((x3557.==(x3558))) {
            x3550 = 0
          } else {
            x3550 = 1
          }
        } else {
          x3550 = 1
        }
      } else {
        x3550 = 1
      }
      val x3567 = x3550;
      x3567
    }
  }
   object SEntry8_IIIIITDS_Idx12345678 extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3652 : SEntry8_IIIIITDS) = {
      var x3653: Int = 0;
      val x3654 = x3653;
      val x3655 = x3652._1;
      x3653 = (x3654.^(((((x3655.hashCode()).+(-1640531527)).+((x3654.<<(6)))).+((x3654.>>(2))))))
      val x3664 = x3653;
      val x3665 = x3652._2;
      x3653 = (x3664.^(((((x3665.hashCode()).+(-1640531527)).+((x3664.<<(6)))).+((x3664.>>(2))))))
      val x3674 = x3653;
      val x3675 = x3652._3;
      x3653 = (x3674.^(((((x3675.hashCode()).+(-1640531527)).+((x3674.<<(6)))).+((x3674.>>(2))))))
      val x3684 = x3653;
      val x3685 = x3652._4;
      x3653 = (x3684.^(((((x3685.hashCode()).+(-1640531527)).+((x3684.<<(6)))).+((x3684.>>(2))))))
      val x3694 = x3653;
      val x3695 = x3652._5;
      x3653 = (x3694.^(((((x3695.hashCode()).+(-1640531527)).+((x3694.<<(6)))).+((x3694.>>(2))))))
      val x3704 = x3653;
      val x3705 = x3652._6;
      x3653 = (x3704.^(((((x3705.hashCode()).+(-1640531527)).+((x3704.<<(6)))).+((x3704.>>(2))))))
      val x3714 = x3653;
      val x3715 = x3652._7;
      x3653 = (x3714.^(((((x3715.hashCode()).+(-1640531527)).+((x3714.<<(6)))).+((x3714.>>(2))))))
      val x3724 = x3653;
      val x3725 = x3652._8;
      x3653 = (x3724.^(((((x3725.hashCode()).+(-1640531527)).+((x3724.<<(6)))).+((x3724.>>(2))))))
      val x3734 = x3653;
      x3734
    }
    override def cmp(x3736 : SEntry8_IIIIITDS , x3737 : SEntry8_IIIIITDS) = {
      var x3738: Int = 0;
      val x3739 = x3736._1;
      val x3740 = x3737._1;
      if((x3739.==(x3740))) {
        val x3742 = x3736._2;
        val x3743 = x3737._2;
        if((x3742.==(x3743))) {
          val x3745 = x3736._3;
          val x3746 = x3737._3;
          if((x3745.==(x3746))) {
            val x3748 = x3736._4;
            val x3749 = x3737._4;
            if((x3748.==(x3749))) {
              val x3751 = x3736._5;
              val x3752 = x3737._5;
              if((x3751.==(x3752))) {
                val x3754 = x3736._6;
                val x3755 = x3737._6;
                if((x3754.==(x3755))) {
                  val x3757 = x3736._7;
                  val x3758 = x3737._7;
                  if((x3757.==(x3758))) {
                    val x3760 = x3736._8;
                    val x3761 = x3737._8;
                    if((x3760.==(x3761))) {
                      x3738 = 0
                    } else {
                      x3738 = 1
                    }
                  } else {
                    x3738 = 1
                  }
                } else {
                  x3738 = 1
                }
              } else {
                x3738 = 1
              }
            } else {
              x3738 = 1
            }
          } else {
            x3738 = 1
          }
        } else {
          x3738 = 1
        }
      } else {
        x3738 = 1
      }
      val x3780 = x3738;
      x3780
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4088 : SEntry10_IIIIIITIDS) = {
      var x4089: Int = 0;
      val x4090 = x4089;
      val x4091 = x4088._1;
      x4089 = (x4090.^(((((x4091.hashCode()).+(-1640531527)).+((x4090.<<(6)))).+((x4090.>>(2))))))
      val x4100 = x4089;
      val x4101 = x4088._2;
      x4089 = (x4100.^(((((x4101.hashCode()).+(-1640531527)).+((x4100.<<(6)))).+((x4100.>>(2))))))
      val x4110 = x4089;
      val x4111 = x4088._3;
      x4089 = (x4110.^(((((x4111.hashCode()).+(-1640531527)).+((x4110.<<(6)))).+((x4110.>>(2))))))
      val x4120 = x4089;
      x4120
    }
    override def cmp(x4122 : SEntry10_IIIIIITIDS , x4123 : SEntry10_IIIIIITIDS) = {
      var x4124: Int = 0;
      val x4125 = x4122._1;
      val x4126 = x4123._1;
      if((x4125.==(x4126))) {
        val x4128 = x4122._2;
        val x4129 = x4123._2;
        if((x4128.==(x4129))) {
          val x4131 = x4122._3;
          val x4132 = x4123._3;
          if((x4131.==(x4132))) {
            x4124 = 0
          } else {
            x4124 = 1
          }
        } else {
          x4124 = 1
        }
      } else {
        x4124 = 1
      }
      val x4141 = x4124;
      x4141
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3604 : SEntry3_III) = {
      var x3605: Int = 0;
      val x3606 = x3605;
      val x3607 = x3604._2;
      x3605 = (x3606.^(((((x3607.hashCode()).+(-1640531527)).+((x3606.<<(6)))).+((x3606.>>(2))))))
      val x3616 = x3605;
      val x3617 = x3604._3;
      x3605 = (x3616.^(((((x3617.hashCode()).+(-1640531527)).+((x3616.<<(6)))).+((x3616.>>(2))))))
      val x3626 = x3605;
      x3626
    }
    override def cmp(x3628 : SEntry3_III , x3629 : SEntry3_III) = {
      var x3630: Int = 0;
      val x3631 = x3628._2;
      val x3632 = x3629._2;
      if((x3631.==(x3632))) {
        val x3634 = x3628._3;
        val x3635 = x3629._3;
        if((x3634.==(x3635))) {
          x3630 = 0
        } else {
          x3630 = 1
        }
      } else {
        x3630 = 1
      }
      val x3642 = x3630;
      x3642
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4176 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4177: Int = 0;
      val x4178 = x4177;
      val x4179 = x4176._2;
      x4177 = (x4178.^(((((x4179.hashCode()).+(-1640531527)).+((x4178.<<(6)))).+((x4178.>>(2))))))
      val x4188 = x4177;
      val x4189 = x4176._3;
      x4177 = (x4188.^(((((x4189.hashCode()).+(-1640531527)).+((x4188.<<(6)))).+((x4188.>>(2))))))
      val x4198 = x4177;
      val x4199 = x4176._6;
      x4177 = (x4198.^(((((x4199.hashCode()).+(-1640531527)).+((x4198.<<(6)))).+((x4198.>>(2))))))
      val x4208 = x4177;
      x4208
    }
    override def cmp(x4210 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4211 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4212: Int = 0;
      val x4213 = x4210._2;
      val x4214 = x4211._2;
      if((x4213.==(x4214))) {
        val x4216 = x4210._3;
        val x4217 = x4211._3;
        if((x4216.==(x4217))) {
          val x4219 = x4210._6;
          val x4220 = x4211._6;
          if((x4219.==(x4220))) {
            x4212 = 0
          } else {
            x4212 = 1
          }
        } else {
          x4212 = 1
        }
      } else {
        x4212 = 1
      }
      val x4229 = x4212;
      x4229
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3829 : SEntry8_IIIITIIB) = {
      var x3830: Int = 0;
      val x3831 = x3830;
      val x3832 = x3829._1;
      x3830 = (x3831.^(((((x3832.hashCode()).+(-1640531527)).+((x3831.<<(6)))).+((x3831.>>(2))))))
      val x3841 = x3830;
      val x3842 = x3829._2;
      x3830 = (x3841.^(((((x3842.hashCode()).+(-1640531527)).+((x3841.<<(6)))).+((x3841.>>(2))))))
      val x3851 = x3830;
      val x3852 = x3829._3;
      x3830 = (x3851.^(((((x3852.hashCode()).+(-1640531527)).+((x3851.<<(6)))).+((x3851.>>(2))))))
      val x3861 = x3830;
      x3861
    }
    override def cmp(x3863 : SEntry8_IIIITIIB , x3864 : SEntry8_IIIITIIB) = {
      var x3865: Int = 0;
      val x3866 = x3863._1;
      val x3867 = x3864._1;
      if((x3866.==(x3867))) {
        val x3869 = x3863._2;
        val x3870 = x3864._2;
        if((x3869.==(x3870))) {
          val x3872 = x3863._3;
          val x3873 = x3864._3;
          if((x3872.==(x3873))) {
            x3865 = 0
          } else {
            x3865 = 1
          }
        } else {
          x3865 = 1
        }
      } else {
        x3865 = 1
      }
      val x3882 = x3865;
      x3882
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3570 : SEntry3_III) = {
      var x3571: Int = 0;
      val x3572 = x3571;
      val x3573 = x3570._2;
      x3571 = (x3572.^(((((x3573.hashCode()).+(-1640531527)).+((x3572.<<(6)))).+((x3572.>>(2))))))
      val x3582 = x3571;
      val x3583 = x3570._3;
      x3571 = (x3582.^(((((x3583.hashCode()).+(-1640531527)).+((x3582.<<(6)))).+((x3582.>>(2))))))
      val x3592 = x3571;
      x3592
    }
    override def cmp(x3594 : SEntry3_III , x3595 : SEntry3_III) = {
      val x3596 = x3594._1;
      val x3597 = x3595._1;
      (if((x3596.==(x3597))) 0 else (if((x3596.>(x3597))) 1 else -1))
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3885 : SEntry8_IIIITIIB) = {
      var x3886: Int = 0;
      val x3887 = x3886;
      val x3888 = x3885._2;
      x3886 = (x3887.^(((((x3888.hashCode()).+(-1640531527)).+((x3887.<<(6)))).+((x3887.>>(2))))))
      val x3897 = x3886;
      val x3898 = x3885._3;
      x3886 = (x3897.^(((((x3898.hashCode()).+(-1640531527)).+((x3897.<<(6)))).+((x3897.>>(2))))))
      val x3907 = x3886;
      val x3908 = x3885._4;
      x3886 = (x3907.^(((((x3908.hashCode()).+(-1640531527)).+((x3907.<<(6)))).+((x3907.>>(2))))))
      val x3917 = x3886;
      x3917
    }
    override def cmp(x3919 : SEntry8_IIIITIIB , x3920 : SEntry8_IIIITIIB) = {
      val x3921 = x3919._1;
      val x3922 = x3920._1;
      (if((x3921.==(x3922))) 0 else (if((x3921.>(x3922))) 1 else -1))
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4241 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4242: Int = 0;
      val x4243 = x4241._1;
      val x4245 = x4242;
      x4242 = ((x4245.*(100000)).+((x4243.-(1))))
      val x4249 = x4241._2;
      val x4251 = x4242;
      x4242 = ((x4251.*(1)).+((x4249.-(1))))
      val x4255 = x4242;
      x4255
    }
    override def cmp(x4238 : SEntry17_IIISSSSSSSSSSIIIS , x4239 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4153 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4154: Int = 0;
      val x4155 = x4153._1;
      val x4157 = x4154;
      x4154 = ((x4157.*(3000)).+((x4155.-(1))))
      val x4161 = x4153._2;
      val x4163 = x4154;
      x4154 = ((x4163.*(10)).+((x4161.-(1))))
      val x4167 = x4153._3;
      val x4169 = x4154;
      x4154 = ((x4169.*(1)).+((x4167.-(1))))
      val x4173 = x4154;
      x4173
    }
    override def cmp(x4150 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4151 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3810 : SEntry5_IISDS) = {
      var x3811: Int = 0;
      val x3812 = x3810._1;
      val x3814 = x3811;
      x3811 = ((x3814.*(100000)).+((x3812.-(1))))
      val x3818 = x3811;
      x3818
    }
    override def cmp(x3807 : SEntry5_IISDS , x3808 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3791 : SEntry9_ISSSSSSDD) = {
      var x3792: Int = 0;
      val x3793 = x3791._1;
      val x3795 = x3792;
      x3792 = ((x3795.*(1)).+((x3793.-(1))))
      val x3799 = x3792;
      x3799
    }
    override def cmp(x3788 : SEntry9_ISSSSSSDD , x3789 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x3995 : SEntry11_IISSSSSSDDI) = {
      var x3996: Int = 0;
      val x3997 = x3995._1;
      val x3999 = x3996;
      x3996 = ((x3999.*(10)).+((x3997.-(1))))
      val x4003 = x3995._2;
      val x4005 = x3996;
      x3996 = ((x4005.*(1)).+((x4003.-(1))))
      val x4009 = x3996;
      x4009
    }
    override def cmp(x3992 : SEntry11_IISSSSSSDDI , x3993 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
  val x6521 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x7091 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6733 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7065 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x6910 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7085 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6541 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x6853 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6545 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6689 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6760 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6893 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7088 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x6658 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6743 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7098 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7115 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6670 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7188 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x6848 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x6532 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7101 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x6876 = SEntry8_IIIIITDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null);
  class DeliveryTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](10);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val x27 = x18;
        x6521._2_=(x27)
        x6521._3_=(x12)
        val x10772 = x3649.get(x6521);
        if((x10772.!=(null))) {
          val x6525 = x10772._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x6525)
          newOrderTbl.delete(x10772)
          val x41 = x18;
          x6532._1_=(x6525)
          x6532._2_=(x41)
          x6532._3_=(x12)
          val x10785 = x3988.get(x6532);
          val x6534 = x10785._4;
          x10785._6_=(x13)
          var x50: Double = 0.0;
          val x52 = x18;
          x6541._1_=(x6525)
          x6541._2_=(x52)
          x6541._3_=(x12)
          val x12271 = x4148.sliceRes(x6541);
          if((x12271.isEmpty)) {
          } else {
            x4148.sliceResMap(x6541, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
                orderLineEntry._7_=(x11)
                val x57 = x50;
                val x6585 = orderLineEntry._9;
                x50 = (x57.+(x6585))
              
              }
            }), x12271)
          }
          val x65 = x18;
          x6545._1_=(x6534)
          x6545._2_=(x65)
          x6545._3_=(x12)
          val x10807 = x4235.get(x6545);
          val x69 = x50;
          x10807._17 +=(x69)
          x10807._20 +=(1)
        } else {
          val x73 = x18;
          orderIDs.update((x73.-(1)), 0)
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
      x6658._1_=(x85)
      x6658._2_=(x84)
      val x10874 = x4015.get(x6658);
      val x6660 = x10874._11;
      var x95: Int = (x6660.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply2;
      while({
        val x99 = x95;
        (x99.<(x6660))
      })
      {
        val x101 = x95;
        x6670._1_=(x101)
        x6670._2_=(x85)
        x6670._3_=(x84)
        val x12317 = x4148.sliceRes(x6670);
        if((x12317.isEmpty)) {
        } else {
          x4148.sliceResMap(x6670, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              val x6687 = orderLineEntry._5;
              x6689._1_=(x6687)
              x6689._2_=(x84)
              val x10888 = x4261.get(x6689);
              val x6691 = x10888._3;
              if((x6691.<(x86))) {
                val x114 = unique_ol_i_id.+=(x6687);
              } else {
              }
              ()
            }
          }), x12317)
        }
        val x118 = x95;
        x95 = (x118.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x124 : Boolean, x125 : Date, x126 : Int, x127 : Int, x128 : Int, x129 : Int, x130 : Int, x131 : String) =     {
      val x6730 = if((x129.>(0))) {
        val x6740 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6743._2_=(x128)
        x6743._3_=(x127)
        x6743._6_=(x131)
        val x12334 = x4236.sliceRes(x6743);
        if((x12334.isEmpty)) {
        } else {
          x4236.sliceResMap(x6743, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6740.append(custEntry)
              ()
            }
          }), x12334)
        }
        val x143 = x6740.size;
        var x145: Int = (x143./(2));
        val x147 = x6740.size;
        if(((x147.%(2)).==(0))) {
          val x150 = x145;
          x145 = (x150.-(1))
        } else {
        }
        val x161 = x6740.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6784 = c1._4;
            val x6785 = c2._4;
            ((StringExtra.StringCompare(x6784, x6785)).<(0))
          }
        }));
        val x162 = x145;
        val x6758 = x161.apply(x162);
      x6758
      } else {
        x6760._1_=(x130)
        x6760._2_=(x128)
        x6760._3_=(x127)
        val x10968 = x4235.get(x6760);
      x10968
      };
      val x6731 = x6730._3;
      x6733._2_=(x128)
      x6733._3_=(x127)
      x6733._4_=(x6731)
      val x10974 = x3989.get(x6733);
      var x181: Int = 0;
      val x6736 = x10974._1;
      x181 = x6736
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x185 : Boolean, x186 : Date, x187 : Int, x188 : Int, x189 : Int, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : String, x195 : Double) =     {
      x6848._1_=(x188)
      val x11025 = x3805.get(x6848);
      x11025._9 +=(x195)
      x6853._1_=(x189)
      x6853._2_=(x188)
      val x11030 = x4015.get(x6853);
      x11030._10 +=(x195)
      val x6858 = if((x190.>(0))) {
        val x6890 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6893._2_=(x192)
        x6893._3_=(x191)
        x6893._6_=(x194)
        val x12391 = x4236.sliceRes(x6893);
        if((x12391.isEmpty)) {
        } else {
          x4236.sliceResMap(x6893, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6890.append(custEntry)
              ()
            }
          }), x12391)
        }
        val x219 = x6890.size;
        var x221: Int = (x219./(2));
        val x223 = x6890.size;
        if(((x223.%(2)).==(0))) {
          val x226 = x221;
          x221 = (x226.-(1))
        } else {
        }
        val x237 = x6890.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6956 = c1._4;
            val x6957 = c2._4;
            ((StringExtra.StringCompare(x6956, x6957)).<(0))
          }
        }));
        val x238 = x221;
        val x6908 = x237.apply(x238);
      x6908
      } else {
        x6910._1_=(x193)
        x6910._2_=(x192)
        x6910._3_=(x191)
        val x11067 = x4235.get(x6910);
      x11067
      };
      val x6859 = x6858._21;
      val x6860 = x6858._14;
      val x247 = x6860.contains("BC");
      if(x247) {
        val x6863 = x6858._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x6863,x192,x191,x189,x188,x195,x186,x6859)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x6858._17 +=(x195)
        x6858._21_=(c_new_data)
      } else {
        x6858._17 +=(x195)
      }
      val x6870 = x11025._2;
      val x6871 = x11030._3;
      var h_data = "%.10s    %.10s".format(x6870,x6871)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x6874 = x6858._1;
      x6876._1_=(x6874)
      x6876._2_=(x192)
      x6876._3_=(x191)
      x6876._4_=(x189)
      x6876._5_=(x188)
      x6876._6_=(x186)
      x6876._7_=(x195)
      x6876._8_=(h_data)
      historyTbl.unsafeInsert(x6876)
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
        ((x295.<(x274)).&&({
          val x297 = x293;
          x297
        }))
      })
      {
        val x300 = x285;
        val x301 = x276.apply(x300);
        x7065._1_=(x301)
        val x11176 = x3824.get(x7065);
        if((x11176.==(null))) {
          x293 = false
        } else {
          val x307 = x285;
          val x7071 = x11176._3;
          x280.update(x307, x7071)
          val x310 = x285;
          val x7074 = x11176._4;
          x279.update(x310, x7074)
          val x313 = x285;
          val x7077 = x11176._5;
          idata.update(x313, x7077)
        }
        val x317 = x285;
        x285 = (x317.+(1))
        ()
      }
      val x321 = x293;
      if(x321) {
        x7085._1_=(x273)
        x7085._2_=(x272)
        x7085._3_=(x271)
        val x11198 = x4235.get(x7085);
        x7088._1_=(x271)
        val x11201 = x3805.get(x7088);
        x7091._1_=(x272)
        x7091._2_=(x271)
        val x11205 = x4015.get(x7091);
        val x7093 = x11205._11;
        x11205._11 +=(1)
        x7098._1_=(x7093)
        x7098._2_=(x272)
        x7098._3_=(x271)
        x7098._4_=(x273)
        x7098._5_=(x269)
        x7098._6_=(-1)
        x7098._7_=(x274)
        x7098._8_=((x275.>(0)))
        orderTbl.unsafeInsert(x7098)
        x7101._1_=(x7093)
        x7101._2_=(x272)
        x7101._3_=(x271)
        newOrderTbl.unsafeInsert(x7101)
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
          x7115._1_=(ol_i_id)
          x7115._2_=(ol_supply_w_id)
          val x11238 = x4261.get(x7115);
          val ol_dist_info = if((x272.==(1))) {
            val x7119 = x11238._4;
          x7119
          } else {
            val x391 = if((x272.==(2))) {
              val x7122 = x11238._5;
            x7122
            } else {
              val x390 = if((x272.==(3))) {
                val x7125 = x11238._6;
              x7125
              } else {
                val x389 = if((x272.==(4))) {
                  val x7128 = x11238._7;
                x7128
                } else {
                  val x388 = if((x272.==(5))) {
                    val x7131 = x11238._8;
                  x7131
                  } else {
                    val x387 = if((x272.==(6))) {
                      val x7134 = x11238._9;
                    x7134
                    } else {
                      val x386 = if((x272.==(7))) {
                        val x7137 = x11238._10;
                      x7137
                      } else {
                        val x385 = if((x272.==(8))) {
                          val x7140 = x11238._11;
                        x7140
                        } else {
                          val x384 = if((x272.==(9))) {
                            val x7143 = x11238._12;
                          x7143
                          } else {
                            val x7144 = x11238._13;
                          x7144
                          };
                        x384
                        };
                      x385
                      };
                    x386
                    };
                  x387
                  };
                x388
                };
              x389
              };
            x390
            };
          x391
          };
          val x7145 = x11238._3;
          val x395 = x285;
          x281.update(x395, x7145)
          val x7148 = x11198._14;
          val x398 = x7148.contains("original");
          if((x398.&&({
            val x7151 = x11238._17;
            val x400 = x7151.contains("original");
            x400
          }))) {
            val x402 = x285;
            x282.update(x402, "B")
          } else {
            val x404 = x285;
            x282.update(x404, "G")
          }
          x11238._3_=((x7145.-(ol_quantity)))
          if((x7145.<=(ol_quantity))) {
            x11238._3 +=(91)
          } else {
          }
          var x413: Int = 0;
          if((ol_supply_w_id.!=(x271))) {
            x413 = 1
          } else {
          }
          val x7168 = x11198._16;
          val x7169 = x11201._8;
          val x7170 = x11205._9;
          val x426 = x285;
          val x427 = x279.apply(x426);
          val ol_amount = (((ol_quantity.toDouble).*(x427)).*(((1.0.+(x7169)).+(x7170)))).*((1.0.-(x7168)));
          val x435 = x285;
          x283.update(x435, ol_amount)
          val x437 = x346;
          x346 = (x437.+(ol_amount))
          val x440 = x285;
          x7188._1_=(x7093)
          x7188._2_=(x272)
          x7188._3_=(x271)
          x7188._4_=((x440.+(1)))
          x7188._5_=(ol_i_id)
          x7188._6_=(ol_supply_w_id)
          x7188._8_=(ol_quantity)
          x7188._9_=(ol_amount)
          x7188._10_=(ol_dist_info)
          orderLineTbl.unsafeInsert(x7188)
          val x445 = x285;
          x285 = (x445.+(1))
          ()
        }
      } else {
      }
      1
    }
  }

}
