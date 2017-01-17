#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
using namespace std;
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "program_base.hpp"

#define USING_GENERIC_ENTRY false

#ifdef NUMWARE
  const int numWare = NUMWARE;
#else
  const int numWare = 2;
#endif
#ifdef NUMPROG
  const size_t numPrograms = NUMPROG;
#else
  const size_t numPrograms = 100;
#endif

const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
const size_t itemTblSize = 100000;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

     
struct SEntry5_IISDS {
  int _1;  int _2;  PString _3;  double _4;  PString _5;  SEntry5_IISDS *prv;  SEntry5_IISDS *nxt; void* backPtrs[5];
  SEntry5_IISDS() :_1(-2147483648), _2(-2147483648), _3(), _4(-1.7976931348623157E308), _5(), prv(nullptr), nxt(nullptr) {}
  SEntry5_IISDS(const int& _1, const int& _2, const PString& _3, const double& _4, const PString& _5) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), prv(nullptr), nxt(nullptr) {}
  SEntry5_IISDS* copy() const { return new SEntry5_IISDS(_1, _2, *_3.copy(), _4, *_5.copy()); }
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  SEntry11_IISSSSSSDDI *prv;  SEntry11_IISSSSSSDDI *nxt; void* backPtrs[11];
  SEntry11_IISSSSSSDDI() :_1(-2147483648), _2(-2147483648), _3(), _4(), _5(), _6(), _7(), _8(), _9(-1.7976931348623157E308), _10(-1.7976931348623157E308), _11(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI(const int& _1, const int& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const double& _9, const double& _10, const int& _11) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI* copy() const { return new SEntry11_IISSSSSSDDI(_1, _2, *_3.copy(), *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), _9, _10, _11); }
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[21];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const { return new SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), _13, *_14.copy(), _15, _16, _17, _18, _19, _20, *_21.copy()); }
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt; void* backPtrs[8];
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB* copy() const { return new SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8); }
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  SEntry3_III* copy() const { return new SEntry3_III(_1, _2, _3); }
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS* copy() const { return new SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, *_8.copy()); }
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS* copy() const { return new SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), *_13.copy(), _14, _15, _16, *_17.copy()); }
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS* copy() const { return new SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, *_10.copy()); }
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  SEntry9_ISSSSSSDD *prv;  SEntry9_ISSSSSSDD *nxt; void* backPtrs[9];
  SEntry9_ISSSSSSDD() :_1(-2147483648), _2(), _3(), _4(), _5(), _6(), _7(), _8(-1.7976931348623157E308), _9(-1.7976931348623157E308), prv(nullptr), nxt(nullptr) {}
  SEntry9_ISSSSSSDD(const int& _1, const PString& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const double& _8, const double& _9) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), prv(nullptr), nxt(nullptr) {}
  SEntry9_ISSSSSSDD* copy() const { return new SEntry9_ISSSSSSDD(_1, *_2.copy(), *_3.copy(), *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), _8, _9); }
};
bool operator== (const SEntry5_IISDS& o1, const SEntry5_IISDS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  (fabs(o1._4 - o2._4) < 0.01) && 
  o1._5 == o2._5;
}
bool operator== (const SEntry11_IISSSSSSDDI& o1, const SEntry11_IISSSSSSDDI& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8 && 
  (fabs(o1._9 - o2._9) < 0.01) && 
  (fabs(o1._10 - o2._10) < 0.01) && 
  o1._11 == o2._11;
}
bool operator== (const SEntry21_IIISSSSSSSSSTSDDDDIIS& o1, const SEntry21_IIISSSSSSSSSTSDDDDIIS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8 && 
  o1._9 == o2._9 && 
  o1._10 == o2._10 && 
  o1._11 == o2._11 && 
  o1._12 == o2._12 && 
  o1._13 == o2._13 && 
  o1._14 == o2._14 && 
  (fabs(o1._15 - o2._15) < 0.01) && 
  (fabs(o1._16 - o2._16) < 0.01) && 
  (fabs(o1._17 - o2._17) < 0.01) && 
  (fabs(o1._18 - o2._18) < 0.01) && 
  o1._19 == o2._19 && 
  o1._20 == o2._20 && 
  o1._21 == o2._21;
}
bool operator== (const SEntry8_IIIITIIB& o1, const SEntry8_IIIITIIB& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8;
}
bool operator== (const SEntry3_III& o1, const SEntry3_III& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3;
}
bool operator== (const SEntry8_IIIIITDS& o1, const SEntry8_IIIIITDS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  (fabs(o1._7 - o2._7) < 0.01) && 
  o1._8 == o2._8;
}
bool operator== (const SEntry17_IIISSSSSSSSSSIIIS& o1, const SEntry17_IIISSSSSSSSSSIIIS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8 && 
  o1._9 == o2._9 && 
  o1._10 == o2._10 && 
  o1._11 == o2._11 && 
  o1._12 == o2._12 && 
  o1._13 == o2._13 && 
  o1._14 == o2._14 && 
  o1._15 == o2._15 && 
  o1._16 == o2._16 && 
  o1._17 == o2._17;
}
bool operator== (const SEntry10_IIIIIITIDS& o1, const SEntry10_IIIIIITIDS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8 && 
  (fabs(o1._9 - o2._9) < 0.01) && 
  o1._10 == o2._10;
}
bool operator== (const SEntry9_ISSSSSSDD& o1, const SEntry9_ISSSSSSDD& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  (fabs(o1._8 - o2._8) < 0.01) && 
  (fabs(o1._9 - o2._9) < 0.01);
}
 struct SEntry10_IIIIIITIDS_Idx1234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x1946)  { 
    int x1947 = -889275714;
    int x1948 = x1946._1;
    int x1949 = HASH(x1948);
    int x1950 = -862048943*(x1949);
    int x1951 = x1950<<(15);
    int x1952 = x1950 >> (-15 & (8*sizeof(x1950)-1));
    int x1953 = x1951|(x1952);
    int x1954 = x1953*(461845907);
    int x1955 = x1947;
    int x1956 = x1954^(x1955);
    int x1957 = x1956<<(13);
    int x1958 = x1956 >> (-13 & (8*sizeof(x1956)-1));
    int x1959 = x1957|(x1958);
    int x1960 = x1959*(5);
    int x1961 = x1960+(-430675100);
    x1947 = x1961;
    int x1963 = x1946._2;
    int x1964 = HASH(x1963);
    int x1965 = -862048943*(x1964);
    int x1966 = x1965<<(15);
    int x1967 = x1965 >> (-15 & (8*sizeof(x1965)-1));
    int x1968 = x1966|(x1967);
    int x1969 = x1968*(461845907);
    int x1970 = x1947;
    int x1971 = x1969^(x1970);
    int x1972 = x1971<<(13);
    int x1973 = x1971 >> (-13 & (8*sizeof(x1971)-1));
    int x1974 = x1972|(x1973);
    int x1975 = x1974*(5);
    int x1976 = x1975+(-430675100);
    x1947 = x1976;
    int x1978 = x1946._3;
    int x1979 = HASH(x1978);
    int x1980 = -862048943*(x1979);
    int x1981 = x1980<<(15);
    int x1982 = x1980 >> (-15 & (8*sizeof(x1980)-1));
    int x1983 = x1981|(x1982);
    int x1984 = x1983*(461845907);
    int x1985 = x1947;
    int x1986 = x1984^(x1985);
    int x1987 = x1986<<(13);
    int x1988 = x1986 >> (-13 & (8*sizeof(x1986)-1));
    int x1989 = x1987|(x1988);
    int x1990 = x1989*(5);
    int x1991 = x1990+(-430675100);
    x1947 = x1991;
    int x1993 = x1946._4;
    int x1994 = HASH(x1993);
    int x1995 = -862048943*(x1994);
    int x1996 = x1995<<(15);
    int x1997 = x1995 >> (-15 & (8*sizeof(x1995)-1));
    int x1998 = x1996|(x1997);
    int x1999 = x1998*(461845907);
    int x2000 = x1947;
    int x2001 = x1999^(x2000);
    int x2002 = x2001<<(13);
    int x2003 = x2001 >> (-13 & (8*sizeof(x2001)-1));
    int x2004 = x2002|(x2003);
    int x2005 = x2004*(5);
    int x2006 = x2005+(-430675100);
    x1947 = x2006;
    int x2008 = x1947;
    int x2009 = x2008^(2);
    int x2010 = x2009 >> (16 & (8*sizeof(x2009)-1));
    int x2011 = x2009^(x2010);
    int x2012 = x2011*(-2048144789);
    int x2013 = x2012 >> (13 & (8*sizeof(x2012)-1));
    int x2014 = x2012^(x2013);
    int x2015 = x2014*(-1028477387);
    int x2016 = x2015 >> (16 & (8*sizeof(x2015)-1));
    int x2017 = x2015^(x2016);
    return x2017; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x2019, const struct SEntry10_IIIIIITIDS& x2020) { 
    int ite12428 = 0;
    if(1) {
      
      int x2021 = x2019._1;
      int x2022 = x2020._1;
      int x2023 = x2021==(-2147483648);
      int ite12552 = 0;
      if(x2023) {
        ite12552 = 1;
      } else {
        
        
        int x2024 = x2022==(-2147483648);
        int x12554 = x2024;
        ite12552 = x12554;
      };
      int x12434 = ite12552;
      int ite12559 = 0;
      if(x12434) {
        ite12559 = 1;
      } else {
        
        
        int x2026 = x2021==(x2022);
        int x12561 = x2026;
        ite12559 = x12561;
      };
      int x12436 = ite12559;
      int x12429 = x12436;
      ite12428 = x12429;
    } else {
      
      ite12428 = 0;
    };
    int x12409 = ite12428;
    int ite12441 = 0;
    if(x12409) {
      
      int x2029 = x2019._2;
      int x2030 = x2020._2;
      int x2031 = x2029==(-2147483648);
      int ite12575 = 0;
      if(x2031) {
        ite12575 = 1;
      } else {
        
        
        int x2032 = x2030==(-2147483648);
        int x12577 = x2032;
        ite12575 = x12577;
      };
      int x12447 = ite12575;
      int ite12582 = 0;
      if(x12447) {
        ite12582 = 1;
      } else {
        
        
        int x2034 = x2029==(x2030);
        int x12584 = x2034;
        ite12582 = x12584;
      };
      int x12449 = ite12582;
      int x12442 = x12449;
      ite12441 = x12442;
    } else {
      
      ite12441 = 0;
    };
    int x12411 = ite12441;
    int ite12454 = 0;
    if(x12411) {
      
      int x2037 = x2019._3;
      int x2038 = x2020._3;
      int x2039 = x2037==(-2147483648);
      int ite12598 = 0;
      if(x2039) {
        ite12598 = 1;
      } else {
        
        
        int x2040 = x2038==(-2147483648);
        int x12600 = x2040;
        ite12598 = x12600;
      };
      int x12460 = ite12598;
      int ite12605 = 0;
      if(x12460) {
        ite12605 = 1;
      } else {
        
        
        int x2042 = x2037==(x2038);
        int x12607 = x2042;
        ite12605 = x12607;
      };
      int x12462 = ite12605;
      int x12455 = x12462;
      ite12454 = x12455;
    } else {
      
      ite12454 = 0;
    };
    int x12413 = ite12454;
    int ite12467 = 0;
    if(x12413) {
      
      int x2045 = x2019._4;
      int x2046 = x2020._4;
      int x2047 = x2045==(-2147483648);
      int ite12621 = 0;
      if(x2047) {
        ite12621 = 1;
      } else {
        
        
        int x2048 = x2046==(-2147483648);
        int x12623 = x2048;
        ite12621 = x12623;
      };
      int x12473 = ite12621;
      int ite12628 = 0;
      if(x12473) {
        ite12628 = 1;
      } else {
        
        
        int x2050 = x2045==(x2046);
        int x12630 = x2050;
        ite12628 = x12630;
      };
      int x12475 = ite12628;
      int x12468 = x12475;
      ite12467 = x12468;
    } else {
      
      ite12467 = 0;
    };
    int x12415 = ite12467;
    int ite12480 = 0;
    if(x12415) {
      
      int x2053 = x2019._5;
      int x2054 = x2020._5;
      int x2055 = x2053==(-2147483648);
      int ite12644 = 0;
      if(x2055) {
        ite12644 = 1;
      } else {
        
        
        int x2056 = x2054==(-2147483648);
        int x12646 = x2056;
        ite12644 = x12646;
      };
      int x12486 = ite12644;
      int ite12651 = 0;
      if(x12486) {
        ite12651 = 1;
      } else {
        
        
        int x2058 = x2053==(x2054);
        int x12653 = x2058;
        ite12651 = x12653;
      };
      int x12488 = ite12651;
      int x12481 = x12488;
      ite12480 = x12481;
    } else {
      
      ite12480 = 0;
    };
    int x12417 = ite12480;
    int ite12493 = 0;
    if(x12417) {
      
      int x2061 = x2019._6;
      int x2062 = x2020._6;
      int x2063 = x2061==(-2147483648);
      int ite12667 = 0;
      if(x2063) {
        ite12667 = 1;
      } else {
        
        
        int x2064 = x2062==(-2147483648);
        int x12669 = x2064;
        ite12667 = x12669;
      };
      int x12499 = ite12667;
      int ite12674 = 0;
      if(x12499) {
        ite12674 = 1;
      } else {
        
        
        int x2066 = x2061==(x2062);
        int x12676 = x2066;
        ite12674 = x12676;
      };
      int x12501 = ite12674;
      int x12494 = x12501;
      ite12493 = x12494;
    } else {
      
      ite12493 = 0;
    };
    int x12419 = ite12493;
    int ite12506 = 0;
    if(x12419) {
      
      date x2069 = x2019._7;
      date x2070 = x2020._7;
      int x2071 = x2069==(0);
      int ite12690 = 0;
      if(x2071) {
        ite12690 = 1;
      } else {
        
        
        int x2072 = x2070==(0);
        int x12692 = x2072;
        ite12690 = x12692;
      };
      int x12512 = ite12690;
      int ite12697 = 0;
      if(x12512) {
        ite12697 = 1;
      } else {
        
        
        int x2074 = x2069==(x2070);
        int x12699 = x2074;
        ite12697 = x12699;
      };
      int x12514 = ite12697;
      int x12507 = x12514;
      ite12506 = x12507;
    } else {
      
      ite12506 = 0;
    };
    int x12421 = ite12506;
    int ite12519 = 0;
    if(x12421) {
      
      int x2077 = x2019._8;
      int x2078 = x2020._8;
      int x2079 = x2077==(-2147483648);
      int ite12713 = 0;
      if(x2079) {
        ite12713 = 1;
      } else {
        
        
        int x2080 = x2078==(-2147483648);
        int x12715 = x2080;
        ite12713 = x12715;
      };
      int x12525 = ite12713;
      int ite12720 = 0;
      if(x12525) {
        ite12720 = 1;
      } else {
        
        
        int x2082 = x2077==(x2078);
        int x12722 = x2082;
        ite12720 = x12722;
      };
      int x12527 = ite12720;
      int x12520 = x12527;
      ite12519 = x12520;
    } else {
      
      ite12519 = 0;
    };
    int x12423 = ite12519;
    int ite12532 = 0;
    if(x12423) {
      
      double x2085 = x2019._9;
      double x2086 = x2020._9;
      int x2087 = x2085==(-1.7976931348623157E308);
      int ite12736 = 0;
      if(x2087) {
        ite12736 = 1;
      } else {
        
        
        int x2088 = x2086==(-1.7976931348623157E308);
        int x12738 = x2088;
        ite12736 = x12738;
      };
      int x12538 = ite12736;
      int ite12743 = 0;
      if(x12538) {
        ite12743 = 1;
      } else {
        
        
        int x2090 = x2085==(x2086);
        int x12745 = x2090;
        ite12743 = x12745;
      };
      int x12540 = ite12743;
      int x12533 = x12540;
      ite12532 = x12533;
    } else {
      
      ite12532 = 0;
    };
    int x12425 = ite12532;
    int x2093 = x12425 ? 0 : 1;
    return x2093; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x1236)  { 
    int x1237 = -889275714;
    int x1238 = x1236._1;
    int x1239 = HASH(x1238);
    int x1240 = -862048943*(x1239);
    int x1241 = x1240<<(15);
    int x1242 = x1240 >> (-15 & (8*sizeof(x1240)-1));
    int x1243 = x1241|(x1242);
    int x1244 = x1243*(461845907);
    int x1245 = x1237;
    int x1246 = x1244^(x1245);
    int x1247 = x1246<<(13);
    int x1248 = x1246 >> (-13 & (8*sizeof(x1246)-1));
    int x1249 = x1247|(x1248);
    int x1250 = x1249*(5);
    int x1251 = x1250+(-430675100);
    x1237 = x1251;
    int x1253 = x1236._2;
    int x1254 = HASH(x1253);
    int x1255 = -862048943*(x1254);
    int x1256 = x1255<<(15);
    int x1257 = x1255 >> (-15 & (8*sizeof(x1255)-1));
    int x1258 = x1256|(x1257);
    int x1259 = x1258*(461845907);
    int x1260 = x1237;
    int x1261 = x1259^(x1260);
    int x1262 = x1261<<(13);
    int x1263 = x1261 >> (-13 & (8*sizeof(x1261)-1));
    int x1264 = x1262|(x1263);
    int x1265 = x1264*(5);
    int x1266 = x1265+(-430675100);
    x1237 = x1266;
    int x1268 = x1236._3;
    int x1269 = HASH(x1268);
    int x1270 = -862048943*(x1269);
    int x1271 = x1270<<(15);
    int x1272 = x1270 >> (-15 & (8*sizeof(x1270)-1));
    int x1273 = x1271|(x1272);
    int x1274 = x1273*(461845907);
    int x1275 = x1237;
    int x1276 = x1274^(x1275);
    int x1277 = x1276<<(13);
    int x1278 = x1276 >> (-13 & (8*sizeof(x1276)-1));
    int x1279 = x1277|(x1278);
    int x1280 = x1279*(5);
    int x1281 = x1280+(-430675100);
    x1237 = x1281;
    int x1283 = x1237;
    int x1284 = x1283^(2);
    int x1285 = x1284 >> (16 & (8*sizeof(x1284)-1));
    int x1286 = x1284^(x1285);
    int x1287 = x1286*(-2048144789);
    int x1288 = x1287 >> (13 & (8*sizeof(x1287)-1));
    int x1289 = x1287^(x1288);
    int x1290 = x1289*(-1028477387);
    int x1291 = x1290 >> (16 & (8*sizeof(x1290)-1));
    int x1292 = x1290^(x1291);
    return x1292; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x1294, const struct SEntry3_III& x1295) { 
    int ite13023 = 0;
    if(1) {
      
      int x1296 = x1294._1;
      int x1297 = x1295._1;
      int x1298 = x1296==(-2147483648);
      int ite13056 = 0;
      if(x1298) {
        ite13056 = 1;
      } else {
        
        
        int x1299 = x1297==(-2147483648);
        int x13058 = x1299;
        ite13056 = x13058;
      };
      int x13029 = ite13056;
      int ite13063 = 0;
      if(x13029) {
        ite13063 = 1;
      } else {
        
        
        int x1301 = x1296==(x1297);
        int x13065 = x1301;
        ite13063 = x13065;
      };
      int x13031 = ite13063;
      int x13024 = x13031;
      ite13023 = x13024;
    } else {
      
      ite13023 = 0;
    };
    int x13018 = ite13023;
    int ite13036 = 0;
    if(x13018) {
      
      int x1304 = x1294._2;
      int x1305 = x1295._2;
      int x1306 = x1304==(-2147483648);
      int ite13079 = 0;
      if(x1306) {
        ite13079 = 1;
      } else {
        
        
        int x1307 = x1305==(-2147483648);
        int x13081 = x1307;
        ite13079 = x13081;
      };
      int x13042 = ite13079;
      int ite13086 = 0;
      if(x13042) {
        ite13086 = 1;
      } else {
        
        
        int x1309 = x1304==(x1305);
        int x13088 = x1309;
        ite13086 = x13088;
      };
      int x13044 = ite13086;
      int x13037 = x13044;
      ite13036 = x13037;
    } else {
      
      ite13036 = 0;
    };
    int x13020 = ite13036;
    int x1312 = x13020 ? 0 : 1;
    return x1312; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x2100)  { 
    int x2101 = -889275714;
    int x2102 = x2100._1;
    int x2103 = HASH(x2102);
    int x2104 = -862048943*(x2103);
    int x2105 = x2104<<(15);
    int x2106 = x2104 >> (-15 & (8*sizeof(x2104)-1));
    int x2107 = x2105|(x2106);
    int x2108 = x2107*(461845907);
    int x2109 = x2101;
    int x2110 = x2108^(x2109);
    int x2111 = x2110<<(13);
    int x2112 = x2110 >> (-13 & (8*sizeof(x2110)-1));
    int x2113 = x2111|(x2112);
    int x2114 = x2113*(5);
    int x2115 = x2114+(-430675100);
    x2101 = x2115;
    int x2117 = x2100._2;
    int x2118 = HASH(x2117);
    int x2119 = -862048943*(x2118);
    int x2120 = x2119<<(15);
    int x2121 = x2119 >> (-15 & (8*sizeof(x2119)-1));
    int x2122 = x2120|(x2121);
    int x2123 = x2122*(461845907);
    int x2124 = x2101;
    int x2125 = x2123^(x2124);
    int x2126 = x2125<<(13);
    int x2127 = x2125 >> (-13 & (8*sizeof(x2125)-1));
    int x2128 = x2126|(x2127);
    int x2129 = x2128*(5);
    int x2130 = x2129+(-430675100);
    x2101 = x2130;
    int x2132 = x2100._3;
    int x2133 = HASH(x2132);
    int x2134 = -862048943*(x2133);
    int x2135 = x2134<<(15);
    int x2136 = x2134 >> (-15 & (8*sizeof(x2134)-1));
    int x2137 = x2135|(x2136);
    int x2138 = x2137*(461845907);
    int x2139 = x2101;
    int x2140 = x2138^(x2139);
    int x2141 = x2140<<(13);
    int x2142 = x2140 >> (-13 & (8*sizeof(x2140)-1));
    int x2143 = x2141|(x2142);
    int x2144 = x2143*(5);
    int x2145 = x2144+(-430675100);
    x2101 = x2145;
    int x2147 = x2101;
    int x2148 = x2147^(2);
    int x2149 = x2148 >> (16 & (8*sizeof(x2148)-1));
    int x2150 = x2148^(x2149);
    int x2151 = x2150*(-2048144789);
    int x2152 = x2151 >> (13 & (8*sizeof(x2151)-1));
    int x2153 = x2151^(x2152);
    int x2154 = x2153*(-1028477387);
    int x2155 = x2154 >> (16 & (8*sizeof(x2154)-1));
    int x2156 = x2154^(x2155);
    return x2156; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x2158, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x2159) { 
    int ite13241 = 0;
    if(1) {
      
      int x2160 = x2158._1;
      int x2161 = x2159._1;
      int x2162 = x2160==(-2147483648);
      int ite13508 = 0;
      if(x2162) {
        ite13508 = 1;
      } else {
        
        
        int x2163 = x2161==(-2147483648);
        int x13510 = x2163;
        ite13508 = x13510;
      };
      int x13247 = ite13508;
      int ite13515 = 0;
      if(x13247) {
        ite13515 = 1;
      } else {
        
        
        int x2165 = x2160==(x2161);
        int x13517 = x2165;
        ite13515 = x13517;
      };
      int x13249 = ite13515;
      int x13242 = x13249;
      ite13241 = x13242;
    } else {
      
      ite13241 = 0;
    };
    int x13200 = ite13241;
    int ite13254 = 0;
    if(x13200) {
      
      int x2168 = x2158._2;
      int x2169 = x2159._2;
      int x2170 = x2168==(-2147483648);
      int ite13531 = 0;
      if(x2170) {
        ite13531 = 1;
      } else {
        
        
        int x2171 = x2169==(-2147483648);
        int x13533 = x2171;
        ite13531 = x13533;
      };
      int x13260 = ite13531;
      int ite13538 = 0;
      if(x13260) {
        ite13538 = 1;
      } else {
        
        
        int x2173 = x2168==(x2169);
        int x13540 = x2173;
        ite13538 = x13540;
      };
      int x13262 = ite13538;
      int x13255 = x13262;
      ite13254 = x13255;
    } else {
      
      ite13254 = 0;
    };
    int x13202 = ite13254;
    int ite13267 = 0;
    if(x13202) {
      
      int x2176 = x2158._3;
      int x2177 = x2159._3;
      int x2178 = x2176==(-2147483648);
      int ite13554 = 0;
      if(x2178) {
        ite13554 = 1;
      } else {
        
        
        int x2179 = x2177==(-2147483648);
        int x13556 = x2179;
        ite13554 = x13556;
      };
      int x13273 = ite13554;
      int ite13561 = 0;
      if(x13273) {
        ite13561 = 1;
      } else {
        
        
        int x2181 = x2176==(x2177);
        int x13563 = x2181;
        ite13561 = x13563;
      };
      int x13275 = ite13561;
      int x13268 = x13275;
      ite13267 = x13268;
    } else {
      
      ite13267 = 0;
    };
    int x13204 = ite13267;
    int ite13280 = 0;
    if(x13204) {
      
      PString x2184 = x2158._4;
      PString x2185 = x2159._4;
      int x2186 = x2184.data_ == nullptr;
      int ite13577 = 0;
      if(x2186) {
        ite13577 = 1;
      } else {
        
        
        int x2187 = x2185.data_ == nullptr;
        int x13579 = x2187;
        ite13577 = x13579;
      };
      int x13286 = ite13577;
      int ite13584 = 0;
      if(x13286) {
        ite13584 = 1;
      } else {
        
        
        int x2189 = x2184==(x2185);
        int x13586 = x2189;
        ite13584 = x13586;
      };
      int x13288 = ite13584;
      int x13281 = x13288;
      ite13280 = x13281;
    } else {
      
      ite13280 = 0;
    };
    int x13206 = ite13280;
    int ite13293 = 0;
    if(x13206) {
      
      PString x2192 = x2158._5;
      PString x2193 = x2159._5;
      int x2194 = x2192.data_ == nullptr;
      int ite13600 = 0;
      if(x2194) {
        ite13600 = 1;
      } else {
        
        
        int x2195 = x2193.data_ == nullptr;
        int x13602 = x2195;
        ite13600 = x13602;
      };
      int x13299 = ite13600;
      int ite13607 = 0;
      if(x13299) {
        ite13607 = 1;
      } else {
        
        
        int x2197 = x2192==(x2193);
        int x13609 = x2197;
        ite13607 = x13609;
      };
      int x13301 = ite13607;
      int x13294 = x13301;
      ite13293 = x13294;
    } else {
      
      ite13293 = 0;
    };
    int x13208 = ite13293;
    int ite13306 = 0;
    if(x13208) {
      
      PString x2200 = x2158._6;
      PString x2201 = x2159._6;
      int x2202 = x2200.data_ == nullptr;
      int ite13623 = 0;
      if(x2202) {
        ite13623 = 1;
      } else {
        
        
        int x2203 = x2201.data_ == nullptr;
        int x13625 = x2203;
        ite13623 = x13625;
      };
      int x13312 = ite13623;
      int ite13630 = 0;
      if(x13312) {
        ite13630 = 1;
      } else {
        
        
        int x2205 = x2200==(x2201);
        int x13632 = x2205;
        ite13630 = x13632;
      };
      int x13314 = ite13630;
      int x13307 = x13314;
      ite13306 = x13307;
    } else {
      
      ite13306 = 0;
    };
    int x13210 = ite13306;
    int ite13319 = 0;
    if(x13210) {
      
      PString x2208 = x2158._7;
      PString x2209 = x2159._7;
      int x2210 = x2208.data_ == nullptr;
      int ite13646 = 0;
      if(x2210) {
        ite13646 = 1;
      } else {
        
        
        int x2211 = x2209.data_ == nullptr;
        int x13648 = x2211;
        ite13646 = x13648;
      };
      int x13325 = ite13646;
      int ite13653 = 0;
      if(x13325) {
        ite13653 = 1;
      } else {
        
        
        int x2213 = x2208==(x2209);
        int x13655 = x2213;
        ite13653 = x13655;
      };
      int x13327 = ite13653;
      int x13320 = x13327;
      ite13319 = x13320;
    } else {
      
      ite13319 = 0;
    };
    int x13212 = ite13319;
    int ite13332 = 0;
    if(x13212) {
      
      PString x2216 = x2158._8;
      PString x2217 = x2159._8;
      int x2218 = x2216.data_ == nullptr;
      int ite13669 = 0;
      if(x2218) {
        ite13669 = 1;
      } else {
        
        
        int x2219 = x2217.data_ == nullptr;
        int x13671 = x2219;
        ite13669 = x13671;
      };
      int x13338 = ite13669;
      int ite13676 = 0;
      if(x13338) {
        ite13676 = 1;
      } else {
        
        
        int x2221 = x2216==(x2217);
        int x13678 = x2221;
        ite13676 = x13678;
      };
      int x13340 = ite13676;
      int x13333 = x13340;
      ite13332 = x13333;
    } else {
      
      ite13332 = 0;
    };
    int x13214 = ite13332;
    int ite13345 = 0;
    if(x13214) {
      
      PString x2224 = x2158._9;
      PString x2225 = x2159._9;
      int x2226 = x2224.data_ == nullptr;
      int ite13692 = 0;
      if(x2226) {
        ite13692 = 1;
      } else {
        
        
        int x2227 = x2225.data_ == nullptr;
        int x13694 = x2227;
        ite13692 = x13694;
      };
      int x13351 = ite13692;
      int ite13699 = 0;
      if(x13351) {
        ite13699 = 1;
      } else {
        
        
        int x2229 = x2224==(x2225);
        int x13701 = x2229;
        ite13699 = x13701;
      };
      int x13353 = ite13699;
      int x13346 = x13353;
      ite13345 = x13346;
    } else {
      
      ite13345 = 0;
    };
    int x13216 = ite13345;
    int ite13358 = 0;
    if(x13216) {
      
      PString x2232 = x2158._10;
      PString x2233 = x2159._10;
      int x2234 = x2232.data_ == nullptr;
      int ite13715 = 0;
      if(x2234) {
        ite13715 = 1;
      } else {
        
        
        int x2235 = x2233.data_ == nullptr;
        int x13717 = x2235;
        ite13715 = x13717;
      };
      int x13364 = ite13715;
      int ite13722 = 0;
      if(x13364) {
        ite13722 = 1;
      } else {
        
        
        int x2237 = x2232==(x2233);
        int x13724 = x2237;
        ite13722 = x13724;
      };
      int x13366 = ite13722;
      int x13359 = x13366;
      ite13358 = x13359;
    } else {
      
      ite13358 = 0;
    };
    int x13218 = ite13358;
    int ite13371 = 0;
    if(x13218) {
      
      PString x2240 = x2158._11;
      PString x2241 = x2159._11;
      int x2242 = x2240.data_ == nullptr;
      int ite13738 = 0;
      if(x2242) {
        ite13738 = 1;
      } else {
        
        
        int x2243 = x2241.data_ == nullptr;
        int x13740 = x2243;
        ite13738 = x13740;
      };
      int x13377 = ite13738;
      int ite13745 = 0;
      if(x13377) {
        ite13745 = 1;
      } else {
        
        
        int x2245 = x2240==(x2241);
        int x13747 = x2245;
        ite13745 = x13747;
      };
      int x13379 = ite13745;
      int x13372 = x13379;
      ite13371 = x13372;
    } else {
      
      ite13371 = 0;
    };
    int x13220 = ite13371;
    int ite13384 = 0;
    if(x13220) {
      
      PString x2248 = x2158._12;
      PString x2249 = x2159._12;
      int x2250 = x2248.data_ == nullptr;
      int ite13761 = 0;
      if(x2250) {
        ite13761 = 1;
      } else {
        
        
        int x2251 = x2249.data_ == nullptr;
        int x13763 = x2251;
        ite13761 = x13763;
      };
      int x13390 = ite13761;
      int ite13768 = 0;
      if(x13390) {
        ite13768 = 1;
      } else {
        
        
        int x2253 = x2248==(x2249);
        int x13770 = x2253;
        ite13768 = x13770;
      };
      int x13392 = ite13768;
      int x13385 = x13392;
      ite13384 = x13385;
    } else {
      
      ite13384 = 0;
    };
    int x13222 = ite13384;
    int ite13397 = 0;
    if(x13222) {
      
      date x2256 = x2158._13;
      date x2257 = x2159._13;
      int x2258 = x2256==(0);
      int ite13784 = 0;
      if(x2258) {
        ite13784 = 1;
      } else {
        
        
        int x2259 = x2257==(0);
        int x13786 = x2259;
        ite13784 = x13786;
      };
      int x13403 = ite13784;
      int ite13791 = 0;
      if(x13403) {
        ite13791 = 1;
      } else {
        
        
        int x2261 = x2256==(x2257);
        int x13793 = x2261;
        ite13791 = x13793;
      };
      int x13405 = ite13791;
      int x13398 = x13405;
      ite13397 = x13398;
    } else {
      
      ite13397 = 0;
    };
    int x13224 = ite13397;
    int ite13410 = 0;
    if(x13224) {
      
      PString x2264 = x2158._14;
      PString x2265 = x2159._14;
      int x2266 = x2264.data_ == nullptr;
      int ite13807 = 0;
      if(x2266) {
        ite13807 = 1;
      } else {
        
        
        int x2267 = x2265.data_ == nullptr;
        int x13809 = x2267;
        ite13807 = x13809;
      };
      int x13416 = ite13807;
      int ite13814 = 0;
      if(x13416) {
        ite13814 = 1;
      } else {
        
        
        int x2269 = x2264==(x2265);
        int x13816 = x2269;
        ite13814 = x13816;
      };
      int x13418 = ite13814;
      int x13411 = x13418;
      ite13410 = x13411;
    } else {
      
      ite13410 = 0;
    };
    int x13226 = ite13410;
    int ite13423 = 0;
    if(x13226) {
      
      double x2272 = x2158._15;
      double x2273 = x2159._15;
      int x2274 = x2272==(-1.7976931348623157E308);
      int ite13830 = 0;
      if(x2274) {
        ite13830 = 1;
      } else {
        
        
        int x2275 = x2273==(-1.7976931348623157E308);
        int x13832 = x2275;
        ite13830 = x13832;
      };
      int x13429 = ite13830;
      int ite13837 = 0;
      if(x13429) {
        ite13837 = 1;
      } else {
        
        
        int x2277 = x2272==(x2273);
        int x13839 = x2277;
        ite13837 = x13839;
      };
      int x13431 = ite13837;
      int x13424 = x13431;
      ite13423 = x13424;
    } else {
      
      ite13423 = 0;
    };
    int x13228 = ite13423;
    int ite13436 = 0;
    if(x13228) {
      
      double x2280 = x2158._16;
      double x2281 = x2159._16;
      int x2282 = x2280==(-1.7976931348623157E308);
      int ite13853 = 0;
      if(x2282) {
        ite13853 = 1;
      } else {
        
        
        int x2283 = x2281==(-1.7976931348623157E308);
        int x13855 = x2283;
        ite13853 = x13855;
      };
      int x13442 = ite13853;
      int ite13860 = 0;
      if(x13442) {
        ite13860 = 1;
      } else {
        
        
        int x2285 = x2280==(x2281);
        int x13862 = x2285;
        ite13860 = x13862;
      };
      int x13444 = ite13860;
      int x13437 = x13444;
      ite13436 = x13437;
    } else {
      
      ite13436 = 0;
    };
    int x13230 = ite13436;
    int ite13449 = 0;
    if(x13230) {
      
      double x2288 = x2158._17;
      double x2289 = x2159._17;
      int x2290 = x2288==(-1.7976931348623157E308);
      int ite13876 = 0;
      if(x2290) {
        ite13876 = 1;
      } else {
        
        
        int x2291 = x2289==(-1.7976931348623157E308);
        int x13878 = x2291;
        ite13876 = x13878;
      };
      int x13455 = ite13876;
      int ite13883 = 0;
      if(x13455) {
        ite13883 = 1;
      } else {
        
        
        int x2293 = x2288==(x2289);
        int x13885 = x2293;
        ite13883 = x13885;
      };
      int x13457 = ite13883;
      int x13450 = x13457;
      ite13449 = x13450;
    } else {
      
      ite13449 = 0;
    };
    int x13232 = ite13449;
    int ite13462 = 0;
    if(x13232) {
      
      double x2296 = x2158._18;
      double x2297 = x2159._18;
      int x2298 = x2296==(-1.7976931348623157E308);
      int ite13899 = 0;
      if(x2298) {
        ite13899 = 1;
      } else {
        
        
        int x2299 = x2297==(-1.7976931348623157E308);
        int x13901 = x2299;
        ite13899 = x13901;
      };
      int x13468 = ite13899;
      int ite13906 = 0;
      if(x13468) {
        ite13906 = 1;
      } else {
        
        
        int x2301 = x2296==(x2297);
        int x13908 = x2301;
        ite13906 = x13908;
      };
      int x13470 = ite13906;
      int x13463 = x13470;
      ite13462 = x13463;
    } else {
      
      ite13462 = 0;
    };
    int x13234 = ite13462;
    int ite13475 = 0;
    if(x13234) {
      
      int x2304 = x2158._19;
      int x2305 = x2159._19;
      int x2306 = x2304==(-2147483648);
      int ite13922 = 0;
      if(x2306) {
        ite13922 = 1;
      } else {
        
        
        int x2307 = x2305==(-2147483648);
        int x13924 = x2307;
        ite13922 = x13924;
      };
      int x13481 = ite13922;
      int ite13929 = 0;
      if(x13481) {
        ite13929 = 1;
      } else {
        
        
        int x2309 = x2304==(x2305);
        int x13931 = x2309;
        ite13929 = x13931;
      };
      int x13483 = ite13929;
      int x13476 = x13483;
      ite13475 = x13476;
    } else {
      
      ite13475 = 0;
    };
    int x13236 = ite13475;
    int ite13488 = 0;
    if(x13236) {
      
      int x2312 = x2158._20;
      int x2313 = x2159._20;
      int x2314 = x2312==(-2147483648);
      int ite13945 = 0;
      if(x2314) {
        ite13945 = 1;
      } else {
        
        
        int x2315 = x2313==(-2147483648);
        int x13947 = x2315;
        ite13945 = x13947;
      };
      int x13494 = ite13945;
      int ite13952 = 0;
      if(x13494) {
        ite13952 = 1;
      } else {
        
        
        int x2317 = x2312==(x2313);
        int x13954 = x2317;
        ite13952 = x13954;
      };
      int x13496 = ite13952;
      int x13489 = x13496;
      ite13488 = x13489;
    } else {
      
      ite13488 = 0;
    };
    int x13238 = ite13488;
    int x2320 = x13238 ? 0 : 1;
    return x2320; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx12 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x2327)  { 
    int x2328 = -889275714;
    int x2329 = x2327._1;
    int x2330 = HASH(x2329);
    int x2331 = -862048943*(x2330);
    int x2332 = x2331<<(15);
    int x2333 = x2331 >> (-15 & (8*sizeof(x2331)-1));
    int x2334 = x2332|(x2333);
    int x2335 = x2334*(461845907);
    int x2336 = x2328;
    int x2337 = x2335^(x2336);
    int x2338 = x2337<<(13);
    int x2339 = x2337 >> (-13 & (8*sizeof(x2337)-1));
    int x2340 = x2338|(x2339);
    int x2341 = x2340*(5);
    int x2342 = x2341+(-430675100);
    x2328 = x2342;
    int x2344 = x2327._2;
    int x2345 = HASH(x2344);
    int x2346 = -862048943*(x2345);
    int x2347 = x2346<<(15);
    int x2348 = x2346 >> (-15 & (8*sizeof(x2346)-1));
    int x2349 = x2347|(x2348);
    int x2350 = x2349*(461845907);
    int x2351 = x2328;
    int x2352 = x2350^(x2351);
    int x2353 = x2352<<(13);
    int x2354 = x2352 >> (-13 & (8*sizeof(x2352)-1));
    int x2355 = x2353|(x2354);
    int x2356 = x2355*(5);
    int x2357 = x2356+(-430675100);
    x2328 = x2357;
    int x2359 = x2328;
    int x2360 = x2359^(2);
    int x2361 = x2360 >> (16 & (8*sizeof(x2360)-1));
    int x2362 = x2360^(x2361);
    int x2363 = x2362*(-2048144789);
    int x2364 = x2363 >> (13 & (8*sizeof(x2363)-1));
    int x2365 = x2363^(x2364);
    int x2366 = x2365*(-1028477387);
    int x2367 = x2366 >> (16 & (8*sizeof(x2366)-1));
    int x2368 = x2366^(x2367);
    return x2368; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x2370, const struct SEntry17_IIISSSSSSSSSSIIIS& x2371) { 
    int ite14498 = 0;
    if(1) {
      
      int x2372 = x2370._1;
      int x2373 = x2371._1;
      int x2374 = x2372==(-2147483648);
      int ite14713 = 0;
      if(x2374) {
        ite14713 = 1;
      } else {
        
        
        int x2375 = x2373==(-2147483648);
        int x14715 = x2375;
        ite14713 = x14715;
      };
      int x14504 = ite14713;
      int ite14720 = 0;
      if(x14504) {
        ite14720 = 1;
      } else {
        
        
        int x2377 = x2372==(x2373);
        int x14722 = x2377;
        ite14720 = x14722;
      };
      int x14506 = ite14720;
      int x14499 = x14506;
      ite14498 = x14499;
    } else {
      
      ite14498 = 0;
    };
    int x14465 = ite14498;
    int ite14511 = 0;
    if(x14465) {
      
      int x2380 = x2370._2;
      int x2381 = x2371._2;
      int x2382 = x2380==(-2147483648);
      int ite14736 = 0;
      if(x2382) {
        ite14736 = 1;
      } else {
        
        
        int x2383 = x2381==(-2147483648);
        int x14738 = x2383;
        ite14736 = x14738;
      };
      int x14517 = ite14736;
      int ite14743 = 0;
      if(x14517) {
        ite14743 = 1;
      } else {
        
        
        int x2385 = x2380==(x2381);
        int x14745 = x2385;
        ite14743 = x14745;
      };
      int x14519 = ite14743;
      int x14512 = x14519;
      ite14511 = x14512;
    } else {
      
      ite14511 = 0;
    };
    int x14467 = ite14511;
    int ite14524 = 0;
    if(x14467) {
      
      int x2388 = x2370._3;
      int x2389 = x2371._3;
      int x2390 = x2388==(-2147483648);
      int ite14759 = 0;
      if(x2390) {
        ite14759 = 1;
      } else {
        
        
        int x2391 = x2389==(-2147483648);
        int x14761 = x2391;
        ite14759 = x14761;
      };
      int x14530 = ite14759;
      int ite14766 = 0;
      if(x14530) {
        ite14766 = 1;
      } else {
        
        
        int x2393 = x2388==(x2389);
        int x14768 = x2393;
        ite14766 = x14768;
      };
      int x14532 = ite14766;
      int x14525 = x14532;
      ite14524 = x14525;
    } else {
      
      ite14524 = 0;
    };
    int x14469 = ite14524;
    int ite14537 = 0;
    if(x14469) {
      
      PString x2396 = x2370._4;
      PString x2397 = x2371._4;
      int x2398 = x2396.data_ == nullptr;
      int ite14782 = 0;
      if(x2398) {
        ite14782 = 1;
      } else {
        
        
        int x2399 = x2397.data_ == nullptr;
        int x14784 = x2399;
        ite14782 = x14784;
      };
      int x14543 = ite14782;
      int ite14789 = 0;
      if(x14543) {
        ite14789 = 1;
      } else {
        
        
        int x2401 = x2396==(x2397);
        int x14791 = x2401;
        ite14789 = x14791;
      };
      int x14545 = ite14789;
      int x14538 = x14545;
      ite14537 = x14538;
    } else {
      
      ite14537 = 0;
    };
    int x14471 = ite14537;
    int ite14550 = 0;
    if(x14471) {
      
      PString x2404 = x2370._5;
      PString x2405 = x2371._5;
      int x2406 = x2404.data_ == nullptr;
      int ite14805 = 0;
      if(x2406) {
        ite14805 = 1;
      } else {
        
        
        int x2407 = x2405.data_ == nullptr;
        int x14807 = x2407;
        ite14805 = x14807;
      };
      int x14556 = ite14805;
      int ite14812 = 0;
      if(x14556) {
        ite14812 = 1;
      } else {
        
        
        int x2409 = x2404==(x2405);
        int x14814 = x2409;
        ite14812 = x14814;
      };
      int x14558 = ite14812;
      int x14551 = x14558;
      ite14550 = x14551;
    } else {
      
      ite14550 = 0;
    };
    int x14473 = ite14550;
    int ite14563 = 0;
    if(x14473) {
      
      PString x2412 = x2370._6;
      PString x2413 = x2371._6;
      int x2414 = x2412.data_ == nullptr;
      int ite14828 = 0;
      if(x2414) {
        ite14828 = 1;
      } else {
        
        
        int x2415 = x2413.data_ == nullptr;
        int x14830 = x2415;
        ite14828 = x14830;
      };
      int x14569 = ite14828;
      int ite14835 = 0;
      if(x14569) {
        ite14835 = 1;
      } else {
        
        
        int x2417 = x2412==(x2413);
        int x14837 = x2417;
        ite14835 = x14837;
      };
      int x14571 = ite14835;
      int x14564 = x14571;
      ite14563 = x14564;
    } else {
      
      ite14563 = 0;
    };
    int x14475 = ite14563;
    int ite14576 = 0;
    if(x14475) {
      
      PString x2420 = x2370._7;
      PString x2421 = x2371._7;
      int x2422 = x2420.data_ == nullptr;
      int ite14851 = 0;
      if(x2422) {
        ite14851 = 1;
      } else {
        
        
        int x2423 = x2421.data_ == nullptr;
        int x14853 = x2423;
        ite14851 = x14853;
      };
      int x14582 = ite14851;
      int ite14858 = 0;
      if(x14582) {
        ite14858 = 1;
      } else {
        
        
        int x2425 = x2420==(x2421);
        int x14860 = x2425;
        ite14858 = x14860;
      };
      int x14584 = ite14858;
      int x14577 = x14584;
      ite14576 = x14577;
    } else {
      
      ite14576 = 0;
    };
    int x14477 = ite14576;
    int ite14589 = 0;
    if(x14477) {
      
      PString x2428 = x2370._8;
      PString x2429 = x2371._8;
      int x2430 = x2428.data_ == nullptr;
      int ite14874 = 0;
      if(x2430) {
        ite14874 = 1;
      } else {
        
        
        int x2431 = x2429.data_ == nullptr;
        int x14876 = x2431;
        ite14874 = x14876;
      };
      int x14595 = ite14874;
      int ite14881 = 0;
      if(x14595) {
        ite14881 = 1;
      } else {
        
        
        int x2433 = x2428==(x2429);
        int x14883 = x2433;
        ite14881 = x14883;
      };
      int x14597 = ite14881;
      int x14590 = x14597;
      ite14589 = x14590;
    } else {
      
      ite14589 = 0;
    };
    int x14479 = ite14589;
    int ite14602 = 0;
    if(x14479) {
      
      PString x2436 = x2370._9;
      PString x2437 = x2371._9;
      int x2438 = x2436.data_ == nullptr;
      int ite14897 = 0;
      if(x2438) {
        ite14897 = 1;
      } else {
        
        
        int x2439 = x2437.data_ == nullptr;
        int x14899 = x2439;
        ite14897 = x14899;
      };
      int x14608 = ite14897;
      int ite14904 = 0;
      if(x14608) {
        ite14904 = 1;
      } else {
        
        
        int x2441 = x2436==(x2437);
        int x14906 = x2441;
        ite14904 = x14906;
      };
      int x14610 = ite14904;
      int x14603 = x14610;
      ite14602 = x14603;
    } else {
      
      ite14602 = 0;
    };
    int x14481 = ite14602;
    int ite14615 = 0;
    if(x14481) {
      
      PString x2444 = x2370._10;
      PString x2445 = x2371._10;
      int x2446 = x2444.data_ == nullptr;
      int ite14920 = 0;
      if(x2446) {
        ite14920 = 1;
      } else {
        
        
        int x2447 = x2445.data_ == nullptr;
        int x14922 = x2447;
        ite14920 = x14922;
      };
      int x14621 = ite14920;
      int ite14927 = 0;
      if(x14621) {
        ite14927 = 1;
      } else {
        
        
        int x2449 = x2444==(x2445);
        int x14929 = x2449;
        ite14927 = x14929;
      };
      int x14623 = ite14927;
      int x14616 = x14623;
      ite14615 = x14616;
    } else {
      
      ite14615 = 0;
    };
    int x14483 = ite14615;
    int ite14628 = 0;
    if(x14483) {
      
      PString x2452 = x2370._11;
      PString x2453 = x2371._11;
      int x2454 = x2452.data_ == nullptr;
      int ite14943 = 0;
      if(x2454) {
        ite14943 = 1;
      } else {
        
        
        int x2455 = x2453.data_ == nullptr;
        int x14945 = x2455;
        ite14943 = x14945;
      };
      int x14634 = ite14943;
      int ite14950 = 0;
      if(x14634) {
        ite14950 = 1;
      } else {
        
        
        int x2457 = x2452==(x2453);
        int x14952 = x2457;
        ite14950 = x14952;
      };
      int x14636 = ite14950;
      int x14629 = x14636;
      ite14628 = x14629;
    } else {
      
      ite14628 = 0;
    };
    int x14485 = ite14628;
    int ite14641 = 0;
    if(x14485) {
      
      PString x2460 = x2370._12;
      PString x2461 = x2371._12;
      int x2462 = x2460.data_ == nullptr;
      int ite14966 = 0;
      if(x2462) {
        ite14966 = 1;
      } else {
        
        
        int x2463 = x2461.data_ == nullptr;
        int x14968 = x2463;
        ite14966 = x14968;
      };
      int x14647 = ite14966;
      int ite14973 = 0;
      if(x14647) {
        ite14973 = 1;
      } else {
        
        
        int x2465 = x2460==(x2461);
        int x14975 = x2465;
        ite14973 = x14975;
      };
      int x14649 = ite14973;
      int x14642 = x14649;
      ite14641 = x14642;
    } else {
      
      ite14641 = 0;
    };
    int x14487 = ite14641;
    int ite14654 = 0;
    if(x14487) {
      
      PString x2468 = x2370._13;
      PString x2469 = x2371._13;
      int x2470 = x2468.data_ == nullptr;
      int ite14989 = 0;
      if(x2470) {
        ite14989 = 1;
      } else {
        
        
        int x2471 = x2469.data_ == nullptr;
        int x14991 = x2471;
        ite14989 = x14991;
      };
      int x14660 = ite14989;
      int ite14996 = 0;
      if(x14660) {
        ite14996 = 1;
      } else {
        
        
        int x2473 = x2468==(x2469);
        int x14998 = x2473;
        ite14996 = x14998;
      };
      int x14662 = ite14996;
      int x14655 = x14662;
      ite14654 = x14655;
    } else {
      
      ite14654 = 0;
    };
    int x14489 = ite14654;
    int ite14667 = 0;
    if(x14489) {
      
      int x2476 = x2370._14;
      int x2477 = x2371._14;
      int x2478 = x2476==(-2147483648);
      int ite15012 = 0;
      if(x2478) {
        ite15012 = 1;
      } else {
        
        
        int x2479 = x2477==(-2147483648);
        int x15014 = x2479;
        ite15012 = x15014;
      };
      int x14673 = ite15012;
      int ite15019 = 0;
      if(x14673) {
        ite15019 = 1;
      } else {
        
        
        int x2481 = x2476==(x2477);
        int x15021 = x2481;
        ite15019 = x15021;
      };
      int x14675 = ite15019;
      int x14668 = x14675;
      ite14667 = x14668;
    } else {
      
      ite14667 = 0;
    };
    int x14491 = ite14667;
    int ite14680 = 0;
    if(x14491) {
      
      int x2484 = x2370._15;
      int x2485 = x2371._15;
      int x2486 = x2484==(-2147483648);
      int ite15035 = 0;
      if(x2486) {
        ite15035 = 1;
      } else {
        
        
        int x2487 = x2485==(-2147483648);
        int x15037 = x2487;
        ite15035 = x15037;
      };
      int x14686 = ite15035;
      int ite15042 = 0;
      if(x14686) {
        ite15042 = 1;
      } else {
        
        
        int x2489 = x2484==(x2485);
        int x15044 = x2489;
        ite15042 = x15044;
      };
      int x14688 = ite15042;
      int x14681 = x14688;
      ite14680 = x14681;
    } else {
      
      ite14680 = 0;
    };
    int x14493 = ite14680;
    int ite14693 = 0;
    if(x14493) {
      
      int x2492 = x2370._16;
      int x2493 = x2371._16;
      int x2494 = x2492==(-2147483648);
      int ite15058 = 0;
      if(x2494) {
        ite15058 = 1;
      } else {
        
        
        int x2495 = x2493==(-2147483648);
        int x15060 = x2495;
        ite15058 = x15060;
      };
      int x14699 = ite15058;
      int ite15065 = 0;
      if(x14699) {
        ite15065 = 1;
      } else {
        
        
        int x2497 = x2492==(x2493);
        int x15067 = x2497;
        ite15065 = x15067;
      };
      int x14701 = ite15065;
      int x14694 = x14701;
      ite14693 = x14694;
    } else {
      
      ite14693 = 0;
    };
    int x14495 = ite14693;
    int x2500 = x14495 ? 0 : 1;
    return x2500; 
  }
};
 struct SEntry5_IISDS_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x1620)  { 
    int x1621 = -889275714;
    int x1622 = x1620._1;
    int x1623 = HASH(x1622);
    int x1624 = -862048943*(x1623);
    int x1625 = x1624<<(15);
    int x1626 = x1624 >> (-15 & (8*sizeof(x1624)-1));
    int x1627 = x1625|(x1626);
    int x1628 = x1627*(461845907);
    int x1629 = x1621;
    int x1630 = x1628^(x1629);
    int x1631 = x1630<<(13);
    int x1632 = x1630 >> (-13 & (8*sizeof(x1630)-1));
    int x1633 = x1631|(x1632);
    int x1634 = x1633*(5);
    int x1635 = x1634+(-430675100);
    x1621 = x1635;
    int x1637 = x1621;
    int x1638 = x1637^(2);
    int x1639 = x1638 >> (16 & (8*sizeof(x1638)-1));
    int x1640 = x1638^(x1639);
    int x1641 = x1640*(-2048144789);
    int x1642 = x1641 >> (13 & (8*sizeof(x1641)-1));
    int x1643 = x1641^(x1642);
    int x1644 = x1643*(-1028477387);
    int x1645 = x1644 >> (16 & (8*sizeof(x1644)-1));
    int x1646 = x1644^(x1645);
    return x1646; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x1648, const struct SEntry5_IISDS& x1649) { 
    int ite15480 = 0;
    if(1) {
      
      int x1650 = x1648._1;
      int x1651 = x1649._1;
      int x1652 = x1650==(-2147483648);
      int ite15539 = 0;
      if(x1652) {
        ite15539 = 1;
      } else {
        
        
        int x1653 = x1651==(-2147483648);
        int x15541 = x1653;
        ite15539 = x15541;
      };
      int x15486 = ite15539;
      int ite15546 = 0;
      if(x15486) {
        ite15546 = 1;
      } else {
        
        
        int x1655 = x1650==(x1651);
        int x15548 = x1655;
        ite15546 = x15548;
      };
      int x15488 = ite15546;
      int x15481 = x15488;
      ite15480 = x15481;
    } else {
      
      ite15480 = 0;
    };
    int x15471 = ite15480;
    int ite15493 = 0;
    if(x15471) {
      
      int x1658 = x1648._2;
      int x1659 = x1649._2;
      int x1660 = x1658==(-2147483648);
      int ite15562 = 0;
      if(x1660) {
        ite15562 = 1;
      } else {
        
        
        int x1661 = x1659==(-2147483648);
        int x15564 = x1661;
        ite15562 = x15564;
      };
      int x15499 = ite15562;
      int ite15569 = 0;
      if(x15499) {
        ite15569 = 1;
      } else {
        
        
        int x1663 = x1658==(x1659);
        int x15571 = x1663;
        ite15569 = x15571;
      };
      int x15501 = ite15569;
      int x15494 = x15501;
      ite15493 = x15494;
    } else {
      
      ite15493 = 0;
    };
    int x15473 = ite15493;
    int ite15506 = 0;
    if(x15473) {
      
      PString x1666 = x1648._3;
      PString x1667 = x1649._3;
      int x1668 = x1666.data_ == nullptr;
      int ite15585 = 0;
      if(x1668) {
        ite15585 = 1;
      } else {
        
        
        int x1669 = x1667.data_ == nullptr;
        int x15587 = x1669;
        ite15585 = x15587;
      };
      int x15512 = ite15585;
      int ite15592 = 0;
      if(x15512) {
        ite15592 = 1;
      } else {
        
        
        int x1671 = x1666==(x1667);
        int x15594 = x1671;
        ite15592 = x15594;
      };
      int x15514 = ite15592;
      int x15507 = x15514;
      ite15506 = x15507;
    } else {
      
      ite15506 = 0;
    };
    int x15475 = ite15506;
    int ite15519 = 0;
    if(x15475) {
      
      double x1674 = x1648._4;
      double x1675 = x1649._4;
      int x1676 = x1674==(-1.7976931348623157E308);
      int ite15608 = 0;
      if(x1676) {
        ite15608 = 1;
      } else {
        
        
        int x1677 = x1675==(-1.7976931348623157E308);
        int x15610 = x1677;
        ite15608 = x15610;
      };
      int x15525 = ite15608;
      int ite15615 = 0;
      if(x15525) {
        ite15615 = 1;
      } else {
        
        
        int x1679 = x1674==(x1675);
        int x15617 = x1679;
        ite15615 = x15617;
      };
      int x15527 = ite15615;
      int x15520 = x15527;
      ite15519 = x15520;
    } else {
      
      ite15519 = 0;
    };
    int x15477 = ite15519;
    int x1682 = x15477 ? 0 : 1;
    return x1682; 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x1320)  { 
    int x1321 = -889275714;
    int x1322 = x1320._1;
    int x1323 = HASH(x1322);
    int x1324 = -862048943*(x1323);
    int x1325 = x1324<<(15);
    int x1326 = x1324 >> (-15 & (8*sizeof(x1324)-1));
    int x1327 = x1325|(x1326);
    int x1328 = x1327*(461845907);
    int x1329 = x1321;
    int x1330 = x1328^(x1329);
    int x1331 = x1330<<(13);
    int x1332 = x1330 >> (-13 & (8*sizeof(x1330)-1));
    int x1333 = x1331|(x1332);
    int x1334 = x1333*(5);
    int x1335 = x1334+(-430675100);
    x1321 = x1335;
    int x1337 = x1320._2;
    int x1338 = HASH(x1337);
    int x1339 = -862048943*(x1338);
    int x1340 = x1339<<(15);
    int x1341 = x1339 >> (-15 & (8*sizeof(x1339)-1));
    int x1342 = x1340|(x1341);
    int x1343 = x1342*(461845907);
    int x1344 = x1321;
    int x1345 = x1343^(x1344);
    int x1346 = x1345<<(13);
    int x1347 = x1345 >> (-13 & (8*sizeof(x1345)-1));
    int x1348 = x1346|(x1347);
    int x1349 = x1348*(5);
    int x1350 = x1349+(-430675100);
    x1321 = x1350;
    int x1352 = x1320._3;
    int x1353 = HASH(x1352);
    int x1354 = -862048943*(x1353);
    int x1355 = x1354<<(15);
    int x1356 = x1354 >> (-15 & (8*sizeof(x1354)-1));
    int x1357 = x1355|(x1356);
    int x1358 = x1357*(461845907);
    int x1359 = x1321;
    int x1360 = x1358^(x1359);
    int x1361 = x1360<<(13);
    int x1362 = x1360 >> (-13 & (8*sizeof(x1360)-1));
    int x1363 = x1361|(x1362);
    int x1364 = x1363*(5);
    int x1365 = x1364+(-430675100);
    x1321 = x1365;
    int x1367 = x1320._4;
    int x1368 = HASH(x1367);
    int x1369 = -862048943*(x1368);
    int x1370 = x1369<<(15);
    int x1371 = x1369 >> (-15 & (8*sizeof(x1369)-1));
    int x1372 = x1370|(x1371);
    int x1373 = x1372*(461845907);
    int x1374 = x1321;
    int x1375 = x1373^(x1374);
    int x1376 = x1375<<(13);
    int x1377 = x1375 >> (-13 & (8*sizeof(x1375)-1));
    int x1378 = x1376|(x1377);
    int x1379 = x1378*(5);
    int x1380 = x1379+(-430675100);
    x1321 = x1380;
    int x1382 = x1320._5;
    int x1383 = HASH(x1382);
    int x1384 = -862048943*(x1383);
    int x1385 = x1384<<(15);
    int x1386 = x1384 >> (-15 & (8*sizeof(x1384)-1));
    int x1387 = x1385|(x1386);
    int x1388 = x1387*(461845907);
    int x1389 = x1321;
    int x1390 = x1388^(x1389);
    int x1391 = x1390<<(13);
    int x1392 = x1390 >> (-13 & (8*sizeof(x1390)-1));
    int x1393 = x1391|(x1392);
    int x1394 = x1393*(5);
    int x1395 = x1394+(-430675100);
    x1321 = x1395;
    date x1397 = x1320._6;
    int x1398 = HASH(x1397);
    int x1399 = -862048943*(x1398);
    int x1400 = x1399<<(15);
    int x1401 = x1399 >> (-15 & (8*sizeof(x1399)-1));
    int x1402 = x1400|(x1401);
    int x1403 = x1402*(461845907);
    int x1404 = x1321;
    int x1405 = x1403^(x1404);
    int x1406 = x1405<<(13);
    int x1407 = x1405 >> (-13 & (8*sizeof(x1405)-1));
    int x1408 = x1406|(x1407);
    int x1409 = x1408*(5);
    int x1410 = x1409+(-430675100);
    x1321 = x1410;
    double x1412 = x1320._7;
    int x1413 = HASH(x1412);
    int x1414 = -862048943*(x1413);
    int x1415 = x1414<<(15);
    int x1416 = x1414 >> (-15 & (8*sizeof(x1414)-1));
    int x1417 = x1415|(x1416);
    int x1418 = x1417*(461845907);
    int x1419 = x1321;
    int x1420 = x1418^(x1419);
    int x1421 = x1420<<(13);
    int x1422 = x1420 >> (-13 & (8*sizeof(x1420)-1));
    int x1423 = x1421|(x1422);
    int x1424 = x1423*(5);
    int x1425 = x1424+(-430675100);
    x1321 = x1425;
    PString x1427 = x1320._8;
    int x1428 = HASH(x1427);
    int x1429 = -862048943*(x1428);
    int x1430 = x1429<<(15);
    int x1431 = x1429 >> (-15 & (8*sizeof(x1429)-1));
    int x1432 = x1430|(x1431);
    int x1433 = x1432*(461845907);
    int x1434 = x1321;
    int x1435 = x1433^(x1434);
    int x1436 = x1435<<(13);
    int x1437 = x1435 >> (-13 & (8*sizeof(x1435)-1));
    int x1438 = x1436|(x1437);
    int x1439 = x1438*(5);
    int x1440 = x1439+(-430675100);
    x1321 = x1440;
    int x1442 = x1321;
    int x1443 = x1442^(2);
    int x1444 = x1443 >> (16 & (8*sizeof(x1443)-1));
    int x1445 = x1443^(x1444);
    int x1446 = x1445*(-2048144789);
    int x1447 = x1446 >> (13 & (8*sizeof(x1446)-1));
    int x1448 = x1446^(x1447);
    int x1449 = x1448*(-1028477387);
    int x1450 = x1449 >> (16 & (8*sizeof(x1449)-1));
    int x1451 = x1449^(x1450);
    return x1451; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x1453, const struct SEntry8_IIIIITDS& x1454) { 
    int ite15865 = 0;
    if(1) {
      
      int x1455 = x1453._1;
      int x1456 = x1454._1;
      int x1457 = x1455==(-2147483648);
      int ite15963 = 0;
      if(x1457) {
        ite15963 = 1;
      } else {
        
        
        int x1458 = x1456==(-2147483648);
        int x15965 = x1458;
        ite15963 = x15965;
      };
      int x15871 = ite15963;
      int ite15970 = 0;
      if(x15871) {
        ite15970 = 1;
      } else {
        
        
        int x1460 = x1455==(x1456);
        int x15972 = x1460;
        ite15970 = x15972;
      };
      int x15873 = ite15970;
      int x15866 = x15873;
      ite15865 = x15866;
    } else {
      
      ite15865 = 0;
    };
    int x15850 = ite15865;
    int ite15878 = 0;
    if(x15850) {
      
      int x1463 = x1453._2;
      int x1464 = x1454._2;
      int x1465 = x1463==(-2147483648);
      int ite15986 = 0;
      if(x1465) {
        ite15986 = 1;
      } else {
        
        
        int x1466 = x1464==(-2147483648);
        int x15988 = x1466;
        ite15986 = x15988;
      };
      int x15884 = ite15986;
      int ite15993 = 0;
      if(x15884) {
        ite15993 = 1;
      } else {
        
        
        int x1468 = x1463==(x1464);
        int x15995 = x1468;
        ite15993 = x15995;
      };
      int x15886 = ite15993;
      int x15879 = x15886;
      ite15878 = x15879;
    } else {
      
      ite15878 = 0;
    };
    int x15852 = ite15878;
    int ite15891 = 0;
    if(x15852) {
      
      int x1471 = x1453._3;
      int x1472 = x1454._3;
      int x1473 = x1471==(-2147483648);
      int ite16009 = 0;
      if(x1473) {
        ite16009 = 1;
      } else {
        
        
        int x1474 = x1472==(-2147483648);
        int x16011 = x1474;
        ite16009 = x16011;
      };
      int x15897 = ite16009;
      int ite16016 = 0;
      if(x15897) {
        ite16016 = 1;
      } else {
        
        
        int x1476 = x1471==(x1472);
        int x16018 = x1476;
        ite16016 = x16018;
      };
      int x15899 = ite16016;
      int x15892 = x15899;
      ite15891 = x15892;
    } else {
      
      ite15891 = 0;
    };
    int x15854 = ite15891;
    int ite15904 = 0;
    if(x15854) {
      
      int x1479 = x1453._4;
      int x1480 = x1454._4;
      int x1481 = x1479==(-2147483648);
      int ite16032 = 0;
      if(x1481) {
        ite16032 = 1;
      } else {
        
        
        int x1482 = x1480==(-2147483648);
        int x16034 = x1482;
        ite16032 = x16034;
      };
      int x15910 = ite16032;
      int ite16039 = 0;
      if(x15910) {
        ite16039 = 1;
      } else {
        
        
        int x1484 = x1479==(x1480);
        int x16041 = x1484;
        ite16039 = x16041;
      };
      int x15912 = ite16039;
      int x15905 = x15912;
      ite15904 = x15905;
    } else {
      
      ite15904 = 0;
    };
    int x15856 = ite15904;
    int ite15917 = 0;
    if(x15856) {
      
      int x1487 = x1453._5;
      int x1488 = x1454._5;
      int x1489 = x1487==(-2147483648);
      int ite16055 = 0;
      if(x1489) {
        ite16055 = 1;
      } else {
        
        
        int x1490 = x1488==(-2147483648);
        int x16057 = x1490;
        ite16055 = x16057;
      };
      int x15923 = ite16055;
      int ite16062 = 0;
      if(x15923) {
        ite16062 = 1;
      } else {
        
        
        int x1492 = x1487==(x1488);
        int x16064 = x1492;
        ite16062 = x16064;
      };
      int x15925 = ite16062;
      int x15918 = x15925;
      ite15917 = x15918;
    } else {
      
      ite15917 = 0;
    };
    int x15858 = ite15917;
    int ite15930 = 0;
    if(x15858) {
      
      date x1495 = x1453._6;
      date x1496 = x1454._6;
      int x1497 = x1495==(0);
      int ite16078 = 0;
      if(x1497) {
        ite16078 = 1;
      } else {
        
        
        int x1498 = x1496==(0);
        int x16080 = x1498;
        ite16078 = x16080;
      };
      int x15936 = ite16078;
      int ite16085 = 0;
      if(x15936) {
        ite16085 = 1;
      } else {
        
        
        int x1500 = x1495==(x1496);
        int x16087 = x1500;
        ite16085 = x16087;
      };
      int x15938 = ite16085;
      int x15931 = x15938;
      ite15930 = x15931;
    } else {
      
      ite15930 = 0;
    };
    int x15860 = ite15930;
    int ite15943 = 0;
    if(x15860) {
      
      double x1503 = x1453._7;
      double x1504 = x1454._7;
      int x1505 = x1503==(-1.7976931348623157E308);
      int ite16101 = 0;
      if(x1505) {
        ite16101 = 1;
      } else {
        
        
        int x1506 = x1504==(-1.7976931348623157E308);
        int x16103 = x1506;
        ite16101 = x16103;
      };
      int x15949 = ite16101;
      int ite16108 = 0;
      if(x15949) {
        ite16108 = 1;
      } else {
        
        
        int x1508 = x1503==(x1504);
        int x16110 = x1508;
        ite16108 = x16110;
      };
      int x15951 = ite16108;
      int x15944 = x15951;
      ite15943 = x15944;
    } else {
      
      ite15943 = 0;
    };
    int x15862 = ite15943;
    int x1511 = x15862 ? 0 : 1;
    return x1511; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx12 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x1813)  { 
    int x1814 = -889275714;
    int x1815 = x1813._1;
    int x1816 = HASH(x1815);
    int x1817 = -862048943*(x1816);
    int x1818 = x1817<<(15);
    int x1819 = x1817 >> (-15 & (8*sizeof(x1817)-1));
    int x1820 = x1818|(x1819);
    int x1821 = x1820*(461845907);
    int x1822 = x1814;
    int x1823 = x1821^(x1822);
    int x1824 = x1823<<(13);
    int x1825 = x1823 >> (-13 & (8*sizeof(x1823)-1));
    int x1826 = x1824|(x1825);
    int x1827 = x1826*(5);
    int x1828 = x1827+(-430675100);
    x1814 = x1828;
    int x1830 = x1813._2;
    int x1831 = HASH(x1830);
    int x1832 = -862048943*(x1831);
    int x1833 = x1832<<(15);
    int x1834 = x1832 >> (-15 & (8*sizeof(x1832)-1));
    int x1835 = x1833|(x1834);
    int x1836 = x1835*(461845907);
    int x1837 = x1814;
    int x1838 = x1836^(x1837);
    int x1839 = x1838<<(13);
    int x1840 = x1838 >> (-13 & (8*sizeof(x1838)-1));
    int x1841 = x1839|(x1840);
    int x1842 = x1841*(5);
    int x1843 = x1842+(-430675100);
    x1814 = x1843;
    int x1845 = x1814;
    int x1846 = x1845^(2);
    int x1847 = x1846 >> (16 & (8*sizeof(x1846)-1));
    int x1848 = x1846^(x1847);
    int x1849 = x1848*(-2048144789);
    int x1850 = x1849 >> (13 & (8*sizeof(x1849)-1));
    int x1851 = x1849^(x1850);
    int x1852 = x1851*(-1028477387);
    int x1853 = x1852 >> (16 & (8*sizeof(x1852)-1));
    int x1854 = x1852^(x1853);
    return x1854; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x1856, const struct SEntry11_IISSSSSSDDI& x1857) { 
    int ite16343 = 0;
    if(1) {
      
      int x1858 = x1856._1;
      int x1859 = x1857._1;
      int x1860 = x1858==(-2147483648);
      int ite16480 = 0;
      if(x1860) {
        ite16480 = 1;
      } else {
        
        
        int x1861 = x1859==(-2147483648);
        int x16482 = x1861;
        ite16480 = x16482;
      };
      int x16349 = ite16480;
      int ite16487 = 0;
      if(x16349) {
        ite16487 = 1;
      } else {
        
        
        int x1863 = x1858==(x1859);
        int x16489 = x1863;
        ite16487 = x16489;
      };
      int x16351 = ite16487;
      int x16344 = x16351;
      ite16343 = x16344;
    } else {
      
      ite16343 = 0;
    };
    int x16322 = ite16343;
    int ite16356 = 0;
    if(x16322) {
      
      int x1866 = x1856._2;
      int x1867 = x1857._2;
      int x1868 = x1866==(-2147483648);
      int ite16503 = 0;
      if(x1868) {
        ite16503 = 1;
      } else {
        
        
        int x1869 = x1867==(-2147483648);
        int x16505 = x1869;
        ite16503 = x16505;
      };
      int x16362 = ite16503;
      int ite16510 = 0;
      if(x16362) {
        ite16510 = 1;
      } else {
        
        
        int x1871 = x1866==(x1867);
        int x16512 = x1871;
        ite16510 = x16512;
      };
      int x16364 = ite16510;
      int x16357 = x16364;
      ite16356 = x16357;
    } else {
      
      ite16356 = 0;
    };
    int x16324 = ite16356;
    int ite16369 = 0;
    if(x16324) {
      
      PString x1874 = x1856._3;
      PString x1875 = x1857._3;
      int x1876 = x1874.data_ == nullptr;
      int ite16526 = 0;
      if(x1876) {
        ite16526 = 1;
      } else {
        
        
        int x1877 = x1875.data_ == nullptr;
        int x16528 = x1877;
        ite16526 = x16528;
      };
      int x16375 = ite16526;
      int ite16533 = 0;
      if(x16375) {
        ite16533 = 1;
      } else {
        
        
        int x1879 = x1874==(x1875);
        int x16535 = x1879;
        ite16533 = x16535;
      };
      int x16377 = ite16533;
      int x16370 = x16377;
      ite16369 = x16370;
    } else {
      
      ite16369 = 0;
    };
    int x16326 = ite16369;
    int ite16382 = 0;
    if(x16326) {
      
      PString x1882 = x1856._4;
      PString x1883 = x1857._4;
      int x1884 = x1882.data_ == nullptr;
      int ite16549 = 0;
      if(x1884) {
        ite16549 = 1;
      } else {
        
        
        int x1885 = x1883.data_ == nullptr;
        int x16551 = x1885;
        ite16549 = x16551;
      };
      int x16388 = ite16549;
      int ite16556 = 0;
      if(x16388) {
        ite16556 = 1;
      } else {
        
        
        int x1887 = x1882==(x1883);
        int x16558 = x1887;
        ite16556 = x16558;
      };
      int x16390 = ite16556;
      int x16383 = x16390;
      ite16382 = x16383;
    } else {
      
      ite16382 = 0;
    };
    int x16328 = ite16382;
    int ite16395 = 0;
    if(x16328) {
      
      PString x1890 = x1856._5;
      PString x1891 = x1857._5;
      int x1892 = x1890.data_ == nullptr;
      int ite16572 = 0;
      if(x1892) {
        ite16572 = 1;
      } else {
        
        
        int x1893 = x1891.data_ == nullptr;
        int x16574 = x1893;
        ite16572 = x16574;
      };
      int x16401 = ite16572;
      int ite16579 = 0;
      if(x16401) {
        ite16579 = 1;
      } else {
        
        
        int x1895 = x1890==(x1891);
        int x16581 = x1895;
        ite16579 = x16581;
      };
      int x16403 = ite16579;
      int x16396 = x16403;
      ite16395 = x16396;
    } else {
      
      ite16395 = 0;
    };
    int x16330 = ite16395;
    int ite16408 = 0;
    if(x16330) {
      
      PString x1898 = x1856._6;
      PString x1899 = x1857._6;
      int x1900 = x1898.data_ == nullptr;
      int ite16595 = 0;
      if(x1900) {
        ite16595 = 1;
      } else {
        
        
        int x1901 = x1899.data_ == nullptr;
        int x16597 = x1901;
        ite16595 = x16597;
      };
      int x16414 = ite16595;
      int ite16602 = 0;
      if(x16414) {
        ite16602 = 1;
      } else {
        
        
        int x1903 = x1898==(x1899);
        int x16604 = x1903;
        ite16602 = x16604;
      };
      int x16416 = ite16602;
      int x16409 = x16416;
      ite16408 = x16409;
    } else {
      
      ite16408 = 0;
    };
    int x16332 = ite16408;
    int ite16421 = 0;
    if(x16332) {
      
      PString x1906 = x1856._7;
      PString x1907 = x1857._7;
      int x1908 = x1906.data_ == nullptr;
      int ite16618 = 0;
      if(x1908) {
        ite16618 = 1;
      } else {
        
        
        int x1909 = x1907.data_ == nullptr;
        int x16620 = x1909;
        ite16618 = x16620;
      };
      int x16427 = ite16618;
      int ite16625 = 0;
      if(x16427) {
        ite16625 = 1;
      } else {
        
        
        int x1911 = x1906==(x1907);
        int x16627 = x1911;
        ite16625 = x16627;
      };
      int x16429 = ite16625;
      int x16422 = x16429;
      ite16421 = x16422;
    } else {
      
      ite16421 = 0;
    };
    int x16334 = ite16421;
    int ite16434 = 0;
    if(x16334) {
      
      PString x1914 = x1856._8;
      PString x1915 = x1857._8;
      int x1916 = x1914.data_ == nullptr;
      int ite16641 = 0;
      if(x1916) {
        ite16641 = 1;
      } else {
        
        
        int x1917 = x1915.data_ == nullptr;
        int x16643 = x1917;
        ite16641 = x16643;
      };
      int x16440 = ite16641;
      int ite16648 = 0;
      if(x16440) {
        ite16648 = 1;
      } else {
        
        
        int x1919 = x1914==(x1915);
        int x16650 = x1919;
        ite16648 = x16650;
      };
      int x16442 = ite16648;
      int x16435 = x16442;
      ite16434 = x16435;
    } else {
      
      ite16434 = 0;
    };
    int x16336 = ite16434;
    int ite16447 = 0;
    if(x16336) {
      
      double x1922 = x1856._9;
      double x1923 = x1857._9;
      int x1924 = x1922==(-1.7976931348623157E308);
      int ite16664 = 0;
      if(x1924) {
        ite16664 = 1;
      } else {
        
        
        int x1925 = x1923==(-1.7976931348623157E308);
        int x16666 = x1925;
        ite16664 = x16666;
      };
      int x16453 = ite16664;
      int ite16671 = 0;
      if(x16453) {
        ite16671 = 1;
      } else {
        
        
        int x1927 = x1922==(x1923);
        int x16673 = x1927;
        ite16671 = x16673;
      };
      int x16455 = ite16671;
      int x16448 = x16455;
      ite16447 = x16448;
    } else {
      
      ite16447 = 0;
    };
    int x16338 = ite16447;
    int ite16460 = 0;
    if(x16338) {
      
      double x1930 = x1856._10;
      double x1931 = x1857._10;
      int x1932 = x1930==(-1.7976931348623157E308);
      int ite16687 = 0;
      if(x1932) {
        ite16687 = 1;
      } else {
        
        
        int x1933 = x1931==(-1.7976931348623157E308);
        int x16689 = x1933;
        ite16687 = x16689;
      };
      int x16466 = ite16687;
      int ite16694 = 0;
      if(x16466) {
        ite16694 = 1;
      } else {
        
        
        int x1935 = x1930==(x1931);
        int x16696 = x1935;
        ite16694 = x16696;
      };
      int x16468 = ite16694;
      int x16461 = x16468;
      ite16460 = x16461;
    } else {
      
      ite16460 = 0;
    };
    int x16340 = ite16460;
    int x1938 = x16340 ? 0 : 1;
    return x1938; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x1519)  { 
    int x1520 = -889275714;
    int x1521 = x1519._1;
    int x1522 = HASH(x1521);
    int x1523 = -862048943*(x1522);
    int x1524 = x1523<<(15);
    int x1525 = x1523 >> (-15 & (8*sizeof(x1523)-1));
    int x1526 = x1524|(x1525);
    int x1527 = x1526*(461845907);
    int x1528 = x1520;
    int x1529 = x1527^(x1528);
    int x1530 = x1529<<(13);
    int x1531 = x1529 >> (-13 & (8*sizeof(x1529)-1));
    int x1532 = x1530|(x1531);
    int x1533 = x1532*(5);
    int x1534 = x1533+(-430675100);
    x1520 = x1534;
    int x1536 = x1520;
    int x1537 = x1536^(2);
    int x1538 = x1537 >> (16 & (8*sizeof(x1537)-1));
    int x1539 = x1537^(x1538);
    int x1540 = x1539*(-2048144789);
    int x1541 = x1540 >> (13 & (8*sizeof(x1540)-1));
    int x1542 = x1540^(x1541);
    int x1543 = x1542*(-1028477387);
    int x1544 = x1543 >> (16 & (8*sizeof(x1543)-1));
    int x1545 = x1543^(x1544);
    return x1545; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x1547, const struct SEntry9_ISSSSSSDD& x1548) { 
    int ite16979 = 0;
    if(1) {
      
      int x1549 = x1547._1;
      int x1550 = x1548._1;
      int x1551 = x1549==(-2147483648);
      int ite17090 = 0;
      if(x1551) {
        ite17090 = 1;
      } else {
        
        
        int x1552 = x1550==(-2147483648);
        int x17092 = x1552;
        ite17090 = x17092;
      };
      int x16985 = ite17090;
      int ite17097 = 0;
      if(x16985) {
        ite17097 = 1;
      } else {
        
        
        int x1554 = x1549==(x1550);
        int x17099 = x1554;
        ite17097 = x17099;
      };
      int x16987 = ite17097;
      int x16980 = x16987;
      ite16979 = x16980;
    } else {
      
      ite16979 = 0;
    };
    int x16962 = ite16979;
    int ite16992 = 0;
    if(x16962) {
      
      PString x1557 = x1547._2;
      PString x1558 = x1548._2;
      int x1559 = x1557.data_ == nullptr;
      int ite17113 = 0;
      if(x1559) {
        ite17113 = 1;
      } else {
        
        
        int x1560 = x1558.data_ == nullptr;
        int x17115 = x1560;
        ite17113 = x17115;
      };
      int x16998 = ite17113;
      int ite17120 = 0;
      if(x16998) {
        ite17120 = 1;
      } else {
        
        
        int x1562 = x1557==(x1558);
        int x17122 = x1562;
        ite17120 = x17122;
      };
      int x17000 = ite17120;
      int x16993 = x17000;
      ite16992 = x16993;
    } else {
      
      ite16992 = 0;
    };
    int x16964 = ite16992;
    int ite17005 = 0;
    if(x16964) {
      
      PString x1565 = x1547._3;
      PString x1566 = x1548._3;
      int x1567 = x1565.data_ == nullptr;
      int ite17136 = 0;
      if(x1567) {
        ite17136 = 1;
      } else {
        
        
        int x1568 = x1566.data_ == nullptr;
        int x17138 = x1568;
        ite17136 = x17138;
      };
      int x17011 = ite17136;
      int ite17143 = 0;
      if(x17011) {
        ite17143 = 1;
      } else {
        
        
        int x1570 = x1565==(x1566);
        int x17145 = x1570;
        ite17143 = x17145;
      };
      int x17013 = ite17143;
      int x17006 = x17013;
      ite17005 = x17006;
    } else {
      
      ite17005 = 0;
    };
    int x16966 = ite17005;
    int ite17018 = 0;
    if(x16966) {
      
      PString x1573 = x1547._4;
      PString x1574 = x1548._4;
      int x1575 = x1573.data_ == nullptr;
      int ite17159 = 0;
      if(x1575) {
        ite17159 = 1;
      } else {
        
        
        int x1576 = x1574.data_ == nullptr;
        int x17161 = x1576;
        ite17159 = x17161;
      };
      int x17024 = ite17159;
      int ite17166 = 0;
      if(x17024) {
        ite17166 = 1;
      } else {
        
        
        int x1578 = x1573==(x1574);
        int x17168 = x1578;
        ite17166 = x17168;
      };
      int x17026 = ite17166;
      int x17019 = x17026;
      ite17018 = x17019;
    } else {
      
      ite17018 = 0;
    };
    int x16968 = ite17018;
    int ite17031 = 0;
    if(x16968) {
      
      PString x1581 = x1547._5;
      PString x1582 = x1548._5;
      int x1583 = x1581.data_ == nullptr;
      int ite17182 = 0;
      if(x1583) {
        ite17182 = 1;
      } else {
        
        
        int x1584 = x1582.data_ == nullptr;
        int x17184 = x1584;
        ite17182 = x17184;
      };
      int x17037 = ite17182;
      int ite17189 = 0;
      if(x17037) {
        ite17189 = 1;
      } else {
        
        
        int x1586 = x1581==(x1582);
        int x17191 = x1586;
        ite17189 = x17191;
      };
      int x17039 = ite17189;
      int x17032 = x17039;
      ite17031 = x17032;
    } else {
      
      ite17031 = 0;
    };
    int x16970 = ite17031;
    int ite17044 = 0;
    if(x16970) {
      
      PString x1589 = x1547._6;
      PString x1590 = x1548._6;
      int x1591 = x1589.data_ == nullptr;
      int ite17205 = 0;
      if(x1591) {
        ite17205 = 1;
      } else {
        
        
        int x1592 = x1590.data_ == nullptr;
        int x17207 = x1592;
        ite17205 = x17207;
      };
      int x17050 = ite17205;
      int ite17212 = 0;
      if(x17050) {
        ite17212 = 1;
      } else {
        
        
        int x1594 = x1589==(x1590);
        int x17214 = x1594;
        ite17212 = x17214;
      };
      int x17052 = ite17212;
      int x17045 = x17052;
      ite17044 = x17045;
    } else {
      
      ite17044 = 0;
    };
    int x16972 = ite17044;
    int ite17057 = 0;
    if(x16972) {
      
      PString x1597 = x1547._7;
      PString x1598 = x1548._7;
      int x1599 = x1597.data_ == nullptr;
      int ite17228 = 0;
      if(x1599) {
        ite17228 = 1;
      } else {
        
        
        int x1600 = x1598.data_ == nullptr;
        int x17230 = x1600;
        ite17228 = x17230;
      };
      int x17063 = ite17228;
      int ite17235 = 0;
      if(x17063) {
        ite17235 = 1;
      } else {
        
        
        int x1602 = x1597==(x1598);
        int x17237 = x1602;
        ite17235 = x17237;
      };
      int x17065 = ite17235;
      int x17058 = x17065;
      ite17057 = x17058;
    } else {
      
      ite17057 = 0;
    };
    int x16974 = ite17057;
    int ite17070 = 0;
    if(x16974) {
      
      double x1605 = x1547._8;
      double x1606 = x1548._8;
      int x1607 = x1605==(-1.7976931348623157E308);
      int ite17251 = 0;
      if(x1607) {
        ite17251 = 1;
      } else {
        
        
        int x1608 = x1606==(-1.7976931348623157E308);
        int x17253 = x1608;
        ite17251 = x17253;
      };
      int x17076 = ite17251;
      int ite17258 = 0;
      if(x17076) {
        ite17258 = 1;
      } else {
        
        
        int x1610 = x1605==(x1606);
        int x17260 = x1610;
        ite17258 = x17260;
      };
      int x17078 = ite17258;
      int x17071 = x17078;
      ite17070 = x17071;
    } else {
      
      ite17070 = 0;
    };
    int x16976 = ite17070;
    int x1613 = x16976 ? 0 : 1;
    return x1613; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x1689)  { 
    int x1690 = -889275714;
    int x1691 = x1689._1;
    int x1692 = HASH(x1691);
    int x1693 = -862048943*(x1692);
    int x1694 = x1693<<(15);
    int x1695 = x1693 >> (-15 & (8*sizeof(x1693)-1));
    int x1696 = x1694|(x1695);
    int x1697 = x1696*(461845907);
    int x1698 = x1690;
    int x1699 = x1697^(x1698);
    int x1700 = x1699<<(13);
    int x1701 = x1699 >> (-13 & (8*sizeof(x1699)-1));
    int x1702 = x1700|(x1701);
    int x1703 = x1702*(5);
    int x1704 = x1703+(-430675100);
    x1690 = x1704;
    int x1706 = x1689._2;
    int x1707 = HASH(x1706);
    int x1708 = -862048943*(x1707);
    int x1709 = x1708<<(15);
    int x1710 = x1708 >> (-15 & (8*sizeof(x1708)-1));
    int x1711 = x1709|(x1710);
    int x1712 = x1711*(461845907);
    int x1713 = x1690;
    int x1714 = x1712^(x1713);
    int x1715 = x1714<<(13);
    int x1716 = x1714 >> (-13 & (8*sizeof(x1714)-1));
    int x1717 = x1715|(x1716);
    int x1718 = x1717*(5);
    int x1719 = x1718+(-430675100);
    x1690 = x1719;
    int x1721 = x1689._3;
    int x1722 = HASH(x1721);
    int x1723 = -862048943*(x1722);
    int x1724 = x1723<<(15);
    int x1725 = x1723 >> (-15 & (8*sizeof(x1723)-1));
    int x1726 = x1724|(x1725);
    int x1727 = x1726*(461845907);
    int x1728 = x1690;
    int x1729 = x1727^(x1728);
    int x1730 = x1729<<(13);
    int x1731 = x1729 >> (-13 & (8*sizeof(x1729)-1));
    int x1732 = x1730|(x1731);
    int x1733 = x1732*(5);
    int x1734 = x1733+(-430675100);
    x1690 = x1734;
    int x1736 = x1690;
    int x1737 = x1736^(2);
    int x1738 = x1737 >> (16 & (8*sizeof(x1737)-1));
    int x1739 = x1737^(x1738);
    int x1740 = x1739*(-2048144789);
    int x1741 = x1740 >> (13 & (8*sizeof(x1740)-1));
    int x1742 = x1740^(x1741);
    int x1743 = x1742*(-1028477387);
    int x1744 = x1743 >> (16 & (8*sizeof(x1743)-1));
    int x1745 = x1743^(x1744);
    return x1745; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x1747, const struct SEntry8_IIIITIIB& x1748) { 
    int ite17525 = 0;
    if(1) {
      
      int x1749 = x1747._1;
      int x1750 = x1748._1;
      int x1751 = x1749==(-2147483648);
      int ite17623 = 0;
      if(x1751) {
        ite17623 = 1;
      } else {
        
        
        int x1752 = x1750==(-2147483648);
        int x17625 = x1752;
        ite17623 = x17625;
      };
      int x17531 = ite17623;
      int ite17630 = 0;
      if(x17531) {
        ite17630 = 1;
      } else {
        
        
        int x1754 = x1749==(x1750);
        int x17632 = x1754;
        ite17630 = x17632;
      };
      int x17533 = ite17630;
      int x17526 = x17533;
      ite17525 = x17526;
    } else {
      
      ite17525 = 0;
    };
    int x17510 = ite17525;
    int ite17538 = 0;
    if(x17510) {
      
      int x1757 = x1747._2;
      int x1758 = x1748._2;
      int x1759 = x1757==(-2147483648);
      int ite17646 = 0;
      if(x1759) {
        ite17646 = 1;
      } else {
        
        
        int x1760 = x1758==(-2147483648);
        int x17648 = x1760;
        ite17646 = x17648;
      };
      int x17544 = ite17646;
      int ite17653 = 0;
      if(x17544) {
        ite17653 = 1;
      } else {
        
        
        int x1762 = x1757==(x1758);
        int x17655 = x1762;
        ite17653 = x17655;
      };
      int x17546 = ite17653;
      int x17539 = x17546;
      ite17538 = x17539;
    } else {
      
      ite17538 = 0;
    };
    int x17512 = ite17538;
    int ite17551 = 0;
    if(x17512) {
      
      int x1765 = x1747._3;
      int x1766 = x1748._3;
      int x1767 = x1765==(-2147483648);
      int ite17669 = 0;
      if(x1767) {
        ite17669 = 1;
      } else {
        
        
        int x1768 = x1766==(-2147483648);
        int x17671 = x1768;
        ite17669 = x17671;
      };
      int x17557 = ite17669;
      int ite17676 = 0;
      if(x17557) {
        ite17676 = 1;
      } else {
        
        
        int x1770 = x1765==(x1766);
        int x17678 = x1770;
        ite17676 = x17678;
      };
      int x17559 = ite17676;
      int x17552 = x17559;
      ite17551 = x17552;
    } else {
      
      ite17551 = 0;
    };
    int x17514 = ite17551;
    int ite17564 = 0;
    if(x17514) {
      
      int x1773 = x1747._4;
      int x1774 = x1748._4;
      int x1775 = x1773==(-2147483648);
      int ite17692 = 0;
      if(x1775) {
        ite17692 = 1;
      } else {
        
        
        int x1776 = x1774==(-2147483648);
        int x17694 = x1776;
        ite17692 = x17694;
      };
      int x17570 = ite17692;
      int ite17699 = 0;
      if(x17570) {
        ite17699 = 1;
      } else {
        
        
        int x1778 = x1773==(x1774);
        int x17701 = x1778;
        ite17699 = x17701;
      };
      int x17572 = ite17699;
      int x17565 = x17572;
      ite17564 = x17565;
    } else {
      
      ite17564 = 0;
    };
    int x17516 = ite17564;
    int ite17577 = 0;
    if(x17516) {
      
      date x1781 = x1747._5;
      date x1782 = x1748._5;
      int x1783 = x1781==(0);
      int ite17715 = 0;
      if(x1783) {
        ite17715 = 1;
      } else {
        
        
        int x1784 = x1782==(0);
        int x17717 = x1784;
        ite17715 = x17717;
      };
      int x17583 = ite17715;
      int ite17722 = 0;
      if(x17583) {
        ite17722 = 1;
      } else {
        
        
        int x1786 = x1781==(x1782);
        int x17724 = x1786;
        ite17722 = x17724;
      };
      int x17585 = ite17722;
      int x17578 = x17585;
      ite17577 = x17578;
    } else {
      
      ite17577 = 0;
    };
    int x17518 = ite17577;
    int ite17590 = 0;
    if(x17518) {
      
      int x1789 = x1747._6;
      int x1790 = x1748._6;
      int x1791 = x1789==(-2147483648);
      int ite17738 = 0;
      if(x1791) {
        ite17738 = 1;
      } else {
        
        
        int x1792 = x1790==(-2147483648);
        int x17740 = x1792;
        ite17738 = x17740;
      };
      int x17596 = ite17738;
      int ite17745 = 0;
      if(x17596) {
        ite17745 = 1;
      } else {
        
        
        int x1794 = x1789==(x1790);
        int x17747 = x1794;
        ite17745 = x17747;
      };
      int x17598 = ite17745;
      int x17591 = x17598;
      ite17590 = x17591;
    } else {
      
      ite17590 = 0;
    };
    int x17520 = ite17590;
    int ite17603 = 0;
    if(x17520) {
      
      int x1797 = x1747._7;
      int x1798 = x1748._7;
      int x1799 = x1797==(-2147483648);
      int ite17761 = 0;
      if(x1799) {
        ite17761 = 1;
      } else {
        
        
        int x1800 = x1798==(-2147483648);
        int x17763 = x1800;
        ite17761 = x17763;
      };
      int x17609 = ite17761;
      int ite17768 = 0;
      if(x17609) {
        ite17768 = 1;
      } else {
        
        
        int x1802 = x1797==(x1798);
        int x17770 = x1802;
        ite17768 = x17770;
      };
      int x17611 = ite17768;
      int x17604 = x17611;
      ite17603 = x17604;
    } else {
      
      ite17603 = 0;
    };
    int x17522 = ite17603;
    int x1805 = x17522 ? 0 : 1;
    return x1805; 
  }
};

typedef ListIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 0> newOrderTblIdx0Type;
typedef MultiHashMap<struct SEntry3_III, char,
   ListIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x1318 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef ListIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   ListIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x1517 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ListIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 0> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ListIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 0>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x1619 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ListIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 0> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ListIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 0>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x1688 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef ListIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 0> orderTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   ListIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 0>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x1811 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ListIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 0> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ListIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 0>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x1944 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef ListIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 0> orderLineTblIdx0Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   ListIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x2099 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ListIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 0> customerTblIdx0Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ListIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x2326 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ListIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 0> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ListIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 0>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x2506 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    struct SEntry3_III* x3785result;
    MinAggregator<struct SEntry3_III, int> x3785(([&](struct SEntry3_III* e) {
      int x3837 = e->_1;
      return x3837; 
    }), &x3785result);
    int x27 = x18;
    struct SEntry3_III* x11192 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x11192, 0, 1 * sizeof(struct SEntry3_III));
    x11192->_1 = -2147483648; x11192->_2 = x27; x11192->_3 = x12;
    newOrderTbl.slice(0, x11192, x3785);
    struct SEntry3_III* x3790 = x3785result;
    if((x3790!=(NULL))) {
      int x3793 = x3790->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x3793;
      newOrderTbl.del(x3790);
      int x41 = x18;
      struct SEntry8_IIIITIIB* x11205 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
      memset(x11205, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
      x11205->_1 = x3793; x11205->_2 = x41; x11205->_3 = x12; x11205->_4 = -2147483648; x11205->_5 = 0; x11205->_6 = -2147483648; x11205->_7 = -2147483648; x11205->_8 = 0;
      struct SEntry8_IIIITIIB* x5998 = orderTbl.get(x11205, 0);
      int x3803 = x5998->_4;
      x5998->_6 = x13;
      orderTbl.update(x5998);
      double x51 = 0.0;
      int x53 = x18;
      struct SEntry10_IIIIIITIDS* x11222 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x11222, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x11222->_1 = x3793; x11222->_2 = x53; x11222->_3 = x12; x11222->_4 = -2147483648; x11222->_5 = -2147483648; x11222->_6 = -2147483648; x11222->_7 = 0; x11222->_8 = -2147483648; x11222->_9 = -1.7976931348623157E308; x11222->_10 = PString();
      orderLineTbl.slice(0, x11222, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
        orderLineEntry->_7 = x11;
        double x58 = x51;
        double x3864 = orderLineEntry->_9;
        x51 = (x58+(x3864));
        orderLineTbl.update(orderLineEntry);
      
      }));
      int x66 = x18;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11227 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      memset(x11227, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      x11227->_1 = x3803; x11227->_2 = x66; x11227->_3 = x12; x11227->_4 = PString(); x11227->_5 = PString(); x11227->_6 = PString(); x11227->_7 = PString(); x11227->_8 = PString(); x11227->_9 = PString(); x11227->_10 = PString(); x11227->_11 = PString(); x11227->_12 = PString(); x11227->_13 = 0; x11227->_14 = PString(); x11227->_15 = -1.7976931348623157E308; x11227->_16 = -1.7976931348623157E308; x11227->_17 = -1.7976931348623157E308; x11227->_18 = -1.7976931348623157E308; x11227->_19 = -2147483648; x11227->_20 = -2147483648; x11227->_21 = PString();
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6018 = customerTbl.get(x11227, 0);
      double x70 = x51;
      double x3817 = x6018->_17;
      x6018->_17 = (x3817+(x70));
      int x3820 = x6018->_20;
      x6018->_20 = (x3820+(1));
      customerTbl.update(x6018);
    } else {
      
      int x74 = x18;
      orderIDs[(x74-(1))] = 0;
    };
    int x78 = x18;
    x18 = (x78+(1));
  };
}
void StockLevelTx(int x82, date x83, int x84, int x85, int x86, int x87) {
  struct SEntry11_IISSSSSSDDI* x11245 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x11245, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x11245->_1 = x86; x11245->_2 = x85; x11245->_3 = PString(); x11245->_4 = PString(); x11245->_5 = PString(); x11245->_6 = PString(); x11245->_7 = PString(); x11245->_8 = PString(); x11245->_9 = -1.7976931348623157E308; x11245->_10 = -1.7976931348623157E308; x11245->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x6096 = districtTbl.get(x11245, 0);
  int x3954 = x6096->_11;
  int x97 = (x3954-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x101 = x97;
    if (!((x101<(x3954)))) break; 
    
    int x103 = x97;
    struct SEntry10_IIIIIITIDS* x11268 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
    memset(x11268, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
    x11268->_1 = x103; x11268->_2 = x86; x11268->_3 = x85; x11268->_4 = -2147483648; x11268->_5 = -2147483648; x11268->_6 = -2147483648; x11268->_7 = 0; x11268->_8 = -2147483648; x11268->_9 = -1.7976931348623157E308; x11268->_10 = PString();
    orderLineTbl.slice(0, x11268, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x3983 = orderLineEntry->_5;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11259 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x11259, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x11259->_1 = x3983; x11259->_2 = x85; x11259->_3 = -2147483648; x11259->_4 = PString(); x11259->_5 = PString(); x11259->_6 = PString(); x11259->_7 = PString(); x11259->_8 = PString(); x11259->_9 = PString(); x11259->_10 = PString(); x11259->_11 = PString(); x11259->_12 = PString(); x11259->_13 = PString(); x11259->_14 = -2147483648; x11259->_15 = -2147483648; x11259->_16 = -2147483648; x11259->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x6109 = stockTbl.get(x11259, 0);
      int x3987 = x6109->_3;
      if((x3987<(x87))) {
        unique_ol_i_id.insert(x3983);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite10390 = NULL;
  if((x131>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x10391;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11282 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11282, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11282->_1 = -2147483648; x11282->_2 = x130; x11282->_3 = x129; x11282->_4 = PString(); x11282->_5 = PString(); x11282->_6 = x133; x11282->_7 = PString(); x11282->_8 = PString(); x11282->_9 = PString(); x11282->_10 = PString(); x11282->_11 = PString(); x11282->_12 = PString(); x11282->_13 = 0; x11282->_14 = PString(); x11282->_15 = -1.7976931348623157E308; x11282->_16 = -1.7976931348623157E308; x11282->_17 = -1.7976931348623157E308; x11282->_18 = -1.7976931348623157E308; x11282->_19 = -2147483648; x11282->_20 = -2147483648; x11282->_21 = PString();
    customerTbl.slice(0, x11282, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x10391.push_back(custEntry);
    
    }));
    int x10397 = x10391.size();
    int x10399 = (x10397/(2));
    int x10407 = x10391.size();
    if(((x10407%(2))==(0))) {
      int x152 = x10399;
      x10399 = (x152-(1));
    };
    sort(x10391.begin(), x10391.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x4092 = c1->_4;
      PString x4093 = c2->_4;
      return ((strcmpi(x4092.data_, x4093.data_))<(0)); 
    }));
    int x10415 = x10399;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10416 = x10391[x10415];
    ite10390 = x10416;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11307 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11307, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11307->_1 = x132; x11307->_2 = x130; x11307->_3 = x129; x11307->_4 = PString(); x11307->_5 = PString(); x11307->_6 = PString(); x11307->_7 = PString(); x11307->_8 = PString(); x11307->_9 = PString(); x11307->_10 = PString(); x11307->_11 = PString(); x11307->_12 = PString(); x11307->_13 = 0; x11307->_14 = PString(); x11307->_15 = -1.7976931348623157E308; x11307->_16 = -1.7976931348623157E308; x11307->_17 = -1.7976931348623157E308; x11307->_18 = -1.7976931348623157E308; x11307->_19 = -2147483648; x11307->_20 = -2147483648; x11307->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10419 = customerTbl.get(x11307, 0);
    ite10390 = x10419;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x4029 = ite10390;
  int x4030 = x4029->_3;
  struct SEntry8_IIIITIIB* x4032result;
  MaxAggregator<struct SEntry8_IIIITIIB, int> x4032(([&](struct SEntry8_IIIITIIB* e) {
    int x4068 = e->_1;
    return x4068; 
  }), &x4032result);
  struct SEntry8_IIIITIIB* x11318 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
  memset(x11318, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
  x11318->_1 = -2147483648; x11318->_2 = x130; x11318->_3 = x129; x11318->_4 = x4030; x11318->_5 = 0; x11318->_6 = -2147483648; x11318->_7 = -2147483648; x11318->_8 = 0;
  orderTbl.slice(0, x11318, x4032);
  struct SEntry8_IIIITIIB* x4036 = x4032result;
  int x184 = 0;
  int x4038 = x4036->_1;
  x184 = x4038;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  struct SEntry9_ISSSSSSDD* x11326 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
  memset(x11326, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
  x11326->_1 = x191; x11326->_2 = PString(); x11326->_3 = PString(); x11326->_4 = PString(); x11326->_5 = PString(); x11326->_6 = PString(); x11326->_7 = PString(); x11326->_8 = -1.7976931348623157E308; x11326->_9 = -1.7976931348623157E308;
  struct SEntry9_ISSSSSSDD* x6244 = warehouseTbl.get(x11326, 0);
  double x4171 = x6244->_9;
  x6244->_9 = (x4171+(x198));
  warehouseTbl.update(x6244);
  struct SEntry11_IISSSSSSDDI* x11334 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x11334, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x11334->_1 = x192; x11334->_2 = x191; x11334->_3 = PString(); x11334->_4 = PString(); x11334->_5 = PString(); x11334->_6 = PString(); x11334->_7 = PString(); x11334->_8 = PString(); x11334->_9 = -1.7976931348623157E308; x11334->_10 = -1.7976931348623157E308; x11334->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x6251 = districtTbl.get(x11334, 0);
  double x4178 = x6251->_10;
  x6251->_10 = (x4178+(x198));
  districtTbl.update(x6251);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite10492 = NULL;
  if((x193>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x10493;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11349 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11349, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11349->_1 = -2147483648; x11349->_2 = x195; x11349->_3 = x194; x11349->_4 = PString(); x11349->_5 = PString(); x11349->_6 = x197; x11349->_7 = PString(); x11349->_8 = PString(); x11349->_9 = PString(); x11349->_10 = PString(); x11349->_11 = PString(); x11349->_12 = PString(); x11349->_13 = 0; x11349->_14 = PString(); x11349->_15 = -1.7976931348623157E308; x11349->_16 = -1.7976931348623157E308; x11349->_17 = -1.7976931348623157E308; x11349->_18 = -1.7976931348623157E308; x11349->_19 = -2147483648; x11349->_20 = -2147483648; x11349->_21 = PString();
    customerTbl.slice(0, x11349, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x10493.push_back(custEntry);
    
    }));
    int x10499 = x10493.size();
    int x10501 = (x10499/(2));
    int x10509 = x10493.size();
    if(((x10509%(2))==(0))) {
      int x230 = x10501;
      x10501 = (x230-(1));
    };
    sort(x10493.begin(), x10493.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x4299 = c1->_4;
      PString x4300 = c2->_4;
      return ((strcmpi(x4299.data_, x4300.data_))<(0)); 
    }));
    int x10517 = x10501;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10518 = x10493[x10517];
    ite10492 = x10518;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11374 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11374, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11374->_1 = x196; x11374->_2 = x195; x11374->_3 = x194; x11374->_4 = PString(); x11374->_5 = PString(); x11374->_6 = PString(); x11374->_7 = PString(); x11374->_8 = PString(); x11374->_9 = PString(); x11374->_10 = PString(); x11374->_11 = PString(); x11374->_12 = PString(); x11374->_13 = 0; x11374->_14 = PString(); x11374->_15 = -1.7976931348623157E308; x11374->_16 = -1.7976931348623157E308; x11374->_17 = -1.7976931348623157E308; x11374->_18 = -1.7976931348623157E308; x11374->_19 = -2147483648; x11374->_20 = -2147483648; x11374->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10521 = customerTbl.get(x11374, 0);
    ite10492 = x10521;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x4183 = ite10492;
  PString x4184 = x4183->_21;
  PString x4185 = x4183->_14;
  char* x11837 = strstr(x4185.data_, "BC");
  if((x11837!=(NULL))) {
    int x4188 = x4183->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x4188, x195, x194, x192, x191, x198, IntToStrdate(x189), x4184.data_);
    double x4191 = x4183->_17;
    x4183->_17 = (x4191+(x198));
    x4183->_21 = c_new_data;
  } else {
    
    double x4195 = x4183->_17;
    x4183->_17 = (x4195+(x198));
  };
  customerTbl.update(x4183);
  PString x4199 = x6244->_2;
  PString x4200 = x6251->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x4199.data_, x4200.data_);
  int x4203 = x4183->_1;
  struct SEntry8_IIIIITDS* x11400 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x11400, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x11400->_1 = x4203; x11400->_2 = x195; x11400->_3 = x194; x11400->_4 = x192; x11400->_5 = x191; x11400->_6 = x189; x11400->_7 = x198; x11400->_8 = h_data;
  historyTbl.add(x11400);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite10792 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x10793 = x301;
      ite10792 = x10793;
    } else {
      
      ite10792 = 0;
    };
    int x10622 = ite10792;
    if (!(x10622)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    struct SEntry5_IISDS* x11420 = (struct SEntry5_IISDS*)malloc(1 * sizeof(struct SEntry5_IISDS));
    memset(x11420, 0, 1 * sizeof(struct SEntry5_IISDS));
    x11420->_1 = x305; x11420->_2 = -2147483648; x11420->_3 = PString(); x11420->_4 = -1.7976931348623157E308; x11420->_5 = PString();
    struct SEntry5_IISDS* x6465 = itemTbl.get(x11420, 0);
    if((x6465==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x4428 = x6465->_3;
      x284[x312] = x4428;
      int x315 = x289;
      double x4431 = x6465->_4;
      x283[x315] = x4431;
      int x318 = x289;
      PString x4434 = x6465->_5;
      idata[x318] = x4434;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11441 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11441, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11441->_1 = x277; x11441->_2 = x276; x11441->_3 = x275; x11441->_4 = PString(); x11441->_5 = PString(); x11441->_6 = PString(); x11441->_7 = PString(); x11441->_8 = PString(); x11441->_9 = PString(); x11441->_10 = PString(); x11441->_11 = PString(); x11441->_12 = PString(); x11441->_13 = 0; x11441->_14 = PString(); x11441->_15 = -1.7976931348623157E308; x11441->_16 = -1.7976931348623157E308; x11441->_17 = -1.7976931348623157E308; x11441->_18 = -1.7976931348623157E308; x11441->_19 = -2147483648; x11441->_20 = -2147483648; x11441->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6486 = customerTbl.get(x11441, 0);
    struct SEntry9_ISSSSSSDD* x11445 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
    memset(x11445, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
    x11445->_1 = x275; x11445->_2 = PString(); x11445->_3 = PString(); x11445->_4 = PString(); x11445->_5 = PString(); x11445->_6 = PString(); x11445->_7 = PString(); x11445->_8 = -1.7976931348623157E308; x11445->_9 = -1.7976931348623157E308;
    struct SEntry9_ISSSSSSDD* x6489 = warehouseTbl.get(x11445, 0);
    struct SEntry11_IISSSSSSDDI* x11449 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
    memset(x11449, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
    x11449->_1 = x276; x11449->_2 = x275; x11449->_3 = PString(); x11449->_4 = PString(); x11449->_5 = PString(); x11449->_6 = PString(); x11449->_7 = PString(); x11449->_8 = PString(); x11449->_9 = -1.7976931348623157E308; x11449->_10 = -1.7976931348623157E308; x11449->_11 = -2147483648;
    struct SEntry11_IISSSSSSDDI* x6492 = districtTbl.get(x11449, 0);
    int x4451 = x6492->_11;
    int x4452 = x6492->_11;
    x6492->_11 = (x4452+(1));
    districtTbl.update(x6492);
    struct SEntry8_IIIITIIB* x11459 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x11459, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x11459->_1 = x4451; x11459->_2 = x276; x11459->_3 = x275; x11459->_4 = x277; x11459->_5 = x273; x11459->_6 = -1; x11459->_7 = x278; x11459->_8 = (x279>(0));
    orderTbl.add(x11459);
    struct SEntry3_III* x11463 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x11463, 0, 1 * sizeof(struct SEntry3_III));
    x11463->_1 = x4451; x11463->_2 = x276; x11463->_3 = x275;
    newOrderTbl.add(x11463);
    double x352 = 0.0;
    x289 = 0;
    while(1) {
      
      int x355 = x289;
      if (!((x355<(x278)))) break; 
      
      int x358 = x289;
      int ol_supply_w_id = x281[x358];
      int x361 = x289;
      int ol_i_id = x280[x361];
      int x364 = x289;
      int ol_quantity = x282[x364];
      struct SEntry17_IIISSSSSSSSSSIIIS* x11478 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x11478, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x11478->_1 = ol_i_id; x11478->_2 = ol_supply_w_id; x11478->_3 = -2147483648; x11478->_4 = PString(); x11478->_5 = PString(); x11478->_6 = PString(); x11478->_7 = PString(); x11478->_8 = PString(); x11478->_9 = PString(); x11478->_10 = PString(); x11478->_11 = PString(); x11478->_12 = PString(); x11478->_13 = PString(); x11478->_14 = -2147483648; x11478->_15 = -2147483648; x11478->_16 = -2147483648; x11478->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x6518 = stockTbl.get(x11478, 0);
      PString ite10675 = PString();
      if((x276==(1))) {
        PString x10676 = x6518->_4;
        ite10675 = x10676;
      } else {
        
        PString ite10680 = PString();
        if((x276==(2))) {
          PString x10681 = x6518->_5;
          ite10680 = x10681;
        } else {
          
          PString ite10685 = PString();
          if((x276==(3))) {
            PString x10686 = x6518->_6;
            ite10685 = x10686;
          } else {
            
            PString ite10690 = PString();
            if((x276==(4))) {
              PString x10691 = x6518->_7;
              ite10690 = x10691;
            } else {
              
              PString ite10695 = PString();
              if((x276==(5))) {
                PString x10696 = x6518->_8;
                ite10695 = x10696;
              } else {
                
                PString ite10700 = PString();
                if((x276==(6))) {
                  PString x10701 = x6518->_9;
                  ite10700 = x10701;
                } else {
                  
                  PString ite10705 = PString();
                  if((x276==(7))) {
                    PString x10706 = x6518->_10;
                    ite10705 = x10706;
                  } else {
                    
                    PString ite10710 = PString();
                    if((x276==(8))) {
                      PString x10711 = x6518->_11;
                      ite10710 = x10711;
                    } else {
                      
                      PString ite10715 = PString();
                      if((x276==(9))) {
                        PString x10716 = x6518->_12;
                        ite10715 = x10716;
                      } else {
                        
                        PString x10718 = x6518->_13;
                        ite10715 = x10718;
                      };
                      PString x10714 = ite10715;
                      ite10710 = x10714;
                    };
                    PString x10709 = ite10710;
                    ite10705 = x10709;
                  };
                  PString x10704 = ite10705;
                  ite10700 = x10704;
                };
                PString x10699 = ite10700;
                ite10695 = x10699;
              };
              PString x10694 = ite10695;
              ite10690 = x10694;
            };
            PString x10689 = ite10690;
            ite10685 = x10689;
          };
          PString x10684 = ite10685;
          ite10680 = x10684;
        };
        PString x10679 = ite10680;
        ite10675 = x10679;
      };
      PString ol_dist_info = ite10675;
      int x4505 = x6518->_3;
      int x401 = x289;
      x285[x401] = x4505;
      PString x4508 = x6486->_14;
      char* x12085 = strstr(x4508.data_, "original");
      int ite10918 = 0;
      if((x12085!=(NULL))) {
        
        PString x4511 = x6518->_17;
        char* x12091 = strstr(x4511.data_, "original");
        int x10919 = (x12091!=(NULL));
        ite10918 = x10919;
      } else {
        
        ite10918 = 0;
      };
      int x10743 = ite10918;
      if(x10743) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      x6518->_3 = (x4505-(ol_quantity));
      if((x4505<=(ol_quantity))) {
        int x4522 = x6518->_3;
        x6518->_3 = (x4522+(91));
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      stockTbl.update(x6518);
      double x4530 = x6486->_16;
      double x4531 = x6489->_8;
      double x4532 = x6492->_9;
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(x4531))+(x4532))))*((1.0-(x4530)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      struct SEntry10_IIIIIITIDS* x11594 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x11594, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x11594->_1 = x4451; x11594->_2 = x276; x11594->_3 = x275; x11594->_4 = (x446+(1)); x11594->_5 = ol_i_id; x11594->_6 = ol_supply_w_id; x11594->_7 = NULL; x11594->_8 = ol_quantity; x11594->_9 = ol_amount; x11594->_10 = ol_dist_info;
      orderLineTbl.add(x11594);
      int x451 = x289;
      x289 = (x451+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  TPCCDataGen tpcc;
  tpcc.loadPrograms();
  tpcc.loadWare();
  tpcc.loadDist();
  tpcc.loadCust();
  tpcc.loadItem();
  tpcc.loadNewOrd();
  tpcc.loadOrders();
  tpcc.loadOrdLine();
  tpcc.loadHist();
  tpcc.loadStocks();
  
  for(size_t i = 0; i < numPrograms; ++i){
    Program *prg = tpcc.programs[i];
    switch(prg->id){
       case NEWORDER :
        {
           NewOrder& p = *(NewOrder *)prg;
           NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
           break;
        }
      case PAYMENTBYID :
        {
           PaymentById& p = *(PaymentById *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
           break;
        }
      case PAYMENTBYNAME :
        {
           PaymentByName& p = *(PaymentByName *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
           break;
        }
      case ORDERSTATUSBYID :
        {
           OrderStatusById &p = *(OrderStatusById *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
           break;
        }
      case ORDERSTATUSBYNAME :
        {
           OrderStatusByName &p = *(OrderStatusByName *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
           break;
        }
      case DELIVERY :
        {
           Delivery &p = *(Delivery *) prg;
           DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
           break;
        }
      case STOCKLEVEL :
       {
         StockLevel &p = *(StockLevel *) prg;
         StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         break;
       }
       default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
  
    }
  }
  
  #ifdef VERIFY_TPCC
      if (warehouseTblPrimaryIdx == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (districtTblPrimaryIdx == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (customerTblPrimaryIdx == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orderTblPrimaryIdx == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orderLineTblPrimaryIdx == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (newOrderTblPrimaryIdx == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (itemTblPrimaryIdx == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (stockTblPrimaryIdx == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (historyTblPrimaryIdx == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
