#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(" " 
	"-opt index" 
"-opt index -opt fixedrange" 
"-opt index -opt fixedrange -opt lookupfusion"
"-opt lookupfusion -opt entry"
"-opt index -opt entry" 
"-opt index -opt lookupfusion -opt entry" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx"
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx -opt sliceinline" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt tmpmap -opt idxinline -opt deadidx -opt sliceinline -opt codemotion" 
)
cnt=1
for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#if [ $cnt == 7 ] || [ $cnt == 9 ]
#then

sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt " 
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=1 -DNUMPROG=100000 -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/  -ldbtoaster -o tpcc.out
./tpcc.out
#sbt "Runtime/runMain  ddbt.tpcc.loadtest.TpccUnitTest"
#fi
cnt=$((cnt+1))
done
