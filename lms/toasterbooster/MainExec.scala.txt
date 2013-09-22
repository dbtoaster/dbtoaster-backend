package toasterbooster

import org.dbtoaster.dbtoasterlib.StreamAdaptor._
import org.dbtoaster.dbtoasterlib.K3Collection._
import org.dbtoaster.dbtoasterlib.Source._
import org.dbtoaster.dbtoasterlib.DBToasterExceptions._
import org.dbtoaster.dbtoasterlib.ImplicitConversions._
import org.dbtoaster.dbtoasterlib.StdFunctions._
import org.dbtoaster.dbtoasterlib.QueryInterface._

trait DBTOptimizerQuery extends DBTQuery {
  def printMapSizes(): Unit
  def printResults(): Unit
}
  
class MainExec(q: DBTOptimizerQuery, onTupleProc: Function1[Unit,Unit], onQDone: Function[Unit,Unit]) {
  def main(args: Array[String]): Unit = {
    var counter = 0
    val logCountIdx = args.indexOf("--log-count")
    val logCount: Int =
      if (logCountIdx >= 0)
        args(logCountIdx + 1).toInt
      else
        -1

    val logMapSizes = args.contains("--log-map-sizes")

    def printProgress(i: Int) {
      val t = System.nanoTime() / 1000
      val us = t % 1000000
      val s = t / 1000000
      println(i + " tuples processed at " + s + "s+" + us + "us")
      if (logMapSizes)
        q.printMapSizes
    }

    val timeStart = System.nanoTime()

    val msgRcvr = new DBTMessageReceiver {
      def onTupleProcessed(): Unit = {
        onTupleProc();
        /*if (logCount > 0) {
          counter += 1
          if (counter % logCount == 0) {
            printProgress(counter)
          }
        }*/
      }

      def onQueryDone(): Unit = {
        onQDone();
        /*if (logCount > 0 && counter % logCount != 0)
          printProgress(counter)

        val runtime = (System.nanoTime() - timeStart) / 1000000000.0
        println("<runtime>" + runtime + "</runtime>")
        q.printResults()*/
      }
    }

    val r = new QuerySupervisor(q, msgRcvr)
    if (logCount > 0)
      printProgress(0)
    r.start
  }
}