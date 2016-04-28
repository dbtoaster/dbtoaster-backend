
package ddbt.transformer

import java.io.FileWriter

import ch.epfl.data.sc.pardis.ir.Base
import ch.epfl.data.sc.pardis.optimization.TransformerHandler
import ch.epfl.data.sc.pardis.types.PardisType
import ddbt.codegen.prettyprinter.StoreScalaCodeGenerator
import ddbt.lib.store.deep.StoreDSL

/**
 * Factory for creating a transformation phase which does not change the given program, but dumps its representation into a file.
 * The main use case is for debugging the transformation phases in a transformation pipeline.
 */
object TreeDumper {
  /**
   * Creates a tree dumper transformation phase.
   *
   * @param concreteSyntax specifies if the dumped tree should be printed in the concrete syntax form  or in the IR form
   */
  def apply(concreteSyntax: Boolean) = new TransformerHandler {
    def apply[Lang <: Base, T: PardisType](context: Lang)(block: context.Block[T]): context.Block[T] = {
      if (concreteSyntax) {
        val cg = new StoreScalaCodeGenerator(context.asInstanceOf[StoreDSL])
        val pw = new FileWriter("tree_debug_dump.txt", true)
        val doc = cg.blockToDocument(block)
        doc.format(40, pw)
        pw.write("\n-----------------------[END OF BLOCK]------------------------\n")
        pw.flush()
      } else {
        val pw = new FileWriter("tree_debug_dump.txt", true)
        pw.write(block.toString)
        pw.flush()
      }

      block
    }
  }
}
