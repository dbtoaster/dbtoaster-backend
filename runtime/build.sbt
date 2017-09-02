
// --------- Project informations
Seq(
  name := "Runtime",
  organization := "ch.epfl.data",
  version := "2.1"
)
Seq(
  scalaSource in Compile <<= baseDirectory / "tpcc",
  javaSource in Compile <<= baseDirectory / "tpcc",
  sourceDirectory in Compile <<= baseDirectory / "tpcc"
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.11",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-target:jvm-1.6" /*, "-Yinline-warnings" */),
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target","1.6")
)

// --------- Execution options
Seq(
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m","-XX:-DontCompileHugeMethods","-XX:+CMSClassUnloadingEnabled"),
  javaOptions ++= Seq("-Xmx4G","-Xms1G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath=" + cp.files.absString) // propagate paths
)

// --------- Pardis codegen -- START
{
  // generatorSettings
  import ch.epfl.data.sc.purgatory.plugin.PurgatoryPlugin._
   Seq(
    scalaSource in Compile <<= baseDirectory / "pardis", // incorrect; copied from lms
    resolvers += Resolver.sonatypeRepo("snapshots"),
    libraryDependencies ++= Seq(
      "ch.epfl.data" % "sc-pardis-compiler_2.11" % "0.1.1-SNAPSHOT",
      "ch.epfl.data" % "sc-pardis-quasi_2.11" % "0.1.1-SNAPSHOT"
    ))
}
// --------- Pardis codegen -- FINISH
