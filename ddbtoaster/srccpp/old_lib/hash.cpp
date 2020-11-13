#include "hash.hpp"

using namespace dbtoaster;

namespace dbtoaster {
    volatile Cast c;
    volatile Cast cLLD;
}

std::hash<double> double_hasher;
std::hash<std::string> string_hasher;