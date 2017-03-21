#!/usr/bin/env bash
sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000  -csv lscala.csv -dump lscala.txt  -l lscala  -d big_del  -q  .*tpch.*"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000  -csv llms.csv -dump llms.txt  -l llms  -d big_del  -q  .*tpch.*"
sbt "DDBToaster/runMain  ddbt.UnitTest -x  -p 2 -w 0 -s 3 -t 60000  -csv lcpp.csv -dump lcpp.txt  -l lcpp  -d big_del  -q  .*tpch.*"
