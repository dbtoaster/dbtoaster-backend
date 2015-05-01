package ddbt.lib.spark

import java.io.InputStream
import java.util.Properties
import org.apache.spark.SparkConf

class SparkConfig(input: InputStream) {
 
  private val prop = new Properties()
  prop.load(input)  

  val sparkMasterURL = prop.getProperty("spark.master.url")
  val sparkHomeDir = prop.getProperty("spark.home.dir")
  val sparkNumCores = prop.getProperty("spark.cores.max", null)
  val sparkNumSlaves = prop.getProperty("spark.slaves.num", "1").toInt
  val sparkNumPartitions = prop.getProperty("spark.partitions.num", "10").toInt
  val sparkExecutorMemory = prop.getProperty("spark.executor.memory")
  val sparkJars = prop.getProperty("spark.jars", "").split(":")
  val sparkTmpDir = prop.getProperty("spark.tmp.dir")
  val sparkAkkaThreads = prop.getProperty("spark.akka.threads")
  val sparkExecutorJavaOpts = prop.getProperty("spark.executor.javaopts")
  
  def sparkConf(): SparkConf = {
    val conf = new SparkConf()
      .setMaster(sparkMasterURL)    
      .setSparkHome(sparkHomeDir)
      .setJars(sparkJars)      
      .set("spark.eventLog.enabled", "true")
      .set("spark.akka.threads", "16")      
      .set("spark.akka.frameSize", "1024")
      .set("spark.serializer", "org.apache.spark.serializer.KryoSerializer")
      .set("spark.kryo.referenceTracking", "false")
      .set("spark.kryo.registrator", "ddbt.lib.spark.store.Registrator")

//      .set("spark.default.parallelism", "16")
//      .set("spark.broadcast.compress", "false")
//      .set("spark.shuffle.compress", "false")
//      .set("spark.shuffle.spill", "false")
//      .set("spark.shuffle.file.buffer.kb", "10000")
//      .set("spark.shuffle.spill.compress", "false")
//      .set("spark.rdd.compress", "false")     

    if (sparkExecutorMemory != null) conf.set("spark.executor.memory", sparkExecutorMemory)
    if (sparkNumCores != null) conf.set("spark.cores.max", sparkNumCores)
    if (sparkTmpDir != null) conf.set("spark.local.dir", sparkTmpDir)
    if (sparkAkkaThreads != null) conf.set("spark.akka.threads", sparkAkkaThreads)
    if (sparkExecutorJavaOpts != null) conf.set("spark.executor.extraJavaOptions", sparkExecutorJavaOpts)
    conf
  }
}
