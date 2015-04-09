package ddbt.codegen.compiler

import ddbt.codegen.prettyprinter.StoreScalaGenerator
import ddbt.lib.store.deep.StoreDSL
import ch.epfl.data.sc.pardis
import pardis.optimization._
import pardis.compiler._


/**
 * Created by khayyam on 4/8/15.
 */

class StoreCompiler(val DSL: StoreDSL) extends Compiler[StoreDSL] {
  pipeline += DCE

  val codeGenerator = new StoreScalaGenerator(DSL)
}
