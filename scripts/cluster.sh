#!/bin/sh
#
# CLUSTER CONFIGURATION
#
PARTS=2 # partitions per worker
PORT=22550 # base port
MASTER="127.0.0.1"
WORKERS="127.0.0.1 127.0.0.1 127.0.0.1 127.0.0.1"
DEBUG=1 # debug mode
#
# SYSTEM CONFIGURATIONS
#
CMD_USER="tck";                       # username on remote hosts
CMD_DIR="/Documents/EPFL/Data/ddbt";  # base folder on remote hosts
CMD_SSH="ssh -p 22";                  # ssh command 'ssh user@host exec <class> <options>'
CMD_CPY="rsync -av";                  # copy command 'cp src user@dest:dir'
CMD_JAVA="java -Xmx2G -Xms2G";        # Java path and options
CMD_SBT="/usr/local/bin/sbt"          # SBT path and options (debug mode only)

#
# Remotes
#
DEBUG=""
CMD_DIR="/Users/tck/ddbt"
#MASTER="192.168.0.2"
#WORKERS="192.168.0.3 192.168.0.2 192.168.0.3 192.168.0.2"
# andres / icdhcp-1-160.epfl.ch
#MASTER="128.179.149.67"
#WORKERS="128.179.149.67 128.179.149.67 128.178.116.160 128.178.116.160"
#
# End
#

cd `dirname $0`; cd ..; base=`pwd`; 
pkgdir="$base/pkg"
cmd_launch() { # $1=host $2,...=arguments
  local host="$1"; shift
  if [ "$DEBUG" ]; then nohup $CMD_SSH $CMD_USER@$host "$CMD_DIR/scripts/cluster.sh launcher $@"; 
  else nohup $CMD_SSH $CMD_USER@$host "$CMD_DIR/launcher $@"; fi
}

case "$1" in
  "launcher") shift; exec $CMD_SBT "run-main ddbt.lib.ClusterApp $*";; # debug helper
  "pkg") if [ "$DEBUG" ]; then echo 'Debug mode is enabled, skipped.'; exit; fi
    sbt pkg
    for w in $WORKERS; do printf "Transfer to $w ..."
      $CMD_SSH $CMD_USER@$w "mkdir -p $CMD_DIR"
      $CMD_CPY "$pkgdir/ddbt_deps.jar" $CMD_USER@$w:"$CMD_DIR/ddbt_deps.jar" >/dev/null
      $CMD_CPY "$pkgdir/ddbt_lib.jar" $CMD_USER@$w:"$CMD_DIR/ddbt_lib.jar" >/dev/null
      printf "#!/bin/sh\ncd \"\`dirname \$0\`\"\n" >$pkgdir/launcher
      echo "exec $CMD_JAVA -Djava.awt.headless=true -cp ddbt_lib.jar:ddbt_deps.jar ddbt.lib.ClusterApp \"\$@\"" >> "$pkgdir/launcher";
      chmod +x "$pkgdir/launcher"
      $CMD_CPY "$pkgdir/launcher" $CMD_USER@$w:"$CMD_DIR/launcher" >/dev/null
      rm "$pkgdir/launcher"
      echo ' done.';
    done
    # --- PKG-TEST
    sbt 'test:compile'
    for w in $WORKERS; do
      $CMD_SSH $CMD_USER@$w "mkdir -p $CMD_DIR/target/scala-2.10/test-classes"
      $CMD_CPY target/scala-2.10/test-classes/ $CMD_USER@$w:"$CMD_DIR/target/scala-2.10/test-classes/" >/dev/null
    done
    # --- PKG-TEST END
  ;;
  "help"|"-help"|"--help")
    cat<<EOF
Usage: `basename $0` <mode>
       pkg       build and ship JAR to remote nodes
       help      display help message
EOF
  ;;
  *)
    sbt compile || exit
    if [ "$DEBUG" ]; then trap "pkill java; exit 0" 0 1 2 3 9 15; fi
    for w in $WORKERS; do $CMD_SSH $CMD_USER@$w "killall java"; done
    ws=""; i=1
    for w in $WORKERS; do p="`expr $PORT + $i`"; i=`expr $i + 1`
      ws="$ws -w $w:$p:$PARTS"
      cmd_launch $w -h $w:$p:$PARTS "$@" | sed 's/^/'$i': /g' &
    done
    sleep 5
    cmd_launch $MASTER -h $MASTER:$PORT $ws "$@" | sed 's/^/M: /g'
  ;;
esac
