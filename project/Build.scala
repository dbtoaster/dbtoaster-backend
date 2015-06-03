import sbt._

object DDBToasterBuild extends Build {
  lazy val DDBToaster = Project(id = "root", base = file(".")) aggregate(root, storelib)
  lazy val storelib = Project(id = "storelib", base = file("storelib"))
  lazy val root = Project(id = "DDBToaster", base = file("ddbtoaster")) dependsOn(storelib)
}
