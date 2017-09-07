#!/usr/bin/env bash
rm -f opt_list.txt
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

# allopts=(
# #base
# "-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

# #deadidx
# "-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion"

# #tmpvar
# "-opt refcounter -opt regex -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx"

# #minmax + med + spl
# "-opt refcounter -opt regex -opt entry -opt index -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"

# #entry + tmpvar
# "-opt refcounter -opt regex -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt idxinline -opt lookupfusion -opt deadidx"

# #regex
# "-opt refcounter -opt entry -opt index -opt spl -opt minmax -opt med -opt fixedrange -opt online -opt tmpvar -opt idxinline -opt lookupfusion -opt deadidx"
# )
cnt=1
ware=5
for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#Scala
#sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -lang scala"
#sbt "Runtime/runMain  ddbt.tpcc.tx.TpccUnitTest"

#CPP
sbt "DBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt -lang pcpp -ware $ware"
rm -f tpcc.out
g++ -std=c++11 -O3 -DNUMWARE=$ware -DNUMTHREADS=3 -DNUMPROG=1000  -DVERIFY_TPCC=1 -DPROJECT_ROOT=\"/home/sachin/TStore/\" runtime/tpcc/pardisgen/TpccGenSC.cpp -I ddbtoaster/srccpp/lib/ -I ddbtoaster/srccpp/lib/mmap/  -L ddbtoaster/srccpp/lib/  -ldbtoaster -o tpcc.out -pthread
./tpcc.out


cnt=$((cnt+1))
done
