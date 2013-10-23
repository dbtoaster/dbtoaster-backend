package ddbt.test.examples
import ddbt.lib._

import org.scalatest._
import akka.actor.Actor
import java.util.Date

// r_indynamic

class RidSpec extends FunSpec {
  import Helper._
  import scala.language.implicitConversions
  implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  implicit def strConv(d:Long):String = ""+d
  describe("Dataset 'standard'") {
    it("COUNT correct") {
      (0 until 5).foreach{ x=>  
        val (t,res) = runLocal[RidMaster,RidWorker](2251,4,Seq(
          (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/simple/tiny/r.dat"),new Adaptor.CSV("R","long,long","\\Q,\\E"),Split())
        ))
        def kv(l:List[Any]) = l match { case List(v0:Long,v1:Long,v2:Long) => ((v0,v1),v2) }
        diff(res(0).asInstanceOf[Map[(Long,Long),Long]], Map[(Long,Long),Long](((3L,4L),1L),((2L,3L),2L),((5L,3L),1L),((1L,3L),1L),((4L,2L),2L),((4L,5L),1L),((5L,5L),1L),((2L,1L),1L)))
      }
    }
  }
}

class RidWorker extends WorkerActor {
  import WorkerActor._
  import ddbt.lib.Functions._
  // constants
  val map0 = MapRef(0)
  val map1 = MapRef(1)
  val map2 = MapRef(2)
  val fa1 = FunRef(0)
  val fa2 = FunRef(1)
  val fa3 = FunRef(2)
  // maps
  val COUNT = M3Map.make[(Long,Long),Long]();
  val COUNT_mR2_E2_1 = M3Map.make[Long,Long]();
  val COUNT_mR4 = M3Map.make[(Long,Long),Long]((k:(Long,Long))=>k._2);
  val local = Array[M3Map[_,_]](COUNT,COUNT_mR2_E2_1,COUNT_mR4)
  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match { case _ => co() }
  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {
    /*
    case (`fa1`,List(r_a:Long,r_b:Long)) =>
      val add_l1 = M3Map.temp[(Long,Long),Long]()
      val r2_b = r_a;
      aggr(map2,fa2,Array[Any](r2_b,r_a),M3Map.temp[Long,Long](),(add_l2:M3Map[Long,Long]) => {
      val add_r1 = M3Map.temp[Long,Long]()
      val r2_a = r_a;
      add_r1.add(r2_a,(if (r2_b == r_b) 1L else 0L));
      add_r1.sum(add_l2);
      add_l2.foreach{ (k2,v2) =>
        val r2_a = k2
        get(map1,r2_b,(v3:Long)=>{
        get(map1,r2_b,(v4:Long)=>{
        add_l1.add((r2_b,r2_a),(v2 * (((if ((v3)!=0) 1L else 0L) * -1L) + (if (((v4 + 1L))!=0) 1L else 0L))));
      }
      co(add_l1)}) }) })
    */
    case (`fa2`,List(r2_b:Long)) =>
      val add_l2 = M3Map.temp[Long,Long]()
      COUNT_mR4.slice(0,r2_b).foreach { (k1,v1) =>
        val r2_a = k1._1;
        add_l2.add(r2_a,v1);
      }
      co(add_l2)
    /*
    case (`fa3`,List(r_a:Long,r_b:Long)) =>
      val add_r2 = M3Map.temp[(Long,Long),Long]()
      val r2_a = r_a;
      val r2_b = r_b;
      add_r2.add((r2_b,r2_a),(if ((COUNT_mR2_E2_1.get(r2_b))!=0) 1L else 0L));
      co(add_r2)
    */
    case _ => co(null)
  }
}

class RidMaster extends RidWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import Functions._
  import scala.util.continuations._
  
  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"R",List(v0:Long,v1:Long)) => onAddR(v0,v1)
    case TupleEvent(TupleDelete,"R",List(v0:Long,v1:Long)) => onDelR(v0,v1)
    case _ => deq
  }

  def onAddR(r_a:Long, r_b:Long) {
    pre(map0,Array[MapRef](map2,map1),(u:Unit)=> {

    val add1 = M3Map.temp[(Long,Long),Long]()
    val add2 = M3Map.temp[Long,Long]()
    //COUNT_mR4.slice(0,r_a).foreach { (k3,v3) => add2.add(k3._1,v3) }
    //val acc2=Acc()
    //acc2.i
    aggr(map2,fa2,Array[Any](r_a),add2,(_:M3Map[Long,Long]) => { //acc2.d })
    //acc2(_=>{
        
    add2.add(r_a,(if (r_a == r_b) 1L else 0L));
    add2.foreach{ (k2,v2) =>
      val v3 = COUNT_mR2_E2_1.get(r_a)
      add1.add((r_a,k2),(v2 * ((if (v3!=0) -1L else 0L) + (if (v3 + 1L!=0) 1L else 0L))));
    }

    add1.add((r_b,r_a),(if ((COUNT_mR2_E2_1.get(r_b))!=0) 1L else 0L));
    add1.foreach{ (k3,v5) => add(map0,(k3._2,k3._1),v5) }

    pre(map1,Array[MapRef](),_=> {
    COUNT_mR2_E2_1.add(r_a,1L); //add(map1,r_a,1L);
    pre(map2,Array[MapRef](),_=> {
    add(map2,(r_a,r_b),1L);
    deq }) }) }) })
  }

/*
  def onAddR(r_a:Long, r_b:Long) {
    val add1 = M3Map.temp[(Long,Long),Long]()
    ;{
      val r2_b = r_a;
      val add2 = M3Map.temp[Long,Long]()
      COUNT_mR4.slice(0,r2_b).foreach { (k3,v3) =>
        val r2_a = k3._1;
        add2.add(r2_a,v3);
      }
      val r2_a = r_a;
      add2.add(r2_a,(if (r2_b == r_b) 1L else 0L));
      add2.foreach{ (k2,v2) =>
        val r2_a = k2
        add1.add((r2_b,r2_a),(v2 * (((if ((COUNT_mR2_E2_1.get(r2_b))!=0) 1L else 0L) * -1L) + (if (((COUNT_mR2_E2_1.get(r2_b) + 1L))!=0) 1L else 0L))));
      }
    };
    ;{
      val r2_a = r_a;
      val r2_b = r_b;
      add1.add((r2_b,r2_a),(if ((COUNT_mR2_E2_1.get(r2_b))!=0) 1L else 0L));
    };
    add1.foreach{ (k1,v1) =>
      val r2_b = k1._1
      val r2_a = k1._2
      COUNT.add((r2_a,r2_b),v1);
    }
    COUNT_mR2_E2_1.add(r_a,1L);
    COUNT_mR4.add((r_a,r_b),1L);
  }
*/
  
  /*
  def onAddR(r_a:Long, r_b:Long) {
    pre(map0,Array[MapRef](map2,map1),(u:Unit)=> {
    aggr(map2,fa1,Array[Any](r_a,r_b),M3Map.temp[(Long,Long),Long](),(add_l1:M3Map[(Long,Long),Long]) => {
    aggr(map1,fa3,Array[Any](r_a,r_b),M3Map.temp[(Long,Long),Long](),(add_r2:M3Map[(Long,Long),Long]) => {
    add_r2.sum(add_l1);
    add_l1.foreach{ (k3,v5) =>
      val r2_b = k3._1
      val r2_a = k3._2
      add(map0,(r2_a,r2_b),v5);
    }
    pre(map1,Array[MapRef](),(u:Unit)=> {
    add(map1,r_a,1L);
    pre(map2,Array[MapRef](),(u:Unit)=> {
    add(map2,(r_a,r_b),1L);
    deq}) }) }) }) })
  }
  */
  
  def onDelR(r_a:Long, r_b:Long) { deq }
  def onSystemReady() { ready }
}
