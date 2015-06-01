import sbt._

object DDBToasterBuild extends Build {
  lazy val DDBToaster = Project(id = "root", base = file(".")) aggregate(root, sstore)
  lazy val sstore = Project(id = "sstore", base = file("sstore"))
  lazy val root = Project(id = "DDBToaster", base = file("ddbtoaster")) dependsOn(sstore)
}
