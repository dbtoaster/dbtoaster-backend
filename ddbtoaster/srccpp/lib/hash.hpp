#ifndef DBTOASTER_HASH_HPP
#define DBTOASTER_HASH_HPP

#include "macro.hpp"
#include "hpds/KDouble.hpp"

extern std::hash<double> double_hasher;
extern std::hash<std::string> string_hasher;

namespace dbtoaster {

  template <class T>
  FORCE_INLINE void hash_combine(std::size_t& seed, const T& v)
  {
      seed ^= hash_value(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

  union Cast
  {
    double d;
    long l;
  };
  
  extern volatile Cast c;

  inline int float2int( double d )
  {
    c.d = d + 6755399441055744.0;
    return c.l;
  }

  union CastLLD
  {
    long double d;
    long l;
  };
  
  extern volatile Cast cLLD;

  inline int longDouble2int( long double d )
  {
    cLLD.d = d + 6755399441055744.0;
    return cLLD.l;
  }

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const int& v)
  {
      seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const long& v)
  {
      seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  
  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const std::string& v)
  {
      seed ^= string_hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

 template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const float& v)
  {
      seed ^= float2int(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  
#if DOUBLE_TYPE_SYM == DOUBLE_TYPE_KAHAN_DOUBLE

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const KDouble& v)
  {
      seed ^= float2int(v.sum) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

#elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_BOOST

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const cpp_dec_float_1000& v)
  {
      seed ^= static_cast<int>(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

#elif DOUBLE_TYPE_SYM == DOUBLE_TYPE_STD_LONG_DOUBLE

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const long double& v)
  {
      seed ^= longDouble2int(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

#else

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const double& v)
  {
      seed ^= float2int(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

#endif

  template <>
  FORCE_INLINE void hash_combine(std::size_t& seed, const char& v)
  {
      seed ^= v + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }

}

#endif /* DBTOASTER_HASH_HPP */
