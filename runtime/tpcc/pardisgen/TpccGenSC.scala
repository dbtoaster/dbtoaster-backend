
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x877 = EntryIdx.genericOps(List(1, 2, 3));
  val x882 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), ({ e: GenericEntry => {
      val x24 = e.get[Int](1);
      x24
    }
  })), EntryIdx.genericOps(List(2, 3)))
  val x883 = new Store[GenericEntry](3, x882);
  val x884 = x883.index(0, IHash, true, -1)
  val x885 = x883.index(1, ISliceHeapMin, false, 2)
  val x886 = x883.index(2, INone, false, -1)
  val x889 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val x890 = new Store[GenericEntry](1, x889);
  val x891 = x890.index(0, IList, false, -1)
  val x894 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,2))))
  val x895 = new Store[GenericEntry](1, x894);
  val x896 = x895.index(0, IDirect, true, 1)
  val x899 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001))))
  val x900 = new Store[GenericEntry](1, x899);
  val x901 = x900.index(0, IDirect, true, 100000)
  val x906 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), ({ e: GenericEntry => {
      val x222 = e.get[Int](1);
      x222
    }
  })), EntryIdx.genericOps(List(2, 3, 4)))
  val x907 = new Store[GenericEntry](3, x906);
  val x908 = x907.index(0, IHash, true, -1)
  val x909 = x907.index(1, ISliceHeapMax, false, 2)
  val x910 = x907.index(2, INone, false, -1)
  val x913 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,11), (2,1,2))))
  val x914 = new Store[GenericEntry](1, x913);
  val x915 = x914.index(0, IDirect, true, 10)
  val x918 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val x919 = new Store[GenericEntry](2, x918);
  val x920 = x919.index(0, IHash, true, -1)
  val x921 = x919.index(1, IHash, false, -1)
  val x925 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,3001), (2,1,11), (3,1,2))), EntryIdx.genericOps(List(2, 3, 6)))
  val x926 = new Store[GenericEntry](2, x925);
  val x927 = x926.index(0, IDirect, true, 30000)
  val x928 = x926.index(1, IHash, false, -1)
  val x931 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001), (2,1,2))))
  val x932 = new Store[GenericEntry](1, x931);
  val x933 = x932.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x883
  val historyTbl = x890
  val warehouseTbl = x895
  val itemTbl = x900
  val orderTbl = x907
  val districtTbl = x914
  val orderLineTbl = x919
  val customerTbl = x926
  val stockTbl = x932
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   
  class DeliveryTx(x883: Store[GenericEntry], x890: Store[GenericEntry], x895: Store[GenericEntry], x900: Store[GenericEntry], x907: Store[GenericEntry], x914: Store[GenericEntry], x919: Store[GenericEntry], x926: Store[GenericEntry], x932: Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val orderIDs = new Array[Int](123);
      var x18: Int = 1;
      while({
        val x20 = x18;
        (x20.<=(10))
      })
      {
        val x27 = x18;
        val x29 = GenericEntry.apply("SteSampleSEntry", 2, 3, x27, x12);
        val x4495 = x885.get(x29);
        if((x4495.!=(null))) 
        {
          val no_o_id = x4495.get[Int](1);
          val x36 = x18;
          orderIDs.update((x36.-(1)), no_o_id)
          x883.delete(x4495)
          val x41 = x18;
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x41, x12);
          val x4506 = x908.get(x43);
          val c_id = x4506.get[Int](4);
          x4506.update(6, x13)
          val x4509 = x908.get(x4506);
          x909.updateCopyDependent(x4506, x4509)
          x908.updateCopyDependent(x4506, x4509)
          var x50: Double = 0.0;
          val x52 = x18;
          val x54 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, no_o_id, x52, x12);
          x921.slice(x54, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x57 = x50;
              val x58 = orderLineEntry.get[Double](9);
              x50 = (x57.+(x58))
              x920.update(orderLineEntry)
              x921.update(orderLineEntry)
              ()
            }
          }))
          val x65 = x18;
          val x67 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, c_id, x65, x12);
          val x4529 = x927.get(x67);
          val x69 = x50;
          x4529.+=(17, x69)
          x4529.+=(20, 1)
          val x4533 = x927.get(x4529);
          x927.updateCopyDependent(x4529, x4533)
          x928.updateCopyDependent(x4529, x4533)
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
      if(x10) 
      {
        val x82 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11);
        val x83 = x82.+("\n\n Warehouse: ");
        val x84 = x83.+(x12);
        val x85 = x84.+("\n Carrier:   ");
        val x86 = x85.+(x13);
        val x87 = x86.+("\n\n Delivered Orders\n");
        var x88: String = x87;
        var x91: Int = 0;
        var x94: Int = 1;
        while({
          val x96 = x94;
          (x96.<=(10))
        })
        {
          val x98 = x94;
          val x100 = orderIDs.apply((x98.-(1)));
          if((x100.>=(0))) 
          {
            val x102 = x88;
            val x103 = x102.+("  District ");
            val x104 = x94;
            val x106 = if((x104.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x107 = x103.+(x106);
            val x108 = x94;
            val x109 = x107.+(x108);
            val x110 = x109.+(": Order number ");
            val x111 = x94;
            val x113 = orderIDs.apply((x111.-(1)));
            val x114 = x110.+(x113);
            val x115 = x114.+(" was delivered.\n");
            x88 = x115
            ()
          }
          else
          {
            val x117 = x88;
            val x118 = x117.+("  District ");
            val x119 = x94;
            val x121 = if((x119.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            ;
            val x122 = x118.+(x121);
            val x123 = x94;
            val x124 = x122.+(x123);
            val x125 = x124.+(": No orders to be delivered.\n");
            x88 = x125
            val x127 = x91;
            x91 = (x127.+(1))
            ()
          }
          
          val x131 = x94;
          x94 = (x131.+(1))
          ()
        }
        val x135 = x88;
        val x136 = x135.+("+-----------------------------------------------------------------+\n\n");
        x88 = x136
        val x138 = x88;
        println(x138)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class StockLevelTx(x883: Store[GenericEntry], x890: Store[GenericEntry], x895: Store[GenericEntry], x900: Store[GenericEntry], x907: Store[GenericEntry], x914: Store[GenericEntry], x919: Store[GenericEntry], x926: Store[GenericEntry], x932: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x141 : Boolean, x142 : Date, x143 : Int, x144 : Int, x145 : Int, x146 : Int) =     {
      val x147 = GenericEntry("SteSampleSEntry", 1, 2, x145, x144);
      val x4708 = x915.get(x147);
      val x150 = x4708.get[Int](11);
      var x152: Int = (x150.-(20));
      val x153 = Set.apply[Int]();
      while({
        val x154 = x152;
        (x154.<(x150))
      })
      {
        val x156 = x152;
        val x158 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x156, x145, x144);
        x921.slice(x158, ({ x159: GenericEntry => {
            val x160 = x159.get[Int](5);
            val x161 = GenericEntry("SteSampleSEntry", 1, 2, x160, x144);
            val x4723 = x933.get(x161);
            val x163 = x4723.get[Int](3);
            if((x163.<(x146))) 
            {
              val x165 = x153.+=(x160);
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x169 = x152;
        x152 = (x169.+(1))
        ()
      }
      1
    }
  }
  class OrderStatusTx(x883: Store[GenericEntry], x890: Store[GenericEntry], x895: Store[GenericEntry], x900: Store[GenericEntry], x907: Store[GenericEntry], x914: Store[GenericEntry], x919: Store[GenericEntry], x926: Store[GenericEntry], x932: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x174 : Boolean, x175 : Date, x176 : Int, x177 : Int, x178 : Int, x179 : Int, x180 : Int, x181 : String) =     {
      val customerEntry = if((x179.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x187 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x178, x177, x181);
        x928.slice(x187, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x193 = customersWithLastName.size;
        var x195: Int = (x193./(2));
        val x197 = customersWithLastName.size;
        if(((x197.%(2)).==(0))) 
        {
          val x200 = x195;
          x195 = (x200.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x211 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x206 = c1.get[String](4);
            val x207 = c2.get[String](4);
            ((StringExtra.StringCompare(x206, x207)).<(0))
          }
        }));
        val x212 = x195;
        val x213 = x211.apply(x212);
        x213
      }
      else
      {
        val x214 = GenericEntry("SteSampleSEntry", 1, 2, 3, x180, x178, x177);
        val x4789 = x927.get(x214);
        x4789
      }
      ;
      val found_c_id = customerEntry.get[Int](3);
      val x226 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x178, x177, found_c_id);
      val x4794 = x909.get(x226);
      var x231: Int = 0;
      val x233 = x4794.get[Int](1);
      x231 = x233
      1
    }
  }
  class PaymentTx(x883: Store[GenericEntry], x890: Store[GenericEntry], x895: Store[GenericEntry], x900: Store[GenericEntry], x907: Store[GenericEntry], x914: Store[GenericEntry], x919: Store[GenericEntry], x926: Store[GenericEntry], x932: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x235 : Boolean, x236 : Date, x237 : Int, x238 : Int, x239 : Int, x240 : Int, x241 : Int, x242 : Int, x243 : Int, x244 : String, x245 : Double) =     {
      val x246 = GenericEntry("SteSampleSEntry", 1, x238);
      val x4840 = x896.get(x246);
      x4840.+=(9, x245)
      x896.update(x4840)
      val x251 = GenericEntry("SteSampleSEntry", 1, 2, x239, x238);
      val x4845 = x915.get(x251);
      x4845.+=(10, x245)
      x915.update(x4845)
      val customerEntry = if((x240.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x261 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x242, x241, x244);
        x928.slice(x261, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x267 = customersWithLastName.size;
        var x269: Int = (x267./(2));
        val x271 = customersWithLastName.size;
        if(((x271.%(2)).==(0))) 
        {
          val x274 = x269;
          x269 = (x274.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x285 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x280 = c1.get[String](4);
            val x281 = c2.get[String](4);
            ((StringExtra.StringCompare(x280, x281)).<(0))
          }
        }));
        val x286 = x269;
        val x287 = x285.apply(x286);
        x287
      }
      else
      {
        val x288 = GenericEntry("SteSampleSEntry", 1, 2, 3, x243, x242, x241);
        val x4879 = x927.get(x288);
        x4879
      }
      ;
      val c_data = customerEntry.get[String](21);
      val x294 = customerEntry.get[String](14);
      val x295 = x294.contains("BC");
      val x304 = if(x295) 
      {
        val x297 = customerEntry.get[Int](1);
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x297,x242,x241,x239,x238,x245,(x236.toString()),c_data)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        customerEntry.+=(17, x245)
        customerEntry.update(21, c_new_data)
        ()
      }
      else
      {
        customerEntry.+=(17, x245)
        ()
      }
      ;
      x927.update(customerEntry)
      x928.update(customerEntry)
      val w_name = x4840.get[String](2);
      val d_name = x4845.get[String](3);
      var h_data = "%.10s    %.10s".format(w_name,d_name)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x313 = customerEntry.get[Int](1);
      val x315 = GenericEntry.apply("SteNewSEntry", x313, x242, x241, x239, x238, x236, x245, h_data);
      x890.insert(x315)
      1
    }
  }
  class NewOrderTx(x883: Store[GenericEntry], x890: Store[GenericEntry], x895: Store[GenericEntry], x900: Store[GenericEntry], x907: Store[GenericEntry], x914: Store[GenericEntry], x919: Store[GenericEntry], x926: Store[GenericEntry], x932: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x317 : Boolean, x318 : Date, x319 : Int, x320 : Int, x321 : Int, x322 : Int, x323 : Int, x324 : Int, x325 : Array[Int], x326 : Array[Int], x327 : Array[Int], x328 : Array[Double], x329 : Array[String], x330 : Array[Int], x331 : Array[String], x332 : Array[Double]) =     {
      var x333: Int = 0;
      var x334: Boolean = false;
      val x335 = new Array[String](x323);
      var x336: Boolean = true;
      while({
        val x337 = x333;
        ((x337.<(x323)).&&({
          val x339 = x336;
          x339
        }))
      })
      {
        val x342 = x333;
        val x343 = x325.apply(x342);
        val x344 = GenericEntry("SteSampleSEntry", 1, x343);
        val x4977 = x901.get(x344);
        if((x4977.==(null))) 
        {
          x336 = false
          ()
        }
        else
        {
          val x349 = x333;
          val x350 = x4977.get[String](3);
          x329.update(x349, x350)
          val x352 = x333;
          val x353 = x4977.get[Double](4);
          x328.update(x352, x353)
          val x355 = x333;
          val x356 = x4977.get[String](5);
          x335.update(x355, x356)
          ()
        }
        
        val x359 = x333;
        x333 = (x359.+(1))
        ()
      }
      val x363 = x336;
      if(x363) 
      {
        val x364 = GenericEntry("SteSampleSEntry", 1, 2, 3, x322, x321, x320);
        val x4997 = x927.get(x364);
        val x367 = GenericEntry("SteSampleSEntry", 1, x320);
        val x5000 = x896.get(x367);
        val x370 = GenericEntry("SteSampleSEntry", 1, 2, x321, x320);
        val x5003 = x915.get(x370);
        val x373 = x5003.get[Int](11);
        x5003.+=(11, 1)
        x915.update(x5003)
        val x378 = GenericEntry.apply("SteNewSEntry", x373, x321, x320, x322, x318, -1, x323, (x324.>(0)));
        x907.insert(x378)
        val x381 = GenericEntry.apply("SteNewSEntry", x373, x321, x320);
        x883.insert(x381)
        var x383: Double = 0.0;
        x333 = 0
        while({
          val x385 = x333;
          (x385.<(x323))
        })
        {
          val x388 = x333;
          val ol_supply_w_id = x326.apply(x388);
          val x391 = x333;
          val ol_i_id = x325.apply(x391);
          val x394 = x333;
          val ol_quantity = x327.apply(x394);
          val x398 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val x5027 = x933.get(x398);
          val ol_dist_info = if((x321.==(1))) 
          {
            val x402 = x5027.get[String](4);
            x402
          }
          else
          {
            val x427 = if((x321.==(2))) 
            {
              val x404 = x5027.get[String](5);
              x404
            }
            else
            {
              val x426 = if((x321.==(3))) 
              {
                val x406 = x5027.get[String](6);
                x406
              }
              else
              {
                val x425 = if((x321.==(4))) 
                {
                  val x408 = x5027.get[String](7);
                  x408
                }
                else
                {
                  val x424 = if((x321.==(5))) 
                  {
                    val x410 = x5027.get[String](8);
                    x410
                  }
                  else
                  {
                    val x423 = if((x321.==(6))) 
                    {
                      val x412 = x5027.get[String](9);
                      x412
                    }
                    else
                    {
                      val x422 = if((x321.==(7))) 
                      {
                        val x414 = x5027.get[String](10);
                        x414
                      }
                      else
                      {
                        val x421 = if((x321.==(8))) 
                        {
                          val x416 = x5027.get[String](11);
                          x416
                        }
                        else
                        {
                          val x420 = if((x321.==(9))) 
                          {
                            val x418 = x5027.get[String](12);
                            x418
                          }
                          else
                          {
                            val x419 = x5027.get[String](13);
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
              x426
            }
            ;
            x427
          }
          ;
          val s_quantity = x5027.get[Int](3);
          val x431 = x333;
          x330.update(x431, s_quantity)
          val x433 = x4997.get[String](14);
          val x434 = x433.contains("original");
          if((x434.&&({
            val x435 = x5027.get[String](17);
            val x436 = x435.contains("original");
            x436
          }))) 
          {
            val x438 = x333;
            x331.update(x438, "B")
            ()
          }
          else
          {
            val x440 = x333;
            x331.update(x440, "G")
            ()
          }
          
          x5027.update(3, (s_quantity.-(ol_quantity)))
          val x447 = if((s_quantity.<=(ol_quantity))) 
          {
            x5027.+=(3, 91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x449: Int = 0;
          if((ol_supply_w_id.!=(x320))) 
          {
            x449 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x5078 = x933.get(x5027);
          x933.updateCopyDependent(x5027, x5078)
          val c_discount = x4997.get[Double](16);
          val w_tax = x5000.get[Double](8);
          val d_tax = x5003.get[Double](9);
          val x462 = x333;
          val x463 = x328.apply(x462);
          val ol_amount = (((ol_quantity.toDouble).*(x463)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x471 = x333;
          x332.update(x471, ol_amount)
          val x473 = x383;
          x383 = (x473.+(ol_amount))
          val x476 = x333;
          val x479 = GenericEntry.apply("SteNewSEntry", x373, x321, x320, (x476.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          x919.insert(x479)
          val x481 = x333;
          x333 = (x481.+(1))
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
