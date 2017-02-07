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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4026)  { 
    int x4027 = 0;
    int x4028 = x4027;
    int x4029 = x4026._1;
    x4027 = (x4028^(((((HASH(x4029))+(-1640531527))+((x4028<<(6))))+((x4028>>(2))))));
    int x4038 = x4027;
    int x4039 = x4026._2;
    x4027 = (x4038^(((((HASH(x4039))+(-1640531527))+((x4038<<(6))))+((x4038>>(2))))));
    int x4048 = x4027;
    int x4049 = x4026._3;
    x4027 = (x4048^(((((HASH(x4049))+(-1640531527))+((x4048<<(6))))+((x4048>>(2))))));
    int x4058 = x4027;
    int x4059 = x4026._4;
    x4027 = (x4058^(((((HASH(x4059))+(-1640531527))+((x4058<<(6))))+((x4058>>(2))))));
    int x4068 = x4027;
    return x4068; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4070, const struct SEntry10_IIIIIITIDS& x4071) { 
    int x4072 = 0;
    int x4073 = x4070._1;
    int x4074 = x4071._1;
    if((x4073==(x4074))) {
      int x4076 = x4070._2;
      int x4077 = x4071._2;
      if((x4076==(x4077))) {
        int x4079 = x4070._3;
        int x4080 = x4071._3;
        if((x4079==(x4080))) {
          int x4082 = x4070._4;
          int x4083 = x4071._4;
          if((x4082==(x4083))) {
            x4072 = 0;
          } else {
            x4072 = 1;
          };
        } else {
          x4072 = 1;
        };
      } else {
        x4072 = 1;
      };
    } else {
      x4072 = 1;
    };
    int x4094 = x4072;
    return x4094; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3938)  { 
    int x3939 = 0;
    int x3940 = x3939;
    int x3941 = x3938._2;
    x3939 = (x3940^(((((HASH(x3941))+(-1640531527))+((x3940<<(6))))+((x3940>>(2))))));
    int x3950 = x3939;
    int x3951 = x3938._3;
    x3939 = (x3950^(((((HASH(x3951))+(-1640531527))+((x3950<<(6))))+((x3950>>(2))))));
    int x3960 = x3939;
    int x3961 = x3938._4;
    x3939 = (x3960^(((((HASH(x3961))+(-1640531527))+((x3960<<(6))))+((x3960>>(2))))));
    int x3970 = x3939;
    return x3970; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3972, const struct SEntry8_IIIITIIB& x3973) { 
    int x3974 = 0;
    int x3975 = x3972._2;
    int x3976 = x3973._2;
    if((x3975==(x3976))) {
      int x3978 = x3972._3;
      int x3979 = x3973._3;
      if((x3978==(x3979))) {
        int x3981 = x3972._4;
        int x3982 = x3973._4;
        if((x3981==(x3982))) {
          x3974 = 0;
        } else {
          x3974 = 1;
        };
      } else {
        x3974 = 1;
      };
    } else {
      x3974 = 1;
    };
    int x3991 = x3974;
    return x3991; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3523)  { 
    int x3524 = 0;
    int x3525 = x3524;
    int x3526 = x3523._1;
    x3524 = (x3525^(((((HASH(x3526))+(-1640531527))+((x3525<<(6))))+((x3525>>(2))))));
    int x3535 = x3524;
    int x3536 = x3523._2;
    x3524 = (x3535^(((((HASH(x3536))+(-1640531527))+((x3535<<(6))))+((x3535>>(2))))));
    int x3545 = x3524;
    int x3546 = x3523._3;
    x3524 = (x3545^(((((HASH(x3546))+(-1640531527))+((x3545<<(6))))+((x3545>>(2))))));
    int x3555 = x3524;
    return x3555; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3557, const struct SEntry3_III& x3558) { 
    int x3559 = 0;
    int x3560 = x3557._1;
    int x3561 = x3558._1;
    if((x3560==(x3561))) {
      int x3563 = x3557._2;
      int x3564 = x3558._2;
      if((x3563==(x3564))) {
        int x3566 = x3557._3;
        int x3567 = x3558._3;
        if((x3566==(x3567))) {
          x3559 = 0;
        } else {
          x3559 = 1;
        };
      } else {
        x3559 = 1;
      };
    } else {
      x3559 = 1;
    };
    int x3576 = x3559;
    return x3576; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3661)  { 
    int x3662 = 0;
    int x3663 = x3662;
    int x3664 = x3661._1;
    x3662 = (x3663^(((((HASH(x3664))+(-1640531527))+((x3663<<(6))))+((x3663>>(2))))));
    int x3673 = x3662;
    int x3674 = x3661._2;
    x3662 = (x3673^(((((HASH(x3674))+(-1640531527))+((x3673<<(6))))+((x3673>>(2))))));
    int x3683 = x3662;
    int x3684 = x3661._3;
    x3662 = (x3683^(((((HASH(x3684))+(-1640531527))+((x3683<<(6))))+((x3683>>(2))))));
    int x3693 = x3662;
    int x3694 = x3661._4;
    x3662 = (x3693^(((((HASH(x3694))+(-1640531527))+((x3693<<(6))))+((x3693>>(2))))));
    int x3703 = x3662;
    int x3704 = x3661._5;
    x3662 = (x3703^(((((HASH(x3704))+(-1640531527))+((x3703<<(6))))+((x3703>>(2))))));
    int x3713 = x3662;
    date x3714 = x3661._6;
    x3662 = (x3713^(((((HASH(x3714))+(-1640531527))+((x3713<<(6))))+((x3713>>(2))))));
    int x3723 = x3662;
    double x3724 = x3661._7;
    x3662 = (x3723^(((((HASH(x3724))+(-1640531527))+((x3723<<(6))))+((x3723>>(2))))));
    int x3733 = x3662;
    const PString& x3734 = x3661._8;
    x3662 = (x3733^(((((HASH(x3734))+(-1640531527))+((x3733<<(6))))+((x3733>>(2))))));
    int x3743 = x3662;
    return x3743; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3745, const struct SEntry8_IIIIITDS& x3746) { 
    int x3747 = 0;
    int x3748 = x3745._1;
    int x3749 = x3746._1;
    if((x3748==(x3749))) {
      int x3751 = x3745._2;
      int x3752 = x3746._2;
      if((x3751==(x3752))) {
        int x3754 = x3745._3;
        int x3755 = x3746._3;
        if((x3754==(x3755))) {
          int x3757 = x3745._4;
          int x3758 = x3746._4;
          if((x3757==(x3758))) {
            int x3760 = x3745._5;
            int x3761 = x3746._5;
            if((x3760==(x3761))) {
              date x3763 = x3745._6;
              date x3764 = x3746._6;
              if((x3763==(x3764))) {
                double x3766 = x3745._7;
                double x3767 = x3746._7;
                if((x3766==(x3767))) {
                  const PString& x3769 = x3745._8;
                  const PString& x3770 = x3746._8;
                  if((x3769==(x3770))) {
                    x3747 = 0;
                  } else {
                    x3747 = 1;
                  };
                } else {
                  x3747 = 1;
                };
              } else {
                x3747 = 1;
              };
            } else {
              x3747 = 1;
            };
          } else {
            x3747 = 1;
          };
        } else {
          x3747 = 1;
        };
      } else {
        x3747 = 1;
      };
    } else {
      x3747 = 1;
    };
    int x3789 = x3747;
    return x3789; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4097)  { 
    int x4098 = 0;
    int x4099 = x4098;
    int x4100 = x4097._1;
    x4098 = (x4099^(((((HASH(x4100))+(-1640531527))+((x4099<<(6))))+((x4099>>(2))))));
    int x4109 = x4098;
    int x4110 = x4097._2;
    x4098 = (x4109^(((((HASH(x4110))+(-1640531527))+((x4109<<(6))))+((x4109>>(2))))));
    int x4119 = x4098;
    int x4120 = x4097._3;
    x4098 = (x4119^(((((HASH(x4120))+(-1640531527))+((x4119<<(6))))+((x4119>>(2))))));
    int x4129 = x4098;
    return x4129; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4131, const struct SEntry10_IIIIIITIDS& x4132) { 
    int x4133 = 0;
    int x4134 = x4131._1;
    int x4135 = x4132._1;
    if((x4134==(x4135))) {
      int x4137 = x4131._2;
      int x4138 = x4132._2;
      if((x4137==(x4138))) {
        int x4140 = x4131._3;
        int x4141 = x4132._3;
        if((x4140==(x4141))) {
          x4133 = 0;
        } else {
          x4133 = 1;
        };
      } else {
        x4133 = 1;
      };
    } else {
      x4133 = 1;
    };
    int x4150 = x4133;
    return x4150; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3613)  { 
    int x3614 = 0;
    int x3615 = x3614;
    int x3616 = x3613._2;
    x3614 = (x3615^(((((HASH(x3616))+(-1640531527))+((x3615<<(6))))+((x3615>>(2))))));
    int x3625 = x3614;
    int x3626 = x3613._3;
    x3614 = (x3625^(((((HASH(x3626))+(-1640531527))+((x3625<<(6))))+((x3625>>(2))))));
    int x3635 = x3614;
    return x3635; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3637, const struct SEntry3_III& x3638) { 
    int x3639 = 0;
    int x3640 = x3637._2;
    int x3641 = x3638._2;
    if((x3640==(x3641))) {
      int x3643 = x3637._3;
      int x3644 = x3638._3;
      if((x3643==(x3644))) {
        x3639 = 0;
      } else {
        x3639 = 1;
      };
    } else {
      x3639 = 1;
    };
    int x3651 = x3639;
    return x3651; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4185)  { 
    int x4186 = 0;
    int x4187 = x4186;
    int x4188 = x4185._2;
    x4186 = (x4187^(((((HASH(x4188))+(-1640531527))+((x4187<<(6))))+((x4187>>(2))))));
    int x4197 = x4186;
    int x4198 = x4185._3;
    x4186 = (x4197^(((((HASH(x4198))+(-1640531527))+((x4197<<(6))))+((x4197>>(2))))));
    int x4207 = x4186;
    const PString& x4208 = x4185._6;
    x4186 = (x4207^(((((HASH(x4208))+(-1640531527))+((x4207<<(6))))+((x4207>>(2))))));
    int x4217 = x4186;
    return x4217; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4219, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4220) { 
    int x4221 = 0;
    int x4222 = x4219._2;
    int x4223 = x4220._2;
    if((x4222==(x4223))) {
      int x4225 = x4219._3;
      int x4226 = x4220._3;
      if((x4225==(x4226))) {
        const PString& x4228 = x4219._6;
        const PString& x4229 = x4220._6;
        if((x4228==(x4229))) {
          x4221 = 0;
        } else {
          x4221 = 1;
        };
      } else {
        x4221 = 1;
      };
    } else {
      x4221 = 1;
    };
    int x4238 = x4221;
    return x4238; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3838)  { 
    int x3839 = 0;
    int x3840 = x3839;
    int x3841 = x3838._1;
    x3839 = (x3840^(((((HASH(x3841))+(-1640531527))+((x3840<<(6))))+((x3840>>(2))))));
    int x3850 = x3839;
    int x3851 = x3838._2;
    x3839 = (x3850^(((((HASH(x3851))+(-1640531527))+((x3850<<(6))))+((x3850>>(2))))));
    int x3860 = x3839;
    int x3861 = x3838._3;
    x3839 = (x3860^(((((HASH(x3861))+(-1640531527))+((x3860<<(6))))+((x3860>>(2))))));
    int x3870 = x3839;
    return x3870; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3872, const struct SEntry8_IIIITIIB& x3873) { 
    int x3874 = 0;
    int x3875 = x3872._1;
    int x3876 = x3873._1;
    if((x3875==(x3876))) {
      int x3878 = x3872._2;
      int x3879 = x3873._2;
      if((x3878==(x3879))) {
        int x3881 = x3872._3;
        int x3882 = x3873._3;
        if((x3881==(x3882))) {
          x3874 = 0;
        } else {
          x3874 = 1;
        };
      } else {
        x3874 = 1;
      };
    } else {
      x3874 = 1;
    };
    int x3891 = x3874;
    return x3891; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3579)  { 
    int x3580 = 0;
    int x3581 = x3580;
    int x3582 = x3579._2;
    x3580 = (x3581^(((((HASH(x3582))+(-1640531527))+((x3581<<(6))))+((x3581>>(2))))));
    int x3591 = x3580;
    int x3592 = x3579._3;
    x3580 = (x3591^(((((HASH(x3592))+(-1640531527))+((x3591<<(6))))+((x3591>>(2))))));
    int x3601 = x3580;
    return x3601; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3603, const struct SEntry3_III& x3604) { 
    int x3605 = x3603._1;
    int x3606 = x3604._1;
    return ((x3605==(x3606)) ? 0 : ((x3605>(x3606)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3894)  { 
    int x3895 = 0;
    int x3896 = x3895;
    int x3897 = x3894._2;
    x3895 = (x3896^(((((HASH(x3897))+(-1640531527))+((x3896<<(6))))+((x3896>>(2))))));
    int x3906 = x3895;
    int x3907 = x3894._3;
    x3895 = (x3906^(((((HASH(x3907))+(-1640531527))+((x3906<<(6))))+((x3906>>(2))))));
    int x3916 = x3895;
    int x3917 = x3894._4;
    x3895 = (x3916^(((((HASH(x3917))+(-1640531527))+((x3916<<(6))))+((x3916>>(2))))));
    int x3926 = x3895;
    return x3926; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3928, const struct SEntry8_IIIITIIB& x3929) { 
    int x3930 = x3928._1;
    int x3931 = x3929._1;
    return ((x3930==(x3931)) ? 0 : ((x3930>(x3931)) ? 1 : -1)); 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4250)  { 
    int x4251 = 0;
    int x4252 = x4250._1;
    int x4254 = x4251;
    x4251 = ((x4254*(100000))+((x4252-(1))));
    int x4258 = x4250._2;
    int x4260 = x4251;
    x4251 = ((x4260*(1))+((x4258-(1))));
    int x4264 = x4251;
    return x4264; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4247, const struct SEntry17_IIISSSSSSSSSSIIIS& x4248) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4162)  { 
    int x4163 = 0;
    int x4164 = x4162._1;
    int x4166 = x4163;
    x4163 = ((x4166*(3000))+((x4164-(1))));
    int x4170 = x4162._2;
    int x4172 = x4163;
    x4163 = ((x4172*(10))+((x4170-(1))));
    int x4176 = x4162._3;
    int x4178 = x4163;
    x4163 = ((x4178*(1))+((x4176-(1))));
    int x4182 = x4163;
    return x4182; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4159, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4160) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3819)  { 
    int x3820 = 0;
    int x3821 = x3819._1;
    int x3823 = x3820;
    x3820 = ((x3823*(100000))+((x3821-(1))));
    int x3827 = x3820;
    return x3827; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3816, const struct SEntry5_IISDS& x3817) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3800)  { 
    int x3801 = 0;
    int x3802 = x3800._1;
    int x3804 = x3801;
    x3801 = ((x3804*(1))+((x3802-(1))));
    int x3808 = x3801;
    return x3808; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3797, const struct SEntry9_ISSSSSSDD& x3798) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4004)  { 
    int x4005 = 0;
    int x4006 = x4004._1;
    int x4008 = x4005;
    x4005 = ((x4008*(10))+((x4006-(1))));
    int x4012 = x4004._2;
    int x4014 = x4005;
    x4005 = ((x4014*(1))+((x4012-(1))));
    int x4018 = x4005;
    return x4018; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4001, const struct SEntry11_IISSSSSSDDI& x4002) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& x3657 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x3658 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& x3795 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& x3814 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& x3833 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& x3997 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x3998 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& x4024 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& x4156 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x4157 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& x4244 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x4245 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& x4270 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6922;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6772;
struct SEntry9_ISSSSSSDD x6860;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6554;
struct SEntry11_IISSSSSSDDI x7103;
struct SEntry8_IIIITIIB x6541;
struct SEntry5_IISDS x7077;
struct SEntry10_IIIIIITIDS x6680;
struct SEntry8_IIIITIIB x7110;
struct SEntry17_IIISSSSSSSSSSIIIS x6700;
struct SEntry10_IIIIIITIDS x7200;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6905;
struct SEntry11_IISSSSSSDDI x6667;
struct SEntry11_IISSSSSSDDI x6865;
struct SEntry8_IIIIITDS x6888;
struct SEntry8_IIIITIIB x6745;
struct SEntry3_III x7113;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6755;
struct SEntry17_IIISSSSSSSSSSIIIS x7127;
struct SEntry3_III x6530;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7097;
struct SEntry10_IIIIIITIDS x6550;
struct SEntry9_ISSSSSSDD x7100;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x6530._2 = x27;
    x6530._3 = x12;
    struct SEntry3_III* x10787 = x3658.get(x6530);
    if((x10787!=(NULL))) {
      int x6534 = x10787->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6534;
      newOrderTbl.del(x10787);
      int x41 = x18;
      x6541._1 = x6534;
      x6541._2 = x41;
      x6541._3 = x12;
      struct SEntry8_IIIITIIB* x10800 = x3997.get(x6541);
      int x6543 = x10800->_4;
      x10800->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x6550._1 = x6534;
      x6550._2 = x52;
      x6550._3 = x12;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN12288;
      HASH_RES_t h12288 = IDXFN12288::hash(x6550);
      auto* x12288 = &(x4157.buckets_[h12288 % x4157.size_]);
      do if(x12288 -> obj && h12288 == x12288->hash && !IDXFN12288::cmp(x6550, *x12288->obj))
           break;
      while((x12288 = x12288->nxt));
      if((x12288 == nullptr)) {
      } else {
        //sliceResMap 
        do {
          auto orderLineEntry = x12288->obj;
              
              orderLineEntry->_7 = x11;
              double x57 = x50;
              double x6594 = orderLineEntry->_9;
              x50 = (x57+(x6594));
        } while((x12288 = x12288->nxt) && (h12288== x12288->hash) && !IDXFN12288::cmp(x6550, *x12288->obj));
      };
      int x65 = x18;
      x6554._1 = x6543;
      x6554._2 = x65;
      x6554._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10822 = x4244.get(x6554);
      double x69 = x50;
      x10822->_17 += x69;
      x10822->_20 += 1;
    } else {
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x6667._1 = x85;
  x6667._2 = x84;
  struct SEntry11_IISSSSSSDDI* x10889 = x4024.get(x6667);
  int x6669 = x10889->_11;
  int x95 = (x6669-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x100 = x95;
    if (!((x100<(x6669)))) break; 
    
    int x102 = x95;
    x6680._1 = x102;
    x6680._2 = x85;
    x6680._3 = x84;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN12335;
    HASH_RES_t h12335 = IDXFN12335::hash(x6680);
    auto* x12335 = &(x4157.buckets_[h12335 % x4157.size_]);
    do if(x12335 -> obj && h12335 == x12335->hash && !IDXFN12335::cmp(x6680, *x12335->obj))
         break;
    while((x12335 = x12335->nxt));
    if((x12335 == nullptr)) {
    } else {
      //sliceResMap 
      do {
        auto orderLineEntry = x12335->obj;
            
            int x6698 = orderLineEntry->_5;
            x6700._1 = x6698;
            x6700._2 = x84;
            struct SEntry17_IIISSSSSSSSSSIIIS* x10904 = x4270.get(x6700);
            int x6702 = x10904->_3;
            if((x6702<(x86))) {
              unique_ol_i_id.insert(x6698);
            };
      } while((x12335 = x12335->nxt) && (h12335== x12335->hash) && !IDXFN12335::cmp(x6680, *x12335->obj));
    };
    int x119 = x95;
    x95 = (x119+(1));
  };
}
void OrderStatusTx(int x125, date x126, int x127, int x128, int x129, int x130, int x131, PString x132) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16829 = NULL;
  if((x130>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16830;
    x6755._2 = x129;
    x6755._3 = x128;
    x6755._6 = x132;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16837;
    HASH_RES_t h16837 = IDXFN16837::hash(x6755);
    auto* x16837 = &(x4245.buckets_[h16837 % x4245.size_]);
    do if(x16837 -> obj && h16837 == x16837->hash && !IDXFN16837::cmp(x6755, *x16837->obj))
         break;
    while((x16837 = x16837->nxt));
    if((x16837 == nullptr)) {
    } else {
      //sliceResMap 
      do {
        auto custEntry = x16837->obj;
            
            x16830.push_back(custEntry);
      } while((x16837 = x16837->nxt) && (h16837== x16837->hash) && !IDXFN16837::cmp(x6755, *x16837->obj));
    };
    int x16841 = x16830.size();
    int x16843 = (x16841/(2));
    int x16851 = x16830.size();
    if(((x16851%(2))==(0))) {
      int x151 = x16843;
      x16843 = (x151-(1));
    };
    sort(x16830.begin(), x16830.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6796 = c1->_4;
      const PString& x6797 = c2->_4;
      return ((strcmpi(x6796.data_, x6797.data_))<(0)); 
    }));
    int x16859 = x16843;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16860 = x16830[x16859];
    ite16829 = x16860;
  } else {
    x6772._1 = x131;
    x6772._2 = x129;
    x6772._3 = x128;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16865 = x4244.get(x6772);
    ite16829 = x16865;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6742 = ite16829;
  int x6743 = x6742->_3;
  x6745._2 = x129;
  x6745._3 = x128;
  x6745._4 = x6743;
  struct SEntry8_IIIITIIB* x10991 = x3998.get(x6745);
  int x182 = 0;
  int x6748 = x10991->_1;
  x182 = x6748;
}
void PaymentTx(int x186, date x187, int x188, int x189, int x190, int x191, int x192, int x193, int x194, PString x195, double x196) {
  x6860._1 = x189;
  struct SEntry9_ISSSSSSDD* x11042 = x3814.get(x6860);
  x11042->_9 += x196;
  x6865._1 = x190;
  x6865._2 = x189;
  struct SEntry11_IISSSSSSDDI* x11047 = x4024.get(x6865);
  x11047->_10 += x196;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16934 = NULL;
  if((x191>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16935;
    x6905._2 = x193;
    x6905._3 = x192;
    x6905._6 = x195;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16942;
    HASH_RES_t h16942 = IDXFN16942::hash(x6905);
    auto* x16942 = &(x4245.buckets_[h16942 % x4245.size_]);
    do if(x16942 -> obj && h16942 == x16942->hash && !IDXFN16942::cmp(x6905, *x16942->obj))
         break;
    while((x16942 = x16942->nxt));
    if((x16942 == nullptr)) {
    } else {
      //sliceResMap 
      do {
        auto custEntry = x16942->obj;
            
            x16935.push_back(custEntry);
      } while((x16942 = x16942->nxt) && (h16942== x16942->hash) && !IDXFN16942::cmp(x6905, *x16942->obj));
    };
    int x16946 = x16935.size();
    int x16948 = (x16946/(2));
    int x16956 = x16935.size();
    if(((x16956%(2))==(0))) {
      int x227 = x16948;
      x16948 = (x227-(1));
    };
    sort(x16935.begin(), x16935.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6968 = c1->_4;
      const PString& x6969 = c2->_4;
      return ((strcmpi(x6968.data_, x6969.data_))<(0)); 
    }));
    int x16964 = x16948;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16965 = x16935[x16964];
    ite16934 = x16965;
  } else {
    x6922._1 = x194;
    x6922._2 = x193;
    x6922._3 = x192;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16970 = x4244.get(x6922);
    ite16934 = x16970;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6870 = ite16934;
  const PString& x6871 = x6870->_21;
  const PString& x6872 = x6870->_14;
  char* x18316 = strstr(x6872.data_, "BC");
  if((x18316!=(NULL))) {
    int x6875 = x6870->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x6875, x193, x192, x190, x189, x196, IntToStrdate(x187), x6871.data_);
    x6870->_17 += x196;
    x6870->_21 = c_new_data;
  } else {
    x6870->_17 += x196;
  };
  const PString& x6882 = x11042->_2;
  const PString& x6883 = x11047->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x6882.data_, x6883.data_);
  int x6886 = x6870->_1;
  x6888._1 = x6886;
  x6888._2 = x193;
  x6888._3 = x192;
  x6888._4 = x190;
  x6888._5 = x189;
  x6888._6 = x187;
  x6888._7 = x196;
  x6888._8 = h_data;
  historyTbl.insert_nocheck(x6888);
}
void NewOrderTx(int x269, date x270, int x271, int x272, int x273, int x274, int x275, int x276, int* x277, int* x278, int* x279, double* x280, PString* x281, int* x282, PString* x283, double* x284) {
  int x286 = 0;
  int x289 = 0;
  PString idata[x275];
  int x294 = 1;
  while(1) {
    
    int x296 = x286;
    int ite17262 = 0;
    if((x296<(x275))) {
      
      int x298 = x294;
      int x17263 = x298;
      ite17262 = x17263;
    } else {
      ite17262 = 0;
    };
    int x17077 = ite17262;
    if (!(x17077)) break; 
    
    int x301 = x286;
    int x302 = x277[x301];
    x7077._1 = x302;
    struct SEntry5_IISDS* x11193 = x3833.get(x7077);
    if((x11193==(NULL))) {
      x294 = 0;
    } else {
      int x308 = x286;
      const PString& x7083 = x11193->_3;
      x281[x308] = x7083;
      int x311 = x286;
      double x7086 = x11193->_4;
      x280[x311] = x7086;
      int x314 = x286;
      const PString& x7089 = x11193->_5;
      idata[x314] = x7089;
    };
    int x318 = x286;
    x286 = (x318+(1));
  };
  int x322 = x294;
  if(x322) {
    x7097._1 = x274;
    x7097._2 = x273;
    x7097._3 = x272;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11215 = x4244.get(x7097);
    x7100._1 = x272;
    struct SEntry9_ISSSSSSDD* x11218 = x3814.get(x7100);
    x7103._1 = x273;
    x7103._2 = x272;
    struct SEntry11_IISSSSSSDDI* x11222 = x4024.get(x7103);
    int x7105 = x11222->_11;
    x11222->_11 += 1;
    x7110._1 = x7105;
    x7110._2 = x273;
    x7110._3 = x272;
    x7110._4 = x274;
    x7110._5 = x270;
    x7110._6 = -1;
    x7110._7 = x275;
    x7110._8 = (x276>(0));
    orderTbl.insert_nocheck(x7110);
    x7113._1 = x7105;
    x7113._2 = x273;
    x7113._3 = x272;
    newOrderTbl.insert_nocheck(x7113);
    double x347 = 0.0;
    x286 = 0;
    while(1) {
      
      int x350 = x286;
      if (!((x350<(x275)))) break; 
      
      int x353 = x286;
      int ol_supply_w_id = x278[x353];
      int x356 = x286;
      int ol_i_id = x277[x356];
      int x359 = x286;
      int ol_quantity = x279[x359];
      x7127._1 = ol_i_id;
      x7127._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11255 = x4270.get(x7127);
      PString ite17140 = PString();
      if((x273==(1))) {
        const PString& x17141 = x11255->_4;
        ite17140 = x17141;
      } else {
        PString ite17145 = PString();
        if((x273==(2))) {
          const PString& x17146 = x11255->_5;
          ite17145 = x17146;
        } else {
          PString ite17150 = PString();
          if((x273==(3))) {
            const PString& x17151 = x11255->_6;
            ite17150 = x17151;
          } else {
            PString ite17155 = PString();
            if((x273==(4))) {
              const PString& x17156 = x11255->_7;
              ite17155 = x17156;
            } else {
              PString ite17160 = PString();
              if((x273==(5))) {
                const PString& x17161 = x11255->_8;
                ite17160 = x17161;
              } else {
                PString ite17165 = PString();
                if((x273==(6))) {
                  const PString& x17166 = x11255->_9;
                  ite17165 = x17166;
                } else {
                  PString ite17170 = PString();
                  if((x273==(7))) {
                    const PString& x17171 = x11255->_10;
                    ite17170 = x17171;
                  } else {
                    PString ite17175 = PString();
                    if((x273==(8))) {
                      const PString& x17176 = x11255->_11;
                      ite17175 = x17176;
                    } else {
                      PString ite17180 = PString();
                      if((x273==(9))) {
                        const PString& x17181 = x11255->_12;
                        ite17180 = x17181;
                      } else {
                        const PString& x17183 = x11255->_13;
                        ite17180 = x17183;
                      };
                      PString x17179 = ite17180;
                      ite17175 = x17179;
                    };
                    PString x17174 = ite17175;
                    ite17170 = x17174;
                  };
                  PString x17169 = ite17170;
                  ite17165 = x17169;
                };
                PString x17164 = ite17165;
                ite17160 = x17164;
              };
              PString x17159 = ite17160;
              ite17155 = x17159;
            };
            PString x17154 = ite17155;
            ite17150 = x17154;
          };
          PString x17149 = ite17150;
          ite17145 = x17149;
        };
        PString x17144 = ite17145;
        ite17140 = x17144;
      };
      PString ol_dist_info = ite17140;
      int x7157 = x11255->_3;
      int x396 = x286;
      x282[x396] = x7157;
      const PString& x7160 = x11215->_14;
      char* x18554 = strstr(x7160.data_, "original");
      int ite17398 = 0;
      if((x18554!=(NULL))) {
        
        const PString& x7163 = x11255->_17;
        char* x18560 = strstr(x7163.data_, "original");
        int x17399 = (x18560!=(NULL));
        ite17398 = x17399;
      } else {
        ite17398 = 0;
      };
      int x17208 = ite17398;
      if(x17208) {
        int x403 = x286;
        x283[x403] = "B";
      } else {
        int x405 = x286;
        x283[x405] = "G";
      };
      x11255->_3 = (x7157-(ol_quantity));
      if((x7157<=(ol_quantity))) {
        x11255->_3 += 91;
      };
      int x414 = 0;
      if((ol_supply_w_id!=(x272))) {
        x414 = 1;
      };
      double x7180 = x11215->_16;
      double x7181 = x11218->_8;
      double x7182 = x11222->_9;
      int x427 = x286;
      double x428 = x280[x427];
      double ol_amount = ((ol_quantity*(x428))*(((1.0+(x7181))+(x7182))))*((1.0-(x7180)));
      int x436 = x286;
      x284[x436] = ol_amount;
      double x438 = x347;
      x347 = (x438+(ol_amount));
      int x441 = x286;
      x7200._1 = x7105;
      x7200._2 = x273;
      x7200._3 = x272;
      x7200._4 = (x441+(1));
      x7200._5 = ol_i_id;
      x7200._6 = ol_supply_w_id;
      x7200._8 = ol_quantity;
      x7200._9 = ol_amount;
      x7200._10 = ol_dist_info;
      orderLineTbl.insert_nocheck(x7200);
      int x446 = x286;
      x286 = (x446+(1));
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
    fout << "\nCPP-CDEFGIMNORSTUVX,";
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
