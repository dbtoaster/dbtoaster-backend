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
    // filling tmp1
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
    // filling tmp2
    val tmp_add3 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k6,v6) =>
      val C_ORDERS_C_CUSTKEY = k6;
      tmp_add3.add(C_ORDERS_C_CUSTKEY,v6)
    }
    tmp_add3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add3.foreach{ (k5,v5) =>
      val C_ORDERS_C_CUSTKEY = k5
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k7,v7) =>
        val C_ORDERS_C_CUSTKEY = k7;
        val C_ORDERS_C_COUNT = v7;
        tmp2.add(C_ORDERS_C_COUNT,(v5 != 0));
      }
    }
    // using tmp2
    tmp2.foreach { case (k8,v8) =>
      val C_ORDERS_C_COUNT = k8;
      tmp_add2.add(C_ORDERS_C_COUNT,v8)
    }
    tmp_add2.foreach{ (k2,v2) =>
      val C_ORDERS_C_COUNT = k2
      tmp_add1.add(C_ORDERS_C_COUNT,(v2 * -1L))
    }
    val tmp_add4 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp3 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp3
    val tmp_add5 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k11,v11) =>
      val C_ORDERS_C_CUSTKEY = k11;
      tmp_add5.add(C_ORDERS_C_CUSTKEY,v11)
    }
    tmp_add5.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add5.foreach{ (k10,v10) =>
      val C_ORDERS_C_CUSTKEY = k10
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k12,v12) =>
        val C_ORDERS_C_CUSTKEY = k12;
        val C_ORDERS_C_COUNT = v12;
        tmp3.add(C_ORDERS_C_COUNT,(v10 != 0));
      }
    }
    // using tmp3
    tmp3.foreach { case (k13,v13) =>
      val C_ORDERS_C_COUNT = k13;
      tmp_add4.add(C_ORDERS_C_COUNT,v13)
    }
    val tmp4 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp4
    val tmp_add6 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k15,v15) =>
      val C_ORDERS_C_CUSTKEY = k15;
      tmp_add6.add(C_ORDERS_C_CUSTKEY,v15)
    }
    tmp_add6.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY)))
    tmp_add6.foreach{ (k14,v14) =>
      val C_ORDERS_C_CUSTKEY = k14
      val C_ORDERS_C_COUNT = v14;
      tmp4.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp4
    tmp4.foreach { case (k16,v16) =>
      val C_ORDERS_C_COUNT = k16;
      tmp_add4.add(C_ORDERS_C_COUNT,v16)
    }
    tmp_add4.foreach{ (k9,v9) =>
      val C_ORDERS_C_COUNT = k9
      tmp_add1.add(C_ORDERS_C_COUNT,v9)
    }
    tmp_add1.foreach{ (k1,v1) =>
      val C_ORDERS_C_COUNT = k1
      val tmp5 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp5
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k17,v17) =>
        val C_ORDERS_C_CUSTKEY = k17;
        val C_ORDERS_C_COUNT1 = v17;
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
    // filling tmp6
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k20,v20) =>
      val C_ORDERS_C_CUSTKEY = k20;
      val C_ORDERS_C_COUNT = v20;
      tmp6.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp6
    tmp6.foreach { case (k21,v21) =>
      val C_ORDERS_C_COUNT = k21;
      tmp_add8.add(C_ORDERS_C_COUNT,v21)
    }
    val tmp7 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp7
    val tmp_add9 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k23,v23) =>
      val C_ORDERS_C_CUSTKEY = k23;
      tmp_add9.add(C_ORDERS_C_CUSTKEY,v23)
    }
    tmp_add9.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add9.foreach{ (k22,v22) =>
      val C_ORDERS_C_CUSTKEY = k22
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k24,v24) =>
        val C_ORDERS_C_CUSTKEY = k24;
        val C_ORDERS_C_COUNT = v24;
        tmp7.add(C_ORDERS_C_COUNT,(v22 != 0));
      }
    }
    // using tmp7
    tmp7.foreach { case (k25,v25) =>
      val C_ORDERS_C_COUNT = k25;
      tmp_add8.add(C_ORDERS_C_COUNT,v25)
    }
    tmp_add8.foreach{ (k19,v19) =>
      val C_ORDERS_C_COUNT = k19
      tmp_add7.add(C_ORDERS_C_COUNT,(v19 * -1L))
    }
    val tmp_add10 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp8 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp8
    val tmp_add11 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k28,v28) =>
      val C_ORDERS_C_CUSTKEY = k28;
      tmp_add11.add(C_ORDERS_C_CUSTKEY,v28)
    }
    tmp_add11.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add11.foreach{ (k27,v27) =>
      val C_ORDERS_C_CUSTKEY = k27
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k29,v29) =>
        val C_ORDERS_C_CUSTKEY = k29;
        val C_ORDERS_C_COUNT = v29;
        tmp8.add(C_ORDERS_C_COUNT,(v27 != 0));
      }
    }
    // using tmp8
    tmp8.foreach { case (k30,v30) =>
      val C_ORDERS_C_COUNT = k30;
      tmp_add10.add(C_ORDERS_C_COUNT,v30)
    }
    val tmp9 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp9
    val tmp_add12 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k32,v32) =>
      val C_ORDERS_C_CUSTKEY = k32;
      tmp_add12.add(C_ORDERS_C_CUSTKEY,v32)
    }
    tmp_add12.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)))
    tmp_add12.foreach{ (k31,v31) =>
      val C_ORDERS_C_CUSTKEY = k31
      val C_ORDERS_C_COUNT = v31;
      tmp9.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp9
    tmp9.foreach { case (k33,v33) =>
      val C_ORDERS_C_COUNT = k33;
      tmp_add10.add(C_ORDERS_C_COUNT,v33)
    }
    tmp_add10.foreach{ (k26,v26) =>
      val C_ORDERS_C_COUNT = k26
      tmp_add7.add(C_ORDERS_C_COUNT,v26)
    }
    tmp_add7.foreach{ (k18,v18) =>
      val C_ORDERS_C_COUNT = k18
      val tmp10 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp10
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k34,v34) =>
        val C_ORDERS_C_CUSTKEY = k34;
        val C_ORDERS_C_COUNT2 = v34;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT2) {
          tmp10.add(C_ORDERS_C_COUNT2,(C_ORDERS_C_COUNT2 != 0));
        }
      }
      // using tmp10
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp10.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v18);
    }
    CUSTDIST_mCUSTOMER1_E1_1.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * (CUSTDIST_mORDERS1_E1_4.get(ORDERS_CUSTKEY) * -1L)));
    CUSTDIST_mCUSTOMER1_E1_3.add(ORDERS_CUSTKEY,((0L == Uregexp_match("^.*special.*requests.*$",ORDERS_COMMENT)) * -1L));
  }
  
  def onAddCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add13 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add14 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp11 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp11
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k37,v37) =>
      val C_ORDERS_C_CUSTKEY = k37;
      val C_ORDERS_C_COUNT = v37;
      tmp11.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp11
    tmp11.foreach { case (k38,v38) =>
      val C_ORDERS_C_COUNT = k38;
      tmp_add14.add(C_ORDERS_C_COUNT,v38)
    }
    val tmp12 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp12
    val tmp_add15 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k40,v40) =>
      val C_ORDERS_C_CUSTKEY = k40;
      tmp_add15.add(C_ORDERS_C_CUSTKEY,v40)
    }
    tmp_add15.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add15.foreach{ (k39,v39) =>
      val C_ORDERS_C_CUSTKEY = k39
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k41,v41) =>
        val C_ORDERS_C_CUSTKEY = k41;
        val C_ORDERS_C_COUNT = v41;
        tmp12.add(C_ORDERS_C_COUNT,(v39 != 0));
      }
    }
    // using tmp12
    tmp12.foreach { case (k42,v42) =>
      val C_ORDERS_C_COUNT = k42;
      tmp_add14.add(C_ORDERS_C_COUNT,v42)
    }
    tmp_add14.foreach{ (k36,v36) =>
      val C_ORDERS_C_COUNT = k36
      tmp_add13.add(C_ORDERS_C_COUNT,(v36 * -1L))
    }
    val tmp_add16 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp13 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp13
    val tmp_add17 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k45,v45) =>
      val C_ORDERS_C_CUSTKEY = k45;
      tmp_add17.add(C_ORDERS_C_CUSTKEY,v45)
    }
    tmp_add17.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add17.foreach{ (k44,v44) =>
      val C_ORDERS_C_CUSTKEY = k44
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k46,v46) =>
        val C_ORDERS_C_CUSTKEY = k46;
        val C_ORDERS_C_COUNT = v46;
        tmp13.add(C_ORDERS_C_COUNT,(v44 != 0));
      }
    }
    // using tmp13
    tmp13.foreach { case (k47,v47) =>
      val C_ORDERS_C_COUNT = k47;
      tmp_add16.add(C_ORDERS_C_COUNT,v47)
    }
    val tmp14 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp14
    val tmp_add18 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k49,v49) =>
      val C_ORDERS_C_CUSTKEY = k49;
      tmp_add18.add(C_ORDERS_C_CUSTKEY,v49)
    }
    tmp_add18.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY))
    tmp_add18.foreach{ (k48,v48) =>
      val C_ORDERS_C_CUSTKEY = k48
      val C_ORDERS_C_COUNT = v48;
      tmp14.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp14
    tmp14.foreach { case (k50,v50) =>
      val C_ORDERS_C_COUNT = k50;
      tmp_add16.add(C_ORDERS_C_COUNT,v50)
    }
    tmp_add16.foreach{ (k43,v43) =>
      val C_ORDERS_C_COUNT = k43
      tmp_add13.add(C_ORDERS_C_COUNT,v43)
    }
    tmp_add13.foreach{ (k35,v35) =>
      val C_ORDERS_C_COUNT = k35
      val tmp15 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp15
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k51,v51) =>
        val C_ORDERS_C_CUSTKEY = k51;
        val C_ORDERS_C_COUNT3 = v51;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT3) {
          tmp15.add(C_ORDERS_C_COUNT3,(C_ORDERS_C_COUNT3 != 0));
        }
      }
      // using tmp15
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp15.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v35);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY));
  }
  
  def onDelCUSTOMER(CUSTOMER_CUSTKEY:Long, CUSTOMER_NAME:String, CUSTOMER_ADDRESS:String, CUSTOMER_NATIONKEY:Long, CUSTOMER_PHONE:String, CUSTOMER_ACCTBAL:Double, CUSTOMER_MKTSEGMENT:String, CUSTOMER_COMMENT:String) {
    val tmp_add19 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp_add20 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp16 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp16
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k54,v54) =>
      val C_ORDERS_C_CUSTKEY = k54;
      val C_ORDERS_C_COUNT = v54;
      tmp16.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp16
    tmp16.foreach { case (k55,v55) =>
      val C_ORDERS_C_COUNT = k55;
      tmp_add20.add(C_ORDERS_C_COUNT,v55)
    }
    val tmp17 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp17
    val tmp_add21 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k57,v57) =>
      val C_ORDERS_C_CUSTKEY = k57;
      tmp_add21.add(C_ORDERS_C_CUSTKEY,v57)
    }
    tmp_add21.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add21.foreach{ (k56,v56) =>
      val C_ORDERS_C_CUSTKEY = k56
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k58,v58) =>
        val C_ORDERS_C_CUSTKEY = k58;
        val C_ORDERS_C_COUNT = v58;
        tmp17.add(C_ORDERS_C_COUNT,(v56 != 0));
      }
    }
    // using tmp17
    tmp17.foreach { case (k59,v59) =>
      val C_ORDERS_C_COUNT = k59;
      tmp_add20.add(C_ORDERS_C_COUNT,v59)
    }
    tmp_add20.foreach{ (k53,v53) =>
      val C_ORDERS_C_COUNT = k53
      tmp_add19.add(C_ORDERS_C_COUNT,(v53 * -1L))
    }
    val tmp_add22 = K3Map.temp[Long,Long]() // XXX: fix types
    val tmp18 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp18
    val tmp_add23 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k62,v62) =>
      val C_ORDERS_C_CUSTKEY = k62;
      tmp_add23.add(C_ORDERS_C_CUSTKEY,v62)
    }
    tmp_add23.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add23.foreach{ (k61,v61) =>
      val C_ORDERS_C_CUSTKEY = k61
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k63,v63) =>
        val C_ORDERS_C_CUSTKEY = k63;
        val C_ORDERS_C_COUNT = v63;
        tmp18.add(C_ORDERS_C_COUNT,(v61 != 0));
      }
    }
    // using tmp18
    tmp18.foreach { case (k64,v64) =>
      val C_ORDERS_C_COUNT = k64;
      tmp_add22.add(C_ORDERS_C_COUNT,v64)
    }
    val tmp19 = K3Map.make[Long,Long]() // XXX: fix types
    // filling tmp19
    val tmp_add24 = K3Map.temp[Long,Long]() // XXX: fix types
    CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k66,v66) =>
      val C_ORDERS_C_CUSTKEY = k66;
      tmp_add24.add(C_ORDERS_C_CUSTKEY,v66)
    }
    tmp_add24.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L))
    tmp_add24.foreach{ (k65,v65) =>
      val C_ORDERS_C_CUSTKEY = k65
      val C_ORDERS_C_COUNT = v65;
      tmp19.add(C_ORDERS_C_COUNT,(C_ORDERS_C_COUNT != 0));
    }
    // using tmp19
    tmp19.foreach { case (k67,v67) =>
      val C_ORDERS_C_COUNT = k67;
      tmp_add22.add(C_ORDERS_C_COUNT,v67)
    }
    tmp_add22.foreach{ (k60,v60) =>
      val C_ORDERS_C_COUNT = k60
      tmp_add19.add(C_ORDERS_C_COUNT,v60)
    }
    tmp_add19.foreach{ (k52,v52) =>
      val C_ORDERS_C_COUNT = k52
      val tmp20 = K3Map.make[Long,Long]() // XXX: fix types
      // filling tmp20
      CUSTDIST_mCUSTOMER1_E1_1.foreach { case (k68,v68) =>
        val C_ORDERS_C_CUSTKEY = k68;
        val C_ORDERS_C_COUNT4 = v68;
        if (C_ORDERS_C_COUNT == C_ORDERS_C_COUNT4) {
          tmp20.add(C_ORDERS_C_COUNT4,(C_ORDERS_C_COUNT4 != 0));
        }
      }
      // using tmp20
      if (CUSTDIST.get(C_ORDERS_C_COUNT)==0) CUSTDIST.set(C_ORDERS_C_COUNT,tmp20.get(C_ORDERS_C_COUNT));
      CUSTDIST.add(C_ORDERS_C_COUNT,v52);
    }
    CUSTDIST_mORDERS1_E1_4.add(CUSTOMER_CUSTKEY,-1L);
    CUSTDIST_mCUSTOMER1_E1_1.add(CUSTOMER_CUSTKEY,(CUSTDIST_mCUSTOMER1_E1_3.get(CUSTOMER_CUSTKEY) * -1L));
  }
  
  def onSystemReady() {
    
  }
}
