package ddbt.codegen
import ddbt.ast.{M3,Source,Type,EvtBatchUpdate,EvtAdd,EvtDel}

/**
 * An abstraction of the code generator. Because we want to instrument generated
 * code for testability, we distinguish helper functions and core processing.
 *
 * @author TCK
 */
trait CodeGen extends (M3.System => String) {
  val cls:String="Query"
  val printProgress:Long=0L

  // Generate the system (everything but stream and views I/O)
  def apply(s:M3.System) : String

  // Stream sources definition
  def streams(sources:List[Source]) : String

  // Context maintenance helpers
  case class Ctx[T](ctx0:Map[String,T]=Map[String,T]()) extends Function1[String,T] {
    // TODO Khayyam make it private again
    var ctx = scala.collection.mutable.HashMap[String,T]()
    def add(c:Map[String,T]) = c.foreach(x=>ctx.put(x._1,x._2))
    def add(n:String,t:T) { ctx.put(n,t) }
    def load(c:Map[String,T]=Map()) { ctx.clear; add(c) }
    def save = ctx.toMap
    def contains(name:String):Boolean = apply(name)!=null
    def apply(name:String) = ctx.getOrElse(name,ctx0.getOrElse(name,null.asInstanceOf[T]))
  }
  case class CtxSet(ctx0:Set[String]=Set()) extends Function1[String,Boolean] {
    private var ctx = scala.collection.mutable.HashSet[String]()
    def add(c:Set[String]) { ctx++=c }
    def add(s:String) { ctx+=s }
    def load(c:Set[String]=Set()) { ctx.clear; c.foreach{ ctx+=_ } }
    def save = ctx.toSet
    def contains(name:String) = apply(name)
    def apply(name:String) = ctx.contains(name) || ctx0.contains(name)
  }

  def consts:String

  def constApply(a:M3.Apply):String

  // Generate (1:stream events handling, 2:table loading, 3:global constants declaration)
  def genInternals(s0:M3.System,nextSkip:String="context.become(receive_skip)") : (String,String,String)

  def toMapFunction(q: M3.Query):String

  def onEndStream:String

  def genMap(m:M3.MapDef):String

  def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String):String

  def genLMS(s0:M3.System):(String,String,String,String) = (null,null,null,null)

  def genPardis(s0:M3.System):(String, String, String) = (null, null, null)

  def clearOut:Unit

  def additionalImports():String

  def pkgWrapper(pkg:String, body:String):String

  def hasOnlyBatchProcessingForAdd(s0:M3.System, evt:EvtBatchUpdate) = s0.triggers.forall{ t => t.evt match {
      case EvtAdd(s) if(evt.schema.name == s.name) => false
      case _ => true
    }
  }

  def hasOnlyBatchProcessingForDel(s0:M3.System, evt:EvtBatchUpdate) = s0.triggers.forall{ t => t.evt match {
      case EvtDel(s) if(evt.schema.name == s.name) => false
      case _ => true
    }
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
  ==> phase after TypeCheck: union/add is disambiguated with Add.agg
  - simplifying aliases where possible
  - propagating constants
  - moving to enclosing class constant subexpressions
  - providing correct zero for types
  - mapref construction
  - avoiding duplicate get (benefitial for akka)
  - reducing aggregation of one element
  - disambiguate add/union at optimization phase ?
  - adding map slicing information
  */
}
