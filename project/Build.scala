import sbt._

object DDBToasterBuild extends Build {
 lazy val DDBToaster = Project(id = "DDBToaster", base = file("ddbtoaster")) dependsOn(storelib) 
 lazy val storelib = Project(id = "storelib", base = file("storelib"))
  lazy val root = Project(id = "root", base = file(".")) aggregate(DDBToaster, storelib)
  lazy val runtime = Project(id ="Runtime", base = file("runtime")) dependsOn(DDBToaster)	
}
