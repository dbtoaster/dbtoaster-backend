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

abstract class LMSGen(override val cls:String="Query", val impl: LMSExpGen) extends IScalaGen {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  import ManifestHelper.{man,zero,manEntry,manStore}
  import impl.Rep
  implicit val overloaded1 = impl.overloaded1
  import ddbt.lib.store._

  var cx : Ctx[Rep[_]] = null

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
    case Exists(e) => expr(e,(ve:Rep[_]) => co(impl.__ifThenElse(impl.notequals(ve,impl.unit(0L)),impl.unit(1L),impl.unit(0L))))
    case Cmp(l,r,op) => expr(l,(vl:Rep[_]) => expr(r,(vr:Rep[_]) => co(cmp(vl,op,vr,ex.tp)) )) // formally, we should take the derived type from left and right, but this makes no difference to LMS
    case a@Apply(fn,tp,as) =>
      def app(es:List[Expr],vs:List[Rep[_]]):Rep[Unit] = es match {
        case x :: xs => expr(x,(v:Rep[_]) => app(xs,v::vs))
        case Nil => co(impl.m3apply(fn,vs.reverse,tp))
      }
      if (as.forall(_.isInstanceOf[Const])) co(impl.named(constApply(a),tp,false)) // hoist constants resulting from function application
      else app(as,Nil)
    case m@MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>cx.contains(k)}
      val proxy = mapProxy(cx(n))
      if(ks.size == 0) { // variable
        co(cx(n))
      } else if(ki.size == 0) { // all keys are bound
        val z = impl.unit(zero(tp))
        val vs = ks.zipWithIndex.map{ case (n,i) => (i+1,cx(n))}
        val r = proxy.get(vs : _*)
        co(impl.__ifThenElse(impl.__equal(r,impl.unit(null)),z,impl.steGet(r,ks.size+1)))
      } else { // we need to iterate over all keys not bound (ki)
        if (ko.size > 0) {
          implicit val mE=me(m.tks,tp)
          val mm = cx(n).asInstanceOf[Rep[Store[Entry]]]
          impl.stSlice(mm, {
            (e:Rep[Entry])=> cx.add(ki.map{ case (k,i) => (k,impl.steGet(e, i+1)) }.toMap); co(impl.steGet(e, ks.size+1))
          },ko.map{ case (k,i) => (i+1,cx(k)) } : _*)
        } else {
          proxy.foreach((e:Rep[Entry])=> {
            cx.add(ki.map{ case (k,i) => (k,impl.steGet(e, i+1)) }.toMap); co(impl.steGet(e, ks.size+1))
          })
        }
      }
    case Lift(n,e) =>
      if (cx.contains(n)) expr(e,(ve:Rep[_])=>co(impl.__ifThenElse(impl.equals(ve,cx(n)),impl.unit(1L),impl.unit(0L))  ),am)
      else e match {
        case Ref(n2) => cx.add(n,cx(n2)); co(impl.unit(1L))
        case _ => expr(e,(ve:Rep[_]) => { cx.add(n,ve); co(impl.unit(1L)) } )
      }
    case Mul(l,r) => expr(l,(vl:Rep[_])=> expr(r,(vr:Rep[_]) => co(mul(vl,vr,ex.tp)),am),am)
    case a@Add(l,r) =>
      if (a.agg==Nil) {
        val cur=cx.save
        expr(l,(vl:Rep[_])=>{
          cx.load(cur)
          expr(r,(vr:Rep[_])=>{
            cx.load(cur)
            co(add(vl,vr,ex.tp))
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
    case a@AggSum(ks,e) =>
      val agg_keys = (ks zip a.tks).filter{ case (n,t)=> !cx.contains(n) } // the aggregation is only made on free variables
      if (agg_keys.size==0) { // Accumulate expr(e) in the acc, returns (Rep[Unit],ctx) and we ignore ctx
        val cur=cx.save;
        val acc:impl.Var[_] = ex.tp match {
          case TypeLong =>
            val agg:impl.Var[Long] = impl.var_new[Long](impl.unit(0L))
            expr(e,
              (v:Rep[_]) => impl.var_assign[Long](agg.asInstanceOf[impl.Var[Long]], impl.numeric_plus[Long](impl.readVar[Long](agg.asInstanceOf[impl.Var[Long]]),v.asInstanceOf[Rep[Long]]))
            )
            agg
          case TypeDouble =>
            val agg:impl.Var[Double] = impl.var_new[Double](impl.unit(0.0))
            expr(e,
              (v:Rep[_]) => impl.var_assign[Double](agg.asInstanceOf[impl.Var[Double]], impl.numeric_plus[Double](impl.readVar[Double](agg.asInstanceOf[impl.Var[Double]]),v.asInstanceOf[Rep[Double]]))
            )
            agg
          case TypeString =>
            val agg:impl.Var[String] = impl.var_new[String](impl.unit(""))
            expr(e,
              (v:Rep[_]) => impl.var_assign[String](agg.asInstanceOf[impl.Var[String]], impl.string_plus(impl.readVar[String](agg.asInstanceOf[impl.Var[String]]),v.asInstanceOf[Rep[String]]))
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
      } else am match {
        case Some(t) if t.toSet.subsetOf(agg_keys.toSet) => expr(e,co,am)
        case _ =>

        val cur = cx.save

        implicit val mE=me(agg_keys.map(_._2),ex.tp)
        val acc = impl.m3temp()(mE)
        val coAcc = (v:Rep[_]) => {
          val vs:List[Rep[_]] = agg_keys.map(x=>cx(x._1)).toList ::: List(v)
          impl.m3add(acc, impl.stNewEntry2(acc, vs : _*))(mE)
        }
        expr(e,coAcc,Some(agg_keys)); cx.load(cur) // returns (Rep[Unit],ctx) and we ignore ctx
        foreach(acc,agg_keys,a.tp,co)
      }
    case _ => sys.error("Unimplemented: "+ex)
  }

  def foreach(map:Rep[_],keys:List[(String,Type)],value_tp:Type,co:Rep[_]=>Rep[Unit]):Rep[Unit] = {
    implicit val mE = manEntry(keys.map(_._2) ::: List(value_tp))
    val proxy = mapProxy(map)
    proxy.foreach{ e:Rep[Entry] =>
      cx.add(keys.zipWithIndex.filter(x=> !cx.contains(x._1._1)).map { case ((n,t),i) => (n,impl.steGet(e, i+1)) }.toMap)
      co(impl.steGet(e, keys.size+1))
    }
  }

  def accessTuple(tuple: Rep[_],elemTp:Type,sz: Int, idx: Int)(implicit pos: scala.reflect.SourceContext): Rep[_] = sz match {
      case 1 => tuple
      case _ => impl.getClass.getDeclaredMethod("tuple%d_get%d".format(sz,idx+1),Class.forName("java.lang.Object"), Class.forName("scala.reflect.Manifest"), Class.forName("scala.reflect.SourceContext"))
                 .invoke(impl, tuple, man(elemTp), pos).asInstanceOf[Rep[_]]
  }

  def mul(l:Rep[_], r:Rep[_], tp:Type) = {
    tp match {
      case TypeLong | TypeDouble => impl.m3apply("mul",List(l,r),tp)
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

  def filterStatement(s:Stmt) = true

  // Trigger code generation
  def genTriggerLMS(t:Trigger, s0:System) = {
    val (name,args) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtBatchUpdate(Schema(n,cs)) => ("BatchUpdate"+n,cs)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }

    var params = ""
    val block = impl.reifyEffects {
      params = t.evt match {
        case EvtBatchUpdate(Schema(n,_)) =>
          val rel = s0.sources.filter(_.schema.name == n)(0).schema
          val name = rel.deltaSchema
          
          name+":Store["+impl.codegen.storeEntryType(ctx0(name)._1)+"]"
        case _ =>
          args.map(a=>a._1+":"+a._2.toScala).mkString(", ")
      }
      // Trigger context: global maps + trigger arguments
      cx = Ctx((
        ctx0.map{ case (name,(sym,keys,tp)) => (name, sym) }.toList union
        {
          t.evt match {
            case EvtBatchUpdate(Schema(n,_)) =>
              // val rel = s0.sources.filter(_.schema.name == n)(0).schema
              // val ks = rel.fields.map(_._2)
              // val tp = TypeLong
              // val name = rel.deltaSchema

              // val m = me(ks,tp)
              // val sc=impl.named(name,true)(manStore(m))
              // impl.collectStore(sc)(m)

              // List(name -> sc)
              Nil
            case _ =>
              args.map{ case (name,tp) => (name,impl.named(name,tp)) }
          }
        }
      ).toMap)
      // Execute each statement
      t.stmts.filter(filterStatement).map {
        case StmtMap(m,e,op,oi) => cx.load()
          if (m.keys.size==0) {
            val mm = m.tp match {
              case TypeLong => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[Long]]])
              case TypeDouble => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[Double]]])
              case TypeString => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[String]]])
              //case TypeDate => impl.Variable(cx(m.name).asInstanceOf[Rep[impl.Variable[java.util.Date]]])
              case _ => sys.error("Unsupported type "+m.tp)
            }
            expr(e,(r:Rep[_]) => op match { case OpAdd => impl.var_plusequals(mm,r) case OpSet => impl.__assign(mm,r) })
          } else {
            val mm = cx(m.name).asInstanceOf[Rep[Store[Entry]]]
            implicit val mE = manEntry(m.tks ++ List(m.tp)).asInstanceOf[Manifest[Entry]]
            if (op==OpSet) impl.stClear(mm)
            oi match { case None => case Some(ie) =>
              expr(ie,(r:Rep[_]) => {
                val ent = impl.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)) : _*)
                impl.__ifThenElse(impl.equals(mapProxy(mm).get(m.keys.zipWithIndex.map{ case (n,i) => (i+1,cx(n))} : _*),impl.unit(null)),impl.m3set(mm,ent),impl.unit(()))
              })
            }
            cx.load()
            expr(e,(r:Rep[_]) => {
              val ent = impl.stNewEntry2(mm, (m.keys.map(cx) ++ List(r)) : _*)
              op match { case OpAdd | OpSet => impl.m3add(mm, ent)(mE) }
            }, /*if (op==OpAdd)*/ Some(m.keys zip m.tks) /*else None*/) // XXXX commented out the if expression
          }
        case m@MapDef(name,tp,keys,_) =>
          // val m = me(keys.map(_._2),tp)
          // val s=impl.named(name,true)(manStore(m))
          // impl.collectStore(s)(m)
          // cx = Ctx(cx.ctx0 + (name -> s))
        case _ => sys.error("Unimplemented") // we leave room for other type of events
      }
      impl.unit(())
    }
    cx = null; (name,params,block)
  }

  override def toMapFunction(q: Query) = {
    val map = q.name
    val m = maps(map)
    val mapKeys = m.keys.map(_._2)
    val nodeName = map+"_node"
    val res = nodeName+"_mres"
    "{ val "+res+" = new scala.collection.mutable.HashMap["+tup(mapKeys.map(_.toScala))+","+q.map.tp.toScala+"](); "+map+".foreach{e => "+res+" += ("+tup(mapKeys.zipWithIndex.map{ case (_,i) => "e._"+(i+1) })+" -> e._"+(mapKeys.size+1)+") }; "+res+".toMap }"
  }

  override def onEndStream = "printMapsInfo();"

  override def genMap(m:MapDef):String = {
    if (m.keys.size==0) createVarDefinition(m.name, m.tp)+";"
    else {
      impl.codegen.generateNewStore(ctx0(m.name)._1.asInstanceOf[impl.codegen.IR.Sym[_]], true)
    }
  }

  def genAllMaps(maps:Seq[MapDef]) = maps.map(genMap).mkString("\n")
  def createVarDefinition(name: String, tp:Type) = "var "+name+":"+tp.toScala+" = "+tp.zero

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = {
    val (a, keys, tp) = ctx0(map)
    val acc = a.asInstanceOf[Rep[Store[Entry]]]
    val mE = me(keys.map(_._2),tp)
    val block = impl.reifyEffects {
      impl.m3add(acc,impl.stNewEntry2(acc,  ((keyNames.map{ case (n,t) => impl.named(n,false)(mE) })++List(impl.unit(1))) : _*))(mE)
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
  var ctx0 = Map[String,(Rep[_], List[(String,Type)], Type)]()
  override def genLMS(s0:System):(String,String,String,String) = {
    val classLevelMaps = s0.triggers.filter(_.evt match {
      case EvtBatchUpdate(s) => true
      case _ => false
    }).map(_.evt match { //delta relations
      case EvtBatchUpdate(sc) =>
        val name = sc.name
        val schema = s0.sources.filter(x => x.schema.name == name)(0).schema
        val deltaRel = sc.deltaSchema
        val tp = TypeLong
        val keys = schema.fields
        MapDef(deltaRel,tp,keys,null)
      case _ => null
    }) ++
    s0.triggers.flatMap{ t=> //local maps
      t.stmts.filter{
        case MapDef(_,_,_,_) => true
        case _ => false
      }.map{
        case m@MapDef(_,_,_,_) => m
        case _ => null
      }
    } ++
    maps.map{
      case (_,m@MapDef(_,_,_,_)) => m
    } // XXX missing indexes
    ctx0 = classLevelMaps.map{
      case MapDef(name,tp,keys,_) => if (keys.size==0) {
        val m = man(tp)
        val s = impl.named(name,false)(m)
        s.emitted = true
        (name,(s,keys,tp))
      } else {
        val m = me(keys.map(_._2),tp)
        val s=impl.named(name,true)(manStore(m))
        impl.collectStore(s)(m)
        (name,(/*impl.newSStore()(m)*/s,keys,tp))
      }
    }.toMap // XXX missing indexes
    val (str,ld0,_) = genInternals(s0)
    //TODO: this should be replaced by a specific traversal for completing the slice information
    // s0.triggers.map(super.genTrigger)
    val tsResBlks = s0.triggers.map(genTriggerLMS(_,s0)) // triggers (need to be generated before maps)
    val ts = tsResBlks.map{ case (name,params,b) =>
      impl.emitTrigger(b,name,params)
    }.mkString("\n\n")
    val ms = genAllMaps(classLevelMaps) // maps
    var outStream = new java.io.StringWriter
    var outWriter = new java.io.PrintWriter(outStream)
    //impl.codegen.generateClassArgsDefs(outWriter,Nil)

    impl.codegen.emitDataStructures(outWriter)
    val ds = outStream.toString
    val printInfoDef = if(Store.GATHER_STATISTICS) {
      "def printMapsInfo() = {\n" + 
        maps.map{ case (m,MapDef(_,_,keys,_)) => if (keys.size>0) "  System.out.println(\""+m+" => \" + "+m+".getInfoStr)\n  Store.addTimersFromStore(\""+m+"\", "+m+".totalTimers, "+m+".timersPerIndex)\n" else "" }.mkString +
        impl.storeSyms.map{ map => if(map.attributes.get("_isTemp").asInstanceOf[Option[Boolean]].getOrElse(false)) { val m = impl.codegen.quote(map); "  Store.addTimersFromStore(\""+m+"\", "+m+".totalTimers, "+m+".timersPerIndex)\n" } else "" }.mkString +
        "  System.out.println(\"Timers Info => {\\n%s\\n%s}\".format(Store.printTimersInfo,Store.printTimersInfoCSV))\n"+
        "}"
    } else "def printMapsInfo() = {}"
    val r=ds+"\n"+ms+"\n"+ts+"\n"+printInfoDef
    (r,str,ld0,consts)
  }

  override def genBatchTupleRec(name:String, keys:List[(String,Type)], value:String) = "insert(new "+impl.codegen.storeEntryType(ctx0(name)._1)+"("+keys.zipWithIndex.map{ case ((_,tp),i) => "v"+i+","}.mkString+value+"))"

  override def clearOut = {
    maps=Map()
    impl.reset

  }

  override def additionalImports():String = "import ddbt.lib.store._\n"

  override def getEntryDefinitions:String = ""
}

class LMSScalaGen(cls:String="Query") extends LMSGen(cls,ScalaExpGen) 

class LMSCppGen(cls:String="Query") extends LMSGen(cls,CppExpGen) with ICppGen {
  import ddbt.ast.M3._

  override def toMapFunction(q: Query) = super[LMSGen].toMapFunction(q)
  override def onEndStream = super[LMSGen].onEndStream
  override def genMap(m:MapDef):String = super[LMSGen].genMap(m)
  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = super[LMSGen].genInitializationFor(map, keyNames, keyNamesConcat)
  override def genLMS(s0:System):(String,String,String,String) = super[LMSGen].genLMS(s0)
  override def clearOut = super[LMSGen].clearOut
  override def additionalImports():String = ""
}

class LMSSparkGen(cls:String="Query") extends LMSGen(cls,SparkExpGen) with IScalaGen {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  import ManifestHelper.{man,zero,manEntry,manStore,manContainer}
  import ddbt.lib.store._
  import impl.Rep

  override def genMap(m:MapDef):String = {
    if (m.keys.size==0) createVarDefinition(m.name, m.tp)+";"
    else {
      impl.codegen.generateNewStore(ctx0(m.name)._1.asInstanceOf[impl.codegen.IR.Sym[_]], true)
    }
  }

  override def genAllMaps(maps:Seq[MapDef]) = "class "+cls+"MapContext(val partitionId: Int) extends LocalMapContext {\n"+ind(
    maps.filter(!_.name.endsWith("_DELTA")).map(genMap).mkString("\n")
  )+"\n}"
  // +"\n"+maps.filter(_.name.endsWith("_DELTA")).map(genMap).mkString("\n")



  override def genLMS(s0:System):(String,String,String,String) = {
    def relationUsingMapName(mName: String) = s0.triggers.filter(t => t.evt != EvtReady && t.stmts.exists(_ match{
      case StmtMap(m2,_,_,_) if m2.name == mName => true
      case _ => false
    }))(0).evt match {
      case EvtBatchUpdate(s) => s.name
      case e => sys.error("Unsupported event type: " + e)
    }
    def relationUsingMap(m: MapDef) = relationUsingMapName(m.name)

    val classLevelMaps = s0.triggers.flatMap{ t=> //local maps
      t.stmts.filter{
        case MapDef(_,_,_,_) => true
        case _ => false
      }.map{
        case m@MapDef(_,_,_,_) => m
        case _ => null
      }
    } ++
    maps.map{
      case (_,m@MapDef(_,_,_,_)) => m
    } // XXX missing indexes
    ctx0 = (classLevelMaps ++ s0.triggers.filter(_.evt match {
      case EvtBatchUpdate(s) => true
      case _ => false
    }).map(_.evt match { //delta relations
      case EvtBatchUpdate(sc) =>
        val name = sc.name
        val schema = s0.sources.filter(x => x.schema.name == name)(0).schema
        val deltaRel = sc.deltaSchema
        val tp = TypeLong
        val keys = schema.fields
        MapDef(deltaRel,tp,keys,null)
      case _ => null
    })).map{
      case MapDef(name,tp,keys,_) => if (keys.size==0) {
        val m = man(tp)
        val s = impl.named(name,false)(m)
        s.emitted = true
        (name,(s,keys,tp))
      } else {
        val m = me(keys.map(_._2),tp)

        if(name.endsWith("_DELTA")) {
          val s=impl.named(name,true)(manContainer(m))
          s.asInstanceOf[impl.Sym[_]].attributes.put(oltp.opt.lifters.SparkGenStore.FIELDS, keys.map(_._1))
          (name,(/*impl.newSStore()(m)*/s,keys,tp))
        } else {
          val s=impl.named(name,true)(manStore(m))
          impl.collectStore(s)(m)
          (name,(/*impl.newSStore()(m)*/s,keys,tp))
        }
      }
    }.toMap // XXX missing indexes
    val deltaMaps = classLevelMaps.filter(_.name.endsWith("_DELTA"))
    val (str,ld0,_) = genInternals(s0)
    //TODO: this should be replaced by a specific traversal for completing the slice information
    // s0.triggers.map(super.genTrigger)
    val tsResBlks = s0.triggers.map(t => (genTriggerLMS(t,s0), t.evt match {
      case EvtBatchUpdate(Schema(n,_)) =>
        val rel = s0.sources.filter(_.schema.name == n)(0).schema
        val name = rel.name
        deltaMaps.filter(relationUsingMap(_) == name).map{ m =>
          m.name+":"+name+"Container"
        }.mkString(", ")
      case _ => ""
    })) // triggers (need to be generated before maps)
    val ts = tsResBlks.map{ case ((name,_,b),params) =>
      impl.emitTrigger(b,name,params)
    }.mkString("\n\n")
    val ms = genAllMaps(classLevelMaps) // maps
    var outStream = new java.io.StringWriter
    var outWriter = new java.io.PrintWriter(outStream)
    //impl.codegen.generateClassArgsDefs(outWriter,Nil)

    impl.codegen.emitDataStructures(outWriter)
    val ds = outStream.toString
    val outputBatchCls = cls+"Batch"
    val inputBatchCls = "TpchBatch"
    val contextCls = cls+"MapContext"
    val taskCls = cls+"Task"
    val r=ds+"\n"+ms+"\n\n"+
    "class "+outputBatchCls+"{\n"+
    deltaMaps.map{ m =>
    "  val "+m.name+" = new "+relationUsingMap(m)+"Container(batchSize, "+m.keys.map("use"+_._1+" = true").mkString(", ")+")\n"
    }.mkString+
    "  /*private*/ val containers = Array[TPCHContainer]("+deltaMaps.map(_.name).mkString(", ")+")\n\n" +
    // "  private def signature: Int = {\n" +
    // "    if (containers.size > 32) throw new IllegalStateException(\"Too many containers.\")\n" +
    // "    containers.foldLeft (0) ((s, c) => (s << 1) | (if (c.capacity > 0) 1 else 0))\n" +
    // "  }\n\n" +
    // "  def clear() = containers foreach { _.clear() }\n\n" +
    // "  def write(out: OutputStreamWrapper): Unit = {\n" +
    // "    // write header (signature)\n" +
    // "    out.writeInt(signature)\n" +
    // "    // write containers\n" +
    // "    containers foreach { _.write(out) }\n" +
    // "  }\n" +
    "}\n\n"+
    "class "+taskCls+"(val batchSize: Int, val numPartitions: Int) extends TPCHTask["+contextCls+"] {\n" +
      ind(
        "val processedBatch = Array.tabulate(numPartitions)(id => new TPCHBatchPartition(id, new "+outputBatchCls+" ))\n\n"+
        "def onBatchUpdate(ctx: GlobalMapContext["+contextCls+"], batch: "+outputBatchCls+"): Unit = {\n"+
          ind(
            "def preprocess(input: "+inputBatchCls+", output: "+outputBatchCls+"): Unit = {\n"+
            ind(s0.triggers.filter(_.evt != EvtReady).map{ t => 
              ctx=Ctx(t.evt.schema.fields.map(x=>(x._1,(x._2,x._1))).toMap)
              val schemaName = t.evt.schema.name
              "val in"+schemaName+" = input."+schemaName+"\n"+
              "val len"+schemaName+" = input."+schemaName+".size\n"+
              t.stmts.filter(!filterStatement(_)).map { s =>
                prepGenStmt(t,s)+"\n"
              }.mkString
            }.mkString("//------\n\n"))+
            "\n}\n\n"+
            "swPreprocess.time {\n"+
            "  processedBatch.clear()\n"+
            "  preprocess(batch, processedBatch)\n"+
            "}\n"+
            deltaMaps.map{ m =>
              "total"+m.name+"Tuples += batch."+m.name+".size\n"
            }.mkString+"\n"+
            "val partitionedBatch = ctx.sc.parallelize(processedBatch, numPartitions)\n\n"+
            "ctx.rdd.zip(partitionedBatch).foreach {\n"+
            "  case ((id, ctx), partitionedBatch) => {\n"+
              ind(
                ts+"\n"+
                s0.triggers.filter(_.evt != EvtReady).map{ t => 
                  val relName = t.evt.schema.name
                  "Stopwatch.time(\"ON "+relName+" executing... \", onBatchUpdate"+relName+"("+
                    deltaMaps.filter(relationUsingMap(_) == relName).map("partitionedBatch.batch."+_.name).mkString(", ")+"))"
                }.mkString("\n")
              ,2)+
            "\n  }\n"+
            "}\n"+
            "swBroadcastUnpersist.time { partitionedBatch.unpersist(false) }"
          )+
        "\n}\n"
      )+
    "\n}"
    (r,str,ld0,consts)
  }

  override def filterStatement(s:Stmt) = s match {
    case StmtMap(m,_,_,_) if m.name.endsWith("_DELTA") => false
    case _ => true
  }

  override def additionalImports():String = super.additionalImports+"import scala.util.hashing.MurmurHash3.stringHash\n"


  def prepGenStmt(trig:Trigger, s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) =>
      val (fop,sop)=op match { case OpAdd => ("add","+=") case OpSet => ("add","=") }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = oi match {
        case Some(ie) =>
          ctx.load()
          prepCpsExpr(ie,(i:String)=>
            if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
            else "if ("+m.name+".get("+genTuple(m.keys map ctx)+")==0) "+m.name+".set("+genTuple(m.keys map ctx)+","+i+");\n"
          )
        case None => ""
      }
      ctx.load(); clear+init+prepCpsExpr(e,(v:String) =>
        (if (m.keys.size==0) {
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              "(if ("+c+") "+m.name+" "+sop+" "+t+" else ());\n"
            case _ =>
              m.name+" "+sop+" "+v+"\n"
          }
        } else {
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              if(m.name.endsWith("_DELTA")){
                val partitionId = "partitionId"+m.name
                val outContainer = "out"+m.name
                val inContainer = "in"+trig.evt.schema.name
                val i = "i"+trig.evt.schema.name
                "(if ("+c+") "+"{\n"+ind(
                  "val "+partitionId+" = 0; // TODO\n"+
                  "val "+outContainer+" = output("+partitionId+").batch."+m.name+"\n"+
                  m.keys.map{k =>
                    outContainer+"."+k+" += ("+inContainer+"."+k+","+i+")\n"
                  }.mkString+
                  outContainer+".values += "+t+"\n"
                )+
                "\n} else ());\n"
              } else {
                "(if ("+c+") "+m.name+"."+fop+"("+genTuple(m.keys map ctx)+","+t+") else ());\n"
              }
            case _ =>
              if(m.name.endsWith("_DELTA")){
                val partitionId = "partitionId"+m.name
                val outContainer = "out"+m.name
                val inContainer = "in"+trig.evt.schema.name
                val i = "i"+trig.evt.schema.name
                "{\n"+ind(
                  "val "+partitionId+" = 0; // TODO\n"+
                  "val "+outContainer+" = output("+partitionId+").batch."+m.name+"\n"+
                  m.keys.map{k =>
                    outContainer+"."+k+" += ("+inContainer+"."+k+","+i+")\n"
                  }.mkString+
                  outContainer+".values += "+v+"\n"
                )+
                "\n}\n"
              } else {
                m.name+"."+fop+"("+genTuple(m.keys map ctx)+","+v+")\n"
              }
          }
        }),/*if (op==OpAdd)*/ Some(m.keys zip m.tks) /*else None*/) // XXXX commented out the if expression
    case m@MapDef(_,_,_,_) => "" //nothing to do
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def prepCpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match { // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp,v) => tp match {
      case TypeLong => co(v+"L")
      case TypeString => co("\""+v+"\"")
      case _ => co(v)
    }
    case Exists(e) => prepCpsExpr(e,(v:String)=>co("(if ("+v+" != 0) 1L else 0L)"))
    case Cmp(l,r,op) => prepCpsExpr(l,(ll:String)=>prepCpsExpr(r,(rr:String)=>co(cmpFunc(l.tp,op,ll,rr))))
    case app@Apply(fn,tp,as) => prepApplyFunc(co,fn,tp,as)
    //ki : inner key
    //ko : outer key
    //Example:
    //  f(A) {
    //    Mul(M[A,B],ex)
    //  }
    // will be translated to:
    // f(A) {
    //   M.slice(A).foreach{ case (k,v) => // here A is ko
    //     val B = k._2 // here B is ki
    //     v * ex
    //   }
    // }
    case m@MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
      if(ks.size == 0) { // variable
        if(ctx contains n) co(rn(n)) else co(n)
      } else if (ki.size == 0) { // all keys are bound
        co(n+".get("+genTuple(ks map ctx)+")")
      } else { // we need to iterate over all keys not bound (ki)
        val (k0,v0)=(fresh("k"),fresh("v"))
        val sl = if (ko.size > 0) ".slice("+slicase m@MapDefce(n,ko.map(_._2))+","+tup(ko.map(x=>rn(x._1)))+")" else "" // slice on bound variables
        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)
        if(n.startsWith("DELTA_")){
          val col = "in"+n.replace("DELTA_","")
          val len = "len"+n.replace("DELTA_","")
          val i = "i"+n.replace("DELTA_","")
          "val "+i+" = 0\n"+
          "while("+i+" < "+len+") {\n"+
            ind(
              // (if (ks.size>1) {
              //   ki.map{case (k,i)=>"val "+rn(k)+" = "+k0+"._"+(i+1)+";\n"}.mkString
              // } else "")+
              "val " + v0 + " = " + col + ".values("+i+")\n"+
              co(v0)+"\n"+
              i + " += 1"
            )+"\n"+
          "}\n" // bind free variables from retrieved key
        } else {
          n+sl+".foreach { ("+(if (ks.size==1) rn(ks.head) else k0)+","+v0+") =>\n"+
            ind(
              (if (ks.size>1) {
                ki.map{case (k,i)=>"val "+rn(k)+" = "+k0+"._"+(i+1)+";\n"}.mkString
              } else "")+
              co(v0)
            )+"\n"+
          "}\n" // bind free variables from retrieved key
        }
      }
    // "1L" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) prepCpsExpr(e,(v:String)=>co(cmpFunc(TypeLong,OpEq,rn(n),v)),am)
      else e match {
        case Ref(n2) => ctx.add(n,(e.tp,rn(n2))); co("1L") // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ =>
          ctx.add(n,(e.tp,fresh("l")))
          prepCpsExpr(e,(v:String)=> "val "+rn(n)+" = "+v+";\n"+co("1L"),am)
      }
    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) )
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el,er) => //prepCpsExpr(el,(vl:String)=>prepCpsExpr(er,(vr:String)=>co(if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"),am),am)
      def mul(vl:String,vr:String) = { // simplifies (vl * vr)
        def vx(vl:String,vr:String) = if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"
        //pulling out the conditionals from a multiplication
        (extractBooleanExp(vl),extractBooleanExp(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => "(if ("+cl+" && "+cr+") "+vx(tl,tr)+" else "+ex.tp.zeroScala+")"
          case (Some((cl,tl)),_) => "(if ("+cl+") "+vx(tl,vr)+" else "+ex.tp.zeroScala+")"
          case (_,Some((cr,tr))) => "(if ("+cr+") "+vx(vl,tr)+" else "+ex.tp.zeroScala+")"
          case _ => vx(vl,vr)
        }
      }
      prepCpsExpr(el,(vl:String)=>prepCpsExpr(er,(vr:String)=>co(mul(vl,vr)),am),am)
    // Add(el,er)
    // ==
    //   Add( (el,ctx0) -> (vl,ctx1) , (er,ctx0) -> (vr,ctx2) )
    //         <-------- L -------->    <-------- R -------->
    //    (add - if there's no free variable) ==>
    //   (v=vl+vr , ctx0)
    //    (union - if there are some free variables) ==>
    //   T = Map[....]
    //   foreach vl in L, T += vl
    //   foreach vr in R, T += vr
    //   foreach t in T, co(t)
    case a@Add(el,er) =>
      if (a.agg==Nil) {
        val cur=ctx.save
        prepCpsExpr(el,(vl:String)=>{
          ctx.load(cur)
          prepCpsExpr(er,(vr:String)=>{
            ctx.load(cur)
            co("("+vl+" + "+vr+")")
          },am)
        },am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) =>
          val cur=ctx.save
          val s1=prepCpsExpr(el,co,am)
          ctx.load(cur)
          val s2=prepCpsExpr(er,co,am)
          ctx.load(cur)
          s1+s2
        case _ =>
          val (acc,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val ksTp = a.agg.map(_._2)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = prepCpsExpr(el,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,acc,ks,v),tmp); ctx.load(cur)
          val s2 = prepCpsExpr(er,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,acc,ks,v),tmp); ctx.load(cur)

          genVar(acc,ex.tp,a.agg.map(_._2))+
          s1+
          s2+
          prepCpsExpr(mapRef(acc,ex.tp,a.agg),co)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) {
        val a0=fresh("agg")

        genVar(a0,a.tp)+
        prepCpsExpr(e,(v:String)=>
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              "(if ("+c+") "+a0+" += "+t+" else ())\n"
            case _ =>
              a0+" += "+v+"\n"
          }
        )+
        co(a0)
      } else am match {
        case Some(t) if t.toSet.subsetOf(aks.toSet) => prepCpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = M3Map.temp["+genTupleDef(aks.map(x=>x._2))+","+e.tp.toScala+"]()\n"+
          prepCpsExpr(e,(v:String)=>ADD_TO_TEMP_MAP_FUNC(aks.map(_._2),e.tp,a0,aks.map(_._1),v),tmp);
          ctx.load(cur)
          s1+prepCpsExpr(mapRef(a0,e.tp,aks),co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  // var ctx:Ctx[(Type,String)] = null // Context: variable->(type,unique_name)
  // def cmpFunc(tp: Type, op:OpCmp, arg1: String, arg2: String, withIfThenElse: Boolean = true) = tp match {
  //   case _ => 
  //     if(withIfThenElse)
  //       "(if ("+arg1+" "+op+" "+arg2+") 1L else 0L)"
  //     else
  //       arg1+" "+op+" "+arg2
  // }
  // def extractBooleanExp(s:String):Option[(String,String)] = if (!s.startsWith("(if (")) {
  //   None
  // } else {
  //   var d=1
  //   val pInit="(if (".length
  //   var p=pInit
  //   while(d>0) {
  //     if (s(p)=='(') d+=1 else if (s(p)==')') d-=1
  //     p+=1
  //   }
  //   Some(s.substring(pInit,p-1),s.substring(p+1,s.lastIndexOf("else")-1))
  // }
  // def ADD_TO_TEMP_MAP_FUNC(ksTp:List[Type],vsTp:Type,m:String,ks:List[String],vs:String) = extractBooleanExp(vs) match {
  //   case Some((c,t)) =>
  //     "(if ("+c+") "+m+".add("+genTuple(ks map ctx)+","+t+") else ())\n"
  //   case _ =>
  //     m+".add("+genTuple(ks map ctx)+","+vs+")\n"
  // }

  def prepApplyFunc(co:String=>String, fn1:String, tp:Type, as1:List[Expr]) = {
    val (as, fn) = (fn1 match {
      case "regexp_match" if (ENABLE_REGEXP_PARTIAL_EVAL && as1.head.isInstanceOf[Const] && !as1.tail.head.isInstanceOf[Const]) => val regex=as1.head.asInstanceOf[Const].v; val preg0=regexpCacheMap.getOrElse(regex, fresh("preg")); regexpCacheMap.update(regex,preg0); (as1.tail, "preg_match("+preg0+",")
      case _ => (as1, fn1+"(")
    })
    if (as.forall(_.isInstanceOf[Const])) co(constApply(Apply(fn1,tp,as1))) // hoist constants resulting from function application
    else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>prepCpsExpr(a,(v:String)=>c0(p+(if (i>0) "," else "")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+fn) }
  }
}
