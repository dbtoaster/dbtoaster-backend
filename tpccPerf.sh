#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(
" "
"-opt lookupfusion -opt entry"
"-opt index"
"-opt index -opt fixedrange"
"-opt index -opt fixedrange -opt lookupfusion"
"-opt index -opt entry"
"-opt index -opt lookupfusion -opt entry"
"-opt index -opt fixedrange -opt lookupfusion -opt entry"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx -opt sliceinline"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar  -opt idxinline -opt deadidx -opt sliceinline -opt codemotion"
)
cnt=1

rm -f out_dump.txt
rm -f tpcc*.csv
#echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
#echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv

initsize="-opt initsize"
rm -f runtime/stats/*

for opt in "${allopts[@]}"
do
echo "$cnt $opt" >> opt_list.txt


if [ $cnt -eq 1 ]
then
n=100
elif [ $cnt -eq 2 ]
then
n=1000
elif [ $cnt -lt 7 ]
then
n=100000
else
n=1000000
fi

##CPP
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -lang cpp"
#noinitsize only jemalloc
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..5}
do
./tpcc.out $i
done

cnt=$((cnt+1))
done
n=1000000
#most optimal case dry run
opt="-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar  -opt idxinline -opt deadidx -opt sliceinline -opt codemotion"
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..5}
do
./tpcc.out $i
done

#actual run
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1 -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..5}
do
./tpcc.out $i
done