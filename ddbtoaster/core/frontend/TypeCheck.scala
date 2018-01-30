package ddbt.frontend

import ddbt.ast._

/**
  * Fixes the M3 parse result to provide a correct AST and annotates 
  * the AST with appropriate types needed for code generation.
  *
  * @author Thierry Coppey, Milos Nikolic
  */
object TypeCheck extends (M3.System => M3.System) {

  import ddbt.lib.Utils.{ fresh, freshClear, delta }
  import M3._

  def err(msg: String) = sys.error("Type checking error: " + msg)

  def getTargetMaps(s0: Statement): List[MapRef] = s0 match {
    case s: TriggerStmt => List(s.target)
    case s: IfStmt => s.thenBlk.flatMap(getTargetMaps) ++ s.elseBlk.flatMap(getTargetMaps)
  }

  // 1. Add used tables and batch updates as maps
  def addMissingMaps(s0: System) = {
    val accessedMaps = scala.collection.mutable.Set[String]()

    // Replace access by MapRefs (M3 fix?)
    def replaceExpr(e: Expr): Expr = e.replace {
      case MapRefConst(n, ks) =>
        accessedMaps += n
        MapRef(n, TypeInt, ks)
      case DeltaMapRefConst(n, ks) =>
        accessedMaps += delta(n)
        MapRef(delta(n), TypeInt, ks)
    }
    
    def replaceStmt(s0: Statement): Statement = s0 match {
      case s: TriggerStmt => 
        TriggerStmt(s.target, replaceExpr(s.expr), s.op, s.initExpr.map(replaceExpr))
      case s: IfStmt =>
        IfStmt(Cmp(replaceExpr(s.cond.l), replaceExpr(s.cond.r), s.cond.op),
          s.thenBlk.map(replaceStmt), s.elseBlk.map(replaceStmt))
    }

    def toLowerCase(fields: List[(String, Type)]) = 
      fields.map { case (n, t) => (n.toLowerCase, t) }

    val queries = s0.queries.map { q => Query(q.name, replaceExpr(q.expr)) }
    
    val triggers = s0.triggers.map { t => Trigger(t.event, t.stmts.map(replaceStmt)) }

    val usedTableDefs = s0.sources.filter { s => 
        !s.isStream && accessedMaps.contains(s.schema.name)
      }.map { s => 
        MapDef(s.schema.name, TypeInt, toLowerCase(s.schema.fields), Const(TypeInt, "0"), LocalExp)
      } 
    val usedDeltaDefs = 
      s0.sources.filter { s =>
        s.isStream && accessedMaps.contains(delta(s.schema.name))
      }.map { s =>
        MapDef(delta(s.schema.name), TypeInt, toLowerCase(s.schema.fields), Const(TypeInt, "0"), LocalExp)
      }

    System(s0.sources, s0.maps ::: usedTableDefs ::: usedDeltaDefs, queries, triggers)
  }

  // 2. Prettify variable names (not streams, not maps) 
  //    using a renaming function
  // 3. Rename M3 functions into implementation functions: 
  //    converting to lower case
  def renameVarsAndFuns (vn: String => String, fn: String => String) (s0: System) = {
    val globalMaps = s0.maps.map(_.name).toSet
    var localMapRenaming: Map[String, String] = null

    def renameKeys(keys: List[(String, Type)]) = 
      keys.map { case (n, t) => (vn(n), t) }

    def renameSchema(s: Schema) = 
      Schema(s.name, renameKeys(s.fields))

    def renameExpr(e: Expr): Expr = e.replace {
      case Ref(n) => 
        Ref(vn(n))
      case MapRef(n, tp, ks, tmp) => 
        MapRef(localMapRenaming.getOrElse(n, n), tp, renameKeys(ks), tmp)
      case DeltaMapRefConst(n, ks) => 
        MapRef(delta(n), TypeInt, renameKeys(ks))
      case Lift(n, e) => 
        Lift(vn(n), renameExpr(e))
      case AggSum(ks, e) => 
        AggSum(renameKeys(ks), renameExpr(e))
      case Repartition(ks, e) => 
        Repartition(renameKeys(ks), renameExpr(e))
      case Apply(f, tp, args) =>  
        Apply(fn(f), tp, args.map(renameExpr))
    }

    def renameStmt(s0: Statement): Statement = s0 match {
      case s: TriggerStmt =>
        TriggerStmt(
          renameExpr(s.target).asInstanceOf[MapRef],
          renameExpr(s.expr),
          s.op,
          s.initExpr.map(renameExpr)
        )
      case s: IfStmt =>
        IfStmt(
          Cmp(renameExpr(s.cond.l), renameExpr(s.cond.r), s.cond.op),
          s.thenBlk.map(renameStmt),
          s.elseBlk.map(renameStmt)
        )
    }

    val sources = s0.sources.map { case Source(st, sch, in, sp, ad, loc) => 
      Source(st, renameSchema(sch), in, sp, ad, loc)
    }

    val triggers = s0.triggers.map { t =>
      localMapRenaming = 
        t.stmts.flatMap(getTargetMaps).map(_.name).filterNot(globalMaps.contains)
               .map { n => (n -> (n + "_" + fresh("local"))) }
               .toMap
      Trigger(
        t.event match {
          case EventInsert(s) => EventInsert(renameSchema(s))
          case EventDelete(s) => EventDelete(renameSchema(s))
          case EventBatchUpdate(s) => EventBatchUpdate(renameSchema(s))
          case e => e
        },
        t.stmts.map(renameStmt)
      )
    }
    
    val queries = s0.queries.map { q => Query(q.name, renameExpr(q.expr)) }
    
    System(sources, s0.maps, queries, triggers)
  }

  // 4. Type trigger arguments by binding to the corresponding input schema
  // 5. Type untyped maps definitions (using statements left hand-side) 
  //    (M3 language fix)
  def typeMaps(s0: System) = {
    val schemaMap = s0.sources.map { s => (s.schema.name, s.schema) }.toMap

    def fixSchema(s: Schema): Schema = schemaMap.get(s.name) match {
      case Some(s2) =>
        if (s.fields.nonEmpty && s.fields.map(_._1) != s2.fields.map(_._1)) {
          err("Trigger param names do not match schema field names: " + s + " vs. " + s2)
        }
        s2
      case None => err("Trigger input not found " + s)
    }
    
    val triggers = s0.triggers.map { t => 
      Trigger(t.event match {
        case EventInsert(s) => EventInsert(fixSchema(s))
        case EventDelete(s) => EventDelete(fixSchema(s))
        case EventBatchUpdate(s) => EventBatchUpdate(fixSchema(s))
        case EventReady => EventReady
      }, t.stmts)
    }

    val mapTypes = triggers.flatMap { t =>
      t.stmts.flatMap(getTargetMaps).map(m => (m.name, m.tp))
    }.toMap
   
    val maps = s0.maps.map { m => 
      val t0 = mapTypes.getOrElse(m.name, null)
      val t1 = m.tp
      val tp = if (t0 == null && t1 != null)
                 t1 
               else if (t1 == null && t0 != null)
                 t0
               else if (t0 != t1)
                 sys.error("Map " + m.name + " type differs (" + t0 + " != " + t1 + ")")
               else if (t0 == null)
                 sys.error("Map " + m.name + " has no type")
               else t0
      MapDef(m.name, tp, m.keys, m.expr, m.locality)
    }

    System(s0.sources, maps, s0.queries, triggers)
  }

  // 6. Rename lifted variables to avoid name clashes when code gets flattened.
  // We "lock" input args, output keys and aggregation variables from being renamed
  // Example: Mul(Lift(a,3),Mul(a,Mul(Lift(a,2),a))) => 6
  def renameLifts(s0: System) = {

    def renameExpr(e: Expr, locked: Set[String]): Expr = e.replace {
      case AggSum(ks, sub0) => 
        val ivars = sub0.schema._1
        val lck = locked ++ (ivars ++ ks).map(_._1).toSet
        val sub = renameExpr(sub0, lck)
        val ovars = sub.schema._2.map(_._1).toSet
        val lifts = sub.collect { case Lift(v, _) => List(v) }
        val mapping = lifts.filter(l => ovars.contains(l) && !lck.contains(l))
                           .map((_, fresh("lift"))).toMap
        AggSum(ks, sub.rename(mapping))
    }
    
    def renameStmt(s0: Statement, locked: Set[String] = Set()): Statement = s0 match { 
      case TriggerStmt(target, expr, op, initExpr) =>
        val lck = locked ++ target.keys.map(_._1).toSet
        TriggerStmt(
          target, 
          renameExpr(expr, lck), 
          op, 
          initExpr.map(e => renameExpr(e, lck))
        )
      case IfStmt(cond, thenBlk, elseBlk) =>
        IfStmt(
          Cmp(renameExpr(cond.l, locked), renameExpr(cond.r, locked), cond.op),
          thenBlk.map(s => renameStmt(s, locked)),
          elseBlk.map(s => renameStmt(s, locked))
        )
    }
    
    val triggers = s0.triggers.map { t =>
      val locked = t.event.params.map(_._1).toSet
      Trigger(t.event, t.stmts.map(s => renameStmt(s, locked)))
    }
    
    val queries = s0.queries.map(q => Query(q.name, renameExpr(q.expr, Set())))
    
    freshClear()
    
    System(s0.sources, s0.maps, queries, triggers)
  }

  // 7. Resolve missing types (and also make sure operations are correctly typed)
  def typeCheck(s0: System) = {

    val mapTypes: Map[String, (List[Type], Type)] =
      s0.maps.map { m => (m.name, (m.keys.map(_._2), m.tp)) }.toMap

    def resolveType(tp1: Type, tp2: Type) = tp1.resolve(tp2)

    // give a type to all untyped nodes
    def typeExpr(expr: Expr, ctx0: Map[String, Type], t: Option[Trigger]): Map[String, Type] = {
      var ctxRet = ctx0 // new bindings
      try {
        expr match { 
          case m @ Mul(l, r) => 
            ctxRet = typeExpr(r, typeExpr(l, ctx0, t), t)
            m.tp = resolveType(l.tp, r.tp)
          case a @ Add(l, r) =>
            val lfree = typeExpr(l, ctx0, t).filter { case (n, t) => !ctx0.contains(n) }
            val rfree = typeExpr(r, ctx0, t).filter { case (n, t) => !ctx0.contains(n) }
            ctxRet = ctx0 ++ lfree ++ rfree
            a.tp = resolveType(l.tp, r.tp)
          case Cmp(l, r, _) => 
            ctxRet = typeExpr(l, ctx0, t) ++ typeExpr(r, ctx0, t)
            resolveType(l.tp, r.tp)   // check types
          case CmpOrList(l, rl) =>
            ctxRet = typeExpr(l, ctx0, t) ++ rl.flatMap(x => typeExpr(x, ctx0, t))
            rl.foreach(r => resolveType(l.tp, r.tp))   // check types
          case Exists(e) =>
            ctxRet = typeExpr(e, ctx0, t)
          case Lift(n, e) =>
            ctxRet = typeExpr(e, ctx0, t)
            ctx0.get(n) match {
              case Some(t) => 
                try { 
                  resolveType(t, e.tp) 
                }
                catch {
                  case _: TypeMismatchException => 
                    err("Value " + n + " lifted as " + t + " compared with " + e.tp)
                }
              case None => ctxRet = ctxRet + ((n, e.tp))
            }
          case a @ AggSum(ks, e) =>
            val subctx = typeExpr(e, ctx0, t)
            ctxRet = ctx0 ++ ks.map { case (n, _) => (n, subctx(n)) }
            a.keys = ks.map { case (n, _) => (n, ctxRet(n)) }   // resolved types
          case a @ Apply(n, tp, args) => 
            args.map(typeExpr(_, ctx0, t))
            a.tp = Library.typeCheck(n, args.map(_.tp))
          case r @ Ref(n) => 
            r.tp = ctx0(n)
          case m @ MapRef(n, tp, ks, tmp) =>
            mapTypes.get(n) match {
              case Some((mktps, mtp)) =>
                ctxRet = ctx0 ++ ((ks.map(_._1)) zip mktps).toMap
                if (tp == null) m.tp = mtp
                else if (tp != mtp) {
                  err("Bad value type: expected " + mtp + ", got " + tp + " for " + expr)
                }
                m.keys = (ks zip mktps).map { case ((n, _), t) =>
                  if (ctx0.contains(n) && !Library.cast(ctx0(n), t)) {
                    err("Key type (" + n + ") mismatch in " + expr + ", tp1: " + ctx0(n) + "  tp2: " + t)
                  }
                  (n, t)
                }
              case None => sys.error("Unknown map type: " + expr)
            }
          case r @ Repartition(ks, e) => 
            ctxRet = typeExpr(e, ctx0, t)
            r.ks = ks.map { case (n, _) => (n, ctxRet(n)) }   // resolved types  
          case Gather(e) => 
            ctxRet = typeExpr(e, ctx0, t)  
          case Tuple(es) => 
            es.foreach(e => ctxRet = typeExpr(e, ctxRet, t))
          case TupleLift(ns, e) => 
            ctxRet = typeExpr(e, ctx0, t)
          case _ =>
        }
        if (expr.tp == null) err("Untyped: " + expr)
      }
      catch {
        case ex: TypeMismatchException => err(ex + " Expression: " + expr)
      }
      ctxRet      
    }
    
    def typeStmt(s0: Statement, ctx: Map[String, Type] = Map(), t: Option[Trigger]): Statement = s0 match {
      case TriggerStmt(target, expr, op, initExpr) =>
        // TODO: avoid state mutation
        typeExpr(expr, ctx, t)
        initExpr.map(e => typeExpr(e, ctx, t))
        typeExpr(target, ctx, t)
        
        // Check if target and init expr are of same type
        initExpr.foreach(ie =>
          if (!Library.cast(ie.tp, target.tp))
            err("Type mismatch in map " + target.toDecoratedString + " of type " + target.tp +
                " and init expression " + ie.toDecoratedString + " of type " + ie.tp))
        
        // Check if target and expr are of same type
        if (!Library.cast(expr.tp, target.tp))
          err("Type mismatch in map " + target.toDecoratedString + " of type " + target.tp +
              " and RHS expression " + expr.toDecoratedString + " of type " + expr.tp)
        
        TriggerStmt(target, expr, op, initExpr)

      case IfStmt(cond, thenBlk, elseBlk) =>
        // TODO: avoid state mutation
        typeExpr(cond, ctx, t)
        thenBlk.map(s => typeStmt(s, ctx, t))
        elseBlk.map(s => typeStmt(s, ctx, t))
        IfStmt(cond, thenBlk, elseBlk)
    }
    
    val triggers = s0.triggers.map { t =>
      val ctx = t.event.params.toMap
      Trigger(t.event, t.stmts.map(s => typeStmt(s, ctx, Some(t))))
    }
    
    // Set type and keys of each query
    val queries = s0.queries.map { q =>
      typeExpr(q.expr, Map(), None)
      Query(q.name, q.expr)
    }

    System(s0.sources, s0.maps, queries, triggers)
  }

  def apply(s: System) = {
    val phases = 
      addMissingMaps _ andThen
      renameVarsAndFuns(
        (s: String) => s.toLowerCase, 
        (s: String) => Map(("/","div")).getOrElse(s, s)
      ) andThen
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
  import M3._

  // available functions (overloaded included) as 
  // userName -> (callName, [retType, paramTypes])
  private val functions = 
    new collection.mutable.HashMap[String, (String, List[(Type, List[Type])])]()

  // min # of arguments
  private val minArgs = new collection.mutable.HashMap[String, Int]()

  private def typeOf[T](c: Class[T]) = c.toString match {
    case "char"   => TypeChar
    case "short"  => TypeShort
    case "int"    => TypeInt
    case "long"   => TypeLong
    case "float"  => TypeFloat
    case "double" => TypeDouble
    case "class java.lang.String" => TypeString
    case "class java.util.Date" => TypeDate
    case _ => null
  }

  // Test if name is a library function (used by parser)
  def apply(name: String) = functions.contains(name.toLowerCase)

  def typeCheck(name: String, args: List[Type]): Type = {
    if (!functions.contains(name)) {
      sys.error("Library: no such function: " + name)
    }

    val numArgs = args.size
    val argMin = minArgs.getOrElse(name, 0)
    if (numArgs < argMin) {
      sys.error("Library: not enough argument for " + name + 
                " (expected " + argMin + 
                ", provided " + numArgs + ")")
    }

    val (_, signatures) = functions(name)
    val candidates = signatures.filter(_._2.size >= numArgs)
    if (candidates.isEmpty) {
      sys.error("Library: too many argument for " + name +
                " (expected " + signatures.maxBy(_._2.size) + 
                ", provided " + numArgs + ")")
    } 
    // exact matching  
    candidates.foreach { 
      case (retType, paramTypes) => 
        if ((true /: (args zip paramTypes)) { case (c, (t1, t2)) => c && t1 == t2 })
          return retType
    } 
    // matching with cast
    candidates.foreach { 
      case (retType, paramTypes) => 
        if ((true /: (args zip paramTypes)) { case (c, (t1, t2)) => c && cast(t1, t2) })
          return retType
    }
    sys.error("Library: bad arguments for " + name + 
              ": got <" + args.mkString(", ") + "> expected " + 
              signatures.map { case (_, paramTypes) => 
                "<" + paramTypes.mkString(", ") + ">" 
              }.mkString(", "))
    null
  }

  private def inspect[T](obj: T, namePrefix: String = null, callPrefix: String = null) {
    val methods = 
      obj.getClass.getMethods
        .filter(m => (m.getModifiers() & java.lang.reflect.Modifier.PUBLIC) != 0)
        .filter(m => namePrefix == null || m.getName.startsWith(namePrefix))

    methods.foreach { m =>
      val retType = typeOf(m.getReturnType)
      val paramTypes = m.getParameterTypes.toList.map(t => typeOf(t))

      if (retType != null && !paramTypes.contains(null)) {
        val name = m.getName
        val userName = if (namePrefix != null) name.substring(namePrefix.length) else name
        val callName = if (callPrefix != null) callPrefix + "." + name else name

        // default argument <i> of <f> is a val named <f>$default$<i> where i=1,2,3...
        val idx = userName.indexOf("$default$")
        if (idx == -1) {
          functions.get(userName) match {
            case Some((cn, signatures)) =>
              // overloaded function
              functions += (userName -> (callName, (retType, paramTypes) :: signatures))
            case None =>
              functions += (userName -> (callName, List((retType, paramTypes))))
          }
        } 
        else { 
          // min #arguments required for this function = min(in-1) forall in
          val fn = userName.substring(0, idx)
          val i = userName.substring(idx + 9).toInt - 1
          
          minArgs += (fn -> Math.min(i, minArgs.getOrElse(fn, i)))
        }
      }
    }
  }

  // Implicit castings allowed by second-stage compiler ('a' can be promoted to 'b'?)
  def cast(a: Type, b: Type) = 
    try { b == a.resolve(b) } 
    catch { case TypeMismatchException(msg) => false }

  inspect(ddbt.lib.Functions, "U")
}
