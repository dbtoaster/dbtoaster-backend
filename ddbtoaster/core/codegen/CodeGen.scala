package ddbt.codegen

import ddbt.ast.{ Type, M3 }
import scala.collection.mutable.HashMap

/**
  * An abstraction of the code generator.
  *
  * Because we want to instrument generated code for testability,
  * we distinguish helper functions and core processing.
  *
  * @author TCK
  */
trait CodeGen extends (M3.System => String) {

  // Context maintenance helpers
  case class Ctx[T](ctx0: Map[String, T] = Map[String, T]()) extends Function1[String, T] {
    private var ctx = scala.collection.mutable.HashMap[String, T]()

    def add(c: Map[String, T]) = c.foreach(x => ctx.put(x._1, x._2))
    def add(n: String, t: T) = ctx.put(n, t) 
    def load(c: Map[String, T] = Map()) = { ctx.clear; add(c) }
    def save = ctx.toMap
    def contains(name: String): Boolean = apply(name) != null
    def apply(name: String): T = ctx.getOrElse(name, ctx0.getOrElse(name, null.asInstanceOf[T]))
  }

  case class CtxSet(ctx0: Set[String] = Set()) extends Function1[String, Boolean] {
    private var ctx = scala.collection.mutable.HashSet[String]()

    def add(c: Set[String]) = ctx ++= c
    def add(s: String) = ctx += s 
    def load(c: Set[String] = Set()) = { ctx.clear; c foreach { ctx += _ } }
    def save = ctx.toSet
    def contains(name: String) = apply(name)
    def apply(name: String) = ctx.contains(name) || ctx0.contains(name)
  }

  // Generate the system (everything but stream and views I/O)
  def apply(s: M3.System): String

  protected def cgOpts: CodeGenOptions

  // Context: variable->(type,unique_name)
  protected var ctx: Ctx[(Type, String)] = null 

  /* Get unique name
    
    Used to rename variable to avoid putting individual statements in separated blocks
        M[x] = Add( Mul(Lift(x,2),A[x]), Mul(Lift(x,3),B[x]) )
        { x=A[2]; x } + { x=B[3]; x }
    but we want
        val x1=A[2]
        val x2=B[3]
        x1+x2
  */  
  protected def rn(n: String): String = ctx(n)._2 

  protected def genLMS(s0: M3.System): (String, String, String, String) = (null, null, null, null)

  protected def genPardis(s0: M3.System): (String, String, String) = (null, null, null)

  // ---------- Regular expression methods
  protected val ENABLE_REGEXP_PARTIAL_EVAL = true

  // Regex string => Regex object name
  protected val regexpCacheMap = HashMap[String, String]() 

  // Function invocations involving only constants are hoisted as global constants
  protected val hoistedConsts = HashMap[M3.Apply, String]()

  // Map mapName => MapDef
  protected var mapDefs = Map[String, M3.MapDef]() 
}
