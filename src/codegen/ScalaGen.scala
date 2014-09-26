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
class ScalaGen(override val cls:String="Query", override val printProgress:Long=0L) extends IScalaGen

object ScalaGen {
  def tupleNameOfTps(types: List[Type]) =
    if(types.length == 1)
      types.head.toScala
    else
      "T"+types.map(t => t.simpleName).mkString
}

trait IScalaGen extends CodeGen {
  import scala.collection.mutable.HashMap
  import ddbt.ast.M3._
  import ddbt.Utils.{ind,tup,fresh,freshClear} // common functions
  def mapRef(n:String,tp:Type,keys:List[(String,Type)]) = { val m=M3.MapRef(n,tp,keys.map(_._1)); m.tks=keys.map(_._2); m.isTemp=true; m }

  // Methods involving only constants are hoisted as global constants
  protected val cs = HashMap[Apply,String]()
  override def constApply(a:Apply):String = cs.get(a) match { case Some(n) => n case None => val n=fresh("c"); cs+=((a,n)); n }
  override def consts:String = cs.map{ case (Apply(f,tp,as),n) => val vs=as.map(a=>cpsExpr(a)); "val "+n+":"+tp.toScala+" = U"+f+"("+vs.mkString(",")+")\n" }.mkString+ // constant function applications
                               regexpCacheMap.map{ case (regex,preg) => "val "+preg+"=java.util.regex.Pattern.compile(\""+regex+"\");\n"}.mkString+"\n"

  protected val ENABLE_REGEXP_PARTIAL_EVAL=true
  protected val regexpCacheMap = HashMap[String,String]() //Regex String => Regex object name

  // XXX: enlarge the definition to generalized constants

  var ctx:Ctx[(Type,String)] = null // Context: variable->(type,unique_name)
  def rn(n:String):String = ctx(n)._2 // get unique name (avoids nesting Lifts)
  /*
  Here you need to rename variable to avoid putting individual statements in separated blocks
  M[x] = Add( Mul(Lift(x,2),A[x]), Mul(Lift(x,3),B[x]) )
  { x=A[2]; x } + { x=B[3]; x }
  but we want
  val x1=A[2]
  val x2=B[3]
  x1+x2
  */

  private def cmpFunc(tp: Type, op:OpCmp, arg1: String, arg2: String) = tp match {
    // case TypeDouble => op match {
    //   case OpEq => "Math.abs("+arg1+"-"+arg2+") < diff_p"
    //   case OpNe => "Math.abs("+arg1+"-"+arg2+") >= diff_p"
    //   case _ => arg1+" "+op+" "+arg2
    // }
    case _ => arg1+" "+op+" "+arg2
  }

  // Create a variable declaration
  def genVar(n:String,tp:Type,ks:List[Type]=Nil) = if (ks==Nil) "var "+n+" = "+tp.zeroScala+"\n" else "val "+n+" = M3Map.temp["+genTupleDef(ks)+","+tp.toScala+"]()\n"

  var tuples = Map[String, String]()

  def genTupleDef(types: List[Type]) = {
    val tupleName = ScalaGen.tupleNameOfTps(types)
    if(types.length > 1 && !(tuples contains tupleName)) {
      def prodDef =
        "def canEqual(that:Any) = true\n"+
        "def productArity = "+types.length+"\n"+
        "def productElement(i:Int):Any = List[Any]("+(1 to types.length).map(i => "_"+i).mkString(",")+")(i)\n"
      def eqDef =
        "override def equals(o:Any) = { o match { case x:"+tupleName+" => ("+
        (1 to types.length).map{ i => cmpFunc(types(i-1),OpEq,"_"+i,"x._"+i) }.mkString(" && ")+") case x:Product => if(this.productArity == x.productArity) (0 to (productArity - 1)).forall(i => x.productElement(i) == this.productElement(i)) else false case _ => false } }\n"+
        "override def toString() = \"<\"+List[Any]("+(1 to types.length).map(i => "_"+i).mkString(",")+").mkString(\",\")+\">\"\n"+
        "override def hashCode() = {\n"+
        "  var h:Int="+types.length+"\n"+
        (1 to types.length).map { i =>
        "  h = h * 41 + "+(types(i-1) match {
            case TypeLong => "_"+i+".toInt"
            case TypeDouble => "_"+i+".toInt"
            case _ => "_"+i+".hashCode"
          })+"\n"
        }.mkString+
        "  h\n"+
        "}\n"
      def classDef = "class "+tupleName+"("+types.zipWithIndex.map{ case(t,i) => "val _"+(i+1)+":"+t.toScala }.mkString(",")+") extends Product {\n"+
        ind(prodDef+eqDef)+"\n}\n"
      tuples = tuples + (tupleName -> classDef)
    }
    tupleName
  }

  def genTuple(vars: List[(Type,String)]) = {
    val (types,values) = vars.unzip
    val tupleName = genTupleDef(types)
    if(vars.length == 1)
      vars.head._2
    else
      "new "+tupleName+"("+values.mkString(",")+")"
  }

  def applyFunc(co:String=>String, fn1:String, tp:Type, as1:List[Expr]) = {
    val (as, fn) = (fn1 match {
      case "regexp_match" if (ENABLE_REGEXP_PARTIAL_EVAL && as1.head.isInstanceOf[Const] && !as1.tail.head.isInstanceOf[Const]) => val regex=as1.head.asInstanceOf[Const].v; val preg0=regexpCacheMap.getOrElse(regex, fresh("preg")); regexpCacheMap.update(regex,preg0); (as1.tail, "preg_match("+preg0+",")
      case _ => (as1, fn1+"(")
    })
    if (as.forall(_.isInstanceOf[Const])) co(constApply(Apply(fn1,tp,as1))) // hoist constants resulting from function application
    else { var c=co; as.zipWithIndex.reverse.foreach { case (a,i) => val c0=c; c=(p:String)=>cpsExpr(a,(v:String)=>c0(p+(if (i>0) "," else "")+v+(if (i==as.size-1) ")" else ""))) }; c("U"+fn) }
  }

  // Generate code bottom-up using delimited CPS and a list of bound variables
  //   ex:expression to convert
  //   co:delimited continuation (code with 'holes' to be filled by expression) similar to Rep[Expr]=>Rep[Unit]
  //   am:shared aggregation map for Add and AggSum, avoiding useless intermediate map where possible
  def cpsExpr(ex:Expr,co:String=>String=(v:String)=>v,am:Option[List[(String,Type)]]=None):String = ex match { // XXX: am should be a Set instead of a List
    case Ref(n) => co(rn(n))
    case Const(tp,v) => tp match {
      case TypeLong => co(v+"L")
      case TypeString => co("\""+v+"\"")
      case _ => co(v)
    }
    case Exists(e) => cpsExpr(e,(v:String)=>co("(if ("+v+" != 0) 1L else 0L)"))
    case Cmp(l,r,op) => cpsExpr(l,(ll:String)=>cpsExpr(r,(rr:String)=>co("(if ("+cmpFunc(l.tp,op,ll,rr)+") 1L else 0L)")))
    case app@Apply(fn,tp,as) => applyFunc(co,fn,tp,as)
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
      if(ks.size == 0) { // variable
        if(ctx contains n) co(rn(n)) else co(n)
      } else if (ki.size == 0) { // all keys are bound
        co(n+".get("+genTuple(ks map ctx)+")")
      } else { // we need to iterate over all keys not bound (ki)
        val (k0,v0)=(fresh("k"),fresh("v"))
        val sl = if (ko.size > 0) ".slice("+slice(n,ko.map(_._2))+","+tup(ko.map(x=>rn(x._1)))+")" else "" // slice on bound variables
        ctx.add((ks zip m.tks).filter(x=> !ctx.contains(x._1)).map(x=>(x._1,(x._2,x._1))).toMap)
        n+sl+".foreach { ("+(if (ks.size==1) rn(ks.head) else k0)+","+v0+") =>\n"+
          ind(
            (if (ks.size>1) {
              ki.map{case (k,i)=>"val "+rn(k)+" = "+k0+"._"+(i+1)+";\n"}.mkString
            } else "")+
            co(v0)
          )+"\n"+
        "}\n" // bind free variables from retrieved key
      }
    // "1L" is the neutral element for multiplication, and chaining is done with multiplication
    case Lift(n,e) =>
    // Mul(Lift(x,3),Mul(Lift(x,4),x)) ==> (x=3;x) == (x=4;x)
      if (ctx.contains(n)) cpsExpr(e,(v:String)=>co("(if ("+rn(n)+" == "+v+") 1L else 0L)"),am)
      else e match {
        case Ref(n2) => ctx.add(n,(e.tp,rn(n2))); co("1L") // de-aliasing
        //This renaming is required. As an example:
        //
        //C[x] = Add(A[x,y], B[x,y])
        //D[x] = E[x]
        //
        // will fail without a renaming.
        case _ =>
          ctx.add(n,(e.tp,fresh("l")))
          cpsExpr(e,(v:String)=> "val "+rn(n)+" = "+v+";\n"+co("1L"),am)
      }
    // Mul(el,er)
    // ==
    //   Mul( (el,ctx0) -> (vl,ctx1) , (er,ctx1) -> (vr,ctx2) )
    //    ==>
    //   (v=vl*vr , ctx2)
    case Mul(el,er) => //cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"),am),am)
      def mul(vl:String,vr:String) = { // simplifies (vl * vr)
        // extract cond and then branch of "if (c) t else 0"
        // no better way for finding boolean type
        // TODO: add Boolean type
        def cx(s:String):Option[(String,String)] = if (!s.startsWith("(if (")) {
          None
        } else {
          var d=1
          val pInit="(if (".length
          var p=pInit
          while(d>0) {
            if (s(p)=='(') d+=1 else if (s(p)==')') d-=1
            p+=1
          }
          Some(s.substring(pInit,p-1),s.substring(p+1,s.lastIndexOf("else")-1))
        }
        def vx(vl:String,vr:String) = if (vl=="1L") vr else if (vr=="1L") vl else "("+vl+" * "+vr+")"
        //pulling out the conditionals from a multiplication
        (cx(vl),cx(vr)) match {
          case (Some((cl,tl)),Some((cr,tr))) => "(if ("+cl+" && "+cr+") "+vx(tl,tr)+" else "+ex.tp.zeroScala+")"
          case (Some((cl,tl)),_) => "(if ("+cl+") "+vx(tl,vr)+" else "+ex.tp.zeroScala+")"
          case (_,Some((cr,tr))) => "(if ("+cr+") "+vx(vl,tr)+" else "+ex.tp.zeroScala+")"
          case _ => vx(vl,vr)
        }
      }
      cpsExpr(el,(vl:String)=>cpsExpr(er,(vr:String)=>co(mul(vl,vr)),am),am)
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
        cpsExpr(el,(vl:String)=>{
          ctx.load(cur)
          cpsExpr(er,(vr:String)=>{
            ctx.load(cur)
            co("("+vl+" + "+vr+")")
          },am)
        },am)
      } else am match {
        case Some(t) if t.toSet.subsetOf(a.agg.toSet) =>
          val cur=ctx.save
          val s1=cpsExpr(el,co,am)
          ctx.load(cur)
          val s2=cpsExpr(er,co,am)
          ctx.load(cur)
          s1+s2
        case _ =>
          val (a0,k0,v0)=(fresh("add"),fresh("k"),fresh("v"))
          val ks = a.agg.map(_._1)
          val tmp = Some(a.agg)
          val cur = ctx.save
          val s1 = cpsExpr(el,(v:String)=>a0+".add("+genTuple(ks map ctx)+","+v+");\n",tmp); ctx.load(cur)
          val s2 = cpsExpr(er,(v:String)=>a0+".add("+genTuple(ks map ctx)+","+v+");\n",tmp); ctx.load(cur)

          genVar(a0,ex.tp,a.agg.map(_._2))+
          s1+
          s2+
          cpsExpr(mapRef(a0,ex.tp,a.agg),co)
      }
    case a@AggSum(ks,e) =>
      val aks = (ks zip a.tks).filter { case(n,t)=> !ctx.contains(n) } // aggregation keys as (name,type)
      if (aks.size==0) {
        val a0=fresh("agg")

        genVar(a0,a.tp)+
        cpsExpr(e,(v:String)=>a0+" += "+v+";\n")+
        co(a0)
      } else am match {
        case Some(t) if t.toSet.subsetOf(aks.toSet) => cpsExpr(e,co,am)
        case _ =>
          val a0=fresh("agg")
          val tmp=Some(aks) // declare this as summing target
          val cur = ctx.save
          val s1 = "val "+a0+" = M3Map.temp["+genTupleDef(aks.map(x=>x._2))+","+e.tp.toScala+"]()\n"+cpsExpr(e,(v:String)=>a0+".add("+genTuple(aks.map(x=>ctx(x._1)))+","+v+");\n",tmp);
          ctx.load(cur)
          s1+cpsExpr(mapRef(a0,e.tp,aks),co)
      }
    case _ => sys.error("Don't know how to generate "+ex)
  }

  def genStmt(s:Stmt):String = s match {
    case StmtMap(m,e,op,oi) =>
      val (fop,sop)=op match { case OpAdd => ("add","+=") case OpSet => ("add","=") }
      val clear = op match { case OpAdd => "" case OpSet => if (m.keys.size>0) m.name+".clear()\n" else "" }
      val init = oi match {
        case Some(ie) =>
          ctx.load()
          cpsExpr(ie,(i:String)=>
            if (m.keys.size==0) "if ("+m.name+"==0) "+m.name+" = "+i+";\n"
            else "if ("+m.name+".get("+genTuple(m.keys map ctx)+")==0) "+m.name+".set("+genTuple(m.keys map ctx)+","+i+");\n"
          )
        case None => ""
      }
      ctx.load(); clear+init+cpsExpr(e,(v:String) => m.name+(if (m.keys.size==0) " "+sop+" "+v else "."+fop+"("+genTuple(m.keys map ctx)+","+v+")")+";\n",if (op==OpAdd) Some(m.keys zip m.tks) else None)
    case m@MapDef(_,_,_,_) => "" //nothing to do
    case _ => sys.error("Unimplemented") // we leave room for other type of events
  }

  def genTrigger(t:Trigger, s0:System):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtBatchUpdate(Schema(n,cs)) => ("BatchUpdate"+n,cs)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    ctx=Ctx(as.map(x=>(x._1,(x._2,x._1))).toMap); val body=t.stmts.map(genStmt).mkString; ctx=null
    val params = t.evt match {
      case EvtBatchUpdate(Schema(n,_)) =>
        val rel = s0.sources.filter(_.schema.name == n)(0).schema
        val ks = rel.fields.map(_._2)
        val tp = TypeLong
        DeltaMapRefConst(rel.name,Nil).deltaSchema+":M3Map["+genTupleDef(ks)+","+tp.toScala+"]"
      case _ =>
        as.map(a=>a._1+":"+a._2.toScala).mkString(", ")
    }
    "def on"+n+"("+params+") "+(if (body=="") "{ }" else "{\n"+ind(body)+"\n}")
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
      val tk = genTupleDef(m.keys.map(x=>x._2))
      val s = sx.getOrElse(m.name,List[List[Int]]())
      "val "+m.name+" = M3Map.make["+tk+","+m.tp.toScala+"]("+s.map{is=>"(k:"+tk+")=>"+tup(is.map{i=>"k._"+(i+1)}) }.mkString(", ")+");"
    }
  }

  override def genInitializationFor(map:String, keyNames:List[(String,Type)], keyNamesConcat: String) = map+".add("+keyNamesConcat+",1L)"

  // Generate (1:stream events handling, 2:table loading, 3:global constants declaration)
  override def genInternals(s0:System,nextSkip:String="context.become(receive_skip)") : (String,String,String) = {
    // XXX: reduce as much as possible the overhead here to decode data, use Decoder's internals and inline the SourceMux here
    def ev(s:Schema,short:Boolean=true):(String,String,String,List[(String,Type)]) = {
      val fs = if (short) s.fields.zipWithIndex.map{ case ((s,t),i) => ("v"+i,t) } else s.fields
      (fs.map{case(s,t)=>s.toLowerCase+":"+t.toScala}.mkString(","),genTuple(fs.map { case (v,t) => (t,v) }),"("+fs.map{case(s,t)=>s.toLowerCase}.mkString(",")+")",fs)
    }
    val step = 128 // periodicity of timeout verification, must be a power of 2
    val skip = "if (t1>0 && (tN&"+(step-1)+")==0) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; "+nextSkip+" } else tN+=1 } else tN+=1; "
    val pp = if(printProgress > 0L) "printProgress(); " else ""
    val str = s0.triggers.map(_.evt match {
      case EvtAdd(s) =>
        val (i,_,o,pl) = ev(s)
        "case TupleEvent(ord,TupleInsert,\""+s.name+"\",List("+i+")) => "+skip+pp+"onAdd"+s.name+o+"\n"
      case EvtDel(s) =>
        val (i,_,o,pl) = ev(s)
        "case TupleEvent(ord,TupleDelete,\""+s.name+"\",List("+i+")) => "+skip+pp+"onDel"+s.name+o+"\n"
      case b@EvtBatchUpdate(s) =>
        val schema = s0.sources.filter(_.schema.name == s.name)(0).schema
        val (i,_,o,pl) = ev(schema)
        val batchSkip = "if (t1>0 && (tN/"+step+")<((tN+dataList.size)/"+step+")) { val t=System.nanoTime; if (t>t1) { t1=t; tS=1; "+nextSkip+" } else tN+=dataList.size } else tN+=dataList.size; "
        val deltaRel = DeltaMapRefConst(schema.name,Nil).deltaSchema
        val batch = deltaRel+".clear\n"+
                    "  dataList.foreach{ case List("+i+",vv:"+TypeLong.toScala+") => \n    "+deltaRel+".set("+genTuple(schema.fields.zipWithIndex.map{ case ((_,tp),i) => (tp,"v"+i)})+", vv)\n  }; "
        val singleAdd = deltaRel+".clear\n"+
                    "  "+deltaRel+".set("+genTuple(schema.fields.zipWithIndex.map{ case ((_,tp),i) => (tp,"v"+i)})+",  1L); "
        val singleDel = deltaRel+".clear\n"+
                    "  "+deltaRel+".set("+genTuple(schema.fields.zipWithIndex.map{ case ((_,tp),i) => (tp,"v"+i)})+", -1L); "
        "case BatchUpdateEvent(ord,\""+s.name+"\",dataList) => \n  "+batchSkip+"\n  "+pp+"\n  "+batch+"\n  onBatchUpdate"+s.name+"("+deltaRel+")\n"+
        (if(hasOnlyBatchProcessingForAdd(s0,b))
           "case TupleEvent(ord,TupleInsert,\""+s.name+"\",List("+i+")) => \n  "+skip+"\n  "+pp+"\n  "+singleAdd+"\n  onBatchUpdate"+s.name+"("+deltaRel+")\n"
         else "")+
        (if(hasOnlyBatchProcessingForDel(s0,b))
           "case TupleEvent(ord,TupleDelete,\""+s.name+"\",List("+i+")) => \n  "+skip+"\n  "+pp+"\n  "+singleDel+"\n  onBatchUpdate"+s.name+"("+deltaRel+")\n"
         else "")
      case _ => ""
    }).mkString
    val ld0 = s0.sources.filter{s => !s.stream}.map {
      s => {
        val (in,ad,sp) = genStream(s)
        val (i,o,_,pl) = ev(s.schema)
        "SourceMux({ case TupleEvent(ord,TupleInsert,rn,"+i+")=>"+genInitializationFor(s.schema.name,pl,o)+" }, Seq(("+in+","+ad+","+sp+"))).read;" 
      }
    }.mkString("\n");
    (str,ld0,consts)
  }

  def hasOnlyBatchProcessingForAdd(s0:System, evt:EvtBatchUpdate) = s0.triggers.forall{ t => t.evt match {
      case EvtAdd(s) if(evt.schema.name == s.name) => false
      case _ => true
    }
  }

  def hasOnlyBatchProcessingForDel(s0:System, evt:EvtBatchUpdate) = s0.triggers.forall{ t => t.evt match {
      case EvtDel(s) if(evt.schema.name == s.name) => false
      case _ => true
    }
  }

  def genQueries(queries:List[Query]) = {
    queries.map {
      query => {
        query.map match {
          case MapRef(n,_,_) if (n == query.name) => ""
          case _ =>
            ctx = Ctx[(Type,String)]()
            "def "+query.name+"() = {\n"+
            ind(
              if(query.keys.length == 0) cpsExpr(query.map)
              else {
                val mName = "m"+query.name
                val tk = tup(query.keys.map(x=>x._2.toScala))
                val nk = query.keys.map(x=>x._1)
                "val "+mName+" = M3Map.make["+tk+","+query.tp.toScala+"]()\n"+
                cpsExpr(query.map, (v:String) => mName+".add("+genTuple(nk map ctx)+","+v+")")+"\n"+
                mName
              }
            )+"\n}"
        }
      }
    }.mkString("\n")
  }

  override def toMapFunction(q: Query) = {
    val map = q.name
    val m = maps(map)
    val mapKeys = m.keys.map(_._2)
    val nodeName = map+"_node"
    val res = nodeName+"_mres"
    "{ val "+res+" = new scala.collection.mutable.HashMap["+tup(mapKeys.map(_.toScala))+","+q.map.tp.toScala+"](); "+map+".foreach{case (e,v) => "+res+" += ("+(if(mapKeys.size > 1) tup(mapKeys.zipWithIndex.map{ case (_,i) => "e._"+(i+1) }) else "e")+" -> v) }; "+res+".toMap }"
  }
  override def clearOut = {}
  override def onEndStream = ""

  var maps = Map[String,MapDef]() // declared global maps
  def apply(s0:System):String = {
    maps=s0.maps.map(m=>(m.name,m)).toMap
    val (lms,strLMS,ld0LMS,gcLMS) = genLMS(s0)
    val body = if (lms!=null) lms else {
      val ts = s0.triggers.map(genTrigger(_,s0)).mkString("\n\n") // triggers (need to be generated before maps)
      val ms = s0.triggers.map(_.evt match { //delta relations
                 case EvtBatchUpdate(s) =>
                   val schema = s0.sources.filter(_.schema.name == s.name)(0).schema
                   val deltaRel = DeltaMapRefConst(schema.name,Nil).deltaSchema
                   genMap(MapDef(deltaRel,TypeLong,schema.fields,null))+"\n"
                 case _ => ""
               }).mkString +
               s0.triggers.flatMap{ t=> //local maps
                 t.stmts.filter{
                   case MapDef(_,_,_,_) => true
                   case _ => false
                 }.map{
                  case m@MapDef(_,_,_,_) => genMap(m)+"\n"
                  case _ => ""
                 }
               }.mkString +
               s0.maps.map(genMap).mkString("\n") // maps
      ms+"\n\n"+genQueries(s0.queries)+"\n\n"+ts
    }
    val (str,ld0,gc) = if(lms!=null) (strLMS,ld0LMS,gcLMS) else genInternals(s0)
    val ld = if (ld0!="") "\n\ndef loadTables() {\n"+ind(ld0)+"\n}" else "" // optional preloading of static tables content
    freshClear()
    val snap=onEndStream+" sender ! (StreamStat(t1-t0,tN,tS),List("+s0.queries.map(q => (if (q.keys.size > 0) toMapFunction(q) else q.name)).mkString(",")+"))"
    val pp = if(printProgress > 0L) "def printProgress():Unit = if(tN % "+printProgress+" == 0) Console.println((System.nanoTime - t0)+\"\\t\"+tN);\n" else ""
    clearOut
    helper(s0)+"class "+cls+" extends Actor {\n"+ind(
    "import ddbt.lib.Messages._\nimport "+cls+"._\n"+
    "import ddbt.lib.Functions._\n\n"+body+"\n\n"+
    "var t0=0L; var t1=0L; var tN=0L; var tS=0L\n"+
    pp+
    "def receive_skip:Receive = { case EndOfStream | GetSnapshot(_) => "+snap+" case _ => tS+=1 }\n"+
    "def receive = {\n"+ind(str+
      "case StreamInit(timeout) =>"+(if (ld!="") " loadTables();" else "")+" onSystemReady(); t0=System.nanoTime; if (timeout>0) t1=t0+timeout*1000000L\n"+
      "case EndOfStream | GetSnapshot(_) => t1=System.nanoTime; "+snap
    )+"\n}\n"+gc+ld)+"\n}\n"
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

  def getEntryDefinitions:String = tuples.values.mkString("\n")

  // Helper that contains the main and stream generator
  private def helper(s0:System) =
    "import ddbt.lib._\n"+additionalImports()+"\nimport akka.actor.Actor\nimport java.util.Date\n\n"+
    "object "+cls+" {\n"+ind("import Helper._\nval precision = 7; // significative numbers (7 to pass r_sumdivgrp, 10 otherwise)\nval diff_p = Math.pow(0.1,precision)\n"+getEntryDefinitions+"\n"+
    "def execute(args:Array[String],f:List[Any]=>Unit) = bench(args,(d:String,p:Int,t:Long,b:Int)=>run["+cls+"]("+streams(s0.sources)+",p,t,b),f)\n\n"+
    "def main(args:Array[String]) {\n"+ind("execute(args,(res:List[Any])=>{\n"+
    ind(s0.queries.zipWithIndex.map{ case (q,i)=> "println(\""+q.name+":\\n\"+M3Map.toStr(res("+i+"))+\"\\n\")" }.mkString("\n"))+
    "\n})")+"\n}")+"\n}\n"

  override def pkgWrapper(pkg:String, body:String) = "package "+pkg+"\n"+body+"\n"

  override def additionalImports():String = ""
}
