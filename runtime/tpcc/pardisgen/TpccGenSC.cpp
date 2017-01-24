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
    int x4203 = HASH(x4202);
    int x4204 = -862048943*(x4203);
    int x4205 = x4204<<(15);
    int x4206 = x4204 >> (-15 & (8*sizeof(x4204)-1));
    int x4207 = x4205|(x4206);
    int x4208 = x4207*(461845907);
    int x4209 = x4201;
    int x4210 = x4208^(x4209);
    int x4211 = x4210<<(13);
    int x4212 = x4210 >> (-13 & (8*sizeof(x4210)-1));
    int x4213 = x4211|(x4212);
    int x4214 = x4213*(5);
    int x4215 = x4214+(-430675100);
    x4201 = x4215;
    int x4217 = x4200._2;
    int x4218 = HASH(x4217);
    int x4219 = -862048943*(x4218);
    int x4220 = x4219<<(15);
    int x4221 = x4219 >> (-15 & (8*sizeof(x4219)-1));
    int x4222 = x4220|(x4221);
    int x4223 = x4222*(461845907);
    int x4224 = x4201;
    int x4225 = x4223^(x4224);
    int x4226 = x4225<<(13);
    int x4227 = x4225 >> (-13 & (8*sizeof(x4225)-1));
    int x4228 = x4226|(x4227);
    int x4229 = x4228*(5);
    int x4230 = x4229+(-430675100);
    x4201 = x4230;
    int x4232 = x4200._3;
    int x4233 = HASH(x4232);
    int x4234 = -862048943*(x4233);
    int x4235 = x4234<<(15);
    int x4236 = x4234 >> (-15 & (8*sizeof(x4234)-1));
    int x4237 = x4235|(x4236);
    int x4238 = x4237*(461845907);
    int x4239 = x4201;
    int x4240 = x4238^(x4239);
    int x4241 = x4240<<(13);
    int x4242 = x4240 >> (-13 & (8*sizeof(x4240)-1));
    int x4243 = x4241|(x4242);
    int x4244 = x4243*(5);
    int x4245 = x4244+(-430675100);
    x4201 = x4245;
    int x4247 = x4200._4;
    int x4248 = HASH(x4247);
    int x4249 = -862048943*(x4248);
    int x4250 = x4249<<(15);
    int x4251 = x4249 >> (-15 & (8*sizeof(x4249)-1));
    int x4252 = x4250|(x4251);
    int x4253 = x4252*(461845907);
    int x4254 = x4201;
    int x4255 = x4253^(x4254);
    int x4256 = x4255<<(13);
    int x4257 = x4255 >> (-13 & (8*sizeof(x4255)-1));
    int x4258 = x4256|(x4257);
    int x4259 = x4258*(5);
    int x4260 = x4259+(-430675100);
    x4201 = x4260;
    int x4262 = x4201;
    int x4263 = x4262^(2);
    int x4264 = x4263 >> (16 & (8*sizeof(x4263)-1));
    int x4265 = x4263^(x4264);
    int x4266 = x4265*(-2048144789);
    int x4267 = x4266 >> (13 & (8*sizeof(x4266)-1));
    int x4268 = x4266^(x4267);
    int x4269 = x4268*(-1028477387);
    int x4270 = x4269 >> (16 & (8*sizeof(x4269)-1));
    int x4271 = x4269^(x4270);
    return x4271; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4273, const struct SEntry10_IIIIIITIDS& x4274) { 
    int x4275 = 0;
    int x4276 = x4273._1;
    int x4277 = x4274._1;
    int x4278 = x4276==(x4277);
    if(x4278) {
      int x4279 = x4273._2;
      int x4280 = x4274._2;
      int x4281 = x4279==(x4280);
      if(x4281) {
        int x4282 = x4273._3;
        int x4283 = x4274._3;
        int x4284 = x4282==(x4283);
        if(x4284) {
          int x4285 = x4273._4;
          int x4286 = x4274._4;
          int x4287 = x4285==(x4286);
          if(x4287) {
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
    int x4091 = HASH(x4090);
    int x4092 = -862048943*(x4091);
    int x4093 = x4092<<(15);
    int x4094 = x4092 >> (-15 & (8*sizeof(x4092)-1));
    int x4095 = x4093|(x4094);
    int x4096 = x4095*(461845907);
    int x4097 = x4089;
    int x4098 = x4096^(x4097);
    int x4099 = x4098<<(13);
    int x4100 = x4098 >> (-13 & (8*sizeof(x4098)-1));
    int x4101 = x4099|(x4100);
    int x4102 = x4101*(5);
    int x4103 = x4102+(-430675100);
    x4089 = x4103;
    int x4105 = x4088._3;
    int x4106 = HASH(x4105);
    int x4107 = -862048943*(x4106);
    int x4108 = x4107<<(15);
    int x4109 = x4107 >> (-15 & (8*sizeof(x4107)-1));
    int x4110 = x4108|(x4109);
    int x4111 = x4110*(461845907);
    int x4112 = x4089;
    int x4113 = x4111^(x4112);
    int x4114 = x4113<<(13);
    int x4115 = x4113 >> (-13 & (8*sizeof(x4113)-1));
    int x4116 = x4114|(x4115);
    int x4117 = x4116*(5);
    int x4118 = x4117+(-430675100);
    x4089 = x4118;
    int x4120 = x4088._4;
    int x4121 = HASH(x4120);
    int x4122 = -862048943*(x4121);
    int x4123 = x4122<<(15);
    int x4124 = x4122 >> (-15 & (8*sizeof(x4122)-1));
    int x4125 = x4123|(x4124);
    int x4126 = x4125*(461845907);
    int x4127 = x4089;
    int x4128 = x4126^(x4127);
    int x4129 = x4128<<(13);
    int x4130 = x4128 >> (-13 & (8*sizeof(x4128)-1));
    int x4131 = x4129|(x4130);
    int x4132 = x4131*(5);
    int x4133 = x4132+(-430675100);
    x4089 = x4133;
    int x4135 = x4089;
    int x4136 = x4135^(2);
    int x4137 = x4136 >> (16 & (8*sizeof(x4136)-1));
    int x4138 = x4136^(x4137);
    int x4139 = x4138*(-2048144789);
    int x4140 = x4139 >> (13 & (8*sizeof(x4139)-1));
    int x4141 = x4139^(x4140);
    int x4142 = x4141*(-1028477387);
    int x4143 = x4142 >> (16 & (8*sizeof(x4142)-1));
    int x4144 = x4142^(x4143);
    return x4144; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4146, const struct SEntry8_IIIITIIB& x4147) { 
    int x4148 = 0;
    int x4149 = x4146._2;
    int x4150 = x4147._2;
    int x4151 = x4149==(x4150);
    if(x4151) {
      int x4152 = x4146._3;
      int x4153 = x4147._3;
      int x4154 = x4152==(x4153);
      if(x4154) {
        int x4155 = x4146._4;
        int x4156 = x4147._4;
        int x4157 = x4155==(x4156);
        if(x4157) {
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
    int x3517 = HASH(x3516);
    int x3518 = -862048943*(x3517);
    int x3519 = x3518<<(15);
    int x3520 = x3518 >> (-15 & (8*sizeof(x3518)-1));
    int x3521 = x3519|(x3520);
    int x3522 = x3521*(461845907);
    int x3523 = x3515;
    int x3524 = x3522^(x3523);
    int x3525 = x3524<<(13);
    int x3526 = x3524 >> (-13 & (8*sizeof(x3524)-1));
    int x3527 = x3525|(x3526);
    int x3528 = x3527*(5);
    int x3529 = x3528+(-430675100);
    x3515 = x3529;
    int x3531 = x3514._2;
    int x3532 = HASH(x3531);
    int x3533 = -862048943*(x3532);
    int x3534 = x3533<<(15);
    int x3535 = x3533 >> (-15 & (8*sizeof(x3533)-1));
    int x3536 = x3534|(x3535);
    int x3537 = x3536*(461845907);
    int x3538 = x3515;
    int x3539 = x3537^(x3538);
    int x3540 = x3539<<(13);
    int x3541 = x3539 >> (-13 & (8*sizeof(x3539)-1));
    int x3542 = x3540|(x3541);
    int x3543 = x3542*(5);
    int x3544 = x3543+(-430675100);
    x3515 = x3544;
    int x3546 = x3514._3;
    int x3547 = HASH(x3546);
    int x3548 = -862048943*(x3547);
    int x3549 = x3548<<(15);
    int x3550 = x3548 >> (-15 & (8*sizeof(x3548)-1));
    int x3551 = x3549|(x3550);
    int x3552 = x3551*(461845907);
    int x3553 = x3515;
    int x3554 = x3552^(x3553);
    int x3555 = x3554<<(13);
    int x3556 = x3554 >> (-13 & (8*sizeof(x3554)-1));
    int x3557 = x3555|(x3556);
    int x3558 = x3557*(5);
    int x3559 = x3558+(-430675100);
    x3515 = x3559;
    int x3561 = x3515;
    int x3562 = x3561^(2);
    int x3563 = x3562 >> (16 & (8*sizeof(x3562)-1));
    int x3564 = x3562^(x3563);
    int x3565 = x3564*(-2048144789);
    int x3566 = x3565 >> (13 & (8*sizeof(x3565)-1));
    int x3567 = x3565^(x3566);
    int x3568 = x3567*(-1028477387);
    int x3569 = x3568 >> (16 & (8*sizeof(x3568)-1));
    int x3570 = x3568^(x3569);
    return x3570; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3572, const struct SEntry3_III& x3573) { 
    int x3574 = 0;
    int x3575 = x3572._1;
    int x3576 = x3573._1;
    int x3577 = x3575==(x3576);
    if(x3577) {
      int x3578 = x3572._2;
      int x3579 = x3573._2;
      int x3580 = x3578==(x3579);
      if(x3580) {
        int x3581 = x3572._3;
        int x3582 = x3573._3;
        int x3583 = x3581==(x3582);
        if(x3583) {
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
    int x3717 = HASH(x3716);
    int x3718 = -862048943*(x3717);
    int x3719 = x3718<<(15);
    int x3720 = x3718 >> (-15 & (8*sizeof(x3718)-1));
    int x3721 = x3719|(x3720);
    int x3722 = x3721*(461845907);
    int x3723 = x3715;
    int x3724 = x3722^(x3723);
    int x3725 = x3724<<(13);
    int x3726 = x3724 >> (-13 & (8*sizeof(x3724)-1));
    int x3727 = x3725|(x3726);
    int x3728 = x3727*(5);
    int x3729 = x3728+(-430675100);
    x3715 = x3729;
    int x3731 = x3714._2;
    int x3732 = HASH(x3731);
    int x3733 = -862048943*(x3732);
    int x3734 = x3733<<(15);
    int x3735 = x3733 >> (-15 & (8*sizeof(x3733)-1));
    int x3736 = x3734|(x3735);
    int x3737 = x3736*(461845907);
    int x3738 = x3715;
    int x3739 = x3737^(x3738);
    int x3740 = x3739<<(13);
    int x3741 = x3739 >> (-13 & (8*sizeof(x3739)-1));
    int x3742 = x3740|(x3741);
    int x3743 = x3742*(5);
    int x3744 = x3743+(-430675100);
    x3715 = x3744;
    int x3746 = x3714._3;
    int x3747 = HASH(x3746);
    int x3748 = -862048943*(x3747);
    int x3749 = x3748<<(15);
    int x3750 = x3748 >> (-15 & (8*sizeof(x3748)-1));
    int x3751 = x3749|(x3750);
    int x3752 = x3751*(461845907);
    int x3753 = x3715;
    int x3754 = x3752^(x3753);
    int x3755 = x3754<<(13);
    int x3756 = x3754 >> (-13 & (8*sizeof(x3754)-1));
    int x3757 = x3755|(x3756);
    int x3758 = x3757*(5);
    int x3759 = x3758+(-430675100);
    x3715 = x3759;
    int x3761 = x3714._4;
    int x3762 = HASH(x3761);
    int x3763 = -862048943*(x3762);
    int x3764 = x3763<<(15);
    int x3765 = x3763 >> (-15 & (8*sizeof(x3763)-1));
    int x3766 = x3764|(x3765);
    int x3767 = x3766*(461845907);
    int x3768 = x3715;
    int x3769 = x3767^(x3768);
    int x3770 = x3769<<(13);
    int x3771 = x3769 >> (-13 & (8*sizeof(x3769)-1));
    int x3772 = x3770|(x3771);
    int x3773 = x3772*(5);
    int x3774 = x3773+(-430675100);
    x3715 = x3774;
    int x3776 = x3714._5;
    int x3777 = HASH(x3776);
    int x3778 = -862048943*(x3777);
    int x3779 = x3778<<(15);
    int x3780 = x3778 >> (-15 & (8*sizeof(x3778)-1));
    int x3781 = x3779|(x3780);
    int x3782 = x3781*(461845907);
    int x3783 = x3715;
    int x3784 = x3782^(x3783);
    int x3785 = x3784<<(13);
    int x3786 = x3784 >> (-13 & (8*sizeof(x3784)-1));
    int x3787 = x3785|(x3786);
    int x3788 = x3787*(5);
    int x3789 = x3788+(-430675100);
    x3715 = x3789;
    date x3791 = x3714._6;
    int x3792 = HASH(x3791);
    int x3793 = -862048943*(x3792);
    int x3794 = x3793<<(15);
    int x3795 = x3793 >> (-15 & (8*sizeof(x3793)-1));
    int x3796 = x3794|(x3795);
    int x3797 = x3796*(461845907);
    int x3798 = x3715;
    int x3799 = x3797^(x3798);
    int x3800 = x3799<<(13);
    int x3801 = x3799 >> (-13 & (8*sizeof(x3799)-1));
    int x3802 = x3800|(x3801);
    int x3803 = x3802*(5);
    int x3804 = x3803+(-430675100);
    x3715 = x3804;
    double x3806 = x3714._7;
    int x3807 = HASH(x3806);
    int x3808 = -862048943*(x3807);
    int x3809 = x3808<<(15);
    int x3810 = x3808 >> (-15 & (8*sizeof(x3808)-1));
    int x3811 = x3809|(x3810);
    int x3812 = x3811*(461845907);
    int x3813 = x3715;
    int x3814 = x3812^(x3813);
    int x3815 = x3814<<(13);
    int x3816 = x3814 >> (-13 & (8*sizeof(x3814)-1));
    int x3817 = x3815|(x3816);
    int x3818 = x3817*(5);
    int x3819 = x3818+(-430675100);
    x3715 = x3819;
    PString x3821 = x3714._8;
    int x3822 = HASH(x3821);
    int x3823 = -862048943*(x3822);
    int x3824 = x3823<<(15);
    int x3825 = x3823 >> (-15 & (8*sizeof(x3823)-1));
    int x3826 = x3824|(x3825);
    int x3827 = x3826*(461845907);
    int x3828 = x3715;
    int x3829 = x3827^(x3828);
    int x3830 = x3829<<(13);
    int x3831 = x3829 >> (-13 & (8*sizeof(x3829)-1));
    int x3832 = x3830|(x3831);
    int x3833 = x3832*(5);
    int x3834 = x3833+(-430675100);
    x3715 = x3834;
    int x3836 = x3715;
    int x3837 = x3836^(2);
    int x3838 = x3837 >> (16 & (8*sizeof(x3837)-1));
    int x3839 = x3837^(x3838);
    int x3840 = x3839*(-2048144789);
    int x3841 = x3840 >> (13 & (8*sizeof(x3840)-1));
    int x3842 = x3840^(x3841);
    int x3843 = x3842*(-1028477387);
    int x3844 = x3843 >> (16 & (8*sizeof(x3843)-1));
    int x3845 = x3843^(x3844);
    return x3845; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3847, const struct SEntry8_IIIIITDS& x3848) { 
    int x3849 = 0;
    int x3850 = x3847._1;
    int x3851 = x3848._1;
    int x3852 = x3850==(x3851);
    if(x3852) {
      int x3853 = x3847._2;
      int x3854 = x3848._2;
      int x3855 = x3853==(x3854);
      if(x3855) {
        int x3856 = x3847._3;
        int x3857 = x3848._3;
        int x3858 = x3856==(x3857);
        if(x3858) {
          int x3859 = x3847._4;
          int x3860 = x3848._4;
          int x3861 = x3859==(x3860);
          if(x3861) {
            int x3862 = x3847._5;
            int x3863 = x3848._5;
            int x3864 = x3862==(x3863);
            if(x3864) {
              date x3865 = x3847._6;
              date x3866 = x3848._6;
              int x3867 = x3865==(x3866);
              if(x3867) {
                double x3868 = x3847._7;
                double x3869 = x3848._7;
                int x3870 = x3868==(x3869);
                if(x3870) {
                  PString x3871 = x3847._8;
                  PString x3872 = x3848._8;
                  int x3873 = x3871==(x3872);
                  if(x3873) {
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
    int x4303 = HASH(x4302);
    int x4304 = -862048943*(x4303);
    int x4305 = x4304<<(15);
    int x4306 = x4304 >> (-15 & (8*sizeof(x4304)-1));
    int x4307 = x4305|(x4306);
    int x4308 = x4307*(461845907);
    int x4309 = x4301;
    int x4310 = x4308^(x4309);
    int x4311 = x4310<<(13);
    int x4312 = x4310 >> (-13 & (8*sizeof(x4310)-1));
    int x4313 = x4311|(x4312);
    int x4314 = x4313*(5);
    int x4315 = x4314+(-430675100);
    x4301 = x4315;
    int x4317 = x4300._2;
    int x4318 = HASH(x4317);
    int x4319 = -862048943*(x4318);
    int x4320 = x4319<<(15);
    int x4321 = x4319 >> (-15 & (8*sizeof(x4319)-1));
    int x4322 = x4320|(x4321);
    int x4323 = x4322*(461845907);
    int x4324 = x4301;
    int x4325 = x4323^(x4324);
    int x4326 = x4325<<(13);
    int x4327 = x4325 >> (-13 & (8*sizeof(x4325)-1));
    int x4328 = x4326|(x4327);
    int x4329 = x4328*(5);
    int x4330 = x4329+(-430675100);
    x4301 = x4330;
    int x4332 = x4300._3;
    int x4333 = HASH(x4332);
    int x4334 = -862048943*(x4333);
    int x4335 = x4334<<(15);
    int x4336 = x4334 >> (-15 & (8*sizeof(x4334)-1));
    int x4337 = x4335|(x4336);
    int x4338 = x4337*(461845907);
    int x4339 = x4301;
    int x4340 = x4338^(x4339);
    int x4341 = x4340<<(13);
    int x4342 = x4340 >> (-13 & (8*sizeof(x4340)-1));
    int x4343 = x4341|(x4342);
    int x4344 = x4343*(5);
    int x4345 = x4344+(-430675100);
    x4301 = x4345;
    int x4347 = x4301;
    int x4348 = x4347^(2);
    int x4349 = x4348 >> (16 & (8*sizeof(x4348)-1));
    int x4350 = x4348^(x4349);
    int x4351 = x4350*(-2048144789);
    int x4352 = x4351 >> (13 & (8*sizeof(x4351)-1));
    int x4353 = x4351^(x4352);
    int x4354 = x4353*(-1028477387);
    int x4355 = x4354 >> (16 & (8*sizeof(x4354)-1));
    int x4356 = x4354^(x4355);
    return x4356; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4358, const struct SEntry10_IIIIIITIDS& x4359) { 
    int x4360 = 0;
    int x4361 = x4358._1;
    int x4362 = x4359._1;
    int x4363 = x4361==(x4362);
    if(x4363) {
      int x4364 = x4358._2;
      int x4365 = x4359._2;
      int x4366 = x4364==(x4365);
      if(x4366) {
        int x4367 = x4358._3;
        int x4368 = x4359._3;
        int x4369 = x4367==(x4368);
        if(x4369) {
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
    int x3650 = HASH(x3649);
    int x3651 = -862048943*(x3650);
    int x3652 = x3651<<(15);
    int x3653 = x3651 >> (-15 & (8*sizeof(x3651)-1));
    int x3654 = x3652|(x3653);
    int x3655 = x3654*(461845907);
    int x3656 = x3648;
    int x3657 = x3655^(x3656);
    int x3658 = x3657<<(13);
    int x3659 = x3657 >> (-13 & (8*sizeof(x3657)-1));
    int x3660 = x3658|(x3659);
    int x3661 = x3660*(5);
    int x3662 = x3661+(-430675100);
    x3648 = x3662;
    int x3664 = x3647._3;
    int x3665 = HASH(x3664);
    int x3666 = -862048943*(x3665);
    int x3667 = x3666<<(15);
    int x3668 = x3666 >> (-15 & (8*sizeof(x3666)-1));
    int x3669 = x3667|(x3668);
    int x3670 = x3669*(461845907);
    int x3671 = x3648;
    int x3672 = x3670^(x3671);
    int x3673 = x3672<<(13);
    int x3674 = x3672 >> (-13 & (8*sizeof(x3672)-1));
    int x3675 = x3673|(x3674);
    int x3676 = x3675*(5);
    int x3677 = x3676+(-430675100);
    x3648 = x3677;
    int x3679 = x3648;
    int x3680 = x3679^(2);
    int x3681 = x3680 >> (16 & (8*sizeof(x3680)-1));
    int x3682 = x3680^(x3681);
    int x3683 = x3682*(-2048144789);
    int x3684 = x3683 >> (13 & (8*sizeof(x3683)-1));
    int x3685 = x3683^(x3684);
    int x3686 = x3685*(-1028477387);
    int x3687 = x3686 >> (16 & (8*sizeof(x3686)-1));
    int x3688 = x3686^(x3687);
    return x3688; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3690, const struct SEntry3_III& x3691) { 
    int x3692 = 0;
    int x3693 = x3690._2;
    int x3694 = x3691._2;
    int x3695 = x3693==(x3694);
    if(x3695) {
      int x3696 = x3690._3;
      int x3697 = x3691._3;
      int x3698 = x3696==(x3697);
      if(x3698) {
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
    int x4415 = HASH(x4414);
    int x4416 = -862048943*(x4415);
    int x4417 = x4416<<(15);
    int x4418 = x4416 >> (-15 & (8*sizeof(x4416)-1));
    int x4419 = x4417|(x4418);
    int x4420 = x4419*(461845907);
    int x4421 = x4413;
    int x4422 = x4420^(x4421);
    int x4423 = x4422<<(13);
    int x4424 = x4422 >> (-13 & (8*sizeof(x4422)-1));
    int x4425 = x4423|(x4424);
    int x4426 = x4425*(5);
    int x4427 = x4426+(-430675100);
    x4413 = x4427;
    int x4429 = x4412._3;
    int x4430 = HASH(x4429);
    int x4431 = -862048943*(x4430);
    int x4432 = x4431<<(15);
    int x4433 = x4431 >> (-15 & (8*sizeof(x4431)-1));
    int x4434 = x4432|(x4433);
    int x4435 = x4434*(461845907);
    int x4436 = x4413;
    int x4437 = x4435^(x4436);
    int x4438 = x4437<<(13);
    int x4439 = x4437 >> (-13 & (8*sizeof(x4437)-1));
    int x4440 = x4438|(x4439);
    int x4441 = x4440*(5);
    int x4442 = x4441+(-430675100);
    x4413 = x4442;
    PString x4444 = x4412._6;
    int x4445 = HASH(x4444);
    int x4446 = -862048943*(x4445);
    int x4447 = x4446<<(15);
    int x4448 = x4446 >> (-15 & (8*sizeof(x4446)-1));
    int x4449 = x4447|(x4448);
    int x4450 = x4449*(461845907);
    int x4451 = x4413;
    int x4452 = x4450^(x4451);
    int x4453 = x4452<<(13);
    int x4454 = x4452 >> (-13 & (8*sizeof(x4452)-1));
    int x4455 = x4453|(x4454);
    int x4456 = x4455*(5);
    int x4457 = x4456+(-430675100);
    x4413 = x4457;
    int x4459 = x4413;
    int x4460 = x4459^(2);
    int x4461 = x4460 >> (16 & (8*sizeof(x4460)-1));
    int x4462 = x4460^(x4461);
    int x4463 = x4462*(-2048144789);
    int x4464 = x4463 >> (13 & (8*sizeof(x4463)-1));
    int x4465 = x4463^(x4464);
    int x4466 = x4465*(-1028477387);
    int x4467 = x4466 >> (16 & (8*sizeof(x4466)-1));
    int x4468 = x4466^(x4467);
    return x4468; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4470, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4471) { 
    int x4472 = 0;
    int x4473 = x4470._2;
    int x4474 = x4471._2;
    int x4475 = x4473==(x4474);
    if(x4475) {
      int x4476 = x4470._3;
      int x4477 = x4471._3;
      int x4478 = x4476==(x4477);
      if(x4478) {
        PString x4479 = x4470._6;
        PString x4480 = x4471._6;
        int x4481 = x4479==(x4480);
        if(x4481) {
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
    int x3943 = HASH(x3942);
    int x3944 = -862048943*(x3943);
    int x3945 = x3944<<(15);
    int x3946 = x3944 >> (-15 & (8*sizeof(x3944)-1));
    int x3947 = x3945|(x3946);
    int x3948 = x3947*(461845907);
    int x3949 = x3941;
    int x3950 = x3948^(x3949);
    int x3951 = x3950<<(13);
    int x3952 = x3950 >> (-13 & (8*sizeof(x3950)-1));
    int x3953 = x3951|(x3952);
    int x3954 = x3953*(5);
    int x3955 = x3954+(-430675100);
    x3941 = x3955;
    int x3957 = x3940._2;
    int x3958 = HASH(x3957);
    int x3959 = -862048943*(x3958);
    int x3960 = x3959<<(15);
    int x3961 = x3959 >> (-15 & (8*sizeof(x3959)-1));
    int x3962 = x3960|(x3961);
    int x3963 = x3962*(461845907);
    int x3964 = x3941;
    int x3965 = x3963^(x3964);
    int x3966 = x3965<<(13);
    int x3967 = x3965 >> (-13 & (8*sizeof(x3965)-1));
    int x3968 = x3966|(x3967);
    int x3969 = x3968*(5);
    int x3970 = x3969+(-430675100);
    x3941 = x3970;
    int x3972 = x3940._3;
    int x3973 = HASH(x3972);
    int x3974 = -862048943*(x3973);
    int x3975 = x3974<<(15);
    int x3976 = x3974 >> (-15 & (8*sizeof(x3974)-1));
    int x3977 = x3975|(x3976);
    int x3978 = x3977*(461845907);
    int x3979 = x3941;
    int x3980 = x3978^(x3979);
    int x3981 = x3980<<(13);
    int x3982 = x3980 >> (-13 & (8*sizeof(x3980)-1));
    int x3983 = x3981|(x3982);
    int x3984 = x3983*(5);
    int x3985 = x3984+(-430675100);
    x3941 = x3985;
    int x3987 = x3941;
    int x3988 = x3987^(2);
    int x3989 = x3988 >> (16 & (8*sizeof(x3988)-1));
    int x3990 = x3988^(x3989);
    int x3991 = x3990*(-2048144789);
    int x3992 = x3991 >> (13 & (8*sizeof(x3991)-1));
    int x3993 = x3991^(x3992);
    int x3994 = x3993*(-1028477387);
    int x3995 = x3994 >> (16 & (8*sizeof(x3994)-1));
    int x3996 = x3994^(x3995);
    return x3996; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3998, const struct SEntry8_IIIITIIB& x3999) { 
    int x4000 = 0;
    int x4001 = x3998._1;
    int x4002 = x3999._1;
    int x4003 = x4001==(x4002);
    if(x4003) {
      int x4004 = x3998._2;
      int x4005 = x3999._2;
      int x4006 = x4004==(x4005);
      if(x4006) {
        int x4007 = x3998._3;
        int x4008 = x3999._3;
        int x4009 = x4007==(x4008);
        if(x4009) {
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
    int x3597 = HASH(x3596);
    int x3598 = -862048943*(x3597);
    int x3599 = x3598<<(15);
    int x3600 = x3598 >> (-15 & (8*sizeof(x3598)-1));
    int x3601 = x3599|(x3600);
    int x3602 = x3601*(461845907);
    int x3603 = x3595;
    int x3604 = x3602^(x3603);
    int x3605 = x3604<<(13);
    int x3606 = x3604 >> (-13 & (8*sizeof(x3604)-1));
    int x3607 = x3605|(x3606);
    int x3608 = x3607*(5);
    int x3609 = x3608+(-430675100);
    x3595 = x3609;
    int x3611 = x3594._3;
    int x3612 = HASH(x3611);
    int x3613 = -862048943*(x3612);
    int x3614 = x3613<<(15);
    int x3615 = x3613 >> (-15 & (8*sizeof(x3613)-1));
    int x3616 = x3614|(x3615);
    int x3617 = x3616*(461845907);
    int x3618 = x3595;
    int x3619 = x3617^(x3618);
    int x3620 = x3619<<(13);
    int x3621 = x3619 >> (-13 & (8*sizeof(x3619)-1));
    int x3622 = x3620|(x3621);
    int x3623 = x3622*(5);
    int x3624 = x3623+(-430675100);
    x3595 = x3624;
    int x3626 = x3595;
    int x3627 = x3626^(2);
    int x3628 = x3627 >> (16 & (8*sizeof(x3627)-1));
    int x3629 = x3627^(x3628);
    int x3630 = x3629*(-2048144789);
    int x3631 = x3630 >> (13 & (8*sizeof(x3630)-1));
    int x3632 = x3630^(x3631);
    int x3633 = x3632*(-1028477387);
    int x3634 = x3633 >> (16 & (8*sizeof(x3633)-1));
    int x3635 = x3633^(x3634);
    return x3635; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3637, const struct SEntry3_III& x3638) { 
    int x3639 = x3637._1;
    int x3640 = x3638._1;
    int x3641 = x3639==(x3640);
    int x3642 = x3639>(x3640);
    int x3643 = x3642 ? 1 : -1;
    int x3644 = x3641 ? 0 : x3643;
    return x3644; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4020)  { 
    int x4021 = -889275714;
    int x4022 = x4020._2;
    int x4023 = HASH(x4022);
    int x4024 = -862048943*(x4023);
    int x4025 = x4024<<(15);
    int x4026 = x4024 >> (-15 & (8*sizeof(x4024)-1));
    int x4027 = x4025|(x4026);
    int x4028 = x4027*(461845907);
    int x4029 = x4021;
    int x4030 = x4028^(x4029);
    int x4031 = x4030<<(13);
    int x4032 = x4030 >> (-13 & (8*sizeof(x4030)-1));
    int x4033 = x4031|(x4032);
    int x4034 = x4033*(5);
    int x4035 = x4034+(-430675100);
    x4021 = x4035;
    int x4037 = x4020._3;
    int x4038 = HASH(x4037);
    int x4039 = -862048943*(x4038);
    int x4040 = x4039<<(15);
    int x4041 = x4039 >> (-15 & (8*sizeof(x4039)-1));
    int x4042 = x4040|(x4041);
    int x4043 = x4042*(461845907);
    int x4044 = x4021;
    int x4045 = x4043^(x4044);
    int x4046 = x4045<<(13);
    int x4047 = x4045 >> (-13 & (8*sizeof(x4045)-1));
    int x4048 = x4046|(x4047);
    int x4049 = x4048*(5);
    int x4050 = x4049+(-430675100);
    x4021 = x4050;
    int x4052 = x4020._4;
    int x4053 = HASH(x4052);
    int x4054 = -862048943*(x4053);
    int x4055 = x4054<<(15);
    int x4056 = x4054 >> (-15 & (8*sizeof(x4054)-1));
    int x4057 = x4055|(x4056);
    int x4058 = x4057*(461845907);
    int x4059 = x4021;
    int x4060 = x4058^(x4059);
    int x4061 = x4060<<(13);
    int x4062 = x4060 >> (-13 & (8*sizeof(x4060)-1));
    int x4063 = x4061|(x4062);
    int x4064 = x4063*(5);
    int x4065 = x4064+(-430675100);
    x4021 = x4065;
    int x4067 = x4021;
    int x4068 = x4067^(2);
    int x4069 = x4068 >> (16 & (8*sizeof(x4068)-1));
    int x4070 = x4068^(x4069);
    int x4071 = x4070*(-2048144789);
    int x4072 = x4071 >> (13 & (8*sizeof(x4071)-1));
    int x4073 = x4071^(x4072);
    int x4074 = x4073*(-1028477387);
    int x4075 = x4074 >> (16 & (8*sizeof(x4074)-1));
    int x4076 = x4074^(x4075);
    return x4076; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4078, const struct SEntry8_IIIITIIB& x4079) { 
    int x4080 = x4078._1;
    int x4081 = x4079._1;
    int x4082 = x4080==(x4081);
    int x4083 = x4080>(x4081);
    int x4084 = x4083 ? 1 : -1;
    int x4085 = x4082 ? 0 : x4084;
    return x4085; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4501)  { 
    int x4502 = 0;
    int x4503 = x4501._1;
    int x4504 = x4503-(1);
    int x4505 = x4502;
    int x4506 = x4505*(100000);
    int x4507 = x4506+(x4504);
    x4502 = x4507;
    int x4509 = x4501._2;
    int x4510 = x4509-(1);
    int x4511 = x4502;
    int x4512 = x4511*(1);
    int x4513 = x4512+(x4510);
    x4502 = x4513;
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
    int x4392 = x4391-(1);
    int x4393 = x4390;
    int x4394 = x4393*(3000);
    int x4395 = x4394+(x4392);
    x4390 = x4395;
    int x4397 = x4389._2;
    int x4398 = x4397-(1);
    int x4399 = x4390;
    int x4400 = x4399*(10);
    int x4401 = x4400+(x4398);
    x4390 = x4401;
    int x4403 = x4389._3;
    int x4404 = x4403-(1);
    int x4405 = x4390;
    int x4406 = x4405*(1);
    int x4407 = x4406+(x4404);
    x4390 = x4407;
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
    int x3924 = x3923-(1);
    int x3925 = x3922;
    int x3926 = x3925*(100000);
    int x3927 = x3926+(x3924);
    x3922 = x3927;
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
    int x3905 = x3904-(1);
    int x3906 = x3903;
    int x3907 = x3906*(1);
    int x3908 = x3907+(x3905);
    x3903 = x3908;
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
    int x4181 = x4180-(1);
    int x4182 = x4179;
    int x4183 = x4182*(10);
    int x4184 = x4183+(x4181);
    x4179 = x4184;
    int x4186 = x4178._2;
    int x4187 = x4186-(1);
    int x4188 = x4179;
    int x4189 = x4188*(1);
    int x4190 = x4189+(x4187);
    x4179 = x4190;
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
