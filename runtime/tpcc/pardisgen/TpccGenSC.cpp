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

const size_t districtTblArrayLengths[] = {0};
const size_t customerTblArrayLengths[] = {0,42001};
const size_t itemTblArrayLengths[] = {0};
const size_t historyTblArrayLengths[] = {328948};
const size_t orderTblArrayLengths[] = {327174,101108};
const size_t newOrderTblArrayLengths[] = {38792,43};
const size_t warehouseTblArrayLengths[] = {0};
const size_t stockTblArrayLengths[] = {0};
const size_t orderLineTblArrayLengths[] = {3270631,327174};

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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x8183)  { 
    int x8184 = 0;
    int x8185 = x8184;
    x8184 = (x8185^(((((HASH((x8183._3)))+(-1640531527))+((x8185<<(6))))+((x8185>>(2))))));
    int x8195 = x8184;
    x8184 = (x8195^(((((HASH((x8183._2)))+(-1640531527))+((x8195<<(6))))+((x8195>>(2))))));
    int x8205 = x8184;
    x8184 = (x8205^(((((HASH((x8183._1)))+(-1640531527))+((x8205<<(6))))+((x8205>>(2))))));
    int x8215 = x8184;
    x8184 = (x8215^(((((HASH((x8183._4)))+(-1640531527))+((x8215<<(6))))+((x8215>>(2))))));
    int x8225 = x8184;
    return x8225; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x8227, const struct SEntry10_IIIIIITIDS& x8228) { 
    int x8229 = 0;
    if(((x8227._3)==((x8228._3)))) {
      if(((x8227._2)==((x8228._2)))) {
        if(((x8227._1)==((x8228._1)))) {
          if(((x8227._4)==((x8228._4)))) {
            x8229 = 0;
          } else {
            x8229 = 1;
          };
        } else {
          x8229 = 1;
        };
      } else {
        x8229 = 1;
      };
    } else {
      x8229 = 1;
    };
    int x8251 = x8229;
    return x8251; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x8095)  { 
    int x8096 = 0;
    int x8097 = x8096;
    x8096 = (x8097^(((((HASH((x8095._2)))+(-1640531527))+((x8097<<(6))))+((x8097>>(2))))));
    int x8107 = x8096;
    x8096 = (x8107^(((((HASH((x8095._3)))+(-1640531527))+((x8107<<(6))))+((x8107>>(2))))));
    int x8117 = x8096;
    x8096 = (x8117^(((((HASH((x8095._4)))+(-1640531527))+((x8117<<(6))))+((x8117>>(2))))));
    int x8127 = x8096;
    return x8127; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x8129, const struct SEntry8_IIIITIIB& x8130) { 
    int x8131 = 0;
    if(((x8129._2)==((x8130._2)))) {
      if(((x8129._3)==((x8130._3)))) {
        if(((x8129._4)==((x8130._4)))) {
          x8131 = 0;
        } else {
          x8131 = 1;
        };
      } else {
        x8131 = 1;
      };
    } else {
      x8131 = 1;
    };
    int x8148 = x8131;
    return x8148; 
  }
};
 struct SEntry8_IIIITIIB_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x7995)  { 
    int x7996 = 0;
    int x7997 = x7996;
    x7996 = (x7997^(((((HASH((x7995._3)))+(-1640531527))+((x7997<<(6))))+((x7997>>(2))))));
    int x8007 = x7996;
    x7996 = (x8007^(((((HASH((x7995._2)))+(-1640531527))+((x8007<<(6))))+((x8007>>(2))))));
    int x8017 = x7996;
    x7996 = (x8017^(((((HASH((x7995._1)))+(-1640531527))+((x8017<<(6))))+((x8017>>(2))))));
    int x8027 = x7996;
    return x8027; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x8029, const struct SEntry8_IIIITIIB& x8030) { 
    int x8031 = 0;
    if(((x8029._3)==((x8030._3)))) {
      if(((x8029._2)==((x8030._2)))) {
        if(((x8029._1)==((x8030._1)))) {
          x8031 = 0;
        } else {
          x8031 = 1;
        };
      } else {
        x8031 = 1;
      };
    } else {
      x8031 = 1;
    };
    int x8048 = x8031;
    return x8048; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x7818)  { 
    int x7819 = 0;
    int x7820 = x7819;
    x7819 = (x7820^(((((HASH((x7818._1)))+(-1640531527))+((x7820<<(6))))+((x7820>>(2))))));
    int x7830 = x7819;
    x7819 = (x7830^(((((HASH((x7818._2)))+(-1640531527))+((x7830<<(6))))+((x7830>>(2))))));
    int x7840 = x7819;
    x7819 = (x7840^(((((HASH((x7818._3)))+(-1640531527))+((x7840<<(6))))+((x7840>>(2))))));
    int x7850 = x7819;
    x7819 = (x7850^(((((HASH((x7818._4)))+(-1640531527))+((x7850<<(6))))+((x7850>>(2))))));
    int x7860 = x7819;
    x7819 = (x7860^(((((HASH((x7818._5)))+(-1640531527))+((x7860<<(6))))+((x7860>>(2))))));
    int x7870 = x7819;
    x7819 = (x7870^(((((HASH((x7818._6)))+(-1640531527))+((x7870<<(6))))+((x7870>>(2))))));
    int x7880 = x7819;
    x7819 = (x7880^(((((HASH((x7818._7)))+(-1640531527))+((x7880<<(6))))+((x7880>>(2))))));
    int x7890 = x7819;
    x7819 = (x7890^(((((HASH((x7818._8)))+(-1640531527))+((x7890<<(6))))+((x7890>>(2))))));
    int x7900 = x7819;
    return x7900; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x7902, const struct SEntry8_IIIIITDS& x7903) { 
    int x7904 = 0;
    if(((x7902._1)==((x7903._1)))) {
      if(((x7902._2)==((x7903._2)))) {
        if(((x7902._3)==((x7903._3)))) {
          if(((x7902._4)==((x7903._4)))) {
            if(((x7902._5)==((x7903._5)))) {
              if(((x7902._6)==((x7903._6)))) {
                if(((x7902._7)==((x7903._7)))) {
                  if(((x7902._8)==((x7903._8)))) {
                    x7904 = 0;
                  } else {
                    x7904 = 1;
                  };
                } else {
                  x7904 = 1;
                };
              } else {
                x7904 = 1;
              };
            } else {
              x7904 = 1;
            };
          } else {
            x7904 = 1;
          };
        } else {
          x7904 = 1;
        };
      } else {
        x7904 = 1;
      };
    } else {
      x7904 = 1;
    };
    int x7946 = x7904;
    return x7946; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x8254)  { 
    int x8255 = 0;
    int x8256 = x8255;
    x8255 = (x8256^(((((HASH((x8254._1)))+(-1640531527))+((x8256<<(6))))+((x8256>>(2))))));
    int x8266 = x8255;
    x8255 = (x8266^(((((HASH((x8254._2)))+(-1640531527))+((x8266<<(6))))+((x8266>>(2))))));
    int x8276 = x8255;
    x8255 = (x8276^(((((HASH((x8254._3)))+(-1640531527))+((x8276<<(6))))+((x8276>>(2))))));
    int x8286 = x8255;
    return x8286; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x8288, const struct SEntry10_IIIIIITIDS& x8289) { 
    int x8290 = 0;
    if(((x8288._1)==((x8289._1)))) {
      if(((x8288._2)==((x8289._2)))) {
        if(((x8288._3)==((x8289._3)))) {
          x8290 = 0;
        } else {
          x8290 = 1;
        };
      } else {
        x8290 = 1;
      };
    } else {
      x8290 = 1;
    };
    int x8307 = x8290;
    return x8307; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x7770)  { 
    int x7771 = 0;
    int x7772 = x7771;
    x7771 = (x7772^(((((HASH((x7770._2)))+(-1640531527))+((x7772<<(6))))+((x7772>>(2))))));
    int x7782 = x7771;
    x7771 = (x7782^(((((HASH((x7770._3)))+(-1640531527))+((x7782<<(6))))+((x7782>>(2))))));
    int x7792 = x7771;
    return x7792; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x7794, const struct SEntry3_III& x7795) { 
    int x7796 = 0;
    if(((x7794._2)==((x7795._2)))) {
      if(((x7794._3)==((x7795._3)))) {
        x7796 = 0;
      } else {
        x7796 = 1;
      };
    } else {
      x7796 = 1;
    };
    int x7808 = x7796;
    return x7808; 
  }
};
 struct SEntry3_III_Idx321 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x7680)  { 
    int x7681 = 0;
    int x7682 = x7681;
    x7681 = (x7682^(((((HASH((x7680._3)))+(-1640531527))+((x7682<<(6))))+((x7682>>(2))))));
    int x7692 = x7681;
    x7681 = (x7692^(((((HASH((x7680._2)))+(-1640531527))+((x7692<<(6))))+((x7692>>(2))))));
    int x7702 = x7681;
    x7681 = (x7702^(((((HASH((x7680._1)))+(-1640531527))+((x7702<<(6))))+((x7702>>(2))))));
    int x7712 = x7681;
    return x7712; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x7714, const struct SEntry3_III& x7715) { 
    int x7716 = 0;
    if(((x7714._3)==((x7715._3)))) {
      if(((x7714._2)==((x7715._2)))) {
        if(((x7714._1)==((x7715._1)))) {
          x7716 = 0;
        } else {
          x7716 = 1;
        };
      } else {
        x7716 = 1;
      };
    } else {
      x7716 = 1;
    };
    int x7733 = x7716;
    return x7733; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8390)  { 
    int x8391 = 0;
    int x8392 = x8391;
    x8391 = (x8392^(((((HASH((x8390._2)))+(-1640531527))+((x8392<<(6))))+((x8392>>(2))))));
    int x8402 = x8391;
    x8391 = (x8402^(((((HASH((x8390._3)))+(-1640531527))+((x8402<<(6))))+((x8402>>(2))))));
    int x8412 = x8391;
    x8391 = (x8412^(((((HASH((x8390._6)))+(-1640531527))+((x8412<<(6))))+((x8412>>(2))))));
    int x8422 = x8391;
    return x8422; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8424, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8425) { 
    int x8426 = 0;
    if(((x8424._2)==((x8425._2)))) {
      if(((x8424._3)==((x8425._3)))) {
        if(((x8424._6)==((x8425._6)))) {
          x8426 = 0;
        } else {
          x8426 = 1;
        };
      } else {
        x8426 = 1;
      };
    } else {
      x8426 = 1;
    };
    int x8443 = x8426;
    return x8443; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x7736)  { 
    int x7737 = 0;
    int x7738 = x7737;
    x7737 = (x7738^(((((HASH((x7736._2)))+(-1640531527))+((x7738<<(6))))+((x7738>>(2))))));
    int x7748 = x7737;
    x7737 = (x7748^(((((HASH((x7736._3)))+(-1640531527))+((x7748<<(6))))+((x7748>>(2))))));
    int x7758 = x7737;
    return x7758; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x7760, const struct SEntry3_III& x7761) { 
    int x7762 = x7760._1;
    int x7763 = x7761._1;
    return ((x7762==(x7763)) ? 0 : ((x7762>(x7763)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8345)  { 
    int x8346 = 0;
    int x8347 = x8346;
    x8346 = (x8347^(((((HASH((x8345._2)))+(-1640531527))+((x8347<<(6))))+((x8347>>(2))))));
    int x8357 = x8346;
    x8346 = (x8357^(((((HASH((x8345._3)))+(-1640531527))+((x8357<<(6))))+((x8357>>(2))))));
    int x8367 = x8346;
    x8346 = (x8367^(((((HASH((x8345._6)))+(-1640531527))+((x8367<<(6))))+((x8367>>(2))))));
    int x8377 = x8346;
    return x8377; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8379, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8380) { 
    int x8383 = strcmpi((x8379._4).data_, (x8380._4).data_);
    return ((x8383>(0)) ? 1 : ((x8383<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x8051)  { 
    int x8052 = 0;
    int x8053 = x8052;
    x8052 = (x8053^(((((HASH((x8051._2)))+(-1640531527))+((x8053<<(6))))+((x8053>>(2))))));
    int x8063 = x8052;
    x8052 = (x8063^(((((HASH((x8051._3)))+(-1640531527))+((x8063<<(6))))+((x8063>>(2))))));
    int x8073 = x8052;
    x8052 = (x8073^(((((HASH((x8051._4)))+(-1640531527))+((x8073<<(6))))+((x8073>>(2))))));
    int x8083 = x8052;
    return x8083; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x8085, const struct SEntry8_IIIITIIB& x8086) { 
    int x8087 = x8085._1;
    int x8088 = x8086._1;
    return ((x8087==(x8088)) ? 0 : ((x8087>(x8088)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t6 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x7957)  { 
    int x7958 = 0;
    int x7961 = x7958;
    x7958 = ((x7961*(5))+(((x7957._1)-(1))));
    int x7965 = x7958;
    return x7965; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x7954, const struct SEntry9_ISSSSSSDD& x7955) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x8161)  { 
    int x8162 = 0;
    int x8165 = x8162;
    x8162 = ((x8165*(5))+(((x8161._2)-(1))));
    int x8171 = x8162;
    x8162 = ((x8171*(10))+(((x8161._1)-(1))));
    int x8175 = x8162;
    return x8175; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x8158, const struct SEntry11_IISSSSSSDDI& x8159) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100002 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x7976)  { 
    int x7977 = 0;
    int x7980 = x7977;
    x7977 = ((x7980*(100001))+(((x7976._1)-(1))));
    int x7984 = x7977;
    return x7984; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x7973, const struct SEntry5_IISDS& x7974) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8322)  { 
    int x8323 = 0;
    int x8326 = x8323;
    x8323 = ((x8326*(5))+(((x8322._3)-(1))));
    int x8332 = x8323;
    x8323 = ((x8332*(10))+(((x8322._2)-(1))));
    int x8338 = x8323;
    x8323 = ((x8338*(3000))+(((x8322._1)-(1))));
    int x8342 = x8323;
    return x8342; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8319, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x8320) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x8456)  { 
    int x8457 = 0;
    int x8460 = x8457;
    x8457 = ((x8460*(5))+(((x8456._2)-(1))));
    int x8466 = x8457;
    x8457 = ((x8466*(100000))+(((x8456._1)-(1))));
    int x8470 = x8457;
    return x8470; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x8453, const struct SEntry17_IIISSSSSSSSSSIIIS& x8454) { 
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
  newOrderTbl(newOrderTblArrayLengths, newOrderTblPoolSizes), newOrderTblIdx0(*(newOrderTblIdx0Type *)newOrderTbl.index[0]), newOrderTblIdx1(*(newOrderTblIdx1Type *)newOrderTbl.index[1]), 
  historyTbl(historyTblArrayLengths, historyTblPoolSizes), historyTblIdx0(*(historyTblIdx0Type *)historyTbl.index[0]), 
  warehouseTbl(warehouseTblArrayLengths, warehouseTblPoolSizes), warehouseTblIdx0(*(warehouseTblIdx0Type *)warehouseTbl.index[0]), 
  itemTbl(itemTblArrayLengths, itemTblPoolSizes), itemTblIdx0(*(itemTblIdx0Type *)itemTbl.index[0]), 
  orderTbl(orderTblArrayLengths, orderTblPoolSizes), orderTblIdx0(*(orderTblIdx0Type *)orderTbl.index[0]), orderTblIdx1(*(orderTblIdx1Type *)orderTbl.index[1]), 
  districtTbl(districtTblArrayLengths, districtTblPoolSizes), districtTblIdx0(*(districtTblIdx0Type *)districtTbl.index[0]), 
  orderLineTbl(orderLineTblArrayLengths, orderLineTblPoolSizes), orderLineTblIdx0(*(orderLineTblIdx0Type *)orderLineTbl.index[0]), orderLineTblIdx1(*(orderLineTblIdx1Type *)orderLineTbl.index[1]), 
  customerTbl(customerTblArrayLengths, customerTblPoolSizes), customerTblIdx0(*(customerTblIdx0Type *)customerTbl.index[0]), customerTblIdx1(*(customerTblIdx1Type *)customerTbl.index[1]), 
  stockTbl(stockTblArrayLengths, stockTblPoolSizes), stockTblIdx0(*(stockTblIdx0Type *)stockTbl.index[0])  {
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
  
  struct SEntry11_IISSSSSSDDI x11036;
  struct SEntry10_IIIIIITIDS x11048;
  struct SEntry9_ISSSSSSDD x11172;
  struct SEntry8_IIIIITDS x11219;
  struct SEntry5_IISDS x11525;
  struct SEntry8_IIIITIIB x10901;
  struct SEntry10_IIIIIITIDS x11859;
  struct SEntry17_IIISSSSSSSSSSIIIS x11575;
  struct SEntry9_ISSSSSSDD x11784;
  struct SEntry11_IISSSSSSDDI x11177;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11371;
  struct SEntry8_IIIITIIB x11111;
  struct SEntry17_IIISSSSSSSSSSIIIS x11067;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11444;
  struct SEntry3_III x10890;
  struct SEntry3_III x11561;
  struct SEntry17_IIISSSSSSSSSSIIIS x11811;
  struct SEntry11_IISSSSSSDDI x11551;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11545;
  struct SEntry9_ISSSSSSDD x11334;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11368;
  struct SEntry5_IISDS x11996;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11234;
  struct SEntry17_IIISSSSSSSSSSIIIS x12017;
  struct SEntry8_IIIITIIB x11794;
  struct SEntry8_IIIITIIB x11558;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11237;
  struct SEntry11_IISSSSSSDDI x11787;
  struct SEntry11_IISSSSSSDDI x11339;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11126;
  struct SEntry10_IIIIIITIDS x11623;
  struct SEntry5_IISDS x11761;
  struct SEntry10_IIIIIITIDS x11121;
  struct SEntry3_III x11797;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11129;
  struct SEntry8_IIIIITDS x11353;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11447;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x11781;
  struct SEntry9_ISSSSSSDD x11548;
  struct SEntry10_IIIIIITIDS x10910;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x10914;
  
  uint partitionID;
  uint failedNO;
  uint xactCounts[5];
         
  FORCE_INLINE void DeliveryTx(int x13, date x14, int x15, int x16) {
    int orderIDs[10];
    int x21 = 1;
    while(1) {
      
      int x23 = x21;
      if (!((x23<=(10)))) break; 
      
      int x30 = x21;
      x10890._2 = x30;
      x10890._3 = x15;
      struct SEntry3_III* x16429 = newOrderTblIdx1.get(x10890);
      if((x16429!=(NULL))) {
        int x10894 = x16429->_1;
        int x39 = x21;
        orderIDs[(x39-(1))] = x10894;
        newOrderTbl.del(x16429);
        int x44 = x21;
        x10901._1 = x10894;
        x10901._2 = x44;
        x10901._3 = x15;
        struct SEntry8_IIIITIIB* x16442 = orderTblIdx0.get(x10901);
        x16442->_6 = x16;
        double x53 = 0.0;
        int x55 = x21;
        x10910._1 = x10894;
        x10910._2 = x55;
        x10910._3 = x15;
        //sliceRes 
        typedef typename orderLineTblIdx1Type::IFN IDXFN19953;
        HASH_RES_t h19953 = IDXFN19953::hash(x10910);
        auto* x19953 = &(orderLineTblIdx1.buckets_[h19953 % orderLineTblIdx1.size_]);
        if(x19953 -> head.obj) {
           do {
             if(h19953 == x19953->hash && !IDXFN19953::cmp(x10910, *x19953->head.obj))
               break;
           } while((x19953 = x19953->nxt));
        } else { 
           x19953 = nullptr;
        }
        if((x19953 == nullptr)) {
        } else {
          //sliceResMapNoUpd 
          auto* nx19953 = &x19953->head;
          do {
            auto orderLineEntry = nx19953->obj;
            orderLineEntry->_7 = x14;
            double x60 = x53;
            x53 = (x60+((orderLineEntry->_9)));
          } while((nx19953 = nx19953->nxt));
        };
        int x68 = x21;
        x10914._1 = (x16442->_4);
        x10914._2 = x68;
        x10914._3 = x15;
        struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16464 = customerTblIdx0.get(x10914);
        double x72 = x53;
        x16464->_17 += x72;
        x16464->_20 += 1;
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
    x11036._1 = x91;
    x11036._2 = x90;
    struct SEntry11_IISSSSSSDDI* x16537 = districtTblIdx0.get(x11036);
    int x11038 = x16537->_11;
    int x101 = (x11038-(20));
    unordered_set<int> unique_ol_i_id; //setApply2
    while(1) {
      
      int x105 = x101;
      if (!((x105<(x11038)))) break; 
      
      int x107 = x101;
      x11048._1 = x107;
      x11048._2 = x91;
      x11048._3 = x90;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN20002;
      HASH_RES_t h20002 = IDXFN20002::hash(x11048);
      auto* x20002 = &(orderLineTblIdx1.buckets_[h20002 % orderLineTblIdx1.size_]);
      if(x20002 -> head.obj) {
         do {
           if(h20002 == x20002->hash && !IDXFN20002::cmp(x11048, *x20002->head.obj))
             break;
         } while((x20002 = x20002->nxt));
      } else { 
         x20002 = nullptr;
      }
      if((x20002 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx20002 = &x20002->head;
        do {
          auto orderLineEntry = nx20002->obj;
          int x11065 = orderLineEntry->_5;
          x11067._1 = x11065;
          x11067._2 = x90;
          struct SEntry17_IIISSSSSSSSSSIIIS* x16551 = stockTblIdx0.get(x11067);
          if(((x16551->_3)<(x92))) {
            unique_ol_i_id.insert(x11065);
          };
        } while((nx20002 = nx20002->nxt));
      };
      int x124 = x101;
      x101 = (x124+(1));
    };
    clearTempMem();
  }
  FORCE_INLINE void OrderStatusTx(int x130, date x131, int x132, int x133, int x134, int x135, int x136, PString x137) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite32735 = 0;
    if((x135>(0))) {
      x11126._2 = x134;
      x11126._3 = x133;
      x11126._6 = x137;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32739 = customerTblIdx1.get(x11126);
      ite32735 = x32739;
    } else {
      x11129._1 = x136;
      x11129._2 = x134;
      x11129._3 = x133;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32744 = customerTblIdx0.get(x11129);
      ite32735 = x32744;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11108 = ite32735;
    x11111._2 = x134;
    x11111._3 = x133;
    x11111._4 = (x11108->_3);
    struct SEntry8_IIIITIIB* x16613 = orderTblIdx1.get(x11111);
    int ite32754 = 0;
    if((x16613==(NULL))) {
      int x32755 = failedOS;
      failedOS = (1+(x32755));
      ite32754 = 0;
    } else {
      x11121._1 = (x16613->_1);
      x11121._2 = x134;
      x11121._3 = x133;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN32763;
      HASH_RES_t h32763 = IDXFN32763::hash(x11121);
      auto* x32763 = &(orderLineTblIdx1.buckets_[h32763 % orderLineTblIdx1.size_]);
      if(x32763 -> head.obj) {
         do {
           if(h32763 == x32763->hash && !IDXFN32763::cmp(x11121, *x32763->head.obj))
             break;
         } while((x32763 = x32763->nxt));
      } else { 
         x32763 = nullptr;
      }
      if((x32763 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx32763 = &x32763->head;
        do {
          auto orderLineEntry = nx32763->obj;
          int x175 = 1;
        } while((nx32763 = nx32763->nxt));
      };
      ite32754 = 1;
    };
    int x179 = ite32754;
    clearTempMem();
  }
  FORCE_INLINE void PaymentTx(int x180, date x181, int x182, int x183, int x184, int x185, int x186, int x187, int x188, PString x189, double x190) {
    x11172._1 = x183;
    struct SEntry9_ISSSSSSDD* x16662 = warehouseTblIdx0.get(x11172);
    x16662->_9 += x190;
    x11177._1 = x184;
    x11177._2 = x183;
    struct SEntry11_IISSSSSSDDI* x16667 = districtTblIdx0.get(x11177);
    x16667->_10 += x190;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite32820 = 0;
    if((x185>(0))) {
      x11234._2 = x187;
      x11234._3 = x186;
      x11234._6 = x189;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32824 = customerTblIdx1.get(x11234);
      ite32820 = x32824;
    } else {
      x11237._1 = x188;
      x11237._2 = x187;
      x11237._3 = x186;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32829 = customerTblIdx0.get(x11237);
      ite32820 = x32829;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11182 = ite32820;
    char* x34897 = strstr((x11182->_14).data_, "BC");
    if((x34897!=(NULL))) {
      PString x4225 = PString(500);
      x4225.append((x11182->_1));
      x4225.append(' ');
      x4225.append(x187);
      x4225.append(' ');
      x4225.append(x186);
      x4225.append(' ');
      x4225.append(x184);
      x4225.append(' ');
      x4225.append(x183);
      x4225.append(' ');
      x4225.append('$');
      x4225.append(x190);
      x4225.append(' ');
      x4225.appendDate(x181);
      x4225.append(' ');
      x4225.append('|');
      x4225.append(' ');
      x4225.append((x11182->_21).data_, 500);
      x11182->_17 += x190;
      x11182->_21 = x4225;
    } else {
      x11182->_17 += x190;
    };
    PString x4251 = PString(24);
    x4251.append((x16662->_2).data_, 10);
    x4251.append("    ", 4);
    x4251.append((x16667->_3).data_, 10);
    x11219._1 = (x11182->_1);
    x11219._2 = x187;
    x11219._3 = x186;
    x11219._4 = x184;
    x11219._5 = x183;
    x11219._6 = x181;
    x11219._7 = x190;
    x11219._8 = x4251;
    historyTbl.insert_nocheck(x11219);
    clearTempMem();
  }
  FORCE_INLINE void PaymentTxLocal(int x242, date x243, int x244, int x245, int x246, int x247, int x248, int x249, int x250, PString x251, double x252) {
    x11334._1 = x245;
    struct SEntry9_ISSSSSSDD* x16792 = warehouseTblIdx0.get(x11334);
    x16792->_9 += x252;
    x11339._1 = x246;
    x11339._2 = x245;
    struct SEntry11_IISSSSSSDDI* x16797 = districtTblIdx0.get(x11339);
    x16797->_10 += x252;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite32948 = 0;
    if((x247>(0))) {
      x11368._2 = x249;
      x11368._3 = x248;
      x11368._6 = x251;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32952 = customerTblIdx1.get(x11368);
      ite32948 = x32952;
    } else {
      x11371._1 = x250;
      x11371._2 = x249;
      x11371._3 = x248;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x32957 = customerTblIdx0.get(x11371);
      ite32948 = x32957;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11344 = ite32948;
    PString x4346 = PString(24);
    x4346.append((x16792->_2).data_, 10);
    x4346.append("    ", 4);
    x4346.append((x16797->_3).data_, 10);
    x11353._1 = (x11344->_1);
    x11353._2 = x249;
    x11353._3 = x248;
    x11353._4 = x246;
    x11353._5 = x245;
    x11353._6 = x243;
    x11353._7 = x252;
    x11353._8 = x4346;
    historyTbl.insert_nocheck(x11353);
    clearTempMem();
  }
  FORCE_INLINE void PaymentTxRemote(int x291, date x292, int x293, int x294, int x295, int x296, int x297, int x298, int x299, PString x300, double x301) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite33015 = 0;
    if((x296>(0))) {
      x11444._2 = x298;
      x11444._3 = x297;
      x11444._6 = x300;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x33019 = customerTblIdx1.get(x11444);
      ite33015 = x33019;
    } else {
      x11447._1 = x299;
      x11447._2 = x298;
      x11447._3 = x297;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x33024 = customerTblIdx0.get(x11447);
      ite33015 = x33024;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11412 = ite33015;
    char* x35057 = strstr((x11412->_14).data_, "BC");
    if((x35057!=(NULL))) {
      PString x4405 = PString(500);
      x4405.append((x11412->_1));
      x4405.append(' ');
      x4405.append(x298);
      x4405.append(' ');
      x4405.append(x297);
      x4405.append(' ');
      x4405.append(x295);
      x4405.append(' ');
      x4405.append(x294);
      x4405.append(' ');
      x4405.append('$');
      x4405.append(x301);
      x4405.append(' ');
      x4405.appendDate(x292);
      x4405.append(' ');
      x4405.append('|');
      x4405.append(' ');
      x4405.append((x11412->_21).data_, 500);
      x11412->_17 += x301;
      x11412->_21 = x4405;
    } else {
      x11412->_17 += x301;
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
      int ite33229 = 0;
      if((x357<(x336))) {
        
        int x359 = x355;
        int x33230 = x359;
        ite33229 = x33230;
      } else {
        ite33229 = 0;
      };
      int x33103 = ite33229;
      if (!(x33103)) break; 
      
      int x362 = x347;
      int x363 = x338[x362];
      x11525._1 = x363;
      struct SEntry5_IISDS* x16957 = itemTblIdx0.get(x11525);
      if((x16957==(NULL))) {
        x355 = 0;
      } else {
        int x369 = x347;
        x342[x369] = (x16957->_3);
        int x372 = x347;
        x341[x372] = (x16957->_4);
        int x375 = x347;
        idata[x375] = (x16957->_5);
      };
      int x379 = x347;
      x347 = (x379+(1));
    };
    int x383 = x355;
    if(x383) {
      x11545._1 = x335;
      x11545._2 = x334;
      x11545._3 = x333;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16979 = customerTblIdx0.get(x11545);
      x11548._1 = x333;
      struct SEntry9_ISSSSSSDD* x16982 = warehouseTblIdx0.get(x11548);
      x11551._1 = x334;
      x11551._2 = x333;
      struct SEntry11_IISSSSSSDDI* x16986 = districtTblIdx0.get(x11551);
      int x11553 = x16986->_11;
      x16986->_11 += 1;
      x11558._1 = x11553;
      x11558._2 = x334;
      x11558._3 = x333;
      x11558._4 = x335;
      x11558._5 = x331;
      x11558._6 = -1;
      x11558._7 = x336;
      x11558._8 = (x337>(0));
      orderTbl.insert_nocheck(x11558);
      x11561._1 = x11553;
      x11561._2 = x334;
      x11561._3 = x333;
      newOrderTbl.insert_nocheck(x11561);
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
        x11575._1 = ol_i_id;
        x11575._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x17019 = stockTblIdx0.get(x11575);
        const PString& x11578 = *(&x17019->_4 + (x334-1));
        int x11579 = x17019->_3;
        int x431 = x347;
        x343[x431] = x11579;
        int x433 = x347;
        PString& x434 = idata[x433];
        char* x35205 = strstr(x434.data_, "original");
        int ite33303 = 0;
        if((x35205!=(NULL))) {
          
          char* x35211 = strstr((x17019->_17).data_, "original");
          int x33304 = (x35211!=(NULL));
          ite33303 = x33304;
        } else {
          ite33303 = 0;
        };
        int x33172 = ite33303;
        if(x33172) {
          int x439 = x347;
          x344[x439].data_[0] = 'B';
        } else {
          int x441 = x347;
          x344[x441].data_[0] = 'G';
        };
        x17019->_3 = (x11579-(ol_quantity));
        if((x11579<=(ol_quantity))) {
          x17019->_3 += 91;
        };
        int x450 = 0;
        if((ol_supply_w_id!=(x333))) {
          x450 = 1;
        };
        int x463 = x347;
        double x464 = x341[x463];
        double ol_amount = ((ol_quantity*(x464))*(((1.0+((x16982->_8)))+((x16986->_9)))))*((1.0-((x16979->_16))));
        int x472 = x347;
        x345[x472] = ol_amount;
        double x474 = x408;
        x408 = (x474+(ol_amount));
        int x477 = x347;
        x11623._1 = x11553;
        x11623._2 = x334;
        x11623._3 = x333;
        x11623._4 = (x477+(1));
        x11623._5 = ol_i_id;
        x11623._6 = ol_supply_w_id;
        x11623._8 = ol_quantity;
        x11623._9 = ol_amount;
        x11623._10 = x11578;
        orderLineTbl.insert_nocheck(x11623);
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
      int ite33629 = 0;
      if((x517<(x496))) {
        
        int x519 = x515;
        int x33630 = x519;
        ite33629 = x33630;
      } else {
        ite33629 = 0;
      };
      int x33503 = ite33629;
      if (!(x33503)) break; 
      
      int x522 = x507;
      int x523 = x498[x522];
      x11761._1 = x523;
      struct SEntry5_IISDS* x17231 = itemTblIdx0.get(x11761);
      if((x17231==(NULL))) {
        x515 = 0;
      } else {
        int x529 = x507;
        x502[x529] = (x17231->_3);
        int x532 = x507;
        x501[x532] = (x17231->_4);
        int x535 = x507;
        idata[x535] = (x17231->_5);
      };
      int x539 = x507;
      x507 = (x539+(1));
    };
    int x543 = x515;
    if(x543) {
      x11781._1 = x495;
      x11781._2 = x494;
      x11781._3 = x493;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17253 = customerTblIdx0.get(x11781);
      x11784._1 = x493;
      struct SEntry9_ISSSSSSDD* x17256 = warehouseTblIdx0.get(x11784);
      x11787._1 = x494;
      x11787._2 = x493;
      struct SEntry11_IISSSSSSDDI* x17260 = districtTblIdx0.get(x11787);
      int x11789 = x17260->_11;
      x17260->_11 += 1;
      x11794._1 = x11789;
      x11794._2 = x494;
      x11794._3 = x493;
      x11794._4 = x495;
      x11794._5 = x491;
      x11794._6 = -1;
      x11794._7 = x496;
      x11794._8 = (x497>(0));
      orderTbl.insert_nocheck(x11794);
      x11797._1 = x11789;
      x11797._2 = x494;
      x11797._3 = x493;
      newOrderTbl.insert_nocheck(x11797);
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
        x11811._1 = ol_i_id;
        x11811._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x17293 = stockTblIdx0.get(x11811);
        const PString& x11814 = *(&x17293->_4 + (x494-1));
        int x589 = x507;
        PString& x590 = idata[x589];
        char* x35480 = strstr(x590.data_, "original");
        int ite33700 = 0;
        if((x35480!=(NULL))) {
          
          char* x35486 = strstr((x17293->_17).data_, "original");
          int x33701 = (x35486!=(NULL));
          ite33700 = x33701;
        } else {
          ite33700 = 0;
        };
        int x33569 = ite33700;
        if(x33569) {
          int x595 = x507;
          x504[x595].data_[0] = 'B';
        } else {
          int x597 = x507;
          x504[x597].data_[0] = 'G';
        };
        int x11826 = x17293->_3;
        int x602 = x507;
        x503[x602] = x11826;
        x17293->_3 = (x11826-(ol_quantity));
        if((x11826<=(ol_quantity))) {
          x17293->_3 += 91;
        };
        int x610 = 0;
        if((ol_supply_w_id!=(x493))) {
          x610 = 1;
        };
        int x623 = x507;
        double x624 = x501[x623];
        double ol_amount = ((ol_quantity*(x624))*(((1.0+((x17256->_8)))+((x17260->_9)))))*((1.0-((x17253->_16))));
        int x632 = x507;
        x505[x632] = ol_amount;
        double x634 = x568;
        x568 = (x634+(ol_amount));
        int x637 = x507;
        x11859._1 = x11789;
        x11859._2 = x494;
        x11859._3 = x493;
        x11859._4 = (x637+(1));
        x11859._5 = ol_i_id;
        x11859._6 = ol_supply_w_id;
        x11859._8 = ol_quantity;
        x11859._9 = ol_amount;
        x11859._10 = x11814;
        orderLineTbl.insert_nocheck(x11859);
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
      int ite33953 = 0;
      if((x675<(x656))) {
        
        int x677 = x673;
        int x33954 = x677;
        ite33953 = x33954;
      } else {
        ite33953 = 0;
      };
      int x33902 = ite33953;
      if (!(x33902)) break; 
      
      int x680 = x667;
      int x681 = x658[x680];
      x11996._1 = x681;
      struct SEntry5_IISDS* x17504 = itemTblIdx0.get(x11996);
      if((x17504==(NULL))) {
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
        x12017._1 = ol_i_id;
        x12017._2 = ol_supply_w_id;
        struct SEntry17_IIISSSSSSSSSSIIIS* x17526 = stockTblIdx0.get(x12017);
        int x12019 = x17526->_3;
        int x711 = x667;
        x663[x711] = x12019;
        x17526->_3 = (x12019-(ol_quantity));
        if((x12019<=(ol_quantity))) {
          x17526->_3 += 91;
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
    fout << "\nCPP-ABCDEFGILNOQRSUVXYZ-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] - failedCount[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/tpcc-par.json");
  info << "{\n";
  GET_RUN_STAT_P(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT_P(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT_P(newOrderTblIdx1, info);
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
