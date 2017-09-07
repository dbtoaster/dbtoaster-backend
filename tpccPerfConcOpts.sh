#!/usr/bin/env bash
rm -f opt_list.txt
exec="0712/concopts/t1"
allopts=(
#base
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

#deadidx
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion"

#tmpvar
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx"

#minmax + med + spl
"-opt refcounter -opt regex -opt entry -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

#entry + tmpvar
"-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx"

#regex
"-opt refcounter -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"
)

rm -f runtime/stats/*
rm -f out_dump.txt
rm -f tpcc_res_cpp.csv

numThread=5
cnt=1
profTx="" #-opt profileblocks"
initsize="" #-opt initsize"
for numWare in 5
do
    for opt in "${allopts[@]}"
    do
        echo "Running optimization combo $cnt"
        echo "$cnt $opt" >> opt_list.txt

        n=800000

        mkdir -p $exec/tpcc$cnt/
        rm -f profile.csv

        ##CPP
        sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx -lang cpp -ware $numWare"

        #noinitsize only jemalloc
        rm -f tpcc.out
        g++ -std=c++11  -DNUMTHREADS=$numThread -DNUMWARE=$numWare -O3 -DNUMPROG=$n -DNDEBUG -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -pthread -o tpcc.out
        for i in {1..1}
        do
            ./tpcc.out $i
        done

        mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/

        cnt=$((cnt+1))
    done
    mv tpcc_res_cpp.csv $exec/
done