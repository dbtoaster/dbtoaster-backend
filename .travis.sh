#!/bin/sh

DIST="http://www.dbtoaster.org/dist/dbtoaster_ubuntu12.04_x86_64_2827.tgz"

# SETUP ENVIRONMENT
cd `dirname $0`;
if [ ! -f dbt.tgz ]; then curl $DIST > dbt.tgz; fi
dbt_load() {
  while [ "$1" != "" ]; do
    if [ ! -e "$1" ]; then
      tar -xzf dbt.tgz --strip-components 1 dbtoaster/$1
    fi
    shift
  done
}
dbt_load bin/dbtoaster_release examples/data examples/queries lib/dbt_scala/dbtlib.jar

if [ ! -d conf ]; then mkdir conf; fi
cat>conf/ddbt.properties<<EOF
ddbt.dbtoaster = bin/dbtoaster_release
EOF

