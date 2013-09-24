package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Map,K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.reflect.SourceContext

trait M3Ops extends Base {
  // Nodes creation
  def named(name:String,tp:Type,mutable:Boolean=false):Rep[_]
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]):Rep[T]
  def k3var(value:Type) : Rep[K3Var[_]]
  def k3temp(key_tp:List[Type],value_tp:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:Rep[_], key:List[Rep[_]]=Nil,value_tp:Type):Rep[_]
  def k3set(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:Rep[_], key: Rep[_], value: Rep[_], body: => Rep[Unit]) : Rep[Unit]
  def k3slice(map:Rep[_],part:Int,partKey:List[Rep[_]]):Rep[_]
  def k3clear(map:Rep[_]):Rep[Unit]
  // Function application
  def k3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends BaseExp with EffectExp with M3Ops
    with Equal with NumericOps with MathOps with DateOps with StringOps with PrimitiveOps with IfThenElseExp {
  import ManifestHelper.man
  def named(name:String,tp:Type,mutable:Boolean=false) = named(name,mutable)(man(tp))
  def named[T](name:String,mutable:Boolean=false)(implicit mT:Manifest[T]) = { val n=Named(name)(mT); if (mutable) reflectMutable(n) else n }
  def k3var(value:Type) = reflectMutable(NewK3Var(value,man(value)))
  def k3temp(key:List[Type],value:Type) = reflectMutable(NewK3Temp(key,value,man(key),man(value)))

  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Set(map,key,value))
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Add(map,key,value))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = k3foreach(map,key,value,reifyEffects(body))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = reflectEffect(K3Foreach(map,key,value,body),summarizeEffects(body).star)
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = K3Slice(map,part,partKey)
  def k3clear(map:Exp[_]) = K3Clear(map)

  def k3apply(fn:String,args:List[Exp[_]],tp:Type) = fn match {
    case "div" => val x=args(0).asInstanceOf[Rep[Double]]; __ifThenElse(__equal(x,unit(0.0)),unit(0.0),numeric_divide(unit(1.0),x))
    case "listmax" => (args(0),args(1)) match { case (x:Rep[Long] @unchecked,y:Rep[Long] @unchecked) => math_max(x,y) } // type erased anyway
    case "listmin" => (args(0),args(1)) match { case (x:Rep[Long] @unchecked,y:Rep[Long] @unchecked) => math_min(x,y) } // type erased anyway
    case "substring" =>
      def i(n:Int):Exp[Int] = long_toint(args(n).asInstanceOf[Exp[Long]])
      val s = args(0).asInstanceOf[Exp[String]]
      if (args.size<3) string_substring(s,i(1)) else string_substring(s,i(1),i(2))
    // XXX: inline library functions here
    case _ => K3Apply(fn,args,man(tp)) // fallback for large or unknown functions
  }

  case class Named[T](n:String)(implicit mT:Manifest[T]) extends Def[T]
  case class NewK3Var[K,V](value:Type,mV:Manifest[V]) extends Def[K3Var[_]]
  case class NewK3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
  case class K3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Block[Unit]) extends Def[Unit]
  case class K3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  case class K3Clear(map:Exp[_]) extends Def[Unit]
  case class K3Apply[T](name:String,args:List[Exp[_]],mT:Manifest[T]) extends Def[T]

  override def syms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => syms(k):::syms(v):::syms(b)
    case _ => super.syms(e)
  }
  override def boundSyms(e: Any): List[Sym[Any]] = e match {
    case K3Foreach(m,k,v,b) => effectSyms(k):::effectSyms(v):::effectSyms(b)
    case _ => super.boundSyms(e)
  }
  override def symsFreq(e: Any): List[(Sym[Any], Double)] = e match {
    case K3Foreach(m,k,v,b) => freqHot(k):::freqHot(v):::freqHot(b)
    case _ => super.symsFreq(e)
  }
  override def aliasSyms(e: Any): List[Sym[Any]] = e match {
    case K3Get(m,k,t) => Nil
    case K3Set(m,k,v) => Nil
    case K3Add(m,k,v) => Nil
    case _ => super.aliasSyms(e)
  }
/*
  override def containSyms(e: Any): List[Sym[Any]] = e match {
    case K3Get(m,k,t) => Nil //syms(m):::syms(k)
    case _ => super.containSyms(e)
  }
  override def extractSyms(e: Any): List[Sym[Any]] = e match {
    case K3Get(m,k,t) => Nil //syms(m):::syms(k)
    case _ => super.extractSyms(e)
  }
  override def copySyms(e: Any): List[Sym[Any]] = e match {
    case K3Get(m,k,t) => Nil
    case _ => super.copySyms(e)
  }
*/
/*
  // alloc = reflectMutable()
  def rw[A:Manifest](d:Def[A], read:List[Exp[Any]]=Nil, write:List[Exp[Any]]=Nil):Exp[A] = {
    reflectEffect(d,infix_andAlso(Read(read flatMap syms),Write(write flatMap syms)))
  }
  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = rw(K3Get(map,key,man(value_tp)),List(map),Nil)
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = rw(K3Set(map,key,value),Nil,List(map))
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = rw(K3Add(map,key,value),Nil,List(map))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = k3foreach(map,key,value,reifyEffects(body))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = {
    reflectEffect(K3Foreach(map,key,value,body),infix_andAlso(summarizeEffects(body),Read(syms(map))).star)
  }
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = rw(K3Slice(map,part,partKey),List(map),Nil)
  def k3clear(map:Exp[_]) = rw(K3Clear(map),Nil,List(map))
*/
}

trait ScalaGenM3Ops extends ScalaGenBase with ScalaGenEffect with ScalaGenIfThenElse {
  val IR: M3OpsExp
  import IR._
  import ddbt.Utils.{ind,tup}

  private def getBlock(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  private val nameAttr = "_name"
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    // LMS create useless undeclared Unit symbols, plus we know we only have one branch (initialization)
    case IfThenElse(c,a,b) if (quote(getBlockResult(b))=="()") =>
        stream.println("if (" + quote(c) + ") {")
        stream.println(getBlock(a))
        //stream.println("  "+quote(getBlockResult(a)))
        stream.println("}")
    case Named(n) => /*emitValDef(sym, n);*/ sym.attributes.update(nameAttr,n)
    case NewK3Var(v,_) => emitValDef(sym, "new K3Var["+v.toScala+"]()")
    case NewK3Temp(ks,v,_,_) => emitValDef(sym, "K3Map.temp["+tup(ks map (_.toScala))+","+v.toScala+"]()")
    case K3Get(m,ks,_) => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
    case K3Set(m,ks,v) => stream.println(quote(m)+".set("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    case K3Add(m,ks,v) => stream.println(quote(m)+".add("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    case K3Foreach(m,k,v,body) =>
      val block=getBlock(body) // enables both the renaming trick and allow nested block indentation
      stream.println(quote(m)+".foreach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
    case K3Slice(m,p,pks) => emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
    case K3Clear(m) => stream.println(quote(m)+".clear")
    case K3Apply(fn,args,_) => emitValDef(sym,"U"+fn+"("+(args map quote).mkString(",")+")")
    case _ => super.emitNode(sym,rhs)
  }
  override def quote(x: Exp[Any]) : String = x match {
    case sym@Sym(_) if sym.attributes.contains(nameAttr) => sym.attributes(nameAttr).toString
    case _ => super.quote(x)
  }
}
