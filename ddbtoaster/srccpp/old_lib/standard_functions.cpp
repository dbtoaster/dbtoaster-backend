#include "standard_functions.hpp"

#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>

namespace dbtoaster {

namespace standard_functions {

// Date extraction functions
// ImperativeCompiler synthesizes calls to the following from calls to 
// date_part
int Udate_year(dbtoaster::DateType d) { 
  return d.getYear();
}
int Udate_month(dbtoaster::DateType d) { 
  return d.getMonth();
}
int Udate_day(dbtoaster::DateType d) { 
  return d.getDay();
}

dbtoaster::DateType Udate(const char *c) { //cast_date_from_string
  unsigned int y = 0, m = 0, d = 0;
  if (sscanf(c, "%u-%u-%u", &y, &m, &d) < 3 || m > 12 || d > 31) {
    throw std::invalid_argument("invalid date string " + string(c) + " (expected format YYYY-MM-DD)");
  }
  return dbtoaster::DateType(y, m, d);
}

StringType cast_string_from_date(dbtoaster::DateType d) { 
  std::stringstream ss;
  ss << d.getYear() << d.getMonth() << d.getDay();
  return StringType(ss.str().c_str());
}

// StringType cast_string_from_date(date ymd)   { 
//   std::stringstream ss;
//   ss << ((ymd / 10000) % 10000)
//      << ((ymd / 100  ) % 100)
//      << ((ymd        ) % 100);
//   return StringType(ss.str().c_str());
// }

// date Udate(const char *c) { //cast_date_from_string
//   unsigned int y, m, d;
//   if(sscanf(c, "%u-%u-%u", &y, &m, &d) < 3){
//     cerr << "Invalid date string: "<< c << endl;
//   }
//   if((m > 12) || (d > 31)){ 
//     cerr << "Invalid date string: "<< c << endl;
//   }
//   return (y%10000) * 10000 + (m%100) * 100 + (d%100);
// }


// String functions
StringType Usubstring(const StringType &s, size_t start, size_t len){
    return s.substr(start, len);
}

DoubleType Uvec_length(DoubleType x, DoubleType y, DoubleType z){
  return sqrt(x*x+y*y+z*z);
}

DoubleType Uvec_dot(DoubleType x1, DoubleType y1, DoubleType z1, 
              DoubleType x2, DoubleType y2, DoubleType z2){
  return x1*x2+y1*y2+z1*z2;
}

void Uvec_cross(DoubleType x1, DoubleType y1, DoubleType z1, 
               DoubleType x2, DoubleType y2, DoubleType z2,
               DoubleType& x, DoubleType& y, DoubleType& z){
  x = (y1*z2-z1*y2);
  y = (z1*x2-x1*z2);
  z = (x1*y2-y1*x2);
}

DoubleType Uvector_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
              DoubleType x2, DoubleType y2, DoubleType z2){
  return acos(Uvec_dot(x1,y1,z1,x2,y2,z2) /
               (Uvec_length(x1,y1,z1)*Uvec_length(x2,y2,z2)));
}

DoubleType Udihedral_angle(DoubleType x1, DoubleType y1, DoubleType z1, 
                    DoubleType x2, DoubleType y2, DoubleType z2,
                    DoubleType x3, DoubleType y3, DoubleType z3,
                    DoubleType x4, DoubleType y4, DoubleType z4){
  DoubleType v1_x, v1_y, v1_z;
  DoubleType v2_x, v2_y, v2_z;
  DoubleType v3_x, v3_y, v3_z;
  DoubleType n1_x, n1_y, n1_z;
  DoubleType n2_x, n2_y, n2_z;
  
  v1_x = x2-x1;
  v1_y = y2-y1;
  v1_z = z2-z1;

  v2_x = x3-x2;
  v2_y = y3-y2;
  v2_z = z3-z2;

  v3_x = x4-x3;
  v3_y = y4-y3;
  v3_z = z4-z3;

  Uvec_cross(v1_x, v1_y, v1_z,
            v2_x, v2_y, v2_z,
            n1_x, n1_y, n1_z);
  Uvec_cross(v2_x, v2_y, v2_z,
            v3_x, v3_y, v3_z,
            n2_x, n2_y, n2_z);
  
  return atan2(Uvec_length(v2_x, v2_y, v2_z)*Uvec_dot(v1_x,v1_y,v1_z,n2_x,n2_y,n2_z), 
                Uvec_dot(n1_x, n1_y, n1_z, n2_x, n2_y, n2_z));
}

HashType Uhash(long long v) {
   
   v = v * 3935559000370003845 + 2691343689449507681;
   v ^= v >> 21; v^= v << 37; v ^= v >> 4;
   v *= 4768777413237032717LL;
   v ^= v >> 20; v^= v << 41; v ^= v >> 5;
   
   return v;
}

const DoubleType PI = 3.141592653589793238462643383279502884;

DoubleType Uradians(DoubleType degree) {
  return degree * PI / 180;
}

DoubleType Udegrees(DoubleType radian) {
  return radian * 180 / PI;
}

DoubleType Upow(DoubleType a, DoubleType b) {
  return pow(a, b);
}

DoubleType Ucos(DoubleType a) { 
  return cos(a); 
}

DoubleType Usin(DoubleType a) { 
  return sin(a);
}

/*DoubleType pow(DoubleType a, int b) {
  return ::pow(a, (DoubleType)b);
}
DoubleType pow(int a, DoubleType b) {
  return ::pow((DoubleType)a, b);
}
DoubleType pow(int a, int b) {
  return ::pow((DoubleType)a, (DoubleType)b);
}*/

int Uregexp_match(const char *regex, const StringType &s){
  //TODO: Caching regexes, or possibly inlining regex construction
  regex_t preg;
  int ret;

  if(regcomp(&preg, regex, REG_EXTENDED | REG_NOSUB)){
    cerr << "Error compiling regular expression: /" << 
        regex << "/" << endl;
    exit(-1);
  }
  ret = regexec(&preg, s.c_str(), 0, NULL, 0);
  regfree(&preg);

  switch(ret){
    case 0: return 1;
    case REG_NOMATCH: return 0;
    default:
    cerr << "Error evaluating regular expression: /" << 
        regex << "/" << endl;
    exit(-1);
  }

  regfree(&preg);
}

int Upreg_match(const regex_t &preg, const StringType &s){
  int ret = regexec(&preg, s.c_str(), 0, NULL, 0);

  switch(ret){
    case 0: return 1;
    case REG_NOMATCH: return 0;
    default:
    cerr << "Error evaluating regular expression." << endl;
    exit(-1);
  }
}

long UmulLng(long x, long y) { return x * y; }
DoubleType Udiv(DoubleType x) { if(x==0.0) return 0.0; else return (1.0 / x); }
DoubleType UmulDbl(DoubleType x, DoubleType y) { return x * y; }

long Ulistmax(int v1, int v2) { return ((v1 > v2) ? v1 : v2 ); }
long Ulistmax(int v1, long v2) { return ((v1 > v2) ? v1 : v2 ); }
DoubleType Ulistmax(int v1, DoubleType v2) { return ((v1 > v2) ? v1 : v2); }

// long Ulistmax(long v1, int v2) { return ((v1 > v2) ? v1 : v2 ); }
// long Ulistmax(long v1, long v2) { return ((v1 > v2) ? v1 : v2 ); }
// DoubleType Ulistmax(DoubleType v1, DoubleType v2) { return ((v1 > v2) ? v1 : v2); }
// DoubleType Ulistmax(long v1, DoubleType v2) { return ((v2 < v1) ? v1 : v2); }
// DoubleType Ulistmax(DoubleType v1, long v2) { return ((v1 > v2) ? v1 : v2); }

// Type conversion functions
template <class T> 
StringType cast_string(const T &t) {
    std::stringstream ss;
    ss << t;
    return StringType(ss.str().c_str());
}

}

}