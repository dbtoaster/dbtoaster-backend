package ddbt.lib.spark.store

import com.esotericsoftware.kryo.io.{Input, Output}

abstract sealed class Buffer extends KryoSerializable {

  var position: Int = 0         // public to make inlining possible

  def buffer: Array[_]

  def stepSize: Int             // number of buffer items that make one element
  
  def clear(): Unit = position = 0

  def capacity = buffer.length / stepSize
  
  def size = position / stepSize

  def size_=(n: Int): Unit = {
    val nativeSize = n * stepSize
    ensureSize(nativeSize)
    position = nativeSize
  }

  def ensureSize(n: Int): Unit   
}

object Buffer {

  def apply(tp: String, size: Int, strFieldLength: Int = 0) = tp match {
    case "int"    => new IntBuffer(size)
    case "double" => new DoubleBuffer(size)
    case "char"   => new CharBuffer(size)
    case "charArray" | "wstring" => new CharArrayBuffer(size, strFieldLength)
    case "wint"    => new WrappedIntBuffer(size)
    case "wdouble" => new WrappedDoubleBuffer(size)
    case "wchar"   => new WrappedCharBuffer(size)
    case "wcharArray" | "wstring" => new WrappedCharArrayBuffer(size, strFieldLength)
    case _ => sys.error("Unsupported buffer type")
  } 

  def write(out: Output, buffer: Buffer): Unit = {
    // We don't use case classes here to enable inlining
    if (buffer.isInstanceOf[IntBuffer]) {
      out.writeInt('I')
      out.writeInt(buffer.size)
      buffer.write(out)  
    } 
    else if (buffer.isInstanceOf[DoubleBuffer]) {
      out.writeInt('D')
      out.writeInt(buffer.size)
      buffer.write(out)
    }
    else if (buffer.isInstanceOf[CharBuffer]) {
      out.writeInt('C')
      out.writeInt(buffer.size)
      buffer.write(out)
    }
    else if (buffer.isInstanceOf[CharArrayBuffer]) {
      out.writeInt('S')
      out.writeInt(buffer.size)
      out.writeInt(buffer.asInstanceOf[CharArrayBuffer].fieldLength)
      buffer.write(out)
    }
    else if (buffer.isInstanceOf[WrappedIntBuffer]) {
      out.writeInt('i')
      out.writeInt(buffer.size)
      buffer.write(out)      
    }
    else if (buffer.isInstanceOf[WrappedDoubleBuffer]) {
      out.writeInt('d')
      out.writeInt(buffer.size)
      buffer.write(out)      
    }
    else if (buffer.isInstanceOf[WrappedCharBuffer]) {
      out.writeInt('c')
      out.writeInt(buffer.size)
      buffer.write(out)      
    }
    else if (buffer.isInstanceOf[WrappedCharArrayBuffer]) {
      out.writeInt('s')
      out.writeInt(buffer.size)
      out.writeInt(buffer.asInstanceOf[WrappedCharArrayBuffer].fieldLength)
      buffer.write(out)      
    }
    else sys.error("Unknown buffer type " + buffer.getClass.getName)
  }

  def read(in: Input): Buffer = {
    val classId = in.readInt()
    val size = in.readInt()
    val buffer = classId match {
      case 'I' => new IntBuffer(size)
      case 'D' => new DoubleBuffer(size)
      case 'C' => new CharBuffer(size)
      case 'S' => new CharArrayBuffer(size, in.readInt())
      case 'i' => new WrappedIntBuffer(size)
      case 'd' => new WrappedDoubleBuffer(size)
      case 'c' => new WrappedCharBuffer(size)
      case 's' => new WrappedCharArrayBuffer(size, in.readInt())
      case  x => sys.error("Unknown buffer type " + x)
    }
    buffer.size = size
    buffer.read(in)
    buffer
  }  
}

final class IntBuffer(initialSize: Int) extends Buffer { 
  var buffer = new Array[Int](Math.max(initialSize, 1))
  val stepSize = 1

  def write(out: Output): Unit = {
    val byteBuffer = new Array[Byte](4)
    var i = 0    
    while (i < position) {
       ByteUtils.intToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 4)
       i += 1
    }
  }

  def read(in: Input): Unit = {
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

final class DoubleBuffer(initialSize: Int) extends Buffer { 
  var buffer = new Array[Double](Math.max(initialSize, 1))
  val stepSize = 1

  def write(out: Output): Unit = {
    val byteBuffer = new Array[Byte](8)
    var i = 0    
    while (i < position) {
       ByteUtils.doubleToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 8)
       i += 1
    }    
  }

  def read(in: Input): Unit = {
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

final class CharBuffer(initialSize: Int) extends Buffer {
  var buffer = new Array[Char](Math.max(initialSize, 1))
  val stepSize = 1

  def write(out: Output): Unit = {
    val byteBuffer = new Array[Byte](2)
    var i = 0    
    while (i < position) {
       ByteUtils.charToBytes(buffer(i), byteBuffer, 0)
       out.writeBytes(byteBuffer, 0, 2)
       i += 1
    }
  }

  def read(in: Input): Unit = {
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

final class CharArrayBuffer(initialSize: Int, val fieldLength: Int) extends Buffer {   
  val stepSize = 2 * fieldLength
  var buffer = new Array[Byte](initialSize * stepSize) 
  val charArray = new CharArray(fieldLength)
  
  def write(out: Output) = out.writeBytes(buffer, 0, position)

  def read(in: Input) = in.readBytes(buffer, 0, position)

  
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
    ensureSize(position + stepSize)
    ByteUtils.charArrayToBytes(elem, buffer, position)
    position += stepSize
  }

  @inline
  def +=(elem: String): Unit = {
    ensureSize(position + stepSize)
    charArray.putString(elem)
    ByteUtils.charArrayToBytes(charArray, buffer, position)
    position += stepSize
  }
  
  @inline
  def apply(idx: Int): CharArray = {
    val offset = idx * stepSize
    if (offset + stepSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToCharArray(buffer, offset, charArray)
    charArray    
  }
}

abstract class WrappedBuffer extends Buffer {
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

  def write(out: Output) = out.writeBytes(buffer, 0, position)

  def read(in: Input) = in.readBytes(buffer, 0, position)
}

final class WrappedIntBuffer(initialSize: Int) extends WrappedBuffer {
  val stepSize = 4
  var buffer = new Array[Byte](initialSize * stepSize)

  @inline
  def +=(elem: Int): Unit = {
    ensureSize(position + stepSize)
    ByteUtils.intToBytes(elem, buffer, position)
    position += stepSize
  }

  @inline
  def apply(idx: Int): Int = {
    val offset = idx * stepSize    
    if (offset + stepSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToInt(buffer, offset)
  }  
}

final class WrappedDoubleBuffer(initialSize: Int) extends WrappedBuffer { 
  val stepSize = 8
  var buffer = new Array[Byte](initialSize * stepSize)

  @inline
  def +=(elem: Double): Unit = {
    ensureSize(position + stepSize)
    ByteUtils.doubleToBytes(elem, buffer, position)
    position += stepSize
  }

  @inline
  def apply(idx: Int): Double = {
    val offset = idx * stepSize
    if (offset + stepSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToDouble(buffer, offset)
  }  
}

final class WrappedCharBuffer(initialSize: Int) extends WrappedBuffer { 
  val stepSize = 2
  var buffer = new Array[Byte](initialSize * stepSize)

  @inline
  def +=(elem: Char): Unit = {
    ensureSize(position + stepSize)
    ByteUtils.charToBytes(elem, buffer, position)
    position += stepSize
  }
  
  @inline
  def apply(idx: Int): Char = {
    val offset = idx * stepSize
    if (offset + stepSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToChar(buffer, offset)
  }  
}

final class WrappedCharArrayBuffer(initialSize: Int, val fieldLength: Int) extends WrappedBuffer {  
  val stepSize = 2 * fieldLength
  var buffer = new Array[Byte](initialSize * stepSize)
  private val charArray = new CharArray(fieldLength)
  
  @inline
  def +=(elem: CharArray): Unit = {
    ensureSize(position + stepSize)
    ByteUtils.charArrayToBytes(elem, buffer, position)
    position += stepSize
  }

  @inline
  def apply(idx: Int): CharArray = {
    val offset = idx * stepSize
    if (offset + stepSize > position) throw new IndexOutOfBoundsException(idx.toString)
    ByteUtils.bytesToCharArray(buffer, offset, charArray)
    charArray
  }
}