package ddbt.test
import org.scalatest._
import java.io._

object SlowTest extends Tag("ddbt.SlowTest")

class ParserSpec extends FunSpec with ParallelTestExecution {
  import ddbt.Utils
  import ddbt.frontend._
  import ddbt.UnitTest

  val (allSQL,allM3,baseSQL,myToast) = if (false && Utils.path_repo!="") {
    val b = Utils.path_repo+"/"+Utils.path_base
    def m(file:String) = UnitTest.load(file).sql
    (UnitTest.all.map(m),UnitTest.filtered.map(m),b,UnitTest.toast _)
  } else {
    val qdir = "examples/queries"
    if (!new File(qdir).exists) {
      System.err.println(("@"*80)+"\n@"+(" "*78)+"@")
      System.err.println("@ %-76s @".format("WARNING : folder '"+qdir+"' does not exist, parsers tests skipped"))
      System.err.println("@"+(" "*78)+"@\n"+("@"*80))
      (Array[String](),Array[String](),null,(s:String)=>s)
    } else {
      val files=Utils.exec(Array("find",qdir,"-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
      (files,files,null,(s:String)=>Utils.toast(new File(s)))
    }
  }
  
  //val m3src = files.par.map { f=>toast(new File(f)) }
  // sbt 'test-only * -- -l ddbt.SlowTest'

  allM3.foreach { file =>
    it("parse M3: "+file,SlowTest) {
      val m3 = myToast(file)
      val ast1=M3Parser(m3)
      val ast2=M3Parser(ast1.toString)
      assert(ast2==ast1,"Double parsing does not preserve semantics")
    }
  }
  allSQL.foreach { file =>
    it("parse SQL: "+file,SlowTest) {
      SQLParser.load(file,baseSQL)
    }
  }
}
