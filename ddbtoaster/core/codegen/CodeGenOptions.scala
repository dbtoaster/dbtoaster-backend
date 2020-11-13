package ddbt.codegen

/**
  * Set of options based to each code generator
  */
class CodeGenOptions(
  val className: String,
  val packageName: String,
  val dataset: String, 
  val datasetWithDeletions: Boolean,
  val timeoutMilli: Long, 
  val isReleaseMode: Boolean,
  val printTiminingInfo: Boolean, 
  val printProgress: Long = 0L,
  val useOldRuntimeLibrary: Boolean = false
)