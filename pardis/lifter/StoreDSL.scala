package ddbt.lib.store.deep

import ch.epfl.data.sc.pardis.deep.scalalib.StringComponent
import ch.epfl.data.sc.pardis.ir.Constant
import ddbt.ast.{TypeDouble, TypeLong, Type}
import ddbt.lib.store.{IHash, Store, Entry}
import lifter.{SCLMSInterop, TypeToTypeRep}

/**
 * Created by khayyam on 4/8/15.
 */

trait StoreDSL extends MStoreComponent with SCLMSInterop with DateComponent with StringComponent with TypeToTypeRep {
  // cases classes
  case class M3Apply[T: TypeRep](name1:String,args1:List[Rep[_]]) extends FunctionDef[T](None, "U" + name1, List(args1)) {

  }
  def m3_apply[T: TypeRep](name1: String, args: List[Rep[_]]): Rep[T] = M3Apply[T](name1, args)
  // case class SteNewSEntry   [E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) extends Def[E]
  // case class SteSampleSEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]) extends Def[E]


  def m3apply(fn:String,args:List[Rep[_]],tp:Type): Rep[_] = {
    fn match {
      case "div" => div(args(0).asInstanceOf[Rep[Double]])
      case "mul" => tp match {
        case TypeLong => mulLong(args(0).asInstanceOf[Rep[Long]], args(1).asInstanceOf[Rep[Long]])
        case TypeDouble => mulDouble(args(0).asInstanceOf[Rep[Double]], args(1).asInstanceOf[Rep[Double]])
        case _ => m3_apply(fn,args)(man(tp))
      }
      case "listmax" => max(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "listmin" => min(args(0).asInstanceOf[Rep[Double]],args(1).asInstanceOf[Rep[Double]])
      case "substring" => substring(args(0).asInstanceOf[Rep[String]],args(1).asInstanceOf[Rep[Long]],args(2).asInstanceOf[Rep[Long]])
      case "date" => args(0) match {
        case Constant(strDate) => Constant(ddbt.lib.Functions.Udate(strDate.asInstanceOf[String]))
        case _ => m3_apply(fn,args)(man(tp))
      }
      case _ => m3_apply(fn,args)(man(tp)) // fallback for large or unknown functions
    }
  }


  def m3temp[E<:Entry]()(implicit tp:TypeRep[E]):Rep[Store[E]] = null
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = null
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = null
  def steGet[E<:Entry:TypeRep](x: Rep[E], i: Int) = null
  def stClear      [E<:Entry:TypeRep](x: Rep[Store[E]]) = null

  def stNewEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) = null//SteNewSEntry[E](x, args)
  def stNewEntry2[E<:Entry:TypeRep](x: Rep[Store[E]], args:Rep[Any]*):Rep[E] = null//stNewEntry[E](x, args)

  def storeEntryType(sym:Rep[_]) = ""

  def dtGetTime(x: Rep[Date]): Rep[Long] = dateGetTime(x)
  def stProxyGet[E<:Entry: TypeRep](x: Rep[Store[E]], args:(Int,Rep[Any])*):Rep[E] = steGet(stSampleEntry(x, args),-1)
  def stSampleEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]):Rep[E] = null //SteSampleSEntry[E](x, args)

  // FIXME
  def store2StoreOpsCls[E <: Entry](store: Rep[Store[E]]) = new MStoreRep(store.asInstanceOf[Rep[MStore[E]]])(runtimeType[Int].asInstanceOf[TypeRep[E]])
  // def dtGetYear(x: Rep[Date]): Rep[Long] = dateGetYear(x)

  // helper functions
  def div(x: Rep[Double]): Rep[Double] = unit(1.0) / x

  def mulLong(l: Rep[Long], r: Rep[Long]): Rep[Long] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString=="Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString=="Double" => Constant(scala.runtime.BoxesRunTime.unboxToDouble(v).toLong)
      case _ => r
    })
    numeric_times[Long](ll,rr)
  }
  def mulDouble(l: Rep[Double], r: Rep[Double]): Rep[Double] = {
    val ll = (l match {
      case Constant(v) if l.tp.toString=="Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => l
    })
    val rr = (r match {
      case Constant(v) if r.tp.toString=="Long" => Constant(scala.runtime.BoxesRunTime.unboxToLong(v).toDouble)
      case _ => r
    })
    numeric_times[Double](ll,rr)
  }
  def max(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 > v2, v1, v2)
  def min(v1: Rep[Double], v2: Rep[Double]): Rep[Double] = __ifThenElse(v1 < v2, v1, v2)

  def substring(str: Rep[String], start: Rep[Long], length: Rep[Long]): Rep[String] = null


}