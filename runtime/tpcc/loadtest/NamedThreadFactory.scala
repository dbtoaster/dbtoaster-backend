package ddbt.tpcc.loadtest

import java.util.concurrent.ThreadFactory

class NamedThreadFactory(var namePrefix: String) extends ThreadFactory {

  private var nextID: Int = 1

  def newThread(runnable: Runnable): Thread = {
    var id: Int = 0
    this.synchronized {
      id = nextID
      nextID += 1
    }
    new Thread(runnable, namePrefix + "-" + id)
  }
}
