#!/bin/bash

for i in 3 7 19 27 34 42 43 46 52 55 68 73 79;
do
    for bs in 1 10 100 1000 10000 100000
    do
        echo ""
        echo "#############################"

        echo "Compiling TPC-DS query${i}..."
        g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpcds -include src/tpcds/query${i}.hpp -o bin/tpcds_query${i} -DBATCH_MODE -DBATCH_SIZE=$bs -DNUMBER_OF_RUNS=3 -DTPCDS

        echo "Running TPC-DS query${i} with batch size ${bs}..."
        bin/tpcds_query${i}

        echo "#############################"
        echo ""
    done
done    
