#!/usr/bin/env bash
rm -f opt_list.txt

cnt=1
numWare=1
rm profile.csv
rm -f out_dump.txt
#echo "Entry,TmpVar,CmpMult,FixedRange,Online,Inline,DeadIdx,TmpMap,RegexHoister,Fusion full,CodeMotion,RefCnt,Index,SliceInline,Fusion" > tpcc_res_cpp.csv
#echo "E,V,T,G,O,N,D,M,X,F,C,R,I,S,F" >> tpcc_res_cpp.csv
#cp ~/TStore/commands_orig.txt ~/TStore/commands.txt
initsize="-opt initsize"
profTx="-opt profilestore"

#rm -f runtime/stats/*


n=8000000
#most optimal case dry run
opt="-opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd -ware $numWare"
#sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang cpp -info tpcc-$n"
#rm -f tpcc.out
#g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
#for i in {1..1}
#do
#./tpcc.out $i
#done

#actual run
sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx $initsize -lang cpp -info tpcc-$n"
cp ./runtime/tpcc/pardisgen/TpccGenSC.cpp .
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
for i in {1..3}
do
./tpcc.out $i
done

mv profile.csv profileStoreOps.csv
