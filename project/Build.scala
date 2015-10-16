import sbt._
import Keys._

object DDBToasterBuild extends Build {
  lazy val root = Project(id = "DDBToaster", base = file(".")) //aggregate (spark)
 
  lazy val spark = Project(id = "DDBToaster-spark", base = file("spark")) dependsOn(root)
}
