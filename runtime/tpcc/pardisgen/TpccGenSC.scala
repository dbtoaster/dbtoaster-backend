
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
class SCExecutor {
  
  val x3655 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val newOrderTbl = new Store[SEntry3_III](3, x3655);
  val newOrderTblIdx0 = newOrderTbl.index(0, IHash, true, -1)
  val newOrderTblIdx1 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val newOrderTblIdx2 = newOrderTbl.index(2, INone, false, -1)
  val x3793 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx12345678)
  val historyTbl = new Store[SEntry8_IIIIITDS](1, x3793);
  val historyTblIdx0 = historyTbl.index(0, IHash, true, -1)
  val x3812 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val warehouseTbl = new Store[SEntry9_ISSSSSSDD](1, x3812);
  val warehouseTblIdx0 = warehouseTbl.index(0, IDirect, true, 1)
  val x3831 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val itemTbl = new Store[SEntry5_IISDS](1, x3831);
  val itemTblIdx0 = itemTbl.index(0, IDirect, true, 100000)
  val x3995 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val orderTbl = new Store[SEntry8_IIIITIIB](3, x3995);
  val orderTblIdx0 = orderTbl.index(0, IHash, true, -1)
  val orderTblIdx1 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val orderTblIdx2 = orderTbl.index(2, INone, false, -1)
  val x4022 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val districtTbl = new Store[SEntry11_IISSSSSSDDI](1, x4022);
  val districtTblIdx0 = districtTbl.index(0, IDirect, true, 10)
  val x4154 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val orderLineTbl = new Store[SEntry10_IIIIIITIDS](2, x4154);
  val orderLineTblIdx0 = orderLineTbl.index(0, IHash, true, -1)
  val orderLineTblIdx1 = orderLineTbl.index(1, IHash, false, -1)
  val x4242 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val customerTbl = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4242);
  val customerTblIdx0 = customerTbl.index(0, IDirect, true, 30000)
  val customerTblIdx1 = customerTbl.index(1, IHash, false, -1)
  val x4268 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val stockTbl = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4268);
  val stockTblIdx0 = stockTbl.index(0, IDirect, true, 100000)
  
  districtTbl.setInitialSizes(List(0))
  customerTbl.setInitialSizes(List(0,42000))
  itemTbl.setInitialSizes(List(0))
  historyTbl.setInitialSizes(List(4911566))
  orderTbl.setInitialSizes(List(4862943,41676))
  newOrderTbl.setInitialSizes(List(12601,15))
  warehouseTbl.setInitialSizes(List(0))
  stockTbl.setInitialSizes(List(0))
  orderLineTbl.setInitialSizes(List(48629600,48629600))

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4026 : SEntry10_IIIIIITIDS) = {
      var x4027: Int = 0;
      val x4028 = x4027;
      val x4029 = x4026._1;
      x4027 = (x4028.^(((((x4029.hashCode()).+(-1640531527)).+((x4028.<<(6)))).+((x4028.>>(2))))))
      val x4038 = x4027;
      val x4039 = x4026._2;
      x4027 = (x4038.^(((((x4039.hashCode()).+(-1640531527)).+((x4038.<<(6)))).+((x4038.>>(2))))))
      val x4048 = x4027;
      val x4049 = x4026._3;
      x4027 = (x4048.^(((((x4049.hashCode()).+(-1640531527)).+((x4048.<<(6)))).+((x4048.>>(2))))))
      val x4058 = x4027;
      val x4059 = x4026._4;
      x4027 = (x4058.^(((((x4059.hashCode()).+(-1640531527)).+((x4058.<<(6)))).+((x4058.>>(2))))))
      val x4068 = x4027;
      x4068
    }
    override def cmp(x4070 : SEntry10_IIIIIITIDS , x4071 : SEntry10_IIIIIITIDS) = {
      var x4072: Int = 0;
      val x4073 = x4070._1;
      val x4074 = x4071._1;
      if((x4073.==(x4074))) {
        val x4076 = x4070._2;
        val x4077 = x4071._2;
        if((x4076.==(x4077))) {
          val x4079 = x4070._3;
          val x4080 = x4071._3;
          if((x4079.==(x4080))) {
            val x4082 = x4070._4;
            val x4083 = x4071._4;
            if((x4082.==(x4083))) {
              x4072 = 0
            } else {
              x4072 = 1
            }
          } else {
            x4072 = 1
          }
        } else {
          x4072 = 1
        }
      } else {
        x4072 = 1
      }
      val x4094 = x4072;
      x4094
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3938 : SEntry8_IIIITIIB) = {
      var x3939: Int = 0;
      val x3940 = x3939;
      val x3941 = x3938._2;
      x3939 = (x3940.^(((((x3941.hashCode()).+(-1640531527)).+((x3940.<<(6)))).+((x3940.>>(2))))))
      val x3950 = x3939;
      val x3951 = x3938._3;
      x3939 = (x3950.^(((((x3951.hashCode()).+(-1640531527)).+((x3950.<<(6)))).+((x3950.>>(2))))))
      val x3960 = x3939;
      val x3961 = x3938._4;
      x3939 = (x3960.^(((((x3961.hashCode()).+(-1640531527)).+((x3960.<<(6)))).+((x3960.>>(2))))))
      val x3970 = x3939;
      x3970
    }
    override def cmp(x3972 : SEntry8_IIIITIIB , x3973 : SEntry8_IIIITIIB) = {
      var x3974: Int = 0;
      val x3975 = x3972._2;
      val x3976 = x3973._2;
      if((x3975.==(x3976))) {
        val x3978 = x3972._3;
        val x3979 = x3973._3;
        if((x3978.==(x3979))) {
          val x3981 = x3972._4;
          val x3982 = x3973._4;
          if((x3981.==(x3982))) {
            x3974 = 0
          } else {
            x3974 = 1
          }
        } else {
          x3974 = 1
        }
      } else {
        x3974 = 1
      }
      val x3991 = x3974;
      x3991
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3523 : SEntry3_III) = {
      var x3524: Int = 0;
      val x3525 = x3524;
      val x3526 = x3523._1;
      x3524 = (x3525.^(((((x3526.hashCode()).+(-1640531527)).+((x3525.<<(6)))).+((x3525.>>(2))))))
      val x3535 = x3524;
      val x3536 = x3523._2;
      x3524 = (x3535.^(((((x3536.hashCode()).+(-1640531527)).+((x3535.<<(6)))).+((x3535.>>(2))))))
      val x3545 = x3524;
      val x3546 = x3523._3;
      x3524 = (x3545.^(((((x3546.hashCode()).+(-1640531527)).+((x3545.<<(6)))).+((x3545.>>(2))))))
      val x3555 = x3524;
      x3555
    }
    override def cmp(x3557 : SEntry3_III , x3558 : SEntry3_III) = {
      var x3559: Int = 0;
      val x3560 = x3557._1;
      val x3561 = x3558._1;
      if((x3560.==(x3561))) {
        val x3563 = x3557._2;
        val x3564 = x3558._2;
        if((x3563.==(x3564))) {
          val x3566 = x3557._3;
          val x3567 = x3558._3;
          if((x3566.==(x3567))) {
            x3559 = 0
          } else {
            x3559 = 1
          }
        } else {
          x3559 = 1
        }
      } else {
        x3559 = 1
      }
      val x3576 = x3559;
      x3576
    }
  }
   object SEntry8_IIIIITDS_Idx12345678 extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3661 : SEntry8_IIIIITDS) = {
      var x3662: Int = 0;
      val x3663 = x3662;
      val x3664 = x3661._1;
      x3662 = (x3663.^(((((x3664.hashCode()).+(-1640531527)).+((x3663.<<(6)))).+((x3663.>>(2))))))
      val x3673 = x3662;
      val x3674 = x3661._2;
      x3662 = (x3673.^(((((x3674.hashCode()).+(-1640531527)).+((x3673.<<(6)))).+((x3673.>>(2))))))
      val x3683 = x3662;
      val x3684 = x3661._3;
      x3662 = (x3683.^(((((x3684.hashCode()).+(-1640531527)).+((x3683.<<(6)))).+((x3683.>>(2))))))
      val x3693 = x3662;
      val x3694 = x3661._4;
      x3662 = (x3693.^(((((x3694.hashCode()).+(-1640531527)).+((x3693.<<(6)))).+((x3693.>>(2))))))
      val x3703 = x3662;
      val x3704 = x3661._5;
      x3662 = (x3703.^(((((x3704.hashCode()).+(-1640531527)).+((x3703.<<(6)))).+((x3703.>>(2))))))
      val x3713 = x3662;
      val x3714 = x3661._6;
      x3662 = (x3713.^(((((x3714.hashCode()).+(-1640531527)).+((x3713.<<(6)))).+((x3713.>>(2))))))
      val x3723 = x3662;
      val x3724 = x3661._7;
      x3662 = (x3723.^(((((x3724.hashCode()).+(-1640531527)).+((x3723.<<(6)))).+((x3723.>>(2))))))
      val x3733 = x3662;
      val x3734 = x3661._8;
      x3662 = (x3733.^(((((x3734.hashCode()).+(-1640531527)).+((x3733.<<(6)))).+((x3733.>>(2))))))
      val x3743 = x3662;
      x3743
    }
    override def cmp(x3745 : SEntry8_IIIIITDS , x3746 : SEntry8_IIIIITDS) = {
      var x3747: Int = 0;
      val x3748 = x3745._1;
      val x3749 = x3746._1;
      if((x3748.==(x3749))) {
        val x3751 = x3745._2;
        val x3752 = x3746._2;
        if((x3751.==(x3752))) {
          val x3754 = x3745._3;
          val x3755 = x3746._3;
          if((x3754.==(x3755))) {
            val x3757 = x3745._4;
            val x3758 = x3746._4;
            if((x3757.==(x3758))) {
              val x3760 = x3745._5;
              val x3761 = x3746._5;
              if((x3760.==(x3761))) {
                val x3763 = x3745._6;
                val x3764 = x3746._6;
                if((x3763.==(x3764))) {
                  val x3766 = x3745._7;
                  val x3767 = x3746._7;
                  if((x3766.==(x3767))) {
                    val x3769 = x3745._8;
                    val x3770 = x3746._8;
                    if((x3769.==(x3770))) {
                      x3747 = 0
                    } else {
                      x3747 = 1
                    }
                  } else {
                    x3747 = 1
                  }
                } else {
                  x3747 = 1
                }
              } else {
                x3747 = 1
              }
            } else {
              x3747 = 1
            }
          } else {
            x3747 = 1
          }
        } else {
          x3747 = 1
        }
      } else {
        x3747 = 1
      }
      val x3789 = x3747;
      x3789
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4097 : SEntry10_IIIIIITIDS) = {
      var x4098: Int = 0;
      val x4099 = x4098;
      val x4100 = x4097._1;
      x4098 = (x4099.^(((((x4100.hashCode()).+(-1640531527)).+((x4099.<<(6)))).+((x4099.>>(2))))))
      val x4109 = x4098;
      val x4110 = x4097._2;
      x4098 = (x4109.^(((((x4110.hashCode()).+(-1640531527)).+((x4109.<<(6)))).+((x4109.>>(2))))))
      val x4119 = x4098;
      val x4120 = x4097._3;
      x4098 = (x4119.^(((((x4120.hashCode()).+(-1640531527)).+((x4119.<<(6)))).+((x4119.>>(2))))))
      val x4129 = x4098;
      x4129
    }
    override def cmp(x4131 : SEntry10_IIIIIITIDS , x4132 : SEntry10_IIIIIITIDS) = {
      var x4133: Int = 0;
      val x4134 = x4131._1;
      val x4135 = x4132._1;
      if((x4134.==(x4135))) {
        val x4137 = x4131._2;
        val x4138 = x4132._2;
        if((x4137.==(x4138))) {
          val x4140 = x4131._3;
          val x4141 = x4132._3;
          if((x4140.==(x4141))) {
            x4133 = 0
          } else {
            x4133 = 1
          }
        } else {
          x4133 = 1
        }
      } else {
        x4133 = 1
      }
      val x4150 = x4133;
      x4150
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3613 : SEntry3_III) = {
      var x3614: Int = 0;
      val x3615 = x3614;
      val x3616 = x3613._2;
      x3614 = (x3615.^(((((x3616.hashCode()).+(-1640531527)).+((x3615.<<(6)))).+((x3615.>>(2))))))
      val x3625 = x3614;
      val x3626 = x3613._3;
      x3614 = (x3625.^(((((x3626.hashCode()).+(-1640531527)).+((x3625.<<(6)))).+((x3625.>>(2))))))
      val x3635 = x3614;
      x3635
    }
    override def cmp(x3637 : SEntry3_III , x3638 : SEntry3_III) = {
      var x3639: Int = 0;
      val x3640 = x3637._2;
      val x3641 = x3638._2;
      if((x3640.==(x3641))) {
        val x3643 = x3637._3;
        val x3644 = x3638._3;
        if((x3643.==(x3644))) {
          x3639 = 0
        } else {
          x3639 = 1
        }
      } else {
        x3639 = 1
      }
      val x3651 = x3639;
      x3651
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4185 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4186: Int = 0;
      val x4187 = x4186;
      val x4188 = x4185._2;
      x4186 = (x4187.^(((((x4188.hashCode()).+(-1640531527)).+((x4187.<<(6)))).+((x4187.>>(2))))))
      val x4197 = x4186;
      val x4198 = x4185._3;
      x4186 = (x4197.^(((((x4198.hashCode()).+(-1640531527)).+((x4197.<<(6)))).+((x4197.>>(2))))))
      val x4207 = x4186;
      val x4208 = x4185._6;
      x4186 = (x4207.^(((((x4208.hashCode()).+(-1640531527)).+((x4207.<<(6)))).+((x4207.>>(2))))))
      val x4217 = x4186;
      x4217
    }
    override def cmp(x4219 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4220 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4221: Int = 0;
      val x4222 = x4219._2;
      val x4223 = x4220._2;
      if((x4222.==(x4223))) {
        val x4225 = x4219._3;
        val x4226 = x4220._3;
        if((x4225.==(x4226))) {
          val x4228 = x4219._6;
          val x4229 = x4220._6;
          if((x4228.==(x4229))) {
            x4221 = 0
          } else {
            x4221 = 1
          }
        } else {
          x4221 = 1
        }
      } else {
        x4221 = 1
      }
      val x4238 = x4221;
      x4238
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3838 : SEntry8_IIIITIIB) = {
      var x3839: Int = 0;
      val x3840 = x3839;
      val x3841 = x3838._1;
      x3839 = (x3840.^(((((x3841.hashCode()).+(-1640531527)).+((x3840.<<(6)))).+((x3840.>>(2))))))
      val x3850 = x3839;
      val x3851 = x3838._2;
      x3839 = (x3850.^(((((x3851.hashCode()).+(-1640531527)).+((x3850.<<(6)))).+((x3850.>>(2))))))
      val x3860 = x3839;
      val x3861 = x3838._3;
      x3839 = (x3860.^(((((x3861.hashCode()).+(-1640531527)).+((x3860.<<(6)))).+((x3860.>>(2))))))
      val x3870 = x3839;
      x3870
    }
    override def cmp(x3872 : SEntry8_IIIITIIB , x3873 : SEntry8_IIIITIIB) = {
      var x3874: Int = 0;
      val x3875 = x3872._1;
      val x3876 = x3873._1;
      if((x3875.==(x3876))) {
        val x3878 = x3872._2;
        val x3879 = x3873._2;
        if((x3878.==(x3879))) {
          val x3881 = x3872._3;
          val x3882 = x3873._3;
          if((x3881.==(x3882))) {
            x3874 = 0
          } else {
            x3874 = 1
          }
        } else {
          x3874 = 1
        }
      } else {
        x3874 = 1
      }
      val x3891 = x3874;
      x3891
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3579 : SEntry3_III) = {
      var x3580: Int = 0;
      val x3581 = x3580;
      val x3582 = x3579._2;
      x3580 = (x3581.^(((((x3582.hashCode()).+(-1640531527)).+((x3581.<<(6)))).+((x3581.>>(2))))))
      val x3591 = x3580;
      val x3592 = x3579._3;
      x3580 = (x3591.^(((((x3592.hashCode()).+(-1640531527)).+((x3591.<<(6)))).+((x3591.>>(2))))))
      val x3601 = x3580;
      x3601
    }
    override def cmp(x3603 : SEntry3_III , x3604 : SEntry3_III) = {
      val x3605 = x3603._1;
      val x3606 = x3604._1;
      (if((x3605.==(x3606))) 0 else (if((x3605.>(x3606))) 1 else -1))
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3894 : SEntry8_IIIITIIB) = {
      var x3895: Int = 0;
      val x3896 = x3895;
      val x3897 = x3894._2;
      x3895 = (x3896.^(((((x3897.hashCode()).+(-1640531527)).+((x3896.<<(6)))).+((x3896.>>(2))))))
      val x3906 = x3895;
      val x3907 = x3894._3;
      x3895 = (x3906.^(((((x3907.hashCode()).+(-1640531527)).+((x3906.<<(6)))).+((x3906.>>(2))))))
      val x3916 = x3895;
      val x3917 = x3894._4;
      x3895 = (x3916.^(((((x3917.hashCode()).+(-1640531527)).+((x3916.<<(6)))).+((x3916.>>(2))))))
      val x3926 = x3895;
      x3926
    }
    override def cmp(x3928 : SEntry8_IIIITIIB , x3929 : SEntry8_IIIITIIB) = {
      val x3930 = x3928._1;
      val x3931 = x3929._1;
      (if((x3930.==(x3931))) 0 else (if((x3930.>(x3931))) 1 else -1))
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4250 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4251: Int = 0;
      val x4252 = x4250._1;
      val x4254 = x4251;
      x4251 = ((x4254.*(100000)).+((x4252.-(1))))
      val x4258 = x4250._2;
      val x4260 = x4251;
      x4251 = ((x4260.*(1)).+((x4258.-(1))))
      val x4264 = x4251;
      x4264
    }
    override def cmp(x4247 : SEntry17_IIISSSSSSSSSSIIIS , x4248 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4162 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4163: Int = 0;
      val x4164 = x4162._1;
      val x4166 = x4163;
      x4163 = ((x4166.*(3000)).+((x4164.-(1))))
      val x4170 = x4162._2;
      val x4172 = x4163;
      x4163 = ((x4172.*(10)).+((x4170.-(1))))
      val x4176 = x4162._3;
      val x4178 = x4163;
      x4163 = ((x4178.*(1)).+((x4176.-(1))))
      val x4182 = x4163;
      x4182
    }
    override def cmp(x4159 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4160 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3819 : SEntry5_IISDS) = {
      var x3820: Int = 0;
      val x3821 = x3819._1;
      val x3823 = x3820;
      x3820 = ((x3823.*(100000)).+((x3821.-(1))))
      val x3827 = x3820;
      x3827
    }
    override def cmp(x3816 : SEntry5_IISDS , x3817 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3800 : SEntry9_ISSSSSSDD) = {
      var x3801: Int = 0;
      val x3802 = x3800._1;
      val x3804 = x3801;
      x3801 = ((x3804.*(1)).+((x3802.-(1))))
      val x3808 = x3801;
      x3808
    }
    override def cmp(x3797 : SEntry9_ISSSSSSDD , x3798 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4004 : SEntry11_IISSSSSSDDI) = {
      var x4005: Int = 0;
      val x4006 = x4004._1;
      val x4008 = x4005;
      x4005 = ((x4008.*(10)).+((x4006.-(1))))
      val x4012 = x4004._2;
      val x4014 = x4005;
      x4005 = ((x4014.*(1)).+((x4012.-(1))))
      val x4018 = x4005;
      x4018
    }
    override def cmp(x4001 : SEntry11_IISSSSSSDDI , x4002 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
  val x6862 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x7074 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x7198 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x6554 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6902 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6698 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6541 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x6742 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7107 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x7110 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x6679 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7124 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6667 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6752 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6769 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7094 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6919 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6530 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x7097 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x6550 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7100 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6857 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x6885 = SEntry8_IIIIITDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null);
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
        x6530._2_=(x27)
        x6530._3_=(x12)
        val x10786 = newOrderTblIdx1.get(x6530);
        if((x10786.!=(null))) {
          val x6534 = x10786._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x6534)
          newOrderTbl.delete(x10786)
          val x41 = x18;
          x6541._1_=(x6534)
          x6541._2_=(x41)
          x6541._3_=(x12)
          val x10799 = orderTblIdx0.get(x6541);
          val x6543 = x10799._4;
          x10799._6_=(x13)
          var x50: Double = 0.0;
          val x52 = x18;
          x6550._1_=(x6534)
          x6550._2_=(x52)
          x6550._3_=(x12)
          val x12287 = orderLineTblIdx1.sliceRes(x6550);
          if((x12287.isEmpty)) {
          } else {
            orderLineTblIdx1.sliceResMap(x6550, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
                orderLineEntry._7_=(x11)
                val x57 = x50;
                val x6594 = orderLineEntry._9;
                x50 = (x57.+(x6594))
              
              }
            }), x12287)
          }
          val x65 = x18;
          x6554._1_=(x6543)
          x6554._2_=(x65)
          x6554._3_=(x12)
          val x10821 = customerTblIdx0.get(x6554);
          val x69 = x50;
          x10821._17 +=(x69)
          x10821._20 +=(1)
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
      x6667._1_=(x85)
      x6667._2_=(x84)
      val x10888 = districtTblIdx0.get(x6667);
      val x6669 = x10888._11;
      var x95: Int = (x6669.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply2;
      while({
        val x99 = x95;
        (x99.<(x6669))
      })
      {
        val x101 = x95;
        x6679._1_=(x101)
        x6679._2_=(x85)
        x6679._3_=(x84)
        val x12333 = orderLineTblIdx1.sliceRes(x6679);
        if((x12333.isEmpty)) {
        } else {
          orderLineTblIdx1.sliceResMap(x6679, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              val x6696 = orderLineEntry._5;
              x6698._1_=(x6696)
              x6698._2_=(x84)
              val x10902 = stockTblIdx0.get(x6698);
              val x6700 = x10902._3;
              if((x6700.<(x86))) {
                val x114 = unique_ol_i_id.+=(x6696);
              } else {
              }
              ()
            }
          }), x12333)
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
      val x6739 = if((x129.>(0))) {
        val x6749 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6752._2_=(x128)
        x6752._3_=(x127)
        x6752._6_=(x131)
        val x12350 = customerTblIdx1.sliceRes(x6752);
        if((x12350.isEmpty)) {
        } else {
          customerTblIdx1.sliceResMap(x6752, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6749.append(custEntry)
              ()
            }
          }), x12350)
        }
        val x143 = x6749.size;
        var x145: Int = (x143./(2));
        val x147 = x6749.size;
        if(((x147.%(2)).==(0))) {
          val x150 = x145;
          x145 = (x150.-(1))
        } else {
        }
        val x161 = x6749.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6793 = c1._4;
            val x6794 = c2._4;
            ((StringExtra.StringCompare(x6793, x6794)).<(0))
          }
        }));
        val x162 = x145;
        val x6767 = x161.apply(x162);
      x6767
      } else {
        x6769._1_=(x130)
        x6769._2_=(x128)
        x6769._3_=(x127)
        val x10982 = customerTblIdx0.get(x6769);
      x10982
      };
      val x6740 = x6739._3;
      x6742._2_=(x128)
      x6742._3_=(x127)
      x6742._4_=(x6740)
      val x10988 = orderTblIdx1.get(x6742);
      var x181: Int = 0;
      val x6745 = x10988._1;
      x181 = x6745
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x185 : Boolean, x186 : Date, x187 : Int, x188 : Int, x189 : Int, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : String, x195 : Double) =     {
      x6857._1_=(x188)
      val x11039 = warehouseTblIdx0.get(x6857);
      x11039._9 +=(x195)
      x6862._1_=(x189)
      x6862._2_=(x188)
      val x11044 = districtTblIdx0.get(x6862);
      x11044._10 +=(x195)
      val x6867 = if((x190.>(0))) {
        val x6899 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6902._2_=(x192)
        x6902._3_=(x191)
        x6902._6_=(x194)
        val x12407 = customerTblIdx1.sliceRes(x6902);
        if((x12407.isEmpty)) {
        } else {
          customerTblIdx1.sliceResMap(x6902, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6899.append(custEntry)
              ()
            }
          }), x12407)
        }
        val x219 = x6899.size;
        var x221: Int = (x219./(2));
        val x223 = x6899.size;
        if(((x223.%(2)).==(0))) {
          val x226 = x221;
          x221 = (x226.-(1))
        } else {
        }
        val x237 = x6899.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6965 = c1._4;
            val x6966 = c2._4;
            ((StringExtra.StringCompare(x6965, x6966)).<(0))
          }
        }));
        val x238 = x221;
        val x6917 = x237.apply(x238);
      x6917
      } else {
        x6919._1_=(x193)
        x6919._2_=(x192)
        x6919._3_=(x191)
        val x11081 = customerTblIdx0.get(x6919);
      x11081
      };
      val x6868 = x6867._21;
      val x6869 = x6867._14;
      val x247 = x6869.contains("BC");
      if(x247) {
        val x6872 = x6867._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x6872,x192,x191,x189,x188,x195,x186,x6868)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x6867._17 +=(x195)
        x6867._21_=(c_new_data)
      } else {
        x6867._17 +=(x195)
      }
      val x6879 = x11039._2;
      val x6880 = x11044._3;
      var h_data = "%.10s    %.10s".format(x6879,x6880)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x6883 = x6867._1;
      x6885._1_=(x6883)
      x6885._2_=(x192)
      x6885._3_=(x191)
      x6885._4_=(x189)
      x6885._5_=(x188)
      x6885._6_=(x186)
      x6885._7_=(x195)
      x6885._8_=(h_data)
      historyTbl.unsafeInsert(x6885)
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
        x7074._1_=(x301)
        val x11190 = itemTblIdx0.get(x7074);
        if((x11190.==(null))) {
          x293 = false
        } else {
          val x307 = x285;
          val x7080 = x11190._3;
          x280.update(x307, x7080)
          val x310 = x285;
          val x7083 = x11190._4;
          x279.update(x310, x7083)
          val x313 = x285;
          val x7086 = x11190._5;
          idata.update(x313, x7086)
        }
        val x317 = x285;
        x285 = (x317.+(1))
        ()
      }
      val x321 = x293;
      if(x321) {
        x7094._1_=(x273)
        x7094._2_=(x272)
        x7094._3_=(x271)
        val x11212 = customerTblIdx0.get(x7094);
        x7097._1_=(x271)
        val x11215 = warehouseTblIdx0.get(x7097);
        x7100._1_=(x272)
        x7100._2_=(x271)
        val x11219 = districtTblIdx0.get(x7100);
        val x7102 = x11219._11;
        x11219._11 +=(1)
        x7107._1_=(x7102)
        x7107._2_=(x272)
        x7107._3_=(x271)
        x7107._4_=(x273)
        x7107._5_=(x269)
        x7107._6_=(-1)
        x7107._7_=(x274)
        x7107._8_=((x275.>(0)))
        orderTbl.unsafeInsert(x7107)
        x7110._1_=(x7102)
        x7110._2_=(x272)
        x7110._3_=(x271)
        newOrderTbl.unsafeInsert(x7110)
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
          x7124._1_=(ol_i_id)
          x7124._2_=(ol_supply_w_id)
          val x11252 = stockTblIdx0.get(x7124);
          val ol_dist_info = if((x272.==(1))) {
            val x7128 = x11252._4;
          x7128
          } else {
            val x391 = if((x272.==(2))) {
              val x7131 = x11252._5;
            x7131
            } else {
              val x390 = if((x272.==(3))) {
                val x7134 = x11252._6;
              x7134
              } else {
                val x389 = if((x272.==(4))) {
                  val x7137 = x11252._7;
                x7137
                } else {
                  val x388 = if((x272.==(5))) {
                    val x7140 = x11252._8;
                  x7140
                  } else {
                    val x387 = if((x272.==(6))) {
                      val x7143 = x11252._9;
                    x7143
                    } else {
                      val x386 = if((x272.==(7))) {
                        val x7146 = x11252._10;
                      x7146
                      } else {
                        val x385 = if((x272.==(8))) {
                          val x7149 = x11252._11;
                        x7149
                        } else {
                          val x384 = if((x272.==(9))) {
                            val x7152 = x11252._12;
                          x7152
                          } else {
                            val x7153 = x11252._13;
                          x7153
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
          val x7154 = x11252._3;
          val x395 = x285;
          x281.update(x395, x7154)
          val x397 = x285;
          val x398 = idata.apply(x397);
          val x399 = x398.contains("original");
          if((x399.&&({
            val x7161 = x11252._17;
            val x401 = x7161.contains("original");
            x401
          }))) {
            val x403 = x285;
            x282.update(x403, "B")
          } else {
            val x405 = x285;
            x282.update(x405, "G")
          }
          x11252._3_=((x7154.-(ol_quantity)))
          if((x7154.<=(ol_quantity))) {
            x11252._3 +=(91)
          } else {
          }
          var x414: Int = 0;
          if((ol_supply_w_id.!=(x271))) {
            x414 = 1
          } else {
          }
          val x7178 = x11212._16;
          val x7179 = x11215._8;
          val x7180 = x11219._9;
          val x427 = x285;
          val x428 = x279.apply(x427);
          val ol_amount = (((ol_quantity.toDouble).*(x428)).*(((1.0.+(x7179)).+(x7180)))).*((1.0.-(x7178)));
          val x436 = x285;
          x283.update(x436, ol_amount)
          val x438 = x346;
          x346 = (x438.+(ol_amount))
          val x441 = x285;
          x7198._1_=(x7102)
          x7198._2_=(x272)
          x7198._3_=(x271)
          x7198._4_=((x441.+(1)))
          x7198._5_=(ol_i_id)
          x7198._6_=(ol_supply_w_id)
          x7198._8_=(ol_quantity)
          x7198._9_=(ol_amount)
          x7198._10_=(ol_dist_info)
          orderLineTbl.unsafeInsert(x7198)
          val x446 = x285;
          x285 = (x446.+(1))
          ()
        }
      } else {
      }
      1
    }
  }

}
