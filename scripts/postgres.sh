#!/bin/sh
#
# Helper to compute results on PostgreSQL database system.
#
# Usage: postgres.sh help
#
# Examples:
#
#    ./postgres.sh -d tiny finance/chrissedtrades
#
#    ./postgres.sh -f -d big tpch/queries/query8
#

PSQL="/usr/local/bin/psql -h/usr/local/pgsql/socket -q"

PG_BASE=ddbt
PG_USER=root

cd `dirname $0`; cd ..
DBT_REPO=`sed 's/#.*//g' conf/ddbt.properties | grep ddbt.base_repo | sed 's/.*= *//g'`
DBT_DATA="$DBT_REPO/dbtoaster/experiments/data"
DBT_QUERIES="$DBT_REPO/dbtoaster/compiler/alpha5/test/queries"
if [ "$DBT_REPO" = "" ]; then echo "No repository configured in conf/ddbt.properties"; exit 0; fi

pg_exec() { #$1=schema, $2=dataset (optional), sql is piped inside
	if [ "$2" = "" ]; then s="$1"; p="${DBT_DATA}/$1"; else s="$1_$2"; p="${DBT_DATA}/$1/$2"; fi;
	printf "$s... "; s="`echo $s | tr '[:lower:]' '[:upper:]'`"
	printf "DROP SCHEMA IF EXISTS \"$s\" CASCADE;\nCREATE SCHEMA \"$s\";\n" | $PSQL -U${PG_USER} ${PG_BASE} 2>/dev/null
	sed "s/@S/\"$s\"/g" | sed "s!@P!$p!g" | $PSQL -U${PG_USER} ${PG_BASE}
	echo 'done.'
}

case "$1" in
# ------------------------------------------------------------------------------
""|-h|help|-help|--help)
	exec cat<<EOF
`basename $0` <action>
    create     create postgresql database
    remove     remove postgresql database
    help       display available commands

`basename $0` [options] <query>
    <query>    a file in test/queries without .sql extension
options:
    -f         use test/script/postgres for queries
    -d <set>   change dataset (tiny, standard, ...)
EOF
;;
# ------------------------------------------------------------------------------
remove) echo "DROP DATABASE IF EXISTS ${PG_BASE};" | exec $PSQL -U${PG_USER} postgres;;
# ------------------------------------------------------------------------------
create) $PSQL -U${PG_USER} postgres<<EOF
DROP DATABASE IF EXISTS ${PG_BASE};
CREATE DATABASE ${PG_BASE} OWNER ${PG_USER} ENCODING 'unicode';
GRANT ALL PRIVILEGES ON DATABASE ${PG_BASE} to ${PG_USER};
EOF
# -------- tpch
for ds in tiny tiny_del standard standard_del big big_del; do
	if [ "`echo $ds | grep '_del'`" != "" ]; then suf="_active"; else suf=""; fi
	pg_exec tpch $ds<<EOF
CREATE TABLE @S.CUSTOMER (CUSTKEY int NOT NULL, NAME varchar(25) NOT NULL, ADDRESS varchar(40) NOT NULL,
    NATIONKEY int NOT NULL, PHONE char(15) NOT NULL, ACCTBAL decimal(10,2) NOT NULL, MKTSEGMENT char(10) NOT NULL,
    COMMENT varchar(117) NOT NULL, PRIMARY KEY (CUSTKEY));

CREATE TABLE @S.LINEITEM (ORDERKEY int NOT NULL, PARTKEY int NOT NULL, SUPPKEY int NOT NULL, LINENUMBER int NOT NULL,
    QUANTITY decimal(20,10) NOT NULL, EXTENDEDPRICE decimal(10,2) NOT NULL, DISCOUNT decimal(10,10) NOT NULL,
    TAX decimal(10,10) NOT NULL, RETURNFLAG char(1) NOT NULL, LINESTATUS char(1) NOT NULL, SHIPDATE date NOT NULL,
    COMMITDATE date NOT NULL, RECEIPTDATE date NOT NULL, SHIPINSTRUCT char(25) NOT NULL, SHIPMODE char(10) NOT NULL,
    COMMENT varchar(44) NOT NULL, PRIMARY KEY (ORDERKEY, LINENUMBER));

CREATE INDEX ON @S.LINEITEM (PARTKEY);

CREATE TABLE @S.NATION (NATIONKEY int NOT NULL, NAME char(25) NOT NULL, REGIONKEY int NOT NULL, COMMENT varchar(152) NOT NULL, PRIMARY KEY (NATIONKEY));
CREATE TABLE @S.ORDERS ( ORDERKEY int NOT NULL, CUSTKEY int NOT NULL, ORDERSTATUS char(1) NOT NULL, TOTALPRICE decimal(10,2) NOT NULL, ORDERDATE date NOT NULL,
    ORDERPRIORITY char(15) NOT NULL, CLERK char(15) NOT NULL, SHIPPRIORITY int NOT NULL, COMMENT varchar(79) NOT NULL, PRIMARY KEY (ORDERKEY));
CREATE TABLE @S.PART (PARTKEY int NOT NULL, NAME varchar(55) NOT NULL, MFGR char(25) NOT NULL, BRAND char(10) NOT NULL, TYPE varchar(25) NOT NULL,
    SIZE int NOT NULL, CONTAINER char(10) NOT NULL, RETAILPRICE decimal(10,2) NOT NULL, COMMENT varchar(23) NOT NULL, PRIMARY KEY (PARTKEY));
CREATE TABLE @S.PARTSUPP (PARTKEY int NOT NULL, SUPPKEY int NOT NULL, AVAILQTY int NOT NULL, SUPPLYCOST decimal(10,2) NOT NULL,
 COMMENT varchar(199) NOT NULL,
 PRIMARY KEY (PARTKEY,SUPPKEY)
-- For the standard and tiny datasets the reference integrity is not preserved.
);
CREATE TABLE @S.REGION (REGIONKEY int NOT NULL, NAME char(25) NOT NULL, COMMENT varchar(152) NOT NULL, PRIMARY KEY (REGIONKEY));
CREATE TABLE @S.SUPPLIER (SUPPKEY int NOT NULL, NAME char(25) NOT NULL, ADDRESS varchar(40) NOT NULL, NATIONKEY int NOT NULL, PHONE char(15) NOT NULL,
    ACCTBAL decimal(10,2) NOT NULL, COMMENT varchar(101) NOT NULL, PRIMARY KEY (SUPPKEY));

COPY @S.REGION   FROM '@P/region$suf.csv'   WITH DELIMITER AS '|';
COPY @S.NATION   FROM '@P/nation$suf.csv'   WITH DELIMITER AS '|';
COPY @S.CUSTOMER FROM '@P/customer$suf.csv' WITH DELIMITER AS '|';
COPY @S.SUPPLIER FROM '@P/supplier$suf.csv' WITH DELIMITER AS '|';
COPY @S.PART     FROM '@P/part$suf.csv'     WITH DELIMITER AS '|';
COPY @S.PARTSUPP FROM '@P/partsupp$suf.csv' WITH DELIMITER AS '|';
COPY @S.ORDERS   FROM '@P/orders$suf.csv'   WITH DELIMITER AS '|';
COPY @S.LINEITEM FROM '@P/lineitem$suf.csv' WITH DELIMITER AS '|';
EOF
done
# -------- finance
for ds in tiny standard big huge; do
	pg_exec finance $ds<<EOF
CREATE TABLE @S.ASKS (T float NOT NULL, ID int NOT NULL, BROKER_ID int NOT NULL, VOLUME float NOT NULL, PRICE float NOT NULL);
CREATE TABLE @S.BIDS (T float NOT NULL, ID int NOT NULL, BROKER_ID int NOT NULL, VOLUME float NOT NULL, PRICE float NOT NULL);
COPY @S.ASKS FROM '@P/asks_export.csv' WITH DELIMITER AS ',';
COPY @S.BIDS FROM '@P/bids_export.csv' WITH DELIMITER AS ',';
EOF
done
# -------- mddb
for ds in tiny standard; do
	pg_exec mddb $ds<<EOF
CREATE TABLE @S.AtomPositions (trj_id int, t int, atom_id int, x float, y float, z float);
CREATE TABLE @S.AtomMeta (protein_id int, atom_id int, atom_type varchar(100), atom_name varchar(100),
		residue_id int, residue_name varchar(100), segment_name varchar(100));
CREATE TABLE @S.Bonds (protein_id int, atom_id1 int, atom_id2 int, bond_const float, bond_length float);
CREATE TABLE @S.Angles (protein_id int, atom_id1 int, atom_id2 int, atom_id3 int, angle_const float, angle float);
CREATE TABLE @S.Dihedrals (protein_id int, atom_id1 int, atom_id2 int, atom_id3 int, atom_id4 int, force_const float, n float, delta float);
CREATE TABLE @S.ImproperDihedrals (protein_id int, atom_id1 int, atom_id2 int, atom_id3 int, atom_id4 int, force_const float, delta float);
CREATE TABLE @S.NonBonded (protein_id int, atom_id1 int, atom_id2 int, atom_ty1 varchar(100), atom_ty2 varchar(100),
    rmin float, eps float, acoef float, bcoef float, charge1 float, charge2 float);
CREATE TABLE @S.ConformationPoints (trj_id int, t int, point_id int);
CREATE TABLE @S.Dimensions (atom_id1 int, atom_id2 int, atom_id3 int, atom_id4 int, dim_id int);
CREATE TABLE @S.Buckets (dim_id int, bucket_id int, bucket_start float, bucket_end float);

COPY @S.AtomPositions      FROM '@P/atompositions.csv' WITH DELIMITER AS ',';
COPY @S.AtomMeta           FROM '@P/atommeta.csv' WITH DELIMITER AS ',';
COPY @S.Bonds              FROM '@P/bonds.csv' WITH DELIMITER AS ',';
COPY @S.Angles             FROM '@P/angles.csv' WITH DELIMITER AS ',';
COPY @S.Dihedrals          FROM '@P/dihedrals.csv' WITH DELIMITER AS ',';
COPY @S.ImproperDihedrals  FROM '@P/improperdihedrals.csv' WITH DELIMITER AS ',';
COPY @S.NonBonded          FROM '@P/nonbonded.csv' WITH DELIMITER AS ',';
COPY @S.ConformationPoints FROM '@P/conformationpoints.csv' WITH DELIMITER AS ',';
COPY @S.Dimensions         FROM '@P/dimensions.csv' WITH DELIMITER AS ',';
COPY @S.Buckets            FROM '@P/buckets.csv' WITH DELIMITER AS ',';
EOF
done
# -------- simple
for ds in tiny standard big; do
	pg_exec simple $ds <<EOF
CREATE TABLE @S.R(A int, B int);
CREATE TABLE @S.S(B int, C int);
CREATE TABLE @S.T(C int, D int);

COPY @S.R FROM '@P/r.dat' WITH DELIMITER AS ',';
COPY @S.S FROM '@P/s.dat' WITH DELIMITER AS ',';
COPY @S.T FROM '@P/t.dat' WITH DELIMITER AS ',';
EOF
done
# -------- employee
	pg_exec employee<<EOF
CREATE TABLE @S.EMPLOYEE(employee_id INT, last_name VARCHAR(30), first_name VARCHAR(20), middle_name CHAR(1),
    job_id INT, manager_id INT, hire_date DATE, salary FLOAT, commission FLOAT, department_id INT);
CREATE TABLE @S.DEPARTMENT(department_id INT, name VARCHAR(20), location_id INT);
CREATE TABLE @S.LOCATION(location_id INT, regional_group VARCHAR(20));
CREATE TABLE @S.SALARY_GRADE(grade_id INT, lower_bound FLOAT, upper_bound FLOAT);
CREATE TABLE @S.JOB(job_id INT, job_function VARCHAR(20));

COPY @S.EMPLOYEE     FROM '@P/employee.dat' WITH DELIMITER AS ',';
COPY @S.DEPARTMENT   FROM '@P/department.dat' WITH DELIMITER AS ',';
COPY @S.LOCATION     FROM '@P/location.dat' WITH DELIMITER AS ',';
COPY @S.SALARY_GRADE FROM '@P/salary_grade.dat' WITH DELIMITER AS ',';
COPY @S.JOB          FROM '@P/job.dat' WITH DELIMITER AS ',';
EOF
;;
# ------------------------------------------------------------------------------
*)
	ds=STANDARD;
	fix=""; if [ "$1" = "-f" ]; then shift; fix=1; DBT_QUERIES="$DBT_REPO/dbtoaster/compiler/alpha5/test/scripts/postgres"; fi
	if [ "$1" = "-d" ]; then shift; ds="$1"; shift; fi
	tp="`echo $1 | sed 's/\/.*//g'`"
	query="`tr '\n' ' ' < ${DBT_QUERIES}/$1.sql`"
	query=`echo "$query" | sed 's/.*; *SELECT/SELECT/g' | sed 's/  */ /g'`
	if [ "$fix" != "" ]; then query=`echo "$query" | sed 's/\.[a-z]_/./g' | sed 's/\ [a-z]_/ /g'`; fi
	$PSQL -U${PG_USER} -AtF "," ${PG_BASE}<<EOF
SET search_path='`echo ${tp}_${ds} | tr '[:lower:]' '[:upper:]'`';
$query
EOF
;;
# ------------------------------------------------------------------------------
esac	
