#!/usr/bin/env bash

rm -f out_dump.txt
rm -f tpcc_res_cpp.csv
rm -f runtime/stats/*

initsize="-opt initsize"
n=8000000
exec="0601/t1"
opt="-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx -opt sliceinline -opt codemotion -opt multires -opt coldmotion -opt slicenoupd"

for  numWare in 15 20 25 30 40 50 70 90 100
do
    #most optimal case dry run
    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  -ware $numWare $opt $initsize -lang cpp -info tpcc-$numWare-$n"
    rm -f tpcc.out
    g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

    for i in {1..1}
    do
        ./tpcc.out $i
    done

    #actual run
    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC -ware $numWare  $opt  -opt profileblocks $initsize -lang cpp -info tpcc-$numWare-$n"
    rm -f tpcc.out
    g++ -std=c++11 -O3 -DNUMWARE=$numWare -DNORESIZE=1 -DNDEBUG -DNUMPROG=$n -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/ -ljemalloc -ldbtoaster -o tpcc.out

    for i in {1..3}
    do
        ./tpcc.out $i
    done

    mv profile.csv $exec/profile$numWare.csv
    mv runtime/tpcc/pardisgen/TpccGenSC.cpp $exec/TpccW$numWare.cpp

#    scalatime=$((14 * n/1000000))
#    #Scala
#    sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt $initsize -lang scala -info tpcc-$numWare-$n" 2>&1 | tee -a out_color.txt
#    sbt "Runtime/runMain  ddbt.tpcc.tx.TpccInMem -t $scalatime"  2>&1 | tee -a out_color.txt
#    sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g" out_color.txt > out_dump.txt
#    rm out_color.txt
#    ./tpcc_res.sh
#
#    echo "" >> tpcc_res_cpp.csv
#    echo "" >> tpcc_res_scala.csv
done
