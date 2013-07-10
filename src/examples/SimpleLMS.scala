package examples

import java.io._
import ddbt.lib.{K3Map,K3Var}
import org.dbtoaster.dbtoasterlib.Source._
import org.dbtoaster.dbtoasterlib.StreamAdaptor._
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._

import scala.actors.Actor
import scala.actors.Actor._

trait DBTMessageReceiver {
  def onTupleProcessed(): Unit
  def onQueryDone(): Unit
}
case object DBTTupleProcessed
case object DBTDone

class QuerySupervisor(query: DBTQuery, msgRcv: DBTMessageReceiver) extends Actor {
  def act() {
    query.setSupervisor(this)
    query.start
    while(true) {
      receive {
        case DBTDone => msgRcv.onQueryDone(); exit()
        case DBTTupleProcessed => msgRcv.onTupleProcessed()
      }
    }
  }
}

trait DBTQuery extends Actor {
  def setSupervisor(supervisor: Actor): Unit
}

trait DBTOptimizerQuery extends DBTQuery {
  def printMapSizes(): Unit
  def printResults(): Unit
}

/*
 * - LMS code generated
 * - new data structures
 * - legacy streaming
 */
object SimpleLMS {
  val onTupleProc = (u:Unit)=>{}
  val onQDone = (u:Unit)=>{}
  val q = new Query("resources/data/finance-huge.csv")

  def main(args: Array[String]): Unit = {
    var counter = 0
    val logCountIdx = args.indexOf("--log-count")
    val logCount: Int = if (logCountIdx >= 0) args(logCountIdx + 1).toInt else -1
    val logMapSizes = args.contains("--log-map-sizes")

    def printProgress(i: Int) {
      val t = System.nanoTime() / 1000
      val us = t % 1000000
      val s = t / 1000000
      println(i + " tuples processed at " + s + "s+" + us + "us")
      if (logMapSizes) q.printMapSizes
    }

    val timeStart = System.nanoTime()

    val msgRcvr = new DBTMessageReceiver {
      def onTupleProcessed(): Unit = {
        onTupleProc();
        if (logCount > 0) {
          counter += 1
          if (counter % logCount == 0) printProgress(counter)
        }
      }
      def onQueryDone(): Unit = {
        onQDone();
        if (logCount > 0 && counter % logCount != 0) printProgress(counter)
        val runtime = (System.nanoTime() - timeStart) / 1000000000.0
        println("<runtime>" + runtime + "</runtime>")
        q.printResults()
      }
    }

    val r = new QuerySupervisor(q, msgRcvr)
    if (logCount > 0) printProgress(0)
    r.start
  }
}

class Query(val input: String) extends DBTOptimizerQuery {
    var supervisor: Actor = null;
    def setSupervisor(supervisor: Actor) = this.supervisor = supervisor;

    val s1 = createInputStreamSource(new FileReader(input), List(
               createAdaptor("orderbook", "BIDS", List(("book", "bids"),("brokers", "10"),("deterministic", "yes"))),
               createAdaptor("orderbook", "ASKS", List(("book", "asks"),("brokers", "10"),("deterministic", "yes")))
             ), Delimited("\n"));
    val sources = new SourceMultiplexer(this, List(s1));

    /*
    val COUNT = new K3PersistentCollection[(Long), Long]("COUNT", Map(), None); // out
    val COUNT_mASKS2 = SimpleVal[Long]("COUNT_mASKS2", 0);
    val COUNT_mBIDS2 = SimpleVal[Long]("COUNT_mBIDS2", 0);
    */
    val COUNT = new K3Map[Long,Long](0); // out
    val COUNT_mASKS2 = K3Var[Long](0);
    val COUNT_mBIDS2 = K3Var[Long](0);
/*
Original result: 
<COUNT>
  <item>
    <__a0>1</__a0>
    <__av>270</__av>
  </item>
</COUNT>
*/

    def onInsertBIDS(COUNT4: Double, COUNT5: Long, COUNT6: Long, COUNT7: Double, COUNT8: Double): Unit = {
      val x8 = (1L, 1L)
      val x9 = List(x8)
      val COUNT_mASKS25 = COUNT_mBIDS2.get
      x9.foreach { COUNT_mASKS22 =>
            val COUNT_mASKS23 = COUNT_mASKS22._1
            val COUNT_mASKS24 = COUNT_mASKS22._2
            val COUNT_mASKS26 = COUNT_mASKS24 * COUNT_mASKS25
            val COUNT_mASKS28 = COUNT.get(COUNT_mASKS23)!=0L
            val COUNT_mBIDS20 = if (COUNT_mASKS28) COUNT.get(COUNT_mASKS23) else 0L
            val COUNT_mBIDS21 = COUNT_mBIDS20 + COUNT_mASKS26
            COUNT.set(COUNT_mASKS23, COUNT_mBIDS21)
      }
      val COUNT_mBIDS25 = COUNT_mASKS2.get
      val COUNT_mBIDS26 = COUNT_mBIDS25 + 1L
      COUNT_mASKS2.set(COUNT_mBIDS26)
   }

    def onDeleteBIDS(COUNT_mBIDS29: Double, x80: Long, x81: Long, x82: Double, x83: Double) {
      val x8 = (1L, 1L)
      val x9 = List(x8)
      val x90 = COUNT_mBIDS2.get
      x9.foreach { x87 =>
            val x88 = x87._1
            val x89 = x87._2
            val x91 = x89 * x90
            val x93 = x91 * -1L
            val x95 = COUNT.get(x88)!=0L
            val x97 = if (x95) COUNT.get(x88) else 0L
            val x98 = x97 + x93
            COUNT.set(x88, x98)
      }
      val x102 = COUNT_mASKS2.get
      val x103 = x102 + -1L
      COUNT_mASKS2.set(x103)
   }

    def onInsertASKS(x0: Double, x1: Long, x2: Long, x3: Double, x4: Double) {
      val x8 = (1L, 1L)
      val x9 = List(x8)
      val x13 = COUNT_mASKS2.get
      x9.foreach { x10 =>
            val x11 = x10._1
            val x12 = x10._2
            val x14 = x12 * x13
            val x16 = COUNT.get(x11)!=0L
            val x18 = if (x16) COUNT.get(x11) else 0L
            val x19 = x18 + x14
            COUNT.set(x11, x19)
      }
      val x23 = COUNT_mBIDS2.get
      val x24 = x23 + 1L
      COUNT_mBIDS2.set(x24)
   }

   // --------------------------------------------------------------------------
    def onDeleteASKS(x27: Double, x28: Long, x29: Long, x30: Double, x31: Double) {
      val x8 = (1L, 1L)
      val x9 = List(x8)
      val x38 = COUNT_mASKS2.get
      x9.foreach { x35 =>
            val x36 = x35._1
            val x37 = x35._2
            val x39 = x37 * x38
            val x41 = x39 * -1L
            val x43 = COUNT.get(x36)!=0L
            val x45 = if (x43) COUNT.get(x36) else 0L
            val x46 = x45 + x41
            COUNT.set(x36, x46)
      }
      val COUNT0 = COUNT_mBIDS2.get
      val COUNT1 = COUNT0 + -1L
      COUNT_mBIDS2.set(COUNT1)
   }
   // --------------------------------------------------------------------------

    def getCOUNT = COUNT;
    def onSystemInitialized() = {}
    def fillTables(): Unit = {}

    def dispatcher(event: DBTEvent): Unit = {
      event match {
        case StreamEvent(InsertTuple, o, "BIDS",List(vBIDS_T: Double, vBIDS_ID: Long, vBIDS_BROKER_ID: Long, vBIDS_VOLUME: Double, vBIDS_PRICE: Double)) => onInsertBIDS(vBIDS_T, vBIDS_ID, vBIDS_BROKER_ID, vBIDS_VOLUME, vBIDS_PRICE);
        case StreamEvent(DeleteTuple, o, "BIDS",List(vBIDS_T: Double, vBIDS_ID: Long, vBIDS_BROKER_ID: Long, vBIDS_VOLUME: Double, vBIDS_PRICE: Double)) => onDeleteBIDS(vBIDS_T, vBIDS_ID, vBIDS_BROKER_ID, vBIDS_VOLUME, vBIDS_PRICE);
        case StreamEvent(InsertTuple, o, "ASKS",List(vASKS_T: Double, vASKS_ID: Long, vASKS_BROKER_ID: Long, vASKS_VOLUME: Double, vASKS_PRICE: Double)) => onInsertASKS(vASKS_T, vASKS_ID, vASKS_BROKER_ID, vASKS_VOLUME, vASKS_PRICE);
        case StreamEvent(DeleteTuple, o, "ASKS",List(vASKS_T: Double, vASKS_ID: Long, vASKS_BROKER_ID: Long, vASKS_VOLUME: Double, vASKS_PRICE: Double)) => onDeleteASKS(vASKS_T, vASKS_ID, vASKS_BROKER_ID, vASKS_VOLUME, vASKS_PRICE);
        case StreamEvent(SystemInitialized, o, "", Nil) => onSystemInitialized()
        case EndOfStream => ()
        case _ => throw DBTFatalError("Event could not be dispatched: " + event)
      }
      supervisor ! DBTTupleProcessed;
    }

    def act() {
      fillTables();
      onSystemInitialized();
      sources.start;
      while(true) {
        receive {
          case EndOfStream => supervisor ! DBTDone; exit();
          case e: DBTEvent => dispatcher(e) 
        }
      }
    }

    def toXML[K,V](m:K3Map[K,V]): List[xml.Elem] = {
      val ft = new java.text.SimpleDateFormat("yyyyMMdd")
      def valToStr(v: Any): String = v match {
        case d:java.util.Date => ft.format(d)
        case x => x.toString
      }
      var l = List[xml.Elem]()
      m.foreach{case (k,v) => 
        val key = try {
            (k.asInstanceOf[Product].productIterator.foldLeft((0,List[xml.Elem]())) { 
                  case ((i,l), k) => (i+1, <xml>{ valToStr(k) }</xml>.copy(label=("__a" + i)) :: l)
            })._2.reverse
          } catch { case e:java.lang.ClassCastException => <__a0>{ valToStr(k) }</__a0> }
        l = <item>{ key }<__av>{ valToStr(v) }</__av></item> :: l
      }
      l
    }

    def printResults {
      val pp = new xml.PrettyPrinter(8000, 2);
      println(pp.format(<COUNT>{ toXML(getCOUNT) }</COUNT>));
    }
    def printMapSizes {
      println("COUNT : "+COUNT.size);
      /*
      COUNT.printSize;
      COUNT_mASKS2.printSize;
      COUNT_mBIDS2.printSize;
      */
    }
}
