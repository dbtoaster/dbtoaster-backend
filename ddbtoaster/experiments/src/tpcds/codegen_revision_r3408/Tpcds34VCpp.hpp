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
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  
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
    STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_SALUTATION; STRING_TYPE CUSTOMER_C_PREFERRED_CUST_FLAG; long DN_SS_TICKET_NUMBER; long DN_CNT; long __av; 
    explicit COUNT_entry() { /*CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_SALUTATION = ""; CUSTOMER_C_PREFERRED_CUST_FLAG = ""; DN_SS_TICKET_NUMBER = 0L; DN_CNT = 0L; __av = 0L; */ }
    explicit COUNT_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5, const long c6) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_SALUTATION = c2; CUSTOMER_C_PREFERRED_CUST_FLAG = c3; DN_SS_TICKET_NUMBER = c4; DN_CNT = c5; __av = c6; }
    COUNT_entry(const COUNT_entry& other) : CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_SALUTATION( other.CUSTOMER_C_SALUTATION ), CUSTOMER_C_PREFERRED_CUST_FLAG( other.CUSTOMER_C_PREFERRED_CUST_FLAG ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), DN_CNT( other.DN_CNT ), __av( other.__av ) {}
    FORCE_INLINE COUNT_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const long c5) { CUSTOMER_C_LAST_NAME = c0; CUSTOMER_C_FIRST_NAME = c1; CUSTOMER_C_SALUTATION = c2; CUSTOMER_C_PREFERRED_CUST_FLAG = c3; DN_SS_TICKET_NUMBER = c4; DN_CNT = c5;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_SALUTATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_PREFERRED_CUST_FLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_CNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNT_mapkey012345_idxfn {
    FORCE_INLINE static size_t hash(const COUNT_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_SALUTATION);
      hash_combine(h, e.CUSTOMER_C_PREFERRED_CUST_FLAG);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      hash_combine(h, e.DN_CNT);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNT_entry& x, const COUNT_entry& y) {
      return x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_SALUTATION == y.CUSTOMER_C_SALUTATION && x.CUSTOMER_C_PREFERRED_CUST_FLAG == y.CUSTOMER_C_PREFERRED_CUST_FLAG && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER && x.DN_CNT == y.DN_CNT;
    }
  };
  
  typedef MultiHashMap<COUNT_entry,long,
    HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true>
  > COUNT_map;
  typedef HashIndex<COUNT_entry,long,COUNT_mapkey012345_idxfn,true> HashIndex_COUNT_map_012345;
  
  struct COUNTSTORE_SALES1_entry {
    long CUSTOMER_C_CUSTOMER_SK; STRING_TYPE CUSTOMER_C_SALUTATION; STRING_TYPE CUSTOMER_C_FIRST_NAME; STRING_TYPE CUSTOMER_C_LAST_NAME; STRING_TYPE CUSTOMER_C_PREFERRED_CUST_FLAG; long __av; 
    explicit COUNTSTORE_SALES1_entry() { /*CUSTOMER_C_CUSTOMER_SK = 0L; CUSTOMER_C_SALUTATION = ""; CUSTOMER_C_FIRST_NAME = ""; CUSTOMER_C_LAST_NAME = ""; CUSTOMER_C_PREFERRED_CUST_FLAG = ""; __av = 0L; */ }
    explicit COUNTSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const long c5) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4; __av = c5; }
    COUNTSTORE_SALES1_entry(const COUNTSTORE_SALES1_entry& other) : CUSTOMER_C_CUSTOMER_SK( other.CUSTOMER_C_CUSTOMER_SK ), CUSTOMER_C_SALUTATION( other.CUSTOMER_C_SALUTATION ), CUSTOMER_C_FIRST_NAME( other.CUSTOMER_C_FIRST_NAME ), CUSTOMER_C_LAST_NAME( other.CUSTOMER_C_LAST_NAME ), CUSTOMER_C_PREFERRED_CUST_FLAG( other.CUSTOMER_C_PREFERRED_CUST_FLAG ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { CUSTOMER_C_CUSTOMER_SK = c0; CUSTOMER_C_SALUTATION = c1; CUSTOMER_C_FIRST_NAME = c2; CUSTOMER_C_LAST_NAME = c3; CUSTOMER_C_PREFERRED_CUST_FLAG = c4;  return *this; }
    FORCE_INLINE COUNTSTORE_SALES1_entry& modify0(const long c0) { CUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_SALUTATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_FIRST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_LAST_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_C_PREFERRED_CUST_FLAG);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.CUSTOMER_C_SALUTATION);
      hash_combine(h, e.CUSTOMER_C_FIRST_NAME);
      hash_combine(h, e.CUSTOMER_C_LAST_NAME);
      hash_combine(h, e.CUSTOMER_C_PREFERRED_CUST_FLAG);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES1_entry& x, const COUNTSTORE_SALES1_entry& y) {
      return x.CUSTOMER_C_CUSTOMER_SK == y.CUSTOMER_C_CUSTOMER_SK && x.CUSTOMER_C_SALUTATION == y.CUSTOMER_C_SALUTATION && x.CUSTOMER_C_FIRST_NAME == y.CUSTOMER_C_FIRST_NAME && x.CUSTOMER_C_LAST_NAME == y.CUSTOMER_C_LAST_NAME && x.CUSTOMER_C_PREFERRED_CUST_FLAG == y.CUSTOMER_C_PREFERRED_CUST_FLAG;
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
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey01234_idxfn,true>,
    HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false>
  > COUNTSTORE_SALES1_map;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey01234_idxfn,true> HashIndex_COUNTSTORE_SALES1_map_01234;
  typedef HashIndex<COUNTSTORE_SALES1_entry,long,COUNTSTORE_SALES1_mapkey0_idxfn,false> HashIndex_COUNTSTORE_SALES1_map_0;
  
  struct COUNTSTORE_SALES3_L1_3_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_3_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_3_entry(const long c0, const long c1) { COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_3_entry(const COUNTSTORE_SALES3_L1_3_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_3_entry& modify(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_3_entry& x, const COUNTSTORE_SALES3_L1_3_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_3_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_3_entry,long,COUNTSTORE_SALES3_L1_3_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_3_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_3_entry,long,COUNTSTORE_SALES3_L1_3_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_3_map_0;
  
  struct COUNTSTORE_SALES3_L1_4_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_4_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_4_entry(const long c0, const long c1) { COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_4_entry(const COUNTSTORE_SALES3_L1_4_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_4_entry& modify(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_4_entry& x, const COUNTSTORE_SALES3_L1_4_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_4_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_4_entry,long,COUNTSTORE_SALES3_L1_4_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_4_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_4_entry,long,COUNTSTORE_SALES3_L1_4_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_4_map_0;
  
  struct COUNTSTORE_SALES3_L1_5_entry {
    long COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK; long __av; 
    explicit COUNTSTORE_SALES3_L1_5_entry() { /*COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = 0L; __av = 0L; */ }
    explicit COUNTSTORE_SALES3_L1_5_entry(const long c0, const long c1) { COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = c0; __av = c1; }
    COUNTSTORE_SALES3_L1_5_entry(const COUNTSTORE_SALES3_L1_5_entry& other) : COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK( other.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE COUNTSTORE_SALES3_L1_5_entry& modify(const long c0) { COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTSTORE_SALES3_L1_5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const COUNTSTORE_SALES3_L1_5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTSTORE_SALES3_L1_5_entry& x, const COUNTSTORE_SALES3_L1_5_entry& y) {
      return x.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK == y.COUNTSTORE_SALESSTORE_SALES_SS_HDEMO_SK;
    }
  };
  
  typedef MultiHashMap<COUNTSTORE_SALES3_L1_5_entry,long,
    HashIndex<COUNTSTORE_SALES3_L1_5_entry,long,COUNTSTORE_SALES3_L1_5_mapkey0_idxfn,true>
  > COUNTSTORE_SALES3_L1_5_map;
  typedef HashIndex<COUNTSTORE_SALES3_L1_5_entry,long,COUNTSTORE_SALES3_L1_5_mapkey0_idxfn,true> HashIndex_COUNTSTORE_SALES3_L1_5_map_0;
  
  struct COUNTCUSTOMER1_E1_1_entry {
    long COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER1_E1_1_entry() { /*COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1_entry(const long c0, const long c1, const long c2) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; DN_SS_TICKET_NUMBER = c1; __av = c2; }
    COUNTCUSTOMER1_E1_1_entry(const COUNTCUSTOMER1_E1_1_entry& other) : COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK( other.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify(const long c0, const long c1) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; DN_SS_TICKET_NUMBER = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify1(const long c1) { DN_SS_TICKET_NUMBER = c1;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1_entry& modify0(const long c0) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1_entry& x, const COUNTCUSTOMER1_E1_1_entry& y) {
      return x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
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
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey01_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey1_idxfn,false>,
    HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false>
  > COUNTCUSTOMER1_E1_1_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey01_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1_map_01;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_1;
  typedef HashIndex<COUNTCUSTOMER1_E1_1_entry,long,COUNTCUSTOMER1_E1_1_mapkey0_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1_map_0;
  
  struct COUNTCUSTOMER1_E1_1STORE2_entry {
    long COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK; long COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK; long DN_SS_TICKET_NUMBER; long __av; 
    explicit COUNTCUSTOMER1_E1_1STORE2_entry() { /*COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = 0L; COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK = 0L; DN_SS_TICKET_NUMBER = 0L; __av = 0L; */ }
    explicit COUNTCUSTOMER1_E1_1STORE2_entry(const long c0, const long c1, const long c2, const long c3) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK = c1; DN_SS_TICKET_NUMBER = c2; __av = c3; }
    COUNTCUSTOMER1_E1_1STORE2_entry(const COUNTCUSTOMER1_E1_1STORE2_entry& other) : COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK( other.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK ), COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK( other.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK ), DN_SS_TICKET_NUMBER( other.DN_SS_TICKET_NUMBER ), __av( other.__av ) {}
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE2_entry& modify(const long c0, const long c1, const long c2) { COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK = c0; COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK = c1; DN_SS_TICKET_NUMBER = c2;  return *this; }
    FORCE_INLINE COUNTCUSTOMER1_E1_1STORE2_entry& modify1(const long c1) { COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DN_SS_TICKET_NUMBER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct COUNTCUSTOMER1_E1_1STORE2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK);
      hash_combine(h, e.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK);
      hash_combine(h, e.DN_SS_TICKET_NUMBER);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1STORE2_entry& x, const COUNTCUSTOMER1_E1_1STORE2_entry& y) {
      return x.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK == y.COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK && x.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK == y.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK && x.DN_SS_TICKET_NUMBER == y.DN_SS_TICKET_NUMBER;
    }
  };
  
  struct COUNTCUSTOMER1_E1_1STORE2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const COUNTCUSTOMER1_E1_1STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const COUNTCUSTOMER1_E1_1STORE2_entry& x, const COUNTCUSTOMER1_E1_1STORE2_entry& y) {
      return x.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK == y.COUNTCUSTOMER1_E1_1STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<COUNTCUSTOMER1_E1_1STORE2_entry,long,
    HashIndex<COUNTCUSTOMER1_E1_1STORE2_entry,long,COUNTCUSTOMER1_E1_1STORE2_mapkey012_idxfn,true>,
    HashIndex<COUNTCUSTOMER1_E1_1STORE2_entry,long,COUNTCUSTOMER1_E1_1STORE2_mapkey1_idxfn,false>
  > COUNTCUSTOMER1_E1_1STORE2_map;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE2_entry,long,COUNTCUSTOMER1_E1_1STORE2_mapkey012_idxfn,true> HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_012;
  typedef HashIndex<COUNTCUSTOMER1_E1_1STORE2_entry,long,COUNTCUSTOMER1_E1_1STORE2_mapkey1_idxfn,false> HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_1;
  
  struct tuple6_LSSSS_L {
    long _1; STRING_TYPE _2; STRING_TYPE _3; STRING_TYPE _4; STRING_TYPE _5; long __av;
    explicit tuple6_LSSSS_L() { }
    explicit tuple6_LSSSS_L(const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const STRING_TYPE& c5, long c__av=0L) { _1 = c1; _2 = c2; _3 = c3; _4 = c4; _5 = c5; __av = c__av;}
    int operator==(const tuple6_LSSSS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2) && (this->_3==rhs._3) && (this->_4==rhs._4) && (this->_5==rhs._5)); }
    FORCE_INLINE tuple6_LSSSS_L& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const STRING_TYPE& c4, long c__av) { _1 = c0; _2 = c1; _3 = c2; _4 = c3; _5 = c4; __av = c__av; return *this; }
    static bool equals(const tuple6_LSSSS_L &x, const tuple6_LSSSS_L &y) { return ((x._1==y._1) && (x._2==y._2) && (x._3==y._3) && (x._4==y._4) && (x._5==y._5)); }
    static long hash(const tuple6_LSSSS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
      hash_combine(h, e._3);
      hash_combine(h, e._4);
      hash_combine(h, e._5);
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
    data_t(): tlq_t(), _c1(16U) {
      c7 = STRING_TYPE("Ziebach County");
      c8 = STRING_TYPE("Walker County");
      c4 = STRING_TYPE("Luce County");
      c3 = STRING_TYPE("Barrow County");
      c9 = STRING_TYPE(">10000");
      c5 = STRING_TYPE("Fairfield County");
      c10 = STRING_TYPE("5001-10000");
      c6 = STRING_TYPE("Richland County");
      c2 = STRING_TYPE("Franklin Parish");
      c1 = STRING_TYPE("Daviess County");
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
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_1* i1 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1*>(COUNTCUSTOMER1_E1_1.index[1]);
          const HASH_RES_t h2 = COUNTCUSTOMER1_E1_1_mapkey1_idxfn::hash(se4.modify1(store_sales_ss_ticket_number));
          HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode* n1 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_1::IdxNode*>(i1->slice(se4, h2));
          COUNTCUSTOMER1_E1_1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long customer_c_customer_sk = e1->COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK;
              long v2 = e1->__av;
              long l1 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se2.modify(customer_c_customer_sk,store_sales_ss_ticket_number));
              { //slice 
                const HashIndex_COUNTSTORE_SALES1_map_0* i2 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0*>(COUNTSTORE_SALES1.index[1]);
                const HASH_RES_t h1 = COUNTSTORE_SALES1_mapkey0_idxfn::hash(se3.modify0(customer_c_customer_sk));
                HashIndex_COUNTSTORE_SALES1_map_0::IdxNode* n2 = static_cast<HashIndex_COUNTSTORE_SALES1_map_0::IdxNode*>(i2->slice(se3, h1));
                COUNTSTORE_SALES1_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    STRING_TYPE customer_c_salutation = e2->CUSTOMER_C_SALUTATION;
                    STRING_TYPE customer_c_first_name = e2->CUSTOMER_C_FIRST_NAME;
                    STRING_TYPE customer_c_last_name = e2->CUSTOMER_C_LAST_NAME;
                    STRING_TYPE customer_c_preferred_cust_flag = e2->CUSTOMER_C_PREFERRED_CUST_FLAG;
                    long v3 = e2->__av;
                    (/*if */(20L >= l1 && l1 >= 15L) ? _c1.addOrDelOnZero(st1.modify(l1,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag,(((v2 != 0 ? 1L : 0L) * v3) * -1L)), (((v2 != 0 ? 1L : 0L) * v3) * -1L)) : (void)0);
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  COUNTSTORE_SALES1_mapkey0_idxfn::equals(se3, *e2)); 
                }
              }
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h2 == n1->hash &&  COUNTCUSTOMER1_E1_1_mapkey1_idxfn::equals(se4, *e1)); 
          }
        }{  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_01234* i3 = static_cast<HashIndex_COUNTSTORE_SALES1_map_01234*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_01234::IdxNode* n3; 
          COUNTSTORE_SALES1_entry* e3;
        
          for (size_t i = 0; i < i3->size_; i++)
          {
            n3 = i3->buckets_ + i;
            while (n3 && (e3 = n3->obj))
            {
                long lift1 = e3->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_salutation = e3->CUSTOMER_C_SALUTATION;
                STRING_TYPE customer_c_first_name = e3->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e3->CUSTOMER_C_LAST_NAME;
                STRING_TYPE customer_c_preferred_cust_flag = e3->CUSTOMER_C_PREFERRED_CUST_FLAG;
                long v4 = e3->__av;
                long l2 = (COUNTCUSTOMER1_E1_1.getValueOrDefault(se5.modify(lift1,store_sales_ss_ticket_number)) + (/*if */(lift1 == store_sales_ss_customer_sk) ? (COUNTSTORE_SALES3_L1_3.getValueOrDefault(se6.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES3_L1_4.getValueOrDefault(se7.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_5.getValueOrDefault(se8.modify(store_sales_ss_hdemo_sk)))) : 0L));
                (/*if */(20L >= l2 && l2 >= 15L) ? _c1.addOrDelOnZero(st2.modify(l2,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag,(v4 * ((COUNTCUSTOMER1_E1_1.getValueOrDefault(se9.modify(lift1,store_sales_ss_ticket_number)) + (/*if */(lift1 == store_sales_ss_customer_sk) ? (COUNTSTORE_SALES3_L1_3.getValueOrDefault(se10.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES3_L1_4.getValueOrDefault(se11.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_5.getValueOrDefault(se12.modify(store_sales_ss_hdemo_sk)))) : 0L)) != 0 ? 1L : 0L))), (v4 * ((COUNTCUSTOMER1_E1_1.getValueOrDefault(se9.modify(lift1,store_sales_ss_ticket_number)) + (/*if */(lift1 == store_sales_ss_customer_sk) ? (COUNTSTORE_SALES3_L1_3.getValueOrDefault(se10.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES3_L1_4.getValueOrDefault(se11.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_5.getValueOrDefault(se12.modify(store_sales_ss_hdemo_sk)))) : 0L)) != 0 ? 1L : 0L))) : (void)0);
              n3 = n3->nxt;
            }
          }
        }{  // temp foreach
          const HashIndex<tuple6_LSSSS_L, long>* i4 = static_cast<HashIndex<tuple6_LSSSS_L, long>*>(_c1.index[0]);
          HashIndex<tuple6_LSSSS_L, long>::IdxNode* n4; 
          tuple6_LSSSS_L* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
              long dn_cnt = e4->_1;
              STRING_TYPE customer_c_salutation = e4->_2;
              STRING_TYPE customer_c_first_name = e4->_3;
              STRING_TYPE customer_c_last_name = e4->_4;
              STRING_TYPE customer_c_preferred_cust_flag = e4->_5;  
              long v5 = e4->__av; 
            COUNT.addOrDelOnZero(se1.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,store_sales_ss_ticket_number,dn_cnt),v5);      
              n4 = n4->nxt;
            }
          }
        }COUNTCUSTOMER1_E1_1.addOrDelOnZero(se13.modify(store_sales_ss_customer_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES3_L1_3.getValueOrDefault(se14.modify(store_sales_ss_sold_date_sk)) * (COUNTSTORE_SALES3_L1_4.getValueOrDefault(se15.modify(store_sales_ss_store_sk)) * COUNTSTORE_SALES3_L1_5.getValueOrDefault(se16.modify(store_sales_ss_hdemo_sk)))));
        COUNTCUSTOMER1_E1_1STORE2.addOrDelOnZero(se17.modify(store_sales_ss_customer_sk,store_sales_ss_store_sk,store_sales_ss_ticket_number),(COUNTSTORE_SALES3_L1_3.getValueOrDefault(se18.modify(store_sales_ss_sold_date_sk)) * COUNTSTORE_SALES3_L1_5.getValueOrDefault(se19.modify(store_sales_ss_hdemo_sk))));
      }
    }
    void on_insert_CUSTOMER(const long customer_c_customer_sk, const STRING_TYPE& customer_c_customer_id, const long customer_c_current_cdemo_sk, const long customer_c_current_hdemo_sk, const long customer_c_current_addr_sk, const long customer_c_first_shipto_date_sk, const long customer_c_first_sales_date_sk, const STRING_TYPE& customer_c_salutation, const STRING_TYPE& customer_c_first_name, const STRING_TYPE& customer_c_last_name, const STRING_TYPE& customer_c_preferred_cust_flag, const long customer_c_birth_day, const long customer_c_birth_month, const long customer_c_birth_year, const STRING_TYPE& customer_c_birth_country, const STRING_TYPE& customer_c_login, const STRING_TYPE& customer_c_email_address, const STRING_TYPE& customer_c_last_review_date) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i5 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
          const HASH_RES_t h3 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se22.modify0(customer_c_customer_sk));
          HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n5 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i5->slice(se22, h3));
          COUNTCUSTOMER1_E1_1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long dn_ss_ticket_number = e5->DN_SS_TICKET_NUMBER;
              long v6 = e5->__av;
              long l3 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se21.modify(customer_c_customer_sk,dn_ss_ticket_number));
              (/*if */(l3 >= 15L && 20L >= l3) ? COUNT.addOrDelOnZero(se20.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,dn_ss_ticket_number,l3),(v6 != 0 ? 1L : 0L)) : (void)0);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h3 == n5->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se22, *e5)); 
          }
        }COUNTSTORE_SALES1.addOrDelOnZero(se23.modify(customer_c_customer_sk,customer_c_salutation,customer_c_first_name,customer_c_last_name,customer_c_preferred_cust_flag),1L);
      }
    }
    void on_insert_STORE(const long store_s_store_sk, const STRING_TYPE& store_s_store_id, const date store_s_rec_start_date, const date store_s_rec_end_date, const long store_s_closed_date_sk, const STRING_TYPE& store_s_store_name, const long store_s_number_employees, const long store_s_floor_space, const STRING_TYPE& store_s_hours, const STRING_TYPE& store_s_manager, const long store_s_market_id, const STRING_TYPE& store_s_geography_class, const STRING_TYPE& store_s_market_desc, const STRING_TYPE& store_s_market_manager, const long store_s_division_id, const STRING_TYPE& store_s_division_name, const long store_s_company_id, const STRING_TYPE& store_s_company_name, const STRING_TYPE& store_s_street_number, const STRING_TYPE& store_s_street_name, const STRING_TYPE& store_s_street_type, const STRING_TYPE& store_s_suite_number, const STRING_TYPE& store_s_city, const STRING_TYPE& store_s_county, const STRING_TYPE& store_s_state, const STRING_TYPE& store_s_zip, const STRING_TYPE& store_s_country, const DOUBLE_TYPE store_s_gmt_offset, const DOUBLE_TYPE store_s_tax_precentage) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(((store_s_county == c1) || (store_s_county == c2) || (store_s_county == c3) || (store_s_county == c4) || (store_s_county == c5) || (store_s_county == c6) || (store_s_county == c7) || (store_s_county == c8))) ? COUNTSTORE_SALES3_L1_4.addOrDelOnZero(se24.modify(store_s_store_sk),1L) : (void)0);
        { //slice 
          const HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_1* i6 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_1*>(COUNTCUSTOMER1_E1_1STORE2.index[1]);
          const HASH_RES_t h4 = COUNTCUSTOMER1_E1_1STORE2_mapkey1_idxfn::hash(se26.modify1(store_s_store_sk));
          HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_1::IdxNode* n6 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1STORE2_map_1::IdxNode*>(i6->slice(se26, h4));
          COUNTCUSTOMER1_E1_1STORE2_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              long countcustomercustomer_c_customer_sk = e6->COUNTCUSTOMERCUSTOMER_C_CUSTOMER_SK;
              long dn_ss_ticket_number = e6->DN_SS_TICKET_NUMBER;
              long v7 = e6->__av;
              (/*if */(((store_s_county == c1) || (store_s_county == c2) || (store_s_county == c3) || (store_s_county == c4) || (store_s_county == c5) || (store_s_county == c6) || (store_s_county == c7) || (store_s_county == c8))) ? COUNTCUSTOMER1_E1_1.addOrDelOnZero(se25.modify(countcustomercustomer_c_customer_sk,dn_ss_ticket_number),v7) : (void)0);
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  COUNTCUSTOMER1_E1_1STORE2_mapkey1_idxfn::equals(se26, *e6)); 
          }
        }COUNT.clear();
        {  // foreach
          const HashIndex_COUNTSTORE_SALES1_map_01234* i7 = static_cast<HashIndex_COUNTSTORE_SALES1_map_01234*>(COUNTSTORE_SALES1.index[0]);
          HashIndex_COUNTSTORE_SALES1_map_01234::IdxNode* n7; 
          COUNTSTORE_SALES1_entry* e7;
        
          for (size_t i = 0; i < i7->size_; i++)
          {
            n7 = i7->buckets_ + i;
            while (n7 && (e7 = n7->obj))
            {
                long customer_c_customer_sk = e7->CUSTOMER_C_CUSTOMER_SK;
                STRING_TYPE customer_c_salutation = e7->CUSTOMER_C_SALUTATION;
                STRING_TYPE customer_c_first_name = e7->CUSTOMER_C_FIRST_NAME;
                STRING_TYPE customer_c_last_name = e7->CUSTOMER_C_LAST_NAME;
                STRING_TYPE customer_c_preferred_cust_flag = e7->CUSTOMER_C_PREFERRED_CUST_FLAG;
                long v8 = e7->__av;
                { //slice 
                  const HashIndex_COUNTCUSTOMER1_E1_1_map_0* i8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0*>(COUNTCUSTOMER1_E1_1.index[2]);
                  const HASH_RES_t h5 = COUNTCUSTOMER1_E1_1_mapkey0_idxfn::hash(se29.modify0(customer_c_customer_sk));
                  HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode* n8 = static_cast<HashIndex_COUNTCUSTOMER1_E1_1_map_0::IdxNode*>(i8->slice(se29, h5));
                  COUNTCUSTOMER1_E1_1_entry* e8;
                 
                  if (n8 && (e8 = n8->obj)) {
                    do {                
                      long dn_ss_ticket_number = e8->DN_SS_TICKET_NUMBER;
                      long v9 = e8->__av;
                      long l4 = COUNTCUSTOMER1_E1_1.getValueOrDefault(se28.modify(customer_c_customer_sk,dn_ss_ticket_number));
                      (/*if */(20L >= l4 && l4 >= 15L) ? COUNT.addOrDelOnZero(se27.modify(customer_c_last_name,customer_c_first_name,customer_c_salutation,customer_c_preferred_cust_flag,dn_ss_ticket_number,l4),(v8 * (v9 != 0 ? 1L : 0L))) : (void)0);
                      n8 = n8->nxt;
                    } while (n8 && (e8 = n8->obj) && h5 == n8->hash &&  COUNTCUSTOMER1_E1_1_mapkey0_idxfn::equals(se29, *e8)); 
                  }
                }
              n7 = n7->nxt;
            }
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        COUNTSTORE_SALES3_L1_3.clear();
        {  // foreach
          const HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627* i9 = static_cast<HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627*>(DATE_DIM.index[0]);
          HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627::IdxNode* n9; 
          DATE_DIM_entry* e9;
        
          for (size_t i = 0; i < i9->size_; i++)
          {
            n9 = i9->buckets_ + i;
            while (n9 && (e9 = n9->obj))
            {
                long countstore_salesstore_sales_ss_sold_date_sk = e9->DATE_DIM_D_DATE_SK;
                STRING_TYPE date_dim_d_date_id = e9->DATE_DIM_D_DATE_ID;
                date date_dim_d_date = e9->DATE_DIM_D_DATE;
                long date_dim_d_month_seq = e9->DATE_DIM_D_MONTH_SEQ;
                long date_dim_d_week_seq = e9->DATE_DIM_D_WEEK_SEQ;
                long date_dim_d_quarter_seq = e9->DATE_DIM_D_QUARTER_SEQ;
                long date_dim_d_year = e9->DATE_DIM_D_YEAR;
                long date_dim_d_dow = e9->DATE_DIM_D_DOW;
                long date_dim_d_moy = e9->DATE_DIM_D_MOY;
                long date_dim_d_dom = e9->DATE_DIM_D_DOM;
                long date_dim_d_qoy = e9->DATE_DIM_D_QOY;
                long date_dim_d_fy_year = e9->DATE_DIM_D_FY_YEAR;
                long date_dim_d_fy_quarter_seq = e9->DATE_DIM_D_FY_QUARTER_SEQ;
                long date_dim_d_fy_week_seq = e9->DATE_DIM_D_FY_WEEK_SEQ;
                STRING_TYPE date_dim_d_day_name = e9->DATE_DIM_D_DAY_NAME;
                STRING_TYPE date_dim_d_quarter_name = e9->DATE_DIM_D_QUARTER_NAME;
                STRING_TYPE date_dim_d_holiday = e9->DATE_DIM_D_HOLIDAY;
                STRING_TYPE date_dim_d_weekend = e9->DATE_DIM_D_WEEKEND;
                STRING_TYPE date_dim_d_following_holiday = e9->DATE_DIM_D_FOLLOWING_HOLIDAY;
                long date_dim_d_first_dom = e9->DATE_DIM_D_FIRST_DOM;
                long date_dim_d_last_dom = e9->DATE_DIM_D_LAST_DOM;
                long date_dim_d_same_day_ly = e9->DATE_DIM_D_SAME_DAY_LY;
                long date_dim_d_same_day_lq = e9->DATE_DIM_D_SAME_DAY_LQ;
                STRING_TYPE date_dim_d_current_day = e9->DATE_DIM_D_CURRENT_DAY;
                STRING_TYPE date_dim_d_current_week = e9->DATE_DIM_D_CURRENT_WEEK;
                STRING_TYPE date_dim_d_current_month = e9->DATE_DIM_D_CURRENT_MONTH;
                STRING_TYPE date_dim_d_current_quarter = e9->DATE_DIM_D_CURRENT_QUARTER;
                STRING_TYPE date_dim_d_current_year = e9->DATE_DIM_D_CURRENT_YEAR;
                long v10 = e9->__av;
                long l5 = ((/*if */(3L >= date_dim_d_dom && date_dim_d_dom >= 1L) ? 1L : 0L) + (/*if */(28L >= date_dim_d_dom && date_dim_d_dom >= 25L) ? 1L : 0L));
                (/*if */(((date_dim_d_year == 1999L) || (date_dim_d_year == 2000L) || (date_dim_d_year == 2001L)) && l5 > 0L) ? COUNTSTORE_SALES3_L1_3.addOrDelOnZero(se30.modify(countstore_salesstore_sales_ss_sold_date_sk),v10) : (void)0);
              n9 = n9->nxt;
            }
          }
        }COUNTSTORE_SALES3_L1_5.clear();
        {  // foreach
          const HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234* i10 = static_cast<HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234*>(HOUSEHOLD_DEMOGRAPHICS.index[0]);
          HashIndex_HOUSEHOLD_DEMOGRAPHICS_map_01234::IdxNode* n10; 
          HOUSEHOLD_DEMOGRAPHICS_entry* e10;
        
          for (size_t i = 0; i < i10->size_; i++)
          {
            n10 = i10->buckets_ + i;
            while (n10 && (e10 = n10->obj))
            {
                long countstore_salesstore_sales_ss_hdemo_sk = e10->HOUSEHOLD_DEMOGRAPHICS_HD_DEMO_SK;
                long household_demographics_hd_income_band_sk = e10->HOUSEHOLD_DEMOGRAPHICS_HD_INCOME_BAND_SK;
                STRING_TYPE household_demographics_hd_buy_potential = e10->HOUSEHOLD_DEMOGRAPHICS_HD_BUY_POTENTIAL;
                long household_demographics_hd_dep_count = e10->HOUSEHOLD_DEMOGRAPHICS_HD_DEP_COUNT;
                long household_demographics_hd_vehicle_count = e10->HOUSEHOLD_DEMOGRAPHICS_HD_VEHICLE_COUNT;
                long v11 = e10->__av;
                long l6 = ((/*if */(household_demographics_hd_buy_potential == c9) ? 1L : 0L) + (/*if */(household_demographics_hd_buy_potential == c10) ? 1L : 0L));
                DOUBLE_TYPE l7 = (household_demographics_hd_dep_count * Udiv(household_demographics_hd_vehicle_count));
                (/*if */(household_demographics_hd_vehicle_count > 0L && l6 > 0L && l7 > 1.2) ? COUNTSTORE_SALES3_L1_5.addOrDelOnZero(se31.modify(countstore_salesstore_sales_ss_hdemo_sk),v11) : (void)0);
              n10 = n10->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    COUNT_entry se1;
    COUNTCUSTOMER1_E1_1_entry se2;
    tuple6_LSSSS_L st1;
    COUNTSTORE_SALES1_entry se3;
    COUNTCUSTOMER1_E1_1_entry se4;
    COUNTCUSTOMER1_E1_1_entry se5;
    COUNTSTORE_SALES3_L1_3_entry se6;
    COUNTSTORE_SALES3_L1_4_entry se7;
    COUNTSTORE_SALES3_L1_5_entry se8;
    COUNTCUSTOMER1_E1_1_entry se9;
    COUNTSTORE_SALES3_L1_3_entry se10;
    COUNTSTORE_SALES3_L1_4_entry se11;
    COUNTSTORE_SALES3_L1_5_entry se12;
    tuple6_LSSSS_L st2;
    COUNTCUSTOMER1_E1_1_entry se13;
    COUNTSTORE_SALES3_L1_3_entry se14;
    COUNTSTORE_SALES3_L1_4_entry se15;
    COUNTSTORE_SALES3_L1_5_entry se16;
    COUNTCUSTOMER1_E1_1STORE2_entry se17;
    COUNTSTORE_SALES3_L1_3_entry se18;
    COUNTSTORE_SALES3_L1_5_entry se19;
    COUNT_entry se20;
    COUNTCUSTOMER1_E1_1_entry se21;
    COUNTCUSTOMER1_E1_1_entry se22;
    COUNTSTORE_SALES1_entry se23;
    COUNTSTORE_SALES3_L1_4_entry se24;
    COUNTCUSTOMER1_E1_1_entry se25;
    COUNTCUSTOMER1_E1_1STORE2_entry se26;
    COUNT_entry se27;
    COUNTCUSTOMER1_E1_1_entry se28;
    COUNTCUSTOMER1_E1_1_entry se29;
    COUNTSTORE_SALES3_L1_3_entry se30;
    COUNTSTORE_SALES3_L1_5_entry se31;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    HOUSEHOLD_DEMOGRAPHICS_map HOUSEHOLD_DEMOGRAPHICS;
    COUNTSTORE_SALES1_map COUNTSTORE_SALES1;
    COUNTSTORE_SALES3_L1_3_map COUNTSTORE_SALES3_L1_3;
    COUNTSTORE_SALES3_L1_4_map COUNTSTORE_SALES3_L1_4;
    COUNTSTORE_SALES3_L1_5_map COUNTSTORE_SALES3_L1_5;
    COUNTCUSTOMER1_E1_1_map COUNTCUSTOMER1_E1_1;
    COUNTCUSTOMER1_E1_1STORE2_map COUNTCUSTOMER1_E1_1STORE2;
    MultiHashMap<tuple6_LSSSS_L,long,HashIndex<tuple6_LSSSS_L,long> > _c1;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c9;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c10;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c1;
  
  };

}
