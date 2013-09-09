// resources/dbtoaster_mac -l SCALA resources/queries/tpch/query18.sql

// run-main example.TPCH18Ref

package examples

import java.io._;
import org.dbtoaster.dbtoasterlib.StreamAdaptor._;
import org.dbtoaster.dbtoasterlib.K3Collection._;
import org.dbtoaster.dbtoasterlib.Source._;
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._;
import org.dbtoaster.dbtoasterlib.ImplicitConversions._;
import org.dbtoaster.dbtoasterlib.StdFunctions._;
import org.dbtoaster.dbtoasterlib.QueryInterface._;
import scala.collection.mutable.Map;
import java.util.Date;
import java.util.GregorianCalendar;
import xml._;
import scala.actors.Actor;
import scala.actors.Actor._;

object TPCH18Ref {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new TPCH18QueryRef()

  def main(args: Array[String]): Unit = {
    var counter = 0
    val logCountIdx = args.indexOf("--log-count")
    val logCount: Int = if (logCountIdx >= 0) args(logCountIdx + 1).toInt else -1
    val logMapSizes = args.contains("--log-map-sizes")

    def printProgress(i: Int) {
      val t = System.nanoTime() / 1000
      val us = t % 1000000
      val s = t / 1000000
      println(i + " tuples processed at " + s + "s+" + us + "us")
      if (logMapSizes) q.printMapSizes
    }

    val timeStart = System.nanoTime()

    val msgRcvr = new DBTMessageReceiver {
      def onTupleProcessed(): Unit = {
        onTupleProc();
        if (logCount > 0) {
          counter += 1
          if (counter % logCount == 0) printProgress(counter)
        }
      }
      def onQueryDone(): Unit = {
        onQDone();
        if (logCount > 0 && counter % logCount != 0) printProgress(counter)
        val runtime = (System.nanoTime() - timeStart) / 1000000000.0
        println("<runtime>" + runtime + "</runtime>")
        //q.printResults()
      }
    }
    val r = new QuerySupervisor(q, msgRcvr)
    if (logCount > 0) printProgress(0)
    r.start
  }
}

class TPCH18QueryRef() extends DBTQuery {
  var supervisor: Actor = null;
  def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;
  val s1 = createInputStreamSource(new FileReader("resources/data/tpch/lineitem.csv"), List(new CSVAdaptor("LINEITEM", List(IntColumn,IntColumn,IntColumn,IntColumn,FloatColumn,FloatColumn,FloatColumn,FloatColumn,StringColumn,StringColumn,DateColumn,DateColumn,DateColumn,StringColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s2 = createInputStreamSource(new FileReader("resources/data/tpch/orders.csv"), List(new CSVAdaptor("ORDERS", List(IntColumn,IntColumn,StringColumn,FloatColumn,DateColumn,StringColumn,StringColumn,IntColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s3 = createInputStreamSource(new FileReader("resources/data/tpch/customer.csv"), List(new CSVAdaptor("CUSTOMER", List(IntColumn,StringColumn,StringColumn,IntColumn,StringColumn,FloatColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));

  val sources = new SourceMultiplexer(this, List(s1,s2,s3));
  var NATION = new K3PersistentCollection[Tuple4[Long,String,Long,String], Long]("NATION", Map(), None) /* out */;
  var REGION = new K3PersistentCollection[Tuple3[Long,String,String], Long]("REGION", Map(), None) /* out */;
  var QUERY18 = new K3PersistentCollection[Tuple5[String,Long,Long,Date,Double], Double]("QUERY18", Map(), Some(Map("1_2_3_4" -> SecondaryIndex[Tuple4[Long,Long,Date,Double],Tuple5[String,Long,Long,Date,Double], Double](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple4(x2,x3,x4,x5) 
  }
  ),"0_1" -> SecondaryIndex[Tuple2[String,Long],Tuple5[String,Long,Long,Date,Double], Double](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple2(x1,x2) 
  }
  )))) /* out */;
  var QUERY18_mORDERS2 = new K3PersistentCollection[Tuple2[String,Long], Long]("QUERY18_mORDERS2", Map(), Some(Map("1" -> SecondaryIndex[(Long),Tuple2[String,Long], Long](x => x match {
    case Tuple2(x1,x2) => (x2) 
  }
  )))) /* out */;
  var QUERY18_mCUSTOMER1 = new K3PersistentCollection[Tuple4[Long,Long,Date,Double], Double]("QUERY18_mCUSTOMER1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple4[Long,Long,Date,Double], Double](x => x match {
    case Tuple4(x1,x2,x3,x4) => (x1) 
  }
  ),"1" -> SecondaryIndex[(Long),Tuple4[Long,Long,Date,Double], Double](x => x match {
    case Tuple4(x1,x2,x3,x4) => (x2) 
  }
  )))) /* out */;
  var QUERY18_mCUSTOMER1_mLINEITEM1 = new K3PersistentCollection[Tuple4[Long,Long,Date,Double], Long]("QUERY18_mCUSTOMER1_mLINEITEM1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple4[Long,Long,Date,Double], Long](x => x match {
    case Tuple4(x1,x2,x3,x4) => (x1) 
  }
  ),"1" -> SecondaryIndex[(Long),Tuple4[Long,Long,Date,Double], Long](x => x match {
    case Tuple4(x1,x2,x3,x4) => (x2) 
  }
  )))) /* out */;
  var QUERY18_mLINEITEM1 = new K3PersistentCollection[Tuple5[Long,String,Long,Date,Double], Double]("QUERY18_mLINEITEM1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple5[Long,String,Long,Date,Double], Double](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => (x1) 
  }
  ),"0_2_3_4" -> SecondaryIndex[Tuple4[Long,Long,Date,Double],Tuple5[Long,String,Long,Date,Double], Double](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple4(x1,x3,x4,x5) 
  }
  ),"1_2" -> SecondaryIndex[Tuple2[String,Long],Tuple5[Long,String,Long,Date,Double], Double](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple2(x2,x3) 
  }
  )))) /* out */;
  var QUERY18_mLINEITEM1_mLINEITEM1 = new K3PersistentCollection[Tuple5[Long,String,Long,Date,Double], Long]("QUERY18_mLINEITEM1_mLINEITEM1", Map(), Some(Map("0" -> SecondaryIndex[(Long),Tuple5[Long,String,Long,Date,Double], Long](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => (x1) 
  }
  ),"0_2_3_4" -> SecondaryIndex[Tuple4[Long,Long,Date,Double],Tuple5[Long,String,Long,Date,Double], Long](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple4(x1,x3,x4,x5) 
  }
  ),"1_2" -> SecondaryIndex[Tuple2[String,Long],Tuple5[Long,String,Long,Date,Double], Long](x => x match {
    case Tuple5(x1,x2,x3,x4,x5) => Tuple2(x2,x3) 
  }
  )))) /* out */;
  var QUERY18_mLINEITEM1_E1_1_L1_1 = new K3PersistentCollection[(Long), Double]("QUERY18_mLINEITEM1_E1_1_L1_1", Map(), None) /* out */;
  def getQUERY18():K3PersistentCollection[Tuple5[String,Long,Long,Date,Double], Double] = {
    QUERY18
  };
  def onInsertLINEITEM(LINEITEM_ORDERKEY: Long,LINEITEM_PARTKEY: Long,LINEITEM_SUPPKEY: Long,LINEITEM_LINENUMBER: Long,LINEITEM_QUANTITY: Double,LINEITEM_EXTENDEDPRICE: Double,LINEITEM_DISCOUNT: Double,LINEITEM_TAX: Double,LINEITEM_RETURNFLAG: String,LINEITEM_LINESTATUS: String,LINEITEM_SHIPDATE: Date,LINEITEM_COMMITDATE: Date,LINEITEM_RECEIPTDATE: Date,LINEITEM_SHIPINSTRUCT: String,LINEITEM_SHIPMODE: String,LINEITEM_COMMENT: String) = {
    (QUERY18_mCUSTOMER1_mLINEITEM1.slice((LINEITEM_ORDERKEY), List(0))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Long]) => {
        val __opt_1:Long = x._1._1; // Long
        val QUERY18_mCUSTOMERCUSTOMER_CUSTKEY:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__1:Long = x._2; // Long
        if((QUERY18_mCUSTOMER1).contains(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mCUSTOMER1).lookup(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + ((__map_ret__1) * (LINEITEM_QUANTITY));
            QUERY18_mCUSTOMER1.updateValue(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (__map_ret__1) * (LINEITEM_QUANTITY);
            QUERY18_mCUSTOMER1.updateValue(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    (QUERY18_mLINEITEM1_mLINEITEM1.slice((LINEITEM_ORDERKEY), List(0))).foreach {
      (x:Tuple2[Tuple5[Long,String,Long,Date,Double], Long]) => {
        val __opt_2:Long = x._1._1; // Long
        val C_NAME:String = x._1._2 /* String => String */;
        val C_CUSTKEY:Long = x._1._3; // Long
        val O_ORDERDATE:Date = x._1._4; // Date
        val O_TOTALPRICE:Double = x._1._5; // Double
        val __map_ret__2:Long = x._2; // Long
        if((QUERY18_mLINEITEM1).contains(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + ((__map_ret__2) * (LINEITEM_QUANTITY));
            QUERY18_mLINEITEM1.updateValue(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (__map_ret__2) * (LINEITEM_QUANTITY);
            QUERY18_mLINEITEM1.updateValue(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((LINEITEM_ORDERKEY))) {        {
        val nv = ((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((LINEITEM_ORDERKEY))) + (LINEITEM_QUANTITY);
        QUERY18_mLINEITEM1_E1_1_L1_1.updateValue((LINEITEM_ORDERKEY), nv)
      }
    }
    else {        {
        val nv = LINEITEM_QUANTITY;
        QUERY18_mLINEITEM1_E1_1_L1_1.updateValue((LINEITEM_ORDERKEY), nv)
      }
    };
    {
      (QUERY18).foreach {
        (x:Tuple2[Tuple5[String,Long,Long,Date,Double], Double]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val C_CUSTKEY:Long = x._1._2; // Long
          val O_ORDERKEY:Long = x._1._3; // Long
          val O_ORDERDATE:Date = x._1._4; // Date
          val O_TOTALPRICE:Double = x._1._5; // Double
          val __prod_ret__5:Double = x._2; // Double
          QUERY18.remove(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) 
        }
      };
      (QUERY18_mLINEITEM1).foreach {
        (x:Tuple2[Tuple5[Long,String,Long,Date,Double], Double]) => {
          val O_ORDERKEY:Long = x._1._1; // Long
          val C_NAME:String = x._1._2 /* String => String */;
          val C_CUSTKEY:Long = x._1._3; // Long
          val O_ORDERDATE:Date = x._1._4; // Date
          val O_TOTALPRICE:Double = x._1._5; // Double
          val __map_ret__3:Double = x._2; // Double
          if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {              {
              val nv = (__map_ret__3) * ((({
                val Tuple2(_L3_QTY,___prod_ret__3) = {
                  val Tuple2(_L3_QTY,___lift_ret__1) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__1:Long = ___lift_ret__1; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__1) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__3:Long = ___prod_ret__3; // Long
                __prod_ret__3
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L));
              QUERY18.updateValue(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18.updateValue(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
            }
          }
        }
      }
    }
  };
  def onDeleteLINEITEM(LINEITEM_ORDERKEY: Long,LINEITEM_PARTKEY: Long,LINEITEM_SUPPKEY: Long,LINEITEM_LINENUMBER: Long,LINEITEM_QUANTITY: Double,LINEITEM_EXTENDEDPRICE: Double,LINEITEM_DISCOUNT: Double,LINEITEM_TAX: Double,LINEITEM_RETURNFLAG: String,LINEITEM_LINESTATUS: String,LINEITEM_SHIPDATE: Date,LINEITEM_COMMITDATE: Date,LINEITEM_RECEIPTDATE: Date,LINEITEM_SHIPINSTRUCT: String,LINEITEM_SHIPMODE: String,LINEITEM_COMMENT: String) = {
    (QUERY18_mCUSTOMER1_mLINEITEM1.slice((LINEITEM_ORDERKEY), List(0))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Long]) => {
        val __opt_3:Long = x._1._1; // Long
        val QUERY18_mCUSTOMERCUSTOMER_CUSTKEY:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__6:Long = x._2; // Long
        if((QUERY18_mCUSTOMER1).contains(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mCUSTOMER1).lookup(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + (((__map_ret__6) * (-1L)) * (LINEITEM_QUANTITY));
            QUERY18_mCUSTOMER1.updateValue(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = ((__map_ret__6) * (-1L)) * (LINEITEM_QUANTITY);
            QUERY18_mCUSTOMER1.updateValue(Tuple4(LINEITEM_ORDERKEY,QUERY18_mCUSTOMERCUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    (QUERY18_mLINEITEM1_mLINEITEM1.slice((LINEITEM_ORDERKEY), List(0))).foreach {
      (x:Tuple2[Tuple5[Long,String,Long,Date,Double], Long]) => {
        val __opt_4:Long = x._1._1; // Long
        val C_NAME:String = x._1._2 /* String => String */;
        val C_CUSTKEY:Long = x._1._3; // Long
        val O_ORDERDATE:Date = x._1._4; // Date
        val O_TOTALPRICE:Double = x._1._5; // Double
        val __map_ret__7:Long = x._2; // Long
        if((QUERY18_mLINEITEM1).contains(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + (((__map_ret__7) * (-1L)) * (LINEITEM_QUANTITY));
            QUERY18_mLINEITEM1.updateValue(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = ((__map_ret__7) * (-1L)) * (LINEITEM_QUANTITY);
            QUERY18_mLINEITEM1.updateValue(Tuple5(LINEITEM_ORDERKEY,C_NAME,C_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((LINEITEM_ORDERKEY))) {        {
        val nv = ((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((LINEITEM_ORDERKEY))) + ((-1L) * (LINEITEM_QUANTITY));
        QUERY18_mLINEITEM1_E1_1_L1_1.updateValue((LINEITEM_ORDERKEY), nv)
      }
    }
    else {        {
        val nv = (-1L) * (LINEITEM_QUANTITY);
        QUERY18_mLINEITEM1_E1_1_L1_1.updateValue((LINEITEM_ORDERKEY), nv)
      }
    };
    {
      (QUERY18).foreach {
        (x:Tuple2[Tuple5[String,Long,Long,Date,Double], Double]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val C_CUSTKEY:Long = x._1._2; // Long
          val O_ORDERKEY:Long = x._1._3; // Long
          val O_ORDERDATE:Date = x._1._4; // Date
          val O_TOTALPRICE:Double = x._1._5; // Double
          val __prod_ret__13:Double = x._2; // Double
          QUERY18.remove(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) 
        }
      };
      (QUERY18_mLINEITEM1).foreach {
        (x:Tuple2[Tuple5[Long,String,Long,Date,Double], Double]) => {
          val O_ORDERKEY:Long = x._1._1; // Long
          val C_NAME:String = x._1._2 /* String => String */;
          val C_CUSTKEY:Long = x._1._3; // Long
          val O_ORDERDATE:Date = x._1._4; // Date
          val O_TOTALPRICE:Double = x._1._5; // Double
          val __map_ret__8:Double = x._2; // Double
          if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {              {
              val nv = (__map_ret__8) * ((({
                val Tuple2(_L3_QTY,___prod_ret__11) = {
                  val Tuple2(_L3_QTY,___lift_ret__2) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__2:Long = ___lift_ret__2; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__2) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__11:Long = ___prod_ret__11; // Long
                __prod_ret__11
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L));
              QUERY18.updateValue(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18.updateValue(Tuple5(C_NAME,C_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
            }
          }
        }
      }
    }
  };
  def onInsertORDERS(ORDERS_ORDERKEY: Long,ORDERS_CUSTKEY: Long,ORDERS_ORDERSTATUS: String,ORDERS_TOTALPRICE: Double,ORDERS_ORDERDATE: Date,ORDERS_ORDERPRIORITY: String,ORDERS_CLERK: String,ORDERS_SHIPPRIORITY: Long,ORDERS_COMMENT: String) = {
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_6:Long = x._1._2; // Long
          val __map_ret__13:Long = x._2; // Long
          if((QUERY18).contains(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val ___cse_1:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_1:Double = ___cse_1; // Double
              {
                val nv = ((QUERY18).lookup(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (((__map_ret__13) * ((({
                  val Tuple2(_L3_QTY,___prod_ret__14) = {
                    val _L3_QTY:Double = __cse_1;
                    val L3_QTY:Double = _L3_QTY; // Double
                    Tuple2[Double,Boolean]((L3_QTY),((100L) < (L3_QTY)))
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __prod_ret__14:Long = (if(___prod_ret__14) 1L else 0L) /* Boolean => Long */;
                  __prod_ret__14
                }
                ) * ((__cse_1) != (0L))) != (0L))) * (__cse_1));
                QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
          else {              {
              val ___cse_1:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_1:Double = ___cse_1; // Double
              {
                val nv = ((__map_ret__13) * ((({
                  val Tuple2(_L3_QTY,___prod_ret__14) = {
                    val _L3_QTY:Double = __cse_1;
                    val L3_QTY:Double = _L3_QTY; // Double
                    Tuple2[Double,Boolean]((L3_QTY),((100L) < (L3_QTY)))
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __prod_ret__14:Long = (if(___prod_ret__14) 1L else 0L) /* Boolean => Long */;
                  __prod_ret__14
                }
                ) * ((__cse_1) != (0L))) != (0L))) * (__cse_1);
                QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
        }
      }
    }
    else {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_5:Long = x._1._2; // Long
          val __map_ret__13:Long = x._2; // Long
          if((QUERY18).contains(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val nv = (QUERY18).lookup(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
              QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
        }
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      if((QUERY18_mCUSTOMER1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {          {
          val ___cse_2:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
          val __cse_2:Double = ___cse_2; // Double
          {
            val nv = ((QUERY18_mCUSTOMER1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (__cse_2);
            QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
      else {          {
          val ___cse_2:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
          val __cse_2:Double = ___cse_2; // Double
          {
            val nv = __cse_2;
            QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
    }
    else {
      if((QUERY18_mCUSTOMER1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {          {
          val nv = (QUERY18_mCUSTOMER1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
          QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
        }
      }
      else {          {
          val nv = 0.0;
          QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
        }
      }
    };
    if((QUERY18_mCUSTOMER1_mLINEITEM1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {        {
        val nv = ((QUERY18_mCUSTOMER1_mLINEITEM1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (1L);
        QUERY18_mCUSTOMER1_mLINEITEM1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
      }
    }
    else {        {
        val nv = 1L;
        QUERY18_mCUSTOMER1_mLINEITEM1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_8:Long = x._1._2; // Long
          val __map_ret__16:Long = x._2; // Long
          if((QUERY18_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val ___cse_3:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_3:Double = ___cse_3; // Double
              {
                val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + ((__map_ret__16) * (__cse_3));
                QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
          else {              {
              val ___cse_3:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_3:Double = ___cse_3; // Double
              {
                val nv = (__map_ret__16) * (__cse_3);
                QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
        }
      }
    }
    else {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_7:Long = x._1._2; // Long
          val __map_ret__16:Long = x._2; // Long
          if((QUERY18_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val nv = (QUERY18_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
              QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
        }
      }
    };
    (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple2[String,Long], Long]) => {
        val C_NAME:String = x._1._1 /* String => String */;
        val __opt_9:Long = x._1._2; // Long
        val __map_ret__18:Long = x._2; // Long
        if((QUERY18_mLINEITEM1_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (__map_ret__18);
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = __map_ret__18;
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
    }
  };
  def onDeleteORDERS(ORDERS_ORDERKEY: Long,ORDERS_CUSTKEY: Long,ORDERS_ORDERSTATUS: String,ORDERS_TOTALPRICE: Double,ORDERS_ORDERDATE: Date,ORDERS_ORDERPRIORITY: String,ORDERS_CLERK: String,ORDERS_SHIPPRIORITY: Long,ORDERS_COMMENT: String) = {
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_11:Long = x._1._2; // Long
          val __map_ret__21:Long = x._2; // Long
          if((QUERY18).contains(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val ___cse_4:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_4:Double = ___cse_4; // Double
              {
                val nv = ((QUERY18).lookup(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + ((((__map_ret__21) * ((({
                  val Tuple2(_L3_QTY,___prod_ret__19) = {
                    val _L3_QTY:Double = __cse_4;
                    val L3_QTY:Double = _L3_QTY; // Double
                    Tuple2[Double,Boolean]((L3_QTY),((100L) < (L3_QTY)))
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __prod_ret__19:Long = (if(___prod_ret__19) 1L else 0L) /* Boolean => Long */;
                  __prod_ret__19
                }
                ) * ((__cse_4) != (0L))) != (0L))) * (__cse_4)) * (-1L));
                QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
          else {              {
              val ___cse_4:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_4:Double = ___cse_4; // Double
              {
                val nv = (((__map_ret__21) * ((({
                  val Tuple2(_L3_QTY,___prod_ret__19) = {
                    val _L3_QTY:Double = __cse_4;
                    val L3_QTY:Double = _L3_QTY; // Double
                    Tuple2[Double,Boolean]((L3_QTY),((100L) < (L3_QTY)))
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __prod_ret__19:Long = (if(___prod_ret__19) 1L else 0L) /* Boolean => Long */;
                  __prod_ret__19
                }
                ) * ((__cse_4) != (0L))) != (0L))) * (__cse_4)) * (-1L);
                QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
        }
      }
    }
    else {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_10:Long = x._1._2; // Long
          val __map_ret__21:Long = x._2; // Long
          if((QUERY18).contains(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val nv = (QUERY18).lookup(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
              QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18.updateValue(Tuple5(C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
        }
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      if((QUERY18_mCUSTOMER1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {          {
          val ___cse_5:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
          val __cse_5:Double = ___cse_5; // Double
          {
            val nv = ((QUERY18_mCUSTOMER1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + ((__cse_5) * (-1L));
            QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
      else {          {
          val ___cse_5:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
          val __cse_5:Double = ___cse_5; // Double
          {
            val nv = (__cse_5) * (-1L);
            QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
    }
    else {
      if((QUERY18_mCUSTOMER1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {          {
          val nv = (QUERY18_mCUSTOMER1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
          QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
        }
      }
      else {          {
          val nv = 0.0;
          QUERY18_mCUSTOMER1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
        }
      }
    };
    if((QUERY18_mCUSTOMER1_mLINEITEM1).contains(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {        {
        val nv = ((QUERY18_mCUSTOMER1_mLINEITEM1).lookup(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (-1L);
        QUERY18_mCUSTOMER1_mLINEITEM1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
      }
    }
    else {        {
        val nv = -1L;
        QUERY18_mCUSTOMER1_mLINEITEM1.updateValue(Tuple4(ORDERS_ORDERKEY,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
      }
    };
    if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((ORDERS_ORDERKEY))) {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_13:Long = x._1._2; // Long
          val __map_ret__24:Long = x._2; // Long
          if((QUERY18_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val ___cse_6:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_6:Double = ___cse_6; // Double
              {
                val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + (((__map_ret__24) * (__cse_6)) * (-1L));
                QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
          else {              {
              val ___cse_6:Double = (QUERY18_mLINEITEM1_E1_1_L1_1).lookup((ORDERS_ORDERKEY));
              val __cse_6:Double = ___cse_6; // Double
              {
                val nv = ((__map_ret__24) * (__cse_6)) * (-1L);
                QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
              }
            }
          }
        }
      }
    }
    else {
      (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
        (x:Tuple2[Tuple2[String,Long], Long]) => {
          val C_NAME:String = x._1._1 /* String => String */;
          val __opt_12:Long = x._1._2; // Long
          val __map_ret__24:Long = x._2; // Long
          if((QUERY18_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {              {
              val nv = (QUERY18_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE));
              QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
          else {              {
              val nv = 0.0;
              QUERY18_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
            }
          }
        }
      }
    };
    (QUERY18_mORDERS2.slice((ORDERS_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple2[String,Long], Long]) => {
        val C_NAME:String = x._1._1 /* String => String */;
        val __opt_14:Long = x._1._2; // Long
        val __map_ret__26:Long = x._2; // Long
        if((QUERY18_mLINEITEM1_mLINEITEM1).contains(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1_mLINEITEM1).lookup(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE))) + ((__map_ret__26) * (-1L));
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (__map_ret__26) * (-1L);
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(ORDERS_ORDERKEY,C_NAME,ORDERS_CUSTKEY,ORDERS_ORDERDATE,ORDERS_TOTALPRICE), nv)
          }
        }
      }
    }
  };
  def onInsertCUSTOMER(CUSTOMER_CUSTKEY: Long,CUSTOMER_NAME: String,CUSTOMER_ADDRESS: String,CUSTOMER_NATIONKEY: Long,CUSTOMER_PHONE: String,CUSTOMER_ACCTBAL: Double,CUSTOMER_MKTSEGMENT: String,CUSTOMER_COMMENT: String) = {
    (QUERY18_mCUSTOMER1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Double]) => {
        val O_ORDERKEY:Long = x._1._1; // Long
        val __opt_15:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__27:Double = x._2; // Double
        if((QUERY18).contains(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18).lookup(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))) + (if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
              (__map_ret__27) * ((({
                val Tuple2(_L3_QTY,___prod_ret__28) = {
                  val Tuple2(_L3_QTY,___lift_ret__5) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__5:Long = ___lift_ret__5; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__5) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__28:Long = ___prod_ret__28; // Long
                __prod_ret__28
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L)) 
            }
            else {
              0.0 
            }
            );
            QUERY18.updateValue(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
              (__map_ret__27) * ((({
                val Tuple2(_L3_QTY,___prod_ret__28) = {
                  val Tuple2(_L3_QTY,___lift_ret__5) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__5:Long = ___lift_ret__5; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__5) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__28:Long = ___prod_ret__28; // Long
                __prod_ret__28
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L)) 
            }
            else {
              0.0 
            };
            QUERY18.updateValue(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    if((QUERY18_mORDERS2).contains(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY))) {        {
        val nv = ((QUERY18_mORDERS2).lookup(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY))) + (1L);
        QUERY18_mORDERS2.updateValue(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY), nv)
      }
    }
    else {        {
        val nv = 1L;
        QUERY18_mORDERS2.updateValue(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY), nv)
      }
    };
    (QUERY18_mCUSTOMER1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Double]) => {
        val O_ORDERKEY:Long = x._1._1; // Long
        val __opt_16:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__30:Double = x._2; // Double
        if((QUERY18_mLINEITEM1).contains(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + (__map_ret__30);
            QUERY18_mLINEITEM1.updateValue(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = __map_ret__30;
            QUERY18_mLINEITEM1.updateValue(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    (QUERY18_mCUSTOMER1_mLINEITEM1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Long]) => {
        val QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY:Long = x._1._1; // Long
        val __opt_17:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__31:Long = x._2; // Long
        if((QUERY18_mLINEITEM1_mLINEITEM1).contains(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1_mLINEITEM1).lookup(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + (__map_ret__31);
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = __map_ret__31;
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    }
  };
  def onDeleteCUSTOMER(CUSTOMER_CUSTKEY: Long,CUSTOMER_NAME: String,CUSTOMER_ADDRESS: String,CUSTOMER_NATIONKEY: Long,CUSTOMER_PHONE: String,CUSTOMER_ACCTBAL: Double,CUSTOMER_MKTSEGMENT: String,CUSTOMER_COMMENT: String) = {
    (QUERY18_mCUSTOMER1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Double]) => {
        val O_ORDERKEY:Long = x._1._1; // Long
        val __opt_18:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__32:Double = x._2; // Double
        if((QUERY18).contains(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18).lookup(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))) + ((if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
              (__map_ret__32) * ((({
                val Tuple2(_L3_QTY,___prod_ret__31) = {
                  val Tuple2(_L3_QTY,___lift_ret__6) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__6:Long = ___lift_ret__6; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__6) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__31:Long = ___prod_ret__31; // Long
                __prod_ret__31
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L)) 
            }
            else {
              0.0 
            }
            ) * (-1L));
            QUERY18.updateValue(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
              (__map_ret__32) * ((({
                val Tuple2(_L3_QTY,___prod_ret__31) = {
                  val Tuple2(_L3_QTY,___lift_ret__6) = if((QUERY18_mLINEITEM1_E1_1_L1_1).contains((O_ORDERKEY))) {
                    Tuple2[Double,Long](((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))),(1L)) 
                  }
                  else {
                    Tuple2[Double,Long]((0.0),(1L)) 
                  };
                  val L3_QTY:Double = _L3_QTY; // Double
                  val __lift_ret__6:Long = ___lift_ret__6; // Long
                  Tuple2[Double,Long]((L3_QTY),((__lift_ret__6) * ((100L) < (L3_QTY))))
                };
                val L3_QTY:Double = _L3_QTY; // Double
                val __prod_ret__31:Long = ___prod_ret__31; // Long
                __prod_ret__31
              }
              ) * (((QUERY18_mLINEITEM1_E1_1_L1_1).lookup((O_ORDERKEY))) != (0L))) != (0L)) 
            }
            else {
              0.0 
            }
            ) * (-1L);
            QUERY18.updateValue(Tuple5(CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    if((QUERY18_mORDERS2).contains(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY))) {        {
        val nv = ((QUERY18_mORDERS2).lookup(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY))) + (-1L);
        QUERY18_mORDERS2.updateValue(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY), nv)
      }
    }
    else {        {
        val nv = -1L;
        QUERY18_mORDERS2.updateValue(Tuple2(CUSTOMER_NAME,CUSTOMER_CUSTKEY), nv)
      }
    };
    (QUERY18_mCUSTOMER1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Double]) => {
        val O_ORDERKEY:Long = x._1._1; // Long
        val __opt_19:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__35:Double = x._2; // Double
        if((QUERY18_mLINEITEM1).contains(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1).lookup(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + ((__map_ret__35) * (-1L));
            QUERY18_mLINEITEM1.updateValue(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (__map_ret__35) * (-1L);
            QUERY18_mLINEITEM1.updateValue(Tuple5(O_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    };
    (QUERY18_mCUSTOMER1_mLINEITEM1.slice((CUSTOMER_CUSTKEY), List(1))).foreach {
      (x:Tuple2[Tuple4[Long,Long,Date,Double], Long]) => {
        val QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY:Long = x._1._1; // Long
        val __opt_20:Long = x._1._2; // Long
        val O_ORDERDATE:Date = x._1._3; // Date
        val O_TOTALPRICE:Double = x._1._4; // Double
        val __map_ret__36:Long = x._2; // Long
        if((QUERY18_mLINEITEM1_mLINEITEM1).contains(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) {            {
            val nv = ((QUERY18_mLINEITEM1_mLINEITEM1).lookup(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE))) + ((__map_ret__36) * (-1L));
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
        else {            {
            val nv = (__map_ret__36) * (-1L);
            QUERY18_mLINEITEM1_mLINEITEM1.updateValue(Tuple5(QUERY18_mLINEITEM1_mLINEITEMLINEITEM_ORDERKEY,CUSTOMER_NAME,CUSTOMER_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), nv)
          }
        }
      }
    }
  };
  def onSystemInitialized() = {
  };
  def fillTables(): Unit = {;
  }
  def dispatcher(event: DBTEvent): Unit = {
    event match {
      case StreamEvent(InsertTuple, o, "LINEITEM", (var_LINEITEM_ORDERKEY: Long)::(var_LINEITEM_PARTKEY: Long)::(var_LINEITEM_SUPPKEY: Long)::(var_LINEITEM_LINENUMBER: Long)::(var_LINEITEM_QUANTITY: Double)::(var_LINEITEM_EXTENDEDPRICE: Double)::(var_LINEITEM_DISCOUNT: Double)::(var_LINEITEM_TAX: Double)::(var_LINEITEM_RETURNFLAG: String)::(var_LINEITEM_LINESTATUS: String)::(var_LINEITEM_SHIPDATE: Date)::(var_LINEITEM_COMMITDATE: Date)::(var_LINEITEM_RECEIPTDATE: Date)::(var_LINEITEM_SHIPINSTRUCT: String)::(var_LINEITEM_SHIPMODE: String)::(var_LINEITEM_COMMENT: String)::Nil) => onInsertLINEITEM(var_LINEITEM_ORDERKEY,var_LINEITEM_PARTKEY,var_LINEITEM_SUPPKEY,var_LINEITEM_LINENUMBER,var_LINEITEM_QUANTITY,var_LINEITEM_EXTENDEDPRICE,var_LINEITEM_DISCOUNT,var_LINEITEM_TAX,var_LINEITEM_RETURNFLAG,var_LINEITEM_LINESTATUS,var_LINEITEM_SHIPDATE,var_LINEITEM_COMMITDATE,var_LINEITEM_RECEIPTDATE,var_LINEITEM_SHIPINSTRUCT,var_LINEITEM_SHIPMODE,var_LINEITEM_COMMENT);
      case StreamEvent(DeleteTuple, o, "LINEITEM", (var_LINEITEM_ORDERKEY: Long)::(var_LINEITEM_PARTKEY: Long)::(var_LINEITEM_SUPPKEY: Long)::(var_LINEITEM_LINENUMBER: Long)::(var_LINEITEM_QUANTITY: Double)::(var_LINEITEM_EXTENDEDPRICE: Double)::(var_LINEITEM_DISCOUNT: Double)::(var_LINEITEM_TAX: Double)::(var_LINEITEM_RETURNFLAG: String)::(var_LINEITEM_LINESTATUS: String)::(var_LINEITEM_SHIPDATE: Date)::(var_LINEITEM_COMMITDATE: Date)::(var_LINEITEM_RECEIPTDATE: Date)::(var_LINEITEM_SHIPINSTRUCT: String)::(var_LINEITEM_SHIPMODE: String)::(var_LINEITEM_COMMENT: String)::Nil) => onDeleteLINEITEM(var_LINEITEM_ORDERKEY,var_LINEITEM_PARTKEY,var_LINEITEM_SUPPKEY,var_LINEITEM_LINENUMBER,var_LINEITEM_QUANTITY,var_LINEITEM_EXTENDEDPRICE,var_LINEITEM_DISCOUNT,var_LINEITEM_TAX,var_LINEITEM_RETURNFLAG,var_LINEITEM_LINESTATUS,var_LINEITEM_SHIPDATE,var_LINEITEM_COMMITDATE,var_LINEITEM_RECEIPTDATE,var_LINEITEM_SHIPINSTRUCT,var_LINEITEM_SHIPMODE,var_LINEITEM_COMMENT);
      case StreamEvent(InsertTuple, o, "ORDERS", (var_ORDERS_ORDERKEY: Long)::(var_ORDERS_CUSTKEY: Long)::(var_ORDERS_ORDERSTATUS: String)::(var_ORDERS_TOTALPRICE: Double)::(var_ORDERS_ORDERDATE: Date)::(var_ORDERS_ORDERPRIORITY: String)::(var_ORDERS_CLERK: String)::(var_ORDERS_SHIPPRIORITY: Long)::(var_ORDERS_COMMENT: String)::Nil) => onInsertORDERS(var_ORDERS_ORDERKEY,var_ORDERS_CUSTKEY,var_ORDERS_ORDERSTATUS,var_ORDERS_TOTALPRICE,var_ORDERS_ORDERDATE,var_ORDERS_ORDERPRIORITY,var_ORDERS_CLERK,var_ORDERS_SHIPPRIORITY,var_ORDERS_COMMENT);
      case StreamEvent(DeleteTuple, o, "ORDERS", (var_ORDERS_ORDERKEY: Long)::(var_ORDERS_CUSTKEY: Long)::(var_ORDERS_ORDERSTATUS: String)::(var_ORDERS_TOTALPRICE: Double)::(var_ORDERS_ORDERDATE: Date)::(var_ORDERS_ORDERPRIORITY: String)::(var_ORDERS_CLERK: String)::(var_ORDERS_SHIPPRIORITY: Long)::(var_ORDERS_COMMENT: String)::Nil) => onDeleteORDERS(var_ORDERS_ORDERKEY,var_ORDERS_CUSTKEY,var_ORDERS_ORDERSTATUS,var_ORDERS_TOTALPRICE,var_ORDERS_ORDERDATE,var_ORDERS_ORDERPRIORITY,var_ORDERS_CLERK,var_ORDERS_SHIPPRIORITY,var_ORDERS_COMMENT);
      case StreamEvent(InsertTuple, o, "CUSTOMER", (var_CUSTOMER_CUSTKEY: Long)::(var_CUSTOMER_NAME: String)::(var_CUSTOMER_ADDRESS: String)::(var_CUSTOMER_NATIONKEY: Long)::(var_CUSTOMER_PHONE: String)::(var_CUSTOMER_ACCTBAL: Double)::(var_CUSTOMER_MKTSEGMENT: String)::(var_CUSTOMER_COMMENT: String)::Nil) => onInsertCUSTOMER(var_CUSTOMER_CUSTKEY,var_CUSTOMER_NAME,var_CUSTOMER_ADDRESS,var_CUSTOMER_NATIONKEY,var_CUSTOMER_PHONE,var_CUSTOMER_ACCTBAL,var_CUSTOMER_MKTSEGMENT,var_CUSTOMER_COMMENT);
      case StreamEvent(DeleteTuple, o, "CUSTOMER", (var_CUSTOMER_CUSTKEY: Long)::(var_CUSTOMER_NAME: String)::(var_CUSTOMER_ADDRESS: String)::(var_CUSTOMER_NATIONKEY: Long)::(var_CUSTOMER_PHONE: String)::(var_CUSTOMER_ACCTBAL: Double)::(var_CUSTOMER_MKTSEGMENT: String)::(var_CUSTOMER_COMMENT: String)::Nil) => onDeleteCUSTOMER(var_CUSTOMER_CUSTKEY,var_CUSTOMER_NAME,var_CUSTOMER_ADDRESS,var_CUSTOMER_NATIONKEY,var_CUSTOMER_PHONE,var_CUSTOMER_ACCTBAL,var_CUSTOMER_MKTSEGMENT,var_CUSTOMER_COMMENT);
      case StreamEvent(SystemInitialized, o, "", Nil) => onSystemInitialized();
      case EndOfStream => ();
      case _ => throw DBTFatalError("Event could not be dispatched: " + event)
    }
    /*
    val rt = Runtime.getRuntime
    val usedMB = (rt.totalMemory() - rt.freeMemory()) / 1024.0 / 1024.0;
    println("Mem: %.2f".format(usedMB))
    */

    supervisor ! DBTTupleProcessed;
  }
  def act(): Unit ={
    fillTables();
    onSystemInitialized();
    sources.start;
    while(true) {
      receive {
        case EndOfStream => {
          //printResults
          println(ddbt.lib.K3Helper.toStr(getQUERY18().elems.toMap))
          supervisor ! DBTDone;
          exit();
        }
        case e: DBTEvent => dispatcher(e) 
      }
    }
  }
  def printResults(): Unit = {
    val pp = new PrettyPrinter(8000, 2);
    println(pp.format(<QUERY18>{
      getQUERY18().toXML() 
    }
    </QUERY18>));
  }
  def printMapSizes() = {
    NATION.printSize;
    REGION.printSize;
    QUERY18.printSize;
    QUERY18_mORDERS2.printSize;
    QUERY18_mCUSTOMER1.printSize;
    QUERY18_mCUSTOMER1_mLINEITEM1.printSize;
    QUERY18_mLINEITEM1.printSize;
    QUERY18_mLINEITEM1_mLINEITEM1.printSize;
    QUERY18_mLINEITEM1_E1_1_L1_1.printSize;
  }
}
