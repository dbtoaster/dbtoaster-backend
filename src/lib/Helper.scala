package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorSystem,Props}

object Helper {
  // Message being passed to supervisor
  case object StartTimer
  case class SetSupervisor(actor:ActorRef)
  case class Result(r:Any)

  // System setup
  val system = ActorSystem("DDBT")
  val supervisor = system.actorOf(Props[Supervisor],"Supervisor")
  /*
  def main(args:Array[String]) {
    val act = system.actorOf(Props[AXFinder],"AXFinder")
    act ! SetSupervisor(sup)
    val s = new SourceFile("resources/data/finance.csv") // -standard
    s.setReceiver(act);
    sup ! StartTimer
    s.readAll
  }
  */

  // Wrapper to read data from disk
  case class SourceFile(file:String,bufSize:Int=128*1024) {
    var r:ActorRef = null
    val d = Decoder((ev:TupleEvent)=>{ r ! ev })
    def setReceiver(receiver:ActorRef) { r=receiver }

    def readAll() {
      val in = new java.io.FileInputStream(file)
      val buf = new Array[Byte](bufSize)
      var n:Int = 0
      do { n=in.read(buf); d.add(buf,n); } while (n>0);
      in.close()
      r ! EndOfStream
    }
  }

  // Supervisor for result output and time measurement
  class Supervisor extends Actor {
    var t0:Long = 0
    def receive = {
      case Result(r:Map[_,_]) => println(K3Helper.toStr(r))
      case Result(r) => println(r.toString)
      case StartTimer => t0 = System.nanoTime()
      case EndOfStream =>
        val t1 = System.nanoTime()
        val t = (t1-t0) / 1000
        println("Running time: %d.%6d".format(t/1000000,t%1000000))
        system.shutdown
    }
  }
}
