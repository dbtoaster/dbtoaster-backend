# Installation on Windows

This document describes the installation of DBToaster and DDBToaster on Windows
for developers. Other versions of the tools and binaries described below might
work as well but are untested.

## Requirements
* Windows 7
* Java SE Development Kit 7 (64-bit)
* sbt 0.13.2
* Scala 2.10.3
* Cygwin (32-bit) with the following packages (and their dependencies):
   * gcc-g++ 4.8.2-2
   * Ocaml 4.01.0-1 (to compile DBToaster)
   * ruby 1.9.3-p484-1 (for the test scripts)
   * git 1.7.9-1 (to clone the DDBToaster repository)
   * git-svn 1.7.9-1 (to checkout the DBToaster repository)
   * libboost and libboost-devel 1.53.0-2

## Configuration

### Bash profile

Add the following lines to your `.bash_profile` file:

```
export SBT_HOME=<cygwin-style path to your sbt folder>
export SCALA_HOME=<cygwin-style path to your Scala folder>
export JAVA_HOME=<cygwin-style path to your JDK folder>
export PATH=$PATH:${SBT_HOME}/bin:${SCALA_HOME}/bin:${JAVA_HOME}/bin
```

### DDBToaster configuration

Use the following options in the DDBToaster configuration file
`conf/ddbt.properties`:

```
ddbt.base_repo = <Windows-style path to the DBToaster repository>
ddb.lib_boost = /usr/lib
ddbt.find_bin = <Windows-style path to your cygwin installation>\\bin\\find
```
