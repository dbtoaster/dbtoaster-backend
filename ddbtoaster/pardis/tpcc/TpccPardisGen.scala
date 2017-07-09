package sc.tpcc

import java.io.{File, PrintWriter}
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
import ddbt.transformer.Index

import scala.util.parsing.json.JSON


/**
  * Created by sachin on 14/09/16.
  */
trait TpccPardisGen {
  def header: String


  val infoFile = new File(s"../runtime/stats/${if (Optimizer.infoFileName == "") "default" else Optimizer.infoFileName}.json")
  val infoFilePath = infoFile.getAbsolutePath
  var StoreArrayLengths = Map[String, String]()
  var idxSymNames: List[String] = null
  if (Optimizer.initialStoreSize) {
    if (infoFile.exists()) {
      System.err.println(s"Loading runtime info from ${infoFilePath}")
      val txt = new java.util.Scanner(infoFile).useDelimiter("\\Z").next()
      val allinfo: Map[String, _] = JSON.parseFull(txt).get.asInstanceOf[Map[String, _]]
      StoreArrayLengths = allinfo.map(t => t._1 -> t._2.asInstanceOf[List[Map[String, String]]].map(_.getOrElse("OptArrayLength", "0")).map(_.toInt).max.toString)
    } else {
      System.err.println("Runtime info file missing!!  Using default initial sizes")
    }
  }
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
      |import math.Ordering.{String => _}
      |import scala.collection.mutable.{ArrayBuffer,Set}
      |import java.util.Date
      | """.stripMargin


  override val file: PrintWriter = new PrintWriter(s"$genDir/TpccGenSC.scala")

  implicit def toPath(filename: String) = get(filename)

  if (Optimizer.analyzeEntry) {
    if (Optimizer.secondaryIndex) {
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
    var codestr = Document.nest(2, codeGen.blockToDocumentNoBraces(optTP.initBlock)).toString
    var i = codestr.lastIndexOf("1")
    val allstores = optTP.globalVars.map(_.name).mkDocument(", ")
    val executor =
      s"""class SCExecutor {
          |  implicit object StringNoCase extends Ordering[String]{
          |   override def compare(x: String, y: String): Int = x.compareToIgnoreCase(y)
          |  }
          |
          |  class DoubleExtra(var d: Double) {
          |    def toSB : StringBuilder = {
          |      var i = d.toInt
          |      val sb = new StringBuilder(15)
          |      sb.append(i); sb.append('.')
          |      val len = sb.length
          |      d = ((d - i) * 1000000); i=d.toInt ; sb.append(i)
          |      var x = sb.length - len
          |      while(x < 6) {
          |       sb.append('0');
          |        x+=1;
          |       }
          |      sb
          |    }
          |  }
          |
          """.stripMargin + codestr.substring(0, i) + "\n" +
        (if (Optimizer.initialStoreSize && !StoreArrayLengths.isEmpty) {
          val tbls = StoreArrayLengths.keys.toList.groupBy(_.split("Idx")(0)).map(t => t._1 -> t._2.map(StoreArrayLengths.getOrElse(_, "1")))
          tbls.map(t => doc"  ${t._1}.setInitialSizes(List(${t._2.mkString(",")}))").mkString("\n") + "\n"
        }
        else "") +
        s"""
           |  val newOrderTxInst = new NewOrderTx($allstores)
           |  val paymentTxInst = new PaymentTx($allstores)
           |  val orderStatusTxInst = new OrderStatusTx($allstores)
           |  val deliveryTxInst = new DeliveryTx($allstores)
           |  val stockLevelTxInst = new StockLevelTx($allstores)
           |
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
    //    val txns = new PrintWriter("TpccTxns.scala")
    optTP.codeBlocks.foreach { case (className, args: List[Sym[_]], body) => {
      val argsWithTypes = optTP.globalVars.map(m => doc"$m : Store[${storeType(m).tp}]").mkDocument(", ")
      val genCode = doc"  class $className($argsWithTypes) extends ((${args.map(_.tp).mkDocument(", ")}) => ${body.typeT} ) {" :/:
        doc"    def apply(${args.map(s => doc"$s : ${s.tp}").mkDocument(", ")}) = "
      val cgDoc = Document.nest(4, codeGen.blockToDocument(body))
      file.println(genCode + cgDoc.toString + "\n  }")
      //      txns.println(genCode + cgDoc.toString + "\n  }")
    }
    }
    //    txns.close()
    file.println("\n}")

    //    new TpccCompiler(Context).compile(codeBlock, "test/gen/tpcc")
    file.close()
  }
}

class TpccPardisParallelCppGen(val IR: StoreDSL) extends TpccPardisGen {

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
       |#include <mmap.hpp>
       |#include <valgrind/callgrind.h>
       |#include <iomanip>
       |#include <fstream>
       |#include <locale>
       |
       |#include <thread>
       |#include <sched.h>
       |#include <pthread.h>
       |
       |${if (Optimizer.profileBlocks || Optimizer.profileStoreOperations) "#define EXEC_PROFILE 1" else ""}
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
       |struct Partition;
       |const int numThreads = 3;
       |std::thread workers[numThreads];
       |volatile bool isReady[numThreads];
       |volatile bool startExecution, hasFinished;
       |
       |#define CORE_FOR_W(x) (x%numThreads)
       |
       |#define setAffinity(thread_id)\\
       |    cpu_set_t cpuset;\\
       |    CPU_ZERO(&cpuset);\\
       |    CPU_SET(thread_id+1, &cpuset);\\
       |    auto s = sched_setaffinity(0, sizeof (cpu_set_t), &cpuset);\\
       |    if (s != 0)\\
       |        throw std::runtime_error("Cannot set affinity");
       |
       |#define setSched(type)\\
       |    sched_param param;\\
       |    param.__sched_priority =  sched_get_priority_max(type);\\
       |    s = sched_setscheduler(0, type, &param);\\
       |    if (s != 0)\\
       |        cerr << "Cannot set scheduler" << endl;
       |
       |uint failedOS = 0;
       |uint failedDel = 0;
       |uint failedNO = 0;
       |
       |const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
       |const size_t itemTblSize = 100000 * 1.5;
       |const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
       |const size_t customerTblSize = districtTblSize * 3000;
       |const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
       |const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
       |const size_t orderLineTblSize = orderTblSize * 12;
       |const size_t stockTblSize = numWare * itemTblSize;
       |const size_t historyTblSize = orderTblSize;
       |
       |${genInitArrayLengths}
       |
       |const size_t warehouseTblPoolSizes[] = {8, 0};
       |const size_t itemTblPoolSizes[] = {65536*2, 0};
       |const size_t districtTblPoolSizes[] = {16, 0};
       |const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
       |const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
       |const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
       |const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
       |const size_t stockTblPoolSizes[] = {65536*2, 0};
       |const size_t historyTblPoolSizes[] = {262144*2, 65536};
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

    val (stTypdef, stDecl, stInit) = optTP.globalVars.map(s => {
      def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"

      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      val idx3 = idx2(s).filter(_._2 != "INone")
      val idxTypes = idx3.map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
      val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

      val storeTypeDef = doc"typedef MultiHashMap<${entryTp}, char," :: idxTypes.map(t => idxTypeName(t._2)).mkDocument(", ") :: doc"> ${s.name}StoreType;"

      val storeDecl = s.name :: "StoreType  " :: s.name :: ";"
      val idxDecl = idx3.zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1};").mkDocument("\n")

      val storeinit = s.name :: (if (Optimizer.initialStoreSize) doc"(${s.name}ArrayLengths, ${s.name}PoolSizes)" else doc"()") :: ", "
      val idxInit = idx3.zipWithIndex.map(t => doc"${t._1._1}(*(${idxTypeName(t._2)} *)${s.name}.index[${t._2}])").mkDocument(", ")
      (idxTypeDefs :\\: storeTypeDef :: "\n", storeDecl :\\: idxDecl :: "\n", storeinit :: idxInit)
    }).reduce((a, b) => (a._1 :\\: b._1, a._2 :\\: b._2, a._3 :: ", " :\\: b._3))

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
        val copyFn = doc"FORCE_INLINE ${tag.typeName}* copy() const {  ${tag.typeName}* ptr = (${tag.typeName}*) malloc(sizeof(${tag.typeName})); new(ptr) ${tag.typeName}(" :: fields.map(x => {
          //          if (x.tpe == StringType)
          //            doc"*${x.name}.copy()"
          //          else
          doc"${x.name}"
        }).mkDocument(", ") :: ");  return ptr;}"
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
    def argsDoc(args: List[Sym[_]]) = args.map(t => doc"${t.tp} ${t}").mkDocument(", ") //SBJ: These args are both input/output. Should not be made const
    //    def blockTofunction(x :(String, List[ExpressionSymbol[_]], PardisBlock[T])) = {
    //      (Sym.freshNamed(x._1)(x._3.typeT, IR), x._2, x._3)
    //    }
    //    optTP.codeBlocks.foreach(x => codeGen.functionsList += (blockTofunction(x)))
    def stPrf(n: String) = if (Optimizer.profileBlocks) doc"\nauto start$n = Now;" else doc""
    def endPrf(id: String) = if (Optimizer.profileBlocks) doc"\nauto end$id = Now;" :/:
      doc"""if(durations.find("$id") == durations.end()) {""" :/:
      doc"""  durations["$id"] = DurationNS(end$id - start$id);""" :/:
      doc"""  counters["$id"] = 1;""" :/:
      doc"} else  {" :/:
      doc"""  durations["$id"] += DurationNS(end$id- start$id);""" :/:
      doc"""  counters["$id"]++;""" :/:
      doc"}"
    else doc""

    val blocks = optTP.codeBlocks.map(x => doc"FORCE_INLINE void ${x._1}(${argsDoc(x._2)}) {" ::
      stPrf(x._1) :: Document.nest(2, codeGen.blockToDocument(x._3)) :/: "  clearTempMem();" :: endPrf(x._1) :/:
      "}").mkDocument("\n")

    idxSymNames = idx2.values.flatMap(l => l.filter(x => x._2 != "INone").map(_._1.name)).toList
    val getSizes = idxSymNames.map(i => doc"GET_RUN_STAT_P($i, info);").mkDocument("info << \"{\\n\";\n", "\ninfo <<\",\\n\";\n", "\ninfo << \"\\n}\\n\";")
    val threadFn =
      s"""
         |void threadFunction(uint8_t thread_id) {
         |    setAffinity(thread_id);
         |    //    setSched(SCHED_FIFO);
         |
         |    Partition& pt = partitions[thread_id];
         |    pt.partitionID = thread_id;
         |    isReady[thread_id] = true;
         |    while (!startExecution);
         |
         |    for (size_t i = 0; i < numPrograms && !hasFinished; ++i) {
         |        Program *prg = tpcc.programs[i];
         |        switch (prg->id) {
         |            case NEWORDER:
         |            {
         |                NewOrder& p = *(NewOrder *) prg;
         |                pt.NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
         |                break;
         |            }
         |            case PAYMENTBYID:
         |            {
         |                PaymentById& p = *(PaymentById *) prg;
         |                pt.PaymentTx( false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
         |                break;
         |            }
         |            case PAYMENTBYNAME:
         |            {
         |                PaymentByName& p = *(PaymentByName *) prg;
         |                pt.PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
         |                break;
         |            }
         |            case ORDERSTATUSBYID:
         |            {
         |                OrderStatusById &p = *(OrderStatusById *) prg;
         |                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
         |                break;
         |            }
         |            case ORDERSTATUSBYNAME:
         |            {
         |                OrderStatusByName &p = *(OrderStatusByName *) prg;
         |                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
         |                break;
         |            }
         |            case DELIVERY:
         |            {
         |                Delivery &p = *(Delivery *) prg;
         |                pt.DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
         |                break;
         |            }
         |            case STOCKLEVEL:
         |            {
         |                StockLevel &p = *(StockLevel *) prg;
         |                pt.StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         |                break;
         |            }
         |            default: cerr << "UNKNOWN PROGRAM TYPE" << endl;
         |
         |        }
         |    }
         |    hasFinished = true;
         |}
         |
       """.stripMargin
    def mainPrg =
      s"""
         |#ifndef NORESIZE
         |cout << "Index Resizing warning disabled" << endl;
         |#endif
         |
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
         |Timepoint startTime, endTime;
         |
         |
         |//CALLGRIND_START_INSTRUMENTATION;
         |for (uint8_t i = 0; i < numThreads; ++i) {
         |    workers[i] = std::thread(threadFunction, i);
         |}
         |bool all_ready = true;
         |//check if all worker threads are ready. Execution can be started once all threads finish startup procedure
         |while (true) {
         |    for (uint8_t i = 0; i < numThreads; ++i) {
         |        if (isReady[i] == false) {
         |            all_ready = false;
         |            break;
         |        }
         |    }
         |    if (all_ready) {
         |        startTime = Now;
         |        startExecution = true;
         |        break;
         |    }
         |
         |    all_ready = true;
         |}
         |
         |for (uint8_t i = 0; i < numThreads; ++i) {
         |    workers[i].join();
         |}
         |endTime = Now;
         |uint totalPrgsExec = 0;
         |for (int i = 0; i < numThreads; ++i) {
         |
         |    cout << "\\n Thread " << i << " : ";
         |    for (int x = 0; x < 5; ++x) {
         |        cout << partitions[i].xactCounts[x] << "  ";
         |        xactCounts[x] += partitions[i].xactCounts[x];
         |        totalPrgsExec += partitions[i].xactCounts[x];
         |    }
         |}
         |failedNO = partitions[0].failedNO; // WRONG! do max?

         |
         |cout << endl;
         |//CALLGRIND_STOP_INSTRUMENTATION;
         |//CALLGRIND_DUMP_STATS;
         |
         |auto execTime = DurationMS(endTime - startTime);
         |cout << "Failed NO (approx) = " << failedNO << endl;
         |cout << "Failed Del = " << failedDel << endl;
         |cout << "Failed OS = " << failedOS << endl;
         |cout << "Total time = " << execTime << " ms" << endl;
         |uint failedCount[] = {failedNO, 0, failedOS, failedDel / 10, 0};
         |cout << "Total transactions = " << totalPrgsExec << "   NewOrder = " << xactCounts[0] << endl;
         |cout << "TpmC = " << fixed << (xactCounts[0])* 60000.0 / execTime << endl;


         |${
        if (Optimizer.profileBlocks || Optimizer.profileStoreOperations)
          s"""
             |//counters["FailedNO"] = failedNO; counters["FailedDel"] = failedDel/10; counters["FailedOS"] = failedOS;
             |//durations["FailedNO"] = 0; durations["FailedDel"] = 0; durations["FailedOS"] = 0;
             |ExecutionProfiler::printProfileToFile();
            """.stripMargin
        else doc""
      }
         |ofstream fout("tpcc_res_cpp.csv", ios::app);
         |if(argc == 1 || atoi(argv[1]) == 1) {
         |  fout << "\\nCPP-${Optimizer.optCombination}-" << numPrograms << ",";
         |  for(int i = 0; i < 5 ; ++i)
         |     fout << xactCounts[i] - failedCount[i] << ",";
         |  fout <<",";
         | }
         |fout << execTime << ",";
         |fout.close();
         |
         |
         |ofstream info("$infoFilePath");
         |${getSizes}
         |info.close();
         |

         |#ifdef VERIFY_TPCC
         |    warehouseTblIdx0Type warehouseTblIdx0;
         |    districtTblIdx0Type districtTblIdx0;
         |    customerTblIdx0Type customerTblIdx0;
         |    orderTblIdx0Type orderTblIdx0;
         |    newOrderTblIdx0Type newOrderTblIdx0;
         |    orderLineTblIdx0Type orderLineTblIdx0;
         |    itemTblIdx0Type itemTblIdx0;
         |    stockTblIdx0Type stockTblIdx0;
         |    historyTblIdx0Type historyTblIdx0;
         |
         |    warehouseTblIdx0.idxId = 0;
         |    districtTblIdx0.idxId = 0;
         |    customerTblIdx0.idxId = 0;
         |    orderTblIdx0.idxId = 0;
         |    newOrderTblIdx0.idxId = 0;
         |    orderLineTblIdx0.idxId = 0;
         |    itemTblIdx0.idxId = 0;
         |    stockTblIdx0.idxId = 0;
         |    historyTblIdx0.idxId = 0;
         |
         |    warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
         |    districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
         |    customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
         |    orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
         |    newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
         |    orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
         |    itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
         |    stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
         |    historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
         |
         |
         |    for (int i = 0; i < numThreads; ++i) {
         |        partitions[i].warehouseTblIdx0.foreach([&](WarehouseEntry * e) {
         |                warehouseTblIdx0.add(e->copy());
         |        });
         |        partitions[i].districtTblIdx0.foreach([&](DistrictEntry * e) {
         |                districtTblIdx0.add(e->copy());
         |        });
         |        partitions[i].customerTblIdx0.foreach([&](CustomerEntry * e) {
         |            if (CORE_FOR_W(e->_3) == i) {
         |                customerTblIdx0.add(e->copy());
         |            }
         |        });
         |        partitions[i].orderTblIdx0.foreach([&](OrderEntry * e) {
         |                orderTblIdx0.add(e->copy());
         |        });
         |        partitions[i].newOrderTblIdx0.foreach([&](NewOrderEntry * e) {
         |                newOrderTblIdx0.add(e->copy());
         |        });
         |        partitions[i].orderLineTblIdx0.foreach([&](OrderLineEntry * e) {
         |                orderLineTblIdx0.add(e->copy());
         |        });
         |        partitions[0].itemTblIdx0.foreach([&](ItemEntry * e) {
         |                itemTblIdx0.add(e->copy());
         |        });
         |        partitions[i].stockTblIdx0.foreach([&](StockEntry * e) {
         |            if (CORE_FOR_W(e->_2) == i)
         |                stockTblIdx0.add(e->copy());
         |        });
         |
         |        partitions[i].historyTblIdx0.foreach([&](HistoryEntry * e) {
         |                historyTblIdx0.add(e->copy());
         |        });
         |    }
         |
         |    if (warehouseTblIdx0 == tpcc.wareRes) {
         |        cout << "Warehouse results are correct" << endl;
         |    } else {
         |        cerr << "Warehouse results INCORRECT!" << endl;
         |    }
         |    if (districtTblIdx0 == tpcc.distRes) {
         |        cout << "District results are correct" << endl;
         |    } else {
         |        cerr << "District results INCORRECT!" << endl;
         |    }
         |    if (customerTblIdx0 == tpcc.custRes) {
         |        cout << "Customer results are correct" << endl;
         |    } else {
         |        cerr << "Customer results INCORRECT!" << endl;
         |    }
         |    if (orderTblIdx0 == tpcc.ordRes) {
         |        cout << "Order results are correct" << endl;
         |    } else {
         |        cerr << "Order results INCORRECT!" << endl;
         |    }
         |    if (orderLineTblIdx0 == tpcc.ordLRes) {
         |        cout << "OrderLine results are correct" << endl;
         |    } else {
         |        cerr << "OrderLine results INCORRECT!" << endl;
         |    }
         |    if (newOrderTblIdx0 == tpcc.newOrdRes) {
         |        cout << "NewOrder results are correct" << endl;
         |    } else {
         |        cerr << "NewOrder results INCORRECT!" << endl;
         |    }
         |    if (itemTblIdx0 == tpcc.itemRes) {
         |        cout << "Item results are correct" << endl;
         |    } else {
         |        cerr << "Item results INCORRECT!" << endl;
         |    }
         |    if (stockTblIdx0 == tpcc.stockRes) {
         |        cout << "Stock results are correct" << endl;
         |    } else {
         |        cerr << "Stock results INCORRECT!" << endl;
         |    }
         |    if (historyTblIdx0 == tpcc.histRes) {
         |        cout << "History results are correct" << endl;
         |    } else {
         |        cerr << "History results INCORRECT!" << endl;
         |    }
         |
         |#endif
         |
      """.stripMargin
    val execProfile = if (Optimizer.profileBlocks || Optimizer.profileStoreOperations)
      s""" std::unordered_map<std::string, Timepoint> startTimes;
          | std::unordered_map<std::string, size_t> durations;
          | std::unordered_map<std::string, size_t> counters;""".stripMargin
    else ""
    //    val txns = new PrintWriter("TpccTxns.hpp")
    //    txns.print(blocks)
    //    txns.close()
    file.println(header :/: execProfile :/: structs :\\: structEquals :\\: entryIdxes :\\: stTypdef :\\:
      doc"struct Partition { " :\\: Document.nest(2, doc"Partition():" :\\:
      stInit :: doc"  {\n  memset(xactCounts, 0, sizeof(uint) *5); }\n" :\\:
      stDecl :\\: structVars ::
      s"""
         |
         |int partitionID;
         |uint failedNO;
         |uint xactCounts[5];
       """.stripMargin :\\: blocks) :\\:
      "};" :\\:
      "Partition partitions[numThreads];" :\\:
      "#define PARTITIONED 1" :\\:
      "#include \"TPCC.h\"\n" :\\:
      "TPCCDataGen tpcc;" :\\:
      threadFn :\\:
      traits :/: Document.nest(2, mainPrg) :/: "}")
    file.close()
  }
}

class TpccPardisCppGen(val IR: StoreDSL) extends TpccPardisGen {

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
       |#include <mmap.hpp>
       |#include <valgrind/callgrind.h>
       |#include <iomanip>
       |#include <fstream>
       |#include <locale>
       |
       |#include "TransactionManager.h"
       |
       |${if (Optimizer.profileBlocks || Optimizer.profileStoreOperations) "#define EXEC_PROFILE 1" else ""}
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
       |uint failedOS = 0;
       |uint failedDel = 0;
       |uint failedNO = 0;
       |
       |const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
       |const size_t itemTblSize = 100000 * 1.5;
       |const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
       |const size_t customerTblSize = districtTblSize * 3000;
       |const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
       |const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
       |const size_t orderLineTblSize = orderTblSize * 12;
       |const size_t stockTblSize = numWare * itemTblSize;
       |const size_t historyTblSize = orderTblSize;
       |
       |${genInitArrayLengths}
       |
       |const size_t warehouseTblPoolSizes[] = {8, 0};
       |const size_t itemTblPoolSizes[] = {65536*2, 0};
       |const size_t districtTblPoolSizes[] = {16, 0};
       |const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
       |const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
       |const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
       |const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
       |const size_t stockTblPoolSizes[] = {65536*2, 0};
       |const size_t historyTblPoolSizes[] = {262144*2, 65536};
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
        case "IHash" if idx._3 => doc"CuckooIndex<$entryTp, ${idx._5}>"
        case "IHash" if !idx._3 => doc"ConcurrentCuckooSecondaryIndex<$entryTp, ${idx._5}>"
        case "IHash" => doc"HashIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
        case "IDirect" => doc"ConcurrentArrayIndex<$entryTp, ${idx._5}, ${unit(idx._4)}>"
        case "ISliceHeapMax" => val idx2 = allIdxs(idx._4); doc"MaxHeapIndex<$entryTp, ${idx2._5}, ${idx._5}>"
        case "ISliceHeapMin" => val idx2 = allIdxs(idx._4); doc"MinHeapIndex<$entryTp, ${idx2._5}, ${idx._5}>"
        case "ISlicedHeapMed" => val idx2 = allIdxs(idx._4); doc"MedHeapIndex<$entryTp, ${idx2._5}, ${idx._5}>"
        case "IList" => doc"ListIndex<$entryTp, char, ${idx._5}, ${unit(idx._3)}>"
      }

    }

    val (stTypdef, stDecl, stInit1, stRefs, stInit2) = optTP.globalVars.map(s => {
      def idxTypeName(i: Int) = s.name :: "Idx" :: i :: "Type"

      val entryTp = s.tp.asInstanceOf[StoreType[_]].typeE
      val idx3 = idx2(s).filter(_._2 != "INone")
      val idxTypes = idx3.map(idxToDoc(_, entryTp, idx2(s))).zipWithIndex
      val idxTypeDefs = idxTypes.map(t => doc"typedef ${t._1} ${idxTypeName(t._2)};").mkDocument("\n")

      val storeTypeDef = doc"typedef MultiHashMapMV<${entryTp}," :: idxTypes.map(t => idxTypeName(t._2)).mkDocument(", ") :: doc"> ${s.name}StoreType;"

      val storeDecl = s.name :: "StoreType  " :: s.name :: ";  "
      val storeRef = s.name :: "StoreType& " :: s.name :: ";  "

      val idxDecl = idx3.zipWithIndex.map(t => doc"${idxTypeName(t._2)}& ${t._1._1};").mkDocument("  ")

      val storeinit = s.name :: (if (Optimizer.initialStoreSize) doc"(${s.name}ArrayLengths, ${s.name}PoolSizes)" else doc"()") :: ", "
      val storeRefInit = s.name :: "(t." :: s.name :: "), "

      val idxInit = idx3.zipWithIndex.map(t => doc"${t._1._1}(*(${idxTypeName(t._2)} *)${s.name}.index[${t._2}])").mkDocument(", ")
      val idxRefInit = idx3.zipWithIndex.map(t=> doc"${t._1._1}(t.${t._1._1})").mkDocument(", ")

      (idxTypeDefs :\\: storeTypeDef :: "\n", storeDecl :: idxDecl , storeinit :: idxInit , storeRef :: idxDecl , storeRefInit :: idxRefInit)
    }).reduce((a, b) => (a._1 :\\: b._1, a._2 :\\: b._2, a._3 :: ", " :/: b._3, a._4 :\\: b._4, a._5 ::", ":\\: b._5))

    val entryIdxes = optTP.entryIdxDefs.map(codeGen.nodeToDocument).mkDocument("\n")
    def structToDoc(s: PardisStructDef[_]) = s match {
      case PardisStructDef(tag, fields, methods) =>
        val fieldsDoc = fields.map(x => doc"${x.tpe} ${x.name};").mkDocument("  ") ::
          doc"  bool isInvalid;"
//        doc"  ${tag.typeName} *prv;  ${tag.typeName} *nxt; void* backPtrs[${fields.size}];"
        val constructor = doc"${tag.typeName}() :" :: fields.map(x => {
          if (x.tpe == StringType)
            doc"${x.name}()"
          else doc"${x.name}(${nullValue(x.tpe)})"
        }).mkDocument(", ") ::
          ", isInvalid(false){}"
//          ", prv(nullptr), nxt(nullptr) {}"
        val constructorWithArgs = doc"${tag.typeName}(" :: fields.map(x => doc"const ${x.tpe}& ${x.name}").mkDocument(", ") :: ") : " :: fields.map(x => doc"${x.name}(${x.name})").mkDocument(", ") ::
          ", isInvalid(false){}"
//          ", prv(nullptr), nxt(nullptr) {}"
        val copyFn = doc"FORCE_INLINE ${tag.typeName}* copy() const {  ${tag.typeName}* ptr = (${tag.typeName}*) malloc(sizeof(${tag.typeName})); new(ptr) ${tag.typeName}(" :: fields.map(x => {
          //          if (x.tpe == StringType)
          //            doc"*${x.name}.copy()"
          //          else
          doc"${x.name}"
        }).mkDocument(", ") :: ");  return ptr;}"
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
      doc"bool operator== (const $sname& o1, const $sname& o2) {" :\\: Document.nest(2,
        "if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;" :\\:
          "else return " :: equals :: ";") :\\: "}"
    }).mkDocument("\n")

    val traits = doc"/* TRAITS STARTING */" :/: codeGen.getTraitSignature :/: doc" /* TRAITS ENDING   */"
    def argsDoc(args: List[Sym[_]]) = args.map(t => doc"${t.tp} ${t}").mkDocument(", ") //SBJ: These args are both input/output. Should not be made const
    //    def blockTofunction(x :(String, List[ExpressionSymbol[_]], PardisBlock[T])) = {
    //      (Sym.freshNamed(x._1)(x._3.typeT, IR), x._2, x._3)
    //    }
    //    optTP.codeBlocks.foreach(x => codeGen.functionsList += (blockTofunction(x)))
    def stPrf(n: String) = if (Optimizer.profileBlocks) doc"\nauto start$n = Now;" else doc""
    def endPrf(id: String) = if (Optimizer.profileBlocks) doc"\nauto end$id = Now;" :/:
      doc"""if(durations.find("$id") == durations.end()) {""" :/:
      doc"""  durations["$id"] = DurationNS(end$id - start$id);""" :/:
      doc"""  counters["$id"] = 1;""" :/:
      doc"} else  {" :/:
      doc"""  durations["$id"] += DurationNS(end$id- start$id);""" :/:
      doc"""  counters["$id"]++;""" :/:
      doc"}"
    else doc""

    val blocks = optTP.codeBlocks.map(x => doc"FORCE_INLINE TransactionReturnStatus ${x._1}(Transaction& xact, ${argsDoc(x._2)}) {" ::
      stPrf(x._1) :: Document.nest(2, codeGen.blockToDocument(x._3)) :/: "  clearTempMem();" :: endPrf(x._1) :/: "  return SUCCESS;" :/:
      "}").mkDocument("\n\n")

    idxSymNames = idx2.values.flatMap(l => l.filter(x => x._2 != "INone").map(_._1.name)).toList
    val getSizes = idxSymNames.map(i => doc"GET_RUN_STAT(orig.$i, info);").mkDocument("info << \"{\\n\";\n", "\ninfo <<\",\\n\";\n", "\ninfo << \"\\n}\\n\";")
    def mainPrg =
      s"""
         |setAffinity(-1);
         |#ifndef NORESIZE
         |cout << "Index Resizing warning disabled" << endl;
         |#endif
         |
         |cout  << "NumThreads = " << numThreads << endl;
         |
         |tpcc.loadPrograms();
         |
         |Transaction t0;
         |xactManager.begin(t0, 0);
         |tpcc.loadWare(t0);
         |tpcc.loadDist(t0);
         |tpcc.loadCust(t0);
         |tpcc.loadItem(t0);
         |tpcc.loadNewOrd(t0);
         |tpcc.loadOrders(t0);
         |tpcc.loadOrdLine(t0);
         |tpcc.loadHist(t0);
         |tpcc.loadStocks(t0);
         |xactManager.commit(t0, 0);
         |cout.imbue(std::locale(""));
         |
         |memset(xactCounts, 0, 5 * sizeof(uint));
         |memset(xactManager.activeXactStartTS, 0xff, sizeof(xactManager.activeXactStartTS[0]) * numThreads);
         |
         |Timepoint startTime, endTime;
         |std::thread workers[numThreads];
         |
         |for (uint8_t i = 0; i < numThreads; ++i) {
         |    workers[i] = std::thread(threadFunction, i, &orig);
         |}
         |bool all_ready = true;
         |//check if all worker threads are ready. Execution can be started once all threads finish startup procedure
         |while (true) {
         |    for (uint8_t i = 0; i < numThreads; ++i) {
         |        if (isReady[i] == false) {
         |            all_ready = false;
         |            break;
         |        }
         |    }
         |    if (all_ready) {
         |        startTime = Now;
         |        startExecution = true;
         |        break;
         |    }
         |    all_ready = true;
         |}
         |
         |for (uint8_t i = 0; i < numThreads; ++i) {
         |    workers[i].join();
         |}
         |endTime = Now;
         |auto execTime = DurationMS(endTime - startTime);
         |
         |cout << "Failed NO = " << failedNO << endl;
         |cout << "Failed Del = " << failedDel << endl;
         |cout << "Failed OS = " << failedOS << endl;
         |cout << "Total time = " << execTime << " ms" << endl;
         |cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  xactCounts[0]  << endl;
         |cout << "TpmC = " << fixed <<  (xactCounts[0])* 60000.0/execTime << endl;
         |${
        if (Optimizer.profileBlocks || Optimizer.profileStoreOperations)
          s"""
             |//counters["FailedNO"] = failedNO; counters["FailedDel"] = failedDel/10; counters["FailedOS"] = failedOS;
             |//durations["FailedNO"] = 0; durations["FailedDel"] = 0; durations["FailedOS"] = 0;
             |ExecutionProfiler::printProfileToFile();
            """.stripMargin
        else doc""
      }
         |ofstream fout("tpcc_res_cpp.csv", ios::app);
         |if(argc == 1 || atoi(argv[1]) == 1) {
         |  fout << "\\nCPP-${Optimizer.optCombination}-" << numPrograms << ",";
         |  for(int i = 0; i < 5 ; ++i)
         |     fout << xactCounts[i] << ",";
         |  fout <<",";
         | }
         |fout << execTime << ",";
         |fout.close();
         |
         |/*
         |ofstream info("$infoFilePath");
         |${getSizes}
         |info.close();
         |*/
         |
         |#ifdef VERIFY_CONC
         |ThreadLocal ver(-1, res);
         |std::sort(tpcc.programs, tpcc.programs + numPrograms, [](const Program* a, const Program * b) {
         |  return a->xact.commitTS < b->xact.commitTS;
         |});
         |xactManager.committedXactsTail = nullptr;
         |for (uint i = 0; i < numPrograms; ++i) {
         |  Program* p = tpcc.programs[i];
         |  if (p->xact.commitTS == initCommitTS)
         |    break;
         |  p->xact.reset();
         |  TransactionReturnStatus st;
         |  xactManager.begin(p->xact, 0);
         |  st = ver.runProgram(p);
         |  assert(st == SUCCESS);
         |  bool st2 = xactManager.validateAndCommit(p->xact, 0);
         |  assert(st2);
         |}
         |
         |if (orig.warehouseTblIdx0 == res.warehouseTblIdx0) {
         |  cout << "Warehouse results are same as serial version" << endl;
         |} else {
         |  cerr << "Warehouse results INCORRECT!" << endl;
         |}
         |if (orig.districtTblIdx0 == res.districtTblIdx0) {
         |  cout << "District results are same as serial version" << endl;
         |} else {
         |  cerr << "District results INCORRECT!" << endl;
         |}
         |if (orig.customerTblIdx0 == res.customerTblIdx0) {
         |  cout << "Customer results are same as serial version" << endl;
         |} else {
         |  cerr << "Customer results INCORRECT!" << endl;
         |}
         |if (orig.orderTblIdx0 == res.orderTblIdx0) {
         |  cout << "Order results are same as serial version" << endl;
         |} else {
         |  cerr << "Order results INCORRECT!" << endl;
         |}
         |if (orig.orderLineTblIdx0 == res.orderLineTblIdx0) {
         |  cout << "OrderLine results are same as serial version" << endl;
         |} else {
         |  cerr << "OrderLine results INCORRECT!" << endl;
         |}
         |if (orig.newOrderTblIdx0 == res.newOrderTblIdx0) {
         |  cout << "NewOrder results are same as serial version" << endl;
         |} else {
         |  cerr << "NewOrder results INCORRECT!" << endl;
         |}
         |if (orig.itemTblIdx0 == res.itemTblIdx0) {
         |  cout << "Item results are same as serial version" << endl;
         |} else {
         |  cerr << "Item results INCORRECT!" << endl;
         |}
         |if (orig.stockTblIdx0 == res.stockTblIdx0) {
         |  cout << "Stock results are same as serial version" << endl;
         |} else {
         |  cerr << "Stock results INCORRECT!" << endl;
         |}
         |if (orig.historyTblIdx0 == res.historyTblIdx0) {
         |  cout << "History results are same as serial version" << endl;
         |} else {
         |  cerr << "History results INCORRECT!" << endl;
         |}
         |#endif
         |#ifdef VERIFY_TPCC
         |/*
         |    warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
         |    districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
         |    customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
         |    orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
         |    newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
         |    orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
         |    itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
         |    stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
         |    historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
         |*/
         |    if (orig.warehouseTblIdx0 == tpcc.wareRes) {
         |        cout << "Warehouse results are correct" << endl;
         |    } else {
         |        cerr << "Warehouse results INCORRECT!" << endl;
         |    }
         |    if (orig.districtTblIdx0 == tpcc.distRes) {
         |        cout << "District results are correct" << endl;
         |    } else {
         |        cerr << "District results INCORRECT!" << endl;
         |    }
         |    if (orig.customerTblIdx0 == tpcc.custRes) {
         |        cout << "Customer results are correct" << endl;
         |    } else {
         |        cerr << "Customer results INCORRECT!" << endl;
         |    }
         |    if (orig.orderTblIdx0 == tpcc.ordRes) {
         |        cout << "Order results are correct" << endl;
         |    } else {
         |        cerr << "Order results INCORRECT!" << endl;
         |    }
         |    if (orig.orderLineTblIdx0 == tpcc.ordLRes) {
         |        cout << "OrderLine results are correct" << endl;
         |    } else {
         |        cerr << "OrderLine results INCORRECT!" << endl;
         |    }
         |    if (orig.newOrderTblIdx0 == tpcc.newOrdRes) {
         |        cout << "NewOrder results are correct" << endl;
         |    } else {
         |        cerr << "NewOrder results INCORRECT!" << endl;
         |    }
         |    if (orig.itemTblIdx0 == tpcc.itemRes) {
         |        cout << "Item results are correct" << endl;
         |    } else {
         |        cerr << "Item results INCORRECT!" << endl;
         |    }
         |    if (orig.stockTblIdx0 == tpcc.stockRes) {
         |        cout << "Stock results are correct" << endl;
         |    } else {
         |        cerr << "Stock results INCORRECT!" << endl;
         |    }
         |    if (orig.historyTblIdx0 == tpcc.histRes) {
         |        cout << "History results are correct" << endl;
         |    } else {
         |        cerr << "History results INCORRECT!" << endl;
         |    }
         |
         |#endif
         |
      """.stripMargin
    val execProfile = if (Optimizer.profileBlocks || Optimizer.profileStoreOperations)
      s""" std::unordered_map<std::string, Timepoint> startTimes;
          | std::unordered_map<std::string, size_t> durations;
          | std::unordered_map<std::string, size_t> counters;""".stripMargin
    else ""
    //    val txns = new PrintWriter("TpccTxns.hpp")
    //    txns.print(blocks)
    //    txns.close()
    val tm =
      """
        |TransactionManager xactManager;
        |TransactionManager& Transaction::tm(xactManager);
        |uint xactCounts[5];
        |uint8_t prgId7to5[] = {0, 1, 1, 2, 2, 3, 4};
        |
        |volatile bool isReady[numThreads];
        |volatile bool startExecution, hasFinished;
        |
        |
        |#define CONCURRENT 1
        |TPCC_Data orig;
        |#ifdef VERIFY_CONC
        |   TPCC_Data res;
        |#endif
        | """.stripMargin

    val runPrgFn =
      """TPCCDataGen tpcc;
        |
        |TransactionReturnStatus ThreadLocal::runProgram(Program* prg) {
        |  TransactionReturnStatus ret = SUCCESS;
        |  switch (prg->id) {
        |    case NEWORDER:
        |    {
        |      NewOrder& p = *(NewOrder *) prg;
        |      ret = NewOrderTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
        |      break;
        |    }
        |    case PAYMENTBYID:
        |    {
        |      PaymentById& p = *(PaymentById *) prg;
        |      ret = PaymentTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
        |      break;
        |    }
        |    case PAYMENTBYNAME:
        |    {
        |      PaymentByName& p = *(PaymentByName *) prg;
        |      ret = PaymentTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
        |      break;
        |    }
        |    case ORDERSTATUSBYID:
        |    {
        |      OrderStatusById &p = *(OrderStatusById *) prg;
        |      ret = OrderStatusTx(prg->xact, false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
        |      break;
        |    }
        |    case ORDERSTATUSBYNAME:
        |    {
        |      OrderStatusByName &p = *(OrderStatusByName *) prg;
        |      ret = OrderStatusTx(prg->xact, false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
        |      break;
        |    }
        |    case DELIVERY:
        |    {
        |      Delivery &p = *(Delivery *) prg;
        |      ret = DeliveryTx(prg->xact, false, p.datetime, p.w_id, p.o_carrier_id);
        |      break;
        |    }
        |    case STOCKLEVEL:
        |    {
        |      StockLevel &p = *(StockLevel *) prg;
        |      ret = StockLevelTx(prg->xact, false, -1, -1, p.w_id, p.d_id, p.threshold);
        |      break;
        |    }
        |    default: cerr << "UNKNOWN PROGRAM TYPE" << endl;
        |
        |  }
        |  return ret;
        |}
      """.stripMargin
    val threadFn =
      s"""std::atomic<uint> PC(0);
         |void threadFunction(uint8_t thread_id, TPCC_Data* data) {
         |    setAffinity(thread_id);
         |    //    setSched(SCHED_FIFO);
         |
         |  ThreadLocal tl(thread_id, *data);
         |  isReady[thread_id] = true;
         |  uint pid = PC++;
         |  Program* p;
         |  TransactionReturnStatus st;
         |  while (!startExecution);
         |  const uint failedProgramSize = 32;
         |  Program * failedPrograms[failedProgramSize];
         |  uint head = 0, tail = 0;
         |  bool full = false;
         |  p = tpcc.programs[pid];
         |  while (!hasFinished) {
         |
         |    xactManager.begin(p->xact, thread_id);
         |
         |    st = tl.runProgram(p);
         |
         |    if (st != SUCCESS) {
         |      xactManager.rollback(p->xact, thread_id);
         |      if (!full && p->xact.failedBecauseOf != nullptr) {
         |        failedPrograms[tail++] = p;
         |        if (tail == failedProgramSize)
         |          tail = 0;
         |        if (head == tail)
         |          full = true;
         |        pid = PC++;
         |        if (pid >= numPrograms)
         |          break;
         |        p = tpcc.programs[pid];
         |      }
         |    } else {
         |      if (xactManager.validateAndCommit(p->xact, thread_id)) {   //rollback happens inside function if it fails
         |        xactCounts[prgId7to5[p->id]]++;
         |        if (head != tail || full) {
         |          p = failedPrograms[head];
         |          if (p->xact.failedBecauseOf->commitTS != initCommitTS) {
         |            head++;
         |            full = false;
         |            if (head == failedProgramSize)
         |              head = 0;
         |            continue;
         |          }
         |        }
         |        pid = PC++;
         |        if(pid >= numPrograms)
         |          break;
         |        p = tpcc.programs[pid];
         |      }
         |    }
         |  }
         |  hasFinished = true;
         |}
         |
       """.stripMargin
    val tpccData = doc"struct TPCC_Data {" :\\: Document.nest(2, doc"TPCC_Data(): " :\\: stInit1 :: "{}\n" :\\: stDecl) :\\: "};"
    val threadLocal = doc"struct ThreadLocal { " :\\: Document.nest(2,
    "\nuint8_t threadId;\nuint xactCounts[5];\n" :\\: doc"ThreadLocal(uint8_t tid, TPCC_Data& t): threadId(tid), "
      :\\: stInit2 :: "{\n   memset(xactCounts, 0, sizeof(uint)*5);\n}\n" :\\: stRefs :: "\n" :\\: structVars :: "\n"
      :\\: blocks :\\: "\n TransactionReturnStatus runProgram(Program* prg);") :\\: "};"
    //disabled entryidx temporarily
    val entryidx2 =
      """#if USING_GENERIC_ENTRY
        |struct GenericOps_3214 {  //OL 0
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(1).data.i;
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    int x4 = (x3 << 4) + e.map.at(4).data.i;
        |    return x4;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1) || e1.map.at(4) != e2.map.at(4))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_23 { //NO 1
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(3).data.i;
        |    int x2 = (x1 << 4) + e.map.at(2).data.i;
        |    return x2;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_321 { //C0  O0   NO0
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(1).data.i;
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_236 { //C 1
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = HASH(e.map.at(6).data.s);
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(6) != e2.map.at(6))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_123 { //OL1
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(1).data.i;
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_12345678 { // H0
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    unsigned int h = 0;
        |    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(5)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(6)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(7)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    h = h ^ (HASH(e.map.at(8)) + 0x9e3779b9 + (h<<6) + (h>>2));
        |    return h;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4) || e1.map.at(5) != e2.map.at(5) || e1.map.at(6) != e2.map.at(6) || e1.map.at(7) != e2.map.at(7) || e1.map.at(8) != e2.map.at(8))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericOps_234 {  //O 1
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(4).data.i;
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4))
        |       return 1;
        |    return 0;
        |  }
        |};
        |struct GenericCmp_236_4 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = HASH(e.map.at(6));
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    const Any &r1 = e1.map.at(4);
        |    const Any &r2 = e2.map.at(4);
        |    if (r1 == r2)
        |      return 0;
        |    else if( r1 < r2)
        |      return -1;
        |    else
        |      return 1;
        |
        |  }
        |};
        |struct GenericCmp_23_1 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.getInt(3);
        |    int x2 = (x1 << 4) + e.getInt(2);
        |    return x2;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    const Any &r1 = e1.map.at(1);
        |    const Any &r2 = e2.map.at(1);
        |    if (r1 == r2)
        |      return 0;
        |    else if( r1 < r2)
        |      return -1;
        |    else
        |      return 1;
        |
        |  }
        |};
        |struct GenericCmp_234_1 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    int x1 = e.map.at(4).data.i;
        |    int x2 = (x1 << 2) + e.map.at(3).data.i;
        |    int x3 = (x2 << 4) + e.map.at(2).data.i;
        |    return x3;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
        |    const Any &r1 = e1.map.at(1);
        |    const Any &r2 = e2.map.at(1);
        |    if (r1 == r2)
        |      return 0;
        |    else if( r1 < r2)
        |      return -1;
        |    else
        |      return 1;
        |
        |  }
        |};
        |struct GenericFixedRange_1f1t100002 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    return e.getInt(1)-1;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
        |};
        |struct GenericFixedRange_3f1t6_2f1t11_1f1t3001 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    return ((e.getInt(3)-1) * 10 + e.getInt(2)-1)*3000 + e.getInt(1)-1;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
        |};
        |struct GenericFixedRange_2f1t6_1f1t100001 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    return (e.getInt(2)-1)* 100000 + e.getInt(1)-1;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
        |};
        |struct GenericFixedRange_1f1t6 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e)
        |    return  e.getInt(1) - 1;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
        |};
        |struct GenericFixedRange_2f1t6_1f1t11 {
        |  FORCE_INLINE static size_t hash(const GenericEntry& e) {
        |    return (e.getInt(2)-1) * 10 + e.getInt(1)-1;;
        |  }
        |  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
        |};
        |#else
        |struct SEntry8_IIIITIIB_Idx234 {  // O 1
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3468)  {
        |    int x1 = x3468._4;
        |    int x2 = (x1 << 2) + x3468._3;
        |    int x3 = (x2 << 4) + x3468._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3502, const struct SEntry8_IIIITIIB& x3503) {
        |    int x3504 = 0;
        |    if(((x3502._2)==((x3503._2)))) {
        |      if(((x3502._3)==((x3503._3)))) {
        |        if(((x3502._4)==((x3503._4)))) {
        |          x3504 = 0;
        |        } else {
        |          x3504 = 1;
        |        };
        |      } else {
        |        x3504 = 1;
        |      };
        |    } else {
        |      x3504 = 1;
        |    };
        |    int x3521 = x3504;
        |    return x3521;
        |  }
        |};
        | struct SEntry10_IIIIIITIDS_Idx3214 { // OL 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3576)  {
        |    int x1 = x3576._1;
        |    int x2 = (x1 << 2) + x3576._3;
        |    int x3 = (x2 << 4) + x3576._2;
        |    int x4 = (x3 << 4) + x3576._4;
        |    return x4;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3620, const struct SEntry10_IIIIIITIDS& x3621) {
        |    int x3622 = 0;
        |    if(((x3620._3)==((x3621._3)))) {
        |      if(((x3620._2)==((x3621._2)))) {
        |        if(((x3620._1)==((x3621._1)))) {
        |          if(((x3620._4)==((x3621._4)))) {
        |            x3622 = 0;
        |          } else {
        |            x3622 = 1;
        |          };
        |        } else {
        |          x3622 = 1;
        |        };
        |      } else {
        |        x3622 = 1;
        |      };
        |    } else {
        |      x3622 = 1;
        |    };
        |    int x3644 = x3622;
        |    return x3644;
        |  }
        |};
        | struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321 {  //C 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3709)  {
        |    int x2 = x3709._3;
        |    int x3 = (x2 << 4) + x3709._2;
        |    int x1 = (x3 << 12) + x3709._1;
        |    return x1;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3743, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3744) {
        |    int x3745 = 0;
        |    if(((x3743._3)==((x3744._3)))) {
        |      if(((x3743._2)==((x3744._2)))) {
        |        if(((x3743._1)==((x3744._1)))) {
        |          x3745 = 0;
        |        } else {
        |          x3745 = 1;
        |        };
        |      } else {
        |        x3745 = 1;
        |      };
        |    } else {
        |      x3745 = 1;
        |    };
        |    int x3762 = x3745;
        |    return x3762;
        |  }
        |};
        | struct SEntry8_IIIIITDS_Idx12345678 {  //H Idx0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3215)  {
        |    int x3216 = 0;
        |    int x3217 = x3216;
        |    x3216 = (x3217^(((((HASH((x3215._1)))+(-1640531527))+((x3217<<(6))))+((x3217>>(2))))));
        |    int x3227 = x3216;
        |    x3216 = (x3227^(((((HASH((x3215._2)))+(-1640531527))+((x3227<<(6))))+((x3227>>(2))))));
        |    int x3237 = x3216;
        |    x3216 = (x3237^(((((HASH((x3215._3)))+(-1640531527))+((x3237<<(6))))+((x3237>>(2))))));
        |    int x3247 = x3216;
        |    x3216 = (x3247^(((((HASH((x3215._4)))+(-1640531527))+((x3247<<(6))))+((x3247>>(2))))));
        |    int x3257 = x3216;
        |    x3216 = (x3257^(((((HASH((x3215._5)))+(-1640531527))+((x3257<<(6))))+((x3257>>(2))))));
        |    int x3267 = x3216;
        |    x3216 = (x3267^(((((HASH((x3215._6)))+(-1640531527))+((x3267<<(6))))+((x3267>>(2))))));
        |    int x3277 = x3216;
        |    x3216 = (x3277^(((((HASH((x3215._7)))+(-1640531527))+((x3277<<(6))))+((x3277>>(2))))));
        |    int x3287 = x3216;
        |    x3216 = (x3287^(((((HASH((x3215._8)))+(-1640531527))+((x3287<<(6))))+((x3287>>(2))))));
        |    int x3297 = x3216;
        |    return x3297;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3299, const struct SEntry8_IIIIITDS& x3300) {
        |    int x3301 = 0;
        |    if(((x3299._1)==((x3300._1)))) {
        |      if(((x3299._2)==((x3300._2)))) {
        |        if(((x3299._3)==((x3300._3)))) {
        |          if(((x3299._4)==((x3300._4)))) {
        |            if(((x3299._5)==((x3300._5)))) {
        |              if(((x3299._6)==((x3300._6)))) {
        |                if(((x3299._7)==((x3300._7)))) {
        |                  if(((x3299._8)==((x3300._8)))) {
        |                    x3301 = 0;
        |                  } else {
        |                    x3301 = 1;
        |                  };
        |                } else {
        |                  x3301 = 1;
        |                };
        |              } else {
        |                x3301 = 1;
        |              };
        |            } else {
        |              x3301 = 1;
        |            };
        |          } else {
        |            x3301 = 1;
        |          };
        |        } else {
        |          x3301 = 1;
        |        };
        |      } else {
        |        x3301 = 1;
        |      };
        |    } else {
        |      x3301 = 1;
        |    };
        |    int x3343 = x3301;
        |    return x3343;
        |  }
        |};
        | struct SEntry8_IIIITIIB_Idx321 {  // O 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3412)  {
        |    int x1 = x3412._1;
        |    int x2 = (x1 << 2) + x3412._3;
        |    int x3 = (x2 << 4) + x3412._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3446, const struct SEntry8_IIIITIIB& x3447) {
        |    int x3448 = 0;
        |    if(((x3446._3)==((x3447._3)))) {
        |      if(((x3446._2)==((x3447._2)))) {
        |        if(((x3446._1)==((x3447._1)))) {
        |          x3448 = 0;
        |        } else {
        |          x3448 = 1;
        |        };
        |      } else {
        |        x3448 = 1;
        |      };
        |    } else {
        |      x3448 = 1;
        |    };
        |    int x3465 = x3448;
        |    return x3465;
        |  }
        |};
        | struct SEntry17_IIISSSSSSSSSSIIIS_Idx21 { // S 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3826)  {
        |    int x1 = x3826._1;
        |    int x2 = (x1 << 2) + x3826._2;
        |    return x2;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3850, const struct SEntry17_IIISSSSSSSSSSIIIS& x3851) {
        |    int x3852 = 0;
        |    if(((x3850._2)==((x3851._2)))) {
        |      if(((x3850._1)==((x3851._1)))) {
        |        x3852 = 0;
        |      } else {
        |        x3852 = 1;
        |      };
        |    } else {
        |      x3852 = 1;
        |    };
        |    int x3864 = x3852;
        |    return x3864;
        |  }
        |};
        | struct SEntry3_III_Idx23 {  //NO Idx 1
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3168)  {
        |    int x1 = x3168._3;
        |    int x2 = (x1 << 4) + x3168._2;
        |    return x2;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry3_III& x3192, const struct SEntry3_III& x3193) {
        |    int x3194 = 0;
        |    if(((x3192._2)==((x3193._2)))) {
        |      if(((x3192._3)==((x3193._3)))) {
        |        x3194 = 0;
        |      } else {
        |        x3194 = 1;
        |      };
        |    } else {
        |      x3194 = 1;
        |    };
        |    int x3206 = x3194;
        |    return x3206;
        |  }
        |};
        | struct SEntry10_IIIIIITIDS_Idx123 {  // OL 1
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3647)  {
        |    int x1 = x3647._1;
        |    int x2 = (x1 << 2) + x3647._3;
        |    int x3 = (x2 << 4) + x3647._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3681, const struct SEntry10_IIIIIITIDS& x3682) {
        |    int x3683 = 0;
        |    if(((x3681._1)==((x3682._1)))) {
        |      if(((x3681._2)==((x3682._2)))) {
        |        if(((x3681._3)==((x3682._3)))) {
        |          x3683 = 0;
        |        } else {
        |          x3683 = 1;
        |        };
        |      } else {
        |        x3683 = 1;
        |      };
        |    } else {
        |      x3683 = 1;
        |    };
        |    int x3700 = x3683;
        |    return x3700;
        |  }
        |};
        | struct SEntry3_III_Idx321 {  //NO Idx0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3112)  {
        |    int x1 = x3112._1;
        |    int x2 = (x1 << 2) + x3112._3;
        |    int x3 = (x2 << 4) + x3112._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry3_III& x3146, const struct SEntry3_III& x3147) {
        |    int x3148 = 0;
        |    if(((x3146._3)==((x3147._3)))) {
        |      if(((x3146._2)==((x3147._2)))) {
        |        if(((x3146._1)==((x3147._1)))) {
        |          x3148 = 0;
        |        } else {
        |          x3148 = 1;
        |        };
        |      } else {
        |        x3148 = 1;
        |      };
        |    } else {
        |      x3148 = 1;
        |    };
        |    int x3165 = x3148;
        |    return x3165;
        |  }
        |};
        | struct SEntry5_IISDS_Idx1 { // I 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3381)  {
        |    int x3382 = 0;
        |    int x3383 = x3382;
        |    x3382 = (x3383^(((((HASH((x3381._1)))+(-1640531527))+((x3383<<(6))))+((x3383>>(2))))));
        |    int x3393 = x3382;
        |    return x3393;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3395, const struct SEntry5_IISDS& x3396) {
        |    int x3397 = 0;
        |    if(((x3395._1)==((x3396._1)))) {
        |      x3397 = 0;
        |    } else {
        |      x3397 = 1;
        |    };
        |    int x3404 = x3397;
        |    return x3404;
        |  }
        |};
        | struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 { // C 1
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3765)  {
        |    int x1 = HASH(x3765._6);
        |    int x2 = (x1 << 2) + x3765._3;
        |    int x3 = (x2 << 4) + x3765._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3799, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3800) {
        |    int x3801 = 0;
        |    if(((x3799._2)==((x3800._2)))) {
        |      if(((x3799._3)==((x3800._3)))) {
        |        if(((x3799._6)==((x3800._6)))) {
        |          x3801 = 0;
        |        } else {
        |          x3801 = 1;
        |        };
        |      } else {
        |        x3801 = 1;
        |      };
        |    } else {
        |      x3801 = 1;
        |    };
        |    int x3818 = x3801;
        |    return x3818;
        |  }
        |};
        | struct SEntry9_ISSSSSSDD_Idx1 { // W 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3351)  {
        |    int x3352 = 0;
        |    int x3353 = x3352;
        |    x3352 = (x3353^(((((HASH((x3351._1)))+(-1640531527))+((x3353<<(6))))+((x3353>>(2))))));
        |    int x3363 = x3352;
        |    return x3363;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3365, const struct SEntry9_ISSSSSSDD& x3366) {
        |    int x3367 = 0;
        |    if(((x3365._1)==((x3366._1)))) {
        |      x3367 = 0;
        |    } else {
        |      x3367 = 1;
        |    };
        |    int x3374 = x3367;
        |    return x3374;
        |  }
        |};
        | struct SEntry11_IISSSSSSDDI_Idx21 { // D 0
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3530)  {
        |    int x3531 = 0;
        |    int x3532 = x3531;
        |    x3531 = (x3532^(((((HASH((x3530._2)))+(-1640531527))+((x3532<<(6))))+((x3532>>(2))))));
        |    int x3542 = x3531;
        |    x3531 = (x3542^(((((HASH((x3530._1)))+(-1640531527))+((x3542<<(6))))+((x3542>>(2))))));
        |    int x3552 = x3531;
        |    return x3552;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3554, const struct SEntry11_IISSSSSSDDI& x3555) {
        |    int x3556 = 0;
        |    if(((x3554._2)==((x3555._2)))) {
        |      if(((x3554._1)==((x3555._1)))) {
        |        x3556 = 0;
        |      } else {
        |        x3556 = 1;
        |      };
        |    } else {
        |      x3556 = 1;
        |    };
        |    int x3568 = x3556;
        |    return x3568;
        |  }
        |};
        |
        |struct SEntry9_ISSSSSSDD_Idx1f1t6 {
        |#define int unsigned int
        |
        |  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3379) {
        |    return (x3379._1)-1;
        |  }
        |#undef int
        |
        |  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3376, const struct SEntry9_ISSSSSSDD& x3377) {
        |    return 0;
        |  }
        |};
        |
        |struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
        |#define int unsigned int
        |
        |  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3535) {
        |    return (x3535._2-1) * 10 + x3535._1-1;
        |  }
        |#undef int
        |
        |  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3532, const struct SEntry11_IISSSSSSDDI& x3533) {
        |    return 0;
        |  }
        |};
        |
        |struct SEntry5_IISDS_Idx1f1t100002 {
        |#define int unsigned int
        |
        |  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3398) {
        |    return (x3398._1)-1;
        |  }
        |#undef int
        |
        |  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3395, const struct SEntry5_IISDS& x3396) {
        |    return 0;
        |  }
        |};
        |
        |struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
        |#define int unsigned int
        |
        |  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3693) {
        |    return ((x3693._3-1) * 10 + x3693._2-1)*3000 + x3693._1-1;
        |  }
        |#undef int
        |
        |  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3690, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3691) {
        |    return 0;
        |  }
        |};
        |
        |struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
        |#define int unsigned int
        |
        |  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3781) {
        |    return (x3781._2-1)* 100000 + x3781._1-1;
        |  }
        |#undef int
        |
        |  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3778, const struct SEntry17_IIISSSSSSSSSSIIIS& x3779) {
        |    return 0;
        |  }
        |};
        |
        |struct SEntry3_III_Idx23_1 {
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3168)  {
        |    int x1 = x3168._3;
        |    int x2 = (x1 << 4) + x3168._2;
        |    return x2;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry3_III& x3251, const struct SEntry3_III& x3252) {
        |    int x3253 = x3251._1;
        |    int x3254 = x3252._1;
        |    return ((x3253==(x3254)) ? 0 : ((x3253>(x3254)) ? 1 : -1));
        |  }
        |};
        | struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3765)  {
        |    int x1 = HASH(x3765._6);
        |    int x2 = (x1 << 2) + x3765._3;
        |    int x3 = (x2 << 4) + x3765._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3944, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3945) {
        |    int x3948 = strcmpi((x3944._4).data_, (x3945._4).data_);
        |    return ((x3948>(0)) ? 1 : ((x3948<(0)) ? -1 : 0));
        |  }
        |};
        | struct SEntry8_IIIITIIB_Idx234_1 {
        |  #define int unsigned int
        |  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3468)  {
        |    int x1 = x3468._4;
        |    int x2 = (x1 << 2) + x3468._3;
        |    int x3 = (x2 << 4) + x3468._2;
        |    return x3;
        |  }
        |  #undef int
        |  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3599, const struct SEntry8_IIIITIIB& x3600) {
        |    int x3601 = x3599._1;
        |    int x3602 = x3600._1;
        |    return ((x3601==(x3602)) ? 0 : ((x3601>(x3602)) ? 1 : -1));
        |  }
        |};
        |#endif

      """.stripMargin
    file.println(header :/: execProfile :/: structs :\\: structEquals  :\\: entryidx2 :\\: stTypdef :\\:
    tpccData :\\: threadLocal :\\: tm :: "\n\n#include \"TPCC.h\"\n"  :\\: runPrgFn :\\:
      threadFn:\\:
      traits :/: Document.nest(2, mainPrg) :/: "}")
    file.close()
  }
}

