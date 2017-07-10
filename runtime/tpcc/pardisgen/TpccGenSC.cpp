#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SC_GENERATED 1
#define USING_GENERIC_ENTRY true
#define CONCURRENT 1

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <mmap.hpp>
#include <valgrind/callgrind.h>
#include <iomanip>
#include <fstream>
#include <locale>

#include "TransactionManager.h"


#include "ExecutionProfiler.h"

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

uint failedOS = 0;
uint failedDel = 0;
uint failedNO = 0;

const size_t warehouseTblSize = 8 * (numWare / 8 + 1);
const size_t itemTblSize = 100000 * 1.5;
const size_t districtTblSize = 8 * ((numWare * 10) / 8 + 1);
const size_t customerTblSize = districtTblSize * 3000;
const size_t orderTblSize = customerTblSize * 1.5 + 0.5 * numPrograms;
const size_t newOrderTblSize = orderTblSize * 0.3 + 0.5 * numPrograms;
const size_t orderLineTblSize = orderTblSize * 12;
const size_t stockTblSize = numWare * itemTblSize;
const size_t historyTblSize = orderTblSize;

const size_t districtTblArrayLengths[] = {1};
const size_t customerTblArrayLengths[] = {1,1};
const size_t itemTblArrayLengths[] = {1};
const size_t historyTblArrayLengths[] = {1};
const size_t orderTblArrayLengths[] = {1,1};
const size_t newOrderTblArrayLengths[] = {1,1};
const size_t warehouseTblArrayLengths[] = {1};
const size_t stockTblArrayLengths[] = {1};
const size_t orderLineTblArrayLengths[] = {1,1};

const size_t warehouseTblPoolSizes[] = {8, 0};
const size_t itemTblPoolSizes[] = {65536*2, 0};
const size_t districtTblPoolSizes[] = {16, 0};
const size_t customerTblPoolSizes[] = {16384*2, 0, 16384};
const size_t orderTblPoolSizes[] = {262144*2, 65536, 0};
const size_t newOrderTblPoolSizes[] = {8192*2, 2048, 0};
const size_t orderLineTblPoolSizes[] = {4194304*2, 1048576, 2097152};
const size_t stockTblPoolSizes[] = {65536*2, 0};
const size_t historyTblPoolSizes[] = {262144*2, 65536};
     



#if USING_GENERIC_ENTRY
struct GenericOps_3214 {  //OL 0
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(1).data.i;
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    int x4 = (x3 << 4) + e.map.at(4).data.i;
    return x4;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1) || e1.map.at(4) != e2.map.at(4))
       return 1;
    return 0;
  }
};
struct GenericOps_23 { //NO 1
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(3).data.i;
    int x2 = (x1 << 4) + e.map.at(2).data.i;
    return x2;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
       return 1;
    return 0;
  }
};
struct GenericOps_321 { //C0  O0   NO0
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(1).data.i;
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(3) != e2.map.at(3) || e1.map.at(2) != e2.map.at(2) || e1.map.at(1) != e2.map.at(1))
       return 1;
    return 0;
  }
};
struct GenericOps_236 { //C 1
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = HASH(e.map.at(6).data.s);
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(6) != e2.map.at(6))
       return 1;
    return 0;
  }
};
struct GenericOps_123 { //OL1
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(1).data.i;
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3))
       return 1;
    return 0;
  }
};
struct GenericOps_12345678 { // H0
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    unsigned int h = 0;
    h = h ^ (HASH(e.map.at(1)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(2)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(3)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(4)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(5)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(6)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(7)) + 0x9e3779b9 + (h<<6) + (h>>2));
    h = h ^ (HASH(e.map.at(8)) + 0x9e3779b9 + (h<<6) + (h>>2));
    return h;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(1) != e2.map.at(1) || e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4) || e1.map.at(5) != e2.map.at(5) || e1.map.at(6) != e2.map.at(6) || e1.map.at(7) != e2.map.at(7) || e1.map.at(8) != e2.map.at(8))
       return 1;
    return 0;
  }
};
struct GenericOps_234 {  //O 1
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(4).data.i;
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;

  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    if(e1.map.at(2) != e2.map.at(2) || e1.map.at(3) != e2.map.at(3) || e1.map.at(4) != e2.map.at(4))
       return 1;
    return 0;
  }
};
struct GenericCmp_236_4 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = HASH(e.map.at(6));
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    const Any &r1 = e1.map.at(4);
    const Any &r2 = e2.map.at(4);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;

  }
};
struct GenericCmp_23_1 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.getInt(3);
    int x2 = (x1 << 4) + e.getInt(2);
    return x2;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    const Any &r1 = e1.map.at(1);
    const Any &r2 = e2.map.at(1);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;

  }
};
struct GenericCmp_234_1 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    int x1 = e.map.at(4).data.i;
    int x2 = (x1 << 2) + e.map.at(3).data.i;
    int x3 = (x2 << 4) + e.map.at(2).data.i;
    return x3;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) {
    const Any &r1 = e1.map.at(1);
    const Any &r2 = e2.map.at(1);
    if (r1 == r2)
      return 0;
    else if( r1 < r2)
      return -1;
    else
      return 1;

  }
};
struct GenericFixedRange_1f1t100002 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    return e.getInt(1)-1;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_3f1t6_2f1t11_1f1t3001 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    return ((e.getInt(3)-1) * 10 + e.getInt(2)-1)*3000 + e.getInt(1)-1;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_2f1t6_1f1t100001 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    return (e.getInt(2)-1)* 100000 + e.getInt(1)-1;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_1f1t6 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    return  e.getInt(1) - 1;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
struct GenericFixedRange_2f1t6_1f1t11 {
  FORCE_INLINE static size_t hash(const GenericEntry& e) {
    return (e.getInt(2)-1) * 10 + e.getInt(1)-1;;
  }
  FORCE_INLINE static char cmp(const GenericEntry& e1, const GenericEntry& e2) { return 0;}
};
#else
struct SEntry8_IIIITIIB_Idx234 {  // O 1
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3468)  {
    int x1 = x3468._4;
    int x2 = (x1 << 2) + x3468._3;
    int x3 = (x2 << 4) + x3468._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3502, const struct SEntry8_IIIITIIB& x3503) {
    int x3504 = 0;
    if(((x3502._2)==((x3503._2)))) {
      if(((x3502._3)==((x3503._3)))) {
        if(((x3502._4)==((x3503._4)))) {
          x3504 = 0;
        } else {
          x3504 = 1;
        };
      } else {
        x3504 = 1;
      };
    } else {
      x3504 = 1;
    };
    int x3521 = x3504;
    return x3521;
  }
};
 struct SEntry10_IIIIIITIDS_Idx3214 { // OL 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3576)  {
    int x1 = x3576._1;
    int x2 = (x1 << 2) + x3576._3;
    int x3 = (x2 << 4) + x3576._2;
    int x4 = (x3 << 4) + x3576._4;
    return x4;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3620, const struct SEntry10_IIIIIITIDS& x3621) {
    int x3622 = 0;
    if(((x3620._3)==((x3621._3)))) {
      if(((x3620._2)==((x3621._2)))) {
        if(((x3620._1)==((x3621._1)))) {
          if(((x3620._4)==((x3621._4)))) {
            x3622 = 0;
          } else {
            x3622 = 1;
          };
        } else {
          x3622 = 1;
        };
      } else {
        x3622 = 1;
      };
    } else {
      x3622 = 1;
    };
    int x3644 = x3622;
    return x3644;
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx321 {  //C 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3709)  {
    int x2 = x3709._3;
    int x3 = (x2 << 4) + x3709._2;
    int x1 = (x3 << 12) + x3709._1;
    return x1;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3743, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3744) {
    int x3745 = 0;
    if(((x3743._3)==((x3744._3)))) {
      if(((x3743._2)==((x3744._2)))) {
        if(((x3743._1)==((x3744._1)))) {
          x3745 = 0;
        } else {
          x3745 = 1;
        };
      } else {
        x3745 = 1;
      };
    } else {
      x3745 = 1;
    };
    int x3762 = x3745;
    return x3762;
  }
};
 struct SEntry8_IIIIITDS_Idx12345678 {  //H Idx0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x3215)  {
    int x3216 = 0;
    int x3217 = x3216;
    x3216 = (x3217^(((((HASH((x3215._1)))+(-1640531527))+((x3217<<(6))))+((x3217>>(2))))));
    int x3227 = x3216;
    x3216 = (x3227^(((((HASH((x3215._2)))+(-1640531527))+((x3227<<(6))))+((x3227>>(2))))));
    int x3237 = x3216;
    x3216 = (x3237^(((((HASH((x3215._3)))+(-1640531527))+((x3237<<(6))))+((x3237>>(2))))));
    int x3247 = x3216;
    x3216 = (x3247^(((((HASH((x3215._4)))+(-1640531527))+((x3247<<(6))))+((x3247>>(2))))));
    int x3257 = x3216;
    x3216 = (x3257^(((((HASH((x3215._5)))+(-1640531527))+((x3257<<(6))))+((x3257>>(2))))));
    int x3267 = x3216;
    x3216 = (x3267^(((((HASH((x3215._6)))+(-1640531527))+((x3267<<(6))))+((x3267>>(2))))));
    int x3277 = x3216;
    x3216 = (x3277^(((((HASH((x3215._7)))+(-1640531527))+((x3277<<(6))))+((x3277>>(2))))));
    int x3287 = x3216;
    x3216 = (x3287^(((((HASH((x3215._8)))+(-1640531527))+((x3287<<(6))))+((x3287>>(2))))));
    int x3297 = x3216;
    return x3297;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x3299, const struct SEntry8_IIIIITDS& x3300) {
    int x3301 = 0;
    if(((x3299._1)==((x3300._1)))) {
      if(((x3299._2)==((x3300._2)))) {
        if(((x3299._3)==((x3300._3)))) {
          if(((x3299._4)==((x3300._4)))) {
            if(((x3299._5)==((x3300._5)))) {
              if(((x3299._6)==((x3300._6)))) {
                if(((x3299._7)==((x3300._7)))) {
                  if(((x3299._8)==((x3300._8)))) {
                    x3301 = 0;
                  } else {
                    x3301 = 1;
                  };
                } else {
                  x3301 = 1;
                };
              } else {
                x3301 = 1;
              };
            } else {
              x3301 = 1;
            };
          } else {
            x3301 = 1;
          };
        } else {
          x3301 = 1;
        };
      } else {
        x3301 = 1;
      };
    } else {
      x3301 = 1;
    };
    int x3343 = x3301;
    return x3343;
  }
};
 struct SEntry8_IIIITIIB_Idx321 {  // O 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3412)  {
    int x1 = x3412._1;
    int x2 = (x1 << 2) + x3412._3;
    int x3 = (x2 << 4) + x3412._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3446, const struct SEntry8_IIIITIIB& x3447) {
    int x3448 = 0;
    if(((x3446._3)==((x3447._3)))) {
      if(((x3446._2)==((x3447._2)))) {
        if(((x3446._1)==((x3447._1)))) {
          x3448 = 0;
        } else {
          x3448 = 1;
        };
      } else {
        x3448 = 1;
      };
    } else {
      x3448 = 1;
    };
    int x3465 = x3448;
    return x3465;
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx21 { // S 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3826)  {
    int x1 = x3826._1;
    int x2 = (x1 << 2) + x3826._2;
    return x2;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3850, const struct SEntry17_IIISSSSSSSSSSIIIS& x3851) {
    int x3852 = 0;
    if(((x3850._2)==((x3851._2)))) {
      if(((x3850._1)==((x3851._1)))) {
        x3852 = 0;
      } else {
        x3852 = 1;
      };
    } else {
      x3852 = 1;
    };
    int x3864 = x3852;
    return x3864;
  }
};
 struct SEntry3_III_Idx23 {  //NO Idx 1
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3168)  {
    int x1 = x3168._3;
    int x2 = (x1 << 4) + x3168._2;
    return x2;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3192, const struct SEntry3_III& x3193) {
    int x3194 = 0;
    if(((x3192._2)==((x3193._2)))) {
      if(((x3192._3)==((x3193._3)))) {
        x3194 = 0;
      } else {
        x3194 = 1;
      };
    } else {
      x3194 = 1;
    };
    int x3206 = x3194;
    return x3206;
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {  // OL 1
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x3647)  {
    int x1 = x3647._1;
    int x2 = (x1 << 2) + x3647._3;
    int x3 = (x2 << 4) + x3647._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x3681, const struct SEntry10_IIIIIITIDS& x3682) {
    int x3683 = 0;
    if(((x3681._1)==((x3682._1)))) {
      if(((x3681._2)==((x3682._2)))) {
        if(((x3681._3)==((x3682._3)))) {
          x3683 = 0;
        } else {
          x3683 = 1;
        };
      } else {
        x3683 = 1;
      };
    } else {
      x3683 = 1;
    };
    int x3700 = x3683;
    return x3700;
  }
};
 struct SEntry3_III_Idx321 {  //NO Idx0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3112)  {
    int x1 = x3112._1;
    int x2 = (x1 << 2) + x3112._3;
    int x3 = (x2 << 4) + x3112._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3146, const struct SEntry3_III& x3147) {
    int x3148 = 0;
    if(((x3146._3)==((x3147._3)))) {
      if(((x3146._2)==((x3147._2)))) {
        if(((x3146._1)==((x3147._1)))) {
          x3148 = 0;
        } else {
          x3148 = 1;
        };
      } else {
        x3148 = 1;
      };
    } else {
      x3148 = 1;
    };
    int x3165 = x3148;
    return x3165;
  }
};
 struct SEntry5_IISDS_Idx1 { // I 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3381)  {
    int x3382 = 0;
    int x3383 = x3382;
    x3382 = (x3383^(((((HASH((x3381._1)))+(-1640531527))+((x3383<<(6))))+((x3383>>(2))))));
    int x3393 = x3382;
    return x3393;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3395, const struct SEntry5_IISDS& x3396) {
    int x3397 = 0;
    if(((x3395._1)==((x3396._1)))) {
      x3397 = 0;
    } else {
      x3397 = 1;
    };
    int x3404 = x3397;
    return x3404;
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 { // C 1
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3765)  {
    int x1 = HASH(x3765._6);
    int x2 = (x1 << 2) + x3765._3;
    int x3 = (x2 << 4) + x3765._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3799, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3800) {
    int x3801 = 0;
    if(((x3799._2)==((x3800._2)))) {
      if(((x3799._3)==((x3800._3)))) {
        if(((x3799._6)==((x3800._6)))) {
          x3801 = 0;
        } else {
          x3801 = 1;
        };
      } else {
        x3801 = 1;
      };
    } else {
      x3801 = 1;
    };
    int x3818 = x3801;
    return x3818;
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 { // W 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3351)  {
    int x3352 = 0;
    int x3353 = x3352;
    x3352 = (x3353^(((((HASH((x3351._1)))+(-1640531527))+((x3353<<(6))))+((x3353>>(2))))));
    int x3363 = x3352;
    return x3363;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3365, const struct SEntry9_ISSSSSSDD& x3366) {
    int x3367 = 0;
    if(((x3365._1)==((x3366._1)))) {
      x3367 = 0;
    } else {
      x3367 = 1;
    };
    int x3374 = x3367;
    return x3374;
  }
};
 struct SEntry11_IISSSSSSDDI_Idx21 { // D 0
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3530)  {
    int x3531 = 0;
    int x3532 = x3531;
    x3531 = (x3532^(((((HASH((x3530._2)))+(-1640531527))+((x3532<<(6))))+((x3532>>(2))))));
    int x3542 = x3531;
    x3531 = (x3542^(((((HASH((x3530._1)))+(-1640531527))+((x3542<<(6))))+((x3542>>(2))))));
    int x3552 = x3531;
    return x3552;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3554, const struct SEntry11_IISSSSSSDDI& x3555) {
    int x3556 = 0;
    if(((x3554._2)==((x3555._2)))) {
      if(((x3554._1)==((x3555._1)))) {
        x3556 = 0;
      } else {
        x3556 = 1;
      };
    } else {
      x3556 = 1;
    };
    int x3568 = x3556;
    return x3568;
  }
};

struct SEntry9_ISSSSSSDD_Idx1f1t6 {
#define int unsigned int

  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x3379) {
    return (x3379._1)-1;
  }
#undef int

  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x3376, const struct SEntry9_ISSSSSSDD& x3377) {
    return 0;
  }
};

struct SEntry11_IISSSSSSDDI_Idx2f1t6_1f1t11 {
#define int unsigned int

  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x3535) {
    return (x3535._2-1) * 10 + x3535._1-1;
  }
#undef int

  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x3532, const struct SEntry11_IISSSSSSDDI& x3533) {
    return 0;
  }
};

struct SEntry5_IISDS_Idx1f1t100002 {
#define int unsigned int

  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x3398) {
    return (x3398._1)-1;
  }
#undef int

  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x3395, const struct SEntry5_IISDS& x3396) {
    return 0;
  }
};

struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx3f1t6_2f1t11_1f1t3001 {
#define int unsigned int

  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3693) {
    return ((x3693._3-1) * 10 + x3693._2-1)*3000 + x3693._1-1;
  }
#undef int

  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3690, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3691) {
    return 0;
  }
};

struct SEntry17_IIISSSSSSSSSSIIIS_Idx2f1t6_1f1t100001 {
#define int unsigned int

  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3781) {
    return (x3781._2-1)* 100000 + x3781._1-1;
  }
#undef int

  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3778, const struct SEntry17_IIISSSSSSSSSSIIIS& x3779) {
    return 0;
  }
};

struct SEntry3_III_Idx23_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x3168)  {
    int x1 = x3168._3;
    int x2 = (x1 << 4) + x3168._2;
    return x2;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry3_III& x3251, const struct SEntry3_III& x3252) {
    int x3253 = x3251._1;
    int x3254 = x3252._1;
    return ((x3253==(x3254)) ? 0 : ((x3253>(x3254)) ? 1 : -1));
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236_4 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3765)  {
    int x1 = HASH(x3765._6);
    int x2 = (x1 << 2) + x3765._3;
    int x3 = (x2 << 4) + x3765._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3944, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3945) {
    int x3948 = strcmpi((x3944._4).data_, (x3945._4).data_);
    return ((x3948>(0)) ? 1 : ((x3948<(0)) ? -1 : 0));
  }
};
 struct SEntry8_IIIITIIB_Idx234_1 {
  #define int unsigned int
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x3468)  {
    int x1 = x3468._4;
    int x2 = (x1 << 2) + x3468._3;
    int x3 = (x2 << 4) + x3468._2;
    return x3;
  }
  #undef int
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x3599, const struct SEntry8_IIIITIIB& x3600) {
    int x3601 = x3599._1;
    int x3602 = x3600._1;
    return ((x3601==(x3602)) ? 0 : ((x3601>(x3602)) ? 1 : -1));
  }
};
#endif

      
typedef CuckooIndex<GenericEntry, GenericOps_321> newOrderTblIdx0Type;
typedef MinHeapIndex<GenericEntry, GenericOps_23, GenericCmp_23_1> newOrderTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,newOrderTblIdx0Type, newOrderTblIdx1Type> newOrderTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_12345678> historyTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,historyTblIdx0Type> historyTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_1f1t6, 5> warehouseTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,warehouseTblIdx0Type> warehouseTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_1f1t100002, 100001> itemTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,itemTblIdx0Type> itemTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_321> orderTblIdx0Type;
typedef MaxHeapIndex<GenericEntry, GenericOps_234, GenericCmp_234_1> orderTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,orderTblIdx0Type, orderTblIdx1Type> orderTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_2f1t6_1f1t11, 50> districtTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,districtTblIdx0Type> districtTblStoreType;

typedef CuckooIndex<GenericEntry, GenericOps_3214> orderLineTblIdx0Type;
typedef ConcurrentCuckooSecondaryIndex<GenericEntry, GenericOps_123> orderLineTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,orderLineTblIdx0Type, orderLineTblIdx1Type> orderLineTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_3f1t6_2f1t11_1f1t3001, 150000> customerTblIdx0Type;
typedef MedHeapIndex<GenericEntry, GenericOps_236, GenericCmp_236_4> customerTblIdx1Type;
typedef MultiHashMapMV<GenericEntry,customerTblIdx0Type, customerTblIdx1Type> customerTblStoreType;

typedef ConcurrentArrayIndex<GenericEntry, GenericFixedRange_2f1t6_1f1t100001, 500000> stockTblIdx0Type;
typedef MultiHashMapMV<GenericEntry,stockTblIdx0Type> stockTblStoreType;

struct TPCC_Data {
  TPCC_Data(): 
  newOrderTbl(), newOrderTblIdx0(*(newOrderTblIdx0Type *)newOrderTbl.index[0]), newOrderTblIdx1(*(newOrderTblIdx1Type *)newOrderTbl.index[1]), 
  historyTbl(), historyTblIdx0(*(historyTblIdx0Type *)historyTbl.index[0]), 
  warehouseTbl(), warehouseTblIdx0(*(warehouseTblIdx0Type *)warehouseTbl.index[0]), 
  itemTbl(), itemTblIdx0(*(itemTblIdx0Type *)itemTbl.index[0]), 
  orderTbl(), orderTblIdx0(*(orderTblIdx0Type *)orderTbl.index[0]), orderTblIdx1(*(orderTblIdx1Type *)orderTbl.index[1]), 
  districtTbl(), districtTblIdx0(*(districtTblIdx0Type *)districtTbl.index[0]), 
  orderLineTbl(), orderLineTblIdx0(*(orderLineTblIdx0Type *)orderLineTbl.index[0]), orderLineTblIdx1(*(orderLineTblIdx1Type *)orderLineTbl.index[1]), 
  customerTbl(), customerTblIdx0(*(customerTblIdx0Type *)customerTbl.index[0]), customerTblIdx1(*(customerTblIdx1Type *)customerTbl.index[1]), 
  stockTbl(), stockTblIdx0(*(stockTblIdx0Type *)stockTbl.index[0]){}
  
  newOrderTblStoreType  newOrderTbl;  newOrderTblIdx0Type& newOrderTblIdx0;  newOrderTblIdx1Type& newOrderTblIdx1;
  historyTblStoreType  historyTbl;  historyTblIdx0Type& historyTblIdx0;
  warehouseTblStoreType  warehouseTbl;  warehouseTblIdx0Type& warehouseTblIdx0;
  itemTblStoreType  itemTbl;  itemTblIdx0Type& itemTblIdx0;
  orderTblStoreType  orderTbl;  orderTblIdx0Type& orderTblIdx0;  orderTblIdx1Type& orderTblIdx1;
  districtTblStoreType  districtTbl;  districtTblIdx0Type& districtTblIdx0;
  orderLineTblStoreType  orderLineTbl;  orderLineTblIdx0Type& orderLineTblIdx0;  orderLineTblIdx1Type& orderLineTblIdx1;
  customerTblStoreType  customerTbl;  customerTblIdx0Type& customerTblIdx0;  customerTblIdx1Type& customerTblIdx1;
  stockTblStoreType  stockTbl;  stockTblIdx0Type& stockTblIdx0;
};
struct ThreadLocal { 
  
  uint8_t threadId;
  uint xactCounts[5];
  
  ThreadLocal(uint8_t tid, TPCC_Data& t): threadId(tid), 
  newOrderTbl(t.newOrderTbl), newOrderTblIdx0(t.newOrderTblIdx0), newOrderTblIdx1(t.newOrderTblIdx1), 
  historyTbl(t.historyTbl), historyTblIdx0(t.historyTblIdx0), 
  warehouseTbl(t.warehouseTbl), warehouseTblIdx0(t.warehouseTblIdx0), 
  itemTbl(t.itemTbl), itemTblIdx0(t.itemTblIdx0), 
  orderTbl(t.orderTbl), orderTblIdx0(t.orderTblIdx0), orderTblIdx1(t.orderTblIdx1), 
  districtTbl(t.districtTbl), districtTblIdx0(t.districtTblIdx0), 
  orderLineTbl(t.orderLineTbl), orderLineTblIdx0(t.orderLineTblIdx0), orderLineTblIdx1(t.orderLineTblIdx1), 
  customerTbl(t.customerTbl), customerTblIdx0(t.customerTblIdx0), customerTblIdx1(t.customerTblIdx1), 
  stockTbl(t.stockTbl), stockTblIdx0(t.stockTblIdx0){
     memset(xactCounts, 0, sizeof(uint)*5);
  }
  
  newOrderTblStoreType& newOrderTbl;  newOrderTblIdx0Type& newOrderTblIdx0;  newOrderTblIdx1Type& newOrderTblIdx1;
  historyTblStoreType& historyTbl;  historyTblIdx0Type& historyTblIdx0;
  warehouseTblStoreType& warehouseTbl;  warehouseTblIdx0Type& warehouseTblIdx0;
  itemTblStoreType& itemTbl;  itemTblIdx0Type& itemTblIdx0;
  orderTblStoreType& orderTbl;  orderTblIdx0Type& orderTblIdx0;  orderTblIdx1Type& orderTblIdx1;
  districtTblStoreType& districtTbl;  districtTblIdx0Type& districtTblIdx0;
  orderLineTblStoreType& orderLineTbl;  orderLineTblIdx0Type& orderLineTblIdx0;  orderLineTblIdx1Type& orderLineTblIdx1;
  customerTblStoreType& customerTbl;  customerTblIdx0Type& customerTblIdx0;  customerTblIdx1Type& customerTblIdx1;
  stockTblStoreType& stockTbl;  stockTblIdx0Type& stockTblIdx0;
  
  
  
  FORCE_INLINE TransactionReturnStatus PaymentTx(Transaction& xact, int x16, date x17, int x18, int x19, int x20, int x21, int x22, int x23, int x24, PString x25, double x26) {
    GenericEntry y29(true_type(), 1, x19); GenericEntry* x29 = &y29;
    OperationReturnStatus stx4310;
    GenericEntry* x4310 =  warehouseTblIdx0.getForUpdate(x29, stx4310, xact);
    if(stx4310 == WW_VALUE) return WW_ABORT;
    x4310->increase(9, x26);
    warehouseTblIdx0.update(x4310);
    GenericEntry y35(true_type(), 1, x20, 2, x19); GenericEntry* x35 = &y35;
    OperationReturnStatus stx4315;
    GenericEntry* x4315 =  districtTblIdx0.getForUpdate(x35, stx4315, xact);
    if(stx4315 == WW_VALUE) return WW_ABORT;
    x4315->increase(10, x26);
    districtTblIdx0.update(x4315);
    GenericEntry* ite7882 = 0;
    if((x21>(0))) {
      GenericEntry y7884(true_type(), 2, x23, 3, x22, 6, x25); GenericEntry* x7884 = &y7884;
      OperationReturnStatus stx7885;
      GenericEntry* x7885 =  customerTblIdx1.getForUpdate(x7884, stx7885, xact);
      if(stx7885 == WW_VALUE) return WW_ABORT;
      ite7882 = x7885;
    } else {
      GenericEntry y7888(true_type(), 1, x24, 2, x23, 3, x22); GenericEntry* x7888 = &y7888;
      OperationReturnStatus stx7889;
      GenericEntry* x7889 =  customerTblIdx0.getForUpdate(x7888, stx7889, xact);
      if(stx7889 == WW_VALUE) return WW_ABORT;
      ite7882 = x7889;
    };
    GenericEntry* customerEntry = ite7882;
    const PString& c_data = customerEntry->getString(21);
    const PString& x56 = customerEntry->getString(14);
    char* x8972 = strstr(x56.data_, "BC");
    if((x8972!=(NULL))) {
      int x59 = customerEntry->getInt(1);
      PString x2479 = PString(500);
      x2479.append(x59);
      x2479.append(' ');
      x2479.append(x23);
      x2479.append(' ');
      x2479.append(x22);
      x2479.append(' ');
      x2479.append(x20);
      x2479.append(' ');
      x2479.append(x19);
      x2479.append(' ');
      x2479.append('$');
      x2479.append(x26);
      x2479.append(' ');
      x2479.appendDate(x17);
      x2479.append(' ');
      x2479.append('|');
      x2479.append(' ');
      x2479.append(c_data.data_, 500);
      customerEntry->increase(17, x26);
      customerEntry->update(21, x2479);
    } else {
      customerEntry->increase(17, x26);
    };
    customerTblIdx1.update(customerEntry);
    customerTblIdx0.update(customerEntry);
    const PString& w_name = x4310->getString(2);
    const PString& d_name = x4315->getString(3);
    PString x2505 = PString(24);
    x2505.append(w_name.data_, 10);
    x2505.append("    ", 4);
    x2505.append(d_name.data_, 10);
    int x74 = customerEntry->getInt(1);
    GenericEntry y76(false_type(), x74, x23, x22, x20, x19, x17, x26, x2505); GenericEntry* x76 = &y76;
    OperationReturnStatus st6894 = historyTbl.insert_nocheck(x76, xact);
    if(st6894 == WW_VALUE) return WW_ABORT;
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus NewOrderTx(Transaction& xact, int x78, date x79, int x80, int x81, int x82, int x83, int x84, int x85, int* x86, int* x87, int* x88, double* x89, PString* x90, int* x91, PString* x92, double* x93) {
    int x95 = 0;
    int x98 = 0;
    PString idata[x84];
    int x103 = 1;
    int x106 = 1;
    while(1) {
      
      int x108 = x95;
      int ite8123 = 0;
      if((x108<(x84))) {
        
        int x110 = x103;
        int x8124 = x110;
        ite8123 = x8124;
      } else {
        ite8123 = 0;
      };
      int x8001 = ite8123;
      if (!(x8001)) break; 
      
      int x113 = x95;
      int supwid = x87[x113];
      if((supwid!=(x81))) {
        x106 = 0;
      };
      int x119 = x95;
      int x120 = x86[x119];
      GenericEntry y122(true_type(), 1, x120); GenericEntry* x122 = &y122;
      GenericEntry* x3769 = itemTblIdx0.get(x122, xact);
      if((x3769==(NULL))) {
        x103 = 0;
      } else {
        int x126 = x95;
        const PString& x127 = x3769->getString(3);
        x90[x126] = x127;
        int x129 = x95;
        double x130 = x3769->getDouble(4);
        x89[x129] = x130;
        int x132 = x95;
        const PString& x133 = x3769->getString(5);
        idata[x132] = x133;
      };
      int x136 = x95;
      x95 = (x136+(1));
    };
    int x140 = x103;
    if(x140) {
      GenericEntry y143(true_type(), 1, x83, 2, x82, 3, x81); GenericEntry* x143 = &y143;
      GenericEntry* x3789 = customerTblIdx0.get(x143, xact);
      GenericEntry y147(true_type(), 1, x81); GenericEntry* x147 = &y147;
      GenericEntry* x3792 = warehouseTblIdx0.get(x147, xact);
      GenericEntry y151(true_type(), 1, x82, 2, x81); GenericEntry* x151 = &y151;
      OperationReturnStatus stx4542;
      GenericEntry* x4542 =  districtTblIdx0.getForUpdate(x151, stx4542, xact);
      if(stx4542 == WW_VALUE) return WW_ABORT;
      int o_id = x4542->getInt(11);
      x4542->increase(11, 1);
      districtTblIdx0.update(x4542);
      int x157 = x106;
      GenericEntry y159(false_type(), o_id, x82, x81, x83, x79, -1, x84, x157); GenericEntry* x159 = &y159;
      OperationReturnStatus st6947 = orderTbl.insert_nocheck(x159, xact);
      if(st6947 == WW_VALUE) return WW_ABORT;
      GenericEntry y162(false_type(), o_id, x82, x81); GenericEntry* x162 = &y162;
      OperationReturnStatus st6950 = newOrderTbl.insert_nocheck(x162, xact);
      if(st6950 == WW_VALUE) return WW_ABORT;
      double x165 = 0.0;
      x95 = 0;
      while(1) {
        
        int x168 = x95;
        if (!((x168<(x84)))) break; 
        
        int x171 = x95;
        int ol_supply_w_id = x87[x171];
        int x174 = x95;
        int ol_i_id = x86[x174];
        int x177 = x95;
        int ol_quantity = x88[x177];
        GenericEntry y181(true_type(), 1, ol_i_id, 2, ol_supply_w_id); GenericEntry* x181 = &y181;
        OperationReturnStatus stx4566;
        GenericEntry* x4566 =  stockTblIdx0.getForUpdate(x181, stx4566, xact);
        if(stx4566 == WW_VALUE) return WW_ABORT;
        const PString& ol_dist_info = x4566->getString((3+(x82)));
        int s_quantity = x4566->getInt(3);
        int x188 = x95;
        x91[x188] = s_quantity;
        int x190 = x95;
        PString& x191 = idata[x190];
        char* x9154 = strstr(x191.data_, "original");
        int ite8198 = 0;
        if((x9154!=(NULL))) {
          
          const PString& x193 = x4566->getString(17);
          char* x9160 = strstr(x193.data_, "original");
          int x8199 = (x9160!=(NULL));
          ite8198 = x8199;
        } else {
          ite8198 = 0;
        };
        int x8071 = ite8198;
        if(x8071) {
          int x196 = x95;
          x92[x196].data_[0] = 'B';
        } else {
          int x198 = x95;
          x92[x198].data_[0] = 'G';
        };
        x4566->update(3, (s_quantity-(ol_quantity)));
        if((s_quantity<=(ol_quantity))) {
          x4566->increase(3, 91);
        };
        int x207 = 0;
        if((ol_supply_w_id!=(x81))) {
          x207 = 1;
        };
        stockTblIdx0.update(x4566);
        double c_discount = x3789->getDouble(16);
        double w_tax = x3792->getDouble(8);
        double d_tax = x4542->getDouble(9);
        int x220 = x95;
        double x221 = x89[x220];
        double ol_amount = ((ol_quantity*(x221))*(((1.0+(w_tax))+(d_tax))))*((1.0-(c_discount)));
        int x229 = x95;
        x93[x229] = ol_amount;
        double x231 = x165;
        x165 = (x231+(ol_amount));
        int x234 = x95;
        GenericEntry y237(false_type(), o_id, x82, x81, (x234+(1)), ol_i_id, ol_supply_w_id, NULL, ol_quantity, ol_amount, ol_dist_info); GenericEntry* x237 = &y237;
        OperationReturnStatus st7012 = orderLineTbl.insert_nocheck(x237, xact);
        if(st7012 == WW_VALUE) return WW_ABORT;
        int x239 = x95;
        x95 = (x239+(1));
      };
    } else {
      int x243 = failedNO;
      failedNO = (1+(x243));
    };
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus DeliveryTx(Transaction& xact, int x247, date x248, int x249, int x250) {
    int orderIDs[10];
    int x255 = 1;
    while(1) {
      
      int x257 = x255;
      if (!((x257<=(10)))) break; 
      
      int x264 = x255;
      GenericEntry y266(true_type(), 2, x264, 3, x249); GenericEntry* x266 = &y266;
      OperationReturnStatus stx4757;
      GenericEntry* x4757 =  newOrderTblIdx1.getForUpdate(x266, stx4757, xact);
      if(stx4757 == WW_VALUE) return WW_ABORT;
      if((x4757!=(NULL))) {
        int no_o_id = x4757->getInt(1);
        int x273 = x255;
        orderIDs[(x273-(1))] = no_o_id;
        newOrderTbl.del(x4757);
        int x278 = x255;
        GenericEntry y280(true_type(), 1, no_o_id, 2, x278, 3, x249); GenericEntry* x280 = &y280;
        OperationReturnStatus stx4768;
        GenericEntry* x4768 =  orderTblIdx0.getForUpdate(x280, stx4768, xact);
        if(stx4768 == WW_VALUE) return WW_ABORT;
        int c_id = x4768->getInt(4);
        x4768->update(6, x250);
        orderTblIdx0.update(x4768);
        orderTblIdx1.update(x4768);
        double x287 = 0.0;
        int x289 = x255;
        GenericEntry y291(true_type(), 1, no_o_id, 2, x289, 3, x249); GenericEntry* x291 = &y291;
        OperationReturnStatus st4039 = orderLineTblIdx1.slice(x291, [&](GenericEntry* orderLineEntry) -> TransactionReturnStatus {
          orderLineEntry->update(7, x248);
          double x294 = x287;
          double x295 = orderLineEntry->getDouble(9);
          x287 = (x294+(x295));
          orderLineTblIdx0.update(orderLineEntry);
          orderLineTblIdx1.update(orderLineEntry);
          return SUCCESS;
        }, xact);
        if(st4039 == WW_VALUE) return WW_ABORT;
        int x302 = x255;
        GenericEntry y304(true_type(), 1, c_id, 2, x302, 3, x249); GenericEntry* x304 = &y304;
        OperationReturnStatus stx4790;
        GenericEntry* x4790 =  customerTblIdx0.getForUpdate(x304, stx4790, xact);
        if(stx4790 == WW_VALUE) return WW_ABORT;
        double x306 = x287;
        x4790->increase(17, x306);
        x4790->increase(20, 1);
        customerTblIdx1.update(x4790);
        customerTblIdx0.update(x4790);
      } else {
        int x310 = failedDel;
        failedDel = (1+(x310));
        int x313 = x255;
        orderIDs[(x313-(1))] = 0;
      };
      int x317 = x255;
      x255 = (x317+(1));
    };
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus StockLevelTx(Transaction& xact, int x321, date x322, int x323, int x324, int x325, int x326) {
    GenericEntry y329(true_type(), 1, x325, 2, x324); GenericEntry* x329 = &y329;
    GenericEntry* x4120 = districtTblIdx0.get(x329, xact);
    int o_id = x4120->getInt(11);
    int x335 = (o_id-(20));
    unordered_set<int> unique_ol_i_id({}); //setApply1
    while(1) {
      
      int x340 = x335;
      if (!((x340<(o_id)))) break; 
      
      int x342 = x335;
      GenericEntry y344(true_type(), 1, x342, 2, x325, 3, x324); GenericEntry* x344 = &y344;
      OperationReturnStatus st5266 = orderLineTblIdx1.sliceNoUpdate(x344, [&](GenericEntry* orderLineEntry) -> TransactionReturnStatus {
        int ol_i_id = orderLineEntry->getInt(5);
        GenericEntry y350(true_type(), 1, ol_i_id, 2, x324); GenericEntry* x350 = &y350;
        GenericEntry* x4134 = stockTblIdx0.get(x350, xact);
        int s_quantity = x4134->getInt(3);
        if((s_quantity<(x326))) {
          unique_ol_i_id.insert(ol_i_id);
        };
        return SUCCESS;
      }, xact);
      if(st5266 == WW_VALUE) return WW_ABORT;
      int x359 = x335;
      x335 = (x359+(1));
    };
    clearTempMem();
    return SUCCESS;
  }
  
  FORCE_INLINE TransactionReturnStatus OrderStatusTx(Transaction& xact, int x365, date x366, int x367, int x368, int x369, int x370, int x371, PString x372) {
    GenericEntry* ite8466 = 0;
    if((x370>(0))) {
      GenericEntry y8468(true_type(), 2, x369, 3, x368, 6, x372); GenericEntry* x8468 = &y8468;
      GenericEntry* x8469 = customerTblIdx1.get(x8468, xact);
      ite8466 = x8469;
    } else {
      GenericEntry y8472(true_type(), 1, x371, 2, x369, 3, x368); GenericEntry* x8472 = &y8472;
      GenericEntry* x8473 = customerTblIdx0.get(x8472, xact);
      ite8466 = x8473;
    };
    GenericEntry* customerEntry = ite8466;
    int found_c_id = customerEntry->getInt(3);
    GenericEntry y396(true_type(), 2, x369, 3, x368, 4, found_c_id); GenericEntry* x396 = &y396;
    GenericEntry* x4193 = orderTblIdx1.get(x396, xact);
    int ite8482 = 0;
    if((x4193==(NULL))) {
      int x8483 = failedOS;
      failedOS = (1+(x8483));
      ite8482 = 0;
    } else {
      int x8487 = x4193->getInt(1);
      GenericEntry y8492(true_type(), 1, x8487, 2, x369, 3, x368); GenericEntry* x8492 = &y8492;
      OperationReturnStatus st8493 = orderLineTblIdx1.sliceNoUpdate(x8492, [&](GenericEntry* orderLineEntry) -> TransactionReturnStatus {
        int x410 = 1;
        return SUCCESS;
      }, xact);
      if(st8493 == WW_VALUE) return WW_ABORT;
      ite8482 = 1;
    };
    int x414 = ite8482;
    clearTempMem();
    return SUCCESS;
  }
  
   TransactionReturnStatus runProgram(Program* prg);
};

TransactionManager xactManager;
TransactionManager& Transaction::tm(xactManager);
uint xactCounts[5];
uint8_t prgId7to5[] = {0, 1, 1, 2, 2, 3, 4};

volatile bool isReady[numThreads];
volatile bool startExecution, hasFinished;


TPCC_Data orig;
#ifdef VERIFY_CONC
   TPCC_Data res;
#endif
 

#include "TPCC.h"

TPCCDataGen tpcc;

TransactionReturnStatus ThreadLocal::runProgram(Program* prg) {
  TransactionReturnStatus ret = SUCCESS;
  switch (prg->id) {
    case NEWORDER:
    {
      NewOrder& p = *(NewOrder *) prg;
      ret = NewOrderTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, p.c_id, p.o_ol_cnt, p.o_all_local, p.itemid, p.supware, p.quantity, p.price, p.iname, p.stock, p.bg, p.amt);
      break;
    }
    case PAYMENTBYID:
    {
      PaymentById& p = *(PaymentById *) prg;
      ret = PaymentTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, 0, p.c_w_id, p.c_d_id, p.c_id, nullptr, p.h_amount);
      break;
    }
    case PAYMENTBYNAME:
    {
      PaymentByName& p = *(PaymentByName *) prg;
      ret = PaymentTx(prg->xact, false, p.datetime, -1, p.w_id, p.d_id, 1, p.c_w_id, p.c_d_id, -1, p.c_last_input, p.h_amount);
      break;
    }
    case ORDERSTATUSBYID:
    {
      OrderStatusById &p = *(OrderStatusById *) prg;
      ret = OrderStatusTx(prg->xact, false, -1, -1, p.w_id, p.d_id, 0, p.c_id, nullptr);
      break;
    }
    case ORDERSTATUSBYNAME:
    {
      OrderStatusByName &p = *(OrderStatusByName *) prg;
      ret = OrderStatusTx(prg->xact, false, -1, -1, p.w_id, p.d_id, 1, -1, p.c_last);
      break;
    }
    case DELIVERY:
    {
      Delivery &p = *(Delivery *) prg;
      ret = DeliveryTx(prg->xact, false, p.datetime, p.w_id, p.o_carrier_id);
      break;
    }
    case STOCKLEVEL:
    {
      StockLevel &p = *(StockLevel *) prg;
      ret = StockLevelTx(prg->xact, false, -1, -1, p.w_id, p.d_id, p.threshold);
      break;
    }
    default: cerr << "UNKNOWN PROGRAM TYPE" << endl;

  }
  return ret;
}
      
std::atomic<uint> PC(0);
void threadFunction(uint8_t thread_id, TPCC_Data* data) {
    setAffinity(thread_id);
    //    setSched(SCHED_FIFO);

  ThreadLocal tl(thread_id, *data);
  isReady[thread_id] = true;
  uint pid = PC++;
  Program* p;
  TransactionReturnStatus st;
  while (!startExecution);
  const uint failedProgramSize = 32;
  Program * failedPrograms[failedProgramSize];
  uint head = 0, tail = 0;
  bool full = false;
  p = tpcc.programs[pid];
  while (!hasFinished) {

    xactManager.begin(p->xact, thread_id);

    st = tl.runProgram(p);

    if (st != SUCCESS) {
      xactManager.rollback(p->xact, thread_id);
      if (!full && p->xact.failedBecauseOf != nullptr) {
        failedPrograms[tail++] = p;
        if (tail == failedProgramSize)
          tail = 0;
        if (head == tail)
          full = true;
        pid = PC++;
        if (pid >= numPrograms)
          break;
        p = tpcc.programs[pid];
      }
    } else {
      if (xactManager.validateAndCommit(p->xact, thread_id)) {   //rollback happens inside function if it fails
        xactCounts[prgId7to5[p->id]]++;
        if (head != tail || full) {
          p = failedPrograms[head];
          if (p->xact.failedBecauseOf->commitTS != initCommitTS) {
            head++;
            full = false;
            if (head == failedProgramSize)
              head = 0;
            continue;
          }
        }
        pid = PC++;
        if(pid >= numPrograms)
          break;
        p = tpcc.programs[pid];
      }
    }
  }
  hasFinished = true;
}

       
/* TRAITS STARTING */


int main(int argc, char** argv) {
 /* TRAITS ENDING   */
  
  setAffinity(-1);
  #ifndef NORESIZE
  cout << "Index Resizing warning disabled" << endl;
  #endif
  
  cout  << "NumThreads = " << numThreads << endl;
  
  tpcc.loadPrograms();
  
  Transaction t0;
  xactManager.begin(t0, 0);
  tpcc.loadWare(t0);
  tpcc.loadDist(t0);
  tpcc.loadCust(t0);
  tpcc.loadItem(t0);
  tpcc.loadNewOrd(t0);
  tpcc.loadOrders(t0);
  tpcc.loadOrdLine(t0);
  tpcc.loadHist(t0);
  tpcc.loadStocks(t0);
  xactManager.commit(t0, 0);
  cout.imbue(std::locale(""));
  
  memset(xactCounts, 0, 5 * sizeof(uint));
  memset(xactManager.activeXactStartTS, 0xff, sizeof(xactManager.activeXactStartTS[0]) * numThreads);
  
  Timepoint startTime, endTime;
  std::thread workers[numThreads];
  
  for (uint8_t i = 0; i < numThreads; ++i) {
      workers[i] = std::thread(threadFunction, i, &orig);
  }
  bool all_ready = true;
  //check if all worker threads are ready. Execution can be started once all threads finish startup procedure
  while (true) {
      for (uint8_t i = 0; i < numThreads; ++i) {
          if (isReady[i] == false) {
              all_ready = false;
              break;
          }
      }
      if (all_ready) {
          startTime = Now;
          startExecution = true;
          break;
      }
      all_ready = true;
  }
  
  for (uint8_t i = 0; i < numThreads; ++i) {
      workers[i].join();
  }
  endTime = Now;
  auto execTime = DurationMS(endTime - startTime);
  
  cout << "Failed NO = " << failedNO << endl;
  cout << "Failed Del = " << failedDel << endl;
  cout << "Failed OS = " << failedOS << endl;
  cout << "Total time = " << execTime << " ms" << endl;
  cout << "Total transactions = " << numPrograms << "   NewOrder = " <<  xactCounts[0]  << endl;
  cout << "TpmC = " << fixed <<  (xactCounts[0])* 60000.0/execTime << endl;
  
  ofstream fout("tpcc_res_cpp.csv", ios::app);
  if(argc == 1 || atoi(argv[1]) == 1) {
    fout << "\nCPP-ABFGILNORXY-" << numPrograms << ",";
    for(int i = 0; i < 5 ; ++i)
       fout << xactCounts[i] << ",";
    fout <<",";
   }
  fout << execTime << ",";
  fout.close();
  
  /*
  ofstream info("/home/sachin/Data/EPFL/Sem4/DDBToaster/ddbtoaster/../runtime/stats/default.json");
  info << "{\n";
  GET_RUN_STAT(orig.newOrderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.newOrderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.itemTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.customerTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.customerTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.historyTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderLineTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.orderLineTblIdx1, info);
  info <<",\n";
  GET_RUN_STAT(orig.stockTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.districtTblIdx0, info);
  info <<",\n";
  GET_RUN_STAT(orig.warehouseTblIdx0, info);
  info << "\n}\n";
  info.close();
  */
  
  #ifdef VERIFY_CONC
  ThreadLocal ver(-1, res);
  std::sort(tpcc.programs, tpcc.programs + numPrograms, [](const Program* a, const Program * b) {
    return a->xact.commitTS < b->xact.commitTS;
  });
  xactManager.committedXactsTail = nullptr;
  for (uint i = 0; i < numPrograms; ++i) {
    Program* p = tpcc.programs[i];
    if (p->xact.commitTS == initCommitTS)
      break;
    p->xact.reset();
    TransactionReturnStatus st;
    xactManager.begin(p->xact, 0);
    st = ver.runProgram(p);
    assert(st == SUCCESS);
    bool st2 = xactManager.validateAndCommit(p->xact, 0);
    assert(st2);
  }
  
  if (orig.warehouseTblIdx0 == res.warehouseTblIdx0) {
    cout << "Warehouse results are same as serial version" << endl;
  } else {
    cerr << "Warehouse results INCORRECT!" << endl;
  }
  if (orig.districtTblIdx0 == res.districtTblIdx0) {
    cout << "District results are same as serial version" << endl;
  } else {
    cerr << "District results INCORRECT!" << endl;
  }
  if (orig.customerTblIdx0 == res.customerTblIdx0) {
    cout << "Customer results are same as serial version" << endl;
  } else {
    cerr << "Customer results INCORRECT!" << endl;
  }
  if (orig.orderTblIdx0 == res.orderTblIdx0) {
    cout << "Order results are same as serial version" << endl;
  } else {
    cerr << "Order results INCORRECT!" << endl;
  }
  if (orig.orderLineTblIdx0 == res.orderLineTblIdx0) {
    cout << "OrderLine results are same as serial version" << endl;
  } else {
    cerr << "OrderLine results INCORRECT!" << endl;
  }
  if (orig.newOrderTblIdx0 == res.newOrderTblIdx0) {
    cout << "NewOrder results are same as serial version" << endl;
  } else {
    cerr << "NewOrder results INCORRECT!" << endl;
  }
  if (orig.itemTblIdx0 == res.itemTblIdx0) {
    cout << "Item results are same as serial version" << endl;
  } else {
    cerr << "Item results INCORRECT!" << endl;
  }
  if (orig.stockTblIdx0 == res.stockTblIdx0) {
    cout << "Stock results are same as serial version" << endl;
  } else {
    cerr << "Stock results INCORRECT!" << endl;
  }
  if (orig.historyTblIdx0 == res.historyTblIdx0) {
    cout << "History results are same as serial version" << endl;
  } else {
    cerr << "History results INCORRECT!" << endl;
  }
  #endif
  #ifdef VERIFY_TPCC
  /*
      warehouseTblIdx0.resize_(warehouseTblSize); tpcc.wareRes.resize_(warehouseTblSize);
      districtTblIdx0.resize_(districtTblSize); tpcc.distRes.resize_(districtTblSize);
      customerTblIdx0.resize_(customerTblSize); tpcc.custRes.resize_(customerTblSize);
      orderTblIdx0.resize_(orderTblSize); tpcc.ordRes.resize_(orderTblSize);
      newOrderTblIdx0.resize_(newOrderTblSize); tpcc.newOrdRes.resize_(newOrderTblSize);
      orderLineTblIdx0.resize_(orderLineTblSize); tpcc.ordLRes.resize_(orderLineTblSize);
      itemTblIdx0.resize_(itemTblSize); tpcc.itemRes.resize_(itemTblSize);
      stockTblIdx0.resize_(stockTblSize); tpcc.stockRes.resize_(stockTblSize);
      historyTblIdx0.resize_(historyTblSize); tpcc.histRes.resize_(historyTblSize);
  */
      if (orig.warehouseTblIdx0 == tpcc.wareRes) {
          cout << "Warehouse results are correct" << endl;
      } else {
          cerr << "Warehouse results INCORRECT!" << endl;
      }
      if (orig.districtTblIdx0 == tpcc.distRes) {
          cout << "District results are correct" << endl;
      } else {
          cerr << "District results INCORRECT!" << endl;
      }
      if (orig.customerTblIdx0 == tpcc.custRes) {
          cout << "Customer results are correct" << endl;
      } else {
          cerr << "Customer results INCORRECT!" << endl;
      }
      if (orig.orderTblIdx0 == tpcc.ordRes) {
          cout << "Order results are correct" << endl;
      } else {
          cerr << "Order results INCORRECT!" << endl;
      }
      if (orig.orderLineTblIdx0 == tpcc.ordLRes) {
          cout << "OrderLine results are correct" << endl;
      } else {
          cerr << "OrderLine results INCORRECT!" << endl;
      }
      if (orig.newOrderTblIdx0 == tpcc.newOrdRes) {
          cout << "NewOrder results are correct" << endl;
      } else {
          cerr << "NewOrder results INCORRECT!" << endl;
      }
      if (orig.itemTblIdx0 == tpcc.itemRes) {
          cout << "Item results are correct" << endl;
      } else {
          cerr << "Item results INCORRECT!" << endl;
      }
      if (orig.stockTblIdx0 == tpcc.stockRes) {
          cout << "Stock results are correct" << endl;
      } else {
          cerr << "Stock results INCORRECT!" << endl;
      }
      if (orig.historyTblIdx0 == tpcc.histRes) {
          cout << "History results are correct" << endl;
      } else {
          cerr << "History results INCORRECT!" << endl;
      }
  
  #endif
  
        
}
