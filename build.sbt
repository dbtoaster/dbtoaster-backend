lazy val commonSettings = Seq(
  // --------- Project information
  organization := "ch.epfl.data",
  version := "3.0",

  // --------- Compilation options
  scalaVersion := "2.11.11",    // LMS requires 2.11.2 --> root uses the same
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target", "1.6"),
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-target:jvm-1.6" /* , "-Yinline-warnings" */),

  // --------- Dependencies
  resolvers += Resolver.sonatypeRepo("snapshots")
)  

lazy val storelib = Project(id = "storelib", base = file("storelib"), settings = commonSettings)

lazy val core = Project(id = "core", base = file("ddbtoaster/core"), settings = commonSettings) dependsOn (storelib)

lazy val sparklib = Project(id = "sparklib", base = file("ddbtoaster/spark"), settings = commonSettings) dependsOn (storelib) 

lazy val lms = Project(id = "lms", base = file("ddbtoaster/lms"), settings = commonSettings) dependsOn (storelib, core, sparklib)

lazy val pardis = Project(id = "pardis", base = file("ddbtoaster/pardis"), settings = commonSettings) dependsOn (storelib, core)

lazy val root = Project(id = "DBToaster", base = file("."), settings = commonSettings) dependsOn(core, lms, pardis) aggregate(core, sparklib, lms, pardis, storelib)

lazy val runtime = Project(id = "Runtime", base = file("runtime"), settings = commonSettings) dependsOn(storelib, pardis)

Seq(
  // --------- Project information
  name := "dbtoaster",

  // --------- Paths
  scalaSource in Compile <<= baseDirectory / "ddbtoaster/src",
  javaSource in Compile <<= baseDirectory / "ddbtoaster/src",
  sourceDirectory in Compile <<= baseDirectory / "ddbtoaster/src",
  scalaSource in Test <<= baseDirectory / "ddbtoaster/test",
  javaSource in Test <<= baseDirectory / "ddbtoaster/test",
  sourceDirectory in Test <<= baseDirectory / "ddbtoaster/test",
  resourceDirectory in Compile <<= baseDirectory / "ddbtoaster/conf",

  // --------- Execution options
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m", "-XX:-DontCompileHugeMethods", "-XX:+CMSClassUnloadingEnabled"), // ,"-Xss512m"
  javaOptions ++= Seq("-Xmx4G", "-Xms1G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath=" + cp.files.absString) // propagate paths
)

// --------- LMS codegen, enabled with ddbt.lms = 1 in conf/ddbt.properties
{
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) } 
  catch { case _: Throwable => }

  if (prop.getProperty("ddbt.lms", "0") == "0") Seq() 
  else Seq(
      scalaVersion := "2.11.2",
      scalaOrganization := "org.scala-lang.virtualized",
      scalacOptions ++= List("-Yvirtualize")
    )
}

mainClass in run in Compile := Some("ddbt.Compiler")

packSettings

packMain := Map("compiler" -> "ddbt.Compiler")

addCommandAlias("toast", ";runMain ddbt.Compiler ") ++
addCommandAlias("unit", ";runMain ddbt.UnitTest ") 

// // --------- Custom tasks
val LANG_SCALA = "vscala"
val LANG_SCALA_SC = "scala"

addCommandAlias("queries", "unit -dd -v -x -s 0 -l " + LANG_SCALA_SC + " ")
// addCommandAlias("queries-lms", "unit -dd -v -x -s 0 -l lms -xsc ") ++
// addCommandAlias("queries-akka", "unit -dd -v -x -s 0 -l akka -qx mddb/query2 -qx tpch/query21 ") // too long to compile/execute

// // Akka individual queries testing
// addCommandAlias("aq","unit -dd -v -x -s 0 -l akka -q ")

// addCommandAlias("bench", ";unit -v -x -xsc -xvm -csv bench.csv -l ") ++ // usage: sbt 'bench lms'
// addCommandAlias("bench-all", ";unit -v -x -xsc -xvm -csv bench-all.csv -l " + LANG_SCALA + " -l " + LANG_SCALA_SC + " -l lscala -l llms ") ++ // usage: sbt 'bench-all'
// //addCommandAlias("bench-all-tpch", ";unit -p 2 -x -xsc -xvm -csv bench-all.csv -dump bench-all-dump.txt -l lscala -l llms -l "+LANG_SCALA+" -l "+LANG_SCALA_SC+" -l cpp -l lcpp -w 2 -s 3 -t 60000 -d big_del -q tpch.*query[0-9]+.sql ")
// addCommandAlias("bench-all-tpch", ";unit -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000 -csv bench-all.csv -dump bench-all-dump.txt -l " + LANG_SCALA + " -l " + LANG_SCALA_SC + " -l cpp -d big_del -q tpch.*query[0-9]+ ")


// addCommandAlias("test-regression-cpp-single", 
//                 ";unit -xsc -xvm -p 2 -l cpp -v -x" +
//                 ";unit -xsc -xvm -p 2 -l cpp -v -x -q finance.* -qx finance/missedtrades -d big")


commands += Command.command("release")((state: State) => {
  def copyFile(file: File, targetDir: File) = { 
    if (!targetDir.exists) targetDir.mkdirs
    IO.copyFile(file, targetDir/file.getName)
  }
  def copyFiles(files: Iterable[File], targetDir: File) = { 
    if (!targetDir.exists) targetDir.mkdirs
    files.foreach { f => IO.copyFile(f, targetDir/f.getName) } 
  }
  def copyDir(sourceDir: File, targetDir: File) = { 
    if (!targetDir.exists) targetDir.mkdirs
    IO.copyDirectory(sourceDir, targetDir, true) 
  }
  def read(file: String): String = { 
    val f = new File(file)
    val cs = new Array[Char](f.length.toInt)
    val r = new java.io.FileReader(f)
    r.read(cs)
    r.close
    new String(cs) 
  }
  def write(file: String, data: String) = { 
    val f = new File(file)
    val dir = f.getParentFile
    if (dir != null && !dir.exists) dir.mkdirs
    val o = new java.io.PrintWriter(f)
    o.write(data)
    o.close() 
  }
  def fixSqlFiles(files: Iterable[File], targetDir: File) = { 
    if (!targetDir.exists) targetDir.mkdirs

    def fixSQL(input:String) = {
      var output_next_blank = false
      (new scala.collection.immutable.StringOps(input)).lines.map { l =>
        l.replace("../../experiments", "examples")
         .replace("test/queries", "examples/queries")
         .replace("standard/", "")
         .replace("tiny/", "")
         .replace("big/", "")
         .replace("data/finance/finance.csv", "data/finance.csv")
         .replace("../alpha5/", "")
         .replaceAll("--.*", "") + IO.Newline
      }.filter { l =>
        if(!l.trim.isEmpty) { output_next_blank = true; true }
        else if(output_next_blank) { output_next_blank = false; true }
        else false
      }.mkString
    }

    files.foreach { f => 
      write((targetDir/f.getName).getAbsolutePath(), fixSQL(read(f.getAbsolutePath()))) 
    } 
  }
  
  // load all the properties
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) } 
  catch { case _: Throwable => }

  println("defining base and release paths")
  val baseDir = baseDirectory.value/"ddbtoaster"
  val releaseDir = baseDir/"release"

  println("cleaning")
  IO.delete(releaseDir/"bin"/"dbtoaster_frontend")
  IO.delete(releaseDir/"CHANGELOG")
  IO.delete(releaseDir/"LICENSE")
  IO.delete(releaseDir/"README")
  IO.delete(releaseDir/"doc")
  IO.delete(releaseDir/"examples")
  IO.delete(releaseDir/"lib")

  println("compiling sources")
  val compilerFilePath = (baseDir/"src/Compiler.scala").getAbsolutePath
  val compilerClassContent = read(compilerFilePath)
  write(compilerFilePath, compilerClassContent.replace("= DEPLOYMENT_STATUS_DEVELOPMENT", "= DEPLOYMENT_STATUS_RELEASE"))
  Project.runTask(compile, state)

  println("execute pack task")
  Project.runTask(pack, state)

  println("copy all the Scala dependency libraries")
  val sourceDir = baseDirectory.value/"target"/"pack"/"lib";
  if (sourceDir.exists) {
    val targetDir = releaseDir/"lib"/"dbt_scala"
    targetDir.mkdirs

    copyFiles(IO.listFiles(sourceDir).filter { _.getName.matches(
      "(akka-actor|config|scala-library|scala-reflect|scala-parser-combinators|scala-xml" + 
      "|sc-shared|sc-pardis-compiler|sc-pardis-core-compiler|sc-pardis-library|sc-pardis-quasi|scala-yinyang|squid-sc-backend" +
      "|dbtoaster|lms|scalariform).*") }, targetDir)

    val ddbtJar = targetDir/s"dbtoaster_${scalaBinaryVersion.value}-${version.value}.jar"
    if (prop.getProperty("ddbt.lms","0") != "1") { // vanilla scala
      println(s"using vanilla Scala + PARDIS version using dbtoaster_${scalaBinaryVersion.value}-${version.value}.jar")
      IO.copyFile(ddbtJar, targetDir/s"dbtoaster-${version.value}.jar")
    } 
    else { // lms
      println(s"using Scala + LMS version using dbtoaster_${scalaBinaryVersion.value}-${version.value}.jar")
      IO.copyFile(ddbtJar, targetDir/s"dbtoaster-${version.value}-lms.jar")
    }
    IO.delete(ddbtJar)
  } else {
    println("Libraries (in " + sourceDir + ") are not created via pack command.")
  }

  println("copy dbtoaster_release")
  val frontendRepo = file(prop.getProperty("ddbt.base_repo",""))
  if (frontendRepo != "") {
    val currentBranchPath = frontendRepo/"/dbtoaster"/"compiler"/"alpha5"
    
    println("make dbt_release")
    ("make -C " + currentBranchPath.getAbsolutePath)!;
    
    println("copy dbt_release")
    val dbtBinPath = currentBranchPath/prop.getProperty("ddbt.dbtoaster.frontend", "bin/dbtoaster_release")
    copyFile(dbtBinPath, releaseDir/"bin")
    ("mv " + (releaseDir/"bin"/dbtBinPath.getName).getAbsolutePath + " " + (releaseDir/"bin"/"dbtoaster_frontend").getAbsolutePath)!;
    ("chmod +x " + (releaseDir/"bin"/"dbtoaster_frontend").getAbsolutePath)!;
    
    println("copy README, LICENSE and CHANGELOG")
    copyFile(currentBranchPath/"doc"/"README", releaseDir)
    copyFile(currentBranchPath/"doc"/"LICENSE", releaseDir)
    copyFile(currentBranchPath/"doc"/"CHANGELOG", releaseDir)
    
    println("copy docs to doc dir")
    val releaseDocDir = releaseDir/"doc"
    releaseDocDir.mkdirs
    copyFiles(
      List("9.jpg", "bakeoff.png", "bluetab.gif", "bluetabactive.gif", "dbtoaster-logo.gif",
           "favicon.ico", "internal_arch.png", "perf.png", "schematic.png")
        .map(f => currentBranchPath/"doc"/"site_html"/f),
      releaseDocDir)
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html").filter(f => f.getName.endsWith(".html") && !f.getName.startsWith("samples_")), releaseDocDir)
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html"/"css").filter(_.getName.endsWith(".css")), releaseDocDir/"css")
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html"/"js").filter(_.getName.endsWith(".js")), releaseDocDir/"js")

    println("make c++ libs")
    val cppLibDir = baseDir/"srccpp"/"lib"    
    ("make -C " + cppLibDir.getAbsolutePath)!;

    println("copy c++ libs")
    val releaseCppLibDir = releaseDir/"lib"/"dbt_c++"
    releaseCppLibDir.mkdirs
    (releaseCppLibDir/"hpds").mkdirs
    (releaseCppLibDir/"mmap").mkdirs
    (releaseCppLibDir/"smhasher").mkdirs
    copyFiles(IO.listFiles(cppLibDir).filter { f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".h") || f.getName.endsWith(".a") || "makefile" == f.getName }, releaseCppLibDir)
    copyFiles(IO.listFiles(cppLibDir/"hpds").filter { f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".a") || "makefile" == f.getName }, releaseCppLibDir/"hpds")
    copyFiles(IO.listFiles(cppLibDir/"mmap").filter { f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".a") || "makefile" == f.getName }, releaseCppLibDir/"mmap")
    copyFiles(IO.listFiles(cppLibDir/"smhasher").filter { f => f.getName.startsWith("MurmurHash2") }, releaseCppLibDir/"smhasher")

    println("copy main.cpp")
    copyFile(currentBranchPath/"lib"/"dbt_c++"/"main.cpp", releaseDir/"examples"/"code")

    // println("make scala libs")
    // val scalaLibDir = currentBranchPath/"lib"/"dbt_scala"
    // ("make -C "+scalaLibDir.getAbsolutePath)!;
    // copyFile(currentBranchPath/"lib"/"dbt_scala"/"dbtlib.jar", releaseDir/"lib"/"dbt_scala")
    // copyFile(currentBranchPath/"lib"/"dbt_scala"/"tuplegen.jar", releaseDir/"lib"/"dbt_scala")

    println("copy data files to data")
    copyFiles(IO.listFiles(frontendRepo/"dbtoaster"/"experiments"/"data"/"simple"/"tiny").filter(_.getName.endsWith(".dat")), releaseDir/"examples"/"data"/"simple")
    copyFiles(IO.listFiles(frontendRepo/"dbtoaster"/"experiments"/"data"/"tpch"/"tiny").filter(_.getName.endsWith(".csv")), releaseDir/"examples"/"data"/"tpch")
    copyFiles(IO.listFiles(frontendRepo/"dbtoaster"/"experiments"/"data"/"mddb"/"tiny").filter(_.getName.endsWith(".csv")), releaseDir/"examples"/"data"/"mddb")
    copyFile(frontendRepo/"dbtoaster"/"experiments"/"data"/"finance"/"tiny"/"finance.csv", releaseDir/"examples"/"data")
    
    println("copy query files to queries")
    fixSqlFiles((currentBranchPath/"test"/"queries"/"simple") * "r*.sql" get, releaseDir/"examples"/"queries"/"simple")
    fixSqlFiles(IO.listFiles(currentBranchPath/"test"/"queries"/"tpch").filter(f => !"""((query[0-9]+a?)|(schemas)).sql""".r.findFirstIn(f.getName).isEmpty), releaseDir/"examples"/"queries"/"tpch")
    fixSqlFiles(((currentBranchPath/"test"/"queries"/"finance") * "*.sql" get).filter(_.getName != "chrissedtrades.sql"), releaseDir/"examples"/"queries"/"finance")
    fixSqlFiles(IO.listFiles(currentBranchPath/"test"/"queries"/"mddb").filter(f => !"""((query[1-2]+.sql)|(schemas.sql)|(README))""".r.findFirstIn(f.getName).isEmpty), releaseDir/"examples"/"queries"/"mddb")
    
    val distDir = baseDir/"dist";
    if (!distDir.exists) distDir.mkdirs;
    val tmpDir = baseDir/"dbtoaster"
    (s"mv ${releaseDir.getAbsolutePath} ${tmpDir.getAbsolutePath}")!;
    (s"tar -cvzf ${distDir.getAbsolutePath}/dbtoaster.tgz -C ${baseDir} ./dbtoaster")!;
    (s"mv ${tmpDir.getAbsolutePath} ${releaseDir.getAbsolutePath}")!;
  }
  write(compilerFilePath, compilerClassContent)

  state
})
