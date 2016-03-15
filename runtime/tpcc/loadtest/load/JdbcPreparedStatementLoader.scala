package ddbt.tpcc.loadtest.load

import java.sql.Connection
import java.sql.PreparedStatement
import java.sql.SQLException

/**
 * Data loader using prepared statements and batches. This is slower than the JdbcStatementLoader which uses
 * bulk inserts.
 */
class JdbcPreparedStatementLoader(var conn: Connection, 
    var tableName: String, 
    var columnName: Array[String], 
    var ignore: Boolean, 
    var maxBatchSize: Int) extends RecordLoader {

  var pstmt: PreparedStatement = _

  var currentBatchSize: Int = _

  val b = new StringBuilder()

  b.append("INSERT ")

  if (ignore) {
    b.append("IGNORE ")
  }

  b.append("INTO `").append(tableName).append("` (")

  for (i <- 0 until columnName.length) {
    if (i > 0) {
      b.append(',')
    }
    b.append(columnName(i).trim())
  }

  b.append(") VALUES (")

  for (i <- 0 until columnName.length) {
    if (i > 0) {
      b.append(',')
    }
    b.append('?')
  }

  b.append(')')

  val sql = b.toString

  {
    this.conn.setAutoCommit(false)
    this.pstmt = conn.prepareStatement(sql)
  }

  def load(r: Record) {
    for (i <- 0 until columnName.length) {
      pstmt.setObject(i + 1, r.getField(i))
    }
    pstmt.addBatch()
    currentBatchSize += 1 
    if (currentBatchSize == maxBatchSize) {
      executeCurrentBatch()
    }
  }

  private def executeCurrentBatch() {
    pstmt.executeBatch()
    currentBatchSize = 0
  }

  def commit() {
    conn.commit()
  }

  def close() {
    executeCurrentBatch()
    pstmt.close()
    conn.commit()
  }
}
