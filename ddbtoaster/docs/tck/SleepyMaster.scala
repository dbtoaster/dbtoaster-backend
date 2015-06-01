package test.tck

import scala.concurrent.{Future,Await}
import scala.concurrent.duration._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import akka.util.Timeout
import akka.pattern.ask

object SleepyMaster {
  def main(args:Array[String]) {
    val system = ActorSystem("DDBT")
    val a = system.actorOf(Props[A],"Actor")

    // Simulate internal events    
    var t:Thread = new Thread { override def run() =
      try { while(true) { a ! "Blop"; Thread.sleep(5) } }
      catch { case e:InterruptedException => }
    }
    t.start()

    // Send 10 external events
    for (i<-0 until 10) { a ! i }
    implicit val timeout = Timeout(5.seconds)
    val f = a ? -10
    val r = Await.result(f,timeout.duration)

    t.interrupt; println(r); system.shutdown
  }
}

class A extends Actor {
  type StreamEvent = Int
  val EndOfStream : StreamEvent = -10

  // ---- blocking mechanism and external events queue
  private val rEv = 1 // waiting for an event
  private var rIn = 2 // waiting for internal event
  private var reason : Int = 0 // 
  private def block(r:Int) = this.synchronized { reason=r; this.wait }
  private def unblock(r:Int) = this.synchronized { if (r==reason) { reason=0; this.notifyAll } }
  private val evq = new java.util.LinkedList[(StreamEvent,ActorRef)]()
  def eventAdd(e:StreamEvent,a:ActorRef=null) = this.synchronized { e match {
    case EndOfStream => evq.add((e,a)); unblock(rEv)
    case _ => evq.add((e,null)); unblock(rEv)
  }}
  var thr:Thread = new Thread { override def run() =
    try { while(true) { val (e,a)=this.synchronized { if (evq.size==0) block(rEv); evq.remove; }; events(e,a) }}
    catch { case e:InterruptedException => }
  }
  thr.start

  // internal events processing
  def receive = {
    case "Blop" => unblock(rIn)
    case id:Int => eventAdd(id,sender)
  }

  def dodo() { block(rIn) }
  
  // ------------ userland part

  def events(e:StreamEvent,sender:ActorRef) = e match {
    case EndOfStream => sender ! "End!"; Thread.currentThread.interrupt
    case id=>handler(id)
    // ...
  }

  def handler(id:Int) {
    print("Event "+id+"0")
    for (i<-1 until 10) { dodo; print(" "+id+i) }
    println
  }

}
