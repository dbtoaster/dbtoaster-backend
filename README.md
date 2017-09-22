## DBToaster Backend

[DBToaster](http://www.dbtoaster.org) creates query engines for incremental view maintenance (IVM) by recursively computing the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems. More information:

   * [DB Toaster website](http://www.dbtoaster.org)
   * [DATA laboratory, EPFL](http://data.epfl.ch/dbtoaster)

DBToaster consists of two major components: [frontend](https://github.com/mdashti/DDBtoaster) and [backend](https://github.com/epfldata/dbtoaster-backend). The [frontend](https://github.com/dbtoaster/dbtoaster-a5) of DBToaster accepts SQL queries and emits IVM triggers in M3 language, which is an intermediate language used internally in DBToaster for representing these triggers. The backend (i.e., this project) accepts the set of trigger programs in M3 language, efficiently compiles them and generates highly efficient IVM programs in multiple target execution environment.

#### Status
Currently the project matches original DBToaster code generation based on M3 and can target
 [Scala](http://scala-lang.org),
 [C++11](http://www.stroustrup.com/C++11FAQ.html) and distributed
 [Spark](http://spark.apache.org/) backends.

#### Setup
1. Install [SBT](http://www.scala-sbt.org/release/docs/Getting-Started/Setup.html) and [Git](http://git-scm.com) in your PATH.
2. Checkout the repository `$ git clone https://github.com/epfldata/dbtoaster-backend`
3. Get some data/queries to play with: add `bin/dbtoaster_frontend` and `examples/{data,queries}` from [here](https://dbtoaster.github.io/) to the `dbtoaster-backend` folder (keep the same paths).
4. Execute the compiler using `$ sbt 'toast <options> <sql_input>'`. The list of available options is show using `$ sbt 'toast --help'`.
5. You can also run the whole test suit by following the extended setup.

#### Extended setup (to connect with dbtoaster-frontend)
1. Checkout and compile DBToaster. You'll need [OCaml](http://caml.inria.fr/download.en.html) to compile the front-end. Please checkout the [front-end repository](https://github.com/dbtoaster/dbtoaster-a5) for more instructions.
2. Create a file `conf/ddbt.properties` to suit your needs. In particular:
   - `ddbt.base_repo` path to dbtoaster-frontend repository (required for unit tests)
   - `ddbt.dbtoaster` dbtoaster binary (required if `base_repo` is not set)
   - Options to run unit tests and benchmarking: `$ sbt 'unit --help'`
   - Tests queries using `$ sbt queries`.

   A sample configuration file named `conf/ddbt.properties.example` exists in the repository and you can create a copy of it, rename it to `conf/ddbt.properties` and modify it to have your desired parameters.

   Please note that for running the unit-tests, you need the base data files for the relations. Currently, these data files are missing from the front-end repository. Please contact us if you want to get access to these base data files for running the tests.

#### Instructions for running the distributed version

TBA

#### Troubleshooting
- __UnsupportedClassVersionError: Unsupported major.minor version 51.0__
  - If you are getting this exception, make sure that you have a JRE for Java 7 installed.
  - For Ubuntu you can solve the problem by installing version 7 of OpenJDK:
      - `sudo apt-get install openjdk-7-jre`
  - You can also force Java 6 compatibility in build.sbt
     - Make sure `scalacOptions` does not contain `-target:jvm-1.7`
     - Add `javacOptions ++= Seq("-source","1.6","-target","1.6")`
