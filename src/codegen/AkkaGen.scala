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
class AkkaGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear}
  import scala.collection.mutable.HashMap

  // Context informations
  var local : CtxSet = null // locally available maps
  val inuse = CtxSet() // set of variables used in the current continuation/used
  var clctr : Int=0; // closures counter "how many closures to close" (no pun intended)
  def cl(n:Int=1) { clctr+=n }

  // remote functions as (map,expression,context) => (func_name,body)
  val ref = new HashMap[String,String]() // map: name(local)->reference(remote)
  private val aggl = HashMap[(String,Expr,List[String]),(String,String)]()
  private val forl = HashMap[(String,Expr,List[String]),(String,String)]()


  /** Get the first (in evaluation order) map with free variables. (implicit 'ctx' is used to determine free variables) */
  def fmap(e:Expr):String = e match { // first map with free variables in the evaluation order (using context ctx), to be used as 'aggregation over' map
    case MapRef(n,tp,ks) if ks.exists(!ctx.contains(_)) => n
    case Lift(n,e) => fmap(e)
    case AggSum(ks,e) => fmap(e)
    case Exists(e) => fmap(e)
    case Mul(l,r) => val lm=fmap(l); if (lm==null) fmap(r) else lm
    case Add(l,r) => val lm=fmap(l); if (lm==null) fmap(r) else lm
    case _ => null
  }

  /** Wrapper for remote code generation, return body and context */
  def remote(m:String,fn:String,f:()=>String):(String,List[String]) = {
    val l0=local.save; local.load(Set(m)); val u0=inuse.save; val c=ctx.save ++ ctx.ctx0
    val body=f()
    val u=inuse.save; local.load(l0); inuse.load(u0)
    val rc = (c.map(_._1).toSet & u).toList // remote context
    ("case (`"+fn+"`,List("+rc.map(v=>v+":"+c(v).toScala).mkString(",")+")) =>\n"+ind(body),rc)
  }

  // Remote aggregation
  def ragg(a0:String,m:String,key:List[(String,Type)],e:Expr):String = {
    // remote handler
    val fn = fresh("fa");
    val (body:String,rc:List[String])=remote(m,fn,()=>{ inuse.add(key.map(_._1).toSet)
      if (key.size==0) "var "+a0+":"+e.tp.toScala+" = 0;\n"+cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+"co("+a0+")"
      else { "val "+a0+" = K3Map.temp["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+
             cpsExpr(e,(v:String)=>a0+".add("+tup(key.map(_._1))+","+v+");\n")+"co("+a0+".toMap)" }
    })
    aggl.put((m,e,rc),(fn,body))
    // local handler
    val rt = if (key.size==0) e.tp.toScala else "Map["+tup(key.map(_._2.toScala))+","+e.tp.toScala+"]"
    cl(1); "aggr("+ref(m)+","+fn+",Array[Any]("+rc.mkString(",")+"),null,null,("+a0+":"+rt+") => {\n"
  }

  override def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case Ref(n) => inuse.add(Set(n)); super.cpsExpr(ex,co,am) // 'inuse' maintenance
    case MapRef(n,tp,ks) if local(n) => inuse.add(ks.toSet); super.cpsExpr(ex,co)
    case Lift(n,e) =>
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("("+n+" == "+v+")"),am)
      else { ctx.add(Map((n,ex.tp))); cpsExpr(e,(v:String)=> "val "+n+" = "+v+";\n"+co("1")) }
    case MapRef(n,tp,ks) if local(n) => super.cpsExpr(ex,co,am)
    case m@MapRef(n,tp,ks) => val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
      // XXX: use CPS@execution
      if (ki.size==0) { cl(1); val v=fresh("v"); "get("+ref.getOrElse(n,n)+","+(if(ks.size>0) tup(ks) else "null")+",("+v+":"+ex.tp.toScala+")=>{\n"+co(v) /*+"\n});\n"*/ }
      else {
        // remote handler
        val fn = fresh("ff");
        val (body,rc)=remote(n,fn,()=>super.cpsExpr(ex,co))
        forl.put((n,ex,rc),(fn,body))
        // local handler
        "foreach("+(ref(n)::fn::rc).mkString(",")+");\n"
      }
    case a@AggSum(ks,e) => inuse.add(ks.toSet);
      val m=fmap(e);
      if (m==null) super.cpsExpr(ex,co,am) // projection only
      else {
        val a0=fresh("agg"); val aks=(ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
        ragg(a0,m,aks,e)+
        (if (aks.size==0) co(a0) else { // XXX: make zero and plus for Map[_,_]
          val ma=MapRef(a0,e.tp,aks.map(_._1)); ma.tks=aks.map(_._2); cpsExpr(ma,co)
        })
      }
    case a@Add(el,er) =>
      if (a.agg==Nil) { val cur=ctx.save; cpsExpr(el,(vl:String)=>{ ctx.load(cur); cpsExpr(er,(vr:String)=>{ctx.load(cur); co("("+vl+" + "+vr+")")},am)},am) }
      else {
        // ;toast examples/queries/simple/r_btimesa.sql -l akka -o test/x.scala;test:run-main ddbt.generated.X
        // ON - R(R_A, R_B) {
        //    mSSA[][R1_A] += (R1_A ^= R_A) * R_B * (R_A - mSSA_mR8[][]) - (mSSA_mR4[][R1_A] * R_A);
        
        // XXX: issue with onSystemReady: it should only fill local maps
        
        // XXX: introduce a semantic change such that K3Var are stored everywhere for faster access !!!!
        // XXX: rework map distribution and API
        

        val cur = ctx.save
        
        def add(a0:String,e:Expr):String = {
          val m = fmap(e)
          var r = if (m!=null) ragg(a0,m,a.agg,e);
          else {
            "val "+a0+" = K3Map.temp["+tup(a.agg.map(_._2.toScala))+","+e.tp.toScala+"]()\n"+
            super.cpsExpr(e,(v:String)=>a0+".add("+tup(a.agg.map(_._1))+","+v+");\n")
          }
          ctx.load(cur); r
        }
        // XXX: what if one side has no unbound map => call super.cpsExpr(...)
        val al=fresh("add_l"); val rl=add(al,el); //ragg(al,"__SQL_SUM_AGGREGATE_2",a.agg,el); ctx.load(cur)
        val ar=fresh("add_r"); val rr=add(ar,er); //ragg(ar,"__SQL_SUM_AGGREGATE_2",a.agg,er); ctx.load(cur)
        val (k0,v0)=(fresh("k"),fresh("v"))
        ctx.add(a.agg.toMap)
        val ks=a.agg.map(_._1)
        rl+rr+{
          "K3Helper.union("+al+","+ar+").foreach{ ("+k0+","+v0+") =>\n"+ind(
            (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+
            co(v0))+"\n}"
        }
      
        //sys.error("Union semantics")
        /*
        // XXX: use CPS@execution => get rid of (most) CPS transforms during plugin/compilation
        // XXX: use CPS@execution => get rid of (most) CPS transforms during plugin/compilation
        // XXX: use CPS@execution => get rid of (most) CPS transforms during plugin/compilation

        // aggregate left and right then merge together XXX: only if local
        val (k0,v0)=(fresh("k"),fresh("v"))
        val ks = a.agg.map(_._1)
        ral+rar+
        "("+al+"++"+ar+").foreach{ ("+k0+","+v0+") =>\n"+ind(
          (if (ks.size==1) "val "+ks(0)+" = "+k0+"\n" else ks.zipWithIndex.map{ case (v,i) => "val "+v+" = "+k0+"._"+(i+1)+"\n" }.mkString)+co(v0))+"\n}\n"
        
        //sys.error("Union required")
        // make zero and add manually
        /*
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
        */
        */
      }
    case _ => super.cpsExpr(ex,co,am)
  }

  override def genStmt(s:Stmt) = s match {
    case StmtMap(m,e,op,oi) => val r=ref(m.name); val fop=op match { case OpAdd => "add" case OpSet => "set" }
      def rd(ex:Expr):List[String] = ex.collect{ case MapRef(n,t,ks)=>Set(ref(n)) }.toList
      def set():String = { cl(2); "pre(-1,Array("+r+"),(u:Unit)=> {\nclear("+r+");\nbarrier((u:Unit)=> {\n" }
      def mop(o:String,v:String) = fop+"("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+","+v+");"
      // preparation (synchronization) for map operation
      val pre=op match { case OpAdd => cl(1); "pre("+r+",Array[MapRef]("+rd(e).mkString(",")+"),(u:Unit)=> {\n" case OpSet => set() }
      val init = oi match { case None => "" case Some(ie) => inuse.load(m.keys.toSet); cl(3)
        "pre(-1,Array("+(r::rd(ie)).mkString(",")+"),(u:Unit)=>\n"+
        "get("+r+","+(if (m.keys.size==0) "null" else tup(m.keys))+", (z:"+m.tp.toScala+") => if (z==0) {\n"+ind(cpsExpr(ie,(v:String)=>mop("set",v)))+"\n}"+
        "barrier((u:Unit)=> {\n"
      }
      inuse.load(m.keys.toSet)
      pre+init+cpsExpr(e,(v:String)=>mop(fop,v))+"\n"
    case _ => sys.error("Unimplemented")
  }

  // Add the pre and deq calls in master's triggers
  override def genTrigger(t:Trigger):String = {
    val (n,as,deq) = t.evt match {
      case EvtReady => ("SystemReady",Nil,"") // no deq as it is handled already
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs,"deq ")
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs,"deq ")
    }
    clctr=0; ctx = Ctx(as.toMap)
    val res = "def on"+n+"("+as.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") = {\n"+ind(t.stmts.map(genStmt).mkString+deq+("})"*clctr)) /*.replaceAll("\n","; println(\"x"+n+"\");\n")*/ +"\n}"
    ctx = null; clctr=0; res
  }

  override def apply(s:System) = {
    local = CtxSet(s.sources.filter(s=> !s.stream).map(_.schema.name).toSet)
    val refs = s.maps.zipWithIndex.map{case (m,i)=> ref.put(m.name,"map"+i); "val map"+i+" = MapRef("+i+")\n" }.mkString
    val ts = s.triggers.map(genTrigger).mkString("\n\n") // triggers
    val ms = s.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s)
    def fs(xs:Iterable[(String,String)]) = { val s=xs.toList.sortBy(_._1); (s.map(_._1).zipWithIndex.map{case (n,i)=>"val "+n+" = FunRef("+i+")\n" }.mkString,s.map(_._2).mkString("\n")) }
    val (fds,fbs) = fs(forl.values)
    val (ads,abs) = fs(aggl.values)
    freshClear(); ref.clear; aggl.clear; forl.clear; local=null
    "class "+cls+"Worker extends WorkerActor {\n"+ind(
    "import WorkerActor._\nimport ddbt.lib.Functions._\n// constants\n"+refs+fds+ads+gc+ // constants
    "// maps\n"+ms+"\nval local = Array[Any]("+s.maps.map(m=>m.name).mkString(",")+")\n"+
    (if (ld0!="") "// tables content preloading\n"+ld0+"\n" else "")+"\n"+
    "// remote foreach\ndef forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match {\n"+ind(fbs+(if (fbs!="") "\n" else "")+"case _ => co()")+"\n}\n\n"+
    "// remote aggregations\ndef aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {\n"+ind(abs+(if (abs!="") "\n" else "")+"case _ => co(null)")+"\n}")+"\n}\n\n"+
    "class "+cls+"Master extends "+cls+"Worker with MasterActor {\n"+ind(
    "import WorkerActor._\nimport Messages._\nimport Functions._\nimport scala.util.continuations._\n\n"+
    "val dispatch : PartialFunction[TupleEvent,Unit] = {\n"+ind(str)+"\n}\n\n"+ts)+"\n}"
  }

  override def helper(s:System,numSamples:Int=10) =
    "package ddbt.generated\nimport ddbt.lib._\nimport java.util.Date\n\n"+
    "object "+cls+" extends Helper {\n"+ind("import WorkerActor._\ndef main(args:Array[String]) {\n"+ind(
    "val (t,res) = runLocal["+cls+"Master,"+cls+"Worker](5,2251,4,"+streams(s.sources)+")\n"+ // XXX: CUSTOMIZE ARGUMENTS
    s.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+K3Helper.toStr(res("+i+"))"+"+\"\\n\")\n"}.mkString+
    "println(\"Time = \"+time(t));\n")+"\n}")+"\n}\n\n"
}

/*
Issues to solve:
- Maintaining extra (map) information such as Var->Type (akka) or Var->Symbol (LMS) for each nodes
- cluster initialization and maps distribution => make workers tell to master they want to join with their maps (all local but null maps)
- join and leave cluster preparation
- at each foreach point, possibly transform in a remote continuation if map is not local
- move lazy map slicing into the TypeChecking ?
- move a good part of the test generator directly in the code generator
- move test AST into its own ddbt.ast package ?
- shall we make unit tests part of the compiler ?

Tests previously passing (26):
Axfinder
Employee01
Employee01a
Employee02
Employee02a
Employee03
Employee03a
Employee04
Employee04a
Employee05
Employee06
Employee07
Employee10
Employee10a
Employee12a
Employee22
Rgbasumb
Rimpossibleineq
Rinstatic
Rnogroupby
Rnonjoineq
Rpossibleineq
Rselectstar
Rstarofnested
Zeus37494577
Zeus75453299
*/
