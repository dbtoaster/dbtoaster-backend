package ddbt.codegen
import ddbt.ast._

// Generators to emit LMS nodes from AST
object ScalaGen {
  import ddbt.ast.M3._
  import scala.collection.mutable.HashMap
  
  private val counter = HashMap[String,Int]()
  def fresh(name:String="x") = { val c = counter.getOrElse(name,0)+1; counter.put(name,c); name+c }
  def ind(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll(" +$","").replace("\n","\n"+i) }
  def tpe(tp:Type):String = { val s=tp.toString; s.substring(0,1).toUpperCase+s.substring(1).toLowerCase }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  // Retrieve a list of binding variables
  private def bnd(ex:Expr):Set[String] = ex match {
    case Mul(l,r) => bnd(l)++bnd(r)
    case Add(l,r) => bnd(l)++bnd(r)
    case Apply(f,t,as) => as.flatMap(a=>bnd(a).toList).toSet
    case Lift(n,e) => bnd(e)+n
    case MapRef(n,tp,ks) => ks.toSet
    case _ => Set() // AggSum
  }
  
  private def getMapRefs(e:Expr):List[MapRef] = Nil
  private def getLift(e:Expr): List[Lift] = Nil
  private def useRef(e:Expr,n:String): Boolean = false

  // Generate code bottom-up using delimited CPS and a list of bounded variables
  //   ex:expression to convert
  //   b :bounded variables
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  def cpsExpr(ex:Expr,b:Set[String],co:String=>String):String = ex match {
    case Const(tp,v) => tp match { case TypeLong => co(v+"L") case TypeString => co("\""+v+"\"") case _ => co(v) }
    case Ref(n) => co(n)
    case MapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>b.contains(k)}
      if (ki.size==0) co(n+".get("+tup(ks)+")") // all keys are bounded
      else {
        val k0=fresh("k"); val v0=fresh("v");
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map{case (k,i)=>i})+","+tup(ko.map{case (k,i)=>k})+")" else ""
        n+sl+".foreach { case ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";"}.mkString("\n")+"\n"+co(v0))+"\n}" // bind unbounded variables from retrieved key
      }

    // We have a LiftExist here
    case Mul(Exists(e1),Lift(n,e)) if (e1==e) => assert(b.contains(n)); 
      cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";\n"+co("(if ("+n+" != 0) "+n+" else 0)"))
    case Lift(n,e) => assert(b.contains(n)); cpsExpr(e,b,(v:String)=>co("("+n+" == "+v+")")) // lift acts as a constraint

    // XXX: Mul(Mul(Exists,Lift),er)
    case Mul(Lift(n,e),er) if (!b.contains(n)) => cpsExpr(e,b,(v:String)=>"val "+n+" = "+v+";\n")+cpsExpr(Mul(Ref(n),er),b+n,co)
    // XXX: ditto for sum ?
    
    case Mul(el,er) => cpsExpr(el,b,(vl:String)=>{ cpsExpr(er,b++bnd(el),(vr:String)=>co("("+vl+" * "+vr+")")) }) // right is nested in left
    case Add(el,er) => cpsExpr(el,b,(vl:String)=>{ cpsExpr(er,b++bnd(el),(vr:String)=>co("("+vl+" + "+vr+")")) }) // right is nested in left
    
    /*
    Lift alone has only bound variables
    Exists+Lift : Exist binds variables for the lift
    */
    
    case AggSum(ks,e) =>
      if ((ks.toSet--b).size>0) {
        val s0=fresh("set");
        val k0=fresh("k");
        val v0=fresh("v")
        "var "+s0+" = K3Map.make[K?,V?]()\n//filling set\n"+cpsExpr(e,b++ks.toSet,(v:String)=>s0+".add("+tup(ks)+","+v+");")+"\n//using set\n"+s0+".foreach{ case ("+tup(ks)+","+v0+") =>\n"+ind(co(v0))+"\n}\n"
      } else {
        val a0=fresh("agg"); "var "+a0+":Double = 0 //correct type???\n"+cpsExpr(e,b /*++ks.toSet*/,(v:String)=>a0+" += "+v+";")+"\n"+co(a0) // XXX: we did not use ks. Problem?
      }
      // val fk = ks.toSet -- b if (fk.size>0) ...
      // XXX: if inner contains element that cannot be bound, create intermediate map ?
    case Exists(e) => val e0=fresh("ex"); "var "+e0+":Long = 0L\n"+cpsExpr(e,b,(v:String)=>e0+" |= ("+v+")!=0;")+"\n"+co(e0)
      // XXX: if all variables are bound, inline it [let ex=v; co(ex)]
      //cpsExpr(e,b,(v:String)=>"if (("+v+")!=0) {\n"+ind(co("1L"))+"\n}")
    case app@Apply(f,tp,as) => if (as.filter(!_.isInstanceOf[Const]).size==0) co(constApply(app)) // hoist constants
      else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>cpsExpr(a,b,(v:String)=>c0(p+(if (i>0) "," else "(")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+f) }
      // val vs = as.map { a=>cpsExpr(a,b,(v:String)=>v) } co("<<"+f+"("+vs.mkString(",")+")>>")
      //var app = f+"<<("; as.foreach { a=>cpsExpr(a,b,(v:String)=>app+v+",") }; co((if (as.size>0) app.substring(0,app.length-1) else app)+")>>")
    case Cmp(l,r,op) => co(cpsExpr(l,b,(ll:String)=>cpsExpr(r,b,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt,b:Set[String]):String = s match {
    case StmtMap(m,e,op,oi) => val fop=op match { case OpAdd => "add" case OpSet => "set" }
      cpsExpr(e,b,(res:String)=>m.name+"."+fop+"("+(if (m.keys.size==0) "" else tup(m.keys)+",")+res+");")
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
  private val sx = HashMap[String,List[List[Int]]]() // slicing indices
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

  // Methods involving only constants are hoisted as global constants
  private val cs = HashMap[Apply,String]() 
  def constApply(a:Apply):String = cs.get(a) match { case Some(n) => n case None => val n=fresh("c"); cs+=((a,n)); n }
  
  def genSystem(s:System,cls:String="Query"):String = {
    val ts = s.triggers.map{genTrigger(_)}.mkString("\n\n") // triggers need to be generated before maps
    val ms = s.maps.map{genMap(_)}.mkString("\n")
    val qs = "def result = "+s.queries(0).name+".toMap" // fix for multiple queries
    def ev(s:Schema,short:Boolean=true):(String,String) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      ("List("+fs.map{case(s,t)=>s.toLowerCase+":"+tpe(t)}.mkString(",")+")","("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")")
    }
    "class "+cls+" extends Actor {\n"+ind(
      "import ddbt.lib.Messages._\n"+
      "import ddbt.lib.Functions._\n\n"+ms+"\n\n"+
      "var t0:Long = 0\n"+
      "def receive = {\n"+ind(
        s.triggers.map{
          case TriggerAdd(s,_) => val (i,o)=ev(s); "case TupleEvent(TupleInsert,\""+s.name+"\",tx,"+i+") => onAdd"+s.name+o+"\n"
          case TriggerDel(s,_) => val (i,o)=ev(s); "case TupleEvent(TupleDelete,\""+s.name+"\",tx,"+i+") => onDel"+s.name+o+"\n"
          case _ => ""
        }.mkString+
        "case SystemInit => onSystemReady(); t0=System.nanoTime()\n"+
        "case EndOfStream => val time=System.nanoTime()-t0; sender ! (time,result)"
      )+"\n}\n\n"+qs+"\n\n"+cs.map{case (Apply(f,tp,as),n) =>
        val vs = as.map { a=>cpsExpr(a,Set(),(v:String)=>v) }
        "val "+n+":"+tpe(tp)+" = U"+f+"("+vs.mkString(",")+")\n"
      }.mkString+"\n"+ts)+"\n}\n"
  }
}

  // Retrieve a list of used variables
  /*
  private def vars(ex:Expr):Set[String] = ex match {
    case Mul(l,r) => vars(l)++vars(r)
    case Add(l,r) => vars(l)++vars(r)
    case Apply(f,t,as) => as.flatMap(a=>vars(a).toList).toSet
    case Lift(n,e) => vars(e)
    case Cmp(l,r,op) => vars(l)++vars(r)
    case MapRef(n,tp,ks) => ks.toSet
    case Exists(e) => vars(e)
    case _ => Set() // AggSum
  }
  */
/*
  private def replace(ex:Expr,eo:Expr,en:Expr):Expr = ex match {
    case `eo` => en
    case Lift(n,e) => Lift(n,replace(e,eo,en))
    case AggSum(ks,e) => AggSum(ks,replace(e,eo,en))
    case Mul(l,r) => Mul(replace(l,eo,en),replace(r,eo,en))
    case Add(l,r) => Add(replace(l,eo,en),replace(r,eo,en))
    case Exists(e) => Exists(replace(e,eo,en))
    case Apply(f,tp,as) => Apply(f,tp,as.map{e=>replace(e,eo,en)})
    case Cmp(l,r,op) => Cmp(replace(l,eo,en),replace(r,eo,en),op)
    case _ => ex
  }
*/
  


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



  
    // We shall understand the add/multiply as a continuation of the left operand in the right one
  
    // Some "-1" simplifications
    //case Add(l,Mul(Const(typeLong,"-1"),Ref(n))) => co(cpsExpr(l,b,(ll:String)=>"("+ll+" - "+n+")"))
    //case Mul(Const(typeLong,"-1"),Ref(n)) => co("-"+n)

    // -----------------------------------------------

    // if a binding MapRef on the left binds some variable on the right, let's unfold it now
    // if a binding Lift on the left binds a variable used on the right, let's unfold it now
    
/*    
    case mul@Mul(ref@MapRef(n,tp,ks),er) if (ks.filter{!b.contains(_)}.size>0) => // outer foreach loop bind unbound keys
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>b.contains(k)}
      val k0=fresh("k"); val v0=fresh("v");
      val b1 = b ++ ki.map{case (k,i)=>k} + v0 // we bind keys and value
      var m1 = replace(mul,ref,Ref(v0))

      // now we replace map reference in the body
      // finally we generate the body by continuation
      // then we put that code in the loop
        
      // we just generate a loop and that's all we do here
      // then we rewire all gets into the new value and bind all inner keys
      
      // transform <er> to replace access by references
      // XXX: do we need also to test for non-emptiness of maps that we are currently binding ??
      val sl = if (ko.size>0) ".slice("+slice(n,ko.map{case (k,i)=>i})+","+tup(ko.map{case (k,i)=>k})+")" else ""
      n+sl+".foreach { case ("+k0+","+v0+") =>\n"+ind( // slice on bound variables
        ki.map{case (k,i)=>"val "+k+" = "+k0+(if (ks.size>1) "._"+(i+1) else "")+";\n"}.mkString+ // bind unbounded variables from retrieved key
        cpsExpr(m1,b1,co) )+"\n}"
*/
    // Different approach: if a variable happen on both sides of the same branch AND if this variable is used by both, generate a loop, replace inner access by variables


    // -----------------------------------------------

  

/*
  private def bnd(e:Expr):Set[String] = e match { // find bound variables
    case Lift(n,e) => bnd(e)+n
    case AggSum(ks,e) => Set() //bnd(e)++ks
    case Mul(l,r) => bnd(l)++bnd(r)
    case Add(l,r) => bnd(l)++bnd(r)
    case Exists(e) => bnd(e)
    case Apply(f,t,as) => as.flatMap(a=>bnd(a).toList).toSet
    case Cmp(l,r,op) => bnd(l)++bnd(r)
    case MapRef(n,tp,ks) => ks.toSet
    case _ => Set()
  }
*/
  /*
  private def free(e:Expr):Set[String] = e match {

  case class Const(tp:Type,v:String) extends Expr { override def toString=if (tp==TypeString) "'"+v+"'" else v }
  // Variables
  case class Ref(name:String) extends Expr { override def toString=name }
  case class MapRef(name:String, tp:Type, keys:List[String]) extends Expr { override def toString=name+(if (tp!=null)"("+tp+")" else "")+"[]["+keys.mkString(",")+"]" }
  case class Lift(name:String, e:Expr) extends Expr { override def toString="( "+name+" ^= "+e+")" } // 'Let name=e in' semantics (usually followed by * ...)
  case class Tuple(schema:String, proj:List[String]) extends Expr { override def toString=schema+"("+proj.mkString(", ")+")" } // appear only in Map declaration
  // Operations
  case class AggSum(ks:List[String], e:Expr) extends Expr { override def toString="AggSum(["+ks.mkString(",")+"],\n"+i(e.toString)+"\n)" } // returns a {[tuple(group_keys)] => count} relation
  case class Mul(l:Expr,r:Expr) extends Expr { override def toString="("+l+" * "+r+")" } // cross-product semantics
  case class Add(l:Expr,r:Expr) extends Expr { override def toString="("+l+" + "+r+")" } // union semantics
    case Exists(e) extends Expr { override def toString="EXISTS("+e+")" } // returns 0 or 1 (check that there is at least one tuple)
    case Apply(f,tp,as) => as.flatMap(a=>bnd(a).toList).toSet
    case Cmp(l,r,_) => free(l)++free(r)
    case _ => Set()
  }
  */
  
  
