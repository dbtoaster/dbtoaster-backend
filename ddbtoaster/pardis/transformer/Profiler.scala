package ddbt.transformer

import java.util.Locale

import ch.epfl.data.sc.pardis.ir.Statement
import ch.epfl.data.sc.pardis.optimization.{RecursiveRuleBasedTransformer, RuleBasedTransformer}
import ch.epfl.data.sc.pardis.types.UnitType
import ddbt.lib.store.deep.{ProfileEnd, ProfileStart, StoreDSL}

/**
  * Created by sachin on 14/3/17.
  */
class Profiler(override val IR: StoreDSL) extends RecursiveRuleBasedTransformer[StoreDSL](IR) {

  import IR._

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

  val alreadyProfiled = collection.mutable.ArrayBuffer[Sym[_]]()

  import ddbt.codegen.Optimizer._

  rewrite += statement {
    case sym -> (node@StoreGetCopy(s: Sym[_], i, key)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Get,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.typeE)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@StoreUpdateCopy(s: Sym[_], _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Update,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@StoreSliceCopy(s: Sym[_], _, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Slice,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@StoreInsert(s: Sym[_], _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Insert,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@StoreUnsafeInsert(s: Sym[_], _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},UnsafeInsert,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@StoreDeleteCopy(s: Sym[_], _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Delete,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@StoreForeachCopy(s: Sym[_], _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"${s.name},Foreach,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(UnitType)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep
    case sym -> (node@GenericEntryApplyObject(i, e)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Constructor,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@SteNewSEntry(i, e)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Constructor,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@SteSampleSEntry(i, e)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Constructor,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@GenericEntryGet(i, e)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Get,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep


    case sym -> (node@GenericEntry$minus$eq(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Update,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@GenericEntryDecrease(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Update,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@GenericEntryIncrease(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Update,à$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@GenericEntry$plus$eq(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Update,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@GenericEntryUpdate(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"Entry,Update,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep

    case sym -> (node@StringExtraStringPrintfObject(_, _, _)) if !alreadyProfiled.contains(sym) =>
      val name = unit(s"String,Printf,$currentBlock,${sym.id}")
      toAtom(ProfileStart(name))(UnitType)
      val rep = toAtom(node)(node.tp)
      alreadyProfiled += rep.asInstanceOf[Sym[_]]
      toAtom(ProfileEnd(name))(UnitType)
      rep


  }
}
