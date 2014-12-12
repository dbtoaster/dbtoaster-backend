package ddbt.codegen
import ddbt.codegen.lms._
import ddbt.ast._
import ddbt.lib._

/**
 * This code generator is similar to ScalaGen but targets Spark as a parallel backend.
 *
 * @author Mohammad Dashti
 */
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
        val sl = if (ko.size > 0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(x=>rn(x._1)))+")" else "" // slice on bound variables
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
