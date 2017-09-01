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
    FORCE_INLINE DATE_DIM_entry& modify614(const long c6, const STRING_TYPE& c14) { DATE_DIM_D_YEAR = c6; DATE_DIM_D_DAY_NAME = c14;  return *this; }
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
  
  struct DATE_DIM_mapkey614_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_DAY_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_DAY_NAME == y.DATE_DIM_D_DAY_NAME;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey614_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey614_idxfn,false> HashIndex_DATE_DIM_map_614;
  
  struct SUN_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit SUN_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit SUN_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    SUN_SALES_entry(const SUN_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALES_entry& x, const SUN_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<SUN_SALES_entry,DOUBLE_TYPE,
    HashIndex<SUN_SALES_entry,DOUBLE_TYPE,SUN_SALES_mapkey01_idxfn,true>
  > SUN_SALES_map;
  typedef HashIndex<SUN_SALES_entry,DOUBLE_TYPE,SUN_SALES_mapkey01_idxfn,true> HashIndex_SUN_SALES_map_01;
  
  struct SUN_SALESSTORE2_entry {
    long SUN_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit SUN_SALESSTORE2_entry() { /*SUN_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit SUN_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { SUN_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    SUN_SALESSTORE2_entry(const SUN_SALESSTORE2_entry& other) : SUN_SALESSTORESTORE_S_STORE_SK( other.SUN_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE2_entry& modify(const long c0) { SUN_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUN_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUN_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE2_entry& x, const SUN_SALESSTORE2_entry& y) {
      return x.SUN_SALESSTORESTORE_S_STORE_SK == y.SUN_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<SUN_SALESSTORE2_entry,DOUBLE_TYPE,SUN_SALESSTORE2_mapkey0_idxfn,true>
  > SUN_SALESSTORE2_map;
  typedef HashIndex<SUN_SALESSTORE2_entry,DOUBLE_TYPE,SUN_SALESSTORE2_mapkey0_idxfn,true> HashIndex_SUN_SALESSTORE2_map_0;
  
  struct SUN_SALESSTORE_SALES1_entry {
    long SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK; STRING_TYPE STORE_S_STORE_ID; STRING_TYPE STORE_S_STORE_NAME; long __av; 
    explicit SUN_SALESSTORE_SALES1_entry() { /*SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK = 0L; STORE_S_STORE_ID = ""; STORE_S_STORE_NAME = ""; __av = 0L; */ }
    explicit SUN_SALESSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2, const long c3) { SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2; __av = c3; }
    SUN_SALESSTORE_SALES1_entry(const SUN_SALESSTORE_SALES1_entry& other) : SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK( other.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const STRING_TYPE& c2) { SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK = c0; STORE_S_STORE_ID = c1; STORE_S_STORE_NAME = c2;  return *this; }
    FORCE_INLINE SUN_SALESSTORE_SALES1_entry& modify0(const long c0) { SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE_SALES1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK);
      hash_combine(h, e.STORE_S_STORE_ID);
      hash_combine(h, e.STORE_S_STORE_NAME);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_entry& x, const SUN_SALESSTORE_SALES1_entry& y) {
      return x.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK == y.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID && x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME;
    }
  };
  
  struct SUN_SALESSTORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES1_entry& x, const SUN_SALESSTORE_SALES1_entry& y) {
      return x.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK == y.SUN_SALESSTORE_SALESSTORE_SALES_SS_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE_SALES1_entry,long,
    HashIndex<SUN_SALESSTORE_SALES1_entry,long,SUN_SALESSTORE_SALES1_mapkey012_idxfn,true>,
    HashIndex<SUN_SALESSTORE_SALES1_entry,long,SUN_SALESSTORE_SALES1_mapkey0_idxfn,false>
  > SUN_SALESSTORE_SALES1_map;
  typedef HashIndex<SUN_SALESSTORE_SALES1_entry,long,SUN_SALESSTORE_SALES1_mapkey012_idxfn,true> HashIndex_SUN_SALESSTORE_SALES1_map_012;
  typedef HashIndex<SUN_SALESSTORE_SALES1_entry,long,SUN_SALESSTORE_SALES1_mapkey0_idxfn,false> HashIndex_SUN_SALESSTORE_SALES1_map_0;
  
  struct SUN_SALESSTORE_SALES2_entry {
    long SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit SUN_SALESSTORE_SALES2_entry() { /*SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit SUN_SALESSTORE_SALES2_entry(const long c0, const long c1) { SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    SUN_SALESSTORE_SALES2_entry(const SUN_SALESSTORE_SALES2_entry& other) : SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE SUN_SALESSTORE_SALES2_entry& modify(const long c0) { SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUN_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUN_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUN_SALESSTORE_SALES2_entry& x, const SUN_SALESSTORE_SALES2_entry& y) {
      return x.SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.SUN_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<SUN_SALESSTORE_SALES2_entry,long,
    HashIndex<SUN_SALESSTORE_SALES2_entry,long,SUN_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > SUN_SALESSTORE_SALES2_map;
  typedef HashIndex<SUN_SALESSTORE_SALES2_entry,long,SUN_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_SUN_SALESSTORE_SALES2_map_0;
  
  struct MON_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit MON_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit MON_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    MON_SALES_entry(const MON_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE MON_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALES_entry& x, const MON_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<MON_SALES_entry,DOUBLE_TYPE,
    HashIndex<MON_SALES_entry,DOUBLE_TYPE,MON_SALES_mapkey01_idxfn,true>
  > MON_SALES_map;
  typedef HashIndex<MON_SALES_entry,DOUBLE_TYPE,MON_SALES_mapkey01_idxfn,true> HashIndex_MON_SALES_map_01;
  
  struct MON_SALESSTORE2_entry {
    long MON_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit MON_SALESSTORE2_entry() { /*MON_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit MON_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { MON_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    MON_SALESSTORE2_entry(const MON_SALESSTORE2_entry& other) : MON_SALESSTORESTORE_S_STORE_SK( other.MON_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE MON_SALESSTORE2_entry& modify(const long c0) { MON_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MON_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MON_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALESSTORE2_entry& x, const MON_SALESSTORE2_entry& y) {
      return x.MON_SALESSTORESTORE_S_STORE_SK == y.MON_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<MON_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<MON_SALESSTORE2_entry,DOUBLE_TYPE,MON_SALESSTORE2_mapkey0_idxfn,true>
  > MON_SALESSTORE2_map;
  typedef HashIndex<MON_SALESSTORE2_entry,DOUBLE_TYPE,MON_SALESSTORE2_mapkey0_idxfn,true> HashIndex_MON_SALESSTORE2_map_0;
  
  struct MON_SALESSTORE_SALES2_entry {
    long MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit MON_SALESSTORE_SALES2_entry() { /*MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit MON_SALESSTORE_SALES2_entry(const long c0, const long c1) { MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    MON_SALESSTORE_SALES2_entry(const MON_SALESSTORE_SALES2_entry& other) : MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE MON_SALESSTORE_SALES2_entry& modify(const long c0) { MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct MON_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const MON_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const MON_SALESSTORE_SALES2_entry& x, const MON_SALESSTORE_SALES2_entry& y) {
      return x.MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.MON_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<MON_SALESSTORE_SALES2_entry,long,
    HashIndex<MON_SALESSTORE_SALES2_entry,long,MON_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > MON_SALESSTORE_SALES2_map;
  typedef HashIndex<MON_SALESSTORE_SALES2_entry,long,MON_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_MON_SALESSTORE_SALES2_map_0;
  
  struct TUE_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit TUE_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit TUE_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    TUE_SALES_entry(const TUE_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALES_entry& x, const TUE_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<TUE_SALES_entry,DOUBLE_TYPE,
    HashIndex<TUE_SALES_entry,DOUBLE_TYPE,TUE_SALES_mapkey01_idxfn,true>
  > TUE_SALES_map;
  typedef HashIndex<TUE_SALES_entry,DOUBLE_TYPE,TUE_SALES_mapkey01_idxfn,true> HashIndex_TUE_SALES_map_01;
  
  struct TUE_SALESSTORE2_entry {
    long TUE_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit TUE_SALESSTORE2_entry() { /*TUE_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit TUE_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { TUE_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    TUE_SALESSTORE2_entry(const TUE_SALESSTORE2_entry& other) : TUE_SALESSTORESTORE_S_STORE_SK( other.TUE_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALESSTORE2_entry& modify(const long c0) { TUE_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TUE_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TUE_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALESSTORE2_entry& x, const TUE_SALESSTORE2_entry& y) {
      return x.TUE_SALESSTORESTORE_S_STORE_SK == y.TUE_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<TUE_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<TUE_SALESSTORE2_entry,DOUBLE_TYPE,TUE_SALESSTORE2_mapkey0_idxfn,true>
  > TUE_SALESSTORE2_map;
  typedef HashIndex<TUE_SALESSTORE2_entry,DOUBLE_TYPE,TUE_SALESSTORE2_mapkey0_idxfn,true> HashIndex_TUE_SALESSTORE2_map_0;
  
  struct TUE_SALESSTORE_SALES2_entry {
    long TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit TUE_SALESSTORE_SALES2_entry() { /*TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit TUE_SALESSTORE_SALES2_entry(const long c0, const long c1) { TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    TUE_SALESSTORE_SALES2_entry(const TUE_SALESSTORE_SALES2_entry& other) : TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE TUE_SALESSTORE_SALES2_entry& modify(const long c0) { TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct TUE_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const TUE_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const TUE_SALESSTORE_SALES2_entry& x, const TUE_SALESSTORE_SALES2_entry& y) {
      return x.TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.TUE_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<TUE_SALESSTORE_SALES2_entry,long,
    HashIndex<TUE_SALESSTORE_SALES2_entry,long,TUE_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > TUE_SALESSTORE_SALES2_map;
  typedef HashIndex<TUE_SALESSTORE_SALES2_entry,long,TUE_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_TUE_SALESSTORE_SALES2_map_0;
  
  struct WED_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit WED_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit WED_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    WED_SALES_entry(const WED_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE WED_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALES_entry& x, const WED_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<WED_SALES_entry,DOUBLE_TYPE,
    HashIndex<WED_SALES_entry,DOUBLE_TYPE,WED_SALES_mapkey01_idxfn,true>
  > WED_SALES_map;
  typedef HashIndex<WED_SALES_entry,DOUBLE_TYPE,WED_SALES_mapkey01_idxfn,true> HashIndex_WED_SALES_map_01;
  
  struct WED_SALESSTORE2_entry {
    long WED_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit WED_SALESSTORE2_entry() { /*WED_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit WED_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { WED_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    WED_SALESSTORE2_entry(const WED_SALESSTORE2_entry& other) : WED_SALESSTORESTORE_S_STORE_SK( other.WED_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE WED_SALESSTORE2_entry& modify(const long c0) { WED_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, WED_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.WED_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALESSTORE2_entry& x, const WED_SALESSTORE2_entry& y) {
      return x.WED_SALESSTORESTORE_S_STORE_SK == y.WED_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<WED_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<WED_SALESSTORE2_entry,DOUBLE_TYPE,WED_SALESSTORE2_mapkey0_idxfn,true>
  > WED_SALESSTORE2_map;
  typedef HashIndex<WED_SALESSTORE2_entry,DOUBLE_TYPE,WED_SALESSTORE2_mapkey0_idxfn,true> HashIndex_WED_SALESSTORE2_map_0;
  
  struct WED_SALESSTORE_SALES2_entry {
    long WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit WED_SALESSTORE_SALES2_entry() { /*WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit WED_SALESSTORE_SALES2_entry(const long c0, const long c1) { WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    WED_SALESSTORE_SALES2_entry(const WED_SALESSTORE_SALES2_entry& other) : WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE WED_SALESSTORE_SALES2_entry& modify(const long c0) { WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct WED_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const WED_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const WED_SALESSTORE_SALES2_entry& x, const WED_SALESSTORE_SALES2_entry& y) {
      return x.WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.WED_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<WED_SALESSTORE_SALES2_entry,long,
    HashIndex<WED_SALESSTORE_SALES2_entry,long,WED_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > WED_SALESSTORE_SALES2_map;
  typedef HashIndex<WED_SALESSTORE_SALES2_entry,long,WED_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_WED_SALESSTORE_SALES2_map_0;
  
  struct THU_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit THU_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit THU_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    THU_SALES_entry(const THU_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE THU_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALES_entry& x, const THU_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<THU_SALES_entry,DOUBLE_TYPE,
    HashIndex<THU_SALES_entry,DOUBLE_TYPE,THU_SALES_mapkey01_idxfn,true>
  > THU_SALES_map;
  typedef HashIndex<THU_SALES_entry,DOUBLE_TYPE,THU_SALES_mapkey01_idxfn,true> HashIndex_THU_SALES_map_01;
  
  struct THU_SALESSTORE2_entry {
    long THU_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit THU_SALESSTORE2_entry() { /*THU_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit THU_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { THU_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    THU_SALESSTORE2_entry(const THU_SALESSTORE2_entry& other) : THU_SALESSTORESTORE_S_STORE_SK( other.THU_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE THU_SALESSTORE2_entry& modify(const long c0) { THU_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, THU_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.THU_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALESSTORE2_entry& x, const THU_SALESSTORE2_entry& y) {
      return x.THU_SALESSTORESTORE_S_STORE_SK == y.THU_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<THU_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<THU_SALESSTORE2_entry,DOUBLE_TYPE,THU_SALESSTORE2_mapkey0_idxfn,true>
  > THU_SALESSTORE2_map;
  typedef HashIndex<THU_SALESSTORE2_entry,DOUBLE_TYPE,THU_SALESSTORE2_mapkey0_idxfn,true> HashIndex_THU_SALESSTORE2_map_0;
  
  struct THU_SALESSTORE_SALES2_entry {
    long THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit THU_SALESSTORE_SALES2_entry() { /*THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit THU_SALESSTORE_SALES2_entry(const long c0, const long c1) { THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    THU_SALESSTORE_SALES2_entry(const THU_SALESSTORE_SALES2_entry& other) : THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE THU_SALESSTORE_SALES2_entry& modify(const long c0) { THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct THU_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const THU_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const THU_SALESSTORE_SALES2_entry& x, const THU_SALESSTORE_SALES2_entry& y) {
      return x.THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.THU_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<THU_SALESSTORE_SALES2_entry,long,
    HashIndex<THU_SALESSTORE_SALES2_entry,long,THU_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > THU_SALESSTORE_SALES2_map;
  typedef HashIndex<THU_SALESSTORE_SALES2_entry,long,THU_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_THU_SALESSTORE_SALES2_map_0;
  
  struct FRI_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit FRI_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit FRI_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    FRI_SALES_entry(const FRI_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALES_entry& x, const FRI_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<FRI_SALES_entry,DOUBLE_TYPE,
    HashIndex<FRI_SALES_entry,DOUBLE_TYPE,FRI_SALES_mapkey01_idxfn,true>
  > FRI_SALES_map;
  typedef HashIndex<FRI_SALES_entry,DOUBLE_TYPE,FRI_SALES_mapkey01_idxfn,true> HashIndex_FRI_SALES_map_01;
  
  struct FRI_SALESSTORE2_entry {
    long FRI_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit FRI_SALESSTORE2_entry() { /*FRI_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit FRI_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { FRI_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    FRI_SALESSTORE2_entry(const FRI_SALESSTORE2_entry& other) : FRI_SALESSTORESTORE_S_STORE_SK( other.FRI_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALESSTORE2_entry& modify(const long c0) { FRI_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, FRI_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.FRI_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALESSTORE2_entry& x, const FRI_SALESSTORE2_entry& y) {
      return x.FRI_SALESSTORESTORE_S_STORE_SK == y.FRI_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<FRI_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<FRI_SALESSTORE2_entry,DOUBLE_TYPE,FRI_SALESSTORE2_mapkey0_idxfn,true>
  > FRI_SALESSTORE2_map;
  typedef HashIndex<FRI_SALESSTORE2_entry,DOUBLE_TYPE,FRI_SALESSTORE2_mapkey0_idxfn,true> HashIndex_FRI_SALESSTORE2_map_0;
  
  struct FRI_SALESSTORE_SALES2_entry {
    long FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit FRI_SALESSTORE_SALES2_entry() { /*FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit FRI_SALESSTORE_SALES2_entry(const long c0, const long c1) { FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    FRI_SALESSTORE_SALES2_entry(const FRI_SALESSTORE_SALES2_entry& other) : FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE FRI_SALESSTORE_SALES2_entry& modify(const long c0) { FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct FRI_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const FRI_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const FRI_SALESSTORE_SALES2_entry& x, const FRI_SALESSTORE_SALES2_entry& y) {
      return x.FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.FRI_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<FRI_SALESSTORE_SALES2_entry,long,
    HashIndex<FRI_SALESSTORE_SALES2_entry,long,FRI_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > FRI_SALESSTORE_SALES2_map;
  typedef HashIndex<FRI_SALESSTORE_SALES2_entry,long,FRI_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_FRI_SALESSTORE_SALES2_map_0;
  
  struct SAT_SALES_entry {
    STRING_TYPE STORE_S_STORE_NAME; STRING_TYPE STORE_S_STORE_ID; DOUBLE_TYPE __av; 
    explicit SAT_SALES_entry() { /*STORE_S_STORE_NAME = ""; STORE_S_STORE_ID = ""; __av = 0.0; */ }
    explicit SAT_SALES_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1; __av = c2; }
    SAT_SALES_entry(const SAT_SALES_entry& other) : STORE_S_STORE_NAME( other.STORE_S_STORE_NAME ), STORE_S_STORE_ID( other.STORE_S_STORE_ID ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALES_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1) { STORE_S_STORE_NAME = c0; STORE_S_STORE_ID = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, STORE_S_STORE_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALES_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALES_entry& e) {
      size_t h = 0;
      hash_combine(h, e.STORE_S_STORE_NAME);
      hash_combine(h, e.STORE_S_STORE_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALES_entry& x, const SAT_SALES_entry& y) {
      return x.STORE_S_STORE_NAME == y.STORE_S_STORE_NAME && x.STORE_S_STORE_ID == y.STORE_S_STORE_ID;
    }
  };
  
  typedef MultiHashMap<SAT_SALES_entry,DOUBLE_TYPE,
    HashIndex<SAT_SALES_entry,DOUBLE_TYPE,SAT_SALES_mapkey01_idxfn,true>
  > SAT_SALES_map;
  typedef HashIndex<SAT_SALES_entry,DOUBLE_TYPE,SAT_SALES_mapkey01_idxfn,true> HashIndex_SAT_SALES_map_01;
  
  struct SAT_SALESSTORE2_entry {
    long SAT_SALESSTORESTORE_S_STORE_SK; DOUBLE_TYPE __av; 
    explicit SAT_SALESSTORE2_entry() { /*SAT_SALESSTORESTORE_S_STORE_SK = 0L; __av = 0.0; */ }
    explicit SAT_SALESSTORE2_entry(const long c0, const DOUBLE_TYPE c1) { SAT_SALESSTORESTORE_S_STORE_SK = c0; __av = c1; }
    SAT_SALESSTORE2_entry(const SAT_SALESSTORE2_entry& other) : SAT_SALESSTORESTORE_S_STORE_SK( other.SAT_SALESSTORESTORE_S_STORE_SK ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALESSTORE2_entry& modify(const long c0) { SAT_SALESSTORESTORE_S_STORE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SAT_SALESSTORESTORE_S_STORE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALESSTORE2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALESSTORE2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SAT_SALESSTORESTORE_S_STORE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALESSTORE2_entry& x, const SAT_SALESSTORE2_entry& y) {
      return x.SAT_SALESSTORESTORE_S_STORE_SK == y.SAT_SALESSTORESTORE_S_STORE_SK;
    }
  };
  
  typedef MultiHashMap<SAT_SALESSTORE2_entry,DOUBLE_TYPE,
    HashIndex<SAT_SALESSTORE2_entry,DOUBLE_TYPE,SAT_SALESSTORE2_mapkey0_idxfn,true>
  > SAT_SALESSTORE2_map;
  typedef HashIndex<SAT_SALESSTORE2_entry,DOUBLE_TYPE,SAT_SALESSTORE2_mapkey0_idxfn,true> HashIndex_SAT_SALESSTORE2_map_0;
  
  struct SAT_SALESSTORE_SALES2_entry {
    long SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit SAT_SALESSTORE_SALES2_entry() { /*SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit SAT_SALESSTORE_SALES2_entry(const long c0, const long c1) { SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    SAT_SALESSTORE_SALES2_entry(const SAT_SALESSTORE_SALES2_entry& other) : SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE SAT_SALESSTORE_SALES2_entry& modify(const long c0) { SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SAT_SALESSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SAT_SALESSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SAT_SALESSTORE_SALES2_entry& x, const SAT_SALESSTORE_SALES2_entry& y) {
      return x.SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.SAT_SALESSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<SAT_SALESSTORE_SALES2_entry,long,
    HashIndex<SAT_SALESSTORE_SALES2_entry,long,SAT_SALESSTORE_SALES2_mapkey0_idxfn,true>
  > SAT_SALESSTORE_SALES2_map;
  typedef HashIndex<SAT_SALESSTORE_SALES2_entry,long,SAT_SALESSTORE_SALES2_mapkey0_idxfn,true> HashIndex_SAT_SALESSTORE_SALES2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const SUN_SALES_map& _SUN_SALES = get_SUN_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUN_SALES), _SUN_SALES, "\t");
      ar << "\n";
      const MON_SALES_map& _MON_SALES = get_MON_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(MON_SALES), _MON_SALES, "\t");
      ar << "\n";
      const TUE_SALES_map& _TUE_SALES = get_TUE_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(TUE_SALES), _TUE_SALES, "\t");
      ar << "\n";
      const WED_SALES_map& _WED_SALES = get_WED_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(WED_SALES), _WED_SALES, "\t");
      ar << "\n";
      const THU_SALES_map& _THU_SALES = get_THU_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(THU_SALES), _THU_SALES, "\t");
      ar << "\n";
      const FRI_SALES_map& _FRI_SALES = get_FRI_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(FRI_SALES), _FRI_SALES, "\t");
      ar << "\n";
      const SAT_SALES_map& _SAT_SALES = get_SAT_SALES();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SAT_SALES), _SAT_SALES, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUN_SALES_map& get_SUN_SALES() const {
      return SUN_SALES;
    
    }
    const MON_SALES_map& get_MON_SALES() const {
      return MON_SALES;
    
    }
    const TUE_SALES_map& get_TUE_SALES() const {
      return TUE_SALES;
    
    }
    const WED_SALES_map& get_WED_SALES() const {
      return WED_SALES;
    
    }
    const THU_SALES_map& get_THU_SALES() const {
      return THU_SALES;
    
    }
    const FRI_SALES_map& get_FRI_SALES() const {
      return FRI_SALES;
    
    }
    const SAT_SALES_map& get_SAT_SALES() const {
      return SAT_SALES;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUN_SALES_map SUN_SALES;
    MON_SALES_map MON_SALES;
    TUE_SALES_map TUE_SALES;
    WED_SALES_map WED_SALES;
    THU_SALES_map THU_SALES;
    FRI_SALES_map FRI_SALES;
    SAT_SALES_map SAT_SALES;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      c6 = STRING_TYPE("Friday");
      c5 = STRING_TYPE("Thursday");
      c2 = STRING_TYPE("Monday");
      c7 = STRING_TYPE("Saturday");
      c1 = STRING_TYPE("Sunday");
      c4 = STRING_TYPE("Wednesday");
      c3 = STRING_TYPE("Tuesday");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_DATE_DIM(const long date_dim_d_date_sk, const STRING_TYPE date_dim_d_date_id, const date date_dim_d_date, const long date_dim_d_month_seq, const long date_dim_d_week_seq, const long date_dim_d_quarter_seq, const long date_dim_d_year, const long date_dim_d_dow, const long date_dim_d_moy, const long date_dim_d_dom, const long date_dim_d_qoy, const long date_dim_d_fy_year, const long date_dim_d_fy_quarter_seq, const long date_dim_d_fy_week_seq, const STRING_TYPE date_dim_d_day_name, const STRING_TYPE date_dim_d_quarter_name, const STRING_TYPE date_dim_d_holiday, const STRING_TYPE date_dim_d_weekend, const STRING_TYPE date_dim_d_following_holiday, const long date_dim_d_first_dom, const long date_dim_d_last_dom, const long date_dim_d_same_day_ly, const long date_dim_d_same_day_lq, const STRING_TYPE date_dim_d_current_day, const STRING_TYPE date_dim_d_current_week, const STRING_TYPE date_dim_d_current_month, const STRING_TYPE date_dim_d_current_quarter, const STRING_TYPE date_dim_d_current_year) {
      DATE_DIM_entry e(date_dim_d_date_sk, date_dim_d_date_id, date_dim_d_date, date_dim_d_month_seq, date_dim_d_week_seq, date_dim_d_quarter_seq, date_dim_d_year, date_dim_d_dow, date_dim_d_moy, date_dim_d_dom, date_dim_d_qoy, date_dim_d_fy_year, date_dim_d_fy_quarter_seq, date_dim_d_fy_week_seq, date_dim_d_day_name, date_dim_d_quarter_name, date_dim_d_holiday, date_dim_d_weekend, date_dim_d_following_holiday, date_dim_d_first_dom, date_dim_d_last_dom, date_dim_d_same_day_ly, date_dim_d_same_day_lq, date_dim_d_current_day, date_dim_d_current_week, date_dim_d_current_month, date_dim_d_current_quarter, date_dim_d_current_year, 1L);
      DATE_DIM.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_STORE_SALES(const long store_sales_ss_sold_date_sk, const long store_sales_ss_sold_time_sk, const long store_sales_ss_item_sk, const long store_sales_ss_customer_sk, const long store_sales_ss_cdemo_sk, const long store_sales_ss_hdemo_sk, const long store_sales_ss_addr_sk, const long store_sales_ss_store_sk, const long store_sales_ss_promo_sk, const long store_sales_ss_ticket_number, const long store_sales_ss_quantity, const DOUBLE_TYPE store_sales_ss_wholesale_cost, const DOUBLE_TYPE store_sales_ss_list_price, const DOUBLE_TYPE store_sales_ss_sales_price, const DOUBLE_TYPE store_sales_ss_ext_discount_amt, const DOUBLE_TYPE store_sales_ss_ext_sales_price, const DOUBLE_TYPE store_sales_ss_ext_wholesale_cost, const DOUBLE_TYPE store_sales_ss_ext_list_price, const DOUBLE_TYPE store_sales_ss_ext_tax, const DOUBLE_TYPE store_sales_ss_coupon_amt, const DOUBLE_TYPE store_sales_ss_net_paid, const DOUBLE_TYPE store_sales_ss_net_paid_inc_tax, const DOUBLE_TYPE store_sales_ss_net_profit) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i1 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h1 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se3.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n1 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i1->slice(se3, h1));
          SUN_SALESSTORE_SALES1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e1->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e1->STORE_S_STORE_NAME;
              long v1 = e1->__av;
              SUN_SALES.addOrDelOnZero(se1.modify(store_s_store_name,store_s_store_id),(SUN_SALESSTORE_SALES2.getValueOrDefault(se2.modify(store_sales_ss_sold_date_sk)) * (v1 * store_sales_ss_sales_price)));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }SUN_SALESSTORE2.addOrDelOnZero(se4.modify(store_sales_ss_store_sk),(SUN_SALESSTORE_SALES2.getValueOrDefault(se5.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i2 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h2 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se8.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n2 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i2->slice(se8, h2));
          SUN_SALESSTORE_SALES1_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e2->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e2->STORE_S_STORE_NAME;
              long v2 = e2->__av;
              MON_SALES.addOrDelOnZero(se6.modify(store_s_store_name,store_s_store_id),(MON_SALESSTORE_SALES2.getValueOrDefault(se7.modify(store_sales_ss_sold_date_sk)) * (v2 * store_sales_ss_sales_price)));
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se8, *e2)); 
          }
        }MON_SALESSTORE2.addOrDelOnZero(se9.modify(store_sales_ss_store_sk),(MON_SALESSTORE_SALES2.getValueOrDefault(se10.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i3 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h3 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se13.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n3 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i3->slice(se13, h3));
          SUN_SALESSTORE_SALES1_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e3->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e3->STORE_S_STORE_NAME;
              long v3 = e3->__av;
              TUE_SALES.addOrDelOnZero(se11.modify(store_s_store_name,store_s_store_id),(TUE_SALESSTORE_SALES2.getValueOrDefault(se12.modify(store_sales_ss_sold_date_sk)) * (v3 * store_sales_ss_sales_price)));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se13, *e3)); 
          }
        }TUE_SALESSTORE2.addOrDelOnZero(se14.modify(store_sales_ss_store_sk),(TUE_SALESSTORE_SALES2.getValueOrDefault(se15.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i4 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h4 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se18.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n4 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i4->slice(se18, h4));
          SUN_SALESSTORE_SALES1_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e4->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e4->STORE_S_STORE_NAME;
              long v4 = e4->__av;
              WED_SALES.addOrDelOnZero(se16.modify(store_s_store_name,store_s_store_id),(WED_SALESSTORE_SALES2.getValueOrDefault(se17.modify(store_sales_ss_sold_date_sk)) * (v4 * store_sales_ss_sales_price)));
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se18, *e4)); 
          }
        }WED_SALESSTORE2.addOrDelOnZero(se19.modify(store_sales_ss_store_sk),(WED_SALESSTORE_SALES2.getValueOrDefault(se20.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i5 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h5 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se23.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n5 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i5->slice(se23, h5));
          SUN_SALESSTORE_SALES1_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e5->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e5->STORE_S_STORE_NAME;
              long v5 = e5->__av;
              THU_SALES.addOrDelOnZero(se21.modify(store_s_store_name,store_s_store_id),(THU_SALESSTORE_SALES2.getValueOrDefault(se22.modify(store_sales_ss_sold_date_sk)) * (v5 * store_sales_ss_sales_price)));
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se23, *e5)); 
          }
        }THU_SALESSTORE2.addOrDelOnZero(se24.modify(store_sales_ss_store_sk),(THU_SALESSTORE_SALES2.getValueOrDefault(se25.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i6 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h6 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se28.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n6 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i6->slice(se28, h6));
          SUN_SALESSTORE_SALES1_entry* e6;
         
          if (n6 && (e6 = n6->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e6->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e6->STORE_S_STORE_NAME;
              long v6 = e6->__av;
              FRI_SALES.addOrDelOnZero(se26.modify(store_s_store_name,store_s_store_id),(FRI_SALESSTORE_SALES2.getValueOrDefault(se27.modify(store_sales_ss_sold_date_sk)) * (v6 * store_sales_ss_sales_price)));
              n6 = n6->nxt;
            } while (n6 && (e6 = n6->obj) && h6 == n6->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se28, *e6)); 
          }
        }FRI_SALESSTORE2.addOrDelOnZero(se29.modify(store_sales_ss_store_sk),(FRI_SALESSTORE_SALES2.getValueOrDefault(se30.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
        { //slice 
          const HashIndex_SUN_SALESSTORE_SALES1_map_0* i7 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0*>(SUN_SALESSTORE_SALES1.index[1]);
          const HASH_RES_t h7 = SUN_SALESSTORE_SALES1_mapkey0_idxfn::hash(se33.modify0(store_sales_ss_store_sk));
          HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode* n7 = static_cast<HashIndex_SUN_SALESSTORE_SALES1_map_0::IdxNode*>(i7->slice(se33, h7));
          SUN_SALESSTORE_SALES1_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              STRING_TYPE store_s_store_id = e7->STORE_S_STORE_ID;
              STRING_TYPE store_s_store_name = e7->STORE_S_STORE_NAME;
              long v7 = e7->__av;
              SAT_SALES.addOrDelOnZero(se31.modify(store_s_store_name,store_s_store_id),(SAT_SALESSTORE_SALES2.getValueOrDefault(se32.modify(store_sales_ss_sold_date_sk)) * (v7 * store_sales_ss_sales_price)));
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h7 == n7->hash &&  SUN_SALESSTORE_SALES1_mapkey0_idxfn::equals(se33, *e7)); 
          }
        }SAT_SALESSTORE2.addOrDelOnZero(se34.modify(store_sales_ss_store_sk),(SAT_SALESSTORE_SALES2.getValueOrDefault(se35.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_sales_price));
      }
    }
    void on_insert_STORE(const long store_s_store_sk, const STRING_TYPE& store_s_store_id, const date store_s_rec_start_date, const date store_s_rec_end_date, const long store_s_closed_date_sk, const STRING_TYPE& store_s_store_name, const long store_s_number_employees, const long store_s_floor_space, const STRING_TYPE& store_s_hours, const STRING_TYPE& store_s_manager, const long store_s_market_id, const STRING_TYPE& store_s_geography_class, const STRING_TYPE& store_s_market_desc, const STRING_TYPE& store_s_market_manager, const long store_s_division_id, const STRING_TYPE& store_s_division_name, const long store_s_company_id, const STRING_TYPE& store_s_company_name, const STRING_TYPE& store_s_street_number, const STRING_TYPE& store_s_street_name, const STRING_TYPE& store_s_street_type, const STRING_TYPE& store_s_suite_number, const STRING_TYPE& store_s_city, const STRING_TYPE& store_s_county, const STRING_TYPE& store_s_state, const STRING_TYPE& store_s_zip, const STRING_TYPE& store_s_country, const DOUBLE_TYPE store_s_gmt_offset, const DOUBLE_TYPE store_s_tax_precentage) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(store_s_gmt_offset == -6L) ? SUN_SALES.addOrDelOnZero(se36.modify(store_s_store_name,store_s_store_id),SUN_SALESSTORE2.getValueOrDefault(se37.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? SUN_SALESSTORE_SALES1.addOrDelOnZero(se38.modify(store_s_store_sk,store_s_store_id,store_s_store_name),1L) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? MON_SALES.addOrDelOnZero(se39.modify(store_s_store_name,store_s_store_id),MON_SALESSTORE2.getValueOrDefault(se40.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? TUE_SALES.addOrDelOnZero(se41.modify(store_s_store_name,store_s_store_id),TUE_SALESSTORE2.getValueOrDefault(se42.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? WED_SALES.addOrDelOnZero(se43.modify(store_s_store_name,store_s_store_id),WED_SALESSTORE2.getValueOrDefault(se44.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? THU_SALES.addOrDelOnZero(se45.modify(store_s_store_name,store_s_store_id),THU_SALESSTORE2.getValueOrDefault(se46.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? FRI_SALES.addOrDelOnZero(se47.modify(store_s_store_name,store_s_store_id),FRI_SALESSTORE2.getValueOrDefault(se48.modify(store_s_store_sk))) : (void)0);
        (/*if */(store_s_gmt_offset == -6L) ? SAT_SALES.addOrDelOnZero(se49.modify(store_s_store_name,store_s_store_id),SAT_SALESSTORE2.getValueOrDefault(se50.modify(store_s_store_sk))) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        SUN_SALESSTORE_SALES2.clear();
        long l1 = 1998L;
        STRING_TYPE l2 = c1;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i8 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h8 = DATE_DIM_mapkey614_idxfn::hash(se52.modify614(l1, l2));
          HashIndex_DATE_DIM_map_614::IdxNode* n8 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i8->slice(se52, h8));
          DATE_DIM_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long sun_salesstore_salesstore_sales_ss_sold_date_sk = e8->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e8->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e8->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e8->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e8->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e8->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e8->DATE_DIM_D_DOW;
              long date_dim_d_moy = e8->DATE_DIM_D_MOY;
              long date_dim_d_dom = e8->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e8->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e8->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e8->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e8->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e8->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e8->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e8->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e8->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e8->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e8->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e8->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e8->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e8->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e8->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e8->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e8->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e8->DATE_DIM_D_CURRENT_YEAR;
              long v8 = e8->__av;
              SUN_SALESSTORE_SALES2.addOrDelOnZero(se51.modify(sun_salesstore_salesstore_sales_ss_sold_date_sk),v8);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h8 == n8->hash &&  DATE_DIM_mapkey614_idxfn::equals(se52, *e8)); 
          }
        }MON_SALESSTORE_SALES2.clear();
        long l3 = 1998L;
        STRING_TYPE l4 = c2;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i9 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h9 = DATE_DIM_mapkey614_idxfn::hash(se54.modify614(l3, l4));
          HashIndex_DATE_DIM_map_614::IdxNode* n9 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i9->slice(se54, h9));
          DATE_DIM_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long mon_salesstore_salesstore_sales_ss_sold_date_sk = e9->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e9->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e9->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e9->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e9->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e9->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e9->DATE_DIM_D_DOW;
              long date_dim_d_moy = e9->DATE_DIM_D_MOY;
              long date_dim_d_dom = e9->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e9->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e9->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e9->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e9->DATE_DIM_D_FY_WEEK_SEQ;
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
              long v9 = e9->__av;
              MON_SALESSTORE_SALES2.addOrDelOnZero(se53.modify(mon_salesstore_salesstore_sales_ss_sold_date_sk),v9);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h9 == n9->hash &&  DATE_DIM_mapkey614_idxfn::equals(se54, *e9)); 
          }
        }TUE_SALESSTORE_SALES2.clear();
        long l5 = 1998L;
        STRING_TYPE l6 = c3;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i10 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h10 = DATE_DIM_mapkey614_idxfn::hash(se56.modify614(l5, l6));
          HashIndex_DATE_DIM_map_614::IdxNode* n10 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i10->slice(se56, h10));
          DATE_DIM_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long tue_salesstore_salesstore_sales_ss_sold_date_sk = e10->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e10->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e10->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e10->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e10->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e10->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e10->DATE_DIM_D_DOW;
              long date_dim_d_moy = e10->DATE_DIM_D_MOY;
              long date_dim_d_dom = e10->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e10->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e10->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e10->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e10->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e10->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e10->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e10->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e10->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e10->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e10->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e10->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e10->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e10->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e10->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e10->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e10->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e10->DATE_DIM_D_CURRENT_YEAR;
              long v10 = e10->__av;
              TUE_SALESSTORE_SALES2.addOrDelOnZero(se55.modify(tue_salesstore_salesstore_sales_ss_sold_date_sk),v10);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h10 == n10->hash &&  DATE_DIM_mapkey614_idxfn::equals(se56, *e10)); 
          }
        }WED_SALESSTORE_SALES2.clear();
        long l7 = 1998L;
        STRING_TYPE l8 = c4;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i11 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h11 = DATE_DIM_mapkey614_idxfn::hash(se58.modify614(l7, l8));
          HashIndex_DATE_DIM_map_614::IdxNode* n11 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i11->slice(se58, h11));
          DATE_DIM_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long wed_salesstore_salesstore_sales_ss_sold_date_sk = e11->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e11->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e11->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e11->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e11->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e11->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e11->DATE_DIM_D_DOW;
              long date_dim_d_moy = e11->DATE_DIM_D_MOY;
              long date_dim_d_dom = e11->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e11->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e11->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e11->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e11->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e11->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e11->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e11->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e11->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e11->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e11->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e11->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e11->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e11->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e11->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e11->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e11->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e11->DATE_DIM_D_CURRENT_YEAR;
              long v11 = e11->__av;
              WED_SALESSTORE_SALES2.addOrDelOnZero(se57.modify(wed_salesstore_salesstore_sales_ss_sold_date_sk),v11);
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h11 == n11->hash &&  DATE_DIM_mapkey614_idxfn::equals(se58, *e11)); 
          }
        }THU_SALESSTORE_SALES2.clear();
        long l9 = 1998L;
        STRING_TYPE l10 = c5;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i12 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h12 = DATE_DIM_mapkey614_idxfn::hash(se60.modify614(l9, l10));
          HashIndex_DATE_DIM_map_614::IdxNode* n12 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i12->slice(se60, h12));
          DATE_DIM_entry* e12;
         
          if (n12 && (e12 = n12->obj)) {
            do {                
              long thu_salesstore_salesstore_sales_ss_sold_date_sk = e12->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e12->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e12->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e12->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e12->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e12->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e12->DATE_DIM_D_DOW;
              long date_dim_d_moy = e12->DATE_DIM_D_MOY;
              long date_dim_d_dom = e12->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e12->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e12->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e12->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e12->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e12->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e12->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e12->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e12->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e12->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e12->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e12->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e12->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e12->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e12->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e12->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e12->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e12->DATE_DIM_D_CURRENT_YEAR;
              long v12 = e12->__av;
              THU_SALESSTORE_SALES2.addOrDelOnZero(se59.modify(thu_salesstore_salesstore_sales_ss_sold_date_sk),v12);
              n12 = n12->nxt;
            } while (n12 && (e12 = n12->obj) && h12 == n12->hash &&  DATE_DIM_mapkey614_idxfn::equals(se60, *e12)); 
          }
        }FRI_SALESSTORE_SALES2.clear();
        long l11 = 1998L;
        STRING_TYPE l12 = c6;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i13 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h13 = DATE_DIM_mapkey614_idxfn::hash(se62.modify614(l11, l12));
          HashIndex_DATE_DIM_map_614::IdxNode* n13 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i13->slice(se62, h13));
          DATE_DIM_entry* e13;
         
          if (n13 && (e13 = n13->obj)) {
            do {                
              long fri_salesstore_salesstore_sales_ss_sold_date_sk = e13->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e13->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e13->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e13->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e13->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e13->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e13->DATE_DIM_D_DOW;
              long date_dim_d_moy = e13->DATE_DIM_D_MOY;
              long date_dim_d_dom = e13->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e13->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e13->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e13->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e13->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e13->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e13->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e13->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e13->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e13->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e13->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e13->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e13->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e13->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e13->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e13->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e13->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e13->DATE_DIM_D_CURRENT_YEAR;
              long v13 = e13->__av;
              FRI_SALESSTORE_SALES2.addOrDelOnZero(se61.modify(fri_salesstore_salesstore_sales_ss_sold_date_sk),v13);
              n13 = n13->nxt;
            } while (n13 && (e13 = n13->obj) && h13 == n13->hash &&  DATE_DIM_mapkey614_idxfn::equals(se62, *e13)); 
          }
        }SAT_SALESSTORE_SALES2.clear();
        long l13 = 1998L;
        STRING_TYPE l14 = c7;
        { //slice 
          const HashIndex_DATE_DIM_map_614* i14 = static_cast<HashIndex_DATE_DIM_map_614*>(DATE_DIM.index[1]);
          const HASH_RES_t h14 = DATE_DIM_mapkey614_idxfn::hash(se64.modify614(l13, l14));
          HashIndex_DATE_DIM_map_614::IdxNode* n14 = static_cast<HashIndex_DATE_DIM_map_614::IdxNode*>(i14->slice(se64, h14));
          DATE_DIM_entry* e14;
         
          if (n14 && (e14 = n14->obj)) {
            do {                
              long sat_salesstore_salesstore_sales_ss_sold_date_sk = e14->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e14->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e14->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e14->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e14->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e14->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e14->DATE_DIM_D_DOW;
              long date_dim_d_moy = e14->DATE_DIM_D_MOY;
              long date_dim_d_dom = e14->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e14->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e14->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e14->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e14->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_quarter_name = e14->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e14->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e14->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e14->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e14->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e14->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e14->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e14->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e14->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e14->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e14->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e14->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e14->DATE_DIM_D_CURRENT_YEAR;
              long v14 = e14->__av;
              SAT_SALESSTORE_SALES2.addOrDelOnZero(se63.modify(sat_salesstore_salesstore_sales_ss_sold_date_sk),v14);
              n14 = n14->nxt;
            } while (n14 && (e14 = n14->obj) && h14 == n14->hash &&  DATE_DIM_mapkey614_idxfn::equals(se64, *e14)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUN_SALES_entry se1;
    SUN_SALESSTORE_SALES2_entry se2;
    SUN_SALESSTORE_SALES1_entry se3;
    SUN_SALESSTORE2_entry se4;
    SUN_SALESSTORE_SALES2_entry se5;
    MON_SALES_entry se6;
    MON_SALESSTORE_SALES2_entry se7;
    SUN_SALESSTORE_SALES1_entry se8;
    MON_SALESSTORE2_entry se9;
    MON_SALESSTORE_SALES2_entry se10;
    TUE_SALES_entry se11;
    TUE_SALESSTORE_SALES2_entry se12;
    SUN_SALESSTORE_SALES1_entry se13;
    TUE_SALESSTORE2_entry se14;
    TUE_SALESSTORE_SALES2_entry se15;
    WED_SALES_entry se16;
    WED_SALESSTORE_SALES2_entry se17;
    SUN_SALESSTORE_SALES1_entry se18;
    WED_SALESSTORE2_entry se19;
    WED_SALESSTORE_SALES2_entry se20;
    THU_SALES_entry se21;
    THU_SALESSTORE_SALES2_entry se22;
    SUN_SALESSTORE_SALES1_entry se23;
    THU_SALESSTORE2_entry se24;
    THU_SALESSTORE_SALES2_entry se25;
    FRI_SALES_entry se26;
    FRI_SALESSTORE_SALES2_entry se27;
    SUN_SALESSTORE_SALES1_entry se28;
    FRI_SALESSTORE2_entry se29;
    FRI_SALESSTORE_SALES2_entry se30;
    SAT_SALES_entry se31;
    SAT_SALESSTORE_SALES2_entry se32;
    SUN_SALESSTORE_SALES1_entry se33;
    SAT_SALESSTORE2_entry se34;
    SAT_SALESSTORE_SALES2_entry se35;
    SUN_SALES_entry se36;
    SUN_SALESSTORE2_entry se37;
    SUN_SALESSTORE_SALES1_entry se38;
    MON_SALES_entry se39;
    MON_SALESSTORE2_entry se40;
    TUE_SALES_entry se41;
    TUE_SALESSTORE2_entry se42;
    WED_SALES_entry se43;
    WED_SALESSTORE2_entry se44;
    THU_SALES_entry se45;
    THU_SALESSTORE2_entry se46;
    FRI_SALES_entry se47;
    FRI_SALESSTORE2_entry se48;
    SAT_SALES_entry se49;
    SAT_SALESSTORE2_entry se50;
    SUN_SALESSTORE_SALES2_entry se51;
    DATE_DIM_entry se52;
    MON_SALESSTORE_SALES2_entry se53;
    DATE_DIM_entry se54;
    TUE_SALESSTORE_SALES2_entry se55;
    DATE_DIM_entry se56;
    WED_SALESSTORE_SALES2_entry se57;
    DATE_DIM_entry se58;
    THU_SALESSTORE_SALES2_entry se59;
    DATE_DIM_entry se60;
    FRI_SALESSTORE_SALES2_entry se61;
    DATE_DIM_entry se62;
    SAT_SALESSTORE_SALES2_entry se63;
    DATE_DIM_entry se64;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    SUN_SALESSTORE2_map SUN_SALESSTORE2;
    SUN_SALESSTORE_SALES1_map SUN_SALESSTORE_SALES1;
    SUN_SALESSTORE_SALES2_map SUN_SALESSTORE_SALES2;
    MON_SALESSTORE2_map MON_SALESSTORE2;
    MON_SALESSTORE_SALES2_map MON_SALESSTORE_SALES2;
    TUE_SALESSTORE2_map TUE_SALESSTORE2;
    TUE_SALESSTORE_SALES2_map TUE_SALESSTORE_SALES2;
    WED_SALESSTORE2_map WED_SALESSTORE2;
    WED_SALESSTORE_SALES2_map WED_SALESSTORE_SALES2;
    THU_SALESSTORE2_map THU_SALESSTORE2;
    THU_SALESSTORE_SALES2_map THU_SALESSTORE_SALES2;
    FRI_SALESSTORE2_map FRI_SALESSTORE2;
    FRI_SALESSTORE_SALES2_map FRI_SALESSTORE_SALES2;
    SAT_SALESSTORE2_map SAT_SALESSTORE2;
    SAT_SALESSTORE_SALES2_map SAT_SALESSTORE_SALES2;
    
    /*const static*/ STRING_TYPE c6;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c2;
    /*const static*/ STRING_TYPE c7;
    /*const static*/ STRING_TYPE c1;
    /*const static*/ STRING_TYPE c4;
    /*const static*/ STRING_TYPE c3;
  
  };

}
