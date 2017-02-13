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

const size_t warehouseTblArrayLengths[] = {0};
const size_t itemTblArrayLengths[] = {0};
const size_t districtTblArrayLengths[] = {0};
const size_t customerTblArrayLengths[] = {0, 65536};
const size_t orderTblArrayLengths[] = {1048576, 65536};
const size_t newOrderTblArrayLengths[] = {16384, 32};
const size_t orderLineTblArrayLengths[] = {8388608, 8388608};
const size_t stockTblArrayLengths[] = {0};
const size_t historyTblArrayLengths[] = {1048576};

const size_t warehouseTblPoolSizes[] = {8, 0};
const size_t itemTblPoolSizes[] = {65536*2, 0};
const size_t districtTblPoolSizes[] = {16, 0};
const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
const size_t stockTblPoolSizes[] = {65536*2, 0};
const size_t historyTblPoolSizes[] = {262144*2, 65536};
     
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
newOrderTblStoreType  newOrderTbl(newOrderTblArrayLengths, newOrderTblPoolSizes);
newOrderTblIdx0Type& x3657 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x3658 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblArrayLengths, historyTblPoolSizes);
historyTblIdx0Type& x3795 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblArrayLengths, warehouseTblPoolSizes);
warehouseTblIdx0Type& x3814 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblArrayLengths, itemTblPoolSizes);
itemTblIdx0Type& x3833 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblArrayLengths, orderTblPoolSizes);
orderTblIdx0Type& x3997 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x3998 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblArrayLengths, districtTblPoolSizes);
districtTblIdx0Type& x4024 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblArrayLengths, orderLineTblPoolSizes);
orderLineTblIdx0Type& x4156 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x4157 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblArrayLengths, customerTblPoolSizes);
customerTblIdx0Type& x4244 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x4245 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblArrayLengths, stockTblPoolSizes);
stockTblIdx0Type& x4270 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry11_IISSSSSSDDI x6862;
struct SEntry5_IISDS x7074;
struct SEntry10_IIIIIITIDS x7198;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6554;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6902;
struct SEntry17_IIISSSSSSSSSSIIIS x6698;
struct SEntry8_IIIITIIB x6541;
struct SEntry8_IIIITIIB x6742;
struct SEntry8_IIIITIIB x7107;
struct SEntry3_III x7110;
struct SEntry10_IIIIIITIDS x6679;
struct SEntry17_IIISSSSSSSSSSIIIS x7124;
struct SEntry11_IISSSSSSDDI x6667;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6752;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6769;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7094;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6919;
struct SEntry3_III x6530;
struct SEntry9_ISSSSSSDD x7097;
struct SEntry10_IIIIIITIDS x6550;
struct SEntry11_IISSSSSSDDI x7100;
struct SEntry9_ISSSSSSDD x6857;
struct SEntry8_IIIIITDS x6885;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x6530._2 = x27;
    x6530._3 = x12;
    struct SEntry3_III* x10786 = x3658.get(x6530);
    if((x10786!=(NULL))) {
      int x6534 = x10786->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6534;
      newOrderTbl.del(x10786);
      int x41 = x18;
      x6541._1 = x6534;
      x6541._2 = x41;
      x6541._3 = x12;
      struct SEntry8_IIIITIIB* x10799 = x3997.get(x6541);
      int x6543 = x10799->_4;
      x10799->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x6550._1 = x6534;
      x6550._2 = x52;
      x6550._3 = x12;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN12287;
      HASH_RES_t h12287 = IDXFN12287::hash(x6550);
      auto* x12287 = &(x4157.buckets_[h12287 % x4157.size_]);
      if(x12287 -> obj)
         do if(h12287 == x12287->hash && !IDXFN12287::cmp(x6550, *x12287->obj))
           break;
         while((x12287 = x12287->nxt));
      else 
         x12287 = nullptr;
      if((x12287 == nullptr)) {
      } else {
        //sliceResMap 
         do if(h12287== x12287->hash && !IDXFN12287::cmp(x6550, *x12287->obj)) {
            auto orderLineEntry = x12287->obj;
            
            orderLineEntry->_7 = x11;
            double x57 = x50;
            double x6594 = orderLineEntry->_9;
            x50 = (x57+(x6594));
        } while((x12287 = x12287->nxt));
      };
      int x65 = x18;
      x6554._1 = x6543;
      x6554._2 = x65;
      x6554._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10821 = x4244.get(x6554);
      double x69 = x50;
      x10821->_17 += x69;
      x10821->_20 += 1;
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
  struct SEntry11_IISSSSSSDDI* x10888 = x4024.get(x6667);
  int x6669 = x10888->_11;
  int x95 = (x6669-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x99 = x95;
    if (!((x99<(x6669)))) break; 
    
    int x101 = x95;
    x6679._1 = x101;
    x6679._2 = x85;
    x6679._3 = x84;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN12333;
    HASH_RES_t h12333 = IDXFN12333::hash(x6679);
    auto* x12333 = &(x4157.buckets_[h12333 % x4157.size_]);
    if(x12333 -> obj)
       do if(h12333 == x12333->hash && !IDXFN12333::cmp(x6679, *x12333->obj))
         break;
       while((x12333 = x12333->nxt));
    else 
       x12333 = nullptr;
    if((x12333 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h12333== x12333->hash && !IDXFN12333::cmp(x6679, *x12333->obj)) {
          auto orderLineEntry = x12333->obj;
          
          int x6696 = orderLineEntry->_5;
          x6698._1 = x6696;
          x6698._2 = x84;
          struct SEntry17_IIISSSSSSSSSSIIIS* x10902 = x4270.get(x6698);
          int x6700 = x10902->_3;
          if((x6700<(x86))) {
            unique_ol_i_id.insert(x6696);
          };
      } while((x12333 = x12333->nxt));
    };
    int x118 = x95;
    x95 = (x118+(1));
  };
}
void OrderStatusTx(int x124, date x125, int x126, int x127, int x128, int x129, int x130, PString x131) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16827 = NULL;
  if((x129>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16828;
    x6752._2 = x128;
    x6752._3 = x127;
    x6752._6 = x131;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16835;
    HASH_RES_t h16835 = IDXFN16835::hash(x6752);
    auto* x16835 = &(x4245.buckets_[h16835 % x4245.size_]);
    if(x16835 -> obj)
       do if(h16835 == x16835->hash && !IDXFN16835::cmp(x6752, *x16835->obj))
         break;
       while((x16835 = x16835->nxt));
    else 
       x16835 = nullptr;
    if((x16835 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h16835== x16835->hash && !IDXFN16835::cmp(x6752, *x16835->obj)) {
          auto custEntry = x16835->obj;
          
          x16828.push_back(custEntry);
      } while((x16835 = x16835->nxt));
    };
    int x16839 = x16828.size();
    int x16841 = (x16839/(2));
    int x16849 = x16828.size();
    if(((x16849%(2))==(0))) {
      int x150 = x16841;
      x16841 = (x150-(1));
    };
    sort(x16828.begin(), x16828.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6793 = c1->_4;
      const PString& x6794 = c2->_4;
      return ((strcmpi(x6793.data_, x6794.data_))<(0)); 
    }));
    int x16857 = x16841;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16858 = x16828[x16857];
    ite16827 = x16858;
  } else {
    x6769._1 = x130;
    x6769._2 = x128;
    x6769._3 = x127;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16863 = x4244.get(x6769);
    ite16827 = x16863;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6739 = ite16827;
  int x6740 = x6739->_3;
  x6742._2 = x128;
  x6742._3 = x127;
  x6742._4 = x6740;
  struct SEntry8_IIIITIIB* x10988 = x3998.get(x6742);
  int x181 = 0;
  int x6745 = x10988->_1;
  x181 = x6745;
}
void PaymentTx(int x185, date x186, int x187, int x188, int x189, int x190, int x191, int x192, int x193, PString x194, double x195) {
  x6857._1 = x188;
  struct SEntry9_ISSSSSSDD* x11039 = x3814.get(x6857);
  x11039->_9 += x195;
  x6862._1 = x189;
  x6862._2 = x188;
  struct SEntry11_IISSSSSSDDI* x11044 = x4024.get(x6862);
  x11044->_10 += x195;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16932 = NULL;
  if((x190>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16933;
    x6902._2 = x192;
    x6902._3 = x191;
    x6902._6 = x194;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16940;
    HASH_RES_t h16940 = IDXFN16940::hash(x6902);
    auto* x16940 = &(x4245.buckets_[h16940 % x4245.size_]);
    if(x16940 -> obj)
       do if(h16940 == x16940->hash && !IDXFN16940::cmp(x6902, *x16940->obj))
         break;
       while((x16940 = x16940->nxt));
    else 
       x16940 = nullptr;
    if((x16940 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h16940== x16940->hash && !IDXFN16940::cmp(x6902, *x16940->obj)) {
          auto custEntry = x16940->obj;
          
          x16933.push_back(custEntry);
      } while((x16940 = x16940->nxt));
    };
    int x16944 = x16933.size();
    int x16946 = (x16944/(2));
    int x16954 = x16933.size();
    if(((x16954%(2))==(0))) {
      int x226 = x16946;
      x16946 = (x226-(1));
    };
    sort(x16933.begin(), x16933.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6965 = c1->_4;
      const PString& x6966 = c2->_4;
      return ((strcmpi(x6965.data_, x6966.data_))<(0)); 
    }));
    int x16962 = x16946;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16963 = x16933[x16962];
    ite16932 = x16963;
  } else {
    x6919._1 = x193;
    x6919._2 = x192;
    x6919._3 = x191;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16968 = x4244.get(x6919);
    ite16932 = x16968;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6867 = ite16932;
  const PString& x6868 = x6867->_21;
  const PString& x6869 = x6867->_14;
  char* x18316 = strstr(x6869.data_, "BC");
  if((x18316!=(NULL))) {
    int x6872 = x6867->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x6872, x192, x191, x189, x188, x195, IntToStrdate(x186), x6868.data_);
    x6867->_17 += x195;
    x6867->_21 = c_new_data;
  } else {
    x6867->_17 += x195;
  };
  const PString& x6879 = x11039->_2;
  const PString& x6880 = x11044->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x6879.data_, x6880.data_);
  int x6883 = x6867->_1;
  x6885._1 = x6883;
  x6885._2 = x192;
  x6885._3 = x191;
  x6885._4 = x189;
  x6885._5 = x188;
  x6885._6 = x186;
  x6885._7 = x195;
  x6885._8 = h_data;
  historyTbl.insert_nocheck(x6885);
}
void NewOrderTx(int x268, date x269, int x270, int x271, int x272, int x273, int x274, int x275, int* x276, int* x277, int* x278, double* x279, PString* x280, int* x281, PString* x282, double* x283) {
  int x285 = 0;
  int x288 = 0;
  PString idata[x274];
  int x293 = 1;
  while(1) {
    
    int x295 = x285;
    int ite17261 = 0;
    if((x295<(x274))) {
      
      int x297 = x293;
      int x17262 = x297;
      ite17261 = x17262;
    } else {
      ite17261 = 0;
    };
    int x17075 = ite17261;
    if (!(x17075)) break; 
    
    int x300 = x285;
    int x301 = x276[x300];
    x7074._1 = x301;
    struct SEntry5_IISDS* x11190 = x3833.get(x7074);
    if((x11190==(NULL))) {
      x293 = 0;
    } else {
      int x307 = x285;
      const PString& x7080 = x11190->_3;
      x280[x307] = x7080;
      int x310 = x285;
      double x7083 = x11190->_4;
      x279[x310] = x7083;
      int x313 = x285;
      const PString& x7086 = x11190->_5;
      idata[x313] = x7086;
    };
    int x317 = x285;
    x285 = (x317+(1));
  };
  int x321 = x293;
  if(x321) {
    x7094._1 = x273;
    x7094._2 = x272;
    x7094._3 = x271;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11212 = x4244.get(x7094);
    x7097._1 = x271;
    struct SEntry9_ISSSSSSDD* x11215 = x3814.get(x7097);
    x7100._1 = x272;
    x7100._2 = x271;
    struct SEntry11_IISSSSSSDDI* x11219 = x4024.get(x7100);
    int x7102 = x11219->_11;
    x11219->_11 += 1;
    x7107._1 = x7102;
    x7107._2 = x272;
    x7107._3 = x271;
    x7107._4 = x273;
    x7107._5 = x269;
    x7107._6 = -1;
    x7107._7 = x274;
    x7107._8 = (x275>(0));
    orderTbl.insert_nocheck(x7107);
    x7110._1 = x7102;
    x7110._2 = x272;
    x7110._3 = x271;
    newOrderTbl.insert_nocheck(x7110);
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
      x7124._1 = ol_i_id;
      x7124._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11252 = x4270.get(x7124);
      PString ite17138 = PString();
      if((x272==(1))) {
        const PString& x17139 = x11252->_4;
        ite17138 = x17139;
      } else {
        PString ite17143 = PString();
        if((x272==(2))) {
          const PString& x17144 = x11252->_5;
          ite17143 = x17144;
        } else {
          PString ite17148 = PString();
          if((x272==(3))) {
            const PString& x17149 = x11252->_6;
            ite17148 = x17149;
          } else {
            PString ite17153 = PString();
            if((x272==(4))) {
              const PString& x17154 = x11252->_7;
              ite17153 = x17154;
            } else {
              PString ite17158 = PString();
              if((x272==(5))) {
                const PString& x17159 = x11252->_8;
                ite17158 = x17159;
              } else {
                PString ite17163 = PString();
                if((x272==(6))) {
                  const PString& x17164 = x11252->_9;
                  ite17163 = x17164;
                } else {
                  PString ite17168 = PString();
                  if((x272==(7))) {
                    const PString& x17169 = x11252->_10;
                    ite17168 = x17169;
                  } else {
                    PString ite17173 = PString();
                    if((x272==(8))) {
                      const PString& x17174 = x11252->_11;
                      ite17173 = x17174;
                    } else {
                      PString ite17178 = PString();
                      if((x272==(9))) {
                        const PString& x17179 = x11252->_12;
                        ite17178 = x17179;
                      } else {
                        const PString& x17181 = x11252->_13;
                        ite17178 = x17181;
                      };
                      PString x17177 = ite17178;
                      ite17173 = x17177;
                    };
                    PString x17172 = ite17173;
                    ite17168 = x17172;
                  };
                  PString x17167 = ite17168;
                  ite17163 = x17167;
                };
                PString x17162 = ite17163;
                ite17158 = x17162;
              };
              PString x17157 = ite17158;
              ite17153 = x17157;
            };
            PString x17152 = ite17153;
            ite17148 = x17152;
          };
          PString x17147 = ite17148;
          ite17143 = x17147;
        };
        PString x17142 = ite17143;
        ite17138 = x17142;
      };
      PString ol_dist_info = ite17138;
      int x7154 = x11252->_3;
      int x395 = x285;
      x281[x395] = x7154;
      int x397 = x285;
      PString& x398 = idata[x397];
      char* x18555 = strstr(x398.data_, "original");
      int ite17398 = 0;
      if((x18555!=(NULL))) {
        
        const PString& x7161 = x11252->_17;
        char* x18561 = strstr(x7161.data_, "original");
        int x17399 = (x18561!=(NULL));
        ite17398 = x17399;
      } else {
        ite17398 = 0;
      };
      int x17207 = ite17398;
      if(x17207) {
        int x403 = x285;
        x282[x403] = "B";
      } else {
        int x405 = x285;
        x282[x405] = "G";
      };
      x11252->_3 = (x7154-(ol_quantity));
      if((x7154<=(ol_quantity))) {
        x11252->_3 += 91;
      };
      int x414 = 0;
      if((ol_supply_w_id!=(x271))) {
        x414 = 1;
      };
      double x7178 = x11212->_16;
      double x7179 = x11215->_8;
      double x7180 = x11219->_9;
      int x427 = x285;
      double x428 = x279[x427];
      double ol_amount = ((ol_quantity*(x428))*(((1.0+(x7179))+(x7180))))*((1.0-(x7178)));
      int x436 = x285;
      x283[x436] = ol_amount;
      double x438 = x346;
      x346 = (x438+(ol_amount));
      int x441 = x285;
      x7198._1 = x7102;
      x7198._2 = x272;
      x7198._3 = x271;
      x7198._4 = (x441+(1));
      x7198._5 = ol_i_id;
      x7198._6 = ol_supply_w_id;
      x7198._8 = ol_quantity;
      x7198._9 = ol_amount;
      x7198._10 = ol_dist_info;
      orderLineTbl.insert_nocheck(x7198);
      int x446 = x285;
      x285 = (x446+(1));
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
    fout << "\nCPP-CDEFGIMNORSTUVXZ,";
  fout << fixed << xactCounts[0] * 60000.0/execTime << ",";
  fout.close();
  
  #ifdef VERIFY_TPCC
      warehouseTblPrimaryIdx.resize_(warehouseTblSize);
      districtTblPrimaryIdx.resize_(districtTblSize);
      customerTblPrimaryIdx.resize_(customerTblSize);
      orderTblPrimaryIdx.resize_(orderTblSize);
      newOrderTblPrimaryIdx.resize_(newOrderTblSize);
      orderLineTblPrimaryIdx.resize_(orderLineTblSize);
      itemTblPrimaryIdx.resize_(itemTblSize);
      stockTblPrimaryIdx.resize_(stockTblSize);
      historyTblPrimaryIdx.resize_(historyTblSize);
  
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
