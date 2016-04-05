package ddbt.lib.spark

import java.io.InputStream
import java.util.Properties
import org.apache.spark.SparkConf

class SparkConfig(input: InputStream) {
 
  private val prop = new Properties()
  prop.load(input)  

  val sparkMasterURL = prop.getProperty("spark.master.url")
  val sparkHomeDir = prop.getProperty("spark.home.dir")
  val sparkJars = prop.getProperty("spark.jars", "").split(":")

  // Optional parameters
  val sparkLocalDir = prop.getProperty("spark.local.dir")
  val sparkEventLogDir = prop.getProperty("spark.eventLog.dir")
  val sparkEventLogEnabled = prop.getProperty("spark.eventLog.enabled")
  val sparkExecutorJavaOpts = prop.getProperty("spark.executor.javaopts")

  // Runtime configuration
  val sparkNumCores = prop.getProperty("spark.cores.max")  
  val sparkExecutorMemory = prop.getProperty("spark.executor.memory")
  val sparkNumPartitions = prop.getProperty("spark.partitions.num", "0").toInt
  val distInputPath = prop.getProperty("dist.input.path")
  val logOutputPath = prop.getProperty("log.output.path")

  def sparkConf(): SparkConf = {
    val conf = new SparkConf()
      .setMaster(sparkMasterURL)    
      .setSparkHome(sparkHomeDir)
      .setJars(sparkJars)      
            
      .set("spark.akka.threads", "32")
      .set("spark.akka.frameSize", "1024")
      .set("spark.driver.cores", "2")
      .set("spark.driver.maxResultSize", "0")
      .set("spark.network.timeout", "1200s")
      
      // Kryo Serializer
      .set("spark.serializer", "org.apache.spark.serializer.KryoSerializer")
      .set("spark.kryo.referenceTracking", "false")
      .set("spark.kryo.registrator", "ddbt.lib.spark.Registrator")

//      .set("spark.default.parallelism", "16")
//      .set("spark.broadcast.compress", "false")
//      .set("spark.shuffle.compress", "false")
//      .set("spark.shuffle.spill", "false")
//      .set("spark.shuffle.file.buffer.kb", "10000")
//      .set("spark.shuffle.spill.compress", "false")
//      .set("spark.rdd.compress", "false")     
//      .set("spark.scheduler.mode", "FAIR")

      .set("spark.locality.wait", "30s")

    if (sparkEventLogEnabled != null) {
      conf.set("spark.eventLog.enabled", sparkEventLogEnabled)
      if (sparkEventLogDir != null) 
        conf.set("spark.eventLog.dir", sparkEventLogDir)  
    }

    if (sparkLocalDir != null) 
      conf.set("spark.local.dir", sparkLocalDir)    
    if (sparkExecutorJavaOpts != null) 
      conf.set("spark.executor.extraJavaOptions", sparkExecutorJavaOpts)
    if (sparkExecutorMemory != null) 
      conf.set("spark.executor.memory", sparkExecutorMemory)
    if (sparkNumCores != null) 
      conf.set("spark.cores.max", sparkNumCores)
      
    conf
  }
}
