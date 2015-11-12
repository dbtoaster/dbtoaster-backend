package ddbt.lib.spark

import org.apache.spark.HashPartitioner
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext.rddToPairRDDFunctions
import org.apache.spark.rdd.RDD
import org.apache.hadoop.fs.{ Path, FileSystem }
import org.apache.hadoop.conf.Configuration
import ddbt.lib.Adaptor
import ddbt.lib.Messages._
  
class GlobalMapContext[A](
  val sc: SparkContext,
  val numPartitions: Int,
  val localContext: (Int => A)) {

  val isCheckpointingEnabled = true

  val shuffleInsertDatasets = false

  val fs = FileSystem.get(new Configuration())  
  
  val partitioner = new HashPartitioner(numPartitions)

  val rdd =
    sc.parallelize(0 until numPartitions)
      .map(x => (x, x))
      .partitionBy(partitioner)
      .mapValues(localContext)

  def init() = materialize()

  def destroy() = unmaterialize()  

  def materialize() = {
    rdd.persist(org.apache.spark.storage.StorageLevel.MEMORY_ONLY)
    sc.runJob(rdd, (iter: Iterator[_]) => {})
  }

  def unmaterialize() = rdd.unpersist(true)

  def load(queryName: String, streams: List[(String, (String, String, String, String))]): RDD[Array[(List[Any], (Long, Int))]] = {

    assert(streams.length > 0)

    val numStreams = streams.length
    val hasDeletions = (streams.head._2._4 != "insert")
    val randomizeDataset = !hasDeletions && shuffleInsertDatasets
    
    val path = streams.head._1
    val checkpointPath = 
      path.substring(0, path.lastIndexOf("/")) + "/checkpoint/" + queryName +
      (if (randomizeDataset) "_random" else "")

    val mapped: RDD[(List[Any], (Long, Int))] = 
      if (isCheckpointingEnabled && fs.exists(new Path(checkpointPath))) {
        sc.objectFile(checkpointPath)
      }
      else {
        // Load streams, assign order ids, and sort them 
        val streamRDDs = streams.zipWithIndex.map {
          case ((path, (name, schema, sep, del)), streamId) =>
            sc.textFile(path, numPartitions)
              .mapPartitionsWithIndex((pid, it) => {
                val adaptor = new Adaptor.CSV(name, schema, sep, del)
                val rnd = new scala.util.Random(pid * numStreams + streamId)
                it.toList.flatMap(s => adaptor.apply(s).map {
                  case OrderedInputEvent(ord, event) =>
                    val orderId = if (randomizeDataset) rnd.nextLong else ord.toLong
                    val tupleEvent = event.asInstanceOf[TupleEvent]
                    (orderId, streamId, tupleEvent.data :+ tupleEvent.op)
              }).iterator
            }, false)
        }                                      // List[RDD[(ord, relId, data)]]

        val unified = 
          // Datasets with deletions have orderIDs 
          if (hasDeletions || randomizeDataset) streamRDDs.reduce( _ union _) 
          else streamRDDs
                .map(_.zipWithIndex().map { case (x, t) => (t, x._2, x._3) })
                .reduce( _ union _)            // RDD[(ord, relId, data)]

        val sorted = 
          unified.sortBy(x => x._1 * numStreams + x._2, true, numPartitions)

        val zipped = sorted.zipWithIndex()    // RDD[((ord, relId, data), ind)]
                                   
        val mapped =                          // RDD[(data, (ind, relId))]
          zipped.map { case ((ord, relId, data), ind) => (data, (ind, relId)) }
    
        if (isCheckpointingEnabled) mapped.saveAsObjectFile(checkpointPath)    

        mapped
      }
                          
    val partitioned = 
      mapped.partitionBy(partitioner)
            .mapPartitions(it => Array(it.toArray).iterator, true)

    partitioned
  }
}