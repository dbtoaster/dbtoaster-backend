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
  int _1;  int _2;  PString _3;  double _4;  PString _5;  SEntry5_IISDS *prv;  SEntry5_IISDS *nxt;
  SEntry5_IISDS() :_1(-2147483648), _2(-2147483648), _3(), _4(-1.7976931348623157E308), _5(), prv(nullptr), nxt(nullptr) {}
  SEntry5_IISDS(const int& _1, const int& _2, const PString& _3, const double& _4, const PString& _5) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), prv(nullptr), nxt(nullptr) {}
  SEntry5_IISDS* copy() { return new SEntry5_IISDS(_1, _2, *_3.copy(), _4, *_5.copy()); }
};
struct SEntry11_IISSSSSSDDI {
  int _1;  int _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  double _9;  double _10;  int _11;  SEntry11_IISSSSSSDDI *prv;  SEntry11_IISSSSSSDDI *nxt;
  SEntry11_IISSSSSSDDI() :_1(-2147483648), _2(-2147483648), _3(), _4(), _5(), _6(), _7(), _8(), _9(-1.7976931348623157E308), _10(-1.7976931348623157E308), _11(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI(const int& _1, const int& _2, const PString& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const double& _9, const double& _10, const int& _11) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), prv(nullptr), nxt(nullptr) {}
  SEntry11_IISSSSSSDDI* copy() { return new SEntry11_IISSSSSSDDI(_1, _2, *_3.copy(), *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), _9, _10, _11); }
};
struct SEntry21_IIISSSSSSSSSTSDDDDIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  date _13;  PString _14;  double _15;  double _16;  double _17;  double _18;  int _19;  int _20;  PString _21;  SEntry21_IIISSSSSSSSSTSDDDDIIS *prv;  SEntry21_IIISSSSSSSSSTSDDDDIIS *nxt;
  SEntry21_IIISSSSSSSSSTSDDDDIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(0), _14(), _15(-1.7976931348623157E308), _16(-1.7976931348623157E308), _17(-1.7976931348623157E308), _18(-1.7976931348623157E308), _19(-2147483648), _20(-2147483648), _21(), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const date& _13, const PString& _14, const double& _15, const double& _16, const double& _17, const double& _18, const int& _19, const int& _20, const PString& _21) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), _18(_18), _19(_19), _20(_20), _21(_21), prv(nullptr), nxt(nullptr) {}
  SEntry21_IIISSSSSSSSSTSDDDDIIS* copy() { return new SEntry21_IIISSSSSSSSSTSDDDDIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), _13, *_14.copy(), _15, _16, _17, _18, _19, _20, *_21.copy()); }
};
struct SEntry8_IIIITIIB {
  int _1;  int _2;  int _3;  int _4;  date _5;  int _6;  int _7;  int _8;  SEntry8_IIIITIIB *prv;  SEntry8_IIIITIIB *nxt;
  SEntry8_IIIITIIB() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(0), _6(-2147483648), _7(-2147483648), _8(0), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB(const int& _1, const int& _2, const int& _3, const int& _4, const date& _5, const int& _6, const int& _7, const int& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIITIIB* copy() { return new SEntry8_IIIITIIB(_1, _2, _3, _4, _5, _6, _7, _8); }
};
struct SEntry3_III {
  int _1;  int _2;  int _3;  SEntry3_III *prv;  SEntry3_III *nxt;
  SEntry3_III() :_1(-2147483648), _2(-2147483648), _3(-2147483648), prv(nullptr), nxt(nullptr) {}
  SEntry3_III(const int& _1, const int& _2, const int& _3) : _1(_1), _2(_2), _3(_3), prv(nullptr), nxt(nullptr) {}
  SEntry3_III* copy() { return new SEntry3_III(_1, _2, _3); }
};
struct SEntry8_IIIIITDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  date _6;  double _7;  PString _8;  SEntry8_IIIIITDS *prv;  SEntry8_IIIIITDS *nxt;
  SEntry8_IIIIITDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(0), _7(-1.7976931348623157E308), _8(), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const date& _6, const double& _7, const PString& _8) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), prv(nullptr), nxt(nullptr) {}
  SEntry8_IIIIITDS* copy() { return new SEntry8_IIIIITDS(_1, _2, _3, _4, _5, _6, _7, *_8.copy()); }
};
struct SEntry17_IIISSSSSSSSSSIIIS {
  int _1;  int _2;  int _3;  PString _4;  PString _5;  PString _6;  PString _7;  PString _8;  PString _9;  PString _10;  PString _11;  PString _12;  PString _13;  int _14;  int _15;  int _16;  PString _17;  SEntry17_IIISSSSSSSSSSIIIS *prv;  SEntry17_IIISSSSSSSSSSIIIS *nxt;
  SEntry17_IIISSSSSSSSSSIIIS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(), _5(), _6(), _7(), _8(), _9(), _10(), _11(), _12(), _13(), _14(-2147483648), _15(-2147483648), _16(-2147483648), _17(), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS(const int& _1, const int& _2, const int& _3, const PString& _4, const PString& _5, const PString& _6, const PString& _7, const PString& _8, const PString& _9, const PString& _10, const PString& _11, const PString& _12, const PString& _13, const int& _14, const int& _15, const int& _16, const PString& _17) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), _11(_11), _12(_12), _13(_13), _14(_14), _15(_15), _16(_16), _17(_17), prv(nullptr), nxt(nullptr) {}
  SEntry17_IIISSSSSSSSSSIIIS* copy() { return new SEntry17_IIISSSSSSSSSSIIIS(_1, _2, _3, *_4.copy(), *_5.copy(), *_6.copy(), *_7.copy(), *_8.copy(), *_9.copy(), *_10.copy(), *_11.copy(), *_12.copy(), *_13.copy(), _14, _15, _16, *_17.copy()); }
};
struct SEntry10_IIIIIITIDS {
  int _1;  int _2;  int _3;  int _4;  int _5;  int _6;  date _7;  int _8;  double _9;  PString _10;  SEntry10_IIIIIITIDS *prv;  SEntry10_IIIIIITIDS *nxt;
  SEntry10_IIIIIITIDS() :_1(-2147483648), _2(-2147483648), _3(-2147483648), _4(-2147483648), _5(-2147483648), _6(-2147483648), _7(0), _8(-2147483648), _9(-1.7976931348623157E308), _10(), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS(const int& _1, const int& _2, const int& _3, const int& _4, const int& _5, const int& _6, const date& _7, const int& _8, const double& _9, const PString& _10) : _1(_1), _2(_2), _3(_3), _4(_4), _5(_5), _6(_6), _7(_7), _8(_8), _9(_9), _10(_10), prv(nullptr), nxt(nullptr) {}
  SEntry10_IIIIIITIDS* copy() { return new SEntry10_IIIIIITIDS(_1, _2, _3, _4, _5, _6, _7, _8, _9, *_10.copy()); }
};
struct SEntry9_ISSSSSSDD {
  int _1;  PString _2;  PString _3;  PString _4;  PString _5;  PString _6;  PString _7;  double _8;  double _9;  SEntry9_ISSSSSSDD *prv;  SEntry9_ISSSSSSDD *nxt;
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
    int ite16307 = 0;
    if(1) {
      
      int x2704 = x2702._2;
      int x2705 = x2703._2;
      int x2706 = x2704==(x2705);
      int x16308 = x2706;
      ite16307 = x16308;
    } else {
      
      ite16307 = 0;
    };
    int x16300 = ite16307;
    int ite16316 = 0;
    if(x16300) {
      
      int x2708 = x2702._3;
      int x2709 = x2703._3;
      int x2710 = x2708==(x2709);
      int x16317 = x2710;
      ite16316 = x16317;
    } else {
      
      ite16316 = 0;
    };
    int x16302 = ite16316;
    int ite16325 = 0;
    if(x16302) {
      
      int x2712 = x2702._4;
      int x2713 = x2703._4;
      int x2714 = x2712==(x2713);
      int x16326 = x2714;
      ite16325 = x16326;
    } else {
      
      ite16325 = 0;
    };
    int x16304 = ite16325;
    int x2716 = x16304 ? 0 : 1;
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
    int ite16426 = 0;
    if(1) {
      
      int x2085 = x2083._1;
      int x2086 = x2084._1;
      int x2087 = x2085==(x2086);
      int x16427 = x2087;
      ite16426 = x16427;
    } else {
      
      ite16426 = 0;
    };
    int x16419 = ite16426;
    int ite16435 = 0;
    if(x16419) {
      
      int x2089 = x2083._2;
      int x2090 = x2084._2;
      int x2091 = x2089==(x2090);
      int x16436 = x2091;
      ite16435 = x16436;
    } else {
      
      ite16435 = 0;
    };
    int x16421 = ite16435;
    int ite16444 = 0;
    if(x16421) {
      
      int x2093 = x2083._3;
      int x2094 = x2084._3;
      int x2095 = x2093==(x2094);
      int x16445 = x2095;
      ite16444 = x16445;
    } else {
      
      ite16444 = 0;
    };
    int x16423 = ite16444;
    int x2097 = x16423 ? 0 : 1;
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
    int ite16562 = 0;
    if(1) {
      
      int x2862 = x2860._1;
      int x2863 = x2861._1;
      int x2864 = x2862==(x2863);
      int x16563 = x2864;
      ite16562 = x16563;
    } else {
      
      ite16562 = 0;
    };
    int x16553 = ite16562;
    int ite16571 = 0;
    if(x16553) {
      
      int x2866 = x2860._2;
      int x2867 = x2861._2;
      int x2868 = x2866==(x2867);
      int x16572 = x2868;
      ite16571 = x16572;
    } else {
      
      ite16571 = 0;
    };
    int x16555 = ite16571;
    int ite16580 = 0;
    if(x16555) {
      
      int x2870 = x2860._3;
      int x2871 = x2861._3;
      int x2872 = x2870==(x2871);
      int x16581 = x2872;
      ite16580 = x16581;
    } else {
      
      ite16580 = 0;
    };
    int x16557 = ite16580;
    int ite16589 = 0;
    if(x16557) {
      
      int x2874 = x2860._4;
      int x2875 = x2861._4;
      int x2876 = x2874==(x2875);
      int x16590 = x2876;
      ite16589 = x16590;
    } else {
      
      ite16589 = 0;
    };
    int x16559 = ite16589;
    int x2878 = x16559 ? 0 : 1;
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
    int ite16699 = 0;
    if(1) {
      
      int x3022 = x3020._1;
      int x3023 = x3021._1;
      int x3024 = x3022==(x3023);
      int x16700 = x3024;
      ite16699 = x16700;
    } else {
      
      ite16699 = 0;
    };
    int x16692 = ite16699;
    int ite16708 = 0;
    if(x16692) {
      
      int x3026 = x3020._2;
      int x3027 = x3021._2;
      int x3028 = x3026==(x3027);
      int x16709 = x3028;
      ite16708 = x16709;
    } else {
      
      ite16708 = 0;
    };
    int x16694 = ite16708;
    int ite16717 = 0;
    if(x16694) {
      
      int x3030 = x3020._3;
      int x3031 = x3021._3;
      int x3032 = x3030==(x3031);
      int x16718 = x3032;
      ite16717 = x16718;
    } else {
      
      ite16717 = 0;
    };
    int x16696 = ite16717;
    int x3034 = x16696 ? 0 : 1;
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
    int ite16801 = 0;
    if(1) {
      
      int x2198 = x2196._2;
      int x2199 = x2197._2;
      int x2200 = x2198==(x2199);
      int x16802 = x2200;
      ite16801 = x16802;
    } else {
      
      ite16801 = 0;
    };
    int x16796 = ite16801;
    int ite16810 = 0;
    if(x16796) {
      
      int x2202 = x2196._3;
      int x2203 = x2197._3;
      int x2204 = x2202==(x2203);
      int x16811 = x2204;
      ite16810 = x16811;
    } else {
      
      ite16810 = 0;
    };
    int x16798 = ite16810;
    int x2206 = x16798 ? 0 : 1;
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
    int ite16902 = 0;
    if(1) {
      
      int x2941 = x2939._1;
      int x2942 = x2940._1;
      int x2943 = x2941==(x2942);
      int x16903 = x2943;
      ite16902 = x16903;
    } else {
      
      ite16902 = 0;
    };
    int x16895 = ite16902;
    int ite16911 = 0;
    if(x16895) {
      
      int x2945 = x2939._2;
      int x2946 = x2940._2;
      int x2947 = x2945==(x2946);
      int x16912 = x2947;
      ite16911 = x16912;
    } else {
      
      ite16911 = 0;
    };
    int x16897 = ite16911;
    int ite16920 = 0;
    if(x16897) {
      
      int x2949 = x2939._3;
      int x2950 = x2940._3;
      int x2951 = x2949==(x2950);
      int x16921 = x2951;
      ite16920 = x16921;
    } else {
      
      ite16920 = 0;
    };
    int x16899 = ite16920;
    int x2953 = x16899 ? 0 : 1;
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
    int ite17004 = 0;
    if(1) {
      
      int x3162 = x3160._1;
      int x3163 = x3161._1;
      int x3164 = x3162==(x3163);
      int x17005 = x3164;
      ite17004 = x17005;
    } else {
      
      ite17004 = 0;
    };
    int x16999 = ite17004;
    int ite17013 = 0;
    if(x16999) {
      
      int x3166 = x3160._2;
      int x3167 = x3161._2;
      int x3168 = x3166==(x3167);
      int x17014 = x3168;
      ite17013 = x17014;
    } else {
      
      ite17013 = 0;
    };
    int x17001 = ite17013;
    int x3170 = x17001 ? 0 : 1;
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
    int ite17188 = 0;
    if(1) {
      
      int x2351 = x2349._1;
      int x2352 = x2350._1;
      int x2353 = x2351==(-2147483648);
      int ite17286 = 0;
      if(x2353) {
        ite17286 = 1;
      } else {
        
        
        int x2354 = x2352==(-2147483648);
        int x17288 = x2354;
        ite17286 = x17288;
      };
      int x17194 = ite17286;
      int ite17293 = 0;
      if(x17194) {
        ite17293 = 1;
      } else {
        
        
        int x2356 = x2351==(x2352);
        int x17295 = x2356;
        ite17293 = x17295;
      };
      int x17196 = ite17293;
      int x17189 = x17196;
      ite17188 = x17189;
    } else {
      
      ite17188 = 0;
    };
    int x17173 = ite17188;
    int ite17201 = 0;
    if(x17173) {
      
      int x2359 = x2349._2;
      int x2360 = x2350._2;
      int x2361 = x2359==(-2147483648);
      int ite17309 = 0;
      if(x2361) {
        ite17309 = 1;
      } else {
        
        
        int x2362 = x2360==(-2147483648);
        int x17311 = x2362;
        ite17309 = x17311;
      };
      int x17207 = ite17309;
      int ite17316 = 0;
      if(x17207) {
        ite17316 = 1;
      } else {
        
        
        int x2364 = x2359==(x2360);
        int x17318 = x2364;
        ite17316 = x17318;
      };
      int x17209 = ite17316;
      int x17202 = x17209;
      ite17201 = x17202;
    } else {
      
      ite17201 = 0;
    };
    int x17175 = ite17201;
    int ite17214 = 0;
    if(x17175) {
      
      int x2367 = x2349._3;
      int x2368 = x2350._3;
      int x2369 = x2367==(-2147483648);
      int ite17332 = 0;
      if(x2369) {
        ite17332 = 1;
      } else {
        
        
        int x2370 = x2368==(-2147483648);
        int x17334 = x2370;
        ite17332 = x17334;
      };
      int x17220 = ite17332;
      int ite17339 = 0;
      if(x17220) {
        ite17339 = 1;
      } else {
        
        
        int x2372 = x2367==(x2368);
        int x17341 = x2372;
        ite17339 = x17341;
      };
      int x17222 = ite17339;
      int x17215 = x17222;
      ite17214 = x17215;
    } else {
      
      ite17214 = 0;
    };
    int x17177 = ite17214;
    int ite17227 = 0;
    if(x17177) {
      
      int x2375 = x2349._4;
      int x2376 = x2350._4;
      int x2377 = x2375==(-2147483648);
      int ite17355 = 0;
      if(x2377) {
        ite17355 = 1;
      } else {
        
        
        int x2378 = x2376==(-2147483648);
        int x17357 = x2378;
        ite17355 = x17357;
      };
      int x17233 = ite17355;
      int ite17362 = 0;
      if(x17233) {
        ite17362 = 1;
      } else {
        
        
        int x2380 = x2375==(x2376);
        int x17364 = x2380;
        ite17362 = x17364;
      };
      int x17235 = ite17362;
      int x17228 = x17235;
      ite17227 = x17228;
    } else {
      
      ite17227 = 0;
    };
    int x17179 = ite17227;
    int ite17240 = 0;
    if(x17179) {
      
      int x2383 = x2349._5;
      int x2384 = x2350._5;
      int x2385 = x2383==(-2147483648);
      int ite17378 = 0;
      if(x2385) {
        ite17378 = 1;
      } else {
        
        
        int x2386 = x2384==(-2147483648);
        int x17380 = x2386;
        ite17378 = x17380;
      };
      int x17246 = ite17378;
      int ite17385 = 0;
      if(x17246) {
        ite17385 = 1;
      } else {
        
        
        int x2388 = x2383==(x2384);
        int x17387 = x2388;
        ite17385 = x17387;
      };
      int x17248 = ite17385;
      int x17241 = x17248;
      ite17240 = x17241;
    } else {
      
      ite17240 = 0;
    };
    int x17181 = ite17240;
    int ite17253 = 0;
    if(x17181) {
      
      date x2391 = x2349._6;
      date x2392 = x2350._6;
      int x2393 = x2391==(0);
      int ite17401 = 0;
      if(x2393) {
        ite17401 = 1;
      } else {
        
        
        int x2394 = x2392==(0);
        int x17403 = x2394;
        ite17401 = x17403;
      };
      int x17259 = ite17401;
      int ite17408 = 0;
      if(x17259) {
        ite17408 = 1;
      } else {
        
        
        int x2396 = x2391==(x2392);
        int x17410 = x2396;
        ite17408 = x17410;
      };
      int x17261 = ite17408;
      int x17254 = x17261;
      ite17253 = x17254;
    } else {
      
      ite17253 = 0;
    };
    int x17183 = ite17253;
    int ite17266 = 0;
    if(x17183) {
      
      double x2399 = x2349._7;
      double x2400 = x2350._7;
      int x2401 = x2399==(-1.7976931348623157E308);
      int ite17424 = 0;
      if(x2401) {
        ite17424 = 1;
      } else {
        
        
        int x2402 = x2400==(-1.7976931348623157E308);
        int x17426 = x2402;
        ite17424 = x17426;
      };
      int x17272 = ite17424;
      int ite17431 = 0;
      if(x17272) {
        ite17431 = 1;
      } else {
        
        
        int x2404 = x2399==(x2400);
        int x17433 = x2404;
        ite17431 = x17433;
      };
      int x17274 = ite17431;
      int x17267 = x17274;
      ite17266 = x17267;
    } else {
      
      ite17266 = 0;
    };
    int x17185 = ite17266;
    int x2407 = x17185 ? 0 : 1;
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
    int ite17633 = 0;
    if(1) {
      
      int x2486 = x2484._1;
      int x2487 = x2485._1;
      int x2488 = x2486==(x2487);
      int x17634 = x2488;
      ite17633 = x17634;
    } else {
      
      ite17633 = 0;
    };
    int x17630 = ite17633;
    int x2490 = x17630 ? 0 : 1;
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
    int ite17699 = 0;
    if(1) {
      
      int x2771 = x2769._1;
      int x2772 = x2770._1;
      int x2773 = x2771==(x2772);
      int x17700 = x2773;
      ite17699 = x17700;
    } else {
      
      ite17699 = 0;
    };
    int x17694 = ite17699;
    int ite17708 = 0;
    if(x17694) {
      
      int x2775 = x2769._2;
      int x2776 = x2770._2;
      int x2777 = x2775==(x2776);
      int x17709 = x2777;
      ite17708 = x17709;
    } else {
      
      ite17708 = 0;
    };
    int x17696 = ite17708;
    int x2779 = x17696 ? 0 : 1;
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
    int ite17800 = 0;
    if(1) {
      
      int x3097 = x3095._2;
      int x3098 = x3096._2;
      int x3099 = x3097==(x3098);
      int x17801 = x3099;
      ite17800 = x17801;
    } else {
      
      ite17800 = 0;
    };
    int x17793 = ite17800;
    int ite17809 = 0;
    if(x17793) {
      
      int x3101 = x3095._3;
      int x3102 = x3096._3;
      int x3103 = x3101==(x3102);
      int x17810 = x3103;
      ite17809 = x17810;
    } else {
      
      ite17809 = 0;
    };
    int x17795 = ite17809;
    int ite17818 = 0;
    if(x17795) {
      
      PString x3105 = x3095._6;
      PString x3106 = x3096._6;
      int x3107 = x3105==(x3106);
      int x17819 = x3107;
      ite17818 = x17819;
    } else {
      
      ite17818 = 0;
    };
    int x17797 = ite17818;
    int x3109 = x17797 ? 0 : 1;
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
    int ite17885 = 0;
    if(1) {
      
      int x2445 = x2443._1;
      int x2446 = x2444._1;
      int x2447 = x2445==(x2446);
      int x17886 = x2447;
      ite17885 = x17886;
    } else {
      
      ite17885 = 0;
    };
    int x17882 = ite17885;
    int x2449 = x17882 ? 0 : 1;
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
    int ite17968 = 0;
    if(1) {
      
      int x2561 = x2559._1;
      int x2562 = x2560._1;
      int x2563 = x2561==(x2562);
      int x17969 = x2563;
      ite17968 = x17969;
    } else {
      
      ite17968 = 0;
    };
    int x17961 = ite17968;
    int ite17977 = 0;
    if(x17961) {
      
      int x2565 = x2559._2;
      int x2566 = x2560._2;
      int x2567 = x2565==(x2566);
      int x17978 = x2567;
      ite17977 = x17978;
    } else {
      
      ite17977 = 0;
    };
    int x17963 = ite17977;
    int ite17986 = 0;
    if(x17963) {
      
      int x2569 = x2559._3;
      int x2570 = x2560._3;
      int x2571 = x2569==(x2570);
      int x17987 = x2571;
      ite17986 = x17987;
    } else {
      
      ite17986 = 0;
    };
    int x17965 = ite17986;
    int x2573 = x17965 ? 0 : 1;
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
newOrderTblStoreType& x2211 = newOrderTbl;
newOrderTblIdx0Type& x806 = * (newOrderTblIdx0Type *)newOrderTbl.index[0];
newOrderTblIdx1Type& x807 = * (newOrderTblIdx1Type *)newOrderTbl.index[1];
newOrderTblIdx0Type& newOrderTblPrimaryIdx = * (newOrderTblIdx0Type *) newOrderTbl.index[0];


typedef HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0> historyTblIdx0Type;
typedef MultiHashMap<struct SEntry8_IIIIITDS, char,
   HashIndex<struct SEntry8_IIIIITDS, char, SEntry8_IIIIITDS_Idx, 0>> historyTblStoreType;
historyTblStoreType  historyTbl(historyTblSize);
historyTblStoreType& x2412 = historyTbl;
historyTblIdx0Type& x813 = * (historyTblIdx0Type *)historyTbl.index[0];
historyTblIdx0Type& historyTblPrimaryIdx = * (historyTblIdx0Type *) historyTbl.index[0];


typedef HashIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 1> warehouseTblIdx0Type;
typedef MultiHashMap<struct SEntry9_ISSSSSSDD, char,
   HashIndex<struct SEntry9_ISSSSSSDD, char, SEntry9_ISSSSSSDD_Idx1, 1>> warehouseTblStoreType;
warehouseTblStoreType  warehouseTbl(warehouseTblSize);
warehouseTblStoreType& x2454 = warehouseTbl;
warehouseTblIdx0Type& x818 = * (warehouseTblIdx0Type *)warehouseTbl.index[0];
warehouseTblIdx0Type& warehouseTblPrimaryIdx = * (warehouseTblIdx0Type *) warehouseTbl.index[0];


typedef HashIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 1> itemTblIdx0Type;
typedef MultiHashMap<struct SEntry5_IISDS, char,
   HashIndex<struct SEntry5_IISDS, char, SEntry5_IISDS_Idx1, 1>> itemTblStoreType;
itemTblStoreType  itemTbl(itemTblSize);
itemTblStoreType& x2495 = itemTbl;
itemTblIdx0Type& x821 = * (itemTblIdx0Type *)itemTbl.index[0];
itemTblIdx0Type& itemTblPrimaryIdx = * (itemTblIdx0Type *) itemTbl.index[0];


typedef HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1> orderTblIdx0Type;
typedef TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1> orderTblIdx1Type;
typedef MultiHashMap<struct SEntry8_IIIITIIB, char,
   HashIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx123, 1>,
   TreeIndex<struct SEntry8_IIIITIIB, char, SEntry8_IIIITIIB_Idx234, SEntry8_IIIITIIB_Idx234_Ordering, 1>> orderTblStoreType;
orderTblStoreType  orderTbl(orderTblSize);
orderTblStoreType& x2721 = orderTbl;
orderTblIdx0Type& x828 = * (orderTblIdx0Type *)orderTbl.index[0];
orderTblIdx1Type& x829 = * (orderTblIdx1Type *)orderTbl.index[1];
orderTblIdx0Type& orderTblPrimaryIdx = * (orderTblIdx0Type *) orderTbl.index[0];


typedef HashIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 1> districtTblIdx0Type;
typedef MultiHashMap<struct SEntry11_IISSSSSSDDI, char,
   HashIndex<struct SEntry11_IISSSSSSDDI, char, SEntry11_IISSSSSSDDI_Idx12, 1>> districtTblStoreType;
districtTblStoreType  districtTbl(districtTblSize);
districtTblStoreType& x2784 = districtTbl;
districtTblIdx0Type& x835 = * (districtTblIdx0Type *)districtTbl.index[0];
districtTblIdx0Type& districtTblPrimaryIdx = * (districtTblIdx0Type *) districtTbl.index[0];


typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1> orderLineTblIdx0Type;
typedef HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0> orderLineTblIdx1Type;
typedef MultiHashMap<struct SEntry10_IIIIIITIDS, char,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx1234, 1>,
   HashIndex<struct SEntry10_IIIIIITIDS, char, SEntry10_IIIIIITIDS_Idx123, 0>> orderLineTblStoreType;
orderLineTblStoreType  orderLineTbl(orderLineTblSize);
orderLineTblStoreType& x2958 = orderLineTbl;
orderLineTblIdx0Type& x840 = * (orderLineTblIdx0Type *)orderLineTbl.index[0];
orderLineTblIdx1Type& x841 = * (orderLineTblIdx1Type *)orderLineTbl.index[1];
orderLineTblIdx0Type& orderLineTblPrimaryIdx = * (orderLineTblIdx0Type *) orderLineTbl.index[0];


typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1> customerTblIdx0Type;
typedef HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0> customerTblIdx1Type;
typedef MultiHashMap<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx123, 1>,
   HashIndex<struct SEntry21_IIISSSSSSSSSTSDDDDIIS, char, SEntry21_IIISSSSSSSSSTSDDDDIIS_Idx236, 0>> customerTblStoreType;
customerTblStoreType  customerTbl(customerTblSize);
customerTblStoreType& x3114 = customerTbl;
customerTblIdx0Type& x846 = * (customerTblIdx0Type *)customerTbl.index[0];
customerTblIdx1Type& x847 = * (customerTblIdx1Type *)customerTbl.index[1];
customerTblIdx0Type& customerTblPrimaryIdx = * (customerTblIdx0Type *) customerTbl.index[0];


typedef HashIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 1> stockTblIdx0Type;
typedef MultiHashMap<struct SEntry17_IIISSSSSSSSSSIIIS, char,
   HashIndex<struct SEntry17_IIISSSSSSSSSSIIIS, char, SEntry17_IIISSSSSSSSSSIIIS_Idx12, 1>> stockTblStoreType;
stockTblStoreType  stockTbl(stockTblSize);
stockTblStoreType& x3175 = stockTbl;
stockTblIdx0Type& x850 = * (stockTblIdx0Type *)stockTbl.index[0];
stockTblIdx0Type& stockTblPrimaryIdx = * (stockTblIdx0Type *) stockTbl.index[0];




void DeliveryTx(int x10, date x11, int x12, int x13) {
  int orderIDs[123];
  int x18 = 1;
  while(1) {
    
    int x20 = x18;
    if (!((x20<=(10)))) break; 
    
    int x27 = x18;
    struct SEntry3_III* x15108 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x15108, 0, 1 * sizeof(struct SEntry3_III));
    x15108->_1 = -2147483648; x15108->_2 = x27; x15108->_3 = x12;
    struct SEntry3_III* x10248 = x2211.getCopyDependent(x15108, 1);
    if((x10248!=(NULL))) {
      int x6656 = x10248->_1;
      int x36 = x18;
      orderIDs[(x36-(1))] = x6656;
      x2211.delCopyDependent(x10248);
      int x41 = x18;
      struct SEntry8_IIIITIIB* x15120 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
      memset(x15120, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
      x15120->_1 = x6656; x15120->_2 = x41; x15120->_3 = x12; x15120->_4 = -2147483648; x15120->_5 = 0; x15120->_6 = -2147483648; x15120->_7 = -2147483648; x15120->_8 = 0;
      struct SEntry8_IIIITIIB* x10260 = x2721.getCopyDependent(x15120, 0);
      int x6666 = x10260->_4;
      x10260->_6 = x13;
      x2721.updateCopyDependent(x10260);
      double x51 = 0.0;
      int x53 = x18;
      struct SEntry10_IIIIIITIDS* x15137 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x15137, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x15137->_1 = x6656; x15137->_2 = x53; x15137->_3 = x12; x15137->_4 = -2147483648; x15137->_5 = -2147483648; x15137->_6 = -2147483648; x15137->_7 = 0; x15137->_8 = -2147483648; x15137->_9 = -1.7976931348623157E308; x15137->_10 = PString();
      x2958.sliceCopyDependent(1, x15137, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
        struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
        orderLineEntry->_7 = x11;
        double x58 = x51;
        double x6728 = orderLineEntry->_9;
        x51 = (x58+(x6728));
        x2958.updateCopyDependent(orderLineEntry);
      
      }));
      int x66 = x18;
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15142 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      memset(x15142, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
      x15142->_1 = x6666; x15142->_2 = x66; x15142->_3 = x12; x15142->_4 = PString(); x15142->_5 = PString(); x15142->_6 = PString(); x15142->_7 = PString(); x15142->_8 = PString(); x15142->_9 = PString(); x15142->_10 = PString(); x15142->_11 = PString(); x15142->_12 = PString(); x15142->_13 = 0; x15142->_14 = PString(); x15142->_15 = -1.7976931348623157E308; x15142->_16 = -1.7976931348623157E308; x15142->_17 = -1.7976931348623157E308; x15142->_18 = -1.7976931348623157E308; x15142->_19 = -2147483648; x15142->_20 = -2147483648; x15142->_21 = PString();
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10280 = x3114.getCopyDependent(x15142, 0);
      double x70 = x51;
      double x6680 = x10280->_17;
      x10280->_17 = (x6680+(x70));
      int x6683 = x10280->_20;
      x10280->_20 = (x6683+(1));
      x3114.updateCopyDependent(x10280);
    } else {
      
      int x74 = x18;
      orderIDs[(x74-(1))] = 0;
    };
    int x78 = x18;
    x18 = (x78+(1));
  };
}
void StockLevelTx(int x82, date x83, int x84, int x85, int x86, int x87) {
  struct SEntry11_IISSSSSSDDI* x15160 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x15160, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x15160->_1 = x86; x15160->_2 = x85; x15160->_3 = PString(); x15160->_4 = PString(); x15160->_5 = PString(); x15160->_6 = PString(); x15160->_7 = PString(); x15160->_8 = PString(); x15160->_9 = -1.7976931348623157E308; x15160->_10 = -1.7976931348623157E308; x15160->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x10359 = x2784.getCopyDependent(x15160, 0);
  int x6819 = x10359->_11;
  int x97 = (x6819-(20));
  unordered_set<int> unique_ol_i_id;
  while(1) {
    
    int x101 = x97;
    if (!((x101<(x6819)))) break; 
    
    int x103 = x97;
    struct SEntry10_IIIIIITIDS* x15183 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
    memset(x15183, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
    x15183->_1 = x103; x15183->_2 = x86; x15183->_3 = x85; x15183->_4 = -2147483648; x15183->_5 = -2147483648; x15183->_6 = -2147483648; x15183->_7 = 0; x15183->_8 = -2147483648; x15183->_9 = -1.7976931348623157E308; x15183->_10 = PString();
    x2958.sliceCopyDependent(1, x15183, ([&](const struct SEntry10_IIIIIITIDS&  sliceVar) {
      struct SEntry10_IIIIIITIDS* orderLineEntry = const_cast<struct SEntry10_IIIIIITIDS*>(&sliceVar);
      int x6848 = orderLineEntry->_5;
      struct SEntry17_IIISSSSSSSSSSIIIS* x15174 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x15174, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x15174->_1 = x6848; x15174->_2 = x85; x15174->_3 = -2147483648; x15174->_4 = PString(); x15174->_5 = PString(); x15174->_6 = PString(); x15174->_7 = PString(); x15174->_8 = PString(); x15174->_9 = PString(); x15174->_10 = PString(); x15174->_11 = PString(); x15174->_12 = PString(); x15174->_13 = PString(); x15174->_14 = -2147483648; x15174->_15 = -2147483648; x15174->_16 = -2147483648; x15174->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x10372 = x3175.getCopyDependent(x15174, 0);
      int x6852 = x10372->_3;
      if((x6852<(x87))) {
        unique_ol_i_id.insert(x6848);
      };
    
    }));
    int x120 = x97;
    x97 = (x120+(1));
  };
}
void OrderStatusTx(int x126, date x127, int x128, int x129, int x130, int x131, int x132, PString x133) {
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite14314 = NULL;
  if((x131>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14315;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15197 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x15197, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x15197->_1 = -2147483648; x15197->_2 = x130; x15197->_3 = x129; x15197->_4 = PString(); x15197->_5 = PString(); x15197->_6 = x133; x15197->_7 = PString(); x15197->_8 = PString(); x15197->_9 = PString(); x15197->_10 = PString(); x15197->_11 = PString(); x15197->_12 = PString(); x15197->_13 = 0; x15197->_14 = PString(); x15197->_15 = -1.7976931348623157E308; x15197->_16 = -1.7976931348623157E308; x15197->_17 = -1.7976931348623157E308; x15197->_18 = -1.7976931348623157E308; x15197->_19 = -2147483648; x15197->_20 = -2147483648; x15197->_21 = PString();
    x3114.sliceCopyDependent(1, x15197, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x14315.push_back(custEntry);
    
    }));
    int x14321 = x14315.size();
    int x14323 = (x14321/(2));
    int x14331 = x14315.size();
    if(((x14331%(2))==(0))) {
      int x152 = x14323;
      x14323 = (x152-(1));
    };
    sort(x14315.begin(), x14315.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x6959 = c1->_4;
      PString x6960 = c2->_4;
      return ((strcmpi(x6959.data_, x6960.data_))<(0)); 
    }));
    int x14339 = x14323;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14340 = x14315[x14339];
    ite14314 = x14340;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15222 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x15222, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x15222->_1 = x132; x15222->_2 = x130; x15222->_3 = x129; x15222->_4 = PString(); x15222->_5 = PString(); x15222->_6 = PString(); x15222->_7 = PString(); x15222->_8 = PString(); x15222->_9 = PString(); x15222->_10 = PString(); x15222->_11 = PString(); x15222->_12 = PString(); x15222->_13 = 0; x15222->_14 = PString(); x15222->_15 = -1.7976931348623157E308; x15222->_16 = -1.7976931348623157E308; x15222->_17 = -1.7976931348623157E308; x15222->_18 = -1.7976931348623157E308; x15222->_19 = -2147483648; x15222->_20 = -2147483648; x15222->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14343 = x3114.getCopyDependent(x15222, 0);
    ite14314 = x14343;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x6894 = ite14314;
  int x6895 = x6894->_3;
  struct SEntry8_IIIITIIB* x15229 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
  memset(x15229, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
  x15229->_1 = -2147483648; x15229->_2 = x130; x15229->_3 = x129; x15229->_4 = x6895; x15229->_5 = 0; x15229->_6 = -2147483648; x15229->_7 = -2147483648; x15229->_8 = 0;
  struct SEntry8_IIIITIIB* x10456 = x2721.getCopyDependent(x15229, 1);
  int x184 = 0;
  int x6904 = x10456->_1;
  x184 = x6904;
}
void PaymentTx(int x188, date x189, int x190, int x191, int x192, int x193, int x194, int x195, int x196, PString x197, double x198) {
  struct SEntry9_ISSSSSSDD* x15236 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
  memset(x15236, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
  x15236->_1 = x191; x15236->_2 = PString(); x15236->_3 = PString(); x15236->_4 = PString(); x15236->_5 = PString(); x15236->_6 = PString(); x15236->_7 = PString(); x15236->_8 = -1.7976931348623157E308; x15236->_9 = -1.7976931348623157E308;
  struct SEntry9_ISSSSSSDD* x10509 = x2454.getCopyDependent(x15236, 0);
  double x7040 = x10509->_9;
  x10509->_9 = (x7040+(x198));
  x2454.updateCopyDependent(x10509);
  struct SEntry11_IISSSSSSDDI* x15244 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
  memset(x15244, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
  x15244->_1 = x192; x15244->_2 = x191; x15244->_3 = PString(); x15244->_4 = PString(); x15244->_5 = PString(); x15244->_6 = PString(); x15244->_7 = PString(); x15244->_8 = PString(); x15244->_9 = -1.7976931348623157E308; x15244->_10 = -1.7976931348623157E308; x15244->_11 = -2147483648;
  struct SEntry11_IISSSSSSDDI* x10516 = x2784.getCopyDependent(x15244, 0);
  double x7047 = x10516->_10;
  x10516->_10 = (x7047+(x198));
  x2784.updateCopyDependent(x10516);
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* ite14406 = NULL;
  if((x193>(0))) {
    vector<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*> x14407;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15259 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x15259, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x15259->_1 = -2147483648; x15259->_2 = x195; x15259->_3 = x194; x15259->_4 = PString(); x15259->_5 = PString(); x15259->_6 = x197; x15259->_7 = PString(); x15259->_8 = PString(); x15259->_9 = PString(); x15259->_10 = PString(); x15259->_11 = PString(); x15259->_12 = PString(); x15259->_13 = 0; x15259->_14 = PString(); x15259->_15 = -1.7976931348623157E308; x15259->_16 = -1.7976931348623157E308; x15259->_17 = -1.7976931348623157E308; x15259->_18 = -1.7976931348623157E308; x15259->_19 = -2147483648; x15259->_20 = -2147483648; x15259->_21 = PString();
    x3114.sliceCopyDependent(1, x15259, ([&](const struct SEntry21_IIISSSSSSSSSTSDDDDIIS&  sliceVar) {
      struct SEntry21_IIISSSSSSSSSTSDDDDIIS* custEntry = const_cast<struct SEntry21_IIISSSSSSSSSTSDDDDIIS*>(&sliceVar);
      x14407.push_back(custEntry);
    
    }));
    int x14413 = x14407.size();
    int x14415 = (x14413/(2));
    int x14423 = x14407.size();
    if(((x14423%(2))==(0))) {
      int x230 = x14415;
      x14415 = (x230-(1));
    };
    sort(x14407.begin(), x14407.end(), ([&](struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c1, struct SEntry21_IIISSSSSSSSSTSDDDDIIS* c2) {
      
      PString x7168 = c1->_4;
      PString x7169 = c2->_4;
      return ((strcmpi(x7168.data_, x7169.data_))<(0)); 
    }));
    int x14431 = x14415;
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14432 = x14407[x14431];
    ite14406 = x14432;
  } else {
    
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15284 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x15284, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x15284->_1 = x196; x15284->_2 = x195; x15284->_3 = x194; x15284->_4 = PString(); x15284->_5 = PString(); x15284->_6 = PString(); x15284->_7 = PString(); x15284->_8 = PString(); x15284->_9 = PString(); x15284->_10 = PString(); x15284->_11 = PString(); x15284->_12 = PString(); x15284->_13 = 0; x15284->_14 = PString(); x15284->_15 = -1.7976931348623157E308; x15284->_16 = -1.7976931348623157E308; x15284->_17 = -1.7976931348623157E308; x15284->_18 = -1.7976931348623157E308; x15284->_19 = -2147483648; x15284->_20 = -2147483648; x15284->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x14435 = x3114.getCopyDependent(x15284, 0);
    ite14406 = x14435;
  };
  struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x7052 = ite14406;
  PString x7053 = x7052->_21;
  PString x7054 = x7052->_14;
  char* x15743 = strstr(x7054.data_, "BC");
  if((x15743!=(NULL))) {
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
  x3114.updateCopyDependent(x7052);
  PString x7068 = x10509->_2;
  PString x7069 = x10516->_3;
  PString h_data(24);
  snprintf(h_data.data_, 25, "%.10s    %.10s", x7068.data_, x7069.data_);
  int x7072 = x7052->_1;
  struct SEntry8_IIIIITDS* x15310 = (struct SEntry8_IIIIITDS*)malloc(1 * sizeof(struct SEntry8_IIIIITDS));
  memset(x15310, 0, 1 * sizeof(struct SEntry8_IIIIITDS));
  x15310->_1 = x7072; x15310->_2 = x195; x15310->_3 = x194; x15310->_4 = x192; x15310->_5 = x191; x15310->_6 = x189; x15310->_7 = x198; x15310->_8 = h_data;
  x2412.add(x15310);
}
void NewOrderTx(int x272, date x273, int x274, int x275, int x276, int x277, int x278, int x279, int* x280, int* x281, int* x282, double* x283, PString* x284, int* x285, PString* x286, double* x287) {
  int x289 = 0;
  int x292 = 0;
  PString idata[x278];
  int x297 = 1;
  while(1) {
    
    int x299 = x289;
    int ite14706 = 0;
    if((x299<(x278))) {
      
      int x301 = x297;
      int x14707 = x301;
      ite14706 = x14707;
    } else {
      
      ite14706 = 0;
    };
    int x14536 = ite14706;
    if (!(x14536)) break; 
    
    int x304 = x289;
    int x305 = x280[x304];
    struct SEntry5_IISDS* x15330 = (struct SEntry5_IISDS*)malloc(1 * sizeof(struct SEntry5_IISDS));
    memset(x15330, 0, 1 * sizeof(struct SEntry5_IISDS));
    x15330->_1 = x305; x15330->_2 = -2147483648; x15330->_3 = PString(); x15330->_4 = -1.7976931348623157E308; x15330->_5 = PString();
    struct SEntry5_IISDS* x10660 = x2495.getCopyDependent(x15330, 0);
    if((x10660==(NULL))) {
      x297 = 0;
    } else {
      
      int x312 = x289;
      PString x7297 = x10660->_3;
      x284[x312] = x7297;
      int x315 = x289;
      double x7300 = x10660->_4;
      x283[x315] = x7300;
      int x318 = x289;
      PString x7303 = x10660->_5;
      idata[x318] = x7303;
    };
    int x322 = x289;
    x289 = (x322+(1));
  };
  int x326 = x297;
  if(x326) {
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x15351 = (struct SEntry21_IIISSSSSSSSSTSDDDDIIS*)malloc(1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    memset(x15351, 0, 1 * sizeof(struct SEntry21_IIISSSSSSSSSTSDDDDIIS));
    x15351->_1 = x277; x15351->_2 = x276; x15351->_3 = x275; x15351->_4 = PString(); x15351->_5 = PString(); x15351->_6 = PString(); x15351->_7 = PString(); x15351->_8 = PString(); x15351->_9 = PString(); x15351->_10 = PString(); x15351->_11 = PString(); x15351->_12 = PString(); x15351->_13 = 0; x15351->_14 = PString(); x15351->_15 = -1.7976931348623157E308; x15351->_16 = -1.7976931348623157E308; x15351->_17 = -1.7976931348623157E308; x15351->_18 = -1.7976931348623157E308; x15351->_19 = -2147483648; x15351->_20 = -2147483648; x15351->_21 = PString();
    struct SEntry21_IIISSSSSSSSSTSDDDDIIS* x10681 = x3114.getCopyDependent(x15351, 0);
    struct SEntry9_ISSSSSSDD* x15355 = (struct SEntry9_ISSSSSSDD*)malloc(1 * sizeof(struct SEntry9_ISSSSSSDD));
    memset(x15355, 0, 1 * sizeof(struct SEntry9_ISSSSSSDD));
    x15355->_1 = x275; x15355->_2 = PString(); x15355->_3 = PString(); x15355->_4 = PString(); x15355->_5 = PString(); x15355->_6 = PString(); x15355->_7 = PString(); x15355->_8 = -1.7976931348623157E308; x15355->_9 = -1.7976931348623157E308;
    struct SEntry9_ISSSSSSDD* x10684 = x2454.getCopyDependent(x15355, 0);
    struct SEntry11_IISSSSSSDDI* x15359 = (struct SEntry11_IISSSSSSDDI*)malloc(1 * sizeof(struct SEntry11_IISSSSSSDDI));
    memset(x15359, 0, 1 * sizeof(struct SEntry11_IISSSSSSDDI));
    x15359->_1 = x276; x15359->_2 = x275; x15359->_3 = PString(); x15359->_4 = PString(); x15359->_5 = PString(); x15359->_6 = PString(); x15359->_7 = PString(); x15359->_8 = PString(); x15359->_9 = -1.7976931348623157E308; x15359->_10 = -1.7976931348623157E308; x15359->_11 = -2147483648;
    struct SEntry11_IISSSSSSDDI* x10687 = x2784.getCopyDependent(x15359, 0);
    int x7320 = x10687->_11;
    int x7321 = x10687->_11;
    x10687->_11 = (x7321+(1));
    x2784.updateCopyDependent(x10687);
    struct SEntry8_IIIITIIB* x15369 = (struct SEntry8_IIIITIIB*)malloc(1 * sizeof(struct SEntry8_IIIITIIB));
    memset(x15369, 0, 1 * sizeof(struct SEntry8_IIIITIIB));
    x15369->_1 = x7320; x15369->_2 = x276; x15369->_3 = x275; x15369->_4 = x277; x15369->_5 = x273; x15369->_6 = -1; x15369->_7 = x278; x15369->_8 = (x279>(0));
    x2721.add(x15369);
    struct SEntry3_III* x15373 = (struct SEntry3_III*)malloc(1 * sizeof(struct SEntry3_III));
    memset(x15373, 0, 1 * sizeof(struct SEntry3_III));
    x15373->_1 = x7320; x15373->_2 = x276; x15373->_3 = x275;
    x2211.add(x15373);
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
      struct SEntry17_IIISSSSSSSSSSIIIS* x15388 = (struct SEntry17_IIISSSSSSSSSSIIIS*)malloc(1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      memset(x15388, 0, 1 * sizeof(struct SEntry17_IIISSSSSSSSSSIIIS));
      x15388->_1 = ol_i_id; x15388->_2 = ol_supply_w_id; x15388->_3 = -2147483648; x15388->_4 = PString(); x15388->_5 = PString(); x15388->_6 = PString(); x15388->_7 = PString(); x15388->_8 = PString(); x15388->_9 = PString(); x15388->_10 = PString(); x15388->_11 = PString(); x15388->_12 = PString(); x15388->_13 = PString(); x15388->_14 = -2147483648; x15388->_15 = -2147483648; x15388->_16 = -2147483648; x15388->_17 = PString();
      struct SEntry17_IIISSSSSSSSSSIIIS* x10713 = x3175.getCopyDependent(x15388, 0);
      PString ite14589 = PString();
      if((x276==(1))) {
        PString x14590 = x10713->_4;
        ite14589 = x14590;
      } else {
        
        PString ite14594 = PString();
        if((x276==(2))) {
          PString x14595 = x10713->_5;
          ite14594 = x14595;
        } else {
          
          PString ite14599 = PString();
          if((x276==(3))) {
            PString x14600 = x10713->_6;
            ite14599 = x14600;
          } else {
            
            PString ite14604 = PString();
            if((x276==(4))) {
              PString x14605 = x10713->_7;
              ite14604 = x14605;
            } else {
              
              PString ite14609 = PString();
              if((x276==(5))) {
                PString x14610 = x10713->_8;
                ite14609 = x14610;
              } else {
                
                PString ite14614 = PString();
                if((x276==(6))) {
                  PString x14615 = x10713->_9;
                  ite14614 = x14615;
                } else {
                  
                  PString ite14619 = PString();
                  if((x276==(7))) {
                    PString x14620 = x10713->_10;
                    ite14619 = x14620;
                  } else {
                    
                    PString ite14624 = PString();
                    if((x276==(8))) {
                      PString x14625 = x10713->_11;
                      ite14624 = x14625;
                    } else {
                      
                      PString ite14629 = PString();
                      if((x276==(9))) {
                        PString x14630 = x10713->_12;
                        ite14629 = x14630;
                      } else {
                        
                        PString x14632 = x10713->_13;
                        ite14629 = x14632;
                      };
                      PString x14628 = ite14629;
                      ite14624 = x14628;
                    };
                    PString x14623 = ite14624;
                    ite14619 = x14623;
                  };
                  PString x14618 = ite14619;
                  ite14614 = x14618;
                };
                PString x14613 = ite14614;
                ite14609 = x14613;
              };
              PString x14608 = ite14609;
              ite14604 = x14608;
            };
            PString x14603 = ite14604;
            ite14599 = x14603;
          };
          PString x14598 = ite14599;
          ite14594 = x14598;
        };
        PString x14593 = ite14594;
        ite14589 = x14593;
      };
      PString ol_dist_info = ite14589;
      int x7374 = x10713->_3;
      int x401 = x289;
      x285[x401] = x7374;
      PString x7377 = x10681->_14;
      char* x15991 = strstr(x7377.data_, "original");
      int ite14832 = 0;
      if((x15991!=(NULL))) {
        
        PString x7380 = x10713->_17;
        char* x15997 = strstr(x7380.data_, "original");
        int x14833 = (x15997!=(NULL));
        ite14832 = x14833;
      } else {
        
        ite14832 = 0;
      };
      int x14657 = ite14832;
      if(x14657) {
        int x408 = x289;
        x286[x408] = "B";
      } else {
        
        int x410 = x289;
        x286[x410] = "G";
      };
      x10713->_3 = (x7374-(ol_quantity));
      if((x7374<=(ol_quantity))) {
        int x7391 = x10713->_3;
        x10713->_3 = (x7391+(91));
      };
      int x419 = 0;
      if((ol_supply_w_id!=(x275))) {
        x419 = 1;
      };
      x3175.updateCopyDependent(x10713);
      double x7399 = x10681->_16;
      double x7400 = x10684->_8;
      double x7401 = x10687->_9;
      int x432 = x289;
      double x433 = x283[x432];
      double ol_amount = ((ol_quantity*(x433))*(((1.0+(x7400))+(x7401))))*((1.0-(x7399)));
      int x441 = x289;
      x287[x441] = ol_amount;
      double x443 = x352;
      x352 = (x443+(ol_amount));
      int x446 = x289;
      struct SEntry10_IIIIIITIDS* x15504 = (struct SEntry10_IIIIIITIDS*)malloc(1 * sizeof(struct SEntry10_IIIIIITIDS));
      memset(x15504, 0, 1 * sizeof(struct SEntry10_IIIIIITIDS));
      x15504->_1 = x7320; x15504->_2 = x276; x15504->_3 = x275; x15504->_4 = (x446+(1)); x15504->_5 = ol_i_id; x15504->_6 = ol_supply_w_id; x15504->_7 = NULL; x15504->_8 = ol_quantity; x15504->_9 = ol_amount; x15504->_10 = ol_dist_info;
      x2958.add(x15504);
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
