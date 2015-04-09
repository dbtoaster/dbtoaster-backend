package ddbt.lib.store.deep

import ch.epfl.data.pardis.deep.scalalib.StringComponent
import ddbt.ast.{TypeDouble, TypeLong, Type}
import ddbt.lib.ManifestHelper._
import ddbt.lib.store.{Store, Entry}
import lifter.{SCLMSInterop, TypeToTypeRep}

/**
 * Created by khayyam on 4/8/15.
 */

trait StoreDSL extends MStoreComponent with SCLMSInterop with DateComponent with StringComponent with TypeToTypeRep {
  type Manifest[T] = TypeRep[T]
  def m3apply(fn:String,args:List[Rep[_]],tp:Type) = null
  def m3temp[E<:Entry]()(implicit tp:TypeRep[E]):Rep[Store[E]] = null
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = null
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:TypeRep[E]) = null
  def steGet[E<:Entry:TypeRep](x: Rep[E], i: Int) = null
  def stClear      [E<:Entry:TypeRep](x: Rep[Store[E]]) = null
  def stNewEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[Rep[Any]]) = null
  def stNewEntry2[E<:Entry:TypeRep](x: Rep[Store[E]], args:Rep[Any]*):Rep[E] = stNewEntry[E](x, args)
  def storeEntryType(sym:Rep[_]) = ""
  def dtGetTime(x: Rep[Date]): Rep[Long] = dateGetTime(x)
  def stProxyGet[E<:Entry: TypeRep](x: Rep[Store[E]], args:(Int,Rep[Any])*):Rep[E] = steGet(stSampleEntry(x, args),-1)
  def stSampleEntry[E<:Entry:TypeRep](x: Rep[Store[E]], args:Seq[(Int,Rep[Any])]):Rep[E] = null
  // FIXME
  def store2StoreOpsCls[E <: Entry](store: Rep[Store[E]]) = new MStoreRep(store.asInstanceOf[Rep[MStore[E]]])(runtimeType[Int].asInstanceOf[TypeRep[E]])
//  def dtGetYear(x: Rep[Date]): Rep[Long] = dateGetYear(x)
}