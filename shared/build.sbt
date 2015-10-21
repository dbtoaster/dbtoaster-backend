// --------- Project informations
Seq(
  name := "DBToaster-shared",
  organization := "ch.epfl.data",
  version := "1.0"
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

scalaVersion := "2.10.4"

// --------- Dependencies
libraryDependencies ++= Seq(
  "com.typesafe.akka" %% "akka-actor"     % "2.3.11",
  "com.typesafe.akka" %% "akka-remote"    % "2.3.11",
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
)

