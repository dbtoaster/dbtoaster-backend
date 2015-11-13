#!/bin/bash

for i in `seq 1 22`;
do
    echo "Running tpch$i..."
    bin/tpch$i
done    
