#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(
#ref counter turn on ??
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion"
#"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt slicenoupd"
#"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt multires -opt coldmotion -opt slicenoupd"
#"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt codemotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt lookupfusion -opt codemotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med  -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt entry -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
"-opt refcounter -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
)
rm -f runtime/stats/*
cnt=1
numWare=1
profTx="-opt profileblocks"
rm -f out_dump.txt
rm -f tpcc_res_cpp.csv
#echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
#echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv

initsize="-opt initsize"

for opt in "${allopts[@]}"
do
echo "$cnt $opt" >> opt_list.txt


if [ $cnt -eq 11 ]
then
n=8000
elif [ $cnt -eq 4 ]
then
n=800000
elif [ $cnt -eq 6 ]
then
n=4000000
elif [ $cnt -eq 12 ]
then
n=800000
else
n=8000000
fi

##CPP
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx -lang cpp -ware $numWare"
#noinitsize only jemalloc
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=$numWare  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..3}
do
./tpcc.out $i
done

cnt=$((cnt+1))
done
n=8000000
#most optimal case dry run
opt="$profTx -opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd -ware $numWare"
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

mv profile.csv profileBlocks.csv