// --------- Project informations
Seq(
  name := "sstore",
  organization := "ch.epfl.data",
  version := "2.1"
)

Seq(
  scalaSource in Compile <<= baseDirectory / "src",
  javaSource in Compile <<= baseDirectory / "src",
  sourceDirectory in Compile <<= baseDirectory / "src"
)

libraryDependencies ++= Seq(
  "com.typesafe.akka" %% "akka-actor"     % "2.3.11",
  "com.typesafe.akka" %% "akka-remote"    % "2.3.11",
  // "com.typesafe.akka" %% "akka-actor"     % "2.2.3",   // release only
  // "com.typesafe.akka" %% "akka-remote"    % "2.2.3",   // release only  
  "org.scala-lang"     % "scala-actors"   % scalaVersion.value, // to compile legacy Scala
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.2",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-Yinline-warnings", "-target:jvm-1.6"),
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target","1.6")
)
