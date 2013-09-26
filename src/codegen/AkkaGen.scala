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

/*
Issues to solve:
- Maintaining extra (map) information such as type (akka) or symbol (LMS) for each nodes
- cluster initialization and maps distribution => make workers tell to master they want to join with their maps (all local but null maps)
- join and leave cluster preparation
- at each foreach point, possibly transform in a remote continuation if map is not local
- move lazy map slicing into the TypeChecking ?
- move a good part of the test generator directly in the code generator
- move test AST into its own ddbt.ast package ?
- shall we make unit tests part of the compiler ?
*/
  // remote functions as (map,expression,context) => (func_name,body)
  private val aggl = HashMap[(String,Expr,List[String]),(String,String)]()
  private val forl = HashMap[(String,Expr,List[String]),(String,String)]()

  // variables being used in the subexpression
  def used(e:Expr):Set[String] = e.collect{ case Ref(n)=>Set(n) case MapRef(n,t,ks)=>ks.toSet case AggSum(ks,e)=>ks.toSet++used(e) }

  private var mapl:List[String] = Nil // context stack of 1 map allowed to be used locally
  def pushl(m:String) { mapl=m::mapl }
  def popl() { mapl = if (mapl==Nil) Nil else mapl.tail }

  def fmap(e:Expr,b:Set[String]):String = e match { // first map with free variables in the evaluation order, to be used as 'aggregation over' map
    case MapRef(n,tp,ks) if (ks.toSet &~ b).size>0 => n
    case Lift(n,e) => fmap(e,b)
    case AggSum(ks,e) => fmap(e,b)
    case Exists(e) => fmap(e,b)
    case Mul(l,r) => val lm=fmap(l,b); if (lm==null) fmap(r,b) else lm
    case Add(l,r) => val lm=fmap(l,b); if (lm==null) fmap(r,b) else lm
    case _ => null
  }
  
  override def cpsExpr(ex:Expr,b:Set[String]=Set(),co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match {
    case MapRef(n,tp,ks) if (n==mapl.head) => super.cpsExpr(ex,b,co)
    case MapRef(n,tp,ks) => co("<XXX>")
    case a@AggSum(ks,e) =>
      val ctx = (b&used(e)).toList // context to be passed remotely
      val m=fmap(e,b); if (m==null) sys.error("No aggregation map")
      val a0=fresh("agg"); val aks=(ks zip a.tks).filter { case(n,t)=> !b.contains(n) } // aggregation keys as (name,type)
      // remote handler      
      val (fn,body) = aggl.getOrElseUpdate((m,e,ctx),{ // XXX: rename such that we could match aliases where only bound variable names differ
        val fn = fresh("fa"); pushl(m)
        val body = "case (`"+fn+"`,"+ctx.map(v=>"("+v+":?)::").mkString+"Nil) =>\n"+ind(
          if (aks.size==0) "var "+a0+":"+ex.tp.toScala+" = 0;\n"+cpsExpr(e,b,(v:String)=>a0+" += "+v+";\n")+"co("+a0+")"
          else {
            val r = { val ns=aks.map(v=>(v._1,fresh(v._1))).toMap; (n:String)=>ns.getOrElse(n,n) } // renaming function
            "val "+a0+" = K3Map.temp["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]()\n"+
            cpsExpr(e.rename(r),b,(v:String)=>a0+".add("+tup(aks.map(x=>r(x._1)))+","+v+");\n")+"co("+a0+".toMap)"
          }
        )
        popl; (fn,body)
      })
      // local handler
      if (aks.size==0) "val "+a0+" = aggr["+ex.tp.toScala+"]("+(mref(m)::fn::ctx).mkString(",")+");\n"+co(a0)
      else {
        "val "+a0+" = aggr[HashMap["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]]("+(mref(m)::fn::ctx).mkString(",")+");\n"+
        cpsExpr(MapRef(a0,e.tp,aks.map(_._1)),b,co)
      }
    case _ => super.cpsExpr(ex,b,co,am)
  }

  // Add the pre and deq calls in master's triggers
  override def genTrigger(t:Trigger):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    val b=as.map{_._1}.toSet
    "def on"+n+"("+as.map{a=>a._1+":"+a._2.toScala} .mkString(", ")+") = "+(if (t.stmts.size>0) "reset" else "")+" {\n"+ind(t.stmts.map{s=>genStmt(s,b)}.mkString+"deq")+"\n}"
  }
  
  override def genStmt(s:Stmt,b:Set[String]) = s match {
    case StmtMap(m,e,op,oi) => val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val (mr,read) = (mref(m.name),e.collect{ case MapRef(n,t,ks)=>Set(mref(n)) }.toList)
      val pre=op match { case OpAdd => "pre("+(mr::read).mkString(",")+"); " case OpSet => "barrier; clear("+mr+"); barrier; " }
      //val init = oi match { case None => "" case Some(ie) => cpsExpr(ie,b,(i:String)=>"if (get("+mr+","+(if (m.keys.size==0) "" else tup(m.keys))+")==0) set("+mr+","+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n" }
      pre+ /*init+*/ cpsExpr(e,b,(v:String) => fop+"("+mr+","+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
    case _ => sys.error("Unimplemented")
  }
  
  val mref = new HashMap[String,String]() // map name->map reference
  override def apply(s:System) = {
    val mrefs = s.maps.zipWithIndex.map{case (m,i)=> mref.put(m.name,"map"+i); "val map"+i+" = MapRef("+i+")\n" }.mkString
    
    val ts = s.triggers.map(genTrigger).mkString("\n\n") // triggers
    val ms = s.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s)
    
    def fs(xs:Iterable[(String,String)]) = { val s=xs.toList.sortBy(_._1); (s.map(_._1).zipWithIndex.map{case (n,i)=>"val "+n+" = FunRef("+i+")\n" }.mkString,s.map(_._2).mkString("\n")) }
    val (fds,fbs) = fs(forl.values)
    val (ads,abs) = fs(aggl.values)
    
    // XXX: force onSystemReady in the AkkaSystem.scala implementation

    freshClear(); mref.clear; aggl.clear; forl.clear
    "class "+cls+"Worker extends WorkerActor {\n"+ind(
    "import WorkerActor._\n// constants\n"+mrefs+fds+ads+gc+ // constants
    "// maps\n"+ms+"\nval local = Array[K3Map[_,_]]("+s.maps.map(m=>m.name).mkString(",")+")\n"+
    (if (ld0!="") "// tables content preloading\n"+ld0+"\n" else "")+"\n"+
    "// remote foreach\ndef forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match {\n"+ind(fbs+"case _ => co()")+"\n}\n\n"+
    "// remote aggregations\ndef aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {\n"+ind(abs+"case _ => co(null)")+"\n}")+"\n}\n\n"+
    "class "+cls+"Master extends "+cls+"Worker with MasterActor {\n"+ind(
    "import WorkerActor._\nimport Messages._\nimport scala.util.continuations._\n\n"+
    "val dispatch : PartialFunction[TupleEvent,Unit] = {\n"+ind(str)+"\n}\n\n"+ts)+"\n}"
  }

  override def helper(s:System,numSamples:Int=10) = 
    "package ddbt.generated\nimport ddbt.lib._\nimport java.util.Date\n\n"+
    "object "+cls+" extends Helper {\n"+ind("import WorkerActor._\ndef main(args:Array[String]) {\n"+ind(
    "val (t,res) = runLocal["+cls+"Master,"+cls+"Worker](5,2251,4,"+streams(s.sources)+")\n"+ // XXX: CUSTOMIZE ARGUMENTS
    s.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+K3Helper.toStr(res("+i+"))"+"+\"\\n\")\n"}.mkString+
    "println(\"Time = \"+time(t));\n")+"\n}")+"\n}\n\n"
}
