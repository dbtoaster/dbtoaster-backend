package ddbt.test.examples
import ddbt.lib._

object AX {
  //def streams(ds:String) = Helper.streamsFinance()
  def streams(d:String="standard") = Seq(
    (new java.io.FileInputStream("/Documents/EPFL/Data/cornell_db_maybms/dbtoaster/experiments/data/finance/"+d+"/finance.csv"),
     new Adaptor.OrderBook(brokers=10000,deterministic=true,bids="BIDS",asks="ASKS"),Split())
  )
}

object AXFinderAkka {
  import Helper._
  import WorkerActor._
  def main(args:Array[String]) {
    var i=0; do {
      val (t,res) = runLocal[AXMaster,AXWorker](2251,4,AX.streams() /*,debug=true*/)
      println("Time = "+t); // println(M3Map.toStr(res.head))
    i+=1; } while (i<10);
  }
}

class AXWorker extends WorkerActor {
  import WorkerActor._
  import ddbt.lib.Functions._
  import ddbt.lib.Messages._
  // constants
  val map0 = /*MapRef*/(0)
  val map1 = /*MapRef*/(1)
  val map2 = /*MapRef*/(2)
  val map3 = /*MapRef*/(3)
  val map4 = /*MapRef*/(4)
  val fa1 = /*FunRef*/(0)
  val fa2 = /*FunRef*/(1)
  val fa5 = /*FunRef*/(2)
  val fa6 = /*FunRef*/(3)

  // maps
  val AXFINDER = M3Map.make[Long,Double]();
  val AXFINDER_mASKS1 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1);
  val AXFINDER_mASKS2 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1);
  val AXFINDER_mBIDS1 = M3Map.make[(Long,Double),Long]((k:(Long,Double))=>k._1);
  val AXFINDER_mBIDS3 = M3Map.make[(Long,Double),Double]((k:(Long,Double))=>k._1);
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
        val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
        agg1 += (v1 * (if (lift1 > 0L) 1L else 0L));
      }
      co(agg1)
    case (`fa2`,List(bids_price:Double,bids_volume:Double,bids_broker_id:Long)) =>
      var agg2:Double = 0;
      AXFINDER_mBIDS3.slice(0,bids_broker_id).foreach { (k2,v2) =>
        val a_price = k2._2;
        val lift2 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L));
        agg2 += (v2 * (if (lift2 > 0L) 1L else 0L));
      }
      co(agg2)
    case (`fa5`,List(asks_broker_id:Long,asks_price:Double)) =>
      var agg5:Double = 0;
      AXFINDER_mASKS1.slice(0,asks_broker_id).foreach { (k5,v5) =>
        val b_price = k5._2;
        val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
        agg5 += (v5 * (if (lift5 > 0L) 1L else 0L));
      }
      co(agg5)
    case (`fa6`,List(asks_broker_id:Long,asks_price:Double)) =>
      var agg6:Long = 0;
      AXFINDER_mASKS2.slice(0,asks_broker_id).foreach { (k6,v6) =>
        val b_price = k6._2;
        val lift6 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L));
        agg6 += (v6 * (if (lift6 > 0L) 1L else 0L));
      }
      co(agg6)
    case _ => co(null)
  }
}

class AXMaster extends AXWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import Functions._

  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelASKS(v0,v1,v2,v3,v4)
    case _ => deq
  }

  // time=5.848s / rtt=0.484ms, 5000 records, 0.220s locally
  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre2(Array(map0,map1,map2),Array(true,true,true),Array(map3,map4),()=>{
      var ctr = 2 // + 1 to avoid in-loop depletion
      var ctr2 = 2
      var agg1:Long = 0L
      var agg2:Double = 0.0
      aggr(map3,fa1,Array[Any](bids_price,bids_broker_id),null,(v:Long) => { agg1=v; ctr-=1; if (ctr==0) op })
      aggr(map4,fa2,Array[Any](bids_price,bids_volume,bids_broker_id),null,(v:Double) => { agg2=v; ctr-=1; if (ctr==0) op })
      def op { add(map0,bids_broker_id,((agg1 * (-1L * bids_volume)) + agg2)); ctr2-=1; if (ctr2==0) deq }
      add(map1,(bids_broker_id,bids_price),bids_volume)
      add(map2,(bids_broker_id,bids_price),1L)
      ctr2-=1; if (ctr2==0) deq
    })
  }
  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre2(Array(map0,map1,map2),Array(true,true,true),Array(map3,map4),()=>{
      var ctr = 2 // + 1 to avoid in-loop depletion
      var ctr2 = 2
      var agg1:Long = 0L
      var agg2:Double = 0.0
      aggr(map3,fa1,Array[Any](bids_price,bids_broker_id),null,(v:Long) => { agg1=v; ctr-=1; if (ctr==0) op })
      aggr(map4,fa2,Array[Any](bids_price,bids_volume,bids_broker_id),null,(v:Double) => { agg2=v; ctr-=1; if (ctr==0) op })
      def op { add(map0,bids_broker_id,((agg1 * bids_volume) - agg2)); ctr2-=1; if (ctr2==0) deq }
      add(map1,(bids_broker_id,bids_price),-bids_volume)
      add(map2,(bids_broker_id,bids_price),-1L)
      ctr2-=1; if (ctr2==0) deq
    })
  }
  def onAddASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre2(Array(map0,map3,map4),Array(true,true,true),Array(map1,map2),()=>{
      var ctr = 2 // + 1 to avoid in-loop depletion
      var ctr2 = 2
      var agg5:Double = 0.0
      var agg6:Long = 0L
      aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(v:Double) => { agg5=v; ctr-=1; if (ctr==0) op })
      aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(v:Long) => { agg6=v; ctr-=1; if (ctr==0) op })
      def op { add(map0,asks_broker_id,((agg5 * -1L) + (agg6 * asks_volume))); ctr2-=1; if (ctr2==0) deq }
      add(map3,(asks_broker_id,asks_price),1L);
      add(map4,(asks_broker_id,asks_price),asks_volume);
      ctr2-=1; if (ctr2==0) deq
    })
  }
  def onDelASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre2(Array(map0,map3,map4),Array(true,true,true),Array(map1,map2),()=>{
      var ctr = 2 // + 1 to avoid in-loop depletion
      var ctr2 = 2
      var agg5:Double = 0.0
      var agg6:Long = 0L
      aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(v:Double) => { agg5=v; ctr-=1; if (ctr==0) op })
      aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(v:Long) => { agg6=v; ctr-=1; if (ctr==0) op })
      def op { add(map0,asks_broker_id,(agg5 - (agg6 * asks_volume))); ctr2-=1; if (ctr2==0) deq }
      add(map3,(asks_broker_id,asks_price),-1L);
      add(map4,(asks_broker_id,asks_price),-asks_volume);
      ctr2-=1; if (ctr2==0) deq
    })
/*
    s1
    def s1 = pre(map0,false,Array[MapRef](map1,map2),()=> {
      val acc = Acc(); acc.i; acc.i
      var agg5:Double = 0.0
      var agg6:Long = 0L
      aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(v:Double) => { agg5=v; acc.d })
      aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(v:Long) => { agg6=v; acc.d })
      acc(()=>{ add(map0,asks_broker_id,agg5 - (agg6 * asks_volume)); s2 })
    })
    def s2 = pre(map3,false,Array(),()=> { add(map3,(asks_broker_id,asks_price),-1L); s3 })
    def s3 = pre(map4,false,Array(),()=> { add(map4,(asks_broker_id,asks_price),-asks_volume); deq })
*/
  }




  /*
  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre(map0,false,Array[MapRef](map3,map4),()=> {

    val acc = Acc(); acc.i; acc.i
    var agg1:Long = 0L
    var agg2:Double = 0.0
    aggr(map3,fa1,Array[Any](bids_price,bids_broker_id),null,(v:Long) => { agg1=v; acc.d })
    aggr(map4,fa2,Array[Any](bids_price,bids_volume,bids_broker_id),null,(v:Double) => { agg2=v; acc.d })
    acc(()=>{ add(map0,bids_broker_id,((agg1 * (-1L * bids_volume)) + agg2)); })

    pre(map1,false,Array[MapRef](),()=> {
    add(map1,(bids_broker_id,bids_price),bids_volume);
    pre(map2,false,Array[MapRef](),()=> {
    add(map2,(bids_broker_id,bids_price),1L);
    deq
    }) }) })
  }

  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    pre(map0,false,Array[MapRef](map3,map4),()=> {

    val acc = Acc(); acc.i; acc.i
    var agg3:Long = 0L
    var agg4:Double = 0.0
    aggr(map3,fa1,Array(bids_price,bids_broker_id),null,(v:Long) => { agg3=v; acc.d })
    aggr(map4,fa2,Array(bids_price,bids_volume,bids_broker_id),null,(v:Double) => { agg4=v; acc.d })
    acc(()=>{ add(map0,bids_broker_id,((agg3 * bids_volume) + (agg4 * -1L))); })

    pre(map1,false,Array(),()=> {
    add(map1,(bids_broker_id,bids_price),(-1L * bids_volume));
    pre(map2,false,Array(),()=> {
    add(map2,(bids_broker_id,bids_price),-1L);
    deq
    }) }) })
  }

  def onAddASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre(map0,false,Array[MapRef](map1,map2),()=> {

    val acc = Acc(); acc.i; acc.i
    var agg5:Double = 0.0
    var agg6:Long = 0L
    aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(v:Double) => { agg5=v; acc.d })
    aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(v:Long) => { agg6=v; acc.d })
    acc(()=>{ add(map0,asks_broker_id,((agg5 * -1L) + (agg6 * asks_volume))); })

    pre(map3,false,Array(),()=> {
    add(map3,(asks_broker_id,asks_price),1L);
    pre(map4,false,Array(),()=> {
    add(map4,(asks_broker_id,asks_price),asks_volume);
    deq
    }) }) })
  }

  def onDelASKS(asks_t:Double, asks_id:Long, asks_broker_id:Long, asks_volume:Double, asks_price:Double) {
    pre(map0,false,Array[MapRef](map1,map2),()=> {

    val acc = Acc(); acc.i; acc.i
    var agg5:Double = 0.0
    var agg6:Long = 0L
    aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(v:Double) => { agg5=v; acc.d })
    aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(v:Long) => { agg6=v; acc.d })
    acc(()=>{ add(map0,asks_broker_id,(agg5 +  -1L * (agg6 * asks_volume))); })


/*
    aggr(map1,fa5,Array[Any](asks_broker_id,asks_price),null,(agg7:Double) => {
    aggr(map2,fa6,Array[Any](asks_broker_id,asks_price),null,(agg8:Long) => {
    add(map0,asks_broker_id,(agg7 + (agg8 * (-1L * asks_volume))));
    }) })
*/
    pre(map3,false,Array[MapRef](),()=> {
    add(map3,(asks_broker_id,asks_price),-1L);
    pre(map4,false,Array[MapRef](),()=> {
    add(map4,(asks_broker_id,asks_price),(-1L * asks_volume));
    deq
    }) }) })
  }
  */

  def onSystemReady() {
    ready
  }
}


















/*
class AXWorker extends WorkerActor {
  import WorkerActor._
  import Messages._
  import Functions._
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
  val AXFINDER = M3Map.make[Long,Double]();
  val mASKS1 = M3Map.makeIdx[(Long,Double),Double](0)
  val mASKS2 = M3Map.makeIdx[(Long,Double),Long](0)
  val mBIDS1 = M3Map.makeIdx[(Long,Double),Long](0)
  val mBIDS3 = M3Map.makeIdx[(Long,Double),Double](0)
  val local = Array[M3Map[_,_]](AXFINDER,mASKS1,mASKS2,mBIDS1,mBIDS3)

  // aggregations
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = { co() }
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = {
    val a0 = args(0).asInstanceOf[Long] // broker_id
    val a1 = args(1).asInstanceOf[Double] // price
    f match {
      case `f0` => co{var a:Long=0; mBIDS1.slice(0,a0).foreach{ (k,v) => val a_price=k._2; val bids_price=a1 // Add/del BIDS
        val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); a += v * (if (lift1 > 0L) 1L else 0L) }; a}
      case `f1` => co{var a:Double=0; mBIDS3.slice(0,a0).foreach{ (k,v) => val a_price=k._2; val bids_price=a1
        val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); a += v * (if (lift1 > 0L) 1L else 0L) }; a}
      case `f2` => co{var a:Double=0; mASKS1.slice(0,a0).foreach{ (k,v) => val b_price=k._2; val asks_price=a1 // Add/del ASKS
        val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); a += v * (if (lift5 > 0L) 1L else 0L) }; a}
      case `f3` => co{var a:Long=0; mASKS2.slice(0,a0).foreach{ (k,v) => val b_price=k._2; val asks_price=a1
        val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); a += v * (if (lift5 > 0L) 1L else 0L) }; a}
    }
  }
}

class AXMaster extends AXWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import scala.util.continuations._

  val queries = List(0)

  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleInsert,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddASKS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"ASKS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelASKS(v0,v1,v2,v3,v4)
  }
  def onAddBIDS(bids_t:Double, bids_id:Long, br_id:Long, vol:Double, price:Double) = / *reset* / {
    // New format: no CPS plug-in required
    pre(mAX,Array(mB1,mB3),(u:Unit)=>{
    aggr(mB1,f0,Array[Any](br_id,price),null,(agg1:Long)=>{
    aggr(mB3,f1,Array[Any](br_id,price),null,(agg2:Double)=>{
    add(mAX,br_id,((agg1 * (-1L * vol)) + agg2));
    }) })
    pre(mA1,Array[MapRef](),(u:Unit)=>{
    add(mA1,(br_id,price),vol)
    pre(mA2,Array[MapRef](),(u:Unit)=>{
    add(mA2,(br_id,price),1L)
    deq }) }) })
    / *
    _pre(mAX,mB1,mB3)
    val agg1 = _aggr[Long](mB1,f0,br_id,price);
    val agg2 = _aggr[Double](mB3,f1,br_id,price);
    add(mAX,br_id,((agg1 * (-1L * vol)) + agg2));
    _pre(mA1); add(mA1,(br_id,price),vol);
    _pre(mA2); add(mA2,(br_id,price),1L);
    deq
    * /
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
  def onSystemReady() { ready }
}
*/
