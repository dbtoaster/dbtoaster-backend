package ddbt.codegen.prettyprinter

import ddbt.lib.store.deep.MirrorStoreDSL
import ch.epfl.data.pardis.prettyprinter._
import ch.epfl.data.pardis.utils.Document


/**
 * Created by khayyam on 4/8/15.
 */
class MirrorStoreScalaGenerator(val IR: MirrorStoreDSL) extends ScalaCodeGenerator with ASTCodeGenerator[MirrorStoreDSL] {

  override def getHeader: Document = s"""package ch.epfl.data
package vector

import ch.epfl.data.vector.shallow._

"""

  override def getTraitSignature(): Document = s"""object GeneratedVectorApp {
  def main(args: Array[String]): Unit = """
}
