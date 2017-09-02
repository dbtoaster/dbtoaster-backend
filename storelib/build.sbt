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
  "org.scala-lang.modules" % "scala-xml_2.11" % "1.0.6",
  "com.typesafe.akka" %% "akka-actor"     % "2.5.4",
  "com.typesafe.akka" %% "akka-remote"    % "2.5.4",
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
  // "com.typesafe.akka" %% "akka-actor"     % "2.2.3",   // release only
  // "com.typesafe.akka" %% "akka-remote"    % "2.2.3",   // release only  
)

// --------- Compilation options
Seq(
  scalaVersion := "2.11.11",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-target:jvm-1.6" /* , "-Yinline-warnings" */),
  javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target","1.6")
)
