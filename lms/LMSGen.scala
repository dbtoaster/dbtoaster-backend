package ddbt.codegen
import ddbt.codegen.lms._
import ddbt.ast._
import ddbt.lib._

import java.util.Date

// TPCH11c and TPCH16 seem to block forever
// Symbol errors in sbt 'toast examples/queries/simple/rs_joinon.sql -l lms'

class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  import ddbt.Utils.fresh
  import ManifestHelper.man

  val impl = ScalaExpGen
  import impl.Rep
  type LMSContext = Map[String, Rep[_]]
  val ctx0 = Map[String, Rep[_]]() // empty context

  override def genTrigger(t:Trigger):String = {
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    // the ctx argument contains all the symbols that are available in the current context
    // the returned context is only _NEW_ symbols that have been added to the original context
    def expr(ex:Expr,ctx:LMSContext, co: (Rep[_], LMSContext) => (Rep[Unit], LMSContext),am:Option[List[(String,Type)]]=None):(Rep[Unit],LMSContext) = ex match {
      case Ref(n) => co(ctx(n), ctx0)
      case Const(tp,v) => ex.tp match {
        case TypeLong => co(impl.unit(v.toLong), ctx0)
        case TypeDouble => co(impl.unit(v.toDouble), ctx0)
        case TypeString => co(impl.unit(v), ctx0)
        case TypeDate => sys.error("date is not implemented for Const(tp, v)") //co(impl.unit(new java.util.Date())) // XXX: set correct value
      }
      case Mul(l,r) => expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
                       expr(r, ctx ++ newCtx1, (vr:Rep[_], newCtx2: LMSContext) => co(mul(vl,vr,ex.tp), newCtx1 ++ newCtx2) ))
      case a@Add(l,r) =>
        if (a.agg==Nil) expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
                        expr(r, ctx, (vr:Rep[_], newCtx2: LMSContext) => co(add(vl,vr,ex.tp), newCtx1 ++ newCtx2) ))
        else am match {
          case Some(t) if t==a.agg => expr(l,ctx,co,am); expr(r,ctx,co,am)
          case _ =>
            val acc = impl.k3temp(a.agg.map(_._2),ex.tp)
            val inCo = (v:Rep[_],c:LMSContext) => (impl.k3add(acc,a.agg.map(x=>c(x._1)),v),c)
            expr(l,ctx,inCo,Some(a.agg))
            expr(r,ctx,inCo,Some(a.agg))
            foreach(acc,a.agg.zipWithIndex.map{case((k,t),i)=>(k,t,i)},a.tp,ctx,co)
        }

      case Cmp(l,r,op) => expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
        expr(r, ctx, (vr:Rep[_], newCtx2: LMSContext) => {
          co(cmp(vl,op,vr,ex.tp), newCtx1 ++ newCtx2) // formally, we should take the derived type from left and right, but this makes no difference to LMS
        })
      )
      case Exists(e) => expr(e, ctx, (ve:Rep[_], newCtx: LMSContext) => 
        co(impl.__ifThenElse(impl.notequals(ve,impl.unit(0L)),impl.unit(1L),impl.unit(0L)),newCtx)
      )
      case Lift(n,e) => expr(e, ctx, (ve:Rep[_], newCtx: LMSContext) => 
        if (!ctx.contains(n)) co(impl.unit(1L),newCtx+(n -> ve))
        else co(cmp(ctx(n),OpEq,ve,e.tp),newCtx)
      )
      case Apply(fn,tp,as) =>
        def ev2(es:List[Expr],vs:List[Rep[_]],c:LMSContext) : (Rep[Unit],LMSContext) = es match {
          case x :: xs => expr(x,ctx++c,(v:Rep[_],nc:LMSContext) => ev2(xs,vs:::v::Nil,c++nc))
          case Nil => co(impl.k3apply(fn,vs,tp),c)
        }
        ev2(as,Nil,ctx0)

      case MapRef(n,tp,ks) => 
        val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
        if(ki.size == 0) { // all keys are bound
          co(impl.k3get(ctx(n),ko.map{case (k,i)=>ctx(k)},tp), ctx0) 
        } else { // we need to iterate over all keys not bound (ki)
          val mapRef = ctx(n)
          val slicedMapRef = if(ko.size == 0) mapRef
          else impl.k3slice(mapRef,slice(n,ko.map{case (k,i)=>i}),ko.map{case (k,i)=>ctx(k)})
          val key = (ks.zip(maps(n).keys.map(_._2))).zipWithIndex map { case ((n,k),i) => (n,k,i) }
          foreach(slicedMapRef,key,tp,ctx,co,"m")
        }

      case a@AggSum(ks,e) =>
        val agg_keys = (ks zip a.tks).filter{ case (n,t)=> !ctx.contains(n) } // the aggregation is only made on free variables
        val acc = if (agg_keys.size==0) impl.k3var(ex.tp) else impl.k3temp(agg_keys.map(_._2),ex.tp)
        // Accumulate expr(e) in the acc
        val coAcc = (v: Rep[_], ctxAcc: LMSContext) => (impl.k3add(acc, agg_keys.map(x=>(ctx ++ ctxAcc)(x._1)), v), ctxAcc)
        expr(e,ctx,coAcc,Some(agg_keys)) // returns (Rep[Unit],ctx) and we ignore ctx
        // Iterate over acc and call original continuation
        if (agg_keys.size==0) co(impl.k3get(acc,Nil,ex.tp),ctx) // accumulator is a single result
        else am match {
          case Some(t) if (t==agg_keys) => expr(e,ctx,co,am)
          case _ => 
            val key = agg_keys.zipWithIndex map { case ((n,k),i) => (n,k,i) }
            foreach(acc,key,a.tp,ctx,co,"a")
        }
      case _ => sys.error("Unimplemented: "+ex)
    }

    def foreach(map:Rep[_],key:List[(String,Type,Int)],value_tp:Type,ctx:LMSContext,co:(Rep[_],LMSContext)=>(Rep[Unit],LMSContext),prefix:String=""):(Rep[Unit],LMSContext) = {
      var newCtx = ctx0
      var keyArg: Rep[_] = null
      var valArg: Rep[_] = null
      val body = impl.reifyEffects {
        keyArg = impl.named(fresh(prefix+"k"),true)(man(key.filter(k=> !ctx.contains(k._1)).map(_._2)))
        valArg = impl.named(fresh(prefix+"v"),value_tp,true)
        val innerCtx = ctx ++ key.filter(k=> !ctx.contains(k._1)).map{ case (n,t,i) => (n,accessTuple(keyArg,t,key.size,i)) }
        val (b,nc) = co(valArg, innerCtx); newCtx=nc; b
      }
      (impl.k3foreach(map, keyArg, valArg , body), newCtx)
    }

    def accessTuple(tuple: Rep[_],elemTp:Type,sz: Int, idx: Int)(implicit pos: scala.reflect.SourceContext): Rep[_] = sz match {
        case 1 => tuple
        case _ => impl.getClass.getDeclaredMethod("tuple%d_get%d".format(sz,idx+1),Class.forName("java.lang.Object"), Class.forName("scala.reflect.Manifest"), Class.forName("scala.reflect.SourceContext"))
                   .invoke(impl, tuple, man(elemTp), pos).asInstanceOf[Rep[_]]
    }

    def mul(l:Rep[_], r:Rep[_], tp:Type) = {
      @inline def times[T:Numeric:Manifest]() = impl.numeric_times[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
      tp match {
        case TypeLong => times[Long]()
        case TypeDouble => times[Double]()
        case _ => sys.error("Mul(l,r) only allowed on numeric types")
      }
    }

    def add(l:Rep[_], r:Rep[_], tp:Type) = {
      @inline def plus[T:Numeric:Manifest]() = impl.numeric_plus[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
      tp match {
        case TypeLong => plus[Long]()
        case TypeDouble => plus[Double]()
        case _ => sys.error("Add(l,r) only allowed on numeric types")
      }
    }

    def cmp(l:Rep[_], op:OpCmp, r:Rep[_], tp:Type): Rep[Long] = {
      @inline def cmp2[T:Ordering:Manifest](vl:Rep[_],vr:Rep[_]): Rep[Boolean] = {
        val (ll,rr)=(vl.asInstanceOf[Rep[T]],vr.asInstanceOf[Rep[T]])
        op match {
          case OpEq => impl.equals[T,T](ll,rr)
          case OpNe => impl.notequals[T,T](ll,rr)
          case OpGt => impl.ordering_gt[T](ll,rr)
          case OpGe => impl.ordering_gteq[T](ll,rr)
        }
      }
      impl.__ifThenElse(tp match {
        case TypeLong => cmp2[Long](l,r)
        case TypeDouble => cmp2[Double](l,r)
        case TypeDate => cmp2[Long](impl.dtGetTime(l.asInstanceOf[Rep[Date]]),impl.dtGetTime(r.asInstanceOf[Rep[Date]]))
        case TypeString => cmp2[String](l,r)
      },impl.unit(1L),impl.unit(0L))
    }
    
    val triggerBlock = impl.reifyEffects {
      // Trigger context
      val ctxTrigger:LMSContext=(
        maps.map{ case (name,MapDef(_,_,keys,_)) => if (keys.size==0) (name,impl.named[K3Var[_]](name,true)) else (name,impl.named[K3Map[_,_]](name,true)) }.toList union
        args.map{ case (name,tp) => (name,impl.named(name,tp)) }
      ).toMap
      // Execute each statement
      t.stmts.map {
        case StmtMap(m,e,op,oi) =>
          val mm = ctxTrigger(m.name)
          if (op==OpSet && m.keys.size>0) impl.k3clear(mm)
          oi match { case None => case Some(ie) => 
            expr(ie,ctxTrigger,(r:Rep[_],c:LMSContext) => { val keys = m.keys.map(ctxTrigger++c)
               (impl.__ifThenElse(impl.equals(impl.k3get(mm,keys,m.tp),impl.unit(0L)),impl.k3set(mm,keys,r),impl.unit(())),c)
            })
          }
          val co = (r:Rep[_],c:LMSContext) => (op match {
            case OpAdd => impl.k3add(mm,m.keys.map(ctxTrigger++c),r)
            case OpSet => impl.k3set(mm,m.keys.map(ctxTrigger++c),r)
          },c)
          expr(e,ctxTrigger,co)._1
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      impl.unit(())
    }
    "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ddbt.Utils.ind(impl.emit(triggerBlock))+"\n}"
  }

  var maps = Map[String,MapDef]() // global maps, to be replaced by a Map[String,LMS_K3Map]
  override def apply(s0:System):String = {
    maps=s0.maps.map(m=>(m.name,m)).toMap; val r=super.apply(s0); maps=Map(); r
  }
}

  /*
  def newVariable(tp: Type): impl.Var[Any] = tp match {
    case TypeLong => impl.var_new(impl.unit(0L))
    case TypeDouble => impl.var_new(impl.unit(0.0))
    case _ => sys.error("newVariable(tp) only allowed on numeric types")
  }
  */
  /*
  def tup(ks: List[Rep[_]]): Rep[_] = ks.size match {
    case 1 => ks.head
    case 2 => impl.make_tuple2((ks(0),ks(1)))
    case 3 => impl.make_tuple3((ks(0),ks(1),ks(2)))
    case 4 => impl.make_tuple3((ks(0),ks(1),ks(2),ks(3)))
    case 5 => impl.make_tuple3((ks(0),ks(1),ks(2),ks(3),ks(4)))
    case 6 => impl.make_tuple3((ks(0),ks(1),ks(2),ks(3),ks(4),ks(5)))
  }
  */

  // def createTuple(elems: List[Rep[_]]): Rep[_] = elems.size match {
  //   case 1 => impl.getClass.getDeclaredMethod("make_tuple1",impl.Exp[Any].getClass).invoke(impl,elems(0)).asInstanceOf[Rep[_]]
  //   case 2 => impl.getClass.getDeclaredMethod("make_tuple2",impl.Exp[Any].getClass).invoke(impl,elems(0),elems(1)).asInstanceOf[Rep[_]]
  //   case 3 => impl.getClass.getDeclaredMethod("make_tuple3",impl.Exp[Any].getClass).invoke(impl,elems(0),elems(1),elems(2)).asInstanceOf[Rep[_]]
  //   case _ => sys.error("createTupple(elems) only allowed on tuples of size <= 3")
  // }
  //def extractMapKeyParamType(mapName: String): 
  //def getMapKeyNames(name: String): List[String] = maps(name).keys.map(_._1)
  //def getMapKeyTypes(name: String): List[Type] = maps(name).keys.map(_._2)

  /*
  def setSymName(s: impl.Sym[Any], name: String): impl.Sym[Any] = {
    val SymNameAttributeKey = "sn"
    s.attributes.update(SymNameAttributeKey, name)
    s
  }
  def freshRef(tp: Type, name: String): impl.Sym[_] = freshRefManifest(man(tp), name)
  def freshRef(tp: List[Type], name: String): impl.Sym[_] = freshRefManifest(man(tp), name)
  def freshRefManifest[T:Manifest](mf: Manifest[T], name: String): impl.Sym[T] = setSymName(impl.fresh[T], name).asInstanceOf[impl.Sym[T]]
  */
