package ddbt.codegen

import ddbt.ast.M3

/** Stub for conditional compilation, actual implementation in lms/ folder */
abstract class LMSGen(override val cgOpts: CodeGenOptions) extends CodeGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}

class LMSScalaGen(cgOpts: CodeGenOptions, override val watch: Boolean = false) extends LMSGen(cgOpts) with IScalaGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}

class LMSCppGen(cgOpts: CodeGenOptions) extends LMSGen(cgOpts) with ICppGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}
class LMSSparkGen(cgOpts: CodeGenOptions) extends LMSGen(cgOpts) with IScalaGen {
  override def apply(s0: M3.System): String = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}