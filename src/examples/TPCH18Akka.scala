package examples
import ddbt.lib._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import java.util.Date;

object TPCH18Akka extends Helper {
  def main(args:Array[String]) {
    val (t,res) = run[TPCH18Akka,Long,Double](streamsTPCH18(),false);
    println(K3Helper.toStr(res)); println("Time: "+time(t))
  }
}

class TPCH18Akka extends TPCH18Base {
  val N = 16
  val QUERY18 = K4Map.make[(String,Long,Long,Date,Double), Double](context,N)
  val mORDERS2 = K4Map.make[(String,Long), Long](context,N,List((x:(String,Long))=>x._2)) // 0=List(1)
  val mCUSTOMER1 = K4Map.make[(Long,Long,Date,Double), Double](context,N,List((x:(Long,Long,Date,Double))=>x._2)) // 0=List(1)
  val mCUSTOMER1_mLINEITEM1 = K4Map.make[(Long,Long,Date,Double), Long](context,N,List(
    (x:(Long,Long,Date,Double))=>x._1, // 0=List(0)
    (x:(Long,Long,Date,Double))=>x._2  // 1=List(1)
  ))
  val mLINEITEM1 = K4Map.make[(Long,String,Long,Date,Double), Double](context,N)
  val mLINEITEM1_mLINEITEM1 = K4Map.make[(Long,String,Long,Date,Double), Long](context,N,List((x:(Long,String,Long,Date,Double))=>x._1)) // 0=List(0)
  val mLINEITEM1_E1_1_L1_1 = K4Map.make[Long,Double](context,N)
  def result = QUERY18.toMap

  // ---------------------------------------------------------------------------
  def onAddLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1_mLINEITEM1.foreach((0,L_ORDERKEY)) { case (k,v) => mCUSTOMER1.add((L_ORDERKEY,k._2,k._3,k._4), v * L_QUANTITY) };
    mLINEITEM1_mLINEITEM1.foreach((0,L_ORDERKEY)) { case (k,v) => mLINEITEM1.add((L_ORDERKEY,k._2,k._3,k._4,k._5), v * L_QUANTITY) };
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, L_QUANTITY)
    QUERY18.clear() //foreach { case (k,v) => QUERY18.set(k,0.0) }; //remove(k)
    mLINEITEM1.foreach(null) { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * (( (1L * (100L < L3_QTY)) * (L3_QTY /*alias?*/ != 0L)) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onDelLINEITEM(L_ORDERKEY: Long,L_PARTKEY: Long,L_SUPPKEY: Long,L_LINENUMBER: Long,L_QUANTITY: Double,L_EXTENDEDPRICE: Double,L_DISCOUNT: Double,L_TAX: Double,L_RETURNFLAG: String,L_LINESTATUS: String,L_SHIPDATE: Date,L_COMMITDATE: Date,L_RECEIPTDATE: Date,L_SHIPINSTRUCT: String,L_SHIPMODE: String,L_COMMENT: String) = {
    mCUSTOMER1_mLINEITEM1.foreach((0,L_ORDERKEY)) { case (k,v) => mCUSTOMER1.add((L_ORDERKEY,k._2,k._3,k._4), -v * L_QUANTITY) };
    mLINEITEM1_mLINEITEM1.foreach((0,L_ORDERKEY)) { case (k,v) => mLINEITEM1.add((L_ORDERKEY,k._2,k._3,k._4,k._5), -v * L_QUANTITY) };
    mLINEITEM1_E1_1_L1_1.add(L_ORDERKEY, -L_QUANTITY);
    QUERY18.clear() //foreach { case (k,v) => QUERY18.set(k,0.0) }; //remove(k)
    mLINEITEM1.foreach(null) { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY)
      QUERY18.set((k._2,k._3,ORDERKEY,k._4,k._5), v * ( (100L < L3_QTY) * (L3_QTY /*alias?*/ != 0L) != 0L))
    }
  }
  // ---------------------------------------------------------------------------
  def onAddORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY);
    if (L3_QTY!=0.0) mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) =>
      val nv = (v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L)) * L3_QTY;
      QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), 1L)
    if (L3_QTY!=0.0) mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) => mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v * L3_QTY) }
    mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) => mLINEITEM1_mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), v) }
  };
  // ---------------------------------------------------------------------------
  def onDelORDERS(O_ORDERKEY: Long,O_CUSTKEY: Long,O_ORDERSTATUS: String,O_TOTALPRICE: Double,O_ORDERDATE: Date,O_ORDERPRIORITY: String,O_CLERK: String,O_SHIPPRIORITY: Long,O_COMMENT: String) = {
    val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(O_ORDERKEY)
    if(L3_QTY!=0.0) mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) =>
      val nv = ((v * ((100L < L3_QTY) * (L3_QTY != 0L)) != 0L) * L3_QTY) * -1L;
      QUERY18.add((k._1,O_CUSTKEY,O_ORDERKEY,O_ORDERDATE,O_TOTALPRICE), nv)
    }
    mCUSTOMER1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -L3_QTY)
    mCUSTOMER1_mLINEITEM1.add((O_ORDERKEY,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -1L)
    if(L3_QTY!=0.0) mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) => mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), - (v * L3_QTY)) }
    mORDERS2.foreach((0,O_CUSTKEY)) { case (k,v) => mLINEITEM1_mLINEITEM1.add((O_ORDERKEY,k._1,O_CUSTKEY,O_ORDERDATE,O_TOTALPRICE), -v) }
  };
  // ---------------------------------------------------------------------------
  def onAddCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER1.foreach((0,C_CUSTKEY)) { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
    };
    mORDERS2.add((C_NAME,C_CUSTKEY), 1L)
    mCUSTOMER1.foreach((0,C_CUSTKEY)) { case (k,v) => mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) }
    mCUSTOMER1_mLINEITEM1.foreach((1,C_CUSTKEY)) { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), v) }
  };
  // ---------------------------------------------------------------------------
  def onDelCUSTOMER(C_CUSTKEY: Long,C_NAME: String,C_ADDRESS: String,C_NATIONKEY: Long,C_PHONE: String,C_ACCTBAL: Double,C_MKTSEGMENT: String,C_COMMENT: String) = {
    mCUSTOMER1.foreach((0,C_CUSTKEY)) { case (k,v) =>
      val ORDERKEY:Long = k._1; // Long
      val L3_QTY:Double = mLINEITEM1_E1_1_L1_1.get(ORDERKEY); // Double
      val nv = -v * (( (100L < L3_QTY) * (L3_QTY != 0L)) != 0L);
      QUERY18.add((C_NAME,C_CUSTKEY,ORDERKEY,k._3,k._4), nv)
    };
    mORDERS2.add(Tuple2(C_NAME,C_CUSTKEY), -1L)
    mCUSTOMER1.foreach((0,C_CUSTKEY)) { case (k,v) => mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) }
    mCUSTOMER1_mLINEITEM1.foreach((1,C_CUSTKEY)) { case (k,v) => mLINEITEM1_mLINEITEM1.add((k._1,C_NAME,C_CUSTKEY,k._3,k._4), -v) }
  };
}
