package test

import ddbt.lib._ //.{K3Map,K3Helper,Messages}
import akka.actor.Props
//import scala.reflect.ClassTag
//import scala.concurrent.{Future,Await}
//import akka.actor.{Actor,ActorRef,ActorSystem,Props,Deploy,Address}
//import akka.remote.RemoteScope
//import akka.pattern.ask

// -----------------------------------------------------------------------------
/*
class MyWorker extends WorkerActor {
  import WorkerActor._
  val map:MapRef = 0
  val m1 = K3Map.make[Long,Double]()
  def local[K,V](m:MapRef) = m1.asInstanceOf[K3Map[K,V]]
  def myReceive : PartialFunction[Any,Unit] = {
    case Foreach(1,List(d:Double)) => m1.foreach{case (k,v) => map.get(k-1,(v:Double)=>map.add(k,d+v)) }
    case Aggr(id,1,Nil) => sender ! AggrPart(id,m1.aggr{case (k,v) => v})
  }
  override def receive = myReceive orElse super.receive
}
class MyMaster(props:Array[Props]) extends MasterActor(props) {
  import WorkerActor._
  import Messages._
  val map:MapRef = 0
  override def receive = myReceive orElse super.receive
  def myReceive : PartialFunction[Any,Unit] = {
    case TupleEvent(_,_,_,_) =>
      //println("OK ----------")
      flush()
      //println("OK ----------")
      flush()
      //println("OK ----------")
      for (i <- 0 until 10) map.add(i.toLong,1.0)
      map.foreach(1,List(3.0))
      //map.get(0L,(d:Double)=>println("map(0)="+d))
      map.aggr(1,Nil,(d:Double)=>map.add(100L,d))
  }
}

object MyHelper extends Helper {
  // -------- specific
  val N = 2
  val port = 2551

  import Messages._
  def main(args:Array[String]) {
    val (t,r) = runLocal[MyMaster,MyWorker,Long,Double](port,N,streamsFinance());
    println("Time : "+time(t)+"\n"+K3Helper.toStr(r))
  }
}
*/
