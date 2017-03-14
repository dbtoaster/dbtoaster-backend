package sc.micro

import ch.epfl.data.sc.pardis.types.{DoubleType, IntType, StringType}
import ddbt.codegen.TransactionProgram
import ddbt.lib.store.deep.DateIRs.DateType
import ddbt.lib.store.{GenericEntry, Store}
import ddbt.lib.store.deep._
import ddbt.transformer.{IndexedCols, StoreSchema}
import sc.micro.MicroBenchRunner._
class MB1 (override val Context : StoreDSL) extends Prog(Context) {
  import Sqd.Predef.{anyContextIsEmptyContext => _, _}
  import Sqd.Quasicodes._
  import Context.Predef._
  import Context.{__newStoreNamed, typeGenericEntry}
  var tbl : Rep[Store[GenericEntry]] = null
  val initBlock = reifyBlock({
    tbl = __newStoreNamed[GenericEntry]("customerTbl")
    unit(1)
  })
  def body = ir {
    var customerNames = $(tbl).map(e => GenericEntry("SteNewSEntry", e.get[Double](16)-e.get[Double](17), e.get[String](1))).filter(e => e.get[Double](1) < 1000.0).map(e => GenericEntry("SteNewSEntry", e.get[String](2))).fold(0)((a, b) => a+1)
//    var test = $(tbl).map(e => GenericEntry(10)).map(e => GenericEntry(20))
//    $(tbl).map(e => GenericEntry("SteNewSEntry", e.get[Int](3) * -2, 2, e.get[String](2))).filter(e => e.get[Int](1) > 0).map(e => GenericEntry("SteNewSEntry", e.get[Int](1)*100)).getCopy(0, GenericEntry("SteSampleSEntry", 1))
//    entry += (1, 11)
    1
  }.toRep
  override def getTransactionProgram: TransactionProgram[Int] = {
    val idxCols = new IndexedCols
    idxCols.primary =  List(1, 2, 3)
//    idxCols.fixedrange = List((1, 1, 3001), (2, 1, 11), (3, 1, 100 + 1))  //can't do for each on array index yet
    tbl.asInstanceOf[Sym[_]].attributes += idxCols
    tbl.asInstanceOf[Sym[_]].attributes += StoreSchema(List(IntType, IntType, IntType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, StringType, DateType, StringType, DoubleType, DoubleType, DoubleType, DoubleType, IntType, IntType, StringType))
    TransactionProgram(initBlock, List(tbl.asInstanceOf[Sym[_]]), List(("fun1", List(), reifyBlock(body))), Nil, Nil)
  }
}
