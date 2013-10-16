package ddbt.test
import akka.actor.{ActorSystem,Actor,ActorRef,Props}
import akka.util.Timeout
import scala.util.{Success,Failure}
import scala.concurrent.duration._
import concurrent.ExecutionContext.Implicits.global

case class MQ(n:Int)
case class MR(n:Int)
class AR extends Actor { def receive = { case MQ(n) => sender ! MR(n) } }

// Vanilla Akka
class AQ1(r:ActorRef) extends Actor {
  import context.dispatcher
  implicit val timeout = Timeout(50.seconds)

  var q:ActorRef = null // query source
  var c = 0 // countdown
  var s = 0 // sum
  def recv(n:Int) { s+=n; c-=1; if (c==0) q ! MR(s) }

  def receive = {
    case MQ(n) => c=n; s=0; q=sender;
      var i=0;
      do {
        val f = akka.pattern.ask(r,MQ(n))
        f.onComplete { case Success(MR(x)) => recv(x) case _ => println("Failure") }
        i+=1
      } while (i<n)
  }
}

// NoFuture
class AQ2(r:ActorRef) extends Actor {
  var q:ActorRef = null // query source
  var c = 0 // countdown
  var s = 0 // sum
  def recv(n:Int) { s+=n; c-=1; if (c==0) q ! MR(s) }

  val m = new java.util.HashMap[Int,()=>Unit]()
  def receive = {
    case MR(n) => val f = m.get(n); f(); m.remove(n);
    case MQ(n) => c=n; s=0; q=sender; var i=0; do { m.put(i,()=>recv(n)); r ! MQ(i); i+=1 } while (i<n)
  }
/*
  def receive = {
    case MR(n) => recv(n)
    case MQ(n) => c=n; s=0; q=sender; var i=0; do { r ! MQ(n); i+=1 } while (i<n)
  }
*/
}

object Cont {
  val N = 10000000
  //val N = 10000
  val mem0={ System.gc(); mem() }
  implicit val timeout = Timeout(50.seconds)

  private def mem() = { val r = Runtime.getRuntime(); (r.totalMemory()-r.freeMemory()) / 1048576.0 }
  def time(ns:Long) = { val ms=ns/1000000; "%d.%03d".format(ms/1000,ms%1000) }

  def test[T](name:String,cl:Class[T]) {
    val system = ActorSystem("DDBT")
    val r = system.actorOf(Props[AR])
    val a = system.actorOf(Props(cl,r))
    val m = new Object()
    try {
      println(name+":")
      val t0=System.nanoTime()
      var t1:Long = 0
      val f = akka.pattern.ask(a,MQ(N))
      f.onComplete { case Success(MR(x)) => t1=System.nanoTime(); println("Result: "+x); m.synchronized { m.notifyAll() } case _ => }
      m.synchronized { m.wait() }; System.gc(); println("Memory: %.1fMb".format(mem()-mem0)+"\nTime  : "+time(t1-t0)+"\n")
    } catch { case t:Throwable => t.printStackTrace(); } finally { system.shutdown }
  }

  def main(args: Array[String]) {
    test("Continuation",classOf[AQ2])
    Thread.sleep(100); System.gc(); Thread.sleep(100)
    test("Continuation",classOf[AQ2])
    Thread.sleep(100); System.gc(); Thread.sleep(100)
    test("Futures",classOf[AQ1])
    Thread.sleep(100); System.gc(); Thread.sleep(100)
    test("Futures",classOf[AQ1])
  
    
    
/*
    val system = ActorSystem("DDBT")
    val r = system.actorOf(Props[AR])
    val aq1 = system.actorOf(Props(classOf[AQ1],r))
    val aq2 = system.actorOf(Props(classOf[AQ2],r))
    
    val m = new Object()
    
    try {
    ;{
      println("Continuations")
      val t0=System.nanoTime()
      var t1:Long = 0
      val f = akka.pattern.ask(aq2,MQ(N))
      f.onComplete { case Success(MR(x)) => t1=System.nanoTime(); println("Result: "+x); m.synchronized { m.notifyAll() } case _ => }
      m.synchronized { m.wait() }
      System.gc()
      println("Memory: %.1fMb".format(mem()-mem0))
      println("Time  : "+time(t1-t0))
    };
      Thread.sleep(100);
      System.gc()
    ;{
      println("Scala futures")
      val t0=System.nanoTime()
      var t1:Long = 0
      val f = akka.pattern.ask(aq1,MQ(N))
      f.onComplete { case Success(MR(x)) => t1=System.nanoTime(); println("Result: "+x); m.synchronized { m.notifyAll() } case _ => }
      m.synchronized { m.wait() }
      System.gc()
      println("Memory: %.1fMb".format(mem()-mem0))
      println("Time  : "+time(t1-t0))
    };
    } catch {
      case t:Throwable => t.printStackTrace();
    } finally { system.shutdown }
*/
  
    /*
    //val m = new java.util.ArrayList[Int=>Unit]();
    val cos=(0 until 1000000).map { x => (y:Int)=>println(x+"XXXXXXXXXXXXXXXXXXXX"+y) }.toList
    val prs=(0 until 1000000).map { x => promise[Unit]
    //println("Size = "+m.size())
    / *
    val m = new java.util.HashMap[String,String]();
    (0 until 1000000).foreach { x => m.put("aaaaaaaaaaaaaaaaaaaaaaaaaaaa"+x,x+"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") }
    * /
    println("Used memory: %.1fMb".format(mem()-mem0))
    println("Hello, world! " + args.toList)
    */
  }
}
