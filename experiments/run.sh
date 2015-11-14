#!/bin/bash

for i in `seq 1 22`;
do
    echo ""
    echo "#############################"

    echo "Compiling tpch$i..."
    g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpch -include src/tpch/tpch$i.hpp -o bin/tpch$i

    echo "Running tpch$i..."
    bin/tpch$i

    echo "#############################"
    echo ""
done    
