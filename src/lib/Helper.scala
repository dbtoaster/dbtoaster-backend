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
  // T is usually Map[K,V]. For multiple maps, it is a tuple (Map[K1,V1],Map[K2,V2],...)
  
  def mux[T](actor:ActorRef,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,wait:Int=60000) = {
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ actor ! ev },ad,sp))},parallel)
    actor ! SystemInit
    // preload existing tables in the query
    mux.read()
    val timeout = akka.util.Timeout(wait)
    scala.concurrent.Await.result(akka.pattern.ask(actor,EndOfStream)(timeout), timeout.duration).asInstanceOf[(Long,T)]
  }
  
  def run[Q<:akka.actor.Actor,T](streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false)(implicit cq:ClassTag[Q]):(Long,T) = {
    val system = ActorSystem("DDBT")
    val query = system.actorOf(Props[Q],"Query")
    val res = mux[T](query,streams,parallel)
    system.shutdown; res
  }
    
  def runLocal[M<:akka.actor.Actor,W<:akka.actor.Actor,T](port:Int,N:Int,streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false)(implicit cm:ClassTag[M],cw:ClassTag[W]):(Long,T) = {
    val system:ActorSystem = this.sys("MasterSystem","127.0.0.1",port-1)
    val nodes = (0 until N).map { i => sys("NodeSystem"+i,"127.0.0.1",port+i) }
    val wprops = (0 until N).map { i=>props[W]("NodeSystem"+i,"127.0.0.1",port+i) }.toArray
    val master = system.actorOf(Props(cm.runtimeClass,wprops))
    val res = mux[T](master,streams,parallel)
    Thread.sleep(100); nodes.foreach{ _.shutdown }; system.shutdown; Thread.sleep(100); res
  }
  
  def time(ns:Long) = { val ms=ns/1000000; "%d.%03d".format(ms/1000,ms%1000) }
  def bench[T](name:String,count:Int,f:()=>(Long,T)):T = {
    val out = (0 until count).map { x => f() }
    val res = out.map(_._2).toList; assert(res.tail.filter{ x=> x!=res.head }.isEmpty)
    val ts = out.map(_._1).sorted;
    println(name+" : "+time(ts(count/2))+" ["+time(ts(0))+", "+time(ts(count-1))+"] (sec)"); res.head
  }

  // ---------------------------------------------------------------------------
  // Unit testing helpers
  def diff[K,V](m1:Map[K,V],m2:Map[K,V]) {
    // XXX: complete here
    assert(m1==m2)
  }
  
  def loadCSV[K,V](kv:List[Any]=>(K,V),file:String,fmt:String,sep:String=","):Map[K,V] = {
    val m = new java.util.HashMap[K,V]()
    def f(e:TupleEvent) = { val (k,v)=kv(e.data); m.put(k,v) }
    val d = Decoder(f,new Adaptor.CSV("REF",fmt,sep),Split())
    val s = SourceMux(Seq((new java.io.FileInputStream(file),d)))
    s.read; scala.collection.JavaConversions.mapAsScalaMap(m).toMap
  }

  // ---------------------------------------------------------------------------
  // Stream definitions
  def streamsFinance(s:String="") = {
    val file = new java.io.FileInputStream("resources/data/finance"+(if (s!="") "-"+s else "")+".csv")
    Seq((file,Adaptor("orderbook",Nil),Split()))
  }

  private def s(n:String,s:String) = (new java.io.FileInputStream("resources/data/tpch/"+n+".csv"),new Adaptor.CSV(n.toUpperCase,s,"\\|"),Split())
  def streamsTPCH13() = Seq(
        s("orders","int,int,string,float,date,string,string,int,string"),
        s("customer","int,string,string,int,string,float,string,string"))
  def streamsTPCH15() = Seq(
        s("lineitem","int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"),
        s("supplier","int,string,string,int,string,float,string"))
  def streamsTPCH18() = Seq(
        s("lineitem","int,int,int,int,float,float,float,float,string,string,date,date,date,string,string,string"),
        s("orders","int,int,string,float,date,string,string,int,string"),
        s("customer","int,string,string,int,string,float,string,string"))
}
