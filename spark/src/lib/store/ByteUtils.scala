package ddbt.lib.spark.store

object ByteUtils {
         
  @inline
  def intToBytes(value: Int, bytes: Array[Byte], offset: Int): Unit = {
    bytes(offset) = (value >> 24).toByte
    bytes(offset + 1) = (value >> 16).toByte
    bytes(offset + 2) = (value >> 8).toByte
    bytes(offset + 3) = value.toByte
  }

  @inline
  def bytesToInt(bytes: Array[Byte], offset: Int): Int = {
    (bytes(offset) & 0xFF) << 24 |
      (bytes(offset + 1) & 0xFF) << 16 |
      (bytes(offset + 2) & 0xFF) << 8 |
      (bytes(offset + 3) & 0xFF)
  }

  @inline
  def longToBytes(value: Long, bytes: Array[Byte], offset: Int): Unit = {
    bytes(offset) = (value >>> 56).toByte
    bytes(offset + 1) = (value >>> 48).toByte
    bytes(offset + 2) = (value >>> 40).toByte
    bytes(offset + 3) = (value >>> 32).toByte
    bytes(offset + 4) = (value >>> 24).toByte
    bytes(offset + 5) = (value >>> 16).toByte
    bytes(offset + 6) = (value >>> 8).toByte
    bytes(offset + 7) = value.toByte
  }

  @inline
  def bytesToLong(bytes: Array[Byte], offset: Int): Long = {
    bytes(offset).toLong << 56 |
      (bytes(offset + 1).toLong & 0xFF) << 48 |
      (bytes(offset + 2).toLong & 0xFF) << 40 |
      (bytes(offset + 3).toLong & 0xFF) << 32 |
      (bytes(offset + 4).toLong & 0xFF) << 24 |
      (bytes(offset + 5) & 0xFF) << 16 |
      (bytes(offset + 6) & 0xFF) << 8 |
      (bytes(offset + 7) & 0xFF)
  }

  @inline
  def doubleToBytes(value: Double, bytes: Array[Byte], offset: Int): Unit =
    longToBytes(java.lang.Double.doubleToLongBits(value), bytes, offset)

  @inline
  def bytesToDouble(bytes: Array[Byte], offset: Int): Double =
    java.lang.Double.longBitsToDouble(bytesToLong(bytes, offset))

  @inline
  def charToBytes(value: Char, bytes: Array[Byte], offset: Int): Unit = {
    bytes(offset) = (value >>> 8).toByte
    bytes(offset + 1) = value.toByte
  }

  @inline
  def bytesToChar(bytes: Array[Byte], offset: Int): Char =
    (((bytes(offset) & 0xFF) << 8) | (bytes(offset + 1) & 0xFF)).toChar

  @inline
  def boolToBytes(value: Boolean, bytes: Array[Byte], offset: Int): Unit = 
    bytes(offset) = if (value) 0x01 else 0x00

  @inline
  def bytesToBool(bytes: Array[Byte], offset: Int): Boolean =
    bytes(offset) != 0x00
    
  @inline
  def charArrayToBytes(value: CharArray, bytes: Array[Byte], offset: Int): Unit =
    value.getBytes(bytes, offset)

  @inline
  def bytesToCharArray(bytes: Array[Byte], offset: Int, value: CharArray): Unit = 
    value.putBytes(bytes, offset)
}