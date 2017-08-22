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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x6412)  { 
    int x6413 = 0;
    int x6414 = x6413;
    x6413 = (x6414^(((((HASH((x6412._3)))+(-1640531527))+((x6414<<(6))))+((x6414>>(2))))));
    int x6424 = x6413;
    x6413 = (x6424^(((((HASH((x6412._2)))+(-1640531527))+((x6424<<(6))))+((x6424>>(2))))));
    int x6434 = x6413;
    x6413 = (x6434^(((((HASH((x6412._1)))+(-1640531527))+((x6434<<(6))))+((x6434>>(2))))));
    int x6444 = x6413;
    x6413 = (x6444^(((((HASH((x6412._4)))+(-1640531527))+((x6444<<(6))))+((x6444>>(2))))));
    int x6454 = x6413;
    return x6454; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6456, const struct SEntry10_IIIIIITIDS& x6457) { 
    int x6458 = 0;
    if(((x6456._3)==((x6457._3)))) {
      if(((x6456._2)==((x6457._2)))) {
        if(((x6456._1)==((x6457._1)))) {
          if(((x6456._4)==((x6457._4)))) {
            x6458 = 0;
          } else {
            x6458 = 1;
          };
        } else {
          x6458 = 1;
        };
      } else {
        x6458 = 1;
      };
    } else {
      x6458 = 1;
    };
    int x6480 = x6458;
    return x6480; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6324)  { 
    int x6325 = 0;
    int x6326 = x6325;
    x6325 = (x6326^(((((HASH((x6324._2)))+(-1640531527))+((x6326<<(6))))+((x6326>>(2))))));
    int x6336 = x6325;
    x6325 = (x6336^(((((HASH((x6324._3)))+(-1640531527))+((x6336<<(6))))+((x6336>>(2))))));
    int x6346 = x6325;
    x6325 = (x6346^(((((HASH((x6324._4)))+(-1640531527))+((x6346<<(6))))+((x6346>>(2))))));
    int x6356 = x6325;
    return x6356; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6358, const struct SEntry8_IIIITIIB& x6359) { 
    int x6360 = 0;
    if(((x6358._2)==((x6359._2)))) {
      if(((x6358._3)==((x6359._3)))) {
        if(((x6358._4)==((x6359._4)))) {
          x6360 = 0;
        } else {
          x6360 = 1;
        };
      } else {
        x6360 = 1;
      };
    } else {
      x6360 = 1;
    };
    int x6377 = x6360;
    return x6377; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6224)  { 
    int x6225 = 0;
    int x6226 = x6225;
    x6225 = (x6226^(((((HASH((x6224._3)))+(-1640531527))+((x6226<<(6))))+((x6226>>(2))))));
    int x6236 = x6225;
    x6225 = (x6236^(((((HASH((x6224._2)))+(-1640531527))+((x6236<<(6))))+((x6236>>(2))))));
    int x6246 = x6225;
    x6225 = (x6246^(((((HASH((x6224._1)))+(-1640531527))+((x6246<<(6))))+((x6246>>(2))))));
    int x6256 = x6225;
    return x6256; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6258, const struct SEntry8_IIIITIIB& x6259) { 
    int x6260 = 0;
    if(((x6258._3)==((x6259._3)))) {
      if(((x6258._2)==((x6259._2)))) {
        if(((x6258._1)==((x6259._1)))) {
          x6260 = 0;
        } else {
          x6260 = 1;
        };
      } else {
        x6260 = 1;
      };
    } else {
      x6260 = 1;
    };
    int x6277 = x6260;
    return x6277; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x6047)  { 
    int x6048 = 0;
    int x6049 = x6048;
    x6048 = (x6049^(((((HASH((x6047._1)))+(-1640531527))+((x6049<<(6))))+((x6049>>(2))))));
    int x6059 = x6048;
    x6048 = (x6059^(((((HASH((x6047._2)))+(-1640531527))+((x6059<<(6))))+((x6059>>(2))))));
    int x6069 = x6048;
    x6048 = (x6069^(((((HASH((x6047._3)))+(-1640531527))+((x6069<<(6))))+((x6069>>(2))))));
    int x6079 = x6048;
    x6048 = (x6079^(((((HASH((x6047._4)))+(-1640531527))+((x6079<<(6))))+((x6079>>(2))))));
    int x6089 = x6048;
    x6048 = (x6089^(((((HASH((x6047._5)))+(-1640531527))+((x6089<<(6))))+((x6089>>(2))))));
    int x6099 = x6048;
    x6048 = (x6099^(((((HASH((x6047._6)))+(-1640531527))+((x6099<<(6))))+((x6099>>(2))))));
    int x6109 = x6048;
    x6048 = (x6109^(((((HASH((x6047._7)))+(-1640531527))+((x6109<<(6))))+((x6109>>(2))))));
    int x6119 = x6048;
    x6048 = (x6119^(((((HASH((x6047._8)))+(-1640531527))+((x6119<<(6))))+((x6119>>(2))))));
    int x6129 = x6048;
    return x6129; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x6131, const struct SEntry8_IIIIITDS& x6132) { 
    int x6133 = 0;
    if(((x6131._1)==((x6132._1)))) {
      if(((x6131._2)==((x6132._2)))) {
        if(((x6131._3)==((x6132._3)))) {
          if(((x6131._4)==((x6132._4)))) {
            if(((x6131._5)==((x6132._5)))) {
              if(((x6131._6)==((x6132._6)))) {
                if(((x6131._7)==((x6132._7)))) {
                  if(((x6131._8)==((x6132._8)))) {
                    x6133 = 0;
                  } else {
                    x6133 = 1;
                  };
                } else {
                  x6133 = 1;
                };
              } else {
                x6133 = 1;
              };
            } else {
              x6133 = 1;
            };
          } else {
            x6133 = 1;
          };
        } else {
          x6133 = 1;
        };
      } else {
        x6133 = 1;
      };
    } else {
      x6133 = 1;
    };
    int x6175 = x6133;
    return x6175; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x6483)  { 
    int x6484 = 0;
    int x6485 = x6484;
    x6484 = (x6485^(((((HASH((x6483._1)))+(-1640531527))+((x6485<<(6))))+((x6485>>(2))))));
    int x6495 = x6484;
    x6484 = (x6495^(((((HASH((x6483._2)))+(-1640531527))+((x6495<<(6))))+((x6495>>(2))))));
    int x6505 = x6484;
    x6484 = (x6505^(((((HASH((x6483._3)))+(-1640531527))+((x6505<<(6))))+((x6505>>(2))))));
    int x6515 = x6484;
    return x6515; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x6517, const struct SEntry10_IIIIIITIDS& x6518) { 
    int x6519 = 0;
    if(((x6517._1)==((x6518._1)))) {
      if(((x6517._2)==((x6518._2)))) {
        if(((x6517._3)==((x6518._3)))) {
          x6519 = 0;
        } else {
          x6519 = 1;
        };
      } else {
        x6519 = 1;
      };
    } else {
      x6519 = 1;
    };
    int x6536 = x6519;
    return x6536; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5999)  { 
    int x6000 = 0;
    int x6001 = x6000;
    x6000 = (x6001^(((((HASH((x5999._2)))+(-1640531527))+((x6001<<(6))))+((x6001>>(2))))));
    int x6011 = x6000;
    x6000 = (x6011^(((((HASH((x5999._3)))+(-1640531527))+((x6011<<(6))))+((x6011>>(2))))));
    int x6021 = x6000;
    return x6021; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x6023, const struct SEntry3_III& x6024) { 
    int x6025 = 0;
    if(((x6023._2)==((x6024._2)))) {
      if(((x6023._3)==((x6024._3)))) {
        x6025 = 0;
      } else {
        x6025 = 1;
      };
    } else {
      x6025 = 1;
    };
    int x6037 = x6025;
    return x6037; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5909)  { 
    int x5910 = 0;
    int x5911 = x5910;
    x5910 = (x5911^(((((HASH((x5909._3)))+(-1640531527))+((x5911<<(6))))+((x5911>>(2))))));
    int x5921 = x5910;
    x5910 = (x5921^(((((HASH((x5909._2)))+(-1640531527))+((x5921<<(6))))+((x5921>>(2))))));
    int x5931 = x5910;
    x5910 = (x5931^(((((HASH((x5909._1)))+(-1640531527))+((x5931<<(6))))+((x5931>>(2))))));
    int x5941 = x5910;
    return x5941; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5943, const struct SEntry3_III& x5944) { 
    int x5945 = 0;
    if(((x5943._3)==((x5944._3)))) {
      if(((x5943._2)==((x5944._2)))) {
        if(((x5943._1)==((x5944._1)))) {
          x5945 = 0;
        } else {
          x5945 = 1;
        };
      } else {
        x5945 = 1;
      };
    } else {
      x5945 = 1;
    };
    int x5962 = x5945;
    return x5962; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6619)  { 
    int x6620 = 0;
    int x6621 = x6620;
    x6620 = (x6621^(((((HASH((x6619._2)))+(-1640531527))+((x6621<<(6))))+((x6621>>(2))))));
    int x6631 = x6620;
    x6620 = (x6631^(((((HASH((x6619._3)))+(-1640531527))+((x6631<<(6))))+((x6631>>(2))))));
    int x6641 = x6620;
    x6620 = (x6641^(((((HASH((x6619._6)))+(-1640531527))+((x6641<<(6))))+((x6641>>(2))))));
    int x6651 = x6620;
    return x6651; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6653, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6654) { 
    int x6655 = 0;
    if(((x6653._2)==((x6654._2)))) {
      if(((x6653._3)==((x6654._3)))) {
        if(((x6653._6)==((x6654._6)))) {
          x6655 = 0;
        } else {
          x6655 = 1;
        };
      } else {
        x6655 = 1;
      };
    } else {
      x6655 = 1;
    };
    int x6672 = x6655;
    return x6672; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x5965)  { 
    int x5966 = 0;
    int x5967 = x5966;
    x5966 = (x5967^(((((HASH((x5965._2)))+(-1640531527))+((x5967<<(6))))+((x5967>>(2))))));
    int x5977 = x5966;
    x5966 = (x5977^(((((HASH((x5965._3)))+(-1640531527))+((x5977<<(6))))+((x5977>>(2))))));
    int x5987 = x5966;
    return x5987; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x5989, const struct SEntry3_III& x5990) { 
    int x5991 = x5989._1;
    int x5992 = x5990._1;
    return ((x5991==(x5992)) ? 0 : ((x5991>(x5992)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6574)  { 
    int x6575 = 0;
    int x6576 = x6575;
    x6575 = (x6576^(((((HASH((x6574._2)))+(-1640531527))+((x6576<<(6))))+((x6576>>(2))))));
    int x6586 = x6575;
    x6575 = (x6586^(((((HASH((x6574._3)))+(-1640531527))+((x6586<<(6))))+((x6586>>(2))))));
    int x6596 = x6575;
    x6575 = (x6596^(((((HASH((x6574._6)))+(-1640531527))+((x6596<<(6))))+((x6596>>(2))))));
    int x6606 = x6575;
    return x6606; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6608, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6609) { 
    int x6612 = strcmpi((x6608._4).data_, (x6609._4).data_);
    return ((x6612>(0)) ? 1 : ((x6612<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x6280)  { 
    int x6281 = 0;
    int x6282 = x6281;
    x6281 = (x6282^(((((HASH((x6280._2)))+(-1640531527))+((x6282<<(6))))+((x6282>>(2))))));
    int x6292 = x6281;
    x6281 = (x6292^(((((HASH((x6280._3)))+(-1640531527))+((x6292<<(6))))+((x6292>>(2))))));
    int x6302 = x6281;
    x6281 = (x6302^(((((HASH((x6280._4)))+(-1640531527))+((x6302<<(6))))+((x6302>>(2))))));
    int x6312 = x6281;
    return x6312; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x6314, const struct SEntry8_IIIITIIB& x6315) { 
    int x6316 = x6314._1;
    int x6317 = x6315._1;
    return ((x6316==(x6317)) ? 0 : ((x6316>(x6317)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t6 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x6186)  { 
    int x6187 = 0;
    int x6190 = x6187;
    x6187 = ((x6190*(5))+(((x6186._1)-(1))));
    int x6194 = x6187;
    return x6194; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x6183, const struct SEntry9_ISSSSSSDD& x6184) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x6390)  { 
    int x6391 = 0;
    int x6394 = x6391;
    x6391 = ((x6394*(5))+(((x6390._2)-(1))));
    int x6400 = x6391;
    x6391 = ((x6400*(10))+(((x6390._1)-(1))));
    int x6404 = x6391;
    return x6404; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x6387, const struct SEntry11_IISSSSSSDDI& x6388) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100002 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x6205)  { 
    int x6206 = 0;
    int x6209 = x6206;
    x6206 = ((x6209*(100001))+(((x6205._1)-(1))));
    int x6213 = x6206;
    return x6213; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x6202, const struct SEntry5_IISDS& x6203) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6551)  { 
    int x6552 = 0;
    int x6555 = x6552;
    x6552 = ((x6555*(5))+(((x6551._3)-(1))));
    int x6561 = x6552;
    x6552 = ((x6561*(10))+(((x6551._2)-(1))));
    int x6567 = x6552;
    x6552 = ((x6567*(3000))+(((x6551._1)-(1))));
    int x6571 = x6552;
    return x6571; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6548, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x6549) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x6685)  { 
    int x6686 = 0;
    int x6689 = x6686;
    x6686 = ((x6689*(5))+(((x6685._2)-(1))));
    int x6695 = x6686;
    x6686 = ((x6695*(100000))+(((x6685._1)-(1))));
    int x6699 = x6686;
    return x6699; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x6682, const struct SEntry17_IIISSSSSSSSSSIIIS& x6683) { 
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
  
  struct SEntry17_IIISSSSSSSSSSIIIS x9372;
  struct SEntry10_IIIIIITIDS x9423;
  struct SEntry3_III x9640;
  struct SEntry11_IISSSSSSDDI x9349;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9119;
  struct SEntry8_IIIIITDS x9199;
  struct SEntry8_IIIITIIB x9356;
  struct SEntry5_IISDS x9316;
  struct SEntry17_IIISSSSSSSSSSIIIS x9843;
  struct SEntry8_IIIITIIB x9651;
  struct SEntry11_IISSSSSSDDI x9187;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9921;
  struct SEntry3_III x9359;
  struct SEntry8_IIIITIIB x9900;
  struct SEntry10_IIIIIITIDS x9660;
  struct SEntry10_IIIIIITIDS x9910;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9127;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9343;
  struct SEntry9_ISSSSSSDD x9182;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9664;
  struct SEntry11_IISSSSSSDDI x9804;
  struct SEntry17_IIISSSSSSSSSSIIIS x9441;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9924;
  struct SEntry10_IIIIIITIDS x9817;
  struct SEntry9_ISSSSSSDD x9346;
  
  int partitionID;
  uint failedNO;
  uint xactCounts[5];
         
  
  FORCE_INLINE void PaymentTx(int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
    int x28 = 0;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9113 = NULL;
    int x45 = x22%(numThreads);
    if((x21>(0))) {
      x9119._2 = x23;
      x9119._3 = x22;
      x9119._6 = x25;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13702 = customerTblIdx1.get(x9119);
      x9113 = x13702;
    };
    if((x45==(partitionID))) {
      if((x21==(0))) {
        x9127._1 = x24;
        x9127._2 = x23;
        x9127._3 = x22;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13712 = customerTblIdx0.get(x9127);
        x9113 = x13712;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9130 = x9113;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9132 = x9113;
      x28 = (x9132->_1);
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9135 = x9113;
      char* x22558 = strstr((x9135->_14).data_, "BC");
      if((x22558!=(NULL))) {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9139 = x9113;
        PString x3181 = PString(500);
        x3181.append((x9139->_1));
        x3181.append(' ');
        x3181.append(x23);
        x3181.append(' ');
        x3181.append(x22);
        x3181.append(' ');
        x3181.append(x20);
        x3181.append(' ');
        x3181.append(x19);
        x3181.append(' ');
        x3181.append('$');
        x3181.append(x26);
        x3181.append(' ');
        x3181.appendDate(x17);
        x3181.append(' ');
        x3181.append('|');
        x3181.append(' ');
        x3181.append((x9130->_21).data_, 500);
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9160 = x9113;
        x9160->_17 += x26;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9162 = x9113;
        x9162->_21 = x3181;
      } else {
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9164 = x9113;
        x9164->_17 += x26;
      };
    };
    if(((x19%(numThreads))==(partitionID))) {
      int x80 = xactCounts[1];
      xactCounts[1] = (x80+(1));
      if((x45!=(partitionID))) {
        if((x21>(0))) {
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9177 = x9113;
          x28 = (x9177->_1);
        } else {
          x28 = x24;
        };
      };
      x9182._1 = x19;
      struct SEntry9_ISSSSSSDD* x13768 = warehouseTblIdx0.get(x9182);
      x13768->_9 += x26;
      x9187._1 = x20;
      x9187._2 = x19;
      struct SEntry11_IISSSSSSDDI* x13774 = districtTblIdx0.get(x9187);
      x13774->_10 += x26;
      PString x3234 = PString(24);
      x3234.append((x13768->_2).data_, 10);
      x3234.append("    ", 4);
      x3234.append((x13774->_3).data_, 10);
      int x110 = x28;
      x9199._1 = x110;
      x9199._2 = x23;
      x9199._3 = x22;
      x9199._4 = x20;
      x9199._5 = x19;
      x9199._6 = x17;
      x9199._7 = x26;
      x9199._8 = x3234;
      historyTbl.insert_nocheck(x9199);
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
      int ite21465 = 0;
      if(x150) {
        
        int x151 = x132;
        int x21466 = (x151<(x121));
        ite21465 = x21466;
      } else {
        ite21465 = 0;
      };
      int x21290 = ite21465;
      if (!(x21290)) break; 
      
      int x155 = x132;
      int supwid = x124[x155];
      if((supwid!=(x118))) {
        x148 = 0;
      };
      int x160 = x145;
      int ite21479 = 0;
      if(x160) {
        ite21479 = 1;
      } else {
        
        int x21481 = ((supwid%(numThreads))==(partitionID));
        ite21479 = x21481;
      };
      int x21298 = ite21479;
      x145 = x21298;
      int x166 = x132;
      int x167 = x123[x166];
      x9316._1 = x167;
      struct SEntry5_IISDS* x13923 = itemTblIdx0.get(x9316);
      if((x13923==(NULL))) {
        x140 = 0;
      } else {
        int x173 = x132;
        x127[x173] = (x13923->_3);
        int x176 = x132;
        x126[x176] = (x13923->_4);
        int x179 = x132;
        idata[x179] = (x13923->_5);
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
          x9343._1 = x120;
          x9343._2 = x119;
          x9343._3 = x118;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13952 = customerTblIdx0.get(x9343);
          x9346._1 = x118;
          struct SEntry9_ISSSSSSDD* x13955 = warehouseTblIdx0.get(x9346);
          x9349._1 = x119;
          x9349._2 = x118;
          struct SEntry11_IISSSSSSDDI* x13959 = districtTblIdx0.get(x9349);
          int x9351 = x13959->_11;
          x13959->_11 += 1;
          int x210 = x148;
          x9356._1 = x9351;
          x9356._2 = x119;
          x9356._3 = x118;
          x9356._4 = x120;
          x9356._5 = x116;
          x9356._6 = -1;
          x9356._7 = x121;
          x9356._8 = x210;
          orderTbl.insert_nocheck(x9356);
          x9359._1 = x9351;
          x9359._2 = x119;
          x9359._3 = x118;
          newOrderTbl.insert_nocheck(x9359);
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
            x9372._1 = ol_i_id;
            x9372._2 = ol_supply_w_id;
            struct SEntry17_IIISSSSSSSSSSIIIS* x13992 = stockTblIdx0.get(x9372);
            const PString& x9375 = *(&x13992->_4 + (x119-1));
            int x9376 = x13992->_3;
            int x240 = x132;
            x128[x240] = x9376;
            if(((ol_supply_w_id%(numThreads))==(partitionID))) {
              x13992->_3 = (x9376-(ol_quantity));
              if((x9376<=(ol_quantity))) {
                x13992->_3 += 91;
              };
              int x250 = 0;
              if((ol_supply_w_id!=(x118))) {
                x250 = 1;
              };
            };
            int x257 = x132;
            PString& x258 = idata[x257];
            char* x22834 = strstr(x258.data_, "original");
            int ite21573 = 0;
            if((x22834!=(NULL))) {
              
              char* x22840 = strstr((x13992->_17).data_, "original");
              int x21574 = (x22840!=(NULL));
              ite21573 = x21574;
            } else {
              ite21573 = 0;
            };
            int x21386 = ite21573;
            if(x21386) {
              int x263 = x132;
              x129[x263].data_[0] = 'B';
            } else {
              int x265 = x132;
              x129[x265].data_[0] = 'G';
            };
            int x275 = x132;
            double x276 = x126[x275];
            double ol_amount = ((ol_quantity*(x276))*(((1.0+((x13955->_8)))+((x13959->_9)))))*((1.0-((x13952->_16))));
            int x284 = x132;
            x130[x284] = ol_amount;
            double x286 = x218;
            x218 = (x286+(ol_amount));
            int x289 = x132;
            x9423._1 = x9351;
            x9423._2 = x119;
            x9423._3 = x118;
            x9423._4 = (x289+(1));
            x9423._5 = ol_i_id;
            x9423._6 = ol_supply_w_id;
            x9423._8 = ol_quantity;
            x9423._9 = ol_amount;
            x9423._10 = x9375;
            orderLineTbl.insert_nocheck(x9423);
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
              x9441._1 = ol_i_id;
              x9441._2 = ol_supply_w_id;
              struct SEntry17_IIISSSSSSSSSSIIIS* x14070 = stockTblIdx0.get(x9441);
              int x9443 = x14070->_3;
              x14070->_3 = (x9443-(ol_quantity));
              if((x9443<=(ol_quantity))) {
                x14070->_3 += 91;
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
        x9640._2 = x359;
        x9640._3 = x342;
        struct SEntry3_III* x14292 = newOrderTblIdx1.get(x9640);
        if((x14292!=(NULL))) {
          int x9644 = x14292->_1;
          int x368 = x350;
          orderIDs[(x368-(1))] = x9644;
          newOrderTbl.del(x14292);
          int x373 = x350;
          x9651._1 = x9644;
          x9651._2 = x373;
          x9651._3 = x342;
          struct SEntry8_IIIITIIB* x14305 = orderTblIdx0.get(x9651);
          x14305->_6 = x343;
          double x382 = 0.0;
          int x384 = x350;
          x9660._1 = x9644;
          x9660._2 = x384;
          x9660._3 = x342;
          orderLineTblIdx1.slice(x9660, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
            orderLineEntry->_7 = x341;
            double x389 = x382;
            x382 = (x389+((orderLineEntry->_9)));
          
          });
          int x397 = x350;
          x9664._1 = (x14305->_4);
          x9664._2 = x397;
          x9664._3 = x342;
          struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14331 = customerTblIdx0.get(x9664);
          double x401 = x382;
          x14331->_17 += x401;
          x14331->_20 += 1;
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
      x9804._1 = x425;
      x9804._2 = x424;
      struct SEntry11_IISSSSSSDDI* x14424 = districtTblIdx0.get(x9804);
      int x9806 = x14424->_11;
      int x437 = (x9806-(20));
      unordered_set<int> unique_ol_i_id({}); //setApply1
      while(1) {
        
        int x442 = x437;
        if (!((x442<(x9806)))) break; 
        
        int x444 = x437;
        x9817._1 = x444;
        x9817._2 = x425;
        x9817._3 = x424;
        orderLineTblIdx1.slice(x9817, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
          int x9841 = orderLineEntry->_5;
          x9843._1 = x9841;
          x9843._2 = x424;
          struct SEntry17_IIISSSSSSSSSSIIIS* x14439 = stockTblIdx0.get(x9843);
          if(((x14439->_3)<(x426))) {
            unique_ol_i_id.insert(x9841);
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
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite21939 = 0;
      if((x477>(0))) {
        x9921._2 = x476;
        x9921._3 = x475;
        x9921._6 = x479;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x21943 = customerTblIdx1.get(x9921);
        ite21939 = x21943;
      } else {
        x9924._1 = x478;
        x9924._2 = x476;
        x9924._3 = x475;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x21948 = customerTblIdx0.get(x9924);
        ite21939 = x21948;
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9897 = ite21939;
      x9900._2 = x476;
      x9900._3 = x475;
      x9900._4 = (x9897->_3);
      struct SEntry8_IIIITIIB* x14514 = orderTblIdx1.get(x9900);
      int ite21958 = 0;
      if((x14514==(NULL))) {
        int x21959 = failedOS;
        failedOS = (1+(x21959));
        ite21958 = 0;
      } else {
        x9910._1 = (x14514->_1);
        x9910._2 = x476;
        x9910._3 = x475;
        orderLineTblIdx1.slice(x9910, [&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
          int x519 = 1;
        
        });
        ite21958 = 1;
      };
      int x523 = ite21958;
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
    fout << "\nCPP-ABCDEFGINORVXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << globalXactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT_P(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx1, info);
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
  
      warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
  
  
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
