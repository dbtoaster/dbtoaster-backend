package ddbt.lib.store

import ch.epfl.data.sc.pardis.annotations.{needs, reflect, deep, ::}

/**
  * Created by sachin on 15.04.16.
  */
@deep
@needs[GenericEntry]
@reflect[EntryIdx[_]]
abstract class MirrorEntryIdx[E <: Entry] {
  def cmp(e1: E, e2: E): Int
  def hash(e: E): Int
}

object MirrorEntryIdx {
  def apply[E<:Entry](h: (E => Int), c: ((E, E) => Int)): EntryIdx[E] = ???
  def genericOps(cols: Seq[Int]): EntryIdx[GenericEntry] = ???
  def genericCmp[R](cols: Seq[Int], f: GenericEntry => R): EntryIdx[GenericEntry] = ???
}


//
//@deep
//case class MirrorGenericCmp[R](val f: MirrorGenericEntry => R)(implicit order: Ordering[R]) extends MirrorEntryIdx[MirrorGenericEntry] {
//  def hash(e: MirrorGenericEntry): Int = ???
//  def cmp(e1: MirrorGenericEntry, e2: MirrorGenericEntry): Int = ???
//}