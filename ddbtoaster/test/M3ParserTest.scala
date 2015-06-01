package ddbt.test
import org.scalatest._
import java.io._
import ddbt._
import ddbt.frontend._
import ddbt.codegen._

object M3ParserTest {
  val LANG = Compiler.LANG_SCALA_LMS
  val BATCH_SIZE = 4
  val DATASET = "standard"
  val INPUT_PROCESSING_MODE = 2
  
  // Usage:
  // test:run-main ddbt.test.M3ParserTest /path/to/your/m3/file.m3
  def main(args: Array[String]) {
    if(args.length > 0) {
      val m3File = args(0)
      val source = scala.io.Source.fromFile(m3File)
      val m3_src = if (Utils.path_repo!=null) source.mkString.replaceAll("../../experiments/data",new File(Utils.path_repo).getParentFile.getParent+"/experiments/data").replace("throw DBTFatalError(\"Event could not be dispatched: \" + event)","supervisor ! DBTDone; throw DBTFatalError(\"Event could not be dispatched: \" + event)") else source.mkString
      source.close()
      Compiler.lang = LANG
      Compiler.name = "Query"
      Compiler.exec = true
      Compiler.exec_sc = true
      Compiler.exec_vm = true
      Compiler.batching_enabled = true
      Compiler.exec_bs = BATCH_SIZE
      Compiler.exec_args = "-n1" :: "-b"+BATCH_SIZE :: "-p"+INPUT_PROCESSING_MODE /*:: "-m1"*/ :: "-d"+DATASET :: Nil
      Compiler.out = "./tpch3Test"+(if(Compiler.lang == Compiler.LANG_CPP) ".cpp" else ".scala")
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
