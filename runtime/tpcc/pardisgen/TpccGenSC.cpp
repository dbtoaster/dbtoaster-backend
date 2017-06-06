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
  int _1;  int _2;  PString _3;  double _4;  PString _5;  bool isInvalid; EntryMV<SEntry5_IISDS>* e;
  SEntry5_IISDS() :_1(-2147483648), _2(-2147483648), _3(), _4(-1.7976931348623157E308), _5(), isInvalid(false), e(nullptr) {}
  SEntry5_IISDS(const int& _1, const int& _2, const PString& _3, const double& _4, const PString& _5) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry5_IISDS* copy() const {  SEntry5_IISDS* ptr = (SEntry5_IISDS*) malloc(sizeof(SEntry5_IISDS)); new(ptr) SEntry5_IISDS(_1, _2, _3, _4, _5);  return ptr;}
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  bool isInvalid; EntryMV<SEntry11_IISSSSSSDDI>* e;
  SEntry11_IISSSSSSDDI() :_1(-2147483648), _2(-2147483648), _3(), _4(), _5(), _6(), _7(), _8(), _9(-1.7976931348623157E308), _10(-1.7976931348623157E308), _11(-2147483648), isInvalid(false), e(nullptr) {}
  SEntry11_IISSSSSSDDI(const int& _1, const int& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const double& _9, const double& _10, const int& _11) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry11_IISSSSSSDDI* copy() const {  SEntry11_IISSSSSSDDI* ptr = (SEntry11_IISSSSSSDDI*) malloc(sizeof(SEntry11_IISSSSSSDDI)); new(ptr) SEntry11_IISSSSSSDDI(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11);  return ptr;}
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  bool isInvalid; EntryMV<SEntry8_IIIITIIB>* e;
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), isInvalid(false), e(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry8_IIIITIIB* copy() const {  SEntry8_IIIITIIB* ptr = (SEntry8_IIIITIIB*) malloc(sizeof(SEntry8_IIIITIIB)); new(ptr) SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  bool isInvalid; EntryMV<SEntry3_III>* e;
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), isInvalid(false), e(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry3_III* copy() const {  SEntry3_III* ptr = (SEntry3_III*) malloc(sizeof(SEntry3_III)); new(ptr) SEntry3_III(_1, _2, _3);  return ptr;}
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  bool isInvalid; EntryMV<SEntry21_IIISSSSSSSSSTSDDDDIIS>* e;
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), isInvalid(false), e(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const {  SEntry21_IIISSSSSSSSSTSDDDDIIS* ptr = (SEntry21_IIISSSSSSSSSTSDDDDIIS*) malloc(sizeof(SEntry21_IIISSSSSSSSSTSDDDDIIS)); new(ptr) SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21);  return ptr;}
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  bool isInvalid; EntryMV<SEntry8_IIIIITDS>* e;
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), isInvalid(false), e(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry8_IIIIITDS* copy() const {  SEntry8_IIIIITDS* ptr = (SEntry8_IIIIITDS*) malloc(sizeof(SEntry8_IIIIITDS)); new(ptr) SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  bool isInvalid; EntryMV<SEntry17_IIISSSSSSSSSSIIIS>* e;
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), isInvalid(false), e(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry17_IIISSSSSSSSSSIIIS* copy() const {  SEntry17_IIISSSSSSSSSSIIIS* ptr = (SEntry17_IIISSSSSSSSSSIIIS*) malloc(sizeof(SEntry17_IIISSSSSSSSSSIIIS)); new(ptr) SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17);  return ptr;}
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  bool isInvalid; EntryMV<SEntry10_IIIIIITIDS>* e;
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), isInvalid(false), e(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry10_IIIIIITIDS* copy() const {  SEntry10_IIIIIITIDS* ptr = (SEntry10_IIIIIITIDS*) malloc(sizeof(SEntry10_IIIIIITIDS)); new(ptr) SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);  return ptr;}
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  bool isInvalid; EntryMV<SEntry9_ISSSSSSDD>* e;
  SEntry9_ISSSSSSDD() :_1(-2147483648), _2(), _3(), _4(), _5(), _6(), _7(), _8(-1.7976931348623157E308), _9(-1.7976931348623157E308), isInvalid(false), e(nullptr) {}
  SEntry9_ISSSSSSDD(const int& _1, const PString& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const double& _8, const double& _9) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), isInvalid(false), e(nullptr) {}
  FORCE_INLINE SEntry9_ISSSSSSDD* copy() const {  SEntry9_ISSSSSSDD* ptr = (SEntry9_ISSSSSSDD*) malloc(sizeof(SEntry9_ISSSSSSDD)); new(ptr) SEntry9_ISSSSSSDD(_1, _2, _3, _4, _5, _6, _7, _8, _9);  return ptr;}
};
bool operator== (const SEntry5_IISDS& o1, const SEntry5_IISDS& o2) {
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  (fabs(o1._4 - o2._4) < 0.01) && 
  o1._5 == o2._5;
}
bool operator== (const SEntry11_IISSSSSSDDI& o1, const SEntry11_IISSSSSSDDI& o2) {
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
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
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  o1._7 == o2._7 && 
  o1._8 == o2._8;
}
bool operator== (const SEntry3_III& o1, const SEntry3_III& o2) {
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3;
}
bool operator== (const SEntry21_IIISSSSSSSSSTSDDDDIIS& o1, const SEntry21_IIISSSSSSSSSTSDDDDIIS& o2) {
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
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
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  o1._4 == o2._4 && 
  o1._5 == o2._5 && 
  o1._6 == o2._6 && 
  (fabs(o1._7 - o2._7) < 0.01) && 
  o1._8 == o2._8;
}
bool operator== (const SEntry17_IIISSSSSSSSSSIIIS& o1, const SEntry17_IIISSSSSSSSSSIIIS& o2) {
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
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
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
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
  if (o1.isInvalid || o2.isInvalid) return o1.isInvalid && o2.isInvalid;
  else return o1._1 == o2._1 && 
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
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3459)  { 
    int x3460 = 0;
    int x3461 = x3460;
    x3460 = (x3461^(((((HASH((x3459._2)))+(-1640531527))+((x3461<<(6))))+((x3461>>(2))))));
    int x3471 = x3460;
    x3460 = (x3471^(((((HASH((x3459._3)))+(-1640531527))+((x3471<<(6))))+((x3471>>(2))))));
    int x3481 = x3460;
    x3460 = (x3481^(((((HASH((x3459._4)))+(-1640531527))+((x3481<<(6))))+((x3481>>(2))))));
    int x3491 = x3460;
    return x3491; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3493, const struct SEntry8_IIIITIIB& x3494) { 
    int x3495 = 0;
    if(((x3493._2)==((x3494._2)))) {
      if(((x3493._3)==((x3494._3)))) {
        if(((x3493._4)==((x3494._4)))) {
          x3495 = 0;
        } else {
          x3495 = 1;
        };
      } else {
        x3495 = 1;
      };
    } else {
      x3495 = 1;
    };
    int x3512 = x3495;
    return x3512; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx3214 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3567)  { 
    int x3568 = 0;
    int x3569 = x3568;
    x3568 = (x3569^(((((HASH((x3567._3)))+(-1640531527))+((x3569<<(6))))+((x3569>>(2))))));
    int x3579 = x3568;
    x3568 = (x3579^(((((HASH((x3567._2)))+(-1640531527))+((x3579<<(6))))+((x3579>>(2))))));
    int x3589 = x3568;
    x3568 = (x3589^(((((HASH((x3567._1)))+(-1640531527))+((x3589<<(6))))+((x3589>>(2))))));
    int x3599 = x3568;
    x3568 = (x3599^(((((HASH((x3567._4)))+(-1640531527))+((x3599<<(6))))+((x3599>>(2))))));
    int x3609 = x3568;
    return x3609; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3611, const struct SEntry10_IIIIIITIDS& x3612) { 
    int x3613 = 0;
    if(((x3611._3)==((x3612._3)))) {
      if(((x3611._2)==((x3612._2)))) {
        if(((x3611._1)==((x3612._1)))) {
          if(((x3611._4)==((x3612._4)))) {
            x3613 = 0;
          } else {
            x3613 = 1;
          };
        } else {
          x3613 = 1;
        };
      } else {
        x3613 = 1;
      };
    } else {
      x3613 = 1;
    };
    int x3635 = x3613;
    return x3635; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3700)  { 
    int x3701 = 0;
    int x3702 = x3701;
    x3701 = (x3702^(((((HASH((x3700._3)))+(-1640531527))+((x3702<<(6))))+((x3702>>(2))))));
    int x3712 = x3701;
    x3701 = (x3712^(((((HASH((x3700._2)))+(-1640531527))+((x3712<<(6))))+((x3712>>(2))))));
    int x3722 = x3701;
    x3701 = (x3722^(((((HASH((x3700._1)))+(-1640531527))+((x3722<<(6))))+((x3722>>(2))))));
    int x3732 = x3701;
    return x3732; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3734, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3735) { 
    int x3736 = 0;
    if(((x3734._3)==((x3735._3)))) {
      if(((x3734._2)==((x3735._2)))) {
        if(((x3734._1)==((x3735._1)))) {
          x3736 = 0;
        } else {
          x3736 = 1;
        };
      } else {
        x3736 = 1;
      };
    } else {
      x3736 = 1;
    };
    int x3753 = x3736;
    return x3753; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3206)  { 
    int x3207 = 0;
    int x3208 = x3207;
    x3207 = (x3208^(((((HASH((x3206._1)))+(-1640531527))+((x3208<<(6))))+((x3208>>(2))))));
    int x3218 = x3207;
    x3207 = (x3218^(((((HASH((x3206._2)))+(-1640531527))+((x3218<<(6))))+((x3218>>(2))))));
    int x3228 = x3207;
    x3207 = (x3228^(((((HASH((x3206._3)))+(-1640531527))+((x3228<<(6))))+((x3228>>(2))))));
    int x3238 = x3207;
    x3207 = (x3238^(((((HASH((x3206._4)))+(-1640531527))+((x3238<<(6))))+((x3238>>(2))))));
    int x3248 = x3207;
    x3207 = (x3248^(((((HASH((x3206._5)))+(-1640531527))+((x3248<<(6))))+((x3248>>(2))))));
    int x3258 = x3207;
    x3207 = (x3258^(((((HASH((x3206._6)))+(-1640531527))+((x3258<<(6))))+((x3258>>(2))))));
    int x3268 = x3207;
    x3207 = (x3268^(((((HASH((x3206._7)))+(-1640531527))+((x3268<<(6))))+((x3268>>(2))))));
    int x3278 = x3207;
    x3207 = (x3278^(((((HASH((x3206._8)))+(-1640531527))+((x3278<<(6))))+((x3278>>(2))))));
    int x3288 = x3207;
    return x3288; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3290, const struct SEntry8_IIIIITDS& x3291) { 
    int x3292 = 0;
    if(((x3290._1)==((x3291._1)))) {
      if(((x3290._2)==((x3291._2)))) {
        if(((x3290._3)==((x3291._3)))) {
          if(((x3290._4)==((x3291._4)))) {
            if(((x3290._5)==((x3291._5)))) {
              if(((x3290._6)==((x3291._6)))) {
                if(((x3290._7)==((x3291._7)))) {
                  if(((x3290._8)==((x3291._8)))) {
                    x3292 = 0;
                  } else {
                    x3292 = 1;
                  };
                } else {
                  x3292 = 1;
                };
              } else {
                x3292 = 1;
              };
            } else {
              x3292 = 1;
            };
          } else {
            x3292 = 1;
          };
        } else {
          x3292 = 1;
        };
      } else {
        x3292 = 1;
      };
    } else {
      x3292 = 1;
    };
    int x3334 = x3292;
    return x3334; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3403)  { 
    int x3404 = 0;
    int x3405 = x3404;
    x3404 = (x3405^(((((HASH((x3403._3)))+(-1640531527))+((x3405<<(6))))+((x3405>>(2))))));
    int x3415 = x3404;
    x3404 = (x3415^(((((HASH((x3403._2)))+(-1640531527))+((x3415<<(6))))+((x3415>>(2))))));
    int x3425 = x3404;
    x3404 = (x3425^(((((HASH((x3403._1)))+(-1640531527))+((x3425<<(6))))+((x3425>>(2))))));
    int x3435 = x3404;
    return x3435; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3437, const struct SEntry8_IIIITIIB& x3438) { 
    int x3439 = 0;
    if(((x3437._3)==((x3438._3)))) {
      if(((x3437._2)==((x3438._2)))) {
        if(((x3437._1)==((x3438._1)))) {
          x3439 = 0;
        } else {
          x3439 = 1;
        };
      } else {
        x3439 = 1;
      };
    } else {
      x3439 = 1;
    };
    int x3456 = x3439;
    return x3456; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3817)  { 
    int x3818 = 0;
    int x3819 = x3818;
    x3818 = (x3819^(((((HASH((x3817._2)))+(-1640531527))+((x3819<<(6))))+((x3819>>(2))))));
    int x3829 = x3818;
    x3818 = (x3829^(((((HASH((x3817._1)))+(-1640531527))+((x3829<<(6))))+((x3829>>(2))))));
    int x3839 = x3818;
    return x3839; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3841, const struct SEntry17_IIISSSSSSSSSSIIIS& x3842) { 
    int x3843 = 0;
    if(((x3841._2)==((x3842._2)))) {
      if(((x3841._1)==((x3842._1)))) {
        x3843 = 0;
      } else {
        x3843 = 1;
      };
    } else {
      x3843 = 1;
    };
    int x3855 = x3843;
    return x3855; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3159)  { 
    int x3160 = 0;
    int x3161 = x3160;
    x3160 = (x3161^(((((HASH((x3159._2)))+(-1640531527))+((x3161<<(6))))+((x3161>>(2))))));
    int x3171 = x3160;
    x3160 = (x3171^(((((HASH((x3159._3)))+(-1640531527))+((x3171<<(6))))+((x3171>>(2))))));
    int x3181 = x3160;
    return x3181; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3183, const struct SEntry3_III& x3184) { 
    int x3185 = 0;
    if(((x3183._2)==((x3184._2)))) {
      if(((x3183._3)==((x3184._3)))) {
        x3185 = 0;
      } else {
        x3185 = 1;
      };
    } else {
      x3185 = 1;
    };
    int x3197 = x3185;
    return x3197; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3638)  { 
    int x3639 = 0;
    int x3640 = x3639;
    x3639 = (x3640^(((((HASH((x3638._1)))+(-1640531527))+((x3640<<(6))))+((x3640>>(2))))));
    int x3650 = x3639;
    x3639 = (x3650^(((((HASH((x3638._2)))+(-1640531527))+((x3650<<(6))))+((x3650>>(2))))));
    int x3660 = x3639;
    x3639 = (x3660^(((((HASH((x3638._3)))+(-1640531527))+((x3660<<(6))))+((x3660>>(2))))));
    int x3670 = x3639;
    return x3670; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3672, const struct SEntry10_IIIIIITIDS& x3673) { 
    int x3674 = 0;
    if(((x3672._1)==((x3673._1)))) {
      if(((x3672._2)==((x3673._2)))) {
        if(((x3672._3)==((x3673._3)))) {
          x3674 = 0;
        } else {
          x3674 = 1;
        };
      } else {
        x3674 = 1;
      };
    } else {
      x3674 = 1;
    };
    int x3691 = x3674;
    return x3691; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3103)  { 
    int x3104 = 0;
    int x3105 = x3104;
    x3104 = (x3105^(((((HASH((x3103._3)))+(-1640531527))+((x3105<<(6))))+((x3105>>(2))))));
    int x3115 = x3104;
    x3104 = (x3115^(((((HASH((x3103._2)))+(-1640531527))+((x3115<<(6))))+((x3115>>(2))))));
    int x3125 = x3104;
    x3104 = (x3125^(((((HASH((x3103._1)))+(-1640531527))+((x3125<<(6))))+((x3125>>(2))))));
    int x3135 = x3104;
    return x3135; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3137, const struct SEntry3_III& x3138) { 
    int x3139 = 0;
    if(((x3137._3)==((x3138._3)))) {
      if(((x3137._2)==((x3138._2)))) {
        if(((x3137._1)==((x3138._1)))) {
          x3139 = 0;
        } else {
          x3139 = 1;
        };
      } else {
        x3139 = 1;
      };
    } else {
      x3139 = 1;
    };
    int x3156 = x3139;
    return x3156; 
  }
};
 struct SEntry5_IISDS_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3372)  { 
    int x3373 = 0;
    int x3374 = x3373;
    x3373 = (x3374^(((((HASH((x3372._1)))+(-1640531527))+((x3374<<(6))))+((x3374>>(2))))));
    int x3384 = x3373;
    return x3384; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3386, const struct SEntry5_IISDS& x3387) { 
    int x3388 = 0;
    if(((x3386._1)==((x3387._1)))) {
      x3388 = 0;
    } else {
      x3388 = 1;
    };
    int x3395 = x3388;
    return x3395; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3756)  { 
    int x3757 = 0;
    int x3758 = x3757;
    x3757 = (x3758^(((((HASH((x3756._2)))+(-1640531527))+((x3758<<(6))))+((x3758>>(2))))));
    int x3768 = x3757;
    x3757 = (x3768^(((((HASH((x3756._3)))+(-1640531527))+((x3768<<(6))))+((x3768>>(2))))));
    int x3778 = x3757;
    x3757 = (x3778^(((((HASH((x3756._6)))+(-1640531527))+((x3778<<(6))))+((x3778>>(2))))));
    int x3788 = x3757;
    return x3788; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3790, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3791) { 
    int x3792 = 0;
    if(((x3790._2)==((x3791._2)))) {
      if(((x3790._3)==((x3791._3)))) {
        if(((x3790._6)==((x3791._6)))) {
          x3792 = 0;
        } else {
          x3792 = 1;
        };
      } else {
        x3792 = 1;
      };
    } else {
      x3792 = 1;
    };
    int x3809 = x3792;
    return x3809; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3342)  { 
    int x3343 = 0;
    int x3344 = x3343;
    x3343 = (x3344^(((((HASH((x3342._1)))+(-1640531527))+((x3344<<(6))))+((x3344>>(2))))));
    int x3354 = x3343;
    return x3354; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3356, const struct SEntry9_ISSSSSSDD& x3357) { 
    int x3358 = 0;
    if(((x3356._1)==((x3357._1)))) {
      x3358 = 0;
    } else {
      x3358 = 1;
    };
    int x3365 = x3358;
    return x3365; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3521)  { 
    int x3522 = 0;
    int x3523 = x3522;
    x3522 = (x3523^(((((HASH((x3521._2)))+(-1640531527))+((x3523<<(6))))+((x3523>>(2))))));
    int x3533 = x3522;
    x3522 = (x3533^(((((HASH((x3521._1)))+(-1640531527))+((x3533<<(6))))+((x3533>>(2))))));
    int x3543 = x3522;
    return x3543; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3545, const struct SEntry11_IISSSSSSDDI& x3546) { 
    int x3547 = 0;
    if(((x3545._2)==((x3546._2)))) {
      if(((x3545._1)==((x3546._1)))) {
        x3547 = 0;
      } else {
        x3547 = 1;
      };
    } else {
      x3547 = 1;
    };
    int x3559 = x3547;
    return x3559; 
  }
};

typedef CuckooIndex<struct SEntry3_III, SEntry3_III_Idx321> newOrderTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry3_III, SEntry3_III_Idx23> newOrderTblIdx1Type;
typedef MultiHashMapMV<struct SEntry3_III,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef CuckooIndex<struct SEntry8_IIIIITDS, SEntry8_IIIIITDS_Idx12345678> historyTblIdx0Type;
typedef MultiHashMapMV<struct SEntry8_IIIIITDS,historyTblIdx0Type> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef CuckooIndex<struct SEntry9_ISSSSSSDD, SEntry9_ISSSSSSDD_Idx1> warehouseTblIdx0Type;
typedef MultiHashMapMV<struct SEntry9_ISSSSSSDD,warehouseTblIdx0Type> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef CuckooIndex<struct SEntry5_IISDS, SEntry5_IISDS_Idx1> itemTblIdx0Type;
typedef MultiHashMapMV<struct SEntry5_IISDS,itemTblIdx0Type> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef CuckooIndex<struct SEntry8_IIIITIIB, SEntry8_IIIITIIB_Idx321> orderTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry8_IIIITIIB, SEntry8_IIIITIIB_Idx234> orderTblIdx1Type;
typedef MultiHashMapMV<struct SEntry8_IIIITIIB,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef CuckooIndex<struct SEntry11_IISSSSSSDDI, SEntry11_IISSSSSSDDI_Idx21> districtTblIdx0Type;
typedef MultiHashMapMV<struct SEntry11_IISSSSSSDDI,districtTblIdx0Type> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef CuckooIndex<struct SEntry10_IIIIIITIDS, SEntry10_IIIIIITIDS_Idx3214> orderLineTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry10_IIIIIITIDS, SEntry10_IIIIIITIDS_Idx123> orderLineTblIdx1Type;
typedef MultiHashMapMV<struct SEntry10_IIIIIITIDS,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef CuckooIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321> customerTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236> customerTblIdx1Type;
typedef MultiHashMapMV<struct SEntry21_IIISSSSSSSSSTSDDDDIIS,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef CuckooIndex<struct SEntry17_IIISSSSSSSSSSIIIS, SEntry17_IIISSSSSSSSSSIIIS_Idx21> stockTblIdx0Type;
typedef MultiHashMapMV<struct SEntry17_IIISSSSSSSSSSIIIS,stockTblIdx0Type> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5373;
struct SEntry10_IIIIIITIDS x5142;
struct SEntry3_III x5121;
struct SEntry8_IIIITIIB x5133;
struct SEntry10_IIIIIITIDS x5290;
struct SEntry8_IIIIITDS x4675;
struct SEntry17_IIISSSSSSSSSSIIIS x5309;
struct SEntry11_IISSSSSSDDI x4631;
struct SEntry10_IIIIIITIDS x5366;
struct SEntry8_IIIITIIB x5355;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5377;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x5146;
struct SEntry9_ISSSSSSDD x4626;
struct SEntry5_IISDS x4882;
struct SEntry9_ISSSSSSDD x4905;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4696;
struct SEntry17_IIISSSSSSSSSSIIIS x4932;
struct SEntry10_IIIIIITIDS x4980;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4692;
struct SEntry11_IISSSSSSDDI x5278;
struct SEntry11_IISSSSSSDDI x4908;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x4902;
struct SEntry3_III x4918;
struct SEntry8_IIIITIIB x4915;


FORCE_INLINE void PaymentTx(int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
  x4626._1 = x19;
  struct SEntry9_ISSSSSSDD* x10395 = warehouseTblIdx0.getForUpdate(x4626);
  x10395->_9 += x26;
  x4631._1 = x20;
  x4631._2 = x19;
  struct SEntry11_IISSSSSSDDI* x10401 = districtTblIdx0.getForUpdate(x4631);
  x10401->_10 += x26;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite18312 = 0;
  if((x21>(0))) {
    std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x18316results;
    MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x18316([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
      return (e->_4); 
    }, x18316results);
    x4692._2 = x23;
    x4692._3 = x22;
    x4692._6 = x25;
    customerTblIdx1.sliceNoUpdate(x4692, x18316);
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x18321 = x18316.resultForUpdate();
    ite18312 = x18321;
  } else {
    x4696._1 = x24;
    x4696._2 = x23;
    x4696._3 = x22;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x18326 = customerTblIdx0.getForUpdate(x4696);
    ite18312 = x18326;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x4636 = ite18312;
  char* x19495 = strstr((x4636->_14).data_, "BC");
  if((x19495!=(NULL))) {
    PString x2403 = PString(500);
    x2403.append((x4636->_1));
    x2403.append(' ');
    x2403.append(x23);
    x2403.append(' ');
    x2403.append(x22);
    x2403.append(' ');
    x2403.append(x20);
    x2403.append(' ');
    x2403.append(x19);
    x2403.append(' ');
    x2403.append('$');
    x2403.append(x26);
    x2403.append(' ');
    x2403.appendDate(x17);
    x2403.append(' ');
    x2403.append('|');
    x2403.append(' ');
    x2403.append((x4636->_21).data_, 500);
    x4636->_17 += x26;
    x4636->_21 = x2403;
  } else {
    x4636->_17 += x26;
  };
  PString x2429 = PString(24);
  x2429.append((x10395->_2).data_, 10);
  x2429.append("    ", 4);
  x2429.append((x10401->_3).data_, 10);
  x4675._1 = (x4636->_1);
  x4675._2 = x23;
  x4675._3 = x22;
  x4675._4 = x20;
  x4675._5 = x19;
  x4675._6 = x17;
  x4675._7 = x26;
  x4675._8 = x2429;
  historyTbl.insert_nocheck(x4675);
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
    int ite18582 = 0;
    if((x108<(x84))) {
      
      int x110 = x103;
      int x18583 = x110;
      ite18582 = x18583;
    } else {
      ite18582 = 0;
    };
    int x18450 = ite18582;
    if (!(x18450)) break; 
    
    int x113 = x95;
    int supwid = x87[x113];
    if((supwid!=(x81))) {
      x106 = 0;
    };
    int x119 = x95;
    int x120 = x86[x119];
    x4882._1 = x120;
    struct SEntry5_IISDS* x9077 = itemTblIdx0.get(x4882);
    if((x9077==(NULL))) {
      x103 = 0;
    } else {
      int x126 = x95;
      x90[x126] = (x9077->_3);
      int x129 = x95;
      x89[x129] = (x9077->_4);
      int x132 = x95;
      idata[x132] = (x9077->_5);
    };
    int x136 = x95;
    x95 = (x136+(1));
  };
  int x140 = x103;
  if(x140) {
    x4902._1 = x83;
    x4902._2 = x82;
    x4902._3 = x81;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9099 = customerTblIdx0.get(x4902);
    x4905._1 = x81;
    struct SEntry9_ISSSSSSDD* x9102 = warehouseTblIdx0.get(x4905);
    x4908._1 = x82;
    x4908._2 = x81;
    struct SEntry11_IISSSSSSDDI* x10669 = districtTblIdx0.getForUpdate(x4908);
    int x4910 = x10669->_11;
    x10669->_11 += 1;
    int x157 = x106;
    x4915._1 = x4910;
    x4915._2 = x82;
    x4915._3 = x81;
    x4915._4 = x83;
    x4915._5 = x79;
    x4915._6 = -1;
    x4915._7 = x84;
    x4915._8 = x157;
    orderTbl.insert_nocheck(x4915);
    x4918._1 = x4910;
    x4918._2 = x82;
    x4918._3 = x81;
    newOrderTbl.insert_nocheck(x4918);
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
      x4932._1 = ol_i_id;
      x4932._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x10703 = stockTblIdx0.getForUpdate(x4932);
      const PString& x4935 = *(&x10703->_4 + (x82-1));
      int x4936 = x10703->_3;
      int x188 = x95;
      x91[x188] = x4936;
      int x190 = x95;
      PString& x191 = idata[x190];
      char* x19693 = strstr(x191.data_, "original");
      int ite18661 = 0;
      if((x19693!=(NULL))) {
        
        char* x19699 = strstr((x10703->_17).data_, "original");
        int x18662 = (x19699!=(NULL));
        ite18661 = x18662;
      } else {
        ite18661 = 0;
      };
      int x18524 = ite18661;
      if(x18524) {
        int x196 = x95;
        x92[x196].data_[0] = 'B';
      } else {
        int x198 = x95;
        x92[x198].data_[0] = 'G';
      };
      x10703->_3 = (x4936-(ol_quantity));
      if((x4936<=(ol_quantity))) {
        x10703->_3 += 91;
      };
      int x207 = 0;
      if((ol_supply_w_id!=(x81))) {
        x207 = 1;
      };
      int x220 = x95;
      double x221 = x89[x220];
      double ol_amount = ((ol_quantity*(x221))*(((1.0+((x9102->_8)))+((x10669->_9)))))*((1.0-((x9099->_16))));
      int x229 = x95;
      x93[x229] = ol_amount;
      double x231 = x165;
      x165 = (x231+(ol_amount));
      int x234 = x95;
      x4980._1 = x4910;
      x4980._2 = x82;
      x4980._3 = x81;
      x4980._4 = (x234+(1));
      x4980._5 = ol_i_id;
      x4980._6 = ol_supply_w_id;
      x4980._8 = ol_quantity;
      x4980._9 = ol_amount;
      x4980._10 = x4935;
      orderLineTbl.insert_nocheck(x4980);
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
    
    struct SEntry3_III* x5118result = nullptr;
    MinAggregator<struct SEntry3_III, int> x5118([&](struct SEntry3_III* e) -> int {
      return (e->_1); 
    }, &x5118result);
    int x264 = x255;
    x5121._2 = x264;
    x5121._3 = x249;
    newOrderTblIdx1.sliceNoUpdate(x5121, x5118);
    struct SEntry3_III* x5123 = x5118.result();
    if((x5123!=(NULL))) {
      int x5126 = x5123->_1;
      int x273 = x255;
      orderIDs[(x273-(1))] = x5126;
      x5123->isInvalid = true;
      int x278 = x255;
      x5133._1 = x5126;
      x5133._2 = x278;
      x5133._3 = x249;
      struct SEntry8_IIIITIIB* x10938 = orderTblIdx0.getForUpdate(x5133);
      x10938->_6 = x250;
      double x287 = 0.0;
      int x289 = x255;
      x5142._1 = x5126;
      x5142._2 = x289;
      x5142._3 = x249;
      orderLineTblIdx1.sliceNoUpdate(x5142, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
        orderLineEntry->_7 = x248;
        double x294 = x287;
        x287 = (x294+((orderLineEntry->_9)));
      
      });
      int x302 = x255;
      x5146._1 = (x10938->_4);
      x5146._2 = x302;
      x5146._3 = x249;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10964 = customerTblIdx0.getForUpdate(x5146);
      double x306 = x287;
      x10964->_17 += x306;
      x10964->_20 += 1;
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
  x5278._1 = x325;
  x5278._2 = x324;
  struct SEntry11_IISSSSSSDDI* x9487 = districtTblIdx0.get(x5278);
  int x5280 = x9487->_11;
  int x335 = (x5280-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x339 = x335;
    if (!((x339<(x5280)))) break; 
    
    int x341 = x335;
    x5290._1 = x341;
    x5290._2 = x325;
    x5290._3 = x324;
    orderLineTblIdx1.sliceNoUpdate(x5290, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x5307 = orderLineEntry->_5;
      x5309._1 = x5307;
      x5309._2 = x324;
      struct SEntry17_IIISSSSSSSSSSIIIS* x9501 = stockTblIdx0.get(x5309);
      if(((x9501->_3)<(x326))) {
        unique_ol_i_id.insert(x5307);
      };
    
    });
    int x358 = x335;
    x335 = (x358+(1));
  };
  clearTempMem();
}
FORCE_INLINE void OrderStatusTx(int x364, date x365, int x366, int x367, int x368, int x369, int x370, PString x371) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite18947 = 0;
  if((x369>(0))) {
    std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x18951results;
    MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x18951([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
      return (e->_4); 
    }, x18951results);
    x5373._2 = x368;
    x5373._3 = x367;
    x5373._6 = x371;
    customerTblIdx1.sliceNoUpdate(x5373, x18951);
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x18956 = x18951.result();
    ite18947 = x18956;
  } else {
    x5377._1 = x370;
    x5377._2 = x368;
    x5377._3 = x367;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x18961 = customerTblIdx0.get(x5377);
    ite18947 = x18961;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x5350 = ite18947;
  struct SEntry8_IIIITIIB* x5353result = nullptr;
  MaxAggregator<struct SEntry8_IIIITIIB, int> x5353([&](struct SEntry8_IIIITIIB* e) -> int {
    return (e->_1); 
  }, &x5353result);
  x5355._2 = x368;
  x5355._3 = x367;
  x5355._4 = (x5350->_3);
  orderTblIdx1.sliceNoUpdate(x5355, x5353);
  struct SEntry8_IIIITIIB* x5357 = x5353.result();
  int ite18976 = 0;
  if((x5357==(NULL))) {
    int x18977 = failedOS;
    failedOS = (1+(x18977));
    ite18976 = 0;
  } else {
    x5366._1 = (x5357->_1);
    x5366._2 = x368;
    x5366._3 = x367;
    orderLineTblIdx1.sliceNoUpdate(x5366, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x409 = 1;
    
    });
    ite18976 = 1;
  };
  int x413 = ite18976;
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
  GET_RUN_STAT(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info <<",\n";
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
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info << "\n}\n";
  info.close();
  
  #ifdef VERIFY_TPCC
  /*
      warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
  */
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
