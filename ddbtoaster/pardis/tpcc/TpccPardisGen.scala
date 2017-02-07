package sc.tpcc

import java.io.PrintWriter
import java.nio.file.Files._
import java.nio.file.Paths._
import java.nio.file.StandardCopyOption._

import ch.epfl.data.sc.pardis.ir.CTypes.PointerType
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
    if (Optimizer.analyzeIndex) {
      copy(s"$genDir/SCTxSplEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
    } else {
      copy(s"$genDir/SCTxSplEntry-SE.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
    }
  } else {
    copy(s"$genDir/SCTxGenEntry.txt", s"$genDir/SCTx.scala", REPLACE_EXISTING)
  }
  override val codeGen: StoreScalaCodeGenerator = new StoreScalaCodeGenerator(IR)

  override def generate[T](optTP: TransactionProgram[T]): Unit = {
    import IR._
    import codeGen.expLiftable, codeGen.tpeLiftable, codeGen.ListDocumentOps2
    var codestr = codeGen.blockToDocument(optTP.initBlock).toString
    var i = codestr.lastIndexOf("1")
    val allstores = optTP.globalVars.map(_.name).mkDocument(", ")
    val executor = "class SCExecutor \n" + codestr.substring(0, i) + "\n" +
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
      val argsWithTypes = optTP.globalVars.map(m => doc"$m : Store[${storeType(m).tp}]").mkDocument(", ")
      val genCode = doc"  class $className($argsWithTypes) extends ((${args.map(_.tp).mkDocument(", ")}) => ${body.typeT} ) {" :/:
        doc"    def apply(${args.map(s => doc"$s : ${s.tp}").mkDocument(", ")}) = "
      val cgDoc = Document.nest(4, codeGen.blockToDocument(body))
      file.println(genCode + cgDoc.toString + "\n  }")
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
       |#define SC_GENERATED 1
       |#define USING_GENERIC_ENTRY ${!Optimizer.analyzeEntry}
       |
       |#include <algorithm>
       |#include <vector>
       |#include <unordered_set>
       |#include <mmap.hpp>
       |#include <iomanip>
       |#include <fstream>
       |#include <locale>
       |
       |#include "ExecutionProfiler.h"
       |
       |using namespace std;
       |#include "hpds/pstring.hpp"
       |#include "hpds/pstringops.hpp"
       |#include "program_base.hpp"
       |
       |#ifdef NUMWARE
       |  const int numWare = NUMWARE;
       |#else
       |  const int numWare = 2;
       |#endif
       |#ifdef NUMPROG
       |  const size_t numPrograms = NUMPROG;
       |#else
       |  const size_t numPrograms = 100;
       |#endif
       |
       |const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
       |const size_t itemTblSize = 100000;
       |const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
       |const size_t customerTblSize = districtTblSize * 3000;
       |const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
       |const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
       |const size_t orderLineTblSize = orderTblSize * 12;
       |const size_t stockTblSize = numWare * itemTblSize;
       |const size_t historyTblSize = orderTblSize;
       |
     """.stripMargin

  override val codeGen = new StoreCppCodeGenerator(IR)


  override val file: PrintWriter = new PrintWriter(s"$genDir/TpccGenSC.cpp")
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
            val ord = Def.unapply(n.f).get.asInstanceOf[PardisLambda[_, _]].o.stmts(0).rhs match {
              case GenericEntryGet(_, Constant(i)) => i
            }
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
        case "IList" => doc"ListIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
      }

    }

    val stores = optTP.globalVars.map(s => {
      def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"

      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      val idxTypes = idx2(s).filter(_._2 != "INone").map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
      val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

      val storeTypeDef = doc"typedef MultiHashMap<${entryTp}, char," :/: idxTypes.map(_._1).mkDocument("   ", ",\n   ", ">") :: doc" ${s.name}StoreType;"
      val storeDecl = s.name :: "StoreType  " :: s.name :: ";" //"(" :: s.name :: "Size);"

      val idxDecl = idx2(s).filter(_._2 != "INone").zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1} = * (${idxTypeName(t._2)} *)${s.name}.index[${t._2}];").mkDocument("\n")
      val primaryIdx = idx2(s)(0)
      val primaryRef = doc"${idxTypeName(0)}& ${s.name}PrimaryIdx = * (${idxTypeName(0)} *) ${s.name}.index[0];"
      idxTypeDefs :\\: storeTypeDef :\\: storeDecl :\\: idxDecl :\\: primaryRef
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
            doc"*${x.name}.copy()"
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
    def mainPrg =
      s"""
         |TPCCDataGen tpcc;
         |tpcc.loadPrograms();
         |tpcc.loadWare();
         |tpcc.loadDist();
         |tpcc.loadCust();
         |tpcc.loadItem();
         |tpcc.loadNewOrd();
         |tpcc.loadOrders();
         |tpcc.loadOrdLine();
         |tpcc.loadHist();
         |tpcc.loadStocks();
         |
         |uint xactCounts[5] = {0, 0, 0, 0, 0};
         |auto start = Now;
         |for(size_t i = 0; i < numPrograms; ++i){
         |  Program *prg = tpcc.programs[i];
         |  switch(prg->id){
         |     case NEWORDER :
         |      {
         |         NewOrder& p = *(NewOrder *)prg;
         |         xactCounts[0]++;
         |         NewOrderTx($showOutput, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
         |         break;
         |      }
         |    case PAYMENTBYID :
         |      {
         |         PaymentById& p = *(PaymentById *) prg;
         |         xactCounts[1]++;
         |         PaymentTx($showOutput, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
         |         break;
         |      }
         |    case PAYMENTBYNAME :
         |      {
         |         PaymentByName& p = *(PaymentByName *) prg;
         |         xactCounts[1]++;
         |         PaymentTx($showOutput, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
         |         break;
         |      }
         |    case ORDERSTATUSBYID :
         |      {
         |         OrderStatusById &p = *(OrderStatusById *) prg;
         |         xactCounts[2]++;
         |         OrderStatusTx($showOutput, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
         |         break;
         |      }
         |    case ORDERSTATUSBYNAME :
         |      {
         |         OrderStatusByName &p = *(OrderStatusByName *) prg;
         |         xactCounts[2]++;
         |         OrderStatusTx($showOutput, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
         |         break;
         |      }
         |    case DELIVERY :
         |      {
         |         Delivery &p = *(Delivery *) prg;
         |         xactCounts[3]++;
         |         DeliveryTx($showOutput, p.datetime, p.w_id, p.o_carrier_id);
         |         break;
         |      }
         |    case STOCKLEVEL :
         |     {
         |       StockLevel &p = *(StockLevel *) prg;
         |       xactCounts[4]++;
         |       StockLevelTx($showOutput, -1, -1, p.w_id, p.d_id, p.threshold);
         |       break;
         |     }
         |     default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
         |
         |  }
         |}
         |auto end = Now;
         |auto execTime = DurationMS(end - start);
         |cout << "Total time = " << execTime << " ms" << endl;
         |cout << "TpmC = " << fixed <<  xactCounts[0] * 60000.0/execTime << endl;
         |ofstream fout("tpcc_res_cpp.csv", ios::app);
         |if(argc == 1 || atoi(argv[1]) == 1)
         |  fout << "\\nCPP-${Optimizer.optCombination},";
         |fout << fixed << xactCounts[0] * 60000.0/execTime << ",";
         |fout.close();

         |#ifdef VERIFY_TPCC
         |    if (warehouseTblPrimaryIdx == tpcc.wareRes) {
         |        cout << "Warehouse results are correct" << endl;
         |    } else {
         |        cerr << "Warehouse results INCORRECT!" << endl;
         |    }
         |    if (districtTblPrimaryIdx == tpcc.distRes) {
         |        cout << "District results are correct" << endl;
         |    } else {
         |        cerr << "District results INCORRECT!" << endl;
         |    }
         |    if (customerTblPrimaryIdx == tpcc.custRes) {
         |        cout << "Customer results are correct" << endl;
         |    } else {
         |        cerr << "Customer results INCORRECT!" << endl;
         |    }
         |    if (orderTblPrimaryIdx == tpcc.ordRes) {
         |        cout << "Order results are correct" << endl;
         |    } else {
         |        cerr << "Order results INCORRECT!" << endl;
         |    }
         |    if (orderLineTblPrimaryIdx == tpcc.ordLRes) {
         |        cout << "OrderLine results are correct" << endl;
         |    } else {
         |        cerr << "OrderLine results INCORRECT!" << endl;
         |    }
         |    if (newOrderTblPrimaryIdx == tpcc.newOrdRes) {
         |        cout << "NewOrder results are correct" << endl;
         |    } else {
         |        cerr << "NewOrder results INCORRECT!" << endl;
         |    }
         |    if (itemTblPrimaryIdx == tpcc.itemRes) {
         |        cout << "Item results are correct" << endl;
         |    } else {
         |        cerr << "Item results INCORRECT!" << endl;
         |    }
         |    if (stockTblPrimaryIdx == tpcc.stockRes) {
         |        cout << "Stock results are correct" << endl;
         |    } else {
         |        cerr << "Stock results INCORRECT!" << endl;
         |    }
         |    if (historyTblPrimaryIdx == tpcc.histRes) {
         |        cout << "History results are correct" << endl;
         |    } else {
         |        cerr << "History results INCORRECT!" << endl;
         |    }
         |
         |#endif
         |
      """.stripMargin
    file.println(header :/: structs :\\: structEquals :\\: entryIdxes :\\: stores :\\: structVars :: "\n\n" :\\: blocks :\\: "#include \"TPCC.h\"\n" :\\: traits :/: Document.nest(2, mainPrg) :/: codeGen.footer)
    file.close()
  }
}