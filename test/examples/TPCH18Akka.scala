package ddbt.test.examples
import ddbt.lib._
import java.util.Date

object TPCH18Akka extends Helper {
  def main(args:Array[String]) {
    val (t,res) = runLocal[Q18Master,Q18Worker](7,2251,4,streamsTPCH18());
    println(K3Helper.toStr(res.head)); println("Time:"+time(t))
  }
}

class Q18Worker extends WorkerActor {
  import WorkerActor._
  // constants
  val mQ18 = MapRef(0)
  val mO = MapRef(1)
  val mC = MapRef(2)
  val mCL = MapRef(3)
  val mL = MapRef(4)
  val mLL = MapRef(5)
  val mLE = MapRef(6)
  val f0 = FunRef(0)
  val f1 = FunRef(1)
  val f2 = FunRef(2)
  val f3 = FunRef(3)
  val f4 = FunRef(4)
  val f5 = FunRef(5)
  val f6 = FunRef(6)
  val f7 = FunRef(7)
  val f8 = FunRef(8)
  // maps
  val QUERY18 = K3Map.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS2 = K3Map.make[(String,Long), Long](List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = K3Map.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_L1 = K3Map.make[(Long,Long,Date,Double), Long](List((x:(Long,Long,Date,Double))=>x._1,(x:(Long,Long,Date,Double))=>x._2))
  val mLINEITEM1 = K3Map.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM1_L1 = K3Map.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E11 = K3Map.make[Long,Double]()
  val local = Array[K3Map[_,_]](QUERY18,mORDERS2,mCUSTOMER1,mCUSTOMER1_L1,mLINEITEM1,mLINEITEM1_L1,mLINEITEM1_E11)
  // foreach
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args) match {
    // Lineitem triggers
    case (`f0`,Array(l_okey:Long,l_qty:Double,mul:Int)) => mCUSTOMER1_L1.slice(0,l_okey).foreach { case (k,v) => add(mC,(l_okey,k._2,k._3,k._4), v * l_qty * mul) }; co()
    case (`f1`,Array(l_okey:Long,l_qty:Double,mul:Int)) => mLINEITEM1_L1.slice(0,l_okey).foreach { case (k,v) => add(mL,(l_okey,k._2,k._3,k._4,k._5), v * l_qty * mul) }; co()
    case (`f2`,_) => mLINEITEM1.foreach { case (k,v) => val o_key:Long=k._1; get(mLE,o_key,(l3_qty:Double) => set(mQ18,(k._2,k._3,o_key,k._4,k._5), v * (if (100L<l3_qty && l3_qty!=0L) 1L else 0L) )) }; co()
    // Orders triggers
    case (`f3`,Array(l3_qty:Double,c_key:Long,o_key:Long,o_date:Date,o_total:Double,mul:Int)) => mORDERS2.slice(0,c_key).foreach { case (k,v) => add(mQ18,(k._1,c_key,o_key,o_date,o_total), (v * (if (100L<l3_qty && l3_qty!=0L) 1L else 0L) * l3_qty * mul)) }; co()
    case (`f4`,Array(l3_qty:Double,c_key:Long,o_key:Long,o_date:Date,o_total:Double,mul:Int)) => mORDERS2.slice(0,c_key).foreach { case (k,v) => add(mL,(o_key,k._1,c_key,o_date,o_total), v * l3_qty) }; co()
    case (`f5`,Array(l3_qty:Double,c_key:Long,o_key:Long,o_date:Date,o_total:Double,mul:Int)) => mORDERS2.slice(0,c_key).foreach { case (k,v) => add(mLL,(o_key,k._1,c_key,o_date,o_total), v) }; co()
    // Customer triggers
    case (`f6`,Array(c_key:Long,c_name:String,mul:Int)) => mCUSTOMER1.slice(0,c_key).foreach { case (k,v) => val o_key:Long=k._1; get(mLE,o_key,(l3_qty:Double)=>{ add(mQ18,(c_name,c_key,o_key,k._3,k._4), v * (if (100L<l3_qty && l3_qty!=0L) 1L else 0L) * mul) }) }; co()
    case (`f7`,Array(c_key:Long,c_name:String,mul:Int)) => mCUSTOMER1.slice(0,c_key).foreach { case (k,v) => add(mL,(k._1,c_name,c_key,k._3,k._4), v * mul) }; co()
    case (`f8`,Array(c_key:Long,c_name:String,mul:Int)) => mCUSTOMER1_L1.slice(1,c_key).foreach { case (k,v) => add(mLL,(k._1,c_name,c_key,k._3,k._4), v * mul) }; co()
  }
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = sys.error("No aggregation")
}

class Q18Master extends Q18Worker with MasterActor {
  import WorkerActor._
  import Messages._
  import scala.util.continuations._

  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleInsert,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onAddCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDelCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
  }

  def onAddLINEITEM(l_okey:Long,l_pkey:Long,l_skey:Long,l_linenum:Long,l_qty:Double,l_extprice:Double,l_discount:Double,l_tax:Double,l_retflag:String,l_status:String,
                    l_shipdate:Date,l_commitdate:Date,l_receiptdate:Date,l_shipinstruct:String,l_shipmode:String,l_comm:String) = reset {
    pre(mC,mCL); foreach(mCL,f0,l_okey,l_qty,1)
    pre(mL,mLL); foreach(mLL,f1,l_okey,l_qty,1)
    pre(mLE); add(mLE,l_okey, l_qty)
    clear(mQ18); barrier; pre(mQ18,mL); foreach(mL,f2)
    deq
  }
  def onDelLINEITEM(l_okey:Long,l_pkey:Long,l_skey:Long,l_linenum:Long,l_qty:Double,l_extprice:Double,l_discount:Double,l_tax:Double,l_retflag:String,l_status:String,
                    l_shipdate:Date,l_commitdate:Date,l_receiptdate:Date,l_shipinstruct:String,l_shipmode:String,l_comm:String) = reset {
    pre(mC,mCL); foreach(mCL,f0,l_okey,l_qty,-1)
    pre(mL,mLL); foreach(mLL,f1,l_okey,l_qty,-1)
    pre(mLE); add(mLE,l_okey, -l_qty)
    clear(mQ18); barrier; pre(mQ18,mL); foreach(mL,f2)
    deq
  }

  def onAddORDERS(o_key:Long,c_key:Long,O_ORDERSTATUS:String,o_total:Double,o_date:Date,o_pri:String,o_clerk:String,o_shippri:Long,o_comm:String) = reset {
    pre(-1,mLE); val l3_qty:Double = get[Long,Double](mLE,o_key)
    pre(mQ18,mO); if (l3_qty!=0.0) { foreach(mO,f3,l3_qty,c_key,o_key,o_date,o_total,1) }
    pre(mC); add(mC,(o_key,c_key,o_date,o_total), l3_qty)
    pre(mCL); add(mCL,(o_key,c_key,o_date,o_total), 1L)
    pre(mL,mO); if (l3_qty!=0.0) { foreach(mO,f4,l3_qty,c_key,o_key,o_date,o_total,1) }
    pre(mLL,mO); foreach(mO,f5,l3_qty,c_key,o_key,o_date,o_total,1)
    deq
  }
  def onDelORDERS(o_key:Long,c_key:Long,O_ORDERSTATUS:String,o_total:Double,o_date:Date,o_pri:String,o_clerk:String,o_shippri:Long,o_comm:String) = reset {
    pre(-1,mLE); val l3_qty:Double = get[Long,Double](mLE,o_key)
    pre(mQ18,mO); if (l3_qty!=0.0) { foreach(mO,f3,l3_qty,c_key,o_key,o_date,o_total,-1) }
    pre(mC); add(mC,(o_key,c_key,o_date,o_total), -l3_qty)
    pre(mCL); add(mCL,(o_key,c_key,o_date,o_total), -1L)
    pre(mL,mO); if (l3_qty!=0.0) { foreach(mO,f4,l3_qty,c_key,o_key,o_date,o_total,-1) }
    pre(mLL,mO); foreach(mO,f5,l3_qty,c_key,o_key,o_date,o_total,-1)
    deq
  }

  def onAddCUSTOMER(c_key:Long,c_name:String,c_addr:String,c_nat:Long,c_phone:String,c_acctbal:Double,c_mktseg:String,c_comm:String) = reset {
    pre(mQ18,mC,mLE); foreach(mC,f6,c_key,c_name,1)
    add(mO,(c_name,c_key), 1L)
    pre(mL,mC); foreach(mC,f7,c_key,c_name,1)
    pre(mLL,mCL); foreach(mCL,f8,c_key,c_name,1)
    deq
  }
  def onDelCUSTOMER(c_key:Long,c_name:String,c_addr:String,c_nat:Long,c_phone:String,c_acctbal:Double,c_mktseg:String,c_comm:String) = reset {
    pre(mQ18,mC,mLE); foreach(mC,f6,c_key,c_name,-1)
    add(mO,(c_name,c_key), -1L)
    pre(mL,mC); foreach(mC,f7,c_key,c_name,-1)
    pre(mLL,mCL); foreach(mCL,f8,c_key,c_name,-1)
    deq
  }
  def onSystemReady() {}
}
