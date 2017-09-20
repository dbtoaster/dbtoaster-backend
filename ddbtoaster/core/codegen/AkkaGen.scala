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
Roadmap:
--------------------------------
1. De-aliasing and smarter condition filtering
   - Break add's aliased variables C[x]:=A[x]+B[x] ==> C[x]=A[a]*(a=x) + B[b]*(b=x)
   - Multi-elements Add( an Mul() nodes
   - Reorder conditions in a multiplication (to put as many related to map as possible in
   - MapRef should swallow as many conditions as possible
   - Heading conditions should be transformed into "if"s
2. Group non-colliding operations in a single multi-map pre() verification
   - Re-introduce dependency trackers where necessary (inlined in functions)
   - AxFinder's statements should be reordered and tracker should be avoided (only deq in continuation)
   - Add a 'pending local dependencies' counter on every node (similar to get/aggr):
     + Incremented when a (remote) continuation is created
     + Decremented when a remote continuation has completed
     + The barrier will wait for it
3. Sub-statement parallelism (lift/aggregation/get/add branches)
   + Annotate all candidates blocks with (read+written) variables + isRemote => dependency graph
   + Group all independent blocks (remote and local) in 1st round
   + In 2nd round, all non-remote depending on 1st + all block dependents on 1st + 2nd-non-remote
   + ...
   + finally when completed, release the barrier
4. Idea: out-of-order execution of triggers/intra-triggers statements?

Observations:
- variadic arguments are 5x faster than array for Any, Array is 20x faster than variadic for primitive types

Issues to solve (big XXX list):
- Move 'inuse' maintenance in Scala code generator => strip unnecessary key parts creation in foreach
- move lazy map slicing into the TypeChecking ?
- move tests (TestUnit) AST into its own ddbt.ast package ?
- for union, instead of shipping both maps to 3rd party, why not ship one to another and make union there ? (would increase locality)
- re-introduce intra-statement parallelization with library-level support for pending continuations (in barrier) to guarantee correctness
- distinguish between forced sequentiality (master and in aggregation/sum) and parallel execution(pure foreach)
- make both parts of an Add work in parallel
*/

class AkkaGen(cls:String="Query") extends ScalaGen(cls) {
  import M3._
  import ddbt.lib.Utils.{ ind, tup, fresh, freshClear }
  import scala.collection.mutable.HashMap
  import ddbt.frontend.Partitioning
  import ddbt.lib.TypeHelper.Scala._

  // Context additional informations
  private val ref = new HashMap[String,String]() // map: name(local)->reference(remote)
  private val inuse = CtxSet() // set of variables used in the current continuation/used
  private var part : Partitioning = null // locally available partitions
  private var lacc : (String,Type,List[(String,Type)]) = null // local accumulator to handle aggregation in nested (remote) loops as (name, result, key types)

  var cl_ctr=0;
  def cl_add(n:Int=1) { cl_ctr+=n; }
  def close(f:()=>String) = { val b=cl_ctr; cl_ctr=0; val s=f(); val n=cl_ctr; cl_ctr=b; if (n>0) s+("}"*n)+"\n" else s }

  // XXX: dependency tracking
  /*
  case class Dep(var co:String=>String, co_end:String, parent:Dep=null) extends (String=>String) {
    private var en = false // remote dependency tracking enabled
    private lazy val name = fresh("dep")
    // introduce an operation that create a dependency (hole at completion)
    def op(f:String=>String):String = { en=true; name+"c += 1\n"+f(name+"c -=1; if ("+name+"c==0) "+name+"\n") }
    // apply the continuation (wrapping if dependencies)
    def apply(v:String) = if (en) "def "+name+" {\n"+ind(co(v)+co_end)+"\n}\n" else co(v)+co_end
    // support parent: def apply(s:String):String = { val c=co(s); if (en) { if (parent!=null) parent.op((x:String)=>name+"(()=>{\n"+ind(c+x)+"\n})\n") else name+"(()=>{\n"+ind(c)+"\n})\n" } else c }

    // wrap to create declarations ahead of dependencies
    def wrap(f:()=>String) = { val r=f(); if (en) "var "+name+"c = 1\n"+r+name+"\n" else r }
    // put a wrapper around the inner continuation [use:foreach]
    def in(f:(String=>String)=>(String=>String)) { val co0=co; co=f(co0) }
  }
  */

  override def rn(n:String):String = try { ctx(n)._2 } catch { case _:Throwable => n } // get unique name (avoids nesting Lifts)

  type RFun = (String,String,String) // Remote functions as (func_name,body,context_insensitive_body)
  private var aggl = List[RFun]()
  private var forl = List[RFun]()
  private def rfun(agg:Boolean,fn:String,body:String,rc:List[String]) : (String,String) ={
    val deny0 = List("Long","Double","Date","String") ::: ref.keys.toList
    def ch(c:Char) = (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') || c=='_'
    def cmp(b1:String,b2:String):Boolean = { // compare semi-normalized body of two functions
      var p=0; var s2=b2; var deny=deny0
      do {
        val l=math.min(b1.length,s2.length); while(p<l && b1(p)==s2(p)) p+=1
        if (p==l) return b1==s2 // if (b1==s2) { println("\n\nEQUALITY:\n"+b1+"\n"+b2); true } else false
        // find variable
        while(p>0 && ch(b1(p-1))) p-=1
        var p1=p; while (p1<b1.length-1 && ch(b1(p1))) p1+=1
        var p2=p; while (p2<s2.length-1 && ch(s2(p2))) p2+=1
        if (p1==p || p2==p) return false
        // replace
        val v1=b1.substring(p,p1)
        val v2=s2.substring(p,p2)
        // do not allow remote calls [recursively renamed] types and maps renaming
        if (v1==v2 || v1.startsWith("ff") || v1.startsWith("fa") || deny.contains(v1)) return false
        deny = v1::deny // avoid loops
        s2=s2.replace(v2,v1)
      } while(true)
      false
    }
    var b=body.replace(fn,"$$$"); rc.zipWithIndex.foreach{case(n,i)=>b=b.replace(n,"$"+i+"$")} // semi normalize body
    (if (agg) aggl else forl).find(x=>cmp(x._3,b)) match {
      case Some(r) => (r._1,r._2)
      case None => if (agg) aggl=(fn,body,b)::aggl else forl=(fn,body,b)::forl; (fn,body)
    }
  }

  // Get the first map with free variables (in evaluation order). Implicit 'ctx' is used to determine free variables.
  // On top of that, c2 defines additional evaluation context
  def fmap(e:Expr,c2:Set[String]=Set()):MapRef = e match {
    case m@MapRef(n,tp,ks,_) if ks.exists(k=> !ctx.contains(k._1) && !c2.contains(k._1)) => m
    case Lift(n,e) => fmap(e,c2)
    case Exists(e) => fmap(e,c2)
    case Mul(l,r) => val lm=fmap(l,c2); if (lm==null) fmap(r,c2++l.collect{ case Lift(n,e) => List(n) }) else lm
    case a@Add(l,r) => 
      val agg = a.schema._2.filter { case(n,t)=> !ctx.contains(n) }
      if (agg!=Nil) null else { val lm=fmap(l,c2); if (lm==null) fmap(r,c2) else lm }
    case _ => null
  }

  // Wrapper for remote code generation, return body and context
  def remote(m:MapRef,fn:String,f:()=>String):(String,List[String]) = {
    val p0=part; part=p0.setLocal(m); /*val u0=inuse.save;*/ val c=ctx.save++ctx.ctx0; val body=close(f);
    val u=inuse.save; part=p0; //inuse.load(u0)
    val rc = (c.map(_._1).toSet & u).toList // remote context
    ("case (`"+fn+"`,List("+rc.map(v=>rn(v)+":"+typeToString(c(v)._1)).mkString(",")+")) =>\n"+ind(body),rc map rn)
  }

  // Remote aggregation
  def remote_agg(a0:String,m:MapRef,key:List[(String,Type)],e:Expr,add:Boolean=false):String = {
    // remote handler
    val fn0 = fresh("fa");
    val (body0:String,rc:List[String])=remote(m,fn0,()=>{ inuse.add(key.map(_._1).toSet)
      if (key.size==0) "var "+a0+":"+typeToString(e.tp)+" = 0;\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+"co("+a0+")"
      else { "val "+a0+" = M3Map.temp["+tup(key.map(x => typeToString(x._2)))+","+typeToString(e.tp)+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+tup(key.map(x=>rn(x._1)))+","+v+");\n")+"co("+a0+")" }
    })
    val (fn,body) = rfun(true,fn0,body0,rc)
    // local handler
    val rt = if (key.size==0) typeToString(e.tp) else "M3Map["+tup(key.map(x => typeToString(x._2)))+","+typeToString(e.tp)+"]"
    val acc = if (key.size==0) "null" else "M3Map.temp["+tup(key.map(x => typeToString(x._2)))+","+typeToString(e.tp)+"]()"
    cl_add(1); "aggr("+ref(m.name)+","+fn+rc.map(x=>","+rn(x)).mkString+")("+(if (add) a0+"){(_" else acc+"){("+a0)+":"+rt+") =>\n"
  }

  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => inuse.add(Set(n)); super.cpsExpr(ex,co,am) // 'inuse' maintenance
    case Lift(n,e) => if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("(if ("+rn(n)+" == "+v+") 1L else 0L)"),am)
                      else { val s=ctx.save; val r=cpsExpr(e,(v:String)=>{ ctx.add(n,(e.tp,fresh("l"))); "val "+rn(n)+" = "+v+";\n"+co("1L")}); ctx.load(s); r }
    case m@MapRef(n,tp,ks,_) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k._1)};
      if (part.local(m) || !ref.contains(n)) {
        //super.cpsExpr(ex,(v:String)=>close(()=>co(v)))
        if (ki.size==0) { inuse.add(ks.map(_._1).toSet); co(n+(if (ks.size>0) ".get("+tup(ks map { case (n, _) => rn(n) })+")" else "")) } // all keys are bound
        else { val (k0,v0)=(fresh("k"),fresh("v")); var async=false
          val s=ctx.save
          inuse.add(ko.map(_._1._1).toSet); ctx.add(v0,(ex.tp,v0));inuse.add(Set(v0));
          val sl = if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(x=>rn(x._1._1)))+")" else ""
          ctx.add(ks.filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)
          val co1=close(()=>{ val r=co(v0); if (cl_ctr>0) { async=true; n+"_c.i\n"+r+n+"_c.d\n" } else r })
          val r = (if (async) "val "+n+"_c = Acc()\n" else "")+
          n+sl+".foreach { ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
            ki.map{case (k,i)=>"val "+rn(k._1)+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";\n"}.mkString+co1)+"\n}\n"+ // bind free variables from retrieved key
            (if (async) { cl_add(1); n+"_c{\n" } else "")
          ctx.load(s)
          r
        }
      } else if (ki.size==0) {
        val v=fresh("v"); cl_add(1); inuse.add(ks.map(_._1).toSet); ctx.add(v,(ex.tp,v)); inuse.add(Set(v));
        "get("+ref.getOrElse(n,n)+","+(if(ks.size>0) tup(ks map (x => rn(x._1))) else "null")+"){("+v+":"+typeToString(ex.tp)+")=>\n"+co(v)
      } else if (lacc!=null) {
        // XXX: introduce a projection for only the relevant variables (?)
        val n0=fresh("m"); val v=fresh("v")
        remote_agg(n0,m,ki.map(_._1),m)+n0+".foreach{ case ("+tup(ki.map(_._1._1))+","+v+") =>\n"+ind(co(v))+"\n}\n"
      } else {
        // remote handler
        val fn0 = fresh("ff");
        val (body0,rc)=remote(m,fn0,()=>close(()=>cpsExpr(ex,co)+"co()"))
        val (fn,body) = rfun(false,fn0,body0,rc)
        // local handler
        "foreach("+(ref(n)::fn::rc).mkString(",")+");\n"
      }
    case a@AggSum(ks,e) => val m=fmap(e); val cur=ctx.save; inuse.add(ks.map(_._1).toSet);
      val aks = ks.filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (m==null || part.local(m)) {
        if (aks.size==0) { val a0=fresh("agg"); ctx.add(a0,(e.tp,a0)); inuse.add(a0); genVar(a0,ex.tp)+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+co(a0) } // context/use mainenance
        else super.cpsExpr(ex,co,am) // 1-tuple projection or map available locally
      } else {
        val a0=fresh("agg"); val l0=lacc; lacc=(a0,e.tp,aks); val r =remote_agg(a0,m,aks,e); lacc=l0
        r+(if (aks.size==0) { ctx.add(a0,(e.tp,a0)); inuse.add(Set(a0)); co(a0) } else { ctx.load(cur); cpsExpr(MapRef(a0,e.tp,aks,true),co) })
      }
    case a@Add(el,er) => val cur=ctx.save;
      val agg = a.schema._2.filter { case(n,t)=> !ctx.contains(n) }
      if (agg==Nil) { cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t==agg => val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+s2
        case _ => val a0=fresh("add")
          def add(e:Expr):String = { val m=fmap(e)
            val r = if (m!=null) { val l0=lacc; lacc=(a0,e.tp,agg); val r=remote_agg(a0,m,agg,e,true); lacc=l0; r }
                    else cpsExpr(e,(v:String)=>a0+".add("+tup(agg.map(x=>rn(x._1)))+","+v+");\n",am); ctx.load(cur); r
          }
          "val "+a0+" = M3Map.temp["+tup(agg.map(x => typeToString(x._2)))+","+typeToString(ex.tp)+"]()\n"+add(el)+add(er)+{ cpsExpr(MapRef(a0,ex.tp,agg,true),co) }
      }
    case _ => super.cpsExpr(ex,co,am)
  }

  override def genStmt(s:TriggerStmt) = s match {
    case TriggerStmt(m,e,op,oi) => val r=ref(m.name);
      def rd(ex:Expr,self:Boolean=false) = ((if (self) List(r) else Nil):::ex.collect{ case MapRef(n,t,ks,_)=>List(ref(n)) }).map(x=>","+x).mkString
      def pre(o:OpMap,e:Expr) = (if (o==OpSet && m.keys.size>0) { cl_add(1); "pre("+r+",false){\nclear("+r+");\n" } else "")+
                                ({ cl_add(1); "pre("+r+","+(o==OpAdd)+rd(e)+"){\n" })
      def mo(o:OpMap,v:String) = (if (o==OpSet) "set" else "add")+"("+r+","+(if (m.keys.size==0) "null" else tup(m.keys map (x => rn(x._1))))+","+v+");\n"
      val init = oi match { case None => "" case Some(ie) => ctx.load(); inuse.load(m.keys.map(_._1).toSet);
        val co=(v:String)=> { val v0=fresh("v"); val o=mo(OpSet,v); "get("+r+","+(if (m.keys.size==0) "null" else tup(m.keys map (x => rn(x._1))))+"){("+v0+":"+typeToString(m.tp)+")=> if ("+v0+"==0) "+o.substring(0,o.length-1)+" }\n" }
        cl_add(1); "pre("+r+",false"+rd(ie,true)+"){\n"+cpsExpr(ie,co)
      }
      ctx.load(); inuse.load(m.keys.map(_._1).toSet); init+pre(op,e)+cpsExpr(e,(v:String)=>mo(op,v))
  }

  override def genTrigger(t:Trigger, s0:System):String = { // add pre and deq/ready calls in master's triggers
    val (n,as,deq) = t.event match { case EventReady=>("SystemReady",Nil,"ready\n") case EventInsert(Schema(n,cs))=>("Add"+n,cs,"deq\n") case EventDelete(Schema(n,cs))=>("Del"+n,cs,"deq\n") case EventBatchUpdate(_) => sys.error("Batch updates not supported") }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap); val res="def on"+n+"("+as.map{a=>a._1+":"+typeToString(a._2)} .mkString(", ")+") {\n"+ind(close(()=>t.stmts.map(genStmt).mkString+deq))+"\n}"; ctx=null; res
  }

  override def apply(s:System) = ???
  private def helper(s0:System) =
    "import ddbt.lib._\nimport java.util.Date\n\n"+
    "object "+cls+" {\n"+ind("import Helper._\n"+
    "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long,b:Int,no_output:Boolean)=>runLocal["+cls+"Master,"+cls+"Worker](args)("+streams(s0.sources)+",p,t),f)\n"+
    "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    "\n})")+"\n}")+"\n}\n"
}
