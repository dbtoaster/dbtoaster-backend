package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Map,K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.reflect.SourceContext

trait M3Ops extends Base {
  // This is slightly incorrect but ultimately we plan to hide these
  // implementation details under a common interface
  type K3M = Rep[K3Map[_,_]] // || K3Temp[_,_] || K3Var[_]

  // Nodes creation
  def named(name:String,tp:Type):Rep[_]
  def k3temp(key:List[Type],value:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:K3M, key:List[Rep[_]],value_tp:Type):Rep[_]
  def k3set(map:K3M, key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:K3M, key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:K3M, f:(Rep[_],Rep[_])=>Rep[Unit]):Rep[Unit]
  def k3aggr[T:Manifest](map:K3M, f:(Rep[_],Rep[_])=>Rep[T]):Rep[T]
  def k3slice(map:K3M,part:Int,partKey:Rep[_]):K3M
  def k3clear(map:K3M):Rep[Unit]
  // Function application
  def k3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends BaseExp with M3Ops {
  import ManifestHelper.man
  def named(name:String,tp:Type) = Named(name,man(tp))
  def k3temp(key:List[Type],value:Type) = NewK3Temp(key,value,man(key),man(value))
  def k3get(map:K3M, key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:K3M, key:List[Exp[_]],value:Exp[_]) = K3Set(map,key,value)
  def k3add(map:K3M, key:List[Exp[_]],value:Exp[_]) = K3Add(map,key,value)
  def k3foreach[K:Manifest,V:Manifest](map:K3M, f:(Exp[K],Exp[V])=>Exp[Unit]) = K3Foreach(map,f)
  def k3aggr[T:Manifest](map:K3M, f:(Exp[_],Exp[_])=>Exp[T]) = K3Aggr(map,f)
  def k3slice(map:K3M,part:Int,partKey:Exp[_]) = K3Slice(map,part,partKey)
  def k3clear(map:K3M) = K3Clear(map)
  def k3apply(fn:String,args:List[Rep[_]],tp:Type) = fn match {
    // inline here
    /*
    case "div" => //(x: Double): Double = if (x==0.0) 0.0 else 1.0 / x
    case "listmax" // (v1: Long, v2: Long): Long = Math.max(v1, v2)
                   // (v1: Double, v2: Double): Double = Math.max(v1, v2)
    case "substring" //(s:String,b:Long,e:Long= -1) = if (e== -1) s.substring(b.toInt) else s.substring(b.toInt,e.toInt)
    case "vec_length" //(x:Double, y:Double, z:Double):Double = Vector(x,y,z).length
    */
    case _ => K3Apply(fn,args,man(tp)) // fallback for large or unknown functions
  }
  case class Named[T](n:String,mT:Manifest[T]) extends Def[T]
  case class NewK3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
  case class K3Get[T](map:K3M, key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:K3M, key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:K3M, key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach[K:Manifest,V:Manifest](map:K3M, f:(Exp[K],Exp[V])=>Exp[Unit]) extends Def[Unit] { val (k,v)=(fresh[K],fresh[V]); val body=f(k,v) }
  case class K3Aggr[T:Manifest](map:K3M, f:(Exp[_],Exp[_])=>Exp[T]) extends Def[T] {}
  case class K3Slice(map:K3M,part:Int,partKey:Exp[_]) extends Def[K3Map[_,_]]
  case class K3Clear(map:K3M) extends Def[Unit]
  case class K3Apply[T](name:String,args:List[Rep[_]],mT:Manifest[T]) extends Def[T]
}

trait ScalaGenM3Ops extends ScalaGenBase {
  val IR: M3OpsExp
  import IR._

  import ddbt.Utils.tup
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Named(n,_) => emitValDef(sym, n)
    case NewK3Temp(ks,v,_,_) => emitValDef(sym, "K3Temp.temp["+tup(ks map (_.toScala))+","+v.toScala+"]()")
    case K3Get(m,ks,_) => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
    case K3Set(m,ks,v) => stream.println(quote(m)+".set("+tup(ks map quote)+","+quote(v)+")")
    case K3Add(m,ks,v) => stream.println(quote(m)+".add("+tup(ks map quote)+","+quote(v)+")")
    case f@K3Foreach(m,_) => stream.println(quote(m)+".foreach( ("+quote(f.k)+","+quote(f.v)+") => "+quote(f.body)+")")
    //case K3Aggr(m,f) => emitValDef(sym, quote(m)+".aggr("+quote(f)+")")
    case K3Slice(m,p,pk) => emitValDef(sym, quote(m)+".slice("+p+","+quote(pk)+")")
    case K3Clear(m) => stream.println(quote(m)+".clear")
    case K3Apply(fn,args,_) => emitValDef(sym,fn+"("+(args map quote).mkString(",")+")")
    case _ => super.emitNode(sym,rhs)
  }
}
