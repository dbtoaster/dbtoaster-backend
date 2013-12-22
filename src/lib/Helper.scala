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
    actor ! StreamInit(timeout); mux.read(); val tout = akka.util.Timeout(if (timeout==0) (1L<<42) /*139 years*/ else timeout+5000 /*extra time*/ )
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
    val res = try mux(master,streams,parallel,timeout) finally { Thread.sleep(100); nodes.foreach(_.shutdown); system.shutdown; Thread.sleep(100); }; res
  }

  // ---------------------------------------------------------------------------
  @inline private def mmm(ss:List[StreamStat]) = { val ts=ss.sorted; val n=ts.size; val m=ts(n/2); (if (n%2==1) m else { val b=ts(n/2-1); StreamStat((m.ns+b.ns)/2,(m.count+b.count)/2,(m.skip+b.skip+1)/2) },ts(0),ts(n-1)) } // mid: if 1 skip, result must skip

  // Query benchmark, supported arguments:
  //   -s<num>       number of samples (default=1)
  //   -w<num>       number of warmup transients to remove (default=0)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -t<num>       set execution timeout (in miliseconds)
  //   -h            hide output (verification mode)
  //   -h<str>       display the header (benchmark mode)
  //   -dp           disable parallel input streams
  //   -l<file>      dumps "dataset,time_ns,count,skip\n" for each sample in the file
  def bench(args:Array[String],run:(String,Boolean,Long)=>(StreamStat,List[Any]),op:List[Any]=>Unit=null) {
    def ad[T](s:String,d:T,f:String=>T) = args.filter(x=>x.startsWith(s)).lastOption.map(x=>f(x.substring(2))).getOrElse(d)
    val parallel=ad("-dp",true,x=>false)
    val samples = ad("-s",1,x=>math.max(1,x.toInt))
    val trans = ad("-w",0,x=>math.max(0,x.toInt))
    val timeout = ad("-t",0L,x=>x.toLong)
    var ds=args.filter(x=>x.startsWith("-d")).map(x=>x.substring(2)); if (ds.size==0) ds=Array("standard")
    val log=ad("-l",(data:String)=>{},file=>(data:String) => { val fw=new java.io.FileWriter(file,true); try fw.write(data) finally fw.close })
    val fmt=ad("-h",null,x=>x)
    if (fmt==null) println("Java "+System.getProperty("java.version")+", Scala "+util.Properties.versionString.replaceAll(".* ",""))
    ds.foreach { d=> var res0:List[Any]=null; var ts=List[StreamStat](); var i=0
      def pr(s:String,c:Boolean=true) = if (fmt!="") { println("%-70s".format((if (fmt!=null) "%-20s".format(fmt+" "+d) else d)+": "+s)); if (c) print("\033[F"+"[info] ") } // assumes terminal + SBT
      def f() = { val (t,res)=run(d,parallel,timeout); if (t.skip==0) { if (res0==null) res0=res else assert(res0==res,"Inconsistent results: "+res0+" != "+res); }; (t,res) }
      i=0; while (i<trans) { i+=1; f(); pr("."*i) }
      i=0; while(i<samples) { i+=1; val (t,res)=f(); ts=t::ts; log(d+","+t.ns+","+t.count+","+t.skip+"\n")
        val (med,min,max)=mmm(ts)
        val abs_time = timeout==0L || min.skip==0 && med.skip==0 && max.skip==0
        pr((if (abs_time) "%7s".format(med.t)+" ["+max.t+", "+min.t+"] (" else med.f+" ["+min.f+", "+max.f+"] (views/")+"sec, "+ts.size+(if (ts.size<samples) "/"+samples else "")+" samples)",ts.size<samples)
      }
      if (fmt!=null && fmt.size>0) { val (mid,min,max)=mmm(ts); println("EXEC_CSV="+d+":"+mid+min+max) }
      else if (res0!=null && op!=null) op(res0)
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
