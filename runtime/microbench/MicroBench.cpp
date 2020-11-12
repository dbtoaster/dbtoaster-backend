#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY false

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <fstream>
#include <locale>

#include "sc/mmap.hpp"
#include "sc/ExecutionProfiler.h"

using namespace std;
#include "types.hpp"
     
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int isSE;  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[22];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :isSE(0), _1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& isSE, const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : isSE(isSE), _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() const { return new SEntry21_IIISSSSSSSSSTSDDDDIIS(isSE, _1, _2, _3, _4.copy(), _5.copy(), _6.copy(), _7.copy(), _8.copy(), _9.copy(), _10.copy(), _11.copy(), _12.copy(), _13, _14.copy(), _15, _16, _17, _18, _19, _20, _21.copy()); }
};
struct SEntry2_DS {
  int isSE;  double _1;  PString _2;  SEntry2_DS *prv;  SEntry2_DS *nxt; void* backPtrs[3];
  SEntry2_DS() :isSE(0), _1(-1.7976931348623157E308), _2(), prv(nullptr), nxt(nullptr) {}
  SEntry2_DS(const int& isSE, const double& _1, const PString& _2) : isSE(isSE), _1(_1), _2(_2), prv(nullptr), nxt(nullptr) {}
  SEntry2_DS* copy() const { return new SEntry2_DS(isSE, _1, _2.copy()); }
};
struct SEntry1_S {
  int isSE;  PString _1;  SEntry1_S *prv;  SEntry1_S *nxt; void* backPtrs[2];
  SEntry1_S() :isSE(0), _1(), prv(nullptr), nxt(nullptr) {}
  SEntry1_S(const int& isSE, const PString& _1) : isSE(isSE), _1(_1), prv(nullptr), nxt(nullptr) {}
  SEntry1_S* copy() const { return new SEntry1_S(isSE, _1.copy()); }
};
bool operator== (const SEntry21_IIISSSSSSSSSTSDDDDIIS& o1, const SEntry21_IIISSSSSSSSSTSDDDDIIS& o2) {
  return o1.isSE == o2.isSE && 
  o1._1 == o2._1 && 
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
  return o1.isSE == o2.isSE && 
  (fabs(o1._1 - o2._1) < 0.01) && 
  o1._2 == o2._2;
}
bool operator== (const SEntry1_S& o1, const SEntry1_S& o2) {
  return o1.isSE == o2.isSE && 
  o1._1 == o2._1;
}
 struct SEntry1_S_Idx1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry1_S& x1167)  { 
    int x1168 = 0;
    int x1169 = x1168;
    x1168 = (x1169^(((((HASH((x1167._1)))+(-1640531527))+((x1169<<(6))))+((x1169>>(2))))));
    int x1179 = x1168;
    return x1179; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry1_S& x1181, const struct SEntry1_S& x1182) { 
    int x1183 = 0;
    if((x1181.isSE)) {
      PString x1185 = x1181._1;
      int x1188 = 1;
      if((x1185.data_ == nullptr)) {
      } else {
        x1188 = (x1185==((x1182._1)));
      };
      int x1192 = x1188;
      if(x1192) {
        x1183 = 0;
      } else {
        x1183 = 1;
      };
    } else {
      if((x1182.isSE)) {
        PString x1198 = x1182._1;
        int x1200 = 1;
        if((x1198.data_ == nullptr)) {
        } else {
          x1200 = ((x1181._1)==(x1198));
        };
        int x1204 = x1200;
        if(x1204) {
          x1183 = 0;
        } else {
          x1183 = 1;
        };
      } else {
        if(((x1181._1)==((x1182._1)))) {
          x1183 = 0;
        } else {
          x1183 = 1;
        };
      };
    };
    int x1216 = x1183;
    return x1216; 
  }
};
 struct SEntry2_DS_Idx12 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry2_DS& x1078)  { 
    int x1079 = 0;
    int x1080 = x1079;
    x1079 = (x1080^(((((HASH((x1078._1)))+(-1640531527))+((x1080<<(6))))+((x1080>>(2))))));
    int x1090 = x1079;
    x1079 = (x1090^(((((HASH((x1078._2)))+(-1640531527))+((x1090<<(6))))+((x1090>>(2))))));
    int x1100 = x1079;
    return x1100; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry2_DS& x1102, const struct SEntry2_DS& x1103) { 
    int x1104 = 0;
    if((x1102.isSE)) {
      double x1106 = x1102._1;
      int x1109 = 1;
      if((x1106==(-1.7976931348623157E308))) {
      } else {
        x1109 = (x1106==((x1103._1)));
      };
      int x1113 = x1109;
      if(x1113) {
        PString x1114 = x1102._2;
        int x1117 = 1;
        if((x1114.data_ == nullptr)) {
        } else {
          x1117 = (x1114==((x1103._2)));
        };
        int x1121 = x1117;
        if(x1121) {
          x1104 = 0;
        } else {
          x1104 = 1;
        };
      } else {
        x1104 = 1;
      };
    } else {
      if((x1103.isSE)) {
        double x1129 = x1103._1;
        int x1131 = 1;
        if((x1129==(-1.7976931348623157E308))) {
        } else {
          x1131 = ((x1102._1)==(x1129));
        };
        int x1135 = x1131;
        if(x1135) {
          PString x1137 = x1103._2;
          int x1139 = 1;
          if((x1137.data_ == nullptr)) {
          } else {
            x1139 = ((x1102._2)==(x1137));
          };
          int x1143 = x1139;
          if(x1143) {
            x1104 = 0;
          } else {
            x1104 = 1;
          };
        } else {
          x1104 = 1;
        };
      } else {
        if(((x1102._1)==((x1103._1)))) {
          if(((x1102._2)==((x1103._2)))) {
            x1104 = 0;
          } else {
            x1104 = 1;
          };
        } else {
          x1104 = 1;
        };
      };
    };
    int x1162 = x1104;
    return x1162; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x101)  { 
    int x102 = 0;
    int x103 = x102;
    x102 = (x103^(((((HASH((x101._1)))+(-1640531527))+((x103<<(6))))+((x103>>(2))))));
    int x113 = x102;
    x102 = (x113^(((((HASH((x101._2)))+(-1640531527))+((x113<<(6))))+((x113>>(2))))));
    int x123 = x102;
    x102 = (x123^(((((HASH((x101._3)))+(-1640531527))+((x123<<(6))))+((x123>>(2))))));
    int x133 = x102;
    return x133; 
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x135, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x136) { 
    int x137 = 0;
    if((x135.isSE)) {
      int x139 = x135._1;
      int x142 = 1;
      if((x139==(-2147483648))) {
      } else {
        x142 = (x139==((x136._1)));
      };
      int x146 = x142;
      if(x146) {
        int x147 = x135._2;
        int x150 = 1;
        if((x147==(-2147483648))) {
        } else {
          x150 = (x147==((x136._2)));
        };
        int x154 = x150;
        if(x154) {
          int x155 = x135._3;
          int x158 = 1;
          if((x155==(-2147483648))) {
          } else {
            x158 = (x155==((x136._3)));
          };
          int x162 = x158;
          if(x162) {
            PString x163 = x135._4;
            int x166 = 1;
            if((x163.data_ == nullptr)) {
            } else {
              x166 = (x163==((x136._4)));
            };
            int x170 = x166;
            if(x170) {
              PString x171 = x135._5;
              int x174 = 1;
              if((x171.data_ == nullptr)) {
              } else {
                x174 = (x171==((x136._5)));
              };
              int x178 = x174;
              if(x178) {
                PString x179 = x135._6;
                int x182 = 1;
                if((x179.data_ == nullptr)) {
                } else {
                  x182 = (x179==((x136._6)));
                };
                int x186 = x182;
                if(x186) {
                  PString x187 = x135._7;
                  int x190 = 1;
                  if((x187.data_ == nullptr)) {
                  } else {
                    x190 = (x187==((x136._7)));
                  };
                  int x194 = x190;
                  if(x194) {
                    PString x195 = x135._8;
                    int x198 = 1;
                    if((x195.data_ == nullptr)) {
                    } else {
                      x198 = (x195==((x136._8)));
                    };
                    int x202 = x198;
                    if(x202) {
                      PString x203 = x135._9;
                      int x206 = 1;
                      if((x203.data_ == nullptr)) {
                      } else {
                        x206 = (x203==((x136._9)));
                      };
                      int x210 = x206;
                      if(x210) {
                        PString x211 = x135._10;
                        int x214 = 1;
                        if((x211.data_ == nullptr)) {
                        } else {
                          x214 = (x211==((x136._10)));
                        };
                        int x218 = x214;
                        if(x218) {
                          PString x219 = x135._11;
                          int x222 = 1;
                          if((x219.data_ == nullptr)) {
                          } else {
                            x222 = (x219==((x136._11)));
                          };
                          int x226 = x222;
                          if(x226) {
                            PString x227 = x135._12;
                            int x230 = 1;
                            if((x227.data_ == nullptr)) {
                            } else {
                              x230 = (x227==((x136._12)));
                            };
                            int x234 = x230;
                            if(x234) {
                              date x235 = x135._13;
                              int x238 = 1;
                              if((x235==(0))) {
                              } else {
                                x238 = (x235==((x136._13)));
                              };
                              int x242 = x238;
                              if(x242) {
                                PString x243 = x135._14;
                                int x246 = 1;
                                if((x243.data_ == nullptr)) {
                                } else {
                                  x246 = (x243==((x136._14)));
                                };
                                int x250 = x246;
                                if(x250) {
                                  double x251 = x135._15;
                                  int x254 = 1;
                                  if((x251==(-1.7976931348623157E308))) {
                                  } else {
                                    x254 = (x251==((x136._15)));
                                  };
                                  int x258 = x254;
                                  if(x258) {
                                    double x259 = x135._16;
                                    int x262 = 1;
                                    if((x259==(-1.7976931348623157E308))) {
                                    } else {
                                      x262 = (x259==((x136._16)));
                                    };
                                    int x266 = x262;
                                    if(x266) {
                                      double x267 = x135._17;
                                      int x270 = 1;
                                      if((x267==(-1.7976931348623157E308))) {
                                      } else {
                                        x270 = (x267==((x136._17)));
                                      };
                                      int x274 = x270;
                                      if(x274) {
                                        double x275 = x135._18;
                                        int x278 = 1;
                                        if((x275==(-1.7976931348623157E308))) {
                                        } else {
                                          x278 = (x275==((x136._18)));
                                        };
                                        int x282 = x278;
                                        if(x282) {
                                          int x283 = x135._19;
                                          int x286 = 1;
                                          if((x283==(-2147483648))) {
                                          } else {
                                            x286 = (x283==((x136._19)));
                                          };
                                          int x290 = x286;
                                          if(x290) {
                                            int x291 = x135._20;
                                            int x294 = 1;
                                            if((x291==(-2147483648))) {
                                            } else {
                                              x294 = (x291==((x136._20)));
                                            };
                                            int x298 = x294;
                                            if(x298) {
                                              PString x299 = x135._21;
                                              int x302 = 1;
                                              if((x299.data_ == nullptr)) {
                                              } else {
                                                x302 = (x299==((x136._21)));
                                              };
                                              int x306 = x302;
                                              if(x306) {
                                                x137 = 0;
                                              } else {
                                                x137 = 1;
                                              };
                                            } else {
                                              x137 = 1;
                                            };
                                          } else {
                                            x137 = 1;
                                          };
                                        } else {
                                          x137 = 1;
                                        };
                                      } else {
                                        x137 = 1;
                                      };
                                    } else {
                                      x137 = 1;
                                    };
                                  } else {
                                    x137 = 1;
                                  };
                                } else {
                                  x137 = 1;
                                };
                              } else {
                                x137 = 1;
                              };
                            } else {
                              x137 = 1;
                            };
                          } else {
                            x137 = 1;
                          };
                        } else {
                          x137 = 1;
                        };
                      } else {
                        x137 = 1;
                      };
                    } else {
                      x137 = 1;
                    };
                  } else {
                    x137 = 1;
                  };
                } else {
                  x137 = 1;
                };
              } else {
                x137 = 1;
              };
            } else {
              x137 = 1;
            };
          } else {
            x137 = 1;
          };
        } else {
          x137 = 1;
        };
      } else {
        x137 = 1;
      };
    } else {
      if((x136.isSE)) {
        int x352 = x136._1;
        int x354 = 1;
        if((x352==(-2147483648))) {
        } else {
          x354 = ((x135._1)==(x352));
        };
        int x358 = x354;
        if(x358) {
          int x360 = x136._2;
          int x362 = 1;
          if((x360==(-2147483648))) {
          } else {
            x362 = ((x135._2)==(x360));
          };
          int x366 = x362;
          if(x366) {
            int x368 = x136._3;
            int x370 = 1;
            if((x368==(-2147483648))) {
            } else {
              x370 = ((x135._3)==(x368));
            };
            int x374 = x370;
            if(x374) {
              PString x376 = x136._4;
              int x378 = 1;
              if((x376.data_ == nullptr)) {
              } else {
                x378 = ((x135._4)==(x376));
              };
              int x382 = x378;
              if(x382) {
                PString x384 = x136._5;
                int x386 = 1;
                if((x384.data_ == nullptr)) {
                } else {
                  x386 = ((x135._5)==(x384));
                };
                int x390 = x386;
                if(x390) {
                  PString x392 = x136._6;
                  int x394 = 1;
                  if((x392.data_ == nullptr)) {
                  } else {
                    x394 = ((x135._6)==(x392));
                  };
                  int x398 = x394;
                  if(x398) {
                    PString x400 = x136._7;
                    int x402 = 1;
                    if((x400.data_ == nullptr)) {
                    } else {
                      x402 = ((x135._7)==(x400));
                    };
                    int x406 = x402;
                    if(x406) {
                      PString x408 = x136._8;
                      int x410 = 1;
                      if((x408.data_ == nullptr)) {
                      } else {
                        x410 = ((x135._8)==(x408));
                      };
                      int x414 = x410;
                      if(x414) {
                        PString x416 = x136._9;
                        int x418 = 1;
                        if((x416.data_ == nullptr)) {
                        } else {
                          x418 = ((x135._9)==(x416));
                        };
                        int x422 = x418;
                        if(x422) {
                          PString x424 = x136._10;
                          int x426 = 1;
                          if((x424.data_ == nullptr)) {
                          } else {
                            x426 = ((x135._10)==(x424));
                          };
                          int x430 = x426;
                          if(x430) {
                            PString x432 = x136._11;
                            int x434 = 1;
                            if((x432.data_ == nullptr)) {
                            } else {
                              x434 = ((x135._11)==(x432));
                            };
                            int x438 = x434;
                            if(x438) {
                              PString x440 = x136._12;
                              int x442 = 1;
                              if((x440.data_ == nullptr)) {
                              } else {
                                x442 = ((x135._12)==(x440));
                              };
                              int x446 = x442;
                              if(x446) {
                                date x448 = x136._13;
                                int x450 = 1;
                                if((x448==(0))) {
                                } else {
                                  x450 = ((x135._13)==(x448));
                                };
                                int x454 = x450;
                                if(x454) {
                                  PString x456 = x136._14;
                                  int x458 = 1;
                                  if((x456.data_ == nullptr)) {
                                  } else {
                                    x458 = ((x135._14)==(x456));
                                  };
                                  int x462 = x458;
                                  if(x462) {
                                    double x464 = x136._15;
                                    int x466 = 1;
                                    if((x464==(-1.7976931348623157E308))) {
                                    } else {
                                      x466 = ((x135._15)==(x464));
                                    };
                                    int x470 = x466;
                                    if(x470) {
                                      double x472 = x136._16;
                                      int x474 = 1;
                                      if((x472==(-1.7976931348623157E308))) {
                                      } else {
                                        x474 = ((x135._16)==(x472));
                                      };
                                      int x478 = x474;
                                      if(x478) {
                                        double x480 = x136._17;
                                        int x482 = 1;
                                        if((x480==(-1.7976931348623157E308))) {
                                        } else {
                                          x482 = ((x135._17)==(x480));
                                        };
                                        int x486 = x482;
                                        if(x486) {
                                          double x488 = x136._18;
                                          int x490 = 1;
                                          if((x488==(-1.7976931348623157E308))) {
                                          } else {
                                            x490 = ((x135._18)==(x488));
                                          };
                                          int x494 = x490;
                                          if(x494) {
                                            int x496 = x136._19;
                                            int x498 = 1;
                                            if((x496==(-2147483648))) {
                                            } else {
                                              x498 = ((x135._19)==(x496));
                                            };
                                            int x502 = x498;
                                            if(x502) {
                                              int x504 = x136._20;
                                              int x506 = 1;
                                              if((x504==(-2147483648))) {
                                              } else {
                                                x506 = ((x135._20)==(x504));
                                              };
                                              int x510 = x506;
                                              if(x510) {
                                                PString x512 = x136._21;
                                                int x514 = 1;
                                                if((x512.data_ == nullptr)) {
                                                } else {
                                                  x514 = ((x135._21)==(x512));
                                                };
                                                int x518 = x514;
                                                if(x518) {
                                                  x137 = 0;
                                                } else {
                                                  x137 = 1;
                                                };
                                              } else {
                                                x137 = 1;
                                              };
                                            } else {
                                              x137 = 1;
                                            };
                                          } else {
                                            x137 = 1;
                                          };
                                        } else {
                                          x137 = 1;
                                        };
                                      } else {
                                        x137 = 1;
                                      };
                                    } else {
                                      x137 = 1;
                                    };
                                  } else {
                                    x137 = 1;
                                  };
                                } else {
                                  x137 = 1;
                                };
                              } else {
                                x137 = 1;
                              };
                            } else {
                              x137 = 1;
                            };
                          } else {
                            x137 = 1;
                          };
                        } else {
                          x137 = 1;
                        };
                      } else {
                        x137 = 1;
                      };
                    } else {
                      x137 = 1;
                    };
                  } else {
                    x137 = 1;
                  };
                } else {
                  x137 = 1;
                };
              } else {
                x137 = 1;
              };
            } else {
              x137 = 1;
            };
          } else {
            x137 = 1;
          };
        } else {
          x137 = 1;
        };
      } else {
        if(((x135._1)==((x136._1)))) {
          if(((x135._2)==((x136._2)))) {
            if(((x135._3)==((x136._3)))) {
              x137 = 0;
            } else {
              x137 = 1;
            };
          } else {
            x137 = 1;
          };
        } else {
          x137 = 1;
        };
      };
    };
    int x580 = x137;
    return x580; 
  }
};

typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1> customerTblIdx0Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1>> customerTblStoreType;
customerTblStoreType  customerTbl;
customerTblIdx0Type& customerTblIdx0 = * (customerTblIdx0Type *)customerTbl.index[0];




void fun1() {
  auto& x1165 = customerTbl.map<struct SEntry2_DS, HashIndex<struct SEntry2_DS, char, SEntry2_DS_Idx12, 1>>([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* e) -> struct SEntry2_DS* {
    struct SEntry2_DS y3243; struct SEntry2_DS* x3243 = &y3243;
    x3243->_1 = ((e->_15)-((e->_17))); x3243->_2 = ((e->_4).substr(0, 5));
    return x3243; 
  });
  auto& x17 = x1165.filter([&](struct SEntry2_DS* e) -> int {
    return ((e->_1)<(47000.0)); 
  });
  auto& x1219 = x17.map<struct SEntry1_S, HashIndex<struct SEntry1_S, char, SEntry1_S_Idx1, 1>>([&](struct SEntry2_DS* e) -> struct SEntry1_S* {
    struct SEntry1_S y3253; struct SEntry1_S* x3253 = &y3253;
    x3253->_1 = (e->_2);
    return x3253; 
  });
  int x28 = x1219.fold<int>(0, [&](int a, struct SEntry1_S* b) -> int {
    return (a+(1)); 
  });
  int x29 = x28;
}
#include "sc/MB1.h"

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
