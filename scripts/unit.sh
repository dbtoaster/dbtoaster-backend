#!/bin/sh
#
# Continuous integration script that automate setup and periodic updates for
# the unit tests. It also sends mails to developers when a build has finished.
#
# Options:
#    -lms     enable unit tests for LMS code generator
#    -akka    enable unit tests for Akka code generator
#    -live    periodically poll repositories for new updates and send mail
#             with the results of the compilation
#

cd `dirname $0`; cd ..;
BASE=`pwd`
CONF="conf/ddbt.properties"
REPO=`cat $CONF 2>/dev/null | sed 's/#.*//g' | grep ddbt.base_repo | sed 's/.*= *//g'`
DIST="http://www.dbtoaster.org/dist/dbtoaster_ubuntu12.04_x86_64_2827.tgz"

# argument options
lms=""
akka=""
live=""
build=""
args="scripts/unit.sh `echo $@ | sed 's/ *-build//g'` -build"

while [ "$1" ]; do case "$1" in
  "-lms") lms=1;;
  "-akka") akka=1;;
  "-live") live=1;;
  "-build") build=1;;
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
      cd virtualization-lms-core; git checkout booster-develop-0.3;
      echo 'sbt.version=0.13.0' > project/build.properties; sbt publish-local;
    else
      cd virtualization-lms-core; r1=`git_vers`; git pull >/dev/null; r2=`git_vers`;
      if [ "$r1" != "$r2" ]; then echo UP; sbt publish-local; fi
    fi; cd $BASE
  fi
  # Front-end
  if [ "$REPO" ]; then
    cd $REPO/dbtoaster/compiler/alpha5; r1=`svn_vers`; svn update >/dev/null; r2=`svn_vers`
    if [ "$r1" != "$r2" ]; then echo UP; make clean; make; fi; cd $BASE
  fi
}

###### EXECUTING TESTS
lms_get() { cat $CONF | sed 's/#.*//g' | grep ddbt.lms | sed 's/.*= *//g'; }
lms_set() { # $1 = 1/0 to enable/disable LMS
  if [ ! "`lms_get`" ]; then echo "ddbt.lms=$1\n" >> $CONF; fi
  perl -pi -e 's/ddbt.lms *=[^#]*/ddbt.lms='"$1"'\n/g' $CONF
}
sep() { echo -------------------------------------------------------------------; }
do_exec() {
  if [ ! "$REPO" ]; then
    # Travis-CI / standalone
    lms_set 0; sbt test
    if [ "$lms" ]; then lms_set 1; sbt test; fi
  else
    # DBToaster developers
    lms_bk="`lms_get`"
    lms_set 0; echo 'Scala'; sep; sbt queries; sep;
    if [ "$lms" ]; then lms_set 1; echo 'LMS'; sep; sbt queries-lms; sep; fi
    if [ "$akka" ]; then lms_set 0; echo 'Akka'; sep; sbt queries-akka; sep; fi
    lms_set "$lms_bk"
  fi
}

###### CONTINUOUS INTEGRATION
do_live() {
  subj=`date "+DDBT build %Y-%m-%d %H:%M:%S"`
  dest="thierry.coppey@epfl.ch andres.notzli@epfl.ch"
  (
  echo 'Front-end latest commit:'; cd $REPO; svn info | grep Last | sed 's/^/   /g'; sep;
  echo 'DDBToaster latest commit:'; cd $BASE; git log -1 | sed 's/^/   /g'; sep;
  do_exec
  ) | tee /dev/stderr | perl -p -e 's/(\x1B\[[0-9]+m|\x1BM\x1B\[2K.*\n)//g' \
    | sed 's/\[info\] //g' | grep -vEe '(-+ test/queries|Query .* generated|- .* correct|Dataset )' \
    | perl -p -e 'undef $/; $_=<>; s/(\n[a-zA-Z0-9]+Spec:)+\n([a-zA-Z0-9]+Spec:)/\n\2/g;' \
    | grep -vEe '^(Set current|Updating|Resolving|nVars=)' \
    | scripts/pushover.sh \
    | mail -s "$subj" $dest;
}

printf "Setup..."; do_setup; echo ' done.';

if [ "$build" ]; then echo 'New build...'; do_live; fi
if [ "$live" ]; then while true; do
  sleep 120;
  printf "Polling..."; updt=`do_update`
  if [ "$updt" ]; then echo ' updated.';
    cd $BASE; exec $args
    #do_live
  else echo ' up to date.'; fi
done; else
  printf "Update..."; do_update; echo '';
  do_exec
fi
