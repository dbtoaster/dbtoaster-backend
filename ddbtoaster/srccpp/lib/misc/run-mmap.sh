#!/bin/sh

rm -f ./mmap
g++ -Wall -O3 -std=c++17 -I .. -I/usr/local/include -L/usr/local/lib mmap.cpp -o mmap && ./mmap