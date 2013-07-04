// Generators to emit LMS nodes from AST

package ddbt.codegen
import ddbt.ast._

object ScalaGen {
  def i(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll(" +$","").replace("\n","\n"+i) }
  def tpe(tp:Type):String = { val s=tp.toString; s.substring(0,1).toUpperCase+s.substring(1).toLowerCase }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  private var counter:Int = 0
  def fresh(name:String="x") = { counter=counter+1; name+counter }


  // e0:expression to convert
  // b0:bound variables
  // d0:delimited continuation function (code with 'holes' to be filled by expression) Rep[Expr]=>Rep[Unit]
  import ddbt.ast.M3._
  
  // use delimited CPS to generate code
  // we construct bottom-up, generate the code, and the list of unbounded variables

  // Hoisting: not very clean design, use 2x2 continuation ?
  var hoisted:String = "";
  def cpsExpr(e0:Expr,b:Set[String],co:String=>String):String = e0 match {
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Ref(n) => co(n)
    case MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.span{case(k,i)=> b.contains(k)}
      if (ki.size==0) co(n+".get("+tup(ks)+")") // all keys are bounded
      else {
        val k0=fresh("k"); val v0=fresh("v"); var c=co(v0); val h=hoisted; hoisted=""
        n+ko.map{case (k,i)=>".slice("+i+","+k+")"}.mkString+".foreach { case ("+k0+","+v0+") =>\n"+i( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+ // bind unbounded variables from retrieved key
          h+c)+"\n}"
      }  
    case Lift(n,e) => hoisted=hoisted+cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";")+"\n"; co(n)
      // XXX: we did not introduce the variable in the later expression
    
    case AggSum(ks,e) =>
     //val a0=fresh("a"); co("{\n"+i("var "+a0+":<<<XXX>>> = 0;\n"+cpsExpr(e,b,(v:String)=>a0+" = "+a0+" + "+v+";")+"\n"+a0)+"\n}")
     val a0=fresh("agg"); val h=hoisted; hoisted=""; val c=cpsExpr(e,b,(v:String)=>a0+" = "+a0+" + "+v+";")
     hoisted=h+hoisted+"var "+a0+":<<<XXX>>> = 0;\n"+c+"\n"; co(a0)
     
    // "-1" simplifications
    case Add(l,Mul(Const(typeLong,"-1"),Ref(n))) => co(cpsExpr(l,b,(ll:String)=>"("+ll+" - "+n+")"))
    case Mul(Const(typeLong,"-1"),Ref(n)) => co("-"+n)
    // End

    case Mul(l,r) => cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>co("("+ll+" * "+rr+")"))) // XXX: add Lift left variable to right bounded context
    case Add(l,r) => cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>co("("+ll+" + "+rr+")")))
    case Exists(e) => cpsExpr(e,b,(v:String)=>"EXISTS("+co(v)+")")
    
    case Apply(f,tp,as) => var app = f+"("; as.foreach { a=>cpsExpr(a,b,(v:String)=>app+v+",") }; co((if (as.size>0) app.substring(0,app.length-1) else app)+")")
    case Cmp(l,r,op) => co(cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case Tuple(_,_) => sys.error("Tuple should not appear")
  }

  def genStmt(s:Stmt,b:Set[String]):String = s match {
    case StmtMap(m,e,op) =>
      def bnd(e:Expr):Set[String] = e match {
        case Lift(n,e) => bnd(e)+n
        case AggSum(ks,e) => bnd(e)
        case Mul(l,r) => bnd(l)++bnd(r)
        case Add(l,r) => bnd(l)++bnd(r)
        case Exists(e) => bnd(e)
        case Apply(f,t,as) => as.flatMap(a=>bnd(a).toList).toSet
        case Cmp(l,r,op) => bnd(l)++bnd(r)
        case _ => Set()
      }
      val (ko,ki) = m.keys.zipWithIndex.span{case(k,i)=> (b++bnd(e)).contains(k)} // we also use bounds from right expression
      val fop=op match { case OpAdd => "add" case OpSet => "set" }
      val fun = m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")
      val co = if (ki.size==0) (res:String)=>fun+res+");" // all keys are bounded
      else { val k0=fresh("k"); val v0=fresh("v");
        (res:String)=>m.name+ko.map{case (k,i)=>".slice("+i+","+k+")"}.mkString+".foreach { case ("+k0+","+v0+") =>\n"+i( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+ // bind unbounded variables from retrieved key
          fun+res+");")+"\n}"
      }
      val r = cpsExpr(e,b,co); val h=hoisted; hoisted=""; h+r
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }
  
  def genTrigger(t:Trigger):String = {
    val (n,as,ss) = t match {
      case TriggerReady(ss) => ("SystemReady",Nil,ss)
      case TriggerAdd(Schema(n,cs),ss) => ("Add"+n,cs,ss)
      case TriggerDel(Schema(n,cs),ss) => ("Del"+n,cs,ss)
    }
    val b=as.map{_._1}.toSet
    "def on"+n+"("+as.map{a=>a._1+":"+tpe(a._2)} .mkString(", ")+") {\n"+i(ss.map{s=>genStmt(s,b)}.mkString("\n"))+"\n}"
  }
  
  def genMap(m:Map):String = {
    if (m.keys.size==0) "val "+m.name+" = new K3Var["+tpe(m.tp)+"](0);"
    else "val "+m.name+" = K3Map.create["+tup(m.keys.map(x=>tpe(x._2)))+","+tpe(m.tp)+"](0,List("+"<<<SECONDARY_INDICES>>>"+"));"
  }

  def genSystem(s:System):String = {
    // import scala.language.implicitConversions  
    // implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
    
    // XXX: fix map to have a map(Int=>Index) instead of a List(Index)
    
    "class TestQuery {\n"+  
    i(s.maps.map{genMap(_)}.mkString("\n")+"\n\n"+s.triggers.map{genTrigger(_)}.mkString("\n\n"))+"\n}\n"
  }
  
}

