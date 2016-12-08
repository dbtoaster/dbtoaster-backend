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
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx -opt codemotion" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult" 
"-opt index -opt fixedrange -opt lookupfusion -opt entry -opt online -opt tmpvar -opt idxinline -opt deadidx -opt codemotion -opt m3cmpmult -opt refcounter" 
)
cnt=1
for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#if [ $cnt == 7 ] || [ $cnt == 9 ]
#then

sbt "DDBToaster/runMain sc.tpcc.TpccXactGenerator_SC  $opt " 
sbt "Runtime/runMain  ddbt.tpcc.tx.TpccInMem"
#fi
cnt=$((cnt+1))
done
