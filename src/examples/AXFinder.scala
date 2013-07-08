package examples

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import ddbt.lib._

case class SourceFile(file:String,bufSize:Int=128*1024) {
  var r:ActorRef = null
  val d = Decoder((ev:TupleEvent)=>{ r ! ev })
  def setReceiver(receiver:ActorRef) { r=receiver }

  def readAll() {
    val in = new java.io.FileInputStream(file)
    val buf = new Array[Byte](bufSize)
    var n:Int = 0
    do { n=in.read(buf); d.add(buf,n); } while (n>0);
    in.close()
    r ! EndOfStream2
  }
}

case class SetSupervisor(actor:ActorRef)
case class Result(r:Any)

object AXFinder {
  val system = ActorSystem("DDBT")
  var t0:Long = 0
  def main(args:Array[String]) {
    val sup = system.actorOf(Props[Supervisor],"Supervisor")
    val act = system.actorOf(Props[AXFinder],"AXFinder")
    act ! SetSupervisor(sup)
    val s = new SourceFile("resources/data/finance.csv") // -standard
    s.setReceiver(act);
    t0 = System.nanoTime()
    s.readAll
  }
  class Supervisor extends Actor {
    def receive = {
      case Result(r) => println(r.toString)
      case EndOfStream2 =>
        val t1 = System.nanoTime()
        val t = (t1-t0) / 1000
        println("Running time: %d.%06d".format(t/1000000,t%1000000))
        system.shutdown
    }
  }
}


class AXFinder extends Actor {
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
    case EndOfStream2 => 
      sup ! Result(AXFINDER.dump)
      sup ! EndOfStream2
  }

  // Generated code. Completed by hand:
  // - Create/createIdx for maps
  // - Secondary indices of the maps
  // - Type of aggregation values
  // - Default value for maps

  val AXFINDER = K3Map.create[Long,Double](0,Nil);
  val AXFINDER_mASKS1 = K3Map.createIdx[(Long,Double),Double](0,List(0));
  val AXFINDER_mASKS2 = K3Map.createIdx[(Long,Double),Long](0,List(0));
  val AXFINDER_mBIDS1 = K3Map.createIdx[(Long,Double),Long](0,List(0));
  val AXFINDER_mBIDS3 = K3Map.createIdx[(Long,Double),Double](0,List(0));
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    var agg1:Double = 0;
    AXFINDER_mBIDS1.slice(0,BIDS_BROKER_ID).foreach { case (k2,v3) =>
      val A_PRICE = k2._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg1 = agg1 + (v3 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg4:Double = 0;
    AXFINDER_mBIDS3.slice(0,BIDS_BROKER_ID).foreach { case (k5,v6) =>
      val A_PRICE = k5._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg4 = agg4 + (v6 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg1 * -BIDS_VOLUME) + agg4));
    AXFINDER_mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    AXFINDER_mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),1L);
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    var agg7:Double = 0;
    AXFINDER_mBIDS1.slice(0,BIDS_BROKER_ID).foreach { case (k8,v9) =>
      val A_PRICE = k8._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg7 = agg7 + (v9 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg10:Double = 0;
    AXFINDER_mBIDS3.slice(0,BIDS_BROKER_ID).foreach { case (k11,v12) =>
      val A_PRICE = k11._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      agg10 = agg10 + (v12 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(BIDS_BROKER_ID,((agg7 * BIDS_VOLUME) + (agg10 * -1L)));
    AXFINDER_mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    AXFINDER_mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),-1L);
  }
  
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg13:Double = 0;
    AXFINDER_mASKS1.slice(0,ASKS_BROKER_ID).foreach { case (k14,v15) =>
      val B_PRICE = k14._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg13 = agg13 + (v15 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg16:Double = 0;
    AXFINDER_mASKS2.slice(0,ASKS_BROKER_ID).foreach { case (k17,v18) =>
      val B_PRICE = k17._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg16 = agg16 + (v18 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,((agg13 * -1L) + (agg16 * ASKS_VOLUME)));
    AXFINDER_mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    AXFINDER_mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }
  
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    var agg19:Double = 0;
    AXFINDER_mASKS1.slice(0,ASKS_BROKER_ID).foreach { case (k20,v21) =>
      val B_PRICE = k20._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg19 = agg19 + (v21 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    var agg22:Double = 0;
    AXFINDER_mASKS2.slice(0,ASKS_BROKER_ID).foreach { case (k23,v24) =>
      val B_PRICE = k23._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      agg22 = agg22 + (v24 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    }
    AXFINDER.add(ASKS_BROKER_ID,(agg19 + (agg22 * -ASKS_VOLUME)));
    AXFINDER_mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    AXFINDER_mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }
  
  def onSystemReady() {
    
  }

  /*
  val COUNT = new K3Map[Long,Long](0);
  val COUNT_mASKS2 = new K3Var[Long](0);
  val COUNT_mBIDS2 = new K3Var[Long](0);
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mBIDS2.get()));
    COUNT_mASKS2.add(1L);
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mBIDS2.get() * -1L)));
    COUNT_mASKS2.add(-1L);
  }
  
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * COUNT_mASKS2.get()));
    COUNT_mBIDS2.add(1L);
  }
  
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    val AXFINDER = 1L;
    COUNT.add(AXFINDER,(AXFINDER * (COUNT_mASKS2.get() * -1L)));
    COUNT_mBIDS2.add(-1L);
  }
  
  def onSystemReady() {
    
  }
  */
}
