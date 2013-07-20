package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorRefFactory,Props}

import scala.reflect.ClassTag
import scala.reflect.classTag

import scala.concurrent.Await
import akka.pattern.ask
import akka.util.Timeout
import scala.concurrent.duration._

// A K4Map is a wrapper for ActorRef to provide map-like features.
// 
// Issues:
//  - Performance: actor.ask creates a new actor to wait for the reply. Problem ?
//  - Deadlock   : ask blocks the thread, hence we cannot do m.foreach{ m.get() }
//
trait K4Map[K,V] {
  def get(key:K) : V
  def add(key:K, value:V) : Unit
  def set(key:K, value:V) : Unit
  def foreach(s:(Int,Any))(f:(K,V)=>Unit) : Unit    // map.slice(s._1,s._2).foreach { case (k,v) => f(k,v) }
  def aggr[T:ClassTag](s:(Int,Any))(f:(K,V)=>T) : T // val s=0; map.slice(s._1,s._2).foreach { case (k,v) => s+=f(k,v) }; s
  def collect(s:(Int,Any)) : Map[K,V]               // map.slice(s._1,s._2).toMap
  def clear(s:(Int,Any)) : Unit                     // map.slice(s._1,s._2).clear()
}
object K4Map {
  def make[K,V](ctx:ActorRefFactory,workers:Int,projs:List[K=>_]=Nil)(implicit cv:ClassTag[V]):K4Map.Wrapper[K,V] = {
    val m = ctx.actorOf(Props[K4Map.Master[K,V]])
    val ws = (0 until workers).map{x=>ctx.actorOf(Props[K4Map.Worker[K,V]])}.toArray
    m ! K4Init(ws,cv,projs); ws.foreach { w => w ! K4Init(ws,cv,projs) }; new Wrapper(m)
  }

  // ---------------------------------------------------------------------------
  // Implementation

  private val timeout = Timeout(5.seconds) // transfer (get+collect) operation timeout

  import scala.language.implicitConversions
  implicit def toActor[K,V](w:Wrapper[K,V]):ActorRef = w.a
  implicit def toWrapper[K,V:ClassTag](a:ActorRef):Wrapper[K,V] = new Wrapper[K,V](a)

  def sask[T](a:ActorRef,m:Any):T = Await.result(a.ask(m)(timeout), timeout.duration).asInstanceOf[T]

  class Wrapper[K,V:ClassTag](val a:ActorRef) extends K4Map[K,V] {
    val v0 = K3Helper.make_zero[V]()
    def get(key:K) = sask[V](a,K4Get(key))
    def set(key:K,value:V) = a ! K4Set(key,value)
    def add(key:K,value:V) = if (value!=v0) a ! K4Add(key,value)
    def foreach(s:(Int,Any)=null)(f:(K,V)=>Unit) = sask[Any](a,K4Foreach(s,f)) //a ! K4Foreach(s,f)
    def aggr[T:ClassTag](s:(Int,Any))(f:(K,V)=>T) = sask[T](a,K4Aggr(s,f,classTag[T]))
    def collect(s:(Int,Any)=null) = sask[Map[K,V]](a,K4Collect(s))
    def clear(s:(Int,Any)=null) = a ! K4Clear(s)
    
    // Aliases:
    def toMap = collect(null)
  }

  class Master[K,V] extends Actor {
    var zero:V = null.asInstanceOf[V]
    var workers:Array[ActorRef] = null
    var h: Any=>ActorRef = null
    def receive = {
      case K4Init(ws,cv,projs) =>
        implicit val tag = cv.asInstanceOf[ClassTag[V]]
        zero = K3Helper.make_zero[V]()
        workers=ws;
        val n=ws.size
        h=(k:Any)=>ws(((k.hashCode%n)+n)%n)
        //println("Master["+self.path+"] ready")
      case m:K4Add[K,V] => if (m.value!=zero) h(m.key) ! m
      case m:K4Set[K,V] => h(m.key) ! m
      case m:K4Get[K] => sender ! Await.result(h(m.key).ask(m)(timeout), timeout.duration)
      case m:K4Foreach[K,V] => //workers.foreach(w=>w ! m)
        val fs = workers.map{ w=>w.ask(m)(timeout) }
        fs.foreach{ f=> Await.result(f, timeout.duration) }
        sender ! K4Ack
      case m:K4Aggr[K,V,_] =>
        val fs = workers.map{ w=>w.ask(m)(timeout) }
        val rs = fs.map{ f=> Await.result(f,timeout.duration) }
        val p = K3Helper.make_plus()(m.ct).asInstanceOf[(Any,Any)=>Any]
        val z = K3Helper.make_zero()(m.ct).asInstanceOf[Any]
        sender ! rs.foldLeft(z)(p)
      case m:K4Collect =>
        val ms = workers.map{ w=> Await.result(w.ask(m)(timeout), timeout.duration).asInstanceOf[Map[K,V]] }
        sender ! ms.foldLeft(scala.collection.immutable.HashMap[K,V]())(_ ++ _)
      case m:K4Clear => workers.foreach(w=>w ! m)
      case m => println("Master did not understood "+m)
    }
  }

  class Worker[K,V] extends Actor {
    var zero:V = null.asInstanceOf[V]
    var map:K3Map[K,V] = null
    var workers:Array[ActorRef] = null
    def slice(s:(Int,Any)) = (if (s==null || s._1<0) map else map.slice(s._1,s._2))
    def receive = {
      case K4Init(ws,cv,projs) =>
        implicit val tag = cv.asInstanceOf[ClassTag[V]]
        zero = K3Helper.make_zero[V]()
        map = K3Map.make[K,V](projs.asInstanceOf[List[K=>_]])
        workers = ws
        //println("Worker["+self.path+"] ready")
      case m:K4Add[K,V] => map.add(m.key,m.value)
      case m:K4Set[K,V] => map.set(m.key,m.value)
      case m:K4Get[K] => sender ! map.get(m.key)
      case m:K4Foreach[K,V] => slice(m.slice).foreach(m.f); sender ! K4Ack
      case m:K4Aggr[K,V,_] =>
        val plus = K3Helper.make_plus()(m.ct)
        var agg = K3Helper.make_zero()(m.ct)
        slice(m.slice).foreach{ case(k,v)=> agg=plus(agg,m.f(k,v)) }
        sender ! agg
      case K4Collect(s) => sender ! slice(s).toMap
      case K4Clear(s) => slice(s).clear()
      case m => println("Worker did not understood "+m)
    }
  }
  // Messages passed
  case class K4Init[K,V](ws:Array[ActorRef],cv:ClassTag[V], projs:List[K=>_]=Nil) // Let worker know peers
  case class K4Add[K,V](key:K,value:V) // apply on the fly
  case class K4Set[K,V](key:K,value:V) // must receive exactly 1 message from _ALL_ workers before applying
  case class K4Get[K](key:K) // ask a single actor, raw result
  case class K4Aggr[K,V,T](slice:(Int,Any),f:(K,V)=>T,ct:ClassTag[T]) // XXX: pass the class tag within message
  case class K4Foreach[K,V](slice:(Int,Any),f:(K,V)=>Unit)
  case class K4Collect(slice:(Int,Any)) // ask all actors, raw result
  case class K4Clear(slice:(Int,Any))
  case object K4Ack // foreach is finished
}


/*** LEGACY ***
    implicit val timeout = Timeout(5 seconds)
    val future = m ? Get(3)
    val result = Await.result(future, timeout.duration).asInstanceOf[Int]
    println("Result = "+result)

- create a bunch of actors
- each actor has an identifier (implicit)
- each actor know each other
- pass master in order to create a barrier
- update messages are passed : either add (async) or set (collect+write)

***/
