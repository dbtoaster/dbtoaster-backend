package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import akka.remote.RemoteScope
import scala.reflect.ClassTag
import java.io.InputStream

object Helper {
  import Messages._

  // ---------------------------------------------------------------------------
  // Akka helpers
  def actorSys(name:String,host:String=null,port:Int=0) = {
    val conf = "akka.loglevel=ERROR\nakka.log-dead-letters-during-shutdown=off\n"+ // disable verbose logging
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

  def mux(actor:ActorRef,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=true,timeout:Long=0) = {
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ actor ! ev },ad,sp))},parallel)
    actor ! StreamInit(timeout); mux.read(); val tout = akka.util.Timeout(if (timeout==0) (1L<<42) /*139 years*/ else timeout)
    scala.concurrent.Await.result(akka.pattern.ask(actor,EndOfStream)(tout), tout.duration).asInstanceOf[(StreamStat,List[Any])]
  }

  def run[Q<:akka.actor.Actor](streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=true,timeout:Long=0)(implicit cq:ClassTag[Q]) = {
    val system = actorSys("DDBT")
    val query = system.actorOf(Props[Q],"Query")
    try { mux(query,streams,parallel,timeout); } finally { system.shutdown }
  }

  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor](port:Int,N:Int,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=true,timeout:Long=0,debug:Boolean=false)(implicit cm:ClassTag[M],cw:ClassTag[W]) = {
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
    val res = try { mux(master,streams,parallel,timeout) } finally { Thread.sleep(100); nodes.foreach(_.shutdown); system.shutdown; Thread.sleep(100); }; res
  }

  // Query benchmark, supported arguments:
  //   -n<num>       number of samples (default=1)
  //   -w<num>       number of warmup transients to remove (default=0)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -t<num>       set execution timeout (in miliseconds)
  //   -h            hide the benchmark time
  //   -h<str>       display the header
  //   -s            silent the query output
  //   -dp           disable parallel input streams
  //   -o<csv_file>  dump "med,min,max," for each dataset file
  //   -l<log_file>  dump "dataset,time_ns,count,skip\n" for each sample in the file
  def bench(args:Array[String],run:(String,Boolean,Long)=>(StreamStat,List[Any]),print:List[Any]=>Unit=null) {
    def append(file:String,data:String) { val fw=new java.io.FileWriter(file,true); try fw.write(data) finally fw.close }
    def ad[T](s:String,d:T,f:String=>T) = args.filter(x=>x.startsWith(s)).lastOption.map(x=>f(x.substring(2))).getOrElse(d)
    val parallel=ad("-dp",true,x=>false)
    val count = ad("-n",1,x=>x.toInt)
    val trans = ad("-w",0,x=>x.toInt)
    val timeout = ad("-t",0L,x=>x.toLong)
    var ds=args.filter(x=>x.startsWith("-d")).map(x=>x.substring(2)); if (ds.size==0) ds=Array("standard")
    val out=ad("-o",null,x=>x)
    val log=ad("-l",null,x=>x)
    val fmt=ad("-h",null,x=>x)
    ds.foreach { d=> var res0:List[Any]=null;
      def f(x:Int) = { val (t,res)=run(d,parallel,timeout); if (res0==null) res0=res else assert(res0==res,"Inconsistent results: "+res0+" != "+res); t }
      (0 until math.max(0,trans)).foreach(f)
      val ts = (0 until math.max(1,count)).map{x=>val r=f(x); if (log!=null) append(log,d+","+r.ns+","+r.count+","+r.skip+"\n"); r}.sorted.toList
      val mid = if (count%2==0) { val (a,b)=(ts(count/2),ts(count/2-1)); StreamStat((a.ns+b.ns)/2,(a.count+b.count)/2,(a.skip+b.skip)/2) } else ts(count/2)
      val (min,max)=(ts(0),ts(count-1))
      def cf(s:StreamStat) = "\""+s.count+"/"+(s.ns/1000000000)+".06d".format(s.ns/1000)+"\""
      if (out!=null) append(out,cf(mid)+","+cf(min)+","+cf(max)+",")
      if (!args.contains("-h")) println((if (fmt!=null) "%-20s".format(fmt+" "+d) else d)+": "+mid.f+" ["+min.f+", "+max.f+"] (views/sec, "+count+" samples)")
      if (!args.contains("-s") && res0!=null && print!=null) print(res0)
    }
  }

  // ---------------------------------------------------------------------------
  // Unit testing helpers

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
