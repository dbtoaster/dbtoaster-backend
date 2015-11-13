#!/bin/bash

mkdir -p bin

for i in `seq 1 22`;
do
    echo "Compiling tpch$i..."
    g++ -Wall -Wno-unused-variable -std=c++11 -pedantic -O3  src/main.cpp -I src/lib -I src/tpch -include src/tpch/tpch$i.hpp -o bin/tpch$i
done    
