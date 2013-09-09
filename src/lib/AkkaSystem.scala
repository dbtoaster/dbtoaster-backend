package ddbt.lib

import scala.reflect.ClassTag
import akka.actor.{Actor,ActorRef}

/**
 * Model: fully asynchronous nodes. To provide a sequential-like model, the
 * master must execute event handlers on a separate (blocking) thread.
 * Distributed operations:
 * - Request/response (RR): the execution is paused into a continuation
 *   (in *Matcher classes) that will be resumed when the response is received.
 * - Remote calls (RC): context+closure identifier is sent, remote nodes
 *   execute the closure asynchronously.
 *
 * Synchronization:
 * - RR: if there is no pending request in the matcher, obviously all operations
 *   have been completed.
 * - RC: an acknowledgement must be produced at the end of the procedure. These
 *   are aggregated in a barrier (only when synchronization is needed).
 *
 * Barrier:
 * Nodes maintain two counters: CR:=#RC received, CS[n]=#RC sent to node n.
 * 1. Master broadcasts <start> to enable barrier mode on all nodes.
 *    At this point, the master is not allowed to send additional RC.
 * 2. In barrier mode, after every RC fully processed:
 *    if (there is no pending request in the matcher) {
 *      if (CR!=0 || CS!={0..0}) {
 *        send ack(CR,CS) to the master
 *        set CR=0, CS={0..0}
 *      }
 *    }
 * 3. When master receives ack(CR,CS), it sums with local counters.
 * 4. When (CR!=0 && CS!={0..0}) on master (there is no in-flight message), the
 *    master broadcast <stop> to disable barrier mode and continues processing.
 * Note: <start> counts as one RC to enforce barrier.
 *
 * @author TCK
 */

/** Internal types and messages */
object WorkerActor {
  type MapRef = Byte
  type FunRef = Byte
  type NodeRef = Short
  // Internal messages
  case class Members(master:ActorRef,workers:Array[(ActorRef,List[MapRef])]) // master can also be a worker for some maps
  case class Barrier(en:Boolean) // switch barrier mode
  case class Ack(to:Array[NodeRef],num:Array[Long]) // cumulative ack to master (to, count) : -1 for sent, 1 for recv
  // Data messages
  case class Get[K](map:MapRef,key:K) // => Val[K,V]
  case class Val[K,V](map:MapRef,key:K,value:V)
  case class Add[K,V](map:MapRef,key:K,value:V)
  case class Set[K,V](map:MapRef,key:K,value:V)
  case class Clear[P](map:MapRef,part:Int,partKey:P)
  case class Foreach(f:FunRef,args:Array[Any])
  case class Aggr(id:Int,f:FunRef,args:Array[Any]) // => Sum
  case class AggrPart[R](id:Int,res:R)
}

/** Worker, owns portions of all maps determined by hash() function. */
abstract class WorkerActor extends Actor {
  import scala.collection.JavaConversions.mapAsScalaMap
  import WorkerActor._
  // ---- concrete maps
  val local:Array[K3Map[_,_]] // local maps
  def hash(m:MapRef,k:Any) = k.hashCode

  // ---- membership management
  private var master : ActorRef = null
  private var workers : Array[ActorRef] = null
  private val owns = new java.util.HashMap[MapRef,Array[ActorRef]]()
  @inline private def owner(m:MapRef,k:Any):ActorRef = { val o=owns.get(m); val n=o.length; val h=hash(m,k); o((h%n+n)%n) }
  @inline private def members(m:ActorRef,ws:Array[(ActorRef,List[MapRef])]) {
    master=m; workers=ws.map(_._1); owns.clear;
    ws.flatMap(_._2).toSet.foreach { m:MapRef => owns.put(m,ws.filter(w=>w._2.contains(m)).map(_._1).toArray) }
    if (master==self) workers.foreach { w => w!Members(m,ws) }
  }
  // XXX: protected def addWorker(w:ActorRef,ms:List[Maps]) {}
  // XXX: protected def delWorker(w:ActorRef) {}
  
  // ---- get/continuations matcher
  private object matcherGet {
    private val cache = new java.util.HashMap[(MapRef,Any),Any]()
    private val cont = new java.util.HashMap[(MapRef,Any),List[Any=>Unit]]()
    @inline def req[K,V](map:MapRef,key:K,co:V=>Unit) { // map.get(key,continuation)
      val o=owner(map,key);
      if (o==self) co(local(map).asInstanceOf[K3Map[K,V]].get(key)) // resolves locally
      else {
        val k=(map,key); val v=cache.get(k);
        if (v!=null) co(v.asInstanceOf[V]) // cached
        else {
          val cs=cont.get(k); val c=co.asInstanceOf[Any=>Unit];
          cont.put(k,c::(if (cs!=null) cs else Nil))
          if (cs==null) o ! Get(map,key); lookupWait // send request
        }
      }
    }
    @inline def res[K,V](map:MapRef,key:K,value:V) { // onReceive Val(map,key,value)
      val k=(map,key); cache.put(k,value); cont.remove(k).foreach{ _(value) }
      bar.ack; lookupDone // ack pending barrier if needed
    }
    @inline def ready = cont.size==0
    @inline def clear = cache.clear
  }
  
  // ---- aggregation/continuations matcher
  protected object matcherAggr {
    private val cache = new java.util.HashMap[(FunRef,Array[Any]),Any]()
    private val cont = new java.util.HashMap[Int,List[Any=>Unit]]
    private val sum = new java.util.HashMap[Int,(Int/*count_down*/,Any/*sum*/,(Any,Any)=>Any/*plus*/)]
    private val params = new java.util.HashMap[Int,(FunRef,Array[Any])]()
    private var ctr:Int = 0
    @inline private def getId(f:FunRef,args:Array[Any]):Int = { params.foreach{ case (k,v) => if (v==(f,args)) return k; }; ctr=ctr+1; ctr }
    @inline def req[R](m:MapRef,f:FunRef,args:Array[Any],co:R=>Unit,zero:Any,plus:(Any,Any)=>Any) { // call aggregation ("f(args)",continuation) on map m (m used only to restrict broadcasting)
      val k=(f,args); val v=cache.get(k);
      if (v!=null) co(v.asInstanceOf[R]) // cached
      else {
        val k=getId(f,args); val cs=cont.get(k); val c=co.asInstanceOf[Any=>Unit];
        cont.put(k,c::(if (cs!=null) cs else Nil))
        if (cs==null) { // new request, create all structures and broadcast request to workers owning map m
          params.put(k,(f,args))
          val os = owns.get(m)
          sum.put(k,(os.length,zero,plus))
          os.foreach{ w=> w!Aggr(k,f,args) }; lookupWait // send
        }
      }
    }
    @inline def res[R](id:Int,res:R) { // onReceive AggrPart(id,res)
      val s = sum.get(id)
      val r = (s._1-1,s._3(s._2,res.asInstanceOf[Any]),s._3)
      if (r._1>0) sum.put(id,r) // incomplete aggregation, wait...
      else {
        cache.put(params.get(id),r._2); cont.remove(id).foreach { _(r._2) }
        sum.remove(id); params.remove(id) // cleanup other entries
        bar.ack; lookupDone // ack pending barrier if needed
      }
    }
    @inline def ready = cont.size==0
    @inline def clear = cache.clear
  }

  // ---- barrier and counters management
  private object bar {
    private var enabled = false
    private val count = new java.util.HashMap[ActorRef,Long]() // destination, count (-1 for sent, 1 for recv)
    @inline private def add(a:ActorRef,v:Long) { if (count.containsKey(a)) { val n=count.get(a)+v; if (n==0) count.remove(a) else count.put(a,n) } else if (v!=0) count.put(a,v) }
    @inline def ack = if (enabled && matcherGet.ready && matcherAggr.ready && count.size>0) {
      var ds : List[NodeRef] = Nil
      var cs : List[Long] = Nil
      count.foreach { case (a,n) => ds=workers.indexOf(a).toShort::ds; cs=n::cs }
      master ! Ack(ds.toArray,cs.toArray); count.clear
    }
    @inline def sumAck(to:Array[NodeRef],num:Array[Long]) {
      (to.map(workers(_)) zip num).foreach { case (w,n) => add(w,n) }
      if (enabled && count.size==0) {
        enabled=false; workers.foreach { w => if (w!=master) w ! Barrier(false) }
        barrierEnd // continue with sequential event processing (master)
      }
    }
    def set(en:Boolean) {
      if (enabled==en) return; enabled=en;
      if (self!=master) ack
      else workers.foreach { w => if (w!=master) { if (en) add(w,-1); w ! Barrier(en) } } // count barrier msg
    }
    // local counters usage
    @inline def recv = { add(self,1); ack }
    @inline def send(to:ActorRef,msg:Any) { add(to,-1); to ! msg }
  }

  // ---- message passing
  protected val fun_collect : FunRef = 255.toByte
  def receive = {
    case Members(m,ws) => members(m,ws)
    case Barrier(en) => bar.set(en) // assert(self!=master)
    case Ack(to,num) => bar.sumAck(to,num) // assert(self==master)
    //case Collect(m) => sender ! local(m).toMap
    case Get(m,k) => sender ! Val(m,k,local(m).asInstanceOf[K3Map[Any,Any]].get(k))
    case Val(m,k,v) => matcherGet.res(m,k,v)
    case Add(m,k,v) => local(m).asInstanceOf[K3Map[Any,Any]].add(k,v); bar.recv
    case Set(m,k,v) => local(m).asInstanceOf[K3Map[Any,Any]].set(k,v); bar.recv
    case Clear(m,p,pk) => (if (p<0) local(m) else local(m).slice(p,pk)).clear; bar.recv
    case Aggr(id,fun_collect,Array(m:MapRef)) => sender ! local(m).toMap
    //case Foreach(f,as) => call(f,as); bar.recv
    //case Aggr(id,f,as) => sender ! AggrPart(id,<result>)
    case AggrPart(id,res) => matcherAggr.res(id,res)
    case m => println("No handler for: "+m)
  }

  // ---- inheritable functions
  protected def barrierStart { /*assert(self==master);*/ bar.set(true) }
  protected def barrierEnd {} // master callback
  protected def lookupWait {} // at get/aggr request
  protected def lookupDone {} // at get/aggr response
  // Element operation: if key hashes to local, apply locally, otherwise call appropriate worker
  def get[K,V](m:MapRef,k:K,co:V=>Unit) = matcherGet.req(m,k,co) 
  def add[K,V](m:MapRef,k:K,v:V) { val o=owner(m,k); if (o==self) local(m).asInstanceOf[K3Map[K,V]].add(k,v) else bar.send(o,Add(m,k,v)) }
  def set[K,V](m:MapRef,k:K,v:V) { val o=owner(m,k); if (o==self) local(m).asInstanceOf[K3Map[K,V]].set(k,v) else bar.send(o,Set(m,k,v)) }
  // Group operations: master (or nested operation) broadcasts request, worker process locally
  def clear[P](m:MapRef,p:Int= -1,pk:P=null) = owns(m).foreach { bar.send(_,Clear(m,p,pk)) }
  def foreach(m:MapRef,f:FunRef,args:Array[Any]) { owns(m).foreach { bar.send(_,Foreach(f,args)) } }
  def aggr[R:ClassTag](m:MapRef,f:FunRef,args:Array[Any],co:R=>Unit) = matcherAggr.req(m,f,args,co,K3Helper.make_zero[R](),K3Helper.make_plus[R]().asInstanceOf[(Any,Any)=>Any])

  // ---- convenience debugging helpers (should be rewritten by compiler instead)
  import scala.language.implicitConversions
  implicit def mapRefConv(m:MapRef) = new MapFunc[Any](m)
  class MapFunc[P](m:MapRef,p:Int= -1,pk:P=null) { private val w=WorkerActor.this
    def get[K,V](k:K,co:V=>Unit) = w.get(m,k,co)
    def add[K,V](k:K,v:V) = w.add(m,k,v)
    def set[K,V](k:K,v:V) = w.set(m,k,v)
    def clear() = w.clear(m,p,pk)
    def slice(part:Int, partKey:Any) = new MapFunc(m,part,partKey)
    def foreach[K,V](f:FunRef,args:Array[Any]) = w.foreach(m,f,args)
    def aggr[R:ClassTag](f:FunRef,args:Array[Any],co:R=>Unit) = w.aggr(m,f,args,co)
  }
}

/**
 * Master is the main actor and streams entry point. It keeps track of 'invalid'
 * maps, and enforce flushing in-flight messages with a barrier when necessary.
 * Additionally, it simulates sequential processing of external events and blocks
 * on get, aggregation and flush.
 */
abstract class MasterActor extends WorkerActor {
  import scala.collection.JavaConversions.mapAsScalaMap
  import WorkerActor._
  import Messages._
  private var t0:Long = 0 // startup time


  // declare all event handlers with reset wrapped around


  // XXX: use continuations plugin for Scala
  // XXX: use continuations plugin for Scala
  // XXX: use continuations plugin for Scala


  // XXX: rewrite as fully asynchronous !!!
  // XXX: rewrite as fully asynchronous !!!
  // XXX: rewrite as fully asynchronous !!!
  // XXX: rewrite as fully asynchronous !!!

  // XXX: use continuations plugin for Scala

  // ---- event handlers
  def receive(e:StreamEvent,sender:ActorRef):Unit // to be implemented
  
  // ---- thread blocking mechanism
  private object thr {
    private val evq = new java.util.LinkedList[(StreamEvent,ActorRef)]() // external event queue
    private var reason = 0 // event being waited by master thread
    val r_extevt  = 1 // external event
    val r_barrier = 2 // pending barrier
    val r_getagg  = 3 // pending get or aggregation
    def block(r:Int) = this.synchronized { if (r!=reason) { reason=r; this.wait } } // force to block that thread
    def unblock(r:Int) = this.synchronized { if (r==reason) { reason=0; this.notifyAll } }
    def add(e:StreamEvent) = {
      val a = e match { case EndOfStream|GetSnapshot => sender case _ => null }
      this.synchronized { evq.add((e,a)) }
    }
    private var th:Thread = new Thread { override def run() =
      try { while(true) { val (e,a)=this.synchronized { if (evq.size==0) block(r_extevt); evq.remove; };
        e match {
          case SystemInit => barrierStart; t0=System.nanoTime() // XXX: we're not calling from 
          case EndOfStream|GetSnapshot => barrierStart; val time=System.nanoTime()-t0; sender ! /*(*/ time /*,toMap(0))*/
          case e:TupleEvent => receive(e,a) 
        }
      }}
      catch { case e:InterruptedException => }
    }
    th.start
    def stop() = th.interrupt
  }
  override def barrierStart { super.barrierStart; thr.block(thr.r_barrier) }
  override def barrierEnd { thr.unblock(thr.r_barrier) }
  override def lookupWait { thr.block(thr.r_getagg); }
  override def lookupDone { thr.unblock(thr.r_getagg); }

  // ---- synchronous collection of map data
  private var tmpMap:Map[_,_] = null
  def toMap[K,V](m:MapRef):Map[K,V] = {
    def cont(m:java.util.HashMap[K,V]) { tmpMap=m.toMap; thr.unblock(thr.r_getagg); }
    val zero = new java.util.HashMap[K,V]()
    def plus[K,V](acc:java.util.HashMap[K,V], m:Map[K,V]) = { m.foreach { case (k,v)=> acc.put(k,v) }; acc }
    matcherAggr.req(m,fun_collect,Array(m),cont,zero,(plus _).asInstanceOf[(Any,Any)=>Any])
    thr.block(thr.r_getagg); /*wait*/ val r=tmpMap.asInstanceOf[Map[K,V]]; tmpMap=null; r
  }

  // ---- coherency mechanism: if a map used is not flushed, flush all
  private val invalid = scala.collection.mutable.Set[MapRef]()
  def pre(write:MapRef,used:List[MapRef]=Nil) {
    if (!used.filter{r=>invalid.contains(r)}.isEmpty) { barrierStart; invalid.clear; }
    invalid += write
  }

  // ---- legacy behavior
  // At present, we do not support group management, this is done at setup
  // as with previous implementation, worker should support membership.
  // members(self,props.map{p=>context.actorOf(p)})
}


trait MyMaps {
  val map0 = K3Map.make[Long,Long]()
  val map1 = K3Map.make[Double,Double]()
  val local = Array[K3Map[_,_]](map0,map1)
}

class Worker extends WorkerActor with MyMaps {
  import WorkerActor._
}

class Master extends MasterActor with MyMaps {
  import Messages._
  def receive(e:StreamEvent,sender:ActorRef) {
  
  }
}

object Akka3 {
  import akka.actor.ActorSystem
  def main(args:Array[String]) {
    println("OK")
    val system = ActorSystem("DDBT")
    /*
    val w = system.actorOf(TestWorker,"Query")
    w ! 
    Thread.sleep(1000);
    system.shutdown()
    */
  }
}

/*
// ======================================================================
//
// WARNING: CURRENT BARRIER IMPLEMENTATION IS FLAWED, REFER TO 
//          docs/draft/m4.tex FOR PROTOCOL CORRECTIONS.
//
// ======================================================================

import scala.concurrent.{Future,Await}
import akka.pattern.ask
import akka.actor.Props

abstract class WorkerActor extends Actor {
  // Cluster
  protected val timeout = akka.util.Timeout(1000) // operation timeout (ms)
  private val barrier = new java.util.HashMap[ActorRef,Long]()
  private var owner : Int => ActorRef = (h:Int)=>null // returns null if local
  private var master : ActorRef = null
  protected var workers : Array[ActorRef] = null
  // ------ Concrete workers should define the functions below
  def local[K,V](m:MapRef):K3Map[K,V] // local map partition
  def hash(m:MapRef,k:Any):Int = k.hashCode
  // ------

  // def msg(m:String) { val s=self.path.toString; val p=s.indexOf("/user/"); println(s.substring(p)+": "+m); }

  // Events handling
  private def ackBarrier() {
    if (barrier.size==0) return; // no barrier started
    if (GetMatcher.pending || AggrMatcher.pending) return; // value requests pending, abort
    val t=barrier.get(master);
    if (scala.collection.JavaConversions.mapAsScalaMap(barrier).filter{case(k,v) => v==t}.size==workers.size) { // everyone responded, respond back to master
      master ! Barrier(t); barrier.clear; GetMatcher.clear; AggrMatcher.clear
    }
  }

  def receive = {
    case Init(m,ws) => init(m,ws)
    case Barrier(tx) => barrier.put(sender,tx);
      if (!workers.contains(sender)) { workers.foreach{ w=> if (w!=self) w!Barrier(tx) }; master=sender } // hack: ask() creates a new Actor
      ackBarrier()
    case Collect(m) => sender ! local(m).toMap
    case Get(m,k) => sender ! Val(m,k,local(m).get(k))
    case Val(m,k,v) => GetMatcher.res(m,k,v)
    case Add(m,k,v) => local(m).add(k,v)
    case Set(m,k,v) => local(m).set(k,v)
    case Clear(m,p,pk) => (if (p<0) local(m) else local(m).slice(p,pk)).clear()
    //case Foreach(<f>,<args>) => needs to be implemented by subclasses
    //case Aggr(id,<f>,<args>) => sender ! AggrPart(id,<result>) needs to be implemented by subclasses
    case x => println("Did not understood "+x)
  }

  // Helpers
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
  implicit def mapRefConv(m:MapRef) = new MapFunc[Any](m)
  class MapFunc[P](m:MapRef,p:Int= -1,pk:P=null) {
    // Element operation: if key hashes to local, apply locally, otherwise call appropriate worker
    def get[K,V](k:K,co:V=>Unit) = if (self!=master) GetMatcher.req(m,k,co) else // master is blocking
        { val r = Await.result(owner(hash(m,k)).ask(Get(m,k))(timeout),timeout.duration).asInstanceOf[Val[K,V]]; co(r.value) }
    def add[K,V](k:K,v:V) { val o=owner(hash(m,k)); if (o==null) local(m).add(k,v) else o!Add(m,k,v) }
    def set[K,V](k:K,v:V) { val o=owner(hash(m,k)); if (o==null) local(m).set(k,v) else o!Set(m,k,v) }
    // Group operations: master (or nested operation) broadcasts request, worker process locally
    def clear() = workers.foreach { _ ! Clear(m,p,pk); }
    def slice(part:Int, partKey:Any) = new MapFunc(m,part,partKey)
  }

  def foreach[K,V](f:FunRef,args:List[Any]=Nil) { workers.foreach { _ ! Foreach(f,args) } }
  def aggr[R:ClassTag](f:FunRef,args:List[Any],co:R=>Unit) = if (self!=master) AggrMatcher.req(f,args,co) else {
    val fs = workers.map{ w => w.ask(Aggr(-1,f,args))(timeout) };
    val rs = fs.map{ f=>Await.result(f,timeout.duration).asInstanceOf[AggrPart[R]].res; }
    var r = K3Helper.make_zero[R](); val p = K3Helper.make_plus[R](); rs.foreach { x=>r=p(r,x) }; co(r)
  }
}

class MasterActor(props:Array[Props]) extends WorkerActor {
  import WorkerActor._
  import Messages._
  init(self,props.map{p=>context.actorOf(p)})
  final def local[K,V](m:MapRef) = sys.error("Master owns no map")
  override def receive = masterReceive orElse super.receive
  private var t0:Long = 0
  private def masterReceive : PartialFunction[Any,Unit] = {
    case SystemInit => flush(); t0=System.nanoTime()
    case EndOfStream => flush(); val time=System.nanoTime()-t0; sender ! (time,toMap(0))
  }
}

LEGACY ARCHITECTURE OVERVIEW (push-based flow)
---------------------------------------------------

                  Source (streams)
                     |
                     v
Supervisor <---> Serializer -----> Storage
    ^          (broadcasting) <--- (setup tables)
    |                |
    |                v
    |             /+-+-+\
    |            / | | | \
    +---------- W W W W W Workers (partitioned)
                 \ | | | /
                  \+-+-+/
                     |
                     v
                  Display (query result)


The SOURCE represents the input stream, conceptually external to the system. It
could be: reading a file or receiving binary data from the network.

The SERIALIZER is the entry point all messages to the system. Its only duty is
to serialize and broacast all messages it receive: from source and from other
nodes that need to communicate.

The STORAGE has two roles:
- storage (database) for static relations (used at initialization)
- traditional database (preferably: compactness, easy recovery) or (WAL) log
  storing the stream. Purpose: recover from nodes crash, if necessary. 

The work is distributed to WORKERS that are responsible for processing the tuple
applying the deltas it generates to their local storage and exchange messages
with peers, if the peer computation requires their internal state. More
specifically, each node compute foreach modified map whether they own the slice
in which modification should happen. If:
- Yes: compute the delta, possibly waiting data from other nodes
- No : find owner, send it all _aggregated_ data related to modification

Example: SELECT COUNT(*) FROM R,S where R.r=S.s ==> maps mCOUNT,mR(r),mS(s)
    Assume 2 workers W1,W2 partitionned using modulo 2 on id, and mCOUNT on W1.
    When tuple <serial,+R(3)> arrives, owner=W1: mR is updated on W1.
    To compute mCOUNT+=1[R(3)]*COUNT(mS),
    - W1 does 1[R(3)]*COUNT(mS%2==1) and wait data from W2
    - W2 detects that its map is used, compute 1[R(3)]*COUNT(mS%2==0) and sends
      it to W1
    - W1 receive data from W2, completes its computation and update mCOUNT
The key here is to notice that since W1,W2 receive +R(3), they can pre aggregate
locally before agregating between nodes.

The DISPLAY is the receiver of the query maps, these can be send by all workers
whenever requested (request message needs to go through serializer).

Finally the SUPERVISOR coordinates all the nodes by handling failures and
checkpointing. To do that, all system messages are passed to the serializer.
This guarantees a coherent snapshot of the system.

FAULT TOLERANCE
---------------------------------------------------
Gap property: the application can sustain a gap in the stream without affecting
too much the result. Gap can be measured in time, #tuples, relative size, ...

Checkpointing: broadcast message for all workers and storage
- Workers write their map to permanent local storage.
- Storage as relations: make a snapshot (lock tables, ...)
- Storage as stream: if checkpoiting succeeds, discard stream up to check point

Failures
- Serializer fails: system waits for recovery. If the source does not enqueue
  messages and not Gap, system is stale and need to be reset.
- Storage fails: recovery of system becomes impossible.
  When detected, if has Gap property and worth it checkpoint (else useless).
- Supervisor or display fails: does not affect computation
- Worker fails: if Gap property or system could sustain a burst
  1. Enqueue all message at serializer
  2.a If storage holds the stream
      - Restore worker from its stable storage (tx_old)
      - Replay the stream (tx_old->tx_current) with help of storage and coworkers
  2.b If storage holds the relations
      - Recompute all the maps from the relations (we do not need local storage here)
  3. Release queue at serializer (burst), continue processing

**/

/*
abstract sealed class Msg
// Data
case object MsgEndOfStream extends Msg
case class MsgTuple(op:TupleOp,tx:Long,data:List[Any]) extends Msg
//case class MsgEndOfTrx(tx:Long,s:Long) extends Msg // all tuples have been exchanged between two workers for the sth statement of transaction tx
//case class MsgBulk(op:TupleOp,tx:Long,s:Long,data:List[List[Any]]) extends Msg // bulk transfer between two workers
// System
case object MsgNodeUp extends Msg    // worker is initialized
case object MsgNodeReady extends Msg // worker has received all tables content
case object MsgNodeDone extends Msg  // worker has received end of stream from all its sources
case class MsgState(num:Long,mem:Long) extends Msg // worker status (#processed tuples, memory usage)
case class MsgRate(state:Long,view:Long) extends Msg // how often nodes send state (to supervisor) and result (to display)
// case class MsgCheckpoint extends Msg
*/
