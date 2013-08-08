package examples
import akka.actor.Actor
import ddbt.lib._
import java.util.Date

class TPCH13Gen extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._
  
  val CUSTDIST = K3Map.make[Long,Long](Nil);
  val CUSTDIST_mORDERS1_E1_4 = K3Map.make[Long,Long](Nil);
  val CUSTDIST_mCUSTOMER1_E1_1 = K3Map.make[Long,Long](Nil);
  val CUSTDIST_mCUSTOMER1_E1_3 = K3Map.make[Long,Long](Nil);
  
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
    val tmp1 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp1 (ks = List(C_ORDERS_C_COUNT))
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k3,v3) =>
      val C_ORDERS_C_CUSTKEY = k3;
      val C_ORDERS_C_COUNT = v3;
      tmp1.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp1
    tmp1.foreach { case (k4,v4) =>
      val C_ORDERS_C_COUNT = k4;
      tmp_add2.add(C_ORDERS_C_COUNT,v4)
    }
    val tmp2 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp2 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add3 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k6,v6) =>
      val C_ORDERS_C_CUSTKEY = k6;
      tmp_add3.add(C_ORDERS_C_CUSTKEY,v6)
    }
    tmp_add3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add3.foreach{ (k5,v5) =>
      val C_ORDERS_C_CUSTKEY = k5
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp2.add(C_ORDERS_C_COUNT,(v5 != 0));
    }
    // using tmp2
    tmp2.foreach { case (k7,v7) =>
      val C_ORDERS_C_COUNT = k7;
      tmp_add2.add(C_ORDERS_C_COUNT,v7)
    }
    tmp_add2.foreach{ (k2,v2) =>
      val C_ORDERS_C_COUNT = k2
      tmp_add1.add(C_ORDERS_C_COUNT,(v2 * -1L))
    }
    val tmp_add4 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp3 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp3 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add5 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k10,v10) =>
      val C_ORDERS_C_CUSTKEY = k10;
      tmp_add5.add(C_ORDERS_C_CUSTKEY,v10)
    }
    tmp_add5.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add5.foreach{ (k9,v9) =>
      val C_ORDERS_C_CUSTKEY = k9
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp3.add(C_ORDERS_C_COUNT,(v9 != 0));
    }
    // using tmp3
    tmp3.foreach { case (k11,v11) =>
      val C_ORDERS_C_COUNT = k11;
      tmp_add4.add(C_ORDERS_C_COUNT,v11)
    }
    val tmp4 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp4 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add6 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k13,v13) =>
      val C_ORDERS_C_CUSTKEY = k13;
      tmp_add6.add(C_ORDERS_C_CUSTKEY,v13)
    }
    tmp_add6.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add6.foreach{ (k12,v12) =>
      val C_ORDERS_C_CUSTKEY = k12
      val C_ORDERS_C_COUNT = v12;
      tmp4.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp4
    tmp4.foreach { case (k14,v14) =>
      val C_ORDERS_C_COUNT = k14;
      tmp_add4.add(C_ORDERS_C_COUNT,v14)
    }
    tmp_add4.foreach{ (k8,v8) =>
      val C_ORDERS_C_COUNT = k8
      tmp_add1.add(C_ORDERS_C_COUNT,v8)
    }
    tmp_add1.foreach{ (k1,v1) =>
      val C_ORDERS_C_COUNT = k1
      val tmp5 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp5 (ks = List(C_ORDERS_C_COUNT))
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k15,v15) =>
        val C_ORDERS_C_CUSTKEY = k15;
        val C_ORDERS_C_COUNT1 = v15;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT1) {
          tmp5.add(C_ORDERS_C_COUNT1,(C_ORDERS_C_COUNT1 != 0));
        }
      }
      // using tmp5
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp5.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v1);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)));
    CUSTDIST_mCUSTOMER1_E1_3.add(ORDERS_CUSTKEY,(0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)));
  }
  
  def onDelORDERS(ORDERS_ORDERKEY:Long, ORDERS_CUSTKEY:Long, ORDERS_ORDERSTATUS:String, ORDERS_TOTALPRICE:Double, ORDERS_ORDERDATE:Date, ORDERS_ORDERPRIORITY:String, ORDERS_CLERK:String, ORDERS_SHIPPRIORITY:Long, ORDERS_COMMENT:String) {
    val tmp_add7 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add8 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp6 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp6 (ks = List(C_ORDERS_C_COUNT))
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k18,v18) =>
      val C_ORDERS_C_CUSTKEY = k18;
      val C_ORDERS_C_COUNT = v18;
      tmp6.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp6
    tmp6.foreach { case (k19,v19) =>
      val C_ORDERS_C_COUNT = k19;
      tmp_add8.add(C_ORDERS_C_COUNT,v19)
    }
    val tmp7 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp7 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add9 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k21,v21) =>
      val C_ORDERS_C_CUSTKEY = k21;
      tmp_add9.add(C_ORDERS_C_CUSTKEY,v21)
    }
    tmp_add9.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add9.foreach{ (k20,v20) =>
      val C_ORDERS_C_CUSTKEY = k20
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp7.add(C_ORDERS_C_COUNT,(v20 != 0));
    }
    // using tmp7
    tmp7.foreach { case (k22,v22) =>
      val C_ORDERS_C_COUNT = k22;
      tmp_add8.add(C_ORDERS_C_COUNT,v22)
    }
    tmp_add8.foreach{ (k17,v17) =>
      val C_ORDERS_C_COUNT = k17
      tmp_add7.add(C_ORDERS_C_COUNT,(v17 * -1L))
    }
    val tmp_add10 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp8 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp8 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add11 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k25,v25) =>
      val C_ORDERS_C_CUSTKEY = k25;
      tmp_add11.add(C_ORDERS_C_CUSTKEY,v25)
    }
    tmp_add11.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add11.foreach{ (k24,v24) =>
      val C_ORDERS_C_CUSTKEY = k24
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp8.add(C_ORDERS_C_COUNT,(v24 != 0));
    }
    // using tmp8
    tmp8.foreach { case (k26,v26) =>
      val C_ORDERS_C_COUNT = k26;
      tmp_add10.add(C_ORDERS_C_COUNT,v26)
    }
    val tmp9 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp9 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add12 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k28,v28) =>
      val C_ORDERS_C_CUSTKEY = k28;
      tmp_add12.add(C_ORDERS_C_CUSTKEY,v28)
    }
    tmp_add12.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add12.foreach{ (k27,v27) =>
      val C_ORDERS_C_CUSTKEY = k27
      val C_ORDERS_C_COUNT = v27;
      tmp9.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp9
    tmp9.foreach { case (k29,v29) =>
      val C_ORDERS_C_COUNT = k29;
      tmp_add10.add(C_ORDERS_C_COUNT,v29)
    }
    tmp_add10.foreach{ (k23,v23) =>
      val C_ORDERS_C_COUNT = k23
      tmp_add7.add(C_ORDERS_C_COUNT,v23)
    }
    tmp_add7.foreach{ (k16,v16) =>
      val C_ORDERS_C_COUNT = k16
      val tmp10 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp10 (ks = List(C_ORDERS_C_COUNT))
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k30,v30) =>
        val C_ORDERS_C_CUSTKEY = k30;
        val C_ORDERS_C_COUNT2 = v30;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT2) {
          tmp10.add(C_ORDERS_C_COUNT2,(C_ORDERS_C_COUNT2 != 0));
        }
      }
      // using tmp10
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp10.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v16);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)));
    CUSTDIST_mCUSTOMER1_E1_3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * -1L));
  }
  
  def onAddCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add13 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add14 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp11 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp11 (ks = List(C_ORDERS_C_COUNT))
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k33,v33) =>
      val C_ORDERS_C_CUSTKEY = k33;
      val C_ORDERS_C_COUNT = v33;
      tmp11.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp11
    tmp11.foreach { case (k34,v34) =>
      val C_ORDERS_C_COUNT = k34;
      tmp_add14.add(C_ORDERS_C_COUNT,v34)
    }
    val tmp12 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp12 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add15 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k36,v36) =>
      val C_ORDERS_C_CUSTKEY = k36;
      tmp_add15.add(C_ORDERS_C_CUSTKEY,v36)
    }
    tmp_add15.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add15.foreach{ (k35,v35) =>
      val C_ORDERS_C_CUSTKEY = k35
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp12.add(C_ORDERS_C_COUNT,(v35 != 0));
    }
    // using tmp12
    tmp12.foreach { case (k37,v37) =>
      val C_ORDERS_C_COUNT = k37;
      tmp_add14.add(C_ORDERS_C_COUNT,v37)
    }
    tmp_add14.foreach{ (k32,v32) =>
      val C_ORDERS_C_COUNT = k32
      tmp_add13.add(C_ORDERS_C_COUNT,(v32 * -1L))
    }
    val tmp_add16 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp13 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp13 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add17 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k40,v40) =>
      val C_ORDERS_C_CUSTKEY = k40;
      tmp_add17.add(C_ORDERS_C_CUSTKEY,v40)
    }
    tmp_add17.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add17.foreach{ (k39,v39) =>
      val C_ORDERS_C_CUSTKEY = k39
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp13.add(C_ORDERS_C_COUNT,(v39 != 0));
    }
    // using tmp13
    tmp13.foreach { case (k41,v41) =>
      val C_ORDERS_C_COUNT = k41;
      tmp_add16.add(C_ORDERS_C_COUNT,v41)
    }
    val tmp14 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp14 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add18 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k43,v43) =>
      val C_ORDERS_C_CUSTKEY = k43;
      tmp_add18.add(C_ORDERS_C_CUSTKEY,v43)
    }
    tmp_add18.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add18.foreach{ (k42,v42) =>
      val C_ORDERS_C_CUSTKEY = k42
      val C_ORDERS_C_COUNT = v42;
      tmp14.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp14
    tmp14.foreach { case (k44,v44) =>
      val C_ORDERS_C_COUNT = k44;
      tmp_add16.add(C_ORDERS_C_COUNT,v44)
    }
    tmp_add16.foreach{ (k38,v38) =>
      val C_ORDERS_C_COUNT = k38
      tmp_add13.add(C_ORDERS_C_COUNT,v38)
    }
    tmp_add13.foreach{ (k31,v31) =>
      val C_ORDERS_C_COUNT = k31
      val tmp15 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp15 (ks = List(C_ORDERS_C_COUNT))
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k45,v45) =>
        val C_ORDERS_C_CUSTKEY = k45;
        val C_ORDERS_C_COUNT3 = v45;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT3) {
          tmp15.add(C_ORDERS_C_COUNT3,(C_ORDERS_C_COUNT3 != 0));
        }
      }
      // using tmp15
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp15.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v31);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY));
  }
  
  def onDelCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add19 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add20 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp16 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp16 (ks = List(C_ORDERS_C_COUNT))
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k48,v48) =>
      val C_ORDERS_C_CUSTKEY = k48;
      val C_ORDERS_C_COUNT = v48;
      tmp16.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp16
    tmp16.foreach { case (k49,v49) =>
      val C_ORDERS_C_COUNT = k49;
      tmp_add20.add(C_ORDERS_C_COUNT,v49)
    }
    val tmp17 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp17 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add21 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k51,v51) =>
      val C_ORDERS_C_CUSTKEY = k51;
      tmp_add21.add(C_ORDERS_C_CUSTKEY,v51)
    }
    tmp_add21.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add21.foreach{ (k50,v50) =>
      val C_ORDERS_C_CUSTKEY = k50
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp17.add(C_ORDERS_C_COUNT,(v50 != 0));
    }
    // using tmp17
    tmp17.foreach { case (k52,v52) =>
      val C_ORDERS_C_COUNT = k52;
      tmp_add20.add(C_ORDERS_C_COUNT,v52)
    }
    tmp_add20.foreach{ (k47,v47) =>
      val C_ORDERS_C_COUNT = k47
      tmp_add19.add(C_ORDERS_C_COUNT,(v47 * -1L))
    }
    val tmp_add22 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp18 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp18 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add23 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k55,v55) =>
      val C_ORDERS_C_CUSTKEY = k55;
      tmp_add23.add(C_ORDERS_C_CUSTKEY,v55)
    }
    tmp_add23.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add23.foreach{ (k54,v54) =>
      val C_ORDERS_C_CUSTKEY = k54
      val C_ORDERS_C_COUNT = CUSTDIST_mCUSTOMER1_E1_1.get(C_ORDERS_C_CUSTKEY);
      tmp18.add(C_ORDERS_C_COUNT,(v54 != 0));
    }
    // using tmp18
    tmp18.foreach { case (k56,v56) =>
      val C_ORDERS_C_COUNT = k56;
      tmp_add22.add(C_ORDERS_C_COUNT,v56)
    }
    val tmp19 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp19 (ks = List(C_ORDERS_C_COUNT))
    val tmp_add24 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k58,v58) =>
      val C_ORDERS_C_CUSTKEY = k58;
      tmp_add24.add(C_ORDERS_C_CUSTKEY,v58)
    }
    tmp_add24.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add24.foreach{ (k57,v57) =>
      val C_ORDERS_C_CUSTKEY = k57
      val C_ORDERS_C_COUNT = v57;
      tmp19.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp19
    tmp19.foreach { case (k59,v59) =>
      val C_ORDERS_C_COUNT = k59;
      tmp_add22.add(C_ORDERS_C_COUNT,v59)
    }
    tmp_add22.foreach{ (k53,v53) =>
      val C_ORDERS_C_COUNT = k53
      tmp_add19.add(C_ORDERS_C_COUNT,v53)
    }
    tmp_add19.foreach{ (k46,v46) =>
      val C_ORDERS_C_COUNT = k46
      val tmp20 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp20 (ks = List(C_ORDERS_C_COUNT))
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k60,v60) =>
        val C_ORDERS_C_CUSTKEY = k60;
        val C_ORDERS_C_COUNT4 = v60;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT4) {
          tmp20.add(C_ORDERS_C_COUNT4,(C_ORDERS_C_COUNT4 != 0));
        }
      }
      // using tmp20
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp20.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v46);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,-1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L));
  }
  
  def onSystemReady() {
    
  }
}
