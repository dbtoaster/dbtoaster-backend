package ddbt.transformer


import ch.epfl.data.sc.pardis.ir.{PardisStructArg, PardisStruct}
import ch.epfl.data.sc.pardis.optimization.Rule.Statement
import ch.epfl.data.sc.pardis.optimization.RuleBasedTransformer
import ddbt.lib.store.deep.StoreDSL

/**
  * Created by sachin on 02.05.16.
  */
class SampleEntryHoister(override val IR: StoreDSL) extends RuleBasedTransformer[StoreDSL](IR) {

  import IR._

  val tmpVars = collection.mutable.HashMap[Sym[_], PardisStruct[_]]()


  analysis += statement {
    case sym -> (ent@PardisStruct(tag, elems, methods)) => {
      val elems_ = elems.map(arg => PardisStructArg(arg.name, arg.mutable, nullValue(arg.init.tp)))
      tmpVars += sym -> PardisStruct(tag, elems_, methods)(ent.tp)
      ()
    }
  }
  rewrite += statement {
    case sym -> (ent@PardisStruct(tag, elems, methods)) if tmpVars.contains(sym) => {
      val entry = sym.asInstanceOf[Rep[SEntry]]
      elems.foreach(arg => {
        implicit val tp = arg.init.tp
        if (arg.init != nullValue(tp))
          fieldSetter(entry, arg.name, arg.init)
      })
      sym
    }
  }

}
