#include "hpds/macro.hpp"
#include <cmath>

namespace dbtoaster {
  size_t precision = 7; // significative numbers (7 to pass r_sumdivgrp, 10 otherwise)
  double diff_p = pow(0.1,precision);

  template <class T>
  FORCE_INLINE void hash_combine(std::size_t& seed, const T& v)
  {
      seed ^= hash_value(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

  std::hash<double> double_hasher;
  std::hash<std::string> string_hasher;

  union Cast
  {
    double d;
    long l;
  };
  volatile Cast c;
  inline int float2int( double d )
  {
    c.d = d + 6755399441055744.0;
    return c.l;
  }

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const long& v)
  {
      seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const double& v)
  {
      seed ^= float2int(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const std::string& v)
  {
      seed ^= string_hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
}