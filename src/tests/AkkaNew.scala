package tests

import scala.reflect.ClassTag
import scala.concurrent.{Future,Await}
//import scala.concurrent.ExecutionContext.Implicits.global
import akka.actor.{Actor,ActorRef,ActorSystem,Props,Deploy,Address}
import akka.remote.RemoteScope
import akka.pattern.ask

import ddbt.lib.{K3Map,K3Helper,Messages}

/*
 * Model: fully asynchronous message passing on workers. Synchronous statements
 * on master. Non-returning operations like add, set, foreach and clear do not
 * acknowledge but use a barrier instead. A barrier divides in 4 steps:
 * 1. Master send to all nodes a barrier message (n messages)
 * 2. All nodes broadcast the message to all peers (but themselves = n*(n-1) messages)
 * 3. When a node received n messages (incl master) it discards its cache and replies to the master
 * 4. When the master received n messages, it moves forward
 * A sparse barrier (only affected nodes participate) might not work as a node
 * involved might not receive 1 (involving) message before processing the barrier, thus
 * either not replying to the source (deadlock), or replying too early (coherency issue).
 */
object Msg {
  type MapRef = Byte
  type FunRef = Byte
  case class Init(master:ActorRef,workers:Array[ActorRef])
  case class Barrier(tx:Long)
  case class Collect(map:MapRef) // => Map[K,V] (blocking)
  case class Get[K](map:MapRef,key:K) // => Val
  case class Val[K,V](map:MapRef,key:K,value:V)
  case class Add[K,V](map:MapRef,key:K,value:V)
  case class Set[K,V](map:MapRef,key:K,value:V)
  case class Clear[P](map:MapRef,part:Int,partKey:P)
  case class Foreach(f:FunRef,args:List[Any]) /*f->map,part,partKey*/
  case class Aggr(id:Int,f:FunRef,args:List[Any]) /*f->map,part,partKey*/ // => Sum
  case class AggrPart[R](id:Int,res:R)
}
import Msg._

/**
 * A worker 'owns' a portion of all maps, determined by hash() function.
 * It responds to events from the master, and can interact with other workers.
 */
abstract class WorkerActor extends Actor {
  /** Matcher for lookup requests/continuations. Also provides caching/merging of requests. */
  object GetMatcher {
    private val cache = new java.util.HashMap[(MapRef,Any),Any]()
    private val cont = new java.util.HashMap[(MapRef,Any),List[Any=>Unit]]()
    def req[K,V](map:MapRef,key:K,co:V=>Unit) { // map.get(key,continuation)
      val o=owner(hash(map,key));
      if (o==null) co(local(map).get(key)) // resolves locally
      else {
        val k=(map,key); val v=cache.get(k);
        if (v!=null) co(v.asInstanceOf[V]) // cached
        else {
          val cs=cont.get(k); val c=co.asInstanceOf[Any=>Unit];
          cont.put(k,c::(if (cs!=null) cs else Nil))
          if (cs==null) o ! Get(map,key) // send request
        }
      }
    }
    def res[K,V](map:MapRef,key:K,value:V) { // onReceive Val(map,key,value)
      val k=(map,key); cache.put(k,value); cont.remove(k).foreach{ _(value) }
      ackBarrier() // Ack pending barrier if any
    }
    def pending = cont.size>0
    def clear = cache.clear
  }
  /** Matcher for aggregation requests/continuations. */
  object AggrMatcher {
    private val cache = new java.util.HashMap[(FunRef,List[Any]),Any]()
    private val cont = new java.util.HashMap[Int,List[Any=>Unit]]
    private val sum = new java.util.HashMap[Int,(Int/*count*/,Any/*sum*/,(Any,Any)=>Any/*plus*/)]
    private val params = new java.util.HashMap[Int,(FunRef,List[Any])]()
    private var ctr:Int = 0
    private def getId(f:FunRef,args:List[Any]):Int = { scala.collection.JavaConversions.mapAsScalaMap(params).foreach{ case (k,v) => if (v==(f,args)) return k; }; ctr=ctr+1; ctr }
    def req[R:ClassTag](f:FunRef,args:List[Any],co:R=>Unit) { // call("f(args)",continuation)
      val k=(f,args); val v=cache.get(k);
      if (v!=null) co(v.asInstanceOf[R]) // cached
      else {
        val k=getId(f,args); val cs=cont.get(k); val c=co.asInstanceOf[Any=>Unit];
        cont.put(k,c::(if (cs!=null) cs else Nil))
        if (cs==null) { // new request, create all structures and broadcast request
          params.put(k,(f,args))
          sum.put(k,(0,K3Helper.make_zero[R](),K3Helper.make_plus[R]().asInstanceOf[(Any,Any)=>Any]))
          workers.foreach{ w=> w!Aggr(k,f,args) } // send
        }
      }
    }
    def res[R](id:Int,res:R) { // onReceive AggrPart(id,res)
      val s = sum.get(id)
      val r = (s._1+1,s._3(s._2,res.asInstanceOf[Any]),s._3)
      if (r._1<workers.size) sum.put(id,r) // incomplete aggregation, wait...
      else {
        cache.put(params.get(id),r._2); cont.remove(id).foreach { _(r._2) }
        sum.remove(id); params.remove(id) // cleanup other entries
        ackBarrier() // Ack pending barrier if any
      }
    }
    def pending = cont.size > 0
    def clear = cache.clear
  }

  // Cluster
  protected val timeout = akka.util.Timeout(1000) // operation timeout (ms)  
  private val barrier = new java.util.HashMap[ActorRef,Long]()
  private var owner : Int => ActorRef = (h:Int)=>null // returns null if local
  private var master : ActorRef = null
  protected var workers : Array[ActorRef] = null
  protected def init(m:ActorRef,ws:Array[ActorRef]) {
    println("Init "+self.path)
    master=m; workers=ws; val id=workers.indexOf(self); val n=workers.size
    owner = (x:Int) => { val k=((x%n)+n)%n; if (k==id) null else workers(k) } // we might want to use more hash bits
    if (master==self) workers.foreach { w => w!Init(master,workers) }
  }
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
    def foreach[K,V](f:FunRef,args:List[Any]=Nil) { workers.foreach { _ ! Foreach(f,args) } }
    def aggr[R:ClassTag](f:FunRef,args:List[Any],co:R=>Unit) = if (self!=master) AggrMatcher.req(f,args,co) else {
      val fs = workers.map{ w => w.ask(Aggr(-1,f,args))(timeout) };
      val rs = fs.map{ f=>Await.result(f,timeout.duration).asInstanceOf[AggrPart[R]].res; }
      var r = K3Helper.make_zero[R](); val p = K3Helper.make_plus[R](); rs.foreach { x=>r=p(r,x) }; co(r)
    }
    def slice(part:Int, partKey:Any) = new MapFunc(m,part,partKey)
  }
}

/*
 * Master is the main actor where the program runs, and does not own any map portion.
 * Coherency mechanism: keep track of 'invalid' maps, force-write (flush) when necessary
 * - A write invalidates the map
 * - A map needs to be valid to be read from
 * - When flushing, all writes are committed to the map
 */
class MasterActor(props:Array[Props]) extends WorkerActor {
  import Messages._
  init(self,props.map{p=>context.actorOf(p)})
  final def local[K,V](m:MapRef) = sys.error("Master owns no map")
  
  private var tx:Long=0
  def flush() { tx=tx+1;
    val fs = workers.map{w=>w.ask(Barrier(tx))(timeout)}
    fs.foreach { f => Await.result(f,timeout.duration) }
  }
  override def receive = masterReceive orElse super.receive
  private var t0:Long = 0
  private def masterReceive : PartialFunction[Any,Unit] = {
    case SystemInit => flush(); t0=System.nanoTime()
    case EndOfStream => flush(); val time=System.nanoTime()-t0; sender ! (time,toMap(0))
  }
  private def toMap[K,V](m:MapRef):Map[K,V] = {
    val fs = workers.map { w => w.ask(Collect(m))(timeout) }
    def merge[K,V](maps:Array[Map[K,V]]):Map[K,V] = {
      val r = new java.util.HashMap[K,V]()
      maps.foreach { m=>m.foreach { case (k,v)=> r.put(k,v) } }
      scala.collection.JavaConversions.mapAsScalaMap(r).toMap
    }  
    merge(fs.map{ r => Await.result(r,timeout.duration).asInstanceOf[Map[K,V]] })
  }

  private val invalid = scala.collection.mutable.Set[MapRef]()
  def pre(write:MapRef,read:List[MapRef]) {
    if (!read.filter{r=>invalid.contains(r)}.isEmpty) { flush(); invalid.clear; }
    invalid += write
  }
}

// -----------------------------------------------------------------------------

class MyWorker extends WorkerActor {
  val map:MapRef = 0
  val m1 = K3Map.make[Long,Double]()
  def local[K,V](m:MapRef) = m1.asInstanceOf[K3Map[K,V]]
  def myReceive : PartialFunction[Any,Unit] = {
    case Foreach(1,List(d:Double)) => m1.foreach{case (k,v) => map.get(k-1,(v:Double)=>map.add(k,d+v)) }
    case Aggr(id,1,Nil) => sender ! AggrPart(id,m1.aggr{case (k,v) => v})
  }
  override def receive = myReceive orElse super.receive
}
class MyMaster(props:Array[Props]) extends MasterActor(props) {
  val map:MapRef = 0
  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    case "Hello" =>
      println("OK ----------")
      flush()
      println("OK ----------")
      flush()
      println("OK ----------")
      for (i <- 0 until 10) map.add(i.toLong,1.0)
      map.foreach(1,List(3.0))
      map.get(0L,(d:Double)=>println("map(0)="+d))
      map.aggr(1,Nil,(d:Double)=>map.add(100L,d))
  }
}

object MyHelper {
  def sys(name:String,host:String,port:Int) = {
    val conf = "akka.loglevel=ERROR\nakka.log-dead-letters-during-shutdown=off\n"+ // disable verbose logging
               "akka {\nactor.provider=\"akka.remote.RemoteActorRefProvider\"\nremote.netty {\nhostname=\""+host+"\"\ntcp.port="+port+"\n}\n}\n"
    ActorSystem(name,com.typesafe.config.ConfigFactory.parseString(conf))
  }
  def props[A<:Actor](name:String,host:String,port:Int)(implicit cA:ClassTag[A]) = Props(cA.runtimeClass).withDeploy(Deploy(scope = RemoteScope(new Address("akka.tcp",name,host,port))))

  // -------- specific
  val N = 2
  val port = 2551

  import Messages._
  def main(args:Array[String]) {
    val system = sys("MasterSystem","127.0.0.1",port-1)
    val nodes = (0 until N).map { i => sys("NodeSystem"+i,"127.0.0.1",port+i) }
    val wprops = (0 until N).map { i=>props[MyWorker]("NodeSystem"+i,"127.0.0.1",port+i) }.toArray
    val master = system.actorOf(Props(classOf[MyMaster],wprops))
    master ! SystemInit

    master ! "Hello"

    val timeout = akka.util.Timeout(10000) // operation timeout (ms)  
    val (t,r) = Await.result(master.ask(EndOfStream)(timeout),timeout.duration).asInstanceOf[(Long,Map[Long,Double])]
    def tim(ns:Long) = { val ms = ns/1000000; "%d.%03ds".format(ms/1000,ms%1000) }
    println("Time : "+tim(t)+"\n"+K3Helper.toStr(r))
    nodes.foreach{ _.shutdown }; system.shutdown
  }
}
