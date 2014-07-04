#ifndef DBTOASTER_STANDARD_FUNCTIONS_H
#define DBTOASTER_STANDARD_FUNCTIONS_H

#include <cstdlib>
#include <string>
using namespace std;
#include "hpds/pstring.hpp"

#include "event.hpp"
#include <regex.h>

namespace dbtoaster {

  // Date extraction functions
  // ImperativeCompiler synthesizes calls to the following from calls to 
  // date_part
  long Uyear_part(date d);
  long Umonth_part(date d);
  long Uday_part(date d);
  
  // String functions
  string Usubstring(string &s, long start, long len);  
  int Uregexp_match(const char *regex, const string &s);
  int Upreg_match(const regex_t &preg, const string &s);
  int Uregexp_match(const char *regex, const PString &s);
  int Upreg_match(const regex_t &preg, const PString &s);
  
  // Vector functions
  float Uvec_dot(float x1, float y1, float z1, 
              float x2, float y2, float z2);
  float Uvec_length(float x1, float y1, float z1);
  float Uvector_angle(float x1, float y1, float z1, 
              float x2, float y2, float z2);
  float Udihedral_angle(float x1, float y1, float z1, 
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4);

  long long Uhash(long long v);
  
  // Math funtions
  float Uradians(float degree);
  float Udegrees(float radian);
  float Upow(float a, float b);
/*  float pow(float a, int b);
  float pow(int a, float b);
  float pow(int a, int b);
 */
  double Udiv(double x);
  double UmulDbl(double x, double y);
  long UmulLng(long x, long y);
  long Ulistmax(long v1,  long v2);
  double Ulistmax(double v1, double v2);
  double Ulistmax(long v1, double v2);
  double Ulistmax(double v1, long v2);
  
  // Type conversion functions
  inline long cast_int_from_float(double           d) { return (long)d; };
  inline long cast_int_from_string(const char     *c) { return atoi(c); };
  inline long cast_int_from_string(string         &s) { 
    return cast_int_from_string(s.c_str()); 
  };
  inline double cast_float_from_int(long           i) { return (double)i; };
  inline double cast_float_from_string(const char *c) { return atof(c); };
  inline double cast_float_from_string(string     &s) { 
    return cast_float_from_string(s.c_str()); 
  };
  
  template <class T> 
  string cast_string(const T &t);
  
  inline string cast_string_from_int(long      i) { return cast_string(i); }
  inline string cast_string_from_double(double d) { return cast_string(d); }
  string cast_string_from_date(date ymd);
  date Udate(const char *c);
  inline date Udate(string &s) { 
    return Udate(s.c_str()); 
  }
  
}

#endif //DBTOASTER_STANDARD_FUNCTIONS_H
