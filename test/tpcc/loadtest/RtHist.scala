package ddbt.tpcc.loadtest


object RtHist {

  private val MAXREC = 20

  private val REC_PER_SEC = 1000

  private var total_hist = Array.ofDim[Int](5, MAXREC * REC_PER_SEC)

  private var cur_hist = Array.ofDim[Int](5, MAXREC * REC_PER_SEC)

  var max_rt: Array[Double] = new Array[Double](10)

  var cur_max_rt: Array[Double] = new Array[Double](10)

  def histInit() {
    var i = 0
    var j = 0
    i = 0
    while (i < 5) {
      j = 0
      while (j < (MAXREC * REC_PER_SEC)) {
        cur_hist(i)(j) = 0
        total_hist(i)(j) = 0
        j += 1
      }
      i += 1
    }
  }

  def histInc(transaction: Int, rtclk: Double) {
    var i = 0
    i = (rtclk * REC_PER_SEC.toDouble).toInt
    if (i >= (MAXREC * REC_PER_SEC)) {
      i = (MAXREC * REC_PER_SEC) - 1
    }
    if (rtclk > cur_max_rt(transaction)) {
      cur_max_rt(transaction) = rtclk
    }
    cur_hist(transaction)(i)
  }

  def histCkp(transaction: Int): Double = {
    var i: Int = 0
    var total: Int = 0
    var tmp: Int = 0
    var line: Int = 0
    var line_set: Int = 0
    line = MAXREC * REC_PER_SEC
    i = 0
    while (i < (MAXREC * REC_PER_SEC)) {
      total += cur_hist(transaction)(i)
      i += 1
    }
    i = 0
    while (i < (MAXREC * REC_PER_SEC)) {
      tmp += cur_hist(transaction)(i)
      total_hist(transaction)(i) += cur_hist(transaction)(i)
      cur_hist(transaction)(i) = 0
      if ((tmp >= (total * 99 / 100)) && (line_set == 0)) {
        line = i
        line_set = 1
      }
      i += 1
    }
    ((line).toDouble / (REC_PER_SEC).toDouble)
  }

  def histReport() {
    var i = 0
    var j = 0
    val total = Array.ofDim[Int](5)
    val tmp = Array.ofDim[Int](5)
    val line = Array.ofDim[Int](5)
    j = 0
    while (j < 5) {
      tmp(j) = 0
      total(j) = 0
      line(j) = MAXREC * REC_PER_SEC
      i = 0
      while (i < (MAXREC * REC_PER_SEC)) {
        total(j) += total_hist(j)(i)
        i += 1
      }
      i = (MAXREC * REC_PER_SEC) - 1
      while (i >= 0) {
        tmp(j) += total_hist(j)(i)
        if ((tmp(j) * 10) <= total(j)) {
          line(j) = i
        }
        i -= 1
      }
      j += 1
    }
    System.out.print("\n<RT Histogram>\n")
    j = 0
    while (j < 5) j match {
      case 0 => System.out.print("\n1.New-Order\n\n")
      case 1 => System.out.print("\n2.Payment\n\n")
      case 2 => System.out.print("\n3.Order-Status\n\n")
      case 3 => System.out.print("\n4.Delivery\n\n")
      case 4 => System.out.print("\n5.Stock-Level\n\n")
    }
    System.out.print("\n<90th Percentile RT (MaxRT)>\n")
    j = 0
    while (j < 5) j match {
      case 0 => System.out.print("   New-Order : ")
      case 1 => System.out.print("     Payment : ")
      case 2 => System.out.print("Order-Status : ")
      case 3 => System.out.print("    Delivery : ")
      case 4 => System.out.print(" Stock-Level : ")
    }
  }
}
