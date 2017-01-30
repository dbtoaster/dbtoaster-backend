#!/bin/bash

for i in `seq 1 22`;
do
    echo ""
    echo "#############################"

    echo "Compiling TPC-H query${i}..."
    g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpch -include src/tpch/query${i}.hpp -o bin/tpch_query${i} -DNUMBER_OF_RUNS=3 -DTPCH

    echo "Running TPC-H query${i}..."
    bin/tpch_query${i}

    echo "#############################"
    echo ""
done    
