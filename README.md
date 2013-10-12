## Distributed DB Toaster [![Build Status](https://api.travis-ci.org/TCKnet/DDBToaster.png?branch=master)](https://travis-ci.org/TCKnet/DDBToaster)
DB Toaster allows incremental view maintenance (IVM) by recursively computing
the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems. More information:

   * [DB Toaster website](http://www.dbtoaster.org)
   * [DATA laboratory, EPFL](http://data.epfl.ch)

The goal of Distributed DB Toaster project is to reuse current infrastructure and create a framework to distribute the data and updates load across multiple servers.

#### Setup
1. Checkout the repository `$ git clone https://github.com/tcknet/ddbtoaster.git`
2. Get some data/queries to play with. Do you have access to DB Toaster repository? (i.e. are you in DATA lab?)
  - _No:_ add `bin/dbtoaster_release` and `examples/{data,queries}` from [here](http://www.dbtoaster.org/index.php?page=download) to the DDBToaster folder (keep the same paths).
  - _Yes:_ Create a file `conf/ddbt.properties` and add the following properties:
     - `ddbt.base_repo` path to DB Toaster repository (required for unit tests)
     - `ddbt.dbtoaster` dbtoaster binary (required if base_repo is not set)
     - `ddbt.lms = 1` to enable LMS support (files in `lms/` folder)
     - `ddbt.lib_boost` optional folder for C++ Boost library (for legacy C++)
     - You can run DB Toaster unit tests of  using `$ sbt queries` (takes a while)
3. Execute the compiler using `$ sbt 'run-main ddbt.Compiler <options> <sql_input>'`. You get the options description by running the compiler without arguments.

#### Status
Currently the project matches original DBToaster code generation based on M3 for Scala and LMS backends (C++ support is suspended as maps performs better in JVM). The code generation is currently in the process of being extended to support distributed runtime based on Akka remote actors.

#### Roadmap
__Codegen__

- Create [Akka](http://akka.io)-based distributed codegen _(high priority)_
- Create LMS/[Boost](http://www.boost.org)-based C++ codegen _(low priority)_

__Runtime__

- Automate distribution and testing over remote nodes
- Use serialization frameworks like [Kryo](http://code.google.com/p/kryo/) and [FST](http://code.google.com/p/fast-serialization/) if needed
- Experiment with bare Java NIO and/or JNI with C sockets

__Front-end__

- Complete SQL parser to generate correct AST _(low priority)_

__Language__

- Extend the M3 language to support reactive programming and recursive evaluation

#### Troubleshooting
- __How to use the [LMS](https://github.com/TiarkRompf/virtualization-lms-core) code generator?__
  - Clone LMS: `git clone https://github.com/TiarkRompf/virtualization-lms-core.git`
  - Use the DATA branch and install: `git checkout booster-develop-0.3 && sbt publish-local` 
  - Make sure that `ddbt.lms = 1` in the configuration (see above).
  - You can now use the option `-l lms` when invoking the compiler
- __UnsupportedClassVersionError: Unsupported major.minor version 51.0__
  - If you are getting this exception, make sure that you have a JRE for Java 7 installed.
  - For Ubuntu you can solve the problem by installing version 7 of OpenJDK:
  - `sudo apt-get install openjdk-7-jre`
