Seq(
  // --------- Project information
  name := "dbtoaster-spark",

  // --------- Paths
  scalaSource in Compile <<= baseDirectory / "src",
  javaSource in Compile <<= baseDirectory / "src",
  sourceDirectory in Compile <<= baseDirectory / "src",
  resourceDirectory in Compile <<= baseDirectory / "conf"
)

libraryDependencies ++= Seq(
  "org.apache.spark" %% "spark-core" % "2.2.0"
)