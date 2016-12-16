
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x875 = EntryIdx.genericOps(List(1, 2, 3));
  val x880 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), ({ x14: GenericEntry => {
      val x15 = x14.get[Int](1);
      x15
    }
  })), EntryIdx.genericOps(List(2, 3)))
  val x881 = new Store[GenericEntry](3, x880);
  val x882 = x881.index(0, IHash, true, -1)
  val x883 = x881.index(1, ISliceHeapMin, false, 2)
  val x884 = x881.index(2, INone, false, -1)
  val x887 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val x888 = new Store[GenericEntry](1, x887);
  val x889 = x888.index(0, IList, false, -1)
  val x892 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,2))))
  val x893 = new Store[GenericEntry](1, x892);
  val x894 = x893.index(0, IDirect, true, 1)
  val x897 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001))))
  val x898 = new Store[GenericEntry](1, x897);
  val x899 = x898.index(0, IDirect, true, 100000)
  val x904 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), ({ x181: GenericEntry => {
      val x182 = x181.get[Int](1);
      x182
    }
  })), EntryIdx.genericOps(List(2, 3, 4)))
  val x905 = new Store[GenericEntry](3, x904);
  val x906 = x905.index(0, IHash, true, -1)
  val x907 = x905.index(1, ISliceHeapMax, false, 2)
  val x908 = x905.index(2, INone, false, -1)
  val x911 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,11), (2,1,2))))
  val x912 = new Store[GenericEntry](1, x911);
  val x913 = x912.index(0, IDirect, true, 10)
  val x916 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val x917 = new Store[GenericEntry](2, x916);
  val x918 = x917.index(0, IHash, true, -1)
  val x919 = x917.index(1, IHash, false, -1)
  val x923 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,3001), (2,1,11), (3,1,2))), EntryIdx.genericOps(List(2, 3, 6)))
  val x924 = new Store[GenericEntry](2, x923);
  val x925 = x924.index(0, IDirect, true, 30000)
  val x926 = x924.index(1, IHash, false, -1)
  val x929 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001), (2,1,2))))
  val x930 = new Store[GenericEntry](1, x929);
  val x931 = x930.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x881
  val historyTbl = x888
  val warehouseTbl = x893
  val itemTbl = x898
  val orderTbl = x905
  val districtTbl = x912
  val orderLineTbl = x917
  val customerTbl = x924
  val stockTbl = x930
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   
  class DeliveryTx(x881: Store[GenericEntry], x888: Store[GenericEntry], x893: Store[GenericEntry], x898: Store[GenericEntry], x905: Store[GenericEntry], x912: Store[GenericEntry], x917: Store[GenericEntry], x924: Store[GenericEntry], x930: Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](123);
      var x22: Int = 1;
      while({
        val x24 = x22;
        (x24.<=(10))
      })
      {
        val x26 = x22;
        val x28 = GenericEntry.apply("SteSampleSEntry", 2, 3, x26, x12);
        val x4493 = x883.get(x28);
        if((x4493.!=(null))) 
        {
          val no_o_id = x4493.get[Int](1);
          val x35 = x22;
          orderIDs.update((x35.-(1)), no_o_id)
          x881.delete(x4493)
          val x40 = x22;
          val x42 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x40, x12);
          val x4504 = x906.get(x42);
          val c_id = x4504.get[Int](4);
          x4504.update(6, x13)
          val x4507 = x906.get(x4504);
          x906.updateCopyDependent(x4504, x4507)
          x907.updateCopyDependent(x4504, x4507)
          var x49: Double = 0.0;
          val x51 = x22;
          val x53 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x51, x12);
          x919.slice(x53, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x56 = x49;
              val x57 = orderLineEntry.get[Double](9);
              x49 = (x56.+(x57))
              x918.update(orderLineEntry)
              x919.update(orderLineEntry)
              ()
            }
          }))
          val x64 = x22;
          val x66 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, c_id, x64, x12);
          val x4527 = x925.get(x66);
          val x68 = x49;
          x4527.+=(17, x68)
          x4527.+=(20, 1)
          val x4531 = x925.get(x4527);
          x925.updateCopyDependent(x4527, x4531)
          x926.updateCopyDependent(x4527, x4531)
          ()
        }
        else
        {
          val x72 = x22;
          orderIDs.update((x72.-(1)), 0)
          ()
        }
        
        val x76 = x22;
        x22 = (x76.+(1))
        ()
      }
      if(x10) 
      {
        val x81 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11);
        val x82 = x81.+("\n\n Warehouse: ");
        val x83 = x82.+(x12);
        val x84 = x83.+("\n Carrier:   ");
        val x85 = x84.+(x13);
        val x86 = x85.+("\n\n Delivered Orders\n");
        var x87: String = x86;
        var x90: Int = 0;
        var x93: Int = 1;
        while({
          val x95 = x93;
          (x95.<=(10))
        })
        {
          val x97 = x93;
          val x99 = orderIDs.apply((x97.-(1)));
          if((x99.>=(0))) 
          {
            val x101 = x87;
            val x102 = x101.+("  District ");
            val x103 = x93;
            val x105 = if((x103.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x106 = x102.+(x105);
            val x107 = x93;
            val x108 = x106.+(x107);
            val x109 = x108.+(": Order number ");
            val x110 = x93;
            val x112 = orderIDs.apply((x110.-(1)));
            val x113 = x109.+(x112);
            val x114 = x113.+(" was delivered.\n");
            x87 = x114
            ()
          }
          else
          {
            val x116 = x87;
            val x117 = x116.+("  District ");
            val x118 = x93;
            val x120 = if((x118.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x121 = x117.+(x120);
            val x122 = x93;
            val x123 = x121.+(x122);
            val x124 = x123.+(": No orders to be delivered.\n");
            x87 = x124
            val x126 = x90;
            x90 = (x126.+(1))
            ()
          }
          
          val x130 = x93;
          x93 = (x130.+(1))
          ()
        }
        val x134 = x87;
        val x135 = x134.+("+-----------------------------------------------------------------+\n\n");
        x87 = x135
        val x137 = x87;
        println(x137)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class StockLevelTx(x881: Store[GenericEntry], x888: Store[GenericEntry], x893: Store[GenericEntry], x898: Store[GenericEntry], x905: Store[GenericEntry], x912: Store[GenericEntry], x917: Store[GenericEntry], x924: Store[GenericEntry], x930: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x140 : Boolean, x141 : Date, x142 : Int, x143 : Int, x144 : Int, x145 : Int) =     {
      val x146 = GenericEntry("SteSampleSEntry", 1, 2, x144, x143);
      val x4706 = x913.get(x146);
      val x149 = x4706.get[Int](11);
      var x151: Int = (x149.-(20));
      val x152 = Set.apply[Int]();
      while({
        val x153 = x151;
        (x153.<(x149))
      })
      {
        val x155 = x151;
        val x157 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x155, x144, x143);
        x919.slice(x157, ({ x158: GenericEntry => {
            val x159 = x158.get[Int](5);
            val x160 = GenericEntry("SteSampleSEntry", 1, 2, x159, x143);
            val x4721 = x931.get(x160);
            val x162 = x4721.get[Int](3);
            if((x162.<(x145))) 
            {
              val x164 = x152.+=(x159);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x168 = x151;
        x151 = (x168.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(x881: Store[GenericEntry], x888: Store[GenericEntry], x893: Store[GenericEntry], x898: Store[GenericEntry], x905: Store[GenericEntry], x912: Store[GenericEntry], x917: Store[GenericEntry], x924: Store[GenericEntry], x930: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x173 : Boolean, x174 : Date, x175 : Int, x176 : Int, x177 : Int, x178 : Int, x179 : Int, x180 : String) =     {
      val customerEntry = if((x178.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x190 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x177, x176, x180);
        x926.slice(x190, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x196 = customersWithLastName.size;
        var x198: Int = (x196./(2));
        val x200 = customersWithLastName.size;
        if(((x200.%(2)).==(0))) 
        {
          val x203 = x198;
          x198 = (x203.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x214 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x209 = c1.get[String](4);
            val x210 = c2.get[String](4);
            ((StringExtra.StringCompare(x209, x210)).<(0))
          }
        }));
        val x215 = x198;
        val x216 = x214.apply(x215);
        x216
      }
      else
      {
        val x217 = GenericEntry("SteSampleSEntry", 1, 2, 3, x179, x177, x176);
        val x4787 = x925.get(x217);
        x4787
      }
      ;
      val found_c_id = customerEntry.get[Int](3);
      val x224 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x177, x176, found_c_id);
      val x4792 = x907.get(x224);
      var x229: Int = 0;
      val x231 = x4792.get[Int](1);
      x229 = x231
      1
    }
  }
  class PaymentTx(x881: Store[GenericEntry], x888: Store[GenericEntry], x893: Store[GenericEntry], x898: Store[GenericEntry], x905: Store[GenericEntry], x912: Store[GenericEntry], x917: Store[GenericEntry], x924: Store[GenericEntry], x930: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x233 : Boolean, x234 : Date, x235 : Int, x236 : Int, x237 : Int, x238 : Int, x239 : Int, x240 : Int, x241 : Int, x242 : String, x243 : Double) =     {
      val x244 = GenericEntry("SteSampleSEntry", 1, x236);
      val x4838 = x894.get(x244);
      x4838.+=(9, x243)
      x894.update(x4838)
      val x249 = GenericEntry("SteSampleSEntry", 1, 2, x237, x236);
      val x4843 = x913.get(x249);
      x4843.+=(10, x243)
      x913.update(x4843)
      val customerEntry = if((x238.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x259 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x240, x239, x242);
        x926.slice(x259, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x265 = customersWithLastName.size;
        var x267: Int = (x265./(2));
        val x269 = customersWithLastName.size;
        if(((x269.%(2)).==(0))) 
        {
          val x272 = x267;
          x267 = (x272.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x283 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x278 = c1.get[String](4);
            val x279 = c2.get[String](4);
            ((StringExtra.StringCompare(x278, x279)).<(0))
          }
        }));
        val x284 = x267;
        val x285 = x283.apply(x284);
        x285
      }
      else
      {
        val x286 = GenericEntry("SteSampleSEntry", 1, 2, 3, x241, x240, x239);
        val x4877 = x925.get(x286);
        x4877
      }
      ;
      val c_data = customerEntry.get[String](21);
      val x292 = customerEntry.get[String](14);
      val x293 = x292.contains("BC");
      val x302 = if(x293) 
      {
        val x295 = customerEntry.get[Int](1);
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x295,x240,x239,x237,x236,x243,(x234.toString()),c_data)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        customerEntry.+=(17, x243)
        customerEntry.update(21, c_new_data)
        ()
      }
      else
      {
        customerEntry.+=(17, x243)
        ()
      }
      ;
      x925.update(customerEntry)
      x926.update(customerEntry)
      val w_name = x4838.get[String](2);
      val d_name = x4843.get[String](3);
      var h_data = "%.10s    %.10s".format(w_name,d_name)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x311 = customerEntry.get[Int](1);
      val x313 = GenericEntry.apply("SteNewSEntry", x311, x240, x239, x237, x236, x234, x243, h_data);
      x888.insert(x313)
      1
    }
  }
  class NewOrderTx(x881: Store[GenericEntry], x888: Store[GenericEntry], x893: Store[GenericEntry], x898: Store[GenericEntry], x905: Store[GenericEntry], x912: Store[GenericEntry], x917: Store[GenericEntry], x924: Store[GenericEntry], x930: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x315 : Boolean, x316 : Date, x317 : Int, x318 : Int, x319 : Int, x320 : Int, x321 : Int, x322 : Int, x323 : Array[Int], x324 : Array[Int], x325 : Array[Int], x326 : Array[Double], x327 : Array[String], x328 : Array[Int], x329 : Array[String], x330 : Array[Double]) =     {
      var x331: Int = 0;
      var x332: Boolean = false;
      val x333 = new Array[String](x321);
      var x334: Boolean = true;
      while({
        val x335 = x331;
        ((x335.<(x321)).&&({
          val x337 = x334;
          x337
        }))
      })
      {
        val x340 = x331;
        val x341 = x323.apply(x340);
        val x342 = GenericEntry("SteSampleSEntry", 1, x341);
        val x4975 = x899.get(x342);
        if((x4975.==(null))) 
        {
          x334 = false
          ()
        }
        else
        {
          val x347 = x331;
          val x348 = x4975.get[String](3);
          x327.update(x347, x348)
          val x350 = x331;
          val x351 = x4975.get[Double](4);
          x326.update(x350, x351)
          val x353 = x331;
          val x354 = x4975.get[String](5);
          x333.update(x353, x354)
          ()
        }
        
        val x357 = x331;
        x331 = (x357.+(1))
        ()
      }
      val x361 = x334;
      if(x361) 
      {
        val x362 = GenericEntry("SteSampleSEntry", 1, 2, 3, x320, x319, x318);
        val x4995 = x925.get(x362);
        val x365 = GenericEntry("SteSampleSEntry", 1, x318);
        val x4998 = x894.get(x365);
        val x368 = GenericEntry("SteSampleSEntry", 1, 2, x319, x318);
        val x5001 = x913.get(x368);
        val x371 = x5001.get[Int](11);
        x5001.+=(11, 1)
        x913.update(x5001)
        val x376 = GenericEntry.apply("SteNewSEntry", x371, x319, x318, x320, x316, -1, x321, (x322.>(0)));
        x905.insert(x376)
        val x379 = GenericEntry.apply("SteNewSEntry", x371, x319, x318);
        x881.insert(x379)
        var x381: Double = 0.0;
        x331 = 0
        while({
          val x383 = x331;
          (x383.<(x321))
        })
        {
          val x386 = x331;
          val ol_supply_w_id = x324.apply(x386);
          val x389 = x331;
          val ol_i_id = x323.apply(x389);
          val x392 = x331;
          val ol_quantity = x325.apply(x392);
          val x396 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val x5025 = x931.get(x396);
          val ol_dist_info = if((x319.==(1))) 
          {
            val x400 = x5025.get[String](4);
            x400
          }
          else
          {
            val x425 = if((x319.==(2))) 
            {
              val x402 = x5025.get[String](5);
              x402
            }
            else
            {
              val x424 = if((x319.==(3))) 
              {
                val x404 = x5025.get[String](6);
                x404
              }
              else
              {
                val x423 = if((x319.==(4))) 
                {
                  val x406 = x5025.get[String](7);
                  x406
                }
                else
                {
                  val x422 = if((x319.==(5))) 
                  {
                    val x408 = x5025.get[String](8);
                    x408
                  }
                  else
                  {
                    val x421 = if((x319.==(6))) 
                    {
                      val x410 = x5025.get[String](9);
                      x410
                    }
                    else
                    {
                      val x420 = if((x319.==(7))) 
                      {
                        val x412 = x5025.get[String](10);
                        x412
                      }
                      else
                      {
                        val x419 = if((x319.==(8))) 
                        {
                          val x414 = x5025.get[String](11);
                          x414
                        }
                        else
                        {
                          val x418 = if((x319.==(9))) 
                          {
                            val x416 = x5025.get[String](12);
                            x416
                          }
                          else
                          {
                            val x417 = x5025.get[String](13);
                            x417
                          }
                          ;
                          x418
                        }
                        ;
                        x419
                      }
                      ;
                      x420
                    }
                    ;
                    x421
                  }
                  ;
                  x422
                }
                ;
                x423
              }
              ;
              x424
            }
            ;
            x425
          }
          ;
          val s_quantity = x5025.get[Int](3);
          val x429 = x331;
          x328.update(x429, s_quantity)
          val x431 = x4995.get[String](14);
          val x432 = x431.contains("original");
          if((x432.&&({
            val x433 = x5025.get[String](17);
            val x434 = x433.contains("original");
            x434
          }))) 
          {
            val x436 = x331;
            x329.update(x436, "B")
            ()
          }
          else
          {
            val x438 = x331;
            x329.update(x438, "G")
            ()
          }
          
          x5025.update(3, (s_quantity.-(ol_quantity)))
          val x445 = if((s_quantity.<=(ol_quantity))) 
          {
            x5025.+=(3, 91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x447: Int = 0;
          if((ol_supply_w_id.!=(x318))) 
          {
            x447 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x5076 = x931.get(x5025);
          x931.updateCopyDependent(x5025, x5076)
          val c_discount = x4995.get[Double](16);
          val w_tax = x4998.get[Double](8);
          val d_tax = x5001.get[Double](9);
          val x460 = x331;
          val x461 = x326.apply(x460);
          val ol_amount = (((ol_quantity.toDouble).*(x461)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x469 = x331;
          x330.update(x469, ol_amount)
          val x471 = x381;
          x381 = (x471.+(ol_amount))
          val x474 = x331;
          val x477 = GenericEntry.apply("SteNewSEntry", x371, x319, x318, (x474.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          x917.insert(x477)
          val x479 = x331;
          x331 = (x479.+(1))
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
