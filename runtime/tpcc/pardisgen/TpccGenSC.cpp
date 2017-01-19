#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
using namespace std;
#include "hpds/pstring.hpp"
#include "hpds/pstringops.hpp"
#include "program_base.hpp"

#define USING_GENERIC_ENTRY false

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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4175)  { 
    int x4176 = -889275714;
    int x4177 = x4175._1;
    int x4178 = HASH(x4177);
    int x4179 = -862048943*(x4178);
    int x4180 = x4179<<(15);
    int x4181 = x4179 >> (-15 & (8*sizeof(x4179)-1));
    int x4182 = x4180|(x4181);
    int x4183 = x4182*(461845907);
    int x4184 = x4176;
    int x4185 = x4183^(x4184);
    int x4186 = x4185<<(13);
    int x4187 = x4185 >> (-13 & (8*sizeof(x4185)-1));
    int x4188 = x4186|(x4187);
    int x4189 = x4188*(5);
    int x4190 = x4189+(-430675100);
    x4176 = x4190;
    int x4192 = x4175._2;
    int x4193 = HASH(x4192);
    int x4194 = -862048943*(x4193);
    int x4195 = x4194<<(15);
    int x4196 = x4194 >> (-15 & (8*sizeof(x4194)-1));
    int x4197 = x4195|(x4196);
    int x4198 = x4197*(461845907);
    int x4199 = x4176;
    int x4200 = x4198^(x4199);
    int x4201 = x4200<<(13);
    int x4202 = x4200 >> (-13 & (8*sizeof(x4200)-1));
    int x4203 = x4201|(x4202);
    int x4204 = x4203*(5);
    int x4205 = x4204+(-430675100);
    x4176 = x4205;
    int x4207 = x4175._3;
    int x4208 = HASH(x4207);
    int x4209 = -862048943*(x4208);
    int x4210 = x4209<<(15);
    int x4211 = x4209 >> (-15 & (8*sizeof(x4209)-1));
    int x4212 = x4210|(x4211);
    int x4213 = x4212*(461845907);
    int x4214 = x4176;
    int x4215 = x4213^(x4214);
    int x4216 = x4215<<(13);
    int x4217 = x4215 >> (-13 & (8*sizeof(x4215)-1));
    int x4218 = x4216|(x4217);
    int x4219 = x4218*(5);
    int x4220 = x4219+(-430675100);
    x4176 = x4220;
    int x4222 = x4175._4;
    int x4223 = HASH(x4222);
    int x4224 = -862048943*(x4223);
    int x4225 = x4224<<(15);
    int x4226 = x4224 >> (-15 & (8*sizeof(x4224)-1));
    int x4227 = x4225|(x4226);
    int x4228 = x4227*(461845907);
    int x4229 = x4176;
    int x4230 = x4228^(x4229);
    int x4231 = x4230<<(13);
    int x4232 = x4230 >> (-13 & (8*sizeof(x4230)-1));
    int x4233 = x4231|(x4232);
    int x4234 = x4233*(5);
    int x4235 = x4234+(-430675100);
    x4176 = x4235;
    int x4237 = x4176;
    int x4238 = x4237^(2);
    int x4239 = x4238 >> (16 & (8*sizeof(x4238)-1));
    int x4240 = x4238^(x4239);
    int x4241 = x4240*(-2048144789);
    int x4242 = x4241 >> (13 & (8*sizeof(x4241)-1));
    int x4243 = x4241^(x4242);
    int x4244 = x4243*(-1028477387);
    int x4245 = x4244 >> (16 & (8*sizeof(x4244)-1));
    int x4246 = x4244^(x4245);
    return x4246; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4248, const struct SEntry10_IIIIIITIDS& x4249) { 
    int x4250 = x4248._1;
    int x4251 = x4249._1;
    int x4252 = x4250==(x4251);
    int ite19355 = 0;
    if(x4252) {
      
      int x4253 = x4248._2;
      int x4254 = x4249._2;
      int x4255 = x4253==(x4254);
      int x19356 = x4255;
      ite19355 = x19356;
    } else {
      
      ite19355 = 0;
    };
    int x19345 = ite19355;
    int ite19364 = 0;
    if(x19345) {
      
      int x4257 = x4248._3;
      int x4258 = x4249._3;
      int x4259 = x4257==(x4258);
      int x19365 = x4259;
      ite19364 = x19365;
    } else {
      
      ite19364 = 0;
    };
    int x19347 = ite19364;
    int ite19373 = 0;
    if(x19347) {
      
      int x4261 = x4248._4;
      int x4262 = x4249._4;
      int x4263 = x4261==(x4262);
      int x19374 = x4263;
      ite19373 = x19374;
    } else {
      
      ite19373 = 0;
    };
    int x19349 = ite19373;
    int x4265 = x19349 ? 0 : 1;
    return x4265; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4069)  { 
    int x4070 = -889275714;
    int x4071 = x4069._2;
    int x4072 = HASH(x4071);
    int x4073 = -862048943*(x4072);
    int x4074 = x4073<<(15);
    int x4075 = x4073 >> (-15 & (8*sizeof(x4073)-1));
    int x4076 = x4074|(x4075);
    int x4077 = x4076*(461845907);
    int x4078 = x4070;
    int x4079 = x4077^(x4078);
    int x4080 = x4079<<(13);
    int x4081 = x4079 >> (-13 & (8*sizeof(x4079)-1));
    int x4082 = x4080|(x4081);
    int x4083 = x4082*(5);
    int x4084 = x4083+(-430675100);
    x4070 = x4084;
    int x4086 = x4069._3;
    int x4087 = HASH(x4086);
    int x4088 = -862048943*(x4087);
    int x4089 = x4088<<(15);
    int x4090 = x4088 >> (-15 & (8*sizeof(x4088)-1));
    int x4091 = x4089|(x4090);
    int x4092 = x4091*(461845907);
    int x4093 = x4070;
    int x4094 = x4092^(x4093);
    int x4095 = x4094<<(13);
    int x4096 = x4094 >> (-13 & (8*sizeof(x4094)-1));
    int x4097 = x4095|(x4096);
    int x4098 = x4097*(5);
    int x4099 = x4098+(-430675100);
    x4070 = x4099;
    int x4101 = x4069._4;
    int x4102 = HASH(x4101);
    int x4103 = -862048943*(x4102);
    int x4104 = x4103<<(15);
    int x4105 = x4103 >> (-15 & (8*sizeof(x4103)-1));
    int x4106 = x4104|(x4105);
    int x4107 = x4106*(461845907);
    int x4108 = x4070;
    int x4109 = x4107^(x4108);
    int x4110 = x4109<<(13);
    int x4111 = x4109 >> (-13 & (8*sizeof(x4109)-1));
    int x4112 = x4110|(x4111);
    int x4113 = x4112*(5);
    int x4114 = x4113+(-430675100);
    x4070 = x4114;
    int x4116 = x4070;
    int x4117 = x4116^(2);
    int x4118 = x4117 >> (16 & (8*sizeof(x4117)-1));
    int x4119 = x4117^(x4118);
    int x4120 = x4119*(-2048144789);
    int x4121 = x4120 >> (13 & (8*sizeof(x4120)-1));
    int x4122 = x4120^(x4121);
    int x4123 = x4122*(-1028477387);
    int x4124 = x4123 >> (16 & (8*sizeof(x4123)-1));
    int x4125 = x4123^(x4124);
    return x4125; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4127, const struct SEntry8_IIIITIIB& x4128) { 
    int x4129 = x4127._2;
    int x4130 = x4128._2;
    int x4131 = x4129==(x4130);
    int ite19481 = 0;
    if(x4131) {
      
      int x4132 = x4127._3;
      int x4133 = x4128._3;
      int x4134 = x4132==(x4133);
      int x19482 = x4134;
      ite19481 = x19482;
    } else {
      
      ite19481 = 0;
    };
    int x19473 = ite19481;
    int ite19490 = 0;
    if(x19473) {
      
      int x4136 = x4127._4;
      int x4137 = x4128._4;
      int x4138 = x4136==(x4137);
      int x19491 = x4138;
      ite19490 = x19491;
    } else {
      
      ite19490 = 0;
    };
    int x19475 = ite19490;
    int x4140 = x19475 ? 0 : 1;
    return x4140; 
  }
};
 struct SEntry3_III_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3523)  { 
    int x3524 = -889275714;
    int x3525 = x3523._1;
    int x3526 = HASH(x3525);
    int x3527 = -862048943*(x3526);
    int x3528 = x3527<<(15);
    int x3529 = x3527 >> (-15 & (8*sizeof(x3527)-1));
    int x3530 = x3528|(x3529);
    int x3531 = x3530*(461845907);
    int x3532 = x3524;
    int x3533 = x3531^(x3532);
    int x3534 = x3533<<(13);
    int x3535 = x3533 >> (-13 & (8*sizeof(x3533)-1));
    int x3536 = x3534|(x3535);
    int x3537 = x3536*(5);
    int x3538 = x3537+(-430675100);
    x3524 = x3538;
    int x3540 = x3523._2;
    int x3541 = HASH(x3540);
    int x3542 = -862048943*(x3541);
    int x3543 = x3542<<(15);
    int x3544 = x3542 >> (-15 & (8*sizeof(x3542)-1));
    int x3545 = x3543|(x3544);
    int x3546 = x3545*(461845907);
    int x3547 = x3524;
    int x3548 = x3546^(x3547);
    int x3549 = x3548<<(13);
    int x3550 = x3548 >> (-13 & (8*sizeof(x3548)-1));
    int x3551 = x3549|(x3550);
    int x3552 = x3551*(5);
    int x3553 = x3552+(-430675100);
    x3524 = x3553;
    int x3555 = x3523._3;
    int x3556 = HASH(x3555);
    int x3557 = -862048943*(x3556);
    int x3558 = x3557<<(15);
    int x3559 = x3557 >> (-15 & (8*sizeof(x3557)-1));
    int x3560 = x3558|(x3559);
    int x3561 = x3560*(461845907);
    int x3562 = x3524;
    int x3563 = x3561^(x3562);
    int x3564 = x3563<<(13);
    int x3565 = x3563 >> (-13 & (8*sizeof(x3563)-1));
    int x3566 = x3564|(x3565);
    int x3567 = x3566*(5);
    int x3568 = x3567+(-430675100);
    x3524 = x3568;
    int x3570 = x3524;
    int x3571 = x3570^(2);
    int x3572 = x3571 >> (16 & (8*sizeof(x3571)-1));
    int x3573 = x3571^(x3572);
    int x3574 = x3573*(-2048144789);
    int x3575 = x3574 >> (13 & (8*sizeof(x3574)-1));
    int x3576 = x3574^(x3575);
    int x3577 = x3576*(-1028477387);
    int x3578 = x3577 >> (16 & (8*sizeof(x3577)-1));
    int x3579 = x3577^(x3578);
    return x3579; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3581, const struct SEntry3_III& x3582) { 
    int x3583 = x3581._1;
    int x3584 = x3582._1;
    int x3585 = x3583==(x3584);
    int ite19589 = 0;
    if(x3585) {
      
      int x3586 = x3581._2;
      int x3587 = x3582._2;
      int x3588 = x3586==(x3587);
      int x19590 = x3588;
      ite19589 = x19590;
    } else {
      
      ite19589 = 0;
    };
    int x19581 = ite19589;
    int ite19598 = 0;
    if(x19581) {
      
      int x3590 = x3581._3;
      int x3591 = x3582._3;
      int x3592 = x3590==(x3591);
      int x19599 = x3592;
      ite19598 = x19599;
    } else {
      
      ite19598 = 0;
    };
    int x19583 = ite19598;
    int x3594 = x19583 ? 0 : 1;
    return x3594; 
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3712)  { 
    int x3713 = -889275714;
    int x3714 = x3712._1;
    int x3715 = HASH(x3714);
    int x3716 = -862048943*(x3715);
    int x3717 = x3716<<(15);
    int x3718 = x3716 >> (-15 & (8*sizeof(x3716)-1));
    int x3719 = x3717|(x3718);
    int x3720 = x3719*(461845907);
    int x3721 = x3713;
    int x3722 = x3720^(x3721);
    int x3723 = x3722<<(13);
    int x3724 = x3722 >> (-13 & (8*sizeof(x3722)-1));
    int x3725 = x3723|(x3724);
    int x3726 = x3725*(5);
    int x3727 = x3726+(-430675100);
    x3713 = x3727;
    int x3729 = x3712._2;
    int x3730 = HASH(x3729);
    int x3731 = -862048943*(x3730);
    int x3732 = x3731<<(15);
    int x3733 = x3731 >> (-15 & (8*sizeof(x3731)-1));
    int x3734 = x3732|(x3733);
    int x3735 = x3734*(461845907);
    int x3736 = x3713;
    int x3737 = x3735^(x3736);
    int x3738 = x3737<<(13);
    int x3739 = x3737 >> (-13 & (8*sizeof(x3737)-1));
    int x3740 = x3738|(x3739);
    int x3741 = x3740*(5);
    int x3742 = x3741+(-430675100);
    x3713 = x3742;
    int x3744 = x3712._3;
    int x3745 = HASH(x3744);
    int x3746 = -862048943*(x3745);
    int x3747 = x3746<<(15);
    int x3748 = x3746 >> (-15 & (8*sizeof(x3746)-1));
    int x3749 = x3747|(x3748);
    int x3750 = x3749*(461845907);
    int x3751 = x3713;
    int x3752 = x3750^(x3751);
    int x3753 = x3752<<(13);
    int x3754 = x3752 >> (-13 & (8*sizeof(x3752)-1));
    int x3755 = x3753|(x3754);
    int x3756 = x3755*(5);
    int x3757 = x3756+(-430675100);
    x3713 = x3757;
    int x3759 = x3712._4;
    int x3760 = HASH(x3759);
    int x3761 = -862048943*(x3760);
    int x3762 = x3761<<(15);
    int x3763 = x3761 >> (-15 & (8*sizeof(x3761)-1));
    int x3764 = x3762|(x3763);
    int x3765 = x3764*(461845907);
    int x3766 = x3713;
    int x3767 = x3765^(x3766);
    int x3768 = x3767<<(13);
    int x3769 = x3767 >> (-13 & (8*sizeof(x3767)-1));
    int x3770 = x3768|(x3769);
    int x3771 = x3770*(5);
    int x3772 = x3771+(-430675100);
    x3713 = x3772;
    int x3774 = x3712._5;
    int x3775 = HASH(x3774);
    int x3776 = -862048943*(x3775);
    int x3777 = x3776<<(15);
    int x3778 = x3776 >> (-15 & (8*sizeof(x3776)-1));
    int x3779 = x3777|(x3778);
    int x3780 = x3779*(461845907);
    int x3781 = x3713;
    int x3782 = x3780^(x3781);
    int x3783 = x3782<<(13);
    int x3784 = x3782 >> (-13 & (8*sizeof(x3782)-1));
    int x3785 = x3783|(x3784);
    int x3786 = x3785*(5);
    int x3787 = x3786+(-430675100);
    x3713 = x3787;
    date x3789 = x3712._6;
    int x3790 = HASH(x3789);
    int x3791 = -862048943*(x3790);
    int x3792 = x3791<<(15);
    int x3793 = x3791 >> (-15 & (8*sizeof(x3791)-1));
    int x3794 = x3792|(x3793);
    int x3795 = x3794*(461845907);
    int x3796 = x3713;
    int x3797 = x3795^(x3796);
    int x3798 = x3797<<(13);
    int x3799 = x3797 >> (-13 & (8*sizeof(x3797)-1));
    int x3800 = x3798|(x3799);
    int x3801 = x3800*(5);
    int x3802 = x3801+(-430675100);
    x3713 = x3802;
    double x3804 = x3712._7;
    int x3805 = HASH(x3804);
    int x3806 = -862048943*(x3805);
    int x3807 = x3806<<(15);
    int x3808 = x3806 >> (-15 & (8*sizeof(x3806)-1));
    int x3809 = x3807|(x3808);
    int x3810 = x3809*(461845907);
    int x3811 = x3713;
    int x3812 = x3810^(x3811);
    int x3813 = x3812<<(13);
    int x3814 = x3812 >> (-13 & (8*sizeof(x3812)-1));
    int x3815 = x3813|(x3814);
    int x3816 = x3815*(5);
    int x3817 = x3816+(-430675100);
    x3713 = x3817;
    PString x3819 = x3712._8;
    int x3820 = HASH(x3819);
    int x3821 = -862048943*(x3820);
    int x3822 = x3821<<(15);
    int x3823 = x3821 >> (-15 & (8*sizeof(x3821)-1));
    int x3824 = x3822|(x3823);
    int x3825 = x3824*(461845907);
    int x3826 = x3713;
    int x3827 = x3825^(x3826);
    int x3828 = x3827<<(13);
    int x3829 = x3827 >> (-13 & (8*sizeof(x3827)-1));
    int x3830 = x3828|(x3829);
    int x3831 = x3830*(5);
    int x3832 = x3831+(-430675100);
    x3713 = x3832;
    int x3834 = x3713;
    int x3835 = x3834^(2);
    int x3836 = x3835 >> (16 & (8*sizeof(x3835)-1));
    int x3837 = x3835^(x3836);
    int x3838 = x3837*(-2048144789);
    int x3839 = x3838 >> (13 & (8*sizeof(x3838)-1));
    int x3840 = x3838^(x3839);
    int x3841 = x3840*(-1028477387);
    int x3842 = x3841 >> (16 & (8*sizeof(x3841)-1));
    int x3843 = x3841^(x3842);
    return x3843; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3845, const struct SEntry8_IIIIITDS& x3846) { 
    int x3847 = x3845._1;
    int x3848 = x3846._1;
    int x3849 = x3847==(x3848);
    int ite19782 = 0;
    if(x3849) {
      
      int x3850 = x3845._2;
      int x3851 = x3846._2;
      int x3852 = x3850==(x3851);
      int x19783 = x3852;
      ite19782 = x19783;
    } else {
      
      ite19782 = 0;
    };
    int x19764 = ite19782;
    int ite19791 = 0;
    if(x19764) {
      
      int x3854 = x3845._3;
      int x3855 = x3846._3;
      int x3856 = x3854==(x3855);
      int x19792 = x3856;
      ite19791 = x19792;
    } else {
      
      ite19791 = 0;
    };
    int x19766 = ite19791;
    int ite19800 = 0;
    if(x19766) {
      
      int x3858 = x3845._4;
      int x3859 = x3846._4;
      int x3860 = x3858==(x3859);
      int x19801 = x3860;
      ite19800 = x19801;
    } else {
      
      ite19800 = 0;
    };
    int x19768 = ite19800;
    int ite19809 = 0;
    if(x19768) {
      
      int x3862 = x3845._5;
      int x3863 = x3846._5;
      int x3864 = x3862==(x3863);
      int x19810 = x3864;
      ite19809 = x19810;
    } else {
      
      ite19809 = 0;
    };
    int x19770 = ite19809;
    int ite19818 = 0;
    if(x19770) {
      
      date x3866 = x3845._6;
      date x3867 = x3846._6;
      int x3868 = x3866==(x3867);
      int x19819 = x3868;
      ite19818 = x19819;
    } else {
      
      ite19818 = 0;
    };
    int x19772 = ite19818;
    int ite19827 = 0;
    if(x19772) {
      
      double x3870 = x3845._7;
      double x3871 = x3846._7;
      int x3872 = x3870==(x3871);
      int x19828 = x3872;
      ite19827 = x19828;
    } else {
      
      ite19827 = 0;
    };
    int x19774 = ite19827;
    int ite19836 = 0;
    if(x19774) {
      
      PString x3874 = x3845._8;
      PString x3875 = x3846._8;
      int x3876 = x3874==(x3875);
      int x19837 = x3876;
      ite19836 = x19837;
    } else {
      
      ite19836 = 0;
    };
    int x19776 = ite19836;
    int x3878 = x19776 ? 0 : 1;
    return x3878; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4268)  { 
    int x4269 = -889275714;
    int x4270 = x4268._1;
    int x4271 = HASH(x4270);
    int x4272 = -862048943*(x4271);
    int x4273 = x4272<<(15);
    int x4274 = x4272 >> (-15 & (8*sizeof(x4272)-1));
    int x4275 = x4273|(x4274);
    int x4276 = x4275*(461845907);
    int x4277 = x4269;
    int x4278 = x4276^(x4277);
    int x4279 = x4278<<(13);
    int x4280 = x4278 >> (-13 & (8*sizeof(x4278)-1));
    int x4281 = x4279|(x4280);
    int x4282 = x4281*(5);
    int x4283 = x4282+(-430675100);
    x4269 = x4283;
    int x4285 = x4268._2;
    int x4286 = HASH(x4285);
    int x4287 = -862048943*(x4286);
    int x4288 = x4287<<(15);
    int x4289 = x4287 >> (-15 & (8*sizeof(x4287)-1));
    int x4290 = x4288|(x4289);
    int x4291 = x4290*(461845907);
    int x4292 = x4269;
    int x4293 = x4291^(x4292);
    int x4294 = x4293<<(13);
    int x4295 = x4293 >> (-13 & (8*sizeof(x4293)-1));
    int x4296 = x4294|(x4295);
    int x4297 = x4296*(5);
    int x4298 = x4297+(-430675100);
    x4269 = x4298;
    int x4300 = x4268._3;
    int x4301 = HASH(x4300);
    int x4302 = -862048943*(x4301);
    int x4303 = x4302<<(15);
    int x4304 = x4302 >> (-15 & (8*sizeof(x4302)-1));
    int x4305 = x4303|(x4304);
    int x4306 = x4305*(461845907);
    int x4307 = x4269;
    int x4308 = x4306^(x4307);
    int x4309 = x4308<<(13);
    int x4310 = x4308 >> (-13 & (8*sizeof(x4308)-1));
    int x4311 = x4309|(x4310);
    int x4312 = x4311*(5);
    int x4313 = x4312+(-430675100);
    x4269 = x4313;
    int x4315 = x4269;
    int x4316 = x4315^(2);
    int x4317 = x4316 >> (16 & (8*sizeof(x4316)-1));
    int x4318 = x4316^(x4317);
    int x4319 = x4318*(-2048144789);
    int x4320 = x4319 >> (13 & (8*sizeof(x4319)-1));
    int x4321 = x4319^(x4320);
    int x4322 = x4321*(-1028477387);
    int x4323 = x4322 >> (16 & (8*sizeof(x4322)-1));
    int x4324 = x4322^(x4323);
    return x4324; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4326, const struct SEntry10_IIIIIITIDS& x4327) { 
    int x4328 = x4326._1;
    int x4329 = x4327._1;
    int x4330 = x4328==(x4329);
    int ite19980 = 0;
    if(x4330) {
      
      int x4331 = x4326._2;
      int x4332 = x4327._2;
      int x4333 = x4331==(x4332);
      int x19981 = x4333;
      ite19980 = x19981;
    } else {
      
      ite19980 = 0;
    };
    int x19972 = ite19980;
    int ite19989 = 0;
    if(x19972) {
      
      int x4335 = x4326._3;
      int x4336 = x4327._3;
      int x4337 = x4335==(x4336);
      int x19990 = x4337;
      ite19989 = x19990;
    } else {
      
      ite19989 = 0;
    };
    int x19974 = ite19989;
    int x4339 = x19974 ? 0 : 1;
    return x4339; 
  }
};
 struct SEntry3_III_Idx23 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3650)  { 
    int x3651 = -889275714;
    int x3652 = x3650._2;
    int x3653 = HASH(x3652);
    int x3654 = -862048943*(x3653);
    int x3655 = x3654<<(15);
    int x3656 = x3654 >> (-15 & (8*sizeof(x3654)-1));
    int x3657 = x3655|(x3656);
    int x3658 = x3657*(461845907);
    int x3659 = x3651;
    int x3660 = x3658^(x3659);
    int x3661 = x3660<<(13);
    int x3662 = x3660 >> (-13 & (8*sizeof(x3660)-1));
    int x3663 = x3661|(x3662);
    int x3664 = x3663*(5);
    int x3665 = x3664+(-430675100);
    x3651 = x3665;
    int x3667 = x3650._3;
    int x3668 = HASH(x3667);
    int x3669 = -862048943*(x3668);
    int x3670 = x3669<<(15);
    int x3671 = x3669 >> (-15 & (8*sizeof(x3669)-1));
    int x3672 = x3670|(x3671);
    int x3673 = x3672*(461845907);
    int x3674 = x3651;
    int x3675 = x3673^(x3674);
    int x3676 = x3675<<(13);
    int x3677 = x3675 >> (-13 & (8*sizeof(x3675)-1));
    int x3678 = x3676|(x3677);
    int x3679 = x3678*(5);
    int x3680 = x3679+(-430675100);
    x3651 = x3680;
    int x3682 = x3651;
    int x3683 = x3682^(2);
    int x3684 = x3683 >> (16 & (8*sizeof(x3683)-1));
    int x3685 = x3683^(x3684);
    int x3686 = x3685*(-2048144789);
    int x3687 = x3686 >> (13 & (8*sizeof(x3686)-1));
    int x3688 = x3686^(x3687);
    int x3689 = x3688*(-1028477387);
    int x3690 = x3689 >> (16 & (8*sizeof(x3689)-1));
    int x3691 = x3689^(x3690);
    return x3691; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3693, const struct SEntry3_III& x3694) { 
    int x3695 = x3693._2;
    int x3696 = x3694._2;
    int x3697 = x3695==(x3696);
    int ite20071 = 0;
    if(x3697) {
      
      int x3698 = x3693._3;
      int x3699 = x3694._3;
      int x3700 = x3698==(x3699);
      int x20072 = x3700;
      ite20071 = x20072;
    } else {
      
      ite20071 = 0;
    };
    int x20065 = ite20071;
    int x3702 = x20065 ? 0 : 1;
    return x3702; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4374)  { 
    int x4375 = -889275714;
    int x4376 = x4374._2;
    int x4377 = HASH(x4376);
    int x4378 = -862048943*(x4377);
    int x4379 = x4378<<(15);
    int x4380 = x4378 >> (-15 & (8*sizeof(x4378)-1));
    int x4381 = x4379|(x4380);
    int x4382 = x4381*(461845907);
    int x4383 = x4375;
    int x4384 = x4382^(x4383);
    int x4385 = x4384<<(13);
    int x4386 = x4384 >> (-13 & (8*sizeof(x4384)-1));
    int x4387 = x4385|(x4386);
    int x4388 = x4387*(5);
    int x4389 = x4388+(-430675100);
    x4375 = x4389;
    int x4391 = x4374._3;
    int x4392 = HASH(x4391);
    int x4393 = -862048943*(x4392);
    int x4394 = x4393<<(15);
    int x4395 = x4393 >> (-15 & (8*sizeof(x4393)-1));
    int x4396 = x4394|(x4395);
    int x4397 = x4396*(461845907);
    int x4398 = x4375;
    int x4399 = x4397^(x4398);
    int x4400 = x4399<<(13);
    int x4401 = x4399 >> (-13 & (8*sizeof(x4399)-1));
    int x4402 = x4400|(x4401);
    int x4403 = x4402*(5);
    int x4404 = x4403+(-430675100);
    x4375 = x4404;
    PString x4406 = x4374._6;
    int x4407 = HASH(x4406);
    int x4408 = -862048943*(x4407);
    int x4409 = x4408<<(15);
    int x4410 = x4408 >> (-15 & (8*sizeof(x4408)-1));
    int x4411 = x4409|(x4410);
    int x4412 = x4411*(461845907);
    int x4413 = x4375;
    int x4414 = x4412^(x4413);
    int x4415 = x4414<<(13);
    int x4416 = x4414 >> (-13 & (8*sizeof(x4414)-1));
    int x4417 = x4415|(x4416);
    int x4418 = x4417*(5);
    int x4419 = x4418+(-430675100);
    x4375 = x4419;
    int x4421 = x4375;
    int x4422 = x4421^(2);
    int x4423 = x4422 >> (16 & (8*sizeof(x4422)-1));
    int x4424 = x4422^(x4423);
    int x4425 = x4424*(-2048144789);
    int x4426 = x4425 >> (13 & (8*sizeof(x4425)-1));
    int x4427 = x4425^(x4426);
    int x4428 = x4427*(-1028477387);
    int x4429 = x4428 >> (16 & (8*sizeof(x4428)-1));
    int x4430 = x4428^(x4429);
    return x4430; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4432, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4433) { 
    int x4434 = x4432._2;
    int x4435 = x4433._2;
    int x4436 = x4434==(x4435);
    int ite20161 = 0;
    if(x4436) {
      
      int x4437 = x4432._3;
      int x4438 = x4433._3;
      int x4439 = x4437==(x4438);
      int x20162 = x4439;
      ite20161 = x20162;
    } else {
      
      ite20161 = 0;
    };
    int x20153 = ite20161;
    int ite20170 = 0;
    if(x20153) {
      
      PString x4441 = x4432._6;
      PString x4442 = x4433._6;
      int x4443 = x4441==(x4442);
      int x20171 = x4443;
      ite20170 = x20171;
    } else {
      
      ite20170 = 0;
    };
    int x20155 = ite20170;
    int x4445 = x20155 ? 0 : 1;
    return x4445; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3927)  { 
    int x3928 = -889275714;
    int x3929 = x3927._1;
    int x3930 = HASH(x3929);
    int x3931 = -862048943*(x3930);
    int x3932 = x3931<<(15);
    int x3933 = x3931 >> (-15 & (8*sizeof(x3931)-1));
    int x3934 = x3932|(x3933);
    int x3935 = x3934*(461845907);
    int x3936 = x3928;
    int x3937 = x3935^(x3936);
    int x3938 = x3937<<(13);
    int x3939 = x3937 >> (-13 & (8*sizeof(x3937)-1));
    int x3940 = x3938|(x3939);
    int x3941 = x3940*(5);
    int x3942 = x3941+(-430675100);
    x3928 = x3942;
    int x3944 = x3927._2;
    int x3945 = HASH(x3944);
    int x3946 = -862048943*(x3945);
    int x3947 = x3946<<(15);
    int x3948 = x3946 >> (-15 & (8*sizeof(x3946)-1));
    int x3949 = x3947|(x3948);
    int x3950 = x3949*(461845907);
    int x3951 = x3928;
    int x3952 = x3950^(x3951);
    int x3953 = x3952<<(13);
    int x3954 = x3952 >> (-13 & (8*sizeof(x3952)-1));
    int x3955 = x3953|(x3954);
    int x3956 = x3955*(5);
    int x3957 = x3956+(-430675100);
    x3928 = x3957;
    int x3959 = x3927._3;
    int x3960 = HASH(x3959);
    int x3961 = -862048943*(x3960);
    int x3962 = x3961<<(15);
    int x3963 = x3961 >> (-15 & (8*sizeof(x3961)-1));
    int x3964 = x3962|(x3963);
    int x3965 = x3964*(461845907);
    int x3966 = x3928;
    int x3967 = x3965^(x3966);
    int x3968 = x3967<<(13);
    int x3969 = x3967 >> (-13 & (8*sizeof(x3967)-1));
    int x3970 = x3968|(x3969);
    int x3971 = x3970*(5);
    int x3972 = x3971+(-430675100);
    x3928 = x3972;
    int x3974 = x3928;
    int x3975 = x3974^(2);
    int x3976 = x3975 >> (16 & (8*sizeof(x3975)-1));
    int x3977 = x3975^(x3976);
    int x3978 = x3977*(-2048144789);
    int x3979 = x3978 >> (13 & (8*sizeof(x3978)-1));
    int x3980 = x3978^(x3979);
    int x3981 = x3980*(-1028477387);
    int x3982 = x3981 >> (16 & (8*sizeof(x3981)-1));
    int x3983 = x3981^(x3982);
    return x3983; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3985, const struct SEntry8_IIIITIIB& x3986) { 
    int x3987 = x3985._1;
    int x3988 = x3986._1;
    int x3989 = x3987==(x3988);
    int ite20269 = 0;
    if(x3989) {
      
      int x3990 = x3985._2;
      int x3991 = x3986._2;
      int x3992 = x3990==(x3991);
      int x20270 = x3992;
      ite20269 = x20270;
    } else {
      
      ite20269 = 0;
    };
    int x20261 = ite20269;
    int ite20278 = 0;
    if(x20261) {
      
      int x3994 = x3985._3;
      int x3995 = x3986._3;
      int x3996 = x3994==(x3995);
      int x20279 = x3996;
      ite20278 = x20279;
    } else {
      
      ite20278 = 0;
    };
    int x20263 = ite20278;
    int x3998 = x20263 ? 0 : 1;
    return x3998; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3597)  { 
    int x3598 = -889275714;
    int x3599 = x3597._2;
    int x3600 = HASH(x3599);
    int x3601 = -862048943*(x3600);
    int x3602 = x3601<<(15);
    int x3603 = x3601 >> (-15 & (8*sizeof(x3601)-1));
    int x3604 = x3602|(x3603);
    int x3605 = x3604*(461845907);
    int x3606 = x3598;
    int x3607 = x3605^(x3606);
    int x3608 = x3607<<(13);
    int x3609 = x3607 >> (-13 & (8*sizeof(x3607)-1));
    int x3610 = x3608|(x3609);
    int x3611 = x3610*(5);
    int x3612 = x3611+(-430675100);
    x3598 = x3612;
    int x3614 = x3597._3;
    int x3615 = HASH(x3614);
    int x3616 = -862048943*(x3615);
    int x3617 = x3616<<(15);
    int x3618 = x3616 >> (-15 & (8*sizeof(x3616)-1));
    int x3619 = x3617|(x3618);
    int x3620 = x3619*(461845907);
    int x3621 = x3598;
    int x3622 = x3620^(x3621);
    int x3623 = x3622<<(13);
    int x3624 = x3622 >> (-13 & (8*sizeof(x3622)-1));
    int x3625 = x3623|(x3624);
    int x3626 = x3625*(5);
    int x3627 = x3626+(-430675100);
    x3598 = x3627;
    int x3629 = x3598;
    int x3630 = x3629^(2);
    int x3631 = x3630 >> (16 & (8*sizeof(x3630)-1));
    int x3632 = x3630^(x3631);
    int x3633 = x3632*(-2048144789);
    int x3634 = x3633 >> (13 & (8*sizeof(x3633)-1));
    int x3635 = x3633^(x3634);
    int x3636 = x3635*(-1028477387);
    int x3637 = x3636 >> (16 & (8*sizeof(x3636)-1));
    int x3638 = x3636^(x3637);
    return x3638; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3640, const struct SEntry3_III& x3641) { 
    int x3642 = x3640._1;
    int x3643 = x3641._1;
    int x3644 = x3642==(x3643);
    int x3645 = x3642>(x3643);
    int x3646 = x3645 ? 1 : -1;
    int x3647 = x3644 ? 0 : x3646;
    return x3647; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4001)  { 
    int x4002 = -889275714;
    int x4003 = x4001._2;
    int x4004 = HASH(x4003);
    int x4005 = -862048943*(x4004);
    int x4006 = x4005<<(15);
    int x4007 = x4005 >> (-15 & (8*sizeof(x4005)-1));
    int x4008 = x4006|(x4007);
    int x4009 = x4008*(461845907);
    int x4010 = x4002;
    int x4011 = x4009^(x4010);
    int x4012 = x4011<<(13);
    int x4013 = x4011 >> (-13 & (8*sizeof(x4011)-1));
    int x4014 = x4012|(x4013);
    int x4015 = x4014*(5);
    int x4016 = x4015+(-430675100);
    x4002 = x4016;
    int x4018 = x4001._3;
    int x4019 = HASH(x4018);
    int x4020 = -862048943*(x4019);
    int x4021 = x4020<<(15);
    int x4022 = x4020 >> (-15 & (8*sizeof(x4020)-1));
    int x4023 = x4021|(x4022);
    int x4024 = x4023*(461845907);
    int x4025 = x4002;
    int x4026 = x4024^(x4025);
    int x4027 = x4026<<(13);
    int x4028 = x4026 >> (-13 & (8*sizeof(x4026)-1));
    int x4029 = x4027|(x4028);
    int x4030 = x4029*(5);
    int x4031 = x4030+(-430675100);
    x4002 = x4031;
    int x4033 = x4001._4;
    int x4034 = HASH(x4033);
    int x4035 = -862048943*(x4034);
    int x4036 = x4035<<(15);
    int x4037 = x4035 >> (-15 & (8*sizeof(x4035)-1));
    int x4038 = x4036|(x4037);
    int x4039 = x4038*(461845907);
    int x4040 = x4002;
    int x4041 = x4039^(x4040);
    int x4042 = x4041<<(13);
    int x4043 = x4041 >> (-13 & (8*sizeof(x4041)-1));
    int x4044 = x4042|(x4043);
    int x4045 = x4044*(5);
    int x4046 = x4045+(-430675100);
    x4002 = x4046;
    int x4048 = x4002;
    int x4049 = x4048^(2);
    int x4050 = x4049 >> (16 & (8*sizeof(x4049)-1));
    int x4051 = x4049^(x4050);
    int x4052 = x4051*(-2048144789);
    int x4053 = x4052 >> (13 & (8*sizeof(x4052)-1));
    int x4054 = x4052^(x4053);
    int x4055 = x4054*(-1028477387);
    int x4056 = x4055 >> (16 & (8*sizeof(x4055)-1));
    int x4057 = x4055^(x4056);
    return x4057; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4059, const struct SEntry8_IIIITIIB& x4060) { 
    int x4061 = x4059._1;
    int x4062 = x4060._1;
    int x4063 = x4061==(x4062);
    int x4064 = x4061>(x4062);
    int x4065 = x4064 ? 1 : -1;
    int x4066 = x4063 ? 0 : x4065;
    return x4066; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4457)  { 
    int x4458 = 0;
    int x4459 = x4457._1;
    int x4460 = x4459-(1);
    int x4461 = x4458;
    int x4462 = x4461*(100000);
    int x4463 = x4462+(x4460);
    x4458 = x4463;
    int x4465 = x4457._2;
    int x4466 = x4465-(1);
    int x4467 = x4458;
    int x4468 = x4467*(1);
    int x4469 = x4468+(x4466);
    x4458 = x4469;
    int x4471 = x4458;
    return x4471; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4454, const struct SEntry17_IIISSSSSSSSSSIIIS& x4455) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4351)  { 
    int x4352 = 0;
    int x4353 = x4351._1;
    int x4354 = x4353-(1);
    int x4355 = x4352;
    int x4356 = x4355*(3000);
    int x4357 = x4356+(x4354);
    x4352 = x4357;
    int x4359 = x4351._2;
    int x4360 = x4359-(1);
    int x4361 = x4352;
    int x4362 = x4361*(10);
    int x4363 = x4362+(x4360);
    x4352 = x4363;
    int x4365 = x4351._3;
    int x4366 = x4365-(1);
    int x4367 = x4352;
    int x4368 = x4367*(1);
    int x4369 = x4368+(x4366);
    x4352 = x4369;
    int x4371 = x4352;
    return x4371; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4348, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4349) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3908)  { 
    int x3909 = 0;
    int x3910 = x3908._1;
    int x3911 = x3910-(1);
    int x3912 = x3909;
    int x3913 = x3912*(100000);
    int x3914 = x3913+(x3911);
    x3909 = x3914;
    int x3916 = x3909;
    return x3916; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3905, const struct SEntry5_IISDS& x3906) { 
    return 0; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3889)  { 
    int x3890 = 0;
    int x3891 = x3889._1;
    int x3892 = x3891-(1);
    int x3893 = x3890;
    int x3894 = x3893*(1);
    int x3895 = x3894+(x3892);
    x3890 = x3895;
    int x3897 = x3890;
    return x3897; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3886, const struct SEntry9_ISSSSSSDD& x3887) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4153)  { 
    int x4154 = 0;
    int x4155 = x4153._1;
    int x4156 = x4155-(1);
    int x4157 = x4154;
    int x4158 = x4157*(10);
    int x4159 = x4158+(x4156);
    x4154 = x4159;
    int x4161 = x4153._2;
    int x4162 = x4161-(1);
    int x4163 = x4154;
    int x4164 = x4163*(1);
    int x4165 = x4164+(x4162);
    x4154 = x4165;
    int x4167 = x4154;
    return x4167; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4150, const struct SEntry11_IISSSSSSDDI& x4151) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x3708 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x3709 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx12345678, 1>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x3884 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x3903 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x3922 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x4146 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x4147 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x4173 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x4345 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x4346 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x4451 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x4452 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x4477 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7382;
struct SEntry8_IIIITIIB x7573;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7600;
struct SEntry8_IIIITIIB x7938;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7750;
struct SEntry3_III x7358;
struct SEntry11_IISSSSSSDDI x7495;
struct SEntry11_IISSSSSSDDI x7931;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7733;
struct SEntry10_IIIIIITIDS x8028;
struct SEntry11_IISSSSSSDDI x7693;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7925;
struct SEntry8_IIIITIIB x7369;
struct SEntry3_III x7941;
struct SEntry17_IIISSSSSSSSSSIIIS x7955;
struct SEntry9_ISSSSSSDD x7688;
struct SEntry8_IIIIITDS x7716;
struct SEntry10_IIIIIITIDS x7378;
struct SEntry17_IIISSSSSSSSSSIIIS x7528;
struct SEntry9_ISSSSSSDD x7928;
struct SEntry5_IISDS x7905;
struct SEntry10_IIIIIITIDS x7508;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7583;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x7358._2 = x27;
    x7358._3 = x12;
    struct SEntry3_III* x12236 = x3709.get(x7358);
    if((x12236!=(NULL))) {
      int x7362 = x12236->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x7362;
      newOrderTbl.del(x12236);
      int x41 = x18;
      x7369._1 = x7362;
      x7369._2 = x41;
      x7369._3 = x12;
      struct SEntry8_IIIITIIB* x12249 = x4146.get(x7369);
      int x7371 = x12249->_4;
      x12249->_6 = x13;
      double x50 = 0.0;
      int x52 = x18;
      x7378._1 = x7362;
      x7378._2 = x52;
      x7378._3 = x12;
      x4346.slice(x7378, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
        orderLineEntry->_7 = x11;
        double x57 = x50;
        double x7422 = orderLineEntry->_9;
        x50 = (x57+(x7422));
      
      }));
      int x65 = x18;
      x7382._1 = x7371;
      x7382._2 = x65;
      x7382._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12271 = x4451.get(x7382);
      double x69 = x50;
      x12271->_17 += x69;
      x12271->_20 += 1;
    } else {
      
      int x73 = x18;
      orderIDs[(x73-(1))] = 0;
    };
    int x77 = x18;
    x18 = (x77+(1));
  };
}
void StockLevelTx(int x81, date x82, int x83, int x84, int x85, int x86) {
  x7495._1 = x85;
  x7495._2 = x84;
  struct SEntry11_IISSSSSSDDI* x12338 = x4173.get(x7495);
  int x7497 = x12338->_11;
  int x95 = (x7497-(20));
  unordered_set<int> unique_ol_i_id({}); //setApply1
  while(1) {
    
    int x100 = x95;
    if (!((x100<(x7497)))) break; 
    
    int x102 = x95;
    x7508._1 = x102;
    x7508._2 = x85;
    x7508._3 = x84;
    x4346.slice(x7508, ([&](struct SEntry10_IIIIIITIDS* orderLineEntry) {
      int x7526 = orderLineEntry->_5;
      x7528._1 = x7526;
      x7528._2 = x84;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12353 = x4477.get(x7528);
      int x7530 = x12353->_3;
      if((x7530<(x86))) {
        unique_ol_i_id.insert(x7526);
      };
    
    }));
    int x119 = x95;
    x95 = (x119+(1));
  };
}
void OrderStatusTx(int x125, date x126, int x127, int x128, int x129, int x130, int x131, PString x132) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite17330 = NULL;
  if((x130>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x17331;
    x7583._2 = x129;
    x7583._3 = x128;
    x7583._6 = x132;
    x4452.slice(x7583, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x17331.push_back(custEntry);
    
    }));
    int x17339 = x17331.size();
    int x17341 = (x17339/(2));
    int x17349 = x17331.size();
    if(((x17349%(2))==(0))) {
      int x151 = x17341;
      x17341 = (x151-(1));
    };
    sort(x17331.begin(), x17331.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7624 = c1->_4;
      PString x7625 = c2->_4;
      return ((strcmpi(x7624.data_, x7625.data_))<(0)); 
    }));
    int x17357 = x17341;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17358 = x17331[x17357];
    ite17330 = x17358;
  } else {
    
    x7600._1 = x131;
    x7600._2 = x129;
    x7600._3 = x128;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17363 = x4451.get(x7600);
    ite17330 = x17363;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7570 = ite17330;
  int x7571 = x7570->_3;
  x7573._2 = x129;
  x7573._3 = x128;
  x7573._4 = x7571;
  struct SEntry8_IIIITIIB* x12440 = x4147.get(x7573);
  int x182 = 0;
  int x7576 = x12440->_1;
  x182 = x7576;
}
void PaymentTx(int x186, date x187, int x188, int x189, int x190, int x191, int x192, int x193, int x194, PString x195, double x196) {
  x7688._1 = x189;
  struct SEntry9_ISSSSSSDD* x12491 = x3903.get(x7688);
  x12491->_9 += x196;
  x7693._1 = x190;
  x7693._2 = x189;
  struct SEntry11_IISSSSSSDDI* x12496 = x4173.get(x7693);
  x12496->_10 += x196;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite17429 = NULL;
  if((x191>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x17430;
    x7733._2 = x193;
    x7733._3 = x192;
    x7733._6 = x195;
    x4452.slice(x7733, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry) {
      x17430.push_back(custEntry);
    
    }));
    int x17438 = x17430.size();
    int x17440 = (x17438/(2));
    int x17448 = x17430.size();
    if(((x17448%(2))==(0))) {
      int x227 = x17440;
      x17440 = (x227-(1));
    };
    sort(x17430.begin(), x17430.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7796 = c1->_4;
      PString x7797 = c2->_4;
      return ((strcmpi(x7796.data_, x7797.data_))<(0)); 
    }));
    int x17456 = x17440;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17457 = x17430[x17456];
    ite17429 = x17457;
  } else {
    
    x7750._1 = x194;
    x7750._2 = x193;
    x7750._3 = x192;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x17462 = x4451.get(x7750);
    ite17429 = x17462;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7698 = ite17429;
  PString x7699 = x7698->_21;
  PString x7700 = x7698->_14;
  char* x18781 = strstr(x7700.data_, "BC");
  if((x18781!=(NULL))) {
    int x7703 = x7698->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x7703, x193, x192, x190, x189, x196, IntToStrdate(x187), x7699.data_);
    x7698->_17 += x196;
    x7698->_21 = c_new_data;
  } else {
    
    x7698->_17 += x196;
  };
  PString x7710 = x12491->_2;
  PString x7711 = x12496->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x7710.data_, x7711.data_);
  int x7714 = x7698->_1;
  x7716._1 = x7714;
  x7716._2 = x193;
  x7716._3 = x192;
  x7716._4 = x190;
  x7716._5 = x189;
  x7716._6 = x187;
  x7716._7 = x196;
  x7716._8 = h_data;
  historyTbl.add(x7716);
}
void NewOrderTx(int x269, date x270, int x271, int x272, int x273, int x274, int x275, int x276, int* x277, int* x278, int* x279, double* x280, PString* x281, int* x282, PString* x283, double* x284) {
  int x286 = 0;
  int x289 = 0;
  PString idata[x275];
  int x294 = 1;
  while(1) {
    
    int x296 = x286;
    int ite17751 = 0;
    if((x296<(x275))) {
      
      int x298 = x294;
      int x17752 = x298;
      ite17751 = x17752;
    } else {
      
      ite17751 = 0;
    };
    int x17566 = ite17751;
    if (!(x17566)) break; 
    
    int x301 = x286;
    int x302 = x277[x301];
    x7905._1 = x302;
    struct SEntry5_IISDS* x12642 = x3922.get(x7905);
    if((x12642==(NULL))) {
      x294 = 0;
    } else {
      
      int x308 = x286;
      PString x7911 = x12642->_3;
      x281[x308] = x7911;
      int x311 = x286;
      double x7914 = x12642->_4;
      x280[x311] = x7914;
      int x314 = x286;
      PString x7917 = x12642->_5;
      idata[x314] = x7917;
    };
    int x318 = x286;
    x286 = (x318+(1));
  };
  int x322 = x294;
  if(x322) {
    x7925._1 = x274;
    x7925._2 = x273;
    x7925._3 = x272;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12664 = x4451.get(x7925);
    x7928._1 = x272;
    struct SEntry9_ISSSSSSDD* x12667 = x3903.get(x7928);
    x7931._1 = x273;
    x7931._2 = x272;
    struct SEntry11_IISSSSSSDDI* x12671 = x4173.get(x7931);
    int x7933 = x12671->_11;
    x12671->_11 += 1;
    x7938._1 = x7933;
    x7938._2 = x273;
    x7938._3 = x272;
    x7938._4 = x274;
    x7938._5 = x270;
    x7938._6 = -1;
    x7938._7 = x275;
    x7938._8 = (x276>(0));
    orderTbl.add(x7938);
    x7941._1 = x7933;
    x7941._2 = x273;
    x7941._3 = x272;
    newOrderTbl.add(x7941);
    double x347 = 0.0;
    x286 = 0;
    while(1) {
      
      int x350 = x286;
      if (!((x350<(x275)))) break; 
      
      int x353 = x286;
      int ol_supply_w_id = x278[x353];
      int x356 = x286;
      int ol_i_id = x277[x356];
      int x359 = x286;
      int ol_quantity = x279[x359];
      x7955._1 = ol_i_id;
      x7955._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12704 = x4477.get(x7955);
      PString ite17629 = PString();
      if((x273==(1))) {
        PString x17630 = x12704->_4;
        ite17629 = x17630;
      } else {
        
        PString ite17634 = PString();
        if((x273==(2))) {
          PString x17635 = x12704->_5;
          ite17634 = x17635;
        } else {
          
          PString ite17639 = PString();
          if((x273==(3))) {
            PString x17640 = x12704->_6;
            ite17639 = x17640;
          } else {
            
            PString ite17644 = PString();
            if((x273==(4))) {
              PString x17645 = x12704->_7;
              ite17644 = x17645;
            } else {
              
              PString ite17649 = PString();
              if((x273==(5))) {
                PString x17650 = x12704->_8;
                ite17649 = x17650;
              } else {
                
                PString ite17654 = PString();
                if((x273==(6))) {
                  PString x17655 = x12704->_9;
                  ite17654 = x17655;
                } else {
                  
                  PString ite17659 = PString();
                  if((x273==(7))) {
                    PString x17660 = x12704->_10;
                    ite17659 = x17660;
                  } else {
                    
                    PString ite17664 = PString();
                    if((x273==(8))) {
                      PString x17665 = x12704->_11;
                      ite17664 = x17665;
                    } else {
                      
                      PString ite17669 = PString();
                      if((x273==(9))) {
                        PString x17670 = x12704->_12;
                        ite17669 = x17670;
                      } else {
                        
                        PString x17672 = x12704->_13;
                        ite17669 = x17672;
                      };
                      PString x17668 = ite17669;
                      ite17664 = x17668;
                    };
                    PString x17663 = ite17664;
                    ite17659 = x17663;
                  };
                  PString x17658 = ite17659;
                  ite17654 = x17658;
                };
                PString x17653 = ite17654;
                ite17649 = x17653;
              };
              PString x17648 = ite17649;
              ite17644 = x17648;
            };
            PString x17643 = ite17644;
            ite17639 = x17643;
          };
          PString x17638 = ite17639;
          ite17634 = x17638;
        };
        PString x17633 = ite17634;
        ite17629 = x17633;
      };
      PString ol_dist_info = ite17629;
      int x7985 = x12704->_3;
      int x396 = x286;
      x282[x396] = x7985;
      PString x7988 = x12664->_14;
      char* x19016 = strstr(x7988.data_, "original");
      int ite17887 = 0;
      if((x19016!=(NULL))) {
        
        PString x7991 = x12704->_17;
        char* x19022 = strstr(x7991.data_, "original");
        int x17888 = (x19022!=(NULL));
        ite17887 = x17888;
      } else {
        
        ite17887 = 0;
      };
      int x17697 = ite17887;
      if(x17697) {
        int x403 = x286;
        x283[x403] = "B";
      } else {
        
        int x405 = x286;
        x283[x405] = "G";
      };
      x12704->_3 = (x7985-(ol_quantity));
      if((x7985<=(ol_quantity))) {
        x12704->_3 += 91;
      };
      int x414 = 0;
      if((ol_supply_w_id!=(x272))) {
        x414 = 1;
      };
      double x8008 = x12664->_16;
      double x8009 = x12667->_8;
      double x8010 = x12671->_9;
      int x427 = x286;
      double x428 = x280[x427];
      double ol_amount = ((ol_quantity*(x428))*(((1.0+(x8009))+(x8010))))*((1.0-(x8008)));
      int x436 = x286;
      x284[x436] = ol_amount;
      double x438 = x347;
      x347 = (x438+(ol_amount));
      int x441 = x286;
      x8028._1 = x7933;
      x8028._2 = x273;
      x8028._3 = x272;
      x8028._4 = (x441+(1));
      x8028._5 = ol_i_id;
      x8028._6 = ol_supply_w_id;
      x8028._8 = ol_quantity;
      x8028._9 = ol_amount;
      x8028._10 = ol_dist_info;
      orderLineTbl.add(x8028);
      int x446 = x286;
      x286 = (x446+(1));
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
