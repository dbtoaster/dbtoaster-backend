package sc.micro

import ddbt.codegen.TransactionProgram
import ddbt.lib.store.{GenericEntry, Store}
import ddbt.lib.store.deep._
import ddbt.transformer.IndexedCols
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
    var customerNames = $(tbl).map(e => GenericEntry("SteNewSEntry", e.get[Double](4)-e.get[Double](3), e.get[String](2))).filter(e => e.get[Double](1) < 1000).map(e => GenericEntry("SteNewSEntry", e.get[String](2))).fold(0)((a, b) => a+1)
//    var test = $(tbl).map(e => GenericEntry(10)).map(e => GenericEntry(20))
//    $(tbl).map(e => GenericEntry("SteNewSEntry", e.get[Int](3) * -2, 2, e.get[String](2))).filter(e => e.get[Int](1) > 0).map(e => GenericEntry("SteNewSEntry", e.get[Int](1)*100)).getCopy(0, GenericEntry("SteSampleSEntry", 1))
//    entry += (1, 11)
    1
  }.toRep
  override def getTransactionProgram: TransactionProgram[Int] = {
    val idxCols = new IndexedCols
    idxCols.primary = List(1)
    tbl.asInstanceOf[Sym[_]].attributes += idxCols
    TransactionProgram(initBlock, List(tbl.asInstanceOf[Sym[_]]), List(("fun1", List(), reifyBlock(body))), Nil, Nil)
  }
}
