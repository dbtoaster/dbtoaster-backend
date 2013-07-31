package examples
import ddbt.lib._
//import scala.concurrent.Future
import scala.reflect.ClassTag
import scala.reflect.classTag
import scala.concurrent._
import ExecutionContext.Implicits.global

import akka.actor.{Actor,ActorRef}
import akka.pattern.{ask,pipe}

/*
For the moment, this is slower than regular Akka and does not produce
desired result !!!

Running examples.AXFinder(standard)
Reference     time: 0.652s
Gen2          time: 0.334s
Akka          time: 1.822s
Simple LMS    time: 0.037s
Simple Gen2   time: 0.025s
0 -> 2446668.0
1 -> -648039.0
2 -> -5363809.0
3 -> 864240.0
4 -> 8384852.0
5 -> 3288320.0
6 -> -2605617.0
7 -> 243551.0
8 -> 1565128.0
9 -> 995180.0

Akka2         time: 1.969s (by reducing # synchronization)

*/


object Msgs {
  type MapRef[K,V] = Byte // Map identifier
  case class Init(master:ActorRef,workers:Array[ActorRef])
  case class Get[K,V](map:MapRef[K,V],key:K) // => V
  case class Add[K,V](map:MapRef[K,V],key:K,value:V)
  case class Set[K,V](map:MapRef[K,V],key:K,value:V)
  case class Foreach[K,V,P](map:MapRef[K,V],part:Int,partKey:P,f:(K,V)=>Unit)
  case class Aggr[K,V,P,R](map:MapRef[K,V],part:Int,partKey:P,f:(K,V)=>R,cR:ClassTag[R]) // => R
  case class Clear[K,V,P](map:MapRef[K,V],part:Int,partKey:P)
  case class Collect[K,V](map:MapRef[K,V]) // => Map[K,V]
  case object Flush // => Any (usually Flush)
}

/**
 * Model: actors run asynchronously/in parallel all operations (using Futures).
 * Synchronization is guaranteed using the flush() operation that 1) forces all
 * Futures (get operation) to terminate, 2) forces all writes to map (add,set)
 * using acknowledgement (Flush) and relying on TCP and Actors sequentiality.
 */
abstract class WorkerActor extends Actor {
  import Msgs._

  private val timeout = akka.util.Timeout(5000) // transfer (get+collect) operation timeout (ms)  
  private var _master : ActorRef = null
  private var _workers : Array[ActorRef] = null
  private var _futures : List[Future[Unit]] = Nil // pending futures (waiting on get)
  private var _written = scala.collection.mutable.Set[ActorRef]() // written-to actors
  private var _id : Int = -1 // local identifier (hash result)
  private var hr = (h:Int) => h // reduce hash to [0, #workers-1]

  def local[K,V](m:MapRef[K,V]):K3Map[K,V] // return local K3Map
  def hash[K,V](m:MapRef[K,V],k:Any):Int = k.hashCode // hash(key) for given map (override allows colocation)
  def init(master:ActorRef,workers:Array[ActorRef]) {
    _master=master; _workers=workers; _id=workers.indexOf(self);
    val n=_workers.size; hr=(h:Int)=>((h%n)+n)%n // we might want to improve reduction to improve distribution
    //println("Initialized "+self.path+" : id = "+_id)
  }

  import scala.language.implicitConversions  
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  // Operation on MapRefs are implicitly converted in a distributed execution wrapper
  implicit def mapRefConv[K,V](m:MapRef[K,V]) = new MapFunc[K,V,Any](m)
  class MapFunc[K,V,P](m:MapRef[K,V],p:Int= -1,pk:P=null) {
    // Element operation: if key hashes to local, apply locally, otherwise call appropriate worker
    def get[K,V](k:K,c:(K,V)=>Unit) { val h=hr(hash(m,k)); if (h==_id) c(k,local(m).get(k))
      else _futures = _workers(h).ask(Get(m,k))(timeout).map{ v=> c(k,v.asInstanceOf[V]) } :: _futures
    }
    def add(k:Any,v:Any) { val h=hr(hash(m,k)); if (h==_id) local(m).add(k,v) else { val w=_workers(h); w!Add(m,k,v); _written+=w; } }
    def set(k:K,v:V) { val h=hr(hash(m,k)); if (h==_id) local(m).set(k,v) else { val w=_workers(h); w!Set(m,k,v); _written+=w; } }

    def aggr[R:ClassTag](f:(K,V)=>R,c:R=>Unit) { 
      _futures = Future.sequence(_workers.map { w => w.ask(Aggr[K,V,P,R](m,p,pk,f,classTag[R]))(timeout) }.toList).transform(
        s => { var a=K3Helper.make_zero[R](); val p=K3Helper.make_plus[R](); s.foreach{ x => a=p(a,x.asInstanceOf[R]) }; c(a) },
        f => f
      ) :: _futures
    }

    // Group operations: master (or nested operation) broadcasts request, worker process locally
    def foreach(f:(K,V)=>Unit) { _workers.foreach { w => w ! Foreach[K,V,P](m,p,pk,f) } }
    def clear() { _workers.foreach { w => w ! Clear[K,V,P](m,p,pk) } }
    def slice(part:Int, partKey:Any) = new MapFunc(m,part,partKey)
    
    def toMap():Map[K,V] = {
      if (self!=_master) sys.error("Collect must be run on master") // as we use blocking calls
      val fs = _workers.map { w => w.ask(Collect[K,V](m))(timeout) }
      
      def mergeMaps[K,V](maps:Array[Map[K,V]]):Map[K,V] = {
        val r = new java.util.HashMap[K,V]()
        maps.foreach { m=>m.foreach { case (k,v)=> r.put(k,v) } }
        scala.collection.JavaConversions.mapAsScalaMap(r).toMap
      }  
      mergeMaps(fs.map{ r => Await.result(r,timeout.duration).asInstanceOf[Map[K,V]] })
    }
  }

  // Block for current operation completion (master only)
  // http://doc.akka.io/docs/akka/snapshot/scala/futures.html
  // file:///Developer/Scala/docs/index.html#scala.concurrent.Future
  def flush() {
    if (self!=_master) sys.error("Flush can only be invoked on master") // as we use blocking calls
    val fs = _workers.map { w => w.ask(Flush)(timeout) }
    fs.foreach { f => Await.result(f,timeout.duration) }
  }
  
  // Whenever we receive a message, we know that the operation has already been
  // distributed: we do not need to broadcast it and can execute immediately on local.
  def receive = {
    case Init(m,ws) => init(m,ws)
    case Get(m,k) => sender ! local(m).get(k)
    case Add(m,k,v) => local(m).add(k,v)
    case Set(m,k,v) => local(m).set(k,v)
    case Foreach(m,p,pk,f) => (if (p<0) local(m) else local(m).slice(p,pk)).foreach { (k,v) => f(k,v) }
    case Aggr(m,p,pk,f,cr) => sender ! (if (p<0) local(m) else local(m).slice(p,pk)).aggr(f)(cr)
    case Clear(m,p,pk) => (if (p<0) local(m) else local(m).slice(p,pk)).clear()
    case Collect(m) => sender ! local(m).toMap
    case Flush => // finish reads, then request ack for all writes
      Future.sequence(_futures).transform(
        s => Future.sequence(_written.map{w=>w.ask(Flush)(timeout)}),
        f => f).transform(s=>Flush,f=>f) pipeTo sender
  }
}

import scala.reflect.ClassTag
import akka.actor.{Actor,Props}
class MasterActor[T<:Actor](val N:Int)(implicit val cT:ClassTag[T]) extends WorkerActor {
  import Messages._
  import Msgs._
  def local[K,V](m:MapRef[K,V]) = sys.error("Master has no map")
  var t0:Long = 0
  override def receive = super.receive orElse {
    case SystemInit =>
      val ws = (0 until N).map {i=>context.actorOf(Props[T])}.toArray
      init(self,ws); ws.foreach { w => w ! Init(self,ws) }; t0=System.nanoTime()
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,new MapFunc(0).toMap())
  }
  
  /*
   * Coherency: keep track of invalid maps, and force-write (flush) when necessary
   * - A write 'invalidates' the map, write op is queued
   * - A map needs to be valid to be read
   * - When flushing, all writes are committed to the map
   */
   /*
   val invalid = Set[MapRef[Any,Any]]()
   def registerOp(write:MapRef[Any,Any],read:List[MapRef[Any,Any]]) {
   }
   val 
   // add a queue
   // redefine add, set and flush operation to store in queue
   */  
  
}

// Testing ----------------------------------------

class WorkerAXFinder extends WorkerActor {
  import Msgs._
  private val idx = List((x:(Long,Double))=>x._1)
  val maps = List(
    K3Map.make[Long,Double](),
    K3Map.make[(Long,Double),Double](idx),
    K3Map.make[(Long,Double),Long](idx),
    K3Map.make[(Long,Double),Long](idx),
    K3Map.make[(Long,Double),Double](idx)
  )
  def local[K,V](m:MapRef[K,V]) = maps(m.toInt).asInstanceOf[K3Map[K,V]]
  //override def preStart(): Unit = println("Worker started")
  //override def postStop(): Unit = println("Worker stopped")
  //override def receive = super.receive orElse { case _ => }
}

import akka.actor.{Actor,ActorRef,ActorRefFactory,Props}

class AXFinderAkka2 extends MasterActor[WorkerAXFinder](16) {
  import Messages._
  import Msgs._

  override def receive = super.receive orElse {
    case TupleEvent(TupleInsert,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddBIDS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"BIDS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelBIDS(t,id,b,v,p)
    case TupleEvent(TupleInsert,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onAddASKS(t,id,b,v,p)
    case TupleEvent(TupleDelete,"ASKS",tx,List(t:Double,id:Long,b:Long,v:Double,p:Double)) => onDelASKS(t,id,b,v,p)
  }

  // Must exactly match maps in WorkerAXFinder
  val AXFINDER : MapRef[Long,Double] = 0
  val mASKS1 : MapRef[(Long,Double),Double] = 1
  val mASKS2 : MapRef[(Long,Double),Long] = 2
  val mBIDS1 : MapRef[(Long,Double),Long] = 3
  val mBIDS3 : MapRef[(Long,Double),Double] = 4
  
  def onAddBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    mBIDS1.slice(0,BIDS_BROKER_ID).aggr( (k2:(Long,Double),v3:Long)=>{
      val A_PRICE = k2._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v3 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)))
    },(agg1:Long)=>
    mBIDS3.slice(0,BIDS_BROKER_ID).aggr( (k5:(Long,Double),v6:Double)=>{
      val A_PRICE = k5._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v6 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    },(agg4:Double)=>
    AXFINDER.add(BIDS_BROKER_ID,((agg1 * -BIDS_VOLUME) + agg4))
    ))
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),1L);
    flush()
  }
  
  def onDelBIDS(BIDS_T:Double, BIDS_ID:Long, BIDS_BROKER_ID:Long, BIDS_VOLUME:Double, BIDS_PRICE:Double) {
    mBIDS1.slice(0,BIDS_BROKER_ID).aggr( (k8:(Long,Double),v9:Long) => {
      val A_PRICE = k8._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v9 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    },(agg7:Long)=>
    mBIDS3.slice(0,BIDS_BROKER_ID).aggr( (k11:(Long,Double),v12:Double) => {
      val A_PRICE = k11._2;
      val __sql_inline_or_1 = (((A_PRICE - BIDS_PRICE) > 1000L) + ((BIDS_PRICE - A_PRICE) > 1000L));
      (v12 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    },(agg10:Double)=>
    AXFINDER.add(BIDS_BROKER_ID,((agg7 * BIDS_VOLUME) + (agg10 * -1L)))
    ))
    mASKS1.add((BIDS_BROKER_ID,BIDS_PRICE),-BIDS_VOLUME);
    mASKS2.add((BIDS_BROKER_ID,BIDS_PRICE),-1L);
    flush()
  }
  
  def onAddASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    mASKS1.slice(0,ASKS_BROKER_ID).aggr( (k14:(Long,Double),v15:Double) => {
      val B_PRICE = k14._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v15 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    },(agg13:Double)=>

    mASKS2.slice(0,ASKS_BROKER_ID).aggr ( (k17:(Long,Double),v18:Long) => {
      val B_PRICE = k17._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      v18 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L))
    },(agg16:Long)=>
    AXFINDER.add(ASKS_BROKER_ID,((agg13 * -1L) + (agg16 * ASKS_VOLUME)))
    ))
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),ASKS_VOLUME);
    flush()
  }
  
  def onDelASKS(ASKS_T:Double, ASKS_ID:Long, ASKS_BROKER_ID:Long, ASKS_VOLUME:Double, ASKS_PRICE:Double) {
    mASKS1.slice(0,ASKS_BROKER_ID).aggr ((k20:(Long,Double),v21:Double) => {
      val B_PRICE = k20._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v21 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    },(agg19:Double)=>
    mASKS2.slice(0,ASKS_BROKER_ID).aggr ((k23:(Long,Double),v24:Long) => {
      val B_PRICE = k23._2;
      val __sql_inline_or_1 = (((ASKS_PRICE - B_PRICE) > 1000L) + ((B_PRICE - ASKS_PRICE) > 1000L));
      (v24 * (__sql_inline_or_1 * (__sql_inline_or_1 > 0L)));
    },(agg22:Long)=>
      AXFINDER.add(ASKS_BROKER_ID,(agg19 + (agg22 * -ASKS_VOLUME)))
    ))
    mBIDS1.add((ASKS_BROKER_ID,ASKS_PRICE),-1L);
    mBIDS3.add((ASKS_BROKER_ID,ASKS_PRICE),-ASKS_VOLUME);
    flush()
  }
}

object AXFinderAkka2 extends Helper {
  def main(args:Array[String]) {
    val (time,res) = run[AXFinderAkka2,Long,Double](streamsFinance( "standard" ),false);
    printMap(res); printTime(time)
  }
}

/*

IDEA: focus on simple abstraction
- implement NxN messages barrier (all to all EndOfTransaction msg)
   - refine using lamport clocks / tree of dependencies ?
- implement simple get and wait => non-blocking for all values lookup
- foreach and slice operations are executed on each workers

- 2 locks : read lock, write lock, each event locks and unlocks maps until termination

trait K3Map[K,V] {
  def get(key:K): V                // returns the value or zero if it is not present
  def set(key:K, value:V)          // inserts or set the value
  def add(key:K, value:V)          // combines new value with existing one using 'plus'
  def foreach(f:(K,V)=>Unit)       // iterates through all non-zero values of the map
  def slice[P](part:Int, partKey:P):K3Map[K,V] // returns the map partition where the key part is equal to subKey
  def clear()                      // erases all elements of the map or slice
  // additional features
  def size: Int                    // returns the number of key-value mappings in the map
  def toMap: Map[K,V]              // returns the map content
  def toXML: List[xml.Elem]        // returns the map content as XML
  def toStr: String                // returns the map content as (comparable) String
}


Differentiate
- primary operation on a map (read) => only do locally
- secondary lookup (do remotely if needed)
- update to map + ack at the end

1. individual updates => do lookup on master, execute on master
2. loop-based updates => distribute closure, execute on workers


==> operation work differently if they are on master or slaves

master:
- distribute closure on workers (either all or only one)
- wait for workers to ack (barrier or ask pattern)

slave:
- execute outer loop locally (foreach, ...) [or outer lookup only]
- execute inner operations (lookup, ... remotely ONLY if they are in a loop),



trait K3Map[K,V] {
  def get(key:K): V
    // M: direct lookup
    // W: collect all lookup from outer loop and execute at once
  def set(key:K, value:V)
  def add(key:K, value:V)
    // M: direct set and wait for ack
    // W: delay and apply in bulk at the end of the loop (and ack there)

  def foreach(f:(K,V)=>Unit)
  def clear()                      // erases all elements of the map or slice
    // M: distribute to ALL workers (possibly split into lookup and op phases
    // W: execute on local partition
  
  def toMap: Map[K,V]
    // M: execute on all workers and wait for result
    // W: returns local map content
}

==> find a non-blocking pattern for ask/reply + continuation function with a local
    map storing answers
*/


  /*
object Msg {
  type Op = Char
  val  OpAdd : Op = 0x01 // add to existing value
  val  OpSet : Op = 0x02 // set to new value
  type MapRef = (Short,Short,Any) // map id, slice number, slicing value
  
  // Write operations (sent to key owner)
  case class Write[K,V](op:Op,map:MapRef,key:K,value:V)
  case class Write[K,V](op:Op,map:MapRef,keys:Array[K],values:Array[V])
  case class Clear(map:MapRef)
  // Read operations (broadcasted to all/appropriate workers)
  case class Collect(map:MapRef) // => Map[K,V]
  case class Read[K](map:MapRef,keys:Array[K]) // => Map[K,V] where K in keys
  case class Aggr[P,V,R](map:MapRef,f:(K,V)->R) // => R as result
  // Synchronization between workers
  case class AckReq // W1->W2: request # of W1 ops processed on W2
  case class Ack(n:Int) // return # of ops processed
  // Jobs
  case class JobDone
  
  // Setup
  case class Init[K,V](master:ActorRef, workers:Array[ActorRef])
  
  // Messages between workers

  // Messages with master
  case class WorkerDone // BarrierRequest from worker (job finished)
  */
  // Messages passed
/*
  case class K4Init[K,V](ws:Array[ActorRef],cv:ClassTag[V], projs:List[K=>_]=Nil) // Let worker know peers

  case class K4Aggr[K,V,T](slice:(Int,Any),f:(K,V)=>T,ct:ClassTag[T]) // XXX: pass the class tag within message
  case class K4Foreach[K,V](slice:(Int,Any),f:(K,V)=>Unit)
  case class K4Collect(slice:(Int,Any)) // ask all actors, raw result
  case class K4Clear(slice:(Int,Any))
  case object K4Ack // foreach is finished  
}
*/
/* Continuation/caching ask pattern for Actor. */
// Idea: use a counter of pending messages, register the result in a HashMap, block for completion at the end
/* Implement a barrier with master/workers, consistent hashing among workers */
//trait SplitActor extends Actor {
 // super.receive orElse { case ... }
//}

  /* Q18:
  def maps = List(
    K3Map.make[(String,Long,Long,Date,Double), Double](),
    K3Map.make[(String,Long), Long](List((x:(String,Long))=>x._2)),
    K3Map.make[(Long,Long,Date,Double), Double](List((x:(Long,Long,Date,Double))=>x._2)),
    K3Map.make[(Long,Long,Date,Double), Long](List((x:(Long,Long,Date,Double))=>x._1,(x:(Long,Long,Date,Double))=>x._2)),
    K3Map.make[(Long,String,Long,Date,Double), Double](),
    K3Map.make[(Long,String,Long,Date,Double), Long](List((x:(Long,String,Long,Date,Double))=>x._1)),
    K3Map.make[Long,Double]()
  )
  def refs = {
    def ref[K,V](m:K3Map[K,V],i:Int):MapRef[K,V] = i.toByte.asInstanceOf[MapRef[K,V]]
    val ms = maps.zipWithIndex.map { case (m,i) => ref(m,i) }
    (ms(0),ms(1),ms(2),ms(3),ms(4),ms(5),ms(6))
  }
  val (mQ18,mORDERS,mCUSTOMER,mCUSTOMER_LINEITEM,mLINEITEM,mLINEITEM_LINEITEM,mLINEITEM_E1_L1) = Q18.refs
  */

