package examples

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import ddbt.lib._

object AXFinderAkka {
  import Helper._

  def main(args:Array[String]) {
    val act = system.actorOf(Props[AXFinder],"AXFinder")
    act ! SetSupervisor(supervisor)
    val s = new SourceFile("resources/data/finance.csv") // -standard
    s.setReceiver(act);
    supervisor ! StartTimer
    s.readAll
  }
}

class AXFinderAkka extends Actor {
  import Helper._
  var sup:ActorRef = null
  
  // This is manually written for the moment, needs to go into ddbt.lib
  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
  
  override def preStart(): Unit = println("Started")
  override def postStop(): Unit = println("Stopped")
  def receive = {
    case SetSupervisor(s) => sup=s
    case TupleEvent(TupleInsert,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
    case EndOfStream => 
      sup ! Result(AXFINDER.toMap)
      sup ! EndOfStream
  }

  val idx = List((x:(Long,Double))=>x._1)
  val AXFINDER = K4Map.make[Long,Double](system,8);
  val mASKS1 = K4Map.make[(Long,Double),Double](system,8,idx);
  val mASKS2 = K4Map.make[(Long,Double),Long](system,8,idx);
  val mBIDS1 = K4Map.make[(Long,Double),Long](system,8,idx);
  val mBIDS3 = K4Map.make[(Long,Double),Double](system,8,idx);
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    var agg1:Double = 0;
    mBIDS1.foreach((0,BIDS_BROKER_ID)) { case (k2,v3) =>
      val A_PRICE = k2._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg1 = agg1 + (v3 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg4:Double = 0;
    mBIDS3.foreach((0,BIDS_BROKER_ID)) { case (k5,v6) =>
      val A_PRICE = k5._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg4 = agg4 + (v6 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg1 * -BIDS_VOLUME) + agg4));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),1L);
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    var agg7:Double = 0;
    mBIDS1.foreach((0,BIDS_BROKER_ID)) { case (k8,v9) =>
      val A_PRICE = k8._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg7 = agg7 + (v9 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg10:Double = 0;
    mBIDS3.foreach((0,BIDS_BROKER_ID)) { case (k11,v12) =>
      val A_PRICE = k11._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg10 = agg10 + (v12 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg7 * BIDS_VOLUME) + (agg10 * -1L)));
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),-1L);
  }
  
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg13:Double = 0;
    mASKS1.foreach((0,ASKS_BROKER_ID)) { case (k14,v15) =>
      val B_PRICE = k14._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg13 = agg13 + (v15 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg16:Double = 0;
    mASKS2.foreach((0,ASKS_BROKER_ID)) { case (k17,v18) =>
      val B_PRICE = k17._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg16 = agg16 + (v18 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,((agg13 * -1L) + (agg16 * ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }
  
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg19:Double = 0;
    mASKS1.foreach((0,ASKS_BROKER_ID)) { case (k20,v21) =>
      val B_PRICE = k20._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg19 = agg19 + (v21 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg22:Double = 0;
    mASKS2.foreach((0,ASKS_BROKER_ID)) { case (k23,v24) =>
      val B_PRICE = k23._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg22 = agg22 + (v24 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,(agg19 + (agg22 * -ASKS_VOLUME)));
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }
  
  def onSystemReady() {
    
  }
}
