#!/usr/bin/env bash
rm -f opt_list.txt
rm -rf runtime/stats/*
rm -rf ddbtoaster/r*.csv
rm -rf ddbtoaster/r*.txt
exec="0105/t5"
allopts=(
#base
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd -opt coldmotion"

#slicenoupd
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires  -opt coldmotion"

#regex
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt multires -opt slicenoupd  -opt coldmotion"

#m3cmpmult
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt regex -opt multires -opt slicenoupd -opt coldmotion"

#sliceinline
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"

#deadidx + slicenoupd
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires  -opt coldmotion"

#deadidx + slicenoupd + sliceinline + multires + coldmotion
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt codemotion -opt m3cmpmult -opt regex"

#deadidx + slicenoupd + idxinline + sliceinline + multires + coldmotion
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt codemotion -opt m3cmpmult -opt regex"

#deadix + slicenoupd + lookupfusion + sliceinline + multires + coldmotion
"-opt entry  -opt index -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt codemotion -opt m3cmpmult -opt regex"

#tmpmap
"-opt entry  -opt index -opt online -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"

#tmpvar + sliceinline
"-opt entry  -opt index -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"

#online
"-opt entry  -opt index -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"

#entry + tmpvar + sliceinline
"-opt index -opt online -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt regex -opt multires -opt slicenoupd  -opt coldmotion"
	 )
cnt=1
queries=".*((tpch)|(simple)).*"
numExec=1
dataset="standard_del"

for opt in "${allopts[@]}"
do
    echo "Running opt combo count $cnt"
    mkdir -p $exec/e$cnt/hpp
    mkdir -p $exec/e$cnt/out
   

    echo "$cnt $opt" >> opt_list.txt

    sbt "DBToaster/runMain  ddbt.UnitTest -x  -v -p 2 -w 0 -s $numExec -t 60000  -csv rCPP$cnt.csv -dump rCPP$cnt.txt  -l cpp -d $dataset $opt -q $queries"
    sbt "DBToaster/runMain  ddbt.UnitTest -x  -v -p 2 -w 0 -s $numExec -t 60000  -csv rScala$cnt.csv -dump rScala$cnt.txt  -l scala -d $dataset $opt -q $queries"
    mv ddbtoaster/target/tmp/*.hpp $exec/e$cnt/hpp/

    cnt=$((cnt+1))
done
