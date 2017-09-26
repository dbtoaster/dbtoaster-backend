#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY false

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
#include <valgrind/callgrind.h>
#include <iomanip>
#include <fstream>
#include <locale>

#define EXEC_PROFILE 1
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

uint failedOS = 0;
uint failedDel = 0;
uint failedNO = 0;

const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
const size_t itemTblSize = 100000 * 1.5;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

const size_t districtTblArrayLengths[] = {1};
const size_t customerTblArrayLengths[] = {1,1};
const size_t itemTblArrayLengths[] = {1};
const size_t historyTblArrayLengths[] = {1};
const size_t orderTblArrayLengths[] = {1,1};
const size_t newOrderTblArrayLengths[] = {1,1};
const size_t warehouseTblArrayLengths[] = {1};
const size_t stockTblArrayLengths[] = {1};
const size_t orderLineTblArrayLengths[] = {1,1};

const size_t warehouseTblPoolSizes[] = {8, 0};
const size_t itemTblPoolSizes[] = {65536*2, 0};
const size_t districtTblPoolSizes[] = {16, 0};
const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
const size_t stockTblPoolSizes[] = {65536*2, 0};
const size_t historyTblPoolSizes[] = {262144*2, 65536};
     
 std::unordered_map<std::string, Timepoint> startTimes;
 std::unordered_map<std::string, size_t> durations;
 std::unordered_map<std::string, size_t> counters;
struct SEntry5_IISDS {
  int _1;  int _2;  PString _3;  double _4;  PString _5;  SEntry5_IISDS *prv;  SEntry5_IISDS *nxt; void* backPtrs[5];
  SEntry5_IISDS() :_1(-2147483648), _2(-2147483648), _3(), _4(-1.7976931348623157E308), _5(), prv(nullptr), nxt(nullptr) {}
  SEntry5_IISDS(const int& _1, const int& _2, const PString& _3, const double& _4, const PString& _5) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry5_IISDS* copy() const {  SEntry5_IISDS* ptr = (SEntry5_IISDS*) malloc(sizeof(SEntry5_IISDS)); new(ptr) SEntry5_IISDS(_1, _2, _3, _4, _5);  return ptr;}
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  SEntry11_IISSSSSSDDI *prv;  SEntry11_IISSSSSSDDI *nxt; void* backPtrs[11];
  SEntry11_IISSSSSSDDI() :_1(-2147483648), _2(-2147483648), _3(), _4(), _5(), _6(), _7(), _8(), _9(-1.7976931348623157E308), _10(-1.7976931348623157E308), _11(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI(const int& _1, const int& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const double& _9, const double& _10, const int& _11) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry11_IISSSSSSDDI* copy() const {  SEntry11_IISSSSSSDDI* ptr = (SEntry11_IISSSSSSDDI*) malloc(sizeof(SEntry11_IISSSSSSDDI)); new(ptr) SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11);  return ptr;}
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt; void* backPtrs[8];
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry8_IIIITIIB* copy() const {  SEntry8_IIIITIIB* ptr = (SEntry8_IIIITIIB*) malloc(sizeof(SEntry8_IIIITIIB)); new(ptr) SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry3_III* copy() const {  SEntry3_III* ptr = (SEntry3_III*) malloc(sizeof(SEntry3_III)); new(ptr) SEntry3_III(_1, _2, _3);  return ptr;}
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[21];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const {  SEntry21_IIISSSSSSSSSTSDDDDIIS* ptr = (SEntry21_IIISSSSSSSSSTSDDDDIIS*) malloc(sizeof(SEntry21_IIISSSSSSSSSTSDDDDIIS)); new(ptr) SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21);  return ptr;}
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry8_IIIIITDS* copy() const {  SEntry8_IIIIITDS* ptr = (SEntry8_IIIIITDS*) malloc(sizeof(SEntry8_IIIIITDS)); new(ptr) SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry10_IIIIIITIDS* copy() const {  SEntry10_IIIIIITIDS* ptr = (SEntry10_IIIIIITIDS*) malloc(sizeof(SEntry10_IIIIIITIDS)); new(ptr) SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);  return ptr;}
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry17_IIISSSSSSSSSSIIIS* copy() const {  SEntry17_IIISSSSSSSSSSIIIS* ptr = (SEntry17_IIISSSSSSSSSSIIIS*) malloc(sizeof(SEntry17_IIISSSSSSSSSSIIIS)); new(ptr) SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17);  return ptr;}
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  SEntry9_ISSSSSSDD *prv;  SEntry9_ISSSSSSDD *nxt; void* backPtrs[9];
  SEntry9_ISSSSSSDD() :_1(-2147483648), _2(), _3(), _4(), _5(), _6(), _7(), _8(-1.7976931348623157E308), _9(-1.7976931348623157E308), prv(nullptr), nxt(nullptr) {}
  SEntry9_ISSSSSSDD(const int& _1, const PString& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const double& _8, const double& _9) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry9_ISSSSSSDD* copy() const {  SEntry9_ISSSSSSDD* ptr = (SEntry9_ISSSSSSDD*) malloc(sizeof(SEntry9_ISSSSSSDD)); new(ptr) SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9);  return ptr;}
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
 struct SEntry10_IIIIIITIDS_Idx3214 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4209)  { 
    int x4210 = 0;
    int x4211 = x4210;
    x4210 = (x4211^(((((HASH((x4209._3)))+(-1640531527))+((x4211<<(6))))+((x4211>>(2))))));
    int x4221 = x4210;
    x4210 = (x4221^(((((HASH((x4209._2)))+(-1640531527))+((x4221<<(6))))+((x4221>>(2))))));
    int x4231 = x4210;
    x4210 = (x4231^(((((HASH((x4209._1)))+(-1640531527))+((x4231<<(6))))+((x4231>>(2))))));
    int x4241 = x4210;
    x4210 = (x4241^(((((HASH((x4209._4)))+(-1640531527))+((x4241<<(6))))+((x4241>>(2))))));
    int x4251 = x4210;
    return x4251; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4253, const struct SEntry10_IIIIIITIDS& x4254) { 
    int x4255 = 0;
    if(((x4253._3)==((x4254._3)))) {
      if(((x4253._2)==((x4254._2)))) {
        if(((x4253._1)==((x4254._1)))) {
          if(((x4253._4)==((x4254._4)))) {
            x4255 = 0;
          } else {
            x4255 = 1;
          };
        } else {
          x4255 = 1;
        };
      } else {
        x4255 = 1;
      };
    } else {
      x4255 = 1;
    };
    int x4277 = x4255;
    return x4277; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4121)  { 
    int x4122 = 0;
    int x4123 = x4122;
    x4122 = (x4123^(((((HASH((x4121._2)))+(-1640531527))+((x4123<<(6))))+((x4123>>(2))))));
    int x4133 = x4122;
    x4122 = (x4133^(((((HASH((x4121._3)))+(-1640531527))+((x4133<<(6))))+((x4133>>(2))))));
    int x4143 = x4122;
    x4122 = (x4143^(((((HASH((x4121._4)))+(-1640531527))+((x4143<<(6))))+((x4143>>(2))))));
    int x4153 = x4122;
    return x4153; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4155, const struct SEntry8_IIIITIIB& x4156) { 
    int x4157 = 0;
    if(((x4155._2)==((x4156._2)))) {
      if(((x4155._3)==((x4156._3)))) {
        if(((x4155._4)==((x4156._4)))) {
          x4157 = 0;
        } else {
          x4157 = 1;
        };
      } else {
        x4157 = 1;
      };
    } else {
      x4157 = 1;
    };
    int x4174 = x4157;
    return x4174; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4021)  { 
    int x4022 = 0;
    int x4023 = x4022;
    x4022 = (x4023^(((((HASH((x4021._3)))+(-1640531527))+((x4023<<(6))))+((x4023>>(2))))));
    int x4033 = x4022;
    x4022 = (x4033^(((((HASH((x4021._2)))+(-1640531527))+((x4033<<(6))))+((x4033>>(2))))));
    int x4043 = x4022;
    x4022 = (x4043^(((((HASH((x4021._1)))+(-1640531527))+((x4043<<(6))))+((x4043>>(2))))));
    int x4053 = x4022;
    return x4053; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4055, const struct SEntry8_IIIITIIB& x4056) { 
    int x4057 = 0;
    if(((x4055._3)==((x4056._3)))) {
      if(((x4055._2)==((x4056._2)))) {
        if(((x4055._1)==((x4056._1)))) {
          x4057 = 0;
        } else {
          x4057 = 1;
        };
      } else {
        x4057 = 1;
      };
    } else {
      x4057 = 1;
    };
    int x4074 = x4057;
    return x4074; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3844)  { 
    int x3845 = 0;
    int x3846 = x3845;
    x3845 = (x3846^(((((HASH((x3844._1)))+(-1640531527))+((x3846<<(6))))+((x3846>>(2))))));
    int x3856 = x3845;
    x3845 = (x3856^(((((HASH((x3844._2)))+(-1640531527))+((x3856<<(6))))+((x3856>>(2))))));
    int x3866 = x3845;
    x3845 = (x3866^(((((HASH((x3844._3)))+(-1640531527))+((x3866<<(6))))+((x3866>>(2))))));
    int x3876 = x3845;
    x3845 = (x3876^(((((HASH((x3844._4)))+(-1640531527))+((x3876<<(6))))+((x3876>>(2))))));
    int x3886 = x3845;
    x3845 = (x3886^(((((HASH((x3844._5)))+(-1640531527))+((x3886<<(6))))+((x3886>>(2))))));
    int x3896 = x3845;
    x3845 = (x3896^(((((HASH((x3844._6)))+(-1640531527))+((x3896<<(6))))+((x3896>>(2))))));
    int x3906 = x3845;
    x3845 = (x3906^(((((HASH((x3844._7)))+(-1640531527))+((x3906<<(6))))+((x3906>>(2))))));
    int x3916 = x3845;
    x3845 = (x3916^(((((HASH((x3844._8)))+(-1640531527))+((x3916<<(6))))+((x3916>>(2))))));
    int x3926 = x3845;
    return x3926; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3928, const struct SEntry8_IIIIITDS& x3929) { 
    int x3930 = 0;
    if(((x3928._1)==((x3929._1)))) {
      if(((x3928._2)==((x3929._2)))) {
        if(((x3928._3)==((x3929._3)))) {
          if(((x3928._4)==((x3929._4)))) {
            if(((x3928._5)==((x3929._5)))) {
              if(((x3928._6)==((x3929._6)))) {
                if(((x3928._7)==((x3929._7)))) {
                  if(((x3928._8)==((x3929._8)))) {
                    x3930 = 0;
                  } else {
                    x3930 = 1;
                  };
                } else {
                  x3930 = 1;
                };
              } else {
                x3930 = 1;
              };
            } else {
              x3930 = 1;
            };
          } else {
            x3930 = 1;
          };
        } else {
          x3930 = 1;
        };
      } else {
        x3930 = 1;
      };
    } else {
      x3930 = 1;
    };
    int x3972 = x3930;
    return x3972; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4280)  { 
    int x4281 = 0;
    int x4282 = x4281;
    x4281 = (x4282^(((((HASH((x4280._1)))+(-1640531527))+((x4282<<(6))))+((x4282>>(2))))));
    int x4292 = x4281;
    x4281 = (x4292^(((((HASH((x4280._2)))+(-1640531527))+((x4292<<(6))))+((x4292>>(2))))));
    int x4302 = x4281;
    x4281 = (x4302^(((((HASH((x4280._3)))+(-1640531527))+((x4302<<(6))))+((x4302>>(2))))));
    int x4312 = x4281;
    return x4312; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4314, const struct SEntry10_IIIIIITIDS& x4315) { 
    int x4316 = 0;
    if(((x4314._1)==((x4315._1)))) {
      if(((x4314._2)==((x4315._2)))) {
        if(((x4314._3)==((x4315._3)))) {
          x4316 = 0;
        } else {
          x4316 = 1;
        };
      } else {
        x4316 = 1;
      };
    } else {
      x4316 = 1;
    };
    int x4333 = x4316;
    return x4333; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3796)  { 
    int x3797 = 0;
    int x3798 = x3797;
    x3797 = (x3798^(((((HASH((x3796._2)))+(-1640531527))+((x3798<<(6))))+((x3798>>(2))))));
    int x3808 = x3797;
    x3797 = (x3808^(((((HASH((x3796._3)))+(-1640531527))+((x3808<<(6))))+((x3808>>(2))))));
    int x3818 = x3797;
    return x3818; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3820, const struct SEntry3_III& x3821) { 
    int x3822 = 0;
    if(((x3820._2)==((x3821._2)))) {
      if(((x3820._3)==((x3821._3)))) {
        x3822 = 0;
      } else {
        x3822 = 1;
      };
    } else {
      x3822 = 1;
    };
    int x3834 = x3822;
    return x3834; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3706)  { 
    int x3707 = 0;
    int x3708 = x3707;
    x3707 = (x3708^(((((HASH((x3706._3)))+(-1640531527))+((x3708<<(6))))+((x3708>>(2))))));
    int x3718 = x3707;
    x3707 = (x3718^(((((HASH((x3706._2)))+(-1640531527))+((x3718<<(6))))+((x3718>>(2))))));
    int x3728 = x3707;
    x3707 = (x3728^(((((HASH((x3706._1)))+(-1640531527))+((x3728<<(6))))+((x3728>>(2))))));
    int x3738 = x3707;
    return x3738; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3740, const struct SEntry3_III& x3741) { 
    int x3742 = 0;
    if(((x3740._3)==((x3741._3)))) {
      if(((x3740._2)==((x3741._2)))) {
        if(((x3740._1)==((x3741._1)))) {
          x3742 = 0;
        } else {
          x3742 = 1;
        };
      } else {
        x3742 = 1;
      };
    } else {
      x3742 = 1;
    };
    int x3759 = x3742;
    return x3759; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4416)  { 
    int x4417 = 0;
    int x4418 = x4417;
    x4417 = (x4418^(((((HASH((x4416._2)))+(-1640531527))+((x4418<<(6))))+((x4418>>(2))))));
    int x4428 = x4417;
    x4417 = (x4428^(((((HASH((x4416._3)))+(-1640531527))+((x4428<<(6))))+((x4428>>(2))))));
    int x4438 = x4417;
    x4417 = (x4438^(((((HASH((x4416._6)))+(-1640531527))+((x4438<<(6))))+((x4438>>(2))))));
    int x4448 = x4417;
    return x4448; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4450, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4451) { 
    int x4452 = 0;
    if(((x4450._2)==((x4451._2)))) {
      if(((x4450._3)==((x4451._3)))) {
        if(((x4450._6)==((x4451._6)))) {
          x4452 = 0;
        } else {
          x4452 = 1;
        };
      } else {
        x4452 = 1;
      };
    } else {
      x4452 = 1;
    };
    int x4469 = x4452;
    return x4469; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3762)  { 
    int x3763 = 0;
    int x3764 = x3763;
    x3763 = (x3764^(((((HASH((x3762._2)))+(-1640531527))+((x3764<<(6))))+((x3764>>(2))))));
    int x3774 = x3763;
    x3763 = (x3774^(((((HASH((x3762._3)))+(-1640531527))+((x3774<<(6))))+((x3774>>(2))))));
    int x3784 = x3763;
    return x3784; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3786, const struct SEntry3_III& x3787) { 
    int x3788 = x3786._1;
    int x3789 = x3787._1;
    return ((x3788==(x3789)) ? 0 : ((x3788>(x3789)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4371)  { 
    int x4372 = 0;
    int x4373 = x4372;
    x4372 = (x4373^(((((HASH((x4371._2)))+(-1640531527))+((x4373<<(6))))+((x4373>>(2))))));
    int x4383 = x4372;
    x4372 = (x4383^(((((HASH((x4371._3)))+(-1640531527))+((x4383<<(6))))+((x4383>>(2))))));
    int x4393 = x4372;
    x4372 = (x4393^(((((HASH((x4371._6)))+(-1640531527))+((x4393<<(6))))+((x4393>>(2))))));
    int x4403 = x4372;
    return x4403; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4405, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4406) { 
    int x4409 = strcmpi((x4405._4).data_, (x4406._4).data_);
    return ((x4409>(0)) ? 1 : ((x4409<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4077)  { 
    int x4078 = 0;
    int x4079 = x4078;
    x4078 = (x4079^(((((HASH((x4077._2)))+(-1640531527))+((x4079<<(6))))+((x4079>>(2))))));
    int x4089 = x4078;
    x4078 = (x4089^(((((HASH((x4077._3)))+(-1640531527))+((x4089<<(6))))+((x4089>>(2))))));
    int x4099 = x4078;
    x4078 = (x4099^(((((HASH((x4077._4)))+(-1640531527))+((x4099<<(6))))+((x4099>>(2))))));
    int x4109 = x4078;
    return x4109; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4111, const struct SEntry8_IIIITIIB& x4112) { 
    int x4113 = x4111._1;
    int x4114 = x4112._1;
    return ((x4113==(x4114)) ? 0 : ((x4113>(x4114)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t6 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3983)  { 
    int x3984 = 0;
    int x3987 = x3984;
    x3984 = ((x3987*(5))+(((x3983._1)-(1))));
    int x3991 = x3984;
    return x3991; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3980, const struct SEntry9_ISSSSSSDD& x3981) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4187)  { 
    int x4188 = 0;
    int x4191 = x4188;
    x4188 = ((x4191*(5))+(((x4187._2)-(1))));
    int x4197 = x4188;
    x4188 = ((x4197*(10))+(((x4187._1)-(1))));
    int x4201 = x4188;
    return x4201; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4184, const struct SEntry11_IISSSSSSDDI& x4185) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100002 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x4002)  { 
    int x4003 = 0;
    int x4006 = x4003;
    x4003 = ((x4006*(100001))+(((x4002._1)-(1))));
    int x4010 = x4003;
    return x4010; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3999, const struct SEntry5_IISDS& x4000) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4348)  { 
    int x4349 = 0;
    int x4352 = x4349;
    x4349 = ((x4352*(5))+(((x4348._3)-(1))));
    int x4358 = x4349;
    x4349 = ((x4358*(10))+(((x4348._2)-(1))));
    int x4364 = x4349;
    x4349 = ((x4364*(3000))+(((x4348._1)-(1))));
    int x4368 = x4349;
    return x4368; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4345, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4346) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4482)  { 
    int x4483 = 0;
    int x4486 = x4483;
    x4483 = ((x4486*(5))+(((x4482._2)-(1))));
    int x4492 = x4483;
    x4483 = ((x4492*(100000))+(((x4482._1)-(1))));
    int x4496 = x4483;
    return x4496; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4479, const struct SEntry17_IIISSSSSSSSSSIIIS& x4480) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx321, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_1, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,historyTblIdx0Type> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t6, 5> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,warehouseTblIdx0Type> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100002, 100001> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,itemTblIdx0Type> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx321, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_1, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11, 50> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,districtTblIdx0Type> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx3214, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001, 150000> customerTblIdx0Type;
typedef SlicedMedHeapIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001, 500000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,stockTblIdx0Type> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];

struct SEntry10_IIIIIITIDS x7187;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7350;
struct SEntry9_ISSSSSSDD x6910;
struct SEntry3_III x7125;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7565;
struct SEntry10_IIIIIITIDS x7346;
struct SEntry17_IIISSSSSSSSSSIIIS x7505;
struct SEntry9_ISSSSSSDD x7112;
struct SEntry8_IIIITIIB x7122;
struct SEntry3_III x7326;
struct SEntry11_IISSSSSSDDI x6915;
struct SEntry8_IIIIITDS x6957;
struct SEntry11_IISSSSSSDDI x7472;
struct SEntry10_IIIIIITIDS x7485;
struct SEntry8_IIIITIIB x7337;
struct SEntry17_IIISSSSSSSSSSIIIS x7139;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7109;
struct SEntry5_IISDS x7089;
struct SEntry10_IIIIIITIDS x7560;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6975;
struct SEntry8_IIIITIIB x7550;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7568;
struct SEntry11_IISSSSSSDDI x7115;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6972;


FORCE_INLINE void PaymentTx(int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
auto startPaymentTx = Now;
  x6910._1 = x19;
  struct SEntry9_ISSSSSSDD* x11103 = warehouseTblIdx0.get(x6910);
  x11103->_9 += x26;
  x6915._1 = x20;
  x6915._2 = x19;
  struct SEntry11_IISSSSSSDDI* x11109 = districtTblIdx0.get(x6915);
  x11109->_10 += x26;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite24714 = 0;
  if((x21>(0))) {
    x6972._2 = x23;
    x6972._3 = x22;
    x6972._6 = x25;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x24718 = customerTblIdx1.get(x6972);
    ite24714 = x24718;
  } else {
    x6975._1 = x24;
    x6975._2 = x23;
    x6975._3 = x22;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x24723 = customerTblIdx0.get(x6975);
    ite24714 = x24723;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6920 = ite24714;
  char* x25866 = strstr((x6920->_14).data_, "BC");
  if((x25866!=(NULL))) {
    PString x1586 = PString(500);
    x1586.append((x6920->_1));
    x1586.append(' ');
    x1586.append(x23);
    x1586.append(' ');
    x1586.append(x22);
    x1586.append(' ');
    x1586.append(x20);
    x1586.append(' ');
    x1586.append(x19);
    x1586.append(' ');
    x1586.append('$');
    x1586.append(x26);
    x1586.append(' ');
    x1586.appendDate(x17);
    x1586.append(' ');
    x1586.append('|');
    x1586.append(' ');
    x1586.append((x6920->_21).data_, 500);
    x6920->_17 += x26;
    x6920->_21 = x1586;
  } else {
    x6920->_17 += x26;
  };
  PString x1612 = PString(24);
  x1612.append((x11103->_2).data_, 10);
  x1612.append("    ", 4);
  x1612.append((x11109->_3).data_, 10);
  x6957._1 = (x6920->_1);
  x6957._2 = x23;
  x6957._3 = x22;
  x6957._4 = x20;
  x6957._5 = x19;
  x6957._6 = x17;
  x6957._7 = x26;
  x6957._8 = x1612;
  historyTbl.insert_nocheck(x6957);
  clearTempMem();
auto endPaymentTx = Now;
if(durations.find("PaymentTx") == durations.end()) {
  durations["PaymentTx"] = DurationNS(endPaymentTx - startPaymentTx);
  counters["PaymentTx"] = 1;
} else  {
  durations["PaymentTx"] += DurationNS(endPaymentTx- startPaymentTx);
  counters["PaymentTx"]++;
}
}
FORCE_INLINE void NewOrderTx(int x78, date x79, int x80, int x81, int x82, int x83, int x84, int x85, int* x86, int* x87, int* x88, double* x89, PString* x90, int* x91, PString* x92, double* x93) {
auto startNewOrderTx = Now;
  int x95 = 0;
  int x98 = 0;
  PString idata[x84];
  int x103 = 1;
  int x106 = 1;
  while(1) {
    
    int x108 = x95;
    int ite24974 = 0;
    if((x108<(x84))) {
      
      int x110 = x103;
      int x24975 = x110;
      ite24974 = x24975;
    } else {
      ite24974 = 0;
    };
    int x24842 = ite24974;
    if (!(x24842)) break; 
    
    int x113 = x95;
    int supwid = x87[x113];
    if((supwid!=(x81))) {
      x106 = 0;
    };
    int x119 = x95;
    int x120 = x86[x119];
    x7089._1 = x120;
    struct SEntry5_IISDS* x11258 = itemTblIdx0.get(x7089);
    if((x11258==(NULL))) {
      x103 = 0;
    } else {
      int x126 = x95;
      x90[x126] = (x11258->_3);
      int x129 = x95;
      x89[x129] = (x11258->_4);
      int x132 = x95;
      idata[x132] = (x11258->_5);
    };
    int x136 = x95;
    x95 = (x136+(1));
  };
  int x140 = x103;
  if(x140) {
    x7109._1 = x83;
    x7109._2 = x82;
    x7109._3 = x81;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11280 = customerTblIdx0.get(x7109);
    x7112._1 = x81;
    struct SEntry9_ISSSSSSDD* x11283 = warehouseTblIdx0.get(x7112);
    x7115._1 = x82;
    x7115._2 = x81;
    struct SEntry11_IISSSSSSDDI* x11287 = districtTblIdx0.get(x7115);
    int x7117 = x11287->_11;
    x11287->_11 += 1;
    int x157 = x106;
    x7122._1 = x7117;
    x7122._2 = x82;
    x7122._3 = x81;
    x7122._4 = x83;
    x7122._5 = x79;
    x7122._6 = -1;
    x7122._7 = x84;
    x7122._8 = x157;
    orderTbl.insert_nocheck(x7122);
    x7125._1 = x7117;
    x7125._2 = x82;
    x7125._3 = x81;
    newOrderTbl.insert_nocheck(x7125);
    double x165 = 0.0;
    x95 = 0;
    while(1) {
      
      int x168 = x95;
      if (!((x168<(x84)))) break; 
      
      int x171 = x95;
      int ol_supply_w_id = x87[x171];
      int x174 = x95;
      int ol_i_id = x86[x174];
      int x177 = x95;
      int ol_quantity = x88[x177];
      x7139._1 = ol_i_id;
      x7139._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11321 = stockTblIdx0.get(x7139);
      const PString& x7142 = *(&x11321->_4 + (x82-1));
      int x7143 = x11321->_3;
      int x188 = x95;
      x91[x188] = x7143;
      int x190 = x95;
      PString& x191 = idata[x190];
      char* x26059 = strstr(x191.data_, "original");
      int ite25053 = 0;
      if((x26059!=(NULL))) {
        
        char* x26065 = strstr((x11321->_17).data_, "original");
        int x25054 = (x26065!=(NULL));
        ite25053 = x25054;
      } else {
        ite25053 = 0;
      };
      int x24916 = ite25053;
      if(x24916) {
        int x196 = x95;
        x92[x196].data_[0] = 'B';
      } else {
        int x198 = x95;
        x92[x198].data_[0] = 'G';
      };
      x11321->_3 = (x7143-(ol_quantity));
      if((x7143<=(ol_quantity))) {
        x11321->_3 += 91;
      };
      int x207 = 0;
      if((ol_supply_w_id!=(x81))) {
        x207 = 1;
      };
      int x220 = x95;
      double x221 = x89[x220];
      double ol_amount = ((ol_quantity*(x221))*(((1.0+((x11283->_8)))+((x11287->_9)))))*((1.0-((x11280->_16))));
      int x229 = x95;
      x93[x229] = ol_amount;
      double x231 = x165;
      x165 = (x231+(ol_amount));
      int x234 = x95;
      x7187._1 = x7117;
      x7187._2 = x82;
      x7187._3 = x81;
      x7187._4 = (x234+(1));
      x7187._5 = ol_i_id;
      x7187._6 = ol_supply_w_id;
      x7187._8 = ol_quantity;
      x7187._9 = ol_amount;
      x7187._10 = x7142;
      orderLineTbl.insert_nocheck(x7187);
      int x239 = x95;
      x95 = (x239+(1));
    };
  } else {
    int x243 = failedNO;
    failedNO = (1+(x243));
  };
  clearTempMem();
auto endNewOrderTx = Now;
if(durations.find("NewOrderTx") == durations.end()) {
  durations["NewOrderTx"] = DurationNS(endNewOrderTx - startNewOrderTx);
  counters["NewOrderTx"] = 1;
} else  {
  durations["NewOrderTx"] += DurationNS(endNewOrderTx- startNewOrderTx);
  counters["NewOrderTx"]++;
}
}
FORCE_INLINE void DeliveryTx(int x247, date x248, int x249, int x250) {
auto startDeliveryTx = Now;
  int orderIDs[10];
  int x255 = 1;
  while(1) {
    
    int x257 = x255;
    if (!((x257<=(10)))) break; 
    
    int x264 = x255;
    x7326._2 = x264;
    x7326._3 = x249;
    struct SEntry3_III* x11538 = newOrderTblIdx1.get(x7326);
    if((x11538!=(NULL))) {
      int x7330 = x11538->_1;
      int x273 = x255;
      orderIDs[(x273-(1))] = x7330;
      newOrderTbl.del(x11538);
      int x278 = x255;
      x7337._1 = x7330;
      x7337._2 = x278;
      x7337._3 = x249;
      struct SEntry8_IIIITIIB* x11551 = orderTblIdx0.get(x7337);
      x11551->_6 = x250;
      double x287 = 0.0;
      int x289 = x255;
      x7346._1 = x7330;
      x7346._2 = x289;
      x7346._3 = x249;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN15220;
      HASH_RES_t h15220 = IDXFN15220::hash(x7346);
      auto* x15220 = &(orderLineTblIdx1.buckets_[h15220 % orderLineTblIdx1.size_]);
      if(x15220 -> head.obj) {
         do {
           if(h15220 == x15220->hash && !IDXFN15220::cmp(x7346, *x15220->head.obj))
             break;
         } while((x15220 = x15220->nxt));
      } else { 
         x15220 = nullptr;
      }
      if((x15220 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx15220 = &x15220->head;
        do {
          auto orderLineEntry = nx15220->obj;
          orderLineEntry->_7 = x248;
          double x294 = x287;
          x287 = (x294+((orderLineEntry->_9)));
        } while((nx15220 = nx15220->nxt));
      };
      int x302 = x255;
      x7350._1 = (x11551->_4);
      x7350._2 = x302;
      x7350._3 = x249;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11577 = customerTblIdx0.get(x7350);
      double x306 = x287;
      x11577->_17 += x306;
      x11577->_20 += 1;
    } else {
      int x310 = failedDel;
      failedDel = (1+(x310));
      int x313 = x255;
      orderIDs[(x313-(1))] = 0;
    };
    int x317 = x255;
    x255 = (x317+(1));
  };
  clearTempMem();
auto endDeliveryTx = Now;
if(durations.find("DeliveryTx") == durations.end()) {
  durations["DeliveryTx"] = DurationNS(endDeliveryTx - startDeliveryTx);
  counters["DeliveryTx"] = 1;
} else  {
  durations["DeliveryTx"] += DurationNS(endDeliveryTx- startDeliveryTx);
  counters["DeliveryTx"]++;
}
}
FORCE_INLINE void StockLevelTx(int x321, date x322, int x323, int x324, int x325, int x326) {
auto startStockLevelTx = Now;
  x7472._1 = x325;
  x7472._2 = x324;
  struct SEntry11_IISSSSSSDDI* x11658 = districtTblIdx0.get(x7472);
  int x7474 = x11658->_11;
  int x335 = (x7474-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x340 = x335;
    if (!((x340<(x7474)))) break; 
    
    int x342 = x335;
    x7485._1 = x342;
    x7485._2 = x325;
    x7485._3 = x324;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN15270;
    HASH_RES_t h15270 = IDXFN15270::hash(x7485);
    auto* x15270 = &(orderLineTblIdx1.buckets_[h15270 % orderLineTblIdx1.size_]);
    if(x15270 -> head.obj) {
       do {
         if(h15270 == x15270->hash && !IDXFN15270::cmp(x7485, *x15270->head.obj))
           break;
       } while((x15270 = x15270->nxt));
    } else { 
       x15270 = nullptr;
    }
    if((x15270 == nullptr)) {
    } else {
      //sliceResMapNoUpd 
      auto* nx15270 = &x15270->head;
      do {
        auto orderLineEntry = nx15270->obj;
        int x7503 = orderLineEntry->_5;
        x7505._1 = x7503;
        x7505._2 = x324;
        struct SEntry17_IIISSSSSSSSSSIIIS* x11673 = stockTblIdx0.get(x7505);
        if(((x11673->_3)<(x326))) {
          unique_ol_i_id.insert(x7503);
        };
      } while((nx15270 = nx15270->nxt));
    };
    int x359 = x335;
    x335 = (x359+(1));
  };
  clearTempMem();
auto endStockLevelTx = Now;
if(durations.find("StockLevelTx") == durations.end()) {
  durations["StockLevelTx"] = DurationNS(endStockLevelTx - startStockLevelTx);
  counters["StockLevelTx"] = 1;
} else  {
  durations["StockLevelTx"] += DurationNS(endStockLevelTx- startStockLevelTx);
  counters["StockLevelTx"]++;
}
}
FORCE_INLINE void OrderStatusTx(int x365, date x366, int x367, int x368, int x369, int x370, int x371, PString x372) {
auto startOrderStatusTx = Now;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite25341 = 0;
  if((x370>(0))) {
    x7565._2 = x369;
    x7565._3 = x368;
    x7565._6 = x372;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x25345 = customerTblIdx1.get(x7565);
    ite25341 = x25345;
  } else {
    x7568._1 = x371;
    x7568._2 = x369;
    x7568._3 = x368;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x25350 = customerTblIdx0.get(x7568);
    ite25341 = x25350;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7547 = ite25341;
  x7550._2 = x369;
  x7550._3 = x368;
  x7550._4 = (x7547->_3);
  struct SEntry8_IIIITIIB* x11736 = orderTblIdx1.get(x7550);
  int ite25360 = 0;
  if((x11736==(NULL))) {
    int x25361 = failedOS;
    failedOS = (1+(x25361));
    ite25360 = 0;
  } else {
    x7560._1 = (x11736->_1);
    x7560._2 = x369;
    x7560._3 = x368;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN25369;
    HASH_RES_t h25369 = IDXFN25369::hash(x7560);
    auto* x25369 = &(orderLineTblIdx1.buckets_[h25369 % orderLineTblIdx1.size_]);
    if(x25369 -> head.obj) {
       do {
         if(h25369 == x25369->hash && !IDXFN25369::cmp(x7560, *x25369->head.obj))
           break;
       } while((x25369 = x25369->nxt));
    } else { 
       x25369 = nullptr;
    }
    if((x25369 == nullptr)) {
    } else {
      //sliceResMapNoUpd 
      auto* nx25369 = &x25369->head;
      do {
        auto orderLineEntry = nx25369->obj;
        int x410 = 1;
      } while((nx25369 = nx25369->nxt));
    };
    ite25360 = 1;
  };
  int x414 = ite25360;
  clearTempMem();
auto endOrderStatusTx = Now;
if(durations.find("OrderStatusTx") == durations.end()) {
  durations["OrderStatusTx"] = DurationNS(endOrderStatusTx - startOrderStatusTx);
  counters["OrderStatusTx"] = 1;
} else  {
  durations["OrderStatusTx"] += DurationNS(endOrderStatusTx- startOrderStatusTx);
  counters["OrderStatusTx"]++;
}
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  #ifndef NORESIZE
  cout << "Index Resizing warning disabled" << endl;
  #endif
  
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
  //CALLGRIND_START_INSTRUMENTATION;
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
  //CALLGRIND_STOP_INSTRUMENTATION;
  //CALLGRIND_DUMP_STATS;
  auto end = Now;
  auto execTime = DurationMS(end - start);
  cout << "Failed NO = " << failedNO << endl;
  cout << "Failed Del = " << failedDel << endl;
  cout << "Failed OS = " << failedOS << endl;
  cout << "Total time = " << execTime << " ms" << endl;
  uint failedCount[] = {failedNO, 0, failedOS, failedDel/10, 0};
  cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  xactCounts[0]  << endl;
  cout << "TpmC = " << fixed <<  (xactCounts[0] - failedNO)* 60000.0/execTime << endl;
  
  //counters["FailedNO"] = failedNO; counters["FailedDel"] = failedDel/10; counters["FailedOS"] = failedOS;
  //durations["FailedNO"] = 0; durations["FailedDel"] = 0; durations["FailedOS"] = 0;
  ExecutionProfiler::printProfileToFile();
              
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABCDEFGILNOQRSUVXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/sem4/DDBToaster/runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx1, info);
  info << "\n}\n";
  info.close();
  
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
