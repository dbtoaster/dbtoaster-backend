#!/usr/bin/env bash
rm -f opt_list.txt
allopts=(
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult -opt regex"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion -opt m3cmpmult"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt codemotion"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt idxinline"
	"-opt entry -opt index -opt online -opt tmpvar -opt tmpmap"
	"-opt entry -opt index -opt online -opt tmpvar"
	"-opt entry -opt index -opt online"
	"-opt entry -opt index"
	"-opt entry -opt lookupfusion"
	"-opt index"
	" "
	 )
cnt=1
#allopts=(
#    "-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult -opt codemotion"
#    "-opt entry -opt index -opt online -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult -opt codemotion"
#    "-opt entry -opt index -opt online -opt tmpvar -opt tmpmap  -opt idxinline -opt m3cmpmult -opt codemotion"
#    "-opt entry -opt index -opt online -opt idxinline -opt m3cmpmult -opt codemotion"
#    "-opt index -opt online -opt idxinline -opt m3cmpmult -opt codemotion"
#    "-opt entry -opt index -opt online -opt tmpvar -opt tmpmap -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult"
#    "-opt entry -opt index -opt online -opt lookupfusion -opt idxinline -opt deadidx -opt sliceinline -opt m3cmpmult"
#    "-opt entry -opt index -opt online -opt tmpvar -opt tmpmap  -opt idxinline -opt m3cmpmult"
#    "-opt entry -opt index -opt online -opt idxinline -opt m3cmpmult"
#    "-opt index -opt online -opt idxinline -opt m3cmpmult"
#	)

sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s 3 -t 60000  -csv r0.csv -dump r0.txt  -l vcpp  -d big_del $opt -q  .*tpch.*"

for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#if [ $cnt == 7 ] || [ $cnt == 9 ]
#then
sbt "DDBToaster/runMain  ddbt.UnitTest -x -p 2 -w 0 -s 3 -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l cpp -d big_del $opt -q  .*tpch.*"
#sbt "DDBToaster/runMain  ddbt.UnitTest -v -x -p 2 -w 0 -s 1 -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l scala -d standard_del $opt -q .*tpch.*" 
#fi
cnt=$((cnt+1))
done
