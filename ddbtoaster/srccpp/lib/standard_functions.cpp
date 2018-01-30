#include "standard_functions.hpp"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <math.h>

namespace dbtoaster {

// Date extraction functions
// ImperativeCompiler synthesizes calls to the following from calls to 
// date_part
int Udate_year(date d) { 
	return (d / 10000) % 10000;
}
int Udate_month(date d) { 
	return (d / 100) % 100;
}
int Udate_day(date d) { 
	return d % 100;
}

// String functions
STRING_TYPE Usubstring(const STRING_TYPE &s, long start, long len){
	return s.substr(start, len);
}

DOUBLE_TYPE Uvec_length(DOUBLE_TYPE x, DOUBLE_TYPE y, DOUBLE_TYPE z){
  return sqrt(x*x+y*y+z*z);
}

DOUBLE_TYPE Uvec_dot(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
              DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2){
  return x1*x2+y1*y2+z1*z2;
}

void Uvec_cross(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
               DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
               DOUBLE_TYPE& x, DOUBLE_TYPE& y, DOUBLE_TYPE& z){
  x = (y1*z2-z1*y2);
  y = (z1*x2-x1*z2);
  z = (x1*y2-y1*x2);
}

DOUBLE_TYPE Uvector_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
              DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2){
  return acos(Uvec_dot(x1,y1,z1,x2,y2,z2) /
               (Uvec_length(x1,y1,z1)*Uvec_length(x2,y2,z2)));
}

DOUBLE_TYPE Udihedral_angle(DOUBLE_TYPE x1, DOUBLE_TYPE y1, DOUBLE_TYPE z1, 
                    DOUBLE_TYPE x2, DOUBLE_TYPE y2, DOUBLE_TYPE z2,
                    DOUBLE_TYPE x3, DOUBLE_TYPE y3, DOUBLE_TYPE z3,
                    DOUBLE_TYPE x4, DOUBLE_TYPE y4, DOUBLE_TYPE z4){
  DOUBLE_TYPE v1_x, v1_y, v1_z;
  DOUBLE_TYPE v2_x, v2_y, v2_z;
  DOUBLE_TYPE v3_x, v3_y, v3_z;
  DOUBLE_TYPE n1_x, n1_y, n1_z;
  DOUBLE_TYPE n2_x, n2_y, n2_z;
  
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

long long Uhash(long long v) {
   
   v = v * 3935559000370003845 + 2691343689449507681;
   v ^= v >> 21; v^= v << 37; v ^= v >> 4;
   v *= 4768777413237032717LL;
   v ^= v >> 20; v^= v << 41; v ^= v >> 5;
   
   return v;
}

const DOUBLE_TYPE PI = 3.141592653589793238462643383279502884;

DOUBLE_TYPE Uradians(DOUBLE_TYPE degree) {
  return degree * PI / 180;
}

DOUBLE_TYPE Udegrees(DOUBLE_TYPE radian) {
  return radian * 180 / PI;
}

DOUBLE_TYPE Upow(DOUBLE_TYPE a, DOUBLE_TYPE b) {
  return pow(a, b);
}
/*DOUBLE_TYPE pow(DOUBLE_TYPE a, int b) {
  return ::pow(a, (DOUBLE_TYPE)b);
}
DOUBLE_TYPE pow(int a, DOUBLE_TYPE b) {
  return ::pow((DOUBLE_TYPE)a, b);
}
DOUBLE_TYPE pow(int a, int b) {
  return ::pow((DOUBLE_TYPE)a, (DOUBLE_TYPE)b);
}*/

int Uregexp_match(const char *regex, const STRING_TYPE &s){
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

int Upreg_match(const regex_t &preg, const STRING_TYPE &s){
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
DOUBLE_TYPE Udiv(DOUBLE_TYPE x) { if(x==0.0) return 0.0; else return (1.0 / x); }
DOUBLE_TYPE UmulDbl(DOUBLE_TYPE x, DOUBLE_TYPE y) { return x * y; }

long Ulistmax(int v1, int v2) { return ((v1 > v2) ? v1 : v2 ); }
long Ulistmax(int v1, long v2) { return ((v1 > v2) ? v1 : v2 ); }
DOUBLE_TYPE Ulistmax(int v1, DOUBLE_TYPE v2) { return ((v1 > v2) ? v1 : v2); }

// long Ulistmax(long v1, int v2) { return ((v1 > v2) ? v1 : v2 ); }
// long Ulistmax(long v1, long v2) { return ((v1 > v2) ? v1 : v2 ); }
// DOUBLE_TYPE Ulistmax(DOUBLE_TYPE v1, DOUBLE_TYPE v2) { return ((v1 > v2) ? v1 : v2); }
// DOUBLE_TYPE Ulistmax(long v1, DOUBLE_TYPE v2) { return ((v2 < v1) ? v1 : v2); }
// DOUBLE_TYPE Ulistmax(DOUBLE_TYPE v1, long v2) { return ((v1 > v2) ? v1 : v2); }

// Type conversion functions
template <class T> 
STRING_TYPE cast_string(const T &t) {
	std::stringstream ss;
	ss << t;
	return STRING_TYPE(ss.str().c_str());
}
STRING_TYPE cast_string_from_date(date ymd)   { 
	std::stringstream ss;
	ss << ((ymd / 10000) % 10000)
	   << ((ymd / 100  ) % 100)
	   << ((ymd        ) % 100);
  return STRING_TYPE(ss.str().c_str());
}
date Udate(const char *c) { //cast_date_from_string
	unsigned int y, m, d;
	if(sscanf(c, "%u-%u-%u", &y, &m, &d) < 3){
	  cerr << "Invalid date string: "<< c << endl;
	}
	if((m > 12) || (d > 31)){ 
	  cerr << "Invalid date string: "<< c << endl;
	}
	return (y%10000) * 10000 + (m%100) * 100 + (d%100);
}

}