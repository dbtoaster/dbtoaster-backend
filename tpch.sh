#!/usr/bin/env bash
rm -f opt_list.txt
rm -rf runtime/stats/*
rm -rf ddbtoaster/r*.csv
rm -rf ddbtoaster/r*.txt
exec="0704/t1"
allopts=(
"-opt index -opt regex"
"-opt index -opt regex -opt entry"
"-opt index -opt regex -opt entry -opt tmpvar"
"-opt index -opt regex -opt entry -opt tmpvar -opt lookupfusion"
	 )
cnt=1
queries=".*tpch.*y([0-9]*)"
numExec=1

for opt in "${allopts[@]}"
do
mkdir -p $exec/e$cnt/hpp
mkdir -p $exec/e$cnt/hppProf
mkdir -p $exec/e$cnt/out
mkdir -p $exec/e$cnt/profile

echo "$cnt $opt" >> opt_list.txt
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s 1 -t 60000  -l cpp -d big_del $opt -opt profilestore -q $queries"
mv ddbtoaster/target/tmp/*.hpp $exec/e$cnt/hppProf/
mv ddbtoaster/target/tmp/*.txt $exec/e$cnt/out/
mv ddbtoaster/profile*.csv $exec/e$cnt/profile/

sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l cpp -d big_del $opt -q $queries"
mv ddbtoaster/target/tmp/*.hpp $exec/e$cnt/hpp/

cnt=$((cnt+1))
done

#cnt=0
#mkdir -p $exec/e$cnt/hpp
#mkdir -p $exec/e$cnt/hppProf
#mkdir -p $exec/e$cnt/out
#mkdir -p $exec/e$cnt/profile
#
#opt="-opt entry -opt parpromo -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt coldmotion"
##sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv rcpp.csv -dump rcpp.txt  -l cpp -d big_del $opt -q $queries"
##sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv rvcpp.csv -dump rvcpp.txt  -l vcpp -d big_del $opt -q $queries"
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0.csv -dump r0.txt  -l cpp -d big_del $opt -opt initsize -q $queries"
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -l cpp -d big_del $opt -opt initsize -opt profilestore -q $queries"
#mv ddbtoaster/target/tmp/*.hpp $exec/e0/hppProf/
#mv ddbtoaster/profile*.csv $exec/e0/profile/
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0i.csv -dump r0i.txt  -l cpp -d big_del $opt -opt initsize -q $queries"
#mv ddbtoaster/target/tmp/*.hpp $exec/e0/hpp/
##sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 3 -s $numExec -t 60000  -csv r0iscala.csv -dump r0iscala.txt  -l scala -d big_del $opt -opt initsize -q $queries"
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 3 -s $numExec -t 60000  -csv r0iscala.csv -dump r0iscala.txt  -l scala -d big_del $opt -opt initsize -q $queries"