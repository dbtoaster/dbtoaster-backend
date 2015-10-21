package ddbt.lib.spark

import ddbt.lib.spark.store.{ ColumnarPartition, StoreWrapper }
import org.apache.spark.serializer.KryoRegistrator
import com.esotericsoftware.kryo.Kryo
import com.esotericsoftware.kryo.Serializer
import com.esotericsoftware.kryo.io.Input
import com.esotericsoftware.kryo.io.Output

class Registrator extends KryoRegistrator {

  override def registerClasses(kryo: Kryo) {

    kryo.setRegistrationRequired(true)
       
    kryo.register(classOf[scala.collection.immutable.Range])
    kryo.register(classOf[scala.collection.mutable.WrappedArray$ofRef])
    kryo.register(classOf[Array[scala.collection.immutable.Map[_,_]]])
    kryo.register(classOf[scala.collection.immutable.Map$EmptyMap$])

    kryo.register(classOf[Array[scala.Tuple3[_,_,_]]])
    kryo.register(classOf[Array[Int]])
    kryo.register(classOf[scala.reflect.ClassTag$$anon$1])
    kryo.register(classOf[java.lang.Class[_]])
    kryo.register(classOf[scala.collection.immutable.$colon$colon[_]])
    // NOTICE: Uncomment the following line after successfully compiling the spark subproject
    //kryo.register(classOf[scala.collection.immutable.Nil$])


    kryo.register(classOf[Array[StoreWrapper]], new Serializer[Array[StoreWrapper]] {
      def write(kryo: Kryo, output: Output, container: Array[StoreWrapper]) = {
        // Stopwatch.time("Serializer -- Array[StoreWrapper]...", {
          output.writeInt(container.length)
          container.foreach { w => 
            output.writeInt(w.id)
            output.writeInt(w.lArray.length)
            w.lArray.foreach(output.writeLong)
            output.writeInt(w.dArray.length)
            w.dArray.foreach(output.writeDouble)
            output.writeInt(w.pArray.length)
            w.pArray.foreach { s => ColumnarPartition.write(output, s) }
          }
        // })
      }

      def read(kryo: Kryo, input: Input, t: Class[Array[StoreWrapper]]) = {
        // Stopwatch.time("Deserializer -- Array[StoreWrapper]...", {
          val length = input.readInt()
          Array.fill[StoreWrapper](length) {
            val id = input.readInt()
            val lLength = input.readInt()
            val lArray = Array.fill[Long](lLength)(input.readLong())
            val dLength = input.readInt()
            val dArray = Array.fill[Double](dLength)(input.readDouble())
            val pLength = input.readInt()
            val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
            new StoreWrapper(id, lArray, dArray, pArray)
          }
        // })
      }
    })


    kryo.register(classOf[ColumnarPartition], new Serializer[ColumnarPartition] {
      def write(kryo: Kryo, output: Output, partition: ColumnarPartition) = {
        // Stopwatch.time("Serializer -- ColumnarPartition...", {
          ColumnarPartition.write(output, partition)
        // })
      }

      def read(kryo: Kryo, input: Input, t: Class[ColumnarPartition]) = {
        // Stopwatch.time("Deserializer -- ColumnarPartition...", {
          ColumnarPartition.read(input)
        // })
      }        
    })        
  }  
}
