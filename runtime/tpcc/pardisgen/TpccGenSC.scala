
package tpcc.sc
import ddbt.lib.store._
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 

class SCExecutor 
{
  val x914 = EntryIdx.genericOps(List(1, 2, 3))
  val x919 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3), ({ x18: GenericEntry => {
      val x19 = x18.get[Int](1)
      x19
    }
  })), EntryIdx.genericOps(List(2, 3)))
  val x920 = new Store[GenericEntry](3, x919)
  val x921 = x920.index(0, IHash, true, -1)
  val x922 = x920.index(1, ISliceHeapMin, false, 2)
  val x923 = x920.index(2, INone, false, -1)
  val x926 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List()))
  val x927 = new Store[GenericEntry](1, x926)
  val x928 = x927.index(0, IList, false, -1)
  val x931 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1)))
  val x932 = new Store[GenericEntry](1, x931)
  val x933 = x932.index(0, IHash, true, -1)
  val x934 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1)))
  val x935 = new Store[GenericEntry](1, x934)
  val x936 = x935.index(0, IHash, true, -1)
  val x941 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericCmp(List(2, 3, 4), ({ x210: GenericEntry => {
      val x211 = x210.get[Int](1)
      x211
    }
  })), EntryIdx.genericOps(List(2, 3, 4)))
  val x942 = new Store[GenericEntry](3, x941)
  val x943 = x942.index(0, IHash, true, -1)
  val x944 = x942.index(1, ISliceHeapMax, false, 2)
  val x945 = x942.index(2, INone, false, -1)
  val x947 = Array[Int](1, 1, 11)
  val x949 = Array[Int](2, 1, 2)
  val x953 = Array[EntryIdx[GenericEntry]](EntryIdx.genericFixedRangeOps((Seq(x947, x949))))
  val x954 = new Store[GenericEntry](1, x953)
  val x955 = x954.index(0, IDirect, true, 10)
  val x958 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3, 4)), EntryIdx.genericOps(List(1, 2, 3)))
  val x959 = new Store[GenericEntry](2, x958)
  val x960 = x959.index(0, IHash, true, -1)
  val x961 = x959.index(1, IHash, false, -1)
  val x964 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2, 3)), EntryIdx.genericOps(List(2, 3, 6)))
  val x965 = new Store[GenericEntry](2, x964)
  val x966 = x965.index(0, IHash, true, -1)
  val x967 = x965.index(1, IHash, false, -1)
  val x970 = Array[EntryIdx[GenericEntry]](EntryIdx.genericOps(List(1, 2)))
  val x971 = new Store[GenericEntry](1, x970)
  val x972 = x971.index(0, IHash, true, -1)
  
  val newOrderTbl = x920
  val historyTbl = x927
  val warehouseTbl = x932
  val itemTbl = x935
  val orderTbl = x942
  val districtTbl = x954
  val orderLineTbl = x959
  val customerTbl = x965
  val stockTbl = x971
  val newOrderTxInst = new NewOrderTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val paymentTxInst = new PaymentTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val orderStatusTxInst = new OrderStatusTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val deliveryTxInst = new DeliveryTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)
  val stockLevelTxInst = new StockLevelTx(newOrderTbl,historyTbl,warehouseTbl,itemTbl,orderTbl,districtTbl,orderLineTbl,customerTbl,stockTbl)

      
   
  class DeliveryTx(x920: Store[GenericEntry], x927: Store[GenericEntry], x932: Store[GenericEntry], x935: Store[GenericEntry], x942: Store[GenericEntry], x954: Store[GenericEntry], x959: Store[GenericEntry], x965: Store[GenericEntry], x971: Store[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int) {
    def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) =     {
      val x14 = new Array[Int](10)
      var x15: Int = 1
      while({
        val x16 = x15
        (x16.<=(10))
      })
      {
        val x22 = x15
        val x24 = GenericEntry.apply("SteSampleSEntry", 2, 3, x22, x12)
        val x4826 = x922.get(x24)
        if((x4826.!=(null))) 
        {
          val x28 = x4826.get[Int](1)
          val x29 = x15
          x14.update((x29.-(1)), x28)
          x921.delete(x4826)
          x922.delete(x4826)
          val x33 = x15
          val x34 = GenericEntry("SteSampleSEntry", 1, 2, 3, x28, x33, x12)
          val x4838 = x943.get(x34)
          val x37 = x4838.get[Int](4)
          x4838.update(6, x13)
          x944.update(x4838)
          x943.update(x4838)
          var x40: Double = 0.0
          val x41 = x15
          val x43 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x28, x41, x12)
          x961.slice(x43, ({ x44: GenericEntry => {
              x44.update(7, x11)
              val x46 = x40
              val x47 = x44.get[Double](9)
              x40 = (x46.+(x47))
              x960.update(x44)
              x961.update(x44)
              ()
            }
          }))
          val x53 = x15
          val x54 = GenericEntry("SteSampleSEntry", 1, 2, 3, x37, x53, x12)
          val x4859 = x966.get(x54)
          val x56 = x40
          x4859.+=(17, x56)
          x4859.+=(20, 1)
          x967.update(x4859)
          x966.update(x4859)
          ()
        }
        else
        {
          val x60 = x15
          x14.update((x60.-(1)), 0)
          ()
        }
        
        val x64 = x15
        x15 = (x64.+(1))
        ()
      }
      if(x10) 
      {
        val x68 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
        val x69 = x68.+("\n\n Warehouse: ")
        val x70 = x69.+(x12)
        val x71 = x70.+("\n Carrier:   ")
        val x72 = x71.+(x13)
        val x73 = x72.+("\n\n Delivered Orders\n")
        var x74: String = x73
        var x75: Int = 0
        var x76: Int = 1
        while({
          val x77 = x76
          (x77.<=(10))
        })
        {
          val x79 = x76
          val x81 = x14.apply((x79.-(1)))
          if((x81.>=(0))) 
          {
            val x83 = x74
            val x84 = x83.+("  District ")
            val x85 = x76
            val x87 = if((x85.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            
            val x88 = x84.+(x87)
            val x89 = x76
            val x90 = x88.+(x89)
            val x91 = x90.+(": Order number ")
            val x92 = x76
            val x94 = x14.apply((x92.-(1)))
            val x95 = x91.+(x94)
            val x96 = x95.+(" was delivered.\n")
            x74 = x96
            ()
          }
          else
          {
            val x98 = x74
            val x99 = x98.+("  District ")
            val x100 = x76
            val x102 = if((x100.<(10))) 
            {
              " "
            }
            else
            {
              ""
            }
            
            val x103 = x99.+(x102)
            val x104 = x76
            val x105 = x103.+(x104)
            val x106 = x105.+(": No orders to be delivered.\n")
            x74 = x106
            val x108 = x75
            x75 = (x108.+(1))
            ()
          }
          
          val x112 = x76
          x76 = (x112.+(1))
          ()
        }
        val x116 = x74
        val x117 = x116.+("+-----------------------------------------------------------------+\n\n")
        x74 = x117
        val x119 = x74
        println(x119)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class StockLevelTx(x920: Store[GenericEntry], x927: Store[GenericEntry], x932: Store[GenericEntry], x935: Store[GenericEntry], x942: Store[GenericEntry], x954: Store[GenericEntry], x959: Store[GenericEntry], x965: Store[GenericEntry], x971: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
    def apply(x122: Boolean, x123: Date, x124: Int, x125: Int, x126: Int, x127: Int) =     {
      val x128 = GenericEntry("SteSampleSEntry", 1, 2, x126, x125)
      val x5035 = x955.get(x128)
      val x131 = x5035.get[Int](11)
      var x133: Int = (x131.-(20))
      val x134 = Set.apply[Int]()
      while({
        val x135 = x133
        (x135.<(x131))
      })
      {
        val x137 = x133
        val x139 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x137, x126, x125)
        x961.slice(x139, ({ x140: GenericEntry => {
            val x141 = x140.get[Int](5)
            val x142 = GenericEntry("SteSampleSEntry", 1, 2, x141, x125)
            val x5050 = x972.get(x142)
            val x144 = x5050.get[Int](3)
            if((x144.<(x127))) 
            {
              val x146 = x134.+=(x141)
              ()
            }
            else
            {
              ()
            }
            
            ()
          }
        }))
        val x150 = x133
        x133 = (x150.+(1))
        ()
      }
      val x154 = x134.size
      if(x122) 
      {
        val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x125)
        val x156 = x155.+("\n District:  ")
        val x157 = x156.+(x126)
        val x158 = x157.+("\n\n Stock Level Threshold: ")
        val x159 = x158.+(x127)
        val x160 = x159.+("\n Low Stock Count:       ")
        val x161 = x160.+(x154)
        val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
        println(x162)
        ()
      }
      else
      {
        ()
      }
      
      1
    }
  }
  class OrderStatusTx(x920: Store[GenericEntry], x927: Store[GenericEntry], x932: Store[GenericEntry], x935: Store[GenericEntry], x942: Store[GenericEntry], x954: Store[GenericEntry], x959: Store[GenericEntry], x965: Store[GenericEntry], x971: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
    def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) =     {
      var x173: GenericEntry = null
      if((x170.>(0))) 
      {
        val x175 = new ArrayBuffer[GenericEntry]()
        val x177 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x169, x168, x172)
        x967.slice(x177, ({ x178: GenericEntry => {
            x175.append(x178)
            ()
          }
        }))
        val x182 = x175.size
        var x184: Int = (x182./(2))
        val x185 = x175.size
        if(((x185.%(2)).==(0))) 
        {
          val x188 = x184
          x184 = (x188.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x199 = x175.sortWith(({ (x192: GenericEntry, x193: GenericEntry) => {
            val x194 = x192.get[String](4)
            val x195 = x193.get[String](4)
            val x196 = x194.compareToIgnoreCase(x195)
            (x196.<(0))
          }
        }))
        val x200 = x184
        val x201 = x199.apply(x200)
        x173 = x201
        ()
      }
      else
      {
        val x203 = GenericEntry("SteSampleSEntry", 1, 2, 3, x171, x169, x168)
        val x5140 = x966.get(x203)
        x173 = x5140
        ()
      }
      
      val x208 = x173
      val x209 = x208.get[Int](3)
      val x215 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x169, x168, x209)
      var x218: Int = 0
      1
    }
  }
  class PaymentTx(x920: Store[GenericEntry], x927: Store[GenericEntry], x932: Store[GenericEntry], x935: Store[GenericEntry], x942: Store[GenericEntry], x954: Store[GenericEntry], x959: Store[GenericEntry], x965: Store[GenericEntry], x971: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
    def apply(x219: Boolean, x220: Date, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: Int, x227: Int, x228: String, x229: Double) =     {
      val x230 = GenericEntry("SteSampleSEntry", 1, x222)
      val x5189 = x933.get(x230)
      x5189.+=(9, x229)
      x933.update(x5189)
      val x235 = GenericEntry("SteSampleSEntry", 1, 2, x223, x222)
      val x5194 = x955.get(x235)
      x5194.+=(10, x229)
      x955.update(x5194)
      var x240: GenericEntry = null
      if((x224.>(0))) 
      {
        val x242 = new ArrayBuffer[GenericEntry]()
        val x244 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x226, x225, x228)
        x967.slice(x244, ({ x245: GenericEntry => {
            x242.append(x245)
            ()
          }
        }))
        val x249 = x242.size
        var x251: Int = (x249./(2))
        val x252 = x242.size
        if(((x252.%(2)).==(0))) 
        {
          val x255 = x251
          x251 = (x255.-(1))
          ()
        }
        else
        {
          ()
        }
        
        val x266 = x242.sortWith(({ (x259: GenericEntry, x260: GenericEntry) => {
            val x261 = x259.get[String](4)
            val x262 = x260.get[String](4)
            val x263 = x261.compareToIgnoreCase(x262)
            (x263.<(0))
          }
        }))
        val x267 = x251
        val x268 = x266.apply(x267)
        x240 = x268
        ()
      }
      else
      {
        val x270 = GenericEntry("SteSampleSEntry", 1, 2, 3, x227, x226, x225)
        val x5230 = x966.get(x270)
        x240 = x5230
        ()
      }
      
      val x275 = x240
      val x276 = x275.get[String](21)
      var x277: String = x276
      val x278 = x240
      val x279 = x278.get[String](14)
      val x280 = x279.contains("BC")
      if(x280) 
      {
        val x281 = x240
        val x282 = x281.get[Int](1)
        val x283 = x277
        val x285 = "%d %d %d %d %d $%f %s | %s".format(x282,x226,x225,x223,x222,x229,x220,x283)
        x277 = x285
        val x287 = x277
        val x288 = x287.length
        if((x288.>(500))) 
        {
          val x290 = x277
          val x291 = x290.substring(0, 500)
          x277 = x291
          ()
        }
        else
        {
          ()
        }
        
        val x294 = x240
        x294.+=(17, x229)
        val x296 = x240
        val x297 = x277
        x296.update(21, x297)
        ()
      }
      else
      {
        val x299 = x240
        x299.+=(17, x229)
        ()
      }
      
      val x302 = x240
      x967.update(x302)
      x966.update(x302)
      val x304 = x5189.get[String](2)
      val x305 = x5194.get[String](3)
      val x306 = x304.length
      val x309 = if((x306.>(10))) 
      {
        val x308 = x304.substring(0, 10)
        x308
      }
      else
      {
        x304
      }
      
      val x310 = x309.+("    ")
      val x311 = x305.length
      val x314 = if((x311.>(10))) 
      {
        val x313 = x305.substring(0, 10)
        x313
      }
      else
      {
        x305
      }
      
      val x315 = x310.+(x314)
      val x316 = x240
      val x317 = x316.get[Int](1)
      val x319 = GenericEntry.apply("SteNewSEntry", x317, x226, x225, x223, x222, x220, x229, x315)
      x927.insert(x319)
      1
    }
  }
  class NewOrderTx(x920: Store[GenericEntry], x927: Store[GenericEntry], x932: Store[GenericEntry], x935: Store[GenericEntry], x942: Store[GenericEntry], x954: Store[GenericEntry], x959: Store[GenericEntry], x965: Store[GenericEntry], x971: Store[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
    def apply(x321: Boolean, x322: Date, x323: Int, x324: Int, x325: Int, x326: Int, x327: Int, x328: Int, x329: Array[Int], x330: Array[Int], x331: Array[Int], x332: Array[Double], x333: Array[String], x334: Array[Int], x335: Array[String], x336: Array[Double]) =     {
      if(x321) 
      {
        val x338 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x324,x325,x326)
        println(x338)
        ()
      }
      else
      {
        ()
      }
      
      var x341: Int = 0
      var x342: Boolean = false
      val x343 = new Array[String](x327)
      var x344: Boolean = true
      while({
        val x345 = x341
        ((x345.<(x327)).&&({
          val x347 = x344
          x347
        }))
      })
      {
        val x349 = x341
        val x350 = x329.apply(x349)
        val x351 = GenericEntry("SteSampleSEntry", 1, x350)
        val x5388 = x936.get(x351)
        if((x5388.==(null))) 
        {
          x344 = false
          ()
        }
        else
        {
          val x356 = x341
          val x357 = x5388.get[String](3)
          x333.update(x356, x357)
          val x359 = x341
          val x360 = x5388.get[Double](4)
          x332.update(x359, x360)
          val x362 = x341
          val x363 = x5388.get[String](5)
          x343.update(x362, x363)
          ()
        }
        
        val x366 = x341
        x341 = (x366.+(1))
        ()
      }
      val x370 = x344
      if(x370) 
      {
        val x371 = GenericEntry("SteSampleSEntry", 1, 2, 3, x326, x325, x324)
        val x5408 = x966.get(x371)
        val x374 = GenericEntry("SteSampleSEntry", 1, x324)
        val x5411 = x933.get(x374)
        val x377 = GenericEntry("SteSampleSEntry", 1, 2, x325, x324)
        val x5414 = x955.get(x377)
        val x380 = x5414.get[Int](11)
        x5414.+=(11, 1)
        x955.update(x5414)
        val x385 = GenericEntry.apply("SteNewSEntry", x380, x325, x324, x326, x322, -1, x327, (x328.>(0)))
        x942.insert(x385)
        val x388 = GenericEntry.apply("SteNewSEntry", x380, x325, x324)
        x920.insert(x388)
        var x390: Double = 0.0
        x341 = 0
        while({
          val x392 = x341
          (x392.<(x327))
        })
        {
          val x394 = x341
          val x395 = x330.apply(x394)
          val x396 = x341
          val x397 = x329.apply(x396)
          val x398 = x341
          val x399 = x331.apply(x398)
          val x400 = GenericEntry("SteSampleSEntry", 1, 2, x397, x395)
          val x5437 = x972.get(x400)
          val x429 = if((x325.==(1))) 
          {
            val x403 = x5437.get[String](4)
            x403
          }
          else
          {
            val x428 = if((x325.==(2))) 
            {
              val x405 = x5437.get[String](5)
              x405
            }
            else
            {
              val x427 = if((x325.==(3))) 
              {
                val x407 = x5437.get[String](6)
                x407
              }
              else
              {
                val x426 = if((x325.==(4))) 
                {
                  val x409 = x5437.get[String](7)
                  x409
                }
                else
                {
                  val x425 = if((x325.==(5))) 
                  {
                    val x411 = x5437.get[String](8)
                    x411
                  }
                  else
                  {
                    val x424 = if((x325.==(6))) 
                    {
                      val x413 = x5437.get[String](9)
                      x413
                    }
                    else
                    {
                      val x423 = if((x325.==(7))) 
                      {
                        val x415 = x5437.get[String](10)
                        x415
                      }
                      else
                      {
                        val x422 = if((x325.==(8))) 
                        {
                          val x417 = x5437.get[String](11)
                          x417
                        }
                        else
                        {
                          val x421 = if((x325.==(9))) 
                          {
                            val x419 = x5437.get[String](12)
                            x419
                          }
                          else
                          {
                            val x420 = x5437.get[String](13)
                            x420
                          }
                          
                          x421
                        }
                        
                        x422
                      }
                      
                      x423
                    }
                    
                    x424
                  }
                  
                  x425
                }
                
                x426
              }
              
              x427
            }
            
            x428
          }
          
          val x430 = x5437.get[Int](3)
          val x431 = x341
          x334.update(x431, x430)
          val x433 = x5408.get[String](14)
          val x434 = x433.contains("original")
          if((x434.&&({
            val x435 = x5437.get[String](17)
            val x436 = x435.contains("original")
            x436
          }))) 
          {
            val x438 = x341
            x335.update(x438, "B")
            ()
          }
          else
          {
            val x440 = x341
            x335.update(x440, "G")
            ()
          }
          
          x5437.update(3, (x430.-(x399)))
          if((x430.<=(x399))) 
          {
            x5437.+=(3, 91)
            ()
          }
          else
          {
            ()
          }
          
          var x448: Int = 0
          if((x395.!=(x324))) 
          {
            x448 = 1
            ()
          }
          else
          {
            ()
          }
          
          x972.update(x5437)
          val x453 = x5408.get[Double](16)
          val x454 = x5411.get[Double](8)
          val x455 = x5414.get[Double](9)
          val x456 = x341
          val x457 = x332.apply(x456)
          val x464 = (((x399.toDouble).*(x457)).*(((1.0.+(x454)).+(x455)))).*((1.0.-(x453)))
          val x465 = x341
          x336.update(x465, x464)
          val x467 = x390
          x390 = (x467.+(x464))
          val x470 = x341
          val x473 = GenericEntry.apply("SteNewSEntry", x380, x325, x324, (x470.+(1)), x397, x395, null, x399, x464, x429)
          x959.insert(x473)
          val x475 = x341
          x341 = (x475.+(1))
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
