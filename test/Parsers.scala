package ddbt.test
import org.scalatest._
import java.io._

object SlowTest extends Tag("ddbt.SlowTest")

class ParserSpec extends FunSpec with ParallelTestExecution {
  import ddbt.Compiler._
  import ddbt.Utils._
  import ddbt.frontend._

  val files=exec(Array("find","resources/queries","-name","*.sql","-and","-not","-name","schemas.sql"))._1.split("\n")
  //val t = System.currentTimeMillis;
  //print("Toasting ...")
  //val m3src = files.par.map { f=>toast(new File(f)) }
  // describe("Parsers") {}
  
  // sbt 'test-only * -- -l ddbt.SlowTest'
  files.foreach { file =>
    it("parse M3: "+file,SlowTest) {
      val m3 = toast(new File(file))
      val ast1=M3Parser(m3)
      val ast2=M3Parser(ast1.toString)
      assert(ast2==ast1,"Double parsing does not preserve semantics")
    }
  }

  files.foreach { file =>
    it("parse SQL: "+file,SlowTest) {
      SQLParser.load(file)
    }
  }
}
