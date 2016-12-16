
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x743 = EntryIdx.genericOps(List(1, 2, 3));
  val x748 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), ({ x18: GenericEntry => {
      val x19 = x18.get[Int](1);
      x19
    }
  })), EntryIdx.genericOps(List(2, 3)))
  val x749 = new Store[GenericEntry](3, x748);
  val x750 = x749.index(0, IHash, true, -1)
  val x751 = x749.index(1, ISliceHeapMin, false, 2)
  val x752 = x749.index(2, INone, false, -1)
  val x755 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val x756 = new Store[GenericEntry](1, x755);
  val x757 = x756.index(0, IList, false, -1)
  val x760 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,2))))
  val x761 = new Store[GenericEntry](1, x760);
  val x762 = x761.index(0, IDirect, true, 1)
  val x765 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001))))
  val x766 = new Store[GenericEntry](1, x765);
  val x767 = x766.index(0, IDirect, true, 100000)
  val x772 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), ({ x145: GenericEntry => {
      val x146 = x145.get[Int](1);
      x146
    }
  })), EntryIdx.genericOps(List(2, 3, 4)))
  val x773 = new Store[GenericEntry](3, x772);
  val x774 = x773.index(0, IHash, true, -1)
  val x775 = x773.index(1, ISliceHeapMax, false, 2)
  val x776 = x773.index(2, INone, false, -1)
  val x779 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,11), (2,1,2))))
  val x780 = new Store[GenericEntry](1, x779);
  val x781 = x780.index(0, IDirect, true, 10)
  val x784 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val x785 = new Store[GenericEntry](2, x784);
  val x786 = x785.index(0, IHash, true, -1)
  val x787 = x785.index(1, IHash, false, -1)
  val x791 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,3001), (2,1,11), (3,1,2))), EntryIdx.genericOps(List(2, 3, 6)))
  val x792 = new Store[GenericEntry](2, x791);
  val x793 = x792.index(0, IDirect, true, 30000)
  val x794 = x792.index(1, IHash, false, -1)
  val x797 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001), (2,1,2))))
  val x798 = new Store[GenericEntry](1, x797);
  val x799 = x798.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x749
  val historyTbl = x756
  val warehouseTbl = x761
  val itemTbl = x766
  val orderTbl = x773
  val districtTbl = x780
  val orderLineTbl = x785
  val customerTbl = x792
  val stockTbl = x798
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   
  class DeliveryTx(x749: Store[GenericEntry], x756: Store[GenericEntry], x761: Store[GenericEntry], x766: Store[GenericEntry], x773: Store[GenericEntry], x780: Store[GenericEntry], x785: Store[GenericEntry], x792: Store[GenericEntry], x798: Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
    def apply(x10 : Boolean, x11 : Date, x12 : Int, x13 : Int) =     {
      val x14 = new Array[Int](10);
      var x15: Int = 1;
      while({
        val x16 = x15;
        (x16.<=(10))
      })
      {
        val x22 = x15;
        val x24 = GenericEntry.apply("SteSampleSEntry", 2, 3, x22, x12);
        val x3921 = x751.get(x24);
        if((x3921.!=(null))) 
        {
          val x28 = x3921.get[Int](1);
          val x29 = x15;
          x14.update((x29.-(1)), x28)
          x749.delete(x3921)
          val x33 = x15;
          val x34 = GenericEntry("SteSampleSEntry", 1, 2, 3, x28, x33, x12);
          val x3932 = x774.get(x34);
          val x37 = x3932.get[Int](4);
          x3932.update(6, x13)
          x774.update(x3932)
          x775.update(x3932)
          var x40: Double = 0.0;
          val x41 = x15;
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x28, x41, x12);
          x787.slice(x43, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x46 = x40;
              val x47 = orderLineEntry.get[Double](9);
              x40 = (x46.+(x47))
              x786.update(orderLineEntry)
              x787.update(orderLineEntry)
              ()
            }
          }))
          val x53 = x15;
          val x54 = GenericEntry("SteSampleSEntry", 1, 2, 3, x37, x53, x12);
          val x3953 = x793.get(x54);
          val x56 = x40;
          x3953.+=(17, x56)
          x3953.+=(20, 1)
          x794.update(x3953)
          x793.update(x3953)
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
  class StockLevelTx(x749: Store[GenericEntry], x756: Store[GenericEntry], x761: Store[GenericEntry], x766: Store[GenericEntry], x773: Store[GenericEntry], x780: Store[GenericEntry], x785: Store[GenericEntry], x792: Store[GenericEntry], x798: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x68 : Boolean, x69 : Date, x70 : Int, x71 : Int, x72 : Int, x73 : Int) =     {
      val x74 = GenericEntry("SteSampleSEntry", 1, 2, x72, x71);
      val x4020 = x781.get(x74);
      val x77 = x4020.get[Int](11);
      var x79: Int = (x77.-(20));
      val x80 = Set.apply[Int]();
      while({
        val x81 = x79;
        (x81.<(x77))
      })
      {
        val x83 = x79;
        val x85 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x83, x72, x71);
        x787.slice(x85, ({ x86: GenericEntry => {
            val x87 = x86.get[Int](5);
            val x88 = GenericEntry("SteSampleSEntry", 1, 2, x87, x71);
            val x4035 = x799.get(x88);
            val x90 = x4035.get[Int](3);
            if((x90.<(x73))) 
            {
              val x92 = x80.+=(x87);
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
  class OrderStatusTx(x749: Store[GenericEntry], x756: Store[GenericEntry], x761: Store[GenericEntry], x766: Store[GenericEntry], x773: Store[GenericEntry], x780: Store[GenericEntry], x785: Store[GenericEntry], x792: Store[GenericEntry], x798: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x101 : Boolean, x102 : Date, x103 : Int, x104 : Int, x105 : Int, x106 : Int, x107 : Int, x108 : String) =     {
      val x143 = if((x106.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x113 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x105, x104, x108);
        x794.slice(x113, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x119 = customersWithLastName.size;
        var x121: Int = (x119./(2));
        val x123 = customersWithLastName.size;
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
        
        val x137 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x132 = c1.get[String](4);
            val x133 = c2.get[String](4);
            ((StringExtra.StringCompare(x132, x133)).<(0))
          }
        }));
        val x138 = x121;
        val x139 = x137.apply(x138);
        x139
      }
      else
      {
        val x140 = GenericEntry("SteSampleSEntry", 1, 2, 3, x107, x105, x104);
        val x4101 = x793.get(x140);
        x4101
      }
      ;
      val x144 = x143.get[Int](3);
      val x150 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x105, x104, x144);
      val x4106 = x775.get(x150);
      var x153: Int = 0;
      val x154 = x4106.get[Int](1);
      x153 = x154
      1
    }
  }
  class PaymentTx(x749: Store[GenericEntry], x756: Store[GenericEntry], x761: Store[GenericEntry], x766: Store[GenericEntry], x773: Store[GenericEntry], x780: Store[GenericEntry], x785: Store[GenericEntry], x792: Store[GenericEntry], x798: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x156 : Boolean, x157 : Date, x158 : Int, x159 : Int, x160 : Int, x161 : Int, x162 : Int, x163 : Int, x164 : Int, x165 : String, x166 : Double) =     {
      val x167 = GenericEntry("SteSampleSEntry", 1, x159);
      val x4152 = x762.get(x167);
      x4152.+=(9, x166)
      x762.update(x4152)
      val x172 = GenericEntry("SteSampleSEntry", 1, 2, x160, x159);
      val x4157 = x781.get(x172);
      x4157.+=(10, x166)
      x781.update(x4157)
      val customerEntry = if((x161.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x182 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x163, x162, x165);
        x794.slice(x182, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x188 = customersWithLastName.size;
        var x190: Int = (x188./(2));
        val x192 = customersWithLastName.size;
        if(((x192.%(2)).==(0))) 
        {
          val x195 = x190;
          x190 = (x195.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x206 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x201 = c1.get[String](4);
            val x202 = c2.get[String](4);
            ((StringExtra.StringCompare(x201, x202)).<(0))
          }
        }));
        val x207 = x190;
        val x208 = x206.apply(x207);
        x208
      }
      else
      {
        val x209 = GenericEntry("SteSampleSEntry", 1, 2, 3, x164, x163, x162);
        val x4191 = x793.get(x209);
        x4191
      }
      ;
      val c_data = customerEntry.get[String](21);
      val x215 = customerEntry.get[String](14);
      val x216 = x215.contains("BC");
      val x225 = if(x216) 
      {
        val x218 = customerEntry.get[Int](1);
        var c_new_data = "%d %d %d %d %d $%f %s | %s".format(x218,x163,x162,x160,x159,x166,(x157.toString()),c_data)
        if(c_new_data.size > 500) 
          c_new_data = c_new_data.substring(0, 500)
        customerEntry.+=(17, x166)
        customerEntry.update(21, c_new_data)
        ()
      }
      else
      {
        customerEntry.+=(17, x166)
        ()
      }
      ;
      x794.update(customerEntry)
      x793.update(customerEntry)
      val w_name = x4152.get[String](2);
      val d_name = x4157.get[String](3);
      var h_data = "%.10s    %.10s".format(w_name,d_name)
      if(h_data.size > 24) 
        h_data = h_data.substring(0, 24)
      val x234 = customerEntry.get[Int](1);
      val x236 = GenericEntry.apply("SteNewSEntry", x234, x163, x162, x160, x159, x157, x166, h_data);
      x756.insert(x236)
      1
    }
  }
  class NewOrderTx(x749: Store[GenericEntry], x756: Store[GenericEntry], x761: Store[GenericEntry], x766: Store[GenericEntry], x773: Store[GenericEntry], x780: Store[GenericEntry], x785: Store[GenericEntry], x792: Store[GenericEntry], x798: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x238 : Boolean, x239 : Date, x240 : Int, x241 : Int, x242 : Int, x243 : Int, x244 : Int, x245 : Int, x246 : Array[Int], x247 : Array[Int], x248 : Array[Int], x249 : Array[Double], x250 : Array[String], x251 : Array[Int], x252 : Array[String], x253 : Array[Double]) =     {
      var x254: Int = 0;
      var x255: Boolean = false;
      val x256 = new Array[String](x244);
      var x257: Boolean = true;
      while({
        val x258 = x254;
        ((x258.<(x244)).&&({
          val x260 = x257;
          x260
        }))
      })
      {
        val x263 = x254;
        val x264 = x246.apply(x263);
        val x265 = GenericEntry("SteSampleSEntry", 1, x264);
        val x4289 = x767.get(x265);
        if((x4289.==(null))) 
        {
          x257 = false
          ()
        }
        else
        {
          val x270 = x254;
          val x271 = x4289.get[String](3);
          x250.update(x270, x271)
          val x273 = x254;
          val x274 = x4289.get[Double](4);
          x249.update(x273, x274)
          val x276 = x254;
          val x277 = x4289.get[String](5);
          x256.update(x276, x277)
          ()
        }
        
        val x280 = x254;
        x254 = (x280.+(1))
        ()
      }
      val x284 = x257;
      if(x284) 
      {
        val x285 = GenericEntry("SteSampleSEntry", 1, 2, 3, x243, x242, x241);
        val x4309 = x793.get(x285);
        val x288 = GenericEntry("SteSampleSEntry", 1, x241);
        val x4312 = x762.get(x288);
        val x291 = GenericEntry("SteSampleSEntry", 1, 2, x242, x241);
        val x4315 = x781.get(x291);
        val x294 = x4315.get[Int](11);
        x4315.+=(11, 1)
        x781.update(x4315)
        val x299 = GenericEntry.apply("SteNewSEntry", x294, x242, x241, x243, x239, -1, x244, (x245.>(0)));
        x773.insert(x299)
        val x302 = GenericEntry.apply("SteNewSEntry", x294, x242, x241);
        x749.insert(x302)
        var x304: Double = 0.0;
        x254 = 0
        while({
          val x306 = x254;
          (x306.<(x244))
        })
        {
          val x309 = x254;
          val ol_supply_w_id = x247.apply(x309);
          val x312 = x254;
          val ol_i_id = x246.apply(x312);
          val x315 = x254;
          val ol_quantity = x248.apply(x315);
          val x319 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val x4339 = x799.get(x319);
          val ol_dist_info = if((x242.==(1))) 
          {
            val x323 = x4339.get[String](4);
            x323
          }
          else
          {
            val x348 = if((x242.==(2))) 
            {
              val x325 = x4339.get[String](5);
              x325
            }
            else
            {
              val x347 = if((x242.==(3))) 
              {
                val x327 = x4339.get[String](6);
                x327
              }
              else
              {
                val x346 = if((x242.==(4))) 
                {
                  val x329 = x4339.get[String](7);
                  x329
                }
                else
                {
                  val x345 = if((x242.==(5))) 
                  {
                    val x331 = x4339.get[String](8);
                    x331
                  }
                  else
                  {
                    val x344 = if((x242.==(6))) 
                    {
                      val x333 = x4339.get[String](9);
                      x333
                    }
                    else
                    {
                      val x343 = if((x242.==(7))) 
                      {
                        val x335 = x4339.get[String](10);
                        x335
                      }
                      else
                      {
                        val x342 = if((x242.==(8))) 
                        {
                          val x337 = x4339.get[String](11);
                          x337
                        }
                        else
                        {
                          val x341 = if((x242.==(9))) 
                          {
                            val x339 = x4339.get[String](12);
                            x339
                          }
                          else
                          {
                            val x340 = x4339.get[String](13);
                            x340
                          }
                          ;
                          x341
                        }
                        ;
                        x342
                      }
                      ;
                      x343
                    }
                    ;
                    x344
                  }
                  ;
                  x345
                }
                ;
                x346
              }
              ;
              x347
            }
            ;
            x348
          }
          ;
          val s_quantity = x4339.get[Int](3);
          val x352 = x254;
          x251.update(x352, s_quantity)
          val x354 = x4309.get[String](14);
          val x355 = x354.contains("original");
          if((x355.&&({
            val x356 = x4339.get[String](17);
            val x357 = x356.contains("original");
            x357
          }))) 
          {
            val x359 = x254;
            x252.update(x359, "B")
            ()
          }
          else
          {
            val x361 = x254;
            x252.update(x361, "G")
            ()
          }
          
          x4339.update(3, (s_quantity.-(ol_quantity)))
          val x368 = if((s_quantity.<=(ol_quantity))) 
          {
            x4339.+=(3, 91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x370: Int = 0;
          if((ol_supply_w_id.!=(x241))) 
          {
            x370 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x4390 = x799.get(x4339);
          x799.updateCopyDependent(x4339, x4390)
          val c_discount = x4309.get[Double](16);
          val w_tax = x4312.get[Double](8);
          val d_tax = x4315.get[Double](9);
          val x383 = x254;
          val x384 = x249.apply(x383);
          val ol_amount = (((ol_quantity.toDouble).*(x384)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x392 = x254;
          x253.update(x392, ol_amount)
          val x394 = x304;
          x304 = (x394.+(ol_amount))
          val x397 = x254;
          val x400 = GenericEntry.apply("SteNewSEntry", x294, x242, x241, (x397.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          x785.insert(x400)
          val x402 = x254;
          x254 = (x402.+(1))
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
