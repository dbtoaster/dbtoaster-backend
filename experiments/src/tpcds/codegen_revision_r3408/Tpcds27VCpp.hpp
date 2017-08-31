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
    FORCE_INLINE DATE_DIM_entry& modify6(const long c6) { DATE_DIM_D_YEAR = c6;  return *this; }
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
  
  struct DATE_DIM_mapkey6_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey6_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey6_idxfn,false> HashIndex_DATE_DIM_map_6;
  
  struct CUSTOMER_DEMOGRAPHICS_entry {
    long CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_GENDER; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS; long CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE; STRING_TYPE CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING; long CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT; long CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT; long CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT; long __av; 
    explicit CUSTOMER_DEMOGRAPHICS_entry() { /*CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = 0L; CUSTOMER_DEMOGRAPHICS_CD_GENDER = ""; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = ""; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = ""; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = 0L; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = ""; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = 0L; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = 0L; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = 0L; __av = 0L; */ }
    explicit CUSTOMER_DEMOGRAPHICS_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const long c8, const long c9) { CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = c0; CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = c4; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = c5; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = c6; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = c7; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = c8; __av = c9; }
    CUSTOMER_DEMOGRAPHICS_entry(const CUSTOMER_DEMOGRAPHICS_entry& other) : CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK( other.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK ), CUSTOMER_DEMOGRAPHICS_CD_GENDER( other.CUSTOMER_DEMOGRAPHICS_CD_GENDER ), CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS( other.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS ), CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS( other.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS ), CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE( other.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE ), CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING( other.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING ), CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT ), CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT ), CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT( other.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT ), __av( other.__av ) {}
    FORCE_INLINE CUSTOMER_DEMOGRAPHICS_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4, const STRING_TYPE& c5, const long c6, const long c7, const long c8) { CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK = c0; CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3; CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE = c4; CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING = c5; CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT = c6; CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT = c7; CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT = c8;  return *this; }
    FORCE_INLINE CUSTOMER_DEMOGRAPHICS_entry& modify123(const STRING_TYPE& c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { CUSTOMER_DEMOGRAPHICS_CD_GENDER = c1; CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS = c2; CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOMER_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTOMER_DEMOGRAPHICS_entry& x, const CUSTOMER_DEMOGRAPHICS_entry& y) {
      return x.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK == y.CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK && x.CUSTOMER_DEMOGRAPHICS_CD_GENDER == y.CUSTOMER_DEMOGRAPHICS_CD_GENDER && x.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE == y.CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE && x.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING == y.CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT && x.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT == y.CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT;
    }
  };
  
  struct CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn {
    FORCE_INLINE static size_t hash(const CUSTOMER_DEMOGRAPHICS_entry& e) {
      size_t h = 0;
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_GENDER);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS);
      hash_combine(h, e.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS);
      return h;
    }
    FORCE_INLINE static bool equals(const CUSTOMER_DEMOGRAPHICS_entry& x, const CUSTOMER_DEMOGRAPHICS_entry& y) {
      return x.CUSTOMER_DEMOGRAPHICS_CD_GENDER == y.CUSTOMER_DEMOGRAPHICS_CD_GENDER && x.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_MARITAL_STATUS && x.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS == y.CUSTOMER_DEMOGRAPHICS_CD_EDUCATION_STATUS;
    }
  };
  
  typedef MultiHashMap<CUSTOMER_DEMOGRAPHICS_entry,long,
    HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn,true>,
    HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn,false>
  > CUSTOMER_DEMOGRAPHICS_map;
  typedef HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey012345678_idxfn,true> HashIndex_CUSTOMER_DEMOGRAPHICS_map_012345678;
  typedef HashIndex<CUSTOMER_DEMOGRAPHICS_entry,long,CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn,false> HashIndex_CUSTOMER_DEMOGRAPHICS_map_123;
  
  struct AGG1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG1_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1_entry(const AGG1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1_entry& x, const AGG1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1_entry,DOUBLE_TYPE,
    HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey01_idxfn,true>
  > AGG1_map;
  typedef HashIndex<AGG1_entry,DOUBLE_TYPE,AGG1_mapkey01_idxfn,true> HashIndex_AGG1_map_01;
  
  struct AGG1ITEM1_L1_2_entry {
    STRING_TYPE STORE_S_STATE; long AGG1ITEMITEM_I_ITEM_SK; long __av; 
    explicit AGG1ITEM1_L1_2_entry() { /*STORE_S_STATE = ""; AGG1ITEMITEM_I_ITEM_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2_entry(const STRING_TYPE& c0, const long c1, const long c2) { STORE_S_STATE = c0; AGG1ITEMITEM_I_ITEM_SK = c1; __av = c2; }
    AGG1ITEM1_L1_2_entry(const AGG1ITEM1_L1_2_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), AGG1ITEMITEM_I_ITEM_SK( other.AGG1ITEMITEM_I_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2_entry& modify(const STRING_TYPE& c0, const long c1) { STORE_S_STATE = c0; AGG1ITEMITEM_I_ITEM_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2_entry& modify1(const long c1) { AGG1ITEMITEM_I_ITEM_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_entry& x, const AGG1ITEM1_L1_2_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2_entry& x, const AGG1ITEM1_L1_2_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2_entry,long,
    HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey1_idxfn,false>
  > AGG1ITEM1_L1_2_map;
  typedef HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2_entry,long,AGG1ITEM1_L1_2_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_L1_2_map_1;
  
  struct AGG1ITEM1_L1_2STORE_SALES1_entry {
    long AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES1_entry() { /*AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES1_entry(const long c0, const long c1) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK = c0; __av = c1; }
    AGG1ITEM1_L1_2STORE_SALES1_entry(const AGG1ITEM1_L1_2STORE_SALES1_entry& other) : AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK( other.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES1_entry& modify(const long c0) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES1_entry& x, const AGG1ITEM1_L1_2STORE_SALES1_entry& y) {
      return x.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK == y.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_CDEMO_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES1_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES1_entry,long,AGG1ITEM1_L1_2STORE_SALES1_mapkey0_idxfn,true>
  > AGG1ITEM1_L1_2STORE_SALES1_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES1_entry,long,AGG1ITEM1_L1_2STORE_SALES1_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES1_map_0;
  
  struct AGG1ITEM1_L1_2STORE_SALES2_entry {
    long AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES2_entry() { /*AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES2_entry(const long c0, const long c1) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    AGG1ITEM1_L1_2STORE_SALES2_entry(const AGG1ITEM1_L1_2STORE_SALES2_entry& other) : AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES2_entry& modify(const long c0) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES2_entry& x, const AGG1ITEM1_L1_2STORE_SALES2_entry& y) {
      return x.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES2_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES2_entry,long,AGG1ITEM1_L1_2STORE_SALES2_mapkey0_idxfn,true>
  > AGG1ITEM1_L1_2STORE_SALES2_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES2_entry,long,AGG1ITEM1_L1_2STORE_SALES2_mapkey0_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES2_map_0;
  
  struct AGG1ITEM1_L1_2STORE_SALES3_entry {
    long AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM1_L1_2STORE_SALES3_entry() { /*AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE_SALES3_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM1_L1_2STORE_SALES3_entry(const AGG1ITEM1_L1_2STORE_SALES3_entry& other) : AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK( other.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES3_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE_SALES3_entry& modify0(const long c0) { AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE_SALES3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES3_entry& x, const AGG1ITEM1_L1_2STORE_SALES3_entry& y) {
      return x.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK == y.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE_SALES3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE_SALES3_entry& x, const AGG1ITEM1_L1_2STORE_SALES3_entry& y) {
      return x.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK == y.AGG1ITEM1_L1_2STORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE_SALES3_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES3_entry,long,AGG1ITEM1_L1_2STORE_SALES3_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2STORE_SALES3_entry,long,AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn,false>
  > AGG1ITEM1_L1_2STORE_SALES3_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES3_entry,long,AGG1ITEM1_L1_2STORE_SALES3_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2STORE_SALES3_entry,long,AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0;
  
  struct AGG1ITEM1_L1_2STORE1_entry {
    long AGG1ITEMITEM_I_ITEM_SK; long AGG1ITEM1_L1_2STORESTORE_S_STORE_SK; long __av; 
    explicit AGG1ITEM1_L1_2STORE1_entry() { /*AGG1ITEMITEM_I_ITEM_SK = 0L; AGG1ITEM1_L1_2STORESTORE_S_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM1_L1_2STORE1_entry(const long c0, const long c1, const long c2) { AGG1ITEMITEM_I_ITEM_SK = c0; AGG1ITEM1_L1_2STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG1ITEM1_L1_2STORE1_entry(const AGG1ITEM1_L1_2STORE1_entry& other) : AGG1ITEMITEM_I_ITEM_SK( other.AGG1ITEMITEM_I_ITEM_SK ), AGG1ITEM1_L1_2STORESTORE_S_STORE_SK( other.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify(const long c0, const long c1) { AGG1ITEMITEM_I_ITEM_SK = c0; AGG1ITEM1_L1_2STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify0(const long c0) { AGG1ITEMITEM_I_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG1ITEM1_L1_2STORE1_entry& modify1(const long c1) { AGG1ITEM1_L1_2STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM1_L1_2STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM1_L1_2STORE1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK && x.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK == y.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG1ITEM1_L1_2STORE1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM1_L1_2STORE1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM1_L1_2STORE1_entry& x, const AGG1ITEM1_L1_2STORE1_entry& y) {
      return x.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK == y.AGG1ITEM1_L1_2STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM1_L1_2STORE1_entry,long,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey0_idxfn,false>,
    HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey1_idxfn,false>
  > AGG1ITEM1_L1_2STORE1_map;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey01_idxfn,true> HashIndex_AGG1ITEM1_L1_2STORE1_map_01;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey0_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE1_map_0;
  typedef HashIndex<AGG1ITEM1_L1_2STORE1_entry,long,AGG1ITEM1_L1_2STORE1_mapkey1_idxfn,false> HashIndex_AGG1ITEM1_L1_2STORE1_map_1;
  
  struct AGG1ITEM4_entry {
    long AGG1ITEMITEM_I_ITEM_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM4_entry() { /*AGG1ITEMITEM_I_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM4_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM4_entry(const AGG1ITEM4_entry& other) : AGG1ITEMITEM_I_ITEM_SK( other.AGG1ITEMITEM_I_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4_entry& modify0(const long c0) { AGG1ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4_entry& x, const AGG1ITEM4_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4_entry& x, const AGG1ITEM4_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4_entry,long,
    HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey0_idxfn,false>
  > AGG1ITEM4_map;
  typedef HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey01_idxfn,true> HashIndex_AGG1ITEM4_map_01;
  typedef HashIndex<AGG1ITEM4_entry,long,AGG1ITEM4_mapkey0_idxfn,false> HashIndex_AGG1ITEM4_map_0;
  
  struct AGG1ITEM4STORE2_entry {
    long AGG1ITEMITEM_I_ITEM_SK; long AGG1ITEM4STORESTORE_S_STORE_SK; long __av; 
    explicit AGG1ITEM4STORE2_entry() { /*AGG1ITEMITEM_I_ITEM_SK = 0L; AGG1ITEM4STORESTORE_S_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1ITEM4STORE2_entry(const long c0, const long c1, const long c2) { AGG1ITEMITEM_I_ITEM_SK = c0; AGG1ITEM4STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG1ITEM4STORE2_entry(const AGG1ITEM4STORE2_entry& other) : AGG1ITEMITEM_I_ITEM_SK( other.AGG1ITEMITEM_I_ITEM_SK ), AGG1ITEM4STORESTORE_S_STORE_SK( other.AGG1ITEM4STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4STORE2_entry& modify(const long c0, const long c1) { AGG1ITEMITEM_I_ITEM_SK = c0; AGG1ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE2_entry& modify0(const long c0) { AGG1ITEMITEM_I_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE2_entry& modify1(const long c1) { AGG1ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM4STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG1ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE2_entry& x, const AGG1ITEM4STORE2_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK && x.AGG1ITEM4STORESTORE_S_STORE_SK == y.AGG1ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG1ITEM4STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE2_entry& x, const AGG1ITEM4STORE2_entry& y) {
      return x.AGG1ITEMITEM_I_ITEM_SK == y.AGG1ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG1ITEM4STORE2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE2_entry& x, const AGG1ITEM4STORE2_entry& y) {
      return x.AGG1ITEM4STORESTORE_S_STORE_SK == y.AGG1ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4STORE2_entry,long,
    HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey0_idxfn,false>,
    HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey1_idxfn,false>
  > AGG1ITEM4STORE2_map;
  typedef HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey01_idxfn,true> HashIndex_AGG1ITEM4STORE2_map_01;
  typedef HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey0_idxfn,false> HashIndex_AGG1ITEM4STORE2_map_0;
  typedef HashIndex<AGG1ITEM4STORE2_entry,long,AGG1ITEM4STORE2_mapkey1_idxfn,false> HashIndex_AGG1ITEM4STORE2_map_1;
  
  struct AGG1ITEM4STORE_SALES3_entry {
    long AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1ITEM4STORE_SALES3_entry() { /*AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK = 0L; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1ITEM4STORE_SALES3_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1ITEM4STORE_SALES3_entry(const AGG1ITEM4STORE_SALES3_entry& other) : AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK( other.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1ITEM4STORE_SALES3_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1ITEM4STORE_SALES3_entry& modify0(const long c0) { AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1ITEM4STORE_SALES3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE_SALES3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE_SALES3_entry& x, const AGG1ITEM4STORE_SALES3_entry& y) {
      return x.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK == y.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG1ITEM4STORE_SALES3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1ITEM4STORE_SALES3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1ITEM4STORE_SALES3_entry& x, const AGG1ITEM4STORE_SALES3_entry& y) {
      return x.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK == y.AGG1ITEM4STORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1ITEM4STORE_SALES3_entry,long,
    HashIndex<AGG1ITEM4STORE_SALES3_entry,long,AGG1ITEM4STORE_SALES3_mapkey01_idxfn,true>,
    HashIndex<AGG1ITEM4STORE_SALES3_entry,long,AGG1ITEM4STORE_SALES3_mapkey0_idxfn,false>
  > AGG1ITEM4STORE_SALES3_map;
  typedef HashIndex<AGG1ITEM4STORE_SALES3_entry,long,AGG1ITEM4STORE_SALES3_mapkey01_idxfn,true> HashIndex_AGG1ITEM4STORE_SALES3_map_01;
  typedef HashIndex<AGG1ITEM4STORE_SALES3_entry,long,AGG1ITEM4STORE_SALES3_mapkey0_idxfn,false> HashIndex_AGG1ITEM4STORE_SALES3_map_0;
  
  struct AGG1STORE2_entry {
    STRING_TYPE AGG1STORESTORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE2_entry() { /*AGG1STORESTORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { AGG1STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE2_entry(const AGG1STORE2_entry& other) : AGG1STORESTORE_S_STATE( other.AGG1STORESTORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AGG1STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE2_entry& modify0(const STRING_TYPE& c0) { AGG1STORESTORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORESTORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2_entry& x, const AGG1STORE2_entry& y) {
      return x.AGG1STORESTORE_S_STATE == y.AGG1STORESTORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2_entry& x, const AGG1STORE2_entry& y) {
      return x.AGG1STORESTORE_S_STATE == y.AGG1STORESTORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE2_entry,long,
    HashIndex<AGG1STORE2_entry,long,AGG1STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE2_entry,long,AGG1STORE2_mapkey0_idxfn,false>
  > AGG1STORE2_map;
  typedef HashIndex<AGG1STORE2_entry,long,AGG1STORE2_mapkey01_idxfn,true> HashIndex_AGG1STORE2_map_01;
  typedef HashIndex<AGG1STORE2_entry,long,AGG1STORE2_mapkey0_idxfn,false> HashIndex_AGG1STORE2_map_0;
  
  struct AGG1STORE2ITEM1_entry {
    long AGG1STORE2ITEMITEM_I_ITEM_SK; STRING_TYPE AGG1STORESTORE_S_STATE; long __av; 
    explicit AGG1STORE2ITEM1_entry() { /*AGG1STORE2ITEMITEM_I_ITEM_SK = 0L; AGG1STORESTORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE2ITEM1_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1STORE2ITEMITEM_I_ITEM_SK = c0; AGG1STORESTORE_S_STATE = c1; __av = c2; }
    AGG1STORE2ITEM1_entry(const AGG1STORE2ITEM1_entry& other) : AGG1STORE2ITEMITEM_I_ITEM_SK( other.AGG1STORE2ITEMITEM_I_ITEM_SK ), AGG1STORESTORE_S_STATE( other.AGG1STORESTORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE2ITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1STORE2ITEMITEM_I_ITEM_SK = c0; AGG1STORESTORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG1STORE2ITEM1_entry& modify0(const long c0) { AGG1STORE2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORE2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORE2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG1STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2ITEM1_entry& x, const AGG1STORE2ITEM1_entry& y) {
      return x.AGG1STORE2ITEMITEM_I_ITEM_SK == y.AGG1STORE2ITEMITEM_I_ITEM_SK && x.AGG1STORESTORE_S_STATE == y.AGG1STORESTORE_S_STATE;
    }
  };
  
  struct AGG1STORE2ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORE2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2ITEM1_entry& x, const AGG1STORE2ITEM1_entry& y) {
      return x.AGG1STORE2ITEMITEM_I_ITEM_SK == y.AGG1STORE2ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE2ITEM1_entry,long,
    HashIndex<AGG1STORE2ITEM1_entry,long,AGG1STORE2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE2ITEM1_entry,long,AGG1STORE2ITEM1_mapkey0_idxfn,false>
  > AGG1STORE2ITEM1_map;
  typedef HashIndex<AGG1STORE2ITEM1_entry,long,AGG1STORE2ITEM1_mapkey01_idxfn,true> HashIndex_AGG1STORE2ITEM1_map_01;
  typedef HashIndex<AGG1STORE2ITEM1_entry,long,AGG1STORE2ITEM1_mapkey0_idxfn,false> HashIndex_AGG1STORE2ITEM1_map_0;
  
  struct AGG1STORE2STORE_SALES4_entry {
    long AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE2STORE_SALES4_entry() { /*AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE2STORE_SALES4_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE2STORE_SALES4_entry(const AGG1STORE2STORE_SALES4_entry& other) : AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK( other.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE2STORE_SALES4_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE2STORE_SALES4_entry& modify0(const long c0) { AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE2STORE_SALES4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2STORE_SALES4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2STORE_SALES4_entry& x, const AGG1STORE2STORE_SALES4_entry& y) {
      return x.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK == y.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE2STORE_SALES4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2STORE_SALES4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2STORE_SALES4_entry& x, const AGG1STORE2STORE_SALES4_entry& y) {
      return x.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK == y.AGG1STORE2STORE_SALESSTORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE2STORE_SALES4_entry,long,
    HashIndex<AGG1STORE2STORE_SALES4_entry,long,AGG1STORE2STORE_SALES4_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE2STORE_SALES4_entry,long,AGG1STORE2STORE_SALES4_mapkey0_idxfn,false>
  > AGG1STORE2STORE_SALES4_map;
  typedef HashIndex<AGG1STORE2STORE_SALES4_entry,long,AGG1STORE2STORE_SALES4_mapkey01_idxfn,true> HashIndex_AGG1STORE2STORE_SALES4_map_01;
  typedef HashIndex<AGG1STORE2STORE_SALES4_entry,long,AGG1STORE2STORE_SALES4_mapkey0_idxfn,false> HashIndex_AGG1STORE2STORE_SALES4_map_0;
  
  struct AGG1STORE2_L1_2_entry {
    STRING_TYPE ITEM_I_ITEM_ID; long AGG1STORESTORE_S_STORE_SK; long __av; 
    explicit AGG1STORE2_L1_2_entry() { /*ITEM_I_ITEM_ID = ""; AGG1STORESTORE_S_STORE_SK = 0L; __av = 0L; */ }
    explicit AGG1STORE2_L1_2_entry(const STRING_TYPE& c0, const long c1, const long c2) { ITEM_I_ITEM_ID = c0; AGG1STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG1STORE2_L1_2_entry(const AGG1STORE2_L1_2_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), AGG1STORESTORE_S_STORE_SK( other.AGG1STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE2_L1_2_entry& modify(const STRING_TYPE& c0, const long c1) { ITEM_I_ITEM_ID = c0; AGG1STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG1STORE2_L1_2_entry& modify1(const long c1) { AGG1STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE2_L1_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.AGG1STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2_L1_2_entry& x, const AGG1STORE2_L1_2_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.AGG1STORESTORE_S_STORE_SK == y.AGG1STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG1STORE2_L1_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE2_L1_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE2_L1_2_entry& x, const AGG1STORE2_L1_2_entry& y) {
      return x.AGG1STORESTORE_S_STORE_SK == y.AGG1STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE2_L1_2_entry,long,
    HashIndex<AGG1STORE2_L1_2_entry,long,AGG1STORE2_L1_2_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE2_L1_2_entry,long,AGG1STORE2_L1_2_mapkey1_idxfn,false>
  > AGG1STORE2_L1_2_map;
  typedef HashIndex<AGG1STORE2_L1_2_entry,long,AGG1STORE2_L1_2_mapkey01_idxfn,true> HashIndex_AGG1STORE2_L1_2_map_01;
  typedef HashIndex<AGG1STORE2_L1_2_entry,long,AGG1STORE2_L1_2_mapkey1_idxfn,false> HashIndex_AGG1STORE2_L1_2_map_1;
  
  struct AGG1STORE7_entry {
    long AGG1STORESTORE_S_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE7_entry() { /*AGG1STORESTORE_S_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE7_entry(const long c0, const STRING_TYPE& c1, const long c2) { AGG1STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE7_entry(const AGG1STORE7_entry& other) : AGG1STORESTORE_S_STORE_SK( other.AGG1STORESTORE_S_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE7_entry& modify(const long c0, const STRING_TYPE& c1) { AGG1STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE7_entry& modify0(const long c0) { AGG1STORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG1STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORESTORE_S_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE7_entry& x, const AGG1STORE7_entry& y) {
      return x.AGG1STORESTORE_S_STORE_SK == y.AGG1STORESTORE_S_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG1STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE7_entry& x, const AGG1STORE7_entry& y) {
      return x.AGG1STORESTORE_S_STORE_SK == y.AGG1STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG1STORE7_entry,long,
    HashIndex<AGG1STORE7_entry,long,AGG1STORE7_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE7_entry,long,AGG1STORE7_mapkey0_idxfn,false>
  > AGG1STORE7_map;
  typedef HashIndex<AGG1STORE7_entry,long,AGG1STORE7_mapkey01_idxfn,true> HashIndex_AGG1STORE7_map_01;
  typedef HashIndex<AGG1STORE7_entry,long,AGG1STORE7_mapkey0_idxfn,false> HashIndex_AGG1STORE7_map_0;
  
  struct AGG1STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; long __av; 
    explicit AGG1STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG1STORE_SALES1_entry(const AGG1STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG1STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_entry& x, const AGG1STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG1STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_entry& x, const AGG1STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1_entry,long,
    HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey1_idxfn,false>
  > AGG1STORE_SALES1_map;
  typedef HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG1STORE_SALES1_map_01;
  typedef HashIndex<AGG1STORE_SALES1_entry,long,AGG1STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG1STORE_SALES1_map_1;
  
  struct AGG1STORE_SALES1_L1_1_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; long __av; 
    explicit AGG1STORE_SALES1_L1_1_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0L; */ }
    explicit AGG1STORE_SALES1_L1_1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG1STORE_SALES1_L1_1_entry(const AGG1STORE_SALES1_L1_1_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG1STORE_SALES1_L1_1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG1STORE_SALES1_L1_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG1STORE_SALES1_L1_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG1STORE_SALES1_L1_1_entry& x, const AGG1STORE_SALES1_L1_1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG1STORE_SALES1_L1_1_entry,long,
    HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey01_idxfn,true>
  > AGG1STORE_SALES1_L1_1_map;
  typedef HashIndex<AGG1STORE_SALES1_L1_1_entry,long,AGG1STORE_SALES1_L1_1_mapkey01_idxfn,true> HashIndex_AGG1STORE_SALES1_L1_1_map_01;
  
  struct AGG2_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG2_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG2_entry(const AGG2_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2_entry& x, const AGG2_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG2_entry,DOUBLE_TYPE,
    HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey01_idxfn,true>
  > AGG2_map;
  typedef HashIndex<AGG2_entry,DOUBLE_TYPE,AGG2_mapkey01_idxfn,true> HashIndex_AGG2_map_01;
  
  struct AGG2ITEM4_entry {
    long AGG2ITEMITEM_I_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG2ITEM4_entry() { /*AGG2ITEMITEM_I_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG2ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG2ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG2ITEM4_entry(const AGG2ITEM4_entry& other) : AGG2ITEMITEM_I_ITEM_SK( other.AGG2ITEMITEM_I_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { AGG2ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG2ITEM4_entry& modify0(const long c0) { AGG2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4_entry& x, const AGG2ITEM4_entry& y) {
      return x.AGG2ITEMITEM_I_ITEM_SK == y.AGG2ITEMITEM_I_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG2ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4_entry& x, const AGG2ITEM4_entry& y) {
      return x.AGG2ITEMITEM_I_ITEM_SK == y.AGG2ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey0_idxfn,false>
  > AGG2ITEM4_map;
  typedef HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey01_idxfn,true> HashIndex_AGG2ITEM4_map_01;
  typedef HashIndex<AGG2ITEM4_entry,DOUBLE_TYPE,AGG2ITEM4_mapkey0_idxfn,false> HashIndex_AGG2ITEM4_map_0;
  
  struct AGG2ITEM4STORE2_entry {
    long AGG2ITEMITEM_I_ITEM_SK; long AGG2ITEM4STORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG2ITEM4STORE2_entry() { /*AGG2ITEMITEM_I_ITEM_SK = 0L; AGG2ITEM4STORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG2ITEM4STORE2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { AGG2ITEMITEM_I_ITEM_SK = c0; AGG2ITEM4STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG2ITEM4STORE2_entry(const AGG2ITEM4STORE2_entry& other) : AGG2ITEMITEM_I_ITEM_SK( other.AGG2ITEMITEM_I_ITEM_SK ), AGG2ITEM4STORESTORE_S_STORE_SK( other.AGG2ITEM4STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG2ITEM4STORE2_entry& modify(const long c0, const long c1) { AGG2ITEMITEM_I_ITEM_SK = c0; AGG2ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG2ITEM4STORE2_entry& modify0(const long c0) { AGG2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG2ITEM4STORE2_entry& modify1(const long c1) { AGG2ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2ITEM4STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2ITEM4STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG2ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE2_entry& x, const AGG2ITEM4STORE2_entry& y) {
      return x.AGG2ITEMITEM_I_ITEM_SK == y.AGG2ITEMITEM_I_ITEM_SK && x.AGG2ITEM4STORESTORE_S_STORE_SK == y.AGG2ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG2ITEM4STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE2_entry& x, const AGG2ITEM4STORE2_entry& y) {
      return x.AGG2ITEMITEM_I_ITEM_SK == y.AGG2ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG2ITEM4STORE2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG2ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2ITEM4STORE2_entry& x, const AGG2ITEM4STORE2_entry& y) {
      return x.AGG2ITEM4STORESTORE_S_STORE_SK == y.AGG2ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey0_idxfn,false>,
    HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey1_idxfn,false>
  > AGG2ITEM4STORE2_map;
  typedef HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey01_idxfn,true> HashIndex_AGG2ITEM4STORE2_map_01;
  typedef HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey0_idxfn,false> HashIndex_AGG2ITEM4STORE2_map_0;
  typedef HashIndex<AGG2ITEM4STORE2_entry,DOUBLE_TYPE,AGG2ITEM4STORE2_mapkey1_idxfn,false> HashIndex_AGG2ITEM4STORE2_map_1;
  
  struct AGG2STORE2_entry {
    STRING_TYPE AGG2STORESTORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE2_entry() { /*AGG2STORESTORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG2STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE2_entry(const AGG2STORE2_entry& other) : AGG2STORESTORE_S_STATE( other.AGG2STORESTORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AGG2STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE2_entry& modify0(const STRING_TYPE& c0) { AGG2STORESTORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORESTORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE2_entry& x, const AGG2STORE2_entry& y) {
      return x.AGG2STORESTORE_S_STATE == y.AGG2STORESTORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE2_entry& x, const AGG2STORE2_entry& y) {
      return x.AGG2STORESTORE_S_STATE == y.AGG2STORESTORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG2STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE2_entry,DOUBLE_TYPE,AGG2STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE2_entry,DOUBLE_TYPE,AGG2STORE2_mapkey0_idxfn,false>
  > AGG2STORE2_map;
  typedef HashIndex<AGG2STORE2_entry,DOUBLE_TYPE,AGG2STORE2_mapkey01_idxfn,true> HashIndex_AGG2STORE2_map_01;
  typedef HashIndex<AGG2STORE2_entry,DOUBLE_TYPE,AGG2STORE2_mapkey0_idxfn,false> HashIndex_AGG2STORE2_map_0;
  
  struct AGG2STORE2ITEM1_entry {
    long AGG2STORE2ITEMITEM_I_ITEM_SK; STRING_TYPE AGG2STORESTORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG2STORE2ITEM1_entry() { /*AGG2STORE2ITEMITEM_I_ITEM_SK = 0L; AGG2STORESTORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG2STORE2ITEM1_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG2STORE2ITEMITEM_I_ITEM_SK = c0; AGG2STORESTORE_S_STATE = c1; __av = c2; }
    AGG2STORE2ITEM1_entry(const AGG2STORE2ITEM1_entry& other) : AGG2STORE2ITEMITEM_I_ITEM_SK( other.AGG2STORE2ITEMITEM_I_ITEM_SK ), AGG2STORESTORE_S_STATE( other.AGG2STORESTORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE2ITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { AGG2STORE2ITEMITEM_I_ITEM_SK = c0; AGG2STORESTORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG2STORE2ITEM1_entry& modify0(const long c0) { AGG2STORE2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2STORE2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORE2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG2STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE2ITEM1_entry& x, const AGG2STORE2ITEM1_entry& y) {
      return x.AGG2STORE2ITEMITEM_I_ITEM_SK == y.AGG2STORE2ITEMITEM_I_ITEM_SK && x.AGG2STORESTORE_S_STATE == y.AGG2STORESTORE_S_STATE;
    }
  };
  
  struct AGG2STORE2ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORE2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE2ITEM1_entry& x, const AGG2STORE2ITEM1_entry& y) {
      return x.AGG2STORE2ITEMITEM_I_ITEM_SK == y.AGG2STORE2ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG2STORE2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE2ITEM1_entry,DOUBLE_TYPE,AGG2STORE2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE2ITEM1_entry,DOUBLE_TYPE,AGG2STORE2ITEM1_mapkey0_idxfn,false>
  > AGG2STORE2ITEM1_map;
  typedef HashIndex<AGG2STORE2ITEM1_entry,DOUBLE_TYPE,AGG2STORE2ITEM1_mapkey01_idxfn,true> HashIndex_AGG2STORE2ITEM1_map_01;
  typedef HashIndex<AGG2STORE2ITEM1_entry,DOUBLE_TYPE,AGG2STORE2ITEM1_mapkey0_idxfn,false> HashIndex_AGG2STORE2ITEM1_map_0;
  
  struct AGG2STORE7_entry {
    long AGG2STORESTORE_S_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE7_entry() { /*AGG2STORESTORE_S_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE7_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG2STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE7_entry(const AGG2STORE7_entry& other) : AGG2STORESTORE_S_STORE_SK( other.AGG2STORESTORE_S_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE7_entry& modify(const long c0, const STRING_TYPE& c1) { AGG2STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE7_entry& modify0(const long c0) { AGG2STORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG2STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORESTORE_S_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE7_entry& x, const AGG2STORE7_entry& y) {
      return x.AGG2STORESTORE_S_STORE_SK == y.AGG2STORESTORE_S_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG2STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE7_entry& x, const AGG2STORE7_entry& y) {
      return x.AGG2STORESTORE_S_STORE_SK == y.AGG2STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG2STORE7_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE7_entry,DOUBLE_TYPE,AGG2STORE7_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE7_entry,DOUBLE_TYPE,AGG2STORE7_mapkey0_idxfn,false>
  > AGG2STORE7_map;
  typedef HashIndex<AGG2STORE7_entry,DOUBLE_TYPE,AGG2STORE7_mapkey01_idxfn,true> HashIndex_AGG2STORE7_map_01;
  typedef HashIndex<AGG2STORE7_entry,DOUBLE_TYPE,AGG2STORE7_mapkey0_idxfn,false> HashIndex_AGG2STORE7_map_0;
  
  struct AGG2STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG2STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG2STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG2STORE_SALES1_entry(const AGG2STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG2STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG2STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG2STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE_SALES1_entry& x, const AGG2STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG2STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG2STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG2STORE_SALES1_entry& x, const AGG2STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG2STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey1_idxfn,false>
  > AGG2STORE_SALES1_map;
  typedef HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG2STORE_SALES1_map_01;
  typedef HashIndex<AGG2STORE_SALES1_entry,DOUBLE_TYPE,AGG2STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG2STORE_SALES1_map_1;
  
  struct AGG3_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG3_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG3_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG3_entry(const AGG3_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG3_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3_entry& x, const AGG3_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG3_entry,DOUBLE_TYPE,
    HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey01_idxfn,true>
  > AGG3_map;
  typedef HashIndex<AGG3_entry,DOUBLE_TYPE,AGG3_mapkey01_idxfn,true> HashIndex_AGG3_map_01;
  
  struct AGG3ITEM4_entry {
    long AGG3ITEMITEM_I_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG3ITEM4_entry() { /*AGG3ITEMITEM_I_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG3ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG3ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG3ITEM4_entry(const AGG3ITEM4_entry& other) : AGG3ITEMITEM_I_ITEM_SK( other.AGG3ITEMITEM_I_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { AGG3ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG3ITEM4_entry& modify0(const long c0) { AGG3ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4_entry& x, const AGG3ITEM4_entry& y) {
      return x.AGG3ITEMITEM_I_ITEM_SK == y.AGG3ITEMITEM_I_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG3ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4_entry& x, const AGG3ITEM4_entry& y) {
      return x.AGG3ITEMITEM_I_ITEM_SK == y.AGG3ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey0_idxfn,false>
  > AGG3ITEM4_map;
  typedef HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey01_idxfn,true> HashIndex_AGG3ITEM4_map_01;
  typedef HashIndex<AGG3ITEM4_entry,DOUBLE_TYPE,AGG3ITEM4_mapkey0_idxfn,false> HashIndex_AGG3ITEM4_map_0;
  
  struct AGG3ITEM4STORE2_entry {
    long AGG3ITEMITEM_I_ITEM_SK; long AGG3ITEM4STORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG3ITEM4STORE2_entry() { /*AGG3ITEMITEM_I_ITEM_SK = 0L; AGG3ITEM4STORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG3ITEM4STORE2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { AGG3ITEMITEM_I_ITEM_SK = c0; AGG3ITEM4STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG3ITEM4STORE2_entry(const AGG3ITEM4STORE2_entry& other) : AGG3ITEMITEM_I_ITEM_SK( other.AGG3ITEMITEM_I_ITEM_SK ), AGG3ITEM4STORESTORE_S_STORE_SK( other.AGG3ITEM4STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG3ITEM4STORE2_entry& modify(const long c0, const long c1) { AGG3ITEMITEM_I_ITEM_SK = c0; AGG3ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG3ITEM4STORE2_entry& modify0(const long c0) { AGG3ITEMITEM_I_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG3ITEM4STORE2_entry& modify1(const long c1) { AGG3ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3ITEM4STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3ITEM4STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG3ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE2_entry& x, const AGG3ITEM4STORE2_entry& y) {
      return x.AGG3ITEMITEM_I_ITEM_SK == y.AGG3ITEMITEM_I_ITEM_SK && x.AGG3ITEM4STORESTORE_S_STORE_SK == y.AGG3ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG3ITEM4STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE2_entry& x, const AGG3ITEM4STORE2_entry& y) {
      return x.AGG3ITEMITEM_I_ITEM_SK == y.AGG3ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG3ITEM4STORE2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG3ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3ITEM4STORE2_entry& x, const AGG3ITEM4STORE2_entry& y) {
      return x.AGG3ITEM4STORESTORE_S_STORE_SK == y.AGG3ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey0_idxfn,false>,
    HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey1_idxfn,false>
  > AGG3ITEM4STORE2_map;
  typedef HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey01_idxfn,true> HashIndex_AGG3ITEM4STORE2_map_01;
  typedef HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey0_idxfn,false> HashIndex_AGG3ITEM4STORE2_map_0;
  typedef HashIndex<AGG3ITEM4STORE2_entry,DOUBLE_TYPE,AGG3ITEM4STORE2_mapkey1_idxfn,false> HashIndex_AGG3ITEM4STORE2_map_1;
  
  struct AGG3STORE2_entry {
    STRING_TYPE AGG3STORESTORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE2_entry() { /*AGG3STORESTORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG3STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE2_entry(const AGG3STORE2_entry& other) : AGG3STORESTORE_S_STATE( other.AGG3STORESTORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AGG3STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE2_entry& modify0(const STRING_TYPE& c0) { AGG3STORESTORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORESTORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE2_entry& x, const AGG3STORE2_entry& y) {
      return x.AGG3STORESTORE_S_STATE == y.AGG3STORESTORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE2_entry& x, const AGG3STORE2_entry& y) {
      return x.AGG3STORESTORE_S_STATE == y.AGG3STORESTORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG3STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE2_entry,DOUBLE_TYPE,AGG3STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE2_entry,DOUBLE_TYPE,AGG3STORE2_mapkey0_idxfn,false>
  > AGG3STORE2_map;
  typedef HashIndex<AGG3STORE2_entry,DOUBLE_TYPE,AGG3STORE2_mapkey01_idxfn,true> HashIndex_AGG3STORE2_map_01;
  typedef HashIndex<AGG3STORE2_entry,DOUBLE_TYPE,AGG3STORE2_mapkey0_idxfn,false> HashIndex_AGG3STORE2_map_0;
  
  struct AGG3STORE2ITEM1_entry {
    long AGG3STORE2ITEMITEM_I_ITEM_SK; STRING_TYPE AGG3STORESTORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG3STORE2ITEM1_entry() { /*AGG3STORE2ITEMITEM_I_ITEM_SK = 0L; AGG3STORESTORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG3STORE2ITEM1_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG3STORE2ITEMITEM_I_ITEM_SK = c0; AGG3STORESTORE_S_STATE = c1; __av = c2; }
    AGG3STORE2ITEM1_entry(const AGG3STORE2ITEM1_entry& other) : AGG3STORE2ITEMITEM_I_ITEM_SK( other.AGG3STORE2ITEMITEM_I_ITEM_SK ), AGG3STORESTORE_S_STATE( other.AGG3STORESTORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE2ITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { AGG3STORE2ITEMITEM_I_ITEM_SK = c0; AGG3STORESTORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG3STORE2ITEM1_entry& modify0(const long c0) { AGG3STORE2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3STORE2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORE2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG3STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE2ITEM1_entry& x, const AGG3STORE2ITEM1_entry& y) {
      return x.AGG3STORE2ITEMITEM_I_ITEM_SK == y.AGG3STORE2ITEMITEM_I_ITEM_SK && x.AGG3STORESTORE_S_STATE == y.AGG3STORESTORE_S_STATE;
    }
  };
  
  struct AGG3STORE2ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORE2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE2ITEM1_entry& x, const AGG3STORE2ITEM1_entry& y) {
      return x.AGG3STORE2ITEMITEM_I_ITEM_SK == y.AGG3STORE2ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG3STORE2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE2ITEM1_entry,DOUBLE_TYPE,AGG3STORE2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE2ITEM1_entry,DOUBLE_TYPE,AGG3STORE2ITEM1_mapkey0_idxfn,false>
  > AGG3STORE2ITEM1_map;
  typedef HashIndex<AGG3STORE2ITEM1_entry,DOUBLE_TYPE,AGG3STORE2ITEM1_mapkey01_idxfn,true> HashIndex_AGG3STORE2ITEM1_map_01;
  typedef HashIndex<AGG3STORE2ITEM1_entry,DOUBLE_TYPE,AGG3STORE2ITEM1_mapkey0_idxfn,false> HashIndex_AGG3STORE2ITEM1_map_0;
  
  struct AGG3STORE7_entry {
    long AGG3STORESTORE_S_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE7_entry() { /*AGG3STORESTORE_S_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE7_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG3STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE7_entry(const AGG3STORE7_entry& other) : AGG3STORESTORE_S_STORE_SK( other.AGG3STORESTORE_S_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE7_entry& modify(const long c0, const STRING_TYPE& c1) { AGG3STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE7_entry& modify0(const long c0) { AGG3STORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG3STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORESTORE_S_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE7_entry& x, const AGG3STORE7_entry& y) {
      return x.AGG3STORESTORE_S_STORE_SK == y.AGG3STORESTORE_S_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG3STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE7_entry& x, const AGG3STORE7_entry& y) {
      return x.AGG3STORESTORE_S_STORE_SK == y.AGG3STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG3STORE7_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE7_entry,DOUBLE_TYPE,AGG3STORE7_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE7_entry,DOUBLE_TYPE,AGG3STORE7_mapkey0_idxfn,false>
  > AGG3STORE7_map;
  typedef HashIndex<AGG3STORE7_entry,DOUBLE_TYPE,AGG3STORE7_mapkey01_idxfn,true> HashIndex_AGG3STORE7_map_01;
  typedef HashIndex<AGG3STORE7_entry,DOUBLE_TYPE,AGG3STORE7_mapkey0_idxfn,false> HashIndex_AGG3STORE7_map_0;
  
  struct AGG3STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG3STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG3STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG3STORE_SALES1_entry(const AGG3STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG3STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG3STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG3STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE_SALES1_entry& x, const AGG3STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG3STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG3STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG3STORE_SALES1_entry& x, const AGG3STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG3STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey1_idxfn,false>
  > AGG3STORE_SALES1_map;
  typedef HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG3STORE_SALES1_map_01;
  typedef HashIndex<AGG3STORE_SALES1_entry,DOUBLE_TYPE,AGG3STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG3STORE_SALES1_map_1;
  
  struct AGG4_entry {
    STRING_TYPE ITEM_I_ITEM_ID; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG4_entry() { /*ITEM_I_ITEM_ID = ""; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG4_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1; __av = c2; }
    AGG4_entry(const AGG4_entry& other) : ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG4_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c0; STORE_S_STATE = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4_entry& x, const AGG4_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG4_entry,DOUBLE_TYPE,
    HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey01_idxfn,true>
  > AGG4_map;
  typedef HashIndex<AGG4_entry,DOUBLE_TYPE,AGG4_mapkey01_idxfn,true> HashIndex_AGG4_map_01;
  
  struct AGG4ITEM4_entry {
    long AGG4ITEMITEM_I_ITEM_SK; STRING_TYPE STORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG4ITEM4_entry() { /*AGG4ITEMITEM_I_ITEM_SK = 0L; STORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG4ITEM4_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG4ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1; __av = c2; }
    AGG4ITEM4_entry(const AGG4ITEM4_entry& other) : AGG4ITEMITEM_I_ITEM_SK( other.AGG4ITEMITEM_I_ITEM_SK ), STORE_S_STATE( other.STORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM4_entry& modify(const long c0, const STRING_TYPE& c1) { AGG4ITEMITEM_I_ITEM_SK = c0; STORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG4ITEM4_entry& modify0(const long c0) { AGG4ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM4_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.STORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4_entry& x, const AGG4ITEM4_entry& y) {
      return x.AGG4ITEMITEM_I_ITEM_SK == y.AGG4ITEMITEM_I_ITEM_SK && x.STORE_S_STATE == y.STORE_S_STATE;
    }
  };
  
  struct AGG4ITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4_entry& x, const AGG4ITEM4_entry& y) {
      return x.AGG4ITEMITEM_I_ITEM_SK == y.AGG4ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM4_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey01_idxfn,true>,
    HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey0_idxfn,false>
  > AGG4ITEM4_map;
  typedef HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey01_idxfn,true> HashIndex_AGG4ITEM4_map_01;
  typedef HashIndex<AGG4ITEM4_entry,DOUBLE_TYPE,AGG4ITEM4_mapkey0_idxfn,false> HashIndex_AGG4ITEM4_map_0;
  
  struct AGG4ITEM4STORE2_entry {
    long AGG4ITEMITEM_I_ITEM_SK; long AGG4ITEM4STORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit AGG4ITEM4STORE2_entry() { /*AGG4ITEMITEM_I_ITEM_SK = 0L; AGG4ITEM4STORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit AGG4ITEM4STORE2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { AGG4ITEMITEM_I_ITEM_SK = c0; AGG4ITEM4STORESTORE_S_STORE_SK = c1; __av = c2; }
    AGG4ITEM4STORE2_entry(const AGG4ITEM4STORE2_entry& other) : AGG4ITEMITEM_I_ITEM_SK( other.AGG4ITEMITEM_I_ITEM_SK ), AGG4ITEM4STORESTORE_S_STORE_SK( other.AGG4ITEM4STORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE AGG4ITEM4STORE2_entry& modify(const long c0, const long c1) { AGG4ITEMITEM_I_ITEM_SK = c0; AGG4ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    FORCE_INLINE AGG4ITEM4STORE2_entry& modify0(const long c0) { AGG4ITEMITEM_I_ITEM_SK = c0;  return *this; }
    FORCE_INLINE AGG4ITEM4STORE2_entry& modify1(const long c1) { AGG4ITEM4STORESTORE_S_STORE_SK = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4ITEM4STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4ITEM4STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG4ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE2_entry& x, const AGG4ITEM4STORE2_entry& y) {
      return x.AGG4ITEMITEM_I_ITEM_SK == y.AGG4ITEMITEM_I_ITEM_SK && x.AGG4ITEM4STORESTORE_S_STORE_SK == y.AGG4ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  struct AGG4ITEM4STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE2_entry& x, const AGG4ITEM4STORE2_entry& y) {
      return x.AGG4ITEMITEM_I_ITEM_SK == y.AGG4ITEMITEM_I_ITEM_SK;
    }
  };
  
  struct AGG4ITEM4STORE2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG4ITEM4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4ITEM4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4ITEM4STORE2_entry& x, const AGG4ITEM4STORE2_entry& y) {
      return x.AGG4ITEM4STORESTORE_S_STORE_SK == y.AGG4ITEM4STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey0_idxfn,false>,
    HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey1_idxfn,false>
  > AGG4ITEM4STORE2_map;
  typedef HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey01_idxfn,true> HashIndex_AGG4ITEM4STORE2_map_01;
  typedef HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey0_idxfn,false> HashIndex_AGG4ITEM4STORE2_map_0;
  typedef HashIndex<AGG4ITEM4STORE2_entry,DOUBLE_TYPE,AGG4ITEM4STORE2_mapkey1_idxfn,false> HashIndex_AGG4ITEM4STORE2_map_1;
  
  struct AGG4STORE2_entry {
    STRING_TYPE AGG4STORESTORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE2_entry() { /*AGG4STORESTORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE2_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG4STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE2_entry(const AGG4STORE2_entry& other) : AGG4STORESTORE_S_STATE( other.AGG4STORESTORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE2_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { AGG4STORESTORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE2_entry& modify0(const STRING_TYPE& c0) { AGG4STORESTORE_S_STATE = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORESTORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE2_entry& x, const AGG4STORE2_entry& y) {
      return x.AGG4STORESTORE_S_STATE == y.AGG4STORESTORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE2_entry& x, const AGG4STORE2_entry& y) {
      return x.AGG4STORESTORE_S_STATE == y.AGG4STORESTORE_S_STATE;
    }
  };
  
  typedef MultiHashMap<AGG4STORE2_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE2_entry,DOUBLE_TYPE,AGG4STORE2_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE2_entry,DOUBLE_TYPE,AGG4STORE2_mapkey0_idxfn,false>
  > AGG4STORE2_map;
  typedef HashIndex<AGG4STORE2_entry,DOUBLE_TYPE,AGG4STORE2_mapkey01_idxfn,true> HashIndex_AGG4STORE2_map_01;
  typedef HashIndex<AGG4STORE2_entry,DOUBLE_TYPE,AGG4STORE2_mapkey0_idxfn,false> HashIndex_AGG4STORE2_map_0;
  
  struct AGG4STORE2ITEM1_entry {
    long AGG4STORE2ITEMITEM_I_ITEM_SK; STRING_TYPE AGG4STORESTORE_S_STATE; DOUBLE_TYPE __av; 
    explicit AGG4STORE2ITEM1_entry() { /*AGG4STORE2ITEMITEM_I_ITEM_SK = 0L; AGG4STORESTORE_S_STATE = ""; __av = 0.0; */ }
    explicit AGG4STORE2ITEM1_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG4STORE2ITEMITEM_I_ITEM_SK = c0; AGG4STORESTORE_S_STATE = c1; __av = c2; }
    AGG4STORE2ITEM1_entry(const AGG4STORE2ITEM1_entry& other) : AGG4STORE2ITEMITEM_I_ITEM_SK( other.AGG4STORE2ITEMITEM_I_ITEM_SK ), AGG4STORESTORE_S_STATE( other.AGG4STORESTORE_S_STATE ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE2ITEM1_entry& modify(const long c0, const STRING_TYPE& c1) { AGG4STORE2ITEMITEM_I_ITEM_SK = c0; AGG4STORESTORE_S_STATE = c1;  return *this; }
    FORCE_INLINE AGG4STORE2ITEM1_entry& modify0(const long c0) { AGG4STORE2ITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4STORE2ITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4STORESTORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE2ITEM1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORE2ITEMITEM_I_ITEM_SK);
      hash_combine(h, e.AGG4STORESTORE_S_STATE);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE2ITEM1_entry& x, const AGG4STORE2ITEM1_entry& y) {
      return x.AGG4STORE2ITEMITEM_I_ITEM_SK == y.AGG4STORE2ITEMITEM_I_ITEM_SK && x.AGG4STORESTORE_S_STATE == y.AGG4STORESTORE_S_STATE;
    }
  };
  
  struct AGG4STORE2ITEM1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE2ITEM1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORE2ITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE2ITEM1_entry& x, const AGG4STORE2ITEM1_entry& y) {
      return x.AGG4STORE2ITEMITEM_I_ITEM_SK == y.AGG4STORE2ITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<AGG4STORE2ITEM1_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE2ITEM1_entry,DOUBLE_TYPE,AGG4STORE2ITEM1_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE2ITEM1_entry,DOUBLE_TYPE,AGG4STORE2ITEM1_mapkey0_idxfn,false>
  > AGG4STORE2ITEM1_map;
  typedef HashIndex<AGG4STORE2ITEM1_entry,DOUBLE_TYPE,AGG4STORE2ITEM1_mapkey01_idxfn,true> HashIndex_AGG4STORE2ITEM1_map_01;
  typedef HashIndex<AGG4STORE2ITEM1_entry,DOUBLE_TYPE,AGG4STORE2ITEM1_mapkey0_idxfn,false> HashIndex_AGG4STORE2ITEM1_map_0;
  
  struct AGG4STORE7_entry {
    long AGG4STORESTORE_S_STORE_SK; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE7_entry() { /*AGG4STORESTORE_S_STORE_SK = 0L; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE7_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { AGG4STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE7_entry(const AGG4STORE7_entry& other) : AGG4STORESTORE_S_STORE_SK( other.AGG4STORESTORE_S_STORE_SK ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE7_entry& modify(const long c0, const STRING_TYPE& c1) { AGG4STORESTORE_S_STORE_SK = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE7_entry& modify0(const long c0) { AGG4STORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, AGG4STORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE7_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORESTORE_S_STORE_SK);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE7_entry& x, const AGG4STORE7_entry& y) {
      return x.AGG4STORESTORE_S_STORE_SK == y.AGG4STORESTORE_S_STORE_SK && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE7_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE7_entry& e) {
      size_t h = 0;
      hash_combine(h, e.AGG4STORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE7_entry& x, const AGG4STORE7_entry& y) {
      return x.AGG4STORESTORE_S_STORE_SK == y.AGG4STORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<AGG4STORE7_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE7_entry,DOUBLE_TYPE,AGG4STORE7_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE7_entry,DOUBLE_TYPE,AGG4STORE7_mapkey0_idxfn,false>
  > AGG4STORE7_map;
  typedef HashIndex<AGG4STORE7_entry,DOUBLE_TYPE,AGG4STORE7_mapkey01_idxfn,true> HashIndex_AGG4STORE7_map_01;
  typedef HashIndex<AGG4STORE7_entry,DOUBLE_TYPE,AGG4STORE7_mapkey0_idxfn,false> HashIndex_AGG4STORE7_map_0;
  
  struct AGG4STORE_SALES1_entry {
    STRING_TYPE STORE_S_STATE; STRING_TYPE ITEM_I_ITEM_ID; DOUBLE_TYPE __av; 
    explicit AGG4STORE_SALES1_entry() { /*STORE_S_STATE = ""; ITEM_I_ITEM_ID = ""; __av = 0.0; */ }
    explicit AGG4STORE_SALES1_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1; __av = c2; }
    AGG4STORE_SALES1_entry(const AGG4STORE_SALES1_entry& other) : STORE_S_STATE( other.STORE_S_STATE ), ITEM_I_ITEM_ID( other.ITEM_I_ITEM_ID ), __av( other.__av ) {}
    FORCE_INLINE AGG4STORE_SALES1_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STATE = c0; ITEM_I_ITEM_ID = c1;  return *this; }
    FORCE_INLINE AGG4STORE_SALES1_entry& modify1(const STRING_TYPE& c1) { ITEM_I_ITEM_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STATE);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, ITEM_I_ITEM_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct AGG4STORE_SALES1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STATE);
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE_SALES1_entry& x, const AGG4STORE_SALES1_entry& y) {
      return x.STORE_S_STATE == y.STORE_S_STATE && x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  struct AGG4STORE_SALES1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const AGG4STORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.ITEM_I_ITEM_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const AGG4STORE_SALES1_entry& x, const AGG4STORE_SALES1_entry& y) {
      return x.ITEM_I_ITEM_ID == y.ITEM_I_ITEM_ID;
    }
  };
  
  typedef MultiHashMap<AGG4STORE_SALES1_entry,DOUBLE_TYPE,
    HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey01_idxfn,true>,
    HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey1_idxfn,false>
  > AGG4STORE_SALES1_map;
  typedef HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey01_idxfn,true> HashIndex_AGG4STORE_SALES1_map_01;
  typedef HashIndex<AGG4STORE_SALES1_entry,DOUBLE_TYPE,AGG4STORE_SALES1_mapkey1_idxfn,false> HashIndex_AGG4STORE_SALES1_map_1;
  
  struct tuple2_S_D {
    STRING_TYPE _1; DOUBLE_TYPE __av;
    explicit tuple2_S_D() { }
    explicit tuple2_S_D(const STRING_TYPE& c1, DOUBLE_TYPE c__av=0.0) { _1 = c1; __av = c__av;}
    int operator==(const tuple2_S_D &rhs) const { return ((this->_1==rhs._1)); }
    FORCE_INLINE tuple2_S_D& modify(const STRING_TYPE& c0, DOUBLE_TYPE c__av) { _1 = c0; __av = c__av; return *this; }
    static bool equals(const tuple2_S_D &x, const tuple2_S_D &y) { return ((x._1==y._1)); }
    static long hash(const tuple2_S_D &e) {
      size_t h = 0;
      hash_combine(h, e._1);
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
      const AGG1_map& _AGG1 = get_AGG1();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG1), _AGG1, "\t");
      ar << "\n";
      const AGG2_map& _AGG2 = get_AGG2();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG2), _AGG2, "\t");
      ar << "\n";
      const AGG3_map& _AGG3 = get_AGG3();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG3), _AGG3, "\t");
      ar << "\n";
      const AGG4_map& _AGG4 = get_AGG4();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(AGG4), _AGG4, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const AGG1_map& get_AGG1() const {
      return AGG1;
    
    }
    const AGG2_map& get_AGG2() const {
      return AGG2;
    
    }
    const AGG3_map& get_AGG3() const {
      return AGG3;
    
    }
    const AGG4_map& get_AGG4() const {
      return AGG4;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    AGG1_map AGG1;
    AGG2_map AGG2;
    AGG3_map AGG3;
    AGG4_map AGG4;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), _c1(16U), _c4(16U), _c7(16U), _c6(16U), _c3(16U), _c2(16U), _c5(16U), _c8(16U) {
      c2 = STRING_TYPE("LA");
      c7 = STRING_TYPE("M");
      c4 = STRING_TYPE("MI");
      c6 = STRING_TYPE("OH");
      c5 = STRING_TYPE("SC");
      c3 = STRING_TYPE("GA");
      c8 = STRING_TYPE("W");
      c9 = STRING_TYPE("College");
      c1 = STRING_TYPE("MO");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
    }
    
    void on_insert_CUSTOMER_DEMOGRAPHICS(const long customer_demographics_cd_demo_sk, const STRING_TYPE customer_demographics_cd_gender, const STRING_TYPE customer_demographics_cd_marital_status, const STRING_TYPE customer_demographics_cd_education_status, const long customer_demographics_cd_purchase_estimate, const STRING_TYPE customer_demographics_cd_credit_rating, const long customer_demographics_cd_dep_count, const long customer_demographics_cd_dep_employed_count, const long customer_demographics_cd_dep_college_count) {
      CUSTOMER_DEMOGRAPHICS_entry e(customer_demographics_cd_demo_sk, customer_demographics_cd_gender, customer_demographics_cd_marital_status, customer_demographics_cd_education_status, customer_demographics_cd_purchase_estimate, customer_demographics_cd_credit_rating, customer_demographics_cd_dep_count, customer_demographics_cd_dep_employed_count, customer_demographics_cd_dep_college_count, 1L);
      CUSTOMER_DEMOGRAPHICS.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_STORE_SALES(const long store_sales_ss_sold_date_sk, const long store_sales_ss_sold_time_sk, const long store_sales_ss_item_sk, const long store_sales_ss_customer_sk, const long store_sales_ss_cdemo_sk, const long store_sales_ss_hdemo_sk, const long store_sales_ss_addr_sk, const long store_sales_ss_store_sk, const long store_sales_ss_promo_sk, const long store_sales_ss_ticket_number, const long store_sales_ss_quantity, const DOUBLE_TYPE store_sales_ss_wholesale_cost, const DOUBLE_TYPE store_sales_ss_list_price, const DOUBLE_TYPE store_sales_ss_sales_price, const DOUBLE_TYPE store_sales_ss_ext_discount_amt, const DOUBLE_TYPE store_sales_ss_ext_sales_price, const DOUBLE_TYPE store_sales_ss_ext_wholesale_cost, const DOUBLE_TYPE store_sales_ss_ext_list_price, const DOUBLE_TYPE store_sales_ss_ext_tax, const DOUBLE_TYPE store_sales_ss_coupon_amt, const DOUBLE_TYPE store_sales_ss_net_paid, const DOUBLE_TYPE store_sales_ss_net_paid_inc_tax, const DOUBLE_TYPE store_sales_ss_net_profit) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i1 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h1 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se4.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n1 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i1->slice(se4, h1));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE store_s_state = e1->STORE_S_STATE;
              long v1 = e1->__av;
              AGG1ITEM1_L1_2.addOrDelOnZero(se1.modify(store_s_state,store_sales_ss_item_sk),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se2.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se3.modify(store_sales_ss_sold_date_sk)) * v1)));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }AGG1ITEM1_L1_2STORE1.addOrDelOnZero(se5.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se6.modify(store_sales_ss_sold_date_sk)) * AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se7.modify(store_sales_ss_cdemo_sk))));
        { //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i2 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h2 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se11.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n2 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i2->slice(se11, h2));
          AGG1ITEM4STORE_SALES3_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE store_s_state = e2->STORE_S_STATE;
              long v2 = e2->__av;
              AGG1ITEM4.addOrDelOnZero(se8.modify(store_sales_ss_item_sk,store_s_state),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se9.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se10.modify(store_sales_ss_cdemo_sk)) * (v2 * store_sales_ss_quantity))));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se11, *e2)); 
          }
        }AGG1ITEM4STORE2.addOrDelOnZero(se12.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se13.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se14.modify(store_sales_ss_cdemo_sk)) * store_sales_ss_quantity)));
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i3 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h4 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se19.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n3 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i3->slice(se19, h4));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              STRING_TYPE agg1storestore_s_state = e3->STORE_S_STATE;
              long v3 = e3->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i4 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h3 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se18.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n4 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i4->slice(se18, h3));
                AGG1STORE2STORE_SALES4_entry* e4;
               
                if (n4 && (e4 = n4->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e4->ITEM_I_ITEM_ID;
                    long v4 = e4->__av;
                    AGG1STORE2.addOrDelOnZero(se15.modify(agg1storestore_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se16.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se17.modify(store_sales_ss_cdemo_sk)) * (v3 * (v4 * store_sales_ss_quantity)))));
                    n4 = n4->nxt;
                  } while (n4 && (e4 = n4->obj) && h3 == n4->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se18, *e4)); 
                }
              }
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h4 == n3->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se19, *e3)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i5 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h5 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se23.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n5 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i5->slice(se23, h5));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE agg1storestore_s_state = e5->STORE_S_STATE;
              long v5 = e5->__av;
              AGG1STORE2ITEM1.addOrDelOnZero(se20.modify(store_sales_ss_item_sk,agg1storestore_s_state),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se21.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se22.modify(store_sales_ss_sold_date_sk)) * (v5 * store_sales_ss_quantity))));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se23, *e5)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i6 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h6 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se27.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n6 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i6->slice(se27, h6));
          AGG1STORE2STORE_SALES4_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e6->ITEM_I_ITEM_ID;
              long v6 = e6->__av;
              AGG1STORE2_L1_2.addOrDelOnZero(se24.modify(item_i_item_id,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se25.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se26.modify(store_sales_ss_sold_date_sk)) * v6)));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se27, *e6)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i7 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h7 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se31.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n7 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i7->slice(se31, h7));
          AGG1STORE2STORE_SALES4_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e7->ITEM_I_ITEM_ID;
              long v7 = e7->__av;
              AGG1STORE7.addOrDelOnZero(se28.modify(store_sales_ss_store_sk,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se29.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se30.modify(store_sales_ss_cdemo_sk)) * (v7 * store_sales_ss_quantity))));
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se31, *e7)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i8 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h9 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se36.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n8 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i8->slice(se36, h9));
          AGG1ITEM4STORE_SALES3_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              STRING_TYPE store_s_state = e8->STORE_S_STATE;
              long v8 = e8->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i9 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h8 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se35.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n9 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i9->slice(se35, h8));
                AGG1STORE2STORE_SALES4_entry* e9;
               
                if (n9 && (e9 = n9->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e9->ITEM_I_ITEM_ID;
                    long v9 = e9->__av;
                    AGG1STORE_SALES1.addOrDelOnZero(se32.modify(store_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se33.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se34.modify(store_sales_ss_sold_date_sk)) * (v8 * (v9 * store_sales_ss_quantity)))));
                    n9 = n9->nxt;
                  } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se35, *e9)); 
                }
              }
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h9 == n8->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se36, *e8)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i10 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h11 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se41.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n10 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i10->slice(se41, h11));
          AGG1STORE2STORE_SALES4_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e10->ITEM_I_ITEM_ID;
              long v10 = e10->__av;
              { //slice 
                const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i11 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
                const HASH_RES_t h10 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se40.modify0(store_sales_ss_store_sk));
                HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n11 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i11->slice(se40, h10));
                AGG1ITEM1_L1_2STORE_SALES3_entry* e11;
               
                if (n11 && (e11 = n11->obj)) {
                  do {                
                    STRING_TYPE store_s_state = e11->STORE_S_STATE;
                    long v11 = e11->__av;
                    AGG1STORE_SALES1_L1_1.addOrDelOnZero(se37.modify(item_i_item_id,store_s_state),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se38.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se39.modify(store_sales_ss_sold_date_sk)) * (v10 * v11))));
                    n11 = n11->nxt;
                  } while (n11 && (e11 = n11->obj) && h10 == n11->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se40, *e11)); 
                }
              }
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h11 == n10->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se41, *e10)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i12 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h12 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se45.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n12 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i12->slice(se45, h12));
          AGG1ITEM4STORE_SALES3_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              STRING_TYPE store_s_state = e12->STORE_S_STATE;
              long v12 = e12->__av;
              AGG2ITEM4.addOrDelOnZero(se42.modify(store_sales_ss_item_sk,store_s_state),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se43.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se44.modify(store_sales_ss_cdemo_sk)) * (v12 * store_sales_ss_list_price))));
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se45, *e12)); 
          }
        }AGG2ITEM4STORE2.addOrDelOnZero(se46.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se47.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se48.modify(store_sales_ss_cdemo_sk)) * store_sales_ss_list_price)));
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i13 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h14 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se53.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n13 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i13->slice(se53, h14));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              STRING_TYPE agg2storestore_s_state = e13->STORE_S_STATE;
              long v13 = e13->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i14 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h13 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se52.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n14 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i14->slice(se52, h13));
                AGG1STORE2STORE_SALES4_entry* e14;
               
                if (n14 && (e14 = n14->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e14->ITEM_I_ITEM_ID;
                    long v14 = e14->__av;
                    AGG2STORE2.addOrDelOnZero(se49.modify(agg2storestore_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se50.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se51.modify(store_sales_ss_cdemo_sk)) * (v13 * (v14 * store_sales_ss_list_price)))));
                    n14 = n14->nxt;
                  } while (n14 && (e14 = n14->obj) && h13 == n14->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se52, *e14)); 
                }
              }
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h14 == n13->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se53, *e13)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i15 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h15 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se57.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n15 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i15->slice(se57, h15));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              STRING_TYPE agg2storestore_s_state = e15->STORE_S_STATE;
              long v15 = e15->__av;
              AGG2STORE2ITEM1.addOrDelOnZero(se54.modify(store_sales_ss_item_sk,agg2storestore_s_state),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se55.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se56.modify(store_sales_ss_sold_date_sk)) * (v15 * store_sales_ss_list_price))));
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h15 == n15->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se57, *e15)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i16 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h16 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se61.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n16 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i16->slice(se61, h16));
          AGG1STORE2STORE_SALES4_entry* e16;
         
          if (n16 && (e16 = n16->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e16->ITEM_I_ITEM_ID;
              long v16 = e16->__av;
              AGG2STORE7.addOrDelOnZero(se58.modify(store_sales_ss_store_sk,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se59.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se60.modify(store_sales_ss_cdemo_sk)) * (v16 * store_sales_ss_list_price))));
              n16 = n16->nxt;
            } while (n16 && (e16 = n16->obj) && h16 == n16->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se61, *e16)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i17 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h18 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se66.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n17 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i17->slice(se66, h18));
          AGG1ITEM4STORE_SALES3_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              STRING_TYPE store_s_state = e17->STORE_S_STATE;
              long v17 = e17->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i18 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h17 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se65.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n18 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i18->slice(se65, h17));
                AGG1STORE2STORE_SALES4_entry* e18;
               
                if (n18 && (e18 = n18->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e18->ITEM_I_ITEM_ID;
                    long v18 = e18->__av;
                    AGG2STORE_SALES1.addOrDelOnZero(se62.modify(store_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se63.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se64.modify(store_sales_ss_sold_date_sk)) * (v17 * (v18 * store_sales_ss_list_price)))));
                    n18 = n18->nxt;
                  } while (n18 && (e18 = n18->obj) && h17 == n18->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se65, *e18)); 
                }
              }
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h18 == n17->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se66, *e17)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i19 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h19 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se70.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n19 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i19->slice(se70, h19));
          AGG1ITEM4STORE_SALES3_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              STRING_TYPE store_s_state = e19->STORE_S_STATE;
              long v19 = e19->__av;
              AGG3ITEM4.addOrDelOnZero(se67.modify(store_sales_ss_item_sk,store_s_state),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se68.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se69.modify(store_sales_ss_cdemo_sk)) * (v19 * store_sales_ss_coupon_amt))));
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h19 == n19->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se70, *e19)); 
          }
        }AGG3ITEM4STORE2.addOrDelOnZero(se71.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se72.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se73.modify(store_sales_ss_cdemo_sk)) * store_sales_ss_coupon_amt)));
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i20 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h21 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se78.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n20 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i20->slice(se78, h21));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              STRING_TYPE agg3storestore_s_state = e20->STORE_S_STATE;
              long v20 = e20->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i21 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h20 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se77.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n21 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i21->slice(se77, h20));
                AGG1STORE2STORE_SALES4_entry* e21;
               
                if (n21 && (e21 = n21->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e21->ITEM_I_ITEM_ID;
                    long v21 = e21->__av;
                    AGG3STORE2.addOrDelOnZero(se74.modify(agg3storestore_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se75.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se76.modify(store_sales_ss_cdemo_sk)) * (v20 * (v21 * store_sales_ss_coupon_amt)))));
                    n21 = n21->nxt;
                  } while (n21 && (e21 = n21->obj) && h20 == n21->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se77, *e21)); 
                }
              }
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h21 == n20->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se78, *e20)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i22 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h22 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se82.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n22 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i22->slice(se82, h22));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e22;
         
          if (n22 && (e22 = n22->obj)) {
            do {                
              STRING_TYPE agg3storestore_s_state = e22->STORE_S_STATE;
              long v22 = e22->__av;
              AGG3STORE2ITEM1.addOrDelOnZero(se79.modify(store_sales_ss_item_sk,agg3storestore_s_state),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se80.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se81.modify(store_sales_ss_sold_date_sk)) * (v22 * store_sales_ss_coupon_amt))));
              n22 = n22->nxt;
            } while (n22 && (e22 = n22->obj) && h22 == n22->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se82, *e22)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i23 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h23 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se86.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n23 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i23->slice(se86, h23));
          AGG1STORE2STORE_SALES4_entry* e23;
         
          if (n23 && (e23 = n23->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e23->ITEM_I_ITEM_ID;
              long v23 = e23->__av;
              AGG3STORE7.addOrDelOnZero(se83.modify(store_sales_ss_store_sk,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se84.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se85.modify(store_sales_ss_cdemo_sk)) * (v23 * store_sales_ss_coupon_amt))));
              n23 = n23->nxt;
            } while (n23 && (e23 = n23->obj) && h23 == n23->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se86, *e23)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i24 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h25 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se91.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n24 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i24->slice(se91, h25));
          AGG1ITEM4STORE_SALES3_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              STRING_TYPE store_s_state = e24->STORE_S_STATE;
              long v24 = e24->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i25 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h24 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se90.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n25 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i25->slice(se90, h24));
                AGG1STORE2STORE_SALES4_entry* e25;
               
                if (n25 && (e25 = n25->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e25->ITEM_I_ITEM_ID;
                    long v25 = e25->__av;
                    AGG3STORE_SALES1.addOrDelOnZero(se87.modify(store_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se88.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se89.modify(store_sales_ss_sold_date_sk)) * (v24 * (v25 * store_sales_ss_coupon_amt)))));
                    n25 = n25->nxt;
                  } while (n25 && (e25 = n25->obj) && h24 == n25->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se90, *e25)); 
                }
              }
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h25 == n24->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se91, *e24)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i26 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h26 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se95.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n26 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i26->slice(se95, h26));
          AGG1ITEM4STORE_SALES3_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              STRING_TYPE store_s_state = e26->STORE_S_STATE;
              long v26 = e26->__av;
              AGG4ITEM4.addOrDelOnZero(se92.modify(store_sales_ss_item_sk,store_s_state),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se93.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se94.modify(store_sales_ss_cdemo_sk)) * (v26 * store_sales_ss_sales_price))));
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h26 == n26->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se95, *e26)); 
          }
        }AGG4ITEM4STORE2.addOrDelOnZero(se96.modify(store_sales_ss_item_sk,store_sales_ss_store_sk),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se97.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se98.modify(store_sales_ss_cdemo_sk)) * store_sales_ss_sales_price)));
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i27 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h28 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se103.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n27 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i27->slice(se103, h28));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              STRING_TYPE agg4storestore_s_state = e27->STORE_S_STATE;
              long v27 = e27->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i28 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h27 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se102.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n28 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i28->slice(se102, h27));
                AGG1STORE2STORE_SALES4_entry* e28;
               
                if (n28 && (e28 = n28->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e28->ITEM_I_ITEM_ID;
                    long v28 = e28->__av;
                    AGG4STORE2.addOrDelOnZero(se99.modify(agg4storestore_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se100.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se101.modify(store_sales_ss_cdemo_sk)) * (v27 * (v28 * store_sales_ss_sales_price)))));
                    n28 = n28->nxt;
                  } while (n28 && (e28 = n28->obj) && h27 == n28->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se102, *e28)); 
                }
              }
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h28 == n27->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se103, *e27)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0* i29 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0*>(AGG1ITEM1_L1_2STORE_SALES3.index[1]);
          const HASH_RES_t h29 = AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::hash(se107.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode* n29 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE_SALES3_map_0::IdxNode*>(i29->slice(se107, h29));
          AGG1ITEM1_L1_2STORE_SALES3_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              STRING_TYPE agg4storestore_s_state = e29->STORE_S_STATE;
              long v29 = e29->__av;
              AGG4STORE2ITEM1.addOrDelOnZero(se104.modify(store_sales_ss_item_sk,agg4storestore_s_state),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se105.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se106.modify(store_sales_ss_sold_date_sk)) * (v29 * store_sales_ss_sales_price))));
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h29 == n29->hash &&  AGG1ITEM1_L1_2STORE_SALES3_mapkey0_idxfn::equals(se107, *e29)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE2STORE_SALES4_map_0* i30 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
          const HASH_RES_t h30 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se111.modify0(store_sales_ss_item_sk));
          HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n30 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i30->slice(se111, h30));
          AGG1STORE2STORE_SALES4_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e30->ITEM_I_ITEM_ID;
              long v30 = e30->__av;
              AGG4STORE7.addOrDelOnZero(se108.modify(store_sales_ss_store_sk,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se109.modify(store_sales_ss_sold_date_sk)) * (AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se110.modify(store_sales_ss_cdemo_sk)) * (v30 * store_sales_ss_sales_price))));
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h30 == n30->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se111, *e30)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE_SALES3_map_0* i31 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0*>(AGG1ITEM4STORE_SALES3.index[1]);
          const HASH_RES_t h32 = AGG1ITEM4STORE_SALES3_mapkey0_idxfn::hash(se116.modify0(store_sales_ss_store_sk));
          HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode* n31 = static_cast<HashIndex_AGG1ITEM4STORE_SALES3_map_0::IdxNode*>(i31->slice(se116, h32));
          AGG1ITEM4STORE_SALES3_entry* e31;
         
          if (n31 && (e31 = n31->obj)) {
            do {                
              STRING_TYPE store_s_state = e31->STORE_S_STATE;
              long v31 = e31->__av;
              { //slice 
                const HashIndex_AGG1STORE2STORE_SALES4_map_0* i32 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0*>(AGG1STORE2STORE_SALES4.index[1]);
                const HASH_RES_t h31 = AGG1STORE2STORE_SALES4_mapkey0_idxfn::hash(se115.modify0(store_sales_ss_item_sk));
                HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode* n32 = static_cast<HashIndex_AGG1STORE2STORE_SALES4_map_0::IdxNode*>(i32->slice(se115, h31));
                AGG1STORE2STORE_SALES4_entry* e32;
               
                if (n32 && (e32 = n32->obj)) {
                  do {                
                    STRING_TYPE item_i_item_id = e32->ITEM_I_ITEM_ID;
                    long v32 = e32->__av;
                    AGG4STORE_SALES1.addOrDelOnZero(se112.modify(store_s_state,item_i_item_id),(AGG1ITEM1_L1_2STORE_SALES1.getValueOrDefault(se113.modify(store_sales_ss_cdemo_sk)) * (AGG1ITEM1_L1_2STORE_SALES2.getValueOrDefault(se114.modify(store_sales_ss_sold_date_sk)) * (v31 * (v32 * store_sales_ss_sales_price)))));
                    n32 = n32->nxt;
                  } while (n32 && (e32 = n32->obj) && h31 == n32->hash &&  AGG1STORE2STORE_SALES4_mapkey0_idxfn::equals(se115, *e32)); 
                }
              }
              n31 = n31->nxt;
            } while (n31 && (e31 = n31->obj) && h32 == n31->hash &&  AGG1ITEM4STORE_SALES3_mapkey0_idxfn::equals(se116, *e31)); 
          }
        }AGG1.clear();
        {  // foreach
          const HashIndex_AGG1STORE_SALES1_map_01* i33 = static_cast<HashIndex_AGG1STORE_SALES1_map_01*>(AGG1STORE_SALES1.index[0]);
          HashIndex_AGG1STORE_SALES1_map_01::IdxNode* n33; 
          AGG1STORE_SALES1_entry* e33;
        
          for (size_t i = 0; i < i33->size_; i++)
          {
            n33 = i33->buckets_ + i;
            while (n33 && (e33 = n33->obj))
            {
                STRING_TYPE store_s_state = e33->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e33->ITEM_I_ITEM_ID;
                long v33 = e33->__av;
                DOUBLE_TYPE agg1 = 0.0;
                long l1 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se118.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l1) ? agg1 += Udiv(Ulistmax(1L, l1)) : 0.0);
                AGG1.addOrDelOnZero(se117.modify(item_i_item_id,store_s_state),(v33 * agg1));
              n33 = n33->nxt;
            }
          }
        }AGG2.clear();
        {  // foreach
          const HashIndex_AGG2STORE_SALES1_map_01* i34 = static_cast<HashIndex_AGG2STORE_SALES1_map_01*>(AGG2STORE_SALES1.index[0]);
          HashIndex_AGG2STORE_SALES1_map_01::IdxNode* n34; 
          AGG2STORE_SALES1_entry* e34;
        
          for (size_t i = 0; i < i34->size_; i++)
          {
            n34 = i34->buckets_ + i;
            while (n34 && (e34 = n34->obj))
            {
                STRING_TYPE store_s_state = e34->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e34->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v34 = e34->__av;
                DOUBLE_TYPE agg2 = 0.0;
                long l2 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se120.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l2) ? agg2 += Udiv(Ulistmax(1L, l2)) : 0.0);
                AGG2.addOrDelOnZero(se119.modify(item_i_item_id,store_s_state),(v34 * agg2));
              n34 = n34->nxt;
            }
          }
        }AGG3.clear();
        {  // foreach
          const HashIndex_AGG3STORE_SALES1_map_01* i35 = static_cast<HashIndex_AGG3STORE_SALES1_map_01*>(AGG3STORE_SALES1.index[0]);
          HashIndex_AGG3STORE_SALES1_map_01::IdxNode* n35; 
          AGG3STORE_SALES1_entry* e35;
        
          for (size_t i = 0; i < i35->size_; i++)
          {
            n35 = i35->buckets_ + i;
            while (n35 && (e35 = n35->obj))
            {
                STRING_TYPE store_s_state = e35->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e35->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v35 = e35->__av;
                DOUBLE_TYPE agg3 = 0.0;
                long l3 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se122.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l3) ? agg3 += Udiv(Ulistmax(1L, l3)) : 0.0);
                AGG3.addOrDelOnZero(se121.modify(item_i_item_id,store_s_state),(v35 * agg3));
              n35 = n35->nxt;
            }
          }
        }AGG4.clear();
        {  // foreach
          const HashIndex_AGG4STORE_SALES1_map_01* i36 = static_cast<HashIndex_AGG4STORE_SALES1_map_01*>(AGG4STORE_SALES1.index[0]);
          HashIndex_AGG4STORE_SALES1_map_01::IdxNode* n36; 
          AGG4STORE_SALES1_entry* e36;
        
          for (size_t i = 0; i < i36->size_; i++)
          {
            n36 = i36->buckets_ + i;
            while (n36 && (e36 = n36->obj))
            {
                STRING_TYPE store_s_state = e36->STORE_S_STATE;
                STRING_TYPE item_i_item_id = e36->ITEM_I_ITEM_ID;
                DOUBLE_TYPE v36 = e36->__av;
                DOUBLE_TYPE agg4 = 0.0;
                long l4 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se124.modify(item_i_item_id,store_s_state));
                (/*if */(0L != l4) ? agg4 += Udiv(Ulistmax(1L, l4)) : 0.0);
                AGG4.addOrDelOnZero(se123.modify(item_i_item_id,store_s_state),(v36 * agg4));
              n36 = n36->nxt;
            }
          }
        }
      }
    }
    void on_insert_ITEM(const long item_i_item_sk, const STRING_TYPE& item_i_item_id, const date item_i_rec_start_date, const date item_i_rec_end_date, const STRING_TYPE& item_i_item_desc, const DOUBLE_TYPE item_i_current_price, const DOUBLE_TYPE item_i_wholesale_cost, const long item_i_brand_id, const STRING_TYPE& item_i_brand, const long item_i_class_id, const STRING_TYPE& item_i_class, const long item_i_category_id, const STRING_TYPE& item_i_category, const long item_i_manufact_id, const STRING_TYPE& item_i_manufact, const STRING_TYPE& item_i_size, const STRING_TYPE& item_i_formulation, const STRING_TYPE& item_i_color, const STRING_TYPE& item_i_units, const STRING_TYPE& item_i_container, const long item_i_manager_id, const STRING_TYPE& item_i_product_name) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        _c1.clear();
        { //slice 
          const HashIndex_AGG1STORE_SALES1_map_1* i37 = static_cast<HashIndex_AGG1STORE_SALES1_map_1*>(AGG1STORE_SALES1.index[1]);
          const HASH_RES_t h33 = AGG1STORE_SALES1_mapkey1_idxfn::hash(se129.modify1(item_i_item_id));
          HashIndex_AGG1STORE_SALES1_map_1::IdxNode* n37 = static_cast<HashIndex_AGG1STORE_SALES1_map_1::IdxNode*>(i37->slice(se129, h33));
          AGG1STORE_SALES1_entry* e37;
         
          if (n37 && (e37 = n37->obj)) {
            do {                
              STRING_TYPE store_s_state = e37->STORE_S_STATE;
              long v38 = e37->__av;
              DOUBLE_TYPE agg5 = 0.0;
              long l5 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se126.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se127.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l5) ? agg5 += Udiv(Ulistmax(1L, l5)) : 0.0);
              DOUBLE_TYPE agg6 = 0.0;
              long l6 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se128.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l6) ? agg6 += Udiv(Ulistmax(1L, l6)) : 0.0);
              _c1.addOrDelOnZero(st1.modify(store_s_state,(v38 * (agg5 + (agg6 * -1L)))), (v38 * (agg5 + (agg6 * -1L))));
              n37 = n37->nxt;
            } while (n37 && (e37 = n37->obj) && h33 == n37->hash &&  AGG1STORE_SALES1_mapkey1_idxfn::equals(se129, *e37)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4_map_0* i38 = static_cast<HashIndex_AGG1ITEM4_map_0*>(AGG1ITEM4.index[1]);
          const HASH_RES_t h34 = AGG1ITEM4_mapkey0_idxfn::hash(se132.modify0(item_i_item_sk));
          HashIndex_AGG1ITEM4_map_0::IdxNode* n38 = static_cast<HashIndex_AGG1ITEM4_map_0::IdxNode*>(i38->slice(se132, h34));
          AGG1ITEM4_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              STRING_TYPE store_s_state = e38->STORE_S_STATE;
              long v39 = e38->__av;
              DOUBLE_TYPE agg7 = 0.0;
              long l7 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se130.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se131.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l7) ? agg7 += Udiv(Ulistmax(1L, l7)) : 0.0);
              _c1.addOrDelOnZero(st2.modify(store_s_state,(v39 * agg7)), (v39 * agg7));
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h34 == n38->hash &&  AGG1ITEM4_mapkey0_idxfn::equals(se132, *e38)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i39 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c1.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n39; 
          tuple2_S_D* e39;
        
          for (size_t i = 0; i < i39->size_; i++)
          {
            n39 = i39->buckets_ + i;
            while (n39 && (e39 = n39->obj))
            {
              STRING_TYPE store_s_state = e39->_1;  
              DOUBLE_TYPE v40 = e39->__av; 
            AGG1.addOrDelOnZero(se125.modify(item_i_item_id,store_s_state),v40);      
              n39 = n39->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG1STORE2ITEM1_map_0* i40 = static_cast<HashIndex_AGG1STORE2ITEM1_map_0*>(AGG1STORE2ITEM1.index[1]);
          const HASH_RES_t h35 = AGG1STORE2ITEM1_mapkey0_idxfn::hash(se134.modify0(item_i_item_sk));
          HashIndex_AGG1STORE2ITEM1_map_0::IdxNode* n40 = static_cast<HashIndex_AGG1STORE2ITEM1_map_0::IdxNode*>(i40->slice(se134, h35));
          AGG1STORE2ITEM1_entry* e40;
         
          if (n40 && (e40 = n40->obj)) {
            do {                
              STRING_TYPE agg1storestore_s_state = e40->AGG1STORESTORE_S_STATE;
              long v41 = e40->__av;
              AGG1STORE2.addOrDelOnZero(se133.modify(agg1storestore_s_state,item_i_item_id),v41);
              n40 = n40->nxt;
            } while (n40 && (e40 = n40->obj) && h35 == n40->hash &&  AGG1STORE2ITEM1_mapkey0_idxfn::equals(se134, *e40)); 
          }
        }AGG1STORE2STORE_SALES4.addOrDelOnZero(se135.modify(item_i_item_sk,item_i_item_id),1L);
        { //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE1_map_0* i41 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_0*>(AGG1ITEM1_L1_2STORE1.index[1]);
          const HASH_RES_t h36 = AGG1ITEM1_L1_2STORE1_mapkey0_idxfn::hash(se137.modify0(item_i_item_sk));
          HashIndex_AGG1ITEM1_L1_2STORE1_map_0::IdxNode* n41 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_0::IdxNode*>(i41->slice(se137, h36));
          AGG1ITEM1_L1_2STORE1_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              long agg1storestore_s_store_sk = e41->AGG1ITEM1_L1_2STORESTORE_S_STORE_SK;
              long v42 = e41->__av;
              AGG1STORE2_L1_2.addOrDelOnZero(se136.modify(item_i_item_id,agg1storestore_s_store_sk),v42);
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h36 == n41->hash &&  AGG1ITEM1_L1_2STORE1_mapkey0_idxfn::equals(se137, *e41)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE2_map_0* i42 = static_cast<HashIndex_AGG1ITEM4STORE2_map_0*>(AGG1ITEM4STORE2.index[1]);
          const HASH_RES_t h37 = AGG1ITEM4STORE2_mapkey0_idxfn::hash(se139.modify0(item_i_item_sk));
          HashIndex_AGG1ITEM4STORE2_map_0::IdxNode* n42 = static_cast<HashIndex_AGG1ITEM4STORE2_map_0::IdxNode*>(i42->slice(se139, h37));
          AGG1ITEM4STORE2_entry* e42;
         
          if (n42 && (e42 = n42->obj)) {
            do {                
              long agg1storestore_s_store_sk = e42->AGG1ITEM4STORESTORE_S_STORE_SK;
              long v43 = e42->__av;
              AGG1STORE7.addOrDelOnZero(se138.modify(agg1storestore_s_store_sk,item_i_item_id),v43);
              n42 = n42->nxt;
            } while (n42 && (e42 = n42->obj) && h37 == n42->hash &&  AGG1ITEM4STORE2_mapkey0_idxfn::equals(se139, *e42)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4_map_0* i43 = static_cast<HashIndex_AGG1ITEM4_map_0*>(AGG1ITEM4.index[1]);
          const HASH_RES_t h38 = AGG1ITEM4_mapkey0_idxfn::hash(se141.modify0(item_i_item_sk));
          HashIndex_AGG1ITEM4_map_0::IdxNode* n43 = static_cast<HashIndex_AGG1ITEM4_map_0::IdxNode*>(i43->slice(se141, h38));
          AGG1ITEM4_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              STRING_TYPE store_s_state = e43->STORE_S_STATE;
              long v44 = e43->__av;
              AGG1STORE_SALES1.addOrDelOnZero(se140.modify(store_s_state,item_i_item_id),v44);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h38 == n43->hash &&  AGG1ITEM4_mapkey0_idxfn::equals(se141, *e43)); 
          }
        }_c2.clear();
        { //slice 
          const HashIndex_AGG2STORE_SALES1_map_1* i44 = static_cast<HashIndex_AGG2STORE_SALES1_map_1*>(AGG2STORE_SALES1.index[1]);
          const HASH_RES_t h39 = AGG2STORE_SALES1_mapkey1_idxfn::hash(se146.modify1(item_i_item_id));
          HashIndex_AGG2STORE_SALES1_map_1::IdxNode* n44 = static_cast<HashIndex_AGG2STORE_SALES1_map_1::IdxNode*>(i44->slice(se146, h39));
          AGG2STORE_SALES1_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              STRING_TYPE store_s_state = e44->STORE_S_STATE;
              DOUBLE_TYPE v46 = e44->__av;
              DOUBLE_TYPE agg8 = 0.0;
              long l8 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se143.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se144.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l8) ? agg8 += Udiv(Ulistmax(1L, l8)) : 0.0);
              DOUBLE_TYPE agg9 = 0.0;
              long l9 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se145.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l9) ? agg9 += Udiv(Ulistmax(1L, l9)) : 0.0);
              _c2.addOrDelOnZero(st3.modify(store_s_state,(v46 * (agg8 + (agg9 * -1L)))), (v46 * (agg8 + (agg9 * -1L))));
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h39 == n44->hash &&  AGG2STORE_SALES1_mapkey1_idxfn::equals(se146, *e44)); 
          }
        }{ //slice 
          const HashIndex_AGG2ITEM4_map_0* i45 = static_cast<HashIndex_AGG2ITEM4_map_0*>(AGG2ITEM4.index[1]);
          const HASH_RES_t h40 = AGG2ITEM4_mapkey0_idxfn::hash(se149.modify0(item_i_item_sk));
          HashIndex_AGG2ITEM4_map_0::IdxNode* n45 = static_cast<HashIndex_AGG2ITEM4_map_0::IdxNode*>(i45->slice(se149, h40));
          AGG2ITEM4_entry* e45;
         
          if (n45 && (e45 = n45->obj)) {
            do {                
              STRING_TYPE store_s_state = e45->STORE_S_STATE;
              DOUBLE_TYPE v47 = e45->__av;
              DOUBLE_TYPE agg10 = 0.0;
              long l10 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se147.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se148.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l10) ? agg10 += Udiv(Ulistmax(1L, l10)) : 0.0);
              _c2.addOrDelOnZero(st4.modify(store_s_state,(v47 * agg10)), (v47 * agg10));
              n45 = n45->nxt;
            } while (n45 && (e45 = n45->obj) && h40 == n45->hash &&  AGG2ITEM4_mapkey0_idxfn::equals(se149, *e45)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i46 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c2.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n46; 
          tuple2_S_D* e46;
        
          for (size_t i = 0; i < i46->size_; i++)
          {
            n46 = i46->buckets_ + i;
            while (n46 && (e46 = n46->obj))
            {
              STRING_TYPE store_s_state = e46->_1;  
              DOUBLE_TYPE v48 = e46->__av; 
            AGG2.addOrDelOnZero(se142.modify(item_i_item_id,store_s_state),v48);      
              n46 = n46->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG2STORE2ITEM1_map_0* i47 = static_cast<HashIndex_AGG2STORE2ITEM1_map_0*>(AGG2STORE2ITEM1.index[1]);
          const HASH_RES_t h41 = AGG2STORE2ITEM1_mapkey0_idxfn::hash(se151.modify0(item_i_item_sk));
          HashIndex_AGG2STORE2ITEM1_map_0::IdxNode* n47 = static_cast<HashIndex_AGG2STORE2ITEM1_map_0::IdxNode*>(i47->slice(se151, h41));
          AGG2STORE2ITEM1_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              STRING_TYPE agg2storestore_s_state = e47->AGG2STORESTORE_S_STATE;
              DOUBLE_TYPE v49 = e47->__av;
              AGG2STORE2.addOrDelOnZero(se150.modify(agg2storestore_s_state,item_i_item_id),v49);
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h41 == n47->hash &&  AGG2STORE2ITEM1_mapkey0_idxfn::equals(se151, *e47)); 
          }
        }{ //slice 
          const HashIndex_AGG2ITEM4STORE2_map_0* i48 = static_cast<HashIndex_AGG2ITEM4STORE2_map_0*>(AGG2ITEM4STORE2.index[1]);
          const HASH_RES_t h42 = AGG2ITEM4STORE2_mapkey0_idxfn::hash(se153.modify0(item_i_item_sk));
          HashIndex_AGG2ITEM4STORE2_map_0::IdxNode* n48 = static_cast<HashIndex_AGG2ITEM4STORE2_map_0::IdxNode*>(i48->slice(se153, h42));
          AGG2ITEM4STORE2_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              long agg2storestore_s_store_sk = e48->AGG2ITEM4STORESTORE_S_STORE_SK;
              DOUBLE_TYPE v50 = e48->__av;
              AGG2STORE7.addOrDelOnZero(se152.modify(agg2storestore_s_store_sk,item_i_item_id),v50);
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h42 == n48->hash &&  AGG2ITEM4STORE2_mapkey0_idxfn::equals(se153, *e48)); 
          }
        }{ //slice 
          const HashIndex_AGG2ITEM4_map_0* i49 = static_cast<HashIndex_AGG2ITEM4_map_0*>(AGG2ITEM4.index[1]);
          const HASH_RES_t h43 = AGG2ITEM4_mapkey0_idxfn::hash(se155.modify0(item_i_item_sk));
          HashIndex_AGG2ITEM4_map_0::IdxNode* n49 = static_cast<HashIndex_AGG2ITEM4_map_0::IdxNode*>(i49->slice(se155, h43));
          AGG2ITEM4_entry* e49;
         
          if (n49 && (e49 = n49->obj)) {
            do {                
              STRING_TYPE store_s_state = e49->STORE_S_STATE;
              DOUBLE_TYPE v51 = e49->__av;
              AGG2STORE_SALES1.addOrDelOnZero(se154.modify(store_s_state,item_i_item_id),v51);
              n49 = n49->nxt;
            } while (n49 && (e49 = n49->obj) && h43 == n49->hash &&  AGG2ITEM4_mapkey0_idxfn::equals(se155, *e49)); 
          }
        }_c3.clear();
        { //slice 
          const HashIndex_AGG3STORE_SALES1_map_1* i50 = static_cast<HashIndex_AGG3STORE_SALES1_map_1*>(AGG3STORE_SALES1.index[1]);
          const HASH_RES_t h44 = AGG3STORE_SALES1_mapkey1_idxfn::hash(se160.modify1(item_i_item_id));
          HashIndex_AGG3STORE_SALES1_map_1::IdxNode* n50 = static_cast<HashIndex_AGG3STORE_SALES1_map_1::IdxNode*>(i50->slice(se160, h44));
          AGG3STORE_SALES1_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              STRING_TYPE store_s_state = e50->STORE_S_STATE;
              DOUBLE_TYPE v53 = e50->__av;
              DOUBLE_TYPE agg11 = 0.0;
              long l11 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se157.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se158.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l11) ? agg11 += Udiv(Ulistmax(1L, l11)) : 0.0);
              DOUBLE_TYPE agg12 = 0.0;
              long l12 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se159.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l12) ? agg12 += Udiv(Ulistmax(1L, l12)) : 0.0);
              _c3.addOrDelOnZero(st5.modify(store_s_state,(v53 * (agg11 + (agg12 * -1L)))), (v53 * (agg11 + (agg12 * -1L))));
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h44 == n50->hash &&  AGG3STORE_SALES1_mapkey1_idxfn::equals(se160, *e50)); 
          }
        }{ //slice 
          const HashIndex_AGG3ITEM4_map_0* i51 = static_cast<HashIndex_AGG3ITEM4_map_0*>(AGG3ITEM4.index[1]);
          const HASH_RES_t h45 = AGG3ITEM4_mapkey0_idxfn::hash(se163.modify0(item_i_item_sk));
          HashIndex_AGG3ITEM4_map_0::IdxNode* n51 = static_cast<HashIndex_AGG3ITEM4_map_0::IdxNode*>(i51->slice(se163, h45));
          AGG3ITEM4_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              STRING_TYPE store_s_state = e51->STORE_S_STATE;
              DOUBLE_TYPE v54 = e51->__av;
              DOUBLE_TYPE agg13 = 0.0;
              long l13 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se161.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se162.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l13) ? agg13 += Udiv(Ulistmax(1L, l13)) : 0.0);
              _c3.addOrDelOnZero(st6.modify(store_s_state,(v54 * agg13)), (v54 * agg13));
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h45 == n51->hash &&  AGG3ITEM4_mapkey0_idxfn::equals(se163, *e51)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i52 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c3.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n52; 
          tuple2_S_D* e52;
        
          for (size_t i = 0; i < i52->size_; i++)
          {
            n52 = i52->buckets_ + i;
            while (n52 && (e52 = n52->obj))
            {
              STRING_TYPE store_s_state = e52->_1;  
              DOUBLE_TYPE v55 = e52->__av; 
            AGG3.addOrDelOnZero(se156.modify(item_i_item_id,store_s_state),v55);      
              n52 = n52->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG3STORE2ITEM1_map_0* i53 = static_cast<HashIndex_AGG3STORE2ITEM1_map_0*>(AGG3STORE2ITEM1.index[1]);
          const HASH_RES_t h46 = AGG3STORE2ITEM1_mapkey0_idxfn::hash(se165.modify0(item_i_item_sk));
          HashIndex_AGG3STORE2ITEM1_map_0::IdxNode* n53 = static_cast<HashIndex_AGG3STORE2ITEM1_map_0::IdxNode*>(i53->slice(se165, h46));
          AGG3STORE2ITEM1_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              STRING_TYPE agg3storestore_s_state = e53->AGG3STORESTORE_S_STATE;
              DOUBLE_TYPE v56 = e53->__av;
              AGG3STORE2.addOrDelOnZero(se164.modify(agg3storestore_s_state,item_i_item_id),v56);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h46 == n53->hash &&  AGG3STORE2ITEM1_mapkey0_idxfn::equals(se165, *e53)); 
          }
        }{ //slice 
          const HashIndex_AGG3ITEM4STORE2_map_0* i54 = static_cast<HashIndex_AGG3ITEM4STORE2_map_0*>(AGG3ITEM4STORE2.index[1]);
          const HASH_RES_t h47 = AGG3ITEM4STORE2_mapkey0_idxfn::hash(se167.modify0(item_i_item_sk));
          HashIndex_AGG3ITEM4STORE2_map_0::IdxNode* n54 = static_cast<HashIndex_AGG3ITEM4STORE2_map_0::IdxNode*>(i54->slice(se167, h47));
          AGG3ITEM4STORE2_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              long agg3storestore_s_store_sk = e54->AGG3ITEM4STORESTORE_S_STORE_SK;
              DOUBLE_TYPE v57 = e54->__av;
              AGG3STORE7.addOrDelOnZero(se166.modify(agg3storestore_s_store_sk,item_i_item_id),v57);
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h47 == n54->hash &&  AGG3ITEM4STORE2_mapkey0_idxfn::equals(se167, *e54)); 
          }
        }{ //slice 
          const HashIndex_AGG3ITEM4_map_0* i55 = static_cast<HashIndex_AGG3ITEM4_map_0*>(AGG3ITEM4.index[1]);
          const HASH_RES_t h48 = AGG3ITEM4_mapkey0_idxfn::hash(se169.modify0(item_i_item_sk));
          HashIndex_AGG3ITEM4_map_0::IdxNode* n55 = static_cast<HashIndex_AGG3ITEM4_map_0::IdxNode*>(i55->slice(se169, h48));
          AGG3ITEM4_entry* e55;
         
          if (n55 && (e55 = n55->obj)) {
            do {                
              STRING_TYPE store_s_state = e55->STORE_S_STATE;
              DOUBLE_TYPE v58 = e55->__av;
              AGG3STORE_SALES1.addOrDelOnZero(se168.modify(store_s_state,item_i_item_id),v58);
              n55 = n55->nxt;
            } while (n55 && (e55 = n55->obj) && h48 == n55->hash &&  AGG3ITEM4_mapkey0_idxfn::equals(se169, *e55)); 
          }
        }_c4.clear();
        { //slice 
          const HashIndex_AGG4STORE_SALES1_map_1* i56 = static_cast<HashIndex_AGG4STORE_SALES1_map_1*>(AGG4STORE_SALES1.index[1]);
          const HASH_RES_t h49 = AGG4STORE_SALES1_mapkey1_idxfn::hash(se174.modify1(item_i_item_id));
          HashIndex_AGG4STORE_SALES1_map_1::IdxNode* n56 = static_cast<HashIndex_AGG4STORE_SALES1_map_1::IdxNode*>(i56->slice(se174, h49));
          AGG4STORE_SALES1_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              STRING_TYPE store_s_state = e56->STORE_S_STATE;
              DOUBLE_TYPE v60 = e56->__av;
              DOUBLE_TYPE agg14 = 0.0;
              long l14 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se171.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se172.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l14) ? agg14 += Udiv(Ulistmax(1L, l14)) : 0.0);
              DOUBLE_TYPE agg15 = 0.0;
              long l15 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se173.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l15) ? agg15 += Udiv(Ulistmax(1L, l15)) : 0.0);
              _c4.addOrDelOnZero(st7.modify(store_s_state,(v60 * (agg14 + (agg15 * -1L)))), (v60 * (agg14 + (agg15 * -1L))));
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h49 == n56->hash &&  AGG4STORE_SALES1_mapkey1_idxfn::equals(se174, *e56)); 
          }
        }{ //slice 
          const HashIndex_AGG4ITEM4_map_0* i57 = static_cast<HashIndex_AGG4ITEM4_map_0*>(AGG4ITEM4.index[1]);
          const HASH_RES_t h50 = AGG4ITEM4_mapkey0_idxfn::hash(se177.modify0(item_i_item_sk));
          HashIndex_AGG4ITEM4_map_0::IdxNode* n57 = static_cast<HashIndex_AGG4ITEM4_map_0::IdxNode*>(i57->slice(se177, h50));
          AGG4ITEM4_entry* e57;
         
          if (n57 && (e57 = n57->obj)) {
            do {                
              STRING_TYPE store_s_state = e57->STORE_S_STATE;
              DOUBLE_TYPE v61 = e57->__av;
              DOUBLE_TYPE agg16 = 0.0;
              long l16 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se175.modify(item_i_item_id,store_s_state)) + AGG1ITEM1_L1_2.getValueOrDefault(se176.modify(store_s_state,item_i_item_sk)));
              (/*if */(0L != l16) ? agg16 += Udiv(Ulistmax(1L, l16)) : 0.0);
              _c4.addOrDelOnZero(st8.modify(store_s_state,(v61 * agg16)), (v61 * agg16));
              n57 = n57->nxt;
            } while (n57 && (e57 = n57->obj) && h50 == n57->hash &&  AGG4ITEM4_mapkey0_idxfn::equals(se177, *e57)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i58 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c4.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n58; 
          tuple2_S_D* e58;
        
          for (size_t i = 0; i < i58->size_; i++)
          {
            n58 = i58->buckets_ + i;
            while (n58 && (e58 = n58->obj))
            {
              STRING_TYPE store_s_state = e58->_1;  
              DOUBLE_TYPE v62 = e58->__av; 
            AGG4.addOrDelOnZero(se170.modify(item_i_item_id,store_s_state),v62);      
              n58 = n58->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2_map_1* i59 = static_cast<HashIndex_AGG1ITEM1_L1_2_map_1*>(AGG1ITEM1_L1_2.index[1]);
          const HASH_RES_t h51 = AGG1ITEM1_L1_2_mapkey1_idxfn::hash(se179.modify1(item_i_item_sk));
          HashIndex_AGG1ITEM1_L1_2_map_1::IdxNode* n59 = static_cast<HashIndex_AGG1ITEM1_L1_2_map_1::IdxNode*>(i59->slice(se179, h51));
          AGG1ITEM1_L1_2_entry* e59;
         
          if (n59 && (e59 = n59->obj)) {
            do {                
              STRING_TYPE store_s_state = e59->STORE_S_STATE;
              long v63 = e59->__av;
              AGG1STORE_SALES1_L1_1.addOrDelOnZero(se178.modify(item_i_item_id,store_s_state),v63);
              n59 = n59->nxt;
            } while (n59 && (e59 = n59->obj) && h51 == n59->hash &&  AGG1ITEM1_L1_2_mapkey1_idxfn::equals(se179, *e59)); 
          }
        }{ //slice 
          const HashIndex_AGG4STORE2ITEM1_map_0* i60 = static_cast<HashIndex_AGG4STORE2ITEM1_map_0*>(AGG4STORE2ITEM1.index[1]);
          const HASH_RES_t h52 = AGG4STORE2ITEM1_mapkey0_idxfn::hash(se181.modify0(item_i_item_sk));
          HashIndex_AGG4STORE2ITEM1_map_0::IdxNode* n60 = static_cast<HashIndex_AGG4STORE2ITEM1_map_0::IdxNode*>(i60->slice(se181, h52));
          AGG4STORE2ITEM1_entry* e60;
         
          if (n60 && (e60 = n60->obj)) {
            do {                
              STRING_TYPE agg4storestore_s_state = e60->AGG4STORESTORE_S_STATE;
              DOUBLE_TYPE v64 = e60->__av;
              AGG4STORE2.addOrDelOnZero(se180.modify(agg4storestore_s_state,item_i_item_id),v64);
              n60 = n60->nxt;
            } while (n60 && (e60 = n60->obj) && h52 == n60->hash &&  AGG4STORE2ITEM1_mapkey0_idxfn::equals(se181, *e60)); 
          }
        }{ //slice 
          const HashIndex_AGG4ITEM4STORE2_map_0* i61 = static_cast<HashIndex_AGG4ITEM4STORE2_map_0*>(AGG4ITEM4STORE2.index[1]);
          const HASH_RES_t h53 = AGG4ITEM4STORE2_mapkey0_idxfn::hash(se183.modify0(item_i_item_sk));
          HashIndex_AGG4ITEM4STORE2_map_0::IdxNode* n61 = static_cast<HashIndex_AGG4ITEM4STORE2_map_0::IdxNode*>(i61->slice(se183, h53));
          AGG4ITEM4STORE2_entry* e61;
         
          if (n61 && (e61 = n61->obj)) {
            do {                
              long agg4storestore_s_store_sk = e61->AGG4ITEM4STORESTORE_S_STORE_SK;
              DOUBLE_TYPE v65 = e61->__av;
              AGG4STORE7.addOrDelOnZero(se182.modify(agg4storestore_s_store_sk,item_i_item_id),v65);
              n61 = n61->nxt;
            } while (n61 && (e61 = n61->obj) && h53 == n61->hash &&  AGG4ITEM4STORE2_mapkey0_idxfn::equals(se183, *e61)); 
          }
        }{ //slice 
          const HashIndex_AGG4ITEM4_map_0* i62 = static_cast<HashIndex_AGG4ITEM4_map_0*>(AGG4ITEM4.index[1]);
          const HASH_RES_t h54 = AGG4ITEM4_mapkey0_idxfn::hash(se185.modify0(item_i_item_sk));
          HashIndex_AGG4ITEM4_map_0::IdxNode* n62 = static_cast<HashIndex_AGG4ITEM4_map_0::IdxNode*>(i62->slice(se185, h54));
          AGG4ITEM4_entry* e62;
         
          if (n62 && (e62 = n62->obj)) {
            do {                
              STRING_TYPE store_s_state = e62->STORE_S_STATE;
              DOUBLE_TYPE v66 = e62->__av;
              AGG4STORE_SALES1.addOrDelOnZero(se184.modify(store_s_state,item_i_item_id),v66);
              n62 = n62->nxt;
            } while (n62 && (e62 = n62->obj) && h54 == n62->hash &&  AGG4ITEM4_mapkey0_idxfn::equals(se185, *e62)); 
          }
        }
      }
    }
    void on_insert_STORE(const long store_s_store_sk, const STRING_TYPE& store_s_store_id, const date store_s_rec_start_date, const date store_s_rec_end_date, const long store_s_closed_date_sk, const STRING_TYPE& store_s_store_name, const long store_s_number_employees, const long store_s_floor_space, const STRING_TYPE& store_s_hours, const STRING_TYPE& store_s_manager, const long store_s_market_id, const STRING_TYPE& store_s_geography_class, const STRING_TYPE& store_s_market_desc, const STRING_TYPE& store_s_market_manager, const long store_s_division_id, const STRING_TYPE& store_s_division_name, const long store_s_company_id, const STRING_TYPE& store_s_company_name, const STRING_TYPE& store_s_street_number, const STRING_TYPE& store_s_street_name, const STRING_TYPE& store_s_street_type, const STRING_TYPE& store_s_suite_number, const STRING_TYPE& store_s_city, const STRING_TYPE& store_s_county, const STRING_TYPE& store_s_state, const STRING_TYPE& store_s_zip, const STRING_TYPE& store_s_country, const DOUBLE_TYPE store_s_gmt_offset, const DOUBLE_TYPE store_s_tax_precentage) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        _c5.clear();
        { //slice 
          const HashIndex_AGG1STORE2_map_0* i63 = static_cast<HashIndex_AGG1STORE2_map_0*>(AGG1STORE2.index[1]);
          const HASH_RES_t h55 = AGG1STORE2_mapkey0_idxfn::hash(se190.modify0(store_s_state));
          HashIndex_AGG1STORE2_map_0::IdxNode* n63 = static_cast<HashIndex_AGG1STORE2_map_0::IdxNode*>(i63->slice(se190, h55));
          AGG1STORE2_entry* e63;
         
          if (n63 && (e63 = n63->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e63->ITEM_I_ITEM_ID;
              long v68 = e63->__av;
              DOUBLE_TYPE agg17 = 0.0;
              long l17 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se187.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se188.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l17) ? agg17 += Udiv(Ulistmax(1L, l17)) : 0.0);
              DOUBLE_TYPE agg18 = 0.0;
              long l18 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se189.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l18) ? agg18 += Udiv(Ulistmax(1L, l18)) : 0.0);
              _c5.addOrDelOnZero(st9.modify(item_i_item_id,(v68 * (agg17 + (agg18 * -1L)))), (v68 * (agg17 + (agg18 * -1L))));
              n63 = n63->nxt;
            } while (n63 && (e63 = n63->obj) && h55 == n63->hash &&  AGG1STORE2_mapkey0_idxfn::equals(se190, *e63)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE7_map_0* i64 = static_cast<HashIndex_AGG1STORE7_map_0*>(AGG1STORE7.index[1]);
          const HASH_RES_t h56 = AGG1STORE7_mapkey0_idxfn::hash(se193.modify0(store_s_store_sk));
          HashIndex_AGG1STORE7_map_0::IdxNode* n64 = static_cast<HashIndex_AGG1STORE7_map_0::IdxNode*>(i64->slice(se193, h56));
          AGG1STORE7_entry* e64;
         
          if (n64 && (e64 = n64->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e64->ITEM_I_ITEM_ID;
              long v69 = e64->__av;
              DOUBLE_TYPE agg19 = 0.0;
              long l19 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se191.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se192.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l19) ? agg19 += Udiv(Ulistmax(1L, l19)) : 0.0);
              _c5.addOrDelOnZero(st10.modify(item_i_item_id,(v69 * agg19)), (v69 * agg19));
              n64 = n64->nxt;
            } while (n64 && (e64 = n64->obj) && h56 == n64->hash &&  AGG1STORE7_mapkey0_idxfn::equals(se193, *e64)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i65 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c5.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n65; 
          tuple2_S_D* e65;
        
          for (size_t i = 0; i < i65->size_; i++)
          {
            n65 = i65->buckets_ + i;
            while (n65 && (e65 = n65->obj))
            {
              STRING_TYPE item_i_item_id = e65->_1;  
              DOUBLE_TYPE v70 = e65->__av; 
            (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1.addOrDelOnZero(se186.modify(item_i_item_id,store_s_state),v70) : (void)0);      
              n65 = n65->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG1ITEM1_L1_2STORE1_map_1* i66 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_1*>(AGG1ITEM1_L1_2STORE1.index[2]);
          const HASH_RES_t h57 = AGG1ITEM1_L1_2STORE1_mapkey1_idxfn::hash(se195.modify1(store_s_store_sk));
          HashIndex_AGG1ITEM1_L1_2STORE1_map_1::IdxNode* n66 = static_cast<HashIndex_AGG1ITEM1_L1_2STORE1_map_1::IdxNode*>(i66->slice(se195, h57));
          AGG1ITEM1_L1_2STORE1_entry* e66;
         
          if (n66 && (e66 = n66->obj)) {
            do {                
              long agg1itemitem_i_item_sk = e66->AGG1ITEMITEM_I_ITEM_SK;
              long v71 = e66->__av;
              AGG1ITEM1_L1_2.addOrDelOnZero(se194.modify(store_s_state,agg1itemitem_i_item_sk),v71);
              n66 = n66->nxt;
            } while (n66 && (e66 = n66->obj) && h57 == n66->hash &&  AGG1ITEM1_L1_2STORE1_mapkey1_idxfn::equals(se195, *e66)); 
          }
        }AGG1ITEM1_L1_2STORE_SALES3.addOrDelOnZero(se196.modify(store_s_store_sk,store_s_state),1L);
        { //slice 
          const HashIndex_AGG1ITEM4STORE2_map_1* i67 = static_cast<HashIndex_AGG1ITEM4STORE2_map_1*>(AGG1ITEM4STORE2.index[2]);
          const HASH_RES_t h58 = AGG1ITEM4STORE2_mapkey1_idxfn::hash(se198.modify1(store_s_store_sk));
          HashIndex_AGG1ITEM4STORE2_map_1::IdxNode* n67 = static_cast<HashIndex_AGG1ITEM4STORE2_map_1::IdxNode*>(i67->slice(se198, h58));
          AGG1ITEM4STORE2_entry* e67;
         
          if (n67 && (e67 = n67->obj)) {
            do {                
              long agg1itemitem_i_item_sk = e67->AGG1ITEMITEM_I_ITEM_SK;
              long v72 = e67->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1ITEM4.addOrDelOnZero(se197.modify(agg1itemitem_i_item_sk,store_s_state),v72) : (void)0);
              n67 = n67->nxt;
            } while (n67 && (e67 = n67->obj) && h58 == n67->hash &&  AGG1ITEM4STORE2_mapkey1_idxfn::equals(se198, *e67)); 
          }
        }(/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1ITEM4STORE_SALES3.addOrDelOnZero(se199.modify(store_s_store_sk,store_s_state),1L) : (void)0);
        { //slice 
          const HashIndex_AGG1STORE7_map_0* i68 = static_cast<HashIndex_AGG1STORE7_map_0*>(AGG1STORE7.index[1]);
          const HASH_RES_t h59 = AGG1STORE7_mapkey0_idxfn::hash(se201.modify0(store_s_store_sk));
          HashIndex_AGG1STORE7_map_0::IdxNode* n68 = static_cast<HashIndex_AGG1STORE7_map_0::IdxNode*>(i68->slice(se201, h59));
          AGG1STORE7_entry* e68;
         
          if (n68 && (e68 = n68->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e68->ITEM_I_ITEM_ID;
              long v73 = e68->__av;
              AGG1STORE2.addOrDelOnZero(se200.modify(store_s_state,item_i_item_id),v73);
              n68 = n68->nxt;
            } while (n68 && (e68 = n68->obj) && h59 == n68->hash &&  AGG1STORE7_mapkey0_idxfn::equals(se201, *e68)); 
          }
        }{ //slice 
          const HashIndex_AGG1ITEM4STORE2_map_1* i69 = static_cast<HashIndex_AGG1ITEM4STORE2_map_1*>(AGG1ITEM4STORE2.index[2]);
          const HASH_RES_t h60 = AGG1ITEM4STORE2_mapkey1_idxfn::hash(se203.modify1(store_s_store_sk));
          HashIndex_AGG1ITEM4STORE2_map_1::IdxNode* n69 = static_cast<HashIndex_AGG1ITEM4STORE2_map_1::IdxNode*>(i69->slice(se203, h60));
          AGG1ITEM4STORE2_entry* e69;
         
          if (n69 && (e69 = n69->obj)) {
            do {                
              long agg1store2itemitem_i_item_sk = e69->AGG1ITEMITEM_I_ITEM_SK;
              long v74 = e69->__av;
              AGG1STORE2ITEM1.addOrDelOnZero(se202.modify(agg1store2itemitem_i_item_sk,store_s_state),v74);
              n69 = n69->nxt;
            } while (n69 && (e69 = n69->obj) && h60 == n69->hash &&  AGG1ITEM4STORE2_mapkey1_idxfn::equals(se203, *e69)); 
          }
        }{ //slice 
          const HashIndex_AGG1STORE7_map_0* i70 = static_cast<HashIndex_AGG1STORE7_map_0*>(AGG1STORE7.index[1]);
          const HASH_RES_t h61 = AGG1STORE7_mapkey0_idxfn::hash(se205.modify0(store_s_store_sk));
          HashIndex_AGG1STORE7_map_0::IdxNode* n70 = static_cast<HashIndex_AGG1STORE7_map_0::IdxNode*>(i70->slice(se205, h61));
          AGG1STORE7_entry* e70;
         
          if (n70 && (e70 = n70->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e70->ITEM_I_ITEM_ID;
              long v75 = e70->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG1STORE_SALES1.addOrDelOnZero(se204.modify(store_s_state,item_i_item_id),v75) : (void)0);
              n70 = n70->nxt;
            } while (n70 && (e70 = n70->obj) && h61 == n70->hash &&  AGG1STORE7_mapkey0_idxfn::equals(se205, *e70)); 
          }
        }_c6.clear();
        { //slice 
          const HashIndex_AGG2STORE2_map_0* i71 = static_cast<HashIndex_AGG2STORE2_map_0*>(AGG2STORE2.index[1]);
          const HASH_RES_t h62 = AGG2STORE2_mapkey0_idxfn::hash(se210.modify0(store_s_state));
          HashIndex_AGG2STORE2_map_0::IdxNode* n71 = static_cast<HashIndex_AGG2STORE2_map_0::IdxNode*>(i71->slice(se210, h62));
          AGG2STORE2_entry* e71;
         
          if (n71 && (e71 = n71->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e71->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v77 = e71->__av;
              DOUBLE_TYPE agg20 = 0.0;
              long l20 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se207.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se208.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l20) ? agg20 += Udiv(Ulistmax(1L, l20)) : 0.0);
              DOUBLE_TYPE agg21 = 0.0;
              long l21 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se209.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l21) ? agg21 += Udiv(Ulistmax(1L, l21)) : 0.0);
              _c6.addOrDelOnZero(st11.modify(item_i_item_id,(v77 * (agg20 + (agg21 * -1L)))), (v77 * (agg20 + (agg21 * -1L))));
              n71 = n71->nxt;
            } while (n71 && (e71 = n71->obj) && h62 == n71->hash &&  AGG2STORE2_mapkey0_idxfn::equals(se210, *e71)); 
          }
        }{ //slice 
          const HashIndex_AGG2STORE7_map_0* i72 = static_cast<HashIndex_AGG2STORE7_map_0*>(AGG2STORE7.index[1]);
          const HASH_RES_t h63 = AGG2STORE7_mapkey0_idxfn::hash(se213.modify0(store_s_store_sk));
          HashIndex_AGG2STORE7_map_0::IdxNode* n72 = static_cast<HashIndex_AGG2STORE7_map_0::IdxNode*>(i72->slice(se213, h63));
          AGG2STORE7_entry* e72;
         
          if (n72 && (e72 = n72->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e72->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v78 = e72->__av;
              DOUBLE_TYPE agg22 = 0.0;
              long l22 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se211.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se212.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l22) ? agg22 += Udiv(Ulistmax(1L, l22)) : 0.0);
              _c6.addOrDelOnZero(st12.modify(item_i_item_id,(v78 * agg22)), (v78 * agg22));
              n72 = n72->nxt;
            } while (n72 && (e72 = n72->obj) && h63 == n72->hash &&  AGG2STORE7_mapkey0_idxfn::equals(se213, *e72)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i73 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c6.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n73; 
          tuple2_S_D* e73;
        
          for (size_t i = 0; i < i73->size_; i++)
          {
            n73 = i73->buckets_ + i;
            while (n73 && (e73 = n73->obj))
            {
              STRING_TYPE item_i_item_id = e73->_1;  
              DOUBLE_TYPE v79 = e73->__av; 
            (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG2.addOrDelOnZero(se206.modify(item_i_item_id,store_s_state),v79) : (void)0);      
              n73 = n73->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG2ITEM4STORE2_map_1* i74 = static_cast<HashIndex_AGG2ITEM4STORE2_map_1*>(AGG2ITEM4STORE2.index[2]);
          const HASH_RES_t h64 = AGG2ITEM4STORE2_mapkey1_idxfn::hash(se215.modify1(store_s_store_sk));
          HashIndex_AGG2ITEM4STORE2_map_1::IdxNode* n74 = static_cast<HashIndex_AGG2ITEM4STORE2_map_1::IdxNode*>(i74->slice(se215, h64));
          AGG2ITEM4STORE2_entry* e74;
         
          if (n74 && (e74 = n74->obj)) {
            do {                
              long agg2itemitem_i_item_sk = e74->AGG2ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v80 = e74->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG2ITEM4.addOrDelOnZero(se214.modify(agg2itemitem_i_item_sk,store_s_state),v80) : (void)0);
              n74 = n74->nxt;
            } while (n74 && (e74 = n74->obj) && h64 == n74->hash &&  AGG2ITEM4STORE2_mapkey1_idxfn::equals(se215, *e74)); 
          }
        }{ //slice 
          const HashIndex_AGG2STORE7_map_0* i75 = static_cast<HashIndex_AGG2STORE7_map_0*>(AGG2STORE7.index[1]);
          const HASH_RES_t h65 = AGG2STORE7_mapkey0_idxfn::hash(se217.modify0(store_s_store_sk));
          HashIndex_AGG2STORE7_map_0::IdxNode* n75 = static_cast<HashIndex_AGG2STORE7_map_0::IdxNode*>(i75->slice(se217, h65));
          AGG2STORE7_entry* e75;
         
          if (n75 && (e75 = n75->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e75->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v81 = e75->__av;
              AGG2STORE2.addOrDelOnZero(se216.modify(store_s_state,item_i_item_id),v81);
              n75 = n75->nxt;
            } while (n75 && (e75 = n75->obj) && h65 == n75->hash &&  AGG2STORE7_mapkey0_idxfn::equals(se217, *e75)); 
          }
        }{ //slice 
          const HashIndex_AGG2ITEM4STORE2_map_1* i76 = static_cast<HashIndex_AGG2ITEM4STORE2_map_1*>(AGG2ITEM4STORE2.index[2]);
          const HASH_RES_t h66 = AGG2ITEM4STORE2_mapkey1_idxfn::hash(se219.modify1(store_s_store_sk));
          HashIndex_AGG2ITEM4STORE2_map_1::IdxNode* n76 = static_cast<HashIndex_AGG2ITEM4STORE2_map_1::IdxNode*>(i76->slice(se219, h66));
          AGG2ITEM4STORE2_entry* e76;
         
          if (n76 && (e76 = n76->obj)) {
            do {                
              long agg2store2itemitem_i_item_sk = e76->AGG2ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v82 = e76->__av;
              AGG2STORE2ITEM1.addOrDelOnZero(se218.modify(agg2store2itemitem_i_item_sk,store_s_state),v82);
              n76 = n76->nxt;
            } while (n76 && (e76 = n76->obj) && h66 == n76->hash &&  AGG2ITEM4STORE2_mapkey1_idxfn::equals(se219, *e76)); 
          }
        }{ //slice 
          const HashIndex_AGG2STORE7_map_0* i77 = static_cast<HashIndex_AGG2STORE7_map_0*>(AGG2STORE7.index[1]);
          const HASH_RES_t h67 = AGG2STORE7_mapkey0_idxfn::hash(se221.modify0(store_s_store_sk));
          HashIndex_AGG2STORE7_map_0::IdxNode* n77 = static_cast<HashIndex_AGG2STORE7_map_0::IdxNode*>(i77->slice(se221, h67));
          AGG2STORE7_entry* e77;
         
          if (n77 && (e77 = n77->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e77->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v83 = e77->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG2STORE_SALES1.addOrDelOnZero(se220.modify(store_s_state,item_i_item_id),v83) : (void)0);
              n77 = n77->nxt;
            } while (n77 && (e77 = n77->obj) && h67 == n77->hash &&  AGG2STORE7_mapkey0_idxfn::equals(se221, *e77)); 
          }
        }_c7.clear();
        { //slice 
          const HashIndex_AGG3STORE2_map_0* i78 = static_cast<HashIndex_AGG3STORE2_map_0*>(AGG3STORE2.index[1]);
          const HASH_RES_t h68 = AGG3STORE2_mapkey0_idxfn::hash(se226.modify0(store_s_state));
          HashIndex_AGG3STORE2_map_0::IdxNode* n78 = static_cast<HashIndex_AGG3STORE2_map_0::IdxNode*>(i78->slice(se226, h68));
          AGG3STORE2_entry* e78;
         
          if (n78 && (e78 = n78->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e78->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v85 = e78->__av;
              DOUBLE_TYPE agg23 = 0.0;
              long l23 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se223.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se224.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l23) ? agg23 += Udiv(Ulistmax(1L, l23)) : 0.0);
              DOUBLE_TYPE agg24 = 0.0;
              long l24 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se225.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l24) ? agg24 += Udiv(Ulistmax(1L, l24)) : 0.0);
              _c7.addOrDelOnZero(st13.modify(item_i_item_id,(v85 * (agg23 + (agg24 * -1L)))), (v85 * (agg23 + (agg24 * -1L))));
              n78 = n78->nxt;
            } while (n78 && (e78 = n78->obj) && h68 == n78->hash &&  AGG3STORE2_mapkey0_idxfn::equals(se226, *e78)); 
          }
        }{ //slice 
          const HashIndex_AGG3STORE7_map_0* i79 = static_cast<HashIndex_AGG3STORE7_map_0*>(AGG3STORE7.index[1]);
          const HASH_RES_t h69 = AGG3STORE7_mapkey0_idxfn::hash(se229.modify0(store_s_store_sk));
          HashIndex_AGG3STORE7_map_0::IdxNode* n79 = static_cast<HashIndex_AGG3STORE7_map_0::IdxNode*>(i79->slice(se229, h69));
          AGG3STORE7_entry* e79;
         
          if (n79 && (e79 = n79->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e79->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v86 = e79->__av;
              DOUBLE_TYPE agg25 = 0.0;
              long l25 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se227.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se228.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l25) ? agg25 += Udiv(Ulistmax(1L, l25)) : 0.0);
              _c7.addOrDelOnZero(st14.modify(item_i_item_id,(v86 * agg25)), (v86 * agg25));
              n79 = n79->nxt;
            } while (n79 && (e79 = n79->obj) && h69 == n79->hash &&  AGG3STORE7_mapkey0_idxfn::equals(se229, *e79)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i80 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c7.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n80; 
          tuple2_S_D* e80;
        
          for (size_t i = 0; i < i80->size_; i++)
          {
            n80 = i80->buckets_ + i;
            while (n80 && (e80 = n80->obj))
            {
              STRING_TYPE item_i_item_id = e80->_1;  
              DOUBLE_TYPE v87 = e80->__av; 
            (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG3.addOrDelOnZero(se222.modify(item_i_item_id,store_s_state),v87) : (void)0);      
              n80 = n80->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG3ITEM4STORE2_map_1* i81 = static_cast<HashIndex_AGG3ITEM4STORE2_map_1*>(AGG3ITEM4STORE2.index[2]);
          const HASH_RES_t h70 = AGG3ITEM4STORE2_mapkey1_idxfn::hash(se231.modify1(store_s_store_sk));
          HashIndex_AGG3ITEM4STORE2_map_1::IdxNode* n81 = static_cast<HashIndex_AGG3ITEM4STORE2_map_1::IdxNode*>(i81->slice(se231, h70));
          AGG3ITEM4STORE2_entry* e81;
         
          if (n81 && (e81 = n81->obj)) {
            do {                
              long agg3itemitem_i_item_sk = e81->AGG3ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v88 = e81->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG3ITEM4.addOrDelOnZero(se230.modify(agg3itemitem_i_item_sk,store_s_state),v88) : (void)0);
              n81 = n81->nxt;
            } while (n81 && (e81 = n81->obj) && h70 == n81->hash &&  AGG3ITEM4STORE2_mapkey1_idxfn::equals(se231, *e81)); 
          }
        }{ //slice 
          const HashIndex_AGG3STORE7_map_0* i82 = static_cast<HashIndex_AGG3STORE7_map_0*>(AGG3STORE7.index[1]);
          const HASH_RES_t h71 = AGG3STORE7_mapkey0_idxfn::hash(se233.modify0(store_s_store_sk));
          HashIndex_AGG3STORE7_map_0::IdxNode* n82 = static_cast<HashIndex_AGG3STORE7_map_0::IdxNode*>(i82->slice(se233, h71));
          AGG3STORE7_entry* e82;
         
          if (n82 && (e82 = n82->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e82->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v89 = e82->__av;
              AGG3STORE2.addOrDelOnZero(se232.modify(store_s_state,item_i_item_id),v89);
              n82 = n82->nxt;
            } while (n82 && (e82 = n82->obj) && h71 == n82->hash &&  AGG3STORE7_mapkey0_idxfn::equals(se233, *e82)); 
          }
        }{ //slice 
          const HashIndex_AGG3ITEM4STORE2_map_1* i83 = static_cast<HashIndex_AGG3ITEM4STORE2_map_1*>(AGG3ITEM4STORE2.index[2]);
          const HASH_RES_t h72 = AGG3ITEM4STORE2_mapkey1_idxfn::hash(se235.modify1(store_s_store_sk));
          HashIndex_AGG3ITEM4STORE2_map_1::IdxNode* n83 = static_cast<HashIndex_AGG3ITEM4STORE2_map_1::IdxNode*>(i83->slice(se235, h72));
          AGG3ITEM4STORE2_entry* e83;
         
          if (n83 && (e83 = n83->obj)) {
            do {                
              long agg3store2itemitem_i_item_sk = e83->AGG3ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v90 = e83->__av;
              AGG3STORE2ITEM1.addOrDelOnZero(se234.modify(agg3store2itemitem_i_item_sk,store_s_state),v90);
              n83 = n83->nxt;
            } while (n83 && (e83 = n83->obj) && h72 == n83->hash &&  AGG3ITEM4STORE2_mapkey1_idxfn::equals(se235, *e83)); 
          }
        }{ //slice 
          const HashIndex_AGG3STORE7_map_0* i84 = static_cast<HashIndex_AGG3STORE7_map_0*>(AGG3STORE7.index[1]);
          const HASH_RES_t h73 = AGG3STORE7_mapkey0_idxfn::hash(se237.modify0(store_s_store_sk));
          HashIndex_AGG3STORE7_map_0::IdxNode* n84 = static_cast<HashIndex_AGG3STORE7_map_0::IdxNode*>(i84->slice(se237, h73));
          AGG3STORE7_entry* e84;
         
          if (n84 && (e84 = n84->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e84->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v91 = e84->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG3STORE_SALES1.addOrDelOnZero(se236.modify(store_s_state,item_i_item_id),v91) : (void)0);
              n84 = n84->nxt;
            } while (n84 && (e84 = n84->obj) && h73 == n84->hash &&  AGG3STORE7_mapkey0_idxfn::equals(se237, *e84)); 
          }
        }_c8.clear();
        { //slice 
          const HashIndex_AGG4STORE2_map_0* i85 = static_cast<HashIndex_AGG4STORE2_map_0*>(AGG4STORE2.index[1]);
          const HASH_RES_t h74 = AGG4STORE2_mapkey0_idxfn::hash(se242.modify0(store_s_state));
          HashIndex_AGG4STORE2_map_0::IdxNode* n85 = static_cast<HashIndex_AGG4STORE2_map_0::IdxNode*>(i85->slice(se242, h74));
          AGG4STORE2_entry* e85;
         
          if (n85 && (e85 = n85->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e85->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v93 = e85->__av;
              DOUBLE_TYPE agg26 = 0.0;
              long l26 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se239.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se240.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l26) ? agg26 += Udiv(Ulistmax(1L, l26)) : 0.0);
              DOUBLE_TYPE agg27 = 0.0;
              long l27 = AGG1STORE_SALES1_L1_1.getValueOrDefault(se241.modify(item_i_item_id,store_s_state));
              (/*if */(0L != l27) ? agg27 += Udiv(Ulistmax(1L, l27)) : 0.0);
              _c8.addOrDelOnZero(st15.modify(item_i_item_id,(v93 * (agg26 + (agg27 * -1L)))), (v93 * (agg26 + (agg27 * -1L))));
              n85 = n85->nxt;
            } while (n85 && (e85 = n85->obj) && h74 == n85->hash &&  AGG4STORE2_mapkey0_idxfn::equals(se242, *e85)); 
          }
        }{ //slice 
          const HashIndex_AGG4STORE7_map_0* i86 = static_cast<HashIndex_AGG4STORE7_map_0*>(AGG4STORE7.index[1]);
          const HASH_RES_t h75 = AGG4STORE7_mapkey0_idxfn::hash(se245.modify0(store_s_store_sk));
          HashIndex_AGG4STORE7_map_0::IdxNode* n86 = static_cast<HashIndex_AGG4STORE7_map_0::IdxNode*>(i86->slice(se245, h75));
          AGG4STORE7_entry* e86;
         
          if (n86 && (e86 = n86->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e86->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v94 = e86->__av;
              DOUBLE_TYPE agg28 = 0.0;
              long l28 = (AGG1STORE_SALES1_L1_1.getValueOrDefault(se243.modify(item_i_item_id,store_s_state)) + AGG1STORE2_L1_2.getValueOrDefault(se244.modify(item_i_item_id,store_s_store_sk)));
              (/*if */(0L != l28) ? agg28 += Udiv(Ulistmax(1L, l28)) : 0.0);
              _c8.addOrDelOnZero(st16.modify(item_i_item_id,(v94 * agg28)), (v94 * agg28));
              n86 = n86->nxt;
            } while (n86 && (e86 = n86->obj) && h75 == n86->hash &&  AGG4STORE7_mapkey0_idxfn::equals(se245, *e86)); 
          }
        }{  // temp foreach
          const HashIndex<tuple2_S_D, DOUBLE_TYPE>* i87 = static_cast<HashIndex<tuple2_S_D, DOUBLE_TYPE>*>(_c8.index[0]);
          HashIndex<tuple2_S_D, DOUBLE_TYPE>::IdxNode* n87; 
          tuple2_S_D* e87;
        
          for (size_t i = 0; i < i87->size_; i++)
          {
            n87 = i87->buckets_ + i;
            while (n87 && (e87 = n87->obj))
            {
              STRING_TYPE item_i_item_id = e87->_1;  
              DOUBLE_TYPE v95 = e87->__av; 
            (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG4.addOrDelOnZero(se238.modify(item_i_item_id,store_s_state),v95) : (void)0);      
              n87 = n87->nxt;
            }
          }
        }{ //slice 
          const HashIndex_AGG1STORE2_L1_2_map_1* i88 = static_cast<HashIndex_AGG1STORE2_L1_2_map_1*>(AGG1STORE2_L1_2.index[1]);
          const HASH_RES_t h76 = AGG1STORE2_L1_2_mapkey1_idxfn::hash(se247.modify1(store_s_store_sk));
          HashIndex_AGG1STORE2_L1_2_map_1::IdxNode* n88 = static_cast<HashIndex_AGG1STORE2_L1_2_map_1::IdxNode*>(i88->slice(se247, h76));
          AGG1STORE2_L1_2_entry* e88;
         
          if (n88 && (e88 = n88->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e88->ITEM_I_ITEM_ID;
              long v96 = e88->__av;
              AGG1STORE_SALES1_L1_1.addOrDelOnZero(se246.modify(item_i_item_id,store_s_state),v96);
              n88 = n88->nxt;
            } while (n88 && (e88 = n88->obj) && h76 == n88->hash &&  AGG1STORE2_L1_2_mapkey1_idxfn::equals(se247, *e88)); 
          }
        }{ //slice 
          const HashIndex_AGG4ITEM4STORE2_map_1* i89 = static_cast<HashIndex_AGG4ITEM4STORE2_map_1*>(AGG4ITEM4STORE2.index[2]);
          const HASH_RES_t h77 = AGG4ITEM4STORE2_mapkey1_idxfn::hash(se249.modify1(store_s_store_sk));
          HashIndex_AGG4ITEM4STORE2_map_1::IdxNode* n89 = static_cast<HashIndex_AGG4ITEM4STORE2_map_1::IdxNode*>(i89->slice(se249, h77));
          AGG4ITEM4STORE2_entry* e89;
         
          if (n89 && (e89 = n89->obj)) {
            do {                
              long agg4itemitem_i_item_sk = e89->AGG4ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v97 = e89->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG4ITEM4.addOrDelOnZero(se248.modify(agg4itemitem_i_item_sk,store_s_state),v97) : (void)0);
              n89 = n89->nxt;
            } while (n89 && (e89 = n89->obj) && h77 == n89->hash &&  AGG4ITEM4STORE2_mapkey1_idxfn::equals(se249, *e89)); 
          }
        }{ //slice 
          const HashIndex_AGG4STORE7_map_0* i90 = static_cast<HashIndex_AGG4STORE7_map_0*>(AGG4STORE7.index[1]);
          const HASH_RES_t h78 = AGG4STORE7_mapkey0_idxfn::hash(se251.modify0(store_s_store_sk));
          HashIndex_AGG4STORE7_map_0::IdxNode* n90 = static_cast<HashIndex_AGG4STORE7_map_0::IdxNode*>(i90->slice(se251, h78));
          AGG4STORE7_entry* e90;
         
          if (n90 && (e90 = n90->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e90->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v98 = e90->__av;
              AGG4STORE2.addOrDelOnZero(se250.modify(store_s_state,item_i_item_id),v98);
              n90 = n90->nxt;
            } while (n90 && (e90 = n90->obj) && h78 == n90->hash &&  AGG4STORE7_mapkey0_idxfn::equals(se251, *e90)); 
          }
        }{ //slice 
          const HashIndex_AGG4ITEM4STORE2_map_1* i91 = static_cast<HashIndex_AGG4ITEM4STORE2_map_1*>(AGG4ITEM4STORE2.index[2]);
          const HASH_RES_t h79 = AGG4ITEM4STORE2_mapkey1_idxfn::hash(se253.modify1(store_s_store_sk));
          HashIndex_AGG4ITEM4STORE2_map_1::IdxNode* n91 = static_cast<HashIndex_AGG4ITEM4STORE2_map_1::IdxNode*>(i91->slice(se253, h79));
          AGG4ITEM4STORE2_entry* e91;
         
          if (n91 && (e91 = n91->obj)) {
            do {                
              long agg4store2itemitem_i_item_sk = e91->AGG4ITEMITEM_I_ITEM_SK;
              DOUBLE_TYPE v99 = e91->__av;
              AGG4STORE2ITEM1.addOrDelOnZero(se252.modify(agg4store2itemitem_i_item_sk,store_s_state),v99);
              n91 = n91->nxt;
            } while (n91 && (e91 = n91->obj) && h79 == n91->hash &&  AGG4ITEM4STORE2_mapkey1_idxfn::equals(se253, *e91)); 
          }
        }{ //slice 
          const HashIndex_AGG4STORE7_map_0* i92 = static_cast<HashIndex_AGG4STORE7_map_0*>(AGG4STORE7.index[1]);
          const HASH_RES_t h80 = AGG4STORE7_mapkey0_idxfn::hash(se255.modify0(store_s_store_sk));
          HashIndex_AGG4STORE7_map_0::IdxNode* n92 = static_cast<HashIndex_AGG4STORE7_map_0::IdxNode*>(i92->slice(se255, h80));
          AGG4STORE7_entry* e92;
         
          if (n92 && (e92 = n92->obj)) {
            do {                
              STRING_TYPE item_i_item_id = e92->ITEM_I_ITEM_ID;
              DOUBLE_TYPE v100 = e92->__av;
              (/*if */(((store_s_state == c1) || (store_s_state == c2) || (store_s_state == c3) || (store_s_state == c4) || (store_s_state == c5) || (store_s_state == c6))) ? AGG4STORE_SALES1.addOrDelOnZero(se254.modify(store_s_state,item_i_item_id),v100) : (void)0);
              n92 = n92->nxt;
            } while (n92 && (e92 = n92->obj) && h80 == n92->hash &&  AGG4STORE7_mapkey0_idxfn::equals(se255, *e92)); 
          }
        }
      }
    }
    void on_system_ready_event() {
      {  
        AGG1ITEM1_L1_2STORE_SALES1.clear();
        STRING_TYPE l29 = c7;
        STRING_TYPE l30 = c8;
        STRING_TYPE l31 = c9;
        { //slice 
          const HashIndex_CUSTOMER_DEMOGRAPHICS_map_123* i93 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123*>(CUSTOMER_DEMOGRAPHICS.index[1]);
          const HASH_RES_t h81 = CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::hash(se257.modify123(l29, l30, l31));
          HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode* n93 = static_cast<HashIndex_CUSTOMER_DEMOGRAPHICS_map_123::IdxNode*>(i93->slice(se257, h81));
          CUSTOMER_DEMOGRAPHICS_entry* e93;
         
          if (n93 && (e93 = n93->obj)) {
            do {                
              long agg1item1_l1_2store_salesstore_sales_ss_cdemo_sk = e93->CUSTOMER_DEMOGRAPHICS_CD_DEMO_SK;
              long customer_demographics_cd_purchase_estimate = e93->CUSTOMER_DEMOGRAPHICS_CD_PURCHASE_ESTIMATE;
              STRING_TYPE customer_demographics_cd_credit_rating = e93->CUSTOMER_DEMOGRAPHICS_CD_CREDIT_RATING;
              long customer_demographics_cd_dep_count = e93->CUSTOMER_DEMOGRAPHICS_CD_DEP_COUNT;
              long customer_demographics_cd_dep_employed_count = e93->CUSTOMER_DEMOGRAPHICS_CD_DEP_EMPLOYED_COUNT;
              long customer_demographics_cd_dep_college_count = e93->CUSTOMER_DEMOGRAPHICS_CD_DEP_COLLEGE_COUNT;
              long v101 = e93->__av;
              AGG1ITEM1_L1_2STORE_SALES1.addOrDelOnZero(se256.modify(agg1item1_l1_2store_salesstore_sales_ss_cdemo_sk),v101);
              n93 = n93->nxt;
            } while (n93 && (e93 = n93->obj) && h81 == n93->hash &&  CUSTOMER_DEMOGRAPHICS_mapkey123_idxfn::equals(se257, *e93)); 
          }
        }AGG1ITEM1_L1_2STORE_SALES2.clear();
        long l32 = 2002L;
        { //slice 
          const HashIndex_DATE_DIM_map_6* i94 = static_cast<HashIndex_DATE_DIM_map_6*>(DATE_DIM.index[1]);
          const HASH_RES_t h82 = DATE_DIM_mapkey6_idxfn::hash(se259.modify6(l32));
          HashIndex_DATE_DIM_map_6::IdxNode* n94 = static_cast<HashIndex_DATE_DIM_map_6::IdxNode*>(i94->slice(se259, h82));
          DATE_DIM_entry* e94;
         
          if (n94 && (e94 = n94->obj)) {
            do {                
              long agg1item1_l1_2store_salesstore_sales_ss_sold_date_sk = e94->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e94->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e94->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e94->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e94->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e94->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e94->DATE_DIM_D_DOW;
              long date_dim_d_moy = e94->DATE_DIM_D_MOY;
              long date_dim_d_dom = e94->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e94->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e94->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e94->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e94->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e94->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e94->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e94->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e94->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e94->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e94->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e94->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e94->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e94->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e94->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e94->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e94->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e94->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e94->DATE_DIM_D_CURRENT_YEAR;
              long v102 = e94->__av;
              AGG1ITEM1_L1_2STORE_SALES2.addOrDelOnZero(se258.modify(agg1item1_l1_2store_salesstore_sales_ss_sold_date_sk),v102);
              n94 = n94->nxt;
            } while (n94 && (e94 = n94->obj) && h82 == n94->hash &&  DATE_DIM_mapkey6_idxfn::equals(se259, *e94)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    AGG1ITEM1_L1_2_entry se1;
    AGG1ITEM1_L1_2STORE_SALES1_entry se2;
    AGG1ITEM1_L1_2STORE_SALES2_entry se3;
    AGG1ITEM1_L1_2STORE_SALES3_entry se4;
    AGG1ITEM1_L1_2STORE1_entry se5;
    AGG1ITEM1_L1_2STORE_SALES2_entry se6;
    AGG1ITEM1_L1_2STORE_SALES1_entry se7;
    AGG1ITEM4_entry se8;
    AGG1ITEM1_L1_2STORE_SALES2_entry se9;
    AGG1ITEM1_L1_2STORE_SALES1_entry se10;
    AGG1ITEM4STORE_SALES3_entry se11;
    AGG1ITEM4STORE2_entry se12;
    AGG1ITEM1_L1_2STORE_SALES2_entry se13;
    AGG1ITEM1_L1_2STORE_SALES1_entry se14;
    AGG1STORE2_entry se15;
    AGG1ITEM1_L1_2STORE_SALES2_entry se16;
    AGG1ITEM1_L1_2STORE_SALES1_entry se17;
    AGG1STORE2STORE_SALES4_entry se18;
    AGG1ITEM1_L1_2STORE_SALES3_entry se19;
    AGG1STORE2ITEM1_entry se20;
    AGG1ITEM1_L1_2STORE_SALES1_entry se21;
    AGG1ITEM1_L1_2STORE_SALES2_entry se22;
    AGG1ITEM1_L1_2STORE_SALES3_entry se23;
    AGG1STORE2_L1_2_entry se24;
    AGG1ITEM1_L1_2STORE_SALES1_entry se25;
    AGG1ITEM1_L1_2STORE_SALES2_entry se26;
    AGG1STORE2STORE_SALES4_entry se27;
    AGG1STORE7_entry se28;
    AGG1ITEM1_L1_2STORE_SALES2_entry se29;
    AGG1ITEM1_L1_2STORE_SALES1_entry se30;
    AGG1STORE2STORE_SALES4_entry se31;
    AGG1STORE_SALES1_entry se32;
    AGG1ITEM1_L1_2STORE_SALES1_entry se33;
    AGG1ITEM1_L1_2STORE_SALES2_entry se34;
    AGG1STORE2STORE_SALES4_entry se35;
    AGG1ITEM4STORE_SALES3_entry se36;
    AGG1STORE_SALES1_L1_1_entry se37;
    AGG1ITEM1_L1_2STORE_SALES1_entry se38;
    AGG1ITEM1_L1_2STORE_SALES2_entry se39;
    AGG1ITEM1_L1_2STORE_SALES3_entry se40;
    AGG1STORE2STORE_SALES4_entry se41;
    AGG2ITEM4_entry se42;
    AGG1ITEM1_L1_2STORE_SALES2_entry se43;
    AGG1ITEM1_L1_2STORE_SALES1_entry se44;
    AGG1ITEM4STORE_SALES3_entry se45;
    AGG2ITEM4STORE2_entry se46;
    AGG1ITEM1_L1_2STORE_SALES2_entry se47;
    AGG1ITEM1_L1_2STORE_SALES1_entry se48;
    AGG2STORE2_entry se49;
    AGG1ITEM1_L1_2STORE_SALES2_entry se50;
    AGG1ITEM1_L1_2STORE_SALES1_entry se51;
    AGG1STORE2STORE_SALES4_entry se52;
    AGG1ITEM1_L1_2STORE_SALES3_entry se53;
    AGG2STORE2ITEM1_entry se54;
    AGG1ITEM1_L1_2STORE_SALES1_entry se55;
    AGG1ITEM1_L1_2STORE_SALES2_entry se56;
    AGG1ITEM1_L1_2STORE_SALES3_entry se57;
    AGG2STORE7_entry se58;
    AGG1ITEM1_L1_2STORE_SALES2_entry se59;
    AGG1ITEM1_L1_2STORE_SALES1_entry se60;
    AGG1STORE2STORE_SALES4_entry se61;
    AGG2STORE_SALES1_entry se62;
    AGG1ITEM1_L1_2STORE_SALES1_entry se63;
    AGG1ITEM1_L1_2STORE_SALES2_entry se64;
    AGG1STORE2STORE_SALES4_entry se65;
    AGG1ITEM4STORE_SALES3_entry se66;
    AGG3ITEM4_entry se67;
    AGG1ITEM1_L1_2STORE_SALES2_entry se68;
    AGG1ITEM1_L1_2STORE_SALES1_entry se69;
    AGG1ITEM4STORE_SALES3_entry se70;
    AGG3ITEM4STORE2_entry se71;
    AGG1ITEM1_L1_2STORE_SALES2_entry se72;
    AGG1ITEM1_L1_2STORE_SALES1_entry se73;
    AGG3STORE2_entry se74;
    AGG1ITEM1_L1_2STORE_SALES2_entry se75;
    AGG1ITEM1_L1_2STORE_SALES1_entry se76;
    AGG1STORE2STORE_SALES4_entry se77;
    AGG1ITEM1_L1_2STORE_SALES3_entry se78;
    AGG3STORE2ITEM1_entry se79;
    AGG1ITEM1_L1_2STORE_SALES1_entry se80;
    AGG1ITEM1_L1_2STORE_SALES2_entry se81;
    AGG1ITEM1_L1_2STORE_SALES3_entry se82;
    AGG3STORE7_entry se83;
    AGG1ITEM1_L1_2STORE_SALES2_entry se84;
    AGG1ITEM1_L1_2STORE_SALES1_entry se85;
    AGG1STORE2STORE_SALES4_entry se86;
    AGG3STORE_SALES1_entry se87;
    AGG1ITEM1_L1_2STORE_SALES1_entry se88;
    AGG1ITEM1_L1_2STORE_SALES2_entry se89;
    AGG1STORE2STORE_SALES4_entry se90;
    AGG1ITEM4STORE_SALES3_entry se91;
    AGG4ITEM4_entry se92;
    AGG1ITEM1_L1_2STORE_SALES2_entry se93;
    AGG1ITEM1_L1_2STORE_SALES1_entry se94;
    AGG1ITEM4STORE_SALES3_entry se95;
    AGG4ITEM4STORE2_entry se96;
    AGG1ITEM1_L1_2STORE_SALES2_entry se97;
    AGG1ITEM1_L1_2STORE_SALES1_entry se98;
    AGG4STORE2_entry se99;
    AGG1ITEM1_L1_2STORE_SALES2_entry se100;
    AGG1ITEM1_L1_2STORE_SALES1_entry se101;
    AGG1STORE2STORE_SALES4_entry se102;
    AGG1ITEM1_L1_2STORE_SALES3_entry se103;
    AGG4STORE2ITEM1_entry se104;
    AGG1ITEM1_L1_2STORE_SALES1_entry se105;
    AGG1ITEM1_L1_2STORE_SALES2_entry se106;
    AGG1ITEM1_L1_2STORE_SALES3_entry se107;
    AGG4STORE7_entry se108;
    AGG1ITEM1_L1_2STORE_SALES2_entry se109;
    AGG1ITEM1_L1_2STORE_SALES1_entry se110;
    AGG1STORE2STORE_SALES4_entry se111;
    AGG4STORE_SALES1_entry se112;
    AGG1ITEM1_L1_2STORE_SALES1_entry se113;
    AGG1ITEM1_L1_2STORE_SALES2_entry se114;
    AGG1STORE2STORE_SALES4_entry se115;
    AGG1ITEM4STORE_SALES3_entry se116;
    AGG1_entry se117;
    AGG1STORE_SALES1_L1_1_entry se118;
    AGG2_entry se119;
    AGG1STORE_SALES1_L1_1_entry se120;
    AGG3_entry se121;
    AGG1STORE_SALES1_L1_1_entry se122;
    AGG4_entry se123;
    AGG1STORE_SALES1_L1_1_entry se124;
    AGG1_entry se125;
    AGG1STORE_SALES1_L1_1_entry se126;
    AGG1ITEM1_L1_2_entry se127;
    AGG1STORE_SALES1_L1_1_entry se128;
    tuple2_S_D st1;
    AGG1STORE_SALES1_entry se129;
    AGG1STORE_SALES1_L1_1_entry se130;
    AGG1ITEM1_L1_2_entry se131;
    tuple2_S_D st2;
    AGG1ITEM4_entry se132;
    AGG1STORE2_entry se133;
    AGG1STORE2ITEM1_entry se134;
    AGG1STORE2STORE_SALES4_entry se135;
    AGG1STORE2_L1_2_entry se136;
    AGG1ITEM1_L1_2STORE1_entry se137;
    AGG1STORE7_entry se138;
    AGG1ITEM4STORE2_entry se139;
    AGG1STORE_SALES1_entry se140;
    AGG1ITEM4_entry se141;
    AGG2_entry se142;
    AGG1STORE_SALES1_L1_1_entry se143;
    AGG1ITEM1_L1_2_entry se144;
    AGG1STORE_SALES1_L1_1_entry se145;
    tuple2_S_D st3;
    AGG2STORE_SALES1_entry se146;
    AGG1STORE_SALES1_L1_1_entry se147;
    AGG1ITEM1_L1_2_entry se148;
    tuple2_S_D st4;
    AGG2ITEM4_entry se149;
    AGG2STORE2_entry se150;
    AGG2STORE2ITEM1_entry se151;
    AGG2STORE7_entry se152;
    AGG2ITEM4STORE2_entry se153;
    AGG2STORE_SALES1_entry se154;
    AGG2ITEM4_entry se155;
    AGG3_entry se156;
    AGG1STORE_SALES1_L1_1_entry se157;
    AGG1ITEM1_L1_2_entry se158;
    AGG1STORE_SALES1_L1_1_entry se159;
    tuple2_S_D st5;
    AGG3STORE_SALES1_entry se160;
    AGG1STORE_SALES1_L1_1_entry se161;
    AGG1ITEM1_L1_2_entry se162;
    tuple2_S_D st6;
    AGG3ITEM4_entry se163;
    AGG3STORE2_entry se164;
    AGG3STORE2ITEM1_entry se165;
    AGG3STORE7_entry se166;
    AGG3ITEM4STORE2_entry se167;
    AGG3STORE_SALES1_entry se168;
    AGG3ITEM4_entry se169;
    AGG4_entry se170;
    AGG1STORE_SALES1_L1_1_entry se171;
    AGG1ITEM1_L1_2_entry se172;
    AGG1STORE_SALES1_L1_1_entry se173;
    tuple2_S_D st7;
    AGG4STORE_SALES1_entry se174;
    AGG1STORE_SALES1_L1_1_entry se175;
    AGG1ITEM1_L1_2_entry se176;
    tuple2_S_D st8;
    AGG4ITEM4_entry se177;
    AGG1STORE_SALES1_L1_1_entry se178;
    AGG1ITEM1_L1_2_entry se179;
    AGG4STORE2_entry se180;
    AGG4STORE2ITEM1_entry se181;
    AGG4STORE7_entry se182;
    AGG4ITEM4STORE2_entry se183;
    AGG4STORE_SALES1_entry se184;
    AGG4ITEM4_entry se185;
    AGG1_entry se186;
    AGG1STORE_SALES1_L1_1_entry se187;
    AGG1STORE2_L1_2_entry se188;
    AGG1STORE_SALES1_L1_1_entry se189;
    tuple2_S_D st9;
    AGG1STORE2_entry se190;
    AGG1STORE_SALES1_L1_1_entry se191;
    AGG1STORE2_L1_2_entry se192;
    tuple2_S_D st10;
    AGG1STORE7_entry se193;
    AGG1ITEM1_L1_2_entry se194;
    AGG1ITEM1_L1_2STORE1_entry se195;
    AGG1ITEM1_L1_2STORE_SALES3_entry se196;
    AGG1ITEM4_entry se197;
    AGG1ITEM4STORE2_entry se198;
    AGG1ITEM4STORE_SALES3_entry se199;
    AGG1STORE2_entry se200;
    AGG1STORE7_entry se201;
    AGG1STORE2ITEM1_entry se202;
    AGG1ITEM4STORE2_entry se203;
    AGG1STORE_SALES1_entry se204;
    AGG1STORE7_entry se205;
    AGG2_entry se206;
    AGG1STORE_SALES1_L1_1_entry se207;
    AGG1STORE2_L1_2_entry se208;
    AGG1STORE_SALES1_L1_1_entry se209;
    tuple2_S_D st11;
    AGG2STORE2_entry se210;
    AGG1STORE_SALES1_L1_1_entry se211;
    AGG1STORE2_L1_2_entry se212;
    tuple2_S_D st12;
    AGG2STORE7_entry se213;
    AGG2ITEM4_entry se214;
    AGG2ITEM4STORE2_entry se215;
    AGG2STORE2_entry se216;
    AGG2STORE7_entry se217;
    AGG2STORE2ITEM1_entry se218;
    AGG2ITEM4STORE2_entry se219;
    AGG2STORE_SALES1_entry se220;
    AGG2STORE7_entry se221;
    AGG3_entry se222;
    AGG1STORE_SALES1_L1_1_entry se223;
    AGG1STORE2_L1_2_entry se224;
    AGG1STORE_SALES1_L1_1_entry se225;
    tuple2_S_D st13;
    AGG3STORE2_entry se226;
    AGG1STORE_SALES1_L1_1_entry se227;
    AGG1STORE2_L1_2_entry se228;
    tuple2_S_D st14;
    AGG3STORE7_entry se229;
    AGG3ITEM4_entry se230;
    AGG3ITEM4STORE2_entry se231;
    AGG3STORE2_entry se232;
    AGG3STORE7_entry se233;
    AGG3STORE2ITEM1_entry se234;
    AGG3ITEM4STORE2_entry se235;
    AGG3STORE_SALES1_entry se236;
    AGG3STORE7_entry se237;
    AGG4_entry se238;
    AGG1STORE_SALES1_L1_1_entry se239;
    AGG1STORE2_L1_2_entry se240;
    AGG1STORE_SALES1_L1_1_entry se241;
    tuple2_S_D st15;
    AGG4STORE2_entry se242;
    AGG1STORE_SALES1_L1_1_entry se243;
    AGG1STORE2_L1_2_entry se244;
    tuple2_S_D st16;
    AGG4STORE7_entry se245;
    AGG1STORE_SALES1_L1_1_entry se246;
    AGG1STORE2_L1_2_entry se247;
    AGG4ITEM4_entry se248;
    AGG4ITEM4STORE2_entry se249;
    AGG4STORE2_entry se250;
    AGG4STORE7_entry se251;
    AGG4STORE2ITEM1_entry se252;
    AGG4ITEM4STORE2_entry se253;
    AGG4STORE_SALES1_entry se254;
    AGG4STORE7_entry se255;
    AGG1ITEM1_L1_2STORE_SALES1_entry se256;
    CUSTOMER_DEMOGRAPHICS_entry se257;
    AGG1ITEM1_L1_2STORE_SALES2_entry se258;
    DATE_DIM_entry se259;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    CUSTOMER_DEMOGRAPHICS_map CUSTOMER_DEMOGRAPHICS;
    AGG1ITEM1_L1_2_map AGG1ITEM1_L1_2;
    AGG1ITEM1_L1_2STORE_SALES1_map AGG1ITEM1_L1_2STORE_SALES1;
    AGG1ITEM1_L1_2STORE_SALES2_map AGG1ITEM1_L1_2STORE_SALES2;
    AGG1ITEM1_L1_2STORE_SALES3_map AGG1ITEM1_L1_2STORE_SALES3;
    AGG1ITEM1_L1_2STORE1_map AGG1ITEM1_L1_2STORE1;
    AGG1ITEM4_map AGG1ITEM4;
    AGG1ITEM4STORE2_map AGG1ITEM4STORE2;
    AGG1ITEM4STORE_SALES3_map AGG1ITEM4STORE_SALES3;
    AGG1STORE2_map AGG1STORE2;
    AGG1STORE2ITEM1_map AGG1STORE2ITEM1;
    AGG1STORE2STORE_SALES4_map AGG1STORE2STORE_SALES4;
    AGG1STORE2_L1_2_map AGG1STORE2_L1_2;
    AGG1STORE7_map AGG1STORE7;
    AGG1STORE_SALES1_map AGG1STORE_SALES1;
    AGG1STORE_SALES1_L1_1_map AGG1STORE_SALES1_L1_1;
    AGG2ITEM4_map AGG2ITEM4;
    AGG2ITEM4STORE2_map AGG2ITEM4STORE2;
    AGG2STORE2_map AGG2STORE2;
    AGG2STORE2ITEM1_map AGG2STORE2ITEM1;
    AGG2STORE7_map AGG2STORE7;
    AGG2STORE_SALES1_map AGG2STORE_SALES1;
    AGG3ITEM4_map AGG3ITEM4;
    AGG3ITEM4STORE2_map AGG3ITEM4STORE2;
    AGG3STORE2_map AGG3STORE2;
    AGG3STORE2ITEM1_map AGG3STORE2ITEM1;
    AGG3STORE7_map AGG3STORE7;
    AGG3STORE_SALES1_map AGG3STORE_SALES1;
    AGG4ITEM4_map AGG4ITEM4;
    AGG4ITEM4STORE2_map AGG4ITEM4STORE2;
    AGG4STORE2_map AGG4STORE2;
    AGG4STORE2ITEM1_map AGG4STORE2ITEM1;
    AGG4STORE7_map AGG4STORE7;
    AGG4STORE_SALES1_map AGG4STORE_SALES1;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c1;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c4;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c7;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c6;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c3;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c2;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c5;
    MultiHashMap<tuple2_S_D,DOUBLE_TYPE,HashIndex<tuple2_S_D,DOUBLE_TYPE> > _c8;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ STRING_TYPE c8;
    /*const static*/ STRING_TYPE c9;
    /*const static*/ STRING_TYPE c1;
  
  };

}
