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
    val unified = streams.zipWithIndex.map {
      case ((path, (name, schema, sep, del)), ind) =>
        sc.textFile(path, numPartitions).mapPartitions(it => {
          val adaptor = new Adaptor.CSV(name, schema, sep, del)
          it.flatMap(s => adaptor.apply(s).map {
            case OrderedInputEvent(ord, event) =>
              val tupleEvent = event.asInstanceOf[TupleEvent]
              (ord, ind, tupleEvent.data :+ tupleEvent.op)
          })
        }, false)
    }.reduce( _ union _)                   // (ord, relId, data)
    val sorted = unified.sortBy(x => x._1 * 2 + x._2)
    val zipped = sorted.zipWithIndex()     // ((ord, relId, data), ind)
    val partitioned =                      // (data, (ind, relId))
      zipped.map { case ((ord, relId, data), ind) => (data, (ind, relId)) }
            .partitionBy(partitioner)
            .mapPartitions(it => Array(it.toArray).iterator, true)
    partitioned
  }
}
