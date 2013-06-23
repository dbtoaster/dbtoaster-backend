// --------- project informations
Seq(
  name := "DistributedDBtoaster",
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

// --------- Dependencies
libraryDependencies ++= Seq(
//	"org.scala-lang" % "scala-reflect" % "2.10.2",
	"org.scala-lang" % "scala-actors" % "2.10.2",
    "org.scalatest" % "scalatest_2.10" % "2.0.M5b" % "test"
)

// --------- Compilation options
Seq(
  scalaVersion := "2.10.2",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-Yinline-warnings")
)


//scalaOrganization := "org.scala-lang.virtualized"
//scalaVersion := Option(System.getenv("SCALA_VIRTUALIZED_VERSION")).getOrElse("2.10.2-RC1")

//resolvers ++= Seq(
//    ScalaToolsSnapshots, 
//    "Sonatype Public" at "https://oss.sonatype.org/content/groups/public",
//	Classpaths.typesafeSnapshots
//)
//	"org.scalariform" %% "scalariform" % "0.1.4",
//    "ch.epfl" % "lms_2.10" % "0.4-SNAPSHOT"

//Our tests are not threadsafe so disabling parallel execution for now
//parallelExecution in Test := false
// disable publishing of main docs
//publishArtifact in (Compile, packageDoc) := false
// continuations
//autoCompilerPlugins := true
//libraryDependencies <<= (scalaVersion, libraryDependencies) { (ver, deps) =>
//    deps :+ compilerPlugin("org.scala-lang.plugins" % "continuations" % ver)
//}
//mainClass := Some("Main")
//selectMainClass := Some("Main")

