
package tpcc.sc
import ddbt.lib.store.{Store => MStore, _}
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  
  val x1 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(2, 3)))) 
  x1.index(0,IHash, false, 0)
  
  val x2 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List()))) 
  x2.index(0,IHash, false, 0)
  
  val x3 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(1)))) 
  x3.index(0,IHash, true, 0)
  
  val x4 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(1)))) 
  x4.index(0,IHash, true, 0)
  
  val x5 = new MStore[GenericEntry](2, Array[EntryIdx[GenericEntry]](new GenericOps(List(1, 2, 3)), new GenericOps(List(2, 3, 4)))) 
  x5.index(0,IHash, true, 0)
  x5.index(1,IHash, false, 1)
  
  val x6 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(1, 2)))) 
  x6.index(0,IHash, true, 0)
  
  val x7 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(1, 2, 3)))) 
  x7.index(0,IHash, false, 0)
  
  val x8 = new MStore[GenericEntry](2, Array[EntryIdx[GenericEntry]](new GenericOps(List(1, 2, 3)), new GenericOps(List(2, 3, 6)))) 
  x8.index(0,IHash, true, 0)
  x8.index(1,IHash, false, 1)
  
  val x9 = new MStore[GenericEntry](1, Array[EntryIdx[GenericEntry]](new GenericOps(List(1, 2)))) 
  x9.index(0,IHash, true, 0)
  
    val newOrderTxInst = new NewOrderTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val paymentTxInst = new PaymentTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val orderStatusTxInst = new OrderStatusTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val deliveryTxInst = new DeliveryTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val stockLevelTxInst = new StockLevelTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
}
      
class NewOrderTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x319: Boolean, x320: Date, x321: Int, x322: Int, x323: Int, x324: Int, x325: Int, x326: Int, x327: Array[Int], x328: Array[Int], x329: Array[Int], x330: Array[Double], x331: Array[String], x332: Array[Int], x333: Array[String], x334: Array[Double]) = {
  val x338 = if(x319) 
  {
    val x336 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x322,x323,x324)
    val x337 = println(x336)
    x337
  }
  else
  {
    ()
  }
  
  var x339: Int = 0
  var x340: Boolean = false
  val x341 = new Array[String](x325)
  var x342: Boolean = true
  val x367 = while({
    val x343 = x339
    val x344 = x343.<(x325)
    val x346 = x344.&&({
      val x345 = x342
      x345
    })
    x346
  })
  {
    val x347 = x339
    val x348 = x327.apply(x347)
    val x350 = GenericEntry.apply("SteSampleSEntry", 1, x348)
    val x351 = x4.get(0, x350)
    val x352 = x351.==(null)
    val x363 = if(x352) 
    {
      val x353 = x342 = false
      ()
    }
    else
    {
      val x354 = x339
      val x355 = x351.get[String](3)
      val x356 = x331.update(x354, x355)
      val x357 = x339
      val x358 = x351.get[Double](4)
      val x359 = x330.update(x357, x358)
      val x360 = x339
      val x361 = x351.get[String](5)
      val x362 = x341.update(x360, x361)
      x362
    }
    
    val x364 = x339
    val x365 = x364.+(1)
    val x366 = x339 = x365
    ()
  }
  val x368 = x342
  val x478 = if(x368) 
  {
    val x370 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x324, x323, x322)
    val x371 = x8.get(0, x370)
    val x373 = GenericEntry.apply("SteSampleSEntry", 1, x322)
    val x374 = x3.get(0, x373)
    val x376 = GenericEntry.apply("SteSampleSEntry", 1, 2, x323, x322)
    val x377 = x6.get(0, x376)
    val x378 = x377.get[Int](11)
    val x379 = x377.+=(11, 1)
    val x380 = x6.update(x377)
    val x381 = x326.>(0)
    val x383 = GenericEntry.apply("SteNewSEntry", x378, x323, x322, x324, x320, -1, x325, x381)
    val x384 = x5.insert(x383)
    val x386 = GenericEntry.apply("SteNewSEntry", x378, x323, x322)
    val x387 = x1.insert(x386)
    var x388: Double = 0.0
    val x389 = x339 = 0
    val x477 = while({
      val x390 = x339
      val x391 = x390.<(x325)
      x391
    })
    {
      val x392 = x339
      val x393 = x328.apply(x392)
      val x394 = x339
      val x395 = x327.apply(x394)
      val x396 = x339
      val x397 = x329.apply(x396)
      val x399 = GenericEntry.apply("SteSampleSEntry", 1, 2, x395, x393)
      val x400 = x9.get(0, x399)
      val x401 = x323.==(1)
      val x428 = if(x401) 
      {
        val x402 = x400.get[String](4)
        x402
      }
      else
      {
        val x403 = x323.==(2)
        val x427 = if(x403) 
        {
          val x404 = x400.get[String](5)
          x404
        }
        else
        {
          val x405 = x323.==(3)
          val x426 = if(x405) 
          {
            val x406 = x400.get[String](6)
            x406
          }
          else
          {
            val x407 = x323.==(4)
            val x425 = if(x407) 
            {
              val x408 = x400.get[String](7)
              x408
            }
            else
            {
              val x409 = x323.==(5)
              val x424 = if(x409) 
              {
                val x410 = x400.get[String](8)
                x410
              }
              else
              {
                val x411 = x323.==(6)
                val x423 = if(x411) 
                {
                  val x412 = x400.get[String](9)
                  x412
                }
                else
                {
                  val x413 = x323.==(7)
                  val x422 = if(x413) 
                  {
                    val x414 = x400.get[String](10)
                    x414
                  }
                  else
                  {
                    val x415 = x323.==(8)
                    val x421 = if(x415) 
                    {
                      val x416 = x400.get[String](11)
                      x416
                    }
                    else
                    {
                      val x417 = x323.==(9)
                      val x420 = if(x417) 
                      {
                        val x418 = x400.get[String](12)
                        x418
                      }
                      else
                      {
                        val x419 = x400.get[String](13)
                        x419
                      }
                      
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
      
      val x429 = x400.get[Int](3)
      val x430 = x339
      val x431 = x332.update(x430, x429)
      val x432 = x371.get[String](14)
      val x433 = x432.contains("original")
      val x436 = x433.&&({
        val x434 = x400.get[String](17)
        val x435 = x434.contains("original")
        x435
      })
      val x441 = if(x436) 
      {
        val x437 = x339
        val x438 = x333.update(x437, "B")
        ()
      }
      else
      {
        val x439 = x339
        val x440 = x333.update(x439, "G")
        ()
      }
      
      val x442 = x429.-(x397)
      val x443 = x400.update(3, x442)
      val x444 = x429.<=(x397)
      val x446 = if(x444) 
      {
        val x445 = x400.+=(3, 91)
        x445
      }
      else
      {
        ()
      }
      
      var x447: Int = 0
      val x448 = x393.!=(x322)
      val x450 = if(x448) 
      {
        val x449 = x447 = 1
        x449
      }
      else
      {
        ()
      }
      
      val x451 = x9.update(x400)
      val x452 = x371.get[Double](16)
      val x453 = x374.get[Double](8)
      val x454 = x377.get[Double](9)
      val x455 = x339
      val x456 = x330.apply(x455)
      val x457 = x397.toDouble
      val x458 = x457.*(x456)
      val x459 = 1.0.+(x453)
      val x460 = x459.+(x454)
      val x461 = x458.*(x460)
      val x462 = 1.0.-(x452)
      val x463 = x461.*(x462)
      val x464 = x339
      val x465 = x334.update(x464, x463)
      val x466 = x388
      val x467 = x466.+(x463)
      val x468 = x388 = x467
      val x469 = x339
      val x470 = x469.+(1)
      val x472 = GenericEntry.apply("SteNewSEntry", x378, x323, x322, x470, x395, x393, null, x397, x463, x428)
      val x473 = x7.insert(x472)
      val x474 = x339
      val x475 = x474.+(1)
      val x476 = x339 = x475
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
class StockLevelTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int) => Int) {
def apply(x121: Boolean, x122: Date, x123: Int, x124: Int, x125: Int, x126: Int) = {
  val x128 = GenericEntry.apply("SteSampleSEntry", 1, 2, x125, x124)
  val x129 = x6.get(0, x128)
  val x130 = x129.get[Int](11)
  val x131 = x130.-(20)
  var x132: Int = x131
  val x133 = Set.apply[Int]()
  val x153 = while({
    val x134 = x132
    val x135 = x134.<(x130)
    x135
  })
  {
    val x136 = x132
    val x138 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x136, x125, x124)
    val x148 = { x139: GenericEntry => {
        val x140 = x139.get[Int](5)
        val x142 = GenericEntry.apply("SteSampleSEntry", 1, 2, x140, x124)
        val x143 = x9.get(0, x142)
        val x144 = x143.get[Int](3)
        val x145 = x144.<(x126)
        val x147 = if(x145) 
        {
          val x146 = x133.+=(x140)
          ()
        }
        else
        {
          ()
        }
        
        x147
      }
    }
    val x149 = x7.slice(0, x138, x148)
    val x150 = x132
    val x151 = x150.+(1)
    val x152 = x132 = x151
    x152
  }
  val x154 = x133.size
  val x164 = if(x121) 
  {
    val x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x124)
    val x156 = x155.+("\n District:  ")
    val x157 = x156.+(x125)
    val x158 = x157.+("\n\n Stock Level Threshold: ")
    val x159 = x158.+(x126)
    val x160 = x159.+("\n Low Stock Count:       ")
    val x161 = x160.+(x154)
    val x162 = x161.+("\n+-----------------------------------------------------------------+\n\n")
    val x163 = println(x162)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class DeliveryTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  val x66 = while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x18 = new Aggregator[GenericEntry]()
    val x19 = x15
    val x21 = GenericEntry.apply("SteSampleSEntry", 2, 3, x19, x12)
    val x22 = x18.gather
    val x23 = x1.slice(0, x21, x22)
    val x24 = x18.min(1)
    val x25 = x24.!=(null)
    val x62 = if(x25) 
    {
      val x26 = x24.get[Int](1)
      val x27 = x15
      val x28 = x27.-(1)
      val x29 = x14.update(x28, x26)
      val x30 = x1.delete(x24)
      val x31 = x15
      val x33 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x26, x31, x12)
      val x34 = x5.get(0, x33)
      val x35 = x34.get[Int](4)
      val x36 = x34.update(6, x13)
      val x37 = x5.update(x34)
      var x38: Double = 0.0
      val x39 = x15
      val x41 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x26, x39, x12)
      val x49 = { x42: GenericEntry => {
          val x43 = x42.update(7, x11)
          val x44 = x38
          val x45 = x42.get[Double](9)
          val x46 = x44.+(x45)
          val x47 = x38 = x46
          val x48 = x7.update(x42)
          x48
        }
      }
      val x50 = x7.slice(0, x41, x49)
      val x51 = x15
      val x53 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x35, x51, x12)
      val x54 = x8.get(0, x53)
      val x55 = x38
      val x56 = x54.+=(17, x55)
      val x57 = x54.+=(20, 1)
      val x58 = x8.update(x54)
      x58
    }
    else
    {
      val x59 = x15
      val x60 = x59.-(1)
      val x61 = x14.update(x60, 0)
      x61
    }
    
    val x63 = x15
    val x64 = x63.+(1)
    val x65 = x15 = x64
    x65
  }
  val x120 = if(x10) 
  {
    val x67 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
    val x68 = x67.+("\n\n Warehouse: ")
    val x69 = x68.+(x12)
    val x70 = x69.+("\n Carrier:   ")
    val x71 = x70.+(x13)
    val x72 = x71.+("\n\n Delivered Orders\n")
    var x73: String = x72
    var x74: Int = 0
    var x75: Int = 1
    val x114 = while({
      val x76 = x75
      val x77 = x76.<=(10)
      x77
    })
    {
      val x78 = x75
      val x79 = x78.-(1)
      val x80 = x14.apply(x79)
      val x81 = x80.>=(0)
      val x110 = if(x81) 
      {
        val x82 = x73
        val x83 = x82.+("  District ")
        val x84 = x75
        val x85 = x84.<(10)
        val x86 = if(x85) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x87 = x83.+(x86)
        val x88 = x75
        val x89 = x87.+(x88)
        val x90 = x89.+(": Order number ")
        val x91 = x75
        val x92 = x91.-(1)
        val x93 = x14.apply(x92)
        val x94 = x90.+(x93)
        val x95 = x94.+(" was delivered.\n")
        val x96 = x73 = x95
        x96
      }
      else
      {
        val x97 = x73
        val x98 = x97.+("  District ")
        val x99 = x75
        val x100 = x99.<(10)
        val x101 = if(x100) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x102 = x98.+(x101)
        val x103 = x75
        val x104 = x102.+(x103)
        val x105 = x104.+(": No orders to be delivered.\n")
        val x106 = x73 = x105
        val x107 = x74
        val x108 = x107.+(1)
        val x109 = x74 = x108
        x109
      }
      
      val x111 = x75
      val x112 = x111.+(1)
      val x113 = x75 = x112
      x113
    }
    val x115 = x73
    val x116 = x115.+("+-----------------------------------------------------------------+\n\n")
    val x117 = x73 = x116
    val x118 = x73
    val x119 = println(x118)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class PaymentTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x217: Boolean, x218: Date, x219: Int, x220: Int, x221: Int, x222: Int, x223: Int, x224: Int, x225: Int, x226: String, x227: Double) = {
  val x229 = GenericEntry.apply("SteSampleSEntry", 1, x220)
  val x230 = x3.get(0, x229)
  val x231 = x230.+=(9, x227)
  val x232 = x3.update(x230)
  val x234 = GenericEntry.apply("SteSampleSEntry", 1, 2, x221, x220)
  val x235 = x6.get(0, x234)
  val x236 = x235.+=(10, x227)
  val x237 = x6.update(x235)
  var x238: GenericEntry = null
  val x239 = x222.>(0)
  val x272 = if(x239) 
  {
    val x240 = new ArrayBuffer[GenericEntry]()
    val x242 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x224, x223, x226)
    val x245 = { x243: GenericEntry => {
        val x244 = x240.append(x243)
        x244
      }
    }
    val x246 = x8.slice(1, x242, x245)
    val x247 = x240.size
    val x248 = x247./(2)
    var x249: Int = x248
    val x250 = x240.size
    val x251 = x250.%(2)
    val x252 = x251.==(0)
    val x256 = if(x252) 
    {
      val x253 = x249
      val x254 = x253.-(1)
      val x255 = x249 = x254
      x255
    }
    else
    {
      ()
    }
    
    val x263 = { (x257: GenericEntry, x258: GenericEntry) => {
        val x259 = x257.get[String](4)
        val x260 = x258.get[String](4)
        val x261 = x259.compareToIgnoreCase(x260)
        val x262 = x261.<(0)
        x262
      }
    }
    val x264 = x240.sortWith(x263)
    val x265 = x249
    val x266 = x264.apply(x265)
    val x267 = x238 = x266
    x267
  }
  else
  {
    val x269 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x225, x224, x223)
    val x270 = x8.get(0, x269)
    val x271 = x238 = x270
    x271
  }
  
  val x273 = x238
  val x274 = x273.get[String](21)
  var x275: String = x274
  val x276 = x238
  val x277 = x276.get[String](14)
  val x278 = x277.contains("BC")
  val x299 = if(x278) 
  {
    val x279 = x238
    val x280 = x279.get[Int](1)
    val x281 = x275
    val x283 = "%d %d %d %d %d $%f %s | %s".format(x280,x224,x223,x221,x220,x227,x218,x281)
    val x284 = x275 = x283
    val x285 = x275
    val x286 = x285.length
    val x287 = x286.>(500)
    val x291 = if(x287) 
    {
      val x288 = x275
      val x289 = x288.substring(0, 500)
      val x290 = x275 = x289
      x290
    }
    else
    {
      ()
    }
    
    val x292 = x238
    val x293 = x292.+=(17, x227)
    val x294 = x238
    val x295 = x275
    val x296 = x294.update(21, x295)
    ()
  }
  else
  {
    val x297 = x238
    val x298 = x297.+=(17, x227)
    x298
  }
  
  val x300 = x238
  val x301 = x8.update(x300)
  val x302 = x230.get[String](2)
  val x303 = x235.get[String](3)
  val x304 = x302.length
  val x305 = x304.>(10)
  val x307 = if(x305) 
  {
    val x306 = x302.substring(0, 10)
    x306
  }
  else
  {
    x302
  }
  
  val x308 = x307.+("    ")
  val x309 = x303.length
  val x310 = x309.>(10)
  val x312 = if(x310) 
  {
    val x311 = x303.substring(0, 10)
    x311
  }
  else
  {
    x303
  }
  
  val x313 = x308.+(x312)
  val x314 = x238
  val x315 = x314.get[Int](1)
  val x317 = GenericEntry.apply("SteNewSEntry", x315, x224, x223, x221, x220, x218, x227, x313)
  val x318 = x2.insert(x317)
  1
}
}
class OrderStatusTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x165: Boolean, x166: Date, x167: Int, x168: Int, x169: Int, x170: Int, x171: Int, x172: String) = {
  var x173: GenericEntry = null
  val x174 = x170.>(0)
  val x207 = if(x174) 
  {
    val x175 = new ArrayBuffer[GenericEntry]()
    val x177 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x169, x168, x172)
    val x180 = { x178: GenericEntry => {
        val x179 = x175.append(x178)
        x179
      }
    }
    val x181 = x8.slice(1, x177, x180)
    val x182 = x175.size
    val x183 = x182./(2)
    var x184: Int = x183
    val x185 = x175.size
    val x186 = x185.%(2)
    val x187 = x186.==(0)
    val x191 = if(x187) 
    {
      val x188 = x184
      val x189 = x188.-(1)
      val x190 = x184 = x189
      x190
    }
    else
    {
      ()
    }
    
    val x198 = { (x192: GenericEntry, x193: GenericEntry) => {
        val x194 = x192.get[String](4)
        val x195 = x193.get[String](4)
        val x196 = x194.compareToIgnoreCase(x195)
        val x197 = x196.<(0)
        x197
      }
    }
    val x199 = x175.sortWith(x198)
    val x200 = x184
    val x201 = x199.apply(x200)
    val x202 = x173 = x201
    x202
  }
  else
  {
    val x204 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x171, x169, x168)
    val x205 = x8.get(0, x204)
    val x206 = x173 = x205
    x206
  }
  
  val x208 = x173
  val x209 = x208.get[Int](3)
  val x210 = new Aggregator[GenericEntry]()
  val x212 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x169, x168, x209)
  val x213 = x210.gather
  val x214 = x5.slice(1, x212, x213)
  val x215 = x210.max(1)
  var x216: Int = 0
  1
}
}
