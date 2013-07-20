package examples
import ddbt.lib._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import java.util.Date;

object TPCH18 extends Helper {
  def main(args:Array[String]) {
    val (time,res) = run[TPCH18,Long,Double](streamsTPCH18(),false);
    printMap(res); printTime(time)
  }
}

abstract class TPCH18Base extends Actor {
  import Messages._
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onAddLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleDelete, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onDelLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleInsert, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onAddORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleDelete, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onDelORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleInsert, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onAddCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
    case TupleEvent(TupleDelete, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onDelCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,result.toMap)
  }
  def onAddLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) : Unit
  def onDelLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) : Unit
  def onAddORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) : Unit
  def onDelORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) : Unit
  def onAddCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) : Unit
  def onDelCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) : Unit
  def result:Map[_,_]
}

class TPCH18 extends TPCH18Base {
  val QUERY18 = K3Map.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS2 = K3Map.make[(String,Long), Long](List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = K3Map.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = K3Map.make[(Long,Long,Date,Double), Long](List(
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  ))
  val mLINEITEM1 = K3Map.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM1_mLINEITEM1 = K3Map.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = K3Map.make[Long,Double]()
  def result = QUERY18.toMap

  // ---------------------------------------------------------------------------
  def onAddLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1_mLINEITEM1.slice(0,L_ORDERKEY).foreach { case (k,v) => mCUSTOMER1.add((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY) };
    mLINEITEM1_mLINEITEM1.slice(0,L_ORDERKEY).foreach { case (k,v) => mLINEITEM1.add((L_ORDERKEY,k._2,k._3,k._4,k._5), v * L_QUANTITY) };
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.clear() //foreach { case (k,v) => QUERY18.set(k,0.0) }; //remove(k)
    mLINEITEM1.foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * (( (1L * (100L < L3_QTY)) * (L3_QTY /*alias?*/ != 0L)) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onDelLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1_mLINEITEM1.slice(0,L_ORDERKEY).foreach { case (k,v) => mCUSTOMER1.add((L_ORDERKEY,k._2,k._3,k._4), -v * L_QUANTITY) };
    mLINEITEM1_mLINEITEM1.slice(0,L_ORDERKEY).foreach { case (k,v) => mLINEITEM1.add((L_ORDERKEY,k._2,k._3,k._4,k._5), -v * L_QUANTITY) };
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, -L_QUANTITY);
    QUERY18.clear() //foreach { case (k,v) => QUERY18.set(k,0.0) }; //remove(k)
    mLINEITEM1.foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * ( (100L < L3_QTY) * (L3_QTY /*alias?*/ != 0L) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onAddORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY);
    if (L3_QTY!=0.0) mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) =>
      val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
      QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
    if (L3_QTY!=0.0) mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) => mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v * L3_QTY) }
    mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v) }
  }
  // ---------------------------------------------------------------------------
  def onDelORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY)
    if(L3_QTY!=0.0) mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) =>
      val nv = ((v * ((100L < L3_QTY) * (L3_QTY != 0L)) != 0L) * L3_QTY) * -1L;
      QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
    if(L3_QTY!=0.0) mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) => mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), - (v * L3_QTY)) }
    mORDERS2.slice(0,O_CUSTKEY).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v) }
  }
  // ---------------------------------------------------------------------------
  def onAddCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER1.slice(0,C_CUSTKEY).foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
    };
    mORDERS2.add((C_NAME,C_CUSTKEY), 1L)
    mCUSTOMER1.slice(0,C_CUSTKEY).foreach { case (k,v) => mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) }
    mCUSTOMER1_mLINEITEM1.slice(1,C_CUSTKEY).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) }
  }
  // ---------------------------------------------------------------------------
  def onDelCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER1.slice(0,C_CUSTKEY).foreach { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = -v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
    };
    mORDERS2.add(Tuple2(C_NAME,C_CUSTKEY), -1L)
    mCUSTOMER1.slice(0,C_CUSTKEY).foreach { case (k,v) => mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) }
    mCUSTOMER1_mLINEITEM1.slice(1,C_CUSTKEY).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) }
  }
}
