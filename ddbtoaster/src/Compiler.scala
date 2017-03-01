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

  val DEPLOYMENT_STATUS_RELEASE=1
  val DEPLOYMENT_STATUS_DEVELOPMENT=2

  val DEPLOYMENT_STATUS=DEPLOYMENT_STATUS_DEVELOPMENT

  val LANG_CALC = "calc"
  val LANG_M3 = "m3"
  val LANG_SCALA = "vscala"
  val LANG_CPP = "vcpp"
  val LANG_AKKA = "akka"
  val LANG_LMS = "lms"
  val LANG_CPP_LMS = "cpp"
  val LANG_SCALA_LMS = "scala"
  val LANG_SPARK_LMS = "spark"

  val M3_FILE_SUFFIX = ".m3"

  var frontend_path_bin:String = null // the path to DBToaster's frontend
  var batching_enabled:Boolean = false// determines whether batching is enabled or not
  var in   : List[String] = Nil  // input files
  var out  : String = null       // output file (defaults to stdout)
  var lang : String = null       // output language
  var cPath: String = null       // path for putting the compiled program
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
  var exec_bs : Int     = 0      // execute as batches of certain size

  // Print the time and the number of tuples processed every X tuples (0 = disable printing)
  var printProgress = 0
  var exec_args = List[String]() // arguments passed for execution
  def opts(o: String) = o match{
      case "entry" => Optimizer.analyzeEntry=true
      case "index" => Optimizer.analyzeIndex=true
      case "fixedrange" => Optimizer.fixedRange=true
      case "online" => Optimizer.onlineOpts=true
      case "m3cmpmult" => Optimizer.m3CompareMultiply=true
      case "tmpvar" => Optimizer.tmpVarHoist = true
      case "tmpmap" => Optimizer.tmpMapHoist = true
      case "idxinline" => Optimizer.indexInline = true
      case "sliceinline" => Optimizer.sliceInline = true
      case "lookupfusion" => Optimizer.indexLookupFusion = true
      case "partiallookupfusion" => Optimizer.indexLookupPartialFusion = true
      case "deadidx" => Optimizer.deadIndexUpdate = true
      case "codemotion" =>Optimizer.codeMotion = true
      case "refcounter" => Optimizer.refCounter = true
      case "regex" => Optimizer.regexHoister = true
      case "multires" => Optimizer.multiResSplitter = true
      case "slicenoupd" => Optimizer.sliceNoUpd = true
      case _ => throw new IllegalArgumentException(s"Unknown option $o")

    }
  def error(str:String,fatal:Boolean=false) = { System.err.println(str); if (fatal) System.exit(0); null }
  def toast(lang:String, opts:String*):(Long,String) = { // if opts is empty we do _NOT_ use repository
    val os = optm3 :: "-l" :: lang :: (if (depth>=0) List("--depth",""+depth) else Nil) ::: flags.flatMap(f=>List("-d",f)) ::: (if (!opts.isEmpty) opts.toList else in) ::: (if(batching_enabled) List("--batch") else Nil )
    val repo = if (Utils.path_repo!=null && !opts.isEmpty) new File(Utils.path_repo) else null
    val (t0,(m3,err)) = Utils.ns(()=>Utils.exec(((if(frontend_path_bin == null) Utils.path_bin else frontend_path_bin) :: os).toArray,repo,fatal=false))
    if (err.trim!="") { val e=new Exception("dbtoaster "+os.mkString(" ")+" failed because:\n"+err); e.setStackTrace(Array()); throw e }
    (t0, if (repo!=null) m3.replaceAll("../../experiments/data",repo.getParentFile.getParent+"/experiments/data").replace("throw DBTFatalError(\"Event could not be dispatched: \" + event)","supervisor ! DBTDone; throw DBTFatalError(\"Event could not be dispatched: \" + event)") else m3)
  }

  def parseArgs(args:Array[String]) {
    val l=args.length
    var i=0
    def eat(f:String=>Unit,s:Boolean=false) { i+=1; if (i<l) f(if(s) args(i).toLowerCase else args(i)) }
    while(i<l) {
      args(i) match {
        case "-l" => eat(s=>s match { case LANG_CALC|LANG_M3|LANG_SCALA|LANG_CPP|LANG_LMS|LANG_CPP_LMS|LANG_SCALA_LMS|LANG_SPARK_LMS|LANG_AKKA => lang=s; case _ => error("Unsupported language: "+s,true) },true)
        case "--frontend" => eat(s=>frontend_path_bin=s)
        case "--batch" => batching_enabled = true
        case "-o" => eat(s=>out=s)
        case "-c" => eat(s=>cPath=s)
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
        case "-xbs" => eat{i => exec_bs = i.toInt; batching_enabled = true}
        case "-pp" => eat(i => printProgress = i.toInt)
        case "-opt" => eat(s => opts(s), true)
        case s@"--no-output" => exec_args=exec_args:::List(s)
        case s if s.matches("-O[123]") => optm3=s;
        case s if s.startsWith("--") => exec_args=exec_args:::List(s.substring(1)) // --flag is a shorthand for -xa -flag
        case s => in = in ::: List(s)

      }
      i+=1
    }
    if (in.size==0) {
      error("Usage: Compiler [options] file1 [file2 [...]]")
      error("Global options:")
      error("  -o <file>     output file (default: stdout)")
      error("  -c <file>     invoke a second stage compiler on the source file")
      error("  -l <lang>     defines the target language")
      error("                - "+LANG_CALC     +"     : relational calculus")
      error("                - "+LANG_M3       +"       : M3 program")
      error("                - "+LANG_SCALA    +"    : vanilla Scala code")
      error("                - "+LANG_CPP      +"      : vanilla C++ code")
      // error("                - "+LANG_AKKA     +"     : distributed Akka code")
      // error("                - "+LANG_CPP_LMS  +"      : LMS-optimized C++")
      error("                - "+LANG_SCALA_LMS+" : LMS-optimized Scala")
      // error("                - "+LANG_SPARK_LMS+" : LMS-optimized Spark")
      //   ("                - dcpp     : distributed C/C++ code")
      error("Front-end options:")
      error("  -d <depth>    incrementalization depth (default: infinite)")
      error("  -O[123]       optimization level for M3 (default: -O2)")
      error("  -F <flag>     set a front-end optimization flag")
      // error("  -ni           non-incremental (on-demand) query evaluation")
      error("Code generation options:")
      error("  -n <name>     name of internal structures (default: Query)")
      // error("  -L            libraries for target language")
      // error("  -inl <level>  inlining level (0-10,none,spec,full,default:none)")
      // error("Execution options:")
      // error("  -x            compile and execute immediately")
      // error("  -xd <path>    destination for generated binaries")
      // error("  -xsc          use external fsc/scalac compiler")
      // error("  -xvm          execute in a new JVM instance")
      // error("  -xbs          execute as batches of certain size")
      // error("  -xa <arg>     pass an argument to generated program")
      error("", true) //exit the application
    }
    if(lang == null) {
      if(out != null){
        lang = if(out.endsWith(".cpp") || out.endsWith(".hpp") || out.endsWith(".h") || out.endsWith(".c")) LANG_CPP else LANG_SCALA
      } else {
        lang = LANG_CPP
      }
    }
    if (out==null && exec) { error("Execution disabled, specify an output file"); exec=false }
    if (name==null) {
      val n = if (out!=null) out.replaceAll(".*[/\\\\]","").replaceAll("\\..*","") else "query"
      val firstChar = n.substring(0,1);
      name = (if(Character.isDigit(firstChar(0))) "_"+firstChar else firstChar.toUpperCase)+n.substring(1)
    }
    def lib(s:String):Boolean = if (new File(s).exists) { libs=s::Nil; true } else false
    if (libs==Nil && exec) lang match {
      case LANG_SCALA => lib("lib/ddbt.jar") || lib("target/scala-2.10/classes") || ({ error("Cannot find runtime libraries"); exec=false; false })
      case _ =>
    }
  }

  def output(s:String) = if (out==null) println(s) else Utils.write(out,s)

  // M3 -> execution phase, returns (gen,compile) time
  def compile(m3_src:String,post_gen:(ast.M3.System)=>Unit=null,t_gen:Long=>Unit=null,t_comp:Long=>Unit=null,t_run:(()=>Unit)=>Unit=null, t_verify:(String,ast.M3.System,String)=>Unit=null) {
    val t0=System.nanoTime
    // Front-end phases
    val m3 = postProc((M3Parser andThen TypeCheck) (m3_src))

    // Back-end
    val cg:CodeGen = lang match {
      case LANG_SCALA => new ScalaGen(name,printProgress)
      case LANG_CPP => new CppGen(name)
      case LANG_AKKA => new AkkaGen(name)
     // case LANG_LMS => new LMSCppGen(name)
      case LANG_CPP_LMS => Optimizer.cTransformer = true ; new PardisCppGen(name)
      case LANG_SCALA_LMS => new PardisScalaGen(name) //DSL
     // case LANG_SPARK_LMS => new LMSSparkGen(name)
      case _ => error("Code generation for "+lang+" is not supported",true)
    }
    if (ni) {
      // ---- NON-INCREMENTAL START
      import ddbt.ast._; import M3._
      //XXX: Make this work with EXPRESSIVE-TLQS
      val (qns,qss) = (m3.queries.map{q=>q.name},scala.collection.mutable.HashMap[String,Stmt]())
      val triggers=m3.triggers.map(t=>Trigger(t.evt,t.stmts.filter {
        case s@StmtMap(m,e,op,i) => if (qns.contains(m.name)) { qss += ((m.name,s)); false } else true
        // case case MapDef(n,tp,ks,e) => XXXXXX
        case _ => true
      }))
      val r = cg.pkgWrapper(pkg,cg(System(m3.sources,m3.maps,m3.queries,Trigger(EvtAdd(Schema("__execute__",Nil)), qss.map(_._2).toList)::triggers)))
      // XXX: improve this RegExp
      output(r.replaceAll("GetSnapshot\\(_\\) => ","GetSnapshot(_) => onAdd__execute__(); ").replaceAll("onAdd__execute__","onExecute")) // Scala transforms
      // ---- NON-INCREMENTAL ENDS
    } else {
      output(cg.pkgWrapper(pkg,cg(m3)))
    }
    if (t_gen!=null) t_gen(System.nanoTime-t0)
    if (post_gen!=null) post_gen(m3)
    var dir:File = null
    if (cPath!=null || exec) {
      dir = if (exec_dir!=null) { val d=new File(exec_dir); if (!d.exists) d.mkdirs; d } else Utils.makeTempDir()
      lang match {
        case LANG_SCALA|LANG_AKKA|LANG_SCALA_LMS|LANG_SPARK_LMS =>
          val t2=Utils.ns(()=>Utils.scalaCompiler(dir,if (libs!=Nil) libs.mkString(":") else null,exec_sc)(List(out)))._1
          if (t_comp!=null) t_comp(t2)
          // TODO XXX should generate jar file in cPath
        case LANG_CPP|LANG_LMS|LANG_CPP_LMS => if(cPath!=null) {
          val pl = "srccpp/lib"
          val t2 = Utils.ns(()=>Utils.cppCompiler(out,cPath,null,pl))._1; if (t_comp!=null) t_comp(t2)
        }
      }
    }
    // Execution
    if (exec) {
      lang match {
        case LANG_SCALA|LANG_AKKA|LANG_SCALA_LMS|LANG_SPARK_LMS =>
          Utils.scalaExec(dir::libs.map(p=>new File(p)),pkg+"."+name,("-b"+exec_bs :: exec_args).toArray,exec_vm)
        case LANG_CPP|LANG_LMS|LANG_CPP_LMS =>
          val (samplesAndWarmupRounds, mode, timeout, pMode, datasets, batchSize, no_output) = ddbt.lib.Helper.extractExecArgs(("-b"+exec_bs :: exec_args).toArray)
          val actual_exec_args = "-b "+exec_bs :: "-p "+pMode :: (if(no_output) List("--no-output") else Nil)
          val compiledSrc = Utils.read(out);
          datasets.foreach{ dataset =>
            def tc(p:String="") = "gettimeofday(&("+p+"t),NULL); "+p+"tT=(("+p+"t).tv_sec-("+p+"t0).tv_sec)*1000000L+(("+p+"t).tv_usec-("+p+"t0).tv_usec);"
            val srcTmp=compiledSrc.replace("standard",dataset)
                            .replace("++tN;",(if (timeout>0) "if (tS>0) { ++tS; return; } if (tN%100==0) { "+tc()+" if (tT>"+(timeout*1000L)+"L) { tS=1; return; } } " else "")+"++tN;")
                            .replace("//P"+pMode+"_PLACE_HOLDER",
                                      "struct timeval t0;\n"+
                            "          gettimeofday(&t0,NULL);\n"+
                            "          data.t0 = t0;\n")
            //TODO XXX dataset should be an argument to the program
            val src = if(dataset.contains("_del")) srcTmp.replace("make_pair(\"schema\",\"", "make_pair(\"deletions\",\"true\"), make_pair(\"schema\",\"").replace("\"),2,", "\"),3,") else srcTmp
            Utils.write(out,src)
            val pl = "srccpp/lib"
            val po = if(cPath!=null) cPath else out.substring(0,out.lastIndexOf("."))
            val t2 = Utils.ns(()=>Utils.cppCompiler(out,out.substring(0,out.lastIndexOf(".")),null,pl))._1; if (t_comp!=null) t_comp(t2)
            if(t_run != null) {
              t_run(()=>{
                var i = 0
                while (i < samplesAndWarmupRounds) {
                  i += 1
                  val (out,err) = Utils.exec((po :: actual_exec_args).toArray,null,null)
                  if(t_verify != null) t_verify(out,m3,dataset)
                  if (err!="") System.err.println(err)
                  Utils.write(po+"_"+lang+".txt",out)
                  println(out)
                }
              })
            } else {
              var i=0
              while (i < samplesAndWarmupRounds) {
                i+=1
                val (out,err)=Utils.exec((po :: actual_exec_args).toArray,null,null)
                if(t_verify != null) t_verify(out,m3,dataset)
                if (err!="") System.err.println(err)
                Utils.write(po+"_"+lang+".txt",out)
                println(out)
              }
            }
          }
        case _ => error("Execution not supported for "+lang,true)
      }
    }
  }

  def postProc(s0:ast.M3.System) = {
    //fixing the unique id for each statement
    //used in debugging and performance measurements
    var stmtId = 0
    s0.triggers.foreach{ trg => trg.stmts.map { stmt =>
        stmt.stmtId = stmtId
        stmtId += 1
      }
    }
    s0
  }

  def main(args: Array[String]) {
    parseArgs(args)
    try {
      lang match {
        case LANG_CALC => output(toast(lang)._2)
        case LANG_M3 => output(TypeCheck(M3Parser(toast(lang)._2)).toString)
        case _ if in.forall(_.endsWith(M3_FILE_SUFFIX)) => compile(in.map(Utils.read(_)).mkString("\n"))
        case _ => compile(toast(LANG_M3)._2)
      }
    } catch { case t:Throwable => val sw = new StringWriter(); val pw = new PrintWriter(sw); t.printStackTrace(pw); error(sw.toString(),true) }
  }
}
