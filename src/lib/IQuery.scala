package ddbt.lib

import ddbt.lib.Messages.StreamEvent

trait IQuery {
  def handleEvent(e: StreamEvent): Any
}
