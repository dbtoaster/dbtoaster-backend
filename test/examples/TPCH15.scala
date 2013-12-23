package ddbt.test.examples
import ddbt.lib._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import java.util.Date;

object TPCH15 {
  import Helper._
  def main(args:Array[String]) {
    /*
    println("Reference:")
    val (t1,r1) = run[TPCH15Ref,Long,Double](streamsTPCH15(),false);
    println(K3Helper.toStr(r1)); println("Time: "+time(t1))
    */
    println("Mine:")
    val (t2,r2) = run[TPCH15](Compat.streamsTPCH15(),false);
    println(r2.head); println("Time: "+t2)
  }
}

// This example is manually fixed
// Leverage it to address ScalaGen issues

class TPCH15 extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._

  val COUNT = M3Map.make[(Long,String,String,String,Double),Long]();
  val COUNT_mLINEITEM1 = M3Map.make[(String,String,String,Long),Long](); // OK
  val COUNT_mLINEITEM1_L2_1 = M3Map.make[Long,Double](); // OK
  val COUNT_mLINEITEM1_L2_3 = M3Map.make[Long,Double](); // OK
  val COUNT_mLINEITEM1_L3_1_E1_1 = M3Map.make[Long,Double](); // OK
  val COUNT_mLINEITEM1_L3_1_E1_3 = M3Map.make[Long,Double](); // OK

  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onAddLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onDelLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleInsert,"SUPPLIER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onAddSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case TupleEvent(TupleDelete,"SUPPLIER",List(v0:Long,v1:String,v2:String,v3:Long,v4:String,v5:Double,v6:String)) => onDelSUPPLIER(v0,v1,v2,v3,v4,v5,v6)
    case StreamInit(_) => onSystemReady(); t0=System.nanoTime()
    case EndOfStream => val time=System.nanoTime()-t0;
      /*
      println("COUNT_mLINEITEM1")
      println(K3Helper.toStr(COUNT_mLINEITEM1.toMap))
      println("COUNT_mLINEITEM1_L2_1")
      println(K3Helper.toStr(COUNT_mLINEITEM1_L2_1.toMap))
      println("COUNT_mLINEITEM1_L2_3")
      println(K3Helper.toStr(COUNT_mLINEITEM1_L2_3.toMap))
      println("COUNT_mLINEITEM1_L3_1_E1_1")
      println(K3Helper.toStr(COUNT_mLINEITEM1_L3_1_E1_1.toMap))
      println("COUNT_mLINEITEM1_L3_1_E1_3")
      println(K3Helper.toStr(COUNT_mLINEITEM1_L3_1_E1_3.toMap))
      */
      sender ! (time,List(result))
  }

  def result = COUNT.toMap

  val c1:Date = Udate("1996-4-1")
  val c2:Date = Udate("1996-1-1")

  def onAddLINEITEM(L_ORDERKEY:Long, L_PARTKEY:Long, L_SUPPKEY:Long, L_LINENUMBER:Long, L_QUANTITY:Double, L_EXTENDEDPRICE:Double, L_DISCOUNT:Double, L_TAX:Double, L_RETURNFLAG:String, L_LINESTATUS:String, L_SHIPDATE:Date, L_COMMITDATE:Date, L_RECEIPTDATE:Date, L_SHIPINSTRUCT:String, L_SHIPMODE:String, L_COMMENT:String) {
    COUNT_mLINEITEM1.foreach { case (k1,v1) =>
      val S_NAME = k1._1;
      val S_ADDRESS = k1._2;
      val S_PHONE = k1._3;
      val S_SUPPKEY = k1._4;
      ; {
        val R1_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY));
        var ex1:Long = 0L
        ex1 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var ex2:Long = 0L
        ex2 |= ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var ex3:Long = 0L
        ex3 |= ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var ex4:Long = 0L
        ex4 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var ex5:Long = 0L
        ex5 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg1:Double = 0 //correct type???
        var agg2:Double = 0 //correct type???
        var ex6:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k2,v2) =>
          val R2_SUPPKEY = k2;
          ex6 |= (((v2 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg2 += (ex6 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = agg2;
          agg1 += (__domain_1 * (__domain_1 == (0L)));
        }
        var ex7:Long = 0L
        ex7 |= ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var ex8:Long = 0L
        ex8 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg3:Double = 0 //correct type???
        var agg4:Double = 0 //correct type???
        var ex9:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k3,v3) =>
          val R2_SUPPKEY = k3;
          ex9 |= (((v3 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg4 += (ex9 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg5:Double = 0 //correct type???
        var ex10:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex10 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg5 += (ex10 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg6:Double = 0 //correct type???
        var ex11:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k4,v4) =>
          val R2_SUPPKEY = k4;
          ex11 |= (((v4 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg6 += (ex11 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg7:Double = 0 //correct type???
        var ex12:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex12 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg7 += (ex12 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg8:Double = 0 //correct type???
        var ex13:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex13 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = (((R2_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)));
          agg8 += (ex13 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = (((agg4 + agg5) * -1L) + (agg6 + (agg7 + agg8)));
          agg3 += (__domain_1 * (__domain_1 == (0L)));
        }
        var ex14:Long = 0L
        ex14 |= ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var ex15:Long = 0L
        ex15 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg9:Double = 0 //correct type???
        var agg10:Double = 0 //correct type???
        var ex16:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k5,v5) =>
          val R2_SUPPKEY = k5;
          ex16 |= (((v5 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg10 += (ex16 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = agg10;
          agg9 += (__domain_1 * (__domain_1 == (0L)));
        }
        var ex17:Long = 0L
        ex17 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var ex18:Long = 0L
        ex18 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var ex19:Long = 0L
        ex19 |= ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var agg11:Double = 0 //correct type???
        var agg12:Double = 0 //correct type???
        var ex20:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k6,v6) =>
          val R2_SUPPKEY = k6;
          ex20 |= (((v6 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg12 += (ex20 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg13:Double = 0 //correct type???
        var ex21:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex21 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg13 += (ex21 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg14:Double = 0 //correct type???
        var ex22:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k7,v7) =>
          val R2_SUPPKEY = k7;
          ex22 |= (((v7 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg14 += (ex22 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg15:Double = 0 //correct type???
        var ex23:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex23 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg15 += (ex23 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg16:Double = 0 //correct type???
        var ex24:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex24 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = (((R2_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)));
          agg16 += (ex24 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = (((agg12 + agg13) * -1L) + (agg14 + (agg15 + agg16)));
          agg11 += (__domain_1 * (__domain_1 == (0L)));
        }
        var ex25:Long = 0L
        ex25 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg17:Double = 0 //correct type???
        var agg18:Double = 0 //correct type???
        var ex26:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k8,v8) =>
          val R2_SUPPKEY = k8;
          ex26 |= (((v8 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg18 += (ex26 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = agg18;
          agg17 += (__domain_1 * (__domain_1 == (0L)));
        }
        var ex27:Long = 0L
        ex27 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg19:Double = 0 //correct type???
        var agg20:Double = 0 //correct type???
        var ex28:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k9,v9) =>
          val R2_SUPPKEY = k9;
          ex28 |= (((v9 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg20 += (ex28 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg21:Double = 0 //correct type???
        var ex29:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex29 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg21 += (ex29 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg22:Double = 0 //correct type???
        var ex30:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k10,v10) =>
          val R2_SUPPKEY = k10;
          ex30 |= (((v10 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg22 += (ex30 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg23:Double = 0 //correct type???
        var ex31:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex31 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg23 += (ex31 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        var agg24:Double = 0 //correct type???
        var ex32:Long = 0L
        ; {
          val R2_SUPPKEY = L_SUPPKEY;
          ex32 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
          val R2_TOTAL_REVENUE = (((R2_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE)))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)));
          agg24 += (ex32 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = (((agg20 + agg21) * -1L) + (agg22 + (agg23 + agg24)));
          agg19 += (__domain_1 * (__domain_1 == (0L)));
        }
        COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE),(v1 * (((S_SUPPKEY == (L_SUPPKEY)) * ((((R1_TOTAL_REVENUE * ((ex1 * 2L) + ex2)) + (((S_SUPPKEY == (L_SUPPKEY)) * ((ex3 * ((R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))) + (R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))))) + (ex4 * ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) + (R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))))))) + ((R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))) * ex5))) * agg1) + (((ex7 * ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) + ((S_SUPPKEY == (L_SUPPKEY)) * (R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))))))) + (ex8 * ((R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))) + ((S_SUPPKEY == (L_SUPPKEY)) * (R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))))))) * agg3))) + (((((S_SUPPKEY == (L_SUPPKEY)) * ((((ex14 * ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) + ((S_SUPPKEY == (L_SUPPKEY)) * ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) + (R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))))))) + (ex15 * (((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * 2L) + (((S_SUPPKEY == (L_SUPPKEY)) * ((R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))) + (R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))))) + (R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))))))) * agg9) + ((((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * (ex17 * 2L)) + ((S_SUPPKEY == (L_SUPPKEY)) * (((R1_TOTAL_REVENUE == ((((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (((-1L * L_DISCOUNT) + 1L) * L_EXTENDEDPRICE))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))) * ex18) + ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * ex19)))) * agg11))) + ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * (ex25 * agg17))) * -1L) + ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * (ex27 * agg19)))).toLong));
      }
    }
    COUNT_mLINEITEM1_L2_1.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (L_DISCOUNT * L_EXTENDEDPRICE))));
    COUNT_mLINEITEM1_L2_3.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * L_EXTENDEDPRICE)));
    COUNT_mLINEITEM1_L3_1_E1_1.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (L_DISCOUNT * L_EXTENDEDPRICE))));
    COUNT_mLINEITEM1_L3_1_E1_3.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * L_EXTENDEDPRICE)));
  }

  def onDelLINEITEM(L_ORDERKEY:Long, L_PARTKEY:Long, L_SUPPKEY:Long, L_LINENUMBER:Long, L_QUANTITY:Double, L_EXTENDEDPRICE:Double, L_DISCOUNT:Double, L_TAX:Double, L_RETURNFLAG:String, L_LINESTATUS:String, L_SHIPDATE:Date, L_COMMITDATE:Date, L_RECEIPTDATE:Date, L_SHIPINSTRUCT:String, L_SHIPMODE:String, L_COMMENT:String) {
    COUNT_mLINEITEM1.foreach { case (k11,v11) =>
      val S_NAME = k11._1;
      val S_ADDRESS = k11._2;
      val S_PHONE = k11._3;
      val S_SUPPKEY = k11._4;
      var ex33:Long = 0L
      ex33 |= ((((S_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
      ; {
        val R1_TOTAL_REVENUE = (((S_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)));
        var agg25:Double = 0 //correct type???
        ; {
          val __domain_1 = 0L;
          var agg26:Double = 0 //correct type???
          var ex34:Long = 0L
          COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k12,v12) =>
            val R2_SUPPKEY = k12;
            ex34 |= (((v12 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg26 += (ex34 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          agg25 += (__domain_1 * (__domain_1 == (agg26)));
        }
        var agg27:Double = 0 //correct type???
        ; {
          val __domain_1 = 0L;
          var agg28:Double = 0 //correct type???
          var ex35:Long = 0L
          COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k13,v13) =>
            val R2_SUPPKEY = k13;
            ex35 |= (((v13 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg28 += (ex35 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          var agg29:Double = 0 //correct type???
          var ex36:Long = 0L
          ; {
            val R2_SUPPKEY = L_SUPPKEY;
            ex36 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg29 += (ex36 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          var agg30:Double = 0 //correct type???
          var ex37:Long = 0L
          COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k14,v14) =>
            val R2_SUPPKEY = k14;
            ex37 |= (((v14 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg30 += (ex37 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          var agg31:Double = 0 //correct type???
          var ex38:Long = 0L
          ; {
            val R2_SUPPKEY = L_SUPPKEY;
            ex38 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg31 += (ex38 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          var agg32:Double = 0 //correct type???
          var ex39:Long = 0L
          ; {
            val R2_SUPPKEY = L_SUPPKEY;
            ex39 |= (((R2_SUPPKEY * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY))))!=0;
            val R2_TOTAL_REVENUE = (((R2_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)));
            agg32 += (ex39 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          agg27 += (__domain_1 * (__domain_1 == ((((agg28 + agg29) * -1L) + (agg30 + (agg31 + agg32))))));
        }
        var agg33:Double = 0 //correct type???
        ; {
          val __domain_1 = 0L;
          var agg34:Double = 0 //correct type???
          var ex40:Long = 0L
          COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k15,v15) =>
            val R2_SUPPKEY = k15;
            ex40 |= (((v15 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg34 += (ex40 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          agg33 += (__domain_1 * (__domain_1 == (agg34)));
        }
        var ex41:Long = 0L
        ex41 |= ((((S_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))!=0;
        var ex42:Long = 0L
        ex42 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg35:Double = 0 //correct type???
        ; {
          val __domain_1 = 0L;
          var agg36:Double = 0 //correct type???
          var ex43:Long = 0L
          COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k16,v16) =>
            val R2_SUPPKEY = k16;
            ex43 |= (((v16 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
            val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
            agg36 += (ex43 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
          }
          agg35 += (__domain_1 * (__domain_1 == (agg36)));
        }
        COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE),(v11 * ((ex33 * ((R1_TOTAL_REVENUE * (agg25 + agg27)) + ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * agg33))) + (((ex41 * ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) + (R1_TOTAL_REVENUE == ((((S_SUPPKEY == (L_SUPPKEY)) * ((c1 > L_SHIPDATE) * ((L_SHIPDATE >= c2) * (L_EXTENDEDPRICE * (-1L + L_DISCOUNT))))) + ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY))))))) + ((R1_TOTAL_REVENUE == (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))) * ex42)) * (agg35 * -1L))).toLong));
      }
    }
    COUNT_mLINEITEM1_L2_1.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (-1L * (L_DISCOUNT * L_EXTENDEDPRICE)))));
    COUNT_mLINEITEM1_L2_3.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (-1L * L_EXTENDEDPRICE))));
    COUNT_mLINEITEM1_L3_1_E1_1.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (-1L * (L_DISCOUNT * L_EXTENDEDPRICE)))));
    COUNT_mLINEITEM1_L3_1_E1_3.add(L_SUPPKEY,((L_SHIPDATE >= c2) * ((c1 > L_SHIPDATE) * (-1L * L_EXTENDEDPRICE))));
  }

  def onAddSUPPLIER(S_SUPPKEY:Long, S_NAME:String, S_ADDRESS:String, S_NATIONKEY:Long, S_PHONE:String, S_ACCTBAL:Double, S_COMMENT:String) {
/*
COUNT(int)[][S_SUPPKEY, S_NAME, S_ADDRESS, S_PHONE, R1_TOTAL_REVENUE] +=
  (S_SUPPKEY ^= S_SUPPKEY) *
  (R1_TOTAL_REVENUE ^= MM) *
  EXISTS(MM) *
  AggSum([],(
    (__domain_1 ^= AggSum([],
      EXISTS((MM) *
      (R2_TOTAL_REVENUE ^= MM) *
      {R2_TOTAL_REVENUE > R1_TOTAL_REVENUE}
    )) *
    (__domain_1 ^= 0)
  ));
*/
/*
    // Original semantics
    val R1_TOTAL_REVENUE:Double = COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY) - COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY);
    var result = Map[Long,Double]();
    def agg(k:Long,v:Double) { result += ((k, (result.get(k) match { case Some(v0) => v0 + v; case _ => v }))) }
    COUNT_mLINEITEM1_L3_1_E1_1.foreach { (k,v) => agg(k,-v) }
    COUNT_mLINEITEM1_L3_1_E1_3.foreach { (k,v) => agg(k,v) }

    val v__domain_1 = result.map{x=> val R2_SUPPKEY:Long = x._1;
      val R2_TOTAL_REVENUE:Double = COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY) - COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY)
      (x._2 != 0L) * (R1_TOTAL_REVENUE < R2_TOTAL_REVENUE)
    }.foldLeft(0L)(_+_)

    val nv = (R1_TOTAL_REVENUE != 0L) * (0L == v__domain_1)
    COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE), nv)
    COUNT_mLINEITEM1.add((S_NAME,S_ADDRESS,S_PHONE,S_SUPPKEY),1L)
*/
/*
    // Intended result
    val R1_TOTAL_REVENUE:Double = COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY) - COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY);
    var agg : Long = 0
    COUNT_mLINEITEM1_L3_1_E1_1.foreach { (k,v1) =>
      val v3 = COUNT_mLINEITEM1_L3_1_E1_3.get(k)
      val R2_TOTAL_REVENUE = v3 - v1
      if (v3!=0) {
        agg += (R1_TOTAL_REVENUE < R2_TOTAL_REVENUE)
      }
    }
    COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE), agg==0L)
    COUNT_mLINEITEM1.add((S_NAME,S_ADDRESS,S_PHONE,S_SUPPKEY),1L)
*/

    // Generated
    // removed S_SUPPKEY = S_SUPPKEY
    val R1_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY));
    var ex46:Long = 0L
    ex46 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
    var agg39:Long = 0 // fixed type
    var agg40:Long = 0 // fixed type
    var ex47:Long = 0L
    COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k18,v18) =>
      val R2_SUPPKEY = k18;
      ex47 |= (((v18 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
      // --- this was moved --
      val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
      agg40 += (ex47 * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE));
      // --- this was moved --
    }
    val __domain_1 = agg40;
    agg39 += (__domain_1 == 0L);
    COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE),(ex46 * agg39));
    COUNT_mLINEITEM1.add((S_NAME,S_ADDRESS,S_PHONE,S_SUPPKEY),1L);


/*
    // Generated
    val R1_TOTAL_REVENUE = COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY) - COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY);
    var ex44:Long = 0L
    ex44 |= R1_TOTAL_REVENUE!=0;
// ----------
    var agg37:Double = 0 //correct type???
    var agg38:Double = 0 //correct type???
    var ex45:Long = 0L
    COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k17,v17) =>
      val R2_SUPPKEY = k17;
      ex45 |= (((v17 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
      val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
      agg38 += (ex45 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
    }
    val __domain_1 = agg38;
    agg37 += (__domain_1 * (__domain_1 == (0L)));
    COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE),(S_SUPPKEY * (R1_TOTAL_REVENUE * (ex44 * agg37)).toLong));
// ----------
    COUNT_mLINEITEM1.add((S_NAME,S_ADDRESS,S_PHONE,S_SUPPKEY),1L);
*/
  }

  def onDelSUPPLIER(S_SUPPKEY:Long, S_NAME:String, S_ADDRESS:String, S_NATIONKEY:Long, S_PHONE:String, S_ACCTBAL:Double, S_COMMENT:String) {
/*
    ; {
      val S_SUPPKEY = S_SUPPKEY;
      ; {
        val R1_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY));
        var ex46:Long = 0L
        ex46 |= (((COUNT_mLINEITEM1_L2_1.get(S_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L2_3.get(S_SUPPKEY)))!=0;
        var agg39:Double = 0 //correct type???
        var agg40:Double = 0 //correct type???
        var ex47:Long = 0L
        COUNT_mLINEITEM1_L3_1_E1_1.foreach { case (k18,v18) =>
          val R2_SUPPKEY = k18;
          ex47 |= (((v18 * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY)))!=0;
          val R2_TOTAL_REVENUE = ((COUNT_mLINEITEM1_L3_1_E1_1.get(R2_SUPPKEY) * -1L) + COUNT_mLINEITEM1_L3_1_E1_3.get(R2_SUPPKEY));
          agg40 += (ex47 * (R2_TOTAL_REVENUE * (R2_TOTAL_REVENUE > R1_TOTAL_REVENUE)));
        }
        ; {
          val __domain_1 = agg40;
          agg39 += (__domain_1 * (__domain_1 == (0L)));
        }
        COUNT.add((S_SUPPKEY,S_NAME,S_ADDRESS,S_PHONE,R1_TOTAL_REVENUE),(S_SUPPKEY * (R1_TOTAL_REVENUE * (ex46 * (agg39 * -1L))).toLong));
      }
    }
    COUNT_mLINEITEM1.add((S_NAME,S_ADDRESS,S_PHONE,S_SUPPKEY),-1L);
*/
  }

  def onSystemReady() {

  }
}
