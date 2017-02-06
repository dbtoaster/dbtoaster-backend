package ddbt.lib.store

import scala.reflect._

import ch.epfl.data.sc.pardis.annotations._

@needs[Array[_] :: EntryIdx[_] :: Idx[_]]
@deep
@reflect[Store[_]]
class MStore[E <: Entry](val idxs: Array[Idx[E]], val ops: Array[EntryIdx[E]]) {
  def this()(implicit cE: Manifest[E]) = this(new Array[Idx[E]](0), new Array[EntryIdx[E]](0))

  def this(n: Int, ops: Array[EntryIdx[E]])(implicit cE: Manifest[E]) = this(new Array[Idx[E]](0), ops)

  private val n = idxs.length

  // def this(n:Int) = this(new Array[Idx[E]](n),null)(cE)
  // def this(n:Int,ops:Array[EntryIdx[E]]) = this(new Array[Idx[E]](n),ops)(cE)
  def unsafeInsert(e: E): Unit = ???

  def insert(e: E): Unit = ???

  def update(e: E): Unit = ???

  def updateCopy(e: E): Unit = ???

  def updateCopyDependent(e: E): Unit = ???

  def delete(e: E): Unit = ???

  def deleteCopy(e: E): Unit = ???

  def deleteCopyDependent(e: E): Unit = ???

  @read
  def get(idx: Int, key: E): E = ???

  @read
  def getCopy(idx: Int, key: E): E = ???

  @read
  def getCopyDependent(idx: Int, key: E): E = ???

  def foreach(f: E => Unit): Unit = ???

  def slice(idx: Int, key: E, f: E => Unit): Unit = ???

  def sliceCopy(idx: Int, key: E, f: E => Unit): Unit = ???

  def sliceCopyDependent(idx: Int, key: E, f: E => Unit): Unit = ???

  def range(idx: Int, min: E, max: E, withMin: Boolean, withMax: Boolean, f: E => Unit): Unit = ???

  def delete(idx: Int, key: E): Unit = ???

  def clear: Unit = ???

  def index(idx: Int, idxType: String, uniq: Boolean, otherIdx: Int): Idx[E] = ???

  def copyIntoPool(e: E): E = ???
}