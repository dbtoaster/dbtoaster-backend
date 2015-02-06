package ddbt.lib.spark.store

import ddbt.lib.spark.store.io.{InputStreamWrapper, OutputStreamWrapper}

trait Serializable {
  
  def write(out: OutputStreamWrapper): Unit
  
  def read(in: InputStreamWrapper): Unit  
}