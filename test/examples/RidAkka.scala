package ddbt.test.gen
import ddbt.lib._
import java.util.Date
import org.scalatest._

class RidSpec extends FunSpec {
  import Helper._
  import scala.language.implicitConversions
  implicit def dateConv(d:Long) = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  implicit def strConv(d:Long) = ""+d
  Rid.execute(Array("-n1","-dstandard","-h"),(res:List[Any])=>describe("Dataset 'standard'") {
    it("COUNT correct") {
      def kv(l:List[Any]) = l match { case List(v0:Long,v1:Long,v2:Long) => ((v0,v1),v2) }
      diff(res(0).asInstanceOf[Map[(Long,Long),Long]], Map[(Long,Long),Long](((3L,4L),1L),((2L,3L),2L),((5L,3L),1L),((1L,3L),1L),((4L,2L),2L),((4L,5L),1L),((5L,5L),1L),((2L,1L),1L)))
    }
  })
}

object Rid {
  import Helper._
  import WorkerActor._
  def streams(d:String) = Seq(
    (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/simple/tiny/r.dat"),new Adaptor.CSV("R","long,long","\\Q,\\E",if(d.endsWith("_del")) "ins+del" else "insert"),Split())
  )
  def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Boolean,t:Long)=>runLocal[RidMaster,RidWorker](22550,4,streams(d),p),f)
  def main(args:Array[String]) {
    execute(args,(res:List[Any])=>{
      println("COUNT:\n"+M3Map.toStr(res(0))+"\n")
    })
  }
}

class RidWorker extends WorkerActor {
  import WorkerActor._
  import ddbt.lib.Functions._
  import ddbt.lib.Messages._
  // constants
  val map0 = /*MapRef*/(0)
  val map1 = /*MapRef*/(1)
  val map2 = /*MapRef*/(2)
  val fa1 = /*FunRef*/(0)
  val fa2 = /*FunRef*/(1)

  // maps
  val COUNT = M3Map.make[(Long,Long),Long]();
  val COUNT_mR2_E2_1 = M3Map.make[Long,Long]();
  val COUNT_mR4 = M3Map.make[(Long,Long),Long]((k:(Long,Long))=>k._2);
  val local = Array[M3Map[_,_]](COUNT,COUNT_mR2_E2_1,COUNT_mR4)

  // remote foreach
  def forl(f:FunRef,args:Array[Any],co:()=>Unit) = (f,args.toList) match {
    case _ => co()
  }

  // remote aggregations
  def aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {
    case (`fa1`,List(r2_b:Long,r_a:Long)) =>
      val add2 = M3Map.temp[Long,Long]()
      COUNT_mR4.slice(0,r2_b).foreach { (k1,v1) =>
        val r2_a = k1._1;
        add2.add(r2_a,v1);
      }
      co(add2)
    case (`fa2`,List(r_a:Long,r_b:Long)) =>
      val add3 = M3Map.temp[(Long,Long),Long]()
      val COUNT_mR4_c = Acc()
      COUNT_mR4.foreach { (k4,v8) =>
        val r2_a = k4._1;
        val r2_b = k4._2;
        COUNT_mR4_c.i
        get(map1,r2_b,(v9:Long)=>{
        get(map1,r2_b,(v10:Long)=>{
        add3.add((r2_a,r2_b),(v8 * ((if (((v9 + ((if (r2_b == r_a) 1L else 0L) * -1L)))!=0) 1L else 0L) + ((if ((v10)!=0) 1L else 0L) * -1L))));
        COUNT_mR4_c.d
        }) })
      }
      COUNT_mR4_c(() => {
      co(add3)})
    case _ => co(null)
  }
}

class RidMaster extends RidWorker with MasterActor {
  import WorkerActor._
  import Messages._
  import Functions._

  val queries = List(0)
  val dispatch : PartialFunction[TupleEvent,Unit] = {
    case TupleEvent(TupleInsert,"R",List(v0:Long,v1:Long)) => onAddR(v0,v1)
    case TupleEvent(TupleDelete,"R",List(v0:Long,v1:Long)) => onDelR(v0,v1)
    case _ => deq
  }

  def onAddR(r_a:Long, r_b:Long) {
    pre(map0,false,Array[MapRef](map2,map1),()=> {
    val add1 = M3Map.temp[(Long,Long),Long]()
    val r2_b = r_a;
    val add2 = M3Map.temp[Long,Long]()
    aggr(map2,fa1,Array[Any](r2_b,r_a),add2,(_:M3Map[Long,Long]) => {
    val r2_a = r_a;
    add2.add(r2_a,(if (r2_b == r_b) 1L else 0L));
    val add2_c = Acc()
    add2.foreach { (k2,v2) =>
      val r2_a = k2;
      add2_c.i
      get(map1,r2_b,(v3:Long)=>{
      get(map1,r2_b,(v4:Long)=>{
      add1.add((r2_b,r2_a),(v2 * (((if ((v3)!=0) 1L else 0L) * -1L) + (if (((v4 + 1L))!=0) 1L else 0L))));
      add2_c.d
      }) })
    }
    add2_c(() => {
    val r2_a = r_a;
    val r2_b = r_b;
    get(map1,r2_b,(v5:Long)=>{
    add1.add((r2_b,r2_a),(if ((v5)!=0) 1L else 0L));
    add1.foreach { (k3,v6) =>
      val r2_b = k3._1;
      val r2_a = k3._2;
      add(map0,(r2_a,r2_b),v6);
    }
    pre(map1,false,Array[MapRef](),()=> {
    add(map1,r_a,1L);
    pre(map2,false,Array[MapRef](),()=> {
    add(map2,(r_a,r_b),1L);
    deq
    }) }) }) }) }) })
  }

  def onDelR(r_a:Long, r_b:Long) {
    pre(map0,false,Array[MapRef](map1,map2),()=> {
    val add3 = M3Map.temp[(Long,Long),Long]()
    val r2_a = r_a;
    val r2_b = r_b;
    get(map1,r2_b,(v7:Long)=>{
    add3.add((r2_a,r2_b),((if (((v7 + ((if (r2_b == r_a) 1L else 0L) * -1L)))!=0) 1L else 0L) * -1L));
    aggr(map2,fa2,Array[Any](r_a,r_b),add3,(_:M3Map[(Long,Long),Long]) => {
    add3.foreach { (k5,v11) =>
      val r2_a = k5._1;
      val r2_b = k5._2;
      add(map0,(r2_a,r2_b),v11);
    }
    pre(map1,false,Array[MapRef](),()=> {
    add(map1,r_a,-1L);
    pre(map2,false,Array[MapRef](),()=> {
    add(map2,(r_a,r_b),-1L);
    deq
    }) }) }) }) })
  }

  def onSystemReady() {
    ready
  }
}
