#!/usr/bin/env bash
rm -f opt_list.txt
rm -rf runtime/stats/*
allopts=(
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd" # remove the warning for dead-index update and slide-no-update
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt codemotion -opt m3cmpmult -opt regex"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt codemotion -opt m3cmpmult -opt regex"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt med -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt minmax -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt spl -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
"-opt entry -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd" #check for dependencies
"-opt index -opt spl -opt minmax -opt med -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd"
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

opt="-opt entry -opt index -opt spl -opt minmax -opt med -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt initsize"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0.csv -dump r0.txt  -l cpp -d big_del $opt -q $queries"
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s $numExec -t 60000  -csv r0i.csv -dump r0i.txt  -l cpp -d big_del $opt -q $queries"