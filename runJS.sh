JS_PROJECT="../dbtoaster.js"
JS_FILE="ddbtoaster/target/tmp/$1"
cp $JS_FILE $JS_PROJECT/target/scala-2.12/scalajs-bundler/main/dbtoaster-js-fastopt.js
cd $JS_PROJECT
sbt run 2>run_error.txt