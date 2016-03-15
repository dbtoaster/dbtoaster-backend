
package ddbt.tpcc.sc
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
    val x22 = x21.==(null)
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
  val x196 = if(x171) 
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
    
    val x189 = x181
    val x190 = x172.apply(x189)
    val x191 = x170 = x190
    x191
  }
  else
  {
    val x193 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x168, x166, x165)
    val x194 = x8.get(0, x193)
    val x195 = x170 = x194
    x195
  }
  
  val x197 = x170
  val x198 = x197.get[Int](3)
  val x200 = GenericEntry.apply("SteSampleSEntry", 2, 3, 4, x166, x165, x198)
  val x201 = x5.getSliceMax(0, x200, 1)
  var x202: Int = 0
  1
}
}
class PaymentTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Int, String, Double) => Int) {
def apply(x203: Boolean, x204: Date, x205: Int, x206: Int, x207: Int, x208: Int, x209: Int, x210: Int, x211: Int, x212: String, x213: Double) = {
  val x215 = GenericEntry.apply("SteSampleSEntry", 1, x206)
  val x216 = x3.get(0, x215)
  val x217 = x216.+=(9, x213)
  val x218 = x3.update(x216)
  val x220 = GenericEntry.apply("SteSampleSEntry", 1, 2, x207, x206)
  val x221 = x6.get(0, x220)
  val x222 = x221.+=(10, x213)
  val x223 = x6.update(x221)
  var x224: GenericEntry = null
  val x225 = x208.>(0)
  val x250 = if(x225) 
  {
    val x226 = new ArrayBuffer[GenericEntry]()
    val x228 = GenericEntry.apply("SteSampleSEntry", 2, 3, 6, x210, x209, x212)
    val x231 = { x229: GenericEntry => {
        val x230 = x226.append(x229)
        x230
      }
    }
    val x232 = x8.slice(0, x228, x231)
    val x233 = x226.size
    val x234 = x233./(2)
    var x235: Int = x234
    val x236 = x226.size
    val x237 = x236.%(2)
    val x238 = x237.==(0)
    val x242 = if(x238) 
    {
      val x239 = x235
      val x240 = x239.-(1)
      val x241 = x235 = x240
      x241
    }
    else
    {
      ()
    }
    
    val x243 = x235
    val x244 = x226.apply(x243)
    val x245 = x224 = x244
    x245
  }
  else
  {
    val x247 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x211, x210, x209)
    val x248 = x8.get(0, x247)
    val x249 = x224 = x248
    x249
  }
  
  val x251 = x224
  val x252 = x251.get[String](21)
  var x253: String = x252
  val x254 = x224
  val x255 = x254.get[String](14)
  val x256 = x255.contains("BC")
  val x277 = if(x256) 
  {
    val x257 = x224
    val x258 = x257.get[Int](1)
    val x259 = x253
    val x261 = "%d %d %d %d %d  $%f %s | %s".format("FIX ME", x258, x210, x209, x207, x206, x213, x204, x259)
    val x262 = x253 = x261
    val x263 = x253
    val x264 = x263.length
    val x265 = x264.>(500)
    val x269 = if(x265) 
    {
      val x266 = x253
      val x267 = x266.substring(0, 500)
      val x268 = x253 = x267
      x268
    }
    else
    {
      ()
    }
    
    val x270 = x224
    val x271 = x270.+=(17, x213)
    val x272 = x224
    val x273 = x253
    val x274 = x272.update(21, x273)
    ()
  }
  else
  {
    val x275 = x224
    val x276 = x275.+=(17, x213)
    x276
  }
  
  val x278 = x224
  val x279 = x8.update(x278)
  val x280 = x216.get[String](2)
  val x281 = x221.get[String](3)
  val x282 = x280.length
  val x283 = x282.>(10)
  val x285 = if(x283) 
  {
    val x284 = x280.substring(0, 10)
    x284
  }
  else
  {
    x280
  }
  
  val x286 = x285.+("    ")
  val x287 = x281.length
  val x288 = x287.>(10)
  val x290 = if(x288) 
  {
    val x289 = x281.substring(0, 10)
    x289
  }
  else
  {
    x281
  }
  
  val x291 = x286.+(x290)
  val x292 = x224
  val x293 = x292.get[Int](1)
  val x295 = GenericEntry.apply("SteNewSEntry", x293, x210, x209, x207, x206, x204, x213, x291)
  val x296 = x2.insert(x295)
  1
}
}
class NewOrderTx(x1:MStore[GenericEntry], x2:MStore[GenericEntry], x3:MStore[GenericEntry], x4:MStore[GenericEntry], x5:MStore[GenericEntry], x6:MStore[GenericEntry], x7:MStore[GenericEntry], x8:MStore[GenericEntry], x9:MStore[GenericEntry]) extends ((Boolean, Date, Int, Int, Int, Int, Int, Int, Array[Int], Array[Int], Array[Int], Array[Double], Array[String], Array[Int], Array[String], Array[Double]) => Int) {
def apply(x297: Boolean, x298: Date, x299: Int, x300: Int, x301: Int, x302: Int, x303: Int, x304: Int, x305: Array[Int], x306: Array[Int], x307: Array[Int], x308: Array[Double], x309: Array[String], x310: Array[Int], x311: Array[String], x312: Array[Double]) = {
  val x314 = if(x297) 
  {
    val x313 = println("Started NewOrder transaction for warehouse=%d, district=%d, customer=%d.format(w_id$macro$2, d_id$macro$3, c_id$macro$4)")
    ()
  }
  else
  {
    ()
  }
  
  var x315: Int = 0
  var x316: Boolean = false
  val x317 = new Array[String](x303)
  var x318: Boolean = true
  val x343 = while({
    val x319 = x315
    val x320 = x319.<(x303)
    val x322 = x320.&&({
      val x321 = x318
      x321
    })
    x322
  })
  {
    val x323 = x315
    val x324 = x305.apply(x323)
    val x326 = GenericEntry.apply("SteSampleSEntry", 1, x324)
    val x327 = x4.get(0, x326)
    val x328 = x327.==(null)
    val x339 = if(x328) 
    {
      val x329 = x318 = false
      ()
    }
    else
    {
      val x330 = x315
      val x331 = x327.get[String](3)
      val x332 = x309.update(x330, x331)
      val x333 = x315
      val x334 = x327.get[Double](4)
      val x335 = x308.update(x333, x334)
      val x336 = x315
      val x337 = x327.get[String](5)
      val x338 = x317.update(x336, x337)
      x338
    }
    
    val x340 = x315
    val x341 = x340.+(1)
    val x342 = x315 = x341
    ()
  }
  val x344 = x318
  val x345 = x344.unary_!
  val x455 = if(x345) 
  {
    val x347 = GenericEntry.apply("SteSampleSEntry", 1, 2, 3, x302, x301, x300)
    val x348 = x8.get(0, x347)
    val x350 = GenericEntry.apply("SteSampleSEntry", 1, x300)
    val x351 = x3.get(0, x350)
    val x353 = GenericEntry.apply("SteSampleSEntry", 1, 2, x301, x300)
    val x354 = x6.get(0, x353)
    val x355 = x354.get[Int](11)
    val x356 = x354.+=(11, 1)
    val x357 = x6.update(x354)
    val x358 = x304.>(0)
    val x360 = GenericEntry.apply("SteNewSEntry", x355, x301, x300, x302, x298, -1, x303, x358)
    val x361 = x5.insert(x360)
    val x363 = GenericEntry.apply("SteNewSEntry", x355, x301, x300)
    val x364 = x1.insert(x363)
    var x365: Double = 0.0
    val x366 = x315 = 0
    val x454 = while({
      val x367 = x315
      val x368 = x367.<(x303)
      x368
    })
    {
      val x369 = x315
      val x370 = x306.apply(x369)
      val x371 = x315
      val x372 = x305.apply(x371)
      val x373 = x315
      val x374 = x307.apply(x373)
      val x376 = GenericEntry.apply("SteSampleSEntry", 1, 2, x372, x370)
      val x377 = x9.get(0, x376)
      val x378 = x301.==(1)
      val x405 = if(x378) 
      {
        val x379 = x377.get[String](4)
        x379
      }
      else
      {
        val x380 = x301.==(2)
        val x404 = if(x380) 
        {
          val x381 = x377.get[String](5)
          x381
        }
        else
        {
          val x382 = x301.==(3)
          val x403 = if(x382) 
          {
            val x383 = x377.get[String](6)
            x383
          }
          else
          {
            val x384 = x301.==(4)
            val x402 = if(x384) 
            {
              val x385 = x377.get[String](7)
              x385
            }
            else
            {
              val x386 = x301.==(5)
              val x401 = if(x386) 
              {
                val x387 = x377.get[String](8)
                x387
              }
              else
              {
                val x388 = x301.==(6)
                val x400 = if(x388) 
                {
                  val x389 = x377.get[String](9)
                  x389
                }
                else
                {
                  val x390 = x301.==(7)
                  val x399 = if(x390) 
                  {
                    val x391 = x377.get[String](10)
                    x391
                  }
                  else
                  {
                    val x392 = x301.==(8)
                    val x398 = if(x392) 
                    {
                      val x393 = x377.get[String](11)
                      x393
                    }
                    else
                    {
                      val x394 = x301.==(9)
                      val x397 = if(x394) 
                      {
                        val x395 = x377.get[String](12)
                        x395
                      }
                      else
                      {
                        val x396 = x377.get[String](13)
                        x396
                      }
                      
                      x397
                    }
                    
                    x398
                  }
                  
                  x399
                }
                
                x400
              }
              
              x401
            }
            
            x402
          }
          
          x403
        }
        
        x404
      }
      
      val x406 = x377.get[Int](3)
      val x407 = x315
      val x408 = x310.update(x407, x406)
      val x409 = x348.get[String](14)
      val x410 = x409.contains("original")
      val x413 = x410.&&({
        val x411 = x377.get[String](17)
        val x412 = x411.contains("original")
        x412
      })
      val x418 = if(x413) 
      {
        val x414 = x315
        val x415 = x311.update(x414, "B")
        ()
      }
      else
      {
        val x416 = x315
        val x417 = x311.update(x416, "G")
        ()
      }
      
      val x419 = x406.-(x374)
      val x420 = x377.update(3, x419)
      val x421 = x406.<=(x374)
      val x423 = if(x421) 
      {
        val x422 = x377.+=(3, 91)
        x422
      }
      else
      {
        ()
      }
      
      var x424: Int = 0
      val x425 = x370.!=(x300)
      val x427 = if(x425) 
      {
        val x426 = x424 = 1
        x426
      }
      else
      {
        ()
      }
      
      val x428 = x9.update(x377)
      val x429 = x348.get[Double](16)
      val x430 = x351.get[Double](8)
      val x431 = x354.get[Double](9)
      val x432 = x315
      val x433 = x308.apply(x432)
      val x434 = x374.toDouble
      val x435 = x434.*(x433)
      val x436 = 1.0.+(x430)
      val x437 = x436.+(x431)
      val x438 = x435.*(x437)
      val x439 = 1.0.-(x429)
      val x440 = x438.*(x439)
      val x441 = x315
      val x442 = x312.update(x441, x440)
      val x443 = x365
      val x444 = x443.+(x440)
      val x445 = x365 = x444
      val x446 = x315
      val x447 = x446.+(1)
      val x449 = GenericEntry.apply("SteNewSEntry", x355, x301, x300, x447, x372, x370, null, x374, x440, x405)
      val x450 = x7.insert(x449)
      val x451 = x315
      val x452 = x451.+(1)
      val x453 = x315 = x452
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
