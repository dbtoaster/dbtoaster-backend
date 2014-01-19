package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import akka.remote.RemoteScope
import scala.reflect.ClassTag
import java.io.InputStream

object Helper {
  import Messages._

  // ---------------------------------------------------------------------------
  // Akka helpers
  def actorSys(name:String="DDBT",host:String=null,port:Int=0) = {
    val conf = "akka.loglevel=ERROR\nakka.log-dead-letters-during-shutdown=off\n"+ // disable verbose logging
               MessageSerializer.conf()+ // custom serializer
               (if (host!=null) "akka {\nactor.provider=\"akka.remote.RemoteActorRefProvider\"\nremote {\n"+
                "enabled-transports=[\"akka.remote.netty.tcp\"]\nnetty.tcp {\nhostname=\""+host+"\"\nport="+port+"\n}\n"+"}\n}\n" else "")
    val user = { val f="conf/akka.conf"; if (new java.io.File(f).exists) scala.io.Source.fromFile(f).mkString else "" }
    val system = ActorSystem(name, com.typesafe.config.ConfigFactory.parseString(conf+user))
    //Runtime.getRuntime.addShutdownHook(new Thread{ override def run() = { /*println("Stopping "+host+":"+port);*/ system.shutdown() } });
    /*println("Started "+host+":"+port);*/ system
  }

  // ---------------------------------------------------------------------------
  // Run query actor and collect time + resulting maps or values (for 0-key maps)
  // The result is usually like List(Map[K1,V1],Map[K2,V2],Value3,Map...)
  private type Streams = Seq[(InputStream,Adaptor,Split)]
  private def askWait[T](actor:ActorRef,msg:Any,timeout:Long=0L) = {
    val to=akka.util.Timeout(if (timeout<=0) (1L<<42) /*139 years*/ else timeout)
    scala.concurrent.Await.result(akka.pattern.ask(actor,msg)(to), to.duration).asInstanceOf[T]
  }

  def mux(actor:ActorRef,streams:Streams,parallel:Boolean=true,timeout:Long=0) = {
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ actor ! ev },ad,sp))},parallel)
    actor ! StreamInit(timeout); mux.read(); askWait[(StreamStat,List[Any])](actor,EndOfStream,if (timeout==0) 0 else timeout+2000)
  }

  def run[Q<:akka.actor.Actor](streams:Streams,parallel:Boolean=true,timeout:Long=0)(implicit cq:ClassTag[Q]) = {
    val system = actorSys()
    val query = system.actorOf(Props[Q],"Query")
    try { mux(query,streams,parallel,timeout); } finally { system.shutdown }
  }


  // 0|1: -Hhost:port -Wworkers -Ccluster_mode:hosts_num
  // 2|3: -Hhost:port -Wworkers -Mhost:port (worker)
  //      -Hhost:port -Wworkers             (master)
  private var runMaster:ActorRef = null
  private var runCount = 0
  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor](args:Array[String])(streams:Streams,parallel:Boolean=true,timeout:Long=0)(implicit cm:ClassTag[M],cw:ClassTag[W]) : (StreamStat,List[Any]) = {

    val master:ActorRef = if (runCount>0 && runMaster!=null) { runCount-=1; runMaster }
    else { runCount=args.filter(_.startsWith("-n")).lastOption.map(x=>math.max(0,x.substring(2).toInt-1)).getOrElse(0)

    // SINGLE RUN ---------------------
    def ad[T](s:String,d:T,f:Array[String]=>T) = args.filter(_.startsWith(s)).lastOption.map(x=>f(x.substring(s.length).split(":"))).getOrElse(d)
    def ac(s:String) = args.filter(_.startsWith(s)).size>0
    val (debug,hosts_num)=ad("-C",(if (ac("-H")) 2 else 0,1),x=>(x(0).toInt,x(1).toInt))
    val (host,port)=ad("-H",("127.0.0.1",8800),x=>(x(0),x(1).toInt))
    val wnum = ad("-W",1,x=>x(0).toInt)
    val isMaster = args.filter(_.startsWith("-M")).size==0 || debug <= 1
    val system = if (debug==0) actorSys() else actorSys(host=host,port=port)
    val workers:Seq[ActorRef] = debug match {
      case 0 => (0 until hosts_num * wnum).map(i=>system.actorOf(Props[W]())) // launch all in one system
      case 1 => (0 until hosts_num).flatMap { h=> val s=actorSys("DDBT"+h,host,port+1+h); (0 until wnum).map(i=>s.actorOf(Props[W]())) } // launch one system for each node group
      case _ => if (isMaster) Seq() else (0 until wnum).map(i=>system.actorOf(Props[W]()))
    }
    val master = if (isMaster) system.actorOf(Props[M](),name="master") else null

    // Refactor a bit below
    import WorkerActor._
    debug match {
      case 0|1 => master ! Members(master,workers.toArray)
      case _ =>
        if (isMaster) askWait[Any](system.actorOf(Props(classOf[HelperActor],master,wnum),name="helper"),"ready")
        else {
          val (h,p)=ad("-M",(host,port),x=>(x(0),x(1).toInt)); system.actorSelection("akka.tcp://DDBT@"+h+":"+p+"/user/helper") ! workers.toArray
          println("Worker ready"); system.awaitTermination; println("Worker stopped"); System.exit(0); return (StreamStat(0,0,0),Nil)
        }
    }
    class HelperActor(master:ActorRef,waiting:Int) extends Actor {
      var workers = new Array[ActorRef](0)
      var watcher = null.asInstanceOf[ActorRef]
      def receive = {
        case "ready" => watcher=sender; if (workers.size==waiting) watcher ! ()
        case as:Array[ActorRef] => workers++=as; if (workers.size==waiting) { master ! WorkerActor.Members(master,workers.toArray); if (watcher!=null) watcher ! () }
      }
    }
    //try mux(master,streams,parallel,timeout) finally { master ! ClusterShutdown; Thread.sleep(100); System.gc; Thread.sleep(100) }
    // SINGLE RUN ---------------------
    master
    }

    import WorkerActor._
    try mux(master,streams,parallel,timeout) finally {
      if (runCount>0) { master ! ClusterReset; runMaster=master; }
      else { master ! ClusterShutdown; runMaster=null; }
      Thread.sleep(100); System.gc; Thread.sleep(100)
    }

    // DEBUG ----------------------
    /*
    def m(d:String="tiny") = SourceMux(Seq((
      new java.io.FileInputStream("/Documents/EPFL/Data/cornell_db_maybms/dbtoaster/experiments/data/finance/"+d+"/finance.csv"),
      Decoder((ev:TupleEvent)=>{ master ! ev },new Adaptor.OrderBook(brokers=10,deterministic=true,bids="BIDS",asks="ASKS"))
    )))
    println("Ev1")
    master ! StreamInit(); m().read()
    println(askWait[(StreamStat,List[Any])](master,EndOfStream))
    master ! ClusterReset;
    println("Ev2")
    master ! StreamInit(); m().read()
    println(askWait[(StreamStat,List[Any])](master,EndOfStream))
    println("Ev3")
    */
    // DEBUG ----------------------


/*
*/
    /*
    // test:run-main ddbt.test.gen.Axfinder
    // println(args.toList)
    val port:Int = 22550
    val N = 4
    val debug = true

    val (system,nodes,workers) = if (debug) {
      val system = actorSys("DDBT")
      (system,Seq[ActorSystem](),(0 until N).map (i=>system.actorOf(Props[W]())))
    } else {
      val system = actorSys("MasterSystem","127.0.0.1",port-1)
      val nodes = (0 until N).map { i => actorSys("NodeSystem"+i,"127.0.0.1",port+i) }
      val workers = nodes.map (_.actorOf(Props[W]()))
      (system,nodes,workers)
    }
    val master = system.actorOf(Props[M]())
    master ! WorkerActor.Members(master,workers.toArray) // initial membership
    val res = try mux(master,streams,parallel,timeout) finally { Thread.sleep(100); nodes.foreach(_.shutdown); system.shutdown; Thread.sleep(100); }; res
    */
  }

  // ---------------------------------------------------------------------------
  // Query benchmark, supported arguments:
  //   -n<num>       number of samples (default=1)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -t<num>       set execution timeout (in miliseconds)
  //   -m<num>       0=hide output (verification mode), 1=sampling (benchmark mode)
  //   -p            une parallel input streams
  def bench(args:Array[String],run:(String,Boolean,Long)=>(StreamStat,List[Any]),op:List[Any]=>Unit=null) {
    def ad[T](s:String,d:T,f:String=>T) = args.filter(_.startsWith(s)).lastOption.map(x=>f(x.substring(s.length))).getOrElse(d)
    val num = ad("-n",1,x=>math.max(0,x.toInt))
    val mode = ad("-m",-1,x=>x.toInt)
    val timeout = ad("-t",0L,x=>x.toLong)
    val parallel = ad("-p",false,x=>true)
    var ds = args.filter(x=>x.startsWith("-d")).map(x=>x.substring(2)); if (ds.size==0) ds=Array("standard")
    if (mode<0) println("Java "+System.getProperty("java.version")+", Scala "+util.Properties.versionString.replaceAll(".* ",""))
    ds.foreach { d=> var i=0; var res0:List[Any]=null
      while (i<num) { i+=1;
        val (t,res)=run(d,parallel,timeout); if (t.skip==0) { if (res0==null) res0=res else assert(res0==res,"Inconsistent results: "+res0+" != "+res); }
        if (mode==1) println("SAMPLE="+d+","+(t.ns/1000)+","+t.count+","+t.skip)
        if (mode<0) println("Time: "+t)
      }
      if (mode!=1 && res0!=null && op!=null) op(res0)
    }
  }

  // ---------------------------------------------------------------------------
  // Correctness helpers

  val precision = 7 // significative numbers (7 to pass r_sumdivgrp, 10 otherwise)
  private val diff_p = Math.pow(0.1,precision)
  private def eq_v[V](v1:V,v2:V) = v1==v2 || ((v1,v2) match { case (d1:Double,d2:Double) => (Math.abs(2*(d1-d2)/(d1+d2))<diff_p) case _ => false })
  private def eq_p(p1:Product,p2:Product) = { val n=p1.productArity; assert(n==p2.productArity); var r=true; for (i <- 0 until n) { r = r && eq_v(p1.productElement(i),p2.productElement(i)) }; r }

  def diff[V](v1:V,v2:V) = if (!eq_v(v1,v2)) throw new Exception("Bad value: "+v1+" (expected "+v2+")")
  def diff[K,V](map1:Map[K,V],map2:Map[K,V]) = { // map1 is the test result, map2 is the reference
    val m1 = map1.filter{ case (k,v) => map2.get(k) match { case Some(v2) => v2!=v case None => true } }
    val m2 = map2.filter{ case (k,v) => map1.get(k) match { case Some(v2) => v2!=v case None => true } }
    if (m1.size>0 || m2.size>0) {
      val err=new StringBuilder()
      val b1 = scala.collection.mutable.HashMap[K,V](); b1 ++= m1
      val b2 = scala.collection.mutable.HashMap[K,V](); b2 ++= m2
      m1.foreach { x=> x._2 match { case d1:Double => if (Math.abs(d1)<diff_p) b1.remove(x._1) case _ => }} // ignore 'almost zero' values
      m1.foreach { case (k1,v1) =>
        m2.foreach { case (k2,v2) =>
          if (b1.contains(k1) && b2.contains(k2)) {
            val (k,v) = ((k1,k2) match { case (p1:Product,p2:Product) => eq_p(p1,p2) case _ => eq_v(k1,k2) }, eq_v(v1,v2))
            if (k) { b1.remove(k1); b2.remove(k2); if (!v) err.append("Bad value: "+k1+" -> "+v1+" (expected "+v2+")\n") }
          }
        }
      }
      b1.foreach { case (k,v) => err.append("Extra key: "+k+" -> "+v+"\n") }
      b2.foreach { case (k,v) => err.append("Missing key: "+k+" -> "+v+"\n") }
      val s = err.toString; if (s!="") { val e=new Exception("Result differs:\n"+s); e.setStackTrace(Array[StackTraceElement]()); throw e }
    }
  }

  def loadCSV[K,V](kv:List[Any]=>(K,V),file:String,fmt:String,sep:String=","):Map[K,V] = {
    val m = new java.util.HashMap[K,V]()
    def f(e:TupleEvent) = { val (k,v)=kv(e.data); m.put(k,v) }
    val d = Decoder(f,new Adaptor.CSV("REF",fmt,sep),Split())
    val s = SourceMux(Seq((new java.io.FileInputStream(file),d)))
    s.read; scala.collection.JavaConversions.mapAsScalaMap(m).toMap
  }
}
