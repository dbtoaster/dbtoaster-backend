#!/bin/sh

cd ../..

rm -f target/htest

BOOST_LIB="/usr/local/Cellar/boost/1.55.0"

g++ test/cpp/htest.cpp -o target/htest -O3 -lpthread -ldbtoaster -Isrccpp/lib -Lsrccpp/lib -lboost_program_options-mt -lboost_serialization-mt -lboost_system-mt -lboost_filesystem-mt -lboost_chrono-mt -lboost_thread-mt -I$BOOST_LIB/include -L$BOOST_LIB/lib

target/htest