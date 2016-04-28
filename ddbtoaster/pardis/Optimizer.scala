package ddbt.codegen

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.optimization.{ParameterPromotion, DCE, TransformerHandler}
import ch.epfl.data.sc.pardis.types.{PardisType, UnitType, RecordType}
import ddbt.lib.store.deep.StoreDSL
import ddbt.transformer._

import scala.collection.mutable

/**
  * Created by sachin on 27.04.16.
  */
case class TransactionProgram[T](val initBlock: PardisBlock[T], val global: List[ExpressionSymbol[_]], val codeBlocks: Seq[(String, List[ExpressionSymbol[_]], PardisBlock[T])], val structsDefMap: Map[StructTags.StructTag[SEntry], PardisStructDef[SEntry]]) {}

object Optimizer {
  var analyzeEntry: Boolean = true
  var analyzeIndex: Boolean = true
  var onlineOpts = true
  var m3CompareMultiply = true
}

class Optimizer(val IR: StoreDSL) {
  val pipeline = scala.collection.mutable.ArrayBuffer[TransformerHandler]()
  if (Optimizer.analyzeIndex) {
    pipeline += new IndexAnalysis(IR)
    pipeline += new IndexDecider(IR)
    pipeline += new IndexTransformer(IR)
  } else
    pipeline += new IndexDecider(IR)

  if (Optimizer.analyzeEntry) {
    val ea = new EntryAnalysis(IR)
    val et = new EntryTransformer(IR, ea.EntryTypes)
    pipeline += ea
    pipeline += et
  }
  //    pipeline += TreeDumper(true)
  //    pipeline += PartiallyEvaluate
  pipeline += DCE
  pipeline += ParameterPromotion
  pipeline += new StoreDCE(IR)

  //has to be last
  def optimize[T: PardisType](transactionProgram: TransactionProgram[T]) = pipeline.foldLeft(transactionProgram)(applyOptimization)

  def applyOptimization[T: PardisType](prg: TransactionProgram[T], opt: TransformerHandler) = {
    val init_ = opt(IR)(prg.initBlock)
    val codeB_ = prg.codeBlocks.map(t => (t._1, t._2, opt(IR)(t._3)))
    val (global_, structs_) = opt match {
      case writer: IndexDecider => (writer.changeGlobal(prg.global), prg.structsDefMap)
      case writer: EntryTransformer => (writer.changeGlobal(prg.global), prg.structsDefMap ++ writer.structsDefMap)
      case _ => (prg.global, prg.structsDefMap)
    }
    TransactionProgram(init_, global_, codeB_, structs_)
  }
}