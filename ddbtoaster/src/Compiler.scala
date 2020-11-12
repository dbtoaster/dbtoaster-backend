package ddbt

import java.io._
import ddbt.lib.Utils
import ddbt.ast._
import ddbt.frontend._
import ddbt.codegen._
import ddbt.codegen.Optimizer


/**
 * This class is the main compiler executable. It coordinates compilation phases
 * with respect to used-defined options passed as arguments in the command line.
 *
 * @author TCK, Milos Nikolic
 */
object Compiler {

  val DEPLOYMENT_STATUS_RELEASE = 1
  val DEPLOYMENT_STATUS_DEVELOPMENT = 2
  val DEPLOYMENT_STATUS = DEPLOYMENT_STATUS_DEVELOPMENT

  val PRINT_TIMING_INFO = false

  val LANG_CALC = "calc"
  val LANG_M3 = "m3"
  val LANG_DIST_M3 = "annotm3"
  val LANG_CPP_VANILLA = "cpp"
  val LANG_CPP_LMS = "lmscpp"
  val LANG_CPP_PARDIS = "pcpp"
  val LANG_SCALA_VANILLA = "vscala"
  val LANG_SCALA_LMS = "lmsscala"
  val LANG_SCALA_PARDIS = "scala"
  val LANG_SPARK_LMS = "spark"
  val LANG_AKKA = "akka"

  val frontendFileExtensions = Map(
      LANG_CALC -> "calc",
      LANG_M3 -> "m3",
      LANG_DIST_M3 -> "dm3",
      LANG_CPP_VANILLA -> "m3",
      LANG_CPP_LMS -> "m3",
      LANG_CPP_PARDIS -> "m3",
      LANG_SCALA_VANILLA -> "m3",
      LANG_SCALA_LMS -> "m3",
      LANG_SCALA_PARDIS -> "m3",
      LANG_SPARK_LMS -> "dm3",
      LANG_AKKA -> "m3"
    )

  val backendFileExtensions = Map(
      LANG_CALC -> "calc",
      LANG_M3 -> "m3",
      LANG_DIST_M3 -> "dm3",
      LANG_CPP_VANILLA -> "hpp",
      LANG_CPP_LMS -> "hpp",
      LANG_CPP_PARDIS -> "hpp",
      LANG_SCALA_VANILLA -> "scala",
      LANG_SCALA_LMS -> "scala",
      LANG_SCALA_PARDIS -> "scala",
      LANG_SPARK_LMS -> "scala",
      LANG_AKKA -> "scala"
    )

  val M3_FILE_SUFFIX = ("""\.(""" + frontendFileExtensions(LANG_M3) + "|" + 
                                    frontendFileExtensions(LANG_DIST_M3) + ")").r
  
  val DEFAULT_LANG_CPP = LANG_CPP_VANILLA
  val DEFAULT_LANG_SCALA = LANG_SCALA_PARDIS
  val DEFAULT_PACKAGE_NAME = "ddbt.gen"
  val DEFAULT_DATASET_NAME = "standard"

  private var inputFile: String = null        // input file
  private var outputSrcFile: String = null    // output file (defaults to stdout)
  private var outputExeFile: String = null    // path for putting the compiled program
  private var outputExeDir = new File("./")  // output directory
  private var lang: String = null             // output language

  private var frontendPathBin = Utils.pathDBTBin    // the path to DBToaster's frontend
  private var frontendOptLevel = "-O2"              // optimization level
  private var frontendIvmDepth = -1                 // incrementalization depth (-1 = infinite)
  private var frontendDebugFlags = List[String]()   // front-end flags
  private var batchingEnabled = false               // determines whether batching is enabled or not

  // Codegen options
  private var className: String = null              // class/structures name (defaults to Query or capitalized filename)
  private var packageName = DEFAULT_PACKAGE_NAME    // class package
  private var datasetName = DEFAULT_DATASET_NAME    // dataset name (used for codegen)
  private var datasetWithDeletions = false          // whether dataset contains deletions or not
  
  // Execution
  private var execOutput = false               // compile and execute immediately
  private var execArgs = List[String]()        // arguments passed for execution
  private var execPrintProgress = 0            // print time and number of tuples processed every X tuples (0 = disable printing)
  private var execBatchSize = 0                // execute as batches of certain size
  private var execTimeoutMilli = 0L            // execution timeout in milliseconds
  private var execRuntimeLibs = List[String]() // runtime libraries (defaults to lib/ddbt.jar for scala)
  private var execPreloadInput = false         // preload input dataset  

  // Experimental features
  private var useExperimentalCppHashMap = false
  private var useExperimentalCppRuntimeLibrary = false    

  private var useExternalScalac = false        // compile using fsc / external scalac
  private var useExternalJVM = false           // execute in a fresh JVM

  // private var ni   = false     // non-incremental query evaluation (implies depth=0)
  // private var watch  = false    // stream of updates on result map

  def isBatchingEnable = batchingEnabled

  def batchSize = execBatchSize

  def outputLang = lang

  def timeoutMilli = execTimeoutMilli

  def error(s: String, fatal: Boolean = false) = {
    System.err.println(s)
    if (fatal) System.exit(0)
    null
  }

  private def output(s: String, file: String) =   
    if (file == null) println(s) else Utils.write(file, s)

  private def showHelp() = {
    def pad(s: String) = f"${s}%8s"

    error("Usage: Compiler [options] file")
    error("Global options:")
    error("  -h            show help message")
    error("  -o <file>     output file (default: stdout)")
    error("  -c <file>     invoke a second stage compiler on the source file")
    error("  -l <lang>     defines the target language")
    error("                - " + pad(LANG_CALC)          + ": relational calculus")
    error("                - " + pad(LANG_M3)            + ": M3 program")
    error("                - " + pad(LANG_DIST_M3)       + ": distributed M3 program")
    error("                - " + pad(LANG_CPP_VANILLA)   + ": vanilla C++ code")
    // error("                - " + pad(LANG_CPP_LMS)       + ": LMS-optimized C++")
    error("                - " + pad(LANG_CPP_PARDIS)    + ": PARDIS-optimized C++")
    error("                - " + pad(LANG_SCALA_VANILLA) + ": vanilla Scala code")
    error("                - " + pad(LANG_SCALA_LMS)     + ": LMS-optimized Scala")
    error("                - " + pad(LANG_SCALA_PARDIS)  + ": PARDIS-optimized Scala")
    error("                - " + pad(LANG_SPARK_LMS)     + ": LMS-optimized Spark")
    // error("                - " + pad(LANG_AKKA)          +": distributed Akka code")
    error("Front-end options:")
    error("  --depth <depth>    incrementalization depth (default: -1 = infinite)")
    error("  --batch       Enable batch processing")
    error("  -O[123]       optimization level for M3 (default: -O2)")
    error("  -F <flag>     set a front-end optimization flag")
    // error("  -ni           non-incremental (on-demand) query evaluation")
    error("Code generation options:")
    error("  -n <name>     name of internal structures (default: Query)")
    error("  -d <name>     dataset name")
    error("  --del         dataset contains deletions")
    error("  -L            libraries for target language")
    error("Execution options:")
    error("  -x            compile and execute immediately")
    error("  -xd <path>    destination for generated binaries")
    error("  -xsc          use external fsc/scalac compiler (Scala)")
    error("  -xvm          execute in a new JVM instance (Scala)")
    error("  -t <n>        execution timeout in seconds")
    error("  -xbs <n>      execute with batches of certain size")
    error("  -xa <arg>     pass an argument to generated program")    
    error("Experimental features:")
    error("  -xhashmap     use experimental C++ hash map implementation")
    error("  -xruntime     use experimental C++ runtime library")
    error("  -preload      preload input datasets")
    
    error("", true)     // exit here
  }

  private def opts(o: String) = o match {
    case "entry" => Optimizer.analyzeEntry = true
    case "index" => Optimizer.secondaryIndex = true
    case "fixedrange" => Optimizer.fixedRange = true
    case "online" => Optimizer.onlineOpts = true
    case "m3cmpmult" => Optimizer.m3CompareMultiply = true
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
    case "initsize" => Optimizer.initialStoreSize = true
    case "slicenoupd" => Optimizer.sliceNoUpd = true
    case "spl" => Optimizer.splSecondaryIdx = true
    case "minmax" => Optimizer.minMaxIdx = true
    case "med" => Optimizer.medIdx = true
    case "coldmotion" => Optimizer.coldMotion = true
    case "profilestore" => Optimizer.profileStoreOperations = true
    case "parpromo" => Optimizer.parameterPromotion = true
    case _ => throw new IllegalArgumentException(s"Unknown option $o")
  }

  private def resetParameters() = {
    inputFile = null
    outputSrcFile = null
    outputExeFile = null
    outputExeDir = new File("./")
    lang = null

    frontendPathBin = Utils.pathDBTBin
    frontendOptLevel = "-O2"
    frontendIvmDepth = -1 
    frontendDebugFlags = Nil
    batchingEnabled = false

    className = null
    packageName = DEFAULT_PACKAGE_NAME
    datasetName = DEFAULT_DATASET_NAME
    datasetWithDeletions = false
  
    execOutput = false
    execArgs = Nil
    execPrintProgress = 0
    execBatchSize = 0
    execTimeoutMilli = 0L
    execRuntimeLibs = Nil
    execPreloadInput = false

    useExperimentalCppHashMap = false
    useExperimentalCppRuntimeLibrary = false

    useExternalScalac = false
    useExternalJVM = false
  }

  def parseArgs(args: Array[String], reset: Boolean = false): Unit = {
    if (reset) resetParameters()
    execArgs = Nil

    var i = 0 
    def eat(f: String => Unit, lower: Boolean = false) = {
      i += 1
      if (i < args.length) f(if (lower) args(i).toLowerCase else args(i)) 
    }
    var inputFiles = List[String]()
    while (i < args.length) {
      args(i) match {
        case "-h"|"-help"|"--help" => showHelp()
        case "-o" => eat(s => outputSrcFile = s)
        case "-c" => eat(s => outputExeFile = s)
        case "-l" => eat(s => s match { 
            case LANG_CALC|LANG_M3|LANG_DIST_M3|
                 LANG_CPP_VANILLA|LANG_CPP_LMS|LANG_CPP_PARDIS|
                 LANG_SCALA_VANILLA|LANG_SCALA_LMS|LANG_SCALA_PARDIS|
                 LANG_SPARK_LMS|LANG_AKKA => lang = s
            case _ => sys.error("Unsupported language: " + s)
          }, true)
        case "--frontend" => eat(s => frontendPathBin = s)
        case "--depth" => eat(s => frontendIvmDepth = s.toInt)
        case "--batch" => batchingEnabled = true
        case "-F" => eat(s => frontendDebugFlags = s :: frontendDebugFlags)
        case "-n" => eat(s => { val p = s.lastIndexOf('.')
                                if (p == -1) {
                                  packageName = DEFAULT_PACKAGE_NAME
                                  className = s
                                }
                                else {
                                  packageName = s.substring(0, p)
                                  className = s.substring(p + 1) 
                                }
                              })
        case "-d" => eat(s => datasetName = s)
        case "--del" => datasetWithDeletions = true
        case "-L" => eat(s => execRuntimeLibs = s :: execRuntimeLibs)
        case "-xhashmap" => useExperimentalCppHashMap = true
        case "-xruntime" => useExperimentalCppRuntimeLibrary = true
        case "-preload" => execPreloadInput = true
        // case "-wa" => watch = true;
        // case "-ni" => ni = true; frontendIvmDepth = 0; frontendDebugFlags = Nil
        case "-x" => execOutput = true
        case "-xd" => eat(s => outputExeDir = new File(s))
        case "-xsc" => useExternalScalac = true
        case "-xvm" => useExternalJVM = true
        case "-t" => eat(s => execTimeoutMilli = s.toLong * 1000)
        case "-xbs" => eat { i => execBatchSize = i.toInt; batchingEnabled = true }
        case "-xa" => eat(s => execArgs = execArgs ::: List(s))
        case "-pp" => eat(i => execPrintProgress = i.toInt)
        case "-opt" => eat(s => opts(s), true)
        case s @ "--no-output" => execArgs = execArgs ::: List(s)
        case s if s.matches("-O[123]") => frontendOptLevel = s;
        case s if s.startsWith("--") => execArgs = execArgs ::: List(s.substring(1)) // --flag is a shorthand for -xa -flag
        case s => inputFiles = inputFiles ::: List(s)
      }
      i += 1
    }

    if (inputFiles.size > 1) {
      showHelp()  // exit here
    }
    inputFile = inputFiles.headOption.getOrElse(null)

    if (lang == null && outputSrcFile != null) {
      if (outputSrcFile.matches(".+\\.(cpp|c|hpp|h)$"))
        lang = DEFAULT_LANG_CPP
      else if (outputSrcFile.endsWith(".scala"))
        lang = DEFAULT_LANG_SCALA
    }

    if (batchingEnabled) {
      if (lang == LANG_SCALA_PARDIS) {
        error(s"Pardis Scala code generator does not support batching. Use '-l ${LANG_SCALA_LMS}' or '-l ${LANG_SCALA_VANILLA}' instead.", true)
      }
      else if (lang == LANG_CPP_PARDIS) {
       error(s"Pardis C++ code generator does not support batching. Use '-l ${LANG_CPP_VANILLA}' instead.", true) 
      }
    }

    if (outputSrcFile == null && outputExeFile != null) {
      outputSrcFile = backendFileExtensions.get(lang).map(outputExeFile + "." + _).getOrElse(null)
    }

    if (className == null) {
      val n = if (outputSrcFile == null) "Query"
              else outputSrcFile.replaceAll(".*[/\\\\]", "").replaceAll("\\..*", "")
      val firstChar = n.substring(0, 1)
      className = (if (Character.isDigit(firstChar(0))) "_" + firstChar else firstChar.toUpperCase) + n.substring(1)
    }

    if (execOutput && outputSrcFile == null) {
      error("Execution disabled, specify an output file")
      execOutput = false
    }

    if (execOutput && batchingEnabled && execBatchSize <= 0) {
      error("Execution disabled, invalid batch size: " + execBatchSize)
      execOutput = false
    }

    // TODO: check runtime libs
    def checkLib(s: String) = if (new File(s).exists) { execRuntimeLibs = s :: execRuntimeLibs; true } else false

    if (execRuntimeLibs == Nil && execOutput) lang match {
      case LANG_SCALA_VANILLA | LANG_SCALA_LMS | LANG_SCALA_PARDIS => 
        if (!checkLib("lib/ddbt.jar") && !checkLib("target/scala-2.11/classes")) { 
          error("Cannot find runtime libraries")
          execOutput = false
        }
      case _ =>
    }
  }

  private def toast(repo: File, inputFile: String, lang: String, batchingEnabled: Boolean, 
                    optLevel: String, debugFlags: List[String], ivmDepth: Int): String = {

    val options = debugFlags.flatMap(f => List("-d", f)) :::
                  (if (batchingEnabled) List("--batch") else Nil) :::
                  (if (ivmDepth >= 0) List("--depth", ivmDepth.toString) else Nil) :::
                  List(optLevel, "-l", lang, inputFile)
    
    val command = (frontendPathBin :: options).toArray

    val (m3, err) = Utils.exec(command, repo, fatal = false)

    if (err.trim != "") {
      val e = new Exception(command + " failed because:\n" + err)
      e.setStackTrace(Array())
      throw e
    }
    m3
  }

  def toast(inputFile: String, lang: String, batchingEnabled: Boolean = batchingEnabled,
            optLevel: String = frontendOptLevel, debugFlags: List[String] = frontendDebugFlags,
            ivmDepth: Int = frontendIvmDepth, pathRepo: String = Utils.pathRepo): String = {

    if (inputFile == null) error("Missing input file", true)

    if (pathRepo == null) {     // If not running from sbt (development env)
      toast(null, inputFile, lang, batchingEnabled, optLevel, debugFlags, ivmDepth)
    }
    else {
      val repo = new File(pathRepo)
      val m3 = toast(repo, inputFile, lang, batchingEnabled, optLevel, debugFlags, ivmDepth)
      if(Utils.dataRepo != null)
        m3.replaceAll("../../experiments/data",  Utils.dataRepo)
      else
        m3
    }
  }

  def string2AST = M3Parser andThen TypeCheck

  def codegen(sourceM3: String, lang: String, codegenOpts: CodeGenOptions): String = {

    // Front-end phases
    val m3 = string2AST(sourceM3)

    // Back-end
    val codegen: CodeGen = lang match {
      case LANG_CPP_VANILLA => 
        new CppGen(codegenOpts)
      // case LANG_CPP_LMS => 
      //   new LMSCppGen(codegenOpts)
      case LANG_CPP_PARDIS => 
        // Set Pardis optimizer options
        val optOn = (frontendOptLevel == "-O2") || (frontendOptLevel == "-O3")
        Optimizer.analyzeEntry = optOn
        Optimizer.secondaryIndex = optOn
        Optimizer.fixedRange = optOn
        Optimizer.onlineOpts = optOn
        Optimizer.m3CompareMultiply = optOn
        Optimizer.tmpVarHoist = optOn
        Optimizer.tmpMapHoist = optOn
        Optimizer.indexInline = optOn
        Optimizer.sliceInline = optOn
        Optimizer.indexLookupFusion = optOn
        Optimizer.indexLookupPartialFusion = optOn
        Optimizer.deadIndexUpdate = optOn
        Optimizer.codeMotion = optOn
        Optimizer.refCounter = true
        Optimizer.regexHoister = optOn
        Optimizer.multiResSplitter = optOn
        // Optimizer.initialStoreSize = optOn
        Optimizer.sliceNoUpd = optOn
        Optimizer.splSecondaryIdx = optOn
        Optimizer.minMaxIdx = optOn
        Optimizer.medIdx = optOn
        Optimizer.coldMotion = optOn
        // Optimizer.profileStoreOperations = optOn
        Optimizer.parameterPromotion = true
        Optimizer.cTransformer = true 
        new PardisCppGen(codegenOpts)
      case LANG_SCALA_VANILLA => 
        new ScalaGen(codegenOpts)
      case LANG_SCALA_LMS => new 
        LMSScalaGen(codegenOpts /*, watch */)
      case LANG_SCALA_PARDIS => 
        // Set Pardis optimizer options
        val optOn = (frontendOptLevel == "-O2") || (frontendOptLevel == "-O3")
        Optimizer.analyzeEntry = optOn
        Optimizer.secondaryIndex = optOn
        Optimizer.fixedRange = optOn
        Optimizer.onlineOpts = optOn
        Optimizer.m3CompareMultiply = optOn
        Optimizer.tmpVarHoist = optOn
        Optimizer.tmpMapHoist = optOn
        Optimizer.indexInline = optOn
        Optimizer.sliceInline = optOn
        Optimizer.indexLookupFusion = optOn
        Optimizer.indexLookupPartialFusion = optOn
        Optimizer.deadIndexUpdate = optOn
        Optimizer.codeMotion = optOn
        Optimizer.refCounter = true
        Optimizer.regexHoister = optOn
        Optimizer.multiResSplitter = optOn
        // Optimizer.initialStoreSize = optOn
        Optimizer.sliceNoUpd = optOn
        Optimizer.splSecondaryIdx = optOn
        Optimizer.minMaxIdx = optOn
        Optimizer.medIdx = optOn
        Optimizer.coldMotion = optOn
        // Optimizer.profileStoreOperations = optOn
        Optimizer.parameterPromotion = true
        Optimizer.cTransformer = false
        new PardisScalaGen(codegenOpts) //DSL
      case LANG_SPARK_LMS => 
        new LMSSparkGen(codegenOpts)
      case LANG_AKKA => 
        new AkkaGen(codegenOpts)

      case _ => error("Code generation for " + lang + " is not supported", true)
    }

    codegen(m3)
  }

  def compile(lang: String, inputFile: String, outputFile: String, outputDir: File, 
              runtimeLibs: List[String], useExternalScalac: Boolean): Unit = {
    
    if (inputFile == null) {
      error("Compilation failed, input source file missing", true)
    }
    if (outputDir == null) {
      error("Compilation failed, output directory missing", true) 
    }

    if (!outputDir.exists) { outputDir.mkdirs() }

    lang match {
      case LANG_SCALA_VANILLA|LANG_SCALA_LMS|LANG_SCALA_PARDIS|LANG_AKKA =>
        Utils.scalaCompiler(outputDir,
                            runtimeLibs.mkString(":"),
                            useExternalScalac) (List(inputFile))

      case LANG_SPARK_LMS =>
        Utils.sparkCompiler(outputDir, 
                            runtimeLibs.mkString(":"), 
                            useExternalScalac) (List(inputFile))

        // Create a jar file
        val baseDir = new File("./")
        val sharedDirPath = baseDir.getAbsolutePath + "/storelib/target/scala-2.11/classes"
        val sparkDirPath = baseDir.getAbsolutePath + "/ddbtoaster/spark/target/scala-2.11/classes"
        val pkgDir = new File("./ddbtoaster/pkg")
        if (!pkgDir.exists) pkgDir.mkdirs
        Utils.exec(Array[String](
          "jar", "-cMf", (pkgDir.getAbsolutePath + "/ddbt_gen.jar"),
          "-C", outputDir.getAbsolutePath, "ddbt/test/gen",
          "-C", sharedDirPath, "ch/epfl/data/dbtoaster/lib",
          "-C", sparkDirPath, "ch/epfl/data/dbtoaster/lib/spark",
          "-C", sparkDirPath, "log4j.properties",
          "-C", sparkDirPath, "spark.config"))

      case LANG_CPP_VANILLA|LANG_CPP_LMS|LANG_CPP_PARDIS => 
        if (outputFile == null) {
          error("Compilation failed, output file name missing", true)
        }
        if (useExperimentalCppRuntimeLibrary) 
          Utils.cppCompilerNewDriver(inputFile, outputFile, null, "ddbtoaster/srccpp/lib")  
        else
          Utils.cppCompiler(inputFile, outputFile, null, "ddbtoaster/srccpp/lib")

      case _ => error("Source compilation for " + lang + " is not supported", true)
    }    
  }

  def runCpp(file: String, args: List[String], batchSize: Int, preloadInput: Boolean): (String, String) = {
    if (file == null) {
      error("Execution failed, executable file missing", true)
    }
    val execArgs = args ++ 
      (if (batchSize > 0 && !useExperimentalCppRuntimeLibrary) List("-b" + batchSize) else Nil) ++
      (if (batchSize > 0 && useExperimentalCppRuntimeLibrary) List("-b", batchSize.toString) else Nil) ++
      (if (preloadInput && useExperimentalCppRuntimeLibrary) List("--preload") else Nil) 
    Utils.cppExec(file, execArgs)
  }

  def runScala(dir: File, runtimeLibs: List[String], useExternalJVM: Boolean,
               packageName: String, className: String, args: List[String], batchSize: Int, dataset: String): (String, String) = {
    if (dir == null || !dir.exists) {
      error("Execution failed, directory with executables missing", true)
    }
    val execArgs = ("-d" + dataset) :: args ++ 
                   (if (batchSize > 0) List("-b" + batchSize) else Nil) ++ 
                   (if (timeoutMilli > 0) List("-t" + timeoutMilli) else Nil)
    Utils.scalaExec(dir :: runtimeLibs.map(new File(_)), 
                    packageName + "." + className,
                    execArgs.toArray, useExternalJVM)
  }

  def runSpark(packageName: String, className: String, args: List[String], batchSize: Int, dataset: String): (String, String) = {
    val execArgs = ("-d" + dataset) :: args ++ 
                   (if (batchSize > 0) List("-b" + batchSize) else Nil) ++
                   (if (timeoutMilli > 0) List("-t" + timeoutMilli) else Nil)
    Utils.sparkSubmit(packageName + "." + className, args.toArray)

    // useExternalJVM = true
    // Utils.sparkExec(
    //   outputExeDir :: execRuntimeLibs.map(p => new File(p)), 
    //   packageName + "." + className,
    //   ("-b" + batchSize :: args).toArray,
    //   useExternalJVM)
  }

  private def defaultRunFn(time: Long, out: String, err: String): Unit = {
    if (err.trim != "") System.err.println(err)
    else if (out.trim != "") System.out.println(out)
  }

  def compile(sourceM3: String, 
              codegenFn: (Long, String) => Unit = { (t,c) => () },
              compileFn: Long => Unit = (x => ()),
              runFn: (Long, String, String) => Unit = defaultRunFn): Unit = {

    // Codegen
    val codegenOpts =
      new CodeGenOptions(
        className, packageName, datasetName, datasetWithDeletions, execTimeoutMilli, 
        DEPLOYMENT_STATUS == DEPLOYMENT_STATUS_RELEASE, PRINT_TIMING_INFO, 
        execPrintProgress, useExperimentalCppHashMap, useExperimentalCppRuntimeLibrary)

    val (tCodegen, code) = Utils.ns(() => codegen(sourceM3, lang, codegenOpts))

    output(code, outputSrcFile)

    codegenFn(tCodegen, code)

    if (execOutput && outputSrcFile != null && outputExeDir != null) {

      // Compile generated output file    
      val (tCompile, _) = 
        Utils.ns(() => 
          compile(lang, outputSrcFile, outputExeFile, outputExeDir, execRuntimeLibs, useExternalScalac)
        )

      compileFn(tCompile)
    }
  }

  def run(dataset: String, runFn: (Long, String, String) => Unit = defaultRunFn): Unit = {
    if (execOutput && outputExeDir != null) {      
      // Run compiled files
      val (tRun, (out, err)) = Utils.ns(() =>
        lang match {
          case LANG_CPP_VANILLA | LANG_CPP_LMS | LANG_CPP_PARDIS =>
            runCpp(outputExeFile, execArgs, execBatchSize, execPreloadInput)
          case LANG_SCALA_VANILLA | LANG_SCALA_LMS | LANG_SCALA_PARDIS | LANG_AKKA =>
            runScala(outputExeDir, execRuntimeLibs, useExternalJVM, packageName, className, execArgs, execBatchSize, dataset)
          case LANG_SPARK_LMS =>
            runSpark(packageName, className, execArgs, execBatchSize, dataset)
          case _ => error("Running " + lang + " programs is not supported", true)
        }
      )
      runFn(tRun, out, err)
    }
  }

  def main(args: Array[String]): Unit = {
    parseArgs(args, true)

    if (inputFile == null) {
      showHelp()
      return
    }
    
    try {
      lang match {
        case LANG_CALC =>
          output(toast(inputFile, lang), outputSrcFile)
        case LANG_M3 | LANG_DIST_M3 =>
          output(TypeCheck(M3Parser(toast(inputFile, lang))).toString, outputSrcFile)
        case _ if M3_FILE_SUFFIX.findFirstIn(inputFile) != None =>
          compile(Utils.read(inputFile))
        case LANG_SPARK_LMS =>
          compile(toast(inputFile, LANG_DIST_M3))
        case _ =>
          compile(toast(inputFile, LANG_M3))
      }
    }
    catch { case t: Throwable =>
      val sw = new StringWriter()
      val pw = new PrintWriter(sw)
      t.printStackTrace(pw)
      error(sw.toString(), true)
    }
  }
}
