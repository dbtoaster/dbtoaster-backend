package ddbt

import java.io._
import java.util.concurrent.{ BlockingQueue, LinkedBlockingQueue }
import ddbt.lib.Helper
import ddbt.codegen.Optimizer
import Compiler._

/**
 * Benchmarking and correctness verification generator. Instruments the
 * compiler such that options can be shared. To get more information:
 *
 * Usage: sbt 'run-main ddbt.UnitTest -help'
 *
 * @author TCK
 */
object UnitTest {

  import ddbt.lib.Utils
  import ddbt.lib.Utils._
  import ddbt.ast._
  import ddbt.ast.M3
  import scala.collection.mutable.{Set => MSet}

  private val datasets = MSet[String]()           // selected datasets
  private val languages = MSet[String]()          // selected languages
  private var queryFilter = (s: String) => true   // query filter (by sql filename)

  private var runBenchmark = false                // enable benchmark
  private var verifyOutput = false                // enforce correctness verification in benchmark
  private var numRuns = 1                         // number of runs
  private var numWarmups = 0                      // number of warm-ups

  private var readMode = 2                        // input stream read mode
  private var cacheM3 = false                     // M3 cache is disabled
  private var replaceQuery = true                 // replaceQuery is enabled
  
  // query test (.sql) -> (dataset -> result set)
  private var unitTestResults = Map[String, Map[String, QueryResultSet]]()

  val skipQueries = Set(
      // front-end failure (SQL constructs not supported)
      "employee/query11.sql",
      "employee/query11a.sql",
      "employee/query12.sql",
      "employee/query17.sql",   // IS NULL
      "employee/query18.sql",   // ORDER BY
      "employee/query19.sql",
      "employee/query20.sql",
      "employee/query21.sql",
      "employee/query23.sql",   // MAX
      "employee/query24.sql",
      "employee/query34.sql",
      "employee/query41.sql",
      "employee/query44.sql",   // ANY
      "employee/query52.sql",
      "employee/query53.sql",
      "employee/query56.sql",
      "employee/query57.sql",
      "employee/query58.sql",
      "employee/query62.sql",
      "employee/query63.sql",
      "employee/query64.sql",
      "employee/query65.sql",
      "employee/query66.sql",
      "employee/query66a.sql",
      // regular expressions not supported by front-end 
      "employee/query15.sql",
      // front-end swaps table order in JOIN .. ON, test (and Scala typing) fails
      "employee/query35b.sql",
      "employee/query36b.sql",
      // too long to compile
      "mddb/query3.sql",
      "finance/missedtrades.sql",
      "finance/chrissedtrades.sql",
      // dataset missing
      "simple/matrixmult.sql",
      "simple/r_case2.sql",
      // Nested subqueries not supported outside of aggregates
      "simple/selectnesting.sql",
      "simple/type_mappings.sql"
    )

  private val pathExamples = "examples/queries"
  private val pathSources = "ddbtoaster/test/gen"
  private val pathClasses = "ddbtoaster/target/scala-2.11/test-classes"
  private val pathM3 = "ddbtoaster/target/m3"

  private var zeusEnabled = false      // zeus mode
  private var zeusSeed = 0             // zeus seed  


  private var csv: PrintWriter = null
  private var csvFile: String = null

  private var tmpDir = makeTempDir() //(auto_delete=false)

  private val samplePattern = "(?m)(SAMPLE = (.*), (.*), (.*), (.*)\n)?(?s)(.*)".r

  private def tf(ns: Long) = "%7s".format(time(ns, false))

  private def print(k: String, v: String) = { 
    System.out.println("%-70s".format("%-30s".format(k) + ": " + v))
  }

  private val repo = if (Utils.pathRepo != null) new File(Utils.pathRepo) else null

  private val find = if (Utils.pathFindBin != null) Utils.pathFindBin else "find"

  def findQueries: Array[String] = {
    if (repo != null) {
      val (out, _) = exec(Array(find, "test/queries", "-name", "*.sql", "-and", "-not", "-name", "schemas*.sql"), repo)
      out.split("\n")
    }
    else if (new File(pathExamples).exists) {
      val (out, _) = exec(Array(find, pathExamples, "-name", "*.sql", "-and", "-not", "-name", "schemas*.sql"))
      out.split("\n")
    }
    else Array()
  }

  def loadUnitTests: Map[String, Map[String, QueryResultSet]] = {
    if (repo != null) {
      val (out, _) = exec(Array(find, "test/unit/queries", "-type", "f"), repo)
      out.split("\n").filterNot(_ contains "/.")      // to exclude test/unit/queries/.DS_Store
         .map(f => UnitParser(read(repo.getPath + "/" + f)))
         .map(queryTest => queryTest.sql -> queryTest.queryResultsByDataset).toMap
    }
    else Map()
  }  

  def parseArgs(args: Array[String]) = {    
    val qinc = MSet[String]()
    val qexcl = MSet[String]()
    var qfail = false

    var as = List[String]()
    var i = 0
    def eat(f: String => Unit, s: Boolean = false) { 
      i += 1
      if (i < args.length) f(if (s) args(i).toLowerCase else args(i)) 
    }
    while (i < args.length) { args(i) match {
        case "-d" => eat(s => datasets += s, true)
        case "-dd" => datasets += ("tiny", "tiny_del", "standard", "standard_del")
        case "-l" => eat(s => languages += s, true)
        case "-q" => eat(s => qinc += s)
        case "-qx" => eat(s => qexcl += s)        
        case "-qfail" => qfail = true
        case "-x" => runBenchmark = true
        case "-v" => verifyOutput = true
        case "-r" => eat(s => numRuns = s.toInt)
        case "-w" => eat(s => numWarmups = s.toInt)
        case "-p" => eat(s => readMode = s.toInt)
        case "-z" => zeusEnabled = true
        case "-seed" => eat(s => zeusSeed = s.toInt)
        case "-cache" => cacheM3 = true
        case "-noreplace" => replaceQuery = false
        case "-csv" => eat(s => csvFile = s)
        case "-h" | "-help" | "--help" => 
          error("Usage: Unit [options] [compiler options]")
          error("Filtering options:")
          error("  -d <dataset>  add a dataset")
          error("  -dd           add tiny, tiny_del, standard, standard_del datasets")
          error("  -l <lang>     add language: " + 
                                  List(
                                    LANG_CPP_VANILLA, LANG_CPP_LMS, LANG_CPP_PARDIS, 
                                    LANG_SCALA_VANILLA, LANG_SCALA_LMS, LANG_SCALA_PARDIS, 
                                    LANG_SPARK_LMS, LANG_AKKA
                                  ).mkString(", ") /* + " (_spec|_full|_0-10)?" */)
          error("  -q <filter>   add an inclusion filter for queries")
          error("  -qx <filter>  add an exclusion filter for queries")
          error("  -qfail        also include queries that are known to fail")
          error("Benchmarking options:")
          error("  -x            enable benchmarks (compile and execute)")
          error("  -v            verification against reference result")
          error("  -r <n>        number of runs (default = 1)")
          error("  -w <n>        number of warm-ups (default = 0)")
          error("  -p <mode>     parallel streams: 0 = off" /*+", 1 = thread"*/ + ", 2 = deterministic (default)")

          error("  -csv <file>   store benchmark results in a file")
          error("  -cache        enable M3 cache")
          error("  -xbs <n>      execute with batches of certain size")
          error("  -noreplace    disable replacing generated trigger programs, if any exists")

          error("Zeus mode:")
          error("  -z            enable zeus mode")
          error("  -r <n>        number of runs to test (default: 10, 0=infinite)")
          error("  -seed <int>   set the seed to test (implies 1 sample)")
          error("")
          error("Other options are forwarded to the compiler:")
          Compiler.parseArgs(Array[String](), true)
        case s => as = s :: as
      }
      i += 1 
    }
    if (verifyOutput && as.contains("--no-output")) { 
      sys.error("Result validation is impossible while the --no-output option is enabled.\n" +
                "Disable one of these options (-v or --no-output) and try again.") 
    }

    if (datasets.isEmpty) datasets += "standard"

    if (languages.isEmpty) languages += DEFAULT_LANG_CPP
    
    if (qinc.size > 0) {
      val pattern = (".*(" + qinc.mkString("|") + ")(\\.sql)?$").r
      queryFilter = (s: String) => pattern.findFirstIn(s) != None
    }
    if (qexcl.size > 0) { 
      val pattern = (".*(" + qexcl.mkString("|") + ")(\\.sql)?$").r
      val q0 = queryFilter
      queryFilter = (s: String) => q0(s) && pattern.findFirstIn(s) == None
    }
    if (!qfail) { 
      val q0 = queryFilter
      println("Front-end skip   : %4d".format(skipQueries.size))
      queryFilter = (s: String) => !skipQueries.exists(s.endsWith) && q0(s) 
    }
    
    Compiler.parseArgs(as.reverse.toArray, true)
  }

  def toast(lang: String, inputFile: String, name: String) = {
    val ext = Compiler.frontendFileExtensions(lang)
    var outputFile = "ddbtoaster/target/m3/" + name + "." + ext
    if (cacheM3 && new File(outputFile).exists)
        Utils.ns(() => Utils.read(outputFile))
    else {
      val queryName = if (replaceQuery) name
                      else Utils.generateNewFileName(name, "ddbtoaster/target/m3/%s." + ext)
      outputFile = "ddbtoaster/target/m3/" + queryName + "." + ext
      val (t, src) = Utils.ns(() => Compiler.toast(inputFile, lang))
      Utils.write(outputFile, src)
      print("SQL -> " + lang.toUpperCase, tf(t))
      (t, src)
    }
  }
  
  def main(args: Array[String]): Unit = {

    parseArgs(args)

    // TODO: Zeus mode
    if (zeusEnabled) { 
      testZeus()
      return 
    }

    val total = findQueries
    val selected = total.filter(queryFilter).sorted

    println("Queries total    : %4d".format(total.size))
    println("Queries selected : %4d".format(selected.size))
    
    if (selected.isEmpty) { 
      error("No queries selected, exiting...", true)
    }

    if (verifyOutput) {
      unitTestResults = loadUnitTests
    }

    // directory cleanup (erase previous tests)
    val outputDir = new File(pathSources)
    if (!outputDir.exists) outputDir.mkdirs()
    outputDir.listFiles().foreach(_.delete())

    val cacheDir = new File(pathM3)
    if (!cacheDir.exists) cacheDir.mkdirs


    if (csvFile != null) {
      csv = new PrintWriter(new File (csvFile + stringIf(!csvFile.endsWith(".csv"), ".csv")))
    }

    if (csv != null) {
      csv.println(
        ( List("Query", "Dataset", "Language", "BatchSize", "SQLtoM3", "M3toCode", "AvgTime", "AvgRate") ++
          (1 to numRuns).flatMap(i => List("Time" + i, "ProcTuples" + i, "SkipTuples" + i))).mkString(", "))
    }

    for (query <- selected) {
      try {   
        var queryName = query.replaceAll("test/queries/|.sql", "")
        Optimizer.infoFileName = queryName

        println("---------[[ " + queryName + " ]]---------")
               
        val frontendExt = languages.map(Compiler.frontendFileExtensions(_)).toSet

        val (timeM3, codeM3) = 
          if (frontendExt.contains("m3")) toast(LANG_M3, query, queryName) else (-1L, "")
        val (timeDM3, codeDM3) = 
          if (frontendExt.contains("dm3")) toast(LANG_DIST_M3, query, queryName) else (-1L, "")

        val t0 = if (timeM3 != -1L) timeM3 else timeDM3

        for (dataset <- datasets) {
          for (lang <- languages) lang match {
            case LANG_SCALA_VANILLA|LANG_SCALA_LMS|LANG_SCALA_PARDIS|LANG_SPARK_LMS => 
              val className = queryName.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]", "").capitalize
              testQueryScala(query, className, dataset, lang, tmpDir, codeM3)
            case LANG_CPP_VANILLA | LANG_CPP_LMS | LANG_CPP_PARDIS => 
              val exeName = queryName.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]", "").capitalize
              testQueryCpp(query, exeName, dataset, lang, tmpDir, codeM3)
            case _ => sys.error("Language is not supported: " + lang)
          }
        }
      }
      catch {
        case e: Exception => e.printStackTrace
      }

      System.gc
    }
    if (csv != null) csv.close
  }

  // ---------------------------------------------------------------------------
  // Zeus mode
  def testZeus() = {
    val num = if (zeusSeed != 0) 1 else numRuns
    numRuns = 1; numWarmups = 0; runBenchmark = true
    for (i <- 1 to num) {
      val (out, _) = exec("ddbtoaster/scripts/zeus.rb" + stringIf(zeusSeed != 0, " -s " + zeusSeed), true)
      val dataset = "tiny"
      val sql = out.replaceAll("@@DATA@@", pathRepo + "/../../experiments/data/simple/tiny")
      val ma = java.util.regex.Pattern.compile("^-- seed *= *([0-9]+).*").matcher(sql.split("\n")(0))
      val id = if (ma.matches) ma.group(1).toLong else sys.error("No seed")
      println("---------[[ Zeus " + id + " ]]---------")

      val queryName = if (replaceQuery) "zeus" + id 
                      else Utils.generateNewFileName("zeus" + id, tmpDir + "/%s.sql")
      val fileName = tmpDir.getPath + "/" + queryName + ".sql"
      val codeM3 = {
        write(fileName, sql)
        Compiler.toast(fileName, "m3", pathRepo = null)
      }
      for (lang <- languages) lang match {
        case LANG_SCALA_VANILLA | LANG_SCALA_LMS | LANG_SCALA_PARDIS | LANG_SPARK_LMS =>
          val className = queryName.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]", "").capitalize
          testQueryScala(fileName, className, dataset, lang, tmpDir, codeM3)
        case LANG_CPP_VANILLA | LANG_CPP_LMS | LANG_CPP_PARDIS =>
          val exeName = queryName.replaceAll("tmp/|test/queries/|finance/|simple/|/query|.sql|[/_]", "").capitalize
          testQueryCpp(fileName, exeName, dataset, lang, tmpDir, codeM3)
        case _ => sys.error("Language is not supported: " + lang)
      }
    }
  }

  def verifyResult(output: String, queryFile: String, dataset: String, queries: Map[String, List[(String, Type)]]) = {
    import scala.xml._
    import ddbt.lib.TypeHelper

    val startIdx = output.indexOf("<snap>")
    val endIdx = output.indexOf("</snap>")+"</snap>".length
    val snap = XML.loadString(output.substring(startIdx, endIdx))

    unitTestResults.get(queryFile) match {
      case Some(m) => m.get(dataset) match {
        case Some(resultSet) => 
          queries.foreach { case (qname, schema) => 
            val keys = schema.dropRight(1)
            val value = schema.last

            resultSet.queryResultByName.get(qname) match {
              case Some(QueryResultMap(m)) =>
                val res = (snap \ qname \ "item").map { item =>
                    ( keys.map { case (k, tp) =>
                       TypeHelper.fromString((item \ k.toUpperCase).text, tp)
                      },
                      TypeHelper.fromString((item \ value._1).text, value._2) )
                  }.toMap
                val refRes = m.map { case (kList, v) =>
                    ( (kList zip keys).map { case (kv, (_, tp)) =>
                        TypeHelper.fromString(kv, tp)
                      },
                      TypeHelper.fromString(v, value._2) )
                  }    
                Helper.diff(res, refRes)

              case Some(QueryResultFile(path, sep)) =>
                val res = (snap \ qname \ "item").map { item =>
                    ( keys.map { case (k, tp) =>
                       TypeHelper.fromString((item \ k.toUpperCase).text, tp)
                      },
                      TypeHelper.fromString((item \ value._1).text, value._2) )
                  }.toMap
                val refRes = 
                  Helper.loadCSV(
                    l => (l.dropRight(1), l.last),
                    Utils.pathRepo + "/" + path,
                    (keys.map(_._2) ::: List(value._2)).mkString(","),
                    (if (sep != null) "\\Q" + sep.replaceAll("\\\\\\|", "|") + "\\E" else ",")
                  )
                Helper.diff(res,refRes)

              case Some(QueryResultSingleton(v)) =>
                val res = TypeHelper.fromString((snap \ qname).text, value._2)
                val refRes = TypeHelper.fromString(v, value._2)
                Helper.diff(res, refRes)

              case None => error("Unexpected result type")
            }
          }
        case None =>
          warning("Verification failed, test result missing for " + queryFile + " and " + dataset + " dataset")
          val e = new Exception
          e.setStackTrace(Array[StackTraceElement]())
          throw e
      }
      case None => 
        warning("Verification failed, test result missing for " + queryFile)
        val e = new Exception
        e.setStackTrace(Array[StackTraceElement]())
        throw e
    }
  }

  def testQueryCpp(sqlFile: String, queryName: String, dataset: String, 
                   lang: String,  dir: File, sourceM3: String) = {
    val langID = lang match {
        case LANG_CPP_VANILLA => "VCpp"
        case LANG_CPP_LMS => "LMSCpp"
        case LANG_CPP_PARDIS => "Cpp"
        case _ => sys.error("Unknown lang: " + lang)
      }
    val exeFile = dir.getPath + "/" + queryName + langID

    val args =  List( "-l", lang, 
                      "-o", exeFile + "." + Compiler.backendFileExtensions(lang),
                      "-xa", "-p" + readMode) ++
                (if (runBenchmark) List("-x", "-c", exeFile) else Nil)
                
    Compiler.parseArgs(args.toArray)

    val sampleRecorder = SampleRecorder(queryName, dataset, langID, Compiler.batchSize)

    def codegenFn(t: Long, code: String) = {
      print(langID + " codegen", tf(t))
      sampleRecorder.recordCodegenTime(Math.round(t / 1000000.0))
    }
    
    def compileFn(t: Long) = {
      print(langID + " compile", tf(t))
      sampleRecorder.recordCompileTime(Math.round(t / 1000000.0))
    }
    
    Compiler.compile(sourceM3, codegenFn, compileFn)

    def runFn(t: Long, out: String, err: String) = {
      if (err.trim != "") {
        System.err.println(err)
      }
      else if (verifyOutput) {
        val samplePattern(sample, _, timeMicro, count, skipped, result) = out

        if (sample != null) {
          sampleRecorder.recordRunInfo(Math.round(timeMicro.toLong / 1000.0), count.toLong, skipped.toLong)
        }

        import ddbt.codegen.CppGen

        val m3 = Compiler.string2AST(sourceM3)

        val queries = 
          m3.queries.map { q =>
            val schema = q.expr.ovars 
            val (keys, value) = 
              if (lang == LANG_CPP_PARDIS) 
                (schema.zipWithIndex.map { case ((n, tp), i) => ("_" + (i + 1), tp) }, 
                 ("_" + (schema.size + 1), q.expr.tp))
              else
                (schema, (CppGen.VALUE_NAME, q.expr.tp))
            q.name -> (keys ++ List(value))
          }.toMap 

        try {
          verifyResult(out, sqlFile, dataset, queries)
          print(langID + " verification", "%7s".format("OK"))
        }
        catch { case ex: Exception => 
          print(langID + " verification", "%7s".format("FAILED"))
          ex.printStackTrace()
        }
      }
    }

    (1 to numWarmups).foreach(x => 
      Compiler.run((t, out, err) => ())
    )

    (1 to numRuns).foreach(x => 
      Compiler.run(runFn)
    )

    print(langID + " run " + dataset, 
          "%7.03f".format(sampleRecorder.avgTimeMilli / 1000.0) +
          "%11.1f tup/s".format(sampleRecorder.avgRefreshRate) + 
          "%10s".format("(" + numRuns + " runs)"))

    if (csv != null) csv.println(sampleRecorder.toCSV)
  }

  def testQueryScala(sqlFile: String, queryName: String, dataset: String, 
                     lang: String,  dir: File, sourceM3: String) = {
    val langID = lang match {
        case LANG_SCALA_VANILLA => "VScala"
        case LANG_SCALA_LMS => "LMSScala"
        case LANG_SCALA_PARDIS => "Scala"
        case LANG_SPARK_LMS => "Spark"
        case _ => sys.error("Unknown lang: " + lang)
      }

    val className = queryName + langID
    val outputSrcFile = dir.getPath + "/" + className

    val args =  List( "-l", lang, 
                      "-o", outputSrcFile + "." + Compiler.backendFileExtensions(lang),
                      "-xd", pathClasses,
                      "-n", "ddbt.test.gen." + className,
                      "-xa", "-p" + readMode) ++
                (if (runBenchmark) List("-x") else Nil) ++
                (if (verifyOutput) List("-xa", "-m1") else Nil) ++
                (if (Utils.isLMSTurnedOn) List("-xsc") else Nil)
                
    Compiler.parseArgs(args.toArray)

    val sampleRecorder = SampleRecorder(queryName, dataset, langID, Compiler.batchSize)

    def codegenFn(t: Long, code: String) = {
      print(langID + " codegen", tf(t))
      sampleRecorder.recordCodegenTime(Math.round(t / 1000000.0))
    }
    
    def compileFn(t: Long) = {
      print(langID + " compile", tf(t))
      sampleRecorder.recordCompileTime(Math.round(t / 1000000.0))
    }

    Compiler.compile(sourceM3, codegenFn, compileFn)
    
    def runFn(t: Long, out: String, err: String) = {
      if (err.trim != "") {
        System.err.println(err)
      }
      else if (verifyOutput) {
        val samplePattern(sample, _, timeMilli, count, skipped, result) = out

        if (sample != null) {
          sampleRecorder.recordRunInfo(timeMilli.toLong, count.toLong, skipped.toLong)
        }

        import ddbt.codegen.ScalaGen

        val m3 = Compiler.string2AST(sourceM3)

        val queries = 
          m3.queries.map { q =>
            val keys = q.expr.ovars 
            val value = (ScalaGen.VALUE_NAME, q.expr.tp)
            q.name -> (q.expr.ovars ++ List(value))
          }.toMap 

        try {
          verifyResult(result, sqlFile, dataset, queries)
          print(langID + " verification", "%7s".format("OK"))
        }
        catch { case ex: Exception => 
          print(langID + " verification", "%7s".format("FAILED"))
          ex.printStackTrace()
        }
      }
    }

    (1 to numWarmups).foreach(x => 
      Compiler.run((t, out, err) => ())
    )

    (1 to numRuns).foreach(x => 
      Compiler.run(runFn)
    )

    print(langID + " run " + dataset, 
          "%7.03f".format(sampleRecorder.avgTimeMilli / 1000.0) +
          "%11.1f tup/s".format(sampleRecorder.avgRefreshRate) + 
          "%10s".format("(" + numRuns + " runs)"))

    if (csv != null) csv.println(sampleRecorder.toCSV)
  }

  case class SampleRecorder(query: String, dataset: String, lang: String, batchSize: Long) {

    private val runInfo = scala.collection.mutable.ArrayBuffer[(Long, Long, Long)]()

    private var codegenTimeMilli = 0L

    private var compileTimeMilli = 0L

    def recordCodegenTime(timeMilli: Long) = codegenTimeMilli = timeMilli

    def recordCompileTime(timeMilli: Long) = compileTimeMilli = timeMilli

    def recordRunInfo(timeMilli: Long, numProcessedTuples: Long, numSkippedTuples: Long) =
      runInfo += ((timeMilli, numProcessedTuples, numSkippedTuples))

    def avgTimeMilli = if (runInfo.isEmpty) 0L else Math.round(runInfo.map(_._1.toDouble).sum / runInfo.size)

    def avgRefreshRate = if (runInfo.isEmpty) 0.0 else runInfo.map(x => x._2.toDouble / x._1 * 1000).sum / runInfo.size

    def toCSV =
      ( List(query, dataset, lang, batchSize.toString, 
             "%1.3f".format(codegenTimeMilli / 1000.0), 
             "%1.3f".format(compileTimeMilli / 1000.0), 
             "%1.3f".format(avgTimeMilli / 1000.0), 
             "%1.2f".format(avgRefreshRate)) ++
        runInfo.map { case (t, count, skip) => s"""${"%1.3f".format(t / 1000.0)}, $count, $skip""" }
      ).mkString(", ")
  }

  // ---------------------------------------------------------------------------
  // AST of query unit tests
  abstract sealed class QueryResult
  case class QueryResultMap(m: Map[List[String], String]) extends QueryResult
  case class QueryResultFile(path: String, sep: String = null) extends QueryResult
  case class QueryResultSingleton(v: String) extends QueryResult

  case class QueryResultSet(subs: List[(String, String)] = Nil, queryResultByName: Map[String, QueryResult] = Map())

  case class QueryTest(sql: String, queryResultsByDataset: Map[String, QueryResultSet] = Map(("standard",QueryResultSet()))) { 
    override def toString = 
      sql + ind(queryResultsByDataset.map { case (k, v) => "\n - " + k + ": " + v.queryResultByName.toString }.mkString) 
  }

  // Parser for unit tests declarations
  import scala.util.parsing.combinator.RegexParsers
  object UnitParser extends RegexParsers {
    
    lazy val str = "\"" ~> """(\\.|[^\"])*""".r <~ "\"" | "'" ~> """(\\.|[^'])*""".r <~ "'"

    lazy val num = "-?[0-9]+(\\.[0-9]*)?([eE][\\-+]?[0-9]+)?".r ^^ {
        case x => x // if (x.matches("^-?[0-9]+$")) x + "L" else x
      }

    lazy val pat = "/" ~> """(\\.|[^/])*""".r <~ "/" ^^ {
        _.replaceAll("\\\\/","/")
      } // might need a better solution
   
    lazy val qrow = ("[" ~> repsep(num|(str ^^ { s => "\"" + s + "\"" }), ",") <~ "]") ~ ("=>" ~> num) ^^ { 
        case cs ~ n => (cs, n)
      }

    lazy val qmap: Parser[QueryResult] =
      "{" ~> repsep(qrow, ",") <~ opt(",") <~ "}" ^^ {
        case rs => QueryResultMap(rs.toMap)
      }

    lazy val qfile: Parser[QueryResult] =
      ("results_file" ~> "(" ~> str) ~ (opt("," ~> pat) <~ ")") ^^ {
        case f ~ op => QueryResultFile(f, op match { case Some(p) => p case None => null })
      }
    
    lazy val qout =
      "{"~>":type"~>"=>"~> ((":onelevel"~>","~>":expected"~"=>"~>(qfile|qmap)) |
                            (":singleton"~>","~>":expected"~>"=>"~>num ^^ {
                              case n => QueryResultSingleton(n) })) <~ opt(",") <~"}" ^^ {
        case q => q
      }
    
    lazy val qsub = ("[" ~> pat <~ ",") ~ (str <~ "]") ^^ {
        case p ~ r => (p, r)
      }

    lazy val qset = "{" ~> opt(":subs" ~> "=>" ~> "[" ~> repsep(qsub,",") <~ "]" <~ ",") ~ (":toplevels" ~> "=>" ~> map(qout)) <~ "}" ^^ {
        case ss ~ os => QueryResultSet(ss match { case Some(s) => s case None => Nil }, os)
      }
    
    lazy val qtest = 
      ("{" ~> ":path" ~> "=>" ~> str <~ ",") ~ 
      (":datasets" ~> "=>" ~> map(qset) <~ "}") ^^ {
        case n ~ qs => QueryTest(n, qs)
      }

    private def map[T](p:Parser[T]) = 
      "{" ~> repsep((str <~ "=>") ~ p, ",") <~ "}" ^^ { 
        case rs => rs.map { case n ~ v => (n, v) }.toMap 
      } // JSON-like map String -> T

    def apply(input: String): QueryTest =
      parseAll(qtest, input) match {
        case Success(r, _) => r
        case f => sys.error(f.toString)
    }
  }
}
