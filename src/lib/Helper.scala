package ddbt.lib

import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import scala.reflect.ClassTag
import java.io.InputStream

trait Helper {
  import Messages._

  def ask[T](a:ActorRef,m:Any):T = {
    import scala.concurrent.duration._
    val timeout = akka.util.Timeout(60.seconds)
    scala.concurrent.Await.result(akka.pattern.ask(a,m)(timeout), timeout.duration).asInstanceOf[T]
  }

  def run[Q<:akka.actor.Actor,K,V:ClassTag](streams:Seq[(InputStream,Adaptor,Split)],parallel:Boolean=false,conf:String=null)(implicit cq:ClassTag[Q]):(Long,Map[K,V]) = {
    val system = ActorSystem("DDBT")
    val query = system.actorOf(Props[Q],"Query")
    val mux = SourceMux(streams.map {case (in,ad,sp) => (in,Decoder((ev:TupleEvent)=>{ query ! ev },ad,sp))},parallel)
    query ! SystemInit
    // preload existing tables in the query
    mux.read()
    val res = ask[(Long,Map[K,V])](query,EndOfStream)
    system.shutdown
    res
  }

  def printTime(ns:Long) { val ms = ns/1000000; println("time: %d.%03ds".format(ms/1000,ms%1000)) }
  def printMap[K,V](m:Map[K,V]) { println(K3Helper.toStr(m)) } // XXX: remove duplicates

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
