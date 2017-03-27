#!/usr/bin/env bash
rm -f opt_list.txt
rm -rf runtime/stats/*
rm -rf ddbtoaster/r*.csv
rm -rf ddbtoaster/r*.txt

allopts=(
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt slicenoupd"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt regex -opt multires -opt slicenoupd -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt codemotion -opt m3cmpmult -opt regex"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt codemotion -opt m3cmpmult -opt regex"
"-opt entry -opt index -opt online -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt index -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt entry -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
"-opt index -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
	 )
cnt=1
queries=".*tpch.*"
numExec=3

for opt in "${allopts[@]}"
do
echo "$cnt $opt" >> opt_list.txt
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l cpp -d big_del $opt -q $queries"
#sbt "DDBToaster/runMain  ddbt.UnitTest -v -x -p 2 -w 0 -s 1 -t 60000 -l scala -d standard_del $opt -q .*tpch.*"
#sbt "DDBToaster/runMain  ddbt.UnitTest -v -x -p 2 -w 0 -s 1 -t 60000 -l cpp -d standard_del $opt -q .*tpch.*"
cnt=$((cnt+1))
done

opt="-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt coldmotion"
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv rcpp.csv -dump rcpp.txt  -l cpp -d big_del $opt -q $queries"
#sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv rvcpp.csv -dump rvcpp.txt  -l vcpp -d big_del $opt -q $queries"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0.csv -dump r0.txt  -l cpp -d big_del $opt -opt initsize -q $queries"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0i.csv -dump r0i.txt  -l cpp -d big_del $opt -opt initsize -q $queries"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 3 -s $numExec -t 60000  -csv r0iscala.csv -dump r0iscala.txt  -l scala -d big_del $opt -opt initsize -q $queries"