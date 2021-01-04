jsProjectPath="/home/amir/dbtoaster.js"
jsfile=$jsProjectPath/target/scala-2.12/scalajs-bundler/main/dbtoaster-js-fastopt.js
scalaOutputPath="."
queryName=$1
cp $scalaOutputPath/$queryName.scala $jsProjectPath/$queryName.scala
cd $jsProjectPath
sbt clean
sbt fastOptJS::webpack
sed -i 's/var req = new $g.XMLHttpRequest();/var XMLHttpRequest = require(\x27xhr2\x27); var req = new XMLHttpRequest();/g'  $jsfile 
sbt run 
rem $jsProjectPath/$queryName.scala 

