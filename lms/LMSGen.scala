package ddbt.codegen
import ddbt.ast._

class LMSGen(cls:String="Query") extends ScalaGen(cls) {
  import ddbt.ast.M3._

  type Rep[+A] = A // to be replaced

  type Ctx = Map[String,Rep[_]]
  protected val ctx0 = Map[String,Rep[_]]()

  /*
  def mul[T](l:Rep[T],r:Rep[T]):Rep[T] = __mul(l,r)
  def add[T](l:Rep[T],r:Rep[T]):Rep[T] = __add(l,r)
  def cmp[T](l:Rep[T],r:Rep[T]):Rep[T]
  def ex[T](e:Rep[T]):Rep[T]
  def lift[T](n:String,e:Rep[T]):(Rep[T],Ctx)

  def expr(ex:Expr,ctx:Ctx=ctx0):(Rep[_],Ctx) = ex match {
    case Mul(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,cl); (mul(sl,sr),cr)
    case Add(l,r) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,ctx); (add(sl,sr),cl++cr)
    case Cmp(l,r,op) => val (sl,cl)=expr(l,ctx); val (sr,cr)=expr(r,ctx); (cmp(sl,sr),cl++cr)
    case Exists(e) => val (se,ce)=expr(e,ctx); (ex(se),ce)
    case Lift(n,e) => val (se,ce)=expr(e,ctx); val (sl,cl)=lift(n,se); (sl,cl++ce)
    case AggSum(ks,e) => ks.toSet
    case Apply(fn,tp,as) => as.flatMap(a=>a.collect(f)).toSet
    case MapRef(n,tp,ks) => ks.toSet
    case _ => (xx,ctx0)
  }
  */

  override def genTrigger(t:Trigger):String = {
    val (n,as) = t.evt match {
      case EvtReady => ("SystemReady",Nil)
      case EvtAdd(Schema(n,cs)) => ("Add"+n,cs)
      case EvtDel(Schema(n,cs)) => ("Del"+n,cs)
    }
    // val ctx=as.map{ case (n,tp) => (n,freshRef(tp)) }.toMap
    "def on"+n+"("+as.map{a=>a._1+":"+tpe(a._2)} .mkString(", ")+") {\n"+
    "  hello"+ //ind(t.stmts.map{s=>genStmt(s,b)}.mkString)
    "\n}"
  }

  var maps = List[MapDef]() // global maps, to be replaced by a Map[String,LMS_K3Map]
  override def genSystem(s0:System):String = {
    maps=s0.maps; val r=super.genSystem(s0); maps=Nil; r
  }
}
