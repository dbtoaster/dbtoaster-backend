
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
  val warehouseTblArrayLengths = List(0)
  val itemTblArrayLengths = List(0)
  val districtTblArrayLengths = List(0)
  val customerTblArrayLengths = List(0, 65536)
  val orderTblArrayLengths = List(1048576, 65536)
  val newOrderTblArrayLengths = List(16384, 32)
  val orderLineTblArrayLengths = List(8388608, 8388608)
  val stockTblArrayLengths = List(0)
  val historyTblArrayLengths = List(1048576)

          
  val x3664 = Array[EntryIdx[SEntry3_III]](SEntry3_III_Idx123, SEntry3_III_Idx23_Ordering, SEntry3_III_Idx23)
  val newOrderTbl = new Store[SEntry3_III](3, x3664);
  val newOrderTblIdx0 = newOrderTbl.index(0, IHash, true, -1)
  val newOrderTblIdx1 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val newOrderTblIdx2 = newOrderTbl.index(2, INone, false, -1)
  val x3802 = Array[EntryIdx[SEntry8_IIIIITDS]](SEntry8_IIIIITDS_Idx12345678)
  val historyTbl = new Store[SEntry8_IIIIITDS](1, x3802);
  val historyTblIdx0 = historyTbl.index(0, IHash, true, -1)
  val x3821 = Array[EntryIdx[SEntry9_ISSSSSSDD]](SEntry9_ISSSSSSDD_Idx1f1t2)
  val warehouseTbl = new Store[SEntry9_ISSSSSSDD](1, x3821);
  val warehouseTblIdx0 = warehouseTbl.index(0, IDirect, true, 1)
  val x3840 = Array[EntryIdx[SEntry5_IISDS]](SEntry5_IISDS_Idx1f1t100001)
  val itemTbl = new Store[SEntry5_IISDS](1, x3840);
  val itemTblIdx0 = itemTbl.index(0, IDirect, true, 100000)
  val x4004 = Array[EntryIdx[SEntry8_IIIITIIB]](SEntry8_IIIITIIB_Idx123, SEntry8_IIIITIIB_Idx234_Ordering, SEntry8_IIIITIIB_Idx234)
  val orderTbl = new Store[SEntry8_IIIITIIB](3, x4004);
  val orderTblIdx0 = orderTbl.index(0, IHash, true, -1)
  val orderTblIdx1 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val orderTblIdx2 = orderTbl.index(2, INone, false, -1)
  val x4031 = Array[EntryIdx[SEntry11_IISSSSSSDDI]](SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2)
  val districtTbl = new Store[SEntry11_IISSSSSSDDI](1, x4031);
  val districtTblIdx0 = districtTbl.index(0, IDirect, true, 10)
  val x4163 = Array[EntryIdx[SEntry10_IIIIIITIDS]](SEntry10_IIIIIITIDS_Idx1234, SEntry10_IIIIIITIDS_Idx123)
  val orderLineTbl = new Store[SEntry10_IIIIIITIDS](2, x4163);
  val orderLineTblIdx0 = orderLineTbl.index(0, IHash, true, -1)
  val orderLineTblIdx1 = orderLineTbl.index(1, IHash, false, -1)
  val x4251 = Array[EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS]](SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236)
  val customerTbl = new Store[SEntry21_IIISSSSSSSSSTSDDDDIIS](2, x4251);
  val customerTblIdx0 = customerTbl.index(0, IDirect, true, 30000)
  val customerTblIdx1 = customerTbl.index(1, IHash, false, -1)
  val x4277 = Array[EntryIdx[SEntry17_IIISSSSSSSSSSIIIS]](SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2)
  val stockTbl = new Store[SEntry17_IIISSSSSSSSSSIIIS](1, x4277);
  val stockTblIdx0 = stockTbl.index(0, IDirect, true, 100000)
  

  warehouseTbl.setInitialSizes(warehouseTblArrayLengths)
  historyTbl.setInitialSizes(historyTblArrayLengths)
  districtTbl.setInitialSizes(districtTblArrayLengths)
  customerTbl.setInitialSizes(customerTblArrayLengths)
  orderTbl.setInitialSizes(orderLineTblArrayLengths)
  newOrderTbl.setInitialSizes(newOrderTblArrayLengths)
  orderLineTbl.setInitialSizes(orderLineTblArrayLengths)
  stockTbl.setInitialSizes(stockTblArrayLengths)
  historyTbl.setInitialSizes(historyTblArrayLengths)

       
  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   object SEntry10_IIIIIITIDS_Idx1234 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4035 : SEntry10_IIIIIITIDS) = {
      var x4036: Int = 0;
      val x4037 = x4036;
      val x4038 = x4035._1;
      x4036 = (x4037.^(((((x4038.hashCode()).+(-1640531527)).+((x4037.<<(6)))).+((x4037.>>(2))))))
      val x4047 = x4036;
      val x4048 = x4035._2;
      x4036 = (x4047.^(((((x4048.hashCode()).+(-1640531527)).+((x4047.<<(6)))).+((x4047.>>(2))))))
      val x4057 = x4036;
      val x4058 = x4035._3;
      x4036 = (x4057.^(((((x4058.hashCode()).+(-1640531527)).+((x4057.<<(6)))).+((x4057.>>(2))))))
      val x4067 = x4036;
      val x4068 = x4035._4;
      x4036 = (x4067.^(((((x4068.hashCode()).+(-1640531527)).+((x4067.<<(6)))).+((x4067.>>(2))))))
      val x4077 = x4036;
      x4077
    }
    override def cmp(x4079 : SEntry10_IIIIIITIDS , x4080 : SEntry10_IIIIIITIDS) = {
      var x4081: Int = 0;
      val x4082 = x4079._1;
      val x4083 = x4080._1;
      if((x4082.==(x4083))) {
        val x4085 = x4079._2;
        val x4086 = x4080._2;
        if((x4085.==(x4086))) {
          val x4088 = x4079._3;
          val x4089 = x4080._3;
          if((x4088.==(x4089))) {
            val x4091 = x4079._4;
            val x4092 = x4080._4;
            if((x4091.==(x4092))) {
              x4081 = 0
            } else {
              x4081 = 1
            }
          } else {
            x4081 = 1
          }
        } else {
          x4081 = 1
        }
      } else {
        x4081 = 1
      }
      val x4103 = x4081;
      x4103
    }
  }
   object SEntry8_IIIITIIB_Idx234 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3947 : SEntry8_IIIITIIB) = {
      var x3948: Int = 0;
      val x3949 = x3948;
      val x3950 = x3947._2;
      x3948 = (x3949.^(((((x3950.hashCode()).+(-1640531527)).+((x3949.<<(6)))).+((x3949.>>(2))))))
      val x3959 = x3948;
      val x3960 = x3947._3;
      x3948 = (x3959.^(((((x3960.hashCode()).+(-1640531527)).+((x3959.<<(6)))).+((x3959.>>(2))))))
      val x3969 = x3948;
      val x3970 = x3947._4;
      x3948 = (x3969.^(((((x3970.hashCode()).+(-1640531527)).+((x3969.<<(6)))).+((x3969.>>(2))))))
      val x3979 = x3948;
      x3979
    }
    override def cmp(x3981 : SEntry8_IIIITIIB , x3982 : SEntry8_IIIITIIB) = {
      var x3983: Int = 0;
      val x3984 = x3981._2;
      val x3985 = x3982._2;
      if((x3984.==(x3985))) {
        val x3987 = x3981._3;
        val x3988 = x3982._3;
        if((x3987.==(x3988))) {
          val x3990 = x3981._4;
          val x3991 = x3982._4;
          if((x3990.==(x3991))) {
            x3983 = 0
          } else {
            x3983 = 1
          }
        } else {
          x3983 = 1
        }
      } else {
        x3983 = 1
      }
      val x4000 = x3983;
      x4000
    }
  }
   object SEntry3_III_Idx123 extends EntryIdx[SEntry3_III] {
    override def hash(x3532 : SEntry3_III) = {
      var x3533: Int = 0;
      val x3534 = x3533;
      val x3535 = x3532._1;
      x3533 = (x3534.^(((((x3535.hashCode()).+(-1640531527)).+((x3534.<<(6)))).+((x3534.>>(2))))))
      val x3544 = x3533;
      val x3545 = x3532._2;
      x3533 = (x3544.^(((((x3545.hashCode()).+(-1640531527)).+((x3544.<<(6)))).+((x3544.>>(2))))))
      val x3554 = x3533;
      val x3555 = x3532._3;
      x3533 = (x3554.^(((((x3555.hashCode()).+(-1640531527)).+((x3554.<<(6)))).+((x3554.>>(2))))))
      val x3564 = x3533;
      x3564
    }
    override def cmp(x3566 : SEntry3_III , x3567 : SEntry3_III) = {
      var x3568: Int = 0;
      val x3569 = x3566._1;
      val x3570 = x3567._1;
      if((x3569.==(x3570))) {
        val x3572 = x3566._2;
        val x3573 = x3567._2;
        if((x3572.==(x3573))) {
          val x3575 = x3566._3;
          val x3576 = x3567._3;
          if((x3575.==(x3576))) {
            x3568 = 0
          } else {
            x3568 = 1
          }
        } else {
          x3568 = 1
        }
      } else {
        x3568 = 1
      }
      val x3585 = x3568;
      x3585
    }
  }
   object SEntry8_IIIIITDS_Idx12345678 extends EntryIdx[SEntry8_IIIIITDS] {
    override def hash(x3670 : SEntry8_IIIIITDS) = {
      var x3671: Int = 0;
      val x3672 = x3671;
      val x3673 = x3670._1;
      x3671 = (x3672.^(((((x3673.hashCode()).+(-1640531527)).+((x3672.<<(6)))).+((x3672.>>(2))))))
      val x3682 = x3671;
      val x3683 = x3670._2;
      x3671 = (x3682.^(((((x3683.hashCode()).+(-1640531527)).+((x3682.<<(6)))).+((x3682.>>(2))))))
      val x3692 = x3671;
      val x3693 = x3670._3;
      x3671 = (x3692.^(((((x3693.hashCode()).+(-1640531527)).+((x3692.<<(6)))).+((x3692.>>(2))))))
      val x3702 = x3671;
      val x3703 = x3670._4;
      x3671 = (x3702.^(((((x3703.hashCode()).+(-1640531527)).+((x3702.<<(6)))).+((x3702.>>(2))))))
      val x3712 = x3671;
      val x3713 = x3670._5;
      x3671 = (x3712.^(((((x3713.hashCode()).+(-1640531527)).+((x3712.<<(6)))).+((x3712.>>(2))))))
      val x3722 = x3671;
      val x3723 = x3670._6;
      x3671 = (x3722.^(((((x3723.hashCode()).+(-1640531527)).+((x3722.<<(6)))).+((x3722.>>(2))))))
      val x3732 = x3671;
      val x3733 = x3670._7;
      x3671 = (x3732.^(((((x3733.hashCode()).+(-1640531527)).+((x3732.<<(6)))).+((x3732.>>(2))))))
      val x3742 = x3671;
      val x3743 = x3670._8;
      x3671 = (x3742.^(((((x3743.hashCode()).+(-1640531527)).+((x3742.<<(6)))).+((x3742.>>(2))))))
      val x3752 = x3671;
      x3752
    }
    override def cmp(x3754 : SEntry8_IIIIITDS , x3755 : SEntry8_IIIIITDS) = {
      var x3756: Int = 0;
      val x3757 = x3754._1;
      val x3758 = x3755._1;
      if((x3757.==(x3758))) {
        val x3760 = x3754._2;
        val x3761 = x3755._2;
        if((x3760.==(x3761))) {
          val x3763 = x3754._3;
          val x3764 = x3755._3;
          if((x3763.==(x3764))) {
            val x3766 = x3754._4;
            val x3767 = x3755._4;
            if((x3766.==(x3767))) {
              val x3769 = x3754._5;
              val x3770 = x3755._5;
              if((x3769.==(x3770))) {
                val x3772 = x3754._6;
                val x3773 = x3755._6;
                if((x3772.==(x3773))) {
                  val x3775 = x3754._7;
                  val x3776 = x3755._7;
                  if((x3775.==(x3776))) {
                    val x3778 = x3754._8;
                    val x3779 = x3755._8;
                    if((x3778.==(x3779))) {
                      x3756 = 0
                    } else {
                      x3756 = 1
                    }
                  } else {
                    x3756 = 1
                  }
                } else {
                  x3756 = 1
                }
              } else {
                x3756 = 1
              }
            } else {
              x3756 = 1
            }
          } else {
            x3756 = 1
          }
        } else {
          x3756 = 1
        }
      } else {
        x3756 = 1
      }
      val x3798 = x3756;
      x3798
    }
  }
   object SEntry10_IIIIIITIDS_Idx123 extends EntryIdx[SEntry10_IIIIIITIDS] {
    override def hash(x4106 : SEntry10_IIIIIITIDS) = {
      var x4107: Int = 0;
      val x4108 = x4107;
      val x4109 = x4106._1;
      x4107 = (x4108.^(((((x4109.hashCode()).+(-1640531527)).+((x4108.<<(6)))).+((x4108.>>(2))))))
      val x4118 = x4107;
      val x4119 = x4106._2;
      x4107 = (x4118.^(((((x4119.hashCode()).+(-1640531527)).+((x4118.<<(6)))).+((x4118.>>(2))))))
      val x4128 = x4107;
      val x4129 = x4106._3;
      x4107 = (x4128.^(((((x4129.hashCode()).+(-1640531527)).+((x4128.<<(6)))).+((x4128.>>(2))))))
      val x4138 = x4107;
      x4138
    }
    override def cmp(x4140 : SEntry10_IIIIIITIDS , x4141 : SEntry10_IIIIIITIDS) = {
      var x4142: Int = 0;
      val x4143 = x4140._1;
      val x4144 = x4141._1;
      if((x4143.==(x4144))) {
        val x4146 = x4140._2;
        val x4147 = x4141._2;
        if((x4146.==(x4147))) {
          val x4149 = x4140._3;
          val x4150 = x4141._3;
          if((x4149.==(x4150))) {
            x4142 = 0
          } else {
            x4142 = 1
          }
        } else {
          x4142 = 1
        }
      } else {
        x4142 = 1
      }
      val x4159 = x4142;
      x4159
    }
  }
   object SEntry3_III_Idx23 extends EntryIdx[SEntry3_III] {
    override def hash(x3622 : SEntry3_III) = {
      var x3623: Int = 0;
      val x3624 = x3623;
      val x3625 = x3622._2;
      x3623 = (x3624.^(((((x3625.hashCode()).+(-1640531527)).+((x3624.<<(6)))).+((x3624.>>(2))))))
      val x3634 = x3623;
      val x3635 = x3622._3;
      x3623 = (x3634.^(((((x3635.hashCode()).+(-1640531527)).+((x3634.<<(6)))).+((x3634.>>(2))))))
      val x3644 = x3623;
      x3644
    }
    override def cmp(x3646 : SEntry3_III , x3647 : SEntry3_III) = {
      var x3648: Int = 0;
      val x3649 = x3646._2;
      val x3650 = x3647._2;
      if((x3649.==(x3650))) {
        val x3652 = x3646._3;
        val x3653 = x3647._3;
        if((x3652.==(x3653))) {
          x3648 = 0
        } else {
          x3648 = 1
        }
      } else {
        x3648 = 1
      }
      val x3660 = x3648;
      x3660
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4194 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4195: Int = 0;
      val x4196 = x4195;
      val x4197 = x4194._2;
      x4195 = (x4196.^(((((x4197.hashCode()).+(-1640531527)).+((x4196.<<(6)))).+((x4196.>>(2))))))
      val x4206 = x4195;
      val x4207 = x4194._3;
      x4195 = (x4206.^(((((x4207.hashCode()).+(-1640531527)).+((x4206.<<(6)))).+((x4206.>>(2))))))
      val x4216 = x4195;
      val x4217 = x4194._6;
      x4195 = (x4216.^(((((x4217.hashCode()).+(-1640531527)).+((x4216.<<(6)))).+((x4216.>>(2))))))
      val x4226 = x4195;
      x4226
    }
    override def cmp(x4228 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4229 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4230: Int = 0;
      val x4231 = x4228._2;
      val x4232 = x4229._2;
      if((x4231.==(x4232))) {
        val x4234 = x4228._3;
        val x4235 = x4229._3;
        if((x4234.==(x4235))) {
          val x4237 = x4228._6;
          val x4238 = x4229._6;
          if((x4237.==(x4238))) {
            x4230 = 0
          } else {
            x4230 = 1
          }
        } else {
          x4230 = 1
        }
      } else {
        x4230 = 1
      }
      val x4247 = x4230;
      x4247
    }
  }
   object SEntry8_IIIITIIB_Idx123 extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3847 : SEntry8_IIIITIIB) = {
      var x3848: Int = 0;
      val x3849 = x3848;
      val x3850 = x3847._1;
      x3848 = (x3849.^(((((x3850.hashCode()).+(-1640531527)).+((x3849.<<(6)))).+((x3849.>>(2))))))
      val x3859 = x3848;
      val x3860 = x3847._2;
      x3848 = (x3859.^(((((x3860.hashCode()).+(-1640531527)).+((x3859.<<(6)))).+((x3859.>>(2))))))
      val x3869 = x3848;
      val x3870 = x3847._3;
      x3848 = (x3869.^(((((x3870.hashCode()).+(-1640531527)).+((x3869.<<(6)))).+((x3869.>>(2))))))
      val x3879 = x3848;
      x3879
    }
    override def cmp(x3881 : SEntry8_IIIITIIB , x3882 : SEntry8_IIIITIIB) = {
      var x3883: Int = 0;
      val x3884 = x3881._1;
      val x3885 = x3882._1;
      if((x3884.==(x3885))) {
        val x3887 = x3881._2;
        val x3888 = x3882._2;
        if((x3887.==(x3888))) {
          val x3890 = x3881._3;
          val x3891 = x3882._3;
          if((x3890.==(x3891))) {
            x3883 = 0
          } else {
            x3883 = 1
          }
        } else {
          x3883 = 1
        }
      } else {
        x3883 = 1
      }
      val x3900 = x3883;
      x3900
    }
  }
   object SEntry3_III_Idx23_Ordering extends EntryIdx[SEntry3_III] {
    override def hash(x3588 : SEntry3_III) = {
      var x3589: Int = 0;
      val x3590 = x3589;
      val x3591 = x3588._2;
      x3589 = (x3590.^(((((x3591.hashCode()).+(-1640531527)).+((x3590.<<(6)))).+((x3590.>>(2))))))
      val x3600 = x3589;
      val x3601 = x3588._3;
      x3589 = (x3600.^(((((x3601.hashCode()).+(-1640531527)).+((x3600.<<(6)))).+((x3600.>>(2))))))
      val x3610 = x3589;
      x3610
    }
    override def cmp(x3612 : SEntry3_III , x3613 : SEntry3_III) = {
      val x3614 = x3612._1;
      val x3615 = x3613._1;
      (if((x3614.==(x3615))) 0 else (if((x3614.>(x3615))) 1 else -1))
    }
  }
   object SEntry8_IIIITIIB_Idx234_Ordering extends EntryIdx[SEntry8_IIIITIIB] {
    override def hash(x3903 : SEntry8_IIIITIIB) = {
      var x3904: Int = 0;
      val x3905 = x3904;
      val x3906 = x3903._2;
      x3904 = (x3905.^(((((x3906.hashCode()).+(-1640531527)).+((x3905.<<(6)))).+((x3905.>>(2))))))
      val x3915 = x3904;
      val x3916 = x3903._3;
      x3904 = (x3915.^(((((x3916.hashCode()).+(-1640531527)).+((x3915.<<(6)))).+((x3915.>>(2))))))
      val x3925 = x3904;
      val x3926 = x3903._4;
      x3904 = (x3925.^(((((x3926.hashCode()).+(-1640531527)).+((x3925.<<(6)))).+((x3925.>>(2))))))
      val x3935 = x3904;
      x3935
    }
    override def cmp(x3937 : SEntry8_IIIITIIB , x3938 : SEntry8_IIIITIIB) = {
      val x3939 = x3937._1;
      val x3940 = x3938._1;
      (if((x3939.==(x3940))) 0 else (if((x3939.>(x3940))) 1 else -1))
    }
  }
   object SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 extends EntryIdx[SEntry17_IIISSSSSSSSSSIIIS] {
    override def hash(x4259 : SEntry17_IIISSSSSSSSSSIIIS) = {
      var x4260: Int = 0;
      val x4261 = x4259._1;
      val x4263 = x4260;
      x4260 = ((x4263.*(100000)).+((x4261.-(1))))
      val x4267 = x4259._2;
      val x4269 = x4260;
      x4260 = ((x4269.*(1)).+((x4267.-(1))))
      val x4273 = x4260;
      x4273
    }
    override def cmp(x4256 : SEntry17_IIISSSSSSSSSSIIIS , x4257 : SEntry17_IIISSSSSSSSSSIIIS) = {
      0
    }
  }
   object SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 extends EntryIdx[SEntry21_IIISSSSSSSSSTSDDDDIIS] {
    override def hash(x4171 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      var x4172: Int = 0;
      val x4173 = x4171._1;
      val x4175 = x4172;
      x4172 = ((x4175.*(3000)).+((x4173.-(1))))
      val x4179 = x4171._2;
      val x4181 = x4172;
      x4172 = ((x4181.*(10)).+((x4179.-(1))))
      val x4185 = x4171._3;
      val x4187 = x4172;
      x4172 = ((x4187.*(1)).+((x4185.-(1))))
      val x4191 = x4172;
      x4191
    }
    override def cmp(x4168 : SEntry21_IIISSSSSSSSSTSDDDDIIS , x4169 : SEntry21_IIISSSSSSSSSTSDDDDIIS) = {
      0
    }
  }
   object SEntry5_IISDS_Idx1f1t100001 extends EntryIdx[SEntry5_IISDS] {
    override def hash(x3828 : SEntry5_IISDS) = {
      var x3829: Int = 0;
      val x3830 = x3828._1;
      val x3832 = x3829;
      x3829 = ((x3832.*(100000)).+((x3830.-(1))))
      val x3836 = x3829;
      x3836
    }
    override def cmp(x3825 : SEntry5_IISDS , x3826 : SEntry5_IISDS) = {
      0
    }
  }
   object SEntry9_ISSSSSSDD_Idx1f1t2 extends EntryIdx[SEntry9_ISSSSSSDD] {
    override def hash(x3809 : SEntry9_ISSSSSSDD) = {
      var x3810: Int = 0;
      val x3811 = x3809._1;
      val x3813 = x3810;
      x3810 = ((x3813.*(1)).+((x3811.-(1))))
      val x3817 = x3810;
      x3817
    }
    override def cmp(x3806 : SEntry9_ISSSSSSDD , x3807 : SEntry9_ISSSSSSDD) = {
      0
    }
  }
   object SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 extends EntryIdx[SEntry11_IISSSSSSDDI] {
    override def hash(x4013 : SEntry11_IISSSSSSDDI) = {
      var x4014: Int = 0;
      val x4015 = x4013._1;
      val x4017 = x4014;
      x4014 = ((x4017.*(10)).+((x4015.-(1))))
      val x4021 = x4013._2;
      val x4023 = x4014;
      x4014 = ((x4023.*(1)).+((x4021.-(1))))
      val x4027 = x4014;
      x4027
    }
    override def cmp(x4010 : SEntry11_IISSSSSSDDI , x4011 : SEntry11_IISSSSSSDDI) = {
      0
    }
  }
  val x6781 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7106 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7136 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6869 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x6874 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6676 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x6709 = SEntry17_IIISSSSSSSSSSIIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, -2147483648, -2147483648, -2147483648, null);
  val x6914 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x7122 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x7112 = SEntry11_IISSSSSSDDI(-2147483648, -2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648);
  val x7086 = SEntry5_IISDS(-2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x6897 = SEntry8_IIIIITDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -1.7976931348623157E308, null);
  val x6689 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7210 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x6931 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6539 = SEntry3_III(-2147483648, -2147483648, -2147483648);
  val x6559 = SEntry10_IIIIIITIDS(-2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -1.7976931348623157E308, null);
  val x7109 = SEntry9_ISSSSSSDD(-2147483648, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308);
  val x7119 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x6764 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6563 = SEntry21_IIISSSSSSSSSTSDDDDIIS(-2147483648, -2147483648, -2147483648, null, null, null, null, null, null, null, null, null, null, null, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -1.7976931348623157E308, -2147483648, -2147483648, null);
  val x6550 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
  val x6754 = SEntry8_IIIITIIB(-2147483648, -2147483648, -2147483648, -2147483648, null, -2147483648, -2147483648, false);
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
        x6539._2_=(x27)
        x6539._3_=(x12)
        val x10801 = newOrderTblIdx1.get(x6539);
        if((x10801.!=(null))) {
          val x6543 = x10801._1;
          val x36 = x18;
          orderIDs.update((x36.-(1)), x6543)
          newOrderTbl.delete(x10801)
          val x41 = x18;
          x6550._1_=(x6543)
          x6550._2_=(x41)
          x6550._3_=(x12)
          val x10814 = orderTblIdx0.get(x6550);
          val x6552 = x10814._4;
          x10814._6_=(x13)
          var x50: Double = 0.0;
          val x52 = x18;
          x6559._1_=(x6543)
          x6559._2_=(x52)
          x6559._3_=(x12)
          val x12304 = orderLineTblIdx1.sliceRes(x6559);
          if((x12304.isEmpty)) {
          } else {
            orderLineTblIdx1.sliceResMap(x6559, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
                orderLineEntry._7_=(x11)
                val x57 = x50;
                val x6603 = orderLineEntry._9;
                x50 = (x57.+(x6603))
              
              }
            }), x12304)
          }
          val x65 = x18;
          x6563._1_=(x6552)
          x6563._2_=(x65)
          x6563._3_=(x12)
          val x10836 = customerTblIdx0.get(x6563);
          val x69 = x50;
          x10836._17 +=(x69)
          x10836._20 +=(1)
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
      x6676._1_=(x85)
      x6676._2_=(x84)
      val x10903 = districtTblIdx0.get(x6676);
      val x6678 = x10903._11;
      var x95: Int = (x6678.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply1;
      while({
        val x100 = x95;
        (x100.<(x6678))
      })
      {
        val x102 = x95;
        x6689._1_=(x102)
        x6689._2_=(x85)
        x6689._3_=(x84)
        val x12351 = orderLineTblIdx1.sliceRes(x6689);
        if((x12351.isEmpty)) {
        } else {
          orderLineTblIdx1.sliceResMap(x6689, ({ orderLineEntry: SEntry10_IIIIIITIDS => {
              val x6707 = orderLineEntry._5;
              x6709._1_=(x6707)
              x6709._2_=(x84)
              val x10918 = stockTblIdx0.get(x6709);
              val x6711 = x10918._3;
              if((x6711.<(x86))) {
                val x115 = unique_ol_i_id.+=(x6707);
              } else {
              }
              ()
            }
          }), x12351)
        }
        val x119 = x95;
        x95 = (x119.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x125 : Boolean, x126 : Date, x127 : Int, x128 : Int, x129 : Int, x130 : Int, x131 : Int, x132 : String) =     {
      val x6751 = if((x130.>(0))) {
        val x6761 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6764._2_=(x129)
        x6764._3_=(x128)
        x6764._6_=(x132)
        val x12368 = customerTblIdx1.sliceRes(x6764);
        if((x12368.isEmpty)) {
        } else {
          customerTblIdx1.sliceResMap(x6764, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6761.append(custEntry)
              ()
            }
          }), x12368)
        }
        val x144 = x6761.size;
        var x146: Int = (x144./(2));
        val x148 = x6761.size;
        if(((x148.%(2)).==(0))) {
          val x151 = x146;
          x146 = (x151.-(1))
        } else {
        }
        val x162 = x6761.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6805 = c1._4;
            val x6806 = c2._4;
            ((StringExtra.StringCompare(x6805, x6806)).<(0))
          }
        }));
        val x163 = x146;
        val x6779 = x162.apply(x163);
      x6779
      } else {
        x6781._1_=(x131)
        x6781._2_=(x129)
        x6781._3_=(x128)
        val x10999 = customerTblIdx0.get(x6781);
      x10999
      };
      val x6752 = x6751._3;
      x6754._2_=(x129)
      x6754._3_=(x128)
      x6754._4_=(x6752)
      val x11005 = orderTblIdx1.get(x6754);
      var x182: Int = 0;
      val x6757 = x11005._1;
      x182 = x6757
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x186 : Boolean, x187 : Date, x188 : Int, x189 : Int, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : Int, x195 : String, x196 : Double) =     {
      x6869._1_=(x189)
      val x11056 = warehouseTblIdx0.get(x6869);
      x11056._9 +=(x196)
      x6874._1_=(x190)
      x6874._2_=(x189)
      val x11061 = districtTblIdx0.get(x6874);
      x11061._10 +=(x196)
      val x6879 = if((x191.>(0))) {
        val x6911 = new ArrayBuffer[SEntry21_IIISSSSSSSSSTSDDDDIIS]();
        x6914._2_=(x193)
        x6914._3_=(x192)
        x6914._6_=(x195)
        val x12425 = customerTblIdx1.sliceRes(x6914);
        if((x12425.isEmpty)) {
        } else {
          customerTblIdx1.sliceResMap(x6914, ({ custEntry: SEntry21_IIISSSSSSSSSTSDDDDIIS => {
              x6911.append(custEntry)
              ()
            }
          }), x12425)
        }
        val x220 = x6911.size;
        var x222: Int = (x220./(2));
        val x224 = x6911.size;
        if(((x224.%(2)).==(0))) {
          val x227 = x222;
          x222 = (x227.-(1))
        } else {
        }
        val x238 = x6911.sortWith(({ (c1: SEntry21_IIISSSSSSSSSTSDDDDIIS, c2: SEntry21_IIISSSSSSSSSTSDDDDIIS) => {
            val x6977 = c1._4;
            val x6978 = c2._4;
            ((StringExtra.StringCompare(x6977, x6978)).<(0))
          }
        }));
        val x239 = x222;
        val x6929 = x238.apply(x239);
      x6929
      } else {
        x6931._1_=(x194)
        x6931._2_=(x193)
        x6931._3_=(x192)
        val x11098 = customerTblIdx0.get(x6931);
      x11098
      };
      val x6880 = x6879._21;
      val x6881 = x6879._14;
      val x248 = x6881.contains("BC");
      if(x248) {
        val x6884 = x6879._1;
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x6884,x193,x192,x190,x189,x196,x187,x6880)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        x6879._17 +=(x196)
        x6879._21_=(c_new_data)
      } else {
        x6879._17 +=(x196)
      }
      val x6891 = x11056._2;
      val x6892 = x11061._3;
      var h_data = "%.10s    %.10s".format(x6891,x6892)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x6895 = x6879._1;
      x6897._1_=(x6895)
      x6897._2_=(x193)
      x6897._3_=(x192)
      x6897._4_=(x190)
      x6897._5_=(x189)
      x6897._6_=(x187)
      x6897._7_=(x196)
      x6897._8_=(h_data)
      historyTbl.unsafeInsert(x6897)
      1
    }
  }
  class NewOrderTx(newOrderTbl : Store[SEntry3_III], historyTbl : Store[SEntry8_IIIIITDS], warehouseTbl : Store[SEntry9_ISSSSSSDD], itemTbl : Store[SEntry5_IISDS], orderTbl : Store[SEntry8_IIIITIIB], districtTbl : Store[SEntry11_IISSSSSSDDI], orderLineTbl : Store[SEntry10_IIIIIITIDS], customerTbl : Store[SEntry21_IIISSSSSSSSSTSDDDDIIS], stockTbl : Store[SEntry17_IIISSSSSSSSSSIIIS]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x269 : Boolean, x270 : Date, x271 : Int, x272 : Int, x273 : Int, x274 : Int, x275 : Int, x276 : Int, x277 : Array[Int], x278 : Array[Int], x279 : Array[Int], x280 : Array[Double], x281 : Array[String], x282 : Array[Int], x283 : Array[String], x284 : Array[Double]) =     {
      var x286: Int = 0;
      var x289: Int = 0;
      val idata = new Array[String](x275);
      var x294: Boolean = true;
      while({
        val x296 = x286;
        ((x296.<(x275)).&&({
          val x298 = x294;
          x298
        }))
      })
      {
        val x301 = x286;
        val x302 = x277.apply(x301);
        x7086._1_=(x302)
        val x11207 = itemTblIdx0.get(x7086);
        if((x11207.==(null))) {
          x294 = false
        } else {
          val x308 = x286;
          val x7092 = x11207._3;
          x281.update(x308, x7092)
          val x311 = x286;
          val x7095 = x11207._4;
          x280.update(x311, x7095)
          val x314 = x286;
          val x7098 = x11207._5;
          idata.update(x314, x7098)
        }
        val x318 = x286;
        x286 = (x318.+(1))
        ()
      }
      val x322 = x294;
      if(x322) {
        x7106._1_=(x274)
        x7106._2_=(x273)
        x7106._3_=(x272)
        val x11229 = customerTblIdx0.get(x7106);
        x7109._1_=(x272)
        val x11232 = warehouseTblIdx0.get(x7109);
        x7112._1_=(x273)
        x7112._2_=(x272)
        val x11236 = districtTblIdx0.get(x7112);
        val x7114 = x11236._11;
        x11236._11 +=(1)
        x7119._1_=(x7114)
        x7119._2_=(x273)
        x7119._3_=(x272)
        x7119._4_=(x274)
        x7119._5_=(x270)
        x7119._6_=(-1)
        x7119._7_=(x275)
        x7119._8_=((x276.>(0)))
        orderTbl.unsafeInsert(x7119)
        x7122._1_=(x7114)
        x7122._2_=(x273)
        x7122._3_=(x272)
        newOrderTbl.unsafeInsert(x7122)
        var x347: Double = 0.0;
        x286 = 0
        while({
          val x350 = x286;
          (x350.<(x275))
        })
        {
          val x353 = x286;
          val ol_supply_w_id = x278.apply(x353);
          val x356 = x286;
          val ol_i_id = x277.apply(x356);
          val x359 = x286;
          val ol_quantity = x279.apply(x359);
          x7136._1_=(ol_i_id)
          x7136._2_=(ol_supply_w_id)
          val x11269 = stockTblIdx0.get(x7136);
          val ol_dist_info = if((x273.==(1))) {
            val x7140 = x11269._4;
          x7140
          } else {
            val x392 = if((x273.==(2))) {
              val x7143 = x11269._5;
            x7143
            } else {
              val x391 = if((x273.==(3))) {
                val x7146 = x11269._6;
              x7146
              } else {
                val x390 = if((x273.==(4))) {
                  val x7149 = x11269._7;
                x7149
                } else {
                  val x389 = if((x273.==(5))) {
                    val x7152 = x11269._8;
                  x7152
                  } else {
                    val x388 = if((x273.==(6))) {
                      val x7155 = x11269._9;
                    x7155
                    } else {
                      val x387 = if((x273.==(7))) {
                        val x7158 = x11269._10;
                      x7158
                      } else {
                        val x386 = if((x273.==(8))) {
                          val x7161 = x11269._11;
                        x7161
                        } else {
                          val x385 = if((x273.==(9))) {
                            val x7164 = x11269._12;
                          x7164
                          } else {
                            val x7165 = x11269._13;
                          x7165
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
          x392
          };
          val x7166 = x11269._3;
          val x396 = x286;
          x282.update(x396, x7166)
          val x398 = x286;
          val x399 = idata.apply(x398);
          val x400 = x399.contains("original");
          if((x400.&&({
            val x7173 = x11269._17;
            val x402 = x7173.contains("original");
            x402
          }))) {
            val x404 = x286;
            x283.update(x404, "B")
          } else {
            val x406 = x286;
            x283.update(x406, "G")
          }
          x11269._3_=((x7166.-(ol_quantity)))
          if((x7166.<=(ol_quantity))) {
            x11269._3 +=(91)
          } else {
          }
          var x415: Int = 0;
          if((ol_supply_w_id.!=(x272))) {
            x415 = 1
          } else {
          }
          val x7190 = x11229._16;
          val x7191 = x11232._8;
          val x7192 = x11236._9;
          val x428 = x286;
          val x429 = x280.apply(x428);
          val ol_amount = (((ol_quantity.toDouble).*(x429)).*(((1.0.+(x7191)).+(x7192)))).*((1.0.-(x7190)));
          val x437 = x286;
          x284.update(x437, ol_amount)
          val x439 = x347;
          x347 = (x439.+(ol_amount))
          val x442 = x286;
          x7210._1_=(x7114)
          x7210._2_=(x273)
          x7210._3_=(x272)
          x7210._4_=((x442.+(1)))
          x7210._5_=(ol_i_id)
          x7210._6_=(ol_supply_w_id)
          x7210._8_=(ol_quantity)
          x7210._9_=(ol_amount)
          x7210._10_=(ol_dist_info)
          orderLineTbl.unsafeInsert(x7210)
          val x447 = x286;
          x286 = (x447.+(1))
          ()
        }
      } else {
      }
      1
    }
  }

}
