## Distributed DBToaster <!-- [![Build Status](https://api.travis-ci.org/TCKnet/DDBToaster.png?branch=master)](https://travis-ci.org/TCKnet/DDBToaster) -->
[DBToaster](http://www.dbtoaster.org) creates query engines for incremental view maintenance (IVM) by recursively computing the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems. More information:

   * [DB Toaster website](http://www.dbtoaster.org)
   * [DATA laboratory, EPFL](http://data.epfl.ch/dbtoaster)

The goal of Distributed DB Toaster project is to reuse the existing incrementalization infrastructure (front-end) and create a code generator (back-end) to distribute the data and updates load across multiple servers.

#### Status
Currently the project matches original DBToaster code generation based on M3 and can target
 [Scala](http://scala-lang.org),
 [LMS](https://github.com/TiarkRompf/virtualization-lms-core) and distributed
 [Akka](http://akka.io) backends (C++ support is currently suspended).

#### Setup
1. Install [SBT](http://www.scala-sbt.org/release/docs/Getting-Started/Setup.html) and [Git](http://git-scm.com) in your PATH.
2. Checkout the repository `$ git clone https://github.com/tcknet/ddbtoaster.git`
3. Get some data/queries to play with: add `bin/dbtoaster_release` and `examples/{data,queries}` from [here](http://www.dbtoaster.org/index.php?page=download) to the DDBToaster folder (keep the same paths).
4. Execute the compiler using `$ sbt 'toast <options> <sql_input>'`. The list of available options is show using `$ sbt 'toast --help'`.
5. You can also use LMS and Akka by following the extended setup, however, you will not be able to run the tests as they are stored in DBToaster (private) repository.

#### Extended setup (DATA Lab members only)
1. Checkout and compile DBToaster (you'll need [OCaml](http://caml.inria.fr/download.en.html) and [Boost](http://www.boost.org/users/download/) to compile the front-end.
2. To support legacy LMS (`-O4`), you need to recompile DBToaster:
   - `svn patch dbtoaster/compiler/alpha5/lms.patch`
   - `make -C dbtoaster/compiler/alpha5`
   - Copy the following libraries in `dbtoaster/compiler/alpha5/lib/dbt_scala`: `scala-compiler.jar`, `scala-library.jar`, `scala-reflect.jar`, `dbtlib.jar`, `lms.jar`, `toasterbooster.jar`, `tuplegen.jar`

3. Checkout and publish locally LMS from the DATA lab repository
   - `git clone https://github.com/epfldata/lms.git`
   - `git checkout booster-develop-0.3 && sbt publish-local`
4. Create a file `conf/ddbt.properties` to suit your needs. In particular:
   - `ddbt.base_repo` path to DBToaster repository (required for unit tests)
   - `ddbt.dbtoaster` dbtoaster binary (required if `base_repo` is not set)
   - `ddbt.lms = 1` to enable LMS support (actual source files are in `lms/` folder)
   - Options to run unit tests and benchmarking: `$ sbt 'unit --help'`
   - Tests queries using `$ sbt queries`, `$ sbt queries-lms`, `$ sbt queries-akka`

#### Instructions for running the distributed version
1. Generate the code for distributed execution of your query, using:
   - `sbt unit -q <SQL FILE PATH> -l akka`
2. Configure distributed execution parameters in "conf/ddbt.properties"
   - `make sure that you can connect from this machine to all master/worker nodes via SSH without the need for entering the password.`
3. Open sbt, and run:
   - `"pkg full" to create a package containing all dependencies in "pkg" folder`
   - `"test:compile" to compile your generated code for distributed execution`
   - `"pkg dist" to ship the packages to the cluster`
4. Executing the distributed program, using:
   - `"sbt exec <TARGET_CLASS_NAME>"`

#### Roadmap
__Codegen__

- Add a new distribution and partition analysis phase _(high priority)_
- Merge contextual analyses that are currently done 3x in each code generators in an new phase that targets a lower-level (imperative?) language (discuss this with Amir, Vojin to integrate best with upcoming new LMS)
- Create LMS/[Boost](http://www.boost.org)-based C++ codegen _(low priority)_

__Front-end__

- Complete SQL parser to generate correct AST _(low priority)_

__Language__

- Extend the M3 language to support reactive programming and recursive evaluation

#### Troubleshooting
- __UnsupportedClassVersionError: Unsupported major.minor version 51.0__
  - If you are getting this exception, make sure that you have a JRE for Java 7 installed.
  - For Ubuntu you can solve the problem by installing version 7 of OpenJDK:
      - `sudo apt-get install openjdk-7-jre`
  - You can also force Java 6 compatibility in build.sbt
     - Make sure `scalacOptions` does not contain `-target:jvm-1.7`
     - Add `javacOptions ++= Seq("-source","1.6","-target","1.6")`
