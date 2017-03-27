#!/usr/bin/env bash

rm -f out_dump.txt
rm -f tpcc_res_cpp.csv
#echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
#echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv

initsize="-opt initsize"
for  numWare in 5 1 10
do
cnt=1

rm -f runtime/stats/*
~/TStore/bench/tpcc-cmd-log.sh 8000000 $numWare

n=8000000
#most optimal case dry run
opt="-opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd -ware $numWare"
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

for i in {1..3}
do
./tpcc.out $i
done

#actual run
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

for i in {1..3}
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


echo "" >> tpcc_res_cpp.csv
echo "" >> tpcc_res_scala.csv
done

cat tpcc_res_cpp.csv tpcc_res_scala.csv > tpccWare.csv