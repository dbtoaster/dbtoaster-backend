package ddbt.test.examples
import ddbt.lib._
/*
 * Hand-Optimized AxFinder-Akka
 * SPECIALIZED PARTITIONING (broker_id)
 * VoltDB-style partitioning
 *
 * Scala : 0.030s
 * Akka  : 5.455s
 * NonSeq: 4.252s
 * VoltDB: 0.135s (40x speedup)
 *
 */

object Axfinder3 {
  import Helper._
  def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long,b:Int,no_output:Boolean)=>runLocal[Axfinder3Master,Axfinder3Worker](args)(Seq(
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

class Axfinder3Worker extends WorkerActor {
  import ddbt.lib.Functions._
  import ddbt.lib.Messages._
  // constants
  val fa1=0; val fa2=1; val fa5=2; val fa6=3;

  // maps
  val AXFINDER = M3Map.make[Long,Double](); // map0
  val mASKS1 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1); // map1
  val mASKS2 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1); // map2
  val mBIDS1 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1); // map3
  val mBIDS3 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1); // map4
  val local = Array[M3Map[_,_]](AXFINDER,mASKS1,mASKS2,mBIDS1,mBIDS3)
  override def hash(m:MapRef,k:Any) = m match {
    case 0 => k.asInstanceOf[Long].toInt
    case _ => k.asInstanceOf[Product].productElement(0).asInstanceOf[Long].toInt
  }

  val (addBIDS,delBIDS,addASKS,delASKS)=(0,1,2,3)
  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:()=>Unit) = {
    val br_id = args(0).asInstanceOf[Long]
    val volume = args(1).asInstanceOf[Double]
    val price = args(2).asInstanceOf[Double]
    f match {
      case `addBIDS` =>
        var agg1 = 0L
        mBIDS1.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg1 += v }
        var agg2 = 0.0
        mBIDS3.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg2 += v }
        AXFINDER.add(br_id,agg2 - agg1  * volume)
        mASKS1.add((br_id,price),volume)
        mASKS2.add((br_id,price),1L)
        co()
      case `delBIDS` =>
        var agg3 = 0L
        mBIDS1.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg3 += v }
        var agg4 = 0.0
        mBIDS3.slice(0,br_id).foreach { (k,v) => if (k._2-price > 1000L || price-k._2 > 1000L) agg4 += v }
        AXFINDER.add(br_id,agg3 * volume - agg4)
        mASKS1.add((br_id,price),-volume)
        mASKS2.add((br_id,price),-1L)
        co()
      case `addASKS` =>
        var agg5 = 0.0
        mASKS1.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg5 += v }
        var agg6 = 0L
        mASKS2.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg6 += v }
        AXFINDER.add(br_id,agg6*volume - agg5)
        mBIDS1.add((br_id,price),1L)
        mBIDS3.add((br_id,price),volume)
        co()
      case `delASKS` =>
        var agg7 = 0.0
        mASKS1.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg7 += v }
        var agg8 = 0L
        mASKS2.slice(0,br_id).foreach { (k,v) => if (price-k._2 > 1000L || k._2-price > 1000L) agg8 += v }
        AXFINDER.add(br_id,agg7 - agg8 * volume)
        mBIDS1.add((br_id,price),-1L)
        mBIDS3.add((br_id,price),-volume)
        co()
      case _ => co()
    }
  }

  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = co(null)
}

class Axfinder3Master extends Axfinder3Worker with MasterActor {
  import Messages._

  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(_,TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(_,TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => if (t1>0 && (tN&127)==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; skip=true } else tN+=1 } else tN+=1; onDelASKS(v0,v1,v2,v3,v4)
    case _ => deq
  }
  def onAddBIDS(t:Double, id:Long, broker_id:Long, volume:Double, price:Double) { rpc(0,broker_id, addBIDS, broker_id,volume,price); deq }
  def onDelBIDS(t:Double, id:Long, broker_id:Long, volume:Double, price:Double) { rpc(0,broker_id, delBIDS, broker_id,volume,price); deq }
  def onAddASKS(t:Double, id:Long, broker_id:Long, volume:Double, price:Double) { rpc(0,broker_id, addASKS, broker_id,volume,price); deq }
  def onDelASKS(t:Double, id:Long, broker_id:Long, volume:Double, price:Double) { rpc(0,broker_id, delASKS, broker_id,volume,price); deq }
  def onSystemReady() { ready }
}
