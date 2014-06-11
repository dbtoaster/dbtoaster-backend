#!/bin/sh

rm -f ./mmap
g++ -Wall -O2 mmap.cpp mmap.hpp -std=c++11 -o mmap -I/usr/local/include -L/usr/local/lib && ./mmap