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
  @inline private def askWait[T](actor:ActorRef,msg:Any,timeout:Long=0L) = {
    val to=akka.util.Timeout(if (timeout<=0) (1L << 42) /*139 years*/ else timeout+200000)
    scala.concurrent.Await.result(akka.pattern.ask(actor,msg)(to), to.duration).asInstanceOf[T]
  }
  def mux(actor:ActorRef,streams:Streams,parallel:Int=0,timeout:Long=0L) = {
    val mux = SourceMux((ev:TupleEvent)=>{ actor ! ev },streams.map {case (in,ad,sp) => (in,ad,sp)},parallel)
    actor ! StreamInit(timeout); mux.read(); askWait[(StreamStat,List[Any])](actor,EndOfStream,timeout)
  }

  def run[Q<:akka.actor.Actor](streams:Streams,parallel:Int=0,timeout:Long=0L)(implicit cq:ClassTag[Q]) = {
    val system = actorSys()
    val query = system.actorOf(Props[Q],"Query")
    try { mux(query,streams,parallel,timeout); } finally { system.shutdown }
  }

  // ---------------------------------------------------------------------------
  // Akka helper, reuse the same nodes across samples. Uses additional arguments to configure:
  // 0|1: -H<host:port> -W<workers> -C<cluster_mode>:<hosts_num>  [debug]
  // 2|3: -H<host:port> -W<workers> -M<master_host>:<master_port> [worker]
  //      -H<host:port> -W<total_expected_workers>                [master]
  private var runMaster:ActorRef = null
  private var runCount = 0
  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor](args:Array[String])(streams:Streams,parallel:Int=0,timeout:Long=0L)(implicit cm:ClassTag[M],cw:ClassTag[W]) : (StreamStat,List[Any]) = {
    def ad[T](s:String,d:T,f:Array[String]=>T) = args.filter(_.startsWith(s)).lastOption.map(x=>f(x.substring(s.length).split(":"))).getOrElse(d)
    val master:ActorRef = if (runCount>0 && runMaster!=null) { runCount-=1; runMaster }
    else { runCount=ad("-n",0,x=>math.max(0,x(0).toInt-1))
      val (debug,hosts_num)=ad("-C",(ad("-H",0,x=>2),1),x=>(x(0).toInt,x(1).toInt))
      val (host,port)=ad("-H",("127.0.0.1",8800),x=>(x(0),x(1).toInt))
      val wnum = ad("-W",1,x=>x(0).toInt)
      val isMaster = debug <= 1 || ad("-M",true,x=>false)
      val system = if (debug==0) actorSys() else actorSys(host=host,port=port)
      val workers:Seq[ActorRef] = debug match {
        case 0 => (0 until hosts_num * wnum).map(i=>system.actorOf(Props[W]())) // launch all in one system
        case 1 => (0 until hosts_num).flatMap { h=> val s=actorSys("DDBT"+h,host,port+1+h); (0 until wnum).map(i=>s.actorOf(Props[W]())) } // launch one system for each node group
        case _ => if (isMaster) Seq() else (0 until wnum).map(i=>system.actorOf(Props[W]()))
      }
      val master = if (isMaster) system.actorOf(Props[M](),name="master") else null
      debug match {
        case 0|1 => master ! Members(master,workers.toArray)
        case _ if isMaster =>askWait[Any](system.actorOf(Props(classOf[HelperActor],master,wnum),name="helper"),"ready")
        case _ => val (h,p)=ad("-M",(host,port),x=>(x(0),x(1).toInt)); system.actorSelection("akka.tcp://DDBT@"+h+":"+p+"/user/helper") ! workers.toArray
          println(wnum+" workers started"); system.awaitTermination; println("Shutdown"); System.exit(0)
      }
      class HelperActor(master:ActorRef,waiting:Int) extends Actor {
        private var workers = new Array[ActorRef](0)      // Collects all workers advertisements and forward them to the master.
        private var watcher = null.asInstanceOf[ActorRef] // Responds to "ready" when all workers are available.
        def receive = {
          case "ready" => watcher=sender; if (workers.size==waiting) watcher ! ()
          case as:Array[ActorRef] => workers++=as; if (workers.size==waiting) { master ! Members(master,workers.toArray); if (watcher!=null) watcher ! () }
        }
      }
      //try mux(master,streams,parallel,timeout) finally { master ! ClusterShutdown; Thread.sleep(100); System.gc; Thread.sleep(100) }
      master
    }
    try mux(master,streams,parallel,timeout) finally {
      if (runCount>0) { runMaster=master; master ! Reset } else { runMaster=null; master ! Shutdown }
      Thread.sleep(100); System.gc; Thread.sleep(100)
    }
  }

  // ---------------------------------------------------------------------------
  // Query benchmark, supported arguments:
  //   -n<num>       number of samples (default=1)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -t<num>       set execution timeout (in miliseconds)
  //   -m<num>       0=hide output (verification mode), 1=sampling (benchmark mode)
  //   -p<num>       parallel input streams 0=disabled 1=threads 2=deterministic
  def bench(args:Array[String],run:(String,Int,Long)=>(StreamStat,List[Any]),op:List[Any]=>Unit=null) {
    def ad[T](s:String,d:T,f:String=>T) = args.filter(_.startsWith(s)).lastOption.map(x=>f(x.substring(s.length))).getOrElse(d)
    val num = ad("-n",1,x=>math.max(0,x.toInt))
    val mode = ad("-m",-1,x=>x.toInt)
    val timeout = ad("-t",0L,x=>x.toLong)
    val parallel = ad("-p",2,x=>x.toInt)
    var ds = args.filter(x=>x.startsWith("-d")).map(x=>x.substring(2)); if (ds.size==0) ds=Array("standard")
    if (mode < 0) println("Java "+System.getProperty("java.version")+", Scala "+util.Properties.versionString.replaceAll(".* ",""))
    ds.foreach { d=> var i=0; var res0:List[Any]=null
      while (i<num) { i+=1;
        val (t,res)=run(d,parallel,timeout);
        if (t.skip==0) { 
          if (res0==null) 
            res0=res 
          else 
            assert(res0==res,"Inconsistent results: "+res0+" != "+res);
        }
        if (mode==1) println("SAMPLE="+d+","+(t.ns/1000)+","+t.count+","+t.skip)
        if (mode < 0) println("Time: "+t)
      }
      if (mode!=1 && res0!=null && op!=null) op(res0)
    }
  }

  // ---------------------------------------------------------------------------
  // Correctness helpers

  val precision = 7 // significative numbers (7 to pass r_sumdivgrp, 10 otherwise)
  private val diff_p = Math.pow(0.1,precision)
  private def eq_v[V](v1:V,v2:V) = ((v1,v2) match { 
    case (d1:Double,d2:Double) => (Math.abs(2*(d1-d2)/(d1+d2))<diff_p) 
    case (l:Long,d:Double) => (Math.abs(2*(d-l)/(d+l))<diff_p) 
    case (d:Double,l:Long) => (Math.abs(2*(d-l)/(d+l))<diff_p) 
    case _ => v1==v2 })
  private def eq_l(l1:List[Any],l2:List[Any]) = { (l1 zip l2).forall{ case (v1,v2) => eq_v(v1,v2) } }
  private def eq_p(p1:Product,p2:Product) = { val n=p1.productArity; assert(n==p2.productArity);  List.range(0,n).forall(i => eq_v(p1.productElement(i), p2.productElement(i))) }

  def diff(v1:List[Any],v2:List[Any]) = if (!eq_p(v1,v2)) throw new Exception("Bad value: "+v1+" (expected "+v2+")")

  /* Checks whether the test result is the same as the reference. 
   * 
   * @param map1 The map containing the test result
   *
   * @param map2 The map containing the reference result
   */
  def diff[K](map1:Map[K,List[Any]],map2:Map[K,List[Any]]) = {
    import scala.collection.mutable.HashMap
    import java.util.Date
    val m1 = map1.filter{ case (k,v) => map2.get(k) match { case Some(v2) => v2!=v case None => true } }
    val m2 = map2.filter{ case (k,v) => map1.get(k) match { case Some(v2) => v2!=v case None => true } }

    // merges similar keys within one map (using sorting)
    def rekey(m:Map[K,List[Any]]):HashMap[K,List[Any]] = {
      val l0 = m.toList.sortBy(_._1.toString) // not nicest but works
      val z = if (l0.size==0) null else l0(0)._2.map(v => v match { case d:Double => 0.0 case _ => 0L })
      val mm = HashMap[K,List[Any]]() 
      def re(l:List[(K,List[Any])]):Unit = l match {
        case a::b::ls if ((a._1,b._1) match { case (p1:Product,p2:Product) => 
          eq_p(p1,p2) case (k1,k2) => eq_v(k1,k2) }) => mm += (a._1 -> (a._2 zip b._2).map({ case (v1,v2) => (v1,v2) match { case (d1:Double,d2:Double) => d1+d2 case (l1:Long,l2:Long) => l1+l2 case _ => sys.error("Expected long or double") } })) 
          re(ls)
        case a::ls => mm += (a._1 -> a._2); re(ls)
        case Nil =>
      }
      re(l0); 
      mm
    }
    if (m1.size>0 || m2.size>0) {
      val err=new StringBuilder()
      val b1 = rekey(m1)
      val b2 = rekey(m2)
      // ignore 'almost zero' values
      // b1.toMap.foreach { x=> x._2 match { case d1:Double => if (Math.abs(d1)<diff_p) b1.remove(x._1) case _ => }}       
      b1.toMap.foreach { case (k1,v1) =>
        b2.toMap.foreach { case (k2,v2) =>
          if (b1.contains(k1) && b2.contains(k2)) {
            val (k,v) = ((k1,k2) match { case (p1:Product,p2:Product) => eq_p(p1,p2) case _ => eq_v(k1,k2) }, (v1,v2) match { case (p1:List[Any],p2:List[Any]) => eq_l(p1,p2) case _ => eq_v(v1,v2) })
            if (k) { b1.remove(k1); b2.remove(k2); if (!v) err.append("Bad value: "+k1+" -> "+v1+" (expected "+v2+")\n") }
          }
        }
      }
      b1.foreach { case (k,v) => err.append("Extra key: "+k+" -> "+v+"\n") }
      b2.foreach { case (k,v) => err.append("Missing key: "+k+" -> "+v+"\n") }
      val s = err.toString; if (s!="") { val e=new Exception("Result differs:\n"+s); e.setStackTrace(Array[StackTraceElement]()); throw e }
    }
  }

  def loadCSV[K,V](kv:List[Any]=>(K,List[Any]),file:String,fmt:String,sep:String=","):Map[K,List[Any]] = {
    val m = new java.util.HashMap[K,List[Any]]()
    def f(e:TupleEvent) = { val (k,v)=kv(e.data); m.put(k,v) }
    val s = SourceMux(f,Seq((new java.io.FileInputStream(file),new Adaptor.CSV("REF",fmt,sep),Split())))
    s.read; scala.collection.JavaConversions.mapAsScalaMap(m).toMap
  }
}
