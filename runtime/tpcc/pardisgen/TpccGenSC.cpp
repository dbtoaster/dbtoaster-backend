#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_set>
using namespace std;
     
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
/* TRAITS STARTING */

/* GLOBAL VARS */

Store_SEntry3_III x4539;
Store_SEntry8_IIIIITDS x4619;
Store_SEntry9_ISSSSSSDD x4638;
Store_SEntry5_IISDS x4657;
Store_SEntry8_IIIITIIB x4881;
Store_SEntry11_IISSSSSSDDI x4908;
Store_SEntry10_IIIIIITIDS x5080;
Store_SEntry21_IIISSSSSSSSSTSDDDDIIS x5186;
Store_SEntry17_IIISSSSSSSSSSIIIS x5212;
int main(int argc, char** argv) {
 /* TRAITS ENDING   */
void DeliveryTx() {
  int x14[10];
  int x15 = 1;
  while(1) {
    
    int x16 = x15;
    if (!((x16<=(10)))) break; 
    
    int x22 = x15;
    x7806->_2 = x22;
    x7806->_3 = x12;
    struct SEntry3_III x12857 = x926.get(x7806);
    if((x12857!=(NULL))) {
      int x7812 = x12857->_1;
      int x29 = x15;
      x14[(x29-(1))] = x7812;
      x925.del(x12857);;
      x926.del(x12857);;
      int x33 = x15;
      x7818->_1 = x7812;
      x7818->_2 = x33;
      x7818->_3 = x12;
      struct SEntry8_IIIITIIB x12871 = x949.get(x7818);
      int x7821 = x12871->_4;
      x12871->_6 = x13;
      x949.update(x12871);
      x950.update(x12871);
      double x40 = 0.0;
      int x41 = x15;
      x7827->_1 = x7812;
      x7827->_2 = x41;
      x7827->_3 = x12;
      x962.slice(x7827, ([&](struct SEntry10_IIIIIITIDS & x44) {
        x44->_7 = x11;
        double x46 = x40;
        double x7930 = x44->_9;
        x40 = (x46+(x7930));
        x962.update(x44);
        x961.update(x44);
      
      }));;
      int x53 = x15;
      x7831->_1 = x7821;
      x7831->_2 = x53;
      x7831->_3 = x12;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS x12896 = x968.get(x7831);
      double x56 = x40;
      x12896->_17 += x56;
      x12896->_20 += 1;
      x969.update(x12896);
      x968.update(x12896);
    } else {
      
      int x60 = x15;
      x14[(x60-(1))] = 0;
    };
    int x64 = x15;
    x15 = (x64+(1));
  };
  if(x10) {
    char* x68 = "\n+---------------------------- DELIVERY ---------------------------+\n Date: "+(x11);
    char* x69 = x68+("\n\n Warehouse: ");
    char* x70 = x69+(x12);
    char* x71 = x70+("\n Carrier:   ");
    char* x72 = x71+(x13);
    char* x73 = x72+("\n\n Delivered Orders\n");
    char* x74 = x73;
    int x75 = 0;
    int x76 = 1;
    while(1) {
      
      int x77 = x76;
      if (!((x77<=(10)))) break; 
      
      int x79 = x76;
      int x81 = x14[(x79-(1))];
      if((x81>=(0))) {
        char* x83 = x74;
        char* x84 = x83+("  District ");
        int x85 = x76;
        char* x87 = if((x85<(10))) {
        };
        char* x88 = x84+(x87);
        int x89 = x76;
        char* x90 = x88+(x89);
        char* x91 = x90+(": Order number ");
        int x92 = x76;
        int x94 = x14[(x92-(1))];
        char* x95 = x91+(x94);
        char* x96 = x95+(" was delivered.\n");
        x74 = x96;
      } else {
        
        char* x98 = x74;
        char* x99 = x98+("  District ");
        int x100 = x76;
        char* x102 = if((x100<(10))) {
        };
        char* x103 = x99+(x102);
        int x104 = x76;
        char* x105 = x103+(x104);
        char* x106 = x105+(": No orders to be delivered.\n");
        x74 = x106;
        int x108 = x75;
        x75 = (x108+(1));
      };
      int x112 = x76;
      x76 = (x112+(1));
    };
    char* x116 = x74;
    char* x117 = x116+("+-----------------------------------------------------------------+\n\n");
    x74 = x117;
    char* x119 = x74;
    println(x119);
  };
}
void StockLevelTx() {
  x8107->_1 = x126;
  x8107->_2 = x125;
  struct SEntry11_IISSSSSSDDI x13082 = x956.get(x8107);
  int x8111 = x13082->_11;
  int x133 = (x8111-(20));
  unordered_set<int> x134;
  while(1) {
    
    int x135 = x133;
    if (!((x135<(x8111)))) break; 
    
    int x137 = x133;
    x8120->_1 = x137;
    x8120->_2 = x126;
    x8120->_3 = x125;
    x962.slice(x8120, ([&](struct SEntry10_IIIIIITIDS & x140) {
      int x8153 = x140->_5;
      x8154->_1 = x8153;
      x8154->_2 = x125;
      struct SEntry17_IIISSSSSSSSSSIIIS x13100 = x974.get(x8154);
      int x8156 = x13100->_3;
      if((x8156<(x127))) {
        x134.insert(x8153);
      };
    
    }));;
    int x150 = x133;
    x133 = (x150+(1));
  };
  int x154 = x134.size();
  if(x122) {
    char* x155 = "\n+-------------------------- STOCK-LEVEL --------------------------+\n Warehouse: "+(x125);
    char* x156 = x155+("\n District:  ");
    char* x157 = x156+(x126);
    char* x158 = x157+("\n\n Stock Level Threshold: ");
    char* x159 = x158+(x127);
    char* x160 = x159+("\n Low Stock Count:       ");
    char* x161 = x160+(x154);
    char* x162 = x161+("\n+-----------------------------------------------------------------+\n\n");
    println(x162);
  };
}
void OrderStatusTx() {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8213 = NULL;
  if((x170>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS> x8216;
    x8218->_2 = x169;
    x8218->_3 = x168;
    x8218->_6 = x172;
    x969.slice(x8218, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x178) {
      x8216.push_back(x178);
    
    }));;
    int x182 = x8216.size();
    int x184 = (x182/(2));
    int x185 = x8216.size();
    if(((x185%(2))==(0))) {
      int x188 = x184;
      x184 = (x188-(1));
    };
    sort(x8216.begin(), x8216.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x192, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x193) {
      char* x8274 = x192->_4;
      char* x8275 = x193->_4;
      int x196 = strcmpi(x8274, x8275);
      return (x196<(0)); 
    }));
    int x200 = x184;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8234 = x8216[x200];
    x8213 = x8234;
  } else {
    
    x8236->_1 = x171;
    x8236->_2 = x169;
    x8236->_3 = x168;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x13200 = x968.get(x8236);
    x8213 = x13200;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8241 = x8213;
  int x8242 = x8241->_3;
  x8244->_2 = x169;
  x8244->_3 = x168;
  x8244->_4 = x8242;
  struct SEntry8_IIIITIIB x13210 = x950.get(x8244);
  int x218 = 0;
  int x8249 = x13210->_1;
  x218 = x8249;
}
void PaymentTx() {
  x8343->_1 = x224;
  struct SEntry9_ISSSSSSDD x13269 = x937.get(x8343);
  x13269->_9 += x231;
  x937.update(x13269);
  x8349->_1 = x225;
  x8349->_2 = x224;
  struct SEntry11_IISSSSSSDDI x13275 = x956.get(x8349);
  x13275->_10 += x231;
  x956.update(x13275);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8354 = NULL;
  if((x226>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS> x8357;
    x8359->_2 = x228;
    x8359->_3 = x227;
    x8359->_6 = x230;
    x969.slice(x8359, ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x247) {
      x8357.push_back(x247);
    
    }));;
    int x251 = x8357.size();
    int x253 = (x251/(2));
    int x254 = x8357.size();
    if(((x254%(2))==(0))) {
      int x257 = x253;
      x253 = (x257-(1));
    };
    sort(x8357.begin(), x8357.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x261, struct SEntry21_IIISSSSSSSSSTSDDDDIIS & x262) {
      char* x8461 = x261->_4;
      char* x8462 = x262->_4;
      int x265 = strcmpi(x8461, x8462);
      return (x265<(0)); 
    }));
    int x269 = x253;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8375 = x8357[x269];
    x8354 = x8375;
  } else {
    
    x8377->_1 = x229;
    x8377->_2 = x228;
    x8377->_3 = x227;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x13315 = x968.get(x8377);
    x8354 = x13315;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8381 = x8354;
  char* x8382 = x8381->_21;
  char* x279 = x8382;
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8384 = x8354;
  char* x8385 = x8384->_14;
  int x282 = x8385contains("BC");
  if(x282) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8388 = x8354;
    int x8389 = x8388->_1;
    char* x285 = x279;
    /* val x287 = "%d %d %d %d %d $%f %s | %s".format(x8389,x228,x227,x225,x224,x231,x222,x285) */
    x279 = x287;
    char* x289 = x279;
    int x290 = x289length;
    if((x290>(500))) {
      char* x292 = x279;
      char* x293 = x292substring(0, 500);
      x279 = x293;
    };
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8401 = x8354;
    x8401->_17 += x231;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8403 = x8354;
    char* x299 = x279;
    x8403->_21 = x299;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8406 = x8354;
    x8406->_17 += x231;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8408 = x8354;
  x969.update(x8408);
  x968.update(x8408);
  char* x8410 = x13269->_2;
  char* x8411 = x13275->_3;
  int x308 = x8410length;
  char* x311 = if((x308>(10))) {
    char* x310 = x8410substring(0, 10);
  };
  char* x312 = x311+("    ");
  int x313 = x8411length;
  char* x316 = if((x313>(10))) {
    char* x315 = x8411substring(0, 10);
  };
  char* x317 = x312+(x316);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS x8422 = x8354;
  int x8423 = x8422->_1;
  x4619.insert(());
}
void NewOrderTx() {
  if(x323) {
    /* val x340 = "Started NewOrder transaction for warehouse=%d, district=%d, customer=%d".format(x326,x327,x328) */
    println(x340);
  };
  int x343 = 0;
  int x344 = 0;
  char* x345[x329];
  int x346 = 1;
  while(1) {
    
    int x347 = x343;
    if (!(((x347<(x329))&&(x349)))) break; 
    
    int x351 = x343;
    int x352 = x331[x351];
    x8626->_1 = x352;
    struct SEntry5_IISDS x13480 = x942.get(x8626);
    if((x13480==(NULL))) {
      x346 = 0;
    } else {
      
      int x358 = x343;
      char* x8634 = x13480->_3;
      x335[x358] = x8634;
      int x361 = x343;
      double x8637 = x13480->_4;
      x334[x361] = x8637;
      int x364 = x343;
      char* x8640 = x13480->_5;
      x345[x364] = x8640;
    };
    int x368 = x343;
    x343 = (x368+(1));
  };
  int x372 = x346;
  if(x372) {
    x8647->_1 = x328;
    x8647->_2 = x327;
    x8647->_3 = x326;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS x13503 = x968.get(x8647);
    x8651->_1 = x326;
    struct SEntry9_ISSSSSSDD x13506 = x937.get(x8651);
    x8654->_1 = x327;
    x8654->_2 = x326;
    struct SEntry11_IISSSSSSDDI x13510 = x956.get(x8654);
    int x8657 = x13510->_11;
    x13510->_11 += 1;
    x956.update(x13510);
    x4881.insert(());
    x4539.insert(());
    double x392 = 0.0;
    x343 = 0;
    while(1) {
      
      int x394 = x343;
      if (!((x394<(x329)))) break; 
      
      int x396 = x343;
      int x397 = x332[x396];
      int x398 = x343;
      int x399 = x331[x398];
      int x400 = x343;
      int x401 = x333[x400];
      x8678->_1 = x399;
      x8678->_2 = x397;
      struct SEntry17_IIISSSSSSSSSSIIIS x13534 = x974.get(x8678);
      char* x431 = if((x327==(1))) {
        char* x8682 = x13534->_4;
      } else {
        
        char* x430 = if((x327==(2))) {
          char* x8685 = x13534->_5;
        } else {
          
          char* x429 = if((x327==(3))) {
            char* x8688 = x13534->_6;
          } else {
            
            char* x428 = if((x327==(4))) {
              char* x8691 = x13534->_7;
            } else {
              
              char* x427 = if((x327==(5))) {
                char* x8694 = x13534->_8;
              } else {
                
                char* x426 = if((x327==(6))) {
                  char* x8697 = x13534->_9;
                } else {
                  
                  char* x425 = if((x327==(7))) {
                    char* x8700 = x13534->_10;
                  } else {
                    
                    char* x424 = if((x327==(8))) {
                      char* x8703 = x13534->_11;
                    } else {
                      
                      char* x423 = if((x327==(9))) {
                        char* x8706 = x13534->_12;
                      } else {
                        
                        char* x8707 = x13534->_13;
                      };
                    };
                  };
                };
              };
            };
          };
        };
      };
      int x8708 = x13534->_3;
      int x433 = x343;
      x336[x433] = x8708;
      char* x8711 = x13503->_14;
      int x436 = x8711contains("original");
      if((x436&&(x438))) {
        int x440 = x343;
        x337[x440] = "B";
      } else {
        
        int x442 = x343;
        x337[x442] = "G";
      };
      x13534->_3 = (x8708-(x401));
      if((x8708<=(x401))) {
        x13534->_3 += 91;
      };
      int x450 = 0;
      if((x397!=(x326))) {
        x450 = 1;
      };
      x974.update(x13534);
      double x8731 = x13503->_16;
      double x8732 = x13506->_8;
      double x8733 = x13510->_9;
      int x458 = x343;
      double x459 = x334[x458];
      double x466 = (((x401toDouble)*(x459))*(((1.0+(x8732))+(x8733))))*((1.0-(x8731)));
      int x467 = x343;
      x338[x467] = x466;
      double x469 = x392;
      x392 = (x469+(x466));
      int x472 = x343;
      x5080.insert(());
      int x477 = x343;
      x343 = (x477+(1));
    };
  };
}
}
/* ----------- FUNCTIONS ----------- */
