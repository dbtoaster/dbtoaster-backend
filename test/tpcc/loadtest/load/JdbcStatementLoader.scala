package ddbt.tpcc.loadtest.load

import java.sql.Connection
import java.sql.SQLException
import java.sql.Statement
import java.util.Date

/**
 * Copyright (C) 2011 CodeFutures Corporation. All rights reserved.
 */
class JdbcStatementLoader(var conn: Connection, 
    var tableName: String, 
    var columnName: Array[String], 
    var ignore: Boolean, 
    var maxBatchSize: Int) extends RecordLoader {

  var stmt: Statement = null

  var currentBatchSize: Int = 0

  var b: StringBuilder = new StringBuilder()

  def load(r: Record) {
    if (currentBatchSize == 0) {
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
      b.append(") VALUES ")
    } else {
      b.append(',')
    }
    b.append('(')
    write(b, r, ",")
    b.append(')')
    currentBatchSize += 1
    if (currentBatchSize == maxBatchSize) {
      executeBulkInsert()
    }
  }

  private def executeBulkInsert() {
    if (stmt == null) {
      stmt = conn.createStatement()
    }
    val sql = b.toString
    b.setLength(0)
    stmt.execute(sql)
    currentBatchSize = 0
  }

  def write(b: StringBuilder, r: Record, delim: String) {
    val field = r.getField
    for (i <- 0 until field.length) {
      if (i > 0) {
        b.append(delim)
      }
      val fieldValue = field(i)
      if (fieldValue.isInstanceOf[Date]) {
        b.append("'").append(fieldValue.asInstanceOf[Date])
          .append("'")
      } else if (fieldValue.isInstanceOf[String]) {
        b.append("'").append(fieldValue).append("'")
      } else {
        b.append(fieldValue)
      }
    }
  }

  def commit() {
    if (!conn.getAutoCommit) {
      conn.commit()
    }
  }

  def close() {
    if (currentBatchSize > 0) {
      executeBulkInsert()
      stmt.close()
    }
    if (!conn.getAutoCommit) {
      conn.commit()
    }
  }
}
