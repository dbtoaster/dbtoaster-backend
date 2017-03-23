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
const size_t itemTblSize = 100000 * 1.5;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

const size_t districtTblArrayLengths[] = {0};
const size_t customerTblArrayLengths[] = {0,14001};
const size_t itemTblArrayLengths[] = {0};
const size_t historyTblArrayLengths[] = {42063};
const size_t orderTblArrayLengths[] = {42061,31548};
const size_t newOrderTblArrayLengths[] = {12602,15};
const size_t warehouseTblArrayLengths[] = {0};
const size_t stockTblArrayLengths[] = {0};
const size_t orderLineTblArrayLengths[] = {421661,42061};

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
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  SEntry3_III* copy() const { return new SEntry3_III(_1, _2, _3); }
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
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS* copy() const { return new SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, *_8.copy()); }
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS* copy() const { return new SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, *_10.copy()); }
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS* copy() const { return new SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), *_13.copy(), _14, _15, _16, *_17.copy()); }
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
 struct SEntry10_IIIIIITIDS_Idx1234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4755)  { 
    int x4756 = 0;
    int x4757 = x4756;
    x4756 = (x4757^(((((HASH((x4755._1)))+(-1640531527))+((x4757<<(6))))+((x4757>>(2))))));
    int x4767 = x4756;
    x4756 = (x4767^(((((HASH((x4755._2)))+(-1640531527))+((x4767<<(6))))+((x4767>>(2))))));
    int x4777 = x4756;
    x4756 = (x4777^(((((HASH((x4755._3)))+(-1640531527))+((x4777<<(6))))+((x4777>>(2))))));
    int x4787 = x4756;
    x4756 = (x4787^(((((HASH((x4755._4)))+(-1640531527))+((x4787<<(6))))+((x4787>>(2))))));
    int x4797 = x4756;
    return x4797; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4799, const struct SEntry10_IIIIIITIDS& x4800) { 
    int x4801 = 0;
    if(((x4799._1)==((x4800._1)))) {
      if(((x4799._2)==((x4800._2)))) {
        if(((x4799._3)==((x4800._3)))) {
          if(((x4799._4)==((x4800._4)))) {
            x4801 = 0;
          } else {
            x4801 = 1;
          };
        } else {
          x4801 = 1;
        };
      } else {
        x4801 = 1;
      };
    } else {
      x4801 = 1;
    };
    int x4823 = x4801;
    return x4823; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4673)  { 
    int x4674 = 0;
    int x4675 = x4674;
    x4674 = (x4675^(((((HASH((x4673._2)))+(-1640531527))+((x4675<<(6))))+((x4675>>(2))))));
    int x4685 = x4674;
    x4674 = (x4685^(((((HASH((x4673._3)))+(-1640531527))+((x4685<<(6))))+((x4685>>(2))))));
    int x4695 = x4674;
    x4674 = (x4695^(((((HASH((x4673._4)))+(-1640531527))+((x4695<<(6))))+((x4695>>(2))))));
    int x4705 = x4674;
    return x4705; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4707, const struct SEntry8_IIIITIIB& x4708) { 
    int x4709 = 0;
    if(((x4707._2)==((x4708._2)))) {
      if(((x4707._3)==((x4708._3)))) {
        if(((x4707._4)==((x4708._4)))) {
          x4709 = 0;
        } else {
          x4709 = 1;
        };
      } else {
        x4709 = 1;
      };
    } else {
      x4709 = 1;
    };
    int x4726 = x4709;
    return x4726; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x4264)  { 
    int x4265 = 0;
    int x4266 = x4265;
    x4265 = (x4266^(((((HASH((x4264._1)))+(-1640531527))+((x4266<<(6))))+((x4266>>(2))))));
    int x4276 = x4265;
    x4265 = (x4276^(((((HASH((x4264._2)))+(-1640531527))+((x4276<<(6))))+((x4276>>(2))))));
    int x4286 = x4265;
    x4265 = (x4286^(((((HASH((x4264._3)))+(-1640531527))+((x4286<<(6))))+((x4286>>(2))))));
    int x4296 = x4265;
    return x4296; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x4298, const struct SEntry3_III& x4299) { 
    int x4300 = 0;
    if(((x4298._1)==((x4299._1)))) {
      if(((x4298._2)==((x4299._2)))) {
        if(((x4298._3)==((x4299._3)))) {
          x4300 = 0;
        } else {
          x4300 = 1;
        };
      } else {
        x4300 = 1;
      };
    } else {
      x4300 = 1;
    };
    int x4317 = x4300;
    return x4317; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x4402)  { 
    int x4403 = 0;
    int x4404 = x4403;
    x4403 = (x4404^(((((HASH((x4402._1)))+(-1640531527))+((x4404<<(6))))+((x4404>>(2))))));
    int x4414 = x4403;
    x4403 = (x4414^(((((HASH((x4402._2)))+(-1640531527))+((x4414<<(6))))+((x4414>>(2))))));
    int x4424 = x4403;
    x4403 = (x4424^(((((HASH((x4402._3)))+(-1640531527))+((x4424<<(6))))+((x4424>>(2))))));
    int x4434 = x4403;
    x4403 = (x4434^(((((HASH((x4402._4)))+(-1640531527))+((x4434<<(6))))+((x4434>>(2))))));
    int x4444 = x4403;
    x4403 = (x4444^(((((HASH((x4402._5)))+(-1640531527))+((x4444<<(6))))+((x4444>>(2))))));
    int x4454 = x4403;
    x4403 = (x4454^(((((HASH((x4402._6)))+(-1640531527))+((x4454<<(6))))+((x4454>>(2))))));
    int x4464 = x4403;
    x4403 = (x4464^(((((HASH((x4402._7)))+(-1640531527))+((x4464<<(6))))+((x4464>>(2))))));
    int x4474 = x4403;
    x4403 = (x4474^(((((HASH((x4402._8)))+(-1640531527))+((x4474<<(6))))+((x4474>>(2))))));
    int x4484 = x4403;
    return x4484; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x4486, const struct SEntry8_IIIIITDS& x4487) { 
    int x4488 = 0;
    if(((x4486._1)==((x4487._1)))) {
      if(((x4486._2)==((x4487._2)))) {
        if(((x4486._3)==((x4487._3)))) {
          if(((x4486._4)==((x4487._4)))) {
            if(((x4486._5)==((x4487._5)))) {
              if(((x4486._6)==((x4487._6)))) {
                if(((x4486._7)==((x4487._7)))) {
                  if(((x4486._8)==((x4487._8)))) {
                    x4488 = 0;
                  } else {
                    x4488 = 1;
                  };
                } else {
                  x4488 = 1;
                };
              } else {
                x4488 = 1;
              };
            } else {
              x4488 = 1;
            };
          } else {
            x4488 = 1;
          };
        } else {
          x4488 = 1;
        };
      } else {
        x4488 = 1;
      };
    } else {
      x4488 = 1;
    };
    int x4530 = x4488;
    return x4530; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4826)  { 
    int x4827 = 0;
    int x4828 = x4827;
    x4827 = (x4828^(((((HASH((x4826._1)))+(-1640531527))+((x4828<<(6))))+((x4828>>(2))))));
    int x4838 = x4827;
    x4827 = (x4838^(((((HASH((x4826._2)))+(-1640531527))+((x4838<<(6))))+((x4838>>(2))))));
    int x4848 = x4827;
    x4827 = (x4848^(((((HASH((x4826._3)))+(-1640531527))+((x4848<<(6))))+((x4848>>(2))))));
    int x4858 = x4827;
    return x4858; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4860, const struct SEntry10_IIIIIITIDS& x4861) { 
    int x4862 = 0;
    if(((x4860._1)==((x4861._1)))) {
      if(((x4860._2)==((x4861._2)))) {
        if(((x4860._3)==((x4861._3)))) {
          x4862 = 0;
        } else {
          x4862 = 1;
        };
      } else {
        x4862 = 1;
      };
    } else {
      x4862 = 1;
    };
    int x4879 = x4862;
    return x4879; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x4354)  { 
    int x4355 = 0;
    int x4356 = x4355;
    x4355 = (x4356^(((((HASH((x4354._2)))+(-1640531527))+((x4356<<(6))))+((x4356>>(2))))));
    int x4366 = x4355;
    x4355 = (x4366^(((((HASH((x4354._3)))+(-1640531527))+((x4366<<(6))))+((x4366>>(2))))));
    int x4376 = x4355;
    return x4376; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x4378, const struct SEntry3_III& x4379) { 
    int x4380 = 0;
    if(((x4378._2)==((x4379._2)))) {
      if(((x4378._3)==((x4379._3)))) {
        x4380 = 0;
      } else {
        x4380 = 1;
      };
    } else {
      x4380 = 1;
    };
    int x4392 = x4380;
    return x4392; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4956)  { 
    int x4957 = 0;
    int x4958 = x4957;
    x4957 = (x4958^(((((HASH((x4956._2)))+(-1640531527))+((x4958<<(6))))+((x4958>>(2))))));
    int x4968 = x4957;
    x4957 = (x4968^(((((HASH((x4956._3)))+(-1640531527))+((x4968<<(6))))+((x4968>>(2))))));
    int x4978 = x4957;
    x4957 = (x4978^(((((HASH((x4956._6)))+(-1640531527))+((x4978<<(6))))+((x4978>>(2))))));
    int x4988 = x4957;
    return x4988; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4990, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4991) { 
    int x4992 = 0;
    if(((x4990._2)==((x4991._2)))) {
      if(((x4990._3)==((x4991._3)))) {
        if(((x4990._6)==((x4991._6)))) {
          x4992 = 0;
        } else {
          x4992 = 1;
        };
      } else {
        x4992 = 1;
      };
    } else {
      x4992 = 1;
    };
    int x5009 = x4992;
    return x5009; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4573)  { 
    int x4574 = 0;
    int x4575 = x4574;
    x4574 = (x4575^(((((HASH((x4573._1)))+(-1640531527))+((x4575<<(6))))+((x4575>>(2))))));
    int x4585 = x4574;
    x4574 = (x4585^(((((HASH((x4573._2)))+(-1640531527))+((x4585<<(6))))+((x4585>>(2))))));
    int x4595 = x4574;
    x4574 = (x4595^(((((HASH((x4573._3)))+(-1640531527))+((x4595<<(6))))+((x4595>>(2))))));
    int x4605 = x4574;
    return x4605; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4607, const struct SEntry8_IIIITIIB& x4608) { 
    int x4609 = 0;
    if(((x4607._1)==((x4608._1)))) {
      if(((x4607._2)==((x4608._2)))) {
        if(((x4607._3)==((x4608._3)))) {
          x4609 = 0;
        } else {
          x4609 = 1;
        };
      } else {
        x4609 = 1;
      };
    } else {
      x4609 = 1;
    };
    int x4626 = x4609;
    return x4626; 
  }
};
 struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x4320)  { 
    int x4321 = 0;
    int x4322 = x4321;
    x4321 = (x4322^(((((HASH((x4320._2)))+(-1640531527))+((x4322<<(6))))+((x4322>>(2))))));
    int x4332 = x4321;
    x4321 = (x4332^(((((HASH((x4320._3)))+(-1640531527))+((x4332<<(6))))+((x4332>>(2))))));
    int x4342 = x4321;
    return x4342; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x4344, const struct SEntry3_III& x4345) { 
    int x4346 = x4344._1;
    int x4347 = x4345._1;
    return ((x4346==(x4347)) ? 0 : ((x4346>(x4347)) ? 1 : -1)); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4911)  { 
    int x4912 = 0;
    int x4913 = x4912;
    x4912 = (x4913^(((((HASH((x4911._2)))+(-1640531527))+((x4913<<(6))))+((x4913>>(2))))));
    int x4923 = x4912;
    x4912 = (x4923^(((((HASH((x4911._3)))+(-1640531527))+((x4923<<(6))))+((x4923>>(2))))));
    int x4933 = x4912;
    x4912 = (x4933^(((((HASH((x4911._6)))+(-1640531527))+((x4933<<(6))))+((x4933>>(2))))));
    int x4943 = x4912;
    return x4943; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4945, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4946) { 
    int x4949 = strcmpi((x4945._4).data_, (x4946._4).data_);
    return ((x4949>(0)) ? 1 : ((x4949<(0)) ? -1 : 0)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4629)  { 
    int x4630 = 0;
    int x4631 = x4630;
    x4630 = (x4631^(((((HASH((x4629._2)))+(-1640531527))+((x4631<<(6))))+((x4631>>(2))))));
    int x4641 = x4630;
    x4630 = (x4641^(((((HASH((x4629._3)))+(-1640531527))+((x4641<<(6))))+((x4641>>(2))))));
    int x4651 = x4630;
    x4630 = (x4651^(((((HASH((x4629._4)))+(-1640531527))+((x4651<<(6))))+((x4651>>(2))))));
    int x4661 = x4630;
    return x4661; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4663, const struct SEntry8_IIIITIIB& x4664) { 
    int x4665 = x4663._1;
    int x4666 = x4664._1;
    return ((x4665==(x4666)) ? 0 : ((x4665>(x4666)) ? 1 : -1)); 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x5022)  { 
    int x5023 = 0;
    int x5026 = x5023;
    x5023 = ((x5026*(100000))+(((x5022._1)-(1))));
    int x5030 = x5023;
    return x5030; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x5019, const struct SEntry17_IIISSSSSSSSSSIIIS& x5020) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4894)  { 
    int x4895 = 0;
    int x4898 = x4895;
    x4895 = ((x4898*(3000))+(((x4894._1)-(1))));
    int x4904 = x4895;
    x4895 = ((x4904*(10))+(((x4894._2)-(1))));
    int x4908 = x4895;
    return x4908; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4891, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4892) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x4554)  { 
    int x4555 = 0;
    int x4558 = x4555;
    x4555 = ((x4558*(100000))+(((x4554._1)-(1))));
    int x4562 = x4555;
    return x4562; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x4551, const struct SEntry5_IISDS& x4552) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x4541)  { 
    int x4542 = 0;
    int x4543 = x4542;
    return x4543; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x4538, const struct SEntry9_ISSSSSSDD& x4539) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4739)  { 
    int x4740 = 0;
    int x4743 = x4740;
    x4740 = ((x4743*(10))+(((x4739._1)-(1))));
    int x4747 = x4740;
    return x4747; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4736, const struct SEntry11_IISSSSSSDDI& x4737) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_1, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   SlicedHeapIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_1, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl;
newOrderTblIdx0Type& newOrderTblIdx0 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& newOrderTblIdx1 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl;
historyTblIdx0Type& historyTblIdx0 = * (historyTblIdx0Type *)historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl;
warehouseTblIdx0Type& warehouseTblIdx0 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl;
itemTblIdx0Type& itemTblIdx0 = * (itemTblIdx0Type *)itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_1, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   SlicedHeapIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_1, 1>> orderTblStoreType;
orderTblStoreType  orderTbl;
orderTblIdx0Type& orderTblIdx0 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& orderTblIdx1 = * (orderTblIdx1Type *)orderTbl.index[1];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl;
districtTblIdx0Type& districtTblIdx0 = * (districtTblIdx0Type *)districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl;
orderLineTblIdx0Type& orderLineTblIdx0 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& orderLineTblIdx1 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef SlicedMedHeapIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   SlicedMedHeapIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4>> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& customerTblIdx1 = * (customerTblIdx1Type *)customerTbl.index[1];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl;
stockTblIdx0Type& stockTblIdx0 = * (stockTblIdx0Type *)stockTbl.index[0];

struct SEntry9_ISSSSSSDD x7816;
struct SEntry9_ISSSSSSDD x7620;
struct SEntry10_IIIIIITIDS x7891;
struct SEntry8_IIIITIIB x7826;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7592;
struct SEntry8_IIIIITDS x7667;
struct SEntry11_IISSSSSSDDI x7625;
struct SEntry8_IIIITIIB x7380;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7393;
struct SEntry3_III x7829;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7813;
struct SEntry11_IISSSSSSDDI x7819;
struct SEntry11_IISSSSSSDDI x7506;
struct SEntry5_IISDS x7793;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7685;
struct SEntry3_III x7369;
struct SEntry10_IIIIIITIDS x7519;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7682;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7595;
struct SEntry8_IIIITIIB x7584;
struct SEntry17_IIISSSSSSSSSSIIIS x7843;
struct SEntry10_IIIIIITIDS x7389;
struct SEntry17_IIISSSSSSSSSSIIIS x7539;


FORCE_INLINE void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[10];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x7369._2 = x27;
    x7369._3 = x12;
    struct SEntry3_III* x11361 = newOrderTblIdx1.get(x7369);
    if((x11361!=(NULL))) {
      int x7373 = x11361->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x7373;
      newOrderTbl.del(x11361);
      int x41 = x18;
      x7380._1 = x7373;
      x7380._2 = x41;
      x7380._3 = x12;
      struct SEntry8_IIIITIIB* x11374 = orderTblIdx0.get(x7380);
      x11374->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x7389._1 = x7373;
      x7389._2 = x52;
      x7389._3 = x12;
      //sliceRes 
      typedef typename orderLineTblIdx1Type::IFN IDXFN13948;
      HASH_RES_t h13948 = IDXFN13948::hash(x7389);
      auto* x13948 = &(orderLineTblIdx1.buckets_[h13948 % orderLineTblIdx1.size_]);
      if(x13948 -> head.obj) {
         do {
           if(h13948 == x13948->hash && !IDXFN13948::cmp(x7389, *x13948->head.obj))
             break;
         } while((x13948 = x13948->nxt));
      } else { 
         x13948 = nullptr;
      }
      if((x13948 == nullptr)) {
      } else {
        //sliceResMapNoUpd 
        auto* nx13948 = &x13948->head;
        do {
          auto orderLineEntry = nx13948->obj;
          orderLineEntry->_7 = x11;
          double x57 = x50;
          x50 = (x57+((orderLineEntry->_9)));
        } while((nx13948 = nx13948->nxt));
      };
      int x65 = x18;
      x7393._1 = (x11374->_4);
      x7393._2 = x65;
      x7393._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11396 = customerTblIdx0.get(x7393);
      double x69 = x50;
      x11396->_17 += x69;
      x11396->_20 += 1;
    } else {
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
FORCE_INLINE void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x7506._1 = x85;
  x7506._2 = x84;
  struct SEntry11_IISSSSSSDDI* x11463 = districtTblIdx0.get(x7506);
  int x7508 = x11463->_11;
  int x95 = (x7508-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x100 = x95;
    if (!((x100<(x7508)))) break; 
    
    int x102 = x95;
    x7519._1 = x102;
    x7519._2 = x85;
    x7519._3 = x84;
    //sliceRes 
    typedef typename orderLineTblIdx1Type::IFN IDXFN13995;
    HASH_RES_t h13995 = IDXFN13995::hash(x7519);
    auto* x13995 = &(orderLineTblIdx1.buckets_[h13995 % orderLineTblIdx1.size_]);
    if(x13995 -> head.obj) {
       do {
         if(h13995 == x13995->hash && !IDXFN13995::cmp(x7519, *x13995->head.obj))
           break;
       } while((x13995 = x13995->nxt));
    } else { 
       x13995 = nullptr;
    }
    if((x13995 == nullptr)) {
    } else {
      //sliceResMapNoUpd 
      auto* nx13995 = &x13995->head;
      do {
        auto orderLineEntry = nx13995->obj;
        int x7537 = orderLineEntry->_5;
        x7539._1 = x7537;
        x7539._2 = x84;
        struct SEntry17_IIISSSSSSSSSSIIIS* x11478 = stockTblIdx0.get(x7539);
        if(((x11478->_3)<(x86))) {
          unique_ol_i_id.insert(x7537);
        };
      } while((nx13995 = nx13995->nxt));
    };
    int x119 = x95;
    x95 = (x119+(1));
  };
}
FORCE_INLINE void OrderStatusTx(int x125, date x126, int x127, int x128, int x129, int x130, int x131, PString x132) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite23213 = 0;
  if((x130>(0))) {
    x7592._2 = x129;
    x7592._3 = x128;
    x7592._6 = x132;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x23217 = customerTblIdx1.get(x7592);
    ite23213 = x23217;
  } else {
    x7595._1 = x131;
    x7595._2 = x129;
    x7595._3 = x128;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x23222 = customerTblIdx0.get(x7595);
    ite23213 = x23222;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7581 = ite23213;
  x7584._2 = x129;
  x7584._3 = x128;
  x7584._4 = (x7581->_3);
  struct SEntry8_IIIITIIB* x11541 = orderTblIdx1.get(x7584);
  int x161 = 0;
  x161 = (x11541->_1);
}
FORCE_INLINE void PaymentTx(int x165, date x166, int x167, int x168, int x169, int x170, int x171, int x172, int x173, PString x174, double x175) {
  x7620._1 = x168;
  struct SEntry9_ISSSSSSDD* x11568 = warehouseTblIdx0.get(x7620);
  x11568->_9 += x175;
  x7625._1 = x169;
  x7625._2 = x168;
  struct SEntry11_IISSSSSSDDI* x11573 = districtTblIdx0.get(x7625);
  x11573->_10 += x175;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite23264 = 0;
  if((x170>(0))) {
    x7682._2 = x172;
    x7682._3 = x171;
    x7682._6 = x174;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x23268 = customerTblIdx1.get(x7682);
    ite23264 = x23268;
  } else {
    x7685._1 = x173;
    x7685._2 = x172;
    x7685._3 = x171;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x23273 = customerTblIdx0.get(x7685);
    ite23264 = x23273;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7630 = ite23264;
  char* x24295 = strstr((x7630->_14).data_, "BC");
  if((x24295!=(NULL))) {
    PString x2399 = PString(500);
    x2399.append((x7630->_1));
    x2399.append(' ');
    x2399.append(x172);
    x2399.append(' ');
    x2399.append(x171);
    x2399.append(' ');
    x2399.append(x169);
    x2399.append(' ');
    x2399.append(x168);
    x2399.append(' ');
    x2399.append('$');
    x2399.append(x175);
    x2399.append(' ');
    x2399.appendDate(x166);
    x2399.append(' ');
    x2399.append('|');
    x2399.append(' ');
    x2399.append((x7630->_21).data_, 500);
    x7630->_17 += x175;
    x7630->_21 = x2399;
  } else {
    x7630->_17 += x175;
  };
  PString x2425 = PString(24);
  x2425.append((x11568->_2).data_, 10);
  x2425.append("    ", 4);
  x2425.append((x11573->_3).data_, 10);
  x7667._1 = (x7630->_1);
  x7667._2 = x172;
  x7667._3 = x171;
  x7667._4 = x169;
  x7667._5 = x168;
  x7667._6 = x166;
  x7667._7 = x175;
  x7667._8 = x2425;
  historyTbl.insert_nocheck(x7667);
}
FORCE_INLINE void NewOrderTx(int x227, date x228, int x229, int x230, int x231, int x232, int x233, int x234, int* x235, int* x236, int* x237, double* x238, PString* x239, int* x240, PString* x241, double* x242) {
  int x244 = 0;
  int x247 = 0;
  PString idata[x233];
  int x252 = 1;
  while(1) {
    
    int x254 = x244;
    int ite23514 = 0;
    if((x254<(x233))) {
      
      int x256 = x252;
      int x23515 = x256;
      ite23514 = x23515;
    } else {
      ite23514 = 0;
    };
    int x23391 = ite23514;
    if (!(x23391)) break; 
    
    int x259 = x244;
    int x260 = x235[x259];
    x7793._1 = x260;
    struct SEntry5_IISDS* x11709 = itemTblIdx0.get(x7793);
    if((x11709==(NULL))) {
      x252 = 0;
    } else {
      int x266 = x244;
      x239[x266] = (x11709->_3);
      int x269 = x244;
      x238[x269] = (x11709->_4);
      int x272 = x244;
      idata[x272] = (x11709->_5);
    };
    int x276 = x244;
    x244 = (x276+(1));
  };
  int x280 = x252;
  if(x280) {
    x7813._1 = x232;
    x7813._2 = x231;
    x7813._3 = x230;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11731 = customerTblIdx0.get(x7813);
    x7816._1 = x230;
    struct SEntry9_ISSSSSSDD* x11734 = warehouseTblIdx0.get(x7816);
    x7819._1 = x231;
    x7819._2 = x230;
    struct SEntry11_IISSSSSSDDI* x11738 = districtTblIdx0.get(x7819);
    int x7821 = x11738->_11;
    x11738->_11 += 1;
    x7826._1 = x7821;
    x7826._2 = x231;
    x7826._3 = x230;
    x7826._4 = x232;
    x7826._5 = x228;
    x7826._6 = -1;
    x7826._7 = x233;
    x7826._8 = (x234>(0));
    orderTbl.insert_nocheck(x7826);
    x7829._1 = x7821;
    x7829._2 = x231;
    x7829._3 = x230;
    newOrderTbl.insert_nocheck(x7829);
    double x305 = 0.0;
    x244 = 0;
    while(1) {
      
      int x308 = x244;
      if (!((x308<(x233)))) break; 
      
      int x311 = x244;
      int ol_supply_w_id = x236[x311];
      int x314 = x244;
      int ol_i_id = x235[x314];
      int x317 = x244;
      int ol_quantity = x237[x317];
      x7843._1 = ol_i_id;
      x7843._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11771 = stockTblIdx0.get(x7843);
      const PString& x7846 = *(&x11771->_4 + (x231-1));
      int x7847 = x11771->_3;
      int x328 = x244;
      x240[x328] = x7847;
      int x330 = x244;
      PString& x331 = idata[x330];
      char* x24482 = strstr(x331.data_, "original");
      int ite23588 = 0;
      if((x24482!=(NULL))) {
        
        char* x24488 = strstr((x11771->_17).data_, "original");
        int x23589 = (x24488!=(NULL));
        ite23588 = x23589;
      } else {
        ite23588 = 0;
      };
      int x23460 = ite23588;
      if(x23460) {
        int x336 = x244;
        x241[x336].data_[0] = 'B';
      } else {
        int x338 = x244;
        x241[x338].data_[0] = 'G';
      };
      x11771->_3 = (x7847-(ol_quantity));
      if((x7847<=(ol_quantity))) {
        x11771->_3 += 91;
      };
      int x347 = 0;
      if((ol_supply_w_id!=(x230))) {
        x347 = 1;
      };
      int x360 = x244;
      double x361 = x238[x360];
      double ol_amount = ((ol_quantity*(x361))*(((1.0+((x11734->_8)))+((x11738->_9)))))*((1.0-((x11731->_16))));
      int x369 = x244;
      x242[x369] = ol_amount;
      double x371 = x305;
      x305 = (x371+(ol_amount));
      int x374 = x244;
      x7891._1 = x7821;
      x7891._2 = x231;
      x7891._3 = x230;
      x7891._4 = (x374+(1));
      x7891._5 = ol_i_id;
      x7891._6 = ol_supply_w_id;
      x7891._8 = ol_quantity;
      x7891._9 = ol_amount;
      x7891._10 = x7846;
      orderLineTbl.insert_nocheck(x7891);
      int x379 = x244;
      x244 = (x379+(1));
    };
  };
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
  cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  xactCounts[0]  << endl;
  cout << "TpmC = " << fixed <<  xactCounts[0] * 60000.0/execTime << endl;
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABCDEFGILNOQRSUVXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(warehouseTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(itemTblIdx0, info);
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
