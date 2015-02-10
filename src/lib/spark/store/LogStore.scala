package ddbt.lib.spark.store

trait ReadStore[E <: MapEntry] { this: ColumnarStore =>
  def foreach(f: E => Unit): Unit 
  def size: Int = buffers.headOption.map(_.size).getOrElse(-1)
}

trait WriteStore[E <: MapEntry] extends ReadStore[E] { this: ColumnarStore =>
  def +=(e: E): Unit 
  def clear(): Unit = buffers foreach { _.clear() }   
  def size_=(_size: Int) = buffers foreach { _.size = _size } 
}

class ColumnarStore(val buffers: Array[Buffer])

class ColumnarPartition(val id: Int, val buffers: Array[Buffer])

object ColumnarPartition {
  import com.esotericsoftware.kryo.io.{Input, Output}

  def write(out: Output, store: ColumnarPartition) = {
    out.writeInt(store.id)
    out.writeInt(store.buffers.length)
    store.buffers foreach { b => Buffer.write(out, b) }
  }

  def read(in: Input): ColumnarPartition = {
    val id = in.readInt()
    val length = in.readInt()
    val buffers = Array.fill[Buffer](length)(Buffer.read(in))
    new ColumnarPartition(id, buffers)
  }
}

class PartitionContainer[E <: MapEntry](
    val partitions: Array[_ <: ColumnarStore with WriteStore[E]]) {
  def +=(e: E): Unit = partitions.foreach(_ += e)

  def foreach(f: E => Unit): Unit = partitions.foreach(_.foreach(f))

  def clear(): Unit = partitions foreach { _.clear() } 
}