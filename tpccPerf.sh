#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(
" "
#"-opt index"
#"-opt index -opt fixedrange"
#"-opt index -opt fixedrange -opt lookupfusion"
#"-opt lookupfusion -opt entry"
#"-opt index -opt entry"
#"-opt index -opt lookupfusion -opt entry"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx -opt sliceinline"
#"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar  -opt idxinline -opt deadidx -opt codemotion"
)
cnt=1

rm -f out_dump.txt
rm -f tpcc*.csv
#echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
#echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv

initsize="-opt initsize"

#for opt in "${allopts[@]}"
#do
#echo "$cnt $opt" >> opt_list.txt


rm -f runtime/stats/*
for n in 1000000 2000000 4000000 8000000 16000000
do
##CPP
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"

#nothing
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/  -ldbtoaster -o tpcc.out
for i in {1..1}
do
./tpcc.out $i
done

#noinitsize only jemalloc
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..1}
do
./tpcc.out $i
done

sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
#initsize and jemalloc
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1 -DNORESIZE=1 -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..1}
do
./tpcc.out $i
done

scalatime=$((14 * n/1000000))
#Scala
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang scala -info tpcc-$n" 2>&1 | tee -a out_color.txt
sbt "Runtime/runMain  ddbt.tpcc.tx.TpccInMem -t $scalatime"  2>&1 | tee -a out_color.txt
sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g" out_color.txt > out_dump.txt
rm out_color.txt
./tpcc_res.sh

done