#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
using namespace std;

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
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4294) = { 
    int x4295 = -889275714;
    int x4296 = x4294._1;
    int x4298 = -862048943*((HASH(x4296)));
    int x4303 = x4295;
    int x4304 = (((x4298<<(15))|((x4298>>>(-15))))*(461845907))^(x4303);
    x4295 = ((((x4304<<(13))|((x4304>>>(-13))))*(5))+(-430675100));
    int x4311 = x4294._2;
    int x4313 = -862048943*((HASH(x4311)));
    int x4318 = x4295;
    int x4319 = (((x4313<<(15))|((x4313>>>(-15))))*(461845907))^(x4318);
    x4295 = ((((x4319<<(13))|((x4319>>>(-13))))*(5))+(-430675100));
    int x4326 = x4294._3;
    int x4328 = -862048943*((HASH(x4326)));
    int x4333 = x4295;
    int x4334 = (((x4328<<(15))|((x4328>>>(-15))))*(461845907))^(x4333);
    x4295 = ((((x4334<<(13))|((x4334>>>(-13))))*(5))+(-430675100));
    int x4341 = x4294._4;
    int x4343 = -862048943*((HASH(x4341)));
    int x4348 = x4295;
    int x4349 = (((x4343<<(15))|((x4343>>>(-15))))*(461845907))^(x4348);
    x4295 = ((((x4349<<(13))|((x4349>>>(-13))))*(5))+(-430675100));
    int x4356 = x4295;
    int x4357 = x4356^(2);
    int x4360 = (x4357^((x4357>>>(16))))*(-2048144789);
    int x4363 = (x4360^((x4360>>>(13))))*(-1028477387);
    return (x4363^((x4363>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4367, const struct SEntry10_IIIIIITIDS& x4368) { 
    int x4369 = x4367._1;
    int x4370 = x4368._1;
    return (((((x4369==(x4370))&&((x4372==(x4373))))&&((x4376==(x4377))))&&((x4380==(x4381)))) ? 0 : 1); 
  }
}
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4188) = { 
    int x4189 = -889275714;
    int x4190 = x4188._2;
    int x4192 = -862048943*((HASH(x4190)));
    int x4197 = x4189;
    int x4198 = (((x4192<<(15))|((x4192>>>(-15))))*(461845907))^(x4197);
    x4189 = ((((x4198<<(13))|((x4198>>>(-13))))*(5))+(-430675100));
    int x4205 = x4188._3;
    int x4207 = -862048943*((HASH(x4205)));
    int x4212 = x4189;
    int x4213 = (((x4207<<(15))|((x4207>>>(-15))))*(461845907))^(x4212);
    x4189 = ((((x4213<<(13))|((x4213>>>(-13))))*(5))+(-430675100));
    int x4220 = x4188._4;
    int x4222 = -862048943*((HASH(x4220)));
    int x4227 = x4189;
    int x4228 = (((x4222<<(15))|((x4222>>>(-15))))*(461845907))^(x4227);
    x4189 = ((((x4228<<(13))|((x4228>>>(-13))))*(5))+(-430675100));
    int x4235 = x4189;
    int x4236 = x4235^(2);
    int x4239 = (x4236^((x4236>>>(16))))*(-2048144789);
    int x4242 = (x4239^((x4239>>>(13))))*(-1028477387);
    return (x4242^((x4242>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x4246, const struct SEntry8_IIIITIIB& x4247) { 
    int x4248 = x4246._2;
    int x4249 = x4247._2;
    return ((((x4248==(x4249))&&((x4251==(x4252))))&&((x4255==(x4256)))) ? 0 : 1); 
  }
}
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3738) = { 
    int x3739 = -889275714;
    int x3740 = x3738._1;
    int x3742 = -862048943*((HASH(x3740)));
    int x3747 = x3739;
    int x3748 = (((x3742<<(15))|((x3742>>>(-15))))*(461845907))^(x3747);
    x3739 = ((((x3748<<(13))|((x3748>>>(-13))))*(5))+(-430675100));
    int x3755 = x3738._2;
    int x3757 = -862048943*((HASH(x3755)));
    int x3762 = x3739;
    int x3763 = (((x3757<<(15))|((x3757>>>(-15))))*(461845907))^(x3762);
    x3739 = ((((x3763<<(13))|((x3763>>>(-13))))*(5))+(-430675100));
    int x3770 = x3738._3;
    int x3772 = -862048943*((HASH(x3770)));
    int x3777 = x3739;
    int x3778 = (((x3772<<(15))|((x3772>>>(-15))))*(461845907))^(x3777);
    x3739 = ((((x3778<<(13))|((x3778>>>(-13))))*(5))+(-430675100));
    int x3785 = x3739;
    int x3786 = x3785^(2);
    int x3789 = (x3786^((x3786>>>(16))))*(-2048144789);
    int x3792 = (x3789^((x3789>>>(13))))*(-1028477387);
    return (x3792^((x3792>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3796, const struct SEntry3_III& x3797) { 
    int x3798 = x3796._1;
    int x3799 = x3797._1;
    return ((((x3798==(x3799))&&((x3801==(x3802))))&&((x3805==(x3806)))) ? 0 : 1); 
  }
}
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x4387) = { 
    int x4388 = -889275714;
    int x4389 = x4387._1;
    int x4391 = -862048943*((HASH(x4389)));
    int x4396 = x4388;
    int x4397 = (((x4391<<(15))|((x4391>>>(-15))))*(461845907))^(x4396);
    x4388 = ((((x4397<<(13))|((x4397>>>(-13))))*(5))+(-430675100));
    int x4404 = x4387._2;
    int x4406 = -862048943*((HASH(x4404)));
    int x4411 = x4388;
    int x4412 = (((x4406<<(15))|((x4406>>>(-15))))*(461845907))^(x4411);
    x4388 = ((((x4412<<(13))|((x4412>>>(-13))))*(5))+(-430675100));
    int x4419 = x4387._3;
    int x4421 = -862048943*((HASH(x4419)));
    int x4426 = x4388;
    int x4427 = (((x4421<<(15))|((x4421>>>(-15))))*(461845907))^(x4426);
    x4388 = ((((x4427<<(13))|((x4427>>>(-13))))*(5))+(-430675100));
    int x4434 = x4388;
    int x4435 = x4434^(2);
    int x4438 = (x4435^((x4435>>>(16))))*(-2048144789);
    int x4441 = (x4438^((x4438>>>(13))))*(-1028477387);
    return (x4441^((x4441>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry10_IIIIIITIDS& x4445, const struct SEntry10_IIIIIITIDS& x4446) { 
    int x4447 = x4445._1;
    int x4448 = x4446._1;
    return ((((x4447==(x4448))&&((x4450==(x4451))))&&((x4454==(x4455)))) ? 0 : 1); 
  }
}
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3865) = { 
    int x3866 = -889275714;
    int x3867 = x3865._2;
    int x3869 = -862048943*((HASH(x3867)));
    int x3874 = x3866;
    int x3875 = (((x3869<<(15))|((x3869>>>(-15))))*(461845907))^(x3874);
    x3866 = ((((x3875<<(13))|((x3875>>>(-13))))*(5))+(-430675100));
    int x3882 = x3865._3;
    int x3884 = -862048943*((HASH(x3882)));
    int x3889 = x3866;
    int x3890 = (((x3884<<(15))|((x3884>>>(-15))))*(461845907))^(x3889);
    x3866 = ((((x3890<<(13))|((x3890>>>(-13))))*(5))+(-430675100));
    int x3897 = x3866;
    int x3898 = x3897^(2);
    int x3901 = (x3898^((x3898>>>(16))))*(-2048144789);
    int x3904 = (x3901^((x3901>>>(13))))*(-1028477387);
    return (x3904^((x3904>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3908, const struct SEntry3_III& x3909) { 
    int x3910 = x3908._2;
    int x3911 = x3909._2;
    return (((x3910==(x3911))&&((x3913==(x3914)))) ? 0 : 1); 
  }
}
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3927) = { 
    int x3928 = -889275714;
    int x3929 = x3928;
    int x3930 = x3929^(2);
    int x3933 = (x3930^((x3930>>>(16))))*(-2048144789);
    int x3936 = (x3933^((x3933>>>(13))))*(-1028477387);
    return (x3936^((x3936>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIIITDS& x3940, const struct SEntry8_IIIIITDS& x3941) { 
    int x3942 = x3940._1;
    int x3943 = x3941._1;
    return ((((((((((x3942==(-1))||((x3943==(-1))))||((x3942==(x3943))))&&((((x3949==(-1))||((x3950==(-1))))||((x3949==(x3950))))))&&((((x3957==(-1))||((x3958==(-1))))||((x3957==(x3958))))))&&((((x3965==(-1))||((x3966==(-1))))||((x3965==(x3966))))))&&((((x3973==(-1))||((x3974==(-1))))||((x3973==(x3974))))))&&((((x3981==(NULL))||((x3982==(NULL))))||((x3981==(x3982))))))&&((((x3989==(-1.0))||((x3990==(-1.0))))||((x3989==(x3990)))))) ? 0 : 1); 
  }
}
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4493) = { 
    int x4494 = -889275714;
    int x4495 = x4493._2;
    int x4497 = -862048943*((HASH(x4495)));
    int x4502 = x4494;
    int x4503 = (((x4497<<(15))|((x4497>>>(-15))))*(461845907))^(x4502);
    x4494 = ((((x4503<<(13))|((x4503>>>(-13))))*(5))+(-430675100));
    int x4510 = x4493._3;
    int x4512 = -862048943*((HASH(x4510)));
    int x4517 = x4494;
    int x4518 = (((x4512<<(15))|((x4512>>>(-15))))*(461845907))^(x4517);
    x4494 = ((((x4518<<(13))|((x4518>>>(-13))))*(5))+(-430675100));
    char* x4525 = x4493._6;
    int x4527 = -862048943*((HASH(x4525)));
    int x4532 = x4494;
    int x4533 = (((x4527<<(15))|((x4527>>>(-15))))*(461845907))^(x4532);
    x4494 = ((((x4533<<(13))|((x4533>>>(-13))))*(5))+(-430675100));
    int x4540 = x4494;
    int x4541 = x4540^(2);
    int x4544 = (x4541^((x4541>>>(16))))*(-2048144789);
    int x4547 = (x4544^((x4544>>>(13))))*(-1028477387);
    return (x4547^((x4547>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4551, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4552) { 
    int x4553 = x4551._2;
    int x4554 = x4552._2;
    return ((((x4553==(x4554))&&((x4556==(x4557))))&&((x4560==(x4561)))) ? 0 : 1); 
  }
}
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4046) = { 
    int x4047 = -889275714;
    int x4048 = x4046._1;
    int x4050 = -862048943*((HASH(x4048)));
    int x4055 = x4047;
    int x4056 = (((x4050<<(15))|((x4050>>>(-15))))*(461845907))^(x4055);
    x4047 = ((((x4056<<(13))|((x4056>>>(-13))))*(5))+(-430675100));
    int x4063 = x4046._2;
    int x4065 = -862048943*((HASH(x4063)));
    int x4070 = x4047;
    int x4071 = (((x4065<<(15))|((x4065>>>(-15))))*(461845907))^(x4070);
    x4047 = ((((x4071<<(13))|((x4071>>>(-13))))*(5))+(-430675100));
    int x4078 = x4046._3;
    int x4080 = -862048943*((HASH(x4078)));
    int x4085 = x4047;
    int x4086 = (((x4080<<(15))|((x4080>>>(-15))))*(461845907))^(x4085);
    x4047 = ((((x4086<<(13))|((x4086>>>(-13))))*(5))+(-430675100));
    int x4093 = x4047;
    int x4094 = x4093^(2);
    int x4097 = (x4094^((x4094>>>(16))))*(-2048144789);
    int x4100 = (x4097^((x4097>>>(13))))*(-1028477387);
    return (x4100^((x4100>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x4104, const struct SEntry8_IIIITIIB& x4105) { 
    int x4106 = x4104._1;
    int x4107 = x4105._1;
    return ((((x4106==(x4107))&&((x4109==(x4110))))&&((x4113==(x4114)))) ? 0 : 1); 
  }
}
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3812) = { 
    int x3813 = -889275714;
    int x3814 = x3812._2;
    int x3816 = -862048943*((HASH(x3814)));
    int x3821 = x3813;
    int x3822 = (((x3816<<(15))|((x3816>>>(-15))))*(461845907))^(x3821);
    x3813 = ((((x3822<<(13))|((x3822>>>(-13))))*(5))+(-430675100));
    int x3829 = x3812._3;
    int x3831 = -862048943*((HASH(x3829)));
    int x3836 = x3813;
    int x3837 = (((x3831<<(15))|((x3831>>>(-15))))*(461845907))^(x3836);
    x3813 = ((((x3837<<(13))|((x3837>>>(-13))))*(5))+(-430675100));
    int x3844 = x3813;
    int x3845 = x3844^(2);
    int x3848 = (x3845^((x3845>>>(16))))*(-2048144789);
    int x3851 = (x3848^((x3848>>>(13))))*(-1028477387);
    return (x3851^((x3851>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry3_III& x3855, const struct SEntry3_III& x3856) { 
    int x3857 = x783(x3855);
    int x3858 = x783(x3856);
    int x3861 = if((x3857>(x3858))) {
    };
    return ((x3857==(x3858)) ? 0 : x3861); 
  }
}
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x4120) = { 
    int x4121 = -889275714;
    int x4122 = x4120._2;
    int x4124 = -862048943*((HASH(x4122)));
    int x4129 = x4121;
    int x4130 = (((x4124<<(15))|((x4124>>>(-15))))*(461845907))^(x4129);
    x4121 = ((((x4130<<(13))|((x4130>>>(-13))))*(5))+(-430675100));
    int x4137 = x4120._3;
    int x4139 = -862048943*((HASH(x4137)));
    int x4144 = x4121;
    int x4145 = (((x4139<<(15))|((x4139>>>(-15))))*(461845907))^(x4144);
    x4121 = ((((x4145<<(13))|((x4145>>>(-13))))*(5))+(-430675100));
    int x4152 = x4120._4;
    int x4154 = -862048943*((HASH(x4152)));
    int x4159 = x4121;
    int x4160 = (((x4154<<(15))|((x4154>>>(-15))))*(461845907))^(x4159);
    x4121 = ((((x4160<<(13))|((x4160>>>(-13))))*(5))+(-430675100));
    int x4167 = x4121;
    int x4168 = x4167^(2);
    int x4171 = (x4168^((x4168>>>(16))))*(-2048144789);
    int x4174 = (x4171^((x4171>>>(13))))*(-1028477387);
    return (x4174^((x4174>>>(16)))); 
  }
  FORCE_INLINE static bool equals(const struct SEntry8_IIIITIIB& x4178, const struct SEntry8_IIIITIIB& x4179) { 
    int x4180 = x807(x4178);
    int x4181 = x807(x4179);
    int x4184 = if((x4180>(x4181))) {
    };
    return ((x4180==(x4181)) ? 0 : x4184); 
  }
}
 struct SEntry9_ISSSSSSDD_Idx1f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x4008) = { 
    int x4009 = 0;
    int x4010 = x4008._1;
    int x4012 = x4009;
    x4009 = ((x4012*(1))+((x4010-(1))));
    int x4016 = x4009;
    return x4016; 
  }
  FORCE_INLINE static bool equals(const struct SEntry9_ISSSSSSDD& x4005, const struct SEntry9_ISSSSSSDD& x4006) { 
    return 0; 
  }
}
 struct SEntry5_IISDS_Idx1f1t100001 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x4027) = { 
    int x4028 = 0;
    int x4029 = x4027._1;
    int x4031 = x4028;
    x4028 = ((x4031*(100000))+((x4029-(1))));
    int x4035 = x4028;
    return x4035; 
  }
  FORCE_INLINE static bool equals(const struct SEntry5_IISDS& x4024, const struct SEntry5_IISDS& x4025) { 
    return 0; 
  }
}
 struct SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x4272) = { 
    int x4273 = 0;
    int x4274 = x4272._1;
    int x4276 = x4273;
    x4273 = ((x4276*(10))+((x4274-(1))));
    int x4280 = x4272._2;
    int x4282 = x4273;
    x4273 = ((x4282*(1))+((x4280-(1))));
    int x4286 = x4273;
    return x4286; 
  }
  FORCE_INLINE static bool equals(const struct SEntry11_IISSSSSSDDI& x4269, const struct SEntry11_IISSSSSSDDI& x4270) { 
    return 0; 
  }
}
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4470) = { 
    int x4471 = 0;
    int x4472 = x4470._1;
    int x4474 = x4471;
    x4471 = ((x4474*(3000))+((x4472-(1))));
    int x4478 = x4470._2;
    int x4480 = x4471;
    x4471 = ((x4480*(10))+((x4478-(1))));
    int x4484 = x4470._3;
    int x4486 = x4471;
    x4471 = ((x4486*(1))+((x4484-(1))));
    int x4490 = x4471;
    return x4490; 
  }
  FORCE_INLINE static bool equals(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4467, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x4468) { 
    return 0; 
  }
}
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x4576) = { 
    int x4577 = 0;
    int x4578 = x4576._1;
    int x4580 = x4577;
    x4577 = ((x4580*(100000))+((x4578-(1))));
    int x4584 = x4576._2;
    int x4586 = x4577;
    x4577 = ((x4586*(1))+((x4584-(1))));
    int x4590 = x4577;
    return x4590; 
  }
  FORCE_INLINE static bool equals(const struct SEntry17_IIISSSSSSSSSSIIIS& x4573, const struct SEntry17_IIISSSSSSSSSSIIIS& x4574) { 
    return 0; 
  }
}
MultiHashMap<struct SEntry3_III,void,
   HashIndex<struct SEntry3_III, void, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, void, SEntry3_III_Idx23_Ordering, 0>,
   NoIndex<struct SEntry3_III, void, SEntry3_III_Idx23, 0> > x3922;
auto newOrderTbl& = x3922;

MultiHashMap<struct SEntry8_IIIIITDS,void,
   ListIndex<struct SEntry8_IIIIITDS, void, SEntry8_IIIIITDS_Idx, 0> > x4002;
auto historyTbl& = x4002;

MultiHashMap<struct SEntry9_ISSSSSSDD,void,
   ArrayIndex<struct SEntry9_ISSSSSSDD, void, SEntry9_ISSSSSSDD_Idx1f1t2, 1> > x4021;
auto warehouseTbl& = x4021;

MultiHashMap<struct SEntry5_IISDS,void,
   ArrayIndex<struct SEntry5_IISDS, void, SEntry5_IISDS_Idx1f1t100001, 1> > x4040;
auto itemTbl& = x4040;

MultiHashMap<struct SEntry8_IIIITIIB,void,
   HashIndex<struct SEntry8_IIIITIIB, void, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, void, SEntry8_IIIITIIB_Idx234_Ordering, 0>,
   NoIndex<struct SEntry8_IIIITIIB, void, SEntry8_IIIITIIB_Idx234, 0> > x4264;
auto orderTbl& = x4264;

MultiHashMap<struct SEntry11_IISSSSSSDDI,void,
   ArrayIndex<struct SEntry11_IISSSSSSDDI, void, SEntry11_IISSSSSSDDI_Idx1f1t11_2f1t2, 1> > x4291;
auto districtTbl& = x4291;

MultiHashMap<struct SEntry10_IIIIIITIDS,void,
   HashIndex<struct SEntry10_IIIIIITIDS, void, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, void, SEntry10_IIIIIITIDS_Idx123, 0> > x4463;
auto orderLineTbl& = x4463;

MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS,void,
   ArrayIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, void, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx1f1t3001_2f1t11_3f1t2, 1>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, void, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> > x4569;
auto customerTbl& = x4569;

MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS,void,
   ArrayIndex<struct SEntry17_IIISSSSSSSSSSIIIS, void, SEntry17_IIISSSSSSSSSSIIIS_Idx1f1t100001_2f1t2, 1> > x4595;
auto stockTbl& = x4595;

void DeliveryTx(int x10, Date x11, int x12, int x13) {
  int x14[10];
  int x15 = 1;
  while(1) {
    
    int x16 = x15;
    if (!((x16<=(10)))) break; 
    
    int x22 = x15;
    x7189._2 = x22;
    x7189._3 = x12;
    struct SEntry3_III* x11830 = x790.get(x7189);
    if((x11830!=(NULL))) {
      int x7195 = x11830->_1;
      int x29 = x15;
      x14[(x29-(1))] = x7195;
      x790.del(x11830);;
      x789.del(x11830);;
      int x33 = x15;
      x7201._1 = x7195;
      x7201._2 = x33;
      x7201._3 = x12;
      struct SEntry8_IIIITIIB* x11844 = x813.get(x7201);
      int x7204 = x11844->_4;
      x11844->_6 = x13;
      x814.update(x11844);
      x813.update(x11844);
      double x40 = 0.0;
      int x41 = x15;
      x7210._1 = x7195;
      x7210._2 = x41;
      x7210._3 = x12;
      x826.slice(x7210, ([&](const struct SEntry10_IIIIIITIDS &  sliceVar) {
        struct SEntry10_IIIIIITIDS* x44 = &sliceVar;
        x44->_7 = x11;
        double x46 = x40;
        double x7259 = x44->_9;
        x40 = (x46+(x7259));
        x825.update(x44);
        x826.update(x44);
      
      }));;
      int x53 = x15;
      x7214._1 = x7204;
      x7214._2 = x53;
      x7214._3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11869 = x832.get(x7214);
      double x56 = x40;
      x11869->_17 += x56;
      x11869->_20 += 1;
      x833.update(x11869);
      x832.update(x11869);
    } else {
      
      int x60 = x15;
      x14[(x60-(1))] = 0;
    };
    int x64 = x15;
    x15 = (x64+(1));
  };
}
void StockLevelTx(int x68, Date x69, int x70, int x71, int x72, int x73) {
  x7328._1 = x72;
  x7328._2 = x71;
  struct SEntry11_IISSSSSSDDI* x11947 = x820.get(x7328);
  int x7332 = x11947->_11;
  int x79 = (x7332-(20));
  unordered_set<int> x80;
  while(1) {
    
    int x81 = x79;
    if (!((x81<(x7332)))) break; 
    
    int x83 = x79;
    x7341._1 = x83;
    x7341._2 = x72;
    x7341._3 = x71;
    x826.slice(x7341, ([&](const struct SEntry10_IIIIIITIDS &  sliceVar) {
      struct SEntry10_IIIIIITIDS* x86 = &sliceVar;
      int x7363 = x86->_5;
      x7364._1 = x7363;
      x7364._2 = x71;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11965 = x838.get(x7364);
      int x7366 = x11965->_3;
      if((x7366<(x73))) {
        x80.insert(x7363);
      };
    
    }));;
    int x96 = x79;
    x79 = (x96+(1));
  };
}
void OrderStatusTx(int x101, Date x102, int x103, int x104, int x105, int x106, int x107, char* x108) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7401 = NULL;
  if((x106>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x7404;
    x7406._2 = x105;
    x7406._3 = x104;
    x7406._6 = x108;
    x833.slice(x7406, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS &  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x114 = &sliceVar;
      x7404.push_back(x114);
    
    }));;
    int x118 = x7404.size();
    int x120 = (x118/(2));
    int x121 = x7404.size();
    if(((x121%(2))==(0))) {
      int x124 = x120;
      x120 = (x124-(1));
    };
    sort(x7404.begin(), x7404.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x128, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x129) {
      
      char* x7462 = x128._4;
      char* x7463 = x129._4;
      int x132 = strcmpi(x7462, x7463);
      return (x132<(0)); 
    }));
    int x136 = x120;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7422 = x7404[x136];
    x7401 = x7422;
  } else {
    
    x7424._1 = x107;
    x7424._2 = x105;
    x7424._3 = x104;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12043 = x832.get(x7424);
    x7401 = x12043;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7429 = x7401;
  int x7430 = x7429->_3;
  x7432._2 = x105;
  x7432._3 = x104;
  x7432._4 = x7430;
  struct SEntry8_IIIITIIB* x12053 = x814.get(x7432);
  int x154 = 0;
  int x7437 = x12053->_1;
  x154 = x7437;
}
void PaymentTx(int x157, Date x158, int x159, int x160, int x161, int x162, int x163, int x164, int x165, char* x166, double x167) {
  x7531._1 = x160;
  struct SEntry9_ISSSSSSDD* x12112 = x801.get(x7531);
  x12112->_9 += x167;
  x801.update(x12112);
  x7537._1 = x161;
  x7537._2 = x160;
  struct SEntry11_IISSSSSSDDI* x12118 = x820.get(x7537);
  x12118->_10 += x167;
  x820.update(x12118);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7542 = NULL;
  if((x162>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x7545;
    x7547._2 = x164;
    x7547._3 = x163;
    x7547._6 = x166;
    x833.slice(x7547, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS &  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x183 = &sliceVar;
      x7545.push_back(x183);
    
    }));;
    int x187 = x7545.size();
    int x189 = (x187/(2));
    int x190 = x7545.size();
    if(((x190%(2))==(0))) {
      int x193 = x189;
      x189 = (x193-(1));
    };
    sort(x7545.begin(), x7545.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x197, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x198) {
      
      char* x7649 = x197._4;
      char* x7650 = x198._4;
      int x201 = strcmpi(x7649, x7650);
      return (x201<(0)); 
    }));
    int x205 = x189;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7563 = x7545[x205];
    x7542 = x7563;
  } else {
    
    x7565._1 = x165;
    x7565._2 = x164;
    x7565._3 = x163;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12158 = x832.get(x7565);
    x7542 = x12158;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7569 = x7542;
  char* x7570 = x7569->_21;
  char* x215 = x7570;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7572 = x7542;
  char* x7573 = x7572->_14;
  char* x16073 = strstr(x7573, "BC");
  int x16074 = x16073!=(NULL);
  if(x16074) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7576 = x7542;
    int x7577 = x7576->_1;
    char* x221 = x215;
    /* val x223 = "%d %d %d %d %d $%f %s | %s".format(x7577,x164,x163,x161,x160,x167,x158,x221) */
    x215 = x223;
    char* x225 = x215;
    int x16083 = strlen(x225);
    if((x16083>(500))) {
      char* x228 = x215;
      char* x229 = x228substring(0, 500);
      x215 = x229;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7589 = x7542;
    x7589->_17 += x167;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7591 = x7542;
    char* x235 = x215;
    x7591->_21 = x235;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7594 = x7542;
    x7594->_17 += x167;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7596 = x7542;
  x833.update(x7596);
  x832.update(x7596);
  char* x7598 = x12112->_2;
  char* x7599 = x12118->_3;
  int x16101 = strlen(x7598);
  char* x247 = if((x16101>(10))) {
    char* x246 = x7598substring(0, 10);
  };
  char* x248 = x247+("    ");
  int x16106 = strlen(x7599);
  char* x252 = if((x16106>(10))) {
    char* x251 = x7599substring(0, 10);
  };
  char* x253 = x248+(x252);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7610 = x7542;
  int x7611 = x7610->_1;
  struct SEntry8_IIIIITDS* x15697 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x15697, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x15697->_1 = x7611; x15697->_2 = x164; x15697->_3 = x163; x15697->_4 = x161; x15697->_5 = x160; x15697->_6 = x158; x15697->_7 = x167; x15697->_8 = x253;
  x4002.add(x15697);
}
void NewOrderTx(int x259, Date x260, int x261, int x262, int x263, int x264, int x265, int x266, int x267, int x268, int x269, double x270, char* x271, int x272, char* x273, double x274) {
  int x275 = 0;
  int x276 = 0;
  char* x277[x265];
  int x278 = 1;
  while(1) {
    
    int x279 = x275;
    if (!(((x279<(x265))&&(x281)))) break; 
    
    int x283 = x275;
    int x284 = x267[x283];
    x7810._1 = x284;
    struct SEntry5_IISDS* x12319 = x806.get(x7810);
    if((x12319==(NULL))) {
      x278 = 0;
    } else {
      
      int x290 = x275;
      char* x7818 = x12319->_3;
      x271[x290] = x7818;
      int x293 = x275;
      double x7821 = x12319->_4;
      x270[x293] = x7821;
      int x296 = x275;
      char* x7824 = x12319->_5;
      x277[x296] = x7824;
    };
    int x300 = x275;
    x275 = (x300+(1));
  };
  int x304 = x278;
  if(x304) {
    x7831._1 = x264;
    x7831._2 = x263;
    x7831._3 = x262;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12342 = x832.get(x7831);
    x7835._1 = x262;
    struct SEntry9_ISSSSSSDD* x12345 = x801.get(x7835);
    x7838._1 = x263;
    x7838._2 = x262;
    struct SEntry11_IISSSSSSDDI* x12349 = x820.get(x7838);
    int x7841 = x12349->_11;
    x12349->_11 += 1;
    x820.update(x12349);
    struct SEntry8_IIIITIIB* x15744 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x15744, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x15744->_1 = x7841; x15744->_2 = x263; x15744->_3 = x262; x15744->_4 = x264; x15744->_5 = x260; x15744->_6 = -1; x15744->_7 = x265; x15744->_8 = (x266>(0));
    x4264.add(x15744);
    struct SEntry3_III* x15748 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x15748, 0, 1 * sizeof(struct SEntry3_III));
    x15748->_1 = x7841; x15748->_2 = x263; x15748->_3 = x262;
    x3922.add(x15748);
    double x324 = 0.0;
    x275 = 0;
    while(1) {
      
      int x326 = x275;
      if (!((x326<(x265)))) break; 
      
      int x328 = x275;
      int x329 = x268[x328];
      int x330 = x275;
      int x331 = x267[x330];
      int x332 = x275;
      int x333 = x269[x332];
      x7862._1 = x331;
      x7862._2 = x329;
      struct SEntry17_IIISSSSSSSSSSIIIS* x12373 = x838.get(x7862);
      char* x363 = if((x263==(1))) {
        char* x7866 = x12373->_4;
      } else {
        
        char* x362 = if((x263==(2))) {
          char* x7869 = x12373->_5;
        } else {
          
          char* x361 = if((x263==(3))) {
            char* x7872 = x12373->_6;
          } else {
            
            char* x360 = if((x263==(4))) {
              char* x7875 = x12373->_7;
            } else {
              
              char* x359 = if((x263==(5))) {
                char* x7878 = x12373->_8;
              } else {
                
                char* x358 = if((x263==(6))) {
                  char* x7881 = x12373->_9;
                } else {
                  
                  char* x357 = if((x263==(7))) {
                    char* x7884 = x12373->_10;
                  } else {
                    
                    char* x356 = if((x263==(8))) {
                      char* x7887 = x12373->_11;
                    } else {
                      
                      char* x355 = if((x263==(9))) {
                        char* x7890 = x12373->_12;
                      } else {
                        
                        char* x7891 = x12373->_13;
                      };
                    };
                  };
                };
              };
            };
          };
        };
      };
      int x7892 = x12373->_3;
      int x365 = x275;
      x272[x365] = x7892;
      char* x7895 = x12342->_14;
      char* x16309 = strstr(x7895, "original");
      int x16310 = x16309!=(NULL);
      if((x16310&&(x16314))) {
        int x372 = x275;
        x273[x372] = "B";
      } else {
        
        int x374 = x275;
        x273[x374] = "G";
      };
      x12373->_3 = (x7892-(x333));
      if((x7892<=(x333))) {
        x12373->_3 += 91;
      };
      int x382 = 0;
      if((x329!=(x262))) {
        x382 = 1;
      };
      x838.update(x12373);
      double x7915 = x12342->_16;
      double x7916 = x12345->_8;
      double x7917 = x12349->_9;
      int x390 = x275;
      double x391 = x270[x390];
      double x398 = (((x333toDouble)*(x391))*(((1.0+(x7916))+(x7917))))*((1.0-(x7915)));
      int x399 = x275;
      x274[x399] = x398;
      double x401 = x324;
      x324 = (x401+(x398));
      int x404 = x275;
      struct SEntry10_IIIIIITIDS* x15836 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x15836, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x15836->_1 = x7841; x15836->_2 = x263; x15836->_3 = x262; x15836->_4 = (x404+(1)); x15836->_5 = x331; x15836->_6 = x329; x15836->_7 = NULL; x15836->_8 = x333; x15836->_9 = x398; x15836->_10 = x363;
      x4463.add(x15836);
      int x409 = x275;
      x275 = (x409+(1));
    };
  };
}
/* TRAITS STARTING */

/* GLOBAL VARS */

struct SEntry17_IIISSSSSSSSSSIIIS x7364;
struct SEntry11_IISSSSSSDDI x7838;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7214;
struct SEntry9_ISSSSSSDD x7835;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7565;
struct SEntry10_IIIIIITIDS x7210;
struct SEntry9_ISSSSSSDD x7531;
struct SEntry8_IIIITIIB x7201;
struct SEntry11_IISSSSSSDDI x7328;
struct SEntry17_IIISSSSSSSSSSIIIS x7862;
struct SEntry10_IIIIIITIDS x7341;
struct SEntry3_III x7189;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7406;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7831;
struct SEntry11_IISSSSSSDDI x7537;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7424;
struct SEntry5_IISDS x7810;
struct SEntry8_IIIITIIB x7432;
struct SEntry21_IIISSSSSSSSSTSDDDDIIS x7547;
int main(int argc, char** argv) {
 /* TRAITS ENDING   */
}
/* ----------- FUNCTIONS ----------- */
