package sc.tpcc

import java.io.PrintWriter
import java.nio.file.Files._
import java.nio.file.Paths._
import java.nio.file.StandardCopyOption._

import ch.epfl.data.sc.pardis.ir._
import ch.epfl.data.sc.pardis.types.PardisType
import ch.epfl.data.sc.pardis.utils.document._
import ddbt.codegen.{Optimizer, TransactionProgram}
import ddbt.codegen.prettyprinter.{StoreCodeGenerator, StoreCppCodeGenerator, StoreScalaCodeGenerator}
import ddbt.lib.store.deep.StoreDSL


/**
  * Created by sachin on 14/09/16.
  */
trait TpccPardisGen {
  def header: String

  val codeGen: StoreCodeGenerator
  val genDir = "../runtime/tpcc/pardisgen"


  def generate[T](optTP: TransactionProgram[T])

  val file: PrintWriter
}

class TpccPardisScalaGen(IR: StoreDSL) extends TpccPardisGen {
  override def header: String =
    """
      |package tpcc.sc
      |import ddbt.lib.store._
      |import scala.collection.mutable.{ArrayBuffer,Set}
      |import java.util.Date
      | """.stripMargin


  override val file: PrintWriter = new PrintWriter(s"$genDir/TpccGenSC.scala")

  implicit def toPath(filename: String) = get(filename)

  if (Optimizer.analyzeEntry) {
    copy(s"$genDir/SCTxSplEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
  } else {
    copy(s"$genDir/SCTxGenEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
  }
  override val codeGen: StoreCodeGenerator = new StoreScalaCodeGenerator(IR)

  override def generate[T](optTP: TransactionProgram[T]): Unit = {
    import IR._
    var codestr = codeGen.blockToDocument(optTP.initBlock).toString
    var i = codestr.lastIndexOf("1")
    val storesnames = List("newOrderTbl", "historyTbl", "warehouseTbl", "itemTbl", "orderTbl", "districtTbl", "orderLineTbl", "customerTbl", "stockTbl")
    val allstores = storesnames.mkString(",")
    val executor = "class SCExecutor \n" + codestr.substring(0, i) + "\n" + storesnames.zip(optTP.globalVars).map(t => {
      s"""  val ${t._1} = ${codeGen.expToDocument(t._2)}""".stripMargin
    }).mkString("\n") +
      s"""
         |  val newOrderTxInst = new NewOrderTx($allstores)
         |  val paymentTxInst = new PaymentTx($allstores)
         |  val orderStatusTxInst = new OrderStatusTx($allstores)
         |  val deliveryTxInst = new DeliveryTx($allstores)
         |  val stockLevelTxInst = new StockLevelTx($allstores)

      """.stripMargin
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
      val genCode = "  class " + className + "(" + optTP.globalVars.map(_.asInstanceOf[Sym[_]]).map(m => m.name + m.id + s": Store[${storeType(m).name}]").mkString(", ") + ") extends ((" + args.map(s => codeGen.tpeToDocument(s.tp)).mkString(", ") + ") => " + codeGen.tpeToDocument(body.typeT) + ") {\n" +
        "    def apply(" + args.map(s => s + ": " + codeGen.tpeToDocument(s.tp)).mkString(", ") + ") = "
      val cgDoc = Document.nest(4, codeGen.blockToDocument(body))
      file.println(genCode + cgDoc + "\n  }")
    }
    }
    file.println("\n}")

    //    new TpccCompiler(Context).compile(codeBlock, "test/gen/tpcc")
    file.close()
  }
}

class TpccPardisCppGen(val IR: StoreDSL) extends TpccPardisGen {

  import IR._

  override def header: String = codeGen.header +
    s"""
       |#include <vector>
       |#include <unordered_set>
       |#include <mmap.hpp>
       |using namespace std;
       |
       |typedef unsigned int Date;
     """.stripMargin

  override val codeGen = new StoreCppCodeGenerator(IR)


  override val file: PrintWriter = new PrintWriter(s"$genDir/TpccGenSC.cpp")

  override def generate[T](optTP: TransactionProgram[T]): Unit = {

    codeGen.currentProgram = PardisProgram(optTP.structs, optTP.main, optTP.tempVars.map(_._1).toList)
    codeGen.refSymbols ++= codeGen.currentProgram.globalVars
    val idxes = optTP.globalVars.map(s => s -> (collection.mutable.ArrayBuffer[(String, Boolean, Int)](), collection.mutable.ArrayBuffer[String]())).toMap
    optTP.initBlock.stmts.collect {
      case Statement(s, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) => {
        val names = ops.collect {
          case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
        }
        idxes(s)._2.++=(names)
      }
      case Statement(_, StoreIndex(s, _, Constant(typ), Constant(uniq), Constant(other))) => idxes(s.asInstanceOf[Sym[Store[_]]])._1.+=((typ, uniq, other))
    }
    val idx2 = idxes.map(t => t._1 -> (t._2._1 zip t._2._2 map (x => (x._1._1, x._1._2, x._1._3, x._2))).toList)   // Store -> List[ Type, unique, otherInfo, IdxName ]
    def idxToDoc(idx: (String, Boolean, Int, String), entryTp: PardisType[_]) = {
      val idxType = idx._1 match {
        case "IHash" => "HashIndex"
        case "IDirect" => "ArrayIndex"
        case "INone" => "NoIndex"
        case "ISliceHeapMax" => "TreeIndex"
        case "ISliceHeapMin" => "TreeIndex"
        case "IList" => "ListIndex"
      }
      idxType :: "<" :: codeGen.tpeToDocument(entryTp) :: ", void, " :: idx._4 :: ", " :: codeGen.expToDocument(unit(idx._2)) :: ">"
    }
    val storesnames = optTP.globalVars.zip(List("newOrderTbl", "historyTbl", "warehouseTbl", "itemTbl", "orderTbl", "districtTbl", "orderLineTbl", "customerTbl", "stockTbl")).toMap
    val stores = optTP.globalVars.map(s => {
      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      "MultiHashMap<" :: codeGen.tpeToDocument(entryTp) :: ",void,\n   " :: idx2(s).map(idxToDoc(_, entryTp)).mkDocument(",\n   ") ::  " > " :: codeGen.expToDocument(s) :: ";\n" ::
      "auto " :: storesnames(s) :: "& = " :: codeGen.expToDocument(s) :: ";\n"

    }).mkDocument("\n")
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    val structs = codeGen.getStructs(optTP.structs)
    val traits = doc"/* TRAITS STARTING */" :/: codeGen.getTraitSignature :/: doc" /* TRAITS ENDING   */"
    def argsDoc(args: List[Sym[_]]) = args.map(a => codeGen.tpeToDocument(a.tp) :: " " :: codeGen.expToDocument(a)).mkDocument(", ")
    //    def blockTofunction(x :(String, List[ExpressionSymbol[_]], PardisBlock[T])) = {
    //      (Sym.freshNamed(x._1)(x._3.typeT, IR), x._2, x._3)
    //    }
    //    optTP.codeBlocks.foreach(x => codeGen.functionsList += (blockTofunction(x)))

    val blocks = optTP.codeBlocks.map(x => doc"void ${x._1}(${argsDoc(x._2)}) {" :: Document.nest(2, codeGen.blockToDocument(x._3)) :/: "}").mkDocument("\n")
    file.println(header :/: structs :/: entryIdxes :/: stores :/: blocks :/: traits :/: codeGen.footer)
    file.close()
  }
}