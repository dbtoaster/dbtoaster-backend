#!/bin/sh

cd ../..

echo "Moved to project root folder."

rm -f target/time_hash_map

echo "Cleaned."

BOOST_LIB="/usr/local/Cellar/boost/1.55.0"

g++ test/cpp/time_hash_map.cc -o target/time_hash_map -O3 -lpthread -ldbtoaster -Isrccpp/lib -Lsrccpp/lib -lboost_program_options-mt -lboost_serialization-mt -lboost_system-mt -lboost_filesystem-mt -lboost_chrono-mt -lboost_thread-mt -I$BOOST_LIB/include -L$BOOST_LIB/lib

echo "Compiled"

target/time_hash_map

echo "Finished exec."