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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4035)  { 
    int x4036 = 0;
    int x4037 = x4036;
    int x4038 = x4035._1;
    x4036 = (x4037^(((((HASH(x4038))+(-1640531527))+((x4037<<(6))))+((x4037>>(2))))));
    int x4047 = x4036;
    int x4048 = x4035._2;
    x4036 = (x4047^(((((HASH(x4048))+(-1640531527))+((x4047<<(6))))+((x4047>>(2))))));
    int x4057 = x4036;
    int x4058 = x4035._3;
    x4036 = (x4057^(((((HASH(x4058))+(-1640531527))+((x4057<<(6))))+((x4057>>(2))))));
    int x4067 = x4036;
    int x4068 = x4035._4;
    x4036 = (x4067^(((((HASH(x4068))+(-1640531527))+((x4067<<(6))))+((x4067>>(2))))));
    int x4077 = x4036;
    return x4077; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4079, const struct SEntry10_IIIIIITIDS& x4080) { 
    int x4081 = 0;
    int x4082 = x4079._1;
    int x4083 = x4080._1;
    if((x4082==(x4083))) {
      int x4085 = x4079._2;
      int x4086 = x4080._2;
      if((x4085==(x4086))) {
        int x4088 = x4079._3;
        int x4089 = x4080._3;
        if((x4088==(x4089))) {
          int x4091 = x4079._4;
          int x4092 = x4080._4;
          if((x4091==(x4092))) {
            x4081 = 0;
          } else {
            x4081 = 1;
          };
        } else {
          x4081 = 1;
        };
      } else {
        x4081 = 1;
      };
    } else {
      x4081 = 1;
    };
    int x4103 = x4081;
    return x4103; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3947)  { 
    int x3948 = 0;
    int x3949 = x3948;
    int x3950 = x3947._2;
    x3948 = (x3949^(((((HASH(x3950))+(-1640531527))+((x3949<<(6))))+((x3949>>(2))))));
    int x3959 = x3948;
    int x3960 = x3947._3;
    x3948 = (x3959^(((((HASH(x3960))+(-1640531527))+((x3959<<(6))))+((x3959>>(2))))));
    int x3969 = x3948;
    int x3970 = x3947._4;
    x3948 = (x3969^(((((HASH(x3970))+(-1640531527))+((x3969<<(6))))+((x3969>>(2))))));
    int x3979 = x3948;
    return x3979; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3981, const struct SEntry8_IIIITIIB& x3982) { 
    int x3983 = 0;
    int x3984 = x3981._2;
    int x3985 = x3982._2;
    if((x3984==(x3985))) {
      int x3987 = x3981._3;
      int x3988 = x3982._3;
      if((x3987==(x3988))) {
        int x3990 = x3981._4;
        int x3991 = x3982._4;
        if((x3990==(x3991))) {
          x3983 = 0;
        } else {
          x3983 = 1;
        };
      } else {
        x3983 = 1;
      };
    } else {
      x3983 = 1;
    };
    int x4000 = x3983;
    return x4000; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3532)  { 
    int x3533 = 0;
    int x3534 = x3533;
    int x3535 = x3532._1;
    x3533 = (x3534^(((((HASH(x3535))+(-1640531527))+((x3534<<(6))))+((x3534>>(2))))));
    int x3544 = x3533;
    int x3545 = x3532._2;
    x3533 = (x3544^(((((HASH(x3545))+(-1640531527))+((x3544<<(6))))+((x3544>>(2))))));
    int x3554 = x3533;
    int x3555 = x3532._3;
    x3533 = (x3554^(((((HASH(x3555))+(-1640531527))+((x3554<<(6))))+((x3554>>(2))))));
    int x3564 = x3533;
    return x3564; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3566, const struct SEntry3_III& x3567) { 
    int x3568 = 0;
    int x3569 = x3566._1;
    int x3570 = x3567._1;
    if((x3569==(x3570))) {
      int x3572 = x3566._2;
      int x3573 = x3567._2;
      if((x3572==(x3573))) {
        int x3575 = x3566._3;
        int x3576 = x3567._3;
        if((x3575==(x3576))) {
          x3568 = 0;
        } else {
          x3568 = 1;
        };
      } else {
        x3568 = 1;
      };
    } else {
      x3568 = 1;
    };
    int x3585 = x3568;
    return x3585; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3670)  { 
    int x3671 = 0;
    int x3672 = x3671;
    int x3673 = x3670._1;
    x3671 = (x3672^(((((HASH(x3673))+(-1640531527))+((x3672<<(6))))+((x3672>>(2))))));
    int x3682 = x3671;
    int x3683 = x3670._2;
    x3671 = (x3682^(((((HASH(x3683))+(-1640531527))+((x3682<<(6))))+((x3682>>(2))))));
    int x3692 = x3671;
    int x3693 = x3670._3;
    x3671 = (x3692^(((((HASH(x3693))+(-1640531527))+((x3692<<(6))))+((x3692>>(2))))));
    int x3702 = x3671;
    int x3703 = x3670._4;
    x3671 = (x3702^(((((HASH(x3703))+(-1640531527))+((x3702<<(6))))+((x3702>>(2))))));
    int x3712 = x3671;
    int x3713 = x3670._5;
    x3671 = (x3712^(((((HASH(x3713))+(-1640531527))+((x3712<<(6))))+((x3712>>(2))))));
    int x3722 = x3671;
    date x3723 = x3670._6;
    x3671 = (x3722^(((((HASH(x3723))+(-1640531527))+((x3722<<(6))))+((x3722>>(2))))));
    int x3732 = x3671;
    double x3733 = x3670._7;
    x3671 = (x3732^(((((HASH(x3733))+(-1640531527))+((x3732<<(6))))+((x3732>>(2))))));
    int x3742 = x3671;
    const PString& x3743 = x3670._8;
    x3671 = (x3742^(((((HASH(x3743))+(-1640531527))+((x3742<<(6))))+((x3742>>(2))))));
    int x3752 = x3671;
    return x3752; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3754, const struct SEntry8_IIIIITDS& x3755) { 
    int x3756 = 0;
    int x3757 = x3754._1;
    int x3758 = x3755._1;
    if((x3757==(x3758))) {
      int x3760 = x3754._2;
      int x3761 = x3755._2;
      if((x3760==(x3761))) {
        int x3763 = x3754._3;
        int x3764 = x3755._3;
        if((x3763==(x3764))) {
          int x3766 = x3754._4;
          int x3767 = x3755._4;
          if((x3766==(x3767))) {
            int x3769 = x3754._5;
            int x3770 = x3755._5;
            if((x3769==(x3770))) {
              date x3772 = x3754._6;
              date x3773 = x3755._6;
              if((x3772==(x3773))) {
                double x3775 = x3754._7;
                double x3776 = x3755._7;
                if((x3775==(x3776))) {
                  const PString& x3778 = x3754._8;
                  const PString& x3779 = x3755._8;
                  if((x3778==(x3779))) {
                    x3756 = 0;
                  } else {
                    x3756 = 1;
                  };
                } else {
                  x3756 = 1;
                };
              } else {
                x3756 = 1;
              };
            } else {
              x3756 = 1;
            };
          } else {
            x3756 = 1;
          };
        } else {
          x3756 = 1;
        };
      } else {
        x3756 = 1;
      };
    } else {
      x3756 = 1;
    };
    int x3798 = x3756;
    return x3798; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4106)  { 
    int x4107 = 0;
    int x4108 = x4107;
    int x4109 = x4106._1;
    x4107 = (x4108^(((((HASH(x4109))+(-1640531527))+((x4108<<(6))))+((x4108>>(2))))));
    int x4118 = x4107;
    int x4119 = x4106._2;
    x4107 = (x4118^(((((HASH(x4119))+(-1640531527))+((x4118<<(6))))+((x4118>>(2))))));
    int x4128 = x4107;
    int x4129 = x4106._3;
    x4107 = (x4128^(((((HASH(x4129))+(-1640531527))+((x4128<<(6))))+((x4128>>(2))))));
    int x4138 = x4107;
    return x4138; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4140, const struct SEntry10_IIIIIITIDS& x4141) { 
    int x4142 = 0;
    int x4143 = x4140._1;
    int x4144 = x4141._1;
    if((x4143==(x4144))) {
      int x4146 = x4140._2;
      int x4147 = x4141._2;
      if((x4146==(x4147))) {
        int x4149 = x4140._3;
        int x4150 = x4141._3;
        if((x4149==(x4150))) {
          x4142 = 0;
        } else {
          x4142 = 1;
        };
      } else {
        x4142 = 1;
      };
    } else {
      x4142 = 1;
    };
    int x4159 = x4142;
    return x4159; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3622)  { 
    int x3623 = 0;
    int x3624 = x3623;
    int x3625 = x3622._2;
    x3623 = (x3624^(((((HASH(x3625))+(-1640531527))+((x3624<<(6))))+((x3624>>(2))))));
    int x3634 = x3623;
    int x3635 = x3622._3;
    x3623 = (x3634^(((((HASH(x3635))+(-1640531527))+((x3634<<(6))))+((x3634>>(2))))));
    int x3644 = x3623;
    return x3644; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3646, const struct SEntry3_III& x3647) { 
    int x3648 = 0;
    int x3649 = x3646._2;
    int x3650 = x3647._2;
    if((x3649==(x3650))) {
      int x3652 = x3646._3;
      int x3653 = x3647._3;
      if((x3652==(x3653))) {
        x3648 = 0;
      } else {
        x3648 = 1;
      };
    } else {
      x3648 = 1;
    };
    int x3660 = x3648;
    return x3660; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4194)  { 
    int x4195 = 0;
    int x4196 = x4195;
    int x4197 = x4194._2;
    x4195 = (x4196^(((((HASH(x4197))+(-1640531527))+((x4196<<(6))))+((x4196>>(2))))));
    int x4206 = x4195;
    int x4207 = x4194._3;
    x4195 = (x4206^(((((HASH(x4207))+(-1640531527))+((x4206<<(6))))+((x4206>>(2))))));
    int x4216 = x4195;
    const PString& x4217 = x4194._6;
    x4195 = (x4216^(((((HASH(x4217))+(-1640531527))+((x4216<<(6))))+((x4216>>(2))))));
    int x4226 = x4195;
    return x4226; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4228, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4229) { 
    int x4230 = 0;
    int x4231 = x4228._2;
    int x4232 = x4229._2;
    if((x4231==(x4232))) {
      int x4234 = x4228._3;
      int x4235 = x4229._3;
      if((x4234==(x4235))) {
        const PString& x4237 = x4228._6;
        const PString& x4238 = x4229._6;
        if((x4237==(x4238))) {
          x4230 = 0;
        } else {
          x4230 = 1;
        };
      } else {
        x4230 = 1;
      };
    } else {
      x4230 = 1;
    };
    int x4247 = x4230;
    return x4247; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3847)  { 
    int x3848 = 0;
    int x3849 = x3848;
    int x3850 = x3847._1;
    x3848 = (x3849^(((((HASH(x3850))+(-1640531527))+((x3849<<(6))))+((x3849>>(2))))));
    int x3859 = x3848;
    int x3860 = x3847._2;
    x3848 = (x3859^(((((HASH(x3860))+(-1640531527))+((x3859<<(6))))+((x3859>>(2))))));
    int x3869 = x3848;
    int x3870 = x3847._3;
    x3848 = (x3869^(((((HASH(x3870))+(-1640531527))+((x3869<<(6))))+((x3869>>(2))))));
    int x3879 = x3848;
    return x3879; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3881, const struct SEntry8_IIIITIIB& x3882) { 
    int x3883 = 0;
    int x3884 = x3881._1;
    int x3885 = x3882._1;
    if((x3884==(x3885))) {
      int x3887 = x3881._2;
      int x3888 = x3882._2;
      if((x3887==(x3888))) {
        int x3890 = x3881._3;
        int x3891 = x3882._3;
        if((x3890==(x3891))) {
          x3883 = 0;
        } else {
          x3883 = 1;
        };
      } else {
        x3883 = 1;
      };
    } else {
      x3883 = 1;
    };
    int x3900 = x3883;
    return x3900; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3588)  { 
    int x3589 = 0;
    int x3590 = x3589;
    int x3591 = x3588._2;
    x3589 = (x3590^(((((HASH(x3591))+(-1640531527))+((x3590<<(6))))+((x3590>>(2))))));
    int x3600 = x3589;
    int x3601 = x3588._3;
    x3589 = (x3600^(((((HASH(x3601))+(-1640531527))+((x3600<<(6))))+((x3600>>(2))))));
    int x3610 = x3589;
    return x3610; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3612, const struct SEntry3_III& x3613) { 
    int x3614 = x3612._1;
    int x3615 = x3613._1;
    return ((x3614==(x3615)) ? 0 : ((x3614>(x3615)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3903)  { 
    int x3904 = 0;
    int x3905 = x3904;
    int x3906 = x3903._2;
    x3904 = (x3905^(((((HASH(x3906))+(-1640531527))+((x3905<<(6))))+((x3905>>(2))))));
    int x3915 = x3904;
    int x3916 = x3903._3;
    x3904 = (x3915^(((((HASH(x3916))+(-1640531527))+((x3915<<(6))))+((x3915>>(2))))));
    int x3925 = x3904;
    int x3926 = x3903._4;
    x3904 = (x3925^(((((HASH(x3926))+(-1640531527))+((x3925<<(6))))+((x3925>>(2))))));
    int x3935 = x3904;
    return x3935; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3937, const struct SEntry8_IIIITIIB& x3938) { 
    int x3939 = x3937._1;
    int x3940 = x3938._1;
    return ((x3939==(x3940)) ? 0 : ((x3939>(x3940)) ? 1 : -1)); 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4259)  { 
    int x4260 = 0;
    int x4261 = x4259._1;
    int x4263 = x4260;
    x4260 = ((x4263*(100000))+((x4261-(1))));
    int x4267 = x4259._2;
    int x4269 = x4260;
    x4260 = ((x4269*(1))+((x4267-(1))));
    int x4273 = x4260;
    return x4273; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4256, const struct SEntry17_IIISSSSSSSSSSIIIS& x4257) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4171)  { 
    int x4172 = 0;
    int x4173 = x4171._1;
    int x4175 = x4172;
    x4172 = ((x4175*(3000))+((x4173-(1))));
    int x4179 = x4171._2;
    int x4181 = x4172;
    x4172 = ((x4181*(10))+((x4179-(1))));
    int x4185 = x4171._3;
    int x4187 = x4172;
    x4172 = ((x4187*(1))+((x4185-(1))));
    int x4191 = x4172;
    return x4191; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4168, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4169) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3828)  { 
    int x3829 = 0;
    int x3830 = x3828._1;
    int x3832 = x3829;
    x3829 = ((x3832*(100000))+((x3830-(1))));
    int x3836 = x3829;
    return x3836; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3825, const struct SEntry5_IISDS& x3826) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3809)  { 
    int x3810 = 0;
    int x3811 = x3809._1;
    int x3813 = x3810;
    x3810 = ((x3813*(1))+((x3811-(1))));
    int x3817 = x3810;
    return x3817; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3806, const struct SEntry9_ISSSSSSDD& x3807) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4013)  { 
    int x4014 = 0;
    int x4015 = x4013._1;
    int x4017 = x4014;
    x4014 = ((x4017*(10))+((x4015-(1))));
    int x4021 = x4013._2;
    int x4023 = x4014;
    x4014 = ((x4023*(1))+((x4021-(1))));
    int x4027 = x4014;
    return x4027; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4010, const struct SEntry11_IISSSSSSDDI& x4011) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblArrayLengths, newOrderTblPoolSizes);
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblArrayLengths, historyTblPoolSizes);
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblArrayLengths, warehouseTblPoolSizes);
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblArrayLengths, itemTblPoolSizes);
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblArrayLengths, orderTblPoolSizes);
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblArrayLengths, districtTblPoolSizes);
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblArrayLengths, orderLineTblPoolSizes);
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblArrayLengths, customerTblPoolSizes);
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblArrayLengths, stockTblPoolSizes);
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6781;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7106;
struct SEntry17_IIISSSSSSSSSSIIIS x7136;
struct SEntry9_ISSSSSSDD x6869;
struct SEntry11_IISSSSSSDDI x6874;
struct SEntry11_IISSSSSSDDI x6676;
struct SEntry17_IIISSSSSSSSSSIIIS x6709;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6914;
struct SEntry3_III x7122;
struct SEntry11_IISSSSSSDDI x7112;
struct SEntry5_IISDS x7086;
struct SEntry8_IIIIITDS x6897;
struct SEntry10_IIIIIITIDS x6689;
struct SEntry10_IIIIIITIDS x7210;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6931;
struct SEntry3_III x6539;
struct SEntry10_IIIIIITIDS x6559;
struct SEntry9_ISSSSSSDD x7109;
struct SEntry8_IIIITIIB x7119;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6764;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6563;
struct SEntry8_IIIITIIB x6550;
struct SEntry8_IIIITIIB x6754;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x6539._2 = x27;
    x6539._3 = x12;
    struct SEntry3_III* x10801 = newOrderTblIdx1.get(x6539);
    if((x10801!=(NULL))) {
      int x6543 = x10801->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6543;
      newOrderTbl.del(x10801);
      int x41 = x18;
      x6550._1 = x6543;
      x6550._2 = x41;
      x6550._3 = x12;
      struct SEntry8_IIIITIIB* x10814 = orderTblIdx0.get(x6550);
      int x6552 = x10814->_4;
      x10814->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x6559._1 = x6543;
      x6559._2 = x52;
      x6559._3 = x12;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN12304;
      HASH_RES_t h12304 = IDXFN12304::hash(x6559);
      auto* x12304 = &(orderLineTblIdx1.buckets_[h12304 % orderLineTblIdx1.size_]);
      if(x12304 -> obj)
         do if(h12304 == x12304->hash && !IDXFN12304::cmp(x6559, *x12304->obj))
           break;
         while((x12304 = x12304->nxt));
      else 
         x12304 = nullptr;
      if((x12304 == nullptr)) {
      } else {
        //sliceResMap 
         do if(h12304== x12304->hash && !IDXFN12304::cmp(x6559, *x12304->obj)) {
            auto orderLineEntry = x12304->obj;
            
            orderLineEntry->_7 = x11;
            double x57 = x50;
            double x6603 = orderLineEntry->_9;
            x50 = (x57+(x6603));
        } while((x12304 = x12304->nxt));
      };
      int x65 = x18;
      x6563._1 = x6552;
      x6563._2 = x65;
      x6563._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10836 = customerTblIdx0.get(x6563);
      double x69 = x50;
      x10836->_17 += x69;
      x10836->_20 += 1;
    } else {
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x6676._1 = x85;
  x6676._2 = x84;
  struct SEntry11_IISSSSSSDDI* x10903 = districtTblIdx0.get(x6676);
  int x6678 = x10903->_11;
  int x95 = (x6678-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x100 = x95;
    if (!((x100<(x6678)))) break; 
    
    int x102 = x95;
    x6689._1 = x102;
    x6689._2 = x85;
    x6689._3 = x84;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN12351;
    HASH_RES_t h12351 = IDXFN12351::hash(x6689);
    auto* x12351 = &(orderLineTblIdx1.buckets_[h12351 % orderLineTblIdx1.size_]);
    if(x12351 -> obj)
       do if(h12351 == x12351->hash && !IDXFN12351::cmp(x6689, *x12351->obj))
         break;
       while((x12351 = x12351->nxt));
    else 
       x12351 = nullptr;
    if((x12351 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h12351== x12351->hash && !IDXFN12351::cmp(x6689, *x12351->obj)) {
          auto orderLineEntry = x12351->obj;
          
          int x6707 = orderLineEntry->_5;
          x6709._1 = x6707;
          x6709._2 = x84;
          struct SEntry17_IIISSSSSSSSSSIIIS* x10918 = stockTblIdx0.get(x6709);
          int x6711 = x10918->_3;
          if((x6711<(x86))) {
            unique_ol_i_id.insert(x6707);
          };
      } while((x12351 = x12351->nxt));
    };
    int x119 = x95;
    x95 = (x119+(1));
  };
}
void OrderStatusTx(int x125, date x126, int x127, int x128, int x129, int x130, int x131, PString x132) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16851 = NULL;
  if((x130>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16852;
    x6764._2 = x129;
    x6764._3 = x128;
    x6764._6 = x132;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16859;
    HASH_RES_t h16859 = IDXFN16859::hash(x6764);
    auto* x16859 = &(customerTblIdx1.buckets_[h16859 % customerTblIdx1.size_]);
    if(x16859 -> obj)
       do if(h16859 == x16859->hash && !IDXFN16859::cmp(x6764, *x16859->obj))
         break;
       while((x16859 = x16859->nxt));
    else 
       x16859 = nullptr;
    if((x16859 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h16859== x16859->hash && !IDXFN16859::cmp(x6764, *x16859->obj)) {
          auto custEntry = x16859->obj;
          
          x16852.push_back(custEntry);
      } while((x16859 = x16859->nxt));
    };
    int x16863 = x16852.size();
    int x16865 = (x16863/(2));
    int x16873 = x16852.size();
    if(((x16873%(2))==(0))) {
      int x151 = x16865;
      x16865 = (x151-(1));
    };
    sort(x16852.begin(), x16852.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6805 = c1->_4;
      const PString& x6806 = c2->_4;
      return ((strcmpi(x6805.data_, x6806.data_))<(0)); 
    }));
    int x16881 = x16865;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16882 = x16852[x16881];
    ite16851 = x16882;
  } else {
    x6781._1 = x131;
    x6781._2 = x129;
    x6781._3 = x128;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16887 = customerTblIdx0.get(x6781);
    ite16851 = x16887;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6751 = ite16851;
  int x6752 = x6751->_3;
  x6754._2 = x129;
  x6754._3 = x128;
  x6754._4 = x6752;
  struct SEntry8_IIIITIIB* x11005 = orderTblIdx1.get(x6754);
  int x182 = 0;
  int x6757 = x11005->_1;
  x182 = x6757;
}
void PaymentTx(int x186, date x187, int x188, int x189, int x190, int x191, int x192, int x193, int x194, PString x195, double x196) {
  x6869._1 = x189;
  struct SEntry9_ISSSSSSDD* x11056 = warehouseTblIdx0.get(x6869);
  x11056->_9 += x196;
  x6874._1 = x190;
  x6874._2 = x189;
  struct SEntry11_IISSSSSSDDI* x11061 = districtTblIdx0.get(x6874);
  x11061->_10 += x196;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16956 = NULL;
  if((x191>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16957;
    x6914._2 = x193;
    x6914._3 = x192;
    x6914._6 = x195;
    //sliceRes 
    typedef typename customerTblIdx1Type::IFN IDXFN16964;
    HASH_RES_t h16964 = IDXFN16964::hash(x6914);
    auto* x16964 = &(customerTblIdx1.buckets_[h16964 % customerTblIdx1.size_]);
    if(x16964 -> obj)
       do if(h16964 == x16964->hash && !IDXFN16964::cmp(x6914, *x16964->obj))
         break;
       while((x16964 = x16964->nxt));
    else 
       x16964 = nullptr;
    if((x16964 == nullptr)) {
    } else {
      //sliceResMap 
       do if(h16964== x16964->hash && !IDXFN16964::cmp(x6914, *x16964->obj)) {
          auto custEntry = x16964->obj;
          
          x16957.push_back(custEntry);
      } while((x16964 = x16964->nxt));
    };
    int x16968 = x16957.size();
    int x16970 = (x16968/(2));
    int x16978 = x16957.size();
    if(((x16978%(2))==(0))) {
      int x227 = x16970;
      x16970 = (x227-(1));
    };
    sort(x16957.begin(), x16957.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      const PString& x6977 = c1->_4;
      const PString& x6978 = c2->_4;
      return ((strcmpi(x6977.data_, x6978.data_))<(0)); 
    }));
    int x16986 = x16970;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16987 = x16957[x16986];
    ite16956 = x16987;
  } else {
    x6931._1 = x194;
    x6931._2 = x193;
    x6931._3 = x192;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16992 = customerTblIdx0.get(x6931);
    ite16956 = x16992;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6879 = ite16956;
  const PString& x6880 = x6879->_21;
  const PString& x6881 = x6879->_14;
  char* x18342 = strstr(x6881.data_, "BC");
  if((x18342!=(NULL))) {
    int x6884 = x6879->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x6884, x193, x192, x190, x189, x196, IntToStrdate(x187), x6880.data_);
    x6879->_17 += x196;
    x6879->_21 = c_new_data;
  } else {
    x6879->_17 += x196;
  };
  const PString& x6891 = x11056->_2;
  const PString& x6892 = x11061->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x6891.data_, x6892.data_);
  int x6895 = x6879->_1;
  x6897._1 = x6895;
  x6897._2 = x193;
  x6897._3 = x192;
  x6897._4 = x190;
  x6897._5 = x189;
  x6897._6 = x187;
  x6897._7 = x196;
  x6897._8 = h_data;
  historyTbl.insert_nocheck(x6897);
}
void NewOrderTx(int x269, date x270, int x271, int x272, int x273, int x274, int x275, int x276, int* x277, int* x278, int* x279, double* x280, PString* x281, int* x282, PString* x283, double* x284) {
  int x286 = 0;
  int x289 = 0;
  PString idata[x275];
  int x294 = 1;
  while(1) {
    
    int x296 = x286;
    int ite17285 = 0;
    if((x296<(x275))) {
      
      int x298 = x294;
      int x17286 = x298;
      ite17285 = x17286;
    } else {
      ite17285 = 0;
    };
    int x17099 = ite17285;
    if (!(x17099)) break; 
    
    int x301 = x286;
    int x302 = x277[x301];
    x7086._1 = x302;
    struct SEntry5_IISDS* x11207 = itemTblIdx0.get(x7086);
    if((x11207==(NULL))) {
      x294 = 0;
    } else {
      int x308 = x286;
      const PString& x7092 = x11207->_3;
      x281[x308] = x7092;
      int x311 = x286;
      double x7095 = x11207->_4;
      x280[x311] = x7095;
      int x314 = x286;
      const PString& x7098 = x11207->_5;
      idata[x314] = x7098;
    };
    int x318 = x286;
    x286 = (x318+(1));
  };
  int x322 = x294;
  if(x322) {
    x7106._1 = x274;
    x7106._2 = x273;
    x7106._3 = x272;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11229 = customerTblIdx0.get(x7106);
    x7109._1 = x272;
    struct SEntry9_ISSSSSSDD* x11232 = warehouseTblIdx0.get(x7109);
    x7112._1 = x273;
    x7112._2 = x272;
    struct SEntry11_IISSSSSSDDI* x11236 = districtTblIdx0.get(x7112);
    int x7114 = x11236->_11;
    x11236->_11 += 1;
    x7119._1 = x7114;
    x7119._2 = x273;
    x7119._3 = x272;
    x7119._4 = x274;
    x7119._5 = x270;
    x7119._6 = -1;
    x7119._7 = x275;
    x7119._8 = (x276>(0));
    orderTbl.insert_nocheck(x7119);
    x7122._1 = x7114;
    x7122._2 = x273;
    x7122._3 = x272;
    newOrderTbl.insert_nocheck(x7122);
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
      x7136._1 = ol_i_id;
      x7136._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11269 = stockTblIdx0.get(x7136);
      PString ite17162 = PString();
      if((x273==(1))) {
        const PString& x17163 = x11269->_4;
        ite17162 = x17163;
      } else {
        PString ite17167 = PString();
        if((x273==(2))) {
          const PString& x17168 = x11269->_5;
          ite17167 = x17168;
        } else {
          PString ite17172 = PString();
          if((x273==(3))) {
            const PString& x17173 = x11269->_6;
            ite17172 = x17173;
          } else {
            PString ite17177 = PString();
            if((x273==(4))) {
              const PString& x17178 = x11269->_7;
              ite17177 = x17178;
            } else {
              PString ite17182 = PString();
              if((x273==(5))) {
                const PString& x17183 = x11269->_8;
                ite17182 = x17183;
              } else {
                PString ite17187 = PString();
                if((x273==(6))) {
                  const PString& x17188 = x11269->_9;
                  ite17187 = x17188;
                } else {
                  PString ite17192 = PString();
                  if((x273==(7))) {
                    const PString& x17193 = x11269->_10;
                    ite17192 = x17193;
                  } else {
                    PString ite17197 = PString();
                    if((x273==(8))) {
                      const PString& x17198 = x11269->_11;
                      ite17197 = x17198;
                    } else {
                      PString ite17202 = PString();
                      if((x273==(9))) {
                        const PString& x17203 = x11269->_12;
                        ite17202 = x17203;
                      } else {
                        const PString& x17205 = x11269->_13;
                        ite17202 = x17205;
                      };
                      PString x17201 = ite17202;
                      ite17197 = x17201;
                    };
                    PString x17196 = ite17197;
                    ite17192 = x17196;
                  };
                  PString x17191 = ite17192;
                  ite17187 = x17191;
                };
                PString x17186 = ite17187;
                ite17182 = x17186;
              };
              PString x17181 = ite17182;
              ite17177 = x17181;
            };
            PString x17176 = ite17177;
            ite17172 = x17176;
          };
          PString x17171 = ite17172;
          ite17167 = x17171;
        };
        PString x17166 = ite17167;
        ite17162 = x17166;
      };
      PString ol_dist_info = ite17162;
      int x7166 = x11269->_3;
      int x396 = x286;
      x282[x396] = x7166;
      int x398 = x286;
      PString& x399 = idata[x398];
      char* x18581 = strstr(x399.data_, "original");
      int ite17422 = 0;
      if((x18581!=(NULL))) {
        
        const PString& x7173 = x11269->_17;
        char* x18587 = strstr(x7173.data_, "original");
        int x17423 = (x18587!=(NULL));
        ite17422 = x17423;
      } else {
        ite17422 = 0;
      };
      int x17231 = ite17422;
      if(x17231) {
        int x404 = x286;
        x283[x404] = "B";
      } else {
        int x406 = x286;
        x283[x406] = "G";
      };
      x11269->_3 = (x7166-(ol_quantity));
      if((x7166<=(ol_quantity))) {
        x11269->_3 += 91;
      };
      int x415 = 0;
      if((ol_supply_w_id!=(x272))) {
        x415 = 1;
      };
      double x7190 = x11229->_16;
      double x7191 = x11232->_8;
      double x7192 = x11236->_9;
      int x428 = x286;
      double x429 = x280[x428];
      double ol_amount = ((ol_quantity*(x429))*(((1.0+(x7191))+(x7192))))*((1.0-(x7190)));
      int x437 = x286;
      x284[x437] = ol_amount;
      double x439 = x347;
      x347 = (x439+(ol_amount));
      int x442 = x286;
      x7210._1 = x7114;
      x7210._2 = x273;
      x7210._3 = x272;
      x7210._4 = (x442+(1));
      x7210._5 = ol_i_id;
      x7210._6 = ol_supply_w_id;
      x7210._8 = ol_quantity;
      x7210._9 = ol_amount;
      x7210._10 = ol_dist_info;
      orderLineTbl.insert_nocheck(x7210);
      int x447 = x286;
      x286 = (x447+(1));
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
      warehouseTblIdx0.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize);
  
      if (warehouseTblIdx0 == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (districtTblIdx0 == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (customerTblIdx0 == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orderTblIdx0 == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orderLineTblIdx0 == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (newOrderTblIdx0 == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (itemTblIdx0 == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (stockTblIdx0 == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (historyTblIdx0 == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
