#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9 10 12 14 17 18 20 21 11 13 15 16 19 22;
do
    for bs in 1 10 100 1000 10000 100000
    do
        echo ""
        echo "#############################"

        echo "Compiling tpch$i..."
        g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpch -include src/tpch/tpch$i.hpp -o bin/tpch$i -DBATCH_MODE -DBATCH_SIZE=$bs

        echo "Running tpch$i with batch size $bs..."
        bin/tpch$i

        echo "#############################"
        echo ""
    done
done    
