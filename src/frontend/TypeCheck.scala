package ddbt.frontend

import ddbt.ast._
import ddbt.ast.M3._

object TypeCheck {
  def fixTypes(sys0:System) : System = {
    // 1. Bind trigger schemas to input schemas (M3 language fix)
    val schemas=sys0.sources.map{s=>(s.schema.name,s.schema)}.toMap
    def sch(s:Schema):Schema = schemas.get(s.name) match {
      case Some(s2) => assert(s.fields.map(_._1)==s2.fields.map(_._1)); s2
      case None => sys.error("Trigger input not found "+s)
    }
    val triggers=sys0.triggers.map { t=>t match {
      case TriggerAdd(s,sts) => TriggerAdd(sch(s),sts)
      case TriggerDel(s,sts) => TriggerDel(sch(s),sts)
      case _ => t
    } }
    
    // 2. Resolve untyped maps (using statements left hand-side) (M3 language fix)
    def stp(s:Stmt) = s match { case StmtMap(m,_,_,_)=>List(m) case _ => Nil }
    val mtp = triggers.flatMap(t=>t match {
      case TriggerAdd(_,ss) => ss flatMap stp
      case TriggerDel(_,ss) => ss flatMap stp
      case TriggerReady(ss) => ss flatMap stp
    }).map(m=>(m.name,m.tp)).toMap
    val maps = sys0.maps.map{ m=> val tp=mtp(m.name); assert(m.tp==null || m.tp==tp); Map(m.name,tp, m.keys, m.expr) }
    
    System(sys0.sources,maps,sys0.queries,triggers)
  }

  // 3. Typecheck deeply the tree to make sure all ops are OK
  // - MapRef must have the same type as Map
  // - MapRef keys/arguments must have the same type as Map declaration
  // - Apply: name must exist in the library, arguments type must match, return type from library
  // - usual type verifications

  // 4. Optional renaming phase for simple&unique variable names

  // 5. add information to schemas to know dimensions along which they are sliced => maintain appropriate index


// -----------------------------------------------------------------------------
// Typed internal language

// Note: the M3 language has some design issues
// - Lift(name,value) should be more explicit as Let(name,value,body)
// - Types are incomplete (see fixes in TypeCheck)
// - Some names are long






   // operations: fix m3 (resolve types)
   // - typecheck: propagate type information wherever possible
   // - compute secondary indices: need to compute bound/free variables for each element
   // - rename: use mapping and regexp to simplify variable names




/*
  def collect(e:Expr,f:Expr=>Boolean):List[Expr] = {
    val ls:List[Expr] = e match {
      case Lift(_,e1) => collect(e1,f)
      case AggSum(_,e1) => collect(e1,f)
      case Mul(l,r) => collect(l,f):::collect(r,f)
      case Add(l,r) => collect(l,f):::collect(r,f)
      case Exists(e1) => collect(e1,f)
      case Apply(_,_,as) => as.flatMap{collect(_,f)}
      case Cmp(l,r,_) => collect(l,f):::collect(r,f)
      case _ => Nil
    }
    if (f(e)) e::ls else ls
  }
*/



}
