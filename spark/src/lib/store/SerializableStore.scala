package ddbt.lib.spark.store

import ddbt.lib.spark.store.io.{InputStreamWrapper, OutputStreamWrapper}

// abstract class SerializableStore extends Serializable {

//   def buffers: Vector[Buffer]

//   def size: Int = if (buffers != null && buffers.size > 0) buffers(0).size else -1

//   def size_=(_size: Int) = buffers foreach { _.size = _size } 

//   def clear(): Unit = buffers foreach { _.clear() } 
        
//   def write(out: OutputStreamWrapper): Unit = buffers foreach { _.write(out) }
    
//   def read(in: InputStreamWrapper): Unit = buffers foreach { _.read(in) }      
// }