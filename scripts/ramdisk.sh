#!/bin/sh
#
# This script creates a Mac OS X ramdisk to 'hot' directories
#

SIZE_MB=512

cd  `dirname $0`; cd ..;
base=`pwd`
mpoint="$base/target";

rd_dev=`mount | grep "$mpoint" | sed 's/ .*//g'`

if [ "$rd_dev" != "" ]; then
  if [ "$1" = "" ]; then echo "Disk $rd_dev already mounted"
  else
    case $OSTYPE in
      darwin*) diskutil eject $rd_dev;;
      *) echo "Maybe try this command: umount $rd_dev";;
    esac;
    # remove redirections
    # rm "$base/test/gen"
  fi
  exit
fi

case $OSTYPE in
  darwin*)
    rd_size=`expr $SIZE_MB '*' 2048`
    rd_name=`basename $mpoint`
    rd_dev=`/usr/bin/hdiutil attach -nomount ram://$rd_size`
    diskutil erasevolume HFS+ $rd_name $rd_dev >/dev/null
    diskutil unmount $rd_dev >/dev/null
    diskutil mount -mountPoint $mpoint $rd_dev
	# chflags hidden $mpoint; killall Finder # nohidden
  ;;
  *) echo 'Sorry, no ramdisk script currently available';;
esac

# Extra redirections into ramdisk
redirect() { # $1=source $2=rd_folder
  dir="$2"; if [ "$dir" = "" ]; then dir=`basename $1`; fi
  if [ ! -d "$mpoint/$dir" ]; then mkdir "$mpoint/$dir"; fi
  if [ ! -e "$1" ]; then ln -s "$mpoint/$dir" "$1"; fi
}

#redirect "$base/test/gen"
