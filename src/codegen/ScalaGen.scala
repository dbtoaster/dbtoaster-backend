package ddbt.codegen
import ddbt.ast._

/**
 * ScalaGen is responsible to transform a typed AST into vanilla Scala code (String).
 * It should be quite straightforward to use LMS to do that instead.
 *
 * Implementation notes:
 * ---------------------------------------------
 * 1. We shall understand the multiply as a continuation of the left operand in the right one.
 *
 * 2. Add is more complicated than Mul as it does set union of lhs and rhs.
 *    If a free variable is present in both sides, iterate these. Concretely:
 *       f(A*B) --> A.foreach{ (k_a,v_a) => B.foreach { (k_b,v_b) => f(v_a * v_b) } }
 *       f(A+B) --> val dom=A.keySet++B.keySet; dom.foreach { k => f(A.get(k) + B.get(k)) }
 *
 *    An lighter approach to set union is:
 *       val tmp = Temp[domA(k_a)=domB(k_b)=dom -> tp(A)=tp(B)]
 *       A.foreach{ (k_a,v_a) => tmp.add(domA(k_a),v_a) }
 *       B.foreach{ (k_b,v_b) => tmp.add(domB(k_b),v_b) }
 *       tmp.foreach { (k,v) => f(v) }
 *
 * Constraints inherited from M3:
 * - Lift alone has only bound variables.
 * - In Exists*Lift, Exists binds variables for the Lift
 *
 * @author TCK
 */
class ScalaGen(cls:String="Query") extends CodeGen(cls) {
  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions

  // Methods involving only constants are hoisted as global constants
  private val cs = HashMap[Apply,String]()
  def constApply(a:Apply):String = cs.get(a) match { case Some(n) => n case None => val n=fresh("c"); cs+=((a,n)); n }
  // XXX: enlarge the definition to generalized constants

  var ctx:Ctx[Type] = null // Context: variable->type

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => co(n)
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Exists(e) => cpsExpr(e,(v:String)=>co("(if (("+v+")!=0) 1L else 0L)"))
    case Cmp(l,r,op) => co(cpsExpr(l,(ll:String)=>cpsExpr(r,(rr:String)=>"(if ("+ll+" "+op+" "+rr+") 1L else 0L)")))
    case app@Apply(fn,tp,as) =>
      if (as.forall(_.isInstanceOf[Const])) co(constApply(app)) // hoist constants resulting from function application
      else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>cpsExpr(a,(v:String)=>c0(p+(if (i>0) "," else "(")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+fn) }
    case m@MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
      if (ki.size==0) co(n+".get("+tup(ks)+")") // all keys are bound
      else { val (k0,v0)=(fresh("k"),fresh("v"))
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(_._1))+")" else ""
        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).toMap)
        n+sl+".foreach { ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";"}.mkString("\n")+"\n"+co(v0))+"\n}\n" // bind free variables from retrieved key
      }
    case Lift(n,e) =>
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("("+n+" == "+v+")"),am)
      else { ctx.add(Map((n,ex.tp))); cpsExpr(e,(v:String)=> if (n.matches("^lift[0-9]+$")) "val "+n+" = "+v+";\n"+co("1") else ";{\n"+ind("val "+n+" = "+v+";\n"+co("1"))+"\n};\n",am) }
    case Mul(el,er) => cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(if (vl=="1") vr else if (vr=="1") vl else "("+vl+" * "+vr+")"),am),am)
    case a@Add(el,er) =>
      if (a.agg==Nil) { val cur=ctx.save; cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t==a.agg => val cur=ctx.save; val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+"\n"+s2
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>a0+".add("+tup(ks)+","+v+")",tmp)+"\n"; ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>a0+".add("+tup(ks)+","+v+")",tmp)+"\n"; ctx.load(cur)
          ctx.add(a.agg.toMap)
          "val "+a0+" = K3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+s1+s2+
          a0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}\n"
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) { val a0=fresh("agg"); "var "+a0+":"+ex.tp.toScala+" = 0;\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t==aks => cpsExpr(e,co,am)
        case _ =>
          //val r = { val ns=aks.map{case (v,t)=>(v,fresh(v))}.toMap; (n:String)=>ns.getOrElse(n,n) } // renaming function
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = K3Map.temp["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]()\n"+cpsExpr(e,(v:String)=> { a0+".add("+tup(aks.map(_._1))+","+v+");\n" },tmp);
          ctx.load(cur); val ma=MapRef(a0,e.tp,aks.map(_._1)); ma.tks=aks.map(_._2); s1+cpsExpr(ma,co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) => val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = oi match {
        case Some(ie) => ctx.load(); cpsExpr(ie,(i:String)=>"if ("+m.name+".get("+(if (m.keys.size==0) "" else tup(m.keys))+")==0) "+m.name+".set("+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n"
        case None => ""
      }
      ctx.load(); clear+init+cpsExpr(e,(v:String) => m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  def genTrigger(t:Trigger):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    ctx = Ctx(as.toMap)
    val res = "def on"+n+"("+as.map(a=>a._1+":"+a._2.toScala).mkString(", ")+") {\n"+ind(t.stmts.map(genStmt).mkString)+"\n}"
    ctx = null; res
  }

  // Lazy slicing (secondary) indices computation
  protected val sx = HashMap[String,List[List[Int]]]() // slicing indices
  def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  def genMap(m:MapDef):String = {
    if (m.keys.size==0) "val "+m.name+" = new K3Var["+m.tp.toScala+"]();"
    else {
      val tk = tup(m.keys.map(x=>x._2.toScala))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      val ix = if (s.size==0) "" else "List("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+")"
      "val "+m.name+" = K3Map.make["+tk+","+m.tp.toScala+"]("+ix+");"
    }
  }

  // Generate (1:stream events handling, 2:table loading, 3:global constants declaration)
  def genInternals(s0:System) : (String,String,String) = {
    def ev(s:Schema,short:Boolean=true):(String,String) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      ("List("+fs.map{case(s,t)=>s.toLowerCase+":"+t.toScala}.mkString(",")+")","("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")")
    }
    val str = s0.triggers.map(_.evt match {
      case EvtAdd(s) => val (i,o)=ev(s); "case TupleEvent(TupleInsert,\""+s.name+"\","+i+") => onAdd"+s.name+o+"\n"
      case EvtDel(s) => val (i,o)=ev(s); "case TupleEvent(TupleDelete,\""+s.name+"\","+i+") => onDel"+s.name+o+"\n"
      case _ => ""
    }).mkString
    val ld0 = s0.sources.filter{s=> !s.stream}.map { s=> val (in,ad,sp)=genStream(s); val (i,o)=ev(s.schema)
      "SourceMux(Seq(("+in+",Decoder({ case TupleEvent(TupleInsert,_,"+i+")=>"+s.schema.name+".add("+o+",1L) },"+ad+","+sp+")))).read;" }.mkString("\n");
    val gc = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "val "+n+":"+tp.toScala+" = U"+f+"("+vs.mkString(",")+")\n" }.mkString+"\n" // constant function applications
    (str,ld0,gc)
  }

  def printK3VarGetMethod = ".get()"

  def apply(s0:System):String = {
    val ts = s0.triggers.map(genTrigger).mkString("\n\n") // triggers (need to be generated before maps)
    val ms = s0.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s0)
    val ld = if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else "" // optional preloading of static tables content
    freshClear()
    "class "+cls+" extends Actor {\n"+ind(
    "import ddbt.lib.Messages._\n"+
    "import ddbt.lib.Functions._\n\n"+ms+"\n\n"+
    "var t0:Long = 0\n"+
    "def receive = {\n"+ind(str+
      "case SystemInit =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime()\n"+
      "case EndOfStream | GetSnapshot(_) => val time=System.nanoTime()-t0; sender ! (time,List[Any]("+s0.queries.map{q=>q.name+(if (s0.mapType(q.map.name)._1.size>0) ".toMap" else printK3VarGetMethod)}.mkString(",")+"))"
    )+"\n}\n"+gc+ts+ld)+"\n}\n"
  }

  private def genStream(s:Source): (String,String,String) = {
    val in = s.in match { case SourceFile(path) => "new java.io.FileInputStream(\""+path+"\")" }
    val split = "Split"+(s.split match { case SplitLine => "()" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => ".p("+p+")" })
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => "OrderBook("+s.adaptor.options.toList.map { case (k,v) => k+"="+(k match {
        case "brokers" => v case "bids"|"asks" => "\""+v+"\"" case "deterministic" => (v!="no"&&v!="false").toString case _ => ""
      })}.filter(!_.endsWith("=")).mkString(",")+")"
      case "CSV" => val sep=java.util.regex.Pattern.quote(s.adaptor.options.getOrElse("delimiter",",")).replaceAll("\\\\","\\\\\\\\")
                    "CSV(\""+s.schema.name.toUpperCase+"\",\""+s.schema.fields.map(_._2).mkString(",")+"\",\""+sep+"\")"
    }
    (in,"new Adaptor."+adaptor,split)
  }

  def streams(sources:List[Source]) = {
    def fixOrderbook(ss:List[Source]):List[Source] = { // one source generates BOTH asks and bids events
      val (os,xs) = ss.partition{_.adaptor.name=="ORDERBOOK"}
      val ob = new java.util.HashMap[(Boolean,SourceIn),(Schema,Split,Map[String,String])]()
      os.foreach { case Source(s,sc,in,sp,ad) =>
        val (k,v) = ((s,in),(ad.options-"book") + ((ad.options.getOrElse("book","bids"),sc.name)))
        val p=ob.get(k); if (p==null) ob.put(k,(sc,sp,v)) else ob.put(k,(sc,sp,p._3++v))
      }
      scala.collection.JavaConversions.mapAsScalaMap(ob).toList.map { case ((s,in),(sc,sp,opts)) => Source(s,sc,in,sp,Adaptor("ORDERBOOK",opts)) } ::: xs
    }
    "Seq(\n"+ind(fixOrderbook(sources).filter{s=>s.stream}.map{s=> val (in,ad,sp)=genStream(s); "("+in+","+ad+","+sp+")" }.mkString(",\n"))+"\n)"
  }

  // Helper that contains the main and stream generator
  def helper(s0:System,numSamples:Int=10) = {
    "package ddbt.generated\nimport ddbt.lib._\n\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    "object "+cls+" extends Helper {\n"+ind(
    "def execute() = run["+cls+"]("+streams(s0.sources)+")\n\n"+
    "def main(args:Array[String]) {\n"+ind("val res = bench(\"NewGen\","+numSamples+",execute)\n"+
    s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\")\nprintln("+
      (if (q.map.keys.size==0) "res("+i+").toString" else "K3Helper.toStr(res("+i+").asInstanceOf[Map[_,_]])")+"+\"\\n\")" }.mkString("\n"))+"\n}")+"\n}\n\n"
  }
}
