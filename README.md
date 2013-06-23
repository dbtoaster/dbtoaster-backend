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

Currently the project is in a very early stage.

Roadmap
------

Front-end
1. Parser: write full SQL (for future conversion in Scala) and M3 parsers
2. Typer: make sure that we get all needed types at appropriate place

Code gen & optimizer

Distribution
