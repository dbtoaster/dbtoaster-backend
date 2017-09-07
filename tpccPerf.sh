#!/usr/bin/env bash
rm -f opt_list.txt
exec="0105/t2"

allopts=(

#base
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#slicenoupd
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion"

#sliceinline
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#deadidx + slicenoupd
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt sliceinline -opt codemotion -opt multires -opt coldmotion"

#deadidx + slicenoupd + sliceinline +  multires + coldmotion
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt codemotion"

#lookupfusion + deadidx + sliceinline + slicenoupd + multires + coldmotion
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt codemotion"

#idxinline + deadidx + slicenoupd + sliceinline +  multires + coldmotion
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt lookupfusion -opt codemotion"

#tmpvar + sliceinline
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#fixedrange
"-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med  -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#minmax + med + spl
"-opt refcounter -opt regex -opt entry -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#entry + tmpvar + sliceinline
"-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

#regex
"-opt refcounter -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"
)

rm -f runtime/stats/*
rm -f out_dump.txt
rm -f tpcc_res_cpp.csv

cnt=1
numWare=5
profTx="-opt profileblocks"


initsize="-opt initsize"
for numWare in 5
do
    for opt in "${allopts[@]}"
    do
        echo "Running optimization combo $cnt"
        echo "$cnt $opt" >> opt_list.txt

        n=8000000

        mkdir -p $exec/tpcc$cnt/
        rm -f profile.csv

        ##CPP
        sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $profTx -lang cpp -ware $numWare"
        #noinitsize only jemalloc
        rm -f tpcc.out
        g++ -std=c++11   -DNUMWARE=$numWare -O3 -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
        for i in {1..3}
        do
            ./tpcc.out $i
        done

        mv profile.csv $exec/tpcc$cnt/profileBlock.csv
        mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccBlock.cpp


        sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -opt profilestore -lang cpp -ware $numWare"
        #noinitsize only jemalloc
        rm -f tpcc.out
        g++ -std=c++11 -DNUMWARE=$numWare -O3 -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out
        for i in {1..3}
        do
            ./tpcc.out $i
        done

        mv profile.csv $exec/tpcc$cnt/profileStore.csv
        mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccStore.cpp

        cnt=$((cnt+1))
    done

    opt="-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

    cnt=0
    mkdir -p $exec/tpcc$cnt/
    n=8000000
    #most optimal case dry run

    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  -ware $numWare $opt $initsize -lang cpp -info tpcc-$numWare-$n"
    rm -f tpcc.out
    g++ -std=c++11 -O3 -g -DNUMWARE=$numWare -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

    for i in {1..1}
    do
    ./tpcc.out $i
    done

    #actual run
    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  -ware $numWare $opt -opt profileblocks $initsize -lang cpp -info tpcc-$numWare-$n"
    rm -f tpcc.out
    g++ -std=c++11 -O3 -g -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

    for i in {1..3}
    do
    ./tpcc.out $i
    done

    mv profile.csv $exec/tpcc$cnt/profileBlock.csv
    mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccBlock.cpp


    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  -ware $numWare $opt -opt profilestore $initsize -lang cpp -info tpcc-$numWare-$n"
    rm -f tpcc.out
    g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

    for i in {1..3}
    do
    ./tpcc.out $i
    done

    mv profile.csv $exec/tpcc$cnt/profileStore.csv
    mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/tpcc$cnt/TpccStore.cpp

done