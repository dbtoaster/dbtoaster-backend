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

/*
Little problems to solve:
3. cluster initialization and maps distribution => workers tell master they want to join with their maps (all local but null maps)
4. join and leave cluster => just output message
*/


// 1. before each statement, add pre computation
// 2. at each foreach point, transform into a remote continuation, possibly with a local aggregation continuation

/*
  map messages
  map master triggers
  map worker continuations triggers
*/
/*
  def genRemote(e:Expr,ctx:Map[String,Type],co:String=>String) // this is the only thing we need to insert ?
  def genExpr(e:Expr,co:Continuation)
  def genWorker
*/

/*
From ScalaGen, methods to modify
- respond to more events (receive method)
- cpsExpr to support remote continuations
- Tag continuations with 'needs to respond to sender' when needed

- Generate 2 classes:
  - Master, handles global events streams
  - Workers: only handle internal messages

- Declare all messages/types in some common place

- Generate coherency information with list of read(option) and written(list) maps

==> move lazy map slicing into the TypeChecking ?

- move a good part of the test generator directly in the code generator
- move test AST into ddbt.ast package ?
*/

  // remote functions as (map,expression,context) => (func_name,body)
  val aggl = new java.util.HashMap[(String,Expr,List[String]),(String,String)]()
  //val forl = new java.util.HashMap[(String,Expr,List[String]),(String,String)]()

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
      val fn = fresh("fa")
      println("Ctx = "+ctx," map="+m)
      
      pushl(m)
      // generate aggregation
      println("case (`"+fn+"`,"+ctx.map(v=>"("+v+":?)::").mkString+"Nil) => <ACCUMULATOR>\n"+cpsExpr(e,b,(s:String)=>"AGG["+s+"]")+"co(ACCUMULATOR)")
      println
      popl

/*
      val fs = ks.filter{k=> !b.contains(k)} // free variables
      val agg = (ks zip a.tks).filter { case(n,t)=>fs.contains(n) } // aggregation keys as (name,type)
      if (fs.size==0) { val a0=fresh("agg"); "var "+a0+":"+ex.tp.toScala+" = 0;\n"+cpsExpr(e,b,(v:String)=>a0+" += "+v+";\n")+co(a0) }
      else am match {
        case Some(t) if t==agg => cpsExpr(e,b,co,am)
        case _ =>
          val r = { val ns=fs.map(v=>(v,fresh(v))).toMap; (n:String)=>ns.getOrElse(n,n) } // renaming function
          val a0=fresh("agg")
          val tmp=Some(agg) // declare this as summing target
          "val "+a0+" = K3Map.temp["+tup(agg.map(x=>x._2.toScala))+","+e.tp.toScala+"]()\n"+
          cpsExpr(e.rename(r),b,(v:String)=> { a0+".add("+tup(agg.map(x=>r(x._1)))+","+v+");\n" },tmp)+cpsExpr(MapRef(a0,e.tp,fs),b,co)
*/

      // local handler
      val a0=fresh("agg");
      val aks = (ks zip a.tks).filter { case(n,t)=> !b.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) "val "+a0+" = aggr["+ex.tp.toScala+"]("+(mref.get(m)::fn::ctx).mkString(",")+");\n"+co(a0)
      else {
        "val "+a0+" = aggr[HashMap["+tup(aks.map(x=>x._2.toScala))+","+e.tp.toScala+"]]("+(mref.get(m)::fn::ctx).mkString(",")+");\n"+
        cpsExpr(MapRef(a0,e.tp,aks.map(_._1)),b,co)
      }
    case _ => super.cpsExpr(ex,b,co,am)
  }

  // Add the pre and deq calls in master's triggers
  override def genTrigger(t:Trigger) = { val s=super.genTrigger(t); s.substring(0,s.length-2)+"\n  deq\n}" }
  override def genStmt(s:Stmt,b:Set[String]) = s match {
    case StmtMap(m,e,op,oi) => val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val (mr,read) = (mref.get(m.name),e.collect{ case MapRef(n,t,ks)=>Set(mref.get(n)) }.toList)
      val pre=op match { case OpAdd => "pre("+(mr::read).mkString(",")+"); " case OpSet => "barrier; clear("+mr+"); barrier; " }
      //val init = oi match { case None => "" case Some(ie) => cpsExpr(ie,b,(i:String)=>"if (get("+mr+","+(if (m.keys.size==0) "" else tup(m.keys))+")==0) set("+mr+","+(if (m.keys.size==0) "" else tup(m.keys)+",")+i+");")+"\n" }
      pre+ /*init+*/ cpsExpr(e,b,(v:String) => fop+"("+mr+","+(if (m.keys.size==0) "" else tup(m.keys)+",")+v+");")+"\n"
    case _ => sys.error("Unimplemented")
  }
  
  val mref = new java.util.HashMap[String,String]() // map name->map reference
  override def apply(s:System) = {
    val mrefs = s.maps.zipWithIndex.map{case (m,i)=> mref.put(m.name,"map"+i); "val map"+i+" = MapRef("+i+")\n" }.mkString
    
    val ts = s.triggers.map(genTrigger).mkString("\n\n") // triggers
    val ms = s.maps.map(genMap).mkString("\n") // maps
    val (str,ld0,gc) = genInternals(s)

    freshClear(); mref.clear
    "class "+cls+"Worker extends WorkerActor {\n"+ind(
    "import WorkerActor._\n// constants\n"+mrefs+ // constants
"""
//val f0 = FunRef(0) // XXX : implement all foreach and aggregation function names
//val f1 = FunRef(1)
//val f2 = FunRef(2)
//val f3 = FunRef(3)
"""+
    gc+"// maps\n"+ms+"\n"+ 
    "val local = Array[K3Map[_,_]]("+s.maps.map(m=>m.name).mkString(",")+")\n"+
    (if (ld0!="") "// tables content preloading\n"+ld0+"\n" else "")+"\n"+
    "// remote foreach\ndef forl(f:FunRef,args:Array[Any],co:Unit=>Unit) = (f,args.toList) match {\n"+ind(
    // XXX: IMPLEMENT REMOTE FOREACH HERE
    "case _ => co()")+"\n}\n\n"+
    "// remote aggregations\ndef aggl(f:FunRef,args:Array[Any],co:Any=>Unit) = (f,args.toList) match {\n"+ind(
    // XXX: IMPLEMENT REMOTE AGGREGATIONS HERE
"""
//val a0 = args(0).asInstanceOf[Long] // broker_id XXX
//val a1 = args(1).asInstanceOf[Double] // price
//  case `f0` => co(mBIDS1.slice(0,a0).aggr{ (k,v) => val a_price=k._2; val bids_price=a1 // Add/del BIDS
//    val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); v * (if (lift1 > 0L) 1L else 0L) })
//  case `f1` => co(mBIDS3.slice(0,a0).aggr{ (k,v) => val a_price=k._2; val bids_price=a1
//    val lift1 = ((if ((a_price + (-1L * bids_price)) > 1000L) 1L else 0L) + (if ((bids_price + (-1L * a_price)) > 1000L) 1L else 0L)); v * (if (lift1 > 0L) 1L else 0L) })
//  case `f2` => co(mASKS1.slice(0,a0).aggr{ (k,v) => val b_price=k._2; val asks_price=a1 // Add/del ASKS
//    val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); v * (if (lift5 > 0L) 1L else 0L) })
//  case `f3` => co(mASKS2.slice(0,a0).aggr{ (k,v) => val b_price=k._2; val asks_price=a1
//    val lift5 = ((if ((asks_price + (-1L * b_price)) > 1000L) 1L else 0L) + (if ((b_price + (-1L * asks_price)) > 1000L) 1L else 0L)); v * (if (lift5 > 0L) 1L else 0L) })
//}
"""
    // XXX: force onSystemReady in the AkkaSystem.scala implementation
    )+"\n}")+"\n}\n\n"+
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
