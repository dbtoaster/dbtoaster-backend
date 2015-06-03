package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.utils.document.Document
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store.deep.MStoreIRs._


class StoreScalaCodeGenerator extends ScalaCodeGenerator {
  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if(sym.name != "x") {
      Document.text(sym.name)
    } else {
      super.symToDocument(sym)
    }
  }

  override def functionNodeToDocument(fun: FunctionNode[_]) = fun match {
    case MStoreNew2() => "new Store[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))"
    case _                                         => super.functionNodeToDocument(fun)
  }
}
