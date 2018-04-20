## DBToaster Backend

[DBToaster](http://www.dbtoaster.org) creates query engines for incremental view maintenance (IVM) by recursively computing the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems. More information:

   * [DB Toaster website](http://www.dbtoaster.org)
   * [DATA laboratory, EPFL](http://data.epfl.ch/dbtoaster)

DBToaster consists of two major components: [frontend](https://github.com/dbtoaster/dbtoaster-a5) and [backend](https://github.com/epfldata/dbtoaster-backend). The [frontend](https://github.com/dbtoaster/dbtoaster-a5) of DBToaster accepts SQL queries and emits IVM triggers in M3 language, which is an intermediate language used internally in DBToaster for representing these triggers. The backend (i.e., this project) accepts the set of trigger programs in M3 language, efficiently compiles them and generates highly efficient IVM programs in multiple target execution environment.

#### Status
Currently the project matches original DBToaster code generation based on M3 and can target
 [Scala](http://scala-lang.org),
 [C++11](http://www.stroustrup.com/C++11FAQ.html) and distributed
 [Spark](http://spark.apache.org/) backends.

#### Setup
1. Install [Scala 2.11](https://www.scala-lang.org/download/), [SBT](http://www.scala-sbt.org/release/docs/Getting-Started/Setup.html) and [Git](http://git-scm.com) in your PATH.
2. Checkout the repository `$ git clone https://github.com/epfldata/dbtoaster-backend`
3. Get some data/queries to play with: add `bin/dbtoaster_frontend` and `examples/{data,queries}` from [here](https://dbtoaster.github.io/) to the `dbtoaster-backend` folder (keep the same paths).
4. Execute the compiler using `$ sbt 'toast <options> <sql_input>'`. For example, `sbt 'toast -l cpp examples/queries/simple/r_count.sql'`. The list of available options is show using `$ sbt 'toast --help'`.
5. You can also run the whole test suit by following the extended setup.

#### [Optional] Extended setup (to connect with dbtoaster-frontend)
1. Follow steps 1 and 2 from the basic setup. No need to copy `bin/dbtoaster_frontend`.
2. Checkout the DBToaster [front-end repository](https://github.com/dbtoaster/dbtoaster-a5). You will need [OCaml](http://caml.inria.fr/download.en.html) to compile the front-end. Compile using the `make` command.
3. Create a file `ddbtoaster/conf/ddbt.properties` and set `ddbt.base_repo` path to dbtoaster-frontend repository (required for unit tests). A sample configuration file named `ddbtoaster/conf/ddbt.properties.example` exists in the repository. You can create a copy of it, rename it to `ddbtoaster/conf/ddbt.properties`, and modify it to have your desired parameters.
4. Execute the compiler using `$ sbt 'toast <options> <sql_input>'`. For example, `sbt 'toast -l cpp test/queries/simple/r_count.sql'`. Note that filenames are relative to `ddbt.base_repo`. Use absolute filenames if necessary.
5. Run unit tests and benchmarking: `$ sbt 'unit --help'`
   
   Please note that for running the unit tests, you need the base data files for the relations. Currently, these data files are missing from the front-end repository. Please contact us if you want to get access to these base data files for running the tests.

#### Instructions for running the distributed version

Currently, DBToaster provides a limited support for distributed incremental evaluation. The current implementation can compile the provided TPCH-like queries into executable Spark programs.

1. Follow the extended setup from above.
2. Set `ddbt.lms=1` in `ddbtoaster/conf/ddbt.properties`.
3. Generate a Spark program for incrementally computing a TPCH query. For instance, `sbt 'toast -l spark --batch -O3 test/queries/tpch/query1.sql -o tpch1.scala'`
4. Compile the generated Spark program for the target execution environment. 


#### Troubleshooting
- __UnsupportedClassVersionError: Unsupported major.minor version 51.0__
  - If you are getting this exception, make sure that you have a JRE for Java 7 installed.
  - For Ubuntu you can solve the problem by installing version 7 of OpenJDK:
      - `sudo apt-get install openjdk-7-jre`
  - You can also force Java 6 compatibility in build.sbt
     - Make sure `scalacOptions` does not contain `-target:jvm-1.7`
     - Add `javacOptions ++= Seq("-source","1.6","-target","1.6")`
