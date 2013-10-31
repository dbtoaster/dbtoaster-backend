package ddbt.lib
import akka.actor._

/**
 * Helper to startup cluster nodes and load appropriate actor on their system.
 * A node correspond usually to a physical host and an actor correspond to a
 * partition of the maps.
 *
 * Arguments:
 *   -n <name>            name of the actor system (shared across cluster)
 *   -b <base>            absolute class path prefix -> (baseWorker, baseMaster)
 *   -cp <classpath>      extra classpath to lookup master/worker actors
 *
 *   -h <host>:<port>     address:port for the local system
 *   -h <host>:<port>:<N> where N is the number of local actors/partitions
 *
 * Master-only arguments:
 *   -w <host>:<port>     master only: define the worker nodes
 *   -w <host>:<port>:<N>
 *
 *   -d <dataset>         dataset to use (default:standard)
 *   -p                   parallel streams
 *   -samples <num>       number of samples
 */
object ClusterApp {
  import WorkerActor._
  private var system:ActorSystem = null
  private var base = "ddbt.lib.Test"
  private var loader:Loader = null
  // Worker
  private var parts = 1 // number of local partitions
  // Master
  private var nodes:Array[(Address,Int)] = null // workers nodes(+partitons)
  private var dataset = "standard"
  private var parallel = false
  private var samples = 1

  import java.net.{URLClassLoader} // Duplicated from compiler utils (but anyway different context)
  private class Loader(cp:String) extends URLClassLoader(cp.split(":").map(p=>new java.io.File(p).toURI.toURL),null) {
    override def loadClass(name:String, resolve:Boolean) : Class[_] = {
      try { return super.loadClass(name, resolve); }
      catch { case e:ClassNotFoundException => Class.forName(name, resolve, ClusterApp.getClass.getClassLoader); }
    }
  }

  def parseArgs(args:Array[String]):Array[String] = {
    var name="DDBT"
    var hosts = List[(String,Int,Int)]()
    var rest = List[String]()
    var cp:String = "target/scala-2.10/test-classes"
    var my_host:String="127.0.0.1"; var my_port=0
    var i=0; val l=args.size; while(i<l) { args(i) match {
      case "-h" if i<l-1 => i+=1; val s=args(i).split(":"); my_host=s(0); my_port=s(1).toInt; if (s.size>2) parts=s(2).toInt
      case "-w" if i<l-1 => i+=1; val s=args(i).split(":"); hosts=(s(0),s(1).toInt,if (s.size>2) s(2).toInt else 1)::hosts
      case "-n" if i<l-1 => i+=1; name=args(i)
      case "-b" if i<l-1 => i+=1; base=args(i)
      case "-cp" if i<l-1 => i+=1; cp=args(i)
      case "-d" if i<l-1 => i+=1; dataset=args(i)
      case "-samples" if i<l-1 => i+=1; samples=math.max(1,args(i).toInt)
      case "-p" => parallel = true
      case s => rest = rest:+s // invalid arguments are passed further down
    }; i+=1 }
    if (cp!=null) loader=new Loader(cp) else ClusterApp.getClass.getClassLoader
    system = Helper.actorSys(name,my_host,my_port)
    nodes = hosts.map { case (host,port,num) => (new Address("akka.tcp",name,host,port),num) }.toArray
    rest.toArray
  }

  private def cls(name:String) = if (loader!=null) loader.loadClass(base+name) else Class.forName(base+name)
  def main(args:Array[String]) {
    val as=parseArgs(args)
    try {
      if (nodes!=null && nodes.size>0) {
        val master = system.actorOf(Props(cls("Master")),name="master")
        master ! ClusterNodes(nodes)
        println("MasterNode @ "+system)
        val streams:String=>Seq[(java.io.InputStream,Adaptor,Split)] = try {
          val cl = cls("$") // companion object
          val fn = cl.getMethod("streams","".getClass)
          val obj = cl.getField("MODULE$").get(null)
          (set:String) => fn.invoke(obj,set).asInstanceOf[Seq[(java.io.InputStream,Adaptor,Split)]]
        } catch { case t:Throwable => throw new Exception("Companion object "+base+".streams() not found") }

        // Stream data to the master
        var i=0; do {
          Thread.sleep(1000); // make sure all workers are resolved
          val (t,res)=Helper.mux(master,streams(dataset),parallel)
          println("Time: "+Helper.time(t))
          println("Result:\n"+res.mkString("\n\n"))
          master ! ClusterReset; i+=1;
        } while(i<samples);
        master ! ClusterShutdown
      } else {
        val p=Props(cls("Worker")); (0 until parts).foreach { i=>system.actorOf(p,name="worker"+i) }
        println("WorkerNode @ "+system+" with "+parts+" workers")
      }
    } catch { case t:Throwable => system.shutdown; throw t }
  }
}

// ------------------------------------------------------
// Cluster testing
object Test { def streams(s:String) = Seq[(java.io.InputStream,Adaptor,Split)]() }
class TestMaster() extends Actor {
  import WorkerActor._
  var ws:Array[ActorRef]=null
  var ctr=0
  println("Master ready: "+self)
  def receive = {
    case ClusterNodes(nodes) => implicit val timeout = akka.util.Timeout(5000)
      ws=nodes.flatMap{ case (n,c) => (0 until c).map { i=>
        scala.concurrent.Await.result(context.actorSelection(akka.actor.RootActorPath(n)/"user"/("worker"+i)).resolveOne,timeout.duration)
      }}; ws.foreach( _ ! "Ping" )
    case "Pong" => println("Got pong from "+sender); ctr=ctr+1; if (ctr==ws.size) { ws.foreach( _ ! PoisonPill ); Thread.sleep(500); context.system.shutdown }
  }
  override def postStop() = context.system.shutdown
}
class TestWorker() extends Actor {
  println("Worker ready: "+self)
  def receive = { case "Ping" => println("Got ping"); sender ! "Pong" }
  override def postStop() = context.system.shutdown
}
