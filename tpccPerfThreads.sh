#!/usr/bin/env bash
rm -f opt_list.txt
exec="0713/concThreads/t1"


rm -f runtime/stats/*
rm -f out_dump.txt
rm -f tpcc_res_cpp.csv

allopts=(
#base
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

#minmax + med + spl
"-opt refcounter -opt regex -opt entry -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

#entry + tmpvar
"-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx"

#no_opts
"-opt refcounter -opt index -opt idxinline -opt lookupfusion"
)
numWare=5
profTx="" #"-opt profileblocks"
cnt=1
n=800000
initsize="" #"-opt initsize"

for numWare in 5
do
    for opts in "${allopts[@]}"
    do
    echo "running opt combo $cnt"
    mkdir -p $exec/tpcc$cnt
        rm -f profile.csv
        sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx -lang cpp -ware $numWare"
        for numThread in {1..5}
        do
            echo "Running thread $numThread"
            #noinitsize only jemalloc
            rm -f tpcc.out
            g++ -std=c++11  -DNUMTHREADS=$numThread -DNUMWARE=$numWare -O3 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -pthread -o tpcc.out
            for i in {1..5}
            do
                ./tpcc.out $i
            done
            mv profile.csv $exec/tpcc$cnt/profileBlock$numThread.csv
        done
        mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccBlock.cpp
        cnt=$((cnt+1))
    done
done