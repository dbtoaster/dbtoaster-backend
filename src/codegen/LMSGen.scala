package ddbt.codegen
import ddbt.ast._

/** Stub for conditional compilation, actual implementation in lms/ folder */
case class LMSGen(cls:String="Query") extends ScalaGen(cls) {
//  def apply(sys:M3.System) = "// Placeholder code generator.\n//\n"+
//    "// Set ddbt.lms = 1 in conf/ddbt.properties to embed LMS code generator\n"
}
