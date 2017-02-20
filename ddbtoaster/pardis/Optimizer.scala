package ddbt.codegen

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.optimization._
import ch.epfl.data.sc.pardis.types.PardisType
import ddbt.lib.store.deep.EntryIdxIRs.EntryIdxApplyObject
import ddbt.lib.store.deep.StoreDSL
import ddbt.transformer._

import scala.collection.mutable

/**
  * Created by sachin on 27.04.16.
  */
case class TransactionProgram[T](val initBlock: PardisBlock[T], val globalVars: List[ExpressionSymbol[Any]], val codeBlocks: Seq[(String, List[ExpressionSymbol[_]], PardisBlock[T])], val structs: List[PardisStructDef[Any]], val entryIdxDefs: Seq[PardisNode[_]], val tempVars: Seq[(ExpressionSymbol[_], PardisStruct[_])] = Nil, val tmpMaps: Seq[(ExpressionSymbol[_], collection.mutable.ArrayBuffer[ExpressionSymbol[_]])] = Nil) extends PardisProgram {
  override val main: PardisBlock[Any] = initBlock.asInstanceOf[PardisBlock[Any]]
}

object Optimizer {
  var analyzeEntry: Boolean = false
  var analyzeIndex: Boolean = false
  var fixedRange: Boolean = false
  var onlineOpts = false
  var tmpVarHoist = false
  var tmpMapHoist = false
  var indexInline = false
  var indexLookupFusion = false
  var indexLookupPartialFusion = false
  var sliceInline = false
  var deadIndexUpdate = false
  var codeMotion = false
  var m3CompareMultiply = false
  var regexHoister = false
  var multiResSplitter = false

  var refCounter = true
  var cTransformer = false
  var initialStoreSize = false
  var infoFileName = ""
  var optCombination: String = ""
}

class Optimizer(val IR: StoreDSL) {
  val pipeline = scala.collection.mutable.ArrayBuffer[TransformerHandler]()

  import Optimizer._

  optCombination = List(analyzeEntry -> "E", analyzeIndex -> "I", fixedRange -> "G", onlineOpts -> "O",
    tmpVarHoist -> "V", tmpMapHoist -> "M", indexInline -> "N", indexLookupFusion -> "F",
    indexLookupPartialFusion -> "P", sliceInline -> "S", deadIndexUpdate -> "D", codeMotion -> "C",
    m3CompareMultiply -> "T", regexHoister -> "X", refCounter -> "R", multiResSplitter -> "U", initialStoreSize -> "Z").filter(_._1).sortWith(_._2 < _._2).foldLeft("")((a, c) => a + c._2)

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
  if (!Optimizer.indexLookupFusion && !Optimizer.analyzeIndex && Optimizer.analyzeEntry)
    throw new Error("Entry analysis requires either indexlookup or index analysis")
  if (Optimizer.indexLookupFusion || Optimizer.indexLookupPartialFusion)
    pipeline += new IndexLookupFusion(IR)

  if (Optimizer.indexInline)
    pipeline += new IndexInliner(IR)

  if(Optimizer.multiResSplitter && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("MultiRes Splitter requires Index Inline, IndexLookupFusion")

  if(Optimizer.multiResSplitter)
    pipeline += new MultiResSplitter(IR)

  if (Optimizer.tmpMapHoist)
    pipeline += new TmpMapHoister(IR)

  if (Optimizer.deadIndexUpdate && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("DeadIndexUpdate opt requires both index inline as well as indexlookup fusion")

  if (Optimizer.sliceInline && !(Optimizer.indexInline && Optimizer.indexLookupFusion && Optimizer.tmpVarHoist)) //hash and cmp not implemented for pointer
    throw new Error("Inlining slice requires Index Inline, IndexLookupFusion and TempVarHoisting implemented only for c++")

  pipeline += DCE
  pipeline += ParameterPromotion

  pipeline += new StoreDCE(IR)

//  pipeline += new CommonPureExpression(IR)
  pipeline += new InsertNoChecks(IR)
  if (Optimizer.cTransformer) {
    pipeline += new ScalaConstructsToCTranformer(IR, false)
    pipeline += new ScalaStructToMallocTransformer(IR)
    pipeline += new StringToCTransformer(IR)
  }
//    pipeline += TreeDumper(false)
  if (Optimizer.refCounter)
    pipeline += new CountingAnalysis[StoreDSL](IR) with TransformerHandler {
      override def apply[Lang <: Base, T](context: Lang)(block: context.Block[T])(implicit evidence$1: PardisType[T]): context.Block[T] = {
        traverseBlock(block.asInstanceOf[IR.Block[T]])
        block
      }
    }


  def optimize[T: PardisType](transactionProgram: TransactionProgram[T]) = pipeline.foldLeft(transactionProgram)(applyOptimization)

  def applyOptimization[T: PardisType](prg: TransactionProgram[T], opt: TransformerHandler) = {
    opt match {
      case tmh: TmpMapHoister => tmh.globalMaps = prg.globalVars
      case _ => ()
    }
    val init_ = opt(IR)(prg.initBlock)
    val codeB_ = prg.codeBlocks.map(t => (t._1, t._2, opt(IR)(t._3)))
    val (global_, structs_, entryidx_) = opt match {
      case writer: IndexDecider => (writer.changeGlobal(prg.globalVars), prg.structs, if (Optimizer.cTransformer) (writer.genOps.values ++ writer.genCmp.values ++ writer.genFixed.values).toSeq.map(IR.Def.unapply(_).get) else prg.entryIdxDefs)
      case writer: EntryTransformer => (writer.changeGlobal(prg.globalVars), prg.structs ++ writer.structsDefMap.map(_._2), (writer.genOps.map(_._2) ++ writer.genCmp.map(_._2) ++ writer.genFixRngOps.map(_._2)).toSeq.collect { case IR.Def(e: EntryIdxApplyObject[_]) => e })
      case reader: CountingAnalysis[StoreDSL] =>
        prg.entryIdxDefs.collect {
          case EntryIdxApplyObject(IR.Def(hl@PardisLambda(_, _, h)), IR.Def(cl@PardisLambda2(_, _, _, c)), _) => reader(IR)(h)(hl.typeS); reader(IR)(c)(cl.typeS)
        }
        (prg.globalVars, prg.structs, prg.entryIdxDefs)
      case _ => (prg.globalVars, prg.structs, prg.entryIdxDefs)
    }
    val vars_ = opt match {
      case writer: SampleEntryHoister => writer.tmpVars.toSeq
      case _ => prg.tempVars
    }
    val tmpMaps_ = opt match {
      case tmh: TmpMapHoister => tmh.tmpMaps.toSeq
      case _ => prg.tmpMaps
    }
    TransactionProgram(init_, global_, codeB_, structs_, entryidx_, vars_, tmpMaps_)
  }
}