package ddbt.tpcc.loadtest

import ddbt.tpcc.loadtest.load.FileLoader
import ddbt.tpcc.loadtest.load.JdbcPreparedStatementLoader
import ddbt.tpcc.loadtest.load.JdbcStatementLoader
import ddbt.tpcc.loadtest.load.RecordLoader
import java.io.File
import java.io.IOException
import java.sql.Connection
import scala.beans.{BeanProperty, BooleanBeanProperty}

  object LoadType extends Enumeration {

    type LoadType = Value 

    val JDBC_STATEMENT, JDBC_PREPARED_STATEMENT, CSV = Value

    //implicit def convertValue(v: Value): LoadType = v.asInstanceOf[LoadType]
  }

/**
 * Copyright (C) 2011 CodeFutures Corporation. All rights reserved.
 */
class TpccLoadConfig {

  @BeanProperty
  var loadType: LoadType.LoadType = LoadType.JDBC_PREPARED_STATEMENT

  @BeanProperty
  var conn: Connection = _

  private var outputDir: File = _

  private var jdbcInsertIgnore: Boolean = true

  private var jdbcBatchSize: Int = 100

  def createLoader(tableName: String, columnName: Array[String]): RecordLoader = loadType match {
    case LoadType.JDBC_STATEMENT => new JdbcStatementLoader(conn, tableName, columnName, jdbcInsertIgnore, jdbcBatchSize)
    case LoadType.JDBC_PREPARED_STATEMENT => new JdbcPreparedStatementLoader(conn, tableName, columnName, jdbcInsertIgnore, 
      jdbcBatchSize)
    case LoadType.CSV => new FileLoader(new File(outputDir, tableName + ".txt"))
    case _ => throw new IllegalStateException()
  }

  def setOutputDir(outputDir: File) {
    this.outputDir = outputDir
  }
}
