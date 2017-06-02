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
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt; void* backPtrs[8];
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry8_IIIITIIB* copy() const {  SEntry8_IIIITIIB* ptr = (SEntry8_IIIITIIB*) malloc(sizeof(SEntry8_IIIITIIB)); new(ptr) SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
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
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3468)  { 
    int x3469 = 0;
    int x3470 = x3469;
    x3469 = (x3470^(((((HASH((x3468._2)))+(-1640531527))+((x3470<<(6))))+((x3470>>(2))))));
    int x3480 = x3469;
    x3469 = (x3480^(((((HASH((x3468._3)))+(-1640531527))+((x3480<<(6))))+((x3480>>(2))))));
    int x3490 = x3469;
    x3469 = (x3490^(((((HASH((x3468._4)))+(-1640531527))+((x3490<<(6))))+((x3490>>(2))))));
    int x3500 = x3469;
    return x3500; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3502, const struct SEntry8_IIIITIIB& x3503) { 
    int x3504 = 0;
    if(((x3502._2)==((x3503._2)))) {
      if(((x3502._3)==((x3503._3)))) {
        if(((x3502._4)==((x3503._4)))) {
          x3504 = 0;
        } else {
          x3504 = 1;
        };
      } else {
        x3504 = 1;
      };
    } else {
      x3504 = 1;
    };
    int x3521 = x3504;
    return x3521; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx3214 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3576)  { 
    int x3577 = 0;
    int x3578 = x3577;
    x3577 = (x3578^(((((HASH((x3576._3)))+(-1640531527))+((x3578<<(6))))+((x3578>>(2))))));
    int x3588 = x3577;
    x3577 = (x3588^(((((HASH((x3576._2)))+(-1640531527))+((x3588<<(6))))+((x3588>>(2))))));
    int x3598 = x3577;
    x3577 = (x3598^(((((HASH((x3576._1)))+(-1640531527))+((x3598<<(6))))+((x3598>>(2))))));
    int x3608 = x3577;
    x3577 = (x3608^(((((HASH((x3576._4)))+(-1640531527))+((x3608<<(6))))+((x3608>>(2))))));
    int x3618 = x3577;
    return x3618; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3620, const struct SEntry10_IIIIIITIDS& x3621) { 
    int x3622 = 0;
    if(((x3620._3)==((x3621._3)))) {
      if(((x3620._2)==((x3621._2)))) {
        if(((x3620._1)==((x3621._1)))) {
          if(((x3620._4)==((x3621._4)))) {
            x3622 = 0;
          } else {
            x3622 = 1;
          };
        } else {
          x3622 = 1;
        };
      } else {
        x3622 = 1;
      };
    } else {
      x3622 = 1;
    };
    int x3644 = x3622;
    return x3644; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3709)  { 
    int x3710 = 0;
    int x3711 = x3710;
    x3710 = (x3711^(((((HASH((x3709._3)))+(-1640531527))+((x3711<<(6))))+((x3711>>(2))))));
    int x3721 = x3710;
    x3710 = (x3721^(((((HASH((x3709._2)))+(-1640531527))+((x3721<<(6))))+((x3721>>(2))))));
    int x3731 = x3710;
    x3710 = (x3731^(((((HASH((x3709._1)))+(-1640531527))+((x3731<<(6))))+((x3731>>(2))))));
    int x3741 = x3710;
    return x3741; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3743, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3744) { 
    int x3745 = 0;
    if(((x3743._3)==((x3744._3)))) {
      if(((x3743._2)==((x3744._2)))) {
        if(((x3743._1)==((x3744._1)))) {
          x3745 = 0;
        } else {
          x3745 = 1;
        };
      } else {
        x3745 = 1;
      };
    } else {
      x3745 = 1;
    };
    int x3762 = x3745;
    return x3762; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3215)  { 
    int x3216 = 0;
    int x3217 = x3216;
    x3216 = (x3217^(((((HASH((x3215._1)))+(-1640531527))+((x3217<<(6))))+((x3217>>(2))))));
    int x3227 = x3216;
    x3216 = (x3227^(((((HASH((x3215._2)))+(-1640531527))+((x3227<<(6))))+((x3227>>(2))))));
    int x3237 = x3216;
    x3216 = (x3237^(((((HASH((x3215._3)))+(-1640531527))+((x3237<<(6))))+((x3237>>(2))))));
    int x3247 = x3216;
    x3216 = (x3247^(((((HASH((x3215._4)))+(-1640531527))+((x3247<<(6))))+((x3247>>(2))))));
    int x3257 = x3216;
    x3216 = (x3257^(((((HASH((x3215._5)))+(-1640531527))+((x3257<<(6))))+((x3257>>(2))))));
    int x3267 = x3216;
    x3216 = (x3267^(((((HASH((x3215._6)))+(-1640531527))+((x3267<<(6))))+((x3267>>(2))))));
    int x3277 = x3216;
    x3216 = (x3277^(((((HASH((x3215._7)))+(-1640531527))+((x3277<<(6))))+((x3277>>(2))))));
    int x3287 = x3216;
    x3216 = (x3287^(((((HASH((x3215._8)))+(-1640531527))+((x3287<<(6))))+((x3287>>(2))))));
    int x3297 = x3216;
    return x3297; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3299, const struct SEntry8_IIIIITDS& x3300) { 
    int x3301 = 0;
    if(((x3299._1)==((x3300._1)))) {
      if(((x3299._2)==((x3300._2)))) {
        if(((x3299._3)==((x3300._3)))) {
          if(((x3299._4)==((x3300._4)))) {
            if(((x3299._5)==((x3300._5)))) {
              if(((x3299._6)==((x3300._6)))) {
                if(((x3299._7)==((x3300._7)))) {
                  if(((x3299._8)==((x3300._8)))) {
                    x3301 = 0;
                  } else {
                    x3301 = 1;
                  };
                } else {
                  x3301 = 1;
                };
              } else {
                x3301 = 1;
              };
            } else {
              x3301 = 1;
            };
          } else {
            x3301 = 1;
          };
        } else {
          x3301 = 1;
        };
      } else {
        x3301 = 1;
      };
    } else {
      x3301 = 1;
    };
    int x3343 = x3301;
    return x3343; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3412)  { 
    int x3413 = 0;
    int x3414 = x3413;
    x3413 = (x3414^(((((HASH((x3412._3)))+(-1640531527))+((x3414<<(6))))+((x3414>>(2))))));
    int x3424 = x3413;
    x3413 = (x3424^(((((HASH((x3412._2)))+(-1640531527))+((x3424<<(6))))+((x3424>>(2))))));
    int x3434 = x3413;
    x3413 = (x3434^(((((HASH((x3412._1)))+(-1640531527))+((x3434<<(6))))+((x3434>>(2))))));
    int x3444 = x3413;
    return x3444; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3446, const struct SEntry8_IIIITIIB& x3447) { 
    int x3448 = 0;
    if(((x3446._3)==((x3447._3)))) {
      if(((x3446._2)==((x3447._2)))) {
        if(((x3446._1)==((x3447._1)))) {
          x3448 = 0;
        } else {
          x3448 = 1;
        };
      } else {
        x3448 = 1;
      };
    } else {
      x3448 = 1;
    };
    int x3465 = x3448;
    return x3465; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3826)  { 
    int x3827 = 0;
    int x3828 = x3827;
    x3827 = (x3828^(((((HASH((x3826._2)))+(-1640531527))+((x3828<<(6))))+((x3828>>(2))))));
    int x3838 = x3827;
    x3827 = (x3838^(((((HASH((x3826._1)))+(-1640531527))+((x3838<<(6))))+((x3838>>(2))))));
    int x3848 = x3827;
    return x3848; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3850, const struct SEntry17_IIISSSSSSSSSSIIIS& x3851) { 
    int x3852 = 0;
    if(((x3850._2)==((x3851._2)))) {
      if(((x3850._1)==((x3851._1)))) {
        x3852 = 0;
      } else {
        x3852 = 1;
      };
    } else {
      x3852 = 1;
    };
    int x3864 = x3852;
    return x3864; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3168)  { 
    int x3169 = 0;
    int x3170 = x3169;
    x3169 = (x3170^(((((HASH((x3168._2)))+(-1640531527))+((x3170<<(6))))+((x3170>>(2))))));
    int x3180 = x3169;
    x3169 = (x3180^(((((HASH((x3168._3)))+(-1640531527))+((x3180<<(6))))+((x3180>>(2))))));
    int x3190 = x3169;
    return x3190; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3192, const struct SEntry3_III& x3193) { 
    int x3194 = 0;
    if(((x3192._2)==((x3193._2)))) {
      if(((x3192._3)==((x3193._3)))) {
        x3194 = 0;
      } else {
        x3194 = 1;
      };
    } else {
      x3194 = 1;
    };
    int x3206 = x3194;
    return x3206; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3647)  { 
    int x3648 = 0;
    int x3649 = x3648;
    x3648 = (x3649^(((((HASH((x3647._1)))+(-1640531527))+((x3649<<(6))))+((x3649>>(2))))));
    int x3659 = x3648;
    x3648 = (x3659^(((((HASH((x3647._2)))+(-1640531527))+((x3659<<(6))))+((x3659>>(2))))));
    int x3669 = x3648;
    x3648 = (x3669^(((((HASH((x3647._3)))+(-1640531527))+((x3669<<(6))))+((x3669>>(2))))));
    int x3679 = x3648;
    return x3679; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3681, const struct SEntry10_IIIIIITIDS& x3682) { 
    int x3683 = 0;
    if(((x3681._1)==((x3682._1)))) {
      if(((x3681._2)==((x3682._2)))) {
        if(((x3681._3)==((x3682._3)))) {
          x3683 = 0;
        } else {
          x3683 = 1;
        };
      } else {
        x3683 = 1;
      };
    } else {
      x3683 = 1;
    };
    int x3700 = x3683;
    return x3700; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3112)  { 
    int x3113 = 0;
    int x3114 = x3113;
    x3113 = (x3114^(((((HASH((x3112._3)))+(-1640531527))+((x3114<<(6))))+((x3114>>(2))))));
    int x3124 = x3113;
    x3113 = (x3124^(((((HASH((x3112._2)))+(-1640531527))+((x3124<<(6))))+((x3124>>(2))))));
    int x3134 = x3113;
    x3113 = (x3134^(((((HASH((x3112._1)))+(-1640531527))+((x3134<<(6))))+((x3134>>(2))))));
    int x3144 = x3113;
    return x3144; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3146, const struct SEntry3_III& x3147) { 
    int x3148 = 0;
    if(((x3146._3)==((x3147._3)))) {
      if(((x3146._2)==((x3147._2)))) {
        if(((x3146._1)==((x3147._1)))) {
          x3148 = 0;
        } else {
          x3148 = 1;
        };
      } else {
        x3148 = 1;
      };
    } else {
      x3148 = 1;
    };
    int x3165 = x3148;
    return x3165; 
  }
};
 struct SEntry5_IISDS_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3381)  { 
    int x3382 = 0;
    int x3383 = x3382;
    x3382 = (x3383^(((((HASH((x3381._1)))+(-1640531527))+((x3383<<(6))))+((x3383>>(2))))));
    int x3393 = x3382;
    return x3393; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3395, const struct SEntry5_IISDS& x3396) { 
    int x3397 = 0;
    if(((x3395._1)==((x3396._1)))) {
      x3397 = 0;
    } else {
      x3397 = 1;
    };
    int x3404 = x3397;
    return x3404; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3765)  { 
    int x3766 = 0;
    int x3767 = x3766;
    x3766 = (x3767^(((((HASH((x3765._2)))+(-1640531527))+((x3767<<(6))))+((x3767>>(2))))));
    int x3777 = x3766;
    x3766 = (x3777^(((((HASH((x3765._3)))+(-1640531527))+((x3777<<(6))))+((x3777>>(2))))));
    int x3787 = x3766;
    x3766 = (x3787^(((((HASH((x3765._6)))+(-1640531527))+((x3787<<(6))))+((x3787>>(2))))));
    int x3797 = x3766;
    return x3797; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3799, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3800) { 
    int x3801 = 0;
    if(((x3799._2)==((x3800._2)))) {
      if(((x3799._3)==((x3800._3)))) {
        if(((x3799._6)==((x3800._6)))) {
          x3801 = 0;
        } else {
          x3801 = 1;
        };
      } else {
        x3801 = 1;
      };
    } else {
      x3801 = 1;
    };
    int x3818 = x3801;
    return x3818; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3351)  { 
    int x3352 = 0;
    int x3353 = x3352;
    x3352 = (x3353^(((((HASH((x3351._1)))+(-1640531527))+((x3353<<(6))))+((x3353>>(2))))));
    int x3363 = x3352;
    return x3363; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3365, const struct SEntry9_ISSSSSSDD& x3366) { 
    int x3367 = 0;
    if(((x3365._1)==((x3366._1)))) {
      x3367 = 0;
    } else {
      x3367 = 1;
    };
    int x3374 = x3367;
    return x3374; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3530)  { 
    int x3531 = 0;
    int x3532 = x3531;
    x3531 = (x3532^(((((HASH((x3530._2)))+(-1640531527))+((x3532<<(6))))+((x3532>>(2))))));
    int x3542 = x3531;
    x3531 = (x3542^(((((HASH((x3530._1)))+(-1640531527))+((x3542<<(6))))+((x3542>>(2))))));
    int x3552 = x3531;
    return x3552; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3554, const struct SEntry11_IISSSSSSDDI& x3555) { 
    int x3556 = 0;
    if(((x3554._2)==((x3555._2)))) {
      if(((x3554._1)==((x3555._1)))) {
        x3556 = 0;
      } else {
        x3556 = 1;
      };
    } else {
      x3556 = 1;
    };
    int x3568 = x3556;
    return x3568; 
  }
};

typedef CuckooIndex<struct SEntry3_III, char, SEntry3_III_Idx321> newOrderTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry3_III, char, SEntry3_III_Idx23> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef CuckooIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,historyTblIdx0Type> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef CuckooIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,warehouseTblIdx0Type> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef CuckooIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,itemTblIdx0Type> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef CuckooIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx321> orderTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef CuckooIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx21> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,districtTblIdx0Type> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef CuckooIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx3214> orderLineTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef CuckooIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321> customerTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef CuckooIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx21> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,stockTblIdx0Type> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];

struct SEntry11_IISSSSSSDDI x5287;
struct SEntry8_IIIITIIB x5142;
struct SEntry8_IIIIITDS x4684;
struct SEntry8_IIIITIIB x4924;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4911;
struct SEntry10_IIIIIITIDS x5378;
struct SEntry3_III x5130;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4705;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5155;
struct SEntry17_IIISSSSSSSSSSIIIS x5320;
struct SEntry9_ISSSSSSDD x4635;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5385;
struct SEntry8_IIIITIIB x5367;
struct SEntry3_III x4927;
struct SEntry5_IISDS x4891;
struct SEntry17_IIISSSSSSSSSSIIIS x4941;
struct SEntry11_IISSSSSSDDI x4640;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5389;
struct SEntry10_IIIIIITIDS x5151;
struct SEntry10_IIIIIITIDS x4989;
struct SEntry9_ISSSSSSDD x4914;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4701;
struct SEntry11_IISSSSSSDDI x4917;
struct SEntry10_IIIIIITIDS x5300;


FORCE_INLINE void PaymentTx(int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
  x4635._1 = x19;
  struct SEntry9_ISSSSSSDD* x8923 = warehouseTblIdx0.get(x4635);
  x8923->_9 += x26;
  x4640._1 = x20;
  x4640._2 = x19;
  struct SEntry11_IISSSSSSDDI* x8928 = districtTblIdx0.get(x4640);
  x8928->_10 += x26;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite15711 = 0;
  if((x21>(0))) {
    std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x15715results;
    MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x15715([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
      return (e->_4); 
    }, x15715results);
    x4701._2 = x23;
    x4701._3 = x22;
    x4701._6 = x25;
    customerTblIdx1.sliceNoUpdate(x4701, x15715);
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15720 = x15715.result();
    ite15711 = x15720;
  } else {
    x4705._1 = x24;
    x4705._2 = x23;
    x4705._3 = x22;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15725 = customerTblIdx0.get(x4705);
    ite15711 = x15725;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x4645 = ite15711;
  char* x16896 = strstr((x4645->_14).data_, "BC");
  if((x16896!=(NULL))) {
    PString x2410 = PString(500);
    x2410.append((x4645->_1));
    x2410.append(' ');
    x2410.append(x23);
    x2410.append(' ');
    x2410.append(x22);
    x2410.append(' ');
    x2410.append(x20);
    x2410.append(' ');
    x2410.append(x19);
    x2410.append(' ');
    x2410.append('$');
    x2410.append(x26);
    x2410.append(' ');
    x2410.appendDate(x17);
    x2410.append(' ');
    x2410.append('|');
    x2410.append(' ');
    x2410.append((x4645->_21).data_, 500);
    x4645->_17 += x26;
    x4645->_21 = x2410;
  } else {
    x4645->_17 += x26;
  };
  PString x2436 = PString(24);
  x2436.append((x8923->_2).data_, 10);
  x2436.append("    ", 4);
  x2436.append((x8928->_3).data_, 10);
  x4684._1 = (x4645->_1);
  x4684._2 = x23;
  x4684._3 = x22;
  x4684._4 = x20;
  x4684._5 = x19;
  x4684._6 = x17;
  x4684._7 = x26;
  x4684._8 = x2436;
  historyTbl.insert_nocheck(x4684);
  clearTempMem();
}
FORCE_INLINE void NewOrderTx(int x78, date x79, int x80, int x81, int x82, int x83, int x84, int x85, int* x86, int* x87, int* x88, double* x89, PString* x90, int* x91, PString* x92, double* x93) {
  int x95 = 0;
  int x98 = 0;
  PString idata[x84];
  int x103 = 1;
  int x106 = 1;
  while(1) {
    
    int x108 = x95;
    int ite15981 = 0;
    if((x108<(x84))) {
      
      int x110 = x103;
      int x15982 = x110;
      ite15981 = x15982;
    } else {
      ite15981 = 0;
    };
    int x15849 = ite15981;
    if (!(x15849)) break; 
    
    int x113 = x95;
    int supwid = x87[x113];
    if((supwid!=(x81))) {
      x106 = 0;
    };
    int x119 = x95;
    int x120 = x86[x119];
    x4891._1 = x120;
    struct SEntry5_IISDS* x9084 = itemTblIdx0.get(x4891);
    if((x9084==(NULL))) {
      x103 = 0;
    } else {
      int x126 = x95;
      x90[x126] = (x9084->_3);
      int x129 = x95;
      x89[x129] = (x9084->_4);
      int x132 = x95;
      idata[x132] = (x9084->_5);
    };
    int x136 = x95;
    x95 = (x136+(1));
  };
  int x140 = x103;
  if(x140) {
    x4911._1 = x83;
    x4911._2 = x82;
    x4911._3 = x81;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9106 = customerTblIdx0.get(x4911);
    x4914._1 = x81;
    struct SEntry9_ISSSSSSDD* x9109 = warehouseTblIdx0.get(x4914);
    x4917._1 = x82;
    x4917._2 = x81;
    struct SEntry11_IISSSSSSDDI* x9113 = districtTblIdx0.get(x4917);
    int x4919 = x9113->_11;
    x9113->_11 += 1;
    int x157 = x106;
    x4924._1 = x4919;
    x4924._2 = x82;
    x4924._3 = x81;
    x4924._4 = x83;
    x4924._5 = x79;
    x4924._6 = -1;
    x4924._7 = x84;
    x4924._8 = x157;
    orderTbl.insert_nocheck(x4924);
    x4927._1 = x4919;
    x4927._2 = x82;
    x4927._3 = x81;
    newOrderTbl.insert_nocheck(x4927);
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
      x4941._1 = ol_i_id;
      x4941._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x9146 = stockTblIdx0.get(x4941);
      const PString& x4944 = *(&x9146->_4 + (x82-1));
      int x4945 = x9146->_3;
      int x188 = x95;
      x91[x188] = x4945;
      int x190 = x95;
      PString& x191 = idata[x190];
      char* x17094 = strstr(x191.data_, "original");
      int ite16060 = 0;
      if((x17094!=(NULL))) {
        
        char* x17100 = strstr((x9146->_17).data_, "original");
        int x16061 = (x17100!=(NULL));
        ite16060 = x16061;
      } else {
        ite16060 = 0;
      };
      int x15923 = ite16060;
      if(x15923) {
        int x196 = x95;
        x92[x196].data_[0] = 'B';
      } else {
        int x198 = x95;
        x92[x198].data_[0] = 'G';
      };
      x9146->_3 = (x4945-(ol_quantity));
      if((x4945<=(ol_quantity))) {
        x9146->_3 += 91;
      };
      int x207 = 0;
      if((ol_supply_w_id!=(x81))) {
        x207 = 1;
      };
      int x220 = x95;
      double x221 = x89[x220];
      double ol_amount = ((ol_quantity*(x221))*(((1.0+((x9109->_8)))+((x9113->_9)))))*((1.0-((x9106->_16))));
      int x229 = x95;
      x93[x229] = ol_amount;
      double x231 = x165;
      x165 = (x231+(ol_amount));
      int x234 = x95;
      x4989._1 = x4919;
      x4989._2 = x82;
      x4989._3 = x81;
      x4989._4 = (x234+(1));
      x4989._5 = ol_i_id;
      x4989._6 = ol_supply_w_id;
      x4989._8 = ol_quantity;
      x4989._9 = ol_amount;
      x4989._10 = x4944;
      orderLineTbl.insert_nocheck(x4989);
      int x239 = x95;
      x95 = (x239+(1));
    };
  } else {
    int x243 = failedNO;
    failedNO = (1+(x243));
  };
  clearTempMem();
}
FORCE_INLINE void DeliveryTx(int x247, date x248, int x249, int x250) {
  int orderIDs[10];
  int x255 = 1;
  while(1) {
    
    int x257 = x255;
    if (!((x257<=(10)))) break; 
    
    struct SEntry3_III* x5127result = nullptr;
    MinAggregator<struct SEntry3_III, int> x5127([&](struct SEntry3_III* e) -> int {
      return (e->_1); 
    }, &x5127result);
    int x264 = x255;
    x5130._2 = x264;
    x5130._3 = x249;
    newOrderTblIdx1.sliceNoUpdate(x5130, x5127);
    struct SEntry3_III* x5132 = x5127.result();
    if((x5132!=(NULL))) {
      int x5135 = x5132->_1;
      int x273 = x255;
      orderIDs[(x273-(1))] = x5135;
      newOrderTbl.del(x5132);
      int x278 = x255;
      x5142._1 = x5135;
      x5142._2 = x278;
      x5142._3 = x249;
      struct SEntry8_IIIITIIB* x9378 = orderTblIdx0.get(x5142);
      x9378->_6 = x250;
      double x287 = 0.0;
      int x289 = x255;
      x5151._1 = x5135;
      x5151._2 = x289;
      x5151._3 = x249;
      orderLineTblIdx1.sliceNoUpdate(x5151, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
        orderLineEntry->_7 = x248;
        double x294 = x287;
        x287 = (x294+((orderLineEntry->_9)));
      
      });
      int x302 = x255;
      x5155._1 = (x9378->_4);
      x5155._2 = x302;
      x5155._3 = x249;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9400 = customerTblIdx0.get(x5155);
      double x306 = x287;
      x9400->_17 += x306;
      x9400->_20 += 1;
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
}
FORCE_INLINE void StockLevelTx(int x321, date x322, int x323, int x324, int x325, int x326) {
  x5287._1 = x325;
  x5287._2 = x324;
  struct SEntry11_IISSSSSSDDI* x9478 = districtTblIdx0.get(x5287);
  int x5289 = x9478->_11;
  int x335 = (x5289-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x340 = x335;
    if (!((x340<(x5289)))) break; 
    
    int x342 = x335;
    x5300._1 = x342;
    x5300._2 = x325;
    x5300._3 = x324;
    orderLineTblIdx1.sliceNoUpdate(x5300, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x5318 = orderLineEntry->_5;
      x5320._1 = x5318;
      x5320._2 = x324;
      struct SEntry17_IIISSSSSSSSSSIIIS* x9493 = stockTblIdx0.get(x5320);
      if(((x9493->_3)<(x326))) {
        unique_ol_i_id.insert(x5318);
      };
    
    });
    int x359 = x335;
    x335 = (x359+(1));
  };
  clearTempMem();
}
FORCE_INLINE void OrderStatusTx(int x365, date x366, int x367, int x368, int x369, int x370, int x371, PString x372) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16347 = 0;
  if((x370>(0))) {
    std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16351results;
    MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x16351([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
      return (e->_4); 
    }, x16351results);
    x5385._2 = x369;
    x5385._3 = x368;
    x5385._6 = x372;
    customerTblIdx1.sliceNoUpdate(x5385, x16351);
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16356 = x16351.result();
    ite16347 = x16356;
  } else {
    x5389._1 = x371;
    x5389._2 = x369;
    x5389._3 = x368;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16361 = customerTblIdx0.get(x5389);
    ite16347 = x16361;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x5362 = ite16347;
  struct SEntry8_IIIITIIB* x5365result = nullptr;
  MaxAggregator<struct SEntry8_IIIITIIB, int> x5365([&](struct SEntry8_IIIITIIB* e) -> int {
    return (e->_1); 
  }, &x5365result);
  x5367._2 = x369;
  x5367._3 = x368;
  x5367._4 = (x5362->_3);
  orderTblIdx1.sliceNoUpdate(x5367, x5365);
  struct SEntry8_IIIITIIB* x5369 = x5365.result();
  int ite16376 = 0;
  if((x5369==(NULL))) {
    int x16377 = failedOS;
    failedOS = (1+(x16377));
    ite16376 = 0;
  } else {
    x5378._1 = (x5369->_1);
    x5378._2 = x369;
    x5378._3 = x368;
    orderLineTblIdx1.sliceNoUpdate(x5378, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x410 = 1;
    
    });
    ite16376 = 1;
  };
  int x414 = ite16376;
  clearTempMem();
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
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-DEFILNORVX-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info << "\n}\n";
  info.close();
  
  #ifdef VERIFY_TPCC
      warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
  
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
