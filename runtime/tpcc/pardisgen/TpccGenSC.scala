
package tpcc.sc
import ddbt.lib.store.{Store => MStore, _}
import scala.collection.mutable.{ArrayBuffer,Set}
import java.util.Date
 class SCExecutor 
{
  val x1 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x1.index(0,IHash,true)
  
  val x2 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x2.index(0,IHash,true)
  
  val x3 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x3.index(0,IHash,true)
  
  val x4 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x4.index(0,IHash,true)
  
  val x5 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x5.index(0,IHash,true)
  
  val x6 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x6.index(0,IHash,true)
  
  val x7 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x7.index(0,IHash,true)
  
  val x8 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x8.index(0,IHash,true)
  
  val x9 = new MStore[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))
  x9.index(0,IHash,true)
  
  
    val newOrderTxInst = new NewOrderTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val paymentTxInst = new PaymentTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val orderStatusTxInst = new OrderStatusTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val deliveryTxInst = new DeliveryTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
    val stockLevelTxInst = new StockLevelTx(x1, x2, x3, x4, x5, x6, x7, x8, x9)
}
      
class DeliveryTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int) => Int) {
def apply(x10: Boolean, x11: Date, x12: Int, x13: Int) = {
  val x14 = new Array[Int](10)
  var x15: Int = 1
  val x63 = while({
    val x16 = x15
    val x17 = x16.<=(10)
    x17
  })
  {
    val x18 = x15
    val x20 = GenericEntry.apply("SteSampleSEntry", 2, 3, x18, x12)
    val x21 = x1.getSliceMin(0, x20, 1)
    val x22 = x21.!=(null)
    val x59 = if(x22) 
    {
      val x23 = x21.get[Int](1)
      val x24 = x15
      val x25 = x24.-(1)
      val x26 = x14.update(x25, x23)
      val x27 = x1.delete(x21)
      val x28 = x15
      val x30 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x23, x28, x12)
      val x31 = x5.get(0, x30)
      val x32 = x31.get[Int](4)
      val x33 = x31.update(6, x13)
      val x34 = x5.update(x31)
      var x35: Double = 0.0
      val x36 = x15
      val x38 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x23, x36, x12)
      val x46 = { x39: GenericEntry => {
          val x40 = x39.update(7, x11)
          val x41 = x35
          val x42 = x39.get[Double](9)
          val x43 = x41.+(x42)
          val x44 = x35 = x43
          val x45 = x7.update(x39)
          x45
        }
      }
      val x47 = x7.slice(0, x38, x46)
      val x48 = x15
      val x50 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x32, x48, x12)
      val x51 = x8.get(0, x50)
      val x52 = x35
      val x53 = x51.+=(17, x52)
      val x54 = x51.+=(20, 1)
      val x55 = x8.update(x51)
      x55
    }
    else
    {
      val x56 = x15
      val x57 = x56.-(1)
      val x58 = x14.update(x57, 0)
      x58
    }
    
    val x60 = x15
    val x61 = x60.+(1)
    val x62 = x15 = x61
    x62
  }
  val x117 = if(x10) 
  {
    val x64 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: ".+(x11)
    val x65 = x64.+("\n\n Warehouse: ")
    val x66 = x65.+(x12)
    val x67 = x66.+("\n Carrier:   ")
    val x68 = x67.+(x13)
    val x69 = x68.+("\n\n Delivered Orders\n")
    var x70: String = x69
    var x71: Int = 0
    var x72: Int = 1
    val x111 = while({
      val x73 = x72
      val x74 = x73.<=(10)
      x74
    })
    {
      val x75 = x72
      val x76 = x75.-(1)
      val x77 = x14.apply(x76)
      val x78 = x77.>=(0)
      val x107 = if(x78) 
      {
        val x79 = x70
        val x80 = x79.+("  District ")
        val x81 = x72
        val x82 = x81.<(10)
        val x83 = if(x82) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x84 = x80.+(x83)
        val x85 = x72
        val x86 = x84.+(x85)
        val x87 = x86.+(": Order number ")
        val x88 = x72
        val x89 = x88.-(1)
        val x90 = x14.apply(x89)
        val x91 = x87.+(x90)
        val x92 = x91.+(" was delivered.\n")
        val x93 = x70 = x92
        x93
      }
      else
      {
        val x94 = x70
        val x95 = x94.+("  District ")
        val x96 = x72
        val x97 = x96.<(10)
        val x98 = if(x97) 
        {
          " "
        }
        else
        {
          ""
        }
        
        val x99 = x95.+(x98)
        val x100 = x72
        val x101 = x99.+(x100)
        val x102 = x101.+(": No orders to be delivered.\n")
        val x103 = x70 = x102
        val x104 = x71
        val x105 = x104.+(1)
        val x106 = x71 = x105
        x106
      }
      
      val x108 = x72
      val x109 = x108.+(1)
      val x110 = x72 = x109
      x110
    }
    val x112 = x70
    val x113 = x112.+("+-----------------------------------------------------------------+\n\n")
    val x114 = x70 = x113
    val x115 = x70
    val x116 = println(x115)
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
def apply(x118: Boolean, x119: Date, x120: Int, x121: Int, x122: Int, x123: Int) = {
  val x125 = GenericEntry.apply("SteSampleSEntry", 1, 2, x122, x121)
  val x126 = x6.get(0, x125)
  val x127 = x126.get[Int](11)
  val x128 = x127.-(20)
  var x129: Int = x128
  val x130 = Set.apply[Int]()
  val x150 = while({
    val x131 = x129
    val x132 = x131.<(x127)
    x132
  })
  {
    val x133 = x129
    val x135 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x133, x122, x121)
    val x145 = { x136: GenericEntry => {
        val x137 = x136.get[Int](5)
        val x139 = GenericEntry.apply("SteSampleSEntry", 1, 2, x137, x121)
        val x140 = x9.get(0, x139)
        val x141 = x140.get[Int](3)
        val x142 = x141.<(x123)
        val x144 = if(x142) 
        {
          val x143 = x130.+=(x137)
          ()
        }
        else
        {
          ()
        }
        
        x144
      }
    }
    val x146 = x7.slice(0, x135, x145)
    val x147 = x129
    val x148 = x147.+(1)
    val x149 = x129 = x148
    x149
  }
  val x151 = x130.size
  val x161 = if(x118) 
  {
    val x152 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: ".+(x121)
    val x153 = x152.+("\n District:  ")
    val x154 = x153.+(x122)
    val x155 = x154.+("\n\n Stock Level Threshold: ")
    val x156 = x155.+(x123)
    val x157 = x156.+("\n Low Stock Count:       ")
    val x158 = x157.+(x151)
    val x159 = x158.+("\n+-----------------------------------------------------------------+\n\n")
    val x160 = println(x159)
    ()
  }
  else
  {
    ()
  }
  
  1
}
}
class OrderStatusTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, String) => Int) {
def apply(x162: Boolean, x163: Date, x164: Int, x165: Int, x166: Int, x167: Int, x168: Int, x169: String) = {
  var x170: GenericEntry = null
  val x171 = x167.>(0)
  val x204 = if(x171) 
  {
    val x172 = new ArrayBuffer[GenericEntry]()
    val x174 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x166, x165, x169)
    val x177 = { x175: GenericEntry => {
        val x176 = x172.append(x175)
        x176
      }
    }
    val x178 = x8.slice(0, x174, x177)
    val x179 = x172.size
    val x180 = x179./(2)
    var x181: Int = x180
    val x182 = x172.size
    val x183 = x182.%(2)
    val x184 = x183.==(0)
    val x188 = if(x184) 
    {
      val x185 = x181
      val x186 = x185.-(1)
      val x187 = x181 = x186
      x187
    }
    else
    {
      ()
    }
    
    val x195 = { (x189: GenericEntry, x190: GenericEntry) => {
        val x191 = x189.get[String](4)
        val x192 = x190.get[String](4)
        val x193 = x191.compareToIgnoreCase(x192)
        val x194 = x193.<(0)
        x194
      }
    }
    val x196 = x172.sortWith(x195)
    val x197 = x181
    val x198 = x196.apply(x197)
    val x199 = x170 = x198
    x199
  }
  else
  {
    val x201 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x168, x166, x165)
    val x202 = x8.get(0, x201)
    val x203 = x170 = x202
    x203
  }
  
  val x205 = x170
  val x206 = x205.get[Int](3)
  val x208 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x166, x165, x206)
  val x209 = x5.getSliceMax(0, x208, 1)
  var x210: Int = 0
  1
}
}
class PaymentTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x211: Boolean, x212: Date, x213: Int, x214: Int, x215: Int, x216: Int, x217: Int, x218: Int, x219: Int, x220: String, x221: Double) = {
  val x223 = GenericEntry.apply("SteSampleSEntry", 1, x214)
  val x224 = x3.get(0, x223)
  val x225 = x224.+=(9, x221)
  val x226 = x3.update(x224)
  val x228 = GenericEntry.apply("SteSampleSEntry", 1, 2, x215, x214)
  val x229 = x6.get(0, x228)
  val x230 = x229.+=(10, x221)
  val x231 = x6.update(x229)
  var x232: GenericEntry = null
  val x233 = x216.>(0)
  val x266 = if(x233) 
  {
    val x234 = new ArrayBuffer[GenericEntry]()
    val x236 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x218, x217, x220)
    val x239 = { x237: GenericEntry => {
        val x238 = x234.append(x237)
        x238
      }
    }
    val x240 = x8.slice(0, x236, x239)
    val x241 = x234.size
    val x242 = x241./(2)
    var x243: Int = x242
    val x244 = x234.size
    val x245 = x244.%(2)
    val x246 = x245.==(0)
    val x250 = if(x246) 
    {
      val x247 = x243
      val x248 = x247.-(1)
      val x249 = x243 = x248
      x249
    }
    else
    {
      ()
    }
    
    val x257 = { (x251: GenericEntry, x252: GenericEntry) => {
        val x253 = x251.get[String](4)
        val x254 = x252.get[String](4)
        val x255 = x253.compareToIgnoreCase(x254)
        val x256 = x255.<(0)
        x256
      }
    }
    val x258 = x234.sortWith(x257)
    val x259 = x243
    val x260 = x258.apply(x259)
    val x261 = x232 = x260
    x261
  }
  else
  {
    val x263 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x219, x218, x217)
    val x264 = x8.get(0, x263)
    val x265 = x232 = x264
    x265
  }
  
  val x267 = x232
  val x268 = x267.get[String](21)
  var x269: String = x268
  val x270 = x232
  val x271 = x270.get[String](14)
  val x272 = x271.contains("BC")
  val x293 = if(x272) 
  {
    val x273 = x232
    val x274 = x273.get[Int](1)
    val x275 = x269
    val x277 = "%d %d %d %d %d $%f %s | %s".format(x274,x218,x217,x215,x214,x221,x212,x275)
    val x278 = x269 = x277
    val x279 = x269
    val x280 = x279.length
    val x281 = x280.>(500)
    val x285 = if(x281) 
    {
      val x282 = x269
      val x283 = x282.substring(0, 500)
      val x284 = x269 = x283
      x284
    }
    else
    {
      ()
    }
    
    val x286 = x232
    val x287 = x286.+=(17, x221)
    val x288 = x232
    val x289 = x269
    val x290 = x288.update(21, x289)
    ()
  }
  else
  {
    val x291 = x232
    val x292 = x291.+=(17, x221)
    x292
  }
  
  val x294 = x232
  val x295 = x8.update(x294)
  val x296 = x224.get[String](2)
  val x297 = x229.get[String](3)
  val x298 = x296.length
  val x299 = x298.>(10)
  val x301 = if(x299) 
  {
    val x300 = x296.substring(0, 10)
    x300
  }
  else
  {
    x296
  }
  
  val x302 = x301.+("    ")
  val x303 = x297.length
  val x304 = x303.>(10)
  val x306 = if(x304) 
  {
    val x305 = x297.substring(0, 10)
    x305
  }
  else
  {
    x297
  }
  
  val x307 = x302.+(x306)
  val x308 = x232
  val x309 = x308.get[Int](1)
  val x311 = GenericEntry.apply("SteNewSEntry", x309, x218, x217, x215, x214, x212, x221, x307)
  val x312 = x2.insert(x311)
  1
}
}
class NewOrderTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x313: Boolean, x314: Date, x315: Int, x316: Int, x317: Int, x318: Int, x319: Int, x320: Int, x321: Array[Int], x322: Array[Int], x323: Array[Int], x324: Array[Double], x325: Array[String], x326: Array[Int], x327: Array[String], x328: Array[Double]) = {
  val x332 = if(x313) 
  {
    val x330 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x316,x317,x318)
    val x331 = println(x330)
    x331
  }
  else
  {
    ()
  }
  
  var x333: Int = 0
  var x334: Boolean = false
  val x335 = new Array[String](x319)
  var x336: Boolean = true
  val x361 = while({
    val x337 = x333
    val x338 = x337.<(x319)
    val x340 = x338.&&({
      val x339 = x336
      x339
    })
    x340
  })
  {
    val x341 = x333
    val x342 = x321.apply(x341)
    val x344 = GenericEntry.apply("SteSampleSEntry", 1, x342)
    val x345 = x4.get(0, x344)
    val x346 = x345.==(null)
    val x357 = if(x346) 
    {
      val x347 = x336 = false
      ()
    }
    else
    {
      val x348 = x333
      val x349 = x345.get[String](3)
      val x350 = x325.update(x348, x349)
      val x351 = x333
      val x352 = x345.get[Double](4)
      val x353 = x324.update(x351, x352)
      val x354 = x333
      val x355 = x345.get[String](5)
      val x356 = x335.update(x354, x355)
      x356
    }
    
    val x358 = x333
    val x359 = x358.+(1)
    val x360 = x333 = x359
    ()
  }
  val x362 = x336
  val x475 = if(x362) 
  {
    val x364 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x318, x317, x316)
    val x365 = x8.get(0, x364)
    val x367 = GenericEntry.apply("SteSampleSEntry", 1, x316)
    val x368 = x3.get(0, x367)
    val x370 = GenericEntry.apply("SteSampleSEntry", 1, 2, x317, x316)
    val x371 = x6.get(0, x370)
    val x372 = x371.get[Int](11)
    val x373 = x371.+=(11, 1)
    val x374 = x6.update(x371)
    val x375 = x320.>(0)
    val x377 = GenericEntry.apply("SteNewSEntry", x372, x317, x316, x318, x314, -1, x319, x375)
    val x378 = x5.insert(x377)
    val x380 = GenericEntry.apply("SteNewSEntry", x372, x317, x316)
    val x381 = x1.insert(x380)
    val x383 = "NewOrder transaction for warehouse=%d, district=%d, customer=%d, o_id=%d".format(x316,x317,x318,x372)
    val x384 = println(x383)
    var x385: Double = 0.0
    val x386 = x333 = 0
    val x474 = while({
      val x387 = x333
      val x388 = x387.<(x319)
      x388
    })
    {
      val x389 = x333
      val x390 = x322.apply(x389)
      val x391 = x333
      val x392 = x321.apply(x391)
      val x393 = x333
      val x394 = x323.apply(x393)
      val x396 = GenericEntry.apply("SteSampleSEntry", 1, 2, x392, x390)
      val x397 = x9.get(0, x396)
      val x398 = x317.==(1)
      val x425 = if(x398) 
      {
        val x399 = x397.get[String](4)
        x399
      }
      else
      {
        val x400 = x317.==(2)
        val x424 = if(x400) 
        {
          val x401 = x397.get[String](5)
          x401
        }
        else
        {
          val x402 = x317.==(3)
          val x423 = if(x402) 
          {
            val x403 = x397.get[String](6)
            x403
          }
          else
          {
            val x404 = x317.==(4)
            val x422 = if(x404) 
            {
              val x405 = x397.get[String](7)
              x405
            }
            else
            {
              val x406 = x317.==(5)
              val x421 = if(x406) 
              {
                val x407 = x397.get[String](8)
                x407
              }
              else
              {
                val x408 = x317.==(6)
                val x420 = if(x408) 
                {
                  val x409 = x397.get[String](9)
                  x409
                }
                else
                {
                  val x410 = x317.==(7)
                  val x419 = if(x410) 
                  {
                    val x411 = x397.get[String](10)
                    x411
                  }
                  else
                  {
                    val x412 = x317.==(8)
                    val x418 = if(x412) 
                    {
                      val x413 = x397.get[String](11)
                      x413
                    }
                    else
                    {
                      val x414 = x317.==(9)
                      val x417 = if(x414) 
                      {
                        val x415 = x397.get[String](12)
                        x415
                      }
                      else
                      {
                        val x416 = x397.get[String](13)
                        x416
                      }
                      
                      x417
                    }
                    
                    x418
                  }
                  
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
      
      val x426 = x397.get[Int](3)
      val x427 = x333
      val x428 = x326.update(x427, x426)
      val x429 = x365.get[String](14)
      val x430 = x429.contains("original")
      val x433 = x430.&&({
        val x431 = x397.get[String](17)
        val x432 = x431.contains("original")
        x432
      })
      val x438 = if(x433) 
      {
        val x434 = x333
        val x435 = x327.update(x434, "B")
        ()
      }
      else
      {
        val x436 = x333
        val x437 = x327.update(x436, "G")
        ()
      }
      
      val x439 = x426.-(x394)
      val x440 = x397.update(3, x439)
      val x441 = x426.<=(x394)
      val x443 = if(x441) 
      {
        val x442 = x397.+=(3, 91)
        x442
      }
      else
      {
        ()
      }
      
      var x444: Int = 0
      val x445 = x390.!=(x316)
      val x447 = if(x445) 
      {
        val x446 = x444 = 1
        x446
      }
      else
      {
        ()
      }
      
      val x448 = x9.update(x397)
      val x449 = x365.get[Double](16)
      val x450 = x368.get[Double](8)
      val x451 = x371.get[Double](9)
      val x452 = x333
      val x453 = x324.apply(x452)
      val x454 = x394.toDouble
      val x455 = x454.*(x453)
      val x456 = 1.0.+(x450)
      val x457 = x456.+(x451)
      val x458 = x455.*(x457)
      val x459 = 1.0.-(x449)
      val x460 = x458.*(x459)
      val x461 = x333
      val x462 = x328.update(x461, x460)
      val x463 = x385
      val x464 = x463.+(x460)
      val x465 = x385 = x464
      val x466 = x333
      val x467 = x466.+(1)
      val x469 = GenericEntry.apply("SteNewSEntry", x372, x317, x316, x467, x392, x390, null, x394, x460, x425)
      val x470 = x7.insert(x469)
      val x471 = x333
      val x472 = x471.+(1)
      val x473 = x333 = x472
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
