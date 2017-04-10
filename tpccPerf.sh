#!/usr/bin/env bash
rm -f opt_list.txt
exec="1004/t4"
allopts=(

#base
"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#slicenoupd
"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion"

#multires + coldmotion
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt slicenoupd"

#codemotion
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt multires -opt coldmotion -opt slicenoupd"

#sliceinline
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#deadidx + slicenoupd
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt sliceinline -opt codemotion -opt multires -opt coldmotion"

##deadidx + slicenoupd + sliceinline +  multires + coldmotion
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt codemotion"
#
##lookupfusion + deadidx + sliceinline + slicenoupd + multires + coldmotion
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt codemotion"
#
##idxinline + deadidx + slicenoupd + sliceinline +  multires + coldmotion
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt lookupfusion -opt codemotion"
#
##tmpvar + sliceinline
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##online
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##fixedrange
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med  -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##med
##"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##minmax
##"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##minmax + med + spl
#"-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##index + fixedrange + minmax + med + sliceinline + spl
##"-opt refcounter -opt regex -opt entry -opt parpromo -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
## pp
##"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
###tmpvar + sliceinline + pp
##"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##entry + tmpvar + sliceinline + pp
#"-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#
##regex
#"-opt refcounter -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
#15


#"-opt index"
#"-opt index -opt online"
#"-opt index -opt online -opt fixedrange"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar -opt lookupfusion"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar -opt lookupfusion -opt idxinline"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt slicenoupd"
#"-opt index -opt online -opt fixedrange -opt spl -opt minmax -opt med -opt regex -opt entry -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt slicenoupd -opt sliceinline"

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

#change sizes
#if [ $cnt -eq 11 ]
#then
#n=8000
#elif [ $cnt -eq 4 ]
#then
#n=800000
#elif [ $cnt -eq 6 ]
#then
#n=4000000
#elif [ $cnt -eq 12 ]
#then
#n=800000
#else
n=800000
#fi

mkdir -p $exec/tpcc$cnt/

##CPP
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx -lang cpp -ware $numWare"
#noinitsize only jemalloc
rm -f tpcc.out
g++ -std=c++11  -DNUMWARE=$numWare  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..1}
do
./tpcc.out $i
done

mv profile.csv $exec/tpcc$cnt/profileBlock.csv
mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccBlock.cpp


sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -opt profilestore -lang cpp -ware $numWare"
#noinitsize only jemalloc
rm -f tpcc.out
g++ -std=c++11 -DNUMWARE=$numWare  -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..1}
do
./tpcc.out $i
done

mv profile.csv $exec/tpcc$cnt/profileStore.csv
mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccStore.cpp

cnt=$((cnt+1))
done



#cnt=0
#mkdir -p $exec/tpcc$cnt/
#
#n=800000
##most optimal case dry run
#opt="-opt refcounter -opt regex -opt entry -opt parpromo -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd -ware $numWare"
#sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
#rm -f tpcc.out
#g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
#
#for i in {1..1}
#do
#./tpcc.out $i
#done
#
##actual run
#sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -opt profileblocks $initsize -lang cpp -info tpcc-$n"
#rm -f tpcc.out
#g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
#
#for i in {1..1}
#do
#./tpcc.out $i
#done
#
#mv profile.csv $exec/tpcc$cnt/profileBlock.csv
#mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccBlock.cpp


#sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -opt profilestore $initsize -lang cpp -info tpcc-$n"
#rm -f tpcc.out
#g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
#
#for i in {1..1}
#do
#./tpcc.out $i
#done
#
#mv profile.csv $exec/tpcc$cnt/profileStore.csv
#mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccStore.cpp
