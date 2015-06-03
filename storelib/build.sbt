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
  "com.typesafe.akka" %% "akka-actor"     % "2.2.3",
  "com.typesafe.akka" %% "akka-remote"    % "2.2.3",
//  "com.typesafe.akka" %% "akka-actor"     % "2.3.10",
//  "com.typesafe.akka" %% "akka-remote"    % "2.3.10",
  "org.scala-lang"     % "scala-actors"   % scalaVersion.value, // to compile legacy Scala
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
)

// --------- Compilation options
Seq(
//  scalaVersion := "2.11.2",
  scalaVersion := "2.10.3",
  scalacOptions ++= Seq("-deprecation","-unchecked","-feature","-optimise","-Yinline-warnings"), // ,"-target:jvm-1.7"
  javacOptions ++= Seq("-Xlint:unchecked","-Xlint:-options","-source","1.6","-target","1.6") // forces JVM 1.6 compatibility with JDK 1.7 compiler
)
