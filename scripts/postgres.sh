#!/bin/sh
#
# Helper to compute results on PostgreSQL database system.
# Usage: postgres.sh help
#

PSQL="/usr/local/bin/psql -h/usr/local/pgsql/socket -q"

PG_BASE=ddbt
PG_USER=root

cd `dirname $0`; cd ..
DBT_REPO=`sed 's/#.*//g' conf/ddbt.properties | grep ddbt.base_repo | sed 's/.*= *//g'`
DBT_DATA="$DBT_REPO/dbtoaster/experiments/data"
DBT_QUERIES="$DBT_REPO/dbtoaster/compiler/alpha5/test/queries"
if [ "$DBT_REPO" = "" ]; then echo "No repository configured in conf/ddbt.properties"; exit 0; fi

case "$1" in
# ------------------------------------------------------------------------------
""|-h|help|-help|--help)
	exec cat<<EOF
`basename $0` [options] <action|query>
    create     create postgresql database
    remove     remove postgresql database
    tpch       load TPCH testing datasets
    finance    load financial testing datasets
    help       display available commands
    <query>    execute test/queries/<query>
options:
    -d <set>   change dataset (tiny, standard, ...)
EOF
;;
# ------------------------------------------------------------------------------
create) exec $PSQL -U${PG_USER} postgres<<EOF
CREATE DATABASE ${PG_BASE} OWNER ${PG_USER} ENCODING 'unicode';
GRANT ALL PRIVILEGES ON DATABASE ${PG_BASE} to ${PG_USER};
EOF
;;
# ------------------------------------------------------------------------------
remove) exec $PSQL -U${PG_USER} postgres<<EOF
DROP DATABASE IF EXISTS ${PG_BASE};
EOF
;;
# ------------------------------------------------------------------------------
tpch) for ds in TINY TINY_DEL STANDARD STANDARD_DEL BIG BIG_DEL; do
	printf "TPCH_$ds:"
	printf " schemas"
	$PSQL -U${PG_USER} ${PG_BASE}<<EOF
DROP SCHEMA IF EXISTS "TPCH_$ds" CASCADE;
CREATE SCHEMA "TPCH_$ds";

CREATE TABLE IF NOT EXISTS "TPCH_$ds".CUSTOMER (
  CUSTKEY    int NOT NULL,
  NAME       varchar(25) NOT NULL,
  ADDRESS    varchar(40) NOT NULL,
  NATIONKEY  int NOT NULL,
  PHONE      char(15) NOT NULL,
  ACCTBAL    decimal(10,2) NOT NULL,
  MKTSEGMENT char(10) NOT NULL,
  COMMENT    varchar(117) NOT NULL,
  PRIMARY KEY (CUSTKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".LINEITEM (
  ORDERKEY      int NOT NULL,
  PARTKEY       int NOT NULL,
  SUPPKEY       int NOT NULL,
  LINENUMBER    int NOT NULL,
  QUANTITY      decimal(20,10) NOT NULL,
  EXTENDEDPRICE decimal(10,2) NOT NULL,
  DISCOUNT      decimal(10,10) NOT NULL,
  TAX           decimal(10,10) NOT NULL,
  RETURNFLAG    char(1) NOT NULL,
  LINESTATUS    char(1) NOT NULL,
  SHIPDATE      date NOT NULL,
  COMMITDATE    date NOT NULL,
  RECEIPTDATE   date NOT NULL,
  SHIPINSTRUCT  char(25) NOT NULL,
  SHIPMODE      char(10) NOT NULL,
  COMMENT       varchar(44) NOT NULL,
  PRIMARY KEY (ORDERKEY, LINENUMBER)
);

CREATE INDEX ON "TPCH_$ds".LINEITEM (PARTKEY);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".NATION (
  NATIONKEY int NOT NULL,
  NAME      char(25) NOT NULL,
  REGIONKEY int NOT NULL,
  COMMENT   varchar(152) NOT NULL,
  PRIMARY KEY (NATIONKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".ORDERS (
  ORDERKEY      int NOT NULL,
  CUSTKEY       int NOT NULL,
  ORDERSTATUS   char(1) NOT NULL,
  TOTALPRICE    decimal(10,2) NOT NULL,
  ORDERDATE     date NOT NULL,
  ORDERPRIORITY char(15) NOT NULL,
  CLERK         char(15) NOT NULL,
  SHIPPRIORITY  int NOT NULL,
  COMMENT       varchar(79) NOT NULL,
  PRIMARY KEY (ORDERKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".PART (
  PARTKEY     int NOT NULL,
  NAME        varchar(55) NOT NULL,
  MFGR        char(25) NOT NULL,
  BRAND       char(10) NOT NULL,
  TYPE        varchar(25) NOT NULL,
  SIZE        int NOT NULL,
  CONTAINER   char(10) NOT NULL,
  RETAILPRICE decimal(10,2) NOT NULL,
  COMMENT     varchar(23) NOT NULL,
  PRIMARY KEY (PARTKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".PARTSUPP (
  PARTKEY    int NOT NULL,
  SUPPKEY    int NOT NULL,
  AVAILQTY   int NOT NULL,
  SUPPLYCOST decimal(10,2) NOT NULL,
  COMMENT    varchar(199) NOT NULL,
  PRIMARY KEY (PARTKEY,SUPPKEY)
-- For the standard and tiny datasets the reference integrity is not preserved.
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".REGION (
  REGIONKEY int NOT NULL,
  NAME      char(25) NOT NULL,
  COMMENT   varchar(152) NOT NULL,
  PRIMARY KEY (REGIONKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".SUPPLIER (
  SUPPKEY   int NOT NULL,
  NAME      char(25) NOT NULL,
  ADDRESS   varchar(40) NOT NULL,
  NATIONKEY int NOT NULL,
  PHONE     char(15) NOT NULL,
  ACCTBAL   decimal(10,2) NOT NULL,
  COMMENT   varchar(101) NOT NULL,
  PRIMARY KEY (SUPPKEY)
);

DELETE FROM "TPCH_$ds".LINEITEM;
DELETE FROM "TPCH_$ds".ORDERS;
DELETE FROM "TPCH_$ds".PARTSUPP;
DELETE FROM "TPCH_$ds".PART;
DELETE FROM "TPCH_$ds".SUPPLIER;
DELETE FROM "TPCH_$ds".CUSTOMER;
DELETE FROM "TPCH_$ds".NATION;
DELETE FROM "TPCH_$ds".REGION;
EOF
	printf " data"
	dir="`echo $ds | tr '[:upper:]' '[:lower:]'`"
	if [ "`echo $dir | grep '_del'`" != "" ]; then suf="_active"; else suf=""; fi
	$PSQL -U${PG_USER} ${PG_BASE}<<EOF
COPY "TPCH_$ds".REGION   FROM '${DBT_DATA}/tpch/$dir/region$suf.csv'   WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".NATION   FROM '${DBT_DATA}/tpch/$dir/nation$suf.csv'   WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".CUSTOMER FROM '${DBT_DATA}/tpch/$dir/customer$suf.csv' WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".SUPPLIER FROM '${DBT_DATA}/tpch/$dir/supplier$suf.csv' WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".PART     FROM '${DBT_DATA}/tpch/$dir/part$suf.csv'     WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".PARTSUPP FROM '${DBT_DATA}/tpch/$dir/partsupp$suf.csv' WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".ORDERS   FROM '${DBT_DATA}/tpch/$dir/orders$suf.csv'   WITH DELIMITER AS '|'; 
COPY "TPCH_$ds".LINEITEM FROM '${DBT_DATA}/tpch/$dir/lineitem$suf.csv' WITH DELIMITER AS '|'; 
EOF
	echo '.'
done;;
# ------------------------------------------------------------------------------
finance) for ds in TINY STANDARD BIG HUGE; do
	printf "FINANCE_$ds:"
	printf " schemas"
	$PSQL -U${PG_USER} ${PG_BASE}<<EOF
DROP SCHEMA IF EXISTS "FINANCE_$ds" CASCADE;
CREATE SCHEMA "FINANCE_$ds";

CREATE TABLE IF NOT EXISTS "FINANCE_$ds".ASKS (
  T         float NOT NULL,
  ID        int NOT NULL,
  BROKER_ID int NOT NULL,
  VOLUME    float NOT NULL,
  PRICE     float NOT NULL
);

CREATE TABLE IF NOT EXISTS "FINANCE_$ds".BIDS (
  T         float NOT NULL,
  ID        int NOT NULL,
  BROKER_ID int NOT NULL,
  VOLUME    float NOT NULL,
  PRICE     float NOT NULL
);

DELETE FROM "FINANCE_$ds".ASKS;
DELETE FROM "FINANCE_$ds".BIDS;
EOF
	printf " data"
	dir="`echo $ds | tr '[:upper:]' '[:lower:]'`"
	$PSQL -U${PG_USER} ${PG_BASE}<<EOF
COPY "FINANCE_$ds".ASKS FROM '${DBT_DATA}/finance/$dir/asks_export.csv' WITH DELIMITER AS ','; 
COPY "FINANCE_$ds".BIDS FROM '${DBT_DATA}/finance/$dir/bids_export.csv' WITH DELIMITER AS ','; 
EOF
	echo '.'
done;;
# ------------------------------------------------------------------------------
mddb)
;;
# ------------------------------------------------------------------------------
simple)
;;
# ------------------------------------------------------------------------------
employee)
;;
# ------------------------------------------------------------------------------
*)
	#./postgres.sh -d tiny finance/chrissedtrades
	ds=STANDARD;
	if [ "$1" = "-d" ]; then shift; ds="$1"; shift; fi
	tp="`echo $1 | sed 's/\/.*//g'`"
	query="`tr '\n' ' ' < ${DBT_QUERIES}/$1.sql`"
	query=`echo "$query" | sed 's/.*; *SELECT/SELECT/g' | sed 's/  */ /g'`

	$PSQL -U${PG_USER} -AtF "," ${PG_BASE}<<EOF
SET search_path='`echo ${tp}_${ds} | tr '[:lower:]' '[:upper:]'`';
$query
EOF

;;
# ------------------------------------------------------------------------------
esac	

exit
