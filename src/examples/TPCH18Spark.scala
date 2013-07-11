package examples
import ddbt.lib.{K3Map,KSMap,KDMap}

// run-main example.TPCH18

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

object TPCH18Spark {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new TPCH18QuerySpark()

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

class TPCH18QuerySpark() extends DBTQuery {
  var supervisor: Actor = null;
  def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;
  val s1 = createInputStreamSource(new FileReader("resources/data/tpch/lineitem.csv"), List(new CSVAdaptor("LINEITEM", List(IntColumn,IntColumn,IntColumn,IntColumn,FloatColumn,FloatColumn,FloatColumn,FloatColumn,StringColumn,StringColumn,DateColumn,DateColumn,DateColumn,StringColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s2 = createInputStreamSource(new FileReader("resources/data/tpch/orders.csv"), List(new CSVAdaptor("ORDERS", List(IntColumn,IntColumn,StringColumn,FloatColumn,DateColumn,StringColumn,StringColumn,IntColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s3 = createInputStreamSource(new FileReader("resources/data/tpch/customer.csv"), List(new CSVAdaptor("CUSTOMER", List(IntColumn,StringColumn,StringColumn,IntColumn,StringColumn,FloatColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));

  val sources = new SourceMultiplexer(this, List(s1,s2,s3));
  
  // ---------------------------------------------------------------------------

  import spark.SparkContext
  val sc = new SparkContext("local[8]", "Simple Job", "$YOUR_SPARK_HOME",
             List("target/scala-2.10/distributeddbtoaster_2.10-0.1.jar")) // Match SBT name/version
  val N = 64

  val QUERY18 = KDMap.make[(String,Long,Long,Date,Double), Double](sc,N,0.0)
  val mORDERS2 = KDMap.make[(String,Long), Long](sc,N,0L,List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = KDMap.make[(Long,Long,Date,Double), Double](sc,N,0.0,List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = KDMap.make[(Long,Long,Date,Double), Long](sc,N,0L,List(
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  ))
  val mLINEITEM1 = KDMap.make[(Long,String,Long,Date,Double), Double](sc,N,0.0)
  val mLINEITEM1_mLINEITEM1 = KDMap.make[(Long,String,Long,Date,Double), Long](sc,N,0L,List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = KDMap.make[Long,Double](sc,N,0.0)

  def getQUERY18() = QUERY18

/*
  type Rs[K,V] = scala.collection.mutable.HashMap[K,V]
  type In[K,V] = (Any=>Boolean,KSMap[K,V])

  import spark.RDD

  def parOp[K,V,K2,V2](rdd:RDD[In[K,V]], rdd2:RDD[In[K2,V2]], sl:(Int,Any), f:(K,V)=>(K2,V2),add:Boolean=true) = {
    val tmp = rdd.aggregate(new scala.collection.mutable.HashMap[K2,V2]())(
      (r:Rs[K2,V2],x:(Any=>Boolean,KSMap[K,V])) => { (if (sl==null || sl._1<0) x._2 else x._2.slice(sl._1,sl._2)).foreach { case (k,v) => r + f(k,v) }; r },
      (r1:Rs[K2,V2],r2:Rs[K2,V2]) => r1 ++ r2
    )
    rdd2.map { case (h,m0) => var m=m0; tmp.foreach{ case (k,v) => if (h(k)) m=if (add) m.add(k,v) else m.set(k,v) }; (h,m) }
  }
*/
  var ti:Long = System.nanoTime()
  var tc:Long = 0
  def tick {
    val n:Long = 4
    if ((tc % n)==0) {
        val runtime = (System.nanoTime() - ti) / 1000000000.0
        if (runtime>0) println("Tup/sec: "+(n/runtime));
        ti=System.nanoTime()
    }
    tc=tc+1
  }

  def mapL3_QTY() = { val mL3_QTY = new KSMap[Long,Long](0L)
    mLINEITEM1_E1_1_L1_1.collect{ case(k,v) => mL3_QTY.add(k, ((100L < v) * (v != 0L)) != 0L) }
    mL3_QTY
  }

  // ---------------------------------------------------------------------------
  def onInsertLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1.parOp(mCUSTOMER1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY))
    mLINEITEM1.parOp(mLINEITEM1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,String,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4,k._5), v * L_QUANTITY) )
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.clear()
    val mL3_QTY = mapL3_QTY()
    QUERY18.parOp(mLINEITEM1, null, (k:(Long,String,Long,Date,Double),v:Double) => {
      val ORDERKEY:Long = k._1; ((k._2,k._3,ORDERKEY,k._4,k._5), v * mL3_QTY.get(ORDERKEY))
    },false)
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1.parOp(mCUSTOMER1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4), -v * L_QUANTITY))
    mLINEITEM1.parOp(mLINEITEM1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,String,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4,k._5), -v * L_QUANTITY) )
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, -L_QUANTITY)
    QUERY18.clear()
    val mL3_QTY = new KSMap[Long,Long](0L)
    mLINEITEM1_E1_1_L1_1.collect{ case(k,v) => mL3_QTY.add(k, ((100L < v) * (v != 0L)) != 0L) }
    QUERY18.parOp(mLINEITEM1, null, (k:(Long,String,Long,Date,Double),v:Double) => {
      val ORDERKEY:Long = k._1; ((k._2,k._3,ORDERKEY,k._4,k._5), v * mL3_QTY.get(ORDERKEY))
    },false)
    tick
  }
  // ---------------------------------------------------------------------------
  def onInsertORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
/*
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY);
    if (L3_QTY!=0.0) {
      QUERY18.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long), v:Long) => {
        val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
        ((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
      });
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
*/
    //if (L3_QTY!=0.0) mLINEITEM1.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v * L3_QTY))
    //mLINEITEM1_mLINEITEM1.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v))
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
/*
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY);
    if (L3_QTY!=0.0) {
      QUERY18.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long), v:Long) => {
        val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
        ((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), -nv)
      });
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
*/
    /*
    var o_ORDERKEY = O_ORDERKEY+0
    var o_CUSTKEY = O_CUSTKEY+0
    var o_ORDERDATE = O_ORDERDATE
    var o_TOTALPRICE = O_TOTALPRICE + 0
    */
    //if (L3_QTY!=0.0) mLINEITEM1.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v * L3_QTY))
    //mLINEITEM1_mLINEITEM1.parOp(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v))
    tick
  }
  // ---------------------------------------------------------------------------
  def onInsertCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
/*
    val mL3_QTY = mapL3_QTY()
    QUERY18.parOp(mCUSTOMER1, (0,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Double) => {
      val ORDERKEY:Long = k._1;
      val nv = v * mL3_QTY.get(ORDERKEY);
      ((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
    })
    mORDERS2.add((C_NAME,C_CUSTKEY), 1L)
*/
    /*
    var c_NAME = C_NAME+""       // force Scala compiler to use a new symbol such that it de-alias with
    var c_CUSTKEY = C_CUSTKEY+0  // function arguments and thereby produces clean closures
    mLINEITEM1.parOp(mCUSTOMER1,(0,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Double) => ((k._1,c_NAME,c_CUSTKEY,k._3,k._4), v))
    mLINEITEM1_mLINEITEM1.parOp(mCUSTOMER1_mLINEITEM1,(1,C_CUSTKEY),(k:(Long,Long,Date,Double),v:Long) => ((k._1,c_NAME,c_CUSTKEY,k._3,k._4), v))
    */
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
/*
    val mL3_QTY = mapL3_QTY()
    QUERY18.parOp(mCUSTOMER1, (0,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Double) => {
      val ORDERKEY:Long = k._1;
      val nv = v * mL3_QTY.get(ORDERKEY);
      ((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), -nv)
    })
    mORDERS2.add((C_NAME,C_CUSTKEY), -1L)
*/
    /*
    var c_NAME = C_NAME+""       // force Scala compiler to use a new symbol such that it de-alias with
    var c_CUSTKEY = C_CUSTKEY+0  // function arguments and thereby produces clean closures
    mLINEITEM1.parOp(mCUSTOMER1,(0,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Double) => ((k._1,c_NAME,c_CUSTKEY,k._3,k._4), -v))
    mLINEITEM1_mLINEITEM1.parOp(mCUSTOMER1_mLINEITEM1,(1,C_CUSTKEY),(k:(Long,Long,Date,Double),v:Long) => ((k._1,c_NAME,c_CUSTKEY,k._3,k._4), -v))
    */
    tick
  }
  // ---------------------------------------------------------------------------

  def onSystemInitialized() = {};
  def fillTables(): Unit = {}
  def dispatcher(event: DBTEvent): Unit = {
    event match {
      case StreamEvent(InsertTuple, o, "LINEITEM", (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onInsertLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
      case StreamEvent(DeleteTuple, o, "LINEITEM", (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onDeleteLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
      case StreamEvent(InsertTuple, o, "ORDERS", (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onInsertORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
      case StreamEvent(DeleteTuple, o, "ORDERS", (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onDeleteORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
      case StreamEvent(InsertTuple, o, "CUSTOMER", (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onInsertCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
      case StreamEvent(DeleteTuple, o, "CUSTOMER", (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onDeleteCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
      case StreamEvent(SystemInitialized, o, "", Nil) => onSystemInitialized();
      case EndOfStream => ();
      case _ => throw DBTFatalError("Event could not be dispatched: " + event)
    }
    supervisor ! DBTTupleProcessed;
  }
  def act(): Unit ={
    fillTables();
    onSystemInitialized();
    sources.start;
    while(true) {
      receive {
        case EndOfStream => {
          supervisor ! DBTDone;
          sc.stop
          exit();
        }
        case e: DBTEvent => dispatcher(e) 
      }
    }
  }
  def printResults(): Unit = {
    val pp = new PrettyPrinter(8000, 2);
    println(pp.format(<QUERY18>{ getQUERY18().toXML() }</QUERY18>));
  }
  def printMapSizes() = {
/*
    println(NATION.size)
    REGION.printSize;
    QUERY18.printSize;
    mORDERS2.printSize;
    mCUSTOMER1.printSize;
    mCUSTOMER1_mLINEITEM1.printSize;
    mLINEITEM1.printSize;
    mLINEITEM1_mLINEITEM1.printSize;
    mLINEITEM1_E1_1_L1_1.printSize;
*/
  }
}
