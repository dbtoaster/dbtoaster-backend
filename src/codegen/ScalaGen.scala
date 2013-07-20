package ddbt.codegen
import ddbt.ast._

// Generators to emit LMS nodes from AST
object ScalaGen {
  import ddbt.ast.M3._
  private var counter:Int = 0
  def fresh(name:String="x") = { counter=counter+1; name+counter }
  def ind(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll(" +$","").replace("\n","\n"+i) }
  def tpe(tp:Type):String = { val s=tp.toString; s.substring(0,1).toUpperCase+s.substring(1).toLowerCase }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  private def bnd(e:Expr):Set[String] = e match { // find bound variables
    case Lift(n,e) => bnd(e)+n
    case AggSum(ks,e) => bnd(e)++ks
    case Mul(l,r) => bnd(l)++bnd(r)
    case Add(l,r) => bnd(l)++bnd(r)
    case Exists(e) => bnd(e)
    case Apply(f,t,as) => as.flatMap(a=>bnd(a).toList).toSet
    case Cmp(l,r,op) => bnd(l)++bnd(r)
    case MapRef(n,tp,ks) => ks.toSet
    case _ => Set()
  }
  
  // Generate code bottom-up using delimited CPS and a list of bounded variables
  //   ex:expression to convert
  //   b :bounded variables
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  def cpsExpr(ex:Expr,b:Set[String],co:String=>String):String = ex match {
    // "-1" simplifications
    case Add(l,Mul(Const(typeLong,"-1"),Ref(n))) => co(cpsExpr(l,b,(ll:String)=>"("+ll+" - "+n+")"))
    case Mul(Const(typeLong,"-1"),Ref(n)) => co("-"+n)
    // -----------------------------------------------
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Ref(n) => co(n)
    case MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>b.contains(k)}
      if (ki.size==0) co(n+".get("+tup(ks)+")") // all keys are bounded
      else {
        val k0=fresh("k"); val v0=fresh("v");
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map{case (k,i)=>i})+","+tup(ko.map{case (k,i)=>k})+")" else ""
        n+sl+".foreach { case ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+co(v0))+"\n}" // bind unbounded variables from retrieved key
      }
    case Mul(el,er) => cpsExpr(el,b,(vl:String)=>{  cpsExpr(er,bnd(el)++b,(vr:String)=>co("("+vl+" * "+vr+")"))  }) // right is nested in left
    case Add(el,er) => cpsExpr(el,b,(vl:String)=>{  cpsExpr(er,b,(vr:String)=>co("("+vl+" + "+vr+")"))  }) // left and right are independent
    case Lift(n,e) => cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";\n"+co(n))
    case AggSum(ks,e) => val a0=fresh("agg"); "var "+a0+":Double = 0 //correct type???\n"+cpsExpr(e,b /*++ks.toSet*/,(v:String)=>a0+" = "+a0+" + "+v+";")+"\n"+co(a0) // XXX: we did not use ks. Problem?
    case Exists(e) => cpsExpr(e,b,(v:String)=>co("("+v+" != 0)"))
    case Apply(f,tp,as) => var app = f+"("; as.foreach { a=>cpsExpr(a,b,(v:String)=>app+v+",") }; co((if (as.size>0) app.substring(0,app.length-1) else app)+")")
    case Cmp(l,r,op) => co(cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt,b:Set[String]):String = s match {
    case StmtMap(m,e,op) =>
      val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val co = (res:String)=>m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+res+");"
      cpsExpr(e,b,co)
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  def genTrigger(t:Trigger):String = {
    val (n,as,ss) = t match {
      case TriggerReady(ss) => ("SystemReady",Nil,ss)
      case TriggerAdd(Schema(n,cs),ss) => ("Add"+n,cs,ss)
      case TriggerDel(Schema(n,cs),ss) => ("Del"+n,cs,ss)
    }
    val b=as.map{_._1}.toSet
    "def on"+n+"("+as.map{a=>a._1+":"+tpe(a._2)} .mkString(", ")+") {\n"+ind(ss.map{s=>genStmt(s,b)}.mkString("\n"))+"\n}"
  }

  // Slicing lazy indices (created only when necessary)
  private val sx = scala.collection.mutable.HashMap[String,List[List[Int]]]() // slicing indices
  def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s = sx.getOrElse(m,List[List[Int]]())
    val n = s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }
  
  def genMap(m:Map):String = {
    if (m.keys.size==0) "val "+m.name+" = new K3Var["+tpe(m.tp)+"]();"
    else {
      val tk = tup(m.keys.map(x=>tpe(x._2)))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      val ix = if (s.size==0) "Nil" else "List("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+")"
      "val "+m.name+" = K3Map.make["+tk+","+tpe(m.tp)+"]("+ix+");"
    }
  }

  def genSystem(s:System):String = {
    val ts = s.triggers.map{genTrigger(_)}.mkString("\n\n") // triggers need to be generated before maps
    val ms = s.maps.map{genMap(_)}.mkString("\n")
    val qs = "def result = "+s.queries(0).name+".toMap"
    "class TestQuery {\n"+  
    "  import scala.language.implicitConversions\n"+
    "  implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L\n\n"+
    ind(ms+"\n"+qs+"\n\n"+ts)+"\n}\n"
  }
}
/*
    // By default, we nest right part into left part
    // pairOp(el,er,"+")
    def pairOp(el:Expr,er:Expr,op:String):String = {
      def bnd(e:Expr):Set[String] = e match { // find bound variables
        case Lift(n,e) => bnd(e)+n
        case AggSum(ks,e) => bnd(e)++ks
        case Mul(l,r) => bnd(l)++bnd(r)
        case Add(l,r) => bnd(l)++bnd(r)
        case Exists(e) => bnd(e)
        case Apply(f,t,as) => as.flatMap(a=>bnd(a).toList).toSet
        case Cmp(l,r,op) => bnd(l)++bnd(r)
        case MapRef(n,tp,ks) => ks.toSet
        case _ => Set()
      }
      def agg(e:Expr):Set[String] = e match { // find aggregation variables
        case AggSum(ks,e) => ks.toSet
        case Mul(l,r) => agg(l)++agg(r)
        case Add(l,r) => agg(l)++agg(r)
        case Exists(e) => agg(e)
        case _ => Set()
      }
      // Special case if both left and right subexpression share an aggregation over the same value,
      // we want to keep them distinct loop (or ultimately do loop fusion)

      val al = agg(el)
      val ar = agg(er)
      if (!al.isEmpty && al==ar) cpsExpr(el,b,(vl:String)=>{  cpsExpr(er,b,(vr:String)=>co("("+vl+" "+op+" "+vr+")"))  }) else
      cpsExpr(el,b,(vl:String)=>{  cpsExpr(er,bnd(el)++b,(vr:String)=>co("("+vl+" "+op+" "+vr+")"))  }) 
    }

   e0 match {
    case Lift(n,e) => hoisted=hoisted+cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+"; // XXX: handle this properly ")+"\n"; co(n) // XXX: bad implementation
      // XXX: we did not introduce the variable in the later expression
    case AggSum(ks,e) =>
      val a0=fresh("agg"); val h=hoisted; hoisted=""; val c=cpsExpr(e,b,(v:String)=>a0+" = "+a0+" + "+v+";")
      hoisted=h+hoisted+"var "+a0+":Double = 0;\n"+c+"\n"; co(a0) // XXX: fix this as Double/Long wrt. type checking.
    case Exists(e) => 
      val e0=fresh("ex"); val h=hoisted; hoisted=""; val c=cpsExpr(e,b,(v:String)=>"val "+e0+" = ("+v+") != 0;")
      hoisted=h+hoisted+c+"\n"; co(e0)
    case Mul(l,r) => cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>co("("+ll+" * "+rr+")"))) // XXX: add Lift left variable to right bounded context
    case Add(l,r) => cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>co("("+ll+" + "+rr+")")))
  }
*/
