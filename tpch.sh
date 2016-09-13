rm -f opt_list.txt
allopts=(" " "-opt entry" "-opt index" "-opt entry -opt index"  "-opt entry -opt index -opt online" "-opt entry -opt index -opt online -opt tmpvar" "-opt entry -opt index -opt online -opt tmpvar -opt idxinline"  "-opt entry -opt index -opt online -opt tmpvar -opt lookupfusion" "-opt entry -opt index -opt online -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx" "-opt entry -opt index -opt online -opt tmpvar -opt lookupfusion -opt idxinline -opt deadidx -opt codemotion" )
cnt=1
for opt in "${allopts[@]}" 
do
echo "$cnt $opt" >> opt_list.txt
#if [ $cnt == 7 ] || [ $cnt == 9 ]
#then

sbt "DDBToaster/runMain  ddbt.UnitTest -x -xsc -xvm -p 2 -w 2 -s 3 -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l scala  -d big_del $opt -q  .*tpch.*y(1|2|6|11|12|17|18|21)" 
#sbt "DDBToaster/runMain  ddbt.UnitTest -v -x -xsc -xvm -p 2 -w 0 -s 1 -t 60000  -csv r$cnt.csv -dump r$cnt.txt  -l scala  -d tiny_del $opt -q  .*tpch.*y(1|2|6|11|12|17|18|21)" 
#fi
cnt=$((cnt+1))
done
