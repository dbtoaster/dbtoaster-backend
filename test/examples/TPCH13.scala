package ddbt.test.examples
import ddbt.lib._

import akka.actor.Actor
import java.util.Date

/**
 * This query demonstrates that we _NEED_ to use intermediate maps
 * for aggregation with multiple keys. We need to decompose in 2 steps:
 * 1. for all mapping, we write into the map (body of AggSum)
 * 2. We do a foreach on the map and execute the continuation.
 */

object TPCH13 {
  import Helper._
  def main(args:Array[String]) {
    //val ref = bench("ReferenceLMS ",10,()=>run[TPCH13Ref,Map[Long,Long]](streamsTPCH13()))
    val res = bench("HandOptimized",10,()=>run[TPCH13](streamsTPCH13()))
    val gen = bench("TCK-Generated",10,()=>run[TPCH13Gen](streamsTPCH13()))
    def eq(m1:Map[Long,Long],m2:Map[Long,Long]) = m1.filter{case (k,v) => v!=0}==m2.filter{case (k,v) => v!=0}
    def m0ll(l:List[Any]):Map[Long,Long] = l.head.asInstanceOf[Map[Long,Long]]
    println("Correctness: "+(if(eq(m0ll(res),m0ll(gen))) "OK" else "FAILURE !!!!"))
    println("HandOpt:"); println(res.head.toString);
    if(!eq(m0ll(res),m0ll(gen))) { println("Generated:"); println(gen.head.toString); }

    //println("Correctness: "+(if(eq(ref,res)) "OK" else "FAILURE !!!!"))
    //println("Correctness: "+(if(eq(ref,gen)) "OK" else "FAILURE !!!!"))
    //println("Reference:"); println(K3Helper.toStr(ref));
    //if(!eq(ref,res)) { println("HandOpt:"); println(K3Helper.toStr(res)); }
    //if(!eq(ref,gen)) { println("Generated:"); println(K3Helper.toStr(gen)); }
  }
}

// NB: only inserts have been optimized
class TPCH13 extends Actor {
  import Messages._
  import Functions._

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onInsertORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDeleteORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) =>
       onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
       onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
       onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,List(result))
  }

  val CUSTDIST = M3Map.make[Long,Long]()
  val CUSTDIST_mORDERS1_E1_4 = M3Map.make[Long,Long]()
  val CUSTDIST_mCUSTOMER1_E1_1 = M3Map.make[Long,Long]()
  val CUSTDIST_mCUSTOMER1_E1_3 = M3Map.make[Long,Long]()
  def result:Map[Long,Long] = CUSTDIST.toMap

  def onInsertORDERS(x6: Long, x7: Long, x8: String, x9: Double, x10: Date, x11: String, x12: String, x13: Long, x14: String): Unit = {
    val temp = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val l0 = CUSTDIST_mCUSTOMER1_E1_1.get(x7)
    val l4 = CUSTDIST_mORDERS1_E1_4.get(x7)
    val x64 = 0L == Uregexp_match("^.*special.*requests.*$", x14)
    val x70 = x64 * l4
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) =>
      temp.add(v, (v != 0L) * 4)
      temp.add(v + (((x7 == k) * x64) * l4), v != 0L)
    }
    temp.add(l0, (x70 != 0L) * 2)
    temp.add(l0 + (x64 * l4), x70 != 0L)
    temp.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          var a:Long = 0L; CUSTDIST_mCUSTOMER1_E1_1.foreach((k2:Long,v2:Long) => a += (v2!=0L)*(v2==k)); a
        }) + v)
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(x7, x70)
    CUSTDIST_mCUSTOMER1_E1_3.add(x7, x64)
  }

  // unoptimized as not used
  def onDeleteCUSTOMER(x265: Long, x266: String, x267: String, x268: Long, x269: String, x270: Double, x271: String, x272: String): Unit = {
    val x279 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x280 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x281 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x281.add(v, v != 0L) }
    x281.foreach { case (k,v) => x280.add(k, v) }
    val x310 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x310.add(k, v) }
    val x325 = CUSTDIST_mCUSTOMER1_E1_3.get(x265) * -1L
    x310.add(x265, x325)
    val x330 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x310.foreach { case (k,v) => x330.add(CUSTDIST_mCUSTOMER1_E1_1.get(k), v != 0L) }
    x330.foreach { case (k,v) => x280.add(k, v) }
    x280.foreach { case (k,v) => x279.add(k,-v) }
    val x369 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x369.add(k, v) }
    x369.add(x265, x325)
    val x383 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x369.foreach { case (k,v) => x383.add(CUSTDIST_mCUSTOMER1_E1_1.get(k), v != 0L) }
    x383.foreach { case (k,v) => x279.add(k,v) }
    val x412 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x412.add(k, v) }
    x412.add(x265, x325)
    val x426 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x412.foreach { case (k,v) =>
      val x445 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + (((x265 == k) * CUSTDIST_mCUSTOMER1_E1_3.get(x265)) * -1L)
      x426.add(x445, v != 0L)
    }
    x426.foreach { case (k,v) => x279.add(k, v) }
    x279.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          var x470: Long = 0L
          CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k2,v2) => x470 += (v2 != 0L) * (v2 == k) }
          x470
        }) + v)
    }
    CUSTDIST_mORDERS1_E1_4.add(x265, -1L)
    CUSTDIST_mCUSTOMER1_E1_1.add(x265, x325)
  }

  def onInsertCUSTOMER(c_custkey: Long, x513: String, x514: String, x515: Long, x516: String, x517: Double, x518: String, x519: String): Unit = {
    val e = CUSTDIST_mCUSTOMER1_E1_3.get(c_custkey)

    // manually optimized version
    val tmp = M3Map.temp[Long, Long]()
    def gen(k:Long,v:Long) { val x=v+(k==c_custkey)*e; tmp.add(v,-(v!=0)); tmp.add(x,x!=0) }
    CUSTDIST_mCUSTOMER1_E1_1.foreach(gen)
    if (CUSTDIST_mCUSTOMER1_E1_1.get(c_custkey)==0L) gen(c_custkey,0L)
    tmp.foreach{ (k,v) =>
      if (CUSTDIST.get(k)==0L) CUSTDIST.set(k,{ var a:Long=0L; CUSTDIST_mCUSTOMER1_E1_1.foreach { (k2,v2) => a+=(v2!=0L)*(v2==k) }; a})
      CUSTDIST.add(k, v)
    }
    // XXX: for network, create a M3MapWrapper that executes remotely and contains code for executing locally, then chain responder for messages

    /*
    // (A + B) * -1 + C + D
    val x526 = M3Map.temp[Long, Long]()
    // (A + B)
    val x527 = M3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x527.add(v, v != 0L) }
    val x557 = M3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x557.add(k, v) }
    x557.add(c_custkey, e)
    x557.foreach { (k,v) => val x585 = CUSTDIST_mCUSTOMER1_E1_1.get(k); x527.add(x585, v != 0L) }
    x527.foreach { (k,v) => x526.add(k, v * -1L) }
    // C
    val x614 = M3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x614.add(k, v) }
    x614.add(c_custkey, e)
    x614.foreach { (k,v) => val x638 = CUSTDIST_mCUSTOMER1_E1_1.get(k); x526.add(x638, v != 0L) }
    // D
    val x657 = M3Map.temp[Long, Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k,v) => x657.add(k, v) }
    x657.add(c_custkey, e)
    x657.foreach { (k,v) =>
        val x689 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + ((c_custkey == k) * e)
        x526.add(x689, v != 0L)
    }
    // Update
    x526.foreach { (k,v) =>
      if (CUSTDIST.get(k)==0L) CUSTDIST.set(k, CUSTDIST_mCUSTOMER1_E1_1.aggr{ (k2,v2) =>(v2 != 0L) * (v2 == k)})
      CUSTDIST.add(k, v)
    }
    */

    CUSTDIST_mORDERS1_E1_4.add(c_custkey, 1L)
    CUSTDIST_mCUSTOMER1_E1_1.add(c_custkey, e)
  }
  /*
  CUSTDIST(int)[][C_ORDERS_C_COUNT]:(AggSum([C_ORDERS_C_COUNT],((Exists(CUSTDIST_mCUSTOMER1_E1_1(int)[][C_ORDERS_C_CUSTKEY]) * (C_ORDERS_C_COUNT ^= CUSTDIST_mCUSTOMER1_E1_1(int)[][C_ORDERS_C_CUSTKEY]))))) +=
  let k = C_ORDERS_C_CUSTKEY
  let v = CUSTDIST_mCUSTOMER1_E1_1(int)[][k]
  let e = CUSTDIST_mCUSTOMER1_E1_3(int)[][CUSTOMER_CUSTKEY]
  let x = v + ((k ^= CUSTOMER_CUSTKEY) * e))
  (((
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS(v) *
    (C_ORDERS_C_COUNT ^= v)))
  +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= v)))
  ) * -1) +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= v)))
  +
  AggSum([C_ORDERS_C_COUNT],
    (EXISTS((x) *
    (C_ORDERS_C_COUNT ^= x))
  );
  */

  // unoptimized as not used
  def onDeleteORDERS(x756: Long, x757: Long, x758: String, x759: Double, x760: Date, x761: String, x762: String, x763: Long, x764: String): Unit = {
    val x771 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x772 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    val x773 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x773.add(v, v != 0L) }
    x773.foreach { case (k,v) => x772.add(k, v) }
    val x802 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x802.add(k, v) }
    val x814 = 0L == Uregexp_match("^.*special.*requests.*$", x764)
    val x822 = (x814 * CUSTDIST_mORDERS1_E1_4.get(x757)) * -1L
    x802.add(x757, x822)
    val x827 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x802.foreach { case (k,v) =>
      val x837 = CUSTDIST_mCUSTOMER1_E1_1.get(k)
      x827.add(x837, v != 0L)
    }
    x827.foreach { case (k,v) => x772.add(k, v) }
    x772.foreach { case (k,v) => x771.add(k, v * -1L) }
    val x866 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x866.add(k, v) }
    x866.add(x757, x822)
    val x880 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x866.foreach { case (k,v) =>
      val x882 = k
      val x890 = CUSTDIST_mCUSTOMER1_E1_1.get(x882)
      x880.add(x890, v != 0L)
    }
    x880.foreach { case (k,v) => x771.add(k, v) }
    val x909 = M3Map.make[Long,Long]() // INTERMEDIATE_WITH_UPDATE
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k,v) => x909.add(k, v) }
    x909.add(x757, x822)
    val x923 = M3Map.make[Long,Long]() // GROUP_BY_AGGREGATE
    x909.foreach { case (k,v) =>
      val x943 = CUSTDIST_mCUSTOMER1_E1_1.get(k) + ((((x757 == k) * x814) * CUSTDIST_mORDERS1_E1_4.get(x757)) * -1L)
      x923.set(x943, ((x923.get(x943)) + (v != 0L)))
    }
    x923.foreach { case (k,v) => x771.add(k,v) }
    x771.foreach { case (k,v) =>
        CUSTDIST.set(k, (if (CUSTDIST.get(k)!=0) CUSTDIST.get(k) else {
          var x968: Long = 0L
          CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k2,v2) =>
              x968 += (v2 != 0L) * (v2 == k)
          }
          x968
        }) + v)
    }
    CUSTDIST_mCUSTOMER1_E1_1.set(x757, ((CUSTDIST_mCUSTOMER1_E1_1.get(x757)) + x822))
    CUSTDIST_mCUSTOMER1_E1_3.set(x757, ((CUSTDIST_mCUSTOMER1_E1_3.get(x757)) + (x814 * -1L)))
  }
}

// -----------------------------------------------------------------------------

/*
object TPCH13Gen extends Helper {
  def execute() = run[TPCH13Gen,Map[Long,Long]](Seq(
    (new java.io.FileInputStream("resources/data/tpch/orders.csv"),new Adaptor.CSV("ORDERS","long,long,string,double,date,string,string,long,string","\\Q|\\E"),Split()),
    (new java.io.FileInputStream("resources/data/tpch/customer.csv"),new Adaptor.CSV("CUSTOMER","long,string,string,long,string,double,string,string","\\Q|\\E"),Split())
  ))

  def main(args:Array[String]) {
    val res = bench("NewGen",10,execute)
    println(K3Helper.toStr(res))
  }
}
*/

class TPCH13Gen extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._

  val CUSTDIST = M3Map.make[Long,Long]();
  val CUSTDIST_mORDERS1_E1_4 = M3Map.make[Long,Long]();
  val CUSTDIST_mCUSTOMER1_E1_1 = M3Map.make[Long,Long]();
  val CUSTDIST_mCUSTOMER1_E1_3 = M3Map.make[Long,Long]();

  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onAddCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDelCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case SystemInit => onSystemReady(); t0=System.nanoTime()
    case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,List(CUSTDIST.toMap))
  }

  def onAddORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Date, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    val tmp_add1 = M3Map.temp[Long,Long]()
    val tmp_add2 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k3,v3) =>
      val c_orders_c_custkey = k3;
      val c_orders_c_count = v3;
      tmp_add2.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add3 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k5,v5) =>
      val c_orders_c_custkey = k5;
      tmp_add3.add(c_orders_c_custkey,v5)
    }
    tmp_add3.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * CUSTDIST_mORDERS1_E1_4.get(orders_custkey)))
    tmp_add3.foreach{ (k4,v4) =>
      val c_orders_c_custkey = k4
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add2.add(c_orders_c_count,(v4 != 0));
    }
    tmp_add2.foreach{ (k2,v2) =>
      val c_orders_c_count = k2
      tmp_add1.add(c_orders_c_count,(v2 * -1L))
    }
    val tmp_add4 = M3Map.temp[Long,Long]()
    val tmp_add5 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k8,v8) =>
      val c_orders_c_custkey = k8;
      tmp_add5.add(c_orders_c_custkey,v8)
    }
    tmp_add5.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * CUSTDIST_mORDERS1_E1_4.get(orders_custkey)))
    tmp_add5.foreach{ (k7,v7) =>
      val c_orders_c_custkey = k7
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add4.add(c_orders_c_count,(v7 != 0));
    }
    val tmp_add6 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k10,v10) =>
      val c_orders_c_custkey = k10;
      tmp_add6.add(c_orders_c_custkey,v10)
    }
    tmp_add6.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * CUSTDIST_mORDERS1_E1_4.get(orders_custkey)))
    tmp_add6.foreach{ (k9,v9) =>
      val c_orders_c_custkey = k9
      val c_orders_c_count = v9;
      tmp_add4.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    tmp_add4.foreach{ (k6,v6) =>
      val c_orders_c_count = k6
      tmp_add1.add(c_orders_c_count,v6)
    }
    tmp_add1.foreach{ (k1,v1) =>
      val c_orders_c_count = k1
      val tmp1 = M3Map.make[Long,Long]()
      CUSTDIST_mCUSTOMER1_E1_1.foreach { (k11,v11) =>
        val c_orders_c_custkey = k11;
        val c_orders_c_count1 = v11;
        if (c_orders_c_count == c_orders_c_count1) {
          tmp1.add(c_orders_c_count1,(c_orders_c_count1 != 0));
        }
      }
      if (CUSTDIST.get(c_orders_c_count)==0) CUSTDIST.set(c_orders_c_count,tmp1.get(c_orders_c_count));
      CUSTDIST.add(c_orders_c_count,v1);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * CUSTDIST_mORDERS1_E1_4.get(orders_custkey)));
    CUSTDIST_mCUSTOMER1_E1_3.add(orders_custkey,(0L == Uregexp_match("^.*special.*requests.*$",orders_comment)));
  }

  def onDelORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Date, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    val tmp_add7 = M3Map.temp[Long,Long]()
    val tmp_add8 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k14,v14) =>
      val c_orders_c_custkey = k14;
      val c_orders_c_count = v14;
      tmp_add8.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add9 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k16,v16) =>
      val c_orders_c_custkey = k16;
      tmp_add9.add(c_orders_c_custkey,v16)
    }
    tmp_add9.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * (CUSTDIST_mORDERS1_E1_4.get(orders_custkey) * -1L)))
    tmp_add9.foreach{ (k15,v15) =>
      val c_orders_c_custkey = k15
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add8.add(c_orders_c_count,(v15 != 0));
    }
    tmp_add8.foreach{ (k13,v13) =>
      val c_orders_c_count = k13
      tmp_add7.add(c_orders_c_count,(v13 * -1L))
    }
    val tmp_add10 = M3Map.temp[Long,Long]()
    val tmp_add11 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k19,v19) =>
      val c_orders_c_custkey = k19;
      tmp_add11.add(c_orders_c_custkey,v19)
    }
    tmp_add11.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * (CUSTDIST_mORDERS1_E1_4.get(orders_custkey) * -1L)))
    tmp_add11.foreach{ (k18,v18) =>
      val c_orders_c_custkey = k18
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add10.add(c_orders_c_count,(v18 != 0));
    }
    val tmp_add12 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k21,v21) =>
      val c_orders_c_custkey = k21;
      tmp_add12.add(c_orders_c_custkey,v21)
    }
    tmp_add12.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * (CUSTDIST_mORDERS1_E1_4.get(orders_custkey) * -1L)))
    tmp_add12.foreach{ (k20,v20) =>
      val c_orders_c_custkey = k20
      val c_orders_c_count = v20;
      tmp_add10.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    tmp_add10.foreach{ (k17,v17) =>
      val c_orders_c_count = k17
      tmp_add7.add(c_orders_c_count,v17)
    }
    tmp_add7.foreach{ (k12,v12) =>
      val c_orders_c_count = k12
      val tmp2 = M3Map.make[Long,Long]()
      CUSTDIST_mCUSTOMER1_E1_1.foreach { (k22,v22) =>
        val c_orders_c_custkey = k22;
        val c_orders_c_count2 = v22;
        if (c_orders_c_count == c_orders_c_count2) {
          tmp2.add(c_orders_c_count2,(c_orders_c_count2 != 0));
        }
      }
      if (CUSTDIST.get(c_orders_c_count)==0) CUSTDIST.set(c_orders_c_count,tmp2.get(c_orders_c_count));
      CUSTDIST.add(c_orders_c_count,v12);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * (CUSTDIST_mORDERS1_E1_4.get(orders_custkey) * -1L)));
    CUSTDIST_mCUSTOMER1_E1_3.add(orders_custkey,((0L == Uregexp_match("^.*special.*requests.*$",orders_comment)) * -1L));
  }

  def onAddCUSTOMER(customer_custkey:Long, customer_name:String, customer_address:String, customer_nationkey:Long, customer_phone:String, customer_acctbal:Double, customer_mktsegment:String, customer_comment:String) {
    val tmp_add13 = M3Map.temp[Long,Long]()
    val tmp_add14 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k25,v25) =>
      val c_orders_c_custkey = k25;
      val c_orders_c_count = v25;
      tmp_add14.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add15 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k27,v27) =>
      val c_orders_c_custkey = k27;
      tmp_add15.add(c_orders_c_custkey,v27)
    }
    tmp_add15.add(customer_custkey,CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey))
    tmp_add15.foreach{ (k26,v26) =>
      val c_orders_c_custkey = k26
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add14.add(c_orders_c_count,(v26 != 0));
    }
    tmp_add14.foreach{ (k24,v24) =>
      val c_orders_c_count = k24
      tmp_add13.add(c_orders_c_count,(v24 * -1L))
    }
    val tmp_add16 = M3Map.temp[Long,Long]()
    val tmp_add17 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k30,v30) =>
      val c_orders_c_custkey = k30;
      tmp_add17.add(c_orders_c_custkey,v30)
    }
    tmp_add17.add(customer_custkey,CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey))
    tmp_add17.foreach{ (k29,v29) =>
      val c_orders_c_custkey = k29
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add16.add(c_orders_c_count,(v29 != 0));
    }
    val tmp_add18 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k32,v32) =>
      val c_orders_c_custkey = k32;
      tmp_add18.add(c_orders_c_custkey,v32)
    }
    tmp_add18.add(customer_custkey,CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey))
    tmp_add18.foreach{ (k31,v31) =>
      val c_orders_c_custkey = k31
      val c_orders_c_count = v31;
      tmp_add16.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    tmp_add16.foreach{ (k28,v28) =>
      val c_orders_c_count = k28
      tmp_add13.add(c_orders_c_count,v28)
    }
    tmp_add13.foreach{ (k23,v23) =>
      val c_orders_c_count = k23
      val tmp3 = M3Map.make[Long,Long]()
      CUSTDIST_mCUSTOMER1_E1_1.foreach { (k33,v33) =>
        val c_orders_c_custkey = k33;
        val c_orders_c_count3 = v33;
        if (c_orders_c_count == c_orders_c_count3) {
          tmp3.add(c_orders_c_count3,(c_orders_c_count3 != 0));
        }
      }
      if (CUSTDIST.get(c_orders_c_count)==0) CUSTDIST.set(c_orders_c_count,tmp3.get(c_orders_c_count));
      CUSTDIST.add(c_orders_c_count,v23);
    }
    CUSTDIST_mORDERS1_E1_4.add(customer_custkey,1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(customer_custkey,CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey));
  }

  def onDelCUSTOMER(customer_custkey:Long, customer_name:String, customer_address:String, customer_nationkey:Long, customer_phone:String, customer_acctbal:Double, customer_mktsegment:String, customer_comment:String) {
    val tmp_add19 = M3Map.temp[Long,Long]()
    val tmp_add20 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k36,v36) =>
      val c_orders_c_custkey = k36;
      val c_orders_c_count = v36;
      tmp_add20.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add21 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k38,v38) =>
      val c_orders_c_custkey = k38;
      tmp_add21.add(c_orders_c_custkey,v38)
    }
    tmp_add21.add(customer_custkey,(CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey) * -1L))
    tmp_add21.foreach{ (k37,v37) =>
      val c_orders_c_custkey = k37
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add20.add(c_orders_c_count,(v37 != 0));
    }
    tmp_add20.foreach{ (k35,v35) =>
      val c_orders_c_count = k35
      tmp_add19.add(c_orders_c_count,(v35 * -1L))
    }
    val tmp_add22 = M3Map.temp[Long,Long]()
    val tmp_add23 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k41,v41) =>
      val c_orders_c_custkey = k41;
      tmp_add23.add(c_orders_c_custkey,v41)
    }
    tmp_add23.add(customer_custkey,(CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey) * -1L))
    tmp_add23.foreach{ (k40,v40) =>
      val c_orders_c_custkey = k40
      val c_orders_c_count = CUSTDIST_mCUSTOMER1_E1_1.get(c_orders_c_custkey);
      tmp_add22.add(c_orders_c_count,(v40 != 0));
    }
    val tmp_add24 = M3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k43,v43) =>
      val c_orders_c_custkey = k43;
      tmp_add24.add(c_orders_c_custkey,v43)
    }
    tmp_add24.add(customer_custkey,(CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey) * -1L))
    tmp_add24.foreach{ (k42,v42) =>
      val c_orders_c_custkey = k42
      val c_orders_c_count = v42;
      tmp_add22.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    tmp_add22.foreach{ (k39,v39) =>
      val c_orders_c_count = k39
      tmp_add19.add(c_orders_c_count,v39)
    }
    tmp_add19.foreach{ (k34,v34) =>
      val c_orders_c_count = k34
      val tmp4 = M3Map.make[Long,Long]()
      CUSTDIST_mCUSTOMER1_E1_1.foreach { (k44,v44) =>
        val c_orders_c_custkey = k44;
        val c_orders_c_count4 = v44;
        if (c_orders_c_count == c_orders_c_count4) {
          tmp4.add(c_orders_c_count4,(c_orders_c_count4 != 0));
        }
      }
      if (CUSTDIST.get(c_orders_c_count)==0) CUSTDIST.set(c_orders_c_count,tmp4.get(c_orders_c_count));
      CUSTDIST.add(c_orders_c_count,v34);
    }
    CUSTDIST_mORDERS1_E1_4.add(customer_custkey,-1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(customer_custkey,(CUSTDIST_mCUSTOMER1_E1_3.get(customer_custkey) * -1L));
  }

  def onSystemReady() {
  }
}

// -----------------------------------------------------------------------------

/*
import scala.collection.JavaConversions.mapAsScalaMap
import java.util.HashMap
import org.dbtoaster.dbtoasterlib.K3Collection._

class TPCH13Ref extends Actor {
  import Messages._
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onInsertORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDeleteORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onInsertCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDeleteCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,result.toMap)
  }

   val CUSTDIST = new K3PersistentCollection[(Long), Long]("CUSTDIST", new java.util.HashMap[(Long), Long], None); // == x2
   val CUSTDIST_mORDERS1_E1_4 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mORDERS1_E1_4", new java.util.HashMap[(Long), Long], None); // ==x3
   val CUSTDIST_mCUSTOMER1_E1_1 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mCUSTOMER1_E1_1", new java.util.HashMap[(Long), Long], None); // ==CUSTDIST_mCUSTOMER1_E1_1 
   val CUSTDIST_mCUSTOMER1_E1_3 = new K3PersistentCollection[(Long), Long]("CUSTDIST_mCUSTOMER1_E1_3", new java.util.HashMap[(Long), Long], None); // ==x5
   def result:Map[Long,Long] = CUSTDIST.elems.toMap

   def onInsertORDERS(x6: Long, x7: Long, x8: String, x9: Double, x10: Date, x11: String, x12: String, x13: Long, x14: String): Unit = {
      val x17 = CUSTDIST // mutable K3PersistentCollection
      val x18 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x19 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x20 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x21 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x22 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x23 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x19.foreach {
         x24 =>
            val x25 = x24._1
            val x33 = x19.lookup(x25, 0L)
            x23.updateValue(x33, ((x23.lookup(x33, 0L)) + ((x24._2) != 0L)))
      }
      x23.foreach {
         x44 =>
            val x45 = x44._1
            x22.updateValue(x45, ((x22.lookup(x45, 0)) + (x44._2)))
      }
      val x52 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x53 =>
            val x54 = x53._1
            x52.updateValue(x54, ((x52.lookup(x54, 0)) + (x53._2)))
      }
      val x64 = if ((0L == (regexp_match("^.*special.*requests.*$", x14)))) {
         1L
      } else {
         0L
      }
      val x70 = x64 * (x18.lookup(x7, 0L))
      x52.updateValue(x7, ((x52.lookup(x7, 0)) + x70))
      val x75 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x52.foreach {
         x76 =>
            val x77 = x76._1
            val x85 = x19.lookup(x77, 0L)
            x75.updateValue(x85, ((x75.lookup(x85, 0L)) + ((x76._2) != 0L)))
      }
      x75.foreach {
         x96 =>
            val x97 = x96._1
            x22.updateValue(x97, ((x22.lookup(x97, 0)) + (x96._2)))
      }
      x22.foreach {
         x104 =>
            val x105 = x104._1
            x21.updateValue(x105, ((x21.lookup(x105, 0)) + ((x104._2) * -1L)))
      }
      val x114 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x115 =>
            val x116 = x115._1
            x114.updateValue(x116, ((x114.lookup(x116, 0)) + (x115._2)))
      }
      x114.updateValue(x7, ((x114.lookup(x7, 0)) + x70))
      val x128 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x114.foreach {
         x129 =>
            val x130 = x129._1
            val x138 = x19.lookup(x130, 0L)
            x128.updateValue(x138, ((x128.lookup(x138, 0L)) + ((x129._2) != 0L)))
      }
      x128.foreach {
         x149 =>
            val x150 = x149._1
            x21.updateValue(x150, ((x21.lookup(x150, 0)) + (x149._2)))
      }
      val x157 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x19.foreach {
         x158 =>
            val x159 = x158._1
            x157.updateValue(x159, ((x157.lookup(x159, 0)) + (x158._2)))
      }
      x157.updateValue(x7, ((x157.lookup(x7, 0)) + x70))
      val x171 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x157.foreach {
         x172 =>
            val x173 = x172._1
            val x190 = (x19.lookup(x173, 0L)) + (((x7 == x173) * x64) * (x18.lookup(x7, 0L)))
            x171.updateValue(x190, ((x171.lookup(x190, 0L)) + ((x172._2) != 0L)))
      }
      x171.foreach {
         x201 =>
            val x202 = x201._1
            x21.updateValue(x202, ((x21.lookup(x202, 0)) + (x201._2)))
      }
      x21.foreach {
         x209 =>
            val x210 = x209._1
            x17.updateValue(x210, ((if ((x17.contains(x210))) {
               (x17.lookup(x210, 0))
            } else {
               var x215: Long = 0L
               x19.foreach {
                  x216 =>
                     val x217 = x216._1
                     x215 = ((x215) + (((x216._2) != 0L) * ((x19.lookup(x217, 0L)) == x210)))
               }
               (x215)
            }) + (x209._2)))
      }
      x19.updateValue(x7, ((x19.lookup(x7, 0L)) + x70))
      x20.updateValue(x7, ((x20.lookup(x7, 0L)) + x64))
      ()
   }

   def onDeleteCUSTOMER(x265: Long, x266: String, x267: String, x268: Long, x269: String, x270: Double, x271: String, x272: String): Unit = {
      val x275 = CUSTDIST // mutable K3PersistentCollection
      val x276 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x277 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x278 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x279 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x280 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x281 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x277.foreach {
         x282 =>
            val x283 = x282._1
            val x291 = x277.lookup(x283, 0L)
            x281.updateValue(x291, ((x281.lookup(x291, 0L)) + ((x282._2) != 0L)))
      }
      x281.foreach {
         x302 =>
            val x303 = x302._1
            x280.updateValue(x303, ((x280.lookup(x303, 0)) + (x302._2)))
      }
      val x310 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x311 =>
            val x312 = x311._1
            x310.updateValue(x312, ((x310.lookup(x312, 0)) + (x311._2)))
      }
      val x325 = (x278.lookup(x265, 0L)) * -1L
      x310.updateValue(x265, ((x310.lookup(x265, 0)) + x325))
      val x330 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x310.foreach {
         x331 =>
            val x332 = x331._1
            val x340 = x277.lookup(x332, 0L)
            x330.updateValue(x340, ((x330.lookup(x340, 0L)) + ((x331._2) != 0L)))
      }
      x330.foreach {
         x351 =>
            val x352 = x351._1
            x280.updateValue(x352, ((x280.lookup(x352, 0)) + (x351._2)))
      }
      x280.foreach {
         x359 =>
            val x360 = x359._1
            x279.updateValue(x360, ((x279.lookup(x360, 0)) + ((x359._2) * -1L)))
      }
      val x369 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x370 =>
            val x371 = x370._1
            x369.updateValue(x371, ((x369.lookup(x371, 0)) + (x370._2)))
      }
      x369.updateValue(x265, ((x369.lookup(x265, 0)) + x325))
      val x383 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x369.foreach {
         x384 =>
            val x385 = x384._1
            val x393 = x277.lookup(x385, 0L)
            x383.updateValue(x393, ((x383.lookup(x393, 0L)) + ((x384._2) != 0L)))
      }
      x383.foreach {
         x404 =>
            val x405 = x404._1
            x279.updateValue(x405, ((x279.lookup(x405, 0)) + (x404._2)))
      }
      val x412 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x277.foreach {
         x413 =>
            val x414 = x413._1
            x412.updateValue(x414, ((x412.lookup(x414, 0)) + (x413._2)))
      }
      x412.updateValue(x265, ((x412.lookup(x265, 0)) + x325))
      val x426 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x412.foreach {
         x427 =>
            val x428 = x427._1
            val x445 = (x277.lookup(x428, 0L)) + (((x265 == x428) * (x278.lookup(x265, 0L))) * -1L)
            x426.updateValue(x445, ((x426.lookup(x445, 0L)) + ((x427._2) != 0L)))
      }
      x426.foreach {
         x456 =>
            val x457 = x456._1
            x279.updateValue(x457, ((x279.lookup(x457, 0)) + (x456._2)))
      }
      x279.foreach {
         x464 =>
            val x465 = x464._1
            x275.updateValue(x465, ((if ((x275.contains(x465))) {
               (x275.lookup(x465, 0))
            } else {
               var x470: Long = 0L
               x277.foreach {
                  x471 =>
                     val x472 = x471._1
                     x470 = ((x470) + (((x471._2) != 0L) * ((x277.lookup(x472, 0L)) == x465)))
               }
               (x470)
            }) + (x464._2)))
      }
      x276.updateValue(x265, ((x276.lookup(x265, 0L)) + -1L))
      x277.updateValue(x265, ((x277.lookup(x265, 0L)) + x325))
   }

   def onInsertCUSTOMER(x512: Long, x513: String, x514: String, x515: Long, x516: String, x517: Double, x518: String, x519: String): Unit = {
      val x522 = CUSTDIST // mutable K3PersistentCollection
      val x523 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x524 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x525 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x526 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x527 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x528 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x524.foreach {
         x529 =>
            val x530 = x529._1
            val x538 = x524.lookup(x530, 0L)
            x528.updateValue(x538, ((x528.lookup(x538, 0L)) + ((x529._2) != 0L)))
      }
      x528.foreach {
         x549 =>
            val x550 = x549._1
            x527.updateValue(x550, ((x527.lookup(x550, 0)) + (x549._2)))
      }
      val x557 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x558 =>
            val x559 = x558._1
            x557.updateValue(x559, ((x557.lookup(x559, 0)) + (x558._2)))
      }
      val x570 = x525.lookup(x512, 0L)
      x557.updateValue(x512, ((x557.lookup(x512, 0)) + x570))
      val x575 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x557.foreach {
         x576 =>
            val x577 = x576._1
            val x585 = x524.lookup(x577, 0L)
            x575.updateValue(x585, ((x575.lookup(x585, 0L)) + ((x576._2) != 0L)))
      }
      x575.foreach {
         x596 =>
            val x597 = x596._1
            x527.updateValue(x597, ((x527.lookup(x597, 0)) + (x596._2)))
      }
      x527.foreach {
         x604 =>
            val x605 = x604._1
            x526.updateValue(x605, ((x526.lookup(x605, 0)) + ((x604._2) * -1L)))
      }
      val x614 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x615 =>
            val x616 = x615._1
            x614.updateValue(x616, ((x614.lookup(x616, 0)) + (x615._2)))
      }
      x614.updateValue(x512, ((x614.lookup(x512, 0)) + x570))
      val x628 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x614.foreach {
         x629 =>
            val x630 = x629._1
            val x638 = x524.lookup(x630, 0L)
            x628.updateValue(x638, ((x628.lookup(x638, 0L)) + ((x629._2) != 0L)))
      }
      x628.foreach {
         x649 =>
            val x650 = x649._1
            x526.updateValue(x650, ((x526.lookup(x650, 0)) + (x649._2)))
      }
      val x657 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x524.foreach {
         x658 =>
            val x659 = x658._1
            x657.updateValue(x659, ((x657.lookup(x659, 0)) + (x658._2)))
      }
      x657.updateValue(x512, ((x657.lookup(x512, 0)) + x570))
      val x671 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x657.foreach {
         x672 =>
            val x673 = x672._1
            val x689 = (x524.lookup(x673, 0L)) + ((x512 == x673) * (x525.lookup(x512, 0L)))
            x671.updateValue(x689, ((x671.lookup(x689, 0L)) + ((x672._2) != 0L)))
      }
      x671.foreach {
         x700 =>
            val x701 = x700._1
            x526.updateValue(x701, ((x526.lookup(x701, 0)) + (x700._2)))
      }
      x526.foreach {
         x708 =>
            val x709 = x708._1
            x522.updateValue(x709, ((if ((x522.contains(x709))) {
               (x522.lookup(x709, 0))
            } else {
               var x714: Long = 0L
               x524.foreach {
                  x715 =>
                     val x716 = x715._1
                     x714 = ((x714) + (((x715._2) != 0L) * ((x524.lookup(x716, 0L)) == x709)))
               }
               (x714)
            }) + (x708._2)))
      }
      x523.updateValue(x512, ((x523.lookup(x512, 0L)) + 1L))
      x524.updateValue(x512, ((x524.lookup(x512, 0L)) + x570))
   }

   def onDeleteORDERS(x756: Long, x757: Long, x758: String, x759: Double, x760: Date, x761: String, x762: String, x763: Long, x764: String): Unit = {
      val x767 = CUSTDIST // mutable K3PersistentCollection
      val x768 = CUSTDIST_mORDERS1_E1_4 // mutable K3PersistentCollection
      val x769 = CUSTDIST_mCUSTOMER1_E1_1 // mutable K3PersistentCollection
      val x770 = CUSTDIST_mCUSTOMER1_E1_3 // mutable K3PersistentCollection
      val x771 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x772 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      val x773 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x769.foreach {
         x774 =>
            val x775 = x774._1
            val x783 = x769.lookup(x775, 0L)
            x773.updateValue(x783, ((x773.lookup(x783, 0L)) + ((x774._2) != 0L)))
      }
      x773.foreach {
         x794 =>
            val x795 = x794._1
            x772.updateValue(x795, ((x772.lookup(x795, 0)) + (x794._2)))
      }
      val x802 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x803 =>
            val x804 = x803._1
            x802.updateValue(x804, ((x802.lookup(x804, 0)) + (x803._2)))
      }
      val x814 = if ((0L == (regexp_match("^.*special.*requests.*$", x764)))) {
         1L
      } else {
         0L
      }
      val x822 = (x814 * (x768.lookup(x757, 0L))) * -1L
      x802.updateValue(x757, ((x802.lookup(x757, 0)) + x822))
      val x827 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x802.foreach {
         x828 =>
            val x829 = x828._1
            val x837 = x769.lookup(x829, 0L)
            x827.updateValue(x837, ((x827.lookup(x837, 0L)) + ((x828._2) != 0L)))
      }
      x827.foreach {
         x848 =>
            val x849 = x848._1
            x772.updateValue(x849, ((x772.lookup(x849, 0)) + (x848._2)))
      }
      x772.foreach {
         x856 =>
            val x857 = x856._1
            x771.updateValue(x857, ((x771.lookup(x857, 0)) + ((x856._2) * -1L)))
      }
      val x866 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x867 =>
            val x868 = x867._1
            x866.updateValue(x868, ((x866.lookup(x868, 0)) + (x867._2)))
      }
      x866.updateValue(x757, ((x866.lookup(x757, 0)) + x822))
      val x880 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x866.foreach {
         x881 =>
            val x882 = x881._1
            val x890 = x769.lookup(x882, 0L)
            x880.updateValue(x890, ((x880.lookup(x890, 0L)) + ((x881._2) != 0L)))
      }
      x880.foreach {
         x901 =>
            val x902 = x901._1
            x771.updateValue(x902, ((x771.lookup(x902, 0)) + (x901._2)))
      }
      val x909 = new K3PersistentCollection[Long, Long]("INTERMEDIATE_WITH_UPDATE", new HashMap[Long, Long], None)
      x769.foreach {
         x910 =>
            val x911 = x910._1
            x909.updateValue(x911, ((x909.lookup(x911, 0)) + (x910._2)))
      }
      x909.updateValue(x757, ((x909.lookup(x757, 0)) + x822))
      val x923 = new K3PersistentCollection[Long, Long]("GROUP_BY_AGGREGATE", new HashMap[Long, Long], None)
      x909.foreach {
         x924 =>
            val x925 = x924._1
            val x943 = (x769.lookup(x925, 0L)) + ((((x757 == x925) * x814) * (x768.lookup(x757, 0L))) * -1L)
            x923.updateValue(x943, ((x923.lookup(x943, 0L)) + ((x924._2) != 0L)))
      }
      x923.foreach {
         x954 =>
            val x955 = x954._1
            x771.updateValue(x955, ((x771.lookup(x955, 0)) + (x954._2)))
      }
      x771.foreach {
         x962 =>
            val x963 = x962._1
            x767.updateValue(x963, ((if ((x767.contains(x963))) {
               (x767.lookup(x963, 0))
            } else {
               var x968: Long = 0L
               x769.foreach {
                  x969 =>
                     val x970 = x969._1
                     x968 = ((x968) + (((x969._2) != 0L) * ((x769.lookup(x970, 0L)) == x963)))
               }
               (x968)
            }) + (x962._2)))
      }
      x769.updateValue(x757, ((x769.lookup(x757, 0L)) + x822))
      x770.updateValue(x757, ((x770.lookup(x757, 0L)) + (x814 * -1L)))
   }
}
*/
