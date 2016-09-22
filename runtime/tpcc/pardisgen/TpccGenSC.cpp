#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
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
      else if (c1 == c2)
          continue;
      else if (c1 < c2)
          return true;
      else return false;
   }
}

typedef unsigned int Date;
     
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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4123)  { 
    int x4124 = -889275714;
    int x4125 = x4123._1;
    int x4127 = -862048943*((HASH(x4125)));
    int x4132 = x4124;
    int x4133 = (((x4127<<(15))|((x4127 >> (-15 & (sizeof(x4127)-1)))))*(461845907))^(x4132);
    x4124 = ((((x4133<<(13))|((x4133 >> (-13 & (sizeof(x4133)-1)))))*(5))+(-430675100));
    int x4140 = x4123._2;
    int x4142 = -862048943*((HASH(x4140)));
    int x4147 = x4124;
    int x4148 = (((x4142<<(15))|((x4142 >> (-15 & (sizeof(x4142)-1)))))*(461845907))^(x4147);
    x4124 = ((((x4148<<(13))|((x4148 >> (-13 & (sizeof(x4148)-1)))))*(5))+(-430675100));
    int x4155 = x4123._3;
    int x4157 = -862048943*((HASH(x4155)));
    int x4162 = x4124;
    int x4163 = (((x4157<<(15))|((x4157 >> (-15 & (sizeof(x4157)-1)))))*(461845907))^(x4162);
    x4124 = ((((x4163<<(13))|((x4163 >> (-13 & (sizeof(x4163)-1)))))*(5))+(-430675100));
    int x4170 = x4123._4;
    int x4172 = -862048943*((HASH(x4170)));
    int x4177 = x4124;
    int x4178 = (((x4172<<(15))|((x4172 >> (-15 & (sizeof(x4172)-1)))))*(461845907))^(x4177);
    x4124 = ((((x4178<<(13))|((x4178 >> (-13 & (sizeof(x4178)-1)))))*(5))+(-430675100));
    int x4185 = x4124;
    int x4186 = x4185^(2);
    int x4189 = (x4186^((x4186 >> (16 & (sizeof(x4186)-1)))))*(-2048144789);
    int x4192 = (x4189^((x4189 >> (13 & (sizeof(x4189)-1)))))*(-1028477387);
    return (x4192^((x4192 >> (16 & (sizeof(x4192)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4196, const struct SEntry10_IIIIIITIDS& x4197) { 
    int x4198 = x4196._1;
    int x4199 = x4197._1;
    int ite16943 = 0;
    if((x4198==(x4199))) {
      
      int x4201 = x4196._2;
      int x4202 = x4197._2;
      int x16944 = (x4201==(x4202));
      ite16943 = x16944;
    } else {
      
      ite16943 = 0;
    };
    int x16933 = ite16943;
    int ite16952 = 0;
    if(x16933) {
      
      int x4205 = x4196._3;
      int x4206 = x4197._3;
      int x16953 = (x4205==(x4206));
      ite16952 = x16953;
    } else {
      
      ite16952 = 0;
    };
    int x16935 = ite16952;
    int ite16961 = 0;
    if(x16935) {
      
      int x4209 = x4196._4;
      int x4210 = x4197._4;
      int x16962 = (x4209==(x4210));
      ite16961 = x16962;
    } else {
      
      ite16961 = 0;
    };
    int x16937 = ite16961;
    return (x16937 ? 0 : 1); 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4017)  { 
    int x4018 = -889275714;
    int x4019 = x4017._2;
    int x4021 = -862048943*((HASH(x4019)));
    int x4026 = x4018;
    int x4027 = (((x4021<<(15))|((x4021 >> (-15 & (sizeof(x4021)-1)))))*(461845907))^(x4026);
    x4018 = ((((x4027<<(13))|((x4027 >> (-13 & (sizeof(x4027)-1)))))*(5))+(-430675100));
    int x4034 = x4017._3;
    int x4036 = -862048943*((HASH(x4034)));
    int x4041 = x4018;
    int x4042 = (((x4036<<(15))|((x4036 >> (-15 & (sizeof(x4036)-1)))))*(461845907))^(x4041);
    x4018 = ((((x4042<<(13))|((x4042 >> (-13 & (sizeof(x4042)-1)))))*(5))+(-430675100));
    int x4049 = x4017._4;
    int x4051 = -862048943*((HASH(x4049)));
    int x4056 = x4018;
    int x4057 = (((x4051<<(15))|((x4051 >> (-15 & (sizeof(x4051)-1)))))*(461845907))^(x4056);
    x4018 = ((((x4057<<(13))|((x4057 >> (-13 & (sizeof(x4057)-1)))))*(5))+(-430675100));
    int x4064 = x4018;
    int x4065 = x4064^(2);
    int x4068 = (x4065^((x4065 >> (16 & (sizeof(x4065)-1)))))*(-2048144789);
    int x4071 = (x4068^((x4068 >> (13 & (sizeof(x4068)-1)))))*(-1028477387);
    return (x4071^((x4071 >> (16 & (sizeof(x4071)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x4075, const struct SEntry8_IIIITIIB& x4076) { 
    int x4077 = x4075._2;
    int x4078 = x4076._2;
    int ite17069 = 0;
    if((x4077==(x4078))) {
      
      int x4080 = x4075._3;
      int x4081 = x4076._3;
      int x17070 = (x4080==(x4081));
      ite17069 = x17070;
    } else {
      
      ite17069 = 0;
    };
    int x17061 = ite17069;
    int ite17078 = 0;
    if(x17061) {
      
      int x4084 = x4075._4;
      int x4085 = x4076._4;
      int x17079 = (x4084==(x4085));
      ite17078 = x17079;
    } else {
      
      ite17078 = 0;
    };
    int x17063 = ite17078;
    return (x17063 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3567)  { 
    int x3568 = -889275714;
    int x3569 = x3567._1;
    int x3571 = -862048943*((HASH(x3569)));
    int x3576 = x3568;
    int x3577 = (((x3571<<(15))|((x3571 >> (-15 & (sizeof(x3571)-1)))))*(461845907))^(x3576);
    x3568 = ((((x3577<<(13))|((x3577 >> (-13 & (sizeof(x3577)-1)))))*(5))+(-430675100));
    int x3584 = x3567._2;
    int x3586 = -862048943*((HASH(x3584)));
    int x3591 = x3568;
    int x3592 = (((x3586<<(15))|((x3586 >> (-15 & (sizeof(x3586)-1)))))*(461845907))^(x3591);
    x3568 = ((((x3592<<(13))|((x3592 >> (-13 & (sizeof(x3592)-1)))))*(5))+(-430675100));
    int x3599 = x3567._3;
    int x3601 = -862048943*((HASH(x3599)));
    int x3606 = x3568;
    int x3607 = (((x3601<<(15))|((x3601 >> (-15 & (sizeof(x3601)-1)))))*(461845907))^(x3606);
    x3568 = ((((x3607<<(13))|((x3607 >> (-13 & (sizeof(x3607)-1)))))*(5))+(-430675100));
    int x3614 = x3568;
    int x3615 = x3614^(2);
    int x3618 = (x3615^((x3615 >> (16 & (sizeof(x3615)-1)))))*(-2048144789);
    int x3621 = (x3618^((x3618 >> (13 & (sizeof(x3618)-1)))))*(-1028477387);
    return (x3621^((x3621 >> (16 & (sizeof(x3621)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3625, const struct SEntry3_III& x3626) { 
    int x3627 = x3625._1;
    int x3628 = x3626._1;
    int ite17177 = 0;
    if((x3627==(x3628))) {
      
      int x3630 = x3625._2;
      int x3631 = x3626._2;
      int x17178 = (x3630==(x3631));
      ite17177 = x17178;
    } else {
      
      ite17177 = 0;
    };
    int x17169 = ite17177;
    int ite17186 = 0;
    if(x17169) {
      
      int x3634 = x3625._3;
      int x3635 = x3626._3;
      int x17187 = (x3634==(x3635));
      ite17186 = x17187;
    } else {
      
      ite17186 = 0;
    };
    int x17171 = ite17186;
    return (x17171 ? 0 : 1); 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4216)  { 
    int x4217 = -889275714;
    int x4218 = x4216._1;
    int x4220 = -862048943*((HASH(x4218)));
    int x4225 = x4217;
    int x4226 = (((x4220<<(15))|((x4220 >> (-15 & (sizeof(x4220)-1)))))*(461845907))^(x4225);
    x4217 = ((((x4226<<(13))|((x4226 >> (-13 & (sizeof(x4226)-1)))))*(5))+(-430675100));
    int x4233 = x4216._2;
    int x4235 = -862048943*((HASH(x4233)));
    int x4240 = x4217;
    int x4241 = (((x4235<<(15))|((x4235 >> (-15 & (sizeof(x4235)-1)))))*(461845907))^(x4240);
    x4217 = ((((x4241<<(13))|((x4241 >> (-13 & (sizeof(x4241)-1)))))*(5))+(-430675100));
    int x4248 = x4216._3;
    int x4250 = -862048943*((HASH(x4248)));
    int x4255 = x4217;
    int x4256 = (((x4250<<(15))|((x4250 >> (-15 & (sizeof(x4250)-1)))))*(461845907))^(x4255);
    x4217 = ((((x4256<<(13))|((x4256 >> (-13 & (sizeof(x4256)-1)))))*(5))+(-430675100));
    int x4263 = x4217;
    int x4264 = x4263^(2);
    int x4267 = (x4264^((x4264 >> (16 & (sizeof(x4264)-1)))))*(-2048144789);
    int x4270 = (x4267^((x4267 >> (13 & (sizeof(x4267)-1)))))*(-1028477387);
    return (x4270^((x4270 >> (16 & (sizeof(x4270)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4274, const struct SEntry10_IIIIIITIDS& x4275) { 
    int x4276 = x4274._1;
    int x4277 = x4275._1;
    int ite17285 = 0;
    if((x4276==(x4277))) {
      
      int x4279 = x4274._2;
      int x4280 = x4275._2;
      int x17286 = (x4279==(x4280));
      ite17285 = x17286;
    } else {
      
      ite17285 = 0;
    };
    int x17277 = ite17285;
    int ite17294 = 0;
    if(x17277) {
      
      int x4283 = x4274._3;
      int x4284 = x4275._3;
      int x17295 = (x4283==(x4284));
      ite17294 = x17295;
    } else {
      
      ite17294 = 0;
    };
    int x17279 = ite17294;
    return (x17279 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3694)  { 
    int x3695 = -889275714;
    int x3696 = x3694._2;
    int x3698 = -862048943*((HASH(x3696)));
    int x3703 = x3695;
    int x3704 = (((x3698<<(15))|((x3698 >> (-15 & (sizeof(x3698)-1)))))*(461845907))^(x3703);
    x3695 = ((((x3704<<(13))|((x3704 >> (-13 & (sizeof(x3704)-1)))))*(5))+(-430675100));
    int x3711 = x3694._3;
    int x3713 = -862048943*((HASH(x3711)));
    int x3718 = x3695;
    int x3719 = (((x3713<<(15))|((x3713 >> (-15 & (sizeof(x3713)-1)))))*(461845907))^(x3718);
    x3695 = ((((x3719<<(13))|((x3719 >> (-13 & (sizeof(x3719)-1)))))*(5))+(-430675100));
    int x3726 = x3695;
    int x3727 = x3726^(2);
    int x3730 = (x3727^((x3727 >> (16 & (sizeof(x3727)-1)))))*(-2048144789);
    int x3733 = (x3730^((x3730 >> (13 & (sizeof(x3730)-1)))))*(-1028477387);
    return (x3733^((x3733 >> (16 & (sizeof(x3733)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3737, const struct SEntry3_III& x3738) { 
    int x3739 = x3737._2;
    int x3740 = x3738._2;
    int ite17376 = 0;
    if((x3739==(x3740))) {
      
      int x3742 = x3737._3;
      int x3743 = x3738._3;
      int x17377 = (x3742==(x3743));
      ite17376 = x17377;
    } else {
      
      ite17376 = 0;
    };
    int x17370 = ite17376;
    return (x17370 ? 0 : 1); 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3756)  { 
    int x3757 = -889275714;
    int x3758 = x3757;
    int x3759 = x3758^(2);
    int x3762 = (x3759^((x3759 >> (16 & (sizeof(x3759)-1)))))*(-2048144789);
    int x3765 = (x3762^((x3762 >> (13 & (sizeof(x3762)-1)))))*(-1028477387);
    return (x3765^((x3765 >> (16 & (sizeof(x3765)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIIITDS& x3769, const struct SEntry8_IIIIITDS& x3770) { 
    int x3771 = x3769._1;
    int x3772 = x3770._1;
    int ite17433 = 0;
    if((x3771==(-1))) {
      ite17433 = 1;
    } else {
      
      
      int x17435 = (x3772==(-1));
      ite17433 = x17435;
    };
    int x17413 = ite17433;
    int ite17440 = 0;
    if(x17413) {
      ite17440 = 1;
    } else {
      
      
      int x17442 = (x3771==(x3772));
      ite17440 = x17442;
    };
    int x17415 = ite17440;
    int ite17447 = 0;
    if(x17415) {
      
      int x3778 = x3769._2;
      int x3779 = x3770._2;
      int ite17549 = 0;
      if((x3778==(-1))) {
        ite17549 = 1;
      } else {
        
        
        int x17551 = (x3779==(-1));
        ite17549 = x17551;
      };
      int x17453 = ite17549;
      int ite17556 = 0;
      if(x17453) {
        ite17556 = 1;
      } else {
        
        
        int x17558 = (x3778==(x3779));
        ite17556 = x17558;
      };
      int x17455 = ite17556;
      int x17448 = x17455;
      ite17447 = x17448;
    } else {
      
      ite17447 = 0;
    };
    int x17417 = ite17447;
    int ite17460 = 0;
    if(x17417) {
      
      int x3786 = x3769._3;
      int x3787 = x3770._3;
      int ite17572 = 0;
      if((x3786==(-1))) {
        ite17572 = 1;
      } else {
        
        
        int x17574 = (x3787==(-1));
        ite17572 = x17574;
      };
      int x17466 = ite17572;
      int ite17579 = 0;
      if(x17466) {
        ite17579 = 1;
      } else {
        
        
        int x17581 = (x3786==(x3787));
        ite17579 = x17581;
      };
      int x17468 = ite17579;
      int x17461 = x17468;
      ite17460 = x17461;
    } else {
      
      ite17460 = 0;
    };
    int x17419 = ite17460;
    int ite17473 = 0;
    if(x17419) {
      
      int x3794 = x3769._4;
      int x3795 = x3770._4;
      int ite17595 = 0;
      if((x3794==(-1))) {
        ite17595 = 1;
      } else {
        
        
        int x17597 = (x3795==(-1));
        ite17595 = x17597;
      };
      int x17479 = ite17595;
      int ite17602 = 0;
      if(x17479) {
        ite17602 = 1;
      } else {
        
        
        int x17604 = (x3794==(x3795));
        ite17602 = x17604;
      };
      int x17481 = ite17602;
      int x17474 = x17481;
      ite17473 = x17474;
    } else {
      
      ite17473 = 0;
    };
    int x17421 = ite17473;
    int ite17486 = 0;
    if(x17421) {
      
      int x3802 = x3769._5;
      int x3803 = x3770._5;
      int ite17618 = 0;
      if((x3802==(-1))) {
        ite17618 = 1;
      } else {
        
        
        int x17620 = (x3803==(-1));
        ite17618 = x17620;
      };
      int x17492 = ite17618;
      int ite17625 = 0;
      if(x17492) {
        ite17625 = 1;
      } else {
        
        
        int x17627 = (x3802==(x3803));
        ite17625 = x17627;
      };
      int x17494 = ite17625;
      int x17487 = x17494;
      ite17486 = x17487;
    } else {
      
      ite17486 = 0;
    };
    int x17423 = ite17486;
    int ite17499 = 0;
    if(x17423) {
      
      Date x3810 = x3769._6;
      Date x3811 = x3770._6;
      int ite17641 = 0;
      if((x3810==(NULL))) {
        ite17641 = 1;
      } else {
        
        
        int x17643 = (x3811==(NULL));
        ite17641 = x17643;
      };
      int x17505 = ite17641;
      int ite17648 = 0;
      if(x17505) {
        ite17648 = 1;
      } else {
        
        
        int x17650 = (x3810==(x3811));
        ite17648 = x17650;
      };
      int x17507 = ite17648;
      int x17500 = x17507;
      ite17499 = x17500;
    } else {
      
      ite17499 = 0;
    };
    int x17425 = ite17499;
    int ite17512 = 0;
    if(x17425) {
      
      double x3818 = x3769._7;
      double x3819 = x3770._7;
      int ite17664 = 0;
      if((x3818==(-1.0))) {
        ite17664 = 1;
      } else {
        
        
        int x17666 = (x3819==(-1.0));
        ite17664 = x17666;
      };
      int x17518 = ite17664;
      int ite17671 = 0;
      if(x17518) {
        ite17671 = 1;
      } else {
        
        
        int x17673 = (x3818==(x3819));
        ite17671 = x17673;
      };
      int x17520 = ite17671;
      int x17513 = x17520;
      ite17512 = x17513;
    } else {
      
      ite17512 = 0;
    };
    int x17427 = ite17512;
    return (x17427 ? 0 : 1); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4322)  { 
    int x4323 = -889275714;
    int x4324 = x4322._2;
    int x4326 = -862048943*((HASH(x4324)));
    int x4331 = x4323;
    int x4332 = (((x4326<<(15))|((x4326 >> (-15 & (sizeof(x4326)-1)))))*(461845907))^(x4331);
    x4323 = ((((x4332<<(13))|((x4332 >> (-13 & (sizeof(x4332)-1)))))*(5))+(-430675100));
    int x4339 = x4322._3;
    int x4341 = -862048943*((HASH(x4339)));
    int x4346 = x4323;
    int x4347 = (((x4341<<(15))|((x4341 >> (-15 & (sizeof(x4341)-1)))))*(461845907))^(x4346);
    x4323 = ((((x4347<<(13))|((x4347 >> (-13 & (sizeof(x4347)-1)))))*(5))+(-430675100));
    char* x4354 = x4322._6;
    int x4356 = -862048943*((HASH(x4354)));
    int x4361 = x4323;
    int x4362 = (((x4356<<(15))|((x4356 >> (-15 & (sizeof(x4356)-1)))))*(461845907))^(x4361);
    x4323 = ((((x4362<<(13))|((x4362 >> (-13 & (sizeof(x4362)-1)))))*(5))+(-430675100));
    int x4369 = x4323;
    int x4370 = x4369^(2);
    int x4373 = (x4370^((x4370 >> (16 & (sizeof(x4370)-1)))))*(-2048144789);
    int x4376 = (x4373^((x4373 >> (13 & (sizeof(x4373)-1)))))*(-1028477387);
    return (x4376^((x4376 >> (16 & (sizeof(x4376)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4380, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4381) { 
    int x4382 = x4380._2;
    int x4383 = x4381._2;
    int ite17905 = 0;
    if((x4382==(x4383))) {
      
      int x4385 = x4380._3;
      int x4386 = x4381._3;
      int x17906 = (x4385==(x4386));
      ite17905 = x17906;
    } else {
      
      ite17905 = 0;
    };
    int x17897 = ite17905;
    int ite17914 = 0;
    if(x17897) {
      
      char* x4389 = x4380._6;
      char* x4390 = x4381._6;
      int x17915 = (x4389==(x4390));
      ite17914 = x17915;
    } else {
      
      ite17914 = 0;
    };
    int x17899 = ite17914;
    return (x17899 ? 0 : 1); 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3875)  { 
    int x3876 = -889275714;
    int x3877 = x3875._1;
    int x3879 = -862048943*((HASH(x3877)));
    int x3884 = x3876;
    int x3885 = (((x3879<<(15))|((x3879 >> (-15 & (sizeof(x3879)-1)))))*(461845907))^(x3884);
    x3876 = ((((x3885<<(13))|((x3885 >> (-13 & (sizeof(x3885)-1)))))*(5))+(-430675100));
    int x3892 = x3875._2;
    int x3894 = -862048943*((HASH(x3892)));
    int x3899 = x3876;
    int x3900 = (((x3894<<(15))|((x3894 >> (-15 & (sizeof(x3894)-1)))))*(461845907))^(x3899);
    x3876 = ((((x3900<<(13))|((x3900 >> (-13 & (sizeof(x3900)-1)))))*(5))+(-430675100));
    int x3907 = x3875._3;
    int x3909 = -862048943*((HASH(x3907)));
    int x3914 = x3876;
    int x3915 = (((x3909<<(15))|((x3909 >> (-15 & (sizeof(x3909)-1)))))*(461845907))^(x3914);
    x3876 = ((((x3915<<(13))|((x3915 >> (-13 & (sizeof(x3915)-1)))))*(5))+(-430675100));
    int x3922 = x3876;
    int x3923 = x3922^(2);
    int x3926 = (x3923^((x3923 >> (16 & (sizeof(x3923)-1)))))*(-2048144789);
    int x3929 = (x3926^((x3926 >> (13 & (sizeof(x3926)-1)))))*(-1028477387);
    return (x3929^((x3929 >> (16 & (sizeof(x3929)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x3933, const struct SEntry8_IIIITIIB& x3934) { 
    int x3935 = x3933._1;
    int x3936 = x3934._1;
    int ite18013 = 0;
    if((x3935==(x3936))) {
      
      int x3938 = x3933._2;
      int x3939 = x3934._2;
      int x18014 = (x3938==(x3939));
      ite18013 = x18014;
    } else {
      
      ite18013 = 0;
    };
    int x18005 = ite18013;
    int ite18022 = 0;
    if(x18005) {
      
      int x3942 = x3933._3;
      int x3943 = x3934._3;
      int x18023 = (x3942==(x3943));
      ite18022 = x18023;
    } else {
      
      ite18022 = 0;
    };
    int x18007 = ite18022;
    return (x18007 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3641)  { 
    int x3642 = -889275714;
    int x3643 = x3641._2;
    int x3645 = -862048943*((HASH(x3643)));
    int x3650 = x3642;
    int x3651 = (((x3645<<(15))|((x3645 >> (-15 & (sizeof(x3645)-1)))))*(461845907))^(x3650);
    x3642 = ((((x3651<<(13))|((x3651 >> (-13 & (sizeof(x3651)-1)))))*(5))+(-430675100));
    int x3658 = x3641._3;
    int x3660 = -862048943*((HASH(x3658)));
    int x3665 = x3642;
    int x3666 = (((x3660<<(15))|((x3660 >> (-15 & (sizeof(x3660)-1)))))*(461845907))^(x3665);
    x3642 = ((((x3666<<(13))|((x3666 >> (-13 & (sizeof(x3666)-1)))))*(5))+(-430675100));
    int x3673 = x3642;
    int x3674 = x3673^(2);
    int x3677 = (x3674^((x3674 >> (16 & (sizeof(x3674)-1)))))*(-2048144789);
    int x3680 = (x3677^((x3677 >> (13 & (sizeof(x3677)-1)))))*(-1028477387);
    return (x3680^((x3680 >> (16 & (sizeof(x3680)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3684, const struct SEntry3_III& x3685) { 
    int x3686 = x3684._1;
    int x3687 = x3685._1;
    return ((x3686==(x3687)) ? 0 : ((x3686>(x3687)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3949)  { 
    int x3950 = -889275714;
    int x3951 = x3949._2;
    int x3953 = -862048943*((HASH(x3951)));
    int x3958 = x3950;
    int x3959 = (((x3953<<(15))|((x3953 >> (-15 & (sizeof(x3953)-1)))))*(461845907))^(x3958);
    x3950 = ((((x3959<<(13))|((x3959 >> (-13 & (sizeof(x3959)-1)))))*(5))+(-430675100));
    int x3966 = x3949._3;
    int x3968 = -862048943*((HASH(x3966)));
    int x3973 = x3950;
    int x3974 = (((x3968<<(15))|((x3968 >> (-15 & (sizeof(x3968)-1)))))*(461845907))^(x3973);
    x3950 = ((((x3974<<(13))|((x3974 >> (-13 & (sizeof(x3974)-1)))))*(5))+(-430675100));
    int x3981 = x3949._4;
    int x3983 = -862048943*((HASH(x3981)));
    int x3988 = x3950;
    int x3989 = (((x3983<<(15))|((x3983 >> (-15 & (sizeof(x3983)-1)))))*(461845907))^(x3988);
    x3950 = ((((x3989<<(13))|((x3989 >> (-13 & (sizeof(x3989)-1)))))*(5))+(-430675100));
    int x3996 = x3950;
    int x3997 = x3996^(2);
    int x4000 = (x3997^((x3997 >> (16 & (sizeof(x3997)-1)))))*(-2048144789);
    int x4003 = (x4000^((x4000 >> (13 & (sizeof(x4000)-1)))))*(-1028477387);
    return (x4003^((x4003 >> (16 & (sizeof(x4003)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x4007, const struct SEntry8_IIIITIIB& x4008) { 
    int x4009 = x4007._1;
    int x4010 = x4008._1;
    return ((x4009==(x4010)) ? 0 : ((x4009>(x4010)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3837)  { 
    int x3838 = 0;
    int x3839 = x3837._1;
    int x3841 = x3838;
    x3838 = ((x3841*(1))+((x3839-(1))));
    int x3845 = x3838;
    return x3845; 
  }
  FORCE_INLINE static bool equals(const struct SEntry9_ISSSSSSDD& x3834, const struct SEntry9_ISSSSSSDD& x3835) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3856)  { 
    int x3857 = 0;
    int x3858 = x3856._1;
    int x3860 = x3857;
    x3857 = ((x3860*(100000))+((x3858-(1))));
    int x3864 = x3857;
    return x3864; 
  }
  FORCE_INLINE static bool equals(const struct SEntry5_IISDS& x3853, const struct SEntry5_IISDS& x3854) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4101)  { 
    int x4102 = 0;
    int x4103 = x4101._1;
    int x4105 = x4102;
    x4102 = ((x4105*(10))+((x4103-(1))));
    int x4109 = x4101._2;
    int x4111 = x4102;
    x4102 = ((x4111*(1))+((x4109-(1))));
    int x4115 = x4102;
    return x4115; 
  }
  FORCE_INLINE static bool equals(const struct SEntry11_IISSSSSSDDI& x4098, const struct SEntry11_IISSSSSSDDI& x4099) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4299)  { 
    int x4300 = 0;
    int x4301 = x4299._1;
    int x4303 = x4300;
    x4300 = ((x4303*(3000))+((x4301-(1))));
    int x4307 = x4299._2;
    int x4309 = x4300;
    x4300 = ((x4309*(10))+((x4307-(1))));
    int x4313 = x4299._3;
    int x4315 = x4300;
    x4300 = ((x4315*(1))+((x4313-(1))));
    int x4319 = x4300;
    return x4319; 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4296, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4297) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4405)  { 
    int x4406 = 0;
    int x4407 = x4405._1;
    int x4409 = x4406;
    x4406 = ((x4409*(100000))+((x4407-(1))));
    int x4413 = x4405._2;
    int x4415 = x4406;
    x4406 = ((x4415*(1))+((x4413-(1))));
    int x4419 = x4406;
    return x4419; 
  }
  FORCE_INLINE static bool equals(const struct SEntry17_IIISSSSSSSSSSIIIS& x4402, const struct SEntry17_IIISSSSSSSSSSIIIS& x4403) { 
    return 0; 
  }
};

MultiHashMap<struct SEntry3_III,char ,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> > x3751;
auto& newOrderTbl = x3751;
auto& x751 = x3751.index[0];
auto& x752 = x3751.index[1];


MultiHashMap<struct SEntry8_IIIIITDS,char ,
   HashIndex< struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> > x3831;
auto& historyTbl = x3831;
auto& x758 = x3831.index[0];


MultiHashMap<struct SEntry9_ISSSSSSDD,char ,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> > x3850;
auto& warehouseTbl = x3850;
auto& x763 = x3850.index[0];


MultiHashMap<struct SEntry5_IISDS,char ,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> > x3869;
auto& itemTbl = x3869;
auto& x768 = x3869.index[0];


MultiHashMap<struct SEntry8_IIIITIIB,char ,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> > x4093;
auto& orderTbl = x4093;
auto& x775 = x4093.index[0];
auto& x776 = x4093.index[1];


MultiHashMap<struct SEntry11_IISSSSSSDDI,char ,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> > x4120;
auto& districtTbl = x4120;
auto& x782 = x4120.index[0];


MultiHashMap<struct SEntry10_IIIIIITIDS,char ,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> > x4292;
auto& orderLineTbl = x4292;
auto& x787 = x4292.index[0];
auto& x788 = x4292.index[1];


MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS,char ,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> > x4398;
auto& customerTbl = x4398;
auto& x794 = x4398.index[0];
auto& x795 = x4398.index[1];


MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS,char ,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> > x4424;
auto& stockTbl = x4424;
auto& x800 = x4424.index[0];

struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7603;
struct SEntry8_IIIITIIB x7030;
struct SEntry10_IIIIIITIDS x7039;
struct SEntry17_IIISSSSSSSSSSIIIS x7193;
struct SEntry8_IIIITIIB x7261;
struct SEntry10_IIIIIITIDS x7170;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7394;
struct SEntry3_III x7018;
struct SEntry11_IISSSSSSDDI x7157;
struct SEntry5_IISDS x7582;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7235;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7376;
struct SEntry11_IISSSSSSDDI x7610;
struct SEntry11_IISSSSSSDDI x7366;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7043;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7253;
struct SEntry9_ISSSSSSDD x7607;
struct SEntry9_ISSSSSSDD x7360;
struct SEntry17_IIISSSSSSSSSSIIIS x7634;


void DeliveryTx(int x10, Date x11, int x12, int x13) {
  int x14[10];
  int x15 = 1;
  while(1) {
    
    int x16 = x15;
    if (!((x16<=(10)))) break; 
    
    int x22 = x15;
    x7018._2 = x22;
    x7018._3 = x12;
    struct SEntry3_III* x11545 = x752->get(x7018);
    if((x11545!=(NULL))) {
      int x7024 = x11545->_1;
      int x29 = x15;
      x14[(x29-(1))] = x7024;
      x752->del(x11545);;
      x751->del(x11545);;
      int x33 = x15;
      x7030._1 = x7024;
      x7030._2 = x33;
      x7030._3 = x12;
      struct SEntry8_IIIITIIB* x11559 = x775->get(x7030);
      int x7033 = x11559->_4;
      x11559->_6 = x13;
      double x40 = 0.0;
      int x41 = x15;
      x7039._1 = x7024;
      x7039._2 = x41;
      x7039._3 = x12;
      x788->slice(x7039, ([&](struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* x44 = &sliceVar;
        x44->_7 = x11;
        double x46 = x40;
        double x7088 = x44->_9;
        x40 = (x46+(x7088));
      
      }));;
      int x53 = x15;
      x7043._1 = x7033;
      x7043._2 = x53;
      x7043._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11580 = x794->get(x7043);
      double x56 = x40;
      x11580->_17 += x56;
      x11580->_20 += 1;
    } else {
      
      int x60 = x15;
      x14[(x60-(1))] = 0;
    };
    int x64 = x15;
    x15 = (x64+(1));
  };
}
void StockLevelTx(int x68, Date x69, int x70, int x71, int x72, int x73) {
  x7157._1 = x72;
  x7157._2 = x71;
  struct SEntry11_IISSSSSSDDI* x11650 = x782->get(x7157);
  int x7161 = x11650->_11;
  int x79 = (x7161-(20));
  unordered_set<int> x80;
  while(1) {
    
    int x81 = x79;
    if (!((x81<(x7161)))) break; 
    
    int x83 = x79;
    x7170._1 = x83;
    x7170._2 = x72;
    x7170._3 = x71;
    x788->slice(x7170, ([&](struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* x86 = &sliceVar;
      int x7192 = x86->_5;
      x7193._1 = x7192;
      x7193._2 = x71;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11668 = x800->get(x7193);
      int x7195 = x11668->_3;
      if((x7195<(x73))) {
        x80.insert(x7192);
      };
    
    }));;
    int x96 = x79;
    x79 = (x96+(1));
  };
}
void OrderStatusTx(int x101, Date x102, int x103, int x104, int x105, int x106, int x107, char* x108) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7230 = NULL;
  if((x106>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x7233;
    x7235._2 = x105;
    x7235._3 = x104;
    x7235._6 = x108;
    x795->slice(x7235, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x114 = &sliceVar;
      x7233.push_back(x114);
    
    }));;
    int x118 = x7233.size();
    int x120 = (x118/(2));
    int x121 = x7233.size();
    if(((x121%(2))==(0))) {
      int x124 = x120;
      x120 = (x124-(1));
    };
    sort(x7233.begin(), x7233.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x128, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x129) {
      
      char* x7291 = x128._4;
      char* x7292 = x129._4;
      int x132 = strcmpi(x7291, x7292);
      return (x132<(0)); 
    }));
    int x136 = x120;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7251 = x7233[x136];
    x7230 = x7251;
  } else {
    
    x7253._1 = x107;
    x7253._2 = x105;
    x7253._3 = x104;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11746 = x794->get(x7253);
    x7230 = x11746;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7258 = x7230;
  int x7259 = x7258->_3;
  x7261._2 = x105;
  x7261._3 = x104;
  x7261._4 = x7259;
  struct SEntry8_IIIITIIB* x11756 = x776->get(x7261);
  int x154 = 0;
  int x7266 = x11756->_1;
  x154 = x7266;
}
void PaymentTx(int x157, Date x158, int x159, int x160, int x161, int x162, int x163, int x164, int x165, char* x166, double x167) {
  x7360._1 = x160;
  struct SEntry9_ISSSSSSDD* x11815 = x763->get(x7360);
  x11815->_9 += x167;
  x7366._1 = x161;
  x7366._2 = x160;
  struct SEntry11_IISSSSSSDDI* x11820 = x782->get(x7366);
  x11820->_10 += x167;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7371 = NULL;
  if((x162>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x7374;
    x7376._2 = x164;
    x7376._3 = x163;
    x7376._6 = x166;
    x795->slice(x7376, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x183 = &sliceVar;
      x7374.push_back(x183);
    
    }));;
    int x187 = x7374.size();
    int x189 = (x187/(2));
    int x190 = x7374.size();
    if(((x190%(2))==(0))) {
      int x193 = x189;
      x189 = (x193-(1));
    };
    sort(x7374.begin(), x7374.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x197, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x198) {
      
      char* x7459 = x197._4;
      char* x7460 = x198._4;
      int x201 = strcmpi(x7459, x7460);
      return (x201<(0)); 
    }));
    int x205 = x189;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7392 = x7374[x205];
    x7371 = x7392;
  } else {
    
    x7394._1 = x165;
    x7394._2 = x164;
    x7394._3 = x163;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11859 = x794->get(x7394);
    x7371 = x11859;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7398 = x7371;
  char* x7399 = x7398->_21;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7400 = x7371;
  char* x7401 = x7400->_14;
  char* x16384 = strstr(x7401, "BC");
  int x16385 = x16384!=(NULL);
  if(x16385) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7404 = x7371;
    int x7405 = x7404->_1;
    char* x221 = new char[501];
    snprintf(x221, 500, "%d %d %d %d %d $%f %s | %s", x7405,x164,x163,x161,x160,x167,x158,x7399);
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7408 = x7371;
    x7408->_17 += x167;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7410 = x7371;
    x7410->_21 = x221;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7412 = x7371;
    x7412->_17 += x167;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7414 = x7371;
    ;
    ;
  char* x7416 = x11815->_2;
  char* x7417 = x11820->_3;
  char* x234 = new char[25];
  snprintf(x234, 24, "%.10s    %.10s", x7416,x7417);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7420 = x7371;
  int x7421 = x7420->_1;
  struct SEntry8_IIIIITDS* x15980 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x15980, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x15980->_1 = x7421; x15980->_2 = x164; x15980->_3 = x163; x15980->_4 = x161; x15980->_5 = x160; x15980->_6 = x158; x15980->_7 = x167; x15980->_8 = x234;
  x3831.add(x15980);
}
void NewOrderTx(int x240, Date x241, int x242, int x243, int x244, int x245, int x246, int x247, int* x248, int* x249, int* x250, double* x251, char** x252, int* x253, char** x254, double* x255) {
  int x256 = 0;
  int x257 = 0;
  char* x258[x246];
  int x259 = 1;
  while(1) {
    
    int x260 = x256;
    int ite15394 = 0;
    if((x260<(x246))) {
      
      int x262 = x259;
      int x15395 = x262;
      ite15394 = x15395;
    } else {
      
      ite15394 = 0;
    };
    int x15226 = ite15394;
    if (!(x15226)) break; 
    
    int x264 = x256;
    int x265 = x248[x264];
    x7582._1 = x265;
    struct SEntry5_IISDS* x11980 = x768->get(x7582);
    if((x11980==(NULL))) {
      x259 = 0;
    } else {
      
      int x271 = x256;
      char* x7590 = x11980->_3;
      x252[x271] = x7590;
      int x274 = x256;
      double x7593 = x11980->_4;
      x251[x274] = x7593;
      int x277 = x256;
      char* x7596 = x11980->_5;
      x258[x277] = x7596;
    };
    int x281 = x256;
    x256 = (x281+(1));
  };
  int x285 = x259;
  if(x285) {
    x7603._1 = x245;
    x7603._2 = x244;
    x7603._3 = x243;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12003 = x794->get(x7603);
    x7607._1 = x243;
    struct SEntry9_ISSSSSSDD* x12006 = x763->get(x7607);
    x7610._1 = x244;
    x7610._2 = x243;
    struct SEntry11_IISSSSSSDDI* x12010 = x782->get(x7610);
    int x7613 = x12010->_11;
    x12010->_11 += 1;
    struct SEntry8_IIIITIIB* x16031 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x16031, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x16031->_1 = x7613; x16031->_2 = x244; x16031->_3 = x243; x16031->_4 = x245; x16031->_5 = x241; x16031->_6 = -1; x16031->_7 = x246; x16031->_8 = (x247>(0));
    x4093.add(x16031);
    struct SEntry3_III* x16035 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x16035, 0, 1 * sizeof(struct SEntry3_III));
    x16035->_1 = x7613; x16035->_2 = x244; x16035->_3 = x243;
    x3751.add(x16035);
    double x305 = 0.0;
    x256 = 0;
    while(1) {
      
      int x307 = x256;
      if (!((x307<(x246)))) break; 
      
      int x309 = x256;
      int x310 = x249[x309];
      int x311 = x256;
      int x312 = x248[x311];
      int x313 = x256;
      int x314 = x250[x313];
      x7634._1 = x312;
      x7634._2 = x310;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12033 = x800->get(x7634);
      char* ite15280 = NULL;
      if((x244==(1))) {
        char* x15281 = x12033->_4;
        ite15280 = x15281;
      } else {
        
        int x15283 = x244==(2);
        char* ite15285 = NULL;
        if(x15283) {
          char* x15286 = x12033->_5;
          ite15285 = x15286;
        } else {
          
          int x15288 = x244==(3);
          char* ite15290 = NULL;
          if(x15288) {
            char* x15291 = x12033->_6;
            ite15290 = x15291;
          } else {
            
            int x15293 = x244==(4);
            char* ite15295 = NULL;
            if(x15293) {
              char* x15296 = x12033->_7;
              ite15295 = x15296;
            } else {
              
              int x15298 = x244==(5);
              char* ite15300 = NULL;
              if(x15298) {
                char* x15301 = x12033->_8;
                ite15300 = x15301;
              } else {
                
                int x15303 = x244==(6);
                char* ite15305 = NULL;
                if(x15303) {
                  char* x15306 = x12033->_9;
                  ite15305 = x15306;
                } else {
                  
                  int x15308 = x244==(7);
                  char* ite15310 = NULL;
                  if(x15308) {
                    char* x15311 = x12033->_10;
                    ite15310 = x15311;
                  } else {
                    
                    int x15313 = x244==(8);
                    char* ite15315 = NULL;
                    if(x15313) {
                      char* x15316 = x12033->_11;
                      ite15315 = x15316;
                    } else {
                      
                      int x15318 = x244==(9);
                      char* ite15320 = NULL;
                      if(x15318) {
                        char* x15321 = x12033->_12;
                        ite15320 = x15321;
                      } else {
                        
                        char* x15323 = x12033->_13;
                        ite15320 = x15323;
                      };
                      char* x15319 = ite15320;
                      ite15315 = x15319;
                    };
                    char* x15314 = ite15315;
                    ite15310 = x15314;
                  };
                  char* x15309 = ite15310;
                  ite15305 = x15309;
                };
                char* x15304 = ite15305;
                ite15300 = x15304;
              };
              char* x15299 = ite15300;
              ite15295 = x15299;
            };
            char* x15294 = ite15295;
            ite15290 = x15294;
          };
          char* x15289 = ite15290;
          ite15285 = x15289;
        };
        char* x15284 = ite15285;
        ite15280 = x15284;
      };
      char* x344 = ite15280;
      int x7664 = x12033->_3;
      int x346 = x256;
      x253[x346] = x7664;
      char* x7667 = x12003->_14;
      char* x16621 = strstr(x7667, "original");
      int x16622 = x16621!=(NULL);
      int ite15521 = 0;
      if(x16622) {
        
        char* x7670 = x12033->_17;
        char* x16627 = strstr(x7670, "original");
        int x16628 = x16627!=(NULL);
        int x15522 = x16628;
        ite15521 = x15522;
      } else {
        
        ite15521 = 0;
      };
      int x15348 = ite15521;
      if(x15348) {
        int x353 = x256;
        x254[x353] = "B";
      } else {
        
        int x355 = x256;
        x254[x355] = "G";
      };
      x12033->_3 = (x7664-(x314));
      if((x7664<=(x314))) {
        x12033->_3 += 91;
      };
      int x363 = 0;
      if((x310!=(x243))) {
        x363 = 1;
      };
      double x7687 = x12003->_16;
      double x7688 = x12006->_8;
      double x7689 = x12010->_9;
      int x371 = x256;
      double x372 = x251[x371];
      double x379 = ((x314*(x372))*(((1.0+(x7688))+(x7689))))*((1.0-(x7687)));
      int x380 = x256;
      x255[x380] = x379;
      double x382 = x305;
      x305 = (x382+(x379));
      int x385 = x256;
      struct SEntry10_IIIIIITIDS* x16162 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x16162, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x16162->_1 = x7613; x16162->_2 = x244; x16162->_3 = x243; x16162->_4 = (x385+(1)); x16162->_5 = x312; x16162->_6 = x310; x16162->_7 = NULL; x16162->_8 = x314; x16162->_9 = x379; x16162->_10 = x344;
      x4292.add(x16162);
      int x390 = x256;
      x256 = (x390+(1));
    };
  };
}
/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
}
/* ----------- FUNCTIONS ----------- */
