// --------- Project information
Seq(
  name := "DBToaster-shared",
  organization := "ch.epfl.data",
  version := "1.0"
)

javacOptions ++= Seq("-source", "1.7", "-target", "1.7")
scalacOptions += "-target:jvm-1.7"

scalaVersion := "2.10.6"

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
  "com.typesafe.akka" %% "akka-actor"     % "2.3.11",
  "com.typesafe.akka" %% "akka-remote"    % "2.3.11",
  // "com.typesafe.akka" %% "akka-actor"     % "2.2.3",   // release only
  // "com.typesafe.akka" %% "akka-remote"    % "2.2.3",   // release only
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
)

