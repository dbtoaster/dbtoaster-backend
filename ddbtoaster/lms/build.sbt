Seq(
  // --------- Project information
  name := "dbtoaster-lms",

  // --------- Paths
  scalaSource in Compile <<= baseDirectory / "."
)

// --------- LMS codegen, enabled with ddbt.lms = 1 in conf/ddbt.properties
{
  val prop = new java.util.Properties()
  try { prop.load(new java.io.FileInputStream("ddbtoaster/conf/ddbt.properties")) } 
  catch { case _: Throwable => }

  if (prop.getProperty("ddbt.lms","0") != "1") 
    Seq(
      sources in Compile ~= (_.filter(_.toString.endsWith("DefaultLMSGen.scala")))
    ) 
  else 
    Seq(
      sources in Compile ~= (_.filter(!_.toString.endsWith("DefaultLMSGen.scala"))),

      // --------- Compilation options
      scalaVersion := "2.11.2",
      scalaOrganization := "org.scala-lang.virtualized",
      scalacOptions ++= Seq("-Yvirtualize"),

      libraryDependencies ++= Seq(
        "org.scala-lang.virtualized" % "scala-library" % scalaVersion.value,
        "org.scala-lang.virtualized" % "scala-compiler" % scalaVersion.value,        
        "org.scalariform" %% "scalariform" % "0.2.3",
        "EPFL" %% "lms" % "0.3-SNAPSHOT"
      )
    )
}