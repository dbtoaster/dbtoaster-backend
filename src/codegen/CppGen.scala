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

  private val helperFuncUsage = HashMap[(String,String),Int]()
  def FIND_IN_MAP_FUNC(m:String) = { helperFuncUsage.update(("FIND_IN_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("FIND_IN_MAP_FUNC" -> m),0)+1); "find_in_"+m }
  def SET_IN_MAP_FUNC(m:String) = { helperFuncUsage.update(("SET_IN_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("SET_IN_MAP_FUNC" -> m),0)+1); "set_in_"+m }
  def ADD_TO_MAP_FUNC(m:String) = { helperFuncUsage.update(("ADD_TO_MAP_FUNC" -> m),helperFuncUsage.getOrElse(("ADD_TO_MAP_FUNC" -> m),0)+1); "add_to_"+m }
  def ADD_TO_TEMP_MAP_FUNC(ksTp:List[Type],vsTp:Type,m:String,ks:List[String],vs:String) = {
    val sampleTempEnt=fresh("st")
    sampleEntDef+="  "+tupType(ksTp, vsTp)+" "+sampleTempEnt+";\n"
    "add_to_temp_map"+/*"<"+tupType(ksTp, vsTp)+">"+*/"("+m+", "+sampleTempEnt+".modify"+tup(ks map rn, vs)+");\n"
  }

  val tempTupleTypes = HashMap[String,(List[Type],Type)]()
  def tup(ks:List[String],vs:String) = "("+ks.mkString(",")+","+vs+")"
  def tupType(ksTp:List[Type], vsTp:Type):String = { val tupleTp="tuple"+(ksTp.size+1)+"_"+ksTp.map(_.simpleName).mkString+"_"+vsTp.simpleName; tempTupleTypes.update(tupleTp,(ksTp, vsTp)); tupleTp }

  override def consts = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "/*const static*/ "+tp.toCpp+" "+n+";\n" }.mkString+"\n" // constant member definition
  def constsInit = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); n+" = "+"U"+f+"("+vs.mkString(",")+");\n" }.mkString+"\n" // constant member initilization

  //Sample entry definitions are accumulated in this variable
  var sampleEntDef = ""

  private val mapDefs = HashMap[String,MapDef]() //mapName => MapDef
  private val tmpMapDefs = HashMap[String,String]() //tmp mapName => MapDef string

  // Create a variable declaration
  //XXXXX TODO
  override def genVar(n:String,vsTp:Type,ksTp:List[Type]) = if (ksTp==Nil) vsTp.toCpp+" "+n+" = "+vsTp.zeroCpp+";\n" else { tmpMapDefs += (n -> tupType(ksTp,vsTp)); n+".clear();\n" }

  def getIndexId(m:String,is:List[Int]):String = getIndexPattern(m,is) //slice(m,is)
  def getIndexPattern(m:String,is:List[Int]):String = (if(is.isEmpty) (0 until mapDefs(m).keys.size).toList else is).mkString
  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match { // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Exists(e) => cpsExpr(e,(v:String)=>co("("+v+" != 0 ? 1L : 0L)"))
    case Cmp(l,r,op) => co(cpsExpr(l,(ll:String)=>cpsExpr(r,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case app@Apply(fn1,tp,as1) => {
      val (as, fn) = (fn1 match {
        case "date_part" if as1.head.isInstanceOf[Const] => (as1.tail, as1.head.asInstanceOf[Const].v.toLowerCase+"_part")
        case _ => (as1, fn1)
      })
      applyFunc(co,fn,tp,as)
    }
    case m@MapRef(n,tp,ks) =>
      val kswt = (ks zip m.tks) //ks with type
      val (ko,ki) = kswt.zipWithIndex.partition{case((k,ktp),i)=>ctx.contains(k)}
      val mapName = m.name
      val mapType = mapName+"_map"
      val mapEntry = mapName+"_entry"
      if (ki.size==0) {
        val sampleEnt=fresh("se")
        sampleEntDef+=(if(ks.size > 0) "  "+mapEntry+" "+sampleEnt+";\n" else "")
        co((if (ks.size>0) FIND_IN_MAP_FUNC(n)+"("+n+", "+sampleEnt+".modify("+(ks map rn).mkString(",")+"))" else n)) // all keys are bound
      } else {
        val lup0 = fresh("lkup") //lookup
        val lupItr0 = lup0+"_it"
        val lupItrNext0 = "next_"+lupItr0
        val lupEnd0 = lup0+"_end"
        val is = ko.map(_._2)
        val iKeys = ko.map(x=>rn(x._1._1))
        val iKeysTp = ko.map(x=>x._1._2)
        val (k0,v0,e0)=(fresh("k"),fresh("v"),fresh("e"))

        ctx.add(kswt.filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)

        if (!m.isTemp) { // slice or foreach
          //TODO XXX is it always required to create a unique index?
          //If not, we should change here to reuse an exisiting index
          //or create an index if nothing is available
          // val patternName = n+"_pat"+getIndexPattern(n,is)
          val mapDef = mapDefs(n)

          //TODO XXX make sure that next pointer is not required (see commented code below)
          // (if (ko.size>0) { //slice
          //   val idxType = n+"_index"+getIndexId(n,is)
          //   val idxIterator = idxType+"::iterator"
          //   "std::pair<"+idxIterator+","+idxIterator+"> "+lup0+" = "+n+".get<"+patternName+">().equal_range("+(if (is.size > 1) sampleEnt+".modify"+getIndexId(mapName,is)+"("+iKeys.mkString(", ")+")" else tup(iKeys, iKeysTp))+"); //slice\n"+
          //   //expanded mode
          //   // idxIterator+" "+lupItr0+" = "+lup0+".first;\n"+
          //   // idxIterator+" "+lupEnd0+" = "+lup0+".second;\n"
          //   //compact mode
          //   idxIterator+" "+lupItr0+" = "+lup0+".first, "+lupEnd0+" = "+lup0+".second;\n"
          // } else { //foreach
          //   val mapType = n+"_map"
          //   val idxIterator = mapType+"::iterator"
          //   //expanded mode
          //   // idxIterator+" "+lupItr0+" = "+n+".begin(); //foreach\n"+
          //   // idxIterator+" "+lupEnd0+" = "+n+".end();\n"
          //   //compact mode
          //   idxIterator+" "+lupItr0+" = "+n+".begin(), "+lupEnd0+" = "+n+".end(); //foreach\n"
          // })+
          // // idxIterator+" "+lupItrNext0+" = "+lupItr0+";\n"+
          // "while("+lupItr0+"!="+lupEnd0+") {\n"+
          // // "  ++"+lupItrNext0+";\n"+
          //    ki.map{case ((k,ktp),i)=>"  "+ktp+" "+rn(k)+" = (*"+lupItr0+")."+mapDef.keys(i)._1+";\n"}.mkString+
          // "  "+tp.toCpp+" "+v0+" = "+"(*"+lupItr0+")."+VALUE_NAME+";\n"+
          //    ind(co(v0))+
          // "\n"+
          // // "  "+lupItr0+" = "+lupItrNext0+";\n"+
          // "  ++"+lupItr0+";\n"+
          // "}\n"


          val n0= fresh("n")
          val idx0= fresh("i")
          val mapType = n+"_map"
          val idxName = "HashIndex_"+mapType+"_"+getIndexId(n,is)
          val idxFn = mapType+"key"+getIndexId(n,is)+"_idxfn"
          val body = ki.map{case ((k,ktp),i)=>ktp+" "+rn(k)+" = "+e0+"->"+mapDef.keys(i)._1+";\n"}.mkString+
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
            "    do {\n"+
                   ind(body,3)+"\n"+
            "    } while(("+n0+"="+n0+"->next) && ("+e0+"="+n0+"->obj) && ("+h0+" == "+n0+"->hash) && "+idxFn+"::equals("+sampleEnt+", *"+n0+"->obj));\n"+
            "    break;\n"+
            "  } while (("+n0+"="+n0+"->next));\n"+
            "}\n"
            // n+".index["+idxIndex+"]->slice("+sampleEnt+".modify"+getIndexId(mapName,is)+"("+iKeys.mkString(", ")+"),[&] (const "+mapEntry+"& "+e0+") {\n"+
            //   ind(body)+"\n"+
            // "});\n"
          } else { //foreach
            val b0= fresh("b")
            "{ //foreach\n"+
            "  "+mapEntry+"* "+e0+" = "+n+".head;\n"+
            "  while("+e0+"){\n"+
                 ind(body,2)+"\n"+
            "    "+e0+" = "+e0+"->nxt;\n"+
            "  }\n"+
            "}\n"
            // n+".index[0]->foreach([&] (const "+mapEntry+"& "+e0+") {\n"+
            //   ind(body)+"\n"+
            // "});\n"
          }
        } else { //only foreach for Temp map
          // val idxIterator = "map<"+tupType(m.tks,m.tp)+","+tp.toCpp+">::iterator"
          // //expanded mode
          // // idxIterator+" "+lupItr0+" = "+n+".begin(); //temp foreach\n"+
          // // idxIterator+" "+lupEnd0+" = "+n+".end();\n"+
          // //compact mode
          // idxIterator+" "+lupItr0+" = "+n+".begin(), "+lupEnd0+" = "+n+".end(); //temp foreach\n"+
          // // idxIterator+" "+lupItrNext0+" = "+lupItr0+";\n"+
          // "while("+lupItr0+"!="+lupEnd0+") {\n"+
          // // "  ++"+lupItrNext0+";\n"+
          // "  "+tupType(m.tks,m.tp)+" "+(if(ks.size==1) rn(ks.head) else k0)+" = "+"(*"+lupItr0+").first;\n"+
          // "  "+tp.toCpp+" "+v0+" = "+"(*"+lupItr0+").second;\n"+
          //    (if(ks.size > 1) ki.map{case ((k,ktp),i)=>"  "+ktp+" "+rn(k)+" = "+k0+"._"+(i+1)+";\n"}.mkString else "")+
          //    ind(co(v0))+
          // "\n"+
          // // "  "+lupItr0+" = "+lupItrNext0+";\n"+
          // "  ++"+lupItr0+";\n"+
          // "}\n"


          "{ //temp foreach\n"+
          "  "+tupType(m.tks,m.tp)+"* "+e0+" = "+n+".head;\n"+
          "  while("+e0+"){\n"+
          "    "+ki.map{case ((k,ktp),i)=>ktp+" "+rn(k)+" = "+e0+"->_"+(i+1)+";\n"}.mkString+
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
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co(/*"(/*if */"+*/"("+rn(n)+" == "+v+")"/*+" ? 1L : 0L)"*/),am)
      else e match {
        case Ref(n2) => ctx.add(n,(e.tp,rn(n2))); co("1L") // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ => ctx.add(n,(e.tp,fresh("l"))); cpsExpr(e,(v:String)=> e.tp.toCpp+" "+rn(n)+" = "+v+";\n"+co("1L"),am)
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
      if (a.agg==Nil) { val cur=ctx.save; cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t.toSet==a.agg.toSet => val cur=ctx.save; val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+s2
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val ksTp = a.agg.map(_._2)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,a0,ks,v),tmp); ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>ADD_TO_TEMP_MAP_FUNC(ksTp,a.tp,a0,ks,v),tmp); ctx.load(cur)
          genVar(a0,a.tp,a.agg.map(_._2))+s1+s2+cpsExpr(mapRef(a0,a.tp,a.agg),co)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) { val a0=fresh("agg"); genVar(a0,a.tp)+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t.toSet==aks.toSet => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = genVar(a0,e.tp,aks.map(_._2))+"\n"+cpsExpr(e,(v:String)=>ADD_TO_TEMP_MAP_FUNC(aks.map(_._2),e.tp,a0,aks.map(_._1),v),tmp);
          ctx.load(cur); s1+cpsExpr(mapRef(a0,e.tp,aks),co)
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
            else "if ("+FIND_IN_MAP_FUNC(m.name)+"("+m.name+", "+sampleEnt+".modify("+(m.keys map rn).mkString(",")+"))==0) "+SET_IN_MAP_FUNC(m.name)+"("+m.name+", "+sampleEnt+", "+i+");\n"
          )
        case None => ""
      }
      ctx.load(); clear+init+cpsExpr(e,(v:String) => (if (m.keys.size==0) m.name+" "+sop+" "+v else { fop+"("+m.name+", "+sampleEnt+".modify("+(m.keys map rn).mkString(",")+"),"+v+")"})+";\n",Some(m.keys zip m.tks))
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
    //   val tk = tupType(m.keys.map(_._2),m.tp)
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

  override def toMapFunction(q: Query) = q.name+".toMap"
  override def clearOut = {}
  override def onEndStream = ""

  def genIntermediateDataStructureRefs(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>queries.filter(_.name==m.name).size == 0}.map{m=>m.toCppType+" "+m.name+";\n"}.mkString

  def genTempMapDefs = tmpMapDefs.map{ case (n, tp) => "MultiHashMap<"+tp+",HashIndex<"+tp+"> > "+n+";\n" }.mkString

  def isExpressiveTLQSEnabled(queries:List[Query]) = queries.exists{ query => query.map match {
      case MapRef(n,_,_) => if (n == query.name) false else true
      case _ => true
    }
  }

  private def getInitializationForIntermediateValues(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>(queries.filter(_.name==m.name).size == 0) && (m.keys.size == 0)}.map{m=>", "+m.name+"(" + m.tp.zeroCpp + ")"}.mkString

  private def getInitializationForTempMaps = tmpMapDefs.map{ case (n,tp) => ", "+n+"(16U)" }.mkString

  private def getInitializationForPublicValues(maps:List[MapDef],queries:List[Query]) = maps.filter{m=>(queries.filter(_.name==m.name).size != 0) && (m.keys.size == 0)}.map{m=>", "+m.name+"(" + m.tp.zeroCpp + ")"}.mkString

  private def getInitializationForTLQ_T(maps:List[MapDef],queries:List[Query]) = getInitializationForPublicValues(maps,queries) + (if(isExpressiveTLQSEnabled(queries)) getInitializationForIntermediateValues(maps,queries)+getInitializationForTempMaps else "")

  private def getInitializationForDATA_T(maps:List[MapDef],queries:List[Query]) = (if(isExpressiveTLQSEnabled(queries)) "" else getInitializationForIntermediateValues(maps,queries)+getInitializationForTempMaps)

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

    def genTableTriggers = s0.sources.filter(!_.stream).map{ s =>
      val name = s.schema.name
      val fields = s.schema.fields
      "void on_insert_"+name+"("+fields.map{case (fld,tp) => tp.toCpp+" "+fld }.mkString(", ")+") {\n"+
      "  "+name+"_entry e("+fields.map{case (fld,_) => fld }.mkString(", ")+", 1);\n"+
      "  "+ADD_TO_MAP_FUNC(name)+"("+name+",e,1L);\n"+
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
        "  explicit "+mapEntry+"("+fieldsWithIdx.map{case ((_,tp),i) => tp.toCpp+" c"+i}.mkString(", ")+") { "+fieldsWithIdx.map{case ((fld,_),i) => fld+" = c"+i+"; "}.mkString+"}\n"+
        "  "+mapEntry+"(const "+mapEntry+"& other) : "+fieldsWithIdx.map{case ((fld,tp),i) => fld+"( other."+fld+" ), "}.mkString+"nxt( nullptr ), prv( nullptr ) {}\n"+
        // "  "+mapEntry+"& operator=(const "+mapEntry+"& other) { "+fieldsWithIdx.map{case ((fld,tp),i) => fld+" = other."+fld+";"}.mkString+" return *this; }\n"+
        // "  "+mapEntry+"& operator=(const "+mapEntry+"&& other) { "+fieldsWithIdx.map{case ((fld,tp),i) => fld+" = "+(if(tp.isBasicCppType) "other."+fld else "std::move(other."+fld+")")+";"}.mkString+" return *this; }\n"+
        allIndices.map{ case (is,unique) =>
        "  FORCE_INLINE "+mapEntry+"& modify"+(if(unique) "" else getIndexId(mapName,is))+"("+is.map{case i => fields(i)._2.toCpp+" c"+i}.mkString(", ")+") { "+is.map{case i => fields(i)._1+" = c"+i+"; "}.mkString+" return *this; }\n"
        }.mkString+
        "  template<class Archive>\n"+
        "  void serialize(Archive& ar, const unsigned int version)\n"+
        "  {\n"+
        fields.map{case (fld,_) => "    ar & BOOST_SERIALIZATION_NVP("+fld+");\n"}.mkString+
        "  }\n"+
        "};"
      // def isStringFieldInTheIndex(is:List[Int]) = is.map(fields(_)._2).contains(TypeString)
      // def isIndexingSingleStringField(is:List[Int]) = ((is.size == 1) && (fields(is(0))._2 == TypeString))
      // def isIndexingSingleField(is:List[Int]) = is.size == 1
      // def isIndexingSequentialFields(is:List[Int]):Boolean = {
      //   if(is.size > 1) {
      //     var cur = 0;
      //     while(cur < is.size-1) {
      //       if(is(cur)+1 != is(cur+1)){
      //         return false
      //       }
      //       cur+=1
      //     }
      //   }
      //   true
      // }

      def genExtractorsAndHashers = allIndices.map{ case (is,unique) =>
        //TODO XXX we can implement a better hasher, e.g. using murmur hash
        "struct "+mapType+"key"+getIndexId(mapName,is)+"_idxfn {\n"+
        "  FORCE_INLINE static size_t hash(const "+mapEntry+"& e) {\n"+
        // (if(is.size == m.keys.size && !isStringFieldInTheIndex(is)) {
        // "    return MurmurHash2(&e,sizeof("+mapEntry+")-sizeof((("+mapEntry+" *)0)->__av));"
        // } else if(isIndexingSingleStringField(is)) {
        // "    const char* fld = e."+fields(is(0))._1+".c_str();\n"+
        // "    return MurmurHash2(fld,strlen(fld));"
        // } else if(isIndexingSingleField(is)) {
        // "    return MurmurHash2(&(e."+fields(is(0))._1+"),sizeof((("+mapEntry+" *)0)->"+fields(is(0))._1+"));"
        // } else if(!isStringFieldInTheIndex(is) && isIndexingSequentialFields(is)) {
        // "    return MurmurHash2(&(e."+fields(is(0))._1+"),"+is.map{ isIndex => "sizeof((("+mapEntry+" *)0)->"+fields(isIndex)._1+")"}.mkString("+")+");"
        // } else {
        "    size_t h = 0;\n"+
        is.map{ isIndex => "    hash_combine(h, e."+fields(isIndex)._1+");\n" }.mkString +
        "    return h;"+
        // "    uint32_t h=0, carry=0;\n"+
        // is.map{ isIndex => (if(fields(isIndex)._2 == TypeString) "    const char* fld"+isIndex+" = e."+fields(is(isIndex))._1+".c_str();\n    int fldlen"+isIndex+" = strlen(fld"+isIndex+");\n" else "")+
        // "    PMurHash32_Process(&h, &carry, &(e."+fields(isIndex)._1+"),"+(if(fields(isIndex)._2 == TypeString) "fldlen"+isIndex else "sizeof((("+mapEntry+" *)0)->"+fields(isIndex)._1+")")+");\n"
        // }.mkString +
        // "    return PMurHash32_Result(h, carry, "+is.sortBy{ isIndex => if(fields(isIndex)._2 == TypeString) 1 else 0}.map{ isIndex => if(fields(isIndex)._2 == TypeString) "fldlen"+isIndex else "sizeof((("+mapEntry+" *)0)->"+fields(isIndex)._1+")"}.mkString("+")+");\n"
        // })+
        "\n"+
        "  }\n"+
        "  FORCE_INLINE static bool equals(const "+mapEntry+"& x, const "+mapEntry+"& y) {\n"+
        "    return "+is.map{ isIndex => val fld=fields(isIndex)._1;"(x."+fld+"==y."+fld+")" }.mkString(" && ") + ";\n" +
        "  }\n"+
        "};\n"
      }.mkString("\n")

      def genTypeDefs =
        "typedef MultiHashMap<"+mapEntry+","+
        allIndices.map{case (is,unique) => "\n  HashIndex<"+mapEntry+","+mapType+"key"+getIndexId(mapName,is)+"_idxfn,"+unique+">"}.mkString(",")+
        "\n> "+mapType+";\n"+
        allIndices.map{ case (is,unique) =>
          "typedef HashIndex<"+mapEntry+","+mapType+"key"+getIndexId(mapName,is)+"_idxfn,"+unique+"> HashIndex_"+mapType+"_"+getIndexId(mapName,is)+";\n"
        }.mkString

      def genHelperFunctions =
        (if(helperFuncUsage.contains(("FIND_IN_MAP_FUNC" -> mapName))) "FORCE_INLINE "+mapValueType+" "+FIND_IN_MAP_FUNC(mapName)+"(const "+mapType+"& m, const "+mapEntry+"& k) {\n"+
        "  "+mapValueType+" res = "+m.tp.zeroCpp+";\n"+ 
        "  "+mapEntry+"* lkup = m.get(k);\n"+
        "  if (lkup!=nullptr) res = lkup->"+VALUE_NAME+";\n"+
        "  return res;\n"+
        "}\n" else "")+
        (if(helperFuncUsage.contains(("SET_IN_MAP_FUNC" -> mapName))) "FORCE_INLINE void "+SET_IN_MAP_FUNC(mapName)+"("+mapType+"& m, "+mapEntry+"& k, const "+mapValueType+"& v) {\n"+
        "  "+mapEntry+"* lkup = m.get(k);\n"+
        "  if (v == "+m.tp.zeroCpp+") { if(lkup != nullptr) m.del(lkup); /*else \"nothing should be done\"*/ }\n"+
        "  else if(/*v != "+m.tp.zeroCpp+" &&*/ lkup != nullptr) lkup->"+VALUE_NAME+"=v;\n"+
        "  else /*if(v != "+m.tp.zeroCpp+" && lkup == nullptr)*/ { k."+VALUE_NAME+" = v; m.insert_nocheck(k); }\n"+
        "}\n" else "")+
        (if(helperFuncUsage.contains(("ADD_TO_MAP_FUNC" -> mapName))) "FORCE_INLINE void "+ADD_TO_MAP_FUNC(mapName)+"("+mapType+"& m, "+mapEntry+"& k, const "+mapValueType+"& v) {\n"+
        "  if (v != "+m.tp.zeroCpp+") {\n"+
        "    "+mapEntry+"* lkup = m.get(k);\n"+
        "    if(lkup != nullptr) { lkup->"+VALUE_NAME+"+=v; if(lkup->"+VALUE_NAME+" == "+m.tp.zeroCpp+") m.del(lkup); }\n"+
        "    else { k."+VALUE_NAME+" = v; m.insert_nocheck(k); }\n"+
        "  }\n"+
        "}" else "")
      genEntryStruct+"\n"+genExtractorsAndHashers+"\n"+genTypeDefs+"\n"+genHelperFunctions
    }
    def genTempTupleTypes = tempTupleTypes.map{case (name,(ksTp,vsTp)) => 
      val ksTpWithIdx = ksTp.zipWithIndex
      val valVarName = VALUE_NAME
      "struct " + name +" {\n"+
      "  "+ksTpWithIdx.map{case (k,i) => k.toCpp+" _"+(i+1)+"; "}.mkString+(vsTp.toCpp+" "+valVarName+"; "+name+"* nxt; "+name+"* prv;")+"\n"+
      "  explicit "+name+"() : nxt(nullptr), prv(nullptr) { "/*+ksTpWithIdx.map{case (k,i) => "_"+(i+1)+" = "+k.zeroCpp+"; "}.mkString+(valVarName+" = "+vsTp.zeroCpp+";")*/+"}\n"+
      "  explicit "+name+"("+ksTpWithIdx.map{case (k,i) => k.toCpp+" c"+(i+1)+", "}.mkString+(vsTp.toCpp+" c"+valVarName+"="+vsTp.zeroCpp)+") : nxt(nullptr), prv(nullptr) { "+ksTpWithIdx.map{case (_,i) => "_"+(i+1)+" = c"+(i+1)+"; "}.mkString+(valVarName+" = c"+valVarName+";")+"}\n"+
      "  int operator<(const "+name+" &rhs) const { \n"+ksTpWithIdx.map{case (v,i) => "    if(this->_"+(i+1)+"!=rhs._"+(i+1)+") return (this->_"+(i+1)+"<rhs._"+(i+1)+");\n"}.mkString+"    return 0;\n  }\n"+
      "  int operator==(const "+name+" &rhs) const { return ("+ksTpWithIdx.map{case (v,i) => "(this->_"+(i+1)+"==rhs._"+(i+1)+")"}.mkString(" && ")+"); }\n"+
      "  FORCE_INLINE "+name+"& modify("+ksTpWithIdx.map{case (k,i) => k.toCpp+" c"+i+", "}.mkString+vsTp.toCpp+" c"+valVarName+") { "+ksTpWithIdx.map{case (k,i) => "_"+(i+1)+" = c"+i+"; "}.mkString+valVarName+" = c"+valVarName+"; return *this; }\n"+
      "  static bool equals(const "+name+" &x, const "+name+" &y) { return ("+ksTpWithIdx.map{case (v,i) => "(x._"+(i+1)+"==y._"+(i+1)+")"}.mkString(" && ")+"); }\n"+
      "  static long hash(const "+name+" &e) {\n"+
      "    size_t h = 0;\n"+
      ksTpWithIdx.map{ case (v,i) => "    hash_combine(h, e._"+(i+1)+");\n" }.mkString +
      "    return h;\n"+
      "  }\n"+
      "};"
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
    val resAcc = helperResultAccessor(s0)
    val ms = s0.queries.filter(q=>(s0.maps.filter(_.name==q.name).size == 0) && (q.keys.size > 0)).map(q=>genMapStructDef(MapDef(q.name,q.tp,q.keys,q.map))).mkString("\n") + // queries`without a map (with -F EXPRESSIVE-TLQS)
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
       ind(genIntermediateDataStructureRefs(s0.maps,s0.queries))+"\n"+
       ind(genTempMapDefs)+"\n"+
       ind(consts)+
    "\n\n"} else "")+
    "};\n"+
    "\n"+
    helper(s0)
  }

  private def helperResultAccessor(s0:System) = {
    def compile_serialization = s0.queries.map{q =>
      q.toCppRefType + " _"+q.name+" = get_"+q.name+"();\n"+
      "ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE("+q.name+"), _"+q.name+");\n"
    }.mkString

    def compile_tlqs = s0.queries.map{ query =>
      query.toCppRefType + " get_"+query.name+"(){\n"+
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
              cpsExpr(query.map, (v:String) => ADD_TO_MAP_FUNC(query.name)+"("+mapName+","+sampleEnt+".modify("+(nk map rn).mkString(",")+"),"+v+");")+"\n"+
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
    "  void serialize(Archive& ar, const unsigned int version) {\n"+
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
       ind(genIntermediateDataStructureRefs(s0.maps,s0.queries))+"\n"+
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

  override def pkgWrapper(pkg:String, body:String) = "#include \"program_base.hpp\"\n#include \"mmap/mmap.hpp\"\n"+additionalImports()+"\n"+"namespace dbtoaster {\n"+ind(body)+"\n\n}\n"

    // "package "+pkg+"\nimport ddbt.lib._\n"+additionalImports()+"\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    // "object "+cls+" {\n"+ind("import Helper._\n"+
    // "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long)=>run["+cls+"]("+streams(s0.sources)+",p,t),f)\n\n"+
    // "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    // ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    // "\n})")+"\n}")+"\n}\n\n"
  def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"

  override def additionalImports():String = ""
}
