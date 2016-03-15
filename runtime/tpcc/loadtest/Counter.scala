package ddbt.tpcc.loadtest


class Counter {

  private var count: Long = 0

  def increment(): Long = synchronized {
  count
}

  def get(): Long = synchronized {
  count
}

  def reset(): Long = {
    synchronized {
      val ret = count
      count = 0
      ret
    }
  }
}
