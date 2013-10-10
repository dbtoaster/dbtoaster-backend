package ddbt.codegen
import ddbt.codegen.lms._
import ddbt.ast._
import ddbt.lib._

/**
 * This code generator is similar to ScalaGen but targets LMS graph (IR) to
 * optimize further before actually emitting Scala code for the trigger bodies.
 *
 * @author Mohammad Dashti, TCK
 */

class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  import ManifestHelper.man

  val impl = ScalaExpGen
  import impl.Rep

  var cx : Ctx[Rep[_]] = null

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
    }
    case Mul(l,r) => expr(l,(vl:Rep[_])=> expr(r,(vr:Rep[_]) => co(mul(vl,vr,ex.tp)) ))
    case a@Add(l,r) =>
      if (a.agg==Nil) { val cur=cx.save; expr(l,(vl:Rep[_])=>{ cx.load(cur); expr(r,(vr:Rep[_])=>{ cx.load(cur); co(add(vl,vr,ex.tp)) },am)},am) }
      else am match {
        case Some(t) if t==a.agg => val cur=cx.save; expr(l,co,am); cx.load(cur); expr(r,co,am); cx.load(cur);
        case _ =>
          val acc = impl.k3temp(a.agg.map(_._2),ex.tp)
          val inCo = (v:Rep[_]) => impl.k3add(acc,a.agg.map(x=>cx(x._1)),v)
          val cur = cx.save
          expr(l,inCo,Some(a.agg)); cx.load(cur)
          expr(r,inCo,Some(a.agg)); cx.load(cur)
          foreach(acc,a.agg,a.tp,co)
      }
    case Cmp(l,r,op) => expr(l,(vl:Rep[_]) => expr(r,(vr:Rep[_]) => co(cmp(vl,op,vr,ex.tp)) )) // formally, we should take the derived type from left and right, but this makes no difference to LMS
    case Exists(e) => expr(e,(ve:Rep[_]) => co(impl.__ifThenElse(impl.notequals(ve,impl.unit(0L)),impl.unit(1L),impl.unit(0L))))
    case Lift(n,e) => expr(e,(ve:Rep[_]) => if (cx.contains(n)) co(cmp(cx(n),OpEq,ve,e.tp)) else { cx.add(Map((n,ve))); co(impl.unit(1L)) })
    case a@Apply(fn,tp,as) =>
      def app(es:List[Expr],vs:List[Rep[_]]):Rep[Unit] = es match {
        case x :: xs => expr(x,(v:Rep[_]) => app(xs,v::vs))
        case Nil => co(impl.k3apply(fn,vs.reverse,tp))
      }
      if (as.forall(_.isInstanceOf[Const])) co(impl.named(constApply(a),tp,false)) // hoist constants resulting from function application
      else app(as,Nil)
    case m@MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>cx.contains(k)}
      if(ki.size == 0) { // all keys are bound
        co(impl.k3get(cx(n),ko.map{case (k,i)=>cx(k)},tp))
      } else { // we need to iterate over all keys not bound (ki)
        val mapRef = cx(n)
        val slicedMapRef = if(ko.size == 0) mapRef
        else impl.k3slice(mapRef,slice(n,ko.map(_._2)),ko.map{case (k,i)=>cx(k)})
        foreach(slicedMapRef,(ks zip m.tks),tp,co,"m")
      }
    case a@AggSum(ks,e) =>
      val agg_keys = (ks zip a.tks).filter{ case (n,t)=> !cx.contains(n) } // the aggregation is only made on free variables
      val acc = if (agg_keys.size==0) impl.k3var(ex.tp) else impl.k3temp(agg_keys.map(_._2),ex.tp)
      // Accumulate expr(e) in the acc
      val cur = cx.save
      val coAcc = (v:Rep[_]) => impl.k3add(acc, agg_keys.map(x=>cx(x._1)), v)
      expr(e,coAcc,Some(agg_keys)) // returns (Rep[Unit],ctx) and we ignore ctx
      cx.load(cur)
      // Iterate over acc and call original continuation
      if (agg_keys.size==0) co(impl.k3get(acc,Nil,ex.tp)) // accumulator is a single result
      else am match {
        case Some(t) if (t==agg_keys) => expr(e,co,am)
        case _ => foreach(acc,agg_keys,a.tp,co,"a")
      }
    case _ => sys.error("Unimplemented: "+ex)
  }

  def foreach(map:Rep[_],keys:List[(String,Type)],value_tp:Type,co:Rep[_]=>Rep[Unit],prefix:String=""):Rep[Unit] = {
    var keyArg: Rep[_] = null
    var valArg: Rep[_] = null
    val body = impl.reifyEffects {
      keyArg = impl.named(fresh(prefix+"k"),true)(man(keys.map(_._2)))
      valArg = impl.named(fresh(prefix+"v"),value_tp,true)
      val inKeys = keys.zipWithIndex.filter(k=> !cx.contains(k._1._1)).map{ case ((n,t),i) => (n,accessTuple(keyArg,t,keys.size,i)) }
      cx.add(inKeys.toMap); co(valArg)
    }
    impl.k3foreach(map, keyArg, valArg, body)
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
      case TypeString => cmp2[String](l,r)
      case TypeDate => cmp2[Long](impl.dtGetTime(l.asInstanceOf[Rep[java.util.Date]]),impl.dtGetTime(r.asInstanceOf[Rep[java.util.Date]]))
    },impl.unit(1L),impl.unit(0L))
  }

  // Trigger code generation
  override def genTrigger(t:Trigger):String = {
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    val triggerBlock = impl.reifyEffects {
      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        maps.map{ case (name,MapDef(_,_,keys,_)) => if (keys.size==0) (name,impl.namedK3Var(name)(manifest[Any])) else (name,impl.namedK3Map(name)(manifest[Any],manifest[Any])) }.toList union
        args.map{ case (name,tp) => (name,impl.named(name,tp)) }
      ).toMap)
      // Execute each statement
      t.stmts.map {
        case StmtMap(m,e,op,oi) => cx.load()
          val mm = cx(m.name)
          if (op==OpSet && m.keys.size>0) impl.k3clear(mm)
          oi match { case None => case Some(ie) => 
            expr(ie,(r:Rep[_]) => { val keys = m.keys.map(cx)
               impl.__ifThenElse(impl.equals(impl.k3get(mm,keys,m.tp),impl.unit(0L)),impl.k3set(mm,keys,r),impl.unit(()))
            })
          }
          cx.load()
          expr(e,(r:Rep[_]) => op match {
            case OpAdd => impl.k3add(mm,m.keys.map(cx),r)
            case OpSet => impl.k3set(mm,m.keys.map(cx),r)
          })
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      impl.unit(())
    }
    val res = "def on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ddbt.Utils.ind(impl.emit(triggerBlock))+"\n}"
    cx = null; res
  }

  override def genMap(m:MapDef):String = {
    if (m.keys.size==0) K3MapCommons.createK3VarDefinition(m.name, m.tp)+";"
    else {
      val keys = m.keys.map(_._2)
      val s = sx.getOrElse(m.name,List[List[Int]]())
      K3MapCommons.createK3MapDefinition(m.name,m.tp,keys,s)
    }
  }

  override def printK3VarGetMethod = ""

  // Expose the maps of the system being generated
  var maps = Map[String,MapDef]() // declared global maps
  override def apply(s0:System):String = {
    maps=s0.maps.map(m=>(m.name,m)).toMap; val r=super.apply(s0); maps=Map(); r
  }
}
