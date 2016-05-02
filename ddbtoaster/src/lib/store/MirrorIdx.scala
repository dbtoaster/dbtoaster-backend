package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{deep, read, reflect}

/**
  * Created by sachin on 02.05.16.
  */
@deep
@reflect[Idx[_]]
trait MirrorIdx[E <: Entry] {
  def unsafeInsert(e: E): Unit = ???
  def insert(e: E): Unit = ???
  def delete(e: E): Unit = ???
  def update(e: E): Unit = ???
  @read
  def get(key: E): E = ???
  def foreach(f: (E) => Unit): Unit = ???
  def slice(key: E, f: (E) => Unit): Unit = ???
}
