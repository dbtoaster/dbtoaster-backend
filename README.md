DDBToaster
==========

Distributed DB Toaster project.

DB Toaster allows incremental view maintenance (IVM) by recursively computing
the delta of each individual modification on the query result. This allow dramatic
speedup over traditional database systems.

DB Toaster website : http://www.dbtoaster.org

EPFL Lab website : http://data.epfl.ch

The goal of this project is to reuse as much as possible of the current infrastructure
and create a framework to distribute the data and maintenance load across multiple servers.

Setup
-----
1. Checkout this repository
2. Create conf/ddbt.properties and add the following properties:
   - ddbt.base_repo: checkout of DBToaster repository (required for unit tests)
   - ddbt.dbtoaster: dbtoaster binary (required if base_repo is not set)
3. Do what you want by modifying src/Compiler.scala and run it (WIP)

Status
------
Currently the project is in an early stage, where the goal is to match existing
DBToaster support for code generation. Once it is done, the back-end will be
forked in local and distributed code generation to support both vanilla Scala and
Akka-based distributed back-ends.

Roadmap
-------
Front-end:
- Complete SQL parser to generate correct AST (low priority)

Codegen:
- Fix failing/non-compiling test cases with vanilla Scala codegen
- Create Akka-based distributed codegen

Runtime:
- Experiment with Storm (or provide strong performance argument)
- Automate distribution and testing over remote nodes
