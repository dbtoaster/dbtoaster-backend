#!/bin/sh
#
# This script wires up all the stuff to test legacy DBToaster results.
#
#  regress.sh [-d dataset] query
#

DBT='bin/dbtoaster_frontend'
#DBT='./dbtoaster_ref' # reference released version

cd `dirname $0`; cd ..
BOOST="`sed 's/#.*//g' conf/ddbt.properties | grep ddbt.lib_boost | sed 's/.*= *//g'`"
if [ "$BOOST" != "" ]; then BOOST="$BOOST"; export DYLD_LIBRARY_PATH="$BOOST/lib"; BOOST="-I$BOOST/include -L$BOOST/lib"; fi
cd "`sed 's/#.*//g' conf/ddbt.properties | grep ddbt.base_repo | sed 's/.*= *//g'`/dbtoaster/compiler/alpha5"

# We're now in original DBToaster repository

d='standard'; if [ "$1" = "-d" ]; then shift; d="$1"; shift; fi
q="test/queries/$1.sql"; if [ ! -f "$q" ]; then echo "query $1 does not exist"; exit; fi
gen() { # $1 = lang, $2=file
	printf ' gen'; $DBT -l $1 -O3 -o $2.tmp $q
	sed "s/\/standard\//\/$d\//g" $2.tmp > $2; rm $2.tmp
}

# Scala
printf '[--------------------- Scala:'
gen scala query.scala
printf ' compile'
fsc -cp lib/dbt_scala/dbtlib.jar query.scala lib/dbt_scala/src/org/dbtoaster/RunQuery.scala
echo '. ----]'
scala -J-Xmx14G -J-Xms14G -J-verbose:gc -cp .:lib/dbt_scala/dbtlib.jar org.dbtoaster.RunQuery
rm -r *.scala org

# CPP
printf '[--------------------- C++:'
gen cpp query.hpp
printf ' compile'
g++ -O3 -Ilib/dbt_c++ -Llib/dbt_c++ $BOOST -lpthread -ldbtoaster lib/dbt_c++/main.cpp -include query.hpp -o query \
	-lboost_program_options -lboost_serialization -lboost_system -lboost_filesystem -lboost_chrono -lboost_thread
echo '. ----]'
./query
rm *.hpp query
