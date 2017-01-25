#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY false

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
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
const size_t itemTblSize = 100000;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

     
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
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  SEntry3_III* copy() const { return new SEntry3_III(_1, _2, _3); }
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS* copy() const { return new SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, *_8.copy()); }
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS* copy() const { return new SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), *_13.copy(), _14, _15, _16, *_17.copy()); }
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS* copy() const { return new SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, *_10.copy()); }
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
 struct SEntry10_IIIIIITIDS_Idx1234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4200)  { 
    int x4201 = -889275714;
    int x4202 = x4200._1;
    int x4204 = -862048943*((HASH(x4202)));
    int x4209 = x4201;
    int x4210 = (((x4204<<(15))|((x4204 >> (-15 & (8*sizeof(x4204)-1)))))*(461845907))^(x4209);
    x4201 = ((((x4210<<(13))|((x4210 >> (-13 & (8*sizeof(x4210)-1)))))*(5))+(-430675100));
    int x4217 = x4200._2;
    int x4219 = -862048943*((HASH(x4217)));
    int x4224 = x4201;
    int x4225 = (((x4219<<(15))|((x4219 >> (-15 & (8*sizeof(x4219)-1)))))*(461845907))^(x4224);
    x4201 = ((((x4225<<(13))|((x4225 >> (-13 & (8*sizeof(x4225)-1)))))*(5))+(-430675100));
    int x4232 = x4200._3;
    int x4234 = -862048943*((HASH(x4232)));
    int x4239 = x4201;
    int x4240 = (((x4234<<(15))|((x4234 >> (-15 & (8*sizeof(x4234)-1)))))*(461845907))^(x4239);
    x4201 = ((((x4240<<(13))|((x4240 >> (-13 & (8*sizeof(x4240)-1)))))*(5))+(-430675100));
    int x4247 = x4200._4;
    int x4249 = -862048943*((HASH(x4247)));
    int x4254 = x4201;
    int x4255 = (((x4249<<(15))|((x4249 >> (-15 & (8*sizeof(x4249)-1)))))*(461845907))^(x4254);
    x4201 = ((((x4255<<(13))|((x4255 >> (-13 & (8*sizeof(x4255)-1)))))*(5))+(-430675100));
    int x4262 = x4201;
    int x4263 = x4262^(2);
    int x4266 = (x4263^((x4263 >> (16 & (8*sizeof(x4263)-1)))))*(-2048144789);
    int x4269 = (x4266^((x4266 >> (13 & (8*sizeof(x4266)-1)))))*(-1028477387);
    return (x4269^((x4269 >> (16 & (8*sizeof(x4269)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4273, const struct SEntry10_IIIIIITIDS& x4274) { 
    int x4275 = 0;
    int x4276 = x4273._1;
    int x4277 = x4274._1;
    if((x4276==(x4277))) {
      int x4279 = x4273._2;
      int x4280 = x4274._2;
      if((x4279==(x4280))) {
        int x4282 = x4273._3;
        int x4283 = x4274._3;
        if((x4282==(x4283))) {
          int x4285 = x4273._4;
          int x4286 = x4274._4;
          if((x4285==(x4286))) {
            x4275 = 0;
          } else {
            
            x4275 = 1;
          };
        } else {
          
          x4275 = 1;
        };
      } else {
        
        x4275 = 1;
      };
    } else {
      
      x4275 = 1;
    };
    int x4297 = x4275;
    return x4297; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4088)  { 
    int x4089 = -889275714;
    int x4090 = x4088._2;
    int x4092 = -862048943*((HASH(x4090)));
    int x4097 = x4089;
    int x4098 = (((x4092<<(15))|((x4092 >> (-15 & (8*sizeof(x4092)-1)))))*(461845907))^(x4097);
    x4089 = ((((x4098<<(13))|((x4098 >> (-13 & (8*sizeof(x4098)-1)))))*(5))+(-430675100));
    int x4105 = x4088._3;
    int x4107 = -862048943*((HASH(x4105)));
    int x4112 = x4089;
    int x4113 = (((x4107<<(15))|((x4107 >> (-15 & (8*sizeof(x4107)-1)))))*(461845907))^(x4112);
    x4089 = ((((x4113<<(13))|((x4113 >> (-13 & (8*sizeof(x4113)-1)))))*(5))+(-430675100));
    int x4120 = x4088._4;
    int x4122 = -862048943*((HASH(x4120)));
    int x4127 = x4089;
    int x4128 = (((x4122<<(15))|((x4122 >> (-15 & (8*sizeof(x4122)-1)))))*(461845907))^(x4127);
    x4089 = ((((x4128<<(13))|((x4128 >> (-13 & (8*sizeof(x4128)-1)))))*(5))+(-430675100));
    int x4135 = x4089;
    int x4136 = x4135^(2);
    int x4139 = (x4136^((x4136 >> (16 & (8*sizeof(x4136)-1)))))*(-2048144789);
    int x4142 = (x4139^((x4139 >> (13 & (8*sizeof(x4139)-1)))))*(-1028477387);
    return (x4142^((x4142 >> (16 & (8*sizeof(x4142)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4146, const struct SEntry8_IIIITIIB& x4147) { 
    int x4148 = 0;
    int x4149 = x4146._2;
    int x4150 = x4147._2;
    if((x4149==(x4150))) {
      int x4152 = x4146._3;
      int x4153 = x4147._3;
      if((x4152==(x4153))) {
        int x4155 = x4146._4;
        int x4156 = x4147._4;
        if((x4155==(x4156))) {
          x4148 = 0;
        } else {
          
          x4148 = 1;
        };
      } else {
        
        x4148 = 1;
      };
    } else {
      
      x4148 = 1;
    };
    int x4165 = x4148;
    return x4165; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3514)  { 
    int x3515 = -889275714;
    int x3516 = x3514._1;
    int x3518 = -862048943*((HASH(x3516)));
    int x3523 = x3515;
    int x3524 = (((x3518<<(15))|((x3518 >> (-15 & (8*sizeof(x3518)-1)))))*(461845907))^(x3523);
    x3515 = ((((x3524<<(13))|((x3524 >> (-13 & (8*sizeof(x3524)-1)))))*(5))+(-430675100));
    int x3531 = x3514._2;
    int x3533 = -862048943*((HASH(x3531)));
    int x3538 = x3515;
    int x3539 = (((x3533<<(15))|((x3533 >> (-15 & (8*sizeof(x3533)-1)))))*(461845907))^(x3538);
    x3515 = ((((x3539<<(13))|((x3539 >> (-13 & (8*sizeof(x3539)-1)))))*(5))+(-430675100));
    int x3546 = x3514._3;
    int x3548 = -862048943*((HASH(x3546)));
    int x3553 = x3515;
    int x3554 = (((x3548<<(15))|((x3548 >> (-15 & (8*sizeof(x3548)-1)))))*(461845907))^(x3553);
    x3515 = ((((x3554<<(13))|((x3554 >> (-13 & (8*sizeof(x3554)-1)))))*(5))+(-430675100));
    int x3561 = x3515;
    int x3562 = x3561^(2);
    int x3565 = (x3562^((x3562 >> (16 & (8*sizeof(x3562)-1)))))*(-2048144789);
    int x3568 = (x3565^((x3565 >> (13 & (8*sizeof(x3565)-1)))))*(-1028477387);
    return (x3568^((x3568 >> (16 & (8*sizeof(x3568)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3572, const struct SEntry3_III& x3573) { 
    int x3574 = 0;
    int x3575 = x3572._1;
    int x3576 = x3573._1;
    if((x3575==(x3576))) {
      int x3578 = x3572._2;
      int x3579 = x3573._2;
      if((x3578==(x3579))) {
        int x3581 = x3572._3;
        int x3582 = x3573._3;
        if((x3581==(x3582))) {
          x3574 = 0;
        } else {
          
          x3574 = 1;
        };
      } else {
        
        x3574 = 1;
      };
    } else {
      
      x3574 = 1;
    };
    int x3591 = x3574;
    return x3591; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3714)  { 
    int x3715 = -889275714;
    int x3716 = x3714._1;
    int x3718 = -862048943*((HASH(x3716)));
    int x3723 = x3715;
    int x3724 = (((x3718<<(15))|((x3718 >> (-15 & (8*sizeof(x3718)-1)))))*(461845907))^(x3723);
    x3715 = ((((x3724<<(13))|((x3724 >> (-13 & (8*sizeof(x3724)-1)))))*(5))+(-430675100));
    int x3731 = x3714._2;
    int x3733 = -862048943*((HASH(x3731)));
    int x3738 = x3715;
    int x3739 = (((x3733<<(15))|((x3733 >> (-15 & (8*sizeof(x3733)-1)))))*(461845907))^(x3738);
    x3715 = ((((x3739<<(13))|((x3739 >> (-13 & (8*sizeof(x3739)-1)))))*(5))+(-430675100));
    int x3746 = x3714._3;
    int x3748 = -862048943*((HASH(x3746)));
    int x3753 = x3715;
    int x3754 = (((x3748<<(15))|((x3748 >> (-15 & (8*sizeof(x3748)-1)))))*(461845907))^(x3753);
    x3715 = ((((x3754<<(13))|((x3754 >> (-13 & (8*sizeof(x3754)-1)))))*(5))+(-430675100));
    int x3761 = x3714._4;
    int x3763 = -862048943*((HASH(x3761)));
    int x3768 = x3715;
    int x3769 = (((x3763<<(15))|((x3763 >> (-15 & (8*sizeof(x3763)-1)))))*(461845907))^(x3768);
    x3715 = ((((x3769<<(13))|((x3769 >> (-13 & (8*sizeof(x3769)-1)))))*(5))+(-430675100));
    int x3776 = x3714._5;
    int x3778 = -862048943*((HASH(x3776)));
    int x3783 = x3715;
    int x3784 = (((x3778<<(15))|((x3778 >> (-15 & (8*sizeof(x3778)-1)))))*(461845907))^(x3783);
    x3715 = ((((x3784<<(13))|((x3784 >> (-13 & (8*sizeof(x3784)-1)))))*(5))+(-430675100));
    date x3791 = x3714._6;
    int x3793 = -862048943*((HASH(x3791)));
    int x3798 = x3715;
    int x3799 = (((x3793<<(15))|((x3793 >> (-15 & (8*sizeof(x3793)-1)))))*(461845907))^(x3798);
    x3715 = ((((x3799<<(13))|((x3799 >> (-13 & (8*sizeof(x3799)-1)))))*(5))+(-430675100));
    double x3806 = x3714._7;
    int x3808 = -862048943*((HASH(x3806)));
    int x3813 = x3715;
    int x3814 = (((x3808<<(15))|((x3808 >> (-15 & (8*sizeof(x3808)-1)))))*(461845907))^(x3813);
    x3715 = ((((x3814<<(13))|((x3814 >> (-13 & (8*sizeof(x3814)-1)))))*(5))+(-430675100));
    PString x3821 = x3714._8;
    int x3823 = -862048943*((HASH(x3821)));
    int x3828 = x3715;
    int x3829 = (((x3823<<(15))|((x3823 >> (-15 & (8*sizeof(x3823)-1)))))*(461845907))^(x3828);
    x3715 = ((((x3829<<(13))|((x3829 >> (-13 & (8*sizeof(x3829)-1)))))*(5))+(-430675100));
    int x3836 = x3715;
    int x3837 = x3836^(2);
    int x3840 = (x3837^((x3837 >> (16 & (8*sizeof(x3837)-1)))))*(-2048144789);
    int x3843 = (x3840^((x3840 >> (13 & (8*sizeof(x3840)-1)))))*(-1028477387);
    return (x3843^((x3843 >> (16 & (8*sizeof(x3843)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3847, const struct SEntry8_IIIIITDS& x3848) { 
    int x3849 = 0;
    int x3850 = x3847._1;
    int x3851 = x3848._1;
    if((x3850==(x3851))) {
      int x3853 = x3847._2;
      int x3854 = x3848._2;
      if((x3853==(x3854))) {
        int x3856 = x3847._3;
        int x3857 = x3848._3;
        if((x3856==(x3857))) {
          int x3859 = x3847._4;
          int x3860 = x3848._4;
          if((x3859==(x3860))) {
            int x3862 = x3847._5;
            int x3863 = x3848._5;
            if((x3862==(x3863))) {
              date x3865 = x3847._6;
              date x3866 = x3848._6;
              if((x3865==(x3866))) {
                double x3868 = x3847._7;
                double x3869 = x3848._7;
                if((x3868==(x3869))) {
                  PString x3871 = x3847._8;
                  PString x3872 = x3848._8;
                  if((x3871==(x3872))) {
                    x3849 = 0;
                  } else {
                    
                    x3849 = 1;
                  };
                } else {
                  
                  x3849 = 1;
                };
              } else {
                
                x3849 = 1;
              };
            } else {
              
              x3849 = 1;
            };
          } else {
            
            x3849 = 1;
          };
        } else {
          
          x3849 = 1;
        };
      } else {
        
        x3849 = 1;
      };
    } else {
      
      x3849 = 1;
    };
    int x3891 = x3849;
    return x3891; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4300)  { 
    int x4301 = -889275714;
    int x4302 = x4300._1;
    int x4304 = -862048943*((HASH(x4302)));
    int x4309 = x4301;
    int x4310 = (((x4304<<(15))|((x4304 >> (-15 & (8*sizeof(x4304)-1)))))*(461845907))^(x4309);
    x4301 = ((((x4310<<(13))|((x4310 >> (-13 & (8*sizeof(x4310)-1)))))*(5))+(-430675100));
    int x4317 = x4300._2;
    int x4319 = -862048943*((HASH(x4317)));
    int x4324 = x4301;
    int x4325 = (((x4319<<(15))|((x4319 >> (-15 & (8*sizeof(x4319)-1)))))*(461845907))^(x4324);
    x4301 = ((((x4325<<(13))|((x4325 >> (-13 & (8*sizeof(x4325)-1)))))*(5))+(-430675100));
    int x4332 = x4300._3;
    int x4334 = -862048943*((HASH(x4332)));
    int x4339 = x4301;
    int x4340 = (((x4334<<(15))|((x4334 >> (-15 & (8*sizeof(x4334)-1)))))*(461845907))^(x4339);
    x4301 = ((((x4340<<(13))|((x4340 >> (-13 & (8*sizeof(x4340)-1)))))*(5))+(-430675100));
    int x4347 = x4301;
    int x4348 = x4347^(2);
    int x4351 = (x4348^((x4348 >> (16 & (8*sizeof(x4348)-1)))))*(-2048144789);
    int x4354 = (x4351^((x4351 >> (13 & (8*sizeof(x4351)-1)))))*(-1028477387);
    return (x4354^((x4354 >> (16 & (8*sizeof(x4354)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4358, const struct SEntry10_IIIIIITIDS& x4359) { 
    int x4360 = 0;
    int x4361 = x4358._1;
    int x4362 = x4359._1;
    if((x4361==(x4362))) {
      int x4364 = x4358._2;
      int x4365 = x4359._2;
      if((x4364==(x4365))) {
        int x4367 = x4358._3;
        int x4368 = x4359._3;
        if((x4367==(x4368))) {
          x4360 = 0;
        } else {
          
          x4360 = 1;
        };
      } else {
        
        x4360 = 1;
      };
    } else {
      
      x4360 = 1;
    };
    int x4377 = x4360;
    return x4377; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3647)  { 
    int x3648 = -889275714;
    int x3649 = x3647._2;
    int x3651 = -862048943*((HASH(x3649)));
    int x3656 = x3648;
    int x3657 = (((x3651<<(15))|((x3651 >> (-15 & (8*sizeof(x3651)-1)))))*(461845907))^(x3656);
    x3648 = ((((x3657<<(13))|((x3657 >> (-13 & (8*sizeof(x3657)-1)))))*(5))+(-430675100));
    int x3664 = x3647._3;
    int x3666 = -862048943*((HASH(x3664)));
    int x3671 = x3648;
    int x3672 = (((x3666<<(15))|((x3666 >> (-15 & (8*sizeof(x3666)-1)))))*(461845907))^(x3671);
    x3648 = ((((x3672<<(13))|((x3672 >> (-13 & (8*sizeof(x3672)-1)))))*(5))+(-430675100));
    int x3679 = x3648;
    int x3680 = x3679^(2);
    int x3683 = (x3680^((x3680 >> (16 & (8*sizeof(x3680)-1)))))*(-2048144789);
    int x3686 = (x3683^((x3683 >> (13 & (8*sizeof(x3683)-1)))))*(-1028477387);
    return (x3686^((x3686 >> (16 & (8*sizeof(x3686)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3690, const struct SEntry3_III& x3691) { 
    int x3692 = 0;
    int x3693 = x3690._2;
    int x3694 = x3691._2;
    if((x3693==(x3694))) {
      int x3696 = x3690._3;
      int x3697 = x3691._3;
      if((x3696==(x3697))) {
        x3692 = 0;
      } else {
        
        x3692 = 1;
      };
    } else {
      
      x3692 = 1;
    };
    int x3704 = x3692;
    return x3704; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4412)  { 
    int x4413 = -889275714;
    int x4414 = x4412._2;
    int x4416 = -862048943*((HASH(x4414)));
    int x4421 = x4413;
    int x4422 = (((x4416<<(15))|((x4416 >> (-15 & (8*sizeof(x4416)-1)))))*(461845907))^(x4421);
    x4413 = ((((x4422<<(13))|((x4422 >> (-13 & (8*sizeof(x4422)-1)))))*(5))+(-430675100));
    int x4429 = x4412._3;
    int x4431 = -862048943*((HASH(x4429)));
    int x4436 = x4413;
    int x4437 = (((x4431<<(15))|((x4431 >> (-15 & (8*sizeof(x4431)-1)))))*(461845907))^(x4436);
    x4413 = ((((x4437<<(13))|((x4437 >> (-13 & (8*sizeof(x4437)-1)))))*(5))+(-430675100));
    PString x4444 = x4412._6;
    int x4446 = -862048943*((HASH(x4444)));
    int x4451 = x4413;
    int x4452 = (((x4446<<(15))|((x4446 >> (-15 & (8*sizeof(x4446)-1)))))*(461845907))^(x4451);
    x4413 = ((((x4452<<(13))|((x4452 >> (-13 & (8*sizeof(x4452)-1)))))*(5))+(-430675100));
    int x4459 = x4413;
    int x4460 = x4459^(2);
    int x4463 = (x4460^((x4460 >> (16 & (8*sizeof(x4460)-1)))))*(-2048144789);
    int x4466 = (x4463^((x4463 >> (13 & (8*sizeof(x4463)-1)))))*(-1028477387);
    return (x4466^((x4466 >> (16 & (8*sizeof(x4466)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4470, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4471) { 
    int x4472 = 0;
    int x4473 = x4470._2;
    int x4474 = x4471._2;
    if((x4473==(x4474))) {
      int x4476 = x4470._3;
      int x4477 = x4471._3;
      if((x4476==(x4477))) {
        PString x4479 = x4470._6;
        PString x4480 = x4471._6;
        if((x4479==(x4480))) {
          x4472 = 0;
        } else {
          
          x4472 = 1;
        };
      } else {
        
        x4472 = 1;
      };
    } else {
      
      x4472 = 1;
    };
    int x4489 = x4472;
    return x4489; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3940)  { 
    int x3941 = -889275714;
    int x3942 = x3940._1;
    int x3944 = -862048943*((HASH(x3942)));
    int x3949 = x3941;
    int x3950 = (((x3944<<(15))|((x3944 >> (-15 & (8*sizeof(x3944)-1)))))*(461845907))^(x3949);
    x3941 = ((((x3950<<(13))|((x3950 >> (-13 & (8*sizeof(x3950)-1)))))*(5))+(-430675100));
    int x3957 = x3940._2;
    int x3959 = -862048943*((HASH(x3957)));
    int x3964 = x3941;
    int x3965 = (((x3959<<(15))|((x3959 >> (-15 & (8*sizeof(x3959)-1)))))*(461845907))^(x3964);
    x3941 = ((((x3965<<(13))|((x3965 >> (-13 & (8*sizeof(x3965)-1)))))*(5))+(-430675100));
    int x3972 = x3940._3;
    int x3974 = -862048943*((HASH(x3972)));
    int x3979 = x3941;
    int x3980 = (((x3974<<(15))|((x3974 >> (-15 & (8*sizeof(x3974)-1)))))*(461845907))^(x3979);
    x3941 = ((((x3980<<(13))|((x3980 >> (-13 & (8*sizeof(x3980)-1)))))*(5))+(-430675100));
    int x3987 = x3941;
    int x3988 = x3987^(2);
    int x3991 = (x3988^((x3988 >> (16 & (8*sizeof(x3988)-1)))))*(-2048144789);
    int x3994 = (x3991^((x3991 >> (13 & (8*sizeof(x3991)-1)))))*(-1028477387);
    return (x3994^((x3994 >> (16 & (8*sizeof(x3994)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3998, const struct SEntry8_IIIITIIB& x3999) { 
    int x4000 = 0;
    int x4001 = x3998._1;
    int x4002 = x3999._1;
    if((x4001==(x4002))) {
      int x4004 = x3998._2;
      int x4005 = x3999._2;
      if((x4004==(x4005))) {
        int x4007 = x3998._3;
        int x4008 = x3999._3;
        if((x4007==(x4008))) {
          x4000 = 0;
        } else {
          
          x4000 = 1;
        };
      } else {
        
        x4000 = 1;
      };
    } else {
      
      x4000 = 1;
    };
    int x4017 = x4000;
    return x4017; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3594)  { 
    int x3595 = -889275714;
    int x3596 = x3594._2;
    int x3598 = -862048943*((HASH(x3596)));
    int x3603 = x3595;
    int x3604 = (((x3598<<(15))|((x3598 >> (-15 & (8*sizeof(x3598)-1)))))*(461845907))^(x3603);
    x3595 = ((((x3604<<(13))|((x3604 >> (-13 & (8*sizeof(x3604)-1)))))*(5))+(-430675100));
    int x3611 = x3594._3;
    int x3613 = -862048943*((HASH(x3611)));
    int x3618 = x3595;
    int x3619 = (((x3613<<(15))|((x3613 >> (-15 & (8*sizeof(x3613)-1)))))*(461845907))^(x3618);
    x3595 = ((((x3619<<(13))|((x3619 >> (-13 & (8*sizeof(x3619)-1)))))*(5))+(-430675100));
    int x3626 = x3595;
    int x3627 = x3626^(2);
    int x3630 = (x3627^((x3627 >> (16 & (8*sizeof(x3627)-1)))))*(-2048144789);
    int x3633 = (x3630^((x3630 >> (13 & (8*sizeof(x3630)-1)))))*(-1028477387);
    return (x3633^((x3633 >> (16 & (8*sizeof(x3633)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3637, const struct SEntry3_III& x3638) { 
    int x3639 = x3637._1;
    int x3640 = x3638._1;
    return ((x3639==(x3640)) ? 0 : ((x3639>(x3640)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4020)  { 
    int x4021 = -889275714;
    int x4022 = x4020._2;
    int x4024 = -862048943*((HASH(x4022)));
    int x4029 = x4021;
    int x4030 = (((x4024<<(15))|((x4024 >> (-15 & (8*sizeof(x4024)-1)))))*(461845907))^(x4029);
    x4021 = ((((x4030<<(13))|((x4030 >> (-13 & (8*sizeof(x4030)-1)))))*(5))+(-430675100));
    int x4037 = x4020._3;
    int x4039 = -862048943*((HASH(x4037)));
    int x4044 = x4021;
    int x4045 = (((x4039<<(15))|((x4039 >> (-15 & (8*sizeof(x4039)-1)))))*(461845907))^(x4044);
    x4021 = ((((x4045<<(13))|((x4045 >> (-13 & (8*sizeof(x4045)-1)))))*(5))+(-430675100));
    int x4052 = x4020._4;
    int x4054 = -862048943*((HASH(x4052)));
    int x4059 = x4021;
    int x4060 = (((x4054<<(15))|((x4054 >> (-15 & (8*sizeof(x4054)-1)))))*(461845907))^(x4059);
    x4021 = ((((x4060<<(13))|((x4060 >> (-13 & (8*sizeof(x4060)-1)))))*(5))+(-430675100));
    int x4067 = x4021;
    int x4068 = x4067^(2);
    int x4071 = (x4068^((x4068 >> (16 & (8*sizeof(x4068)-1)))))*(-2048144789);
    int x4074 = (x4071^((x4071 >> (13 & (8*sizeof(x4071)-1)))))*(-1028477387);
    return (x4074^((x4074 >> (16 & (8*sizeof(x4074)-1))))); 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4078, const struct SEntry8_IIIITIIB& x4079) { 
    int x4080 = x4078._1;
    int x4081 = x4079._1;
    return ((x4080==(x4081)) ? 0 : ((x4080>(x4081)) ? 1 : -1)); 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4501)  { 
    int x4502 = 0;
    int x4503 = x4501._1;
    int x4505 = x4502;
    x4502 = ((x4505*(100000))+((x4503-(1))));
    int x4509 = x4501._2;
    int x4511 = x4502;
    x4502 = ((x4511*(1))+((x4509-(1))));
    int x4515 = x4502;
    return x4515; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4498, const struct SEntry17_IIISSSSSSSSSSIIIS& x4499) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4389)  { 
    int x4390 = 0;
    int x4391 = x4389._1;
    int x4393 = x4390;
    x4390 = ((x4393*(3000))+((x4391-(1))));
    int x4397 = x4389._2;
    int x4399 = x4390;
    x4390 = ((x4399*(10))+((x4397-(1))));
    int x4403 = x4389._3;
    int x4405 = x4390;
    x4390 = ((x4405*(1))+((x4403-(1))));
    int x4409 = x4390;
    return x4409; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4386, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4387) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3921)  { 
    int x3922 = 0;
    int x3923 = x3921._1;
    int x3925 = x3922;
    x3922 = ((x3925*(100000))+((x3923-(1))));
    int x3929 = x3922;
    return x3929; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3918, const struct SEntry5_IISDS& x3919) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3902)  { 
    int x3903 = 0;
    int x3904 = x3902._1;
    int x3906 = x3903;
    x3903 = ((x3906*(1))+((x3904-(1))));
    int x3910 = x3903;
    return x3910; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3899, const struct SEntry9_ISSSSSSDD& x3900) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4178)  { 
    int x4179 = 0;
    int x4180 = x4178._1;
    int x4182 = x4179;
    x4179 = ((x4182*(10))+((x4180-(1))));
    int x4186 = x4178._2;
    int x4188 = x4179;
    x4179 = ((x4188*(1))+((x4186-(1))));
    int x4192 = x4179;
    return x4192; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4175, const struct SEntry11_IISSSSSSDDI& x4176) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x3710 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x3711 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x3897 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x3916 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x3935 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x4171 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x4172 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x4198 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x4383 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x4384 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x4495 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x4496 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x4521 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7783;
struct SEntry17_IIISSSSSSSSSSIIIS x8155;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7585;
struct SEntry11_IISSSSSSDDI x8131;
struct SEntry8_IIIITIIB x8138;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8125;
struct SEntry3_III x7561;
struct SEntry5_IISDS x8105;
struct SEntry9_ISSSSSSDD x8128;
struct SEntry10_IIIIIITIDS x7710;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7933;
struct SEntry11_IISSSSSSDDI x7893;
struct SEntry8_IIIITIIB x7773;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7950;
struct SEntry8_IIIITIIB x7572;
struct SEntry3_III x8141;
struct SEntry10_IIIIIITIDS x8228;
struct SEntry10_IIIIIITIDS x7581;
struct SEntry11_IISSSSSSDDI x7698;
struct SEntry8_IIIIITDS x7916;
struct SEntry17_IIISSSSSSSSSSIIIS x7729;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7800;
struct SEntry9_ISSSSSSDD x7888;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x7561._2 = x27;
    x7561._3 = x12;
    struct SEntry3_III* x12592 = x3711.get(x7561);
    if((x12592!=(NULL))) {
      int x7565 = x12592->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x7565;
      newOrderTbl.del(x12592);
      int x41 = x18;
      x7572._1 = x7565;
      x7572._2 = x41;
      x7572._3 = x12;
      struct SEntry8_IIIITIIB* x12605 = x4171.get(x7572);
      int x7574 = x12605->_4;
      x12605->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x7581._1 = x7565;
      x7581._2 = x52;
      x7581._3 = x12;
      x4384.slice(x7581, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
        orderLineEntry->_7 = x11;
        double x57 = x50;
        double x7625 = orderLineEntry->_9;
        x50 = (x57+(x7625));
      
      }));
      int x65 = x18;
      x7585._1 = x7574;
      x7585._2 = x65;
      x7585._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12627 = x4495.get(x7585);
      double x69 = x50;
      x12627->_17 += x69;
      x12627->_20 += 1;
    } else {
      
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x7698._1 = x85;
  x7698._2 = x84;
  struct SEntry11_IISSSSSSDDI* x12694 = x4198.get(x7698);
  int x7700 = x12694->_11;
  int x95 = (x7700-(20));
  unordered_set<int> unique_ol_i_id; //setApply2
  while(1) {
    
    int x99 = x95;
    if (!((x99<(x7700)))) break; 
    
    int x101 = x95;
    x7710._1 = x101;
    x7710._2 = x85;
    x7710._3 = x84;
    x4384.slice(x7710, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x7727 = orderLineEntry->_5;
      x7729._1 = x7727;
      x7729._2 = x84;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12708 = x4521.get(x7729);
      int x7731 = x12708->_3;
      if((x7731<(x86))) {
        unique_ol_i_id.insert(x7727);
      };
    
    }));
    int x118 = x95;
    x95 = (x118+(1));
  };
}
void OrderStatusTx(int x124, date x125, int x126, int x127, int x128, int x129, int x130, PString x131) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite17838 = NULL;
  if((x129>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x17839;
    x7783._2 = x128;
    x7783._3 = x127;
    x7783._6 = x131;
    x4496.slice(x7783, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x17839.push_back(custEntry);
    
    }));
    int x17847 = x17839.size();
    int x17849 = (x17847/(2));
    int x17857 = x17839.size();
    if(((x17857%(2))==(0))) {
      int x150 = x17849;
      x17849 = (x150-(1));
    };
    sort(x17839.begin(), x17839.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7824 = c1->_4;
      PString x7825 = c2->_4;
      return ((strcmpi(x7824.data_, x7825.data_))<(0)); 
    }));
    int x17865 = x17849;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17866 = x17839[x17865];
    ite17838 = x17866;
  } else {
    
    x7800._1 = x130;
    x7800._2 = x128;
    x7800._3 = x127;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17871 = x4495.get(x7800);
    ite17838 = x17871;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7770 = ite17838;
  int x7771 = x7770->_3;
  x7773._2 = x128;
  x7773._3 = x127;
  x7773._4 = x7771;
  struct SEntry8_IIIITIIB* x12794 = x4172.get(x7773);
  int x181 = 0;
  int x7776 = x12794->_1;
  x181 = x7776;
}
void PaymentTx(int x185, date x186, int x187, int x188, int x189, int x190, int x191, int x192, int x193, PString x194, double x195) {
  x7888._1 = x188;
  struct SEntry9_ISSSSSSDD* x12845 = x3916.get(x7888);
  x12845->_9 += x195;
  x7893._1 = x189;
  x7893._2 = x188;
  struct SEntry11_IISSSSSSDDI* x12850 = x4198.get(x7893);
  x12850->_10 += x195;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite17937 = NULL;
  if((x190>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x17938;
    x7933._2 = x192;
    x7933._3 = x191;
    x7933._6 = x194;
    x4496.slice(x7933, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x17938.push_back(custEntry);
    
    }));
    int x17946 = x17938.size();
    int x17948 = (x17946/(2));
    int x17956 = x17938.size();
    if(((x17956%(2))==(0))) {
      int x226 = x17948;
      x17948 = (x226-(1));
    };
    sort(x17938.begin(), x17938.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7996 = c1->_4;
      PString x7997 = c2->_4;
      return ((strcmpi(x7996.data_, x7997.data_))<(0)); 
    }));
    int x17964 = x17948;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17965 = x17938[x17964];
    ite17937 = x17965;
  } else {
    
    x7950._1 = x193;
    x7950._2 = x192;
    x7950._3 = x191;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17970 = x4495.get(x7950);
    ite17937 = x17970;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7898 = ite17937;
  PString x7899 = x7898->_21;
  PString x7900 = x7898->_14;
  char* x19287 = strstr(x7900.data_, "BC");
  if((x19287!=(NULL))) {
    int x7903 = x7898->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x7903, x192, x191, x189, x188, x195, IntToStrdate(x186), x7899.data_);
    x7898->_17 += x195;
    x7898->_21 = c_new_data;
  } else {
    
    x7898->_17 += x195;
  };
  PString x7910 = x12845->_2;
  PString x7911 = x12850->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x7910.data_, x7911.data_);
  int x7914 = x7898->_1;
  x7916._1 = x7914;
  x7916._2 = x192;
  x7916._3 = x191;
  x7916._4 = x189;
  x7916._5 = x188;
  x7916._6 = x186;
  x7916._7 = x195;
  x7916._8 = h_data;
  historyTbl.add(x7916);
}
void NewOrderTx(int x268, date x269, int x270, int x271, int x272, int x273, int x274, int x275, int* x276, int* x277, int* x278, double* x279, PString* x280, int* x281, PString* x282, double* x283) {
  int x285 = 0;
  int x288 = 0;
  PString idata[x274];
  int x293 = 1;
  while(1) {
    
    int x295 = x285;
    int ite18259 = 0;
    if((x295<(x274))) {
      
      int x297 = x293;
      int x18260 = x297;
      ite18259 = x18260;
    } else {
      
      ite18259 = 0;
    };
    int x18074 = ite18259;
    if (!(x18074)) break; 
    
    int x300 = x285;
    int x301 = x276[x300];
    x8105._1 = x301;
    struct SEntry5_IISDS* x12996 = x3935.get(x8105);
    if((x12996==(NULL))) {
      x293 = 0;
    } else {
      
      int x307 = x285;
      PString x8111 = x12996->_3;
      x280[x307] = x8111;
      int x310 = x285;
      double x8114 = x12996->_4;
      x279[x310] = x8114;
      int x313 = x285;
      PString x8117 = x12996->_5;
      idata[x313] = x8117;
    };
    int x317 = x285;
    x285 = (x317+(1));
  };
  int x321 = x293;
  if(x321) {
    x8125._1 = x273;
    x8125._2 = x272;
    x8125._3 = x271;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x13018 = x4495.get(x8125);
    x8128._1 = x271;
    struct SEntry9_ISSSSSSDD* x13021 = x3916.get(x8128);
    x8131._1 = x272;
    x8131._2 = x271;
    struct SEntry11_IISSSSSSDDI* x13025 = x4198.get(x8131);
    int x8133 = x13025->_11;
    x13025->_11 += 1;
    x8138._1 = x8133;
    x8138._2 = x272;
    x8138._3 = x271;
    x8138._4 = x273;
    x8138._5 = x269;
    x8138._6 = -1;
    x8138._7 = x274;
    x8138._8 = (x275>(0));
    orderTbl.add(x8138);
    x8141._1 = x8133;
    x8141._2 = x272;
    x8141._3 = x271;
    newOrderTbl.add(x8141);
    double x346 = 0.0;
    x285 = 0;
    while(1) {
      
      int x349 = x285;
      if (!((x349<(x274)))) break; 
      
      int x352 = x285;
      int ol_supply_w_id = x277[x352];
      int x355 = x285;
      int ol_i_id = x276[x355];
      int x358 = x285;
      int ol_quantity = x278[x358];
      x8155._1 = ol_i_id;
      x8155._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x13058 = x4521.get(x8155);
      PString ite18137 = PString();
      if((x272==(1))) {
        PString x18138 = x13058->_4;
        ite18137 = x18138;
      } else {
        
        PString ite18142 = PString();
        if((x272==(2))) {
          PString x18143 = x13058->_5;
          ite18142 = x18143;
        } else {
          
          PString ite18147 = PString();
          if((x272==(3))) {
            PString x18148 = x13058->_6;
            ite18147 = x18148;
          } else {
            
            PString ite18152 = PString();
            if((x272==(4))) {
              PString x18153 = x13058->_7;
              ite18152 = x18153;
            } else {
              
              PString ite18157 = PString();
              if((x272==(5))) {
                PString x18158 = x13058->_8;
                ite18157 = x18158;
              } else {
                
                PString ite18162 = PString();
                if((x272==(6))) {
                  PString x18163 = x13058->_9;
                  ite18162 = x18163;
                } else {
                  
                  PString ite18167 = PString();
                  if((x272==(7))) {
                    PString x18168 = x13058->_10;
                    ite18167 = x18168;
                  } else {
                    
                    PString ite18172 = PString();
                    if((x272==(8))) {
                      PString x18173 = x13058->_11;
                      ite18172 = x18173;
                    } else {
                      
                      PString ite18177 = PString();
                      if((x272==(9))) {
                        PString x18178 = x13058->_12;
                        ite18177 = x18178;
                      } else {
                        
                        PString x18180 = x13058->_13;
                        ite18177 = x18180;
                      };
                      PString x18176 = ite18177;
                      ite18172 = x18176;
                    };
                    PString x18171 = ite18172;
                    ite18167 = x18171;
                  };
                  PString x18166 = ite18167;
                  ite18162 = x18166;
                };
                PString x18161 = ite18162;
                ite18157 = x18161;
              };
              PString x18156 = ite18157;
              ite18152 = x18156;
            };
            PString x18151 = ite18152;
            ite18147 = x18151;
          };
          PString x18146 = ite18147;
          ite18142 = x18146;
        };
        PString x18141 = ite18142;
        ite18137 = x18141;
      };
      PString ol_dist_info = ite18137;
      int x8185 = x13058->_3;
      int x395 = x285;
      x281[x395] = x8185;
      PString x8188 = x13018->_14;
      char* x19522 = strstr(x8188.data_, "original");
      int ite18395 = 0;
      if((x19522!=(NULL))) {
        
        PString x8191 = x13058->_17;
        char* x19528 = strstr(x8191.data_, "original");
        int x18396 = (x19528!=(NULL));
        ite18395 = x18396;
      } else {
        
        ite18395 = 0;
      };
      int x18205 = ite18395;
      if(x18205) {
        int x402 = x285;
        x282[x402] = "B";
      } else {
        
        int x404 = x285;
        x282[x404] = "G";
      };
      x13058->_3 = (x8185-(ol_quantity));
      if((x8185<=(ol_quantity))) {
        x13058->_3 += 91;
      };
      int x413 = 0;
      if((ol_supply_w_id!=(x271))) {
        x413 = 1;
      };
      double x8208 = x13018->_16;
      double x8209 = x13021->_8;
      double x8210 = x13025->_9;
      int x426 = x285;
      double x427 = x279[x426];
      double ol_amount = ((ol_quantity*(x427))*(((1.0+(x8209))+(x8210))))*((1.0-(x8208)));
      int x435 = x285;
      x283[x435] = ol_amount;
      double x437 = x346;
      x346 = (x437+(ol_amount));
      int x440 = x285;
      x8228._1 = x8133;
      x8228._2 = x272;
      x8228._3 = x271;
      x8228._4 = (x440+(1));
      x8228._5 = ol_i_id;
      x8228._6 = ol_supply_w_id;
      x8228._8 = ol_quantity;
      x8228._9 = ol_amount;
      x8228._10 = ol_dist_info;
      orderLineTbl.add(x8228);
      int x445 = x285;
      x285 = (x445+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
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
  
  for(size_t i = 0; i < numPrograms; ++i){
    Program *prg = tpcc.programs[i];
    switch(prg->id){
       case NEWORDER :
        {
           NewOrder& p = *(NewOrder *)prg;
           NewOrderTx(false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
           break;
        }
      case PAYMENTBYID :
        {
           PaymentById& p = *(PaymentById *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
           break;
        }
      case PAYMENTBYNAME :
        {
           PaymentByName& p = *(PaymentByName *) prg;
           PaymentTx(false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
           break;
        }
      case ORDERSTATUSBYID :
        {
           OrderStatusById &p = *(OrderStatusById *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
           break;
        }
      case ORDERSTATUSBYNAME :
        {
           OrderStatusByName &p = *(OrderStatusByName *) prg;
           OrderStatusTx(false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
           break;
        }
      case DELIVERY :
        {
           Delivery &p = *(Delivery *) prg;
           DeliveryTx(false, p.datetime, p.w_id, p.o_carrier_id);
           break;
        }
      case STOCKLEVEL :
       {
         StockLevel &p = *(StockLevel *) prg;
         StockLevelTx(false, -1, -1, p.w_id, p.d_id, p.threshold);
         break;
       }
       default : cerr << "UNKNOWN PROGRAM TYPE" << endl;
  
    }
  }
  
  #ifdef VERIFY_TPCC
      if (warehouseTblPrimaryIdx == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (districtTblPrimaryIdx == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (customerTblPrimaryIdx == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orderTblPrimaryIdx == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orderLineTblPrimaryIdx == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (newOrderTblPrimaryIdx == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (itemTblPrimaryIdx == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (stockTblPrimaryIdx == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (historyTblPrimaryIdx == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
