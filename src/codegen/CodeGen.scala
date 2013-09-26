package ddbt.codegen
import ddbt.ast.{M3,Source}

/**
 * An abstraction of the code generator. Because we want to instrument generated
 * code for testability, we separate helper functions and core processing.
 *
 * @author TCK
 */
abstract class CodeGen(cls:String="Query") extends (M3.System => String) {
  // Generate the system (everything but stream and views I/O)
  def apply(s:M3.System) : String

  // Generate headers + dummy helper for benchmarking
  def helper(s:M3.System,samples:Int=10) : String
  // Stream sources definition
  def streams(sources:List[Source]) : String
}
