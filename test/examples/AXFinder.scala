package ddbt.test.examples
import ddbt.lib._
import akka.actor.Actor
/* SIMPLIFIED GENERATED VERSION */

object Axfinder0 {
  import Helper._
  def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long)=>run[Axfinder0](Seq(
    (new java.io.FileInputStream("/Documents/EPFL/Data/cornell_db_maybms/dbtoaster/experiments/data/finance/"+d+"/finance.csv"),new Adaptor.OrderBook(brokers=10,deterministic=true,bids="BIDS",asks="ASKS"),Split())
  ),p,t),f)

  def main(args:Array[String]) {
    execute(args,(res:List[Any])=>{
      // Correctness verification for standard dataset
      def kv(l:List[Any]) = l match { case List(v0:Long,v1:Double) => (v0,v1) }
      diff(res(0).asInstanceOf[Map[Long,Double]], Map[Long,Double]((6L,-2605617L),(9L,995180L),(0L,2446668L),(5L,3288320L),(1L,-648039L),(4L,8384852L),(2L,-5363809L),(7L,243551L),(3L,864240L),(8L,1565128L)))

      println("AXFINDER:\n"+M3Map.toStr(res(0))+"\n")
    })
  }
}

class Axfinder0 extends Actor {
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._

  val AXFINDER = M3Map.make[Long,Double]();
  val mASKS1 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1);
  val mASKS2 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1);
  val mBIDS1 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1);
  val mBIDS3 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1);

  var t0=0L; var t1=0L; var tN=0L; var tS=0L
  def receive_skip:Receive = { case EndOfStream | GetSnapshot(_) => sender ! (StreamStat(t1-t0,tN,tS),List(AXFINDER.toMap)) case _ => tS+=1 }
  def receive = {
    case TupleEvent(TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; context.become(receive_skip) } else tN+=1 } else tN+=1; onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; context.become(receive_skip) } else tN+=1 } else tN+=1; onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; context.become(receive_skip) } else tN+=1 } else tN+=1; onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; context.become(receive_skip) } else tN+=1 } else tN+=1; onDelASKS(v0,v1,v2,v3,v4)
    case StreamInit(timeout) => onSystemReady(); t0=System.nanoTime; if (timeout>0) t1=t0+timeout*1000000L
    case EndOfStream | GetSnapshot(_) => t1=System.nanoTime; sender ! (StreamStat(t1-t0,tN,tS),List(AXFINDER.toMap))
  }

  def onAddBIDS(t:Double, id:Long, br_id:Long, volume:Double, price:Double) {
    var agg1 = 0L
    mBIDS1.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg1 += v }
    var agg2 = 0.0
    mBIDS3.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg2 += v }
    AXFINDER.add(br_id,agg2 - agg1  * volume)
    mASKS1.add((br_id,price),volume)
    mASKS2.add((br_id,price),1L)
  }

  def onDelBIDS(t:Double, id:Long, br_id:Long, volume:Double, price:Double) {
    var agg3 = 0L
    mBIDS1.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg3 += v }
    var agg4 = 0.0
    mBIDS3.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg4 += v }
    AXFINDER.add(br_id,agg3 * volume - agg4)
    mASKS1.add((br_id,price),-volume)
    mASKS2.add((br_id,price),-1L)
  }

  def onAddASKS(t:Double, id:Long, br_id:Long, volume:Double, price:Double) {
    var agg5 = 0.0
    mASKS1.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg5 += v }
    var agg6 = 0L
    mASKS2.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg6 += v }
    AXFINDER.add(br_id,agg6*volume - agg5)
    mBIDS1.add((br_id,price),1L)
    mBIDS3.add((br_id,price),volume)
  }

  def onDelASKS(t:Double, id:Long, br_id:Long, volume:Double, price:Double) {
    var agg7 = 0.0
    mASKS1.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg7 += v }
    var agg8 = 0L
    mASKS2.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg8 += v }
    AXFINDER.add(br_id,agg7 - agg8 * volume)
    mBIDS1.add((br_id,price),-1L)
    mBIDS3.add((br_id,price),-volume)
  }

  def onSystemReady() { }
}
