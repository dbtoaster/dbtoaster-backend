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
    val triggers = s0.triggers.map(t=>Trigger(t.evt,t.stmts map rst))
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
    val triggers = s0.triggers.map(t => Trigger(t.evt match {
      case EvtAdd(sc) => EvtAdd(rs(sc))
      case EvtDel(sc) => EvtDel(rs(sc))
      case e => e
    }, t.stmts map rst))
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
    val triggers=s0.triggers.map(t=>Trigger(t.evt match {
      case EvtAdd(s) => EvtAdd(sch(s))
      case EvtDel(s) => EvtDel(sch(s))
      case e => e
    },t.stmts))
    val mtp = triggers.flatMap(t=>t.stmts flatMap { case StmtMap(m,_,_,_)=>List(m) }).map(m=>(m.name,m.tp)).toMap ++
              s0.sources.filter{s=> !s.stream}.map{s=>(s.schema.name,TypeLong)}.toMap // constant table are not written
    val maps = s0.maps.map{ m=> val t0=mtp.getOrElse(m.name,null); val t1=m.tp;
      val tp=if (t0==null && t1!=null) t1 else if (t1==null && t0!=null) t0 else {
        if (t0!=t1) sys.error("Map "+m.name+" type differs ("+t0+" != "+t1+")")
        if (t0==null) sys.error("Map "+m.name+" has no type"); t0
      }
      MapDef(m.name,tp, m.keys, m.expr)
    }
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
    val triggers = s0.triggers.map { case Trigger(e,ss) =>
      val locked = e.args.map(_._1).toSet
      Trigger(e,ss.map(x=>rst(x,locked)))
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
        case a@Apply(n,_,as) => as.map(ie(_,c)); a.tp=Library.typeCheck(n,as.map(_.tp))
        case r@Ref(n) => r.tp=c(n)
        case m@MapRef(n,tp,ks) => val mtp=s0.mapType(n); cr=c++(ks zip mtp._1).toMap
          if (tp==null) m.tp=mtp._2 else if (tp!=mtp._2) err("Bad value type: expected "+mtp._2+", got "+tp+" for "+ex)
          (ks zip mtp._1).foreach{ case(k,t)=> if(c.contains(k) && t!=c(k)) err("Key type ("+k+") mismatch in "+ex) }
          m.tks = mtp._1
        case _ =>
      }
      if (ex.tp==null) err("Untyped: "+ex); cr
    }
    def ist(s:Stmt,b:Map[String,Type]=Map()) = s match { case StmtMap(m,e,op,in) => ie(e,b); in.map(e=>ie(e,b)) }
    s0.triggers.foreach { t=> t.stmts foreach (x=>ist(x,t.evt.args.toMap)) }
    s0
  }

  // XXX: introduce a per-trigger subexpressions lifting (detect subexpression where all variables are bound by trigger arguments only)
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

/*
 * This object exposes user library methods signature to the type checker.
 * Correct referencing/inlining is the responsibility of code generator.
 */
object Library {
  // available functions as userName->(callName,retType,minArgs,argTypes)
  // default argument <i> of <f> is a val named <f>$default$<i> where i=1,2,3...
  private val funs = new java.util.HashMap[String,(String,List[(Type,List[Type])])]()
  private val argm = new java.util.HashMap[String,Int]() // min # of arguments
  private def typeof[T](c:Class[T]) = c.toString match {
    case /*"char"|"short"|"int"|*/ "long" => TypeLong
    case /*"float"|*/ "double" => TypeDouble
    case "class java.lang.String" => TypeString
    case "class java.util.Date" => TypeDate
    case _ => null
  }

  private def inspect[T](obj:T, namePrefix:String=null, callPrefix:String=null) {
    val c = obj.getClass
    val ms0 = c.getMethods.filter(m=>(m.getModifiers()&java.lang.reflect.Modifier.PUBLIC)!=0);
    val ms = if (namePrefix!=null) ms0.filter{m=>m.getName.startsWith(namePrefix)} else ms0
    ms.foreach { m =>
      val rt = typeof(m.getReturnType)
      val at = m.getParameterTypes.toList.map(a=>typeof(a))
      if (rt!=null && !at.contains(null)) {
        val n = m.getName
        val un = if (namePrefix!=null) n.substring(namePrefix.length) else n
        val cn = if (callPrefix!=null) callPrefix+"."+n else n
        val p = un.indexOf("$default$")
        if (p == -1) {
          if (!funs.containsKey(un)) funs.put(un,(cn,List((rt,at))))
          else { val ts=funs.get(un)._2; funs.put(un,(cn,(rt,at)::ts)) } // overloaded
        } else { // min #arguments required for this function = min(in-1) forall in
          val (fn,i) = (un.substring(0,p),un.substring(p+9).toInt-1)
          argm.put(fn,if (!argm.containsKey(fn)) i else Math.min(argm.get(fn),i))
        }
      }
    }
  }

  // Implicit castings allowed by second-stage compiler
  private def cast(a:Type,b:Type) = (a==b) || (a==TypeLong && b==TypeDouble)

  def typeCheck(name:String,as:List[Type]):Type = {
    if (!funs.containsKey(name)) sys.error("Library: no such function: "+name)
    val ft = funs.get(name)._2
    val an = as.size
    val amin = if (argm.containsKey(name)) argm.get(name) else 0
    if (an<amin) sys.error("Library: not enough argument for "+name+" (expected "+amin+")")
    val cs = ft.filter(_._2.size >= an) // candidates prototypes (ret,args)
    if (cs.size==0) sys.error("Library: too many argument for "+name+" (expected "+ft.maxBy(_._2.size)+")")
    cs.foreach{ case (r,ats) => if ((true /: (as zip ats)){ case (c,(t1,t2)) => c && t1==t2 }) return r } // exact matching
    cs.foreach{ case (r,ats) => if ((true /: (as zip ats)){ case (c,(t1,t2)) => c && cast(t1,t2) }) return r } // matching with cast
    sys.error("Library: bad arguments for "+name+": got <"+as.mkString(",")+"> expected "+ft.map{ case (_,tas) => "<"+tas.mkString(",")+">" }.mkString(",")); null
  }

  inspect(ddbt.lib.Functions,"U")

  /*
  // Expose runtime object functions (Scala-only)
  def setContext[T](obj:T, prefix:String="obj.") {
    funs.clear; argm.clear; inspect(ddbt.lib.Functions,"U")
    if (obj!=null) inspect(ddbt.lib.Functions,null,prefix)
  }

  // Example for inlining code generation (to be implemented in LMS)
  def codeGen(name:String,vs:List[String]):String = name match {
    case "substring" => vs(0)+".substring("+vs(1)+(if (vs.size>2) ","+vs(2) else "")+")"
    case _ => funs.get(name)._1+"("+vs.mkString(",")+")"
  }

  // Demo
  def main(args:Array[String]) {
    import collection.JavaConversions._
    println(typeCheck("substring",List(TypeString,TypeLong)))
    println(codeGen("substring",List("foo","123")))
    println("Library content:")
    funs.toMap.foreach { case (k,v) => println("%-15s".format(k)+" -> "+v+" min="+argm.get(k)) }
  }
  */

  // Annotations: http://www.veebsbraindump.com/2013/01/reflecting-annotations-in-scala-2-10/
  // Seems we can only annotate classes, not methods => cannot implement arbitrary renaming from libs
  // def Isubstring(vs:List[String]) = vs(0)+".substring("+vs(1)+(if (vs.size>2) ","+vs(2) else "")+")"
  // try { val m = libClass.getDeclaredMethod("I"+name, classOf[List[String]]); assert(m.getReturnType==classOf[String]); m.invoke(libObj,vs).asInstanceOf[String] }
  // catch { case _:Throwable => funs.get(name)._1+"("+vs.mkString(",")+")" }
}
