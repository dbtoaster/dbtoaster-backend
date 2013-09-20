package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Map,K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.reflect.SourceContext

trait M3Ops extends Base {
  // Nodes creation
  def named(name:String,tp:Type):Rep[_]
  def k3temp(key_tp:List[Type],value_tp:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:Rep[_], key:List[Rep[_]]=Nil,value_tp:Type):Rep[_]
  def k3set(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:Rep[_], key: Rep[_], value: Rep[_], body:Rep[Unit]) : Rep[Unit]
  def k3aggr(map:Rep[_], key: Rep[_], value: Rep[_], body:Rep[_], body_tp:Type) : Rep[_]
  def k3slice(map:Rep[_],part:Int,partKey:List[Rep[_]]):Rep[_]
  def k3clear(map:Rep[_]):Rep[Unit]
  // Function application
  def k3apply(fn:String,args:List[Rep[_]],tp:Type):Rep[_]
}

trait M3OpsExp extends BaseExp with EffectExp with M3Ops {
  import ManifestHelper.man
  def named(name:String,tp:Type) = Named(name,man(tp))
  def k3temp(key:List[Type],value:Type) = NewK3Temp(key,value,man(key),man(value))
  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = K3Set(map,key,value)
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = K3Add(map,key,value)
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Exp[Unit]) = K3Foreach(map,key,value,body)
  def k3aggr(map:Exp[_], key: Exp[_], value: Exp[_], body:Exp[_], body_tp:Type) = K3Aggr(map,key,value,body,man(body_tp))
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = K3Slice(map,part,partKey)
  def k3clear(map:Exp[_]) = K3Clear(map)
  def k3apply(fn:String,args:List[Exp[_]],tp:Type) = fn match {
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
  case class K3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Exp[Unit]) extends Def[Unit]
  case class K3Aggr[T](map:Exp[_], key:Exp[_], value:Exp[_], body:Exp[_], mT:Manifest[T]) extends Def[T]
  case class K3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  case class K3Clear(map:Exp[_]) extends Def[Unit]
  case class K3Apply[T](name:String,args:List[Exp[_]],mT:Manifest[T]) extends Def[T]
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
    case K3Foreach(m,k,v,body) => stream.println(quote(m)+".foreach(("+quote(k)+","+quote(v)+") => "+quote(body)+")")
    case K3Aggr(m,k,v,body,_) => emitValDef(sym, quote(m)+".aggr(("+quote(k)+","+quote(v)+") => "+quote(body)+")")
    case K3Slice(m,p,pks) => emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
    case K3Clear(m) => stream.println(quote(m)+".clear")
    case K3Apply(fn,args,_) => emitValDef(sym,fn+"("+(args map quote).mkString(",")+")")
    case _ => super.emitNode(sym,rhs)
  }
}
