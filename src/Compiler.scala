package ddbt
import ddbt.frontend._
import ddbt.codegen._

/**
 * This class is the main compiler executable. It coordinates compilation phases
 * with respect to used-defined options passed as arguments in the command line.
 * @author TCK
 */
object Compiler {
  import java.io._

  var in  : List[String] = Nil  // input files
  var out : String = null       // output file (defaults to stdout)
  var lang: String = "scala"    // output language
  var libs: String = null       // runtime libraries (defaults to lib/ddbt.jar for scala)
  var name: String = null       // class/structures name (defaults to Query or capitalized filename)
  var exec: Boolean = false     // compile and execute immediately

  def error(str:String,fatal:Boolean=false) = { System.err.println(str); if (fatal) System.exit(1); null }
  def toast(l:String) = Utils.exec((Utils.path_bin :: "-O3" :: "-l" :: l :: in).toArray)._1

  def parseArgs(args:Array[String]) {
    val l=args.length
    var i=0
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) {
      args(i) match {
        case "-x" => exec = true
        case "-l" => eat(s=>s match { case "calc"|"m3"|"scala"|"lms"|"akka" => lang=s; case _ => error("Unsupported language: "+s,true) },true)
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
      error("                - akka  : distributed Akka code")
      error("                - lms   : LMS-optimized Scala")
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
      case _ if in.forall(_.endsWith(".m3")) => in.map(Utils.read(_)).mkString("\n")
      case _ => toast("m3")
    })
    // Back-end
    val cg:CodeGen = lang match {
      case "scala" => new ScalaGen(name)
      case "akka" => new AkkaGen(name)
      case "lms" => new LMSGen(name)
      case _ => error("Code generation for "+lang+" is not supported",true)
    }
    output(cg.helper(m3)+cg(m3))
    // Execution
    if (exec) lang match {
      case "scala"|"akka"|"lms" =>
        val tmp = Utils.makeTempDir()
        Utils.scalaCompiler(tmp,libs)(List(out))
        // Utils.exec(Array("scala","-cp",libs+":"+tmp,"ddbt.generated."+name))
        val (o,e) = Utils.loadMain(tmp,"ddbt.generated."+name) // execution
        if (e!="") error(e); if (o!="") println(o);
      case _ => error("Execution not supported",true)
    }
  }
}
