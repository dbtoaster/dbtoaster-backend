#ifndef DBTOASTER_STANDARD_FUNCTIONS_H
#define DBTOASTER_STANDARD_FUNCTIONS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <regex.h>
#include <functional>
#include "types.hpp"
#include "date_format.hpp"

using namespace std;

namespace dbtoaster {

namespace standard_functions {

// Date extraction functions
inline constexpr unsigned int Udate_year(date d) {
  return d.getYear();
}

inline constexpr unsigned int Udate_month(date d) {
  return d.getMonth();
}

inline constexpr unsigned int Udate_day(date d) {
  return d.getDay();
}

// Date conversion functions
inline constexpr date Udate(const char *s) {
  // expected date format YYYY-MM-DD
  return dbtoaster::DateFormat::parse(s);
}

inline date Udate(const StringType &s) { 
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

inline DoubleType Ulistmin(int v1, DoubleType v2) {
  return (v1 < v2) ? v1 : v2;
}

inline DoubleType Ulistmin(long v1, DoubleType v2) {
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

inline DoubleType Ulistmax(int v1, DoubleType v2) {
  return (v1 > v2) ? v1 : v2;
}

inline DoubleType Ulistmax(long v1, DoubleType v2) {
  return (v1 > v2) ? v1 : v2;
}

// String functions
inline StringType Usubstring(const StringType &s, size_t start, size_t len) {
  return s.substr(start, len);
}

inline int Upreg_match(const regex_t& preg, const StringType& s) {
  auto ret = regexec(&preg, s.c_str(), 0, NULL, 0);
  return (ret == 0) ? 1 : 0;
}

int Uregexp_match(const char* regex, const StringType& s);

int Uregexp_match(const char* regex, const StringType& s) {
  regex_t preg;
  if (regcomp(&preg, regex, REG_EXTENDED | REG_NOSUB)) {
    std::cerr << "Error compiling regular expression: /" << regex << "/" << std::endl;
    exit(-1);
  }
  auto ret = regexec(&preg, s.c_str(), 0, NULL, 0);
  regfree(&preg);
  return (ret == 0 ? 1 : 0);
}

// Vector functions
inline DoubleType Uvec_length(DoubleType x, DoubleType y, DoubleType z) {
  return sqrt(x * x + y * y + z * z);
}

inline DoubleType Uvec_dot(DoubleType x1, DoubleType y1, DoubleType z1, 
                           DoubleType x2, DoubleType y2, DoubleType z2) {
  return x1 * x2 + y1 * y2 + z1 * z2;
}

inline DoubleType Uvector_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
                                DoubleType x2, DoubleType y2, DoubleType z2) {
  return acos(Uvec_dot(x1, y1, z1, x2, y2, z2) / (Uvec_length(x1, y1, z1) * Uvec_length(x2, y2, z2)));
}

inline void Uvec_cross(DoubleType x1, DoubleType y1, DoubleType z1, 
                       DoubleType x2, DoubleType y2, DoubleType z2,
                       DoubleType& x, DoubleType& y, DoubleType& z) {
  x = (y1 * z2 - z1 * y2);
  y = (z1 * x2 - x1 * z2);
  z = (x1 * y2 - y1 * x2);
}

DoubleType Udihedral_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
                           DoubleType x2, DoubleType y2, DoubleType z2,
                           DoubleType x3, DoubleType y3, DoubleType z3,
                           DoubleType x4, DoubleType y4, DoubleType z4);

DoubleType Udihedral_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
                           DoubleType x2, DoubleType y2, DoubleType z2,
                           DoubleType x3, DoubleType y3, DoubleType z3,
                           DoubleType x4, DoubleType y4, DoubleType z4) {
  DoubleType v1_x, v1_y, v1_z;
  DoubleType v2_x, v2_y, v2_z;
  DoubleType v3_x, v3_y, v3_z;
  DoubleType n1_x, n1_y, n1_z;
  DoubleType n2_x, n2_y, n2_z;
  
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
inline HashType Uhash(T x) {
  return std::hash<T>{}(x);
}

// Math operations
constexpr double kPi = 3.141592653589793238462643383279502884;

inline DoubleType Uradians(DoubleType degree) {
  return degree * kPi / 180;
}

inline DoubleType Udegrees(DoubleType radian) {
  return radian * 180 / kPi;
}

inline DoubleType Ucos(DoubleType x) {
  return cos(x);
}

inline DoubleType Usin(DoubleType x) {
  return sin(x);
}

inline DoubleType Udiv(DoubleType x) {
  return (x == 0 ? 0.0 : 1.0 / x);
}

inline DoubleType Usqrt(DoubleType x) {
  return sqrt(x);
}

inline DoubleType Upow(DoubleType base, DoubleType exponent) {
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

inline date cast_date(StringType s) {
  return Udate(s.c_str());
}

template <class T> 
inline StringType cast_string(const T& t) {
  return std::to_string(t);
}

template <>
inline StringType cast_string(const date& d) {
  return std::to_string(d.getYear() * 10000 + d.getMonth() * 100 + d.getDay());
}

}

}
#endif //DBTOASTER_STANDARD_FUNCTIONS_H
