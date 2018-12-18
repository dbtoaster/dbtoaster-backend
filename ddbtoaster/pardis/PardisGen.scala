package ddbt.codegen

import ch.epfl.data.sc.pardis.types.{PardisType, RecordType, UnitType}
import ch.epfl.data.sc.pardis.types.PardisTypeImplicits._
import ch.epfl.data.sc.pardis.utils.TypeUtils
import ch.epfl.data.sc.pardis.utils.document._
import ch.epfl.data.sc.pardis.ir.CTypes.{Pointer, PointerType}
import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.prettyprinter.ScalaCodeGenerator
import ch.epfl.data.sc.pardis.optimization._
import ddbt.ast._
import ddbt.ast.M3._
import ddbt.ast.M3.{Apply => M3ASTApply}
import ddbt.lib.ManifestHelper
import ddbt.lib.ManifestHelper._
import ddbt.lib.store.deep.{StoreDSL, StoreDSLOptimized}
import ddbt.lib.Utils
import ddbt.lib.Utils._
import ddbt.codegen.prettyprinter.{StoreCodeGenerator, StoreCppCodeGenerator, StoreScalaCodeGenerator}
import ddbt.transformer._
import java.io.{File, PrintWriter}

import scala.collection.mutable
import scala.util.parsing.json.JSON
import com.sun.org.apache.xalan.internal.xsltc.compiler.Constants
import ddbt.lib.TypeHelper.Scala.typeToString


abstract class PardisGen(override val cgOpts: CodeGenOptions, val IR: StoreDSL) extends CodeGen {

  import Optimizer._;
  val opts = Map("Entry" -> analyzeEntry, "Index" -> secondaryIndex, "FixedRange" -> fixedRange, "Online" -> onlineOpts,
    "TmpVar" -> tmpVarHoist, "TmpMap" -> tmpMapHoist, "Inline" -> indexInline, "Fusion full" -> indexLookupFusion,
    "Fusion" -> indexLookupPartialFusion, "SliceInline" -> sliceInline, "DeadIdx" -> deadIndexUpdate, "CodeMotion" -> codeMotion,
    "CmpMult" -> m3CompareMultiply, "RegexHoister" -> regexHoister, "RefCnt" -> refCounter, "MultiResSplitter" -> multiResSplitter,
    "InitialStoreSize" -> initialStoreSize, "SliceNoUpdate" -> sliceNoUpd, "Spl" -> splSecondaryIdx, "MinMax" -> minMaxIdx,
    "Med" -> medIdx, "ColdMotion" -> coldMotion, "StoreProfile" -> profileStoreOperations, "BlockProfile" -> profileBlocks,
    "ParameterPromotion" -> parameterPromotion)
//  java.lang.System.err.println("Optimizations :: " + opts.filter(_._2).map(_._1).mkString(", "))

  import scala.language.implicitConversions
  import ddbt.lib.store.deep._
  import IR._

  val infoFile = new File(s"../runtime/stats/${if (Optimizer.infoFileName == "") "default" else Optimizer.infoFileName}.json")
  val infoFilePath = infoFile.getAbsolutePath
  var StoreArrayLengths = Map[String, String]()
  var idxSymNames: List[String] = null
  
  if(Optimizer.initialStoreSize) {
    if (infoFile.exists()) {
      java.lang.System.err.println(s"Loading runtime info from $infoFilePath")
      val txt = new java.util.Scanner(infoFile).useDelimiter("\\Z").next()
      val allinfo: Map[String, _] = JSON.parseFull(txt).get.asInstanceOf[Map[String, _]]
      StoreArrayLengths = allinfo.map(t => t._1 -> t._2.asInstanceOf[Map[String, String]].getOrElse("OptArrayLength", "0"))
    } else {
      java.lang.System.err.println("Runtime info file missing!!  Using default initial sizes")
    }
  }

  val codeGen: StoreCodeGenerator
  val tempMapSchema = collection.mutable.ArrayBuffer[(Sym[_], List[TypeRep[_]])]()

  def debug(s: String): Unit = {
    java.lang.System.out.println(s)
  }

  def typeToTypeRep(tp: Type): TypeRep[Any] = {
    tp match {
      case TypeChar | TypeShort | TypeInt | TypeLong => runtimeType[Long]
      case TypeFloat | TypeDouble => runtimeType[Double]
      case TypeString => runtimeType[String]
      case TypeDate => runtimeType[Long]
      // case TypeDate => runtimeType[Date]
      case _ => sys.error("Unsupported type: " + tp)
    }
  }.asInstanceOf[TypeRep[Any]]


  def me(ks: List[Type], v: Type = null) = manEntry(if (v == null) ks else ks ::: List(v))

  def me2(ks: List[Type], v: Type = null) = ManifestHelper.manEntry(if (v == null) ks else ks ::: List(v))

  def mapProxy(m: Rep[_]) = IR.store2StoreOpsCls(m.asInstanceOf[Rep[Store[Entry]]])

  def mapProxy2(m: Rep[_]) = new IR.StoreRep1(m.asInstanceOf[Rep[Store[Entry]]])


  def containsForeachOrSlice(ex: Expr): Boolean = ex match {
    case MapRef(_, _, ks, _) => {
      ks.size > 0 && {
        val (ko, ki) = ks.zipWithIndex.partition { case (k, i) => cx.contains(k._1) }
        ki.size > 0
      }
    }
    case a@Add(l, r) if a.schema._2.exists { case (n, t) => !cx.contains(n) } => true
    case a@AggSum(ks, e) if ks.exists { case (n, t) => !cx.contains(n) } => true
    case _ => false
  }

  val nameToSymMap = collection.mutable.HashMap[String, Rep[_]]() //maps the name used in IScalaGen/ICppGen to SC Symbols
  var unionDepth = 0
  /**
    Extracts from expressions boolean conditions  on which the result depends on. Used for MultCmp optimization
  */
  def extractBoolean(ex: Expr): Option[Rep[Boolean]] = ex match {

    case Exists(e) if containsForeachOrSlice(e) => None  //No conditions for foreach and slice. They always exist

    case Exists(e@MapRef(n, tp, ks, isTemp)) if ks.size > 0 && ks.foldLeft(true)((acc, k) => acc && cx.contains(k._1)) => //check if it is a get on a store
      val vs = ks.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) }
      val r = mapProxy2(cx(n)).get1(vs: _*)
      Some(IR.infix_!=(r, IR.unit(null)))

    case Exists(e) =>
      var cond: Rep[Boolean] = null
      expr(e, (ve: Rep[_]) => {cond = IR.infix_!=(ve.asInstanceOf[Rep[Int]],IR.unit(0)); IR.unit})
      Some(cond)

    case Cmp(l, r, op) =>
      var cond: Rep[Boolean] = null
      expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => {cond = condition(vl, op, vr, ex.tp); IR.unit}))
      Some(cond)

    case CmpOrList(l, rr) =>
      var orCond: Rep[Boolean] = null
      expr(l, (vl: Rep[_]) => {
        orCond = rr.map { r =>
          var cond: Rep[Boolean] = null
          expr(r, (vr: Rep[_]) => {
            cond = condition(vl, OpEq, vr, ex.tp);
            IR.unit
          })
          cond
        }.reduce(_ || _)
        IR.unit
      })
      Some(orCond)
    case Lift(n, e) if cx.contains(n) =>
      var cond: Rep[Boolean] = null
      expr(e, (ve: Rep[_]) => {cond = IR.infix_==(ve.asInstanceOf[Rep[Any]], cx(n).asInstanceOf[Rep[Any]]); IR.unit})
      Some(cond)
    case _ => None
  }
  // Expression CPS transformation from M3 AST to LMS graph representation
  //   ex : expression to convert
  //   co : continuation in which the result should be plugged
  //   am : shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible

  def expr(ex: Expr, co: Rep[_] => Rep[Unit], am: Option[List[(String, Type)]] = None): Rep[Unit] = ex match {
    case Ref(n) => co(cx(n))
    case Const(tp, v) => ex.tp match {
      case TypeChar | TypeShort | TypeInt | TypeLong => co(IR.unit(v.toLong))
      case TypeFloat | TypeDouble => co(IR.unit(v.toDouble))
      case TypeString if Optimizer.regexHoister && Optimizer.cTransformer => expr(M3ASTApply("STRING_TYPE", TypeString, List(ex)), co, am)
      case TypeString => co(IR.unit(v))
      case TypeDate => sys.error("No date constant conversion") //co(impl.unit(new java.util.Date()))
      case _ => sys.error("Unsupported type " + tp)
    }
    case Exists(e@MapRef(n, tp, ks, isTemp)) if Optimizer.m3CompareMultiply && (ks.size > 0 && !ks.foldLeft(true)((acc, k) => acc && cx.contains(k._1))) =>
      expr(e, (ve: Rep[_]) => co(IR.unit(1)))
    case Exists(e) => 
      expr(e, (ve: Rep[_]) => 
        co(IR.BooleanExtra.conditional(IR.infix_!=(ve.asInstanceOf[Rep[Long]], IR.unit(0L)), IR.unit(1L), IR.unit(0L))))
    case Cmp(l, r, op) => 
      expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(cmp(vl, op, vr, ex.tp)))) // formally, we should take the derived type from left and right, but this makes no difference to LMS
    case CmpOrList(l, rr) =>
      expr(l, (vl: Rep[_]) => {
        val orCond = rr.map { r => 
           var cond: Rep[Boolean] = null
           expr(r, (vr: Rep[_]) => { cond = condition(vl, OpEq, vr, ex.tp); IR.unit })
           cond
         }.reduce(_ || _)
        co(IR.BooleanExtra.conditional(orCond, IR.unit(1L), IR.unit(0L)))
      })
    case a@M3ASTApply(fn, tp, as) =>
      def app(es: List[Expr], vs: List[Rep[_]]): Rep[Unit] = es match {
        case x :: xs => expr(x, (v: Rep[_]) => app(xs, v :: vs))
        case Nil => co(IR.m3apply(fn, vs.reverse, tp))
      }
      if (as.forall(_.isInstanceOf[Const])) {
        val cName = hoistedConsts.getOrElseUpdate(a, Utils.fresh("c"))
        co(nameToSymMap.getOrElseUpdate(cName, IR.freshNamed(cName)(typeToTypeRep(tp)))) // hoist constants resulting from function application
      } else if (Optimizer.regexHoister && fn.equals("regexp_match") && as(0).isInstanceOf[Const]) {
        val cName = regexpCacheMap.getOrElseUpdate(as(0).asInstanceOf[Const].v, Utils.fresh("preg"))
        val regex = nameToSymMap.getOrElseUpdate(cName, IR.freshNamed(cName)(RegexType))
        expr(as(1), (v: Rep[_]) => co(IR.m3apply("preg_match", List(regex, v), tp)))
      } else if (fn.equals("date_part")) { //Need to handle it here before the string constant get hoisted
        val (as2, fn2) = as.head.asInstanceOf[Const].v.toLowerCase match {
          case "year" => (as.tail, "date_year")
          case "month" => (as.tail, "date_month")
          case "day" => (as.tail, "date_day")
          case p => throw new Exception("Invalid date part: " + p)
        }
        expr(M3ASTApply(fn2, tp, as2), co)
      }
      else app(as, Nil)

    case Lift(n, e) =>
      if (cx.contains(n))
        expr(e, (ve: Rep[_]) => 
          co(IR.BooleanExtra.conditional(IR.infix_==(ve.asInstanceOf[Rep[Any]], cx(n).asInstanceOf[Rep[Any]]), IR.unit(1L), IR.unit(0L))), am)
      else e match {
        case Ref(n2) => 
          cx.add(n, cx(n2))
          co(IR.unit(1L))
        case _ => expr(e, (ve: Rep[_]) => {
          cx.add(n, ve);
          co(IR.unit(1L))
        })
      }

    case Mul(l, r) => extractBoolean(l) match {

      //If unionDepth is zero, the zero result is not added to anything else. So entire result cna be discarded and continuation not applied
      case Some(cond) if Optimizer.m3CompareMultiply && unionDepth == 0 =>
        IR.__ifThenElse(cond, {
          expr(r, (vr: Rep[_]) => {
            co(vr)
          },am)
        }, IR.unit())

      //If UnionDepth is non-zero, if condition evaluates to false, the result continuation should still be invoked with  value 0
      case Some(cond) if Optimizer.m3CompareMultiply =>
        val tp = man(r.tp).asInstanceOf[TypeRep[Any]]
        expr(r, (vr: Rep[_]) =>
          co(IR.__ifThenElse(cond, vr, IR.unit(zero(r.tp))(tp))(tp)), am)
      case _ =>  expr(l, (vl: Rep[_]) => expr(r, (vr: Rep[_]) => co(mul(vl, vr, ex.tp)), am), am)
    }

    case a@Add(l, r) =>
      val agg = a.schema._2.filter { case (n, t) => !cx.contains(n) }
      if (agg == Nil) {
        val cur = cx.save
        unionDepth += 1
        expr(l, (vl: Rep[_]) => {
          cx.load(cur)
          expr(r, (vr: Rep[_]) => {
            cx.load(cur)
            unionDepth -= 1
            co(add(vl, vr, ex.tp).asInstanceOf[Rep[_]])
          }, am)
        }, am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(agg.toSet) =>
          val cur = cx.save
          expr(l, co, am)
          cx.load(cur)
          expr(r, co, am)
          cx.load(cur)
          IR.unit(())
        case _ =>
          implicit val mE = me(agg.map(_._2), a.tp)
          val acc = IR.m3temp()(mE)
          tempMapSchema += acc.asInstanceOf[Sym[_]] -> (agg.map(_._2) :+ a.tp).map(man)
          val inCo = (v: Rep[_]) => IR.m3add(acc, IR.stNewEntry2(acc, (agg.map(x => cx(x._1)) ++ List(v)): _*))(mE)
          val cur = cx.save
          expr(l, inCo, Some(agg));
          cx.load(cur)
          expr(r, inCo, Some(agg));
          cx.load(cur)
          foreach(acc, agg, a.tp, co)
      }

    case m@MapRef(n, tp, ks, isTemp) =>
      val (ko, ki) = ks.zipWithIndex.partition { case (k, i) => cx.contains(k._1) }
      val proxy = mapProxy(cx(n))
      val proxy2 = mapProxy2(cx(n))
      if (ks.size == 0) {
        // variable
        co(cx(n))
      } else if (ki.size == 0) {
        // all keys are bound
        val z = IR.unit(zero(tp))
        val vs = ks.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) }
        //TODO: SBJ: Check ok?
        val r = proxy2.get1(vs: _*)
        val mE = man(tp).asInstanceOf[TypeRep[Any]]
        //        println(s"tpe here! ${mE}")
        //                    println(s"tpe here! ${mE.typeArguments}")

        co(IR.__ifThenElse(IR.infix_==(r, IR.unit(null)), z, IR.steGet(r, ks.size + 1)(IR.EntryType, mE))(mE))
      } else {
        // we need to iterate over all keys not bound (ki)
        if (ko.size > 0) {
          implicit val mE = me(ks.map(_._2), tp)
          val mm = cx(n).asInstanceOf[Rep[Store[Entry]]]
          IR.stSlice(mm, { (e: Rep[Entry]) =>
            //            println(s"tpe here! ${mE.typeArguments(i+1)}")
            cx.add(ki.map { case (k, i) => (k._1, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap); co(IR.steGet(e, ks.size + 1)(IR.EntryType, mE.typeArguments(ks.size)))
          }, ko.map { case (k, i) => (i + 1, cx(k._1)) }: _*)
        } else {
          implicit val mE = me(ks.map(_._2), tp)
          proxy.foreachCopy(__lambda { e: Rep[Entry] => {
            //println(s"********************tpe here! ${mE}")
            // println(s"********************tpe here! ${mE.typeArguments}")
            cx.add(ki.map { case (k, i) => (k._1, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap)

            co(IR.steGet(e, ks.size + 1)(IR.EntryType, mE.typeArguments(ks.size)))
          }
          })
        }
      }

    case a@AggSum(ks, e) =>
      val agg_keys = ks.filter { case (n, t) => !cx.contains(n) } // the aggregation is only made on free variables
      if (agg_keys.size == 0) {
        // Accumulate expr(e) in the acc, returns (Rep[Unit],ctx) and we ignore ctx
        val cur = cx.save;
        ex.tp match {
          case TypeChar | TypeShort | TypeInt | TypeLong =>
            val agg: IR.Var[Long] = IR.__newVar[Long](IR.unit(0L))
            expr(e,
              (v: Rep[_]) => IR.__assign[Long](agg.asInstanceOf[IR.Var[Long]], IR.numeric_plus[Long](IR.readVar[Long](agg.asInstanceOf[IR.Var[Long]]), v.asInstanceOf[Rep[Long]]))
            )
            cx.load(cur)
            co(IR.readVar(agg))
          case TypeFloat | TypeDouble =>
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
    proxy.foreachCopy {
      __lambda {
        e: Rep[Entry] =>
          cx.add(keys.zipWithIndex.filter(x => !cx.contains(x._1._1)).map { case ((n, t), i) => (n, IR.steGet(e, i + 1)(IR.EntryType, mE.typeArguments(i))) }.toMap)
          co(IR.steGet(e, keys.size + 1)(IR.EntryType, mE.typeArguments(keys.size)))
      }
    }
  }

  def mul(l: Rep[_], r: Rep[_], tp: Type) = {
    tp match {
      case TypeChar | TypeShort | TypeInt | TypeLong | TypeFloat | TypeDouble => 
        IR.m3apply("mul", List(l, r), tp)
      case _ => sys.error("Mul(l,r) only allowed on numeric types")
    }
  }

  def add(l: Rep[_], r: Rep[_], tp: Type) = {
    @inline def plus[T: TypeRep]() = IR.numeric_plus[T](l.asInstanceOf[Rep[T]], r.asInstanceOf[Rep[T]])
    tp match {
      case TypeChar | TypeShort | TypeInt | TypeLong => plus[Long]()
      case TypeFloat | TypeDouble => plus[Double]()
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
      case TypeChar | TypeShort | TypeInt | TypeLong => cmp2[Long](l, r)
      case TypeFloat | TypeDouble => cmp2[Double](l, r)
      case TypeString => cmp2[String](l, r)
      case TypeDate => cmp2[Long](l, r)
      // case TypeDate => cmp2[Long](IR.dtGetTime(l.asInstanceOf[Rep[java.util.Date]]), IR.dtGetTime(r.asInstanceOf[Rep[java.util.Date]]))
      case _ => sys.error("Unsupported type")
    }
  }

  def cmp(l: Rep[_], op: OpCmp, r: Rep[_], tp: Type): Rep[Long] = {
    IR.BooleanExtra.conditional(condition(l, op, r, tp), IR.unit(1L), IR.unit(0L))
  }

  def filterStatement(s: M3.Statement) = s match {
    case s: TriggerStmt => !s.target.name.endsWith("_DELTA")
    case s: IfStmt => true
  } 

  var cx: Ctx[Rep[_]] = null

  def getTriggerNameArgs(t: Trigger): (String, List[(String, Type)])

  // Trigger code generation
  def genTriggerPardis(t: Trigger, s0: System) = {
    val (name, args) = getTriggerNameArgs(t)


    val block = IR.reifyBlock {

      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        ctx0.map { case (name, (sym, keys, tp)) => (name, sym) }.toList union {
          t.event match {
            case EventBatchUpdate(Schema(n, _)) =>
              Nil
            case _ =>
              args.map { case (name, tp) => (name, IR.freshNamed(name)(typeToTypeRep(tp))) }
          }
        }
        ).toMap)
      // Execute each statement
      t.stmts.filter(filterStatement).map {
        case TriggerStmt(m, e, op, oi) => cx.load()
          if (m.keys.size == 0) {
            val (mm, mmtp) = m.tp match {
              case TypeChar | TypeShort | TypeInt | TypeLong => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[Long]]]) -> LongType
              case TypeFloat | TypeDouble => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[Double]]]) -> DoubleType
              case TypeString => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[String]]]) -> StringType
              case TypeDate => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[Date]]]) -> LongType
              // case TypeDate => IR.Var(cx(m.name).asInstanceOf[Rep[IR.Var[java.util.Date]]]) -> DateType
              case _ => sys.error("Unsupported type " + m.tp)
            }

            expr(e, (r: Rep[_]) => op match {
              case OpAdd => IR.var_plusequals(mm, r)(mmtp.asInstanceOf[TypeRep[Any]])
              case OpSet => IR.__assign(mm, r)
            })
          } else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.keys.map(_._2) ++ List(m.tp))
            if (op == OpSet) IR.stClear(mm)
            oi match {
              case None =>
              case Some(ie) =>
                expr(ie, (r: Rep[_]) => {
                  val ent = IR.stNewEntry2(mm, (m.keys.map(x => cx(x._1)) ++ List(r)): _*)
                  IR.__ifThenElse(IR.infix_==(stProxyGet(mm, m.keys.zipWithIndex.map { case (k, i) => (i + 1, cx(k._1)) }: _*),
                    IR.unit(null)), IR.m3set(mm, ent)(mE), IR.unit(()))
                })
            }
            cx.load()
            expr(e, (r: Rep[_]) => {
              val ent = IR.stNewEntry2(mm, (m.keys.map(x => cx(x._1)) ++ List(r)): _*)
              op match {
                case OpAdd | OpSet => IR.m3add(mm, ent)(mE)
              }
            }, /*if (op==OpAdd)*/ Some(m.keys) /*else None*/) // XXXX commented out the if expression
          }
        case IfStmt(c, t, e) => sys.error("If statement not supported")
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
    val classLevelMaps = 
      // s0.triggers.filter(_.event match {
      //   case EventBatchUpdate(s) => true
      //   case _ => false
      // }).map(_.event match {
      //   //delta relations
      //   case EventBatchUpdate(schema) =>
      //     MapDef(delta(schema.name), TypeLong, schema.fields, null, LocalExp)
      //   case _ => null
      // }) ++
      // s0.triggers.flatMap { t => //local maps
      //   t.stmts.filter {
      //     case MapDef(_, _, _, _, _) => true
      //     case _ => false
      //   }.map {
      //     case m@MapDef(_, _, _, _, _) => m
      //     case _ => null
      //   }
      // } ++
      mapDefs.map {
        case (_, m@MapDef(_, _, _, _, _)) => m
      }.toList // XXX missing indexes
    globalMembersBlock = IR.reifyBlock {
      ctx0 = classLevelMaps.map {
        case MapDef(name, tp, keys, _, _) => if (keys.size == 0) {
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

    val allSchema = classLevelMaps.map({ case MapDef(name, tp, kt, _, _) => ctx0(name)._1.asInstanceOf[IR.Sym[_]] -> (kt.map(_._2) :+ tp).map(man) }) ++ tempMapSchema
    allSchema.foreach(x => {
      x._1.asInstanceOf[Sym[_]].attributes += StoreSchema(x._2)
      val idx = new IndexedCols
      idx.primary = (1 until x._2.size).toSeq
      x._1.asInstanceOf[Sym[_]].attributes += idx
    })
    tempMapSchema.clear()
    val allnames = classLevelMaps.collect { case MapDef(name, _, _, _, _) => name }
    val iGlobal = allnames.map(ctx0(_)._1.asInstanceOf[Sym[_]])
    val initTP = TransactionProgram(globalMembersBlock, iGlobal, tsResBlks, Nil, Nil)
    val optTP = new Optimizer(IR).optimize(initTP)

    val printInfoDef = doc"def printMapsInfo() = {}"

    val res = genCodeForProgram(optTP)
//    val ext = if(cTransformer) "hpp" else "scala"
//    val trigs = new PrintWriter(s"$cgOpts.className.$ext")
//    trigs.print(res._1)
//    trigs.close()
    res
  }

  def genCodeForProgram[T](prg: TransactionProgram[T]): (String, String, String)

}

class PardisScalaGen(cgOpts: CodeGenOptions) extends PardisGen(cgOpts, if (Optimizer.onlineOpts) new StoreDSLOptimized {} else new StoreDSL {}) with IScalaGen {

  import IR._
  import ddbt.lib.TypeHelper.Scala._

  override val codeGen = new StoreScalaCodeGenerator(IR)

  override def getTriggerNameArgs(t: Trigger) = t.event match {
    case EventReady => ("SystemReady", Nil)
    case EventBatchUpdate(Schema(n, cs)) => ("BatchUpdate" + n, cs)
    case EventInsert(Schema(n, cs)) => ("Add" + n, cs)
    case EventDelete(Schema(n, cs)) => ("Del" + n, cs)
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

  override def genInitializationFor(map: String, keyNames: List[(String, Type)], keyNamesConcat: String) = {
    if (Optimizer.analyzeEntry) {
      val ctx = ctx0(map)
      val name = SEntry((ctx._2.map(_._2) :+ ctx._3).map(man)).name
      map + s".unsafeInsert($name(" + (if (Optimizer.secondaryIndex) "" else "false,") + keyNames.map(e => e._1).mkString(",") + ", 1L))"
    }
    else
      map + ".unsafeInsert(GenericEntry(\"SteNewSEntry\"," + keyNames.map(e => e._1).mkString(",") + ", 1L))"
  }

  override def toMapFunction(q: Query) = {
    val map = q.name
    val m = mapDefs(map)
    val mapKeys = m.keys.map(_._2)
    val nodeName = map + "_node"
    val res = nodeName + "_mres"
    def get(i: Int) = if (Optimizer.analyzeEntry) s"e._$i" else s"e.get($i)"
    if (q.expr.ovars.size > 0)
      "{ val " + res + " = new scala.collection.mutable.HashMap[" + tup(mapKeys.map(typeToString)) + "," + typeToString(q.expr.tp) + "](); " + map + ".foreach{e => " + res + " += ((" + (if (mapKeys.size >= 1) tup(mapKeys.zipWithIndex.map { case (_, i) => get(i + 1) }) else "e") + "," + get(if (mapKeys.size >= 1) (mapKeys.size + 1) else mapKeys.size) + ")) }; " + res + ".toMap }"
    else {
      q.name
    }
  }

  override val additionalImports: String = "import ddbt.lib.store._\n"

  override def getEntryDefinitions = "" //TODO:SBJ : Need to be fixed for batch processing(input record type)  
}

class PardisCppGen(cgOpts: CodeGenOptions) extends PardisGen(cgOpts, if (Optimizer.onlineOpts) new StoreDSLOptimized {} else new StoreDSL {}) with ICppGen {
  override val codeGen: StoreCppCodeGenerator = new StoreCppCodeGenerator(IR)

  import IR._

  val pardisExtendEntryParam = !Optimizer.analyzeEntry || !Optimizer.secondaryIndex
  val pardisProfilingOn = Optimizer.profileStoreOperations || Optimizer.profileBlocks

  var streamTriggers = ""
  var mapTypes = ""
  var entryDefs = ""

  override def genCodeForProgram[T](optTP: TransactionProgram[T]) = {
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    var ts = ""
    codeGen.currentProgram = PardisProgram(optTP.structs, optTP.main, Nil)
    codeGen.refSymbols ++= optTP.tempVars.map(_._1)
    for (x <- optTP.codeBlocks) {
      import codeGen.{doc => _, _}

      val sTimeout = if(cgOpts.timeoutMilli > 0)
        s"""|if (tS > 0) { ++tS; return; }
            |if ((tN & 127) == 0) {
            |  gettimeofday(&t, NULL);
            |  tT = (t.tv_sec - t0.tv_sec) * 1000L;
            |  if (tT > ${cgOpts.timeoutMilli}) { tS = 1; return; }
            |}
            |""".stripMargin else ""
      var preBody = ""
      var postBody = ""
      if (!x._1.contains("system_ready")) {
        preBody = s"""
                    |BEGIN_TRIGGER(exec_stats,"${x._1.drop(1)}")
                    |BEGIN_TRIGGER(ivc_stats,"${x._1.drop(1)}")
                    |$sTimeout
                    |++tN;
         """.stripMargin
        postBody =
          s"""
             |clearTempMem();
             |END_TRIGGER(exec_stats,"${x._1.drop(1)}")
             |END_TRIGGER(ivc_stats,"${x._1.drop(1)}")
         """.stripMargin
      }
      val doc2 = preBody :: codeGen.blockToDocument((x._3)) :: postBody
      def argTypeToDoc(tp: TypeRep[_]) = tp match {
        case StringType => doc"const $tp&"
        case _ => doc"const $tp"
      }
      ts += doc"void on${x._1}(${x._2.map(s => argTypeToDoc(s.tp) :: doc" $s").mkDocument(", ")}) {" :/: Document.nest(2, doc2) :/: doc"\n}\n"
    }
    m3System.triggers.filter(_.event != EventReady).foreach(t => ts += (emitUnwrapFunction(t.event, m3System.sources) + "\n"))

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
        val ord = Index.getColumnNumFromLambda(Def.unapply(n.f).get.asInstanceOf[PardisLambda[_, _]])
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
        val copyFn = doc"FORCE_INLINE ${tag.typeName}* copy() const { ${tag.typeName}* ptr = (${tag.typeName}*) malloc(sizeof(${tag.typeName})); new(ptr) ${tag.typeName}(" :: fields.map(x => {
//          if (x.tpe == StringType)
//            doc"*${x.name}.copy()"
//          else
            doc"${x.name}"
        }).mkDocument(", ") :: "); return ptr; }"
        val streamOp = doc"""friend std::ostream& operator<<(std::ostream& os, const ${tag.typeName}& obj) {  os <<"(" <<${fields.map(x => doc"obj.${x.name}").mkDocument(doc""" << "," << """)} << ")"; return os; }"""
        val serializer = doc"template<class Archive> \nvoid serialize(Archive& ar, const unsigned int version) const {" :/:
          Document.nest(4, fields.map(x => doc"DBT_SERIALIZATION_NVP(ar,${x.name});").mkDocument("ar << ELEM_SEPARATOR;\n", "\nar << ELEM_SEPARATOR;\n", "\n")) :/: "}"

        "struct " :: tag.typeName :: " {" :/: Document.nest(2, fieldsDoc :/: constructor :/: constructorWithArgs :/: serializer :/: copyFn :/: streamOp) :/: "};"
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

    val toCheck = mutable.ArrayBuffer[String]() //Gather all maps for debug printing
    val idxSymNames = mutable.ArrayBuffer[String]()

    def genInitArrayLengths = {
      val tbls = idxSymNames.groupBy(_.split("Idx")(0)).map(t => t._1 -> t._2.map(StoreArrayLengths.getOrElse(_, "1")))
      tbls.map(t => doc"const size_t ${t._1}ArrayLengths[] = ${t._2.mkString("{", ",", "};")}").toList.mkDocument("\n") :\\:
        tbls.map(t => doc"const size_t ${t._1}PoolSizes[] = ${t._2.map(_ => "0").mkString("{0, ", ",", "};")}").toList.mkDocument("\n")
    }

    val stores = optTP.globalVars.map(s => {

      if (s.tp.isInstanceOf[StoreType[_]]) {
        def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"
        val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
        val idxTypes = idx2(s).filter(_._2 != "INone").map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
        val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

        val storeTypeDef = doc"typedef MultiHashMap<${entryTp}, char," :/: idxTypes.map(t => idxTypeName(t._2)).mkDocument(", ") :: doc"> ${s.name}_map;"
        val entryTypeDef = doc"typedef $entryTp ${s.name}_entry;"
        val initSize = if (Optimizer.initialStoreSize) doc"(${s.name}ArrayLengths, ${s.name}PoolSizes);" else doc";"
        val storeDecl = s.name :: "_map  " :: s.name :: initSize
        toCheck ++= idx2(s).filter(_._2 == "IHash").map(s => s._1.name)
        idxSymNames ++= idx2(s).filter(_._2 != "INone").map(s => s._1.name)
        val idxDecl = idx2(s).filter(_._2 != "INone").zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1} = * (${idxTypeName(t._2)} *)${s.name}.index[${t._2}];").mkDocument("\n")
        val primaryIdx = idx2(s)(0)
        idxTypeDefs :\\: storeTypeDef :\\: entryTypeDef :\\: storeDecl :\\: idxDecl
      } else {
        doc"${s.tp} ${s.name};"
      }
    }).mkDocument("\n", "\n\n\n", "\n")

    val tempMaps = optTP.tmpMaps.map(s => {
      toCheck ++= s._2.map(s => s.name)
      idxSymNames ++= s._2.map(s => s.name)
      val entryTp = s._1.tp.asInstanceOf[StoreType[_]].typeE
      codeGen.stmtToDocument(Statement(s._1, Def.unapply(s._1).get)) :/:
        s._2.map(i => codeGen.stmtToDocument(Statement(i, Def.unapply(i).get))).mkDocument("\n") //index refs

    }).mkDocument("\n\n") + "\n"

    val checks = doc"void checkAll() {" :/: Document.nest(2, {
      toCheck.map(s => doc"CHECK_STAT($s);").mkDocument("\n")
    }) :/: "}"

    val runtime = doc"void getRuntimeInfo() {" :/: Document.nest(2, {
      doc"""std::ofstream info("$infoFilePath");""" :\\:
        idxSymNames.map(s => doc"GET_RUN_STAT($s, info);").mkDocument("info << \"{\\n\";\n", "\ninfo <<\",\\n\";\n", "\ninfo << \"\\n}\\n\";") :\\:
        doc"info.close();"
    }) :/: "}"

    val ms = (entries :/: entryIdxes :/: genInitArrayLengths :/: stores :/: tempMaps :/: checks :/: runtime).toString

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

  override def getTriggerNameArgs(t: Trigger) = t.event match {
    case EventReady => ("_system_ready_event", Nil)
    case EventBatchUpdate(Schema(n, cs)) => ("_batch_update_" + n, cs)
    case EventInsert(Schema(n, cs)) => ("_insert_" + n, cs)
    case EventDelete(Schema(n, cs)) => ("_delete_" + n, cs)
  }

  def genTrigger(t: Trigger, s0: System): String = {
    val (name, params, block) = genTriggerPardis(t, s0)
    val Cname = t.event match {
      case EventReady => "system_ready_event"
      case EventBatchUpdate(sc@Schema(n, cs)) => "batch_update_" + n
      case EventInsert(Schema(n, cs)) => "insert_" + n
      case EventDelete(Schema(n, cs)) => "delete_" + n
    }
    val code = codeGen.blockToDocument(block)
    s"void on_$Cname(" + params.map(i => "const")
  }

  override def emitIncludeHeaders = 
    s"""|#define SC_GENERATED 1
        |#include "program_base.hpp"
        |#include "hpds/KDouble.hpp"
        |#include "hash.hpp"
        |#include "mmap/mmap.hpp"
        |#include "hpds/pstring.hpp"
        |#include "hpds/pstringops.hpp"
        |""".stripMargin +    
    stringIf(pardisProfilingOn, "#define EXEC_PROFILE 1\n") +
    "#include \"ExecutionProfiler.h\"\n"

  override protected def emitMapTypes(s0: System) = mapTypes  // genPardis._2

  override protected def emitTempEntryTypes = ""

  override protected def emitLocalEntryDefinitions = entryDefs   // genPardis._3  tmpEntrySC

  override protected def emitMapDefinitions(maps: List[MapDef], queries: List[Query]) = "" 

  override protected def emitTempMapDefinitions = ""

  override protected def emitStreamTriggers(triggers: List[Trigger], sources: List[Source]) = streamTriggers // genPardis._1  

  override protected def emitNonTLQMapInitializer(maps: List[MapDef], queries: List[Query]) = ""

  override protected def emitTLQDefinitions(queries: List[Query]) = ""

  override protected def emitTLQMapInitializer(maps: List[MapDef], queries: List[Query]) = ""

  override protected def emitTakeSnapshotBody = 
    super.emitTakeSnapshotBody + 
    "\n// checkAll(); //print bucket statistics\n" +
    stringIf(pardisProfilingOn, "// ") + 
    "ExecutionProfiler::printProfileToFile(\"profile${cgOpts.className}.csv\");\n"

  override protected def emitFieldNames(fields: List[(String, Type)]) = 
    stringIf(pardisExtendEntryParam, "false_type(), ") + super.emitFieldNames(fields)

  override protected def emitInsertToMapFunc(map: String, entry: String) = 
    map + ".insert_nocheck(" + entry + ");"

  override protected def prepareCodegen(s0: System): Unit = {
    val x = genPardis(s0)
    streamTriggers = x._1
    mapTypes = x._2
    entryDefs = x._3
  }
}
class PardisScalaJSGen(cgOpts: CodeGenOptions) extends PardisScalaGen(cgOpts){

  override def apply(s0: System): String = {

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


      val ms = s0.maps.map(genMap).mkString("\n") // maps

      ms + "\n" + genQueries(s0.queries) + "\n" + ts
    }
    val (str,ld0, gc) = if (lms != null) (strLMS,ld0LMS, gcLMS)
    else genInternals(s0)

    // optional preloading of static tables content

    freshClear()
    val snap: String = emitGetSnapshotBody(s0.queries)
    val pp = ""

    clearOut()
    emitMainClass(s0.queries, s0.sources,s0, body, pp, ld0, gc, snap, str)
  }

  def emitMainClass(queries: List[Query], sources: List[Source],s0: System, body: String, pp: String, ld: String, gc: String, snap: String, str: String) = {
    val sResults = queries.zipWithIndex.map { case (q, i) =>
      val ovars = q.expr.ovars
      val skeys = ovars.map(k => "\"" + k._1.toUpperCase + "\"").mkString(", ")
      "println(\"<" + q.name + ">\\n\" + M3Map.toStr(res(" + i + ")" +
        stringIf(ovars.nonEmpty, ", List(" + skeys + ")") + ")+\"\\n\" + \"</" + q.name + ">\\n\")"
    }.mkString("\n")
    val sStreams = streams(sources)
    s"""|package ${cgOpts.packageName}
        |
        |import lib.storeScala{Entry, EntryIdx, IHash, Store}
        |import Helper._
        |
        |import scala.collection.mutable
        |import scala.concurrent.ExecutionContext.Implicits.global
        |import scala.scalajs.js.typedarray.ArrayBufferInputStream
        |${additionalImports}
        |
        |object ${cgOpts.className} {
        |
        |${ind(getEntryDefinitions)}
        |
        |def exec(): Unit = {
        |
        |    var res:List[scala.collection.immutable.Map[_ <: Any, Any]]=List()
        |
        |${ind(sStreams, 3)}
        |
        |  def execute1(streams: Streams, list: List[ArrayBufferInputStream]) = {
        |      loadTables(list);
        |      onSystemReady();
        |      goThroughStreams(streams, dispatchFnNoActor _)
        |        println("<snap>")
        |${ind(sResults, 4)}
        |        println("</snap>")
        |        }
        |  def dispatchFnNoActor(e: StreamEvent) = e match {
        |${ind(str, 2)}
        |    case EndOfStream | GetSnapshot(_) =>
        |      ${onEndStream} res=res:::(${snap})
        |  }
        |def loadTables(list: List[ArrayBufferInputStream]) {
        |       ${ind(ld)}
        |    }
        |}
        |    ////
        |${ind(body)}
        |
        |${ind(gc)}
        |}
        |
        |
        |  ${pp}
        |
        |""".stripMargin
  }
  override protected def genStream(s: Source): (String, String, String) = {
    val in = s.in match {
      case SourceFile(path) =>
        {
          val trigger="dbtoaster-experiments-data"
          val index=path.indexOfSlice(trigger)
          val index1= path.indexOf('/',index+trigger.length)
          val newPath="https://raw.githubusercontent.com/dbtoaster/dbtoaster-experiments-data/master/"+path.substring(index1+1)
          "getABInputStream(\"" + newPath + "\")"
        }
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

  override def streams(sources: List[Source]) = {
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
    var count=0;

    var getAB=""
    var inExecute=""
    var listOfTables=",List(  "
      fixOrderbook(sources).map { s =>
        val (in, ad, sp) = genStream(s)
        val ab="arraybuffer"+count
        val p1= in+".foreach("+ab+"=>\n"
        getAB=getAB+p1
        if(!s.isStream){
          listOfTables=listOfTables+ab+", "
        }else{
          val p2="\n ("+ab+","+ad+", "+sp+")"+","
          inExecute=inExecute+p2
        }
        count=count+1


      }.mkString(",\n")

    listOfTables=listOfTables.dropRight(2)
    def repeatChar(char:Char, n: Int) = List.fill(n)(char).mkString
    val ss =getAB+ "\nexecute1(Seq(\n"+inExecute+"\n)"+listOfTables+")"+repeatChar(')',count)+"\n)"

    ind(ss)
  }


  override def genInternals(s0: System, nextSkip: String = "context.become(receive_skip)"): (String, String, String) = {
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
    val skip =""
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
    var count= -1
    val tableInitialization = s0.sources.filterNot { _.isStream }.map {
      s => {
        count=count+1
        val (in, ad, sp) = genStream(s)
        val (i, o, _, pl) = ev(s.schema)
        "SourceMux({ case TupleEvent(TupleInsert, rn, List(" + i +
          ")) => " + genInitializationFor(s.schema.name, pl, o) + " }, Seq((" +
          "list("+count+")" + ", " + ad + ", " + sp + "))).read;"
      }

    }.mkString("\n");

    (singleStr + batchStr, tableInitialization, consts)
  }
  override val additionalImports: String = "import HelperGS._\nimport Messages._\nimport Functions._\nimport lib.Entry"



}
