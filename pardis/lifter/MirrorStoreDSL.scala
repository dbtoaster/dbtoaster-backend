package ddbt.lib.store.deep

import ddbt.ast.{TypeDouble, TypeLong, Type}
import ddbt.lib.ManifestHelper._
import ddbt.lib.store.{Store, Entry}

/**
 * Created by khayyam on 4/8/15.
 */

trait MirrorStoreDSL extends MStoreComponent {
  def m3apply(fn:String,args:List[Rep[_]],tp:Type) = null
  def m3temp[E<:Entry]()(implicit tp:Manifest[E]):Rep[Store[E]] = null
  def m3add[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = null
  def m3set[E<:Entry](map:Rep[Store[E]], ent:Rep[E])(implicit m:Manifest[E]) = null
  def steGet[E<:Entry:Manifest](x: Rep[E], i: Int) = null
  def stClear      [E<:Entry:Manifest](x: Rep[Store[E]]) = null
  def stNewEntry[E<:Entry:Manifest](x: Rep[Store[E]], args:Seq[Rep[Any]]) = null
  def stNewEntry2[E<:Entry:Manifest](x: Rep[Store[E]], args:Rep[Any]*):Rep[E] = stNewEntry[E](x, args)
  def storeEntryType(sym:Rep[_]) = ""
}