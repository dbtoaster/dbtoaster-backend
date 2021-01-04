SCALA_FILE="$1.scala"
JS_PROJECT="../dbtoaster.js"
cp $SCALA_FILE $JS_PROJECT/Main.scala
cd $JS_PROJECT
sbt "fastOptJS::webpack" > compile.txt 2>&1
JS_FILE=$JS_PROJECT/target/scala-2.12/scalajs-bundler/main/dbtoaster-js-fastopt.js
ls $JS_PROJECT/target/scala-2.12/scalajs-bundler/main/*.js
sed -i -e 's/var req = new $g.XMLHttpRequest();/var XMLHttpRequest = require("xhr2"); var req = new XMLHttpRequest();/g'  $JS_FILE 
cd -
cp $JS_FILE $1.js

