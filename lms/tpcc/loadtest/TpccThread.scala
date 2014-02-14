package ddbt.tpcc.loadtest

import java.io.File
import java.io.FileInputStream
import java.io.IOException
import java.sql.Connection
import java.sql.DriverManager
import java.sql.SQLException
import java.text.DecimalFormat
import java.util.Map
import java.util.Properties
import java.util.Set
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import TpccThread._
import scala.collection.JavaConversions._
import ddbt.tpcc.itx._

object TpccThread {

  private val logger = LoggerFactory.getLogger(classOf[TpccThread])

  private val DEBUG = logger.isDebugEnabled
}

class TpccThread(val number: Int, 
    val port: Int, 
    val is_local: Int, 
    val db_user: String, 
    val db_password: String, 
    val num_ware: Int, 
    val num_conn: Int, 
    val driverClassName: String, 
    val jdbcUrl: String, 
    val fetchSize: Int, 
    val success: Array[Int], 
    val late: Array[Int], 
    val retry: Array[Int], 
    val failure: Array[Int], 
    val success2: Array[Array[Int]], 
    val late2: Array[Array[Int]], 
    val retry2: Array[Array[Int]], 
    val failure2: Array[Array[Int]],
    var conn: Connection,
    val newOrder: INewOrder,
    val payment: IPayment,
    val orderStat: IOrderStatus,
    val slev: IStockLevel,
    val delivery: IDelivery,
    loopConditionChecker: (Int => Boolean)) extends Thread /*with DatabaseConnector*/{

  /**
   * Dedicated JDBC connection for this thread.
   */
  // var conn: Connection = connectToDatabase

  var driver: Driver = new Driver(conn, fetchSize, success, late, retry, failure, success2, late2, retry2, 
    failure2, newOrder, payment, orderStat, slev, delivery)

  override def run() {
    try {
      if (DEBUG) {
        logger.debug("Starting driver with: number: " + number + " num_ware: " + 
          num_ware + 
          " num_conn: " + 
          num_conn)
      }
      driver.runTransaction(number, num_ware, num_conn, loopConditionChecker)
    } catch {
      case e: Throwable => logger.error("Unhandled exception", e)
    }
  }

  // private def connectToDatabase:Connection = connectToDB(driverClassName, jdbcUrl, db_user, db_password)
}
