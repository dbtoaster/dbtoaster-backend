#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(" "
"-opt index"
"-opt index -opt fixedrange"
"-opt index -opt fixedrange -opt lookupfusion"
"-opt lookupfusion -opt entry"
"-opt index -opt entry"
"-opt index -opt lookupfusion -opt entry"
"-opt index -opt fixedrange -opt lookupfusion -opt entry"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx -opt sliceinline"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx -opt sliceinline -opt codemotion"
)
cnt=1

rm -f out_dump.txt
rm -f tpcc_res_scala.csv
rm -f tpcc_res_cpp.csv
echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv

for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#Scala
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -lang scala" 2>&1 | tee -a out_color.txt
sbt "Runtime/runMain  ddbt.tpcc.tx.TpccInMem"  2>&1 | tee -a out_color.txt
sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g" out_color.txt > out_dump.txt
rm out_color.txt
./tpcc_res.sh


#CPP
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -lang cpp "
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1 -DNUMPROG=100000 -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/  -ldbtoaster -o tpcc.out
for i in {1..5}
do
./tpcc.out $i
done
done