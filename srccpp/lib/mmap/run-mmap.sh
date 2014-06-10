#!/bin/sh

rm -f ./mmap
g++ -Wall -O2 mmap.cpp mmap.hpp -std=c++11 -o mmap && ./mmap