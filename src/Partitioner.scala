package ddbt
import ast._
import frontend._

import Utils._
import M3._

/**
 * Experimental partitioner
 * @author TCK
 */
object Partitioner {
  import scala.collection.mutable.HashMap
  private var sys0:System = null // system reference to access map definitions
  private var ctx0 = List[String]() // trigger context
  private var cm0 = List[MapRef]() // maps joining the context
  private var parts = List[CoPart]() // co-located maps

  case class CoPart(var maps:Set[(MapDef,List[Int])], var freq:Int) extends Ordered[CoPart] {
    override def toString = "CoPart<"+freq+"> "+maps.map(mi=>mi._1.name+"("+mi._2.mkString(",")+")").mkString(", ")
    def compare(that: CoPart) =  freq - that.freq
    // Test and merge p2 if it is a non-colliding co-partitioning
    def merge(p2:CoPart):Boolean = {
      val same = !maps.filter(x=> p2.maps(x)).isEmpty
      val self = !maps.filter(x=> !p2.maps.filter(y=>y._1==x._1 && y._2!=x._2).isEmpty ).isEmpty // avoid self-joins
      if (same && !self) { maps++=p2.maps; freq+=p2.freq; true } else false
    }
    // Test and merge p2 if it can be transformed into a non-colliding co-partitioning
    // by reducing its partitioning key, that is key(p2) is a superset key(this)
    def mergeSup(p2:CoPart):Boolean = {
      if (maps.head._2.size >= p2.maps.head._2.size) return false // cannot be a superset
      var sub = List[Int]() // filter fields
      var deny = false // duplicate partitioning (not allowed)
      maps.foreach { case (m1,i1) => p2.maps.foreach { case (m2,i2) => if (m1==m2) {
        val s=i1.map(i2.indexOf(_)); if (!s.contains(-1)) sub=s else deny=true // i2 is a superset of i1
      }}}
      if (sub.size==0 || deny) false
      else { maps++=p2.maps.map{case (m,is) => (m,sub.map(is(_))) }; freq+=p2.freq; true }
    }
  }

  def join(m1:MapRef,m2:MapRef) {
    val in = (m1.keys.toSet & m2.keys.toSet) // also ignores maps with 0-keys (variables)
    if (!in.isEmpty) {
      val maps = Set(m1,m2).map(m=> (sys0.maps.filter(x=>x.name==m.name).head,m.keys.zipWithIndex.filter(x=>in.contains(x._1)).map(_._2)))
      val p0=CoPart(maps,1)
      var found = maps.size<2 // avoid self-join on same keys
      parts.foreach { p=> if (!found && p.merge(p0)) found=true }
      if (!found) parts = p0 :: parts
    }
  }

  def expr(ex:Expr,ctx:List[MapRef]):List[MapRef] = ex match {
    case Exists(e) => expr(e,ctx)
    case Mul(l,r) => expr(r,expr(l,ctx))
    case Add(l,r) => expr(r,expr(l,ctx))
    case Cmp(l,r,op) => expr(r,expr(l,ctx))
    case Apply(fn,tp,as) => (ctx /: as)((c,a)=>expr(a,ctx))
    case Lift(n,e) => expr(e,ctx)
    case AggSum(ks,e) => expr(e,ctx)
    case m@MapRef(n,tp,ks) => (ctx:::cm0).foreach(x=>join(m,x))
      if (!(ctx0.toSet & ks.toSet).isEmpty) cm0=m::cm0; m::ctx
    case _ => ctx
  }

  def analyze(s0:System) {
    sys0=s0; parts=Nil
    s0.triggers.foreach { t => cm0=Nil
      ctx0 = (t.evt match { case EvtReady=>Nil case EvtAdd(s)=>s.fields case EvtDel(s)=>s.fields }).map(_._1)
      t.stmts.foreach { case StmtMap(m,e,_,oi) =>
        cm0.foreach(x=>join(m,x))
        if (!(ctx0.toSet & m.keys.toSet).isEmpty) cm0=m::cm0
        expr(e,List(m)); oi match { case Some(ei) => expr(ei,List(m)) case _ => }
      }
    }
    // Reduce partitioning key supersets
    var ps=parts.sorted.reverse; parts=Nil
    ps.foreach { p0 =>
      var found = false
      parts.foreach { p=> if (!found && p.mergeSup(p0)) found=true }
      if (!found) parts = p0 :: parts
    }
    // Prune colliding co-partitionings by reducing 2nd
    var perfect = true
    ps = parts.sorted.reverse; parts=Nil
    var seen = Set[MapDef]()
    ps.foreach { p0 =>
      val n=p0.maps.size
      p0.maps = p0.maps.filter(m=> !seen.contains(m._1))
      if (p0.maps.size<n) perfect=false
      if (p0.maps.size>0) {
        seen = seen ++ p0.maps.map(_._1)
        parts = p0 :: parts
      }
    }
    parts = parts.reverse

/*

==> 1. always local: single-var and tables
==> 2. co-partitioned tables
==> is_perfect

*/

    /*
    Now we need to "simulate" compilation and attach to every map ref whether it is local or not
    Also all the assignments/plus need to be either foreach or rpc calls unless the map has 0-size-key
    => local (given the key from context)

    XXX: also add context to every AST nodes?
    */


    // Count by frequency
    println("Co-partitioning ("+(if (perfect) "PERFECT" else "imperfect")+"):\n"+parts.mkString("\n"))

    sys0=null; parts=Nil
  }

  def main(args: Array[String]) {
    // Dirty front-end
    if (path_repo==null) return printf("DBT repository must be configured.")
    if (args.size<1) return printf("Usage: ddbt.Parititoner <query_sql_file>")
    val qs = exec(Array("find","test/queries","-type","f","-and","-not","-path","*/.*"),new java.io.File(path_repo))._1.split("\n").filter(x=>x.matches(".*"+args(0)+"(\\.sql)?")).sorted
    if (qs.size==0) return printf("No query selected, relax your pattern")
    if (qs.size>1) return printf("Too many queries, refine your pattern:"+qs.map(x=>"\n - "+x).mkString)
    val m3_src = Compiler.toast("m3",qs(0))._2
    val m3 = (M3Parser andThen TypeCheck)(m3_src)
    analyze(m3)
    //println(m3)
  }
}
