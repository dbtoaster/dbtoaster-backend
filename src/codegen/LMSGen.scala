package ddbt.codegen
import ddbt.ast._

/** Stub for conditional compilation, actual implementation in lms/ folder */
case class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  override def apply(s:M3.System) = sys.error(
    "Set 'ddbt.lms=1' in conf/ddbt.properties to enable LMS code generation"
  )
}
