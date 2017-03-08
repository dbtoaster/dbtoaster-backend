package sc.micro


import java.util.Date

import ddbt.codegen.{Optimizer, TransactionProgram}
import ddbt.lib.store.deep._
import ddbt.newqq.DBToasterSquidBinding
import ddbt.transformer._

import scala.language.implicitConversions

object MicroBenchRunner {

  def main(args: Array[String]): Unit = {
    var lang = ""
    def opts(o: String) = o match {
      case "entry" => Optimizer.analyzeEntry = true
      case "index" => Optimizer.secondaryIndex = true
      case "online" => Optimizer.onlineOpts = true
      case "m3cmpmult" => Optimizer.m3CompareMultiply = true
      case "tmpvar" => Optimizer.tmpVarHoist = true
      case "tmpmap" => Optimizer.tmpMapHoist = true
      case "idxinline" => Optimizer.indexInline = true
      case "sliceinline" => Optimizer.sliceInline = true
      case "lookupfusion" => Optimizer.indexLookupFusion = true
      case "partiallookupfusion" => Optimizer.indexLookupPartialFusion = true
      case "deadidx" => Optimizer.deadIndexUpdate = true
      case "codemotion" => Optimizer.codeMotion = true
      case "refcounter" => Optimizer.refCounter = true
      case "fixedrange" => Optimizer.fixedRange = true
      case "regex" => Optimizer.regexHoister = true
      case "multires" => Optimizer.multiResSplitter = true
      case "initsize" => Optimizer.initialStoreSize = true
      case "slicenoupd" => Optimizer.sliceNoUpd = true
      case "spl" => Optimizer.splSecondaryIdx = true
      case "minmax" => Optimizer.minMaxIdx = true
      case "med" => Optimizer.medIdx = true
      case _ => throw new IllegalArgumentException(s"Unknown option $o")

    }

    def parseArgs(args: Array[String]) {
      val l = args.length
      var i = 0

      def eat(f: String => Unit, s: Boolean = false) {
        i += 1;
        if (i < l) f(if (s) args(i).toLowerCase else args(i))
      }

      while (i < l) {
        args(i) match {
          case "-opt" => eat(s => opts(s), true)
          case "-lang" => eat(s => lang = s)
          case "-info" => eat(s => Optimizer.infoFileName = s)
          case _ =>
        }
        i += 1
      }
    }

    parseArgs(args)

    import Optimizer._

    val all_opts = Map("Entry" -> analyzeEntry, "Index" -> secondaryIndex, "FixedRange" -> fixedRange, "Online" -> onlineOpts, "TmpVar" -> tmpVarHoist, "TmpMap" -> tmpMapHoist, "Inline" -> indexInline, "Fusion full" -> indexLookupFusion, "Fusion" -> indexLookupPartialFusion, "SliceInline" -> sliceInline,  "DeadIdx" -> deadIndexUpdate, "CodeMotion" -> codeMotion, "CmpMult" -> m3CompareMultiply, "RegexHoister" -> regexHoister, "RefCnt" -> refCounter, "MultiResSplitter" -> multiResSplitter, "InitialStoreSize" -> initialStoreSize, "SliceNoUpdate" -> sliceNoUpd, "Spl"->splSecondaryIdx, "MinMax"->minMaxIdx, "Med"->medIdx)
    java.lang.System.err.println("Optimizations :: " + all_opts.filter(_._2).map(_._1).mkString(", "))


    val Context = if (Optimizer.onlineOpts) new StoreDSLOptimized {
    } else new StoreDSL {
    }

    var prog: Prog = new MB1(Context)
    import Context._

    val codeGen = lang match {
      case "scala" => new MicroBenchPardisScalaGen(Context)
      case "cpp" => Optimizer.cTransformer = true;
        new MicroBenchPardisCppGen(Context)
    }
    val initialTP: TransactionProgram[Int] = prog.getTransactionProgram
    val optTP = new Optimizer(Context).optimize(initialTP)
    codeGen.generate(optTP)
  }

  abstract class Prog(val Context: StoreDSL) extends  DBToasterSquidBinding(Context) {
    def getTransactionProgram: TransactionProgram[Int]
  }

}
