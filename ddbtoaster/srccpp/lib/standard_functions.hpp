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
  int Udate_year(date d);
  int Udate_month(date d);
  int Udate_day(date d);
  
  STRING_TYPE cast_string_from_date(date ymd);
  date Udate(const char *c);
  inline date Udate(const STRING_TYPE &s) { 
    return Udate(s.c_str()); 
  }

  // String functions
  STRING_TYPE Usubstring(const STRING_TYPE &s, size_t start, size_t len);
  int Uregexp_match(const char *regex, const STRING_TYPE &s);
  int Upreg_match(const regex_t &preg, const STRING_TYPE &s);
  
  // Vector functions
  DOUBLE_TYPE Uvec_dot(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
              DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2);
  DOUBLE_TYPE Uvec_length(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1);
  DOUBLE_TYPE Uvector_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
              DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2);
  DOUBLE_TYPE Udihedral_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                    DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
                    DOUBLE_TYPE x3, DOUBLE_TYPE y3, DOUBLE_TYPE z3,
                    DOUBLE_TYPE x4, DOUBLE_TYPE y4, DOUBLE_TYPE z4);

  long long Uhash(long long v);
  
  // Math funtions
  DOUBLE_TYPE Uradians(DOUBLE_TYPE degree);
  DOUBLE_TYPE Udegrees(DOUBLE_TYPE radian);
  DOUBLE_TYPE Upow(DOUBLE_TYPE a, DOUBLE_TYPE b);
  DOUBLE_TYPE Ucos(DOUBLE_TYPE a);
  DOUBLE_TYPE Usin(DOUBLE_TYPE a);

/*  DOUBLE_TYPE pow(DOUBLE_TYPE a, int b);
  DOUBLE_TYPE pow(int a, DOUBLE_TYPE b);
  DOUBLE_TYPE pow(int a, int b);
 */
  long UmulLng(long x, long y);

  DOUBLE_TYPE Udiv(DOUBLE_TYPE x);
  DOUBLE_TYPE UmulDbl(DOUBLE_TYPE x, DOUBLE_TYPE y);

  long Ulistmax(int v1, int v2);
  long Ulistmax(int v1, long v2);
  DOUBLE_TYPE Ulistmax(int v1, DOUBLE_TYPE v2);

  // long Ulistmax(long v1, int v2);
  // long Ulistmax(long v1, long v2);
  // DOUBLE_TYPE Ulistmax(DOUBLE_TYPE v1, DOUBLE_TYPE v2);
  // DOUBLE_TYPE Ulistmax(long v1, DOUBLE_TYPE v2);
  // DOUBLE_TYPE Ulistmax(DOUBLE_TYPE v1, long v2);
  
  // Type conversion functions
  inline long cast_int_from_float(double           d) { return (long)d; };
  inline long cast_int_from_string(const char     *c) { return atoi(c); };
  inline long cast_int_from_string(STRING_TYPE         &s) { 
    return cast_int_from_string(s.c_str()); 
  };
  inline double cast_float_from_int(long           i) { return (double)i; };
  inline double cast_float_from_string(const char *c) { return atof(c); };
  inline double cast_float_from_string(STRING_TYPE     &s) { 
    return cast_float_from_string(s.c_str()); 
  };
  
  template <class T> 
  STRING_TYPE cast_string(const T &t);
  
  inline STRING_TYPE cast_string_from_int(long      i) { return cast_string(i); }
  inline STRING_TYPE cast_string_from_double(double d) { return cast_string(d); }  
}

}
#endif //DBTOASTER_STANDARD_FUNCTIONS_H
