#!/bin/bash

# DONE SO FAR
#for query in 1 2 3 4 6 10 11 12 13 14 17 19 22;

for query in 7 8;
do
    for nodes in 50;
    do
        cd spark/conf && rm -f spark.config && ln -s spark.config.${nodes} spark.config && cd ../../

        for batch in 50000000 100000000 200000000 400000000;
        do
            echo ""
            echo "#############################"

            echo "Running TPC-H query${query} with batch size ${batch} on ${nodes} nodes"

            sbt "unit -xvm -xsc  -p 2 -s 1 -w 0 -l spark -q tpch.query${query} -d 500gb -O3 --batch -F HEURISTICS-DECOMPOSE-OVER-TABLES  -xbs ${batch} -x"

            echo "#############################"
            echo ""
        done
    done

    #for nodes in 100 200 400 800;
    for nodes in 100 200 400;
    do
        cd spark/conf && rm -f spark.config && ln -s spark.config.${nodes} spark.config && cd ../../

        for batch in 50000000 100000000 200000000 400000000;
        do
            echo ""
            echo "#############################"

            echo "Running TPC-H query${query} with batch size ${batch} on ${nodes} nodes"

            sbt "unit -xvm -xsc  -p 2 -s 2 -w 0 -l spark -q tpch.query${query} -d 500gb -O3 --batch -F HEURISTICS-DECOMPOSE-OVER-TABLES  -xbs ${batch} -x"

            echo "#############################"
            echo ""
        done
    done

done


for query in 16 20;
do
    for nodes in 50;
    do
        cd spark/conf && rm -f spark.config && ln -s spark.config.${nodes} spark.config && cd ../../

        for batch in 50000000 100000000 200000000 400000000;
        do
            echo ""
            echo "#############################"

            echo "Running TPC-H query${query} with batch size ${batch} on ${nodes} nodes"

            sbt "unit -xvm -xsc  -p 2 -s 1 -w 0 -l spark -q tpch.query${query} -d 500gb -O3 --batch -F HEURISTICS-WEAK-GRAPH-DECOMPOSITION  -xbs ${batch} -x"

            echo "#############################"
            echo ""
        done
    done

    #for nodes in 100 200 400 800;
    for nodes in 100 200 400;
    do
        cd spark/conf && rm -f spark.config && ln -s spark.config.${nodes} spark.config && cd ../../

        for batch in 50000000 100000000 200000000 400000000;
        do
            echo ""
            echo "#############################"

            echo "Running TPC-H query${query} with batch size ${batch} on ${nodes} nodes"

            sbt "unit -xvm -xsc  -p 2 -s 2 -w 0 -l spark -q tpch.query${query} -d 500gb -O3 --batch -F HEURISTICS-WEAK-GRAPH-DECOMPOSITION -xbs ${batch} -x"

            echo "#############################"
            echo ""
        done
    done

done
