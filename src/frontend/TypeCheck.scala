package ddbt.frontend
import ddbt.ast._

object TypeCheck extends (M3.System => M3.System) {
  import ddbt.ast.M3._
  @inline def err(msg:String) = sys.error("Type checking error: "+msg)
  
  def renameVars(r:String=>String)(s0:System) = {
    // 1. Prettify variable names (not streams, not maps) using a renaming function
    def rs(s:Schema) = Schema(s.name,s.fields.map{case(n,t)=>(r(n),t)})
    def re(e:Expr):Expr = e.replace {
      case Ref(n) => Ref(r(n))
      case MapRef(n,tp,ks) => MapRef(n,tp,ks.map(r))
      case Lift(n,e) => Lift(r(n),re(e))
      case AggSum(ks,e) => AggSum(ks map r,re(e))
    }
    def rst(s:Stmt):Stmt = s match {
      case StmtMap(m,e,op,in) => StmtMap(re(m).asInstanceOf[MapRef],re(e),op,in map re)
    }
    val sources = s0.sources.map { case Source(st,sch,in,sp,ad) => Source(st,rs(sch),in,sp,ad) }
    val triggers = s0.triggers.map {
      case TriggerReady(ss) => TriggerReady(ss map rst)
      case TriggerAdd(sc, ss) => TriggerAdd(rs(sc),ss map rst)
      case TriggerDel(sc, ss) => TriggerDel(rs(sc),ss map rst)
    }
    System(sources,s0.maps,s0.queries,triggers)
  }

  def typeMaps(s0:System) = {
    // 2. Type trigger arguments by binding to the corresponding input schema
    val schemas=s0.sources.map{s=>(s.schema.name,s.schema)}.toMap
    def sch(s:Schema):Schema = schemas.get(s.name) match {
      case Some(s2) => assert(s.fields.map(_._1)==s2.fields.map(_._1)); s2
      case None => err("Trigger input not found "+s)
    }
    val triggers=s0.triggers.map {
      case TriggerAdd(s,sts) => TriggerAdd(sch(s),sts)
      case TriggerDel(s,sts) => TriggerDel(sch(s),sts)
      case t => t
    }
    // 3. Type untyped maps definitions (using statements left hand-side) (M3 language fix)
    val mtp = triggers.flatMap(t=>t.stmts flatMap { case StmtMap(m,_,_,_)=>List(m) }).map(m=>(m.name,m.tp)).toMap
    val maps = s0.maps.map{ m=> val tp=mtp(m.name); assert(m.tp==null || m.tp==tp); MapDef(m.name,tp, m.keys, m.expr) }
    System(s0.sources,maps,s0.queries,triggers)
  }

  def typeCheck(s0:System) = {
    def tpRes(t1:Type,t2:Type,ex:Expr):Type = (t1,t2) match {
      case (t1,t2) if t1==t2 => t1
      case (TypeDouble,TypeLong) | (TypeLong,TypeDouble) => TypeDouble
      case _ => err("Bad operands ("+t1+","+t2+"): "+ex)
    }
 
    // 4. Resolve missing types (and also make sure operations are correct)
    def ie(ex:Expr,b:Map[String,Type]):Map[String,Type] = {
      var br=b; // new bindings
      var dim=List[Type]() // dimension of result set
      ex match { // gives a type to all untyped nodes
        case m@Mul(l,r) => br=ie(r,ie(l,b)); m.tp=tpRes(l.tp,r.tp,ex); dim=l.dim:::r.dim
        case a@Add(l,r) => br=b++ie(l,b)++ie(r,b); a.tp=tpRes(l.tp,r.tp,ex); dim = if (l.dim.size>r.dim.size) l.dim else r.dim // we might union a set with one slice of smaller dimensionality
        case Cmp(l,r,_) => br=b++ie(l,b)++ie(r,b); tpRes(l.tp,r.tp,ex)
        case Exists(e) => ie(e,b)
        case Lift(n,e) => ie(e,b); b.get(n) match { case Some(t) => if (t!=e.tp) err("Value "+n+" lifted with "+t+" compared with "+e.tp) case None => br=b+((n,e.tp)) }; dim=e.dim
        case AggSum(ks,e) => br=ie(e,b); dim=ks.map(br)
        case Apply(_,_,as) => as map {x=>ie(x,b)} // XXX: Verify typing of Apply against user-functions library (additional typing informations must be provided)
        case r@Ref(n) => r.tp=b(n)
        case m@MapRef(n,tp,ks) => val mtp=s0.mapType(n); br=b++(ks zip mtp._1).toMap
          if (tp==null) m.tp=mtp._2 else if (tp!=mtp._2) err("Bad value type: expected "+mtp._2+", got "+tp+" for "+ex)
          val fv = (ks zip mtp._1).filter{ case(k,t)=> val c=b.contains(k); if (c && t!=b(k)) err("Key type ("+k+") mismatch in "+ex); !c }
          br=b++fv.toMap; m.tp=mtp._2; dim=fv.map{_._2}
        case _ =>
      }
      ex.dim = dim
      if (ex.tp==null) err("Untyped: "+ex); br
    }
    def ist(s:Stmt,b:Map[String,Type]=Map()) = s match {
      case StmtMap(m,e,op,in) => ie(e,b); in.map(e=>ie(e,b))
    }
    s0.triggers.foreach {
      case TriggerReady(ss) => ss foreach {x=>ist(x)}
      case TriggerAdd(s,ss) => ss foreach {x=>ist(x,s.fields.toMap)}
      case TriggerDel(s,ss) => ss foreach {x=>ist(x,s.fields.toMap)}
    }
    s0
  }

  // XXX: introduce a per-trigger constant expression lifting (detect subexpression where all variables are bound by trigger arguments only)
  // XXX: introduce a unique factorization of expression to simplify expressions if possible. Use case: TPCH13 -> 2/4 maps can be removed in each trigger.
  // XXX: Some names are long, improve renaming function (use mapping/regexp to simplify variable names)

  def apply(s:System) = {
    val phases = renameVars((s:String)=>s.toLowerCase) _ andThen
                 typeMaps _ andThen
                 typeCheck _
    phases(s)
  }
}
