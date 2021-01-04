./copyjs.sh $1
echo "Query $1:"
cd ../dbtoaster.js
./compilejs.sh > /dev/null 2>&1
./fixjs.sh
echo "Compilation completed."
sbt run >> res.txt
echo "Running completed."
