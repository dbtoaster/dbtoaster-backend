// --------- Project information
Seq(
  name := "DBToaster-spark",
  organization := "ch.epfl.data",
  version := "1.0"
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.11",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-target:jvm-1.6" /* , "-Yinline-warnings" */),
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target","1.6")
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

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % "1.6.1"
)

