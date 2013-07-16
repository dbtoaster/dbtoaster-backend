package examples
import ddbt.lib.K3Map

// run-main examples.TPCH18Opt

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

object TPCH18Opt {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new TPCH18QueryNew()

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

class TPCH18QueryOpt() extends DBTQuery {
  var supervisor: Actor = null;
  def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;
  val s1 = createInputStreamSource(new FileReader("resources/data/tpch/lineitem.csv"), List(new CSVAdaptor("LINEITEM", List(IntColumn,IntColumn,IntColumn,IntColumn,FloatColumn,FloatColumn,FloatColumn,FloatColumn,StringColumn,StringColumn,DateColumn,DateColumn,DateColumn,StringColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s2 = createInputStreamSource(new FileReader("resources/data/tpch/orders.csv"), List(new CSVAdaptor("ORDERS", List(IntColumn,IntColumn,StringColumn,FloatColumn,DateColumn,StringColumn,StringColumn,IntColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s3 = createInputStreamSource(new FileReader("resources/data/tpch/customer.csv"), List(new CSVAdaptor("CUSTOMER", List(IntColumn,StringColumn,StringColumn,IntColumn,StringColumn,FloatColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));

  val sources = new SourceMultiplexer(this, List(s1,s2,s3));
  
  // ---------------------------------------------------------------------------

  val QUERY18 = K3Map.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS = K3Map.make[(String,Long), Long](List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER = K3Map.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER_mLINEITEM = K3Map.make[(Long,Long,Date,Double), Long](List(
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  ))
  val mLINEITEM = K3Map.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM_mLINEITEM = K3Map.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM_E1_1_L1_1 = K3Map.make[Long,Double]()

  def getQUERY18() = QUERY18

  // ---------------------------------------------------------------------------
  def onInsertLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER_mLINEITEM.slice(0,L_ORDERKEY).foreach { case (k,v) => mCUSTOMER.add((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY) };
    mLINEITEM_mLINEITEM.slice(0,L_ORDERKEY).foreach { case (k,v) => mLINEITEM.add((L_ORDERKEY,k._2,k._3,k._4,k._5), v * L_QUANTITY) };
    mLINEITEM_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.clear()
    // join on ORDERKEY
    mLINEITEM.foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * (( (1L * (100L < L3_QTY)) * (L3_QTY /*alias?*/ != 0L)) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onDeleteLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER_mLINEITEM.slice(0,L_ORDERKEY).foreach { case (k,v) => mCUSTOMER.add((L_ORDERKEY,k._2,k._3,k._4), -v * L_QUANTITY) };
    mLINEITEM_mLINEITEM.slice(0,L_ORDERKEY).foreach { case (k,v) => mLINEITEM.add((L_ORDERKEY,k._2,k._3,k._4,k._5), -v * L_QUANTITY) };
    mLINEITEM_E1_1_L1_1.add(L_ORDERKEY, -L_QUANTITY);
    QUERY18.clear()
    // join on ORDERKEY
    mLINEITEM.foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * ( (100L < L3_QTY) * (L3_QTY /*alias?*/ != 0L) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onInsertORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(O_ORDERKEY);
    mORDERS.slice(0,O_CUSTKEY).foreach { case (k,v) =>
      if (L3_QTY!=0.0) {
        val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
        QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
        mLINEITEM.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v * L3_QTY)
      }
      mLINEITEM_mLINEITEM.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v)
    }
    mCUSTOMER.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
    mCUSTOMER_mLINEITEM.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
  };
  // ---------------------------------------------------------------------------
  def onDeleteORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(O_ORDERKEY)
    mORDERS.slice(0,O_CUSTKEY).foreach { case (k,v) =>
      if(L3_QTY!=0.0) {
        val nv = ((v * ((100L < L3_QTY) * (L3_QTY != 0L)) != 0L) * L3_QTY) * -1L;
        QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
        mLINEITEM.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), - (v * L3_QTY))
      }
      mLINEITEM_mLINEITEM.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v)
    }
    mCUSTOMER.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
    mCUSTOMER_mLINEITEM.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
  };
  // ---------------------------------------------------------------------------
  def onInsertCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER.slice(0,C_CUSTKEY).foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
      mLINEITEM.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v)
    };
    mORDERS.add((C_NAME,C_CUSTKEY), 1L)
    mCUSTOMER_mLINEITEM.slice(1,C_CUSTKEY).foreach { case (k,v) => mLINEITEM_mLINEITEM.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) }
  };
  // ---------------------------------------------------------------------------
  def onDeleteCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER.slice(0,C_CUSTKEY).foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = -v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
      mLINEITEM.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v)
    };
    mORDERS.add(Tuple2(C_NAME,C_CUSTKEY), -1L)
    mCUSTOMER_mLINEITEM.slice(1,C_CUSTKEY).foreach { case (k,v) => mLINEITEM_mLINEITEM.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) }
  };
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
          exit();
        }
        case e: DBTEvent => dispatcher(e) 
      }
    }
  }
  def printResults(): Unit = {
    val pp = new PrettyPrinter(8000, 2);
    println(pp.format(<QUERY18>{ getQUERY18().toXML }</QUERY18>));
  }
  def printMapSizes() = {
/*
    println(NATION.size)
    REGION.printSize;
    QUERY18.printSize;
    mORDERS.printSize;
    mCUSTOMER.printSize;
    mCUSTOMER_mLINEITEM.printSize;
    mLINEITEM.printSize;
    mLINEITEM_mLINEITEM.printSize;
    mLINEITEM_E1_1_L1_1.printSize;
*/
  }
}
