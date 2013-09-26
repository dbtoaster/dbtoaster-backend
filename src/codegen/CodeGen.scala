package ddbt.codegen
import ddbt.ast.{M3,Source}

/**
 * An abstraction of the code generator. Because we want to instrument generated
 * code for testability, we distinguish helper functions and core processing.
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

  // Stack of contexts abstraction
  case class Ctx[T](ctx0:Map[String,T]=Map()) extends Function1[String,T] {
    private var stack = List[Map[String,T]]()
    def push(ctx:Map[String,T]) { stack=ctx::stack }
    def pop(ctx:Int=0) { while (stack.size>ctx) stack=stack.tail }
    def cur:Int = stack.size

    def contains(name:String):Boolean = apply(name)!=null
    def apply(name:String):T = {
      def g(s:List[Map[String,T]]):T = s match {
        case ctx::xs => ctx.getOrElse(name,g(xs))
        case Nil => ctx0.getOrElse(name,null.asInstanceOf[T])
      }
      g(stack)
    }
  }
}
