#!/bin/sh

cd `dirname $0`; cd ..;
BASE=`pwd`
CONF="conf/ddbt.properties"
REPO=`cat $CONF 2>/dev/null | sed 's/#.*//g' | grep ddbt.base_repo | sed 's/.*= *//g'`
DIST="http://www.dbtoaster.org/dist/dbtoaster_ubuntu12.04_x86_64_2827.tgz"

# argument options
lms=""
akka=""
live=""

while [ "$1" ]; do case "$1" in
  "-lms") lms=1;;
  "-akka") akka=1;;
  "-live") live=1;;
esac; shift; done

###### SETUP DEFAULT SETTINGS
dbt_load() {
  if [ ! -f dbt.tgz ]; then curl $DIST > dbt.tgz; fi
  while [ "$1" ]; do if [ ! -e "$1" ]; then tar -xzf dbt.tgz --strip-components 1 dbtoaster/$1; fi; shift; done
}
do_setup() {
  if [ ! "$REPO" ]; then dbt_load bin/dbtoaster_release examples/data examples/queries lib/dbt_scala/dbtlib.jar; fi
  if [ ! -d conf ]; then mkdir conf; fi
  if [ ! -f $CONF ]; then echo 'ddbt.dbtoaster = bin/dbtoaster_release' > $CONF; fi
}

###### UPDATING REPOSITORIES
git_vers() { git rev-parse HEAD; }
svn_vers() { svn info | grep Revision | sed 's/.*: *//g'; }
do_update() { # return "" if no update, nonempty otherwise
  # DDBT
  r1=`git_vers`; git pull >/dev/null; r2=`git_vers`;
  if [ "$r1" != "$r2" ]; then echo UP; fi
  
  # LMS-ToasterBooster
  if [ "$lms" ]; then
    cd $BASE; cd ..
    if [ ! -d "virtualization-lms-core" ]; then
      git clone https://github.com/TiarkRompf/virtualization-lms-core.git
      cd virtualization-lms-core; git checkout booster-develop-0.3; cd ..
    fi
    cd virtualization-lms-core; r1=`git_vers`; git pull >/dev/null; r2=`git_vers`;
    if [ "$r1" != "$r2" ]; then echo UP; sbt publish-local; fi; cd $BASE
  fi
  # Front-end
  echo "REPO"

  if [ "$REPO" ]; then
    cd $REPO; r1=`svn_vers`; svn update >/dev/null; r2=`svn_vers`
    if [ "$r1" != "$r2" ]; then echo UP; make clean; make; fi; cd $BASE
  fi
}

###### EXECUTING TESTS
lms_get() { cat $CONF | sed 's/#.*//g' | grep ddbt.lms | sed 's/.*= *//g'; }
lms_set() { # $1 = 1/0 to enable/disable LMS
  if [ ! "`lms_get`" ]; then echo 'ddbt.lms = $1' >> $CONF; fi
  perl -pi -e 's/ddbt.lms *= *[01]?/ddbt.lms = '"$1"'/g' $CONF
}
do_exec() {
  if [ ! "$REPO" ]; then
    # Travis-CI / standalone
    lms_set 0; sbt test
    if [ "$lms" ]; then ddbt_lms 1; sbt test; fi
  else
    # DBToaster developers
    lms_bk=`lms_get`
    lms_set 0; sbt queries
    if [ "$lms" ]; then lms_set 1; sbt queries-lms; fi
    if [ "$akka" ]; then lms_set 0; sbt queries-akka; fi
    lms_set "$lms_bk"
  fi
}

printf "Setup..."; do_setup; echo '';
printf "Update..."; do_update; echo '';
do_exec

if [ "$live" ]; then while true; do
  sleep 120;
  printf "Polling..."; updt=`do_update`
  if [ "$updt" ]; then echo ' updated. New build...'; do_exec;
  else echo ' up to date.'; fi
done; fi
