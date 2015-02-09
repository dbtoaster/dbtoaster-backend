package ddbt.lib.spark

import scala.collection.mutable.ArrayBuffer
import scala.reflect.ClassTag

import org.apache.spark.HashPartitioner
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext.rddToPairRDDFunctions

import ddbt.lib.spark.store.Index
import ddbt.lib.spark.store.MapEntry
import ddbt.lib.spark.store.Store
  
abstract class LocalMapContext {
  
//   class LocalMap[E <: MapEntry: ClassTag](
//     val name: String,
//     val indices: Vector[Index[E]],
//     val topLevel: Boolean) {

//     val store = new Store[E](indices)

//     def print(): Unit = {
//       println("NAME: %s  TL: %s".format(name, topLevel))
//       store foreach (e => println("  %s".format(e)))
//     }
    
//     def collect(): (String, Seq[E]) = {
//       val entries = new ArrayBuffer[E](store.size)
//       store foreach (entries += _)
//       (name, entries)
//     }
//   }

//   private val maps = new ArrayBuffer[LocalMap[_]]()
  
//   protected def createMap[E <: MapEntry: ClassTag](
//       name: String, 
//       indices: Vector[Index[E]], 
//       topLevel: Boolean = false) = {
//     val map = new LocalMap[E](name, indices, topLevel)
//     maps += map
//     map
//   }
  
//   def printMaps(): Unit = maps foreach { _.print }

//   def printTopLevelMaps(): Unit = maps filter { _.topLevel } map { _.print }
}

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

  // def printMaps() = rdd foreach { _._2.printMaps() }

  // def printTopLevelMaps() = rdd foreach { _._2.printTopLevelMaps() }
}
