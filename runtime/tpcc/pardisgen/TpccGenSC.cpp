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

bool strcmpi(const char* This, const char *That) {
   int i = 0;
   while(true) {
      char c1 = tolower(This[i]);
      char c2 = tolower(That[i]);
      if(c1 == 0 || c2 == 0)
        return c1 == c2;
      else if (c1 == c2) {
          i++;
          continue;
      }
      else if (c1 < c2)
          return true;
      else return false;
   }
}

typedef size_t Date;
char * IntToStrDate(Date);
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
 struct SEntry10_IIIIIITIDS_Idx1234 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3988)  { 
    int x3989 = -889275714;
    int x3990 = x3988._1;
    int x3991 = HASH(x3990);
    int x3992 = -862048943*(x3991);
    int x3993 = x3992<<(15);
    int x3994 = x3992 >> (-15 & (sizeof(x3992)-1));
    int x3995 = x3993|(x3994);
    int x3996 = x3995*(461845907);
    int x3997 = x3989;
    int x3998 = x3996^(x3997);
    int x3999 = x3998<<(13);
    int x4000 = x3998 >> (-13 & (sizeof(x3998)-1));
    int x4001 = x3999|(x4000);
    int x4002 = x4001*(5);
    int x4003 = x4002+(-430675100);
    x3989 = x4003;
    int x4005 = x3988._2;
    int x4006 = HASH(x4005);
    int x4007 = -862048943*(x4006);
    int x4008 = x4007<<(15);
    int x4009 = x4007 >> (-15 & (sizeof(x4007)-1));
    int x4010 = x4008|(x4009);
    int x4011 = x4010*(461845907);
    int x4012 = x3989;
    int x4013 = x4011^(x4012);
    int x4014 = x4013<<(13);
    int x4015 = x4013 >> (-13 & (sizeof(x4013)-1));
    int x4016 = x4014|(x4015);
    int x4017 = x4016*(5);
    int x4018 = x4017+(-430675100);
    x3989 = x4018;
    int x4020 = x3988._3;
    int x4021 = HASH(x4020);
    int x4022 = -862048943*(x4021);
    int x4023 = x4022<<(15);
    int x4024 = x4022 >> (-15 & (sizeof(x4022)-1));
    int x4025 = x4023|(x4024);
    int x4026 = x4025*(461845907);
    int x4027 = x3989;
    int x4028 = x4026^(x4027);
    int x4029 = x4028<<(13);
    int x4030 = x4028 >> (-13 & (sizeof(x4028)-1));
    int x4031 = x4029|(x4030);
    int x4032 = x4031*(5);
    int x4033 = x4032+(-430675100);
    x3989 = x4033;
    int x4035 = x3988._4;
    int x4036 = HASH(x4035);
    int x4037 = -862048943*(x4036);
    int x4038 = x4037<<(15);
    int x4039 = x4037 >> (-15 & (sizeof(x4037)-1));
    int x4040 = x4038|(x4039);
    int x4041 = x4040*(461845907);
    int x4042 = x3989;
    int x4043 = x4041^(x4042);
    int x4044 = x4043<<(13);
    int x4045 = x4043 >> (-13 & (sizeof(x4043)-1));
    int x4046 = x4044|(x4045);
    int x4047 = x4046*(5);
    int x4048 = x4047+(-430675100);
    x3989 = x4048;
    int x4050 = x3989;
    int x4051 = x4050^(2);
    int x4052 = x4051 >> (16 & (sizeof(x4051)-1));
    int x4053 = x4051^(x4052);
    int x4054 = x4053*(-2048144789);
    int x4055 = x4054 >> (13 & (sizeof(x4054)-1));
    int x4056 = x4054^(x4055);
    int x4057 = x4056*(-1028477387);
    int x4058 = x4057 >> (16 & (sizeof(x4057)-1));
    int x4059 = x4057^(x4058);
    return x4059; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry10_IIIIIITIDS& x4061, const struct SEntry10_IIIIIITIDS& x4062) { 
    int x4063 = x4061._1;
    int x4064 = x4062._1;
    int x4065 = x4063==(x4064);
    int ite16807 = 0;
    if(x4065) {
      
      int x4066 = x4061._2;
      int x4067 = x4062._2;
      int x4068 = x4066==(x4067);
      int x16808 = x4068;
      ite16807 = x16808;
    } else {
      
      ite16807 = 0;
    };
    int x16797 = ite16807;
    int ite16816 = 0;
    if(x16797) {
      
      int x4070 = x4061._3;
      int x4071 = x4062._3;
      int x4072 = x4070==(x4071);
      int x16817 = x4072;
      ite16816 = x16817;
    } else {
      
      ite16816 = 0;
    };
    int x16799 = ite16816;
    int ite16825 = 0;
    if(x16799) {
      
      int x4074 = x4061._4;
      int x4075 = x4062._4;
      int x4076 = x4074==(x4075);
      int x16826 = x4076;
      ite16825 = x16826;
    } else {
      
      ite16825 = 0;
    };
    int x16801 = ite16825;
    int x4078 = x16801 ? 0 : 1;
    return x4078; 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3882)  { 
    int x3883 = -889275714;
    int x3884 = x3882._2;
    int x3885 = HASH(x3884);
    int x3886 = -862048943*(x3885);
    int x3887 = x3886<<(15);
    int x3888 = x3886 >> (-15 & (sizeof(x3886)-1));
    int x3889 = x3887|(x3888);
    int x3890 = x3889*(461845907);
    int x3891 = x3883;
    int x3892 = x3890^(x3891);
    int x3893 = x3892<<(13);
    int x3894 = x3892 >> (-13 & (sizeof(x3892)-1));
    int x3895 = x3893|(x3894);
    int x3896 = x3895*(5);
    int x3897 = x3896+(-430675100);
    x3883 = x3897;
    int x3899 = x3882._3;
    int x3900 = HASH(x3899);
    int x3901 = -862048943*(x3900);
    int x3902 = x3901<<(15);
    int x3903 = x3901 >> (-15 & (sizeof(x3901)-1));
    int x3904 = x3902|(x3903);
    int x3905 = x3904*(461845907);
    int x3906 = x3883;
    int x3907 = x3905^(x3906);
    int x3908 = x3907<<(13);
    int x3909 = x3907 >> (-13 & (sizeof(x3907)-1));
    int x3910 = x3908|(x3909);
    int x3911 = x3910*(5);
    int x3912 = x3911+(-430675100);
    x3883 = x3912;
    int x3914 = x3882._4;
    int x3915 = HASH(x3914);
    int x3916 = -862048943*(x3915);
    int x3917 = x3916<<(15);
    int x3918 = x3916 >> (-15 & (sizeof(x3916)-1));
    int x3919 = x3917|(x3918);
    int x3920 = x3919*(461845907);
    int x3921 = x3883;
    int x3922 = x3920^(x3921);
    int x3923 = x3922<<(13);
    int x3924 = x3922 >> (-13 & (sizeof(x3922)-1));
    int x3925 = x3923|(x3924);
    int x3926 = x3925*(5);
    int x3927 = x3926+(-430675100);
    x3883 = x3927;
    int x3929 = x3883;
    int x3930 = x3929^(2);
    int x3931 = x3930 >> (16 & (sizeof(x3930)-1));
    int x3932 = x3930^(x3931);
    int x3933 = x3932*(-2048144789);
    int x3934 = x3933 >> (13 & (sizeof(x3933)-1));
    int x3935 = x3933^(x3934);
    int x3936 = x3935*(-1028477387);
    int x3937 = x3936 >> (16 & (sizeof(x3936)-1));
    int x3938 = x3936^(x3937);
    return x3938; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x3940, const struct SEntry8_IIIITIIB& x3941) { 
    int x3942 = x3940._2;
    int x3943 = x3941._2;
    int x3944 = x3942==(x3943);
    int ite16933 = 0;
    if(x3944) {
      
      int x3945 = x3940._3;
      int x3946 = x3941._3;
      int x3947 = x3945==(x3946);
      int x16934 = x3947;
      ite16933 = x16934;
    } else {
      
      ite16933 = 0;
    };
    int x16925 = ite16933;
    int ite16942 = 0;
    if(x16925) {
      
      int x3949 = x3940._4;
      int x3950 = x3941._4;
      int x3951 = x3949==(x3950);
      int x16943 = x3951;
      ite16942 = x16943;
    } else {
      
      ite16942 = 0;
    };
    int x16927 = ite16942;
    int x3953 = x16927 ? 0 : 1;
    return x3953; 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3432)  { 
    int x3433 = -889275714;
    int x3434 = x3432._1;
    int x3435 = HASH(x3434);
    int x3436 = -862048943*(x3435);
    int x3437 = x3436<<(15);
    int x3438 = x3436 >> (-15 & (sizeof(x3436)-1));
    int x3439 = x3437|(x3438);
    int x3440 = x3439*(461845907);
    int x3441 = x3433;
    int x3442 = x3440^(x3441);
    int x3443 = x3442<<(13);
    int x3444 = x3442 >> (-13 & (sizeof(x3442)-1));
    int x3445 = x3443|(x3444);
    int x3446 = x3445*(5);
    int x3447 = x3446+(-430675100);
    x3433 = x3447;
    int x3449 = x3432._2;
    int x3450 = HASH(x3449);
    int x3451 = -862048943*(x3450);
    int x3452 = x3451<<(15);
    int x3453 = x3451 >> (-15 & (sizeof(x3451)-1));
    int x3454 = x3452|(x3453);
    int x3455 = x3454*(461845907);
    int x3456 = x3433;
    int x3457 = x3455^(x3456);
    int x3458 = x3457<<(13);
    int x3459 = x3457 >> (-13 & (sizeof(x3457)-1));
    int x3460 = x3458|(x3459);
    int x3461 = x3460*(5);
    int x3462 = x3461+(-430675100);
    x3433 = x3462;
    int x3464 = x3432._3;
    int x3465 = HASH(x3464);
    int x3466 = -862048943*(x3465);
    int x3467 = x3466<<(15);
    int x3468 = x3466 >> (-15 & (sizeof(x3466)-1));
    int x3469 = x3467|(x3468);
    int x3470 = x3469*(461845907);
    int x3471 = x3433;
    int x3472 = x3470^(x3471);
    int x3473 = x3472<<(13);
    int x3474 = x3472 >> (-13 & (sizeof(x3472)-1));
    int x3475 = x3473|(x3474);
    int x3476 = x3475*(5);
    int x3477 = x3476+(-430675100);
    x3433 = x3477;
    int x3479 = x3433;
    int x3480 = x3479^(2);
    int x3481 = x3480 >> (16 & (sizeof(x3480)-1));
    int x3482 = x3480^(x3481);
    int x3483 = x3482*(-2048144789);
    int x3484 = x3483 >> (13 & (sizeof(x3483)-1));
    int x3485 = x3483^(x3484);
    int x3486 = x3485*(-1028477387);
    int x3487 = x3486 >> (16 & (sizeof(x3486)-1));
    int x3488 = x3486^(x3487);
    return x3488; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3490, const struct SEntry3_III& x3491) { 
    int x3492 = x3490._1;
    int x3493 = x3491._1;
    int x3494 = x3492==(x3493);
    int ite17041 = 0;
    if(x3494) {
      
      int x3495 = x3490._2;
      int x3496 = x3491._2;
      int x3497 = x3495==(x3496);
      int x17042 = x3497;
      ite17041 = x17042;
    } else {
      
      ite17041 = 0;
    };
    int x17033 = ite17041;
    int ite17050 = 0;
    if(x17033) {
      
      int x3499 = x3490._3;
      int x3500 = x3491._3;
      int x3501 = x3499==(x3500);
      int x17051 = x3501;
      ite17050 = x17051;
    } else {
      
      ite17050 = 0;
    };
    int x17035 = ite17050;
    int x3503 = x17035 ? 0 : 1;
    return x3503; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4081)  { 
    int x4082 = -889275714;
    int x4083 = x4081._1;
    int x4084 = HASH(x4083);
    int x4085 = -862048943*(x4084);
    int x4086 = x4085<<(15);
    int x4087 = x4085 >> (-15 & (sizeof(x4085)-1));
    int x4088 = x4086|(x4087);
    int x4089 = x4088*(461845907);
    int x4090 = x4082;
    int x4091 = x4089^(x4090);
    int x4092 = x4091<<(13);
    int x4093 = x4091 >> (-13 & (sizeof(x4091)-1));
    int x4094 = x4092|(x4093);
    int x4095 = x4094*(5);
    int x4096 = x4095+(-430675100);
    x4082 = x4096;
    int x4098 = x4081._2;
    int x4099 = HASH(x4098);
    int x4100 = -862048943*(x4099);
    int x4101 = x4100<<(15);
    int x4102 = x4100 >> (-15 & (sizeof(x4100)-1));
    int x4103 = x4101|(x4102);
    int x4104 = x4103*(461845907);
    int x4105 = x4082;
    int x4106 = x4104^(x4105);
    int x4107 = x4106<<(13);
    int x4108 = x4106 >> (-13 & (sizeof(x4106)-1));
    int x4109 = x4107|(x4108);
    int x4110 = x4109*(5);
    int x4111 = x4110+(-430675100);
    x4082 = x4111;
    int x4113 = x4081._3;
    int x4114 = HASH(x4113);
    int x4115 = -862048943*(x4114);
    int x4116 = x4115<<(15);
    int x4117 = x4115 >> (-15 & (sizeof(x4115)-1));
    int x4118 = x4116|(x4117);
    int x4119 = x4118*(461845907);
    int x4120 = x4082;
    int x4121 = x4119^(x4120);
    int x4122 = x4121<<(13);
    int x4123 = x4121 >> (-13 & (sizeof(x4121)-1));
    int x4124 = x4122|(x4123);
    int x4125 = x4124*(5);
    int x4126 = x4125+(-430675100);
    x4082 = x4126;
    int x4128 = x4082;
    int x4129 = x4128^(2);
    int x4130 = x4129 >> (16 & (sizeof(x4129)-1));
    int x4131 = x4129^(x4130);
    int x4132 = x4131*(-2048144789);
    int x4133 = x4132 >> (13 & (sizeof(x4132)-1));
    int x4134 = x4132^(x4133);
    int x4135 = x4134*(-1028477387);
    int x4136 = x4135 >> (16 & (sizeof(x4135)-1));
    int x4137 = x4135^(x4136);
    return x4137; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry10_IIIIIITIDS& x4139, const struct SEntry10_IIIIIITIDS& x4140) { 
    int x4141 = x4139._1;
    int x4142 = x4140._1;
    int x4143 = x4141==(x4142);
    int ite17149 = 0;
    if(x4143) {
      
      int x4144 = x4139._2;
      int x4145 = x4140._2;
      int x4146 = x4144==(x4145);
      int x17150 = x4146;
      ite17149 = x17150;
    } else {
      
      ite17149 = 0;
    };
    int x17141 = ite17149;
    int ite17158 = 0;
    if(x17141) {
      
      int x4148 = x4139._3;
      int x4149 = x4140._3;
      int x4150 = x4148==(x4149);
      int x17159 = x4150;
      ite17158 = x17159;
    } else {
      
      ite17158 = 0;
    };
    int x17143 = ite17158;
    int x4152 = x17143 ? 0 : 1;
    return x4152; 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3559)  { 
    int x3560 = -889275714;
    int x3561 = x3559._2;
    int x3562 = HASH(x3561);
    int x3563 = -862048943*(x3562);
    int x3564 = x3563<<(15);
    int x3565 = x3563 >> (-15 & (sizeof(x3563)-1));
    int x3566 = x3564|(x3565);
    int x3567 = x3566*(461845907);
    int x3568 = x3560;
    int x3569 = x3567^(x3568);
    int x3570 = x3569<<(13);
    int x3571 = x3569 >> (-13 & (sizeof(x3569)-1));
    int x3572 = x3570|(x3571);
    int x3573 = x3572*(5);
    int x3574 = x3573+(-430675100);
    x3560 = x3574;
    int x3576 = x3559._3;
    int x3577 = HASH(x3576);
    int x3578 = -862048943*(x3577);
    int x3579 = x3578<<(15);
    int x3580 = x3578 >> (-15 & (sizeof(x3578)-1));
    int x3581 = x3579|(x3580);
    int x3582 = x3581*(461845907);
    int x3583 = x3560;
    int x3584 = x3582^(x3583);
    int x3585 = x3584<<(13);
    int x3586 = x3584 >> (-13 & (sizeof(x3584)-1));
    int x3587 = x3585|(x3586);
    int x3588 = x3587*(5);
    int x3589 = x3588+(-430675100);
    x3560 = x3589;
    int x3591 = x3560;
    int x3592 = x3591^(2);
    int x3593 = x3592 >> (16 & (sizeof(x3592)-1));
    int x3594 = x3592^(x3593);
    int x3595 = x3594*(-2048144789);
    int x3596 = x3595 >> (13 & (sizeof(x3595)-1));
    int x3597 = x3595^(x3596);
    int x3598 = x3597*(-1028477387);
    int x3599 = x3598 >> (16 & (sizeof(x3598)-1));
    int x3600 = x3598^(x3599);
    return x3600; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3602, const struct SEntry3_III& x3603) { 
    int x3604 = x3602._2;
    int x3605 = x3603._2;
    int x3606 = x3604==(x3605);
    int ite17240 = 0;
    if(x3606) {
      
      int x3607 = x3602._3;
      int x3608 = x3603._3;
      int x3609 = x3607==(x3608);
      int x17241 = x3609;
      ite17240 = x17241;
    } else {
      
      ite17240 = 0;
    };
    int x17234 = ite17240;
    int x3611 = x17234 ? 0 : 1;
    return x3611; 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3621)  { 
    int x3622 = -889275714;
    int x3623 = x3622;
    int x3624 = x3623^(2);
    int x3625 = x3624 >> (16 & (sizeof(x3624)-1));
    int x3626 = x3624^(x3625);
    int x3627 = x3626*(-2048144789);
    int x3628 = x3627 >> (13 & (sizeof(x3627)-1));
    int x3629 = x3627^(x3628);
    int x3630 = x3629*(-1028477387);
    int x3631 = x3630 >> (16 & (sizeof(x3630)-1));
    int x3632 = x3630^(x3631);
    return x3632; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIIITDS& x3634, const struct SEntry8_IIIIITDS& x3635) { 
    int x3636 = x3634._1;
    int x3637 = x3635._1;
    int x3638 = x3636==(-1);
    int ite17297 = 0;
    if(x3638) {
      ite17297 = 1;
    } else {
      
      
      int x3639 = x3637==(-1);
      int x17299 = x3639;
      ite17297 = x17299;
    };
    int x17277 = ite17297;
    int ite17304 = 0;
    if(x17277) {
      ite17304 = 1;
    } else {
      
      
      int x3641 = x3636==(x3637);
      int x17306 = x3641;
      ite17304 = x17306;
    };
    int x17279 = ite17304;
    int ite17311 = 0;
    if(x17279) {
      
      int x3643 = x3634._2;
      int x3644 = x3635._2;
      int x3645 = x3643==(-1);
      int ite17413 = 0;
      if(x3645) {
        ite17413 = 1;
      } else {
        
        
        int x3646 = x3644==(-1);
        int x17415 = x3646;
        ite17413 = x17415;
      };
      int x17317 = ite17413;
      int ite17420 = 0;
      if(x17317) {
        ite17420 = 1;
      } else {
        
        
        int x3648 = x3643==(x3644);
        int x17422 = x3648;
        ite17420 = x17422;
      };
      int x17319 = ite17420;
      int x17312 = x17319;
      ite17311 = x17312;
    } else {
      
      ite17311 = 0;
    };
    int x17281 = ite17311;
    int ite17324 = 0;
    if(x17281) {
      
      int x3651 = x3634._3;
      int x3652 = x3635._3;
      int x3653 = x3651==(-1);
      int ite17436 = 0;
      if(x3653) {
        ite17436 = 1;
      } else {
        
        
        int x3654 = x3652==(-1);
        int x17438 = x3654;
        ite17436 = x17438;
      };
      int x17330 = ite17436;
      int ite17443 = 0;
      if(x17330) {
        ite17443 = 1;
      } else {
        
        
        int x3656 = x3651==(x3652);
        int x17445 = x3656;
        ite17443 = x17445;
      };
      int x17332 = ite17443;
      int x17325 = x17332;
      ite17324 = x17325;
    } else {
      
      ite17324 = 0;
    };
    int x17283 = ite17324;
    int ite17337 = 0;
    if(x17283) {
      
      int x3659 = x3634._4;
      int x3660 = x3635._4;
      int x3661 = x3659==(-1);
      int ite17459 = 0;
      if(x3661) {
        ite17459 = 1;
      } else {
        
        
        int x3662 = x3660==(-1);
        int x17461 = x3662;
        ite17459 = x17461;
      };
      int x17343 = ite17459;
      int ite17466 = 0;
      if(x17343) {
        ite17466 = 1;
      } else {
        
        
        int x3664 = x3659==(x3660);
        int x17468 = x3664;
        ite17466 = x17468;
      };
      int x17345 = ite17466;
      int x17338 = x17345;
      ite17337 = x17338;
    } else {
      
      ite17337 = 0;
    };
    int x17285 = ite17337;
    int ite17350 = 0;
    if(x17285) {
      
      int x3667 = x3634._5;
      int x3668 = x3635._5;
      int x3669 = x3667==(-1);
      int ite17482 = 0;
      if(x3669) {
        ite17482 = 1;
      } else {
        
        
        int x3670 = x3668==(-1);
        int x17484 = x3670;
        ite17482 = x17484;
      };
      int x17356 = ite17482;
      int ite17489 = 0;
      if(x17356) {
        ite17489 = 1;
      } else {
        
        
        int x3672 = x3667==(x3668);
        int x17491 = x3672;
        ite17489 = x17491;
      };
      int x17358 = ite17489;
      int x17351 = x17358;
      ite17350 = x17351;
    } else {
      
      ite17350 = 0;
    };
    int x17287 = ite17350;
    int ite17363 = 0;
    if(x17287) {
      
      Date x3675 = x3634._6;
      Date x3676 = x3635._6;
      int x3677 = x3675==(-1);
      int ite17505 = 0;
      if(x3677) {
        ite17505 = 1;
      } else {
        
        
        int x3678 = x3676==(-1);
        int x17507 = x3678;
        ite17505 = x17507;
      };
      int x17369 = ite17505;
      int ite17512 = 0;
      if(x17369) {
        ite17512 = 1;
      } else {
        
        
        int x3680 = x3675==(x3676);
        int x17514 = x3680;
        ite17512 = x17514;
      };
      int x17371 = ite17512;
      int x17364 = x17371;
      ite17363 = x17364;
    } else {
      
      ite17363 = 0;
    };
    int x17289 = ite17363;
    int ite17376 = 0;
    if(x17289) {
      
      double x3683 = x3634._7;
      double x3684 = x3635._7;
      int x3685 = x3683==(-1.0);
      int ite17528 = 0;
      if(x3685) {
        ite17528 = 1;
      } else {
        
        
        int x3686 = x3684==(-1.0);
        int x17530 = x3686;
        ite17528 = x17530;
      };
      int x17382 = ite17528;
      int ite17535 = 0;
      if(x17382) {
        ite17535 = 1;
      } else {
        
        
        int x3688 = x3683==(x3684);
        int x17537 = x3688;
        ite17535 = x17537;
      };
      int x17384 = ite17535;
      int x17377 = x17384;
      ite17376 = x17377;
    } else {
      
      ite17376 = 0;
    };
    int x17291 = ite17376;
    int x3691 = x17291 ? 0 : 1;
    return x3691; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4187)  { 
    int x4188 = -889275714;
    int x4189 = x4187._2;
    int x4190 = HASH(x4189);
    int x4191 = -862048943*(x4190);
    int x4192 = x4191<<(15);
    int x4193 = x4191 >> (-15 & (sizeof(x4191)-1));
    int x4194 = x4192|(x4193);
    int x4195 = x4194*(461845907);
    int x4196 = x4188;
    int x4197 = x4195^(x4196);
    int x4198 = x4197<<(13);
    int x4199 = x4197 >> (-13 & (sizeof(x4197)-1));
    int x4200 = x4198|(x4199);
    int x4201 = x4200*(5);
    int x4202 = x4201+(-430675100);
    x4188 = x4202;
    int x4204 = x4187._3;
    int x4205 = HASH(x4204);
    int x4206 = -862048943*(x4205);
    int x4207 = x4206<<(15);
    int x4208 = x4206 >> (-15 & (sizeof(x4206)-1));
    int x4209 = x4207|(x4208);
    int x4210 = x4209*(461845907);
    int x4211 = x4188;
    int x4212 = x4210^(x4211);
    int x4213 = x4212<<(13);
    int x4214 = x4212 >> (-13 & (sizeof(x4212)-1));
    int x4215 = x4213|(x4214);
    int x4216 = x4215*(5);
    int x4217 = x4216+(-430675100);
    x4188 = x4217;
    char* x4219 = x4187._6;
    int x4220 = HASH(x4219);
    int x4221 = -862048943*(x4220);
    int x4222 = x4221<<(15);
    int x4223 = x4221 >> (-15 & (sizeof(x4221)-1));
    int x4224 = x4222|(x4223);
    int x4225 = x4224*(461845907);
    int x4226 = x4188;
    int x4227 = x4225^(x4226);
    int x4228 = x4227<<(13);
    int x4229 = x4227 >> (-13 & (sizeof(x4227)-1));
    int x4230 = x4228|(x4229);
    int x4231 = x4230*(5);
    int x4232 = x4231+(-430675100);
    x4188 = x4232;
    int x4234 = x4188;
    int x4235 = x4234^(2);
    int x4236 = x4235 >> (16 & (sizeof(x4235)-1));
    int x4237 = x4235^(x4236);
    int x4238 = x4237*(-2048144789);
    int x4239 = x4238 >> (13 & (sizeof(x4238)-1));
    int x4240 = x4238^(x4239);
    int x4241 = x4240*(-1028477387);
    int x4242 = x4241 >> (16 & (sizeof(x4241)-1));
    int x4243 = x4241^(x4242);
    return x4243; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4245, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4246) { 
    int x4247 = x4245._2;
    int x4248 = x4246._2;
    int x4249 = x4247==(x4248);
    int ite17769 = 0;
    if(x4249) {
      
      int x4250 = x4245._3;
      int x4251 = x4246._3;
      int x4252 = x4250==(x4251);
      int x17770 = x4252;
      ite17769 = x17770;
    } else {
      
      ite17769 = 0;
    };
    int x17761 = ite17769;
    int ite17778 = 0;
    if(x17761) {
      
      char* x4254 = x4245._6;
      char* x4255 = x4246._6;
      int x4256 = strcmpi(x4254, x4255);
      int x17779 = x4256;
      ite17778 = x17779;
    } else {
      
      ite17778 = 0;
    };
    int x17763 = ite17778;
    int x4258 = x17763 ? 0 : 1;
    return x4258; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3740)  { 
    int x3741 = -889275714;
    int x3742 = x3740._1;
    int x3743 = HASH(x3742);
    int x3744 = -862048943*(x3743);
    int x3745 = x3744<<(15);
    int x3746 = x3744 >> (-15 & (sizeof(x3744)-1));
    int x3747 = x3745|(x3746);
    int x3748 = x3747*(461845907);
    int x3749 = x3741;
    int x3750 = x3748^(x3749);
    int x3751 = x3750<<(13);
    int x3752 = x3750 >> (-13 & (sizeof(x3750)-1));
    int x3753 = x3751|(x3752);
    int x3754 = x3753*(5);
    int x3755 = x3754+(-430675100);
    x3741 = x3755;
    int x3757 = x3740._2;
    int x3758 = HASH(x3757);
    int x3759 = -862048943*(x3758);
    int x3760 = x3759<<(15);
    int x3761 = x3759 >> (-15 & (sizeof(x3759)-1));
    int x3762 = x3760|(x3761);
    int x3763 = x3762*(461845907);
    int x3764 = x3741;
    int x3765 = x3763^(x3764);
    int x3766 = x3765<<(13);
    int x3767 = x3765 >> (-13 & (sizeof(x3765)-1));
    int x3768 = x3766|(x3767);
    int x3769 = x3768*(5);
    int x3770 = x3769+(-430675100);
    x3741 = x3770;
    int x3772 = x3740._3;
    int x3773 = HASH(x3772);
    int x3774 = -862048943*(x3773);
    int x3775 = x3774<<(15);
    int x3776 = x3774 >> (-15 & (sizeof(x3774)-1));
    int x3777 = x3775|(x3776);
    int x3778 = x3777*(461845907);
    int x3779 = x3741;
    int x3780 = x3778^(x3779);
    int x3781 = x3780<<(13);
    int x3782 = x3780 >> (-13 & (sizeof(x3780)-1));
    int x3783 = x3781|(x3782);
    int x3784 = x3783*(5);
    int x3785 = x3784+(-430675100);
    x3741 = x3785;
    int x3787 = x3741;
    int x3788 = x3787^(2);
    int x3789 = x3788 >> (16 & (sizeof(x3788)-1));
    int x3790 = x3788^(x3789);
    int x3791 = x3790*(-2048144789);
    int x3792 = x3791 >> (13 & (sizeof(x3791)-1));
    int x3793 = x3791^(x3792);
    int x3794 = x3793*(-1028477387);
    int x3795 = x3794 >> (16 & (sizeof(x3794)-1));
    int x3796 = x3794^(x3795);
    return x3796; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x3798, const struct SEntry8_IIIITIIB& x3799) { 
    int x3800 = x3798._1;
    int x3801 = x3799._1;
    int x3802 = x3800==(x3801);
    int ite17877 = 0;
    if(x3802) {
      
      int x3803 = x3798._2;
      int x3804 = x3799._2;
      int x3805 = x3803==(x3804);
      int x17878 = x3805;
      ite17877 = x17878;
    } else {
      
      ite17877 = 0;
    };
    int x17869 = ite17877;
    int ite17886 = 0;
    if(x17869) {
      
      int x3807 = x3798._3;
      int x3808 = x3799._3;
      int x3809 = x3807==(x3808);
      int x17887 = x3809;
      ite17886 = x17887;
    } else {
      
      ite17886 = 0;
    };
    int x17871 = ite17886;
    int x3811 = x17871 ? 0 : 1;
    return x3811; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3506)  { 
    int x3507 = -889275714;
    int x3508 = x3506._2;
    int x3509 = HASH(x3508);
    int x3510 = -862048943*(x3509);
    int x3511 = x3510<<(15);
    int x3512 = x3510 >> (-15 & (sizeof(x3510)-1));
    int x3513 = x3511|(x3512);
    int x3514 = x3513*(461845907);
    int x3515 = x3507;
    int x3516 = x3514^(x3515);
    int x3517 = x3516<<(13);
    int x3518 = x3516 >> (-13 & (sizeof(x3516)-1));
    int x3519 = x3517|(x3518);
    int x3520 = x3519*(5);
    int x3521 = x3520+(-430675100);
    x3507 = x3521;
    int x3523 = x3506._3;
    int x3524 = HASH(x3523);
    int x3525 = -862048943*(x3524);
    int x3526 = x3525<<(15);
    int x3527 = x3525 >> (-15 & (sizeof(x3525)-1));
    int x3528 = x3526|(x3527);
    int x3529 = x3528*(461845907);
    int x3530 = x3507;
    int x3531 = x3529^(x3530);
    int x3532 = x3531<<(13);
    int x3533 = x3531 >> (-13 & (sizeof(x3531)-1));
    int x3534 = x3532|(x3533);
    int x3535 = x3534*(5);
    int x3536 = x3535+(-430675100);
    x3507 = x3536;
    int x3538 = x3507;
    int x3539 = x3538^(2);
    int x3540 = x3539 >> (16 & (sizeof(x3539)-1));
    int x3541 = x3539^(x3540);
    int x3542 = x3541*(-2048144789);
    int x3543 = x3542 >> (13 & (sizeof(x3542)-1));
    int x3544 = x3542^(x3543);
    int x3545 = x3544*(-1028477387);
    int x3546 = x3545 >> (16 & (sizeof(x3545)-1));
    int x3547 = x3545^(x3546);
    return x3547; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry3_III& x3549, const struct SEntry3_III& x3550) { 
    int x3551 = x3549._1;
    int x3552 = x3550._1;
    int x3553 = x3551==(x3552);
    int x3554 = x3551>(x3552);
    int x3555 = x3554 ? 1 : -1;
    int x3556 = x3553 ? 0 : x3555;
    return x3556; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3814)  { 
    int x3815 = -889275714;
    int x3816 = x3814._2;
    int x3817 = HASH(x3816);
    int x3818 = -862048943*(x3817);
    int x3819 = x3818<<(15);
    int x3820 = x3818 >> (-15 & (sizeof(x3818)-1));
    int x3821 = x3819|(x3820);
    int x3822 = x3821*(461845907);
    int x3823 = x3815;
    int x3824 = x3822^(x3823);
    int x3825 = x3824<<(13);
    int x3826 = x3824 >> (-13 & (sizeof(x3824)-1));
    int x3827 = x3825|(x3826);
    int x3828 = x3827*(5);
    int x3829 = x3828+(-430675100);
    x3815 = x3829;
    int x3831 = x3814._3;
    int x3832 = HASH(x3831);
    int x3833 = -862048943*(x3832);
    int x3834 = x3833<<(15);
    int x3835 = x3833 >> (-15 & (sizeof(x3833)-1));
    int x3836 = x3834|(x3835);
    int x3837 = x3836*(461845907);
    int x3838 = x3815;
    int x3839 = x3837^(x3838);
    int x3840 = x3839<<(13);
    int x3841 = x3839 >> (-13 & (sizeof(x3839)-1));
    int x3842 = x3840|(x3841);
    int x3843 = x3842*(5);
    int x3844 = x3843+(-430675100);
    x3815 = x3844;
    int x3846 = x3814._4;
    int x3847 = HASH(x3846);
    int x3848 = -862048943*(x3847);
    int x3849 = x3848<<(15);
    int x3850 = x3848 >> (-15 & (sizeof(x3848)-1));
    int x3851 = x3849|(x3850);
    int x3852 = x3851*(461845907);
    int x3853 = x3815;
    int x3854 = x3852^(x3853);
    int x3855 = x3854<<(13);
    int x3856 = x3854 >> (-13 & (sizeof(x3854)-1));
    int x3857 = x3855|(x3856);
    int x3858 = x3857*(5);
    int x3859 = x3858+(-430675100);
    x3815 = x3859;
    int x3861 = x3815;
    int x3862 = x3861^(2);
    int x3863 = x3862 >> (16 & (sizeof(x3862)-1));
    int x3864 = x3862^(x3863);
    int x3865 = x3864*(-2048144789);
    int x3866 = x3865 >> (13 & (sizeof(x3865)-1));
    int x3867 = x3865^(x3866);
    int x3868 = x3867*(-1028477387);
    int x3869 = x3868 >> (16 & (sizeof(x3868)-1));
    int x3870 = x3868^(x3869);
    return x3870; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry8_IIIITIIB& x3872, const struct SEntry8_IIIITIIB& x3873) { 
    int x3874 = x3872._1;
    int x3875 = x3873._1;
    int x3876 = x3874==(x3875);
    int x3877 = x3874>(x3875);
    int x3878 = x3877 ? 1 : -1;
    int x3879 = x3876 ? 0 : x3878;
    return x3879; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3702)  { 
    int x3703 = 0;
    int x3704 = x3702._1;
    int x3705 = x3704-(1);
    int x3706 = x3703;
    int x3707 = x3706*(1);
    int x3708 = x3707+(x3705);
    x3703 = x3708;
    int x3710 = x3703;
    return x3710; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry9_ISSSSSSDD& x3699, const struct SEntry9_ISSSSSSDD& x3700) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3721)  { 
    int x3722 = 0;
    int x3723 = x3721._1;
    int x3724 = x3723-(1);
    int x3725 = x3722;
    int x3726 = x3725*(100000);
    int x3727 = x3726+(x3724);
    x3722 = x3727;
    int x3729 = x3722;
    return x3729; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry5_IISDS& x3718, const struct SEntry5_IISDS& x3719) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3966)  { 
    int x3967 = 0;
    int x3968 = x3966._1;
    int x3969 = x3968-(1);
    int x3970 = x3967;
    int x3971 = x3970*(10);
    int x3972 = x3971+(x3969);
    x3967 = x3972;
    int x3974 = x3966._2;
    int x3975 = x3974-(1);
    int x3976 = x3967;
    int x3977 = x3976*(1);
    int x3978 = x3977+(x3975);
    x3967 = x3978;
    int x3980 = x3967;
    return x3980; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry11_IISSSSSSDDI& x3963, const struct SEntry11_IISSSSSSDDI& x3964) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4164)  { 
    int x4165 = 0;
    int x4166 = x4164._1;
    int x4167 = x4166-(1);
    int x4168 = x4165;
    int x4169 = x4168*(3000);
    int x4170 = x4169+(x4167);
    x4165 = x4170;
    int x4172 = x4164._2;
    int x4173 = x4172-(1);
    int x4174 = x4165;
    int x4175 = x4174*(10);
    int x4176 = x4175+(x4173);
    x4165 = x4176;
    int x4178 = x4164._3;
    int x4179 = x4178-(1);
    int x4180 = x4165;
    int x4181 = x4180*(1);
    int x4182 = x4181+(x4179);
    x4165 = x4182;
    int x4184 = x4165;
    return x4184; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4161, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4162) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4270)  { 
    int x4271 = 0;
    int x4272 = x4270._1;
    int x4273 = x4272-(1);
    int x4274 = x4271;
    int x4275 = x4274*(100000);
    int x4276 = x4275+(x4273);
    x4271 = x4276;
    int x4278 = x4270._2;
    int x4279 = x4278-(1);
    int x4280 = x4271;
    int x4281 = x4280*(1);
    int x4282 = x4281+(x4279);
    x4271 = x4282;
    int x4284 = x4271;
    return x4284; 
  }
  FORCE_INLINE static bool cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x4267, const struct SEntry17_IIISSSSSSSSSSIIIS& x4268) { 
    return 0; 
  }
};

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>  newOrderTblIdx0Type;
typedef TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>  newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III,char ,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> >  newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblStoreType& x3616 = newOrderTbl;
newOrderTblIdx0Type& x721 = * (newOrderTblIdx0Type*) newOrderTbl.index[0];
newOrderTblIdx1Type& x722 = * (newOrderTblIdx1Type*) newOrderTbl.index[1];


typedef HashIndex< struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>  historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS,char ,
   HashIndex< struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> >  historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblStoreType& x3696 = historyTbl;
historyTblIdx0Type& x728 = * (historyTblIdx0Type*) historyTbl.index[0];


typedef ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1>  warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD,char ,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> >  warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblStoreType& x3715 = warehouseTbl;
warehouseTblIdx0Type& x733 = * (warehouseTblIdx0Type*) warehouseTbl.index[0];


typedef ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000>  itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS,char ,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> >  itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblStoreType& x3734 = itemTbl;
itemTblIdx0Type& x738 = * (itemTblIdx0Type*) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>  orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>  orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB,char ,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> >  orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblStoreType& x3958 = orderTbl;
orderTblIdx0Type& x745 = * (orderTblIdx0Type*) orderTbl.index[0];
orderTblIdx1Type& x746 = * (orderTblIdx1Type*) orderTbl.index[1];


typedef ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10>  districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI,char ,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> >  districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblStoreType& x3985 = districtTbl;
districtTblIdx0Type& x752 = * (districtTblIdx0Type*) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>  orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>  orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS,char ,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> >  orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblStoreType& x4157 = orderLineTbl;
orderLineTblIdx0Type& x757 = * (orderLineTblIdx0Type*) orderLineTbl.index[0];
orderLineTblIdx1Type& x758 = * (orderLineTblIdx1Type*) orderLineTbl.index[1];


typedef ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>  customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>  customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS,char ,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> >  customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblStoreType& x4263 = customerTbl;
customerTblIdx0Type& x764 = * (customerTblIdx0Type*) customerTbl.index[0];
customerTblIdx1Type& x765 = * (customerTblIdx1Type*) customerTbl.index[1];


typedef ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000>  stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS,char ,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> >  stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblStoreType& x4289 = stockTbl;
stockTblIdx0Type& x770 = * (stockTblIdx0Type*) stockTbl.index[0];

struct SEntry9_ISSSSSSDD x7470;
struct SEntry3_III x6883;
struct SEntry10_IIIIIITIDS x7035;
struct SEntry5_IISDS x7445;
struct SEntry11_IISSSSSSDDI x7473;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7110;
struct SEntry17_IIISSSSSSSSSSIIIS x7497;
struct SEntry8_IIIITIIB x7099;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7288;
struct SEntry10_IIIIIITIDS x6904;
struct SEntry17_IIISSSSSSSSSSIIIS x7058;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7271;
struct SEntry11_IISSSSSSDDI x7230;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6908;
struct SEntry11_IISSSSSSDDI x7022;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7127;
struct SEntry9_ISSSSSSDD x7224;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7466;
struct SEntry8_IIIITIIB x6895;


void DeliveryTx(int x10, Date x11, int x12, int x13) {
  int x14[10];
  int x15 = 1;
  while(1) {
    
    int x16 = x15;
    if (!((x16<=(10)))) break; 
    
    int x22 = x15;
    x6883._2 = x22;
    x6883._3 = x12;
    struct SEntry3_III* x11430 = x722.get(x6883);
    if((x11430!=(NULL))) {
      int x6889 = x11430->_1;
      int x29 = x15;
      x14[(x29-(1))] = x6889;
      x3616.del(x11430);
      int x33 = x15;
      x6895._1 = x6889;
      x6895._2 = x33;
      x6895._3 = x12;
      struct SEntry8_IIIITIIB* x11443 = x745.get(x6895);
      int x6898 = x11443->_4;
      x11443->_6 = x13;
      double x40 = 0.0;
      int x41 = x15;
      x6904._1 = x6889;
      x6904._2 = x41;
      x6904._3 = x12;
      x758.slice(x6904, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* x44 = const_cast < struct SEntry10_IIIIIITIDS*>(&sliceVar);
        x44->_7 = x11;
        double x46 = x40;
        double x6953 = x44->_9;
        x40 = (x46+(x6953));
      
      }));;
      int x53 = x15;
      x6908._1 = x6898;
      x6908._2 = x53;
      x6908._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11464 = x764.get(x6908);
      double x56 = x40;
      x11464->_17 += x56;
      x11464->_20 += 1;
    } else {
      
      int x60 = x15;
      x14[(x60-(1))] = 0;
    };
    int x64 = x15;
    x15 = (x64+(1));
  };
}
void StockLevelTx(int x68, Date x69, int x70, int x71, int x72, int x73) {
  x7022._1 = x72;
  x7022._2 = x71;
  struct SEntry11_IISSSSSSDDI* x11533 = x752.get(x7022);
  int x7026 = x11533->_11;
  int x79 = (x7026-(20));
  unordered_set<int> x80;
  while(1) {
    
    int x81 = x79;
    if (!((x81<(x7026)))) break; 
    
    int x83 = x79;
    x7035._1 = x83;
    x7035._2 = x72;
    x7035._3 = x71;
    x758.slice(x7035, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* x86 = const_cast < struct SEntry10_IIIIIITIDS*>(&sliceVar);
      int x7057 = x86->_5;
      x7058._1 = x7057;
      x7058._2 = x71;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11551 = x770.get(x7058);
      int x7060 = x11551->_3;
      if((x7060<(x73))) {
        x80.insert(x7057);
      };
    
    }));;
    int x96 = x79;
    x79 = (x96+(1));
  };
}
void OrderStatusTx(int x101, Date x102, int x103, int x104, int x105, int x106, int x107, char* x108) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite14897 = NULL;
  if((x106>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14898;
    x7110._2 = x105;
    x7110._3 = x104;
    x7110._6 = x108;
    x765.slice(x7110, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x113 = const_cast < struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x14898.push_back(x113);
    
    }));;
    int x14906 = x14898.size();
    int x14908 = (x14906/(2));
    int x14909 = x14898.size();
    if(((x14909%(2))==(0))) {
      int x123 = x14908;
      x14908 = (x123-(1));
    };
    sort(x14898.begin(), x14898.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS*  x127, struct SEntry21_IIISSSSSSSSSTSDDDDIIS*  x128) {
      
      char* x7162 = x127->_4;
      char* x7163 = x128->_4;
      int x131 = strcmpi(x7162, x7163);
      return (x131<(0)); 
    }));
    int x14924 = x14908;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14925 = x14898[x14924];
    ite14897 = x14925;
  } else {
    
    x7127._1 = x107;
    x7127._2 = x105;
    x7127._3 = x104;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14930 = x764.get(x7127);
    ite14897 = x14930;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7096 = ite14897;
  int x7097 = x7096->_3;
  x7099._2 = x105;
  x7099._3 = x104;
  x7099._4 = x7097;
  struct SEntry8_IIIITIIB* x11635 = x746.get(x7099);
  int x150 = 0;
  int x7104 = x11635->_1;
  x150 = x7104;
}
void PaymentTx(int x153, Date x154, int x155, int x156, int x157, int x158, int x159, int x160, int x161, char* x162, double x163) {
  x7224._1 = x156;
  struct SEntry9_ISSSSSSDD* x11690 = x733.get(x7224);
  x11690->_9 += x163;
  x7230._1 = x157;
  x7230._2 = x156;
  struct SEntry11_IISSSSSSDDI* x11695 = x752.get(x7230);
  x11695->_10 += x163;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite14996 = NULL;
  if((x158>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14997;
    x7271._2 = x160;
    x7271._3 = x159;
    x7271._6 = x162;
    x765.slice(x7271, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x178 = const_cast < struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x14997.push_back(x178);
    
    }));;
    int x15005 = x14997.size();
    int x15007 = (x15005/(2));
    int x15008 = x14997.size();
    if(((x15008%(2))==(0))) {
      int x188 = x15007;
      x15007 = (x188-(1));
    };
    sort(x14997.begin(), x14997.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS*  x192, struct SEntry21_IIISSSSSSSSSTSDDDDIIS*  x193) {
      
      char* x7343 = x192->_4;
      char* x7344 = x193->_4;
      int x196 = strcmpi(x7343, x7344);
      return (x196<(0)); 
    }));
    int x15023 = x15007;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15024 = x14997[x15023];
    ite14996 = x15024;
  } else {
    
    x7288._1 = x161;
    x7288._2 = x160;
    x7288._3 = x159;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15029 = x764.get(x7288);
    ite14996 = x15029;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7236 = ite14996;
  char* x7237 = x7236->_21;
  char* x7238 = x7236->_14;
  char* x16265 = strstr(x7238, "BC");
  if((x16265!=(NULL))) {
    int x7241 = x7236->_1;
    char* x211 = new char[501];
    snprintf(x211, 500, "%d %d %d %d %d $%f %s | %s", x7241,x160,x159,x157,x156,x163,IntToStrDate(x154),x7237);
    x7236->_17 += x163;
    x7236->_21 = x211;
  } else {
    
    x7236->_17 += x163;
  };
  char* x7248 = x11690->_2;
  char* x7249 = x11695->_3;
  char* x220 = new char[25];
  snprintf(x220, 24, "%.10s    %.10s", x7248,x7249);
  int x7252 = x7236->_1;
  struct SEntry8_IIIIITDS* x15863 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x15863, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x15863->_1 = x7252; x15863->_2 = x160; x15863->_3 = x159; x15863->_4 = x157; x15863->_5 = x156; x15863->_6 = x154; x15863->_7 = x163; x15863->_8 = x220;
  x3696.add(x15863);
}
void NewOrderTx(int x225, Date x226, int x227, int x228, int x229, int x230, int x231, int x232, int* x233, int* x234, int* x235, double* x236, char** x237, int* x238, char** x239, double* x240) {
  int x241 = 0;
  int x242 = 0;
  char* x243[x231];
  int x244 = 1;
  while(1) {
    
    int x245 = x241;
    int ite15287 = 0;
    if((x245<(x231))) {
      
      int x247 = x244;
      int x15288 = x247;
      ite15287 = x15288;
    } else {
      
      ite15287 = 0;
    };
    int x15119 = ite15287;
    if (!(x15119)) break; 
    
    int x249 = x241;
    int x250 = x233[x249];
    x7445._1 = x250;
    struct SEntry5_IISDS* x11829 = x738.get(x7445);
    if((x11829==(NULL))) {
      x244 = 0;
    } else {
      
      int x256 = x241;
      char* x7453 = x11829->_3;
      x237[x256] = x7453;
      int x259 = x241;
      double x7456 = x11829->_4;
      x236[x259] = x7456;
      int x262 = x241;
      char* x7459 = x11829->_5;
      x243[x262] = x7459;
    };
    int x266 = x241;
    x241 = (x266+(1));
  };
  int x270 = x244;
  if(x270) {
    x7466._1 = x230;
    x7466._2 = x229;
    x7466._3 = x228;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11852 = x764.get(x7466);
    x7470._1 = x228;
    struct SEntry9_ISSSSSSDD* x11855 = x733.get(x7470);
    x7473._1 = x229;
    x7473._2 = x228;
    struct SEntry11_IISSSSSSDDI* x11859 = x752.get(x7473);
    int x7476 = x11859->_11;
    x11859->_11 += 1;
    struct SEntry8_IIIITIIB* x15914 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x15914, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x15914->_1 = x7476; x15914->_2 = x229; x15914->_3 = x228; x15914->_4 = x230; x15914->_5 = x226; x15914->_6 = -1; x15914->_7 = x231; x15914->_8 = (x232>(0));
    x3958.add(x15914);
    struct SEntry3_III* x15918 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x15918, 0, 1 * sizeof(struct SEntry3_III));
    x15918->_1 = x7476; x15918->_2 = x229; x15918->_3 = x228;
    x3616.add(x15918);
    double x290 = 0.0;
    x241 = 0;
    while(1) {
      
      int x292 = x241;
      if (!((x292<(x231)))) break; 
      
      int x294 = x241;
      int x295 = x234[x294];
      int x296 = x241;
      int x297 = x233[x296];
      int x298 = x241;
      int x299 = x235[x298];
      x7497._1 = x297;
      x7497._2 = x295;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11882 = x770.get(x7497);
      char* ite15173 = NULL;
      if((x229==(1))) {
        char* x15174 = x11882->_4;
        ite15173 = x15174;
      } else {
        
        char* ite15178 = NULL;
        if((x229==(2))) {
          char* x15179 = x11882->_5;
          ite15178 = x15179;
        } else {
          
          char* ite15183 = NULL;
          if((x229==(3))) {
            char* x15184 = x11882->_6;
            ite15183 = x15184;
          } else {
            
            char* ite15188 = NULL;
            if((x229==(4))) {
              char* x15189 = x11882->_7;
              ite15188 = x15189;
            } else {
              
              char* ite15193 = NULL;
              if((x229==(5))) {
                char* x15194 = x11882->_8;
                ite15193 = x15194;
              } else {
                
                char* ite15198 = NULL;
                if((x229==(6))) {
                  char* x15199 = x11882->_9;
                  ite15198 = x15199;
                } else {
                  
                  char* ite15203 = NULL;
                  if((x229==(7))) {
                    char* x15204 = x11882->_10;
                    ite15203 = x15204;
                  } else {
                    
                    char* ite15208 = NULL;
                    if((x229==(8))) {
                      char* x15209 = x11882->_11;
                      ite15208 = x15209;
                    } else {
                      
                      char* ite15213 = NULL;
                      if((x229==(9))) {
                        char* x15214 = x11882->_12;
                        ite15213 = x15214;
                      } else {
                        
                        char* x15216 = x11882->_13;
                        ite15213 = x15216;
                      };
                      char* x15212 = ite15213;
                      ite15208 = x15212;
                    };
                    char* x15207 = ite15208;
                    ite15203 = x15207;
                  };
                  char* x15202 = ite15203;
                  ite15198 = x15202;
                };
                char* x15197 = ite15198;
                ite15193 = x15197;
              };
              char* x15192 = ite15193;
              ite15188 = x15192;
            };
            char* x15187 = ite15188;
            ite15183 = x15187;
          };
          char* x15182 = ite15183;
          ite15178 = x15182;
        };
        char* x15177 = ite15178;
        ite15173 = x15177;
      };
      char* x329 = ite15173;
      int x7527 = x11882->_3;
      int x331 = x241;
      x238[x331] = x7527;
      char* x7530 = x11852->_14;
      char* x16485 = strstr(x7530, "original");
      int ite15414 = 0;
      if((x16485!=(NULL))) {
        
        char* x7533 = x11882->_17;
        char* x16491 = strstr(x7533, "original");
        int x15415 = (x16491!=(NULL));
        ite15414 = x15415;
      } else {
        
        ite15414 = 0;
      };
      int x15241 = ite15414;
      if(x15241) {
        int x338 = x241;
        x239[x338][0] = 'B';
        x239[x338][1] = 0;
      } else {
        
        int x340 = x241;
        x239[x340][0] = 'G';
        x239[x340][1] = 0;
      };
      x11882->_3 = (x7527-(x299));
      if((x7527<=(x299))) {
        x11882->_3 += 91;
      };
      int x348 = 0;
      if((x295!=(x228))) {
        x348 = 1;
      };
      double x7550 = x11852->_16;
      double x7551 = x11855->_8;
      double x7552 = x11859->_9;
      int x356 = x241;
      double x357 = x236[x356];
      double x364 = ((x299*(x357))*(((1.0+(x7551))+(x7552))))*((1.0-(x7550)));
      int x365 = x241;
      x240[x365] = x364;
      double x367 = x290;
      x290 = (x367+(x364));
      int x370 = x241;
      struct SEntry10_IIIIIITIDS* x16045 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x16045, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x16045->_1 = x7476; x16045->_2 = x229; x16045->_3 = x228; x16045->_4 = (x370+(1)); x16045->_5 = x297; x16045->_6 = x295; x16045->_7 = -1; x16045->_8 = x299; x16045->_9 = x364; x16045->_10 = x329;
      x4157.add(x16045);
      int x375 = x241;
      x241 = (x375+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  TPCCDataGen tpcc;
  tpcc.loadPrograms();
  tpcc.loadWare(warehouseTbl);
  tpcc.loadDist(districtTbl);
  tpcc.loadCust(customerTbl);
  tpcc.loadItem(itemTbl);
  tpcc.loadNewOrd(newOrderTbl);
  tpcc.loadOrders(orderTbl);
  tpcc.loadOrdLine(orderLineTbl);
  tpcc.loadHist(historyTbl);
  tpcc.loadStocks(stockTbl);
  
  for(int i=0; i<numPrograms; ++i){
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
  
        
}
/* ----------- FUNCTIONS ----------- */
