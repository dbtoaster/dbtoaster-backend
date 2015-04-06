package ddbt.codegen.pardis

import ddbt.lib.store.deep.MStoreComponent
import ch.epfl.data.pardis.prettyprinter.{CodeGenerator, ScalaCodeGenerator, ASTCodeGenerator}

trait PardisExpGen extends M3OpsExp {
  trait MyGenericCodegen extends CodeGenerator {
    val IR: self.type = self
    def storeEntryType(sym:Rep[_]):String
  }
  def emit[T:Manifest](sym: => Rep[T]):String
  def emit[T:Manifest](blk:Block[T]):String
  def emitTrigger[T:Manifest](blk:Block[T],name:String,params:String):String
}

object ScalaExpGen extends PardisExpGen {
  class MyCodeGen extends ScalaCodeGenerator with MyGenericCodegen {
    def emitSource[T:Manifest](sym: => Rep[T]) : String = emitSource(reifyBlock(sym))
    def emitSource[T:Manifest](body: Block[T]) : String = {
      null
    }

    def storeEntryType(sym:Rep[_]):String = {
      null
    }

  }
  val codegen = new MyCodeGen

  def emit[T:Manifest](sym: => Rep[T]):String = null
  def emit[T:Manifest](blk:Block[T]):String = null
  def emitTrigger[T:Manifest](blk:Block[T],name:String,params:String):String = null
}