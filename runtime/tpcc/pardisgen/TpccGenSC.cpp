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
const int numThreads = 1;
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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x8133)  { 
    int x8134 = 0;
    int x8135 = x8134;
    x8134 = (x8135^(((((HASH((x8133._3)))+(-1640531527))+((x8135<<(6))))+((x8135>>(2))))));
    int x8145 = x8134;
    x8134 = (x8145^(((((HASH((x8133._2)))+(-1640531527))+((x8145<<(6))))+((x8145>>(2))))));
    int x8155 = x8134;
    x8134 = (x8155^(((((HASH((x8133._1)))+(-1640531527))+((x8155<<(6))))+((x8155>>(2))))));
    int x8165 = x8134;
    x8134 = (x8165^(((((HASH((x8133._4)))+(-1640531527))+((x8165<<(6))))+((x8165>>(2))))));
    int x8175 = x8134;
    return x8175; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x8177, const struct SEntry10_IIIIIITIDS& x8178) { 
    int x8179 = 0;
    if(((x8177._3)==((x8178._3)))) {
      if(((x8177._2)==((x8178._2)))) {
        if(((x8177._1)==((x8178._1)))) {
          if(((x8177._4)==((x8178._4)))) {
            x8179 = 0;
          } else {
            x8179 = 1;
          };
        } else {
          x8179 = 1;
        };
      } else {
        x8179 = 1;
      };
    } else {
      x8179 = 1;
    };
    int x8201 = x8179;
    return x8201; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x8046)  { 
    int x8047 = 0;
    int x8048 = x8047;
    x8047 = (x8048^(((((HASH((x8046._2)))+(-1640531527))+((x8048<<(6))))+((x8048>>(2))))));
    int x8058 = x8047;
    x8047 = (x8058^(((((HASH((x8046._3)))+(-1640531527))+((x8058<<(6))))+((x8058>>(2))))));
    int x8068 = x8047;
    x8047 = (x8068^(((((HASH((x8046._4)))+(-1640531527))+((x8068<<(6))))+((x8068>>(2))))));
    int x8078 = x8047;
    return x8078; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x8080, const struct SEntry8_IIIITIIB& x8081) { 
    int x8082 = 0;
    if(((x8080._2)==((x8081._2)))) {
      if(((x8080._3)==((x8081._3)))) {
        if(((x8080._4)==((x8081._4)))) {
          x8082 = 0;
        } else {
          x8082 = 1;
        };
      } else {
        x8082 = 1;
      };
    } else {
      x8082 = 1;
    };
    int x8099 = x8082;
    return x8099; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x7990)  { 
    int x7991 = 0;
    int x7992 = x7991;
    x7991 = (x7992^(((((HASH((x7990._3)))+(-1640531527))+((x7992<<(6))))+((x7992>>(2))))));
    int x8002 = x7991;
    x7991 = (x8002^(((((HASH((x7990._2)))+(-1640531527))+((x8002<<(6))))+((x8002>>(2))))));
    int x8012 = x7991;
    x7991 = (x8012^(((((HASH((x7990._1)))+(-1640531527))+((x8012<<(6))))+((x8012>>(2))))));
    int x8022 = x7991;
    return x8022; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x8024, const struct SEntry8_IIIITIIB& x8025) { 
    int x8026 = 0;
    if(((x8024._3)==((x8025._3)))) {
      if(((x8024._2)==((x8025._2)))) {
        if(((x8024._1)==((x8025._1)))) {
          x8026 = 0;
        } else {
          x8026 = 1;
        };
      } else {
        x8026 = 1;
      };
    } else {
      x8026 = 1;
    };
    int x8043 = x8026;
    return x8043; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x7816)  { 
    int x7817 = 0;
    int x7818 = x7817;
    x7817 = (x7818^(((((HASH((x7816._1)))+(-1640531527))+((x7818<<(6))))+((x7818>>(2))))));
    int x7828 = x7817;
    x7817 = (x7828^(((((HASH((x7816._2)))+(-1640531527))+((x7828<<(6))))+((x7828>>(2))))));
    int x7838 = x7817;
    x7817 = (x7838^(((((HASH((x7816._3)))+(-1640531527))+((x7838<<(6))))+((x7838>>(2))))));
    int x7848 = x7817;
    x7817 = (x7848^(((((HASH((x7816._4)))+(-1640531527))+((x7848<<(6))))+((x7848>>(2))))));
    int x7858 = x7817;
    x7817 = (x7858^(((((HASH((x7816._5)))+(-1640531527))+((x7858<<(6))))+((x7858>>(2))))));
    int x7868 = x7817;
    x7817 = (x7868^(((((HASH((x7816._6)))+(-1640531527))+((x7868<<(6))))+((x7868>>(2))))));
    int x7878 = x7817;
    x7817 = (x7878^(((((HASH((x7816._7)))+(-1640531527))+((x7878<<(6))))+((x7878>>(2))))));
    int x7888 = x7817;
    x7817 = (x7888^(((((HASH((x7816._8)))+(-1640531527))+((x7888<<(6))))+((x7888>>(2))))));
    int x7898 = x7817;
    return x7898; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x7900, const struct SEntry8_IIIIITDS& x7901) { 
    int x7902 = 0;
    if(((x7900._1)==((x7901._1)))) {
      if(((x7900._2)==((x7901._2)))) {
        if(((x7900._3)==((x7901._3)))) {
          if(((x7900._4)==((x7901._4)))) {
            if(((x7900._5)==((x7901._5)))) {
              if(((x7900._6)==((x7901._6)))) {
                if(((x7900._7)==((x7901._7)))) {
                  if(((x7900._8)==((x7901._8)))) {
                    x7902 = 0;
                  } else {
                    x7902 = 1;
                  };
                } else {
                  x7902 = 1;
                };
              } else {
                x7902 = 1;
              };
            } else {
              x7902 = 1;
            };
          } else {
            x7902 = 1;
          };
        } else {
          x7902 = 1;
        };
      } else {
        x7902 = 1;
      };
    } else {
      x7902 = 1;
    };
    int x7944 = x7902;
    return x7944; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x8204)  { 
    int x8205 = 0;
    int x8206 = x8205;
    x8205 = (x8206^(((((HASH((x8204._1)))+(-1640531527))+((x8206<<(6))))+((x8206>>(2))))));
    int x8216 = x8205;
    x8205 = (x8216^(((((HASH((x8204._2)))+(-1640531527))+((x8216<<(6))))+((x8216>>(2))))));
    int x8226 = x8205;
    x8205 = (x8226^(((((HASH((x8204._3)))+(-1640531527))+((x8226<<(6))))+((x8226>>(2))))));
    int x8236 = x8205;
    return x8236; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x8238, const struct SEntry10_IIIIIITIDS& x8239) { 
    int x8240 = 0;
    if(((x8238._1)==((x8239._1)))) {
      if(((x8238._2)==((x8239._2)))) {
        if(((x8238._3)==((x8239._3)))) {
          x8240 = 0;
        } else {
          x8240 = 1;
        };
      } else {
        x8240 = 1;
      };
    } else {
      x8240 = 1;
    };
    int x8257 = x8240;
    return x8257; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x7769)  { 
    int x7770 = 0;
    int x7771 = x7770;
    x7770 = (x7771^(((((HASH((x7769._2)))+(-1640531527))+((x7771<<(6))))+((x7771>>(2))))));
    int x7781 = x7770;
    x7770 = (x7781^(((((HASH((x7769._3)))+(-1640531527))+((x7781<<(6))))+((x7781>>(2))))));
    int x7791 = x7770;
    return x7791; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x7793, const struct SEntry3_III& x7794) { 
    int x7795 = 0;
    if(((x7793._2)==((x7794._2)))) {
      if(((x7793._3)==((x7794._3)))) {
        x7795 = 0;
      } else {
        x7795 = 1;
      };
    } else {
      x7795 = 1;
    };
    int x7807 = x7795;
    return x7807; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x7713)  { 
    int x7714 = 0;
    int x7715 = x7714;
    x7714 = (x7715^(((((HASH((x7713._3)))+(-1640531527))+((x7715<<(6))))+((x7715>>(2))))));
    int x7725 = x7714;
    x7714 = (x7725^(((((HASH((x7713._2)))+(-1640531527))+((x7725<<(6))))+((x7725>>(2))))));
    int x7735 = x7714;
    x7714 = (x7735^(((((HASH((x7713._1)))+(-1640531527))+((x7735<<(6))))+((x7735>>(2))))));
    int x7745 = x7714;
    return x7745; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x7747, const struct SEntry3_III& x7748) { 
    int x7749 = 0;
    if(((x7747._3)==((x7748._3)))) {
      if(((x7747._2)==((x7748._2)))) {
        if(((x7747._1)==((x7748._1)))) {
          x7749 = 0;
        } else {
          x7749 = 1;
        };
      } else {
        x7749 = 1;
      };
    } else {
      x7749 = 1;
    };
    int x7766 = x7749;
    return x7766; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8292)  { 
    int x8293 = 0;
    int x8294 = x8293;
    x8293 = (x8294^(((((HASH((x8292._2)))+(-1640531527))+((x8294<<(6))))+((x8294>>(2))))));
    int x8304 = x8293;
    x8293 = (x8304^(((((HASH((x8292._3)))+(-1640531527))+((x8304<<(6))))+((x8304>>(2))))));
    int x8314 = x8293;
    x8293 = (x8314^(((((HASH((x8292._6)))+(-1640531527))+((x8314<<(6))))+((x8314>>(2))))));
    int x8324 = x8293;
    return x8324; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8326, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8327) { 
    int x8328 = 0;
    if(((x8326._2)==((x8327._2)))) {
      if(((x8326._3)==((x8327._3)))) {
        if(((x8326._6)==((x8327._6)))) {
          x8328 = 0;
        } else {
          x8328 = 1;
        };
      } else {
        x8328 = 1;
      };
    } else {
      x8328 = 1;
    };
    int x8345 = x8328;
    return x8345; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t6 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x7955)  { 
    int x7956 = 0;
    int x7959 = x7956;
    x7956 = ((x7959*(5))+(((x7955._1)-(1))));
    int x7963 = x7956;
    return x7963; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x7952, const struct SEntry9_ISSSSSSDD& x7953) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x8111)  { 
    int x8112 = 0;
    int x8115 = x8112;
    x8112 = ((x8115*(5))+(((x8111._2)-(1))));
    int x8121 = x8112;
    x8112 = ((x8121*(10))+(((x8111._1)-(1))));
    int x8125 = x8112;
    return x8125; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x8108, const struct SEntry11_IISSSSSSDDI& x8109) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100002 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x7974)  { 
    int x7975 = 0;
    int x7978 = x7975;
    x7975 = ((x7978*(100001))+(((x7974._1)-(1))));
    int x7982 = x7975;
    return x7982; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x7971, const struct SEntry5_IISDS& x7972) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8269)  { 
    int x8270 = 0;
    int x8273 = x8270;
    x8270 = ((x8273*(5))+(((x8269._3)-(1))));
    int x8279 = x8270;
    x8270 = ((x8279*(10))+(((x8269._2)-(1))));
    int x8285 = x8270;
    x8270 = ((x8285*(3000))+(((x8269._1)-(1))));
    int x8289 = x8270;
    return x8289; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8266, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8267) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x8357)  { 
    int x8358 = 0;
    int x8361 = x8358;
    x8358 = ((x8361*(5))+(((x8357._2)-(1))));
    int x8367 = x8358;
    x8358 = ((x8367*(100000))+(((x8357._1)-(1))));
    int x8371 = x8358;
    return x8371; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x8354, const struct SEntry17_IIISSSSSSSSSSIIIS& x8355) { 
    return 0; 
  }
};
typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx321, 1> newOrderTblIdx0Type;
typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx23, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;

typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,historyTblIdx0Type> historyTblStoreType;

typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t6, 5> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,warehouseTblIdx0Type> warehouseTblStoreType;

typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100002, 100001> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,itemTblIdx0Type> itemTblStoreType;

typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx321, 1> orderTblIdx0Type;
typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, 0> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;

typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11, 50> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,districtTblIdx0Type> districtTblStoreType;

typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx3214, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;

typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001, 150000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
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
  
  struct SEntry8_IIIITIIB x9068;
  struct SEntry17_IIISSSSSSSSSSIIIS x10408;
  struct SEntry10_IIIIIITIDS x10250;
  struct SEntry11_IISSSSSSDDI x9409;
  struct SEntry11_IISSSSSSDDI x9640;
  struct SEntry3_III x10188;
  struct SEntry10_IIIIIITIDS x9225;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x10172;
  struct SEntry8_IIIITIIB x9290;
  struct SEntry9_ISSSSSSDD x10175;
  struct SEntry17_IIISSSSSSSSSSIIIS x10202;
  struct SEntry5_IISDS x9916;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9472;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9792;
  struct SEntry10_IIIIIITIDS x9301;
  struct SEntry9_ISSSSSSDD x9635;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9312;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9308;
  struct SEntry8_IIIITIIB x9949;
  struct SEntry11_IISSSSSSDDI x9213;
  struct SEntry8_IIIIITDS x9451;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9788;
  struct SEntry17_IIISSSSSSSSSSIIIS x9966;
  struct SEntry5_IISDS x10387;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9936;
  struct SEntry9_ISSSSSSDD x9939;
  struct SEntry11_IISSSSSSDDI x9942;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9468;
  struct SEntry10_IIIIIITIDS x10014;
  struct SEntry17_IIISSSSSSSSSSIIIS x9244;
  struct SEntry8_IIIITIIB x10185;
  struct SEntry3_III x9056;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9671;
  struct SEntry3_III x9952;
  struct SEntry5_IISDS x10152;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9675;
  struct SEntry8_IIIIITDS x9654;
  struct SEntry9_ISSSSSSDD x9404;
  struct SEntry11_IISSSSSSDDI x10178;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x9081;
  struct SEntry10_IIIIIITIDS x9077;
  
  uint partitionID;
  uint failedNO;
  uint xactCounts[5];
         
  FORCE_INLINE void DeliveryTx(int x13, date x14, int x15, int x16) {
    int orderIDs[10];
    int x21 = 1;
    while(1) {
      
      int x23 = x21;
      if (!((x23<=(10)))) break; 
      
      struct SEntry3_III* x9053result = nullptr;
      MinAggregator<struct SEntry3_III, int> x9053([&](struct SEntry3_III* e) -> int {
        return (e->_1); 
      }, &x9053result);
      int x30 = x21;
      x9056._2 = x30;
      x9056._3 = x15;
      //sliceRes 
      typedef typename newOrderTblIdx1Type::IFN IDXFN18006;
      HASH_RES_t h18006 = IDXFN18006::hash(x9056);
      auto* x18006 = &(newOrderTblIdx1.buckets_[h18006 % newOrderTblIdx1.size_]);
      if(x18006 -> head.obj) {
         do {
           if(h18006 == x18006->hash && !IDXFN18006::cmp(x9056, *x18006->head.obj))
             break;
         } while((x18006 = x18006->nxt));
      } else { 
         x18006 = nullptr;
      }
      if((x18006 == nullptr)) {
      } else {
        newOrderTblIdx1.sliceResMapNoUpd(x9056, x9053, x18006);
      };
      struct SEntry3_III* x9058 = x9053.result();
      if((x9058!=(NULL))) {
        int x9061 = x9058->_1;
        int x39 = x21;
        orderIDs[(x39-(1))] = x9061;
        newOrderTbl.del(x9058);
        int x44 = x21;
        x9068._1 = x9061;
        x9068._2 = x44;
        x9068._3 = x15;
        struct SEntry8_IIIITIIB* x14533 = orderTblIdx0.get(x9068);
        x14533->_6 = x16;
        double x53 = 0.0;
        int x55 = x21;
        x9077._1 = x9061;
        x9077._2 = x55;
        x9077._3 = x15;
        //sliceRes 
        typedef typename orderLineTblIdx1Type::IFN IDXFN18039;
        HASH_RES_t h18039 = IDXFN18039::hash(x9077);
        auto* x18039 = &(orderLineTblIdx1.buckets_[h18039 % orderLineTblIdx1.size_]);
        if(x18039 -> head.obj) {
           do {
             if(h18039 == x18039->hash && !IDXFN18039::cmp(x9077, *x18039->head.obj))
               break;
           } while((x18039 = x18039->nxt));
        } else { 
           x18039 = nullptr;
        }
        if((x18039 == nullptr)) {
        } else {
          //sliceResMapNoUpd 
          auto* nx18039 = &x18039->head;
          do {
            auto orderLineEntry = nx18039->obj;
            orderLineEntry->_7 = x14;
            double x60 = x53;
            x53 = (x60+((orderLineEntry->_9)));
          } while((nx18039 = nx18039->nxt));
        };
        int x68 = x21;
        x9081._1 = (x14533->_4);
        x9081._2 = x68;
        x9081._3 = x15;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14555 = customerTblIdx0.get(x9081);
        double x72 = x53;
        x14555->_17 += x72;
        x14555->_20 += 1;
      } else {
        int x76 = failedDel;
        failedDel = (1+(x76));
        int x79 = x21;
        orderIDs[(x79-(1))] = 0;
      };
      int x83 = x21;
      x21 = (x83+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void StockLevelTx(int x87, date x88, int x89, int x90, int x91, int x92) {
    x9213._1 = x91;
    x9213._2 = x90;
    struct SEntry11_IISSSSSSDDI* x14633 = districtTblIdx0.get(x9213);
    int x9215 = x14633->_11;
    int x101 = (x9215-(20));
    unordered_set<int> unique_ol_i_id; //setApply2
    while(1) {
      
      int x105 = x101;
      if (!((x105<(x9215)))) break; 
      
      int x107 = x101;
      x9225._1 = x107;
      x9225._2 = x91;
      x9225._3 = x90;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN18088;
      HASH_RES_t h18088 = IDXFN18088::hash(x9225);
      auto* x18088 = &(orderLineTblIdx1.buckets_[h18088 % orderLineTblIdx1.size_]);
      if(x18088 -> head.obj) {
         do {
           if(h18088 == x18088->hash && !IDXFN18088::cmp(x9225, *x18088->head.obj))
             break;
         } while((x18088 = x18088->nxt));
      } else { 
         x18088 = nullptr;
      }
      if((x18088 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx18088 = &x18088->head;
        do {
          auto orderLineEntry = nx18088->obj;
          int x9242 = orderLineEntry->_5;
          x9244._1 = x9242;
          x9244._2 = x90;
          struct SEntry17_IIISSSSSSSSSSIIIS* x14647 = stockTblIdx0.get(x9244);
          if(((x14647->_3)<(x92))) {
            unique_ol_i_id.insert(x9242);
          };
        } while((nx18088 = nx18088->nxt));
      };
      int x124 = x101;
      x101 = (x124+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void OrderStatusTx(int x130, date x131, int x132, int x133, int x134, int x135, int x136, PString x137) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite30464 = 0;
    if((x135>(0))) {
      std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x30468results;
      MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x30468([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
        return (e->_4); 
      }, x30468results);
      x9308._2 = x134;
      x9308._3 = x133;
      x9308._6 = x137;
      //sliceRes 
      typedef typename customerTblIdx1Type::IFN IDXFN30472;
      HASH_RES_t h30472 = IDXFN30472::hash(x9308);
      auto* x30472 = &(customerTblIdx1.buckets_[h30472 % customerTblIdx1.size_]);
      if(x30472 -> head.obj) {
         do {
           if(h30472 == x30472->hash && !IDXFN30472::cmp(x9308, *x30472->head.obj))
             break;
         } while((x30472 = x30472->nxt));
      } else { 
         x30472 = nullptr;
      }
      if((x30472 == nullptr)) {
      } else {
        customerTblIdx1.sliceResMapNoUpd(x9308, x30468, x30472);
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30476 = x30468.result();
      ite30464 = x30476;
    } else {
      x9312._1 = x136;
      x9312._2 = x134;
      x9312._3 = x133;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30481 = customerTblIdx0.get(x9312);
      ite30464 = x30481;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9285 = ite30464;
    struct SEntry8_IIIITIIB* x9288result = nullptr;
    MaxAggregator<struct SEntry8_IIIITIIB, int> x9288([&](struct SEntry8_IIIITIIB* e) -> int {
      return (e->_1); 
    }, &x9288result);
    x9290._2 = x134;
    x9290._3 = x133;
    x9290._4 = (x9285->_3);
    //sliceRes 
    typedef typename orderTblIdx1Type::IFN IDXFN18124;
    HASH_RES_t h18124 = IDXFN18124::hash(x9290);
    auto* x18124 = &(orderTblIdx1.buckets_[h18124 % orderTblIdx1.size_]);
    if(x18124 -> head.obj) {
       do {
         if(h18124 == x18124->hash && !IDXFN18124::cmp(x9290, *x18124->head.obj))
           break;
       } while((x18124 = x18124->nxt));
    } else { 
       x18124 = nullptr;
    }
    if((x18124 == nullptr)) {
    } else {
      orderTblIdx1.sliceResMapNoUpd(x9290, x9288, x18124);
    };
    struct SEntry8_IIIITIIB* x9292 = x9288.result();
    int ite30499 = 0;
    if((x9292==(NULL))) {
      int x30500 = failedOS;
      failedOS = (1+(x30500));
      ite30499 = 0;
    } else {
      x9301._1 = (x9292->_1);
      x9301._2 = x134;
      x9301._3 = x133;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN30508;
      HASH_RES_t h30508 = IDXFN30508::hash(x9301);
      auto* x30508 = &(orderLineTblIdx1.buckets_[h30508 % orderLineTblIdx1.size_]);
      if(x30508 -> head.obj) {
         do {
           if(h30508 == x30508->hash && !IDXFN30508::cmp(x9301, *x30508->head.obj))
             break;
         } while((x30508 = x30508->nxt));
      } else { 
         x30508 = nullptr;
      }
      if((x30508 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx30508 = &x30508->head;
        do {
          auto orderLineEntry = nx30508->obj;
          int x175 = 1;
        } while((nx30508 = nx30508->nxt));
      };
      ite30499 = 1;
    };
    int x179 = ite30499;
    clearTempMem();
  }
  FORCE_INLINE void PaymentTx(int x180, date x181, int x182, int x183, int x184, int x185, int x186, int x187, int x188, PString x189, double x190) {
    x9404._1 = x183;
    struct SEntry9_ISSSSSSDD* x14778 = warehouseTblIdx0.get(x9404);
    x14778->_9 += x190;
    x9409._1 = x184;
    x9409._2 = x183;
    struct SEntry11_IISSSSSSDDI* x14783 = districtTblIdx0.get(x9409);
    x14783->_10 += x190;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite30581 = 0;
    if((x185>(0))) {
      std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x30585results;
      MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x30585([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
        return (e->_4); 
      }, x30585results);
      x9468._2 = x187;
      x9468._3 = x186;
      x9468._6 = x189;
      //sliceRes 
      typedef typename customerTblIdx1Type::IFN IDXFN30589;
      HASH_RES_t h30589 = IDXFN30589::hash(x9468);
      auto* x30589 = &(customerTblIdx1.buckets_[h30589 % customerTblIdx1.size_]);
      if(x30589 -> head.obj) {
         do {
           if(h30589 == x30589->hash && !IDXFN30589::cmp(x9468, *x30589->head.obj))
             break;
         } while((x30589 = x30589->nxt));
      } else { 
         x30589 = nullptr;
      }
      if((x30589 == nullptr)) {
      } else {
        customerTblIdx1.sliceResMapNoUpd(x9468, x30585, x30589);
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30593 = x30585.result();
      ite30581 = x30593;
    } else {
      x9472._1 = x188;
      x9472._2 = x187;
      x9472._3 = x186;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30598 = customerTblIdx0.get(x9472);
      ite30581 = x30598;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9414 = ite30581;
    char* x32780 = strstr((x9414->_14).data_, "BC");
    if((x32780!=(NULL))) {
      PString x4181 = PString(500);
      x4181.append((x9414->_1));
      x4181.append(' ');
      x4181.append(x187);
      x4181.append(' ');
      x4181.append(x186);
      x4181.append(' ');
      x4181.append(x184);
      x4181.append(' ');
      x4181.append(x183);
      x4181.append(' ');
      x4181.append('$');
      x4181.append(x190);
      x4181.append(' ');
      x4181.appendDate(x181);
      x4181.append(' ');
      x4181.append('|');
      x4181.append(' ');
      x4181.append((x9414->_21).data_, 500);
      x9414->_17 += x190;
      x9414->_21 = x4181;
    } else {
      x9414->_17 += x190;
    };
    PString x4207 = PString(24);
    x4207.append((x14778->_2).data_, 10);
    x4207.append("    ", 4);
    x4207.append((x14783->_3).data_, 10);
    x9451._1 = (x9414->_1);
    x9451._2 = x187;
    x9451._3 = x186;
    x9451._4 = x184;
    x9451._5 = x183;
    x9451._6 = x181;
    x9451._7 = x190;
    x9451._8 = x4207;
    historyTbl.insert_nocheck(x9451);
    clearTempMem();
  }
  FORCE_INLINE void PaymentTxLocal(int x242, date x243, int x244, int x245, int x246, int x247, int x248, int x249, int x250, PString x251, double x252) {
    x9635._1 = x245;
    struct SEntry9_ISSSSSSDD* x14918 = warehouseTblIdx0.get(x9635);
    x14918->_9 += x252;
    x9640._1 = x246;
    x9640._2 = x245;
    struct SEntry11_IISSSSSSDDI* x14923 = districtTblIdx0.get(x9640);
    x14923->_10 += x252;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite30725 = 0;
    if((x247>(0))) {
      std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x30729results;
      MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x30729([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
        return (e->_4); 
      }, x30729results);
      x9671._2 = x249;
      x9671._3 = x248;
      x9671._6 = x251;
      //sliceRes 
      typedef typename customerTblIdx1Type::IFN IDXFN30733;
      HASH_RES_t h30733 = IDXFN30733::hash(x9671);
      auto* x30733 = &(customerTblIdx1.buckets_[h30733 % customerTblIdx1.size_]);
      if(x30733 -> head.obj) {
         do {
           if(h30733 == x30733->hash && !IDXFN30733::cmp(x9671, *x30733->head.obj))
             break;
         } while((x30733 = x30733->nxt));
      } else { 
         x30733 = nullptr;
      }
      if((x30733 == nullptr)) {
      } else {
        customerTblIdx1.sliceResMapNoUpd(x9671, x30729, x30733);
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30737 = x30729.result();
      ite30725 = x30737;
    } else {
      x9675._1 = x250;
      x9675._2 = x249;
      x9675._3 = x248;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30742 = customerTblIdx0.get(x9675);
      ite30725 = x30742;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9645 = ite30725;
    PString x4304 = PString(24);
    x4304.append((x14918->_2).data_, 10);
    x4304.append("    ", 4);
    x4304.append((x14923->_3).data_, 10);
    x9654._1 = (x9645->_1);
    x9654._2 = x249;
    x9654._3 = x248;
    x9654._4 = x246;
    x9654._5 = x245;
    x9654._6 = x243;
    x9654._7 = x252;
    x9654._8 = x4304;
    historyTbl.insert_nocheck(x9654);
    clearTempMem();
  }
  FORCE_INLINE void PaymentTxRemote(int x291, date x292, int x293, int x294, int x295, int x296, int x297, int x298, int x299, PString x300, double x301) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite30808 = 0;
    if((x296>(0))) {
      std::vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x30812results;
      MedianAggregator<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, PString> x30812([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> PString {
        return (e->_4); 
      }, x30812results);
      x9788._2 = x298;
      x9788._3 = x297;
      x9788._6 = x300;
      //sliceRes 
      typedef typename customerTblIdx1Type::IFN IDXFN30816;
      HASH_RES_t h30816 = IDXFN30816::hash(x9788);
      auto* x30816 = &(customerTblIdx1.buckets_[h30816 % customerTblIdx1.size_]);
      if(x30816 -> head.obj) {
         do {
           if(h30816 == x30816->hash && !IDXFN30816::cmp(x9788, *x30816->head.obj))
             break;
         } while((x30816 = x30816->nxt));
      } else { 
         x30816 = nullptr;
      }
      if((x30816 == nullptr)) {
      } else {
        customerTblIdx1.sliceResMapNoUpd(x9788, x30812, x30816);
      };
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30820 = x30812.result();
      ite30808 = x30820;
    } else {
      x9792._1 = x299;
      x9792._2 = x298;
      x9792._3 = x297;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x30825 = customerTblIdx0.get(x9792);
      ite30808 = x30825;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x9754 = ite30808;
    char* x32964 = strstr((x9754->_14).data_, "BC");
    if((x32964!=(NULL))) {
      PString x4365 = PString(500);
      x4365.append((x9754->_1));
      x4365.append(' ');
      x4365.append(x298);
      x4365.append(' ');
      x4365.append(x297);
      x4365.append(' ');
      x4365.append(x295);
      x4365.append(' ');
      x4365.append(x294);
      x4365.append(' ');
      x4365.append('$');
      x4365.append(x301);
      x4365.append(' ');
      x4365.appendDate(x292);
      x4365.append(' ');
      x4365.append('|');
      x4365.append(' ');
      x4365.append((x9754->_21).data_, 500);
      x9754->_17 += x301;
      x9754->_21 = x4365;
    } else {
      x9754->_17 += x301;
    };
    clearTempMem();
  }
  FORCE_INLINE void NewOrderTx(int x330, date x331, int x332, int x333, int x334, int x335, int x336, int x337, int* x338, int* x339, int* x340, double* x341, PString* x342, int* x343, PString* x344, double* x345) {
    int x347 = 0;
    int x350 = 0;
    PString idata[x336];
    int x355 = 1;
    while(1) {
      
      int x357 = x347;
      int ite31038 = 0;
      if((x357<(x336))) {
        
        int x359 = x355;
        int x31039 = x359;
        ite31038 = x31039;
      } else {
        ite31038 = 0;
      };
      int x30912 = ite31038;
      if (!(x30912)) break; 
      
      int x362 = x347;
      int x363 = x338[x362];
      x9916._1 = x363;
      struct SEntry5_IISDS* x15103 = itemTblIdx0.get(x9916);
      if((x15103==(NULL))) {
        x355 = 0;
      } else {
        int x369 = x347;
        x342[x369] = (x15103->_3);
        int x372 = x347;
        x341[x372] = (x15103->_4);
        int x375 = x347;
        idata[x375] = (x15103->_5);
      };
      int x379 = x347;
      x347 = (x379+(1));
    };
    int x383 = x355;
    if(x383) {
      x9936._1 = x335;
      x9936._2 = x334;
      x9936._3 = x333;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15125 = customerTblIdx0.get(x9936);
      x9939._1 = x333;
      struct SEntry9_ISSSSSSDD* x15128 = warehouseTblIdx0.get(x9939);
      x9942._1 = x334;
      x9942._2 = x333;
      struct SEntry11_IISSSSSSDDI* x15132 = districtTblIdx0.get(x9942);
      int x9944 = x15132->_11;
      x15132->_11 += 1;
      x9949._1 = x9944;
      x9949._2 = x334;
      x9949._3 = x333;
      x9949._4 = x335;
      x9949._5 = x331;
      x9949._6 = -1;
      x9949._7 = x336;
      x9949._8 = (x337>(0));
      orderTbl.insert_nocheck(x9949);
      x9952._1 = x9944;
      x9952._2 = x334;
      x9952._3 = x333;
      newOrderTbl.insert_nocheck(x9952);
      double x408 = 0.0;
      x347 = 0;
      while(1) {
        
        int x411 = x347;
        if (!((x411<(x336)))) break; 
        
        int x414 = x347;
        int ol_supply_w_id = x339[x414];
        int x417 = x347;
        int ol_i_id = x338[x417];
        int x420 = x347;
        int ol_quantity = x340[x420];
        x9966._1 = ol_i_id;
        x9966._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x15165 = stockTblIdx0.get(x9966);
        const PString& x9969 = *(&x15165->_4 + (x334-1));
        int x9970 = x15165->_3;
        int x431 = x347;
        x343[x431] = x9970;
        int x433 = x347;
        PString& x434 = idata[x433];
        char* x33120 = strstr(x434.data_, "original");
        int ite31112 = 0;
        if((x33120!=(NULL))) {
          
          char* x33126 = strstr((x15165->_17).data_, "original");
          int x31113 = (x33126!=(NULL));
          ite31112 = x31113;
        } else {
          ite31112 = 0;
        };
        int x30981 = ite31112;
        if(x30981) {
          int x439 = x347;
          x344[x439].data_[0] = 'B';
        } else {
          int x441 = x347;
          x344[x441].data_[0] = 'G';
        };
        x15165->_3 = (x9970-(ol_quantity));
        if((x9970<=(ol_quantity))) {
          x15165->_3 += 91;
        };
        int x450 = 0;
        if((ol_supply_w_id!=(x333))) {
          x450 = 1;
        };
        int x463 = x347;
        double x464 = x341[x463];
        double ol_amount = ((ol_quantity*(x464))*(((1.0+((x15128->_8)))+((x15132->_9)))))*((1.0-((x15125->_16))));
        int x472 = x347;
        x345[x472] = ol_amount;
        double x474 = x408;
        x408 = (x474+(ol_amount));
        int x477 = x347;
        x10014._1 = x9944;
        x10014._2 = x334;
        x10014._3 = x333;
        x10014._4 = (x477+(1));
        x10014._5 = ol_i_id;
        x10014._6 = ol_supply_w_id;
        x10014._8 = ol_quantity;
        x10014._9 = ol_amount;
        x10014._10 = x9969;
        orderLineTbl.insert_nocheck(x10014);
        int x482 = x347;
        x347 = (x482+(1));
      };
    } else {
      int x486 = failedNO;
      failedNO = (1+(x486));
    };
    clearTempMem();
  }
  FORCE_INLINE void NewOrderTxLocal(int x490, date x491, int x492, int x493, int x494, int x495, int x496, int x497, int* x498, int* x499, int* x500, double* x501, PString* x502, int* x503, PString* x504, double* x505) {
    int x507 = 0;
    int x510 = 0;
    PString idata[x496];
    int x515 = 1;
    while(1) {
      
      int x517 = x507;
      int ite31438 = 0;
      if((x517<(x496))) {
        
        int x519 = x515;
        int x31439 = x519;
        ite31438 = x31439;
      } else {
        ite31438 = 0;
      };
      int x31312 = ite31438;
      if (!(x31312)) break; 
      
      int x522 = x507;
      int x523 = x498[x522];
      x10152._1 = x523;
      struct SEntry5_IISDS* x15377 = itemTblIdx0.get(x10152);
      if((x15377==(NULL))) {
        x515 = 0;
      } else {
        int x529 = x507;
        x502[x529] = (x15377->_3);
        int x532 = x507;
        x501[x532] = (x15377->_4);
        int x535 = x507;
        idata[x535] = (x15377->_5);
      };
      int x539 = x507;
      x507 = (x539+(1));
    };
    int x543 = x515;
    if(x543) {
      x10172._1 = x495;
      x10172._2 = x494;
      x10172._3 = x493;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15399 = customerTblIdx0.get(x10172);
      x10175._1 = x493;
      struct SEntry9_ISSSSSSDD* x15402 = warehouseTblIdx0.get(x10175);
      x10178._1 = x494;
      x10178._2 = x493;
      struct SEntry11_IISSSSSSDDI* x15406 = districtTblIdx0.get(x10178);
      int x10180 = x15406->_11;
      x15406->_11 += 1;
      x10185._1 = x10180;
      x10185._2 = x494;
      x10185._3 = x493;
      x10185._4 = x495;
      x10185._5 = x491;
      x10185._6 = -1;
      x10185._7 = x496;
      x10185._8 = (x497>(0));
      orderTbl.insert_nocheck(x10185);
      x10188._1 = x10180;
      x10188._2 = x494;
      x10188._3 = x493;
      newOrderTbl.insert_nocheck(x10188);
      double x568 = 0.0;
      x507 = 0;
      while(1) {
        
        int x571 = x507;
        if (!((x571<(x496)))) break; 
        
        int x574 = x507;
        int ol_supply_w_id = x499[x574];
        int x577 = x507;
        int ol_i_id = x498[x577];
        int x580 = x507;
        int ol_quantity = x500[x580];
        x10202._1 = ol_i_id;
        x10202._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x15439 = stockTblIdx0.get(x10202);
        const PString& x10205 = *(&x15439->_4 + (x494-1));
        int x589 = x507;
        PString& x590 = idata[x589];
        char* x33395 = strstr(x590.data_, "original");
        int ite31509 = 0;
        if((x33395!=(NULL))) {
          
          char* x33401 = strstr((x15439->_17).data_, "original");
          int x31510 = (x33401!=(NULL));
          ite31509 = x31510;
        } else {
          ite31509 = 0;
        };
        int x31378 = ite31509;
        if(x31378) {
          int x595 = x507;
          x504[x595].data_[0] = 'B';
        } else {
          int x597 = x507;
          x504[x597].data_[0] = 'G';
        };
        int x10217 = x15439->_3;
        int x602 = x507;
        x503[x602] = x10217;
        x15439->_3 = (x10217-(ol_quantity));
        if((x10217<=(ol_quantity))) {
          x15439->_3 += 91;
        };
        int x610 = 0;
        if((ol_supply_w_id!=(x493))) {
          x610 = 1;
        };
        int x623 = x507;
        double x624 = x501[x623];
        double ol_amount = ((ol_quantity*(x624))*(((1.0+((x15402->_8)))+((x15406->_9)))))*((1.0-((x15399->_16))));
        int x632 = x507;
        x505[x632] = ol_amount;
        double x634 = x568;
        x568 = (x634+(ol_amount));
        int x637 = x507;
        x10250._1 = x10180;
        x10250._2 = x494;
        x10250._3 = x493;
        x10250._4 = (x637+(1));
        x10250._5 = ol_i_id;
        x10250._6 = ol_supply_w_id;
        x10250._8 = ol_quantity;
        x10250._9 = ol_amount;
        x10250._10 = x10205;
        orderLineTbl.insert_nocheck(x10250);
        int x642 = x507;
        x507 = (x642+(1));
      };
    } else {
      int x646 = failedNO;
      failedNO = (1+(x646));
    };
    clearTempMem();
  }
  FORCE_INLINE void NewOrderTxRemote(int x650, date x651, int x652, int x653, int x654, int x655, int x656, int x657, int* x658, int* x659, int* x660, double* x661, PString* x662, int* x663, PString* x664, double* x665) {
    int x667 = 0;
    int x670 = 0;
    int x673 = 1;
    while(1) {
      
      int x675 = x667;
      int ite31762 = 0;
      if((x675<(x656))) {
        
        int x677 = x673;
        int x31763 = x677;
        ite31762 = x31763;
      } else {
        ite31762 = 0;
      };
      int x31711 = ite31762;
      if (!(x31711)) break; 
      
      int x680 = x667;
      int x681 = x658[x680];
      x10387._1 = x681;
      struct SEntry5_IISDS* x15650 = itemTblIdx0.get(x10387);
      if((x15650==(NULL))) {
        x673 = 0;
      };
      int x688 = x667;
      x667 = (x688+(1));
    };
    int x692 = x673;
    if(x692) {
      x667 = 0;
      while(1) {
        
        int x694 = x667;
        if (!((x694<(x656)))) break; 
        
        int x697 = x667;
        int ol_supply_w_id = x659[x697];
        int x700 = x667;
        int ol_i_id = x658[x700];
        int x703 = x667;
        int ol_quantity = x660[x703];
        x10408._1 = ol_i_id;
        x10408._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x15672 = stockTblIdx0.get(x10408);
        int x10410 = x15672->_3;
        int x711 = x667;
        x663[x711] = x10410;
        x15672->_3 = (x10410-(ol_quantity));
        if((x10410<=(ol_quantity))) {
          x15672->_3 += 91;
        };
        int x719 = 0;
        if((ol_supply_w_id!=(x653))) {
          x719 = 1;
        };
        int x725 = x667;
        x667 = (x725+(1));
      };
    } else {
      int x729 = failedNO;
      failedNO = (1+(x729));
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

    for (size_t i = 0; i < numPrograms && !hasFinished; ++i) {
        Program *prg = tpcc.programs[i];
        switch (prg->id) {
            case NEWORDER:
            {
                NewOrder& p = *(NewOrder *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    bool local = true;
                    for (int ol = 0; ol < p.o_ol_cnt; ++ol)
                        if (CORE_FOR_W(p.supware[ol]) != thread_id) {
                            local = false;
                            break;
                        }
                    pt.xactCounts[0]++;
                    p.o_all_local = local;
                    if (local)
                        pt.NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
                    else
                        pt.NewOrderTxLocal(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
                } else {
                    bool remote = false;
                    for (int ol = 0; ol < p.o_ol_cnt; ++ol)
                        if (CORE_FOR_W(p.supware[ol]) == thread_id) {
                            remote = true;
                            break;
                        }
                    if (remote) {
                        p.o_all_local = false;
                        pt.xactCounts[0]++;
                        pt.NewOrderTxRemote(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
                    }
                }
                break;
            }
            case PAYMENTBYID:
            {
                PaymentById& p = *(PaymentById *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[1]++;
                    if (CORE_FOR_W(p.c_w_id) == thread_id)
                        pt.PaymentTx( false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
                    else
                        pt.PaymentTxLocal(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
                } else if (CORE_FOR_W(p.c_w_id) == thread_id) {
                    pt.xactCounts[1]++;
                    pt.PaymentTxRemote(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
                }
                break;
            }
            case PAYMENTBYNAME:
            {
                PaymentByName& p = *(PaymentByName *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[1]++;
                    if (CORE_FOR_W(p.c_w_id) == thread_id)
                        pt.PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
                    else
                        pt.PaymentTxLocal(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
                } else if (CORE_FOR_W(p.c_w_id) == thread_id) {
                    pt.xactCounts[1]++;
                    pt.PaymentTxRemote(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
                }
                break;
            }
            case ORDERSTATUSBYID:
            {
                OrderStatusById &p = *(OrderStatusById *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[2]++;
                    pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
                }
                break;
            }
            case ORDERSTATUSBYNAME:
            {
                OrderStatusByName &p = *(OrderStatusByName *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[2]++;
                    pt.OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
                }
                break;
            }
            case DELIVERY:
            {
                Delivery &p = *(Delivery *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[3]++;
                    pt.DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
                }
                break;
            }
            case STOCKLEVEL:
            {
                StockLevel &p = *(StockLevel *) prg;
                if (CORE_FOR_W(p.w_id) == thread_id) {
                    pt.xactCounts[4]++;
                    pt.StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
                }
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
      failedNO += partitions[i].failedNO;
      cout << "\n Thread " << i << " : ";
      for (int x = 0; x < 5; ++x) {
          cout << partitions[i].xactCounts[x] << "  ";
          xactCounts[x] += partitions[i].xactCounts[x];
          totalPrgsExec += partitions[i].xactCounts[x];
      }
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
    fout << "\nCPP-CDEFGILNOQRSUVX-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  /*
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info << "\n}\n";
  info.close();
  */
  
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
