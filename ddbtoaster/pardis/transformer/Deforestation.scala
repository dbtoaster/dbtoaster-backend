package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.{Constant, PardisLambda, Statement}
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.types.Lambda1Type
import ddbt.codegen.Optimizer
import ddbt.lib.store.deep.{StoreDSL, StructFieldDecr, StructFieldIncr}

/**
  * Created by sachin on 02.05.16.
  */
class Deforestation(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR.{EntryType => _, _}

  def super_optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val analyseProgram = classOf[RuleBasedTransformer[StoreDSL]].getDeclaredMethod("analyseProgram", classOf[Block[T]], classOf[TypeRep[T]])
    analyseProgram.setAccessible(true)
    val isDone = classOf[RecursiveRuleBasedTransformer[StoreDSL]].getDeclaredField("isDone")
    isDone.setAccessible(true)
    var currentBlock = node
    var counter = 0
    while (isDone.get(this) == false && counter < THRESHOLD) {
      analyseProgram.invoke(this, currentBlock, implicitly[TypeRep[T]])
      postAnalyseProgram(currentBlock)
      isDone.set(this, true)
      currentBlock = transformProgram(currentBlock)
      counter += 1
    }
    if (counter >= THRESHOLD) {
      System.err.println(s"Recursive transformer ${getName} is not converted yet after [${scala.Console.RED}$counter${scala.Console.RESET}] rounds")
    }
    currentBlock
  }

  override def optimize[T: TypeRep](node: Block[T]): Block[T] = {
    val res = super_optimize(node)
    ruleApplied()
    res
  }

  val StoreMaps = collection.mutable.HashMap[Sym[_], collection.immutable.Map[Int, Rep[_]]]()
//  analysis += rule {
//    case StoreMap(self: Sym[_], Def(PardisLambda(_, _, o))) =>
//      o.res match {
//        case Def(GenericEntryApplyObject(Constant("SteNewSEntry"), Def(LiftedSeq(args: Seq[Rep[_]])))) =>
//          val t1 = (1 to args.size) zip args
//          val t2 = t1.toMap
//          StoreMaps += (self -> t1.toMap)
//        case _ => ()
//      }
//      ()
//  }
  rewrite += rule {
    //    case sf@StoreFilter(sm, f) =>
    //      System.err.println(s"StoreFilter containing $sm")
    //      sf
    case StoreFilter(Def(sm@StoreMap(self: Sym[_], mapfn)), filterfn) =>
      implicit val Etp = GenericEntryType.asInstanceOf[TypeRep[Entry]]
    val sf = StoreFilter(self, __lambda{e: Rep[Entry] => {__app[Entry, Boolean](filterfn).apply(__app[Entry, Entry](mapfn).apply(e))}})
      StoreMap(sf, mapfn)

    case StoreMap(Def(StoreMap(self: Sym[_], inner: Rep[Entry => Entry])), outer: Rep[Entry => Entry]) =>
      implicit val Etp = GenericEntryType.asInstanceOf[TypeRep[Entry]]
      StoreMap(self, __lambda{ x: Rep[Entry] => {__app[Entry, Entry](outer).apply(__app[Entry, Entry](inner).apply(x))}})
  }
}