package examples
import ddbt.lib._
import akka.actor.Props
import java.util.Date

object TPCH18Akka2 extends Helper {
  def main(args:Array[String]) {
    //K3Helper.toStr(bench("TPC-H_Q18_Akka2(Network)",4,()=>runLocal[Q18Master,Q18Worker,(String,Long,Long,Date,Double),Double](2251,4,streamsTPCH18()) ))
    val (t,res) = runLocal[Q18Master,Q18Worker,(String,Long,Long,Date,Double),Double](2251,4,streamsTPCH18());
    println(K3Helper.toStr(res)); println("Time: "+time(t))
    //for (i <- 0 until 10) { println("Time: "+time(runLocal[Q18Master,Q18Worker,(String,Long,Long,Date,Double),Double](2251,4,streamsTPCH18())._1)); Thread.sleep(1000); }
  }
}

object Q18Msg {
  case class LFor(f:Int,l_orderkey:Long,l_quantity:Double,mul:Int=1)
  case object LFor2
  case class OFor(f:Int,l3_qty:Double,o_custkey:Long,o_orderkey:Long,o_orderdate:Date,o_totalprice:Double,mul:Int=1)
  case class CFor(f:Int,c_custkey:Long,c_name:String,mul:Int=1)
}


class Q18Worker extends WorkerActor {
  import WorkerActor._
  import Q18Msg._

  val QUERY18 = K3Map.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS2 = K3Map.make[(String,Long), Long](List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = K3Map.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = K3Map.make[(Long,Long,Date,Double), Long](List((x:(Long,Long,Date,Double))=>x._1,(x:(Long,Long,Date,Double))=>x._2))
  val mLINEITEM1 = K3Map.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM1_mLINEITEM1 = K3Map.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = K3Map.make[Long,Double]()

  def local[K,V](m:MapRef) = (m match {
    case 0 => QUERY18
    case 1 => mORDERS2
    case 2 => mCUSTOMER1
    case 3 => mCUSTOMER1_mLINEITEM1
    case 4 => mLINEITEM1
    case 5 => mLINEITEM1_mLINEITEM1
    case 6 => mLINEITEM1_E1_1_L1_1
    case _ => sys.error("No such map")
  }).asInstanceOf[K3Map[K,V]]

  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    // Lineitem triggers
    case LFor(0,l_orderkey,l_quantity,mul) => mCUSTOMER1_mLINEITEM1.slice(0,l_orderkey).foreach { case (k,v) => (2:MapRef).add((l_orderkey,k._2,k._3,k._4), v * l_quantity * mul) };
    case LFor(1,l_orderkey,l_quantity,mul) => mLINEITEM1_mLINEITEM1.slice(0,l_orderkey).foreach { case (k,v) => (4:MapRef).add((l_orderkey,k._2,k._3,k._4,k._5), v * l_quantity * mul) };
    case LFor2 => mLINEITEM1.foreach { case (k,v) => val ORDERKEY:Long = k._1;
      (6:MapRef).get(ORDERKEY,(L3_QTY:Double) => (0:MapRef).set((k._2,k._3,ORDERKEY,k._4,k._5), v * (( (1L * (100L < L3_QTY)) * (L3_QTY != 0L)) != 0L)))
    }
    // Orders triggers
    case OFor(2,l3_qty,o_custkey,o_orderkey,o_orderdate,o_totalprice,mul) => mORDERS2.slice(0,o_custkey).foreach { case (k,v) =>
      (0:MapRef).add((k._1,o_custkey,o_orderkey,o_orderdate,o_totalprice), (v * (( (100L < l3_qty) * (l3_qty != 0L)) != 0L)) * l3_qty * mul)
    }
    case OFor(3,l3_qty,o_custkey,o_orderkey,o_orderdate,o_totalprice,mul) => mORDERS2.slice(0,o_custkey).foreach { case (k,v) => (4:MapRef).add((o_orderkey,k._1,o_custkey,o_orderdate,o_totalprice), v * l3_qty) }
    case OFor(4,l3_qty,o_custkey,o_orderkey,o_orderdate,o_totalprice,mul) => mORDERS2.slice(0,o_custkey).foreach { case (k,v) => (5:MapRef).add((o_orderkey,k._1,o_custkey,o_orderdate,o_totalprice), v) }    
    // Customer triggers
    case CFor(5,c_custkey,c_name,mul) => mCUSTOMER1.slice(0,c_custkey).foreach { case (k,v) => val ORDERKEY:Long = k._1;
      (6:MapRef).get(ORDERKEY,(L3_QTY:Double)=>{ (0:MapRef).add((c_name,c_custkey,ORDERKEY,k._3,k._4), v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L) * mul) })
    }
    case CFor(6,c_custkey,c_name,mul) => mCUSTOMER1.slice(0,c_custkey).foreach { case (k,v) => (4:MapRef).add((k._1,c_name,c_custkey,k._3,k._4), v * mul) }
    case CFor(7,c_custkey,c_name,mul) => mCUSTOMER1_mLINEITEM1.slice(1,c_custkey).foreach { case (k,v) => (5:MapRef).add((k._1,c_name,c_custkey,k._3,k._4), v * mul) }
  }
}

class Q18Master(props:Array[Props]) extends MasterActor(props) {
  import WorkerActor._
  import Messages._
  import Q18Msg._

  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    case TupleEvent(TupleInsert, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onAddLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleDelete, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onDelLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleInsert, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onAddORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleDelete, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onDelORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleInsert, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onAddCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
    case TupleEvent(TupleDelete, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onDelCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
  }

  def b(msg:Any) = workers.foreach { w => w ! msg }

  def onAddLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    pre(2,List(3)); b(LFor(0,L_ORDERKEY,L_QUANTITY,1))
    pre(4,List(5)); b(LFor(1,L_ORDERKEY,L_QUANTITY,1))
    pre(6); (6:MapRef).add(L_ORDERKEY, L_QUANTITY)
    (0:MapRef).clear(); flush(); pre(0,List(4)); b(LFor2)
  }

  def onDelLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    pre(2,List(3)); b(LFor(0,L_ORDERKEY,L_QUANTITY,-1))
    pre(4,List(5)); b(LFor(1,L_ORDERKEY,L_QUANTITY,-1))
    pre(6); (6:MapRef).add(L_ORDERKEY, -L_QUANTITY)
    (0:MapRef).clear(); flush(); pre(0,List(4)); b(LFor2)
  }

  def onAddORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    pre(-1/*dummy*/,List(6)); (6:MapRef).get(O_ORDERKEY,(L3_QTY:Double)=>{
      if (L3_QTY!=0.0) { pre(0,List(1)); b(OFor(2,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,1)) }
      pre(2); (2:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
      pre(3); (3:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
      if (L3_QTY!=0.0) { pre(4,List(1)); b(OFor(3,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,1)) }
      pre(5,List(1)); b(OFor(4,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,1))
    })
  }

  def onDelORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    pre(-1/*dummy*/,List(6)); (6:MapRef).get(O_ORDERKEY,(L3_QTY:Double)=>{
      if (L3_QTY!=0.0) { pre(0,List(1)); b(OFor(2,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,-1)) }
      pre(2); (2:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
      pre(3); (3:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
      if (L3_QTY!=0.0) { pre(4,List(1)); b(OFor(3,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,-1)) }
      pre(5,List(1)); b(OFor(4,L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE,-1))
    })
  }

  def onAddCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    pre(0,List(2,6)); b(CFor(5,C_CUSTKEY,C_NAME,1))
    (1:MapRef).add((C_NAME,C_CUSTKEY), 1L)
    pre(4,List(2)); b(CFor(6,C_CUSTKEY,C_NAME,1))
    pre(5,List(3)); b(CFor(7,C_CUSTKEY,C_NAME,1))
  }

  def onDelCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    pre(0,List(2,6)); b(CFor(5,C_CUSTKEY,C_NAME,-1))
    (1:MapRef).add((C_NAME,C_CUSTKEY), -1L)
    pre(4,List(2)); b(CFor(6,C_CUSTKEY,C_NAME,-1))
    pre(5,List(3)); b(CFor(7,C_CUSTKEY,C_NAME,-1))
  }
}
