#include "PMurHash.hpp"

std::hash<long> long_hasher;
std::hash<double> double_hasher;
std::hash<std::string> string_hasher;

FORCE_INLINE void hash_combine(std::size_t& seed, const long& v)
{
    seed ^= long_hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
FORCE_INLINE void hash_combine(std::size_t& seed, const double& v)
{
    seed ^= double_hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
FORCE_INLINE void hash_combine(std::size_t& seed, const std::string& v)
{
    seed ^= string_hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}
