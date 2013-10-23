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
 *   -w <host>:<port>     master only: define the worker nodes
 *   -w <host>:<port>:<N>
 */
object ClusterApp {
  private var system:ActorSystem = null
  private var nodes:List[(Address,Int)]=Nil // master: workers nodes(+partitons)
  private var parts = 1 // worker: number of local partitions
  private var base = "ddbt.lib.My"
  private var loader:Loader = null

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
      case s => rest = rest:+s // invalid arguments are passed further down
    }; i+=1 }
    if (cp!=null) loader=new Loader(cp) else ClusterApp.getClass.getClassLoader
    system = Helper.actorSys(name,my_host,my_port)
    nodes = hosts.map { case (host,port,num) => (new Address("akka.tcp",name,host,port),num) }
    rest.toArray
  }
  
  private def props(cls:String) = Props(if (loader!=null) loader.loadClass(base+cls) else Class.forName(base+cls))
  
  def main(args:Array[String]) {
    val as=parseArgs(args)
    if (nodes!=Nil) {
      try {
        system.actorOf(props("Master"),name="master") ! Nodes(nodes)
        println("MasterNode: "+system)
      } catch { case t:Throwable => system.shutdown; throw t }
    } else {
      try {
        val p=props("Worker"); (0 until parts).foreach { i=>system.actorOf(p,name="worker"+i) }
        println("WorkerNode: "+system+", "+parts+" workers")
      } catch { case t:Throwable => system.shutdown; throw t }
    }
  }
  
  def actors(ctx:ActorContext,ns:Nodes):List[ActorRef] = {
    implicit val timeout = akka.util.Timeout(1000*5) // 5 seconds
    ns.nodes.flatMap{ case (n,c) => (0 until c).map { i=>
      scala.concurrent.Await.result(ctx.actorSelection(RootActorPath(n)/"user"/("worker"+i)).resolveOne,timeout.duration)
    }}
  }
}

case class Nodes(nodes:List[(Address,Int)])

// ------------------------------------------------------
// Cluster testing
class MyMaster() extends Actor {
  var ws:List[ActorRef]=Nil
  var ctr=0
  println("Master ready: "+self)
  def receive = {
    case ns:Nodes => ws=ClusterApp.actors(context,ns); ws.foreach( _ ! "Ping" )
    case "Pong" => println("Got pong from "+sender); ctr=ctr+1
      if (ctr==ws.size) { ws.foreach( _ ! PoisonPill ); Thread.sleep(500); context.system.shutdown }
  }
  override def postStop() = context.system.shutdown
}
class MyWorker() extends Actor {
  println("Worker ready: "+self)
  def receive = {
    case "Ping" => println("Got ping"); sender ! "Pong"
  }
  override def postStop() = context.system.shutdown
}
// ------------------------------------------------------

// Dumb tester
/*
case class Ask(nodes:List[Address])
*/

/*
import akka.cluster.Cluster
import akka.cluster.ClusterEvent._
import akka.cluster.MemberStatus
import akka.cluster.Member


object ClusterApp {
  var master=false // if this node is the master
  var workers=0      // number of worker nodes in the cluster
  var system:ActorSystem=null

  private def read_args(args:Array[String]) { var i=0; val l=args.length
    var ma_host:String=null; var ma_port=0
    var my_host:String=null; var my_port=0
    while(i<l) { args(i) match {
      case "-m" if i<l-1 => i+=1; val s=args(i).split(":"); ma_host=s(0); ma_port=s(1).toInt
      case "-h" if i<l-1 => i+=1; val s=args(i).split(":"); my_host=s(0); my_port=s(1).toInt
      case "-n" if i<l-1 => i+=1; workers=args(i).toInt
      case "-M" => master=true
      case _ => // XXX: call the appropriate class
    }; i+=1 }
    if (master) { my_host=ma_host; my_port=ma_port }
    val name = "ClusterSystem"
    val conf =
      "akka {\n"+
      "  loglevel=off\nstdout-loglevel=off\n"+
      "  log-dead-letters-during-shutdown=off\n"+
      "  actor.provider=\"akka.cluster.ClusterActorRefProvider\"\n"+
      "  remote {\n"+
      "    log-remote-lifecycle-events = off\n"+
      "    netty.tcp {\n"+
      (if (my_host!=null) "hostname=\""+my_host+"\"\n" else "")+
      (if (my_port>0) "port="+my_port+"\n" else "")+
      "    }\n"+
      "  }\n"+
      "  cluster {\n"+
      "    seed-nodes = [\"akka.tcp://"+name+"@"+ma_host+":"+ma_port+"\"]\n"+
      "    auto-down = on\n"+
      "  }\n"+
      "}\n"
    system = ActorSystem(name, com.typesafe.config.ConfigFactory.parseString(conf))
  }

  def main(args:Array[String]) {
    read_args(args)
    // println("Master = "+master+" nodes = "+nodes)
    // Class.forName("com.duke.MyLocaleServiceProvider");
    // val clusterListener = system.actorOf(Props[SimpleClusterListener], name = "clusterListener")
    // Cluster(system).subscribe(clusterListener, classOf[ClusterDomainEvent])

    val path="target/scala-2.10/test-classes"
    val base="ddbt.test.examples.AX"

    val loader=new Loader(path);
    val c_master=loader.loadClass(base+"Master")
    val c_worker=loader.loadClass(base+"Worker")

    val actor = system.actorOf(if (master) Props(c_master) else Props(c_worker),"node")
    println("My actor is ready: "+actor)
    if (master) system.actorOf(Props(classOf[Streamer],actor,workers))
  }

  import java.net.{URL,URLClassLoader} // Duplicated from compiler utils (but anyway different context)
  private class Loader(cp:String) extends URLClassLoader(Array(new java.io.File(cp).toURI.toURL),null) {
    override def loadClass(name:String, resolve:Boolean) : Class[_] = {
      try { return super.loadClass(name, resolve); }
      catch { case e:ClassNotFoundException => Class.forName(name, resolve, ClusterApp.getClass.getClassLoader); }
    }
  }
}

// Acts as the main object
class Streamer(master:ActorRef,workers:Int) extends Actor {
  import Helper._
  val cluster = Cluster(context.system)
  override def preStart(): Unit = cluster.subscribe(self, classOf[ClusterDomainEvent])
  override def postStop(): Unit = cluster.unsubscribe(self)

  private val members = scala.collection.mutable.Set[Member]()
  def register(m:Member) {
    members += m; println("New member: "+m.address)
    if (members.size==workers+1) {
      println("Ready to begin")
      implicit val timeout = akka.util.Timeout(1000*5) // 5 seconds
      val workers = members.map{ m=> println("Lookup for "+m.address); val a=scala.concurrent.Await.result(context.actorSelection(RootActorPath(m.address)/"user"/"node").resolveOne(),timeout.duration); println("Got1"); a }.filter(a=>a!=master)
      println("Master : "+master)
      println("Workers: "+workers.mkString(", "))

      import WorkerActor.{Members,MapRef}
      val nmaps = 5;
      val ms = (0 until nmaps).map { MapRef(_) }.toList
      master ! Members(master,workers.map{ w => (w,ms) }.toArray)
      val (t,res) = mux(master,Seq(
        (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/finance/tiny/finance.csv"),new Adaptor.OrderBook(brokers=10,deterministic=true,bids="BIDS",asks="ASKS"),Split())
      ))
      println("Time = "+time(t)); println(M3Map.toStr(res.head))
    }
  }

  def receive = {
    //case state: CurrentClusterState => state.members.filter(_.status == MemberStatus.Up) foreach register
    case MemberUp(m) => register(m)
    case UnreachableMember(member) => println("Member detected as unreachable: "+member)
    case MemberRemoved(member, previousStatus) => println("Member "+member.address+" is removed after "+previousStatus)
  }
}

/*
object ClusterHelper {
  def sys(name:String,port:Int=0) = {
    val conf = """
akka.loglevel = "OFF"
akka.stdout-loglevel = "OFF"
akka.log-dead-letters-during-shutdown=off
akka {
  actor.provider = "akka.cluster.ClusterActorRefProvider"
  remote {
    log-remote-lifecycle-events = off
    netty.tcp {
      hostname = "127.0.0.1"
      port = """+port+"""
    }
  }
  cluster {
    seed-nodes = ["akka.tcp://ClusterSystem@127.0.0.1:2551"]
    auto-down = on
  }
}
"""
    ActorSystem(name, com.typesafe.config.ConfigFactory.parseString(conf))
  }
}

class SimpleClusterListener extends Actor {
  def receive = {
    case state: CurrentClusterState => println("Current members: "+state.members.mkString(", "))
    case MemberUp(member) => println("Member is Up: "+member.address)
    case UnreachableMember(member) => println("Member detected as unreachable: "+member)
    case MemberRemoved(member, previousStatus) => println("Member is Removed: "+member.address+" after "+previousStatus)
    case _: ClusterDomainEvent => // ignore
  }
}
 
object SimpleClusterApp {
  def main(args: Array[String]): Unit = {
    val system = ClusterHelper.sys("ClusterSystem", if (args.nonEmpty) args(0).toInt else 0)
    val clusterListener = system.actorOf(Props[SimpleClusterListener], name = "clusterListener")
    Cluster(system).subscribe(clusterListener, classOf[ClusterDomainEvent])
  }
}

// run-main sample.cluster.simple.SimpleClusterApp 2551
// run-main sample.cluster.simple.SimpleClusterApp 2552
// run-main sample.cluster.simple.SimpleClusterApp

// -----------------------------------------------------------------------------

case class TransformationJob(text: String)
case class TransformationResult(text: String)
case class JobFailed(reason: String, job: TransformationJob)
case object BackendRegistration

class TransformationBackend extends Actor { 
  val cluster = Cluster(context.system)
  // subscribe to cluster changes, MemberUp
  // re-subscribe when restart
  override def preStart(): Unit = cluster.subscribe(self, classOf[MemberUp])
  override def postStop(): Unit = cluster.unsubscribe(self)
 
  def receive = {
    case TransformationJob(text) => sender ! TransformationResult(text.toUpperCase)
    case state: CurrentClusterState =>
      state.members.filter(_.status == MemberStatus.Up) foreach register
    case MemberUp(m) => register(m)
  }
 
  def register(member: Member): Unit =
    if (member.hasRole("frontend"))
      context.actorSelection(RootActorPath(member.address) / "user" / "frontend") !
        BackendRegistration
}

class TransformationFrontend extends Actor {
  var backends = IndexedSeq.empty[ActorRef]
  var jobCounter = 0
 
  def receive = {
    case job: TransformationJob if backends.isEmpty =>
      sender ! JobFailed("Service unavailable, try again later", job)
 
    case job: TransformationJob =>
      jobCounter += 1
      backends(jobCounter % backends.size) forward job
 
    case BackendRegistration if !backends.contains(sender) =>
      context watch sender
      backends = backends :+ sender
 
    case Terminated(a) => backends = backends.filterNot(_ == a)
  }
}

run-main ddbt.cluster.TransformationFrontend 2551
run-main ddbt.cluster.TransformationBackend 2552
run-main ddbt.cluster.TransformationBackend
run-main ddbt.cluster.TransformationBackend
run-main ddbt.cluster.TransformationFrontend
*/
*/
