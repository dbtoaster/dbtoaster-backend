## Distributed DB Toaster
DB Toaster allows incremental view maintenance (IVM) by recursively computing
the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems. More information:

   * [DB Toaster website](http://www.dbtoaster.org)
   * [DATA laboratory, EPFL](http://data.epfl.ch)

The goal of Distributed DB Toaster project is to reuse current infrastructure and create a framework to distribute the data and updates load across multiple servers.

#### Setup
1. Checkout the repository `$ git clone https://github.com/tcknet/ddbtoaster.git`
2. Get some data/queries to play with. Do you have access to DB Toaster repository? (i.e. are you in DATA lab?)
  - _No:_ add `bin/dbtoaster_release` and `examples/{data,queries}` from [here](http://www.dbtoaster.org/index.php?page=download) to the ddbtoaster folder (keep the same paths).
  - _Yes:_ Create a file `conf/ddbt.properties` and add the following properties:
     - `ddbt.base_repo` path to DB Toaster repository (required for unit tests)
     - `ddbt.dbtoaster` dbtoaster binary (required if base_repo is not set)
     - You can run DB Toaster unit tests of  using `$ sbt queries` (takes a while)
3. (Optional) To remove [Spark](http://spark-project.org) and Scala-actors dependencies (as they are not used), delete `src/examples`, `src/lib/MapsSpark.scala` and comment the appropriate lines in `build.sbt`.
4. Execute the compiler using `$ sbt 'run-main ddbt.Compiler <options> <sql_input>'`. You get the options description by running the compiler without arguments.

#### Status
Currently the project is in an early stage. It matches existing DBToaster support for code generation based on M3 (Scala only, without LMS optimization). The code generation will soon be extended to support distributed runtime based on Akka remote actors.

#### Roadmap
__Front-end__

- Complete SQL parser to generate correct AST _(low priority)_

__Codegen__

- Create [Akka](http://akka.io)-based distributed codegen _(high priority)_
- Create [LMS](https://github.com/TiarkRompf/virtualization-lms-core)-based Scala codegen
- Create LMS/[Boost](http://www.boost.org)-based C++ codegen

__Runtime__

- Experiment with [Storm](http://storm-project.net) (or provide strong performance argument)
- Experiment with bare Java NIO or JNI with C sockets
- Automate distribution and testing over remote nodes

__Language__

- Extend the M3 language to support reactive programming paradigm

#### Troubleshooting
__UnsupportedClassVersionError: Unsupported major.minor version 51.0__

If you are getting this exception, make sure that you have a JRE for Java 7 installed. 

For Ubuntu you can solve the problem by installing version 7 of OpenJDK:

`sudo apt-get install openjdk-7-jre`
