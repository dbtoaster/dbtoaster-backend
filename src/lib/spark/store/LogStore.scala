package ddbt.lib.spark.store

import ddbt.lib.spark.store.io.{InputStreamWrapper, OutputStreamWrapper}

abstract class LogStore[E <: MapEntry] { 

  def buffers: Array[Buffer]

  def +=(e: E): Unit

  def foreach(f: E => Unit): Unit
  
  def size: Int = if (buffers != null && buffers.size > 0) buffers(0).size else -1

  def size_=(_size: Int) = buffers foreach { _.size = _size } 

  def clear(): Unit = buffers foreach { _.clear() } 
       
  def write(out: OutputStreamWrapper): Unit = buffers foreach { _.write(out) }
    
  def read(in: InputStreamWrapper): Unit = buffers foreach { _.read(in) }
}

abstract class PartitionStore[E <: MapEntry] {

  def partitions: Array[_ <: LogStore[E]] 

  def +=(e: E): Unit

  def foreach(f: E => Unit): Unit = partitions.foreach(_.foreach(f))

  def size_=(_size: Int) = partitions foreach { _.size = _size } 

  def clear(): Unit = partitions foreach { _.clear() } 
       
  def write(out: OutputStreamWrapper): Unit = partitions foreach { _.write(out) }
    
  def read(in: InputStreamWrapper): Unit = partitions foreach { _.read(in) }  
}

abstract class WritePartitionStore[E <: MapEntry] extends PartitionStore[E] {

  def +=(e: E): Unit = partitions.foreach(_ += e)
}

abstract class ReadPartitionStore[E <: MapEntry] extends PartitionStore[E] {
  
  def +=(e: E): Unit = sys.error("ReadPartitionStore does not support append ops.")
}