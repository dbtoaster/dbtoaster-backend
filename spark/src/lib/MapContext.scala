package ddbt.lib.spark

import org.apache.spark.HashPartitioner
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext.rddToPairRDDFunctions
import org.apache.spark.rdd.RDD
import org.apache.hadoop.fs.{ Path, FileSystem }
import org.apache.hadoop.conf.Configuration
import ddbt.lib.Adaptor
import ddbt.lib.Messages._

object GlobalMapContext 
{
  val QUICK_LOAD_OF_INSERT_STREAMS = true

  def uniformBatchSizes(relationSizes: Array[Long], batchSize: Long): Array[Array[Long]] =
  {
    val numBatches = Math.ceil(relationSizes.sum / batchSize.toDouble).toInt
    Array.tabulate(relationSizes.size)(i => {
      val overflow = relationSizes(i) % numBatches
      val a = Array.fill[Long](numBatches) { relationSizes(i) / numBatches }
      a(numBatches - 1) += overflow
      a
    })
  }

  def linearBatchSizes(relationSizes: Array[Long], batchSize: Long): Array[Array[Long]] =
  {
    assert(relationSizes.size <= batchSize)

    // Sorted input sizes
    var input = relationSizes.sorted
    // Allocate output batch sizes
    val output = Array.fill(input.size){ new collection.mutable.ArrayBuffer[Long](16) }

    var lastBeat = 0L
    var currBeat = 0L

    while (input.size > 0) 
    {
      var remaining = batchSize

      while (remaining > 0 && input.size > 0)
      {
        val available = (input.head - currBeat) * input.size
        if (available >= remaining)
        {
          currBeat = currBeat + (remaining - 1) / input.size + 1
          remaining = 0
        }
        else 
        {
          currBeat = input.head
          remaining = remaining - available
          input = input.tail
        }
      }

      for (j <- 0 until relationSizes.size)
      {
        output(j) += (if (lastBeat >= relationSizes(j)) 0
          else if (currBeat <= relationSizes(j)) currBeat - lastBeat
          else relationSizes(j) - lastBeat)
      }
      lastBeat = currBeat
    }

    output.map(_.toArray)
  }

  def split[T](xs: Array[T], ns: List[Int]): List[Array[T]] = ns match {
    case Nil => Nil
    case hd :: tl => (xs take hd) :: split(xs drop hd, tl)
  }

  def chop[T](xs: Array[T], weights: Array[Long]): List[Array[T]] = {
    val sum = weights.sum
    val chunkSz = weights.map(w => Math.ceil(w.toDouble / sum * xs.size).toInt)
    split(xs, chunkSz.toList)
  }
}
  
class GlobalMapContext[A](
  val sc: SparkContext,
  val numPartitions: Int,
  val localContext: (Int => A)) {

  val isCheckpointingEnabled = true

  val shuffleInsertDatasets = true

  val fs = FileSystem.get(new Configuration())  
  
  val partitioner = new HashPartitioner(numPartitions)

  val rdd =
    sc.parallelize(0 until numPartitions, numPartitions)
      .map(x => (x, x))
      .partitionBy(partitioner)
      .mapValues(localContext)

  def init() = materialize()

  def destroy() = unmaterialize()  

  def materialize() = {
    rdd.persist(org.apache.spark.storage.StorageLevel.MEMORY_ONLY)
    rdd.count
  }

  def unmaterialize() = rdd.unpersist(true)

  def loadStreams(queryName: String, streams: List[(String, (String, String, String, String))]): RDD[Array[(List[Any], (Long, Int))]] = {

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

  def loadInsertStreams(streams: Array[(String, (String, String, String, String))]): Array[RDD[List[Any]]] = {
    assert(streams.head._2._4 == "insert")

    streams.zipWithIndex.map {
      case ((path, (name, schema, sep, del)), streamId) =>
        sc.textFile(path, numPartitions)
          .repartition(numPartitions)
          .mapPartitions(it => {
            val adaptor = new Adaptor.CSV(name, schema, sep, del)
            it.flatMap(s => adaptor.apply(s).map {
              case OrderedInputEvent(ord, TupleEvent(op, stream, data)) => data })
          }, true)
    }                         
  }
}
