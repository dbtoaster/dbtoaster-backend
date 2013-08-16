package ddbt

import java.io._
object Compiler {
  import ddbt.frontend._
  import ddbt.codegen._

  // Compilation phases
  val dir = new File("test/gen")
  val compile = ((f:File) => Utils.toast(f)) andThen
                M3Parser andThen
                dump("M3") andThen
                TypeCheck andThen
                ScalaGen("Query") andThen
                dump("Scala") andThen
                writeScala(dir) andThen
                writeTest(dir) //andThen
                //scalac("test/gen") andThen
                //execute("ddbt.gen")
                // then run 'sbt test'

  def dump[T](name:String)(data:T):T = {
    println("======================== "+name+" ========================")
    println(data.toString); data
  }

  def writeScala(dir:File)(data:String):String = {
    val pattern = """class (\w+)""".r
    val cls = pattern.findFirstMatchIn(data).map{_.group(1)} match { case Some(n) => n case _ => sys.error("No class found") }
    Utils.write(dir,cls+".scala",data)
    cls
  }

  def writeTest(dir:File)(cls:String):String = {
    Utils.write(dir,cls+"Spec.scala",
    "package ddbt.gen\n"+
    "import org.scalatest._\n\n"+
    "class "+cls+"Spec extends FunSpec {\n"+
    "  val (t,res) = "+cls+".execute()\n"+
    "  it(\"Executed in \"+"+cls+".time(t)+\" seconds\") {}\n"+
    // XXX: integrate result correctness check, integrate benchmarking
    // println(ddbt.lib.K3Helper.toStr(res))
    // describe("group") { it("test") { ... } }
    "}\n")
    cls
  }

/*
XXX: create a function that allows automated testing of results produced
by codegen: these must generate output, compile it and then compare
result with expected result (stored in a file or better: against DBToaster official results)

1. generate class + associated object + streams
2. compile the class and execute it
3. compare with textual result
*/

  // invoke with any filename in finance or tpch : axfinder, query13, query15, query18, ...

  def main(args: Array[String]) {
    val a = if (args.length>0) args(0) else "axfinder"
    compile(findQuery(a))
    // TPC-H 13,15,18
    //test(scala.io.Source.fromFile("resources/docs/chrissedtrades.m3").mkString);
/*
1. frontend
   - create temp directory (OK)
   - generate the m3 file (OK)
   - parse the m3 (OK)
   - parse the SQL (INCOMPLETE)
2. type the AST (?)
   - make sure we have enough information to output Scala
   ==> obtain an AST
3. optimize the AST
   - high level optimizations
   - simplify arithmetic expression
4. prepare for distributed system
   - add node conditionals in the code
   - replace some read operations by send/receive (depending node)
5. generate code with LMS
6. Distribute over nodes
7. Evaluate query
*/
  }

  def findQuery(s:String):File = {
    val b = "resources/queries/"; val x=".sql"
    val ps:List[String] = List("","finance/","tpch/","mddb/","simple/").map{d=>b+d+s+x} ::: List(s+x,s)
    val fs = ps.map{p => new java.io.File(p)}.filter{f=>f.exists}
    if (fs.size==0) sys.error("File '"+s+"' does not exist") else fs(0)
  }

}
