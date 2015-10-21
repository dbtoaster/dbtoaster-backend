import sbt._
import Keys._

object DDBToasterBuild extends Build {
 
  lazy val root = Project(id = "DDBToaster", base = file(".")) dependsOn (shared, spark)
 
  lazy val shared = Project(id = "DDBToaster-shared", base = file("shared"))
  
  lazy val spark = Project(id = "DDBToaster-spark", base = file("spark")) dependsOn (shared)
}
