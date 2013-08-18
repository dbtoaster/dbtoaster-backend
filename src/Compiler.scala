package ddbt

import java.io._
object Compiler {
  import ddbt.frontend._
  import ddbt.codegen._
  
  var in  : List[String] = Nil  // input files
  var out : String = null       // output file (defaults to stdout)
  var lang: String = "scala"    // output language
  var libs: String = null       // runtime libraries (defaults to lib/ddbt.jar for scala)
  var name: String = null       // class/structures name (defaults to Query or capitalized filename)
  var exec: Boolean = false     // compile and execute immediately

  def error(str:String,fatal:Boolean=false) = { System.err.println(str); if (fatal) System.exit(1) }
  def toast(l:String) = Utils.exec((Utils.path_bin :: "-l" :: l :: in).toArray)._1

  def parseArgs(args:Array[String]) {
    val l=args.length
    var i=0
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) {
      args(i) match {
        case "-x" => exec = true
        case "-l" => eat(s=>s match { case "calc"|"m3"|"scala" => lang=s; case _ => error("Unsupported language: "+s,true) },true)
        case "-o" => eat(s=>out=s)
        case "-n" => eat(s=>name=s)
        case "-L" => eat(s=>libs=s)
        case s => in = in ::: List(s)
      }
      i+=1
    }
    if (in.size==0) {
      error("Usage: Compiler [options] file1 [file2 [...]]")
      error("Global options:")
      error("  -o <file>     output file (default: stdout)")
      error("  -l <lang>     defines the target language") 
      error("                - calc  : relational calculus")
      error("                - m3    : M3 program")
      error("                - scala : vanilla Scala code")
      //   ("                - lms   : LMS-optimized Scala")
      //   ("                - akka  : distributed Akka code")
      //   ("                - cpp   : C++/LMS-optimized code")
      //   ("                - dcpp  : distributed C/C++ code")
      error("Code generation options:")
      error("  -n <name>     name of internal structures (default: Query)")
      error("  -L            libraries for target language")
      error("  -x            compile and execute immediately",true)
    }
    if (out==null && exec) { error("Execution disabled, specify an output file"); exec=false }
    if (name==null) {
      val n = if (out!=null) out.replaceAll(".*[/\\\\]","").replaceAll("\\..*","") else "query"
      name = n.substring(0,1).toUpperCase+n.substring(1)
    }
    def lib(s:String):Boolean = if (new File(s).exists) { libs=s; true } else false
    if (libs==null && exec) lang match {
      case "scala" => lib("lib/ddbt.jar") || lib("target/scala-2.10/classes") || ({ error("Cannot find runtime libraries"); exec=false; false })
      case _ =>
    }
  }
 
  def output(s:String) = if (out==null) println(s) else { val f=new File(out); Utils.write(if (f.getParentFile==null) new File(".") else f.getParentFile,f.getName,s) }

  def main(args: Array[String]) {
    parseArgs(args)
    // Front-end
    val m3 = (M3Parser andThen TypeCheck) (lang match {
      case "calc"|"m3" => output(toast(lang)); System.exit(0); "" // nothing else to do
      case _ => toast("m3")
    })
    // Back-end
    lang match {
      case "scala" => output(ScalaGen(name)(m3))
      case _ => error("Compilation not supported")
    }
    // Execution
    if (exec) lang match {
      case "scala" =>
        val tmp = Utils.makeTempDir()
        Utils.exec(Array("scalac",out,"-cp",libs,"-d",tmp.getPath)) // scala compiler
        val (o,e) = Utils.exec(Array("scala","-cp",libs+":"+tmp,"ddbt.generated."+name)) // execution
        if (e!="") error(e); println(o);
      case _ => error("Execution not supported")
    }
  }
}

  /*
  // invoke with any filename in finance or tpch : axfinder, query13, query15, query18, ...
  // TPC-H 13,15,18
  def findQuery(s:String):File = {
    val b = "resources/queries/"; val x=".sql"
    val ps:List[String] = List("","finance/","tpch/","mddb/","simple/").map{d=>b+d+s+x} ::: List(s+x,s)
    val fs = ps.map{p => new java.io.File(p)}.filter{f=>f.exists}
    if (fs.size==0) sys.error("File '"+s+"' does not exist") else fs(0)
  }
  def dump[T](name:String)(data:T):T = {
    println("======================== "+name+" ========================")
    println(data.toString); data
  }

  // Compilation phases
  val dir = new File("bin")
  val compile = Utils.toast _ andThen
                M3Parser andThen
                //dump("M3") andThen
                TypeCheck andThen
                ScalaGen("Query") andThen
                //dump("Scala") andThen
                writeScala(dir) //andThen
                //writeTest(dir) //andThen
                //scalac("test/gen") andThen
                //execute("ddbt.gen")
                // then run 'sbt test'

  def writeScala(dir:File)(data:String):String = {
    val pattern = """class (\w+)""".r
    val cls = pattern.findFirstMatchIn(data).map{_.group(1)} match { case Some(n) => n case _ => sys.error("No class found") }
    Utils.write(dir,cls+".scala",data)
    cls
  }
*/
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

