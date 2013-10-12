package ddbt.generated
import ddbt.lib._
import java.util.Date

object RbaAkka extends Helper {
  import WorkerActor._
  def main(args:Array[String]) {
    val (t,res) = runLocal[RbaAkkaMaster,RbaAkkaWorker](5,2251,4,Seq(
      (new java.io.FileInputStream("examples/data/simple/r.dat"),new Adaptor.CSV("R","double,double","\\Q,\\E"),Split())
    ))
    println("__SQL_SUM_AGGREGATE_2:\n"+M3Map.toStr(res(0))+"\n")
    println("Time = "+time(t));
  }
}

class RbaAkkaWorker extends WorkerActor {
  import WorkerActor._
  import ddbt.lib.Functions._
  // constants
  val map0 = MapRef(0)
  val map1 = MapRef(1)
  val map2 = MapRef(2)
  val fa1 = FunRef(0)
  val fa2 = FunRef(1)
  
  // maps
  val __SQL_SUM_AGGREGATE_2 = M3Map.make[Double,Double]();
  val __SQL_SUM_AGGREGATE_2_mR4 = M3Map.make[Double,Double]();
  var __SQL_SUM_AGGREGATE_2_mR8:Double = 0.0
  val local = Array[M3Map[_,_]](__SQL_SUM_AGGREGATE_2,__SQL_SUM_AGGREGATE_2_mR4,null)
  
  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match {
    case _ => co()
  }
  
  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {
    case (`fa1`,List(r_a:Double,r_b:Double)) =>
      val add_r1 = M3Map.temp[Double,Double]()
      __SQL_SUM_AGGREGATE_2_mR4.foreach { (k1,v1) =>
        val r1_a = k1;
        add_r1.add(r1_a,(v1 * r_a));
      }
      co(add_r1)
    case (`fa2`,List(r_a:Double,r_b:Double)) =>
      val add_r2 = M3Map.temp[Double,Double]()
      __SQL_SUM_AGGREGATE_2_mR4.foreach { (k3,v3) =>
        val r1_a = k3;
        add_r2.add(r1_a,(v3 * (-1L * r_a)));
      }
      co(add_r2)
    case _ => co(null)
  }
}

class RbaAkkaMaster extends RbaAkkaWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import Functions._
  import scala.util.continuations._
  
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"R",List(v0:Double,v1:Double)) => onAddR(v0,v1)
    case TupleEvent(TupleDelete,"R",List(v0:Double,v1:Double)) => onDelR(v0,v1)
  }
  
  def onAddR(r_a:Double, r_b:Double) = {
    pre(map0,Array[MapRef](map2,map1),(u:Unit)=> {
    val add_l1 = M3Map.temp[Double,Double]()
    val r1_a = r_a;
    add_l1.add(r1_a,(r_b * (r_a + __SQL_SUM_AGGREGATE_2_mR8)));
    aggr(map1,fa1,Array[Any](r_a,r_b),M3Map.temp[Double,Double](),(add_r1:M3Map[Double,Double]) => {
    add_r1.sum(add_l1);
    add_l1.foreach{ (k2,v2) =>
      val r1_a = k2
      add(map0,r1_a,v2);
    }
    pre(map1,Array[MapRef](),(u:Unit)=> {
    add(map1,r_a,r_b);
    pre(map2,Array[MapRef](),(u:Unit)=> {
    __SQL_SUM_AGGREGATE_2_mR8 += r_a;
    deq })})})})
  }
  
  def onDelR(r_a:Double, r_b:Double) = {
    pre(map0,Array[MapRef](map2,map1),(u:Unit)=> {
    val add_l2 = M3Map.temp[Double,Double]()
    val r1_a = r_a;
    add_l2.add(r1_a,(r_b * (r_a + (__SQL_SUM_AGGREGATE_2_mR8 * -1L))));
    aggr(map1,fa2,Array[Any](r_a,r_b),M3Map.temp[Double,Double](),(add_r2:M3Map[Double,Double]) => {
    add_r2.sum(add_l2);
    add_l2.foreach{ (k4,v4) =>
      val r1_a = k4
      add(map0,r1_a,v4);
    }
    pre(map1,Array[MapRef](),(u:Unit)=> {
    add(map1,r_a,(-1L * r_b));
    pre(map2,Array[MapRef](),(u:Unit)=> {
    __SQL_SUM_AGGREGATE_2_mR8 += (-1L * r_a);
    deq })})})})
  }
  
  def onSystemReady() = {
    __SQL_SUM_AGGREGATE_2_mR8 = 0.0;
  }
}
