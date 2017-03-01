package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{deep, needs, read, reflect}

/**
  * Created by sachin on 02.05.16.
  */
@deep
@reflect[Idx[_]]
@needs[MultiRes]
trait MirrorIdx[E <: Entry] {
  def unsafeInsert(e: E): Unit = ???
  def insert(e: E): Unit = ???
  def delete(e: E): Unit = ???
  def deleteCopy(e: E, primary: Idx[E]): Unit = ???
  def deleteCopyDependent(e: E): Unit = ???
  def update(e: E): Unit = ???
  def updateCopyDependent(e: E, ref: E): Unit = ???
  def updateCopy(e: E, primary: Idx[E]): Unit = ???
  @read
  def get(key: E): E = ???
  @read
  def getCopy(key: E): E = ???
  @read
  def getCopyDependent(key: E): E = ???
  def foreach(f: (E) => Unit): Unit = ???
  def foreachRes(): MultiRes = ???
  def foreachResMap(f: (E) => Unit, res: MultiRes): Unit = ???
  def sliceNoUpdate(key: E, f: E => Unit) : Unit = ???
  def slice(key: E, f: (E) => Unit): Unit = ???
  def sliceRes(key: E): MultiRes = ???
  def sliceResMap(key: E, f: (E) => Unit, res: MultiRes): Unit = ???
  def sliceResMapNoUpd(key: E, f: E => Unit, res:MultiRes): Unit = ???
  def sliceCopy(key: E, f: (E) => Unit): Unit = ???
  def sliceCopyDependent(key: E, f: (E) => Unit): Unit = ???
  def clear(): Unit = ???
}
