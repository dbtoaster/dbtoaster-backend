package ddbt.codegen

import ddbt.ast.M3._
import ddbt.ast._
import compiler._
import ddbt.lib.ManifestHelper
import ddbt.lib.ManifestHelper._
import ddbt.lib.store.deep.StoreDSL
import ddbt.lib.store.{Store, Entry}
import ch.epfl.data.pardis.types.PardisTypeImplicits._


abstract class PardisGen(override val cls:String="Query", val impl: StoreDSL) extends IScalaGen {

//  import ch.epfl.data.pardis.types.PardisTypeImplicits._
  import scala.language.implicitConversions
  import ddbt.lib.store.deep._
  import impl._

  def typeToTypeRep(tp: Type): TypeRep[Any] = {
    tp match {
      case TypeLong => runtimeType[Long]
      case TypeDouble => runtimeType[Double]
      //    case TypeString => runtimeType[]
      case TypeDate => runtimeType[Date]
    }
  }.asInstanceOf[TypeRep[Any]]


  def me(ks:List[Type],v:Type=null) = manEntry(if (v==null) ks else ks:::List(v))
  def mapProxy(m:Rep[_]) = impl.store2StoreOpsCls(m.asInstanceOf[Rep[Store[Entry]]])

  // Expression CPS transformation from M3 AST to LMS graph representation
  //   ex : expression to convert
  //   co : continuation in which the result should be plugged
  //   am : shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def expr(ex:Expr, co: Rep[_]=>Rep[Unit], am:Option[List[(String,Type)]]=None):Rep[Unit] = ex match {
    case Ref(n) => co(cx(n))
    case Const(tp,v) => ex.tp match {
      case TypeLong => co(impl.unit(v.toLong))
      case TypeDouble => co(impl.unit(v.toDouble))
      case TypeString => co(impl.unit(v))
      case TypeDate => sys.error("No date constant conversion") //co(impl.unit(new java.util.Date()))
      case _ => sys.error("Unsupported type "+tp)
    }
    case Exists(e) => expr(e,(ve:Rep[_]) => co(impl.__ifThenElse(impl.infix_!=(ve.asInstanceOf[Rep[Long]],impl.unit(0L)),impl.unit(1L),impl.unit(0L))))
    case Cmp(l,r,op) => expr(l,(vl:Rep[_]) => expr(r,(vr:Rep[_]) => co(cmp(vl,op,vr,ex.tp)) )) // formally, we should take the derived type from left and right, but this makes no difference to LMS
    case Mul(l,r) => expr(l,(vl:Rep[_])=> expr(r,(vr:Rep[_]) => co(mul(vl,vr,ex.tp)),am),am)
    case a@Add(l,r) =>
      if (a.agg==Nil) {
        val cur=cx.save
        expr(l,(vl:Rep[_])=>{
          cx.load(cur)
          expr(r,(vr:Rep[_])=>{
            cx.load(cur)
            co(add(vl,vr,ex.tp).asInstanceOf[Rep[_]])
          },am)
        },am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) =>
          val cur=cx.save
          expr(l,co,am)
          cx.load(cur)
          expr(r,co,am)
          cx.load(cur)
          impl.unit(())
        case _ =>
          implicit val mE=me(a.agg.map(_._2),a.tp)
          val acc = impl.m3temp()(mE)
          val inCo = (v:Rep[_]) => impl.m3add(acc,impl.stNewEntry2(acc, (a.agg.map(x=>cx(x._1))++List(v)) : _*))(mE)
          val cur = cx.save
          expr(l,inCo,Some(a.agg)); cx.load(cur)
          expr(r,inCo,Some(a.agg)); cx.load(cur)
          foreach(acc,a.agg,a.tp,co)
      }
    case _ => sys.error("Unimplemented: "+ex)
  }

  def foreach(map:Rep[_],keys:List[(String,Type)],value_tp:Type,co:Rep[_]=>Rep[Unit]) = null

  def mul(l:Rep[_], r:Rep[_], tp:Type) = {
    tp match {
      case TypeLong | TypeDouble => impl.m3apply("mul",List(l,r),tp)
      case _ => sys.error("Mul(l,r) only allowed on numeric types")
    }
  }

  def add(l:Rep[_], r:Rep[_], tp:Type) = {
    @inline def plus[T:TypeRep]() = impl.numeric_plus[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
    tp match {
      case TypeLong => plus[Long]()
      case TypeDouble => plus[Double]()
      case _ => sys.error("Add(l,r) only allowed on numeric types")
    }
  }

  def cmp(l:Rep[_], op:OpCmp, r:Rep[_], tp:Type): Rep[Long] = {
    @inline def cmp2[T:TypeRep](vl:Rep[_],vr:Rep[_]): Rep[Boolean] = {
      val (ll,rr)=(vl.asInstanceOf[Rep[T]],vr.asInstanceOf[Rep[T]])
      op match {
        case OpEq => impl.infix_==[T,T](ll,rr)
        case OpNe => impl.infix_!=[T,T](ll,rr)
        // case OpGt => impl.ordering_gt[T](ll,rr)
        // case OpGe => impl.ordering_gteq[T](ll,rr)
      }
    }
    impl.__ifThenElse(tp match {
      case TypeLong => cmp2[Long](l,r)
      case TypeDouble => cmp2[Double](l,r)
      case TypeString => cmp2[String](l,r)
      case TypeDate => cmp2[Long](impl.dtGetTime(l.asInstanceOf[Rep[java.util.Date]]),impl.dtGetTime(r.asInstanceOf[Rep[java.util.Date]]))
      case _ => sys.error("Unsupported type")
    },impl.unit(1L),impl.unit(0L))
  }

  def filterStatement(s:Stmt) = s match {
    case StmtMap(m,_,_,_) if m.name.endsWith("_DELTA") => false
    case _ => true
  }

  var cx : Ctx[Rep[_]] = null
  // Trigger code generation
  def genTriggerLMS(t:Trigger, s0:System) = {
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtBatchUpdate(Schema(n,cs)) => ("BatchUpdate"+n,cs)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    var params = ""
    val block = impl.reifyBlock {
      params = t.evt match {
        case EvtBatchUpdate(Schema(n,_)) =>
          val rel = s0.sources.filter(_.schema.name == n)(0).schema
          val name = rel.deltaSchema

          name+":Store["+impl.storeEntryType(ctx0(name)._1)+"]"
        case _ =>
          args.map(a=>a._1+":"+a._2.toScala).mkString(", ")
      }
      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        ctx0.map{ case (name,(sym,keys,tp)) => (name, sym) }.toList union
          {
            t.evt match {
              case EvtBatchUpdate(Schema(n,_)) =>
                Nil
              case _ =>
                args.map{ case (name,tp) => (name,impl.freshNamed(name)(typeToTypeRep(tp))) }
            }
          }
        ).toMap)
      // Execute each statement
      t.stmts.filter(filterStatement).map {
        case StmtMap(m,e,op,oi) => cx.load()
          if (m.keys.size==0) {
            val mm = m.tp match {
              case TypeLong => impl.Var(cx(m.name).asInstanceOf[Rep[impl.Var[Long]]])
              case TypeDouble => impl.Var(cx(m.name).asInstanceOf[Rep[impl.Var[Double]]])
              case TypeString => impl.Var(cx(m.name).asInstanceOf[Rep[impl.Var[String]]])
              //case TypeDate => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[java.util.Date]]])
              case _ => sys.error("Unsupported type "+m.tp)
            }
            expr(e,(r:Rep[_]) => op match { case OpAdd => impl.var_plusequals(mm,r) case OpSet => impl.__assign(mm,r) })
          } else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.tks ++ List(m.tp)).asInstanceOf[TypeRep[Entry]]
            if (op==OpSet) impl.stClear(mm)
            oi match { case None => case Some(ie) =>
              expr(ie,(r:Rep[_]) => {
                val ent = impl.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)) : _*)
                impl.__ifThenElse(impl.infix_==(stProxyGet(mm, m.keys.zipWithIndex.map{ case (n,i) => (i+1,cx(n))} : _*),
                  impl.unit(null)),impl.m3set(mm,ent),impl.unit(()))
              })
            }
            cx.load()
            expr(e,(r:Rep[_]) => {
              val ent = impl.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)) : _*)
              op match { case OpAdd | OpSet => impl.m3add(mm, ent)(mE) }
            }, /*if (op==OpAdd)*/ Some(m.keys zip m.tks) /*else None*/) // XXXX commented out the if expression
          }
        case m@MapDef(name,tp,keys,_) =>
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      impl.unit(())
    }
    cx = null; (name,params,block)
  }

  var ctx0 = Map[String,(Rep[_], List[(String,Type)], Type)]()
  override def genPardis(s0: M3.System): (String, String, String, String) = {
    val tsResBlks = s0.triggers.map(genTriggerLMS(_,s0)) // triggers (need to be generated before maps)
    ("par1", "par2", "par3", "par4")
//    val context = new MirrorStoreDSL {
//      implicit def liftInt(i: Int): Rep[Int] = unit(i)
//
//      implicit val typeE = typeRep[Int].asInstanceOf[TypeRep[Entry]]
//
//      def prog = {
//        val v1 = __newMStore[Entry](__newArray[Entry](3), __newArray[Entry](3))
//        //          v1.insert(unit(1))
//        v1.insert(unit(12).asInstanceOf[Rep[Entry]])
//        v1.insert(unit(14).asInstanceOf[Rep[Entry]])
//      }
//    }
//    System.out.println(context.reifyBlock(context.prog))
//
//    import context._
//    new MirrorStoreCompiler(context).compile(prog, "GeneratedMirrorApp")
//
//    val (str, ld0, _) = genInternals(s0)
//    ("Must be added", str, ld0, consts)
  }
}

class PardisScalaGen(cls:String="Query") extends PardisGen(cls, new StoreDSL {})