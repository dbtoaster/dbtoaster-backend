package ddbt.transformer

import ch.epfl.data.sc.pardis.ir.Constant
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ddbt.lib.store.deep.{StoreDSL, StructFieldDecr, StructFieldIncr}

import scala.collection.mutable

/**
  * Created by sachin on 6/6/17.
  */
class DeadIdxUpdate(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

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
  val updatedCols = collection.mutable.HashMap[Rep[_], collection.mutable.HashSet[Int]]()
  analysis += rule {
    case GenericEntryUpdate(e, Constant(i), _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += i; ()
    case GenericEntryIncrease(e, Constant(i), _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += i; ()
    case GenericEntryDecrease(e, Constant(i), _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += i; ()
    case GenericEntry$minus$eq(e, Constant(i), _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += i; ()
    case GenericEntry$plus$eq(e, Constant(i), _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += i; ()
    //Ignore isSE field, if present
    case StructFieldSetter(e, idx, _) if idx.startsWith("_") => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
    case StructFieldIncr(e, idx, _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
    case StructFieldDecr(e, idx, _) => updatedCols.getOrElseUpdate(e, new mutable.HashSet[Int]()) += idx.drop(1).toInt; ()
  }
  rewrite += remove {
    case IdxUpdate(Def(StoreIndex(store, Constant(idx), _, _, _)), e) if {
      val idxes = store.asInstanceOf[Sym[_]].attributes.get(IndexesFlag).get.indexes
      //SBJ: TODO: add checks for columns of min/max index too. What if idx0 is not primary
      idx == 0 || updatedCols(e).intersect(idxes(idx).cols.toSet).isEmpty
    } => ()
  }

}
