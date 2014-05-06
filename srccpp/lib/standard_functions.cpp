#include "standard_functions.hpp"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <regex.h>
#include <math.h>

namespace dbtoaster {

// Date extraction functions
// ImperativeCompiler synthesizes calls to the following from calls to 
// date_part
long Uyear_part(date d) { 
	return (d / 10000) % 10000;
}
long Umonth_part(date d) { 
	return (d / 100) % 100;
}
long Uday_part(date d) { 
	return d % 100;
}

// String functions
string Usubstring(string &s, long start, long len){
	return s.substr(start, len);
}

float Uvec_length(float x, float y, float z){
  return sqrt(x*x+y*y+z*z);
}

float Uvec_dot(float x1, float y1, float z1, 
              float x2, float y2, float z2){
  return x1*x2+y1*y2+z1*z2;
}

void Uvec_cross(float x1, float y1, float z1, 
               float x2, float y2, float z2,
               float& x, float& y, float& z){
  x = (y1*z2-z1*y2);
  y = (z1*x2-x1*z2);
  z = (x1*y2-y1*x2);
}

float Uvector_angle(float x1, float y1, float z1, 
              float x2, float y2, float z2){
  return acos(Uvec_dot(x1,y1,z1,x2,y2,z2) /
               (Uvec_length(x1,y1,z1)*Uvec_length(x2,y2,z2)));
}

float Udihedral_angle(float x1, float y1, float z1, 
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4){
  float v1_x, v1_y, v1_z;
  float v2_x, v2_y, v2_z;
  float v3_x, v3_y, v3_z;
  float n1_x, n1_y, n1_z;
  float n2_x, n2_y, n2_z;
  
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

const float PI = 3.141592653589793238462643383279502884;

float Uradians(float degree) {
  return degree * PI / 180;
}

float Udegrees(float radian) {
  return radian * 180 / PI;
}

float Upow(float a, float b) {
  return ::pow(a, b);
}
/*float pow(float a, int b) {
  return ::pow(a, (float)b);
}
float pow(int a, float b) {
  return ::pow((float)a, b);
}
float pow(int a, int b) {
  return ::pow((float)a, (float)b);
}*/

int Uregexp_match(const char *regex, string &s){
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

double Udiv(double x) { return ((x==0.0) ? 0.0 : (1.0 / x)); }
double UmulDbl(double x, double y) { return x * y; }
long UmulLng(long x, long y) { return x * y; }
long Ulistmax(long v1,  long v2) { return ((v1 > v2) ? v1 : v2 ); }
double Ulistmax(double v1, double v2) { return ((v1 > v2) ? v1 : v2); }
double Ulistmax(long v1, double v2) { return ((v1 > v2) ? v1 : v2); }
double Ulistmax(double v1, long v2) { return ((v1 > v2) ? v1 : v2); }

// Type conversion functions
template <class T> 
string cast_string(const T &t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}
string cast_string_from_date(date ymd)   { 
	std::stringstream ss;
	ss << ((ymd / 10000) % 10000)
	   << ((ymd / 100  ) % 100)
	   << ((ymd        ) % 100);
	return ss.str();
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