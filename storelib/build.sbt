Seq(
  // --------- Project informations
  name := "dbtoaster-sstore",

  // --------- Paths  
  scalaSource in Compile <<= baseDirectory / "src",
  javaSource in Compile <<= baseDirectory / "src",
  sourceDirectory in Compile <<= baseDirectory / "src"
)

libraryDependencies ++= Seq(
  "org.scala-lang.modules" % "scala-xml_2.11" % "1.0.5",
  "com.typesafe.akka" %% "akka-actor"     % "2.5.32",
  "com.typesafe.akka" %% "akka-remote"    % "2.5.32",
  "org.scala-lang"     % "scala-compiler" % scalaVersion.value
)