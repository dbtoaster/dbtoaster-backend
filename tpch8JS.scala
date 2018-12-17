package ddbt.gen

import lib.{Entry, EntryIdx, IHash, Store}
import Helper._
import tutorial.webapp.Functions.Udate

import scala.collection.mutable
import scala.concurrent.ExecutionContext.Implicits.global
import scala.scalajs.js.typedarray.ArrayBufferInputStream
import HelperGS._
import Messages._
import Functions._
import lib.Entry

object Tpch8JS {

  

def exec(): Unit = {

    var res:List[scala.collection.immutable.Map[_ <: Any, Any]]=List()

        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/lineitem.csv").foreach(arraybuffer0=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/orders.csv").foreach(arraybuffer1=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/part.csv").foreach(arraybuffer2=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/customer.csv").foreach(arraybuffer3=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/supplier.csv").foreach(arraybuffer4=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/nation.csv").foreach(arraybuffer5=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/region.csv").foreach(arraybuffer6=>
        
        execute1(Seq(
        
         (arraybuffer0,new Adaptor.CSV("LINEITEM","long,long,long,long,double,double,double,double,string,string,date,date,date,string,string,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer1,new Adaptor.CSV("ORDERS","long,long,string,double,date,string,string,long,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer2,new Adaptor.CSV("PART","long,string,string,string,string,long,string,double,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer3,new Adaptor.CSV("CUSTOMER","long,string,string,long,string,double,string,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer4,new Adaptor.CSV("SUPPLIER","long,string,string,long,string,double,string","\\Q|\\E", "insert"), Split()),
        ),List(  arraybuffer5, arraybuffer6))))))))
        )

  def execute1(streams: Streams, list: List[ArrayBufferInputStream]) = {
      loadTables(list);
      onSystemReady();
      goThroughStreams(streams, dispatchFnNoActor _)
        println("<snap>")
        println("<MKT_SHARE>\n" + M3Map.toStr(res(0), List("TOTAL_O_YEAR"))+"\n" + "</MKT_SHARE>\n")
        println("</snap>")
        }
  def dispatchFnNoActor(e: StreamEvent) = e match {
    case TupleEvent(TupleInsert, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleInsert, "ORDERS", List(v0:Long,v1:Long,v2:String,v3:Double,v4:Long,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete, "ORDERS", List(v0:Long,v1:Long,v2:String,v3:Double,v4:Long,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert, "PART", List(v0:Long,v1:String,v2:String,v3:String,v4:String,v5:Long,v6:String,v7:Double,v8:String)) => onAddPART(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete, "PART", List(v0:Long,v1:String,v2:String,v3:String,v4:String,v5:Long,v6:String,v7:Double,v8:String)) => onDelPART(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert, "CUSTOMER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onAddCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete, "CUSTOMER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDelCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleInsert, "SUPPLIER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onAddSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case TupleEvent(TupleDelete, "SUPPLIER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onDelSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case EndOfStream | GetSnapshot(_) =>
       res=res:::(List({ val MKT_SHARE_node_mres = new scala.collection.mutable.HashMap[Long,Double](); MKT_SHARE.foreach{e => MKT_SHARE_node_mres += ((e._1,e._2)) }; MKT_SHARE_node_mres.toMap }))
  }
def loadTables(list: List[ArrayBufferInputStream]) {
         SourceMux({ case TupleEvent(TupleInsert, rn, List(v0:Long,v1:String,v2:Long,v3:String)) => NATION.unsafeInsert(SEntry5_LSLSL(v0,v1,v2,v3, 1L)) }, Seq((list(0), new Adaptor.CSV("NATION","long,string,long,string","\\Q|\\E", "insert"), Split()))).read;
  SourceMux({ case TupleEvent(TupleInsert, rn, List(v0:Long,v1:String,v2:String)) => REGION.unsafeInsert(SEntry4_LSSL(v0,v1,v2, 1L)) }, Seq((list(1), new Adaptor.CSV("REGION","long,string,string","\\Q|\\E", "insert"), Split()))).read;
    }
}
    ////
  case class SEntry4_LLLD(var _1: Long, var _2: Long, var _3: Long, var _4: Double) extends Entry(4) {def this() = this(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308) ; def copy = SEntry4_LLLD(_1, _2, _3, _4); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry4_LLLD]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4} }
  case class SEntry3_LLD(var _1: Long, var _2: Long, var _3: Double) extends Entry(3) {def this() = this(-2147483648L, -2147483648L, -1.7976931348623157E308) ; def copy = SEntry3_LLD(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_LLD]; _1 = that._1;_2 = that._2;_3 = that._3} }
  case class SEntry2_LD(var _1: Long, var _2: Double) extends Entry(2) {def this() = this(-2147483648L, -1.7976931348623157E308) ; def copy = SEntry2_LD(_1, _2); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry2_LD]; _1 = that._1;_2 = that._2} }
  case class SEntry3_LLL(var _1: Long, var _2: Long, var _3: Long) extends Entry(3) {def this() = this(-2147483648L, -2147483648L, -2147483648L) ; def copy = SEntry3_LLL(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_LLL]; _1 = that._1;_2 = that._2;_3 = that._3} }
  case class SEntry4_LLLL(var _1: Long, var _2: Long, var _3: Long, var _4: Long) extends Entry(4) {def this() = this(-2147483648L, -2147483648L, -2147483648L, -2147483648L) ; def copy = SEntry4_LLLL(_1, _2, _3, _4); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry4_LLLL]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4} }
  case class SEntry5_LLLLD(var _1: Long, var _2: Long, var _3: Long, var _4: Long, var _5: Double) extends Entry(5) {def this() = this(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308) ; def copy = SEntry5_LLLLD(_1, _2, _3, _4, _5); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry5_LLLLD]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5} }
  case class SEntry4_LSSL(var _1: Long, var _2: String, var _3: String, var _4: Long) extends Entry(4) {def this() = this(-2147483648L, null, null, -2147483648L) ; def copy = SEntry4_LSSL(_1, _2, _3, _4); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry4_LSSL]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4} }
  case class SEntry5_LSLSL(var _1: Long, var _2: String, var _3: Long, var _4: String, var _5: Long) extends Entry(5) {def this() = this(-2147483648L, null, -2147483648L, null, -2147483648L) ; def copy = SEntry5_LSLSL(_1, _2, _3, _4, _5); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry5_LSLSL]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5} }
  case class SEntry2_LL(var _1: Long, var _2: Long) extends Entry(2) {def this() = this(-2147483648L, -2147483648L) ; def copy = SEntry2_LL(_1, _2); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry2_LL]; _1 = that._1;_2 = that._2} }
   object SEntry4_LLLD_Idx2 extends EntryIdx[SEntry4_LLLD] {
    override def hash(x47960 : SEntry4_LLLD) = {
      var x47961: Int = 0;
      val x47962 = x47961;
      x47961 = (x47962.^((((((x47960._2).hashCode()).+(-1640531527)).+((x47962.<<(6)))).+((x47962.>>(2))))))
      val x47972 = x47961;
      x47972
    }
    override def cmp(x47974 : SEntry4_LLLD , x47975 : SEntry4_LLLD) = {
      var x47976: Int = 0;
      if(((x47974._2).==((x47975._2)))) {
        x47976 = 0
      } else {
        x47976 = 1
      }
      val x47983 = x47976;
      x47983
    }
  }
   object SEntry5_LSLSL_Idx2 extends EntryIdx[SEntry5_LSLSL] {
    override def hash(x48485 : SEntry5_LSLSL) = {
      var x48486: Int = 0;
      val x48487 = x48486;
      x48486 = (x48487.^((((((x48485._2).hashCode()).+(-1640531527)).+((x48487.<<(6)))).+((x48487.>>(2))))))
      val x48497 = x48486;
      x48497
    }
    override def cmp(x48499 : SEntry5_LSLSL , x48500 : SEntry5_LSLSL) = {
      var x48501: Int = 0;
      if(((x48499._2).==((x48500._2)))) {
        x48501 = 0
      } else {
        x48501 = 1
      }
      val x48508 = x48501;
      x48508
    }
  }
   object SEntry2_LL_Idx1 extends EntryIdx[SEntry2_LL] {
    override def hash(x47715 : SEntry2_LL) = {
      var x47716: Int = 0;
      val x47717 = x47716;
      x47716 = (x47717.^((((((x47715._1).hashCode()).+(-1640531527)).+((x47717.<<(6)))).+((x47717.>>(2))))))
      val x47727 = x47716;
      x47727
    }
    override def cmp(x47729 : SEntry2_LL , x47730 : SEntry2_LL) = {
      var x47731: Int = 0;
      if(((x47729._1).==((x47730._1)))) {
        x47731 = 0
      } else {
        x47731 = 1
      }
      val x47738 = x47731;
      x47738
    }
  }
   object SEntry4_LLLL_Idx1 extends EntryIdx[SEntry4_LLLL] {
    override def hash(x47872 : SEntry4_LLLL) = {
      var x47873: Int = 0;
      val x47874 = x47873;
      x47873 = (x47874.^((((((x47872._1).hashCode()).+(-1640531527)).+((x47874.<<(6)))).+((x47874.>>(2))))))
      val x47884 = x47873;
      x47884
    }
    override def cmp(x47886 : SEntry4_LLLL , x47887 : SEntry4_LLLL) = {
      var x47888: Int = 0;
      if(((x47886._1).==((x47887._1)))) {
        x47888 = 0
      } else {
        x47888 = 1
      }
      val x47895 = x47888;
      x47895
    }
  }
   object SEntry2_LD_Idx1 extends EntryIdx[SEntry2_LD] {
    override def hash(x47745 : SEntry2_LD) = {
      var x47746: Int = 0;
      val x47747 = x47746;
      x47746 = (x47747.^((((((x47745._1).hashCode()).+(-1640531527)).+((x47747.<<(6)))).+((x47747.>>(2))))))
      val x47757 = x47746;
      x47757
    }
    override def cmp(x47759 : SEntry2_LD , x47760 : SEntry2_LD) = {
      var x47761: Int = 0;
      if(((x47759._1).==((x47760._1)))) {
        x47761 = 0
      } else {
        x47761 = 1
      }
      val x47768 = x47761;
      x47768
    }
  }
   object SEntry4_LLLD_Idx123 extends EntryIdx[SEntry4_LLLD] {
    override def hash(x47904 : SEntry4_LLLD) = {
      var x47905: Int = 0;
      val x47906 = x47905;
      x47905 = (x47906.^((((((x47904._1).hashCode()).+(-1640531527)).+((x47906.<<(6)))).+((x47906.>>(2))))))
      val x47916 = x47905;
      x47905 = (x47916.^((((((x47904._2).hashCode()).+(-1640531527)).+((x47916.<<(6)))).+((x47916.>>(2))))))
      val x47926 = x47905;
      x47905 = (x47926.^((((((x47904._3).hashCode()).+(-1640531527)).+((x47926.<<(6)))).+((x47926.>>(2))))))
      val x47936 = x47905;
      x47936
    }
    override def cmp(x47938 : SEntry4_LLLD , x47939 : SEntry4_LLLD) = {
      var x47940: Int = 0;
      if(((x47938._1).==((x47939._1)))) {
        if(((x47938._2).==((x47939._2)))) {
          if(((x47938._3).==((x47939._3)))) {
            x47940 = 0
          } else {
            x47940 = 1
          }
        } else {
          x47940 = 1
        }
      } else {
        x47940 = 1
      }
      val x47957 = x47940;
      x47957
    }
  }
   object SEntry4_LSSL_Idx123 extends EntryIdx[SEntry4_LSSL] {
    override def hash(x48287 : SEntry4_LSSL) = {
      var x48288: Int = 0;
      val x48289 = x48288;
      x48288 = (x48289.^((((((x48287._1).hashCode()).+(-1640531527)).+((x48289.<<(6)))).+((x48289.>>(2))))))
      val x48299 = x48288;
      x48288 = (x48299.^((((((x48287._2).hashCode()).+(-1640531527)).+((x48299.<<(6)))).+((x48299.>>(2))))))
      val x48309 = x48288;
      x48288 = (x48309.^((((((x48287._3).hashCode()).+(-1640531527)).+((x48309.<<(6)))).+((x48309.>>(2))))))
      val x48319 = x48288;
      x48319
    }
    override def cmp(x48321 : SEntry4_LSSL , x48322 : SEntry4_LSSL) = {
      var x48323: Int = 0;
      if(((x48321._1).==((x48322._1)))) {
        if(((x48321._2).==((x48322._2)))) {
          if(((x48321._3).==((x48322._3)))) {
            x48323 = 0
          } else {
            x48323 = 1
          }
        } else {
          x48323 = 1
        }
      } else {
        x48323 = 1
      }
      val x48340 = x48323;
      x48340
    }
  }
   object SEntry3_LLD_Idx1 extends EntryIdx[SEntry3_LLD] {
    override def hash(x47646 : SEntry3_LLD) = {
      var x47647: Int = 0;
      val x47648 = x47647;
      x47647 = (x47648.^((((((x47646._1).hashCode()).+(-1640531527)).+((x47648.<<(6)))).+((x47648.>>(2))))))
      val x47658 = x47647;
      x47658
    }
    override def cmp(x47660 : SEntry3_LLD , x47661 : SEntry3_LLD) = {
      var x47662: Int = 0;
      if(((x47660._1).==((x47661._1)))) {
        x47662 = 0
      } else {
        x47662 = 1
      }
      val x47669 = x47662;
      x47669
    }
  }
   object SEntry3_LLL_Idx12 extends EntryIdx[SEntry3_LLL] {
    override def hash(x48211 : SEntry3_LLL) = {
      var x48212: Int = 0;
      val x48213 = x48212;
      x48212 = (x48213.^((((((x48211._1).hashCode()).+(-1640531527)).+((x48213.<<(6)))).+((x48213.>>(2))))))
      val x48223 = x48212;
      x48212 = (x48223.^((((((x48211._2).hashCode()).+(-1640531527)).+((x48223.<<(6)))).+((x48223.>>(2))))))
      val x48233 = x48212;
      x48233
    }
    override def cmp(x48235 : SEntry3_LLL , x48236 : SEntry3_LLL) = {
      var x48237: Int = 0;
      if(((x48235._1).==((x48236._1)))) {
        if(((x48235._2).==((x48236._2)))) {
          x48237 = 0
        } else {
          x48237 = 1
        }
      } else {
        x48237 = 1
      }
      val x48249 = x48237;
      x48249
    }
  }
   object SEntry3_LLD_Idx2 extends EntryIdx[SEntry3_LLD] {
    override def hash(x47682 : SEntry3_LLD) = {
      var x47683: Int = 0;
      val x47684 = x47683;
      x47683 = (x47684.^((((((x47682._2).hashCode()).+(-1640531527)).+((x47684.<<(6)))).+((x47684.>>(2))))))
      val x47694 = x47683;
      x47694
    }
    override def cmp(x47696 : SEntry3_LLD , x47697 : SEntry3_LLD) = {
      var x47698: Int = 0;
      if(((x47696._2).==((x47697._2)))) {
        x47698 = 0
      } else {
        x47698 = 1
      }
      val x47705 = x47698;
      x47705
    }
  }
   object SEntry5_LSLSL_Idx1234 extends EntryIdx[SEntry5_LSLSL] {
    override def hash(x48414 : SEntry5_LSLSL) = {
      var x48415: Int = 0;
      val x48416 = x48415;
      x48415 = (x48416.^((((((x48414._1).hashCode()).+(-1640531527)).+((x48416.<<(6)))).+((x48416.>>(2))))))
      val x48426 = x48415;
      x48415 = (x48426.^((((((x48414._2).hashCode()).+(-1640531527)).+((x48426.<<(6)))).+((x48426.>>(2))))))
      val x48436 = x48415;
      x48415 = (x48436.^((((((x48414._3).hashCode()).+(-1640531527)).+((x48436.<<(6)))).+((x48436.>>(2))))))
      val x48446 = x48415;
      x48415 = (x48446.^((((((x48414._4).hashCode()).+(-1640531527)).+((x48446.<<(6)))).+((x48446.>>(2))))))
      val x48456 = x48415;
      x48456
    }
    override def cmp(x48458 : SEntry5_LSLSL , x48459 : SEntry5_LSLSL) = {
      var x48460: Int = 0;
      if(((x48458._1).==((x48459._1)))) {
        if(((x48458._2).==((x48459._2)))) {
          if(((x48458._3).==((x48459._3)))) {
            if(((x48458._4).==((x48459._4)))) {
              x48460 = 0
            } else {
              x48460 = 1
            }
          } else {
            x48460 = 1
          }
        } else {
          x48460 = 1
        }
      } else {
        x48460 = 1
      }
      val x48482 = x48460;
      x48482
    }
  }
   object SEntry5_LLLLD_Idx1 extends EntryIdx[SEntry5_LLLLD] {
    override def hash(x48129 : SEntry5_LLLLD) = {
      var x48130: Int = 0;
      val x48131 = x48130;
      x48130 = (x48131.^((((((x48129._1).hashCode()).+(-1640531527)).+((x48131.<<(6)))).+((x48131.>>(2))))))
      val x48141 = x48130;
      x48141
    }
    override def cmp(x48143 : SEntry5_LLLLD , x48144 : SEntry5_LLLLD) = {
      var x48145: Int = 0;
      if(((x48143._1).==((x48144._1)))) {
        x48145 = 0
      } else {
        x48145 = 1
      }
      val x48152 = x48145;
      x48152
    }
  }
   object SEntry3_LLD_Idx12 extends EntryIdx[SEntry3_LLD] {
    override def hash(x47605 : SEntry3_LLD) = {
      var x47606: Int = 0;
      val x47607 = x47606;
      x47606 = (x47607.^((((((x47605._1).hashCode()).+(-1640531527)).+((x47607.<<(6)))).+((x47607.>>(2))))))
      val x47617 = x47606;
      x47606 = (x47617.^((((((x47605._2).hashCode()).+(-1640531527)).+((x47617.<<(6)))).+((x47617.>>(2))))))
      val x47627 = x47606;
      x47627
    }
    override def cmp(x47629 : SEntry3_LLD , x47630 : SEntry3_LLD) = {
      var x47631: Int = 0;
      if(((x47629._1).==((x47630._1)))) {
        if(((x47629._2).==((x47630._2)))) {
          x47631 = 0
        } else {
          x47631 = 1
        }
      } else {
        x47631 = 1
      }
      val x47643 = x47631;
      x47643
    }
  }
   object SEntry5_LLLLD_Idx2 extends EntryIdx[SEntry5_LLLLD] {
    override def hash(x48103 : SEntry5_LLLLD) = {
      var x48104: Int = 0;
      val x48105 = x48104;
      x48104 = (x48105.^((((((x48103._2).hashCode()).+(-1640531527)).+((x48105.<<(6)))).+((x48105.>>(2))))))
      val x48115 = x48104;
      x48115
    }
    override def cmp(x48117 : SEntry5_LLLLD , x48118 : SEntry5_LLLLD) = {
      var x48119: Int = 0;
      if(((x48117._2).==((x48118._2)))) {
        x48119 = 0
      } else {
        x48119 = 1
      }
      val x48126 = x48119;
      x48126
    }
  }
   object SEntry5_LLLLD_Idx1234 extends EntryIdx[SEntry5_LLLLD] {
    override def hash(x48032 : SEntry5_LLLLD) = {
      var x48033: Int = 0;
      val x48034 = x48033;
      x48033 = (x48034.^((((((x48032._1).hashCode()).+(-1640531527)).+((x48034.<<(6)))).+((x48034.>>(2))))))
      val x48044 = x48033;
      x48033 = (x48044.^((((((x48032._2).hashCode()).+(-1640531527)).+((x48044.<<(6)))).+((x48044.>>(2))))))
      val x48054 = x48033;
      x48033 = (x48054.^((((((x48032._3).hashCode()).+(-1640531527)).+((x48054.<<(6)))).+((x48054.>>(2))))))
      val x48064 = x48033;
      x48033 = (x48064.^((((((x48032._4).hashCode()).+(-1640531527)).+((x48064.<<(6)))).+((x48064.>>(2))))))
      val x48074 = x48033;
      x48074
    }
    override def cmp(x48076 : SEntry5_LLLLD , x48077 : SEntry5_LLLLD) = {
      var x48078: Int = 0;
      if(((x48076._1).==((x48077._1)))) {
        if(((x48076._2).==((x48077._2)))) {
          if(((x48076._3).==((x48077._3)))) {
            if(((x48076._4).==((x48077._4)))) {
              x48078 = 0
            } else {
              x48078 = 1
            }
          } else {
            x48078 = 1
          }
        } else {
          x48078 = 1
        }
      } else {
        x48078 = 1
      }
      val x48100 = x48078;
      x48100
    }
  }
   object SEntry5_LLLLD_Idx3 extends EntryIdx[SEntry5_LLLLD] {
    override def hash(x48155 : SEntry5_LLLLD) = {
      var x48156: Int = 0;
      val x48157 = x48156;
      x48156 = (x48157.^((((((x48155._3).hashCode()).+(-1640531527)).+((x48157.<<(6)))).+((x48157.>>(2))))))
      val x48167 = x48156;
      x48167
    }
    override def cmp(x48169 : SEntry5_LLLLD , x48170 : SEntry5_LLLLD) = {
      var x48171: Int = 0;
      if(((x48169._3).==((x48170._3)))) {
        x48171 = 0
      } else {
        x48171 = 1
      }
      val x48178 = x48171;
      x48178
    }
  }
   object SEntry4_LLLL_Idx2 extends EntryIdx[SEntry4_LLLL] {
    override def hash(x47846 : SEntry4_LLLL) = {
      var x47847: Int = 0;
      val x47848 = x47847;
      x47847 = (x47848.^((((((x47846._2).hashCode()).+(-1640531527)).+((x47848.<<(6)))).+((x47848.>>(2))))))
      val x47858 = x47847;
      x47858
    }
    override def cmp(x47860 : SEntry4_LLLL , x47861 : SEntry4_LLLL) = {
      var x47862: Int = 0;
      if(((x47860._2).==((x47861._2)))) {
        x47862 = 0
      } else {
        x47862 = 1
      }
      val x47869 = x47862;
      x47869
    }
  }
   object SEntry4_LLLD_Idx3 extends EntryIdx[SEntry4_LLLD] {
    override def hash(x48536 : SEntry4_LLLD) = {
      var x48537: Int = 0;
      val x48538 = x48537;
      x48537 = (x48538.^((((((x48536._3).hashCode()).+(-1640531527)).+((x48538.<<(6)))).+((x48538.>>(2))))))
      val x48548 = x48537;
      x48548
    }
    override def cmp(x48550 : SEntry4_LLLD , x48551 : SEntry4_LLLD) = {
      var x48552: Int = 0;
      if(((x48550._3).==((x48551._3)))) {
        x48552 = 0
      } else {
        x48552 = 1
      }
      val x48559 = x48552;
      x48559
    }
  }
   object SEntry3_LLL_Idx1 extends EntryIdx[SEntry3_LLL] {
    override def hash(x48252 : SEntry3_LLL) = {
      var x48253: Int = 0;
      val x48254 = x48253;
      x48253 = (x48254.^((((((x48252._1).hashCode()).+(-1640531527)).+((x48254.<<(6)))).+((x48254.>>(2))))))
      val x48264 = x48253;
      x48264
    }
    override def cmp(x48266 : SEntry3_LLL , x48267 : SEntry3_LLL) = {
      var x48268: Int = 0;
      if(((x48266._1).==((x48267._1)))) {
        x48268 = 0
      } else {
        x48268 = 1
      }
      val x48275 = x48268;
      x48275
    }
  }
   object SEntry4_LSSL_Idx12 extends EntryIdx[SEntry4_LSSL] {
    override def hash(x48343 : SEntry4_LSSL) = {
      var x48344: Int = 0;
      val x48345 = x48344;
      x48344 = (x48345.^((((((x48343._1).hashCode()).+(-1640531527)).+((x48345.<<(6)))).+((x48345.>>(2))))))
      val x48355 = x48344;
      x48344 = (x48355.^((((((x48343._2).hashCode()).+(-1640531527)).+((x48355.<<(6)))).+((x48355.>>(2))))))
      val x48365 = x48344;
      x48365
    }
    override def cmp(x48367 : SEntry4_LSSL , x48368 : SEntry4_LSSL) = {
      var x48369: Int = 0;
      if(((x48367._1).==((x48368._1)))) {
        if(((x48367._2).==((x48368._2)))) {
          x48369 = 0
        } else {
          x48369 = 1
        }
      } else {
        x48369 = 1
      }
      val x48381 = x48369;
      x48381
    }
  }
   object SEntry4_LLLL_Idx123 extends EntryIdx[SEntry4_LLLL] {
    override def hash(x47790 : SEntry4_LLLL) = {
      var x47791: Int = 0;
      val x47792 = x47791;
      x47791 = (x47792.^((((((x47790._1).hashCode()).+(-1640531527)).+((x47792.<<(6)))).+((x47792.>>(2))))))
      val x47802 = x47791;
      x47791 = (x47802.^((((((x47790._2).hashCode()).+(-1640531527)).+((x47802.<<(6)))).+((x47802.>>(2))))))
      val x47812 = x47791;
      x47791 = (x47812.^((((((x47790._3).hashCode()).+(-1640531527)).+((x47812.<<(6)))).+((x47812.>>(2))))))
      val x47822 = x47791;
      x47822
    }
    override def cmp(x47824 : SEntry4_LLLL , x47825 : SEntry4_LLLL) = {
      var x47826: Int = 0;
      if(((x47824._1).==((x47825._1)))) {
        if(((x47824._2).==((x47825._2)))) {
          if(((x47824._3).==((x47825._3)))) {
            x47826 = 0
          } else {
            x47826 = 1
          }
        } else {
          x47826 = 1
        }
      } else {
        x47826 = 1
      }
      val x47843 = x47826;
      x47843
    }
  }
   object SEntry4_LLLD_Idx1 extends EntryIdx[SEntry4_LLLD] {
    override def hash(x47986 : SEntry4_LLLD) = {
      var x47987: Int = 0;
      val x47988 = x47987;
      x47987 = (x47988.^((((((x47986._1).hashCode()).+(-1640531527)).+((x47988.<<(6)))).+((x47988.>>(2))))))
      val x47998 = x47987;
      x47998
    }
    override def cmp(x48000 : SEntry4_LLLD , x48001 : SEntry4_LLLD) = {
      var x48002: Int = 0;
      if(((x48000._1).==((x48001._1)))) {
        x48002 = 0
      } else {
        x48002 = 1
      }
      val x48009 = x48002;
      x48009
    }
  }
  
  val x47673 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_mCUSTOMER1 = new Store[SEntry3_LLD](2, x47673);
  val MKT_SHARE_mPART1_mCUSTOMER1Idx0 = MKT_SHARE_mPART1_mCUSTOMER1.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1Idx1 = MKT_SHARE_mPART1_mCUSTOMER1.index(1, IHash, false, -1)
  val x47677 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_mPART2 = new Store[SEntry3_LLD](2, x47677);
  val MKT_SHARE_mPART1_mPART2Idx0 = MKT_SHARE_mPART1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mPART2Idx1 = MKT_SHARE_mPART1_mPART2.index(1, IHash, false, -1)
  val x47709 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx2, SEntry3_LLD_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1 = new Store[SEntry3_LLD](3, x47709);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index(0, IHash, true, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index(1, IHash, false, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.index(2, IHash, false, -1)
  val x47742 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_4 = new Store[SEntry2_LL](1, x47742);
  val MKT_SHARE_mORDERS1_L2_1_L1_4Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_4.index(0, IHash, true, -1)
  val x47772 = Array[EntryIdx[SEntry2_LD]](SEntry2_LD_Idx1)
  val MKT_SHARE_mORDERS6 = new Store[SEntry2_LD](1, x47772);
  val MKT_SHARE_mORDERS6Idx0 = MKT_SHARE_mORDERS6.index(0, IHash, true, -1)
  val x47775 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1 = new Store[SEntry3_LLD](2, x47775);
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.index(1, IHash, false, -1)
  val x47779 = Array[EntryIdx[SEntry2_LD]](SEntry2_LD_Idx1)
  val MKT_SHARE_mPART1 = new Store[SEntry2_LD](1, x47779);
  val MKT_SHARE_mPART1Idx0 = MKT_SHARE_mPART1.index(0, IHash, true, -1)
  val x47782 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mPART2 = new Store[SEntry3_LLD](2, x47782);
  val MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2.index(1, IHash, false, -1)
  val x47786 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS6_mSUPPLIER1 = new Store[SEntry2_LL](1, x47786);
  val MKT_SHARE_mORDERS6_mSUPPLIER1Idx0 = MKT_SHARE_mORDERS6_mSUPPLIER1.index(0, IHash, true, -1)
  val x47899 = Array[EntryIdx[SEntry4_LLLL]](SEntry4_LLLL_Idx123, SEntry4_LLLL_Idx2, SEntry4_LLLL_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3 = new Store[SEntry4_LLLL](3, x47899);
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.index(2, IHash, false, -1)
  val x48013 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1 = new Store[SEntry4_LLLD](3, x48013);
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx2 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.index(2, IHash, false, -1)
  val x48018 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS6_mLINEITEM1 = new Store[SEntry2_LL](1, x48018);
  val MKT_SHARE_mORDERS6_mLINEITEM1Idx0 = MKT_SHARE_mORDERS6_mLINEITEM1.index(0, IHash, true, -1)
  val x48021 = Array[EntryIdx[SEntry2_LD]](SEntry2_LD_Idx1)
  val MKT_SHARE = new Store[SEntry2_LD](1, x48021);
  val MKT_SHAREIdx0 = MKT_SHARE.index(0, IHash, true, -1)
  val x48024 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1 = new Store[SEntry2_LL](1, x48024);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.index(0, IHash, true, -1)
  val x48027 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1 = new Store[SEntry3_LLD](2, x48027);
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.index(1, IHash, false, -1)
  val x48182 = Array[EntryIdx[SEntry5_LLLLD]](SEntry5_LLLLD_Idx1234, SEntry5_LLLLD_Idx2, SEntry5_LLLLD_Idx1, SEntry5_LLLLD_Idx3)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2 = new Store[SEntry5_LLLLD](4, x48182);
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx0 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx1 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx2 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index(2, IHash, false, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx3 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.index(3, IHash, false, -1)
  val x48188 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2 = new Store[SEntry4_LLLD](3, x48188);
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx2 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.index(2, IHash, false, -1)
  val x48193 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx2, SEntry3_LLD_Idx1)
  val MKT_SHARE_mORDERS6_mPART2 = new Store[SEntry3_LLD](3, x48193);
  val MKT_SHARE_mORDERS6_mPART2Idx0 = MKT_SHARE_mORDERS6_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mORDERS6_mPART2Idx1 = MKT_SHARE_mORDERS6_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mORDERS6_mPART2Idx2 = MKT_SHARE_mORDERS6_mPART2.index(2, IHash, false, -1)
  val x48198 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2 = new Store[SEntry4_LLLD](3, x48198);
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx2 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.index(2, IHash, false, -1)
  val x48203 = Array[EntryIdx[SEntry2_LD]](SEntry2_LD_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1 = new Store[SEntry2_LD](1, x48203);
  val MKT_SHARE_mPART1_L2_1_L1_1Idx0 = MKT_SHARE_mPART1_L2_1_L1_1.index(0, IHash, true, -1)
  val x48206 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_mSUPPLIER2_mPART2 = new Store[SEntry4_LLLD](3, x48206);
  val MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx1 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx2 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2.index(2, IHash, false, -1)
  val x48279 = Array[EntryIdx[SEntry3_LLL]](SEntry3_LLL_Idx12, SEntry3_LLL_Idx1)
  val MKT_SHARE_mPART1_mLINEITEM3 = new Store[SEntry3_LLL](2, x48279);
  val MKT_SHARE_mPART1_mLINEITEM3Idx0 = MKT_SHARE_mPART1_mLINEITEM3.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mLINEITEM3Idx1 = MKT_SHARE_mPART1_mLINEITEM3.index(1, IHash, false, -1)
  val x48283 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2 = new Store[SEntry2_LL](1, x48283);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.index(0, IHash, true, -1)
  val x48385 = Array[EntryIdx[SEntry4_LSSL]](SEntry4_LSSL_Idx123, SEntry4_LSSL_Idx12)
  val REGION = new Store[SEntry4_LSSL](2, x48385);
  val REGIONIdx0 = REGION.index(0, IHash, true, -1)
  val REGIONIdx1 = REGION.index(1, IHash, false, -1)
  val x48389 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx1)
  val MKT_SHARE_mPART1_mSUPPLIER2 = new Store[SEntry3_LLD](2, x48389);
  val MKT_SHARE_mPART1_mSUPPLIER2Idx0 = MKT_SHARE_mPART1_mSUPPLIER2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mSUPPLIER2Idx1 = MKT_SHARE_mPART1_mSUPPLIER2.index(1, IHash, false, -1)
  val x48393 = Array[EntryIdx[SEntry3_LLL]](SEntry3_LLL_Idx12, SEntry3_LLL_Idx1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2 = new Store[SEntry3_LLL](2, x48393);
  val MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.index(1, IHash, false, -1)
  val x48397 = Array[EntryIdx[SEntry5_LLLLD]](SEntry5_LLLLD_Idx1234, SEntry5_LLLLD_Idx2, SEntry5_LLLLD_Idx1, SEntry5_LLLLD_Idx3)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2 = new Store[SEntry5_LLLLD](4, x48397);
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx0 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx1 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx2 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index(2, IHash, false, -1)
  val MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx3 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.index(3, IHash, false, -1)
  val x48403 = Array[EntryIdx[SEntry3_LLD]](SEntry3_LLD_Idx12, SEntry3_LLD_Idx2, SEntry3_LLD_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2 = new Store[SEntry3_LLD](3, x48403);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx1 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.index(2, IHash, false, -1)
  val x48408 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2 = new Store[SEntry4_LLLD](3, x48408);
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx1 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx2 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.index(2, IHash, false, -1)
  val x48512 = Array[EntryIdx[SEntry5_LSLSL]](SEntry5_LSLSL_Idx1234, SEntry5_LSLSL_Idx2)
  val NATION = new Store[SEntry5_LSLSL](2, x48512);
  val NATIONIdx0 = NATION.index(0, IHash, true, -1)
  val NATIONIdx1 = NATION.index(1, IHash, false, -1)
  val x48516 = Array[EntryIdx[SEntry2_LD]](SEntry2_LD_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5 = new Store[SEntry2_LD](1, x48516);
  val MKT_SHARE_mORDERS1_L2_1_L1_5Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5.index(0, IHash, true, -1)
  val x48519 = Array[EntryIdx[SEntry4_LLLL]](SEntry4_LLLL_Idx123, SEntry4_LLLL_Idx2, SEntry4_LLLL_Idx1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3 = new Store[SEntry4_LLLL](3, x48519);
  val MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx0 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx1 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.index(2, IHash, false, -1)
  val x48524 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mPART2 = new Store[SEntry4_LLLD](3, x48524);
  val MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx1 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx2 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2.index(2, IHash, false, -1)
  val x48529 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2 = new Store[SEntry2_LL](1, x48529);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.index(0, IHash, true, -1)
  val x48532 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1 = new Store[SEntry2_LL](1, x48532);
  val MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.index(0, IHash, true, -1)
  val x48563 = Array[EntryIdx[SEntry4_LLLD]](SEntry4_LLLD_Idx123, SEntry4_LLLD_Idx2, SEntry4_LLLD_Idx1, SEntry4_LLLD_Idx3)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2 = new Store[SEntry4_LLLD](4, x48563);
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx0 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index(0, IHash, true, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx1 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index(1, IHash, false, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index(2, IHash, false, -1)
  val MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.index(3, IHash, false, -1)
  
  
  
  val x58235 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51747 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51192 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57144 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51200 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58665 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49737 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x51844 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51245 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58608 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58113 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x60038 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54452 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49745 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52491 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51253 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x54842 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57902 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51154 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49583 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56018 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52680 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52601 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52537 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51056 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54287 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49941 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57112 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59959 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53068 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50161 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49622 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57075 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59518 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49643 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56737 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56430 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55952 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57115 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54190 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51181 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57107 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52831 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57088 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57152 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53091 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49727 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55806 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52716 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55828 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55930 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49719 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55785 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49750 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x54309 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51159 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x49783 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54282 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58834 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49753 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51146 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x52559 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54314 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49686 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x54140 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57297 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53113 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55781 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54218 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x53219 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51602 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49668 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55995 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58198 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51022 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56395 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52841 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58702 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54272 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59069 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58906 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51223 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x56516 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51635 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57096 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51261 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x51122 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59540 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57080 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54931 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50195 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x60551 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49713 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x52846 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52675 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51186 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x59697 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59772 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54145 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50300 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51719 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54329 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54442 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51859 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57099 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51036 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58662 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56414 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59611 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50053 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58697 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54277 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59534 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49780 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x57907 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53399 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58622 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49705 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x49539 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49764 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57886 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51205 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59614 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58085 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57859 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55765 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58718 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53428 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51554 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54122 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49629 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58657 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51477 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54813 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52736 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54389 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x53305 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51242 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57945 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59603 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59576 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50273 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59562 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58058 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54405 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54211 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57830 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54206 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x55907 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57835 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52726 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53162 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54324 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54467 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x60053 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49617 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58762 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x60504 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52815 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x51162 = SEntry2_LL(-2147483648L, -2147483648L);
  val x60016 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52758 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x55885 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57894 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56062 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52633 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54978 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51011 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57843 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x52701 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57215 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x59622 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54234 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59567 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57104 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59598 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49708 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52649 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57810 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51697 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x60486 = SEntry5_LSLSL(-2147483648L, null, -2147483648L, null, -2147483648L);
  val x56391 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58713 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55088 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56410 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53456 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49716 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x56561 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56722 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54457 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58681 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59847 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51234 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57973 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x55761 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56442 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57851 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59651 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49549 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x60525 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51090 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59531 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57270 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52856 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59590 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57846 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58705 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54240 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59643 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59669 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52731 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49603 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52496 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58603 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51167 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x59042 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59627 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54086 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51149 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58595 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56434 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58030 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54344 = SEntry2_LL(-2147483648L, -2147483648L);
  val x53191 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52628 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51415 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57867 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55793 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52795 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51076 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54462 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58001 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52851 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52836 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55973 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52542 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52519 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56653 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51795 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51136 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56456 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57432 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58807 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x55769 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49975 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57838 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55029 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57899 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59595 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51116 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52779 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57862 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54351 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59931 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x50385 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54162 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51226 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50370 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58694 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58630 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52670 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52742 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52606 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56422 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57120 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49761 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x56479 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58735 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51173 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57350 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x58592 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52484 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59570 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49697 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x49724 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x51042 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59635 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57136 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51095 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49740 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49681 = SEntry2_LL(-2147483648L, -2147483648L);
  val x55789 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51218 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51527 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54293 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x57188 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54334 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58170 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49649 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52685 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x54709 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51189 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x55059 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51210 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x50003 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49597 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58141 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57454 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59638 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59526 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58987 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54685 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56608 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57083 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51250 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x52763 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57405 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52585 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56438 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x53328 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58587 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59744 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52800 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56700 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x60495 = SEntry4_LSSL(-2147483648L, null, null, -2147483648L);
  val x49732 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51499 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57377 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54732 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51256 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58673 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52711 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51822 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51170 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57123 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58689 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54447 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56077 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x52721 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49563 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57870 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57878 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54373 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58710 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57128 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x57891 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51178 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x54256 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x58934 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57056 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59106 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59559 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52805 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51141 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50080 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51102 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49694 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x52549 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57469 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49534 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49689 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49777 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x54415 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54426 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x51213 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49700 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58686 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58600 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55746 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50128 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49569 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55773 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55864 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58879 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x57875 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x55777 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59904 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51070 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56426 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57131 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59646 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56538 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59014 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50101 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51231 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x52554 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56677 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50321 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49788 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x50245 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54157 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x55738 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58635 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59630 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54093 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57323 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58220 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58678 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52665 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54410 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51197 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x49772 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59606 = SEntry2_LL(-2147483648L, -2147483648L);
  val x57242 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59988 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57147 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56585 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57091 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52810 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54367 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x49663 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59523 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x52706 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58638 = SEntry2_LL(-2147483648L, -2147483648L);
  val x56040 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57061 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51237 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54152 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x54783 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56418 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59091 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x56630 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x53350 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x59554 = SEntry2_LL(-2147483648L, -2147483648L);
  val x49758 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x49769 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x54339 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x58961 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51669 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57883 = SEntry4_LLLL(-2147483648L, -2147483648L, -2147483648L, -2147483648L);
  val x55742 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57816 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59876 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51575 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50223 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x50348 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x58627 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57139 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58670 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54319 = SEntry2_LL(-2147483648L, -2147483648L);
  val x59819 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x59619 = SEntry4_LLLD(-2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x57854 = SEntry2_LL(-2147483648L, -2147483648L);
  val x51449 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49673 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x54955 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x56387 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x51774 = SEntry3_LLD(-2147483648L, -2147483648L, -1.7976931348623157E308);
  val x49676 = SEntry2_LL(-2147483648L, -2147483648L);
  val x50025 = SEntry5_LLLLD(-2147483648L, -2147483648L, -2147483648L, -2147483648L, -1.7976931348623157E308);
  val x54420 = SEntry2_LL(-2147483648L, -2147483648L);
  val x58643 = SEntry2_LL(-2147483648L, -2147483648L);
  val x52612 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  val x51006 = SEntry2_LL(-2147483648L, -2147483648L);
  val x54098 = SEntry2_LD(-2147483648L, -1.7976931348623157E308);
  def onAddLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      x49534._1_=(lineitem_partkey)
      val x78398 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49534);
      val x57 = if((x78398.==(null))) {
      0L
      } else {
      (x78398._2)
      };
      x49539._1_=(lineitem_suppkey)
      val x78403 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49539);
      val x62 = if((x78403.==(null))) {
      0L
      } else {
      (x78403._2)
      };
      val x65 = lineitem_extendedprice.*((1L.+((lineitem_discount.unary_-))));
      x49549._1_=(lineitem_orderkey)
      x49549._2_=((x57.*((x62.*(x65)))))
      val x49550 = x49549._2;
      if((x49550.==(0.0))) {
      } else {
        val x78417 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x49549);
        if((x78417.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x49549)
        } else {
          x78417._2 +=(x49550)
          if(((x78417._2).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x78417)
          } else {
          }
        }
      }
      x49563._1_=(lineitem_partkey)
      val x78428 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49563);
      val x86 = if((x78428.==(null))) {
      0L
      } else {
      (x78428._2)
      };
      x49569._1_=(lineitem_orderkey)
      x49569._2_=(lineitem_suppkey)
      x49569._3_=((x86.*(x65)))
      val x49570 = x49569._3;
      if((x49570.==(0.0))) {
      } else {
        val x78439 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx0.get(x49569);
        if((x78439.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.unsafeInsert(x49569)
        } else {
          x78439._3 +=(x49570)
          if(((x78439._3).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.delete(x78439)
          } else {
          }
        }
      }
      x49583._1_=(lineitem_orderkey)
      x49583._2_=(lineitem_partkey)
      x49583._3_=(lineitem_suppkey)
      x49583._4_=(x65)
      val x49584 = x49583._4;
      if((x49584.==(0.0))) {
      } else {
        val x78458 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx0.get(x49583);
        if((x78458.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.unsafeInsert(x49583)
        } else {
          x78458._4 +=(x49584)
          if(((x78458._4).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.delete(x78458)
          } else {
          }
        }
      }
      x49597._1_=(lineitem_suppkey)
      val x78472 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49597);
      val x120 = if((x78472.==(null))) {
      0L
      } else {
      (x78472._2)
      };
      x49603._1_=(lineitem_orderkey)
      x49603._2_=(lineitem_partkey)
      x49603._3_=((x120.*(x65)))
      val x49604 = x49603._3;
      if((x49604.==(0.0))) {
      } else {
        val x78483 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx0.get(x49603);
        if((x78483.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.unsafeInsert(x49603)
        } else {
          x78483._3 +=(x49604)
          if(((x78483._3).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.delete(x78483)
          } else {
          }
        }
      }
      x49617._1_=(lineitem_partkey)
      val x78496 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49617);
      val x140 = if((x78496.==(null))) {
      0L
      } else {
      (x78496._2)
      };
      x49622._1_=(lineitem_suppkey)
      val x78501 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49622);
      val x145 = if((x78501.==(null))) {
      0L
      } else {
      (x78501._2)
      };
      x49629._1_=(lineitem_orderkey)
      x49629._2_=((x140.*((x145.*(x65)))))
      val x49630 = x49629._2;
      if((x49630.==(0.0))) {
      } else {
        val x78512 = MKT_SHARE_mORDERS6Idx0.get(x49629);
        if((x78512.==(null))) {
          MKT_SHARE_mORDERS6.unsafeInsert(x49629)
        } else {
          x78512._2 +=(x49630)
          if(((x78512._2).==(0.0))) {
            MKT_SHARE_mORDERS6.delete(x78512)
          } else {
          }
        }
      }
      x49643._1_=(lineitem_suppkey)
      val x78523 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49643);
      val x166 = if((x78523.==(null))) {
      0L
      } else {
      (x78523._2)
      };
      x49649._1_=(lineitem_orderkey)
      x49649._2_=(lineitem_partkey)
      x49649._3_=((x166.*(x65)))
      val x49650 = x49649._3;
      if((x49650.==(0.0))) {
      } else {
        val x78534 = MKT_SHARE_mORDERS6_mPART2Idx0.get(x49649);
        if((x78534.==(null))) {
          MKT_SHARE_mORDERS6_mPART2.unsafeInsert(x49649)
        } else {
          x78534._3 +=(x49650)
          if(((x78534._3).==(0.0))) {
            MKT_SHARE_mORDERS6_mPART2.delete(x78534)
          } else {
          }
        }
      }
      x49663._1_=(lineitem_partkey)
      val x78547 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49663);
      x49668._1_=(lineitem_suppkey)
      val x78552 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49668);
      x49673._1_=(lineitem_orderkey)
      val x106035 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x49673);
      if((x106035.isEmpty)) {
      } else {
        val x191 = if((x78552.==(null))) {
        0L
        } else {
        (x78552._2)
        };
        val x186 = if((x78547.==(null))) {
        0L
        } else {
        (x78547._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x49673, ({ x193: SEntry3_LLL => {
            x49941._1_=((x193._2))
            x49941._2_=((x186.*((x191.*(((x193._3).*(x65)))))))
            val x49942 = x49941._2;
            if((x49942.==(0.0))) {
            } else {
              val x78569 = MKT_SHARE_mPART1Idx0.get(x49941);
              if((x78569.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x49941)
              } else {
                x78569._2 +=(x49942)
                if(((x78569._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x78569)
                } else {
                }
              }
            }
          
          }
        }), x106035)
      }
      x49676._1_=(lineitem_partkey)
      val x78581 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49676);
      x49681._1_=(lineitem_suppkey)
      val x78586 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49681);
      x49686._1_=(lineitem_orderkey)
      val x106073 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49686);
      if((x106073.isEmpty)) {
      } else {
        val x224 = if((x78586.==(null))) {
        0L
        } else {
        (x78586._2)
        };
        val x219 = if((x78581.==(null))) {
        0L
        } else {
        (x78581._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49686, ({ x226: SEntry4_LLLL => {
            x49975._1_=((x226._2))
            x49975._2_=((x226._3))
            x49975._3_=((x219.*((x224.*(((x226._4).*(x65)))))))
            val x49976 = x49975._3;
            if((x49976.==(0.0))) {
            } else {
              val x78605 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x49975);
              if((x78605.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x49975)
              } else {
                x78605._3 +=(x49976)
                if(((x78605._3).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.delete(x78605)
                } else {
                }
              }
            }
          
          }
        }), x106073)
      }
      x49689._1_=(lineitem_partkey)
      val x78618 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49689);
      x49694._1_=(lineitem_orderkey)
      val x106106 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49694);
      if((x106106.isEmpty)) {
      } else {
        val x253 = if((x78618.==(null))) {
        0L
        } else {
        (x78618._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49694, ({ x255: SEntry4_LLLL => {
            x50003._1_=(lineitem_suppkey)
            x50003._2_=((x255._2))
            x50003._3_=((x255._3))
            x50003._4_=((x253.*(((x255._4).*(x65)))))
            val x50004 = x50003._4;
            if((x50004.==(0.0))) {
            } else {
              val x78637 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x50003);
              if((x78637.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x50003)
              } else {
                x78637._4 +=(x50004)
                if(((x78637._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x78637)
                } else {
                }
              }
            }
          
          }
        }), x106106)
      }
      x49697._1_=(lineitem_orderkey)
      val x106134 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49697);
      if((x106134.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49697, ({ x278: SEntry4_LLLL => {
            x50025._1_=(lineitem_partkey)
            x50025._2_=(lineitem_suppkey)
            x50025._3_=((x278._2))
            x50025._4_=((x278._3))
            x50025._5_=(((x278._4).*(x65)))
            val x50026 = x50025._5;
            if((x50026.==(0.0))) {
            } else {
              val x78665 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx0.get(x50025);
              if((x78665.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.unsafeInsert(x50025)
              } else {
                x78665._5 +=(x50026)
                if(((x78665._5).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.delete(x78665)
                } else {
                }
              }
            }
          
          }
        }), x106134)
      }
      x49700._1_=(lineitem_suppkey)
      val x78680 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49700);
      x49705._1_=(lineitem_orderkey)
      val x106167 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49705);
      if((x106167.isEmpty)) {
      } else {
        val x303 = if((x78680.==(null))) {
        0L
        } else {
        (x78680._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49705, ({ x305: SEntry4_LLLL => {
            x50053._1_=(lineitem_partkey)
            x50053._2_=((x305._2))
            x50053._3_=((x305._3))
            x50053._4_=((x303.*(((x305._4).*(x65)))))
            val x50054 = x50053._4;
            if((x50054.==(0.0))) {
            } else {
              val x78699 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x50053);
              if((x78699.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x50053)
              } else {
                x78699._4 +=(x50054)
                if(((x78699._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x78699)
                } else {
                }
              }
            }
          
          }
        }), x106167)
      }
      x49708._1_=(lineitem_partkey)
      val x78713 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49708);
      x49713._1_=(lineitem_orderkey)
      val x106198 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x49713);
      if((x106198.isEmpty)) {
      } else {
        val x331 = if((x78713.==(null))) {
        0L
        } else {
        (x78713._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x49713, ({ x333: SEntry3_LLL => {
            x50080._1_=(lineitem_suppkey)
            x50080._2_=((x333._2))
            x50080._3_=((x331.*(((x333._3).*(x65)))))
            val x50081 = x50080._3;
            if((x50081.==(0.0))) {
            } else {
              val x78730 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x50080);
              if((x78730.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x50080)
              } else {
                x78730._3 +=(x50081)
                if(((x78730._3).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.delete(x78730)
                } else {
                }
              }
            }
          
          }
        }), x106198)
      }
      x49716._1_=(lineitem_orderkey)
      val x106224 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x49716);
      if((x106224.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x49716, ({ x355: SEntry3_LLL => {
            x50101._1_=(lineitem_partkey)
            x50101._2_=(lineitem_suppkey)
            x50101._3_=((x355._2))
            x50101._4_=(((x355._3).*(x65)))
            val x50102 = x50101._4;
            if((x50102.==(0.0))) {
            } else {
              val x78755 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x50101);
              if((x78755.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x50101)
              } else {
                x78755._4 +=(x50102)
                if(((x78755._4).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x78755)
                } else {
                }
              }
            }
          
          }
        }), x106224)
      }
      x49719._1_=(lineitem_suppkey)
      val x78769 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x49719);
      x49724._1_=(lineitem_orderkey)
      val x106255 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x49724);
      if((x106255.isEmpty)) {
      } else {
        val x379 = if((x78769.==(null))) {
        0L
        } else {
        (x78769._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x49724, ({ x381: SEntry3_LLL => {
            x50128._1_=(lineitem_partkey)
            x50128._2_=((x381._2))
            x50128._3_=((x379.*(((x381._3).*(x65)))))
            val x50129 = x50128._3;
            if((x50129.==(0.0))) {
            } else {
              val x78786 = MKT_SHARE_mPART1_mPART2Idx0.get(x50128);
              if((x78786.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x50128)
              } else {
                x78786._3 +=(x50129)
                if(((x78786._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x78786)
                } else {
                }
              }
            }
          
          }
        }), x106255)
      }
      x49727._1_=(lineitem_partkey)
      val x78799 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49727);
      x49732._1_=(lineitem_suppkey)
      val x78804 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49732);
      x49737._1_=(lineitem_orderkey)
      val x106291 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x49737);
      if((x106291.isEmpty)) {
      } else {
        val x411 = if((x78804.==(null))) {
        0L
        } else {
        (x78804._2)
        };
        val x406 = if((x78799.==(null))) {
        0L
        } else {
        (x78799._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x49737, ({ x413: SEntry3_LLL => {
            x50161._1_=((x413._2))
            x50161._2_=((x406.*((x411.*(((x413._3).*(x65)))))))
            val x50162 = x50161._2;
            if((x50162.==(0.0))) {
            } else {
              val x78821 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x50161);
              if((x78821.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x50161)
              } else {
                x78821._2 +=(x50162)
                if(((x78821._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x78821)
                } else {
                }
              }
            }
          
          }
        }), x106291)
      }
      x49740._1_=(lineitem_partkey)
      val x78833 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49740);
      x49745._1_=(lineitem_suppkey)
      val x78838 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49745);
      x49750._1_=(lineitem_orderkey)
      val x106329 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49750);
      if((x106329.isEmpty)) {
      } else {
        val x444 = if((x78838.==(null))) {
        0L
        } else {
        (x78838._2)
        };
        val x439 = if((x78833.==(null))) {
        0L
        } else {
        (x78833._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49750, ({ x446: SEntry4_LLLL => {
            x50195._1_=((x446._2))
            x50195._2_=((x446._3))
            x50195._3_=((x439.*((x444.*(((x446._4).*(x65)))))))
            val x50196 = x50195._3;
            if((x50196.==(0.0))) {
            } else {
              val x78857 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x50195);
              if((x78857.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x50195)
              } else {
                x78857._3 +=(x50196)
                if(((x78857._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x78857)
                } else {
                }
              }
            }
          
          }
        }), x106329)
      }
      x49753._1_=(lineitem_partkey)
      val x78870 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49753);
      x49758._1_=(lineitem_orderkey)
      val x106362 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49758);
      if((x106362.isEmpty)) {
      } else {
        val x473 = if((x78870.==(null))) {
        0L
        } else {
        (x78870._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49758, ({ x475: SEntry4_LLLL => {
            x50223._1_=(lineitem_suppkey)
            x50223._2_=((x475._2))
            x50223._3_=((x475._3))
            x50223._4_=((x473.*(((x475._4).*(x65)))))
            val x50224 = x50223._4;
            if((x50224.==(0.0))) {
            } else {
              val x78889 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x50223);
              if((x78889.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x50223)
              } else {
                x78889._4 +=(x50224)
                if(((x78889._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x78889)
                } else {
                }
              }
            }
          
          }
        }), x106362)
      }
      x49761._1_=(lineitem_orderkey)
      val x106390 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49761);
      if((x106390.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49761, ({ x498: SEntry4_LLLL => {
            x50245._1_=(lineitem_partkey)
            x50245._2_=(lineitem_suppkey)
            x50245._3_=((x498._2))
            x50245._4_=((x498._3))
            x50245._5_=(((x498._4).*(x65)))
            val x50246 = x50245._5;
            if((x50246.==(0.0))) {
            } else {
              val x78917 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx0.get(x50245);
              if((x78917.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.unsafeInsert(x50245)
              } else {
                x78917._5 +=(x50246)
                if(((x78917._5).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.delete(x78917)
                } else {
                }
              }
            }
          
          }
        }), x106390)
      }
      x49764._1_=(lineitem_suppkey)
      val x78932 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49764);
      x49769._1_=(lineitem_orderkey)
      val x106423 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x49769);
      if((x106423.isEmpty)) {
      } else {
        val x523 = if((x78932.==(null))) {
        0L
        } else {
        (x78932._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x49769, ({ x525: SEntry4_LLLL => {
            x50273._1_=(lineitem_partkey)
            x50273._2_=((x525._2))
            x50273._3_=((x525._3))
            x50273._4_=((x523.*(((x525._4).*(x65)))))
            val x50274 = x50273._4;
            if((x50274.==(0.0))) {
            } else {
              val x78951 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x50273);
              if((x78951.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x50273)
              } else {
                x78951._4 +=(x50274)
                if(((x78951._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x78951)
                } else {
                }
              }
            }
          
          }
        }), x106423)
      }
      x49772._1_=(lineitem_partkey)
      val x78965 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x49772);
      x49777._1_=(lineitem_orderkey)
      val x106454 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x49777);
      if((x106454.isEmpty)) {
      } else {
        val x551 = if((x78965.==(null))) {
        0L
        } else {
        (x78965._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x49777, ({ x553: SEntry3_LLL => {
            x50300._1_=(lineitem_suppkey)
            x50300._2_=((x553._2))
            x50300._3_=((x551.*(((x553._3).*(x65)))))
            val x50301 = x50300._3;
            if((x50301.==(0.0))) {
            } else {
              val x78982 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x50300);
              if((x78982.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x50300)
              } else {
                x78982._3 +=(x50301)
                if(((x78982._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x78982)
                } else {
                }
              }
            }
          
          }
        }), x106454)
      }
      x49780._1_=(lineitem_orderkey)
      val x106480 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x49780);
      if((x106480.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x49780, ({ x575: SEntry3_LLL => {
            x50321._1_=(lineitem_partkey)
            x50321._2_=(lineitem_suppkey)
            x50321._3_=((x575._2))
            x50321._4_=(((x575._3).*(x65)))
            val x50322 = x50321._4;
            if((x50322.==(0.0))) {
            } else {
              val x79007 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x50321);
              if((x79007.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x50321)
              } else {
                x79007._4 +=(x50322)
                if(((x79007._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x79007)
                } else {
                }
              }
            }
          
          }
        }), x106480)
      }
      x49783._1_=(lineitem_suppkey)
      val x79021 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x49783);
      x49788._1_=(lineitem_orderkey)
      val x106511 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x49788);
      if((x106511.isEmpty)) {
      } else {
        val x599 = if((x79021.==(null))) {
        0L
        } else {
        (x79021._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x49788, ({ x601: SEntry3_LLL => {
            x50348._1_=(lineitem_partkey)
            x50348._2_=((x601._2))
            x50348._3_=((x599.*(((x601._3).*(x65)))))
            val x50349 = x50348._3;
            if((x50349.==(0.0))) {
            } else {
              val x79038 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x50348);
              if((x79038.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x50348)
              } else {
                x79038._3 +=(x50349)
                if(((x79038._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x79038)
                } else {
                }
              }
            }
          
          }
        }), x106511)
      }
      MKT_SHARE.clear
      val x106551 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x106551.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x623: SEntry2_LD => {
            val x626 = Udate_year((x623._1));
            var x627: Double = 0.0;
            x50370._1_=(x626)
            val x79058 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x50370);
            val x632 = if((x79058.==(null))) {
            0.0
            } else {
            (x79058._2)
            };
            val x634 = if((1L.>(x632))) {
            1L
            } else {
            x632
            };
            val x635 = x627;
            x627 = (x635.+(x634))
            val x638 = x627;
            val x641 = if((0.==(x638))) {
            0.0
            } else {
            (1.0./(x638))
            };
            x50385._1_=(x626)
            x50385._2_=(((x623._2).*(x641)))
            val x50386 = x50385._2;
            if((x50386.==(0.0))) {
            } else {
              val x79077 = MKT_SHAREIdx0.get(x50385);
              if((x79077.==(null))) {
                MKT_SHARE.unsafeInsert(x50385)
              } else {
                x79077._2 +=(x50386)
                if(((x79077._2).==(0.0))) {
                  MKT_SHARE.delete(x79077)
                } else {
                }
              }
            }
          
          }
        }), x106551)
      }
    
    }
  
  }
  def onDelLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      x51006._1_=(lineitem_partkey)
      val x79780 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51006);
      val x679 = if((x79780.==(null))) {
      0L
      } else {
      (x79780._2)
      };
      x51011._1_=(lineitem_suppkey)
      val x79785 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51011);
      val x684 = if((x79785.==(null))) {
      0L
      } else {
      (x79785._2)
      };
      val x688 = (lineitem_extendedprice.*((1L.+((lineitem_discount.unary_-))))).unary_-;
      x51022._1_=(lineitem_orderkey)
      x51022._2_=((x679.*((x684.*(x688)))))
      val x51023 = x51022._2;
      if((x51023.==(0.0))) {
      } else {
        val x79800 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x51022);
        if((x79800.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x51022)
        } else {
          x79800._2 +=(x51023)
          if(((x79800._2).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x79800)
          } else {
          }
        }
      }
      x51036._1_=(lineitem_partkey)
      val x79811 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51036);
      val x709 = if((x79811.==(null))) {
      0L
      } else {
      (x79811._2)
      };
      x51042._1_=(lineitem_orderkey)
      x51042._2_=(lineitem_suppkey)
      x51042._3_=((x709.*(x688)))
      val x51043 = x51042._3;
      if((x51043.==(0.0))) {
      } else {
        val x79822 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx0.get(x51042);
        if((x79822.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.unsafeInsert(x51042)
        } else {
          x79822._3 +=(x51043)
          if(((x79822._3).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.delete(x79822)
          } else {
          }
        }
      }
      x51056._1_=(lineitem_orderkey)
      x51056._2_=(lineitem_partkey)
      x51056._3_=(lineitem_suppkey)
      x51056._4_=(x688)
      val x51057 = x51056._4;
      if((x51057.==(0.0))) {
      } else {
        val x79841 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx0.get(x51056);
        if((x79841.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.unsafeInsert(x51056)
        } else {
          x79841._4 +=(x51057)
          if(((x79841._4).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2.delete(x79841)
          } else {
          }
        }
      }
      x51070._1_=(lineitem_suppkey)
      val x79855 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51070);
      val x743 = if((x79855.==(null))) {
      0L
      } else {
      (x79855._2)
      };
      x51076._1_=(lineitem_orderkey)
      x51076._2_=(lineitem_partkey)
      x51076._3_=((x743.*(x688)))
      val x51077 = x51076._3;
      if((x51077.==(0.0))) {
      } else {
        val x79866 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx0.get(x51076);
        if((x79866.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.unsafeInsert(x51076)
        } else {
          x79866._3 +=(x51077)
          if(((x79866._3).==(0.0))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.delete(x79866)
          } else {
          }
        }
      }
      x51090._1_=(lineitem_suppkey)
      val x79879 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51090);
      val x763 = if((x79879.==(null))) {
      0L
      } else {
      (x79879._2)
      };
      x51095._1_=(lineitem_partkey)
      val x79884 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51095);
      val x768 = if((x79884.==(null))) {
      0L
      } else {
      (x79884._2)
      };
      x51102._1_=(lineitem_orderkey)
      x51102._2_=((x763.*((x768.*(x688)))))
      val x51103 = x51102._2;
      if((x51103.==(0.0))) {
      } else {
        val x79895 = MKT_SHARE_mORDERS6Idx0.get(x51102);
        if((x79895.==(null))) {
          MKT_SHARE_mORDERS6.unsafeInsert(x51102)
        } else {
          x79895._2 +=(x51103)
          if(((x79895._2).==(0.0))) {
            MKT_SHARE_mORDERS6.delete(x79895)
          } else {
          }
        }
      }
      x51116._1_=(lineitem_suppkey)
      val x79906 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51116);
      val x789 = if((x79906.==(null))) {
      0L
      } else {
      (x79906._2)
      };
      x51122._1_=(lineitem_orderkey)
      x51122._2_=(lineitem_partkey)
      x51122._3_=((x789.*(x688)))
      val x51123 = x51122._3;
      if((x51123.==(0.0))) {
      } else {
        val x79917 = MKT_SHARE_mORDERS6_mPART2Idx0.get(x51122);
        if((x79917.==(null))) {
          MKT_SHARE_mORDERS6_mPART2.unsafeInsert(x51122)
        } else {
          x79917._3 +=(x51123)
          if(((x79917._3).==(0.0))) {
            MKT_SHARE_mORDERS6_mPART2.delete(x79917)
          } else {
          }
        }
      }
      x51136._1_=(lineitem_suppkey)
      val x79930 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51136);
      x51141._1_=(lineitem_partkey)
      val x79935 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51141);
      x51146._1_=(lineitem_orderkey)
      val x106722 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x51146);
      if((x106722.isEmpty)) {
      } else {
        val x814 = if((x79935.==(null))) {
        0L
        } else {
        (x79935._2)
        };
        val x809 = if((x79930.==(null))) {
        0L
        } else {
        (x79930._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x51146, ({ x816: SEntry3_LLL => {
            x51415._1_=((x816._2))
            x51415._2_=((x809.*((x814.*(((x816._3).*(x688)))))))
            val x51416 = x51415._2;
            if((x51416.==(0.0))) {
            } else {
              val x79952 = MKT_SHARE_mPART1Idx0.get(x51415);
              if((x79952.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x51415)
              } else {
                x79952._2 +=(x51416)
                if(((x79952._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x79952)
                } else {
                }
              }
            }
          
          }
        }), x106722)
      }
      x51149._1_=(lineitem_suppkey)
      val x79964 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51149);
      x51154._1_=(lineitem_partkey)
      val x79969 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51154);
      x51159._1_=(lineitem_orderkey)
      val x106760 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51159);
      if((x106760.isEmpty)) {
      } else {
        val x847 = if((x79969.==(null))) {
        0L
        } else {
        (x79969._2)
        };
        val x842 = if((x79964.==(null))) {
        0L
        } else {
        (x79964._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51159, ({ x849: SEntry4_LLLL => {
            x51449._1_=((x849._2))
            x51449._2_=((x849._3))
            x51449._3_=((x842.*((x847.*(((x849._4).*(x688)))))))
            val x51450 = x51449._3;
            if((x51450.==(0.0))) {
            } else {
              val x79988 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x51449);
              if((x79988.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x51449)
              } else {
                x79988._3 +=(x51450)
                if(((x79988._3).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.delete(x79988)
                } else {
                }
              }
            }
          
          }
        }), x106760)
      }
      x51162._1_=(lineitem_partkey)
      val x80001 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51162);
      x51167._1_=(lineitem_orderkey)
      val x106793 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51167);
      if((x106793.isEmpty)) {
      } else {
        val x876 = if((x80001.==(null))) {
        0L
        } else {
        (x80001._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51167, ({ x878: SEntry4_LLLL => {
            x51477._1_=(lineitem_suppkey)
            x51477._2_=((x878._2))
            x51477._3_=((x878._3))
            x51477._4_=((x876.*(((x878._4).*(x688)))))
            val x51478 = x51477._4;
            if((x51478.==(0.0))) {
            } else {
              val x80020 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x51477);
              if((x80020.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x51477)
              } else {
                x80020._4 +=(x51478)
                if(((x80020._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x80020)
                } else {
                }
              }
            }
          
          }
        }), x106793)
      }
      x51170._1_=(lineitem_orderkey)
      val x106821 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51170);
      if((x106821.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51170, ({ x901: SEntry4_LLLL => {
            x51499._1_=(lineitem_partkey)
            x51499._2_=(lineitem_suppkey)
            x51499._3_=((x901._2))
            x51499._4_=((x901._3))
            x51499._5_=(((x901._4).*(x688)))
            val x51500 = x51499._5;
            if((x51500.==(0.0))) {
            } else {
              val x80048 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx0.get(x51499);
              if((x80048.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.unsafeInsert(x51499)
              } else {
                x80048._5 +=(x51500)
                if(((x80048._5).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.delete(x80048)
                } else {
                }
              }
            }
          
          }
        }), x106821)
      }
      x51173._1_=(lineitem_suppkey)
      val x80063 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51173);
      x51178._1_=(lineitem_orderkey)
      val x106854 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51178);
      if((x106854.isEmpty)) {
      } else {
        val x926 = if((x80063.==(null))) {
        0L
        } else {
        (x80063._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51178, ({ x928: SEntry4_LLLL => {
            x51527._1_=(lineitem_partkey)
            x51527._2_=((x928._2))
            x51527._3_=((x928._3))
            x51527._4_=((x926.*(((x928._4).*(x688)))))
            val x51528 = x51527._4;
            if((x51528.==(0.0))) {
            } else {
              val x80082 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x51527);
              if((x80082.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x51527)
              } else {
                x80082._4 +=(x51528)
                if(((x80082._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x80082)
                } else {
                }
              }
            }
          
          }
        }), x106854)
      }
      x51181._1_=(lineitem_partkey)
      val x80096 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51181);
      x51186._1_=(lineitem_orderkey)
      val x106885 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x51186);
      if((x106885.isEmpty)) {
      } else {
        val x954 = if((x80096.==(null))) {
        0L
        } else {
        (x80096._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x51186, ({ x956: SEntry3_LLL => {
            x51554._1_=(lineitem_suppkey)
            x51554._2_=((x956._2))
            x51554._3_=((x954.*(((x956._3).*(x688)))))
            val x51555 = x51554._3;
            if((x51555.==(0.0))) {
            } else {
              val x80113 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x51554);
              if((x80113.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x51554)
              } else {
                x80113._3 +=(x51555)
                if(((x80113._3).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.delete(x80113)
                } else {
                }
              }
            }
          
          }
        }), x106885)
      }
      x51189._1_=(lineitem_orderkey)
      val x106911 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x51189);
      if((x106911.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x51189, ({ x978: SEntry3_LLL => {
            x51575._1_=(lineitem_partkey)
            x51575._2_=(lineitem_suppkey)
            x51575._3_=((x978._2))
            x51575._4_=(((x978._3).*(x688)))
            val x51576 = x51575._4;
            if((x51576.==(0.0))) {
            } else {
              val x80138 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x51575);
              if((x80138.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x51575)
              } else {
                x80138._4 +=(x51576)
                if(((x80138._4).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x80138)
                } else {
                }
              }
            }
          
          }
        }), x106911)
      }
      x51192._1_=(lineitem_suppkey)
      val x80152 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x51192);
      x51197._1_=(lineitem_orderkey)
      val x106942 = MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceRes(x51197);
      if((x106942.isEmpty)) {
      } else {
        val x1002 = if((x80152.==(null))) {
        0L
        } else {
        (x80152._2)
        };
        MKT_SHARE_mPART1_mLINEITEM3Idx1.sliceResMapNoUpd(x51197, ({ x1004: SEntry3_LLL => {
            x51602._1_=(lineitem_partkey)
            x51602._2_=((x1004._2))
            x51602._3_=((x1002.*(((x1004._3).*(x688)))))
            val x51603 = x51602._3;
            if((x51603.==(0.0))) {
            } else {
              val x80169 = MKT_SHARE_mPART1_mPART2Idx0.get(x51602);
              if((x80169.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x51602)
              } else {
                x80169._3 +=(x51603)
                if(((x80169._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x80169)
                } else {
                }
              }
            }
          
          }
        }), x106942)
      }
      x51200._1_=(lineitem_partkey)
      val x80182 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51200);
      x51205._1_=(lineitem_suppkey)
      val x80187 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51205);
      x51210._1_=(lineitem_orderkey)
      val x106978 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x51210);
      if((x106978.isEmpty)) {
      } else {
        val x1034 = if((x80187.==(null))) {
        0L
        } else {
        (x80187._2)
        };
        val x1029 = if((x80182.==(null))) {
        0L
        } else {
        (x80182._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x51210, ({ x1036: SEntry3_LLL => {
            x51635._1_=((x1036._2))
            x51635._2_=((x1029.*((x1034.*(((x1036._3).*(x688)))))))
            val x51636 = x51635._2;
            if((x51636.==(0.0))) {
            } else {
              val x80204 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x51635);
              if((x80204.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x51635)
              } else {
                x80204._2 +=(x51636)
                if(((x80204._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x80204)
                } else {
                }
              }
            }
          
          }
        }), x106978)
      }
      x51213._1_=(lineitem_partkey)
      val x80216 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51213);
      x51218._1_=(lineitem_suppkey)
      val x80221 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51218);
      x51223._1_=(lineitem_orderkey)
      val x107016 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51223);
      if((x107016.isEmpty)) {
      } else {
        val x1067 = if((x80221.==(null))) {
        0L
        } else {
        (x80221._2)
        };
        val x1062 = if((x80216.==(null))) {
        0L
        } else {
        (x80216._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51223, ({ x1069: SEntry4_LLLL => {
            x51669._1_=((x1069._2))
            x51669._2_=((x1069._3))
            x51669._3_=((x1062.*((x1067.*(((x1069._4).*(x688)))))))
            val x51670 = x51669._3;
            if((x51670.==(0.0))) {
            } else {
              val x80240 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x51669);
              if((x80240.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x51669)
              } else {
                x80240._3 +=(x51670)
                if(((x80240._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x80240)
                } else {
                }
              }
            }
          
          }
        }), x107016)
      }
      x51226._1_=(lineitem_partkey)
      val x80253 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51226);
      x51231._1_=(lineitem_orderkey)
      val x107049 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51231);
      if((x107049.isEmpty)) {
      } else {
        val x1096 = if((x80253.==(null))) {
        0L
        } else {
        (x80253._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51231, ({ x1098: SEntry4_LLLL => {
            x51697._1_=(lineitem_suppkey)
            x51697._2_=((x1098._2))
            x51697._3_=((x1098._3))
            x51697._4_=((x1096.*(((x1098._4).*(x688)))))
            val x51698 = x51697._4;
            if((x51698.==(0.0))) {
            } else {
              val x80272 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x51697);
              if((x80272.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x51697)
              } else {
                x80272._4 +=(x51698)
                if(((x80272._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x80272)
                } else {
                }
              }
            }
          
          }
        }), x107049)
      }
      x51234._1_=(lineitem_orderkey)
      val x107077 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51234);
      if((x107077.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51234, ({ x1121: SEntry4_LLLL => {
            x51719._1_=(lineitem_partkey)
            x51719._2_=(lineitem_suppkey)
            x51719._3_=((x1121._2))
            x51719._4_=((x1121._3))
            x51719._5_=(((x1121._4).*(x688)))
            val x51720 = x51719._5;
            if((x51720.==(0.0))) {
            } else {
              val x80300 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx0.get(x51719);
              if((x80300.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.unsafeInsert(x51719)
              } else {
                x80300._5 +=(x51720)
                if(((x80300._5).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.delete(x80300)
                } else {
                }
              }
            }
          
          }
        }), x107077)
      }
      x51237._1_=(lineitem_suppkey)
      val x80315 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51237);
      x51242._1_=(lineitem_orderkey)
      val x107110 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceRes(x51242);
      if((x107110.isEmpty)) {
      } else {
        val x1146 = if((x80315.==(null))) {
        0L
        } else {
        (x80315._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx2.sliceResMapNoUpd(x51242, ({ x1148: SEntry4_LLLL => {
            x51747._1_=(lineitem_partkey)
            x51747._2_=((x1148._2))
            x51747._3_=((x1148._3))
            x51747._4_=((x1146.*(((x1148._4).*(x688)))))
            val x51748 = x51747._4;
            if((x51748.==(0.0))) {
            } else {
              val x80334 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x51747);
              if((x80334.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x51747)
              } else {
                x80334._4 +=(x51748)
                if(((x80334._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x80334)
                } else {
                }
              }
            }
          
          }
        }), x107110)
      }
      x51245._1_=(lineitem_partkey)
      val x80348 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x51245);
      x51250._1_=(lineitem_orderkey)
      val x107141 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x51250);
      if((x107141.isEmpty)) {
      } else {
        val x1174 = if((x80348.==(null))) {
        0L
        } else {
        (x80348._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x51250, ({ x1176: SEntry3_LLL => {
            x51774._1_=(lineitem_suppkey)
            x51774._2_=((x1176._2))
            x51774._3_=((x1174.*(((x1176._3).*(x688)))))
            val x51775 = x51774._3;
            if((x51775.==(0.0))) {
            } else {
              val x80365 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x51774);
              if((x80365.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x51774)
              } else {
                x80365._3 +=(x51775)
                if(((x80365._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x80365)
                } else {
                }
              }
            }
          
          }
        }), x107141)
      }
      x51253._1_=(lineitem_orderkey)
      val x107167 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x51253);
      if((x107167.isEmpty)) {
      } else {
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x51253, ({ x1198: SEntry3_LLL => {
            x51795._1_=(lineitem_partkey)
            x51795._2_=(lineitem_suppkey)
            x51795._3_=((x1198._2))
            x51795._4_=(((x1198._3).*(x688)))
            val x51796 = x51795._4;
            if((x51796.==(0.0))) {
            } else {
              val x80390 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x51795);
              if((x80390.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x51795)
              } else {
                x80390._4 +=(x51796)
                if(((x80390._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x80390)
                } else {
                }
              }
            }
          
          }
        }), x107167)
      }
      x51256._1_=(lineitem_suppkey)
      val x80404 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x51256);
      x51261._1_=(lineitem_orderkey)
      val x107198 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceRes(x51261);
      if((x107198.isEmpty)) {
      } else {
        val x1222 = if((x80404.==(null))) {
        0L
        } else {
        (x80404._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx1.sliceResMapNoUpd(x51261, ({ x1224: SEntry3_LLL => {
            x51822._1_=(lineitem_partkey)
            x51822._2_=((x1224._2))
            x51822._3_=((x1222.*(((x1224._3).*(x688)))))
            val x51823 = x51822._3;
            if((x51823.==(0.0))) {
            } else {
              val x80421 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x51822);
              if((x80421.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x51822)
              } else {
                x80421._3 +=(x51823)
                if(((x80421._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x80421)
                } else {
                }
              }
            }
          
          }
        }), x107198)
      }
      MKT_SHARE.clear
      val x107238 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x107238.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x1246: SEntry2_LD => {
            val x1249 = Udate_year((x1246._1));
            var x1250: Double = 0.0;
            x51844._1_=(x1249)
            val x80441 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x51844);
            val x1255 = if((x80441.==(null))) {
            0.0
            } else {
            (x80441._2)
            };
            val x1257 = if((1L.>(x1255))) {
            1L
            } else {
            x1255
            };
            val x1258 = x1250;
            x1250 = (x1258.+(x1257))
            val x1261 = x1250;
            val x1264 = if((0.==(x1261))) {
            0.0
            } else {
            (1.0./(x1261))
            };
            x51859._1_=(x1249)
            x51859._2_=(((x1246._2).*(x1264)))
            val x51860 = x51859._2;
            if((x51860.==(0.0))) {
            } else {
              val x80460 = MKT_SHAREIdx0.get(x51859);
              if((x80460.==(null))) {
                MKT_SHARE.unsafeInsert(x51859)
              } else {
                x80460._2 +=(x51860)
                if(((x80460._2).==(0.0))) {
                  MKT_SHARE.delete(x80460)
                } else {
                }
              }
            }
          
          }
        }), x107238)
      }
    
    }
  
  }
  def onAddORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Long, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    {
      val x1291 = Udate_year(orders_orderdate);
      var x1292: Double = 0.0;
      var x1293: Double = 0.0;
      x52484._1_=(x1291)
      val x81167 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x52484);
      val x1298 = if((x81167.==(null))) {
      0.0
      } else {
      (x81167._2)
      };
      val x1300 = orders_orderdate.>=(c1);
      val x1302 = c2.>=(orders_orderdate);
      x52491._1_=(orders_custkey)
      val x81174 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52491);
      val x1307 = if((x81174.==(null))) {
      0L
      } else {
      (x81174._2)
      };
      x52496._1_=(orders_orderkey)
      val x81179 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x52496);
      val x1312 = if((x81179.==(null))) {
      0.0
      } else {
      (x81179._2)
      };
      val x1314 = if(x1302) {
      (x1307.*(x1312))
      } else {
      0.0
      };
      val x1315 = if(x1300) {
      x1314
      } else {
      0.0
      };
      val x1316 = x1298.+(x1315);
      val x1318 = if((1L.>(x1316))) {
      1L
      } else {
      x1316
      };
      val x1319 = x1293;
      x1293 = (x1319.+(x1318))
      val x1322 = x1293;
      val x107286 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x107286.isEmpty)) {
      } else {
        val x1330 = if((0.==(x1322))) {
        0.0
        } else {
        (1.0./(x1322))
        };
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x1323: SEntry2_LD => {
            val x1331 = if(((Udate_year((x1323._1))).==(x1291))) {
            x1330
            } else {
            0.0
            };
            val x1333 = x1292;
            x1292 = (x1333.+(((x1323._2).*(x1331))))
            ()
          }
        }), x107286)
      }
      val x1338 = x1292;
      var x1339: Double = 0.0;
      var x1340: Double = 0.0;
      x52519._1_=(x1291)
      val x81212 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x52519);
      val x1345 = if((x81212.==(null))) {
      0.0
      } else {
      (x81212._2)
      };
      val x1347 = if((1L.>(x1345))) {
      1L
      } else {
      x1345
      };
      val x1348 = x1340;
      x1340 = (x1348.+(x1347))
      val x1351 = x1340;
      val x107318 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x107318.isEmpty)) {
      } else {
        val x1359 = if((0.==(x1351))) {
        0.0
        } else {
        (1.0./(x1351))
        };
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x1352: SEntry2_LD => {
            val x1360 = if(((Udate_year((x1352._1))).==(x1291))) {
            x1359
            } else {
            0.0
            };
            val x1362 = x1339;
            x1339 = (x1362.+(((x1352._2).*(x1360))))
            ()
          }
        }), x107318)
      }
      val x1367 = x1339;
      x52537._1_=(orders_orderkey)
      val x81240 = MKT_SHARE_mORDERS6Idx0.get(x52537);
      val x1373 = if((x81240.==(null))) {
      0.0
      } else {
      (x81240._2)
      };
      x52542._1_=(orders_custkey)
      val x81245 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52542);
      val x1378 = if((x81245.==(null))) {
      0L
      } else {
      (x81245._2)
      };
      var x1379: Double = 0.0;
      var x1380: Double = 0.0;
      x52549._1_=(x1291)
      val x81252 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x52549);
      val x1385 = if((x81252.==(null))) {
      0.0
      } else {
      (x81252._2)
      };
      x52554._1_=(orders_orderkey)
      val x81257 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x52554);
      val x1390 = if((x81257.==(null))) {
      0.0
      } else {
      (x81257._2)
      };
      x52559._1_=(orders_custkey)
      val x81262 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52559);
      val x1395 = if((x81262.==(null))) {
      0L
      } else {
      (x81262._2)
      };
      val x1397 = x1385.+((x1390.*(x1395)));
      val x1399 = if((1L.>(x1397))) {
      1L
      } else {
      x1397
      };
      val x1400 = x1380;
      x1380 = (x1400.+(x1399))
      val x1403 = x1380;
      val x1406 = if((0.==(x1403))) {
      0.0
      } else {
      (1.0./(x1403))
      };
      val x1407 = x1379;
      x1379 = (x1407.+(x1406))
      val x1410 = x1379;
      val x1413 = if(x1302) {
      (x1373.*((x1378.*(x1410))))
      } else {
      0.0
      };
      val x1414 = if(x1300) {
      x1413
      } else {
      0.0
      };
      x52585._1_=(x1291)
      x52585._2_=((x1338.+(((x1367.unary_-).+(x1414)))))
      val x52586 = x52585._2;
      if((x52586.==(0.0))) {
      } else {
        val x81292 = MKT_SHAREIdx0.get(x52585);
        if((x81292.==(null))) {
          MKT_SHARE.unsafeInsert(x52585)
        } else {
          x81292._2 +=(x52586)
          if(((x81292._2).==(0.0))) {
            MKT_SHARE.delete(x81292)
          } else {
          }
        }
      }
      if(x1302) {
        if(x1300) {
          x52601._1_=(orders_custkey)
          val x81305 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52601);
          val x1435 = if((x81305.==(null))) {
          0L
          } else {
          (x81305._2)
          };
          x52606._1_=(orders_orderkey)
          val x81310 = MKT_SHARE_mORDERS6Idx0.get(x52606);
          val x1440 = if((x81310.==(null))) {
          0.0
          } else {
          (x81310._2)
          };
          x52612._1_=(orders_orderdate)
          x52612._2_=((x1435.*(x1440)))
          val x52613 = x52612._2;
          if((x52613.==(0.0))) {
          } else {
            val x81320 = MKT_SHARE_mPART1Idx0.get(x52612);
            if((x81320.==(null))) {
              MKT_SHARE_mPART1.unsafeInsert(x52612)
            } else {
              x81320._2 +=(x52613)
              if(((x81320._2).==(0.0))) {
                MKT_SHARE_mPART1.delete(x81320)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1300) {
        if(x1302) {
          x52628._1_=(orders_orderkey)
          val x81333 = MKT_SHARE_mORDERS6Idx0.get(x52628);
          val x1462 = if((x81333.==(null))) {
          0.0
          } else {
          (x81333._2)
          };
          x52633._1_=(orders_custkey)
          x52633._2_=(orders_orderdate)
          x52633._3_=(x1462)
          val x52634 = x52633._3;
          if((x52634.==(0.0))) {
          } else {
            val x81343 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x52633);
            if((x81343.==(null))) {
              MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x52633)
            } else {
              x81343._3 +=(x52634)
              if(((x81343._3).==(0.0))) {
                MKT_SHARE_mPART1_mCUSTOMER1.delete(x81343)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        x52649._1_=(orders_orderkey)
        x52649._2_=(orders_custkey)
        x52649._3_=(orders_orderdate)
        x52649._4_=((if(x1300) 1L else 0L))
        val x52650 = x52649._4;
        if((x52650.==(0L))) {
        } else {
          val x81363 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx0.get(x52649);
          if((x81363.==(null))) {
            MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.unsafeInsert(x52649)
          } else {
            x81363._4 +=(x52650)
            if(((x81363._4).==(0L))) {
              MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.delete(x81363)
            } else {
            }
          }
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52665._1_=(orders_orderkey)
          val x107476 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x52665);
          if((x107476.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x52665, ({ x1496: SEntry3_LLD => {
                x53068._1_=((x1496._2))
                x53068._2_=(orders_custkey)
                x53068._3_=(orders_orderdate)
                x53068._4_=((x1496._3))
                val x53069 = x53068._4;
                if((x53069.==(0.0))) {
                } else {
                  val x81389 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x53068);
                  if((x81389.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x53068)
                  } else {
                    x81389._4 +=(x53069)
                    if(((x81389._4).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x81389)
                    } else {
                    }
                  }
                }
              
              }
            }), x107476)
          }
        } else {
        }
      } else {
      }
      if(x1300) {
        if(x1302) {
          x52670._1_=(orders_orderkey)
          val x107505 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x52670);
          if((x107505.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x52670, ({ x1518: SEntry4_LLLD => {
                x53091._1_=((x1518._2))
                x53091._2_=((x1518._3))
                x53091._3_=(orders_custkey)
                x53091._4_=(orders_orderdate)
                x53091._5_=((x1518._4))
                val x53092 = x53091._5;
                if((x53092.==(0.0))) {
                } else {
                  val x81418 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx0.get(x53091);
                  if((x81418.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.unsafeInsert(x53091)
                  } else {
                    x81418._5 +=(x53092)
                    if(((x81418._5).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.delete(x81418)
                    } else {
                    }
                  }
                }
              
              }
            }), x107505)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52675._1_=(orders_orderkey)
          val x107532 = MKT_SHARE_mORDERS6_mPART2Idx2.sliceRes(x52675);
          if((x107532.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS6_mPART2Idx2.sliceResMapNoUpd(x52675, ({ x1541: SEntry3_LLD => {
                x53113._1_=((x1541._2))
                x53113._2_=(orders_custkey)
                x53113._3_=(orders_orderdate)
                x53113._4_=((x1541._3))
                val x53114 = x53113._4;
                if((x53114.==(0.0))) {
                } else {
                  val x81446 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x53113);
                  if((x81446.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x53113)
                  } else {
                    x81446._4 +=(x53114)
                    if(((x81446._4).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x81446)
                    } else {
                    }
                  }
                }
              
              }
            }), x107532)
          }
        } else {
        }
      } else {
      }
      if(x1300) {
        if(x1302) {
          x52680._1_=(orders_custkey)
          val x81462 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52680);
          val x1566 = if((x81462.==(null))) {
          0L
          } else {
          (x81462._2)
          };
          x52685._1_=(orders_orderkey)
          x52685._2_=(orders_orderdate)
          x52685._3_=(x1566)
          val x52686 = x52685._3;
          if((x52686.==(0L))) {
          } else {
            val x81472 = MKT_SHARE_mPART1_mLINEITEM3Idx0.get(x52685);
            if((x81472.==(null))) {
              MKT_SHARE_mPART1_mLINEITEM3.unsafeInsert(x52685)
            } else {
              x81472._3 +=(x52686)
              if(((x81472._3).==(0L))) {
                MKT_SHARE_mPART1_mLINEITEM3.delete(x81472)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52701._1_=(orders_custkey)
          val x81486 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52701);
          x52706._1_=(orders_orderkey)
          val x107586 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x52706);
          if((x107586.isEmpty)) {
          } else {
            val x1587 = if((x81486.==(null))) {
            0L
            } else {
            (x81486._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x52706, ({ x1589: SEntry3_LLD => {
                x53162._1_=((x1589._2))
                x53162._2_=(orders_orderdate)
                x53162._3_=((x1587.*((x1589._3))))
                val x53163 = x53162._3;
                if((x53163.==(0.0))) {
                } else {
                  val x81502 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x53162);
                  if((x81502.==(null))) {
                    MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x53162)
                  } else {
                    x81502._3 +=(x53163)
                    if(((x81502._3).==(0.0))) {
                      MKT_SHARE_mPART1_mSUPPLIER2.delete(x81502)
                    } else {
                    }
                  }
                }
              
              }
            }), x107586)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52711._1_=(orders_custkey)
          val x81517 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52711);
          x52716._1_=(orders_orderkey)
          val x107620 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x52716);
          if((x107620.isEmpty)) {
          } else {
            val x1615 = if((x81517.==(null))) {
            0L
            } else {
            (x81517._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x52716, ({ x1617: SEntry4_LLLD => {
                x53191._1_=((x1617._2))
                x53191._2_=((x1617._3))
                x53191._3_=(orders_orderdate)
                x53191._4_=((x1615.*((x1617._4))))
                val x53192 = x53191._4;
                if((x53192.==(0.0))) {
                } else {
                  val x81535 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x53191);
                  if((x81535.==(null))) {
                    MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x53191)
                  } else {
                    x81535._4 +=(x53192)
                    if(((x81535._4).==(0.0))) {
                      MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x81535)
                    } else {
                    }
                  }
                }
              
              }
            }), x107620)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52721._1_=(orders_custkey)
          val x81551 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52721);
          x52726._1_=(orders_orderkey)
          val x107652 = MKT_SHARE_mORDERS6_mPART2Idx2.sliceRes(x52726);
          if((x107652.isEmpty)) {
          } else {
            val x1644 = if((x81551.==(null))) {
            0L
            } else {
            (x81551._2)
            };
            MKT_SHARE_mORDERS6_mPART2Idx2.sliceResMapNoUpd(x52726, ({ x1646: SEntry3_LLD => {
                x53219._1_=((x1646._2))
                x53219._2_=(orders_orderdate)
                x53219._3_=((x1644.*((x1646._3))))
                val x53220 = x53219._3;
                if((x53220.==(0.0))) {
                } else {
                  val x81567 = MKT_SHARE_mPART1_mPART2Idx0.get(x53219);
                  if((x81567.==(null))) {
                    MKT_SHARE_mPART1_mPART2.unsafeInsert(x53219)
                  } else {
                    x81567._3 +=(x53220)
                    if(((x81567._3).==(0.0))) {
                      MKT_SHARE_mPART1_mPART2.delete(x81567)
                    } else {
                    }
                  }
                }
              
              }
            }), x107652)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52731._1_=(orders_custkey)
          val x81582 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52731);
          val x1672 = if((x81582.==(null))) {
          0L
          } else {
          (x81582._2)
          };
          x52736._1_=(orders_orderkey)
          val x81587 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x52736);
          val x1677 = if((x81587.==(null))) {
          0.0
          } else {
          (x81587._2)
          };
          x52742._1_=(x1291)
          x52742._2_=((x1672.*(x1677)))
          val x52743 = x52742._2;
          if((x52743.==(0.0))) {
          } else {
            val x81597 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x52742);
            if((x81597.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x52742)
            } else {
              x81597._2 +=(x52743)
              if(((x81597._2).==(0.0))) {
                MKT_SHARE_mPART1_L2_1_L1_1.delete(x81597)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52758._1_=(orders_orderkey)
          val x81610 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x52758);
          val x1699 = if((x81610.==(null))) {
          0.0
          } else {
          (x81610._2)
          };
          x52763._1_=(orders_custkey)
          x52763._2_=(x1291)
          x52763._3_=(x1699)
          val x52764 = x52763._3;
          if((x52764.==(0.0))) {
          } else {
            val x81620 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x52763);
            if((x81620.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x52763)
            } else {
              x81620._3 +=(x52764)
              if(((x81620._3).==(0.0))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x81620)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52779._1_=(orders_orderkey)
          x52779._2_=(orders_custkey)
          x52779._3_=(x1291)
          x52779._4_=(1L)
          val x52780 = x52779._4;
          if((x52780.==(0L))) {
          } else {
            val x81640 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx0.get(x52779);
            if((x81640.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.unsafeInsert(x52779)
            } else {
              x81640._4 +=(x52780)
              if(((x81640._4).==(0L))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.delete(x81640)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52795._1_=(orders_orderkey)
          val x107746 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x52795);
          if((x107746.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x52795, ({ x1733: SEntry3_LLD => {
                x53305._1_=((x1733._2))
                x53305._2_=(orders_custkey)
                x53305._3_=(x1291)
                x53305._4_=((x1733._3))
                val x53306 = x53305._4;
                if((x53306.==(0.0))) {
                } else {
                  val x81666 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x53305);
                  if((x81666.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x53305)
                  } else {
                    x81666._4 +=(x53306)
                    if(((x81666._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x81666)
                    } else {
                    }
                  }
                }
              
              }
            }), x107746)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52800._1_=(orders_orderkey)
          val x107775 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x52800);
          if((x107775.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x52800, ({ x1755: SEntry4_LLLD => {
                x53328._1_=((x1755._2))
                x53328._2_=((x1755._3))
                x53328._3_=(orders_custkey)
                x53328._4_=(x1291)
                x53328._5_=((x1755._4))
                val x53329 = x53328._5;
                if((x53329.==(0.0))) {
                } else {
                  val x81695 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx0.get(x53328);
                  if((x81695.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.unsafeInsert(x53328)
                  } else {
                    x81695._5 +=(x53329)
                    if(((x81695._5).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.delete(x81695)
                    } else {
                    }
                  }
                }
              
              }
            }), x107775)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52805._1_=(orders_orderkey)
          val x107802 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceRes(x52805);
          if((x107802.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceResMapNoUpd(x52805, ({ x1778: SEntry3_LLD => {
                x53350._1_=((x1778._2))
                x53350._2_=(orders_custkey)
                x53350._3_=(x1291)
                x53350._4_=((x1778._3))
                val x53351 = x53350._4;
                if((x53351.==(0.0))) {
                } else {
                  val x81723 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x53350);
                  if((x81723.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x53350)
                  } else {
                    x81723._4 +=(x53351)
                    if(((x81723._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x81723)
                    } else {
                    }
                  }
                }
              
              }
            }), x107802)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52810._1_=(orders_custkey)
          val x81739 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52810);
          val x1803 = if((x81739.==(null))) {
          0L
          } else {
          (x81739._2)
          };
          x52815._1_=(orders_orderkey)
          x52815._2_=(x1291)
          x52815._3_=(x1803)
          val x52816 = x52815._3;
          if((x52816.==(0L))) {
          } else {
            val x81749 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx0.get(x52815);
            if((x81749.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.unsafeInsert(x52815)
            } else {
              x81749._3 +=(x52816)
              if(((x81749._3).==(0L))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.delete(x81749)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52831._1_=(orders_custkey)
          val x81763 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52831);
          x52836._1_=(orders_orderkey)
          val x107856 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x52836);
          if((x107856.isEmpty)) {
          } else {
            val x1824 = if((x81763.==(null))) {
            0L
            } else {
            (x81763._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x52836, ({ x1826: SEntry3_LLD => {
                x53399._1_=((x1826._2))
                x53399._2_=(x1291)
                x53399._3_=((x1824.*((x1826._3))))
                val x53400 = x53399._3;
                if((x53400.==(0.0))) {
                } else {
                  val x81779 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x53399);
                  if((x81779.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x53399)
                  } else {
                    x81779._3 +=(x53400)
                    if(((x81779._3).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x81779)
                    } else {
                    }
                  }
                }
              
              }
            }), x107856)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52841._1_=(orders_custkey)
          val x81794 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52841);
          x52846._1_=(orders_orderkey)
          val x107890 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x52846);
          if((x107890.isEmpty)) {
          } else {
            val x1852 = if((x81794.==(null))) {
            0L
            } else {
            (x81794._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x52846, ({ x1854: SEntry4_LLLD => {
                x53428._1_=((x1854._2))
                x53428._2_=((x1854._3))
                x53428._3_=(x1291)
                x53428._4_=((x1852.*((x1854._4))))
                val x53429 = x53428._4;
                if((x53429.==(0.0))) {
                } else {
                  val x81812 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x53428);
                  if((x81812.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x53428)
                  } else {
                    x81812._4 +=(x53429)
                    if(((x81812._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x81812)
                    } else {
                    }
                  }
                }
              
              }
            }), x107890)
          }
        } else {
        }
      } else {
      }
      if(x1302) {
        if(x1300) {
          x52851._1_=(orders_custkey)
          val x81828 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x52851);
          x52856._1_=(orders_orderkey)
          val x107922 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceRes(x52856);
          if((x107922.isEmpty)) {
          } else {
            val x1881 = if((x81828.==(null))) {
            0L
            } else {
            (x81828._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceResMapNoUpd(x52856, ({ x1883: SEntry3_LLD => {
                x53456._1_=((x1883._2))
                x53456._2_=(x1291)
                x53456._3_=((x1881.*((x1883._3))))
                val x53457 = x53456._3;
                if((x53457.==(0.0))) {
                } else {
                  val x81844 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x53456);
                  if((x81844.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x53456)
                  } else {
                    x81844._3 +=(x53457)
                    if(((x81844._3).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x81844)
                    } else {
                    }
                  }
                }
              
              }
            }), x107922)
          }
        } else {
        }
      } else {
      }
    
    }
  
  }
  def onDelORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Long, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    {
      val x1914 = Udate_year(orders_orderdate);
      var x1915: Double = 0.0;
      var x1916: Double = 0.0;
      x54086._1_=(x1914)
      val x82553 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x54086);
      val x1921 = if((x82553.==(null))) {
      0.0
      } else {
      (x82553._2)
      };
      val x1922 = orders_orderdate.>=(c1);
      val x1923 = c2.>=(orders_orderdate);
      x54093._1_=(orders_custkey)
      val x82560 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54093);
      val x1928 = if((x82560.==(null))) {
      0L
      } else {
      (x82560._2)
      };
      x54098._1_=(orders_orderkey)
      val x82565 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x54098);
      val x1933 = if((x82565.==(null))) {
      0.0
      } else {
      (x82565._2)
      };
      val x1936 = if(x1923) {
      (x1928.*((x1933.unary_-)))
      } else {
      0.0
      };
      val x1937 = if(x1922) {
      x1936
      } else {
      0.0
      };
      val x1938 = x1921.+(x1937);
      val x1940 = if((1L.>(x1938))) {
      1L
      } else {
      x1938
      };
      val x1941 = x1916;
      x1916 = (x1941.+(x1940))
      val x1944 = x1916;
      val x107971 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x107971.isEmpty)) {
      } else {
        val x1952 = if((0.==(x1944))) {
        0.0
        } else {
        (1.0./(x1944))
        };
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x1945: SEntry2_LD => {
            val x1953 = if(((Udate_year((x1945._1))).==(x1914))) {
            x1952
            } else {
            0.0
            };
            val x1955 = x1915;
            x1915 = (x1955.+(((x1945._2).*(x1953))))
            ()
          }
        }), x107971)
      }
      val x1960 = x1915;
      var x1961: Double = 0.0;
      var x1962: Double = 0.0;
      x54122._1_=(x1914)
      val x82599 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x54122);
      val x1967 = if((x82599.==(null))) {
      0.0
      } else {
      (x82599._2)
      };
      val x1969 = if((1L.>(x1967))) {
      1L
      } else {
      x1967
      };
      val x1970 = x1962;
      x1962 = (x1970.+(x1969))
      val x1973 = x1962;
      val x108003 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x108003.isEmpty)) {
      } else {
        val x1981 = if((0.==(x1973))) {
        0.0
        } else {
        (1.0./(x1973))
        };
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x1974: SEntry2_LD => {
            val x1982 = if(((Udate_year((x1974._1))).==(x1914))) {
            x1981
            } else {
            0.0
            };
            val x1984 = x1961;
            x1961 = (x1984.+(((x1974._2).*(x1982))))
            ()
          }
        }), x108003)
      }
      val x1989 = x1961;
      x54140._1_=(orders_orderkey)
      val x82627 = MKT_SHARE_mORDERS6Idx0.get(x54140);
      val x1995 = if((x82627.==(null))) {
      0.0
      } else {
      (x82627._2)
      };
      x54145._1_=(orders_custkey)
      val x82632 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54145);
      val x2000 = if((x82632.==(null))) {
      0L
      } else {
      (x82632._2)
      };
      var x2001: Double = 0.0;
      var x2002: Double = 0.0;
      x54152._1_=(x1914)
      val x82639 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x54152);
      val x2007 = if((x82639.==(null))) {
      0.0
      } else {
      (x82639._2)
      };
      x54157._1_=(orders_orderkey)
      val x82644 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x54157);
      val x2012 = if((x82644.==(null))) {
      0.0
      } else {
      (x82644._2)
      };
      x54162._1_=(orders_custkey)
      val x82649 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54162);
      val x2017 = if((x82649.==(null))) {
      0L
      } else {
      (x82649._2)
      };
      val x2020 = x2007.+((x2012.*((x2017.unary_-))));
      val x2022 = if((1L.>(x2020))) {
      1L
      } else {
      x2020
      };
      val x2023 = x2002;
      x2002 = (x2023.+(x2022))
      val x2026 = x2002;
      val x2029 = if((0.==(x2026))) {
      0.0
      } else {
      (1.0./(x2026))
      };
      val x2030 = x2001;
      x2001 = (x2030.+(x2029))
      val x2033 = x2001;
      val x2037 = if(x1923) {
      (x1995.*((x2000.*((x2033.unary_-)))))
      } else {
      0.0
      };
      val x2038 = if(x1922) {
      x2037
      } else {
      0.0
      };
      x54190._1_=(x1914)
      x54190._2_=((x1960.+(((x1989.unary_-).+(x2038)))))
      val x54191 = x54190._2;
      if((x54191.==(0.0))) {
      } else {
        val x82681 = MKT_SHAREIdx0.get(x54190);
        if((x82681.==(null))) {
          MKT_SHARE.unsafeInsert(x54190)
        } else {
          x82681._2 +=(x54191)
          if(((x82681._2).==(0.0))) {
            MKT_SHARE.delete(x82681)
          } else {
          }
        }
      }
      if(x1922) {
        if(x1923) {
          x54206._1_=(orders_orderkey)
          val x82694 = MKT_SHARE_mORDERS6Idx0.get(x54206);
          val x2059 = if((x82694.==(null))) {
          0.0
          } else {
          (x82694._2)
          };
          x54211._1_=(orders_custkey)
          val x82699 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54211);
          val x2064 = if((x82699.==(null))) {
          0L
          } else {
          (x82699._2)
          };
          x54218._1_=(orders_orderdate)
          x54218._2_=((x2059.*((x2064.unary_-))))
          val x54219 = x54218._2;
          if((x54219.==(0.0))) {
          } else {
            val x82710 = MKT_SHARE_mPART1Idx0.get(x54218);
            if((x82710.==(null))) {
              MKT_SHARE_mPART1.unsafeInsert(x54218)
            } else {
              x82710._2 +=(x54219)
              if(((x82710._2).==(0.0))) {
                MKT_SHARE_mPART1.delete(x82710)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54234._1_=(orders_orderkey)
          val x82723 = MKT_SHARE_mORDERS6Idx0.get(x54234);
          val x2087 = if((x82723.==(null))) {
          0.0
          } else {
          (x82723._2)
          };
          x54240._1_=(orders_custkey)
          x54240._2_=(orders_orderdate)
          x54240._3_=((x2087.unary_-))
          val x54241 = x54240._3;
          if((x54241.==(0.0))) {
          } else {
            val x82734 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x54240);
            if((x82734.==(null))) {
              MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x54240)
            } else {
              x82734._3 +=(x54241)
              if(((x82734._3).==(0.0))) {
                MKT_SHARE_mPART1_mCUSTOMER1.delete(x82734)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54256._1_=(orders_orderkey)
          x54256._2_=(orders_custkey)
          x54256._3_=(orders_orderdate)
          x54256._4_=(-1L)
          val x54257 = x54256._4;
          if((x54257.==(0L))) {
          } else {
            val x82754 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx0.get(x54256);
            if((x82754.==(null))) {
              MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.unsafeInsert(x54256)
            } else {
              x82754._4 +=(x54257)
              if(((x82754._4).==(0L))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3.delete(x82754)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54272._1_=(orders_orderkey)
          val x108166 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x54272);
          if((x108166.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x54272, ({ x2122: SEntry3_LLD => {
                x54685._1_=((x2122._2))
                x54685._2_=(orders_custkey)
                x54685._3_=(orders_orderdate)
                x54685._4_=(((x2122._3).unary_-))
                val x54686 = x54685._4;
                if((x54686.==(0.0))) {
                } else {
                  val x82781 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x54685);
                  if((x82781.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x54685)
                  } else {
                    x82781._4 +=(x54686)
                    if(((x82781._4).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x82781)
                    } else {
                    }
                  }
                }
              
              }
            }), x108166)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54277._1_=(orders_orderkey)
          val x108196 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x54277);
          if((x108196.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x54277, ({ x2145: SEntry4_LLLD => {
                x54709._1_=((x2145._2))
                x54709._2_=((x2145._3))
                x54709._3_=(orders_custkey)
                x54709._4_=(orders_orderdate)
                x54709._5_=(((x2145._4).unary_-))
                val x54710 = x54709._5;
                if((x54710.==(0.0))) {
                } else {
                  val x82811 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx0.get(x54709);
                  if((x82811.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.unsafeInsert(x54709)
                  } else {
                    x82811._5 +=(x54710)
                    if(((x82811._5).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2.delete(x82811)
                    } else {
                    }
                  }
                }
              
              }
            }), x108196)
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54282._1_=(orders_orderkey)
          val x108224 = MKT_SHARE_mORDERS6_mPART2Idx2.sliceRes(x54282);
          if((x108224.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS6_mPART2Idx2.sliceResMapNoUpd(x54282, ({ x2169: SEntry3_LLD => {
                x54732._1_=((x2169._2))
                x54732._2_=(orders_custkey)
                x54732._3_=(orders_orderdate)
                x54732._4_=(((x2169._3).unary_-))
                val x54733 = x54732._4;
                if((x54733.==(0.0))) {
                } else {
                  val x82840 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x54732);
                  if((x82840.==(null))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x54732)
                  } else {
                    x82840._4 +=(x54733)
                    if(((x82840._4).==(0.0))) {
                      MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x82840)
                    } else {
                    }
                  }
                }
              
              }
            }), x108224)
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54287._1_=(orders_custkey)
          val x82856 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54287);
          val x2195 = if((x82856.==(null))) {
          0L
          } else {
          (x82856._2)
          };
          x54293._1_=(orders_orderkey)
          x54293._2_=(orders_orderdate)
          x54293._3_=((x2195.unary_-))
          val x54294 = x54293._3;
          if((x54294.==(0L))) {
          } else {
            val x82867 = MKT_SHARE_mPART1_mLINEITEM3Idx0.get(x54293);
            if((x82867.==(null))) {
              MKT_SHARE_mPART1_mLINEITEM3.unsafeInsert(x54293)
            } else {
              x82867._3 +=(x54294)
              if(((x82867._3).==(0L))) {
                MKT_SHARE_mPART1_mLINEITEM3.delete(x82867)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54309._1_=(orders_custkey)
          val x82881 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54309);
          x54314._1_=(orders_orderkey)
          val x108280 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x54314);
          if((x108280.isEmpty)) {
          } else {
            val x2217 = if((x82881.==(null))) {
            0L
            } else {
            (x82881._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x54314, ({ x2219: SEntry3_LLD => {
                x54783._1_=((x2219._2))
                x54783._2_=(orders_orderdate)
                x54783._3_=((x2217.*(((x2219._3).unary_-))))
                val x54784 = x54783._3;
                if((x54784.==(0.0))) {
                } else {
                  val x82898 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x54783);
                  if((x82898.==(null))) {
                    MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x54783)
                  } else {
                    x82898._3 +=(x54784)
                    if(((x82898._3).==(0.0))) {
                      MKT_SHARE_mPART1_mSUPPLIER2.delete(x82898)
                    } else {
                    }
                  }
                }
              
              }
            }), x108280)
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54319._1_=(orders_custkey)
          val x82913 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54319);
          x54324._1_=(orders_orderkey)
          val x108315 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x54324);
          if((x108315.isEmpty)) {
          } else {
            val x2246 = if((x82913.==(null))) {
            0L
            } else {
            (x82913._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x54324, ({ x2248: SEntry4_LLLD => {
                x54813._1_=((x2248._2))
                x54813._2_=((x2248._3))
                x54813._3_=(orders_orderdate)
                x54813._4_=((x2246.*(((x2248._4).unary_-))))
                val x54814 = x54813._4;
                if((x54814.==(0.0))) {
                } else {
                  val x82932 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x54813);
                  if((x82932.==(null))) {
                    MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x54813)
                  } else {
                    x82932._4 +=(x54814)
                    if(((x82932._4).==(0.0))) {
                      MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x82932)
                    } else {
                    }
                  }
                }
              
              }
            }), x108315)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54329._1_=(orders_custkey)
          val x82948 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54329);
          x54334._1_=(orders_orderkey)
          val x108348 = MKT_SHARE_mORDERS6_mPART2Idx2.sliceRes(x54334);
          if((x108348.isEmpty)) {
          } else {
            val x2276 = if((x82948.==(null))) {
            0L
            } else {
            (x82948._2)
            };
            MKT_SHARE_mORDERS6_mPART2Idx2.sliceResMapNoUpd(x54334, ({ x2278: SEntry3_LLD => {
                x54842._1_=((x2278._2))
                x54842._2_=(orders_orderdate)
                x54842._3_=((x2276.*(((x2278._3).unary_-))))
                val x54843 = x54842._3;
                if((x54843.==(0.0))) {
                } else {
                  val x82965 = MKT_SHARE_mPART1_mPART2Idx0.get(x54842);
                  if((x82965.==(null))) {
                    MKT_SHARE_mPART1_mPART2.unsafeInsert(x54842)
                  } else {
                    x82965._3 +=(x54843)
                    if(((x82965._3).==(0.0))) {
                      MKT_SHARE_mPART1_mPART2.delete(x82965)
                    } else {
                    }
                  }
                }
              
              }
            }), x108348)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54339._1_=(orders_orderkey)
          val x82980 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x54339);
          val x2305 = if((x82980.==(null))) {
          0.0
          } else {
          (x82980._2)
          };
          x54344._1_=(orders_custkey)
          val x82985 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54344);
          val x2310 = if((x82985.==(null))) {
          0L
          } else {
          (x82985._2)
          };
          x54351._1_=(x1914)
          x54351._2_=((x2305.*((x2310.unary_-))))
          val x54352 = x54351._2;
          if((x54352.==(0.0))) {
          } else {
            val x82996 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x54351);
            if((x82996.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x54351)
            } else {
              x82996._2 +=(x54352)
              if(((x82996._2).==(0.0))) {
                MKT_SHARE_mPART1_L2_1_L1_1.delete(x82996)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54367._1_=(orders_orderkey)
          val x83009 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x54367);
          val x2333 = if((x83009.==(null))) {
          0.0
          } else {
          (x83009._2)
          };
          x54373._1_=(orders_custkey)
          x54373._2_=(x1914)
          x54373._3_=((x2333.unary_-))
          val x54374 = x54373._3;
          if((x54374.==(0.0))) {
          } else {
            val x83020 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x54373);
            if((x83020.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x54373)
            } else {
              x83020._3 +=(x54374)
              if(((x83020._3).==(0.0))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x83020)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54389._1_=(orders_orderkey)
          x54389._2_=(orders_custkey)
          x54389._3_=(x1914)
          x54389._4_=(-1L)
          val x54390 = x54389._4;
          if((x54390.==(0L))) {
          } else {
            val x83040 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx0.get(x54389);
            if((x83040.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.unsafeInsert(x54389)
            } else {
              x83040._4 +=(x54390)
              if(((x83040._4).==(0L))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3.delete(x83040)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54405._1_=(orders_orderkey)
          val x108445 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x54405);
          if((x108445.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x54405, ({ x2368: SEntry3_LLD => {
                x54931._1_=((x2368._2))
                x54931._2_=(orders_custkey)
                x54931._3_=(x1914)
                x54931._4_=(((x2368._3).unary_-))
                val x54932 = x54931._4;
                if((x54932.==(0.0))) {
                } else {
                  val x83067 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x54931);
                  if((x83067.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x54931)
                  } else {
                    x83067._4 +=(x54932)
                    if(((x83067._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x83067)
                    } else {
                    }
                  }
                }
              
              }
            }), x108445)
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54410._1_=(orders_orderkey)
          val x108475 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x54410);
          if((x108475.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x54410, ({ x2391: SEntry4_LLLD => {
                x54955._1_=((x2391._2))
                x54955._2_=((x2391._3))
                x54955._3_=(orders_custkey)
                x54955._4_=(x1914)
                x54955._5_=(((x2391._4).unary_-))
                val x54956 = x54955._5;
                if((x54956.==(0.0))) {
                } else {
                  val x83097 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx0.get(x54955);
                  if((x83097.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.unsafeInsert(x54955)
                  } else {
                    x83097._5 +=(x54956)
                    if(((x83097._5).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2.delete(x83097)
                    } else {
                    }
                  }
                }
              
              }
            }), x108475)
          }
        } else {
        }
      } else {
      }
      if(x1922) {
        if(x1923) {
          x54415._1_=(orders_orderkey)
          val x108503 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceRes(x54415);
          if((x108503.isEmpty)) {
          } else {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceResMapNoUpd(x54415, ({ x2415: SEntry3_LLD => {
                x54978._1_=((x2415._2))
                x54978._2_=(orders_custkey)
                x54978._3_=(x1914)
                x54978._4_=(((x2415._3).unary_-))
                val x54979 = x54978._4;
                if((x54979.==(0.0))) {
                } else {
                  val x83126 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x54978);
                  if((x83126.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x54978)
                  } else {
                    x83126._4 +=(x54979)
                    if(((x83126._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x83126)
                    } else {
                    }
                  }
                }
              
              }
            }), x108503)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54420._1_=(orders_custkey)
          val x83142 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54420);
          val x2441 = if((x83142.==(null))) {
          0L
          } else {
          (x83142._2)
          };
          x54426._1_=(orders_orderkey)
          x54426._2_=(x1914)
          x54426._3_=((x2441.unary_-))
          val x54427 = x54426._3;
          if((x54427.==(0L))) {
          } else {
            val x83153 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx0.get(x54426);
            if((x83153.==(null))) {
              MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.unsafeInsert(x54426)
            } else {
              x83153._3 +=(x54427)
              if(((x83153._3).==(0L))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.delete(x83153)
              } else {
              }
            }
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54442._1_=(orders_custkey)
          val x83167 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54442);
          x54447._1_=(orders_orderkey)
          val x108559 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceRes(x54447);
          if((x108559.isEmpty)) {
          } else {
            val x2463 = if((x83167.==(null))) {
            0L
            } else {
            (x83167._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx2.sliceResMapNoUpd(x54447, ({ x2465: SEntry3_LLD => {
                x55029._1_=((x2465._2))
                x55029._2_=(x1914)
                x55029._3_=((x2463.*(((x2465._3).unary_-))))
                val x55030 = x55029._3;
                if((x55030.==(0.0))) {
                } else {
                  val x83184 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x55029);
                  if((x83184.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x55029)
                  } else {
                    x83184._3 +=(x55030)
                    if(((x83184._3).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x83184)
                    } else {
                    }
                  }
                }
              
              }
            }), x108559)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54452._1_=(orders_custkey)
          val x83199 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54452);
          x54457._1_=(orders_orderkey)
          val x108594 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceRes(x54457);
          if((x108594.isEmpty)) {
          } else {
            val x2492 = if((x83199.==(null))) {
            0L
            } else {
            (x83199._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x54457, ({ x2494: SEntry4_LLLD => {
                x55059._1_=((x2494._2))
                x55059._2_=((x2494._3))
                x55059._3_=(x1914)
                x55059._4_=((x2492.*(((x2494._4).unary_-))))
                val x55060 = x55059._4;
                if((x55060.==(0.0))) {
                } else {
                  val x83218 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x55059);
                  if((x83218.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x55059)
                  } else {
                    x83218._4 +=(x55060)
                    if(((x83218._4).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x83218)
                    } else {
                    }
                  }
                }
              
              }
            }), x108594)
          }
        } else {
        }
      } else {
      }
      if(x1923) {
        if(x1922) {
          x54462._1_=(orders_custkey)
          val x83234 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x54462);
          x54467._1_=(orders_orderkey)
          val x108627 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceRes(x54467);
          if((x108627.isEmpty)) {
          } else {
            val x2522 = if((x83234.==(null))) {
            0L
            } else {
            (x83234._2)
            };
            MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx2.sliceResMapNoUpd(x54467, ({ x2524: SEntry3_LLD => {
                x55088._1_=((x2524._2))
                x55088._2_=(x1914)
                x55088._3_=((x2522.*(((x2524._3).unary_-))))
                val x55089 = x55088._3;
                if((x55089.==(0.0))) {
                } else {
                  val x83251 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x55088);
                  if((x83251.==(null))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x55088)
                  } else {
                    x83251._3 +=(x55089)
                    if(((x83251._3).==(0.0))) {
                      MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x83251)
                    } else {
                    }
                  }
                }
              
              }
            }), x108627)
          }
        } else {
        }
      } else {
      }
    
    }
  
  }
  def onAddPART(part_partkey:Long, part_name:String, part_mfgr:String, part_brand:String, part_type:String, part_size:Long, part_container:String, part_retailprice:Double, part_comment:String) {
    {
      val x2556 = part_type.==("ECONOMY ANODIZED STEEL");
      if(x2556) {
        x55738._2_=(part_partkey)
        val x108652 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx1.sliceRes(x55738);
        if((x108652.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx1.sliceResMapNoUpd(x55738, ({ x2558: SEntry3_LLD => {
              x55806._1_=((x2558._1))
              x55806._2_=((x2558._3))
              val x55807 = x55806._2;
              if((x55807.==(0.0))) {
              } else {
                val x83989 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x55806);
                if((x83989.==(null))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x55806)
                } else {
                  x83989._2 +=(x55807)
                  if(((x83989._2).==(0.0))) {
                    MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x83989)
                  } else {
                  }
                }
              }
            
            }
          }), x108652)
        }
      } else {
      }
      if(x2556) {
        x55742._2_=(part_partkey)
        val x108678 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx1.sliceRes(x55742);
        if((x108678.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x55742, ({ x2579: SEntry4_LLLD => {
              x55828._1_=((x2579._1))
              x55828._2_=((x2579._3))
              x55828._3_=((x2579._4))
              val x55829 = x55828._3;
              if((x55829.==(0.0))) {
              } else {
                val x84013 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx0.get(x55828);
                if((x84013.==(null))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.unsafeInsert(x55828)
                } else {
                  x84013._3 +=(x55829)
                  if(((x84013._3).==(0.0))) {
                    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.delete(x84013)
                  } else {
                  }
                }
              }
            
            }
          }), x108678)
        }
      } else {
      }
      x55746._1_=(part_partkey)
      x55746._2_=((if(x2556) 1L else 0L))
      val x55747 = x55746._2;
      if((x55747.==(0L))) {
      } else {
        val x84032 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x55746);
        if((x84032.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.unsafeInsert(x55746)
        } else {
          x84032._2 +=(x55747)
          if(((x84032._2).==(0L))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.delete(x84032)
          } else {
          }
        }
      }
      if(x2556) {
        x55761._2_=(part_partkey)
        val x108717 = MKT_SHARE_mORDERS6_mPART2Idx1.sliceRes(x55761);
        if((x108717.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS6_mPART2Idx1.sliceResMapNoUpd(x55761, ({ x2616: SEntry3_LLD => {
              x55864._1_=((x2616._1))
              x55864._2_=((x2616._3))
              val x55865 = x55864._2;
              if((x55865.==(0.0))) {
              } else {
                val x84053 = MKT_SHARE_mORDERS6Idx0.get(x55864);
                if((x84053.==(null))) {
                  MKT_SHARE_mORDERS6.unsafeInsert(x55864)
                } else {
                  x84053._2 +=(x55865)
                  if(((x84053._2).==(0.0))) {
                    MKT_SHARE_mORDERS6.delete(x84053)
                  } else {
                  }
                }
              }
            
            }
          }), x108717)
        }
      } else {
      }
      if(x2556) {
        x55765._1_=(part_partkey)
        val x108741 = MKT_SHARE_mPART1_mPART2Idx1.sliceRes(x55765);
        if((x108741.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mPART2Idx1.sliceResMapNoUpd(x55765, ({ x2637: SEntry3_LLD => {
              x55885._1_=((x2637._2))
              x55885._2_=((x2637._3))
              val x55886 = x55885._2;
              if((x55886.==(0.0))) {
              } else {
                val x84075 = MKT_SHARE_mPART1Idx0.get(x55885);
                if((x84075.==(null))) {
                  MKT_SHARE_mPART1.unsafeInsert(x55885)
                } else {
                  x84075._2 +=(x55886)
                  if(((x84075._2).==(0.0))) {
                    MKT_SHARE_mPART1.delete(x84075)
                  } else {
                  }
                }
              }
            
            }
          }), x108741)
        }
      } else {
      }
      if(x2556) {
        x55769._1_=(part_partkey)
        val x108767 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx2.sliceRes(x55769);
        if((x108767.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx2.sliceResMapNoUpd(x55769, ({ x2658: SEntry4_LLLD => {
              x55907._1_=((x2658._2))
              x55907._2_=((x2658._3))
              x55907._3_=((x2658._4))
              val x55908 = x55907._3;
              if((x55908.==(0.0))) {
              } else {
                val x84099 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x55907);
                if((x84099.==(null))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x55907)
                } else {
                  x84099._3 +=(x55908)
                  if(((x84099._3).==(0.0))) {
                    MKT_SHARE_mPART1_mCUSTOMER1.delete(x84099)
                  } else {
                  }
                }
              }
            
            }
          }), x108767)
        }
      } else {
      }
      if(x2556) {
        x55773._1_=(part_partkey)
        val x108795 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx2.sliceRes(x55773);
        if((x108795.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx2.sliceResMapNoUpd(x55773, ({ x2680: SEntry5_LLLLD => {
              x55930._1_=((x2680._2))
              x55930._2_=((x2680._3))
              x55930._3_=((x2680._4))
              x55930._4_=((x2680._5))
              val x55931 = x55930._4;
              if((x55931.==(0.0))) {
              } else {
                val x84126 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x55930);
                if((x84126.==(null))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x55930)
                } else {
                  x84126._4 +=(x55931)
                  if(((x84126._4).==(0.0))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x84126)
                  } else {
                  }
                }
              }
            
            }
          }), x108795)
        }
      } else {
      }
      if(x2556) {
        x55777._1_=(part_partkey)
        val x108821 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx2.sliceRes(x55777);
        if((x108821.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx2.sliceResMapNoUpd(x55777, ({ x2703: SEntry4_LLLD => {
              x55952._1_=((x2703._2))
              x55952._2_=((x2703._3))
              x55952._3_=((x2703._4))
              val x55953 = x55952._3;
              if((x55953.==(0.0))) {
              } else {
                val x84152 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x55952);
                if((x84152.==(null))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x55952)
                } else {
                  x84152._3 +=(x55953)
                  if(((x84152._3).==(0.0))) {
                    MKT_SHARE_mPART1_mSUPPLIER2.delete(x84152)
                  } else {
                  }
                }
              }
            
            }
          }), x108821)
        }
      } else {
      }
      if(x2556) {
        x55781._1_=(part_partkey)
        val x108845 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx1.sliceRes(x55781);
        if((x108845.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx1.sliceResMapNoUpd(x55781, ({ x2725: SEntry3_LLD => {
              x55973._1_=((x2725._2))
              x55973._2_=((x2725._3))
              val x55974 = x55973._2;
              if((x55974.==(0.0))) {
              } else {
                val x84175 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x55973);
                if((x84175.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x55973)
                } else {
                  x84175._2 +=(x55974)
                  if(((x84175._2).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1.delete(x84175)
                  } else {
                  }
                }
              }
            
            }
          }), x108845)
        }
      } else {
      }
      if(x2556) {
        x55785._1_=(part_partkey)
        val x108871 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx2.sliceRes(x55785);
        if((x108871.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx2.sliceResMapNoUpd(x55785, ({ x2746: SEntry4_LLLD => {
              x55995._1_=((x2746._2))
              x55995._2_=((x2746._3))
              x55995._3_=((x2746._4))
              val x55996 = x55995._3;
              if((x55996.==(0.0))) {
              } else {
                val x84199 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x55995);
                if((x84199.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x55995)
                } else {
                  x84199._3 +=(x55996)
                  if(((x84199._3).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x84199)
                  } else {
                  }
                }
              }
            
            }
          }), x108871)
        }
      } else {
      }
      if(x2556) {
        x55789._1_=(part_partkey)
        val x108899 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx2.sliceRes(x55789);
        if((x108899.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x55789, ({ x2768: SEntry5_LLLLD => {
              x56018._1_=((x2768._2))
              x56018._2_=((x2768._3))
              x56018._3_=((x2768._4))
              x56018._4_=((x2768._5))
              val x56019 = x56018._4;
              if((x56019.==(0.0))) {
              } else {
                val x84226 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x56018);
                if((x84226.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x56018)
                } else {
                  x84226._4 +=(x56019)
                  if(((x84226._4).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x84226)
                  } else {
                  }
                }
              }
            
            }
          }), x108899)
        }
      } else {
      }
      if(x2556) {
        x55793._1_=(part_partkey)
        val x108925 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx2.sliceRes(x55793);
        if((x108925.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x55793, ({ x2791: SEntry4_LLLD => {
              x56040._1_=((x2791._2))
              x56040._2_=((x2791._3))
              x56040._3_=((x2791._4))
              val x56041 = x56040._3;
              if((x56041.==(0.0))) {
              } else {
                val x84252 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x56040);
                if((x84252.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x56040)
                } else {
                  x84252._3 +=(x56041)
                  if(((x84252._3).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x84252)
                  } else {
                  }
                }
              }
            
            }
          }), x108925)
        }
      } else {
      }
      MKT_SHARE.clear
      val x108965 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x108965.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x2813: SEntry2_LD => {
            val x2816 = Udate_year((x2813._1));
            var x2817: Double = 0.0;
            x56062._1_=(x2816)
            val x84272 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x56062);
            val x2822 = if((x84272.==(null))) {
            0.0
            } else {
            (x84272._2)
            };
            val x2824 = if((1L.>(x2822))) {
            1L
            } else {
            x2822
            };
            val x2825 = x2817;
            x2817 = (x2825.+(x2824))
            val x2828 = x2817;
            val x2831 = if((0.==(x2828))) {
            0.0
            } else {
            (1.0./(x2828))
            };
            x56077._1_=(x2816)
            x56077._2_=(((x2813._2).*(x2831)))
            val x56078 = x56077._2;
            if((x56078.==(0.0))) {
            } else {
              val x84291 = MKT_SHAREIdx0.get(x56077);
              if((x84291.==(null))) {
                MKT_SHARE.unsafeInsert(x56077)
              } else {
                x84291._2 +=(x56078)
                if(((x84291._2).==(0.0))) {
                  MKT_SHARE.delete(x84291)
                } else {
                }
              }
            }
          
          }
        }), x108965)
      }
    
    }
  
  }
  def onDelPART(part_partkey:Long, part_name:String, part_mfgr:String, part_brand:String, part_type:String, part_size:Long, part_container:String, part_retailprice:Double, part_comment:String) {
    {
      val x2858 = part_type.==("ECONOMY ANODIZED STEEL");
      if(x2858) {
        x56387._2_=(part_partkey)
        val x108991 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx1.sliceRes(x56387);
        if((x108991.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx1.sliceResMapNoUpd(x56387, ({ x2860: SEntry3_LLD => {
              x56456._1_=((x2860._1))
              x56456._2_=(((x2860._3).unary_-))
              val x56457 = x56456._2;
              if((x56457.==(0.0))) {
              } else {
                val x84640 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x56456);
                if((x84640.==(null))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x56456)
                } else {
                  x84640._2 +=(x56457)
                  if(((x84640._2).==(0.0))) {
                    MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x84640)
                  } else {
                  }
                }
              }
            
            }
          }), x108991)
        }
      } else {
      }
      if(x2858) {
        x56391._2_=(part_partkey)
        val x109018 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx1.sliceRes(x56391);
        if((x109018.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x56391, ({ x2882: SEntry4_LLLD => {
              x56479._1_=((x2882._1))
              x56479._2_=((x2882._3))
              x56479._3_=(((x2882._4).unary_-))
              val x56480 = x56479._3;
              if((x56480.==(0.0))) {
              } else {
                val x84665 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx0.get(x56479);
                if((x84665.==(null))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.unsafeInsert(x56479)
                } else {
                  x84665._3 +=(x56480)
                  if(((x84665._3).==(0.0))) {
                    MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1.delete(x84665)
                  } else {
                  }
                }
              }
            
            }
          }), x109018)
        }
      } else {
      }
      if(x2858) {
        x56395._1_=(part_partkey)
        x56395._2_=(-1L)
        val x56396 = x56395._2;
        if((x56396.==(0L))) {
        } else {
          val x84684 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1Idx0.get(x56395);
          if((x84684.==(null))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.unsafeInsert(x56395)
          } else {
            x84684._2 +=(x56396)
            if(((x84684._2).==(0L))) {
              MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM1.delete(x84684)
            } else {
            }
          }
        }
      } else {
      }
      if(x2858) {
        x56410._2_=(part_partkey)
        val x109058 = MKT_SHARE_mORDERS6_mPART2Idx1.sliceRes(x56410);
        if((x109058.isEmpty)) {
        } else {
          MKT_SHARE_mORDERS6_mPART2Idx1.sliceResMapNoUpd(x56410, ({ x2920: SEntry3_LLD => {
              x56516._1_=((x2920._1))
              x56516._2_=(((x2920._3).unary_-))
              val x56517 = x56516._2;
              if((x56517.==(0.0))) {
              } else {
                val x84706 = MKT_SHARE_mORDERS6Idx0.get(x56516);
                if((x84706.==(null))) {
                  MKT_SHARE_mORDERS6.unsafeInsert(x56516)
                } else {
                  x84706._2 +=(x56517)
                  if(((x84706._2).==(0.0))) {
                    MKT_SHARE_mORDERS6.delete(x84706)
                  } else {
                  }
                }
              }
            
            }
          }), x109058)
        }
      } else {
      }
      if(x2858) {
        x56414._1_=(part_partkey)
        val x109083 = MKT_SHARE_mPART1_mPART2Idx1.sliceRes(x56414);
        if((x109083.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mPART2Idx1.sliceResMapNoUpd(x56414, ({ x2942: SEntry3_LLD => {
              x56538._1_=((x2942._2))
              x56538._2_=(((x2942._3).unary_-))
              val x56539 = x56538._2;
              if((x56539.==(0.0))) {
              } else {
                val x84729 = MKT_SHARE_mPART1Idx0.get(x56538);
                if((x84729.==(null))) {
                  MKT_SHARE_mPART1.unsafeInsert(x56538)
                } else {
                  x84729._2 +=(x56539)
                  if(((x84729._2).==(0.0))) {
                    MKT_SHARE_mPART1.delete(x84729)
                  } else {
                  }
                }
              }
            
            }
          }), x109083)
        }
      } else {
      }
      if(x2858) {
        x56418._1_=(part_partkey)
        val x109110 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx2.sliceRes(x56418);
        if((x109110.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx2.sliceResMapNoUpd(x56418, ({ x2964: SEntry4_LLLD => {
              x56561._1_=((x2964._2))
              x56561._2_=((x2964._3))
              x56561._3_=(((x2964._4).unary_-))
              val x56562 = x56561._3;
              if((x56562.==(0.0))) {
              } else {
                val x84754 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x56561);
                if((x84754.==(null))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x56561)
                } else {
                  x84754._3 +=(x56562)
                  if(((x84754._3).==(0.0))) {
                    MKT_SHARE_mPART1_mCUSTOMER1.delete(x84754)
                  } else {
                  }
                }
              }
            
            }
          }), x109110)
        }
      } else {
      }
      if(x2858) {
        x56422._1_=(part_partkey)
        val x109139 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx2.sliceRes(x56422);
        if((x109139.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx2.sliceResMapNoUpd(x56422, ({ x2987: SEntry5_LLLLD => {
              x56585._1_=((x2987._2))
              x56585._2_=((x2987._3))
              x56585._3_=((x2987._4))
              x56585._4_=(((x2987._5).unary_-))
              val x56586 = x56585._4;
              if((x56586.==(0.0))) {
              } else {
                val x84782 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx0.get(x56585);
                if((x84782.==(null))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.unsafeInsert(x56585)
                } else {
                  x84782._4 +=(x56586)
                  if(((x84782._4).==(0.0))) {
                    MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2.delete(x84782)
                  } else {
                  }
                }
              }
            
            }
          }), x109139)
        }
      } else {
      }
      if(x2858) {
        x56426._1_=(part_partkey)
        val x109166 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx2.sliceRes(x56426);
        if((x109166.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx2.sliceResMapNoUpd(x56426, ({ x3011: SEntry4_LLLD => {
              x56608._1_=((x3011._2))
              x56608._2_=((x3011._3))
              x56608._3_=(((x3011._4).unary_-))
              val x56609 = x56608._3;
              if((x56609.==(0.0))) {
              } else {
                val x84809 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x56608);
                if((x84809.==(null))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x56608)
                } else {
                  x84809._3 +=(x56609)
                  if(((x84809._3).==(0.0))) {
                    MKT_SHARE_mPART1_mSUPPLIER2.delete(x84809)
                  } else {
                  }
                }
              }
            
            }
          }), x109166)
        }
      } else {
      }
      if(x2858) {
        x56430._1_=(part_partkey)
        val x109191 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx1.sliceRes(x56430);
        if((x109191.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx1.sliceResMapNoUpd(x56430, ({ x3034: SEntry3_LLD => {
              x56630._1_=((x3034._2))
              x56630._2_=(((x3034._3).unary_-))
              val x56631 = x56630._2;
              if((x56631.==(0.0))) {
              } else {
                val x84833 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x56630);
                if((x84833.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x56630)
                } else {
                  x84833._2 +=(x56631)
                  if(((x84833._2).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1.delete(x84833)
                  } else {
                  }
                }
              }
            
            }
          }), x109191)
        }
      } else {
      }
      if(x2858) {
        x56434._1_=(part_partkey)
        val x109218 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx2.sliceRes(x56434);
        if((x109218.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx2.sliceResMapNoUpd(x56434, ({ x3056: SEntry4_LLLD => {
              x56653._1_=((x3056._2))
              x56653._2_=((x3056._3))
              x56653._3_=(((x3056._4).unary_-))
              val x56654 = x56653._3;
              if((x56654.==(0.0))) {
              } else {
                val x84858 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x56653);
                if((x84858.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x56653)
                } else {
                  x84858._3 +=(x56654)
                  if(((x84858._3).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x84858)
                  } else {
                  }
                }
              }
            
            }
          }), x109218)
        }
      } else {
      }
      if(x2858) {
        x56438._1_=(part_partkey)
        val x109247 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx2.sliceRes(x56438);
        if((x109247.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x56438, ({ x3079: SEntry5_LLLLD => {
              x56677._1_=((x3079._2))
              x56677._2_=((x3079._3))
              x56677._3_=((x3079._4))
              x56677._4_=(((x3079._5).unary_-))
              val x56678 = x56677._4;
              if((x56678.==(0.0))) {
              } else {
                val x84886 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx0.get(x56677);
                if((x84886.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.unsafeInsert(x56677)
                } else {
                  x84886._4 +=(x56678)
                  if(((x84886._4).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1.delete(x84886)
                  } else {
                  }
                }
              }
            
            }
          }), x109247)
        }
      } else {
      }
      if(x2858) {
        x56442._1_=(part_partkey)
        val x109274 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx2.sliceRes(x56442);
        if((x109274.isEmpty)) {
        } else {
          MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx2.sliceResMapNoUpd(x56442, ({ x3103: SEntry4_LLLD => {
              x56700._1_=((x3103._2))
              x56700._2_=((x3103._3))
              x56700._3_=(((x3103._4).unary_-))
              val x56701 = x56700._3;
              if((x56701.==(0.0))) {
              } else {
                val x84913 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x56700);
                if((x84913.==(null))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x56700)
                } else {
                  x84913._3 +=(x56701)
                  if(((x84913._3).==(0.0))) {
                    MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x84913)
                  } else {
                  }
                }
              }
            
            }
          }), x109274)
        }
      } else {
      }
      MKT_SHARE.clear
      val x109314 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x109314.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x3126: SEntry2_LD => {
            val x3129 = Udate_year((x3126._1));
            var x3130: Double = 0.0;
            x56722._1_=(x3129)
            val x84933 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x56722);
            val x3135 = if((x84933.==(null))) {
            0.0
            } else {
            (x84933._2)
            };
            val x3137 = if((1L.>(x3135))) {
            1L
            } else {
            x3135
            };
            val x3138 = x3130;
            x3130 = (x3138.+(x3137))
            val x3141 = x3130;
            val x3144 = if((0.==(x3141))) {
            0.0
            } else {
            (1.0./(x3141))
            };
            x56737._1_=(x3129)
            x56737._2_=(((x3126._2).*(x3144)))
            val x56738 = x56737._2;
            if((x56738.==(0.0))) {
            } else {
              val x84952 = MKT_SHAREIdx0.get(x56737);
              if((x84952.==(null))) {
                MKT_SHARE.unsafeInsert(x56737)
              } else {
                x84952._2 +=(x56738)
                if(((x84952._2).==(0.0))) {
                  MKT_SHARE.delete(x84952)
                } else {
                }
              }
            }
          
          }
        }), x109314)
      }
    
    }
  
  }
  def onAddCUSTOMER(customer_custkey:Long, customer_name:String, customer_address:String, customer_nationkey:Long, customer_phone:String, customer_acctbal:Double, customer_mktsegment:String, customer_comment:String) {
    {
      x57056._1_=(customer_nationkey)
      val x85300 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57056);
      val x3174 = if((x85300.==(null))) {
      0L
      } else {
      (x85300._2)
      };
      x57061._1_=(customer_custkey)
      x57061._2_=(x3174)
      val x57062 = x57061._2;
      if((x57062.==(0L))) {
      } else {
        val x85309 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x57061);
        if((x85309.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_4.unsafeInsert(x57061)
        } else {
          x85309._2 +=(x57062)
          if(((x85309._2).==(0L))) {
            MKT_SHARE_mORDERS1_L2_1_L1_4.delete(x85309)
          } else {
          }
        }
      }
      x57075._1_=(customer_nationkey)
      val x85320 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57075);
      x57080._1_=(customer_custkey)
      val x109362 = MKT_SHARE_mPART1_mCUSTOMER1Idx1.sliceRes(x57080);
      if((x109362.isEmpty)) {
      } else {
        val x3193 = if((x85320.==(null))) {
        0L
        } else {
        (x85320._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1Idx1.sliceResMapNoUpd(x57080, ({ x3195: SEntry3_LLD => {
            x57188._1_=((x3195._2))
            x57188._2_=((x3193.*((x3195._3))))
            val x57189 = x57188._2;
            if((x57189.==(0.0))) {
            } else {
              val x85335 = MKT_SHARE_mPART1Idx0.get(x57188);
              if((x85335.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x57188)
              } else {
                x85335._2 +=(x57189)
                if(((x85335._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x85335)
                } else {
                }
              }
            }
          
          }
        }), x109362)
      }
      x57083._1_=(customer_nationkey)
      val x85347 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57083);
      x57088._2_=(customer_custkey)
      val x109393 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx1.sliceRes(x57088);
      if((x109393.isEmpty)) {
      } else {
        val x3219 = if((x85347.==(null))) {
        0L
        } else {
        (x85347._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx1.sliceResMapNoUpd(x57088, ({ x3221: SEntry4_LLLL => {
            x57215._1_=((x3221._1))
            x57215._2_=((x3221._3))
            x57215._3_=((x3219.*((x3221._4))))
            val x57216 = x57215._3;
            if((x57216.==(0L))) {
            } else {
              val x85364 = MKT_SHARE_mPART1_mLINEITEM3Idx0.get(x57215);
              if((x85364.==(null))) {
                MKT_SHARE_mPART1_mLINEITEM3.unsafeInsert(x57215)
              } else {
                x85364._3 +=(x57216)
                if(((x85364._3).==(0L))) {
                  MKT_SHARE_mPART1_mLINEITEM3.delete(x85364)
                } else {
                }
              }
            }
          
          }
        }), x109393)
      }
      x57091._1_=(customer_nationkey)
      val x85377 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57091);
      x57096._2_=(customer_custkey)
      val x109424 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx1.sliceRes(x57096);
      if((x109424.isEmpty)) {
      } else {
        val x3246 = if((x85377.==(null))) {
        0L
        } else {
        (x85377._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx1.sliceResMapNoUpd(x57096, ({ x3248: SEntry4_LLLD => {
            x57242._1_=((x3248._1))
            x57242._2_=((x3248._3))
            x57242._3_=((x3246.*((x3248._4))))
            val x57243 = x57242._3;
            if((x57243.==(0.0))) {
            } else {
              val x85394 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x57242);
              if((x85394.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x57242)
              } else {
                x85394._3 +=(x57243)
                if(((x85394._3).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.delete(x85394)
                } else {
                }
              }
            }
          
          }
        }), x109424)
      }
      x57099._1_=(customer_nationkey)
      val x85407 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57099);
      x57104._3_=(customer_custkey)
      val x109457 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx3.sliceRes(x57104);
      if((x109457.isEmpty)) {
      } else {
        val x3273 = if((x85407.==(null))) {
        0L
        } else {
        (x85407._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx3.sliceResMapNoUpd(x57104, ({ x3275: SEntry5_LLLLD => {
            x57270._1_=((x3275._1))
            x57270._2_=((x3275._2))
            x57270._3_=((x3275._4))
            x57270._4_=((x3273.*((x3275._5))))
            val x57271 = x57270._4;
            if((x57271.==(0.0))) {
            } else {
              val x85426 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x57270);
              if((x85426.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x57270)
              } else {
                x85426._4 +=(x57271)
                if(((x85426._4).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x85426)
                } else {
                }
              }
            }
          
          }
        }), x109457)
      }
      x57107._1_=(customer_nationkey)
      val x85440 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57107);
      x57112._2_=(customer_custkey)
      val x109488 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx1.sliceRes(x57112);
      if((x109488.isEmpty)) {
      } else {
        val x3301 = if((x85440.==(null))) {
        0L
        } else {
        (x85440._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx1.sliceResMapNoUpd(x57112, ({ x3303: SEntry4_LLLD => {
            x57297._1_=((x3303._1))
            x57297._2_=((x3303._3))
            x57297._3_=((x3301.*((x3303._4))))
            val x57298 = x57297._3;
            if((x57298.==(0.0))) {
            } else {
              val x85457 = MKT_SHARE_mPART1_mPART2Idx0.get(x57297);
              if((x85457.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x57297)
              } else {
                x85457._3 +=(x57298)
                if(((x85457._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x85457)
                } else {
                }
              }
            }
          
          }
        }), x109488)
      }
      x57115._1_=(customer_nationkey)
      val x85470 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57115);
      x57120._1_=(customer_custkey)
      val x109517 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx1.sliceRes(x57120);
      if((x109517.isEmpty)) {
      } else {
        val x3328 = if((x85470.==(null))) {
        0L
        } else {
        (x85470._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx1.sliceResMapNoUpd(x57120, ({ x3330: SEntry3_LLD => {
            x57323._1_=((x3330._2))
            x57323._2_=((x3328.*((x3330._3))))
            val x57324 = x57323._2;
            if((x57324.==(0.0))) {
            } else {
              val x85485 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x57323);
              if((x85485.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x57323)
              } else {
                x85485._2 +=(x57324)
                if(((x85485._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x85485)
                } else {
                }
              }
            }
          
          }
        }), x109517)
      }
      x57123._1_=(customer_nationkey)
      val x85497 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57123);
      x57128._2_=(customer_custkey)
      val x109548 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx1.sliceRes(x57128);
      if((x109548.isEmpty)) {
      } else {
        val x3354 = if((x85497.==(null))) {
        0L
        } else {
        (x85497._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx1.sliceResMapNoUpd(x57128, ({ x3356: SEntry4_LLLL => {
            x57350._1_=((x3356._1))
            x57350._2_=((x3356._3))
            x57350._3_=((x3354.*((x3356._4))))
            val x57351 = x57350._3;
            if((x57351.==(0L))) {
            } else {
              val x85514 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx0.get(x57350);
              if((x85514.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.unsafeInsert(x57350)
              } else {
                x85514._3 +=(x57351)
                if(((x85514._3).==(0L))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.delete(x85514)
                } else {
                }
              }
            }
          
          }
        }), x109548)
      }
      x57131._1_=(customer_nationkey)
      val x85527 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57131);
      x57136._2_=(customer_custkey)
      val x109579 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx1.sliceRes(x57136);
      if((x109579.isEmpty)) {
      } else {
        val x3381 = if((x85527.==(null))) {
        0L
        } else {
        (x85527._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx1.sliceResMapNoUpd(x57136, ({ x3383: SEntry4_LLLD => {
            x57377._1_=((x3383._1))
            x57377._2_=((x3383._3))
            x57377._3_=((x3381.*((x3383._4))))
            val x57378 = x57377._3;
            if((x57378.==(0.0))) {
            } else {
              val x85544 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x57377);
              if((x85544.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x57377)
              } else {
                x85544._3 +=(x57378)
                if(((x85544._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x85544)
                } else {
                }
              }
            }
          
          }
        }), x109579)
      }
      x57139._1_=(customer_nationkey)
      val x85557 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57139);
      x57144._3_=(customer_custkey)
      val x109612 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx3.sliceRes(x57144);
      if((x109612.isEmpty)) {
      } else {
        val x3408 = if((x85557.==(null))) {
        0L
        } else {
        (x85557._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x57144, ({ x3410: SEntry5_LLLLD => {
            x57405._1_=((x3410._1))
            x57405._2_=((x3410._2))
            x57405._3_=((x3410._4))
            x57405._4_=((x3408.*((x3410._5))))
            val x57406 = x57405._4;
            if((x57406.==(0.0))) {
            } else {
              val x85576 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x57405);
              if((x85576.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x57405)
              } else {
                x85576._4 +=(x57406)
                if(((x85576._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x85576)
                } else {
                }
              }
            }
          
          }
        }), x109612)
      }
      x57147._1_=(customer_nationkey)
      val x85590 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57147);
      x57152._2_=(customer_custkey)
      val x109643 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx1.sliceRes(x57152);
      if((x109643.isEmpty)) {
      } else {
        val x3436 = if((x85590.==(null))) {
        0L
        } else {
        (x85590._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx1.sliceResMapNoUpd(x57152, ({ x3438: SEntry4_LLLD => {
            x57432._1_=((x3438._1))
            x57432._2_=((x3438._3))
            x57432._3_=((x3436.*((x3438._4))))
            val x57433 = x57432._3;
            if((x57433.==(0.0))) {
            } else {
              val x85607 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x57432);
              if((x85607.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x57432)
              } else {
                x85607._3 +=(x57433)
                if(((x85607._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x85607)
                } else {
                }
              }
            }
          
          }
        }), x109643)
      }
      MKT_SHARE.clear
      val x109683 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x109683.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x3460: SEntry2_LD => {
            val x3463 = Udate_year((x3460._1));
            var x3464: Double = 0.0;
            x57454._1_=(x3463)
            val x85627 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x57454);
            val x3469 = if((x85627.==(null))) {
            0.0
            } else {
            (x85627._2)
            };
            val x3471 = if((1L.>(x3469))) {
            1L
            } else {
            x3469
            };
            val x3472 = x3464;
            x3464 = (x3472.+(x3471))
            val x3475 = x3464;
            val x3478 = if((0.==(x3475))) {
            0.0
            } else {
            (1.0./(x3475))
            };
            x57469._1_=(x3463)
            x57469._2_=(((x3460._2).*(x3478)))
            val x57470 = x57469._2;
            if((x57470.==(0.0))) {
            } else {
              val x85646 = MKT_SHAREIdx0.get(x57469);
              if((x85646.==(null))) {
                MKT_SHARE.unsafeInsert(x57469)
              } else {
                x85646._2 +=(x57470)
                if(((x85646._2).==(0.0))) {
                  MKT_SHARE.delete(x85646)
                } else {
                }
              }
            }
          
          }
        }), x109683)
      }
    
    }
  
  }
  def onDelCUSTOMER(customer_custkey:Long, customer_name:String, customer_address:String, customer_nationkey:Long, customer_phone:String, customer_acctbal:Double, customer_mktsegment:String, customer_comment:String) {
    {
      x57810._1_=(customer_nationkey)
      val x86016 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57810);
      val x3508 = if((x86016.==(null))) {
      0L
      } else {
      (x86016._2)
      };
      x57816._1_=(customer_custkey)
      x57816._2_=((x3508.unary_-))
      val x57817 = x57816._2;
      if((x57817.==(0L))) {
      } else {
        val x86026 = MKT_SHARE_mORDERS1_L2_1_L1_4Idx0.get(x57816);
        if((x86026.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_4.unsafeInsert(x57816)
        } else {
          x86026._2 +=(x57817)
          if(((x86026._2).==(0L))) {
            MKT_SHARE_mORDERS1_L2_1_L1_4.delete(x86026)
          } else {
          }
        }
      }
      x57830._1_=(customer_nationkey)
      val x86037 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57830);
      x57835._1_=(customer_custkey)
      val x109733 = MKT_SHARE_mPART1_mCUSTOMER1Idx1.sliceRes(x57835);
      if((x109733.isEmpty)) {
      } else {
        val x3528 = if((x86037.==(null))) {
        0L
        } else {
        (x86037._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1Idx1.sliceResMapNoUpd(x57835, ({ x3530: SEntry3_LLD => {
            x57945._1_=((x3530._2))
            x57945._2_=((x3528.*(((x3530._3).unary_-))))
            val x57946 = x57945._2;
            if((x57946.==(0.0))) {
            } else {
              val x86053 = MKT_SHARE_mPART1Idx0.get(x57945);
              if((x86053.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x57945)
              } else {
                x86053._2 +=(x57946)
                if(((x86053._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x86053)
                } else {
                }
              }
            }
          
          }
        }), x109733)
      }
      x57838._1_=(customer_nationkey)
      val x86065 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57838);
      x57843._2_=(customer_custkey)
      val x109765 = MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx1.sliceRes(x57843);
      if((x109765.isEmpty)) {
      } else {
        val x3555 = if((x86065.==(null))) {
        0L
        } else {
        (x86065._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mLINEITEM3Idx1.sliceResMapNoUpd(x57843, ({ x3557: SEntry4_LLLL => {
            x57973._1_=((x3557._1))
            x57973._2_=((x3557._3))
            x57973._3_=((x3555.*(((x3557._4).unary_-))))
            val x57974 = x57973._3;
            if((x57974.==(0L))) {
            } else {
              val x86083 = MKT_SHARE_mPART1_mLINEITEM3Idx0.get(x57973);
              if((x86083.==(null))) {
                MKT_SHARE_mPART1_mLINEITEM3.unsafeInsert(x57973)
              } else {
                x86083._3 +=(x57974)
                if(((x86083._3).==(0L))) {
                  MKT_SHARE_mPART1_mLINEITEM3.delete(x86083)
                } else {
                }
              }
            }
          
          }
        }), x109765)
      }
      x57846._1_=(customer_nationkey)
      val x86096 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57846);
      x57851._2_=(customer_custkey)
      val x109797 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx1.sliceRes(x57851);
      if((x109797.isEmpty)) {
      } else {
        val x3583 = if((x86096.==(null))) {
        0L
        } else {
        (x86096._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx1.sliceResMapNoUpd(x57851, ({ x3585: SEntry4_LLLD => {
            x58001._1_=((x3585._1))
            x58001._2_=((x3585._3))
            x58001._3_=((x3583.*(((x3585._4).unary_-))))
            val x58002 = x58001._3;
            if((x58002.==(0.0))) {
            } else {
              val x86114 = MKT_SHARE_mPART1_mSUPPLIER2Idx0.get(x58001);
              if((x86114.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2.unsafeInsert(x58001)
              } else {
                x86114._3 +=(x58002)
                if(((x86114._3).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2.delete(x86114)
                } else {
                }
              }
            }
          
          }
        }), x109797)
      }
      x57854._1_=(customer_nationkey)
      val x86127 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57854);
      x57859._3_=(customer_custkey)
      val x109831 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx3.sliceRes(x57859);
      if((x109831.isEmpty)) {
      } else {
        val x3611 = if((x86127.==(null))) {
        0L
        } else {
        (x86127._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx3.sliceResMapNoUpd(x57859, ({ x3613: SEntry5_LLLLD => {
            x58030._1_=((x3613._1))
            x58030._2_=((x3613._2))
            x58030._3_=((x3613._4))
            x58030._4_=((x3611.*(((x3613._5).unary_-))))
            val x58031 = x58030._4;
            if((x58031.==(0.0))) {
            } else {
              val x86147 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx0.get(x58030);
              if((x86147.==(null))) {
                MKT_SHARE_mPART1_mSUPPLIER2_mPART2.unsafeInsert(x58030)
              } else {
                x86147._4 +=(x58031)
                if(((x86147._4).==(0.0))) {
                  MKT_SHARE_mPART1_mSUPPLIER2_mPART2.delete(x86147)
                } else {
                }
              }
            }
          
          }
        }), x109831)
      }
      x57862._1_=(customer_nationkey)
      val x86161 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57862);
      x57867._2_=(customer_custkey)
      val x109863 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx1.sliceRes(x57867);
      if((x109863.isEmpty)) {
      } else {
        val x3640 = if((x86161.==(null))) {
        0L
        } else {
        (x86161._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx1.sliceResMapNoUpd(x57867, ({ x3642: SEntry4_LLLD => {
            x58058._1_=((x3642._1))
            x58058._2_=((x3642._3))
            x58058._3_=((x3640.*(((x3642._4).unary_-))))
            val x58059 = x58058._3;
            if((x58059.==(0.0))) {
            } else {
              val x86179 = MKT_SHARE_mPART1_mPART2Idx0.get(x58058);
              if((x86179.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x58058)
              } else {
                x86179._3 +=(x58059)
                if(((x86179._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x86179)
                } else {
                }
              }
            }
          
          }
        }), x109863)
      }
      x57870._1_=(customer_nationkey)
      val x86192 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57870);
      x57875._1_=(customer_custkey)
      val x109893 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx1.sliceRes(x57875);
      if((x109893.isEmpty)) {
      } else {
        val x3668 = if((x86192.==(null))) {
        0L
        } else {
        (x86192._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx1.sliceResMapNoUpd(x57875, ({ x3670: SEntry3_LLD => {
            x58085._1_=((x3670._2))
            x58085._2_=((x3668.*(((x3670._3).unary_-))))
            val x58086 = x58085._2;
            if((x58086.==(0.0))) {
            } else {
              val x86208 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x58085);
              if((x86208.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x58085)
              } else {
                x86208._2 +=(x58086)
                if(((x86208._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x86208)
                } else {
                }
              }
            }
          
          }
        }), x109893)
      }
      x57878._1_=(customer_nationkey)
      val x86220 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57878);
      x57883._2_=(customer_custkey)
      val x109925 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx1.sliceRes(x57883);
      if((x109925.isEmpty)) {
      } else {
        val x3695 = if((x86220.==(null))) {
        0L
        } else {
        (x86220._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mLINEITEM3Idx1.sliceResMapNoUpd(x57883, ({ x3697: SEntry4_LLLL => {
            x58113._1_=((x3697._1))
            x58113._2_=((x3697._3))
            x58113._3_=((x3695.*(((x3697._4).unary_-))))
            val x58114 = x58113._3;
            if((x58114.==(0L))) {
            } else {
              val x86238 = MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2Idx0.get(x58113);
              if((x86238.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.unsafeInsert(x58113)
              } else {
                x86238._3 +=(x58114)
                if(((x86238._3).==(0L))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mLINEITEM2.delete(x86238)
                } else {
                }
              }
            }
          
          }
        }), x109925)
      }
      x57886._1_=(customer_nationkey)
      val x86251 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57886);
      x57891._2_=(customer_custkey)
      val x109957 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx1.sliceRes(x57891);
      if((x109957.isEmpty)) {
      } else {
        val x3723 = if((x86251.==(null))) {
        0L
        } else {
        (x86251._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx1.sliceResMapNoUpd(x57891, ({ x3725: SEntry4_LLLD => {
            x58141._1_=((x3725._1))
            x58141._2_=((x3725._3))
            x58141._3_=((x3723.*(((x3725._4).unary_-))))
            val x58142 = x58141._3;
            if((x58142.==(0.0))) {
            } else {
              val x86269 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx0.get(x58141);
              if((x86269.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.unsafeInsert(x58141)
              } else {
                x86269._3 +=(x58142)
                if(((x86269._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1.delete(x86269)
                } else {
                }
              }
            }
          
          }
        }), x109957)
      }
      x57894._1_=(customer_nationkey)
      val x86282 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57894);
      x57899._3_=(customer_custkey)
      val x109991 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx3.sliceRes(x57899);
      if((x109991.isEmpty)) {
      } else {
        val x3751 = if((x86282.==(null))) {
        0L
        } else {
        (x86282._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x57899, ({ x3753: SEntry5_LLLLD => {
            x58170._1_=((x3753._1))
            x58170._2_=((x3753._2))
            x58170._3_=((x3753._4))
            x58170._4_=((x3751.*(((x3753._5).unary_-))))
            val x58171 = x58170._4;
            if((x58171.==(0.0))) {
            } else {
              val x86302 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx0.get(x58170);
              if((x86302.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.unsafeInsert(x58170)
              } else {
                x86302._4 +=(x58171)
                if(((x86302._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2.delete(x86302)
                } else {
                }
              }
            }
          
          }
        }), x109991)
      }
      x57902._1_=(customer_nationkey)
      val x86316 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x57902);
      x57907._2_=(customer_custkey)
      val x110023 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx1.sliceRes(x57907);
      if((x110023.isEmpty)) {
      } else {
        val x3780 = if((x86316.==(null))) {
        0L
        } else {
        (x86316._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx1.sliceResMapNoUpd(x57907, ({ x3782: SEntry4_LLLD => {
            x58198._1_=((x3782._1))
            x58198._2_=((x3782._3))
            x58198._3_=((x3780.*(((x3782._4).unary_-))))
            val x58199 = x58198._3;
            if((x58199.==(0.0))) {
            } else {
              val x86334 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x58198);
              if((x86334.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x58198)
              } else {
                x86334._3 +=(x58199)
                if(((x86334._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x86334)
                } else {
                }
              }
            }
          
          }
        }), x110023)
      }
      MKT_SHARE.clear
      val x110063 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x110063.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x3805: SEntry2_LD => {
            val x3808 = Udate_year((x3805._1));
            var x3809: Double = 0.0;
            x58220._1_=(x3808)
            val x86354 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x58220);
            val x3814 = if((x86354.==(null))) {
            0.0
            } else {
            (x86354._2)
            };
            val x3816 = if((1L.>(x3814))) {
            1L
            } else {
            x3814
            };
            val x3817 = x3809;
            x3809 = (x3817.+(x3816))
            val x3820 = x3809;
            val x3823 = if((0.==(x3820))) {
            0.0
            } else {
            (1.0./(x3820))
            };
            x58235._1_=(x3808)
            x58235._2_=(((x3805._2).*(x3823)))
            val x58236 = x58235._2;
            if((x58236.==(0.0))) {
            } else {
              val x86373 = MKT_SHAREIdx0.get(x58235);
              if((x86373.==(null))) {
                MKT_SHARE.unsafeInsert(x58235)
              } else {
                x86373._2 +=(x58236)
                if(((x86373._2).==(0.0))) {
                  MKT_SHARE.delete(x86373)
                } else {
                }
              }
            }
          
          }
        }), x110063)
      }
    
    }
  
  }
  def onAddSUPPLIER(supplier_suppkey:Long, supplier_name:String, supplier_address:String, supplier_nationkey:Long, supplier_phone:String, supplier_acctbal:Double, supplier_comment:String) {
    {
      x58587._1_=(supplier_nationkey)
      val x86754 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58587);
      x58592._2_=(supplier_suppkey)
      val x110092 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceRes(x58592);
      if((x110092.isEmpty)) {
      } else {
        val x3852 = if((x86754.==(null))) {
        0L
        } else {
        (x86754._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceResMapNoUpd(x58592, ({ x3854: SEntry3_LLD => {
            x58735._1_=((x3854._1))
            x58735._2_=((x3852.*((x3854._3))))
            val x58736 = x58735._2;
            if((x58736.==(0.0))) {
            } else {
              val x86769 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x58735);
              if((x86769.==(null))) {
                MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x58735)
              } else {
                x86769._2 +=(x58736)
                if(((x86769._2).==(0.0))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x86769)
                } else {
                }
              }
            }
          
          }
        }), x110092)
      }
      x58595._1_=(supplier_nationkey)
      val x86781 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58595);
      x58600._3_=(supplier_suppkey)
      val x110123 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceRes(x58600);
      if((x110123.isEmpty)) {
      } else {
        val x3878 = if((x86781.==(null))) {
        0L
        } else {
        (x86781._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x58600, ({ x3880: SEntry4_LLLD => {
            x58762._1_=((x3880._1))
            x58762._2_=((x3880._2))
            x58762._3_=((x3878.*((x3880._4))))
            val x58763 = x58762._3;
            if((x58763.==(0.0))) {
            } else {
              val x86798 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx0.get(x58762);
              if((x86798.==(null))) {
                MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.unsafeInsert(x58762)
              } else {
                x86798._3 +=(x58763)
                if(((x86798._3).==(0.0))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.delete(x86798)
                } else {
                }
              }
            }
          
          }
        }), x110123)
      }
      x58603._1_=(supplier_nationkey)
      val x86812 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58603);
      val x3905 = if((x86812.==(null))) {
      0L
      } else {
      (x86812._2)
      };
      x58608._1_=(supplier_suppkey)
      x58608._2_=(x3905)
      val x58609 = x58608._2;
      if((x58609.==(0L))) {
      } else {
        val x86821 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x58608);
        if((x86821.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.unsafeInsert(x58608)
        } else {
          x86821._2 +=(x58609)
          if(((x86821._2).==(0L))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.delete(x86821)
          } else {
          }
        }
      }
      x58622._1_=(supplier_nationkey)
      val x86832 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58622);
      x58627._2_=(supplier_suppkey)
      val x110171 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceRes(x58627);
      if((x110171.isEmpty)) {
      } else {
        val x3924 = if((x86832.==(null))) {
        0L
        } else {
        (x86832._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceResMapNoUpd(x58627, ({ x3926: SEntry3_LLD => {
            x58807._1_=((x3926._1))
            x58807._2_=((x3924.*((x3926._3))))
            val x58808 = x58807._2;
            if((x58808.==(0.0))) {
            } else {
              val x86847 = MKT_SHARE_mORDERS6Idx0.get(x58807);
              if((x86847.==(null))) {
                MKT_SHARE_mORDERS6.unsafeInsert(x58807)
              } else {
                x86847._2 +=(x58808)
                if(((x86847._2).==(0.0))) {
                  MKT_SHARE_mORDERS6.delete(x86847)
                } else {
                }
              }
            }
          
          }
        }), x110171)
      }
      x58630._1_=(supplier_nationkey)
      val x86859 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58630);
      x58635._3_=(supplier_suppkey)
      val x110202 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceRes(x58635);
      if((x110202.isEmpty)) {
      } else {
        val x3950 = if((x86859.==(null))) {
        0L
        } else {
        (x86859._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x58635, ({ x3952: SEntry4_LLLD => {
            x58834._1_=((x3952._1))
            x58834._2_=((x3952._2))
            x58834._3_=((x3950.*((x3952._4))))
            val x58835 = x58834._3;
            if((x58835.==(0.0))) {
            } else {
              val x86876 = MKT_SHARE_mORDERS6_mPART2Idx0.get(x58834);
              if((x86876.==(null))) {
                MKT_SHARE_mORDERS6_mPART2.unsafeInsert(x58834)
              } else {
                x86876._3 +=(x58835)
                if(((x86876._3).==(0.0))) {
                  MKT_SHARE_mORDERS6_mPART2.delete(x86876)
                } else {
                }
              }
            }
          
          }
        }), x110202)
      }
      x58638._1_=(supplier_nationkey)
      val x86890 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58638);
      val x3977 = if((x86890.==(null))) {
      0L
      } else {
      (x86890._2)
      };
      x58643._1_=(supplier_suppkey)
      x58643._2_=(x3977)
      val x58644 = x58643._2;
      if((x58644.==(0L))) {
      } else {
        val x86899 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x58643);
        if((x86899.==(null))) {
          MKT_SHARE_mORDERS6_mLINEITEM1.unsafeInsert(x58643)
        } else {
          x86899._2 +=(x58644)
          if(((x86899._2).==(0L))) {
            MKT_SHARE_mORDERS6_mLINEITEM1.delete(x86899)
          } else {
          }
        }
      }
      x58657._1_=(supplier_nationkey)
      val x86910 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58657);
      x58662._1_=(supplier_suppkey)
      val x110250 = MKT_SHARE_mPART1_mSUPPLIER2Idx1.sliceRes(x58662);
      if((x110250.isEmpty)) {
      } else {
        val x3996 = if((x86910.==(null))) {
        0L
        } else {
        (x86910._2)
        };
        MKT_SHARE_mPART1_mSUPPLIER2Idx1.sliceResMapNoUpd(x58662, ({ x3998: SEntry3_LLD => {
            x58879._1_=((x3998._2))
            x58879._2_=((x3996.*((x3998._3))))
            val x58880 = x58879._2;
            if((x58880.==(0.0))) {
            } else {
              val x86925 = MKT_SHARE_mPART1Idx0.get(x58879);
              if((x86925.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x58879)
              } else {
                x86925._2 +=(x58880)
                if(((x86925._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x86925)
                } else {
                }
              }
            }
          
          }
        }), x110250)
      }
      x58665._1_=(supplier_nationkey)
      val x86937 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58665);
      x58670._1_=(supplier_suppkey)
      val x110281 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx2.sliceRes(x58670);
      if((x110281.isEmpty)) {
      } else {
        val x4022 = if((x86937.==(null))) {
        0L
        } else {
        (x86937._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx2.sliceResMapNoUpd(x58670, ({ x4024: SEntry4_LLLD => {
            x58906._1_=((x4024._2))
            x58906._2_=((x4024._3))
            x58906._3_=((x4022.*((x4024._4))))
            val x58907 = x58906._3;
            if((x58907.==(0.0))) {
            } else {
              val x86954 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x58906);
              if((x86954.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x58906)
              } else {
                x86954._3 +=(x58907)
                if(((x86954._3).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.delete(x86954)
                } else {
                }
              }
            }
          
          }
        }), x110281)
      }
      x58673._1_=(supplier_nationkey)
      val x86967 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58673);
      x58678._2_=(supplier_suppkey)
      val x110314 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx1.sliceRes(x58678);
      if((x110314.isEmpty)) {
      } else {
        val x4049 = if((x86967.==(null))) {
        0L
        } else {
        (x86967._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx1.sliceResMapNoUpd(x58678, ({ x4051: SEntry5_LLLLD => {
            x58934._1_=((x4051._1))
            x58934._2_=((x4051._3))
            x58934._3_=((x4051._4))
            x58934._4_=((x4049.*((x4051._5))))
            val x58935 = x58934._4;
            if((x58935.==(0.0))) {
            } else {
              val x86986 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x58934);
              if((x86986.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x58934)
              } else {
                x86986._4 +=(x58935)
                if(((x86986._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x86986)
                } else {
                }
              }
            }
          
          }
        }), x110314)
      }
      x58681._1_=(supplier_nationkey)
      val x87000 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x58681);
      x58686._2_=(supplier_suppkey)
      val x110345 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx1.sliceRes(x58686);
      if((x110345.isEmpty)) {
      } else {
        val x4077 = if((x87000.==(null))) {
        0L
        } else {
        (x87000._2)
        };
        MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx1.sliceResMapNoUpd(x58686, ({ x4079: SEntry4_LLLD => {
            x58961._1_=((x4079._1))
            x58961._2_=((x4079._3))
            x58961._3_=((x4077.*((x4079._4))))
            val x58962 = x58961._3;
            if((x58962.==(0.0))) {
            } else {
              val x87017 = MKT_SHARE_mPART1_mPART2Idx0.get(x58961);
              if((x87017.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x58961)
              } else {
                x87017._3 +=(x58962)
                if(((x87017._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x87017)
                } else {
                }
              }
            }
          
          }
        }), x110345)
      }
      x58689._1_=(supplier_nationkey)
      val x87030 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58689);
      x58694._1_=(supplier_suppkey)
      val x110374 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx1.sliceRes(x58694);
      if((x110374.isEmpty)) {
      } else {
        val x4104 = if((x87030.==(null))) {
        0L
        } else {
        (x87030._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx1.sliceResMapNoUpd(x58694, ({ x4106: SEntry3_LLD => {
            x58987._1_=((x4106._2))
            x58987._2_=((x4104.*((x4106._3))))
            val x58988 = x58987._2;
            if((x58988.==(0.0))) {
            } else {
              val x87045 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x58987);
              if((x87045.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x58987)
              } else {
                x87045._2 +=(x58988)
                if(((x87045._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x87045)
                } else {
                }
              }
            }
          
          }
        }), x110374)
      }
      x58697._1_=(supplier_nationkey)
      val x87057 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58697);
      x58702._1_=(supplier_suppkey)
      val x110405 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx2.sliceRes(x58702);
      if((x110405.isEmpty)) {
      } else {
        val x4130 = if((x87057.==(null))) {
        0L
        } else {
        (x87057._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx2.sliceResMapNoUpd(x58702, ({ x4132: SEntry4_LLLD => {
            x59014._1_=((x4132._2))
            x59014._2_=((x4132._3))
            x59014._3_=((x4130.*((x4132._4))))
            val x59015 = x59014._3;
            if((x59015.==(0.0))) {
            } else {
              val x87074 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x59014);
              if((x87074.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x59014)
              } else {
                x87074._3 +=(x59015)
                if(((x87074._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x87074)
                } else {
                }
              }
            }
          
          }
        }), x110405)
      }
      x58705._1_=(supplier_nationkey)
      val x87087 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58705);
      x58710._2_=(supplier_suppkey)
      val x110438 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx1.sliceRes(x58710);
      if((x110438.isEmpty)) {
      } else {
        val x4157 = if((x87087.==(null))) {
        0L
        } else {
        (x87087._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x58710, ({ x4159: SEntry5_LLLLD => {
            x59042._1_=((x4159._1))
            x59042._2_=((x4159._3))
            x59042._3_=((x4159._4))
            x59042._4_=((x4157.*((x4159._5))))
            val x59043 = x59042._4;
            if((x59043.==(0.0))) {
            } else {
              val x87106 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x59042);
              if((x87106.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x59042)
              } else {
                x87106._4 +=(x59043)
                if(((x87106._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x87106)
                } else {
                }
              }
            }
          
          }
        }), x110438)
      }
      x58713._1_=(supplier_nationkey)
      val x87120 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x58713);
      x58718._2_=(supplier_suppkey)
      val x110469 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx1.sliceRes(x58718);
      if((x110469.isEmpty)) {
      } else {
        val x4185 = if((x87120.==(null))) {
        0L
        } else {
        (x87120._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x58718, ({ x4187: SEntry4_LLLD => {
            x59069._1_=((x4187._1))
            x59069._2_=((x4187._3))
            x59069._3_=((x4185.*((x4187._4))))
            val x59070 = x59069._3;
            if((x59070.==(0.0))) {
            } else {
              val x87137 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x59069);
              if((x87137.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x59069)
              } else {
                x87137._3 +=(x59070)
                if(((x87137._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x87137)
                } else {
                }
              }
            }
          
          }
        }), x110469)
      }
      MKT_SHARE.clear
      val x110509 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x110509.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x4209: SEntry2_LD => {
            val x4212 = Udate_year((x4209._1));
            var x4213: Double = 0.0;
            x59091._1_=(x4212)
            val x87157 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x59091);
            val x4218 = if((x87157.==(null))) {
            0.0
            } else {
            (x87157._2)
            };
            val x4220 = if((1L.>(x4218))) {
            1L
            } else {
            x4218
            };
            val x4221 = x4213;
            x4213 = (x4221.+(x4220))
            val x4224 = x4213;
            val x4227 = if((0.==(x4224))) {
            0.0
            } else {
            (1.0./(x4224))
            };
            x59106._1_=(x4212)
            x59106._2_=(((x4209._2).*(x4227)))
            val x59107 = x59106._2;
            if((x59107.==(0.0))) {
            } else {
              val x87176 = MKT_SHAREIdx0.get(x59106);
              if((x87176.==(null))) {
                MKT_SHARE.unsafeInsert(x59106)
              } else {
                x87176._2 +=(x59107)
                if(((x87176._2).==(0.0))) {
                  MKT_SHARE.delete(x87176)
                } else {
                }
              }
            }
          
          }
        }), x110509)
      }
    
    }
  
  }
  def onDelSUPPLIER(supplier_suppkey:Long, supplier_name:String, supplier_address:String, supplier_nationkey:Long, supplier_phone:String, supplier_acctbal:Double, supplier_comment:String) {
    {
      x59518._1_=(supplier_nationkey)
      val x87622 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59518);
      x59523._2_=(supplier_suppkey)
      val x110539 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceRes(x59523);
      if((x110539.isEmpty)) {
      } else {
        val x4256 = if((x87622.==(null))) {
        0L
        } else {
        (x87622._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceResMapNoUpd(x59523, ({ x4258: SEntry3_LLD => {
            x59669._1_=((x4258._1))
            x59669._2_=((x4256.*(((x4258._3).unary_-))))
            val x59670 = x59669._2;
            if((x59670.==(0.0))) {
            } else {
              val x87638 = MKT_SHARE_mORDERS1_L2_1_L1_5Idx0.get(x59669);
              if((x87638.==(null))) {
                MKT_SHARE_mORDERS1_L2_1_L1_5.unsafeInsert(x59669)
              } else {
                x87638._2 +=(x59670)
                if(((x87638._2).==(0.0))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5.delete(x87638)
                } else {
                }
              }
            }
          
          }
        }), x110539)
      }
      x59526._1_=(supplier_nationkey)
      val x87650 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59526);
      x59531._3_=(supplier_suppkey)
      val x110571 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceRes(x59531);
      if((x110571.isEmpty)) {
      } else {
        val x4283 = if((x87650.==(null))) {
        0L
        } else {
        (x87650._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x59531, ({ x4285: SEntry4_LLLD => {
            x59697._1_=((x4285._1))
            x59697._2_=((x4285._2))
            x59697._3_=((x4283.*(((x4285._4).unary_-))))
            val x59698 = x59697._3;
            if((x59698.==(0.0))) {
            } else {
              val x87668 = MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2Idx0.get(x59697);
              if((x87668.==(null))) {
                MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.unsafeInsert(x59697)
              } else {
                x87668._3 +=(x59698)
                if(((x87668._3).==(0.0))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5_mPART2.delete(x87668)
                } else {
                }
              }
            }
          
          }
        }), x110571)
      }
      x59534._1_=(supplier_nationkey)
      val x87682 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59534);
      val x4311 = if((x87682.==(null))) {
      0L
      } else {
      (x87682._2)
      };
      x59540._1_=(supplier_suppkey)
      x59540._2_=((x4311.unary_-))
      val x59541 = x59540._2;
      if((x59541.==(0L))) {
      } else {
        val x87692 = MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2Idx0.get(x59540);
        if((x87692.==(null))) {
          MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.unsafeInsert(x59540)
        } else {
          x87692._2 +=(x59541)
          if(((x87692._2).==(0L))) {
            MKT_SHARE_mORDERS1_L2_1_L1_5_mLINEITEM2.delete(x87692)
          } else {
          }
        }
      }
      x59554._1_=(supplier_nationkey)
      val x87703 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59554);
      x59559._2_=(supplier_suppkey)
      val x110621 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceRes(x59559);
      if((x110621.isEmpty)) {
      } else {
        val x4331 = if((x87703.==(null))) {
        0L
        } else {
        (x87703._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1Idx1.sliceResMapNoUpd(x59559, ({ x4333: SEntry3_LLD => {
            x59744._1_=((x4333._1))
            x59744._2_=((x4331.*(((x4333._3).unary_-))))
            val x59745 = x59744._2;
            if((x59745.==(0.0))) {
            } else {
              val x87719 = MKT_SHARE_mORDERS6Idx0.get(x59744);
              if((x87719.==(null))) {
                MKT_SHARE_mORDERS6.unsafeInsert(x59744)
              } else {
                x87719._2 +=(x59745)
                if(((x87719._2).==(0.0))) {
                  MKT_SHARE_mORDERS6.delete(x87719)
                } else {
                }
              }
            }
          
          }
        }), x110621)
      }
      x59562._1_=(supplier_nationkey)
      val x87731 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59562);
      x59567._3_=(supplier_suppkey)
      val x110653 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceRes(x59567);
      if((x110653.isEmpty)) {
      } else {
        val x4358 = if((x87731.==(null))) {
        0L
        } else {
        (x87731._2)
        };
        MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER1_mPART2Idx3.sliceResMapNoUpd(x59567, ({ x4360: SEntry4_LLLD => {
            x59772._1_=((x4360._1))
            x59772._2_=((x4360._2))
            x59772._3_=((x4358.*(((x4360._4).unary_-))))
            val x59773 = x59772._3;
            if((x59773.==(0.0))) {
            } else {
              val x87749 = MKT_SHARE_mORDERS6_mPART2Idx0.get(x59772);
              if((x87749.==(null))) {
                MKT_SHARE_mORDERS6_mPART2.unsafeInsert(x59772)
              } else {
                x87749._3 +=(x59773)
                if(((x87749._3).==(0.0))) {
                  MKT_SHARE_mORDERS6_mPART2.delete(x87749)
                } else {
                }
              }
            }
          
          }
        }), x110653)
      }
      x59570._1_=(supplier_nationkey)
      val x87763 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59570);
      val x4386 = if((x87763.==(null))) {
      0L
      } else {
      (x87763._2)
      };
      x59576._1_=(supplier_suppkey)
      x59576._2_=((x4386.unary_-))
      val x59577 = x59576._2;
      if((x59577.==(0L))) {
      } else {
        val x87773 = MKT_SHARE_mORDERS6_mLINEITEM1Idx0.get(x59576);
        if((x87773.==(null))) {
          MKT_SHARE_mORDERS6_mLINEITEM1.unsafeInsert(x59576)
        } else {
          x87773._2 +=(x59577)
          if(((x87773._2).==(0L))) {
            MKT_SHARE_mORDERS6_mLINEITEM1.delete(x87773)
          } else {
          }
        }
      }
      x59590._1_=(supplier_nationkey)
      val x87784 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59590);
      x59595._1_=(supplier_suppkey)
      val x110703 = MKT_SHARE_mPART1_mSUPPLIER2Idx1.sliceRes(x59595);
      if((x110703.isEmpty)) {
      } else {
        val x4406 = if((x87784.==(null))) {
        0L
        } else {
        (x87784._2)
        };
        MKT_SHARE_mPART1_mSUPPLIER2Idx1.sliceResMapNoUpd(x59595, ({ x4408: SEntry3_LLD => {
            x59819._1_=((x4408._2))
            x59819._2_=((x4406.*(((x4408._3).unary_-))))
            val x59820 = x59819._2;
            if((x59820.==(0.0))) {
            } else {
              val x87800 = MKT_SHARE_mPART1Idx0.get(x59819);
              if((x87800.==(null))) {
                MKT_SHARE_mPART1.unsafeInsert(x59819)
              } else {
                x87800._2 +=(x59820)
                if(((x87800._2).==(0.0))) {
                  MKT_SHARE_mPART1.delete(x87800)
                } else {
                }
              }
            }
          
          }
        }), x110703)
      }
      x59598._1_=(supplier_nationkey)
      val x87812 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59598);
      x59603._1_=(supplier_suppkey)
      val x110735 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx2.sliceRes(x59603);
      if((x110735.isEmpty)) {
      } else {
        val x4433 = if((x87812.==(null))) {
        0L
        } else {
        (x87812._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2Idx2.sliceResMapNoUpd(x59603, ({ x4435: SEntry4_LLLD => {
            x59847._1_=((x4435._2))
            x59847._2_=((x4435._3))
            x59847._3_=((x4433.*(((x4435._4).unary_-))))
            val x59848 = x59847._3;
            if((x59848.==(0.0))) {
            } else {
              val x87830 = MKT_SHARE_mPART1_mCUSTOMER1Idx0.get(x59847);
              if((x87830.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1.unsafeInsert(x59847)
              } else {
                x87830._3 +=(x59848)
                if(((x87830._3).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1.delete(x87830)
                } else {
                }
              }
            }
          
          }
        }), x110735)
      }
      x59606._1_=(supplier_nationkey)
      val x87843 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59606);
      x59611._2_=(supplier_suppkey)
      val x110769 = MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx1.sliceRes(x59611);
      if((x110769.isEmpty)) {
      } else {
        val x4461 = if((x87843.==(null))) {
        0L
        } else {
        (x87843._2)
        };
        MKT_SHARE_mPART1_mCUSTOMER1_mSUPPLIER2_mPART2Idx1.sliceResMapNoUpd(x59611, ({ x4463: SEntry5_LLLLD => {
            x59876._1_=((x4463._1))
            x59876._2_=((x4463._3))
            x59876._3_=((x4463._4))
            x59876._4_=((x4461.*(((x4463._5).unary_-))))
            val x59877 = x59876._4;
            if((x59877.==(0.0))) {
            } else {
              val x87863 = MKT_SHARE_mPART1_mCUSTOMER1_mPART2Idx0.get(x59876);
              if((x87863.==(null))) {
                MKT_SHARE_mPART1_mCUSTOMER1_mPART2.unsafeInsert(x59876)
              } else {
                x87863._4 +=(x59877)
                if(((x87863._4).==(0.0))) {
                  MKT_SHARE_mPART1_mCUSTOMER1_mPART2.delete(x87863)
                } else {
                }
              }
            }
          
          }
        }), x110769)
      }
      x59614._1_=(supplier_nationkey)
      val x87877 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x59614);
      x59619._2_=(supplier_suppkey)
      val x110801 = MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx1.sliceRes(x59619);
      if((x110801.isEmpty)) {
      } else {
        val x4490 = if((x87877.==(null))) {
        0L
        } else {
        (x87877._2)
        };
        MKT_SHARE_mPART1_mSUPPLIER2_mPART2Idx1.sliceResMapNoUpd(x59619, ({ x4492: SEntry4_LLLD => {
            x59904._1_=((x4492._1))
            x59904._2_=((x4492._3))
            x59904._3_=((x4490.*(((x4492._4).unary_-))))
            val x59905 = x59904._3;
            if((x59905.==(0.0))) {
            } else {
              val x87895 = MKT_SHARE_mPART1_mPART2Idx0.get(x59904);
              if((x87895.==(null))) {
                MKT_SHARE_mPART1_mPART2.unsafeInsert(x59904)
              } else {
                x87895._3 +=(x59905)
                if(((x87895._3).==(0.0))) {
                  MKT_SHARE_mPART1_mPART2.delete(x87895)
                } else {
                }
              }
            }
          
          }
        }), x110801)
      }
      x59622._1_=(supplier_nationkey)
      val x87908 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59622);
      x59627._1_=(supplier_suppkey)
      val x110831 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx1.sliceRes(x59627);
      if((x110831.isEmpty)) {
      } else {
        val x4518 = if((x87908.==(null))) {
        0L
        } else {
        (x87908._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1Idx1.sliceResMapNoUpd(x59627, ({ x4520: SEntry3_LLD => {
            x59931._1_=((x4520._2))
            x59931._2_=((x4518.*(((x4520._3).unary_-))))
            val x59932 = x59931._2;
            if((x59932.==(0.0))) {
            } else {
              val x87924 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x59931);
              if((x87924.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1.unsafeInsert(x59931)
              } else {
                x87924._2 +=(x59932)
                if(((x87924._2).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1.delete(x87924)
                } else {
                }
              }
            }
          
          }
        }), x110831)
      }
      x59630._1_=(supplier_nationkey)
      val x87936 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59630);
      x59635._1_=(supplier_suppkey)
      val x110863 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx2.sliceRes(x59635);
      if((x110863.isEmpty)) {
      } else {
        val x4545 = if((x87936.==(null))) {
        0L
        } else {
        (x87936._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1Idx2.sliceResMapNoUpd(x59635, ({ x4547: SEntry4_LLLD => {
            x59959._1_=((x4547._2))
            x59959._2_=((x4547._3))
            x59959._3_=((x4545.*(((x4547._4).unary_-))))
            val x59960 = x59959._3;
            if((x59960.==(0.0))) {
            } else {
              val x87954 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1Idx0.get(x59959);
              if((x87954.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.unsafeInsert(x59959)
              } else {
                x87954._3 +=(x59960)
                if(((x87954._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1.delete(x87954)
                } else {
                }
              }
            }
          
          }
        }), x110863)
      }
      x59638._1_=(supplier_nationkey)
      val x87967 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59638);
      x59643._2_=(supplier_suppkey)
      val x110897 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx1.sliceRes(x59643);
      if((x110897.isEmpty)) {
      } else {
        val x4573 = if((x87967.==(null))) {
        0L
        } else {
        (x87967._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x59643, ({ x4575: SEntry5_LLLLD => {
            x59988._1_=((x4575._1))
            x59988._2_=((x4575._3))
            x59988._3_=((x4575._4))
            x59988._4_=((x4573.*(((x4575._5).unary_-))))
            val x59989 = x59988._4;
            if((x59989.==(0.0))) {
            } else {
              val x87987 = MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2Idx0.get(x59988);
              if((x87987.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.unsafeInsert(x59988)
              } else {
                x87987._4 +=(x59989)
                if(((x87987._4).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mCUSTOMER1_mPART2.delete(x87987)
                } else {
                }
              }
            }
          
          }
        }), x110897)
      }
      x59646._1_=(supplier_nationkey)
      val x88001 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x59646);
      x59651._2_=(supplier_suppkey)
      val x110929 = MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx1.sliceRes(x59651);
      if((x110929.isEmpty)) {
      } else {
        val x4602 = if((x88001.==(null))) {
        0L
        } else {
        (x88001._2)
        };
        MKT_SHARE_mPART1_L2_1_L1_1_mSUPPLIER1_mPART2Idx1.sliceResMapNoUpd(x59651, ({ x4604: SEntry4_LLLD => {
            x60016._1_=((x4604._1))
            x60016._2_=((x4604._3))
            x60016._3_=((x4602.*(((x4604._4).unary_-))))
            val x60017 = x60016._3;
            if((x60017.==(0.0))) {
            } else {
              val x88019 = MKT_SHARE_mPART1_L2_1_L1_1_mPART2Idx0.get(x60016);
              if((x88019.==(null))) {
                MKT_SHARE_mPART1_L2_1_L1_1_mPART2.unsafeInsert(x60016)
              } else {
                x88019._3 +=(x60017)
                if(((x88019._3).==(0.0))) {
                  MKT_SHARE_mPART1_L2_1_L1_1_mPART2.delete(x88019)
                } else {
                }
              }
            }
          
          }
        }), x110929)
      }
      MKT_SHARE.clear
      val x110969 = MKT_SHARE_mPART1Idx0.foreachRes();
      if((x110969.isEmpty)) {
      } else {
        MKT_SHARE_mPART1Idx0.foreachResMap(({ x4627: SEntry2_LD => {
            val x4630 = Udate_year((x4627._1));
            var x4631: Double = 0.0;
            x60038._1_=(x4630)
            val x88039 = MKT_SHARE_mPART1_L2_1_L1_1Idx0.get(x60038);
            val x4636 = if((x88039.==(null))) {
            0.0
            } else {
            (x88039._2)
            };
            val x4638 = if((1L.>(x4636))) {
            1L
            } else {
            x4636
            };
            val x4639 = x4631;
            x4631 = (x4639.+(x4638))
            val x4642 = x4631;
            val x4645 = if((0.==(x4642))) {
            0.0
            } else {
            (1.0./(x4642))
            };
            x60053._1_=(x4630)
            x60053._2_=(((x4627._2).*(x4645)))
            val x60054 = x60053._2;
            if((x60054.==(0.0))) {
            } else {
              val x88058 = MKT_SHAREIdx0.get(x60053);
              if((x88058.==(null))) {
                MKT_SHARE.unsafeInsert(x60053)
              } else {
                x88058._2 +=(x60054)
                if(((x88058._2).==(0.0))) {
                  MKT_SHARE.delete(x88058)
                } else {
                }
              }
            }
          
          }
        }), x110969)
      }
    
    }
  
  }
  def onSystemReady() {
    {
      MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.clear
      val x111003 = NATIONIdx0.foreachRes();
      if((x111003.isEmpty)) {
      } else {
        NATIONIdx0.foreachResMap(({ x4664: SEntry5_LSLSL => {
            x60495._1_=((x4664._3))
            x60495._2_=("AMERICA")
            val x110999 = REGIONIdx1.sliceRes(x60495);
            if((x110999.isEmpty)) {
            } else {
              REGIONIdx1.sliceResMapNoUpd(x60495, ({ x4671: SEntry4_LSSL => {
                  x60551._1_=((x4664._1))
                  x60551._2_=(((x4664._5).*((x4671._4))))
                  val x60552 = x60551._2;
                  if((x60552.==(0L))) {
                  } else {
                    val x88534 = MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1Idx0.get(x60551);
                    if((x88534.==(null))) {
                      MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.unsafeInsert(x60551)
                    } else {
                      x88534._2 +=(x60552)
                      if(((x88534._2).==(0L))) {
                        MKT_SHARE_mORDERS1_L2_1_L1_4_mCUSTOMER1.delete(x88534)
                      } else {
                      }
                    }
                  }
                
                }
              }), x110999)
            }
            ()
          }
        }), x111003)
      }
      MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.clear
      val x111026 = NATIONIdx0.foreachRes();
      if((x111026.isEmpty)) {
      } else {
        NATIONIdx0.foreachResMap(({ x4694: SEntry5_LSLSL => {
            x60504._1_=((x4694._1))
            x60504._2_=((x4694._5))
            val x60505 = x60504._2;
            if((x60505.==(0L))) {
            } else {
              val x88556 = MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2Idx0.get(x60504);
              if((x88556.==(null))) {
                MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.unsafeInsert(x60504)
              } else {
                x88556._2 +=(x60505)
                if(((x88556._2).==(0L))) {
                  MKT_SHARE_mORDERS1_L2_1_L1_5_mSUPPLIER2.delete(x88556)
                } else {
                }
              }
            }
          
          }
        }), x111026)
      }
      MKT_SHARE_mORDERS6_mSUPPLIER1.clear
      x60486._2_=("BRAZIL")
      val x111050 = NATIONIdx1.sliceRes(x60486);
      if((x111050.isEmpty)) {
      } else {
        NATIONIdx1.sliceResMapNoUpd(x60486, ({ x4718: SEntry5_LSLSL => {
            x60525._1_=((x4718._1))
            x60525._2_=((x4718._5))
            val x60526 = x60525._2;
            if((x60526.==(0L))) {
            } else {
              val x88578 = MKT_SHARE_mORDERS6_mSUPPLIER1Idx0.get(x60525);
              if((x88578.==(null))) {
                MKT_SHARE_mORDERS6_mSUPPLIER1.unsafeInsert(x60525)
              } else {
                x88578._2 +=(x60526)
                if(((x88578._2).==(0L))) {
                  MKT_SHARE_mORDERS6_mSUPPLIER1.delete(x88578)
                } else {
                }
              }
            }
          
          }
        }), x111050)
      }
    
    }
  
  }

  val c2:Long = Udate("1996-12-31")
  val c1:Long = Udate("1995-1-1")
}


  

