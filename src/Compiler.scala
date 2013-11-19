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

  var in   : List[String] = Nil  // input files
  var out  : String = null       // output file (defaults to stdout)
  var lang : String = "scala"    // output language
  var name : String = null       // class/structures name (defaults to Query or capitalized filename)
  var pkg  : String = "ddbt.gen" // class package
  var optm3: String = "-O2"      // optimization level
  var depth: Int = -1            // incrementalization depth (-1=infinite)
  var flags: List[String] = Nil  // front-end flags
  var libs : List[String] = Nil  // runtime libraries (defaults to lib/ddbt.jar for scala)
  var ni   : Boolean = false     // non-incremental query evaluation (implies depth=0)
  var inl  : Int = 0             // inlining level, in range [0-10]
  // Execution
  var exec    : Boolean = false  // compile and execute immediately
  var exec_dir: String  = null   // execution classpath
  var exec_sc : Boolean = false  // compile using fsc / external scalac
  var exec_vm : Boolean = false  // execute in a fresh JVM
  var exec_args = List[String]() // arguments passed for execution

  def error(str:String,fatal:Boolean=false) = { System.err.println(str); if (fatal) System.exit(1); null }
  def toast(lang:String, opts:String*):(Long,String) = { // if opts is empty we do _NOT_ use repository
    val os = optm3 :: "-l" :: lang :: (if (depth>=0) List("--depth",""+depth) else Nil) ::: flags.flatMap(f=>List("-F",f)) ::: (if (!opts.isEmpty) opts.toList else in)
    val repo = if (Utils.path_repo!=null && !opts.isEmpty) new File(Utils.path_repo) else null
    val (t0,(m3,err)) = Utils.ns(()=>Utils.exec(((if (repo!=null) "bin/dbtoaster_release" else Utils.path_bin) :: os).toArray,repo,fatal=false))
    if (err.trim!="") { val e=new Exception("dbtoaster "+os.mkString(" ")+" failed because:\n"+err); e.setStackTrace(Array()); throw e }
    (t0, if (repo!=null) m3.replaceAll("../../experiments/data",repo.getParentFile.getParent+"/experiments/data") else m3)
  }

  def parseArgs(args:Array[String]) {
    val l=args.length
    var i=0
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) {
      args(i) match {
        case "-l" => eat(s=>s match { case "calc"|"m3"|"scala"|"lms"|"akka" => lang=s; case _ => error("Unsupported language: "+s,true) },true)
        case "-o" => eat(s=>out=s)
        case "-n" => eat(s=>{ val p=s.lastIndexOf('.'); if (p!= -1) { pkg=s.substring(0,p); name=s.substring(p+1) } else name=s})
        case "-L" => eat(s=>libs=s::libs)
        case "-d" => eat(s=>depth=s.toInt)
        case "-F" => eat(s=>flags=s::flags)
        case "-inl" => eat(s=>inl = if (s=="spec") 5 else if (s=="full") 10 else try { math.min(10,math.max(0,s.toInt)) } catch { case _:Throwable => 0 })
        case "-ni" => ni=true; depth=0; flags=Nil
        case "-x" => exec = true
        case "-xd" => eat(s=>exec_dir=s)
        case "-xa" => eat(s=>exec_args=exec_args:::List(s))
        case "-xsc" => exec_sc=true;
        case "-xvm" => exec_vm=true;
        case s if s.matches("-O[123]") => optm3=s;
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
      error("Front-end options:")
      error("  -d <depth>    incrementalization depth (default: infinite)")
      error("  -O[123]       optimization level for M3 (default: -O2)")
      error("  -F <flag>     set a front-end optimization flag")
      error("  -ni           non-incremental (on-demand) query evaluation")
      error("Code generation options:")
      error("  -n <name>     name of internal structures (default: Query)")
      error("  -L            libraries for target language")
      error("  -inl <level>  inlining level (0-10,none,spec,full,default:none)")
      error("Execution options:")
      error("  -x            compile and execute immediately")
      error("  -xd <path>    destination for generated binaries")
      error("  -xsc          use external fsc/scalac compiler")
      error("  -xvm          execute in a new JVM instance")
      error("  -xa <arg>     pass an argument to generated program",true)
    }
    if (out==null && exec) { error("Execution disabled, specify an output file"); exec=false }
    if (name==null) {
      val n = if (out!=null) out.replaceAll(".*[/\\\\]","").replaceAll("\\..*","") else "query"
      name = n.substring(0,1).toUpperCase+n.substring(1)
    }
    def lib(s:String):Boolean = if (new File(s).exists) { libs=s::Nil; true } else false
    if (libs==Nil && exec) lang match {
      case "scala" => lib("lib/ddbt.jar") || lib("target/scala-2.10/classes") || ({ error("Cannot find runtime libraries"); exec=false; false })
      case _ =>
    }
  }

  def output(s:String) = if (out==null) println(s) else { val f=new File(out); Utils.write(if (f.getParentFile==null) new File(".") else f.getParentFile,f.getName,s) }

  // M3 -> execution phase, returns (gen,compile) time
  def compile(m3_src:String,post_gen:(ast.M3.System)=>Unit=null):(Long,Long) = {
    val t0=System.nanoTime
    // Front-end phases
    val m3 = (M3Parser andThen TypeCheck) (m3_src)
    // Back-end
    val cg:CodeGen = lang match {
      case "scala" => new ScalaGen(name)
      case "akka" => new AkkaGen(name)
      case "lms" => new LMSGen(name)
      case _ => error("Code generation for "+lang+" is not supported",true)
    }
    // ---- NON-INCREMENTAL START
    if (ni) { import ddbt.ast._; import M3._
      val (qns,qss) = (m3.queries.map{q=>q.map.name},scala.collection.mutable.HashMap[String,Stmt]())
      val triggers=m3.triggers.map(t=>Trigger(t.evt,t.stmts.filter {
        case s@StmtMap(m,e,op,i) => if (qns.contains(m.name)) { qss += ((m.name,s)); false } else true
        case _ => true
      }))
      val r = cg.helper(m3,pkg)+cg(System(m3.sources,m3.maps,m3.queries,Trigger(EvtAdd(Schema("__execute__",Nil)), qss.map(_._2).toList)::triggers))
      // XXX: improve this RegExp
      output(r.replaceAll("GetSnapshot\\(_\\) => ","GetSnapshot(_) => onAdd__execute__(); ").replaceAll("onAdd__execute__","onExecute")) // Scala transforms
    } else
    // ---- NON-INCREMENTAL ENDS
    output(cg.helper(m3,pkg)+cg(m3))
    val t1=System.nanoTime
    if (post_gen!=null) post_gen(m3)
    // Execution
    var t2=0L
    if (exec) lang match {
      case "scala"|"akka"|"lms" =>
        val dir = if (exec_dir!=null) { val d=new File(exec_dir); if (!d.exists) d.mkdirs; d } else Utils.makeTempDir()
        t2=Utils.ns(()=>Utils.scalaCompiler(dir,if (libs!=Nil) libs.mkString(":") else null,exec_sc)(List(out)))._1
        val (o,e) = Utils.scalaExec(dir::libs.map(p=>new File(p)),pkg+"."+name,exec_args.toArray,exec_vm)
        if (e!="") error(e); if (o!="") println(o);
      case _ => error("Execution not supported for "+lang,true)
    }
    (t1-t0,t2)
  }

  def main(args: Array[String]) {
    parseArgs(args)
    try {
      lang match {
        case "calc"|"m3" => output(toast(lang)._2)
        case _ if in.forall(_.endsWith(".m3")) => compile(in.map(Utils.read(_)).mkString("\n"))
        case _ => compile(toast("m3")._2)
      }
    } catch { case t:Throwable => error(t.getMessage,true) }
  }
}
