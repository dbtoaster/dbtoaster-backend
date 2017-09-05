Seq(
  // --------- Project information
  name := "dbtoaster-pardis",

  // --------- Compilation options
  javacOptions ++= Seq("-P:continuations:enable"),

  // --------- Paths
  scalaSource in Compile <<= baseDirectory / "."
)

autoCompilerPlugins := true
addCompilerPlugin("org.scala-lang.plugins" % "scala-continuations-plugin_2.11.8" % "1.0.3")

// --------- Pardis codegen -- START
{
  // generatorSettings
  import ch.epfl.data.sc.purgatory.plugin.PurgatoryPlugin._

  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) }
  catch { case _: Throwable => }

  Seq(
    // scalaSource in Compile <<= baseDirectory / "pardis", // incorrect; copied from lms
    // sourceDirectories in Compile ++= Seq(file("/Users/milllic/Documents/repo/work/merge/DDBToaster-MERGE/ddbtoaster/pardis")),

    libraryDependencies ++= Seq(
      "org.scala-lang.plugins" %% "scala-continuations-library" % "1.0.2",
      "ch.epfl.data" % "squid-sc-backend_2.11" % "0.1-SNAPSHOT",
      "ch.epfl.data" % "sc-pardis-compiler_2.11" % "0.1.4-SNAPSHOT",
      "ch.epfl.data" % "sc-pardis-quasi_2.11" % "0.1.4-SNAPSHOT"
    ),
    outputFolder := prop.getProperty("ddbt.pardis.outputFolder", "ddbtoaster/pardis/lifter"),
    inputPackage := prop.getProperty("ddbt.pardis.inputPackage", "ddbt.lib.store"),
    outputPackage := prop.getProperty("ddbt.pardis.outputPackage", "ddbt.lib.store.deep")
  ) ++ generatorSettings
}
// --------- Pardis codegen -- FINISH