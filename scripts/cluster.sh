#!/bin/sh
#
# CLUSTER CONFIGURATION
#
PORT=2551
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

cd `dirname $0`; cd ..; base=`pwd`; 
pkgdir="$base/pkg"
cmd_launch() { # $1=host $2,...=arguments
  local host="$1"; shift
  if [ "$DEBUG" ]; then nohup $CMD_SSH $CMD_USER@$host "$CMD_DIR/scripts/cluster.sh launcher $@"; 
  else nohup $CMD_SSH $CMD_USER@$host "$CMD_DIR/launcher $@"; fi
}

wn=0; for w in $WORKERS; do wn=`expr $wn + 1`; done
case "$1" in
  "launcher") shift; exec $CMD_SBT "run-main ddbt.lib.ClusterApp -m $MASTER:$PORT -n $wn $*";; # debug helper
  "pkg") if [ "$DEBUG" ]; then echo 'Debug mode is enabled, skipped.'; exit; fi
    sbt pkg
    for w in $WORKERS; do printf "Transfer to $w ..."
      $CMD_CPY "$pkgdir/ddbt_deps.jar" $CMD_USER@$w:"$CMD_DIR/ddbt_deps.jar" >/dev/null
      $CMD_CPY "$pkgdir/ddbt_lib.jar" $CMD_USER@$w:"$CMD_DIR/ddbt_lib.jar" >/dev/null
      printf "#!/bin/sh\ncd \"\`dirname \$0\`\"\n" >$pkgdir/launcher
      echo "exec $CMD_JAVA -Djava.awt.headless=true -cp ddbt_lib.jar:ddbt_deps.jar ddbt.lib.ClusterApp -m $MASTER:$PORT -n $wn \"\$@\"" >> "$pkgdir/launcher";
      chmod +x "$pkgdir/launcher"
      $CMD_CPY "$pkgdir/launcher" $CMD_USER@$w:"$CMD_DIR/launcher" >/dev/null
      rm "$pkgdir/launcher"
      echo ' done.';
    done
  ;;
  ""|"help"|"-help"|"--help")
    cat<<EOF
Usage: `basename $0` <mode>
       pkg       build and ship JAR to remote nodes
       help      display help message
EOF
  ;;
  *)
    sbt compile || exit
    if [ "$DEBUG" ]; then trap "pkill java; exit 0" 0 1 2 3 9 15; fi
    i=1;
    for w in $WORKERS; do
      if [ "$DEBUG" ]; then p="`expr $PORT + $i `"; else p="$PORT"; fi
      (sleep 5 && cmd_launch $w -h $w:$p "$@" | sed 's/^/'$i': /g') &
      i=`expr $i + 1`
    done
    cmd_launch $MASTER -M "$@" | sed 's/^/M: /g'
  ;;
esac
