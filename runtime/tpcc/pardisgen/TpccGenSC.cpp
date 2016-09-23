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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3988)  { 
    int x3989 = -889275714;
    int x3990 = x3988._1;
    int x3992 = -862048943*((HASH(x3990)));
    int x3997 = x3989;
    int x3998 = (((x3992<<(15))|((x3992 >> (-15 & (sizeof(x3992)-1)))))*(461845907))^(x3997);
    x3989 = ((((x3998<<(13))|((x3998 >> (-13 & (sizeof(x3998)-1)))))*(5))+(-430675100));
    int x4005 = x3988._2;
    int x4007 = -862048943*((HASH(x4005)));
    int x4012 = x3989;
    int x4013 = (((x4007<<(15))|((x4007 >> (-15 & (sizeof(x4007)-1)))))*(461845907))^(x4012);
    x3989 = ((((x4013<<(13))|((x4013 >> (-13 & (sizeof(x4013)-1)))))*(5))+(-430675100));
    int x4020 = x3988._3;
    int x4022 = -862048943*((HASH(x4020)));
    int x4027 = x3989;
    int x4028 = (((x4022<<(15))|((x4022 >> (-15 & (sizeof(x4022)-1)))))*(461845907))^(x4027);
    x3989 = ((((x4028<<(13))|((x4028 >> (-13 & (sizeof(x4028)-1)))))*(5))+(-430675100));
    int x4035 = x3988._4;
    int x4037 = -862048943*((HASH(x4035)));
    int x4042 = x3989;
    int x4043 = (((x4037<<(15))|((x4037 >> (-15 & (sizeof(x4037)-1)))))*(461845907))^(x4042);
    x3989 = ((((x4043<<(13))|((x4043 >> (-13 & (sizeof(x4043)-1)))))*(5))+(-430675100));
    int x4050 = x3989;
    int x4051 = x4050^(2);
    int x4054 = (x4051^((x4051 >> (16 & (sizeof(x4051)-1)))))*(-2048144789);
    int x4057 = (x4054^((x4054 >> (13 & (sizeof(x4054)-1)))))*(-1028477387);
    return (x4057^((x4057 >> (16 & (sizeof(x4057)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4061, const struct SEntry10_IIIIIITIDS& x4062) { 
    int x4063 = x4061._1;
    int x4064 = x4062._1;
    int ite16735 = 0;
    if((x4063==(x4064))) {
      
      int x4066 = x4061._2;
      int x4067 = x4062._2;
      int x16736 = (x4066==(x4067));
      ite16735 = x16736;
    } else {
      
      ite16735 = 0;
    };
    int x16725 = ite16735;
    int ite16744 = 0;
    if(x16725) {
      
      int x4070 = x4061._3;
      int x4071 = x4062._3;
      int x16745 = (x4070==(x4071));
      ite16744 = x16745;
    } else {
      
      ite16744 = 0;
    };
    int x16727 = ite16744;
    int ite16753 = 0;
    if(x16727) {
      
      int x4074 = x4061._4;
      int x4075 = x4062._4;
      int x16754 = (x4074==(x4075));
      ite16753 = x16754;
    } else {
      
      ite16753 = 0;
    };
    int x16729 = ite16753;
    return (x16729 ? 0 : 1); 
  }
};
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3882)  { 
    int x3883 = -889275714;
    int x3884 = x3882._2;
    int x3886 = -862048943*((HASH(x3884)));
    int x3891 = x3883;
    int x3892 = (((x3886<<(15))|((x3886 >> (-15 & (sizeof(x3886)-1)))))*(461845907))^(x3891);
    x3883 = ((((x3892<<(13))|((x3892 >> (-13 & (sizeof(x3892)-1)))))*(5))+(-430675100));
    int x3899 = x3882._3;
    int x3901 = -862048943*((HASH(x3899)));
    int x3906 = x3883;
    int x3907 = (((x3901<<(15))|((x3901 >> (-15 & (sizeof(x3901)-1)))))*(461845907))^(x3906);
    x3883 = ((((x3907<<(13))|((x3907 >> (-13 & (sizeof(x3907)-1)))))*(5))+(-430675100));
    int x3914 = x3882._4;
    int x3916 = -862048943*((HASH(x3914)));
    int x3921 = x3883;
    int x3922 = (((x3916<<(15))|((x3916 >> (-15 & (sizeof(x3916)-1)))))*(461845907))^(x3921);
    x3883 = ((((x3922<<(13))|((x3922 >> (-13 & (sizeof(x3922)-1)))))*(5))+(-430675100));
    int x3929 = x3883;
    int x3930 = x3929^(2);
    int x3933 = (x3930^((x3930 >> (16 & (sizeof(x3930)-1)))))*(-2048144789);
    int x3936 = (x3933^((x3933 >> (13 & (sizeof(x3933)-1)))))*(-1028477387);
    return (x3936^((x3936 >> (16 & (sizeof(x3936)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x3940, const struct SEntry8_IIIITIIB& x3941) { 
    int x3942 = x3940._2;
    int x3943 = x3941._2;
    int ite16861 = 0;
    if((x3942==(x3943))) {
      
      int x3945 = x3940._3;
      int x3946 = x3941._3;
      int x16862 = (x3945==(x3946));
      ite16861 = x16862;
    } else {
      
      ite16861 = 0;
    };
    int x16853 = ite16861;
    int ite16870 = 0;
    if(x16853) {
      
      int x3949 = x3940._4;
      int x3950 = x3941._4;
      int x16871 = (x3949==(x3950));
      ite16870 = x16871;
    } else {
      
      ite16870 = 0;
    };
    int x16855 = ite16870;
    return (x16855 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3432)  { 
    int x3433 = -889275714;
    int x3434 = x3432._1;
    int x3436 = -862048943*((HASH(x3434)));
    int x3441 = x3433;
    int x3442 = (((x3436<<(15))|((x3436 >> (-15 & (sizeof(x3436)-1)))))*(461845907))^(x3441);
    x3433 = ((((x3442<<(13))|((x3442 >> (-13 & (sizeof(x3442)-1)))))*(5))+(-430675100));
    int x3449 = x3432._2;
    int x3451 = -862048943*((HASH(x3449)));
    int x3456 = x3433;
    int x3457 = (((x3451<<(15))|((x3451 >> (-15 & (sizeof(x3451)-1)))))*(461845907))^(x3456);
    x3433 = ((((x3457<<(13))|((x3457 >> (-13 & (sizeof(x3457)-1)))))*(5))+(-430675100));
    int x3464 = x3432._3;
    int x3466 = -862048943*((HASH(x3464)));
    int x3471 = x3433;
    int x3472 = (((x3466<<(15))|((x3466 >> (-15 & (sizeof(x3466)-1)))))*(461845907))^(x3471);
    x3433 = ((((x3472<<(13))|((x3472 >> (-13 & (sizeof(x3472)-1)))))*(5))+(-430675100));
    int x3479 = x3433;
    int x3480 = x3479^(2);
    int x3483 = (x3480^((x3480 >> (16 & (sizeof(x3480)-1)))))*(-2048144789);
    int x3486 = (x3483^((x3483 >> (13 & (sizeof(x3483)-1)))))*(-1028477387);
    return (x3486^((x3486 >> (16 & (sizeof(x3486)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3490, const struct SEntry3_III& x3491) { 
    int x3492 = x3490._1;
    int x3493 = x3491._1;
    int ite16969 = 0;
    if((x3492==(x3493))) {
      
      int x3495 = x3490._2;
      int x3496 = x3491._2;
      int x16970 = (x3495==(x3496));
      ite16969 = x16970;
    } else {
      
      ite16969 = 0;
    };
    int x16961 = ite16969;
    int ite16978 = 0;
    if(x16961) {
      
      int x3499 = x3490._3;
      int x3500 = x3491._3;
      int x16979 = (x3499==(x3500));
      ite16978 = x16979;
    } else {
      
      ite16978 = 0;
    };
    int x16963 = ite16978;
    return (x16963 ? 0 : 1); 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4081)  { 
    int x4082 = -889275714;
    int x4083 = x4081._1;
    int x4085 = -862048943*((HASH(x4083)));
    int x4090 = x4082;
    int x4091 = (((x4085<<(15))|((x4085 >> (-15 & (sizeof(x4085)-1)))))*(461845907))^(x4090);
    x4082 = ((((x4091<<(13))|((x4091 >> (-13 & (sizeof(x4091)-1)))))*(5))+(-430675100));
    int x4098 = x4081._2;
    int x4100 = -862048943*((HASH(x4098)));
    int x4105 = x4082;
    int x4106 = (((x4100<<(15))|((x4100 >> (-15 & (sizeof(x4100)-1)))))*(461845907))^(x4105);
    x4082 = ((((x4106<<(13))|((x4106 >> (-13 & (sizeof(x4106)-1)))))*(5))+(-430675100));
    int x4113 = x4081._3;
    int x4115 = -862048943*((HASH(x4113)));
    int x4120 = x4082;
    int x4121 = (((x4115<<(15))|((x4115 >> (-15 & (sizeof(x4115)-1)))))*(461845907))^(x4120);
    x4082 = ((((x4121<<(13))|((x4121 >> (-13 & (sizeof(x4121)-1)))))*(5))+(-430675100));
    int x4128 = x4082;
    int x4129 = x4128^(2);
    int x4132 = (x4129^((x4129 >> (16 & (sizeof(x4129)-1)))))*(-2048144789);
    int x4135 = (x4132^((x4132 >> (13 & (sizeof(x4132)-1)))))*(-1028477387);
    return (x4135^((x4135 >> (16 & (sizeof(x4135)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4139, const struct SEntry10_IIIIIITIDS& x4140) { 
    int x4141 = x4139._1;
    int x4142 = x4140._1;
    int ite17077 = 0;
    if((x4141==(x4142))) {
      
      int x4144 = x4139._2;
      int x4145 = x4140._2;
      int x17078 = (x4144==(x4145));
      ite17077 = x17078;
    } else {
      
      ite17077 = 0;
    };
    int x17069 = ite17077;
    int ite17086 = 0;
    if(x17069) {
      
      int x4148 = x4139._3;
      int x4149 = x4140._3;
      int x17087 = (x4148==(x4149));
      ite17086 = x17087;
    } else {
      
      ite17086 = 0;
    };
    int x17071 = ite17086;
    return (x17071 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3559)  { 
    int x3560 = -889275714;
    int x3561 = x3559._2;
    int x3563 = -862048943*((HASH(x3561)));
    int x3568 = x3560;
    int x3569 = (((x3563<<(15))|((x3563 >> (-15 & (sizeof(x3563)-1)))))*(461845907))^(x3568);
    x3560 = ((((x3569<<(13))|((x3569 >> (-13 & (sizeof(x3569)-1)))))*(5))+(-430675100));
    int x3576 = x3559._3;
    int x3578 = -862048943*((HASH(x3576)));
    int x3583 = x3560;
    int x3584 = (((x3578<<(15))|((x3578 >> (-15 & (sizeof(x3578)-1)))))*(461845907))^(x3583);
    x3560 = ((((x3584<<(13))|((x3584 >> (-13 & (sizeof(x3584)-1)))))*(5))+(-430675100));
    int x3591 = x3560;
    int x3592 = x3591^(2);
    int x3595 = (x3592^((x3592 >> (16 & (sizeof(x3592)-1)))))*(-2048144789);
    int x3598 = (x3595^((x3595 >> (13 & (sizeof(x3595)-1)))))*(-1028477387);
    return (x3598^((x3598 >> (16 & (sizeof(x3598)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3602, const struct SEntry3_III& x3603) { 
    int x3604 = x3602._2;
    int x3605 = x3603._2;
    int ite17168 = 0;
    if((x3604==(x3605))) {
      
      int x3607 = x3602._3;
      int x3608 = x3603._3;
      int x17169 = (x3607==(x3608));
      ite17168 = x17169;
    } else {
      
      ite17168 = 0;
    };
    int x17162 = ite17168;
    return (x17162 ? 0 : 1); 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3621)  { 
    int x3622 = -889275714;
    int x3623 = x3622;
    int x3624 = x3623^(2);
    int x3627 = (x3624^((x3624 >> (16 & (sizeof(x3624)-1)))))*(-2048144789);
    int x3630 = (x3627^((x3627 >> (13 & (sizeof(x3627)-1)))))*(-1028477387);
    return (x3630^((x3630 >> (16 & (sizeof(x3630)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIIITDS& x3634, const struct SEntry8_IIIIITDS& x3635) { 
    int x3636 = x3634._1;
    int x3637 = x3635._1;
    int ite17225 = 0;
    if((x3636==(-1))) {
      ite17225 = 1;
    } else {
      
      
      int x17227 = (x3637==(-1));
      ite17225 = x17227;
    };
    int x17205 = ite17225;
    int ite17232 = 0;
    if(x17205) {
      ite17232 = 1;
    } else {
      
      
      int x17234 = (x3636==(x3637));
      ite17232 = x17234;
    };
    int x17207 = ite17232;
    int ite17239 = 0;
    if(x17207) {
      
      int x3643 = x3634._2;
      int x3644 = x3635._2;
      int ite17341 = 0;
      if((x3643==(-1))) {
        ite17341 = 1;
      } else {
        
        
        int x17343 = (x3644==(-1));
        ite17341 = x17343;
      };
      int x17245 = ite17341;
      int ite17348 = 0;
      if(x17245) {
        ite17348 = 1;
      } else {
        
        
        int x17350 = (x3643==(x3644));
        ite17348 = x17350;
      };
      int x17247 = ite17348;
      int x17240 = x17247;
      ite17239 = x17240;
    } else {
      
      ite17239 = 0;
    };
    int x17209 = ite17239;
    int ite17252 = 0;
    if(x17209) {
      
      int x3651 = x3634._3;
      int x3652 = x3635._3;
      int ite17364 = 0;
      if((x3651==(-1))) {
        ite17364 = 1;
      } else {
        
        
        int x17366 = (x3652==(-1));
        ite17364 = x17366;
      };
      int x17258 = ite17364;
      int ite17371 = 0;
      if(x17258) {
        ite17371 = 1;
      } else {
        
        
        int x17373 = (x3651==(x3652));
        ite17371 = x17373;
      };
      int x17260 = ite17371;
      int x17253 = x17260;
      ite17252 = x17253;
    } else {
      
      ite17252 = 0;
    };
    int x17211 = ite17252;
    int ite17265 = 0;
    if(x17211) {
      
      int x3659 = x3634._4;
      int x3660 = x3635._4;
      int ite17387 = 0;
      if((x3659==(-1))) {
        ite17387 = 1;
      } else {
        
        
        int x17389 = (x3660==(-1));
        ite17387 = x17389;
      };
      int x17271 = ite17387;
      int ite17394 = 0;
      if(x17271) {
        ite17394 = 1;
      } else {
        
        
        int x17396 = (x3659==(x3660));
        ite17394 = x17396;
      };
      int x17273 = ite17394;
      int x17266 = x17273;
      ite17265 = x17266;
    } else {
      
      ite17265 = 0;
    };
    int x17213 = ite17265;
    int ite17278 = 0;
    if(x17213) {
      
      int x3667 = x3634._5;
      int x3668 = x3635._5;
      int ite17410 = 0;
      if((x3667==(-1))) {
        ite17410 = 1;
      } else {
        
        
        int x17412 = (x3668==(-1));
        ite17410 = x17412;
      };
      int x17284 = ite17410;
      int ite17417 = 0;
      if(x17284) {
        ite17417 = 1;
      } else {
        
        
        int x17419 = (x3667==(x3668));
        ite17417 = x17419;
      };
      int x17286 = ite17417;
      int x17279 = x17286;
      ite17278 = x17279;
    } else {
      
      ite17278 = 0;
    };
    int x17215 = ite17278;
    int ite17291 = 0;
    if(x17215) {
      
      Date x3675 = x3634._6;
      Date x3676 = x3635._6;
      int ite17433 = 0;
      if((x3675==(NULL))) {
        ite17433 = 1;
      } else {
        
        
        int x17435 = (x3676==(NULL));
        ite17433 = x17435;
      };
      int x17297 = ite17433;
      int ite17440 = 0;
      if(x17297) {
        ite17440 = 1;
      } else {
        
        
        int x17442 = (x3675==(x3676));
        ite17440 = x17442;
      };
      int x17299 = ite17440;
      int x17292 = x17299;
      ite17291 = x17292;
    } else {
      
      ite17291 = 0;
    };
    int x17217 = ite17291;
    int ite17304 = 0;
    if(x17217) {
      
      double x3683 = x3634._7;
      double x3684 = x3635._7;
      int ite17456 = 0;
      if((x3683==(-1.0))) {
        ite17456 = 1;
      } else {
        
        
        int x17458 = (x3684==(-1.0));
        ite17456 = x17458;
      };
      int x17310 = ite17456;
      int ite17463 = 0;
      if(x17310) {
        ite17463 = 1;
      } else {
        
        
        int x17465 = (x3683==(x3684));
        ite17463 = x17465;
      };
      int x17312 = ite17463;
      int x17305 = x17312;
      ite17304 = x17305;
    } else {
      
      ite17304 = 0;
    };
    int x17219 = ite17304;
    return (x17219 ? 0 : 1); 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4187)  { 
    int x4188 = -889275714;
    int x4189 = x4187._2;
    int x4191 = -862048943*((HASH(x4189)));
    int x4196 = x4188;
    int x4197 = (((x4191<<(15))|((x4191 >> (-15 & (sizeof(x4191)-1)))))*(461845907))^(x4196);
    x4188 = ((((x4197<<(13))|((x4197 >> (-13 & (sizeof(x4197)-1)))))*(5))+(-430675100));
    int x4204 = x4187._3;
    int x4206 = -862048943*((HASH(x4204)));
    int x4211 = x4188;
    int x4212 = (((x4206<<(15))|((x4206 >> (-15 & (sizeof(x4206)-1)))))*(461845907))^(x4211);
    x4188 = ((((x4212<<(13))|((x4212 >> (-13 & (sizeof(x4212)-1)))))*(5))+(-430675100));
    char* x4219 = x4187._6;
    int x4221 = -862048943*((HASH(x4219)));
    int x4226 = x4188;
    int x4227 = (((x4221<<(15))|((x4221 >> (-15 & (sizeof(x4221)-1)))))*(461845907))^(x4226);
    x4188 = ((((x4227<<(13))|((x4227 >> (-13 & (sizeof(x4227)-1)))))*(5))+(-430675100));
    int x4234 = x4188;
    int x4235 = x4234^(2);
    int x4238 = (x4235^((x4235 >> (16 & (sizeof(x4235)-1)))))*(-2048144789);
    int x4241 = (x4238^((x4238 >> (13 & (sizeof(x4238)-1)))))*(-1028477387);
    return (x4241^((x4241 >> (16 & (sizeof(x4241)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4245, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4246) { 
    int x4247 = x4245._2;
    int x4248 = x4246._2;
    int ite17697 = 0;
    if((x4247==(x4248))) {
      
      int x4250 = x4245._3;
      int x4251 = x4246._3;
      int x17698 = (x4250==(x4251));
      ite17697 = x17698;
    } else {
      
      ite17697 = 0;
    };
    int x17689 = ite17697;
    int ite17706 = 0;
    if(x17689) {
      
      char* x4254 = x4245._6;
      char* x4255 = x4246._6;
      int x17707 = (x4254==(x4255));
      ite17706 = x17707;
    } else {
      
      ite17706 = 0;
    };
    int x17691 = ite17706;
    return (x17691 ? 0 : 1); 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3740)  { 
    int x3741 = -889275714;
    int x3742 = x3740._1;
    int x3744 = -862048943*((HASH(x3742)));
    int x3749 = x3741;
    int x3750 = (((x3744<<(15))|((x3744 >> (-15 & (sizeof(x3744)-1)))))*(461845907))^(x3749);
    x3741 = ((((x3750<<(13))|((x3750 >> (-13 & (sizeof(x3750)-1)))))*(5))+(-430675100));
    int x3757 = x3740._2;
    int x3759 = -862048943*((HASH(x3757)));
    int x3764 = x3741;
    int x3765 = (((x3759<<(15))|((x3759 >> (-15 & (sizeof(x3759)-1)))))*(461845907))^(x3764);
    x3741 = ((((x3765<<(13))|((x3765 >> (-13 & (sizeof(x3765)-1)))))*(5))+(-430675100));
    int x3772 = x3740._3;
    int x3774 = -862048943*((HASH(x3772)));
    int x3779 = x3741;
    int x3780 = (((x3774<<(15))|((x3774 >> (-15 & (sizeof(x3774)-1)))))*(461845907))^(x3779);
    x3741 = ((((x3780<<(13))|((x3780 >> (-13 & (sizeof(x3780)-1)))))*(5))+(-430675100));
    int x3787 = x3741;
    int x3788 = x3787^(2);
    int x3791 = (x3788^((x3788 >> (16 & (sizeof(x3788)-1)))))*(-2048144789);
    int x3794 = (x3791^((x3791 >> (13 & (sizeof(x3791)-1)))))*(-1028477387);
    return (x3794^((x3794 >> (16 & (sizeof(x3794)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x3798, const struct SEntry8_IIIITIIB& x3799) { 
    int x3800 = x3798._1;
    int x3801 = x3799._1;
    int ite17805 = 0;
    if((x3800==(x3801))) {
      
      int x3803 = x3798._2;
      int x3804 = x3799._2;
      int x17806 = (x3803==(x3804));
      ite17805 = x17806;
    } else {
      
      ite17805 = 0;
    };
    int x17797 = ite17805;
    int ite17814 = 0;
    if(x17797) {
      
      int x3807 = x3798._3;
      int x3808 = x3799._3;
      int x17815 = (x3807==(x3808));
      ite17814 = x17815;
    } else {
      
      ite17814 = 0;
    };
    int x17799 = ite17814;
    return (x17799 ? 0 : 1); 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3506)  { 
    int x3507 = -889275714;
    int x3508 = x3506._2;
    int x3510 = -862048943*((HASH(x3508)));
    int x3515 = x3507;
    int x3516 = (((x3510<<(15))|((x3510 >> (-15 & (sizeof(x3510)-1)))))*(461845907))^(x3515);
    x3507 = ((((x3516<<(13))|((x3516 >> (-13 & (sizeof(x3516)-1)))))*(5))+(-430675100));
    int x3523 = x3506._3;
    int x3525 = -862048943*((HASH(x3523)));
    int x3530 = x3507;
    int x3531 = (((x3525<<(15))|((x3525 >> (-15 & (sizeof(x3525)-1)))))*(461845907))^(x3530);
    x3507 = ((((x3531<<(13))|((x3531 >> (-13 & (sizeof(x3531)-1)))))*(5))+(-430675100));
    int x3538 = x3507;
    int x3539 = x3538^(2);
    int x3542 = (x3539^((x3539 >> (16 & (sizeof(x3539)-1)))))*(-2048144789);
    int x3545 = (x3542^((x3542 >> (13 & (sizeof(x3542)-1)))))*(-1028477387);
    return (x3545^((x3545 >> (16 & (sizeof(x3545)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3549, const struct SEntry3_III& x3550) { 
    int x3551 = x3549._1;
    int x3552 = x3550._1;
    return ((x3551==(x3552)) ? 0 : ((x3551>(x3552)) ? 1 : -1)); 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3814)  { 
    int x3815 = -889275714;
    int x3816 = x3814._2;
    int x3818 = -862048943*((HASH(x3816)));
    int x3823 = x3815;
    int x3824 = (((x3818<<(15))|((x3818 >> (-15 & (sizeof(x3818)-1)))))*(461845907))^(x3823);
    x3815 = ((((x3824<<(13))|((x3824 >> (-13 & (sizeof(x3824)-1)))))*(5))+(-430675100));
    int x3831 = x3814._3;
    int x3833 = -862048943*((HASH(x3831)));
    int x3838 = x3815;
    int x3839 = (((x3833<<(15))|((x3833 >> (-15 & (sizeof(x3833)-1)))))*(461845907))^(x3838);
    x3815 = ((((x3839<<(13))|((x3839 >> (-13 & (sizeof(x3839)-1)))))*(5))+(-430675100));
    int x3846 = x3814._4;
    int x3848 = -862048943*((HASH(x3846)));
    int x3853 = x3815;
    int x3854 = (((x3848<<(15))|((x3848 >> (-15 & (sizeof(x3848)-1)))))*(461845907))^(x3853);
    x3815 = ((((x3854<<(13))|((x3854 >> (-13 & (sizeof(x3854)-1)))))*(5))+(-430675100));
    int x3861 = x3815;
    int x3862 = x3861^(2);
    int x3865 = (x3862^((x3862 >> (16 & (sizeof(x3862)-1)))))*(-2048144789);
    int x3868 = (x3865^((x3865 >> (13 & (sizeof(x3865)-1)))))*(-1028477387);
    return (x3868^((x3868 >> (16 & (sizeof(x3868)-1))))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x3872, const struct SEntry8_IIIITIIB& x3873) { 
    int x3874 = x3872._1;
    int x3875 = x3873._1;
    return ((x3874==(x3875)) ? 0 : ((x3874>(x3875)) ? 1 : -1)); 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3702)  { 
    int x3703 = 0;
    int x3704 = x3702._1;
    int x3706 = x3703;
    x3703 = ((x3706*(1))+((x3704-(1))));
    int x3710 = x3703;
    return x3710; 
  }
  FORCE_INLINE static bool equals(const struct SEntry9_ISSSSSSDD& x3699, const struct SEntry9_ISSSSSSDD& x3700) { 
    return 0; 
  }
};
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3721)  { 
    int x3722 = 0;
    int x3723 = x3721._1;
    int x3725 = x3722;
    x3722 = ((x3725*(100000))+((x3723-(1))));
    int x3729 = x3722;
    return x3729; 
  }
  FORCE_INLINE static bool equals(const struct SEntry5_IISDS& x3718, const struct SEntry5_IISDS& x3719) { 
    return 0; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3966)  { 
    int x3967 = 0;
    int x3968 = x3966._1;
    int x3970 = x3967;
    x3967 = ((x3970*(10))+((x3968-(1))));
    int x3974 = x3966._2;
    int x3976 = x3967;
    x3967 = ((x3976*(1))+((x3974-(1))));
    int x3980 = x3967;
    return x3980; 
  }
  FORCE_INLINE static bool equals(const struct SEntry11_IISSSSSSDDI& x3963, const struct SEntry11_IISSSSSSDDI& x3964) { 
    return 0; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4164)  { 
    int x4165 = 0;
    int x4166 = x4164._1;
    int x4168 = x4165;
    x4165 = ((x4168*(3000))+((x4166-(1))));
    int x4172 = x4164._2;
    int x4174 = x4165;
    x4165 = ((x4174*(10))+((x4172-(1))));
    int x4178 = x4164._3;
    int x4180 = x4165;
    x4165 = ((x4180*(1))+((x4178-(1))));
    int x4184 = x4165;
    return x4184; 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4161, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4162) { 
    return 0; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4270)  { 
    int x4271 = 0;
    int x4272 = x4270._1;
    int x4274 = x4271;
    x4271 = ((x4274*(100000))+((x4272-(1))));
    int x4278 = x4270._2;
    int x4280 = x4271;
    x4271 = ((x4280*(1))+((x4278-(1))));
    int x4284 = x4271;
    return x4284; 
  }
  FORCE_INLINE static bool equals(const struct SEntry17_IIISSSSSSSSSSIIIS& x4267, const struct SEntry17_IIISSSSSSSSSSIIIS& x4268) { 
    return 0; 
  }
};

MultiHashMap<struct SEntry3_III,char ,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> > x3616;
auto& newOrderTbl = x3616;
auto& x721 = x3616.index[0];
auto& x722 = x3616.index[1];


MultiHashMap<struct SEntry8_IIIIITDS,char ,
   HashIndex< struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> > x3696;
auto& historyTbl = x3696;
auto& x728 = x3696.index[0];


MultiHashMap<struct SEntry9_ISSSSSSDD,char ,
   ArrayIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1f1t2, 1> > x3715;
auto& warehouseTbl = x3715;
auto& x733 = x3715.index[0];


MultiHashMap<struct SEntry5_IISDS,char ,
   ArrayIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1f1t100001, 100000> > x3734;
auto& itemTbl = x3734;
auto& x738 = x3734.index[0];


MultiHashMap<struct SEntry8_IIIITIIB,char ,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> > x3958;
auto& orderTbl = x3958;
auto& x745 = x3958.index[0];
auto& x746 = x3958.index[1];


MultiHashMap<struct SEntry11_IISSSSSSDDI,char ,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 10> > x3985;
auto& districtTbl = x3985;
auto& x752 = x3985.index[0];


MultiHashMap<struct SEntry10_IIIIIITIDS,char ,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> > x4157;
auto& orderLineTbl = x4157;
auto& x757 = x4157.index[0];
auto& x758 = x4157.index[1];


MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS,char ,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 30000>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> > x4263;
auto& customerTbl = x4263;
auto& x764 = x4263.index[0];
auto& x765 = x4263.index[1];


MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS,char ,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 100000> > x4289;
auto& stockTbl = x4289;
auto& x770 = x4289.index[0];

struct SEntry3_III x6883;
struct SEntry10_IIIIIITIDS x7035;
struct SEntry11_IISSSSSSDDI x7219;
struct SEntry9_ISSSSSSDD x7427;
struct SEntry5_IISDS x7402;
struct SEntry8_IIIITIIB x7122;
struct SEntry17_IIISSSSSSSSSSIIIS x7454;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7116;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7245;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7228;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7099;
struct SEntry10_IIIIIITIDS x6904;
struct SEntry17_IIISSSSSSSSSSIIIS x7058;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x6908;
struct SEntry11_IISSSSSSDDI x7022;
struct SEntry9_ISSSSSSDD x7213;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7423;
struct SEntry11_IISSSSSSDDI x7430;
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
    struct SEntry3_III* x11320 = x722->get(x6883);
    if((x11320!=(NULL))) {
      int x6889 = x11320->_1;
      int x29 = x15;
      x14[(x29-(1))] = x6889;
      x722->del(x11320);;
      x721->del(x11320);;
      int x33 = x15;
      x6895._1 = x6889;
      x6895._2 = x33;
      x6895._3 = x12;
      struct SEntry8_IIIITIIB* x11334 = x745->get(x6895);
      int x6898 = x11334->_4;
      x11334->_6 = x13;
      double x40 = 0.0;
      int x41 = x15;
      x6904._1 = x6889;
      x6904._2 = x41;
      x6904._3 = x12;
      x758->slice(x6904, ([&](struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* x44 = &sliceVar;
        x44->_7 = x11;
        double x46 = x40;
        double x6953 = x44->_9;
        x40 = (x46+(x6953));
      
      }));;
      int x53 = x15;
      x6908._1 = x6898;
      x6908._2 = x53;
      x6908._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11355 = x764->get(x6908);
      double x56 = x40;
      x11355->_17 += x56;
      x11355->_20 += 1;
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
  struct SEntry11_IISSSSSSDDI* x11425 = x752->get(x7022);
  int x7026 = x11425->_11;
  int x79 = (x7026-(20));
  unordered_set<int> x80;
  while(1) {
    
    int x81 = x79;
    if (!((x81<(x7026)))) break; 
    
    int x83 = x79;
    x7035._1 = x83;
    x7035._2 = x72;
    x7035._3 = x71;
    x758->slice(x7035, ([&](struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* x86 = &sliceVar;
      int x7057 = x86->_5;
      x7058._1 = x7057;
      x7058._2 = x71;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11443 = x770->get(x7058);
      int x7060 = x11443->_3;
      if((x7060<(x73))) {
        x80.insert(x7057);
      };
    
    }));;
    int x96 = x79;
    x79 = (x96+(1));
  };
}
void OrderStatusTx(int x101, Date x102, int x103, int x104, int x105, int x106, int x107, char* x108) {
  GenericEntry ite14808 = NULL;
  if((x106>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14809;
    x7099._2 = x105;
    x7099._3 = x104;
    x7099._6 = x108;
    x765->slice(x7099, x14813);;
    int x14817 = x14809.size();
    int x14818 = x14817/(2);
    int x14819 = x14818;
    int x14820 = x14809.size();
    int x14821 = x14820%(2);
    int x14822 = x14821==(0);
    if(x14822) {
      int x123 = x14819;
      x14819 = (x123-(1));
    };
    sort(x14809.begin(), x14809.end(), x14827);
    int x14835 = x14819;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14836 = x14809[x14835];
    ite14808 = x14836;
  } else {
    
    x7116._1 = x107;
    x7116._2 = x105;
    x7116._3 = x104;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14841 = x764->get(x7116);
    ite14808 = x14841;
  };
  GenericEntry x140 = ite14808;
  int x141 = x140get(3);
  x7122._2 = x105;
  x7122._3 = x104;
  x7122._4 = x141;
  struct SEntry8_IIIITIIB* x11527 = x746->get(x7122);
  int x150 = 0;
  int x7127 = x11527->_1;
  x150 = x7127;
}
void PaymentTx(int x153, Date x154, int x155, int x156, int x157, int x158, int x159, int x160, int x161, char* x162, double x163) {
  x7213._1 = x156;
  struct SEntry9_ISSSSSSDD* x11582 = x733->get(x7213);
  x11582->_9 += x163;
  x7219._1 = x157;
  x7219._2 = x156;
  struct SEntry11_IISSSSSSDDI* x11587 = x752->get(x7219);
  x11587->_10 += x163;
  GenericEntry ite14907 = NULL;
  if((x158>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14908;
    x7228._2 = x160;
    x7228._3 = x159;
    x7228._6 = x162;
    x765->slice(x7228, x14912);;
    int x14916 = x14908.size();
    int x14917 = x14916/(2);
    int x14918 = x14917;
    int x14919 = x14908.size();
    int x14920 = x14919%(2);
    int x14921 = x14920==(0);
    if(x14921) {
      int x188 = x14918;
      x14918 = (x188-(1));
    };
    sort(x14908.begin(), x14908.end(), x14926);
    int x14934 = x14918;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14935 = x14908[x14934];
    ite14907 = x14935;
  } else {
    
    x7245._1 = x161;
    x7245._2 = x160;
    x7245._3 = x159;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14940 = x764->get(x7245);
    ite14907 = x14940;
  };
  GenericEntry x205 = ite14907;
  char* x206 = x205get(21);
  char* x207 = x205get(14);
  char* x16187 = strstr(x207, "BC");
  int x16188 = x16187!=(NULL);
  if(x16188) {
    int x209 = x205get(1);
    char* x211 = new char[501];
    snprintf(x211, 500, "%d %d %d %d %d $%f %s | %s", x209,x160,x159,x157,x156,x163,x154,x206);
    x205+=(17, x163);
    x205update(21, x211);
  } else {
    
    x205+=(17, x163);
  };
  GenericEntry x11635 = x764->get(x205);
  x764updateCopyDependent(x205, x11635);
  x765updateCopyDependent(x205, x11635);
  char* x7259 = x11582->_2;
  char* x7260 = x11587->_3;
  char* x220 = new char[25];
  snprintf(x220, 24, "%.10s    %.10s", x7259,x7260);
  int x221 = x205get(1);
  struct SEntry8_IIIIITDS* x15784 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x15784, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x15784->_1 = x221; x15784->_2 = x160; x15784->_3 = x159; x15784->_4 = x157; x15784->_5 = x156; x15784->_6 = x154; x15784->_7 = x163; x15784->_8 = x220;
  x3696.add(x15784);
}
void NewOrderTx(int x225, Date x226, int x227, int x228, int x229, int x230, int x231, int x232, int* x233, int* x234, int* x235, double* x236, char** x237, int* x238, char** x239, double* x240) {
  int x241 = 0;
  int x242 = 0;
  char* x243[x231];
  int x244 = 1;
  while(1) {
    
    int x245 = x241;
    int ite15204 = 0;
    if((x245<(x231))) {
      
      int x247 = x244;
      int x15205 = x247;
      ite15204 = x15205;
    } else {
      
      ite15204 = 0;
    };
    int x15036 = ite15204;
    if (!(x15036)) break; 
    
    int x249 = x241;
    int x250 = x233[x249];
    x7402._1 = x250;
    struct SEntry5_IISDS* x11727 = x738->get(x7402);
    if((x11727==(NULL))) {
      x244 = 0;
    } else {
      
      int x256 = x241;
      char* x7410 = x11727->_3;
      x237[x256] = x7410;
      int x259 = x241;
      double x7413 = x11727->_4;
      x236[x259] = x7413;
      int x262 = x241;
      char* x7416 = x11727->_5;
      x243[x262] = x7416;
    };
    int x266 = x241;
    x241 = (x266+(1));
  };
  int x270 = x244;
  if(x270) {
    x7423._1 = x230;
    x7423._2 = x229;
    x7423._3 = x228;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11750 = x764->get(x7423);
    x7427._1 = x228;
    struct SEntry9_ISSSSSSDD* x11753 = x733->get(x7427);
    x7430._1 = x229;
    x7430._2 = x228;
    struct SEntry11_IISSSSSSDDI* x11757 = x752->get(x7430);
    int x7433 = x11757->_11;
    x11757->_11 += 1;
    struct SEntry8_IIIITIIB* x15835 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x15835, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x15835->_1 = x7433; x15835->_2 = x229; x15835->_3 = x228; x15835->_4 = x230; x15835->_5 = x226; x15835->_6 = -1; x15835->_7 = x231; x15835->_8 = (x232>(0));
    x3958.add(x15835);
    struct SEntry3_III* x15839 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x15839, 0, 1 * sizeof(struct SEntry3_III));
    x15839->_1 = x7433; x15839->_2 = x229; x15839->_3 = x228;
    x3616.add(x15839);
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
      x7454._1 = x297;
      x7454._2 = x295;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11780 = x770->get(x7454);
      char* ite15090 = NULL;
      if((x229==(1))) {
        char* x15091 = x11780->_4;
        ite15090 = x15091;
      } else {
        
        int x15093 = x229==(2);
        char* ite15095 = NULL;
        if(x15093) {
          char* x15096 = x11780->_5;
          ite15095 = x15096;
        } else {
          
          int x15098 = x229==(3);
          char* ite15100 = NULL;
          if(x15098) {
            char* x15101 = x11780->_6;
            ite15100 = x15101;
          } else {
            
            int x15103 = x229==(4);
            char* ite15105 = NULL;
            if(x15103) {
              char* x15106 = x11780->_7;
              ite15105 = x15106;
            } else {
              
              int x15108 = x229==(5);
              char* ite15110 = NULL;
              if(x15108) {
                char* x15111 = x11780->_8;
                ite15110 = x15111;
              } else {
                
                int x15113 = x229==(6);
                char* ite15115 = NULL;
                if(x15113) {
                  char* x15116 = x11780->_9;
                  ite15115 = x15116;
                } else {
                  
                  int x15118 = x229==(7);
                  char* ite15120 = NULL;
                  if(x15118) {
                    char* x15121 = x11780->_10;
                    ite15120 = x15121;
                  } else {
                    
                    int x15123 = x229==(8);
                    char* ite15125 = NULL;
                    if(x15123) {
                      char* x15126 = x11780->_11;
                      ite15125 = x15126;
                    } else {
                      
                      int x15128 = x229==(9);
                      char* ite15130 = NULL;
                      if(x15128) {
                        char* x15131 = x11780->_12;
                        ite15130 = x15131;
                      } else {
                        
                        char* x15133 = x11780->_13;
                        ite15130 = x15133;
                      };
                      char* x15129 = ite15130;
                      ite15125 = x15129;
                    };
                    char* x15124 = ite15125;
                    ite15120 = x15124;
                  };
                  char* x15119 = ite15120;
                  ite15115 = x15119;
                };
                char* x15114 = ite15115;
                ite15110 = x15114;
              };
              char* x15109 = ite15110;
              ite15105 = x15109;
            };
            char* x15104 = ite15105;
            ite15100 = x15104;
          };
          char* x15099 = ite15100;
          ite15095 = x15099;
        };
        char* x15094 = ite15095;
        ite15090 = x15094;
      };
      char* x329 = ite15090;
      int x7484 = x11780->_3;
      int x331 = x241;
      x238[x331] = x7484;
      char* x7487 = x11750->_14;
      char* x16413 = strstr(x7487, "original");
      int x16414 = x16413!=(NULL);
      int ite15331 = 0;
      if(x16414) {
        
        char* x7490 = x11780->_17;
        char* x16419 = strstr(x7490, "original");
        int x16420 = x16419!=(NULL);
        int x15332 = x16420;
        ite15331 = x15332;
      } else {
        
        ite15331 = 0;
      };
      int x15158 = ite15331;
      if(x15158) {
        int x338 = x241;
        x239[x338] = "B";
      } else {
        
        int x340 = x241;
        x239[x340] = "G";
      };
      x11780->_3 = (x7484-(x299));
      if((x7484<=(x299))) {
        x11780->_3 += 91;
      };
      int x348 = 0;
      if((x295!=(x228))) {
        x348 = 1;
      };
      double x7507 = x11750->_16;
      double x7508 = x11753->_8;
      double x7509 = x11757->_9;
      int x356 = x241;
      double x357 = x236[x356];
      double x364 = ((x299*(x357))*(((1.0+(x7508))+(x7509))))*((1.0-(x7507)));
      int x365 = x241;
      x240[x365] = x364;
      double x367 = x290;
      x290 = (x367+(x364));
      int x370 = x241;
      struct SEntry10_IIIIIITIDS* x15966 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x15966, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x15966->_1 = x7433; x15966->_2 = x229; x15966->_3 = x228; x15966->_4 = (x370+(1)); x15966->_5 = x297; x15966->_6 = x295; x15966->_7 = NULL; x15966->_8 = x299; x15966->_9 = x364; x15966->_10 = x329;
      x4157.add(x15966);
      int x375 = x241;
      x241 = (x375+(1));
    };
  };
}
#include "TPCC.h"

/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
}
/* ----------- FUNCTIONS ----------- */
void x14813(struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x113) {
  x14809.push_back(x113);

}

int x14827(struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x127, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x128) {
  char* x7151 = x127->_4;
  char* x7152 = x128->_4;
  int x131 = strcmpi(x7151, x7152);
  return (x131<(0)); 
}

void x14912(struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x178) {
  x14908.push_back(x178);

}

int x14926(struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x192, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x193) {
  char* x7300 = x192->_4;
  char* x7301 = x193->_4;
  int x196 = strcmpi(x7300, x7301);
  return (x196<(0)); 
}

