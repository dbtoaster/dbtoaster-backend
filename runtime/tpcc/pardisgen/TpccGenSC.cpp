#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY false

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
#include <iomanip>
#include <fstream>
#include <locale>

#include "ExecutionProfiler.h"

using namespace std;
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "program_base.hpp"

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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4017)  { 
    int x4018 = 0;
    int x4019 = x4018;
    int x4020 = x4017._1;
    x4018 = (x4019^(((((HASH(x4020))+(-1640531527))+((x4019<<(6))))+((x4019>>(2))))));
    int x4029 = x4018;
    int x4030 = x4017._2;
    x4018 = (x4029^(((((HASH(x4030))+(-1640531527))+((x4029<<(6))))+((x4029>>(2))))));
    int x4039 = x4018;
    int x4040 = x4017._3;
    x4018 = (x4039^(((((HASH(x4040))+(-1640531527))+((x4039<<(6))))+((x4039>>(2))))));
    int x4049 = x4018;
    int x4050 = x4017._4;
    x4018 = (x4049^(((((HASH(x4050))+(-1640531527))+((x4049<<(6))))+((x4049>>(2))))));
    int x4059 = x4018;
    return x4059; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4061, const struct SEntry10_IIIIIITIDS& x4062) { 
    int x4063 = 0;
    int x4064 = x4061._1;
    int x4065 = x4062._1;
    if((x4064==(x4065))) {
      int x4067 = x4061._2;
      int x4068 = x4062._2;
      if((x4067==(x4068))) {
        int x4070 = x4061._3;
        int x4071 = x4062._3;
        if((x4070==(x4071))) {
          int x4073 = x4061._4;
          int x4074 = x4062._4;
          if((x4073==(x4074))) {
            x4063 = 0;
          } else {
            
            x4063 = 1;
          };
        } else {
          
          x4063 = 1;
        };
      } else {
        
        x4063 = 1;
      };
    } else {
      
      x4063 = 1;
    };
    int x4085 = x4063;
    return x4085; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3929)  { 
    int x3930 = 0;
    int x3931 = x3930;
    int x3932 = x3929._2;
    x3930 = (x3931^(((((HASH(x3932))+(-1640531527))+((x3931<<(6))))+((x3931>>(2))))));
    int x3941 = x3930;
    int x3942 = x3929._3;
    x3930 = (x3941^(((((HASH(x3942))+(-1640531527))+((x3941<<(6))))+((x3941>>(2))))));
    int x3951 = x3930;
    int x3952 = x3929._4;
    x3930 = (x3951^(((((HASH(x3952))+(-1640531527))+((x3951<<(6))))+((x3951>>(2))))));
    int x3961 = x3930;
    return x3961; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3963, const struct SEntry8_IIIITIIB& x3964) { 
    int x3965 = 0;
    int x3966 = x3963._2;
    int x3967 = x3964._2;
    if((x3966==(x3967))) {
      int x3969 = x3963._3;
      int x3970 = x3964._3;
      if((x3969==(x3970))) {
        int x3972 = x3963._4;
        int x3973 = x3964._4;
        if((x3972==(x3973))) {
          x3965 = 0;
        } else {
          
          x3965 = 1;
        };
      } else {
        
        x3965 = 1;
      };
    } else {
      
      x3965 = 1;
    };
    int x3982 = x3965;
    return x3982; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3514)  { 
    int x3515 = 0;
    int x3516 = x3515;
    int x3517 = x3514._1;
    x3515 = (x3516^(((((HASH(x3517))+(-1640531527))+((x3516<<(6))))+((x3516>>(2))))));
    int x3526 = x3515;
    int x3527 = x3514._2;
    x3515 = (x3526^(((((HASH(x3527))+(-1640531527))+((x3526<<(6))))+((x3526>>(2))))));
    int x3536 = x3515;
    int x3537 = x3514._3;
    x3515 = (x3536^(((((HASH(x3537))+(-1640531527))+((x3536<<(6))))+((x3536>>(2))))));
    int x3546 = x3515;
    return x3546; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3548, const struct SEntry3_III& x3549) { 
    int x3550 = 0;
    int x3551 = x3548._1;
    int x3552 = x3549._1;
    if((x3551==(x3552))) {
      int x3554 = x3548._2;
      int x3555 = x3549._2;
      if((x3554==(x3555))) {
        int x3557 = x3548._3;
        int x3558 = x3549._3;
        if((x3557==(x3558))) {
          x3550 = 0;
        } else {
          
          x3550 = 1;
        };
      } else {
        
        x3550 = 1;
      };
    } else {
      
      x3550 = 1;
    };
    int x3567 = x3550;
    return x3567; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3652)  { 
    int x3653 = 0;
    int x3654 = x3653;
    int x3655 = x3652._1;
    x3653 = (x3654^(((((HASH(x3655))+(-1640531527))+((x3654<<(6))))+((x3654>>(2))))));
    int x3664 = x3653;
    int x3665 = x3652._2;
    x3653 = (x3664^(((((HASH(x3665))+(-1640531527))+((x3664<<(6))))+((x3664>>(2))))));
    int x3674 = x3653;
    int x3675 = x3652._3;
    x3653 = (x3674^(((((HASH(x3675))+(-1640531527))+((x3674<<(6))))+((x3674>>(2))))));
    int x3684 = x3653;
    int x3685 = x3652._4;
    x3653 = (x3684^(((((HASH(x3685))+(-1640531527))+((x3684<<(6))))+((x3684>>(2))))));
    int x3694 = x3653;
    int x3695 = x3652._5;
    x3653 = (x3694^(((((HASH(x3695))+(-1640531527))+((x3694<<(6))))+((x3694>>(2))))));
    int x3704 = x3653;
    date x3705 = x3652._6;
    x3653 = (x3704^(((((HASH(x3705))+(-1640531527))+((x3704<<(6))))+((x3704>>(2))))));
    int x3714 = x3653;
    double x3715 = x3652._7;
    x3653 = (x3714^(((((HASH(x3715))+(-1640531527))+((x3714<<(6))))+((x3714>>(2))))));
    int x3724 = x3653;
    const PString& x3725 = x3652._8;
    x3653 = (x3724^(((((HASH(x3725))+(-1640531527))+((x3724<<(6))))+((x3724>>(2))))));
    int x3734 = x3653;
    return x3734; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3736, const struct SEntry8_IIIIITDS& x3737) { 
    int x3738 = 0;
    int x3739 = x3736._1;
    int x3740 = x3737._1;
    if((x3739==(x3740))) {
      int x3742 = x3736._2;
      int x3743 = x3737._2;
      if((x3742==(x3743))) {
        int x3745 = x3736._3;
        int x3746 = x3737._3;
        if((x3745==(x3746))) {
          int x3748 = x3736._4;
          int x3749 = x3737._4;
          if((x3748==(x3749))) {
            int x3751 = x3736._5;
            int x3752 = x3737._5;
            if((x3751==(x3752))) {
              date x3754 = x3736._6;
              date x3755 = x3737._6;
              if((x3754==(x3755))) {
                double x3757 = x3736._7;
                double x3758 = x3737._7;
                if((x3757==(x3758))) {
                  const PString& x3760 = x3736._8;
                  const PString& x3761 = x3737._8;
                  if((x3760==(x3761))) {
                    x3738 = 0;
                  } else {
                    
                    x3738 = 1;
                  };
                } else {
                  
                  x3738 = 1;
                };
              } else {
                
                x3738 = 1;
              };
            } else {
              
              x3738 = 1;
            };
          } else {
            
            x3738 = 1;
          };
        } else {
          
          x3738 = 1;
        };
      } else {
        
        x3738 = 1;
      };
    } else {
      
      x3738 = 1;
    };
    int x3780 = x3738;
    return x3780; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4088)  { 
    int x4089 = 0;
    int x4090 = x4089;
    int x4091 = x4088._1;
    x4089 = (x4090^(((((HASH(x4091))+(-1640531527))+((x4090<<(6))))+((x4090>>(2))))));
    int x4100 = x4089;
    int x4101 = x4088._2;
    x4089 = (x4100^(((((HASH(x4101))+(-1640531527))+((x4100<<(6))))+((x4100>>(2))))));
    int x4110 = x4089;
    int x4111 = x4088._3;
    x4089 = (x4110^(((((HASH(x4111))+(-1640531527))+((x4110<<(6))))+((x4110>>(2))))));
    int x4120 = x4089;
    return x4120; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4122, const struct SEntry10_IIIIIITIDS& x4123) { 
    int x4124 = 0;
    int x4125 = x4122._1;
    int x4126 = x4123._1;
    if((x4125==(x4126))) {
      int x4128 = x4122._2;
      int x4129 = x4123._2;
      if((x4128==(x4129))) {
        int x4131 = x4122._3;
        int x4132 = x4123._3;
        if((x4131==(x4132))) {
          x4124 = 0;
        } else {
          
          x4124 = 1;
        };
      } else {
        
        x4124 = 1;
      };
    } else {
      
      x4124 = 1;
    };
    int x4141 = x4124;
    return x4141; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3604)  { 
    int x3605 = 0;
    int x3606 = x3605;
    int x3607 = x3604._2;
    x3605 = (x3606^(((((HASH(x3607))+(-1640531527))+((x3606<<(6))))+((x3606>>(2))))));
    int x3616 = x3605;
    int x3617 = x3604._3;
    x3605 = (x3616^(((((HASH(x3617))+(-1640531527))+((x3616<<(6))))+((x3616>>(2))))));
    int x3626 = x3605;
    return x3626; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3628, const struct SEntry3_III& x3629) { 
    int x3630 = 0;
    int x3631 = x3628._2;
    int x3632 = x3629._2;
    if((x3631==(x3632))) {
      int x3634 = x3628._3;
      int x3635 = x3629._3;
      if((x3634==(x3635))) {
        x3630 = 0;
      } else {
        
        x3630 = 1;
      };
    } else {
      
      x3630 = 1;
    };
    int x3642 = x3630;
    return x3642; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4176)  { 
    int x4177 = 0;
    int x4178 = x4177;
    int x4179 = x4176._2;
    x4177 = (x4178^(((((HASH(x4179))+(-1640531527))+((x4178<<(6))))+((x4178>>(2))))));
    int x4188 = x4177;
    int x4189 = x4176._3;
    x4177 = (x4188^(((((HASH(x4189))+(-1640531527))+((x4188<<(6))))+((x4188>>(2))))));
    int x4198 = x4177;
    const PString& x4199 = x4176._6;
    x4177 = (x4198^(((((HASH(x4199))+(-1640531527))+((x4198<<(6))))+((x4198>>(2))))));
    int x4208 = x4177;
    return x4208; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4210, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4211) { 
    int x4212 = 0;
    int x4213 = x4210._2;
    int x4214 = x4211._2;
    if((x4213==(x4214))) {
      int x4216 = x4210._3;
      int x4217 = x4211._3;
      if((x4216==(x4217))) {
        const PString& x4219 = x4210._6;
        const PString& x4220 = x4211._6;
        if((x4219==(x4220))) {
          x4212 = 0;
        } else {
          
          x4212 = 1;
        };
      } else {
        
        x4212 = 1;
      };
    } else {
      
      x4212 = 1;
    };
    int x4229 = x4212;
    return x4229; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3829)  { 
    int x3830 = 0;
    int x3831 = x3830;
    int x3832 = x3829._1;
    x3830 = (x3831^(((((HASH(x3832))+(-1640531527))+((x3831<<(6))))+((x3831>>(2))))));
    int x3841 = x3830;
    int x3842 = x3829._2;
    x3830 = (x3841^(((((HASH(x3842))+(-1640531527))+((x3841<<(6))))+((x3841>>(2))))));
    int x3851 = x3830;
    int x3852 = x3829._3;
    x3830 = (x3851^(((((HASH(x3852))+(-1640531527))+((x3851<<(6))))+((x3851>>(2))))));
    int x3861 = x3830;
    return x3861; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3863, const struct SEntry8_IIIITIIB& x3864) { 
    int x3865 = 0;
    int x3866 = x3863._1;
    int x3867 = x3864._1;
    if((x3866==(x3867))) {
      int x3869 = x3863._2;
      int x3870 = x3864._2;
      if((x3869==(x3870))) {
        int x3872 = x3863._3;
        int x3873 = x3864._3;
        if((x3872==(x3873))) {
          x3865 = 0;
        } else {
          
          x3865 = 1;
        };
      } else {
        
        x3865 = 1;
      };
    } else {
      
      x3865 = 1;
    };
    int x3882 = x3865;
    return x3882; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3570)  { 
    int x3571 = 0;
    int x3572 = x3571;
    int x3573 = x3570._2;
    x3571 = (x3572^(((((HASH(x3573))+(-1640531527))+((x3572<<(6))))+((x3572>>(2))))));
    int x3582 = x3571;
    int x3583 = x3570._3;
    x3571 = (x3582^(((((HASH(x3583))+(-1640531527))+((x3582<<(6))))+((x3582>>(2))))));
    int x3592 = x3571;
    return x3592; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3594, const struct SEntry3_III& x3595) { 
    int x3596 = x3594._1;
    int x3597 = x3595._1;
    return ((x3596==(x3597)) ? 0 : ((x3596>(x3597)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3885)  { 
    int x3886 = 0;
    int x3887 = x3886;
    int x3888 = x3885._2;
    x3886 = (x3887^(((((HASH(x3888))+(-1640531527))+((x3887<<(6))))+((x3887>>(2))))));
    int x3897 = x3886;
    int x3898 = x3885._3;
    x3886 = (x3897^(((((HASH(x3898))+(-1640531527))+((x3897<<(6))))+((x3897>>(2))))));
    int x3907 = x3886;
    int x3908 = x3885._4;
    x3886 = (x3907^(((((HASH(x3908))+(-1640531527))+((x3907<<(6))))+((x3907>>(2))))));
    int x3917 = x3886;
    return x3917; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3919, const struct SEntry8_IIIITIIB& x3920) { 
    int x3921 = x3919._1;
    int x3922 = x3920._1;
    return ((x3921==(x3922)) ? 0 : ((x3921>(x3922)) ? 1 : -1)); 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4241)  { 
    int x4242 = 0;
    int x4243 = x4241._1;
    int x4245 = x4242;
    x4242 = ((x4245*(100000))+((x4243-(1))));
    int x4249 = x4241._2;
    int x4251 = x4242;
    x4242 = ((x4251*(1))+((x4249-(1))));
    int x4255 = x4242;
    return x4255; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4238, const struct SEntry17_IIISSSSSSSSSSIIIS& x4239) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4153)  { 
    int x4154 = 0;
    int x4155 = x4153._1;
    int x4157 = x4154;
    x4154 = ((x4157*(3000))+((x4155-(1))));
    int x4161 = x4153._2;
    int x4163 = x4154;
    x4154 = ((x4163*(10))+((x4161-(1))));
    int x4167 = x4153._3;
    int x4169 = x4154;
    x4154 = ((x4169*(1))+((x4167-(1))));
    int x4173 = x4154;
    return x4173; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4150, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4151) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3810)  { 
    int x3811 = 0;
    int x3812 = x3810._1;
    int x3814 = x3811;
    x3811 = ((x3814*(100000))+((x3812-(1))));
    int x3818 = x3811;
    return x3818; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3807, const struct SEntry5_IISDS& x3808) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3791)  { 
    int x3792 = 0;
    int x3793 = x3791._1;
    int x3795 = x3792;
    x3792 = ((x3795*(1))+((x3793-(1))));
    int x3799 = x3792;
    return x3799; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3788, const struct SEntry9_ISSSSSSDD& x3789) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3995)  { 
    int x3996 = 0;
    int x3997 = x3995._1;
    int x3999 = x3996;
    x3996 = ((x3999*(10))+((x3997-(1))));
    int x4003 = x3995._2;
    int x4005 = x3996;
    x3996 = ((x4005*(1))+((x4003-(1))));
    int x4009 = x3996;
    return x4009; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3992, const struct SEntry11_IISSSSSSDDI& x3993) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x3648 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x3649 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x3786 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x3805 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x3824 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x3988 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x3989 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x4015 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x4147 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x4148 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x4235 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x4236 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x4261 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry3_III x6521;
struct SEntry11_IISSSSSSDDI x7091;
struct SEntry8_IIIITIIB x6733;
struct SEntry5_IISDS x7065;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6910;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7085;
struct SEntry10_IIIIIITIDS x6541;
struct SEntry11_IISSSSSSDDI x6853;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6545;
struct SEntry17_IIISSSSSSSSSSIIIS x6689;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6760;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6893;
struct SEntry9_ISSSSSSDD x7088;
struct SEntry11_IISSSSSSDDI x6658;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6743;
struct SEntry8_IIIITIIB x7098;
struct SEntry17_IIISSSSSSSSSSIIIS x7115;
struct SEntry10_IIIIIITIDS x6670;
struct SEntry10_IIIIIITIDS x7188;
struct SEntry9_ISSSSSSDD x6848;
struct SEntry8_IIIITIIB x6532;
struct SEntry3_III x7101;
struct SEntry8_IIIIITDS x6876;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x6521._2 = x27;
    x6521._3 = x12;
    struct SEntry3_III* x10772 = x3649.get(x6521);
    if((x10772!=(NULL))) {
      int x6525 = x10772->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6525;
      newOrderTbl.del(x10772);
      int x41 = x18;
      x6532._1 = x6525;
      x6532._2 = x41;
      x6532._3 = x12;
      struct SEntry8_IIIITIIB* x10785 = x3988.get(x6532);
      int x6534 = x10785->_4;
      x10785->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x6541._1 = x6525;
      x6541._2 = x52;
      x6541._3 = x12;
      //slice 
      typedef typename orderLineTblIdx1Type::IFN IDXFN10801;
      HASH_RES_t h10801 = IDXFN10801::hash(x6541);
      auto* n10801 = &(x4148.buckets_[h10801 % x4148.size_]);
      do if(n10801 -> obj && h10801 == n10801->hash && !IDXFN10801::cmp(x6541, *n10801->obj)) {
        do {
            auto orderLineEntry = n10801->obj;
            
            orderLineEntry->_7 = x11;
            double x57 = x50;
            double x6585 = orderLineEntry->_9;
            x50 = (x57+(x6585));
         } while((n10801 = n10801->nxt) && (h10801 == n10801->hash) && !IDXFN10801::cmp(x6541, *n10801->obj));
        break;
      } while((n10801 = n10801->nxt));
      int x65 = x18;
      x6545._1 = x6534;
      x6545._2 = x65;
      x6545._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10807 = x4235.get(x6545);
      double x69 = x50;
      x10807->_17 += x69;
      x10807->_20 += 1;
    } else {
      
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x6658._1 = x85;
  x6658._2 = x84;
  struct SEntry11_IISSSSSSDDI* x10874 = x4015.get(x6658);
  int x6660 = x10874->_11;
  int x95 = (x6660-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x99 = x95;
    if (!((x99<(x6660)))) break; 
    
    int x101 = x95;
    x6670._1 = x101;
    x6670._2 = x85;
    x6670._3 = x84;
    //slice 
    typedef typename orderLineTblIdx1Type::IFN IDXFN10898;
    HASH_RES_t h10898 = IDXFN10898::hash(x6670);
    auto* n10898 = &(x4148.buckets_[h10898 % x4148.size_]);
    do if(n10898 -> obj && h10898 == n10898->hash && !IDXFN10898::cmp(x6670, *n10898->obj)) {
      do {
          auto orderLineEntry = n10898->obj;
          
          int x6687 = orderLineEntry->_5;
          x6689._1 = x6687;
          x6689._2 = x84;
          struct SEntry17_IIISSSSSSSSSSIIIS* x10888 = x4261.get(x6689);
          int x6691 = x10888->_3;
          if((x6691<(x86))) {
            unique_ol_i_id.insert(x6687);
          };
       } while((n10898 = n10898->nxt) && (h10898 == n10898->hash) && !IDXFN10898::cmp(x6670, *n10898->obj));
      break;
    } while((n10898 = n10898->nxt));
    int x118 = x95;
    x95 = (x118+(1));
  };
}
void OrderStatusTx(int x124, date x125, int x126, int x127, int x128, int x129, int x130, PString x131) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite15238 = NULL;
  if((x129>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x15239;
    x6743._2 = x128;
    x6743._3 = x127;
    x6743._6 = x131;
    //slice 
    typedef typename customerTblIdx1Type::IFN IDXFN15246;
    HASH_RES_t h15246 = IDXFN15246::hash(x6743);
    auto* n15246 = &(x4236.buckets_[h15246 % x4236.size_]);
    do if(n15246 -> obj && h15246 == n15246->hash && !IDXFN15246::cmp(x6743, *n15246->obj)) {
      do {
          auto custEntry = n15246->obj;
          
          x15239.push_back(custEntry);
       } while((n15246 = n15246->nxt) && (h15246 == n15246->hash) && !IDXFN15246::cmp(x6743, *n15246->obj));
      break;
    } while((n15246 = n15246->nxt));
    int x15247 = x15239.size();
    int x15249 = (x15247/(2));
    int x15257 = x15239.size();
    if(((x15257%(2))==(0))) {
      int x150 = x15249;
      x15249 = (x150-(1));
    };
    sort(x15239.begin(), x15239.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6784 = c1->_4;
      const PString& x6785 = c2->_4;
      return ((strcmpi(x6784.data_, x6785.data_))<(0)); 
    }));
    int x15265 = x15249;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15266 = x15239[x15265];
    ite15238 = x15266;
  } else {
    
    x6760._1 = x130;
    x6760._2 = x128;
    x6760._3 = x127;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15271 = x4235.get(x6760);
    ite15238 = x15271;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6730 = ite15238;
  int x6731 = x6730->_3;
  x6733._2 = x128;
  x6733._3 = x127;
  x6733._4 = x6731;
  struct SEntry8_IIIITIIB* x10974 = x3989.get(x6733);
  int x181 = 0;
  int x6736 = x10974->_1;
  x181 = x6736;
}
void PaymentTx(int x185, date x186, int x187, int x188, int x189, int x190, int x191, int x192, int x193, PString x194, double x195) {
  x6848._1 = x188;
  struct SEntry9_ISSSSSSDD* x11025 = x3805.get(x6848);
  x11025->_9 += x195;
  x6853._1 = x189;
  x6853._2 = x188;
  struct SEntry11_IISSSSSSDDI* x11030 = x4015.get(x6853);
  x11030->_10 += x195;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite15337 = NULL;
  if((x190>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x15338;
    x6893._2 = x192;
    x6893._3 = x191;
    x6893._6 = x194;
    //slice 
    typedef typename customerTblIdx1Type::IFN IDXFN15345;
    HASH_RES_t h15345 = IDXFN15345::hash(x6893);
    auto* n15345 = &(x4236.buckets_[h15345 % x4236.size_]);
    do if(n15345 -> obj && h15345 == n15345->hash && !IDXFN15345::cmp(x6893, *n15345->obj)) {
      do {
          auto custEntry = n15345->obj;
          
          x15338.push_back(custEntry);
       } while((n15345 = n15345->nxt) && (h15345 == n15345->hash) && !IDXFN15345::cmp(x6893, *n15345->obj));
      break;
    } while((n15345 = n15345->nxt));
    int x15346 = x15338.size();
    int x15348 = (x15346/(2));
    int x15356 = x15338.size();
    if(((x15356%(2))==(0))) {
      int x226 = x15348;
      x15348 = (x226-(1));
    };
    sort(x15338.begin(), x15338.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6956 = c1->_4;
      const PString& x6957 = c2->_4;
      return ((strcmpi(x6956.data_, x6957.data_))<(0)); 
    }));
    int x15364 = x15348;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15365 = x15338[x15364];
    ite15337 = x15365;
  } else {
    
    x6910._1 = x193;
    x6910._2 = x192;
    x6910._3 = x191;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15370 = x4235.get(x6910);
    ite15337 = x15370;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6858 = ite15337;
  const PString& x6859 = x6858->_21;
  const PString& x6860 = x6858->_14;
  char* x16687 = strstr(x6860.data_, "BC");
  if((x16687!=(NULL))) {
    int x6863 = x6858->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x6863, x192, x191, x189, x188, x195, IntToStrdate(x186), x6859.data_);
    x6858->_17 += x195;
    x6858->_21 = c_new_data;
  } else {
    
    x6858->_17 += x195;
  };
  const PString& x6870 = x11025->_2;
  const PString& x6871 = x11030->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x6870.data_, x6871.data_);
  int x6874 = x6858->_1;
  x6876._1 = x6874;
  x6876._2 = x192;
  x6876._3 = x191;
  x6876._4 = x189;
  x6876._5 = x188;
  x6876._6 = x186;
  x6876._7 = x195;
  x6876._8 = h_data;
  historyTbl.add(x6876);
}
void NewOrderTx(int x268, date x269, int x270, int x271, int x272, int x273, int x274, int x275, int* x276, int* x277, int* x278, double* x279, PString* x280, int* x281, PString* x282, double* x283) {
  int x285 = 0;
  int x288 = 0;
  PString idata[x274];
  int x293 = 1;
  while(1) {
    
    int x295 = x285;
    int ite15659 = 0;
    if((x295<(x274))) {
      
      int x297 = x293;
      int x15660 = x297;
      ite15659 = x15660;
    } else {
      
      ite15659 = 0;
    };
    int x15474 = ite15659;
    if (!(x15474)) break; 
    
    int x300 = x285;
    int x301 = x276[x300];
    x7065._1 = x301;
    struct SEntry5_IISDS* x11176 = x3824.get(x7065);
    if((x11176==(NULL))) {
      x293 = 0;
    } else {
      
      int x307 = x285;
      const PString& x7071 = x11176->_3;
      x280[x307] = x7071;
      int x310 = x285;
      double x7074 = x11176->_4;
      x279[x310] = x7074;
      int x313 = x285;
      const PString& x7077 = x11176->_5;
      idata[x313] = x7077;
    };
    int x317 = x285;
    x285 = (x317+(1));
  };
  int x321 = x293;
  if(x321) {
    x7085._1 = x273;
    x7085._2 = x272;
    x7085._3 = x271;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11198 = x4235.get(x7085);
    x7088._1 = x271;
    struct SEntry9_ISSSSSSDD* x11201 = x3805.get(x7088);
    x7091._1 = x272;
    x7091._2 = x271;
    struct SEntry11_IISSSSSSDDI* x11205 = x4015.get(x7091);
    int x7093 = x11205->_11;
    x11205->_11 += 1;
    x7098._1 = x7093;
    x7098._2 = x272;
    x7098._3 = x271;
    x7098._4 = x273;
    x7098._5 = x269;
    x7098._6 = -1;
    x7098._7 = x274;
    x7098._8 = (x275>(0));
    orderTbl.add(x7098);
    x7101._1 = x7093;
    x7101._2 = x272;
    x7101._3 = x271;
    newOrderTbl.add(x7101);
    double x346 = 0.0;
    x285 = 0;
    while(1) {
      
      int x349 = x285;
      if (!((x349<(x274)))) break; 
      
      int x352 = x285;
      int ol_supply_w_id = x277[x352];
      int x355 = x285;
      int ol_i_id = x276[x355];
      int x358 = x285;
      int ol_quantity = x278[x358];
      x7115._1 = ol_i_id;
      x7115._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11238 = x4261.get(x7115);
      PString ite15537 = PString();
      if((x272==(1))) {
        const PString& x15538 = x11238->_4;
        ite15537 = x15538;
      } else {
        
        PString ite15542 = PString();
        if((x272==(2))) {
          const PString& x15543 = x11238->_5;
          ite15542 = x15543;
        } else {
          
          PString ite15547 = PString();
          if((x272==(3))) {
            const PString& x15548 = x11238->_6;
            ite15547 = x15548;
          } else {
            
            PString ite15552 = PString();
            if((x272==(4))) {
              const PString& x15553 = x11238->_7;
              ite15552 = x15553;
            } else {
              
              PString ite15557 = PString();
              if((x272==(5))) {
                const PString& x15558 = x11238->_8;
                ite15557 = x15558;
              } else {
                
                PString ite15562 = PString();
                if((x272==(6))) {
                  const PString& x15563 = x11238->_9;
                  ite15562 = x15563;
                } else {
                  
                  PString ite15567 = PString();
                  if((x272==(7))) {
                    const PString& x15568 = x11238->_10;
                    ite15567 = x15568;
                  } else {
                    
                    PString ite15572 = PString();
                    if((x272==(8))) {
                      const PString& x15573 = x11238->_11;
                      ite15572 = x15573;
                    } else {
                      
                      PString ite15577 = PString();
                      if((x272==(9))) {
                        const PString& x15578 = x11238->_12;
                        ite15577 = x15578;
                      } else {
                        
                        const PString& x15580 = x11238->_13;
                        ite15577 = x15580;
                      };
                      PString x15576 = ite15577;
                      ite15572 = x15576;
                    };
                    PString x15571 = ite15572;
                    ite15567 = x15571;
                  };
                  PString x15566 = ite15567;
                  ite15562 = x15566;
                };
                PString x15561 = ite15562;
                ite15557 = x15561;
              };
              PString x15556 = ite15557;
              ite15552 = x15556;
            };
            PString x15551 = ite15552;
            ite15547 = x15551;
          };
          PString x15546 = ite15547;
          ite15542 = x15546;
        };
        PString x15541 = ite15542;
        ite15537 = x15541;
      };
      PString ol_dist_info = ite15537;
      int x7145 = x11238->_3;
      int x395 = x285;
      x281[x395] = x7145;
      const PString& x7148 = x11198->_14;
      char* x16922 = strstr(x7148.data_, "original");
      int ite15795 = 0;
      if((x16922!=(NULL))) {
        
        const PString& x7151 = x11238->_17;
        char* x16928 = strstr(x7151.data_, "original");
        int x15796 = (x16928!=(NULL));
        ite15795 = x15796;
      } else {
        
        ite15795 = 0;
      };
      int x15605 = ite15795;
      if(x15605) {
        int x402 = x285;
        x282[x402] = "B";
      } else {
        
        int x404 = x285;
        x282[x404] = "G";
      };
      x11238->_3 = (x7145-(ol_quantity));
      if((x7145<=(ol_quantity))) {
        x11238->_3 += 91;
      };
      int x413 = 0;
      if((ol_supply_w_id!=(x271))) {
        x413 = 1;
      };
      double x7168 = x11198->_16;
      double x7169 = x11201->_8;
      double x7170 = x11205->_9;
      int x426 = x285;
      double x427 = x279[x426];
      double ol_amount = ((ol_quantity*(x427))*(((1.0+(x7169))+(x7170))))*((1.0-(x7168)));
      int x435 = x285;
      x283[x435] = ol_amount;
      double x437 = x346;
      x346 = (x437+(ol_amount));
      int x440 = x285;
      x7188._1 = x7093;
      x7188._2 = x272;
      x7188._3 = x271;
      x7188._4 = (x440+(1));
      x7188._5 = ol_i_id;
      x7188._6 = ol_supply_w_id;
      x7188._8 = ol_quantity;
      x7188._9 = ol_amount;
      x7188._10 = ol_dist_info;
      orderLineTbl.add(x7188);
      int x445 = x285;
      x285 = (x445+(1));
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
  
  uint xactCounts[5] = {0, 0, 0, 0, 0};
  auto start = Now;
  for(size_t i = 0; i < numPrograms; ++i){
    Program *prg = tpcc.programs[i];
    switch(prg->id){
       case NEWORDER :
        {
           NewOrder& p = *(NewOrder *)prg;
           xactCounts[0]++;
           NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
           break;
        }
      case PAYMENTBYID :
        {
           PaymentById& p = *(PaymentById *) prg;
           xactCounts[1]++;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
           break;
        }
      case PAYMENTBYNAME :
        {
           PaymentByName& p = *(PaymentByName *) prg;
           xactCounts[1]++;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
           break;
        }
      case ORDERSTATUSBYID :
        {
           OrderStatusById &p = *(OrderStatusById *) prg;
           xactCounts[2]++;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
           break;
        }
      case ORDERSTATUSBYNAME :
        {
           OrderStatusByName &p = *(OrderStatusByName *) prg;
           xactCounts[2]++;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
           break;
        }
      case DELIVERY :
        {
           Delivery &p = *(Delivery *) prg;
           xactCounts[3]++;
           DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
           break;
        }
      case STOCKLEVEL :
       {
         StockLevel &p = *(StockLevel *) prg;
         xactCounts[4]++;
         StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         break;
       }
       default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
  
    }
  }
  auto end = Now;
  auto execTime = DurationMS(end - start);
  cout << "Total time = " << execTime << " ms" << endl;
  cout << "TpmC = " << fixed <<  xactCounts[0] * 60000.0/execTime << endl;
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1)
    fout << "\nCPP-CDEFGIMNORSTVX,";
  fout << fixed << xactCounts[0] * 60000.0/execTime << ",";
  fout.close();
  
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
