package ddbt.gen

import lib.{Entry, EntryIdx, IHash, Store}
import tutorial.webapp.Functions.Udate

import scala.collection.mutable
import scala.concurrent.ExecutionContext.Implicits.global
import scala.scalajs.js.typedarray.ArrayBufferInputStream
import Messages._
import HelperGS._


object Tpch21JS {
  import Helper._

  

def exec(): Unit = {

    var res:List[Map[_ >: (String, String), Any]]=List()

        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/lineitem.csv").foreach(arraybuffer0=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/orders.csv").foreach(arraybuffer1=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/supplier.csv").foreach(arraybuffer2=>
        getABInputStream("https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/tpch/standard/nation.csv").foreach(arraybuffer3=>
        
        execute1(Seq(
        
         (arraybuffer0,new Adaptor.CSV("LINEITEM","long,long,long,long,double,double,double,double,string,string,date,date,date,string,string,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer1,new Adaptor.CSV("ORDERS","long,long,string,double,date,string,string,long,string","\\Q|\\E", "insert"), Split()),
         (arraybuffer2,new Adaptor.CSV("SUPPLIER","long,string,string,long,string,double,string","\\Q|\\E", "insert"), Split()),
        ),List(  arraybuffer3)))))
        )

  def execute1(streams: Streams, list: List[ArrayBufferInputStream]) = {
      loadTables(list);
      onSystemReady();
      goThroughStreams(streams, dispatchFnNoActor _)
        println("<snap>")
        println("<NUMWAIT>\n" + M3Map.toStr(res(0), List("S_NAME"))+"\n" + "</NUMWAIT>\n")
        println("</snap>")
        }
  def dispatchFnNoActor(e: StreamEvent) = e match {
    case TupleEvent(TupleInsert, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete, "LINEITEM", List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Long,v11:Long,v12:Long,v13:String,v14:String,v15:String)) => onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleInsert, "ORDERS", List(v0:Long,v1:Long,v2:String,v3:Double,v4:Long,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete, "ORDERS", List(v0:Long,v1:Long,v2:String,v3:Double,v4:Long,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert, "SUPPLIER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onAddSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case TupleEvent(TupleDelete, "SUPPLIER", List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onDelSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case EndOfStream | GetSnapshot(_) =>
       res=res:::(List({ val NUMWAIT_node_mres = new scala.collection.mutable.HashMap[String,Long](); NUMWAIT.foreach{e => NUMWAIT_node_mres += ((e._1,e._2)) }; NUMWAIT_node_mres.toMap }))
  }
def loadTables(list: List[ArrayBufferInputStream]) {
         SourceMux({ case TupleEvent(TupleInsert, rn, List(v0:Long,v1:String,v2:Long,v3:String)) => NATION.unsafeInsert(SEntry5_LSLSL(v0,v1,v2,v3, 1L)) }, Seq((list(0), new Adaptor.CSV("NATION","long,string,long,string","\\Q|\\E", "insert"), Split()))).read;
    }
}
    ////
  case class SEntry3_LLL(var _1: Long, var _2: Long, var _3: Long) extends Entry(3) {def this() = this(-2147483648L, -2147483648L, -2147483648L) ; def copy = SEntry3_LLL(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_LLL]; _1 = that._1;_2 = that._2;_3 = that._3} }
  case class SEntry2_SL(var _1: String, var _2: Long) extends Entry(2) {def this() = this(null, -2147483648L) ; def copy = SEntry2_SL(_1, _2); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry2_SL]; _1 = that._1;_2 = that._2} }
  case class SEntry4_LLSL(var _1: Long, var _2: Long, var _3: String, var _4: Long) extends Entry(4) {def this() = this(-2147483648L, -2147483648L, null, -2147483648L) ; def copy = SEntry4_LLSL(_1, _2, _3, _4); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry4_LLSL]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4} }
  case class SEntry5_LSLSL(var _1: Long, var _2: String, var _3: Long, var _4: String, var _5: Long) extends Entry(5) {def this() = this(-2147483648L, null, -2147483648L, null, -2147483648L) ; def copy = SEntry5_LSLSL(_1, _2, _3, _4, _5); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry5_LSLSL]; _1 = that._1;_2 = that._2;_3 = that._3;_4 = that._4;_5 = that._5} }
  case class SEntry3_LSL(var _1: Long, var _2: String, var _3: Long) extends Entry(3) {def this() = this(-2147483648L, null, -2147483648L) ; def copy = SEntry3_LSL(_1, _2, _3); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry3_LSL]; _1 = that._1;_2 = that._2;_3 = that._3} }
  case class SEntry2_LL(var _1: Long, var _2: Long) extends Entry(2) {def this() = this(-2147483648L, -2147483648L) ; def copy = SEntry2_LL(_1, _2); override def copyFrom(e: Entry) = { val that = e.asInstanceOf[SEntry2_LL]; _1 = that._1;_2 = that._2} }
   object SEntry5_LSLSL_Idx2 extends EntryIdx[SEntry5_LSLSL] {
    override def hash(x10041 : SEntry5_LSLSL) = {
      var x10042: Int = 0;
      val x10043 = x10042;
      x10042 = (x10043.^((((((x10041._2).hashCode()).+(-1640531527)).+((x10043.<<(6)))).+((x10043.>>(2))))))
      val x10053 = x10042;
      x10053
    }
    override def cmp(x10055 : SEntry5_LSLSL , x10056 : SEntry5_LSLSL) = {
      var x10057: Int = 0;
      if(((x10055._2).==((x10056._2)))) {
        x10057 = 0
      } else {
        x10057 = 1
      }
      val x10064 = x10057;
      x10064
    }
  }
   object SEntry2_LL_Idx1 extends EntryIdx[SEntry2_LL] {
    override def hash(x9833 : SEntry2_LL) = {
      var x9834: Int = 0;
      val x9835 = x9834;
      x9834 = (x9835.^((((((x9833._1).hashCode()).+(-1640531527)).+((x9835.<<(6)))).+((x9835.>>(2))))))
      val x9845 = x9834;
      x9845
    }
    override def cmp(x9847 : SEntry2_LL , x9848 : SEntry2_LL) = {
      var x9849: Int = 0;
      if(((x9847._1).==((x9848._1)))) {
        x9849 = 0
      } else {
        x9849 = 1
      }
      val x9856 = x9849;
      x9856
    }
  }
   object SEntry3_LSL_Idx1 extends EntryIdx[SEntry3_LSL] {
    override def hash(x9771 : SEntry3_LSL) = {
      var x9772: Int = 0;
      val x9773 = x9772;
      x9772 = (x9773.^((((((x9771._1).hashCode()).+(-1640531527)).+((x9773.<<(6)))).+((x9773.>>(2))))))
      val x9783 = x9772;
      x9783
    }
    override def cmp(x9785 : SEntry3_LSL , x9786 : SEntry3_LSL) = {
      var x9787: Int = 0;
      if(((x9785._1).==((x9786._1)))) {
        x9787 = 0
      } else {
        x9787 = 1
      }
      val x9794 = x9787;
      x9794
    }
  }
   object SEntry4_LLSL_Idx123 extends EntryIdx[SEntry4_LLSL] {
    override def hash(x10073 : SEntry4_LLSL) = {
      var x10074: Int = 0;
      val x10075 = x10074;
      x10074 = (x10075.^((((((x10073._1).hashCode()).+(-1640531527)).+((x10075.<<(6)))).+((x10075.>>(2))))))
      val x10085 = x10074;
      x10074 = (x10085.^((((((x10073._2).hashCode()).+(-1640531527)).+((x10085.<<(6)))).+((x10085.>>(2))))))
      val x10095 = x10074;
      x10074 = (x10095.^((((((x10073._3).hashCode()).+(-1640531527)).+((x10095.<<(6)))).+((x10095.>>(2))))))
      val x10105 = x10074;
      x10105
    }
    override def cmp(x10107 : SEntry4_LLSL , x10108 : SEntry4_LLSL) = {
      var x10109: Int = 0;
      if(((x10107._1).==((x10108._1)))) {
        if(((x10107._2).==((x10108._2)))) {
          if(((x10107._3).==((x10108._3)))) {
            x10109 = 0
          } else {
            x10109 = 1
          }
        } else {
          x10109 = 1
        }
      } else {
        x10109 = 1
      }
      val x10126 = x10109;
      x10126
    }
  }
   object SEntry3_LSL_Idx12 extends EntryIdx[SEntry3_LSL] {
    override def hash(x9730 : SEntry3_LSL) = {
      var x9731: Int = 0;
      val x9732 = x9731;
      x9731 = (x9732.^((((((x9730._1).hashCode()).+(-1640531527)).+((x9732.<<(6)))).+((x9732.>>(2))))))
      val x9742 = x9731;
      x9731 = (x9742.^((((((x9730._2).hashCode()).+(-1640531527)).+((x9742.<<(6)))).+((x9742.>>(2))))))
      val x9752 = x9731;
      x9752
    }
    override def cmp(x9754 : SEntry3_LSL , x9755 : SEntry3_LSL) = {
      var x9756: Int = 0;
      if(((x9754._1).==((x9755._1)))) {
        if(((x9754._2).==((x9755._2)))) {
          x9756 = 0
        } else {
          x9756 = 1
        }
      } else {
        x9756 = 1
      }
      val x9768 = x9756;
      x9768
    }
  }
   object SEntry3_LLL_Idx12 extends EntryIdx[SEntry3_LLL] {
    override def hash(x9864 : SEntry3_LLL) = {
      var x9865: Int = 0;
      val x9866 = x9865;
      x9865 = (x9866.^((((((x9864._1).hashCode()).+(-1640531527)).+((x9866.<<(6)))).+((x9866.>>(2))))))
      val x9876 = x9865;
      x9865 = (x9876.^((((((x9864._2).hashCode()).+(-1640531527)).+((x9876.<<(6)))).+((x9876.>>(2))))))
      val x9886 = x9865;
      x9886
    }
    override def cmp(x9888 : SEntry3_LLL , x9889 : SEntry3_LLL) = {
      var x9890: Int = 0;
      if(((x9888._1).==((x9889._1)))) {
        if(((x9888._2).==((x9889._2)))) {
          x9890 = 0
        } else {
          x9890 = 1
        }
      } else {
        x9890 = 1
      }
      val x9902 = x9890;
      x9902
    }
  }
   object SEntry5_LSLSL_Idx1234 extends EntryIdx[SEntry5_LSLSL] {
    override def hash(x9970 : SEntry5_LSLSL) = {
      var x9971: Int = 0;
      val x9972 = x9971;
      x9971 = (x9972.^((((((x9970._1).hashCode()).+(-1640531527)).+((x9972.<<(6)))).+((x9972.>>(2))))))
      val x9982 = x9971;
      x9971 = (x9982.^((((((x9970._2).hashCode()).+(-1640531527)).+((x9982.<<(6)))).+((x9982.>>(2))))))
      val x9992 = x9971;
      x9971 = (x9992.^((((((x9970._3).hashCode()).+(-1640531527)).+((x9992.<<(6)))).+((x9992.>>(2))))))
      val x10002 = x9971;
      x9971 = (x10002.^((((((x9970._4).hashCode()).+(-1640531527)).+((x10002.<<(6)))).+((x10002.>>(2))))))
      val x10012 = x9971;
      x10012
    }
    override def cmp(x10014 : SEntry5_LSLSL , x10015 : SEntry5_LSLSL) = {
      var x10016: Int = 0;
      if(((x10014._1).==((x10015._1)))) {
        if(((x10014._2).==((x10015._2)))) {
          if(((x10014._3).==((x10015._3)))) {
            if(((x10014._4).==((x10015._4)))) {
              x10016 = 0
            } else {
              x10016 = 1
            }
          } else {
            x10016 = 1
          }
        } else {
          x10016 = 1
        }
      } else {
        x10016 = 1
      }
      val x10038 = x10016;
      x10038
    }
  }
   object SEntry2_SL_Idx1 extends EntryIdx[SEntry2_SL] {
    override def hash(x9803 : SEntry2_SL) = {
      var x9804: Int = 0;
      val x9805 = x9804;
      x9804 = (x9805.^((((((x9803._1).hashCode()).+(-1640531527)).+((x9805.<<(6)))).+((x9805.>>(2))))))
      val x9815 = x9804;
      x9815
    }
    override def cmp(x9817 : SEntry2_SL , x9818 : SEntry2_SL) = {
      var x9819: Int = 0;
      if(((x9817._1).==((x9818._1)))) {
        x9819 = 0
      } else {
        x9819 = 1
      }
      val x9826 = x9819;
      x9826
    }
  }
   object SEntry4_LLSL_Idx1 extends EntryIdx[SEntry4_LLSL] {
    override def hash(x10129 : SEntry4_LLSL) = {
      var x10130: Int = 0;
      val x10131 = x10130;
      x10130 = (x10131.^((((((x10129._1).hashCode()).+(-1640531527)).+((x10131.<<(6)))).+((x10131.>>(2))))))
      val x10141 = x10130;
      x10141
    }
    override def cmp(x10143 : SEntry4_LLSL , x10144 : SEntry4_LLSL) = {
      var x10145: Int = 0;
      if(((x10143._1).==((x10144._1)))) {
        x10145 = 0
      } else {
        x10145 = 1
      }
      val x10152 = x10145;
      x10152
    }
  }
   object SEntry3_LLL_Idx2 extends EntryIdx[SEntry3_LLL] {
    override def hash(x9905 : SEntry3_LLL) = {
      var x9906: Int = 0;
      val x9907 = x9906;
      x9906 = (x9907.^((((((x9905._2).hashCode()).+(-1640531527)).+((x9907.<<(6)))).+((x9907.>>(2))))))
      val x9917 = x9906;
      x9917
    }
    override def cmp(x9919 : SEntry3_LLL , x9920 : SEntry3_LLL) = {
      var x9921: Int = 0;
      if(((x9919._2).==((x9920._2)))) {
        x9921 = 0
      } else {
        x9921 = 1
      }
      val x9928 = x9921;
      x9928
    }
  }
   object SEntry3_LLL_Idx1 extends EntryIdx[SEntry3_LLL] {
    override def hash(x9931 : SEntry3_LLL) = {
      var x9932: Int = 0;
      val x9933 = x9932;
      x9932 = (x9933.^((((((x9931._1).hashCode()).+(-1640531527)).+((x9933.<<(6)))).+((x9933.>>(2))))))
      val x9943 = x9932;
      x9943
    }
    override def cmp(x9945 : SEntry3_LLL , x9946 : SEntry3_LLL) = {
      var x9947: Int = 0;
      if(((x9945._1).==((x9946._1)))) {
        x9947 = 0
      } else {
        x9947 = 1
      }
      val x9954 = x9947;
      x9954
    }
  }
  
  val x9798 = Array[EntryIdx[SEntry3_LSL]](SEntry3_LSL_Idx12, SEntry3_LSL_Idx1)
  val NUMWAIT_mLINEITEM2 = new Store[SEntry3_LSL](2, x9798);
  val NUMWAIT_mLINEITEM2Idx0 = NUMWAIT_mLINEITEM2.index(0, IHash, true, -1)
  val NUMWAIT_mLINEITEM2Idx1 = NUMWAIT_mLINEITEM2.index(1, IHash, false, -1)
  val x9830 = Array[EntryIdx[SEntry2_SL]](SEntry2_SL_Idx1)
  val NUMWAIT = new Store[SEntry2_SL](1, x9830);
  val NUMWAITIdx0 = NUMWAIT.index(0, IHash, true, -1)
  val x9860 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val NUMWAIT_mSUPPLIER2 = new Store[SEntry2_LL](1, x9860);
  val NUMWAIT_mSUPPLIER2Idx0 = NUMWAIT_mSUPPLIER2.index(0, IHash, true, -1)
  val x9958 = Array[EntryIdx[SEntry3_LLL]](SEntry3_LLL_Idx12, SEntry3_LLL_Idx2, SEntry3_LLL_Idx1)
  val NUMWAIT_mSUPPLIER1_L2_1 = new Store[SEntry3_LLL](3, x9958);
  val NUMWAIT_mSUPPLIER1_L2_1Idx0 = NUMWAIT_mSUPPLIER1_L2_1.index(0, IHash, true, -1)
  val NUMWAIT_mSUPPLIER1_L2_1Idx1 = NUMWAIT_mSUPPLIER1_L2_1.index(1, IHash, false, -1)
  val NUMWAIT_mSUPPLIER1_L2_1Idx2 = NUMWAIT_mSUPPLIER1_L2_1.index(2, IHash, false, -1)
  val x9965 = Array[EntryIdx[SEntry3_LLL]](SEntry3_LLL_Idx12, SEntry3_LLL_Idx2)
  val NUMWAIT_mSUPPLIER1 = new Store[SEntry3_LLL](2, x9965);
  val NUMWAIT_mSUPPLIER1Idx0 = NUMWAIT_mSUPPLIER1.index(0, IHash, true, -1)
  val NUMWAIT_mSUPPLIER1Idx1 = NUMWAIT_mSUPPLIER1.index(1, IHash, false, -1)
  val x10068 = Array[EntryIdx[SEntry5_LSLSL]](SEntry5_LSLSL_Idx1234, SEntry5_LSLSL_Idx2)
  val NATION = new Store[SEntry5_LSLSL](2, x10068);
  val NATIONIdx0 = NATION.index(0, IHash, true, -1)
  val NATIONIdx1 = NATION.index(1, IHash, false, -1)
  val x10156 = Array[EntryIdx[SEntry4_LLSL]](SEntry4_LLSL_Idx123, SEntry4_LLSL_Idx1)
  val NUMWAIT_mLINEITEM7 = new Store[SEntry4_LLSL](2, x10156);
  val NUMWAIT_mLINEITEM7Idx0 = NUMWAIT_mLINEITEM7.index(0, IHash, true, -1)
  val NUMWAIT_mLINEITEM7Idx1 = NUMWAIT_mLINEITEM7.index(1, IHash, false, -1)
  val x10160 = Array[EntryIdx[SEntry2_LL]](SEntry2_LL_Idx1)
  val NUMWAIT_mLINEITEM3 = new Store[SEntry2_LL](1, x10160);
  val NUMWAIT_mLINEITEM3Idx0 = NUMWAIT_mLINEITEM3.index(0, IHash, true, -1)
  val x10164 = Array[EntryIdx[SEntry3_LLL]](SEntry3_LLL_Idx12, SEntry3_LLL_Idx1)
  val NUMWAIT_mSUPPLIER1_E3_1 = new Store[SEntry3_LLL](2, x10164);
  val NUMWAIT_mSUPPLIER1_E3_1Idx0 = NUMWAIT_mSUPPLIER1_E3_1.index(0, IHash, true, -1)
  val NUMWAIT_mSUPPLIER1_E3_1Idx1 = NUMWAIT_mSUPPLIER1_E3_1.index(1, IHash, false, -1)
  
  
  
  val x12798 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11418 = SEntry2_LL(-2147483648L, -2147483648L);
  val x10626 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x10790 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11384 = SEntry2_LL(-2147483648L, -2147483648L);
  val x10629 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x12217 = SEntry2_SL(null, -2147483648L);
  val x12752 = SEntry2_LL(-2147483648L, -2147483648L);
  val x11393 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10632 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x10607 = SEntry2_LL(-2147483648L, -2147483648L);
  val x11439 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x13132 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10675 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10759 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12173 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x11588 = SEntry2_SL(null, -2147483648L);
  val x10800 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11531 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12452 = SEntry2_LL(-2147483648L, -2147483648L);
  val x11414 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x13107 = SEntry2_LL(-2147483648L, -2147483648L);
  val x13093 = SEntry2_SL(null, -2147483648L);
  val x13213 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x13447 = SEntry5_LSLSL(-2147483648L, null, -2147483648L, null, -2147483648L);
  val x11569 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10767 = SEntry2_SL(null, -2147483648L);
  val x11500 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10637 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x12467 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11403 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x13147 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12530 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12738 = SEntry2_SL(null, -2147483648L);
  val x10616 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12192 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10661 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11406 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x10641 = SEntry2_LL(-2147483648L, -2147483648L);
  val x11409 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x12776 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12727 = SEntry2_LL(-2147483648L, -2147483648L);
  val x12211 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12479 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x13154 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11579 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12791 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10752 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11610 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x12486 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10722 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12733 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12854 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x13456 = SEntry2_LL(-2147483648L, -2147483648L);
  val x13081 = SEntry2_LL(-2147483648L, -2147483648L);
  val x12204 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12253 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x11424 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12493 = SEntry2_SL(null, -2147483648L);
  val x12771 = SEntry2_LL(-2147483648L, -2147483648L);
  val x12177 = SEntry2_LL(-2147483648L, -2147483648L);
  val x10646 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x12448 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x12757 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x10730 = SEntry2_SL(null, -2147483648L);
  val x11538 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x13113 = SEntry3_LSL(-2147483648L, null, -2147483648L);
  val x11509 = SEntry2_SL(null, -2147483648L);
  val x11546 = SEntry2_SL(null, -2147483648L);
  val x11453 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10830 = SEntry4_LLSL(-2147483648L, -2147483648L, null, -2147483648L);
  val x13087 = SEntry3_LLL(-2147483648L, -2147483648L, -2147483648L);
  val x10809 = SEntry2_SL(null, -2147483648L);
  val x13127 = SEntry2_LL(-2147483648L, -2147483648L);
  def onAddLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      x10607._1_=(lineitem_orderkey)
      val x17672 = NUMWAIT_mLINEITEM3Idx0.get(x10607);
      val x30 = if((x17672.==(null))) {
      0L
      } else {
      (x17672._2)
      };
      val x31 = lineitem_receiptdate.>(lineitem_commitdate);
      if(x31) {
        var x32: Long = 0L;
        var x33: Long = 0L;
        x10616._1_=(lineitem_orderkey)
        val x23728 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x10616);
        if((x23728.isEmpty)) {
        } else {
          NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x10616, ({ x35: SEntry3_LLL => {
              val x40 = if(((x35._2).!=(lineitem_suppkey))) {
              (x35._3)
              } else {
              0L
              };
              val x41 = x33;
              x33 = (x41.+(x40))
              ()
            }
          }), x23728)
        }
        val x46 = x33;
        val x49 = x32;
        x32 = (x49.+((if((0L.==(x46))) 1L else 0L)))
        val x52 = x32;
        x10626._1_=(lineitem_suppkey)
        val x23778 = NUMWAIT_mLINEITEM2Idx1.sliceRes(x10626);
        if((x23778.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM2Idx1.sliceResMapNoUpd(x10626, ({ x54: SEntry3_LSL => {
              var x57: Long = 0L;
              x10722._1_=(lineitem_orderkey)
              val x23755 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x10722);
              if((x23755.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x10722, ({ x59: SEntry3_LLL => {
                    val x64 = if(((x59._2).!=(lineitem_suppkey))) {
                    (x59._3)
                    } else {
                    0L
                    };
                    val x65 = x57;
                    x57 = (x65.+(x64))
                    ()
                  }
                }), x23755)
              }
              val x70 = x57;
              val x73 = if((x70.!=(0L))) {
              (x54._3)
              } else {
              0L
              };
              x10730._1_=((x54._2))
              x10730._2_=((x30.*((x52.*(x73)))))
              val x10731 = x10730._2;
              if((x10731.==(0L))) {
              } else {
                val x17725 = NUMWAITIdx0.get(x10730);
                if((x17725.==(null))) {
                  NUMWAIT.unsafeInsert(x10730)
                } else {
                  x17725._2 +=(x10731)
                  if(((x17725._2).==(0L))) {
                    NUMWAIT.delete(x17725)
                  } else {
                  }
                }
              }
            
            }
          }), x23778)
        }
      } else {
      }
      x10629._1_=(lineitem_orderkey)
      val x23840 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x10629);
      if((x23840.isEmpty)) {
      } else {
        NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x10629, ({ x94: SEntry4_LLSL => {
            val x10748 = x94._2;
            var x98: Long = 0L;
            x10752._1_=(lineitem_orderkey)
            val x23799 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x10752);
            if((x23799.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x10752, ({ x100: SEntry3_LLL => {
                  val x105 = if(((x100._2).!=(x10748))) {
                  (x100._3)
                  } else {
                  0L
                  };
                  val x106 = x98;
                  x98 = (x106.+(x105))
                  ()
                }
              }), x23799)
            }
            val x111 = x98;
            if((x111.==(0L))) {
              var x113: Long = 0L;
              x10759._1_=(lineitem_orderkey)
              val x23817 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x10759);
              if((x23817.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x10759, ({ x115: SEntry3_LLL => {
                    val x120 = if(((x115._2).!=(x10748))) {
                    (x115._3)
                    } else {
                    0L
                    };
                    val x121 = x113;
                    x113 = (x121.+(x120))
                    ()
                  }
                }), x23817)
              }
              val x126 = x113;
              val x129 = if((x126.!=(0L))) {
              (x94._4)
              } else {
              0L
              };
              x10767._1_=((x94._3))
              x10767._2_=((x30.*((x129.unary_-))))
              val x10768 = x10767._2;
              if((x10768.==(0L))) {
              } else {
                val x17779 = NUMWAITIdx0.get(x10767);
                if((x17779.==(null))) {
                  NUMWAIT.unsafeInsert(x10767)
                } else {
                  x17779._2 +=(x10768)
                  if(((x17779._2).==(0L))) {
                    NUMWAIT.delete(x17779)
                  } else {
                  }
                }
              }
            } else {
            }
            ()
          }
        }), x23840)
      }
      x10632._1_=(lineitem_orderkey)
      val x23907 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x10632);
      if((x23907.isEmpty)) {
      } else {
        NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x10632, ({ x150: SEntry4_LLSL => {
            val x10786 = x150._2;
            var x154: Long = 0L;
            x10790._1_=(lineitem_orderkey)
            val x23862 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x10790);
            if((x23862.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x10790, ({ x156: SEntry3_LLL => {
                  val x161 = if(((x156._2).!=(x10786))) {
                  (x156._3)
                  } else {
                  0L
                  };
                  val x162 = x154;
                  x154 = (x162.+(x161))
                  ()
                }
              }), x23862)
            }
            val x167 = x154;
            val x168 = lineitem_suppkey.!=(x10786);
            val x170 = if(x168) {
            (if(x31) 1L else 0L)
            } else {
            0L
            };
            if(((x167.+(x170)).==(0L))) {
              var x173: Long = 0L;
              x10800._1_=(lineitem_orderkey)
              val x23883 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x10800);
              if((x23883.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x10800, ({ x175: SEntry3_LLL => {
                    val x180 = if(((x175._2).!=(x10786))) {
                    (x175._3)
                    } else {
                    0L
                    };
                    val x181 = x173;
                    x173 = (x181.+(x180))
                    ()
                  }
                }), x23883)
              }
              val x186 = x173;
              val x191 = if(((x186.+((if(x168) 1L else 0L))).!=(0L))) {
              (x150._4)
              } else {
              0L
              };
              x10809._1_=((x150._3))
              x10809._2_=((x30.*(x191)))
              val x10810 = x10809._2;
              if((x10810.==(0L))) {
              } else {
                val x17838 = NUMWAITIdx0.get(x10809);
                if((x17838.==(null))) {
                  NUMWAIT.unsafeInsert(x10809)
                } else {
                  x17838._2 +=(x10810)
                  if(((x17838._2).==(0L))) {
                    NUMWAIT.delete(x17838)
                  } else {
                  }
                }
              }
            } else {
            }
            ()
          }
        }), x23907)
      }
      if(x31) {
        x10637._1_=(lineitem_suppkey)
        val x23933 = NUMWAIT_mLINEITEM2Idx1.sliceRes(x10637);
        if((x23933.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM2Idx1.sliceResMapNoUpd(x10637, ({ x211: SEntry3_LSL => {
              x10830._1_=(lineitem_orderkey)
              x10830._2_=(lineitem_suppkey)
              x10830._3_=((x211._2))
              x10830._4_=((x211._3))
              val x10831 = x10830._4;
              if((x10831.==(0L))) {
              } else {
                val x17862 = NUMWAIT_mLINEITEM7Idx0.get(x10830);
                if((x17862.==(null))) {
                  NUMWAIT_mLINEITEM7.unsafeInsert(x10830)
                } else {
                  x17862._4 +=(x10831)
                  if(((x17862._4).==(0L))) {
                    NUMWAIT_mLINEITEM7.delete(x17862)
                  } else {
                  }
                }
              }
            
            }
          }), x23933)
        }
      } else {
      }
      if(x31) {
        x10641._1_=(lineitem_orderkey)
        val x17876 = NUMWAIT_mLINEITEM3Idx0.get(x10641);
        val x235 = if((x17876.==(null))) {
        0L
        } else {
        (x17876._2)
        };
        x10646._1_=(lineitem_orderkey)
        x10646._2_=(lineitem_suppkey)
        x10646._3_=(x235)
        val x10647 = x10646._3;
        if((x10647.==(0L))) {
        } else {
          val x17886 = NUMWAIT_mSUPPLIER1Idx0.get(x10646);
          if((x17886.==(null))) {
            NUMWAIT_mSUPPLIER1.unsafeInsert(x10646)
          } else {
            x17886._3 +=(x10647)
            if(((x17886._3).==(0L))) {
              NUMWAIT_mSUPPLIER1.delete(x17886)
            } else {
            }
          }
        }
      } else {
      }
      x10661._1_=(lineitem_orderkey)
      x10661._2_=(lineitem_suppkey)
      x10661._3_=((if(x31) 1L else 0L))
      val x10662 = x10661._3;
      if((x10662.==(0L))) {
      } else {
        val x17904 = NUMWAIT_mSUPPLIER1_L2_1Idx0.get(x10661);
        if((x17904.==(null))) {
          NUMWAIT_mSUPPLIER1_L2_1.unsafeInsert(x10661)
        } else {
          x17904._3 +=(x10662)
          if(((x17904._3).==(0L))) {
            NUMWAIT_mSUPPLIER1_L2_1.delete(x17904)
          } else {
          }
        }
      }
      x10675._1_=(lineitem_orderkey)
      x10675._2_=(lineitem_suppkey)
      x10675._3_=(1L)
      val x10676 = x10675._3;
      if((x10676.==(0L))) {
      } else {
        val x17922 = NUMWAIT_mSUPPLIER1_E3_1Idx0.get(x10675);
        if((x17922.==(null))) {
          NUMWAIT_mSUPPLIER1_E3_1.unsafeInsert(x10675)
        } else {
          x17922._3 +=(x10676)
          if(((x17922._3).==(0L))) {
            NUMWAIT_mSUPPLIER1_E3_1.delete(x17922)
          } else {
          }
        }
      }
    
    }
  
  }
  def onDelLINEITEM(lineitem_orderkey:Long, lineitem_partkey:Long, lineitem_suppkey:Long, lineitem_linenumber:Long, lineitem_quantity:Double, lineitem_extendedprice:Double, lineitem_discount:Double, lineitem_tax:Double, lineitem_returnflag:String, lineitem_linestatus:String, lineitem_shipdate:Long, lineitem_commitdate:Long, lineitem_receiptdate:Long, lineitem_shipinstruct:String, lineitem_shipmode:String, lineitem_comment:String) {
    {
      x11384._1_=(lineitem_orderkey)
      val x18196 = NUMWAIT_mLINEITEM3Idx0.get(x11384);
      val x300 = if((x18196.==(null))) {
      0L
      } else {
      (x18196._2)
      };
      val x301 = lineitem_receiptdate.>(lineitem_commitdate);
      if(x301) {
        var x302: Long = 0L;
        var x303: Long = 0L;
        x11393._1_=(lineitem_orderkey)
        val x24008 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x11393);
        if((x24008.isEmpty)) {
        } else {
          NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x11393, ({ x305: SEntry3_LLL => {
              val x310 = if(((x305._2).!=(lineitem_suppkey))) {
              (x305._3)
              } else {
              0L
              };
              val x311 = x303;
              x303 = (x311.+(x310))
              ()
            }
          }), x24008)
        }
        val x316 = x303;
        val x319 = x302;
        x302 = (x319.+((if((0L.==(x316))) 1L else 0L)))
        val x322 = x302;
        x11403._1_=(lineitem_suppkey)
        val x24059 = NUMWAIT_mLINEITEM2Idx1.sliceRes(x11403);
        if((x24059.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM2Idx1.sliceResMapNoUpd(x11403, ({ x324: SEntry3_LSL => {
              var x327: Long = 0L;
              x11500._1_=(lineitem_orderkey)
              val x24035 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x11500);
              if((x24035.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x11500, ({ x329: SEntry3_LLL => {
                    val x334 = if(((x329._2).!=(lineitem_suppkey))) {
                    (x329._3)
                    } else {
                    0L
                    };
                    val x335 = x327;
                    x327 = (x335.+(x334))
                    ()
                  }
                }), x24035)
              }
              val x340 = x327;
              if((x340.!=(0))) {
                x11509._1_=((x324._2))
                x11509._2_=((x300.*((x322.*(((x324._3).unary_-))))))
                val x11510 = x11509._2;
                if((x11510.==(0L))) {
                } else {
                  val x18250 = NUMWAITIdx0.get(x11509);
                  if((x18250.==(null))) {
                    NUMWAIT.unsafeInsert(x11509)
                  } else {
                    x18250._2 +=(x11510)
                    if(((x18250._2).==(0L))) {
                      NUMWAIT.delete(x18250)
                    } else {
                    }
                  }
                }
              } else {
              }
              ()
            }
          }), x24059)
        }
      } else {
      }
      x11406._1_=(lineitem_orderkey)
      val x24121 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x11406);
      if((x24121.isEmpty)) {
      } else {
        NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x11406, ({ x364: SEntry4_LLSL => {
            val x11527 = x364._2;
            var x368: Long = 0L;
            x11531._1_=(lineitem_orderkey)
            val x24080 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x11531);
            if((x24080.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x11531, ({ x370: SEntry3_LLL => {
                  val x375 = if(((x370._2).!=(x11527))) {
                  (x370._3)
                  } else {
                  0L
                  };
                  val x376 = x368;
                  x368 = (x376.+(x375))
                  ()
                }
              }), x24080)
            }
            val x381 = x368;
            if((x381.==(0L))) {
              var x383: Long = 0L;
              x11538._1_=(lineitem_orderkey)
              val x24098 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x11538);
              if((x24098.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x11538, ({ x385: SEntry3_LLL => {
                    val x390 = if(((x385._2).!=(x11527))) {
                    (x385._3)
                    } else {
                    0L
                    };
                    val x391 = x383;
                    x383 = (x391.+(x390))
                    ()
                  }
                }), x24098)
              }
              val x396 = x383;
              val x399 = if((x396.!=(0L))) {
              (x364._4)
              } else {
              0L
              };
              x11546._1_=((x364._3))
              x11546._2_=((x300.*((x399.unary_-))))
              val x11547 = x11546._2;
              if((x11547.==(0L))) {
              } else {
                val x18304 = NUMWAITIdx0.get(x11546);
                if((x18304.==(null))) {
                  NUMWAIT.unsafeInsert(x11546)
                } else {
                  x18304._2 +=(x11547)
                  if(((x18304._2).==(0L))) {
                    NUMWAIT.delete(x18304)
                  } else {
                  }
                }
              }
            } else {
            }
            ()
          }
        }), x24121)
      }
      x11409._1_=(lineitem_orderkey)
      val x24188 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x11409);
      if((x24188.isEmpty)) {
      } else {
        val x439 = if(x301) {
        -1L
        } else {
        0L
        };
        NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x11409, ({ x420: SEntry4_LLSL => {
            val x11565 = x420._2;
            var x424: Long = 0L;
            x11569._1_=(lineitem_orderkey)
            val x24143 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x11569);
            if((x24143.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x11569, ({ x426: SEntry3_LLL => {
                  val x431 = if(((x426._2).!=(x11565))) {
                  (x426._3)
                  } else {
                  0L
                  };
                  val x432 = x424;
                  x424 = (x432.+(x431))
                  ()
                }
              }), x24143)
            }
            val x437 = x424;
            val x438 = lineitem_suppkey.!=(x11565);
            val x440 = if(x438) {
            x439
            } else {
            0L
            };
            if(((x437.+(x440)).==(0L))) {
              var x443: Long = 0L;
              x11579._1_=(lineitem_orderkey)
              val x24164 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x11579);
              if((x24164.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x11579, ({ x445: SEntry3_LLL => {
                    val x450 = if(((x445._2).!=(x11565))) {
                    (x445._3)
                    } else {
                    0L
                    };
                    val x451 = x443;
                    x443 = (x451.+(x450))
                    ()
                  }
                }), x24164)
              }
              val x456 = x443;
              val x457 = if(x438) {
              -1L
              } else {
              0L
              };
              val x461 = if(((x456.+(x457)).!=(0L))) {
              (x420._4)
              } else {
              0L
              };
              x11588._1_=((x420._3))
              x11588._2_=((x300.*(x461)))
              val x11589 = x11588._2;
              if((x11589.==(0L))) {
              } else {
                val x18363 = NUMWAITIdx0.get(x11588);
                if((x18363.==(null))) {
                  NUMWAIT.unsafeInsert(x11588)
                } else {
                  x18363._2 +=(x11589)
                  if(((x18363._2).==(0L))) {
                    NUMWAIT.delete(x18363)
                  } else {
                  }
                }
              }
            } else {
            }
            ()
          }
        }), x24188)
      }
      if(x301) {
        x11414._1_=(lineitem_suppkey)
        val x24215 = NUMWAIT_mLINEITEM2Idx1.sliceRes(x11414);
        if((x24215.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM2Idx1.sliceResMapNoUpd(x11414, ({ x481: SEntry3_LSL => {
              x11610._1_=(lineitem_orderkey)
              x11610._2_=(lineitem_suppkey)
              x11610._3_=((x481._2))
              x11610._4_=(((x481._3).unary_-))
              val x11611 = x11610._4;
              if((x11611.==(0L))) {
              } else {
                val x18388 = NUMWAIT_mLINEITEM7Idx0.get(x11610);
                if((x18388.==(null))) {
                  NUMWAIT_mLINEITEM7.unsafeInsert(x11610)
                } else {
                  x18388._4 +=(x11611)
                  if(((x18388._4).==(0L))) {
                    NUMWAIT_mLINEITEM7.delete(x18388)
                  } else {
                  }
                }
              }
            
            }
          }), x24215)
        }
      } else {
      }
      if(x301) {
        x11418._1_=(lineitem_orderkey)
        val x18402 = NUMWAIT_mLINEITEM3Idx0.get(x11418);
        val x506 = if((x18402.==(null))) {
        0L
        } else {
        (x18402._2)
        };
        x11424._1_=(lineitem_orderkey)
        x11424._2_=(lineitem_suppkey)
        x11424._3_=((x506.unary_-))
        val x11425 = x11424._3;
        if((x11425.==(0L))) {
        } else {
          val x18413 = NUMWAIT_mSUPPLIER1Idx0.get(x11424);
          if((x18413.==(null))) {
            NUMWAIT_mSUPPLIER1.unsafeInsert(x11424)
          } else {
            x18413._3 +=(x11425)
            if(((x18413._3).==(0L))) {
              NUMWAIT_mSUPPLIER1.delete(x18413)
            } else {
            }
          }
        }
      } else {
      }
      if(x301) {
        x11439._1_=(lineitem_orderkey)
        x11439._2_=(lineitem_suppkey)
        x11439._3_=(-1L)
        val x11440 = x11439._3;
        if((x11440.==(0L))) {
        } else {
          val x18431 = NUMWAIT_mSUPPLIER1_L2_1Idx0.get(x11439);
          if((x18431.==(null))) {
            NUMWAIT_mSUPPLIER1_L2_1.unsafeInsert(x11439)
          } else {
            x18431._3 +=(x11440)
            if(((x18431._3).==(0L))) {
              NUMWAIT_mSUPPLIER1_L2_1.delete(x18431)
            } else {
            }
          }
        }
      } else {
      }
      x11453._1_=(lineitem_orderkey)
      x11453._2_=(lineitem_suppkey)
      x11453._3_=(-1L)
      val x11454 = x11453._3;
      if((x11454.==(0L))) {
      } else {
        val x18449 = NUMWAIT_mSUPPLIER1_E3_1Idx0.get(x11453);
        if((x18449.==(null))) {
          NUMWAIT_mSUPPLIER1_E3_1.unsafeInsert(x11453)
        } else {
          x18449._3 +=(x11454)
          if(((x18449._3).==(0L))) {
            NUMWAIT_mSUPPLIER1_E3_1.delete(x18449)
          } else {
          }
        }
      }
    
    }
  
  }
  def onAddORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Long, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    {
      val x561 = orders_orderstatus.==("F");
      if(x561) {
        x12173._1_=(orders_orderkey)
        val x24330 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x12173);
        if((x24330.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x12173, ({ x563: SEntry4_LLSL => {
              val x12200 = x563._2;
              var x567: Long = 0L;
              x12204._1_=(orders_orderkey)
              val x24291 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x12204);
              if((x24291.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x12204, ({ x569: SEntry3_LLL => {
                    val x574 = if(((x569._2).!=(x12200))) {
                    (x569._3)
                    } else {
                    0L
                    };
                    val x575 = x567;
                    x567 = (x575.+(x574))
                    ()
                  }
                }), x24291)
              }
              val x580 = x567;
              if((x580.==(0L))) {
                var x582: Long = 0L;
                x12211._1_=(orders_orderkey)
                val x24309 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x12211);
                if((x24309.isEmpty)) {
                } else {
                  NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x12211, ({ x584: SEntry3_LLL => {
                      val x589 = if(((x584._2).!=(x12200))) {
                      (x584._3)
                      } else {
                      0L
                      };
                      val x590 = x582;
                      x582 = (x590.+(x589))
                      ()
                    }
                  }), x24309)
                }
                val x595 = x582;
                val x598 = if((x595.!=(0L))) {
                (x563._4)
                } else {
                0L
                };
                x12217._1_=((x563._3))
                x12217._2_=(x598)
                val x12218 = x12217._2;
                if((x12218.==(0L))) {
                } else {
                  val x18768 = NUMWAITIdx0.get(x12217);
                  if((x18768.==(null))) {
                    NUMWAIT.unsafeInsert(x12217)
                  } else {
                    x18768._2 +=(x12218)
                    if(((x18768._2).==(0L))) {
                      NUMWAIT.delete(x18768)
                    } else {
                    }
                  }
                }
              } else {
              }
              ()
            }
          }), x24330)
        }
      } else {
      }
      x12177._1_=(orders_orderkey)
      x12177._2_=((if(x561) 1L else 0L))
      val x12178 = x12177._2;
      if((x12178.==(0L))) {
      } else {
        val x18785 = NUMWAIT_mLINEITEM3Idx0.get(x12177);
        if((x18785.==(null))) {
          NUMWAIT_mLINEITEM3.unsafeInsert(x12177)
        } else {
          x18785._2 +=(x12178)
          if(((x18785._2).==(0L))) {
            NUMWAIT_mLINEITEM3.delete(x18785)
          } else {
          }
        }
      }
      if(x561) {
        x12192._1_=(orders_orderkey)
        val x24370 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x12192);
        if((x24370.isEmpty)) {
        } else {
          NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x12192, ({ x633: SEntry3_LLL => {
              x12253._1_=(orders_orderkey)
              x12253._2_=((x633._2))
              x12253._3_=((x633._3))
              val x12254 = x12253._3;
              if((x12254.==(0L))) {
              } else {
                val x18807 = NUMWAIT_mSUPPLIER1Idx0.get(x12253);
                if((x18807.==(null))) {
                  NUMWAIT_mSUPPLIER1.unsafeInsert(x12253)
                } else {
                  x18807._3 +=(x12254)
                  if(((x18807._3).==(0L))) {
                    NUMWAIT_mSUPPLIER1.delete(x18807)
                  } else {
                  }
                }
              }
            
            }
          }), x24370)
        }
      } else {
      }
    
    }
  
  }
  def onDelORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Long, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    {
      val x662 = orders_orderstatus.==("F");
      if(x662) {
        x12448._1_=(orders_orderkey)
        val x24433 = NUMWAIT_mLINEITEM7Idx1.sliceRes(x12448);
        if((x24433.isEmpty)) {
        } else {
          NUMWAIT_mLINEITEM7Idx1.sliceResMapNoUpd(x12448, ({ x664: SEntry4_LLSL => {
              val x12475 = x664._2;
              var x668: Long = 0L;
              x12479._1_=(orders_orderkey)
              val x24393 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x12479);
              if((x24393.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x12479, ({ x670: SEntry3_LLL => {
                    val x675 = if(((x670._2).!=(x12475))) {
                    (x670._3)
                    } else {
                    0L
                    };
                    val x676 = x668;
                    x668 = (x676.+(x675))
                    ()
                  }
                }), x24393)
              }
              val x681 = x668;
              if((x681.==(0L))) {
                var x683: Long = 0L;
                x12486._1_=(orders_orderkey)
                val x24411 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x12486);
                if((x24411.isEmpty)) {
                } else {
                  NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x12486, ({ x685: SEntry3_LLL => {
                      val x690 = if(((x685._2).!=(x12475))) {
                      (x685._3)
                      } else {
                      0L
                      };
                      val x691 = x683;
                      x683 = (x691.+(x690))
                      ()
                    }
                  }), x24411)
                }
                val x696 = x683;
                val x699 = if((x696.!=(0L))) {
                (x664._4)
                } else {
                0L
                };
                x12493._1_=((x664._3))
                x12493._2_=((x699.unary_-))
                val x12494 = x12493._2;
                if((x12494.==(0L))) {
                } else {
                  val x18957 = NUMWAITIdx0.get(x12493);
                  if((x18957.==(null))) {
                    NUMWAIT.unsafeInsert(x12493)
                  } else {
                    x18957._2 +=(x12494)
                    if(((x18957._2).==(0L))) {
                      NUMWAIT.delete(x18957)
                    } else {
                    }
                  }
                }
              } else {
              }
              ()
            }
          }), x24433)
        }
      } else {
      }
      if(x662) {
        x12452._1_=(orders_orderkey)
        x12452._2_=(-1L)
        val x12453 = x12452._2;
        if((x12453.==(0L))) {
        } else {
          val x18974 = NUMWAIT_mLINEITEM3Idx0.get(x12452);
          if((x18974.==(null))) {
            NUMWAIT_mLINEITEM3.unsafeInsert(x12452)
          } else {
            x18974._2 +=(x12453)
            if(((x18974._2).==(0L))) {
              NUMWAIT_mLINEITEM3.delete(x18974)
            } else {
            }
          }
        }
      } else {
      }
      if(x662) {
        x12467._1_=(orders_orderkey)
        val x24474 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x12467);
        if((x24474.isEmpty)) {
        } else {
          NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x12467, ({ x735: SEntry3_LLL => {
              x12530._1_=(orders_orderkey)
              x12530._2_=((x735._2))
              x12530._3_=(((x735._3).unary_-))
              val x12531 = x12530._3;
              if((x12531.==(0L))) {
              } else {
                val x18997 = NUMWAIT_mSUPPLIER1Idx0.get(x12530);
                if((x18997.==(null))) {
                  NUMWAIT_mSUPPLIER1.unsafeInsert(x12530)
                } else {
                  x18997._3 +=(x12531)
                  if(((x18997._3).==(0L))) {
                    NUMWAIT_mSUPPLIER1.delete(x18997)
                  } else {
                  }
                }
              }
            
            }
          }), x24474)
        }
      } else {
      }
    
    }
  
  }
  def onAddSUPPLIER(supplier_suppkey:Long, supplier_name:String, supplier_address:String, supplier_nationkey:Long, supplier_phone:String, supplier_acctbal:Double, supplier_comment:String) {
    {
      x12727._1_=(supplier_nationkey)
      val x19106 = NUMWAIT_mSUPPLIER2Idx0.get(x12727);
      val x767 = if((x19106.==(null))) {
      0L
      } else {
      (x19106._2)
      };
      var x768: Long = 0L;
      x12733._2_=(supplier_suppkey)
      val x24528 = NUMWAIT_mSUPPLIER1Idx1.sliceRes(x12733);
      if((x24528.isEmpty)) {
      } else {
        NUMWAIT_mSUPPLIER1Idx1.sliceResMapNoUpd(x12733, ({ x770: SEntry3_LLL => {
            val x12788 = x770._1;
            var x773: Long = 0L;
            x12791._1_=(x12788)
            val x24500 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x12791);
            if((x24500.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x12791, ({ x775: SEntry3_LLL => {
                  val x780 = if(((x775._2).!=(supplier_suppkey))) {
                  (x775._3)
                  } else {
                  0L
                  };
                  val x781 = x773;
                  x773 = (x781.+(x780))
                  ()
                }
              }), x24500)
            }
            val x786 = x773;
            if((x786.==(0L))) {
              var x788: Long = 0L;
              x12798._1_=(x12788)
              val x24518 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x12798);
              if((x24518.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x12798, ({ x790: SEntry3_LLL => {
                    val x795 = if(((x790._2).!=(supplier_suppkey))) {
                    (x790._3)
                    } else {
                    0L
                    };
                    val x796 = x788;
                    x788 = (x796.+(x795))
                    ()
                  }
                }), x24518)
              }
              val x801 = x788;
              val x804 = if((x801.!=(0L))) {
              (x770._3)
              } else {
              0L
              };
              val x805 = x768;
              x768 = (x805.+(x804))
            } else {
            }
            ()
          }
        }), x24528)
      }
      val x811 = x768;
      x12738._1_=(supplier_name)
      x12738._2_=((x767.*(x811)))
      val x12739 = x12738._2;
      if((x12739.==(0L))) {
      } else {
        val x19157 = NUMWAITIdx0.get(x12738);
        if((x19157.==(null))) {
          NUMWAIT.unsafeInsert(x12738)
        } else {
          x19157._2 +=(x12739)
          if(((x19157._2).==(0L))) {
            NUMWAIT.delete(x19157)
          } else {
          }
        }
      }
      x12752._1_=(supplier_nationkey)
      val x19168 = NUMWAIT_mSUPPLIER2Idx0.get(x12752);
      val x831 = if((x19168.==(null))) {
      0L
      } else {
      (x19168._2)
      };
      x12757._1_=(supplier_suppkey)
      x12757._2_=(supplier_name)
      x12757._3_=(x831)
      val x12758 = x12757._3;
      if((x12758.==(0L))) {
      } else {
        val x19178 = NUMWAIT_mLINEITEM2Idx0.get(x12757);
        if((x19178.==(null))) {
          NUMWAIT_mLINEITEM2.unsafeInsert(x12757)
        } else {
          x19178._3 +=(x12758)
          if(((x19178._3).==(0L))) {
            NUMWAIT_mLINEITEM2.delete(x19178)
          } else {
          }
        }
      }
      x12771._1_=(supplier_nationkey)
      val x19190 = NUMWAIT_mSUPPLIER2Idx0.get(x12771);
      x12776._2_=(supplier_suppkey)
      val x24595 = NUMWAIT_mSUPPLIER1_L2_1Idx1.sliceRes(x12776);
      if((x24595.isEmpty)) {
      } else {
        val x850 = if((x19190.==(null))) {
        0L
        } else {
        (x19190._2)
        };
        NUMWAIT_mSUPPLIER1_L2_1Idx1.sliceResMapNoUpd(x12776, ({ x852: SEntry3_LLL => {
            x12854._1_=((x852._1))
            x12854._2_=(supplier_suppkey)
            x12854._3_=(supplier_name)
            x12854._4_=((x850.*((x852._3))))
            val x12855 = x12854._4;
            if((x12855.==(0L))) {
            } else {
              val x19207 = NUMWAIT_mLINEITEM7Idx0.get(x12854);
              if((x19207.==(null))) {
                NUMWAIT_mLINEITEM7.unsafeInsert(x12854)
              } else {
                x19207._4 +=(x12855)
                if(((x19207._4).==(0L))) {
                  NUMWAIT_mLINEITEM7.delete(x19207)
                } else {
                }
              }
            }
          
          }
        }), x24595)
      }
    
    }
  
  }
  def onDelSUPPLIER(supplier_suppkey:Long, supplier_name:String, supplier_address:String, supplier_nationkey:Long, supplier_phone:String, supplier_acctbal:Double, supplier_comment:String) {
    {
      x13081._1_=(supplier_nationkey)
      val x19334 = NUMWAIT_mSUPPLIER2Idx0.get(x13081);
      val x883 = if((x19334.==(null))) {
      0L
      } else {
      (x19334._2)
      };
      var x884: Long = 0L;
      x13087._2_=(supplier_suppkey)
      val x24649 = NUMWAIT_mSUPPLIER1Idx1.sliceRes(x13087);
      if((x24649.isEmpty)) {
      } else {
        NUMWAIT_mSUPPLIER1Idx1.sliceResMapNoUpd(x13087, ({ x886: SEntry3_LLL => {
            val x13144 = x886._1;
            var x889: Long = 0L;
            x13147._1_=(x13144)
            val x24621 = NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceRes(x13147);
            if((x24621.isEmpty)) {
            } else {
              NUMWAIT_mSUPPLIER1_L2_1Idx2.sliceResMapNoUpd(x13147, ({ x891: SEntry3_LLL => {
                  val x896 = if(((x891._2).!=(supplier_suppkey))) {
                  (x891._3)
                  } else {
                  0L
                  };
                  val x897 = x889;
                  x889 = (x897.+(x896))
                  ()
                }
              }), x24621)
            }
            val x902 = x889;
            if((x902.==(0L))) {
              var x904: Long = 0L;
              x13154._1_=(x13144)
              val x24639 = NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceRes(x13154);
              if((x24639.isEmpty)) {
              } else {
                NUMWAIT_mSUPPLIER1_E3_1Idx1.sliceResMapNoUpd(x13154, ({ x906: SEntry3_LLL => {
                    val x911 = if(((x906._2).!=(supplier_suppkey))) {
                    (x906._3)
                    } else {
                    0L
                    };
                    val x912 = x904;
                    x904 = (x912.+(x911))
                    ()
                  }
                }), x24639)
              }
              val x917 = x904;
              val x920 = if((x917.!=(0L))) {
              (x886._3)
              } else {
              0L
              };
              val x921 = x884;
              x884 = (x921.+(x920))
            } else {
            }
            ()
          }
        }), x24649)
      }
      val x927 = x884;
      x13093._1_=(supplier_name)
      x13093._2_=((x883.*((x927.unary_-))))
      val x13094 = x13093._2;
      if((x13094.==(0L))) {
      } else {
        val x19386 = NUMWAITIdx0.get(x13093);
        if((x19386.==(null))) {
          NUMWAIT.unsafeInsert(x13093)
        } else {
          x19386._2 +=(x13094)
          if(((x19386._2).==(0L))) {
            NUMWAIT.delete(x19386)
          } else {
          }
        }
      }
      x13107._1_=(supplier_nationkey)
      val x19397 = NUMWAIT_mSUPPLIER2Idx0.get(x13107);
      val x948 = if((x19397.==(null))) {
      0L
      } else {
      (x19397._2)
      };
      x13113._1_=(supplier_suppkey)
      x13113._2_=(supplier_name)
      x13113._3_=((x948.unary_-))
      val x13114 = x13113._3;
      if((x13114.==(0L))) {
      } else {
        val x19408 = NUMWAIT_mLINEITEM2Idx0.get(x13113);
        if((x19408.==(null))) {
          NUMWAIT_mLINEITEM2.unsafeInsert(x13113)
        } else {
          x19408._3 +=(x13114)
          if(((x19408._3).==(0L))) {
            NUMWAIT_mLINEITEM2.delete(x19408)
          } else {
          }
        }
      }
      x13127._1_=(supplier_nationkey)
      val x19420 = NUMWAIT_mSUPPLIER2Idx0.get(x13127);
      x13132._2_=(supplier_suppkey)
      val x24719 = NUMWAIT_mSUPPLIER1_L2_1Idx1.sliceRes(x13132);
      if((x24719.isEmpty)) {
      } else {
        val x968 = if((x19420.==(null))) {
        0L
        } else {
        (x19420._2)
        };
        NUMWAIT_mSUPPLIER1_L2_1Idx1.sliceResMapNoUpd(x13132, ({ x970: SEntry3_LLL => {
            x13213._1_=((x970._1))
            x13213._2_=(supplier_suppkey)
            x13213._3_=(supplier_name)
            x13213._4_=((x968.*(((x970._3).unary_-))))
            val x13214 = x13213._4;
            if((x13214.==(0L))) {
            } else {
              val x19438 = NUMWAIT_mLINEITEM7Idx0.get(x13213);
              if((x19438.==(null))) {
                NUMWAIT_mLINEITEM7.unsafeInsert(x13213)
              } else {
                x19438._4 +=(x13214)
                if(((x19438._4).==(0L))) {
                  NUMWAIT_mLINEITEM7.delete(x19438)
                } else {
                }
              }
            }
          
          }
        }), x24719)
      }
    
    }
  
  }
  def onSystemReady() {
    {
      NUMWAIT_mSUPPLIER2.clear
      x13447._2_=("SAUDI ARABIA")
      val x24743 = NATIONIdx1.sliceRes(x13447);
      if((x24743.isEmpty)) {
      } else {
        NATIONIdx1.sliceResMapNoUpd(x13447, ({ x993: SEntry5_LSLSL => {
            x13456._1_=((x993._1))
            x13456._2_=((x993._5))
            val x13457 = x13456._2;
            if((x13457.==(0L))) {
            } else {
              val x19578 = NUMWAIT_mSUPPLIER2Idx0.get(x13456);
              if((x19578.==(null))) {
                NUMWAIT_mSUPPLIER2.unsafeInsert(x13456)
              } else {
                x19578._2 +=(x13457)
                if(((x19578._2).==(0L))) {
                  NUMWAIT_mSUPPLIER2.delete(x19578)
                } else {
                }
              }
            }
          
          }
        }), x24743)
      }
    
    }
  
  }

  
}


  

  SourceMux({ case TupleEvent(TupleInsert, rn, List(v0:Long,v1:String,v2:Long,v3:String)) => NATION.unsafeInsert(SEntry5_LSLSL(v0,v1,v2,v3, 1L)) }, Seq((list(0), new Adaptor.CSV("NATION","long,string,long,string","\\Q|\\E", "insert"), Split()))).read;
