package ddbt.codegen.pardis

import ch.epfl.data.pardis
import pardis.ir._
import pardis.types.PardisTypeImplicits._
import pardis.effects._
import pardis.deep._
import pardis.deep.scalalib._
import pardis.deep.scalalib.collection._
import pardis.deep.scalalib.io._

import ddbt.ast._
import ddbt.lib.store._
import ddbt.lib.store.deep.MStoreComponent


trait PardisExpGen extends MStoreComponent {

  def emit[T:Manifest](sym: => Rep[T]):String
  def emit[T:Manifest](blk:Block[T]):String
  def emitTrigger[T:Manifest](blk:Block[T],name:String,params:String):String
}

object ScalaExpGen extends PardisExpGen {
  def emit[T:Manifest](sym: => Rep[T]):String = null
  def emit[T:Manifest](blk:Block[T]):String = null
  def emitTrigger[T:Manifest](blk:Block[T],name:String,params:String):String = null
}