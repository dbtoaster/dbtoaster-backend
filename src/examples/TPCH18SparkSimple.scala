package examples
import ddbt.lib.{K3Map,K3Helper}

// run-main examples.TPCH18

import java.io._;
import org.dbtoaster.dbtoasterlib.StreamAdaptor._;
import org.dbtoaster.dbtoasterlib.K3Collection._;
import org.dbtoaster.dbtoasterlib.Source._;
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._;
import org.dbtoaster.dbtoasterlib.ImplicitConversions._;
import org.dbtoaster.dbtoasterlib.QueryInterface._;
import java.util.Date;
import xml._;
import scala.actors.Actor;
import scala.actors.Actor._;

object TPCH18SparkSimple {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new TPCH18SparkSimpleQuery()

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

// -----------------------------------------------------------------------------

import scala.reflect.ClassTag
import spark.SparkContext
import spark.SparkContext._
import spark.RDD


class K3MapS1[K:ClassTag,V:ClassTag](val projs:List[K=>_]=Nil,var rdd:RDD[(K,V)]) {
  private val zero = K3Helper.make_zero[V]()
  private val plus = K3Helper.make_plus[V]()

  def merge(rdd2:RDD[(K,V)]) { rdd = rdd.union(rdd2).reduceByKey(plus).filter{case (k,v) => v!=zero }.coalesce(K3MapS1.N) } // coalesce to reduce memory consumption
  def parAdd[K1,V1](in:K3MapS1[K1,V1],sl:(Int,Any),f:(K1,V1)=>(K,V)) = {
    val m1 = if (sl==null && sl._1<0) in.rdd else in.slice(sl._1,sl._2) // slice (optional)
    merge(m1.map{case (k,v)=>f(k,v)})
  }
  
  def add(k:K,v:V) = merge(K3MapS1.sc.parallelize(Seq((k,v))))
  def get(k:K) = {
    // Lookup blocks indefinitely !!!!
    // rdd.lookup(k) match { case Seq(v) => v case _ => zero }
    println("Faking Lookup")
    zero
  }
  def slice[P](part:Int, partKey:P):RDD[(K,V)] = { val p=projs(part); rdd.filter{case (k,v)=>(p(k)==partKey)} }
  def toXML = K3Helper.toXML(rdd.collect.toMap)
}

object K3MapS1 {
  val sc = new SparkContext("local[8]", "Simple Job", "$YOUR_SPARK_HOME",
             List("target/scala-2.10/distributeddbtoaster_2.10-0.1.jar")) // Match SBT name/version
  val N = 64
  def make[K:ClassTag,V:ClassTag](projs:List[K=>_]=Nil):K3MapS1[K,V] = new K3MapS1(projs, sc.parallelize(Seq[(K,V)](),N))
  def stop { sc.stop }
}

// -----------------------------------------------------------------------------

class TPCH18SparkSimpleQuery() extends DBTQuery {
  var supervisor: Actor = null;
  def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;
  val s1 = createInputStreamSource(new FileReader("resources/data/tpch/lineitem.csv"), List(new CSVAdaptor("LINEITEM", List(IntColumn,IntColumn,IntColumn,IntColumn,FloatColumn,FloatColumn,FloatColumn,FloatColumn,StringColumn,StringColumn,DateColumn,DateColumn,DateColumn,StringColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s2 = createInputStreamSource(new FileReader("resources/data/tpch/orders.csv"), List(new CSVAdaptor("ORDERS", List(IntColumn,IntColumn,StringColumn,FloatColumn,DateColumn,StringColumn,StringColumn,IntColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));
  val s3 = createInputStreamSource(new FileReader("resources/data/tpch/customer.csv"), List(new CSVAdaptor("CUSTOMER", List(IntColumn,StringColumn,StringColumn,IntColumn,StringColumn,FloatColumn,StringColumn,StringColumn), delimiter = "\\|")), Delimited("\n"));

  val sources = new SourceMultiplexer(this, List(s1,s2,s3));
  
  val QUERY18 = K3MapS1.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS2 = K3MapS1.make[(String,Long), Long](List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = K3MapS1.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = K3MapS1.make[(Long,Long,Date,Double), Long](List(
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  ))
  val mLINEITEM1 = K3MapS1.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM1_mLINEITEM1 = K3MapS1.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = K3MapS1.make[Long,Double]()

  def getQUERY18() = QUERY18

  val t0:Long = System.nanoTime()
  var ti:Long = System.nanoTime()
  var tc:Long = 0
  def tick {
    val n:Long = 40
    if ((tc % n)==0) {
        val tt = (System.nanoTime() - t0) / 1000000000.0
        val runtime = (System.nanoTime() - ti) / 1000000000.0
        if (runtime>0) println(("Tup/sec: %5.1f / %5.1f processed: "+tc+" tuples").format(tc/tt,n/runtime))
        ti=System.nanoTime()
    }
    tc=tc+1
    
    
    
    System.gc();
    val rt = Runtime.getRuntime
    val usedMB = (rt.totalMemory() - rt.freeMemory()) / 1024.0 / 1024.0;
    println("Mem: %.2f".format(usedMB))

    /*
    val x = mCUSTOMER1.rdd.collect
    mCUSTOMER1.rdd = K3MapS1.sc.parallelize(x.toSeq)
    */

  }


  //System.setProperty("spark.storage.memoryFraction", "0.1")

    // Plain: Mem: 32.41: [info] Tup/sec:  24.9 /  12.7 processed: 280 tuples
    //mCUSTOMER1.parAdd(mCUSTOMER1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY) )

  // ---------------------------------------------------------------------------
  def onInsertLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    //println("onInsertLINEITEM")
    mCUSTOMER1.parAdd(mCUSTOMER1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY) )
    mLINEITEM1.parAdd(mLINEITEM1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,String,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4,k._5), v * L_QUANTITY) )
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.rdd = mLINEITEM1.rdd.map{ case (k,v) => (k._1,(k,v)) }.join(mLINEITEM1_E1_1_L1_1.rdd).map { case (k0,((k,v),l3_qty)) =>  ((k._2,k._3,k._1,k._4,k._5), v * (100L<l3_qty)) }
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    //println("onDeleteLINEITEM")
    mCUSTOMER1.parAdd(mCUSTOMER1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4), -v * L_QUANTITY) )
    mLINEITEM1.parAdd(mLINEITEM1_mLINEITEM1, (0,L_ORDERKEY), (k:(Long,String,Long,Date,Double),v:Long) => ((L_ORDERKEY,k._2,k._3,k._4,k._5), -v * L_QUANTITY) )
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.rdd = mLINEITEM1.rdd.map{ case (k,v) => (k._1,(k,v)) }.join(mLINEITEM1_E1_1_L1_1.rdd).map { case (k0,((k,v),l3_qty)) =>  ((k._2,k._3,k._1,k._4,k._5), v * (100L<l3_qty)) }
    tick
  }
  // ---------------------------------------------------------------------------
  def onInsertORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    //println("onInsertORDERS")
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY)
    if (L3_QTY!=0.0) QUERY18.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => {
      val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
      ((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
    })
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
    if (L3_QTY!=0.0) mLINEITEM1.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v * L3_QTY))
    mLINEITEM1_mLINEITEM1.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v))
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    //println("onDeleteORDERS")
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY)
    if (L3_QTY!=0.0) QUERY18.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => {
      val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
      ((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), -nv)
    })
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
    if (L3_QTY!=0.0) mLINEITEM1.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v * L3_QTY))
    mLINEITEM1_mLINEITEM1.parAdd(mORDERS2, (0,O_CUSTKEY), (k:(String,Long),v:Long) => ((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v))
    tick
  }
  // ---------------------------------------------------------------------------
  def onInsertCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    //println("onInsertCUSTOMER")
    val m1 = mCUSTOMER1.slice(0,C_CUSTKEY).map { case (k,v) => (k._1,(k,v)) }.join(mLINEITEM1_E1_1_L1_1.rdd)
    QUERY18.merge(m1.map { case (k0,((k,v),l3_qty)) => ((C_NAME,C_CUSTKEY,k._1,k._3,k._4), v * (100L < l3_qty)) })
    mORDERS2.add((C_NAME,C_CUSTKEY), 1L)
    mLINEITEM1.parAdd(mCUSTOMER1, (0,C_CUSTKEY), (k:(Long,Long,Date,Double), v:Double) => ((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v))
    mLINEITEM1_mLINEITEM1.parAdd(mCUSTOMER1_mLINEITEM1, (1,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Long) => ((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) )
    tick
  }
  // ---------------------------------------------------------------------------
  def onDeleteCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    //println("onDeleteCUSTOMER")
    val m1 = mCUSTOMER1.slice(0,C_CUSTKEY).map { case (k,v) => (k._1,(k,v)) }.join(mLINEITEM1_E1_1_L1_1.rdd)
    QUERY18.merge(m1.map { case (k0,((k,v),l3_qty)) => ((C_NAME,C_CUSTKEY,k._1,k._3,k._4), -v * (100L < l3_qty)) })
    mORDERS2.add((C_NAME,C_CUSTKEY), -1L)
    mLINEITEM1.parAdd(mCUSTOMER1, (0,C_CUSTKEY), (k:(Long,Long,Date,Double), v:Double) => ((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v))
    mLINEITEM1_mLINEITEM1.parAdd(mCUSTOMER1_mLINEITEM1, (1,C_CUSTKEY), (k:(Long,Long,Date,Double),v:Long) => ((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) )
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
          K3MapS1.stop
          exit();
        }
        case e: DBTEvent => dispatcher(e) 
      }
      println("Results ---------------")
      printResults
      println("Results end -----------")
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
    mORDERS2.printSize;
    mCUSTOMER1.printSize;
    mCUSTOMER1_mLINEITEM1.printSize;
    mLINEITEM1.printSize;
    mLINEITEM1_mLINEITEM1.printSize;
    mLINEITEM1_E1_1_L1_1.printSize;
*/
  }
}
