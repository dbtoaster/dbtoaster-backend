// --------- project informations
Seq(
  name := "NioTest",
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

// --------- Compilation options
Seq(
  scalaVersion := "2.10.3",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javaOptions ++= Seq("-ea")
)

// --------- Dependencies
libraryDependencies <++= scalaVersion(v=>Seq(
  "com.typesafe.akka" %% "akka-actor"     % "2.2.3",
  "com.typesafe.akka" %% "akka-remote"    % "2.2.3"
))
/*
// http://stackoverflow.com/questions/7344477/adding-new-task-dependencies-to-built-in-sbt-tasks
JAVA_INCLUDE="/System/Library/Frameworks/JavaVM.framework/Headers"
// --------- Execution options
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6") // forces JVM 1.6 compatibility for JDK 1.7 compiler
Seq(
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m"), // ,"-Xss512m","-XX:MaxPermSize=2G"
  javaOptions ++= Seq("-Xmx14G","-Xms14G","-verbose:gc"),parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath="+cp.files.absString) // propagate paths
)
TaskKey[Unit]("scripts") <<= (baseDirectory, fullClasspath in Runtime) map { (base, cp) =>
  def s(file:String,main:String) {
    val content = "#!/bin/sh\njava -classpath \""+cp.files.absString+"\" "+main+" \"$@\"\n"
    val out = base/file; IO.write(out,content); out.setExecutable(true)
  }
  s("toast.sh","ddbt.Compiler")
  s("unit.sh","ddbt.UnitTest")
}
*/
