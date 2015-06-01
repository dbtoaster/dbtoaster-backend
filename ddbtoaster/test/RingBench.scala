package ddbt.test
import akka.actor.{Actor,ActorRef,ActorSystem,Props}

// Ring benchmark N processes ring, sent a message M times around the ring
// https://foundationdb.com/white-papers/flow
// https://foundationdb.com/operations
// https://foundationdb.com/acid-claims

object RingConf {
  val N = 1000 // number of nodes
  val M = 1000 // number of loops
}
import RingConf._

object RingBench {
  import ddbt.lib.Helper._
  import ddbt.Utils._

  @inline private def askWait[T](actor:ActorRef,msg:Any,timeout:Long=0L) = {
    val to=akka.util.Timeout(if (timeout<=0) (1L<<42) /*139 years*/ else timeout+200000)
    scala.concurrent.Await.result(akka.pattern.ask(actor,msg)(to), to.duration).asInstanceOf[T]
  }

  def main(args: Array[String]) {
    val system = actorSys()
    val as = (0 until N).map { i=> system.actorOf(if (i==0) Props[Mon] else Props[Proc]) }
    val n=as.size; var i=0; while (i<n) { as(i) ! as((i+1)%n); i+=1; } // make a ring
    (0 until 10).foreach { x =>
      val (t,c)=ns(()=>askWait[Int](as(0),M*N))
      println("Time = "+time(t)+" sec ("+((c*1000000000.0)/t)+" msg/s)")
    }
    system.shutdown
  }
}

class Mon extends Actor {
  var next:ActorRef = null
  var sink:ActorRef = null
  var max = 0
  def receive = {
    case i:Int =>
      if (i>=max) {
        if (sink==null) { sink=sender; max=i; next ! 1 }
        else { sink ! (i+1); sink=null; max=0; }
      } else next ! (i+1)
    case n:ActorRef => next=n
  }
}

class Proc extends Actor {
  var next:ActorRef = null
  def receive = {
    case i:Int => next ! (i+1)
    case n:ActorRef => next=n
  }
}
