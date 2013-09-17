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
  C_CUSTKEY    int NOT NULL,
  C_NAME       varchar(25) NOT NULL,
  C_ADDRESS    varchar(40) NOT NULL,
  C_NATIONKEY  int NOT NULL,
  C_PHONE      char(15) NOT NULL,
  C_ACCTBAL    decimal(10,2) NOT NULL,
  C_MKTSEGMENT char(10) NOT NULL,
  C_COMMENT    varchar(117) NOT NULL,
  PRIMARY KEY (C_CUSTKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".LINEITEM (
  L_ORDERKEY      int NOT NULL,
  L_PARTKEY       int NOT NULL,
  L_SUPPKEY       int NOT NULL,
  L_LINENUMBER    int NOT NULL,
  L_QUANTITY      decimal(20,10) NOT NULL,
  L_EXTENDEDPRICE decimal(10,2) NOT NULL,
  L_DISCOUNT      decimal(10,10) NOT NULL,
  L_TAX           decimal(10,10) NOT NULL,
  L_RETURNFLAG    char(1) NOT NULL,
  L_LINESTATUS    char(1) NOT NULL,
  L_SHIPDATE      date NOT NULL,
  L_COMMITDATE    date NOT NULL,
  L_RECEIPTDATE   date NOT NULL,
  L_SHIPINSTRUCT  char(25) NOT NULL,
  L_SHIPMODE      char(10) NOT NULL,
  L_COMMENT       varchar(44) NOT NULL,
  PRIMARY KEY (L_ORDERKEY, L_LINENUMBER)
);

CREATE INDEX ON "TPCH_$ds".LINEITEM (L_PARTKEY);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".NATION (
  N_NATIONKEY int NOT NULL,
  N_NAME      char(25) NOT NULL,
  N_REGIONKEY int NOT NULL,
  N_COMMENT   varchar(152) NOT NULL,
  PRIMARY KEY (N_NATIONKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".ORDERS (
  O_ORDERKEY      int NOT NULL,
  O_CUSTKEY       int NOT NULL,
  O_ORDERSTATUS   char(1) NOT NULL,
  O_TOTALPRICE    decimal(10,2) NOT NULL,
  O_ORDERDATE     date NOT NULL,
  O_ORDERPRIORITY char(15) NOT NULL,
  O_CLERK         char(15) NOT NULL,
  O_SHIPPRIORITY  int NOT NULL,
  O_COMMENT       varchar(79) NOT NULL,
  PRIMARY KEY (O_ORDERKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".PART (
  P_PARTKEY     int NOT NULL,
  P_NAME        varchar(55) NOT NULL,
  P_MFGR        char(25) NOT NULL,
  P_BRAND       char(10) NOT NULL,
  P_TYPE        varchar(25) NOT NULL,
  P_SIZE        int NOT NULL,
  P_CONTAINER   char(10) NOT NULL,
  P_RETAILPRICE decimal(10,2) NOT NULL,
  P_COMMENT     varchar(23) NOT NULL,
  PRIMARY KEY (P_PARTKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".PARTSUPP (
  PS_PARTKEY    int NOT NULL,
  PS_SUPPKEY    int NOT NULL,
  PS_AVAILQTY   int NOT NULL,
  PS_SUPPLYCOST decimal(10,2) NOT NULL,
  PS_COMMENT    varchar(199) NOT NULL,
  PRIMARY KEY (PS_PARTKEY,PS_SUPPKEY)
-- For the standard and tiny datasets the reference integrity is not preserved.
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".REGION (
  R_REGIONKEY int NOT NULL,
  R_NAME      char(25) NOT NULL,
  R_COMMENT   varchar(152) NOT NULL,
  PRIMARY KEY (R_REGIONKEY)
);

CREATE TABLE IF NOT EXISTS "TPCH_$ds".SUPPLIER (
  S_SUPPKEY   int NOT NULL,
  S_NAME      char(25) NOT NULL,
  S_ADDRESS   varchar(40) NOT NULL,
  S_NATIONKEY int NOT NULL,
  S_PHONE     char(15) NOT NULL,
  S_ACCTBAL   decimal(10,2) NOT NULL,
  S_COMMENT   varchar(101) NOT NULL,
  PRIMARY KEY (S_SUPPKEY)
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
