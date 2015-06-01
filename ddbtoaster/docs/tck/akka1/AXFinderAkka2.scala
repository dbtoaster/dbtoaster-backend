package examples

import ddbt.lib._
import akka.actor.Props

object AXFinderAkka2 extends Helper {
  //import Messages._
  def main(args:Array[String]) {
    val (t,res) = runLocal[AXFinderMaster,AXFinderWorker,Map[Long,Double]](2251,4,streamsFinance())
    println(time(t)); println(K3Helper.toStr(res))
    //K3Helper.toStr(bench("AXFinderAkka2(Network)",10,()=>runLocal[AXFinderMaster,AXFinderWorker,Map[Long,Double]](2251,4,streamsFinance("standard")) ))
  }
}

class AXFinderWorker extends WorkerActor {
  import WorkerActor._

  val AXFINDER = K3Map.make[Long,Double]();
  val mASKS1 = K3Map.makeIdx[(Long,Double),Double](List(0));
  val mASKS2 = K3Map.makeIdx[(Long,Double),Long](List(0));
  val mBIDS1 = K3Map.makeIdx[(Long,Double),Long](List(0));
  val mBIDS3 = K3Map.makeIdx[(Long,Double),Double](List(0));

  def local[K,V](m:MapRef) = (m match {
    case 0 => AXFINDER
    case 1 => mASKS1
    case 2 => mASKS2
    case 3 => mBIDS1
    case 4 => mBIDS3
    case _ => sys.error("No such map")
  }).asInstanceOf[K3Map[K,V]]

  val aggs = List(
    // Add/del BIDS
    (args:List[Any]) => mBIDS1.slice(0,args(0).asInstanceOf[Double].toLong).aggr { case (k,v) => val a_price = k._2; val bids_price = args(1).asInstanceOf[Double]
       val __sql_inline_or_1 = (((a_price - bids_price) > 1000L) + ((bids_price - a_price) > 1000L)); v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    },
    (args:List[Any]) => mBIDS3.slice(0,args(0).asInstanceOf[Double].toLong).aggr { case (k,v) => val a_price = k._2; val bids_price = args(1).asInstanceOf[Double]
      val __sql_inline_or_1 = (((a_price - bids_price) > 1000L) + ((bids_price - a_price) > 1000L)); v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    },
    // Add/del ASKS
    (args:List[Any]) => mASKS1.slice(0,args(0).asInstanceOf[Double].toLong).aggr { case (k,v) => val b_price = k._2; val asks_price = args(1).asInstanceOf[Double]
      val __sql_inline_or_1 = (((asks_price - b_price) > 1000L) + ((b_price - asks_price) > 1000L)); v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    },
    (args:List[Any]) => mASKS2.slice(0,args(0).asInstanceOf[Double].toLong).aggr { case (k,v) => val b_price = k._2; val asks_price = args(1).asInstanceOf[Double]
      val __sql_inline_or_1 = (((asks_price - b_price) > 1000L) + ((b_price - asks_price) > 1000L)); v * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    }
  )
  
  def myReceive : PartialFunction[Any,Unit] = {
    case Aggr(id,f,args) => sender ! AggrPart(id,aggs(f)(args))
  }
  override def receive = myReceive orElse super.receive
}
class AXFinderMaster(props:Array[Props]) extends MasterActor(props) {
  import WorkerActor._
  import Messages._
  val map:MapRef = 0

  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    case TupleEvent(TupleInsert,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
  }
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    pre(0,List(3,4))
    aggr(0,List(BIDS_BROKER_ID,BIDS_PRICE),(a1:Long) =>
      aggr(1,List(BIDS_BROKER_ID,BIDS_PRICE),(a2:Double) =>
        (0:MapRef).add(BIDS_BROKER_ID,((a1 * -BIDS_VOLUME) + a2))
      )
    )
    pre(1)
    (1:MapRef).add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME)
    pre(2)
    (2:MapRef).add((BIDS_BROKER_ID,BIDS_PRICE),1L)
  }
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    pre(0,List(3,4))
    aggr(0,List(BIDS_BROKER_ID,BIDS_PRICE),(a1:Long) =>
      aggr(1,List(BIDS_BROKER_ID,BIDS_PRICE),(a2:Double) =>
        (0:MapRef).add(BIDS_BROKER_ID,((a1 * BIDS_VOLUME) - a2))
      )
    )
    pre(1)
    (1:MapRef).add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME)
    pre(2)
    (2:MapRef).add((BIDS_BROKER_ID,BIDS_PRICE),-1L)
  }
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    pre(0,List(1,2))
    aggr(2,List(ASKS_BROKER_ID,ASKS_PRICE),(a1:Double) =>
      aggr(3,List(ASKS_BROKER_ID,ASKS_PRICE),(a2:Long) =>
        (0:MapRef).add(ASKS_BROKER_ID,((a2 * ASKS_VOLUME) - a1))
      )
    )
    pre(3)
    (3:MapRef).add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    pre(4)
    (4:MapRef).add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
  }
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    pre(0,List(1,2))
    aggr(2,List(ASKS_BROKER_ID,ASKS_PRICE),(a1:Double) =>
      aggr(3,List(ASKS_BROKER_ID,ASKS_PRICE),(a2:Long) =>
        (0:MapRef).add(ASKS_BROKER_ID,((a2 * -ASKS_VOLUME) + a1))
      )
    )
    pre(3)
    (3:MapRef).add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    pre(4)
    (4:MapRef).add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
  }
}
