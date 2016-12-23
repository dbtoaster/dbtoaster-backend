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
  int _1;  int _2;  PString _3;  double _4;  PString _5;  SEntry5_IISDS *prv;  SEntry5_IISDS *nxt;
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  SEntry11_IISSSSSSDDI *prv;  SEntry11_IISSSSSSDDI *nxt;
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt;
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt;
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt;
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt;
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt;
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt;
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  SEntry9_ISSSSSSDD *prv;  SEntry9_ISSSSSSDD *nxt;
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
#define int unsigned int
 struct SEntry10_IIIIIITIDS_Idx1234 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4256)  { 
    int x4257 = -889275714;
    int x4258 = x4256._1;
    int x4259 = HASH(x4258);
    int x4260 = -862048943*(x4259);
    int x4261 = x4260<<(15);
    int x4262 = x4260 >> (-15 & (8*sizeof(x4260)-1));
    int x4263 = x4261|(x4262);
    int x4264 = x4263*(461845907);
    int x4265 = x4257;
    int x4266 = x4264^(x4265);
    int x4267 = x4266<<(13);
    int x4268 = x4266 >> (-13 & (8*sizeof(x4266)-1));
    int x4269 = x4267|(x4268);
    int x4270 = x4269*(5);
    int x4271 = x4270+(-430675100);
    x4257 = x4271;
    int x4273 = x4256._2;
    int x4274 = HASH(x4273);
    int x4275 = -862048943*(x4274);
    int x4276 = x4275<<(15);
    int x4277 = x4275 >> (-15 & (8*sizeof(x4275)-1));
    int x4278 = x4276|(x4277);
    int x4279 = x4278*(461845907);
    int x4280 = x4257;
    int x4281 = x4279^(x4280);
    int x4282 = x4281<<(13);
    int x4283 = x4281 >> (-13 & (8*sizeof(x4281)-1));
    int x4284 = x4282|(x4283);
    int x4285 = x4284*(5);
    int x4286 = x4285+(-430675100);
    x4257 = x4286;
    int x4288 = x4256._3;
    int x4289 = HASH(x4288);
    int x4290 = -862048943*(x4289);
    int x4291 = x4290<<(15);
    int x4292 = x4290 >> (-15 & (8*sizeof(x4290)-1));
    int x4293 = x4291|(x4292);
    int x4294 = x4293*(461845907);
    int x4295 = x4257;
    int x4296 = x4294^(x4295);
    int x4297 = x4296<<(13);
    int x4298 = x4296 >> (-13 & (8*sizeof(x4296)-1));
    int x4299 = x4297|(x4298);
    int x4300 = x4299*(5);
    int x4301 = x4300+(-430675100);
    x4257 = x4301;
    int x4303 = x4256._4;
    int x4304 = HASH(x4303);
    int x4305 = -862048943*(x4304);
    int x4306 = x4305<<(15);
    int x4307 = x4305 >> (-15 & (8*sizeof(x4305)-1));
    int x4308 = x4306|(x4307);
    int x4309 = x4308*(461845907);
    int x4310 = x4257;
    int x4311 = x4309^(x4310);
    int x4312 = x4311<<(13);
    int x4313 = x4311 >> (-13 & (8*sizeof(x4311)-1));
    int x4314 = x4312|(x4313);
    int x4315 = x4314*(5);
    int x4316 = x4315+(-430675100);
    x4257 = x4316;
    int x4318 = x4257;
    int x4319 = x4318^(2);
    int x4320 = x4319 >> (16 & (8*sizeof(x4319)-1));
    int x4321 = x4319^(x4320);
    int x4322 = x4321*(-2048144789);
    int x4323 = x4322 >> (13 & (8*sizeof(x4322)-1));
    int x4324 = x4322^(x4323);
    int x4325 = x4324*(-1028477387);
    int x4326 = x4325 >> (16 & (8*sizeof(x4325)-1));
    int x4327 = x4325^(x4326);
    return x4327; 
  }
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4329, const struct SEntry10_IIIIIITIDS& x4330) { 
    int x4331 = x4329._1;
    int x4332 = x4330._1;
    int x4333 = x4331==(x4332);
    int ite18065 = 0;
    if(x4333) {
      
      int x4334 = x4329._2;
      int x4335 = x4330._2;
      int x4336 = x4334==(x4335);
      int x18066 = x4336;
      ite18065 = x18066;
    } else {
      
      ite18065 = 0;
    };
    int x18055 = ite18065;
    int ite18074 = 0;
    if(x18055) {
      
      int x4338 = x4329._3;
      int x4339 = x4330._3;
      int x4340 = x4338==(x4339);
      int x18075 = x4340;
      ite18074 = x18075;
    } else {
      
      ite18074 = 0;
    };
    int x18057 = ite18074;
    int ite18083 = 0;
    if(x18057) {
      
      int x4342 = x4329._4;
      int x4343 = x4330._4;
      int x4344 = x4342==(x4343);
      int x18084 = x4344;
      ite18083 = x18084;
    } else {
      
      ite18083 = 0;
    };
    int x18059 = ite18083;
    int x4346 = x18059 ? 0 : 1;
    return x4346; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4150)  { 
    int x4151 = -889275714;
    int x4152 = x4150._2;
    int x4153 = HASH(x4152);
    int x4154 = -862048943*(x4153);
    int x4155 = x4154<<(15);
    int x4156 = x4154 >> (-15 & (8*sizeof(x4154)-1));
    int x4157 = x4155|(x4156);
    int x4158 = x4157*(461845907);
    int x4159 = x4151;
    int x4160 = x4158^(x4159);
    int x4161 = x4160<<(13);
    int x4162 = x4160 >> (-13 & (8*sizeof(x4160)-1));
    int x4163 = x4161|(x4162);
    int x4164 = x4163*(5);
    int x4165 = x4164+(-430675100);
    x4151 = x4165;
    int x4167 = x4150._3;
    int x4168 = HASH(x4167);
    int x4169 = -862048943*(x4168);
    int x4170 = x4169<<(15);
    int x4171 = x4169 >> (-15 & (8*sizeof(x4169)-1));
    int x4172 = x4170|(x4171);
    int x4173 = x4172*(461845907);
    int x4174 = x4151;
    int x4175 = x4173^(x4174);
    int x4176 = x4175<<(13);
    int x4177 = x4175 >> (-13 & (8*sizeof(x4175)-1));
    int x4178 = x4176|(x4177);
    int x4179 = x4178*(5);
    int x4180 = x4179+(-430675100);
    x4151 = x4180;
    int x4182 = x4150._4;
    int x4183 = HASH(x4182);
    int x4184 = -862048943*(x4183);
    int x4185 = x4184<<(15);
    int x4186 = x4184 >> (-15 & (8*sizeof(x4184)-1));
    int x4187 = x4185|(x4186);
    int x4188 = x4187*(461845907);
    int x4189 = x4151;
    int x4190 = x4188^(x4189);
    int x4191 = x4190<<(13);
    int x4192 = x4190 >> (-13 & (8*sizeof(x4190)-1));
    int x4193 = x4191|(x4192);
    int x4194 = x4193*(5);
    int x4195 = x4194+(-430675100);
    x4151 = x4195;
    int x4197 = x4151;
    int x4198 = x4197^(2);
    int x4199 = x4198 >> (16 & (8*sizeof(x4198)-1));
    int x4200 = x4198^(x4199);
    int x4201 = x4200*(-2048144789);
    int x4202 = x4201 >> (13 & (8*sizeof(x4201)-1));
    int x4203 = x4201^(x4202);
    int x4204 = x4203*(-1028477387);
    int x4205 = x4204 >> (16 & (8*sizeof(x4204)-1));
    int x4206 = x4204^(x4205);
    return x4206; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4208, const struct SEntry8_IIIITIIB& x4209) { 
    int x4210 = x4208._2;
    int x4211 = x4209._2;
    int x4212 = x4210==(x4211);
    int ite18191 = 0;
    if(x4212) {
      
      int x4213 = x4208._3;
      int x4214 = x4209._3;
      int x4215 = x4213==(x4214);
      int x18192 = x4215;
      ite18191 = x18192;
    } else {
      
      ite18191 = 0;
    };
    int x18183 = ite18191;
    int ite18200 = 0;
    if(x18183) {
      
      int x4217 = x4208._4;
      int x4218 = x4209._4;
      int x4219 = x4217==(x4218);
      int x18201 = x4219;
      ite18200 = x18201;
    } else {
      
      ite18200 = 0;
    };
    int x18185 = ite18200;
    int x4221 = x18185 ? 0 : 1;
    return x4221; 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3580)  { 
    int x3581 = -889275714;
    int x3582 = x3580._1;
    int x3583 = HASH(x3582);
    int x3584 = -862048943*(x3583);
    int x3585 = x3584<<(15);
    int x3586 = x3584 >> (-15 & (8*sizeof(x3584)-1));
    int x3587 = x3585|(x3586);
    int x3588 = x3587*(461845907);
    int x3589 = x3581;
    int x3590 = x3588^(x3589);
    int x3591 = x3590<<(13);
    int x3592 = x3590 >> (-13 & (8*sizeof(x3590)-1));
    int x3593 = x3591|(x3592);
    int x3594 = x3593*(5);
    int x3595 = x3594+(-430675100);
    x3581 = x3595;
    int x3597 = x3580._2;
    int x3598 = HASH(x3597);
    int x3599 = -862048943*(x3598);
    int x3600 = x3599<<(15);
    int x3601 = x3599 >> (-15 & (8*sizeof(x3599)-1));
    int x3602 = x3600|(x3601);
    int x3603 = x3602*(461845907);
    int x3604 = x3581;
    int x3605 = x3603^(x3604);
    int x3606 = x3605<<(13);
    int x3607 = x3605 >> (-13 & (8*sizeof(x3605)-1));
    int x3608 = x3606|(x3607);
    int x3609 = x3608*(5);
    int x3610 = x3609+(-430675100);
    x3581 = x3610;
    int x3612 = x3580._3;
    int x3613 = HASH(x3612);
    int x3614 = -862048943*(x3613);
    int x3615 = x3614<<(15);
    int x3616 = x3614 >> (-15 & (8*sizeof(x3614)-1));
    int x3617 = x3615|(x3616);
    int x3618 = x3617*(461845907);
    int x3619 = x3581;
    int x3620 = x3618^(x3619);
    int x3621 = x3620<<(13);
    int x3622 = x3620 >> (-13 & (8*sizeof(x3620)-1));
    int x3623 = x3621|(x3622);
    int x3624 = x3623*(5);
    int x3625 = x3624+(-430675100);
    x3581 = x3625;
    int x3627 = x3581;
    int x3628 = x3627^(2);
    int x3629 = x3628 >> (16 & (8*sizeof(x3628)-1));
    int x3630 = x3628^(x3629);
    int x3631 = x3630*(-2048144789);
    int x3632 = x3631 >> (13 & (8*sizeof(x3631)-1));
    int x3633 = x3631^(x3632);
    int x3634 = x3633*(-1028477387);
    int x3635 = x3634 >> (16 & (8*sizeof(x3634)-1));
    int x3636 = x3634^(x3635);
    return x3636; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3638, const struct SEntry3_III& x3639) { 
    int x3640 = x3638._1;
    int x3641 = x3639._1;
    int x3642 = x3640==(x3641);
    int ite18299 = 0;
    if(x3642) {
      
      int x3643 = x3638._2;
      int x3644 = x3639._2;
      int x3645 = x3643==(x3644);
      int x18300 = x3645;
      ite18299 = x18300;
    } else {
      
      ite18299 = 0;
    };
    int x18291 = ite18299;
    int ite18308 = 0;
    if(x18291) {
      
      int x3647 = x3638._3;
      int x3648 = x3639._3;
      int x3649 = x3647==(x3648);
      int x18309 = x3649;
      ite18308 = x18309;
    } else {
      
      ite18308 = 0;
    };
    int x18293 = ite18308;
    int x3651 = x18293 ? 0 : 1;
    return x3651; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4349)  { 
    int x4350 = -889275714;
    int x4351 = x4349._1;
    int x4352 = HASH(x4351);
    int x4353 = -862048943*(x4352);
    int x4354 = x4353<<(15);
    int x4355 = x4353 >> (-15 & (8*sizeof(x4353)-1));
    int x4356 = x4354|(x4355);
    int x4357 = x4356*(461845907);
    int x4358 = x4350;
    int x4359 = x4357^(x4358);
    int x4360 = x4359<<(13);
    int x4361 = x4359 >> (-13 & (8*sizeof(x4359)-1));
    int x4362 = x4360|(x4361);
    int x4363 = x4362*(5);
    int x4364 = x4363+(-430675100);
    x4350 = x4364;
    int x4366 = x4349._2;
    int x4367 = HASH(x4366);
    int x4368 = -862048943*(x4367);
    int x4369 = x4368<<(15);
    int x4370 = x4368 >> (-15 & (8*sizeof(x4368)-1));
    int x4371 = x4369|(x4370);
    int x4372 = x4371*(461845907);
    int x4373 = x4350;
    int x4374 = x4372^(x4373);
    int x4375 = x4374<<(13);
    int x4376 = x4374 >> (-13 & (8*sizeof(x4374)-1));
    int x4377 = x4375|(x4376);
    int x4378 = x4377*(5);
    int x4379 = x4378+(-430675100);
    x4350 = x4379;
    int x4381 = x4349._3;
    int x4382 = HASH(x4381);
    int x4383 = -862048943*(x4382);
    int x4384 = x4383<<(15);
    int x4385 = x4383 >> (-15 & (8*sizeof(x4383)-1));
    int x4386 = x4384|(x4385);
    int x4387 = x4386*(461845907);
    int x4388 = x4350;
    int x4389 = x4387^(x4388);
    int x4390 = x4389<<(13);
    int x4391 = x4389 >> (-13 & (8*sizeof(x4389)-1));
    int x4392 = x4390|(x4391);
    int x4393 = x4392*(5);
    int x4394 = x4393+(-430675100);
    x4350 = x4394;
    int x4396 = x4350;
    int x4397 = x4396^(2);
    int x4398 = x4397 >> (16 & (8*sizeof(x4397)-1));
    int x4399 = x4397^(x4398);
    int x4400 = x4399*(-2048144789);
    int x4401 = x4400 >> (13 & (8*sizeof(x4400)-1));
    int x4402 = x4400^(x4401);
    int x4403 = x4402*(-1028477387);
    int x4404 = x4403 >> (16 & (8*sizeof(x4403)-1));
    int x4405 = x4403^(x4404);
    return x4405; 
  }
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x4407, const struct SEntry10_IIIIIITIDS& x4408) { 
    int x4409 = x4407._1;
    int x4410 = x4408._1;
    int x4411 = x4409==(x4410);
    int ite18407 = 0;
    if(x4411) {
      
      int x4412 = x4407._2;
      int x4413 = x4408._2;
      int x4414 = x4412==(x4413);
      int x18408 = x4414;
      ite18407 = x18408;
    } else {
      
      ite18407 = 0;
    };
    int x18399 = ite18407;
    int ite18416 = 0;
    if(x18399) {
      
      int x4416 = x4407._3;
      int x4417 = x4408._3;
      int x4418 = x4416==(x4417);
      int x18417 = x4418;
      ite18416 = x18417;
    } else {
      
      ite18416 = 0;
    };
    int x18401 = ite18416;
    int x4420 = x18401 ? 0 : 1;
    return x4420; 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3707)  { 
    int x3708 = -889275714;
    int x3709 = x3707._2;
    int x3710 = HASH(x3709);
    int x3711 = -862048943*(x3710);
    int x3712 = x3711<<(15);
    int x3713 = x3711 >> (-15 & (8*sizeof(x3711)-1));
    int x3714 = x3712|(x3713);
    int x3715 = x3714*(461845907);
    int x3716 = x3708;
    int x3717 = x3715^(x3716);
    int x3718 = x3717<<(13);
    int x3719 = x3717 >> (-13 & (8*sizeof(x3717)-1));
    int x3720 = x3718|(x3719);
    int x3721 = x3720*(5);
    int x3722 = x3721+(-430675100);
    x3708 = x3722;
    int x3724 = x3707._3;
    int x3725 = HASH(x3724);
    int x3726 = -862048943*(x3725);
    int x3727 = x3726<<(15);
    int x3728 = x3726 >> (-15 & (8*sizeof(x3726)-1));
    int x3729 = x3727|(x3728);
    int x3730 = x3729*(461845907);
    int x3731 = x3708;
    int x3732 = x3730^(x3731);
    int x3733 = x3732<<(13);
    int x3734 = x3732 >> (-13 & (8*sizeof(x3732)-1));
    int x3735 = x3733|(x3734);
    int x3736 = x3735*(5);
    int x3737 = x3736+(-430675100);
    x3708 = x3737;
    int x3739 = x3708;
    int x3740 = x3739^(2);
    int x3741 = x3740 >> (16 & (8*sizeof(x3740)-1));
    int x3742 = x3740^(x3741);
    int x3743 = x3742*(-2048144789);
    int x3744 = x3743 >> (13 & (8*sizeof(x3743)-1));
    int x3745 = x3743^(x3744);
    int x3746 = x3745*(-1028477387);
    int x3747 = x3746 >> (16 & (8*sizeof(x3746)-1));
    int x3748 = x3746^(x3747);
    return x3748; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3750, const struct SEntry3_III& x3751) { 
    int x3752 = x3750._2;
    int x3753 = x3751._2;
    int x3754 = x3752==(x3753);
    int ite18498 = 0;
    if(x3754) {
      
      int x3755 = x3750._3;
      int x3756 = x3751._3;
      int x3757 = x3755==(x3756);
      int x18499 = x3757;
      ite18498 = x18499;
    } else {
      
      ite18498 = 0;
    };
    int x18492 = ite18498;
    int x3759 = x18492 ? 0 : 1;
    return x3759; 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3769)  { 
    int x3770 = -889275714;
    int x3771 = x3769._1;
    int x3772 = HASH(x3771);
    int x3773 = -862048943*(x3772);
    int x3774 = x3773<<(15);
    int x3775 = x3773 >> (-15 & (8*sizeof(x3773)-1));
    int x3776 = x3774|(x3775);
    int x3777 = x3776*(461845907);
    int x3778 = x3770;
    int x3779 = x3777^(x3778);
    int x3780 = x3779<<(13);
    int x3781 = x3779 >> (-13 & (8*sizeof(x3779)-1));
    int x3782 = x3780|(x3781);
    int x3783 = x3782*(5);
    int x3784 = x3783+(-430675100);
    x3770 = x3784;
    int x3786 = x3769._2;
    int x3787 = HASH(x3786);
    int x3788 = -862048943*(x3787);
    int x3789 = x3788<<(15);
    int x3790 = x3788 >> (-15 & (8*sizeof(x3788)-1));
    int x3791 = x3789|(x3790);
    int x3792 = x3791*(461845907);
    int x3793 = x3770;
    int x3794 = x3792^(x3793);
    int x3795 = x3794<<(13);
    int x3796 = x3794 >> (-13 & (8*sizeof(x3794)-1));
    int x3797 = x3795|(x3796);
    int x3798 = x3797*(5);
    int x3799 = x3798+(-430675100);
    x3770 = x3799;
    int x3801 = x3769._3;
    int x3802 = HASH(x3801);
    int x3803 = -862048943*(x3802);
    int x3804 = x3803<<(15);
    int x3805 = x3803 >> (-15 & (8*sizeof(x3803)-1));
    int x3806 = x3804|(x3805);
    int x3807 = x3806*(461845907);
    int x3808 = x3770;
    int x3809 = x3807^(x3808);
    int x3810 = x3809<<(13);
    int x3811 = x3809 >> (-13 & (8*sizeof(x3809)-1));
    int x3812 = x3810|(x3811);
    int x3813 = x3812*(5);
    int x3814 = x3813+(-430675100);
    x3770 = x3814;
    int x3816 = x3769._4;
    int x3817 = HASH(x3816);
    int x3818 = -862048943*(x3817);
    int x3819 = x3818<<(15);
    int x3820 = x3818 >> (-15 & (8*sizeof(x3818)-1));
    int x3821 = x3819|(x3820);
    int x3822 = x3821*(461845907);
    int x3823 = x3770;
    int x3824 = x3822^(x3823);
    int x3825 = x3824<<(13);
    int x3826 = x3824 >> (-13 & (8*sizeof(x3824)-1));
    int x3827 = x3825|(x3826);
    int x3828 = x3827*(5);
    int x3829 = x3828+(-430675100);
    x3770 = x3829;
    int x3831 = x3769._5;
    int x3832 = HASH(x3831);
    int x3833 = -862048943*(x3832);
    int x3834 = x3833<<(15);
    int x3835 = x3833 >> (-15 & (8*sizeof(x3833)-1));
    int x3836 = x3834|(x3835);
    int x3837 = x3836*(461845907);
    int x3838 = x3770;
    int x3839 = x3837^(x3838);
    int x3840 = x3839<<(13);
    int x3841 = x3839 >> (-13 & (8*sizeof(x3839)-1));
    int x3842 = x3840|(x3841);
    int x3843 = x3842*(5);
    int x3844 = x3843+(-430675100);
    x3770 = x3844;
    date x3846 = x3769._6;
    int x3847 = HASH(x3846);
    int x3848 = -862048943*(x3847);
    int x3849 = x3848<<(15);
    int x3850 = x3848 >> (-15 & (8*sizeof(x3848)-1));
    int x3851 = x3849|(x3850);
    int x3852 = x3851*(461845907);
    int x3853 = x3770;
    int x3854 = x3852^(x3853);
    int x3855 = x3854<<(13);
    int x3856 = x3854 >> (-13 & (8*sizeof(x3854)-1));
    int x3857 = x3855|(x3856);
    int x3858 = x3857*(5);
    int x3859 = x3858+(-430675100);
    x3770 = x3859;
    double x3861 = x3769._7;
    int x3862 = HASH(x3861);
    int x3863 = -862048943*(x3862);
    int x3864 = x3863<<(15);
    int x3865 = x3863 >> (-15 & (8*sizeof(x3863)-1));
    int x3866 = x3864|(x3865);
    int x3867 = x3866*(461845907);
    int x3868 = x3770;
    int x3869 = x3867^(x3868);
    int x3870 = x3869<<(13);
    int x3871 = x3869 >> (-13 & (8*sizeof(x3869)-1));
    int x3872 = x3870|(x3871);
    int x3873 = x3872*(5);
    int x3874 = x3873+(-430675100);
    x3770 = x3874;
    PString x3876 = x3769._8;
    int x3877 = HASH(x3876);
    int x3878 = -862048943*(x3877);
    int x3879 = x3878<<(15);
    int x3880 = x3878 >> (-15 & (8*sizeof(x3878)-1));
    int x3881 = x3879|(x3880);
    int x3882 = x3881*(461845907);
    int x3883 = x3770;
    int x3884 = x3882^(x3883);
    int x3885 = x3884<<(13);
    int x3886 = x3884 >> (-13 & (8*sizeof(x3884)-1));
    int x3887 = x3885|(x3886);
    int x3888 = x3887*(5);
    int x3889 = x3888+(-430675100);
    x3770 = x3889;
    int x3891 = x3770;
    int x3892 = x3891^(2);
    int x3893 = x3892 >> (16 & (8*sizeof(x3892)-1));
    int x3894 = x3892^(x3893);
    int x3895 = x3894*(-2048144789);
    int x3896 = x3895 >> (13 & (8*sizeof(x3895)-1));
    int x3897 = x3895^(x3896);
    int x3898 = x3897*(-1028477387);
    int x3899 = x3898 >> (16 & (8*sizeof(x3898)-1));
    int x3900 = x3898^(x3899);
    return x3900; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3902, const struct SEntry8_IIIIITDS& x3903) { 
    int x3904 = x3902._1;
    int x3905 = x3903._1;
    int x3906 = x3904==(-2147483648);
    int ite18675 = 0;
    if(x3906) {
      ite18675 = 1;
    } else {
      
      
      int x3907 = x3905==(-2147483648);
      int x18677 = x3907;
      ite18675 = x18677;
    };
    int x18655 = ite18675;
    int ite18682 = 0;
    if(x18655) {
      ite18682 = 1;
    } else {
      
      
      int x3909 = x3904==(x3905);
      int x18684 = x3909;
      ite18682 = x18684;
    };
    int x18657 = ite18682;
    int ite18689 = 0;
    if(x18657) {
      
      int x3911 = x3902._2;
      int x3912 = x3903._2;
      int x3913 = x3911==(-2147483648);
      int ite18791 = 0;
      if(x3913) {
        ite18791 = 1;
      } else {
        
        
        int x3914 = x3912==(-2147483648);
        int x18793 = x3914;
        ite18791 = x18793;
      };
      int x18695 = ite18791;
      int ite18798 = 0;
      if(x18695) {
        ite18798 = 1;
      } else {
        
        
        int x3916 = x3911==(x3912);
        int x18800 = x3916;
        ite18798 = x18800;
      };
      int x18697 = ite18798;
      int x18690 = x18697;
      ite18689 = x18690;
    } else {
      
      ite18689 = 0;
    };
    int x18659 = ite18689;
    int ite18702 = 0;
    if(x18659) {
      
      int x3919 = x3902._3;
      int x3920 = x3903._3;
      int x3921 = x3919==(-2147483648);
      int ite18814 = 0;
      if(x3921) {
        ite18814 = 1;
      } else {
        
        
        int x3922 = x3920==(-2147483648);
        int x18816 = x3922;
        ite18814 = x18816;
      };
      int x18708 = ite18814;
      int ite18821 = 0;
      if(x18708) {
        ite18821 = 1;
      } else {
        
        
        int x3924 = x3919==(x3920);
        int x18823 = x3924;
        ite18821 = x18823;
      };
      int x18710 = ite18821;
      int x18703 = x18710;
      ite18702 = x18703;
    } else {
      
      ite18702 = 0;
    };
    int x18661 = ite18702;
    int ite18715 = 0;
    if(x18661) {
      
      int x3927 = x3902._4;
      int x3928 = x3903._4;
      int x3929 = x3927==(-2147483648);
      int ite18837 = 0;
      if(x3929) {
        ite18837 = 1;
      } else {
        
        
        int x3930 = x3928==(-2147483648);
        int x18839 = x3930;
        ite18837 = x18839;
      };
      int x18721 = ite18837;
      int ite18844 = 0;
      if(x18721) {
        ite18844 = 1;
      } else {
        
        
        int x3932 = x3927==(x3928);
        int x18846 = x3932;
        ite18844 = x18846;
      };
      int x18723 = ite18844;
      int x18716 = x18723;
      ite18715 = x18716;
    } else {
      
      ite18715 = 0;
    };
    int x18663 = ite18715;
    int ite18728 = 0;
    if(x18663) {
      
      int x3935 = x3902._5;
      int x3936 = x3903._5;
      int x3937 = x3935==(-2147483648);
      int ite18860 = 0;
      if(x3937) {
        ite18860 = 1;
      } else {
        
        
        int x3938 = x3936==(-2147483648);
        int x18862 = x3938;
        ite18860 = x18862;
      };
      int x18734 = ite18860;
      int ite18867 = 0;
      if(x18734) {
        ite18867 = 1;
      } else {
        
        
        int x3940 = x3935==(x3936);
        int x18869 = x3940;
        ite18867 = x18869;
      };
      int x18736 = ite18867;
      int x18729 = x18736;
      ite18728 = x18729;
    } else {
      
      ite18728 = 0;
    };
    int x18665 = ite18728;
    int ite18741 = 0;
    if(x18665) {
      
      date x3943 = x3902._6;
      date x3944 = x3903._6;
      int x3945 = x3943==(0);
      int ite18883 = 0;
      if(x3945) {
        ite18883 = 1;
      } else {
        
        
        int x3946 = x3944==(0);
        int x18885 = x3946;
        ite18883 = x18885;
      };
      int x18747 = ite18883;
      int ite18890 = 0;
      if(x18747) {
        ite18890 = 1;
      } else {
        
        
        int x3948 = x3943==(x3944);
        int x18892 = x3948;
        ite18890 = x18892;
      };
      int x18749 = ite18890;
      int x18742 = x18749;
      ite18741 = x18742;
    } else {
      
      ite18741 = 0;
    };
    int x18667 = ite18741;
    int ite18754 = 0;
    if(x18667) {
      
      double x3951 = x3902._7;
      double x3952 = x3903._7;
      int x3953 = x3951==(-1.7976931348623157E308);
      int ite18906 = 0;
      if(x3953) {
        ite18906 = 1;
      } else {
        
        
        int x3954 = x3952==(-1.7976931348623157E308);
        int x18908 = x3954;
        ite18906 = x18908;
      };
      int x18760 = ite18906;
      int ite18913 = 0;
      if(x18760) {
        ite18913 = 1;
      } else {
        
        
        int x3956 = x3951==(x3952);
        int x18915 = x3956;
        ite18913 = x18915;
      };
      int x18762 = ite18913;
      int x18755 = x18762;
      ite18754 = x18755;
    } else {
      
      ite18754 = 0;
    };
    int x18669 = ite18754;
    int x3959 = x18669 ? 0 : 1;
    return x3959; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4455)  { 
    int x4456 = -889275714;
    int x4457 = x4455._2;
    int x4458 = HASH(x4457);
    int x4459 = -862048943*(x4458);
    int x4460 = x4459<<(15);
    int x4461 = x4459 >> (-15 & (8*sizeof(x4459)-1));
    int x4462 = x4460|(x4461);
    int x4463 = x4462*(461845907);
    int x4464 = x4456;
    int x4465 = x4463^(x4464);
    int x4466 = x4465<<(13);
    int x4467 = x4465 >> (-13 & (8*sizeof(x4465)-1));
    int x4468 = x4466|(x4467);
    int x4469 = x4468*(5);
    int x4470 = x4469+(-430675100);
    x4456 = x4470;
    int x4472 = x4455._3;
    int x4473 = HASH(x4472);
    int x4474 = -862048943*(x4473);
    int x4475 = x4474<<(15);
    int x4476 = x4474 >> (-15 & (8*sizeof(x4474)-1));
    int x4477 = x4475|(x4476);
    int x4478 = x4477*(461845907);
    int x4479 = x4456;
    int x4480 = x4478^(x4479);
    int x4481 = x4480<<(13);
    int x4482 = x4480 >> (-13 & (8*sizeof(x4480)-1));
    int x4483 = x4481|(x4482);
    int x4484 = x4483*(5);
    int x4485 = x4484+(-430675100);
    x4456 = x4485;
    PString x4487 = x4455._6;
    int x4488 = HASH(x4487);
    int x4489 = -862048943*(x4488);
    int x4490 = x4489<<(15);
    int x4491 = x4489 >> (-15 & (8*sizeof(x4489)-1));
    int x4492 = x4490|(x4491);
    int x4493 = x4492*(461845907);
    int x4494 = x4456;
    int x4495 = x4493^(x4494);
    int x4496 = x4495<<(13);
    int x4497 = x4495 >> (-13 & (8*sizeof(x4495)-1));
    int x4498 = x4496|(x4497);
    int x4499 = x4498*(5);
    int x4500 = x4499+(-430675100);
    x4456 = x4500;
    int x4502 = x4456;
    int x4503 = x4502^(2);
    int x4504 = x4503 >> (16 & (8*sizeof(x4503)-1));
    int x4505 = x4503^(x4504);
    int x4506 = x4505*(-2048144789);
    int x4507 = x4506 >> (13 & (8*sizeof(x4506)-1));
    int x4508 = x4506^(x4507);
    int x4509 = x4508*(-1028477387);
    int x4510 = x4509 >> (16 & (8*sizeof(x4509)-1));
    int x4511 = x4509^(x4510);
    return x4511; 
  }
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4513, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4514) { 
    int x4515 = x4513._2;
    int x4516 = x4514._2;
    int x4517 = x4515==(x4516);
    int ite19147 = 0;
    if(x4517) {
      
      int x4518 = x4513._3;
      int x4519 = x4514._3;
      int x4520 = x4518==(x4519);
      int x19148 = x4520;
      ite19147 = x19148;
    } else {
      
      ite19147 = 0;
    };
    int x19139 = ite19147;
    int ite19156 = 0;
    if(x19139) {
      
      PString x4522 = x4513._6;
      PString x4523 = x4514._6;
      int x4524 = x4522==(x4523);
      int x19157 = x4524;
      ite19156 = x19157;
    } else {
      
      ite19156 = 0;
    };
    int x19141 = ite19156;
    int x4526 = x19141 ? 0 : 1;
    return x4526; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4008)  { 
    int x4009 = -889275714;
    int x4010 = x4008._1;
    int x4011 = HASH(x4010);
    int x4012 = -862048943*(x4011);
    int x4013 = x4012<<(15);
    int x4014 = x4012 >> (-15 & (8*sizeof(x4012)-1));
    int x4015 = x4013|(x4014);
    int x4016 = x4015*(461845907);
    int x4017 = x4009;
    int x4018 = x4016^(x4017);
    int x4019 = x4018<<(13);
    int x4020 = x4018 >> (-13 & (8*sizeof(x4018)-1));
    int x4021 = x4019|(x4020);
    int x4022 = x4021*(5);
    int x4023 = x4022+(-430675100);
    x4009 = x4023;
    int x4025 = x4008._2;
    int x4026 = HASH(x4025);
    int x4027 = -862048943*(x4026);
    int x4028 = x4027<<(15);
    int x4029 = x4027 >> (-15 & (8*sizeof(x4027)-1));
    int x4030 = x4028|(x4029);
    int x4031 = x4030*(461845907);
    int x4032 = x4009;
    int x4033 = x4031^(x4032);
    int x4034 = x4033<<(13);
    int x4035 = x4033 >> (-13 & (8*sizeof(x4033)-1));
    int x4036 = x4034|(x4035);
    int x4037 = x4036*(5);
    int x4038 = x4037+(-430675100);
    x4009 = x4038;
    int x4040 = x4008._3;
    int x4041 = HASH(x4040);
    int x4042 = -862048943*(x4041);
    int x4043 = x4042<<(15);
    int x4044 = x4042 >> (-15 & (8*sizeof(x4042)-1));
    int x4045 = x4043|(x4044);
    int x4046 = x4045*(461845907);
    int x4047 = x4009;
    int x4048 = x4046^(x4047);
    int x4049 = x4048<<(13);
    int x4050 = x4048 >> (-13 & (8*sizeof(x4048)-1));
    int x4051 = x4049|(x4050);
    int x4052 = x4051*(5);
    int x4053 = x4052+(-430675100);
    x4009 = x4053;
    int x4055 = x4009;
    int x4056 = x4055^(2);
    int x4057 = x4056 >> (16 & (8*sizeof(x4056)-1));
    int x4058 = x4056^(x4057);
    int x4059 = x4058*(-2048144789);
    int x4060 = x4059 >> (13 & (8*sizeof(x4059)-1));
    int x4061 = x4059^(x4060);
    int x4062 = x4061*(-1028477387);
    int x4063 = x4062 >> (16 & (8*sizeof(x4062)-1));
    int x4064 = x4062^(x4063);
    return x4064; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4066, const struct SEntry8_IIIITIIB& x4067) { 
    int x4068 = x4066._1;
    int x4069 = x4067._1;
    int x4070 = x4068==(x4069);
    int ite19255 = 0;
    if(x4070) {
      
      int x4071 = x4066._2;
      int x4072 = x4067._2;
      int x4073 = x4071==(x4072);
      int x19256 = x4073;
      ite19255 = x19256;
    } else {
      
      ite19255 = 0;
    };
    int x19247 = ite19255;
    int ite19264 = 0;
    if(x19247) {
      
      int x4075 = x4066._3;
      int x4076 = x4067._3;
      int x4077 = x4075==(x4076);
      int x19265 = x4077;
      ite19264 = x19265;
    } else {
      
      ite19264 = 0;
    };
    int x19249 = ite19264;
    int x4079 = x19249 ? 0 : 1;
    return x4079; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3654)  { 
    int x3655 = -889275714;
    int x3656 = x3654._2;
    int x3657 = HASH(x3656);
    int x3658 = -862048943*(x3657);
    int x3659 = x3658<<(15);
    int x3660 = x3658 >> (-15 & (8*sizeof(x3658)-1));
    int x3661 = x3659|(x3660);
    int x3662 = x3661*(461845907);
    int x3663 = x3655;
    int x3664 = x3662^(x3663);
    int x3665 = x3664<<(13);
    int x3666 = x3664 >> (-13 & (8*sizeof(x3664)-1));
    int x3667 = x3665|(x3666);
    int x3668 = x3667*(5);
    int x3669 = x3668+(-430675100);
    x3655 = x3669;
    int x3671 = x3654._3;
    int x3672 = HASH(x3671);
    int x3673 = -862048943*(x3672);
    int x3674 = x3673<<(15);
    int x3675 = x3673 >> (-15 & (8*sizeof(x3673)-1));
    int x3676 = x3674|(x3675);
    int x3677 = x3676*(461845907);
    int x3678 = x3655;
    int x3679 = x3677^(x3678);
    int x3680 = x3679<<(13);
    int x3681 = x3679 >> (-13 & (8*sizeof(x3679)-1));
    int x3682 = x3680|(x3681);
    int x3683 = x3682*(5);
    int x3684 = x3683+(-430675100);
    x3655 = x3684;
    int x3686 = x3655;
    int x3687 = x3686^(2);
    int x3688 = x3687 >> (16 & (8*sizeof(x3687)-1));
    int x3689 = x3687^(x3688);
    int x3690 = x3689*(-2048144789);
    int x3691 = x3690 >> (13 & (8*sizeof(x3690)-1));
    int x3692 = x3690^(x3691);
    int x3693 = x3692*(-1028477387);
    int x3694 = x3693 >> (16 & (8*sizeof(x3693)-1));
    int x3695 = x3693^(x3694);
    return x3695; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3697, const struct SEntry3_III& x3698) { 
    int x3699 = x3697._1;
    int x3700 = x3698._1;
    int x3701 = x3699==(x3700);
    int x3702 = x3699>(x3700);
    int x3703 = x3702 ? 1 : -1;
    int x3704 = x3701 ? 0 : x3703;
    return x3704; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4082)  { 
    int x4083 = -889275714;
    int x4084 = x4082._2;
    int x4085 = HASH(x4084);
    int x4086 = -862048943*(x4085);
    int x4087 = x4086<<(15);
    int x4088 = x4086 >> (-15 & (8*sizeof(x4086)-1));
    int x4089 = x4087|(x4088);
    int x4090 = x4089*(461845907);
    int x4091 = x4083;
    int x4092 = x4090^(x4091);
    int x4093 = x4092<<(13);
    int x4094 = x4092 >> (-13 & (8*sizeof(x4092)-1));
    int x4095 = x4093|(x4094);
    int x4096 = x4095*(5);
    int x4097 = x4096+(-430675100);
    x4083 = x4097;
    int x4099 = x4082._3;
    int x4100 = HASH(x4099);
    int x4101 = -862048943*(x4100);
    int x4102 = x4101<<(15);
    int x4103 = x4101 >> (-15 & (8*sizeof(x4101)-1));
    int x4104 = x4102|(x4103);
    int x4105 = x4104*(461845907);
    int x4106 = x4083;
    int x4107 = x4105^(x4106);
    int x4108 = x4107<<(13);
    int x4109 = x4107 >> (-13 & (8*sizeof(x4107)-1));
    int x4110 = x4108|(x4109);
    int x4111 = x4110*(5);
    int x4112 = x4111+(-430675100);
    x4083 = x4112;
    int x4114 = x4082._4;
    int x4115 = HASH(x4114);
    int x4116 = -862048943*(x4115);
    int x4117 = x4116<<(15);
    int x4118 = x4116 >> (-15 & (8*sizeof(x4116)-1));
    int x4119 = x4117|(x4118);
    int x4120 = x4119*(461845907);
    int x4121 = x4083;
    int x4122 = x4120^(x4121);
    int x4123 = x4122<<(13);
    int x4124 = x4122 >> (-13 & (8*sizeof(x4122)-1));
    int x4125 = x4123|(x4124);
    int x4126 = x4125*(5);
    int x4127 = x4126+(-430675100);
    x4083 = x4127;
    int x4129 = x4083;
    int x4130 = x4129^(2);
    int x4131 = x4130 >> (16 & (8*sizeof(x4130)-1));
    int x4132 = x4130^(x4131);
    int x4133 = x4132*(-2048144789);
    int x4134 = x4133 >> (13 & (8*sizeof(x4133)-1));
    int x4135 = x4133^(x4134);
    int x4136 = x4135*(-1028477387);
    int x4137 = x4136 >> (16 & (8*sizeof(x4136)-1));
    int x4138 = x4136^(x4137);
    return x4138; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x4140, const struct SEntry8_IIIITIIB& x4141) { 
    int x4142 = x4140._1;
    int x4143 = x4141._1;
    int x4144 = x4142==(x4143);
    int x4145 = x4142>(x4143);
    int x4146 = x4145 ? 1 : -1;
    int x4147 = x4144 ? 0 : x4146;
    return x4147; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3970)  { 
    int x3971 = 0;
    int x3972 = x3970._1;
    int x3973 = x3972-(1);
    int x3974 = x3971;
    int x3975 = x3974*(1);
    int x3976 = x3975+(x3973);
    x3971 = x3976;
    int x3978 = x3971;
    return x3978; 
  }
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3967, const struct SEntry9_ISSSSSSDD& x3968) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3989)  { 
    int x3990 = 0;
    int x3991 = x3989._1;
    int x3992 = x3991-(1);
    int x3993 = x3990;
    int x3994 = x3993*(100000);
    int x3995 = x3994+(x3992);
    x3990 = x3995;
    int x3997 = x3990;
    return x3997; 
  }
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3986, const struct SEntry5_IISDS& x3987) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4234)  { 
    int x4235 = 0;
    int x4236 = x4234._1;
    int x4237 = x4236-(1);
    int x4238 = x4235;
    int x4239 = x4238*(10);
    int x4240 = x4239+(x4237);
    x4235 = x4240;
    int x4242 = x4234._2;
    int x4243 = x4242-(1);
    int x4244 = x4235;
    int x4245 = x4244*(1);
    int x4246 = x4245+(x4243);
    x4235 = x4246;
    int x4248 = x4235;
    return x4248; 
  }
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x4231, const struct SEntry11_IISSSSSSDDI& x4232) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4432)  { 
    int x4433 = 0;
    int x4434 = x4432._1;
    int x4435 = x4434-(1);
    int x4436 = x4433;
    int x4437 = x4436*(3000);
    int x4438 = x4437+(x4435);
    x4433 = x4438;
    int x4440 = x4432._2;
    int x4441 = x4440-(1);
    int x4442 = x4433;
    int x4443 = x4442*(10);
    int x4444 = x4443+(x4441);
    x4433 = x4444;
    int x4446 = x4432._3;
    int x4447 = x4446-(1);
    int x4448 = x4433;
    int x4449 = x4448*(1);
    int x4450 = x4449+(x4447);
    x4433 = x4450;
    int x4452 = x4433;
    return x4452; 
  }
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4429, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4430) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4538)  { 
    int x4539 = 0;
    int x4540 = x4538._1;
    int x4541 = x4540-(1);
    int x4542 = x4539;
    int x4543 = x4542*(100000);
    int x4544 = x4543+(x4541);
    x4539 = x4544;
    int x4546 = x4538._2;
    int x4547 = x4546-(1);
    int x4548 = x4539;
    int x4549 = x4548*(1);
    int x4550 = x4549+(x4547);
    x4539 = x4550;
    int x4552 = x4539;
    return x4552; 
  }
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4535, const struct SEntry17_IIISSSSSSSSSSIIIS& x4536) { 
    return 0; 
  }
};
#undef int

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblStoreType& x3764 = newOrderTbl;
newOrderTblIdx0Type& x806 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x807 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblStoreType& x3964 = historyTbl;
historyTblIdx0Type& x813 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblStoreType& x3983 = warehouseTbl;
warehouseTblIdx0Type& x818 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblStoreType& x4002 = itemTbl;
itemTblIdx0Type& x823 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblStoreType& x4226 = orderTbl;
orderTblIdx0Type& x830 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x831 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblStoreType& x4253 = districtTbl;
districtTblIdx0Type& x837 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblStoreType& x4425 = orderLineTbl;
orderLineTblIdx0Type& x842 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x843 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblStoreType& x4531 = customerTbl;
customerTblIdx0Type& x849 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x850 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblStoreType& x4557 = stockTbl;
stockTblIdx0Type& x855 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry17_IIISSSSSSSSSSIIIS x8134;
struct SEntry17_IIISSSSSSSSSSIIIS x7690;
struct SEntry9_ISSSSSSDD x8107;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7747;
struct SEntry3_III x7511;
struct SEntry10_IIIIIITIDS x7534;
struct SEntry11_IISSSSSSDDI x7657;
struct SEntry8_IIIITIIB x7524;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7908;
struct SEntry11_IISSSSSSDDI x7867;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8103;
struct SEntry5_IISDS x8082;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7538;
struct SEntry11_IISSSSSSDDI x8110;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7925;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7764;
struct SEntry9_ISSSSSSDD x7861;
struct SEntry8_IIIITIIB x7735;
struct SEntry10_IIIIIITIDS x7670;


void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    x7511._2 = x27;
    x7511._3 = x12;
    struct SEntry3_III* x12440 = x807.get(x7511);
    if((x12440!=(NULL))) {
      int x7517 = x12440->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x7517;
      x3764.del(x12440);
      int x41 = x18;
      x7524._1 = x7517;
      x7524._2 = x41;
      x7524._3 = x12;
      struct SEntry8_IIIITIIB* x12454 = x830.get(x7524);
      int x7527 = x12454->_4;
      x12454->_6 = x13;
      double x51 = 0.0;
      int x53 = x18;
      x7534._1 = x7517;
      x7534._2 = x53;
      x7534._3 = x12;
      x843.slice(x7534, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
        orderLineEntry->_7 = x11;
        double x58 = x51;
        double x7581 = orderLineEntry->_9;
        x51 = (x58+(x7581));
      
      }));
      int x66 = x18;
      x7538._1 = x7527;
      x7538._2 = x66;
      x7538._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12476 = x849.get(x7538);
      double x70 = x51;
      x12476->_17 += x70;
      x12476->_20 += 1;
    } else {
      
      int x74 = x18;
      orderIDs[(x74-(1))] = 0;
    };
    int x78 = x18;
    x18 = (x78+(1));
  };
}
void StockLevelTx(int x82, date x83, int x84, int x85, int x86, int x87) {
  x7657._1 = x86;
  x7657._2 = x85;
  struct SEntry11_IISSSSSSDDI* x12547 = x837.get(x7657);
  int x7660 = x12547->_11;
  int x97 = (x7660-(20));
  unordered_set<int> unique_ol_i_id;
  while(1) {
    
    int x101 = x97;
    if (!((x101<(x7660)))) break; 
    
    int x103 = x97;
    x7670._1 = x103;
    x7670._2 = x86;
    x7670._3 = x85;
    x843.slice(x7670, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
      int x7688 = orderLineEntry->_5;
      x7690._1 = x7688;
      x7690._2 = x85;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12561 = x855.get(x7690);
      int x7692 = x12561->_3;
      if((x7692<(x87))) {
        unique_ol_i_id.insert(x7688);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16155 = NULL;
  if((x131>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16156;
    x7747._2 = x130;
    x7747._3 = x129;
    x7747._6 = x133;
    x850.slice(x7747, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x16156.push_back(custEntry);
    
    }));
    int x16164 = x16156.size();
    int x16166 = (x16164/(2));
    int x16174 = x16156.size();
    if(((x16174%(2))==(0))) {
      int x152 = x16166;
      x16166 = (x152-(1));
    };
    sort(x16156.begin(), x16156.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7791 = c1->_4;
      PString x7792 = c2->_4;
      return ((strcmpi(x7791.data_, x7792.data_))<(0)); 
    }));
    int x16182 = x16166;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16183 = x16156[x16182];
    ite16155 = x16183;
  } else {
    
    x7764._1 = x132;
    x7764._2 = x130;
    x7764._3 = x129;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16188 = x849.get(x7764);
    ite16155 = x16188;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7732 = ite16155;
  int x7733 = x7732->_3;
  x7735._2 = x130;
  x7735._3 = x129;
  x7735._4 = x7733;
  struct SEntry8_IIIITIIB* x12651 = x831.get(x7735);
  int x184 = 0;
  int x7740 = x12651->_1;
  x184 = x7740;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  x7861._1 = x191;
  struct SEntry9_ISSSSSSDD* x12706 = x818.get(x7861);
  x12706->_9 += x198;
  x7867._1 = x192;
  x7867._2 = x191;
  struct SEntry11_IISSSSSSDDI* x12711 = x837.get(x7867);
  x12711->_10 += x198;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16254 = NULL;
  if((x193>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16255;
    x7908._2 = x195;
    x7908._3 = x194;
    x7908._6 = x197;
    x850.slice(x7908, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x16255.push_back(custEntry);
    
    }));
    int x16263 = x16255.size();
    int x16265 = (x16263/(2));
    int x16273 = x16255.size();
    if(((x16273%(2))==(0))) {
      int x230 = x16265;
      x16265 = (x230-(1));
    };
    sort(x16255.begin(), x16255.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7972 = c1->_4;
      PString x7973 = c2->_4;
      return ((strcmpi(x7972.data_, x7973.data_))<(0)); 
    }));
    int x16281 = x16265;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16282 = x16255[x16281];
    ite16254 = x16282;
  } else {
    
    x7925._1 = x196;
    x7925._2 = x195;
    x7925._3 = x194;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16287 = x849.get(x7925);
    ite16254 = x16287;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7872 = ite16254;
  PString x7873 = x7872->_21;
  PString x7874 = x7872->_14;
  char* x17523 = strstr(x7874.data_, "BC");
  if((x17523!=(NULL))) {
    int x7877 = x7872->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x7877, x195, x194, x192, x191, x198, IntToStrdate(x189), x7873.data_);
    x7872->_17 += x198;
    x7872->_21 = c_new_data;
  } else {
    
    x7872->_17 += x198;
  };
  PString x7884 = x12706->_2;
  PString x7885 = x12711->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x7884.data_, x7885.data_);
  int x7888 = x7872->_1;
  struct SEntry8_IIIIITDS* x17121 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x17121, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x17121->_1 = x7888; x17121->_2 = x195; x17121->_3 = x194; x17121->_4 = x192; x17121->_5 = x191; x17121->_6 = x189; x17121->_7 = x198; x17121->_8 = h_data;
  x3964.add(x17121);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite16545 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x16546 = x301;
      ite16545 = x16546;
    } else {
      
      ite16545 = 0;
    };
    int x16377 = ite16545;
    if (!(x16377)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    x8082._1 = x305;
    struct SEntry5_IISDS* x12845 = x823.get(x8082);
    if((x12845==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x8089 = x12845->_3;
      x284[x312] = x8089;
      int x315 = x289;
      double x8092 = x12845->_4;
      x283[x315] = x8092;
      int x318 = x289;
      PString x8095 = x12845->_5;
      idata[x318] = x8095;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    x8103._1 = x277;
    x8103._2 = x276;
    x8103._3 = x275;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12868 = x849.get(x8103);
    x8107._1 = x275;
    struct SEntry9_ISSSSSSDD* x12871 = x818.get(x8107);
    x8110._1 = x276;
    x8110._2 = x275;
    struct SEntry11_IISSSSSSDDI* x12875 = x837.get(x8110);
    int x8112 = x12875->_11;
    x12875->_11 += 1;
    struct SEntry8_IIIITIIB* x17172 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x17172, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x17172->_1 = x8112; x17172->_2 = x276; x17172->_3 = x275; x17172->_4 = x277; x17172->_5 = x273; x17172->_6 = -1; x17172->_7 = x278; x17172->_8 = (x279>(0));
    x4226.add(x17172);
    struct SEntry3_III* x17176 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x17176, 0, 1 * sizeof(struct SEntry3_III));
    x17176->_1 = x8112; x17176->_2 = x276; x17176->_3 = x275;
    x3764.add(x17176);
    double x352 = 0.0;
    x289 = 0;
    while(1) {
      
      int x355 = x289;
      if (!((x355<(x278)))) break; 
      
      int x358 = x289;
      int ol_supply_w_id = x281[x358];
      int x361 = x289;
      int ol_i_id = x280[x361];
      int x364 = x289;
      int ol_quantity = x282[x364];
      x8134._1 = ol_i_id;
      x8134._2 = ol_supply_w_id;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12899 = x855.get(x8134);
      PString ite16431 = PString();
      if((x276==(1))) {
        PString x16432 = x12899->_4;
        ite16431 = x16432;
      } else {
        
        PString ite16436 = PString();
        if((x276==(2))) {
          PString x16437 = x12899->_5;
          ite16436 = x16437;
        } else {
          
          PString ite16441 = PString();
          if((x276==(3))) {
            PString x16442 = x12899->_6;
            ite16441 = x16442;
          } else {
            
            PString ite16446 = PString();
            if((x276==(4))) {
              PString x16447 = x12899->_7;
              ite16446 = x16447;
            } else {
              
              PString ite16451 = PString();
              if((x276==(5))) {
                PString x16452 = x12899->_8;
                ite16451 = x16452;
              } else {
                
                PString ite16456 = PString();
                if((x276==(6))) {
                  PString x16457 = x12899->_9;
                  ite16456 = x16457;
                } else {
                  
                  PString ite16461 = PString();
                  if((x276==(7))) {
                    PString x16462 = x12899->_10;
                    ite16461 = x16462;
                  } else {
                    
                    PString ite16466 = PString();
                    if((x276==(8))) {
                      PString x16467 = x12899->_11;
                      ite16466 = x16467;
                    } else {
                      
                      PString ite16471 = PString();
                      if((x276==(9))) {
                        PString x16472 = x12899->_12;
                        ite16471 = x16472;
                      } else {
                        
                        PString x16474 = x12899->_13;
                        ite16471 = x16474;
                      };
                      PString x16470 = ite16471;
                      ite16466 = x16470;
                    };
                    PString x16465 = ite16466;
                    ite16461 = x16465;
                  };
                  PString x16460 = ite16461;
                  ite16456 = x16460;
                };
                PString x16455 = ite16456;
                ite16451 = x16455;
              };
              PString x16450 = ite16451;
              ite16446 = x16450;
            };
            PString x16445 = ite16446;
            ite16441 = x16445;
          };
          PString x16440 = ite16441;
          ite16436 = x16440;
        };
        PString x16435 = ite16436;
        ite16431 = x16435;
      };
      PString ol_dist_info = ite16431;
      int x8164 = x12899->_3;
      int x401 = x289;
      x285[x401] = x8164;
      PString x8167 = x12868->_14;
      char* x17743 = strstr(x8167.data_, "original");
      int ite16672 = 0;
      if((x17743!=(NULL))) {
        
        PString x8170 = x12899->_17;
        char* x17749 = strstr(x8170.data_, "original");
        int x16673 = (x17749!=(NULL));
        ite16672 = x16673;
      } else {
        
        ite16672 = 0;
      };
      int x16499 = ite16672;
      if(x16499) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      x12899->_3 = (x8164-(ol_quantity));
      if((x8164<=(ol_quantity))) {
        x12899->_3 += 91;
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      double x8187 = x12868->_16;
      double x8188 = x12871->_8;
      double x8189 = x12875->_9;
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(x8188))+(x8189))))*((1.0-(x8187)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      struct SEntry10_IIIIIITIDS* x17303 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x17303, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x17303->_1 = x8112; x17303->_2 = x276; x17303->_3 = x275; x17303->_4 = (x446+(1)); x17303->_5 = ol_i_id; x17303->_6 = ol_supply_w_id; x17303->_7 = NULL; x17303->_8 = ol_quantity; x17303->_9 = ol_amount; x17303->_10 = ol_dist_info;
      x4425.add(x17303);
      int x451 = x289;
      x289 = (x451+(1));
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
    if(warehouseTblPrimaryIdx == tpcc.wareRes){
       cout << "Warehouse results are correct" << endl;
    }
    if(districtTblPrimaryIdx == tpcc.distRes){
       cout << "District results are correct" << endl;
    }
    if(customerTblPrimaryIdx == tpcc.custRes){
       cout << "Customer results are correct" << endl;
    }
    if(orderTblPrimaryIdx == tpcc.ordRes){
       cout << "Order results are correct" << endl;
    }
    if(orderLineTblPrimaryIdx == tpcc.ordLRes){
       cout << "OrderLine results are correct" << endl;
    }
    if(newOrderTblPrimaryIdx == tpcc.newOrdRes){
       cout << "NewOrder results are correct" << endl;
    }
    if(itemTblPrimaryIdx == tpcc.itemRes){
       cout << "Item results are correct" << endl;
    }
    if(stockTblPrimaryIdx == tpcc.stockRes){
       cout << "Stock results are correct" << endl;
    }
    if(historyTblPrimaryIdx == tpcc.histRes){
       cout << "History results are correct" << endl;
    }
  
  #endif
  
        
}
/* ----------- FUNCTIONS ----------- */
