package ddbt.lib.spark.store.io

import java.io.InputStream
import java.io.OutputStream
import ddbt.lib.spark.store.ByteUtils

class InputStreamWrapper(input: InputStream) {
  
  val byteBuffer = new Array[Byte](8)
  
  private var prebuffer: Array[Byte] = null
  private var prebufferPosition: Int = 0
  private var prebufferRemaining: Int = 0
  
  def setPrebuffer(buffer: Array[Byte], offset: Int, length: Int) {
    prebuffer = buffer
    prebufferPosition = offset
    prebufferRemaining = length
  }
  
  private def _readBytes(buffer: Array[Byte], offset: Int, length: Int) = {
    var position = offset
    var remaining = length
    while (remaining > 0) {
      val readCount = input.read(buffer, position, remaining)
      if (readCount != -1) {
        position += readCount
        remaining -= readCount
      } 
      else throw new RuntimeException("HEY, IT'S ALREADY OVER?")
    }
  }
  
  def readBytes(buffer: Array[Byte], offset: Int, length: Int) = {
    if (length > 0) {
      if (prebufferRemaining > 0) {
        val copyCount = math.min(prebufferRemaining, length)
        System.arraycopy(prebuffer, prebufferPosition, buffer, offset, copyCount)
        prebufferPosition += copyCount
        prebufferRemaining -= copyCount
        if (length - copyCount > 0)
          _readBytes(buffer, offset + copyCount, length - copyCount)
      } else _readBytes(buffer, offset, length)
    }
  }
  
  def readInt(): Int = {
    readBytes(byteBuffer, 0, 4)
    ByteUtils.bytesToInt(byteBuffer, 0)
  }
  
  def readDouble(): Double = {
    readBytes(byteBuffer, 0, 8)
    ByteUtils.bytesToDouble(byteBuffer, 0)
  }
  
  def readBoolean(): Boolean = {
    readBytes(byteBuffer, 0, 1)
    ByteUtils.bytesToBool(byteBuffer, 0)
  }
}

class OutputStreamWrapper(output: OutputStream) {

  val byteBuffer = new Array[Byte](8)
  
  def writeBytes(buffer: Array[Byte], offset: Int, length: Int) = 
    if (length > 0) output.write(buffer, offset, length)
    
  def writeInt(i: Int) = {
    ByteUtils.intToBytes(i, byteBuffer, 0)
    output.write(byteBuffer, 0, 4)
  }
  
  def writeDouble(d: Double) = {
    ByteUtils.doubleToBytes(d, byteBuffer, 0)
    output.write(byteBuffer, 0, 8)
  }
  
  def writeBoolean(b: Boolean) = {
    ByteUtils.boolToBytes(b, byteBuffer, 0)
    output.write(byteBuffer, 0, 1)
  }
}
