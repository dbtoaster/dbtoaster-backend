package ddbt.codegen
import ddbt.codegen.lms._
import ddbt.ast._
import ddbt.lib._

/**
  * This code generator is similar to ScalaGen but targets LMS graph (IR) to
  * optimize further before emitting Scala code for the trigger bodies.
  *
  * @author Mohammad Dashti, TCK
  */
abstract class LMSGen(override val cls: String = "Query", val impl: LMSExpGen) extends IScalaGen {

  import ddbt.ast.M3._
  import ddbt.Utils.{ind, tup, fresh, freshClear} // common functions
  import ManifestHelper.{man, zero, manEntry, manStore}
  import impl.Rep
  implicit val overloaded1 = impl.overloaded1
  import ddbt.lib.store._

  var cx: Ctx[Rep[_]] = null

  def me(ks: List[Type], v: Type = null) = 
    manEntry(if (v == null) ks else ks ::: List(v))

  def mapProxy(m: Rep[_]) = 
    impl.store2StoreOpsCls(m.asInstanceOf[Rep[Store[Entry]]])


  // Expression CPS transformation from M3 AST to LMS graph representation
  //   ex : expression to convert
  //   co : continuation in which the result should be plugged
  //   am : shared aggregation map for Add and AggSum, 
  //        avoiding useless intermediate map where possible
  def expr(ex: Expr, co: Rep[_] => Rep[Unit], 
           am: Option[List[(String, Type)]] = None): Rep[Unit] = ex match {

    case Ref(n) => co(cx(n))
    case Const(tp, v) => ex.tp match {
      case TypeLong  => co(impl.unit(v.toLong))
      case TypeDouble => co(impl.unit(v.toDouble))
      case TypeString => co(impl.unit(v))
      case TypeDate   => sys.error("No date constant conversion") 
                         //co(impl.unit(new java.util.Date()))
      case _ => sys.error("Unsupported type " + tp)
    }
    case Exists(e) => 
      expr(e, (ve: Rep[_]) => co(impl.__ifThenElse(
        impl.notequals(ve, impl.unit(0L)), impl.unit(1L), impl.unit(0L))))
    case Cmp(l, r, op) => 
      // formally, we should take the derived type from left and right, 
      // but this makes no difference to LMS
      expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(cmp(vl, op, vr, ex.tp)))) 

    case a @ Apply(fn, tp, as) =>
      def app(es: List[Expr], vs: List[Rep[_]]): Rep[Unit] = es match {
        case x :: xs => expr(x, (v: Rep[_]) => app(xs, v :: vs))
        case Nil => co(impl.m3apply(fn, vs.reverse, tp))
      }
      if (as.forall(_.isInstanceOf[Const])) 
        // hoist constants resulting from function application
        co(impl.named(constApply(a), tp, false)) 
      else 
        app(as, Nil)

    case MapRef(n, tp, ks) =>
      val (ko, ki) = ks.zipWithIndex.partition { case (k, i) => cx.contains(k._1) }
      val proxy = mapProxy(cx(n))
      if (ks.size == 0) { // variable
        co(cx(n))
      } 
      else if (ki.size == 0) { // all keys are bound
        val z = impl.unit(zero(tp))
        val vs = ks.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) }
        val r = proxy.get(vs : _*)
        co(impl.__ifThenElse(impl.__equal(r, impl.unit(null)), z, impl.steGet(r, ks.size + 1)))
      } 
      else { // we need to iterate over all keys not bound (ki)
        if (ko.size > 0) {
          implicit val mE = me(ks.map(_._2), tp)
          val mm = cx(n).asInstanceOf[Rep[Store[Entry]]]
          impl.stSlice(mm, { (e: Rep[Entry]) => 
              cx.add(ki.map { case (k, i) => (k._1, impl.steGet(e, i + 1)) }.toMap)
              co(impl.steGet(e, ks.size + 1)) 
            }, ko.map { case (k, i) => (i + 1, cx(k._1)) } : _*)
        } 
        else {
          proxy.foreach((e: Rep[Entry]) => {
            cx.add(ki.map { case (k, i) => (k._1, impl.steGet(e, i + 1)) }.toMap)
            co(impl.steGet(e, ks.size + 1))
          })
        }
      }

    case Lift(n, e) =>
      if (cx.contains(n)) {
        expr(e, (ve: Rep[_]) => co(impl.__ifThenElse(
          impl.equals(ve, cx(n)), impl.unit(1L), impl.unit(0L))), am)
      }
      else e match {
        case Ref(n2) => cx.add(n, cx(n2)); co(impl.unit(1L))
        case _ => expr(e, (ve: Rep[_]) => { cx.add(n, ve); co(impl.unit(1L)) })
      }

    case Mul(l, r) => 
      expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(mul(vl, vr, ex.tp)), am), am)

    case a @ Add(l, r) =>
      val agg = a.schema._2.filter { case (n, t) => !cx.contains(n) }
      if (agg == Nil) {  
        val cur = cx.save
        expr(l, (vl: Rep[_]) => {
          cx.load(cur)
          expr(r, (vr: Rep[_]) => {
            cx.load(cur)
            co(add(vl, vr, ex.tp))
          }, am)
        }, am)
      } 
      else am match {
        case Some(t) if t.toSet.subsetOf(agg.toSet) =>
          val cur = cx.save
          expr(l, co, am)
          cx.load(cur)
          expr(r, co, am)
          cx.load(cur)
          impl.unit(())
        case _ =>
          implicit val mE = me(agg.map(_._2), a.tp)          
          val acc = impl.m3temp()(mE)
          val inCo = (v: Rep[_]) => 
            impl.m3add(acc, 
              impl.stNewEntry2(acc, (agg.map(x => cx(x._1)) ++ List(v)) : _*))(mE)
          val cur = cx.save
          expr(l, inCo, Some(agg))
          cx.load(cur)
          expr(r, inCo, Some(agg))
          cx.load(cur)
          foreach(acc, agg, a.tp, co)
      }

    case a @ AggSum(ks, e) =>
      // the aggregation is only made on free variables
      val agg_keys = ks.filter { case (n, t) => !cx.contains(n) }
      if (agg_keys.size == 0) { 
        // Accumulate expr(e) in the acc, returns (Rep[Unit],ctx) and 
        // we ignore ctx
        val cur = cx.save;
        val acc: impl.Var[_] = ex.tp match {
          case TypeLong =>
            val agg: impl.Var[Long] = impl.var_new[Long](impl.unit(0L))
            expr(e,
              (v: Rep[_]) => 
                impl.var_assign[Long](
                  agg.asInstanceOf[impl.Var[Long]], 
                  impl.numeric_plus[Long](
                    impl.readVar[Long](agg.asInstanceOf[impl.Var[Long]]),
                    v.asInstanceOf[Rep[Long]]
                  )
                )
            )
            agg
          case TypeDouble =>
            val agg: impl.Var[Double] = impl.var_new[Double](impl.unit(0.0))
            expr(e,
              (v: Rep[_]) => 
                impl.var_assign[Double](
                  agg.asInstanceOf[impl.Var[Double]], 
                  impl.numeric_plus[Double](
                    impl.readVar[Double](agg.asInstanceOf[impl.Var[Double]]),
                    v.asInstanceOf[Rep[Double]]
                  )
                )
            )
            agg
          case TypeString =>
            val agg: impl.Var[String] = impl.var_new[String](impl.unit(""))
            expr(e,
              (v: Rep[_]) => 
                impl.var_assign[String](
                  agg.asInstanceOf[impl.Var[String]], 
                  impl.string_plus(
                    impl.readVar[String](agg.asInstanceOf[impl.Var[String]]),
                    v.asInstanceOf[Rep[String]]
                  )
                )
            )
            agg
          //case TypeDate =>
          // val agg:impl.Var[java.util.Date] = impl.var_new[java.util.Date](impl.unit(new java.util.Date()))
          // expr(e,
          //  (v:Rep[_]) => impl.var_assign[java.util.Date](agg.asInstanceOf[impl.Var[java.util.Date]], impl.numeric_plus[java.util.Date](impl.readVar[java.util.Date](agg.asInstanceOf[impl.Var[java.util.Date]]),v.asInstanceOf[Rep[java.util.Date]])),
          //  None
          // )
          // agg
          case _ => sys.error("Unsupported type "+ex.tp)
        }
        cx.load(cur)
        co(impl.readVar(acc))
      } 
      else am match {
        case Some(t) if t.toSet.subsetOf(agg_keys.toSet) => expr(e, co, am)
        case _ =>        
          val cur = cx.save
          implicit val mE = me(agg_keys.map(_._2), ex.tp)
          val acc = impl.m3temp()(mE)
          val coAcc = (v: Rep[_]) => {
            val vs: List[Rep[_]] = agg_keys.map(x => cx(x._1)).toList ::: List(v)
            impl.m3add(acc, impl.stNewEntry2(acc, vs: _*))
          }
          expr(e, coAcc, Some(agg_keys))
          cx.load(cur) // returns (Rep[Unit],ctx) and we ignore ctx
          foreach(acc, agg_keys, a.tp, co)
      }

    case Repartition(ks, e) => expr(e, co)

    case Gather(e) => expr(e, co)

    case _ => sys.error("Unimplemented: " + ex)
  }

  def foreach(map: Rep[_], keys: List[(String, Type)], value_tp: Type, 
              co: Rep[_] => Rep[Unit]): Rep[Unit] = {
    implicit val mE = manEntry(keys.map(_._2) ::: List(value_tp))
    mapProxy(map).foreach { e: Rep[Entry] =>
      cx.add(keys.zipWithIndex.filter(x => !cx.contains(x._1._1))
                              .map { case ((n, t), i) => (n, impl.steGet(e, i + 1)) }
                              .toMap)
      co(impl.steGet(e, keys.size + 1))
    }
  }

  def mul(l: Rep[_], r: Rep[_], tp: Type) = tp match {
    case TypeLong | TypeDouble => impl.m3apply("mul", List(l, r), tp)
    case _ => sys.error("Mul(l,r) only allowed on numeric types")
  }

  def add(l: Rep[_], r: Rep[_], tp: Type) = {
    def plus[T: Numeric: Manifest](l: Rep[_], r: Rep[_]) = 
      impl.numeric_plus[T](l.asInstanceOf[Rep[T]], r.asInstanceOf[Rep[T]])
    tp match {
      case TypeLong => plus[Long](l, r)
      case TypeDouble => plus[Double](l, r)
      case _ => sys.error("Add(l,r) only allowed on numeric types")
    }
  }

  def cmp(l: Rep[_], op: OpCmp, r: Rep[_], tp: Type): Rep[Long] = {
    def cmp2[T: Ordering: Manifest] (vl: Rep[_], vr: Rep[_]): Rep[Boolean] = {
      val (ll, rr) = (vl.asInstanceOf[Rep[T]], vr.asInstanceOf[Rep[T]])
      op match {
        case OpEq => impl.equals[T, T](ll, rr)
        case OpNe => impl.notequals[T, T](ll, rr)
        case OpGt => impl.ordering_gt[T](ll, rr)
        case OpGe => impl.ordering_gteq[T](ll, rr)
      }
    }
    impl.__ifThenElse(tp match {
        case TypeLong => cmp2[Long](l, r)
        case TypeDouble => cmp2[Double](l, r)
        case TypeString => cmp2[String](l, r)
        case TypeDate => cmp2[Long](l, r)
          // cmp2[Long](impl.dtGetTime(l.asInstanceOf[Rep[java.util.Date]]),
          //            impl.dtGetTime(r.asInstanceOf[Rep[java.util.Date]]))
        case _ => sys.error("Unsupported type")
      }, 
      impl.unit(1L), 
      impl.unit(0L)
    )
  }

  def filterStatement(s: Stmt) = true

  // Trigger code generation
  def genTriggerLMS(t: Trigger, s0: System) = {
    val (name, args) = t.evt match {
      case EvtReady => ("SystemReady", Nil)
      case EvtBatchUpdate(Schema(n, cs)) => ("BatchUpdate" + n, cs)
      case EvtAdd(Schema(n, cs)) => ("Add" + n, cs)
      case EvtDel(Schema(n, cs)) => ("Del" + n, cs)
    }

    var params = ""
    val block = impl.reifyEffects {
      params = t.evt match {
        case EvtBatchUpdate(Schema(n, _)) =>
          val rel = s0.sources.filter(_.schema.name == n)(0).schema
          val name = rel.deltaName    
          name + ": Store[" + impl.codegen.storeEntryType(ctx0(name)._1) + "]"
        case _ => args.map(a => a._1 + ": " + a._2.toScala).mkString(", ")
      }
      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        ctx0.map{ case (name, (sym, keys, tp)) => (name, sym) }.toList union
        {
          t.evt match {
            case EvtBatchUpdate(Schema(n, _)) =>
              // val rel = s0.sources.filter(_.schema.name == n)(0).schema
              // val ks = rel.fields.map(_._2)
              // val tp = TypeLong
              // val name = rel.deltaName

              // val m = me(ks,tp)
              // val sc=impl.named(name,true)(manStore(m))
              // impl.collectStore(sc)(m)

              // List(name -> sc)
              Nil
            case _ =>
              args.map{ case (name, tp) => (name, impl.named(name, tp)) }
          }
        }
      ).toMap)
      // Execute each statement
      t.stmts.filter(filterStatement).map {
        case StmtMap(m, e, op, oi) => cx.load()
          if (m.keys.size == 0) {
            val mm = m.tp match {
              case TypeLong => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[Long]]])
              case TypeDouble => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[Double]]])
              case TypeString => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[String]]])
              //case TypeDate => 
              //  impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[java.util.Date]]])
              case _ => sys.error("Unsupported type " + m.tp)
            }
            expr(e, (r: Rep[_]) => op match { 
              case OpAdd => impl.var_plusequals(mm, r) 
              case OpSet => impl.__assign(mm, r) 
            })
          } 
          else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.keys.map(_._2) ++ List(m.tp)).asInstanceOf[Manifest[Entry]]
            if (op == OpSet) impl.stClear(mm)
            oi match { case None => case Some(ie) =>
              expr(ie, (r: Rep[_]) => {
                val ent = impl.stNewEntry2(mm, (m.keys.map(x => cx(x._1)) ++ List(r)) : _*)
                impl.__ifThenElse(
                  impl.equals(
                    mapProxy(mm).get(
                      m.keys.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) } : _*),
                    impl.unit(null)
                  ),
                  impl.m3set(mm, ent),
                  impl.unit(()))
              })
            }
            cx.load()
            expr(e, (r: Rep[_]) => {
              val ent = impl.stNewEntry2(mm, (m.keys.map(x => cx(x._1)) ++ List(r)) : _*)
              op match { case OpAdd | OpSet => impl.m3add(mm, ent)(mE) }
            }, 
            /*if (op==OpAdd)*/ Some(m.keys) /*else None*/) 
            // XXXX commented out the if expression
          }
        case m @ MapDef(name, tp, keys, _, _) =>
          // val m = me(keys.map(_._2),tp)
          // val s = impl.named(name, true)(manStore(m))
          // impl.collectStore(s)(m)
          // cx = Ctx(cx.ctx0 + (name -> s))
        
        // we leave room for other type of events
        case _ => sys.error("Unimplemented") 
      }
      impl.unit(())
    }
    cx = null
    (name, params, block)
  }

  override def toMapFunction(q: Query) = {
    val map = q.name
    val m = maps(map)
    val mapKeys = m.keys.map(_._2)
    val nodeName = map + "_node"
    val res = nodeName + "_mres"
    "{ val " + res + " = new scala.collection.mutable.HashMap[" +
    tup(mapKeys.map(_.toScala)) + "," + q.map.tp.toScala + "](); " + 
    map + ".foreach { e => " + res+" += (" + 
    tup(mapKeys.zipWithIndex.map { case (_, i) => "e._" + (i + 1) }) + 
    " -> e._" + (mapKeys.size + 1) + ") }; " + res + ".toMap }"
  }

  override def onEndStream = "printMapsInfo();"

  override def genMap(m: MapDef): String = {
    if (m.keys.size == 0) createVarDefinition(m.name, m.tp) + ";"
    else {
      impl.codegen.generateStore(
        ctx0(m.name)._1.asInstanceOf[impl.codegen.IR.Sym[_]])
    }
  }

  def genAllMaps(maps: Seq[MapDef]) = maps.map(genMap).mkString("\n")

  def createVarDefinition(name: String, tp: Type) = 
    "var " + name + ": " + tp.toScala + " = " + tp.zero

  override def genInitializationFor(map: String, keyNames: List[(String, Type)], keyNamesConcat: String) = {
    val (a, keys, tp) = ctx0(map)
    val acc = a.asInstanceOf[Rep[Store[Entry]]]
    val mE = me(keys.map(_._2), tp)
    val block = impl.reifyEffects {
      impl.m3add(acc,impl.stNewEntry2(acc, 
        ( (keyNames.map{ case (n, t) => impl.named(n, false)(mE) }) ++
          List(impl.unit(1)) ) : _*
      ))(mE)
    }
    val initCode = impl.emit(block)
    var staticFieldsStr = ""
    impl.codegen.staticFields.map { case (key, staticFldDef) =>
      staticFieldsStr += staticFldDef.trim + "\n"
    }
    impl.codegen.staticFields.clear

    staticFieldsStr + "\n" + initCode
  }

  // Expose the maps of the system being generated
  var ctx0 = Map[String, (Rep[_], List[(String, Type)], Type)]()

  override def genLMS(s0: System): (String, String, String, String) = {
    val classLevelMaps = s0.triggers.filter(_.evt match {
      case EvtBatchUpdate(s) => true
      case _ => false
    }).map(_.evt match { //delta relations
      case EvtBatchUpdate(sc) =>
        val name = sc.name
        val schema = s0.sources.filter(x => x.schema.name == name)(0).schema
        val deltaRel = sc.deltaName
        val tp = TypeLong
        val keys = schema.fields
        MapDef(deltaRel, tp, keys, null, LocalExp)
      case _ => null
    }) ++
    s0.triggers.flatMap { t=> //local maps
      t.stmts.filter{
        case m: MapDef => true
        case _ => false
      }.map{
        case m: MapDef => m
        case _ => null
      }
    } ++
    maps.map{
      case (_, m: MapDef) => m
    } // XXX missing indexes
    ctx0 = classLevelMaps.map {
      case MapDef(name, tp, keys, _, _) => if (keys.size == 0) {
        val s = impl.namedVar(name, tp)
        s.emitted = true
        (name, (s, keys, tp))
      } 
      else {
        val m = me(keys.map(_._2), tp)
        val s = impl.named(name, true)(manStore(m))
        impl.collectStore(s)(m)
        (name, (/*impl.newSStore()(m)*/s, keys, tp))
      }
    }.toMap // XXX missing indexes
    val (str, ld0, _) = genInternals(s0)
    //TODO: this should be replaced by a specific traversal 
    //      for completing the slice information
    // s0.triggers.map(super.genTrigger)
    // triggers (need to be generated before maps)
    val tsResBlks = s0.triggers.map(genTriggerLMS(_, s0)) 
    val ts = tsResBlks.map {
      case (name, params, b) => impl.emitTrigger(b, name, params)
    }.mkString("\n\n")
    val ms = genAllMaps(classLevelMaps) // maps
    var outStream = new java.io.StringWriter
    var outWriter = new java.io.PrintWriter(outStream)
    //impl.codegen.generateClassArgsDefs(outWriter,Nil)

    impl.codegen.emitDataStructures(outWriter)
    val ds = outStream.toString
    val printInfoDef = if (Store.GATHER_STATISTICS) {
      "def printMapsInfo() = {\n" + 
        maps.map { case (m, MapDef(_, _, keys, _, _)) => 
          if (keys.size > 0) 
            "  System.out.println(\"" + m + " => \" + " + m + 
            ".getInfoStr)\n  Store.addTimersFromStore(\"" + m + 
            "\", " + m + ".totalTimers, " + m + ".timersPerIndex)\n" 
          else "" 
        }.mkString +
        impl.storeSyms.map { map => 
          if (map.attributes.get("_isTemp")
              .asInstanceOf[Option[Boolean]].getOrElse(false)) { 
            val m = impl.codegen.quote(map)
            "  Store.addTimersFromStore(\"" + m + "\", " + m + 
            ".totalTimers, " + m + ".timersPerIndex)\n" 
          } 
          else "" 
        }.mkString +
        "  System.out.println(\"Timers Info => {\\n%s\\n%s}\".format(" + 
        "Store.printTimersInfo,Store.printTimersInfoCSV))\n"+ 
        "}"
    } 
    else "def printMapsInfo() = {}"
    val r = ds + "\n" + ms + "\n" + ts + "\n" + printInfoDef
    (r, str, ld0, consts)
  }

  override def genAddBatchTuple(name: String, keys: List[(String, Type)], value: String): String = {
    val (a, keys, tp) = ctx0(name)
    val storeRep = a.asInstanceOf[Rep[Store[Entry]]]
    val mE = me(keys.map(_._2), tp)
    val block = impl.reifyEffects {
      impl.m3add(storeRep, impl.stNewEntry2(storeRep, 
        ( (keys.zipWithIndex.map { case ((_, t), i) => 
             impl.named("v" + i, false)(mE) 
           }) 
           ++ 
           List(impl.named("vv", tp, false)) ) : _*
      ))(mE)
    }
    impl.emit(block)
  }

  override def clearOut = {
    maps = Map()
    impl.reset
  }

  override val additionalImports: String = "import ddbt.lib.store._\n"

  override def getEntryDefinitions: String = ""
}

class LMSScalaGen(cls: String = "Query") extends LMSGen(cls, ScalaExpGen) 

class LMSCppGen(cls: String = "Query") extends LMSGen(cls, CppExpGen) 
                                       with ICppGen {
  import ddbt.ast.M3._

  override def toMapFunction(q: Query) = super[LMSGen].toMapFunction(q)
  override def onEndStream = super[LMSGen].onEndStream
  override def genMap(m: MapDef): String = super[LMSGen].genMap(m)
  override def genInitializationFor(
      map: String, 
      keyNames: List[(String, Type)], 
      keyNamesConcat: String) = 
    super[LMSGen].genInitializationFor(map, keyNames, keyNamesConcat)
  override def genLMS(s0: System):(String, String, String, String) = 
    super[LMSGen].genLMS(s0)
  override def clearOut = super[LMSGen].clearOut
  override val additionalImports: String = ""
}
