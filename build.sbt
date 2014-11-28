val LANG_SCALA = "vscala"
val LANG_SCALA_LMS = "scala"

// --------- Project informations
Seq(
  name := "DBtoaster",
  organization := "ch.epfl.data",
  version := "2.1"
)

mainClass in run in Compile := Some("ddbt.Compiler")

packSettings

packMain := Map("compiler" -> "ddbt.Compiler")

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
  "com.typesafe.akka" %% "akka-actor"     % "2.3.3",
  "com.typesafe.akka" %% "akka-remote"    % "2.3.3",
  "org.scala-lang"     % "scala-actors"   % scalaVersion.value, // to compile legacy Scala
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value,
  "org.scalatest"     %% "scalatest"      % "2.2.0" % "test"
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.1",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6") // forces JVM 1.6 compatibility with JDK 1.7 compiler
)

// --------- Execution options
Seq(
  fork := true, // required to enable javaOptions
  //javaOptions ++= Seq("-agentpath:"+"/Applications/Tools/YourKit Profiler.app/bin/mac/libyjpagent.jnilib"+"=sampling,onexit=snapshot,builtinprobes=all"),
  javaOptions ++= Seq("-Xss128m","-XX:-DontCompileHugeMethods","-XX:+CMSClassUnloadingEnabled"), // ,"-Xss512m","-XX:MaxPermSize=2G"
  javaOptions ++= Seq("-Xmx14G","-Xms14G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath="+cp.files.absString) // propagate paths
)

// --------- Custom tasks
addCommandAlias("toast", ";run-main ddbt.Compiler ") ++
addCommandAlias("unit", ";run-main ddbt.UnitTest ") ++
addCommandAlias("queries", "unit -dd -v -x -s 0 -l "+LANG_SCALA+" ") ++
addCommandAlias("queries-lms", "unit -dd -v -x -s 0 -l lms -xsc ") ++
addCommandAlias("queries-akka", "unit -dd -v -x -s 0 -l akka -qx mddb/query2 -qx tpch/query21 ") // too long to compile/execute

// Akka individual queries testing
addCommandAlias("aq","unit -dd -v -x -s 0 -l akka -q ")

addCommandAlias("bench", ";unit -v -x -xsc -xvm -csv bench.csv -l ") ++ // usage: sbt 'bench lms'
addCommandAlias("bench-all", ";unit -v -x -xsc -xvm -csv bench-all.csv -l "+LANG_SCALA+" -l "+LANG_SCALA_LMS+" -l lscala -l llms ") ++ // usage: sbt 'bench-all'
//addCommandAlias("bench-all-tpch", ";unit -p 2 -x -xsc -xvm -csv bench-all.csv -dump bench-all-dump.txt -l lscala -l llms -l "+LANG_SCALA+" -l "+LANG_SCALA_LMS+" -l cpp -l lcpp -w 2 -s 3 -t 60000 -d big_del -q tpch.*query[0-9]+.sql ")
addCommandAlias("bench-all-tpch", ";unit -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000 -csv bench-all.csv -dump bench-all-dump.txt -l "+LANG_SCALA+" -l "+LANG_SCALA_LMS+" -l cpp -d big_del -q tpch.*query[0-9]+ ")

// --------- Packaging: fake (to use SBT paths for debugging), full (packages all dependencies), dist (ship on all cluster hosts)
InputKey[Unit]("pkg") <<= InputTask(_ => Def.spaceDelimited("<args>")) { result =>
 (result, baseDirectory, classDirectory in Compile, classDirectory in Test, fullClasspath in Runtime, scalaVersion, compile in Compile, compile in Test, copyResources in Compile) map {
  (args,base,cls,test,cp,vers,_,_,_) =>
    val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
    def pr(n:String,d:String="") = prop.getProperty("ddbt."+n,d)
    import scala.collection.JavaConversions._
    import scala.sys.process._
    // Packaging
    val dir=base/"pkg"; if (!dir.exists) dir.mkdirs
    val jars = cp.files.absString.split(":").filter(_!=cls.toString).distinct.sorted // all dependencies
    def mk_jar(name:String,root:File,path:String*) { Process(Seq("jar","-cMf",(dir/(name+".jar")).getPath) ++ path.flatMap(p=>Seq("-C",root.getPath,p)) ).!; print(".") }
    def mk_script(name:String,args:String) {
      val out=dir/name; IO.write(out,"#!/bin/sh\ncd `dirname $0`\nCP_DEPS=\""+jars.mkString(":")+"\"\n"+
      "if [ -f ddbt_deps.jar ]; then CP_DEPS=\"ddbt_deps.jar\"; fi\n"+{ val x=pr("cmd_extra").trim; if (x!="") x+"\n" else "" }+
      "exec "+pr("cmd_java","java")+" "+args+"\n"); out.setExecutable(true)
    }
    if (args.contains("fake")) { // fake runner for debug
      val cp0="../target/scala-"+vers.replaceAll(".[0-9]$","")+"/"
      mk_script("run","-classpath \"$CP_DEPS:"+cp0+"classes:"+cp0+"test-classes\" \"$@\"")
    } else {
      print("Packaging DDBT libraries: ")
      mk_jar("ddbt_lib",cls,"ddbt/lib","ddbt.properties") // runtime libraries
      mk_jar("ddbt_gen",test,"ddbt/test/gen") // tests
      mk_script("run","-classpath \"$CP_DEPS:ddbt_lib.jar:ddbt_gen.jar\" \"$@\"")
      if (args.contains("full")) { mk_jar("ddbt",cls,".") // compiler
        val tmp=base/"target"/"pkg_tmp"; tmp.mkdirs; val r=tmp/"reference.conf"; val rs=tmp/"refs.conf"; IO.write(rs,"")
        jars.foreach { j => Process(Seq("jar","-xf",j),tmp).!; if (r.exists) IO.append(rs,IO.read(r)); print(".") }
        if (r.exists) r.delete; rs.renameTo(r); mk_jar("ddbt_deps",tmp,"."); IO.delete(tmp)
        mk_script("toast","-classpath \"$CP_DEPS:ddbt.jar\" ddbt.Compiler \"$@\"")
        mk_script("unit","-classpath \"$CP_DEPS:ddbt.jar\" ddbt.UnitTest \"$@\"")
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

commands += Command.command("release")((state:State) => {
  def copyFile(file:File, targetDir:File) = { if(!targetDir.exists) targetDir.mkdirs; IO.copyFile(file,targetDir/file.getName)}
  def copyFiles(files:Iterable[File], targetDir:File) = { if(!targetDir.exists) targetDir.mkdirs; files.foreach{ f => IO.copyFile(f,targetDir/f.getName) } }
  def copyDir(sourceDir:File, targetDir:File) = { if(!targetDir.exists) targetDir.mkdirs; IO.copyDirectory(sourceDir,targetDir,true) }
  def read(file:String) = { val f=new File(file); val cs=new Array[Char](f.length.toInt); val r=new java.io.FileReader(f); r.read(cs); r.close; new String(cs) }
  def write(file:String,data:String) { val f=new File(file); val dir=f.getParentFile; if (dir!=null && !dir.exists) dir.mkdirs; val o=new java.io.PrintWriter(f); o.write(data); o.close() }
  def fixSqlFiles(files:Iterable[File], targetDir:File) = { if(!targetDir.exists) targetDir.mkdirs; files.foreach{ f => val fixedSql=fixSQL(read(f.getAbsolutePath())); write((targetDir/f.getName).getAbsolutePath(), fixedSql) } }
  def fixSQL(input:String) = {
    var output_next_blank = false;
    (new scala.collection.immutable.StringOps(input)).lines.map{ l =>
      l.replace("../../experiments", "examples")
       .replace("test/queries", "examples/queries")
       .replace("standard/", "")
       .replace("tiny/", "")
       .replace("big/", "")
       .replace("data/finance/finance.csv", "data/finance.csv")
       .replace("../alpha5/", "")
       .replaceAll("--.*", "")+IO.Newline
    }.filter { l =>
      if(!l.trim.isEmpty) { output_next_blank = true; true }
      else if(output_next_blank) { output_next_blank = false; true }
      else false
    }.mkString
  }
  //load all the properties
  val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  println("defining base and release paths")
  val base = baseDirectory.value
  val releaseDir = base/"release";
  println("cleaning")
  IO.delete(releaseDir/"bin"/"dbtoaster_frontend")
  IO.delete(releaseDir/"CHANGELOG")
  IO.delete(releaseDir/"LICENSE")
  IO.delete(releaseDir/"README")
  IO.delete(releaseDir/"doc")
  IO.delete(releaseDir/"examples")
  IO.delete(releaseDir/"lib")
  println("compiling sources")
  val compilerClassContent = read("src/Compiler.scala")
  write("src/Compiler.scala", compilerClassContent.replace("=DEPLOYMENT_STATUS_DEVELOPMENT", "=DEPLOYMENT_STATUS_RELEASE"))
  Project.evaluateTask(compile, state)
  println("execute pack task")
  Project.evaluateTask(pack, state)
  println("copy all the Scala dependency libraries")
  val sourceDir = base/"target"/"pack"/"lib";
  if (sourceDir.exists) {
    val targetDir=releaseDir/"lib"/"dbt_scala"; targetDir.mkdirs
    copyFiles(IO.listFiles(sourceDir).filter{f => (!f.getName.startsWith("akka-remote") && !f.getName.startsWith("mysql") && !f.getName.startsWith("netty") && !f.getName.startsWith("protobuf")  && !f.getName.startsWith("scala-actors") && !f.getName.startsWith("scalatest") && f.getName != "dbtlib.jar" && f.getName != "tuplegen.jar")},targetDir)
    val ddbtJar = targetDir/"dbtoaster_2.10-2.1.jar"
    if (prop.getProperty("ddbt.lms","0")!="1") { //vanilla scala
      println("using vanilla Scala version using dbtoaster_2.10-2.1-scala.jar")
      IO.copyFile(ddbtJar, targetDir/"dbtoaster_2.10-2.1-scala.jar")
    } else { //lms
      println("using Scala+LMS version using dbtoaster_2.10-2.1-lms.jar")
      IO.copyFile(ddbtJar, targetDir/"dbtoaster_2.10-2.1-lms.jar")
      // IO.copyFile(ddbtJar, targetDir/"dbtoaster_2.10-2.1-scala.jar")
    }
    IO.delete(ddbtJar)
  } else {
    println("Libraries (in "+sourceDir+") are not created via pack command.")
  }
  println("copy dbtoaster_release")
  val baseRepo = file(prop.getProperty("ddbt.base_repo",""))
  if(baseRepo!="") {
    val currentBranchPath = baseRepo/"/dbtoaster"/"compiler"/"alpha5"
    println("make dbt_release")
    ("make -C "+currentBranchPath.getAbsolutePath)!;
    println("copy dbt_release")
    val dbtBinPath = currentBranchPath/prop.getProperty("ddbt.dbtoaster.frontend","bin/dbtoaster_release")
    copyFile(dbtBinPath,releaseDir/"bin")
    ("mv "+(releaseDir/"bin"/dbtBinPath.getName).getAbsolutePath+" "+(releaseDir/"bin"/"dbtoaster_frontend").getAbsolutePath)!;
    ("chmod +x "+(releaseDir/"bin"/"dbtoaster_frontend").getAbsolutePath)!;
    println("copy README, LICENSE and CHANGELOG")
    copyFile(currentBranchPath/"doc"/"README", releaseDir)
    copyFile(currentBranchPath/"doc"/"LICENSE", releaseDir)
    copyFile(currentBranchPath/"doc"/"CHANGELOG", releaseDir)
    println("copy docs to doc dir")
    val releaseDocDir = releaseDir/"doc"; releaseDocDir.mkdirs
    copyFiles(List("9.jpg", "style.css", "bakeoff.png", "bluetab.gif",
         "bluetabactive.gif", "dropdowntabs.js", "dbtoaster-logo.gif")
         .map(f => currentBranchPath/"doc"/"site_html"/f),releaseDocDir)
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html").filter(_.getName.endsWith(".html")), releaseDocDir)
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html"/"css").filter(_.getName.endsWith(".css")), releaseDocDir/"css")
    copyFiles(IO.listFiles(currentBranchPath/"doc"/"site_html"/"js").filter(_.getName.endsWith(".js")), releaseDocDir/"js")
    println("make c++ libs")
    val cppLibDir = base/"srccpp"/"lib"
    ("make -C "+cppLibDir.getAbsolutePath)!;
    println("copy c++ libs")
    val releaseCppLibDir = releaseDir/"lib"/"dbt_c++"; releaseCppLibDir.mkdirs
    (releaseCppLibDir/"hpds").mkdirs
    (releaseCppLibDir/"mmap").mkdirs
    (releaseCppLibDir/"smhasher").mkdirs
    copyFiles(IO.listFiles(cppLibDir).filter{f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".a") || "makefile"==f.getName }, releaseCppLibDir)
    copyFiles(IO.listFiles(cppLibDir/"hpds").filter{f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".a") || "makefile"==f.getName }, releaseCppLibDir/"hpds")
    copyFiles(IO.listFiles(cppLibDir/"mmap").filter{f => f.getName.endsWith(".cpp") || f.getName.endsWith(".hpp") || f.getName.endsWith(".a") || "makefile"==f.getName }, releaseCppLibDir/"mmap")
    copyFiles(IO.listFiles(cppLibDir/"smhasher").filter{f => f.getName.startsWith("MurmurHash2") }, releaseCppLibDir/"smhasher")
    println("copy main.cpp")
    copyFile(currentBranchPath/"lib"/"dbt_c++"/"main.cpp",releaseDir/"examples"/"code")
    println("make scala libs")
    // val scalaLibDir = currentBranchPath/"lib"/"dbt_scala"
    // ("make -C "+scalaLibDir.getAbsolutePath)!;
    // copyFile(currentBranchPath/"lib"/"dbt_scala"/"dbtlib.jar", releaseDir/"lib"/"dbt_scala")
    // copyFile(currentBranchPath/"lib"/"dbt_scala"/"tuplegen.jar", releaseDir/"lib"/"dbt_scala")
    println("copy data files to data")
    copyFiles(IO.listFiles(baseRepo/"dbtoaster"/"experiments"/"data"/"simple"/"tiny").filter(_.getName.endsWith(".dat")), releaseDir/"examples"/"data"/"simple")
    copyFiles(IO.listFiles(baseRepo/"dbtoaster"/"experiments"/"data"/"tpch"/"tiny").filter(_.getName.endsWith(".csv")), releaseDir/"examples"/"data"/"tpch")
    copyFiles(IO.listFiles(baseRepo/"dbtoaster"/"experiments"/"data"/"mddb"/"tiny").filter(_.getName.endsWith(".csv")), releaseDir/"examples"/"data"/"mddb")
    copyFile(baseRepo/"dbtoaster"/"experiments"/"data"/"finance"/"tiny"/"finance.csv", releaseDir/"examples"/"data")
    println("copy query files to queries")
    fixSqlFiles((currentBranchPath/"test"/"queries"/"simple") * "r*.sql" get, releaseDir/"examples"/"queries"/"simple")
    fixSqlFiles(IO.listFiles(currentBranchPath/"test"/"queries"/"tpch").filter(f => !"""((query[0-9]+a?)|(schemas)).sql""".r.findFirstIn(f.getName).isEmpty), releaseDir/"examples"/"queries"/"tpch")
    fixSqlFiles(((currentBranchPath/"test"/"queries"/"finance") * "*.sql" get).filter(_.getName != "chrissedtrades.sql"), releaseDir/"examples"/"queries"/"finance")
    fixSqlFiles(IO.listFiles(currentBranchPath/"test"/"queries"/"mddb").filter(f => !"""((query[1-2]+.sql)|(schemas.sql)|(README))""".r.findFirstIn(f.getName).isEmpty), releaseDir/"examples"/"queries"/"mddb")
    val distDir = base/"dist";
    if(!distDir.exists) distDir.mkdirs;
    ("mv ./release ./dbtoaster")!;
    ("tar -cvzf ./dist/dbtoaster.tgz ./dbtoaster")!;
    ("mv ./dbtoaster ./release")!;
  }
  write("src/Compiler.scala", compilerClassContent)
  state
})

// --------- LMS codegen, enabled with ddbt.lms = 1 in conf/ddbt.properties
{
  val prop=new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  if (prop.getProperty("ddbt.lms","0")!="1") Seq() else Seq(
    // assemblyOption in assembly ~= { _.copy(includeScala = false) }
    sources in Compile ~= (fs => fs.filter(f=> !f.toString.endsWith("codegen/LMSGen.scala"))), // ++ (new java.io.File("lms") ** "*.scala").get
    scalaSource in Compile <<= baseDirectory / "lms", // incorrect; but fixes dependency and allows incremental compilation (SBT 0.13.0)
    //unmanagedSourceDirectories in Compile += file("lms"),
    // LMS-specific options
    scalaOrganization := "org.scala-lang.virtualized",
    scalaVersion := "2.10.2-RC1",
    libraryDependencies ++= Seq(
      "org.scala-lang.virtualized" % "scala-library" % scalaVersion.value,
      "org.scala-lang.virtualized" % "scala-compiler" % scalaVersion.value,
      "org.apache.logging.log4j" % "log4j-api" % "2.0-rc1",
      "org.apache.logging.log4j" % "log4j-core" % "2.0-rc1",
      "org.slf4j" % "slf4j-api" % "1.7.2",
      "org.slf4j" % "slf4j-ext" % "1.7.2",
      "mysql" % "mysql-connector-java" % "5.1.28",
      "org.scalariform" %% "scalariform" % "0.1.4",
      "org.scalatest" %% "scalatest" % "2.0",
      "EPFL" %% "lms" % "0.3-SNAPSHOT"
    ),
    scalacOptions ++= List("-Yvirtualize")
  )
}

// --------- Pardis codegen -- START
{
  val prop = new java.util.Properties(); try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  val outputFolder = prop.getProperty("ddbt.pardis.outputFolder","pardis/lifter")
  val inputPackage = prop.getProperty("ddbt.pardis.inputPackage","ddbt.lib.store")
  val outputPackage = prop.getProperty("ddbt.pardis.outputPackage","ddbt.lib.store.deep")
  lazy val generatorMode = SettingKey[Boolean]("generator-mode", "Is the compiler used for generating the deep embedding")
  def embed = Command.command("embed") { state =>
    val cleaned = Project.runTask(Keys.clean in Compile, state)
    cleaned match {
      case Some((state, _)) =>
        Project.evaluateTask(Keys.compile in Compile,
          (Project extract state).append(Seq(generatorMode := true), state))
        Project.evaluateTask(Keys.clean in Compile, state)
        state
      case None =>
        state
    }
  }
  def generatorSettings: Seq[Setting[_]] = Seq(
    libraryDependencies ++= Seq("ch.epfl.data" % "purgatory-core_2.11" % "0.1-SNAPSHOT",
      "ch.epfl.data" % "purgatory_2.11" % "0.1-SNAPSHOT"
    ),
    generatorMode := false,
    scalacOptions ++= {
      if(generatorMode.value) {
        val cpath = update.value.matching(configurationFilter()).classpath
        val plugin = cpath.files.find(_.getName contains "purgatory_").get.absString
        val purgatory_core = cpath.files.find(_.getName contains "purgatory-core").get.absString
        val yy_core = cpath.files.find(_.getName contains "yinyang-core").get.absString
        val yy = cpath.files.find(_.getName contains "scala-yinyang").get.absString
        Seq(
          s"-Xplugin:$plugin:$yy_core:$yy:$purgatory_core",
          "-Ystop-after:backend-generator", 
          s"-P:backend-generator:output-folder:$outputFolder",
          s"-P:backend-generator:input-package:$inputPackage",
          s"-P:backend-generator:output-package:$outputPackage"
        )
      } else Seq()
    },
    commands += embed
  )
  generatorSettings
}
// --------- Pardis codegen -- FINISH

// show full-classpath
//commands += Command.args("cmd","")((state: State, args: Seq[String]) => { println(args.toList); state })
//javaHome := Some(file("/System/Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Home"))
//javaHome := Some(file("/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home"))
//{
//  val t=TaskKey[Unit]("queries-gen2")
//  val q=TaskKey[Unit]("queries-test2")
//  Seq(
//    fullRunTask(t in Compile, Compile, "ddbt.UnitTest", "tiny","tiny_del","standard","standard_del"),
//    q <<= (t in Compile) map { x => scala.sys.process.Process(Seq("sbt", "test-only ddbt.test.gen.*")).!; }
//    //(test in Test) <<= (test in Test) dependsOn (t in Compile),   // force tests to rebuild
//    //testOptions in Test += Tests.Argument("-l", "ddbt.SlowTest"), // execute only non-tagged tests
//  )
//}
// jar -cf foo.jar -C target/scala-2.10/classes ddbt/lib
// TaskKey[Unit]("test-queries") := { scala.sys.process.Process(Seq("sbt", "test-only ddbt.test.gen.*")).! }
//
// Seq(
//   autoCompilerPlugins := true,
//   libraryDependencies <+= scalaVersion(v=>compilerPlugin("org.scala-lang.plugins" % "continuations" % v)),
//   scalacOptions += "-P:continuations:enable"
// )
//
// http://grokbase.com/t/gg/simple-build-tool/133xb2khew/sbt-external-process-syntax-in-build-sbt
// http://stackoverflow.com/questions/15494508/bash-vs-scala-sys-process-process-with-command-line-arguments
//compile in Compile <<= (compile in Compile) map { x => ("src/librna/make target/scala-2.10/classes").run.exitValue; x }
//	"org.scala-lang" % "scala-reflect" % v,
//	"ch.epfl" %% "lms" % "0.4-SNAPSHOT",
//	"org.scalariform" %% "scalariform" % "0.1.4",
//parallelExecution in Test := false
//scalaOrganization := "org.scala-lang.virtualized"
//scalaVersion := Option(System.getenv("SCALA_VIRTUALIZED_VERSION")).getOrElse("2.10.2-RC1")
//resolvers ++= Seq(
//    ScalaToolsSnapshots,
//    "Sonatype Public" at "https://oss.sonatype.org/content/groups/public",
//	Classpaths.typesafeSnapshots
//)
// disable publishing of main docs
//publishArtifact in (Compile, packageDoc) := false
//mainClass := Some("Main")
//selectMainClass := Some("Main")
// Storm dependencies:
//resolvers ++= Seq(
//  "clojars" at "http://clojars.org/repo/",
//  "clojure-releases" at "http://build.clojure.org/releases"
//)
//
  //"com.esotericsoftware.kryo" % "kryo"  % "2.21",
  //"com.twitter"       %% "chill"        % "0.3.1",
  //"org.spark-project" %% "spark-core"   % "0.8.0-SNAPSHOT",
  //"com.github.velvia" %% "scala-storm"  % "0.2.3-SNAPSHOT",
  //"storm"              % "storm"        % "0.8.2"
