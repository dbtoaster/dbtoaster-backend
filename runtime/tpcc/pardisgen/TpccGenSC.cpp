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

#ifndef NUMTHREADS
  #define NUMTHREADS 1
#endif

struct Partition;
const int numThreads = NUMTHREADS;
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
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt; void* backPtrs[8];
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry8_IIIITIIB* copy() const {  SEntry8_IIIITIIB* ptr = (SEntry8_IIIITIIB*) malloc(sizeof(SEntry8_IIIITIIB)); new(ptr) SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
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
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry8_IIIIITDS* copy() const {  SEntry8_IIIIITDS* ptr = (SEntry8_IIIIITDS*) malloc(sizeof(SEntry8_IIIIITDS)); new(ptr) SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, _8);  return ptr;}
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry17_IIISSSSSSSSSSIIIS* copy() const {  SEntry17_IIISSSSSSSSSSIIIS* ptr = (SEntry17_IIISSSSSSSSSSIIIS*) malloc(sizeof(SEntry17_IIISSSSSSSSSSIIIS)); new(ptr) SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17);  return ptr;}
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  FORCE_INLINE SEntry10_IIIIIITIDS* copy() const {  SEntry10_IIIIIITIDS* ptr = (SEntry10_IIIIIITIDS*) malloc(sizeof(SEntry10_IIIIIITIDS)); new(ptr) SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10);  return ptr;}
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
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6302)  { 
    int x6303 = 0;
    int x6304 = x6303;
    x6303 = (x6304^(((((HASH((x6302._2)))+(-1640531527))+((x6304<<(6))))+((x6304>>(2))))));
    int x6314 = x6303;
    x6303 = (x6314^(((((HASH((x6302._3)))+(-1640531527))+((x6314<<(6))))+((x6314>>(2))))));
    int x6324 = x6303;
    x6303 = (x6324^(((((HASH((x6302._4)))+(-1640531527))+((x6324<<(6))))+((x6324>>(2))))));
    int x6334 = x6303;
    return x6334; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6336, const struct SEntry8_IIIITIIB& x6337) { 
    int x6338 = 0;
    if(((x6336._2)==((x6337._2)))) {
      if(((x6336._3)==((x6337._3)))) {
        if(((x6336._4)==((x6337._4)))) {
          x6338 = 0;
        } else {
          x6338 = 1;
        };
      } else {
        x6338 = 1;
      };
    } else {
      x6338 = 1;
    };
    int x6355 = x6338;
    return x6355; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx3214 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x6411)  { 
    int x6412 = 0;
    int x6413 = x6412;
    x6412 = (x6413^(((((HASH((x6411._3)))+(-1640531527))+((x6413<<(6))))+((x6413>>(2))))));
    int x6423 = x6412;
    x6412 = (x6423^(((((HASH((x6411._2)))+(-1640531527))+((x6423<<(6))))+((x6423>>(2))))));
    int x6433 = x6412;
    x6412 = (x6433^(((((HASH((x6411._1)))+(-1640531527))+((x6433<<(6))))+((x6433>>(2))))));
    int x6443 = x6412;
    x6412 = (x6443^(((((HASH((x6411._4)))+(-1640531527))+((x6443<<(6))))+((x6443>>(2))))));
    int x6453 = x6412;
    return x6453; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6455, const struct SEntry10_IIIIIITIDS& x6456) { 
    int x6457 = 0;
    if(((x6455._3)==((x6456._3)))) {
      if(((x6455._2)==((x6456._2)))) {
        if(((x6455._1)==((x6456._1)))) {
          if(((x6455._4)==((x6456._4)))) {
            x6457 = 0;
          } else {
            x6457 = 1;
          };
        } else {
          x6457 = 1;
        };
      } else {
        x6457 = 1;
      };
    } else {
      x6457 = 1;
    };
    int x6479 = x6457;
    return x6479; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6547)  { 
    int x6548 = 0;
    int x6549 = x6548;
    x6548 = (x6549^(((((HASH((x6547._3)))+(-1640531527))+((x6549<<(6))))+((x6549>>(2))))));
    int x6559 = x6548;
    x6548 = (x6559^(((((HASH((x6547._2)))+(-1640531527))+((x6559<<(6))))+((x6559>>(2))))));
    int x6569 = x6548;
    x6548 = (x6569^(((((HASH((x6547._1)))+(-1640531527))+((x6569<<(6))))+((x6569>>(2))))));
    int x6579 = x6548;
    return x6579; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6581, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6582) { 
    int x6583 = 0;
    if(((x6581._3)==((x6582._3)))) {
      if(((x6581._2)==((x6582._2)))) {
        if(((x6581._1)==((x6582._1)))) {
          x6583 = 0;
        } else {
          x6583 = 1;
        };
      } else {
        x6583 = 1;
      };
    } else {
      x6583 = 1;
    };
    int x6600 = x6583;
    return x6600; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x6002)  { 
    int x6003 = 0;
    int x6004 = x6003;
    x6003 = (x6004^(((((HASH((x6002._1)))+(-1640531527))+((x6004<<(6))))+((x6004>>(2))))));
    int x6014 = x6003;
    x6003 = (x6014^(((((HASH((x6002._2)))+(-1640531527))+((x6014<<(6))))+((x6014>>(2))))));
    int x6024 = x6003;
    x6003 = (x6024^(((((HASH((x6002._3)))+(-1640531527))+((x6024<<(6))))+((x6024>>(2))))));
    int x6034 = x6003;
    x6003 = (x6034^(((((HASH((x6002._4)))+(-1640531527))+((x6034<<(6))))+((x6034>>(2))))));
    int x6044 = x6003;
    x6003 = (x6044^(((((HASH((x6002._5)))+(-1640531527))+((x6044<<(6))))+((x6044>>(2))))));
    int x6054 = x6003;
    x6003 = (x6054^(((((HASH((x6002._6)))+(-1640531527))+((x6054<<(6))))+((x6054>>(2))))));
    int x6064 = x6003;
    x6003 = (x6064^(((((HASH((x6002._7)))+(-1640531527))+((x6064<<(6))))+((x6064>>(2))))));
    int x6074 = x6003;
    x6003 = (x6074^(((((HASH((x6002._8)))+(-1640531527))+((x6074<<(6))))+((x6074>>(2))))));
    int x6084 = x6003;
    return x6084; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x6086, const struct SEntry8_IIIIITDS& x6087) { 
    int x6088 = 0;
    if(((x6086._1)==((x6087._1)))) {
      if(((x6086._2)==((x6087._2)))) {
        if(((x6086._3)==((x6087._3)))) {
          if(((x6086._4)==((x6087._4)))) {
            if(((x6086._5)==((x6087._5)))) {
              if(((x6086._6)==((x6087._6)))) {
                if(((x6086._7)==((x6087._7)))) {
                  if(((x6086._8)==((x6087._8)))) {
                    x6088 = 0;
                  } else {
                    x6088 = 1;
                  };
                } else {
                  x6088 = 1;
                };
              } else {
                x6088 = 1;
              };
            } else {
              x6088 = 1;
            };
          } else {
            x6088 = 1;
          };
        } else {
          x6088 = 1;
        };
      } else {
        x6088 = 1;
      };
    } else {
      x6088 = 1;
    };
    int x6130 = x6088;
    return x6130; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6202)  { 
    int x6203 = 0;
    int x6204 = x6203;
    x6203 = (x6204^(((((HASH((x6202._3)))+(-1640531527))+((x6204<<(6))))+((x6204>>(2))))));
    int x6214 = x6203;
    x6203 = (x6214^(((((HASH((x6202._2)))+(-1640531527))+((x6214<<(6))))+((x6214>>(2))))));
    int x6224 = x6203;
    x6203 = (x6224^(((((HASH((x6202._1)))+(-1640531527))+((x6224<<(6))))+((x6224>>(2))))));
    int x6234 = x6203;
    return x6234; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6236, const struct SEntry8_IIIITIIB& x6237) { 
    int x6238 = 0;
    if(((x6236._3)==((x6237._3)))) {
      if(((x6236._2)==((x6237._2)))) {
        if(((x6236._1)==((x6237._1)))) {
          x6238 = 0;
        } else {
          x6238 = 1;
        };
      } else {
        x6238 = 1;
      };
    } else {
      x6238 = 1;
    };
    int x6255 = x6238;
    return x6255; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x6710)  { 
    int x6711 = 0;
    int x6712 = x6711;
    x6711 = (x6712^(((((HASH((x6710._2)))+(-1640531527))+((x6712<<(6))))+((x6712>>(2))))));
    int x6722 = x6711;
    x6711 = (x6722^(((((HASH((x6710._1)))+(-1640531527))+((x6722<<(6))))+((x6722>>(2))))));
    int x6732 = x6711;
    return x6732; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x6734, const struct SEntry17_IIISSSSSSSSSSIIIS& x6735) { 
    int x6736 = 0;
    if(((x6734._2)==((x6735._2)))) {
      if(((x6734._1)==((x6735._1)))) {
        x6736 = 0;
      } else {
        x6736 = 1;
      };
    } else {
      x6736 = 1;
    };
    int x6748 = x6736;
    return x6748; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5954)  { 
    int x5955 = 0;
    int x5956 = x5955;
    x5955 = (x5956^(((((HASH((x5954._2)))+(-1640531527))+((x5956<<(6))))+((x5956>>(2))))));
    int x5966 = x5955;
    x5955 = (x5966^(((((HASH((x5954._3)))+(-1640531527))+((x5966<<(6))))+((x5966>>(2))))));
    int x5976 = x5955;
    return x5976; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5978, const struct SEntry3_III& x5979) { 
    int x5980 = 0;
    if(((x5978._2)==((x5979._2)))) {
      if(((x5978._3)==((x5979._3)))) {
        x5980 = 0;
      } else {
        x5980 = 1;
      };
    } else {
      x5980 = 1;
    };
    int x5992 = x5980;
    return x5992; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x6482)  { 
    int x6483 = 0;
    int x6484 = x6483;
    x6483 = (x6484^(((((HASH((x6482._1)))+(-1640531527))+((x6484<<(6))))+((x6484>>(2))))));
    int x6494 = x6483;
    x6483 = (x6494^(((((HASH((x6482._2)))+(-1640531527))+((x6494<<(6))))+((x6494>>(2))))));
    int x6504 = x6483;
    x6483 = (x6504^(((((HASH((x6482._3)))+(-1640531527))+((x6504<<(6))))+((x6504>>(2))))));
    int x6514 = x6483;
    return x6514; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6516, const struct SEntry10_IIIIIITIDS& x6517) { 
    int x6518 = 0;
    if(((x6516._1)==((x6517._1)))) {
      if(((x6516._2)==((x6517._2)))) {
        if(((x6516._3)==((x6517._3)))) {
          x6518 = 0;
        } else {
          x6518 = 1;
        };
      } else {
        x6518 = 1;
      };
    } else {
      x6518 = 1;
    };
    int x6535 = x6518;
    return x6535; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5864)  { 
    int x5865 = 0;
    int x5866 = x5865;
    x5865 = (x5866^(((((HASH((x5864._3)))+(-1640531527))+((x5866<<(6))))+((x5866>>(2))))));
    int x5876 = x5865;
    x5865 = (x5876^(((((HASH((x5864._2)))+(-1640531527))+((x5876<<(6))))+((x5876>>(2))))));
    int x5886 = x5865;
    x5865 = (x5886^(((((HASH((x5864._1)))+(-1640531527))+((x5886<<(6))))+((x5886>>(2))))));
    int x5896 = x5865;
    return x5896; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5898, const struct SEntry3_III& x5899) { 
    int x5900 = 0;
    if(((x5898._3)==((x5899._3)))) {
      if(((x5898._2)==((x5899._2)))) {
        if(((x5898._1)==((x5899._1)))) {
          x5900 = 0;
        } else {
          x5900 = 1;
        };
      } else {
        x5900 = 1;
      };
    } else {
      x5900 = 1;
    };
    int x5917 = x5900;
    return x5917; 
  }
};
 struct SEntry5_IISDS_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x6168)  { 
    int x6169 = 0;
    int x6170 = x6169;
    x6169 = (x6170^(((((HASH((x6168._1)))+(-1640531527))+((x6170<<(6))))+((x6170>>(2))))));
    int x6180 = x6169;
    return x6180; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x6182, const struct SEntry5_IISDS& x6183) { 
    int x6184 = 0;
    if(((x6182._1)==((x6183._1)))) {
      x6184 = 0;
    } else {
      x6184 = 1;
    };
    int x6191 = x6184;
    return x6191; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6648)  { 
    int x6649 = 0;
    int x6650 = x6649;
    x6649 = (x6650^(((((HASH((x6648._2)))+(-1640531527))+((x6650<<(6))))+((x6650>>(2))))));
    int x6660 = x6649;
    x6649 = (x6660^(((((HASH((x6648._3)))+(-1640531527))+((x6660<<(6))))+((x6660>>(2))))));
    int x6670 = x6649;
    x6649 = (x6670^(((((HASH((x6648._6)))+(-1640531527))+((x6670<<(6))))+((x6670>>(2))))));
    int x6680 = x6649;
    return x6680; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6682, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6683) { 
    int x6684 = 0;
    if(((x6682._2)==((x6683._2)))) {
      if(((x6682._3)==((x6683._3)))) {
        if(((x6682._6)==((x6683._6)))) {
          x6684 = 0;
        } else {
          x6684 = 1;
        };
      } else {
        x6684 = 1;
      };
    } else {
      x6684 = 1;
    };
    int x6701 = x6684;
    return x6701; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x6138)  { 
    int x6139 = 0;
    int x6140 = x6139;
    x6139 = (x6140^(((((HASH((x6138._1)))+(-1640531527))+((x6140<<(6))))+((x6140>>(2))))));
    int x6150 = x6139;
    return x6150; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x6152, const struct SEntry9_ISSSSSSDD& x6153) { 
    int x6154 = 0;
    if(((x6152._1)==((x6153._1)))) {
      x6154 = 0;
    } else {
      x6154 = 1;
    };
    int x6161 = x6154;
    return x6161; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx21 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x6365)  { 
    int x6366 = 0;
    int x6367 = x6366;
    x6366 = (x6367^(((((HASH((x6365._2)))+(-1640531527))+((x6367<<(6))))+((x6367>>(2))))));
    int x6377 = x6366;
    x6366 = (x6377^(((((HASH((x6365._1)))+(-1640531527))+((x6377<<(6))))+((x6377>>(2))))));
    int x6387 = x6366;
    return x6387; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x6389, const struct SEntry11_IISSSSSSDDI& x6390) { 
    int x6391 = 0;
    if(((x6389._2)==((x6390._2)))) {
      if(((x6389._1)==((x6390._1)))) {
        x6391 = 0;
      } else {
        x6391 = 1;
      };
    } else {
      x6391 = 1;
    };
    int x6403 = x6391;
    return x6403; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5920)  { 
    int x5921 = 0;
    int x5922 = x5921;
    x5921 = (x5922^(((((HASH((x5920._2)))+(-1640531527))+((x5922<<(6))))+((x5922>>(2))))));
    int x5932 = x5921;
    x5921 = (x5932^(((((HASH((x5920._3)))+(-1640531527))+((x5932<<(6))))+((x5932>>(2))))));
    int x5942 = x5921;
    return x5942; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5944, const struct SEntry3_III& x5945) { 
    int x5946 = x5944._1;
    int x5947 = x5945._1;
    return ((x5946==(x5947)) ? 0 : ((x5946>(x5947)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6603)  { 
    int x6604 = 0;
    int x6605 = x6604;
    x6604 = (x6605^(((((HASH((x6603._2)))+(-1640531527))+((x6605<<(6))))+((x6605>>(2))))));
    int x6615 = x6604;
    x6604 = (x6615^(((((HASH((x6603._3)))+(-1640531527))+((x6615<<(6))))+((x6615>>(2))))));
    int x6625 = x6604;
    x6604 = (x6625^(((((HASH((x6603._6)))+(-1640531527))+((x6625<<(6))))+((x6625>>(2))))));
    int x6635 = x6604;
    return x6635; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6637, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6638) { 
    int x6641 = strcmpi((x6637._4).data_, (x6638._4).data_);
    return ((x6641>(0)) ? 1 : ((x6641<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6258)  { 
    int x6259 = 0;
    int x6260 = x6259;
    x6259 = (x6260^(((((HASH((x6258._2)))+(-1640531527))+((x6260<<(6))))+((x6260>>(2))))));
    int x6270 = x6259;
    x6259 = (x6270^(((((HASH((x6258._3)))+(-1640531527))+((x6270<<(6))))+((x6270>>(2))))));
    int x6280 = x6259;
    x6259 = (x6280^(((((HASH((x6258._4)))+(-1640531527))+((x6280<<(6))))+((x6280>>(2))))));
    int x6290 = x6259;
    return x6290; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6292, const struct SEntry8_IIIITIIB& x6293) { 
    int x6294 = x6292._1;
    int x6295 = x6293._1;
    return ((x6294==(x6295)) ? 0 : ((x6294>(x6295)) ? 1 : -1)); 
  }
};
typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx321, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_1, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;

typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,historyTblIdx0Type> historyTblStoreType;

typedef HashIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,warehouseTblIdx0Type> warehouseTblStoreType;

typedef HashIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 1> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,itemTblIdx0Type> itemTblStoreType;

typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx321, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_1, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;

typedef HashIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx21, 1> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,districtTblIdx0Type> districtTblStoreType;

typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx3214, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;

typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321, 1> customerTblIdx0Type;
typedef SlicedMedHeapIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;

typedef HashIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx21, 1> stockTblIdx0Type;
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
  
  
  
  int partitionID;
  uint failedNO;
  uint xactCounts[5];
         
  
  FORCE_INLINE void PaymentTx(int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
    int x28 = 0;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9444 = NULL;
    int x45 = x22%(numThreads);
    if((x21>(0))) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS y19722; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x19722 = &y19722;
      x19722->_2 = x23; x19722->_3 = x22; x19722->_6 = x25;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12874 = customerTblIdx1.get(x19722);
      x9444 = x12874;
    };
    if((x45==(partitionID))) {
      if((x21==(0))) {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS y19731; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x19731 = &y19731;
        x19731->_1 = x24; x19731->_2 = x23; x19731->_3 = x22;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12882 = customerTblIdx0.get(x19731);
        x9444 = x12882;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9461 = x9444;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9463 = x9444;
      x28 = (x9463->_1);
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9466 = x9444;
      char* x20210 = strstr((x9466->_14).data_, "BC");
      if((x20210!=(NULL))) {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9470 = x9444;
        PString x3161 = PString(500);
        x3161.append((x9470->_1));
        x3161.append(' ');
        x3161.append(x23);
        x3161.append(' ');
        x3161.append(x22);
        x3161.append(' ');
        x3161.append(x20);
        x3161.append(' ');
        x3161.append(x19);
        x3161.append(' ');
        x3161.append('$');
        x3161.append(x26);
        x3161.append(' ');
        x3161.appendDate(x17);
        x3161.append(' ');
        x3161.append('|');
        x3161.append(' ');
        x3161.append((x9461->_21).data_, 500);
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9491 = x9444;
        x9491->_17 += x26;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9493 = x9444;
        x9493->_21 = x3161;
      } else {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9495 = x9444;
        x9495->_17 += x26;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9497 = x9444;
      customerTblIdx1.update(x9497);
      customerTblIdx0.update(x9497);
    };
    if(((x19%(numThreads))==(partitionID))) {
      int x80 = xactCounts[1];
      xactCounts[1] = (x80+(1));
      if((x45!=(partitionID))) {
        if((x21>(0))) {
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9508 = x9444;
          x28 = (x9508->_1);
        } else {
          x28 = x24;
        };
      };
      struct SEntry9_ISSSSSSDD y19788; struct SEntry9_ISSSSSSDD* x19788 = &y19788;
      x19788->_1 = x19;
      struct SEntry9_ISSSSSSDD* x12938 = warehouseTblIdx0.get(x19788);
      x12938->_9 += x26;
      struct SEntry11_IISSSSSSDDI y19793; struct SEntry11_IISSSSSSDDI* x19793 = &y19793;
      x19793->_1 = x20; x19793->_2 = x19;
      struct SEntry11_IISSSSSSDDI* x12942 = districtTblIdx0.get(x19793);
      x12942->_10 += x26;
      PString x3214 = PString(24);
      x3214.append((x12938->_2).data_, 10);
      x3214.append("    ", 4);
      x3214.append((x12942->_3).data_, 10);
      int x110 = x28;
      struct SEntry8_IIIIITDS y19805; struct SEntry8_IIIIITDS* x19805 = &y19805;
      x19805->_1 = x110; x19805->_2 = x23; x19805->_3 = x22; x19805->_4 = x20; x19805->_5 = x19; x19805->_6 = x17; x19805->_7 = x26; x19805->_8 = x3214;
      historyTbl.insert_nocheck(x19805);
    };
    clearTempMem();
  }
  FORCE_INLINE void NewOrderTx(int x115, date x116, int x117, int x118, int x119, int x120, int x121, int x122, int* x123, int* x124, int* x125, double* x126, PString* x127, int* x128, PString* x129, double* x130) {
    int x132 = 0;
    int x135 = 0;
    PString idata[x121];
    int x140 = 1;
    int x144 = (x118%(numThreads))==(partitionID);
    int x145 = x144;
    int x148 = 1;
    while(1) {
      
      int x150 = x140;
      int ite19188 = 0;
      if(x150) {
        
        int x151 = x132;
        int x19189 = (x151<(x121));
        ite19188 = x19189;
      } else {
        ite19188 = 0;
      };
      int x19035 = ite19188;
      if (!(x19035)) break; 
      
      int x155 = x132;
      int supwid = x124[x155];
      if((supwid!=(x118))) {
        x148 = 0;
      };
      int x160 = x145;
      int ite19202 = 0;
      if(x160) {
        ite19202 = 1;
      } else {
        
        int x19204 = ((supwid%(numThreads))==(partitionID));
        ite19202 = x19204;
      };
      int x19043 = ite19202;
      x145 = x19043;
      int x166 = x132;
      int x167 = x123[x166];
      struct SEntry5_IISDS y19844; struct SEntry5_IISDS* x19844 = &y19844;
      x19844->_1 = x167;
      struct SEntry5_IISDS* x13069 = itemTblIdx0.get(x19844);
      if((x13069==(NULL))) {
        x140 = 0;
      } else {
        int x173 = x132;
        x127[x173] = (x13069->_3);
        int x176 = x132;
        x126[x176] = (x13069->_4);
        int x179 = x132;
        idata[x179] = (x13069->_5);
      };
      int x183 = x132;
      x132 = (x183+(1));
    };
    x132 = 0;
    int x188 = x145;
    if(x188) {
      int x189 = x140;
      if(x189) {
        if(x144) {
          int x191 = xactCounts[0];
          xactCounts[0] = (x191+(1));
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS y19872; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x19872 = &y19872;
          x19872->_1 = x120; x19872->_2 = x119; x19872->_3 = x118;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13096 = customerTblIdx0.get(x19872);
          struct SEntry9_ISSSSSSDD y19876; struct SEntry9_ISSSSSSDD* x19876 = &y19876;
          x19876->_1 = x118;
          struct SEntry9_ISSSSSSDD* x13099 = warehouseTblIdx0.get(x19876);
          struct SEntry11_IISSSSSSDDI y19880; struct SEntry11_IISSSSSSDDI* x19880 = &y19880;
          x19880->_1 = x119; x19880->_2 = x118;
          struct SEntry11_IISSSSSSDDI* x13102 = districtTblIdx0.get(x19880);
          int x9682 = x13102->_11;
          x13102->_11 += 1;
          int x210 = x148;
          struct SEntry8_IIIITIIB y19887; struct SEntry8_IIIITIIB* x19887 = &y19887;
          x19887->_1 = x9682; x19887->_2 = x119; x19887->_3 = x118; x19887->_4 = x120; x19887->_5 = x116; x19887->_6 = -1; x19887->_7 = x121; x19887->_8 = x210;
          orderTbl.insert_nocheck(x19887);
          struct SEntry3_III y19891; struct SEntry3_III* x19891 = &y19891;
          x19891->_1 = x9682; x19891->_2 = x119; x19891->_3 = x118;
          newOrderTbl.insert_nocheck(x19891);
          double x218 = 0.0;
          while(1) {
            
            int x220 = x132;
            if (!((x220<(x121)))) break; 
            
            int x223 = x132;
            int ol_supply_w_id = x124[x223];
            int x226 = x132;
            int ol_i_id = x123[x226];
            int x229 = x132;
            int ol_quantity = x125[x229];
            struct SEntry17_IIISSSSSSSSSSIIIS y19905; struct SEntry17_IIISSSSSSSSSSIIIS* x19905 = &y19905;
            x19905->_1 = ol_i_id; x19905->_2 = ol_supply_w_id;
            struct SEntry17_IIISSSSSSSSSSIIIS* x13124 = stockTblIdx0.get(x19905);
            const PString& x9706 = *(&x13124->_4 + (x119-1));
            int x9707 = x13124->_3;
            int x240 = x132;
            x128[x240] = x9707;
            if(((ol_supply_w_id%(numThreads))==(partitionID))) {
              x13124->_3 = (x9707-(ol_quantity));
              if((x9707<=(ol_quantity))) {
                x13124->_3 += 91;
              };
              int x250 = 0;
              if((ol_supply_w_id!=(x118))) {
                x250 = 1;
              };
            };
            int x257 = x132;
            PString& x258 = idata[x257];
            char* x20489 = strstr(x258.data_, "original");
            int ite19283 = 0;
            if((x20489!=(NULL))) {
              
              char* x20495 = strstr((x13124->_17).data_, "original");
              int x19284 = (x20495!=(NULL));
              ite19283 = x19284;
            } else {
              ite19283 = 0;
            };
            int x19118 = ite19283;
            if(x19118) {
              int x263 = x132;
              x129[x263].data_[0] = 'B';
            } else {
              int x265 = x132;
              x129[x265].data_[0] = 'G';
            };
            int x275 = x132;
            double x276 = x126[x275];
            double ol_amount = ((ol_quantity*(x276))*(((1.0+((x13099->_8)))+((x13102->_9)))))*((1.0-((x13096->_16))));
            int x284 = x132;
            x130[x284] = ol_amount;
            double x286 = x218;
            x218 = (x286+(ol_amount));
            int x289 = x132;
            struct SEntry10_IIIIIITIDS y19959; struct SEntry10_IIIIIITIDS* x19959 = &y19959;
            x19959->_1 = x9682; x19959->_2 = x119; x19959->_3 = x118; x19959->_4 = (x289+(1)); x19959->_5 = ol_i_id; x19959->_6 = ol_supply_w_id; x19959->_8 = ol_quantity; x19959->_9 = ol_amount; x19959->_10 = x9706;
            orderLineTbl.insert_nocheck(x19959);
            int x294 = x132;
            x132 = (x294+(1));
          };
        } else {
          while(1) {
            
            int x298 = x132;
            if (!((x298<(x121)))) break; 
            
            int x301 = x132;
            int ol_supply_w_id = x124[x301];
            if(((ol_supply_w_id%(numThreads))==(partitionID))) {
              int x306 = x132;
              int ol_i_id = x123[x306];
              int x309 = x132;
              int ol_quantity = x125[x309];
              struct SEntry17_IIISSSSSSSSSSIIIS y19978; struct SEntry17_IIISSSSSSSSSSIIIS* x19978 = &y19978;
              x19978->_1 = ol_i_id; x19978->_2 = ol_supply_w_id;
              struct SEntry17_IIISSSSSSSSSSIIIS* x13192 = stockTblIdx0.get(x19978);
              int x9774 = x13192->_3;
              x13192->_3 = (x9774-(ol_quantity));
              if((x9774<=(ol_quantity))) {
                x13192->_3 += 91;
              };
              int x323 = 0;
              if((ol_supply_w_id!=(x118))) {
                x323 = 1;
              };
            };
            int x330 = x132;
            x132 = (x330+(1));
          };
        };
      } else {
        int x335 = failedNO;
        failedNO = (1+(x335));
      };
    };
    clearTempMem();
  }
  FORCE_INLINE void DeliveryTx(int x340, date x341, int x342, int x343) {
    if(((x342%(numThreads))==(partitionID))) {
      int orderIDs[10];
      int x350 = 1;
      while(1) {
        
        int x352 = x350;
        if (!((x352<=(10)))) break; 
        
        int x359 = x350;
        struct SEntry3_III y20007; struct SEntry3_III* x20007 = &y20007;
        x20007->_2 = x359; x20007->_3 = x342;
        struct SEntry3_III* x13387 = newOrderTblIdx1.get(x20007);
        if((x13387!=(NULL))) {
          int x9975 = x13387->_1;
          int x368 = x350;
          orderIDs[(x368-(1))] = x9975;
          newOrderTbl.del(x13387);
          int x373 = x350;
          struct SEntry8_IIIITIIB y20019; struct SEntry8_IIIITIIB* x20019 = &y20019;
          x20019->_1 = x9975; x20019->_2 = x373; x20019->_3 = x342;
          struct SEntry8_IIIITIIB* x13398 = orderTblIdx0.get(x20019);
          x13398->_6 = x343;
          double x382 = 0.0;
          int x384 = x350;
          struct SEntry10_IIIIIITIDS y20034; struct SEntry10_IIIIIITIDS* x20034 = &y20034;
          x20034->_1 = x9975; x20034->_2 = x384; x20034->_3 = x342;
          orderLineTblIdx1.slice(x20034, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
            orderLineEntry->_7 = x341;
            double x389 = x382;
            x382 = (x389+((orderLineEntry->_9)));
          
          });
          int x397 = x350;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS y20039; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x20039 = &y20039;
          x20039->_1 = (x13398->_4); x20039->_2 = x397; x20039->_3 = x342;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13416 = customerTblIdx0.get(x20039);
          double x401 = x382;
          x13416->_17 += x401;
          x13416->_20 += 1;
        } else {
          int x405 = failedDel;
          failedDel = (1+(x405));
          int x408 = x350;
          orderIDs[(x408-(1))] = 0;
        };
        int x412 = x350;
        x350 = (x412+(1));
      };
      int x417 = xactCounts[3];
      xactCounts[3] = (x417+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void StockLevelTx(int x421, date x422, int x423, int x424, int x425, int x426) {
    if(((x424%(numThreads))==(partitionID))) {
      struct SEntry11_IISSSSSSDDI y20061; struct SEntry11_IISSSSSSDDI* x20061 = &y20061;
      x20061->_1 = x425; x20061->_2 = x424;
      struct SEntry11_IISSSSSSDDI* x13493 = districtTblIdx0.get(x20061);
      int x10137 = x13493->_11;
      int x437 = (x10137-(20));
      unordered_set<int> unique_ol_i_id({}); //setApply1
      while(1) {
        
        int x442 = x437;
        if (!((x442<(x10137)))) break; 
        
        int x444 = x437;
        struct SEntry10_IIIIIITIDS y20085; struct SEntry10_IIIIIITIDS* x20085 = &y20085;
        x20085->_1 = x444; x20085->_2 = x425; x20085->_3 = x424;
        orderLineTblIdx1.slice(x20085, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
          int x10172 = orderLineEntry->_5;
          struct SEntry17_IIISSSSSSSSSSIIIS y20076; struct SEntry17_IIISSSSSSSSSSIIIS* x20076 = &y20076;
          x20076->_1 = x10172; x20076->_2 = x424;
          struct SEntry17_IIISSSSSSSSSSIIIS* x13507 = stockTblIdx0.get(x20076);
          if(((x13507->_3)<(x426))) {
            unique_ol_i_id.insert(x10172);
          };
        
        });
        int x461 = x437;
        x437 = (x461+(1));
      };
      int x468 = xactCounts[4];
      xactCounts[4] = (x468+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void OrderStatusTx(int x472, date x473, int x474, int x475, int x476, int x477, int x478, PString x479) {
    if(((x475%(numThreads))==(partitionID))) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite19607 = 0;
      if((x477>(0))) {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS y20101; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x20101 = &y20101;
        x20101->_2 = x476; x20101->_3 = x475; x20101->_6 = x479;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x19609 = customerTblIdx1.get(x20101);
        ite19607 = x19609;
      } else {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS y20106; struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x20106 = &y20106;
        x20106->_1 = x478; x20106->_2 = x476; x20106->_3 = x475;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x19612 = customerTblIdx0.get(x20106);
        ite19607 = x19612;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10228 = ite19607;
      struct SEntry8_IIIITIIB y20113; struct SEntry8_IIIITIIB* x20113 = &y20113;
      x20113->_2 = x476; x20113->_3 = x475; x20113->_4 = (x10228->_3);
      struct SEntry8_IIIITIIB* x13570 = orderTblIdx1.get(x20113);
      int ite19620 = 0;
      if((x13570==(NULL))) {
        int x19621 = failedOS;
        failedOS = (1+(x19621));
        ite19620 = 0;
      } else {
        struct SEntry10_IIIIIITIDS y20128; struct SEntry10_IIIIIITIDS* x20128 = &y20128;
        x20128->_1 = (x13570->_1); x20128->_2 = x476; x20128->_3 = x475;
        orderLineTblIdx1.slice(x20128, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
          int x519 = 1;
        
        });
        ite19620 = 1;
      };
      int x523 = ite19620;
      int x525 = xactCounts[2];
      xactCounts[2] = (x525+(1));
    };
    clearTempMem();
  }
};
Partition partitions[numThreads];
#define PARTITIONED 1
#include "TPCC.h"

TPCCDataGen tpcc;

void threadFunction(uint8_t thread_id) {
    setAffinity(thread_id);
    //    setSched(SCHED_FIFO);

    Partition& pt = partitions[thread_id];
    pt.partitionID = thread_id;
    isReady[thread_id] = true;
    while (!startExecution);

    for (size_t i = 0; i < numPrograms && !hasFinished; ++i) {
        Program *prg = tpcc.programs[i];
        switch (prg->id) {
            case NEWORDER:
            {
                NewOrder& p = *(NewOrder *) prg;
                pt.NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
                break;
            }
            case PAYMENTBYID:
            {
                PaymentById& p = *(PaymentById *) prg;
                pt.PaymentTx( false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
                break;
            }
            case PAYMENTBYNAME:
            {
                PaymentByName& p = *(PaymentByName *) prg;
                pt.PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
                break;
            }
            case ORDERSTATUSBYID:
            {
                OrderStatusById &p = *(OrderStatusById *) prg;
                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
                break;
            }
            case ORDERSTATUSBYNAME:
            {
                OrderStatusByName &p = *(OrderStatusByName *) prg;
                pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
                break;
            }
            case DELIVERY:
            {
                Delivery &p = *(Delivery *) prg;
                pt.DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
                break;
            }
            case STOCKLEVEL:
            {
                StockLevel &p = *(StockLevel *) prg;
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
  
  cout << "NumThreads = " << numThreads << endl;
  uint globalXactCounts[5] = {0, 0, 0, 0, 0};
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
          globalXactCounts[x] += partitions[i].xactCounts[x];
          totalPrgsExec += partitions[i].xactCounts[x];
      }
  }
  failedNO = partitions[0].failedNO; // WRONG! do max?
  
  
  cout << endl;
  //CALLGRIND_STOP_INSTRUMENTATION;
  //CALLGRIND_DUMP_STATS;
  
  auto execTime = DurationMS(endTime - startTime);
  cout << "Failed NO (approx) = " << failedNO << endl;
  cout << "Failed Del = " << failedDel << endl;
  cout << "Failed OS = " << failedOS << endl;
  cout << "Total time = " << execTime << " ms" << endl;
  uint failedCount[] = {failedNO, 0, failedOS, failedDel / 10, 0};
  cout << "Total transactions = " << totalPrgsExec << "   NewOrder = " << globalXactCounts[0] << endl;
  cout << "TpmC = " << fixed << (globalXactCounts[0])* 60000.0 / execTime << endl;
  
  
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABCDEFINORXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << globalXactCounts[i] - failedCount[i] << ",";
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
  GET_RUN_STAT_P(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(stockTblIdx0, info);
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
                  warehouseTblIdx0.add(e->copy());
          });
          partitions[i].districtTblIdx0.foreach([&](DistrictEntry * e) {
                  districtTblIdx0.add(e->copy());
          });
          partitions[i].customerTblIdx0.foreach([&](CustomerEntry * e) {
              if (CORE_FOR_W(e->_3) == i) {
                  customerTblIdx0.add(e->copy());
              }
          });
          partitions[i].orderTblIdx0.foreach([&](OrderEntry * e) {
                  orderTblIdx0.add(e->copy());
          });
          partitions[i].newOrderTblIdx0.foreach([&](NewOrderEntry * e) {
                  newOrderTblIdx0.add(e->copy());
          });
          partitions[i].orderLineTblIdx0.foreach([&](OrderLineEntry * e) {
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
                  historyTblIdx0.add(e->copy());
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
