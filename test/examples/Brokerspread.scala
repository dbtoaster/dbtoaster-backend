package ddbt.test.examples
import ddbt.lib._

import akka.actor.Actor
import java.util.Date

object BrokerSpread extends Helper {  
  import ddbt.Utils._
  import scala.language.implicitConversions
  implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  //implicit def strConv(d:Long):String = ""+d

  private val sql = read(path_repo+"/"+path_base+"/test/queries/finance/brokerspread.sql")

  def ref(size:String="standard"):Map[Long,Double] = {
    // GENERATED WITH:
    // bin/dbtoaster_release -l scala test/queries/finance/brokerspread.sql > tmp.scala
    // fsc -cp lib/dbt_scala/dbtlib.jar tmp.scala lib/dbt_scala/src/org/dbtoaster/RunQuery.scala
    // scala -cp lib/dbt_scala/dbtlib.jar:. org.dbtoaster.RunQuery
    // rm -r tmp.scala org
    if (size=="big") return Map[Long,Double]( // BSP, runtime: 9.88339 (Legacy Scala's XML output)
      (0L,-6.24372635E11),  (1L,-1.3733520427E12),
      (2L,-5.35811059E11),  (3L,-2.515149258E11),
      (4L, 5.847079795E11), (5L, 1.755421056E12),
      (6L,-2.262831577E11), (7L,-4.43621451E11),
      (8L, 1.1103280205E12),(9L, 1.120289661E12)
    )
    if (size=="huge") return Map[Long,Double](
    )
    val (b,f) = (new java.io.File(path_repo+"/"+path_base),"tmp.sql"); write(b,f,sql.replaceAll("/standard/","/"+size+"/"))
    val r = exec(Array("bin/dbtoaster_release",f).toArray,b)._1.split("\n")
    new java.io.File(path_repo+"/"+path_base+"/"+f).delete;
    val m=new java.util.HashMap[Long,Double]()
    val p = java.util.regex.Pattern.compile(".*\\[([0-9]+)\\]->([\\-0-9\\.]+);.*")
    r.foreach { l => val ma=p.matcher(l); if (ma.matches) m.put(ma.group(1).toLong,ma.group(2).toDouble) }
    scala.collection.JavaConversions.mapAsScalaMap(m).toMap.filter{ case (k,v) => v!=0.0 }
  }
  def gen(size:String="standard") = run[BrokerSpread,Map[Long,Double]](Seq(
    (new java.io.FileInputStream(path_repo+"/dbtoaster/experiments/data/finance/"+size+"/finance.csv"),new Adaptor.OrderBook(),Split())
  ))._2
  
  
  def main(args:Array[String]) { // takes about 1 min
    def t(size:String) {
      val (r,g)=(ref(size),gen(size))
      try { diff(g,r) } catch { case e:Exception => scala.Console.err.println("Error with dataset "+size+": "+e.getMessage) }
      println("Ref "+size+": "+r)
      println("Gen "+size+": "+g)
    }
    t("tiny")
    t("standard")
    t("big")
    t("huge")
    /*  
    val (t,res) = run[BrokerSpread,Map[Long,Double]](Seq((new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/finance/standard/finance.csv"),new Adaptor.OrderBook(),Split())))
    val (t2,ref) = run[BrokerSpreadRef,Map[Long,Double]](Seq((new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/finance/standard/finance.csv"),new Adaptor.OrderBook(),Split())))
    println("---------------- gen:") println(K3Helper.toStr(res))
    println("---------------- vanilla:") println(K3Helper.toStr(ref))
    println("---------------- gen/vanilla diff:") diff(res, ref)
    println("---------------- actual test diff:")
    def kv(l:List[Any]) = l match { case List(v0:Long,v1:Double) => (v0,v1) }
    try { diff(res, Map[Long,Double]((6L,-55136926200L),(9L,140073076900L),(0L,78933620700L),(5L,158875988600L),(1L,-114956214400L),(4L,18596229300L),(2L,186526996800L),(7L,-27166878800L),(3L,85729885500L),(8L,92711476900L))) }
    catch { case e:Exception => println("Failed: "+e.getMessage) }
    */
  }
}

class BrokerSpread extends Actor { // Copied from generated code
  import ddbt.lib.Messages._
  import ddbt.lib.Functions._
  
  val BSP = K3Map.make[Long,Double]();
  val BSP_mBIDS1 = K3Map.make[(Long,Double),Long](List((k:(Long,Double))=>k._1));
  val BSP_mBIDS5 = K3Map.make[(Long,Double),Double](List((k:(Long,Double))=>k._1));
  
  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",tx,List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0,v1,v2,v3,v4)
    case SystemInit => onSystemReady(); t0=System.nanoTime()
    case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,BSP.toMap)
  }
  
  def onAddBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg1:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k1,v1) =>
      val y_t = k1._2;
      agg1 += (v1 * (if (bids_t > y_t) 1L else 0L));
    }
    var agg2:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k2,v2) =>
      val x_t = k2._2;
      agg2 += (v2 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg3:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k3,v3) =>
      val x_t = k3._2;
      agg3 += (v3 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg4:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k4,v4) =>
      val y_t = k4._2;
      agg4 += (v4 * (if (bids_t > y_t) 1L else 0L));
    }
    BSP.add(bids_broker_id,(((agg1 + (agg2 * -1L)) * (bids_price * bids_volume)) + (agg3 + (agg4 * -1L))));
    BSP_mBIDS1.add((bids_broker_id,bids_t),1L);
    BSP_mBIDS5.add((bids_broker_id,bids_t),(bids_volume * bids_price));
  }
  
  def onDelBIDS(bids_t:Double, bids_id:Long, bids_broker_id:Long, bids_volume:Double, bids_price:Double) {
    var agg5:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k5,v5) =>
      val y_t = k5._2;
      agg5 += (v5 * (if (bids_t > y_t) 1L else 0L));
    }
    var agg6:Long = 0;
    BSP_mBIDS1.slice(0,bids_broker_id).foreach { (k6,v6) =>
      val x_t = k6._2;
      agg6 += (v6 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg7:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k7,v7) =>
      val x_t = k7._2;
      agg7 += (v7 * (if (x_t > bids_t) 1L else 0L));
    }
    var agg8:Double = 0;
    BSP_mBIDS5.slice(0,bids_broker_id).foreach { (k8,v8) =>
      val y_t = k8._2;
      agg8 += (v8 * (if (bids_t > y_t) 1L else 0L));
    }
    BSP.add(bids_broker_id,((((agg5 * -1L) + agg6) * (bids_price * bids_volume)) + ((agg7 * -1L) + agg8)));
    BSP_mBIDS1.add((bids_broker_id,bids_t),-1L);
    BSP_mBIDS5.add((bids_broker_id,bids_t),(-1L * (bids_volume * bids_price)));
  }
  
  def onSystemReady() {
    
  }
}
