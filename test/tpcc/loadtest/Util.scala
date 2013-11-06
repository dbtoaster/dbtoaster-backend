package ddbt.tpcc.loadtest

import java.util.Date
import java.util.Random
import TpccConstants._

object Util{

  var no: Int = _

  var py: Int = _

  var os: Int = _

  var dl: Int = _

  var sl: Int = _

  var total: Int = 0

  private var seq: Array[Int] = _

  private var nextNum: Int = 0

  var first: java.lang.Boolean = true

  var permCount: Int = _

  private var generate: Random = new Random()

  private val C_255 = randomNumber(0, 255)

  private val C_1023 = randomNumber(0, 1023)

  private val C_8191 = randomNumber(0, 8191)

  def shuffle() {
    var i: Int = 0
    var j: Int = 0
    var tmp: Int = 0
    var rmd: Int = 0
    val rnd = new Random()
    i = 0
    j = 0
    while (i < no) {
      seq(j) = 0
      i += 1
      j += 1
    }
    i = 0
    while (i < py) {
      seq(j) = 1
      i += 1
      j += 1
    }
    i = 0
    while (i < os) {
      seq(j) = 2
      i += 1
      j += 1
    }
    i = 0
    while (i < dl) {
      seq(j) = 3
      i += 1
      j += 1
    }
    i = 0
    while (i < sl) {
      seq(j) = 4
      i += 1
      j += 1
    }
    i = 0
    j = total - 1
    while (j > 0) {
      rmd = rnd.nextInt() % (j + 1)
      if (rmd < 0) {
        rmd = rmd * -1
      }
      tmp = seq(rmd + i)
      seq(rmd + i) = seq(i)
      seq(i) = tmp
      i += 1
      j -= 1
    }
  }

  def seqInit(n: Int, 
      p: Int, 
      o: Int, 
      d: Int, 
      s: Int) {
    no = n
    py = p
    os = o
    dl = d
    sl = s
    total = n + p + o + d + s
    System.out.print("TOTAL:%d".format(total))
    seq = Array.ofDim[Int](total)
    shuffle()
    nextNum = 0
  }

  def seqGet(): Int = {
    synchronized {
      if (nextNum >= total) {
        shuffle()
        nextNum = 0
      }
      nextNum += 1
      seq(nextNum - 1)
    }
  }

  def setSeed(seed: Int) {
    generate.setSeed(seed)
  }

  def randomNumber(min: Int, max: Int): Int = {
    val next = generate.nextInt()
    var div = next % ((max - min) + 1)
    if (div < 0) {
      div = div * -1
    }
    val value = min + div
    value
  }

  def nuRand(A: Int, x: Int, y: Int): Int = {
    var C = 0
    A match {
      case 255 => C = C_255
      case 1023 => C = C_1023
      case 8191 => C = C_8191
      case _ => throw new RuntimeException("NURand: unexpected value (%d) of A used\n" + A)
    }
    ((((randomNumber(0, A) | randomNumber(x, y)) + C) % (y - x + 1)) + 
      x)
  }

  def makeAlphaString(x: Int, y: Int): String = {
    var str: String = null
    val temp = "0123456789" + "ABCDEFGHIJKLMNOPQRSTUVWXYZ" + "abcdefghijklmnopqrstuvwxyz"
    val alphanum = temp.toCharArray()
    val arrmax = 61
    var i: Int = 0
    var len: Int = 0
    len = randomNumber(x, y)
    i = 0
    while (i < len) {
      str = (if (str != null) {
        str + alphanum(randomNumber(0, arrmax)) 
      } else {
        "" + alphanum(randomNumber(0, arrmax))
      })
      i += 1
    }
    str
  }

  def makeNumberString(x: Int, y: Int): String = {
    var str: String = null
    val numeric = "0123456789".toCharArray()
    val arrmax = 9
    var i: Int = 0
    var len: Int = 0
    len = randomNumber(x, y)
    i = 0
    while (i < len) {
      str = (if (str != null) str + numeric(randomNumber(0, arrmax)) else "0")
      i += 1
    }
    str
  }

  def initPermutation() {
    var i: Int = 0
    var j = 0
    val tempNums = Array.ofDim[Int](CUST_PER_DIST)
    permCount = 0
    i = 0
    while (i < ORD_PER_DIST) {
      nums(i) = i + 1
      tempNums(i) = i + 1
      i += 1
    }
    i = 0
    while (i < ORD_PER_DIST - 1) {
      j = randomNumber(i + 1, ORD_PER_DIST - 1).toInt
      nums(j) = tempNums(i)
      i += 1
    }
  }

  def getPermutation(): Int = {
    if (permCount >= ORD_PER_DIST) {
      throw new RuntimeException("GetPermutation: past end of list!\n")
    }
    permCount += 1
    nums(permCount - 1)
  }

  def lastName(num: Int): String = {
    var name: String = null
    val n = Array("BAR", "OUGHT", "ABLE", "PRI", "PRES", "ESE", "ANTI", "CALLY", "ATION", "EING")
    name = n(num / 100)
    name = name + n((num / 10) % 10)
    name = name + n(num % 10)
    name
  }
  def doubleEq(d1:Double, d2:Double):Boolean = (Math.abs(d1-d2) < 0.1f)
  def floatEq(d1:Float, d2:Float):Boolean = (Math.abs(d1-d2) < 0.1f)
  def dateEq(d1:Date, d2:Date):Boolean = (((d1.getTime - d2.getTime) / 1000) == 0)


  def roundDate(d:Date):Date = {
    val c = java.util.Calendar.getInstance();
    c.setTime(d);
    val mil = c.get(java.util.Calendar.MILLISECOND);
    c.set(java.util.Calendar.MILLISECOND, 0);
    //TODO Date rounding is required for some versions of MySQL
    // if(mil >= 500) {
    //  c.set(java.util.Calendar.SECOND, c.get(java.util.Calendar.SECOND)+1);
    // }
    c.getTime()
  }
}
