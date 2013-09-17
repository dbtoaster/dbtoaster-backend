package toasterbooster.lifters

import xml._
import scala.actors.Actor._
import scala.virtualization.lms.common._
import org.dbtoaster.dbtoasterlib.K3Collection._
import scala.reflect.SourceContext
import ddbt.lib._
import scala.language.implicitConversions

/**
 * Lifter Classes for K3Var
 */
trait K3VarOps extends Base with Variables {

  class K3VarOpsCls[K: Manifest](x: Rep[K3Var[K]]) {
    def apply(name: Rep[String], defVal: Rep[K]): Rep[K3Var[K]] =  svApply[K](name, defVal);
    def get(): Rep[K] = svGet[K](x)
    def update(value: Rep[K]) = svUpdate[K](x, value)
    def mutable: Rep[K3Var[K]] = svMutable[K](x)
  }

  implicit def simpleVal2K3VarOpsCls[K: Manifest](x: Rep[K3Var[K]]): K3VarOpsCls[K] = new K3VarOpsCls[K](x)
  def svApply[K: Manifest](name: Rep[String], defVal: Rep[K]): Rep[K3Var[K]]
  def svGet[K:Manifest](x: Rep[K3Var[K]]): Rep[K]
  def svUpdate[K](x: Rep[K3Var[K]], value: Rep[K]): Rep[Unit]
  def svMutable[K: Manifest](x: Rep[K3Var[K]]): Rep[K3Var[K]]
}

trait K3VarExp extends K3VarOps with BaseExp with EffectExp with VariablesExp {

  case class SvGet[K:Manifest](x: Exp[K3Var[K]]) extends Def[K] {
    val mK = manifest[K]
  }
  case class SvUpdate[K](x: Exp[K3Var[K]], value: Exp[K]) extends Def[Unit]
  case class NewK3Var[K](mK: Manifest[K], name: Exp[String], defVal: Exp[K]) extends Def[K3Var[K]]
  case class SvMutable[K](x: Exp[K3Var[K]]) extends Def[K3Var[K]]

  def newK3Var[K: Manifest](name: Exp[String], defVal: Exp[K]): Exp[K3Var[K]] = reflectMutable(NewK3Var(manifest[K], name, defVal));

  def svApply[K: Manifest](name: Exp[String], defVal: Exp[K]): Exp[K3Var[K]] = newK3Var[K](name, defVal);
  def svGet[K:Manifest](x: Exp[K3Var[K]]) = SvGet[K](x);
  def svUpdate[K](x: Exp[K3Var[K]], value: Exp[K]) = reflectWrite(x)(SvUpdate[K](x, value));
  def svMutable[K: Manifest](x: Exp[K3Var[K]]) = reflectMutable(SvMutable[K](x))
 
  //////////////
  // mirroring
  override def mirror[A:Manifest](e: Def[A], f: Transformer)(implicit pos: SourceContext): Exp[A] = (e match {
    case NewK3Var(mk, name, defVal) => NewK3Var(mtype(mk), f(name), f(defVal))
    case e@SvGet(x) => svGet(f(x))(mtype(e.mK))
    case SvUpdate(x, value) => svUpdate(f(x), f(value))
    case SvMutable(x) => svMutable(f(x))
    case Reflect(NewK3Var(mk, name, defVal), u, es) => reflectMirrored(Reflect(NewK3Var(mtype(mk), f(name), f(defVal)), mapOver(f,u), f(es)))(mtype(manifest[A]))
    case Reflect(e@SvGet(x), u, es) => reflectMirrored(Reflect(SvGet(f(x))(mtype(e.mK)), mapOver(f,u), f(es)))(mtype(manifest[A]))
    case Reflect(SvUpdate(x, value), u, es) => reflectMirrored(Reflect(SvUpdate(f(x), f(value)), mapOver(f,u), f(es)))(mtype(manifest[A]))
    case Reflect(SvMutable(x), u, es) => reflectMirrored(Reflect(SvMutable(f(x)), mapOver(f,u), f(es)))(mtype(manifest[A]))
    case _ => super.mirror(e,f)
  }).asInstanceOf[Exp[A]] // why??
}

trait ScalaGenK3Var extends ScalaGenBase {
  val IR: K3VarExp
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case NewK3Var(mK, name, defVal) => emitValDef(sym, "K3Var[" + mK + "](" + quote(name) + "," + quote(defVal) + ")")
    case SvGet(x) => emitValDef(sym, "" + quote(x) + ".get()");
    case SvUpdate(x, value) => emitValDef(sym, "" + quote(x) + ".update(" + quote(value) + ")");
    case SvMutable(x) => emitValDef(sym, "" + quote(x) + " // mutable K3Var");
    case _ => super.emitNode(sym, rhs)
  }
}