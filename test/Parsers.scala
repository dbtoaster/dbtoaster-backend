package ddbt.test
import org.scalatest._
import java.io._

class ParserSpec extends FunSpec with ParallelTestExecution {
  import ddbt.Utils
  import ddbt.frontend._
  import ddbt.UnitTest
  
  //val m3src = files.par.map { f=>toast(new File(f)) }

  UnitTest.allM3.foreach { file =>
    it("parse M3: "+file,SlowTest) {
      val m3 = UnitTest.toast(file)
      val ast1=M3Parser(m3)
      val ast2=M3Parser(ast1.toString)
      assert(ast2==ast1,"Double parsing does not preserve semantics")
    }
  }
  UnitTest.allSQL.foreach { file =>
    it("parse SQL: "+file,SlowTest) {
      SQLParser.load(file,UnitTest.baseSQL)
    }
  }
}
