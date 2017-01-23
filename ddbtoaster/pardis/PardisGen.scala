package ddbt.codegen

import ch.epfl.data.sc.pardis.types.{PardisType, RecordType, UnitType}
import ch.epfl.data.sc.pardis.utils.TypeUtils
import ch.epfl.data.sc.pardis.utils.document._
import com.sun.org.apache.xalan.internal.xsltc.compiler.Constants
import ddbt.Utils._
import java.io.{PrintWriter, StringWriter}

import ch.epfl.data.sc.pardis.ir.CTypes.{Pointer, PointerType}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.ScalaCodeGenerator
import ddbt.ast.M3._
import ddbt.ast.M3.{Apply => M3ASTApply}
import ddbt.ast._
import ddbt.lib.ManifestHelper
import ddbt.lib.ManifestHelper._
import ddbt.lib.store.deep.{StoreDSL, StoreDSLOptimized}
import ch.epfl.data.sc.pardis.types.PardisTypeImplicits._
import ddbt.codegen.prettyprinter.{StoreCodeGenerator, StoreCppCodeGenerator, StoreScalaCodeGenerator}
import ch.epfl.data.sc.pardis.optimization._
import ddbt.transformer._

abstract class PardisGen(override val cls: String = "Query", val IR: StoreDSL) extends IScalaGen {


  import scala.language.implicitConversions
  import ddbt.lib.store.deep._
  import IR._

  val codeGen: StoreCodeGenerator
  val tempMapSchema = collection.mutable.ArrayBuffer[(Sym[_], List[TypeRep[_]])]()

  def debug(s: String): Unit = {
    java.lang.System.out.println(s)
  }

  def typeToTypeRep(tp: Type): TypeRep[Any] = {
    tp match {
      case TypeLong => runtimeType[Long]
      case TypeDouble => runtimeType[Double]
      case TypeString => runtimeType[String]
      case TypeDate => runtimeType[Date]
    }
  }.asInstanceOf[TypeRep[Any]]


  def me(ks: List[Type], v: Type = null) = manEntry(if (v == null) ks else ks ::: List(v))

  def me2(ks: List[Type], v: Type = null) = ManifestHelper.manEntry(if (v == null) ks else ks ::: List(v))

  def mapProxy(m: Rep[_]) = IR.store2StoreOpsCls(m.asInstanceOf[Rep[Store[Entry]]])

  def mapProxy2(m: Rep[_]) = new IR.StoreRep1(m.asInstanceOf[Rep[Store[Entry]]])


  def containsForeachOrSlice(ex: Expr): Boolean = ex match {
    case MapRef(_, _, ks) => {
      ks.size > 0 && {
        val (ko, ki) = ks.zipWithIndex.partition { case (k, i) => cx.contains(k) }
        ki.size > 0
      }
    }
    case a@Add(l, r) if (a.agg != Nil) => true
    case a@AggSum(ks, e) if ((ks zip a.tks).filter { case (n, t) => !cx.contains(n) }).size != 0 => true
    case s: Product => s.productIterator.collect { case e: Expr => containsForeachOrSlice(e) }.foldLeft(false)(_ || _)
  }

  val csSym = collection.mutable.HashMap[String, Rep[_]]()

  // Expression CPS transformation from M3 AST to LMS graph representation
  //   ex : expression to convert
  //   co : continuation in which the result should be plugged
  //   am : shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def expr(ex: Expr, co: Rep[_] => Rep[Unit], am: Option[List[(String, Type)]] = None): Rep[Unit] = ex match {
    case Ref(n) => co(cx(n))
    case Const(tp, v) => ex.tp match {
      case TypeLong => co(IR.unit(v.toLong))
      case TypeDouble => co(IR.unit(v.toDouble))
      case TypeString => co(IR.unit(v))
      case TypeDate => sys.error("No date constant conversion") //co(impl.unit(new java.util.Date()))
      case _ => sys.error("Unsupported type " + tp)
    }
    case Exists(e) => expr(e, (ve: Rep[_]) => co(IR.BooleanExtra.conditional(IR.infix_!=(ve.asInstanceOf[Rep[Long]], IR.unit(0L)), IR.unit(1L), IR.unit(0L))))
    case Cmp(l, r, op) => expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(cmp(vl, op, vr, ex.tp)))) // formally, we should take the derived type from left and right, but this makes no difference to LMS
    case a@M3ASTApply(fn, tp, as) =>
      def app(es: List[Expr], vs: List[Rep[_]]): Rep[Unit] = es match {
        case x :: xs => expr(x, (v: Rep[_]) => app(xs, v :: vs))
        case Nil => co(IR.m3apply(fn, vs.reverse, tp))
      }
      if (as.forall(_.isInstanceOf[Const])) {
        val cName = constApply(a)
        co(csSym.get(cName) match { case Some(n) => n case None => val cSym = IR.freshNamed(cName)(typeToTypeRep(tp)); csSym += ((cName, cSym)); cSym }) // hoist constants resulting from function application
      }
      else app(as, Nil)

    case Lift(n, e) =>
      if (cx.contains(n))
        expr(e, (ve: Rep[_]) => co(IR.BooleanExtra.conditional(IR.infix_==(ve.asInstanceOf[Rep[Any]], cx(n).asInstanceOf[Rep[Any]]), IR.unit(1L), IR.unit(0L))), am)
      else e match {
        case Ref(n2) => cx.add(n, cx(n2)); co(IR.unit(1L))
        case _ => expr(e, (ve: Rep[_]) => {
          cx.add(n, ve);
          co(IR.unit(1L))
        })
      }
    //        case Mul(Cmp(l1, r1, o1), Cmp(l2, r2, o2)) => expr(l1, (vl1: Rep[_]) => expr(r1, (vr1: Rep[_]) => expr(l2, (vl2: Rep[_]) => expr(r2, (vr2: Rep[_]) => co(IR.BooleanExtra.conditional(condition(vl1, o1, vr1, ex.tp) && condition(vl2, o2, vr2, ex.tp), unit(1L), unit(0L))))))) //TODO: SBJ: am??
    case Mul(Cmp(l, r, op), rr) if Optimizer.m3CompareMultiply && !containsForeachOrSlice(rr) =>
      val tp = man(rr.tp).asInstanceOf[TypeRep[Any]]
      expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(IR.__ifThenElse(condition(vl, op, vr, ex.tp), {
        var tmpVrr: Rep[_] = null;
        expr(rr, (vrr: Rep[_]) => {
          tmpVrr = vrr;
          IR.unit(())
        });
        tmpVrr
      }, IR.unit(zero(rr.tp))(tp))(tp)), am), am)
    case Mul(l, r) => expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(mul(vl, vr, ex.tp)), am), am)
    case a@Add(l, r) =>
      if (a.agg == Nil) {
        val cur = cx.save
        expr(l, (vl: Rep[_]) => {
          cx.load(cur)
          expr(r, (vr: Rep[_]) => {
            cx.load(cur)
            co(add(vl, vr, ex.tp).asInstanceOf[Rep[_]])
          }, am)
        }, am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) =>
          val cur = cx.save
          expr(l, co, am)
          cx.load(cur)
          expr(r, co, am)
          cx.load(cur)
          IR.unit(())
        case _ =>
          implicit val mE = me(a.agg.map(_._2), a.tp)
          val acc = IR.m3temp()(mE)
          tempMapSchema += acc.asInstanceOf[Sym[_]] -> (a.agg.map(_._2) :+ a.tp).map(man)
          val inCo = (v: Rep[_]) => IR.m3add(acc, IR.stNewEntry2(acc, (a.agg.map(x => cx(x._1)) ++ List(v)): _*))(mE)
          val cur = cx.save
          expr(l, inCo, Some(a.agg));
          cx.load(cur)
          expr(r, inCo, Some(a.agg));
          cx.load(cur)
          foreach(acc, a.agg, a.tp, co)
      }

    case m@MapRef(n, tp, ks) =>
      val (ko, ki) = ks.zipWithIndex.partition { case (k, i) => cx.contains(k) }
      val proxy = mapProxy(cx(n))
      val proxy2 = mapProxy2(cx(n))
      if (ks.size == 0) {
        // variable
        co(cx(n))
      } else if (ki.size == 0) {
        // all keys are bound
        val z = IR.unit(zero(tp))
        val vs = ks.zipWithIndex.map { case (n, i) => (i + 1, cx(n)) }
        //TODO: SBJ: Check ok?
        val r = proxy2.get1(vs: _*)
        val mE = man(tp).asInstanceOf[TypeRep[Any]]
        //        println(s"tpe here! ${mE}")
        //                    println(s"tpe here! ${mE.typeArguments}")

        co(IR.__ifThenElse(IR.infix_==(r, IR.unit(null)), z, IR.steGet(r, ks.size + 1)(IR.EntryType, mE))(mE))
      } else {
        // we need to iterate over all keys not bound (ki)
        if (ko.size > 0) {
          implicit val mE = me(m.tks, tp)
          val mm = cx(n).asInstanceOf[Rep[Store[Entry]]]
          IR.stSlice(mm, { (e: Rep[Entry]) =>
            //            println(s"tpe here! ${mE.typeArguments(i+1)}")
            cx.add(ki.map { case (k, i) => (k, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap); co(IR.steGet(e, ks.size + 1)(IR.EntryType, mE.typeArguments(ks.size)))
          }, ko.map { case (k, i) => (i + 1, cx(k)) }: _*)
        } else {
          implicit val mE = me(m.tks, tp)
          proxy.foreach(__lambda { e: Rep[Entry] => {
            //println(s"********************tpe here! ${mE}")
            // println(s"********************tpe here! ${mE.typeArguments}")
            cx.add(ki.map { case (k, i) => (k, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap)

            co(IR.steGet(e, ks.size + 1)(IR.EntryType, mE.typeArguments(ks.size)))
          }
          })
        }
      }

    case a@AggSum(ks, e) =>
      val agg_keys = (ks zip a.tks).filter { case (n, t) => !cx.contains(n) } // the aggregation is only made on free variables
      if (agg_keys.size == 0) {
        // Accumulate expr(e) in the acc, returns (Rep[Unit],ctx) and we ignore ctx
        val cur = cx.save;
        ex.tp match {
          case TypeLong =>
            val agg: IR.Var[Long] = IR.__newVar[Long](IR.unit(0L))
            expr(e,
              (v: Rep[_]) => IR.__assign[Long](agg.asInstanceOf[IR.Var[Long]], IR.numeric_plus[Long](IR.readVar[Long](agg.asInstanceOf[IR.Var[Long]]), v.asInstanceOf[Rep[Long]]))
            )
            cx.load(cur)
            co(IR.readVar(agg))
          case TypeDouble =>
            val agg: IR.Var[Double] = IR.__newVar[Double](IR.unit(0.0))
            expr(e,
              (v: Rep[_]) => IR.__assign[Double](agg.asInstanceOf[IR.Var[Double]], IR.numeric_plus[Double](IR.readVar[Double](agg.asInstanceOf[IR.Var[Double]]), v.asInstanceOf[Rep[Double]]))
            )

            cx.load(cur)
            co(IR.readVar(agg))
          case TypeString =>
            val agg: IR.Var[String] = IR.__newVar[String](IR.unit(""))
            expr(e,
              (v: Rep[_]) => IR.__assign[String](agg.asInstanceOf[IR.Var[String]], IR.string$plus(IR.readVar[String](agg.asInstanceOf[IR.Var[String]]), v.asInstanceOf[Rep[String]]))
            )

            cx.load(cur)
            co(IR.readVar(agg))
          case _ => sys.error("Unsupported type " + ex.tp)
        }
      } else am match {
        case Some(t) if t.toSet.subsetOf(agg_keys.toSet) => expr(e, co, am)
        case _ =>

          val cur = cx.save

          implicit val mE = me(agg_keys.map(_._2), ex.tp)
          val acc = IR.m3temp()(mE)
          tempMapSchema += acc.asInstanceOf[Sym[_]] -> (agg_keys.map(_._2) :+ ex.tp).map(man)
          val coAcc = (v: Rep[_]) => {
            val vs: List[Rep[_]] = agg_keys.map(x => cx(x._1)).toList ::: List(v)
            IR.m3add(acc, IR.stNewEntry2(acc, vs: _*))(mE)
          }
          expr(e, coAcc, Some(agg_keys));
          cx.load(cur) // returns (Rep[Unit],ctx) and we ignore ctx
          foreach(acc, agg_keys, a.tp, co)
      }
    case _ => sys.error("Unimplemented: " + ex)
  }

  //def foreach(map:Rep[_],keys:List[(String,Type)],value_tp:Type,co:Rep[_]=>Rep[Unit]) = null

  def foreach(map: Rep[_], keys: List[(String, Type)], value_tp: Type, co: Rep[_] => Rep[Unit]): Rep[Unit] = {
    implicit val mE = manEntry(keys.map(_._2) ::: List(value_tp))
    // val mE = impl.EntryType
    val proxy = mapProxy(map)
    proxy.foreach {
      __lambda {
        e: Rep[Entry] =>
          cx.add(keys.zipWithIndex.filter(x => !cx.contains(x._1._1)).map { case ((n, t), i) => (n, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap)
          co(IR.steGet(e, keys.size + 1)(IR.EntryType, mE.typeArguments(keys.size)))
      }
    }
  }

  def mul(l: Rep[_], r: Rep[_], tp: Type) = {
    tp match {
      case TypeLong | TypeDouble => IR.m3apply("mul", List(l, r), tp)
      case _ => sys.error("Mul(l,r) only allowed on numeric types")
    }
  }

  def add(l: Rep[_], r: Rep[_], tp: Type) = {
    @inline def plus[T: TypeRep]() = IR.numeric_plus[T](l.asInstanceOf[Rep[T]], r.asInstanceOf[Rep[T]])
    tp match {
      case TypeLong => plus[Long]()
      case TypeDouble => plus[Double]()
      case _ => sys.error("Add(l,r) only allowed on numeric types")
    }
  }

  def condition(l: Rep[_], op: OpCmp, r: Rep[_], tp: Type): Rep[Boolean] = {
    @inline def cmp2[T: TypeRep](vl: Rep[_], vr: Rep[_]): Rep[Boolean] = {
      val (ll, rr) = (vl.asInstanceOf[Rep[T]], vr.asInstanceOf[Rep[T]])
      op match {
        case OpEq => IR.infix_==[T, T](ll, rr)
        case OpNe => IR.infix_!=[T, T](ll, rr)
        case OpGt => IR.ordering_gt[T](ll, rr)
        case OpGe => IR.ordering_gteq[T](ll, rr)
      }
    }
    tp match {
      case TypeLong => cmp2[Long](l, r)
      case TypeDouble => cmp2[Double](l, r)
      case TypeString => cmp2[String](l, r)
      case TypeDate => cmp2[Long](IR.dtGetTime(l.asInstanceOf[Rep[java.util.Date]]), IR.dtGetTime(r.asInstanceOf[Rep[java.util.Date]]))
      case _ => sys.error("Unsupported type")
    }
  }

  def cmp(l: Rep[_], op: OpCmp, r: Rep[_], tp: Type): Rep[Long] = {
    IR.BooleanExtra.conditional(condition(l, op, r, tp), IR.unit(1L), IR.unit(0L))
  }

  def filterStatement(s: Stmt) = s match {
    case StmtMap(m, _, _, _) if m.name.endsWith("_DELTA") => false
    case _ => true
  }


  def createVarDefinition(name: String, tp: Type) = "var " + name + ":" + tp.toScala + " = " + tp.zero

  override def genInitializationFor(map: String, keyNames: List[(String, Type)], keyNamesConcat: String) = {
    if (Optimizer.analyzeEntry) {
      val ctx = ctx0(map)
      val name = SEntry((ctx._2.map(_._2) :+ ctx._3).map(man)).name
      map + s".unsafeInsert(0, $name(" + (if (Optimizer.analyzeIndex) "" else "false,") + keyNames.map(e => e._1).mkString(",") + ",1L))"
    }
    else
      map + ".unsafeInsert(0, GenericEntry(\"SteNewSEntry\"," + keyNames.map(e => e._1).mkString(",") + ",1L))"
  }

  override def toMapFunction(q: Query) = {
    val map = q.name
    val m = maps(map)
    val mapKeys = m.keys.map(_._2)
    val nodeName = map + "_node"
    val res = nodeName + "_mres"
    def get(i: Int) = if (Optimizer.analyzeEntry) s"e._$i" else s"e.get($i)"
    if (q.keys.size > 0)
      "{ val " + res + " = new scala.collection.mutable.HashMap[" + tup(mapKeys.map(_.toScala)) + "," + q.map.tp.toScala + "](); " + map + ".foreach{e => " + res + " += ((" + (if (mapKeys.size >= 1) tup(mapKeys.zipWithIndex.map { case (_, i) => get(i + 1) }) else "e") + "," + get(if (mapKeys.size >= 1) (mapKeys.size + 1) else mapKeys.size) + ")) }; " + res + ".toMap }"
    else {
      q.name
    }
  }

  var cx: Ctx[Rep[_]] = null

  def getTriggerNameArgs(t: Trigger): (String, List[(String, Type)])

  // Trigger code generation
  def genTriggerPardis(t: Trigger, s0: System) = {
    val (name, args) = getTriggerNameArgs(t)


    val block = IR.reifyBlock {

      //println(s"HELLO AGAIN2 ${ctx0}")
      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        ctx0.map { case (name, (sym, keys, tp)) => (name, sym) }.toList union {
          t.evt match {
            case EvtBatchUpdate(Schema(n, _)) =>
              Nil
            case _ =>
              args.map { case (name, tp) => (name, IR.freshNamed(name)(typeToTypeRep(tp))) }
          }
        }
        ).toMap)
      // Execute each statement
      t.stmts.filter(filterStatement).map {
        case StmtMap(m, e, op, oi) => cx.load()
          if (m.keys.size == 0) {
            val (mm, mmtp) = m.tp match {
              case TypeLong => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[Long]]]) -> LongType
              case TypeDouble => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[Double]]]) -> DoubleType
              case TypeString => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[String]]]) -> StringType
              case TypeDate => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[java.util.Date]]]) -> DateType
              case _ => sys.error("Unsupported type " + m.tp)
            }

            //            println(s"tpe here! ${mm}, ${mmtp}, ${m.tp}}");
            expr(e, (r: Rep[_]) => op match {
              case OpAdd => debug(s"tpe here! ${mm}, ${mm.tp}}"); IR.var_plusequals(mm, r)(mmtp.asInstanceOf[TypeRep[Any]])
              case OpSet => IR.__assign(mm, r)
            })
          } else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.tks ++ List(m.tp))
            if (op == OpSet) IR.stClear(mm)
            oi match {
              case None =>
              case Some(ie) =>
                expr(ie, (r: Rep[_]) => {
                  val ent = IR.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)): _*)
                  IR.__ifThenElse(IR.infix_==(stProxyGet(mm, m.keys.zipWithIndex.map { case (n, i) => (i + 1, cx(n)) }: _*),
                    IR.unit(null)), IR.m3set(mm, ent)(mE), IR.unit(()))
                })
            }
            cx.load()
            expr(e, (r: Rep[_]) => {
              val ent = IR.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)): _*)
              op match {
                case OpAdd | OpSet => IR.m3add(mm, ent)(mE)
              }
            }, /*if (op==OpAdd)*/ Some(m.keys zip m.tks) /*else None*/) // XXXX commented out the if expression
          }
        case m@MapDef(name, tp, keys, _) =>
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      IR.unit(())
    }
    val params: List[Sym[_]] = args.map(t => cx(t._1).asInstanceOf[Sym[_]])
    cx = null;
    (name, params, block)
  }

  var ctx0 = Map[String, (Rep[_], List[(String, Type)], Type)]()
  var globalMembersBlock: Block[Unit] = null
  var m3System: M3.System = null

  override def genPardis(s0: M3.System): (String, String, String) = {
    ExpressionSymbol.globalId = 0
    m3System = s0
    val classLevelMaps = s0.triggers.filter(_.evt match {
      case EvtBatchUpdate(s) => true
      case _ => false
    }).map(_.evt match {
      //delta relations
      case EvtBatchUpdate(sc) =>
        val name = sc.name
        val schema = s0.sources.filter(x => x.schema.name == name)(0).schema
        val deltaRel = sc.deltaSchema
        val tp = TypeLong
        val keys = schema.fields
        MapDef(deltaRel, tp, keys, null)
      case _ => null
    }) ++
      s0.triggers.flatMap { t => //local maps
        t.stmts.filter {
          case MapDef(_, _, _, _) => true
          case _ => false
        }.map {
          case m@MapDef(_, _, _, _) => m
          case _ => null
        }
      } ++
      maps.map {
        case (_, m@MapDef(_, _, _, _)) => m
      } // XXX missing indexes
    globalMembersBlock = IR.reifyBlock {
      ctx0 = classLevelMaps.map {
        case MapDef(name, tp, keys, _) => if (keys.size == 0) {
          val m = man(tp).asInstanceOf[TypeRep[Any]]

          val s = IR.__newVarNamed(unit(zero(tp))(m), name)(m).e // xxx::: Change nulls impl.named(name,false)(m)
          //s.emitted = true
          (name, (s, keys, tp))
        } else {
          val m = me2(keys.map(_._2), tp)
          implicit val cE = ManifestHelper.manStore(m)
          val s = IR.__newStoreNamed(name) // xxx::impl.named(name,true)(manStore(m))
          //impl.collectStore(s)(m)
          (name, ( /*impl.newSStore()(m)*/ s, keys, tp))
        }
      }.toMap // XXX missing indexes
      unit(())
    }
    //    val (str, ld0, globalConstants) = genInternals(s0)
    val tsResBlks = s0.triggers.map(genTriggerPardis(_, s0)) // triggers (need to be generated before maps)

    case class OpInfo(var count: Int)

    class AccessOperationAnalysis(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

      import IR._


      /**
        * Keeps the list of while loops that should be converted
        */

      val mapAccess = scala.collection.mutable.HashMap[Rep[_], OpInfo]()
      //
      analysis += statement {
        case sym -> (node@StoreGetCopy
          (map, _, _)) =>
          mapAccess.getOrElseUpdate(map, new OpInfo(0)).count += 1
          ()
      }
    }

    class AccessOperationTransformer(override val IR: StoreDSL, val mapAccess: scala.collection.mutable.HashMap[Rep[_], OpInfo]) extends RuleBasedTransformer[StoreDSL](IR) {

      import IR._

      // rewrite += rule {
      //   case StoreGetCopy(map,idx,key) if(mapAccess(map).count < 4) =>
      //     map.update(unit(null))
      // }
    }

    //    val analysisRound = new AccessOperationAnalysis(impl)
    //
    //    for(x <- tsResBlks) {
    //      analysisRound.optimize(x._3)
    //    }
    //
    //    val transformationRound = new AccessOperationTransformer(impl, analysisRound.mapAccess)
    //    val analysisRound2 = new AccessOperationAnalysis(impl)
    //
    //    for(x <- tsResBlks) {
    //      val nb = transformationRound.transformBlock(x._3)
    //      analysisRound2.traverseBlock(nb)
    //    }

    //     java.lang.System.err.println(analysisRound.mapAccess)
    // java.lang.System.err.println(analysisRound2.mapAccess)

    val allSchema = classLevelMaps.map({ case MapDef(name, tp, kt, _) => ctx0(name)._1.asInstanceOf[IR.Sym[_]] -> (kt.map(_._2) :+ tp).map(man) }) ++ tempMapSchema
    allSchema.foreach(x => {
      x._1.asInstanceOf[Sym[_]].attributes += StoreSchema(x._2)
      val idx = new IndexedCols
      idx.primary = (1 until x._2.size).toSeq
      x._1.asInstanceOf[Sym[_]].attributes += idx
    })
    tempMapSchema.clear()
    val allnames = classLevelMaps.collect { case MapDef(name, _, _, _) => name }
    val iGlobal = allnames.map(ctx0(_)._1.asInstanceOf[Sym[_]])
    val initTP = TransactionProgram(globalMembersBlock, iGlobal, tsResBlks, Nil, Nil)
    val optTP = new Optimizer(IR).optimize(initTP)

    val printInfoDef = doc"def printMapsInfo() = {}"

    genCodeForProgram(optTP)
  }

  def genCodeForProgram[T](prg: TransactionProgram[T]): (String, String, String)

  override def getEntryDefinitions = "" //TODO:SBJ : Need to be fixed for batch processing(input record type)
}

class PardisScalaGen(cls: String = "Query") extends PardisGen(cls, if (Optimizer.onlineOpts) new StoreDSLOptimized {} else new StoreDSL {}) {

  import Optimizer._;
  import IR._

  val opts = Map("Entry" -> analyzeEntry, "Index" -> analyzeIndex, "FixedRange" -> fixedRange, "Online" -> onlineOpts, "TmpMapHoist" -> tmpMapHoist, "TmpVar" -> tmpVarHoist, "Inline" -> indexInline, "Fusion full" -> indexLookupFusion, "Fusion" -> indexLookupPartialFusion, "DeadIdx" -> deadIndexUpdate, "CodeMotion" -> codeMotion, "RefCnt" -> refCounter, "CmpMult" -> m3CompareMultiply)
  java.lang.System.err.println("Optimizations :: " + opts.filter(_._2).map(_._1).mkString(", "))
  override val codeGen = new StoreScalaCodeGenerator(IR)

  override def getTriggerNameArgs(t: Trigger) = t.evt match {
    case EvtReady => ("SystemReady", Nil)
    case EvtBatchUpdate(Schema(n, cs)) => ("BatchUpdate" + n, cs)
    case EvtAdd(Schema(n, cs)) => ("Add" + n, cs)
    case EvtDel(Schema(n, cs)) => ("Del" + n, cs)
  }

  override def genCodeForProgram[T](optTP: TransactionProgram[T]) = {
    var ts = ""
    for (x <- optTP.codeBlocks) {
      import codeGen.{doc => _, _}
      val doc2 = codeGen.blockToDocument((x._3))
      ts += doc"def on${x._1}(${x._2.map(s => doc"$s:${s.tp}").mkDocument(", ")}) {" :/: Document.nest(2, doc2) :/: doc"\n}\n"
    }

    //    val ds = "" // xxx - Fixeit outStream.toString


    val entries = optTP.structs.map(codeGen.getStruct).mkDocument("\n")
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    val globalMaps = codeGen.blockToDocumentNoBraces(optTP.initBlock)
    val tempMaps = optTP.tmpMaps.map(s => {
      val sDef = Def.unapply(s._1).get
      val eIdx = sDef match {
        case StoreNew3(_, ops: Sym[_]) => ops
      }
      codeGen.stmtToDocument(Statement(eIdx, Def.unapply(eIdx).get)) :/:
        codeGen.stmtToDocument(Statement(s._1, sDef)) :/:
        s._2.map(i => codeGen.stmtToDocument(Statement(i, Def.unapply(i).get))).mkDocument("\n") //index defs
    }).mkDocument("\n")
    val ms = (entries :/: entryIdxes :/: globalMaps :/: tempMaps).toString

    val tempEntries = optTP.tempVars.map(t => codeGen.stmtToDocument(Statement(t._1, t._2))).mkDocument("\n").toString

    (ts, ms, tempEntries)
  }
}

class PardisCppGen(cls: String = "Query") extends PardisGen(cls, if (Optimizer.onlineOpts) new StoreDSLOptimized {} else new StoreDSL {}) with ICppGen {
  override val codeGen: StoreCppCodeGenerator = new StoreCppCodeGenerator(IR)

  import IR._

  override val usingPardis: Boolean = true

  override def genCodeForProgram[T](optTP: TransactionProgram[T]) = {
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    var ts = ""
    codeGen.currentProgram = PardisProgram(optTP.structs, optTP.main, Nil)
    codeGen.refSymbols ++= optTP.tempVars.map(_._1)
    for (x <- optTP.codeBlocks) {
      import codeGen.{doc => _, _}
      val preBody =
        s"""
           |BEGIN_TRIGGER(exec_stats,"${x._1.drop(1)}")
           |BEGIN_TRIGGER(ivc_stats,"${x._1.drop(1)}")
           |${if (x._1.contains("system_ready")) "" else "++tN;"}
         """.stripMargin
      val postBody =
        s"""
           |END_TRIGGER(exec_stats,"${x._1.drop(1)}")
           |END_TRIGGER(ivc_stats,"${x._1.drop(1)}")
         """.stripMargin
      val doc2 = preBody :: codeGen.blockToDocument((x._3)) :: postBody
      ts += doc"void on${x._1}(${x._2.map(s => doc"${s.tp}& $s").mkDocument(", ")}) {" :/: Document.nest(2, doc2) :/: doc"\n}\n"
    }
    m3System.triggers.filter(_.evt != EvtReady).foreach(t => ts += (generateUnwrapFunction(t.evt)(m3System) + "\n"))

    def getEntryIdxNames(ops: Seq[Expression[EntryIdx[Entry]]]) = ops.collect {
      case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
      case Def(n: EntryIdxGenericOpsObject) =>
        val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
        if (cols.isEmpty)
          s"GenericOps"
        else {
          s"GenericOps_$cols"

        }
      case Def(n: EntryIdxGenericCmpObject[_]) =>
        val ord = Def.unapply(n.f).get.asInstanceOf[PardisLambda[_, _]].o.stmts(0).rhs match {
          case GenericEntryGet(_, Constant(i)) => i
        }
        val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
        s"GenericCmp_${cols.mkString("")}_$ord"

      case Def(n: EntryIdxGenericFixedRangeOpsObject) =>
        val cols = n.colsRange.asInstanceOf[Constant[List[(Int, Int, Int)]]].underlying.map(t => s"${t._1}f${t._2}t${t._3}").mkString("_")
        s"GenericFixedRange_$cols"
    }
    def structToDoc(s: PardisStructDef[_]) = s match {
      case PardisStructDef(tag, fields, methods) =>
        val fieldsDoc = fields.map(x => doc"${x.tpe} ${x.name};").mkDocument("  ") :: doc"  ${tag.typeName} *prv;  ${tag.typeName} *nxt; void* backPtrs[${fields.size}];"
        val constructorWithArgs = doc"${tag.typeName}(" :: fields.map(x => doc"const ${x.tpe}& ${x.name}").mkDocument(", ") :: ") : " :: fields.map(x => doc"${x.name}(${x.name})").mkDocument(", ") :: ", prv(nullptr), nxt(nullptr) {}"
        val constructor = doc"${tag.typeName}() :" :: fields.map(x => {
          if (x.tpe == StringType)
            doc"${x.name}()"
          else doc"${x.name}(${nullValue(x.tpe)})"
        }).mkDocument(", ") :: ", prv(nullptr), nxt(nullptr) {}"
        val copyFn = doc"${tag.typeName}* copy() const { return new ${tag.typeName}(" :: fields.map(x => {
          if (x.tpe == StringType)
            doc"*${x.name}.copy()"
          else
            doc"${x.name}"
        }).mkDocument(", ") :: "); }"
        val serializer = doc"template<class Archive> \nvoid serialize(Archive& ar, const unsigned int version) const {" :/:
          Document.nest(4, fields.map(x => doc"DBT_SERIALIZATION_NVP(ar,${x.name});").mkDocument("ar << ELEM_SEPARATOR;\n", "\nar << ELEM_SEPARATOR;\n", "\n")) :/: "}"

        "struct " :: tag.typeName :: " {" :/: Document.nest(2, fieldsDoc :/: constructor :/: constructorWithArgs :/: serializer :/: copyFn) :/: "};"
    }
    val entries = optTP.structs.map(structToDoc).mkDocument("\n")
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    val idxes = optTP.globalVars.map(s => s ->(collection.mutable.ArrayBuffer[(Sym[_], String, Boolean, Int)](), collection.mutable.ArrayBuffer[String]())).toMap // store -> (AB(idxSym, IdxType, uniq, other), AB(IdxName))
    optTP.initBlock.stmts.collect {
      case Statement(s, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) => {
        val names = getEntryIdxNames(ops)
        idxes(s)._2.++=(names)
      }
      case Statement(sym, StoreIndex(s, _, Constant(typ), Constant(uniq), Constant(other))) => idxes(s.asInstanceOf[Sym[Store[_]]])._1.+=((sym, typ, uniq, other))
    }
    val idx2 = idxes.map(t => t._1 -> (t._2._1 zip t._2._2 map (x => (x._1._1, x._1._2, x._1._3, x._1._4, x._2))).toList) // Store -> List[Sym, Type, unique, otherInfo, IdxName ]


    val stores = optTP.globalVars.map(s => {

      if (s.tp.isInstanceOf[StoreType[_]]) {
        def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"
        val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
        val idxTypes = idx2(s).filter(_._2 != "INone").map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
        val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

        val storeTypeDef = doc"typedef MultiHashMap<${entryTp}, char," :/: idxTypes.map(_._1).mkDocument("   ", ",\n   ", ">") :: doc" ${s.name}_map;"
        val entryTypeDef = doc"typedef $entryTp ${s.name}_entry;"
        val storeDecl = s.name :: "_map  " :: s.name :: ";"

        val idxDecl = idx2(s).filter(_._2 != "INone").zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1} = * (${idxTypeName(t._2)} *)${s.name}.index[${t._2}];").mkDocument("\n")
        val primaryIdx = idx2(s)(0)
        val primaryRef = doc"${idxTypeName(0)}& ${s.name}PrimaryIdx = * (${idxTypeName(0)} *) ${s.name}.index[0];"
        idxTypeDefs :\\: storeTypeDef :\\: entryTypeDef :\\: storeDecl :\\: idxDecl :\\: primaryRef
      } else {
        doc"${s.tp} ${s.name};"
      }
    }).mkDocument("\n", "\n\n\n", "\n")

    val tempMaps = optTP.tmpMaps.map(s => {
      val entryTp = s._1.tp.asInstanceOf[StoreType[_]].typeE
      codeGen.stmtToDocument(Statement(s._1, Def.unapply(s._1).get)) :/:
        s._2.map(i => codeGen.stmtToDocument(Statement(i, Def.unapply(i).get))).mkDocument("\n") //index refs

    }).mkDocument("\n")
    val ms = (entries :/: entryIdxes :/: stores :/: tempMaps).toString

    val tempEntries = optTP.tempVars.map(t => doc"${t._2.tp} ${t._1};").mkDocument("\n").toString

    (ts, ms, tempEntries)
  }

  //  def storeToDoc(s: ConstructorDef[Store[_]]) = s match {
  //  import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
  //    case StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops))))) =>
  //  }

  def idxToDoc(idx: (Sym[_], String, Boolean, Int, String), entryTp: PardisType[_], allIdxs: List[(Sym[_], String, Boolean, Int, String)]): Document = {
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    idx._2 match {
      case "IHash" => doc"HashIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
      case "IDirect" => doc"ArrayIndex<$entryTp, char, ${idx._5}, ${unit(idx._4)}>"
      case "ISliceHeapMax" => val idx2 = allIdxs(idx._4); doc"TreeIndex<$entryTp, char, ${idx2._5}, ${idx._5}, ${unit(true)}>"
      case "ISliceHeapMin" => val idx2 = allIdxs(idx._4); doc"TreeIndex<$entryTp, char, ${idx2._5}, ${idx._5}, ${unit(false)}>"
      case "IList" => doc"ListIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
    }

  }

  override def getTriggerNameArgs(t: Trigger) = t.evt match {
    case EvtReady => ("_system_ready_event", Nil)
    case EvtBatchUpdate(Schema(n, cs)) => ("_batch_update_" + n, cs)
    case EvtAdd(Schema(n, cs)) => ("_insert_" + n, cs)
    case EvtDel(Schema(n, cs)) => ("_delete_" + n, cs)
  }

  override def genTrigger(t: Trigger, s0: System): String = {
    val (name, params, block) = genTriggerPardis(t, s0)
    val Cname = t.evt match {
      case EvtReady => "system_ready_event"
      case EvtBatchUpdate(sc@Schema(n, cs)) => "batch_update_" + n
      case EvtAdd(Schema(n, cs)) => "insert_" + n
      case EvtDel(Schema(n, cs)) => "delete_" + n
    }
    val code = codeGen.blockToDocument(block)
    s"void on_$Cname(" + params.map(i => "const")
  }
}
