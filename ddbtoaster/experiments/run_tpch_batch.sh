#!/bin/bash

for i in `seq 1 22`;
do
    for bs in 1 10 100 1000 10000 100000
    do
        echo ""
        echo "#############################"

        echo "Compiling TPC-H query${i}..."
        g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpch -include src/tpch/query${i}.hpp -o bin/tpch_query${i} -DBATCH_MODE -DBATCH_SIZE=${bs} -DNUMBER_OF_RUNS=3 -include src/tpch/tpch.hpp -include src/tpch/tpch_template.hpp

        echo "Running TPC-H query${i} with batch size ${bs}..."
        bin/tpch_query${i}

        echo "#############################"
        echo ""
    done
done    
