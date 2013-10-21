package ddbt.test.examples
import ddbt.lib._

import akka.actor.Actor
import java.util.Date

object BrokerSpread {
  import Helper._
  import ddbt.Utils._
  import scala.language.implicitConversions
  implicit def dateConv(d:Long):Date = new java.util.GregorianCalendar((d/10000).toInt,((d%10000)/100).toInt - 1, (d%100).toInt).getTime();
  private val sql = read(path_repo+"/"+path_base+"/test/queries/finance/brokerspread.sql")

  def ref(size:String="standard"):Map[Long,Double] = {
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
  def gen(size:String="standard") = run[BrokerSpread](Seq(
    (new java.io.FileInputStream(path_repo+"/dbtoaster/experiments/data/finance/"+size+"/finance.csv"),new Adaptor.OrderBook(),Split())
  ))._2(0)

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

  val BSP = M3Map.make[Long,Double]();
  val BSP_mBIDS1 = M3Map.make[(Long,Long),Long]((k:(Long,Long))=>k._1);
  val BSP_mBIDS5 = M3Map.make[(Long,Long),Double]((k:(Long,Long))=>k._1);

  var t0:Long = 0
  def receive = {
    case TupleEvent(TupleInsert,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onAddBIDS(v0.toLong,v1,v2,v3,v4)
    case TupleEvent(TupleDelete,"BIDS",List(v0:Double,v1:Long,v2:Long,v3:Double,v4:Double)) => onDelBIDS(v0.toLong,v1,v2,v3,v4)
    case SystemInit => t0=System.nanoTime()
    case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,List(BSP.toMap))
  }

  def bsp(bids_t:Long, broker:Long, volume:Double, price:Double):Double = {
    var agg1:Long = 0;
    var agg2:Long = 0;
    BSP_mBIDS1.foreach { (k,v) => if (k._1==broker) {
      if (bids_t > k._2) agg1 += v
      if (bids_t < k._2) agg2 += v
    }}
    var agg3:Double = 0;
    var agg4:Double = 0;
    BSP_mBIDS5.foreach { (k,v) => if (k._1==broker) {
      if (bids_t > k._2) agg4 += v
      if (bids_t < k._2) agg3 += v
    }}
    /*
    var agg1:Long = 0; BSP_mBIDS1.slice(0,broker).foreach { (k,v) => if (bids_t > k._2) agg1 += v }
    var agg2:Long = 0; BSP_mBIDS1.slice(0,broker).foreach { (k,v) => if (k._2 > bids_t) agg2 += v }
    var agg3:Double = 0; BSP_mBIDS5.slice(0,broker).foreach { (k,v) => if (k._2 > bids_t) agg3 += v }
    var agg4:Double = 0; BSP_mBIDS5.slice(0,broker).foreach { (k,v) => if (bids_t > k._2) agg4 += v }
    */
    (agg1 - agg2) * price * volume + agg3 - agg4
  }

  var tx:Long=0

  def onAddBIDS(bids_t:Long, b_id:Long, broker:Long, volume:Double, price:Double) {
    BSP.add(broker, bsp(bids_t,broker,volume,price));
    BSP_mBIDS1.add((broker,bids_t),1L);
    BSP_mBIDS5.add((broker,bids_t),(volume * price));
  }
  def onDelBIDS(bids_t:Long, b_id:Long, broker:Long, volume:Double, price:Double) {
    BSP.add(broker, -bsp(bids_t,broker,volume,price));
    BSP_mBIDS1.add((broker,bids_t),-1L);
    BSP_mBIDS5.add((broker,bids_t),-1L * (volume * price));
  }
}
