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
  import ManifestHelper.{man,zero,manEntry}

  val impl = ScalaExpGen
  import impl.Rep

  var cx : Ctx[Rep[_]] = null

  import ddbt.lib.store._
  def me(ks:List[Type],v:Type=null):Manifest[Entry] = manEntry(if (v==null) ks else ks:::List(v)).asInstanceOf[Manifest[Entry]]
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
    case Mul(l,r) => expr(l,(vl:Rep[_])=> expr(r,(vr:Rep[_]) => co(mul(vl,vr,ex.tp)),am),am)
    case a@Add(l,r) =>
      if (a.agg==Nil) { val cur=cx.save; expr(l,(vl:Rep[_])=>{ cx.load(cur); expr(r,(vr:Rep[_])=>{ cx.load(cur); co(add(vl,vr,ex.tp)) },am)},am) }
      else am match {
        case Some(t) if t.toSet==a.agg.toSet => val cur=cx.save; expr(l,co,am); cx.load(cur); expr(r,co,am); cx.load(cur);
        case _ =>
          implicit val mE=me(a.agg.map(_._2),a.tp)
          val acc = impl.m3temp()(mE)
          val inCo = (v:Rep[_]) => impl.m3add(acc,acc.newEntry( (a.agg.map(x=>cx(x._1))++List(v)) : _*))(mE)
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
        case Nil => co(impl.m3apply(fn,vs.reverse,tp))
      }
      //if (as.forall(_.isInstanceOf[Const])) co(impl.named(constApply(a),tp,false)) // hoist constants resulting from function application
      //else
       app(as,Nil)
    case m@MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>cx.contains(k)}
      val proxy = mapProxy(cx(n))
      if(ks.size == 0) { // variable
        co(cx(n))
      } else if(ki.size == 0) { // all keys are bound
        val z = impl.unit(zero(tp))
        val vs = ks.zipWithIndex.map{ case (n,i) => (i+1,cx(n))}
        println("vs11 = " + vs)
        val r = proxy.get(vs : _*)
        impl.__ifThenElse(impl.__equal(r,impl.unit(null)),co(z),co(r.get(ks.size+1)))
      } else { // we need to iterate over all keys not bound (ki)
        if (ko.size==0) proxy.foreach(co)
        else {
          implicit val mE=me(m.tks,tp)
          val mm = cx(n).asInstanceOf[Rep[Store[Entry]]]
          mm.slice({
            (e:Rep[Entry])=> cx.add(ki.map{ case (k,i) => (k,e.get(i)) }.toMap); co(e.get(ks.size+1))
          },ko.map{ case (k,i) => (i+1,cx(k)) } : _*)
        }
      }
    case a@AggSum(ks,e) =>
      val agg_keys = (ks zip a.tks).filter{ case (n,t)=> !cx.contains(n) } // the aggregation is only made on free variables
      if (agg_keys.size==0) { // Accumulate expr(e) in the acc, returns (Rep[Unit],ctx) and we ignore ctx
        val acc:impl.Var[_] = ex.tp match {
          case TypeLong => impl.var_new[Long](impl.unit(0L))
          case TypeDouble => impl.var_new[Double](impl.unit(0.0))
          case TypeString => impl.var_new[String](impl.unit(""))
          case TypeDate => impl.var_new[java.util.Date](impl.unit(new java.util.Date()))
          case _ => sys.error("Unsupported type "+ex.tp)
        }
        val cur=cx.save; expr(e,(v:Rep[_]) => impl.var_plusequals(acc, v),None); cx.load(cur); co(acc)
      } else {
        implicit val mE=me(a.tks,ex.tp)
        val acc = impl.m3temp()(mE)
        val cur = cx.save

        val coAcc = (v:Rep[_]) => {
          val vs:List[Rep[_]] = agg_keys.map(x=>cx(x._1)).toList ::: List(v)
          impl.m3add(acc, acc.newEntry(vs : _*))
        }
        expr(e,coAcc,Some(agg_keys)); cx.load(cur) // returns (Rep[Unit],ctx) and we ignore ctx
        am match {
          case Some(t) if (t.toSet==agg_keys.toSet) => expr(e,co,am)
          case _ => foreach(acc,agg_keys,a.tp,co,"a")
        }
      }
    case _ => sys.error("Unimplemented: "+ex)
  }

  def foreach(map:Rep[_],keys:List[(String,Type)],value_tp:Type,co:Rep[_]=>Rep[Unit],prefix:String=""):Rep[Unit] = {
    implicit val mE = manEntry(keys.map(_._2) ::: List(value_tp))
    val proxy = mapProxy(map)
    proxy.foreach{ e:Rep[Entry] =>
      cx.add(keys.zipWithIndex.filter(x=> !cx.contains(x._1._1)).map { case ((n,t),i) => (n,e.get(i)) }.toMap)
      co(e.get(keys.size+1))
    }
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
      case _ => sys.error("Unsupported type")
    },impl.unit(1L),impl.unit(0L))
  }

  // Trigger code generation
  def genTriggerLMS(t:Trigger) = {
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    val block = impl.reifyEffects {
      // Trigger context: global maps + trigger arguments
      val ctx0Mutable = ctx0.map{ case (name,(sym,keys,tp)) => if (keys.size==0) { tp match {
        case TypeLong => (name, impl.allMutable[Long](sym.asInstanceOf[Rep[Long]]))
        case TypeDouble => (name, impl.allMutable[Double](sym.asInstanceOf[Rep[Double]]))
        case TypeString => (name, impl.allMutable[String](sym.asInstanceOf[Rep[String]]))
        case TypeDate => (name, impl.allMutable[java.util.Date](sym.asInstanceOf[Rep[java.util.Date]]))
        case _ => sys.error("No manifest for "+tp)
      } } else { val m = me(keys.map(_._2),tp); (name,impl.stMutable(sym.asInstanceOf[Rep[Store[Entry]]])(m)) } }
      cx = Ctx((
        // maps.map{ case (name,MapDef(_,tp,keys,_)) => if (keys.size==0) (name,impl.fresh(man(tp))) else { val m = me(keys.map(_._2),tp); (name,impl.newStore()(m)) } // XXX missing indexes
        //  impl.namedM3Map(name,keys.map(_._2),tp,sx.getOrElse(name,List[List[Int]]()))(manifest[Any],manifest[Any]))
        //}
        ctx0Mutable.toList union
        args.map{ case (name,tp) => (name,impl.named(name,tp)) }
      ).toMap)
      // Execute each statement
      t.stmts.map {
        case StmtMap(m,e,op,oi) => cx.load()
          if (m.keys.size==0) {
            val mm = cx(m.name).asInstanceOf[impl.Var[_]]
            expr(e,(r:Rep[_]) => op match { case OpAdd => impl.var_plusequals(mm,r) case OpSet => impl.__assign(mm,r) })
          } else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.tks ++ List(m.tp)).asInstanceOf[Manifest[Entry]]
            if (op==OpSet) impl.stClear(mm)
            oi match { case None => case Some(ie) =>
              expr(ie,(r:Rep[_]) => {
                val ent = mm.newEntry((m.keys.map(cx) ++ List(r)) : _*)
                println("vs22 = " + m.keys.zipWithIndex)
                impl.__ifThenElse(impl.equals(mapProxy(mm).get(m.keys.zipWithIndex.map{ case (n,i) => (i+1,cx(n))} : _*),impl.unit(null)),impl.m3set(mm,ent),impl.unit(()))
              })
            }
            cx.load()
            expr(e,(r:Rep[_]) => {
              val ent = mm.newEntry((m.keys.map(cx) ++ List(r)) : _*)
              op match { case OpAdd => impl.m3add(mm, ent)(mE) case OpSet => impl.m3set(mm, ent)(mE) }
            }, if (op==OpAdd) Some(m.keys zip m.tks) else None)
          }
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      impl.unit(())
    }
    cx = null; ("on"+name+"("+args.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+")",block)
  }

  override def toMapFunction(q: Query) = {
    if(M3MapCommons.isInliningHigherThanNone) {
      //m = map
      val map = q.name
      val nodeName = map+"_node"
      val m = maps(q.name)
      val mapKeys = m.keys.map(_._2)
      val mapValue = m.tp
      val indexList = sx.getOrElse(map,List[List[Int]]())

      //val entryCls = M3MapCommons.entryClassName(q.tp, q.keys, sx.getOrElse(q.name,List[List[Int]]()))
      val entryCls = "("+tup(mapKeys.map(_.toScala))+","+q.map.tp.toScala+")"
      val res = nodeName+"_mres"
      val i = nodeName+"_mi"
      val len = nodeName+"_mlen"
      val e = nodeName+"_me"
      "{\n" +
      "  //TOMAP\n" +
      "  var "+res+":scala.collection.mutable.ArrayBuffer["+entryCls+"] = new scala.collection.mutable.ArrayBuffer["+entryCls+"]("+M3MapCommons.genMapSize(map)+");\n" +
      "  var "+i+":Int = 0\n" +
      "  val "+len+":Int = "+map+".length\n" +
      "  while("+i+" < "+len+") {\n" +
      "    var "+e+":"+M3MapCommons.entryClassName(mapValue,mapKeys,indexList)+" = "+map+"("+i+")\n" +
      "    while("+e+" != null) {\n"+
      "      "+res+" += ("+tup(mapKeys.zipWithIndex.map{ case (_,i) => e+"._"+(i+1) })+" -> "+e+".v)\n"+
      "      "+e+" = "+e+".next\n" +
      "    }\n" +
      "    "+i+" += 1\n" +
      "  }\n" +
      "  " + res + "\n" +
      "}.toMap"
    } else {
      super.toMapFunction(q)
    }
  }

  override def genMap(m:MapDef):String = {
    if(M3MapCommons.isInliningHigherThanNone) {
      if (m.keys.size==0) M3MapCommons.createM3VarDefinition(m.name, m.tp)+";"
      else {
        val keys = m.keys.map(_._2)
        val indexList = sx.getOrElse(m.name,List[List[Int]]())
        M3MapCommons.createM3NamedMapDefinition(m.name,m.tp,keys,indexList)
      }
    } else {
      super.genMap(m)
    }
  }

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = {
    if(M3MapCommons.isInliningHigherThanNone) {
      //val theMap = maps(map)
      //val mapKeys = theMap.keys.map(_._2)
      val indexList = sx.getOrElse(map,List[List[Int]]())
      M3MapCommons.genGenericAddNamedMap(true,false,"","",map+"_node",map,keyNames.map(_._2),TypeLong,indexList,keyNames.map(_._1),"1")
    } else {
      super.genInitializationFor(map, keyNames, keyNamesConcat)
    }
  }

  // Expose the maps of the system being generated
  var maps = Map[String,MapDef]() // declared global maps
  var ctx0 = Map[String,(Rep[_], List[(String,Type)], Type)]()
  override def genLMS(s0:System):String = {
    maps=s0.maps.map(m=>(m.name,m)).toMap
    ctx0 = maps.map{ case (name,MapDef(_,tp,keys,_)) => if (keys.size==0) { val m = man(tp); (name,(impl.fresh(m),keys,tp)) } else { val m = me(keys.map(_._2),tp); val s=impl.named(name,true)(m); impl.collectStore(s)(m); (name,(/*impl.newSStore()(m)*/s,keys,tp)) } } // XXX missing indexes

    //TODO: this should be replaced by a specific traversal for completing the slice information
    // s0.triggers.map(super.genTrigger)
    val tsResBlks = s0.triggers.map(genTriggerLMS) // triggers (need to be generated before maps)
    val ts = tsResBlks.map{ case (s,b) =>
      "def "+s+" {\n"+ddbt.Utils.ind(impl.emit(b))+"\n}"
    }.mkString("\n\n")
    var outStream = new java.io.StringWriter
    var outWriter = new java.io.PrintWriter(outStream)
    //val ms = s0.maps.map(genMap).mkString("\n") // maps
    impl.codegen.generateClassArgsDefs(outWriter,Nil)
    val ms = outStream.toString

    outStream = new java.io.StringWriter
    outWriter = new java.io.PrintWriter(outStream)
    //val ds = if(M3MapCommons.isInliningHigherThanNone) M3MapCommons.generateAllEntryClasses else ""
    impl.codegen.emitDataStructures(outWriter)
    val ds = outStream.toString
    val r=ms+"\n"+ts+"\n"+ds
    maps=Map()
    M3MapCommons.clear
    r
  }
}
