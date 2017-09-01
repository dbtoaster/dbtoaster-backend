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
    FORCE_INLINE DATE_DIM_entry& modify8(const long c8) { DATE_DIM_D_MOY = c8;  return *this; }
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
  
  struct DATE_DIM_mapkey8_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_MOY);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_MOY == y.DATE_DIM_D_MOY;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey8_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey8_idxfn,false> HashIndex_DATE_DIM_map_8;
  
  struct SUM_AGG_entry {
    long DT_D_YEAR; long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit SUM_AGG_entry() { /*DT_D_YEAR = 0L; BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit SUM_AGG_entry(const long c0, const long c1, const STRING_TYPE& c2, const DOUBLE_TYPE c3) { DT_D_YEAR = c0; BRAND_ID = c1; BRAND = c2; __av = c3; }
    SUM_AGG_entry(const SUM_AGG_entry& other) : DT_D_YEAR( other.DT_D_YEAR ), BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE SUM_AGG_entry& modify(const long c0, const long c1, const STRING_TYPE& c2) { DT_D_YEAR = c0; BRAND_ID = c1; BRAND = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_AGG_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGG_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DT_D_YEAR);
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGG_entry& x, const SUM_AGG_entry& y) {
      return x.DT_D_YEAR == y.DT_D_YEAR && x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  typedef MultiHashMap<SUM_AGG_entry,DOUBLE_TYPE,
    HashIndex<SUM_AGG_entry,DOUBLE_TYPE,SUM_AGG_mapkey012_idxfn,true>
  > SUM_AGG_map;
  typedef HashIndex<SUM_AGG_entry,DOUBLE_TYPE,SUM_AGG_mapkey012_idxfn,true> HashIndex_SUM_AGG_map_012;
  
  struct SUM_AGGITEM2_entry {
    long SUM_AGGITEMITEM_I_ITEM_SK; long DT_D_YEAR; DOUBLE_TYPE __av; 
    explicit SUM_AGGITEM2_entry() { /*SUM_AGGITEMITEM_I_ITEM_SK = 0L; DT_D_YEAR = 0L; __av = 0.0; */ }
    explicit SUM_AGGITEM2_entry(const long c0, const long c1, const DOUBLE_TYPE c2) { SUM_AGGITEMITEM_I_ITEM_SK = c0; DT_D_YEAR = c1; __av = c2; }
    SUM_AGGITEM2_entry(const SUM_AGGITEM2_entry& other) : SUM_AGGITEMITEM_I_ITEM_SK( other.SUM_AGGITEMITEM_I_ITEM_SK ), DT_D_YEAR( other.DT_D_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_AGGITEM2_entry& modify(const long c0, const long c1) { SUM_AGGITEMITEM_I_ITEM_SK = c0; DT_D_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_AGGITEM2_entry& modify0(const long c0) { SUM_AGGITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUM_AGGITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_AGGITEM2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGITEMITEM_I_ITEM_SK);
      hash_combine(h, e.DT_D_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGITEM2_entry& x, const SUM_AGGITEM2_entry& y) {
      return x.SUM_AGGITEMITEM_I_ITEM_SK == y.SUM_AGGITEMITEM_I_ITEM_SK && x.DT_D_YEAR == y.DT_D_YEAR;
    }
  };
  
  struct SUM_AGGITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGITEM2_entry& x, const SUM_AGGITEM2_entry& y) {
      return x.SUM_AGGITEMITEM_I_ITEM_SK == y.SUM_AGGITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<SUM_AGGITEM2_entry,DOUBLE_TYPE,
    HashIndex<SUM_AGGITEM2_entry,DOUBLE_TYPE,SUM_AGGITEM2_mapkey01_idxfn,true>,
    HashIndex<SUM_AGGITEM2_entry,DOUBLE_TYPE,SUM_AGGITEM2_mapkey0_idxfn,false>
  > SUM_AGGITEM2_map;
  typedef HashIndex<SUM_AGGITEM2_entry,DOUBLE_TYPE,SUM_AGGITEM2_mapkey01_idxfn,true> HashIndex_SUM_AGGITEM2_map_01;
  typedef HashIndex<SUM_AGGITEM2_entry,DOUBLE_TYPE,SUM_AGGITEM2_mapkey0_idxfn,false> HashIndex_SUM_AGGITEM2_map_0;
  
  struct SUM_AGGSTORE_SALES1_entry {
    long SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK; STRING_TYPE BRAND; long BRAND_ID; long __av; 
    explicit SUM_AGGSTORE_SALES1_entry() { /*SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK = 0L; BRAND = ""; BRAND_ID = 0L; __av = 0L; */ }
    explicit SUM_AGGSTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2; __av = c3; }
    SUM_AGGSTORE_SALES1_entry(const SUM_AGGSTORE_SALES1_entry& other) : SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK( other.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK ), BRAND( other.BRAND ), BRAND_ID( other.BRAND_ID ), __av( other.__av ) {}
    FORCE_INLINE SUM_AGGSTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2;  return *this; }
    FORCE_INLINE SUM_AGGSTORE_SALES1_entry& modify0(const long c0) { SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_AGGSTORE_SALES1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.BRAND_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGSTORE_SALES1_entry& x, const SUM_AGGSTORE_SALES1_entry& y) {
      return x.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK == y.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK && x.BRAND == y.BRAND && x.BRAND_ID == y.BRAND_ID;
    }
  };
  
  struct SUM_AGGSTORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGSTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGSTORE_SALES1_entry& x, const SUM_AGGSTORE_SALES1_entry& y) {
      return x.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK == y.SUM_AGGSTORE_SALESSTORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<SUM_AGGSTORE_SALES1_entry,long,
    HashIndex<SUM_AGGSTORE_SALES1_entry,long,SUM_AGGSTORE_SALES1_mapkey012_idxfn,true>,
    HashIndex<SUM_AGGSTORE_SALES1_entry,long,SUM_AGGSTORE_SALES1_mapkey0_idxfn,false>
  > SUM_AGGSTORE_SALES1_map;
  typedef HashIndex<SUM_AGGSTORE_SALES1_entry,long,SUM_AGGSTORE_SALES1_mapkey012_idxfn,true> HashIndex_SUM_AGGSTORE_SALES1_map_012;
  typedef HashIndex<SUM_AGGSTORE_SALES1_entry,long,SUM_AGGSTORE_SALES1_mapkey0_idxfn,false> HashIndex_SUM_AGGSTORE_SALES1_map_0;
  
  struct SUM_AGGSTORE_SALES2_entry {
    long SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long DT_D_YEAR; long __av; 
    explicit SUM_AGGSTORE_SALES2_entry() { /*SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; DT_D_YEAR = 0L; __av = 0L; */ }
    explicit SUM_AGGSTORE_SALES2_entry(const long c0, const long c1, const long c2) { SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; DT_D_YEAR = c1; __av = c2; }
    SUM_AGGSTORE_SALES2_entry(const SUM_AGGSTORE_SALES2_entry& other) : SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), DT_D_YEAR( other.DT_D_YEAR ), __av( other.__av ) {}
    FORCE_INLINE SUM_AGGSTORE_SALES2_entry& modify(const long c0, const long c1) { SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; DT_D_YEAR = c1;  return *this; }
    FORCE_INLINE SUM_AGGSTORE_SALES2_entry& modify0(const long c0) { SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, DT_D_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct SUM_AGGSTORE_SALES2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      hash_combine(h, e.DT_D_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGSTORE_SALES2_entry& x, const SUM_AGGSTORE_SALES2_entry& y) {
      return x.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK && x.DT_D_YEAR == y.DT_D_YEAR;
    }
  };
  
  struct SUM_AGGSTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const SUM_AGGSTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const SUM_AGGSTORE_SALES2_entry& x, const SUM_AGGSTORE_SALES2_entry& y) {
      return x.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.SUM_AGGSTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<SUM_AGGSTORE_SALES2_entry,long,
    HashIndex<SUM_AGGSTORE_SALES2_entry,long,SUM_AGGSTORE_SALES2_mapkey01_idxfn,true>,
    HashIndex<SUM_AGGSTORE_SALES2_entry,long,SUM_AGGSTORE_SALES2_mapkey0_idxfn,false>
  > SUM_AGGSTORE_SALES2_map;
  typedef HashIndex<SUM_AGGSTORE_SALES2_entry,long,SUM_AGGSTORE_SALES2_mapkey01_idxfn,true> HashIndex_SUM_AGGSTORE_SALES2_map_01;
  typedef HashIndex<SUM_AGGSTORE_SALES2_entry,long,SUM_AGGSTORE_SALES2_mapkey0_idxfn,false> HashIndex_SUM_AGGSTORE_SALES2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const SUM_AGG_map& _SUM_AGG = get_SUM_AGG();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(SUM_AGG), _SUM_AGG, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const SUM_AGG_map& get_SUM_AGG() const {
      return SUM_AGG;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    SUM_AGG_map SUM_AGG;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t() {
      
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
          const HashIndex_SUM_AGGSTORE_SALES1_map_0* i1 = static_cast<HashIndex_SUM_AGGSTORE_SALES1_map_0*>(SUM_AGGSTORE_SALES1.index[1]);
          const HASH_RES_t h2 = SUM_AGGSTORE_SALES1_mapkey0_idxfn::hash(se3.modify0(store_sales_ss_item_sk));
          HashIndex_SUM_AGGSTORE_SALES1_map_0::IdxNode* n1 = static_cast<HashIndex_SUM_AGGSTORE_SALES1_map_0::IdxNode*>(i1->slice(se3, h2));
          SUM_AGGSTORE_SALES1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE brand = e1->BRAND;
              long brand_id = e1->BRAND_ID;
              long v1 = e1->__av;
              { //slice 
                const HashIndex_SUM_AGGSTORE_SALES2_map_0* i2 = static_cast<HashIndex_SUM_AGGSTORE_SALES2_map_0*>(SUM_AGGSTORE_SALES2.index[1]);
                const HASH_RES_t h1 = SUM_AGGSTORE_SALES2_mapkey0_idxfn::hash(se2.modify0(store_sales_ss_sold_date_sk));
                HashIndex_SUM_AGGSTORE_SALES2_map_0::IdxNode* n2 = static_cast<HashIndex_SUM_AGGSTORE_SALES2_map_0::IdxNode*>(i2->slice(se2, h1));
                SUM_AGGSTORE_SALES2_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    long dt_d_year = e2->DT_D_YEAR;
                    long v2 = e2->__av;
                    SUM_AGG.addOrDelOnZero(se1.modify(dt_d_year,brand_id,brand),(v1 * (v2 * store_sales_ss_ext_sales_price)));
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h1 == n2->hash &&  SUM_AGGSTORE_SALES2_mapkey0_idxfn::equals(se2, *e2)); 
                }
              }
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h2 == n1->hash &&  SUM_AGGSTORE_SALES1_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }{ //slice 
          const HashIndex_SUM_AGGSTORE_SALES2_map_0* i3 = static_cast<HashIndex_SUM_AGGSTORE_SALES2_map_0*>(SUM_AGGSTORE_SALES2.index[1]);
          const HASH_RES_t h3 = SUM_AGGSTORE_SALES2_mapkey0_idxfn::hash(se5.modify0(store_sales_ss_sold_date_sk));
          HashIndex_SUM_AGGSTORE_SALES2_map_0::IdxNode* n3 = static_cast<HashIndex_SUM_AGGSTORE_SALES2_map_0::IdxNode*>(i3->slice(se5, h3));
          SUM_AGGSTORE_SALES2_entry* e3;
         
          if (n3 && (e3 = n3->obj)) {
            do {                
              long dt_d_year = e3->DT_D_YEAR;
              long v3 = e3->__av;
              SUM_AGGITEM2.addOrDelOnZero(se4.modify(store_sales_ss_item_sk,dt_d_year),(v3 * store_sales_ss_ext_sales_price));
              n3 = n3->nxt;
            } while (n3 && (e3 = n3->obj) && h3 == n3->hash &&  SUM_AGGSTORE_SALES2_mapkey0_idxfn::equals(se5, *e3)); 
          }
        }
      }
    }
    void on_insert_ITEM(const long item_i_item_sk, const STRING_TYPE& item_i_item_id, const date item_i_rec_start_date, const date item_i_rec_end_date, const STRING_TYPE& item_i_item_desc, const DOUBLE_TYPE item_i_current_price, const DOUBLE_TYPE item_i_wholesale_cost, const long item_i_brand_id, const STRING_TYPE& item_i_brand, const long item_i_class_id, const STRING_TYPE& item_i_class, const long item_i_category_id, const STRING_TYPE& item_i_category, const long item_i_manufact_id, const STRING_TYPE& item_i_manufact, const STRING_TYPE& item_i_size, const STRING_TYPE& item_i_formulation, const STRING_TYPE& item_i_color, const STRING_TYPE& item_i_units, const STRING_TYPE& item_i_container, const long item_i_manager_id, const STRING_TYPE& item_i_product_name) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        { //slice 
          const HashIndex_SUM_AGGITEM2_map_0* i4 = static_cast<HashIndex_SUM_AGGITEM2_map_0*>(SUM_AGGITEM2.index[1]);
          const HASH_RES_t h4 = SUM_AGGITEM2_mapkey0_idxfn::hash(se7.modify0(item_i_item_sk));
          HashIndex_SUM_AGGITEM2_map_0::IdxNode* n4 = static_cast<HashIndex_SUM_AGGITEM2_map_0::IdxNode*>(i4->slice(se7, h4));
          SUM_AGGITEM2_entry* e4;
         
          if (n4 && (e4 = n4->obj)) {
            do {                
              long dt_d_year = e4->DT_D_YEAR;
              DOUBLE_TYPE v4 = e4->__av;
              (/*if */(item_i_manufact_id == 436L) ? SUM_AGG.addOrDelOnZero(se6.modify(dt_d_year,item_i_brand_id,item_i_brand),v4) : (void)0);
              n4 = n4->nxt;
            } while (n4 && (e4 = n4->obj) && h4 == n4->hash &&  SUM_AGGITEM2_mapkey0_idxfn::equals(se7, *e4)); 
          }
        }(/*if */(item_i_manufact_id == 436L) ? SUM_AGGSTORE_SALES1.addOrDelOnZero(se8.modify(item_i_item_sk,item_i_brand,item_i_brand_id),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        SUM_AGGSTORE_SALES2.clear();
        long l1 = 12L;
        { //slice 
          const HashIndex_DATE_DIM_map_8* i5 = static_cast<HashIndex_DATE_DIM_map_8*>(DATE_DIM.index[1]);
          const HASH_RES_t h5 = DATE_DIM_mapkey8_idxfn::hash(se10.modify8(l1));
          HashIndex_DATE_DIM_map_8::IdxNode* n5 = static_cast<HashIndex_DATE_DIM_map_8::IdxNode*>(i5->slice(se10, h5));
          DATE_DIM_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long sum_aggstore_salesstore_sales_ss_sold_date_sk = e5->DATE_DIM_D_DATE_SK;
              STRING_TYPE dt_d_date_id = e5->DATE_DIM_D_DATE_ID;
              date dt_d_date = e5->DATE_DIM_D_DATE;
              long dt_d_month_seq = e5->DATE_DIM_D_MONTH_SEQ;
              long dt_d_week_seq = e5->DATE_DIM_D_WEEK_SEQ;
              long dt_d_quarter_seq = e5->DATE_DIM_D_QUARTER_SEQ;
              long dt_d_year = e5->DATE_DIM_D_YEAR;
              long dt_d_dow = e5->DATE_DIM_D_DOW;
              long dt_d_dom = e5->DATE_DIM_D_DOM;
              long dt_d_qoy = e5->DATE_DIM_D_QOY;
              long dt_d_fy_year = e5->DATE_DIM_D_FY_YEAR;
              long dt_d_fy_quarter_seq = e5->DATE_DIM_D_FY_QUARTER_SEQ;
              long dt_d_fy_week_seq = e5->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE dt_d_day_name = e5->DATE_DIM_D_DAY_NAME;
              STRING_TYPE dt_d_quarter_name = e5->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE dt_d_holiday = e5->DATE_DIM_D_HOLIDAY;
              STRING_TYPE dt_d_weekend = e5->DATE_DIM_D_WEEKEND;
              STRING_TYPE dt_d_following_holiday = e5->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long dt_d_first_dom = e5->DATE_DIM_D_FIRST_DOM;
              long dt_d_last_dom = e5->DATE_DIM_D_LAST_DOM;
              long dt_d_same_day_ly = e5->DATE_DIM_D_SAME_DAY_LY;
              long dt_d_same_day_lq = e5->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE dt_d_current_day = e5->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE dt_d_current_week = e5->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE dt_d_current_month = e5->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE dt_d_current_quarter = e5->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE dt_d_current_year = e5->DATE_DIM_D_CURRENT_YEAR;
              long v5 = e5->__av;
              SUM_AGGSTORE_SALES2.addOrDelOnZero(se9.modify(sum_aggstore_salesstore_sales_ss_sold_date_sk,dt_d_year),v5);
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  DATE_DIM_mapkey8_idxfn::equals(se10, *e5)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    SUM_AGG_entry se1;
    SUM_AGGSTORE_SALES2_entry se2;
    SUM_AGGSTORE_SALES1_entry se3;
    SUM_AGGITEM2_entry se4;
    SUM_AGGSTORE_SALES2_entry se5;
    SUM_AGG_entry se6;
    SUM_AGGITEM2_entry se7;
    SUM_AGGSTORE_SALES1_entry se8;
    SUM_AGGSTORE_SALES2_entry se9;
    DATE_DIM_entry se10;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    SUM_AGGITEM2_map SUM_AGGITEM2;
    SUM_AGGSTORE_SALES1_map SUM_AGGSTORE_SALES1;
    SUM_AGGSTORE_SALES2_map SUM_AGGSTORE_SALES2;
    
    
  
  };

}
