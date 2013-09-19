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
      //case Apply(fn,tp,as) =>

      //case Apply(fn,tp,as) =>
      //  val (vs,cn:LMSContext) = ((List[Rep[_]](),ctx0) /: as) { case ((vs,c1),e) => val (v,c2) = expr(e,ctx); (vs:::v::Nil,c1++c2) }
      //  ( /* Apply(fn,vs) */ impl.unit(-10),cn) // XXX: call appropriate LMS node

      case MapRef(n,tp,ks) => 
        if(ks.size == 0) { //sure it's a K3Var
          co(k3get(ctx(n),Nil,tp), ctx0)
        } else { // otherwise it's a K3Map
          val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
          if (ki.size==0) co(k3get(ctx(n),ko.map{case (k,i)=>ctx(k)},tp), ctx0) // all keys are bound
          else { 
            val mapRef = ctx(n)
            val slicedMapRef = if(ko.size > 0) {
              k3slice(mapRef,slice(n,ko.map{case (k,i)=>i}),ko.map{case (k,i)=>ctx(k)}))
            } else {
              mapRef
            }
            val keyArg = freshRef(getMapKeyTypes(n))
            val valueArg = freshRef(tp)
            val innerCtx = ctx ++ ks.zipWithIndex.filter( (k,v) => !ctx.contains(k) ).map( (kPart,i) => (kPart,accessTuple(keyArg,ks.size,i)) )
            val (body, newCtx) = co(valueArg, innerCtx)

            k3foreach(slicedMapRef, keyArg, valueArg , body)
          }
        }
      //case AggSum(ks,e) => ks.toSet
      //case MapRef(n,tp,ks) => ks.toSet
      case _ => exprrrr = exprrrr + "ex = " + ex + "\n";(impl.fresh[Unit], ctx) //sys.error("Unimplemented")
    }

    def accessTuple(tuple: Rep[_],sz: Int, idx: Int): Rep[_] = {

    }
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
          maps.map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) impl.fresh[K3Var[_]] else impl.fresh[K3Map[_,_]]) } union // XXX: we need here name-based k3maps
          args.map{ case (name,tp) => (name,freshRef(/*impl,*/ tp)) }).toMap // we need here name-based references of correct type

    t.stmts.foreach { s =>  s match {
        case StmtMap(m,e,op,oi) => 
          //val fop=op match { case OpAdd => "add" case OpSet => "set" }
          //val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
          //val init = (oi match {
          //  case Some(ie) => cpsExpr(ie,b,(i:String)=>"if ("+m.name+".get("+(if (m.keys.size==0) "" else tup(m.keys))+")==0) "+m.name+".set("+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n"
          //  case None => ""
          //})
          //clear+init+cpsExpr(e,b,(v:String) => m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
          expr(e, ctxTrigger, (r:Rep[_],c:LMSContext) => (impl.unit(()), c))
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
    }

    //maps.map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) name+"[] ++ " else name+"["+keys+"] ++ ") }+
    //"\n\nHiii\n\n%s\n\niiiH\n\n".format(outStream.toString) +
    "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+
    "  "+impl.emit(impl.unit(1.0))+
    "  hello2"+ //ind(t.stmts.map{s=>genStmt(s,b)}.mkString)
    "\n}"
  }

  def freshRef(tp: Type): impl.Sym[_] = freshRefManifest(man(tp))

  def freshRef(tp: List[Type]): impl.Sym[_] = freshRefManifest(man(tp))

  def freshRefManifest[T:Manifest](mf: Manifest[T]): impl.Sym[T] = impl.fresh[T]

/*
  def typeManifest(tp:Type, orTp:Type):Manifest[_] = tp match {
    case TypeLong => typeManifest(orTp)
    case _ => typeManifest(tp)
  }
  
  def tupleManifest(ts:List[Type]) = {
    val ms:List[Manifest[_]] = ts map typeManifest
    val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
    scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*)
  }
*/

  var maps = List[MapDef]() // global maps, to be replaced by a Map[String,LMS_K3Map]
  override def genSystem(s0:System):String = {
    maps=s0.maps; val r=super.genSystem(s0); maps=Nil; r
  }
}
