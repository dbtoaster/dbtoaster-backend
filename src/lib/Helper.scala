package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorSystem,Props,Deploy,Address}
import akka.remote.RemoteScope
import scala.reflect.ClassTag
import java.io.InputStream

trait Helper {
  import Messages._

  // ---------------------------------------------------------------------------
  // Remoting helpers
  def sys(name:String,host:String,port:Int) = {
    val conf = "akka.loglevel=ERROR\nakka.log-dead-letters-during-shutdown=off\n"+ // disable verbose logging
               "akka {\nactor.provider=\"akka.remote.RemoteActorRefProvider\"\nremote.netty {\nhostname=\""+host+"\"\ntcp.port="+port+"\n}\n}\n"
    val system = ActorSystem(name, com.typesafe.config.ConfigFactory.parseString(conf))
    Runtime.getRuntime.addShutdownHook(new Thread{ override def run() = { /*println("Stopping "+host+":"+port);*/ system.shutdown() } });
    /*println("Started "+host+":"+port);*/ system
  }
  def props[A<:Actor](name:String,host:String,port:Int)(implicit cA:ClassTag[A]) = {
    Props(cA.runtimeClass).withDeploy(Deploy(scope = RemoteScope(new Address("akka.tcp",name,host,port))))
  }
  
  // ---------------------------------------------------------------------------
  // Run query actor and collect time+resulting map
  
  def mux[K,V](actor:ActorRef,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,wait:Int=60000) = {
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ actor ! ev },ad,sp))},parallel)
    actor ! SystemInit
    // preload existing tables in the query
    mux.read()
    val timeout = akka.util.Timeout(wait)
    scala.concurrent.Await.result(akka.pattern.ask(actor,EndOfStream)(timeout), timeout.duration).asInstanceOf[(Long,Map[K,V])]
  }
  
  def run[Q<:akka.actor.Actor,K,V](streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false)(implicit cq:ClassTag[Q]):(Long,Map[K,V]) = {
    val system = ActorSystem("DDBT")
    val query = system.actorOf(Props[Q],"Query")
    val res = mux[K,V](query,streams,parallel)
    system.shutdown; res
  }
    
  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor,K,V](port:Int,N:Int,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false)(implicit cm:ClassTag[M],cw:ClassTag[W]):(Long,Map[K,V]) = {
    val system:ActorSystem = this.sys("MasterSystem","127.0.0.1",port-1)
    val nodes = (0 until N).map { i => sys("NodeSystem"+i,"127.0.0.1",port+i) }
    val wprops = (0 until N).map { i=>props[W]("NodeSystem"+i,"127.0.0.1",port+i) }.toArray
    val master = system.actorOf(Props(cm.runtimeClass,wprops))
    val res = mux[K,V](master,streams,parallel)
    Thread.sleep(100); nodes.foreach{ _.shutdown }; system.shutdown; Thread.sleep(100); res
  }
  
  def time(ns:Long) = { val ms=ns/1000000; "%d.%03d".format(ms/1000,ms%1000) }
  def bench[K,V](name:String,count:Int,f:()=>(Long,Map[K,V])):Map[K,V] = {
    val out = (0 until count).map { x => f() }
    val res = out.map(_._2).toList; assert(res.tail.filter{ x=> x!=res.head }.isEmpty)
    val ts = out.map(_._1).sorted;
    println(name+" : "+time(ts(count/2))+" ["+time(ts(0))+", "+time(ts(count-1))+"] (sec)"); res.head
  }

  // ---------------------------------------------------------------------------
  // Stream definitions
  def streamsFinance(s:String="") = {
    val file = new java.io.FileInputStream("resources/data/finance"+(if (s!="") "-"+s else "")+".csv")
    Seq((file,Adaptor("orderbook",Nil),Split()))
  }
  def streamsTPCH15() = {
    def s(n:String,s:String) = (new java.io.FileInputStream("resources/data/tpch/"+n+".csv"),new Adaptor.CSV(n.toUpperCase,s,"\\|"),Split())
    Seq(s("lineitem","int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"),
        s("supplier","int,string,string,int,string,float,string"))
  }
  def streamsTPCH18() = {
    def s(n:String,s:String) = (new java.io.FileInputStream("resources/data/tpch/"+n+".csv"),new Adaptor.CSV(n.toUpperCase,s,"\\|"),Split())
    Seq(s("lineitem","int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"),
        s("orders","int,int,string,float,date,string,string,int,string"),
        s("customer","int,string,string,int,string,float,string,string"))
  }
}
