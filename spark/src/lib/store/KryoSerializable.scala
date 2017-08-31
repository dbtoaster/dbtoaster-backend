package ddbt.lib.spark.store

import com.esotericsoftware.kryo.io.{Input, Output}

trait KryoSerializable {
  
  def write(out: Output): Unit

  def read(in: Input): Unit    
}