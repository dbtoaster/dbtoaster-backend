package ddbt.lib.spark.store

import java.util.Arrays

object CharArrayImplicits { 
  import scala.language.implicitConversions
  implicit def charArrayToStr(c: CharArray): String = c.getString
}

class CharArray(capacity: Int) {

  val charArray = new Array[Char](capacity)   
  var _size = 0

  def this(str: String) = {
    this(str.length)
    putString(str)
  }
  
  def size: Int = _size

  def clear(): Unit = _size = 0

  def putString(str: String): CharArray = {
    _size = math.min(capacity, str.length)
    str.getChars(0, _size, charArray, 0)
    this
  }

  def getString(): String = new String(charArray, 0, _size)

  def putBytes(bytes: Array[Byte], offset: Int): Unit = {
    var endFound = false
    var byteOffset = offset
    var i = 0
    while (i < capacity && !endFound) {      
      charArray(i) = ByteUtils.bytesToChar(bytes, byteOffset)
      endFound = (charArray(i) == 0.toChar)
      byteOffset += 2
      i += 1
    }
	if (endFound) {
	  _size = i - 1
	  Arrays.fill(charArray, i, capacity, 0.toChar)
	}
	else _size = capacity 
  }

  def getBytes(bytes: Array[Byte], offset: Int): Unit = {
    var byteOffset = offset
    var i = 0
    while (i < _size) {
      ByteUtils.charToBytes(charArray(i), bytes, byteOffset)
      byteOffset += 2
      i += 1
    }
    Arrays.fill(bytes, byteOffset, offset + (capacity << 1), 0.toByte)
  }
  
  def equals(other: CharArray): Boolean = {
    if (this._size != other._size) false
    else {
      var result = true
      var i = 0
      while (i < this._size && result) {
        result = (this.charArray(i) == other.charArray(i))
        i += 1
      }
      result
    }
  }
}