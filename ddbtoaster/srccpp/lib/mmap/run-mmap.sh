#!/bin/sh

rm -f ./mmap
g++ -Wall -O2 mmap.cpp -std=c++11 -o mmap -I. -I.. -I/usr/local/include -L/usr/local/lib && ./mmap