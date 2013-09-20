package ddbt.codegen
import ddbt.codegen.lms._

import ddbt.ast._
import ddbt.lib._
//import toasterbooster._
import scala.virtualization.lms.internal._
import scala.virtualization.lms.common._

class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  val impl = ScalaExpGen
  import impl.Rep
  import ManifestHelper.man
  /*
  We need specific LMS nodes for
  - K3Map / K3Var / K3Temp : pass key as list of symbols, specific name as a string (automatic for temp)
    + foreach,get,add/set, ...
    ==> Need to be adapted from previous version / try to provide common interface for all of them
  - Named fresh (for function arguments)
  - Mirror of the user-defined functions library => some functions should be inlined, others not
  */

  override def genTrigger(t:Trigger):String = {
    //val outStream = new java.io.StringWriter
    //val impl = new Impl(new java.io.PrintWriter(outStream), "org.dbtoaster", false) with DSL
    //val impl = new Impl
    
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }



    type LMSContext = Map[String, Rep[_]]
    val ctx0 = Map[String, Rep[_]]() // empty context

    var exprrrr = ""
    // the ctx argument contains all the symbols that are available in the current context
    // the returned context is only _NEW_ symbols that have been added to the original context
    
    // XXX: we need a continuation here somewhere that is just one operation done on the variable
    def expr(ex:Expr,ctx:LMSContext, co: (Rep[_], LMSContext) => (Rep[Unit], LMSContext)):(Rep[Unit],LMSContext) = ex match {
      case Ref(n) => co(ctx(n), ctx0)
      case Const(tp,v) => ex.tp match {
        case TypeLong => co(impl.unit(v.toLong), ctx0)
        case TypeDouble => co(impl.unit(v.toDouble), ctx0)
        case TypeString => co(impl.unit(v), ctx0)
        case TypeDate => sys.error("date is not implemented for Const(tp, v)") //co(impl.unit(new java.util.Date())) // XXX: set correct value
      }
      case Mul(l,r) => expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
        expr(r, ctx ++ newCtx1, (vr:Rep[_], newCtx2: LMSContext) => {
          co(muliply(ex.tp,vl,vr), newCtx1 ++ newCtx2)
        })
      )
      case Add(l,r) => expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
        expr(r, ctx, (vr:Rep[_], newCtx2: LMSContext) => {
          co(addition(ex.tp,vl,vr), newCtx1 ++ newCtx2)
        })
      )
      case Cmp(l,r,op) => expr(l, ctx, (vl:Rep[_], newCtx1: LMSContext) => 
        expr(r, ctx, (vr:Rep[_], newCtx2: LMSContext) => {
          co(comparison(ex.tp,vl,op,vr), newCtx1 ++ newCtx2)
        })
      )
      case Exists(e) => expr(e, ctx, (ve:Rep[_], newCtx: LMSContext) => 
        co(impl.__ifThenElse(impl.notequals(ve,impl.unit(0)),impl.unit(1),impl.unit(0)),newCtx)
      )
      case Lift(n,e) => expr(e, ctx, (ve:Rep[_], newCtx: LMSContext) => 
        if (!ctx.contains(n))
          co(impl.unit(1) ,newCtx + (n -> ve))
        else co(ex.tp match {
          case TypeLong => cmp[Long](ctx(n),OpEq,ve)
          case TypeDouble => cmp[Double](ctx(n),OpEq,ve)
          case _ => sys.error("lift")
        },newCtx)
      )
      case Apply(fn,tp,as) =>
        def ev2(es:List[Expr],vs:List[Rep[_]],c:LMSContext) : (Rep[Unit],LMSContext) = es match {
          case x :: xs => expr(x,ctx++c,(v:Rep[_],nc:LMSContext) => ev2(xs,vs:::v::Nil,c++nc))
          case Nil => co(impl.k3apply(fn,vs,tp),c)
        }
        ev2(as,Nil,ctx0)


      case MapRef(n,tp,ks) => 
        if(ks.size == 0) { //sure it's a K3Var
          co(impl.k3get(ctx(n),Nil,tp), ctx0)
        } else { // otherwise it's a K3Map
          val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
          if (ki.size==0) co(impl.k3get(ctx(n),ko.map{case (k,i)=>ctx(k)},tp), ctx0) // all keys are bound
          else { 
            val mapRef = ctx(n)
            val slicedMapRef = if(ko.size > 0) {
              impl.k3slice(mapRef,slice(n,ko.map{case (k,i)=>i}),ko.map{case (k,i)=>ctx(k)})
            } else {
              mapRef
            }
            val keyArg = freshRef(getMapKeyTypes(n))
            val valueArg = freshRef(tp)
            val innerCtx = ctx ++ ks.zipWithIndex.filter{ case (k,v) => !ctx.contains(k) }.map{ case (kPart,i) => (kPart,accessTuple(keyArg,maps(n).keys(i)._2,ks.size,i)) }
            val (body, newCtx) = co(valueArg, innerCtx)

            (impl.k3foreach(slicedMapRef, keyArg, valueArg , body), newCtx)
          }
        }
      case agg@AggSum(ks,e) => 
        if(ks.size == 0) { //sure it's a K3Var
          val acc = newVariable(ex.tp)
          val (innerBlock, _) = expr(e, ctx, (v: Rep[_], ctxInner: LMSContext) => (impl.var_plusequals(acc, v), ctxInner))
          co(acc, ctx)
        } else { // otherwise it's a K3Map
          val acc = impl.k3temp(agg.tks,ex.tp)

          val (innerBlock, _) = expr(e, ctx, (v: Rep[_], ctxInner: LMSContext) => (impl.k3add(acc, ks.map( (ctx ++ ctxInner) ), v), ctxInner))
          
          val keyArg = freshRef(agg.tks)
          val valueArg = freshRef(ex.tp)
          val innerCtx = ctx ++ ks.zipWithIndex.map{ case (kPart,i) => (kPart,accessTuple(keyArg,agg.tks(i),ks.size,i)) }
          val (body, newCtx) = co(valueArg, innerCtx)

          (impl.k3foreach(acc, keyArg, valueArg , body), newCtx)
          
        }
      case _ => exprrrr = exprrrr + "ex = " + ex + "\n";(impl.fresh[Unit], ctx) //sys.error("Unimplemented")
    }

    def newVariable(tp: Type): impl.Var[Any] = tp match {
      case TypeLong => impl.var_new(impl.unit(0L))
      case TypeDouble => impl.var_new(impl.unit(0.0))
      case _ => sys.error("newVariable(tp) only allowed on numeric types")
    }

    def accessTuple(tuple: Rep[_],elemTp:Type,sz: Int, idx: Int)(implicit pos: scala.reflect.SourceContext): Rep[_] = sz match {
        case 1 => tuple
        case _ => impl.getClass.getDeclaredMethod("tuple%d_get%d".format(sz,idx+1),Class.forName("java.lang.Object"), Class.forName("scala.reflect.Manifest"), Class.forName("scala.reflect.SourceContext"))
                   .invoke(impl, tuple, man(elemTp), pos).asInstanceOf[Rep[_]]
    }

    // def createTuple(elems: List[Rep[_]]): Rep[_] = elems.size match {
    //   case 1 => impl.getClass.getDeclaredMethod("make_tuple1",impl.Exp[Any].getClass).invoke(impl,elems(0)).asInstanceOf[Rep[_]]
    //   case 2 => impl.getClass.getDeclaredMethod("make_tuple2",impl.Exp[Any].getClass).invoke(impl,elems(0),elems(1)).asInstanceOf[Rep[_]]
    //   case 3 => impl.getClass.getDeclaredMethod("make_tuple3",impl.Exp[Any].getClass).invoke(impl,elems(0),elems(1),elems(2)).asInstanceOf[Rep[_]]
    //   case _ => sys.error("createTupple(elems) only allowed on tuples of size <= 3")
    // }
    //def extractMapKeyParamType(mapName: String): 

    def getMapKeyTypes(name: String): List[Type] = maps(name).keys.map(_._2)

    def tup(ks: List[Rep[_]]): Rep[_] = ks.size match {
      case 1 => ks.head
      case 2 => impl.make_tuple2((ks(0),ks(1)))
      case 3 => impl.make_tuple3((ks(0),ks(1),ks(2)))
    }

    def muliply(tp: Type, vl: Rep[_], vr: Rep[_]) = tp match {
      case TypeLong => numeric_times[Long](vl,vr)
      case TypeDouble => numeric_times[Double](vl,vr)
      case _ => sys.error("Mul(l,r) only allowed on numeric types")
    }

    def addition(tp: Type, vl: Rep[_], vr: Rep[_]) = tp match {
      case TypeLong => numeric_plus[Long](vl,vr)
      case TypeDouble => numeric_plus[Double](vl,vr)
      case _ => sys.error("Add(l,r) only allowed on numeric types")
    }

    def comparison(tp: Type, vl: Rep[_], op: OpCmp, vr: Rep[_]) = tp match {
      case TypeLong => cmp[Long](vl,op,vr)
      case TypeDouble => cmp[Double](vl,op,vr)
      case _ => sys.error("Add(l,r) only allowed on numeric types")
    }    

    def numeric_times[T:Numeric:Manifest](l: Rep[_], r: Rep[_]) = impl.numeric_times[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
    def numeric_plus[T:Numeric:Manifest](l: Rep[_], r: Rep[_]) = impl.numeric_plus[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
    def cmp[T:Ordering:Manifest](l: Rep[_], op: OpCmp, r: Rep[_]): Rep[Boolean] = op match {
      case OpEq => impl.equals[T,T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
      case OpNe => impl.notequals[T,T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
      case OpGt => impl.ordering_gt[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
      case OpGe => impl.ordering_gteq[T](l.asInstanceOf[Rep[T]],r.asInstanceOf[Rep[T]])
    }

    val ctxTrigger: LMSContext=(
          maps.toList.map(_._2).map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) impl.fresh[K3Var[_]] else impl.fresh[K3Map[_,_]]) } union // XXX: we need here name-based k3maps
          args.map{ case (name,tp) => (name,freshRef(/*impl,*/ tp)) }).toMap // we need here name-based references of correct type

    var resultSyms: List[Rep[_]] = t.stmts.map {
      case StmtMap(m,e,op,oi) =>
        val co = (r:Rep[_],c:LMSContext) => (op match {
          case OpAdd => impl.k3add(ctxTrigger(m.name),m.keys.map(ctxTrigger++c),r)
          case OpSet => impl.k3set(ctxTrigger(m.name),m.keys.map(ctxTrigger++c),r)
        },c)
        expr(e,ctxTrigger,co)._1

        //val fop=op match { case OpAdd => "add" case OpSet => "set" }
        //val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
        //val init = (oi match {
        //  case Some(ie) => cpsExpr(ie,b,(i:String)=>"if ("+m.name+".get("+(if (m.keys.size==0) "" else tup(m.keys))+")==0) "+m.name+".set("+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n"
        //  case None => ""
        //})
        //clear+init+cpsExpr(e,b,(v:String) => m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"

      case _ => sys.error("Unimplemented") // we leave room for other type of events
    }

    //maps.map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) name+"[] ++ " else name+"["+keys+"] ++ ") }+
    //"\n\nHiii\n\n%s\n\niiiH\n\n".format(outStream.toString) +
    "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+
    ddbt.Utils.ind(resultSyms.map{x => impl.emit(x)}.mkString("//----\n"))+"\n}"
  }

  def freshRef(tp: Type): impl.Sym[_] = freshRefManifest(man(tp))
  def freshRef(tp: List[Type]): impl.Sym[_] = freshRefManifest(man(tp))
  def freshRefManifest[T:Manifest](mf: Manifest[T]): impl.Sym[T] = impl.fresh[T]

  var maps = Map[String,MapDef]() // global maps, to be replaced by a Map[String,LMS_K3Map]
  override def genSystem(s0:System):String = {
    maps=s0.maps.map(m=>(m.name,m)).toMap; val r=super.genSystem(s0); maps=Map(); r
  }
}
