package ddbt.lib.spark

import org.apache.hadoop.conf.Configuration
import org.apache.hadoop.fs.{ Path, FileSystem, FSDataOutputStream }

class LogWriter(name: String, outputPath: String) {
  
  private val fs = FileSystem.get(new Configuration())

  private val output: FSDataOutputStream = 
    if (outputPath == null) null
    else {
      val outputDir = new Path(outputPath)
      if (!fs.exists(outputDir)) fs.mkdirs(outputDir)

      val dateFormat = new java.text.SimpleDateFormat("yyyyMMdd_hhmm")
      val dateSuffix = dateFormat.format(new java.util.Date())
      val filename = new Path(s"${outputPath}/${name}_${dateSuffix}")
      fs.create(filename, true)
    }

  def println(s: String, hsync: Boolean = false) = {
    if (output != null) {
      output.writeUTF(s + "\n")
      if (hsync) output.hsync()
    }
    Predef.println(s)
  }

  def flush() = if (output != null) output.hsync()
}
