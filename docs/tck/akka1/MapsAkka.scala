package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorRefFactory,Props}

import scala.reflect.ClassTag
import scala.reflect.classTag

import scala.concurrent.Await
import akka.pattern.ask
import akka.util.Timeout
import scala.concurrent.duration._

// A KAMap is a wrapper for ActorRef to provide map-like features.
//
// Issues:
//  - Performance: actor.ask creates a new actor to wait for the reply. Problem ?
//  - Deadlock   : ask blocks the thread, hence we cannot do m.foreach{ m.get() }
// XXX: fix coherency issues
// XXX: use pipe to forward get results (?)
//
trait KAMap[K,V] {
  def get(key:K) : V
  def add(key:K, value:V) : Unit
  def set(key:K, value:V) : Unit
  def foreach(s:(Int,Any))(f:(K,V)=>Unit) : Unit    // map.slice(s._1,s._2).foreach { case (k,v) => f(k,v) }
  def aggr[T:ClassTag](s:(Int,Any))(f:(K,V)=>T) : T // val s=0; map.slice(s._1,s._2).foreach { case (k,v) => s+=f(k,v) }; s
  def collect(s:(Int,Any)) : Map[K,V]               // map.slice(s._1,s._2).toMap
  def clear(s:(Int,Any)) : Unit                     // map.slice(s._1,s._2).clear()
}
object KAMap {
  def make[K,V](ctx:ActorRefFactory,workers:Int,projs:List[K=>_]=Nil)(implicit cv:ClassTag[V]):KAMap.Wrapper[K,V] = {
    val m = ctx.actorOf(Props[KAMap.Master[K,V]])
    val ws = (0 until workers).map{x=>ctx.actorOf(Props[KAMap.Worker[K,V]])}.toArray
    m ! KAInit(ws,cv,projs); ws.foreach { w => w ! KAInit(ws,cv,projs) }; new Wrapper(m)
  }

  // ---------------------------------------------------------------------------
  // Implementation

  private val timeout = Timeout(5.seconds) // transfer (get+collect) operation timeout

  import scala.language.implicitConversions
  implicit def toActor[K,V](w:Wrapper[K,V]):ActorRef = w.a
  implicit def toWrapper[K,V:ClassTag](a:ActorRef):Wrapper[K,V] = new Wrapper[K,V](a)

  def sask[T](a:ActorRef,m:Any):T = Await.result(a.ask(m)(timeout), timeout.duration).asInstanceOf[T]

  class Wrapper[K,V:ClassTag](val a:ActorRef) extends KAMap[K,V] {
    val v0 = K3Helper.make_zero[V]()
    def get(key:K) = sask[V](a,KAGet(key))
    def set(key:K,value:V) = a ! KASet(key,value)
    def add(key:K,value:V) = if (value!=v0) a ! KAAdd(key,value)
    def foreach(s:(Int,Any)=null)(f:(K,V)=>Unit) = sask[Any](a,KAForeach(s,f)) //a ! KAForeach(s,f)
    def aggr[T:ClassTag](s:(Int,Any))(f:(K,V)=>T) = sask[T](a,KAAggr(s,f,classTag[T]))
    def collect(s:(Int,Any)=null) = sask[Map[K,V]](a,KACollect(s))
    def clear(s:(Int,Any)=null) = a ! KAClear(s)
    def toMap = collect(null) // convenience alias
  }

  class Master[K,V] extends Actor {
    var zero:V = null.asInstanceOf[V]
    var workers:Array[ActorRef] = null
    var h: Any=>ActorRef = null
    def receive = {
      case KAInit(ws,cv,projs) =>
        implicit val tag = cv.asInstanceOf[ClassTag[V]]
        zero = K3Helper.make_zero[V]()
        workers=ws;
        val n=ws.size
        h=(k:Any)=>ws(((k.hashCode%n)+n)%n)
        //println("Master["+self.path+"] ready")
      case m:KAAdd[K,V] => if (m.value!=zero) h(m.key) ! m
      case m:KASet[K,V] => h(m.key) ! m
      case m:KAGet[K] => sender ! Await.result(h(m.key).ask(m)(timeout), timeout.duration)
      case m:KAForeach[K,V] => //workers.foreach(w=>w ! m)
        val fs = workers.map{ w=>w.ask(m)(timeout) }
        fs.foreach{ f=> Await.result(f, timeout.duration) }
        sender ! KAAck
      case m:KAAggr[K,V,_] =>
        val fs = workers.map{ w=>w.ask(m)(timeout) }
        val rs = fs.map{ f=> Await.result(f,timeout.duration) }
        val p = K3Helper.make_plus()(m.ct).asInstanceOf[(Any,Any)=>Any]
        val z = K3Helper.make_zero()(m.ct).asInstanceOf[Any]
        sender ! rs.foldLeft(z)(p)
      case m:KACollect =>
        val ms = workers.map{ w=> Await.result(w.ask(m)(timeout), timeout.duration).asInstanceOf[Map[K,V]] }
        sender ! ms.foldLeft(scala.collection.immutable.HashMap[K,V]())(_ ++ _)
      case m:KAClear => workers.foreach(w=>w ! m)
      case m => println("Master did not understood "+m)
    }
  }

  class Worker[K,V] extends Actor {
    var zero:V = null.asInstanceOf[V]
    var map:K3Map[K,V] = null
    var workers:Array[ActorRef] = null
    def slice(s:(Int,Any)) = (if (s==null || s._1<0) map else map.slice(s._1,s._2))
    def receive = {
      case KAInit(ws,cv,projs) =>
        implicit val tag = cv.asInstanceOf[ClassTag[V]]
        zero = K3Helper.make_zero[V]()
        map = K3Map.make[K,V](projs.asInstanceOf[List[K=>_]])
        workers = ws
        //println("Worker["+self.path+"] ready")
      case m:KAAdd[K,V] => map.add(m.key,m.value)
      case m:KASet[K,V] => map.set(m.key,m.value)
      case m:KAGet[K] => sender ! map.get(m.key)
      case m:KAForeach[K,V] => slice(m.slice).foreach(m.f); sender ! KAAck
      case m:KAAggr[K,V,_] =>
        val plus = K3Helper.make_plus()(m.ct)
        var agg = K3Helper.make_zero()(m.ct)
        slice(m.slice).foreach{ case(k,v)=> agg=plus(agg,m.f(k,v)) }
        sender ! agg
      case KACollect(s) => sender ! slice(s).toMap
      case KAClear(s) => slice(s).clear()
      case m => println("Worker did not understood "+m)
    }
  }
  // Messages passed
  case class KAInit[K,V](ws:Array[ActorRef],cv:ClassTag[V], projs:List[K=>_]=Nil) // Let worker know peers
  case class KAAdd[K,V](key:K,value:V) // apply on the fly
  case class KASet[K,V](key:K,value:V) // must receive exactly 1 message from _ALL_ workers before applying
  case class KAGet[K](key:K) // ask a single actor, raw result
  case class KAAggr[K,V,T](slice:(Int,Any),f:(K,V)=>T,ct:ClassTag[T]) // XXX: pass the class tag within message
  case class KAForeach[K,V](slice:(Int,Any),f:(K,V)=>Unit)
  case class KACollect(slice:(Int,Any)) // ask all actors, raw result
  case class KAClear(slice:(Int,Any))
  case object KAAck // foreach is finished
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
