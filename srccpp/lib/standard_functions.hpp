#ifndef DBTOASTER_STANDARD_FUNCTIONS_H
#define DBTOASTER_STANDARD_FUNCTIONS_H

#include <cstdlib>
#include <string>
using namespace std;

#include "event.hpp"

namespace dbtoaster {

  // Date extraction functions
  // ImperativeCompiler synthesizes calls to the following from calls to 
  // date_part
  long year_part(date d);
  long month_part(date d);
  long day_part(date d);
  
  // String functions
  string substring(string &s, long start, long len);  
  int regexp_match(const char *regex, string &s);
  
  // Vector functions
  float vec_dot(float x1, float y1, float z1, 
              float x2, float y2, float z2);
  float vec_length(float x1, float y1, float z1);
  float vector_angle(float x1, float y1, float z1, 
              float x2, float y2, float z2);
  float dihedral_angle(float x1, float y1, float z1, 
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4);

  long long hash(long long v);
  
  // Math funtions
  float radians(float degree);
  float degrees(float radian);
  float pow(float a, float b);
/*  float pow(float a, int b);
  float pow(int a, float b);
  float pow(int a, int b);
 */
  double div(double x);
  double mulDbl(double x, double y);
  long mulLng(long x, long y);
  long listmax(long v1,  long v2);
  double listmax(double v1, double v2);
  
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
  date cast_date_from_string(const char *c);
  inline date cast_date_from_string(string &s) { 
    return cast_date_from_string(s.c_str()); 
  }
  
}

#endif //DBTOASTER_STANDARD_FUNCTIONS_H
