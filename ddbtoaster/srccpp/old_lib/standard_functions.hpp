#ifndef DBTOASTER_STANDARD_FUNCTIONS_H
#define DBTOASTER_STANDARD_FUNCTIONS_H

#include <cstdlib>
#include <string>
#include <cmath>
#include <regex.h>
#include "types.hpp"

using namespace std;

namespace dbtoaster {

namespace standard_functions {

  // Date extraction functions
  // ImperativeCompiler synthesizes calls to the following from calls to 
  // date_part
  int Udate_year(dbtoaster::DateType d);
  int Udate_month(dbtoaster::DateType d);
  int Udate_day(dbtoaster::DateType d);
  
  StringType cast_string_from_date(dbtoaster::DateType ymd);
  dbtoaster::DateType Udate(const char *c);
  inline dbtoaster::DateType Udate(const StringType &s) { 
    return Udate(s.c_str()); 
  }

  // String functions
  StringType Usubstring(const StringType &s, size_t start, size_t len);
  int Uregexp_match(const char *regex, const StringType &s);
  int Upreg_match(const regex_t &preg, const StringType &s);
  
  // Vector functions
  DoubleType Uvec_dot(DoubleType x1, DoubleType y1, DoubleType z1, 
              DoubleType x2, DoubleType y2, DoubleType z2);
  DoubleType Uvec_length(DoubleType x1, DoubleType y1, DoubleType z1);
  DoubleType Uvector_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
              DoubleType x2, DoubleType y2, DoubleType z2);
  DoubleType Udihedral_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
                    DoubleType x2, DoubleType y2, DoubleType z2,
                    DoubleType x3, DoubleType y3, DoubleType z3,
                    DoubleType x4, DoubleType y4, DoubleType z4);

  HashType Uhash(long long v);
  
  // Math funtions
  DoubleType Uradians(DoubleType degree);
  DoubleType Udegrees(DoubleType radian);
  DoubleType Upow(DoubleType a, DoubleType b);
  DoubleType Ucos(DoubleType a);
  DoubleType Usin(DoubleType a);

/*  DoubleType pow(DoubleType a, int b);
  DoubleType pow(int a, DoubleType b);
  DoubleType pow(int a, int b);
 */
  long UmulLng(long x, long y);

  DoubleType Udiv(DoubleType x);
  DoubleType UmulDbl(DoubleType x, DoubleType y);

  long Ulistmax(int v1, int v2);
  long Ulistmax(int v1, long v2);
  DoubleType Ulistmax(int v1, DoubleType v2);

  // long Ulistmax(long v1, int v2);
  // long Ulistmax(long v1, long v2);
  // DoubleType Ulistmax(DoubleType v1, DoubleType v2);
  // DoubleType Ulistmax(long v1, DoubleType v2);
  // DoubleType Ulistmax(DoubleType v1, long v2);
  
  // Type conversion functions
  inline long cast_int_from_float(double           d) { return (long)d; };
  inline long cast_int_from_string(const char     *c) { return atoi(c); };
  inline long cast_int_from_string(StringType         &s) { 
    return cast_int_from_string(s.c_str()); 
  };
  inline double cast_float_from_int(long           i) { return (double)i; };
  inline double cast_float_from_string(const char *c) { return atof(c); };
  inline double cast_float_from_string(StringType     &s) { 
    return cast_float_from_string(s.c_str()); 
  };
  
  template <class T> 
  StringType cast_string(const T &t);
  
  inline StringType cast_string_from_int(long      i) { return cast_string(i); }
  inline StringType cast_string_from_double(double d) { return cast_string(d); }  
}

}
#endif //DBTOASTER_STANDARD_FUNCTIONS_H
