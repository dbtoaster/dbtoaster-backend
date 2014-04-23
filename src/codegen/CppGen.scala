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
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions

  override def consts = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); tp.toCpp+" "+n+" = U"+f+"("+vs.mkString(",")+")\n" }.mkString+"\n" // constant function applications

  // Create a variable declaration
  //XXXXX TODO
  override def genVar(n:String,tp:Type,ks:List[Type]=Nil) = if (ks==Nil) tp.toCpp+" "+n+" = "+tp.zeroCpp+"\n" else tp.toCpp+" "+n+" = M3Map.temp["+tup(ks.map(_.toCpp))+","+tp.toCpp+"]()\n"

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match { // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Exists(e) => cpsExpr(e,(v:String)=>co("("+v+" != 0)"))
    case Cmp(l,r,op) => co(cpsExpr(l,(ll:String)=>cpsExpr(r,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case app@Apply(fn,tp,as) =>
      if (as.forall(_.isInstanceOf[Const])) co(constApply(app)) // hoist constants resulting from function application
      else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>cpsExpr(a,(v:String)=>c0(p+(if (i>0) "," else "(")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+fn) }
    case m@MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
      if (ki.size==0) co(n+(if (ks.size>0) ".get("+tup(ks.map(rn))+")" else "")) // all keys are bound
      else { val (k0,v0)=(fresh("k"),fresh("v"))
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(x=>rn(x._1)))+")" else "" // slice on bound variables
        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)
        n+sl+".foreach { ("+(if (ks.size==1) rn(ks.head) else k0)+","+v0+") =>\n"+ind(
          (if (ks.size>1) ki.map{case (k,i)=>"val "+rn(k)+" = "+k0+"._"+(i+1)+";\n"}.mkString else "")+co(v0))+"\n}\n" // bind free variables from retrieved key
      }
    // "1L" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("(if ("+rn(n)+" == "+v+") 1L else 0L)"),am)
      else e match {
        case Ref(n2) => ctx.add(n,(e.tp,rn(n2))); co("1L") // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ => ctx.add(n,(e.tp,fresh("l"))); cpsExpr(e,(v:String)=> "val "+rn(n)+" = "+v+";\n"+co("1L"),am)
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
        def cx(s:String):Option[(String,String)] = if (!s.startsWith("(if (")) None else { var d=1; var p=5; while(d>0) { if (s(p)=='(') d+=1 else if (s(p)==')') d-=1; p+=1; }; Some(s.substring(5,p-1),s.substring(p+1,s.lastIndexOf("else")-1)) }
        def vx(vl:String,vr:String) = if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"
        //pulling out the conditionals from a multiplication
        (cx(vl),cx(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => "(if ("+cl+" && "+cr+") "+vx(tl,tr)+" else "+ex.tp.zeroCpp+")"
          case (Some((cl,tl)),_) => "(if ("+cl+") "+vx(tl,vr)+" else "+ex.tp.zeroCpp+")"
          case (_,Some((cr,tr))) => "(if ("+cr+") "+vx(vl,tr)+" else "+ex.tp.zeroCpp+")"
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
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>a0+".add("+tup(ks map rn)+","+v+");\n",tmp); ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>a0+".add("+tup(ks map rn)+","+v+");\n",tmp); ctx.load(cur)
          genVar(a0,ex.tp,a.agg.map(_._2))+s1+s2+cpsExpr(mapRef(a0,ex.tp,a.agg),co)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) { val a0=fresh("agg"); genVar(a0,ex.tp)+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t.toSet==aks.toSet => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = M3Map.temp["+tup(aks.map(x=>x._2.toCpp))+","+e.tp.toCpp+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+tup(aks.map(x=>rn(x._1)))+","+v+");\n",tmp);
          ctx.load(cur); s1+cpsExpr(mapRef(a0,e.tp,aks),co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  override def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) => val (fop,sop)=op match { case OpAdd => ("add","+=") case OpSet => ("set","=") }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = oi match {
        case Some(ie) => ctx.load(); cpsExpr(ie,(i:String)=>
          if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
          else "if ("+m.name+".get("+tup(m.keys map rn)+")==0) "+m.name+".set("+tup(m.keys map rn)+","+i+");\n")
        case None => ""
      }
      ctx.load(); clear+init+cpsExpr(e,(v:String) => m.name+(if (m.keys.size==0) " "+sop+" "+v else "."+fop+"("+tup(m.keys map rn)+","+v+")")+";\n",if (op==OpAdd) Some(m.keys zip m.tks) else None)
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  override def genTrigger(t:Trigger):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap); val body=t.stmts.map(genStmt).mkString; ctx=null;
    "def on"+n+"("+as.map(a=>a._1+":"+a._2.toCpp).mkString(", ")+") "+(if (body=="") "{ }" else "{\n"+ind(body)+"\n}")
  }

  override def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  override def genMap(m:MapDef):String = {
    if (m.keys.size==0) genVar(m.name,m.tp).trim
    else {
      val tk = tup(m.keys.map(x=>x._2.toCpp))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      "val "+m.name+" = M3Map.make["+tk+","+m.tp.toCpp+"]("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+");"
    }
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
      case EvtAdd(s) => val (i,o,pl)=ev(s); "case TupleEvent(TupleInsert,\""+s.name+"\","+i+") => "+skip+"onAdd"+s.name+o+"\n"
      case EvtDel(s) => val (i,o,pl)=ev(s); "case TupleEvent(TupleDelete,\""+s.name+"\","+i+") => "+skip+"onDel"+s.name+o+"\n"
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
    val (lms,strLMS,ld0LMS,gcLMS) = genLMS(s0)
    val body = if (lms!=null) lms else {
      val ts = s0.triggers.map(genTrigger).mkString("\n\n") // triggers (need to be generated before maps)
      val ms = s0.maps.map(genMap).mkString("\n") // maps
      ms+"\n\n"+ts
    }
    val (str,ld0,gc) = if(lms!=null) (strLMS,ld0LMS,gcLMS) else genInternals(s0)
    val ld = if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else "" // optional preloading of static tables content
    freshClear()
    val snap=onEndStream+" sender ! (StreamStat(t1-t0,tN,tS),List("+s0.queries.map{q=>(if (s0.mapType(q.map.name)._1.size>0) toMapFunction(q) else q.name)}.mkString(",")+"))"
    clearOut
    "class "+cls+" extends Actor {\n"+ind(
    "import ddbt.lib.Messages._\n"+
    "import ddbt.lib.Functions._\n\n"+body+"\n\n"+
    "var t0=0L; var t1=0L; var tN=0L; var tS=0L\n"+
    "def receive_skip:Receive = { case EndOfStream | GetSnapshot(_) => "+snap+" case _ => tS+=1 }\n"+
    "def receive = {\n"+ind(str+
      "case StreamInit(timeout) =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime; if (timeout>0) t1=t0+timeout*1000000L\n"+
      "case EndOfStream | GetSnapshot(_) => t1=System.nanoTime; "+snap
    )+"\n}\n"+gc+ld)+"\n"+"}\n"+helper(s0)
  }

  private def genStream(s:Source): String = {
    val sourceId = fresh("source");
    val sourceSplitVar = sourceId + "_fd"
    val adaptorsArrVar = sourceId+"_adaptors_arr"
    val adaptorsListVar = sourceId+"_adaptors_list"
    val sourceFileVar = sourceId+"_file"
    val in = s.in match { case SourceFile(path) => "boost::shared_ptr<dbt_file_source> "+sourceFileVar+"(new dbt_file_source(\""+path+"\","+sourceSplitVar+","+adaptorsListVar+"));\n" }
    val split = "frame_descriptor "+sourceSplitVar+(s.split match { case SplitLine => "()" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => "XXXXX("+p+")" })+";\n" //XXXX for SplitPrefix
    
    val schema_param = s.schema.fields.map{case (_,tp) => tp.toCpp}.mkString(",")
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => {
        val bidsAndAsks = List("bids","asks")
        val a_opts = s.adaptor.options.filter{case (k,_) => !bidsAndAsks.contains(k)} ++ Map("schema" -> schema_param)
        val a_def = bidsAndAsks.map{ x =>  
          val adaptorVar = sourceId+"_adaptor_"+x
          val paramsVar = adaptorVar+"_params"
          val numParams = a_opts.size+1
          "pair<string,string> "+paramsVar+"[] = { make_pair(\"book\",\""+x+"\"), "+a_opts.map{case (k,v) => "make_pair(\""+k+"\",\""+v+"\")"}.mkString(", ")+" };\n"+
          "boost::shared_ptr<order_books::order_book_adaptor> "+adaptorVar+"(new order_books::order_book_adaptor(get_relation_id(\""+s.adaptor.options(x)+"\"),"+numParams+","+paramsVar+"));\n"
        }.mkString

        a_def+split+
        "boost::shared_ptr<stream_adaptor> "+adaptorsArrVar+"[] = { "+bidsAndAsks.map{ x => sourceId+"_adaptor_"+x}.mkString(", ")+" };\n"
      }      
      case "CSV" => {
        val a_opts = s.adaptor.options ++ Map("schema" -> schema_param)
        val adaptorVar = sourceId+"_adaptor"
        val paramsVar = adaptorVar+"_params"
        val numParams = a_opts.size
        val a_def = "pair<string,string> "+paramsVar+"[] = { "+a_opts.map{case (k,v) => "make_pair(\""+k+"\",\""+v+"\")"}.mkString(", ")+" };\n"+
          "boost::shared_ptr<csv_adaptor> "+adaptorVar+"(new csv_adaptor(get_relation_id(\""+s.schema.name+"\"),"+numParams+","+paramsVar+"));\n"

        a_def+split+
        "boost::shared_ptr<stream_adaptor> "+adaptorsArrVar+"[] = { "+adaptorVar+" };\n"
      }
    }

    adaptor+
    "std::list<boost::shared_ptr<stream_adaptor> > "+adaptorsListVar+"("+adaptorsArrVar+", "+adaptorsArrVar+" + sizeof("+adaptorsArrVar+") / sizeof(boost::shared_ptr<stream_adaptor>));\n"+
    in+"add_source("+sourceFileVar+");\n"
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
    val ss="\n/* Specifying data sources */\n\n"+fixOrderbook(sources)/*.filter{s=>s.stream}*/.map(genStream).mkString("\n")
    ss.replaceAll("/standard/","/DATASETPLACEHOLDER/")
  }

  // Helper that contains the main and stream generator
  override def helper(s0:System) = {
    val dataset = "DATASETPLACEHOLDER" //XXXX
    "/* Type definition providing a way to execute the sql program */\n"+
    "class Program : public ProgramBase\n"+
    "{\n"+
    "  public:\n"+
    "    Program(int argc = 0, char* argv[] = 0) : ProgramBase(argc,argv) {\n"+
    "      data.register_data(*this);\n"+
           ind(streams(s0.sources),3)+"\n"+
    "    }\n"+
    "\n"+
    "    /* Imports data for static tables and performs view initialization based on it. */\n"+
    "    void init() {\n"+
    "        process_tables();\n"+
    "        data.on_system_ready_event();\n"+
    "    }\n"+
    "\n"+
    "    /* Saves a snapshot of the data required to obtain the results of top level queries. */\n"+
    "    snapshot_t take_snapshot(){ tlq_t d=(tlq_t&)data; if (d.tS==0) { "+tc("d.")+" } printf(\"SAMPLE="+dataset+",%ld,%ld,%ld\\\\n\",d.tT,d.tN,d.tS);\n"+
    "        return snapshot_t( new tlq_t((tlq_t&)data) );\n"+
    "    }"+
    "\n"+
    "  protected:\n"+
    "    data_t data;\n"+
    "};\n"
  }

  override def pkgWrapper(pkg:String, body:String) = "#include \"program_base.hpp\"\n"+additionalImports()+"\n\n"+"namespace dbtoaster {\n"+ind(body)+"\n}\n"

    // "package "+pkg+"\nimport ddbt.lib._\n"+additionalImports()+"\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    // "object "+cls+" {\n"+ind("import Helper._\n"+
    // "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long)=>run["+cls+"]("+streams(s0.sources)+",p,t),f)\n\n"+
    // "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    // ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    // "\n})")+"\n}")+"\n}\n\n"
  def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"

  override def additionalImports():String = ""
}
