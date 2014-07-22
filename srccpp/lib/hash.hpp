#include "hpds/macro.hpp"
#include "hpds/KDouble.hpp"

namespace dbtoaster {
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
  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const KDouble& v)
  {
      seed ^= float2int(v.sum) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
}