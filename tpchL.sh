#!/usr/bin/env bash
rm -f opt_list.txt
rm -rf runtime/stats/*
rm -rf ddbtoaster/r*.csv
rm -rf ddbtoaster/r*.txt
rm -rf ddbtoaster/target/tmp

exec="0508/t1"
queries=".*tpch.*y([0-9]*)"
numExec=1
dataset="big_del"

opt="-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt coldmotion"

lang="cppinit"
mkdir -p $exec/$lang/stdout
mkdir -p $exec/$lang/gen

#initsize
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s 1 -t 60000  -csv r0.csv -dump r0.txt  -l cpp -d $dataset $opt -opt initsize -q $queries"
mv ddbtoaster/target/tmp/*.hpp $exec/$lang/gen/
mv ddbtoaster/target/tmp/*.txt $exec/$lang/stdout/

for lang in lscala lcpp llms scala cpp
do
    mkdir -p $exec/$lang/stdout
    mkdir -p $exec/$lang/gen

    sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 2 -s $numExec -t 60000  -csv $lang.csv -dump $lang.txt  -l $lang  -d $dataset  -q  $queries $opt"
    mv ddbtoaster/target/tmp/*.hpp $exec/$lang/gen/
    mv ddbtoaster/target/tmp/*.scala $exec/$lang/gen/
    mv ddbtoaster/target/tmp/*.txt $exec/$lang/stdout/
done

mkdir $exec/execCSV
mkdir $exec/execTXT
mv ddbtoaster/r*.csv $exec/execCSV/
mv ddbtoaster/r*.txt $exec/execTXT/