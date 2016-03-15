
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

libraryDependencies ++= Seq(
//  "com.typesafe.akka" %% "akka-actor"     % "2.2.3",
//  "com.typesafe.akka" %% "akka-remote"    % "2.2.3",
  "com.typesafe.akka" %% "akka-actor"     % "2.3.10",
  "com.typesafe.akka" %% "akka-remote"    % "2.3.10",
  "org.scala-lang"     % "scala-actors"   % scalaVersion.value, // to compile legacy Scala
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value,
      "org.apache.logging.log4j" % "log4j-api" % "2.0-rc1",
      "org.apache.logging.log4j" % "log4j-core" % "2.0-rc1",
      "org.slf4j" % "slf4j-api" % "1.7.2",
      "org.slf4j" % "slf4j-ext" % "1.7.2",
      "mysql" % "mysql-connector-java" % "5.1.28"
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.2",
//  scalaVersion := "2.10.3",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6"), // forces JVM 1.6 compatibility with JDK 1.7 compiler
javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath="+cp.files.absString) // propagate paths
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
