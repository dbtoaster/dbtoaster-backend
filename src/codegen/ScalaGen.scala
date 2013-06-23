// Generators to emit LMS nodes from AST

package ddbt.codegen
import ddbt.ast._

object ScalaGen {
  def i(s:String,n:Int=1) = { val i="  "*n; i+s.replaceAll(" +$","").replace("\n","\n"+i) }
  def tpe(tp:Type):String = { val s=tp.toString; s.substring(0,1).toUpperCase+s.substring(1).toLowerCase }
  def tup(vs:List[String]) = { val v=vs.mkString(","); if (vs.size>1) "("+v+")" else v }

  private var counter:Int = 0
  def fresh = { counter=counter+1; "x"+counter }


  // e0:expression to convert
  // b0:bound variables
  // d0:delimited continuation function (code with 'holes' to be filled by expression)
  import ddbt.ast.M3._
  def cpsExpr(e0:Expr,b0:Set[String],c0:String=>String):String = e0 match {
    case c:Const => c0(c.toString)
    case Ref(n) => c0(n)
    case MMapRef(n,tp,ks) =>
      val (ko,ki) = ks.zipWithIndex.span{case(k,i)=> b0.contains(k)}
      if (ki.size==0) c0(n+".get("+tup(ks)+")") // all keys are bounded
      else {
        val k0=fresh; val v0=fresh;
        n+ko.map{case (k,i)=>".slice("+i+","+k+")"}.mkString+".foreach { case ("+k0+","+v0+") =>\n"+i( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+ // bind unbounded variables from retrieved key
          c0(v0))+"\n}"
      }  
    case Lift(n,e) => cpsExpr(e,b0,(v:String)=>"val "+n+" = "+v+";")+"\n"+c0(n)

    
    case AggSum(ks,e) => c0(cpsExpr(e,b0,(v:String)=>"AggSum["+tup(ks)+"](\n"+i(v)+"\n)"))
    
    
    case Mul(l,r) => c0(cpsExpr(l,b0,(ll:String)=>cpsExpr(r,b0,(rr:String)=>"("+ll+" * "+rr+")")))
    case Add(l,r) => c0(cpsExpr(l,b0,(ll:String)=>cpsExpr(r,b0,(rr:String)=>"("+ll+" + "+rr+")")))
    case Exists(e) => c0(cpsExpr(e,b0,(v:String)=>"EXISTS("+v+")"))
    
    case Apply(f,tp,as) => var app = f+"("; as.foreach { a=>cpsExpr(a,b0,(v:String)=>app+v+",") };
      c0((if (as.size>0) app.substring(0,app.length-1) else app)+")")
    case Cmp(l,r,op) => c0(cpsExpr(l,b0,(ll:String)=>cpsExpr(r,b0,(rr:String)=>"("+ll+" "+op+" "+rr+")")))
    case Tuple(_,_) => sys.error("Tuple should not appear")
  }
  // use delimited CPS to generate code
  // we construct bottom-up, generate the code, and the list of unbounded variables






  // generate expression code where b is the list of bound variables, return generated code and set of unbounded variables
//  import ddbt.ast.M3._
  def genExpr(e:Expr,b:Set[String]):(String,Set[String]) = e match {
    case c:Const => (c.toString,Set())
    case Ref(n) => (n,if (b.contains(n)) Set() else Set(n))
    case Mul(Lift(n,v),e) =>
      val (vv,vf)=genExpr(v,b);
      val (ee,ef)=genExpr(Mul(Ref(n),e),b+n); 
      ("val "+n+" = "+vv+";\n"+ee,ef++vf)
    case Mul(MMapRef(n,t,keys),e) =>
      val k0=fresh; val v0=fresh;
      val (ee,ef)=genExpr(Mul(Ref(v0),e),b++keys.toSet++Set(v0));
      // We split keys in
      // - ko : keys that are bound from outside => we slice on them
      // - ki : keys that are not bound => we read them from map key
      val (ko,ki) = keys.zipWithIndex.span{case(k,i)=> b.contains(k)}
      (n+ko.map{case (k,i)=>".slice("+i+","+k+")"}.mkString+".foreach { case ("+k0+","+v0+") =>\n"+i( // XXX: slice on already bound variables
      ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+ // XXX: get types from referred map
      ee)+"\n}",ef)

    case AggSum(ks,e) =>
      val (ee,ef)=genExpr(e,b++ks.toSet);
      ("AggSum(["+ks+"],\n"+i(ee)+"\n)",ef)
   
    /*
      
      val rk=ks.toSet--b
      //if (rk.size==0) genExpr(e,b) // no aggregation needs to be done
      //else {
      //   val (ee,ef)=genExpr(e,b++ks.toSet);

         println("--------------------------")
         println("At AggSum("+ks+","+e+")")
         println("b = "+b)
         println("ef = "+ef)
      
         // XXX: real aggregation, continue further here
         ("aggsum("+ks.mkString(",")+") = FORALL("+(ef--b--rk).toList.mkString(",")+") GROUPBY("+ks.mkString(",")+") {\n"+i(ee)+"\n}",(ef--(ef--b))--rk)
      //}
    */
      //val (ee,ef)=genExpr(e,b++ks.toSet);
      //("FORALL("+(ef--b--ks.toSet).toList.mkString(",")+") GROUPBY("+ks.mkString(",")+") {\n"+i(ee)+"\n}",ef--ks.toSet--(ef--b--ks.toSet))





    case MMapRef(n,t,ks) =>
      /*
      n+".foreach { (k,v) =>\n"+
      // get types from map
      ks.zipWithIndex.map{(k,i)=>"val "+k+" = k._"+(i+1)+";\n"}+
      "<<continuation with (v) in expression>>"
      "}"
      */
      // replace by a foreach in the map ?
    
      (if (ks.size==0) n+".get()" else n+".get("+tup(ks)+")",ks.filter(k=> !b.contains(k)).toSet)
    case Tuple(n,as) => sys.error("Tuple should not appear")
    case Lift(n,v) => ("",Set()) // sys.error("Useless lift "+n+" ^= "+v)
      //if (!b.contains(n)) sys.error("Missing assignment "+n+" ^= "+v);
    // set product
    case Mul(l,Mul(x:Lift,r)) => genExpr(Mul(x,Mul(l,r)),b)
    case Mul(l,r) => val (ll,lf)=genExpr(l,b); val (rr,rf)=genExpr(r,b); ("(\n"+i(ll+" * "+rr)+"\n)",lf++rf)
    // set union
    case Add(l,r) => val (ll,lf)=genExpr(l,b); val (rr,rf)=genExpr(r,b); ("(\n"+i(ll+" + "+rr)+"\n)",lf++rf)
    case Exists(e) =>  val (ee,ef)=genExpr(e,b); ("EXISTS("+ee+")",ef)
    case Apply(f,t,as) => val ar=as.map(a=>genExpr(a,b)); (f+"("+ar.map(_._1).mkString(",")+")",ar.flatMap(_._2).toSet) // here we could inline immediately functions
    case Cmp(l,r,op) => val (ll,lb)=genExpr(l,b); val (rr,rb)=genExpr(r,b); ("("+l+" "+op+" "+r+")",lb++rb)
  }
  
  def genStmt(s:Stmt,b:Set[String]):String = {
    // we leave room for other type of events
    val (m,e,op) = s match {
      case StAdd(m,e)=>(m,e,"add")
      case StSet(m,e)=>(m,e,"set")
      case _ => sys.error("Unimplemented")
    }
    val (ko,ki) = m.keys.zipWithIndex.span{case(k,i)=> b.contains(k)}
    val fun = if (m.keys.size==0) m.name+"."+op+"(" else m.name+"."+op+"("+tup(m.keys)+","
    val con = if (ki.size==0) (res:String)=>fun+res+");" // all keys are bounded
      else { val k0=fresh; val v0=fresh;
        (res:String)=>m.name+ko.map{case (k,i)=>".slice("+i+","+k+")"}.mkString+".foreach { case ("+k0+","+v0+") =>\n"+i( // slice on bound variables
          ki.map{case (k,i)=>"val "+k+" = "+k0+"._"+(i+1)+";"}.mkString("\n")+"\n"+ // bind unbounded variables from retrieved key
          fun+res+");")+"\n}"
      }

    cpsExpr(e,b,con)
    


    
    /*
    val (ee,ef) = genExpr(e,b)
    
    val st = if (m.keys.size==0) m.name+"."+fn+"("+ee+");"
             else m.name+"."+fn+"("+tup(m.keys)+","+ee+");"
    
    if (ef.size==0) st
    else "forall("+ef.toList.mkString(",")+") {\n"+i(st)+"\n}"
    */
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
  
  def genMMap(m:MMap):String = {
    if (m.keys.size==0) "val "+m.name+" = new MVal["+tpe(m.tp)+"]();"
    else "val "+m.name+" = new MMap["+tup(m.keys.map(x=>tpe(x._2)))+","+tpe(m.tp)+"](List("+"<<<SECONDARY_INDICES>>>"+"));"
  }

  def genSystem(s:System):String = {
    // import scala.language.implicitConversions  
    // implicit def boolConv(b:Boolean):Long = if (b) 1L else 0L
  
    s.maps.map{genMMap(_)}.mkString("\n")+"\n\n"+s.triggers.map{genTrigger(_)}.mkString("\n\n")
  }
  
}

/*
CREATE STREAM BIDS(BIDS_T float, BIDS_ID int, BIDS_BROKER_ID int, BIDS_VOLUME float, BIDS_PRICE float)
CREATE STREAM ASKS(ASKS_T float, ASKS_ID int, ASKS_BROKER_ID int, ASKS_VOLUME float, ASKS_PRICE float)

ON + BIDS(BIDS_T, BIDS_ID, BIDS_BROKER_ID, BIDS_VOLUME, BIDS_PRICE) {
   COUNT(int)[][AXFINDER] += ((AXFINDER ^= 1) * COUNT_mBIDS2(int)[][]);
   COUNT_mASKS2(int)[][] += 1;
}

DECLARE MAP COUNT(int)[][AXFINDER:int] := 
DECLARE MAP COUNT_mASKS2(int)[][] := 
DECLARE MAP COUNT_mBIDS2(int)[][] := 

// ---------------------------------------------------

class onInsertBIDS extends ((Double, Long, Long, Double, Double,
		org.dbtoaster.dbtoasterlib.K3Collection.K3PersistentCollection[Long, Long], // key-value types,  Map "COUNT"
		org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long], // Map COUNT_mASKS2
		org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long]) // Map COUNT_mBIDS2
		=> (Unit)) {
   def apply(x54: Double, x55: Long, x56: Long, x57: Double, x58: Double, // Bid tuple
	      x59: org.dbtoaster.dbtoasterlib.K3Collection.K3PersistentCollection[Long, Long],
	      x60: org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long],
	      x61: org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long]): Unit = {
      val x63 = 1L // key AXFinder(exists?)
      val x70 = if (x59.contains(1L)) x59.lookup(x63, 0) else 0L
      x59.updateValue(x63, x70 + x61.get())
      // COUNT_mASKS2(int)[][] += 1;
      x60.update(x60.get() + 1L)
   }
}



// ---------------------------------------------------

class onInsertBIDS extends ((Double, Long, Long, Double, Double,
		org.dbtoaster.dbtoasterlib.K3Collection.K3PersistentCollection[Long, Long], // key-value types,  Map "COUNT"
		org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long], // Map COUNT_mASKS2
		org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long]) // Map COUNT_mBIDS2
		=> (Unit)) {
   def apply(x54: Double, x55: Long, x56: Long, x57: Double, x58: Double, // Bid tuple
	      x59: org.dbtoaster.dbtoasterlib.K3Collection.K3PersistentCollection[Long, Long],
	      x60: org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long],
	      x61: org.dbtoaster.dbtoasterlib.K3Collection.SimpleVal[Long]): Unit = {
      val x8 = (1L, 1L) // AXFinder ^=1
      val x9 = List(x8)
      val x65 = x61.get() // COUNT_mBIDS2(int)[][]
      x9.foreach {
         x62 =>
            val x63 = x62._1
            val x64 = x62._2
            val x66 = x64 * x65
            val x68 = x59.contains(x63)
            val x70 = if (x68) {
               val x69 = x59.lookup(x63, 0)
               x69
            } else {
               0L
            }
            val x71 = x70 + x66
            x59.updateValue(x63, x71)
      }
      // COUNT_mASKS2(int)[][] += 1;
      val x75 = x60.get()
      val x76 = x75 + 1L
      x60.update(x76)
      ()
   }
}
*/
