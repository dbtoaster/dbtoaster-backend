package ddbt.lib.spark.store

import ddbt.lib.spark.store.io.{InputStreamWrapper, OutputStreamWrapper}

abstract sealed class Buffer extends Serializable {

  var position: Int = 0         // public to make inlining possible
  
  def ensureSize(n: Int): Unit

  def clear(): Unit = position = 0
  
  def size = position

  def size_=(n: Int) = {
    ensureSize(n)
    position = n
  }
}

final class IntBuffer(val initialSize: Int) extends Buffer {   
  var buffer = new Array[Int](Math.max(initialSize, 1))

  def write(out: OutputStreamWrapper): Unit = {
    val byteBuffer = new Array[Byte](4)
    var i = 0    
    while (i < position) {
       ByteUtils.intToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 4)
       i += 1
    }
  }

  def read(in: InputStreamWrapper): Unit = {
    val byteBuffer = new Array[Byte](4)
    var i = 0    
    while (i < position) {
       in.readBytes(byteBuffer, 0, 4)
       buffer(i) = ByteUtils.bytesToInt(byteBuffer, 0)
       i += 1
    }
  }
   
  @inline
  def ensureSize(n: Int): Unit = {
    val bufferLength: Long = buffer.length
    if (n > bufferLength) {
      var newSize: Long = bufferLength * 2
      while (n > newSize) newSize = newSize * 2
      // Clamp newSize to Int.MaxValue
      if (newSize > Int.MaxValue) newSize = Int.MaxValue
      val newBuffer = new Array[Int](newSize.toInt)
      scala.compat.Platform.arraycopy(buffer, 0, newBuffer, 0, position)
      buffer = newBuffer
    }
  }

  @inline
  def +=(elem: Int): Unit = {
    ensureSize(position + 1)
    buffer(position) = elem
    position += 1
  }

  @inline
  def +=(elem: Long): Unit = {
    ensureSize(position + 1)
    buffer(position) = elem.toInt
    position += 1
  }

  @inline
  def apply(idx: Int): Int = {
    if (idx >= position) throw new IndexOutOfBoundsException(idx.toString)
    buffer(idx)
  }   
} 

final class DoubleBuffer(val initialSize: Int) extends Buffer { 
  var buffer = new Array[Double](Math.max(initialSize, 1))
   
  def write(out: OutputStreamWrapper): Unit = {
  	val byteBuffer = new Array[Byte](8)
    var i = 0    
    while (i < position) {
       ByteUtils.doubleToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 8)
       i += 1
    }    
  }

  def read(in: InputStreamWrapper): Unit = {
    val byteBuffer = new Array[Byte](8)
    var i = 0    
    while (i < position) {
       in.readBytes(byteBuffer, 0, 8)
       buffer(i) = ByteUtils.bytesToDouble(byteBuffer, 0)
       i += 1
    }
  }    
  
  @inline
  def ensureSize(n: Int): Unit = {
    val bufferLength: Long = buffer.length
    if (n > bufferLength) {
      var newSize: Long = bufferLength * 2
      while (n > newSize) newSize = newSize * 2
      // Clamp newSize to Int.MaxValue
      if (newSize > Int.MaxValue) newSize = Int.MaxValue
      val newBuffer = new Array[Double](newSize.toInt)
      scala.compat.Platform.arraycopy(buffer, 0, newBuffer, 0, position)
      buffer = newBuffer
    }
  }

  @inline
  def +=(elem: Double): Unit = {
    ensureSize(position + 1)
    buffer(position) = elem
    position += 1
  }
  
  @inline
  def apply(idx: Int): Double = {
    if (idx >= position) throw new IndexOutOfBoundsException(idx.toString)
    buffer(idx)
  }
}

final class CharBuffer(val initialSize: Int) extends Buffer {
  var buffer = new Array[Char](Math.max(initialSize, 1))
  
  def write(out: OutputStreamWrapper): Unit = {
  	val byteBuffer = new Array[Byte](2)
    var i = 0    
    while (i < position) {
       ByteUtils.charToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 2)
       i += 1
    }
  }

  def read(in: InputStreamWrapper): Unit = {
    val byteBuffer = new Array[Byte](2)
    var i = 0    
    while (i < position) {
       in.readBytes(byteBuffer, 0, 2)
       buffer(i) = ByteUtils.bytesToChar(byteBuffer, 0)
       i += 1
    }
  }

  @inline
  def ensureSize(n: Int): Unit = {
    val bufferLength: Long = buffer.length
    if (n > bufferLength) {
      var newSize: Long = bufferLength * 2
      while (n > newSize) newSize = newSize * 2
      // Clamp newSize to Int.MaxValue
      if (newSize > Int.MaxValue) newSize = Int.MaxValue
      val newBuffer = new Array[Char](newSize.toInt)
      scala.compat.Platform.arraycopy(buffer, 0, newBuffer, 0, position)
      buffer = newBuffer
    }
  }
  
  @inline
  def +=(elem: Char): Unit = {
    ensureSize(position + 1)
    buffer(position) = elem
    position += 1
  }
   
  @inline
  def apply(idx: Int): Char = {
    if (idx >= position) throw new IndexOutOfBoundsException(idx.toString)
    buffer(idx)
  }
}

final class CharArrayBuffer(initialSize: Int, fieldLength: Int) extends Buffer { 
  val typeSize = 2 * fieldLength
  var buffer = new Array[Byte](initialSize * typeSize) 
  private val charArray = new CharArray(fieldLength)
  
  override def size = position / typeSize
  
  override def size_=(_size: Int) = super.size_=(_size * typeSize)
  
  def write(out: OutputStreamWrapper) = out.writeBytes(buffer, 0, position)

  def read(in: InputStreamWrapper) = in.readBytes(buffer, 0, position)
  
  @inline
  def ensureSize(n: Int): Unit = {
    val bufferLength: Long = buffer.length
    if (n > bufferLength) {
      var newSize: Long = bufferLength * 2
      while (n > newSize) newSize = newSize * 2
      // Clamp newSize to Int.MaxValue
      if (newSize > Int.MaxValue) newSize = Int.MaxValue
      val newBuffer = new Array[Byte](newSize.toInt)
      scala.compat.Platform.arraycopy(buffer, 0, newBuffer, 0, position)
      buffer = newBuffer
    }
  }
  
  @inline
  def +=(elem: CharArray): Unit = {
    ensureSize(position + typeSize)
    ByteUtils.charArrayToBytes(elem, buffer, position)
    position += typeSize
  }
  
  @inline
  def apply(idx: Int): CharArray = {
    val offset = idx * typeSize
    if (offset + typeSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToCharArray(buffer, offset, charArray)
    charArray    
  }
}

abstract class WrappedBuffer extends Buffer {
  val typeSize: Int
  var buffer: Array[Byte]
  
  @inline
  def ensureSize(n: Int): Unit = {
    val bufferLength: Long = buffer.length
    if (n > bufferLength) {
      var newSize: Long = bufferLength * 2
      while (n > newSize) newSize = newSize * 2
      // Clamp newSize to Int.MaxValue
      if (newSize > Int.MaxValue) newSize = Int.MaxValue
      val newBuffer = new Array[Byte](newSize.toInt)
      scala.compat.Platform.arraycopy(buffer, 0, newBuffer, 0, position)
      buffer = newBuffer
    }
  }

  final def write(out: OutputStreamWrapper) = out.writeBytes(buffer, 0, position)

  final def read(in: InputStreamWrapper) = in.readBytes(buffer, 0, position)
    
  override def size = position / typeSize
  
  override def size_=(_size: Int) = super.size_=(_size * typeSize)
}

final class WrappedIntBuffer(initialSize: Int) extends WrappedBuffer {
  val typeSize = 4
  var buffer = new Array[Byte](initialSize * typeSize)

  @inline
  def +=(elem: Int): Unit = {
    ensureSize(position + typeSize)
    ByteUtils.intToBytes(elem, buffer, position)
    position += typeSize
  }

  @inline
  def apply(idx: Int): Int = {
    val offset = idx * typeSize    
    if (offset + typeSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToInt(buffer, offset)
  }  
}

final class WrappedDoubleBuffer(initialSize: Int) extends WrappedBuffer { 
  val typeSize = 8
  var buffer = new Array[Byte](initialSize * typeSize)

  @inline
  def +=(elem: Double): Unit = {
    ensureSize(position + typeSize)
    ByteUtils.doubleToBytes(elem, buffer, position)
    position += typeSize
  }

  @inline
  def apply(idx: Int): Double = {
    val offset = idx * typeSize
    if (offset + typeSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToDouble(buffer, offset)
  }  
}

final class WrappedCharBuffer(initialSize: Int) extends WrappedBuffer { 
  val typeSize = 2
  var buffer = new Array[Byte](initialSize * typeSize)

  @inline
  def +=(elem: Char): Unit = {
    ensureSize(position + typeSize)
    ByteUtils.charToBytes(elem, buffer, position)
    position += typeSize
  }
  
  @inline
  def apply(idx: Int): Char = {
    val offset = idx * typeSize
    if (offset + typeSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToChar(buffer, offset)
  }  
}

final class WrappedCharArrayBuffer(initialSize: Int, fieldLength: Int) extends WrappedBuffer {  
  val typeSize = 2 * fieldLength
  var buffer = new Array[Byte](initialSize * typeSize)
  private val charArray = new CharArray(fieldLength)
  
  @inline
  def +=(elem: CharArray): Unit = {
    ensureSize(position + typeSize)
    ByteUtils.charArrayToBytes(elem, buffer, position)
    position += typeSize
  }

  @inline
  def apply(idx: Int): CharArray = {
    val offset = idx * typeSize
    if (offset + typeSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToCharArray(buffer, offset, charArray)
    charArray
  }
}