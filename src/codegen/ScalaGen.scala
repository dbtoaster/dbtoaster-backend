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
 * - Lift alone has only bound variables. In Exists*Lift, Exists binds variables for the Lift
 *
 * @author TCK
 */
case class ScalaGen(cls:String="Query") extends (M3.System => String) {
  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  def tpe(tp:Type):String = { val s=tp.toString; s.substring(0,1).toUpperCase+s.substring(1).toLowerCase }
  private def bnd(e:Expr):Set[String] = e.collect { case Lift(n,e) => bnd(e)+n case AggSum(ks,e) => ks.toSet case MapRef(n,tp,ks) => ks.toSet }

  // Methods involving only constants are hoisted as global constants
  private val cs = HashMap[Apply,String]()
  def constApply(a:Apply):String = cs.get(a) match { case Some(n) => n case None => val n=fresh("c"); cs+=((a,n)); n }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   b :bound variables
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def cpsExpr(ex:Expr,b:Set[String]=Set(),co:String=>String=(v:String)=>v,am:Option[(String,List[(String,Type)])]=None):String = ex match {
    // Fixes
    case Mul(Exists(e1),Lift(n,e)) => cpsExpr(e1,b,(v1:String)=>cpsExpr(e,b++bnd(e1),(v:String)=>"val "+n+" = "+v+";\n"+co("(if (("+v1+")!=0) 1L else 0L)"),am),am)
    case Mul(Exists(el),er) => cpsExpr(el,b,(vl:String)=>cpsExpr(er,b++bnd(el),co,am),am)
    
    // case Mul(Lift(n,Ref(n2)),er) if !b.contains(n) && b.contains(n2) => cpsExpr(er,b,co,am).toString.replaceAll("(?<!\\w)"+n+"(?!\\w)",n2) // dealiasing !! co might be out of my allowed scope !!
    // XXX: do we also want to rename aggregation key variables instead of protecting them ? (typecheck/lift rename)
    //case Exists(e) => val e0=fresh("ex"); "var "+e0+":Long = 0L\n"+cpsExpr(e,b,(v:String)=>e0+" |= ("+v+")!=0;")+"\n"+co(e0) // this should not appear, or find how to bind it properly

    // -------------------------------------------------------------------------
    case Ref(n) => co(n)
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Exists(e) => cpsExpr(e,b,(v:String)=>co("(if (("+v+")!=0) 1L else 0L)"))
    case Cmp(l,r,op) => co(cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>"(if ("+ll+" "+op+" "+rr+") 1L else 0L)")))
    case app@Apply(fn,tp,as) =>
      if (as.forall(_.isInstanceOf[Const])) co(constApply(app)) // hoist constants resulting from function application
      else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>cpsExpr(a,b,(v:String)=>c0(p+(if (i>0) "," else "(")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+fn) }
    case MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>b.contains(k)}
      if (ki.size==0) co(n+".get("+tup(ks)+")") // all keys are bound
      else { val (k0,v0)=(fresh("k"),fresh("v"))
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map{case (k,i)=>i})+","+tup(ko.map{case (k,i)=>k})+")" else ""
        n+sl+".foreach { ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";"}.mkString("\n")+"\n"+co(v0))+"\n}\n" // bind free variables from retrieved key
      }
    case Lift(n,e) =>
      if (b.contains(n)) cpsExpr(e,b,(v:String)=>co("("+n+" == "+v+")"),am)
      else cpsExpr(e,b,(v:String)=> if (n.matches("^lift[0-9]+$")) "val "+n+" = "+v+";\n"+co("1") else ";{\n"+ind("val "+n+" = "+v+";\n"+co("1"))+"\n};\n",am)
    case Mul(el,er) => cpsExpr(el,b,(vl:String)=>cpsExpr(er,b++bnd(el),(vr:String)=>co(if (vl=="1") vr else if (vr=="1") vl else "("+vl+" * "+vr+")"),am),am)
    case a@Add(el,er) =>
      if (a.agg==Nil) cpsExpr(el,b,(vl:String)=>cpsExpr(er,b,(vr:String)=>co("("+vl+" + "+vr+")"),am),am)
      else am match {
        case Some(t) if t._2==a.agg => cpsExpr(el,b,co,am)+"\n"+cpsExpr(er,b,co,am)
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks=a.agg.map{x=>x._1}
          val tmp = Some((a0,a.agg))
          "val "+a0+" = K3Map.temp["+tup(a.agg.map{x=>tpe(x._2)})+","+tpe(ex.tp)+"]()\n"+
          cpsExpr(el,b,(v:String)=>a0+".add("+tup(ks)+","+v+")",tmp)+"\n"+
          cpsExpr(er,b,(v:String)=>a0+".add("+tup(ks)+","+v+")",tmp)+"\n"+
          a0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}\n"
      }
    case a@AggSum(ks,e) =>
      val fs = ks.filter{k=> !b.contains(k)} // free variables
      val agg=fs.map{f=>(f,(ks zip a.tks).toMap.apply(f)) }
      if (ks.size==0 || fs.size==0) { val a0=fresh("agg"); "var "+a0+":"+tpe(ex.tp)+" = 0;\n"+cpsExpr(e,b,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t._2==agg => cpsExpr(e,b,co,am)
        case _ =>
          val r = { val ns=fs.map(v=>(v,fresh(v))).toMap; (n:String)=>ns.getOrElse(n,n) } // renaming function
          val a0=fresh("agg")
          val tmp=Some((a0,agg)) // declare this as summing target
          "val "+a0+" = K3Map.temp["+tup(agg.map(x=>tpe(x._2)))+","+tpe(e.tp)+"]()\n"+
          cpsExpr(e.rename(r),b,(v:String)=> { a0+".add("+tup(agg.map(x=>r(x._1)))+","+v+");\n" },tmp)+cpsExpr(MapRef(a0,TypeLong,fs),b,co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt,b:Set[String]):String = s match {
    case StmtMap(m,e,op,oi) => val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = (oi match {
        case Some(ie) => cpsExpr(ie,b,(i:String)=>"if ("+m.name+".get("+(if (m.keys.size==0) "" else tup(m.keys))+")==0) "+m.name+".set("+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n"
        case None => ""
      })
      clear+init+cpsExpr(e,b,(v:String) => m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  def genTrigger(t:Trigger):String = {
    val (n,as,ss) = t match {
      case TriggerReady(ss) => ("SystemReady",Nil,ss)
      case TriggerAdd(Schema(n,cs),ss) => ("Add"+n,cs,ss)
      case TriggerDel(Schema(n,cs),ss) => ("Del"+n,cs,ss)
    }
    val b=as.map{_._1}.toSet
    "def on"+n+"("+as.map{a=>a._1+":"+tpe(a._2)} .mkString(", ")+") {\n"+ind(ss.map{s=>genStmt(s,b)}.mkString)+"\n}"
  }

  // Lazy slicing (secondary) indices computation
  private val sx = HashMap[String,List[List[Int]]]() // slicing indices
  def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  def genMap(m:MapDef):String = {
    if (m.keys.size==0) "val "+m.name+" = new K3Var["+tpe(m.tp)+"]();"
    else {
      val tk = tup(m.keys.map(x=>tpe(x._2)))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      val ix = if (s.size==0) "" else "List("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+")"
      "val "+m.name+" = K3Map.make["+tk+","+tpe(m.tp)+"]("+ix+");"
    }
  }

  def genSystem(s0:System):String = {
    def ev(s:Schema,short:Boolean=true):(String,String) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      ("List("+fs.map{case(s,t)=>s.toLowerCase+":"+tpe(t)}.mkString(",")+")","("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")")
    }
    val ts = s0.triggers.map(genTrigger).mkString("\n\n") // triggers (need to be generated before maps)
    val ms = s0.maps.map(genMap).mkString("\n") // maps
    val ld = { // optional preloading of static tables content
      val ld0 = s0.sources.filter{s=> !s.stream}.map { s=> val (in,ad,sp)=genStream(s); val (i,o)=ev(s.schema)
        "SourceMux(Seq(("+in+",Decoder({ case TupleEvent(TupleInsert,_,_,"+i+")=>"+s.schema.name+".add("+o+",1L) },"+ad+","+sp+")))).read;" }.mkString("\n");
      if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else ""
    }
    val gc = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "val "+n+":"+tpe(tp)+" = U"+f+"("+vs.mkString(",")+")\n" }.mkString+"\n" // constant function applications
    
    freshClear()
    "class "+cls+" extends Actor {\n"+ind(
    "import ddbt.lib.Messages._\n"+
    "import ddbt.lib.Functions._\n\n"+ms+"\n\n"+
    "var t0:Long = 0\n"+
    "def receive = {\n"+ind(
      s0.triggers.map{
        case TriggerAdd(s,_) => val (i,o)=ev(s); "case TupleEvent(TupleInsert,\""+s.name+"\",tx,"+i+") => onAdd"+s.name+o+"\n"
        case TriggerDel(s,_) => val (i,o)=ev(s); "case TupleEvent(TupleDelete,\""+s.name+"\",tx,"+i+") => onDel"+s.name+o+"\n"
        case _ => ""
      }.mkString+
      "case SystemInit =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime()\n"+
      "case EndOfStream | GetSnapshot => val time=System.nanoTime()-t0; sender ! (time,"+tup(s0.queries.map{q=>q.name+(if (s0.mapType(q.m.name)._1.size>0) ".toMap" else ".get()")})+")"
    )+"\n}\n"+gc+ts+ld)+"\n}\n"
  }

  private def genStream(s:Source): (String,String,String) = {
    val in = s.in match { case SourceFile(path) => "new java.io.FileInputStream(\""+path+"\")" }
    val split = "Split"+(s.split match { case SplitLine => "()" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => ".p("+p+")" })
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => "OrderBook()"
      case "CSV" => val sep=java.util.regex.Pattern.quote(s.adaptor.options.getOrElse("delimiter",",")).replaceAll("\\\\","\\\\\\\\")
                    "CSV(\""+s.schema.name.toUpperCase+"\",\""+s.schema.fields.map{f=>f._2}.mkString(",")+"\",\""+sep+"\")"
    }
    (in,"new Adaptor."+adaptor,split)
  }

  def genStreams(sources:List[Source]) = {
    // Little fix for libraries variation as 1 stream for OrderBooks generates BOTH asks and bids events.
    def fixOrderbook(ss:List[Source]):List[Source] = ss.zipWithIndex.filter{case (s,i)=>i>0 || s.adaptor.name!="ORDERBOOK"}.map(_._1)
    "Seq(\n"+ind(fixOrderbook(sources).filter{s=>s.stream}.map{s=> val (in,ad,sp)=genStream(s); "("+in+","+ad+","+sp+")" }.mkString(",\n"))+"\n)"
  }

  // Helper that contains the main and stream generator
  def genViewType(s0:System) = tup(s0.queries.map{q=> val m=s0.mapType(q.m.name); if (m._1.size==0) tpe(m._2) else "Map["+tup(m._1.map(tpe))+","+tpe(m._2)+"]" })
  def genHelper(s0:System) = {
    "package ddbt.generated\nimport ddbt.lib._\n\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    "object "+cls+" extends Helper {\n"+ind(
    "def execute() = run["+cls+","+genViewType(s0)+"]("+genStreams(s0.sources)+")\n\n"+
    "def main(args:Array[String]) {\n"+ind("val res = bench(\"NewGen\",10,execute)\n"+
    s0.queries.zipWithIndex.map { case (q,i)=> val m=s0.mapType(q.m.name);
      "println(\""+q.name+":\")\nprintln(K3Helper.toStr(res"+(if (s0.queries.size>1) "._"+(i+1) else "")+")+\"\\n\")"
    }.mkString("\n"))+"\n}")+"\n}\n\n"
  }
  def apply(s:System) = genHelper(s)+genSystem(s)
}

// add a special primitive for aggregation with keys => groupBy()
// Some "-1" simplifications
//    case Add(l,Mul(Const(typeLong,"-1"),Ref(n))) => co(cpsExpr(l,b,(ll:String)=>"("+ll+" - "+n+")"))
//    case Mul(Const(typeLong,"-1"),Ref(n)) => co("-"+n)

/*
case Mul(Exists(e1),Lift(n,e)) if e1==e => assert(b.contains(n)); cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";\n"+co("("+n+" != 0)")) // LiftExist
case Mul(Exists(e1),Lift(n,e)) => cpsExpr(e1,b,(v1:String)=>cpsExpr(e,b++bnd(e1),(v:String)=>"val "+n+" = "+v+";\n"+co("("+v1+" != 0)"),am),am)
// XXX: optimization
//case Mul(Cmp(l,r,op),e) => cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>"if ("+ll+" "+op+" "+rr+") {\n"+ind(cpsExpr(e,b,co))+"\n}\n"))
// XXX: put each lift in its own context to avoid name clashes
// ASSERTION IS WRONG (see TPC-H 15)
case Mul(Lift(n,e),er) if !b.contains(n) => cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";\n")+cpsExpr(er,b+n,co,am) // 'regular' Lift
case Mul(el,er) => cpsExpr(el,b,(vl:String)=>cpsExpr(er,b++bnd(el),(vr:String)=>co("("+vl+" * "+vr+")"),am),am) // right is nested in left (right is a continuation of left)
case Add(el,er) =>
   val vs = ( (bnd(el)--b) & (bnd(er)--b) ).toList // free variables present on both sides
   //println("b="+b+"\nl="+bnd(el)+"\nr="+bnd(er)+"\nvs="+vs)
   if (vs.size>0 && el.dim.size>0&&er.dim.size>0) {
     val (t0,k0,v0)=(fresh("tmp_add"),fresh("k"),fresh("v"))
     //(if (ex.dim.size==0) "/ *\n BUG: vs="+vs+"\n b="+b+"\nbl="+(bnd(el).filter(x=> !b.contains(x))--b)+"\nbr="+bnd(er)+"\n"+ex.dim+" -> "+ex.tp+" ["+am+"] := "+ex+" * /\n" else "")+
     "val "+t0+" = K3Map.temp["+tup(ex.dim.map(tpe))+","+tpe(ex.tp)+"]()\n"+
     cpsExpr(el,b,(v:String)=>t0+".add("+tup(vs)+","+v+")",Some(t0))+"\n"+
     cpsExpr(er,b,(v:String)=>t0+".add("+tup(vs)+","+v+")",Some(t0))+"\n"+
     t0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
     (if (vs.size==1) "val "+vs(0)+" = "+k0+"\n" else vs.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}"
   } else cpsExpr(el,b,(vl:String)=>cpsExpr(er,b,(vr:String)=>co("("+vl+" + "+vr+")"),am),am) // right is nested in left
case agg@AggSum(ks,e) =>
  val in = if (ks.size>0) e.collect{ case Lift(n,x) => Set(n) } else Set[String]()
  if ((ks.toSet & in).size==0) { // key is not defined by inner Lifts
    if (am!=None) cpsExpr(e,b,co) else { val a0=fresh("agg"); "var "+a0+":"+tpe(ex.tp)+" = 0;\n{ "+cpsExpr(e,b,(v:String)=>a0+" += "+v+";")+" }\n"+co(a0) }
  } else {
    val fs = ks.toSet--b // free variables
    val bs = ks.toSet--fs // bound variables
    val r = { val ns=bs.map(b=>(b,fresh(b))).toMap; (n:String)=>ns.getOrElse(n,n) } // renaming function
    val (t0,fused) = am match {
      case Some(t0) => (t0,true)
      case None => (fresh("tmp"),false)
    }
    (if (!fused) "val "+t0+" = K3Map.make["+tup(agg.dim.map(tpe))+","+tpe(e.tp)+"]()\n" else "")+
    cpsExpr(e.rename(r),b++ks.map(r).toSet,(v:String)=> {
      val s=t0+".add("+tup(ks.map(r))+","+v+");"
      if (bs.size==0) s else "if ("+bs.map{ b=>b+" == "+r(b) }.mkString(" && ")+") {\n"+ind(s)+"\n}"
    })+(if (!fused) "\n"+cpsExpr(MapRef(t0,TypeLong,ks),b,co) else "")
    / * EQUIVALENT TO
    (if (!fused) "val "+t0+" = K3Map.make["+tup(agg.dim.map(tpe))+","+tpe(e.tp)+"]()\n" else "")+
    cpsExpr(e,b++ks.toSet,(v:String)=> { "\n{\n"+t0+".add("+tup(ks)+","+v+");\n}\n"
    })+(if (!fused) "\n"+cpsExpr(MapRef(t0,TypeLong,ks),b,co) else "")
    * /
  }
*/
