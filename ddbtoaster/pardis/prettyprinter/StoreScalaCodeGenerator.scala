package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.utils.document.Document
import ch.epfl.data.sc.pardis.ir._
import ddbt.lib.store.deep.MStoreIRs._
import ddbt.lib.store.deep.StoreDSL


class StoreScalaCodeGenerator(val IR: StoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[StoreDSL]{
  override def symToDocument(sym: ExpressionSymbol[_]): Document = {
    if(sym.name != "x") {
      Document.text(sym.name)
    } else {
      super.symToDocument(sym)
    }
  }

  override def stmtToDocument(stmt: Statement[_]): Document = stmt match {
  	case Statement(sym, MStoreNew2()) => generateNewStore(sym, None)
  	case _ => super.stmtToDocument(stmt)
  }

  def generateNewStore(c: Sym[_], mname:Option[String]):String = {
  	def generateNew: String = "new Store[GenericEntry](1,Array[EntryIdx[GenericEntry]](GenericEntry))"
  	val symbolName = c.name + c.id
  	val mapAlias = mname match {
  	  case Some(mapName) => 
  	  	s"val $mapName = $symbolName"
	  case None => 
	  	s""
  	}
  	s"""val $symbolName = $generateNew
$symbolName.index(0,IHash,true)
$mapAlias"""
  }
}
