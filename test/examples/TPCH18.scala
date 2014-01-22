package ddbt.test.examples
import ddbt.lib._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import java.util.Date;

object TPCH18 {
  import Helper._
  def main(args:Array[String]) {
    val (t,res) = run[TPCH18](Compat.streamsTPCH18());
    println(res.head.toString); println("Time: "+t)
  }
}

abstract class TPCH18Base extends Actor {
  import Messages._
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case StreamInit(_) => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleInsert,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onAddCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDelCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,List(result))
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
  val QUERY18 = M3Map.make[(String,Long,Long,Date,Double), Double]()
  val mORDERS2 = M3Map.make[(String,Long), Long]((x:(String,Long))=>x._2) // 0=List(1)
  val mCUSTOMER1 = M3Map.make[(Long,Long,Date,Double), Double]((x:(Long,Long,Date,Double))=>x._2) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = M3Map.make[(Long,Long,Date,Double), Long](
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  )
  val mLINEITEM1 = M3Map.make[(Long,String,Long,Date,Double), Double]()
  val mLINEITEM1_mLINEITEM1 = M3Map.make[(Long,String,Long,Date,Double), Long]((x:(Long,String,Long,Date,Double))=>x._1) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = M3Map.make[Long,Double]()
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
