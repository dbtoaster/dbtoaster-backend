#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap2.hpp>
using namespace std;

FORCE_INLINE size_t HASH(int x) { return x; }
FORCE_INLINE size_t HASH(char *x) {
   size_t hash = 7;
   int N = strlen(x);
   for (int i = 0; i < (N < 100 ? N : 100); i++) {
      hash = hash * 31 + x[i];
   }
   return hash;
}

int strcmpi(const char* This, const char *That) {
   int i = 0;
   while(true) {
      char c1 = tolower(This[i]);
      char c2 = tolower(That[i]);
      if(!c1)
        return c2 ? -1 : 0;
      else if(!c2)
        return 1;
      else if (c1 == c2) {
          i++;
          continue;
      }
      else if (c1 < c2)
          return -1;
      else return 1;
   }
}

typedef size_t Date;
char* IntToStrDate(Date);

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

     
struct SEntry5_IISDS;
struct SEntry11_IISSSSSSDDI;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS;
struct SEntry8_IIIITIIB;
struct SEntry3_III;
struct SEntry8_IIIIITDS;
struct SEntry17_IIISSSSSSSSSSIIIS;
struct SEntry10_IIIIIITIDS;
struct SEntry9_ISSSSSSDD;
struct SEntry5_IISDS {
  int _1;
  int _2;
  char* _3;
  double _4;
  char* _5;
};

struct SEntry11_IISSSSSSDDI {
  int _1;
  int _2;
  char* _3;
  char* _4;
  char* _5;
  char* _6;
  char* _7;
  char* _8;
  double _9;
  double _10;
  int _11;
};

struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;
  int _2;
  int _3;
  char* _4;
  char* _5;
  char* _6;
  char* _7;
  char* _8;
  char* _9;
  char* _10;
  char* _11;
  char* _12;
  Date _13;
  char* _14;
  double _15;
  double _16;
  double _17;
  double _18;
  int _19;
  int _20;
  char* _21;
};

struct SEntry8_IIIITIIB {
  int _1;
  int _2;
  int _3;
  int _4;
  Date _5;
  int _6;
  int _7;
  int _8;
};

struct SEntry3_III {
  int _1;
  int _2;
  int _3;
};

struct SEntry8_IIIIITDS {
  int _1;
  int _2;
  int _3;
  int _4;
  int _5;
  Date _6;
  double _7;
  char* _8;
};

struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;
  int _2;
  int _3;
  char* _4;
  char* _5;
  char* _6;
  char* _7;
  char* _8;
  char* _9;
  char* _10;
  char* _11;
  char* _12;
  char* _13;
  int _14;
  int _15;
  int _16;
  char* _17;
};

struct SEntry10_IIIIIITIDS {
  int _1;
  int _2;
  int _3;
  int _4;
  int _5;
  int _6;
  Date _7;
  int _8;
  double _9;
  char* _10;
};

struct SEntry9_ISSSSSSDD {
  int _1;
  char* _2;
  char* _3;
  char* _4;
  char* _5;
  char* _6;
  char* _7;
  double _8;
  double _9;
};
bool operator== (const SEntry5_IISDS& o1, const SEntry5_IISDS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  !strcmpi(o1._3, o2._3) && 
  (fabs(o1._4 - o2._4) < 0.01) && 
  !strcmpi(o1._5, o2._5);
}
bool operator== (const SEntry11_IISSSSSSDDI& o1, const SEntry11_IISSSSSSDDI& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  !strcmpi(o1._3, o2._3) && 
  !strcmpi(o1._4, o2._4) && 
  !strcmpi(o1._5, o2._5) && 
  !strcmpi(o1._6, o2._6) && 
  !strcmpi(o1._7, o2._7) && 
  !strcmpi(o1._8, o2._8) && 
  (fabs(o1._9 - o2._9) < 0.01) && 
  (fabs(o1._10 - o2._10) < 0.01) && 
  o1._11 == o2._11;
}
bool operator== (const SEntry21_IIISSSSSSSSSTSDDDDIIS& o1, const SEntry21_IIISSSSSSSSSTSDDDDIIS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  !strcmpi(o1._4, o2._4) && 
  !strcmpi(o1._5, o2._5) && 
  !strcmpi(o1._6, o2._6) && 
  !strcmpi(o1._7, o2._7) && 
  !strcmpi(o1._8, o2._8) && 
  !strcmpi(o1._9, o2._9) && 
  !strcmpi(o1._10, o2._10) && 
  !strcmpi(o1._11, o2._11) && 
  !strcmpi(o1._12, o2._12) && 
  o1._13 == o2._13 && 
  !strcmpi(o1._14, o2._14) && 
  (fabs(o1._15 - o2._15) < 0.01) && 
  (fabs(o1._16 - o2._16) < 0.01) && 
  (fabs(o1._17 - o2._17) < 0.01) && 
  (fabs(o1._18 - o2._18) < 0.01) && 
  o1._19 == o2._19 && 
  o1._20 == o2._20 && 
  !strcmpi(o1._21, o2._21);
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
  !strcmpi(o1._8, o2._8);
}
bool operator== (const SEntry17_IIISSSSSSSSSSIIIS& o1, const SEntry17_IIISSSSSSSSSSIIIS& o2) {
  return o1._1 == o2._1 && 
  o1._2 == o2._2 && 
  o1._3 == o2._3 && 
  !strcmpi(o1._4, o2._4) && 
  !strcmpi(o1._5, o2._5) && 
  !strcmpi(o1._6, o2._6) && 
  !strcmpi(o1._7, o2._7) && 
  !strcmpi(o1._8, o2._8) && 
  !strcmpi(o1._9, o2._9) && 
  !strcmpi(o1._10, o2._10) && 
  !strcmpi(o1._11, o2._11) && 
  !strcmpi(o1._12, o2._12) && 
  !strcmpi(o1._13, o2._13) && 
  o1._14 == o2._14 && 
  o1._15 == o2._15 && 
  o1._16 == o2._16 && 
  !strcmpi(o1._17, o2._17);
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
  !strcmpi(o1._10, o2._10);
}
bool operator== (const SEntry9_ISSSSSSDD& o1, const SEntry9_ISSSSSSDD& o2) {
  return o1._1 == o2._1 && 
  !strcmpi(o1._2, o2._2) && 
  !strcmpi(o1._3, o2._3) && 
  !strcmpi(o1._4, o2._4) && 
  !strcmpi(o1._5, o2._5) && 
  !strcmpi(o1._6, o2._6) && 
  !strcmpi(o1._7, o2._7) && 
  (fabs(o1._8 - o2._8) < 0.01) && 
  (fabs(o1._9 - o2._9) < 0.01);
}
#define int unsigned int
 struct SEntry10_IIIIIITIDS_Idx1234 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4117)  { 
    int x4118 = -889275714;
    int x4119 = x4117._1;
    int x4120 = HASH(x4119);
    int x4121 = -862048943*(x4120);
    int x4122 = x4121<<(15);
    int x4123 = x4121 >> (-15 & (8*sizeof(x4121)-1));
    int x4124 = x4122|(x4123);
    int x4125 = x4124*(461845907);
    int x4126 = x4118;
    int x4127 = x4125^(x4126);
    int x4128 = x4127<<(13);
    int x4129 = x4127 >> (-13 & (8*sizeof(x4127)-1));
    int x4130 = x4128|(x4129);
    int x4131 = x4130*(5);
    int x4132 = x4131+(-430675100);
    x4118 = x4132;
    int x4134 = x4117._2;
    int x4135 = HASH(x4134);
    int x4136 = -862048943*(x4135);
    int x4137 = x4136<<(15);
    int x4138 = x4136 >> (-15 & (8*sizeof(x4136)-1));
    int x4139 = x4137|(x4138);
    int x4140 = x4139*(461845907);
    int x4141 = x4118;
    int x4142 = x4140^(x4141);
    int x4143 = x4142<<(13);
    int x4144 = x4142 >> (-13 & (8*sizeof(x4142)-1));
    int x4145 = x4143|(x4144);
    int x4146 = x4145*(5);
    int x4147 = x4146+(-430675100);
    x4118 = x4147;
    int x4149 = x4117._3;
    int x4150 = HASH(x4149);
    int x4151 = -862048943*(x4150);
    int x4152 = x4151<<(15);
    int x4153 = x4151 >> (-15 & (8*sizeof(x4151)-1));
    int x4154 = x4152|(x4153);
    int x4155 = x4154*(461845907);
    int x4156 = x4118;
    int x4157 = x4155^(x4156);
    int x4158 = x4157<<(13);
    int x4159 = x4157 >> (-13 & (8*sizeof(x4157)-1));
    int x4160 = x4158|(x4159);
    int x4161 = x4160*(5);
    int x4162 = x4161+(-430675100);
    x4118 = x4162;
    int x4164 = x4117._4;
    int x4165 = HASH(x4164);
    int x4166 = -862048943*(x4165);
    int x4167 = x4166<<(15);
    int x4168 = x4166 >> (-15 & (8*sizeof(x4166)-1));
    int x4169 = x4167|(x4168);
    int x4170 = x4169*(461845907);
    int x4171 = x4118;
    int x4172 = x4170^(x4171);
    int x4173 = x4172<<(13);
    int x4174 = x4172 >> (-13 & (8*sizeof(x4172)-1));
    int x4175 = x4173|(x4174);
    int x4176 = x4175*(5);
    int x4177 = x4176+(-430675100);
    x4118 = x4177;
    int x4179 = x4118;
    int x4180 = x4179^(2);
    int x4181 = x4180 >> (16 & (8*sizeof(x4180)-1));
    int x4182 = x4180^(x4181);
    int x4183 = x4182*(-2048144789);
    int x4184 = x4183 >> (13 & (8*sizeof(x4183)-1));
    int x4185 = x4183^(x4184);
    int x4186 = x4185*(-1028477387);
    int x4187 = x4186 >> (16 & (8*sizeof(x4186)-1));
    int x4188 = x4186^(x4187);
    return x4188; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry10_IIIIIITIDS& x4190, const struct SEntry10_IIIIIITIDS& x4191) { 
    int x4192 = x4190._1;
    int x4193 = x4191._1;
    int x4194 = x4192==(x4193);
    int ite17914 = 0;
    if(x4194) {
      
      int x4195 = x4190._2;
      int x4196 = x4191._2;
      int x4197 = x4195==(x4196);
      int x17915 = x4197;
      ite17914 = x17915;
    } else {
      
      ite17914 = 0;
    };
    int x17904 = ite17914;
    int ite17923 = 0;
    if(x17904) {
      
      int x4199 = x4190._3;
      int x4200 = x4191._3;
      int x4201 = x4199==(x4200);
      int x17924 = x4201;
      ite17923 = x17924;
    } else {
      
      ite17923 = 0;
    };
    int x17906 = ite17923;
    int ite17932 = 0;
    if(x17906) {
      
      int x4203 = x4190._4;
      int x4204 = x4191._4;
      int x4205 = x4203==(x4204);
      int x17933 = x4205;
      ite17932 = x17933;
    } else {
      
      ite17932 = 0;
    };
    int x17908 = ite17932;
    int x4207 = x17908 ? 0 : 1;
    return x4207; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4011)  { 
    int x4012 = -889275714;
    int x4013 = x4011._2;
    int x4014 = HASH(x4013);
    int x4015 = -862048943*(x4014);
    int x4016 = x4015<<(15);
    int x4017 = x4015 >> (-15 & (8*sizeof(x4015)-1));
    int x4018 = x4016|(x4017);
    int x4019 = x4018*(461845907);
    int x4020 = x4012;
    int x4021 = x4019^(x4020);
    int x4022 = x4021<<(13);
    int x4023 = x4021 >> (-13 & (8*sizeof(x4021)-1));
    int x4024 = x4022|(x4023);
    int x4025 = x4024*(5);
    int x4026 = x4025+(-430675100);
    x4012 = x4026;
    int x4028 = x4011._3;
    int x4029 = HASH(x4028);
    int x4030 = -862048943*(x4029);
    int x4031 = x4030<<(15);
    int x4032 = x4030 >> (-15 & (8*sizeof(x4030)-1));
    int x4033 = x4031|(x4032);
    int x4034 = x4033*(461845907);
    int x4035 = x4012;
    int x4036 = x4034^(x4035);
    int x4037 = x4036<<(13);
    int x4038 = x4036 >> (-13 & (8*sizeof(x4036)-1));
    int x4039 = x4037|(x4038);
    int x4040 = x4039*(5);
    int x4041 = x4040+(-430675100);
    x4012 = x4041;
    int x4043 = x4011._4;
    int x4044 = HASH(x4043);
    int x4045 = -862048943*(x4044);
    int x4046 = x4045<<(15);
    int x4047 = x4045 >> (-15 & (8*sizeof(x4045)-1));
    int x4048 = x4046|(x4047);
    int x4049 = x4048*(461845907);
    int x4050 = x4012;
    int x4051 = x4049^(x4050);
    int x4052 = x4051<<(13);
    int x4053 = x4051 >> (-13 & (8*sizeof(x4051)-1));
    int x4054 = x4052|(x4053);
    int x4055 = x4054*(5);
    int x4056 = x4055+(-430675100);
    x4012 = x4056;
    int x4058 = x4012;
    int x4059 = x4058^(2);
    int x4060 = x4059 >> (16 & (8*sizeof(x4059)-1));
    int x4061 = x4059^(x4060);
    int x4062 = x4061*(-2048144789);
    int x4063 = x4062 >> (13 & (8*sizeof(x4062)-1));
    int x4064 = x4062^(x4063);
    int x4065 = x4064*(-1028477387);
    int x4066 = x4065 >> (16 & (8*sizeof(x4065)-1));
    int x4067 = x4065^(x4066);
    return x4067; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x4069, const struct SEntry8_IIIITIIB& x4070) { 
    int x4071 = x4069._2;
    int x4072 = x4070._2;
    int x4073 = x4071==(x4072);
    int ite18040 = 0;
    if(x4073) {
      
      int x4074 = x4069._3;
      int x4075 = x4070._3;
      int x4076 = x4074==(x4075);
      int x18041 = x4076;
      ite18040 = x18041;
    } else {
      
      ite18040 = 0;
    };
    int x18032 = ite18040;
    int ite18049 = 0;
    if(x18032) {
      
      int x4078 = x4069._4;
      int x4079 = x4070._4;
      int x4080 = x4078==(x4079);
      int x18050 = x4080;
      ite18049 = x18050;
    } else {
      
      ite18049 = 0;
    };
    int x18034 = ite18049;
    int x4082 = x18034 ? 0 : 1;
    return x4082; 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3441)  { 
    int x3442 = -889275714;
    int x3443 = x3441._1;
    int x3444 = HASH(x3443);
    int x3445 = -862048943*(x3444);
    int x3446 = x3445<<(15);
    int x3447 = x3445 >> (-15 & (8*sizeof(x3445)-1));
    int x3448 = x3446|(x3447);
    int x3449 = x3448*(461845907);
    int x3450 = x3442;
    int x3451 = x3449^(x3450);
    int x3452 = x3451<<(13);
    int x3453 = x3451 >> (-13 & (8*sizeof(x3451)-1));
    int x3454 = x3452|(x3453);
    int x3455 = x3454*(5);
    int x3456 = x3455+(-430675100);
    x3442 = x3456;
    int x3458 = x3441._2;
    int x3459 = HASH(x3458);
    int x3460 = -862048943*(x3459);
    int x3461 = x3460<<(15);
    int x3462 = x3460 >> (-15 & (8*sizeof(x3460)-1));
    int x3463 = x3461|(x3462);
    int x3464 = x3463*(461845907);
    int x3465 = x3442;
    int x3466 = x3464^(x3465);
    int x3467 = x3466<<(13);
    int x3468 = x3466 >> (-13 & (8*sizeof(x3466)-1));
    int x3469 = x3467|(x3468);
    int x3470 = x3469*(5);
    int x3471 = x3470+(-430675100);
    x3442 = x3471;
    int x3473 = x3441._3;
    int x3474 = HASH(x3473);
    int x3475 = -862048943*(x3474);
    int x3476 = x3475<<(15);
    int x3477 = x3475 >> (-15 & (8*sizeof(x3475)-1));
    int x3478 = x3476|(x3477);
    int x3479 = x3478*(461845907);
    int x3480 = x3442;
    int x3481 = x3479^(x3480);
    int x3482 = x3481<<(13);
    int x3483 = x3481 >> (-13 & (8*sizeof(x3481)-1));
    int x3484 = x3482|(x3483);
    int x3485 = x3484*(5);
    int x3486 = x3485+(-430675100);
    x3442 = x3486;
    int x3488 = x3442;
    int x3489 = x3488^(2);
    int x3490 = x3489 >> (16 & (8*sizeof(x3489)-1));
    int x3491 = x3489^(x3490);
    int x3492 = x3491*(-2048144789);
    int x3493 = x3492 >> (13 & (8*sizeof(x3492)-1));
    int x3494 = x3492^(x3493);
    int x3495 = x3494*(-1028477387);
    int x3496 = x3495 >> (16 & (8*sizeof(x3495)-1));
    int x3497 = x3495^(x3496);
    return x3497; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3499, const struct SEntry3_III& x3500) { 
    int x3501 = x3499._1;
    int x3502 = x3500._1;
    int x3503 = x3501==(x3502);
    int ite18148 = 0;
    if(x3503) {
      
      int x3504 = x3499._2;
      int x3505 = x3500._2;
      int x3506 = x3504==(x3505);
      int x18149 = x3506;
      ite18148 = x18149;
    } else {
      
      ite18148 = 0;
    };
    int x18140 = ite18148;
    int ite18157 = 0;
    if(x18140) {
      
      int x3508 = x3499._3;
      int x3509 = x3500._3;
      int x3510 = x3508==(x3509);
      int x18158 = x3510;
      ite18157 = x18158;
    } else {
      
      ite18157 = 0;
    };
    int x18142 = ite18157;
    int x3512 = x18142 ? 0 : 1;
    return x3512; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4210)  { 
    int x4211 = -889275714;
    int x4212 = x4210._1;
    int x4213 = HASH(x4212);
    int x4214 = -862048943*(x4213);
    int x4215 = x4214<<(15);
    int x4216 = x4214 >> (-15 & (8*sizeof(x4214)-1));
    int x4217 = x4215|(x4216);
    int x4218 = x4217*(461845907);
    int x4219 = x4211;
    int x4220 = x4218^(x4219);
    int x4221 = x4220<<(13);
    int x4222 = x4220 >> (-13 & (8*sizeof(x4220)-1));
    int x4223 = x4221|(x4222);
    int x4224 = x4223*(5);
    int x4225 = x4224+(-430675100);
    x4211 = x4225;
    int x4227 = x4210._2;
    int x4228 = HASH(x4227);
    int x4229 = -862048943*(x4228);
    int x4230 = x4229<<(15);
    int x4231 = x4229 >> (-15 & (8*sizeof(x4229)-1));
    int x4232 = x4230|(x4231);
    int x4233 = x4232*(461845907);
    int x4234 = x4211;
    int x4235 = x4233^(x4234);
    int x4236 = x4235<<(13);
    int x4237 = x4235 >> (-13 & (8*sizeof(x4235)-1));
    int x4238 = x4236|(x4237);
    int x4239 = x4238*(5);
    int x4240 = x4239+(-430675100);
    x4211 = x4240;
    int x4242 = x4210._3;
    int x4243 = HASH(x4242);
    int x4244 = -862048943*(x4243);
    int x4245 = x4244<<(15);
    int x4246 = x4244 >> (-15 & (8*sizeof(x4244)-1));
    int x4247 = x4245|(x4246);
    int x4248 = x4247*(461845907);
    int x4249 = x4211;
    int x4250 = x4248^(x4249);
    int x4251 = x4250<<(13);
    int x4252 = x4250 >> (-13 & (8*sizeof(x4250)-1));
    int x4253 = x4251|(x4252);
    int x4254 = x4253*(5);
    int x4255 = x4254+(-430675100);
    x4211 = x4255;
    int x4257 = x4211;
    int x4258 = x4257^(2);
    int x4259 = x4258 >> (16 & (8*sizeof(x4258)-1));
    int x4260 = x4258^(x4259);
    int x4261 = x4260*(-2048144789);
    int x4262 = x4261 >> (13 & (8*sizeof(x4261)-1));
    int x4263 = x4261^(x4262);
    int x4264 = x4263*(-1028477387);
    int x4265 = x4264 >> (16 & (8*sizeof(x4264)-1));
    int x4266 = x4264^(x4265);
    return x4266; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry10_IIIIIITIDS& x4268, const struct SEntry10_IIIIIITIDS& x4269) { 
    int x4270 = x4268._1;
    int x4271 = x4269._1;
    int x4272 = x4270==(x4271);
    int ite18256 = 0;
    if(x4272) {
      
      int x4273 = x4268._2;
      int x4274 = x4269._2;
      int x4275 = x4273==(x4274);
      int x18257 = x4275;
      ite18256 = x18257;
    } else {
      
      ite18256 = 0;
    };
    int x18248 = ite18256;
    int ite18265 = 0;
    if(x18248) {
      
      int x4277 = x4268._3;
      int x4278 = x4269._3;
      int x4279 = x4277==(x4278);
      int x18266 = x4279;
      ite18265 = x18266;
    } else {
      
      ite18265 = 0;
    };
    int x18250 = ite18265;
    int x4281 = x18250 ? 0 : 1;
    return x4281; 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3568)  { 
    int x3569 = -889275714;
    int x3570 = x3568._2;
    int x3571 = HASH(x3570);
    int x3572 = -862048943*(x3571);
    int x3573 = x3572<<(15);
    int x3574 = x3572 >> (-15 & (8*sizeof(x3572)-1));
    int x3575 = x3573|(x3574);
    int x3576 = x3575*(461845907);
    int x3577 = x3569;
    int x3578 = x3576^(x3577);
    int x3579 = x3578<<(13);
    int x3580 = x3578 >> (-13 & (8*sizeof(x3578)-1));
    int x3581 = x3579|(x3580);
    int x3582 = x3581*(5);
    int x3583 = x3582+(-430675100);
    x3569 = x3583;
    int x3585 = x3568._3;
    int x3586 = HASH(x3585);
    int x3587 = -862048943*(x3586);
    int x3588 = x3587<<(15);
    int x3589 = x3587 >> (-15 & (8*sizeof(x3587)-1));
    int x3590 = x3588|(x3589);
    int x3591 = x3590*(461845907);
    int x3592 = x3569;
    int x3593 = x3591^(x3592);
    int x3594 = x3593<<(13);
    int x3595 = x3593 >> (-13 & (8*sizeof(x3593)-1));
    int x3596 = x3594|(x3595);
    int x3597 = x3596*(5);
    int x3598 = x3597+(-430675100);
    x3569 = x3598;
    int x3600 = x3569;
    int x3601 = x3600^(2);
    int x3602 = x3601 >> (16 & (8*sizeof(x3601)-1));
    int x3603 = x3601^(x3602);
    int x3604 = x3603*(-2048144789);
    int x3605 = x3604 >> (13 & (8*sizeof(x3604)-1));
    int x3606 = x3604^(x3605);
    int x3607 = x3606*(-1028477387);
    int x3608 = x3607 >> (16 & (8*sizeof(x3607)-1));
    int x3609 = x3607^(x3608);
    return x3609; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3611, const struct SEntry3_III& x3612) { 
    int x3613 = x3611._2;
    int x3614 = x3612._2;
    int x3615 = x3613==(x3614);
    int ite18347 = 0;
    if(x3615) {
      
      int x3616 = x3611._3;
      int x3617 = x3612._3;
      int x3618 = x3616==(x3617);
      int x18348 = x3618;
      ite18347 = x18348;
    } else {
      
      ite18347 = 0;
    };
    int x18341 = ite18347;
    int x3620 = x18341 ? 0 : 1;
    return x3620; 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3630)  { 
    int x3631 = -889275714;
    int x3632 = x3630._1;
    int x3633 = HASH(x3632);
    int x3634 = -862048943*(x3633);
    int x3635 = x3634<<(15);
    int x3636 = x3634 >> (-15 & (8*sizeof(x3634)-1));
    int x3637 = x3635|(x3636);
    int x3638 = x3637*(461845907);
    int x3639 = x3631;
    int x3640 = x3638^(x3639);
    int x3641 = x3640<<(13);
    int x3642 = x3640 >> (-13 & (8*sizeof(x3640)-1));
    int x3643 = x3641|(x3642);
    int x3644 = x3643*(5);
    int x3645 = x3644+(-430675100);
    x3631 = x3645;
    int x3647 = x3630._2;
    int x3648 = HASH(x3647);
    int x3649 = -862048943*(x3648);
    int x3650 = x3649<<(15);
    int x3651 = x3649 >> (-15 & (8*sizeof(x3649)-1));
    int x3652 = x3650|(x3651);
    int x3653 = x3652*(461845907);
    int x3654 = x3631;
    int x3655 = x3653^(x3654);
    int x3656 = x3655<<(13);
    int x3657 = x3655 >> (-13 & (8*sizeof(x3655)-1));
    int x3658 = x3656|(x3657);
    int x3659 = x3658*(5);
    int x3660 = x3659+(-430675100);
    x3631 = x3660;
    int x3662 = x3630._3;
    int x3663 = HASH(x3662);
    int x3664 = -862048943*(x3663);
    int x3665 = x3664<<(15);
    int x3666 = x3664 >> (-15 & (8*sizeof(x3664)-1));
    int x3667 = x3665|(x3666);
    int x3668 = x3667*(461845907);
    int x3669 = x3631;
    int x3670 = x3668^(x3669);
    int x3671 = x3670<<(13);
    int x3672 = x3670 >> (-13 & (8*sizeof(x3670)-1));
    int x3673 = x3671|(x3672);
    int x3674 = x3673*(5);
    int x3675 = x3674+(-430675100);
    x3631 = x3675;
    int x3677 = x3630._4;
    int x3678 = HASH(x3677);
    int x3679 = -862048943*(x3678);
    int x3680 = x3679<<(15);
    int x3681 = x3679 >> (-15 & (8*sizeof(x3679)-1));
    int x3682 = x3680|(x3681);
    int x3683 = x3682*(461845907);
    int x3684 = x3631;
    int x3685 = x3683^(x3684);
    int x3686 = x3685<<(13);
    int x3687 = x3685 >> (-13 & (8*sizeof(x3685)-1));
    int x3688 = x3686|(x3687);
    int x3689 = x3688*(5);
    int x3690 = x3689+(-430675100);
    x3631 = x3690;
    int x3692 = x3630._5;
    int x3693 = HASH(x3692);
    int x3694 = -862048943*(x3693);
    int x3695 = x3694<<(15);
    int x3696 = x3694 >> (-15 & (8*sizeof(x3694)-1));
    int x3697 = x3695|(x3696);
    int x3698 = x3697*(461845907);
    int x3699 = x3631;
    int x3700 = x3698^(x3699);
    int x3701 = x3700<<(13);
    int x3702 = x3700 >> (-13 & (8*sizeof(x3700)-1));
    int x3703 = x3701|(x3702);
    int x3704 = x3703*(5);
    int x3705 = x3704+(-430675100);
    x3631 = x3705;
    Date x3707 = x3630._6;
    int x3708 = HASH(x3707);
    int x3709 = -862048943*(x3708);
    int x3710 = x3709<<(15);
    int x3711 = x3709 >> (-15 & (8*sizeof(x3709)-1));
    int x3712 = x3710|(x3711);
    int x3713 = x3712*(461845907);
    int x3714 = x3631;
    int x3715 = x3713^(x3714);
    int x3716 = x3715<<(13);
    int x3717 = x3715 >> (-13 & (8*sizeof(x3715)-1));
    int x3718 = x3716|(x3717);
    int x3719 = x3718*(5);
    int x3720 = x3719+(-430675100);
    x3631 = x3720;
    double x3722 = x3630._7;
    int x3723 = HASH(x3722);
    int x3724 = -862048943*(x3723);
    int x3725 = x3724<<(15);
    int x3726 = x3724 >> (-15 & (8*sizeof(x3724)-1));
    int x3727 = x3725|(x3726);
    int x3728 = x3727*(461845907);
    int x3729 = x3631;
    int x3730 = x3728^(x3729);
    int x3731 = x3730<<(13);
    int x3732 = x3730 >> (-13 & (8*sizeof(x3730)-1));
    int x3733 = x3731|(x3732);
    int x3734 = x3733*(5);
    int x3735 = x3734+(-430675100);
    x3631 = x3735;
    char* x3737 = x3630._8;
    int x3738 = HASH(x3737);
    int x3739 = -862048943*(x3738);
    int x3740 = x3739<<(15);
    int x3741 = x3739 >> (-15 & (8*sizeof(x3739)-1));
    int x3742 = x3740|(x3741);
    int x3743 = x3742*(461845907);
    int x3744 = x3631;
    int x3745 = x3743^(x3744);
    int x3746 = x3745<<(13);
    int x3747 = x3745 >> (-13 & (8*sizeof(x3745)-1));
    int x3748 = x3746|(x3747);
    int x3749 = x3748*(5);
    int x3750 = x3749+(-430675100);
    x3631 = x3750;
    int x3752 = x3631;
    int x3753 = x3752^(2);
    int x3754 = x3753 >> (16 & (8*sizeof(x3753)-1));
    int x3755 = x3753^(x3754);
    int x3756 = x3755*(-2048144789);
    int x3757 = x3756 >> (13 & (8*sizeof(x3756)-1));
    int x3758 = x3756^(x3757);
    int x3759 = x3758*(-1028477387);
    int x3760 = x3759 >> (16 & (8*sizeof(x3759)-1));
    int x3761 = x3759^(x3760);
    return x3761; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIIITDS& x3763, const struct SEntry8_IIIIITDS& x3764) { 
    int x3765 = x3763._1;
    int x3766 = x3764._1;
    int x3767 = x3765==(-1);
    int ite18524 = 0;
    if(x3767) {
      ite18524 = 1;
    } else {
      
      
      int x3768 = x3766==(-1);
      int x18526 = x3768;
      ite18524 = x18526;
    };
    int x18504 = ite18524;
    int ite18531 = 0;
    if(x18504) {
      ite18531 = 1;
    } else {
      
      
      int x3770 = x3765==(x3766);
      int x18533 = x3770;
      ite18531 = x18533;
    };
    int x18506 = ite18531;
    int ite18538 = 0;
    if(x18506) {
      
      int x3772 = x3763._2;
      int x3773 = x3764._2;
      int x3774 = x3772==(-1);
      int ite18640 = 0;
      if(x3774) {
        ite18640 = 1;
      } else {
        
        
        int x3775 = x3773==(-1);
        int x18642 = x3775;
        ite18640 = x18642;
      };
      int x18544 = ite18640;
      int ite18647 = 0;
      if(x18544) {
        ite18647 = 1;
      } else {
        
        
        int x3777 = x3772==(x3773);
        int x18649 = x3777;
        ite18647 = x18649;
      };
      int x18546 = ite18647;
      int x18539 = x18546;
      ite18538 = x18539;
    } else {
      
      ite18538 = 0;
    };
    int x18508 = ite18538;
    int ite18551 = 0;
    if(x18508) {
      
      int x3780 = x3763._3;
      int x3781 = x3764._3;
      int x3782 = x3780==(-1);
      int ite18663 = 0;
      if(x3782) {
        ite18663 = 1;
      } else {
        
        
        int x3783 = x3781==(-1);
        int x18665 = x3783;
        ite18663 = x18665;
      };
      int x18557 = ite18663;
      int ite18670 = 0;
      if(x18557) {
        ite18670 = 1;
      } else {
        
        
        int x3785 = x3780==(x3781);
        int x18672 = x3785;
        ite18670 = x18672;
      };
      int x18559 = ite18670;
      int x18552 = x18559;
      ite18551 = x18552;
    } else {
      
      ite18551 = 0;
    };
    int x18510 = ite18551;
    int ite18564 = 0;
    if(x18510) {
      
      int x3788 = x3763._4;
      int x3789 = x3764._4;
      int x3790 = x3788==(-1);
      int ite18686 = 0;
      if(x3790) {
        ite18686 = 1;
      } else {
        
        
        int x3791 = x3789==(-1);
        int x18688 = x3791;
        ite18686 = x18688;
      };
      int x18570 = ite18686;
      int ite18693 = 0;
      if(x18570) {
        ite18693 = 1;
      } else {
        
        
        int x3793 = x3788==(x3789);
        int x18695 = x3793;
        ite18693 = x18695;
      };
      int x18572 = ite18693;
      int x18565 = x18572;
      ite18564 = x18565;
    } else {
      
      ite18564 = 0;
    };
    int x18512 = ite18564;
    int ite18577 = 0;
    if(x18512) {
      
      int x3796 = x3763._5;
      int x3797 = x3764._5;
      int x3798 = x3796==(-1);
      int ite18709 = 0;
      if(x3798) {
        ite18709 = 1;
      } else {
        
        
        int x3799 = x3797==(-1);
        int x18711 = x3799;
        ite18709 = x18711;
      };
      int x18583 = ite18709;
      int ite18716 = 0;
      if(x18583) {
        ite18716 = 1;
      } else {
        
        
        int x3801 = x3796==(x3797);
        int x18718 = x3801;
        ite18716 = x18718;
      };
      int x18585 = ite18716;
      int x18578 = x18585;
      ite18577 = x18578;
    } else {
      
      ite18577 = 0;
    };
    int x18514 = ite18577;
    int ite18590 = 0;
    if(x18514) {
      
      Date x3804 = x3763._6;
      Date x3805 = x3764._6;
      int x3806 = x3804==(0);
      int ite18732 = 0;
      if(x3806) {
        ite18732 = 1;
      } else {
        
        
        int x3807 = x3805==(0);
        int x18734 = x3807;
        ite18732 = x18734;
      };
      int x18596 = ite18732;
      int ite18739 = 0;
      if(x18596) {
        ite18739 = 1;
      } else {
        
        
        int x3809 = x3804==(x3805);
        int x18741 = x3809;
        ite18739 = x18741;
      };
      int x18598 = ite18739;
      int x18591 = x18598;
      ite18590 = x18591;
    } else {
      
      ite18590 = 0;
    };
    int x18516 = ite18590;
    int ite18603 = 0;
    if(x18516) {
      
      double x3812 = x3763._7;
      double x3813 = x3764._7;
      int x3814 = x3812==(-1.0);
      int ite18755 = 0;
      if(x3814) {
        ite18755 = 1;
      } else {
        
        
        int x3815 = x3813==(-1.0);
        int x18757 = x3815;
        ite18755 = x18757;
      };
      int x18609 = ite18755;
      int ite18762 = 0;
      if(x18609) {
        ite18762 = 1;
      } else {
        
        
        int x3817 = x3812==(x3813);
        int x18764 = x3817;
        ite18762 = x18764;
      };
      int x18611 = ite18762;
      int x18604 = x18611;
      ite18603 = x18604;
    } else {
      
      ite18603 = 0;
    };
    int x18518 = ite18603;
    int x3820 = x18518 ? 0 : 1;
    return x3820; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4316)  { 
    int x4317 = -889275714;
    int x4318 = x4316._2;
    int x4319 = HASH(x4318);
    int x4320 = -862048943*(x4319);
    int x4321 = x4320<<(15);
    int x4322 = x4320 >> (-15 & (8*sizeof(x4320)-1));
    int x4323 = x4321|(x4322);
    int x4324 = x4323*(461845907);
    int x4325 = x4317;
    int x4326 = x4324^(x4325);
    int x4327 = x4326<<(13);
    int x4328 = x4326 >> (-13 & (8*sizeof(x4326)-1));
    int x4329 = x4327|(x4328);
    int x4330 = x4329*(5);
    int x4331 = x4330+(-430675100);
    x4317 = x4331;
    int x4333 = x4316._3;
    int x4334 = HASH(x4333);
    int x4335 = -862048943*(x4334);
    int x4336 = x4335<<(15);
    int x4337 = x4335 >> (-15 & (8*sizeof(x4335)-1));
    int x4338 = x4336|(x4337);
    int x4339 = x4338*(461845907);
    int x4340 = x4317;
    int x4341 = x4339^(x4340);
    int x4342 = x4341<<(13);
    int x4343 = x4341 >> (-13 & (8*sizeof(x4341)-1));
    int x4344 = x4342|(x4343);
    int x4345 = x4344*(5);
    int x4346 = x4345+(-430675100);
    x4317 = x4346;
    char* x4348 = x4316._6;
    int x4349 = HASH(x4348);
    int x4350 = -862048943*(x4349);
    int x4351 = x4350<<(15);
    int x4352 = x4350 >> (-15 & (8*sizeof(x4350)-1));
    int x4353 = x4351|(x4352);
    int x4354 = x4353*(461845907);
    int x4355 = x4317;
    int x4356 = x4354^(x4355);
    int x4357 = x4356<<(13);
    int x4358 = x4356 >> (-13 & (8*sizeof(x4356)-1));
    int x4359 = x4357|(x4358);
    int x4360 = x4359*(5);
    int x4361 = x4360+(-430675100);
    x4317 = x4361;
    int x4363 = x4317;
    int x4364 = x4363^(2);
    int x4365 = x4364 >> (16 & (8*sizeof(x4364)-1));
    int x4366 = x4364^(x4365);
    int x4367 = x4366*(-2048144789);
    int x4368 = x4367 >> (13 & (8*sizeof(x4367)-1));
    int x4369 = x4367^(x4368);
    int x4370 = x4369*(-1028477387);
    int x4371 = x4370 >> (16 & (8*sizeof(x4370)-1));
    int x4372 = x4370^(x4371);
    return x4372; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4374, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4375) { 
    int x4376 = x4374._2;
    int x4377 = x4375._2;
    int x4378 = x4376==(x4377);
    int ite18996 = 0;
    if(x4378) {
      
      int x4379 = x4374._3;
      int x4380 = x4375._3;
      int x4381 = x4379==(x4380);
      int x18997 = x4381;
      ite18996 = x18997;
    } else {
      
      ite18996 = 0;
    };
    int x18988 = ite18996;
    int ite19005 = 0;
    if(x18988) {
      
      char* x4383 = x4374._6;
      char* x4384 = x4375._6;
      int x4385 = !strcmpi(x4383, x4384);
      int x19006 = x4385;
      ite19005 = x19006;
    } else {
      
      ite19005 = 0;
    };
    int x18990 = ite19005;
    int x4387 = x18990 ? 0 : 1;
    return x4387; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3869)  { 
    int x3870 = -889275714;
    int x3871 = x3869._1;
    int x3872 = HASH(x3871);
    int x3873 = -862048943*(x3872);
    int x3874 = x3873<<(15);
    int x3875 = x3873 >> (-15 & (8*sizeof(x3873)-1));
    int x3876 = x3874|(x3875);
    int x3877 = x3876*(461845907);
    int x3878 = x3870;
    int x3879 = x3877^(x3878);
    int x3880 = x3879<<(13);
    int x3881 = x3879 >> (-13 & (8*sizeof(x3879)-1));
    int x3882 = x3880|(x3881);
    int x3883 = x3882*(5);
    int x3884 = x3883+(-430675100);
    x3870 = x3884;
    int x3886 = x3869._2;
    int x3887 = HASH(x3886);
    int x3888 = -862048943*(x3887);
    int x3889 = x3888<<(15);
    int x3890 = x3888 >> (-15 & (8*sizeof(x3888)-1));
    int x3891 = x3889|(x3890);
    int x3892 = x3891*(461845907);
    int x3893 = x3870;
    int x3894 = x3892^(x3893);
    int x3895 = x3894<<(13);
    int x3896 = x3894 >> (-13 & (8*sizeof(x3894)-1));
    int x3897 = x3895|(x3896);
    int x3898 = x3897*(5);
    int x3899 = x3898+(-430675100);
    x3870 = x3899;
    int x3901 = x3869._3;
    int x3902 = HASH(x3901);
    int x3903 = -862048943*(x3902);
    int x3904 = x3903<<(15);
    int x3905 = x3903 >> (-15 & (8*sizeof(x3903)-1));
    int x3906 = x3904|(x3905);
    int x3907 = x3906*(461845907);
    int x3908 = x3870;
    int x3909 = x3907^(x3908);
    int x3910 = x3909<<(13);
    int x3911 = x3909 >> (-13 & (8*sizeof(x3909)-1));
    int x3912 = x3910|(x3911);
    int x3913 = x3912*(5);
    int x3914 = x3913+(-430675100);
    x3870 = x3914;
    int x3916 = x3870;
    int x3917 = x3916^(2);
    int x3918 = x3917 >> (16 & (8*sizeof(x3917)-1));
    int x3919 = x3917^(x3918);
    int x3920 = x3919*(-2048144789);
    int x3921 = x3920 >> (13 & (8*sizeof(x3920)-1));
    int x3922 = x3920^(x3921);
    int x3923 = x3922*(-1028477387);
    int x3924 = x3923 >> (16 & (8*sizeof(x3923)-1));
    int x3925 = x3923^(x3924);
    return x3925; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x3927, const struct SEntry8_IIIITIIB& x3928) { 
    int x3929 = x3927._1;
    int x3930 = x3928._1;
    int x3931 = x3929==(x3930);
    int ite19104 = 0;
    if(x3931) {
      
      int x3932 = x3927._2;
      int x3933 = x3928._2;
      int x3934 = x3932==(x3933);
      int x19105 = x3934;
      ite19104 = x19105;
    } else {
      
      ite19104 = 0;
    };
    int x19096 = ite19104;
    int ite19113 = 0;
    if(x19096) {
      
      int x3936 = x3927._3;
      int x3937 = x3928._3;
      int x3938 = x3936==(x3937);
      int x19114 = x3938;
      ite19113 = x19114;
    } else {
      
      ite19113 = 0;
    };
    int x19098 = ite19113;
    int x3940 = x19098 ? 0 : 1;
    return x3940; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3515)  { 
    int x3516 = -889275714;
    int x3517 = x3515._2;
    int x3518 = HASH(x3517);
    int x3519 = -862048943*(x3518);
    int x3520 = x3519<<(15);
    int x3521 = x3519 >> (-15 & (8*sizeof(x3519)-1));
    int x3522 = x3520|(x3521);
    int x3523 = x3522*(461845907);
    int x3524 = x3516;
    int x3525 = x3523^(x3524);
    int x3526 = x3525<<(13);
    int x3527 = x3525 >> (-13 & (8*sizeof(x3525)-1));
    int x3528 = x3526|(x3527);
    int x3529 = x3528*(5);
    int x3530 = x3529+(-430675100);
    x3516 = x3530;
    int x3532 = x3515._3;
    int x3533 = HASH(x3532);
    int x3534 = -862048943*(x3533);
    int x3535 = x3534<<(15);
    int x3536 = x3534 >> (-15 & (8*sizeof(x3534)-1));
    int x3537 = x3535|(x3536);
    int x3538 = x3537*(461845907);
    int x3539 = x3516;
    int x3540 = x3538^(x3539);
    int x3541 = x3540<<(13);
    int x3542 = x3540 >> (-13 & (8*sizeof(x3540)-1));
    int x3543 = x3541|(x3542);
    int x3544 = x3543*(5);
    int x3545 = x3544+(-430675100);
    x3516 = x3545;
    int x3547 = x3516;
    int x3548 = x3547^(2);
    int x3549 = x3548 >> (16 & (8*sizeof(x3548)-1));
    int x3550 = x3548^(x3549);
    int x3551 = x3550*(-2048144789);
    int x3552 = x3551 >> (13 & (8*sizeof(x3551)-1));
    int x3553 = x3551^(x3552);
    int x3554 = x3553*(-1028477387);
    int x3555 = x3554 >> (16 & (8*sizeof(x3554)-1));
    int x3556 = x3554^(x3555);
    return x3556; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3558, const struct SEntry3_III& x3559) { 
    int x3560 = x3558._1;
    int x3561 = x3559._1;
    int x3562 = x3560==(x3561);
    int x3563 = x3560>(x3561);
    int x3564 = x3563 ? 1 : -1;
    int x3565 = x3562 ? 0 : x3564;
    return x3565; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3943)  { 
    int x3944 = -889275714;
    int x3945 = x3943._2;
    int x3946 = HASH(x3945);
    int x3947 = -862048943*(x3946);
    int x3948 = x3947<<(15);
    int x3949 = x3947 >> (-15 & (8*sizeof(x3947)-1));
    int x3950 = x3948|(x3949);
    int x3951 = x3950*(461845907);
    int x3952 = x3944;
    int x3953 = x3951^(x3952);
    int x3954 = x3953<<(13);
    int x3955 = x3953 >> (-13 & (8*sizeof(x3953)-1));
    int x3956 = x3954|(x3955);
    int x3957 = x3956*(5);
    int x3958 = x3957+(-430675100);
    x3944 = x3958;
    int x3960 = x3943._3;
    int x3961 = HASH(x3960);
    int x3962 = -862048943*(x3961);
    int x3963 = x3962<<(15);
    int x3964 = x3962 >> (-15 & (8*sizeof(x3962)-1));
    int x3965 = x3963|(x3964);
    int x3966 = x3965*(461845907);
    int x3967 = x3944;
    int x3968 = x3966^(x3967);
    int x3969 = x3968<<(13);
    int x3970 = x3968 >> (-13 & (8*sizeof(x3968)-1));
    int x3971 = x3969|(x3970);
    int x3972 = x3971*(5);
    int x3973 = x3972+(-430675100);
    x3944 = x3973;
    int x3975 = x3943._4;
    int x3976 = HASH(x3975);
    int x3977 = -862048943*(x3976);
    int x3978 = x3977<<(15);
    int x3979 = x3977 >> (-15 & (8*sizeof(x3977)-1));
    int x3980 = x3978|(x3979);
    int x3981 = x3980*(461845907);
    int x3982 = x3944;
    int x3983 = x3981^(x3982);
    int x3984 = x3983<<(13);
    int x3985 = x3983 >> (-13 & (8*sizeof(x3983)-1));
    int x3986 = x3984|(x3985);
    int x3987 = x3986*(5);
    int x3988 = x3987+(-430675100);
    x3944 = x3988;
    int x3990 = x3944;
    int x3991 = x3990^(2);
    int x3992 = x3991 >> (16 & (8*sizeof(x3991)-1));
    int x3993 = x3991^(x3992);
    int x3994 = x3993*(-2048144789);
    int x3995 = x3994 >> (13 & (8*sizeof(x3994)-1));
    int x3996 = x3994^(x3995);
    int x3997 = x3996*(-1028477387);
    int x3998 = x3997 >> (16 & (8*sizeof(x3997)-1));
    int x3999 = x3997^(x3998);
    return x3999; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x4001, const struct SEntry8_IIIITIIB& x4002) { 
    int x4003 = x4001._1;
    int x4004 = x4002._1;
    int x4005 = x4003==(x4004);
    int x4006 = x4003>(x4004);
    int x4007 = x4006 ? 1 : -1;
    int x4008 = x4005 ? 0 : x4007;
    return x4008; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3831)  { 
    int x3832 = 0;
    int x3833 = x3831._1;
    int x3834 = x3833-(1);
    int x3835 = x3832;
    int x3836 = x3835*(1);
    int x3837 = x3836+(x3834);
    x3832 = x3837;
    int x3839 = x3832;
    return x3839; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry9_ISSSSSSDD& x3828, const struct SEntry9_ISSSSSSDD& x3829) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3850)  { 
    int x3851 = 0;
    int x3852 = x3850._1;
    int x3853 = x3852-(1);
    int x3854 = x3851;
    int x3855 = x3854*(100000);
    int x3856 = x3855+(x3853);
    x3851 = x3856;
    int x3858 = x3851;
    return x3858; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry5_IISDS& x3847, const struct SEntry5_IISDS& x3848) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4095)  { 
    int x4096 = 0;
    int x4097 = x4095._1;
    int x4098 = x4097-(1);
    int x4099 = x4096;
    int x4100 = x4099*(10);
    int x4101 = x4100+(x4098);
    x4096 = x4101;
    int x4103 = x4095._2;
    int x4104 = x4103-(1);
    int x4105 = x4096;
    int x4106 = x4105*(1);
    int x4107 = x4106+(x4104);
    x4096 = x4107;
    int x4109 = x4096;
    return x4109; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry11_IISSSSSSDDI& x4092, const struct SEntry11_IISSSSSSDDI& x4093) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4293)  { 
    int x4294 = 0;
    int x4295 = x4293._1;
    int x4296 = x4295-(1);
    int x4297 = x4294;
    int x4298 = x4297*(3000);
    int x4299 = x4298+(x4296);
    x4294 = x4299;
    int x4301 = x4293._2;
    int x4302 = x4301-(1);
    int x4303 = x4294;
    int x4304 = x4303*(10);
    int x4305 = x4304+(x4302);
    x4294 = x4305;
    int x4307 = x4293._3;
    int x4308 = x4307-(1);
    int x4309 = x4294;
    int x4310 = x4309*(1);
    int x4311 = x4310+(x4308);
    x4294 = x4311;
    int x4313 = x4294;
    return x4313; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4290, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4291) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4399)  { 
    int x4400 = 0;
    int x4401 = x4399._1;
    int x4402 = x4401-(1);
    int x4403 = x4400;
    int x4404 = x4403*(100000);
    int x4405 = x4404+(x4402);
    x4400 = x4405;
    int x4407 = x4399._2;
    int x4408 = x4407-(1);
    int x4409 = x4400;
    int x4410 = x4409*(1);
    int x4411 = x4410+(x4408);
    x4400 = x4411;
    int x4413 = x4400;
    return x4413; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4396, const struct SEntry17_IIISSSSSSSSSSIIIS& x4397) { 
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
newOrderTblStoreType& x3625 = newOrderTbl;
newOrderTblIdx0Type& x723 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x724 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblStoreType& x3825 = historyTbl;
historyTblIdx0Type& x730 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblStoreType& x3844 = warehouseTbl;
warehouseTblIdx0Type& x735 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblStoreType& x3863 = itemTbl;
itemTblIdx0Type& x740 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblStoreType& x4087 = orderTbl;
orderTblIdx0Type& x747 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x748 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblStoreType& x4114 = districtTbl;
districtTblIdx0Type& x754 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblStoreType& x4286 = orderLineTbl;
orderLineTblIdx0Type& x759 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x760 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblStoreType& x4392 = customerTbl;
customerTblIdx0Type& x766 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x767 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblStoreType& x4418 = stockTbl;
stockTblIdx0Type& x772 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];

struct SEntry17_IIISSSSSSSSSSIIIS x7990;
struct SEntry8_IIIITIIB x7384;
struct SEntry11_IISSSSSSDDI x7511;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7599;
struct SEntry11_IISSSSSSDDI x7966;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7778;
struct SEntry5_IISDS x7938;
struct SEntry3_III x7372;
struct SEntry10_IIIIIITIDS x7524;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7959;
struct SEntry11_IISSSSSSDDI x7719;
struct SEntry10_IIIIIITIDS x7393;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7761;
struct SEntry8_IIIITIIB x7588;
struct SEntry9_ISSSSSSDD x7713;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7616;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7397;
struct SEntry9_ISSSSSSDD x7963;
struct SEntry17_IIISSSSSSSSSSIIIS x7547;


void DeliveryTx(int x10, Date x11, int x12, int x13) {
  int x14[10];
  int x15 = 1;
  while(1) {
    
    int x16 = x15;
    if (!((x16<=(10)))) break; 
    
    int x22 = x15;
    x7372._2 = x22;
    x7372._3 = x12;
    struct SEntry3_III* x12287 = x724.get(x7372);
    if((x12287!=(NULL))) {
      int x7378 = x12287->_1;
      int x29 = x15;
      x14[(x29-(1))] = x7378;
      x3625.del(x12287);
      int x33 = x15;
      x7384._1 = x7378;
      x7384._2 = x33;
      x7384._3 = x12;
      struct SEntry8_IIIITIIB* x12300 = x747.get(x7384);
      int x7387 = x12300->_4;
      x12300->_6 = x13;
      double x40 = 0.0;
      int x41 = x15;
      x7393._1 = x7378;
      x7393._2 = x41;
      x7393._3 = x12;
      x760.slice(x7393, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* x44 = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
        x44->_7 = x11;
        double x46 = x40;
        double x7442 = x44->_9;
        x40 = (x46+(x7442));
      
      }));
      int x53 = x15;
      x7397._1 = x7387;
      x7397._2 = x53;
      x7397._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12321 = x766.get(x7397);
      double x56 = x40;
      x12321->_17 += x56;
      x12321->_20 += 1;
    } else {
      
      int x60 = x15;
      x14[(x60-(1))] = 0;
    };
    int x64 = x15;
    x15 = (x64+(1));
  };
}
void StockLevelTx(int x68, Date x69, int x70, int x71, int x72, int x73) {
  x7511._1 = x72;
  x7511._2 = x71;
  struct SEntry11_IISSSSSSDDI* x12390 = x754.get(x7511);
  int x7515 = x12390->_11;
  int x79 = (x7515-(20));
  unordered_set<int> x80;
  while(1) {
    
    int x81 = x79;
    if (!((x81<(x7515)))) break; 
    
    int x83 = x79;
    x7524._1 = x83;
    x7524._2 = x72;
    x7524._3 = x71;
    x760.slice(x7524, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* x86 = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
      int x7546 = x86->_5;
      x7547._1 = x7546;
      x7547._2 = x71;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12408 = x772.get(x7547);
      int x7549 = x12408->_3;
      if((x7549<(x73))) {
        x80.insert(x7546);
      };
    
    }));
    int x96 = x79;
    x79 = (x96+(1));
  };
}
void OrderStatusTx(int x101, Date x102, int x103, int x104, int x105, int x106, int x107, char* x108) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite15999 = NULL;
  if((x106>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16000;
    x7599._2 = x105;
    x7599._3 = x104;
    x7599._6 = x108;
    x767.slice(x7599, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x113 = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x16000.push_back(x113);
    
    }));
    int x16008 = x16000.size();
    int x16010 = (x16008/(2));
    int x16011 = x16000.size();
    if(((x16011%(2))==(0))) {
      int x123 = x16010;
      x16010 = (x123-(1));
    };
    sort(x16000.begin(), x16000.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x127, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x128) {
      
      char* x7651 = x127->_4;
      char* x7652 = x128->_4;
      int x131 = strcmpi(x7651, x7652);
      return (x131<(0)); 
    }));
    int x16026 = x16010;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16027 = x16000[x16026];
    ite15999 = x16027;
  } else {
    
    x7616._1 = x107;
    x7616._2 = x105;
    x7616._3 = x104;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16032 = x766.get(x7616);
    ite15999 = x16032;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7585 = ite15999;
  int x7586 = x7585->_3;
  x7588._2 = x105;
  x7588._3 = x104;
  x7588._4 = x7586;
  struct SEntry8_IIIITIIB* x12492 = x748.get(x7588);
  int x150 = 0;
  int x7593 = x12492->_1;
  x150 = x7593;
}
void PaymentTx(int x153, Date x154, int x155, int x156, int x157, int x158, int x159, int x160, int x161, char* x162, double x163) {
  x7713._1 = x156;
  struct SEntry9_ISSSSSSDD* x12547 = x735.get(x7713);
  x12547->_9 += x163;
  x7719._1 = x157;
  x7719._2 = x156;
  struct SEntry11_IISSSSSSDDI* x12552 = x754.get(x7719);
  x12552->_10 += x163;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite16098 = NULL;
  if((x158>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x16099;
    x7761._2 = x160;
    x7761._3 = x159;
    x7761._6 = x162;
    x767.slice(x7761, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x178 = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x16099.push_back(x178);
    
    }));
    int x16107 = x16099.size();
    int x16109 = (x16107/(2));
    int x16110 = x16099.size();
    if(((x16110%(2))==(0))) {
      int x188 = x16109;
      x16109 = (x188-(1));
    };
    sort(x16099.begin(), x16099.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x192, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x193) {
      
      char* x7834 = x192->_4;
      char* x7835 = x193->_4;
      int x196 = strcmpi(x7834, x7835);
      return (x196<(0)); 
    }));
    int x16125 = x16109;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16126 = x16099[x16125];
    ite16098 = x16126;
  } else {
    
    x7778._1 = x161;
    x7778._2 = x160;
    x7778._3 = x159;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x16131 = x766.get(x7778);
    ite16098 = x16131;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7725 = ite16098;
  char* x7726 = x7725->_21;
  char* x7727 = x7725->_14;
  char* x17370 = strstr(x7727, "BC");
  if((x17370!=(NULL))) {
    int x7730 = x7725->_1;
    char* x212 = new char[501];
    snprintf(x212, 501, "%d %d %d %d %d $%f %s | %s", x7730,x160,x159,x157,x156,x163,(IntToStrDate(x154)),x7726);
    x7725->_17 += x163;
    x7725->_21 = x212;
  } else {
    
    x7725->_17 += x163;
  };
  char* x7738 = x12547->_2;
  char* x7739 = x12552->_3;
  char* x221 = new char[25];
  snprintf(x221, 25, "%.10s    %.10s", x7738,x7739);
  int x7742 = x7725->_1;
  struct SEntry8_IIIIITDS* x16968 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x16968, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x16968->_1 = x7742; x16968->_2 = x160; x16968->_3 = x159; x16968->_4 = x157; x16968->_5 = x156; x16968->_6 = x154; x16968->_7 = x163; x16968->_8 = x221;
  x3825.add(x16968);
}
void NewOrderTx(int x226, Date x227, int x228, int x229, int x230, int x231, int x232, int x233, int* x234, int* x235, int* x236, double* x237, char** x238, int* x239, char** x240, double* x241) {
  int x242 = 0;
  int x243 = 0;
  char* x244[x232];
  int x245 = 1;
  while(1) {
    
    int x246 = x242;
    int ite16391 = 0;
    if((x246<(x232))) {
      
      int x248 = x245;
      int x16392 = x248;
      ite16391 = x16392;
    } else {
      
      ite16391 = 0;
    };
    int x16223 = ite16391;
    if (!(x16223)) break; 
    
    int x250 = x242;
    int x251 = x234[x250];
    x7938._1 = x251;
    struct SEntry5_IISDS* x12688 = x740.get(x7938);
    if((x12688==(NULL))) {
      x245 = 0;
    } else {
      
      int x257 = x242;
      char* x7946 = x12688->_3;
      x238[x257] = x7946;
      int x260 = x242;
      double x7949 = x12688->_4;
      x237[x260] = x7949;
      int x263 = x242;
      char* x7952 = x12688->_5;
      x244[x263] = x7952;
    };
    int x267 = x242;
    x242 = (x267+(1));
  };
  int x271 = x245;
  if(x271) {
    x7959._1 = x231;
    x7959._2 = x230;
    x7959._3 = x229;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12711 = x766.get(x7959);
    x7963._1 = x229;
    struct SEntry9_ISSSSSSDD* x12714 = x735.get(x7963);
    x7966._1 = x230;
    x7966._2 = x229;
    struct SEntry11_IISSSSSSDDI* x12718 = x754.get(x7966);
    int x7969 = x12718->_11;
    x12718->_11 += 1;
    struct SEntry8_IIIITIIB* x17019 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x17019, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x17019->_1 = x7969; x17019->_2 = x230; x17019->_3 = x229; x17019->_4 = x231; x17019->_5 = x227; x17019->_6 = -1; x17019->_7 = x232; x17019->_8 = (x233>(0));
    x4087.add(x17019);
    struct SEntry3_III* x17023 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x17023, 0, 1 * sizeof(struct SEntry3_III));
    x17023->_1 = x7969; x17023->_2 = x230; x17023->_3 = x229;
    x3625.add(x17023);
    double x291 = 0.0;
    x242 = 0;
    while(1) {
      
      int x293 = x242;
      if (!((x293<(x232)))) break; 
      
      int x295 = x242;
      int x296 = x235[x295];
      int x297 = x242;
      int x298 = x234[x297];
      int x299 = x242;
      int x300 = x236[x299];
      x7990._1 = x298;
      x7990._2 = x296;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12741 = x772.get(x7990);
      char* ite16277 = NULL;
      if((x230==(1))) {
        char* x16278 = x12741->_4;
        ite16277 = x16278;
      } else {
        
        char* ite16282 = NULL;
        if((x230==(2))) {
          char* x16283 = x12741->_5;
          ite16282 = x16283;
        } else {
          
          char* ite16287 = NULL;
          if((x230==(3))) {
            char* x16288 = x12741->_6;
            ite16287 = x16288;
          } else {
            
            char* ite16292 = NULL;
            if((x230==(4))) {
              char* x16293 = x12741->_7;
              ite16292 = x16293;
            } else {
              
              char* ite16297 = NULL;
              if((x230==(5))) {
                char* x16298 = x12741->_8;
                ite16297 = x16298;
              } else {
                
                char* ite16302 = NULL;
                if((x230==(6))) {
                  char* x16303 = x12741->_9;
                  ite16302 = x16303;
                } else {
                  
                  char* ite16307 = NULL;
                  if((x230==(7))) {
                    char* x16308 = x12741->_10;
                    ite16307 = x16308;
                  } else {
                    
                    char* ite16312 = NULL;
                    if((x230==(8))) {
                      char* x16313 = x12741->_11;
                      ite16312 = x16313;
                    } else {
                      
                      char* ite16317 = NULL;
                      if((x230==(9))) {
                        char* x16318 = x12741->_12;
                        ite16317 = x16318;
                      } else {
                        
                        char* x16320 = x12741->_13;
                        ite16317 = x16320;
                      };
                      char* x16316 = ite16317;
                      ite16312 = x16316;
                    };
                    char* x16311 = ite16312;
                    ite16307 = x16311;
                  };
                  char* x16306 = ite16307;
                  ite16302 = x16306;
                };
                char* x16301 = ite16302;
                ite16297 = x16301;
              };
              char* x16296 = ite16297;
              ite16292 = x16296;
            };
            char* x16291 = ite16292;
            ite16287 = x16291;
          };
          char* x16286 = ite16287;
          ite16282 = x16286;
        };
        char* x16281 = ite16282;
        ite16277 = x16281;
      };
      char* x330 = ite16277;
      int x8020 = x12741->_3;
      int x332 = x242;
      x239[x332] = x8020;
      char* x8023 = x12711->_14;
      char* x17592 = strstr(x8023, "original");
      int ite16518 = 0;
      if((x17592!=(NULL))) {
        
        char* x8026 = x12741->_17;
        char* x17598 = strstr(x8026, "original");
        int x16519 = (x17598!=(NULL));
        ite16518 = x16519;
      } else {
        
        ite16518 = 0;
      };
      int x16345 = ite16518;
      if(x16345) {
        int x339 = x242;
        strcpy(x240[x339], "B");
      } else {
        
        int x341 = x242;
        strcpy(x240[x341], "G");
      };
      x12741->_3 = (x8020-(x300));
      if((x8020<=(x300))) {
        x12741->_3 += 91;
      };
      int x349 = 0;
      if((x296!=(x229))) {
        x349 = 1;
      };
      double x8043 = x12711->_16;
      double x8044 = x12714->_8;
      double x8045 = x12718->_9;
      int x357 = x242;
      double x358 = x237[x357];
      double x365 = ((x300*(x358))*(((1.0+(x8044))+(x8045))))*((1.0-(x8043)));
      int x366 = x242;
      x241[x366] = x365;
      double x368 = x291;
      x291 = (x368+(x365));
      int x371 = x242;
      struct SEntry10_IIIIIITIDS* x17150 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x17150, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x17150->_1 = x7969; x17150->_2 = x230; x17150->_3 = x229; x17150->_4 = (x371+(1)); x17150->_5 = x298; x17150->_6 = x296; x17150->_7 = 0; x17150->_8 = x300; x17150->_9 = x365; x17150->_10 = x330;
      x4286.add(x17150);
      int x376 = x242;
      x242 = (x376+(1));
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
