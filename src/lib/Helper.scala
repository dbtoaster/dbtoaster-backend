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

  def mux(actor:ActorRef,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,timeout:Long=0) : ((Long,Boolean,Int),List[Any]) = {
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ actor ! ev },ad,sp))},parallel)
    actor ! SystemInit; mux.read(); val tout = akka.util.Timeout(if (timeout==0) (1L<<42) /*139 years*/ else timeout)
    scala.concurrent.Await.result(akka.pattern.ask(actor,EndOfStream)(tout), tout.duration).asInstanceOf[((Long,Boolean,Int),List[Any])]
  }

  def run[Q<:akka.actor.Actor](streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,timeout:Long=0)(implicit cq:ClassTag[Q]) = {
    val system = actorSys("DDBT")
    val query = system.actorOf(Props[Q],"Query")
    try { mux(query,streams,parallel,timeout); } finally { system.shutdown }
  }

  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor](port:Int,N:Int,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,timeout:Long=0,debug:Boolean=false)(implicit cm:ClassTag[M],cw:ClassTag[W]) = {
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

  def time(ns:Long) = { val us=ns/1000; ("%d.%06d").format(us/1000000,us%1000000) }
  def bench[T](name:String,count:Int,f:()=>(Long,T)):T = {
    val out = (0 until math.max(1,count)).map { x => f() }
    val res = out.map(_._2).toList; res.tail.foreach(r=> assert(r==res.head,"Inconsistent results: "+res.head+" != "+r))
    val ts = out.map(_._1).sorted;
    println(name+": "+time(if (count%2==0) (ts(count/2)+ts(count/2-1))/2 else ts(count/2))+" ["+time(ts(0))+", "+time(ts(count-1))+"] (sec)"); res.head
  }

  // Query benchmark, supported arguments:
  //   -n<num>       number of samples (default=1)
  //   -d<set>       dataset selection (can be repeated), (default=standard)
  //   -h            hide the benchmark time
  //   -s            silent the query output
  //   -p            use parallel streams
  def bench2(args:Array[String],run:(String,Boolean)=>((Long,Boolean,Int),List[Any]),print:List[Any]=>Unit=null) {
    val parallel=args.contains("-p")
    var count:Int=1; args.filter(a=>a.startsWith("-n")).foreach { a=>count=a.substring(2).toInt }
    var ds=List[String](); args.filter(a=>a.startsWith("-d")).foreach { a=>ds=ds:::List(a.substring(2)) }; if (ds.size==0) ds=List("standard")
    ds.foreach { d=> var res0:List[Any]=null; var ts:List[(Long,Boolean,Int)]=Nil;
       // XXX: fix this
      val warm = 2
      (0 until math.max(1,count)).foreach { x => val ((t,finished,tupProc),res)=run(d,parallel);
        if(x >= warm && count > warm) { ts=(t,finished,tupProc)::ts; }; if (res0==null) res0=res else assert(res0==res,"Inconsistent results: "+res0+" != "+res)
      }
      ts = scala.util.Sorting.stableSort(ts, (e1: (Long,Boolean,Int), e2: (Long,Boolean,Int)) => e1._3.asInstanceOf[Double]/e1._1.asInstanceOf[Double] < e2._3.asInstanceOf[Double]/e2._1.asInstanceOf[Double]).toList
      val tsMed = ddbt.Utils.med3(ts)
      if (!args.contains("-h")) println(d+": ("+time(tsMed._1)+","+tsMed._2+","+tsMed._3+") [("+time(ts(0)._1)+","+ts(0)._2+","+ts(0)._3+"), ("+time(ts(ts.size-1)._1)+","+ts(ts.size-1)._2+","+ts(ts.size-1)._3+")] (sec, "+ts.size+" samples)")
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
  def diff[K,V](map1:Map[K,V],map2:Map[K,V]) { // map1 is the test result, map2 is the reference
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

  // ---------------------------------------------------------------------------
  // Stream definitions (used for manual debugging only)
  // XXX: remove this

  private def str(file:String,a:Adaptor) = (new java.io.FileInputStream("examples/data/"+file+".csv"),a,Split())
  def streamsFinance(s:String="") = Seq(str("finance"+(if (s!="") "-"+s else ""),Adaptor("orderbook",Nil)))
  def streamsRST(ss:Seq[String]=Seq("r")) = ss.map { s=> str("simple/"+s,new Adaptor.CSV(s.toUpperCase,"int,int")) }

  private def tpch(ss:Seq[String]) = ss.map{ n=>str("tpch/"+n,new Adaptor.CSV(n.toUpperCase,n match {
    case "orders" => "int,int,string,float,date,string,string,int,string"
    case "customer" => "int,string,string,int,string,float,string,string"
    case "supplier" => "int,string,string,int,string,float,string"
    case "lineitem" => "int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"
  },"\\|")) }
  def streamsTPCH1() = tpch(Seq("lineitem"))
  def streamsTPCH13() = tpch(Seq("orders","customer"))
  def streamsTPCH15() = tpch(Seq("lineitem","supplier"))
  def streamsTPCH18() = tpch(Seq("lineitem","orders","customer"))
}
