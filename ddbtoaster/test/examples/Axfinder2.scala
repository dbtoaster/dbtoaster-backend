package ddbt.test.examples
import ddbt.lib._
/*
 * Hand-Optimized AxFinder-Akka
 * NON-SEQUENTIAL STATEMENTS
 */

object Axfinder2 {
  import Helper._
  def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long,b:Int,no_output:Boolean)=>runLocal[Axfinder2Master,Axfinder2Worker](args)(Seq(
    (new java.io.FileInputStream("/Documents/EPFL/Data/cornell_db_maybms/dbtoaster/experiments/data/finance/"+d+"/finance.csv"),new Adaptor.OrderBook(brokers=10,deterministic=true,bids="BIDS",asks="ASKS"),Split())
  ),p,t),f)
  def main(args:Array[String]) {
    import scala.language.implicitConversions
    execute(args,(res:List[Any])=>{
      // Standard dataset
      def kv(l:List[Any]) = l match { case List(v0:Long,v1:Double) => (v0,v1) }
      diff(res(0).asInstanceOf[Map[Long,Double]], Map[Long,Double]((6L,-2605617L),(9L,995180L),(0L,2446668L),(5L,3288320L),(1L,-648039L),(4L,8384852L),(2L,-5363809L),(7L,243551L),(3L,864240L),(8L,1565128L)))
      println("AXFINDER:\n"+M3Map.toStr(res(0))+"\n")
    })
  }
}

class Axfinder2Worker extends WorkerActor {
  import ddbt.lib.Functions._
  import ddbt.lib.Messages._
  // constants
  val fa1=0; val fa2=1; val fa5=2; val fa6=3;

  // maps
  val AXFINDER = M3Map.make[Long,Double](); // map0
  val AXFINDER_mASKS1 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1); // map1
  val AXFINDER_mASKS2 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1); // map2
  val AXFINDER_mBIDS1 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1); // map3
  val AXFINDER_mBIDS3 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1); // map4
  val local = Array[M3Map[_,_]](AXFINDER,AXFINDER_mASKS1,AXFINDER_mASKS2,AXFINDER_mBIDS1,AXFINDER_mBIDS3)

  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:()=>Unit) = (f,args.toList) match {
    case _ => co()
  }

  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {
    case (`fa1`,List(bids_price:Double,bids_broker_id:Long)) =>
      var agg1:Long = 0;
      AXFINDER_mBIDS1.slice(0,bids_broker_id).foreach { (k1,v1) =>
        val a_price = k1._2;
        val l1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
        agg1 += (if (l1 > 0L) v1 else 0L);
      }
      co(agg1)
    case (`fa2`,List(bids_price:Double,bids_volume:Double,bids_broker_id:Long)) =>
      var agg2:Double = 0;
      AXFINDER_mBIDS3.slice(0,bids_broker_id).foreach { (k2,v2) =>
        val a_price = k2._2;
        val l2 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
        agg2 += (if (l2 > 0L) v2 else 0.0);
      }
      co(agg2)
    case (`fa5`,List(asks_broker_id:Long,asks_price:Double)) =>
      var agg5:Double = 0;
      AXFINDER_mASKS1.slice(0,asks_broker_id).foreach { (k5,v5) =>
        val b_price = k5._2;
        val l5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
        agg5 += (if (l5 > 0L) v5 else 0.0);
      }
      co(agg5)
    case (`fa6`,List(asks_broker_id:Long,asks_price:Double)) =>
      var agg6:Long = 0;
      AXFINDER_mASKS2.slice(0,asks_broker_id).foreach { (k6,v6) =>
        val b_price = k6._2;
        val l6 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
        agg6 += (if (l6 > 0L) v6 else 0L);
      }
      co(agg6)
    case _ => co(null)
  }
}

class Axfinder2Master extends Axfinder2Worker with MasterActor {
  import Messages._
  import Functions._

  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(_,TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onDelASKS(v0,v1,v2,v3,v4)
    case _ => deq
  }

  val a=Acc()

  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre2(0,1,2)(true,true,true)(3,4){
      a.i
      val b=Acc(); b.inc(2)
      var a1 = 0L
      var a2 = 0.0
      aggr(3,fa1,bids_price,bids_broker_id)(null){(agg1:Long) => a1=agg1; b.d }
      aggr(4,fa2,bids_price,bids_volume,bids_broker_id)(null){(agg2:Double) => a2=agg2; b.d }
      b{ add(0,bids_broker_id,a2 - a1 * bids_volume); a.d }
      add(1,(bids_broker_id,bids_price),bids_volume);
      add(2,(bids_broker_id,bids_price),1L);
      a(deq)
    }
  }

  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre2(0,1,2)(true,true,true)(3,4){
      a.i
      val b=Acc(); b.inc(2)
      var a3 = 0L
      var a4 = 0.0
      aggr(3,fa1,bids_price,bids_broker_id)(null){(agg3:Long) => a3=agg3; b.d }
      aggr(4,fa2,bids_price,bids_volume,bids_broker_id)(null){(agg4:Double) => a4=agg4; b.d }
      b{ add(0,bids_broker_id,(a3 * bids_volume - a4)); a.d }
      add(1,(bids_broker_id,bids_price),(-1L * bids_volume));
      add(2,(bids_broker_id,bids_price),-1L);
      a(deq)
    }
  }

  def onAddASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre2(0,3,4)(true,true,true)(1,2){
      a.i
      val b=Acc(); b.inc(2)
      var a5 = 0.0
      var a6 = 0L
      aggr(1,fa5,asks_broker_id,asks_price)(null){(agg5:Double) => a5=agg5; b.d }
      aggr(2,fa6,asks_broker_id,asks_price)(null){(agg6:Long) => a6=agg6; b.d }
      b{ add(0,asks_broker_id,a6 * asks_volume - a5); a.d }
      add(3,(asks_broker_id,asks_price),1L);
      add(4,(asks_broker_id,asks_price),asks_volume);
      a(deq)
    }
  }

  def onDelASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre2(0,3,4)(true,true,true)(1,2){
      a.i
      val b=Acc(); b.inc(2)
      var a7 = 0.0
      var a8 = 0L
      aggr(1,fa5,asks_broker_id,asks_price)(null){(agg7:Double) => a7=agg7; b.d }
      aggr(2,fa6,asks_broker_id,asks_price)(null){(agg8:Long) => a8=agg8; b.d }
      b{ add(0,asks_broker_id,a7 - a8 * asks_volume); a.d }
      add(3,(asks_broker_id,asks_price),-1L);
      add(4,(asks_broker_id,asks_price),(-1L * asks_volume));
      a(deq)
    }
  }

  def onSystemReady() {
    ready
  }
}
