package ddbt.lib

import scala.reflect.ClassTag
import akka.actor.{Actor,ActorRef,Address,PoisonPill}

/**
 * Model: fully asynchronous nodes. Serializable execution is provided by the
 * master waiting for in-flight messages to be acknowledged. Messages types:
 * 1. Request/response (get,aggr): response=ack. The continuation is stored
 *    locally and executed on reception.
 * 2. Remote calls: (add,set,foreach): when the remote procedure is completed
 *    ack(#messages ack'ed, workers->#messages to ack) is sent to the master.
 * 3. When master has a count of 0 (#messages-#ack) for all workers, there is
 *    a serialization point. The count might be negative but can be continued
 *    only when exactly 0.
 *
 * There is a 1-1 mapping from NodeRef to ActorRef. We convert as much ActorRef
 * as possible into NodeRef, the idea behind that is that we can free ourselves
 * from Akka (towards plain C) if there is need to do so.
 *
 * @author TCK
 */


/**
 *
 * LEGACY-LEGACY-LEGACY-LEGACY-LEGACY:
 *
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
 * Note 1: <start> counts as one RC to enforce barrier.
 * Note 2: during the barrier, the cache must be disable to avoid propagating
 *         stale informations after the barrier.
 *
 *
 * @author TCK
 */

/*
 * Current Issues:
 * - OnSystemReady needs not to go through network and ignore non-local updates
 * - Batching update and lookups (with timeout/explicit end-of-batch?)
 * - Use multiple timestamps and queue updates in front of maps?
 *   -> If so, use maps as timed key-value store?
 *   -> Expunge previous versions when timestamp completed
 * XXX: _INFER_ (encode) functional dependencies in the maps(?)
 */

/** Worker, owns portions of all maps determined by hash() function. */
abstract class WorkerActor extends Actor {
  import java.util.HashMap
  import scala.collection.JavaConversions.mapAsScalaMap
  import Messages._

  // ---- concrete maps and local operations
  val local:Array[M3Map[_,_]] // ref->local maps conversion
  def local_wr(m:MapRef,v:Any,add:Boolean) {} // write in local variable
  def local_rd(m:MapRef):Any = sys.error("local_rd unspecified") // generic read a local variable
  def hash(m:MapRef,k:Any) = k.hashCode
  def forl(f:FunRef,args:Array[Any],co:()=>Unit) // local foreach
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) // local aggregation
  def loadTables() {}

  // ---- membership management
  private var master : ActorRef = null
  private var workers : Array[ActorRef] = null
  @inline private def owner(m:MapRef,k:Any):ActorRef = { val n=workers.length; val h=hash(m,k); workers((h%n+n)%n) }
  @inline private def members(m:ActorRef,ws:Array[ActorRef]) { master=m; workers=ws; if (master==self) workers.foreach { w => w!Members(m,ws) } }

  // ---- get/continuations matcher
  private object matcherGet {
    private val cont = new HashMap[(MapRef,Any),List[Any=>Unit]]()
    @inline def req[K,V](map:MapRef,key:K,co:V=>Unit) { ??? }
    @inline def res[K,V](map:MapRef,key:K,value:V) { // onReceive Val(map,key,value)
      val k=(map,key); cont.remove(k).foreach(_(value)); if (self!=master) bar.ack // ack pending barrier if needed
    }
    @inline def ready = cont.size==0
  }

  // ---- aggregation/continuations matcher
  // XXX: distinguish the hosts from which the part come => idea: allow duplicated messages without compromising result integrity
  private object matcherAgg {
    private val cont = new HashMap[Int,List[Any=>Unit]]
    private val sum = new HashMap[Int,(Int/*count_down*/,Any/*sum*/,(Any,Any)=>Any/*plus*/)]
    private val params = new HashMap[Int,(FunRef,Array[Any])]()
    private val params_r = new HashMap[(FunRef,Array[Any]),Int]()
    private val uniq:Long = math.abs(self.path.toString.hashCode) // unique among the cluster and membership-independent
    private var ctr:Int = 0
    @inline private def getId(f:FunRef,args:Array[Any]):Int = { val r=params_r.get((f,args)); if (r!=0) r else { ctr+=1; (ctr*uniq).toInt } }
    @inline def req[R](m:MapRef,f:FunRef,args:Array[Any],co:R=>Unit,zero:Any,plus:(Any,Any)=>Any) { // call aggregation ("f(args)",continuation) on map m (m used only to restrict broadcasting)
      val k=getId(f,args); val cs=cont.get(k); val c=co.asInstanceOf[Any=>Unit];
      cont.put(k,c::(if (cs!=null) cs else Nil))
      if (cs==null) { // new request, create all structures and broadcast request to workers owning map m
        params.put(k,(f,args)); params_r.put((f,args),k)
        sum.put(k,(workers.length,zero,plus))
        workers.foreach(_ ! Agg(k,f,args)) // send
      }
    }
    @inline def res[R](id:Int,res:R) { // onReceive AggPart(id,res)
      val s = sum.get(id)
      val r = (s._1-1,s._3(s._2,res.asInstanceOf[Any]),s._3)
      if (r._1>0) sum.put(id,r) // incomplete aggregation, wait...
      else {
        cont.remove(id).foreach { _(r._2) }
        sum.remove(id); { params_r.remove(params.remove(id)) } // cleanup other entries
        if (self!=master) bar.ack // ack pending barrier if needed
      }
    }
    @inline def ready = cont.size==0
  }

  // ---- barrier and counters management
  // XXX: introduce batching (see Messages.java)
  protected object bar {
    private var bco: ()=>Unit = null
    private val count = new HashMap[ActorRef,Long]() // destination, count (-1 for sent, 1 for recv)
    @inline private def add(a:ActorRef,v:Long) { if (count.containsKey(a)) { val n=count.get(a)+v; if (n==0) count.remove(a) else count.put(a,n) } else if (v!=0) count.put(a,v) }
    @inline def ack = if (matcherGet.ready && matcherAgg.ready && count.size>0) {
      var ds : List[NodeRef] = Nil
      var cs : List[Int] = Nil
      count.foreach { case (a,n) => ds=NodeRef(workers.indexOf(a))::ds; cs=n.toInt::cs }
      master ! Ack(ds.toArray,cs.toArray);
      count.clear
    }
    @inline def sumAck(to:Array[NodeRef],num:Array[Long]) {
      (to.map(workers(_)) zip num).foreach { case (w,n) => add(w,n) }
      if (count.size==0) { if (bco!=null) { val co=bco; bco=null; co(); } }
    }
    def set(co:(()=>Unit)) {
      if (self!=master) ack
      else { if (count.size==0) { bco=null; co() } else bco=co; }
    }
    // local counters usage
    @inline def recv = { add(self,1); ack }
    @inline def send(to:ActorRef,msg:Any) { add(to,-1); to ! msg }
  }

  // ---- message passing
  protected val fun_collect = FunRef(0,true)
  protected var local_map:Array[M3Map[Any,Any]] = null
  def receive = {
    // Data messages
    case Get(m,k) => sender ! Val(m,k,local_map(m).get(k)) // get(var) is handled locally
    case Val(m,k,v) => matcherGet.res(m,k,v)
    case Add(m,k,v) => ??? 
    case Set(m,k,v) => ???
    case Clear(m,p,pk) => val mm=local(m); (if (p<0) mm else mm.slice(p,pk)).clear; bar.recv
    case Foreach(f,as) => forl(f,as,()=>bar.recv)
    case Agg(id,fun_collect,Array(m:MapRef)) => sender ! AggPart(id,local(m)) // collect map data
    case Agg(id,f,as) => val s=sender; aggl(f,as,(r:Any)=>s!AggPart(id,r))
    case AggPart(id,res) => matcherAgg.res(id,res)
    // Management messages
    case Members(m,ws) => members(m,ws); local_map=local.asInstanceOf[Array[M3Map[Any,Any]]] // fix initialization order issue XXX: lazy val ?
    case Ack(to,num) => bar.sumAck(to,num.map(_.toLong)) // assert(self==master)
    case Reset => if (self==master) workers.foreach{ _ ! Reset;  }
      local.zipWithIndex.foreach { case (l,i) => if (l!=null) l.clear() else local_wr(MapRef(i),null,false) }
      System.gc; loadTables(); System.gc;
      // XXX: barrier(?) => have a synchronous blocking call
    case Shutdown => workers.foreach{ _ ! PoisonPill }; self ! PoisonPill // assert(self==master)
    case m => println("Not understood: "+m.toString)
  }
  override def postStop() = context.system.shutdown

  // ---- map operations
  // Element operation: if key hashes to local, apply locally, otherwise call remote worker
  def get[K,V](m:MapRef,k:K)(co:V=>Unit) = matcherGet.req(m,k,co)
  def add[K,V](m:MapRef,k:K,v:V) {
    ???
  }
  def set[K,V](m:MapRef,k:K,v:V) {
    ???
  }
  // Group operations: broadcast to owners, workers then process locally
  def clear[P](m:MapRef,p:Int= -1,pk:P=null) = workers.foreach { bar.send(_,Clear(m,p,pk)) }
  def foreach(m:MapRef,f:FunRef,args:Any*) { workers.foreach { bar.send(_,Foreach(f,args.toArray)) } }
  def aggr[R](m:MapRef,f:FunRef,args:Any*)(zero:Any=null)(co:R=>Unit)(implicit cR:ClassTag[R]) {
    ???
  }

  // XXX: Experimental RPC call
  def rpc(m:MapRef,k:Any,op:FunRef,args:Any*) { val n=workers.length; val h=hash(m,k); bar.send(workers((h%n+n)%n),Foreach(op,args.toArray)) }

  // ---- helper for local aggregation (in a local variable, and that needs to be sequential)
  case class Acc() { // applies a continuation when the internal counter is zero
    private var ctr = 0
    private var co:()=>Unit = null
    def inc(n:Int) { ctr+=n; }
    def i { ctr+=1; } // increment
    def d { ctr-=1; if (ctr==0 && co!=null) { val c=co; co=null; c() } } // decrement
    def apply(f: =>Unit) { if (ctr==0) f else co=()=>f; } // define the continuation
  }

  // ---- debugging
  // def msg(m: =>Any) { println(_a(self)+": "+m.toString); }
  // def _a(a:ActorRef) = { val s=a.path.toString; val p0=s.indexOf("System"); val p1=s.indexOf("/user/"); (if(p0>=0 && p0+6<p1) s.substring(p0+6,p1) else "#")+s.substring(p1+5) }
}

/**
 * Master is an additional role for a worker: it acts as streams entry point. It
 * processes external events sequentially, keeps track of read and written maps and
 * enforce writing in-flight messages with a barrier when necessary. To provide a
 * blocking execution, we use a continuation that fetch next events when finished.
 * To write imperative-style in a CPS environment, use the continuations plug-in:
 * http://www.scala-lang.org/api/current/index.html#scala.util.continuations.package
 */
trait MasterActor extends WorkerActor {
  import scala.collection.JavaConversions.mapAsScalaMap
  import Messages._
  val queries:List[MapRef]

  def toMap[K,V](m:MapRef,co:Map[K,V]=>Unit)(implicit cV:ClassTag[V]) = ???

  // ---- coherency mechanism: RAW, WAR and WAW dependency tracking
  // To mitigate WAW dependencies, we differentiate commutative and non-commutative (sequential) writes
  // Map state is a bitfield: 0=clean, 1=read, 2=write_commutative, 4=write_sequential
  //   (m_wr&1)!=0           --> WAR
  //   (m_wr&4)!=0           --> WAW (previous non-commutative)
  //   (m_wr&2)!=0 && seq!=0 --> WAW (this non-commutative)
  //   (m_rd&6)!=            --> RAW
  private var pre_map:Array[Int]=null
  def pre(write:MapRef,commute:Boolean,read:MapRef*)(co: =>Unit) { pre(write,commute,read.toArray,()=>co) }
  def pre(write:MapRef,commute:Boolean,read:Array[MapRef],co:()=>Unit) {
    val seq=if (commute) 0 else 1; var i=0; val t=pre_map.size; val n=read.size;
    var flush = if (write== -1) false else (pre_map(write)&(5|(1<<seq)))!=0 // check dependencies
    if (!flush && n>0) { i=0; do { flush=(pre_map(read(i))&6)>0; i+=1; } while(i<n && !flush) }
    if (flush) { i=0; do { pre_map(i)=0; i+=1; } while(i<t) } // clear
    if (write != -1) pre_map(write) |= 1<<(1+seq); if (n>0) { i=0; do { pre_map(read(i)) |= 1; i+=1; } while(i<n); } // dependencies
    if (!flush) co() else bar.set(co) // now proceed
  }

  // Multiple statements
  // XXX: use this in codegen instead of pre?
  def pre2(write:MapRef*)(commute:Boolean*)(read:MapRef*)(co: =>Unit) { pre2(write.toArray,commute.toArray,read.toArray,()=>co) }
  def pre2(write:Array[MapRef],commute:Array[Boolean],read:Array[MapRef],co:()=>Unit) {
    var flush = false
    var i=0; val nw=write.length; val nr=read.length; val n=pre_map.length
    while(i<nw && !flush) { flush=(pre_map(write(i)) & (if (commute(i)) 5 else 7)) != 0; i+=1 }; i=0;
    while(i<nr && !flush) { flush=(pre_map(read(i))&6) != 0; i+=1; }; i=0;
    if (flush) { i=0; do { pre_map(i)=0; i+=1; } while(i<n) } // clear
    while(i<nw && !flush) { pre_map(write(i)) |= (if (commute(i)) 2 else 4); i+=1 }; i=0;
    while(i<nr && !flush) { pre_map(read(i)) |= 1; i+=1; }
    if (flush) bar.set(co) else co() // now proceed
  }

  def barrier(co:()=>Unit) = { var i=0; val t=pre_map.size; do { pre_map(i)=0; i+=1; } while(i<t); bar.set(co); }

  // ---- handle stream events
  private var t0=0L // startup time
  protected var t1=0L // finish time
  protected var tN=0L // counter
  protected var tS=0L // skipped
  protected var skip=false // skipping state (due to timeout)

  private val eq = new java.util.LinkedList[(StreamEvent,ActorRef)]() // external event queue
  /**
   * est: state
   */
  private var est = 0 // state: 0=no loop, 1=loop pending, 2=trampoline, 3=bounce
  protected def deq {
    if (est==2) est=3; // bounce
    else do {
      if (eq.isEmpty) est=0 // loop exits
      else {
        est=2 // expose trampoline
        val (ev,sender)=eq.removeFirst
        def collect(rqs:List[MapRef],acc:List[Any]=Nil):Unit = rqs match {
          case q::qs =>
            if (local(q)==null) collect(qs,local_rd(q)::acc)
            else toMap(q,(m:Map[_,_])=>collect(qs,m::acc))
          case Nil => sender ! (StreamStat(t1-t0,tN,tS),acc); deq
        }
        ev match {
          case e:TupleEvent => if (skip) { tS+=1; deq } else dispatch(e)
          case StreamInit(timeout) => pre_map=new Array[Int](local.size); t0=0L; t1=timeout; tN=0L; tS=0L; skip=false; onSystemReady()
          case EndOfStream => barrier{()=> t1=System.nanoTime(); collect(queries.reverse)}
          case GetSnapshot(qs:List[Int]) => barrier{()=> t1=System.nanoTime; collect(qs.map(MapRef(_)).reverse)}
        }
        if (est==2) est=1 // disable trampoline
      }
    } while(est==3) // trampoline
  }

  val dispatch:PartialFunction[TupleEvent,Unit] // to be implemented by subclasses
  override def receive = masterRecv orElse super.receive
  private val masterRecv : PartialFunction[Any,Unit] = {
    case ev:StreamEvent => val p=(est==0); est=1; eq.offer((ev,if (ev.isInstanceOf[TupleEvent]) null else sender)); if (p) deq;
  }

  def onSystemReady() // {}
  def ready() { bar.set(()=>{ t0=System.nanoTime(); if (t1>0) t1=t0+t1*1000000L; deq }) } // callback for onSystemReady
}
