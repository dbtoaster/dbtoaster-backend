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
       |#include <algorithm>
       |#include <vector>
       |#include <unordered_set>
       |#include <mmap2.hpp>
       |using namespace std;
       |
       |FORCE_INLINE size_t HASH(int x) { return x; }
       |FORCE_INLINE size_t HASH(char *x) {
       |   size_t hash = 7;
       |   int N = strlen(x);
       |   for (int i = 0; i < (N < 100 ? N : 100); i++) {
       |      hash = hash * 31 + x[i];
       |   }
       |   return hash;
       |}
       |
       |bool strcmpi(const char* This, const char *That) {
       |   int i = 0;
       |   while(true) {
       |      char c1 = tolower(This[i]);
       |      char c2 = tolower(That[i]);
       |      if(c1 == 0 || c2 == 0)
       |        return c1 == c2;
       |      else if (c1 == c2) {
       |          i++;
       |          continue;
       |      }
       |      else if (c1 < c2)
       |          return true;
       |      else return false;
       |   }
       |}
       |
       |typedef size_t Date;
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

    val idxes = optTP.globalVars.map(s => s -> (collection.mutable.ArrayBuffer[(Sym[_], String, Boolean, Int)](), collection.mutable.ArrayBuffer[String]())).toMap
    optTP.initBlock.stmts.collect {
      case Statement(s, StoreNew3(_, Def(ArrayApplyObject(Def(LiftedSeq(ops)))))) => {
        val names = ops.collect {
          case Def(EntryIdxApplyObject(_, _, Constant(name))) => name
        }
        idxes(s)._2.++=(names)
      }
      case Statement(sym, StoreIndex(s, _, Constant(typ), Constant(uniq), Constant(other))) => idxes(s.asInstanceOf[Sym[Store[_]]])._1.+=((sym, typ, uniq, other))
    }
    val idx2 = idxes.map(t => t._1 -> (t._2._1 zip t._2._2 map (x => (x._1._1, x._1._2, x._1._3, x._1._4, x._2))).toList) // Store -> List[Sym, Type, unique, otherInfo, IdxName ]
    def idxToDoc(idx: (Sym[_], String, Boolean, Int, String), entryTp: PardisType[_], allIdxs: List[(Sym[_], String, Boolean, Int, String)]) = {
      idx._2 match {
        case "IHash" => "HashIndex<" :: codeGen.tpeToDocument(entryTp) :: ", char, " :: idx._5 :: ", " :: codeGen.expToDocument(unit(idx._3)) :: ">"
        case "IDirect" => "ArrayIndex<" :: codeGen.tpeToDocument(entryTp) :: ", char, " :: idx._5 :: ", " :: codeGen.expToDocument(unit(idx._4)) :: ">"
        case "ISliceHeapMax" => val idx2 = allIdxs(idx._4); "TreeIndex<" :: codeGen.tpeToDocument(entryTp) :: ", char, " :: idx2._5 :: ", " :: idx._5 :: ", " :: codeGen.expToDocument(unit(true)) :: ">"
        case "ISliceHeapMin" => val idx2 = allIdxs(idx._4); "TreeIndex<" :: codeGen.tpeToDocument(entryTp) :: ", char, " :: idx2._5 :: ", " :: idx._5 :: ", " :: codeGen.expToDocument(unit(false)) :: ">"
        case "IList" => "HashIndex< " :: codeGen.tpeToDocument(entryTp) :: ", char, " :: idx._5 :: ", " :: codeGen.expToDocument(unit(idx._3)) :: ">"
      }

    }
    val storesnames = optTP.globalVars.zip(List("newOrderTbl", "historyTbl", "warehouseTbl", "itemTbl", "orderTbl", "districtTbl", "orderLineTbl", "customerTbl", "stockTbl")).toMap
    val stores = optTP.globalVars.map(s => {
      def idxTypeName(i: Int) = storesnames(s) :: "Idx" ::i::"Type"

      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      val idxTypes = idx2(s).filter(_._2 != "INone").map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
      val idxTypeDefs = idxTypes.map(t => "typedef " :: t._1 ::"  ":: idxTypeName(t._2) ::";").mkDocument("\n")

      val storeTypeDef = "typedef MultiHashMap<" :: codeGen.tpeToDocument(entryTp) :: ",char ,\n   " ::idxTypes.map(_._1).mkDocument(",\n   ") :: " >  " :: storesnames(s) :: "StoreType;"
      val storeDecl = storesnames(s)::"StoreType  ":: storesnames(s) :: "(" ::storesnames(s)::"Size);"
      val storeRef = storesnames(s)::"StoreType& " :: codeGen.expToDocument(s) :: " = " :: storesnames(s) :: ";"

      val idxDecl = idx2(s).filter(_._2 != "INone").zipWithIndex.map(t => idxTypeName(t._2) ::"& " ::codeGen.expToDocument(t._1._1) :: " = * (" :: idxTypeName(t._2) :: "*) " :: storesnames(s) :: doc".index[${t._2}];").mkDocument("\n")
      idxTypeDefs :\\: storeTypeDef :\\: storeDecl :\\: storeRef :\\: idxDecl
    }).mkDocument("\n", "\n\n\n", "\n")
    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    val structs = codeGen.getStructs(optTP.structs)
    val structVars = optTP.tempVars.map(st => codeGen.tpeToDocument(st._2.tp) :: " " :: codeGen.expToDocument(st._1) :: ";").mkDocument("\n")
    val traits = doc"/* TRAITS STARTING */" :/: codeGen.getTraitSignature :/: doc" /* TRAITS ENDING   */"
    def argsDoc(args: List[Sym[_]]) = args.collect {
      case a if a.tp.isArray => (a, PointerType(a.tp.typeArguments(0)))
      case a => (a, a.tp)
    }.map(t => codeGen.tpeToDocument(t._2) :: " " :: codeGen.expToDocument(t._1)).mkDocument(", ")
    //    def blockTofunction(x :(String, List[ExpressionSymbol[_]], PardisBlock[T])) = {
    //      (Sym.freshNamed(x._1)(x._3.typeT, IR), x._2, x._3)
    //    }
    //    optTP.codeBlocks.foreach(x => codeGen.functionsList += (blockTofunction(x)))

    val blocks = optTP.codeBlocks.map(x => doc"void ${x._1}(${argsDoc(x._2)}) {" :: Document.nest(2, codeGen.blockToDocument(x._3)) :/: "}").mkDocument("\n")
    def mainPrg =
      s"""
        |TPCCDataGen tpcc;
        |tpcc.loadPrograms();
        |tpcc.loadWare(warehouseTbl);
        |tpcc.loadDist(districtTbl);
        |tpcc.loadCust(customerTbl);
        |tpcc.loadItem(itemTbl);
        |tpcc.loadNewOrd(newOrderTbl);
        |tpcc.loadOrders(orderTbl);
        |tpcc.loadOrdLine(orderLineTbl);
        |tpcc.loadHist(historyTbl);
        |tpcc.loadStocks(stockTbl);
        |
        |for(int i=0; i<numPrograms; ++i){
        |  Program *prg = tpcc.programs[i];
        |  switch(prg->id){
        |     case NEWORDER :
        |      {
        |         NewOrder& p = *(NewOrder *)prg;
        |         NewOrderTx($showOutput, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
        |         break;
        |      }
        |    case PAYMENTBYID :
        |      {
        |         PaymentById& p = *(PaymentById *) prg;
        |         PaymentTx($showOutput, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
        |         break;
        |      }
        |    case PAYMENTBYNAME :
        |      {
        |         PaymentByName& p = *(PaymentByName *) prg;
        |         PaymentTx($showOutput, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
        |         break;
        |      }
        |    case ORDERSTATUSBYID :
        |      {
        |         OrderStatusById &p = *(OrderStatusById *) prg;
        |         OrderStatusTx($showOutput, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
        |         break;
        |      }
        |    case ORDERSTATUSBYNAME :
        |      {
        |         OrderStatusByName &p = *(OrderStatusByName *) prg;
        |         OrderStatusTx($showOutput, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
        |         break;
        |      }
        |    case DELIVERY :
        |      {
        |         Delivery &p = *(Delivery *) prg;
        |         DeliveryTx($showOutput, p.datetime, p.w_id, p.o_carrier_id);
        |         break;
        |      }
        |    case STOCKLEVEL :
        |     {
        |       StockLevel &p = *(StockLevel *) prg;
        |       StockLevelTx($showOutput, -1, -1, p.w_id, p.d_id, p.threshold);
        |       break;
        |     }
        |     default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
        |
        |  }
        |}
        |
      """.stripMargin
    file.println(header :/: structs :\\: entryIdxes :\\: stores :\\: structVars :: "\n\n" :\\: blocks :\\: "#include \"TPCC.h\"\n" :\\: traits :/: Document.nest(2, mainPrg) :/: codeGen.footer)
    file.close()
  }
}