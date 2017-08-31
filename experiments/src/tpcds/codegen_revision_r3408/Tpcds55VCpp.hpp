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
    FORCE_INLINE DATE_DIM_entry& modify68(const long c6, const long c8) { DATE_DIM_D_YEAR = c6; DATE_DIM_D_MOY = c8;  return *this; }
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
  
  struct DATE_DIM_mapkey68_idxfn {
    FORCE_INLINE static size_t hash(const DATE_DIM_entry& e) {
      size_t h = 0;
      hash_combine(h, e.DATE_DIM_D_YEAR);
      hash_combine(h, e.DATE_DIM_D_MOY);
      return h;
    }
    FORCE_INLINE static bool equals(const DATE_DIM_entry& x, const DATE_DIM_entry& y) {
      return x.DATE_DIM_D_YEAR == y.DATE_DIM_D_YEAR && x.DATE_DIM_D_MOY == y.DATE_DIM_D_MOY;
    }
  };
  
  typedef MultiHashMap<DATE_DIM_entry,long,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true>,
    HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey68_idxfn,false>
  > DATE_DIM_map;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey0123456789101112131415161718192021222324252627_idxfn,true> HashIndex_DATE_DIM_map_0123456789101112131415161718192021222324252627;
  typedef HashIndex<DATE_DIM_entry,long,DATE_DIM_mapkey68_idxfn,false> HashIndex_DATE_DIM_map_68;
  
  struct EXT_PRICE_entry {
    long BRAND_ID; STRING_TYPE BRAND; DOUBLE_TYPE __av; 
    explicit EXT_PRICE_entry() { /*BRAND_ID = 0L; BRAND = ""; __av = 0.0; */ }
    explicit EXT_PRICE_entry(const long c0, const STRING_TYPE& c1, const DOUBLE_TYPE c2) { BRAND_ID = c0; BRAND = c1; __av = c2; }
    EXT_PRICE_entry(const EXT_PRICE_entry& other) : BRAND_ID( other.BRAND_ID ), BRAND( other.BRAND ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICE_entry& modify(const long c0, const STRING_TYPE& c1) { BRAND_ID = c0; BRAND = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICE_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.BRAND_ID);
      hash_combine(h, e.BRAND);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICE_entry& x, const EXT_PRICE_entry& y) {
      return x.BRAND_ID == y.BRAND_ID && x.BRAND == y.BRAND;
    }
  };
  
  typedef MultiHashMap<EXT_PRICE_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey01_idxfn,true>
  > EXT_PRICE_map;
  typedef HashIndex<EXT_PRICE_entry,DOUBLE_TYPE,EXT_PRICE_mapkey01_idxfn,true> HashIndex_EXT_PRICE_map_01;
  
  struct EXT_PRICEITEM2_entry {
    long EXT_PRICEITEMITEM_I_ITEM_SK; DOUBLE_TYPE __av; 
    explicit EXT_PRICEITEM2_entry() { /*EXT_PRICEITEMITEM_I_ITEM_SK = 0L; __av = 0.0; */ }
    explicit EXT_PRICEITEM2_entry(const long c0, const DOUBLE_TYPE c1) { EXT_PRICEITEMITEM_I_ITEM_SK = c0; __av = c1; }
    EXT_PRICEITEM2_entry(const EXT_PRICEITEM2_entry& other) : EXT_PRICEITEMITEM_I_ITEM_SK( other.EXT_PRICEITEMITEM_I_ITEM_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICEITEM2_entry& modify(const long c0) { EXT_PRICEITEMITEM_I_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, EXT_PRICEITEMITEM_I_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICEITEM2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICEITEM2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.EXT_PRICEITEMITEM_I_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICEITEM2_entry& x, const EXT_PRICEITEM2_entry& y) {
      return x.EXT_PRICEITEMITEM_I_ITEM_SK == y.EXT_PRICEITEMITEM_I_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICEITEM2_entry,DOUBLE_TYPE,
    HashIndex<EXT_PRICEITEM2_entry,DOUBLE_TYPE,EXT_PRICEITEM2_mapkey0_idxfn,true>
  > EXT_PRICEITEM2_map;
  typedef HashIndex<EXT_PRICEITEM2_entry,DOUBLE_TYPE,EXT_PRICEITEM2_mapkey0_idxfn,true> HashIndex_EXT_PRICEITEM2_map_0;
  
  struct EXT_PRICESTORE_SALES1_entry {
    long EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK; STRING_TYPE BRAND; long BRAND_ID; long __av; 
    explicit EXT_PRICESTORE_SALES1_entry() { /*EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK = 0L; BRAND = ""; BRAND_ID = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES1_entry(const long c0, const STRING_TYPE& c1, const long c2, const long c3) { EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2; __av = c3; }
    EXT_PRICESTORE_SALES1_entry(const EXT_PRICESTORE_SALES1_entry& other) : EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK( other.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK ), BRAND( other.BRAND ), BRAND_ID( other.BRAND_ID ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES1_entry& modify(const long c0, const STRING_TYPE& c1, const long c2) { EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK = c0; BRAND = c1; BRAND_ID = c2;  return *this; }
    FORCE_INLINE EXT_PRICESTORE_SALES1_entry& modify0(const long c0) { EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, BRAND_ID);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK);
      hash_combine(h, e.BRAND);
      hash_combine(h, e.BRAND_ID);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_entry& x, const EXT_PRICESTORE_SALES1_entry& y) {
      return x.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK == y.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK && x.BRAND == y.BRAND && x.BRAND_ID == y.BRAND_ID;
    }
  };
  
  struct EXT_PRICESTORE_SALES1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES1_entry& x, const EXT_PRICESTORE_SALES1_entry& y) {
      return x.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK == y.EXT_PRICESTORE_SALESSTORE_SALES_SS_ITEM_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES1_entry,long,
    HashIndex<EXT_PRICESTORE_SALES1_entry,long,EXT_PRICESTORE_SALES1_mapkey012_idxfn,true>,
    HashIndex<EXT_PRICESTORE_SALES1_entry,long,EXT_PRICESTORE_SALES1_mapkey0_idxfn,false>
  > EXT_PRICESTORE_SALES1_map;
  typedef HashIndex<EXT_PRICESTORE_SALES1_entry,long,EXT_PRICESTORE_SALES1_mapkey012_idxfn,true> HashIndex_EXT_PRICESTORE_SALES1_map_012;
  typedef HashIndex<EXT_PRICESTORE_SALES1_entry,long,EXT_PRICESTORE_SALES1_mapkey0_idxfn,false> HashIndex_EXT_PRICESTORE_SALES1_map_0;
  
  struct EXT_PRICESTORE_SALES2_entry {
    long EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK; long __av; 
    explicit EXT_PRICESTORE_SALES2_entry() { /*EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = 0L; __av = 0L; */ }
    explicit EXT_PRICESTORE_SALES2_entry(const long c0, const long c1) { EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0; __av = c1; }
    EXT_PRICESTORE_SALES2_entry(const EXT_PRICESTORE_SALES2_entry& other) : EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK( other.EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK ), __av( other.__av ) {}
    FORCE_INLINE EXT_PRICESTORE_SALES2_entry& modify(const long c0) { EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct EXT_PRICESTORE_SALES2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const EXT_PRICESTORE_SALES2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK);
      return h;
    }
    FORCE_INLINE static bool equals(const EXT_PRICESTORE_SALES2_entry& x, const EXT_PRICESTORE_SALES2_entry& y) {
      return x.EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK == y.EXT_PRICESTORE_SALESSTORE_SALES_SS_SOLD_DATE_SK;
    }
  };
  
  typedef MultiHashMap<EXT_PRICESTORE_SALES2_entry,long,
    HashIndex<EXT_PRICESTORE_SALES2_entry,long,EXT_PRICESTORE_SALES2_mapkey0_idxfn,true>
  > EXT_PRICESTORE_SALES2_map;
  typedef HashIndex<EXT_PRICESTORE_SALES2_entry,long,EXT_PRICESTORE_SALES2_mapkey0_idxfn,true> HashIndex_EXT_PRICESTORE_SALES2_map_0;
  
  
  
  /* Type definition providing a way to access the results of the sql program */
  struct tlq_t{
    struct timeval t0,t; long tT,tN,tS;
    tlq_t(): tN(0), tS(0) { gettimeofday(&t0,NULL); }
  
  /* Serialization Code */
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const {
  
      ar << "\n";
      const EXT_PRICE_map& _EXT_PRICE = get_EXT_PRICE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(EXT_PRICE), _EXT_PRICE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const EXT_PRICE_map& get_EXT_PRICE() const {
      return EXT_PRICE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    EXT_PRICE_map EXT_PRICE;
  
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
          const HashIndex_EXT_PRICESTORE_SALES1_map_0* i1 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_map_0*>(EXT_PRICESTORE_SALES1.index[1]);
          const HASH_RES_t h1 = EXT_PRICESTORE_SALES1_mapkey0_idxfn::hash(se3.modify0(store_sales_ss_item_sk));
          HashIndex_EXT_PRICESTORE_SALES1_map_0::IdxNode* n1 = static_cast<HashIndex_EXT_PRICESTORE_SALES1_map_0::IdxNode*>(i1->slice(se3, h1));
          EXT_PRICESTORE_SALES1_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              STRING_TYPE brand = e1->BRAND;
              long brand_id = e1->BRAND_ID;
              long v1 = e1->__av;
              EXT_PRICE.addOrDelOnZero(se1.modify(brand_id,brand),(EXT_PRICESTORE_SALES2.getValueOrDefault(se2.modify(store_sales_ss_sold_date_sk)) * (v1 * store_sales_ss_ext_sales_price)));
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h1 == n1->hash &&  EXT_PRICESTORE_SALES1_mapkey0_idxfn::equals(se3, *e1)); 
          }
        }EXT_PRICEITEM2.addOrDelOnZero(se4.modify(store_sales_ss_item_sk),(EXT_PRICESTORE_SALES2.getValueOrDefault(se5.modify(store_sales_ss_sold_date_sk)) * store_sales_ss_ext_sales_price));
      }
    }
    void on_insert_ITEM(const long item_i_item_sk, const STRING_TYPE& item_i_item_id, const date item_i_rec_start_date, const date item_i_rec_end_date, const STRING_TYPE& item_i_item_desc, const DOUBLE_TYPE item_i_current_price, const DOUBLE_TYPE item_i_wholesale_cost, const long item_i_brand_id, const STRING_TYPE& item_i_brand, const long item_i_class_id, const STRING_TYPE& item_i_class, const long item_i_category_id, const STRING_TYPE& item_i_category, const long item_i_manufact_id, const STRING_TYPE& item_i_manufact, const STRING_TYPE& item_i_size, const STRING_TYPE& item_i_formulation, const STRING_TYPE& item_i_color, const STRING_TYPE& item_i_units, const STRING_TYPE& item_i_container, const long item_i_manager_id, const STRING_TYPE& item_i_product_name) {
      {  if (tS>0) { ++tS; return; } if ((tN&127)==0) { gettimeofday(&(t),NULL); tT=((t).tv_sec-(t0).tv_sec)*1000000L+((t).tv_usec-(t0).tv_usec); if (tT>3600000000L) { tS=1; return; } } ++tN;
        (/*if */(item_i_manager_id == 36L) ? EXT_PRICE.addOrDelOnZero(se6.modify(item_i_brand_id,item_i_brand),EXT_PRICEITEM2.getValueOrDefault(se7.modify(item_i_item_sk))) : (void)0);
        (/*if */(item_i_manager_id == 36L) ? EXT_PRICESTORE_SALES1.addOrDelOnZero(se8.modify(item_i_item_sk,item_i_brand,item_i_brand_id),1L) : (void)0);
      }
    }
    void on_system_ready_event() {
      {  
        EXT_PRICESTORE_SALES2.clear();
        long l1 = 2001L;
        long l2 = 12L;
        { //slice 
          const HashIndex_DATE_DIM_map_68* i2 = static_cast<HashIndex_DATE_DIM_map_68*>(DATE_DIM.index[1]);
          const HASH_RES_t h2 = DATE_DIM_mapkey68_idxfn::hash(se10.modify68(l1, l2));
          HashIndex_DATE_DIM_map_68::IdxNode* n2 = static_cast<HashIndex_DATE_DIM_map_68::IdxNode*>(i2->slice(se10, h2));
          DATE_DIM_entry* e2;
         
          if (n2 && (e2 = n2->obj)) {
            do {                
              long ext_pricestore_salesstore_sales_ss_sold_date_sk = e2->DATE_DIM_D_DATE_SK;
              STRING_TYPE date_dim_d_date_id = e2->DATE_DIM_D_DATE_ID;
              date date_dim_d_date = e2->DATE_DIM_D_DATE;
              long date_dim_d_month_seq = e2->DATE_DIM_D_MONTH_SEQ;
              long date_dim_d_week_seq = e2->DATE_DIM_D_WEEK_SEQ;
              long date_dim_d_quarter_seq = e2->DATE_DIM_D_QUARTER_SEQ;
              long date_dim_d_dow = e2->DATE_DIM_D_DOW;
              long date_dim_d_dom = e2->DATE_DIM_D_DOM;
              long date_dim_d_qoy = e2->DATE_DIM_D_QOY;
              long date_dim_d_fy_year = e2->DATE_DIM_D_FY_YEAR;
              long date_dim_d_fy_quarter_seq = e2->DATE_DIM_D_FY_QUARTER_SEQ;
              long date_dim_d_fy_week_seq = e2->DATE_DIM_D_FY_WEEK_SEQ;
              STRING_TYPE date_dim_d_day_name = e2->DATE_DIM_D_DAY_NAME;
              STRING_TYPE date_dim_d_quarter_name = e2->DATE_DIM_D_QUARTER_NAME;
              STRING_TYPE date_dim_d_holiday = e2->DATE_DIM_D_HOLIDAY;
              STRING_TYPE date_dim_d_weekend = e2->DATE_DIM_D_WEEKEND;
              STRING_TYPE date_dim_d_following_holiday = e2->DATE_DIM_D_FOLLOWING_HOLIDAY;
              long date_dim_d_first_dom = e2->DATE_DIM_D_FIRST_DOM;
              long date_dim_d_last_dom = e2->DATE_DIM_D_LAST_DOM;
              long date_dim_d_same_day_ly = e2->DATE_DIM_D_SAME_DAY_LY;
              long date_dim_d_same_day_lq = e2->DATE_DIM_D_SAME_DAY_LQ;
              STRING_TYPE date_dim_d_current_day = e2->DATE_DIM_D_CURRENT_DAY;
              STRING_TYPE date_dim_d_current_week = e2->DATE_DIM_D_CURRENT_WEEK;
              STRING_TYPE date_dim_d_current_month = e2->DATE_DIM_D_CURRENT_MONTH;
              STRING_TYPE date_dim_d_current_quarter = e2->DATE_DIM_D_CURRENT_QUARTER;
              STRING_TYPE date_dim_d_current_year = e2->DATE_DIM_D_CURRENT_YEAR;
              long v2 = e2->__av;
              EXT_PRICESTORE_SALES2.addOrDelOnZero(se9.modify(ext_pricestore_salesstore_sales_ss_sold_date_sk),v2);
              n2 = n2->nxt;
            } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  DATE_DIM_mapkey68_idxfn::equals(se10, *e2)); 
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    EXT_PRICE_entry se1;
    EXT_PRICESTORE_SALES2_entry se2;
    EXT_PRICESTORE_SALES1_entry se3;
    EXT_PRICEITEM2_entry se4;
    EXT_PRICESTORE_SALES2_entry se5;
    EXT_PRICE_entry se6;
    EXT_PRICEITEM2_entry se7;
    EXT_PRICESTORE_SALES1_entry se8;
    EXT_PRICESTORE_SALES2_entry se9;
    DATE_DIM_entry se10;
  
    /* Data structures used for storing materialized views */
    DATE_DIM_map DATE_DIM;
    EXT_PRICEITEM2_map EXT_PRICEITEM2;
    EXT_PRICESTORE_SALES1_map EXT_PRICESTORE_SALES1;
    EXT_PRICESTORE_SALES2_map EXT_PRICESTORE_SALES2;
    
    
  
  };

}
