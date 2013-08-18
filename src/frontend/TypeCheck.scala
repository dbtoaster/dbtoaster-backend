package ddbt.frontend
import ddbt.ast._

/**
 * This function is responsible to fix the M3 parse result to provide a correct
 * AST and annotate it with appropriate types required for the code generation.
 * @author TCK
 */
object TypeCheck extends (M3.System => M3.System) {
  import ddbt.ast.M3._
  import ddbt.Utils.{fresh,freshClear}
  @inline def err(msg:String) = sys.error("Type checking error: "+msg)

  // 1. Add used (constant) tables in maps, replace access by MapRefs (M3 fix?)
  def addTables(s0:System) = {
    val tabs = s0.sources.filter{!_.stream}.map{ s=>(s.schema.name,s.schema.fields) }.toMap
    var used = Set[String]() // accessed tables
    def re(e:Expr):Expr = e.replace { case Tuple(t,ks) => used+=t; MapRef(t, TypeLong, ks) }
    def rst(s:Stmt):Stmt = s match { case StmtMap(m,e,op,in) => StmtMap(m,re(e),op,in map re) }
    val triggers = s0.triggers.map {
      case TriggerReady(ss) => TriggerReady(ss map rst)
      case TriggerAdd(sc,ss) => TriggerAdd(sc,ss map rst)
      case TriggerDel(sc,ss) => TriggerDel(sc,ss map rst)
    }
    val tabMaps = s0.sources.filter{s=> !s.stream && used.contains(s.schema.name) }.map{ so=>
      val s=so.schema; MapDef(s.name, TypeLong, s.fields, Const(TypeLong,"0L"))
    }
    System(s0.sources,tabMaps:::s0.maps,s0.queries,triggers)
  }

  // 2. Prettify variable names (not streams, not maps) using a renaming function
  // 3. Rename M3 functions into implementation functions
  def renameVarsAndFuns(r:String=>String, fn:String=>String)(s0:System) = {
    def rs(s:Schema) = Schema(s.name,s.fields.map{case(n,t)=>(r(n),t)})
    def re(e:Expr):Expr = e.replace {
      case Ref(n) => Ref(r(n))
      case MapRef(n,tp,ks) => MapRef(n,tp,ks.map(r))
      case Lift(n,e) => Lift(r(n),re(e))
      case AggSum(ks,e) => AggSum(ks map r,re(e))
      case Apply(f,tp,as) => Apply(fn(f),tp,as.map(re))
    }
    def rst(s:Stmt):Stmt = s match { case StmtMap(m,e,op,in) => StmtMap(re(m).asInstanceOf[MapRef],re(e),op,in map re) }
    val sources = s0.sources.map { case Source(st,sch,in,sp,ad) => Source(st,rs(sch),in,sp,ad) }
    val triggers = s0.triggers.map {
      case TriggerReady(ss) => TriggerReady(ss map rst)
      case TriggerAdd(sc,ss) => TriggerAdd(rs(sc),ss map rst)
      case TriggerDel(sc,ss) => TriggerDel(rs(sc),ss map rst)
    }
    System(sources,s0.maps,s0.queries,triggers)
  }

  // 4. Type trigger arguments by binding to the corresponding input schema
  // 5. Type untyped maps definitions (using statements left hand-side) (M3 language fix)
  def typeMaps(s0:System) = {
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
    val mtp = triggers.flatMap(t=>t.stmts flatMap { case StmtMap(m,_,_,_)=>List(m) }).map(m=>(m.name,m.tp)).toMap ++
              s0.sources.filter{s=> !s.stream}.map{s=>(s.schema.name,TypeLong)}.toMap // constant table are not written
    val maps = s0.maps.map{ m=> val tp=mtp(m.name); assert(m.tp==null || m.tp==tp); MapDef(m.name,tp, m.keys, m.expr) }
    System(s0.sources,maps,s0.queries,triggers)
  }

  // 6. Rename lifted variables to avoid name clashes when code gets flattened.
  // We "lock" input args, output keys and aggregation variables from being renamed
  def renameLifts(s0:System) = {
    def re(e:Expr,locked:Set[String]):Expr = e.replace {
      case Mul(Lift(n,e),r) if !locked.contains(n) => e match {
        case Ref(m) if (locked.contains(m)) => Mul(re(Lift(n,e),locked),re(r,locked))
        case _ => val f=fresh("lift"); Mul(Lift(f,re(e.rename(n,f),locked+f)),re(r.rename(n,f),locked+f))
      }
      case AggSum(ks,e) => AggSum(ks,re(e,locked++ks.toSet))
    }
    def rst(s:Stmt,locked:Set[String]=Set()):Stmt = s match {
      case StmtMap(m,e,op,in) => val l=locked++m.keys.toSet; StmtMap(m,re(e,l),op,in map{x=>re(x,l)})
    }
    val triggers = s0.triggers.map {
      case TriggerReady(ss) => TriggerReady(ss map(x=>rst(x)))
      case TriggerAdd(sc,ss) => TriggerAdd(sc,ss map(x=>rst(x,sc.fields.map(_._1).toSet)))
      case TriggerDel(sc,ss) => TriggerDel(sc,ss map(x=>rst(x,sc.fields.map(_._1).toSet)))
    }
    freshClear
    System(s0.sources,s0.maps,s0.queries,triggers)
  }

  // 7. Resolve missing types (and also make sure operations are correctly typed)
  def typeCheck(s0:System) = {
    def tpRes(t1:Type,t2:Type,ex:Expr):Type = (t1,t2) match {
      case (t1,t2) if t1==t2 => t1
      case (TypeDouble,TypeLong) | (TypeLong,TypeDouble) => TypeDouble
      case _ => err("Bad operands ("+t1+","+t2+"): "+ex)
    }
    def ie(ex:Expr,c:Map[String,Type]):Map[String,Type] = {
      var cr=c; // new bindings
      ex match { // gives a type to all untyped nodes
        case m@Mul(l,r) => cr=ie(r,ie(l,c)); m.tp=tpRes(l.tp,r.tp,ex)
        case a@Add(l,r) =>
          val (fl,fr)=(ie(l,c).filter{x=> !c.contains(x._1)},ie(r,c).filter{x=> !c.contains(x._1)}) // free(l), free(r)
          a.agg=fl.filter{x=>fr.contains(x._1)}.toList // sorted(free(l) & free(r)) : a variable is bound differently in l and r => set union
          cr=c++fl++fr; a.tp=tpRes(l.tp,r.tp,ex);
        case Cmp(l,r,_) => cr=c++ie(l,c)++ie(r,c); tpRes(l.tp,r.tp,ex)
        case Exists(e) => cr=ie(e,c)
        case Lift(n,e) => ie(e,c); c.get(n) match { case Some(t) => try { tpRes(t,e.tp,ex) } catch { case _:Throwable=> err("Value "+n+" lifted as "+t+" compared with "+e.tp) } case None => cr=c+((n,e.tp)) }
        case a@AggSum(ks,e) => val in=ie(e,c); cr=c++ks.map{k=>(k,in(k))}; a.tks=ks.map(cr)
        case Apply(_,_,as) => as map {x=>ie(x,c)} // XXX: check args/return types against user-functions library
        case r@Ref(n) => r.tp=c(n)
        case m@MapRef(n,tp,ks) => val mtp=s0.mapType(n); cr=c++(ks zip mtp._1).toMap
          if (tp==null) m.tp=mtp._2 else if (tp!=mtp._2) err("Bad value type: expected "+mtp._2+", got "+tp+" for "+ex)
          (ks zip mtp._1).foreach{ case(k,t)=> if(c.contains(k) && t!=c(k)) err("Key type ("+k+") mismatch in "+ex) }
        case _ =>
      }
      if (ex.tp==null) err("Untyped: "+ex); cr
    }
    def ist(s:Stmt,b:Map[String,Type]=Map()) = s match { case StmtMap(m,e,op,in) => ie(e,b); in.map(e=>ie(e,b)) }
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
    val vn = (s:String)=>s.toLowerCase
    val fn = { val map=Map(("/","div")); (s:String)=>map.getOrElse(s,s) } // renaming of functions
    val phases = addTables _ andThen
                 renameVarsAndFuns(vn,fn) _ andThen
                 typeMaps _ andThen
                 renameLifts andThen
                 typeCheck _
    phases(s)
  }
}
