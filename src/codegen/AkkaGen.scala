package ddbt.codegen
import ddbt.ast._

/**
 * AkkaGen is responsible to transform a typed AST into distributed Akka code.
 * The main difference with ScalaGen is that every closure (i.e. the body of
 * foreach loops and add/set operations need to be distributed:
 *
 * Add/Set: the corresponding message op(key,value) is sent to the owner
 * of the map's partition
 *
 * Void closures: (closures with no return) the message CID(var1, var2, .. varN)
 * is broadcasted, where CID is the unique closure id and var1..varN are the
 * context variables at the point of call. CID encodes (map,slicing,continuation).
 * - At calling site: broadcast the message
 * - At workers receive: add a special handler for the message that is the
 *   iterating over the local portion of the map/slice and executing the continuation
 *   after the context variables var1..varN have been bound.
 *
 * Modifying closures (aggregate, group by, fetch map): two messages (forward and
 * result reply need to be created: one at workers and the other only at sender
 * (that is workers+master/master only or workers only depending where the call
 * happens).
 * - At workers: the continuation needs to create a return variable (aggregate,
 *   group) in it and reply to its parent with the result once the continuation
 *   has produced its result.
 * - At caller: the caller must register locally a special aggregation continuation
 *   that will be executed when it received _exactly_ N responses (where N is the
 *   number of nodes in the cluster.
 *
 * @author TCK
 */

/*
XXX: solve in parallel statement dependencies
XXX: break per statement parenthesis, use barrier to sync inter-statements

Issues to solve:
- move lazy map slicing into the TypeChecking ?
- move tests (TestUnit) AST into its own ddbt.ast package ?
XXX: problem: the same map can be accessed locally in a foreach but again acessed with another key which might not be on the host (Runiquecountsbya)
XXX: warning, some test are incorrect but get correct if they are run first (Rseqineq, ...)
;check -q.*ltalldynamic -dd -makka;test-only ddbt.test.gen.*
XXX: for union, instead of shipping both maps to 3rd party, why not ship one to another and make union there ? (would increase locality)
XXX: for union, instead of shipping both maps to 3rd party, why not ship one to another and make union there ? (would increase locality)
*/

// Failing   : rs_column_mapping_1, rs_column_mapping_2, tpch/query(9|10)
// No compile: -qx employee/query(61|63a|64a|65a) -qx mddb/* -qx tpch/query(2|18|21) -qx zeus/(11564068|48183500|52548748|96434723)
//             -qx (inequality_selfjoin|invalid_schema_fn|r_agtb|r_multinest|rs_columnmapping3|rs_ineqwithnestedagg|ss_math|pricespread)

class AkkaGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear}
  import scala.collection.mutable.HashMap

  // Remote functions as (map,expression,context) => (func_name,body)
  private val aggl = HashMap[(String,Expr,List[String]),(String,String)]()
  private val forl = HashMap[(String,Expr,List[String]),(String,String)]()
  private def anon(e:Expr):Expr = e.rename((n:String)=>n.replaceAll("[0-9]+","")) // anonymize the function (for use as hash key)

  // Context additional informations
  private val ref = new HashMap[String,String]() // map: name(local)->reference(remote)
  private val inuse = CtxSet() // set of variables used in the current continuation/used
  private var local = Set[String]() // locally available maps (tables+vars)
  private var local_r:String = null // map over which delegation happens (can be used only once to generate a foreach)
  var dep : Dep = null // contextual dependency tracker
  var dep2: Dep = null // aggregation dependency tracking

  // Dependency-tracking closure
  case class Dep(co:String=>String,var parent:Dep=null) extends Function1[String,String] {
    var en=false // whether dependency tracking is enabled
    lazy val name=fresh("dep")
    // wait before calling embedded continuation
    def apply(s:String):String = { val c=co(s); if (en) { if (parent!=null) parent.op((x:String)=>name+"(()=>{\n"+ind(c+x)+"\n})\n") else name+"(()=>{\n"+ind(c)+"\n})\n" } else c }
    // generate declaration
    def wrap(f:()=>String):String = { val s=f(); if (en) "val "+name+" = new Acc()\n"+s else s }
    // insert an operation introducing dependencies
    def op(f:String=>String):String = { en=true; name+".i\n"+f(name+".d\n") }
  }

  // Wrapper for remote code generation, return body and context
  def remote(m:String,fn:String,f:()=>String):(String,List[String]) = {
    local_r=m; val c=ctx.save++ctx.ctx0; val body=f(); local_r=null;
    val rc = (c.map(_._1).toSet & inuse.save).toList // context to be transferred
    ("case (`"+fn+"`,List("+rc.map(v=>v+":"+c(v).toScala).mkString(",")+")) =>\n"+ind(body),rc)
  }

  def genVar(n:String,tp:Type,ks:List[Type]=Nil) = "var "+n+(if (ks==Nil) ":"+tp.toScala+" = "+tp.zeroScala else ":M3Map["+tup(ks.map(_.toScala))+","+tp.toScala+"] = null")+"\n"

  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => inuse.add(n); super.cpsExpr(ex,co,am) // 'inuse' maintenance
    case Lift(n,e) => if (ctx.contains(n)) { inuse.add(n); cpsExpr(e,(v:String)=>co("(if ("+n+" == "+v+") 1L else 0L)"),am) }
                      else { ctx.add(n,e.tp); cpsExpr(e,(v:String)=> "lazy val "+n+" = "+v+";\n"+co("1L")) } // we are lazy to avoid evaluation before 'v' is valid
                      // XXX: 'push' in dep instead

    case m@MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)};
      if (local(n) || n==local_r || !ref.contains(n)) { if (n==local_r) local_r=null;
        if (ki.size==0) co(n+(if (ks.size>0) ".get("+tup(ks)+")" else "")) // local get
        else { // local foreach
          ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).toMap)
          val (k0,v0)=(fresh("k"),fresh("v"));

 // create a new outer, use dep as inner
          val kis = ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";\n"}.mkString
          "//dep2="+dep2+"\n"+
          n+(if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(_._1))+")" else "")+".foreach { ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
            if (dep2!=null) { val r=dep2.wrap(()=>kis+co(v0)); dep2=null; r } else kis+co(v0) // bind free variables from retrieved key
          )+"\n}\n"

        }
      } else if (ki.size==0) { // remote get (in a M3Map)
        val v=fresh("v"); inuse.add(ks.toSet+v); ctx.add(Map((v,ex.tp)));
        genVar(v,ex.tp)+(if (dep2!=null) dep2 else dep).op((x:String)=>{ "get("+ref(n)+","+tup(ks)+",("+v+"r:"+ex.tp.toScala+")=>{ "+v+"="+v+"r; "+x+" })\n"+co(v) })
      } else { // remote foreach (no dependency)
        val fn0 = fresh("ff"); local_r=n; // remote handler
        val (body0,rc)=remote(n,fn0,()=>cpsExpr(ex,co)+"co()\n")
        val (fn,body) = forl.getOrElseUpdate((n,anon(ex),rc),(fn0,body0))
        "foreach("+(ref(n)::fn::rc).mkString(",")+");\n" // local handler
      }
// ------------------------------------

    case a@Add(el,er) => val cur=ctx.save;
      if (a.agg==Nil) { cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t==a.agg => val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+s2
        case _ => val a0=fresh("add")
          def add(e:Expr):String = { val m=fmap(e); val r=if (m!=null) remote_agg(a0,m,a.agg,e,true) else cpsExpr(e,(v:String)=>a0+".add("+tup(a.agg.map(_._1))+","+v+");\n",am); ctx.load(cur); r }
          "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+add(el)+add(er)+{ local_r=a0; cpsExpr(mapRef(a0,ex.tp,a.agg),co) }
      }

    case a@AggSum(ks,e) =>
      val aks=(ks zip a.tks).filter{ case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)

      val m=fmap(e); val cur=ctx.save; inuse.add(ks.toSet)
      val co2=(v:String)=>if (ks.size==0) { inuse.add(Set(v)); ctx.add(Map((v,e.tp))); co(v) } else co(v)
      if (m==null || local(m)) {
        //super.cpsExpr(ex,co2,am) // 1-tuple projection or map available locally
        if (aks.size==0) { val a0=fresh("agg"); "var "+a0+":"+ex.tp.toScala+" = "+ex.tp.zeroScala+";\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co2(a0) } // XXX: dep2 here too for both cases
        else am match {
          case Some(t) if t==aks => cpsExpr(e,co2,am)
          case _ =>
            val a0=fresh("agg")
            val tmp=Some(aks) // declare this as summing target
            val cur = ctx.save
            val s1 = "val "+a0+" = M3Map.temp["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+tup(aks.map(_._1))+","+v+");\n",tmp);
            ctx.load(cur); s1+cpsExpr(mapRef(a0,e.tp,aks),co2)
        }
      } else {
        val a0=fresh("agg_r"); genVar(a0,ex.tp,aks.map(_._2))+remote_agg(a0,m,aks,e)+(if (aks.size==0) co2(a0) else { ctx.load(cur); local_r=a0; cpsExpr(mapRef(a0,e.tp,aks),co2) })
      }

// ------------------------------------
    case _ => super.cpsExpr(ex,co,am)
  }

// ------------------------------------
  // Get the first map with free variables (in evaluation order). Implicit 'ctx' union 'c2' is used to determine free variables.
  def fmap(e:Expr,c2:Set[String]=Set()):String = e match {
    case MapRef(n,tp,ks) if ks.exists(k=> !ctx.contains(k) && !c2.contains(k)) => n
    case Lift(n,e) => fmap(e,c2)
    case Exists(e) => fmap(e,c2) // XXX: how to catch co-located map elements? have some sort of alias-tracking?
    case Mul(l,r) => val lm=fmap(l,c2); if (lm==null) fmap(r,c2++l.collect{ case Lift(n,e) => Set(n) }) else lm
    case a@Add(l,r) => if (a.agg!=Nil) null else { val lm=fmap(l,c2); if (lm==null) fmap(r,c2) else lm }
    case _ => null
  }
  // Remote aggregation
  def remote_agg(a0:String,m:String,key:List[(String,Type)],e:Expr,add:Boolean=false):String = {
    // remote handler
    val fn0 = fresh("fa");
    val (body0:String,rc:List[String])=remote(m,fn0,()=>{ inuse.add(key.map(_._1).toSet)
      val d0=dep; dep=Dep((v:String)=>"co("+v+")\n")
      val d2=dep2; dep2=Dep(if(key.size==0) (v:String)=>a0+" += "+v+";\n" else (v:String)=>a0+".add("+tup(key.map(_._1))+","+v+");\n",dep)
      val r = dep.wrap(()=>{
        val body = (if (key.size==0) "var "+a0+":"+e.tp.toScala+" = 0;\n"+cpsExpr(e,dep2)
        else { "val "+a0+" = M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+cpsExpr(e,dep2) })
        body+dep(a0)
      })
      dep=d0;
      dep2=d2
      r
    })
    val (fn,body) = aggl.getOrElseUpdate((m,anon(e),rc),(fn0,body0))
    // local handler
    val rt = if (key.size==0) e.tp.toScala else "M3Map["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]"
    val acc = if (key.size==0) "null" else "M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()"
    (if (dep2!=null) dep2 else dep).op((x:String)=> "aggr("+ref(m)+","+fn+",Array("+rc.mkString(",")+"),"+(if (add) a0+",(_" else acc+",("+a0)+"v:"+rt+") => {\n"+ind((if (add) "" else a0+" = "+a0+"v; ")+"\n"+x)+"\n})\n")
  }
// ------------------------------------






  private var stmtCtr=0; // # of sequential statements to close
  override def genStmt(s:Stmt) = s match {
    case StmtMap(m,e,op,oi) => val r=ref(m.name); val (fop,sop)=op match { case OpAdd => ("add","+=") case OpSet => ("set","=") }
      def rd(ex:Expr):List[String] = ex.collect{ case MapRef(n,t,ks)=>Set(ref(n)) }.toList
      def pre(o:OpMap,e:Expr,clear:Boolean=true):String = { // preparation (conditional barrier) for map operation
        (if (o==OpSet && m.keys.size>0 && clear) { stmtCtr+=1; "pre("+r+",true,Array(),()=> {\nclear("+r+");\n" } else "")+
        ({ stmtCtr+=1; "pre("+r+","+(if (o==OpSet) "true" else "false" )+",Array("+rd(e).mkString(",")+"),()=>{\n" })
      }
      def mop(o:String,v:String) = o+"("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+","+v+");\n"
      val init = oi match { case None => "" case Some(ie) => ctx.load(); inuse.load(m.keys.toSet)
        val co=(v:String)=> { val v0=fresh("v"); val o=mop("set",v); "get("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+",("+v0+":"+m.tp.toScala+")=>{ if ("+v0+"==0) "+o.substring(0,o.length-1)+" })\n" }
        dep = Dep(co); pre(OpSet,ie,false)+ind(dep.wrap(()=>cpsExpr(ie,dep)))+"\n"
      }
      ctx.load(); inuse.load(m.keys.toSet); dep=Dep((v:String)=>mop(fop,v)); init+pre(op,e)+ind(dep.wrap(()=>cpsExpr(e,dep)))+"\n"
    case _ => sys.error("Unimplemented")
  }
  override def genTrigger(t:Trigger):String = { // add pre and deq/ready calls in master's triggers
    val (n,as,deq) = t.evt match { case EvtReady=>("SystemReady",Nil,"ready\n") case EvtAdd(Schema(n,cs))=>("Add"+n,cs,"deq\n") case EvtDel(Schema(n,cs))=>("Del"+n,cs,"deq\n") }
    ctx=Ctx(as.toMap); stmtCtr=0; val body=t.stmts.map(genStmt).mkString; ctx=null; val close=(0 until stmtCtr).map(_=>"})").mkString(" ")+(if (stmtCtr>0) "\n" else "")
    "def on"+n+"("+as.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ind(body+deq+close)+"\n}";
  }

  override def apply(s:System) = {
    local = s.sources.filter(s=> !s.stream).map(_.schema.name).toSet ++ s.maps.filter(m=>m.keys.size==0).map(_.name).toSet
    val refs = s.maps.zipWithIndex.map{case (m,i)=> ref.put(m.name,"map"+i); "val map"+i+" = "+i+" //MapRef\n" }.mkString
    val qs = { val mn=s.maps.zipWithIndex.map{case (m,i)=>(m.name,i)}.toMap; "val queries = List("+s.queries.map(q=>mn(q.map.name)).mkString(",")+")\n" } // queries as map indices
    val ts = s.triggers.map(genTrigger).mkString("\n\n") // triggers
    val ms = s.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s)
    def fs(xs:Iterable[(String,String)]) = { val s=xs.toList.sortBy(_._1); (s.map(_._1).zipWithIndex.map{case (n,i)=>"val "+n+" = "+i+" //FunRef\n" }.mkString,s.map(_._2+"\n").mkString) }
    val (fds,fbs) = fs(forl.values)
    val (ads,abs) = fs(aggl.values)
    val local_vars:String = {
      val vs = s.maps.filter(_.keys.size==0); if (vs.size==0) "" else
      "override def local_wr(m:MapRef,v:Any,add:Boolean) = m match {\n"+ind(vs.map{m=> val add=if (m.tp==TypeDate) m.name+" = new Date("+m.name+".getTime+vv.getTime)" else m.name+" += vv"
        "case `"+ref(m.name)+"` => val vv=if (v==null) "+m.tp.zeroScala+" else v.asInstanceOf["+m.tp.toScala+"]; if (add) "+add+" else "+m.name+" = vv\n"}.mkString+"case _ =>\n")+"\n}\n"+
      "override def local_rd(m:MapRef):Any = m match {\n"+ind(vs.map(m=> "case `"+ref(m.name)+"` => "+m.name+"\n").mkString+"case _ => sys.error(\"Var(\"+m+\") not found\")")+"\n}\n"
    }
    freshClear(); ref.clear; aggl.clear; forl.clear; local=Set()
    "class "+cls+"Worker extends WorkerActor {\n"+ind(
    "import WorkerActor._\nimport ddbt.lib.Functions._\nimport ddbt.lib.Messages._\n// constants\n"+refs+fds+ads+gc+ // constants
    "// maps\n"+ms+"\nval local = Array[M3Map[_,_]]("+s.maps.map(m=>if (m.keys.size>0) m.name else "null").mkString(",")+")\n"+local_vars+
    (if (ld0!="") "// tables content preloading\noverride def loadTables() {\n"+ind(ld0)+"\n}\nloadTables()\n" else "")+"\n"+
    "// remote foreach\ndef forl(f:FunRef,args:Array[Any],co:()=>Unit) = (f,args.toList) match {\n"+ind(fbs+"case _ => co()")+"\n}\n\n"+
    "// remote aggregations\ndef aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {\n"+ind(abs+"case _ => co(null)")+"\n}")+"\n}\n\n"+
    "class "+cls+"Master extends "+cls+"Worker with MasterActor {\n"+ind(
    "import WorkerActor._\nimport Messages._\nimport Functions._\n\n"+qs+
    "val dispatch : PartialFunction[TupleEvent,Unit] = {\n"+ind(str+"case _ => deq")+"\n}\n\n"+ts)+"\n}"
  }

  override def helper(s0:System,pkg:String) =
    "package "+pkg+"\nimport ddbt.lib._\nimport java.util.Date\n\n"+
    "object "+cls+" {\n"+ind("import Helper._\nimport WorkerActor._\n"+
    "def streams(d:String) = "+streams(s0.sources).replaceAll("Adaptor.CSV\\(([^)]+)\\)","Adaptor.CSV($1,if(d.endsWith(\"_del\")) \"ins+del\" else \"insert\")")
                                                  .replaceAll("/standard/","/\"+d+\"/")+"\n"+
    "def execute(args:Array[String],f:List[Any]=>Unit) = bench2(args,(d:String,p:Boolean)=>runLocal["+cls+"Master,"+cls+"Worker](22550,4,streams(d),p),f)\n"+
    "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    "\n})")+"\n}")+"\n}\n\n"
}


/*
  object dep { // dependency tracking context
    / *private* / var has = false // remote dependencies in the closure
    / *private* / var end = false // need to close dependencies 'dep(()=>{ ... })'
    / *private* / var loop= false // in a nested loop context
    // wait for dependencies (if needed)
    def cl(op:()=>String,flat:Boolean=false) = { if (end) { end=false; val (p,s)=if(loop&& !flat) ("dep.i\ndep_loop","dep.d\n") else ("dep",""); p+"(()=>{\n"+ind(op()+s)+"\n})\n" } else op() }
    def wrap(op:()=>String) = { has=true; end=true; "dep"+(if(loop) "_loop" else "")+".i; "+op() }
    def rst { has=false; end=false; loop=false; }
    // nesting
    def in(l:Boolean) = { val r=(has,end,loop); has=false; end=false; loop=l; r }
    def out(b:(Boolean,Boolean,Boolean)) { has|=b._1; end=has||b._2; loop=b._3; }
  }


  // Get the first map with free variables (in evaluation order). Implicit 'ctx' union 'c2' is used to determine free variables.
  def fmap(e:Expr,c2:Set[String]=Set()):String = e match {
    case MapRef(n,tp,ks) if ks.exists(k=> !ctx.contains(k) && !c2.contains(k)) => n
    case Lift(n,e) => fmap(e,c2)
    case Exists(e) => fmap(e,c2) // XXX: how to catch co-located map elements? have some sort of alias-tracking?
    case Mul(l,r) => val lm=fmap(l,c2); if (lm==null) fmap(r,c2++l.collect{ case Lift(n,e) => Set(n) }) else lm
    case a@Add(l,r) => if (a.agg!=Nil) null else { val lm=fmap(l,c2); if (lm==null) fmap(r,c2) else lm }
    case _ => null
  }


  // Remote aggregation
  def remote_agg(a0:String,m:String,key:List[(String,Type)],e:Expr,add:Boolean=false):String = {
    // remote handler
    val fn0 = fresh("fa");
    val (body0:String,rc:List[String])=remote(m,fn0,()=>{ inuse.add(key.map(_._1).toSet)
      (if (key.size==0) "var "+a0+":"+e.tp.toScala+" = 0;\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")
       else { "val "+a0+" = M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+tup(key.map(_._1))+","+v+");\n") }
      )+dep.cl(()=>"co("+a0+")\n",true)
    })
    val (fn,body) = aggl.getOrElseUpdate((m,anon(e),rc),(fn0,body0))
    // local handler
    val rt = if (key.size==0) e.tp.toScala else "M3Map["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]"
    val acc = if (key.size==0) "null" else "M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()"
    dep.wrap(()=>"aggr("+ref(m)+","+fn+",Array("+rc.mkString(",")+"),"+(if (add) a0+",(_" else acc+",("+a0)+"v:"+rt+") => { "+(if (add) "" else a0+" = "+a0+"v; ")+"dep"+(if(dep.loop) "_loop" else "")+".d })\n")

  }

  def genVar0(n:String,tp:Type,ks:List[Type]=Nil) = "var "+n+(if (ks==Nil) ":"+tp.toScala+" = "+tp.zeroScala else ":M3Map["+tup(ks.map(_.toScala))+","+tp.toScala+"] = null")+"\n"

  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => inuse.add(Set(n)); super.cpsExpr(ex,co,am) // 'inuse' maintenance
    case Lift(n,e) => if (ctx.contains(n)) { inuse.add(n); cpsExpr(e,(v:String)=>co("(if ("+n+" == "+v+") 1L else 0L)"),am) }
                      else { ctx.add(n,e.tp); cpsExpr(e,(v:String)=> "val "+n+" = "+v+";\n"+co("1L")) }
    case m@MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)};
      if (local(n) || n==local_r || !ref.contains(n)) { if (n==local_r) local_r=null;
        dep.cl(()=>{
            val bk = dep.in(true)
            if (ki.size==0) co(n+(if (ks.size>0) ".get("+tup(ks)+")" else "")) // all keys are bound
            else { val (k0,v0)=(fresh("k"),fresh("v"))
              val sl = if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(_._1))+")" else ""
              ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).toMap)
              val co0=co(v0)
              val dd = if (dep.has) "val dep_loop = new Acc()\n" else ""
              dep.out(bk) //loop=n0; dep.end=dep.has
              n+sl+".foreach { ("+k0+","+v0+") =>\n"+ind(dd+ // slice on bound variables
                ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";\n"}.mkString+co0)+"\n}\n" // bind free variables from retrieved key
            }
        })
      } else if (ki.size==0) { // remote get
        val v=fresh("v"); inuse.add(ks.toSet+v); ctx.add(Map((v,ex.tp)));
        genVar0(v,ex.tp)+dep.wrap(()=>{ "get("+ref.getOrElse(n,n)+","+(if(ks.size>0) tup(ks) else "null")+",("+v+"r:"+ex.tp.toScala+")=>{ "+v+"="+v+"r; dep"+(if(dep.loop) "_loop" else "")+".d })\n"+co(v) })
      } else { // remote foreach
        val fn0 = fresh("ff"); local_r=n; // remote handler
        val (body0,rc)=remote(n,fn0,()=>cpsExpr(ex,co)+"co()\n")
        val (fn,body) = forl.getOrElseUpdate((n,anon(ex),rc),(fn0,body0))
        dep.cl(()=>"foreach("+(ref(n)::fn::rc).mkString(",")+");\n") // local handler
      }

    case a@Add(el,er) => val cur=ctx.save;
      if (a.agg==Nil) { cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t==a.agg => val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+s2
        case _ => val a0=fresh("add")
          def add(e:Expr):String = { val m=fmap(e); val r=if (m!=null) remote_agg(a0,m,a.agg,e,true) else cpsExpr(e,(v:String)=>a0+".add("+tup(a.agg.map(_._1))+","+v+");\n",am); ctx.load(cur); r }
          "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+add(el)+add(er)+{ local_r=a0; cpsExpr(mapRef(a0,ex.tp,a.agg),co) }
      }

    case a@AggSum(ks,e) =>
      val m=fmap(e); val cur=ctx.save; inuse.add(ks.toSet)
      val co2=(v:String)=>dep.cl(()=> if (ks.size==0) { inuse.add(Set(v)); ctx.add(Map((v,e.tp))); co(v) } else co(v) )
      if (m==null || local(m)) super.cpsExpr(ex,co2,am) // 1-tuple projection or map available locally
      else {
        val aks=(ks zip a.tks).filter{ case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
        val a0=fresh("agg_r"); genVar0(a0,ex.tp,aks.map(_._2))+remote_agg(a0,m,aks,e)+(if (aks.size==0) co2(a0) else { ctx.load(cur); local_r=a0; cpsExpr(mapRef(a0,e.tp,aks),co2) })
      }
    case _ => super.cpsExpr(ex,co,am)


/ *
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) { val a0=fresh("agg"); "var "+a0+":"+ex.tp.toScala+" = "+ex.tp.zeroScala+";\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t==aks => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = M3Map.temp["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+tup(aks.map(_._1))+","+v+");\n",tmp);
          ctx.load(cur); s1+cpsExpr(mapRef(a0,e.tp,aks),co)
      }
* /
  }
*/
/*
in foreach+trigger: opening/closing (fresh context), nesting level, create level if used
in stmt/agg: wrap closure (add/dec corresponding level)
in agg: wait for aggregation completion (if needed) before continuing
*/
