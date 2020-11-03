#ifndef DBTOASTER_HASH_HPP
#define DBTOASTER_HASH_HPP

#include "macro.hpp"
#include "types.hpp"

namespace dbtoaster {

namespace hashing {

template <class T>
FORCE_INLINE void hash_combine(std::size_t& seed, const T& v) {
  seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const int& v) {
  seed ^= static_cast<size_t>(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const long& v) {
  seed ^= static_cast<size_t>(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const std::string& v) {
  seed ^= std::hash<std::string>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

union CastDouble {
  double d;
  std::size_t i;
};

FORCE_INLINE std::size_t castDouble(double v) {
  return CastDouble{ v + 6755399441055744.0 }.i;
}

union CastLongDouble {
  long double d;
  std::size_t i;
};

FORCE_INLINE std::size_t castLongDouble(long double v) {
  return CastLongDouble{ v + 6755399441055744.0 }.i;
}  

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const float& v) {
  seed ^= castDouble(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// template <>
// FORCE_INLINE void hash_combine(std::size_t& seed, const KDouble& v) {
//   seed ^= castDouble(v.sum) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
// }

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const double& v) {
  seed ^= castDouble(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const long double& v) {
  seed ^= castLongDouble(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const char& v) {
  seed ^= static_cast<size_t>(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <>
FORCE_INLINE void hash_combine(std::size_t& seed, const DateType& v) {
  seed ^= v.getNumeric() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}

}
#endif /* DBTOASTER_HASH_HPP */
