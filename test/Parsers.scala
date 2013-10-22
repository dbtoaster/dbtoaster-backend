package ddbt.test
import org.scalatest._
import java.io._

/** These tags are used to mark tests with specific features */
object M3Test extends Tag("ddbt.M3Test")
object SQLTest extends Tag("ddbt.SQLTest")

// sbt 'test-only * -- -l ddbt.M3Test' => run all but M3 tests
// sbt 'test-only ddbt.test.ParserSpec -- -l ddbt.M3Test' => run all but M3 tests

class ParserSpec extends FunSpec with ParallelTestExecution {
  import ddbt.Utils._
  import ddbt.frontend._
  import ddbt.Compiler.toast
  import ddbt.unit.UnitTest.sqlFiles


  sqlFiles(true).foreach { file =>
    it("parse M3: "+file,M3Test) {
      val m3 = toast("m3",file)._2
      val ast1=M3Parser(m3)
      val ast2=M3Parser(ast1.toString)
      assert(ast2==ast1,"Double parsing does not preserve semantics")
    }
  }
  sqlFiles(false).foreach { file =>
    it("parse SQL: "+file,SQLTest) {
      val sql1=SQLParser.load(file,path_repo)
      val sql2=SQLParser(sql1.toString)
      assert(sql2==sql1,"Double parsing does not preserve semantics")
    }
  }
}
