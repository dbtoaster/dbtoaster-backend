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


    kryo.register(classOf[Array[WrapperIPA]], new Serializer[Array[WrapperIPA]] {
      def write(kryo: Kryo, output: Output, container: Array[WrapperIPA]) = {
        Stopwatch.time("Serializer -- Array[WrapperIPA]...", {
          output.writeInt(container.length)
          container.foreach { w => 
            output.writeInt(w.id)
            output.writeInt(w.pArray.length)
            w.pArray.foreach { s => ColumnarPartition.write(output, s) }
          }
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[Array[WrapperIPA]]) = {
        Stopwatch.time("Deserializer -- Array[WrapperIPA]...", {
          val length = input.readInt()
          Array.fill[WrapperIPA](length) {
            val id = input.readInt()
            val pLength = input.readInt()
            val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
            new WrapperIPA(id, pArray)
          }
        })
      }
    })

    kryo.register(classOf[Array[WrapperIDA]], new Serializer[Array[WrapperIDA]] {
      def write(kryo: Kryo, output: Output, container: Array[WrapperIDA]) = {
        Stopwatch.time("Serializer -- Array[WrapperIDA]...", {
          output.writeInt(container.length)
          container.foreach { w => 
            output.writeInt(w.id)
            output.writeInt(w.dArray.length)
            w.dArray.foreach(output.writeDouble)
          }
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[Array[WrapperIDA]]) = {
        Stopwatch.time("Deserializer -- Array[WrapperIDA]...", {
          val length = input.readInt()
          Array.fill[WrapperIDA](length) {
            val id = input.readInt()
            val dLength = input.readInt()
            val dArray = Array.fill[Double](dLength)(input.readDouble())
            new WrapperIDA(id, dArray)
          }
        })
      }
    })

    kryo.register(classOf[Array[WrapperIDAPA]], new Serializer[Array[WrapperIDAPA]] {
      def write(kryo: Kryo, output: Output, container: Array[WrapperIDAPA]) = {
        Stopwatch.time("Serializer -- Array[WrapperIDAPA]...", {
          output.writeInt(container.length)
          container.foreach { w => 
            output.writeInt(w.id)            
            output.writeInt(w.dArray.length)
            w.dArray.foreach(output.writeDouble)
            output.writeInt(w.pArray.length)
            w.pArray.foreach { s => ColumnarPartition.write(output, s) }
          }
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[Array[WrapperIDAPA]]) = {
        Stopwatch.time("Deserializer -- Array[WrapperIDAPA]...", {
          val length = input.readInt()
          Array.fill[WrapperIDAPA](length) {
            val id = input.readInt()
            val dLength = input.readInt()
            val dArray = Array.fill[Double](dLength)(input.readDouble())
            val pLength = input.readInt()
            val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
            new WrapperIDAPA(id, dArray, pArray)
          }
        })
      }
    })

    kryo.register(classOf[ColumnarPartition], new Serializer[ColumnarPartition] {
      def write(kryo: Kryo, output: Output, partition: ColumnarPartition) = {
        Stopwatch.time("Serializer -- ColumnarPartition...", {
          ColumnarPartition.write(output, partition)
        })
      }

      def read(kryo: Kryo, input: Input, t: Class[ColumnarPartition]) = {
        Stopwatch.time("Deserializer -- ColumnarPartition...", {
          ColumnarPartition.read(input)
        })
      }        
    })


    // kryo.register(classOf[Array[WrapperDA]], new Serializer[Array[WrapperDA]] {
    //   def write(kryo: Kryo, output: Output, container: Array[WrapperDA]) = {
    //     Stopwatch.time("Serializer -- Array[WrapperDA]...", {
    //       output.writeInt(container.length)
    //       container.foreach { w => 
    //         output.writeInt(w.dArray.length)
    //         w.dArray.foreach(output.writeDouble)
    //       }
    //     })
    //   }

    //   def read(kryo: Kryo, input: Input, t: Class[Array[WrapperDA]]) = {
    //     Stopwatch.time("Deserializer -- Array[WrapperDA]...", {
    //       val length = input.readInt()
    //       Array.fill[WrapperDA](length) {
    //         val dLength = input.readInt()
    //         val dArray = Array.fill[Double](dLength)(input.readDouble)
    //         new WrapperDA(dArray)
    //       }
    //     })
    //   }
    // })

    // kryo.register(classOf[Array[WrapperPA]], new Serializer[Array[WrapperPA]] {
    //   def write(kryo: Kryo, output: Output, container: Array[WrapperPA]) = {
    //     Stopwatch.time("Serializer -- Array[WrapperPA]...", {
    //       output.writeInt(container.length)
    //       container.foreach { w => 
    //         output.writeInt(w.pArray.length)
    //         w.pArray.foreach { s => ColumnarPartition.write(output, s) }
    //       }
    //     })
    //   }

    //   def read(kryo: Kryo, input: Input, t: Class[Array[WrapperPA]]) = {
    //     Stopwatch.time("Deserializer -- Array[WrapperPA]...", {
    //       val length = input.readInt()
    //       Array.fill[WrapperPA](length) {
    //         val pLength = input.readInt()
    //         val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
    //         new WrapperPA(pArray)
    //       }
    //     })
    //   }
    // })

    // kryo.register(classOf[Array[WrapperDAPA]], new Serializer[Array[WrapperDAPA]] {
    //     def write(kryo: Kryo, output: Output, container: Array[WrapperDAPA]) = {
    //       Stopwatch.time("Serializer -- Array[WrapperDAPA]...", {
    //         output.writeInt(container.length)
    //         container.foreach { w => 
    //           output.writeInt(w.dArray.length)
    //           w.dArray.foreach(output.writeDouble)
    //           output.writeInt(w.pArray.length)
    //           w.pArray.foreach { s => ColumnarPartition.write(output, s) }
    //         }
    //       })
    //     }

    //     def read(kryo: Kryo, input: Input, t: Class[Array[WrapperDAPA]]) = {
    //       Stopwatch.time("Deserializer -- Array[WrapperDAPA]...", {
    //         val length = input.readInt()
    //         Array.fill[WrapperDAPA](length) {
    //           val dLength = input.readInt()
    //           val dArray = Array.fill[Double](dLength)(input.readDouble)
    //           val pLength = input.readInt()
    //           val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
    //           new WrapperDAPA(dArray, pArray)
    //         }
    //       })
    //     }
    //   }
    // )    










    // kryo.register(
    //   classOf[Array[Tuple2[Array[Double], Array[ColumnarPartition]]]], 
    //   new Serializer[Array[Tuple2[Array[Double], Array[ColumnarPartition]]]] {

    //     def write(kryo: Kryo, output: Output, container: Array[Tuple2[Array[Double], Array[ColumnarPartition]]]) = {
    //       Stopwatch.time("Serializer -- Array[(Array[Double], Array[ColumnarPartition])]...", {
    //         output.writeInt(container.length)
    //         container.foreach { case (dArray, pArray) => 
    //           output.writeInt(dArray.length)
    //           dArray.foreach(output.writeDouble)
    //           output.writeInt(pArray.length)
    //           pArray.foreach { s => ColumnarPartition.write(output, s) }
    //         }
    //       })
    //     }

    //     def read(kryo: Kryo, input: Input, t: Class[Array[Tuple2[Array[Double], Array[ColumnarPartition]]]]) = {
    //       Stopwatch.time("Deserializer -- Array[(Array[Double], Array[ColumnarPartition])]...", {
    //         val length = input.readInt()
    //         Array.fill[Tuple2[Array[Double], Array[ColumnarPartition]]](length) {
    //           val dLength = input.readInt()
    //           val dArray = Array.fill[Double](dLength)(input.readDouble)
    //           val pLength = input.readInt()
    //           val pArray = Array.fill[ColumnarPartition](pLength)(ColumnarPartition.read(input))
    //           (dArray, pArray)
    //         }
    //       })
    //     }
    //   }
    // )    




    // kryo.register(classOf[Array[ColumnarPartition]], new Serializer[Array[ColumnarPartition]] {
    //   def write(kryo: Kryo, output: Output, partitions: Array[ColumnarPartition]) = {
    //     Stopwatch.time("Serializer -- Array[ColumnarPartition]...", {
    //         output.writeInt(partitions.length)
    //         partitions.foreach { s => ColumnarPartition.write(output, s) }
    //     })
    //   }

    //   def read(kryo: Kryo, input: Input, t: Class[Array[ColumnarPartition]]) = {
    //     Stopwatch.time("Deserializer -- Array[ColumnarPartition]...", {
    //       val length = input.readInt()
    //       Array.fill[ColumnarPartition](length)(ColumnarPartition.read(input))
    //     })
    //   }        
    // })

  }
}
