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
      /*
      case Result(mj:java.util.HashMap[Any,Any]) => 
         val m = scala.collection.JavaConversions.mapAsScalaMap[Any,Any](mj).toMap
         val pp = new xml.PrettyPrinter(8000, 2);
         println(pp.format(<COUNT>{ toXML(m) }</COUNT>));
      */
      case Result(r) => println(r.toString)
      case StartTimer => t0 = System.nanoTime()
      case EndOfStream =>
        val t1 = System.nanoTime()
        val t = (t1-t0) / 1000
        println("Running time: %d.%06d".format(t/1000000,t%1000000))
        system.shutdown
    }

    def toXML[K,V](m:Map[K,V]): List[xml.Elem] = {
      val ft = new java.text.SimpleDateFormat("yyyyMMdd")
      def valToStr(v: Any): String = v match {
        case d:java.util.Date => ft.format(d)
        case x => x.toString
      }
      var l = List[xml.Elem]()
      m.foreach{case (k,v) => 
        val key = try {
            (k.asInstanceOf[Product].productIterator.foldLeft((0,List[xml.Elem]())) { 
                  case ((i,l), k) => (i+1, <xml>{ valToStr(k) }</xml>.copy(label=("__a" + i)) :: l)
            })._2.reverse
          } catch { case e:java.lang.ClassCastException => <__a0>{ valToStr(k) }</__a0> }
        l = <item>{ key }<__av>{ valToStr(v) }</__av></item> :: l
      }
      l
    }
  }
}
