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

     
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[21];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const { return new SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), _13, *_14.copy(), _15, _16, _17, _18, _19, _20, *_21.copy()); }
};
struct SEntry2_DS {
  double _1;  PString _2;  SEntry2_DS *prv;  SEntry2_DS *nxt; void* backPtrs[2];
  SEntry2_DS() :_1(-1.7976931348623157E308), _2(), prv(nullptr), nxt(nullptr) {}
  SEntry2_DS(const double& _1, const PString& _2) : _1(_1), _2(_2), prv(nullptr), nxt(nullptr) {}
  SEntry2_DS* copy() const { return new SEntry2_DS(_1, *_2.copy()); }
};
struct SEntry1_S {
  PString _1;  SEntry1_S *prv;  SEntry1_S *nxt; void* backPtrs[1];
  SEntry1_S() :_1(), prv(nullptr), nxt(nullptr) {}
  SEntry1_S(const PString& _1) : _1(_1), prv(nullptr), nxt(nullptr) {}
  SEntry1_S* copy() const { return new SEntry1_S(*_1.copy()); }
};
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
bool operator== (const SEntry2_DS& o1, const SEntry2_DS& o2) {
  return (fabs(o1._1 - o2._1) < 0.01) && 
  o1._2 == o2._2;
}
bool operator== (const SEntry1_S& o1, const SEntry1_S& o2) {
  return o1._1 == o2._1;
}
 struct SEntry1_S_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry1_S& x475)  { 
    int x476 = 0;
    int x477 = x476;
    x476 = (x477^(((((HASH((x475._1)))+(-1640531527))+((x477<<(6))))+((x477>>(2))))));
    int x487 = x476;
    return x487; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry1_S& x489, const struct SEntry1_S& x490) { 
    int x491 = 0;
    if(((x489._1)==((x490._1)))) {
      x491 = 0;
    } else {
      x491 = 1;
    };
    int x498 = x491;
    return x498; 
  }
};
 struct SEntry2_DS_Idx12 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry2_DS& x432)  { 
    int x433 = 0;
    int x434 = x433;
    x433 = (x434^(((((HASH((x432._1)))+(-1640531527))+((x434<<(6))))+((x434>>(2))))));
    int x444 = x433;
    x433 = (x444^(((((HASH((x432._2)))+(-1640531527))+((x444<<(6))))+((x444>>(2))))));
    int x454 = x433;
    return x454; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry2_DS& x456, const struct SEntry2_DS& x457) { 
    int x458 = 0;
    if(((x456._1)==((x457._1)))) {
      if(((x456._2)==((x457._2)))) {
        x458 = 0;
      } else {
        x458 = 1;
      };
    } else {
      x458 = 1;
    };
    int x470 = x458;
    return x470; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x307)  { 
    int x308 = 0;
    int x309 = x308;
    x308 = (x309^(((((HASH((x307._1)))+(-1640531527))+((x309<<(6))))+((x309>>(2))))));
    int x319 = x308;
    x308 = (x319^(((((HASH((x307._2)))+(-1640531527))+((x319<<(6))))+((x319>>(2))))));
    int x329 = x308;
    x308 = (x329^(((((HASH((x307._3)))+(-1640531527))+((x329<<(6))))+((x329>>(2))))));
    int x339 = x308;
    return x339; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x341, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x342) { 
    int x343 = 0;
    if(((x341._1)==((x342._1)))) {
      if(((x341._2)==((x342._2)))) {
        if(((x341._3)==((x342._3)))) {
          x343 = 0;
        } else {
          x343 = 1;
        };
      } else {
        x343 = 1;
      };
    } else {
      x343 = 1;
    };
    int x360 = x343;
    return x360; 
  }
};

typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1> customerTblIdx0Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1>> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];




void fun1() {
  auto& x473 = customerTbl.map<struct SEntry2_DS, HashIndex<struct SEntry2_DS, char, SEntry2_DS_Idx12, 1>>(([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> struct SEntry2_DS* {
    struct SEntry2_DS* x2338 = (struct SEntry2_DS*)malloc(1 * sizeof(struct SEntry2_DS));
    memset(x2338, 0, 1 * sizeof(struct SEntry2_DS));
    x2338->_1 = ((e->_16)-((e->_17))); x2338->_2 = (e->_1);
    return x2338; 
  }));
  auto& x16 = x473.filter(([&](struct SEntry2_DS* e) -> int {
    return ((e->_1)<(1000.0)); 
  }));
  auto& x501 = x16.map<struct SEntry1_S, HashIndex<struct SEntry1_S, char, SEntry1_S_Idx1, 1>>(([&](struct SEntry2_DS* e) -> struct SEntry1_S* {
    struct SEntry1_S* x2348 = (struct SEntry1_S*)malloc(1 * sizeof(struct SEntry1_S));
    memset(x2348, 0, 1 * sizeof(struct SEntry1_S));
    x2348->_1 = (e->_2);
    return x2348; 
  }));
  int x27 = x501.fold<int>(0, ([&](int a, struct SEntry1_S* b) -> int {
    return (a+(1)); 
  }));
  int x28 = x27;
}
#include "MB1.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
   MB1 loader;
   loader.loadCust();
  
   size_t durations[5];
   for(int i = 0; i < 5; ++i) {
      auto start = Now;
      fun1();
      auto end = Now;
      durations[i] = DurationMS(end-start);
      cout << durations[i] << endl;
   }
  
        
}
