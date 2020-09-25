package sc.micro

import java.io.{File, PrintWriter}

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.types.PardisType
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.codegen.{Optimizer, TransactionProgram}
import ddbt.codegen.prettyprinter.{StoreCodeGenerator, StoreCppCodeGenerator, StoreScalaCodeGenerator}
import ddbt.lib.store.deep.StoreDSL
import ddbt.transformer.Index
import scala.util.parsing.json.JSON


trait MicroBenchPardisGen {
  def header: String


  val infoFile = new File(s"runtime/stats/${if (Optimizer.infoFileName == "") "default" else Optimizer.infoFileName}.json")
  val infoFilePath = infoFile.getAbsolutePath
  var StoreArrayLengths = Map[String, String]()
  var idxSymNames: List[String] = null

  if (infoFile.exists()) {
    val txt = new java.util.Scanner(infoFile).useDelimiter("\\Z").next()
    val allinfo: Map[String, _] = JSON.parseFull(txt).get.asInstanceOf[Map[String, _]]
    StoreArrayLengths = allinfo.map(t => t._1 -> t._2.asInstanceOf[Map[String, String]].getOrElse("OptArrayLength", "0"))
  } else if(Optimizer.initialStoreSize) {
    System.err.println("Runtime info file missing!!  Using default initial sizes")
  }

  val codeGen: StoreCodeGenerator
  val genDir = "runtime/microbench/"


  def generate[T](optTP: TransactionProgram[T])

  val file: PrintWriter
}

class MicroBenchPardisScalaGen(IR: StoreDSL) extends MicroBenchPardisGen {
  override def header: String =
    """
      |package ddbt.micro
      |import ddbt.lib.store._
      | """.stripMargin


  override val file: PrintWriter = new PrintWriter(s"$genDir/MicroBench.scala")

  override val codeGen: StoreScalaCodeGenerator = new StoreScalaCodeGenerator(IR)

  override def generate[T](optTP: TransactionProgram[T]): Unit = {
    import IR._
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    var codestr = Document.nest(2, codeGen.blockToDocumentNoBraces(optTP.initBlock)).toString
    var i = codestr.lastIndexOf("1")
    val allstores = optTP.globalVars.map(_.name).mkDocument(", ")
    val executor =
      s"""class SCExecutor {

          """.stripMargin + codestr.substring(0, i) + "\n" +
        (if (Optimizer.initialStoreSize && !StoreArrayLengths.isEmpty) {
            val tbls = StoreArrayLengths.keys.toList.groupBy(_.split("Idx")(0)).map(t => t._1 -> t._2.map(StoreArrayLengths.getOrElse(_, "1")))
            tbls.map(t => doc"  ${t._1}.setInitialSizes(List(${t._2.mkString(",")}))").mkString("\n") +"\n"
        }
        else "")

    file.println(header)
    val entries = optTP.structs.map(codeGen.getStruct).mkDocument("\n")
    file.println(entries)
    file.println(executor)
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    implicit val tp = IntType.asInstanceOf[TypeRep[Any]]
    val tempVars = optTP.tempVars.map(t => codeGen.stmtToDocument(Statement(t._1, t._2))).mkDocument("\n")
    val r = Document.nest(2, entryIdxes :/: tempVars)
    file.println(r)
    optTP.codeBlocks.foreach { case (className, args: List[Sym[_]], body) => {
      val argsWithTypes = optTP.globalVars.map(m => doc"$m : Store[${storeType(m).tp}]").mkDocument(", ")
      val genCode = doc"  class $className($argsWithTypes) extends ((${args.map(_.tp).mkDocument(", ")}) => ${body.typeT} ) {" :\\:
        doc"    def apply(${args.map(s => doc"$s : ${s.tp}").mkDocument(", ")}) = {"
      val cgDoc = Document.nest(6, codeGen.blockToDocumentNoBraces(body))
      file.println(genCode + cgDoc.toString + "\n    }\n  }")
    }
    }
    file.println("\n}")
    file.close()
  }
}

class MicroBenchPardisCppGen(val IR: StoreDSL) extends MicroBenchPardisGen {

  import IR._

  def genInitArrayLengths = {
    val tbls = idxSymNames.groupBy(_.split("Idx")(0)).map(t => t._1 -> t._2.map(StoreArrayLengths.getOrElse(_, "1")))
    tbls.map(t => doc"const size_t ${t._1}ArrayLengths[] = ${t._2.mkString("{", ",", "};")}").toList.mkDocument("\n")
  }

  override def header: String = codeGen.header +
    s"""
       |#define SC_GENERATED 1
       |#define USING_GENERIC_ENTRY ${!Optimizer.analyzeEntry}
       |
       |#include <algorithm>
       |#include <vector>
       |#include <unordered_set>
       |#include <iomanip>
       |#include <fstream>
       |#include <locale>
       |
       |#include "sc/mmap.hpp"
       |#include "sc/ExecutionProfiler.h"
       |
       |using namespace std;
       |#include "hpds/pstring.hpp"
       |#include "hpds/pstringops.hpp"
       |#include "program_base.hpp"
       |
     """.stripMargin

  override val codeGen = new StoreCppCodeGenerator(IR)


  override val file: PrintWriter = new PrintWriter(s"$genDir/MicroBench.cpp")
  val showOutput = false

  override def generate[T](optTP: TransactionProgram[T]): Unit = {

    codeGen.currentProgram = PardisProgram(optTP.structs, optTP.main, Nil)
    codeGen.refSymbols ++= optTP.tempVars.map(_._1)
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    val idxes = optTP.globalVars.map(s => s ->(collection.mutable.ArrayBuffer[(Sym[_], String, Boolean, Int)](), collection.mutable.ArrayBuffer[String]())).toMap
    optTP.initBlock.stmts.collect {
      case Statement(s, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) => {
        val names = ops.collect {
          case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
          case Def(n: EntryIdxGenericOpsObject) =>
            val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
            if (cols.isEmpty)
              s"GenericOps"
            else {
              s"GenericOps_$cols"
            }
          case Def(n: EntryIdxGenericCmpObject[_]) =>
            val ord = Index.getColumnNumFromLambda(Def.unapply(n.f).get.asInstanceOf[PardisLambda[_, _]])
            val cols = n.cols.asInstanceOf[Constant[List[Int]]].underlying.mkString("")
            s"GenericCmp_${cols.mkString("")}_$ord"

          case Def(n: EntryIdxGenericFixedRangeOpsObject) =>
            val cols = n.colsRange.asInstanceOf[Constant[List[(Int, Int, Int)]]].underlying.map(t => s"${t._1}f${t._2}t${t._3}").mkString("_")
            s"GenericFixedRange_$cols"
        }
        idxes(s)._2.++=(names)
      }
      case Statement(sym, StoreIndex(s, _, Constant(typ), Constant(uniq), Constant(other))) => idxes(s.asInstanceOf[Sym[Store[_]]])._1.+=((sym, typ, uniq, other))
    }
    val idx2 = idxes.map(t => t._1 -> (t._2._1 zip t._2._2 map (x => (x._1._1, x._1._2, x._1._3, x._1._4, x._2))).toList) // Store -> List[Sym, Type, unique, otherInfo, IdxName ]
    def idxToDoc(idx: (Sym[_], String, Boolean, Int, String), entryTp: PardisType[_], allIdxs: List[(Sym[_], String, Boolean, Int, String)]): Document = {
      idx._2 match {
        case "IHash" => doc"HashIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
        case "IDirect" => doc"ArrayIndex<$entryTp, char, ${idx._5}, ${unit(idx._4)}>"
        case "ISliceHeapMax" => val idx2 = allIdxs(idx._4); doc"SlicedHeapIndex<$entryTp, char, ${idx2._5}, ${idx._5}, ${unit(true)}>"
        case "ISliceHeapMin" => val idx2 = allIdxs(idx._4); doc"SlicedHeapIndex<$entryTp, char, ${idx2._5}, ${idx._5}, ${unit(false)}>"
        case "ISlicedHeapMed" => val idx2 = allIdxs(idx._4); doc"SlicedMedHeapIndex<$entryTp, char, ${idx2._5}, ${idx._5}>"
        case "IList" => doc"ListIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
      }

    }

    val stores = optTP.globalVars.map(s => {
      def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"

      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      val idxTypes = idx2(s).filter(_._2 != "INone").map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
      val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

      val storeTypeDef = doc"typedef MultiHashMap<${entryTp}, char," :/: idxTypes.map(_._1).mkDocument("   ", ",\n   ", ">") :: doc" ${s.name}StoreType;"
      val initSize = if (Optimizer.initialStoreSize) doc"(${s.name}ArrayLengths, ${s.name}PoolSizes);" else doc";"
      val storeDecl = s.name :: "StoreType  " :: s.name :: initSize

      val idxDecl = idx2(s).filter(_._2 != "INone").zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1} = * (${idxTypeName(t._2)} *)${s.name}.index[${t._2}];").mkDocument("\n")
      idxTypeDefs :\\: storeTypeDef :\\: storeDecl :\\: idxDecl
    }).mkDocument("\n", "\n\n\n", "\n")

    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    def structToDoc(s: PardisStructDef[_]) = s match {
      case PardisStructDef(tag, fields, methods) =>
        val fieldsDoc = fields.map(x => doc"${x.tpe} ${x.name};").mkDocument("  ") :: doc"  ${tag.typeName} *prv;  ${tag.typeName} *nxt; void* backPtrs[${fields.size}];"
        val constructor = doc"${tag.typeName}() :" :: fields.map(x => {
          if (x.tpe == StringType)
            doc"${x.name}()"
          else doc"${x.name}(${nullValue(x.tpe)})"
        }).mkDocument(", ") :: ", prv(nullptr), nxt(nullptr) {}"
        val constructorWithArgs = doc"${tag.typeName}(" :: fields.map(x => doc"const ${x.tpe}& ${x.name}").mkDocument(", ") :: ") : " :: fields.map(x => doc"${x.name}(${x.name})").mkDocument(", ") :: ", prv(nullptr), nxt(nullptr) {}"
        val copyFn = doc"${tag.typeName}* copy() const { return new ${tag.typeName}(" :: fields.map(x => {
          if (x.tpe == StringType)
            doc"${x.name}.copy()"
          else
            doc"${x.name}"
        }).mkDocument(", ") :: "); }"
        "struct " :: tag.typeName :: " {" :/: Document.nest(2, fieldsDoc :/: constructor :/: constructorWithArgs :/: copyFn) :/: "};"
    }

    val structs = optTP.structs.map(structToDoc).mkDocument("\n")
    val structVars = optTP.tempVars.map(st => doc"${st._2.tp} ${st._1};").mkDocument("\n")
    val structEquals = optTP.structs.map(s => {
      val sname = s.tag.typeName
      def eqFn(x: StructElemInformation) = {
        val n = x.name
        x.tpe.asInstanceOf[TypeRep[_]] match {
          case StringType => doc"o1.$n == o2.$n"
          case DoubleType => doc"(fabs(o1.$n - o2.$n) < 0.01)"
          case _ => doc"o1.$n == o2.$n"
        }
      }
      val equals = s.fields.map(eqFn).reduce(_ :: " && " :/: _)
      doc"bool operator== (const $sname& o1, const $sname& o2) {" :\\: Document.nest(2, "return " :: equals :: ";") :\\: "}"
    }).mkDocument("\n")

    val traits = doc"/* TRAITS STARTING */" :/: codeGen.getTraitSignature :/: doc" /* TRAITS ENDING   */"
    def argsDoc(args: List[Sym[_]]) = args.map(t => doc"${t.tp} ${t}").mkDocument(", ")
    //    def blockTofunction(x :(String, List[ExpressionSymbol[_]], PardisBlock[T])) = {
    //      (Sym.freshNamed(x._1)(x._3.typeT, IR), x._2, x._3)
    //    }
    //    optTP.codeBlocks.foreach(x => codeGen.functionsList += (blockTofunction(x)))

    val blocks = optTP.codeBlocks.map(x => doc"void ${x._1}(${argsDoc(x._2)}) {" :: Document.nest(2, codeGen.blockToDocument(x._3)) :/: "}").mkDocument("\n")
    idxSymNames = idx2.values.flatMap(l => l.filter(x => x._2 != "INone").map(_._1.name)).toList
    val getSizes = idxSymNames.map(i => doc"GET_RUN_STAT($i, info);").mkDocument("info << \"{\\n\";\n", "\ninfo <<\",\\n\";\n", "\ninfo << \"\\n}\\n\";")
    def mainPrg =
      s"""
         | MB1 loader;
         | loader.loadCust();
         |
         | size_t durations[5];
         | for(int i = 0; i < 5; ++i) {
         |    auto start = Now;
         |    fun1();
         |    auto end = Now;
         |    durations[i] = DurationMS(end-start);
         |    cout << durations[i] << endl;
         | }
         |
      """.stripMargin
    file.println(header :/: structs :\\: structEquals :\\: entryIdxes :\\: stores :\\: structVars :: "\n\n" :\\: blocks :\\: "#include \"sc/MB1.h\"\n" :\\: traits :/: Document.nest(2, mainPrg) :/: "}")
    file.close()
  }
}