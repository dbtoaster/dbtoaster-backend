package examples // <-- only this line has been manually added

import ddbt.lib._
import akka.actor.Actor
import java.util.Date

object TPCH13Gen extends Helper {
  def main(args:Array[String]) {
    val res = bench("NewGen",10,()=>run[TPCH13Gen,Long,Long](Seq(
      (new java.io.FileInputStream("resources/data/tpch/orders.csv"),new Adaptor.CSV("ORDERS","long,long,string,double,date,string,string,long,string","\\Q|\\E"),Split()),
      (new java.io.FileInputStream("resources/data/tpch/customer.csv"),new Adaptor.CSV("CUSTOMER","long,string,string,long,string,double,string,string","\\Q|\\E"),Split())
    )))
    println(K3Helper.toStr(res))
  }
}

class TPCH13Gen extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._
  
  val CUSTDIST = K3Map.make[Long,Long]();
  val CUSTDIST_mORDERS1_E1_4 = K3Map.make[Long,Long]();
  val CUSTDIST_mCUSTOMER1_E1_1 = K3Map.make[Long,Long]();
  val CUSTDIST_mCUSTOMER1_E1_3 = K3Map.make[Long,Long]();
  
  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onAddORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleDelete,"ORDERS",tx,List(v0:Long,v1:Long,v2:String,v3:Double,v4:Date,v5:String,v6:String,v7:Long,v8:String)) => onDelORDERS(v0,v1,v2,v3,v4,v5,v6,v7,v8)
    case TupleEvent(TupleInsert,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onAddCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case TupleEvent(TupleDelete,"CUSTOMER",tx,List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String,v7:String)) => onDelCUSTOMER(v0,v1,v2,v3,v4,v5,v6,v7)
    case SystemInit => onSystemReady(); t0=System.nanoTime()
    case EndOfStream => val time=System.nanoTime()-t0; sender ! (time,result)
  }
  
  def result = CUSTDIST.toMap
  
  
  def onAddORDERS(orders_orderkey:Long, orders_custkey:Long, orders_orderstatus:String, orders_totalprice:Double, orders_orderdate:Date, orders_orderpriority:String, orders_clerk:String, orders_shippriority:Long, orders_comment:String) {
    val tmp_add1 = K3Map.temp[Long,Long]()
    val tmp_add2 = K3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k3,v3) =>
      val c_orders_c_custkey = k3;
      val c_orders_c_count = v3;
      tmp_add2.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add3 = K3Map.temp[Long,Long]()
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
    val tmp_add4 = K3Map.temp[Long,Long]()
    val tmp_add5 = K3Map.temp[Long,Long]()
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
    val tmp_add6 = K3Map.temp[Long,Long]()
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
      val tmp1 = K3Map.make[Long,Long]()
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
    val tmp_add7 = K3Map.temp[Long,Long]()
    val tmp_add8 = K3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k14,v14) =>
      val c_orders_c_custkey = k14;
      val c_orders_c_count = v14;
      tmp_add8.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add9 = K3Map.temp[Long,Long]()
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
    val tmp_add10 = K3Map.temp[Long,Long]()
    val tmp_add11 = K3Map.temp[Long,Long]()
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
    val tmp_add12 = K3Map.temp[Long,Long]()
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
      val tmp2 = K3Map.make[Long,Long]()
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
    val tmp_add13 = K3Map.temp[Long,Long]()
    val tmp_add14 = K3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k25,v25) =>
      val c_orders_c_custkey = k25;
      val c_orders_c_count = v25;
      tmp_add14.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add15 = K3Map.temp[Long,Long]()
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
    val tmp_add16 = K3Map.temp[Long,Long]()
    val tmp_add17 = K3Map.temp[Long,Long]()
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
    val tmp_add18 = K3Map.temp[Long,Long]()
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
      val tmp3 = K3Map.make[Long,Long]()
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
    val tmp_add19 = K3Map.temp[Long,Long]()
    val tmp_add20 = K3Map.temp[Long,Long]()
    CUSTDIST_mCUSTOMER1_E1_1.foreach { (k36,v36) =>
      val c_orders_c_custkey = k36;
      val c_orders_c_count = v36;
      tmp_add20.add(c_orders_c_count,(c_orders_c_count != 0));
    }
    val tmp_add21 = K3Map.temp[Long,Long]()
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
    val tmp_add22 = K3Map.temp[Long,Long]()
    val tmp_add23 = K3Map.temp[Long,Long]()
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
    val tmp_add24 = K3Map.temp[Long,Long]()
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
      val tmp4 = K3Map.make[Long,Long]()
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
