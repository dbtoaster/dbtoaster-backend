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
Issues to solve:
- cluster initialization and maps distribution => make workers tell to master they want to join with their maps (all local but null maps)
- join and leave cluster preparation
- at each foreach point, possibly transform in a remote continuation if map is not local
- move lazy map slicing into the TypeChecking ?
- move a good part of the test generator directly in the code generator
- move test AST into its own ddbt.ast package ?
- shall we make unit tests part of the compiler ?

XXX: problem: the same map can be accessed locally in a foreach but again acessed with another key which might not be on the host (Runiquecountsbya) 
XXX: warning, some test are incorrect but get correct if they are run first (Rseqineq, ...)
;check -q.*ltalldynamic -dd -makka;test-only ddbt.test.gen.*

XXX: for union, instead of shipping both maps to 3rd party, why not ship one to another and make union there ? (would increase locality)
XXX: for union, instead of shipping both maps to 3rd party, why not ship one to another and make union there ? (would increase locality)

Results:
- Syntax    :  36
- Semantics :  42
- Incorrect :   7
- Correct   :  97
*/

class AkkaGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear}
  import scala.collection.mutable.HashMap
  
  // Context additional informations
  private val ref = new HashMap[String,String]() // map: name(local)->reference(remote)
  private val inuse = CtxSet() // set of variables used in the current continuation/used
  private var local = Set[String]() // locally available maps (tables+vars)
  private var local_r:String = null // map over which delegation happens (can be used only once to generate a foreach)
  private var local_a:String = null // aggregation accumulator
  
  var cl_ctr=0;
  def cl_add(n:Int=1) { cl_ctr+=n; }
  def close(f:()=>String) = {
    val b=cl_ctr; cl_ctr=0; val s=f(); val n=cl_ctr; cl_ctr=b;
    if (n>0) s+(0 until n).map(x=>"})").mkString(" ")+"\n" else s
  }

  // Remote functions as (map,expression,context) => (func_name,body)
  private val aggl = HashMap[(String,Expr,List[String]),(String,String)]()
  private val forl = HashMap[(String,Expr,List[String]),(String,String)]()
  private def anon(e:Expr):Expr = e.rename((n:String)=>n.replaceAll("[0-9]+","")) // anonymize the function (for use as hash key)

  // Get the first map with free variables (in evaluation order). Implicit 'ctx' is used to determine free variables.
  // On top of that, c2 defines additional evaluation context
  def fmap(e:Expr,c2:Set[String]=Set()):String = e match {
    case MapRef(n,tp,ks) if ks.exists(k=> !ctx.contains(k) && !c2.contains(k)) => n
    case Lift(n,e) => fmap(e,c2)
    case Exists(e) => fmap(e,c2)
    case Mul(l,r) => val lm=fmap(l,c2); if (lm==null) fmap(r,c2++l.collect{ case Lift(n,e) => Set(n) }) else lm
    case Add(l,r) => val lm=fmap(l,c2); if (lm==null) fmap(r,c2) else lm
    case _ => null
  }

  // Wrapper for remote code generation, return body and context
  def remote(m:String,fn:String,f:()=>String):(String,List[String]) = {
    local_r=m; val u0=inuse.save; val c=ctx.save ++ ctx.ctx0
    val body=close(f);
    val u=inuse.save; local_r=null; inuse.load(u0)
    val rc = (c.map(_._1).toSet & u).toList // remote context
    ("case (`"+fn+"`,List("+rc.map(v=>v+":"+c(v).toScala).mkString(",")+")) =>\n"+ind(body),rc)
  }

  // Remote aggregation
  def remote_agg(a0:String,m:String,key:List[(String,Type)],e:Expr,add:Boolean=false):String = {
    // remote handler
    val fn0 = fresh("fa");
    val (body0:String,rc:List[String])=remote(m,fn0,()=>{ inuse.add(key.map(_._1).toSet)
      if (key.size==0) "var "+a0+":"+e.tp.toScala+" = 0;\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+"co("+a0+")"
      else { "val "+a0+" = M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+
             //XXX: ensure here coherency
             cpsExpr(e,(v:String)=>a0+".add("+tup(key.map(_._1))+","+v+"); /*HERE*/\n")+"co("+a0+")" }
    })
    val (fn,body) = aggl.getOrElseUpdate((m,anon(e),rc),(fn0,body0))
    // local handler
    val rt = if (key.size==0) e.tp.toScala else "M3Map["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]"
    val acc = if (key.size==0) "null" else "M3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()"
    cl_add(1);
    if (add) "aggr("+ref(m)+","+fn+",Array[Any]("+rc.mkString(",")+"),"+a0+",(_:"+rt+") => {\n"
    else "aggr("+ref(m)+","+fn+",Array[Any]("+rc.mkString(",")+"),"+acc+",("+a0+":"+rt+") => {\n"
  }
  
  // Ensures that all continuations in the loop over the intermediate map are terminated
  def agg_co(a0:String,keys:List[(String,Type)],co:String=>String):String = {
    var async=false
    val (k0,v0)=(fresh("k"),fresh("v"))
    val co1=close(()=>{ val r=co(v0); if (cl_ctr>0) { async=true; a0+"_c.i // <---\n"+r+a0+"_c.d // <---\n" } else r })
    (if (async) "val "+a0+"_c = Acc()\n" else "")+a0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
      (if (keys.size==1) "val "+keys(0)._1+" = "+k0+"\n" else keys.map(_._1).zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co1)+"\n}\n"+
      (if (async) { cl_add(1); a0+"_c((_:Unit) => {\n" } else "")
  }
  
  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => inuse.add(Set(n)); super.cpsExpr(ex,co,am) // 'inuse' maintenance
    case Lift(n,e) => if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("(if ("+n+" == "+v+") 1L else 0L)"),am)
                      else { ctx.add(Map((n,e.tp))); cpsExpr(e,(v:String)=> "val "+n+" = "+v+";\n"+co("1L")) }
    case m@MapRef(n,tp,ks) =>
      if (local(n) || n==local_r) { if (n==local_r) local_r=null; super.cpsExpr(ex,(v:String)=>close(()=>co(v))) }
      else if (ks.filter(!ctx.contains(_)).size==0) { val v=fresh("v"); cl_add(1); "get("+ref.getOrElse(n,n)+","+(if(ks.size>0) tup(ks) else "null")+",("+v+":"+ex.tp.toScala+")=>{\n"+co(v) }
      else {
        // remote handler
        val fn0 = fresh("ff"); local_r=n;
        val (body0,rc)=remote(n,fn0,()=>close(()=>cpsExpr(ex,co)+"co()"))
        val (fn,body) = forl.getOrElseUpdate((n,anon(ex),rc),(fn0,body0))
        // local handler
        "foreach("+(ref(n)::fn::rc).mkString(",")+");\n"
      }
    case a@AggSum(ks,e) => val m=fmap(e); inuse.add(ks.toSet);
      if (m==null || local(m)) super.cpsExpr(ex,co,am) // 1-tuple projection or map available locally
      else {
        val a0=fresh("agg"); val aks=(ks zip a.tks).filter{ case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
        remote_agg(a0,m,aks,e)+(if (aks.size==0) co(a0) else { val ma=MapRef(a0,e.tp,aks.map(_._1)); ma.tks=aks.map(_._2); local_r=a0; cpsExpr(ma,co) })
      }
    case a@Add(el,er) =>
      if (a.agg==Nil) { val cur=ctx.save; cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else am match {
        case Some(t) if t==a.agg => val cur=ctx.save; val s1=cpsExpr(el,co,am); ctx.load(cur); val s2=cpsExpr(er,co,am); ctx.load(cur); s1+s2
        case _ => val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          def add(a0:String,e:Expr):String = { val cur=ctx.save; val m=fmap(e)
            val r = if (m!=null) remote_agg(a0,m,a.agg,e,true) else super.cpsExpr(e,(v:String)=>a0+".add("+tup(a.agg.map(_._1))+","+v+");\n")
            ctx.load(cur); r
          }
          "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+"// ---------\n"+add(a0,el)+"\n// ---------\n"+add(a0,er)+"\n// ---------\n"+
          agg_co(a0,a.agg,co)
          
          /*
          var async=false
          val co1=close(()=>{ val r=co(v0); if (cl_ctr>0) { async=true; a0+"_c.i // <---\n"+r+a0+"_c.d // <---\n" } else r })
          
          if (async) cl_add(1)
          
          val ks = a.agg.map(_._1)
          "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+"// ---------\n"+add(a0,el)+"\n// ---------\n"+add(a0,er)+"\n// ---------\n"+
          (if (async) "val "+a0+"_c = Acc()\n" else "")+
          // HERE WE MUST ENSURE THAT WE ADD CORRECTLY
          a0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co1)+"\n}\n"+
          (if (async) a0+"_c((_:Unit) => {\n" else "")
          */

/*
// XXX: distinguish when in an aggregation and when not
          / *
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>a0+".add("+tup(ks)+","+v+");\n",tmp); ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>a0+".add("+tup(ks)+","+v+");\n",tmp); ctx.load(cur)
          ctx.add(a.agg.toMap)
          "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+ex.tp.toScala+"]()\n"+
          "val "+a0+"_acc = Acc()\n"+
          s1+s2+
          a0+".foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}\n"
          * /

        def add(a0:String,e:Expr):String = { val cur=ctx.save; val m=fmap(e)
          var r = if (m!=null) ragg(a0,m,a.agg,e) else {
            "val "+a0+" = M3Map.temp["+tup(a.agg.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+
            super.cpsExpr(e,(v:String)=>a0+".add("+tup(a.agg.map(_._1))+","+v+");\n")
          }
          ctx.load(cur); r
        }
        val al=fresh("add_l"); val rl=add(al,el);
        val ar=fresh("add_r"); val rr=add(ar,er);
        val (k0,v0)=(fresh("k"),fresh("v")); val ks=a.agg.map(_._1); ctx.add(a.agg.toMap)
        rl+rr+ar+".sum("+al+");\n"+al+".foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}\n"

*/
      }
    case _ => super.cpsExpr(ex,co,am)
  }

  override def genStmt(s:Stmt) = s match {
    case StmtMap(m,e,op,oi) => val r=ref(m.name); val (fop,sop)=op match { case OpAdd => ("add","+=") case OpSet => ("set","=") }
      def rd(ex:Expr):List[String] = ex.collect{ case MapRef(n,t,ks)=>Set(ref(n)) }.toList
      def pre(o:OpMap,e:Expr) = o match { // preparation (optional barrier) for map operation
        case OpSet if m.keys.size>0 => cl_add(2); "pre(-1,Array("+r+"),(_:Unit)=> {\nclear("+r+");\nbarrier((_:Unit)=> {\n"
        case _ => cl_add(1); "pre("+r+",Array[MapRef]("+rd(e).mkString(",")+"),(_:Unit)=> {\n"
      }
      def mop(o:String,v:String) = o+"("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+","+v+");\n"
      val init = oi match { case None => "" case Some(ie) => inuse.load(m.keys.toSet); cl_add(3)
        "pre(-1,Array("+(r::rd(ie)).mkString(",")+"),(_:Unit)=>\n"+
        "get("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+", (z:"+m.tp.toScala+") => if (z==0) {\n"+ind(cpsExpr(ie,(v:String)=>mop("set",v)))+"\n}\n"+
        "barrier((_:Unit)=> {\n"
      }
      inuse.load(m.keys.toSet)
      init+pre(op,e)+cpsExpr(e,(v:String)=>mop(fop,v))
    case _ => sys.error("Unimplemented")
  }

  override def genTrigger(t:Trigger):String = { // add pre and deq/ready calls in master's triggers
    val (n,as,deq) = t.evt match { case EvtReady=>("SystemReady",Nil,"ready\n") case EvtAdd(Schema(n,cs))=>("Add"+n,cs,"deq\n") case EvtDel(Schema(n,cs))=>("Del"+n,cs,"deq\n") }
    ctx=Ctx(as.toMap); val res="def on"+n+"("+as.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") {\n"+ind(close(()=>t.stmts.map(genStmt).mkString+deq))+"\n}"; ctx=null; res
  }

  override def apply(s:System) = {
    local = s.sources.filter(s=> !s.stream).map(_.schema.name).toSet ++ s.maps.filter(m=>m.keys.size==0).map(_.name).toSet
    val refs = s.maps.zipWithIndex.map{case (m,i)=> ref.put(m.name,"map"+i); "val map"+i+" = MapRef("+i+")\n" }.mkString
    val qs = { val mn=s.maps.zipWithIndex.map{case (m,i)=>(m.name,i)}.toMap; "val queries = List("+s.queries.map(q=>mn(q.map.name)).mkString(",")+")\n" } // queries as map indices
    val ts = s.triggers.map(genTrigger).mkString("\n\n") // triggers
    val ms = s.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s)
    def fs(xs:Iterable[(String,String)]) = { val s=xs.toList.sortBy(_._1); (s.map(_._1).zipWithIndex.map{case (n,i)=>"val "+n+" = FunRef("+i+")\n" }.mkString,s.map(_._2).mkString("\n")) }
    val (fds,fbs) = fs(forl.values)
    val (ads,abs) = fs(aggl.values)
    val local_vars:String = {
      val vs = s.maps.filter(_.keys.size==0); if (vs.size==0) "" else
      "override def local_wr(m:MapRef,v:Any,add:Boolean) = m match {\n"+ind(vs.map{m=>
        val add = if (m.tp==TypeDate) m.name+" = new Date("+m.name+".getTime+vv.getTime)" else m.name+" += vv"
        "case `"+ref(m.name)+"` => val vv=v.asInstanceOf["+m.tp.toScala+"]; if (add) "+add+" else "+m.name+" = vv\n"}.mkString+"case _ =>\n")+"\n}\n"+
      "override def local_rd(m:MapRef):Any = m match {\n"+ind(vs.map(m=> "case `"+ref(m.name)+"` => "+m.name+"\n").mkString+"case _ => sys.error(\"Var(\"+m+\") not found\")")+"\n}\n"
    }
    freshClear(); ref.clear; aggl.clear; forl.clear; local=Set()
    "class "+cls+"Worker extends WorkerActor {\n"+ind(
    "import WorkerActor._\nimport ddbt.lib.Functions._\n// constants\n"+refs+fds+ads+gc+ // constants
    "// maps\n"+ms+"\nval local = Array[M3Map[_,_]]("+s.maps.map(m=>if (m.keys.size>0) m.name else "null").mkString(",")+")\n"+local_vars+
    (if (ld0!="") "// tables content preloading\n"+ld0+"\n" else "")+"\n"+
    "// remote foreach\ndef forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match {\n"+ind(fbs+(if (fbs!="") "\n" else "")+"case _ => co()")+"\n}\n\n"+
    "// remote aggregations\ndef aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {\n"+ind(abs+(if (abs!="") "\n" else "")+"case _ => co(null)")+"\n}")+"\n}\n\n"+
    "class "+cls+"Master extends "+cls+"Worker with MasterActor {\n"+ind(
    "import WorkerActor._\nimport Messages._\nimport Functions._\nimport scala.util.continuations._\n\n"+qs+
    "val dispatch : PartialFunction[TupleEvent,Unit] = {\n"+ind(str+"case _ => deq")+"\n}\n\n"+ts)+"\n}"
  }

  override def helper(s:System,numSamples:Int=10) =
    "package ddbt.generated\nimport ddbt.lib._\nimport java.util.Date\n\n"+
    "object "+cls+" extends Helper {\n"+ind("import WorkerActor._\ndef main(args:Array[String]) {\n"+ind(
    "val (t,res) = runLocal["+cls+"Master,"+cls+"Worker]("+s.maps.size+",2251,4,"+streams(s.sources)+")\n"+ // XXX: CUSTOMIZE ARGUMENTS
    s.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))"+"+\"\\n\")\n"}.mkString+
    "println(\"Time = \"+time(t));\n")+"\n}")+"\n}\n\n"
}
