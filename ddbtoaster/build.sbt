// --------- Project information
Seq(
  name := "DBToaster",
  organization := "ch.epfl.data",
  version := "2.3"
)

mainClass in run in Compile := Some("ddbt.Compiler")

packSettings

packMain := Map("compiler" -> "ddbt.Compiler")
autoCompilerPlugins := true
addCompilerPlugin("org.scala-lang.plugins" % "scala-continuations-plugin_2.11.8" % "1.0.3")

// --------- Paths
Seq(
  scalaSource in Compile <<= baseDirectory / "src",
  javaSource in Compile <<= baseDirectory / "src",
  sourceDirectory in Compile <<= baseDirectory / "src",
  scalaSource in Test <<= baseDirectory / "test",
  javaSource in Test <<= baseDirectory / "test",
  sourceDirectory in Test <<= baseDirectory / "test",
  resourceDirectory in Compile <<= baseDirectory / "conf"
)

// --------- Dependencies
libraryDependencies ++= Seq(
  "org.scala-lang" % "scala-library" % scalaVersion.value,
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value,
  "org.scala-lang.plugins" %% "scala-continuations-library" % "1.0.2",
  "ch.epfl.data" % "squid-sc-backend_2.11" % "0.1-SNAPSHOT"
)


// --------- Compilation options
Seq(
  scalaVersion := "2.11.11",
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-P:continuations:enable", "-XX:-DontCompileHugeMethods", "-XX:+CMSClassUnloadingEnabled", "-source", "1.6", "-target", "1.6"),
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-J-XX:-DontCompileHugeMethods", "-J-XX:+CMSClassUnloadingEnabled", "-target:jvm-1.6" /* , "-Yinline-warnings" */)
)

// --------- Execution options
Seq(
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m", "-XX:-DontCompileHugeMethods", "-XX:+CMSClassUnloadingEnabled"), // ,"-Xss512m"
  javaOptions ++= Seq("-Xmx4G", "-Xms1G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath=" + cp.files.absString) // propagate paths
)

// --------- Custom tasks
val LANG_SCALA = "vscala"
val LANG_SCALA_LMS = "scala"

addCommandAlias("toast", ";DDBToaster/runMain ddbt.Compiler ") ++
addCommandAlias("unit", ";DDBToaster/runMain ddbt.UnitTest ") ++
addCommandAlias("queries", "unit -dd -v -x -s 0 -l " + LANG_SCALA + " ") ++
addCommandAlias("queries-lms", "unit -dd -v -x -s 0 -l lms -xsc ") ++
addCommandAlias("queries-akka", "unit -dd -v -x -s 0 -l akka -qx mddb/query2 -qx tpch/query21 ") // too long to compile/execute

// Akka individual queries testing
addCommandAlias("aq","unit -dd -v -x -s 0 -l akka -q ")

addCommandAlias("bench", ";unit -v -x -xsc -xvm -csv bench.csv -l ") ++ // usage: sbt 'bench lms'
addCommandAlias("bench-all", ";unit -v -x -xsc -xvm -csv bench-all.csv -l " + LANG_SCALA + " -l " + LANG_SCALA_LMS + " -l lscala -l llms ") ++ // usage: sbt 'bench-all'
//addCommandAlias("bench-all-tpch", ";unit -p 2 -x -xsc -xvm -csv bench-all.csv -dump bench-all-dump.txt -l lscala -l llms -l "+LANG_SCALA+" -l "+LANG_SCALA_LMS+" -l cpp -l lcpp -w 2 -s 3 -t 60000 -d big_del -q tpch.*query[0-9]+.sql ")
addCommandAlias("bench-all-tpch", ";unit -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000 -csv bench-all.csv -dump bench-all-dump.txt -l " + LANG_SCALA + " -l " + LANG_SCALA_LMS + " -l cpp -d big_del -q tpch.*query[0-9]+ ")


addCommandAlias("test-regression-cpp-single", 
                ";unit -xsc -xvm -p 2 -l cpp -v -x" +
                ";unit -xsc -xvm -p 2 -l cpp -v -x -q finance.* -qx finance/missedtrades -d big")


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
  val baseDir = baseDirectory.value
  val releaseDir = baseDir/"release";

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
  val sourceDir = baseDir/"target"/"pack"/"lib";
  if (sourceDir.exists) {
    val targetDir = releaseDir/"lib"/"dbt_scala"
    targetDir.mkdirs

    copyFiles(IO.listFiles(sourceDir).filter { _.getName.matches(
      "(akka-actor|config|scala-library|scala-reflect|scala-parser-combinators" + 
      "|sc-shared|sc-pardis-compiler|sc-pardis-core-compiler|sc-pardis-library|sc-pardis-quasi|scala-yinyang|squid-sc-backend" +
      "|dbtoaster_|sstore_).*") }, targetDir)

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

// --------- LMS codegen, enabled with ddbt.lms = 1 in conf/ddbt.properties
{
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) } 
  catch { case _: Throwable => }

  if (prop.getProperty("ddbt.lms","0") != "1") Seq() 
  else Seq(
    // assemblyOption in assembly ~= { _.copy(includeScala = false) }
    sources in Compile ~= (fs => fs.filter(f => !f.toString.endsWith("codegen/LMSGen.scala"))), // ++ (new java.io.File("lms") ** "*.scala").get
    
    scalaSource in Compile <<= baseDirectory / "lms", // incorrect; but fixes dependency and allows incremental compilation (SBT 0.13.0)
    //unmanagedSourceDirectories in Compile += file("lms"),

    sources in Compile ~= (fs => fs.filter(
      f => !f.toString.contains("lms/dboptimizer") && 
           !f.toString.contains("lms/tpcc"))
    ),
    
    // LMS-specific options
    scalaOrganization := "org.scala-lang.virtualized",
    scalaVersion := "2.11.2",
    libraryDependencies ++= Seq(
      "org.scala-lang.virtualized" % "scala-library" % scalaVersion.value,
      "org.scala-lang.virtualized" % "scala-compiler" % scalaVersion.value,
      // "org.slf4j" % "slf4j-api" % "1.7.2",
      "org.scalariform" %% "scalariform" % "0.2.3",
      "EPFL" %% "lms" % "0.3-SNAPSHOT"
    ),
    scalacOptions ++= List("-Yvirtualize")
  )
}

// --------- Pardis codegen -- START
{
  // generatorSettings
  import ch.epfl.data.sc.purgatory.plugin.PurgatoryPlugin._
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) }
  catch { case _:Throwable => }
  Seq(
    scalaSource in Compile <<= baseDirectory / "pardis", // incorrect; copied from lms
    resolvers += Resolver.sonatypeRepo("snapshots"),
    libraryDependencies ++= Seq(
      "ch.epfl.data" % "sc-pardis-compiler_2.11" % "0.1.4-SNAPSHOT",
      "ch.epfl.data" % "sc-pardis-quasi_2.11" % "0.1.4-SNAPSHOT"
    ),
    outputFolder := prop.getProperty("ddbt.pardis.outputFolder","ddbtoaster/pardis/lifter"),
    inputPackage := prop.getProperty("ddbt.pardis.inputPackage","ddbt.lib.store"),
    outputPackage := prop.getProperty("ddbt.pardis.outputPackage","ddbt.lib.store.deep")
  ) ++ generatorSettings
}
// --------- Pardis codegen -- FINISH

/*
// LEGACY CODE -- TO BE DELETED IN THE FUTURE

// --------- Packaging: fake (to use SBT paths for debugging), full (packages all dependencies), dist (ship on all cluster hosts)
InputKey[Unit]("pkg") <<= InputTask(_ => Def.spaceDelimited("<args>")) { result =>
 (result, baseDirectory, classDirectory in Compile, classDirectory in Test, fullClasspath in Runtime, scalaVersion, compile in Compile, compile in Test, copyResources in Compile) map {
  (args, base, cls, test, cp, vers, _, _, _) =>
    val prop = new java.util.Properties()
    try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } 
    catch { case _:Throwable => }

    def pr(n: String, d: String = "") = prop.getProperty("ddbt." + n, d)
    import scala.collection.JavaConversions._
    import scala.sys.process._
    
    // Packaging
    val dir = base/"pkg"
    if (!dir.exists) dir.mkdirs

    val jars = cp.files.absString.split(":").filter(_ != cls.toString).distinct.sorted // all dependencies
    def mk_jar(name:String,root:File,path:String*) = { 
      Process(
        Seq("jar", "-cMf", (dir/(name+".jar")).getPath) ++ 
        path.flatMap(p => Seq("-C", root.getPath, p)) 
      ).!
      print(".") 
    }

    def mk_script(name: String, args: String) {
      val out = dir/name
      IO.write(out, "#!/bin/sh\ncd `dirname $0`\nCP_DEPS=\"" + jars.mkString(":") + "\"\n" +
        "if [ -f ddbt_deps.jar ]; then CP_DEPS=\"ddbt_deps.jar\"; fi\n" + 
        { 
          val x = pr("cmd_extra").trim
          if (x != "") x + "\n" else "" 
        } +
        "exec " + pr("cmd_java", "java") + " " + args + "\n")
        out.setExecutable(true)
    }

    if (args.contains("fake")) { // fake runner for debug
      val cp0 = "../target/scala-" + vers.replaceAll(".[0-9]$", "") + "/"
      mk_script("run", "-classpath \"$CP_DEPS:" + cp0 + "classes:" + cp0 + "test-classes\" \"$@\"")
    } 
    else {
      print("Packaging DDBT libraries: ")
      mk_jar("ddbt_lib", cls, "ddbt/lib", "ddbt.properties") // runtime libraries
      mk_jar("ddbt_gen", test, "ddbt/test/gen") // tests
      mk_script("run", "-classpath \"$CP_DEPS:ddbt_lib.jar:ddbt_gen.jar\" \"$@\"")
      
      if (args.contains("full")) { 
        mk_jar("ddbt", cls, ".") // compiler
        val tmp = base/"target"/"pkg_tmp"
        tmp.mkdirs
        val r = tmp/"reference.conf"
        val rs = tmp/"refs.conf"
        IO.write(rs, "")
        jars.foreach { j => 
          Process(Seq("jar", "-xf", j), tmp).!
          if (r.exists) IO.append(rs,IO.read(r)) 
          print(".") 
        }
        if (r.exists) r.delete
        rs.renameTo(r)
        mk_jar("ddbt_deps", tmp, ".")
        IO.delete(tmp)
        mk_script("toast", "-classpath \"$CP_DEPS:ddbt.jar\" ddbt.Compiler \"$@\"")
        mk_script("unit", "-classpath \"$CP_DEPS:ddbt.jar\" ddbt.UnitTest \"$@\"")
      }
      println
      // Distribution over cluster nodes
      if (args.contains("dist")) { print("Distribution: ")
        val hs=(prop.stringPropertyNames.filter(_.matches("^ddbt.host[0-9]+$")).map(x=>prop.getProperty(x,null))+pr("master","127.0.0.1")).map(_.split(":")(0)).toSet
        val (cmd,path)=(pr("cmd_scp","rsync -av")+" "+dir+"/ "+pr("cmd_user","root")+"@",":"+pr("cmd_path","")+"/")
        hs.foreach { h => print(h); print(if ( (cmd+h+path).!(ProcessLogger(l=>(),l=>println("\nTransfer to "+h+" error: "+l.trim))) ==0) "." else "<!>") }; println
      }
    }
  }
}

// --------- Cluster execution
// XXX: this needs to be integrated in UnitTest.scala instead
// -H = local host:port
// -M = master host:port
// -W = number of (local@worker/total@master) workers
// -C = cluster_mode:hosts_count
commands += Command.args("exec","")((state:State, args:Seq[String]) => {
  val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  def pr(n:String,d:String) = prop.getProperty("ddbt."+n,d)
  import scala.collection.JavaConversions._
  import scala.sys.process._
  val lo="127.0.0.1"
  val cl=pr("cluster","2").toInt; val w=pr("workers","1").toInt; val m={ val m=pr("master",lo).split(":"); (m(0),if (m.length>1) m(1).toInt else 8800) }
  val hosts=prop.stringPropertyNames.filter(x=>x.matches("^ddbt.host[0-9]+$")).toList.sorted.zipWithIndex.map{ case (x,i)=> val h=prop.getProperty(x,null).split(":")
    (h(0),if (h.length>1 && h(1)!="") h(1).toInt else m._2+1+i,if (h.length>2) h(2).toInt else w,x.substring(9).toInt)
  }
  val hn=pr("hosts","1").toInt
  if (args.size<1) println("Usage: exec <class>") else cl match {
    case 0|1 => ("pkg/run "+args.mkString(" ")+" -H"+m._1+":"+m._2+" -W"+w+" -C"+cl+":"+hn).! // launch in the same JVM
    case 2 => // launch all JVMs locally
      def exec(as:String,p:String) = { val t=new Thread(){ override def run() { ("pkg/run "+args.mkString(" ")+" "+as) ! ProcessLogger(l=>println(p+": "+l),l=>System.err.println(p+": "+l)) }}; t.start; t }
      val nh=pr("hosts","1").toInt
      val tm=exec("-H"+lo+":"+m._2+" -W"+(nh*w),"M"); Thread.sleep(100) // launch master
      val ths=(0 until nh) map { i=> exec("-H"+lo+":"+(m._2+1+i)+" -W"+w+" -M"+lo+":"+m._2,""+(i+1)) }
      (ths:+tm).foreach(_.join)
    case 3 => // launch remotely with SSH
      val (cmd,path)=(pr("cmd_ssh","ssh")+" "+pr("cmd_user","root")+"@"," "+pr("cmd_path","")+"/run "+args.mkString(" "))
      def exec(host:String,as:String,p:String) = { val t=new Thread(){ override def run() { (cmd+host+path+" "+as) ! ProcessLogger(l=>println(p+": "+l),l=>System.err.println(p+": "+l)) }}; t.start; t }
      val tm=exec(m._1,"-H"+m._1+":"+m._2+" -W"+hosts.map(_._3).sum,"M"); Thread.sleep(100) // launch master
      val ths=hosts.map { h => exec(h._1,"-H"+h._1+":"+h._2+" -W"+h._3+" -M"+m._1+":"+m._2,""+h._4) } // launch workers
      (ths:+tm).foreach(_.join)
    case _ => System.err.println("Unrecognized 'ddbt.cluster' value")
  }
  state
})
*/
