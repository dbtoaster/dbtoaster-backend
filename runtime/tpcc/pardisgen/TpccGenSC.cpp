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
  SEntry5_IISDS* copy() { return new SEntry5_IISDS(_1, _2, *_3.copy(), _4, *_5.copy()); }
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  SEntry11_IISSSSSSDDI *prv;  SEntry11_IISSSSSSDDI *nxt; void* backPtrs[11];
  SEntry11_IISSSSSSDDI() :_1(-2147483648), _2(-2147483648), _3(), _4(), _5(), _6(), _7(), _8(), _9(-1.7976931348623157E308), _10(-1.7976931348623157E308), _11(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI(const int& _1, const int& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const double& _9, const double& _10, const int& _11) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI* copy() { return new SEntry11_IISSSSSSDDI(_1, _2, *_3.copy(), *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), _9, _10, _11); }
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt; void* backPtrs[21];
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() { return new SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), _13, *_14.copy(), _15, _16, _17, _18, _19, _20, *_21.copy()); }
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt; void* backPtrs[8];
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB* copy() { return new SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8); }
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt; void* backPtrs[3];
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  SEntry3_III* copy() { return new SEntry3_III(_1, _2, _3); }
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt; void* backPtrs[8];
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS* copy() { return new SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, *_8.copy()); }
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt; void* backPtrs[17];
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS* copy() { return new SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), *_13.copy(), _14, _15, _16, *_17.copy()); }
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt; void* backPtrs[10];
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS* copy() { return new SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, *_10.copy()); }
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  SEntry9_ISSSSSSDD *prv;  SEntry9_ISSSSSSDD *nxt; void* backPtrs[9];
  SEntry9_ISSSSSSDD() :_1(-2147483648), _2(), _3(), _4(), _5(), _6(), _7(), _8(-1.7976931348623157E308), _9(-1.7976931348623157E308), prv(nullptr), nxt(nullptr) {}
  SEntry9_ISSSSSSDD(const int& _1, const PString& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const double& _8, const double& _9) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), prv(nullptr), nxt(nullptr) {}
  SEntry9_ISSSSSSDD* copy() { return new SEntry9_ISSSSSSDD(_1, *_2.copy(), *_3.copy(), *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), _8, _9); }
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
 struct SEntry8_IIIITIIB_Idx234 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x2644)  { 
    int x2645 = -889275714;
    int x2646 = x2644._2;
    int x2647 = HASH(x2646);
    int x2648 = -862048943*(x2647);
    int x2649 = x2648<<(15);
    int x2650 = x2648 >> (-15 & (8*sizeof(x2648)-1));
    int x2651 = x2649|(x2650);
    int x2652 = x2651*(461845907);
    int x2653 = x2645;
    int x2654 = x2652^(x2653);
    int x2655 = x2654<<(13);
    int x2656 = x2654 >> (-13 & (8*sizeof(x2654)-1));
    int x2657 = x2655|(x2656);
    int x2658 = x2657*(5);
    int x2659 = x2658+(-430675100);
    x2645 = x2659;
    int x2661 = x2644._3;
    int x2662 = HASH(x2661);
    int x2663 = -862048943*(x2662);
    int x2664 = x2663<<(15);
    int x2665 = x2663 >> (-15 & (8*sizeof(x2663)-1));
    int x2666 = x2664|(x2665);
    int x2667 = x2666*(461845907);
    int x2668 = x2645;
    int x2669 = x2667^(x2668);
    int x2670 = x2669<<(13);
    int x2671 = x2669 >> (-13 & (8*sizeof(x2669)-1));
    int x2672 = x2670|(x2671);
    int x2673 = x2672*(5);
    int x2674 = x2673+(-430675100);
    x2645 = x2674;
    int x2676 = x2644._4;
    int x2677 = HASH(x2676);
    int x2678 = -862048943*(x2677);
    int x2679 = x2678<<(15);
    int x2680 = x2678 >> (-15 & (8*sizeof(x2678)-1));
    int x2681 = x2679|(x2680);
    int x2682 = x2681*(461845907);
    int x2683 = x2645;
    int x2684 = x2682^(x2683);
    int x2685 = x2684<<(13);
    int x2686 = x2684 >> (-13 & (8*sizeof(x2684)-1));
    int x2687 = x2685|(x2686);
    int x2688 = x2687*(5);
    int x2689 = x2688+(-430675100);
    x2645 = x2689;
    int x2691 = x2645;
    int x2692 = x2691^(2);
    int x2693 = x2692 >> (16 & (8*sizeof(x2692)-1));
    int x2694 = x2692^(x2693);
    int x2695 = x2694*(-2048144789);
    int x2696 = x2695 >> (13 & (8*sizeof(x2695)-1));
    int x2697 = x2695^(x2696);
    int x2698 = x2697*(-1028477387);
    int x2699 = x2698 >> (16 & (8*sizeof(x2698)-1));
    int x2700 = x2698^(x2699);
    return x2700; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x2702, const struct SEntry8_IIIITIIB& x2703) { 
    int ite12991 = 0;
    if(1) {
      
      int x2704 = x2702._2;
      int x2705 = x2703._2;
      int x2706 = x2704==(x2705);
      int x12992 = x2706;
      ite12991 = x12992;
    } else {
      
      ite12991 = 0;
    };
    int x12984 = ite12991;
    int ite13000 = 0;
    if(x12984) {
      
      int x2708 = x2702._3;
      int x2709 = x2703._3;
      int x2710 = x2708==(x2709);
      int x13001 = x2710;
      ite13000 = x13001;
    } else {
      
      ite13000 = 0;
    };
    int x12986 = ite13000;
    int ite13009 = 0;
    if(x12986) {
      
      int x2712 = x2702._4;
      int x2713 = x2703._4;
      int x2714 = x2712==(x2713);
      int x13010 = x2714;
      ite13009 = x13010;
    } else {
      
      ite13009 = 0;
    };
    int x12988 = ite13009;
    int x2716 = x12988 ? 0 : 1;
    return x2716; 
  }
};
 struct SEntry3_III_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x2025)  { 
    int x2026 = -889275714;
    int x2027 = x2025._1;
    int x2028 = HASH(x2027);
    int x2029 = -862048943*(x2028);
    int x2030 = x2029<<(15);
    int x2031 = x2029 >> (-15 & (8*sizeof(x2029)-1));
    int x2032 = x2030|(x2031);
    int x2033 = x2032*(461845907);
    int x2034 = x2026;
    int x2035 = x2033^(x2034);
    int x2036 = x2035<<(13);
    int x2037 = x2035 >> (-13 & (8*sizeof(x2035)-1));
    int x2038 = x2036|(x2037);
    int x2039 = x2038*(5);
    int x2040 = x2039+(-430675100);
    x2026 = x2040;
    int x2042 = x2025._2;
    int x2043 = HASH(x2042);
    int x2044 = -862048943*(x2043);
    int x2045 = x2044<<(15);
    int x2046 = x2044 >> (-15 & (8*sizeof(x2044)-1));
    int x2047 = x2045|(x2046);
    int x2048 = x2047*(461845907);
    int x2049 = x2026;
    int x2050 = x2048^(x2049);
    int x2051 = x2050<<(13);
    int x2052 = x2050 >> (-13 & (8*sizeof(x2050)-1));
    int x2053 = x2051|(x2052);
    int x2054 = x2053*(5);
    int x2055 = x2054+(-430675100);
    x2026 = x2055;
    int x2057 = x2025._3;
    int x2058 = HASH(x2057);
    int x2059 = -862048943*(x2058);
    int x2060 = x2059<<(15);
    int x2061 = x2059 >> (-15 & (8*sizeof(x2059)-1));
    int x2062 = x2060|(x2061);
    int x2063 = x2062*(461845907);
    int x2064 = x2026;
    int x2065 = x2063^(x2064);
    int x2066 = x2065<<(13);
    int x2067 = x2065 >> (-13 & (8*sizeof(x2065)-1));
    int x2068 = x2066|(x2067);
    int x2069 = x2068*(5);
    int x2070 = x2069+(-430675100);
    x2026 = x2070;
    int x2072 = x2026;
    int x2073 = x2072^(2);
    int x2074 = x2073 >> (16 & (8*sizeof(x2073)-1));
    int x2075 = x2073^(x2074);
    int x2076 = x2075*(-2048144789);
    int x2077 = x2076 >> (13 & (8*sizeof(x2076)-1));
    int x2078 = x2076^(x2077);
    int x2079 = x2078*(-1028477387);
    int x2080 = x2079 >> (16 & (8*sizeof(x2079)-1));
    int x2081 = x2079^(x2080);
    return x2081; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x2083, const struct SEntry3_III& x2084) { 
    int ite13110 = 0;
    if(1) {
      
      int x2085 = x2083._1;
      int x2086 = x2084._1;
      int x2087 = x2085==(x2086);
      int x13111 = x2087;
      ite13110 = x13111;
    } else {
      
      ite13110 = 0;
    };
    int x13103 = ite13110;
    int ite13119 = 0;
    if(x13103) {
      
      int x2089 = x2083._2;
      int x2090 = x2084._2;
      int x2091 = x2089==(x2090);
      int x13120 = x2091;
      ite13119 = x13120;
    } else {
      
      ite13119 = 0;
    };
    int x13105 = ite13119;
    int ite13128 = 0;
    if(x13105) {
      
      int x2093 = x2083._3;
      int x2094 = x2084._3;
      int x2095 = x2093==(x2094);
      int x13129 = x2095;
      ite13128 = x13129;
    } else {
      
      ite13128 = 0;
    };
    int x13107 = ite13128;
    int x2097 = x13107 ? 0 : 1;
    return x2097; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx1234 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x2787)  { 
    int x2788 = -889275714;
    int x2789 = x2787._1;
    int x2790 = HASH(x2789);
    int x2791 = -862048943*(x2790);
    int x2792 = x2791<<(15);
    int x2793 = x2791 >> (-15 & (8*sizeof(x2791)-1));
    int x2794 = x2792|(x2793);
    int x2795 = x2794*(461845907);
    int x2796 = x2788;
    int x2797 = x2795^(x2796);
    int x2798 = x2797<<(13);
    int x2799 = x2797 >> (-13 & (8*sizeof(x2797)-1));
    int x2800 = x2798|(x2799);
    int x2801 = x2800*(5);
    int x2802 = x2801+(-430675100);
    x2788 = x2802;
    int x2804 = x2787._2;
    int x2805 = HASH(x2804);
    int x2806 = -862048943*(x2805);
    int x2807 = x2806<<(15);
    int x2808 = x2806 >> (-15 & (8*sizeof(x2806)-1));
    int x2809 = x2807|(x2808);
    int x2810 = x2809*(461845907);
    int x2811 = x2788;
    int x2812 = x2810^(x2811);
    int x2813 = x2812<<(13);
    int x2814 = x2812 >> (-13 & (8*sizeof(x2812)-1));
    int x2815 = x2813|(x2814);
    int x2816 = x2815*(5);
    int x2817 = x2816+(-430675100);
    x2788 = x2817;
    int x2819 = x2787._3;
    int x2820 = HASH(x2819);
    int x2821 = -862048943*(x2820);
    int x2822 = x2821<<(15);
    int x2823 = x2821 >> (-15 & (8*sizeof(x2821)-1));
    int x2824 = x2822|(x2823);
    int x2825 = x2824*(461845907);
    int x2826 = x2788;
    int x2827 = x2825^(x2826);
    int x2828 = x2827<<(13);
    int x2829 = x2827 >> (-13 & (8*sizeof(x2827)-1));
    int x2830 = x2828|(x2829);
    int x2831 = x2830*(5);
    int x2832 = x2831+(-430675100);
    x2788 = x2832;
    int x2834 = x2787._4;
    int x2835 = HASH(x2834);
    int x2836 = -862048943*(x2835);
    int x2837 = x2836<<(15);
    int x2838 = x2836 >> (-15 & (8*sizeof(x2836)-1));
    int x2839 = x2837|(x2838);
    int x2840 = x2839*(461845907);
    int x2841 = x2788;
    int x2842 = x2840^(x2841);
    int x2843 = x2842<<(13);
    int x2844 = x2842 >> (-13 & (8*sizeof(x2842)-1));
    int x2845 = x2843|(x2844);
    int x2846 = x2845*(5);
    int x2847 = x2846+(-430675100);
    x2788 = x2847;
    int x2849 = x2788;
    int x2850 = x2849^(2);
    int x2851 = x2850 >> (16 & (8*sizeof(x2850)-1));
    int x2852 = x2850^(x2851);
    int x2853 = x2852*(-2048144789);
    int x2854 = x2853 >> (13 & (8*sizeof(x2853)-1));
    int x2855 = x2853^(x2854);
    int x2856 = x2855*(-1028477387);
    int x2857 = x2856 >> (16 & (8*sizeof(x2856)-1));
    int x2858 = x2856^(x2857);
    return x2858; 
  }
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x2860, const struct SEntry10_IIIIIITIDS& x2861) { 
    int ite13246 = 0;
    if(1) {
      
      int x2862 = x2860._1;
      int x2863 = x2861._1;
      int x2864 = x2862==(x2863);
      int x13247 = x2864;
      ite13246 = x13247;
    } else {
      
      ite13246 = 0;
    };
    int x13237 = ite13246;
    int ite13255 = 0;
    if(x13237) {
      
      int x2866 = x2860._2;
      int x2867 = x2861._2;
      int x2868 = x2866==(x2867);
      int x13256 = x2868;
      ite13255 = x13256;
    } else {
      
      ite13255 = 0;
    };
    int x13239 = ite13255;
    int ite13264 = 0;
    if(x13239) {
      
      int x2870 = x2860._3;
      int x2871 = x2861._3;
      int x2872 = x2870==(x2871);
      int x13265 = x2872;
      ite13264 = x13265;
    } else {
      
      ite13264 = 0;
    };
    int x13241 = ite13264;
    int ite13273 = 0;
    if(x13241) {
      
      int x2874 = x2860._4;
      int x2875 = x2861._4;
      int x2876 = x2874==(x2875);
      int x13274 = x2876;
      ite13273 = x13274;
    } else {
      
      ite13273 = 0;
    };
    int x13243 = ite13273;
    int x2878 = x13243 ? 0 : 1;
    return x2878; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x2962)  { 
    int x2963 = -889275714;
    int x2964 = x2962._1;
    int x2965 = HASH(x2964);
    int x2966 = -862048943*(x2965);
    int x2967 = x2966<<(15);
    int x2968 = x2966 >> (-15 & (8*sizeof(x2966)-1));
    int x2969 = x2967|(x2968);
    int x2970 = x2969*(461845907);
    int x2971 = x2963;
    int x2972 = x2970^(x2971);
    int x2973 = x2972<<(13);
    int x2974 = x2972 >> (-13 & (8*sizeof(x2972)-1));
    int x2975 = x2973|(x2974);
    int x2976 = x2975*(5);
    int x2977 = x2976+(-430675100);
    x2963 = x2977;
    int x2979 = x2962._2;
    int x2980 = HASH(x2979);
    int x2981 = -862048943*(x2980);
    int x2982 = x2981<<(15);
    int x2983 = x2981 >> (-15 & (8*sizeof(x2981)-1));
    int x2984 = x2982|(x2983);
    int x2985 = x2984*(461845907);
    int x2986 = x2963;
    int x2987 = x2985^(x2986);
    int x2988 = x2987<<(13);
    int x2989 = x2987 >> (-13 & (8*sizeof(x2987)-1));
    int x2990 = x2988|(x2989);
    int x2991 = x2990*(5);
    int x2992 = x2991+(-430675100);
    x2963 = x2992;
    int x2994 = x2962._3;
    int x2995 = HASH(x2994);
    int x2996 = -862048943*(x2995);
    int x2997 = x2996<<(15);
    int x2998 = x2996 >> (-15 & (8*sizeof(x2996)-1));
    int x2999 = x2997|(x2998);
    int x3000 = x2999*(461845907);
    int x3001 = x2963;
    int x3002 = x3000^(x3001);
    int x3003 = x3002<<(13);
    int x3004 = x3002 >> (-13 & (8*sizeof(x3002)-1));
    int x3005 = x3003|(x3004);
    int x3006 = x3005*(5);
    int x3007 = x3006+(-430675100);
    x2963 = x3007;
    int x3009 = x2963;
    int x3010 = x3009^(2);
    int x3011 = x3010 >> (16 & (8*sizeof(x3010)-1));
    int x3012 = x3010^(x3011);
    int x3013 = x3012*(-2048144789);
    int x3014 = x3013 >> (13 & (8*sizeof(x3013)-1));
    int x3015 = x3013^(x3014);
    int x3016 = x3015*(-1028477387);
    int x3017 = x3016 >> (16 & (8*sizeof(x3016)-1));
    int x3018 = x3016^(x3017);
    return x3018; 
  }
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3020, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3021) { 
    int ite13383 = 0;
    if(1) {
      
      int x3022 = x3020._1;
      int x3023 = x3021._1;
      int x3024 = x3022==(x3023);
      int x13384 = x3024;
      ite13383 = x13384;
    } else {
      
      ite13383 = 0;
    };
    int x13376 = ite13383;
    int ite13392 = 0;
    if(x13376) {
      
      int x3026 = x3020._2;
      int x3027 = x3021._2;
      int x3028 = x3026==(x3027);
      int x13393 = x3028;
      ite13392 = x13393;
    } else {
      
      ite13392 = 0;
    };
    int x13378 = ite13392;
    int ite13401 = 0;
    if(x13378) {
      
      int x3030 = x3020._3;
      int x3031 = x3021._3;
      int x3032 = x3030==(x3031);
      int x13402 = x3032;
      ite13401 = x13402;
    } else {
      
      ite13401 = 0;
    };
    int x13380 = ite13401;
    int x3034 = x13380 ? 0 : 1;
    return x3034; 
  }
};
 struct SEntry3_III_Idx23 {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x2153)  { 
    int x2154 = -889275714;
    int x2155 = x2153._2;
    int x2156 = HASH(x2155);
    int x2157 = -862048943*(x2156);
    int x2158 = x2157<<(15);
    int x2159 = x2157 >> (-15 & (8*sizeof(x2157)-1));
    int x2160 = x2158|(x2159);
    int x2161 = x2160*(461845907);
    int x2162 = x2154;
    int x2163 = x2161^(x2162);
    int x2164 = x2163<<(13);
    int x2165 = x2163 >> (-13 & (8*sizeof(x2163)-1));
    int x2166 = x2164|(x2165);
    int x2167 = x2166*(5);
    int x2168 = x2167+(-430675100);
    x2154 = x2168;
    int x2170 = x2153._3;
    int x2171 = HASH(x2170);
    int x2172 = -862048943*(x2171);
    int x2173 = x2172<<(15);
    int x2174 = x2172 >> (-15 & (8*sizeof(x2172)-1));
    int x2175 = x2173|(x2174);
    int x2176 = x2175*(461845907);
    int x2177 = x2154;
    int x2178 = x2176^(x2177);
    int x2179 = x2178<<(13);
    int x2180 = x2178 >> (-13 & (8*sizeof(x2178)-1));
    int x2181 = x2179|(x2180);
    int x2182 = x2181*(5);
    int x2183 = x2182+(-430675100);
    x2154 = x2183;
    int x2185 = x2154;
    int x2186 = x2185^(2);
    int x2187 = x2186 >> (16 & (8*sizeof(x2186)-1));
    int x2188 = x2186^(x2187);
    int x2189 = x2188*(-2048144789);
    int x2190 = x2189 >> (13 & (8*sizeof(x2189)-1));
    int x2191 = x2189^(x2190);
    int x2192 = x2191*(-1028477387);
    int x2193 = x2192 >> (16 & (8*sizeof(x2192)-1));
    int x2194 = x2192^(x2193);
    return x2194; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x2196, const struct SEntry3_III& x2197) { 
    int ite13485 = 0;
    if(1) {
      
      int x2198 = x2196._2;
      int x2199 = x2197._2;
      int x2200 = x2198==(x2199);
      int x13486 = x2200;
      ite13485 = x13486;
    } else {
      
      ite13485 = 0;
    };
    int x13480 = ite13485;
    int ite13494 = 0;
    if(x13480) {
      
      int x2202 = x2196._3;
      int x2203 = x2197._3;
      int x2204 = x2202==(x2203);
      int x13495 = x2204;
      ite13494 = x13495;
    } else {
      
      ite13494 = 0;
    };
    int x13482 = ite13494;
    int x2206 = x13482 ? 0 : 1;
    return x2206; 
  }
};
 struct SEntry10_IIIIIITIDS_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry10_IIIIIITIDS& x2881)  { 
    int x2882 = -889275714;
    int x2883 = x2881._1;
    int x2884 = HASH(x2883);
    int x2885 = -862048943*(x2884);
    int x2886 = x2885<<(15);
    int x2887 = x2885 >> (-15 & (8*sizeof(x2885)-1));
    int x2888 = x2886|(x2887);
    int x2889 = x2888*(461845907);
    int x2890 = x2882;
    int x2891 = x2889^(x2890);
    int x2892 = x2891<<(13);
    int x2893 = x2891 >> (-13 & (8*sizeof(x2891)-1));
    int x2894 = x2892|(x2893);
    int x2895 = x2894*(5);
    int x2896 = x2895+(-430675100);
    x2882 = x2896;
    int x2898 = x2881._2;
    int x2899 = HASH(x2898);
    int x2900 = -862048943*(x2899);
    int x2901 = x2900<<(15);
    int x2902 = x2900 >> (-15 & (8*sizeof(x2900)-1));
    int x2903 = x2901|(x2902);
    int x2904 = x2903*(461845907);
    int x2905 = x2882;
    int x2906 = x2904^(x2905);
    int x2907 = x2906<<(13);
    int x2908 = x2906 >> (-13 & (8*sizeof(x2906)-1));
    int x2909 = x2907|(x2908);
    int x2910 = x2909*(5);
    int x2911 = x2910+(-430675100);
    x2882 = x2911;
    int x2913 = x2881._3;
    int x2914 = HASH(x2913);
    int x2915 = -862048943*(x2914);
    int x2916 = x2915<<(15);
    int x2917 = x2915 >> (-15 & (8*sizeof(x2915)-1));
    int x2918 = x2916|(x2917);
    int x2919 = x2918*(461845907);
    int x2920 = x2882;
    int x2921 = x2919^(x2920);
    int x2922 = x2921<<(13);
    int x2923 = x2921 >> (-13 & (8*sizeof(x2921)-1));
    int x2924 = x2922|(x2923);
    int x2925 = x2924*(5);
    int x2926 = x2925+(-430675100);
    x2882 = x2926;
    int x2928 = x2882;
    int x2929 = x2928^(2);
    int x2930 = x2929 >> (16 & (8*sizeof(x2929)-1));
    int x2931 = x2929^(x2930);
    int x2932 = x2931*(-2048144789);
    int x2933 = x2932 >> (13 & (8*sizeof(x2932)-1));
    int x2934 = x2932^(x2933);
    int x2935 = x2934*(-1028477387);
    int x2936 = x2935 >> (16 & (8*sizeof(x2935)-1));
    int x2937 = x2935^(x2936);
    return x2937; 
  }
  FORCE_INLINE static char cmp(const struct SEntry10_IIIIIITIDS& x2939, const struct SEntry10_IIIIIITIDS& x2940) { 
    int ite13586 = 0;
    if(1) {
      
      int x2941 = x2939._1;
      int x2942 = x2940._1;
      int x2943 = x2941==(x2942);
      int x13587 = x2943;
      ite13586 = x13587;
    } else {
      
      ite13586 = 0;
    };
    int x13579 = ite13586;
    int ite13595 = 0;
    if(x13579) {
      
      int x2945 = x2939._2;
      int x2946 = x2940._2;
      int x2947 = x2945==(x2946);
      int x13596 = x2947;
      ite13595 = x13596;
    } else {
      
      ite13595 = 0;
    };
    int x13581 = ite13595;
    int ite13604 = 0;
    if(x13581) {
      
      int x2949 = x2939._3;
      int x2950 = x2940._3;
      int x2951 = x2949==(x2950);
      int x13605 = x2951;
      ite13604 = x13605;
    } else {
      
      ite13604 = 0;
    };
    int x13583 = ite13604;
    int x2953 = x13583 ? 0 : 1;
    return x2953; 
  }
};
 struct SEntry17_IIISSSSSSSSSSIIIS_Idx12 {
  FORCE_INLINE static size_t hash(const struct SEntry17_IIISSSSSSSSSSIIIS& x3117)  { 
    int x3118 = -889275714;
    int x3119 = x3117._1;
    int x3120 = HASH(x3119);
    int x3121 = -862048943*(x3120);
    int x3122 = x3121<<(15);
    int x3123 = x3121 >> (-15 & (8*sizeof(x3121)-1));
    int x3124 = x3122|(x3123);
    int x3125 = x3124*(461845907);
    int x3126 = x3118;
    int x3127 = x3125^(x3126);
    int x3128 = x3127<<(13);
    int x3129 = x3127 >> (-13 & (8*sizeof(x3127)-1));
    int x3130 = x3128|(x3129);
    int x3131 = x3130*(5);
    int x3132 = x3131+(-430675100);
    x3118 = x3132;
    int x3134 = x3117._2;
    int x3135 = HASH(x3134);
    int x3136 = -862048943*(x3135);
    int x3137 = x3136<<(15);
    int x3138 = x3136 >> (-15 & (8*sizeof(x3136)-1));
    int x3139 = x3137|(x3138);
    int x3140 = x3139*(461845907);
    int x3141 = x3118;
    int x3142 = x3140^(x3141);
    int x3143 = x3142<<(13);
    int x3144 = x3142 >> (-13 & (8*sizeof(x3142)-1));
    int x3145 = x3143|(x3144);
    int x3146 = x3145*(5);
    int x3147 = x3146+(-430675100);
    x3118 = x3147;
    int x3149 = x3118;
    int x3150 = x3149^(2);
    int x3151 = x3150 >> (16 & (8*sizeof(x3150)-1));
    int x3152 = x3150^(x3151);
    int x3153 = x3152*(-2048144789);
    int x3154 = x3153 >> (13 & (8*sizeof(x3153)-1));
    int x3155 = x3153^(x3154);
    int x3156 = x3155*(-1028477387);
    int x3157 = x3156 >> (16 & (8*sizeof(x3156)-1));
    int x3158 = x3156^(x3157);
    return x3158; 
  }
  FORCE_INLINE static char cmp(const struct SEntry17_IIISSSSSSSSSSIIIS& x3160, const struct SEntry17_IIISSSSSSSSSSIIIS& x3161) { 
    int ite13688 = 0;
    if(1) {
      
      int x3162 = x3160._1;
      int x3163 = x3161._1;
      int x3164 = x3162==(x3163);
      int x13689 = x3164;
      ite13688 = x13689;
    } else {
      
      ite13688 = 0;
    };
    int x13683 = ite13688;
    int ite13697 = 0;
    if(x13683) {
      
      int x3166 = x3160._2;
      int x3167 = x3161._2;
      int x3168 = x3166==(x3167);
      int x13698 = x3168;
      ite13697 = x13698;
    } else {
      
      ite13697 = 0;
    };
    int x13685 = ite13697;
    int x3170 = x13685 ? 0 : 1;
    return x3170; 
  }
};
 struct SEntry8_IIIIITDS_Idx {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIIITDS& x2216)  { 
    int x2217 = -889275714;
    int x2218 = x2216._1;
    int x2219 = HASH(x2218);
    int x2220 = -862048943*(x2219);
    int x2221 = x2220<<(15);
    int x2222 = x2220 >> (-15 & (8*sizeof(x2220)-1));
    int x2223 = x2221|(x2222);
    int x2224 = x2223*(461845907);
    int x2225 = x2217;
    int x2226 = x2224^(x2225);
    int x2227 = x2226<<(13);
    int x2228 = x2226 >> (-13 & (8*sizeof(x2226)-1));
    int x2229 = x2227|(x2228);
    int x2230 = x2229*(5);
    int x2231 = x2230+(-430675100);
    x2217 = x2231;
    int x2233 = x2216._2;
    int x2234 = HASH(x2233);
    int x2235 = -862048943*(x2234);
    int x2236 = x2235<<(15);
    int x2237 = x2235 >> (-15 & (8*sizeof(x2235)-1));
    int x2238 = x2236|(x2237);
    int x2239 = x2238*(461845907);
    int x2240 = x2217;
    int x2241 = x2239^(x2240);
    int x2242 = x2241<<(13);
    int x2243 = x2241 >> (-13 & (8*sizeof(x2241)-1));
    int x2244 = x2242|(x2243);
    int x2245 = x2244*(5);
    int x2246 = x2245+(-430675100);
    x2217 = x2246;
    int x2248 = x2216._3;
    int x2249 = HASH(x2248);
    int x2250 = -862048943*(x2249);
    int x2251 = x2250<<(15);
    int x2252 = x2250 >> (-15 & (8*sizeof(x2250)-1));
    int x2253 = x2251|(x2252);
    int x2254 = x2253*(461845907);
    int x2255 = x2217;
    int x2256 = x2254^(x2255);
    int x2257 = x2256<<(13);
    int x2258 = x2256 >> (-13 & (8*sizeof(x2256)-1));
    int x2259 = x2257|(x2258);
    int x2260 = x2259*(5);
    int x2261 = x2260+(-430675100);
    x2217 = x2261;
    int x2263 = x2216._4;
    int x2264 = HASH(x2263);
    int x2265 = -862048943*(x2264);
    int x2266 = x2265<<(15);
    int x2267 = x2265 >> (-15 & (8*sizeof(x2265)-1));
    int x2268 = x2266|(x2267);
    int x2269 = x2268*(461845907);
    int x2270 = x2217;
    int x2271 = x2269^(x2270);
    int x2272 = x2271<<(13);
    int x2273 = x2271 >> (-13 & (8*sizeof(x2271)-1));
    int x2274 = x2272|(x2273);
    int x2275 = x2274*(5);
    int x2276 = x2275+(-430675100);
    x2217 = x2276;
    int x2278 = x2216._5;
    int x2279 = HASH(x2278);
    int x2280 = -862048943*(x2279);
    int x2281 = x2280<<(15);
    int x2282 = x2280 >> (-15 & (8*sizeof(x2280)-1));
    int x2283 = x2281|(x2282);
    int x2284 = x2283*(461845907);
    int x2285 = x2217;
    int x2286 = x2284^(x2285);
    int x2287 = x2286<<(13);
    int x2288 = x2286 >> (-13 & (8*sizeof(x2286)-1));
    int x2289 = x2287|(x2288);
    int x2290 = x2289*(5);
    int x2291 = x2290+(-430675100);
    x2217 = x2291;
    date x2293 = x2216._6;
    int x2294 = HASH(x2293);
    int x2295 = -862048943*(x2294);
    int x2296 = x2295<<(15);
    int x2297 = x2295 >> (-15 & (8*sizeof(x2295)-1));
    int x2298 = x2296|(x2297);
    int x2299 = x2298*(461845907);
    int x2300 = x2217;
    int x2301 = x2299^(x2300);
    int x2302 = x2301<<(13);
    int x2303 = x2301 >> (-13 & (8*sizeof(x2301)-1));
    int x2304 = x2302|(x2303);
    int x2305 = x2304*(5);
    int x2306 = x2305+(-430675100);
    x2217 = x2306;
    double x2308 = x2216._7;
    int x2309 = HASH(x2308);
    int x2310 = -862048943*(x2309);
    int x2311 = x2310<<(15);
    int x2312 = x2310 >> (-15 & (8*sizeof(x2310)-1));
    int x2313 = x2311|(x2312);
    int x2314 = x2313*(461845907);
    int x2315 = x2217;
    int x2316 = x2314^(x2315);
    int x2317 = x2316<<(13);
    int x2318 = x2316 >> (-13 & (8*sizeof(x2316)-1));
    int x2319 = x2317|(x2318);
    int x2320 = x2319*(5);
    int x2321 = x2320+(-430675100);
    x2217 = x2321;
    PString x2323 = x2216._8;
    int x2324 = HASH(x2323);
    int x2325 = -862048943*(x2324);
    int x2326 = x2325<<(15);
    int x2327 = x2325 >> (-15 & (8*sizeof(x2325)-1));
    int x2328 = x2326|(x2327);
    int x2329 = x2328*(461845907);
    int x2330 = x2217;
    int x2331 = x2329^(x2330);
    int x2332 = x2331<<(13);
    int x2333 = x2331 >> (-13 & (8*sizeof(x2331)-1));
    int x2334 = x2332|(x2333);
    int x2335 = x2334*(5);
    int x2336 = x2335+(-430675100);
    x2217 = x2336;
    int x2338 = x2217;
    int x2339 = x2338^(2);
    int x2340 = x2339 >> (16 & (8*sizeof(x2339)-1));
    int x2341 = x2339^(x2340);
    int x2342 = x2341*(-2048144789);
    int x2343 = x2342 >> (13 & (8*sizeof(x2342)-1));
    int x2344 = x2342^(x2343);
    int x2345 = x2344*(-1028477387);
    int x2346 = x2345 >> (16 & (8*sizeof(x2345)-1));
    int x2347 = x2345^(x2346);
    return x2347; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIIITDS& x2349, const struct SEntry8_IIIIITDS& x2350) { 
    int ite13872 = 0;
    if(1) {
      
      int x2351 = x2349._1;
      int x2352 = x2350._1;
      int x2353 = x2351==(-2147483648);
      int ite13970 = 0;
      if(x2353) {
        ite13970 = 1;
      } else {
        
        
        int x2354 = x2352==(-2147483648);
        int x13972 = x2354;
        ite13970 = x13972;
      };
      int x13878 = ite13970;
      int ite13977 = 0;
      if(x13878) {
        ite13977 = 1;
      } else {
        
        
        int x2356 = x2351==(x2352);
        int x13979 = x2356;
        ite13977 = x13979;
      };
      int x13880 = ite13977;
      int x13873 = x13880;
      ite13872 = x13873;
    } else {
      
      ite13872 = 0;
    };
    int x13857 = ite13872;
    int ite13885 = 0;
    if(x13857) {
      
      int x2359 = x2349._2;
      int x2360 = x2350._2;
      int x2361 = x2359==(-2147483648);
      int ite13993 = 0;
      if(x2361) {
        ite13993 = 1;
      } else {
        
        
        int x2362 = x2360==(-2147483648);
        int x13995 = x2362;
        ite13993 = x13995;
      };
      int x13891 = ite13993;
      int ite14000 = 0;
      if(x13891) {
        ite14000 = 1;
      } else {
        
        
        int x2364 = x2359==(x2360);
        int x14002 = x2364;
        ite14000 = x14002;
      };
      int x13893 = ite14000;
      int x13886 = x13893;
      ite13885 = x13886;
    } else {
      
      ite13885 = 0;
    };
    int x13859 = ite13885;
    int ite13898 = 0;
    if(x13859) {
      
      int x2367 = x2349._3;
      int x2368 = x2350._3;
      int x2369 = x2367==(-2147483648);
      int ite14016 = 0;
      if(x2369) {
        ite14016 = 1;
      } else {
        
        
        int x2370 = x2368==(-2147483648);
        int x14018 = x2370;
        ite14016 = x14018;
      };
      int x13904 = ite14016;
      int ite14023 = 0;
      if(x13904) {
        ite14023 = 1;
      } else {
        
        
        int x2372 = x2367==(x2368);
        int x14025 = x2372;
        ite14023 = x14025;
      };
      int x13906 = ite14023;
      int x13899 = x13906;
      ite13898 = x13899;
    } else {
      
      ite13898 = 0;
    };
    int x13861 = ite13898;
    int ite13911 = 0;
    if(x13861) {
      
      int x2375 = x2349._4;
      int x2376 = x2350._4;
      int x2377 = x2375==(-2147483648);
      int ite14039 = 0;
      if(x2377) {
        ite14039 = 1;
      } else {
        
        
        int x2378 = x2376==(-2147483648);
        int x14041 = x2378;
        ite14039 = x14041;
      };
      int x13917 = ite14039;
      int ite14046 = 0;
      if(x13917) {
        ite14046 = 1;
      } else {
        
        
        int x2380 = x2375==(x2376);
        int x14048 = x2380;
        ite14046 = x14048;
      };
      int x13919 = ite14046;
      int x13912 = x13919;
      ite13911 = x13912;
    } else {
      
      ite13911 = 0;
    };
    int x13863 = ite13911;
    int ite13924 = 0;
    if(x13863) {
      
      int x2383 = x2349._5;
      int x2384 = x2350._5;
      int x2385 = x2383==(-2147483648);
      int ite14062 = 0;
      if(x2385) {
        ite14062 = 1;
      } else {
        
        
        int x2386 = x2384==(-2147483648);
        int x14064 = x2386;
        ite14062 = x14064;
      };
      int x13930 = ite14062;
      int ite14069 = 0;
      if(x13930) {
        ite14069 = 1;
      } else {
        
        
        int x2388 = x2383==(x2384);
        int x14071 = x2388;
        ite14069 = x14071;
      };
      int x13932 = ite14069;
      int x13925 = x13932;
      ite13924 = x13925;
    } else {
      
      ite13924 = 0;
    };
    int x13865 = ite13924;
    int ite13937 = 0;
    if(x13865) {
      
      date x2391 = x2349._6;
      date x2392 = x2350._6;
      int x2393 = x2391==(0);
      int ite14085 = 0;
      if(x2393) {
        ite14085 = 1;
      } else {
        
        
        int x2394 = x2392==(0);
        int x14087 = x2394;
        ite14085 = x14087;
      };
      int x13943 = ite14085;
      int ite14092 = 0;
      if(x13943) {
        ite14092 = 1;
      } else {
        
        
        int x2396 = x2391==(x2392);
        int x14094 = x2396;
        ite14092 = x14094;
      };
      int x13945 = ite14092;
      int x13938 = x13945;
      ite13937 = x13938;
    } else {
      
      ite13937 = 0;
    };
    int x13867 = ite13937;
    int ite13950 = 0;
    if(x13867) {
      
      double x2399 = x2349._7;
      double x2400 = x2350._7;
      int x2401 = x2399==(-1.7976931348623157E308);
      int ite14108 = 0;
      if(x2401) {
        ite14108 = 1;
      } else {
        
        
        int x2402 = x2400==(-1.7976931348623157E308);
        int x14110 = x2402;
        ite14108 = x14110;
      };
      int x13956 = ite14108;
      int ite14115 = 0;
      if(x13956) {
        ite14115 = 1;
      } else {
        
        
        int x2404 = x2399==(x2400);
        int x14117 = x2404;
        ite14115 = x14117;
      };
      int x13958 = ite14115;
      int x13951 = x13958;
      ite13950 = x13951;
    } else {
      
      ite13950 = 0;
    };
    int x13869 = ite13950;
    int x2407 = x13869 ? 0 : 1;
    return x2407; 
  }
};
 struct SEntry5_IISDS_Idx1 {
  FORCE_INLINE static size_t hash(const struct SEntry5_IISDS& x2456)  { 
    int x2457 = -889275714;
    int x2458 = x2456._1;
    int x2459 = HASH(x2458);
    int x2460 = -862048943*(x2459);
    int x2461 = x2460<<(15);
    int x2462 = x2460 >> (-15 & (8*sizeof(x2460)-1));
    int x2463 = x2461|(x2462);
    int x2464 = x2463*(461845907);
    int x2465 = x2457;
    int x2466 = x2464^(x2465);
    int x2467 = x2466<<(13);
    int x2468 = x2466 >> (-13 & (8*sizeof(x2466)-1));
    int x2469 = x2467|(x2468);
    int x2470 = x2469*(5);
    int x2471 = x2470+(-430675100);
    x2457 = x2471;
    int x2473 = x2457;
    int x2474 = x2473^(2);
    int x2475 = x2474 >> (16 & (8*sizeof(x2474)-1));
    int x2476 = x2474^(x2475);
    int x2477 = x2476*(-2048144789);
    int x2478 = x2477 >> (13 & (8*sizeof(x2477)-1));
    int x2479 = x2477^(x2478);
    int x2480 = x2479*(-1028477387);
    int x2481 = x2480 >> (16 & (8*sizeof(x2480)-1));
    int x2482 = x2480^(x2481);
    return x2482; 
  }
  FORCE_INLINE static char cmp(const struct SEntry5_IISDS& x2484, const struct SEntry5_IISDS& x2485) { 
    int ite14317 = 0;
    if(1) {
      
      int x2486 = x2484._1;
      int x2487 = x2485._1;
      int x2488 = x2486==(x2487);
      int x14318 = x2488;
      ite14317 = x14318;
    } else {
      
      ite14317 = 0;
    };
    int x14314 = ite14317;
    int x2490 = x14314 ? 0 : 1;
    return x2490; 
  }
};
 struct SEntry11_IISSSSSSDDI_Idx12 {
  FORCE_INLINE static size_t hash(const struct SEntry11_IISSSSSSDDI& x2726)  { 
    int x2727 = -889275714;
    int x2728 = x2726._1;
    int x2729 = HASH(x2728);
    int x2730 = -862048943*(x2729);
    int x2731 = x2730<<(15);
    int x2732 = x2730 >> (-15 & (8*sizeof(x2730)-1));
    int x2733 = x2731|(x2732);
    int x2734 = x2733*(461845907);
    int x2735 = x2727;
    int x2736 = x2734^(x2735);
    int x2737 = x2736<<(13);
    int x2738 = x2736 >> (-13 & (8*sizeof(x2736)-1));
    int x2739 = x2737|(x2738);
    int x2740 = x2739*(5);
    int x2741 = x2740+(-430675100);
    x2727 = x2741;
    int x2743 = x2726._2;
    int x2744 = HASH(x2743);
    int x2745 = -862048943*(x2744);
    int x2746 = x2745<<(15);
    int x2747 = x2745 >> (-15 & (8*sizeof(x2745)-1));
    int x2748 = x2746|(x2747);
    int x2749 = x2748*(461845907);
    int x2750 = x2727;
    int x2751 = x2749^(x2750);
    int x2752 = x2751<<(13);
    int x2753 = x2751 >> (-13 & (8*sizeof(x2751)-1));
    int x2754 = x2752|(x2753);
    int x2755 = x2754*(5);
    int x2756 = x2755+(-430675100);
    x2727 = x2756;
    int x2758 = x2727;
    int x2759 = x2758^(2);
    int x2760 = x2759 >> (16 & (8*sizeof(x2759)-1));
    int x2761 = x2759^(x2760);
    int x2762 = x2761*(-2048144789);
    int x2763 = x2762 >> (13 & (8*sizeof(x2762)-1));
    int x2764 = x2762^(x2763);
    int x2765 = x2764*(-1028477387);
    int x2766 = x2765 >> (16 & (8*sizeof(x2765)-1));
    int x2767 = x2765^(x2766);
    return x2767; 
  }
  FORCE_INLINE static char cmp(const struct SEntry11_IISSSSSSDDI& x2769, const struct SEntry11_IISSSSSSDDI& x2770) { 
    int ite14383 = 0;
    if(1) {
      
      int x2771 = x2769._1;
      int x2772 = x2770._1;
      int x2773 = x2771==(x2772);
      int x14384 = x2773;
      ite14383 = x14384;
    } else {
      
      ite14383 = 0;
    };
    int x14378 = ite14383;
    int ite14392 = 0;
    if(x14378) {
      
      int x2775 = x2769._2;
      int x2776 = x2770._2;
      int x2777 = x2775==(x2776);
      int x14393 = x2777;
      ite14392 = x14393;
    } else {
      
      ite14392 = 0;
    };
    int x14380 = ite14392;
    int x2779 = x14380 ? 0 : 1;
    return x2779; 
  }
};
 struct SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236 {
  FORCE_INLINE static size_t hash(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3037)  { 
    int x3038 = -889275714;
    int x3039 = x3037._2;
    int x3040 = HASH(x3039);
    int x3041 = -862048943*(x3040);
    int x3042 = x3041<<(15);
    int x3043 = x3041 >> (-15 & (8*sizeof(x3041)-1));
    int x3044 = x3042|(x3043);
    int x3045 = x3044*(461845907);
    int x3046 = x3038;
    int x3047 = x3045^(x3046);
    int x3048 = x3047<<(13);
    int x3049 = x3047 >> (-13 & (8*sizeof(x3047)-1));
    int x3050 = x3048|(x3049);
    int x3051 = x3050*(5);
    int x3052 = x3051+(-430675100);
    x3038 = x3052;
    int x3054 = x3037._3;
    int x3055 = HASH(x3054);
    int x3056 = -862048943*(x3055);
    int x3057 = x3056<<(15);
    int x3058 = x3056 >> (-15 & (8*sizeof(x3056)-1));
    int x3059 = x3057|(x3058);
    int x3060 = x3059*(461845907);
    int x3061 = x3038;
    int x3062 = x3060^(x3061);
    int x3063 = x3062<<(13);
    int x3064 = x3062 >> (-13 & (8*sizeof(x3062)-1));
    int x3065 = x3063|(x3064);
    int x3066 = x3065*(5);
    int x3067 = x3066+(-430675100);
    x3038 = x3067;
    PString x3069 = x3037._6;
    int x3070 = HASH(x3069);
    int x3071 = -862048943*(x3070);
    int x3072 = x3071<<(15);
    int x3073 = x3071 >> (-15 & (8*sizeof(x3071)-1));
    int x3074 = x3072|(x3073);
    int x3075 = x3074*(461845907);
    int x3076 = x3038;
    int x3077 = x3075^(x3076);
    int x3078 = x3077<<(13);
    int x3079 = x3077 >> (-13 & (8*sizeof(x3077)-1));
    int x3080 = x3078|(x3079);
    int x3081 = x3080*(5);
    int x3082 = x3081+(-430675100);
    x3038 = x3082;
    int x3084 = x3038;
    int x3085 = x3084^(2);
    int x3086 = x3085 >> (16 & (8*sizeof(x3085)-1));
    int x3087 = x3085^(x3086);
    int x3088 = x3087*(-2048144789);
    int x3089 = x3088 >> (13 & (8*sizeof(x3088)-1));
    int x3090 = x3088^(x3089);
    int x3091 = x3090*(-1028477387);
    int x3092 = x3091 >> (16 & (8*sizeof(x3091)-1));
    int x3093 = x3091^(x3092);
    return x3093; 
  }
  FORCE_INLINE static char cmp(const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3095, const struct SEntry21_IIISSSSSSSSSTSDDDDIIS& x3096) { 
    int ite14484 = 0;
    if(1) {
      
      int x3097 = x3095._2;
      int x3098 = x3096._2;
      int x3099 = x3097==(x3098);
      int x14485 = x3099;
      ite14484 = x14485;
    } else {
      
      ite14484 = 0;
    };
    int x14477 = ite14484;
    int ite14493 = 0;
    if(x14477) {
      
      int x3101 = x3095._3;
      int x3102 = x3096._3;
      int x3103 = x3101==(x3102);
      int x14494 = x3103;
      ite14493 = x14494;
    } else {
      
      ite14493 = 0;
    };
    int x14479 = ite14493;
    int ite14502 = 0;
    if(x14479) {
      
      PString x3105 = x3095._6;
      PString x3106 = x3096._6;
      int x3107 = x3105==(x3106);
      int x14503 = x3107;
      ite14502 = x14503;
    } else {
      
      ite14502 = 0;
    };
    int x14481 = ite14502;
    int x3109 = x14481 ? 0 : 1;
    return x3109; 
  }
};
 struct SEntry9_ISSSSSSDD_Idx1 {
  FORCE_INLINE static size_t hash(const struct SEntry9_ISSSSSSDD& x2415)  { 
    int x2416 = -889275714;
    int x2417 = x2415._1;
    int x2418 = HASH(x2417);
    int x2419 = -862048943*(x2418);
    int x2420 = x2419<<(15);
    int x2421 = x2419 >> (-15 & (8*sizeof(x2419)-1));
    int x2422 = x2420|(x2421);
    int x2423 = x2422*(461845907);
    int x2424 = x2416;
    int x2425 = x2423^(x2424);
    int x2426 = x2425<<(13);
    int x2427 = x2425 >> (-13 & (8*sizeof(x2425)-1));
    int x2428 = x2426|(x2427);
    int x2429 = x2428*(5);
    int x2430 = x2429+(-430675100);
    x2416 = x2430;
    int x2432 = x2416;
    int x2433 = x2432^(2);
    int x2434 = x2433 >> (16 & (8*sizeof(x2433)-1));
    int x2435 = x2433^(x2434);
    int x2436 = x2435*(-2048144789);
    int x2437 = x2436 >> (13 & (8*sizeof(x2436)-1));
    int x2438 = x2436^(x2437);
    int x2439 = x2438*(-1028477387);
    int x2440 = x2439 >> (16 & (8*sizeof(x2439)-1));
    int x2441 = x2439^(x2440);
    return x2441; 
  }
  FORCE_INLINE static char cmp(const struct SEntry9_ISSSSSSDD& x2443, const struct SEntry9_ISSSSSSDD& x2444) { 
    int ite14569 = 0;
    if(1) {
      
      int x2445 = x2443._1;
      int x2446 = x2444._1;
      int x2447 = x2445==(x2446);
      int x14570 = x2447;
      ite14569 = x14570;
    } else {
      
      ite14569 = 0;
    };
    int x14566 = ite14569;
    int x2449 = x14566 ? 0 : 1;
    return x2449; 
  }
};
 struct SEntry8_IIIITIIB_Idx123 {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x2501)  { 
    int x2502 = -889275714;
    int x2503 = x2501._1;
    int x2504 = HASH(x2503);
    int x2505 = -862048943*(x2504);
    int x2506 = x2505<<(15);
    int x2507 = x2505 >> (-15 & (8*sizeof(x2505)-1));
    int x2508 = x2506|(x2507);
    int x2509 = x2508*(461845907);
    int x2510 = x2502;
    int x2511 = x2509^(x2510);
    int x2512 = x2511<<(13);
    int x2513 = x2511 >> (-13 & (8*sizeof(x2511)-1));
    int x2514 = x2512|(x2513);
    int x2515 = x2514*(5);
    int x2516 = x2515+(-430675100);
    x2502 = x2516;
    int x2518 = x2501._2;
    int x2519 = HASH(x2518);
    int x2520 = -862048943*(x2519);
    int x2521 = x2520<<(15);
    int x2522 = x2520 >> (-15 & (8*sizeof(x2520)-1));
    int x2523 = x2521|(x2522);
    int x2524 = x2523*(461845907);
    int x2525 = x2502;
    int x2526 = x2524^(x2525);
    int x2527 = x2526<<(13);
    int x2528 = x2526 >> (-13 & (8*sizeof(x2526)-1));
    int x2529 = x2527|(x2528);
    int x2530 = x2529*(5);
    int x2531 = x2530+(-430675100);
    x2502 = x2531;
    int x2533 = x2501._3;
    int x2534 = HASH(x2533);
    int x2535 = -862048943*(x2534);
    int x2536 = x2535<<(15);
    int x2537 = x2535 >> (-15 & (8*sizeof(x2535)-1));
    int x2538 = x2536|(x2537);
    int x2539 = x2538*(461845907);
    int x2540 = x2502;
    int x2541 = x2539^(x2540);
    int x2542 = x2541<<(13);
    int x2543 = x2541 >> (-13 & (8*sizeof(x2541)-1));
    int x2544 = x2542|(x2543);
    int x2545 = x2544*(5);
    int x2546 = x2545+(-430675100);
    x2502 = x2546;
    int x2548 = x2502;
    int x2549 = x2548^(2);
    int x2550 = x2549 >> (16 & (8*sizeof(x2549)-1));
    int x2551 = x2549^(x2550);
    int x2552 = x2551*(-2048144789);
    int x2553 = x2552 >> (13 & (8*sizeof(x2552)-1));
    int x2554 = x2552^(x2553);
    int x2555 = x2554*(-1028477387);
    int x2556 = x2555 >> (16 & (8*sizeof(x2555)-1));
    int x2557 = x2555^(x2556);
    return x2557; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x2559, const struct SEntry8_IIIITIIB& x2560) { 
    int ite14652 = 0;
    if(1) {
      
      int x2561 = x2559._1;
      int x2562 = x2560._1;
      int x2563 = x2561==(x2562);
      int x14653 = x2563;
      ite14652 = x14653;
    } else {
      
      ite14652 = 0;
    };
    int x14645 = ite14652;
    int ite14661 = 0;
    if(x14645) {
      
      int x2565 = x2559._2;
      int x2566 = x2560._2;
      int x2567 = x2565==(x2566);
      int x14662 = x2567;
      ite14661 = x14662;
    } else {
      
      ite14661 = 0;
    };
    int x14647 = ite14661;
    int ite14670 = 0;
    if(x14647) {
      
      int x2569 = x2559._3;
      int x2570 = x2560._3;
      int x2571 = x2569==(x2570);
      int x14671 = x2571;
      ite14670 = x14671;
    } else {
      
      ite14670 = 0;
    };
    int x14649 = ite14670;
    int x2573 = x14649 ? 0 : 1;
    return x2573; 
  }
};
 struct SEntry3_III_Idx23_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry3_III& x2100)  { 
    int x2101 = -889275714;
    int x2102 = x2100._2;
    int x2103 = HASH(x2102);
    int x2104 = -862048943*(x2103);
    int x2105 = x2104<<(15);
    int x2106 = x2104 >> (-15 & (8*sizeof(x2104)-1));
    int x2107 = x2105|(x2106);
    int x2108 = x2107*(461845907);
    int x2109 = x2101;
    int x2110 = x2108^(x2109);
    int x2111 = x2110<<(13);
    int x2112 = x2110 >> (-13 & (8*sizeof(x2110)-1));
    int x2113 = x2111|(x2112);
    int x2114 = x2113*(5);
    int x2115 = x2114+(-430675100);
    x2101 = x2115;
    int x2117 = x2100._3;
    int x2118 = HASH(x2117);
    int x2119 = -862048943*(x2118);
    int x2120 = x2119<<(15);
    int x2121 = x2119 >> (-15 & (8*sizeof(x2119)-1));
    int x2122 = x2120|(x2121);
    int x2123 = x2122*(461845907);
    int x2124 = x2101;
    int x2125 = x2123^(x2124);
    int x2126 = x2125<<(13);
    int x2127 = x2125 >> (-13 & (8*sizeof(x2125)-1));
    int x2128 = x2126|(x2127);
    int x2129 = x2128*(5);
    int x2130 = x2129+(-430675100);
    x2101 = x2130;
    int x2132 = x2101;
    int x2133 = x2132^(2);
    int x2134 = x2133 >> (16 & (8*sizeof(x2133)-1));
    int x2135 = x2133^(x2134);
    int x2136 = x2135*(-2048144789);
    int x2137 = x2136 >> (13 & (8*sizeof(x2136)-1));
    int x2138 = x2136^(x2137);
    int x2139 = x2138*(-1028477387);
    int x2140 = x2139 >> (16 & (8*sizeof(x2139)-1));
    int x2141 = x2139^(x2140);
    return x2141; 
  }
  FORCE_INLINE static char cmp(const struct SEntry3_III& x2143, const struct SEntry3_III& x2144) { 
    int x2145 = x2143._1;
    int x2146 = x2144._1;
    int x2147 = x2145==(x2146);
    int x2148 = x2145>(x2146);
    int x2149 = x2148 ? 1 : -1;
    int x2150 = x2147 ? 0 : x2149;
    return x2150; 
  }
};
 struct SEntry8_IIIITIIB_Idx234_Ordering {
  FORCE_INLINE static size_t hash(const struct SEntry8_IIIITIIB& x2576)  { 
    int x2577 = -889275714;
    int x2578 = x2576._2;
    int x2579 = HASH(x2578);
    int x2580 = -862048943*(x2579);
    int x2581 = x2580<<(15);
    int x2582 = x2580 >> (-15 & (8*sizeof(x2580)-1));
    int x2583 = x2581|(x2582);
    int x2584 = x2583*(461845907);
    int x2585 = x2577;
    int x2586 = x2584^(x2585);
    int x2587 = x2586<<(13);
    int x2588 = x2586 >> (-13 & (8*sizeof(x2586)-1));
    int x2589 = x2587|(x2588);
    int x2590 = x2589*(5);
    int x2591 = x2590+(-430675100);
    x2577 = x2591;
    int x2593 = x2576._3;
    int x2594 = HASH(x2593);
    int x2595 = -862048943*(x2594);
    int x2596 = x2595<<(15);
    int x2597 = x2595 >> (-15 & (8*sizeof(x2595)-1));
    int x2598 = x2596|(x2597);
    int x2599 = x2598*(461845907);
    int x2600 = x2577;
    int x2601 = x2599^(x2600);
    int x2602 = x2601<<(13);
    int x2603 = x2601 >> (-13 & (8*sizeof(x2601)-1));
    int x2604 = x2602|(x2603);
    int x2605 = x2604*(5);
    int x2606 = x2605+(-430675100);
    x2577 = x2606;
    int x2608 = x2576._4;
    int x2609 = HASH(x2608);
    int x2610 = -862048943*(x2609);
    int x2611 = x2610<<(15);
    int x2612 = x2610 >> (-15 & (8*sizeof(x2610)-1));
    int x2613 = x2611|(x2612);
    int x2614 = x2613*(461845907);
    int x2615 = x2577;
    int x2616 = x2614^(x2615);
    int x2617 = x2616<<(13);
    int x2618 = x2616 >> (-13 & (8*sizeof(x2616)-1));
    int x2619 = x2617|(x2618);
    int x2620 = x2619*(5);
    int x2621 = x2620+(-430675100);
    x2577 = x2621;
    int x2623 = x2577;
    int x2624 = x2623^(2);
    int x2625 = x2624 >> (16 & (8*sizeof(x2624)-1));
    int x2626 = x2624^(x2625);
    int x2627 = x2626*(-2048144789);
    int x2628 = x2627 >> (13 & (8*sizeof(x2627)-1));
    int x2629 = x2627^(x2628);
    int x2630 = x2629*(-1028477387);
    int x2631 = x2630 >> (16 & (8*sizeof(x2630)-1));
    int x2632 = x2630^(x2631);
    return x2632; 
  }
  FORCE_INLINE static char cmp(const struct SEntry8_IIIITIIB& x2634, const struct SEntry8_IIIITIIB& x2635) { 
    int x2636 = x2634._1;
    int x2637 = x2635._1;
    int x2638 = x2636==(x2637);
    int x2639 = x2636>(x2637);
    int x2640 = x2639 ? 1 : -1;
    int x2641 = x2638 ? 0 : x2640;
    return x2641; 
  }
};
#undef int

typedef HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1> newOrderTblIdx0Type;
typedef TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0> newOrderTblIdx1Type;
typedef MultiHashMap<struct SEntry3_III, char,
   HashIndex<struct SEntry3_III, char, SEntry3_III_Idx123, 1>,
   TreeIndex<struct SEntry3_III, char, SEntry3_III_Idx23, SEntry3_III_Idx23_Ordering, 0>> newOrderTblStoreType;
newOrderTblStoreType  newOrderTbl(newOrderTblSize);
newOrderTblIdx0Type& x2212 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x2213 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblIdx0Type& x2413 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef HashIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   HashIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblIdx0Type& x2455 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef HashIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 1> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   HashIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 1>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblIdx0Type& x2496 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblIdx0Type& x2722 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x2723 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef HashIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 1> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   HashIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 1>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblIdx0Type& x2785 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblIdx0Type& x2959 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x2960 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblIdx0Type& x3115 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x3116 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef HashIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 1> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   HashIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 1>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblIdx0Type& x3176 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    struct SEntry3_III* x11775 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x11775, 0, 1 * sizeof(struct SEntry3_III));
    x11775->_1 = -2147483648; x11775->_2 = x27; x11775->_3 = x12;
    struct SEntry3_III* x6653 = newOrderTbl.getCopy(x11775, 1);
    if((x6653!=(NULL))) {
      int x6656 = x6653->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6656;
      newOrderTbl.delCopy(x6653);
      int x41 = x18;
      struct SEntry8_IIIITIIB* x11788 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
      memset(x11788, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
      x11788->_1 = x6656; x11788->_2 = x41; x11788->_3 = x12; x11788->_4 = -2147483648; x11788->_5 = 0; x11788->_6 = -2147483648; x11788->_7 = -2147483648; x11788->_8 = 0;
      struct SEntry8_IIIITIIB* x6665 = orderTbl.getCopy(x11788, 0);
      int x6666 = x6665->_4;
      x6665->_6 = x13;
      orderTbl.updateCopy(x6665);
      double x51 = 0.0;
      int x53 = x18;
      struct SEntry10_IIIIIITIDS* x11805 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x11805, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x11805->_1 = x6656; x11805->_2 = x53; x11805->_3 = x12; x11805->_4 = -2147483648; x11805->_5 = -2147483648; x11805->_6 = -2147483648; x11805->_7 = 0; x11805->_8 = -2147483648; x11805->_9 = -1.7976931348623157E308; x11805->_10 = PString();
      orderLineTbl.sliceCopy(1, x11805, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
        orderLineEntry->_7 = x11;
        double x58 = x51;
        double x6728 = orderLineEntry->_9;
        x51 = (x58+(x6728));
        orderLineTbl.updateCopy(orderLineEntry);
      
      }));
      int x66 = x18;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11810 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      memset(x11810, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      x11810->_1 = x6666; x11810->_2 = x66; x11810->_3 = x12; x11810->_4 = PString(); x11810->_5 = PString(); x11810->_6 = PString(); x11810->_7 = PString(); x11810->_8 = PString(); x11810->_9 = PString(); x11810->_10 = PString(); x11810->_11 = PString(); x11810->_12 = PString(); x11810->_13 = 0; x11810->_14 = PString(); x11810->_15 = -1.7976931348623157E308; x11810->_16 = -1.7976931348623157E308; x11810->_17 = -1.7976931348623157E308; x11810->_18 = -1.7976931348623157E308; x11810->_19 = -2147483648; x11810->_20 = -2147483648; x11810->_21 = PString();
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6678 = customerTbl.getCopy(x11810, 0);
      double x70 = x51;
      double x6680 = x6678->_17;
      x6678->_17 = (x6680+(x70));
      int x6683 = x6678->_20;
      x6678->_20 = (x6683+(1));
      customerTbl.updateCopy(x6678);
    } else {
      
      int x74 = x18;
      orderIDs[(x74-(1))] = 0;
    };
    int x78 = x18;
    x18 = (x78+(1));
  };
}
void StockLevelTx(int x82, date x83, int x84, int x85, int x86, int x87) {
  struct SEntry11_IISSSSSSDDI* x11828 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x11828, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x11828->_1 = x86; x11828->_2 = x85; x11828->_3 = PString(); x11828->_4 = PString(); x11828->_5 = PString(); x11828->_6 = PString(); x11828->_7 = PString(); x11828->_8 = PString(); x11828->_9 = -1.7976931348623157E308; x11828->_10 = -1.7976931348623157E308; x11828->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x6818 = districtTbl.getCopy(x11828, 0);
  int x6819 = x6818->_11;
  int x97 = (x6819-(20));
  unordered_set<int> unique_ol_i_id;
  while(1) {
    
    int x101 = x97;
    if (!((x101<(x6819)))) break; 
    
    int x103 = x97;
    struct SEntry10_IIIIIITIDS* x11852 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
    memset(x11852, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
    x11852->_1 = x103; x11852->_2 = x86; x11852->_3 = x85; x11852->_4 = -2147483648; x11852->_5 = -2147483648; x11852->_6 = -2147483648; x11852->_7 = 0; x11852->_8 = -2147483648; x11852->_9 = -1.7976931348623157E308; x11852->_10 = PString();
    orderLineTbl.sliceCopy(1, x11852, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
      int x6848 = orderLineEntry->_5;
      struct SEntry17_IIISSSSSSSSSSIIIS* x11843 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x11843, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x11843->_1 = x6848; x11843->_2 = x85; x11843->_3 = -2147483648; x11843->_4 = PString(); x11843->_5 = PString(); x11843->_6 = PString(); x11843->_7 = PString(); x11843->_8 = PString(); x11843->_9 = PString(); x11843->_10 = PString(); x11843->_11 = PString(); x11843->_12 = PString(); x11843->_13 = PString(); x11843->_14 = -2147483648; x11843->_15 = -2147483648; x11843->_16 = -2147483648; x11843->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x6851 = stockTbl.getCopy(x11843, 0);
      int x6852 = x6851->_3;
      if((x6852<(x87))) {
        unique_ol_i_id.insert(x6848);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite10969 = NULL;
  if((x131>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x10970;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11866 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11866, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11866->_1 = -2147483648; x11866->_2 = x130; x11866->_3 = x129; x11866->_4 = PString(); x11866->_5 = PString(); x11866->_6 = x133; x11866->_7 = PString(); x11866->_8 = PString(); x11866->_9 = PString(); x11866->_10 = PString(); x11866->_11 = PString(); x11866->_12 = PString(); x11866->_13 = 0; x11866->_14 = PString(); x11866->_15 = -1.7976931348623157E308; x11866->_16 = -1.7976931348623157E308; x11866->_17 = -1.7976931348623157E308; x11866->_18 = -1.7976931348623157E308; x11866->_19 = -2147483648; x11866->_20 = -2147483648; x11866->_21 = PString();
    customerTbl.sliceCopy(1, x11866, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x10970.push_back(custEntry);
    
    }));
    int x10976 = x10970.size();
    int x10978 = (x10976/(2));
    int x10986 = x10970.size();
    if(((x10986%(2))==(0))) {
      int x152 = x10978;
      x10978 = (x152-(1));
    };
    sort(x10970.begin(), x10970.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x6959 = c1->_4;
      PString x6960 = c2->_4;
      return ((strcmpi(x6959.data_, x6960.data_))<(0)); 
    }));
    int x10994 = x10978;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10995 = x10970[x10994];
    ite10969 = x10995;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11891 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11891, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11891->_1 = x132; x11891->_2 = x130; x11891->_3 = x129; x11891->_4 = PString(); x11891->_5 = PString(); x11891->_6 = PString(); x11891->_7 = PString(); x11891->_8 = PString(); x11891->_9 = PString(); x11891->_10 = PString(); x11891->_11 = PString(); x11891->_12 = PString(); x11891->_13 = 0; x11891->_14 = PString(); x11891->_15 = -1.7976931348623157E308; x11891->_16 = -1.7976931348623157E308; x11891->_17 = -1.7976931348623157E308; x11891->_18 = -1.7976931348623157E308; x11891->_19 = -2147483648; x11891->_20 = -2147483648; x11891->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10999 = customerTbl.getCopy(x11891, 0);
    ite10969 = x10999;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6894 = ite10969;
  int x6895 = x6894->_3;
  struct SEntry8_IIIITIIB* x11899 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
  memset(x11899, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
  x11899->_1 = -2147483648; x11899->_2 = x130; x11899->_3 = x129; x11899->_4 = x6895; x11899->_5 = 0; x11899->_6 = -2147483648; x11899->_7 = -2147483648; x11899->_8 = 0;
  struct SEntry8_IIIITIIB* x6902 = orderTbl.getCopy(x11899, 1);
  int x184 = 0;
  int x6904 = x6902->_1;
  x184 = x6904;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  struct SEntry9_ISSSSSSDD* x11907 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
  memset(x11907, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
  x11907->_1 = x191; x11907->_2 = PString(); x11907->_3 = PString(); x11907->_4 = PString(); x11907->_5 = PString(); x11907->_6 = PString(); x11907->_7 = PString(); x11907->_8 = -1.7976931348623157E308; x11907->_9 = -1.7976931348623157E308;
  struct SEntry9_ISSSSSSDD* x7039 = warehouseTbl.getCopy(x11907, 0);
  double x7040 = x7039->_9;
  x7039->_9 = (x7040+(x198));
  warehouseTbl.updateCopy(x7039);
  struct SEntry11_IISSSSSSDDI* x11916 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x11916, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x11916->_1 = x192; x11916->_2 = x191; x11916->_3 = PString(); x11916->_4 = PString(); x11916->_5 = PString(); x11916->_6 = PString(); x11916->_7 = PString(); x11916->_8 = PString(); x11916->_9 = -1.7976931348623157E308; x11916->_10 = -1.7976931348623157E308; x11916->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x7046 = districtTbl.getCopy(x11916, 0);
  double x7047 = x7046->_10;
  x7046->_10 = (x7047+(x198));
  districtTbl.updateCopy(x7046);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite11066 = NULL;
  if((x193>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x11067;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11931 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11931, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11931->_1 = -2147483648; x11931->_2 = x195; x11931->_3 = x194; x11931->_4 = PString(); x11931->_5 = PString(); x11931->_6 = x197; x11931->_7 = PString(); x11931->_8 = PString(); x11931->_9 = PString(); x11931->_10 = PString(); x11931->_11 = PString(); x11931->_12 = PString(); x11931->_13 = 0; x11931->_14 = PString(); x11931->_15 = -1.7976931348623157E308; x11931->_16 = -1.7976931348623157E308; x11931->_17 = -1.7976931348623157E308; x11931->_18 = -1.7976931348623157E308; x11931->_19 = -2147483648; x11931->_20 = -2147483648; x11931->_21 = PString();
    customerTbl.sliceCopy(1, x11931, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x11067.push_back(custEntry);
    
    }));
    int x11073 = x11067.size();
    int x11075 = (x11073/(2));
    int x11083 = x11067.size();
    if(((x11083%(2))==(0))) {
      int x230 = x11075;
      x11075 = (x230-(1));
    };
    sort(x11067.begin(), x11067.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7168 = c1->_4;
      PString x7169 = c2->_4;
      return ((strcmpi(x7168.data_, x7169.data_))<(0)); 
    }));
    int x11091 = x11075;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11092 = x11067[x11091];
    ite11066 = x11092;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11956 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x11956, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x11956->_1 = x196; x11956->_2 = x195; x11956->_3 = x194; x11956->_4 = PString(); x11956->_5 = PString(); x11956->_6 = PString(); x11956->_7 = PString(); x11956->_8 = PString(); x11956->_9 = PString(); x11956->_10 = PString(); x11956->_11 = PString(); x11956->_12 = PString(); x11956->_13 = 0; x11956->_14 = PString(); x11956->_15 = -1.7976931348623157E308; x11956->_16 = -1.7976931348623157E308; x11956->_17 = -1.7976931348623157E308; x11956->_18 = -1.7976931348623157E308; x11956->_19 = -2147483648; x11956->_20 = -2147483648; x11956->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x11095 = customerTbl.getCopy(x11956, 0);
    ite11066 = x11095;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7052 = ite11066;
  PString x7053 = x7052->_21;
  PString x7054 = x7052->_14;
  char* x12422 = strstr(x7054.data_, "BC");
  if((x12422!=(NULL))) {
    int x7057 = x7052->_1;
    PString c_new_data(500);
    snprintf(c_new_data.data_, 501, "%d %d %d %d %d $%f %s | %s", x7057, x195, x194, x192, x191, x198, IntToStrdate(x189), x7053.data_);
    double x7060 = x7052->_17;
    x7052->_17 = (x7060+(x198));
    x7052->_21 = c_new_data;
  } else {
    
    double x7064 = x7052->_17;
    x7052->_17 = (x7064+(x198));
  };
  customerTbl.updateCopy(x7052);
  PString x7068 = x7039->_2;
  PString x7069 = x7046->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x7068.data_, x7069.data_);
  int x7072 = x7052->_1;
  struct SEntry8_IIIIITDS* x11982 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x11982, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x11982->_1 = x7072; x11982->_2 = x195; x11982->_3 = x194; x11982->_4 = x192; x11982->_5 = x191; x11982->_6 = x189; x11982->_7 = x198; x11982->_8 = h_data;
  historyTbl.add(x11982);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite11369 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x11370 = x301;
      ite11369 = x11370;
    } else {
      
      ite11369 = 0;
    };
    int x11197 = ite11369;
    if (!(x11197)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    struct SEntry5_IISDS* x12002 = (struct SEntry5_IISDS*)malloc(1 * sizeof(struct SEntry5_IISDS));
    memset(x12002, 0, 1 * sizeof(struct SEntry5_IISDS));
    x12002->_1 = x305; x12002->_2 = -2147483648; x12002->_3 = PString(); x12002->_4 = -1.7976931348623157E308; x12002->_5 = PString();
    struct SEntry5_IISDS* x7292 = itemTbl.getCopy(x12002, 0);
    if((x7292==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x7297 = x7292->_3;
      x284[x312] = x7297;
      int x315 = x289;
      double x7300 = x7292->_4;
      x283[x315] = x7300;
      int x318 = x289;
      PString x7303 = x7292->_5;
      idata[x318] = x7303;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x12024 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x12024, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x12024->_1 = x277; x12024->_2 = x276; x12024->_3 = x275; x12024->_4 = PString(); x12024->_5 = PString(); x12024->_6 = PString(); x12024->_7 = PString(); x12024->_8 = PString(); x12024->_9 = PString(); x12024->_10 = PString(); x12024->_11 = PString(); x12024->_12 = PString(); x12024->_13 = 0; x12024->_14 = PString(); x12024->_15 = -1.7976931348623157E308; x12024->_16 = -1.7976931348623157E308; x12024->_17 = -1.7976931348623157E308; x12024->_18 = -1.7976931348623157E308; x12024->_19 = -2147483648; x12024->_20 = -2147483648; x12024->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7313 = customerTbl.getCopy(x12024, 0);
    struct SEntry9_ISSSSSSDD* x12029 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
    memset(x12029, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
    x12029->_1 = x275; x12029->_2 = PString(); x12029->_3 = PString(); x12029->_4 = PString(); x12029->_5 = PString(); x12029->_6 = PString(); x12029->_7 = PString(); x12029->_8 = -1.7976931348623157E308; x12029->_9 = -1.7976931348623157E308;
    struct SEntry9_ISSSSSSDD* x7316 = warehouseTbl.getCopy(x12029, 0);
    struct SEntry11_IISSSSSSDDI* x12033 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
    memset(x12033, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
    x12033->_1 = x276; x12033->_2 = x275; x12033->_3 = PString(); x12033->_4 = PString(); x12033->_5 = PString(); x12033->_6 = PString(); x12033->_7 = PString(); x12033->_8 = PString(); x12033->_9 = -1.7976931348623157E308; x12033->_10 = -1.7976931348623157E308; x12033->_11 = -2147483648;
    struct SEntry11_IISSSSSSDDI* x7319 = districtTbl.getCopy(x12033, 0);
    int x7320 = x7319->_11;
    int x7321 = x7319->_11;
    x7319->_11 = (x7321+(1));
    districtTbl.updateCopy(x7319);
    struct SEntry8_IIIITIIB* x12043 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x12043, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x12043->_1 = x7320; x12043->_2 = x276; x12043->_3 = x275; x12043->_4 = x277; x12043->_5 = x273; x12043->_6 = -1; x12043->_7 = x278; x12043->_8 = (x279>(0));
    orderTbl.add(x12043);
    struct SEntry3_III* x12047 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x12047, 0, 1 * sizeof(struct SEntry3_III));
    x12047->_1 = x7320; x12047->_2 = x276; x12047->_3 = x275;
    newOrderTbl.add(x12047);
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
      struct SEntry17_IIISSSSSSSSSSIIIS* x12062 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x12062, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x12062->_1 = ol_i_id; x12062->_2 = ol_supply_w_id; x12062->_3 = -2147483648; x12062->_4 = PString(); x12062->_5 = PString(); x12062->_6 = PString(); x12062->_7 = PString(); x12062->_8 = PString(); x12062->_9 = PString(); x12062->_10 = PString(); x12062->_11 = PString(); x12062->_12 = PString(); x12062->_13 = PString(); x12062->_14 = -2147483648; x12062->_15 = -2147483648; x12062->_16 = -2147483648; x12062->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x7345 = stockTbl.getCopy(x12062, 0);
      PString ite11252 = PString();
      if((x276==(1))) {
        PString x11253 = x7345->_4;
        ite11252 = x11253;
      } else {
        
        PString ite11257 = PString();
        if((x276==(2))) {
          PString x11258 = x7345->_5;
          ite11257 = x11258;
        } else {
          
          PString ite11262 = PString();
          if((x276==(3))) {
            PString x11263 = x7345->_6;
            ite11262 = x11263;
          } else {
            
            PString ite11267 = PString();
            if((x276==(4))) {
              PString x11268 = x7345->_7;
              ite11267 = x11268;
            } else {
              
              PString ite11272 = PString();
              if((x276==(5))) {
                PString x11273 = x7345->_8;
                ite11272 = x11273;
              } else {
                
                PString ite11277 = PString();
                if((x276==(6))) {
                  PString x11278 = x7345->_9;
                  ite11277 = x11278;
                } else {
                  
                  PString ite11282 = PString();
                  if((x276==(7))) {
                    PString x11283 = x7345->_10;
                    ite11282 = x11283;
                  } else {
                    
                    PString ite11287 = PString();
                    if((x276==(8))) {
                      PString x11288 = x7345->_11;
                      ite11287 = x11288;
                    } else {
                      
                      PString ite11292 = PString();
                      if((x276==(9))) {
                        PString x11293 = x7345->_12;
                        ite11292 = x11293;
                      } else {
                        
                        PString x11295 = x7345->_13;
                        ite11292 = x11295;
                      };
                      PString x11291 = ite11292;
                      ite11287 = x11291;
                    };
                    PString x11286 = ite11287;
                    ite11282 = x11286;
                  };
                  PString x11281 = ite11282;
                  ite11277 = x11281;
                };
                PString x11276 = ite11277;
                ite11272 = x11276;
              };
              PString x11271 = ite11272;
              ite11267 = x11271;
            };
            PString x11266 = ite11267;
            ite11262 = x11266;
          };
          PString x11261 = ite11262;
          ite11257 = x11261;
        };
        PString x11256 = ite11257;
        ite11252 = x11256;
      };
      PString ol_dist_info = ite11252;
      int x7374 = x7345->_3;
      int x401 = x289;
      x285[x401] = x7374;
      PString x7377 = x7313->_14;
      char* x12673 = strstr(x7377.data_, "original");
      int ite11497 = 0;
      if((x12673!=(NULL))) {
        
        PString x7380 = x7345->_17;
        char* x12679 = strstr(x7380.data_, "original");
        int x11498 = (x12679!=(NULL));
        ite11497 = x11498;
      } else {
        
        ite11497 = 0;
      };
      int x11320 = ite11497;
      if(x11320) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      x7345->_3 = (x7374-(ol_quantity));
      if((x7374<=(ol_quantity))) {
        int x7391 = x7345->_3;
        x7345->_3 = (x7391+(91));
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      stockTbl.updateCopy(x7345);
      double x7399 = x7313->_16;
      double x7400 = x7316->_8;
      double x7401 = x7319->_9;
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(x7400))+(x7401))))*((1.0-(x7399)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      struct SEntry10_IIIIIITIDS* x12178 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x12178, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x12178->_1 = x7320; x12178->_2 = x276; x12178->_3 = x275; x12178->_4 = (x446+(1)); x12178->_5 = ol_i_id; x12178->_6 = ol_supply_w_id; x12178->_7 = NULL; x12178->_8 = ol_quantity; x12178->_9 = ol_amount; x12178->_10 = ol_dist_info;
      orderLineTbl.add(x12178);
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
