#!/bin/sh

DIST="http://www.dbtoaster.org/dist/dbtoaster_ubuntu12.04_x86_64_2827.tgz"

dbt_load() {
  if [ ! -f dbt.tgz ]; then ftp -o dbt.tgz $DIST; fi
  while [ "$1" != "" ]; do
    if [ ! -e "$1" ]; then tar -xzf dbt.tgz --strip-components 1 dbtoaster/$1; fi
    shift
  done
}

# SETUP ENVIRONMENT
cd `dirname $0`;
dbt_load bin/dbtoaster_release examples/data examples/queries lib/dbt_scala/dbtlib.jar

if [ ! -d conf ]; then mkdir conf; fi
cat>conf/ddbt.properties<<EOF
ddbt.dbtoaster = bin/dbtoaster_release
EOF

# RUN TESTS
sbt test
exec sbt 'test:run-main ddbt.test.Benchmark'
