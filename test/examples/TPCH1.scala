package ddbt.test.examples
import ddbt.lib._
import akka.actor.{Actor,ActorRef,ActorSystem,Props}
import java.util.Date;

object TPCH1 extends Helper {
  def main(args:Array[String]) {
    val (t,res) = run[TPCH1](Seq(
      (new java.io.FileInputStream("../cornell_db_maybms/dbtoaster/experiments/data/tpch/standard/lineitem.csv"),new Adaptor.CSV("LINEITEM","long,long,long,long,double,double,double,double,string,string,date,date,date,string,string,string","\\Q|\\E"),Split())
    ));
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Long) => ((v0,v1),v2) }
      diff(res(7).asInstanceOf[Map[(String,String),Long]], Map[(String,String),Long]((("N","O"),2087L),(("R","F"),1457L),(("A","F"),1478L),(("N","F"),38L))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(1).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),54006481.04),(("R","F"),36570841.24),(("A","F"),37569624.64),(("N","F"),1041301.07))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(3).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),53346924.3385250000000000000000),(("R","F"),36169060.1121930000000000000000),(("A","F"),37101416.2224240000000000000000),(("N","F"),1036450.8022800000000000000000))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(4).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),25.7910876856732151),(("R","F"),25.0590253946465340),(("A","F"),25.3545331529093369),(("N","F"),27.3947368421052632))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(0).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),53826.0000000000),(("R","F"),36511.0000000000),(("A","F"),37474.0000000000),(("N","F"),1041.0000000000))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(5).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),25877.566382367034),(("R","F"),25100.096938915580),(("A","F"),25419.231826792963),(("N","F"),27402.659736842105))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(2).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),51302903.549700000000),(("R","F"),34738472.875800000000),(("A","F"),35676192.097000000000),(("N","F"),999060.898000000000))) }
    { def kv(l:List[Any]) = l match { case List(v0:String,v1:String,v2:Double) => ((v0,v1),v2) }
      diff(res(6).asInstanceOf[Map[(String,String),Double]], Map[(String,String),Double]((("N","O"),0.05012458073790129372),(("R","F"),0.05002745367192862045),(("A","F"),0.05086603518267929635),(("N","F"),0.04289473684210526316))) }
    println("OK")
    println("Time: "+time(t))
  }
}

class TPCH1 extends Actor {
  import Messages._
  import Functions._
  import scala.language.implicitConversions
  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L

  var t0:Long = 0
  def receive = {
    case SystemInit => t0=System.nanoTime()
    case TupleEvent(TupleInsert,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) =>
      onInsertLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
      onInsertLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
      onDeleteLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case TupleEvent(TupleDelete,"LINEITEM",List(v0:Long,v1:Long,v2:Long,v3:Long,v4:Double,v5:Double,v6:Double,v7:Double,v8:String,v9:String,v10:Date,v11:Date,v12:Date,v13:String,v14:String,v15:String)) => onDeleteLINEITEM(v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
    case EndOfStream => val time = System.nanoTime()-t0; sender ! (time,List(SUM_QTY.toMap,SUM_BASE_PRICE.toMap,SUM_DISC_PRICE.toMap,SUM_CHARGE.toMap,AVG_QTY.toMap,AVG_PRICE.toMap,AVG_DISC.toMap,COUNT_ORDER.toMap))
  }

  val c1 = new java.util.GregorianCalendar(1997,9 - 1,1).getTime()
  var SUM_QTY = M3Map.make[(String,String), Double]()
  var SUM_BASE_PRICE = M3Map.make[(String,String), Double]()
  var SUM_DISC_PRICE = M3Map.make[(String,String), Double]()
  var SUM_CHARGE = M3Map.make[(String,String), Double]()
  var AVG_QTY = M3Map.make[(String,String), Double]()
  var AVG_QTY_mLINEITEM1_L3_1 = M3Map.make[(String,String), Long]()
  var AVG_QTY_mLINEITEM5 = M3Map.make[(String,String), Double]()
  var AVG_PRICE = M3Map.make[(String,String), Double]()
  var AVG_PRICE_mLINEITEM5 = M3Map.make[(String,String), Double]()
  var AVG_DISC = M3Map.make[(String,String), Double]()
  var AVG_DISC_mLINEITEM5 = M3Map.make[(String,String), Double]()
  var COUNT_ORDER = M3Map.make[(String,String), Long]()

  import scala.collection.mutable.Map

  def onInsertLINEITEM(l_orderkey: Long,l_partkey: Long,l_suppkey: Long,l_linenumber: Long,l_qty: Double,l_extprice: Double,l_discount: Double,l_tax: Double,l_rf: String,l_ls: String,l_sdate: Date,l_commitdate: Date,l_receiptdate: Date,l_shipinstruct: String,l_shipmode: String,l_comment: String) = {
    val k0 = (l_rf,l_ls)
    val c0:Long = l_sdate.getTime() <= c1.getTime()
    val q = AVG_QTY_mLINEITEM1_L3_1.get(k0);
    val dq = (0L != q) * Udiv(Ulistmax(1L,q))
    val dqc = (0L != q+c0) * Udiv(Ulistmax(1L,q+c0))

    SUM_QTY.add(k0,c0*l_qty)
    SUM_BASE_PRICE.add(k0, c0 * l_extprice)
    SUM_DISC_PRICE.add(k0, c0 * (1-l_discount) * l_extprice)
    SUM_CHARGE.add(k0, c0 * (1-l_discount) * (1L+l_tax) * l_extprice)
    AVG_QTY.add(k0, (c0 * dqc * l_qty) + (AVG_QTY_mLINEITEM5.get(k0) * (dqc-dq)))
    AVG_QTY_mLINEITEM5.add(k0, c0 * l_qty)
    AVG_PRICE.add(k0, (c0 * dqc * l_extprice) + (AVG_PRICE_mLINEITEM5.get(k0) * (dqc-dq)))
    AVG_PRICE_mLINEITEM5.add(k0, c0 * l_extprice)
    AVG_DISC.add(k0, (c0 * dqc * l_discount) + (AVG_DISC_mLINEITEM5.get(k0) * (dqc-dq)))
    AVG_QTY_mLINEITEM1_L3_1.add(k0, c0);
    AVG_DISC_mLINEITEM5.add(k0, c0 * l_discount);
    COUNT_ORDER.add(k0, c0);
  }

  def onDeleteLINEITEM(l_orderkey: Long,l_partkey: Long,l_suppkey: Long,l_linenumber: Long,l_qty: Double,l_extprice: Double,l_discount: Double,l_tax: Double,l_rf: String,l_ls: String,l_sdate: Date,l_commitdate: Date,l_receiptdate: Date,l_shipinstruct: String,l_shipmode: String,l_comment: String) = {
    val k0 = (l_rf,l_ls)
    val c0:Long = l_sdate.getTime() <= c1.getTime()
    val q = AVG_QTY_mLINEITEM1_L3_1.get(k0);
    val dqnc = (0L != q-c0) * Udiv(Ulistmax(1L,q-c0))

    SUM_QTY.add(k0, -c0 * l_qty)
    SUM_BASE_PRICE.add(k0, -c0 * l_extprice);
    SUM_DISC_PRICE.add(k0, -c0 * l_extprice * (1-l_discount))
    SUM_CHARGE.add(k0, -c0 * (1+l_tax) * l_extprice * (1-l_discount))

    AVG_QTY.add(k0,-c0 * dqnc * l_qty)
    AVG_QTY_mLINEITEM5.foreach { (k,v) =>
      val q1 = AVG_QTY_mLINEITEM1_L3_1.get(k)
      val ac1:Long = q1 + (k==k0) * -c0;
      AVG_QTY.add(k, -v * (0L != q1) * Udiv(Ulistmax(1L,q1)) +
                      v * (0L != ac1) * Udiv(Ulistmax(1L,ac1)) )
    }

    AVG_QTY_mLINEITEM5.add(k0, -c0 * l_qty);

    AVG_PRICE.add(k0, -c0 * dqnc * l_extprice)
    AVG_PRICE_mLINEITEM5.foreach{ (k,v) =>
      val q1 = AVG_QTY_mLINEITEM1_L3_1.get(k);
      val ac2:Long = q1 + ((k==k0) * -c0)
      AVG_PRICE.add(k, -v * (0L != q1) * Udiv(Ulistmax(1L,q1)) +
                       v * (0L != ac2) * Udiv(Ulistmax(1L,ac2)))
    }
    AVG_PRICE_mLINEITEM5.add(k0, -c0 * l_extprice);

    AVG_DISC.add(k0, -c0 * dqnc * l_discount)
    AVG_DISC_mLINEITEM5.foreach{ (k,v) =>
      val q1:Long = AVG_QTY_mLINEITEM1_L3_1.get(k);
      val ac3:Long = q1 + ((k==k0) * -c0);
      AVG_DISC.add(k, -v * (0L != q1) * Udiv(Ulistmax(1L,q1)) +
                       v * (0L != ac3) * Udiv(Ulistmax(1L,ac3)))
    }

    AVG_QTY_mLINEITEM1_L3_1.add(k0, -c0);
    AVG_DISC_mLINEITEM5.add(k0, -c0 * l_discount);
    COUNT_ORDER.add(k0, -c0);
  }
}
