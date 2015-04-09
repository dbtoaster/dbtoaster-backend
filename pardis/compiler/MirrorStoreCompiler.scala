package ddbt.codegen.compiler

import ddbt.codegen.prettyprinter.MirrorStoreScalaGenerator
import ddbt.lib.store.deep.MirrorStoreDSL
import ch.epfl.data.pardis
import pardis.optimization._
import pardis.compiler._


/**
 * Created by khayyam on 4/8/15.
 */

class MirrorStoreCompiler(val DSL: MirrorStoreDSL) extends Compiler[MirrorStoreDSL] {
  pipeline += DCE

  val codeGenerator = new MirrorStoreScalaGenerator(DSL)
}
