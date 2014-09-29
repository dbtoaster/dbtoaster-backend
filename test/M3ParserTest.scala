package ddbt.test
import org.scalatest._
import java.io._
import ddbt._
import ddbt.frontend._
import ddbt.codegen._

object M3ParserTest {
  val BATCH_SIZE = 4
  
  // Usage:
  // test:run-main ddbt.test.M3ParserTest /path/to/your/m3/file.m3
  def main(args: Array[String]) {
    if(args.length > 0) {
      val m3File = args(0)
      val source = scala.io.Source.fromFile(m3File)
      val m3_src = if (Utils.path_repo!=null) source.mkString.replaceAll("../../experiments/data",new File(Utils.path_repo).getParentFile.getParent+"/experiments/data").replace("throw DBTFatalError(\"Event could not be dispatched: \" + event)","supervisor ! DBTDone; throw DBTFatalError(\"Event could not be dispatched: \" + event)") else source.mkString
      source.close()
      Compiler.lang = Compiler.LANG_SCALA_LMS
      Compiler.name = "Query"
      Compiler.exec = true
      Compiler.exec_sc = true
      Compiler.exec_vm = true
      Compiler.exec_bs = BATCH_SIZE
      Compiler.exec_args = "-n1" :: "-b"+BATCH_SIZE :: "-p2" /*:: "-m1"*/ :: "-dstandard" :: Nil
      Compiler.out = "tpch3Test.Scala"
      Compiler.compile(m3_src)
      // val m3 = Compiler.postProc((M3Parser andThen TypeCheck) (m3_src))
      // java.lang.System.err.println("---------------------------")
      // java.lang.System.err.println(m3)
      // java.lang.System.err.println("===========================")
    } else {
      // System.err.println("Pass your m3 file path as the parameter.")
      System.err.println("Usage:")
      System.err.println("test:run-main ddbt.test.M3ParserTest /path/to/your/m3/file.m3")
    }
  }
}
