package examples
import akka.actor.Actor
import ddbt.lib._
import java.util.Date

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
  
  
  def onAddORDERS(ORDERS_ORDERKEY:Long, ORDERS_CUSTKEY:Long, ORDERS_ORDERSTATUS:String, ORDERS_TOTALPRICE:Double, ORDERS_ORDERDATE:Date, ORDERS_ORDERPRIORITY:String, ORDERS_CLERK:String, ORDERS_SHIPPRIORITY:Long, ORDERS_COMMENT:String) {
    val tmp_add1 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add2 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k3,v3) =>
      val C_ORDERS_C_CUSTKEY = k3;
      val C_ORDERS_C_COUNT = v3;
      tmp_add2.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    val tmp_add3 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k5,v5) =>
      val C_ORDERS_C_CUSTKEY = k5;
      tmp_add3.add(C_ORDERS_C_CUSTKEY,v5)
    }
    tmp_add3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add3.foreach{ (k4,v4) =>
      val C_ORDERS_C_CUSTKEY = k4
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add2.add(C_ORDERS_C_COUNT,(v4 != 0));
    }
    tmp_add2.foreach{ (k2,v2) =>
      val C_ORDERS_C_COUNT = k2
      tmp_add1.add(C_ORDERS_C_COUNT,(v2 * -1L))
    }
    val tmp_add4 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add5 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k8,v8) =>
      val C_ORDERS_C_CUSTKEY = k8;
      tmp_add5.add(C_ORDERS_C_CUSTKEY,v8)
    }
    tmp_add5.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add5.foreach{ (k7,v7) =>
      val C_ORDERS_C_CUSTKEY = k7
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add4.add(C_ORDERS_C_COUNT,(v7 != 0));
    }
    val tmp_add6 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k10,v10) =>
      val C_ORDERS_C_CUSTKEY = k10;
      tmp_add6.add(C_ORDERS_C_CUSTKEY,v10)
    }
    tmp_add6.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add6.foreach{ (k9,v9) =>
      val C_ORDERS_C_CUSTKEY = k9
      val C_ORDERS_C_COUNT = v9;
      tmp_add4.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    tmp_add4.foreach{ (k6,v6) =>
      val C_ORDERS_C_COUNT = k6
      tmp_add1.add(C_ORDERS_C_COUNT,v6)
    }
    tmp_add1.foreach{ (k1,v1) =>
      val C_ORDERS_C_COUNT = k1
      val tmp1 = K3Map.make[Long,Long]() // XXX: fix types
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k11,v11) =>
        val C_ORDERS_C_CUSTKEY = k11;
        val C_ORDERS_C_COUNT1 = v11;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT1) {
          tmp1.add(C_ORDERS_C_COUNT1,(C_ORDERS_C_COUNT1 != 0));
        }
      }
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp1.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v1);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)));
    CUSTDIST_mCUSTOMER1_E1_3.add(ORDERS_CUSTKEY,(0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)));
  }
  
  def onDelORDERS(ORDERS_ORDERKEY:Long, ORDERS_CUSTKEY:Long, ORDERS_ORDERSTATUS:String, ORDERS_TOTALPRICE:Double, ORDERS_ORDERDATE:Date, ORDERS_ORDERPRIORITY:String, ORDERS_CLERK:String, ORDERS_SHIPPRIORITY:Long, ORDERS_COMMENT:String) {
    val tmp_add7 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add8 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k14,v14) =>
      val C_ORDERS_C_CUSTKEY = k14;
      val C_ORDERS_C_COUNT = v14;
      tmp_add8.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    val tmp_add9 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k16,v16) =>
      val C_ORDERS_C_CUSTKEY = k16;
      tmp_add9.add(C_ORDERS_C_CUSTKEY,v16)
    }
    tmp_add9.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add9.foreach{ (k15,v15) =>
      val C_ORDERS_C_CUSTKEY = k15
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add8.add(C_ORDERS_C_COUNT,(v15 != 0));
    }
    tmp_add8.foreach{ (k13,v13) =>
      val C_ORDERS_C_COUNT = k13
      tmp_add7.add(C_ORDERS_C_COUNT,(v13 * -1L))
    }
    val tmp_add10 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add11 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k19,v19) =>
      val C_ORDERS_C_CUSTKEY = k19;
      tmp_add11.add(C_ORDERS_C_CUSTKEY,v19)
    }
    tmp_add11.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add11.foreach{ (k18,v18) =>
      val C_ORDERS_C_CUSTKEY = k18
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add10.add(C_ORDERS_C_COUNT,(v18 != 0));
    }
    val tmp_add12 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k21,v21) =>
      val C_ORDERS_C_CUSTKEY = k21;
      tmp_add12.add(C_ORDERS_C_CUSTKEY,v21)
    }
    tmp_add12.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add12.foreach{ (k20,v20) =>
      val C_ORDERS_C_CUSTKEY = k20
      val C_ORDERS_C_COUNT = v20;
      tmp_add10.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    tmp_add10.foreach{ (k17,v17) =>
      val C_ORDERS_C_COUNT = k17
      tmp_add7.add(C_ORDERS_C_COUNT,v17)
    }
    tmp_add7.foreach{ (k12,v12) =>
      val C_ORDERS_C_COUNT = k12
      val tmp2 = K3Map.make[Long,Long]() // XXX: fix types
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k22,v22) =>
        val C_ORDERS_C_CUSTKEY = k22;
        val C_ORDERS_C_COUNT2 = v22;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT2) {
          tmp2.add(C_ORDERS_C_COUNT2,(C_ORDERS_C_COUNT2 != 0));
        }
      }
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp2.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v12);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)));
    CUSTDIST_mCUSTOMER1_E1_3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * -1L));
  }
  
  def onAddCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add13 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add14 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k25,v25) =>
      val C_ORDERS_C_CUSTKEY = k25;
      val C_ORDERS_C_COUNT = v25;
      tmp_add14.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    val tmp_add15 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k27,v27) =>
      val C_ORDERS_C_CUSTKEY = k27;
      tmp_add15.add(C_ORDERS_C_CUSTKEY,v27)
    }
    tmp_add15.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add15.foreach{ (k26,v26) =>
      val C_ORDERS_C_CUSTKEY = k26
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add14.add(C_ORDERS_C_COUNT,(v26 != 0));
    }
    tmp_add14.foreach{ (k24,v24) =>
      val C_ORDERS_C_COUNT = k24
      tmp_add13.add(C_ORDERS_C_COUNT,(v24 * -1L))
    }
    val tmp_add16 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add17 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k30,v30) =>
      val C_ORDERS_C_CUSTKEY = k30;
      tmp_add17.add(C_ORDERS_C_CUSTKEY,v30)
    }
    tmp_add17.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add17.foreach{ (k29,v29) =>
      val C_ORDERS_C_CUSTKEY = k29
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add16.add(C_ORDERS_C_COUNT,(v29 != 0));
    }
    val tmp_add18 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k32,v32) =>
      val C_ORDERS_C_CUSTKEY = k32;
      tmp_add18.add(C_ORDERS_C_CUSTKEY,v32)
    }
    tmp_add18.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add18.foreach{ (k31,v31) =>
      val C_ORDERS_C_CUSTKEY = k31
      val C_ORDERS_C_COUNT = v31;
      tmp_add16.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    tmp_add16.foreach{ (k28,v28) =>
      val C_ORDERS_C_COUNT = k28
      tmp_add13.add(C_ORDERS_C_COUNT,v28)
    }
    tmp_add13.foreach{ (k23,v23) =>
      val C_ORDERS_C_COUNT = k23
      val tmp3 = K3Map.make[Long,Long]() // XXX: fix types
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k33,v33) =>
        val C_ORDERS_C_CUSTKEY = k33;
        val C_ORDERS_C_COUNT3 = v33;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT3) {
          tmp3.add(C_ORDERS_C_COUNT3,(C_ORDERS_C_COUNT3 != 0));
        }
      }
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp3.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v23);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY));
  }
  
  def onDelCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add19 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add20 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k36,v36) =>
      val C_ORDERS_C_CUSTKEY = k36;
      val C_ORDERS_C_COUNT = v36;
      tmp_add20.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    val tmp_add21 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k38,v38) =>
      val C_ORDERS_C_CUSTKEY = k38;
      tmp_add21.add(C_ORDERS_C_CUSTKEY,v38)
    }
    tmp_add21.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add21.foreach{ (k37,v37) =>
      val C_ORDERS_C_CUSTKEY = k37
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add20.add(C_ORDERS_C_COUNT,(v37 != 0));
    }
    tmp_add20.foreach{ (k35,v35) =>
      val C_ORDERS_C_COUNT = k35
      tmp_add19.add(C_ORDERS_C_COUNT,(v35 * -1L))
    }
    val tmp_add22 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add23 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k41,v41) =>
      val C_ORDERS_C_CUSTKEY = k41;
      tmp_add23.add(C_ORDERS_C_CUSTKEY,v41)
    }
    tmp_add23.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add23.foreach{ (k40,v40) =>
      val C_ORDERS_C_CUSTKEY = k40
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp_add22.add(C_ORDERS_C_COUNT,(v40 != 0));
    }
    val tmp_add24 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k43,v43) =>
      val C_ORDERS_C_CUSTKEY = k43;
      tmp_add24.add(C_ORDERS_C_CUSTKEY,v43)
    }
    tmp_add24.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add24.foreach{ (k42,v42) =>
      val C_ORDERS_C_CUSTKEY = k42
      val C_ORDERS_C_COUNT = v42;
      tmp_add22.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    tmp_add22.foreach{ (k39,v39) =>
      val C_ORDERS_C_COUNT = k39
      tmp_add19.add(C_ORDERS_C_COUNT,v39)
    }
    tmp_add19.foreach{ (k34,v34) =>
      val C_ORDERS_C_COUNT = k34
      val tmp4 = K3Map.make[Long,Long]() // XXX: fix types
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k44,v44) =>
        val C_ORDERS_C_CUSTKEY = k44;
        val C_ORDERS_C_COUNT4 = v44;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT4) {
          tmp4.add(C_ORDERS_C_COUNT4,(C_ORDERS_C_COUNT4 != 0));
        }
      }
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp4.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v34);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,-1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L));
  }
  
  def onSystemReady() {
    
  }
}
