
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x737 = EntryIdx.genericOps(List(1, 2, 3));
  val x742 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), ({ x18: GenericEntry => {
      val x19 = x18.get[Int](1);
      x19
    }
  })), EntryIdx.genericOps(List(2, 3)))
  val x743 = new Store[GenericEntry](3, x742);
  val x744 = x743.index(0, IHash, true, -1)
  val x745 = x743.index(1, ISliceHeapMin, false, 2)
  val x746 = x743.index(2, INone, false, -1)
  val x749 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val x750 = new Store[GenericEntry](1, x749);
  val x751 = x750.index(0, IList, false, -1)
  val x754 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,2))))
  val x755 = new Store[GenericEntry](1, x754);
  val x756 = x755.index(0, IDirect, true, 1)
  val x759 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001))))
  val x760 = new Store[GenericEntry](1, x759);
  val x761 = x760.index(0, IDirect, true, 100000)
  val x766 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), ({ x145: GenericEntry => {
      val x146 = x145.get[Int](1);
      x146
    }
  })), EntryIdx.genericOps(List(2, 3, 4)))
  val x767 = new Store[GenericEntry](3, x766);
  val x768 = x767.index(0, IHash, true, -1)
  val x769 = x767.index(1, ISliceHeapMax, false, 2)
  val x770 = x767.index(2, INone, false, -1)
  val x773 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,11), (2,1,2))))
  val x774 = new Store[GenericEntry](1, x773);
  val x775 = x774.index(0, IDirect, true, 10)
  val x778 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val x779 = new Store[GenericEntry](2, x778);
  val x780 = x779.index(0, IHash, true, -1)
  val x781 = x779.index(1, IHash, false, -1)
  val x785 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,3001), (2,1,11), (3,1,2))), EntryIdx.genericOps(List(2, 3, 6)))
  val x786 = new Store[GenericEntry](2, x785);
  val x787 = x786.index(0, IDirect, true, 30000)
  val x788 = x786.index(1, IHash, false, -1)
  val x791 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps(List((1,1,100001), (2,1,2))))
  val x792 = new Store[GenericEntry](1, x791);
  val x793 = x792.index(0, IDirect, true, 100000)
  
  val newOrderTbl = x743
  val historyTbl = x750
  val warehouseTbl = x755
  val itemTbl = x760
  val orderTbl = x767
  val districtTbl = x774
  val orderLineTbl = x779
  val customerTbl = x786
  val stockTbl = x792
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   
  class DeliveryTx(x743: Store[GenericEntry], x750: Store[GenericEntry], x755: Store[GenericEntry], x760: Store[GenericEntry], x767: Store[GenericEntry], x774: Store[GenericEntry], x779: Store[GenericEntry], x786: Store[GenericEntry], x792: Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int ) {
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
        val x3915 = x745.get(x24);
        if((x3915.!=(null))) 
        {
          val x28 = x3915.get[Int](1);
          val x29 = x15;
          x14.update((x29.-(1)), x28)
          x743.delete(x3915)
          val x33 = x15;
          val x34 = GenericEntry("SteSampleSEntry", 1, 2, 3, x28, x33, x12);
          val x3926 = x768.get(x34);
          val x37 = x3926.get[Int](4);
          x3926.update(6, x13)
          x769.update(x3926)
          x768.update(x3926)
          var x40: Double = 0.0;
          val x41 = x15;
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x28, x41, x12);
          x781.slice(x43, ({ orderLineEntry: GenericEntry => {
              orderLineEntry.update(7, x11)
              val x46 = x40;
              val x47 = orderLineEntry.get[Double](9);
              x40 = (x46.+(x47))
              x780.update(orderLineEntry)
              x781.update(orderLineEntry)
              ()
            }
          }))
          val x53 = x15;
          val x54 = GenericEntry("SteSampleSEntry", 1, 2, 3, x37, x53, x12);
          val x3947 = x787.get(x54);
          val x56 = x40;
          x3947.+=(17, x56)
          x3947.+=(20, 1)
          x788.update(x3947)
          x787.update(x3947)
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
  class StockLevelTx(x743: Store[GenericEntry], x750: Store[GenericEntry], x755: Store[GenericEntry], x760: Store[GenericEntry], x767: Store[GenericEntry], x774: Store[GenericEntry], x779: Store[GenericEntry], x786: Store[GenericEntry], x792: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int ) {
    def apply(x68 : Boolean, x69 : Date, x70 : Int, x71 : Int, x72 : Int, x73 : Int) =     {
      val x74 = GenericEntry("SteSampleSEntry", 1, 2, x72, x71);
      val x4014 = x775.get(x74);
      val x77 = x4014.get[Int](11);
      var x79: Int = (x77.-(20));
      val x80 = Set.apply[Int]();
      while({
        val x81 = x79;
        (x81.<(x77))
      })
      {
        val x83 = x79;
        val x85 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x83, x72, x71);
        x781.slice(x85, ({ x86: GenericEntry => {
            val x87 = x86.get[Int](5);
            val x88 = GenericEntry("SteSampleSEntry", 1, 2, x87, x71);
            val x4029 = x793.get(x88);
            val x90 = x4029.get[Int](3);
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
  class OrderStatusTx(x743: Store[GenericEntry], x750: Store[GenericEntry], x755: Store[GenericEntry], x760: Store[GenericEntry], x767: Store[GenericEntry], x774: Store[GenericEntry], x779: Store[GenericEntry], x786: Store[GenericEntry], x792: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int ) {
    def apply(x101 : Boolean, x102 : Date, x103 : Int, x104 : Int, x105 : Int, x106 : Int, x107 : Int, x108 : String) =     {
      val x143 = if((x106.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x113 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x105, x104, x108);
        x788.slice(x113, ({ custEntry: GenericEntry => {
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
        val x4095 = x787.get(x140);
        x4095
      }
      ;
      val x144 = x143.get[Int](3);
      val x150 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x105, x104, x144);
      val x4100 = x769.get(x150);
      var x153: Int = 0;
      val x154 = x4100.get[Int](1);
      x153 = x154
      1
    }
  }
  class PaymentTx(x743: Store[GenericEntry], x750: Store[GenericEntry], x755: Store[GenericEntry], x760: Store[GenericEntry], x767: Store[GenericEntry], x774: Store[GenericEntry], x779: Store[GenericEntry], x786: Store[GenericEntry], x792: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int ) {
    def apply(x156 : Boolean, x157 : Date, x158 : Int, x159 : Int, x160 : Int, x161 : Int, x162 : Int, x163 : Int, x164 : Int, x165 : String, x166 : Double) =     {
      val x167 = GenericEntry("SteSampleSEntry", 1, x159);
      val x4146 = x756.get(x167);
      x4146.+=(9, x166)
      x756.update(x4146)
      val x172 = GenericEntry("SteSampleSEntry", 1, 2, x160, x159);
      val x4151 = x775.get(x172);
      x4151.+=(10, x166)
      x775.update(x4151)
      val x211 = if((x161.>(0))) 
      {
        val customersWithLastName = new ArrayBuffer[GenericEntry]();
        val x181 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x163, x162, x165);
        x788.slice(x181, ({ custEntry: GenericEntry => {
            customersWithLastName.append(custEntry)
            ()
          }
        }))
        val x187 = customersWithLastName.size;
        var x189: Int = (x187./(2));
        val x191 = customersWithLastName.size;
        if(((x191.%(2)).==(0))) 
        {
          val x194 = x189;
          x189 = (x194.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x205 = customersWithLastName.sortWith(({ (c1: GenericEntry, c2: GenericEntry) => {
            val x200 = c1.get[String](4);
            val x201 = c2.get[String](4);
            ((StringExtra.StringCompare(x200, x201)).<(0))
          }
        }));
        val x206 = x189;
        val x207 = x205.apply(x206);
        x207
      }
      else
      {
        val x208 = GenericEntry("SteSampleSEntry", 1, 2, 3, x164, x163, x162);
        val x4185 = x787.get(x208);
        x4185
      }
      ;
      val x212 = x211.get[String](21);
      val x213 = x211.get[String](14);
      val x214 = x213.contains("BC");
      if(x214) 
      {
        val x215 = x211.get[Int](1);
        var x218 = "%d %d %d %d %d $%f %s | %s".format(x215,x163,x162,x160,x159,x166,(x157.toString()),x212)
        if(x218.size > 500) 
          x218 = x218.substring(0, 500)
        x211.+=(17, x166)
        x211.update(21, x218)
        ()
      }
      else
      {
        x211.+=(17, x166)
        ()
      }
      
      x788.update(x211)
      x787.update(x211)
      val x224 = x4146.get[String](2);
      val x225 = x4151.get[String](3);
      var x227 = "%.10s    %.10s".format(x224,x225)
      if(x227.size > 24) 
        x227 = x227.substring(0, 24)
      val x228 = x211.get[Int](1);
      val x230 = GenericEntry.apply("SteNewSEntry", x228, x163, x162, x160, x159, x157, x166, x227);
      x750.insert(x230)
      1
    }
  }
  class NewOrderTx(x743: Store[GenericEntry], x750: Store[GenericEntry], x755: Store[GenericEntry], x760: Store[GenericEntry], x767: Store[GenericEntry], x774: Store[GenericEntry], x779: Store[GenericEntry], x786: Store[GenericEntry], x792: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int ) {
    def apply(x232 : Boolean, x233 : Date, x234 : Int, x235 : Int, x236 : Int, x237 : Int, x238 : Int, x239 : Int, x240 : Array[Int], x241 : Array[Int], x242 : Array[Int], x243 : Array[Double], x244 : Array[String], x245 : Array[Int], x246 : Array[String], x247 : Array[Double]) =     {
      var x248: Int = 0;
      var x249: Boolean = false;
      val x250 = new Array[String](x238);
      var x251: Boolean = true;
      while({
        val x252 = x248;
        ((x252.<(x238)).&&({
          val x254 = x251;
          x254
        }))
      })
      {
        val x257 = x248;
        val x258 = x240.apply(x257);
        val x259 = GenericEntry("SteSampleSEntry", 1, x258);
        val x4283 = x761.get(x259);
        if((x4283.==(null))) 
        {
          x251 = false
          ()
        }
        else
        {
          val x264 = x248;
          val x265 = x4283.get[String](3);
          x244.update(x264, x265)
          val x267 = x248;
          val x268 = x4283.get[Double](4);
          x243.update(x267, x268)
          val x270 = x248;
          val x271 = x4283.get[String](5);
          x250.update(x270, x271)
          ()
        }
        
        val x274 = x248;
        x248 = (x274.+(1))
        ()
      }
      val x278 = x251;
      if(x278) 
      {
        val x279 = GenericEntry("SteSampleSEntry", 1, 2, 3, x237, x236, x235);
        val x4303 = x787.get(x279);
        val x282 = GenericEntry("SteSampleSEntry", 1, x235);
        val x4306 = x756.get(x282);
        val x285 = GenericEntry("SteSampleSEntry", 1, 2, x236, x235);
        val x4309 = x775.get(x285);
        val x288 = x4309.get[Int](11);
        x4309.+=(11, 1)
        x775.update(x4309)
        val x293 = GenericEntry.apply("SteNewSEntry", x288, x236, x235, x237, x233, -1, x238, (x239.>(0)));
        x767.insert(x293)
        val x296 = GenericEntry.apply("SteNewSEntry", x288, x236, x235);
        x743.insert(x296)
        var x298: Double = 0.0;
        x248 = 0
        while({
          val x300 = x248;
          (x300.<(x238))
        })
        {
          val x303 = x248;
          val ol_supply_w_id = x241.apply(x303);
          val x306 = x248;
          val ol_i_id = x240.apply(x306);
          val x309 = x248;
          val ol_quantity = x242.apply(x309);
          val x313 = GenericEntry.apply("SteSampleSEntry", 1, 2, ol_i_id, ol_supply_w_id);
          val x4333 = x793.get(x313);
          val ol_dist_info = if((x236.==(1))) 
          {
            val x317 = x4333.get[String](4);
            x317
          }
          else
          {
            val x342 = if((x236.==(2))) 
            {
              val x319 = x4333.get[String](5);
              x319
            }
            else
            {
              val x341 = if((x236.==(3))) 
              {
                val x321 = x4333.get[String](6);
                x321
              }
              else
              {
                val x340 = if((x236.==(4))) 
                {
                  val x323 = x4333.get[String](7);
                  x323
                }
                else
                {
                  val x339 = if((x236.==(5))) 
                  {
                    val x325 = x4333.get[String](8);
                    x325
                  }
                  else
                  {
                    val x338 = if((x236.==(6))) 
                    {
                      val x327 = x4333.get[String](9);
                      x327
                    }
                    else
                    {
                      val x337 = if((x236.==(7))) 
                      {
                        val x329 = x4333.get[String](10);
                        x329
                      }
                      else
                      {
                        val x336 = if((x236.==(8))) 
                        {
                          val x331 = x4333.get[String](11);
                          x331
                        }
                        else
                        {
                          val x335 = if((x236.==(9))) 
                          {
                            val x333 = x4333.get[String](12);
                            x333
                          }
                          else
                          {
                            val x334 = x4333.get[String](13);
                            x334
                          }
                          ;
                          x335
                        }
                        ;
                        x336
                      }
                      ;
                      x337
                    }
                    ;
                    x338
                  }
                  ;
                  x339
                }
                ;
                x340
              }
              ;
              x341
            }
            ;
            x342
          }
          ;
          val s_quantity = x4333.get[Int](3);
          val x346 = x248;
          x245.update(x346, s_quantity)
          val x348 = x4303.get[String](14);
          val x349 = x348.contains("original");
          if((x349.&&({
            val x350 = x4333.get[String](17);
            val x351 = x350.contains("original");
            x351
          }))) 
          {
            val x353 = x248;
            x246.update(x353, "B")
            ()
          }
          else
          {
            val x355 = x248;
            x246.update(x355, "G")
            ()
          }
          
          x4333.update(3, (s_quantity.-(ol_quantity)))
          val x362 = if((s_quantity.<=(ol_quantity))) 
          {
            x4333.+=(3, 91)
            ()
          }
          else
          {
            ()
          }
          ;
          var x364: Int = 0;
          if((ol_supply_w_id.!=(x235))) 
          {
            x364 = 1
            ()
          }
          else
          {
            ()
          }
          
          val x4384 = x793.get(x4333);
          x793.updateCopyDependent(x4333, x4384)
          val c_discount = x4303.get[Double](16);
          val w_tax = x4306.get[Double](8);
          val d_tax = x4309.get[Double](9);
          val x377 = x248;
          val x378 = x243.apply(x377);
          val ol_amount = (((ol_quantity.toDouble).*(x378)).*(((1.0.+(w_tax)).+(d_tax)))).*((1.0.-(c_discount)));
          val x386 = x248;
          x247.update(x386, ol_amount)
          val x388 = x298;
          x298 = (x388.+(ol_amount))
          val x391 = x248;
          val x394 = GenericEntry.apply("SteNewSEntry", x288, x236, x235, (x391.+(1)), ol_i_id, ol_supply_w_id, null, ol_quantity, ol_amount, ol_dist_info);
          x779.insert(x394)
          val x396 = x248;
          x248 = (x396.+(1))
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
