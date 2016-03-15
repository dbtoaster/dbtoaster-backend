package ddbt.tpcc.loadtest

import java.io._
import java.sql.Connection
import java.sql.DriverManager
import java.sql.SQLException
import java.sql.Statement
import java.text.DecimalFormat
import java.util.Properties
import org.slf4j.LoggerFactory
import org.slf4j.Logger
import TpccLoad._
import TpccConstants._

object TpccLoad {

  var num_ware: Int = 0

  var fd: Int = 0

  var seed: Int = 0

  var i: Int = 0

  var option_debug: Boolean = false

  private val logger = LoggerFactory.getLogger(classOf[Tpcc])

  private val MODE = "MODE"

  private val OUTPUTDIR = "OUTPUTDIR"

  private val DRIVER = "DRIVER"

  private val WAREHOUSECOUNT = "WAREHOUSECOUNT"

  private val USER = "USER"

  private val PASSWORD = "PASSWORD"

  private val SHARDCOUNT = "SHARDCOUNT"

  private val JDBCURL = "JDBCURL"

  private val SHARDID = "SHARDID"

  private val PROPERTIESFILE = "./conf/tpcc.properties"

  def main(argv: Array[String]) {
    val sysProp = Array("os.name", "os.arch", "os.version", "java.runtime.name", "java.vm.version", "java.library.path")
    for (s <- sysProp) {
      logger.info("System Property: " + s + " = " + System.getProperty(s))
    }
    val df = new DecimalFormat("#,##0.0")
    println("maxMemory = " + 
      df.format(Runtime.getRuntime.totalMemory() / (1024.0 * 1024.0)) + 
      " MB")
    val tpccLoad = new TpccLoad()
    var ret = 0
    println("Using the ./conf/tpcc.properties file for the load configuration.")
    tpccLoad.init()
    ret = tpccLoad.runLoad(true, argv)
        
    /* We need a better condition here. We can use a library for this.
      if ((argv.length % 2) == 0) {
        println("Using the command line arguments for the load configuration.")
        ret = tpccLoad.runLoad(true, argv)
      } else {
        println("Invalid number of arguments.")
        println("Incorrect Argument: " + argv(i))
        println("The possible arguments are as follows: ")
        println("-h [database host]")
        println("-d [database name]")
        println("-u [database username]")
        println("-p [database password]")
        println("-w [number of warehouses]")
        println("-j [java driver]")
        println("-l [jdbc url]")
        println("-s [shard count]")
        println("-i [shard id]")
        System.exit(-1)
    }*/
    
    System.exit(ret)
  }
}

class TpccLoad {

  private var mode: String = _

  private var outputDir: String = _

  private var dbUser: String = null

  private var dbPassword: String = null

  private var shardCount: Int = 0

  private var jdbcUrl: String = null

  private var javaDriver: String = null

  private var shardId: Int = -1

  var particle_flg: Int = 0

  var part_no: Int = 0

  var min_ware: Long = 1

  var max_ware: Long = _

  private var properties: Properties = _

  private var inputStream: InputStream = _

  def init() {
    logger.info("Loading properties from: " + PROPERTIESFILE)
    properties = new Properties()
    inputStream = new FileInputStream(PROPERTIESFILE)
    properties.load(inputStream)
  }

  def runLoad(overridePropertiesFile: Boolean, argv: Array[String]): Int = {
    mode = properties.getProperty(MODE)
    outputDir = properties.getProperty(OUTPUTDIR)
    dbUser = properties.getProperty(USER)
    dbPassword = properties.getProperty(PASSWORD)
    num_ware = Integer.parseInt(properties.getProperty(WAREHOUSECOUNT))
    shardCount = Integer.parseInt(properties.getProperty(SHARDCOUNT))
    javaDriver = properties.getProperty(DRIVER)
    jdbcUrl = properties.getProperty(JDBCURL)
    shardId = Integer.parseInt(properties.getProperty(SHARDID))
    if (overridePropertiesFile) {      
      var i = 0
      while (i < argv.length) {
        if (argv(i) == "-m") {
          mode = argv(i + 1)
        } else if (argv(i) == "-o") {
          outputDir = argv(i + 1)
        } else if (argv(i) == "-u") {
          dbUser = argv(i + 1)
        } else if (argv(i) == "-p") {
          dbPassword = argv(i + 1)
        } else if (argv(i) == "-j") {
          javaDriver = argv(i + 1)
        } else if (argv(i) == "-l") {
          jdbcUrl = argv(i + 1)
        } else if (argv(i) == "-s") {
          shardCount = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-i") {
          shardId = Integer.parseInt(argv(i + 1))
        } else if (argv(i) == "-w") {
          num_ware = Integer.parseInt(argv(i + 1))
        } else {
          println("Incorrect Argument: " + argv(i))
          println("The possible arguments are as follows: ")
          println("-m [mode (FILE or JDBC)]")
          println("-o [file output dir]")
          println("-u [database username]")
          println("-p [database password]")
          println("-w [number of warehouses]")
          println("-j [java driver]")
          println("-l [jdbc url]")
          println("-s [shard count]")
          println("-i [shard id]")
          System.exit(-1)
        }
        i = i + 2
      }
    }
    System.out.print("*************************************\n")
    System.out.print("*** Java TPC-C Data Loader version " + Tpcc.VERSION + 
      " ***\n")
    System.out.print("*************************************\n")
    val start = System.currentTimeMillis()
    println("Execution time start: " + start)
    if (mode == null) {
      throw new RuntimeException("Mode is null.")
    }
    val jdbcMode = mode.equalsIgnoreCase("JDBC")
    if (jdbcMode) {
      if (dbUser == null) {
        throw new RuntimeException("User is null.")
      }
      if (dbPassword == null) {
        throw new RuntimeException("Password is null.")
      }
    } else if (mode.equalsIgnoreCase("FILE")) {
      if (outputDir == null) {
        throw new RuntimeException("Output dir is null.")
      }
    } else {
      throw new RuntimeException("Invalid mode '" + mode + "': must be CSV or JDBC")
    }
    if (num_ware < 1) {
      throw new RuntimeException("Warehouse count has to be greater than or equal to 1.")
    }
    if (javaDriver == null) {
      throw new RuntimeException("Java Driver is null.")
    }
    if (jdbcUrl == null) {
      throw new RuntimeException("JDBC Url is null.")
    }
    if (shardId == -1) {
      throw new RuntimeException("ShardId was not obtained")
    }
    System.out.print("<Parameters>\n")
    if (jdbcMode) {
      System.out.print("     [Driver]: %s\n".format(javaDriver))
      System.out.print("        [URL]: %s\n".format(jdbcUrl))
      System.out.print("       [user]: %s\n".format(dbUser))
      System.out.print("       [pass]: %s\n".format(dbPassword))
    } else {
      System.out.print(" [Output Dir]: %s\n".format(outputDir))
    }
    System.out.print("  [warehouse]: %d\n".format(num_ware))
    System.out.print("    [shardId]: %d\n".format(shardId))
    if (particle_flg == 1) {
      System.out.print("  [part(1-4)]: %d\n".format(part_no))
      System.out.print("     [MIN WH]: %d\n".format(min_ware))
      System.out.print("     [MAX WH]: %d\n".format(max_ware))
    }
    Util.setSeed(seed)
    val loadConfig = new TpccLoadConfig()
    if (jdbcMode) {
      Class.forName(javaDriver)
      var conn: Connection = null
      val jdbcConnectProp = new Properties()
      jdbcConnectProp.setProperty("user", dbUser)
      jdbcConnectProp.setProperty("password", dbPassword)
      jdbcConnectProp.setProperty("useServerPrepStmts", "true")
      jdbcConnectProp.setProperty("cachePrepStmts", "true")
      conn = DriverManager.getConnection(jdbcUrl, jdbcConnectProp)
      conn.setAutoCommit(false)
      var stmt: Statement = null
      stmt = conn.createStatement()
      stmt.execute("SET UNIQUE_CHECKS=0")
      stmt.execute("SET FOREIGN_KEY_CHECKS=0")
      stmt.close()
      loadConfig.setLoadType(LoadType.JDBC_STATEMENT)
      loadConfig.setConn(conn)
    } else {
      val outputDir = new File(this.outputDir)
      if (outputDir.exists()) {
        val list = outputDir.list(new FilenameFilter() {

          def accept(dir: File, name: String): Boolean = return name.endsWith(".txt")
        })
        if (list.length > 0) {
          throw new RuntimeException("All text files must be deleted from " + outputDir + " before generating data")
        }
      } else {
        if (!outputDir.mkdirs()) {
          throw new RuntimeException("Could not create dir: " + outputDir.getAbsolutePath)
        }
      }
      loadConfig.setLoadType(LoadType.CSV)
      loadConfig.setOutputDir(outputDir)
    }
    System.out.print("TPCC Data Load Started...\n")
    try {
      max_ware = num_ware
      if (particle_flg == 0) {
        System.out.print("Particle flag: %d\n".format(particle_flg))
        Load.loadItems(loadConfig, option_debug)
        Load.loadWare(loadConfig, shardCount, min_ware.toInt, max_ware.toInt, option_debug, shardId)
        Load.loadCust(loadConfig, shardCount, min_ware.toInt, max_ware.toInt, shardId)
        Load.loadOrd(loadConfig, shardCount, max_ware.toInt, shardId)
      } else if (particle_flg == 1) part_no match {
        case 1 => Load.loadItems(loadConfig, option_debug)
        case 2 => Load.loadWare(loadConfig, shardCount, min_ware.toInt, max_ware.toInt, option_debug, 
          shardId)
        case 3 => Load.loadCust(loadConfig, shardCount, min_ware.toInt, max_ware.toInt, shardId)
        case 4 => Load.loadOrd(loadConfig, shardCount, max_ware.toInt, shardId)
        case _ => 
          System.out.print("Unknown part_no\n")
          System.out.print("1:ITEMS 2:WAREHOUSE 3:CUSTOMER 4:ORDERS\n")

      }
      System.out.print("\n...DATA LOADING COMPLETED SUCCESSFULLY.\n")
    } catch {
      case e: Exception => {
        println("Error loading data")
        e.printStackTrace()
      }
    }
    val end = System.currentTimeMillis()
    val durationSeconds = ((end - start) / 1000.0).toLong
    val seconds = durationSeconds % 60
    val minutes = (durationSeconds - seconds) / 60
    val df1 = new DecimalFormat("#,##0")
    val df2 = new DecimalFormat("#,##0.000")
    println("Total execution time: " + df1.format(minutes) + " minute(s), " + 
      df1.format(seconds) + 
      " second(s) (" + 
      df2.format(durationSeconds / 60.0) +
      " minutes)")
    0
  }
}
