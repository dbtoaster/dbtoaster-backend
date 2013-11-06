package ddbt.tpcc.tx

import java.io.FileInputStream
import java.io.IOException
import java.io.InputStream
import java.nio.charset.Charset
import java.text.DecimalFormat
import java.util.Properties
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import ddbt.tpcc.loadtest._
import DatabaseConnector._
import TpccInMem._
import TpccConstants._
import ddbt.tpcc.itx._
import java.sql.Connection

object TpccInMem {

  private val logger = LoggerFactory.getLogger(classOf[TpccInMem])

  private val DEBUG = logger.isDebugEnabled

  val VERSION = "1.0.1"

  private val DRIVER = "DRIVER"

  private val WAREHOUSECOUNT = "WAREHOUSECOUNT"

  private val DATABASE = "DATABASE"

  private val USER = "USER"

  private val PASSWORD = "PASSWORD"

  private val CONNECTIONS = "CONNECTIONS"

  private val RAMPUPTIME = "RAMPUPTIME"

  private val DURATION = "DURATION"

  private val JDBCURL = "JDBCURL"

  private val PROPERTIESFILE = "tpcc.properties"

  private val TRANSACTION_NAME = Array("NewOrder", "Payment", "Order Stat", "Delivery", "Slev")

  @volatile var counting_on: Boolean = false

  @volatile var activate_transaction: Int = 0

  def main(argv: Array[String]) {
    println("TPCC version " + VERSION + " Number of Arguments: " + 
      argv.length)
    val sysProp = Array("os.name", "os.arch", "os.version", "java.runtime.name", "java.vm.version", "java.library.path")
    for (s <- sysProp) {
      logger.info("System Property: " + s + " = " + System.getProperty(s))
    }
    val df = new DecimalFormat("#,##0f")
    println("maxMemory = " + 
      df.format(Runtime.getRuntime.totalMemory() / (1024.0 * 1024.0)) + 
      " MB")
    val tpcc = new TpccInMem()
    var ret = 0
    if (argv.length == 0) {
      println("Using the properties file for configuration.")
      tpcc.init()
      ret = tpcc.runBenchmark(false, argv)
    } else {
      if ((argv.length % 2) == 0) {
        println("Using the command line arguments for configuration.")
        ret = tpcc.runBenchmark(true, argv)
      } else {
        println("Invalid number of arguments.")
        println("The possible arguments are as follows: ")
        println("-h [database host]")
        println("-d [database name]")
        println("-u [database username]")
        println("-p [database password]")
        println("-w [number of warehouses]")
        println("-c [number of connections]")
        println("-r [ramp up time]")
        println("-t [duration of the benchmark (sec)]")
        println("-j [java driver]")
        println("-l [jdbc url]")
        println("-h [jdbc fetch size]")
        System.exit(-1)
      }
    }
    println("Terminating process now")
    System.exit(ret)
  }
}

class TpccInMem {

  private var javaDriver: String = _

  private var jdbcUrl: String = _

  private var dbUser: String = _

  private var dbPassword: String = _

  private var numWare: Int = _

  private var numConn: Int = _

  private var rampupTime: Int = _

  private var measureTime: Int = _

  private var fetchSize: Int = 100

  private var num_node: Int = _

  private val success = new Array[Int](TRANSACTION_COUNT)

  private val late = new Array[Int](TRANSACTION_COUNT)

  private val retry = new Array[Int](TRANSACTION_COUNT)

  private val failure = new Array[Int](TRANSACTION_COUNT)

  private var success2: Array[Array[Int]] = _

  private var late2: Array[Array[Int]] = _

  private var retry2: Array[Array[Int]] = _

  private var failure2: Array[Array[Int]] = _

  private var success2_sum: Array[Int] = new Array[Int](TRANSACTION_COUNT)

  private var late2_sum: Array[Int] = new Array[Int](TRANSACTION_COUNT)

  private var retry2_sum: Array[Int] = new Array[Int](TRANSACTION_COUNT)

  private var failure2_sum: Array[Int] = new Array[Int](TRANSACTION_COUNT)

  private var prev_s: Array[Int] = new Array[Int](5)

  private var prev_l: Array[Int] = new Array[Int](5)

  java.util.Arrays.fill(success, 0)
  java.util.Arrays.fill(late, 0)
  java.util.Arrays.fill(retry, 0)
  java.util.Arrays.fill(failure, 0)
  java.util.Arrays.fill(success2_sum, 0)
  java.util.Arrays.fill(late2_sum, 0)
  java.util.Arrays.fill(retry2_sum, 0)
  java.util.Arrays.fill(failure2_sum, 0)
  java.util.Arrays.fill(prev_s, 0)
  java.util.Arrays.fill(prev_l, 0)

  private var max_rt: Array[Float] = new Array[Float](5)

  java.util.Arrays.fill(max_rt, 0f)

  private var port: Int = 3306

  private var properties: Properties = _

  private var inputStream: InputStream = _

  def activeTransactionChecker(counter:Int) = (Tpcc.activate_transaction == 1)

  private def init() {
    logger.info("Loading properties from: " + PROPERTIESFILE)
    properties = new Properties()
    inputStream = new FileInputStream(PROPERTIESFILE)
    properties.load(inputStream)
  }

  private def runBenchmark(overridePropertiesFile: Boolean, argv: Array[String]): Int = {
    println("***************************************")
    println("****** Java TPC-C Load Generator ******")
    println("***************************************")
    RtHist.histInit()
    activate_transaction = 1
    for (i <- 0 until TRANSACTION_COUNT) {
      success(i) = 0
      late(i) = 0
      retry(i) = 0
      failure(i) = 0
      prev_s(i) = 0
      prev_l(i) = 0
      max_rt(i) = 0f
    }
    num_node = 0
    if (overridePropertiesFile) {
      var i = 0
      while (i < argv.length) {
        if (argv(i) == "-u") {
          dbUser = argv(i + 1)
        } else if (argv(i) == "-p") {
          dbPassword = argv(i + 1)
        } else if (argv(i) == "-w") {
          numWare = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-c") {
          numConn = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-r") {
          rampupTime = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-t") {
          measureTime = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-j") {
          javaDriver = argv(i + 1)
        } else if (argv(i) == "-l") {
          jdbcUrl = argv(i + 1)
        } else if (argv(i) == "-f") {
          fetchSize = Integer.parseInt(argv(i + 1))
        } else {
          println("Incorrect Argument: " + argv(i))
          println("The possible arguments are as follows: ")
          println("-h [database host]")
          println("-d [database name]")
          println("-u [database username]")
          println("-p [database password]")
          println("-w [number of warehouses]")
          println("-c [number of connections]")
          println("-r [ramp up time]")
          println("-t [duration of the benchmark (sec)]")
          println("-j [java driver]")
          println("-l [jdbc url]")
          println("-h [jdbc fetch size]")
          System.exit(-1)
        }
        i = i + 2
      }
    } else {
      dbUser = properties.getProperty(USER)
      dbPassword = properties.getProperty(PASSWORD)
      numWare = Integer.parseInt(properties.getProperty(WAREHOUSECOUNT))
      numConn = Integer.parseInt(properties.getProperty(CONNECTIONS))
      rampupTime = Integer.parseInt(properties.getProperty(RAMPUPTIME))
      measureTime = Integer.parseInt(properties.getProperty(DURATION))
      javaDriver = properties.getProperty(DRIVER)
      jdbcUrl = properties.getProperty(JDBCURL)
      val jdbcFetchSize = properties.getProperty("JDBCFETCHSIZE")
      if (jdbcFetchSize != null) {
        fetchSize = Integer.parseInt(jdbcFetchSize)
      }
    }
    if (num_node > 0) {
      if (numWare % num_node != 0) {
        logger.error(" [warehouse] value must be devided by [num_node].")
        return 1
      }
      if (numConn % num_node != 0) {
        logger.error("[connection] value must be devided by [num_node].")
        return 1
      }
    }
    if (javaDriver == null) {
      throw new RuntimeException("Java Driver is null.")
    }
    if (jdbcUrl == null) {
      throw new RuntimeException("JDBC Url is null.")
    }
    if (dbUser == null) {
      throw new RuntimeException("User is null.")
    }
    if (dbPassword == null) {
      throw new RuntimeException("Password is null.")
    }
    if (numWare < 1) {
      throw new RuntimeException("Warehouse count has to be greater than or equal to 1.")
    }
    if (numConn < 1) {
      throw new RuntimeException("Connections has to be greater than or equal to 1.")
    }
    if (rampupTime < 1) {
      throw new RuntimeException("Rampup time has to be greater than or equal to 1.")
    }
    if (measureTime < 1) {
      throw new RuntimeException("Duration has to be greater than or equal to 1.")
    }
    success2 = Array.ofDim[Int](TRANSACTION_COUNT, numConn)
    late2 = Array.ofDim[Int](TRANSACTION_COUNT, numConn)
    retry2 = Array.ofDim[Int](TRANSACTION_COUNT, numConn)
    failure2 = Array.ofDim[Int](TRANSACTION_COUNT, numConn)
    System.out.print("<Parameters>\n")
    System.out.print("     [driver]: %s\n".format(javaDriver))
    System.out.print("        [URL]: %s\n".format(jdbcUrl))
    System.out.print("       [user]: %s\n".format(dbUser))
    System.out.print("       [pass]: %s\n".format(dbPassword))
    System.out.print("  [warehouse]: %d\n".format(numWare))
    System.out.print(" [connection]: %d\n".format(numConn))
    System.out.print("     [rampup]: %d (sec.)\n".format(rampupTime))
    System.out.print("    [measure]: %d (sec.)\n".format(measureTime))
    Util.seqInit(10, 10, 1, 1, 1)
    if (DEBUG) logger.debug("Creating TpccThread")
    val executor = Executors.newFixedThreadPool(numConn, new NamedThreadFactory("tpcc-thread"))

    val SharedData: TpccTable = new TpccTable
    SharedData.loadDataIntoMaps(javaDriver,jdbcUrl,dbUser,dbPassword)

    for (i <- 0 until numConn) {
      val conn: Connection = connectToDB(javaDriver, jdbcUrl, dbUser, dbPassword)
      // val pStmts: TpccStatements = new TpccStatements(conn, fetchSize)
      // val newOrder: NewOrder = new NewOrder(pStmts)
      // val payment: Payment = new Payment(pStmts)
      // val orderStat: OrderStat = new OrderStat(pStmts)
      // val slev: Slev = new Slev(pStmts)
      // val delivery: Delivery = new Delivery(pStmts)
      val newOrder: INewOrder = new ddbt.tpcc.tx.NewOrder(SharedData)
      val payment: IPayment = new ddbt.tpcc.tx.Payment(SharedData)
      val orderStat: IOrderStatus = new ddbt.tpcc.tx.OrderStatus(SharedData)
      val slev: IStockLevel = new ddbt.tpcc.tx.StockLevel(SharedData)
      val delivery: IDelivery = new ddbt.tpcc.tx.Delivery(SharedData)

      val worker = new TpccThread(i, port, 1, dbUser, dbPassword, numWare, numConn, javaDriver, jdbcUrl, 
        fetchSize, success, late, retry, failure, success2, late2, retry2, failure2, conn, newOrder, payment, orderStat, slev, delivery, activeTransactionChecker)
      executor.execute(worker)
    }
    if (rampupTime > 0) {
      System.out.print("\nRAMPUP START.\n\n")
      try {
        Thread.sleep(rampupTime * 1000)
      } catch {
        case e: InterruptedException => logger.error("Rampup wait interrupted", e)
      }
      System.out.print("\nRAMPUP END.\n\n")
    }
    System.out.print("\nMEASURING START.\n\n")
    counting_on = true
    val startTime = System.currentTimeMillis()
    val df = new DecimalFormat("#,##0f")
    var runTime = 0L
    while ({(runTime = System.currentTimeMillis() - startTime); runTime} < measureTime * 1000) {
      println("Current execution time lapse: " + df.format(runTime / 1000f) + 
        " seconds")
      try {
        Thread.sleep(1000)
      } catch {
        case e: InterruptedException => logger.error("Sleep interrupted", e)
      }
    }
    val actualTestTime = System.currentTimeMillis() - startTime
    println("---------------------------------------------------")
    println("<Raw Results>")
    for (i <- 0 until TRANSACTION_COUNT) {
      System.out.print("  |%s| sc:%d  lt:%d  rt:%d  fl:%d \n".format(TRANSACTION_NAME(i), success(i), late(i), 
        retry(i), failure(i)))
    }
    System.out.print(" in %f sec.\n".format(actualTestTime / 1000f))
    println("<Raw Results2(sum ver.)>")
    for (i <- 0 until TRANSACTION_COUNT) {
      success2_sum(i) = 0
      late2_sum(i) = 0
      retry2_sum(i) = 0
      failure2_sum(i) = 0
      for (k <- 0 until numConn) {
        success2_sum(i) += success2(i)(k)
        late2_sum(i) += late2(i)(k)
        retry2_sum(i) += retry2(i)(k)
        failure2_sum(i) += failure2(i)(k)
      }
    }
    for (i <- 0 until TRANSACTION_COUNT) {
      System.out.print("  |%s| sc:%d  lt:%d  rt:%d  fl:%d \n".format(TRANSACTION_NAME(i), success2_sum(i), 
        late2_sum(i), retry2_sum(i), failure2_sum(i)))
    }
    println("<Constraint Check> (all must be [OK])\n [transaction percentage]")
    var j = 0
    var i: Int = 0
    i = 0
    while (i < TRANSACTION_COUNT) {
      j += (success(i) + late(i))
      i += 1
    }
    var f = 100f * (success(1) + late(1)).toFloat / j.toFloat
    System.out.print("        Payment: %f%% (>=43.0%%)".format(f))
    if (f >= 43.0) {
      System.out.print(" [OK]\n")
    } else {
      System.out.print(" [NG] *\n")
    }
    f = 100f * (success(2) + late(2)).toFloat / j.toFloat
    System.out.print("   Order-Status: %f%% (>= 4.0%%)".format(f))
    if (f >= 4.0) {
      System.out.print(" [OK]\n")
    } else {
      System.out.print(" [NG] *\n")
    }
    f = 100f * (success(3) + late(3)).toFloat / j.toFloat
    System.out.print("       Delivery: %f%% (>= 4.0%%)".format(f))
    if (f >= 4.0) {
      System.out.print(" [OK]\n")
    } else {
      System.out.print(" [NG] *\n")
    }
    f = 100f * (success(4) + late(4)).toFloat / j.toFloat
    System.out.print("    Stock-Level: %f%% (>= 4.0%%)".format(f))
    if (f >= 4.0) {
      System.out.print(" [OK]\n")
    } else {
      System.out.print(" [NG] *\n")
    }
    System.out.print(" [response time (at least 90%% passed)]\n")
    for (n <- 0 until TRANSACTION_NAME.length) {
      f = 100f * success(n).toFloat / (success(n) + late(n)).toFloat
      if (DEBUG) logger.debug("f: " + f + " success[" + n + "]: " + success(n) + " late[" + 
        n + 
        "]: " + 
        late(n))
      System.out.print("      %s: %f%% ".format(TRANSACTION_NAME(n), f))
      if (f >= 90f) {
        System.out.print(" [OK]\n")
      } else {
        System.out.print(" [NG] *\n")
      }
    }
    var total = 0f
    j = 0
    while (j < TRANSACTION_COUNT) {
      total = total + success(j) + late(j)
      println(" " + TRANSACTION_NAME(j) + " Total: " + (success(j) + late(j)))
      j += 1
    }
    val tpcm = (success(0) + late(0)) * 60000f / actualTestTime
    println()
    println("<TpmC>")
    println(tpcm + " TpmC")
    System.out.print("\nSTOPPING THREADS\n")
    activate_transaction = 0

    {
      try {
        Thread.sleep(5000)
      } catch {
        case e: InterruptedException => logger.error("Sleep interrupted", e)
      }
      val newData = new TpccTable
      newData.loadDataIntoMaps(javaDriver,jdbcUrl,dbUser,dbPassword)

      if(newData equals SharedData) {
        println("\n2- new Data equals SharedData")
      } else {
        println("\n2- new Data is not equal to SharedData")
      }
    }

    executor.shutdown()
    try {
      executor.awaitTermination(30, TimeUnit.SECONDS)
    } catch {
      case e: InterruptedException => println("Timed out waiting for executor to terminate")
    }
    0
  }
}
