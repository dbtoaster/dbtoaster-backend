package ddbt.lib

import collection.mutable.HashMap

object ExP {
  val startTimes = HashMap[String, Long]()
  val durations = HashMap[String, Long]()
  val counters = HashMap[String, Long]()

  def start(n: String): Unit = {
    startTimes(n) = System.nanoTime()
    ()
  }

  def end(n: String): Unit = {
    val e = System.nanoTime()
    val s = startTimes(n)
    val d = e - s
    if (durations.contains(n)) {
      durations(n) += d
      counters(n) += 1
    } else {
      durations += ((n, d))
      counters += ((n, 1))
    }
    ()
  }

  def print() = {
    System.err.println(durations.keySet.map(k => s"$k  count = ${counters(k)}   time =  ${durations(k) / 1000000.0} ms    avg time = ${durations(k) / counters(k)} ns").mkString("\n"))
  }
}