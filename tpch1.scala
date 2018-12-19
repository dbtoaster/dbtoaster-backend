package ddbt.gen
    
import ddbt.lib._
import akka.actor.Actor
import ddbt.lib.store._


object Tpch1 {
  import Helper._

  

  def execute(args: Array[String], f: List[Any] => Unit) = 
    bench(args, (dataset: String, parallelMode: Int, timeout: Long, batchSize: Int) => run[Tpch1](
      Seq(
        (new java.io.FileInputStream("/home/gerald/DBtoaster/dbtoaster-experiments-data/tpch/standard/lineitem.csv"),new Adaptor.CSV("LINEITEM","long,long,long,long,double,double,double,double,string,string,date,date,date,string,string,string","\\Q|\\E", "insert"),Split())
      ), 
      parallelMode, timeout, batchSize), f)

  def main(args: Array[String]) {

    val argMap = parseArgs(args)
    
    execute(args, (res: List[Any]) => {
      if (!argMap.contains("noOutput")) {
        println("<snap>")
        println("<SUM_QTY>\n" + M3Map.toStr(res(0), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</SUM_QTY>\n")
        println("<SUM_BASE_PRICE>\n" + M3Map.toStr(res(1), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</SUM_BASE_PRICE>\n")
        println("<SUM_DISC_PRICE>\n" + M3Map.toStr(res(2), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</SUM_DISC_PRICE>\n")
        println("<SUM_CHARGE>\n" + M3Map.toStr(res(3), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</SUM_CHARGE>\n")
        println("<AVG_QTY>\n" + M3Map.toStr(res(4), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</AVG_QTY>\n")
        println("<AVG_PRICE>\n" + M3Map.toStr(res(5), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</AVG_PRICE>\n")
        println("<AVG_DISC>\n" + M3Map.toStr(res(6), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</AVG_DISC>\n")
        println("<COUNT_ORDER>\n" + M3Map.toStr(res(7), List("LINEITEM_RETURNFLAG", "LINEITEM_LINESTATUS"))+"\n" + "</COUNT_ORDER>\n")
        println("</snap>")
      }
    })
  }  
}
class Tpch1Base {
  import Tpch1._
  import ddbt.lib.Functions._

  case class SEntry3_SSD(var _1: String, var _2: String, var _3: Double) extends Entry(3) {def this() = this(null, null, -1.7976931348623157E308) ; def copy = SEntry3_SSD(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_SSD]; _1 = that._1;_2 = that._2;_3 = that._3} }
  case class SEntry3_SSL(var _1: String, var _2: String, var _3: Long) extends Entry(3) {def this() = this(null, null, -2147483648L) ; def copy = SEntry3_SSL(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_SSL]; _1 = that._1;_2 = that._2;_3 = that._3} }
   object SEntry3_SSL_Idx12 extends EntryIdx[SEntry3_SSL] {
    override def hash(x8051 : SEntry3_SSL) = {
      var x8052: Int = 0;
      val x8053 = x8052;
      x8052 = (x8053.^((((((x8051._1).hashCode()).+(-1640531527)).+((x8053.<<(6)))).+((x8053.>>(2))))))
      val x8063 = x8052;
      x8052 = (x8063.^((((((x8051._2).hashCode()).+(-1640531527)).+((x8063.<<(6)))).+((x8063.>>(2))))))
      val x8073 = x8052;
      x8073
    }
    override def cmp(x8075 : SEntry3_SSL , x8076 : SEntry3_SSL) = {
      var x8077: Int = 0;
      if(((x8075._1).==((x8076._1)))) {
        if(((x8075._2).==((x8076._2)))) {
          x8077 = 0
        } else {
          x8077 = 1
        }
      } else {
        x8077 = 1
      }
      val x8089 = x8077;
      x8089
    }
  }
   object SEntry3_SSD_Idx12 extends EntryIdx[SEntry3_SSD] {
    override def hash(x8096 : SEntry3_SSD) = {
      var x8097: Int = 0;
      val x8098 = x8097;
      x8097 = (x8098.^((((((x8096._1).hashCode()).+(-1640531527)).+((x8098.<<(6)))).+((x8098.>>(2))))))
      val x8108 = x8097;
      x8097 = (x8108.^((((((x8096._2).hashCode()).+(-1640531527)).+((x8108.<<(6)))).+((x8108.>>(2))))))
      val x8118 = x8097;
      x8118
    }
    override def cmp(x8120 : SEntry3_SSD , x8121 : SEntry3_SSD) = {
      var x8122: Int = 0;
      if(((x8120._1).==((x8121._1)))) {
        if(((x8120._2).==((x8121._2)))) {
          x8122 = 0
        } else {
          x8122 = 1
        }
      } else {
        x8122 = 1
      }
      val x8134 = x8122;
      x8134
    }
  }
  
  val x8093 = Array[EntryIdx[SEntry3_SSL]](SEntry3_SSL_Idx12)
  val COUNT_ORDER = new Store[SEntry3_SSL](1, x8093);
  val COUNT_ORDERIdx0 = COUNT_ORDER.index(0, IHash, true, -1)
  val x8138 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val SUM_BASE_PRICE = new Store[SEntry3_SSD](1, x8138);
  val SUM_BASE_PRICEIdx0 = SUM_BASE_PRICE.index(0, IHash, true, -1)
  val x8141 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val SUM_CHARGE = new Store[SEntry3_SSD](1, x8141);
  val SUM_CHARGEIdx0 = SUM_CHARGE.index(0, IHash, true, -1)
  val x8144 = Array[EntryIdx[SEntry3_SSL]](SEntry3_SSL_Idx12)
  val AVG_QTY_mLINEITEM1_L1_1 = new Store[SEntry3_SSL](1, x8144);
  val AVG_QTY_mLINEITEM1_L1_1Idx0 = AVG_QTY_mLINEITEM1_L1_1.index(0, IHash, true, -1)
  val x8147 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_QTY = new Store[SEntry3_SSD](1, x8147);
  val AVG_QTYIdx0 = AVG_QTY.index(0, IHash, true, -1)
  val x8150 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val SUM_QTY = new Store[SEntry3_SSD](1, x8150);
  val SUM_QTYIdx0 = SUM_QTY.index(0, IHash, true, -1)
  val x8153 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_PRICE = new Store[SEntry3_SSD](1, x8153);
  val AVG_PRICEIdx0 = AVG_PRICE.index(0, IHash, true, -1)
  val x8156 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_DISC_mLINEITEM2 = new Store[SEntry3_SSD](1, x8156);
  val AVG_DISC_mLINEITEM2Idx0 = AVG_DISC_mLINEITEM2.index(0, IHash, true, -1)
  val x8159 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_PRICE_mLINEITEM2 = new Store[SEntry3_SSD](1, x8159);
  val AVG_PRICE_mLINEITEM2Idx0 = AVG_PRICE_mLINEITEM2.index(0, IHash, true, -1)
  val x8162 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val SUM_DISC_PRICE = new Store[SEntry3_SSD](1, x8162);
  val SUM_DISC_PRICEIdx0 = SUM_DISC_PRICE.index(0, IHash, true, -1)
  val x8165 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_DISC = new Store[SEntry3_SSD](1, x8165);
  val AVG_DISCIdx0 = AVG_DISC.index(0, IHash, true, -1)
  val x8168 = Array[EntryIdx[SEntry3_SSD]](SEntry3_SSD_Idx12)
  val AVG_QTY_mLINEITEM2 = new Store[SEntry3_SSD](1, x8168);
  val AVG_QTY_mLINEITEM2Idx0 = AVG_QTY_mLINEITEM2.index(0, IHash, true, -1)
  
  
  
  val x8499 = SEntry3_SSL(null, null, -2147483648L);
  val x9390 = SEntry3_SSL(null, null, -2147483648L);
  val x9315 = SEntry3_SSL(null, null, -2147483648L);
  val x9200 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8534 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9405 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8426 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9065 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9334 = SEntry3_SSL(null, null, -2147483648L);
  val x9259 = SEntry3_SSL(null, null, -2147483648L);
  val x9119 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9144 = SEntry3_SSL(null, null, -2147483648L);
  val x8455 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9420 = SEntry3_SSL(null, null, -2147483648L);
  val x9309 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9375 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9125 = SEntry3_SSL(null, null, -2147483648L);
  val x9105 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8309 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8347 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9295 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8612 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8461 = SEntry3_SSL(null, null, -2147483648L);
  val x8327 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8519 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9220 = SEntry3_SSL(null, null, -2147483648L);
  val x8548 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8554 = SEntry3_SSL(null, null, -2147483648L);
  val x8386 = SEntry3_SSL(null, null, -2147483648L);
  val x8479 = SEntry3_SSL(null, null, -2147483648L);
  val x8367 = SEntry3_SSL(null, null, -2147483648L);
  val x9049 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9084 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8406 = SEntry3_SSL(null, null, -2147483648L);
  val x8294 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8592 = SEntry3_SSL(null, null, -2147483648L);
  val x8572 = SEntry3_SSL(null, null, -2147483648L);
  val x9354 = SEntry3_SSL(null, null, -2147483648L);
  val x8626 = SEntry3_SSL(null, null, -2147483648L);
  val x8441 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8361 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9214 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8641 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x9280 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  val x8655 = SEntry3_SSL(null, null, -2147483648L);
  val x9239 = SEntry3_SSL(null, null, -2147483648L);
  val x9164 = SEntry3_SSL(null, null, -2147483648L);
  val x9185 = SEntry3_SSD(null, null, -1.7976931348623157E308);
  def onAddLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      val x30 = c1.>=(lineitem_shipdate);
      if(x30) {
        x8294._1_=(lineitem_returnflag)
        x8294._2_=(lineitem_linestatus)
        x8294._3_=(lineitem_quantity)
        val x8295 = x8294._3;
        if((x8295.==(0.0))) {
        } else {
          val x12704 = SUM_QTYIdx0.get(x8294);
          if((x12704.==(null))) {
            SUM_QTY.unsafeInsert(x8294)
          } else {
            x12704._3 +=(x8295)
            if(((x12704._3).==(0.0))) {
              SUM_QTY.delete(x12704)
            } else {
            }
          }
        }
      } else {
      }
      if(x30) {
        x8309._1_=(lineitem_returnflag)
        x8309._2_=(lineitem_linestatus)
        x8309._3_=(lineitem_extendedprice)
        val x8310 = x8309._3;
        if((x8310.==(0.0))) {
        } else {
          val x12721 = SUM_BASE_PRICEIdx0.get(x8309);
          if((x12721.==(null))) {
            SUM_BASE_PRICE.unsafeInsert(x8309)
          } else {
            x12721._3 +=(x8310)
            if(((x12721._3).==(0.0))) {
              SUM_BASE_PRICE.delete(x12721)
            } else {
            }
          }
        }
      } else {
      }
      if(x30) {
        x8327._1_=(lineitem_returnflag)
        x8327._2_=(lineitem_linestatus)
        x8327._3_=((lineitem_extendedprice.*((1L.+((lineitem_discount.unary_-))))))
        val x8328 = x8327._3;
        if((x8328.==(0.0))) {
        } else {
          val x12741 = SUM_DISC_PRICEIdx0.get(x8327);
          if((x12741.==(null))) {
            SUM_DISC_PRICE.unsafeInsert(x8327)
          } else {
            x12741._3 +=(x8328)
            if(((x12741._3).==(0.0))) {
              SUM_DISC_PRICE.delete(x12741)
            } else {
            }
          }
        }
      } else {
      }
      if(x30) {
        x8347._1_=(lineitem_returnflag)
        x8347._2_=(lineitem_linestatus)
        x8347._3_=((lineitem_extendedprice.*(((1L.+((lineitem_discount.unary_-))).*((1L.+(lineitem_tax)))))))
        val x8348 = x8347._3;
        if((x8348.==(0.0))) {
        } else {
          val x12763 = SUM_CHARGEIdx0.get(x8347);
          if((x12763.==(null))) {
            SUM_CHARGE.unsafeInsert(x8347)
          } else {
            x12763._3 +=(x8348)
            if(((x12763._3).==(0.0))) {
              SUM_CHARGE.delete(x12763)
            } else {
            }
          }
        }
      } else {
      }
      x8361._1_=(lineitem_returnflag)
      x8361._2_=(lineitem_linestatus)
      val x12775 = AVG_QTY_mLINEITEM2Idx0.get(x8361);
      val x103 = if((x12775.==(null))) {
      0.0
      } else {
      (x12775._3)
      };
      var x104: Double = 0.0;
      x8367._1_=(lineitem_returnflag)
      x8367._2_=(lineitem_linestatus)
      val x12782 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8367);
      val x109 = if((x12782.==(null))) {
      0L
      } else {
      (x12782._3)
      };
      val x110 = if(x30) 1L else 0L;
      val x111 = x109.+(x110);
      val x114 = if((1L.>(x111))) {
      1L
      } else {
      x111
      };
      val x117 = if((0.==(x114))) {
      0.0
      } else {
      (1.0./(x114))
      };
      val x118 = if((0L.!=(x111))) {
      x117
      } else {
      0.0
      };
      val x119 = x104;
      x104 = (x119.+(x118))
      val x122 = x104;
      var x123: Double = 0.0;
      x8386._1_=(lineitem_returnflag)
      x8386._2_=(lineitem_linestatus)
      val x12802 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8386);
      val x128 = if((x12802.==(null))) {
      0L
      } else {
      (x12802._3)
      };
      val x131 = if((1L.>(x128))) {
      1L
      } else {
      x128
      };
      val x134 = if((0.==(x131))) {
      0.0
      } else {
      (1.0./(x131))
      };
      val x135 = if((0L.!=(x128))) {
      x134
      } else {
      0.0
      };
      val x136 = x123;
      x123 = (x136.+(x135))
      val x139 = x123;
      var x143: Double = 0.0;
      x8406._1_=(lineitem_returnflag)
      x8406._2_=(lineitem_linestatus)
      val x12823 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8406);
      val x148 = if((x12823.==(null))) {
      0L
      } else {
      (x12823._3)
      };
      val x149 = x148.+(1L);
      val x152 = if((1L.>(x149))) {
      1L
      } else {
      x149
      };
      val x155 = if((0.==(x152))) {
      0.0
      } else {
      (1.0./(x152))
      };
      val x156 = if((0L.!=(x149))) {
      x155
      } else {
      0.0
      };
      val x157 = x143;
      x143 = (x157.+(x156))
      val x160 = x143;
      val x162 = if(x30) {
      (x160.*(lineitem_quantity))
      } else {
      0.0
      };
      x8426._1_=(lineitem_returnflag)
      x8426._2_=(lineitem_linestatus)
      x8426._3_=(((x103.*((x122.+((x139.unary_-))))).+(x162)))
      val x8427 = x8426._3;
      if((x8427.==(0.0))) {
      } else {
        val x12848 = AVG_QTYIdx0.get(x8426);
        if((x12848.==(null))) {
          AVG_QTY.unsafeInsert(x8426)
        } else {
          x12848._3 +=(x8427)
          if(((x12848._3).==(0.0))) {
            AVG_QTY.delete(x12848)
          } else {
          }
        }
      }
      if(x30) {
        x8441._1_=(lineitem_returnflag)
        x8441._2_=(lineitem_linestatus)
        x8441._3_=(lineitem_quantity)
        val x8442 = x8441._3;
        if((x8442.==(0.0))) {
        } else {
          val x12865 = AVG_QTY_mLINEITEM2Idx0.get(x8441);
          if((x12865.==(null))) {
            AVG_QTY_mLINEITEM2.unsafeInsert(x8441)
          } else {
            x12865._3 +=(x8442)
            if(((x12865._3).==(0.0))) {
              AVG_QTY_mLINEITEM2.delete(x12865)
            } else {
            }
          }
        }
      } else {
      }
      x8455._1_=(lineitem_returnflag)
      x8455._2_=(lineitem_linestatus)
      val x12877 = AVG_PRICE_mLINEITEM2Idx0.get(x8455);
      val x197 = if((x12877.==(null))) {
      0.0
      } else {
      (x12877._3)
      };
      var x198: Double = 0.0;
      x8461._1_=(lineitem_returnflag)
      x8461._2_=(lineitem_linestatus)
      val x12884 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8461);
      val x203 = if((x12884.==(null))) {
      0L
      } else {
      (x12884._3)
      };
      val x204 = x203.+(x110);
      val x207 = if((1L.>(x204))) {
      1L
      } else {
      x204
      };
      val x210 = if((0.==(x207))) {
      0.0
      } else {
      (1.0./(x207))
      };
      val x211 = if((0L.!=(x204))) {
      x210
      } else {
      0.0
      };
      val x212 = x198;
      x198 = (x212.+(x211))
      val x215 = x198;
      var x216: Double = 0.0;
      x8479._1_=(lineitem_returnflag)
      x8479._2_=(lineitem_linestatus)
      val x12903 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8479);
      val x221 = if((x12903.==(null))) {
      0L
      } else {
      (x12903._3)
      };
      val x224 = if((1L.>(x221))) {
      1L
      } else {
      x221
      };
      val x227 = if((0.==(x224))) {
      0.0
      } else {
      (1.0./(x224))
      };
      val x228 = if((0L.!=(x221))) {
      x227
      } else {
      0.0
      };
      val x229 = x216;
      x216 = (x229.+(x228))
      val x232 = x216;
      var x236: Double = 0.0;
      x8499._1_=(lineitem_returnflag)
      x8499._2_=(lineitem_linestatus)
      val x12924 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8499);
      val x241 = if((x12924.==(null))) {
      0L
      } else {
      (x12924._3)
      };
      val x242 = x241.+(1L);
      val x245 = if((1L.>(x242))) {
      1L
      } else {
      x242
      };
      val x248 = if((0.==(x245))) {
      0.0
      } else {
      (1.0./(x245))
      };
      val x249 = if((0L.!=(x242))) {
      x248
      } else {
      0.0
      };
      val x250 = x236;
      x236 = (x250.+(x249))
      val x253 = x236;
      val x255 = if(x30) {
      (x253.*(lineitem_extendedprice))
      } else {
      0.0
      };
      x8519._1_=(lineitem_returnflag)
      x8519._2_=(lineitem_linestatus)
      x8519._3_=(((x197.*((x215.+((x232.unary_-))))).+(x255)))
      val x8520 = x8519._3;
      if((x8520.==(0.0))) {
      } else {
        val x12949 = AVG_PRICEIdx0.get(x8519);
        if((x12949.==(null))) {
          AVG_PRICE.unsafeInsert(x8519)
        } else {
          x12949._3 +=(x8520)
          if(((x12949._3).==(0.0))) {
            AVG_PRICE.delete(x12949)
          } else {
          }
        }
      }
      if(x30) {
        x8534._1_=(lineitem_returnflag)
        x8534._2_=(lineitem_linestatus)
        x8534._3_=(lineitem_extendedprice)
        val x8535 = x8534._3;
        if((x8535.==(0.0))) {
        } else {
          val x12966 = AVG_PRICE_mLINEITEM2Idx0.get(x8534);
          if((x12966.==(null))) {
            AVG_PRICE_mLINEITEM2.unsafeInsert(x8534)
          } else {
            x12966._3 +=(x8535)
            if(((x12966._3).==(0.0))) {
              AVG_PRICE_mLINEITEM2.delete(x12966)
            } else {
            }
          }
        }
      } else {
      }
      x8548._1_=(lineitem_returnflag)
      x8548._2_=(lineitem_linestatus)
      val x12978 = AVG_DISC_mLINEITEM2Idx0.get(x8548);
      val x290 = if((x12978.==(null))) {
      0.0
      } else {
      (x12978._3)
      };
      var x291: Double = 0.0;
      x8554._1_=(lineitem_returnflag)
      x8554._2_=(lineitem_linestatus)
      val x12985 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8554);
      val x296 = if((x12985.==(null))) {
      0L
      } else {
      (x12985._3)
      };
      val x297 = x296.+(x110);
      val x300 = if((1L.>(x297))) {
      1L
      } else {
      x297
      };
      val x303 = if((0.==(x300))) {
      0.0
      } else {
      (1.0./(x300))
      };
      val x304 = if((0L.!=(x297))) {
      x303
      } else {
      0.0
      };
      val x305 = x291;
      x291 = (x305.+(x304))
      val x308 = x291;
      var x309: Double = 0.0;
      x8572._1_=(lineitem_returnflag)
      x8572._2_=(lineitem_linestatus)
      val x13004 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8572);
      val x314 = if((x13004.==(null))) {
      0L
      } else {
      (x13004._3)
      };
      val x317 = if((1L.>(x314))) {
      1L
      } else {
      x314
      };
      val x320 = if((0.==(x317))) {
      0.0
      } else {
      (1.0./(x317))
      };
      val x321 = if((0L.!=(x314))) {
      x320
      } else {
      0.0
      };
      val x322 = x309;
      x309 = (x322.+(x321))
      val x325 = x309;
      var x329: Double = 0.0;
      x8592._1_=(lineitem_returnflag)
      x8592._2_=(lineitem_linestatus)
      val x13025 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8592);
      val x334 = if((x13025.==(null))) {
      0L
      } else {
      (x13025._3)
      };
      val x335 = x334.+(1L);
      val x338 = if((1L.>(x335))) {
      1L
      } else {
      x335
      };
      val x341 = if((0.==(x338))) {
      0.0
      } else {
      (1.0./(x338))
      };
      val x342 = if((0L.!=(x335))) {
      x341
      } else {
      0.0
      };
      val x343 = x329;
      x329 = (x343.+(x342))
      val x346 = x329;
      val x348 = if(x30) {
      (x346.*(lineitem_discount))
      } else {
      0.0
      };
      x8612._1_=(lineitem_returnflag)
      x8612._2_=(lineitem_linestatus)
      x8612._3_=(((x290.*((x308.+((x325.unary_-))))).+(x348)))
      val x8613 = x8612._3;
      if((x8613.==(0.0))) {
      } else {
        val x13050 = AVG_DISCIdx0.get(x8612);
        if((x13050.==(null))) {
          AVG_DISC.unsafeInsert(x8612)
        } else {
          x13050._3 +=(x8613)
          if(((x13050._3).==(0.0))) {
            AVG_DISC.delete(x13050)
          } else {
          }
        }
      }
      x8626._1_=(lineitem_returnflag)
      x8626._2_=(lineitem_linestatus)
      x8626._3_=(x110)
      val x8627 = x8626._3;
      if((x8627.==(0L))) {
      } else {
        val x13066 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x8626);
        if((x13066.==(null))) {
          AVG_QTY_mLINEITEM1_L1_1.unsafeInsert(x8626)
        } else {
          x13066._3 +=(x8627)
          if(((x13066._3).==(0L))) {
            AVG_QTY_mLINEITEM1_L1_1.delete(x13066)
          } else {
          }
        }
      }
      if(x30) {
        x8641._1_=(lineitem_returnflag)
        x8641._2_=(lineitem_linestatus)
        x8641._3_=(lineitem_discount)
        val x8642 = x8641._3;
        if((x8642.==(0.0))) {
        } else {
          val x13083 = AVG_DISC_mLINEITEM2Idx0.get(x8641);
          if((x13083.==(null))) {
            AVG_DISC_mLINEITEM2.unsafeInsert(x8641)
          } else {
            x13083._3 +=(x8642)
            if(((x13083._3).==(0.0))) {
              AVG_DISC_mLINEITEM2.delete(x13083)
            } else {
            }
          }
        }
      } else {
      }
      x8655._1_=(lineitem_returnflag)
      x8655._2_=(lineitem_linestatus)
      x8655._3_=(x110)
      val x8656 = x8655._3;
      if((x8656.==(0L))) {
      } else {
        val x13099 = COUNT_ORDERIdx0.get(x8655);
        if((x13099.==(null))) {
          COUNT_ORDER.unsafeInsert(x8655)
        } else {
          x13099._3 +=(x8656)
          if(((x13099._3).==(0L))) {
            COUNT_ORDER.delete(x13099)
          } else {
          }
        }
      }
    
    }
  
  }
  def onDelLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      val x423 = c1.>=(lineitem_shipdate);
      if(x423) {
        x9049._1_=(lineitem_returnflag)
        x9049._2_=(lineitem_linestatus)
        x9049._3_=((lineitem_quantity.unary_-))
        val x9050 = x9049._3;
        if((x9050.==(0.0))) {
        } else {
          val x13531 = SUM_QTYIdx0.get(x9049);
          if((x13531.==(null))) {
            SUM_QTY.unsafeInsert(x9049)
          } else {
            x13531._3 +=(x9050)
            if(((x13531._3).==(0.0))) {
              SUM_QTY.delete(x13531)
            } else {
            }
          }
        }
      } else {
      }
      if(x423) {
        x9065._1_=(lineitem_returnflag)
        x9065._2_=(lineitem_linestatus)
        x9065._3_=((lineitem_extendedprice.unary_-))
        val x9066 = x9065._3;
        if((x9066.==(0.0))) {
        } else {
          val x13549 = SUM_BASE_PRICEIdx0.get(x9065);
          if((x13549.==(null))) {
            SUM_BASE_PRICE.unsafeInsert(x9065)
          } else {
            x13549._3 +=(x9066)
            if(((x13549._3).==(0.0))) {
              SUM_BASE_PRICE.delete(x13549)
            } else {
            }
          }
        }
      } else {
      }
      if(x423) {
        x9084._1_=(lineitem_returnflag)
        x9084._2_=(lineitem_linestatus)
        x9084._3_=(((lineitem_extendedprice.*((1L.+((lineitem_discount.unary_-))))).unary_-))
        val x9085 = x9084._3;
        if((x9085.==(0.0))) {
        } else {
          val x13570 = SUM_DISC_PRICEIdx0.get(x9084);
          if((x13570.==(null))) {
            SUM_DISC_PRICE.unsafeInsert(x9084)
          } else {
            x13570._3 +=(x9085)
            if(((x13570._3).==(0.0))) {
              SUM_DISC_PRICE.delete(x13570)
            } else {
            }
          }
        }
      } else {
      }
      if(x423) {
        x9105._1_=(lineitem_returnflag)
        x9105._2_=(lineitem_linestatus)
        x9105._3_=(((lineitem_extendedprice.*(((1L.+((lineitem_discount.unary_-))).*((1L.+(lineitem_tax)))))).unary_-))
        val x9106 = x9105._3;
        if((x9106.==(0.0))) {
        } else {
          val x13593 = SUM_CHARGEIdx0.get(x9105);
          if((x13593.==(null))) {
            SUM_CHARGE.unsafeInsert(x9105)
          } else {
            x13593._3 +=(x9106)
            if(((x13593._3).==(0.0))) {
              SUM_CHARGE.delete(x13593)
            } else {
            }
          }
        }
      } else {
      }
      x9119._1_=(lineitem_returnflag)
      x9119._2_=(lineitem_linestatus)
      val x13605 = AVG_QTY_mLINEITEM2Idx0.get(x9119);
      val x500 = if((x13605.==(null))) {
      0.0
      } else {
      (x13605._3)
      };
      var x501: Double = 0.0;
      x9125._1_=(lineitem_returnflag)
      x9125._2_=(lineitem_linestatus)
      val x13612 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9125);
      val x506 = if((x13612.==(null))) {
      0L
      } else {
      (x13612._3)
      };
      val x507 = if(x423) {
      -1L
      } else {
      0L
      };
      val x508 = x506.+(x507);
      val x511 = if((1L.>(x508))) {
      1L
      } else {
      x508
      };
      val x514 = if((0.==(x511))) {
      0.0
      } else {
      (1.0./(x511))
      };
      val x515 = if((0L.!=(x508))) {
      x514
      } else {
      0.0
      };
      val x516 = x501;
      x501 = (x516.+(x515))
      val x519 = x501;
      var x520: Double = 0.0;
      x9144._1_=(lineitem_returnflag)
      x9144._2_=(lineitem_linestatus)
      val x13632 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9144);
      val x525 = if((x13632.==(null))) {
      0L
      } else {
      (x13632._3)
      };
      val x528 = if((1L.>(x525))) {
      1L
      } else {
      x525
      };
      val x531 = if((0.==(x528))) {
      0.0
      } else {
      (1.0./(x528))
      };
      val x532 = if((0L.!=(x525))) {
      x531
      } else {
      0.0
      };
      val x533 = x520;
      x520 = (x533.+(x532))
      val x536 = x520;
      var x540: Double = 0.0;
      x9164._1_=(lineitem_returnflag)
      x9164._2_=(lineitem_linestatus)
      val x13653 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9164);
      val x545 = if((x13653.==(null))) {
      0L
      } else {
      (x13653._3)
      };
      val x546 = x545.+(-1L);
      val x549 = if((1L.>(x546))) {
      1L
      } else {
      x546
      };
      val x552 = if((0.==(x549))) {
      0.0
      } else {
      (1.0./(x549))
      };
      val x553 = if((0L.!=(x546))) {
      x552
      } else {
      0.0
      };
      val x554 = x540;
      x540 = (x554.+(x553))
      val x557 = x540;
      val x558 = lineitem_quantity.unary_-;
      val x560 = if(x423) {
      (x557.*(x558))
      } else {
      0.0
      };
      x9185._1_=(lineitem_returnflag)
      x9185._2_=(lineitem_linestatus)
      x9185._3_=(((x500.*((x519.+((x536.unary_-))))).+(x560)))
      val x9186 = x9185._3;
      if((x9186.==(0.0))) {
      } else {
        val x13679 = AVG_QTYIdx0.get(x9185);
        if((x13679.==(null))) {
          AVG_QTY.unsafeInsert(x9185)
        } else {
          x13679._3 +=(x9186)
          if(((x13679._3).==(0.0))) {
            AVG_QTY.delete(x13679)
          } else {
          }
        }
      }
      if(x423) {
        x9200._1_=(lineitem_returnflag)
        x9200._2_=(lineitem_linestatus)
        x9200._3_=(x558)
        val x9201 = x9200._3;
        if((x9201.==(0.0))) {
        } else {
          val x13696 = AVG_QTY_mLINEITEM2Idx0.get(x9200);
          if((x13696.==(null))) {
            AVG_QTY_mLINEITEM2.unsafeInsert(x9200)
          } else {
            x13696._3 +=(x9201)
            if(((x13696._3).==(0.0))) {
              AVG_QTY_mLINEITEM2.delete(x13696)
            } else {
            }
          }
        }
      } else {
      }
      x9214._1_=(lineitem_returnflag)
      x9214._2_=(lineitem_linestatus)
      val x13708 = AVG_PRICE_mLINEITEM2Idx0.get(x9214);
      val x595 = if((x13708.==(null))) {
      0.0
      } else {
      (x13708._3)
      };
      var x596: Double = 0.0;
      x9220._1_=(lineitem_returnflag)
      x9220._2_=(lineitem_linestatus)
      val x13715 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9220);
      val x601 = if((x13715.==(null))) {
      0L
      } else {
      (x13715._3)
      };
      val x602 = if(x423) {
      -1L
      } else {
      0L
      };
      val x603 = x601.+(x602);
      val x606 = if((1L.>(x603))) {
      1L
      } else {
      x603
      };
      val x609 = if((0.==(x606))) {
      0.0
      } else {
      (1.0./(x606))
      };
      val x610 = if((0L.!=(x603))) {
      x609
      } else {
      0.0
      };
      val x611 = x596;
      x596 = (x611.+(x610))
      val x614 = x596;
      var x615: Double = 0.0;
      x9239._1_=(lineitem_returnflag)
      x9239._2_=(lineitem_linestatus)
      val x13735 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9239);
      val x620 = if((x13735.==(null))) {
      0L
      } else {
      (x13735._3)
      };
      val x623 = if((1L.>(x620))) {
      1L
      } else {
      x620
      };
      val x626 = if((0.==(x623))) {
      0.0
      } else {
      (1.0./(x623))
      };
      val x627 = if((0L.!=(x620))) {
      x626
      } else {
      0.0
      };
      val x628 = x615;
      x615 = (x628.+(x627))
      val x631 = x615;
      var x635: Double = 0.0;
      x9259._1_=(lineitem_returnflag)
      x9259._2_=(lineitem_linestatus)
      val x13756 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9259);
      val x640 = if((x13756.==(null))) {
      0L
      } else {
      (x13756._3)
      };
      val x641 = x640.+(-1L);
      val x644 = if((1L.>(x641))) {
      1L
      } else {
      x641
      };
      val x647 = if((0.==(x644))) {
      0.0
      } else {
      (1.0./(x644))
      };
      val x648 = if((0L.!=(x641))) {
      x647
      } else {
      0.0
      };
      val x649 = x635;
      x635 = (x649.+(x648))
      val x652 = x635;
      val x653 = lineitem_extendedprice.unary_-;
      val x655 = if(x423) {
      (x652.*(x653))
      } else {
      0.0
      };
      x9280._1_=(lineitem_returnflag)
      x9280._2_=(lineitem_linestatus)
      x9280._3_=(((x595.*((x614.+((x631.unary_-))))).+(x655)))
      val x9281 = x9280._3;
      if((x9281.==(0.0))) {
      } else {
        val x13782 = AVG_PRICEIdx0.get(x9280);
        if((x13782.==(null))) {
          AVG_PRICE.unsafeInsert(x9280)
        } else {
          x13782._3 +=(x9281)
          if(((x13782._3).==(0.0))) {
            AVG_PRICE.delete(x13782)
          } else {
          }
        }
      }
      if(x423) {
        x9295._1_=(lineitem_returnflag)
        x9295._2_=(lineitem_linestatus)
        x9295._3_=(x653)
        val x9296 = x9295._3;
        if((x9296.==(0.0))) {
        } else {
          val x13799 = AVG_PRICE_mLINEITEM2Idx0.get(x9295);
          if((x13799.==(null))) {
            AVG_PRICE_mLINEITEM2.unsafeInsert(x9295)
          } else {
            x13799._3 +=(x9296)
            if(((x13799._3).==(0.0))) {
              AVG_PRICE_mLINEITEM2.delete(x13799)
            } else {
            }
          }
        }
      } else {
      }
      x9309._1_=(lineitem_returnflag)
      x9309._2_=(lineitem_linestatus)
      val x13811 = AVG_DISC_mLINEITEM2Idx0.get(x9309);
      val x690 = if((x13811.==(null))) {
      0.0
      } else {
      (x13811._3)
      };
      var x691: Double = 0.0;
      x9315._1_=(lineitem_returnflag)
      x9315._2_=(lineitem_linestatus)
      val x13818 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9315);
      val x696 = if((x13818.==(null))) {
      0L
      } else {
      (x13818._3)
      };
      val x697 = if(x423) {
      -1L
      } else {
      0L
      };
      val x698 = x696.+(x697);
      val x701 = if((1L.>(x698))) {
      1L
      } else {
      x698
      };
      val x704 = if((0.==(x701))) {
      0.0
      } else {
      (1.0./(x701))
      };
      val x705 = if((0L.!=(x698))) {
      x704
      } else {
      0.0
      };
      val x706 = x691;
      x691 = (x706.+(x705))
      val x709 = x691;
      var x710: Double = 0.0;
      x9334._1_=(lineitem_returnflag)
      x9334._2_=(lineitem_linestatus)
      val x13838 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9334);
      val x715 = if((x13838.==(null))) {
      0L
      } else {
      (x13838._3)
      };
      val x718 = if((1L.>(x715))) {
      1L
      } else {
      x715
      };
      val x721 = if((0.==(x718))) {
      0.0
      } else {
      (1.0./(x718))
      };
      val x722 = if((0L.!=(x715))) {
      x721
      } else {
      0.0
      };
      val x723 = x710;
      x710 = (x723.+(x722))
      val x726 = x710;
      var x730: Double = 0.0;
      x9354._1_=(lineitem_returnflag)
      x9354._2_=(lineitem_linestatus)
      val x13859 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9354);
      val x735 = if((x13859.==(null))) {
      0L
      } else {
      (x13859._3)
      };
      val x736 = x735.+(-1L);
      val x739 = if((1L.>(x736))) {
      1L
      } else {
      x736
      };
      val x742 = if((0.==(x739))) {
      0.0
      } else {
      (1.0./(x739))
      };
      val x743 = if((0L.!=(x736))) {
      x742
      } else {
      0.0
      };
      val x744 = x730;
      x730 = (x744.+(x743))
      val x747 = x730;
      val x748 = lineitem_discount.unary_-;
      val x750 = if(x423) {
      (x747.*(x748))
      } else {
      0.0
      };
      x9375._1_=(lineitem_returnflag)
      x9375._2_=(lineitem_linestatus)
      x9375._3_=(((x690.*((x709.+((x726.unary_-))))).+(x750)))
      val x9376 = x9375._3;
      if((x9376.==(0.0))) {
      } else {
        val x13885 = AVG_DISCIdx0.get(x9375);
        if((x13885.==(null))) {
          AVG_DISC.unsafeInsert(x9375)
        } else {
          x13885._3 +=(x9376)
          if(((x13885._3).==(0.0))) {
            AVG_DISC.delete(x13885)
          } else {
          }
        }
      }
      if(x423) {
        x9390._1_=(lineitem_returnflag)
        x9390._2_=(lineitem_linestatus)
        x9390._3_=(-1L)
        val x9391 = x9390._3;
        if((x9391.==(0L))) {
        } else {
          val x13902 = AVG_QTY_mLINEITEM1_L1_1Idx0.get(x9390);
          if((x13902.==(null))) {
            AVG_QTY_mLINEITEM1_L1_1.unsafeInsert(x9390)
          } else {
            x13902._3 +=(x9391)
            if(((x13902._3).==(0L))) {
              AVG_QTY_mLINEITEM1_L1_1.delete(x13902)
            } else {
            }
          }
        }
      } else {
      }
      if(x423) {
        x9405._1_=(lineitem_returnflag)
        x9405._2_=(lineitem_linestatus)
        x9405._3_=(x748)
        val x9406 = x9405._3;
        if((x9406.==(0.0))) {
        } else {
          val x13919 = AVG_DISC_mLINEITEM2Idx0.get(x9405);
          if((x13919.==(null))) {
            AVG_DISC_mLINEITEM2.unsafeInsert(x9405)
          } else {
            x13919._3 +=(x9406)
            if(((x13919._3).==(0.0))) {
              AVG_DISC_mLINEITEM2.delete(x13919)
            } else {
            }
          }
        }
      } else {
      }
      if(x423) {
        x9420._1_=(lineitem_returnflag)
        x9420._2_=(lineitem_linestatus)
        x9420._3_=(-1L)
        val x9421 = x9420._3;
        if((x9421.==(0L))) {
        } else {
          val x13936 = COUNT_ORDERIdx0.get(x9420);
          if((x13936.==(null))) {
            COUNT_ORDER.unsafeInsert(x9420)
          } else {
            x13936._3 +=(x9421)
            if(((x13936._3).==(0L))) {
              COUNT_ORDER.delete(x13936)
            } else {
            }
          }
        }
      } else {
      }
    
    }
  
  }
  def onSystemReady() {
    {
    
    }
  
  }

  val c1:Long = Udate("1997-9-1")
}

class Tpch1 extends Tpch1Base with Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._
  import Tpch1._
  
  var t0 = 0L; var t1 = 0L; var tN = 0L; var tS = 0L

  

  

  def receive_skip: Receive = { 
    case EndOfStream | GetSnapshot(_) => 
       sender ! (StreamStat(t1 - t0, tN, tS), List({ val SUM_QTY_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_QTY.foreach{e => SUM_QTY_node_mres += (((e._1, e._2),e._3)) }; SUM_QTY_node_mres.toMap }, { val SUM_BASE_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_BASE_PRICE.foreach{e => SUM_BASE_PRICE_node_mres += (((e._1, e._2),e._3)) }; SUM_BASE_PRICE_node_mres.toMap }, { val SUM_DISC_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_DISC_PRICE.foreach{e => SUM_DISC_PRICE_node_mres += (((e._1, e._2),e._3)) }; SUM_DISC_PRICE_node_mres.toMap }, { val SUM_CHARGE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_CHARGE.foreach{e => SUM_CHARGE_node_mres += (((e._1, e._2),e._3)) }; SUM_CHARGE_node_mres.toMap }, { val AVG_QTY_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_QTY.foreach{e => AVG_QTY_node_mres += (((e._1, e._2),e._3)) }; AVG_QTY_node_mres.toMap }, { val AVG_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_PRICE.foreach{e => AVG_PRICE_node_mres += (((e._1, e._2),e._3)) }; AVG_PRICE_node_mres.toMap }, { val AVG_DISC_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_DISC.foreach{e => AVG_DISC_node_mres += (((e._1, e._2),e._3)) }; AVG_DISC_node_mres.toMap }, { val COUNT_ORDER_node_mres = new scala.collection.mutable.HashMap[(String, String),Long](); COUNT_ORDER.foreach{e => COUNT_ORDER_node_mres += (((e._1, e._2),e._3)) }; COUNT_ORDER_node_mres.toMap }))
    case _ => tS += 1L
  }

  def receive = {
    case TupleEvent(TupleInsert, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => if (t1 > 0 && (tN & 127) == 0) { val t = System.nanoTime; if (t > t1) { t1 = t; tS = 1L; context.become(receive_skip) } }; tN += 1L; onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => if (t1 > 0 && (tN & 127) == 0) { val t = System.nanoTime; if (t > t1) { t1 = t; tS = 1L; context.become(receive_skip) } }; tN += 1L; onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case StreamInit(timeout) => 
      
      onSystemReady();
      t0 = System.nanoTime;
      if (timeout > 0) t1 = t0 + timeout * 1000000L
    case EndOfStream | GetSnapshot(_) => 
      t1 = System.nanoTime; 
       sender ! (StreamStat(t1 - t0, tN, tS), List({ val SUM_QTY_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_QTY.foreach{e => SUM_QTY_node_mres += (((e._1, e._2),e._3)) }; SUM_QTY_node_mres.toMap }, { val SUM_BASE_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_BASE_PRICE.foreach{e => SUM_BASE_PRICE_node_mres += (((e._1, e._2),e._3)) }; SUM_BASE_PRICE_node_mres.toMap }, { val SUM_DISC_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_DISC_PRICE.foreach{e => SUM_DISC_PRICE_node_mres += (((e._1, e._2),e._3)) }; SUM_DISC_PRICE_node_mres.toMap }, { val SUM_CHARGE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); SUM_CHARGE.foreach{e => SUM_CHARGE_node_mres += (((e._1, e._2),e._3)) }; SUM_CHARGE_node_mres.toMap }, { val AVG_QTY_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_QTY.foreach{e => AVG_QTY_node_mres += (((e._1, e._2),e._3)) }; AVG_QTY_node_mres.toMap }, { val AVG_PRICE_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_PRICE.foreach{e => AVG_PRICE_node_mres += (((e._1, e._2),e._3)) }; AVG_PRICE_node_mres.toMap }, { val AVG_DISC_node_mres = new scala.collection.mutable.HashMap[(String, String),Double](); AVG_DISC.foreach{e => AVG_DISC_node_mres += (((e._1, e._2),e._3)) }; AVG_DISC_node_mres.toMap }, { val COUNT_ORDER_node_mres = new scala.collection.mutable.HashMap[(String, String),Long](); COUNT_ORDER.foreach{e => COUNT_ORDER_node_mres += (((e._1, e._2),e._3)) }; COUNT_ORDER_node_mres.toMap }))
  }
}