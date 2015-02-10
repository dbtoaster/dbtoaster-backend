package ddbt.lib.spark.store

import com.esotericsoftware.kryo.Kryo
import com.esotericsoftware.kryo.Serializer
import com.esotericsoftware.kryo.io.Input
import com.esotericsoftware.kryo.io.Output
import org.apache.spark.serializer.KryoRegistrator
import ddbt.lib.spark.store.io.{InputStreamWrapper, OutputStreamWrapper}
import ddbt.lib.spark.Stopwatch

class Registrator extends KryoRegistrator {

  override def registerClasses(kryo: Kryo) {

    kryo.setRegistrationRequired(true)
       
    kryo.register(classOf[scala.collection.immutable.Range])
    kryo.register(classOf[scala.collection.mutable.WrappedArray$ofRef])
    kryo.register(classOf[Array[scala.collection.immutable.Map[_,_]]])
    kryo.register(classOf[scala.collection.immutable.Map$EmptyMap$])
    kryo.register(classOf[Array[Int]])
    kryo.register(classOf[Array[Double]])
    kryo.register(classOf[Array[Char]])
    kryo.register(classOf[Array[CharArray]])

    kryo.register(classOf[Array[ColumnarPartition]], new Serializer[Array[ColumnarPartition]] {
      def write(kryo: Kryo, output: Output, partitions: Array[ColumnarPartition]) = {
        Stopwatch.time("Serializer -- writing Array[ColumnarPartition]...", {
            output.writeInt(partitions.length)
            partitions.foreach { s => ColumnarPartition.write(output, s) }  
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[Array[ColumnarPartition]]) = {
        Stopwatch.time("Serializer -- reading Array[ColumnarPartition]...", {
          val length = input.readInt()
          Array.fill[ColumnarPartition](length)(ColumnarPartition.read(input))
        })
      }        
    })

    kryo.register(classOf[ColumnarPartition], new Serializer[ColumnarPartition] {
      def write(kryo: Kryo, output: Output, partition: ColumnarPartition) = {
        Stopwatch.time("Serializer -- writing ColumnarPartition...", {
          ColumnarPartition.write(output, partition)
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[ColumnarPartition]) = {
        Stopwatch.time("Serializer -- reading ColumnarPartition...", {
          ColumnarPartition.read(input)
        })
      }        
    })
  }
}
