package ddbt.tpcc.loadtest.load

import java.io.BufferedOutputStream
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.text.DateFormat
import java.text.SimpleDateFormat
import java.util.Date
import FileLoader._

object FileLoader {

  protected val dateFormat = new SimpleDateFormat("yyyy-MM-dd")

  protected val dateTimeFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
}

/**
 * Copyright (C) 2011 CodeFutures Corporation. All rights reserved.
 */
class FileLoader(file: File) extends RecordLoader {

  protected var os: BufferedOutputStream = new BufferedOutputStream(new FileOutputStream(file, true))

  protected val b = new StringBuilder()

  def load(r: Record) {
    b.setLength(0)
    val field = r.getField
    for (i <- 0 until field.length) {
      if (i > 0) {
        b.append('\t')
      }
      if (field(i) == null) {
        b.append("\\N")
      } else if (field(i).isInstanceOf[Date]) {
        b.append(dateTimeFormat.format(field(i).asInstanceOf[Date]))
      } else {
        b.append(field(i))
      }
    }
    os.write(b.toString.getBytes)
    os.write("\n".getBytes)
  }

  def commit() {
  }

  def close() {
    os.close()
  }
}
