package sc.tpcc
package compiler
import ch.epfl.data.sc.pardis
import ch.epfl.data.sc.pardis.prettyprinter.{ASTCodeGenerator, ScalaCodeGenerator, CodeGenerator}
import pardis.optimization._
import pardis.compiler._
import pardis.deep.scalalib.ScalaCoreCCodeGen
import ddbt.lib.store.deep.StoreDSL


class TpccCompiler(val DSL: StoreDSL) extends  Compiler[StoreDSL]{
  override val codeGenerator: CodeGenerator = new ScalaCodeGenerator with ASTCodeGenerator[StoreDSL] {
    override val IR: StoreDSL = DSL
  }
}
