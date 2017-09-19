package ddbt.frontend

import ddbt.ast._

/**
  * Fixes the M3 parse result to provide a correct AST and annotate it
  * with appropriate types required for the code generation.
  * @author TCK
  */
object TypeCheck extends (M3.System => M3.System) {

  import ddbt.lib.Utils.{ fresh, freshClear }
  import ddbt.ast.M3._

  @inline def err(msg: String) = sys.error("Type checking error: " + msg)

  // 1. Add used (constant) tables in maps, replace access by MapRefs (M3 fix?)
  def addTables(s0: System) = {
    var used = Set[String]() // accessed tables
    def re(e: Expr): Expr = e.replace {
      case MapRefConst(n, ks) =>
        used += n
        MapRef(n, TypeLong, ks)
      case d @ DeltaMapRefConst(_, ks) =>
        used += d.deltaName
        MapRef(d.deltaName, TypeLong, ks)
    }
    def rst(s: Stmt): Stmt = s match {
      case StmtMap(m, e, op, in) => 
        StmtMap(m, re(e), op, in map re)
      case MapDef(n, tp, ks, e, l) => 
        MapDef(n, tp, ks, if (e != null) re(e) else e, l)
    }
    val triggers = s0.triggers.map { t => Trigger(t.event, t.stmts map rst) }
    val queries = s0.queries.map { q => Query(q.name, re(q.map)) }
    val tabMaps = s0.sources.filter { s => 
        !s.stream && used.contains(s.schema.name) 
      }.map { so =>
        val s = so.schema
        MapDef(s.name, TypeLong, s.fields, Const(TypeLong, "0L"), LocalExp) 
      }
    System(s0.sources, tabMaps ::: s0.maps, queries, triggers)
  }

  // 2. Prettify variable names (not streams, not maps) 
  //    using a renaming function
  // 3. Rename M3 functions into implementation functions: 
  //    converting to lower case
  def renameVarsAndFuns (r: String => String, fn: String => String) 
                        (s0: System) = {
    val localMaps = new scala.collection.mutable.HashMap[String,String]
    def rs(s: Schema) = Schema(s.name, s.fields.map { case (n, t) => (r(n), t) })
    def re(e: Expr, t: Trigger): Expr = e.replace {
      case Ref(n) => Ref(r(n))
      case MapRef(n, tp, ks, tmp) =>
        MapRef(localMaps.get(n).getOrElse(n), tp, ks.map { case (n, t) => (r(n), t) })
      case d @ DeltaMapRefConst(_, ks) => 
        MapRef(d.deltaName, TypeLong, ks.map { case (n, t) => (r(n), t) })
      case Lift(n, e) => Lift(r(n), re(e, t))
      case AggSum(ks, e) => AggSum(ks map { case (n, t) => (r(n), t) }, re(e, t))
      case Repartition(ks, e) => Repartition(ks map { case (n, t) => (r(n), t) }, re(e, t))
      case Apply(f, tp, as) => Apply(fn(f), tp, as.map(re(_, t)))       
    }
    def localMap(name: String, t: Trigger) = {
      val newName = name + "_" + t.event.name
      localMaps += (name -> newName)
      newName
    }
    def rst(s: Stmt, t: Trigger): Stmt = s match {
      case StmtMap(m, e, op, in) => 
        StmtMap(re(m, t).asInstanceOf[MapRef], re(e, t), op, in.map(re(_, t)))
      case MapDef(n, tp, ks, e, l) => 
        MapDef(localMap(n, t), tp, ks.map(k => (r(k._1), k._2)), 
               if (e != null) re(e, t) else e,
               l match { 
                 case LocalExp => LocalExp 
                 case DistRandomExp => DistRandomExp
                 case DistByKeyExp(pk) => 
                  DistByKeyExp(pk.map(k => (r(k._1), k._2)))
               })
    }
    val sources = s0.sources.map { 
      case Source(st, sch, in, sp, ad, loc) => Source(st, rs(sch), in, sp, ad, loc) 
    }
    val triggers = s0.triggers.map { t => 
      localMaps.clear
      Trigger(t.event match {
        case EventInsert(sc) => EventInsert(rs(sc))
        case EventDelete(sc) => EventDelete(rs(sc))
        case e => e
      }, t.stmts map(s => rst(s, t)))
    }
    val queries = s0.queries.map(q => Query(q.name, re(q.map, null)))
    System(sources, s0.maps, queries, triggers)
  }

  // 4. Type trigger arguments by binding to the corresponding input schema
  // 5. Type untyped maps definitions (using statements left hand-side) 
  //    (M3 language fix)
  def typeMaps(s0: System) = {
    val schemas = s0.sources.map { s => (s.schema.name, s.schema) }.toMap
    def sch(s: Schema): Schema = schemas.get(s.name) match {
      case Some(s2) => assert(s.fields.map(_._1) == s2.fields.map(_._1)); s2
      case None => err("Trigger input not found "+s)
    }
    val triggers = s0.triggers.map(t => Trigger(t.event match {
      case EventInsert(s) => EventInsert(sch(s))
      case EventDelete(s) => EventDelete(sch(s))
      case e => e
    }, t.stmts))
    val mtp = 
      triggers.flatMap(t => t.stmts map {
        case StmtMap(m, _, _, _) => (m.name, m.tp)
        case MapDef(n, tp, ks, e, l) => (n, tp)
      }).toMap ++
      s0.sources.filter(!_.stream).map { s => 
        (s.schema.name, TypeLong)
      }.toMap // constant table are not written
    val maps = s0.maps.map { m => 
      val t0 = mtp.getOrElse(m.name,null)
      val t1 = m.tp
      val tp = 
        if (t0 == null && t1 != null) t1 
        else if (t1 == null && t0 != null) t0 
        else {
          if (t0 != t1) {
            sys.error("Map " + m.name + " type differs (" + 
              t0 + " != " + t1 + ")")
          }
          if (t0 == null) {
            sys.error("Map " + m.name + " has no type")
          }
          t0
        }
      MapDef(m.name, tp, m.keys, m.expr, m.locality)
    }
    System(s0.sources, maps, s0.queries, triggers)
  }

  // 6. Rename lifted variables to avoid name clashes when code gets flattened.
  // We "lock" input args, output keys and aggregation variables 
  // from being renamed
  // Example: Mul(Lift(a,3),Mul(a,Mul(Lift(a,2),a))) => 6
  def renameLifts(s0: System) = {
    def re(e: Expr, locked: Set[String]): Expr = e.replace {
      case AggSum(ks, sub0) => 
        val iv = sub0.schema._1
        val lck = locked ++ (iv ++ ks).map(_._1).toSet
        val sub = re(sub0, lck)
        val ov = sub.schema._2.map(_._1).toSet
        val lifts = sub.collect { case Lift(v, _) => List(v) }
        val mapping = lifts.filter(l => ov.contains(l) && !lck.contains(l))
                           .map((_, fresh("lift"))).toMap
        AggSum(ks, sub.rename(mapping))
    }
    def rst(s: Stmt, locked: Set[String] = Set()): Stmt = s match {
      case StmtMap(m, e, op, in) => 
        val lck = locked ++ m.keys.map(_._1).toSet
        StmtMap(m, re(e, lck), op, in map { x => re(x, lck) })
      case MapDef(n, tp, ks, e, l) => 
        val lck = locked ++ ks.map(_._1).toSet
        MapDef(n, tp, ks, if (e != null) re(e, lck) else e, l)
    }
    val triggers = s0.triggers.map { 
      case Trigger(e, ss) => 
        val locked = e.params.map(_._1).toSet
        Trigger(e, ss.map(x => rst(x, locked)))
    }
    val queries = s0.queries.map(q => Query(q.name, re(q.map, Set())))
    freshClear
    System(s0.sources, s0.maps, queries, triggers)
  }

  // 7. Resolve missing types (and also make sure operations are correctly typed)
  def typeCheck(s0: System) = {
    def tpRes(t1: Type, t2: Type, ex: Expr): Type = (t1, t2) match {
      case (t1, t2) if t1 == t2 => t1 
      case (TypeLong, TypeDate) | (TypeDate, TypeLong) => TypeLong
      case (TypeDouble, TypeLong) | (TypeLong, TypeDouble) => TypeDouble
      case _ => err("Bad operands (" + t1 + ", " + t2 + "): " + ex)
    }
    //c: context
    def ie(ex: Expr, c: Map[String, Type], t: Option[Trigger]): Map[String, Type] = {
      var cr = c; // new bindings
      ex match { // gives a type to all untyped nodes
        case m @ Mul(l, r) => 
          cr = ie(r, ie(l, c, t), t)
          m.tp = tpRes(l.tp, r.tp, ex)
        case a @ Add(l, r) =>
          val (fl, fr) = 
            (ie(l, c, t).filter { x => !c.contains(x._1) }, 
             ie(r, c, t).filter { x => !c.contains(x._1) }) // free(l), free(r)
          // sorted(free(l) & free(r)) : a variable is bound 
          // differently in l and r => set union
          cr = c ++ fl ++ fr
          a.tp = tpRes(l.tp, r.tp, ex)
        case Cmp(l, r, _) => 
          cr = c ++ ie(l, c, t) ++ ie(r, c, t)
          tpRes(l.tp, r.tp, ex)
        case CmpOrList(l, r) =>
          cr = c ++ ie(l, c, t) ++ r.flatMap(x => ie(x, c, t))
        case Exists(e) => cr = ie(e, c, t)
        case Lift(n,e) => 
          cr = ie(e, c, t)
          c.get(n) match { 
            case Some(t) => 
              try { tpRes(t, e.tp, ex) } 
              catch { 
                case _: Throwable => 
                  err("Value " + n + " lifted as " + t + 
                      " compared with " + e.tp) 
              } 
            case None => cr = cr + ((n, e.tp))
          }
        case a @ AggSum(ks, e) =>
          val in = ie(e, c, t)
          cr = c ++ ks.map { case (n, t) => (n, in(n)) }
          a.keys = ks.map { case (n, _) => (n, cr(n)) }   // resolved types
        case a @ Apply(n, ss, as) => 
          as.map(ie(_, c, t))         
          a.tp = Library.typeCheck(n, as.map(_.tp))
        case r @ Ref(n) => r.tp = c(n)
        case m @ MapRef(n, tp, ks, tmp) =>
          s0.mapType.get(n) match {
            case Some(mtp) =>
              cr = c ++ ((ks.map(_._1)) zip mtp._1).toMap
              if (tp == null) m.tp = mtp._2 
              else if (tp != mtp._2) {
                err("Bad value type: expected " + mtp._2 + 
                    ", got " + tp + " for " + ex)
              }              
              m.keys = (ks zip mtp._1).map { case ((n, _), t) => 
                if (c.contains(n) && t != c(n)) {
                  err("Key type (" + n + ") mismatch in " + ex) 
                }
                (n, t) 
              }
            case None => 
              if (n.startsWith("DELTA_")) { //delta relation
                val relName = n.substring("DELTA_".length)
                val rel = s0.sources.filter(s => s.schema.name == relName)(0)
                cr = c ++ rel.schema.fields.toMap
                if (tp == null) m.tp = TypeLong 
                else if (tp != TypeLong) { 
                  err("Bad value type: expected " + TypeLong + 
                      ", got " + tp + " for " + ex)
                }
                rel.schema.fields.foreach { 
                  case(k, t) => if (c.contains(k) && t != c(k)) 
                    err("Key type (" + k + ") mismatch in " + ex) 
                }
                m.keys = (ks zip rel.schema.fields.map(_._2)).map { case ((n, _), t) => (n, t) }
              } 
              else { //local map def
                s0.triggers.filter(_ == t.getOrElse(null)).foreach { trig =>
                  trig.stmts.foreach { 
                    case MapDef(md_n, md_tp, md_ks, _, _) if (md_n == n) =>
                      cr = c ++ md_ks.toMap
                      if (tp == null) m.tp = md_tp 
                      else if (tp != md_tp) {
                        err("Bad value type: expected " + md_tp + 
                            ", got " + tp + " for " + ex)
                      }
                      md_ks.foreach { 
                        case(k, tp) => if(c.contains(k) && tp != c(k)) {
                          err("Key type (" + k + ") mismatch in " + ex) 
                        }
                      }
                      m.keys = (ks zip (md_ks.map(_._2))).map { case ((n, _), t) => (n, t) }
                    case _ => //ignore
                  }
                }
              } 
          }
        case r @ Repartition(ks, e) => 
          cr = ie(e, c, t)
          r.ks = ks.map { case (n, _) => (n, cr(n)) }   // resolved types  
        case Gather(e) => cr = ie(e, c, t)  
        // Tupling
        case Tuple(es) => es.foreach(e => cr = ie(e, cr, t))
        case TupleLift(ns, e) => cr = ie(e, c, t)
        case _ =>
      }
      if (ex.tp == null) err("Untyped: " + ex)
      cr
    }
    def ist(s:Stmt,b:Map[String,Type]=Map(),t:Option[Trigger]) = s match {
      case StmtMap(m, e, op, in) => 
        ie(e, b, t)
        in.map(e => ie(e, b, t))
        ie(m, b, t)
      case MapDef(n, tp, ks, e, l) => if (e != null) ie(e, b, t) // XXX ie(MapRef(...),b,t)
    }
    s0.triggers.foreach { t=> t.stmts foreach (x => ist(x, t.event.params.toMap, Some(t))) }
    s0.queries.foreach {
      q => {
        val m = ie(q.map, Map(), None)
        q.tp = q.map.tp
        val (_, ov) = q.map.schema
        q.keys = ov.map { case (n, t) => 
          // Sanity check
          if (t != m(n)) sys.error("Type mismatch in " + q)
          (n, t)
        }
      }
    }
    s0
  }

  // XXX: introduce a per-trigger subexpressions lifting (detect subexpression where all variables are bound by trigger arguments only)
  // XXX: introduce a unique factorization of expression to simplify expressions if possible. Use case: TPCH13 -> 2/4 maps can be removed in each trigger.
  // XXX: Some names are long, improve renaming function (use mapping/regexp to simplify variable names)
  def apply(s: System) = {
    val vn = (s: String) => s.toLowerCase
    val fn = { 
      val map = Map(("/","div"))
      (s: String) => map.getOrElse(s, s) 
    } // renaming of functions
    val phases = addTables _ andThen
                 renameVarsAndFuns(vn, fn) andThen
                 typeMaps andThen
                 renameLifts andThen
                 typeCheck
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
  private val funs = 
    new java.util.HashMap[String, (String, List[(Type, List[Type])])]()
  private val argm = new java.util.HashMap[String, Int]() // min # of arguments

  private def typeof[T](c: Class[T]) = c.toString match {
    case /*"char" | "short" | "int" |*/ "long" => TypeLong
    case /*"float" |*/ "double" => TypeDouble
    case "class java.lang.String" => TypeString
    // case "class java.util.Date" => TypeDate
    case _ => null
  }

  // Tests whether a name is part of the library functions (used by parser)
  def apply(s: String): Boolean = funs.get(s.toLowerCase) != null

  private def inspect[T](obj: T, namePrefix: String = null, callPrefix: String = null) {
    val c = obj.getClass
    val ms0 = c.getMethods.filter {
      m => (m.getModifiers() & java.lang.reflect.Modifier.PUBLIC) != 0
    }
    val ms = if (namePrefix != null) ms0.filter { 
      m => m.getName.startsWith(namePrefix)
    } 
    else ms0
    ms.foreach { m =>
      val rt = typeof(m.getReturnType)
      val at = m.getParameterTypes.toList.map(a => typeof(a))
      if (rt != null && !at.contains(null)) {
        val n = m.getName
        val un = if (namePrefix != null) n.substring(namePrefix.length) else n
        val cn = if (callPrefix != null) callPrefix + "." + n else n
        val p = un.indexOf("$default$")
        if (p == -1) {
          if (!funs.containsKey(un)) funs.put(un, (cn, List((rt, at))))
          else { 
            val ts = funs.get(un)._2
            funs.put(un, (cn, (rt, at) :: ts)) 
          } // overloaded
        } 
        else { 
          // min #arguments required for this function = min(in-1) forall in
          val (fn, i) = (un.substring(0, p), un.substring(p + 9).toInt - 1)
          argm.put(
            fn, 
            if (!argm.containsKey(fn)) i else Math.min(argm.get(fn), i)
          )
        }
      }
    }
  }

  // Implicit castings allowed by second-stage compiler
  private def cast(a: Type, b: Type) = 
    (a == b) || (a == TypeDate && b == TypeLong) ||
    (a == TypeLong && b == TypeDouble)

  def typeCheck(name: String, as: List[Type]): Type = {
    if (!funs.containsKey(name)) {
      sys.error("Library: no such function: " + name)
    }
    val ft = funs.get(name)._2
    val an = as.size
    val amin = if (argm.containsKey(name)) argm.get(name) else 0
    if (an < amin) {
      sys.error("Library: not enough argument for " + name + 
                " (expected " + amin + ")")
    }
    val cs = ft.filter(_._2.size >= an) // candidates prototypes (ret,args)
    if (cs.size == 0) {
      sys.error("Library: too many argument for " + name +
                " (expected " + ft.maxBy(_._2.size) + ")")
    }
    cs.foreach { 
      case (r, ats) => 
        if ((true /: (as zip ats)) { case (c, (t1, t2)) => c && t1 == t2 })return r 
    } // exact matching
    cs.foreach{ 
      case (r, ats) => 
        if ((true /: (as zip ats)) { case (c, (t1, t2)) => c && cast(t1, t2) })
          return r 
    } // matching with cast
    sys.error("Library: bad arguments for " + name + 
              ": got <" + as.mkString(",") + "> expected " + 
              ft.map{ case (_, tas) => "<" + 
              tas.mkString(",") + ">" }.mkString(","))
    null
  }

  inspect(ddbt.lib.Functions, "U")

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
