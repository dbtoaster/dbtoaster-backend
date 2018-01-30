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
  var analyzeEntry = false
  var secondaryIndex = false
  var splSecondaryIdx = false
  var minMaxIdx = false
  var medIdx = false
  var fixedRange = false
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
  var sliceNoUpd = false
  var coldMotion = false
  var parameterPromotion = true
  var mvget = false
  var concCPP = false
  var profileBlocks = false
  var profileStoreOperations = false

  var refCounter = true
  var cTransformer = false
  var initialStoreSize = false
  var infoFileName = ""
  var optCombination = ""

  var currentBlock = ""
}

class Optimizer(val IR: StoreDSL) {
  val pipeline = scala.collection.mutable.ArrayBuffer[TransformerHandler]()

  import Optimizer._

  optCombination = List(analyzeEntry -> "E", secondaryIndex -> "I", fixedRange -> "G", onlineOpts -> "O",
    tmpVarHoist -> "V", tmpMapHoist -> "M", indexInline -> "N", indexLookupFusion -> "F",
    indexLookupPartialFusion -> "P", sliceInline -> "S", deadIndexUpdate -> "D", codeMotion -> "C",
    m3CompareMultiply -> "T", regexHoister -> "X", refCounter -> "R", multiResSplitter -> "U", initialStoreSize -> "Z", sliceNoUpd -> "L", splSecondaryIdx -> "Y", minMaxIdx -> "A", medIdx -> "B", coldMotion -> "Q").filter(_._1).sortWith(_._2 < _._2).foldLeft("")((a, c) => a + c._2)

  //pipeline += new DSKReordering(IR)
  //pipeline += new Deforestation(IR)
  //pipeline += DCE

  if (Optimizer.secondaryIndex) {
    pipeline += new IndexAnalysis(IR)
    pipeline += new IndexDecider(IR)
    pipeline += new IndexTransformer(IR)
  } else {
    pipeline += new IndexDecider(IR)
    if (Optimizer.fixedRange)
      throw new Error("Fixed range optimization cannot be enabled without Index analysis")
    /*
      We are not interested in such a case, and therefore, slice etc has not been implented on ArrayIndex
     */
  }

  if (Optimizer.profileStoreOperations)
    pipeline += new Profiler(IR)

  if(Optimizer.regexHoister){
    pipeline += new StringFormatEvaluator(IR)
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
    //TmpVar hoisting will do nothing without EntryAnalysis, as the cases for GenericEntries are not defined.
  }



  //    pipeline += PartiallyEvaluate
  if (Optimizer.indexLookupFusion || Optimizer.indexLookupPartialFusion)
    pipeline += new IndexLookupFusion(IR)

  if (Optimizer.indexInline)
    pipeline += new IndexInliner(IR)

  if(Optimizer.mvget && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("MV-get requires idxInline and lookupfusion")

  if(Optimizer.mvget) {
    pipeline += new MVGet(IR)
    pipeline += new SliceToSliceNoUpd(IR)
  }

  if(Optimizer.deadIndexUpdate)
    pipeline += new DeadIdxUpdate(IR)

  if (Optimizer.multiResSplitter && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("MultiRes Splitter requires Index Inline, IndexLookupFusion")
  /* MultiRes covers cases of only IdxSlice and IdxForEach.
     Theoretically, this can be done at StoreLevel as well as for SliceCopy functions. However, doing so increases the
    number of possible nodes to increase thereby increasing the number of scenarios that sliceInline needs to handle
    */

    if (Optimizer.sliceNoUpd && !(Optimizer.deadIndexUpdate) && !Optimizer.mvget)
      throw new Error("SliceNoUpdate requires deadIndexUpdate")
  /*
      SliceNoUpdate covers the case of only IdxSlice.
      Even though this optimization can be performed without the deadIndexUpdate, for the best case, it should be after
      doing deadIdxupdate which removes all updates (atleast in current benchmarks)
      To do this optimization without LookupFusion, there should be "noUpd" nodes for sliceCopy and sliceCopyDependent
      To do it without IdxInline, there should be "noUpd" versions for StoreSlice
   */

  if (Optimizer.sliceNoUpd && !Optimizer.mvget)
    pipeline += new SliceToSliceNoUpd(IR)

  if (Optimizer.multiResSplitter)
    pipeline += new MultiResSplitter(IR)

  if (Optimizer.coldMotion && !Optimizer.multiResSplitter)
    throw new Error("ColdMotion requires MultiResSplitter")
  //MultiResSplitter is required for ColdMotion to move computation to necessary place

  if (Optimizer.coldMotion) {
    pipeline += new ColdMotion(IR)
  }
  if (Optimizer.tmpMapHoist)
    pipeline += new TmpMapHoister(IR)

  if (Optimizer.deadIndexUpdate && !(Optimizer.indexInline && Optimizer.indexLookupFusion))
    throw new Error("DeadIndexUpdate opt requires both index inline as well as indexlookup fusion")
  /*
    This optimization makes no sense without IdxInline, as without it, it can only be done at runtime by the store.
    This optimization requires lookupfusion because, in the current model of updateCopy, the original element is removed,
    and the new element is inserted. Thus, if one index updates, all of them should also update. However, this is not the case if
     the memory location of the original element is overwritten using the values of the new element. Primary index has to update always,
    as there could be changes in value field, but updates to other indexes could possibly be avoided.
    SBJ: What are the issues with the latter approach?
   */

  if (Optimizer.sliceInline && !(Optimizer.indexInline && Optimizer.indexLookupFusion && Optimizer.tmpVarHoist && Optimizer.secondaryIndex))
    throw new Error("Inlining slice requires Index Inline, IndexLookupFusion and TempVarHoisting implemented only for c++")
  /*
      Restrictions on IdxInline, LookupFusion and secondaryIndex imposed to reduce the number of cases that needs to handled, but
      theoretically, they can be removed.
      Currently implemented as a hack on CPP code generator, and not for scala (but no error is given if this is enabled for scala, and nothing happens)
      TmpVar hoisting is needed to avoid handling cases with and without pointers in C++.
        Currently, sampleEntries are pointers without hoisting and references after hoisting
        If this is changed, then sliceInline has no requirement of TmpVarHoist
   */

  pipeline += DCE
  if(Optimizer.parameterPromotion) {
    pipeline += ParameterPromotion
    pipeline += DCE
  }
  pipeline += new StoreDCE(IR)

  //  pipeline += new CommonPureExpression(IR)
  pipeline += new InsertNoChecks(IR)
  if (Optimizer.cTransformer) {
    pipeline += new StructDynamicAccessTransformer(IR)
    pipeline += DCE
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
    val codeB_ = prg.codeBlocks.map(t =>  {Optimizer.currentBlock = t._1; (t._1, t._2, opt(IR)(t._3))})
    val (global_, structs_, entryidx_) = opt match {
      case writer: IndexDecider => (writer.changeGlobal(prg.globalVars), prg.structs, if (Optimizer.cTransformer) (writer.genOps.values ++ writer.genCmp.values ++ writer.genFixed.values).toSeq.map(IR.Def.unapply(_).get) else prg.entryIdxDefs)
      case writer: EntryTransformer => (writer.changeGlobal(prg.globalVars), prg.structs ++ writer.getStructDefs, (writer.genOps.map(_._2) ++ writer.genCmp.map(_._2) ++ writer.genFixRngOps.map(_._2)).toSeq.collect { case IR.Def(e: EntryIdxApplyObject[_]) => e })
      case reader: CountingAnalysis[StoreDSL] =>
        prg.entryIdxDefs.collect {
          case EntryIdxApplyObject(IR.Def(hl@PardisLambda(_, _, h)), IR.Def(cl@PardisLambda2(_, _, _, c)), _) => reader(IR)(h)(hl.typeS); reader(IR)(c)(cl.typeS)
        }
        (prg.globalVars, prg.structs, prg.entryIdxDefs)
//      case writer : ScalaConstructsToCTranformer =>
//        val ei2 = prg.entryIdxDefs.collect({
//          case EntryIdxApplyObject(IR.Def(hl@PardisLambda(_, hi, h)), IR.Def(cl@PardisLambda2(_, ci1, ci2, c)), n) =>
//            val h2 = writer(IR)(h)(hl.typeS)
//            val c2 = writer(IR)(h)(cl.typeS)
//            val hl2 = ??
//            val cl2 = ???
//            EntryIdxApplyObject(hl2, cl2, n)
//
//        })
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