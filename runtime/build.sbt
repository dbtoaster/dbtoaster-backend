Seq(
  // --------- Project informations
  name := "Runtime",

  // --------- Paths
  scalaSource in Compile <<= baseDirectory / "tpcc",
  javaSource in Compile <<= baseDirectory / "tpcc",
  sourceDirectory in Compile <<= baseDirectory / "tpcc",

  // --------- Execution options
  fork := true, // required to enable javaOptions
  javaOptions ++= Seq("-Xss128m","-XX:-DontCompileHugeMethods","-XX:+CMSClassUnloadingEnabled"),
  javaOptions ++= Seq("-Xmx4G","-Xms1G"/*,"-verbose:gc"*/), parallelExecution in Test := false, // for large benchmarks
  javaOptions <+= (fullClasspath in Runtime) map (cp => "-Dsbt.classpath=" + cp.files.absString) // propagate paths
)

libraryDependencies ++= Seq(
  "org.slf4j" % "slf4j-api" % "1.7.30"
)