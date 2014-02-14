package ddbt.tpcc.loadtest.load


/**
 * Copyright (C) 2011 CodeFutures Corporation. All rights reserved.
 */
trait RecordLoader {

  def load(r: Record): Unit

  def commit(): Unit

  def close(): Unit
}
