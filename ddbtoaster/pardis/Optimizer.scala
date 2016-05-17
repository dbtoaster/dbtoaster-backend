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
  var analyzeEntry: Boolean = true
  var analyzeIndex: Boolean = true
  var onlineOpts = true
  var m3CompareMultiply = true
  var indexInline = true
  var codeMotion = true
  var tmpVarHoist = false
  var refCounter = false
  var indexLookupFusion = true
  var indexLookupPartialFusion = true
  var deadIndexUpdate = true

}

class Optimizer(val IR: StoreDSL) {
  val pipeline = scala.collection.mutable.ArrayBuffer[TransformerHandler]()
  if (Optimizer.analyzeIndex) {
    pipeline += new IndexAnalysis(IR)
    pipeline += new IndexDecider(IR)
    pipeline += new IndexTransformer(IR)
  } else
    pipeline += new IndexDecider(IR)

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
  }

  //    pipeline += PartiallyEvaluate

  if(Optimizer.indexLookupFusion || Optimizer.indexLookupPartialFusion)
    pipeline += new IndexLookupFusion(IR)
      pipeline += TreeDumper(false)
  if (Optimizer.indexInline)
    pipeline += new IndexInliner(IR)
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
      case writer: EntryTransformer => (writer.changeGlobal(prg.global), prg.structsDefs ++ writer.structsDefMap.map(_._2), prg.entryIdxDefs ++ (writer.genOps.map(_._2) ++ writer.genCmp).collect { case IR.Def(e: EntryIdxApplyObject[_]) => e })
      case _ => (prg.global, prg.structsDefs, prg.entryIdxDefs)
    }
    val vars_ = opt match {
      case writer: SampleEntryHoister => writer.tmpVars.toSeq
      case _ => prg.tempVars
    }
    TransactionProgram(init_, global_, codeB_, structs_, entryidx_, vars_)
  }
}