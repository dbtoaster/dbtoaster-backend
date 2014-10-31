package ddbt.codegen
import ddbt.ast._

/**
 * CppGen is responsible to transform a typed AST into vanilla C++ code (String).
 *
 * @author Mohammad Dashti
 */
class CppGen(override val cls:String="Query") extends ICppGen

trait ICppGen extends IScalaGen {
  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,fresh,freshClear} // common functions
  val VALUE_NAME = "__av"

  //Sample entry definitions are accumulated in this variable
  var sampleEntDef = ""

  private var mapDefs = Map[String,MapDef]() //mapName => MapDef
  private val mapDefsList = scala.collection.mutable.MutableList[(String,MapDef)]() //List(mapName => MapDef) to preserver the order
  private val tmpMapDefs = HashMap[String,(List[Type],Type)]() //tmp mapName => (List of key types and value type)

  private val helperFuncUsage = HashMap[(String,String),Int]()
  def FIND_IN_MAP_FUNC(m:String) = { helperFuncUsage.update(("FIND_IN_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("FIND_IN_MAP_FUNC" -> m),0)+1); m+".getValueOrDefault" }
  def SET_IN_MAP_FUNC(m:String) = { helperFuncUsage.update(("SET_IN_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("SET_IN_MAP_FUNC" -> m),0)+1); m+".setOrDelOnZero" }
  def ADD_TO_MAP_FUNC(m:String) = { helperFuncUsage.update(("ADD_TO_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("ADD_TO_MAP_FUNC" -> m),0)+1); m+".addOrDelOnZero" }
  override def ADD_TO_TEMP_MAP_FUNC(ksTp:List[Type],vsTp:Type,m:String,ks:List[String],vs:String) = {
    val sampleTempEnt=fresh("st")
    sampleEntDef+="  "+tupType(ksTp, vsTp)+" "+sampleTempEnt+";\n"
    extractBooleanExp(vs) match {
      case Some((c,t)) =>
        "(/*if */("+c+") ? add_to_temp_map"+/*"<"+tupType(ksTp, vsTp)+">"+*/"("+m+", "+sampleTempEnt+".modify"+tup(ks map rn, t)+") : voidFunc());\n"
      case _ =>
        "add_to_temp_map"+/*"<"+tupType(ksTp, vsTp)+">"+*/"("+m+", "+sampleTempEnt+".modify"+tup(ks map rn, vs)+");\n"
    }
  }

  val tempTupleTypes = HashMap[String,(List[Type],Type)]()
  def tup(ks:List[String],vs:String) = "("+ks.mkString(",")+","+vs+")"
  def tupType(ksTp:List[Type], vsTp:Type):String = {
    val tupleTp="tuple"+(ksTp.size+1)+"_"+ksTp.map(_.simpleName).mkString+"_"+vsTp.simpleName
    tempTupleTypes.update(tupleTp,(ksTp, vsTp))
    tupleTp
  }

  override def consts = cs.map{ case (Apply(f,tp,as),n) => 
    val vs=as.map(a=>cpsExpr(a))
    "/*const static*/ "+tp.toCpp+" "+n+";\n"
  }.mkString+"\n" // constant member definition

  def constsInit = cs.map{ case (Apply(f,tp,as),n) => f match {
      case "STRING_TYPE" => n+" = "+f+"(\""+as(0).asInstanceOf[Const].v+"\");\n" // string initilization
      case _ => val vs=as.map{
          case Const(tp,v) if (tp == TypeString) => "STRING_TYPE(\""+v+"\")"
          case a => cpsExpr(a)
        }
        n+" = "+"U"+f+"("+vs.mkString(",")+");\n"
    }
  }.mkString+"\n" // constant member initilization

  // Create a variable declaration
  //XXXXX TODO
  override def genVar(n:String,vsTp:Type,ksTp:List[Type]) = if (ksTp==Nil) {
    vsTp.toCpp+" "+n+" = "+vsTp.zeroCpp+";\n"
  } else {
    tmpMapDefs += (n -> (ksTp,vsTp))
    n+".clear();\n"
  }

  def getIndexId(m:String,is:List[Int]):String = (if(is.isEmpty) (0 until mapDefs(m).keys.size).toList else is).mkString //slice(m,is)

  override def cmpFunc(tp: Type, op:OpCmp, arg1: String, arg2: String, withIfThenElse: Boolean) = tp match {
    // case TypeDouble => op match {
    //   case OpEq => "abs("+arg1+"-"+arg2+") < KDouble::diff_p"
    //   case OpNe => "abs("+arg1+"-"+arg2+") >= KDouble::diff_p"
    //   case _ => arg1+" "+op+" "+arg2
    // }
    case _ =>
      if(withIfThenElse)
        "(/*if */("+arg1+" "+op+" "+arg2+")"+" ? 1L : 0L)"
      else
        arg1+" "+op+" "+arg2
  }

  // extract cond and then branch of "if (c) t else 0"
  // no better way for finding boolean type
  // TODO: add Boolean type
  override def extractBooleanExp(s:String):Option[(String,String)] = if (!s.startsWith("(/*if */(")) {
      None
    } else {
      var d=1
      val pInit="(/*if */(".length
      var p=pInit
      while(d>0) {
        if (s(p)=='(') d+=1 else if (s(p)==')') d-=1
        p+=1
      }
      Some(s.substring(pInit,p-1),s.substring(p+" ? ".length,s.lastIndexOf(":")-1))
    }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match { // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp,v) => tp match {
      case TypeLong => co(v+"L")
      case TypeString => cpsExpr(Apply("STRING_TYPE",TypeString,List(ex)),co,am)
      case _ => co(v)
    }
    case Exists(e) => cpsExpr(e,(v:String)=>co("("+v+" != 0 ? 1L : 0L)"))
    case Cmp(l,r,op) => co(cpsExpr(l,(ll:String)=>cpsExpr(r,(rr:String)=>cmpFunc(l.tp,op,ll,rr))))
    case app@Apply(fn1,tp,as1) => {
      val (as, fn) = (fn1 match {
        case "date_part" if as1.head.isInstanceOf[Const] => (as1.tail, as1.head.asInstanceOf[Const].v.toLowerCase+"_part")
        case _ => (as1, fn1)
      })
      applyFunc(co,fn,tp,as)
    }
    case m@MapRef(n,tp,ks) =>
      val (ko,ki) = (ks zip m.tks).zipWithIndex.partition{case((k,ktp),i)=>ctx.contains(k)}
      val mapName = m.name
      val mapType = mapName+"_map"
      val mapEntry = mapName+"_entry"
      if(ks.size == 0) { // variable
        if(ctx contains n) co(rn(n)) else co(n)
      } else if (ki.size==0) {
        val sampleEnt=fresh("se")
        sampleEntDef+=(if(ks.size > 0) "  "+mapEntry+" "+sampleEnt+";\n" else "")
        co(FIND_IN_MAP_FUNC(n)+"("+sampleEnt+".modify("+(ks map rn).mkString(",")+"))") // all keys are bound
      } else {
        val lup0 = fresh("lkup") //lookup
        val lupItr0 = lup0+"_it"
        val lupItrNext0 = "next_"+lupItr0
        val lupEnd0 = lup0+"_end"
        val is = ko.map(_._2)
        val iKeys = ko.map(x=>rn(x._1._1))
        val iKeysTp = ko.map(x=>x._1._2)
        val (k0,v0,e0)=(fresh("k"),fresh("v"),fresh("e"))

        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)

        if (!m.isTemp) { // slice or foreach
          val mapDef = mapDefs(n)

          val n0= fresh("n")
          val idx0= fresh("i")
          val mapType = n+"_map"
          val idxName = "HashIndex_"+mapType+"_"+getIndexId(n,is)
          val idxFn = mapType+"key"+getIndexId(n,is)+"_idxfn"
          val body = ki.map{case ((k,ktp),i)=>ktp.toCpp+" "+rn(k)+" = "+e0+"->"+mapDef.keys(i)._1+";\n"}.mkString+
          tp.toCpp+" "+v0+" = "+e0+"->"+VALUE_NAME+";\n"+
          co(v0)

          if (ko.size>0) { //slice
            val idxIndex = slice(n,is)+1 //+1 because the index 0 is the unique index
            val sampleEnt=fresh("se")
            sampleEntDef+=(if (m.keys.size > 0) "  "+mapEntry+" "+sampleEnt+";\n" else "")

            val h0= fresh("h")
            "{ //slice\n"+
            "  const HASH_RES_t "+h0+" = "+idxFn+"::hash("+sampleEnt+".modify"+getIndexId(mapName,is)+"("+iKeys.mkString(", ")+"));\n"+
            "  const "+idxName+"* "+idx0+" = static_cast<"+idxName+"*>("+n+".index["+idxIndex+"]);\n"+
            "  "+idxName+"::IdxNode* "+n0+" = &("+idx0+"->buckets_["+h0+" % "+idx0+"->size_]);\n"+
            "  "+mapEntry+"* "+e0+";\n"+
            "  do if (("+e0+"="+n0+"->obj) && "+h0+" == "+n0+"->hash && "+idxFn+"::equals("+sampleEnt+", *"+e0+")) {\n"+
                 ind(body,2)+"\n"+
            "  } while (("+n0+"="+n0+"->nxt));\n"+
            "}\n"
          } else { //foreach
            "{ //foreach\n"+
            "  "+mapEntry+"* "+e0+" = "+n+".head;\n"+
            "  while("+e0+"){\n"+
                 ind(body,2)+"\n"+
            "    "+e0+" = "+e0+"->nxt;\n"+
            "  }\n"+
            "}\n"
          }
        } else { //only foreach for Temp map
          "{ //temp foreach\n"+
          "  "+tupType(m.tks,m.tp)+"* "+e0+" = "+n+".head;\n"+
          "  while("+e0+"){\n"+
          ki.map{case ((k,ktp),i)=> "    "+ktp.toCpp+" "+rn(k)+" = "+e0+"->_"+(i+1)+";\n"}.mkString+
          "    "+tp.toCpp+" "+v0+" = "+e0+"->"+VALUE_NAME+";\n"+
               ind(co(v0),2)+"\n"+
          "    "+e0+" = "+e0+"->nxt;\n"+
          "  }\n"+
          "}\n"
        }
      }
    // "1L" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co(cmpFunc(TypeLong,OpEq,rn(n),v)),am)
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
          cpsExpr(e,(v:String)=> e.tp.toCpp+" "+rn(n)+" = "+v+";\n"+co("1L"),am)
      }
    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) ) 
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el,er) => //cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"),am),am)
      def mul(vl:String,vr:String) = { // simplifies (vl * vr)
        def vx(vl:String,vr:String) = if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"
        //pulling out the conditionals from a multiplication
        (extractBooleanExp(vl),extractBooleanExp(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => "(/*if */("+cl+" && "+cr+") ? "+vx(tl,tr)+" : "+ex.tp.zeroCpp+")"
          case (Some((cl,tl)),_) => "(/*if */("+cl+") ? "+vx(tl,vr)+" : "+ex.tp.zeroCpp+")"
          case (_,Some((cr,tr))) => "(/*if */("+cr+") ? "+vx(vl,tr)+" : "+ex.tp.zeroCpp+")"
          case _ => vx(vl,vr)
        }
      }
      cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(mul(vl,vr)),am),am)
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
        cpsExpr(el,(vl:String)=> {
          ctx.load(cur)
          cpsExpr(er,(vr:String)=>{
            ctx.load(cur)
            co("("+vl+" + "+vr+")")
          },am)
        },am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) => 
          val cur=ctx.save
          val s1=cpsExpr(el,co,am)
          ctx.load(cur)
          val s2=cpsExpr(er,co,am)
          ctx.load(cur)
          s1+s2
        case _ =>
          val (acc,k0,v0)=(fresh("_c"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val ksTp = a.agg.map(_._2)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,acc,ks,v),tmp); ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,acc,ks,v),tmp); ctx.load(cur)

          genVar(acc,a.tp,a.agg.map(_._2))+
          s1+
          s2+
          cpsExpr(mapRef(acc,a.tp,a.agg),co)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) {
        val a0=fresh("agg")

        genVar(a0,a.tp)+
        cpsExpr(e,(v:String)=>
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              "(/*if */("+c+") ? "+a0+" += "+t+" : "+a.tp.zeroCpp+");\n"
            case _ =>
              a0+" += "+v+";\n"
          }
        )+
        co(a0)
      } else am match {
        case Some(t) if t.toSet.subsetOf(aks.toSet) => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = genVar(a0,e.tp,aks.map(_._2))+"\n"+cpsExpr(e,(v:String)=>ADD_TO_TEMP_MAP_FUNC(aks.map(_._2),e.tp,a0,aks.map(_._1),v),tmp);
          ctx.load(cur)
          s1+cpsExpr(mapRef(a0,e.tp,aks),co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  override def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) =>
      val (fop,sop)=op match { case OpAdd => (ADD_TO_MAP_FUNC(m.name),"+=") case OpSet => (ADD_TO_MAP_FUNC(m.name),"=") }
      val mapName = m.name
      val mapType = mapName+"_map"
      val mapEntry = mapName+"_entry"
      val sampleEnt=fresh("se")
      sampleEntDef+=(if(m.keys.size > 0) "  "+mapEntry+" "+sampleEnt+";\n" else "")
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear();\n" else "" }
      val init = oi match {
        case Some(ie) =>
          ctx.load()
          cpsExpr(ie,(i:String)=>
            if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
            else "if ("+FIND_IN_MAP_FUNC(m.name)+"("+sampleEnt+".modify("+(m.keys map rn).mkString(",")+"))==0) "+SET_IN_MAP_FUNC(m.name)+"("+sampleEnt+", "+i+");\n"
          )
        case None => ""
      }
      ctx.load(); clear+init+cpsExpr(e,(v:String) => 
        (if (m.keys.size==0) {
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              "(/*if */("+c+") ? "+m.name+" "+sop+" "+t+" : 0L);\n"
            case _ =>
              m.name+" "+sop+" "+v+";\n"
          }
        } else {
          extractBooleanExp(v) match {
            case Some((c,t)) =>
              "(/*if */("+c+") ? "+fop+"("+sampleEnt+".modify("+(m.keys map rn).mkString(",")+"),"+t+") : voidFunc());\n"
            case _ =>
              fop+"("+sampleEnt+".modify("+(m.keys map rn).mkString(",")+"),"+v+");\n"
          }
        }), /*if (op==OpAdd)*/ Some(m.keys zip m.tks) /*else None*/)
    case m@MapDef(_,_,_,_) => "" //nothing to do
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  override def genTrigger(t:Trigger, s0:System):String = {
    val (n,as, xActCounter) = t.evt match {
      case EvtReady => ("system_ready_event",Nil,"")
      case EvtBatchUpdate(sc@Schema(n,cs)) => ("batch_update_"+n,cs,"tN+="+sc.deltaSchema+".count()-1; ++tN;") //later, we will find ++tN in the code to add some benchmarkings, so we will let it remain here
      case EvtAdd(Schema(n,cs)) => ("insert_"+n,cs,"++tN;")
      case EvtDel(Schema(n,cs)) => ("delete_"+n,cs,"++tN;")
    }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap)
    val preBody="BEGIN_TRIGGER(exec_stats,\""+n+"\")\n"+
                "BEGIN_TRIGGER(ivc_stats,\""+n+"\")\n"+
                "{  "+(if(ddbt.Compiler.DEPLOYMENT_STATUS == ddbt.Compiler.DEPLOYMENT_STATUS_RELEASE) "//" else "")+xActCounter+"\n"
    val body=ind(t.stmts.map(genStmt).mkString)
    val pstBody="\n}\n"+
                "END_TRIGGER(exec_stats,\""+n+"\")\n"+
                "END_TRIGGER(ivc_stats,\""+n+"\")\n"
    ctx=null
    val params = t.evt match {
      case EvtBatchUpdate(Schema(n,_)) =>
        val rel = s0.sources.filter(_.schema.name == n)(0).schema
        val ks = rel.fields.map(_._2)
        val tp = TypeLong
        rel.deltaSchema + "_map& " + rel.deltaSchema
      case _ =>
        as.map(a=>"const "+a._2.toCppRefType+" "+a._1).mkString(", ")
    }
    "void on_"+n+"("+params+") {\n"+ind(preBody+body+pstBody)+"\n}"
  }

  override def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  override def genMap(m:MapDef):String = {
    m.toCppType+" "+m.name+";\n"
  }

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = map+".add("+keyNamesConcat+",1L)"

  override def toMapFunction(q: Query) = q.name+".toMap"
  override def clearOut = {}
  override def onEndStream = ""

  def genIntermediateDataStructureRefs(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>queries.filter(_.name==m.name).size == 0}.map(genMap).mkString

  def genTempMapDefs = tmpMapDefs.map{ case (n, (ksTp, vsTp)) => "MultiHashMap<"+tupType(ksTp, vsTp)+","+vsTp.toCpp+",HashIndex<"+tupType(ksTp, vsTp)+","+vsTp.toCpp+"> > "+n+";\n" }.mkString

  def isExpressiveTLQSEnabled(queries:List[Query]) = queries.exists{ query => query.map match {
      case MapRef(n,_,_) => if (n == query.name) false else true
      case _ => true
    }
  }

  private def getInitializationForIntermediateValues(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>(queries.filter(_.name==m.name).size == 0) && (m.keys.size == 0)}.map{m=>", "+m.name+"(" + m.tp.zeroCpp + ")"}.mkString

  private def getInitializationForTempMaps = tmpMapDefs.map{ case (n, (ksTp, vsTp)) => ", "+n+"(16U)" }.mkString

  private def getInitializationForPublicValues(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>(queries.filter(_.name==m.name).size != 0) && (m.keys.size == 0)}.map{m=>", "+m.name+"(" + m.tp.zeroCpp + ")"}.mkString

  private def getInitializationForTLQ_T(maps:List[MapDef],queries:List[Query]) = getInitializationForPublicValues(maps,queries) + (if(isExpressiveTLQSEnabled(queries)) getInitializationForIntermediateValues(maps,queries)+getInitializationForTempMaps else "")

  private def getInitializationForDATA_T(maps:List[MapDef],queries:List[Query]) = (if(isExpressiveTLQSEnabled(queries)) "" else getInitializationForIntermediateValues(maps,queries)+getInitializationForTempMaps)

  override def apply(s0:System):String = {
    def register_maps = s0.maps.map{m=>"pb.add_map<"+m.toCppType+">( \""+m.name+"\", "+m.name+" );\n"}.mkString

    def register_relations = s0.sources.map{s => "pb.add_relation(\""+s.schema.name+"\"" + (if(s.stream) "" else ", true") + ");\n"}.mkString

    def register_table_triggers = s0.sources.filter(!_.stream).map{ s => 
      (if(s0.triggers.exists{
        t=>t.evt match {
          case EvtBatchUpdate(_) => true
          case _ => false
        }
      }) "pb.add_trigger(\""+s.schema.name+"\", batch_update, std::bind(&data_t::unwrap_batch_update_"+s.schema.name+", this, std::placeholders::_1));\n" else "") +
      "pb.add_trigger(\""+s.schema.name+"\", insert_tuple, std::bind(&data_t::unwrap_insert_"+s.schema.name+", this, std::placeholders::_1));\n"
      
    }.mkString

    def register_stream_triggers = s0.triggers.filter(_.evt != EvtReady).map{ t=>t.evt match {
        case EvtBatchUpdate(Schema(n,_)) =>
          "pb.add_trigger(\""+n+"\", batch_update, std::bind(&data_t::unwrap_batch_update_"+n+", this, std::placeholders::_1));\n" +
          "pb.add_trigger(\""+n+"\", insert_tuple, std::bind(&data_t::unwrap_insert_"+n+", this, std::placeholders::_1));\n" +
          "pb.add_trigger(\""+n+"\", delete_tuple, std::bind(&data_t::unwrap_delete_"+n+", this, std::placeholders::_1));\n"
        case EvtAdd(Schema(n,_)) => "pb.add_trigger(\""+n+"\", insert_tuple, std::bind(&data_t::unwrap_insert_"+n+", this, std::placeholders::_1));\n"
        case EvtDel(Schema(n,_)) => "pb.add_trigger(\""+n+"\", delete_tuple, std::bind(&data_t::unwrap_delete_"+n+", this, std::placeholders::_1));\n"
        case _ => ""
      }
    }.mkString

    def init_stats = {
      "#ifdef DBT_PROFILE\n"+
      "exec_stats = pb.exec_stats;\n"+
      "ivc_stats = pb.ivc_stats;\n"+
      //TODO XXX should be completed
      s0.triggers.map{ trg => trg.stmts.zipWithIndex.map { case (stmt,i) =>
          "exec_stats->register_probe("+stmt.stmtId+", \""+trg.evt.evtName+"_s"+i+"\");\n"
        }.mkString
      }.mkString+
      "#endif // DBT_PROFILE\n"
    }

    def genTableTriggers = s0.sources.filter(!_.stream).map{ s =>
      val name = s.schema.name
      val fields = s.schema.fields
      "void on_insert_"+name+"("+fields.map{case (fld,tp) => "const "+tp.toCpp+" "+fld }.mkString(", ")+") {\n"+
      "  "+name+"_entry e("+fields.map{case (fld,_) => fld }.mkString(", ")+", 1L);\n"+
      "  "+ADD_TO_MAP_FUNC(name)+"(e,1L);\n"+
      "}\n\n"+
      generateUnwrapFunction(EvtAdd(s.schema))+
      (if(s0.triggers.exists{
          t=>t.evt match {
            case EvtBatchUpdate(_) => true
            case _ => false
          }
        })
        "void unwrap_batch_update_"+name+"(const event_args_t& eaList) {\n"+
        "  size_t sz = eaList.size();\n"+
        "  for(size_t i=0; i < sz; i++){\n"+
        "    event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i]);\n"+
        "    "+name+"_entry e("+fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>((*ea)["+i+"])), "}.mkString+"1L);\n"+
        "    "+ADD_TO_MAP_FUNC(name)+"(e,1L);\n"+
        "  }\n"+
        "}\n\n"
      else "")
    }.mkString

    def genStreamTriggers = s0.triggers.map(t =>
      genTrigger(t,s0)+"\n"+
      (if(t.evt != EvtReady) generateUnwrapFunction(t.evt) else "")
    ).mkString

    def generateUnwrapFunction(evt:EvtTrigger) = {
      val (op,name,fields) = evt match {
        case EvtBatchUpdate(Schema(n,cs)) => ("batch_update",n,cs)
        case EvtAdd(Schema(n,cs)) => ("insert",n,cs)
        case EvtDel(Schema(n,cs)) => ("delete",n,cs)
        case _ => sys.error("Unsupported trigger event "+evt)
      }
      evt match {
        case b@EvtBatchUpdate(_) =>
          val schema = s0.sources.filter(_.schema.name == name)(0).schema
          val deltaRel = schema.deltaSchema
          val entryClass = deltaRel + "_entry"
          "void unwrap_"+op+"_"+name+"(const event_args_t& eaList) {\n"+
          "  size_t sz = eaList.size();\n"+
          "  if(sz == "+deltaRel+".count()) {\n"+
          "    "+entryClass+"* head = "+deltaRel+".head;\n"+
          "    for(size_t i=0; i < sz; i++){\n"+
          "      event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i]);\n"+
          "      head->modify("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>((*ea)["+i+"]))"}.mkString(", ")+");\n"+
          "      head->__av =  *(reinterpret_cast<"+TypeLong.toCpp+"*>((*ea)["+schema.fields.size+"]));\n"+
          "      head = head->nxt;\n"+
          "    }\n"+
          "  } else {\n"+
          "    "+deltaRel+".clear();\n"+
          "    for(size_t i=0; i < sz; i++){\n"+
          "      event_args_t* ea = reinterpret_cast<event_args_t*>(eaList[i]);\n"+
          "      "+entryClass+" e("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>((*ea)["+i+"])), "}.mkString+"*(reinterpret_cast<"+TypeLong.toCpp+"*>((*ea)["+schema.fields.size+"])));\n"+
          "      "+deltaRel+".insert_nocheck(e);\n"+
          "    }\n"+
          "  }\n"+
          "  on_"+op+"_"+name+"("+deltaRel+");\n"+
          "}\n\n" +
          (if(hasOnlyBatchProcessingForAdd(s0,b))
            "void unwrap_insert_"+name+"(const event_args_t& ea) {\n"+
            "  if("+deltaRel+".head){\n"+
            "    "+deltaRel+".head->modify("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>(ea["+i+"]))"}.mkString(", ")+");\n"+
            "    "+deltaRel+".head->__av =  1L;\n"+
            "  } else {\n"+
            "    "+deltaRel+".clear();\n"+
            "    "+entryClass+" e("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>(ea["+i+"])), "}.mkString+" 1L);\n"+
            "    "+deltaRel+".insert_nocheck(e);\n"+
            "  }\n"+
            "  on_batch_update_"+name+"("+deltaRel+");\n"+
            "}\n\n"
           else "") +
          (if(hasOnlyBatchProcessingForDel(s0,b))
            "void unwrap_delete_"+name+"(const event_args_t& ea) {\n"+
            "  if("+deltaRel+".head){\n"+
            "    "+deltaRel+".head->modify("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>(ea["+i+"]))"}.mkString(", ")+");\n"+
            "    "+deltaRel+".head->__av = -1L;\n"+
            "  } else {\n"+
            "    "+deltaRel+".clear();\n"+
            "    "+entryClass+" e("+schema.fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>(ea["+i+"])), "}.mkString+"-1L);\n"+
            "    "+deltaRel+".insert_nocheck(e);\n"+
            "  }\n"+
            "  on_batch_update_"+name+"("+deltaRel+");\n"+
            "}\n\n"
           else "")
        case _ =>
          "void unwrap_"+op+"_"+name+"(const event_args_t& ea) {\n"+
          "  on_"+op+"_"+name+"("+fields.zipWithIndex.map{ case ((_,tp),i) => "*(reinterpret_cast<"+tp.toCpp+"*>(ea["+i+"]))"}.mkString(", ")+");\n"+
          "}\n\n"
      }
    }

    def genMapStructDef(m:MapDef) = {
      val mapName = m.name
      val mapType = mapName+"_map"
      val mapEntry = mapName+"_entry"
      val mapValueType = m.tp.toCpp
      val fields = m.keys ++ List(VALUE_NAME -> m.tp)
      val fieldsWithIdx = fields.zipWithIndex
      val indices = sx.getOrElse(m.name,List[List[Int]]())
      //TODO XXX is it always required to create a unique index?
      val allIndices = ((0 until m.keys.size).toList -> true /*unique*/) :: indices.map(is => (is -> false /*non_unique*/))
      val multiKeyIndices = allIndices.filter{case (is,_) => is.size > 1}

      def genEntryStruct = 
        "struct "+mapEntry+" {\n"+
        "  "+fields.map{case (fld,tp) => tp.toCpp+" "+fld+"; "}.mkString+" "+mapEntry+"* nxt; "+mapEntry+"* prv;\n"+
        "  explicit "+mapEntry+"() : nxt(nullptr), prv(nullptr) { /*"+fieldsWithIdx.map{case ((fld,tp),i) => fld+" = "+tp.zeroCpp+"; "}.mkString+"*/ }\n"+
        "  explicit "+mapEntry+"("+fieldsWithIdx.map{case ((_,tp),i) => "const "+tp.toCppRefType+" c"+i}.mkString(", ")+") { "+fieldsWithIdx.map{case ((fld,_),i) => fld+" = c"+i+"; "}.mkString+"}\n"+
        "  "+mapEntry+"(const "+mapEntry+"& other) : "+fieldsWithIdx.map{case ((fld,tp),i) => fld+"( other."+fld+" ), "}.mkString+"nxt( nullptr ), prv( nullptr ) {}\n"+
        // "  "+mapEntry+"& operator=(const "+mapEntry+"& other) { "+fieldsWithIdx.map{case ((fld,tp),i) => fld+" = other."+fld+";"}.mkString+" return *this; }\n"+
        // "  "+mapEntry+"& operator=(const "+mapEntry+"&& other) { "+fieldsWithIdx.map{case ((fld,tp),i) => fld+" = "+(if(tp.isBasicCppType) "other."+fld else "std::move(other."+fld+")")+";"}.mkString+" return *this; }\n"+
        allIndices.map{ case (is,unique) =>
        "  FORCE_INLINE "+mapEntry+"& modify"+(if(unique) "" else getIndexId(mapName,is))+"("+is.map{case i => "const "+fields(i)._2.toCppRefType+" c"+i}.mkString(", ")+") { "+is.map{case i => fields(i)._1+" = c"+i+"; "}.mkString+" return *this; }\n"
        }.mkString+
        "  template<class Archive>\n"+
        "  void serialize(Archive& ar, const unsigned int version) const \n"+
        "  {\n"+
        fields.map{case (fld,_) => "    ar << ELEM_SEPARATOR;\n    DBT_SERIALIZATION_NVP(ar, "+fld+");\n"}.mkString+
        "  }\n"+
        "};"

      def genExtractorsAndHashers = allIndices.map{ case (is,unique) =>
        "struct "+mapType+"key"+getIndexId(mapName,is)+"_idxfn {\n"+
        "  FORCE_INLINE static size_t hash(const "+mapEntry+"& e) {\n"+
        "    size_t h = 0;\n"+
        is.map{ isIndex => "    hash_combine(h, e."+fields(isIndex)._1+");\n" }.mkString +
        "    return h;\n"+
        "  }\n"+
        "  FORCE_INLINE static bool equals(const "+mapEntry+"& x, const "+mapEntry+"& y) {\n"+
        "    return "+
        is.map{ isIndex =>
          val fld=fields(isIndex)._1
          cmpFunc(fields(isIndex)._2,OpEq,"x."+fld,"y."+fld,false)
        }.mkString(" && ") + ";\n" +
        "  }\n"+
        "};\n"
      }.mkString("\n")

      def genTypeDefs =
        "typedef MultiHashMap<"+mapEntry+","+mapValueType+","+
        allIndices.map{case (is,unique) => "\n  HashIndex<"+mapEntry+","+mapValueType+","+mapType+"key"+getIndexId(mapName,is)+"_idxfn,"+unique+">"}.mkString(",")+
        "\n> "+mapType+";\n"+
        allIndices.map{ case (is,unique) =>
          "typedef HashIndex<"+mapEntry+","+mapValueType+","+mapType+"key"+getIndexId(mapName,is)+"_idxfn,"+unique+"> HashIndex_"+mapType+"_"+getIndexId(mapName,is)+";\n"
        }.mkString

      genEntryStruct+"\n"+genExtractorsAndHashers+"\n"+genTypeDefs
    }
    def genTempTupleTypes = tempTupleTypes.map{case (name,(ksTp,vsTp)) => 
      val ksTpWithIdx = ksTp.zipWithIndex
      val valVarName = VALUE_NAME
      "struct " + name +" {\n"+
      "  "+ksTpWithIdx.map{case (k,i) => k.toCpp+" _"+(i+1)+"; "}.mkString+(vsTp.toCpp+" "+valVarName+"; "+name+"* nxt; "+name+"* prv;")+"\n"+
      "  explicit "+name+"() : nxt(nullptr), prv(nullptr) { "/*+ksTpWithIdx.map{case (k,i) => "_"+(i+1)+" = "+k.zeroCpp+"; "}.mkString+(valVarName+" = "+vsTp.zeroCpp+";")*/+"}\n"+
      "  explicit "+name+"("+ksTpWithIdx.map{case (k,i) => "const "+k.toCppRefType+" c"+(i+1)+", "}.mkString+(vsTp.toCpp+" c"+valVarName+"="+vsTp.zeroCpp)+") : nxt(nullptr), prv(nullptr) { "+ksTpWithIdx.map{case (_,i) => "_"+(i+1)+" = c"+(i+1)+"; "}.mkString+(valVarName+" = c"+valVarName+";")+"}\n"+
      "  int operator<(const "+name+" &rhs) const { \n"+ksTpWithIdx.map{case (v,i) => "    if(this->_"+(i+1)+"!=rhs._"+(i+1)+") return (this->_"+(i+1)+"<rhs._"+(i+1)+");\n"}.mkString+"    return 0;\n  }\n"+
      "  int operator==(const "+name+" &rhs) const { return ("+ksTpWithIdx.map{case (v,i) => "(this->_"+(i+1)+"==rhs._"+(i+1)+")"}.mkString(" && ")+"); }\n"+
      "  FORCE_INLINE "+name+"& modify("+ksTpWithIdx.map{case (k,i) => "const "+k.toCppRefType+" c"+i+", "}.mkString+vsTp.toCpp+" c"+valVarName+") { "+ksTpWithIdx.map{case (k,i) => "_"+(i+1)+" = c"+i+"; "}.mkString+valVarName+" = c"+valVarName+"; return *this; }\n"+
      "  static bool equals(const "+name+" &x, const "+name+" &y) { return ("+ksTpWithIdx.map{case (v,i) => "(x._"+(i+1)+"==y._"+(i+1)+")"}.mkString(" && ")+"); }\n"+
      "  static long hash(const "+name+" &e) {\n"+
      "    size_t h = 0;\n"+
      ksTpWithIdx.map{ case (v,i) => "    hash_combine(h, e._"+(i+1)+");\n" }.mkString +
      "    return h;\n"+
      "  }\n"+
      "};"
    }

    freshClear
    clearOut

    s0.maps.foreach{m =>
      mapDefsList += (m.name -> m)
    }
    s0.triggers.foreach(_.evt match { //delta relations
      case EvtBatchUpdate(s) =>
        val schema = s0.sources.filter(_.schema.name == s.name)(0).schema
        val deltaRel = schema.deltaSchema
        mapDefsList += (deltaRel -> MapDef(deltaRel,TypeLong,schema.fields,null))
      case _ => //nothing to do
    })
    s0.triggers.foreach{ t=> //local maps
      t.stmts.map{
        case m@MapDef(name,_,_,_) =>
          mapDefsList += (name -> m)
        case _ => //nothing to do
      }
    }
    mapDefs = mapDefsList.toMap
    val ts =
      "/* Trigger functions for table relations */\n"+
      genTableTriggers+
      "\n\n"+
      "/* Trigger functions for stream relations */\n"+
      genStreamTriggers
    val resAcc = helperResultAccessor(s0)
    val ms = s0.queries.filter(q=>(s0.maps.filter(_.name==q.name).size == 0) && (q.keys.size > 0)).map(q=>genMapStructDef(MapDef(q.name,q.tp,q.keys,q.map))).mkString("\n") + // queries`without a map (with -F EXPRESSIVE-TLQS)
            s0.triggers.map(_.evt match { //delta relations
              case EvtBatchUpdate(s) =>
                val schema = s0.sources.filter(_.schema.name == s.name)(0).schema
                val deltaRel = schema.deltaSchema
                genMapStructDef(MapDef(deltaRel,TypeLong,schema.fields,null))+"\n"
              case _ => ""
            }).mkString +
            s0.triggers.flatMap{ t=> //local maps
              t.stmts.filter{
                case MapDef(_,_,_,_) => true
                case _ => false
              }.map{
               case m@MapDef(_,_,_,_) => genMapStructDef(m)+"\n"
               case _ => ""
              }
            }.mkString +
            s0.maps.filter(_.keys.size > 0).map(genMapStructDef(_)+"\n").mkString + // maps
            genTempTupleTypes.mkString("\n")

    "\n/* Definitions of auxiliary maps for storing materialized views. */\n"+
    ms +
    "\n\n"+
    resAcc+
    "/* Type definition providing a way to incrementally maintain the results of the sql program */\n"+
    "struct data_t : tlq_t{\n"+
    "  data_t(): tlq_t()"+getInitializationForDATA_T(s0.maps,s0.queries)+" {\n"+
         ind(constsInit,2)+"\n"+ 
    (if(regexpCacheMap.isEmpty) "" else
    "    /* regex_t init */\n"+
    regexpCacheMap.map{case (regex,preg) => 
    "    if(regcomp(&"+preg+", \""+regex+"\", REG_EXTENDED | REG_NOSUB)){\n"+
    "      cerr << \"Error compiling regular expression: /"+regex+"/\" << endl;\n"+
    "      exit(-1);\n"+
    "    }\n"
    }.mkString)+
    "  }\n"+
    "\n"+
    "  #ifdef DBT_PROFILE\n"+
    "  std::shared_ptr<dbtoaster::statistics::trigger_exec_stats> exec_stats;\n"+
    "  std::shared_ptr<dbtoaster::statistics::trigger_exec_stats> ivc_stats;\n"+
    "  #endif\n"+
    "\n"+
    "  /* Registering relations and trigger functions */\n"+
    "  void register_data(ProgramBase& pb) {\n"+
    "\n"+
         ind(register_maps,2)+
    "\n\n"+
         ind(register_relations,2)+
    "\n\n"+
         ind(register_table_triggers,2)+
    "\n\n"+
         ind(register_stream_triggers,2)+
    "\n\n"+
         ind(init_stats,2)+
    "\n\n"+
    "  }\n"+
    "\n"+
       ind(ts)+
    "\n\n"+
    (if(!isExpressiveTLQSEnabled(s0.queries)) {
    "private:\n"+
    "\n"+
    "  /* Sample entries for avoiding recreation of temporary objects */\n"+
    sampleEntDef+
    (if(regexpCacheMap.isEmpty) "" else
    "  /* regex_t temporary objects */\n"+
    regexpCacheMap.map{case (_,preg) => "  regex_t "+preg+";\n"}.mkString)+
    "\n"+
    "  /* Data structures used for storing materialized views */\n"+
       ind(genIntermediateDataStructureRefs(mapDefsList.map(_._2).toList,s0.queries))+"\n"+
       ind(genTempMapDefs)+"\n"+
       ind(consts)+
    "\n\n"} else "")+
    "};\n"+
    "\n"+
    helper(s0)
  }

  private def helperResultAccessor(s0:System) = {
    def compile_serialization = s0.queries.map{q =>
      "ar << \"\\n\";\n"+
      "const " + q.toCppRefType + " _"+q.name+" = get_"+q.name+"();\n"+
      "dbtoaster::serialize_nvp_tabbed(ar, STRING("+q.name+"), _"+q.name+", \"\\t\");\n"
    }.mkString

    def compile_tlqs = s0.queries.map{ query =>
      "const " + query.toCppRefType + " get_"+query.name+"() const {\n"+
      (query.map match {
        case MapRef(n,_,_) if (n == query.name) => "  return "+query.name+";\n"
        case _ => 
          ctx = Ctx[(Type,String)]()
          ind(
            if(query.keys.length == 0) cpsExpr(query.map, (v:String) => "return "+v+";")+"\n"
            else {
              val nk = query.keys.map(_._1)
              val nkTp = query.keys.map(_._2)
              val mapName = query.name
              val mapType = mapName+"_map"
              val mapEntry = mapName+"_entry"
              val sampleEnt=fresh("se")
              sampleEntDef+=(if(nk.size > 0) "  "+mapEntry+" "+sampleEnt+";\n" else "")
              // "val "+mapName+" = M3Map.make["+tk+","+query.tp.toScala+"]()\n"+
              mapName + ".clear();\n"+
              cpsExpr(query.map, (v:String) =>ADD_TO_MAP_FUNC(query.name)+"("+sampleEnt+".modify("+(nk map rn).mkString(",")+"),"+v+");")+"\n"+
              "return " + mapName + ";"
            }
          )
      })+
      "\n}\n"
    }.mkString

    def compile_tlqs_decls = s0.queries.map{q =>
      q.toCppType + " "+q.name+";\n"
    }.mkString

    "/* Type definition providing a way to access the results of the sql program */\n"+
    "struct tlq_t{\n"+
    "  struct timeval t0,t; long tT,tN,tS;\n"+
    "  tlq_t(): tN(0), tS(0)"+getInitializationForTLQ_T(s0.maps,s0.queries)+" { gettimeofday(&t0,NULL); }\n"+
    "\n"+
    "/* Serialization Code */\n"+
    "  template<class Archive>\n"+
    "  void serialize(Archive& ar, const unsigned int version) const {\n"+
    "\n"+
         ind(compile_serialization,2)+
    "\n\n"+
    "  }\n"+
    "\n"+
    "  /* Functions returning / computing the results of top level queries */\n"+
         ind(compile_tlqs)+
    "\n\n"+
    "protected:\n"+
    "\n"+
    "  /* Data structures used for storing / computing top level queries */\n"+
         ind(compile_tlqs_decls)+
    "\n\n"+
    (if(isExpressiveTLQSEnabled(s0.queries)) {
    "  /* Data structures used for storing materialized views */\n"+
       ind(genIntermediateDataStructureRefs(mapDefsList.map(_._2).toList,s0.queries))+"\n"+
       ind(genTempMapDefs)+"\n"+
       ind(consts)+
    "\n\n"} else "")+
    "};\n"+
    "\n"
  }

  // Helper that contains the main and stream generator
  private def helper(s0:System) = {
    val dataset = "standard" //XXXX
    "/* Type definition providing a way to execute the sql program */\n"+
    "class Program : public ProgramBase\n"+
    "{\n"+
    "  public:\n"+
    "    Program(int argc = 0, char* argv[] = 0) : ProgramBase(argc,argv) {\n"+
    "      data.register_data(*this);\n"+
           ind(streams(s0.sources),3)+"\n\n"+
    "    }\n"+
    "\n"+
    "    /* Imports data for static tables and performs view initialization based on it. */\n"+
    "    void init() {\n"+
    "        //P0_PLACE_HOLDER\n"+
    "        table_multiplexer.init_source(run_opts->batch_size);\n"+
    "        stream_multiplexer.init_source(run_opts->batch_size);\n"+
    "        process_tables();\n"+
    "        data.on_system_ready_event();\n"+
    "        //P2_PLACE_HOLDER\n"+
    "    }\n"+
    "\n"+
    "    /* Saves a snapshot of the data required to obtain the results of top level queries. */\n"+
    "    snapshot_t take_snapshot(){\n"+
    "        tlq_t* d = new tlq_t((tlq_t&)data);\n"+
    "        "+(if(ddbt.Compiler.DEPLOYMENT_STATUS == ddbt.Compiler.DEPLOYMENT_STATUS_RELEASE) "//" else "")+"if (d->tS==0) { "+tc("d->")+" } printf(\"SAMPLE="+dataset+",%ld,%ld,%ld\\n\",d->tT,d->tN,d->tS);\n"+
    "        return snapshot_t( d );\n"+
    "    }\n"+
    "\n"+
    "  protected:\n"+
    "    data_t data;\n"+
    "};\n"+ (if (cls != "Program") {
    "class "+cls+" : public Program\n"+
    "{\n"+
    "  public:\n"+
    "    "+cls+"(int argc = 0, char* argv[] = 0) : Program(argc,argv) {\n"+
    "    }\n"+
    "};\n"
    } else "")
  }

  private def genStream(s:Source): String = {
    val sourceId = fresh("source");
    val sourceSplitVar = sourceId + "_fd"
    val adaptorVar = sourceId+"_adaptor"
    val paramsVar = adaptorVar+"_params"
    val sourceFileVar = sourceId+"_file"
    val in = s.in match { case SourceFile(path) => "std::shared_ptr<dbt_file_source> "+sourceFileVar+"(new dbt_file_source(\""+path+"\","+sourceSplitVar+","+adaptorVar+"));\n" }
    val split = "frame_descriptor "+sourceSplitVar+(s.split match { case SplitLine => "(\"\\n\")" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => "XXXXX("+p+")" })+";\n" //XXXX for SplitPrefix
    
    val schema_param = s.schema.fields.map{case (_,tp) => tp.toString}.mkString(",")
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => {
        val bidsAndAsks = List("bids","asks")
        val orderBookTypesList = bidsAndAsks.filter(s.adaptor.options.contains)
        val orderBookType = orderBookTypesList.size match {
          case 1 => orderBookTypesList(0)
          case 2 => "both"
        }
        val a_opts = s.adaptor.options.filter{case (k,_) => !orderBookTypesList.contains(k)} ++ Map("schema" -> schema_param)
        val numParams = a_opts.size+1
        val a_def = "pair<string,string> "+paramsVar+"[] = { make_pair(\"book\",\""+orderBookType+"\"), "+a_opts.map{case (k,v) => "make_pair(\""+k+"\",\""+v+"\")"}.mkString(", ")+" };\n"+
          "std::shared_ptr<order_books::order_book_adaptor> "+adaptorVar+"(new order_books::order_book_adaptor("+bidsAndAsks.map{ x => {if(s.adaptor.options.contains(x)) "get_relation_id(\""+s.adaptor.options(x)+"\")" else "-1"}+","}.mkString+numParams+","+paramsVar+"));\n"

        a_def
      }      
      case "CSV" => {
        val a_opts = s.adaptor.options ++ Map("schema" -> schema_param)
        val numParams = a_opts.size
        val a_def = "pair<string,string> "+paramsVar+"[] = { "+a_opts.map{case (k,v) => "make_pair(\""+k+"\",\""+v+"\")"}.mkString(", ")+" };\n"+
          "std::shared_ptr<csv_adaptor> "+adaptorVar+"(new csv_adaptor(get_relation_id(\""+s.schema.name+"\"),"+numParams+","+paramsVar+"));\n"

        a_def
      }
    }

    adaptor+split+in+
    "add_source("+sourceFileVar+(if(s.stream) "" else ", true")+");\n"
  }

  override def streams(sources:List[Source]) = {
    def fixOrderbook(ss:List[Source]):List[Source] = { // one source generates BOTH asks and bids events
      val (os,xs) = ss.partition{_.adaptor.name=="ORDERBOOK"}
      val ob = new java.util.HashMap[(Boolean,SourceIn),(Schema,Split,Map[String,String])]()
      os.foreach { case Source(s,sc,in,sp,ad) =>
        val (k,v) = ((s,in),(ad.options-"book") + ((ad.options.getOrElse("book","bids"),sc.name)))
        val p=ob.get(k); if (p==null) ob.put(k,(sc,sp,v)) else ob.put(k,(sc,sp,p._3++v))
      }
      scala.collection.JavaConversions.mapAsScalaMap(ob).toList.map { case ((s,in),(sc,sp,opts)) => Source(s,sc,in,sp,Adaptor("ORDERBOOK",opts)) } ::: xs
    }
    val src = fixOrderbook(sources)
    val ss="\n/* Specifying data sources */\n\n"+src.filter{!_.stream}.map(genStream).mkString("\n")+"\n"+src.filter{_.stream}.map(genStream).mkString("\n")
    ss
  }

  override def pkgWrapper(pkg:String, body:String) = additionalImports()+"\n"+"namespace dbtoaster {\n"+ind(body)+"\n\n}\n"

  def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"

  override def additionalImports():String = "#include \"program_base.hpp\"\n#include \"hpds/KDouble.hpp\"\n#include \"hash.hpp\"\n#include \"mmap/mmap.hpp\"\n#include \"hpds/pstring.hpp\"\n#include \"hpds/pstringops.hpp\"\n#define ELEM_SEPARATOR \"\\n\\t\\t\\t\"\n"
}
