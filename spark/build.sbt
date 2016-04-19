// --------- Project informations
Seq(
  name := "DBToaster-spark",
  organization := "ch.epfl.data",
  version := "1.0"
)

scalaVersion := "2.10.4"

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

