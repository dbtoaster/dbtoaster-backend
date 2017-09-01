#include <sys/time.h>
#include "macro.hpp"
#include "types.hpp"
#include "functions.hpp"
#include "hash.hpp"
#include "hashmap.hpp"
#include "serialization.hpp"

#define ELEM_SEPARATOR "\n\t\t\t"

namespace dbtoaster {
  
  /* Definitions of auxiliary maps for storing materialized views. */
  struct DATE_DIM_entry {
    long DATE_DIM_D_DATE_SK; STRING_TYPE DATE_DIM_D_DATE_ID; date DATE_DIM_D_DATE; long DATE_DIM_D_MONTH_SEQ; long DATE_DIM_D_WEEK_SEQ; long DATE_DIM_D_QUARTER_SEQ; long DATE_DIM_D_YEAR; long DATE_DIM_D_DOW; long DATE_DIM_D_MOY; long DATE_DIM_D_DOM; long DATE_DIM_D_QOY; long DATE_DIM_D_FY_YEAR; long DATE_DIM_D_FY_QUARTER_SEQ; long DATE_DIM_D_FY_WEEK_SEQ; STRING_TYPE DATE_DIM_D_DAY_NAME; STRING_TYPE DATE_DIM_D_QUARTER_NAME; STRING_TYPE DATE_DIM_D_HOLIDAY; STRING_TYPE DATE_DIM_D_WEEKEND; STRING_TYPE DATE_DIM_D_FOLLOWING_HOLIDAY; long DATE_DIM_D_FIRST_DOM; long DATE_DIM_D_LAST_DOM; long DATE_DIM_D_SAME_DAY_LY; long DATE_DIM_D_SAME_DAY_LQ; STRING_TYPE DATE_DIM_D_CURRENT_DAY; STRING_TYPE DATE_DIM_D_CURRENT_WEEK; STRING_TYPE DATE_DIM_D_CURRENT_MONTH; STRING_TYPE DATE_DIM_D_CURRENT_QUARTER; STRING_TYPE DATE_DIM_D_CURRENT_YEAR; long __av; 
    explicit DATE_DIM_entry() { /*DATE_DIM_D_DATE_SK = 0L; DATE_DIM_D_DATE_ID = ""; DATE_DIM_D_DATE = 00000000; DATE_DIM_D_MONTH_SEQ = 0L; DATE_DIM_D_WEEK_SEQ = 0L; DATE_DIM_D_QUARTER_SEQ = 0L; DATE_DIM_D_YEAR = 0L; DATE_DIM_D_DOW = 0L; DATE_DIM_D_MOY = 0L; DATE_DIM_D_DOM = 0L; DATE_DIM_D_QOY = 0L; DATE_DIM_D_FY_YEAR = 0L; DATE_DIM_D_FY_QUARTER_SEQ = 0L; DATE_DIM_D_FY_WEEK_SEQ = 0L; DATE_DIM_D_DAY_NAME = ""; DATE_DIM_D_QUARTER_NAME = ""; DATE_DIM_D_HOLIDAY = ""; DATE_DIM_D_WEEKEND = ""; DATE_DIM_D_FOLLOWING_HOLIDAY = ""; DATE_DIM_D_FIRST_DOM = 0L; DATE_DIM_D_LAST_DOM = 0L; DATE_DIM_D_SAME_DAY_LY = 0L; DATE_DIM_D_SAME_DAY_LQ = 0L; DATE_DIM_D_CURRENT_DAY = ""; DATE_DIM_D_CURRENT_WEEK = ""; DATE_DIM_D_CURRENT_MONTH = ""; DATE_DIM_D_CURRENT_QUARTER = ""; DATE_DIM_D_CURRENT_YEAR = ""; __av = 0L; */ }
    explicit DATE_DIM_entry(const long c0, const STRING_TYPE& c1, const date c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const long c19, const long c20, const long c21, const long c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const STRING_TYPE& c27, const long c28) { DATE_DIM_D_DATE_SK = c0; DATE_DIM_D_DATE_ID = c1; DATE_DIM_D_DATE = c2; DATE_DIM_D_MONTH_SEQ = c3; DATE_DIM_D_WEEK_SEQ = c4; DATE_DIM_D_QUARTER_SEQ = c5; DATE_DIM_D_YEAR = c6; DATE_DIM_D_DOW = c7; DATE_DIM_D_MOY = c8; DATE_DIM_D_DOM = c9; DATE_DIM_D_QOY = c10; DATE_DIM_D_FY_YEAR = c11; DATE_DIM_D_FY_QUARTER_SEQ = c12; DATE_DIM_D_FY_WEEK_SEQ = c13; DATE_DIM_D_DAY_NAME = c14; DATE_DIM_D_QUARTER_NAME = c15; DATE_DIM_D_HOLIDAY = c16; DATE_DIM_D_WEEKEND = c17; DATE_DIM_D_FOLLOWING_HOLIDAY = c18; DATE_DIM_D_FIRST_DOM = c19; DATE_DIM_D_LAST_DOM = c20; DATE_DIM_D_SAME_DAY_LY = c21; DATE_DIM_D_SAME_DAY_LQ = c22; DATE_DIM_D_CURRENT_DAY = c23; DATE_DIM_D_CURRENT_WEEK = c24; DATE_DIM_D_CURRENT_MONTH = c25; DATE_DIM_D_CURRENT_QUARTER = c26; DATE_DIM_D_CURRENT_YEAR = c27; __av = c28; }
    DATE_DIM_entry(const DATE_DIM_entry& other) : DATE_DIM_D_DATE_SK( other.DATE_DIM_D_DATE_SK ), DATE_DIM_D_DATE_ID( other.DATE_DIM_D_DATE_ID ), DATE_DIM_D_DATE( other.DATE_DIM_D_DATE ), DATE_DIM_D_MONTH_SEQ( other.DATE_DIM_D_MONTH_SEQ ), DATE_DIM_D_WEEK_SEQ( other.DATE_DIM_D_WEEK_SEQ ), DATE_DIM_D_QUARTER_SEQ( other.DATE_DIM_D_QUARTER_SEQ ), DATE_DIM_D_YEAR( other.DATE_DIM_D_YEAR ), DATE_DIM_D_DOW( other.DATE_DIM_D_DOW ), DATE_DIM_D_MOY( other.DATE_DIM_D_MOY ), DATE_DIM_D_DOM( other.DATE_DIM_D_DOM ), DATE_DIM_D_QOY( other.DATE_DIM_D_QOY ), DATE_DIM_D_FY_YEAR( other.DATE_DIM_D_FY_YEAR ), DATE_DIM_D_FY_QUARTER_SEQ( other.DATE_DIM_D_FY_QUARTER_SEQ ), DATE_DIM_D_FY_WEEK_SEQ( other.DATE_DIM_D_FY_WEEK_SEQ ), DATE_DIM_D_DAY_NAME( other.DATE_DIM_D_DAY_NAME ), DATE_DIM_D_QUARTER_NAME( other.DATE_DIM_D_QUARTER_NAME ), DATE_DIM_D_HOLIDAY( other.DATE_DIM_D_HOLIDAY ), DATE_DIM_D_WEEKEND( other.DATE_DIM_D_WEEKEND ), DATE_DIM_D_FOLLOWING_HOLIDAY( other.DATE_DIM_D_FOLLOWING_HOLIDAY ), DATE_DIM_D_FIRST_DOM( other.DATE_DIM_D_FIRST_DOM ), DATE_DIM_D_LAST_DOM( other.DATE_DIM_D_LAST_DOM ), DATE_DIM_D_SAME_DAY_LY( other.DATE_DIM_D_SAME_DAY_LY ), DATE_DIM_D_SAME_DAY_LQ( other.DATE_DIM_D_SAME_DAY_LQ ), DATE_DIM_D_CURRENT_DAY( other.DATE_DIM_D_CURRENT_DAY ), DATE_DIM_D_CURRENT_WEEK( other.DATE_DIM_D_CURRENT_WEEK ), DATE_DIM_D_CURRENT_MONTH( other.DATE_DIM_D_CURRENT_MONTH ), DATE_DIM_D_CURRENT_QUARTER( other.DATE_DIM_D_CURRENT_QUARTER ), DATE_DIM_D_CURRENT_YEAR( other.DATE_DIM_D_CURRENT_YEAR ), __av( other.__av ) {}
    FORCE_INLINE DATE_DIM_entry& modify(const long c0, const STRING_TYPE& c1, const date c2, const long c3, const long c4, const long c5, const long c6, const long c7, const long c8, const long c9, const long c10, const long c11, const long c12, const long c13, const STRING_TYPE& c14, const STRING_TYPE& c15, const STRING_TYPE& c16, const STRING_TYPE& c17, const STRING_TYPE& c18, const long c19, const long c20, const long c21, const long c22, const STRING_TYPE& c23, const STRING_TYPE& c24, const STRING_TYPE& c25, const STRING_TYPE& c26, const STRING_TYPE& c27) { DATE_DIM_D_DATE_SK = c0; DATE_DIM_D_DATE_ID = c1; DATE_DIM_D_DATE = c2; DATE_DIM_D_MONTH_SEQ = c3; DATE_DIM_D_WEEK_SEQ = c4; DATE_DIM_D_QUARTER_SEQ = c5; DATE_DIM_D_YEAR = c6; DATE_DIM_D_DOW = c7; DATE_DIM_D_MOY = c8; DATE_DIM_D_DOM = c9; DATE_DIM_D_QOY = c10; DATE_DIM_D_FY_YEAR = c11; DATE_DIM_D_FY_QUARTER_SEQ = c12; DATE_DIM_D_FY_WEEK_SEQ = c13; DATE_DIM_D_DAY_NAME = c14; DATE_DIM_D_QUARTER_NAME = c15; DATE_DIM_D_HOLIDAY = c16; DATE_DIM_D_WEEKEND = c17; DATE_DIM_D_FOLLOWING_HOLIDAY = c18; DATE_DIM_D_FIRST_DOM = c19; DATE_DIM_D_LAST_DOM = c20; DATE_DIM_D_SAME_DAY_LY = c21; DATE_DIM_D_SAME_DAY_LQ = c22; DATE_DIM_D_CURRENT_DAY = c23; DATE_DIM_D_CURRENT_WEEK = c24; DATE_DIM_D_CURRENT_MONTH = c25; DATE_DIM_D_CURRENT_QUARTER = c26; DATE_DIM_D_CURRENT_YEAR = c27;  return *this; }
    FORCE_INLINE DATE_DIM_entry& modify7(const long c7) { DATE_DIM_D_DOW = c7;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_MONTH_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_WEEK_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QUARTER_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DOW);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_MOY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QOY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_QUARTER_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FY_WEEK_SEQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_DAY_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_QUARTER_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_HOLIDAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_WEEKEND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FOLLOWING_HOLIDAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_FIRST_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_LAST_DOM);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_SAME_DAY_LY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_SAME_DAY_LQ);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_DAY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_WEEK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_MONTH);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_QUARTER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DATE_DIM_D_CURRENT_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DATE_SK);
      hash_combine(h, e.DATE_DIM_D_DATE_ID);
      hash_combine(h, e.DATE_DIM_D_DATE);
      hash_combine(h, e.DATE_DIM_D_MONTH_SEQ);
      hash_combine(h, e.DATE_DIM_D_WEEK_SEQ);
      hash_combine(h, e.DATE_DIM_D_QUARTER_SEQ);
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_DOW);
      hash_combine(h, e.DATE_DIM_D_MOY);
      hash_combine(h, e.DATE_DIM_D_DOM);
      hash_combine(h, e.DATE_DIM_D_QOY);
      hash_combine(h, e.DATE_DIM_D_FY_YEAR);
      hash_combine(h, e.DATE_DIM_D_FY_QUARTER_SEQ);
      hash_combine(h, e.DATE_DIM_D_FY_WEEK_SEQ);
      hash_combine(h, e.DATE_DIM_D_DAY_NAME);
      hash_combine(h, e.DATE_DIM_D_QUARTER_NAME);
      hash_combine(h, e.DATE_DIM_D_HOLIDAY);
      hash_combine(h, e.DATE_DIM_D_WEEKEND);
      hash_combine(h, e.DATE_DIM_D_FOLLOWING_HOLIDAY);
      hash_combine(h, e.DATE_DIM_D_FIRST_DOM);
      hash_combine(h, e.DATE_DIM_D_LAST_DOM);
      hash_combine(h, e.DATE_DIM_D_SAME_DAY_LY);
      hash_combine(h, e.DATE_DIM_D_SAME_DAY_LQ);
      hash_combine(h, e.DATE_DIM_D_CURRENT_DAY);
      hash_combine(h, e.DATE_DIM_D_CURRENT_WEEK);
      hash_combine(h, e.DATE_DIM_D_CURRENT_MONTH);
      hash_combine(h, e.DATE_DIM_D_CURRENT_QUARTER);
      hash_combine(h, e.DATE_DIM_D_CURRENT_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_DATE_SK == y.DATE_DIM_D_DATE_SK && x.DATE_DIM_D_DATE_ID == y.DATE_DIM_D_DATE_ID && x.DATE_DIM_D_DATE == y.DATE_DIM_D_DATE && x.DATE_DIM_D_MONTH_SEQ == y.DATE_DIM_D_MONTH_SEQ && x.DATE_DIM_D_WEEK_SEQ == y.DATE_DIM_D_WEEK_SEQ && x.DATE_DIM_D_QUARTER_SEQ == y.DATE_DIM_D_QUARTER_SEQ && x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_DOW == y.DATE_DIM_D_DOW && x.DATE_DIM_D_MOY == y.DATE_DIM_D_MOY && x.DATE_DIM_D_DOM == y.DATE_DIM_D_DOM && x.DATE_DIM_D_QOY == y.DATE_DIM_D_QOY && x.DATE_DIM_D_FY_YEAR == y.DATE_DIM_D_FY_YEAR && x.DATE_DIM_D_FY_QUARTER_SEQ == y.DATE_DIM_D_FY_QUARTER_SEQ && x.DATE_DIM_D_FY_WEEK_SEQ == y.DATE_DIM_D_FY_WEEK_SEQ && x.DATE_DIM_D_DAY_NAME == y.DATE_DIM_D_DAY_NAME && x.DATE_DIM_D_QUARTER_NAME == y.DATE_DIM_D_QUARTER_NAME && x.DATE_DIM_D_HOLIDAY == y.DATE_DIM_D_HOLIDAY && x.DATE_DIM_D_WEEKEND == y.DATE_DIM_D_WEEKEND && x.DATE_DIM_D_FOLLOWING_HOLIDAY == y.DATE_DIM_D_FOLLOWING_HOLIDAY && x.DATE_DIM_D_FIRST_DOM == y.DATE_DIM_D_FIRST_DOM && x.DATE_DIM_D_LAST_DOM == y.DATE_DIM_D_LAST_DOM && x.DATE_DIM_D_SAME_DAY_LY == y.DATE_DIM_D_SAME_DAY_LY && x.DATE_DIM_D_SAME_DAY_LQ == y.DATE_DIM_D_SAME_DAY_LQ && x.DATE_DIM_D_CURRENT_DAY == y.DATE_DIM_D_CURRENT_DAY && x.DATE_DIM_D_CURRENT_WEEK == y.DATE_DIM_D_CURRENT_WEEK && x.DATE_DIM_D_CURRENT_MONTH == y.DATE_DIM_D_CURRENT_MONTH && x.DATE_DIM_D_CURRENT_QUARTER == y.DATE_DIM_D_CURRENT_QUARTER && x.DATE_DIM_D_CURRENT_YEAR == y.DATE_DIM_D_CURRENT_YEAR;
    }
  };
  
  struct DATE_DIM_mapkey7_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_DOW);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_DOW == y.DATE_DIM_D_DOW;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey7_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey7_idxfn,false> HashIndex_DATE_DIM_map_7;
  
  struct HOUSEHOLD_DEMOGRAPHICS_entry {
    long HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK; long HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK; STRING_TYPE HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL; long HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT; long HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT; long __av; 
    explicit HOUSEHOLD_DEMOGRAPHICS_entry() { /*HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = ""; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = 0L; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = 0L; __av = 0L; */ }
    explicit HOUSEHOLD_DEMOGRAPHICS_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4, const long c5) { HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = c0; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = c1; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = c2; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = c3; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = c4; __av = c5; }
    HOUSEHOLD_DEMOGRAPHICS_entry(const HOUSEHOLD_DEMOGRAPHICS_entry& other) : HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK( other.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK ), HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK( other.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK ), HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL( other.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL ), HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT( other.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT ), HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT( other.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT ), __av( other.__av ) {}
    FORCE_INLINE HOUSEHOLD_DEMOGRAPHICS_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const long c4) { HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK = c0; HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK = c1; HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL = c2; HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT = c3; HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT = c4;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const HOUSEHOLD_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT);
      hash_combine(h, e.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const HOUSEHOLD_DEMOGRAPHICS_entry& x, const HOUSEHOLD_DEMOGRAPHICS_entry& y) {
      return x.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK == y.HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK && x.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK == y.HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK && x.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL == y.HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL && x.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT == y.HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT && x.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT == y.HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
    }
  };
  
  typedef MultiHashMap<HOUSEHOLD_DEMOGRAPHICS_entry,long,
    HashIndex<HOUSEHOLD_DEMOGRAPHICS_entry,long,HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn,true>
  > HOUSEHOLD_DEMOGRAPHICS_map;
  typedef HashIndex<HOUSEHOLD_DEMOGRAPHICS_entry,long,HOUSEHOLD_DEMOGRAPHICS_mapkey01234_idxfn,true> HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234;
  
  struct COUNT_entry {
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE __SQL_EXPRESSION_1; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE MS_AMT; DOUBLE_TYPE MS_PROFIT; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; __SQL_EXPRESSION_1 = ""; MS_SS_TICKET_NUMBER = 0L; MS_AMT = 0.0; MS_PROFIT = 0.0; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, const long c6) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; __SQL_EXPRESSION_1 = c2; MS_SS_TICKET_NUMBER = c3; MS_AMT = c4; MS_PROFIT = c5; __av = c6; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), __SQL_EXPRESSION_1( other.__SQL_EXPRESSION_1 ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_AMT( other.MS_AMT ), MS_PROFIT( other.MS_PROFIT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; __SQL_EXPRESSION_1 = c2; MS_SS_TICKET_NUMBER = c3; MS_AMT = c4; MS_PROFIT = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __SQL_EXPRESSION_1);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_AMT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_PROFIT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.__SQL_EXPRESSION_1);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_AMT);
      hash_combine(h, e.MS_PROFIT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.__SQL_EXPRESSION_1 == y.__SQL_EXPRESSION_1 && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_AMT == y.MS_AMT && x.MS_PROFIT == y.MS_PROFIT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true> HashIndex_COUNT_map_012345;
  
  struct COUNTSTORE1_E2_5_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long COUNTSTORESTORE_S_STORE_SK; long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE1_E2_5_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; COUNTSTORESTORE_S_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE1_E2_5_entry(const long c0, const long c1, const long c2, const long c3, const long c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE1_E2_5_entry(const COUNTSTORE1_E2_5_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), COUNTSTORESTORE_S_STORE_SK( other.COUNTSTORESTORE_S_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE1_E2_5_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE1_E2_5_entry& modify02(const long c0, const long c2) { CUSTOMER_C_CUSTOMER_SK = c0; COUNTSTORESTORE_S_STORE_SK = c2;  return *this; }
    FORCE_INLINE COUNTSTORE1_E2_5_entry& modify2(const long c2) { COUNTSTORESTORE_S_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE1_E2_5_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E2_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E2_5_entry& x, const COUNTSTORE1_E2_5_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE1_E2_5_mapkey02_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E2_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E2_5_entry& x, const COUNTSTORE1_E2_5_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK;
    }
  };
  
  struct COUNTSTORE1_E2_5_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE1_E2_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE1_E2_5_entry& x, const COUNTSTORE1_E2_5_entry& y) {
      return x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE1_E2_5_entry,long,
    HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey02_idxfn,false>,
    HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey2_idxfn,false>
  > COUNTSTORE1_E2_5_map;
  typedef HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey0123_idxfn,true> HashIndex_COUNTSTORE1_E2_5_map_0123;
  typedef HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey02_idxfn,false> HashIndex_COUNTSTORE1_E2_5_map_02;
  typedef HashIndex<COUNTSTORE1_E2_5_entry,long,COUNTSTORE1_E2_5_mapkey2_idxfn,false> HashIndex_COUNTSTORE1_E2_5_map_2;
  
  struct COUNTSTORE7_E1_1_entry {
    STRING_TYPE COUNTSTORESTORE_S_CITY; long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; long __av; 
    explicit COUNTSTORE7_E1_1_entry() { /*COUNTSTORESTORE_S_CITY = ""; CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTSTORE7_E1_1_entry(const STRING_TYPE& c0, const long c1, const long c2, const long c3, const long c4) { COUNTSTORESTORE_S_CITY = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE7_E1_1_entry(const COUNTSTORE7_E1_1_entry& other) : COUNTSTORESTORE_S_CITY( other.COUNTSTORESTORE_S_CITY ), CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE7_E1_1_entry& modify(const STRING_TYPE& c0, const long c1, const long c2, const long c3) { COUNTSTORESTORE_S_CITY = c0; CUSTOMER_C_CUSTOMER_SK = c1; STORE_SALES_SS_ADDR_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE7_E1_1_entry& modify01(const STRING_TYPE& c0, const long c1) { COUNTSTORESTORE_S_CITY = c0; CUSTOMER_C_CUSTOMER_SK = c1;  return *this; }
    FORCE_INLINE COUNTSTORE7_E1_1_entry& modify0(const STRING_TYPE& c0) { COUNTSTORESTORE_S_CITY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE7_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_E1_1_entry& x, const COUNTSTORE7_E1_1_entry& y) {
      return x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE7_E1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_E1_1_entry& x, const COUNTSTORE7_E1_1_entry& y) {
      return x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY && x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  struct COUNTSTORE7_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_E1_1_entry& x, const COUNTSTORE7_E1_1_entry& y) {
      return x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE7_E1_1_entry,long,
    HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey01_idxfn,false>,
    HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey0_idxfn,false>
  > COUNTSTORE7_E1_1_map;
  typedef HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey0123_idxfn,true> HashIndex_COUNTSTORE7_E1_1_map_0123;
  typedef HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey01_idxfn,false> HashIndex_COUNTSTORE7_E1_1_map_01;
  typedef HashIndex<COUNTSTORE7_E1_1_entry,long,COUNTSTORE7_E1_1_mapkey0_idxfn,false> HashIndex_COUNTSTORE7_E1_1_map_0;
  
  struct COUNTSTORE7_E1_1STORE_SALES2_entry {
    long COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK; STRING_TYPE COUNTSTORESTORE_S_CITY; long __av; 
    explicit COUNTSTORE7_E1_1STORE_SALES2_entry() { /*COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK = 0L; COUNTSTORESTORE_S_CITY = ""; __av = 0L; */ }
    explicit COUNTSTORE7_E1_1STORE_SALES2_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK = c0; COUNTSTORESTORE_S_CITY = c1; __av = c2; }
    COUNTSTORE7_E1_1STORE_SALES2_entry(const COUNTSTORE7_E1_1STORE_SALES2_entry& other) : COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK( other.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK ), COUNTSTORESTORE_S_CITY( other.COUNTSTORESTORE_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE7_E1_1STORE_SALES2_entry& modify(const long c0, const STRING_TYPE& c1) { COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK = c0; COUNTSTORESTORE_S_CITY = c1;  return *this; }
    FORCE_INLINE COUNTSTORE7_E1_1STORE_SALES2_entry& modify0(const long c0) { COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE7_E1_1STORE_SALES2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_E1_1STORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_E1_1STORE_SALES2_entry& x, const COUNTSTORE7_E1_1STORE_SALES2_entry& y) {
      return x.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK == y.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK && x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY;
    }
  };
  
  struct COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_E1_1STORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_E1_1STORE_SALES2_entry& x, const COUNTSTORE7_E1_1STORE_SALES2_entry& y) {
      return x.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK == y.COUNTSTORE7_E1_1STORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE7_E1_1STORE_SALES2_entry,long,
    HashIndex<COUNTSTORE7_E1_1STORE_SALES2_entry,long,COUNTSTORE7_E1_1STORE_SALES2_mapkey01_idxfn,true>,
    HashIndex<COUNTSTORE7_E1_1STORE_SALES2_entry,long,COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn,false>
  > COUNTSTORE7_E1_1STORE_SALES2_map;
  typedef HashIndex<COUNTSTORE7_E1_1STORE_SALES2_entry,long,COUNTSTORE7_E1_1STORE_SALES2_mapkey01_idxfn,true> HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_01;
  typedef HashIndex<COUNTSTORE7_E1_1STORE_SALES2_entry,long,COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn,false> HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0;
  
  struct COUNTSTORE7_L2_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; STRING_TYPE COUNTSTORESTORE_S_CITY; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE7_L2_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; COUNTSTORESTORE_S_CITY = ""; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE7_L2_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_CITY = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE7_L2_1_entry(const COUNTSTORE7_L2_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), COUNTSTORESTORE_S_CITY( other.COUNTSTORESTORE_S_CITY ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE7_L2_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_CITY = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE7_L2_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_L2_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_L2_1_entry& x, const COUNTSTORE7_L2_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE7_L2_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE7_L2_1_entry,DOUBLE_TYPE,COUNTSTORE7_L2_1_mapkey0123_idxfn,true>
  > COUNTSTORE7_L2_1_map;
  typedef HashIndex<COUNTSTORE7_L2_1_entry,DOUBLE_TYPE,COUNTSTORE7_L2_1_mapkey0123_idxfn,true> HashIndex_COUNTSTORE7_L2_1_map_0123;
  
  struct COUNTSTORE7_L3_1_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; STRING_TYPE COUNTSTORESTORE_S_CITY; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE7_L3_1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; COUNTSTORESTORE_S_CITY = ""; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE7_L3_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_CITY = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE7_L3_1_entry(const COUNTSTORE7_L3_1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), COUNTSTORESTORE_S_CITY( other.COUNTSTORESTORE_S_CITY ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE7_L3_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_CITY = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE7_L3_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE7_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_CITY);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE7_L3_1_entry& x, const COUNTSTORE7_L3_1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.COUNTSTORESTORE_S_CITY == y.COUNTSTORESTORE_S_CITY && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE7_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE7_L3_1_entry,DOUBLE_TYPE,COUNTSTORE7_L3_1_mapkey0123_idxfn,true>
  > COUNTSTORE7_L3_1_map;
  typedef HashIndex<COUNTSTORE7_L3_1_entry,DOUBLE_TYPE,COUNTSTORE7_L3_1_mapkey0123_idxfn,true> HashIndex_COUNTSTORE7_L3_1_map_0123;
  
  struct COUNTSTORE11_L3_4_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long COUNTSTORESTORE_S_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE11_L3_4_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; COUNTSTORESTORE_S_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE11_L3_4_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE11_L3_4_entry(const COUNTSTORE11_L3_4_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), COUNTSTORESTORE_S_STORE_SK( other.COUNTSTORESTORE_S_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE11_L3_4_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE11_L3_4_entry& modify2(const long c2) { COUNTSTORESTORE_S_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE11_L3_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE11_L3_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE11_L3_4_entry& x, const COUNTSTORE11_L3_4_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE11_L3_4_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE11_L3_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE11_L3_4_entry& x, const COUNTSTORE11_L3_4_entry& y) {
      return x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE11_L3_4_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE11_L3_4_entry,DOUBLE_TYPE,COUNTSTORE11_L3_4_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE11_L3_4_entry,DOUBLE_TYPE,COUNTSTORE11_L3_4_mapkey2_idxfn,false>
  > COUNTSTORE11_L3_4_map;
  typedef HashIndex<COUNTSTORE11_L3_4_entry,DOUBLE_TYPE,COUNTSTORE11_L3_4_mapkey0123_idxfn,true> HashIndex_COUNTSTORE11_L3_4_map_0123;
  typedef HashIndex<COUNTSTORE11_L3_4_entry,DOUBLE_TYPE,COUNTSTORE11_L3_4_mapkey2_idxfn,false> HashIndex_COUNTSTORE11_L3_4_map_2;
  
  struct COUNTSTORE11_L4_4_entry {
    long CUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long COUNTSTORESTORE_S_STORE_SK; long MS_SS_TICKET_NUMBER; DOUBLE_TYPE __av; 
    explicit COUNTSTORE11_L4_4_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; COUNTSTORESTORE_S_STORE_SK = 0L; MS_SS_TICKET_NUMBER = 0L; __av = 0.0; */ }
    explicit COUNTSTORE11_L4_4_entry(const long c0, const long c1, const long c2, const long c3, const DOUBLE_TYPE c4) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3; __av = c4; }
    COUNTSTORE11_L4_4_entry(const COUNTSTORE11_L4_4_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), COUNTSTORESTORE_S_STORE_SK( other.COUNTSTORESTORE_S_STORE_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE11_L4_4_entry& modify(const long c0, const long c1, const long c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; COUNTSTORESTORE_S_STORE_SK = c2; MS_SS_TICKET_NUMBER = c3;  return *this; }
    FORCE_INLINE COUNTSTORE11_L4_4_entry& modify2(const long c2) { COUNTSTORESTORE_S_STORE_SK = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE11_L4_4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE11_L4_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE11_L4_4_entry& x, const COUNTSTORE11_L4_4_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTSTORE11_L4_4_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE11_L4_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE11_L4_4_entry& x, const COUNTSTORE11_L4_4_entry& y) {
      return x.COUNTSTORESTORE_S_STORE_SK == y.COUNTSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE11_L4_4_entry,DOUBLE_TYPE,
    HashIndex<COUNTSTORE11_L4_4_entry,DOUBLE_TYPE,COUNTSTORE11_L4_4_mapkey0123_idxfn,true>,
    HashIndex<COUNTSTORE11_L4_4_entry,DOUBLE_TYPE,COUNTSTORE11_L4_4_mapkey2_idxfn,false>
  > COUNTSTORE11_L4_4_map;
  typedef HashIndex<COUNTSTORE11_L4_4_entry,DOUBLE_TYPE,COUNTSTORE11_L4_4_mapkey0123_idxfn,true> HashIndex_COUNTSTORE11_L4_4_map_0123;
  typedef HashIndex<COUNTSTORE11_L4_4_entry,DOUBLE_TYPE,COUNTSTORE11_L4_4_mapkey2_idxfn,false> HashIndex_COUNTSTORE11_L4_4_map_2;
  
  struct COUNTSTORE_SALES1_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; long __av; 
    explicit COUNTSTORE_SALES1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2; __av = c3; }
    COUNTSTORE_SALES1_entry(const COUNTSTORE_SALES1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_LAST_NAME = c2;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME;
    }
  };
  
  struct COUNTSTORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_entry,long,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey012_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_map;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey012_idxfn,true> HashIndex_COUNTSTORE_SALES1_map_012;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_map_0;
  
  struct COUNTSTORE_SALES1_E1_2_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_2_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_2_entry(const long c0, const long c1) { COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_2_entry(const COUNTSTORE_SALES1_E1_2_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_2_entry& modify(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_2_entry& x, const COUNTSTORE_SALES1_E1_2_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_2_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_2_entry,long,COUNTSTORE_SALES1_E1_2_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_2_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_2_entry,long,COUNTSTORE_SALES1_E1_2_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_2_map_0;
  
  struct COUNTSTORE_SALES1_E1_5_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK; long __av; 
    explicit COUNTSTORE_SALES1_E1_5_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_5_entry(const long c0, const long c1) { COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = c0; __av = c1; }
    COUNTSTORE_SALES1_E1_5_entry(const COUNTSTORE_SALES1_E1_5_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_5_entry& modify(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_5_entry& x, const COUNTSTORE_SALES1_E1_5_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_5_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_5_entry,long,COUNTSTORE_SALES1_E1_5_mapkey0_idxfn,true>
  > COUNTSTORE_SALES1_E1_5_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_5_entry,long,COUNTSTORE_SALES1_E1_5_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_5_map_0;
  
  struct COUNTSTORE_SALES1_E1_6_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK; STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTSTORE_SALES1_E1_6_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = 0L; MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_E1_6_entry(const long c0, const STRING_TYPE& c1, const long c2) { COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1; __av = c2; }
    COUNTSTORE_SALES1_E1_6_entry(const COUNTSTORE_SALES1_E1_6_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_E1_6_entry& modify(const long c0, const STRING_TYPE& c1) { COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = c0; MS_S_CITY = c1;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_E1_6_entry& modify0(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_E1_6_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_6_entry& x, const COUNTSTORE_SALES1_E1_6_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  struct COUNTSTORE_SALES1_E1_6_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_E1_6_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_E1_6_entry& x, const COUNTSTORE_SALES1_E1_6_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES1_E1_6_entry,long,
    HashIndex<COUNTSTORE_SALES1_E1_6_entry,long,COUNTSTORE_SALES1_E1_6_mapkey01_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_E1_6_entry,long,COUNTSTORE_SALES1_E1_6_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_E1_6_map;
  typedef HashIndex<COUNTSTORE_SALES1_E1_6_entry,long,COUNTSTORE_SALES1_E1_6_mapkey01_idxfn,true> HashIndex_COUNTSTORE_SALES1_E1_6_map_01;
  typedef HashIndex<COUNTSTORE_SALES1_E1_6_entry,long,COUNTSTORE_SALES1_E1_6_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_E1_6_map_0;
  
  struct COUNTCUSTOMER1_E1_1_entry {
    long COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; long __av; 
    explicit COUNTCUSTOMER1_E1_1_entry() { /*COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const long c4) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_E1_1_entry(const COUNTCUSTOMER1_E1_1_entry& other) : COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK( other.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify012(const long c0, const long c1, const long c2) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify2(const long c2) { MS_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify02(const long c0, const long c2) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; MS_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify0(const long c0) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey2_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey02_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_E1_1_entry,long,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey012_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey02_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_E1_1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1_map_0123;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey012_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_012;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey2_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_2;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey02_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_02;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_0;
  
  struct COUNTCUSTOMER1_L3_1_entry {
    long COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L3_1_entry() { /*COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L3_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_L3_1_entry(const COUNTCUSTOMER1_L3_1_entry& other) : COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK( other.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L3_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L3_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L3_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L3_1_entry& x, const COUNTCUSTOMER1_L3_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_1_mapkey0123_idxfn,true>
  > COUNTCUSTOMER1_L3_1_map;
  typedef HashIndex<COUNTCUSTOMER1_L3_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L3_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L3_1_map_0123;
  
  struct COUNTCUSTOMER1_L4_1_entry {
    long COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK; long STORE_SALES_SS_ADDR_SK; long MS_SS_TICKET_NUMBER; STRING_TYPE MS_S_CITY; DOUBLE_TYPE __av; 
    explicit COUNTCUSTOMER1_L4_1_entry() { /*COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = 0L; STORE_SALES_SS_ADDR_SK = 0L; MS_SS_TICKET_NUMBER = 0L; MS_S_CITY = ""; __av = 0.0; */ }
    explicit COUNTCUSTOMER1_L4_1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const DOUBLE_TYPE c4) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3; __av = c4; }
    COUNTCUSTOMER1_L4_1_entry(const COUNTCUSTOMER1_L4_1_entry& other) : COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK( other.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK ), STORE_SALES_SS_ADDR_SK( other.STORE_SALES_SS_ADDR_SK ), MS_SS_TICKET_NUMBER( other.MS_SS_TICKET_NUMBER ), MS_S_CITY( other.MS_S_CITY ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_L4_1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; STORE_SALES_SS_ADDR_SK = c1; MS_SS_TICKET_NUMBER = c2; MS_S_CITY = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_SALES_SS_ADDR_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MS_S_CITY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_L4_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_L4_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.STORE_SALES_SS_ADDR_SK);
      hash_combine(h, e.MS_SS_TICKET_NUMBER);
      hash_combine(h, e.MS_S_CITY);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_L4_1_entry& x, const COUNTCUSTOMER1_L4_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.STORE_SALES_SS_ADDR_SK == y.STORE_SALES_SS_ADDR_SK && x.MS_SS_TICKET_NUMBER == y.MS_SS_TICKET_NUMBER && x.MS_S_CITY == y.MS_S_CITY;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,
    HashIndex<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_1_mapkey0123_idxfn,true>
  > COUNTCUSTOMER1_L4_1_map;
  typedef HashIndex<COUNTCUSTOMER1_L4_1_entry,DOUBLE_TYPE,COUNTCUSTOMER1_L4_1_mapkey0123_idxfn,true> HashIndex_COUNTCUSTOMER1_L4_1_map_0123;
  
  struct tuple6_DDSSS_L {
    DOUBLE_TYPE _1; DOUBLE_TYPE _2; STRING_TYPE _3; STRING_TYPE _4; STRING_TYPE _5; long __av;
    explicit tuple6_DDSSS_L() { }
    explicit tuple6_DDSSS_L(const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_DDSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_DDSSS_L& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_DDSSS_L &x, const tuple6_DDSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_DDSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      return h;
    }
  };
  struct tuple6_SSLDD_L {
    STRING_TYPE _1; STRING_TYPE _2; long _3; DOUBLE_TYPE _4; DOUBLE_TYPE _5; long __av;
    explicit tuple6_SSLDD_L() { }
    explicit tuple6_SSLDD_L(const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3, const DOUBLE_TYPE c4, const DOUBLE_TYPE c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_SSLDD_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_SSLDD_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3, const DOUBLE_TYPE c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_SSLDD_L &x, const tuple6_SSLDD_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_SSLDD_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
      return h;
    }
  };
  struct tuple3_LS_L {
    long _1; STRING_TYPE _2; long __av;
    explicit tuple3_LS_L() { }
    explicit tuple3_LS_L(const long c1, const STRING_TYPE& c2, long c__av=0L) { _1 = c1; _2 = c2; __av = c__av;}
    int operator==(const tuple3_LS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2)); }
    FORCE_INLINE tuple3_LS_L& modify(const long c0, const STRING_TYPE& c1, long c__av) { _1 = c0; _2 = c1; __av = c__av; return *this; }
    static bool equals(const tuple3_LS_L &x, const tuple3_LS_L &y) { return ((x._1==y._1) && (x._2==y._2)); }
    static long hash(const tuple3_LS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      return h;
    }
  };
  struct tuple2_S_L {
    STRING_TYPE _1; long __av;
    explicit tuple2_S_L() { }
    explicit tuple2_S_L(const STRING_TYPE& c1, long c__av=0L) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_S_L &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_S_L& modify(const STRING_TYPE& c0, long c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_S_L &x, const tuple2_S_L &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_S_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      return h;
    }
  };
  struct tuple4_DDS_L {
    DOUBLE_TYPE _1; DOUBLE_TYPE _2; STRING_TYPE _3; long __av;
    explicit tuple4_DDS_L() { }
    explicit tuple4_DDS_L(const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; __av = c__av;}
    int operator==(const tuple4_DDS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3)); }
    FORCE_INLINE tuple4_DDS_L& modify(const DOUBLE_TYPE c0, const DOUBLE_TYPE c1, const STRING_TYPE& c2, long c__av) { _1 = c0; _2 = c1; _3 = c2; __av = c__av; return *this; }
    static bool equals(const tuple4_DDS_L &x, const tuple4_DDS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3)); }
    static long hash(const tuple4_DDS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      return h;
    }
  };
  struct tuple4_LLS_L {
    long _1; long _2; STRING_TYPE _3; long __av;
    explicit tuple4_LLS_L() { }
    explicit tuple4_LLS_L(const long c1, const long c2, const STRING_TYPE& c3, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; __av = c__av;}
    int operator==(const tuple4_LLS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3)); }
    FORCE_INLINE tuple4_LLS_L& modify(const long c0, const long c1, const STRING_TYPE& c2, long c__av) { _1 = c0; _2 = c1; _3 = c2; __av = c__av; return *this; }
    static bool equals(const tuple4_LLS_L &x, const tuple4_LLS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3)); }
    static long hash(const tuple4_LLS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      return h;
    }
  };
  struct tuple3_LL_L {
    long _1; long _2; long __av;
    explicit tuple3_LL_L() { }
    explicit tuple3_LL_L(const long c1, const long c2, long c__av=0L) { _1 = c1; _2 = c2; __av = c__av;}
    int operator==(const tuple3_LL_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2)); }
    FORCE_INLINE tuple3_LL_L& modify(const long c0, const long c1, long c__av) { _1 = c0; _2 = c1; __av = c__av; return *this; }
    static bool equals(const tuple3_LL_L &x, const tuple3_LL_L &y) { return ((x._1==y._1) && (x._2==y._2)); }
    static long hash(const tuple3_LL_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      return h;
    }
  };
  struct tuple5_LDDS_L {
    long _1; DOUBLE_TYPE _2; DOUBLE_TYPE _3; STRING_TYPE _4; long __av;
    explicit tuple5_LDDS_L() { }
    explicit tuple5_LDDS_L(const long c1, const DOUBLE_TYPE c2, const DOUBLE_TYPE c3, const STRING_TYPE& c4, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; __av = c__av;}
    int operator==(const tuple5_LDDS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4)); }
    FORCE_INLINE tuple5_LDDS_L& modify(const long c0, const DOUBLE_TYPE c1, const DOUBLE_TYPE c2, const STRING_TYPE& c3, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; __av = c__av; return *this; }
    static bool equals(const tuple5_LDDS_L &x, const tuple5_LDDS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4)); }
    static long hash(const tuple5_LDDS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      return h;
    }
  };
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const COUNT_map& _COUNT = get_COUNT();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(COUNT), _COUNT, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const COUNT_map& get_COUNT() const {
      return COUNT;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    COUNT_map COUNT;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U), _c4(16U), _c7(16U), _c6(16U), _c9(16U), _c3(16U), _c2(16U), agg1(16U), _c5(16U), _c8(16U) {
      
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
    }
    
    void on_insert_HOUSEHOLD_DEMOGRAPHICS(const long household_demographics_hd_demo_sk, const long household_demographics_hd_income_band_sk, const STRING_TYPE household_demographics_hd_buy_potential, const long household_demographics_hd_dep_count, const long household_demographics_hd_vehicle_count) {
      HOUSEHOLD_DEMOGRAPHICS_entry e(household_demographics_hd_demo_sk, household_demographics_hd_income_band_sk, household_demographics_hd_buy_potential, household_demographics_hd_dep_count, household_demographics_hd_vehicle_count, 1L);
      HOUSEHOLD_DEMOGRAPHICS.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_STORE_SALES(const long store_sales_ss_sold_date_sk, const long store_sales_ss_sold_time_sk, const long store_sales_ss_item_sk, const long store_sales_ss_customer_sk, const long store_sales_ss_cdemo_sk, const long store_sales_ss_hdemo_sk, const long store_sales_ss_addr_sk, const long store_sales_ss_store_sk, const long store_sales_ss_promo_sk, const long store_sales_ss_ticket_number, const long store_sales_ss_quantity, const DOUBLE_TYPE store_sales_ss_wholesale_cost, const DOUBLE_TYPE store_sales_ss_list_price, const DOUBLE_TYPE store_sales_ss_sales_price, const DOUBLE_TYPE store_sales_ss_ext_discount_amt, const DOUBLE_TYPE store_sales_ss_ext_sales_price, const DOUBLE_TYPE store_sales_ss_ext_wholesale_cost, const DOUBLE_TYPE store_sales_ss_ext_list_price, const DOUBLE_TYPE store_sales_ss_ext_tax, const DOUBLE_TYPE store_sales_ss_coupon_amt, const DOUBLE_TYPE store_sales_ss_net_paid, const DOUBLE_TYPE store_sales_ss_net_paid_inc_tax, const DOUBLE_TYPE store_sales_ss_net_profit) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        _c1.clear();
        _c2.clear();
        _c3.clear();
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i1 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[1]);
          const HASH_RES_t h1 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se2.modify012(store_sales_ss_customer_sk, store_sales_ss_addr_sk, store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n1 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i1->slice(se2, h1));
          COUNTCUSTOMER1_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE ms_s_city = e1->MS_S_CITY;
              long v4 = e1->__av;
              _c3.addOrDelOnZero(st1.modify(ms_s_city,v4), v4);
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se2, *e1)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i2 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
          const HASH_RES_t h2 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se5.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n2 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i2->slice(se5, h2));
          COUNTSTORE_SALES1_E1_6_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE ms_s_city = e2->MS_S_CITY;
              long v5 = e2->__av;
              _c3.addOrDelOnZero(st2.modify(ms_s_city,(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se3.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se4.modify(store_sales_ss_hdemo_sk)) * v5))), (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se3.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se4.modify(store_sales_ss_hdemo_sk)) * v5)));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se5, *e2)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_L, long>* i3 = static_cast<HashIndex<tuple2_S_L, long>*>(_c3.index[0]);
          HashIndex<tuple2_S_L, long>::IdxNode* n3; 
          tuple2_S_L* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
              STRING_TYPE ms_s_city = e3->_1;  
              long v6 = e3->__av; 
            STRING_TYPE l1 = Usubstring(ms_s_city, 1L, 30L);
            DOUBLE_TYPE l2 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se6.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city));
            DOUBLE_TYPE l3 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se7.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city));
            _c2.addOrDelOnZero(st3.modify(l3,l2,l1,((v6 != 0 ? 1L : 0L) * -1L)), ((v6 != 0 ? 1L : 0L) * -1L));      
              n3 = n3->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i4 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[1]);
          const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se10.modify012(store_sales_ss_customer_sk, store_sales_ss_addr_sk, store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n4 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i4->slice(se10, h3));
          COUNTCUSTOMER1_E1_1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              STRING_TYPE ms_s_city = e4->MS_S_CITY;
              long v7 = e4->__av;
              STRING_TYPE l4 = Usubstring(ms_s_city, 1L, 30L);
              DOUBLE_TYPE l5 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se8.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city));
              DOUBLE_TYPE l6 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se9.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city));
              _c2.addOrDelOnZero(st4.modify(l6,l5,l4,(v7 != 0 ? 1L : 0L)), (v7 != 0 ? 1L : 0L));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se10, *e4)); 
          }
        }_c4.clear();
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i5 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[1]);
          const HASH_RES_t h4 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se11.modify012(store_sales_ss_customer_sk, store_sales_ss_addr_sk, store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n5 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i5->slice(se11, h4));
          COUNTCUSTOMER1_E1_1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE ms_s_city = e5->MS_S_CITY;
              long v9 = e5->__av;
              _c4.addOrDelOnZero(st5.modify(ms_s_city,v9), v9);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h4 == n5->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se11, *e5)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i6 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
          const HASH_RES_t h5 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se14.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n6 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i6->slice(se14, h5));
          COUNTSTORE_SALES1_E1_6_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE ms_s_city = e6->MS_S_CITY;
              long v10 = e6->__av;
              _c4.addOrDelOnZero(st6.modify(ms_s_city,(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se13.modify(store_sales_ss_hdemo_sk)) * v10))), (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se13.modify(store_sales_ss_hdemo_sk)) * v10)));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h5 == n6->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se14, *e6)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_L, long>* i7 = static_cast<HashIndex<tuple2_S_L, long>*>(_c4.index[0]);
          HashIndex<tuple2_S_L, long>::IdxNode* n7; 
          tuple2_S_L* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
              STRING_TYPE ms_s_city = e7->_1;  
              long v11 = e7->__av; 
            STRING_TYPE l7 = Usubstring(ms_s_city, 1L, 30L);
            DOUBLE_TYPE l8 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se15.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city)) + (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se16.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se17.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se18.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_coupon_amt))));
            DOUBLE_TYPE l9 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se19.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city)) + (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se20.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se21.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se22.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_net_profit))));
            _c2.addOrDelOnZero(st7.modify(l9,l8,l7,(v11 != 0 ? 1L : 0L)), (v11 != 0 ? 1L : 0L));      
              n7 = n7->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_012* i8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012*>(COUNTCUSTOMER1_E1_1.index[1]);
          const HASH_RES_t h6 = COUNTCUSTOMER1_E1_1_mapkey012_idxfn::hash(se31.modify012(store_sales_ss_customer_sk, store_sales_ss_addr_sk, store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode* n8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_012::IdxNode*>(i8->slice(se31, h6));
          COUNTCUSTOMER1_E1_1_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE ms_s_city = e8->MS_S_CITY;
              long v12 = e8->__av;
              STRING_TYPE l10 = Usubstring(ms_s_city, 1L, 30L);
              DOUBLE_TYPE l11 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se23.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city)) + (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se24.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se25.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se26.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_coupon_amt))));
              DOUBLE_TYPE l12 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se27.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city)) + (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se28.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se29.modify(store_sales_ss_store_sk,ms_s_city)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se30.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_net_profit))));
              _c2.addOrDelOnZero(st8.modify(l12,l11,l10,((v12 != 0 ? 1L : 0L) * -1L)), ((v12 != 0 ? 1L : 0L) * -1L));
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h6 == n8->hash &&  COUNTCUSTOMER1_E1_1_mapkey012_idxfn::equals(se31, *e8)); 
          }
        }{  // temp foreach
          const HashIndex<tuple4_DDS_L, long>* i9 = static_cast<HashIndex<tuple4_DDS_L, long>*>(_c2.index[0]);
          HashIndex<tuple4_DDS_L, long>::IdxNode* n9; 
          tuple4_DDS_L* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
              DOUBLE_TYPE ms_profit = e9->_1;
              DOUBLE_TYPE ms_amt = e9->_2;
              STRING_TYPE __sql_expression_1 = e9->_3;  
              long v13 = e9->__av; 
            { //slice 
              const HashIndex_COUNTSTORE_SALES1_map_0* i10 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
              const HASH_RES_t h7 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se32.modify0(store_sales_ss_customer_sk));
              HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n10 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i10->slice(se32, h7));
              COUNTSTORE_SALES1_entry* e10;
             
              if (n10 && (e10 = n10->obj)) {
                do {                
                  STRING_TYPE customer_c_first_name = e10->CUSTOMER_C_FIRST_NAME;
                  STRING_TYPE customer_c_last_name = e10->CUSTOMER_C_LAST_NAME;
                  long v14 = e10->__av;
                  _c1.addOrDelOnZero(st9.modify(ms_profit,ms_amt,__sql_expression_1,customer_c_first_name,customer_c_last_name,(v13 * v14)), (v13 * v14));
                  n10 = n10->nxt;
                } while (n10 && (e10 = n10->obj) && h7 == n10->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se32, *e10)); 
              }
            }      
              n9 = n9->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i11 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[2]);
          const HASH_RES_t h9 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se36.modify2(store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n11 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i11->slice(se36, h9));
          COUNTCUSTOMER1_E1_1_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long customer_c_customer_sk = e11->COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk_1 = e11->STORE_SALES_SS_ADDR_SK;
              STRING_TYPE ms_s_city = e11->MS_S_CITY;
              long v15 = e11->__av;
              STRING_TYPE l13 = Usubstring(ms_s_city, 1L, 30L);
              DOUBLE_TYPE l14 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se33.modify(customer_c_customer_sk,store_sales_ss_addr_sk_1,store_sales_ss_ticket_number,ms_s_city));
              DOUBLE_TYPE l15 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se34.modify(customer_c_customer_sk,store_sales_ss_addr_sk_1,store_sales_ss_ticket_number,ms_s_city));
              { //slice 
                const HashIndex_COUNTSTORE_SALES1_map_0* i12 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                const HASH_RES_t h8 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se35.modify0(customer_c_customer_sk));
                HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n12 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i12->slice(se35, h8));
                COUNTSTORE_SALES1_entry* e12;
               
                if (n12 && (e12 = n12->obj)) {
                  do {                
                    STRING_TYPE customer_c_first_name = e12->CUSTOMER_C_FIRST_NAME;
                    STRING_TYPE customer_c_last_name = e12->CUSTOMER_C_LAST_NAME;
                    long v16 = e12->__av;
                    _c1.addOrDelOnZero(st10.modify(l15,l14,l13,customer_c_first_name,customer_c_last_name,(((v15 != 0 ? 1L : 0L) * v16) * -2L)), (((v15 != 0 ? 1L : 0L) * v16) * -2L));
                    n12 = n12->nxt;
                  } while (n12 && (e12 = n12->obj) && h8 == n12->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se35, *e12)); 
                }
              }
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h9 == n11->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se36, *e11)); 
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i13 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n13; 
          COUNTSTORE_SALES1_entry* e13;
        
          for (size_t i = 0; i < i13->size_; i++)
          {
            n13 = i13->buckets_ + i;
            while (n13 && (e13 = n13->obj))
            {
                long lift2 = e13->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e13->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e13->CUSTOMER_C_LAST_NAME;
                long v17 = e13->__av;
                _c5.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_02* i14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_02*>(COUNTCUSTOMER1_E1_1.index[3]);
                  const HASH_RES_t h10 = COUNTCUSTOMER1_E1_1_mapkey02_idxfn::hash(se37.modify02(lift2, store_sales_ss_ticket_number));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_02::IdxNode* n14 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_02::IdxNode*>(i14->slice(se37, h10));
                  COUNTCUSTOMER1_E1_1_entry* e14;
                 
                  if (n14 && (e14 = n14->obj)) {
                    do {                
                      long lift1 = e14->STORE_SALES_SS_ADDR_SK;
                      STRING_TYPE ms_s_city = e14->MS_S_CITY;
                      long v19 = e14->__av;
                      _c5.addOrDelOnZero(st11.modify(lift1,ms_s_city,v19), v19);
                      n14 = n14->nxt;
                    } while (n14 && (e14 = n14->obj) && h10 == n14->hash &&  COUNTCUSTOMER1_E1_1_mapkey02_idxfn::equals(se37, *e14)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i15 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
                  const HASH_RES_t h11 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se40.modify0(store_sales_ss_store_sk));
                  HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n15 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i15->slice(se40, h11));
                  COUNTSTORE_SALES1_E1_6_entry* e15;
                 
                  if (n15 && (e15 = n15->obj)) {
                    do {                
                      STRING_TYPE ms_s_city = e15->MS_S_CITY;
                      long v20 = e15->__av;
                      (/*if */(lift2 == store_sales_ss_customer_sk) ? _c5.addOrDelOnZero(st12.modify(store_sales_ss_addr_sk,ms_s_city,(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se38.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se39.modify(store_sales_ss_hdemo_sk)) * v20))), (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se38.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se39.modify(store_sales_ss_hdemo_sk)) * v20))) : (void)0);
                      n15 = n15->nxt;
                    } while (n15 && (e15 = n15->obj) && h11 == n15->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se40, *e15)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple3_LS_L, long>* i16 = static_cast<HashIndex<tuple3_LS_L, long>*>(_c5.index[0]);
                  HashIndex<tuple3_LS_L, long>::IdxNode* n16; 
                  tuple3_LS_L* e16;
                
                  for (size_t i = 0; i < i16->size_; i++)
                  {
                    n16 = i16->buckets_ + i;
                    while (n16 && (e16 = n16->obj))
                    {
                      long lift1 = e16->_1;
                      STRING_TYPE ms_s_city = e16->_2;  
                      long v21 = e16->__av; 
                    DOUBLE_TYPE l16 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se41.modify(lift2,lift1,store_sales_ss_ticket_number,ms_s_city));
                    DOUBLE_TYPE l17 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se42.modify(lift2,lift1,store_sales_ss_ticket_number,ms_s_city));
                    STRING_TYPE l18 = Usubstring(ms_s_city, 1L, 30L);
                    _c1.addOrDelOnZero(st13.modify(l16,l17,l18,customer_c_first_name,customer_c_last_name,(v17 * (v21 != 0 ? 1L : 0L))), (v17 * (v21 != 0 ? 1L : 0L)));      
                      n16 = n16->nxt;
                    }
                  }
                }
              n13 = n13->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_2* i17 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2*>(COUNTCUSTOMER1_E1_1.index[2]);
          const HASH_RES_t h13 = COUNTCUSTOMER1_E1_1_mapkey2_idxfn::hash(se52.modify2(store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode* n17 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_2::IdxNode*>(i17->slice(se52, h13));
          COUNTCUSTOMER1_E1_1_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              long customer_c_customer_sk = e17->COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk_1 = e17->STORE_SALES_SS_ADDR_SK;
              STRING_TYPE ms_s_city = e17->MS_S_CITY;
              long v22 = e17->__av;
              DOUBLE_TYPE l19 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se43.modify(customer_c_customer_sk,store_sales_ss_addr_sk_1,store_sales_ss_ticket_number,ms_s_city)) + (/*if */(store_sales_ss_addr_sk_1 == store_sales_ss_addr_sk && customer_c_customer_sk == store_sales_ss_customer_sk) ? (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se44.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se45.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se46.modify(store_sales_ss_store_sk,ms_s_city)) * store_sales_ss_net_profit))) : 0.0));
              DOUBLE_TYPE l20 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se47.modify(customer_c_customer_sk,store_sales_ss_addr_sk_1,store_sales_ss_ticket_number,ms_s_city)) + (/*if */(store_sales_ss_addr_sk_1 == store_sales_ss_addr_sk && customer_c_customer_sk == store_sales_ss_customer_sk) ? (COUNTSTORE_SALES1_E1_2.getValueOrDefault(se48.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se49.modify(store_sales_ss_hdemo_sk)) * (COUNTSTORE_SALES1_E1_6.getValueOrDefault(se50.modify(store_sales_ss_store_sk,ms_s_city)) * store_sales_ss_coupon_amt))) : 0.0));
              STRING_TYPE l21 = Usubstring(ms_s_city, 1L, 30L);
              { //slice 
                const HashIndex_COUNTSTORE_SALES1_map_0* i18 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                const HASH_RES_t h12 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se51.modify0(customer_c_customer_sk));
                HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n18 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i18->slice(se51, h12));
                COUNTSTORE_SALES1_entry* e18;
               
                if (n18 && (e18 = n18->obj)) {
                  do {                
                    STRING_TYPE customer_c_first_name = e18->CUSTOMER_C_FIRST_NAME;
                    STRING_TYPE customer_c_last_name = e18->CUSTOMER_C_LAST_NAME;
                    long v23 = e18->__av;
                    _c1.addOrDelOnZero(st14.modify(l19,l20,l21,customer_c_first_name,customer_c_last_name,((v22 != 0 ? 1L : 0L) * v23)), ((v22 != 0 ? 1L : 0L) * v23));
                    n18 = n18->nxt;
                  } while (n18 && (e18 = n18->obj) && h12 == n18->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se51, *e18)); 
                }
              }
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h13 == n17->hash &&  COUNTCUSTOMER1_E1_1_mapkey2_idxfn::equals(se52, *e17)); 
          }
        }{  // temp foreach
          const HashIndex<tuple6_DDSSS_L, long>* i19 = static_cast<HashIndex<tuple6_DDSSS_L, long>*>(_c1.index[0]);
          HashIndex<tuple6_DDSSS_L, long>::IdxNode* n19; 
          tuple6_DDSSS_L* e19;
        
          for (size_t i = 0; i < i19->size_; i++)
          {
            n19 = i19->buckets_ + i;
            while (n19 && (e19 = n19->obj))
            {
              DOUBLE_TYPE ms_profit = e19->_1;
              DOUBLE_TYPE ms_amt = e19->_2;
              STRING_TYPE __sql_expression_1 = e19->_3;
              STRING_TYPE customer_c_first_name = e19->_4;
              STRING_TYPE customer_c_last_name = e19->_5;  
              long v24 = e19->__av; 
            COUNT.addOrDelOnZero(se1.modify(customer_c_last_name,customer_c_first_name,__sql_expression_1,store_sales_ss_ticket_number,ms_amt,ms_profit),v24);      
              n19 = n19->nxt;
            }
          }
        }COUNTSTORE1_E2_5.addOrDelOnZero(se53.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se54.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES1_E1_5.getValueOrDefault(se55.modify(store_sales_ss_hdemo_sk))));
        { //slice 
          const HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0* i20 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0*>(COUNTSTORE7_E1_1STORE_SALES2.index[1]);
          const HASH_RES_t h14 = COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::hash(se59.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode* n20 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode*>(i20->slice(se59, h14));
          COUNTSTORE7_E1_1STORE_SALES2_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              STRING_TYPE countstorestore_s_city = e20->COUNTSTORESTORE_S_CITY;
              long v25 = e20->__av;
              COUNTSTORE7_E1_1.addOrDelOnZero(se56.modify(countstorestore_s_city,store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se57.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se58.modify(store_sales_ss_hdemo_sk)) * v25)));
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h14 == n20->hash &&  COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::equals(se59, *e20)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0* i21 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0*>(COUNTSTORE7_E1_1STORE_SALES2.index[1]);
          const HASH_RES_t h15 = COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::hash(se63.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode* n21 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode*>(i21->slice(se63, h15));
          COUNTSTORE7_E1_1STORE_SALES2_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              STRING_TYPE countstorestore_s_city = e21->COUNTSTORESTORE_S_CITY;
              long v26 = e21->__av;
              COUNTSTORE7_L2_1.addOrDelOnZero(se60.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,countstorestore_s_city,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se61.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se62.modify(store_sales_ss_hdemo_sk)) * (v26 * store_sales_ss_coupon_amt))));
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h15 == n21->hash &&  COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::equals(se63, *e21)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0* i22 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0*>(COUNTSTORE7_E1_1STORE_SALES2.index[1]);
          const HASH_RES_t h16 = COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::hash(se67.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode* n22 = static_cast<HashIndex_COUNTSTORE7_E1_1STORE_SALES2_map_0::IdxNode*>(i22->slice(se67, h16));
          COUNTSTORE7_E1_1STORE_SALES2_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              STRING_TYPE countstorestore_s_city = e22->COUNTSTORESTORE_S_CITY;
              long v27 = e22->__av;
              COUNTSTORE7_L3_1.addOrDelOnZero(se64.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,countstorestore_s_city,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se65.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se66.modify(store_sales_ss_hdemo_sk)) * (v27 * store_sales_ss_net_profit))));
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h16 == n22->hash &&  COUNTSTORE7_E1_1STORE_SALES2_mapkey0_idxfn::equals(se67, *e22)); 
          }
        }COUNTSTORE11_L3_4.addOrDelOnZero(se68.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se69.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se70.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_net_profit)));
        COUNTSTORE11_L4_4.addOrDelOnZero(se71.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se72.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se73.modify(store_sales_ss_hdemo_sk)) * store_sales_ss_coupon_amt)));
        { //slice 
          const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i23 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
          const HASH_RES_t h17 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se77.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n23 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i23->slice(se77, h17));
          COUNTSTORE_SALES1_E1_6_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              STRING_TYPE ms_s_city = e23->MS_S_CITY;
              long v28 = e23->__av;
              COUNTCUSTOMER1_E1_1.addOrDelOnZero(se74.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se75.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se76.modify(store_sales_ss_hdemo_sk)) * v28)));
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h17 == n23->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se77, *e23)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i24 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
          const HASH_RES_t h18 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se81.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n24 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i24->slice(se81, h18));
          COUNTSTORE_SALES1_E1_6_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              STRING_TYPE ms_s_city = e24->MS_S_CITY;
              long v29 = e24->__av;
              COUNTCUSTOMER1_L3_1.addOrDelOnZero(se78.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se79.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se80.modify(store_sales_ss_hdemo_sk)) * (v29 * store_sales_ss_net_profit))));
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h18 == n24->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se81, *e24)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE_SALES1_E1_6_map_0* i25 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0*>(COUNTSTORE_SALES1_E1_6.index[1]);
          const HASH_RES_t h19 = COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::hash(se85.modify0(store_sales_ss_store_sk));
          HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode* n25 = static_cast<HashIndex_COUNTSTORE_SALES1_E1_6_map_0::IdxNode*>(i25->slice(se85, h19));
          COUNTSTORE_SALES1_E1_6_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              STRING_TYPE ms_s_city = e25->MS_S_CITY;
              long v30 = e25->__av;
              COUNTCUSTOMER1_L4_1.addOrDelOnZero(se82.modify(store_sales_ss_customer_sk,store_sales_ss_addr_sk,store_sales_ss_ticket_number,ms_s_city),(COUNTSTORE_SALES1_E1_2.getValueOrDefault(se83.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES1_E1_5.getValueOrDefault(se84.modify(store_sales_ss_hdemo_sk)) * (v30 * store_sales_ss_coupon_amt))));
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h19 == n25->hash &&  COUNTSTORE_SALES1_E1_6_mapkey0_idxfn::equals(se85, *e25)); 
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_c_customer_sk, const STRING_TYPE& customer_c_customer_id, const long customer_c_current_cdemo_sk, const long customer_c_current_hdemo_sk, const long customer_c_current_addr_sk, const long customer_c_first_shipto_date_sk, const long customer_c_first_sales_date_sk, const STRING_TYPE& customer_c_salutation, const STRING_TYPE& customer_c_first_name, const STRING_TYPE& customer_c_last_name, const STRING_TYPE& customer_c_preferred_cust_flag, const long customer_c_birth_day, const long customer_c_birth_month, const long customer_c_birth_year, const STRING_TYPE& customer_c_birth_country, const STRING_TYPE& customer_c_login, const STRING_TYPE& customer_c_email_address, const STRING_TYPE& customer_c_last_review_date) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        agg1.clear();
        
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i26 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[4]);
          const HASH_RES_t h20 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se89.modify0(customer_c_customer_sk));
          HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n26 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i26->slice(se89, h20));
          COUNTCUSTOMER1_E1_1_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long store_sales_ss_addr_sk = e26->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e26->MS_SS_TICKET_NUMBER;
              STRING_TYPE ms_s_city = e26->MS_S_CITY;
              long v31 = e26->__av;
              STRING_TYPE l22 = Usubstring(ms_s_city, 1L, 30L);
              DOUBLE_TYPE l23 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se87.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
              DOUBLE_TYPE l24 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se88.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
              agg1.addOrDelOnZero(st15.modify(ms_ss_ticket_number,l24,l23,l22,(v31 != 0 ? 1L : 0L)), (v31 != 0 ? 1L : 0L));
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h20 == n26->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se89, *e26)); 
          }
        }{  // temp foreach
          const HashIndex<tuple5_LDDS_L, long>* i27 = static_cast<HashIndex<tuple5_LDDS_L, long>*>(agg1.index[0]);
          HashIndex<tuple5_LDDS_L, long>::IdxNode* n27; 
          tuple5_LDDS_L* e27;
        
          for (size_t i = 0; i < i27->size_; i++)
          {
            n27 = i27->buckets_ + i;
            while (n27 && (e27 = n27->obj))
            {
              long ms_ss_ticket_number = e27->_1;
              DOUBLE_TYPE ms_amt = e27->_2;
              DOUBLE_TYPE ms_profit = e27->_3;
              STRING_TYPE __sql_expression_1 = e27->_4;  
              long v32 = e27->__av; 
            COUNT.addOrDelOnZero(se86.modify(customer_c_last_name,customer_c_first_name,__sql_expression_1,ms_ss_ticket_number,ms_amt,ms_profit),v32);      
              n27 = n27->nxt;
            }
          }
        }COUNTSTORE_SALES1.addOrDelOnZero(se90.modify(customer_c_customer_sk,customer_c_first_name,customer_c_last_name),1L);
      }
    }
    void on_insert_STORE(const long store_s_store_sk, const STRING_TYPE& store_s_store_id, const date store_s_rec_start_date, const date store_s_rec_end_date, const long store_s_closed_date_sk, const STRING_TYPE& store_s_store_name, const long store_s_number_employees, const long store_s_floor_space, const STRING_TYPE& store_s_hours, const STRING_TYPE& store_s_manager, const long store_s_market_id, const STRING_TYPE& store_s_geography_class, const STRING_TYPE& store_s_market_desc, const STRING_TYPE& store_s_market_manager, const long store_s_division_id, const STRING_TYPE& store_s_division_name, const long store_s_company_id, const STRING_TYPE& store_s_company_name, const STRING_TYPE& store_s_street_number, const STRING_TYPE& store_s_street_name, const STRING_TYPE& store_s_street_type, const STRING_TYPE& store_s_suite_number, const STRING_TYPE& store_s_city, const STRING_TYPE& store_s_county, const STRING_TYPE& store_s_state, const STRING_TYPE& store_s_zip, const STRING_TYPE& store_s_country, const DOUBLE_TYPE store_s_gmt_offset, const DOUBLE_TYPE store_s_tax_precentage) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        STRING_TYPE l25 = Usubstring(store_s_city, 1L, 30L);
        _c6.clear();
        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i28 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n28; 
          COUNTSTORE_SALES1_entry* e28;
        
          for (size_t i = 0; i < i28->size_; i++)
          {
            n28 = i28->buckets_ + i;
            while (n28 && (e28 = n28->obj))
            {
                long customer_c_customer_sk = e28->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e28->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e28->CUSTOMER_C_LAST_NAME;
                long v34 = e28->__av;
                _c7.clear();
                { //slice 
                  const HashIndex_COUNTSTORE7_E1_1_map_01* i29 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_01*>(COUNTSTORE7_E1_1.index[1]);
                  const HASH_RES_t h21 = COUNTSTORE7_E1_1_mapkey01_idxfn::hash(se92.modify01(store_s_city, customer_c_customer_sk));
                  HashIndex_COUNTSTORE7_E1_1_map_01::IdxNode* n29 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_01::IdxNode*>(i29->slice(se92, h21));
                  COUNTSTORE7_E1_1_entry* e29;
                 
                  if (n29 && (e29 = n29->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e29->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e29->MS_SS_TICKET_NUMBER;
                      long v36 = e29->__av;
                      _c7.addOrDelOnZero(st16.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v36), v36);
                      n29 = n29->nxt;
                    } while (n29 && (e29 = n29->obj) && h21 == n29->hash &&  COUNTSTORE7_E1_1_mapkey01_idxfn::equals(se92, *e29)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE1_E2_5_map_02* i30 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02*>(COUNTSTORE1_E2_5.index[1]);
                  const HASH_RES_t h22 = COUNTSTORE1_E2_5_mapkey02_idxfn::hash(se93.modify02(customer_c_customer_sk, store_s_store_sk));
                  HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode* n30 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode*>(i30->slice(se93, h22));
                  COUNTSTORE1_E2_5_entry* e30;
                 
                  if (n30 && (e30 = n30->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e30->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e30->MS_SS_TICKET_NUMBER;
                      long v37 = e30->__av;
                      (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? _c7.addOrDelOnZero(st17.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v37), v37) : (void)0);
                      n30 = n30->nxt;
                    } while (n30 && (e30 = n30->obj) && h22 == n30->hash &&  COUNTSTORE1_E2_5_mapkey02_idxfn::equals(se93, *e30)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple3_LL_L, long>* i31 = static_cast<HashIndex<tuple3_LL_L, long>*>(_c7.index[0]);
                  HashIndex<tuple3_LL_L, long>::IdxNode* n31; 
                  tuple3_LL_L* e31;
                
                  for (size_t i = 0; i < i31->size_; i++)
                  {
                    n31 = i31->buckets_ + i;
                    while (n31 && (e31 = n31->obj))
                    {
                      long store_sales_ss_addr_sk = e31->_1;
                      long ms_ss_ticket_number = e31->_2;  
                      long v38 = e31->__av; 
                    DOUBLE_TYPE l26 = COUNTSTORE7_L2_1.getValueOrDefault(se94.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number));
                    DOUBLE_TYPE l27 = COUNTSTORE7_L3_1.getValueOrDefault(se95.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number));
                    _c6.addOrDelOnZero(st18.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l27,l26,((v34 * (v38 != 0 ? 1L : 0L)) * -1L)), ((v34 * (v38 != 0 ? 1L : 0L)) * -1L));      
                      n31 = n31->nxt;
                    }
                  }
                }
              n28 = n28->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTSTORE7_E1_1_map_0* i32 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_0*>(COUNTSTORE7_E1_1.index[2]);
          const HASH_RES_t h24 = COUNTSTORE7_E1_1_mapkey0_idxfn::hash(se99.modify0(store_s_city));
          HashIndex_COUNTSTORE7_E1_1_map_0::IdxNode* n32 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_0::IdxNode*>(i32->slice(se99, h24));
          COUNTSTORE7_E1_1_entry* e32;
         
          if (n32 && (e32 = n32->obj)) {
            do {                
              long customer_c_customer_sk = e32->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e32->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e32->MS_SS_TICKET_NUMBER;
              long v39 = e32->__av;
              DOUBLE_TYPE l28 = COUNTSTORE7_L2_1.getValueOrDefault(se96.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number));
              DOUBLE_TYPE l29 = COUNTSTORE7_L3_1.getValueOrDefault(se97.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number));
              { //slice 
                const HashIndex_COUNTSTORE_SALES1_map_0* i33 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                const HASH_RES_t h23 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se98.modify0(customer_c_customer_sk));
                HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n33 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i33->slice(se98, h23));
                COUNTSTORE_SALES1_entry* e33;
               
                if (n33 && (e33 = n33->obj)) {
                  do {                
                    STRING_TYPE customer_c_first_name = e33->CUSTOMER_C_FIRST_NAME;
                    STRING_TYPE customer_c_last_name = e33->CUSTOMER_C_LAST_NAME;
                    long v40 = e33->__av;
                    _c6.addOrDelOnZero(st19.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l29,l28,((v39 != 0 ? 1L : 0L) * v40)), ((v39 != 0 ? 1L : 0L) * v40));
                    n33 = n33->nxt;
                  } while (n33 && (e33 = n33->obj) && h23 == n33->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se98, *e33)); 
                }
              }
              n32 = n32->nxt;
            } while (n32 && (e32 = n32->obj) && h24 == n32->hash &&  COUNTSTORE7_E1_1_mapkey0_idxfn::equals(se99, *e32)); 
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i34 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n34; 
          COUNTSTORE_SALES1_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                long customer_c_customer_sk = e34->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e34->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e34->CUSTOMER_C_LAST_NAME;
                long v41 = e34->__av;
                _c8.clear();
                { //slice 
                  const HashIndex_COUNTSTORE7_E1_1_map_01* i35 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_01*>(COUNTSTORE7_E1_1.index[1]);
                  const HASH_RES_t h25 = COUNTSTORE7_E1_1_mapkey01_idxfn::hash(se100.modify01(store_s_city, customer_c_customer_sk));
                  HashIndex_COUNTSTORE7_E1_1_map_01::IdxNode* n35 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_01::IdxNode*>(i35->slice(se100, h25));
                  COUNTSTORE7_E1_1_entry* e35;
                 
                  if (n35 && (e35 = n35->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e35->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e35->MS_SS_TICKET_NUMBER;
                      long v43 = e35->__av;
                      _c8.addOrDelOnZero(st20.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v43), v43);
                      n35 = n35->nxt;
                    } while (n35 && (e35 = n35->obj) && h25 == n35->hash &&  COUNTSTORE7_E1_1_mapkey01_idxfn::equals(se100, *e35)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE1_E2_5_map_02* i36 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02*>(COUNTSTORE1_E2_5.index[1]);
                  const HASH_RES_t h26 = COUNTSTORE1_E2_5_mapkey02_idxfn::hash(se101.modify02(customer_c_customer_sk, store_s_store_sk));
                  HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode* n36 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode*>(i36->slice(se101, h26));
                  COUNTSTORE1_E2_5_entry* e36;
                 
                  if (n36 && (e36 = n36->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e36->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e36->MS_SS_TICKET_NUMBER;
                      long v44 = e36->__av;
                      (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? _c8.addOrDelOnZero(st21.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,v44), v44) : (void)0);
                      n36 = n36->nxt;
                    } while (n36 && (e36 = n36->obj) && h26 == n36->hash &&  COUNTSTORE1_E2_5_mapkey02_idxfn::equals(se101, *e36)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple3_LL_L, long>* i37 = static_cast<HashIndex<tuple3_LL_L, long>*>(_c8.index[0]);
                  HashIndex<tuple3_LL_L, long>::IdxNode* n37; 
                  tuple3_LL_L* e37;
                
                  for (size_t i = 0; i < i37->size_; i++)
                  {
                    n37 = i37->buckets_ + i;
                    while (n37 && (e37 = n37->obj))
                    {
                      long store_sales_ss_addr_sk = e37->_1;
                      long ms_ss_ticket_number = e37->_2;  
                      long v45 = e37->__av; 
                    DOUBLE_TYPE l30 = (COUNTSTORE7_L2_1.getValueOrDefault(se102.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number)) + (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE11_L4_4.getValueOrDefault(se103.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
                    DOUBLE_TYPE l31 = (COUNTSTORE7_L3_1.getValueOrDefault(se104.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number)) + (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE11_L3_4.getValueOrDefault(se105.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
                    _c6.addOrDelOnZero(st22.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l31,l30,(v41 * (v45 != 0 ? 1L : 0L))), (v41 * (v45 != 0 ? 1L : 0L)));      
                      n37 = n37->nxt;
                    }
                  }
                }
              n34 = n34->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTSTORE7_E1_1_map_0* i38 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_0*>(COUNTSTORE7_E1_1.index[2]);
          const HASH_RES_t h28 = COUNTSTORE7_E1_1_mapkey0_idxfn::hash(se111.modify0(store_s_city));
          HashIndex_COUNTSTORE7_E1_1_map_0::IdxNode* n38 = static_cast<HashIndex_COUNTSTORE7_E1_1_map_0::IdxNode*>(i38->slice(se111, h28));
          COUNTSTORE7_E1_1_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              long customer_c_customer_sk = e38->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e38->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e38->MS_SS_TICKET_NUMBER;
              long v46 = e38->__av;
              DOUBLE_TYPE l32 = (COUNTSTORE7_L2_1.getValueOrDefault(se106.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number)) + (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE11_L4_4.getValueOrDefault(se107.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
              DOUBLE_TYPE l33 = (COUNTSTORE7_L3_1.getValueOrDefault(se108.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number)) + (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE11_L3_4.getValueOrDefault(se109.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
              { //slice 
                const HashIndex_COUNTSTORE_SALES1_map_0* i39 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                const HASH_RES_t h27 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se110.modify0(customer_c_customer_sk));
                HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n39 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i39->slice(se110, h27));
                COUNTSTORE_SALES1_entry* e39;
               
                if (n39 && (e39 = n39->obj)) {
                  do {                
                    STRING_TYPE customer_c_first_name = e39->CUSTOMER_C_FIRST_NAME;
                    STRING_TYPE customer_c_last_name = e39->CUSTOMER_C_LAST_NAME;
                    long v47 = e39->__av;
                    _c6.addOrDelOnZero(st23.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l33,l32,(((v46 != 0 ? 1L : 0L) * v47) * -1L)), (((v46 != 0 ? 1L : 0L) * v47) * -1L));
                    n39 = n39->nxt;
                  } while (n39 && (e39 = n39->obj) && h27 == n39->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se110, *e39)); 
                }
              }
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h28 == n38->hash &&  COUNTSTORE7_E1_1_mapkey0_idxfn::equals(se111, *e38)); 
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i40 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n40; 
          COUNTSTORE_SALES1_entry* e40;
        
          for (size_t i = 0; i < i40->size_; i++)
          {
            n40 = i40->buckets_ + i;
            while (n40 && (e40 = n40->obj))
            {
                long customer_c_customer_sk = e40->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e40->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e40->CUSTOMER_C_LAST_NAME;
                long v48 = e40->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i41 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[4]);
                  const HASH_RES_t h29 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se114.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n41 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i41->slice(se114, h29));
                  COUNTCUSTOMER1_E1_1_entry* e41;
                 
                  if (n41 && (e41 = n41->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e41->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e41->MS_SS_TICKET_NUMBER;
                      STRING_TYPE ms_s_city = e41->MS_S_CITY;
                      long v49 = e41->__av;
                      DOUBLE_TYPE l34 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se112.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      DOUBLE_TYPE l35 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se113.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city));
                      (/*if */(l25 == Usubstring(ms_s_city, 1L, 30L)) ? _c6.addOrDelOnZero(st24.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l35,l34,((v48 * (v49 != 0 ? 1L : 0L)) * -2L)), ((v48 * (v49 != 0 ? 1L : 0L)) * -2L)) : (void)0);
                      n41 = n41->nxt;
                    } while (n41 && (e41 = n41->obj) && h29 == n41->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se114, *e41)); 
                  }
                }
              n40 = n40->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i42 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n42; 
          COUNTSTORE_SALES1_entry* e42;
        
          for (size_t i = 0; i < i42->size_; i++)
          {
            n42 = i42->buckets_ + i;
            while (n42 && (e42 = n42->obj))
            {
                long customer_c_customer_sk = e42->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e42->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e42->CUSTOMER_C_LAST_NAME;
                long v50 = e42->__av;
                _c9.clear();
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i43 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[4]);
                  const HASH_RES_t h30 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se115.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n43 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i43->slice(se115, h30));
                  COUNTCUSTOMER1_E1_1_entry* e43;
                 
                  if (n43 && (e43 = n43->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e43->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e43->MS_SS_TICKET_NUMBER;
                      STRING_TYPE lift3 = e43->MS_S_CITY;
                      long v52 = e43->__av;
                      _c9.addOrDelOnZero(st25.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,lift3,v52), v52);
                      n43 = n43->nxt;
                    } while (n43 && (e43 = n43->obj) && h30 == n43->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se115, *e43)); 
                  }
                }{ //slice 
                  const HashIndex_COUNTSTORE1_E2_5_map_02* i44 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02*>(COUNTSTORE1_E2_5.index[1]);
                  const HASH_RES_t h31 = COUNTSTORE1_E2_5_mapkey02_idxfn::hash(se116.modify02(customer_c_customer_sk, store_s_store_sk));
                  HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode* n44 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_02::IdxNode*>(i44->slice(se116, h31));
                  COUNTSTORE1_E2_5_entry* e44;
                 
                  if (n44 && (e44 = n44->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e44->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e44->MS_SS_TICKET_NUMBER;
                      long v53 = e44->__av;
                      (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L) ? _c9.addOrDelOnZero(st26.modify(store_sales_ss_addr_sk,ms_ss_ticket_number,store_s_city,v53), v53) : (void)0);
                      n44 = n44->nxt;
                    } while (n44 && (e44 = n44->obj) && h31 == n44->hash &&  COUNTSTORE1_E2_5_mapkey02_idxfn::equals(se116, *e44)); 
                  }
                }{  // temp foreach
                  const HashIndex<tuple4_LLS_L, long>* i45 = static_cast<HashIndex<tuple4_LLS_L, long>*>(_c9.index[0]);
                  HashIndex<tuple4_LLS_L, long>::IdxNode* n45; 
                  tuple4_LLS_L* e45;
                
                  for (size_t i = 0; i < i45->size_; i++)
                  {
                    n45 = i45->buckets_ + i;
                    while (n45 && (e45 = n45->obj))
                    {
                      long store_sales_ss_addr_sk = e45->_1;
                      long ms_ss_ticket_number = e45->_2;
                      STRING_TYPE lift3 = e45->_3;  
                      long v54 = e45->__av; 
                    DOUBLE_TYPE l36 = COUNTCUSTOMER1_L3_1.getValueOrDefault(se117.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,lift3));
                    DOUBLE_TYPE l37 = COUNTCUSTOMER1_L4_1.getValueOrDefault(se118.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,lift3));
                    (/*if */(l25 == Usubstring(lift3, 1L, 30L)) ? _c6.addOrDelOnZero(st27.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l36,l37,(v50 * (v54 != 0 ? 1L : 0L))), (v50 * (v54 != 0 ? 1L : 0L))) : (void)0);      
                      n45 = n45->nxt;
                    }
                  }
                }
              n42 = n42->nxt;
            }
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_012* i46 = static_cast<HashIndex_COUNTSTORE_SALES1_map_012*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_012::IdxNode* n46; 
          COUNTSTORE_SALES1_entry* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
                long customer_c_customer_sk = e46->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_first_name = e46->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e46->CUSTOMER_C_LAST_NAME;
                long v55 = e46->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i47 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[4]);
                  const HASH_RES_t h32 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se123.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n47 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i47->slice(se123, h32));
                  COUNTCUSTOMER1_E1_1_entry* e47;
                 
                  if (n47 && (e47 = n47->obj)) {
                    do {                
                      long store_sales_ss_addr_sk = e47->STORE_SALES_SS_ADDR_SK;
                      long ms_ss_ticket_number = e47->MS_SS_TICKET_NUMBER;
                      STRING_TYPE ms_s_city = e47->MS_S_CITY;
                      long v56 = e47->__av;
                      DOUBLE_TYPE l38 = (COUNTCUSTOMER1_L3_1.getValueOrDefault(se119.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L && ms_s_city == store_s_city) ? COUNTSTORE11_L3_4.getValueOrDefault(se120.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
                      DOUBLE_TYPE l39 = (COUNTCUSTOMER1_L4_1.getValueOrDefault(se121.modify(customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,ms_s_city)) + (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L && ms_s_city == store_s_city) ? COUNTSTORE11_L4_4.getValueOrDefault(se122.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_store_sk,ms_ss_ticket_number)) : 0.0));
                      (/*if */(l25 == Usubstring(ms_s_city, 1L, 30L)) ? _c6.addOrDelOnZero(st28.modify(customer_c_first_name,customer_c_last_name,ms_ss_ticket_number,l38,l39,(v55 * (v56 != 0 ? 1L : 0L))), (v55 * (v56 != 0 ? 1L : 0L))) : (void)0);
                      n47 = n47->nxt;
                    } while (n47 && (e47 = n47->obj) && h32 == n47->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se123, *e47)); 
                  }
                }
              n46 = n46->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple6_SSLDD_L, long>* i48 = static_cast<HashIndex<tuple6_SSLDD_L, long>*>(_c6.index[0]);
          HashIndex<tuple6_SSLDD_L, long>::IdxNode* n48; 
          tuple6_SSLDD_L* e48;
        
          for (size_t i = 0; i < i48->size_; i++)
          {
            n48 = i48->buckets_ + i;
            while (n48 && (e48 = n48->obj))
            {
              STRING_TYPE customer_c_first_name = e48->_1;
              STRING_TYPE customer_c_last_name = e48->_2;
              long ms_ss_ticket_number = e48->_3;
              DOUBLE_TYPE ms_profit = e48->_4;
              DOUBLE_TYPE ms_amt = e48->_5;  
              long v57 = e48->__av; 
            COUNT.addOrDelOnZero(se91.modify(customer_c_last_name,customer_c_first_name,l25,ms_ss_ticket_number,ms_amt,ms_profit),v57);      
              n48 = n48->nxt;
            }
          }
        }{ //slice 
          const HashIndex_COUNTSTORE1_E2_5_map_2* i49 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_2*>(COUNTSTORE1_E2_5.index[2]);
          const HASH_RES_t h33 = COUNTSTORE1_E2_5_mapkey2_idxfn::hash(se125.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE1_E2_5_map_2::IdxNode* n49 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_2::IdxNode*>(i49->slice(se125, h33));
          COUNTSTORE1_E2_5_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              long customer_c_customer_sk = e49->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e49->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e49->MS_SS_TICKET_NUMBER;
              long v58 = e49->__av;
              (/*if */(295L >= store_s_number_employees && store_s_number_employees >= 200L) ? COUNTSTORE7_E1_1.addOrDelOnZero(se124.modify(store_s_city,customer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number),v58) : (void)0);
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h33 == n49->hash &&  COUNTSTORE1_E2_5_mapkey2_idxfn::equals(se125, *e49)); 
          }
        }(/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE7_E1_1STORE_SALES2.addOrDelOnZero(se126.modify(store_s_store_sk,store_s_city),1L) : (void)0);
        { //slice 
          const HashIndex_COUNTSTORE11_L4_4_map_2* i50 = static_cast<HashIndex_COUNTSTORE11_L4_4_map_2*>(COUNTSTORE11_L4_4.index[1]);
          const HASH_RES_t h34 = COUNTSTORE11_L4_4_mapkey2_idxfn::hash(se128.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE11_L4_4_map_2::IdxNode* n50 = static_cast<HashIndex_COUNTSTORE11_L4_4_map_2::IdxNode*>(i50->slice(se128, h34));
          COUNTSTORE11_L4_4_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              long customer_c_customer_sk = e50->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e50->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e50->MS_SS_TICKET_NUMBER;
              DOUBLE_TYPE v59 = e50->__av;
              (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE7_L2_1.addOrDelOnZero(se127.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number),v59) : (void)0);
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h34 == n50->hash &&  COUNTSTORE11_L4_4_mapkey2_idxfn::equals(se128, *e50)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE11_L3_4_map_2* i51 = static_cast<HashIndex_COUNTSTORE11_L3_4_map_2*>(COUNTSTORE11_L3_4.index[1]);
          const HASH_RES_t h35 = COUNTSTORE11_L3_4_mapkey2_idxfn::hash(se130.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE11_L3_4_map_2::IdxNode* n51 = static_cast<HashIndex_COUNTSTORE11_L3_4_map_2::IdxNode*>(i51->slice(se130, h35));
          COUNTSTORE11_L3_4_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              long customer_c_customer_sk = e51->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e51->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e51->MS_SS_TICKET_NUMBER;
              DOUBLE_TYPE v60 = e51->__av;
              (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE7_L3_1.addOrDelOnZero(se129.modify(customer_c_customer_sk,store_sales_ss_addr_sk,store_s_city,ms_ss_ticket_number),v60) : (void)0);
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h35 == n51->hash &&  COUNTSTORE11_L3_4_mapkey2_idxfn::equals(se130, *e51)); 
          }
        }(/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTSTORE_SALES1_E1_6.addOrDelOnZero(se131.modify(store_s_store_sk,store_s_city),1L) : (void)0);
        { //slice 
          const HashIndex_COUNTSTORE1_E2_5_map_2* i52 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_2*>(COUNTSTORE1_E2_5.index[2]);
          const HASH_RES_t h36 = COUNTSTORE1_E2_5_mapkey2_idxfn::hash(se133.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE1_E2_5_map_2::IdxNode* n52 = static_cast<HashIndex_COUNTSTORE1_E2_5_map_2::IdxNode*>(i52->slice(se133, h36));
          COUNTSTORE1_E2_5_entry* e52;
         
          if (n52 && (e52 = n52->obj)) {
            do {                
              long countcustomercustomer_c_customer_sk = e52->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e52->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e52->MS_SS_TICKET_NUMBER;
              long v61 = e52->__av;
              (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTCUSTOMER1_E1_1.addOrDelOnZero(se132.modify(countcustomercustomer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,store_s_city),v61) : (void)0);
              n52 = n52->nxt;
            } while (n52 && (e52 = n52->obj) && h36 == n52->hash &&  COUNTSTORE1_E2_5_mapkey2_idxfn::equals(se133, *e52)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE11_L3_4_map_2* i53 = static_cast<HashIndex_COUNTSTORE11_L3_4_map_2*>(COUNTSTORE11_L3_4.index[1]);
          const HASH_RES_t h37 = COUNTSTORE11_L3_4_mapkey2_idxfn::hash(se135.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE11_L3_4_map_2::IdxNode* n53 = static_cast<HashIndex_COUNTSTORE11_L3_4_map_2::IdxNode*>(i53->slice(se135, h37));
          COUNTSTORE11_L3_4_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              long countcustomercustomer_c_customer_sk = e53->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e53->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e53->MS_SS_TICKET_NUMBER;
              DOUBLE_TYPE v62 = e53->__av;
              (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTCUSTOMER1_L3_1.addOrDelOnZero(se134.modify(countcustomercustomer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,store_s_city),v62) : (void)0);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h37 == n53->hash &&  COUNTSTORE11_L3_4_mapkey2_idxfn::equals(se135, *e53)); 
          }
        }{ //slice 
          const HashIndex_COUNTSTORE11_L4_4_map_2* i54 = static_cast<HashIndex_COUNTSTORE11_L4_4_map_2*>(COUNTSTORE11_L4_4.index[1]);
          const HASH_RES_t h38 = COUNTSTORE11_L4_4_mapkey2_idxfn::hash(se137.modify2(store_s_store_sk));
          HashIndex_COUNTSTORE11_L4_4_map_2::IdxNode* n54 = static_cast<HashIndex_COUNTSTORE11_L4_4_map_2::IdxNode*>(i54->slice(se137, h38));
          COUNTSTORE11_L4_4_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              long countcustomercustomer_c_customer_sk = e54->CUSTOMER_C_CUSTOMER_SK;
              long store_sales_ss_addr_sk = e54->STORE_SALES_SS_ADDR_SK;
              long ms_ss_ticket_number = e54->MS_SS_TICKET_NUMBER;
              DOUBLE_TYPE v63 = e54->__av;
              (/*if */(store_s_number_employees >= 200L && 295L >= store_s_number_employees) ? COUNTCUSTOMER1_L4_1.addOrDelOnZero(se136.modify(countcustomercustomer_c_customer_sk,store_sales_ss_addr_sk,ms_ss_ticket_number,store_s_city),v63) : (void)0);
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h38 == n54->hash &&  COUNTSTORE11_L4_4_mapkey2_idxfn::equals(se137, *e54)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES1_E1_2.clear();
        long l40 = 1L;
        { //slice 
          const HashIndex_DATE_DIM_map_7* i55 = static_cast<HashIndex_DATE_DIM_map_7*>(DATE_DIM.index[1]);
          const HASH_RES_t h39 = DATE_DIM_mapkey7_idxfn::hash(se139.modify7(l40));
          HashIndex_DATE_DIM_map_7::IdxNode* n55 = static_cast<HashIndex_DATE_DIM_map_7::IdxNode*>(i55->slice(se139, h39));
          DATE_DIM_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              long countstore_salesstore_sales_ss_sold_date_sk = e55->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e55->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e55->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e55->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e55->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e55->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_year = e55->DATE_DIM_D_YEAR;
              long date_dim_d_moy = e55->DATE_DIM_D_MOY;
              long date_dim_d_dom = e55->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e55->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e55->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e55->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e55->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e55->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e55->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e55->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e55->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e55->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e55->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e55->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e55->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e55->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e55->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e55->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e55->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e55->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e55->DATE_DIM_D_CURRENT_YEAR;
              long v64 = e55->__av;
              (/*if */(((date_dim_d_year == 1998L) || (date_dim_d_year == 1999L) || (date_dim_d_year == 2000L))) ? COUNTSTORE_SALES1_E1_2.addOrDelOnZero(se138.modify(countstore_salesstore_sales_ss_sold_date_sk),v64) : (void)0);
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h39 == n55->hash &&  DATE_DIM_mapkey7_idxfn::equals(se139, *e55)); 
          }
        }COUNTSTORE_SALES1_E1_5.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i56 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n56; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e56;
        
          for (size_t i = 0; i < i56->size_; i++)
          {
            n56 = i56->buckets_ + i;
            while (n56 && (e56 = n56->obj))
            {
                long countstore_salesstore_sales_ss_hdemo_sk = e56->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e56->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e56->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e56->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e56->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v65 = e56->__av;
                long l41 = ((/*if */(household_demographics_hd_dep_count == 8L) ? 1L : 0L) + (/*if */(household_demographics_hd_vehicle_count > 0L) ? 1L : 0L));
                (/*if */(l41 > 0L) ? COUNTSTORE_SALES1_E1_5.addOrDelOnZero(se140.modify(countstore_salesstore_sales_ss_hdemo_sk),v65) : (void)0);
              n56 = n56->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    tuple2_S_L st1;
    COUNTCUSTOMER1_E1_1_entry se2;
    COUNTSTORE_SALES1_E1_2_entry se3;
    COUNTSTORE_SALES1_E1_5_entry se4;
    tuple2_S_L st2;
    COUNTSTORE_SALES1_E1_6_entry se5;
    COUNTCUSTOMER1_L4_1_entry se6;
    COUNTCUSTOMER1_L3_1_entry se7;
    tuple4_DDS_L st3;
    COUNTCUSTOMER1_L4_1_entry se8;
    COUNTCUSTOMER1_L3_1_entry se9;
    tuple4_DDS_L st4;
    COUNTCUSTOMER1_E1_1_entry se10;
    tuple2_S_L st5;
    COUNTCUSTOMER1_E1_1_entry se11;
    COUNTSTORE_SALES1_E1_2_entry se12;
    COUNTSTORE_SALES1_E1_5_entry se13;
    tuple2_S_L st6;
    COUNTSTORE_SALES1_E1_6_entry se14;
    COUNTCUSTOMER1_L4_1_entry se15;
    COUNTSTORE_SALES1_E1_2_entry se16;
    COUNTSTORE_SALES1_E1_6_entry se17;
    COUNTSTORE_SALES1_E1_5_entry se18;
    COUNTCUSTOMER1_L3_1_entry se19;
    COUNTSTORE_SALES1_E1_2_entry se20;
    COUNTSTORE_SALES1_E1_6_entry se21;
    COUNTSTORE_SALES1_E1_5_entry se22;
    tuple4_DDS_L st7;
    COUNTCUSTOMER1_L4_1_entry se23;
    COUNTSTORE_SALES1_E1_2_entry se24;
    COUNTSTORE_SALES1_E1_6_entry se25;
    COUNTSTORE_SALES1_E1_5_entry se26;
    COUNTCUSTOMER1_L3_1_entry se27;
    COUNTSTORE_SALES1_E1_2_entry se28;
    COUNTSTORE_SALES1_E1_6_entry se29;
    COUNTSTORE_SALES1_E1_5_entry se30;
    tuple4_DDS_L st8;
    COUNTCUSTOMER1_E1_1_entry se31;
    tuple6_DDSSS_L st9;
    COUNTSTORE_SALES1_entry se32;
    COUNTCUSTOMER1_L4_1_entry se33;
    COUNTCUSTOMER1_L3_1_entry se34;
    tuple6_DDSSS_L st10;
    COUNTSTORE_SALES1_entry se35;
    COUNTCUSTOMER1_E1_1_entry se36;
    tuple3_LS_L st11;
    COUNTCUSTOMER1_E1_1_entry se37;
    COUNTSTORE_SALES1_E1_2_entry se38;
    COUNTSTORE_SALES1_E1_5_entry se39;
    tuple3_LS_L st12;
    COUNTSTORE_SALES1_E1_6_entry se40;
    COUNTCUSTOMER1_L3_1_entry se41;
    COUNTCUSTOMER1_L4_1_entry se42;
    tuple6_DDSSS_L st13;
    COUNTCUSTOMER1_L3_1_entry se43;
    COUNTSTORE_SALES1_E1_2_entry se44;
    COUNTSTORE_SALES1_E1_5_entry se45;
    COUNTSTORE_SALES1_E1_6_entry se46;
    COUNTCUSTOMER1_L4_1_entry se47;
    COUNTSTORE_SALES1_E1_2_entry se48;
    COUNTSTORE_SALES1_E1_5_entry se49;
    COUNTSTORE_SALES1_E1_6_entry se50;
    tuple6_DDSSS_L st14;
    COUNTSTORE_SALES1_entry se51;
    COUNTCUSTOMER1_E1_1_entry se52;
    COUNTSTORE1_E2_5_entry se53;
    COUNTSTORE_SALES1_E1_2_entry se54;
    COUNTSTORE_SALES1_E1_5_entry se55;
    COUNTSTORE7_E1_1_entry se56;
    COUNTSTORE_SALES1_E1_2_entry se57;
    COUNTSTORE_SALES1_E1_5_entry se58;
    COUNTSTORE7_E1_1STORE_SALES2_entry se59;
    COUNTSTORE7_L2_1_entry se60;
    COUNTSTORE_SALES1_E1_2_entry se61;
    COUNTSTORE_SALES1_E1_5_entry se62;
    COUNTSTORE7_E1_1STORE_SALES2_entry se63;
    COUNTSTORE7_L3_1_entry se64;
    COUNTSTORE_SALES1_E1_2_entry se65;
    COUNTSTORE_SALES1_E1_5_entry se66;
    COUNTSTORE7_E1_1STORE_SALES2_entry se67;
    COUNTSTORE11_L3_4_entry se68;
    COUNTSTORE_SALES1_E1_2_entry se69;
    COUNTSTORE_SALES1_E1_5_entry se70;
    COUNTSTORE11_L4_4_entry se71;
    COUNTSTORE_SALES1_E1_2_entry se72;
    COUNTSTORE_SALES1_E1_5_entry se73;
    COUNTCUSTOMER1_E1_1_entry se74;
    COUNTSTORE_SALES1_E1_2_entry se75;
    COUNTSTORE_SALES1_E1_5_entry se76;
    COUNTSTORE_SALES1_E1_6_entry se77;
    COUNTCUSTOMER1_L3_1_entry se78;
    COUNTSTORE_SALES1_E1_2_entry se79;
    COUNTSTORE_SALES1_E1_5_entry se80;
    COUNTSTORE_SALES1_E1_6_entry se81;
    COUNTCUSTOMER1_L4_1_entry se82;
    COUNTSTORE_SALES1_E1_2_entry se83;
    COUNTSTORE_SALES1_E1_5_entry se84;
    COUNTSTORE_SALES1_E1_6_entry se85;
    COUNT_entry se86;
    COUNTCUSTOMER1_L3_1_entry se87;
    COUNTCUSTOMER1_L4_1_entry se88;
    tuple5_LDDS_L st15;
    COUNTCUSTOMER1_E1_1_entry se89;
    COUNTSTORE_SALES1_entry se90;
    COUNT_entry se91;
    tuple3_LL_L st16;
    COUNTSTORE7_E1_1_entry se92;
    tuple3_LL_L st17;
    COUNTSTORE1_E2_5_entry se93;
    COUNTSTORE7_L2_1_entry se94;
    COUNTSTORE7_L3_1_entry se95;
    tuple6_SSLDD_L st18;
    COUNTSTORE7_L2_1_entry se96;
    COUNTSTORE7_L3_1_entry se97;
    tuple6_SSLDD_L st19;
    COUNTSTORE_SALES1_entry se98;
    COUNTSTORE7_E1_1_entry se99;
    tuple3_LL_L st20;
    COUNTSTORE7_E1_1_entry se100;
    tuple3_LL_L st21;
    COUNTSTORE1_E2_5_entry se101;
    COUNTSTORE7_L2_1_entry se102;
    COUNTSTORE11_L4_4_entry se103;
    COUNTSTORE7_L3_1_entry se104;
    COUNTSTORE11_L3_4_entry se105;
    tuple6_SSLDD_L st22;
    COUNTSTORE7_L2_1_entry se106;
    COUNTSTORE11_L4_4_entry se107;
    COUNTSTORE7_L3_1_entry se108;
    COUNTSTORE11_L3_4_entry se109;
    tuple6_SSLDD_L st23;
    COUNTSTORE_SALES1_entry se110;
    COUNTSTORE7_E1_1_entry se111;
    COUNTCUSTOMER1_L4_1_entry se112;
    COUNTCUSTOMER1_L3_1_entry se113;
    tuple6_SSLDD_L st24;
    COUNTCUSTOMER1_E1_1_entry se114;
    tuple4_LLS_L st25;
    COUNTCUSTOMER1_E1_1_entry se115;
    tuple4_LLS_L st26;
    COUNTSTORE1_E2_5_entry se116;
    COUNTCUSTOMER1_L3_1_entry se117;
    COUNTCUSTOMER1_L4_1_entry se118;
    tuple6_SSLDD_L st27;
    COUNTCUSTOMER1_L3_1_entry se119;
    COUNTSTORE11_L3_4_entry se120;
    COUNTCUSTOMER1_L4_1_entry se121;
    COUNTSTORE11_L4_4_entry se122;
    tuple6_SSLDD_L st28;
    COUNTCUSTOMER1_E1_1_entry se123;
    COUNTSTORE7_E1_1_entry se124;
    COUNTSTORE1_E2_5_entry se125;
    COUNTSTORE7_E1_1STORE_SALES2_entry se126;
    COUNTSTORE7_L2_1_entry se127;
    COUNTSTORE11_L4_4_entry se128;
    COUNTSTORE7_L3_1_entry se129;
    COUNTSTORE11_L3_4_entry se130;
    COUNTSTORE_SALES1_E1_6_entry se131;
    COUNTCUSTOMER1_E1_1_entry se132;
    COUNTSTORE1_E2_5_entry se133;
    COUNTCUSTOMER1_L3_1_entry se134;
    COUNTSTORE11_L3_4_entry se135;
    COUNTCUSTOMER1_L4_1_entry se136;
    COUNTSTORE11_L4_4_entry se137;
    COUNTSTORE_SALES1_E1_2_entry se138;
    DATE_DIM_entry se139;
    COUNTSTORE_SALES1_E1_5_entry se140;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    HOUSEHOLD_DEMOGRAPHICS_map HOUSEHOLD_DEMOGRAPHICS;
    COUNTSTORE1_E2_5_map COUNTSTORE1_E2_5;
    COUNTSTORE7_E1_1_map COUNTSTORE7_E1_1;
    COUNTSTORE7_E1_1STORE_SALES2_map COUNTSTORE7_E1_1STORE_SALES2;
    COUNTSTORE7_L2_1_map COUNTSTORE7_L2_1;
    COUNTSTORE7_L3_1_map COUNTSTORE7_L3_1;
    COUNTSTORE11_L3_4_map COUNTSTORE11_L3_4;
    COUNTSTORE11_L4_4_map COUNTSTORE11_L4_4;
    COUNTSTORE_SALES1_map COUNTSTORE_SALES1;
    COUNTSTORE_SALES1_E1_2_map COUNTSTORE_SALES1_E1_2;
    COUNTSTORE_SALES1_E1_5_map COUNTSTORE_SALES1_E1_5;
    COUNTSTORE_SALES1_E1_6_map COUNTSTORE_SALES1_E1_6;
    COUNTCUSTOMER1_E1_1_map COUNTCUSTOMER1_E1_1;
    COUNTCUSTOMER1_L3_1_map COUNTCUSTOMER1_L3_1;
    COUNTCUSTOMER1_L4_1_map COUNTCUSTOMER1_L4_1;
    MultiHashMap<tuple6_DDSSS_L,long,HashIndex<tuple6_DDSSS_L,long> > _c1;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c4;
    MultiHashMap<tuple3_LL_L,long,HashIndex<tuple3_LL_L,long> > _c7;
    MultiHashMap<tuple6_SSLDD_L,long,HashIndex<tuple6_SSLDD_L,long> > _c6;
    MultiHashMap<tuple4_LLS_L,long,HashIndex<tuple4_LLS_L,long> > _c9;
    MultiHashMap<tuple2_S_L,long,HashIndex<tuple2_S_L,long> > _c3;
    MultiHashMap<tuple4_DDS_L,long,HashIndex<tuple4_DDS_L,long> > _c2;
    MultiHashMap<tuple5_LDDS_L,long,HashIndex<tuple5_LDDS_L,long> > agg1;
    MultiHashMap<tuple3_LS_L,long,HashIndex<tuple3_LS_L,long> > _c5;
    MultiHashMap<tuple3_LL_L,long,HashIndex<tuple3_LL_L,long> > _c8;
    
  
  };

}
