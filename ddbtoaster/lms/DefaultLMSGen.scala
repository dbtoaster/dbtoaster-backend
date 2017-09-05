package ddbt.codegen

import ddbt.ast.M3

/** Stub for conditional compilation, actual implementation in lms/ folder */
abstract class LMSGen(override val cls: String = "Query") extends CodeGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}

class LMSScalaGen(cls: String = "Query", override val watch: Boolean = false) extends LMSGen(cls) with IScalaGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}

class LMSCppGen(cls: String = "Query") extends LMSGen(cls) with ICppGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}
class LMSSparkGen(cls: String = "Query") extends LMSGen(cls) with IScalaGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}