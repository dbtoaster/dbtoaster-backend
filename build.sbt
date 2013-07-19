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
libraryDependencies <++= scalaVersion(v=>Seq(
  "org.spark-project" %% "spark-core"   % "0.8.0-SNAPSHOT",
  "com.typesafe.akka" %% "akka-actor"   % "2.1.4",
  "com.typesafe.akka" %% "akka-remote"  % "2.1.4",
  "org.scala-lang"     % "scala-actors" % v,
  "org.scalatest"     %% "scalatest"    % "2.0.M5b" % "test"
))

// --------- Compilation options
Seq(
  scalaVersion := "2.10.2",
  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-Yinline-warnings")
)


Seq(
  autoCompilerPlugins := true,
  libraryDependencies <+= scalaVersion(v=>compilerPlugin("org.scala-lang.plugins" % "continuations" % v)),
  scalacOptions += "-P:continuations:enable"
)

// --------- Execution options
Seq(
  fork := true,
  javaOptions ++= Seq("-Xss128m" //"-Xss512m","-Xmx2G","-Xms2G","-XX:MaxPermSize=2G" //,"-verbose:gc"
      //"-agentpath:"+yjp+"=sampling,onexit=snapshot,builtinprobes=all"
  )
)





// libraryDependencies:
//	"org.scala-lang" % "scala-actors" % v,
//	"org.scala-lang" % "scala-reflect" % v,
//	"ch.epfl" %% "lms" % "0.4-SNAPSHOT",
//	"org.scalariform" %% "scalariform" % "0.1.4",
//parallelExecution in Test := false
//scalaOrganization := "org.scala-lang.virtualized"
//scalaVersion := Option(System.getenv("SCALA_VIRTUALIZED_VERSION")).getOrElse("2.10.2-RC1")
//resolvers ++= Seq(
//    ScalaToolsSnapshots, 
//    "Sonatype Public" at "https://oss.sonatype.org/content/groups/public",
//	Classpaths.typesafeSnapshots
//)
// disable publishing of main docs
//publishArtifact in (Compile, packageDoc) := false
// continuations
//autoCompilerPlugins := true
//libraryDependencies <<= (scalaVersion, libraryDependencies) { (ver, deps) =>
//    deps :+ compilerPlugin("org.scala-lang.plugins" % "continuations" % ver)
//}
//mainClass := Some("Main")
//selectMainClass := Some("Main")
