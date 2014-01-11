// --------- project informations
Seq(
  name := "DistributedDBtoaster",
  organization := "ch.epfl.data",
  version := "0.1"
)

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
libraryDependencies <++= scalaVersion(v=>Seq(
  "com.typesafe.akka" %% "akka-actor"     % "2.2.3",
  "com.typesafe.akka" %% "akka-remote"    % "2.2.3",
  //"com.typesafe.akka" %% "akka-cluster"   % "2.2.3",
  // XXX: use scripts/regress.sh to compile legacy Scala back-end instead
  "org.scala-lang"     % "scala-actors"   % v, // XXX: legacy to compile previous Scala back-end
  "org.scala-lang"     % "scala-compiler" % v,
  "org.scalatest"     %% "scalatest"      % "2.0.RC3" % "test"
))

// --------- Compilation options
Seq(
  scalaVersion := "2.10.3",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6") // forces JVM 1.6 compatibility for JDK 1.7 compiler
)

// --------- Execution options
Seq(
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m"), // ,"-Xss512m","-XX:MaxPermSize=2G"
  //javaOptions ++= Seq("-Xmx14G","-Xms14G","-verbose:gc"),parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath="+cp.files.absString) // propagate paths
)

// --------- Custom tasks
addCommandAlias("toast", ";run-main ddbt.Compiler ") ++
addCommandAlias("unit", ";run-main ddbt.UnitTest ") ++
addCommandAlias("queries", ";unit -dd;test-only ddbt.test.gen.*") ++
addCommandAlias("queries-lms", ";unit -dd -l lms;test-only ddbt.test.gen.*") ++
addCommandAlias("queries-akka", ";unit -dd -l akka"+" -qx mddb/.* -qx tpch/query(2|21) -qx zeus/(48183500|52548748) -qx rs_ineqwithnestedagg"+";test-only ddbt.test.gen.*")

// Akka individual queries testing
addCommandAlias("aq","unit -dd -v -x -s 0 -l akka -q ") ++
addCommandAlias("bad", ";unit -dd -v -x -s 0 -l akka -q rs_column_mapping_[12] -q tpch/query(9|10|18);test-only ddbt.test.gen.*") // known incorrect results: incorrect remote call alias detection
// ../dbt/bin/dbtoaster_release ../dbt/test/queries/simple/rs_column_mapping_1.sql -l m3

addCommandAlias("bench", ";unit -v -x -xsc -xvm -csv bench.csv -l ") ++ // usage: sbt 'bench lms'
addCommandAlias("bench-all", ";unit -v -x -xsc -xvm -csv bench-all.csv -l scala -l lms -l lscala -l llms")

TaskKey[Unit]("pkg") <<= (baseDirectory, classDirectory in Compile, fullClasspath in Runtime) map { (base,cd,cp) =>
  import scala.sys.process.Process
  val dir=base/"pkg"; if (!dir.exists) dir.mkdirs;
  println("Packaging DDBT runtime library ...")
  val lib=dir/"ddbt_lib.jar"; Process(Seq("jar","-cMf",lib.getPath,"-C",cd.toString,"ddbt/lib")).!
  println("Packaging DDBT compiler ...")
  val all=dir/"ddbt.jar"; Process(Seq("jar","-cMf",all.getPath,"-C",cd.toString,"ddbt")).!
  val dep=dir/"ddbt_deps.jar"; if (!dep.exists) {
    print("Packaging dependencies "); scala.Console.out.flush; val tmp=new File("target/pkg_tmp"); IO.createDirectory(tmp)
    val jars = (cp.files.absString.split(":").filter(x=>x!=cd.toString).toSet + lib.getPath)
    val sc = jars.filter(_.matches(".*/scala-library.*")).map(_.replaceAll("scala-library","scala-compiler"))
    val r=tmp/"reference.conf"; val rs=tmp/"refs.conf"; IO.write(rs,"")
    (jars++sc).foreach { j => Process(Seq("jar","-xf",j),tmp).!; if (r.exists) IO.append(rs,IO.read(r)); print("."); scala.Console.out.flush; }
    if (r.exists) r.delete; rs.renameTo(r); Process(Seq("jar","-cMf",dep.getPath,"-C",tmp.getAbsolutePath(),".")).!; IO.delete(tmp); println(" done.")
  }
}

TaskKey[Unit]("scripts") <<= (baseDirectory, fullClasspath in Runtime) map { (base, cp) =>
  def s(file:String,main:String) {
    val content = "#!/bin/sh\njava -classpath \""+cp.files.absString+"\" "+main+" \"$@\"\n"
    val out = base/file; IO.write(out,content); out.setExecutable(true)
  }
  s("toast.sh","ddbt.Compiler")
  s("unit.sh","ddbt.UnitTest")
}

// --------- LMS conditional inclusion
{
  // set ddbt.lms = 1 in conf/ddbt.properties to enable LMS
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("conf/ddbt.properties")) } catch { case _:Throwable => }
  val lms = prop.getProperty("ddbt.lms","0")=="1"
  if (!lms) Seq() else Seq(
    sources in Compile ~= (fs => fs.filter(f=> !f.toString.endsWith("codegen/LMSGen.scala"))), // ++ (new java.io.File("lms") ** "*.scala").get
    scalaSource in Compile <<= baseDirectory / "lms", // incorrect; but fixes dependency and allows incremental compilation (SBT 0.13.0)
    //unmanagedSourceDirectories in Compile += file("lms"),
    // LMS-specific options
    scalaOrganization := "org.scala-lang.virtualized",
    scalaVersion := "2.10.2-RC1",
    libraryDependencies ++= Seq(
      "org.scala-lang.virtualized" % "scala-library" % "2.10.2-RC1",
      "org.scala-lang.virtualized" % "scala-compiler" % "2.10.2-RC1",
      "EPFL" %% "lms" % "0.3-SNAPSHOT"
    ),
    scalacOptions ++= List("-Yvirtualize")
  )
}

// show full-classpath
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
