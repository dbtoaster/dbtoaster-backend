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
  def FIND_IN_MAP_FUNC(m:String) = "find_in_"+m
  def SET_IN_MAP_FUNC(m:String) = "set_in_"+m
  def ADD_TO_MAP_FUNC(m:String) = "add_to_"+m
  def ADD_TO_TEMP_MAP_FUNC(k:String,v:String) = "add_to_temp_map<"+k+","+v+">"

  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "boost::fusion::make_tuple("+v+")" else v }
  def tupType(vs:List[String]):String = { val v=vs.mkString(","); if (vs.size>1) "boost::fusion::tuple<"+v+" >" else v }

  override def consts = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "/*const static*/ "+tp.toCpp+" "+n+";\n" }.mkString+"\n" // constant member definition
  def constsInit = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); n+" = "+"U"+f+"("+vs.mkString(",")+");\n" }.mkString+"\n" // constant member initilization

  private val mapDefs = HashMap[String,MapDef]() //mapName => MapDef

  // Create a variable declaration
  //XXXXX TODO
  override def genVar(n:String,tp:Type,ks:List[Type]=Nil) = if (ks==Nil) tp.toCpp+" "+n+" = "+tp.zeroCpp+";\n" else "map<"+tupType(ks.map(_.toCpp))+" ,"+tp.toCpp+"> "+n+";\n"

  def getIndexId(m:String,is:List[Int]):String = getIndexPattern(m,is) //slice(m,is)
  def getIndexPattern(m:String,is:List[Int]):String = (if(is.isEmpty) (0 until mapDefs(m).keys.size).toList else is).mkString
  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  // XXX: am should be a Set instead of a List
  override def cpsExpr(ex:Expr,co:(String,Type)=>(String,Type)=(v:String,t:Type)=>(v,t),am:Option[List[(String,Type)]]=None):(String,Type) = ex match {
    case Ref(n) =>
      val (nn,nt)=rn(n)
      co(nn,nt)
    case Const(tp,v) => tp match { case TypeLong => co(v+"L",tp) case TypeString => co("\""+v+"\"",tp) case _ => co(v,tp) }
    case Exists(e) => cpsExpr(e,(v:String,t:Type)=>co("("+v+" != 0 ? 1L : 0L)",TypeLong))
    case Cmp(l,r,op) => co(cpsExpr(l,(ll:String,llt:Type)=>cpsExpr(r,(rr:String,rrt:Type)=>("("+ll+" "+op+" "+rr+")",TypeLong)))._1,TypeLong)
    case app@Apply(fn1,tp,as1) => {
      val (as, fn) = (fn1 match {
        case "date_part" if as1.head.isInstanceOf[Const] => (as1.tail, as1.head.asInstanceOf[Const].v.toLowerCase+"_part")
        case _ => (as1, fn1)
      })
      if (as.forall(_.isInstanceOf[Const])) co(constApply(app),tp) // hoist constants resulting from function application
      else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String,pt:Type)=>cpsExpr(a,(v:String,vt:Type)=>c0(p+(if (i>0) "," else "(")+v+(if (i==as.size-1) ")" else ""),tp)) }; c("U"+fn,tp) }
    }
    case m@MapRef(n,tp,ks) =>
      val kswt = (ks zip m.tks) //ks with type
      val rt = tp
      val (ko,ki) = kswt.zipWithIndex.partition{case((k,ktp),i)=>ctx.contains(k)}
      if (ki.size==0) co((if (ks.size>0) FIND_IN_MAP_FUNC(n)+"("+n+", "+tup(ks.map(rnv))+")" else n),tp) // all keys are bound
      else {
        val lup0 = fresh("lkup") //lookup
        val lupItr0 = lup0+"_it"
        val lupItrNext0 = "next_"+lupItr0
        val lupEnd0 = lup0+"_end"
        val is = ko.map(_._2)
        val iKeys = ko.map(x=>rnv(x._1._1))
        val (k0,v0)=(fresh("k"),fresh("v"))

        ctx.add(kswt.filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)

        if (!m.isTemp) { // slice or foreach
          //TODO XXX is it always required to create a unique index?
          //If not, we should change here to reuse an exisiting index
          //or create an index if nothing is available
          val patternName = n+"_pat"+getIndexPattern(n,is)
          val mapDef = mapDefs(n)

          //TODO XXX make sure that next pointer is not required (see commented code below)
          ((if (ko.size>0) { //slice
            val idxType = n+"_index"+getIndexId(n,is)
            val idxIterator = idxType+"::iterator"
            slice(n,is)
            "std::pair<"+idxIterator+","+idxIterator+"> "+lup0+" = "+n+".get<"+patternName+">().equal_range("+tup(iKeys)+"); //slice\n"+
            //expanded mode
            // idxIterator+" "+lupItr0+" = "+lup0+".first;\n"+
            // idxIterator+" "+lupEnd0+" = "+lup0+".second;\n"
            //compact mode
            idxIterator+" "+lupItr0+" = "+lup0+".first, "+lupEnd0+" = "+lup0+".second;\n"
          } else { //foreach
            val mapType = n+"_map"
            val idxIterator = mapType+"::iterator"
            //expanded mode
            // idxIterator+" "+lupItr0+" = "+n+".begin(); //foreach\n"+
            // idxIterator+" "+lupEnd0+" = "+n+".end();\n"
            //compact mode
            idxIterator+" "+lupItr0+" = "+n+".begin(), "+lupEnd0+" = "+n+".end(); //foreach\n"
          })+
          // idxIterator+" "+lupItrNext0+" = "+lupItr0+";\n"+
          "while("+lupItr0+"!="+lupEnd0+") {\n"+
          // "  ++"+lupItrNext0+";\n"+
             ki.map{case ((k,ktp),i)=>"  "+ktp+" "+rn(k)+" = (*"+lupItr0+")."+mapDef.keys(i)._1+";\n"}.mkString+
          "  "+tp.toCpp+" "+v0+" = "+"(*"+lupItr0+")."+VALUE_NAME+";\n"+
             ind(co(v0,tp)._1)+
          "\n"+
          // "  "+lupItr0+" = "+lupItrNext0+";\n"+
          "  ++"+lupItr0+";\n"+
          "}\n",rt)
        } else { //only foreach for Temp map
          val mapType = "map<"+tupType(m.tks.map(_.toCpp))+" ,"+tp.toCpp+">"
          val idxIterator = mapType+"::iterator"

          //expanded mode
          // idxIterator+" "+lupItr0+" = "+n+".begin(); //temp foreach\n"+
          // idxIterator+" "+lupEnd0+" = "+n+".end();\n"+
          //compact mode
          (idxIterator+" "+lupItr0+" = "+n+".begin(), "+lupEnd0+" = "+n+".end(); //temp foreach\n"+
          // idxIterator+" "+lupItrNext0+" = "+lupItr0+";\n"+
          "while("+lupItr0+"!="+lupEnd0+") {\n"+
          // "  ++"+lupItrNext0+";\n"+
          "  "+tupType(m.tks.map(_.toCpp))+" "+(if(ks.size==1) rn(ks.head) else k0)+" = "+"(*"+lupItr0+").first;\n"+
          "  "+tp.toCpp+" "+v0+" = "+"(*"+lupItr0+").second;\n"+
             (if(ks.size > 1) ki.map{case ((k,ktp),i)=>"  "+ktp+" "+rn(k)+" = at_c<"+i+">("+k0+");\n"}.mkString else "")+
             ind(co(v0,tp)._1)+
          "\n"+
          // "  "+lupItr0+" = "+lupItrNext0+";\n"+
          "  ++"+lupItr0+";\n"+
          "}\n",rt)
        }
      }
    // "1L" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n :: Nil,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) cpsExpr(e,(v:String,t:Type)=>co(/*"(/*if */"+*/"("+rn(n)+" == "+v+")"/*+" ? 1L : 0L)"*/,TypeLong),am)
      else e match {
        case Ref(n2) => ctx.add(n,(e.tp,rnv(n2))); co("1L",TypeLong) // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ => 
          ctx.add(n,(e.tp,fresh("l")))
          cpsExpr(e,(v:String,t:Type) => {
            val (cov,cot) = co("1L",TypeLong)
            (e.tp.toCpp+" "+rn(n)+" = "+v+";\n"+cov,cot)
          },am)
      }
    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) ) 
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el,er) => //cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"),am),am)
      def mul(vl:String,vr:String) = { // simplifies (vl * vr)
        // extract cond and then branch of "if (c) t else 0"
        // no better way for finding boolean type
        // TODO: add Boolean type
        def cx(s:String):Option[(String,String)] = if (!s.startsWith("(/*if */(")) None else { var d=1; val pInit="(/*if */(".length; var p=pInit; while(d>0) { if (s(p)=='(') d+=1 else if (s(p)==')') d-=1; p+=1; }; Some(s.substring(pInit,p-1),s.substring(p+" ? ".length,s.lastIndexOf(":")-1)) }
        def vx(vl:String,vr:String) = if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"
        //pulling out the conditionals from a multiplication
        (cx(vl),cx(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => "(/*if */("+cl+" && "+cr+") ? "+vx(tl,tr)+" : "+ex.tp.zeroCpp+")"
          case (Some((cl,tl)),_) => "(/*if */("+cl+") ? "+vx(tl,vr)+" : "+ex.tp.zeroCpp+")"
          case (_,Some((cr,tr))) => "(/*if */("+cr+") ? "+vx(vl,tr)+" : "+ex.tp.zeroCpp+")"
          case _ => vx(vl,vr)
        }
      }
      cpsExpr(el,(vl:String,vlt:Type)=>cpsExpr(er,(vr:String,vrt:Type)=>co(mul(vl,vr),Type.tpMul(vlt,vrt)),am),am)
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
        cpsExpr(el,(vl:String,vlt:Type) => {
          ctx.load(cur)
          cpsExpr(er,(vr:String,vrt:Type) => {
            ctx.load(cur)
            co("("+vl+" + "+vr+")",Type.tpAdd(vlt,vrt))
          },am)
        },am)
      }
      else am match {
        case Some(t) if t.toSet==a.agg.toSet => 
          val cur=ctx.save
          val (s1,_)=cpsExpr(el,co,am)
          ctx.load(cur)
          val (s2,rt)=cpsExpr(er,co,am)
          ctx.load(cur)
          (s1+s2,rt)
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String,t:Type)=>(ADD_TO_TEMP_MAP_FUNC(tupType(a.agg.map(_._2.toCpp)),ex.tp.toCpp)+"("+a0+", "+tup(ks map rnv)+","+v+");\n",TypeUnit),tmp)._1
          ctx.load(cur)
          val s2 = cpsExpr(er,(v:String,t:Type)=>(ADD_TO_TEMP_MAP_FUNC(tupType(a.agg.map(_._2.toCpp)),ex.tp.toCpp)+"("+a0+", "+tup(ks map rnv)+","+v+");\n",TypeUnit),tmp)._1
          ctx.load(cur)
          val (r,rt) = cpsExpr(mapRef(a0,ex.tp,a.agg),co)
          (genVar(a0,ex.tp,a.agg.map(_._2))+s1+s2+r,rt)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) {
        val a0=fresh("agg")
        (genVar(a0,ex.tp)+cpsExpr(e,(v:String,t:Type)=>(a0+" += "+v+";\n",TypeUnit))._1+co(a0,a.tp)._1,a.tp)
      }
      else am match {
        case Some(t) if t.toSet==aks.toSet => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = genVar(a0,e.tp,aks.map(_._2))+"\n"+
            cpsExpr(e,(v:String,t:Type)=>(ADD_TO_TEMP_MAP_FUNC(tupType(aks.map(_._2.toCpp)),e.tp.toCpp)+"("+a0+", "+tup(aks.map(x=>rnv(x._1)))+","+v+");\n",TypeUnit),tmp);
          ctx.load(cur)
          (s1+cpsExpr(mapRef(a0,e.tp,aks),co),a.tp)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  override def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) => val (fop,sop)=op match { case OpAdd => (ADD_TO_MAP_FUNC(m.name),"+=") case OpSet => (ADD_TO_MAP_FUNC(m.name),"=") }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear();\n" else "" }
      val init = oi match {
        case Some(ie) => 
          ctx.load()
          cpsExpr(ie,(i:String,it:Type) =>
          (if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
          else "if ("+FIND_IN_MAP_FUNC(m.name)+"("+m.name+", "+tup(m.keys map rnv)+")==0) "+SET_IN_MAP_FUNC(m.name)+"("+m.name+", "+tup(m.keys map rnv)+","+i+");\n",TypeUnit))
        case None => ""
      }
      ctx.load()
      clear+init+cpsExpr(e,(v:String,t:Type) => ((if (m.keys.size==0) m.name+" "+sop+" "+v else { fop+"("+m.name+", "+tup(m.keys map rnv)+","+v+")"})+";\n",TypeUnit),Some(m.keys zip m.tks))
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  override def genTrigger(t:Trigger):String = {
    val (n,as, xActCounter) = t.evt match {
      case EvtReady => ("system_ready_event",Nil,"")
      case EvtAdd(Schema(n,cs)) => ("insert_"+n,cs,"++tN;")
      case EvtDel(Schema(n,cs)) => ("delete_"+n,cs,"++tN;")
    }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap)
    val preBody="BEGIN_TRIGGER(exec_stats,\""+n+"\")\n"+
                "BEGIN_TRIGGER(ivc_stats,\""+n+"\")\n"+
                "{  "+xActCounter+"\n"
    val body=ind(t.stmts.map(genStmt).mkString)
    val pstBody="\n}\n"+
                "END_TRIGGER(exec_stats,\""+n+"\")\n"+
                "END_TRIGGER(ivc_stats,\""+n+"\")\n"
    ctx=null

    "void on_"+n+"("+as.map(a=>a._2.toCpp+" "+a._1).mkString(", ")+") {\n"+ind(preBody+body+pstBody)+"\n}"
  }

  override def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  override def genMap(m:MapDef):String = {
    // if (m.keys.size==0) genVar(m.name,m.tp).trim
    // else {
    //   val tk = tup(m.keys.map(x=>x._2.toCpp))
    //   val s = sx.getOrElse(m.name,List[List[Int]]())
    //   "val "+m.name+" = M3Map.make["+tk+","+m.tp.toCpp+"]("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+");"
    // }
    ""
  }

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = map+".add("+keyNamesConcat+",1L)"

  // Generate (1:stream events handling, 2:table loading, 3:global constants declaration)
  override def genInternals(s0:System,nextSkip:String="context.become(receive_skip)") : (String,String,String) = {
    // XXX: reduce as much as possible the overhead here to decode data, use Decoder's internals and inline the SourceMux here
    def ev(s:Schema,short:Boolean=true):(String,String,List[(String,Type)]) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      ("List("+fs.map{case(s,t)=>s.toLowerCase+":"+t.toCpp}.mkString(",")+")","("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")",fs)
    }
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val skip = "if (t1>0 && (tN&"+(step-1)+")==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; "+nextSkip+" } else tN+=1 } else tN+=1; "
    val str = s0.triggers.map(_.evt match {
      case EvtAdd(s) => val (i,o,pl)=ev(s); "case TupleEvent(_,TupleInsert,\""+s.name+"\","+i+") => "+skip+"onAdd"+s.name+o+"\n"
      case EvtDel(s) => val (i,o,pl)=ev(s); "case TupleEvent(_,TupleDelete,\""+s.name+"\","+i+") => "+skip+"onDel"+s.name+o+"\n"
      case _ => ""
    }).mkString
    //TODO XXX tables should be processed separately
    val ld0 = ""//s0.sources.filter{s=> !s.stream}.map { s=> val (in,ad,sp)=genStream(s); val (i,o,pl)=ev(s.schema)
      // "SourceMux(Seq(("+in+",Decoder({ case TupleEvent(TupleInsert,_,"+i+")=>"+genInitializationFor(s.schema.name,pl,o)+" },"+ad+","+sp+")))).read;" }.mkString("\n");
    (str,ld0,consts)
  }

  override def genLMS(s0:System):(String,String,String,String) = (null,null,null,null)

  override def toMapFunction(q: Query) = q.name+".toMap"
  override def clearOut = {}
  override def onEndStream = ""

  override def apply(s0:System):String = {
    def register_maps = s0.maps.map{m=>"pb.add_map<"+m.toCppType+">( \""+m.name+"\", "+m.name+" );\n"}.mkString

    def register_relations = s0.sources.map{s => "pb.add_relation(\""+s.schema.name+"\"" + (if(s.stream) "" else ", true") + ");\n"}.mkString

    def register_table_triggers = s0.sources.filter(!_.stream).map{ s => 
      "pb.add_trigger(\""+s.schema.name+"\", insert_tuple, boost::bind(&data_t::unwrap_insert_"+s.schema.name+", this, ::boost::lambda::_1));\n"
    }.mkString

    def register_stream_triggers = s0.triggers.filter(_.evt != EvtReady).map{ t=>t.evt match {
        case EvtAdd(Schema(n,_)) => "pb.add_trigger(\""+n+"\", insert_tuple, boost::bind(&data_t::unwrap_insert_"+n+", this, ::boost::lambda::_1));\n"
        case EvtDel(Schema(n,_)) => "pb.add_trigger(\""+n+"\", delete_tuple, boost::bind(&data_t::unwrap_delete_"+n+", this, ::boost::lambda::_1));\n"
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

    def genTmpDataStructureRefs = s0.maps.filter{m=>s0.queries.filter(_.name==m.name).size == 0}.map{m=>m.toCppType+" "+m.name+";\n"}.mkString

    def genTableTriggers = s0.sources.filter(!_.stream).map{ s =>
      val name = s.schema.name
      val fields = s.schema.fields
      "void on_insert_"+name+"("+fields.map{case (fld,tp) => tp.toCpp+" "+fld }.mkString(", ")+") {\n"+
      "  "+name+"_entry e("+fields.map{case (fld,_) => fld }.mkString(", ")+", 1);\n"+
      "  pair<"+name+"_map::iterator,bool> ret = "+name+".insert(e);\n"+
      "  if( !ret.second ) "+name+".modify( ret.first, boost::lambda::bind(&"+name+"_entry::__av, boost::lambda::_1) = ret.first->__av+1 );\n"+
      "}\n"+
      generateUnwrapFunction(EvtAdd(s.schema))
    }.mkString

    def genStreamTriggers = s0.triggers.map(t =>
      genTrigger(t)+"\n"+
      (if(t.evt != EvtReady) generateUnwrapFunction(t.evt) else "")
    ).mkString

    def generateUnwrapFunction(evt:EvtTrigger) = {
      val (op,name,fields) = evt match {
        case EvtAdd(Schema(n,cs)) => ("insert",n,cs)
        case EvtDel(Schema(n,cs)) => ("delete",n,cs)
        case _ => sys.error("Unsupported trigger event "+evt)
      }
      "void unwrap_"+op+"_"+name+"(const event_args_t& ea) {\n"+
      "  on_"+op+"_"+name+"("+fields.zipWithIndex.map{ case ((_,tp),i) => "any_cast<"+tp.toCpp+">(ea["+i+"])"}.mkString(", ")+");\n"+
      "}\n\n"
    }

    def genMapStructDef(m:MapDef) = {
      val mapName = m.name
      val mapType = m.name+"_map"
      val mapEntry = mapName+"_entry"
      val mapKeyType = tupType(m.keys.map{_._2.toCpp})
      val mapValueType = m.tp.toCpp
      val fields = m.keys ++ List(VALUE_NAME -> m.tp)
      val fieldsWithIdx = fields.zipWithIndex
      val indices = sx.getOrElse(m.name,List[List[Int]]())
      //TODO XXX is it always required to create a unique index?
      val allIndices = ((0 until m.keys.size).toList -> true /*unique*/) :: indices.map(is => (is -> false /*non_unique*/))
      val multiKeyIndices = allIndices.filter{case (is,_) => is.size > 1}

      def genEntryStruct = 
        "struct "+mapEntry+" {\n"+
        "  "+fields.map{case (fld,tp) => tp.toCpp+" "+fld+"; "}.mkString+"\n"+
        "  "+mapEntry+"("+fieldsWithIdx.map{case ((_,tp),i) => tp.toCpp+" c"+i}.mkString(", ")+") {"+fieldsWithIdx.map{case ((fld,_),i) => fld+" = c"+i+"; "}.mkString+"}\n"+
        "  "+mapEntry+"(const std::pair<const "+mapKeyType+" , "+mapValueType+">& p) { "+(if(m.keys.size == 1) m.keys(0)._1+" = p.first; " else m.keys.zipWithIndex.map{case ((fld,_),i) => fld+" = at_c<"+i+">(p.first); "}.mkString)+VALUE_NAME+" = p.second; }\n"+
        (if(m.keys.size > 1) "  "+mapEntry+"(const "+mapKeyType+"& k ,  const "+mapValueType+"& v) { "+(if(m.keys.size == 1) m.keys(0)._1+" = k; " else m.keys.zipWithIndex.map{case ((fld,_),i) => fld+" = at_c<"+i+">(k); "}.mkString)+VALUE_NAME+" = v; }\n" else "")+
        "  operator const std::pair<const "+mapKeyType+" , "+mapValueType+">() const { return std::make_pair("+tup(m.keys.map{case (fld,_) => fld})+", "+VALUE_NAME+"); }\n"+
        "  template<class Archive>\n"+
        "  void serialize(Archive& ar, const unsigned int version)\n"+
        "  {\n"+
        fields.map{case (fld,_) => "    ar & BOOST_SERIALIZATION_NVP("+fld+");\n"}.mkString+
        "  }\n"+
        "};"
      
      def genPatternStructs = 
        indices.map{is => "struct "+mapName+"_pat"+getIndexPattern(mapName,is)+" {};"}.mkString("\n")

      def genExtractorsAndHashers = multiKeyIndices.map{ case (is,unique) =>
        "struct "+mapType+"key"+getIndexId(mapName,is)+"_extractor {\n"+
        "  typedef "+tupType(is.map{ isIndex => fields(isIndex)._2.toCpp})+"  result_type;\n"+
        "  result_type operator()(const "+mapEntry+"& e) const {\n"+
        "    return "+tup(is.map{ isIndex => "e."+fields(isIndex)._1})+";\n"+
        "  }\n"+
        "};\n"+
        //TODO XXX we can implement a better hasher, e.g. using murmur hash
        "struct "+mapType+"key"+getIndexId(mapName,is)+"_hasher {\n"+
        "  size_t operator()(const "+mapEntry+"& e) const {\n"+
        "    size_t seed = 0;\n"+
        is.map{ isIndex => "    boost::hash_combine(seed, e."+fields(isIndex)._1+");\n" }.mkString +
        "    return seed;\n"+
        "  }\n"+
        "  size_t operator()("+tupType(is.map{ isIndex => fields(isIndex)._2.toCpp})+"  k) const {\n"+
        "    return boost::fusion::fold(k, 0, fold_hash());\n"+
        "  }\n"+
        "};"
      }.mkString("\n")

      def genTypeDefs =
        "typedef multi_index_container<"+mapEntry+", indexed_by<\n"+
        allIndices.map{case (is,unique) => "  hashed_"+(if(unique) "unique<" else "non_unique<tag<"+mapName+"_pat"+getIndexPattern(mapName,is)+">, ")+(if(is.size > 1) mapType+"key"+getIndexId(mapName,is)+"_extractor,"+mapType+"key"+getIndexId(mapName,is)+"_hasher" else "member<"+mapEntry+","+fields(is(0))._2.toCpp+",&"+mapEntry+"::"+fields(is(0))._1+"> ")+">"}.mkString(",\n")+"\n"+
        " > > "+mapType+";\n"+
        indices.map{is => "typedef "+mapType+"::index<"+mapName+"_pat"+getIndexPattern(mapName,is)+">::type "+mapName+"_index"+getIndexId(mapName,is)+";"}.mkString("\n")

      def genHelperFunctions =
        mapValueType+" "+FIND_IN_MAP_FUNC(mapName)+"(const "+mapType+"& m, const "+mapKeyType+"& k) {\n"+
        "  "+mapValueType+" res;\n"+ 
        "  "+mapType+"::iterator lkup = m.find(k);\n"+
        "  if (lkup!=m.end()) res = (*lkup)."+VALUE_NAME+"; else res = "+m.tp.zeroCpp+";\n"+
        "  return res;\n"+
        "}\n"+
        "void "+SET_IN_MAP_FUNC(mapName)+"("+mapType+"& m, const "+mapKeyType+"& k, const "+mapValueType+"& v) {\n"+
        "  "+mapType+"::iterator lkup = m.find(k), end = m.end();\n"+
        "  if (v == "+m.tp.zeroCpp+") { if(lkup != end) m.erase(lkup); /*else \"nothing should be done\"*/ }\n"+
        "  else if(/*v != "+m.tp.zeroCpp+" &&*/ lkup != end) m.modify(lkup,boost::lambda::bind(&"+mapEntry+"::__av, boost::lambda::_1) = v);\n"+
        "  else /*if(v != "+m.tp.zeroCpp+" && lkup == end)*/ { "+mapEntry+" ent(k,v); m.insert(ent); }\n"+
        "}\n"+
        "void "+ADD_TO_MAP_FUNC(mapName)+"("+mapType+"& m, const "+mapKeyType+"& k, const "+mapValueType+"& v) {\n"+
        "  if (v != "+m.tp.zeroCpp+") {\n"+
        "    "+mapType+"::iterator lkup = m.find(k), end = m.end();\n"+
        "    if(lkup != end) { "+mapValueType+" newV = (v+(*lkup)."+VALUE_NAME+"); m.modify(lkup,boost::lambda::bind(&"+mapEntry+"::__av, boost::lambda::_1) = newV); }\n"+
        "    else { "+mapEntry+" ent(k,v); m.insert(ent); }\n"+
        "  }\n"+
        "}"
      genEntryStruct+"\n"+genPatternStructs+"\n"+genExtractorsAndHashers+"\n"+genTypeDefs+"\n"+genHelperFunctions
    }

    // val (lms,strLMS,ld0LMS,gcLMS) = genLMS(s0)
    // val body = if (lms!=null) lms else {
    //   val ts = s0.triggers.map(genTrigger).mkString("\n\n") // triggers (need to be generated before maps)
    //   val ms = s0.maps.map(genMap).mkString("\n") // maps
    //   ms+"\n\n"+ts
    // }
    // val (str,ld0,gc) = if(lms!=null) (strLMS,ld0LMS,gcLMS) else genInternals(s0)
    // val ld = if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else "" // optional preloading of static tables content
    // val snap=onEndStream+" sender ! (StreamStat(t1-t0,tN,tS),List("+s0.queries.map{q=>(if (s0.mapType(q.map.name)._1.size>0) toMapFunction(q) else q.name)}.mkString(",")+"))"
    

    // "class "+cls+" extends Actor {\n"+ind(
    // "import ddbt.lib.Messages._\n"+
    // "import ddbt.lib.Functions._\n\n"+body+"\n\n"+
    // "var t0=0L; var t1=0L; var tN=0L; var tS=0L\n"+
    // "def receive_skip:Receive = { case EndOfStream | GetSnapshot(_) => "+snap+" case _ => tS+=1 }\n"+
    // "def receive = {\n"+ind(str+
    //   "case StreamInit(timeout) =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime; if (timeout>0) t1=t0+timeout*1000000L\n"+
    //   "case EndOfStream | GetSnapshot(_) => t1=System.nanoTime; "+snap
    // )+"\n}\n"+gc+ld)+"\n"+"}\n"+
    freshClear
    clearOut

    s0.maps.foreach{m => mapDefs += (m.name -> m)}

    val ts =
      "/* Trigger functions for table relations */\n"+
      genTableTriggers+
      "\n\n"+
      "/* Trigger functions for stream relations */\n"+
      genStreamTriggers
    val ms = s0.maps.filter(_.keys.size > 0).map(genMapStructDef).mkString("\n") // maps

    "\n/* Definitions of auxiliary maps for storing materialized views. */\n"+
    ms +
    "\n\n"+
    helperResultAccessor(s0)+
    "/* Type definition providing a way to incrementally maintain the results of the sql program */\n"+
    "struct data_t : tlq_t{\n"+
    "  data_t(): tlq_t()"+{ s0.maps.filter{m=>(s0.queries.filter(_.name==m.name).size == 0) && (m.keys.size == 0)}.map{m=>", "+m.name+"(" + m.tp.zeroCpp + ")"}.mkString }+" {\n"+
         ind(constsInit,2)+"\n"+
    "  }\n"+
    "\n"+
    "  #ifdef DBT_PROFILE\n"+
    "  boost::shared_ptr<dbtoaster::statistics::trigger_exec_stats> exec_stats;\n"+
    "  boost::shared_ptr<dbtoaster::statistics::trigger_exec_stats> ivc_stats;\n"+
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
    "private:\n"+
    "\n"+
    "  /* Data structures used for storing materialized views */\n"+
       ind(genTmpDataStructureRefs)+"\n"+
       ind(consts)+
    "\n\n"+
    "};\n"+
    "\n"+
    helper(s0)
  }

  private def helperResultAccessor(s0:System) = {
    def compile_serialization = s0.queries.map{q =>
      q.toCppRefType + " _"+q.name+" = get_"+q.name+"();\n"+
      "ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE("+q.name+"), _"+q.name+");\n"
    }.mkString

    def compile_tlqs = s0.queries.map{q =>
      q.toCppRefType + " get_"+q.name+"(){\n"+
      "  return "+q.name+";\n"+
      "}\n"
    }.mkString

    def compile_tlqs_decls = s0.queries.map{q =>
      q.toCppType + " "+q.name+";\n"
    }.mkString

    "/* Type definition providing a way to access the results of the sql program */\n"+
    "struct tlq_t{\n"+
    "  struct timeval t0,t; long tT,tN,tS;\n"+
    "  tlq_t(): "+s0.maps.filter{m=>(s0.queries.filter(_.name==m.name).size != 0) && (m.keys.size == 0)}.map{m=>m.name+"(" + m.tp.zeroCpp + "), "}.mkString+"tN(0), tS(0) { gettimeofday(&t0,NULL); }\n"+
    "\n"+
    "/* Serialization Code */\n"+
    "  template<class Archive>\n"+
    "  void serialize(Archive& ar, const unsigned int version) {\n"+
    "\n"+
         ind(compile_serialization,2)+
    "\n\n"+
    "  }\n"+
    "\n"+
    "  /* Functions returning / computing the results of top level queries */\n"+
         ind(compile_tlqs,2)+
    "\n\n"+
    "protected:\n"+
    "\n"+
    "  /* Data structures used for storing / computing top level queries */\n"+
         ind(compile_tlqs_decls,2)+
    "\n\n"+
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
    "        table_multiplexer.init_source();\n"+
    "        stream_multiplexer.init_source();\n"+
    "        process_tables();\n"+
    "        data.on_system_ready_event();\n"+
    "        //P2_PLACE_HOLDER\n"+
    "    }\n"+
    "\n"+
    "    /* Saves a snapshot of the data required to obtain the results of top level queries. */\n"+
    "    snapshot_t take_snapshot(){ tlq_t d=(tlq_t&)data; if (d.tS==0) { "+tc("d.")+" } printf(\"SAMPLE="+dataset+",%ld,%ld,%ld\\n\",d.tT,d.tN,d.tS);\n"+
    "        return snapshot_t( new tlq_t((tlq_t&)data) );\n"+
    "    }\n"+
    "\n"+
    "  protected:\n"+
    "    data_t data;\n"+
    "};\n"
  }

  private def genStream(s:Source): String = {
    val sourceId = fresh("source");
    val sourceSplitVar = sourceId + "_fd"
    val adaptorVar = sourceId+"_adaptor"
    val paramsVar = adaptorVar+"_params"
    val sourceFileVar = sourceId+"_file"
    val in = s.in match { case SourceFile(path) => "boost::shared_ptr<dbt_file_source> "+sourceFileVar+"(new dbt_file_source(\""+path+"\","+sourceSplitVar+","+adaptorVar+"));\n" }
    val split = "frame_descriptor "+sourceSplitVar+(s.split match { case SplitLine => "(\"\\n\")" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => "XXXXX("+p+")" })+";\n" //XXXX for SplitPrefix
    
    val schema_param = s.schema.fields.map{case (_,tp) => tp.toCpp}.mkString(",")
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
          "boost::shared_ptr<order_books::order_book_adaptor> "+adaptorVar+"(new order_books::order_book_adaptor("+bidsAndAsks.map{ x => {if(s.adaptor.options.contains(x)) "get_relation_id(\""+s.adaptor.options(x)+"\")" else "-1"}+","}.mkString+numParams+","+paramsVar+"));\n"

        a_def
      }      
      case "CSV" => {
        val a_opts = s.adaptor.options ++ Map("schema" -> schema_param)
        val numParams = a_opts.size
        val a_def = "pair<string,string> "+paramsVar+"[] = { "+a_opts.map{case (k,v) => "make_pair(\""+k+"\",\""+v+"\")"}.mkString(", ")+" };\n"+
          "boost::shared_ptr<csv_adaptor> "+adaptorVar+"(new csv_adaptor(get_relation_id(\""+s.schema.name+"\"),"+numParams+","+paramsVar+"));\n"

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

  override def pkgWrapper(pkg:String, body:String) = "#include \"program_base.hpp\"\n"+additionalImports()+"\n"+"namespace dbtoaster {\n"+ind(body)+"\n\n}\n"

    // "package "+pkg+"\nimport ddbt.lib._\n"+additionalImports()+"\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    // "object "+cls+" {\n"+ind("import Helper._\n"+
    // "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long)=>run["+cls+"]("+streams(s0.sources)+",p,t),f)\n\n"+
    // "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    // ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    // "\n})")+"\n}")+"\n}\n\n"
  def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"

  override def additionalImports():String = ""
}
