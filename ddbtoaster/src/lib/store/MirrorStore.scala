package ddbt.lib.store
import scala.reflect._

import ch.epfl.data.sc.pardis.annotations._

@needs[Array[_]]
@deep
//@reflect[Store[_]]
class MStore[E<:Entry](val idxs:Array[E], val ops:Array[E]) {
  def this()(implicit cE:Manifest[E]) = this(new Array[E](0), new Array[E](0))
  private val n = idxs.length
  // def this(n:Int) = this(new Array[Idx[E]](n),null)(cE)
  // def this(n:Int,ops:Array[EntryIdx[E]]) = this(new Array[Idx[E]](n),ops)(cE)
  def unsafeInsert(idx:Int,e:E):Unit = ???
  def insert(e:E):Unit = ???
  def update(e:E):Unit = ???
  def delete(e:E):Unit = ???
  def get(idx:Int,key:E):E = ???
  def foreach(f:E=>Unit):Unit = ???
  def slice(idx:Int,key:E,f:E=>Unit): Unit = ???
  def getSliceMin(idx:Int,key:E,col:Int):E = ???
  def getSliceMax(idx:Int,key:E,col:Int):E = ???

  def range(idx:Int,min:E,max:E,withMin:Boolean,withMax:Boolean,f:E=>Unit): Unit = ???
  def delete(idx:Int,key:E):Unit = ???
  def clear:Unit = ???
}