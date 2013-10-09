package ddbt.test.examples
import ddbt.lib._

object AXFinderAkka extends Helper {
  import WorkerActor._
  def main(args:Array[String]) {
    val (t,res) = runLocal[AXMaster,AXWorker](5,2251,4,streamsFinance())
    println("Time = "+time(t)); println(K3Helper.toStr(res.head))
  }
}

class AXWorker extends WorkerActor {
  import WorkerActor._
  // constants
  val mAX = MapRef(0)
  val mA1 = MapRef(1)
  val mA2 = MapRef(2)
  val mB1 = MapRef(3)
  val mB3 = MapRef(4)
  val f0 = FunRef(0)
  val f1 = FunRef(1)
  val f2 = FunRef(2)
  val f3 = FunRef(3)
  // maps
  val AXFINDER = K3Map.make[Long,Double]();
  val mASKS1 = K3Map.makeIdx[(Long,Double),Double](List(0))
  val mASKS2 = K3Map.makeIdx[(Long,Double),Long](List(0))
  val mBIDS1 = K3Map.makeIdx[(Long,Double),Long](List(0))
  val mBIDS3 = K3Map.makeIdx[(Long,Double),Double](List(0))
  val local = Array[Any](AXFINDER,mASKS1,mASKS2,mBIDS1,mBIDS3)
  // aggregations
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = { co() }
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = {
    val a0 = args(0).asInstanceOf[Long] // broker_id
    val a1 = args(1).asInstanceOf[Double] // price
    f match {
      case `f0` => co(mBIDS1.slice(0,a0).aggr{ (k,v) => val a_price=k._2; val bids_price=a1 // Add/del BIDS
        val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); v * (if (lift1 > 0L) 1L else 0L) })
      case `f1` => co(mBIDS3.slice(0,a0).aggr{ (k,v) => val a_price=k._2; val bids_price=a1
        val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); v * (if (lift1 > 0L) 1L else 0L) })
      case `f2` => co(mASKS1.slice(0,a0).aggr{ (k,v) => val b_price=k._2; val asks_price=a1 // Add/del ASKS
        val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); v * (if (lift5 > 0L) 1L else 0L) })
      case `f3` => co(mASKS2.slice(0,a0).aggr{ (k,v) => val b_price=k._2; val asks_price=a1
        val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); v * (if (lift5 > 0L) 1L else 0L) })
    }
  }
}

class AXMaster extends AXWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import scala.util.continuations._

  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelASKS(v0,v1,v2,v3,v4)
  }
  def onAddBIDS(bids_t:Double, bids_id:Long, br_id:Long, vol:Double, price:Double) = /*reset*/ {
    // New format: no CPS plug-in required
    pre(mAX,Array(mB1,mB3),(u:Unit)=>{
    aggr(mB1,f0,Array[Any](br_id,price),null,null,(agg1:Long)=>{
    aggr(mB3,f1,Array[Any](br_id,price),null,null,(agg2:Double)=>{
    add(mAX,br_id,((agg1 * (-1L * vol)) + agg2));
    pre(mA1,Array[MapRef](),(u:Unit)=>{
    add(mA1,(br_id,price),vol)
    pre(mA2,Array[MapRef](),(u:Unit)=>{
    add(mA2,(br_id,price),1L)
    deq }) }) }) }) })
    /*
    _pre(mAX,mB1,mB3)
    val agg1 = _aggr[Long](mB1,f0,br_id,price);
    val agg2 = _aggr[Double](mB3,f1,br_id,price);
    add(mAX,br_id,((agg1 * (-1L * vol)) + agg2));
    _pre(mA1); add(mA1,(br_id,price),vol);
    _pre(mA2); add(mA2,(br_id,price),1L);
    deq
    */
  }
  def onDelBIDS(bids_t:Double, bids_id:Long, br_id:Long, vol:Double, price:Double) = reset {
    _pre(mAX,mB1,mB3)
    val agg3 = _aggr[Long](mB1,f0,br_id,price);
    val agg4 = _aggr[Double](mB3,f1,br_id,price);
    add(mAX,br_id,((agg3 * vol) + (agg4 * -1L)));
    _pre(mA1); add(mA1,(br_id,price),(-1L * vol));
    _pre(mA2); add(mA2,(br_id,price),-1L);
    deq
  }
  def onAddASKS(asks_t:Double, asks_id:Long, br_id:Long, vol:Double, price:Double) = reset {
    _pre(mAX,mA1,mA2)
    val agg5 = _aggr[Double](mA1,f2,br_id,price);
    val agg6 = _aggr[Long](mA2,f3,br_id,price);
    add(mAX,br_id,((agg5 * -1L) + (agg6 * vol)));
    _pre(mB1); add(mB1,(br_id,price),1L);
    _pre(mB3); add(mB3,(br_id,price),vol);
    deq
  }
  def onDelASKS(asks_t:Double, asks_id:Long, br_id:Long, vol:Double, price:Double) = reset {
    _pre(mAX,mA1,mA2)
    val agg7 = _aggr[Double](mA1,f2,br_id,price);
    val agg8 = _aggr[Long](mA2,f3,br_id,price);
    add(mAX,br_id,(agg7 + (agg8 * (-1L * vol))));
    _pre(mB1); add(mB1,(br_id,price),-1L);
    _pre(mB3); add(mB3,(br_id,price),(-1L * vol));
    deq
  }
  def onSystemReady() {}
}
