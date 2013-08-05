package examples
import ddbt.lib._
import akka.actor.Props
import java.util.Date

object TPCH18Akka2 extends Helper {
  def main(args:Array[String]) {
    //K3Helper.toStr(bench("TPC-H_Q18_Akka2(Network)",10,()=>runLocal[Q18Master,Q18Worker,(String,Long,Long,Date,Double),Double](2251,4,streamsTPCH18()) ))

    val (t,res) = runLocal[Q18Master,Q18Worker,(String,Long,Long,Date,Double),Double](2251,4,streamsTPCH18());
    println(K3Helper.toStr(res)); println("Time: "+time(t))
  }
}

class Q18Worker extends WorkerActor {
  import WorkerActor._

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
    // List(L_ORDERKEY,L_QUANTITY)
    case Foreach(1,args) => mCUSTOMER1_mLINEITEM1.slice(0,args(0)).foreach { case (k,v) => (2:MapRef).add((args(0),k._2,k._3,k._4), v * args(1).asInstanceOf[Double]) }
    case Foreach(2,args) => mLINEITEM1_mLINEITEM1.slice(0,args(0)).foreach { case (k,v) => (4:MapRef).add((args(0),k._2,k._3,k._4,k._5), v * args(1).asInstanceOf[Double]) }
    case Foreach(3,args) => mLINEITEM1.foreach { case (k,v) => val orderkey:Long = k._1;
      (6:MapRef).get(orderkey,(l3_qty:Double)=>(0:MapRef).set((k._2,k._3,orderkey,k._4,k._5), v * (( (1L * (100L < l3_qty)) * (l3_qty != 0L)) != 0L)))
    }
    // List(L3_QTY,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)
    case Foreach(4,args) => val L3_QTY=args(0).asInstanceOf[Double];
      mORDERS2.slice(0,args(1)).foreach { case (k,v) =>
        val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
        QUERY18.add((k._1,args(1).asInstanceOf[Long],args(2).asInstanceOf[Long],args(3).asInstanceOf[Date],args(4).asInstanceOf[Double]), nv)
      }
    case Foreach(5,args) => val L3_QTY=args(0).asInstanceOf[Double]; mORDERS2.slice(0,args(1)).foreach { case (k,v) => mLINEITEM1.add((args(2).asInstanceOf[Long],k._1,args(1).asInstanceOf[Long],args(3).asInstanceOf[Date],args(4).asInstanceOf[Double]), v * L3_QTY) }
    // List(O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)
    case Foreach(6,args) => mORDERS2.slice(0,args(0)).foreach { case (k,v) => (5:MapRef).add((args(1).asInstanceOf[Long],k._1,args(0).asInstanceOf[Long],args(2).asInstanceOf[Long],args(3)), v) }

    // List(C_CUSTKEY,C_NAME)
    case Foreach(7,args) => mCUSTOMER1.slice(0,args(0)).foreach { case (k,v) => val ORDERKEY:Long = k._1; (5:MapRef).get(ORDERKEY,(l3_qty:Double) => {
      val nv = v * (( (100L < l3_qty) * (l3_qty != 0L)) != 0L); (0:MapRef).add((args(1).asInstanceOf[String],args(0).asInstanceOf[Long],ORDERKEY,k._3,k._4), nv) })};
    case Foreach(8,args) => mCUSTOMER1.slice(0,args(0)).foreach { case (k,v) => mLINEITEM1.add((k._1,args(1).asInstanceOf[String],args(0).asInstanceOf[Long],k._3,k._4), v) }
    case Foreach(9,args) => mCUSTOMER1_mLINEITEM1.slice(1,args(0)).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,args(1).asInstanceOf[String],args(0).asInstanceOf[Long],k._3,k._4), v) }


    // Negative
    case Foreach(104,args) => val L3_QTY=args(0).asInstanceOf[Double]; mORDERS2.slice(0,args(1)).foreach { case (k,v) => val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
        QUERY18.add((k._1,args(1).asInstanceOf[Long],args(2).asInstanceOf[Long],args(3).asInstanceOf[Date],args(4).asInstanceOf[Double]), -nv) }
    case Foreach(105,args) => val L3_QTY=args(0).asInstanceOf[Double]; mORDERS2.slice(0,args(1)).foreach { case (k,v) => mLINEITEM1.add((args(2).asInstanceOf[Long],k._1,args(1).asInstanceOf[Long],args(3).asInstanceOf[Date],args(4).asInstanceOf[Double]), -v * L3_QTY) }
    case Foreach(106,args) => mORDERS2.slice(0,args(0)).foreach { case (k,v) => (5:MapRef).add((args(1).asInstanceOf[Long],k._1,args(0).asInstanceOf[Long],args(2).asInstanceOf[Long],args(3)), -v) }
    case Foreach(107,args) => mCUSTOMER1.slice(0,args(0)).foreach { case (k,v) => val ORDERKEY:Long = k._1; /*(5:MapRef).get(ORDERKEY,(l3_qty:Double) => {
      val nv = v * (( (100L < l3_qty) * (l3_qty != 0L)) != 0L); (0:MapRef).add((args(1).asInstanceOf[String],args(0).asInstanceOf[Long],ORDERKEY,k._3,k._4), -nv) })*/ };
    case Foreach(108,args) => mCUSTOMER1.slice(0,args(0)).foreach { case (k,v) => mLINEITEM1.add((k._1,args(1).asInstanceOf[String],args(0).asInstanceOf[Long],k._3,k._4), -v) }
    case Foreach(109,args) => mCUSTOMER1_mLINEITEM1.slice(1,args(0)).foreach { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,args(1).asInstanceOf[String],args(0).asInstanceOf[Long],k._3,k._4), -v) }
  }
}

class Q18Master(props:Array[Props]) extends MasterActor(props) {
  import WorkerActor._
  import Messages._
  val map:MapRef = 0

  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    case TupleEvent(TupleInsert, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onAddLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleDelete, "LINEITEM", o, (vlORDERKEY: Long)::(vlPARTKEY: Long)::(vlSUPPKEY: Long)::(vlLINENUMBER: Long)::(vlQUANTITY: Double)::(vlEXTENDEDPRICE: Double)::(vlDISCOUNT: Double)::(vlTAX: Double)::(vlRETURNFLAG: String)::(vlLINESTATUS: String)::(vlSHIPDATE: Date)::(vlCOMMITDATE: Date)::(vlRECEIPTDATE: Date)::(vlSHIPINSTRUCT: String)::(vlSHIPMODE: String)::(vlCOMMENT: String)::Nil) => onDelLINEITEM(vlORDERKEY,vlPARTKEY,vlSUPPKEY,vlLINENUMBER,vlQUANTITY,vlEXTENDEDPRICE,vlDISCOUNT,vlTAX,vlRETURNFLAG,vlLINESTATUS,vlSHIPDATE,vlCOMMITDATE,vlRECEIPTDATE,vlSHIPINSTRUCT,vlSHIPMODE,vlCOMMENT);
    case TupleEvent(TupleInsert, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onAddORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleDelete, "ORDERS", o, (voORDERKEY: Long)::(voCUSTKEY: Long)::(voORDERSTATUS: String)::(voTOTALPRICE: Double)::(voORDERDATE: Date)::(voORDERPRIORITY: String)::(voCLERK: String)::(voSHIPPRIORITY: Long)::(voCOMMENT: String)::Nil) => onDelORDERS(voORDERKEY,voCUSTKEY,voORDERSTATUS,voTOTALPRICE,voORDERDATE,voORDERPRIORITY,voCLERK,voSHIPPRIORITY,voCOMMENT);
    case TupleEvent(TupleInsert, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onAddCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
    case TupleEvent(TupleDelete, "CUSTOMER", o, (vcCUSTKEY: Long)::(vcNAME: String)::(vcADDRESS: String)::(vcNATIONKEY: Long)::(vcPHONE: String)::(vcACCTBAL: Double)::(vcMKTSEGMENT: String)::(vcCOMMENT: String)::Nil) => onDelCUSTOMER(vcCUSTKEY,vcNAME,vcADDRESS,vcNATIONKEY,vcPHONE,vcACCTBAL,vcMKTSEGMENT,vcCOMMENT);
  }

  // ---------------------------------------------------------------------------
  def onAddLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    pre(2,List(3)); foreach(1,List(L_ORDERKEY,L_QUANTITY))
    pre(3,List(5)); foreach(2,List(L_ORDERKEY,L_QUANTITY))
    pre(6); (6:MapRef).add(L_ORDERKEY, L_QUANTITY);
    pre(0); (0:MapRef).clear(); flush(); foreach(3,Nil)
  }
  // ---------------------------------------------------------------------------
  def onDelLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    pre(2,List(3)); foreach(1,List(L_ORDERKEY,-L_QUANTITY))
    pre(3,List(5)); foreach(2,List(L_ORDERKEY,-L_QUANTITY))
    pre(6); (6:MapRef).add(L_ORDERKEY,-L_QUANTITY);
    pre(0); (0:MapRef).clear(); flush(); foreach(3,Nil)
  }
  // ---------------------------------------------------------------------------
  def onAddORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    flush();
    (6:MapRef).get(O_ORDERKEY,(l3_qty:Double) => {
      if (l3_qty!=0.0) { pre(0,List(1)); foreach(4,List(l3_qty,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) }
      pre(2); (2:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), l3_qty)
      pre(3); (3:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
      if (l3_qty!=0.0) { pre(4,List(1)); foreach(5,List(l3_qty,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) }
    })
    pre(5,List(1));
    foreach(6,List(O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))
  }
  // ---------------------------------------------------------------------------
  def onDelORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    flush();
    (6:MapRef).get(O_ORDERKEY,(l3_qty:Double) => {
      if (l3_qty!=0.0) { pre(0,List(1)); foreach(104,List(l3_qty,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) }
      pre(2); (2:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -l3_qty)
      pre(3); (3:MapRef).add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
      if (l3_qty!=0.0) { pre(4,List(1)); foreach(105,List(l3_qty,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE)) }
    })
    pre(5,List(1));
    foreach(106,List(O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE))
  }
  // ---------------------------------------------------------------------------
  def onAddCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
//    pre(0,List(2,5)); foreach(7,List(C_CUSTKEY,C_NAME)) // XXX: bug here
    pre(1); (1:MapRef).add((C_NAME,C_CUSTKEY), 1L)
    pre(4,List(2)); foreach(8,List(C_CUSTKEY,C_NAME))
    pre(5,List(3)); foreach(9,List(C_CUSTKEY,C_NAME))
  }
  // ---------------------------------------------------------------------------
  def onDelCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    pre(0,List(2,5)); foreach(107,List(C_CUSTKEY,C_NAME))
    pre(1); (1:MapRef).add((C_NAME,C_CUSTKEY), -1L)
    pre(4,List(2)); foreach(108,List(C_CUSTKEY,C_NAME))
    pre(5,List(3)); foreach(109,List(C_CUSTKEY,C_NAME))
  }
}
