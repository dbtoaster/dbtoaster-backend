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

#include <thread>
#include <sched.h>
#include <pthread.h>


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

struct Partition;
const int numThreads = 3;
std::thread workers[numThreads];
volatile bool isReady[numThreads];
volatile bool startExecution, hasFinished;

#define CORE_FOR_W(x) (x%numThreads)

#define setAffinity(thread_id)\
    cpu_set_t cpuset;\
    CPU_ZERO(&cpuset);\
    CPU_SET(thread_id+1, &cpuset);\
    auto s = sched_setaffinity(0, sizeof (cpu_set_t), &cpuset);\
    if (s != 0)\
        throw std::runtime_error("Cannot set affinity");

#define setSched(type)\
    sched_param param;\
    param.__sched_priority =  sched_get_priority_max(type);\
    s = sched_setscheduler(0, type, &param);\
    if (s != 0)\
        cerr << "Cannot set scheduler" << endl;

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
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[21];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const {  SEntry21_IIISSSSSSSSSTSDDDDIIS* ptr = (SEntry21_IIISSSSSSSSSTSDDDDIIS*) malloc(sizeof(SEntry21_IIISSSSSSSSSTSDDDDIIS)); new(ptr) SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21);  return ptr;}
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry3_III* copy() const {  SEntry3_III* ptr = (SEntry3_III*) malloc(sizeof(SEntry3_III)); new(ptr) SEntry3_III(_1, _2, _3);  return ptr;}
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
bool operator== (const SEntry3_III& o1, const SEntry3_III& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3;
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
 struct SEntry10_IIIIIITIDS_Idx3214 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x5992)  { 
    int x5993 = 0;
    int x5994 = x5993;
    x5993 = (x5994^(((((HASH((x5992._3)))+(-1640531527))+((x5994<<(6))))+((x5994>>(2))))));
    int x6004 = x5993;
    x5993 = (x6004^(((((HASH((x5992._2)))+(-1640531527))+((x6004<<(6))))+((x6004>>(2))))));
    int x6014 = x5993;
    x5993 = (x6014^(((((HASH((x5992._1)))+(-1640531527))+((x6014<<(6))))+((x6014>>(2))))));
    int x6024 = x5993;
    x5993 = (x6024^(((((HASH((x5992._4)))+(-1640531527))+((x6024<<(6))))+((x6024>>(2))))));
    int x6034 = x5993;
    return x6034; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6036, const struct SEntry10_IIIIIITIDS& x6037) { 
    int x6038 = 0;
    if(((x6036._3)==((x6037._3)))) {
      if(((x6036._2)==((x6037._2)))) {
        if(((x6036._1)==((x6037._1)))) {
          if(((x6036._4)==((x6037._4)))) {
            x6038 = 0;
          } else {
            x6038 = 1;
          };
        } else {
          x6038 = 1;
        };
      } else {
        x6038 = 1;
      };
    } else {
      x6038 = 1;
    };
    int x6060 = x6038;
    return x6060; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x5904)  { 
    int x5905 = 0;
    int x5906 = x5905;
    x5905 = (x5906^(((((HASH((x5904._2)))+(-1640531527))+((x5906<<(6))))+((x5906>>(2))))));
    int x5916 = x5905;
    x5905 = (x5916^(((((HASH((x5904._3)))+(-1640531527))+((x5916<<(6))))+((x5916>>(2))))));
    int x5926 = x5905;
    x5905 = (x5926^(((((HASH((x5904._4)))+(-1640531527))+((x5926<<(6))))+((x5926>>(2))))));
    int x5936 = x5905;
    return x5936; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x5938, const struct SEntry8_IIIITIIB& x5939) { 
    int x5940 = 0;
    if(((x5938._2)==((x5939._2)))) {
      if(((x5938._3)==((x5939._3)))) {
        if(((x5938._4)==((x5939._4)))) {
          x5940 = 0;
        } else {
          x5940 = 1;
        };
      } else {
        x5940 = 1;
      };
    } else {
      x5940 = 1;
    };
    int x5957 = x5940;
    return x5957; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x5804)  { 
    int x5805 = 0;
    int x5806 = x5805;
    x5805 = (x5806^(((((HASH((x5804._3)))+(-1640531527))+((x5806<<(6))))+((x5806>>(2))))));
    int x5816 = x5805;
    x5805 = (x5816^(((((HASH((x5804._2)))+(-1640531527))+((x5816<<(6))))+((x5816>>(2))))));
    int x5826 = x5805;
    x5805 = (x5826^(((((HASH((x5804._1)))+(-1640531527))+((x5826<<(6))))+((x5826>>(2))))));
    int x5836 = x5805;
    return x5836; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x5838, const struct SEntry8_IIIITIIB& x5839) { 
    int x5840 = 0;
    if(((x5838._3)==((x5839._3)))) {
      if(((x5838._2)==((x5839._2)))) {
        if(((x5838._1)==((x5839._1)))) {
          x5840 = 0;
        } else {
          x5840 = 1;
        };
      } else {
        x5840 = 1;
      };
    } else {
      x5840 = 1;
    };
    int x5857 = x5840;
    return x5857; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x5627)  { 
    int x5628 = 0;
    int x5629 = x5628;
    x5628 = (x5629^(((((HASH((x5627._1)))+(-1640531527))+((x5629<<(6))))+((x5629>>(2))))));
    int x5639 = x5628;
    x5628 = (x5639^(((((HASH((x5627._2)))+(-1640531527))+((x5639<<(6))))+((x5639>>(2))))));
    int x5649 = x5628;
    x5628 = (x5649^(((((HASH((x5627._3)))+(-1640531527))+((x5649<<(6))))+((x5649>>(2))))));
    int x5659 = x5628;
    x5628 = (x5659^(((((HASH((x5627._4)))+(-1640531527))+((x5659<<(6))))+((x5659>>(2))))));
    int x5669 = x5628;
    x5628 = (x5669^(((((HASH((x5627._5)))+(-1640531527))+((x5669<<(6))))+((x5669>>(2))))));
    int x5679 = x5628;
    x5628 = (x5679^(((((HASH((x5627._6)))+(-1640531527))+((x5679<<(6))))+((x5679>>(2))))));
    int x5689 = x5628;
    x5628 = (x5689^(((((HASH((x5627._7)))+(-1640531527))+((x5689<<(6))))+((x5689>>(2))))));
    int x5699 = x5628;
    x5628 = (x5699^(((((HASH((x5627._8)))+(-1640531527))+((x5699<<(6))))+((x5699>>(2))))));
    int x5709 = x5628;
    return x5709; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x5711, const struct SEntry8_IIIIITDS& x5712) { 
    int x5713 = 0;
    if(((x5711._1)==((x5712._1)))) {
      if(((x5711._2)==((x5712._2)))) {
        if(((x5711._3)==((x5712._3)))) {
          if(((x5711._4)==((x5712._4)))) {
            if(((x5711._5)==((x5712._5)))) {
              if(((x5711._6)==((x5712._6)))) {
                if(((x5711._7)==((x5712._7)))) {
                  if(((x5711._8)==((x5712._8)))) {
                    x5713 = 0;
                  } else {
                    x5713 = 1;
                  };
                } else {
                  x5713 = 1;
                };
              } else {
                x5713 = 1;
              };
            } else {
              x5713 = 1;
            };
          } else {
            x5713 = 1;
          };
        } else {
          x5713 = 1;
        };
      } else {
        x5713 = 1;
      };
    } else {
      x5713 = 1;
    };
    int x5755 = x5713;
    return x5755; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x6063)  { 
    int x6064 = 0;
    int x6065 = x6064;
    x6064 = (x6065^(((((HASH((x6063._1)))+(-1640531527))+((x6065<<(6))))+((x6065>>(2))))));
    int x6075 = x6064;
    x6064 = (x6075^(((((HASH((x6063._2)))+(-1640531527))+((x6075<<(6))))+((x6075>>(2))))));
    int x6085 = x6064;
    x6064 = (x6085^(((((HASH((x6063._3)))+(-1640531527))+((x6085<<(6))))+((x6085>>(2))))));
    int x6095 = x6064;
    return x6095; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6097, const struct SEntry10_IIIIIITIDS& x6098) { 
    int x6099 = 0;
    if(((x6097._1)==((x6098._1)))) {
      if(((x6097._2)==((x6098._2)))) {
        if(((x6097._3)==((x6098._3)))) {
          x6099 = 0;
        } else {
          x6099 = 1;
        };
      } else {
        x6099 = 1;
      };
    } else {
      x6099 = 1;
    };
    int x6116 = x6099;
    return x6116; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5579)  { 
    int x5580 = 0;
    int x5581 = x5580;
    x5580 = (x5581^(((((HASH((x5579._2)))+(-1640531527))+((x5581<<(6))))+((x5581>>(2))))));
    int x5591 = x5580;
    x5580 = (x5591^(((((HASH((x5579._3)))+(-1640531527))+((x5591<<(6))))+((x5591>>(2))))));
    int x5601 = x5580;
    return x5601; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5603, const struct SEntry3_III& x5604) { 
    int x5605 = 0;
    if(((x5603._2)==((x5604._2)))) {
      if(((x5603._3)==((x5604._3)))) {
        x5605 = 0;
      } else {
        x5605 = 1;
      };
    } else {
      x5605 = 1;
    };
    int x5617 = x5605;
    return x5617; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5489)  { 
    int x5490 = 0;
    int x5491 = x5490;
    x5490 = (x5491^(((((HASH((x5489._3)))+(-1640531527))+((x5491<<(6))))+((x5491>>(2))))));
    int x5501 = x5490;
    x5490 = (x5501^(((((HASH((x5489._2)))+(-1640531527))+((x5501<<(6))))+((x5501>>(2))))));
    int x5511 = x5490;
    x5490 = (x5511^(((((HASH((x5489._1)))+(-1640531527))+((x5511<<(6))))+((x5511>>(2))))));
    int x5521 = x5490;
    return x5521; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5523, const struct SEntry3_III& x5524) { 
    int x5525 = 0;
    if(((x5523._3)==((x5524._3)))) {
      if(((x5523._2)==((x5524._2)))) {
        if(((x5523._1)==((x5524._1)))) {
          x5525 = 0;
        } else {
          x5525 = 1;
        };
      } else {
        x5525 = 1;
      };
    } else {
      x5525 = 1;
    };
    int x5542 = x5525;
    return x5542; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6199)  { 
    int x6200 = 0;
    int x6201 = x6200;
    x6200 = (x6201^(((((HASH((x6199._2)))+(-1640531527))+((x6201<<(6))))+((x6201>>(2))))));
    int x6211 = x6200;
    x6200 = (x6211^(((((HASH((x6199._3)))+(-1640531527))+((x6211<<(6))))+((x6211>>(2))))));
    int x6221 = x6200;
    x6200 = (x6221^(((((HASH((x6199._6)))+(-1640531527))+((x6221<<(6))))+((x6221>>(2))))));
    int x6231 = x6200;
    return x6231; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6233, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6234) { 
    int x6235 = 0;
    if(((x6233._2)==((x6234._2)))) {
      if(((x6233._3)==((x6234._3)))) {
        if(((x6233._6)==((x6234._6)))) {
          x6235 = 0;
        } else {
          x6235 = 1;
        };
      } else {
        x6235 = 1;
      };
    } else {
      x6235 = 1;
    };
    int x6252 = x6235;
    return x6252; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5545)  { 
    int x5546 = 0;
    int x5547 = x5546;
    x5546 = (x5547^(((((HASH((x5545._2)))+(-1640531527))+((x5547<<(6))))+((x5547>>(2))))));
    int x5557 = x5546;
    x5546 = (x5557^(((((HASH((x5545._3)))+(-1640531527))+((x5557<<(6))))+((x5557>>(2))))));
    int x5567 = x5546;
    return x5567; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5569, const struct SEntry3_III& x5570) { 
    int x5571 = x5569._1;
    int x5572 = x5570._1;
    return ((x5571==(x5572)) ? 0 : ((x5571>(x5572)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6154)  { 
    int x6155 = 0;
    int x6156 = x6155;
    x6155 = (x6156^(((((HASH((x6154._2)))+(-1640531527))+((x6156<<(6))))+((x6156>>(2))))));
    int x6166 = x6155;
    x6155 = (x6166^(((((HASH((x6154._3)))+(-1640531527))+((x6166<<(6))))+((x6166>>(2))))));
    int x6176 = x6155;
    x6155 = (x6176^(((((HASH((x6154._6)))+(-1640531527))+((x6176<<(6))))+((x6176>>(2))))));
    int x6186 = x6155;
    return x6186; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6188, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6189) { 
    int x6192 = strcmpi((x6188._4).data_, (x6189._4).data_);
    return ((x6192>(0)) ? 1 : ((x6192<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x5860)  { 
    int x5861 = 0;
    int x5862 = x5861;
    x5861 = (x5862^(((((HASH((x5860._2)))+(-1640531527))+((x5862<<(6))))+((x5862>>(2))))));
    int x5872 = x5861;
    x5861 = (x5872^(((((HASH((x5860._3)))+(-1640531527))+((x5872<<(6))))+((x5872>>(2))))));
    int x5882 = x5861;
    x5861 = (x5882^(((((HASH((x5860._4)))+(-1640531527))+((x5882<<(6))))+((x5882>>(2))))));
    int x5892 = x5861;
    return x5892; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x5894, const struct SEntry8_IIIITIIB& x5895) { 
    int x5896 = x5894._1;
    int x5897 = x5895._1;
    return ((x5896==(x5897)) ? 0 : ((x5896>(x5897)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t6 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x5766)  { 
    int x5767 = 0;
    int x5770 = x5767;
    x5767 = ((x5770*(5))+(((x5766._1)-(1))));
    int x5774 = x5767;
    return x5774; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x5763, const struct SEntry9_ISSSSSSDD& x5764) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x5970)  { 
    int x5971 = 0;
    int x5974 = x5971;
    x5971 = ((x5974*(5))+(((x5970._2)-(1))));
    int x5980 = x5971;
    x5971 = ((x5980*(10))+(((x5970._1)-(1))));
    int x5984 = x5971;
    return x5984; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x5967, const struct SEntry11_IISSSSSSDDI& x5968) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100002 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x5785)  { 
    int x5786 = 0;
    int x5789 = x5786;
    x5786 = ((x5789*(100001))+(((x5785._1)-(1))));
    int x5793 = x5786;
    return x5793; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x5782, const struct SEntry5_IISDS& x5783) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6131)  { 
    int x6132 = 0;
    int x6135 = x6132;
    x6132 = ((x6135*(5))+(((x6131._3)-(1))));
    int x6141 = x6132;
    x6132 = ((x6141*(10))+(((x6131._2)-(1))));
    int x6147 = x6132;
    x6132 = ((x6147*(3000))+(((x6131._1)-(1))));
    int x6151 = x6132;
    return x6151; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6128, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6129) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x6265)  { 
    int x6266 = 0;
    int x6269 = x6266;
    x6266 = ((x6269*(5))+(((x6265._2)-(1))));
    int x6275 = x6266;
    x6266 = ((x6275*(100000))+(((x6265._1)-(1))));
    int x6279 = x6266;
    return x6279; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x6262, const struct SEntry17_IIISSSSSSSSSSIIIS& x6263) { 
    return 0; 
  }
};
typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx321, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_1, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;

typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,historyTblIdx0Type> historyTblStoreType;

typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t6, 5> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,warehouseTblIdx0Type> warehouseTblStoreType;

typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100002, 100001> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,itemTblIdx0Type> itemTblStoreType;

typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx321, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_1, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;

typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11, 50> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,districtTblIdx0Type> districtTblStoreType;

typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx3214, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;

typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001, 150000> customerTblIdx0Type;
typedef SlicedMedHeapIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;

typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001, 500000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,stockTblIdx0Type> stockTblStoreType;

struct Partition { 
  Partition():
  newOrderTbl(), newOrderTblIdx0(*(newOrderTblIdx0Type *)newOrderTbl.index[0]), newOrderTblIdx1(*(newOrderTblIdx1Type *)newOrderTbl.index[1]), 
  historyTbl(), historyTblIdx0(*(historyTblIdx0Type *)historyTbl.index[0]), 
  warehouseTbl(), warehouseTblIdx0(*(warehouseTblIdx0Type *)warehouseTbl.index[0]), 
  itemTbl(), itemTblIdx0(*(itemTblIdx0Type *)itemTbl.index[0]), 
  orderTbl(), orderTblIdx0(*(orderTblIdx0Type *)orderTbl.index[0]), orderTblIdx1(*(orderTblIdx1Type *)orderTbl.index[1]), 
  districtTbl(), districtTblIdx0(*(districtTblIdx0Type *)districtTbl.index[0]), 
  orderLineTbl(), orderLineTblIdx0(*(orderLineTblIdx0Type *)orderLineTbl.index[0]), orderLineTblIdx1(*(orderLineTblIdx1Type *)orderLineTbl.index[1]), 
  customerTbl(), customerTblIdx0(*(customerTblIdx0Type *)customerTbl.index[0]), customerTblIdx1(*(customerTblIdx1Type *)customerTbl.index[1]), 
  stockTbl(), stockTblIdx0(*(stockTblIdx0Type *)stockTbl.index[0])  {
    memset(xactCounts, 0, sizeof(uint) *5); }
  
  newOrderTblStoreType  newOrderTbl;
  newOrderTblIdx0Type& newOrderTblIdx0;
  newOrderTblIdx1Type& newOrderTblIdx1;
  
  historyTblStoreType  historyTbl;
  historyTblIdx0Type& historyTblIdx0;
  
  warehouseTblStoreType  warehouseTbl;
  warehouseTblIdx0Type& warehouseTblIdx0;
  
  itemTblStoreType  itemTbl;
  itemTblIdx0Type& itemTblIdx0;
  
  orderTblStoreType  orderTbl;
  orderTblIdx0Type& orderTblIdx0;
  orderTblIdx1Type& orderTblIdx1;
  
  districtTblStoreType  districtTbl;
  districtTblIdx0Type& districtTblIdx0;
  
  orderLineTblStoreType  orderLineTbl;
  orderLineTblIdx0Type& orderLineTblIdx0;
  orderLineTblIdx1Type& orderLineTblIdx1;
  
  customerTblStoreType  customerTbl;
  customerTblIdx0Type& customerTblIdx0;
  customerTblIdx1Type& customerTblIdx1;
  
  stockTblStoreType  stockTbl;
  stockTblIdx0Type& stockTblIdx0;
  
  struct SEntry3_III x9266;
  struct SEntry11_IISSSSSSDDI x8845;
  struct SEntry17_IIISSSSSSSSSSIIIS x9279;
  struct SEntry8_IIIITIIB x8710;
  struct SEntry5_IISDS x9225;
  struct SEntry10_IIIIIITIDS x8858;
  struct SEntry11_IISSSSSSDDI x9037;
  struct SEntry9_ISSSSSSDD x9032;
  struct SEntry17_IIISSSSSSSSSSIIIS x8878;
  struct SEntry10_IIIIIITIDS x8719;
  struct SEntry11_IISSSSSSDDI x9255;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8941;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9249;
  struct SEntry9_ISSSSSSDD x9252;
  struct SEntry17_IIISSSSSSSSSSIIIS x9348;
  struct SEntry10_IIIIIITIDS x9330;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8723;
  struct SEntry8_IIIIITDS x9049;
  struct SEntry10_IIIIIITIDS x8933;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9059;
  struct SEntry8_IIIITIIB x9263;
  struct SEntry8_IIIITIIB x8923;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9062;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8938;
  struct SEntry3_III x8699;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9026;
  
  int partitionID;
  uint failedNO;
  uint xactCounts[5];
         
  FORCE_INLINE void DeliveryTx(int x15, date x16, int x17, int x18) {
    int orderIDs[10];
    int x23 = 1;
    while(1) {
      
      int x25 = x23;
      if (!((x25<=(10)))) break; 
      
      int x32 = x23;
      x8699._2 = x32;
      x8699._3 = x17;
      struct SEntry3_III* x13250 = newOrderTblIdx1.get(x8699);
      if((x13250!=(NULL))) {
        int x8703 = x13250->_1;
        int x41 = x23;
        orderIDs[(x41-(1))] = x8703;
        newOrderTbl.del(x13250);
        int x46 = x23;
        x8710._1 = x8703;
        x8710._2 = x46;
        x8710._3 = x17;
        struct SEntry8_IIIITIIB* x13263 = orderTblIdx0.get(x8710);
        x13263->_6 = x18;
        double x55 = 0.0;
        int x57 = x23;
        x8719._1 = x8703;
        x8719._2 = x57;
        x8719._3 = x17;
        //sliceRes 
        typedef typename orderLineTblIdx1Type::IFN IDXFN16187;
        HASH_RES_t h16187 = IDXFN16187::hash(x8719);
        auto* x16187 = &(orderLineTblIdx1.buckets_[h16187 % orderLineTblIdx1.size_]);
        if(x16187 -> head.obj) {
           do {
             if(h16187 == x16187->hash && !IDXFN16187::cmp(x8719, *x16187->head.obj))
               break;
           } while((x16187 = x16187->nxt));
        } else { 
           x16187 = nullptr;
        }
        if((x16187 == nullptr)) {
        } else {
          //sliceResMapNoUpd 
          auto* nx16187 = &x16187->head;
          do {
            auto orderLineEntry = nx16187->obj;
            orderLineEntry->_7 = x16;
            double x62 = x55;
            x55 = (x62+((orderLineEntry->_9)));
          } while((nx16187 = nx16187->nxt));
        };
        int x70 = x23;
        x8723._1 = (x13263->_4);
        x8723._2 = x70;
        x8723._3 = x17;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13285 = customerTblIdx0.get(x8723);
        double x74 = x55;
        x13285->_17 += x74;
        x13285->_20 += 1;
      } else {
        int x78 = failedDel;
        failedDel = (1+(x78));
        int x81 = x23;
        orderIDs[(x81-(1))] = 0;
      };
      int x85 = x23;
      x23 = (x85+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void StockLevelTx(int x89, date x90, int x91, int x92, int x93, int x94) {
    x8845._1 = x93;
    x8845._2 = x92;
    struct SEntry11_IISSSSSSDDI* x13358 = districtTblIdx0.get(x8845);
    int x8847 = x13358->_11;
    int x103 = (x8847-(20));
    unordered_set<int> unique_ol_i_id({}); //setApply1
    while(1) {
      
      int x108 = x103;
      if (!((x108<(x8847)))) break; 
      
      int x110 = x103;
      x8858._1 = x110;
      x8858._2 = x93;
      x8858._3 = x92;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN16237;
      HASH_RES_t h16237 = IDXFN16237::hash(x8858);
      auto* x16237 = &(orderLineTblIdx1.buckets_[h16237 % orderLineTblIdx1.size_]);
      if(x16237 -> head.obj) {
         do {
           if(h16237 == x16237->hash && !IDXFN16237::cmp(x8858, *x16237->head.obj))
             break;
         } while((x16237 = x16237->nxt));
      } else { 
         x16237 = nullptr;
      }
      if((x16237 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx16237 = &x16237->head;
        do {
          auto orderLineEntry = nx16237->obj;
          int x8876 = orderLineEntry->_5;
          x8878._1 = x8876;
          x8878._2 = x92;
          struct SEntry17_IIISSSSSSSSSSIIIS* x13373 = stockTblIdx0.get(x8878);
          if(((x13373->_3)<(x94))) {
            unique_ol_i_id.insert(x8876);
          };
        } while((nx16237 = nx16237->nxt));
      };
      int x127 = x103;
      x103 = (x127+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void OrderStatusTx(int x133, date x134, int x135, int x136, int x137, int x138, int x139, PString x140) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite26724 = 0;
    if((x138>(0))) {
      x8938._2 = x137;
      x8938._3 = x136;
      x8938._6 = x140;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x26728 = customerTblIdx1.get(x8938);
      ite26724 = x26728;
    } else {
      x8941._1 = x139;
      x8941._2 = x137;
      x8941._3 = x136;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x26733 = customerTblIdx0.get(x8941);
      ite26724 = x26733;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x8920 = ite26724;
    x8923._2 = x137;
    x8923._3 = x136;
    x8923._4 = (x8920->_3);
    struct SEntry8_IIIITIIB* x13436 = orderTblIdx1.get(x8923);
    int ite26743 = 0;
    if((x13436==(NULL))) {
      int x26744 = failedOS;
      failedOS = (1+(x26744));
      ite26743 = 0;
    } else {
      x8933._1 = (x13436->_1);
      x8933._2 = x137;
      x8933._3 = x136;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN26752;
      HASH_RES_t h26752 = IDXFN26752::hash(x8933);
      auto* x26752 = &(orderLineTblIdx1.buckets_[h26752 % orderLineTblIdx1.size_]);
      if(x26752 -> head.obj) {
         do {
           if(h26752 == x26752->hash && !IDXFN26752::cmp(x8933, *x26752->head.obj))
             break;
         } while((x26752 = x26752->nxt));
      } else { 
         x26752 = nullptr;
      }
      if((x26752 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx26752 = &x26752->head;
        do {
          auto orderLineEntry = nx26752->obj;
          int x178 = 1;
        } while((nx26752 = nx26752->nxt));
      };
      ite26743 = 1;
    };
    int x182 = ite26743;
    clearTempMem();
  }
  FORCE_INLINE void PaymentTx(int x183, date x184, int x185, int x186, int x187, int x188, int x189, int x190, int x191, PString x192, double x193) {
    int x195 = 0;
    int x197 = x189%(numThreads);
    if((x197==(partitionID))) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite26807 = 0;
      if((x188>(0))) {
        x9059._2 = x190;
        x9059._3 = x189;
        x9059._6 = x192;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x26811 = customerTblIdx1.get(x9059);
        ite26807 = x26811;
      } else {
        x9062._1 = x191;
        x9062._2 = x190;
        x9062._3 = x189;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x26816 = customerTblIdx0.get(x9062);
        ite26807 = x26816;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x8989 = ite26807;
      int x8991 = x8989->_1;
      x195 = x8991;
      char* x28179 = strstr((x8989->_14).data_, "BC");
      if((x28179!=(NULL))) {
        PString x3079 = PString(500);
        x3079.append(x8991);
        x3079.append(' ');
        x3079.append(x190);
        x3079.append(' ');
        x3079.append(x189);
        x3079.append(' ');
        x3079.append(x187);
        x3079.append(' ');
        x3079.append(x186);
        x3079.append(' ');
        x3079.append('$');
        x3079.append(x193);
        x3079.append(' ');
        x3079.appendDate(x184);
        x3079.append(' ');
        x3079.append('|');
        x3079.append(' ');
        x3079.append((x8989->_21).data_, 500);
        x8989->_17 += x193;
        x8989->_21 = x3079;
      } else {
        x8989->_17 += x193;
      };
    };
    if(((x186%(numThreads))==(partitionID))) {
      if((x197!=(partitionID))) {
        if((x188>(0))) {
          x9026._2 = x190;
          x9026._3 = x189;
          x9026._6 = x192;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13538 = customerTblIdx1.get(x9026);
          x195 = (x13538->_1);
        } else {
          x195 = x191;
        };
      };
      x9032._1 = x186;
      struct SEntry9_ISSSSSSDD* x13544 = warehouseTblIdx0.get(x9032);
      x13544->_9 += x193;
      x9037._1 = x187;
      x9037._2 = x186;
      struct SEntry11_IISSSSSSDDI* x13549 = districtTblIdx0.get(x9037);
      x13549->_10 += x193;
      PString x3131 = PString(24);
      x3131.append((x13544->_2).data_, 10);
      x3131.append("    ", 4);
      x3131.append((x13549->_3).data_, 10);
      int x267 = x195;
      x9049._1 = x267;
      x9049._2 = x190;
      x9049._3 = x189;
      x9049._4 = x187;
      x9049._5 = x186;
      x9049._6 = x184;
      x9049._7 = x193;
      x9049._8 = x3131;
      historyTbl.insert_nocheck(x9049);
    };
    clearTempMem();
  }
  FORCE_INLINE void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
    int x289 = 0;
    int x292 = 0;
    PString idata[x278];
    int x297 = 1;
    int x301 = (x275%(numThreads))==(partitionID);
    int x302 = x301;
    int x305 = 1;
    while(1) {
      
      int x307 = x297;
      int ite27150 = 0;
      if(x307) {
        
        int x308 = x289;
        int x27151 = (x308<(x278));
        ite27150 = x27151;
      } else {
        ite27150 = 0;
      };
      int x26977 = ite27150;
      if (!(x26977)) break; 
      
      int x312 = x289;
      int supwid = x281[x312];
      if((supwid!=(x275))) {
        x305 = 0;
      };
      int x317 = x302;
      int ite27164 = 0;
      if(x317) {
        ite27164 = 1;
      } else {
        
        int x27166 = ((supwid%(numThreads))==(partitionID));
        ite27164 = x27166;
      };
      int x26985 = ite27164;
      x302 = x26985;
      int x323 = x289;
      int x324 = x280[x323];
      x9225._1 = x324;
      struct SEntry5_IISDS* x13680 = itemTblIdx0.get(x9225);
      if((x13680==(NULL))) {
        x297 = 0;
      } else {
        int x330 = x289;
        x284[x330] = (x13680->_3);
        int x333 = x289;
        x283[x333] = (x13680->_4);
        int x336 = x289;
        idata[x336] = (x13680->_5);
      };
      int x340 = x289;
      x289 = (x340+(1));
    };
    x289 = 0;
    int x345 = x297;
    int ite27194 = 0;
    if(x345) {
      
      int x346 = x302;
      int x27195 = x346;
      ite27194 = x27195;
    } else {
      ite27194 = 0;
    };
    int x27009 = ite27194;
    if(x27009) {
      if(x301) {
        x9249._1 = x277;
        x9249._2 = x276;
        x9249._3 = x275;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13706 = customerTblIdx0.get(x9249);
        x9252._1 = x275;
        struct SEntry9_ISSSSSSDD* x13709 = warehouseTblIdx0.get(x9252);
        x9255._1 = x276;
        x9255._2 = x275;
        struct SEntry11_IISSSSSSDDI* x13713 = districtTblIdx0.get(x9255);
        int x9257 = x13713->_11;
        x13713->_11 += 1;
        int x364 = x305;
        x9263._1 = x9257;
        x9263._2 = x276;
        x9263._3 = x275;
        x9263._4 = x277;
        x9263._5 = x273;
        x9263._6 = -1;
        x9263._7 = x278;
        x9263._8 = (x364>(0));
        orderTbl.insert_nocheck(x9263);
        x9266._1 = x9257;
        x9266._2 = x276;
        x9266._3 = x275;
        newOrderTbl.insert_nocheck(x9266);
        double x373 = 0.0;
        while(1) {
          
          int x375 = x289;
          if (!((x375<(x278)))) break; 
          
          int x378 = x289;
          int ol_supply_w_id = x281[x378];
          int x381 = x289;
          int ol_i_id = x280[x381];
          int x384 = x289;
          int ol_quantity = x282[x384];
          x9279._1 = ol_i_id;
          x9279._2 = ol_supply_w_id;
          struct SEntry17_IIISSSSSSSSSSIIIS* x13746 = stockTblIdx0.get(x9279);
          const PString& x9282 = *(&x13746->_4 + (x276-1));
          int x9283 = x13746->_3;
          int x395 = x289;
          x285[x395] = x9283;
          if(((ol_supply_w_id%(numThreads))==(partitionID))) {
            x13746->_3 = (x9283-(ol_quantity));
            if((x9283<=(ol_quantity))) {
              x13746->_3 += 91;
            };
            int x405 = 0;
            if((ol_supply_w_id!=(x275))) {
              x405 = 1;
            };
          };
          int x412 = x289;
          PString& x413 = idata[x412];
          char* x28444 = strstr(x413.data_, "original");
          int ite27261 = 0;
          if((x28444!=(NULL))) {
            
            char* x28450 = strstr((x13746->_17).data_, "original");
            int x27262 = (x28450!=(NULL));
            ite27261 = x27262;
          } else {
            ite27261 = 0;
          };
          int x27071 = ite27261;
          if(x27071) {
            int x418 = x289;
            x286[x418].data_[0] = 'B';
          } else {
            int x420 = x289;
            x286[x420].data_[0] = 'G';
          };
          int x430 = x289;
          double x431 = x283[x430];
          double ol_amount = ((ol_quantity*(x431))*(((1.0+((x13709->_8)))+((x13713->_9)))))*((1.0-((x13706->_16))));
          int x439 = x289;
          x287[x439] = ol_amount;
          double x441 = x373;
          x373 = (x441+(ol_amount));
          int x444 = x289;
          x9330._1 = x9257;
          x9330._2 = x276;
          x9330._3 = x275;
          x9330._4 = (x444+(1));
          x9330._5 = ol_i_id;
          x9330._6 = ol_supply_w_id;
          x9330._8 = ol_quantity;
          x9330._9 = ol_amount;
          x9330._10 = x9282;
          orderLineTbl.insert_nocheck(x9330);
          int x449 = x289;
          x289 = (x449+(1));
        };
      } else {
        while(1) {
          
          int x453 = x289;
          if (!((x453<(x278)))) break; 
          
          int x456 = x289;
          int ol_supply_w_id = x281[x456];
          if(((ol_supply_w_id%(numThreads))==(partitionID))) {
            int x461 = x289;
            int ol_i_id = x280[x461];
            int x464 = x289;
            int ol_quantity = x282[x464];
            x9348._1 = ol_i_id;
            x9348._2 = ol_supply_w_id;
            struct SEntry17_IIISSSSSSSSSSIIIS* x13823 = stockTblIdx0.get(x9348);
            int x9350 = x13823->_3;
            x13823->_3 = (x9350-(ol_quantity));
            if((x9350<=(ol_quantity))) {
              x13823->_3 += 91;
            };
            int x478 = 0;
            if((ol_supply_w_id!=(x275))) {
              x478 = 1;
            };
          };
          int x485 = x289;
          x289 = (x485+(1));
        };
      };
    } else {
      int x490 = failedNO;
      failedNO = (1+(x490));
    };
    clearTempMem();
  }
};
Partition partitions[numThreads];
#include "TPCC.h"

TPCCDataGen tpcc;

void threadFunction(uint8_t thread_id) {
    setAffinity(thread_id);
    //    setSched(SCHED_FIFO);

    Partition& pt = partitions[thread_id];
    pt.partitionID = thread_id;
    isReady[thread_id] = true;
    while (!startExecution);

    for (size_t i = 0; i < numPrograms; ++i) {
        Program *prg = tpcc.programs[i];
        switch (prg->id) {
            case NEWORDER:
            {
                NewOrder& p = *(NewOrder *) prg;
                pt.xactCounts[0]++;
                pt.NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
                break;
            }
            case PAYMENTBYID:
            {
                PaymentById& p = *(PaymentById *) prg;
                pt.xactCounts[1]++;
                pt.PaymentTx( false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
                break;
            }
            case PAYMENTBYNAME:
            {
                PaymentByName& p = *(PaymentByName *) prg;
                pt.xactCounts[1]++;
                pt.PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
                break;
            }
            case ORDERSTATUSBYID:
            {
                OrderStatusById &p = *(OrderStatusById *) prg;
                pt.xactCounts[2]++;
                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
                break;
            }
            case ORDERSTATUSBYNAME:
            {
                OrderStatusByName &p = *(OrderStatusByName *) prg;
                pt.xactCounts[2]++;
                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
                break;
            }
            case DELIVERY:
            {
                Delivery &p = *(Delivery *) prg;
                pt.xactCounts[3]++;
                pt.DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
                break;
            }
            case STOCKLEVEL:
            {
                StockLevel &p = *(StockLevel *) prg;
                pt.xactCounts[4]++;
                pt.StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
                break;
            }
            default: cerr << "UNKNOWN PROGRAM TYPE" << endl;

        }
    }
    hasFinished = true;
}

       
/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  #ifndef NORESIZE
  cout << "Index Resizing warning disabled" << endl;
  #endif
  
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
  Timepoint startTime, endTime;
  
  
  //CALLGRIND_START_INSTRUMENTATION;
  for (uint8_t i = 0; i < numThreads; ++i) {
      workers[i] = std::thread(threadFunction, i);
  }
  bool all_ready = true;
  //check if all worker threads are ready. Execution can be started once all threads finish startup procedure
  while (true) {
      for (uint8_t i = 0; i < numThreads; ++i) {
          if (isReady[i] == false) {
              all_ready = false;
              break;
          }
      }
      if (all_ready) {
          startTime = Now;
          startExecution = true;
          break;
      }
  
      all_ready = true;
  }
  
  for (uint8_t i = 0; i < numThreads; ++i) {
      workers[i].join();
  }
  endTime = Now;
  uint totalPrgsExec = 0;
  for (int i = 0; i < numThreads; ++i) {
  
      cout << "\n Thread " << i << " : ";
      for (int x = 0; x < 5; ++x) {
          cout << partitions[i].xactCounts[x] << "  ";
      }
  }
  failedNO = partitions[0].failedNO;
  for (int i = 0; i < 5; ++i ) {
    xactCounts[i] = partitions[0].xactCounts[i];
    totalPrgsExec += partitions[0].xactCounts[i];
  }
  
  cout << endl;
  //CALLGRIND_STOP_INSTRUMENTATION;
  //CALLGRIND_DUMP_STATS;
  
  auto execTime = DurationMS(endTime - startTime);
  cout << "Failed NO = " << failedNO << endl;
  cout << "Failed Del = " << failedDel << endl;
  cout << "Failed OS = " << failedOS << endl;
  cout << "Total time = " << execTime << " ms" << endl;
  uint failedCount[] = {failedNO, 0, failedOS, failedDel / 10, 0};
  cout << "Total transactions = " << totalPrgsExec << "   NewOrder = " << xactCounts[0] << endl;
  cout << "TpmC = " << fixed << (xactCounts[0] - failedNO)* 60000.0 / execTime << endl;
  
  
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABCDEFGILNOQRSUVXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT_P(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(itemTblIdx0, info);
  info << "\n}\n";
  info.close();
  
  
  #ifdef VERIFY_TPCC
      warehouseTblIdx0Type warehouseTblIdx0;
      districtTblIdx0Type districtTblIdx0;
      customerTblIdx0Type customerTblIdx0;
      orderTblIdx0Type orderTblIdx0;
      newOrderTblIdx0Type newOrderTblIdx0;
      orderLineTblIdx0Type orderLineTblIdx0;
      itemTblIdx0Type itemTblIdx0;
      stockTblIdx0Type stockTblIdx0;
      historyTblIdx0Type historyTblIdx0;
  
      warehouseTblIdx0.idxId = 0;
      districtTblIdx0.idxId = 0;
      customerTblIdx0.idxId = 0;
      orderTblIdx0.idxId = 0;
      newOrderTblIdx0.idxId = 0;
      orderLineTblIdx0.idxId = 0;
      itemTblIdx0.idxId = 0;
      stockTblIdx0.idxId = 0;
      historyTblIdx0.idxId = 0;
  
      warehouseTblIdx0.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize);
      for (int i = 0; i < numThreads; ++i) {
          partitions[i].warehouseTblIdx0.foreach([&](WarehouseEntry * e) {
              if (CORE_FOR_W(e->_1) == i)
                  warehouseTblIdx0.add(e->copy());
          });
          partitions[i].districtTblIdx0.foreach([&](DistrictEntry * e) {
              if (CORE_FOR_W(e->_2) == i)
                  districtTblIdx0.add(e->copy());
          });
          partitions[i].customerTblIdx0.foreach([&](CustomerEntry * e) {
              if (CORE_FOR_W(e->_3) == i) {
                  customerTblIdx0.add(e->copy());
              }
          });
          partitions[i].orderTblIdx0.foreach([&](OrderEntry * e) {
              if (CORE_FOR_W(e->_3) == i)
                  orderTblIdx0.add(e->copy());
          });
          partitions[i].newOrderTblIdx0.foreach([&](NewOrderEntry * e) {
              if (CORE_FOR_W(e->_3) == i)
                  newOrderTblIdx0.add(e->copy());
          });
          partitions[i].orderLineTblIdx0.foreach([&](OrderLineEntry * e) {
              if (CORE_FOR_W(e->_3) == i)
                  orderLineTblIdx0.add(e->copy());
          });
          partitions[0].itemTblIdx0.foreach([&](ItemEntry * e) {
                  itemTblIdx0.add(e->copy());
          });
          partitions[i].stockTblIdx0.foreach([&](StockEntry * e) {
              if (CORE_FOR_W(e->_2) == i)
                  stockTblIdx0.add(e->copy());
          });
  
          partitions[i].historyTblIdx0.foreach([&](HistoryEntry * e) {
              if (CORE_FOR_W(e->_5) == i) {
                  historyTblIdx0.add(e->copy());
              }
          });
      }
  
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
