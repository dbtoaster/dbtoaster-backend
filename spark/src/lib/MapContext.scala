package ddbt.lib.spark

import org.apache.spark.HashPartitioner
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext.rddToPairRDDFunctions
import org.apache.spark.rdd.RDD
import ddbt.lib.Adaptor
import ddbt.lib.Messages._
  
class GlobalMapContext[A](
  val sc: SparkContext,
  val numPartitions: Int,
  val localContext: (Int => A)) {

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

  def load(streams: List[(String, (String, String, String, String))]): RDD[Array[(List[Any], (Long, Int))]] = {
    val numStreams = streams.length
    val hasDeletions = streams.headOption.map(_._2._4 != "insert").getOrElse(false)

    val streamRDDs = streams.zipWithIndex.map {
      case ((path, (name, schema, sep, del)), ind) =>
        sc.textFile(path, numPartitions).mapPartitions(it => {
          val adaptor = new Adaptor.CSV(name, schema, sep, del)
          it.toList.flatMap(s => adaptor.apply(s).map {
            case OrderedInputEvent(ord, event) =>
              val tupleEvent = event.asInstanceOf[TupleEvent]
              (ord.toLong, ind, tupleEvent.data :+ tupleEvent.op)
          }).iterator
        }, false)
    }                                      // List[RDD[(ord, relId, data)]]

    val unified = 
      // Datasets with deletions have orderIDs 
      if (hasDeletions) streamRDDs.reduce( _ union _) 
      else streamRDDs
            .map(_.zipWithIndex().map { case (x, t) => (t, x._2, x._3) })
            .reduce( _ union _)            // RDD[(ord, relId, data)]

    val sorted = unified.sortBy(x => x._1 * numStreams + x._2, true, numPartitions

    val zipped = sorted.zipWithIndex()     // RDD[((ord, relId, data), ind)]
    val partitioned =                      // RDD[(data, (ind, relId))]
      zipped.map { case ((ord, relId, data), ind) => (data, (ind, relId)) }
            .partitionBy(partitioner)
            .mapPartitions(it => Array(it.toArray).iterator, true)
    partitioned
  }
}
