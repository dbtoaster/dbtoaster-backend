package ddbt.test.examples
import ddbt.lib._

import org.scalatest._
import akka.actor.Actor
import java.util.Date

class RltalldynamicSpec extends FunSpec with Helper {  
  import scala.language.implicitConversions
  implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  implicit def strConv(d:Long):String = ""+d
  describe("Dataset 'standard'") {
    val (t,res) = runLocal[RltalldynamicMaster,RltalldynamicWorker](3,2251,4,Seq(
      (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/simple/tiny/r.dat"),new Adaptor.CSV("R","long,long","\\Q,\\E"),Split())
    ))
    it("COUNT correct") {
      def kv(l:List[Any]) = l match { case List(v0:Long,v1:Long,v2:Long) => ((v0,v1),v2) }
      diff(res(0).asInstanceOf[Map[(Long,Long),Long]], Map[(Long,Long),Long]())
    }
  }
}

class RltalldynamicWorker extends WorkerActor {
  import WorkerActor._
  import ddbt.lib.Functions._
  // constants
  val map0 = MapRef(0)
  val map1 = MapRef(1)
  val map2 = MapRef(2)
  val fa1 = FunRef(0)
  
  // maps
  val COUNT = M3Map.make[(Long,Long),Long]();
  val COUNT_mR1 = M3Map.make[(Long,Long),Long]();
  val COUNT_mR1_L2_1 = M3Map.make[Long,Long]();
  val local = Array[M3Map[_,_]](COUNT,COUNT_mR1,COUNT_mR1_L2_1)
  
  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match { case _ => co() }
  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {
    // Problem with calling aggregation in the aggregation
    //case (`fa1`,_) => get(map2,0L,co)
    case (`fa1`,_) => co(COUNT_mR1_L2_1.get(0L))
    case _ => co(null)
  }
}

class RltalldynamicMaster extends RltalldynamicWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import Functions._
  
  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"R",List(v0:Long,v1:Long)) => onAddR(v0,v1)
    case TupleEvent(TupleDelete,"R",List(v0:Long,v1:Long)) => onDelR(v0,v1)
    case _ => deq
  }
  
  def onAddR(r_a:Long, r_b:Long) { aggr(map1,fa1,Array(0L,0L),null,(x:Long)=>deq); }
  def onDelR(r_a:Long, r_b:Long) { deq }
  def onSystemReady() { ready }
}
