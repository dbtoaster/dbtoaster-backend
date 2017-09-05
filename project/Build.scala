// import sbt._
// import Keys._

// object DDBToasterBuild extends Build {

//   // lazy val commonSettings = Seq(
//   //   // --------- Project information
//   //   organization := "ch.epfl.data",
//   //   version := "3.0",

//   //   // --------- Compilation options
//   //   scalaVersion := "2.11.11",    // LMS uses 2.11.2    
//   //   javacOptions ++= Seq("-Xlint:unchecked", "-Xlint:-options", "-source", "1.6", "-target", "1.6"),
//   //   scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-optimise", "-target:jvm-1.6" /* , "-Yinline-warnings" */),

//   //   // --------- Dependencies
//   //   resolvers += Resolver.sonatypeRepo("snapshots")
//   // )  
 
//   // lazy val storelib = Project(id = "storelib", base = file("storelib"), settings = commonSettings)

//   // lazy val core = Project(id = "core", base = file("ddbtoaster/core"), settings = commonSettings) dependsOn (storelib)

//   // lazy val sparklib = Project(id = "sparklib", base = file("ddbtoaster/spark"), settings = commonSettings) dependsOn (storelib) 

//   // lazy val lms = Project(id = "lms", base = file("ddbtoaster/lms"), settings = commonSettings) dependsOn (storelib, core, sparklib)

//   // lazy val pardis = Project(id = "pardis", base = file("ddbtoaster/pardis"), settings = commonSettings) dependsOn (storelib, core)

//   // lazy val DDBToaster = Project(id = "DDBToaster", base = file("ddbtoaster"), settings = commonSettings) dependsOn(core, lms, pardis) aggregate(core, sparklib, lms, pardis)
  
//   // lazy val root = Project(id = "root", base = file("."), settings = commonSettings) aggregate(DDBToaster, storelib)

//   // lazy val runtime = Project(id = "Runtime", base = file("runtime"), settings = commonSettings) dependsOn(storelib, pardis)
// }
