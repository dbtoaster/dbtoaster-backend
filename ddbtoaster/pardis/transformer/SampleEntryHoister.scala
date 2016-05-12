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

  def isSampleRecord(elems: Seq[PardisStructArg]) = elems.foldLeft(false)((res, arg) => {
    val tp = arg.init.tp
    res || (arg.init == nullValue(tp))
  })

  analysis += statement {
    case sym -> (ent@PardisStruct(tag, elems, methods)) if isSampleRecord(elems) => {
      val elems_ = elems.map(arg => PardisStructArg(arg.name, arg.mutable, nullValue(arg.init.tp)))
      tmpVars += sym -> PardisStruct(tag, elems_, methods)(ent.tp)
      ()
    }
    case sym -> (StoreInsert(_, entry:Sym[_])) => tmpVars.remove(entry);()
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
