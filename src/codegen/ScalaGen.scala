package ddbt.codegen
import ddbt.ast._

/**
 * ScalaGen is responsible to transform a typed AST into vanilla Scala code (String).
 * It should be quite straightforward to use LMS to do that instead.
 *
 * Implementation notes:
 * ---------------------------------------------
 * 1. We shall understand the multiply as a continuation of the left operand in the right one.
 *
 * 2. Add is more complicated than Mul as it does set union of lhs and rhs.
 *    If a free variable is present in both sides, iterate these. Concretely:
 *       f(A*B) --> A.foreach{ (k_a,v_a) => B.foreach { (k_b,v_b) => f(v_a * v_b) } }
 *       f(A+B) --> val dom=A.keySet++B.keySet; dom.foreach { k => f(A.get(k) + B.get(k)) }
 *
 *    An lighter approach to set union is:
 *       val tmp = Temp[domA(k_a)=domB(k_b)=dom -> tp(A)=tp(B)]
 *       A.foreach{ (k_a,v_a) => tmp.add(domA(k_a),v_a) }
 *       B.foreach{ (k_b,v_b) => tmp.add(domB(k_b),v_b) }
 *       tmp.foreach { (k,v) => f(v) }
 *
 * Constraints inherited from M3:
 * - Lift alone has only bound variables.
 * - In Exists*Lift, Exists binds variables for the Lift
 * 
 * @author TCK
 */
class ScalaGen(override val cls:String="Query") extends IScalaGen

trait IScalaGen extends CodeGen {
  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  def mapRef(n:String,tp:Type,keys:List[(String,Type)]) = { val m=M3.MapRef(n,tp,keys.map(_._1)); m.tks=keys.map(_._2); m.isTemp=true; m }

  // Methods involving only constants are hoisted as global constants
  protected val cs = HashMap[Apply,String]()
  override def constApply(a:Apply):String = cs.get(a) match { case Some(n) => n case None => val n=fresh("c"); cs+=((a,n)); n }
  override def consts:String = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "val "+n+":"+tp.toScala+" = U"+f+"("+vs.map({ case (v,t) => getVal(v,t)._1 }).mkString(",")+")\n" }.mkString+"\n" // constant function applications

  // XXX: enlarge the definition to generalized constants

  // Context: variable->(type,unique_name)
  var ctx:Ctx[(Type,String)] = null 

  /** Gets the unique name of a variable in the context
    *  
    *  @param n Name of the variable 
    *  
    *  @return The unique name of the variable
    */
  def rn(n:String):(String,Type) = {
    if(ctx contains n)
      (ctx(n)._2,ctx(n)._1)
    else
      sys.error("Could not find "+n+" in context: "+ctx)
  }

  /** Gets the value of the unique name of a variable in the context
    *  
    *  @param n Name of the variable 
    *  
    *  @return The value of the unique name of the variable
    */
  def rnv(n:String) = {
    val (nn,nt) = rn(n)
    getVal(nn,nt)._1
  }

  /*
  Here you need to rename variable to avoid putting individual statements in separated blocks
  M[x] = Add( Mul(Lift(x,2),A[x]), Mul(Lift(x,3),B[x]) )
  { x=A[2]; x } + { x=B[3]; x }
  but we want
  val x1=A[2]
  val x2=B[3]
  x1+x2
  */

  def mapval(v:String,t:Type,m:Int=1) = 
    t match {
      case TypeMapVal(_) => (v,t)
      case _ if m==1 => ("MapVal["+genType(t)+"]("+v+")",TypeMapVal(t))
      case _ => ("MapVal["+genType(t)+"]("+m+","+v+")",TypeMapVal(t))
    }

  /* Gets the value of a MapVal or just returns the value itself if it is not
   * a MapVal.
   *
   * @param v The code that generates the value 
   * @param t The type of the value
   *
   * @return The value 
   */
  def getVal(v:String,t:Type) = 
    t match {
      case TypeMapVal(rt) => (v+".v",rt)
      case _ => ("("+v+")",t) 
    }


  var tupleClasses:Map[String,String] = Map()
  def tupleClass(ts:List[Type]):String = {
    val ops = List("+", "*")    
    val invalidOps = List(">", "<", ">=", "<=")
    val scalarOps = List("*")
    val scalarTypes = List(TypeLong,TypeDouble)
    val name = "T"+ts.map(_.toString).mkString("_")

    if(!tupleClasses.contains(name)) {
      val vals = Range(0,ts.length).map(i => "_"+i)
      def rings(postfix:String) = ts.map(_.toScala+"Ring"+postfix).mkString(",")
      val caseClass = "case class "+name+"("+(vals zip ts).map({case (v,t) => "val "+v+":"+t.toScala}).mkString(",")+");"
      val zero = "val zero = "+name+"("+rings(".zero")+")"
      val one = "val one = "+name+"("+rings(".one")+")"
      val neg = "def -(x:"+name+") = "+name+"("+(ts zip vals).map({ case (t,v) => t.toScala+"Ring.-(x."+v+")"}).mkString(",")+")"
      val opsDef = ops.map(op => "def "+op+"(x:"+name+",y:"+name+") = "+name+"("+ts.zipWithIndex.map({ case(t,i) => t.toScala+"Ring."+op+"(x._"+i+",y._"+i+")"}).mkString(",")+")").mkString("\n")
      val stubs = invalidOps.map(op => "def "+op+"(x:"+name+",y:"+name+") = ???").mkString("\n")
      val toList = "def toList(x:"+name+") = List("+vals.map(v => "x."+v).mkString(",")+")"
      val obj = "implicit object "+name+"Ring extends Ring["+name+"] {"+List(zero,one,neg,opsDef,stubs,toList).mkString("\n")+"}"
      val code = caseClass+obj
      tupleClasses += (name -> code) 
    }

    name
  }

  def genType(t:Type):String =
    t match {
      case TypeTuple(ts) => tupleClass(ts) 
      case _ => t.toScala
    }

  // Create a variable declaration
  def genVar(n:String,tp:Type,ks:List[Type]=Nil) = if (ks==Nil) "var "+n+" = "+mapval(genZero(tp),tp)._1+"\n" else "val "+n+" = M3Map.temp["+tup(ks.map(_.toScala))+","+genType(tp)+"]()\n"

  def genOp(rvl:String,rvr:String,op:String,tl:Type,tr:Type):(String,Type) = {
    def castIfNeeded(iv:String,ivt:Type,rt:Type):String = {
      def mapValIfNeeded(v:String,rt:Type) = rt match { case TypeMapVal(r) => mapval(v,r)._1 case _ => v }
      val puret = rt match { case TypeMapVal(r) => r case _ => rt }
      if(ivt != rt) {
        val (v,vt) = getVal(iv,ivt)
        (vt,puret) match {
          case (TypeTuple(vts),TypeTuple(rts)) => {
            val c=fresh("c"); 
            "{"+c+"="+v+";"+mapValIfNeeded(tupleClass(rts)+"("+Range(0,rts.length).map(i => c+"._"+i).mkString(",")+")",rt)+"}"
          }
          case (_,TypeTuple(rts)) => {
            val c=fresh("c")
            "{ val "+c+"="+v+";"+mapValIfNeeded(tupleClass(rts)+"("+(List.fill(rts.length)(c)).mkString(",")+")",rt)+" }"
          }
          case (_,_) => 
            mapValIfNeeded(v,rt)
        }
      }
      else
        iv 
    }
    val ct = try {
      op match {
        case "*" => Type.tpMul(tl,tr)
        case "+" => Type.tpAdd(tl,tr)
        case _ => Type.tpRes(tl,tr,op)
      }
    } catch { case _:Throwable => sys.error("Could not find common type of "+rvl+op+rvr) }    
    val vl = castIfNeeded(rvl,tl,ct)
    val vr = castIfNeeded(rvr,tr,ct) 
    ("("+vl+" "+op+" "+vr+")",ct)
  }

  def genZero(t:Type):String = {
    t match {
      case TypeTuple(ts) => tupleClass(ts) + t.zeroScala
      case TypeMapVal(vt) => mapval(genZero(vt),vt,0)._1
      case _ => t.zeroScala
    }
  }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  // XXX: am should be a Set instead of a List
  def cpsExpr(ex:Expr,co:(String,Type)=>(String,Type)=(v:String,t:Type)=>(v,t),am:Option[List[(String,Type)]]=None):(String,Type) = ex match {
    case Ref(n) => 
      val (nn,nt)=rn(n)
      co(nn,nt)
    case Const(tp,v) => tp match { case TypeLong => co(v+"L",tp) case TypeString => co("\""+v+"\"",tp) case _ => co(v,tp) }
    case Exists(e) => cpsExpr(e, (v:String,t:Type) => {
      t match {
        case TypeMapVal(x) => co("(if ("+getVal(v,t)._1+" != 0) MapVal(1L) else MapVal(0,0L))",TypeMapVal(TypeLong))
        case _ => co("MapVal(1L)",TypeMapVal(TypeLong))
      }
    })
    case Cmp(l,r,op) => 
      val cmpt = TypeMapVal(TypeLong)
      co(cpsExpr(l,(ll:String,lt:Type) =>
        cpsExpr(r,(rr:String,rt:Type) =>
          ("(if ("+genOp(ll,rr,op.toString,lt,rt)._1+") MapVal(1L) else MapVal(0,0L))",cmpt)))._1,cmpt)
    case app@Apply(fn,tp,as) =>
      if (as.forall(_.isInstanceOf[Const])) co(constApply(app),tp) // hoist constants resulting from function application
      else {
        def app(vs:List[String],ts:List[Type],as:List[Expr]):(String,Type) = as match {
          case a::Nil => 
            cpsExpr(a,(v:String,t:Type) => {
              val vss = ((vs:::List(v)) zip (ts:::List(t))).map({ case (v,t) => getVal(v,t)._1 })
              co("U"+fn+"("+vss.mkString(",")+")",tp)
            },am)
          case a::as => cpsExpr(a,(v:String,t:Type)=>app(vs:::List(v),ts:::List(t),as),am)
        }
        app(Nil,Nil,as)
      }
    //ki : inner key
    //ko : outer key
    //Example:
    //  f(A) {
    //    Mul(M[A,B],ex)
    //  }
    // will be translated to:
    // f(A) {
    //   M.slice(A).foreach{ case (k,v) => // here A is ko
    //     val B = k._2 // here B is ki
    //     v * ex
    //   }
    // }
    case m@MapRef(n,tp,ks) => 
      val (ko,ki) = ks.zipWithIndex.partition{case(k,i)=>ctx.contains(k)}
      val rt = TypeMapVal(tp)
      // if all keys are bound      
      if (ki.size==0) {
        co(n+(if (ks.size>0) ".get("+tup(ks.map(rnv))+")" else ""),rt) 
      }
      else { 
        val (k0,v0)=(fresh("k"),fresh("v"))
        // slice on bound variables
        val sl = if (ko.size>0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(x=>rnv(x._1)))+")" else "" 
        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)
        // bind free variables from retrieved key
        (n+sl+".foreach { ("+(if (ks.size==1) rn(ks.head)._1 else k0)+","+v0+") =>\n"+ind(
          (if (ks.size>1) ki.map{case (k,i)=>"val "+rn(k)._1+" = "+k0+"._"+(i+1)+";\n"}.mkString else "")+co(v0,rt)._1)+"\n}\n",rt)
      }
    case Lift(n::Nil,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) { 
        cpsExpr(e,(v:String,t:Type)=> {
          val (un,unt) = rn(n)
          co("(if ("+genOp(un,v,"==",unt,t)._1+") MapVal(1L) else MapVal(0,0L))",TypeMapVal(TypeLong))
        },am)
      }
      else e match {
        case Ref(n2) => 
          val (rn2,rn2t) = rn(n2)
          ctx.add(n,(rn2t,rn2)); 
          co("MapVal(1L)",TypeMapVal(TypeLong)) // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ => 
          val tp = TypeMapVal(e.tp)
          val l = fresh("l")
          ctx.add(n,(tp,l))
          cpsExpr(e,(v:String,t:Type) => {
            val (cov,cot) = co("(if("+l+".exists) MapVal(1L) else MapVal(0,0L))",TypeMapVal(TypeLong))
            ("val "+rn(n)._1+" = "+mapval(v,t)._1+";\n"+cov,cot)
          },am)
      }
    case Lift(ns,e) =>
      val tps = e.tp match { case TypeTuple(ts) => ts case _ => sys.error("Expected tuple type") } 
      val refs = e match { case Tuple(es) => es.map(e => e match { case Ref(n) => Some(n) case _ => None }) case _ => List.fill(ns.length)(None) }
      val cmpVars = ns.filter(ctx.contains(_))
      (ns zip refs zip tps).foreach {
        case ((n,ref),t) =>
          ref match {
            case Some(n2) =>
              val (rn2,rn2t) = rn(n2)
              ctx.add(n,(rn2t,rn2));
            case None => 
              val l = fresh("l")
              ctx.add(n,(t,l))
          }
      }
      val t=fresh("t")
      ctx.add(t,(e.tp,t))
      cpsExpr(e,(v:String,vt:Type) => {
        val cur = ctx.save 
        ctx.load(cur)
        val tStr = "val "+t+" = "+mapval(v,vt)._1+";\n"
        val (cmps,r) = (ns zip refs).zipWithIndex.foldLeft((List[String](),"")){ case ((cmps,r),((n,ref),i)) => {
          if (cmpVars.contains(n)) 
            ("("+rnv(n)+" == "+t+".v._"+i+")"::cmps,r)
          else {
            ref match {
              case Some(_) => (cmps,r)
              case None => (cmps,r+"val "+rn(n)._1+" = "+t+".v._"+i+";\n")
            }
          }
        }}
        val strExp = r+
          (if(cmps.length>0)
            co("(if ("+cmps.mkString(" && ")+") MapVal(1,1L) else MapVal(0,0L))",TypeMapVal(TypeLong))
          else
            co("(if("+t+".exists) MapVal(1L) else MapVal(0,0L))",TypeMapVal(TypeLong)))._1
        (tStr+strExp,TypeMapVal(TypeLong))
      },am)

    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) )
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el,er) => 
      //cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"),am),am)
      // simplifies (vl * vr)
      def mul(vl:String,vr:String,tl:Type,tr:Type):(String,Type) = {         
        // extract cond and then branch of "if (c) t else 0"
        // no better way for finding boolean type
        // TODO: add Boolean type
        def cx(s:String):Option[(String,String)] = if (!s.startsWith("(if (")) None else { var d=1; var p=5; while(d>0) { if (s(p)=='(') d+=1 else if (s(p)==')') d-=1; p+=1; }; Some(s.substring(5,p-1),s.substring(p+1,s.lastIndexOf("else")-1)) }

        def vx(cond:String,vl:String,vr:String) = {
          val (v,t) = if (vl=="1L") (vr,tr) else if (vr=="1L") (vl,tl) else genOp(vl,vr,"*",tl,tr) 
          val zero = t match { case TypeMapVal(tv) => mapval(genZero(tv),tv,0)._1 case _ => genZero(t) } 
          val (strIf,strElse) = if (cond != null) ("if ("+cond+") "," else "+zero) else ("","")
          ("("+strIf+v+strElse+")",t)
        }
        // pulling out the conditionals from a multiplication
        (cx(vl),cx(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => vx(cl+" && "+cr,tl,tr)
          case (Some((cl,tl)),_) => vx(cl,tl,vr)
          case (_,Some((cr,tr))) => vx(cr,vl,tr)
          case _ => vx(null,vl,vr)
        }
      }
      cpsExpr(el,(vl:String,tl:Type) => {
        cpsExpr(er,(vr:String,tr:Type) => {
          val (mv,mt) = mul(vl,vr,tl,tr)
          co(mv,mt) 
        })})
    // Add(el,er)
    // ==
    //   Add( (el,ctx0) -> (vl,ctx1) , (er,ctx0) -> (vr,ctx2) )
    //         <-------- L -------->    <-------- R -------->
    //    (add - if there's no free variable) ==>
    //   (v=vl+vr , ctx0)
    //    (union - if there are some free variables) ==>
    //   T = Map[....]
    //   foreach vl in L, T += vl
    //   foreach vr in R, T += vr
    //   foreach t in T, co(t)
    case a@Add(el,er) =>
      if (a.agg==Nil) { 
        val cur=ctx.save
        cpsExpr(el,(vl:String,tl:Type) => {
          ctx.load(cur)
          cpsExpr(er,(vr:String,tr:Type) => {
            ctx.load(cur) 
            val (av,at) = genOp(vl,vr,"+",tl,tr)
            co(av,at)
          },am)
        },am) 
      }
      else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) => 
          val cur=ctx.save
          val (s1,_)=cpsExpr(el,co,am)
          ctx.load(cur)
          val (s2,rt)=cpsExpr(er,co,am)
          ctx.load(cur)
          (s1+s2,rt)
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String,t:Type)=> (a0+".add("+tup(ks map rnv)+","+v+");\n",TypeUnit),tmp)._1
          ctx.load(cur)
          val s2 = cpsExpr(er,(v:String,t:Type)=> (a0+".add("+tup(ks map rnv)+","+v+");\n",TypeUnit),tmp)._1
          ctx.load(cur)
          val (r,rt) = cpsExpr(mapRef(a0,ex.tp,a.agg),co)
          (genVar(a0,ex.tp,a.agg.map(_._2))+"\n"+s1+"\n"+s2+"\n"+r,rt)
      }
    case a@AggSum(ks,e) =>
      // aggregation keys as (name,type)
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } 
      if (aks.size==0) { 
        val a0=fresh("agg")
        val tp=TypeMapVal(ex.tp)
        (genVar(a0,tp)+cpsExpr(e,(v:String,t:Type) => {
          (a0+" = "+genOp(a0,v,"+",tp,t)._1+"\n",TypeUnit)
        })._1+"\n"+co(a0,tp)._1,tp) 
      }
      else am match {
        case Some(t) if t.toSet.subsetOf(aks.toSet) => 
          cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = M3Map.temp["+tup(aks.map(x=>x._2.toScala))+","+genType(e.tp)+"]()\n"+cpsExpr(e,(v:String,t:Type)=>(a0+".add("+tup(aks.map(x=>rnv(x._1)))+","+v+");\n",TypeUnit),tmp)._1
          ctx.load(cur)
          (s1+"\n"+cpsExpr(mapRef(a0,e.tp,aks),co)._1,ex.tp)
      }
    case t@Tuple(es) => 
      def tuple(vs:List[String],ts:List[Type],esp:List[Expr]):(String,Type) = esp match {
        case e::Nil => 
          cpsExpr(e,(v:String,t:Type)=> {
            val (vss,tss) = ((vs:::List(v)) zip (ts:::List(t))).map({ case (v,t) => getVal(v,t) }).unzip
            val tp = TypeTuple(tss)
            val (mv,mvt) = mapval(tupleClass(tss)+"("+vss.mkString(",")+")",tp)
            co(mv,mvt) },am)
        case e::es => cpsExpr(e,(v:String,t:Type)=>tuple(vs:::List(v),ts:::List(t),es),am)
      }
      tuple(Nil,Nil,es)
    case Neg(e) => cpsExpr(e,(v:String,t:Type) => co(" -("+v+")",t),am)
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) => 
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = oi match {
        case Some(ie) => 
          ctx.load(); 
          cpsExpr(ie,(i:String,t:Type) => {
            val exprStr =
              if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
              else "if ("+m.name+".get("+tup(m.keys map rnv)+").isNoVal) "+m.name+".set("+tup(m.keys map rnv)+","+i+");\n"
            (exprStr,TypeUnit) 
          })._1
        case None => ""
      }
      ctx.load(); 
      clear+init+"\n"+
      cpsExpr(e,(v:String,t:Type) => {
        lazy val sop = {
          val (ope,opt) = (op match { case OpAdd => genOp(m.name,v,"+",TypeMapVal(e.tp),t) case OpSet => (v,t) })
          m.name+"="+mapval(ope,opt)._1+";\n"
        }
        ((if (m.keys.size==0) sop else m.name+".add("+tup(m.keys map rnv)+","+mapval(v,t)._1+")")+";\n",TypeUnit)
      },Some(m.keys zip m.tks))._1+"\n"
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  def genTrigger(t:Trigger):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap)
    val body=t.stmts.map(genStmt).mkString
    ctx=null
    "def on"+n+"("+as.map(a=>a._1+":"+a._2.toScala).mkString(", ")+") "+(if (body=="") "{ }" else "{\n"+ind(body)+"\n}")
  }

  // Lazy slicing (secondary) indices computation
  protected val sx = HashMap[String,List[List[Int]]]() // slicing indices
  def slice(m:String,i:List[Int]):Int = { // add slicing over particular index capability
    val s=sx.getOrElse(m,List[List[Int]]()); val n=s.indexOf(i)
    if (n != -1) n else { sx.put(m,s ::: List(i)); s.size }
  }

  override def genMap(m:MapDef):String = {
    if (m.keys.size==0) genVar(m.name,m.tp).trim
    else {
      val tk = tup(m.keys.map(x=>x._2.toScala))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      val proj = if(s.isEmpty) "" else s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ") 
      "val "+m.name+" = M3Map.make["+tk+","+genType(m.tp)+"]("+proj+");"
    }
  }

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = map+".add("+keyNamesConcat+",MapVal.one[Long])"

  // Generate (1:stream events handling, 2:table loading, 3:global constants declaration)
  override def genInternals(s0:System,nextSkip:String="context.become(receive_skip)") : (String,String,String) = {
    // XXX: reduce as much as possible the overhead here to decode data, use Decoder's internals and inline the SourceMux here
    def ev(s:Schema,short:Boolean=true):(String,String,List[(String,Type)]) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      ("List("+fs.map{case(s,t)=>s.toLowerCase+":"+t.toScala}.mkString(",")+")","("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")",fs)
    }
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val skip = "if (t1>0 && (tN&"+(step-1)+")==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; "+nextSkip+" } else tN+=1 } else tN+=1; "
    val str = s0.triggers.map(_.evt match {
      case EvtAdd(s) => val (i,o,pl)=ev(s); "case TupleEvent(ord,TupleInsert,\""+s.name+"\","+i+") => "+skip+"onAdd"+s.name+o+"\n"
      case EvtDel(s) => val (i,o,pl)=ev(s); "case TupleEvent(ord,TupleDelete,\""+s.name+"\","+i+") => "+skip+"onDel"+s.name+o+"\n"
      case _ => ""
    }).mkString
    val ld0 = s0.sources.filter{s=> !s.stream}.map { s=> val (in,ad,sp)=genStream(s); val (i,o,pl)=ev(s.schema)
      "SourceMux({ case TupleEvent(ord,TupleInsert,rn,"+i+")=>"+genInitializationFor(s.schema.name,pl,o)+" }, Seq(("+in+","+ad+","+sp+"))).read;" }.mkString("\n");
    (str,ld0,consts)
  }

  override def genLMS(s0:System):(String,String,String,String) = (null,null,null,null)

  override def toMapFunction(q: Query) = q.name+".toMap"
  override def clearOut = {}
  override def onEndStream = ""

  def apply(s0:System):String = {
    val (lms,strLMS,ld0LMS,gcLMS) = genLMS(s0)
    val body = if (lms!=null) lms else {
      val ts = s0.triggers.map(genTrigger).mkString("\n\n") // triggers (need to be generated before maps)
      val ms = s0.maps.map(genMap).mkString("\n") // maps
      ms+"\n\n"+ts
    }
    val (str,ld0,gc) = if(lms!=null) (strLMS,ld0LMS,gcLMS) else genInternals(s0)
    val ld = if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else "" // optional preloading of static tables content
    freshClear()
    val snap=onEndStream+" sender ! (StreamStat(t1-t0,tN,tS),List("+s0.queries.map{q=>(if (s0.mapType(q.map.name)._1.size>0) q.name+".toListMap" else q.name+".toList")}.mkString(",")+"))"
    clearOut
    helper(s0)+"class "+cls+" extends Actor {\n"+ind(
    "import ddbt.lib.Messages._\n"+
    "import ddbt.lib.Functions._\n\n"+
    tupleClasses.values.mkString("\n")+"\n\n"+
    body+"\n\n"+
    "var t0=0L; var t1=0L; var tN=0L; var tS=0L\n"+
    "def receive_skip:Receive = { case EndOfStream | GetSnapshot(_) => "+snap+" case _ => tS+=1 }\n"+
    "def receive = {\n"+ind(str+
      "case StreamInit(timeout) =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime; if (timeout>0) t1=t0+timeout*1000000L\n"+
      "case EndOfStream | GetSnapshot(_) => t1=System.nanoTime; "+snap
    )+"\n}\n"+gc+ld)+"\n"+"}\n"
  }

  private def genStream(s:Source): (String,String,String) = {
    val in = s.in match { case SourceFile(path) => "new java.io.FileInputStream(\""+path+"\")" }
    val split = "Split"+(s.split match { case SplitLine => "()" case SplitSep(sep) => "(\""+sep+"\")" case SplitSize(bytes) => "("+bytes+")" case SplitPrefix(p) => ".p("+p+")" })
    val adaptor = s.adaptor.name match {
      case "ORDERBOOK" => "OrderBook("+s.adaptor.options.toList.map { case (k,v) => k+"="+(k match {
        case "brokers" => v case "bids"|"asks" => "\""+v+"\"" case "deterministic" => (v!="no"&&v!="false").toString case _ => ""
      })}.filter(!_.endsWith("=")).mkString(",")+")"
      case "CSV" => val sep=java.util.regex.Pattern.quote(s.adaptor.options.getOrElse("delimiter",",")).replaceAll("\\\\","\\\\\\\\")
                    "CSV(\""+s.schema.name.toUpperCase+"\",\""+s.schema.fields.map(_._2).mkString(",")+"\",\""+sep+"\")"
    }
    (in,"new Adaptor."+adaptor,split)
  }

  def streams(sources:List[Source]) = {
    def fixOrderbook(ss:List[Source]):List[Source] = { // one source generates BOTH asks and bids events
      val (os,xs) = ss.partition{_.adaptor.name=="ORDERBOOK"}
      val ob = new java.util.HashMap[(Boolean,SourceIn),(Schema,Split,Map[String,String])]()
      os.foreach { case Source(s,sc,in,sp,ad) =>
        val (k,v) = ((s,in),(ad.options-"book") + ((ad.options.getOrElse("book","bids"),sc.name)))
        val p=ob.get(k); if (p==null) ob.put(k,(sc,sp,v)) else ob.put(k,(sc,sp,p._3++v))
      }
      scala.collection.JavaConversions.mapAsScalaMap(ob).toList.map { case ((s,in),(sc,sp,opts)) => Source(s,sc,in,sp,Adaptor("ORDERBOOK",opts)) } ::: xs
    }
    val ss=fixOrderbook(sources).filter{s=>s.stream}.map{s=> val (in,ad,sp)=genStream(s); "("+in+","+ad+","+sp+")" }.mkString(",\n")
    "Seq(\n"+ind(ss.replaceAll("Adaptor.CSV\\(([^)]+)\\)","Adaptor.CSV($1,if(d.endsWith(\"_del\")) \"ins+del\" else \"insert\")").replaceAll("/standard/","/\"+d+\"/"))+"\n)"
  }

  /*
   * Generates a main function and streams from files.
   *
   * @param  s0 System Generates code for this system
   * @return The generated code
   */
  private def helper(s0:System) =
    "import ddbt.lib._\n"+additionalImports()+"\nimport akka.actor.Actor\nimport java.util.Date\nimport ddbt.lib.Ring._\n\n"+
    "object "+cls+" {\n"+ind("import Helper._\n"+
    "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long)=>run["+cls+"]("+streams(s0.sources)+",p,t),f)\n\n"+
    "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    "\n})")+"\n}")+"\n}\n"

  override def pkgWrapper(pkg:String, body:String) = "package "+pkg+"\n"+body+"\n"

  override def additionalImports():String = ""
}
