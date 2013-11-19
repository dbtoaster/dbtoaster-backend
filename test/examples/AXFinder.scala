package ddbt.test.examples
import ddbt.lib._

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import scala.reflect.ClassTag

object AXFinder {
  import Helper._
  def test[Q<:akka.actor.Actor](name:String,count:Int=10)(implicit cq:ClassTag[Q]) =
        bench(name,count,()=>run[Q](Seq(
    (new java.io.FileInputStream("/Documents/EPFL/Data/cornell_db_maybms/dbtoaster/experiments/data/finance/standard/finance.csv"),
     new Adaptor.OrderBook(brokers=10000,deterministic=true,bids="BIDS",asks="ASKS"),Split())
  ),false))

  def main(args:Array[String]) {
    //val r1=test[AXFinderRef]      ("Reference   ")
    val r2=test[AXFinder]         ("Gen2        "); //assert(r1==r2)
    val r4=test[AXFinderSimpleLMS]("Simple LMS  ")
    val r5=test[AXFinderSimple]   ("Simple Gen2 "); assert(r4==r5)
    println(r2.head)
  }
}

// -----------------------------------------------------------------------------
abstract class AXFinderBase extends Actor {
  import Messages._
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  //override def preStart(): Unit = println("Started")
  //override def postStop(): Unit = println("Stopped")
  def result:Any
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"BIDS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,List(result))
  }
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double):Unit
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double):Unit
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double):Unit
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double):Unit
}

// -----------------------------------------------------------------------------
class AXFinder extends AXFinderBase {
  val AXFINDER = M3Map.make[Long,Double]();
  val mASKS1 = M3Map.makeIdx[(Long,Double),Double](0);
  val mASKS2 = M3Map.makeIdx[(Long,Double),Long](0);
  val mBIDS1 = M3Map.makeIdx[(Long,Double),Long](0);
  val mBIDS3 = M3Map.makeIdx[(Long,Double),Double](0);
  def result = AXFINDER

  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg1:Long = 0;
    mBIDS1.slice(0,bids_broker_id).foreach { (k1,v1) =>
      val a_price = k1._2;
      val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
      agg1 += (v1 * (if (lift1 > 0L) 1L else 0L));
    }
    var agg2:Double = 0;
    mBIDS3.slice(0,bids_broker_id).foreach { (k2,v2) =>
      val a_price = k2._2;
      val lift2 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
      agg2 += (v2 * (if (lift2 > 0L) 1L else 0L));
    }
    AXFINDER.add(bids_broker_id,((agg1 * (-1L * bids_volume)) + agg2));
    mASKS1.add((bids_broker_id,bids_price),bids_volume);
    mASKS2.add((bids_broker_id,bids_price),1L);
  }

  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg3:Long = 0;
    mBIDS1.slice(0,bids_broker_id).foreach { (k3,v3) =>
      val a_price = k3._2;
      val lift3 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
      agg3 += (v3 * (if (lift3 > 0L) 1L else 0L));
    }
    var agg4:Double = 0;
    mBIDS3.slice(0,bids_broker_id).foreach { (k4,v4) =>
      val a_price = k4._2;
      val lift4 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
      agg4 += (v4 * (if (lift4 > 0L) 1L else 0L));
    }
    AXFINDER.add(bids_broker_id,((agg3 * bids_volume) + (agg4 * -1L)));
    mASKS1.add((bids_broker_id,bids_price),(-1L * bids_volume));
    mASKS2.add((bids_broker_id,bids_price),-1L);
  }

  def onAddASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    var agg5:Double = 0;
    mASKS1.slice(0,asks_broker_id).foreach { (k5,v5) =>
      val b_price = k5._2;
      val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
      agg5 += (v5 * (if (lift5 > 0L) 1L else 0L));
    }
    var agg6:Long = 0;
    mASKS2.slice(0,asks_broker_id).foreach { (k6,v6) =>
      val b_price = k6._2;
      val lift6 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
      agg6 += (v6 * (if (lift6 > 0L) 1L else 0L));
    }
    AXFINDER.add(asks_broker_id,((agg5 * -1L) + (agg6 * asks_volume)));
    mBIDS1.add((asks_broker_id,asks_price),1L);
    mBIDS3.add((asks_broker_id,asks_price),asks_volume);
  }

  def onDelASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    var agg7:Double = 0;
    mASKS1.slice(0,asks_broker_id).foreach { (k7,v7) =>
      val b_price = k7._2;
      val lift7 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
      agg7 += (v7 * (if (lift7 > 0L) 1L else 0L));
    }
    var agg8:Long = 0;
    mASKS2.slice(0,asks_broker_id).foreach { (k8,v8) =>
      val b_price = k8._2;
      val lift8 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
      agg8 += (v8 * (if (lift8 > 0L) 1L else 0L));
    }
    AXFINDER.add(asks_broker_id,(agg7 + (agg8 * (-1L * asks_volume))));
    mBIDS1.add((asks_broker_id,asks_price),-1L);
    mBIDS3.add((asks_broker_id,asks_price),(-1L * asks_volume));
  }
}

// -----------------------------------------------------------------------------
class AXFinderSimple extends AXFinderBase {
  val COUNT = M3Map.make[Long,Long]();
  var COUNT_mASKS2:Long = 0L;
  var COUNT_mBIDS2:Long = 0L;
  def result = COUNT

  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mBIDS2));
    COUNT_mASKS2 += 1L;
  }
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mBIDS2 * -1L)));
    COUNT_mASKS2 += -1L;
  }
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mASKS2));
    COUNT_mBIDS2 += 1L;
  }
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mASKS2 * -1L)));
    COUNT_mBIDS2 += -1L;
  }
}

// -----------------------------------------------------------------------------
// Original result: 1 -> 270

class AXFinderSimpleLMS extends AXFinderBase {
  val COUNT = M3Map.make[Long,Long](); // out
  var COUNT_mASKS2:Long = 0L;
  var COUNT_mBIDS2:Long = 0L;
  def result = COUNT

  def onAddBIDS(COUNT4: Double, COUNT5: Long, COUNT6: Long, COUNT7: Double, COUNT8: Double): Unit = {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val COUNT_mASKS25 = COUNT_mBIDS2
    x9.foreach { COUNT_mASKS22 =>
      val COUNT_mASKS23 = COUNT_mASKS22._1
      val COUNT_mASKS24 = COUNT_mASKS22._2
      val COUNT_mASKS26 = COUNT_mASKS24 * COUNT_mASKS25
      val COUNT_mASKS28 = COUNT.get(COUNT_mASKS23)!=0L
      val COUNT_mBIDS20 = if (COUNT_mASKS28) COUNT.get(COUNT_mASKS23) else 0L
      val COUNT_mBIDS21 = COUNT_mBIDS20 + COUNT_mASKS26
      COUNT.set(COUNT_mASKS23, COUNT_mBIDS21)
    }
    val COUNT_mBIDS25 = COUNT_mASKS2
    val COUNT_mBIDS26 = COUNT_mBIDS25 + 1L
    COUNT_mASKS2 = COUNT_mBIDS26
   }

  def onDelBIDS(COUNT_mBIDS29: Double, x80: Long, x81: Long, x82: Double, x83: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x90 = COUNT_mBIDS2
    x9.foreach { x87 =>
      val x88 = x87._1
      val x89 = x87._2
      val x91 = x89 * x90
      val x93 = x91 * -1L
      val x95 = COUNT.get(x88)!=0L
      val x97 = if (x95) COUNT.get(x88) else 0L
      val x98 = x97 + x93
      COUNT.set(x88, x98)
    }
    val x102 = COUNT_mASKS2
    val x103 = x102 + -1L
    COUNT_mASKS2 = x103
   }

  def onAddASKS(x0: Double, x1: Long, x2: Long, x3: Double, x4: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x13 = COUNT_mASKS2
    x9.foreach { x10 =>
      val x11 = x10._1
      val x12 = x10._2
      val x14 = x12 * x13
      val x16 = COUNT.get(x11)!=0L
      val x18 = if (x16) COUNT.get(x11) else 0L
      val x19 = x18 + x14
      COUNT.set(x11, x19)
    }
    val x23 = COUNT_mBIDS2
    val x24 = x23 + 1L
    COUNT_mBIDS2 = x24
   }

  def onDelASKS(x27: Double, x28: Long, x29: Long, x30: Double, x31: Double) {
    val x8 = (1L, 1L)
    val x9 = List(x8)
    val x38 = COUNT_mASKS2
    x9.foreach { x35 =>
      val x36 = x35._1
      val x37 = x35._2
      val x39 = x37 * x38
      val x41 = x39 * -1L
      val x43 = COUNT.get(x36)!=0L
      val x45 = if (x43) COUNT.get(x36) else 0L
      val x46 = x45 + x41
      COUNT.set(x36, x46)
    }
    val COUNT0 = COUNT_mBIDS2
    val COUNT1 = COUNT0 + -1L
    COUNT_mBIDS2 = COUNT1
   }
}
