package ddbt.codegen.lms
import ddbt.ast._
import ddbt.lib.{K3Temp,K3Var}

import scala.virtualization.lms.common._
import scala.virtualization.lms.internal._
import scala.reflect.SourceContext
import toasterbooster.lifters._

/**
 * The following LMS operations are implemented by these traits:
 * - Named expressions (possibly mutable) to beautify the emitted code
 * - M3 maps specific operations (get, set, add, foreach, slice, clear)
 * - Abstraction of user-library function application (inlined in k3apply)
 *
 * @author Mohammad Dashti
 */

trait K3MapOps extends Base {
  // Nodes creation
  def k3var(value:Type) : Rep[K3Var[_]]
  def k3temp(key_tp:List[Type],value_tp:Type):Rep[K3Temp[_,_]]
  // Operations on K3Map, K3Var and K3Temp
  def k3get(map:Rep[_], key:List[Rep[_]]=Nil,value_tp:Type):Rep[_]
  def k3set(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3add(map:Rep[_], key:List[Rep[_]],value:Rep[_]):Rep[Unit]
  def k3foreach(map:Rep[_], key: Rep[_], value: Rep[_], body: => Rep[Unit]) : Rep[Unit]
  def k3slice(map:Rep[_],part:Int,partKey:List[Rep[_]]):Rep[_]
  def k3clear(map:Rep[_]):Rep[Unit]
}

trait K3MapOpsExp extends BaseExp with EffectExp with K3MapOps{
  import ManifestHelper.man
  def k3var(value:Type) = reflectMutable(NewK3Var(value,man(value)))
  def k3temp(key:List[Type],value:Type) = reflectMutable(NewK3Temp(key,value,man(key),man(value)))

  def k3get(map:Exp[_], key:List[Exp[_]],value_tp:Type) = K3Get(map,key,man(value_tp))
  def k3set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Set(map,key,value))
  def k3add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) = reflectWrite(map)(K3Add(map,key,value))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body: => Exp[Unit]) = k3foreach(map,key,value,reifyEffects(body))
  def k3foreach(map:Exp[_], key: Exp[_], value: Exp[_], body:Block[Unit]) = reflectEffect(K3Foreach(map,key,value,body),summarizeEffects(body).star)
  def k3slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) = K3Slice(map,part,partKey)
  def k3clear(map:Exp[_]) = reflectWrite(map)(K3Clear(map))
  
  case class NewK3Var[K,V](value:Type,mV:Manifest[V]) extends Def[K3Var[_]]
  case class NewK3Temp[K,V](key:List[Type],value:Type,mK:Manifest[K],mV:Manifest[V]) extends Def[K3Temp[_,_]]
  case class K3Get[T](map:Exp[_], key:List[Exp[_]],mt:Manifest[T]) extends Def[T]
  case class K3Set(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Add(map:Exp[_], key:List[Exp[_]],value:Exp[_]) extends Def[Unit]
  case class K3Foreach(map:Exp[_], key:Exp[_], value:Exp[_], body:Block[Unit]) extends Def[Unit]
  case class K3Slice(map:Exp[_],part:Int,partKey:List[Exp[_]]) extends Def[Exp[_]]
  case class K3Clear(map:Exp[_]) extends Def[Unit]

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
    case K3Set(m,k,v) => Nil
    case K3Add(m,k,v) => Nil
    case _ => super.aliasSyms(e)
  }
}

trait ScalaGenK3MapOps extends ScalaGenBase with ScalaGenEffect {
  val IR: K3MapOpsExp with ExtendedExpressions
  import IR._
  import ddbt.Utils.{ind,tup}

  protected def getBlockContents(blk:Block[_]):String = {
    val save=stream; val wr=new java.io.StringWriter; stream=new java.io.PrintWriter(wr)
    emitBlock(blk); val res=ind(wr.toString); stream=save; res
  }

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case NewK3Var(v,_) => stream.println("var "+quote(sym)+" = "+zeroValue(v))
    case NewK3Temp(ks,v,_,_) => emitValDef(sym, "K3Map.temp["+tup(ks map (_.toScala))+","+v.toScala+"]()")
    case K3Get(m,ks,_) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) => emitValDef(sym, quote(m))
      case _ => emitValDef(sym, quote(m)+".get("+tup(ks map quote)+")")
    }
    case K3Set(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) => stream.println(quote(m)+" = "+quote(v))
      case _ => stream.println(quote(m)+".set("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Add(m,ks,v) => Def.unapply(m) match {
      case Some(Reflect(NewK3Var(_,_),_,_)) => stream.println(quote(m)+" += "+quote(v))
      case _ => stream.println(quote(m)+".add("+(if (ks.size==0) "" else tup(ks map quote)+",")+quote(v)+")")
    }
    case K3Foreach(m,k,v,body) =>
      val block=getBlockContents(body) // enables both the renaming trick and allow nested block indentation
      stream.println(quote(m)+".foreach { ("+quote(k)+","+quote(v)+") =>"); stream.println(block); stream.println("}")
    case K3Slice(m,p,pks) => emitValDef(sym, quote(m)+".slice("+p+","+tup(pks map quote)+")")
    case K3Clear(m) => stream.println(quote(m)+".clear")
    case _ => super.emitNode(sym,rhs)
  }

  def zeroValue(v: Type) = v match {
    case TypeLong => "0L"
    case TypeDouble => "0.0"
    case TypeString => ""
    case TypeDate => "new Date()"
  }
}
