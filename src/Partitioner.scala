package ddbt
import ast._
import frontend._

import Utils._
import M3._

/**
 * Experimental partitioner
 * 1. count pairwise all the relations between a pair of tables
 * 2. sort by frequency, create largest co-partition with most frequent
 * 3. reduce key size to merge number of co-partitioning
 *
 * @author TCK
 */
object Partitioner {
  import scala.collection.mutable.HashMap
  case class CoPart(var maps:Set[(MapDef,List[Int])], var freq:Int) extends Ordered[CoPart] {
    override def toString = "CoPart<"+freq+"> "+maps.map(mi=>mi._1.name+"("+mi._2.mkString(",")+")").mkString(", ")
    def compare(that: CoPart) = that.freq - freq // descending frequency
    def add(p2:CoPart):Boolean = if (maps==p2.maps) { freq+=p2.freq; true } else false
    def merge(p2:CoPart,tp:Int):Boolean = tp match { // merge p2 in p and return true iff
      case 0 => if ((maps.map(_._1) & p2.maps.map(_._1)).isEmpty) { maps++=p2.maps; freq+=p2.freq; true } else false // p and p2 are disjoint
      case 1 => var (share,deny) = (false,false) // p2 is a non-colliding co-partitioning (shares at least one map)
        maps.foreach { m1 => p2.maps.foreach { m2 => if (m1==m2) share=true else if (m1._1==m2._1) deny=true }}
        if (share && !deny) { maps++=p2.maps; freq+=p2.freq; true } else false
      case 2 => // p2's key can be reduced into a non-colliding co-partitioning, that is key(p2) is a superset key(this)
        if (maps.head._2.size >= p2.maps.head._2.size) return false // cannot be a superset
        var sub = List[Int]() // filter fields§
        var deny = false // duplicate partitioning (not allowed)
        maps.foreach { case (m1,i1) => p2.maps.foreach { case (m2,i2) => if (m1==m2) {
          val s=i1.map(i2.indexOf(_)); if (!s.contains(-1)) sub=s else deny=true // i2 is a superset of i1
        }}}
        if (sub.size>0 && !deny) { maps++=p2.maps.map{case (m,is) => (m,sub.map(is(_))) }; freq+=p2.freq; true } else false
    }
  }

  private var sys0:System = null // system reference to access map definitions
  private var ctx0 = List[String]() // trigger context
  private var cm0 = List[MapRef]() // maps joining the context
  private var parts = List[CoPart]() // co-located maps
  private def join(m1:MapRef,m2:MapRef) {
    val in = (m1.keys.toSet & m2.keys.toSet) // also ignores maps with 0-keys (variables)
    if (!in.isEmpty) {
      val maps = Set(m1,m2).map(m=> (sys0.maps.filter(x=>x.name==m.name).head,m.keys.zipWithIndex.filter(x=>in.contains(x._1)).map(_._2)))
      val p0=CoPart(maps,1); if (maps.size==2 && !parts.exists(p=>p.add(p0))) parts ++= List(p0)
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
    case m@MapRef(n,tp,ks) if (!sys0.sources.filter(!_.stream).map(_.schema.name).contains(n)) => // don't consider replicated tables
      (ctx:::cm0).foreach(x=>join(m,x)); if (!(ctx0.toSet & ks.toSet).isEmpty) cm0=m::cm0; m::ctx
    case _ => ctx
  }

  def apply(s0:System) : (Map[MapDef,List[Int]],Boolean) = {
    sys0=s0; parts=Nil
    s0.triggers.foreach { t => cm0=Nil
      ctx0 = (t.evt match { case EvtReady=>Nil case EvtAdd(s)=>s.fields case EvtDel(s)=>s.fields }).map(_._1)
      t.stmts.foreach { case StmtMap(m,e,_,oi) =>
        cm0.foreach(x=>join(m,x))
        if (!(ctx0.toSet & m.keys.toSet).isEmpty) cm0=m::cm0
        expr(e,List(m)); oi match { case Some(ei) => expr(ei,List(m)) case _ => }
      }
    }
    // merge without and with key reduction
    do { while (m(1)) {} } while (m(2)); m(0)
    def m(r:Int) = { var res=false; var ps=parts.sorted; parts=Nil
      ps.foreach { p0 =>
        var found=false; parts.foreach { p=> if (!found) found=p.merge(p0,r) }
        if (!found) parts=p0::parts else res=true; parts=parts.sorted
      }
      res
    }
    // prune colliding co-partitionings by reducing least frequent
    var perfect = true
    val res = CoPart(Set(),0) // final partitioning
    parts.foreach { p0=>
      val ms = p0.maps.filter(m=> !res.maps.map(_._1).contains(m._1))
      val (n,o)=(ms.size,p0.maps.size)
      if (n<o) perfect=false
      if (n>0) { res.maps++=ms; if (o>1) res.freq += (p0.freq*(n-1))/(o-1) }
    }

    /*
    Now we need to "simulate" compilation and attach to every map ref whether it is local or not
    Also all the assignments/plus need to be either foreach or rpc calls unless the map has 0-size-key
    => local (given the key from context)
    XXX: also add context to every AST nodes?
    */

    println("Co-partitioning:\n"+parts.sorted.mkString("\n"))

    sys0=null; parts=Nil
    (res.maps.toMap,perfect)
  }

  class Partitioning(part:Map[MapDef,List[Int]]) {

    def isLocal(name:String,keys:List[String]) : Boolean = {
      false
    }
    def setLocal(name:String,keys:List[String]) : Partitioning = {
      null
    }
  }

  // XXX: output the hash function
  // XXX: accept a map (name, keys) and tell whether it is local or not
  // XXX: setLocal(name:String,keys:List[String])





  def main(args: Array[String]) {
    // Dirty front-end
    if (path_repo==null) return printf("DBT repository must be configured.")
    if (args.size<1) return printf("Usage: ddbt.Parititoner <query_sql_file>")
    val qs = exec(Array("find","test/queries","-type","f","-and","-not","-path","*/.*"),new java.io.File(path_repo))._1.split("\n").filter(x=>x.matches(".*"+args(0)+"(\\.sql)?")).sorted
    if (qs.size==0) return printf("No query selected, relax your pattern")
    if (qs.size>1) return printf("Too many queries, refine your pattern:"+qs.map(x=>"\n - "+x).mkString)
    val m3_src = Compiler.toast("m3",qs(0))._2
    val m3 = (M3Parser andThen TypeCheck)(m3_src)
    val (part,perf)=apply(m3)
    println("Final ("+(if (perf) "PERFECT" else "imperfect")+") : "+part)
    //println(m3)
  }
}
