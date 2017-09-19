package ddbt.frontend

import ddbt.ast._

/**
 * Experimental partitioning. Algorithm is as follows:
 * 1. Detect all co-partitioning and count them (currently weight:=1)
 * 2. Merge non-colliding co-partitioning by descending weight according to the
 *    following rules order:
 *    a) sharing at least one map partitioning
 *    b) sharing by key reduction (similar to a) where we reduce one of the copartition's key)
 *    c) completely disjoint (no map is shared among copartitionings)
 * 3. Remove least-frequent co-partitioning and create related partitioning
 *
 * @author TCK
 */
case class Partitioning(cps:List[Partitioning.CoPart],score:Double,loc:Set[String]=Set(),cur:Option[(Partitioning.CoPart,List[String])]=None) {
  override def toString = "Partitioning (score=%.2f%%):\n".format(score*100)+cps.map(p=>" - "+p+"\n").mkString
  // XXX: to be done after the code generation renaming
  def setLocal(m:M3.MapRef) = Partitioning(cps,score,loc,Some(cps.find(p=>p.contains(m.name)) match {
    case None => val p=Partitioning.CoPart(); p.put(m.name,(0 until m.keys.size).toList); (p,m.keys.map(_._1)) // selected a non-existing partition
    case Some(p) => (p,p(m.name).map(x=>m.keys(x)._1))
  }))
  def local(m:M3.MapRef) = if (m.keys.size==0 || loc(m.name)) true else cur match { case None=>false case Some((p,ks))=>p.get(m.name) match { case None=>false case Some(is)=>is.map(x=>m.keys(x))==ks } }
}

object Partitioning extends (M3.System => (Partitioning,String)) {
  import ddbt.lib.Utils.{ ind, tup }
  import M3._
  // A co-partitioning is given by a mapping relation->partitioning keys and a frequency.
  case class CoPart(var freq:Int=0) extends scala.collection.mutable.HashMap[String,List[Int]] with Ordered[CoPart] {
    override def toString = "CoPart["+freq+"] "+map{ case (m,k)=>m+"("+k.mkString(",")+":"+ k.map(mapDefs(m).apply).mkString(",") + ")"}.mkString(", ")
    def compare(o:CoPart) = o.freq - freq // descending frequency
    def add(o:CoPart) = if (this==o) { freq+=o.freq; true } else false // freq is not verified in equality
    def merge(p2:CoPart,m:Int):Boolean = m match { // merge p2 in this and return true iff
      case 0 => if ((keys.toSet & p2.keys.toSet).isEmpty) { this++=p2; freq+=p2.freq; true } else false // this and p2 are disjoint
      case 1 => var (share,deny) = (false,false) // this and p2 are non-colliding co-partitioning and share at least one map
        for (m1<-this; m2<-p2) if (m1==m2) share=true else if (m1._1==m2._1) deny=true
        if (share && !deny) { this++=p2; freq+=p2.freq; true } else false
      case 2 => // p2 can be reduced into a non-colliding co-partitioning (key(p2) is a superset key(this))
        if (values.head.size >= p2.values.head.size) return false // cannot be a superset
        var (sub,deny) = (List[Int](),false) // filter fields
        for ((m1,i1)<-this; (m2,i2)<-p2) if (m1==m2) { val s=i1.map(i2.indexOf(_)); if (!s.contains(-1)) sub=s else deny=true } // i2 is a superset of i1
        if (sub.size>0 && !deny) { this++=p2.map{ case (m,is) => (m,sub map is) }; freq+=p2.freq; true } else false
    }
  }

  private var parts = List[CoPart]() // co-located maps
  //create a new CoPart in parts or increase its weight if exists
  private def join(m1:MapRef,m2:MapRef) {
    val in = (m1.keys.toSet & m2.keys.toSet) // also ignores maps with 0-keys (variables)
    if (!in.isEmpty) {
      val p0=CoPart(1); List(m1,m2).foreach(m=> p0.put(m.name,m.keys.zipWithIndex.filter(x=>in.contains(x._1)).map(_._2)))
      if (p0.size==2 && !parts.exists(p=>p.add(p0))) parts ++= List(p0)
    }
  }

  private var sys0:System = null // system reference to access map definitions
  private var ctx0 = List[String]() // trigger context
  private var cm0 = List[MapRef]() // maps joining the context (common map: maps that share sth with the context)
  private var tableNames = Set[String]()
  private var deltaNames = Set[String]()
  private var mapDefs = Map[String, List[String]]()

  private def expr(ex:Expr,ctx:List[MapRef]):List[MapRef] = ex match {
    case Exists(e) => expr(e,ctx)
    case Mul(l,r) => expr(r,expr(l,ctx))
    case Add(l,r) => expr(r,expr(l,ctx))
    case Cmp(l,r,op) => expr(r,expr(l,ctx))
    case Apply(fn,tp,as) => (ctx /: as)((c,a)=>expr(a,ctx))
    case Lift(n,e) => expr(e,ctx)
    case AggSum(ks,e) => expr(e,ctx)
    case m@MapRef(n,tp,ks,isTemp) if (!tableNames.contains(n) && !deltaNames.contains(n)) => // don't consider replicated tables and delta relations
      (ctx:::cm0).foreach(x=>join(m,x)); if (!(ctx0.toSet & ks.map(_._1).toSet).isEmpty) cm0=m::cm0; m::ctx
    case _ => ctx
  }

  def apply(s0:System):(Partitioning,String) = {
    sys0=s0; parts=Nil
    tableNames = s0.sources.filter(!_.stream).map(_.schema.name).toSet
    deltaNames = s0.triggers.flatMap(_.event match {
      case EventBatchUpdate(s) => List(s.deltaName) case _ => Nil
    }).toSet
    mapDefs = s0.maps.map { case m: MapDef => (m.name, m.keys.map(_._1))}.toMap
    s0.triggers.foreach { t => cm0=Nil
      ctx0 = (t.event match { 
        case EventReady => Nil 
        case EventInsert(s) => s.fields 
        case EventDelete(s) => s.fields 
        case EventBatchUpdate(s) => s.fields }).map(_._1)
      t.stmts.foreach { case StmtMap(m,e,_,oi) =>
        cm0.foreach(x=>join(m,x))
        if (!(ctx0.toSet & m.keys.map(_._1).toSet).isEmpty) cm0=m::cm0
        expr(e,List(m)); oi match { case Some(ei) => expr(ei,List(m)) case _ => }
        case m: MapDef =>
      }
    }
    // merge without and with key reduction
    do { while (m(1)) {} } while (m(2)); m(0)
    //merge
    //r: reduction defined in merge
    def m(r:Int) = { var res=false; var ps=parts.sorted; parts=Nil
      ps.foreach { p0 =>
        var found=false; parts.foreach { p=> if (!found) found=p.merge(p0,r) }
        if (!found) parts=p0::parts else res=true; parts=parts.sorted
      }
      res
    }
    // solve colliding co-partitions by dropping least frequent constraints
    val r0 = parts.map(_.freq).sum // sum of weights of all constraints
    val ps=parts; parts=Nil;

    /*
    // --- debug: count how many distinct partitioning must exist
    // test:run-main ddbt.test.Partitioner (finance/.*|tpch/query[0-9]+[a-z]?|mddb/query[12])\.sql
    val ctr = new scala.collection.mutable.HashMap[String,Set[Set[Int]]]()
    ps.foreach { p => p.foreach { case (n,is) =>
      val s = ctr.getOrElse(n,Set[Set[Int]]())
      ctr.put(n,s + is.toSet)
    }}
    var max=0
    var sum=0
    ctr.foreach { case (n,ix) => if (max<ix.size) max=ix.size; sum+=ix.size
      println("- "+n+" => "+ix.map(_.mkString(",")).mkString("; "))
    }
    println("Max: "+max+" average: %.1f".format(sum*1.0/ctr.size))
    // --- debug end
    */

    ps.foreach { p0 =>
      val ms = p0.filter{ case (m,is)=> !parts.exists(p=>p.contains(m)) }
      val (n,o)=(ms.size,p0.size) //if (n<o) perfect=false
      if (n>0) { val p=CoPart(p0.freq*(n-1)/(o-1)); p++=ms; parts=(p::parts).sorted }
    }
    val r1 = parts.map(_.freq).sum // selected constraints (approximation)
    // partitioning
    val part = Partitioning(parts,if (r0==0 || r0==r1) 1 else r1*1.0/r0,s0.sources.filter(!_.stream).map(s=>s.schema.name).toSet);
    // hashing function
    val its = s0.maps.zipWithIndex.map { 
        case (m, i) => (m.name, (i,m.keys.map(_._2))) 
      }.toMap  // name=>(index,tps)       
    val imp = scala.collection.mutable.HashMap[String,List[Int]]() // body => maprefs
    parts.foreach(_.foreach{ case (n,is) => val (i,ts)=its(n)
      val ks=is.map(i=>(if (ts.size>1) "t._"+(i+1) else "t")+(ts(i) match { case TypeLong=>"" case TypeDate=>".getTime" case _=>".##" }))
      val b="val t=k.asInstanceOf["+tup(ts.map(_.toScala))+"]; r="+ks.head+";"+ks.tail.map(k=>" r*=0xcc9e2d51; r^=(r>>>13)^("+k+");").mkString
      imp.put(b,i::imp.getOrElse(b,Nil))
    })
    val hash = if (imp.size==0) "" else "override def hash(m:MapRef,k:Any) = {\n"+ind("var r=0L;\nm match {\n"+ind(
        imp.toList.map{ case (b,is)=>"case "+is.reverse.mkString("|")+" => "+b+"\n" }.mkString+"case _ => r=k.##"
      )+"\n}\nr^=(r>>>33)^(r>>>15); (r^(r>>>3)^(r>>>7)).toInt")+"\n}\n"
    sys0=null; parts=Nil; (part,hash)
  }
}
