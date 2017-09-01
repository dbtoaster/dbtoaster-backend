import sbt._
import Keys._

object DDBToasterBuild extends Build {
 
  lazy val DDBToaster = Project(id = "DDBToaster", base = file("ddbtoaster")) dependsOn (storeLib, /* spark */)

  lazy val spark = Project(id = "DDBToaster-spark", base = file("spark")) dependsOn (shared)

  lazy val storelib = Project(id = "storelib", base = file("storelib"))

  lazy val root = Project(id = "root", base = file(".")) aggregate(DDBToaster, storelib)

  lazy val runtime = Project(id = "Runtime", base = file("runtime")) dependsOn(DDBToaster)

}
