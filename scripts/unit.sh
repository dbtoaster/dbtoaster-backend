#!/bin/sh

DIST="http://www.dbtoaster.org/dist/dbtoaster_ubuntu12.04_x86_64_2827.tgz"

cd `dirname $0`; cd ..;
base=`pwd`
repo=`cat conf/ddbt.properties 2>/dev/null | sed 's/#.*//g' | grep ddbt.base_repo | sed 's/.*= *//g'`
lms=""
akka=""

while [ "$1" != "" ]; do case "$1" in
  "-lms") lms=1;;
  "-akka") akka=1;;
esac; shift; done

###### SETUP ENVIRONMENT
dbt_load() {
  if [ ! -f dbt.tgz ]; then curl $DIST > dbt.tgz; fi
  while [ "$1" != "" ]; do
    if [ ! -e "$1" ]; then
      tar -xzf dbt.tgz --strip-components 1 dbtoaster/$1
    fi
    shift
  done
  if [ ! -d conf ]; then mkdir conf; fi
  echo 'ddbt.dbtoaster = bin/dbtoaster_release' > conf/ddbt.properties
}

if [ "$repo" = "" ]; then
  dbt_load bin/dbtoaster_release examples/data examples/queries lib/dbt_scala/dbtlib.jar
fi

ddbt_lms() { # $1 = 1/0 to enable/disable LMS
  if [ "`cat conf/ddbt.properties | sed 's/#.*//g' | grep ddbt.lms`" = "" ]; then
    echo 'ddbt.lms = $1' >> conf/ddbt.properties
  fi
  perl -pi -e 's/ddbt.lms *= *[01]?/ddbt.lms = '"$1"'/g' conf/ddbt.properties
}

# LMS-ToasterBooster
if [ "$lms" ]; then
  cd $base; cd ..
  if [ ! -d "virtualization-lms-core" ]; then
    git clone https://github.com/TiarkRompf/virtualization-lms-core.git
    cd virtualization-lms-core; git checkout booster-develop-0.3; cd ..
  fi
  cd virtualization-lms-core; git pull; sbt publish-local; cd $base
fi

###### EXECUTING TESTS
if [ ! "$repo" ]; then
  # Travis-CI / standalone
  ddbt_lms 0; sbt test
  if [ "$lms" ]; then ddbt_lms 1; sbt test; fi
else
  # DBToaster developers
  lms_bk=`cat conf/ddbt.properties | sed 's/#.*//g' | grep ddbt.lms | sed 's/.*= *//g'`
  ddbt_lms 0; sbt queries
  if [ "$lms" ]; then ddbt_lms 1; sbt queries-lms; fi
  if [ "$akka" ]; then ddbt_lms 0; sbt queries-akka; fi
  ddbt_lms "$lms_bk"
fi
