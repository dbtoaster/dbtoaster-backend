package ddbt.codegen

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.optimization.{CountingAnalysis, ParameterPromotion, DCE, TransformerHandler}
import ch.epfl.data.sc.pardis.types.{PardisType, UnitType, RecordType}
import ddbt.lib.store.deep.EntryIdxIRs.EntryIdxApplyObject
import ddbt.lib.store.deep.StoreDSL
import ddbt.transformer._

import scala.collection.mutable

/**
  * Created by sachin on 27.04.16.
  */
case class TransactionProgram[T](val initBlock: PardisBlock[T], val global: List[ExpressionSymbol[_]], val codeBlocks: Seq[(String, List[ExpressionSymbol[_]], PardisBlock[T])], val structsDefs: Seq[PardisStructDef[SEntry]], val entryIdxDefs: Seq[EntryIdxApplyObject[SEntry]], val tempVars: Seq[(ExpressionSymbol[_], PardisStruct[_])] = Nil) {}

object Optimizer {
  var analyzeEntry: Boolean = false
  var analyzeIndex: Boolean = false
  var fixedRange: Boolean = false
  var onlineOpts = false
  var tmpVarHoist = false
  var indexInline = false
  var indexLookupFusion = false
  var indexLookupPartialFusion = false
  var deadIndexUpdate = false
  var codeMotion = false
  var refCounter = false
  var m3CompareMultiply = false //Lazy evaluation
}

class Optimizer(val IR: StoreDSL) {
  val pipeline = scala.collection.mutable.ArrayBuffer[TransformerHandler]()
  if (Optimizer.analyzeIndex) {
    pipeline += new IndexAnalysis(IR)
    pipeline += new IndexDecider(IR)
    pipeline += new IndexTransformer(IR)
  } else {
    pipeline += new IndexDecider(IR)
    if (Optimizer.fixedRange)
      throw new Error("Fixed range optimization cannot be enabled without Index analysis")
  }

  if (Optimizer.codeMotion) {
    pipeline += DCE
    pipeline += new CodeMotion(IR)
  }
  if (Optimizer.analyzeEntry) {
    val ea = new EntryAnalysis(IR)
    val et = new EntryTransformer(IR, ea.EntryTypes)
    pipeline += ea
    pipeline += et
    if (Optimizer.tmpVarHoist)
      pipeline += new SampleEntryHoister(IR)
  } else if (Optimizer.tmpVarHoist) {
    throw new Error("Tmp Var Hoisting cannot be enabled without Entry analysis")
  }


  //    pipeline += PartiallyEvaluate
  if(!Optimizer.indexLookupFusion && !Optimizer.analyzeIndex && Optimizer.analyzeEntry)
    throw new Error("Entry analysis requires either indexlookup or index analysis")
  if (Optimizer.indexLookupFusion || Optimizer.indexLookupPartialFusion)
    pipeline += new IndexLookupFusion(IR)
  //      pipeline += TreeDumper(false)
  if (Optimizer.indexInline)
    pipeline += new IndexInliner(IR)
  if (Optimizer.deadIndexUpdate && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("DeadIndexUpdate opt requires both index inline as well as indexlookup fusion")
  pipeline += DCE
  pipeline += ParameterPromotion
  if (Optimizer.refCounter)
    pipeline += new CountingAnalysis[StoreDSL](IR) with TransformerHandler {
      override def apply[Lang <: Base, T](context: Lang)(block: context.Block[T])(implicit evidence$1: PardisType[T]): context.Block[T] = {
        traverseBlock(block.asInstanceOf[IR.Block[T]])
        block
      }
    }
  pipeline += new StoreDCE(IR)

  //has to be last
  def optimize[T: PardisType](transactionProgram: TransactionProgram[T]) = pipeline.foldLeft(transactionProgram)(applyOptimization)

  def applyOptimization[T: PardisType](prg: TransactionProgram[T], opt: TransformerHandler) = {
    val init_ = opt(IR)(prg.initBlock)
    val codeB_ = prg.codeBlocks.map(t => (t._1, t._2, opt(IR)(t._3)))
    val (global_, structs_, entryidx_) = opt match {
      case writer: IndexDecider => (writer.changeGlobal(prg.global), prg.structsDefs, prg.entryIdxDefs)
      case writer: EntryTransformer => (writer.changeGlobal(prg.global), prg.structsDefs ++ writer.structsDefMap.map(_._2), prg.entryIdxDefs ++ (writer.genOps.map(_._2) ++ writer.genCmp ++ writer.genFixRngOps).collect { case IR.Def(e: EntryIdxApplyObject[_]) => e })
      case _ => (prg.global, prg.structsDefs, prg.entryIdxDefs)
    }
    val vars_ = opt match {
      case writer: SampleEntryHoister => writer.tmpVars.toSeq
      case _ => prg.tempVars
    }
    TransactionProgram(init_, global_, codeB_, structs_, entryidx_, vars_)
  }
}