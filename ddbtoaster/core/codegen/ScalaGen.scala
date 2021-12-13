package ddbt.codegen

import ddbt.ast._

/**
  * ScalaGen is responsible to transform a typed AST into vanilla Scala code 
  * (String). It should be quite straightforward to use LMS to do that instead.
  *
  *
  * Implementation notes:
  * ---------------------------------------------
  * 1. We shall understand the multiply as a continuation of the left operand
  *    in the right one.
  *
  * 2. Add is more complicated than Mul as it does set union of lhs and rhs.
  *    If a free variable is present in both sides, iterate these. Concretely:
  *       f(A*B) --> A.foreach{ (k_a,v_a) => 
  *                    B.foreach { (k_b,v_b) => f(v_a * v_b) }
  *                  } 
  *       f(A+B) --> val dom = A.keySet ++ B.keySet; 
  *                  dom.foreach { k => f(A.get(k) + B.get(k)) }
  *
  *    An lighter approach to set union is:
  *       val tmp = Temp[domA(k_a) = domB(k_b) = dom -> tp(A) = tp(B)]
  *       A.foreach{ (k_a,v_a) => tmp.add(domA(k_a),v_a) }
  *       B.foreach{ (k_b,v_b) => tmp.add(domB(k_b),v_b) }
  *       tmp.foreach { (k,v) => f(v) }
  *
  * Constraints inherited from M3:
  * - Lift alone has only bound variables.
  * - In Exists * Lift, Exists binds variables for the Lift
  *
  * @author TCK
  */
object ScalaGen {

  import ddbt.lib.TypeHelper.Scala._

  val STORE_WATCHED = "StoreOps.watched"

  val VALUE_NAME = "__av"

  def tupleNameOfTps(types: List[Type]) =
    if (types.length == 1) typeToString(types.head)
    else "T" + types.map(typeToChar).mkString
}

class ScalaGen(val cgOpts: CodeGenOptions) extends IScalaGen

trait IScalaGen extends CodeGen {

  val watch = false

  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.lib.TypeHelper.Scala._
  import ddbt.lib.Utils.{ ind, tup, fresh, freshClear, stringIf, delta } // common functions

  def addToTempMap(m: String, ks: List[String], vs: String) = 
    extractBooleanExp(vs) match {
      case Some((c, t)) =>
        "(if (" + c + ") " + m + ".add(" + genTuple(ks map ctx) + ", " + t + ") else ())\n"
      case _ =>
        m + ".add(" + genTuple(ks map ctx) + ", " + vs + ")\n"
    }

  def consts: String = 
    hoistedConsts.map { case (Apply(f, tp, as), n) => 
      val vs = as.map(a => cpsExpr(a))
      "val " + n + ":" + typeToString(tp) + " = U" + f + "(" + vs.mkString(", ") + ")\n" 
    }.mkString +  // constant function applications
    regexpCacheMap.map { case (regex, preg) => 
      "val " + preg + " = java.util.regex.Pattern.compile(\"" + regex + "\");\n"
    }.mkString + "\n"

  def cmpFunc(tp: Type, op: OpCmp, arg1: String, arg2: String, withIfThenElse: Boolean = true) = tp match {
    // case TypeDouble => op match {
    //   case OpEq => "Math.abs(" + arg1 + " - " + arg2 + ") < diff_p"
    //   case OpNe => "Math.abs(" + arg1 + " - " + arg2 + ") >= diff_p"
    //   case _ => arg1 + " " + op + " " + arg2
    // }
    case _ => 
      if (withIfThenElse) 
        "(if (" + arg1 + " " + cmpToString(op) + " " + arg2 + ") 1L else 0L)"
      else
        arg1 + " " + cmpToString(op) + " " + arg2
  }

  private def cmpToString(op: OpCmp) = op match {
    case OpEq => "=="
    case OpNe => "!="
    case OpGt => ">"
    case OpGe => ">="
  }

  // extract cond and then branch of "if (cond) t else 0"
  // no better way for finding boolean type
  // TODO: add Boolean type
  def extractBooleanExp(s: String): Option[(String, String)] = 
    if (!s.startsWith("(if (")) None
    else {
      var d = 1
      val pInit = "(if (".length
      var p = pInit
      while (d > 0) {
        if (s(p) == '(') d += 1 else if (s(p) == ')') d -= 1
        p += 1
      }
      Some(s.substring(pInit, p - 1), 
           s.substring(p + 1, s.lastIndexOf("else") - 1))
    }

  // Create a variable declaration
  def genVar(n: String, tp: Type, ks: List[Type] = Nil) = 
    if (ks == Nil) "var " + n + ": " + typeToString(tp) + " = " + zeroOfType(tp) + "\n"
    else "val " + n + " = M3Map.temp[" + genTupleDef(ks) + ", " + typeToString(tp) + "]()\n"

  var tuples = Map[String, String]()

  def genTupleDef(types: List[Type]) = {
    val tupleName = ScalaGen.tupleNameOfTps(types)
    if (types.length > 1 && !(tuples contains tupleName)) {      
      def prodDef =
        "def canEqual(that: Any) = true\n" +
        "def productArity = " + types.length + "\n" +
        "def productElement(i: Int): Any = List[Any](" + 
        (1 to types.length).map("_" + _).mkString(", ") + ")(i)\n"
      
      def eqDef =
        "override def equals(o: Any) = { o match { case x: " + 
        tupleName + " => (" +
        (1 to types.length).map{ i => 
          cmpFunc(types(i - 1), OpEq, "_" + i, "x._" + i, false) 
        }.mkString(" && ") +
        ") case x: Product => if (this.productArity == x.productArity) " + 
        "(0 to (productArity - 1)).forall(i => " + 
        "x.productElement(i) == this.productElement(i)) else false " + 
        "case _ => false } }\n"+
        "override def toString() = \"<\"+List[Any](" + 
        (1 to types.length).map(i => "_"+i).mkString(",") + 
        ").mkString(\",\")+\">\"\n" +
        "override def hashCode() = {\n" +
        "  var h: Int = " + types.length + "\n" +
        (1 to types.length).map { i =>
        "  h = h * 41 + " + (types(i - 1) match {
            case TypeByte | TypeShort | TypeInt | TypeLong => "_" + i + ".toInt"
            case TypeFloat | TypeDouble => "_" + i + ".toInt"
            case _ => "_" + i + ".hashCode"
          }) + "\n"
        }.mkString +
        "  h\n" +
        "}\n"

      def classDef = 
        "class " + tupleName + "(" + types.zipWithIndex.map { 
          case(t, i) => "val _" + (i + 1) + ":" + typeToString(t) 
        }.mkString(", ") + ") extends Product {\n" +
        ind(prodDef + eqDef) + "\n}\n"

      tuples = tuples + (tupleName -> classDef)
    }
    tupleName
  }

  def genTuple(vars: List[(Type, String)]) = {
    val (types, values) = vars.unzip
    val tupleName = genTupleDef(types)
    if (vars.length == 1) vars.head._2
    else "new " + tupleName + "(" + values.mkString(", ") + ")"
  }

  def applyFunc(co: String => String, fn1: String, tp: Type, as1: List[Expr]) = {
    val (as, fn) = (fn1 match {
      case "regexp_match" if (ENABLE_REGEXP_PARTIAL_EVAL && 
                              as1.head.isInstanceOf[Const] && 
                              !as1.tail.head.isInstanceOf[Const]) => 
        val regex = as1.head.asInstanceOf[Const].v
        val preg0 = regexpCacheMap.getOrElse(regex, fresh("preg"))
        regexpCacheMap.update(regex,preg0)
        (as1.tail, "preg_match(" + preg0 + ",")
      case "date_part" => as1.head.asInstanceOf[Const].v.toLowerCase match {
          case "year"  => (as1.tail, "date_year" + "(")
          case "month" => (as1.tail, "date_month" + "(")
          case "day"   => (as1.tail, "date_day" + "(")
          case p       => throw new Exception("Invalid date part: " + p)
        }
      case _ => (as1, fn1 + "(")
    })
    // hoist constants resulting from function application
    if (as.forall(_.isInstanceOf[Const])) 
      co(hoistedConsts.getOrElseUpdate(Apply(fn1, tp, as1), fresh("c")))
    else { 
      var c = co
      as.zipWithIndex.reverse.foreach { case (a, i) => 
        val c0 = c
        c = (p: String) => cpsExpr(a, (v: String) => 
          c0(p + stringIf(i > 0, ", ") + v + stringIf(i == as.size - 1, ")")))
      }
      c("U" + fn) 
    }
  }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex: expression to convert
  //   co: delimited continuation (code with 'holes' to be filled by
  //       expression) similar to Rep[Expr] => Rep[Unit]
  //   am: shared aggregation map for Add and AggSum, avoiding useless 
  //       intermediate map where possible
  protected def cpsExpr(ex: Expr, co: String => String = (v: String) => v, 
                        am: Option[List[(String, Type)]] = None): String = ex match { 
    // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp, v) => tp match {
      case TypeLong => co(v + "L")
      case TypeChar => co("'" + v + "'")
      case TypeString => co("\"" + v + "\"")
      case _ => co(v)
    }
    case Exists(e) => 
      cpsExpr(e, (v: String) => co("(if (" + v + " != 0) 1L else 0L)"))
    case Cmp(l, r, op) => 
      cpsExpr(l, (ll: String) =>
        cpsExpr(r, (rr: String) => co(cmpFunc(l.tp, op, ll, rr))))
    case CmpOrList(l, r) =>
      assert(r.forall(_.isInstanceOf[Const]))
      cpsExpr(l, (ll: String) =>
        co("(if ((" +
          r.map(x => cpsExpr(x, (rr: String) => "(" + ll + " == " + rr + ")"))
          .mkString(" || ") +
          ")) 1L else 0L)"))

    case Apply(fn, tp, as) => applyFunc(co, fn, tp, as)
    //ki : inner key
    //ko : outer key
    //Example:
    //  f(A) {
    //    Mul(M[A,B],ex)
    //  }
    // will be translated to:
    // f(A) {
    //   M.slice(A).foreach { case (k,v) => // here A is ko
    //     val B = k._2 // here B is ki
    //     v * ex
    //   }
    // }
    case MapRef(n, tp, ks, isTemp, _) =>
      val (ko, ki) = ks.zipWithIndex.partition { case ((n, t), i) => ctx.contains(n) }
      if (ks.size == 0) { // variable
        if (ctx contains n) co(rn(n)) else co(n)
      } 
      else if (ki.size == 0) { // all keys are bound
        co(n + ".get(" + genTuple(ks map (x => ctx(x._1))) + ")")
      } 
      else { // we need to iterate over all keys not bound (ki)
        val (k0, v0) = (fresh("k"), fresh("v"))
        val sl = 
          if (ko.size > 0) 
            ".slice(" + slice(n, ko.map(_._2)) + ", " + tup(ko.map(x => rn(x._1._1))) + ")" 
          else "" // slice on bound variables
        ctx.add(ks.filter(x => !ctx.contains(x._1))
                  .map(x => (x._1, (x._2, x._1)))
                  .toMap)
        n + sl + 
        ".foreach { (" + (if (ks.size == 1) rn(ks.head._1) else k0) + ", " + v0 + ") =>\n" +
        ind(
          (if (ks.size == 1) "" 
           else ki.map { case ((n, t), i) => 
             "val " + rn(n) + " = " + k0 + "._" + (i + 1) + ";\n" 
           }.mkString) + co(v0)
        ) + "\n" +
        "}\n" // bind free variables from retrieved key
      }
    // "1L" is the neutral element for multiplication, 
    //  and chaining is done with multiplication
    case Lift(n, e) =>
    // Mul(Lift(x,3), Mul(Lift(x,4),x)) ==> (x=3; x) == (x=4; x)
      if (ctx.contains(n)) 
        cpsExpr(e, (v: String) => co(cmpFunc(TypeLong, OpEq, rn(n), v)), am)
      else e match {
        case Ref(n2) => ctx.add(n, (e.tp, rn(n2))); co("1L") // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ =>
          ctx.add(n, (e.tp, fresh("l")))
          cpsExpr(e, (v: String) => "val " + rn(n) + " = " + v + ";\n" + co("1L"), am)
      }
    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) )
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el, er) =>     
      def mul(vl: String, vr: String) = { // simplifies (vl * vr)
        def vx(vl: String, vr: String) = 
          if (vl == "1L") vr 
          else if (vr == "1L") vl 
          else "(" + vl + " * " + vr + ")"
        //pulling out the conditionals from a multiplication
        (extractBooleanExp(vl), extractBooleanExp(vr)) match {
          case (Some((cl, tl)), Some((cr, tr))) => 
            "(if (" + cl + " && " + cr + ") " + vx(tl, tr) +
            " else " + zeroOfType(ex.tp) + ")"
          case (Some((cl, tl)), _) => 
            "(if (" + cl + ") " + vx(tl, vr) + 
            " else " + zeroOfType(ex.tp) + ")"
          case (_, Some((cr, tr))) => 
            "(if (" + cr + ") " + vx(vl,tr) +
            " else " + zeroOfType(ex.tp) + ")"
          case _ => vx(vl, vr)
        }
      }
      cpsExpr(el, (vl: String) => cpsExpr(er, (vr: String) => co(mul(vl, vr)), am), am)
    // Add(el,er)
    // ==
    //   Add( (el,ctx0) -> (vl,ctx1) , (er,ctx0) -> (vr,ctx2) )
    //         <-------- L -------->    <-------- R -------->
    //    (add - if there's no free variable) ==>
    //   (v=vl+vr , ctx0)
    //    (union - if there are some free variables) ==>
    //   T = Map[....]
    //   foreach vl in L, T += vl
    //   foreach vr in R, T += vr
    //   foreach t in T, co(t)
    case a @ Add(el, er) =>
      val agg = a.schema._2.filter { case (n, t) => !ctx.contains(n) } 
      if (agg == Nil) {
        val cur = ctx.save
        cpsExpr(el, (vl: String) => {
          ctx.load(cur)
          cpsExpr(er, (vr: String) => {
            ctx.load(cur)
            co("(" + vl + " + " + vr + ")")
          }, am)
        }, am)
      } 
      else am match {
        case Some(t) if t.toSet.subsetOf(agg.toSet) =>
          val cur = ctx.save
          val s1 = cpsExpr(el, co, am)
          ctx.load(cur)
          val s2 = cpsExpr(er, co, am)
          ctx.load(cur)
          s1 + s2
        case _ =>
          val (acc, k0, v0) = (fresh("add"), fresh("k"), fresh("v"))
          val ks = agg.map(_._1)
          val ksTp = agg.map(_._2)
          val tmp = Some(agg)
          val cur = ctx.save
          val s1 = cpsExpr(el, (v: String) => addToTempMap(acc, ks, v), tmp)
          ctx.load(cur)
          val s2 = cpsExpr(er, (v: String) => addToTempMap(acc, ks, v), tmp)
          ctx.load(cur)
          genVar(acc, ex.tp, agg.map(_._2)) + s1 + s2 + cpsExpr(MapRef(acc, ex.tp, agg, true), co)
      }
    case a @ AggSum(ks, e) =>
      // aggregation keys as (name,type)
      val aks = ks.filter { case (n, t) => !ctx.contains(n) } 
      if (aks.size == 0) {
        val cur = ctx.save;
        val a0 = fresh("agg")

        genVar(a0, a.tp) +
        cpsExpr(e, (v: String) => extractBooleanExp(v) match {
          case Some((c, t)) =>
            "(if (" + c + ") " + a0 + " += " + t + " else ())\n"
          case _ =>
            a0 + " += " + v + "\n"
        }) + 
        { ctx.load(cur); co(a0) }
      } 
      else am match {
        case Some(t) if t.toSet.subsetOf(aks.toSet) => cpsExpr(e, co, am)
        case _ =>
          val a0 = fresh("agg")
          val tmp = Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = 
            "val " + a0 + " = M3Map.temp[" + genTupleDef(aks.map(_._2)) +
            ", " + typeToString(e.tp) + "]()\n" +
            cpsExpr(e, (v: String) => addToTempMap(a0, aks.map(_._1),v), tmp)
          ctx.load(cur)
          s1 + cpsExpr(MapRef(a0, e.tp, aks, true), co)
      }
    case Repartition(ks, e) => cpsExpr(e, co)
    case Gather(e) => cpsExpr(e, co)

    case _ => sys.error("Don't know how to generate " + ex)
  }

  def genStmt(s: Statement): String = s match {
    case TriggerStmt(m, e, op, oi) =>
      val (fop, sop, clear) = op match { 
        case OpAdd => ("add", " += ", "") 
        case OpSet => ("add", " = " , if (m.keys.size > 0) m.name + ".clear()\n" else "" ) 
      }
      val init = oi match {
        case Some(ie) =>
          ctx.load()
          cpsExpr(ie, (i: String) =>
            if (m.keys.size == 0) 
              "if (" + m.name + " == 0) " + m.name + " = " + i + ";\n"
            else 
              "if (" + m.name + ".get(" + genTuple(m.keys map (x => ctx(x._1))) + ") == 0) " +
              m.name + ".set(" + genTuple(m.keys map (x => ctx(x._1))) + ", " + i + ");\n"
          )
        case None => ""
      }
      ctx.load()
      clear + init + cpsExpr(e, 
        (v: String) =>
          (if (m.keys.size == 0) { 
            extractBooleanExp(v) match {
              case Some((c, t)) => 
                "(if (" + c + ") " + m.name + " " + sop + " " + t + " else ());\n"
              case _ =>
                m.name + " " + sop + " " + v + "\n"
            }
          } 
          else { 
            extractBooleanExp(v) match {
              case Some((c, t)) =>
                "(if (" + c + ") " + m.name + "." + fop +
                "(" + genTuple(m.keys map (x => ctx(x._1))) + ", " + t + ") else ());\n"
              case _ =>
                m.name + "." + fop + 
                "(" + genTuple(m.keys map (x => ctx(x._1))) + ", " + v + ")\n"
            }
          }
        ),
        /*if (op==OpAdd)*/ Some(m.keys)/* else None*/
      ) // XXXX commented out the if expression
    case IfStmt(cond, thenBlk, elseBlk) =>
      ctx.load()
      cpsExpr(cond, (v: String) =>
        extractBooleanExp(v) match {
          case Some((c, t)) =>
            "if (" + c + ") {\n" + 
              ind(thenBlk.map(genStmt).mkString("\n")) +
            "\n}\n" + 
            stringIf(elseBlk.nonEmpty, 
              "else {\n" +
                ind(elseBlk.map(genStmt).mkString("\n")) +
              "\n}\n"
            )
          case None => sys.error("No if condition")
        }, None)
  }

  def genTrigger(t: Trigger, s0: System): String = {
    val (n, as) = t.event match {
      case EventReady => ("SystemReady", Nil)
      case EventBatchUpdate(Schema(n, cs)) => ("BatchUpdate" + n, cs)
      case EventInsert(Schema(n, cs)) => ("Add" + n, cs)
      case EventDelete(Schema(n, cs)) => ("Del" + n, cs)
    }
    ctx = Ctx((t.event match {
                case EventInsert(_) | EventDelete(_) => as.map(x => (x._1, (x._2, x._1)))
                case _ => Nil
              }).toMap)

    val body = t.stmts.map(genStmt).mkString
    ctx = null
    val params = t.event match {
      case EventBatchUpdate(Schema(name, fields)) =>
        delta(name) + ":M3Map[" + genTupleDef(fields.map(_._2)) + ", " + typeToString(TypeLong) + "]"
      case _ =>
        as.map(a => a._1 + ": " + typeToString(a._2)).mkString(", ")
    }
    "def on" + n + "(" + params + ") " + 
    (if (body == "") "{ }" else "{\n" + ind(body) + "\n}")
  }

  // Lazy slicing (secondary) indices computation
  protected val sx = HashMap[String, List[List[Int]]]() // slicing indices

  def slice(m: String, i: List[Int]): Int = { 
    // add slicing over particular index capability
    val s = sx.getOrElse(m, List[List[Int]]())
    val n = s.indexOf(i)
    if (n != -1) n else { sx.put(m, s ::: List(i)); s.size }
  }

  def genMap(m: MapDef): String = {
    if (m.keys.size == 0) genVar(m.name, m.tp).trim
    else {
      val tk = genTupleDef(m.keys.map(_._2))
      val s = sx.getOrElse(m.name, List[List[Int]]())
      "val " + m.name + " = M3Map.make[" + tk + ", " + typeToString(m.tp) + "](" +
      s.map { is => "(k: " + tk + ") => " + 
        tup(is.map { i => "k._" + ( i + 1) }) 
      }.mkString(", ") + ");"
    }
  }

  def genInitializationFor(map: String, keyNames: List[(String, Type)], keyNamesConcat: String) =
    map + ".add(" + keyNamesConcat + ", 1L)"

  def genAddBatchTuple(name: String, keys: List[(String, Type)], value: String): String = {
    name + ".add(" + 
    genTuple(keys.zipWithIndex.map{ case ((_,tp),i) => (tp,"v"+i)})+","+ value + ")"
  }


  // Generate code for: (1) stream events handling
  //                    (2) table loading
  //                    (3) global constants declaration
  def genInternals(s0: System, nextSkip: String = "context.become(receive_skip)"): (String, String, String) = {
    // XXX: reduce as much as possible the overhead here to decode data, use Decoder's internals and inline the SourceMux here
    def ev(s: Schema, short: Boolean = true): (String, String, String, List[(String, Type)]) = {
      val fs = 
        if (short) s.fields.zipWithIndex.map { 
          case ((s, t), i) => ("v" + i, t) 
        } 
        else s.fields
      (fs.map { case(s, t) => s.toLowerCase + ":" + typeToString(t) }.mkString(","),
       genTuple(fs.map { case (v, t) => (t, v) }), 
       "(" + fs.map { case (s, t) => s.toLowerCase }.mkString(",") + ")",
       fs)
    }
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val skip = 
      "if (t1 > 0 && (tN & " + (step - 1) + ") == 0) { " + 
      "val t = System.nanoTime; if (t > t1) { t1 = t; tS = 1L; " + nextSkip +
      " } }; tN += 1L; "
    val pp = "" //if (cgOpts.printProgress > 0L) "printProgress(); " else ""
    
    val (systemEvent, others) = s0.triggers.partition(_.event match { 
      case EventReady => true
      case _ => false
    })
    val (singleEvents, batchEvents) = others.partition(_.event match { 
      case EventBatchUpdate(_) => false
      case EventInsert(_) | EventDelete(_) => true
      case _ => sys.error("Unexpected trigger event")
    })
    val singleStr = singleEvents.map(_.event match {
      case EventInsert(s) =>
        val (i, _, o, pl) = ev(s)
        "case TupleEvent(TupleInsert, \"" + s.name + 
        "\", List(" + i + ")) => " + skip + pp + "onAdd" + s.name + o + "\n"
      case EventDelete(s) =>
        val (i, _, o, pl) = ev(s)
        "case TupleEvent(TupleDelete, \"" + s.name + 
        "\", List(" + i + ")) => " + skip + pp + "onDel" + s.name + o + "\n"
      case _ => ""
    }).mkString

    val batchStr = if (batchEvents.size == 0) "" else {
      val sBatchEvents = batchEvents.map(_.event match { 
        case EventBatchUpdate(schema) =>
          val (params, _, _, _) = ev(schema)
          val deltaName = delta(schema.name)
          """|case ("%s", dataList) => 
             |  %s.clear
             |  dataList.foreach { case List(%s,vv:%s) =>
             |%s
             |  }
             |  onBatchUpdate%s(%s)
             |""".stripMargin
          .format(
            schema.name, deltaName, params, "TupleOp", 
            ind(genAddBatchTuple(deltaName, schema.fields, "vv"), 2), 
            schema.name, deltaName)
        case _ => ""
      }).mkString
      """|case BatchUpdateEvent(streamData) =>
         |  val batchSize = streamData.map(_._2.length).sum
         |  // Timeout check
         |  if (t1 > 0) {
         |    val t = System.nanoTime
         |    if (t > t1) { t1 = t; tS = batchSize; %s }
         |  }
         |  tN += batchSize
         |
         |  streamData.foreach { 
         |%s
         |    case (s, _) => sys.error("Unknown stream event name " + s)
         |  }
         |""".stripMargin
      .format(nextSkip, ind(sBatchEvents, 2))
    }
    val tableInitialization = s0.sources.filterNot { _.isStream }.map {
      s => {
        val (in, ad, sp) = genStream(s)
        val (i, o, _, pl) = ev(s.schema)
        "SourceMux({ case TupleEvent(TupleInsert, rn, List(" + i + 
        ")) => " + genInitializationFor(s.schema.name, pl, o) + " }, Seq((" +
        in + ", " + ad + ", " + sp + "))).read;" 
      }
    }.mkString("\n");
    (singleStr + batchStr, tableInitialization, consts)
  }

  def genSimpleEventsHandling(s0: System):String = {
    def ev(s: Schema, short: Boolean = true): (String, String, String, List[(String, Type)]) = {
      val fs =
        if (short) s.fields.zipWithIndex.map {
          case ((s, t), i) => ("v" + i, t)
        }
        else s.fields
      (fs.map { case(s, t) => s.toLowerCase + ":" + typeToString(t) }.mkString(","),
        genTuple(fs.map { case (v, t) => (t, v) }),
        "(" + fs.map { case (s, t) => s.toLowerCase }.mkString(",") + ")",
        fs)
    }

    val (systemEvent, others) = s0.triggers.partition(_.event match {
      case EventReady => true
      case _ => false
    })

    val (singleEvents, _) = others.partition(_.event match {
      case EventBatchUpdate(_) => false
      case EventInsert(_) | EventDelete(_) => true
      case _ => sys.error("Unexpected trigger event")
    })
    val singleStr = singleEvents.map(_.event match {
      case EventInsert(s) =>
        val (i, _, o, pl) = ev(s)
        "case TupleEvent(TupleInsert, \"" + s.name +
          "\", List(" + i + ")) => onAdd" + s.name + o + "\n"
      case EventDelete(s) =>
        val (i, _, o, pl) = ev(s)
        "case TupleEvent(TupleDelete, \"" + s.name +
          "\", List(" + i + ")) => onDel" + s.name + o + "\n"
      case _ => ""
    }).mkString

    singleStr
  }

  def genQueries(queries: List[Query]) = {
    queries.map { query => { query.expr match {
      case m: MapRef if (m.name == query.name) => ""
      case _ =>
        val keys = query.expr.ovars
        ctx = Ctx[(Type, String)]()
        "def " + query.name + "() = {\n" +
        ind(
          if (keys.length == 0) cpsExpr(query.expr)
          else {
            val mName = "m" + query.name
            val tk = tup(keys.map { case (_, tp) => typeToString(tp) })
            val nk = keys.map(_._1)
            "val " + mName + " = M3Map.make[" + tk + "," + 
            typeToString(query.expr.tp) + "]()\n" +
            cpsExpr(query.expr, (v: String) => 
              mName + ".add(" + genTuple(nk map ctx) + "," + v + ")"
            ) + "\n" +
            mName
          }
        ) + "\n}"
      }}
    }.mkString("\n")
  }

  def toMapFunction(q: Query) = {
    val keys = q.expr.ovars
    val keyTypes = keys.map(_._2)
    val nodeName = q.name + "_node"
    val resName = nodeName + "_mres"
    if (keyTypes.size > 0)
      "{ val " + resName + " = new scala.collection.mutable.HashMap[" +
      tup(keyTypes.map(typeToString)) + ", " + typeToString(q.expr.tp) + "](); " +
      q.name + ".foreach { case (e, v) => " + resName + " += (" +
      ( if (keyTypes.size > 1)
          tup(keyTypes.zipWithIndex.map { case (_, i) => "e._" + (i + 1) })
        else "e"
      ) + " -> v) }; " + resName + ".toMap }"
    else
      q.name
  }

  def clearOut() = {}
  
  def onEndStream = ""
  
  def apply(s0: System): String = {

    mapDefs = s0.maps.map(m => (m.name, m)).toMap
    
    val (tsSC, msSC, tempEntrySC) = genPardis(s0)
    val (lms, strLMS, ld0LMS, gcLMS) = genLMS(s0)

    val body = if (tsSC != null) {
      msSC + "\n\n" + tempEntrySC + "\n" + tsSC
    } 
    else if (lms != null) lms
    else {
      // triggers (need to be generated before maps)
      val ts = s0.triggers.map(genTrigger(_, s0)).mkString("\n\n") 
      
      // val ms = s0.triggers.map(_.event match { //delta relations
      //   case EventBatchUpdate(s) =>
      //     genMap(MapDef(delta(s.name), TypeLong, schema.fields, null, LocalExp)) + "\n"
      //   case _ => ""
      // }).mkString +
      // s0.triggers.flatMap { t => //local maps
      //   t.stmts.filter{
      //     case m: MapDef => true
      //     case _ => false
      //   }.map{
      //     case m: MapDef => genMap(m)+"\n"
      //     case _ => ""
      //   }
      // }.mkString + s0.maps.map(m => genMap(m)).mkString("\n") // maps

      val ms = s0.maps.map(genMap).mkString("\n") // maps

      ms + "\n" + genQueries(s0.queries) + "\n" + ts
    }
    val (str, ld0, gc) = if (lms != null) (strLMS, ld0LMS, gcLMS)
                         else genInternals(s0)
    val ld =
      // optional preloading of static tables content
      if (ld0 != "") "\n\ndef loadTables() {\n" + ind(ld0) + "\n}" else "" 
    freshClear()
    val snap: String = emitGetSnapshotBody(s0.queries)
    val pp = ""
      // if (cgOpts.printProgress > 0L) 
      //   "def printProgress(): Unit = if (tN % " + cgOpts.printProgress + 
      //   " == 0) Console.println((System.nanoTime - t0) + \"\\t\" + tN);\n" 
      // else ""
    clearOut()
    emitMainClass(s0.queries, s0.sources) + 
    emitActorClass(s0, body, pp, ld, gc, snap, str)
  }

  protected def emitGetSnapshotBody(queries: List[Query]) = 
    "List(" + queries.map(toMapFunction).mkString(", ") + ")"

  protected def genStream(s: Source): (String, String, String) = {
    val in = s.in match { 
      case SourceFile(path) => "new java.io.FileInputStream(\"" + path + "\")"
    }
    val split = "Split" + (s.split match { 
      case SplitLine => "()" 
      case SplitSep(sep) => "(\"" + sep + "\")" 
      case SplitSize(bytes) => "(" + bytes + ")" 
      case SplitPrefix(p) => ".p(" + p + ")" 
    })
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => 
        "OrderBook(" + 
        s.adaptor.options.toList.map { case (k,v) => k + "=" + (k match {
          case "brokers" => v 
          case "bids" | "asks" => "\"" + v + "\"" 
          case "deterministic" => (v != "no" && v != "false").toString 
          case _ => ""
        })}.filter(!_.endsWith("=")).mkString(",") + ")"
      case "CSV" => 
        val sep = 
          java.util.regex.Pattern.quote(
            s.adaptor.options.getOrElse("delimiter", ",")
          ).replaceAll("\\\\","\\\\\\\\")
        "CSV(\"" + s.schema.name.toUpperCase + "\",\"" + 
          s.schema.fields.map(_._2).mkString(",") + "\",\"" + sep + "\", " + 
          (if (cgOpts.dataset.endsWith("_del")) "\"ins + del\"" else "\"insert\"") +
        ")"
    }
    (in, "new Adaptor." + adaptor, split)
  }

  def streams(sources: List[Source]) = {
    // one source generates BOTH asks and bids events
    def fixOrderbook(ss: List[Source]): List[Source] = { 
      val (os, xs) = ss.partition { _.adaptor.name == "ORDERBOOK" }
      val ob = new java.util.HashMap[(Boolean, SourceIn), 
        (Schema, Split, Map[String, String], LocalityType)]()
      os.foreach { case Source(s, sc, in, sp, ad, loc) =>
        val (k, v) = 
          ((s, in), 
           (ad.options - "book") + ((ad.options.getOrElse("book","bids"),
                                    sc.name)))
        val p = ob.get(k)
        if (p == null) ob.put(k, (sc, sp, v, loc)) 
        else ob.put(k, (sc, sp, p._3 ++ v, loc))
      }
      scala.collection.JavaConversions.mapAsScalaMap(ob).toList.map { 
        case ((s, in), (sc, sp, opts, loc)) => 
          Source(s, sc, in, sp, Adaptor("ORDERBOOK", opts), loc) 
      } ::: xs
    }
    val ss = 
      fixOrderbook(sources).filter { _.isStream }.map { s => 
        val (in, ad, sp) = genStream(s)
        "(" + in + "," + ad + "," + sp + ")" 
      }.mkString(",\n")
    
    "Seq(\n" + ind(ss) + "\n)"
  }

  def getEntryDefinitions: String = tuples.values.mkString("\n")

  // Helper that contains the main and stream generator
  private def emitMainClass(queries: List[Query], sources: List[Source]) = {
    val sResults = queries.zipWithIndex.map { case (q, i) => 
        val ovars = q.expr.ovars
        val skeys = ovars.map(k => "\"" + k._1.toUpperCase + "\"").mkString(", ")
        "println(\"<" + q.name + ">\\n\" + M3Map.toStr(res(" + i + ")" +
        stringIf(ovars.nonEmpty, ", List(" + skeys + ")") + ")+\"\\n\" + \"</" + q.name + ">\\n\")"
      }.mkString("\n")
    val sStreams = streams(sources)
    s"""|package ${cgOpts.packageName}
        |    
        |import ddbt.lib._
        |import akka.actor.Actor
        |${additionalImports}
        |
        |object ${cgOpts.className} {
        |  import Helper._
        |
        |${ind(getEntryDefinitions)}
        |
        |  def execute(args: Array[String], f: List[Any] => Unit) = 
        |    bench(args, (dataset: String, parallelMode: Int, timeout: Long, batchSize: Int) => run[${cgOpts.className}](
        |${ind(sStreams, 3)}, 
        |      parallelMode, timeout, batchSize), f)
        |
        |  def main(args: Array[String]) {
        |
        |    val argMap = parseArgs(args)
        |    
        |    execute(args, (res: List[Any]) => {
        |      if (!argMap.contains("noOutput")) {
        |        println("<snap>")
        |${ind(sResults, 4)}
        |        println("</snap>")
        |      }
        |    })
        |  }  
        |}
        |""".stripMargin
  }

  protected def emitActorClass(s0: System, body: String, pp: String, ld: String, gc: String, snap: String, str: String) = {

    s"""|class ${cgOpts.className}Base {
        |  import ${cgOpts.className}._
        |  import ddbt.lib.Functions._
        |
        |${ind(body)}
        |
        |${ind(gc)}
        |}
        |
        |class ${cgOpts.className} extends ${cgOpts.className}Base with Actor {
        |  import ddbt.lib.Messages._
        |  import ddbt.lib.Functions._
        |  import ${cgOpts.className}._
        |  
        |  var t0 = 0L; var t1 = 0L; var tN = 0L; var tS = 0L
        |
        |  ${pp}
        |
        |${ind(ld)}
        |
        |  def receive_skip: Receive = { 
        |    case EndOfStream | GetSnapshot(_) => 
        |      ${onEndStream} sender ! (StreamStat(t1 - t0, tN, tS), null)
        |    case _ => tS += 1L
        |  }
        |
        |  def receive = {
        |${ind(str, 2)}
        |    case StreamInit(timeout) => 
        |      ${if (ld != "") " loadTables();" else ""}
        |      onSystemReady();
        |      t0 = System.nanoTime;
        |      if (timeout > 0) t1 = t0 + timeout * 1000000L
        |    case EndOfStream | GetSnapshot(_) => 
        |      t1 = System.nanoTime; 
        |      ${onEndStream} sender ! (StreamStat(t1 - t0, tN, tS), ${snap})
        |  }
        |}""".stripMargin
  }

  def additionalImports: String = ""
}
