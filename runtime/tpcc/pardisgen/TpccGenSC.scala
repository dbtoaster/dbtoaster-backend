
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x458 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)))
  val newOrderTbl = new Store[GenericEntry](1, x458);
  val x460 = newOrderTbl.index(0, IList, false, -1)
  val x463 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val historyTbl = new Store[GenericEntry](1, x463);
  val x465 = historyTbl.index(0, IList, false, -1)
  val x468 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1)))
  val warehouseTbl = new Store[GenericEntry](1, x468);
  val x470 = warehouseTbl.index(0, IList, false, -1)
  val x471 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1)))
  val itemTbl = new Store[GenericEntry](1, x471);
  val x473 = itemTbl.index(0, IList, false, -1)
  val x474 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)))
  val orderTbl = new Store[GenericEntry](1, x474);
  val x476 = orderTbl.index(0, IList, false, -1)
  val x479 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2)))
  val districtTbl = new Store[GenericEntry](1, x479);
  val x481 = districtTbl.index(0, IList, false, -1)
  val x484 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)))
  val orderLineTbl = new Store[GenericEntry](1, x484);
  val x486 = orderLineTbl.index(0, IList, false, -1)
  val x487 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)))
  val customerTbl = new Store[GenericEntry](1, x487);
  val x489 = customerTbl.index(0, IList, false, -1)
  val x490 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2)))
  val stockTbl = new Store[GenericEntry](1, x490);
  val x492 = stockTbl.index(0, IList, false, -1)
  

  val newOrderTxInst = new NewOrderTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl, historyTbl, warehouseTbl, itemTbl, orderTbl, districtTbl, orderLineTbl, customerTbl, stockTbl)

      
   
  class DeliveryTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](123);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val agg = Aggregator.min(({ e: GenericEntry => {
            val x24 = e.get[Int](1);
            x24
          }
        }));
        val x27 = x18;
        val x29 = GenericEntry.apply("SteSampleSEntry", 2, 3, x27, x12);
        newOrderTbl.sliceCopy(0, x29, agg)
        val firstOrderEntry = agg.result;
        if((firstOrderEntry.!=(null))) 
        {
          val no_o_id = firstOrderEntry.get[Int](1);
          val x36 = x18;
          orderIDs.update((x36.-(1)), no_o_id)
          newOrderTbl.deleteCopy(firstOrderEntry)
          val x41 = x18;
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x41, x12);
          val orderEntry = orderTbl.getCopy(0, x43)
          val c_id = orderEntry.get[Int](4);
          orderEntry.update(6, x13)
          orderTbl.updateCopy(orderEntry)
          var x51: Double = 0.0;
          val x53 = x18;
          val x55 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x53, x12);
          orderLineTbl.sliceCopy(0, x55, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x58 = x51;
              val x59 = orderLineEntry.get[Double](9);
              x51 = (x58.+(x59))
              orderLineTbl.updateCopy(orderLineEntry)
              ()
            }
          }))
          val x66 = x18;
          val x68 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, c_id, x66, x12);
          val customerEntry = customerTbl.getCopy(0, x68)
          val x70 = x51;
          customerEntry.+=(17, x70)
          customerEntry.+=(20, 1)
          customerTbl.updateCopy(customerEntry)
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
  class StockLevelTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x82 : Boolean, x83 : Date, x84 : Int, x85 : Int, x86 : Int, x87 : Int) =     {
      val x90 = GenericEntry.apply("SteSampleSEntry", 1, 2, x86, x85);
      val districtEntry = districtTbl.getCopy(0, x90)
      val o_id = districtEntry.get[Int](11);
      var x97: Int = (o_id.-(20));
      val unique_ol_i_id = Set.apply[Int]() //Apply1;
      while({
        val x101 = x97;
        (x101.<(o_id))
      })
      {
        val x103 = x97;
        val x105 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x103, x86, x85);
        orderLineTbl.sliceCopy(0, x105, ({ orderLineEntry: GenericEntry => {
            val ol_i_id = orderLineEntry.get[Int](5);
            val x111 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, x85);
            val stockEntry = stockTbl.getCopy(0, x111)
            val s_quantity = stockEntry.get[Int](3);
            if((s_quantity.<(x87))) 
            {
              val x116 = unique_ol_i_id.+=(ol_i_id);
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
  class OrderStatusTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x126 : Boolean, x127 : Date, x128 : Int, x129 : Int, x130 : Int, x131 : Int, x132 : Int, x133 : String) =     {
      val customerEntry = if((x131.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x139 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x130, x129, x133);
        customerTbl.sliceCopy(0, x139, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x145 = customersWithLastName.size;
        var x147: Int = (x145./(2));
        val x149 = customersWithLastName.size;
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
        
        val x163 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x158 = c1.get[String](4);
            val x159 = c2.get[String](4);
            ((StringExtra.StringCompare(x158, x159)).<(0))
          }
        }));
        val x164 = x147;
        val x165 = x163.apply(x164);
        x165
      }
      else
      {
        val x167 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x132, x130, x129);
        val x169 = customerTbl.getCopy(0, x167)
        x169
      }
      ;
      val found_c_id = customerEntry.get[Int](3);
      val agg = Aggregator.max(({ e: GenericEntry => {
          val x175 = e.get[Int](1);
          x175
        }
      }));
      val x179 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x130, x129, found_c_id);
      orderTbl.sliceCopy(0, x179, agg)
      val newestOrderEntry = agg.result;
      var x184: Int = 0;
      val x186 = newestOrderEntry.get[Int](1);
      x184 = x186
      1
    }
  }
  class PaymentTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x188 : Boolean, x189 : Date, x190 : Int, x191 : Int, x192 : Int, x193 : Int, x194 : Int, x195 : Int, x196 : Int, x197 : String, x198 : Double) =     {
      val x201 = GenericEntry.apply("SteSampleSEntry", 1, x191);
      val warehouseEntry = warehouseTbl.getCopy(0, x201)
      warehouseEntry.+=(9, x198)
      warehouseTbl.updateCopy(warehouseEntry)
      val x208 = GenericEntry.apply("SteSampleSEntry", 1, 2, x192, x191);
      val districtEntry = districtTbl.getCopy(0, x208)
      districtEntry.+=(10, x198)
      districtTbl.updateCopy(districtEntry)
      val customerEntry = if((x193.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x217 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x195, x194, x197);
        customerTbl.sliceCopy(0, x217, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x223 = customersWithLastName.size;
        var x225: Int = (x223./(2));
        val x227 = customersWithLastName.size;
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
        
        val x241 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x236 = c1.get[String](4);
            val x237 = c2.get[String](4);
            ((StringExtra.StringCompare(x236, x237)).<(0))
          }
        }));
        val x242 = x225;
        val x243 = x241.apply(x242);
        x243
      }
      else
      {
        val x245 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x196, x195, x194);
        val x246 = customerTbl.getCopy(0, x245)
        x246
      }
      ;
      val c_data = customerEntry.get[String](21);
      val x250 = customerEntry.get[String](14);
      val x251 = x250.contains("BC");
      if(x251) 
      {
        val x253 = customerEntry.get[Int](1);
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x253,x195,x194,x192,x191,x198,x189,c_data)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        customerEntry.+=(17, x198)
        customerEntry.update(21, c_new_data)
        ()
      }
      else
      {
        customerEntry.+=(17, x198)
        ()
      }
      
      customerTbl.updateCopy(customerEntry)
      val w_name = warehouseEntry.get[String](2);
      val d_name = districtEntry.get[String](3);
      var h_data = "%.10s    %.10s".format(w_name,d_name)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x268 = customerEntry.get[Int](1);
      val x270 = GenericEntry.apply("SteNewSEntry", x268, x195, x194, x192, x191, x189, x198, h_data);
      historyTbl.insert(x270)
      1
    }
  }
  class NewOrderTx(newOrderTbl : Store[GenericEntry], historyTbl : Store[GenericEntry], warehouseTbl : Store[GenericEntry], itemTbl : Store[GenericEntry], orderTbl : Store[GenericEntry], districtTbl : Store[GenericEntry], orderLineTbl : Store[GenericEntry], customerTbl : Store[GenericEntry], stockTbl : Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
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
        val x307 = GenericEntry.apply("SteSampleSEntry", 1, x305);
        val itemEntry = itemTbl.getCopy(0, x307)
        if((itemEntry.==(null))) 
        {
          x297 = false
          ()
        }
        else
        {
          val x312 = x289;
          val x313 = itemEntry.get[String](3);
          x284.update(x312, x313)
          val x315 = x289;
          val x316 = itemEntry.get[Double](4);
          x283.update(x315, x316)
          val x318 = x289;
          val x319 = itemEntry.get[String](5);
          idata.update(x318, x319)
          ()
        }
        
        val x322 = x289;
        x289 = (x322.+(1))
        ()
      }
      val x326 = x297;
      if(x326) 
      {
        val x329 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x277, x276, x275);
        val customerEntry = customerTbl.getCopy(0, x329)
        val x334 = GenericEntry.apply("SteSampleSEntry", 1, x275);
        val warehouseEntry = warehouseTbl.getCopy(0, x334)
        val x338 = GenericEntry.apply("SteSampleSEntry", 1, 2, x276, x275);
        val districtEntry = districtTbl.getCopy(0, x338)
        val o_id = districtEntry.get[Int](11);
        districtEntry.+=(11, 1)
        districtTbl.updateCopy(districtEntry)
        val x346 = GenericEntry.apply("SteNewSEntry", o_id, x276, x275, x277, x273, -1, x278, (x279.>(0)));
        orderTbl.insert(x346)
        val x349 = GenericEntry.apply("SteNewSEntry", o_id, x276, x275);
        newOrderTbl.insert(x349)
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
          val x368 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val stockEntry = stockTbl.getCopy(0, x368)
          val ol_dist_info = if((x276.==(1))) 
          {
            val x372 = stockEntry.get[String](4);
            x372
          }
          else
          {
            val x397 = if((x276.==(2))) 
            {
              val x374 = stockEntry.get[String](5);
              x374
            }
            else
            {
              val x396 = if((x276.==(3))) 
              {
                val x376 = stockEntry.get[String](6);
                x376
              }
              else
              {
                val x395 = if((x276.==(4))) 
                {
                  val x378 = stockEntry.get[String](7);
                  x378
                }
                else
                {
                  val x394 = if((x276.==(5))) 
                  {
                    val x380 = stockEntry.get[String](8);
                    x380
                  }
                  else
                  {
                    val x393 = if((x276.==(6))) 
                    {
                      val x382 = stockEntry.get[String](9);
                      x382
                    }
                    else
                    {
                      val x392 = if((x276.==(7))) 
                      {
                        val x384 = stockEntry.get[String](10);
                        x384
                      }
                      else
                      {
                        val x391 = if((x276.==(8))) 
                        {
                          val x386 = stockEntry.get[String](11);
                          x386
                        }
                        else
                        {
                          val x390 = if((x276.==(9))) 
                          {
                            val x388 = stockEntry.get[String](12);
                            x388
                          }
                          else
                          {
                            val x389 = stockEntry.get[String](13);
                            x389
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
          val s_quantity = stockEntry.get[Int](3);
          val x401 = x289;
          x285.update(x401, s_quantity)
          val x403 = customerEntry.get[String](14);
          val x404 = x403.contains("original");
          if((x404.&&({
            val x405 = stockEntry.get[String](17);
            val x406 = x405.contains("original");
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
          
          stockEntry.update(3, (s_quantity.-(ol_quantity)))
          if((s_quantity.<=(ol_quantity))) 
          {
            stockEntry.+=(3, 91)
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
          
          stockTbl.updateCopy(stockEntry)
          val c_discount = customerEntry.get[Double](16);
          val w_tax = warehouseEntry.get[Double](8);
          val d_tax = districtEntry.get[Double](9);
          val x432 = x289;
          val x433 = x283.apply(x432);
          val ol_amount = (((ol_quantity.toDouble).*(x433)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x441 = x289;
          x287.update(x441, ol_amount)
          val x443 = x352;
          x352 = (x443.+(ol_amount))
          val x446 = x289;
          val x449 = GenericEntry.apply("SteNewSEntry", o_id, x276, x275, (x446.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          orderLineTbl.insert(x449)
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
