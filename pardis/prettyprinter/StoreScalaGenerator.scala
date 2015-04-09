package ddbt.codegen.prettyprinter

import ddbt.lib.store.deep.StoreDSL
import ch.epfl.data.sc.pardis.prettyprinter._
import ch.epfl.data.sc.pardis.utils.Document


/**
 * Created by khayyam on 4/8/15.
 */
class StoreScalaGenerator(val IR: StoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[StoreDSL] {

  override def getHeader: Document = s"""package ch.epfl.data
package vector

import ch.epfl.data.vector.shallow._

"""

  override def getTraitSignature(): Document = s"""object GeneratedVectorApp {
  def main(args: Array[String]): Unit = """
}
