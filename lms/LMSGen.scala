package ddbt.codegen

import ddbt.ast._
import ddbt.lib._
import toasterbooster._
import scala.virtualization.lms.internal._
import scala.virtualization.lms.common._

class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._


  //type Rep[+A] = A // to be replaced

  //type Ctx = Map[String,Rep[_]]
  //protected val ctx0 = Map[String,Rep[_]]()

  /*
  def mul[T](l:Rep[T],r:Rep[T]):Rep[T] = __mul(l,r)
  def add[T](l:Rep[T],r:Rep[T]):Rep[T] = __add(l,r)
  def cmp[T](l:Rep[T],r:Rep[T]):Rep[T]
  def ex[T](e:Rep[T]):Rep[T]
  def lift[T](n:String,e:Rep[T]):(Rep[T],Ctx)

  def expr(ex:Expr,ctx:Ctx=ctx0):(Rep[_],Ctx) = ex match {
    case Mul(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,cl); (mul(sl,sr),cr)
    case Add(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,ctx); (add(sl,sr),cl++cr)
    case Cmp(l,r,op) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,ctx); (cmp(sl,sr),cl++cr)
    case Exists(e) => val (se,ce)=expr(e,ctx); (ex(se),ce)
    case Lift(n,e) => val (se,ce)=expr(e,ctx); val (sl,cl)=lift(n,se); (sl,cl++ce)
    case AggSum(ks,e) => ks.toSet
    case Apply(fn,tp,as) => as.flatMap(a=>a.collect(f)).toSet
    case MapRef(n,tp,ks) => ks.toSet
    case _ => (xx,ctx0)
  }
  */

  override def genTrigger(t:Trigger):String = {
    val outStream = new java.io.StringWriter
    val impl = new Impl(new java.io.PrintWriter(outStream), "org.dbtoaster", false) with DSL
    
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    type LMSContext = Map[String, impl.Rep[_]]

    val ctx0: LMSContext=(
             maps.map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) impl.fresh[K3Var[_]] else impl.fresh[K3Map[_,_]]) }
             union
             args.map{ case (name,tp) => (name,freshRef(impl, tp)) }
            ).toMap

    var exprrrr = ""
    def expr(ex:Expr,ctx:LMSContext):(impl.Rep[_],LMSContext) = ex match {
      case Mul(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,cl); (l.tp, r.tp) match {
        case (TypeLong  , TypeLong  ) => (numeric_times(manifest[Long],sl,sr),cr)
        case (TypeDouble, TypeLong  ) => (numeric_times(manifest[Double],sl,sr),cr)
        case (TypeLong  , TypeDouble) => (numeric_times(manifest[Double],sl,sr),cr)
        case (TypeDouble, TypeDouble) => (numeric_times(manifest[Double],sl,sr),cr)
        case _ => sys.error("Mul(l,r) only allowed on numeric types")
      }
      case Add(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,cl); (l.tp, r.tp) match {
        case (TypeLong  , TypeLong  ) => (numeric_plus(manifest[Long],sl,sr),cl++cr)
        case (TypeDouble, TypeLong  ) => (numeric_plus(manifest[Double],sl,sr),cl++cr)
        case (TypeLong  , TypeDouble) => (numeric_plus(manifest[Double],sl,sr),cl++cr)
        case (TypeDouble, TypeDouble) => (numeric_plus(manifest[Double],sl,sr),cl++cr)
        case _ => sys.error("Add(l,r) only allowed on numeric types")
      }
      case Cmp(l,r,op) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,cl); (l.tp, r.tp) match {
        case (TypeLong  , TypeLong  ) => (cmp(manifest[Long],sl,op,sr),cl++cr)
        case (TypeDouble, TypeLong  ) => (cmp(manifest[Double],sl,op,sr),cl++cr)
        case (TypeLong  , TypeDouble) => (cmp(manifest[Double],sl,op,sr),cl++cr)
        case (TypeDouble, TypeDouble) => (cmp(manifest[Double],sl,op,sr),cl++cr)
        case _ => sys.error("Cmp(l,r,op) is not possible for types (%s, %s)".format(l.tp, r.tp))
      }
      //(cmp(typeManifest(l.tp, r.tp),sl,op,sr),cl++cr)
      case Exists(e) => val (se,ce)=expr(e,ctx); (impl.__ifThenElse(impl.notequals(se,impl.unit(0)),impl.unit(1),impl.unit(0)),ce)
      //case Lift(n,e) => val (se,ce)=expr(e,ctx); val (sl,cl)=lift(n,se); (sl,cl++ce) //(sl, ctx + (n -> sl))
      //case AggSum(ks,e) => ks.toSet
      //case Apply(fn,tp,as) => as.flatMap(a=>a.collect(f)).toSet
      //case MapRef(n,tp,ks) => ks.toSet
      case _ => exprrrr = exprrrr + "ex = " + ex + "\n";(impl.fresh[Any], ctx) //sys.error("Unimplemented")
    }

    def numeric_times[T:Numeric:Manifest](mf: Manifest[T], l: impl.Rep[_], r: impl.Rep[_]) = impl.numeric_times[T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])

    def numeric_plus[T:Numeric:Manifest](mf: Manifest[T], l: impl.Rep[_], r: impl.Rep[_]) = impl.numeric_plus[T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])

    def cmp[T:Ordering:Manifest](mf: Manifest[T], l: impl.Rep[_], op: OpCmp, r: impl.Rep[_]): impl.Rep[Boolean] = op match {
      case OpEq => impl.equals[T,T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])
      case OpNe => impl.notequals[T,T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])
      case OpGt => impl.ordering_gt[T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])
      case OpGe => impl.ordering_gteq[T](l.asInstanceOf[impl.Rep[T]],r.asInstanceOf[impl.Rep[T]])
    }

    /*def lift[T](name: String, e: impl.Rep[T], ctx: LMSContext) = {
      if(ctx.contains(name)) {

      } else {

      }
    }*/

    t.stmts.foreach { s =>  s match {
        case StmtMap(m,e,op,oi) => 
          //val fop=op match { case OpAdd => "add" case OpSet => "set" }
          //val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
          //val init = (oi match {
          //  case Some(ie) => cpsExpr(ie,b,(i:String)=>"if ("+m.name+".get("+(if (m.keys.size==0) "" else tup(m.keys))+")==0) "+m.name+".set("+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n"
          //  case None => ""
          //})
          //clear+init+cpsExpr(e,b,(v:String) => m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
          expr(e, ctx0)
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
    }

    impl.emitAll

    //maps.map{ case MapDef(name,_,keys,_) => (name, if (keys.size==0) name+"[] ++ " else name+"["+keys+"] ++ ") }+
    "\n\nHiii\n\n%s\n\niiiH\n\n".format(outStream.toString) +
    "def on"+n+"("+as.map{a=>a._1+":"+tpe(a._2)} .mkString(", ")+") {\n"+
    "  hello2"+ //ind(t.stmts.map{s=>genStmt(s,b)}.mkString)
    "\n}"
  }

  def freshRef(impl: Impl,tp: Type): impl.Sym[_] = freshRefManifest(typeManifest(tp), impl)

  def freshRefManifest[T:Manifest](mf: Manifest[T], impl: Impl): impl.Sym[T] = impl.fresh[T]

  def typeManifest(tp:Type):Manifest[_] = tp match {
    case TypeLong => manifest[Long]
    case TypeDouble => manifest[Double]
    case _ => sys.error("No manifest for "+tp)
  }

  def typeManifest(tp:Type, orTp:Type):Manifest[_] = tp match {
    case TypeLong => typeManifest(orTp)
    case _ => typeManifest(tp)
  }
  
  def tupleManifest(ts:List[Type]) = {
    val ms:List[Manifest[_]] = ts map typeManifest
    val cls:java.lang.Class[_] = Class.forName("scala.Tuple"+ts.size)
    scala.reflect.ManifestFactory.classType(cls,ms.head,ms.tail:_*)
  }

  var maps = List[MapDef]() // global maps, to be replaced by a Map[String,LMS_K3Map]
  override def genSystem(s0:System):String = {
    maps=s0.maps; val r=super.genSystem(s0); maps=Nil; r
  }
}
