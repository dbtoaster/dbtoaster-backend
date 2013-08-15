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
// Storm dependencies
/*
resolvers ++= Seq(
  "clojars" at "http://clojars.org/repo/",
  "clojure-releases" at "http://build.clojure.org/releases"
)
*/
libraryDependencies <++= scalaVersion(v=>Seq(
  "org.spark-project" %% "spark-core"   % "0.8.0-SNAPSHOT",
  "com.typesafe.akka" %% "akka-actor"   % "2.2.0",
  "com.typesafe.akka" %% "akka-remote"  % "2.2.0",
  "org.scala-lang"     % "scala-actors" % v,
  "org.scalatest"     %% "scalatest"    % "2.0.M5b" % "test"
  //"com.github.velvia" %% "scala-storm"  % "0.2.3-SNAPSHOT",
  //"storm"              % "storm"        % "0.8.2"
))

// --------- Compilation options
Seq(
  scalaVersion := "2.10.2",
  scalacOptions ++= Seq("-target:jvm-1.7", "-deprecation", "-unchecked", "-feature", "-optimise", "-Yinline-warnings")
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

{
  val t=TaskKey[Unit]("queries")
  Seq(
    fullRunTask(t in Compile, Compile, "ddbt.UnitTest", "tiny","tiny_del","standard","standard_del") //,
    //(test in Test) <<= (test in Test) dependsOn (t in Compile),   // force tests to rebuild
    //testOptions in Test += Tests.Argument("-l", "ddbt.SlowTest"), // execute only non-tagged tests
  )
}

//compile in Compile <<= (compile in Compile) map { x => ("src/librna/make target/scala-2.10/classes").run.exitValue; x }
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

