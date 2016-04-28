package ddbt.codegen.prettyprinter

import ch.epfl.data.sc.pardis.prettyprinter.CCodeGenerator
import ch.epfl.data.sc.pardis.utils.document.Document
import ddbt.lib.store.deep.StoreDSL


/**
  * Created by sachin on 28.04.16.
  */
class StoreCppCodeGenerator(override val IR: StoreDSL)  extends CCodeGenerator with StoreCodeGenerator {

}
