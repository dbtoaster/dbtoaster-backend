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

  // Context maintenance helpers
  case class Ctx[T](ctx0:Map[String,T]=Map()) extends Function1[String,T] {
    private var ctx = scala.collection.mutable.HashMap[String,T]()
    def add(c:Map[String,T]) = c.foreach(x=>ctx.put(x._1,x._2))
    def load(c:Map[String,T]=Map()) { ctx.clear; add(c) }
    def save = ctx.toMap
    def contains(name:String):Boolean = apply(name)!=null
    def apply(name:String) = ctx.getOrElse(name,ctx0.getOrElse(name,null.asInstanceOf[T]))
  }
  case class CtxSet(ctx0:Set[String]=Set()) extends Function1[String,Boolean] {
    private var ctx = scala.collection.mutable.HashSet[String]()
    def add(c:Set[String]) { ctx = ctx ++ c }
    def load(c:Set[String]=Set()) { ctx.clear; c.foreach{ ctx+=_ } }
    def save = ctx.toSet
    def contains(name:String) = apply(name)
    def apply(name:String) = ctx.contains(name) || ctx0.contains(name)
  }
  /*
  case class CtxCtr[T](f:Int=>T=(i:Int)=>i) extends Function0[T] {
    private var ctr=0;
    def add(n:Int=1) { ctr=ctr+n; }
    def save = { val c=ctr; ctr=0; c }
    def load(c:Int=0) { ctr=c }
    def apply() = f(ctr)
  }
  */
  
  /*
  Need for an optimization phase:
  - simplifying aliases where possible
  - propagating constants
  - taking out constants
  - providing correct zero for types
  - mapref construction
  - avoiding duplicate get (benefitial for akka)
  - reducing aggregation of one element
  - disambiguate add/union at optimization phase ?
  */
  
  
}
