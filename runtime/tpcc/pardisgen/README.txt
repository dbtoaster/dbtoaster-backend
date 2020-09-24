Compiling generated TpccGenSC.cpp

g++ -std=c++17 -O3 TpccGenSC.cpp -I ../../../ddbtoaster/srccpp/lib/mmap -I ../../../ddbtoaster/srccpp/lib  -I <libcuckoo_dir> -DPROJECT_ROOT=\"<project_root>\"
