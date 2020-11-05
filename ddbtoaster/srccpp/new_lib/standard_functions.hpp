#ifndef DBTOASTER_STANDARD_FUNCTIONS_H
#define DBTOASTER_STANDARD_FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <cmath>
#include <regex.h>
#include <functional>
#include "types.hpp"

using namespace std;

namespace dbtoaster {

namespace standard_functions {

// unsigned int Udate_year(date d);
// unsigned int Udate_month(date d);
// unsigned int Udate_day(date d);
// date Udate(const char *s);
// date Udate(const STRING_TYPE &s);

// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// T Ulistmin(T v1, T v2);
// long Ulistmin(int v1, long v2);
// DOUBLE_TYPE Ulistmin(int v1, DOUBLE_TYPE v2);
// DOUBLE_TYPE Ulistmin(long v1, DOUBLE_TYPE v2);

// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// T Ulistmax(T v1, T v2);
// long Ulistmax(int v1, long v2);
// DOUBLE_TYPE Ulistmax(int v1, DOUBLE_TYPE v2);
// DOUBLE_TYPE Ulistmax(long v1, DOUBLE_TYPE v2);

// // String functions
// STRING_TYPE Usubstring(const STRING_TYPE &s, size_t start, size_t len);
// int Upreg_match(const regex_t& preg, const STRING_TYPE& s);

// // Vector functions
// DOUBLE_TYPE Uvec_length(DOUBLE_TYPE x, DOUBLE_TYPE y, DOUBLE_TYPE z);
// DOUBLE_TYPE Uvec_dot(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
//                      DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2);
// DOUBLE_TYPE Uvector_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
//                           DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2);
// void Uvec_cross(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
//                 DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
//                 DOUBLE_TYPE& x, DOUBLE_TYPE& y, DOUBLE_TYPE& z);
// DOUBLE_TYPE Udihedral_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1,
//                             DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
//                             DOUBLE_TYPE x3, DOUBLE_TYPE y3, DOUBLE_TYPE z3,
//                             DOUBLE_TYPE x4, DOUBLE_TYPE y4, DOUBLE_TYPE z4);

// template <typename T>
// size_t Uhash(T x);

// // Math operations
// DOUBLE_TYPE Uradians(DOUBLE_TYPE degree);
// DOUBLE_TYPE Udegrees(DOUBLE_TYPE radian);
// DOUBLE_TYPE Ucos(DOUBLE_TYPE x);
// DOUBLE_TYPE Usin(DOUBLE_TYPE x);
// DOUBLE_TYPE Udiv(DOUBLE_TYPE x);
// DOUBLE_TYPE Usqrt(DOUBLE_TYPE x);
// DOUBLE_TYPE Upow(DOUBLE_TYPE base, DOUBLE_TYPE exponent);

// // Type conversion functions
// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// int cast_int(T t);
// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// long cast_long(T t);
// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// float cast_float(T t);
// template <typename T,
//           typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
// double cast_double(T t);
// date cast_date(date d);
// date cast_date(STRING_TYPE s);
// template <class T> 
// STRING_TYPE cast_string(const T& t);
// template <>
// STRING_TYPE cast_string(const date& d);


// Date extraction functions
inline unsigned int Udate_year(date d) {
  return d.getYear();
}

inline unsigned int Udate_month(date d) {
  return d.getMonth();
}

inline unsigned int Udate_day(date d) {
  return d.getDay();
}

// Date conversion functions
date Udate(const char *s) {
  unsigned int y = 0, m = 0, d = 0;
  if (sscanf(s, "%u-%u-%u", &y, &m, &d) < 3 || m > 12 || d > 31) {
    throw std::invalid_argument("invalid date string " + string(s) + " (expected format YYYY-MM-DD)");
  }
  return date(y, m, d);
}

inline date Udate(const STRING_TYPE &s) { 
  return Udate(s.c_str()); 
}

// Min and max functions
template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline T Ulistmin(T v1, T v2) {
  return (v1 < v2) ? v1 : v2;
}

inline long Ulistmin(int v1, long v2) {
  return (v1 < v2) ? v1 : v2;
}

inline DOUBLE_TYPE Ulistmin(int v1, DOUBLE_TYPE v2) {
  return (v1 < v2) ? v1 : v2;
}

inline DOUBLE_TYPE Ulistmin(long v1, DOUBLE_TYPE v2) {
  return (v1 < v2) ? v1 : v2;
}

template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline T Ulistmax(T v1, T v2) {
  return (v1 > v2) ? v1 : v2;
}

inline long Ulistmax(int v1, long v2) {
  return (v1 > v2) ? v1 : v2;
}

inline DOUBLE_TYPE Ulistmax(int v1, DOUBLE_TYPE v2) {
  return (v1 > v2) ? v1 : v2;
}

inline DOUBLE_TYPE Ulistmax(long v1, DOUBLE_TYPE v2) {
  return (v1 > v2) ? v1 : v2;
}

// String functions
inline STRING_TYPE Usubstring(const STRING_TYPE &s, size_t start, size_t len) {
  return s.substr(start, len);
}

inline int Upreg_match(const regex_t& preg, const STRING_TYPE& s) {
  auto ret = regexec(&preg, s.c_str(), 0, NULL, 0);
  return (ret == 0) ? 1 : 0;
}

// Vector functions
inline DOUBLE_TYPE Uvec_length(DOUBLE_TYPE x, DOUBLE_TYPE y, DOUBLE_TYPE z) {
  return sqrt(x * x + y * y + z * z);
}

inline DOUBLE_TYPE Uvec_dot(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                            DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2) {
  return x1 * x2 + y1 * y2 + z1 * z2;
}

inline DOUBLE_TYPE Uvector_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                                 DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2) {
  return acos(Uvec_dot(x1, y1, z1, x2, y2, z2) / (Uvec_length(x1, y1, z1) * Uvec_length(x2, y2, z2)));
}

inline void Uvec_cross(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                       DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
                       DOUBLE_TYPE& x, DOUBLE_TYPE& y, DOUBLE_TYPE& z) {
  x = (y1 * z2 - z1 * y2);
  y = (z1 * x2 - x1 * z2);
  z = (x1 * y2 - y1 * x2);
}

DOUBLE_TYPE Udihedral_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                            DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
                            DOUBLE_TYPE x3, DOUBLE_TYPE y3, DOUBLE_TYPE z3,
                            DOUBLE_TYPE x4, DOUBLE_TYPE y4, DOUBLE_TYPE z4) {
  DOUBLE_TYPE v1_x, v1_y, v1_z;
  DOUBLE_TYPE v2_x, v2_y, v2_z;
  DOUBLE_TYPE v3_x, v3_y, v3_z;
  DOUBLE_TYPE n1_x, n1_y, n1_z;
  DOUBLE_TYPE n2_x, n2_y, n2_z;
  
  v1_x = x2 - x1;
  v1_y = y2 - y1;
  v1_z = z2 - z1;

  v2_x = x3 - x2;
  v2_y = y3 - y2;
  v2_z = z3 - z2;

  v3_x = x4 - x3;
  v3_y = y4 - y3;
  v3_z = z4 - z3;

  Uvec_cross(v1_x, v1_y, v1_z, v2_x, v2_y, v2_z, n1_x, n1_y, n1_z);
  Uvec_cross(v2_x, v2_y, v2_z, v3_x, v3_y, v3_z, n2_x, n2_y, n2_z);
  
  return atan2(Uvec_length(v2_x, v2_y, v2_z) * Uvec_dot(v1_x, v1_y, v1_z, n2_x, n2_y, n2_z), 
               Uvec_dot(n1_x, n1_y, n1_z, n2_x, n2_y, n2_z));
}

template <typename T>
inline size_t Uhash(T x) {
  return std::hash<T>{}(x);
}

// Math operations
constexpr double kPi = 3.141592653589793238462643383279502884;

inline DOUBLE_TYPE Uradians(DOUBLE_TYPE degree) {
  return degree * kPi / 180;
}

inline DOUBLE_TYPE Udegrees(DOUBLE_TYPE radian) {
  return radian * 180 / kPi;
}

inline DOUBLE_TYPE Ucos(DOUBLE_TYPE x) {
  return cos(x);
}

inline DOUBLE_TYPE Usin(DOUBLE_TYPE x) {
  return sin(x);
}

inline DOUBLE_TYPE Udiv(DOUBLE_TYPE x) {
  return (x == 0 ? 0.0 : 1.0 / x);
}

inline DOUBLE_TYPE Usqrt(DOUBLE_TYPE x) {
  return sqrt(x);
}

inline DOUBLE_TYPE Upow(DOUBLE_TYPE base, DOUBLE_TYPE exponent) {
  return pow(base, exponent);
}

// Type conversion functions
template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline int cast_int(T t) {
  return static_cast<int>(t);
}

template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline long cast_long(T t) {
  return static_cast<long>(t);
}

template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline float cast_float(T t) {
  return static_cast<float>(t);
}

template <typename T,
          typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
inline double cast_double(T t) {
  return static_cast<double>(t);
}

inline date cast_date(date d) {
  return d;
}

inline date cast_date(STRING_TYPE s) {
  return Udate(s.c_str());
}

template <class T> 
inline STRING_TYPE cast_string(const T& t) {
  return std::to_string(t);
}

template <>
inline STRING_TYPE cast_string(const date& d) {
  return std::to_string(d.getYear() * 10000 + d.getMonth() * 100 + d.getDay());
}

}

}
#endif //DBTOASTER_STANDARD_FUNCTIONS_H
