
package tpcc.sc
import ddbt.lib.store._
import math.Ordering.{String => _}
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor {
  implicit object StringNoCase extends Ordering[String]{
    override def compare(x: String, y: String): Int = x.compareToIgnoreCase(y)
  }

  val x710 = { e: GenericEntry => {
      val x24 = e.get[Int](1);
      x24
    }
  };
  val x714 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), x710), EntryIdx.genericOps(List(2, 3)))
  val newOrderTbl = new Store[GenericEntry](3, x714);
  val newOrderTblIdx0 = newOrderTbl.index(0, IHash, true, -1)
  val newOrderTblIdx1 = newOrderTbl.index(1, ISliceHeapMin, false, 2)
  val newOrderTblIdx2 = newOrderTbl.index(2, INone, false, -1)
  val x721 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4, 5, 6, 7, 8)))
  val historyTbl = new Store[GenericEntry](1, x721);
  val historyTblIdx0 = historyTbl.index(0, IHash, true, -1)
  val x726 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,2))))
  val warehouseTbl = new Store[GenericEntry](1, x726);
  val warehouseTblIdx0 = warehouseTbl.index(0, IDirect, true, 1)
  val x731 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001))))
  val itemTbl = new Store[GenericEntry](1, x731);
  val itemTblIdx0 = itemTbl.index(0, IDirect, true, 100000)
  val x734 = { e: GenericEntry => {
      val x151 = e.get[Int](1);
      x151
    }
  };
  val x738 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), x734), EntryIdx.genericOps(List(2, 3, 4)))
  val orderTbl = new Store[GenericEntry](3, x738);
  val orderTblIdx0 = orderTbl.index(0, IHash, true, -1)
  val orderTblIdx1 = orderTbl.index(1, ISliceHeapMax, false, 2)
  val orderTblIdx2 = orderTbl.index(2, INone, false, -1)
  val x745 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,11), (2,1,2))))
  val districtTbl = new Store[GenericEntry](1, x745);
  val districtTblIdx0 = districtTbl.index(0, IDirect, true, 10)
  val x750 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val orderLineTbl = new Store[GenericEntry](2, x750);
  val orderLineTblIdx0 = orderLineTbl.index(0, IHash, true, -1)
  val orderLineTblIdx1 = orderLineTbl.index(1, IHash, false, -1)
  val x755 = { e: GenericEntry => {
      val x191 = e.get[String](4);
      x191
    }
  };
  val x759 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,3001), (2,1,11), (3,1,2))), EntryIdx.genericCmp(List(2, 3, 6), x755), EntryIdx.genericOps(List(2, 3, 6)))
  val customerTbl = new Store[GenericEntry](3, x759);
  val customerTblIdx0 = customerTbl.index(0, IDirect, true, 30000)
  val customerTblIdx1 = customerTbl.index(1, ISlicedHeapMed, false, 2)
  val customerTblIdx2 = customerTbl.index(2, INone, false, -1)
  val x766 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001), (2,1,2))))
  val stockTbl = new Store[GenericEntry](1, x766);
  val stockTblIdx0 = stockTbl.index(0, IDirect, true, 100000)
  

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)


      
   
  class DeliveryTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](10);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val x27 = x18;
        val x29 = GenericEntry.apply("SteSampleSEntry", 2, 3, x27, x12);
        val x2897 = newOrderTblIdx1.getCopy(x29);
        if((x2897.!=(null))) {
          val no_o_id = x2897.get[Int](1);
          val x36 = x18;
          orderIDs.update((x36.-(1)), no_o_id)
          newOrderTbl.deleteCopy(x2897)
          val x41 = x18;
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x41, x12);
          val x2908 = orderTblIdx0.getCopy(x43);
          val c_id = x2908.get[Int](4);
          x2908.update(6, x13)
          orderTblIdx1.updateCopy(x2908, orderTblIdx0)
          orderTblIdx0.updateCopy(x2908, orderTblIdx0)
          var x50: Double = 0.0;
          val x52 = x18;
          val x54 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x52, x12);
          orderLineTblIdx1.sliceCopy(x54, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x57 = x50;
              val x58 = orderLineEntry.get[Double](9);
              x50 = (x57.+(x58))
              orderLineTblIdx1.updateCopy(orderLineEntry, orderLineTblIdx0)
              orderLineTblIdx0.updateCopy(orderLineEntry, orderLineTblIdx0)
            
            }
          }))
          val x65 = x18;
          val x67 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, c_id, x65, x12);
          val x2930 = customerTblIdx0.getCopy(x67);
          val x69 = x50;
          x2930.+=(17, x69)
          x2930.+=(20, 1)
          customerTblIdx1.updateCopy(x2930, customerTblIdx0)
          customerTblIdx0.updateCopy(x2930, customerTblIdx0)
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
  class StockLevelTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x81 : Boolean, x82 : Date, x83 : Int, x84 : Int, x85 : Int, x86 : Int) =     {
      val x89 = GenericEntry.apply("SteSampleSEntry", 1, 2, x85, x84);
      val x2997 = districtTblIdx0.getCopy(x89);
      val o_id = x2997.get[Int](11);
      var x95: Int = (o_id.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply2;
      while({
        val x99 = x95;
        (x99.<(o_id))
      })
      {
        val x101 = x95;
        val x103 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x101, x85, x84);
        orderLineTblIdx1.sliceCopy(x103, ({ orderLineEntry: GenericEntry => {
            val ol_i_id = orderLineEntry.get[Int](5);
            val x109 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, x84);
            val x3010 = stockTblIdx0.getCopy(x109);
            val s_quantity = x3010.get[Int](3);
            if((s_quantity.<(x86))) {
              val x114 = unique_ol_i_id.+=(ol_i_id);
            } else {
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
  class OrderStatusTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x124 : Boolean, x125 : Date, x126 : Int, x127 : Int, x128 : Int, x129 : Int, x130 : Int, x131 : String) =     {
      val customerEntry = if((x129.>(0))) {
        val x140 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x128, x127, x131);
        val x3053 = customerTblIdx1.getCopy(x140);
      x3053
      } else {
        val x144 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x130, x128, x127);
        val x3056 = customerTblIdx0.getCopy(x144);
      x3056
      };
      val found_c_id = customerEntry.get[Int](3);
      val x155 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x128, x127, found_c_id);
      val x3060 = orderTblIdx1.getCopy(x155);
      var x160: Int = 0;
      val x162 = x3060.get[Int](1);
      x160 = x162
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x164 : Boolean, x165 : Date, x166 : Int, x167 : Int, x168 : Int, x169 : Int, x170 : Int, x171 : Int, x172 : Int, x173 : String, x174 : Double) =     {
      val x177 = GenericEntry.apply("SteSampleSEntry", 1, x167);
      val x3081 = warehouseTblIdx0.getCopy(x177);
      x3081.+=(9, x174)
      warehouseTblIdx0.updateCopy(x3081, warehouseTblIdx0)
      val x183 = GenericEntry.apply("SteSampleSEntry", 1, 2, x168, x167);
      val x3086 = districtTblIdx0.getCopy(x183);
      x3086.+=(10, x174)
      districtTblIdx0.updateCopy(x3086, districtTblIdx0)
      val customerEntry = if((x169.>(0))) {
        val x195 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x171, x170, x173);
        val x3093 = customerTblIdx1.getCopy(x195);
      x3093
      } else {
        val x199 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x172, x171, x170);
        val x3096 = customerTblIdx0.getCopy(x199);
      x3096
      };
      val c_data = customerEntry.get[String](21);
      val x204 = customerEntry.get[String](14);
      val x205 = x204.contains("BC");
      if(x205) {
        val x207 = customerEntry.get[Int](1);
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x207,x171,x170,x168,x167,x174,x165,c_data)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        customerEntry.+=(17, x174)
        customerEntry.update(21, c_new_data)
      } else {
        customerEntry.+=(17, x174)
      }
      customerTblIdx1.updateCopy(customerEntry, customerTblIdx0)
      customerTblIdx0.updateCopy(customerEntry, customerTblIdx0)
      val w_name = x3081.get[String](2);
      val d_name = x3086.get[String](3);
      var h_data = "%.10s    %.10s".format(w_name,d_name)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x222 = customerEntry.get[Int](1);
      val x224 = GenericEntry.apply("SteNewSEntry", x222, x171, x170, x168, x167, x165, x174, h_data);
      historyTbl.unsafeInsert(x224)
      1
    }
  }
  class NewOrderTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x226 : Boolean, x227 : Date, x228 : Int, x229 : Int, x230 : Int, x231 : Int, x232 : Int, x233 : Int, x234 : Array[Int], x235 : Array[Int], x236 : Array[Int], x237 : Array[Double], x238 : Array[String], x239 : Array[Int], x240 : Array[String], x241 : Array[Double]) =     {
      var x243: Int = 0;
      var x246: Int = 0;
      val idata = new Array[String](x232);
      var x251: Boolean = true;
      while({
        val x253 = x243;
        ((x253.<(x232)).&&({
          val x255 = x251;
          x255
        }))
      })
      {
        val x258 = x243;
        val x259 = x234.apply(x258);
        val x261 = GenericEntry.apply("SteSampleSEntry", 1, x259);
        val x3168 = itemTblIdx0.getCopy(x261);
        if((x3168.==(null))) {
          x251 = false
        } else {
          val x265 = x243;
          val x266 = x3168.get[String](3);
          x238.update(x265, x266)
          val x268 = x243;
          val x269 = x3168.get[Double](4);
          x237.update(x268, x269)
          val x271 = x243;
          val x272 = x3168.get[String](5);
          idata.update(x271, x272)
        }
        val x275 = x243;
        x243 = (x275.+(1))
        ()
      }
      val x279 = x251;
      if(x279) {
        val x282 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x231, x230, x229);
        val x3188 = customerTblIdx0.getCopy(x282);
        val x286 = GenericEntry.apply("SteSampleSEntry", 1, x229);
        val x3191 = warehouseTblIdx0.getCopy(x286);
        val x290 = GenericEntry.apply("SteSampleSEntry", 1, 2, x230, x229);
        val x3194 = districtTblIdx0.getCopy(x290);
        val o_id = x3194.get[Int](11);
        x3194.+=(11, 1)
        districtTblIdx0.updateCopy(x3194, districtTblIdx0)
        val x298 = GenericEntry.apply("SteNewSEntry", o_id, x230, x229, x231, x227, -1, x232, (x233.>(0)));
        orderTbl.unsafeInsert(x298)
        val x301 = GenericEntry.apply("SteNewSEntry", o_id, x230, x229);
        newOrderTbl.unsafeInsert(x301)
        var x304: Double = 0.0;
        x243 = 0
        while({
          val x307 = x243;
          (x307.<(x232))
        })
        {
          val x310 = x243;
          val ol_supply_w_id = x235.apply(x310);
          val x313 = x243;
          val ol_i_id = x234.apply(x313);
          val x316 = x243;
          val ol_quantity = x236.apply(x316);
          val x320 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val x3218 = stockTblIdx0.getCopy(x320);
          val ol_dist_info = if((x230.==(1))) {
            val x324 = x3218.get[String](4);
          x324
          } else {
            val x349 = if((x230.==(2))) {
              val x326 = x3218.get[String](5);
            x326
            } else {
              val x348 = if((x230.==(3))) {
                val x328 = x3218.get[String](6);
              x328
              } else {
                val x347 = if((x230.==(4))) {
                  val x330 = x3218.get[String](7);
                x330
                } else {
                  val x346 = if((x230.==(5))) {
                    val x332 = x3218.get[String](8);
                  x332
                  } else {
                    val x345 = if((x230.==(6))) {
                      val x334 = x3218.get[String](9);
                    x334
                    } else {
                      val x344 = if((x230.==(7))) {
                        val x336 = x3218.get[String](10);
                      x336
                      } else {
                        val x343 = if((x230.==(8))) {
                          val x338 = x3218.get[String](11);
                        x338
                        } else {
                          val x342 = if((x230.==(9))) {
                            val x340 = x3218.get[String](12);
                          x340
                          } else {
                            val x341 = x3218.get[String](13);
                          x341
                          };
                        x342
                        };
                      x343
                      };
                    x344
                    };
                  x345
                  };
                x346
                };
              x347
              };
            x348
            };
          x349
          };
          val s_quantity = x3218.get[Int](3);
          val x353 = x243;
          x239.update(x353, s_quantity)
          val x355 = x243;
          val x356 = idata.apply(x355);
          val x357 = x356.contains("original");
          if((x357.&&({
            val x358 = x3218.get[String](17);
            val x359 = x358.contains("original");
            x359
          }))) {
            val x361 = x243;
            x240.update(x361, "B")
          } else {
            val x363 = x243;
            x240.update(x363, "G")
          }
          x3218.update(3, (s_quantity.-(ol_quantity)))
          if((s_quantity.<=(ol_quantity))) {
            x3218.+=(3, 91)
          } else {
          }
          var x372: Int = 0;
          if((ol_supply_w_id.!=(x229))) {
            x372 = 1
          } else {
          }
          stockTblIdx0.updateCopy(x3218, stockTblIdx0)
          val c_discount = x3188.get[Double](16);
          val w_tax = x3191.get[Double](8);
          val d_tax = x3194.get[Double](9);
          val x385 = x243;
          val x386 = x237.apply(x385);
          val ol_amount = (((ol_quantity.toDouble).*(x386)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x394 = x243;
          x241.update(x394, ol_amount)
          val x396 = x304;
          x304 = (x396.+(ol_amount))
          val x399 = x243;
          val x402 = GenericEntry.apply("SteNewSEntry", o_id, x230, x229, (x399.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          orderLineTbl.unsafeInsert(x402)
          val x404 = x243;
          x243 = (x404.+(1))
          ()
        }
      } else {
      }
      1
    }
  }

}
