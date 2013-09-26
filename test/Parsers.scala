package ddbt.test
import org.scalatest._
import java.io._

/** These tags are used to mark tests with specific features */
object M3Test extends Tag("ddbt.M3Test")
object SQLTest extends Tag("ddbt.SQLTest")

// sbt 'test-only * -- -l ddbt.M3Test' => run all but M3 tests
// sbt 'test-only ddbt.test.ParserSpec -- -l ddbt.M3Test' => run all but M3 tests

class ParserSpec extends FunSpec with ParallelTestExecution {
  import ddbt.Utils
  import ddbt.frontend._
  import ddbt.UnitTest.{sqlFiles,toast}

  val (allSQL,allM3,baseSQL) = sqlFiles()

  allM3.foreach { file =>
    it("parse M3: "+file,M3Test) {
      val m3 = toast(file)
      val ast1=M3Parser(m3)
      val ast2=M3Parser(ast1.toString)
      assert(ast2==ast1,"Double parsing does not preserve semantics")
    }
  }
  allSQL.foreach { file =>
    it("parse SQL: "+file,SQLTest) {
      val sql1=SQLParser.load(file,baseSQL)
      val sql2=SQLParser(sql1.toString)
      assert(sql2==sql1,"Double parsing does not preserve semantics")
    }
  }
}
