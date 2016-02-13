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
  struct NATION_entry {
    long NATION_NATIONKEY; STRING_TYPE NATION_NAME; long NATION_REGIONKEY; STRING_TYPE NATION_COMMENT; long __av; 
    explicit NATION_entry() { /*NATION_NATIONKEY = 0L; NATION_NAME = ""; NATION_REGIONKEY = 0L; NATION_COMMENT = ""; __av = 0L; */ }
    explicit NATION_entry(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3, const long c4) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3; __av = c4; }
    NATION_entry(const NATION_entry& other) : NATION_NATIONKEY( other.NATION_NATIONKEY ), NATION_NAME( other.NATION_NAME ), NATION_REGIONKEY( other.NATION_REGIONKEY ), NATION_COMMENT( other.NATION_COMMENT ), __av( other.__av ) {}
    FORCE_INLINE NATION_entry& modify(const long c0, const STRING_TYPE& c1, const long c2, const STRING_TYPE& c3) { NATION_NATIONKEY = c0; NATION_NAME = c1; NATION_REGIONKEY = c2; NATION_COMMENT = c3;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_NAME);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_REGIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, NATION_COMMENT);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct NATION_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const NATION_entry& e) {
      size_t h = 0;
      hash_combine(h, e.NATION_NATIONKEY);
      hash_combine(h, e.NATION_NAME);
      hash_combine(h, e.NATION_REGIONKEY);
      hash_combine(h, e.NATION_COMMENT);
      return h;
    }
    FORCE_INLINE static bool equals(const NATION_entry& x, const NATION_entry& y) {
      return x.NATION_NATIONKEY == y.NATION_NATIONKEY && x.NATION_NAME == y.NATION_NAME && x.NATION_REGIONKEY == y.NATION_REGIONKEY && x.NATION_COMMENT == y.NATION_COMMENT;
    }
  };
  
  typedef MultiHashMap<NATION_entry,long,
    HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true>
  > NATION_map;
  typedef HashIndex<NATION_entry,long,NATION_mapkey0123_idxfn,true> HashIndex_NATION_map_0123;
  
  struct REVENUE_entry {
    STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUE_entry() { /*SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUE_entry(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2, const DOUBLE_TYPE c3) { SHIPPING_SUPP_NATION = c0; SHIPPING_CUST_NATION = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUE_entry(const REVENUE_entry& other) : SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_entry& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, const long c2) { SHIPPING_SUPP_NATION = c0; SHIPPING_CUST_NATION = c1; SHIPPING_L_YEAR = c2;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_entry& e) {
      size_t h = 0;
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_entry& x, const REVENUE_entry& y) {
      return x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  typedef MultiHashMap<REVENUE_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey012_idxfn,true>
  > REVENUE_map;
  typedef HashIndex<REVENUE_entry,DOUBLE_TYPE,REVENUE_mapkey012_idxfn,true> HashIndex_REVENUE_map_012;
  
  struct REVENUE_mCUSTOMER1_entry {
    long REVENUE_mCUSTOMERCUSTOMER_CUSTKEY; long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE SHIPPING_CUST_NATION; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_SUPP_NATION; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER1_entry() { /*REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; SHIPPING_CUST_NATION = ""; SHIPPING_L_YEAR = 0L; SHIPPING_SUPP_NATION = ""; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER1_entry(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_L_YEAR = c3; SHIPPING_SUPP_NATION = c4; __av = c5; }
    REVENUE_mCUSTOMER1_entry(const REVENUE_mCUSTOMER1_entry& other) : REVENUE_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY ), REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const long c3, const STRING_TYPE& c4) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_L_YEAR = c3; SHIPPING_SUPP_NATION = c4;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_entry& modify01(const long c0, const long c1) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_entry& x, const REVENUE_mCUSTOMER1_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY && x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_entry& x, const REVENUE_mCUSTOMER1_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY && x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey01234_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey01_idxfn,false>
  > REVENUE_mCUSTOMER1_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey01234_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_map_01234;
  typedef HashIndex<REVENUE_mCUSTOMER1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mapkey01_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_map_01;
  
  struct REVENUE_mCUSTOMER1_mLINEITEM4_entry {
    long REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY; long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; STRING_TYPE SHIPPING_CUST_NATION; STRING_TYPE SHIPPING_SUPP_NATION; long __av; 
    explicit REVENUE_mCUSTOMER1_mLINEITEM4_entry() { /*REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; SHIPPING_CUST_NATION = ""; SHIPPING_SUPP_NATION = ""; __av = 0L; */ }
    explicit REVENUE_mCUSTOMER1_mLINEITEM4_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3; __av = c4; }
    REVENUE_mCUSTOMER1_mLINEITEM4_entry(const REVENUE_mCUSTOMER1_mLINEITEM4_entry& other) : REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY( other.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY ), REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_mLINEITEM4_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mLINEITEM4_entry& modify0(const long c0) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mLINEITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mLINEITEM4_entry& x, const REVENUE_mCUSTOMER1_mLINEITEM4_entry& y) {
      return x.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY && x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mLINEITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mLINEITEM4_entry& x, const REVENUE_mCUSTOMER1_mLINEITEM4_entry& y) {
      return x.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_mLINEITEM4_entry,long,
    HashIndex<REVENUE_mCUSTOMER1_mLINEITEM4_entry,long,REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0123_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_mLINEITEM4_entry,long,REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn,false>
  > REVENUE_mCUSTOMER1_mLINEITEM4_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_mLINEITEM4_entry,long,REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0123_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0123;
  typedef HashIndex<REVENUE_mCUSTOMER1_mLINEITEM4_entry,long,REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0;
  
  struct REVENUE_mCUSTOMER1_mLINEITEM5_entry {
    long REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY; long REVENUE_mCUSTOMERCUSTOMER_CUSTKEY; long __av; 
    explicit REVENUE_mCUSTOMER1_mLINEITEM5_entry() { /*REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mCUSTOMER1_mLINEITEM5_entry(const long c0, const long c1, const long c2) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1; __av = c2; }
    REVENUE_mCUSTOMER1_mLINEITEM5_entry(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& other) : REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY ), REVENUE_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_mLINEITEM5_entry& modify(const long c0, const long c1) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mLINEITEM5_entry& modify0(const long c0) { REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mLINEITEM5_entry& modify1(const long c1) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mLINEITEM5_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& x, const REVENUE_mCUSTOMER1_mLINEITEM5_entry& y) {
      return x.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY && x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& x, const REVENUE_mCUSTOMER1_mLINEITEM5_entry& y) {
      return x.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mLINEITEM5_entry& x, const REVENUE_mCUSTOMER1_mLINEITEM5_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,
    HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn,false>
  > REVENUE_mCUSTOMER1_mLINEITEM5_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey01_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_01;
  typedef HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0;
  typedef HashIndex<REVENUE_mCUSTOMER1_mLINEITEM5_entry,long,REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1;
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_entry {
    long REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long REVENUE_mCUSTOMERCUSTOMER_CUSTKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER1_mSUPPLIER2_entry() { /*REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER1_mSUPPLIER2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& other) : REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), REVENUE_mCUSTOMERCUSTOMER_CUSTKEY( other.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_entry& modify(const long c0, const long c1, const long c2) { REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0; REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_entry& modify1(const long c1) { REVENUE_mCUSTOMERCUSTOMER_CUSTKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_entry& modify0(const long c0) { REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY == y.REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_entry& y) {
      return x.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn,false>,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn,false>
  > REVENUE_mCUSTOMER1_mSUPPLIER2_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey012_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_012;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0;
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry {
    long REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY; long REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry() { /*REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY = 0L; REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0; REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& other) : REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY( other.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY ), REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& modify(const long c0, const long c1, const long c2) { REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0; REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& modify0(const long c0) { REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& modify1(const long c1) { REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& y) {
      return x.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY == y.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY && x.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& y) {
      return x.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY == y.REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& x, const REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry& y) {
      return x.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey012_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn,false>
  > REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey012_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_012;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0;
  typedef HashIndex<REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1;
  
  struct REVENUE_mCUSTOMER1_mORDERS1_entry {
    long REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY; long REVENUE_mCUSTOMERCUSTOMER_NATIONKEY; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_CUST_NATION; STRING_TYPE SHIPPING_SUPP_NATION; DOUBLE_TYPE __av; 
    explicit REVENUE_mCUSTOMER1_mORDERS1_entry() { /*REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY = 0L; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; SHIPPING_CUST_NATION = ""; SHIPPING_SUPP_NATION = ""; __av = 0.0; */ }
    explicit REVENUE_mCUSTOMER1_mORDERS1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_CUST_NATION = c3; SHIPPING_SUPP_NATION = c4; __av = c5; }
    REVENUE_mCUSTOMER1_mORDERS1_entry(const REVENUE_mCUSTOMER1_mORDERS1_entry& other) : REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY( other.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY ), REVENUE_mCUSTOMERCUSTOMER_NATIONKEY( other.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mCUSTOMER1_mORDERS1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY = c0; REVENUE_mCUSTOMERCUSTOMER_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_CUST_NATION = c3; SHIPPING_SUPP_NATION = c4;  return *this; }
    FORCE_INLINE REVENUE_mCUSTOMER1_mORDERS1_entry& modify0(const long c0) { REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mCUSTOMER1_mORDERS1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mORDERS1_entry& x, const REVENUE_mCUSTOMER1_mORDERS1_entry& y) {
      return x.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY == y.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY && x.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY == y.REVENUE_mCUSTOMERCUSTOMER_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION;
    }
  };
  
  struct REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mCUSTOMER1_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mCUSTOMER1_mORDERS1_entry& x, const REVENUE_mCUSTOMER1_mORDERS1_entry& y) {
      return x.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY == y.REVENUE_mCUSTOMER1_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mCUSTOMER1_mORDERS1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mCUSTOMER1_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mORDERS1_mapkey01234_idxfn,true>,
    HashIndex<REVENUE_mCUSTOMER1_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn,false>
  > REVENUE_mCUSTOMER1_mORDERS1_map;
  typedef HashIndex<REVENUE_mCUSTOMER1_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mORDERS1_mapkey01234_idxfn,true> HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_01234;
  typedef HashIndex<REVENUE_mCUSTOMER1_mORDERS1_entry,DOUBLE_TYPE,REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn,false> HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0;
  
  struct REVENUE_mORDERS1_T_2_entry {
    long S_NATIONKEY; long REVENUE_mORDERSORDERS_ORDERKEY; long SHIPPING_L_YEAR; DOUBLE_TYPE __av; 
    explicit REVENUE_mORDERS1_T_2_entry() { /*S_NATIONKEY = 0L; REVENUE_mORDERSORDERS_ORDERKEY = 0L; SHIPPING_L_YEAR = 0L; __av = 0.0; */ }
    explicit REVENUE_mORDERS1_T_2_entry(const long c0, const long c1, const long c2, const DOUBLE_TYPE c3) { S_NATIONKEY = c0; REVENUE_mORDERSORDERS_ORDERKEY = c1; SHIPPING_L_YEAR = c2; __av = c3; }
    REVENUE_mORDERS1_T_2_entry(const REVENUE_mORDERS1_T_2_entry& other) : S_NATIONKEY( other.S_NATIONKEY ), REVENUE_mORDERSORDERS_ORDERKEY( other.REVENUE_mORDERSORDERS_ORDERKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS1_T_2_entry& modify(const long c0, const long c1, const long c2) { S_NATIONKEY = c0; REVENUE_mORDERSORDERS_ORDERKEY = c1; SHIPPING_L_YEAR = c2;  return *this; }
    FORCE_INLINE REVENUE_mORDERS1_T_2_entry& modify1(const long c1) { REVENUE_mORDERSORDERS_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mORDERSORDERS_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mORDERS1_T_2_mapkey012_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.REVENUE_mORDERSORDERS_ORDERKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_2_entry& x, const REVENUE_mORDERS1_T_2_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY && x.REVENUE_mORDERSORDERS_ORDERKEY == y.REVENUE_mORDERSORDERS_ORDERKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR;
    }
  };
  
  struct REVENUE_mORDERS1_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_2_entry& x, const REVENUE_mORDERS1_T_2_entry& y) {
      return x.REVENUE_mORDERSORDERS_ORDERKEY == y.REVENUE_mORDERSORDERS_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS1_T_2_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mORDERS1_T_2_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_2_mapkey012_idxfn,true>,
    HashIndex<REVENUE_mORDERS1_T_2_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_2_mapkey1_idxfn,false>
  > REVENUE_mORDERS1_T_2_map;
  typedef HashIndex<REVENUE_mORDERS1_T_2_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_2_mapkey012_idxfn,true> HashIndex_REVENUE_mORDERS1_T_2_map_012;
  typedef HashIndex<REVENUE_mORDERS1_T_2_entry,DOUBLE_TYPE,REVENUE_mORDERS1_T_2_mapkey1_idxfn,false> HashIndex_REVENUE_mORDERS1_T_2_map_1;
  
  struct REVENUE_mORDERS1_T_3_entry {
    long REVENUE_mORDERSORDERS_CUSTKEY; long C_NATIONKEY; long __av; 
    explicit REVENUE_mORDERS1_T_3_entry() { /*REVENUE_mORDERSORDERS_CUSTKEY = 0L; C_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mORDERS1_T_3_entry(const long c0, const long c1, const long c2) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1; __av = c2; }
    REVENUE_mORDERS1_T_3_entry(const REVENUE_mORDERS1_T_3_entry& other) : REVENUE_mORDERSORDERS_CUSTKEY( other.REVENUE_mORDERSORDERS_CUSTKEY ), C_NATIONKEY( other.C_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mORDERS1_T_3_entry& modify(const long c0, const long c1) { REVENUE_mORDERSORDERS_CUSTKEY = c0; C_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mORDERS1_T_3_entry& modify0(const long c0) { REVENUE_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mORDERS1_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_3_entry& x, const REVENUE_mORDERS1_T_3_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY && x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUE_mORDERS1_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mORDERS1_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mORDERS1_T_3_entry& x, const REVENUE_mORDERS1_T_3_entry& y) {
      return x.REVENUE_mORDERSORDERS_CUSTKEY == y.REVENUE_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mORDERS1_T_3_entry,long,
    HashIndex<REVENUE_mORDERS1_T_3_entry,long,REVENUE_mORDERS1_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mORDERS1_T_3_entry,long,REVENUE_mORDERS1_T_3_mapkey0_idxfn,false>
  > REVENUE_mORDERS1_T_3_map;
  typedef HashIndex<REVENUE_mORDERS1_T_3_entry,long,REVENUE_mORDERS1_T_3_mapkey01_idxfn,true> HashIndex_REVENUE_mORDERS1_T_3_map_01;
  typedef HashIndex<REVENUE_mORDERS1_T_3_entry,long,REVENUE_mORDERS1_T_3_mapkey0_idxfn,false> HashIndex_REVENUE_mORDERS1_T_3_map_0;
  
  struct REVENUE_mLINEITEM4_T_1_entry {
    long C_NATIONKEY; long S_NATIONKEY; STRING_TYPE SHIPPING_CUST_NATION; STRING_TYPE SHIPPING_SUPP_NATION; long __av; 
    explicit REVENUE_mLINEITEM4_T_1_entry() { /*C_NATIONKEY = 0L; S_NATIONKEY = 0L; SHIPPING_CUST_NATION = ""; SHIPPING_SUPP_NATION = ""; __av = 0L; */ }
    explicit REVENUE_mLINEITEM4_T_1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { C_NATIONKEY = c0; S_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3; __av = c4; }
    REVENUE_mLINEITEM4_T_1_entry(const REVENUE_mLINEITEM4_T_1_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), S_NATIONKEY( other.S_NATIONKEY ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM4_T_1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { C_NATIONKEY = c0; S_NATIONKEY = c1; SHIPPING_CUST_NATION = c2; SHIPPING_SUPP_NATION = c3;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM4_T_1_entry& modify01(const long c0, const long c1) { C_NATIONKEY = c0; S_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM4_T_1_entry& modify0(const long c0) { C_NATIONKEY = c0;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM4_T_1_entry& modify1(const long c1) { S_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM4_T_1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.S_NATIONKEY);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_1_entry& x, const REVENUE_mLINEITEM4_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.S_NATIONKEY == y.S_NATIONKEY && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION;
    }
  };
  
  struct REVENUE_mLINEITEM4_T_1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_1_entry& x, const REVENUE_mLINEITEM4_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  struct REVENUE_mLINEITEM4_T_1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_1_entry& x, const REVENUE_mLINEITEM4_T_1_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY;
    }
  };
  
  struct REVENUE_mLINEITEM4_T_1_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_1_entry& x, const REVENUE_mLINEITEM4_T_1_entry& y) {
      return x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM4_T_1_entry,long,
    HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey0123_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey01_idxfn,false>,
    HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey0_idxfn,false>,
    HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey1_idxfn,false>
  > REVENUE_mLINEITEM4_T_1_map;
  typedef HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey0123_idxfn,true> HashIndex_REVENUE_mLINEITEM4_T_1_map_0123;
  typedef HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey01_idxfn,false> HashIndex_REVENUE_mLINEITEM4_T_1_map_01;
  typedef HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM4_T_1_map_0;
  typedef HashIndex<REVENUE_mLINEITEM4_T_1_entry,long,REVENUE_mLINEITEM4_T_1_mapkey1_idxfn,false> HashIndex_REVENUE_mLINEITEM4_T_1_map_1;
  
  struct REVENUE_mLINEITEM4_T_2_entry {
    long C_NATIONKEY; long REVENUE_mLINEITEMLINEITEM_ORDERKEY; long __av; 
    explicit REVENUE_mLINEITEM4_T_2_entry() { /*C_NATIONKEY = 0L; REVENUE_mLINEITEMLINEITEM_ORDERKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mLINEITEM4_T_2_entry(const long c0, const long c1, const long c2) { C_NATIONKEY = c0; REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1; __av = c2; }
    REVENUE_mLINEITEM4_T_2_entry(const REVENUE_mLINEITEM4_T_2_entry& other) : C_NATIONKEY( other.C_NATIONKEY ), REVENUE_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mLINEITEMLINEITEM_ORDERKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM4_T_2_entry& modify(const long c0, const long c1) { C_NATIONKEY = c0; REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM4_T_2_entry& modify1(const long c1) { REVENUE_mLINEITEMLINEITEM_ORDERKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, C_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM4_T_2_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.C_NATIONKEY);
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_2_entry& x, const REVENUE_mLINEITEM4_T_2_entry& y) {
      return x.C_NATIONKEY == y.C_NATIONKEY && x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  struct REVENUE_mLINEITEM4_T_2_mapkey1_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_2_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_2_entry& x, const REVENUE_mLINEITEM4_T_2_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM4_T_2_entry,long,
    HashIndex<REVENUE_mLINEITEM4_T_2_entry,long,REVENUE_mLINEITEM4_T_2_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM4_T_2_entry,long,REVENUE_mLINEITEM4_T_2_mapkey1_idxfn,false>
  > REVENUE_mLINEITEM4_T_2_map;
  typedef HashIndex<REVENUE_mLINEITEM4_T_2_entry,long,REVENUE_mLINEITEM4_T_2_mapkey01_idxfn,true> HashIndex_REVENUE_mLINEITEM4_T_2_map_01;
  typedef HashIndex<REVENUE_mLINEITEM4_T_2_entry,long,REVENUE_mLINEITEM4_T_2_mapkey1_idxfn,false> HashIndex_REVENUE_mLINEITEM4_T_2_map_1;
  
  struct REVENUE_mLINEITEM4_T_3_entry {
    long REVENUE_mLINEITEMLINEITEM_SUPPKEY; long S_NATIONKEY; long __av; 
    explicit REVENUE_mLINEITEM4_T_3_entry() { /*REVENUE_mLINEITEMLINEITEM_SUPPKEY = 0L; S_NATIONKEY = 0L; __av = 0L; */ }
    explicit REVENUE_mLINEITEM4_T_3_entry(const long c0, const long c1, const long c2) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0; S_NATIONKEY = c1; __av = c2; }
    REVENUE_mLINEITEM4_T_3_entry(const REVENUE_mLINEITEM4_T_3_entry& other) : REVENUE_mLINEITEMLINEITEM_SUPPKEY( other.REVENUE_mLINEITEMLINEITEM_SUPPKEY ), S_NATIONKEY( other.S_NATIONKEY ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mLINEITEM4_T_3_entry& modify(const long c0, const long c1) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0; S_NATIONKEY = c1;  return *this; }
    FORCE_INLINE REVENUE_mLINEITEM4_T_3_entry& modify0(const long c0) { REVENUE_mLINEITEMLINEITEM_SUPPKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, S_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mLINEITEM4_T_3_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      hash_combine(h, e.S_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_3_entry& x, const REVENUE_mLINEITEM4_T_3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mLINEITEMLINEITEM_SUPPKEY && x.S_NATIONKEY == y.S_NATIONKEY;
    }
  };
  
  struct REVENUE_mLINEITEM4_T_3_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mLINEITEM4_T_3_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mLINEITEMLINEITEM_SUPPKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mLINEITEM4_T_3_entry& x, const REVENUE_mLINEITEM4_T_3_entry& y) {
      return x.REVENUE_mLINEITEMLINEITEM_SUPPKEY == y.REVENUE_mLINEITEMLINEITEM_SUPPKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mLINEITEM4_T_3_entry,long,
    HashIndex<REVENUE_mLINEITEM4_T_3_entry,long,REVENUE_mLINEITEM4_T_3_mapkey01_idxfn,true>,
    HashIndex<REVENUE_mLINEITEM4_T_3_entry,long,REVENUE_mLINEITEM4_T_3_mapkey0_idxfn,false>
  > REVENUE_mLINEITEM4_T_3_map;
  typedef HashIndex<REVENUE_mLINEITEM4_T_3_entry,long,REVENUE_mLINEITEM4_T_3_mapkey01_idxfn,true> HashIndex_REVENUE_mLINEITEM4_T_3_map_01;
  typedef HashIndex<REVENUE_mLINEITEM4_T_3_entry,long,REVENUE_mLINEITEM4_T_3_mapkey0_idxfn,false> HashIndex_REVENUE_mLINEITEM4_T_3_map_0;
  
  struct REVENUE_mSUPPLIER1_entry {
    long REVENUE_mSUPPLIERSUPPLIER_SUPPKEY; long REVENUE_mSUPPLIERSUPPLIER_NATIONKEY; long SHIPPING_L_YEAR; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; DOUBLE_TYPE __av; 
    explicit REVENUE_mSUPPLIER1_entry() { /*REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = 0L; SHIPPING_L_YEAR = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0.0; */ }
    explicit REVENUE_mSUPPLIER1_entry(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4, const DOUBLE_TYPE c5) { REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4; __av = c5; }
    REVENUE_mSUPPLIER1_entry(const REVENUE_mSUPPLIER1_entry& other) : REVENUE_mSUPPLIERSUPPLIER_SUPPKEY( other.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY ), REVENUE_mSUPPLIERSUPPLIER_NATIONKEY( other.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY ), SHIPPING_L_YEAR( other.SHIPPING_L_YEAR ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER1_entry& modify(const long c0, const long c1, const long c2, const STRING_TYPE& c3, const STRING_TYPE& c4) { REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_L_YEAR = c2; SHIPPING_SUPP_NATION = c3; SHIPPING_CUST_NATION = c4;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER1_entry& modify01(const long c0, const long c1) { REVENUE_mSUPPLIERSUPPLIER_SUPPKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_L_YEAR);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER1_mapkey01234_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.SHIPPING_L_YEAR);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_entry& x, const REVENUE_mSUPPLIER1_entry& y) {
      return x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY && x.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY == y.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY && x.SHIPPING_L_YEAR == y.SHIPPING_L_YEAR && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUE_mSUPPLIER1_mapkey01_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_entry& x, const REVENUE_mSUPPLIER1_entry& y) {
      return x.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY == y.REVENUE_mSUPPLIERSUPPLIER_SUPPKEY && x.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY == y.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER1_entry,DOUBLE_TYPE,
    HashIndex<REVENUE_mSUPPLIER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER1_mapkey01234_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER1_mapkey01_idxfn,false>
  > REVENUE_mSUPPLIER1_map;
  typedef HashIndex<REVENUE_mSUPPLIER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER1_mapkey01234_idxfn,true> HashIndex_REVENUE_mSUPPLIER1_map_01234;
  typedef HashIndex<REVENUE_mSUPPLIER1_entry,DOUBLE_TYPE,REVENUE_mSUPPLIER1_mapkey01_idxfn,false> HashIndex_REVENUE_mSUPPLIER1_map_01;
  
  struct REVENUE_mSUPPLIER1_mORDERS1_entry {
    long REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY; long REVENUE_mSUPPLIERSUPPLIER_NATIONKEY; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long __av; 
    explicit REVENUE_mSUPPLIER1_mORDERS1_entry() { /*REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0L; */ }
    explicit REVENUE_mSUPPLIER1_mORDERS1_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3; __av = c4; }
    REVENUE_mSUPPLIER1_mORDERS1_entry(const REVENUE_mSUPPLIER1_mORDERS1_entry& other) : REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY( other.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY ), REVENUE_mSUPPLIERSUPPLIER_NATIONKEY( other.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER1_mORDERS1_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER1_mORDERS1_entry& modify0(const long c0) { REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER1_mORDERS1_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_mORDERS1_entry& x, const REVENUE_mSUPPLIER1_mORDERS1_entry& y) {
      return x.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY == y.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY && x.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY == y.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_mORDERS1_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_mORDERS1_entry& x, const REVENUE_mSUPPLIER1_mORDERS1_entry& y) {
      return x.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY == y.REVENUE_mSUPPLIER1_mORDERSORDERS_CUSTKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER1_mORDERS1_entry,long,
    HashIndex<REVENUE_mSUPPLIER1_mORDERS1_entry,long,REVENUE_mSUPPLIER1_mORDERS1_mapkey0123_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER1_mORDERS1_entry,long,REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn,false>
  > REVENUE_mSUPPLIER1_mORDERS1_map;
  typedef HashIndex<REVENUE_mSUPPLIER1_mORDERS1_entry,long,REVENUE_mSUPPLIER1_mORDERS1_mapkey0123_idxfn,true> HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0123;
  typedef HashIndex<REVENUE_mSUPPLIER1_mORDERS1_entry,long,REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn,false> HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0;
  
  struct REVENUE_mSUPPLIER1_mLINEITEM4_entry {
    long REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY; long REVENUE_mSUPPLIERSUPPLIER_NATIONKEY; STRING_TYPE SHIPPING_SUPP_NATION; STRING_TYPE SHIPPING_CUST_NATION; long __av; 
    explicit REVENUE_mSUPPLIER1_mLINEITEM4_entry() { /*REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY = 0L; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = 0L; SHIPPING_SUPP_NATION = ""; SHIPPING_CUST_NATION = ""; __av = 0L; */ }
    explicit REVENUE_mSUPPLIER1_mLINEITEM4_entry(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3, const long c4) { REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3; __av = c4; }
    REVENUE_mSUPPLIER1_mLINEITEM4_entry(const REVENUE_mSUPPLIER1_mLINEITEM4_entry& other) : REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY( other.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY ), REVENUE_mSUPPLIERSUPPLIER_NATIONKEY( other.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY ), SHIPPING_SUPP_NATION( other.SHIPPING_SUPP_NATION ), SHIPPING_CUST_NATION( other.SHIPPING_CUST_NATION ), __av( other.__av ) {}
    FORCE_INLINE REVENUE_mSUPPLIER1_mLINEITEM4_entry& modify(const long c0, const long c1, const STRING_TYPE& c2, const STRING_TYPE& c3) { REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY = c0; REVENUE_mSUPPLIERSUPPLIER_NATIONKEY = c1; SHIPPING_SUPP_NATION = c2; SHIPPING_CUST_NATION = c3;  return *this; }
    FORCE_INLINE REVENUE_mSUPPLIER1_mLINEITEM4_entry& modify0(const long c0) { REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY = c0;  return *this; }
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) const 
    {
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_SUPP_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, SHIPPING_CUST_NATION);
      ar << ELEM_SEPARATOR;
      DBT_SERIALIZATION_NVP(ar, __av);
    }
  };
  struct REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0123_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_mLINEITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY);
      hash_combine(h, e.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY);
      hash_combine(h, e.SHIPPING_SUPP_NATION);
      hash_combine(h, e.SHIPPING_CUST_NATION);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_mLINEITEM4_entry& x, const REVENUE_mSUPPLIER1_mLINEITEM4_entry& y) {
      return x.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY && x.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY == y.REVENUE_mSUPPLIERSUPPLIER_NATIONKEY && x.SHIPPING_SUPP_NATION == y.SHIPPING_SUPP_NATION && x.SHIPPING_CUST_NATION == y.SHIPPING_CUST_NATION;
    }
  };
  
  struct REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn {
    FORCE_INLINE static size_t hash(const REVENUE_mSUPPLIER1_mLINEITEM4_entry& e) {
      size_t h = 0;
      hash_combine(h, e.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY);
      return h;
    }
    FORCE_INLINE static bool equals(const REVENUE_mSUPPLIER1_mLINEITEM4_entry& x, const REVENUE_mSUPPLIER1_mLINEITEM4_entry& y) {
      return x.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY == y.REVENUE_mSUPPLIER1_mLINEITEMLINEITEM_ORDERKEY;
    }
  };
  
  typedef MultiHashMap<REVENUE_mSUPPLIER1_mLINEITEM4_entry,long,
    HashIndex<REVENUE_mSUPPLIER1_mLINEITEM4_entry,long,REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0123_idxfn,true>,
    HashIndex<REVENUE_mSUPPLIER1_mLINEITEM4_entry,long,REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn,false>
  > REVENUE_mSUPPLIER1_mLINEITEM4_map;
  typedef HashIndex<REVENUE_mSUPPLIER1_mLINEITEM4_entry,long,REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0123_idxfn,true> HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0123;
  typedef HashIndex<REVENUE_mSUPPLIER1_mLINEITEM4_entry,long,REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn,false> HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0;
  
  struct tuple3_SS_L {
    STRING_TYPE _1; STRING_TYPE _2; long __av;
    explicit tuple3_SS_L() { }
    explicit tuple3_SS_L(const STRING_TYPE& c1, const STRING_TYPE& c2, long c__av=0L) { _1 = c1; _2 = c2; __av = c__av;}
    int operator==(const tuple3_SS_L &rhs) const { return ((this->_1==rhs._1) && (this->_2==rhs._2)); }
    FORCE_INLINE tuple3_SS_L& modify(const STRING_TYPE& c0, const STRING_TYPE& c1, long c__av) { _1 = c0; _2 = c1; __av = c__av; return *this; }
    static bool equals(const tuple3_SS_L &x, const tuple3_SS_L &y) { return ((x._1==y._1) && (x._2==y._2)); }
    static long hash(const tuple3_SS_L &e) {
      size_t h = 0;
      hash_combine(h, e._1);
      hash_combine(h, e._2);
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
      const REVENUE_map& _REVENUE = get_REVENUE();
      dbtoaster::serialize_nvp_tabbed(ar, STRING_TYPE(REVENUE), _REVENUE, "\t");
  
    }
  
    /* Functions returning / computing the results of top level queries */
    const REVENUE_map& get_REVENUE() const {
      return REVENUE;
    
    }
  
  protected:
  
    /* Data structures used for storing / computing top level queries */
    REVENUE_map REVENUE;
  
  };
  
  /* Type definition providing a way to incrementally maintain the results of the sql program */
  struct data_t : tlq_t{
    data_t(): tlq_t(), agg2(16U), agg1(16U) {
      c1 = Udate(STRING_TYPE("1996-12-31"));
      c3 = STRING_TYPE("FRANCE");
      c2 = Udate(STRING_TYPE("1995-1-1"));
      c4 = STRING_TYPE("GERMANY");
    }
  
  
    /* Trigger functions for table relations */
    void on_insert_NATION(const long nation_nationkey, const STRING_TYPE nation_name, const long nation_regionkey, const STRING_TYPE nation_comment) {
      NATION_entry e(nation_nationkey, nation_name, nation_regionkey, nation_comment, 1L);
      NATION.addOrDelOnZero(e,1L);
    }
    
    
    
    /* Trigger functions for stream relations */
    void on_insert_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        long l1 = Uyear_part(lineitem_shipdate);
        agg1.clear();
        
        { //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_3_map_0* i1 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0*>(REVENUE_mLINEITEM4_T_3.index[1]);
          const HASH_RES_t h3 = REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::hash(se4.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode* n1 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode*>(i1->slice(se4, h3));
          REVENUE_mLINEITEM4_T_3_entry* e1;
         
          if (n1 && (e1 = n1->obj)) {
            do {                
              long s_nationkey = e1->S_NATIONKEY;
              long v1 = e1->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_2_map_1* i2 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_2_map_1*>(REVENUE_mLINEITEM4_T_2.index[1]);
                const HASH_RES_t h2 = REVENUE_mLINEITEM4_T_2_mapkey1_idxfn::hash(se3.modify1(lineitem_orderkey));
                HashIndex_REVENUE_mLINEITEM4_T_2_map_1::IdxNode* n2 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_2_map_1::IdxNode*>(i2->slice(se3, h2));
                REVENUE_mLINEITEM4_T_2_entry* e2;
               
                if (n2 && (e2 = n2->obj)) {
                  do {                
                    long c_nationkey = e2->C_NATIONKEY;
                    long v2 = e2->__av;
                    { //slice 
                      const HashIndex_REVENUE_mLINEITEM4_T_1_map_01* i3 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01*>(REVENUE_mLINEITEM4_T_1.index[1]);
                      const HASH_RES_t h1 = REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::hash(se2.modify01(c_nationkey, s_nationkey));
                      HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode* n3 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode*>(i3->slice(se2, h1));
                      REVENUE_mLINEITEM4_T_1_entry* e3;
                     
                      if (n3 && (e3 = n3->obj)) {
                        do {                
                          STRING_TYPE shipping_cust_nation = e3->SHIPPING_CUST_NATION;
                          STRING_TYPE shipping_supp_nation = e3->SHIPPING_SUPP_NATION;
                          long v3 = e3->__av;
                          agg1.addOrDelOnZero(st1.modify(shipping_cust_nation,shipping_supp_nation,(v1 * (v2 * v3))), (v1 * (v2 * v3)));
                          n3 = n3->nxt;
                        } while (n3 && (e3 = n3->obj) && h1 == n3->hash &&  REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::equals(se2, *e3)); 
                      }
                    }
                    n2 = n2->nxt;
                  } while (n2 && (e2 = n2->obj) && h2 == n2->hash &&  REVENUE_mLINEITEM4_T_2_mapkey1_idxfn::equals(se3, *e2)); 
                }
              }
              n1 = n1->nxt;
            } while (n1 && (e1 = n1->obj) && h3 == n1->hash &&  REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::equals(se4, *e1)); 
          }
        }{  // temp foreach
          const HashIndex<tuple3_SS_L, long>* i4 = static_cast<HashIndex<tuple3_SS_L, long>*>(agg1.index[0]);
          HashIndex<tuple3_SS_L, long>::IdxNode* n4; 
          tuple3_SS_L* e4;
        
          for (size_t i = 0; i < i4->size_; i++)
          {
            n4 = i4->buckets_ + i;
            while (n4 && (e4 = n4->obj))
            {
              STRING_TYPE shipping_cust_nation = e4->_1;
              STRING_TYPE shipping_supp_nation = e4->_2;  
              long v4 = e4->__av; 
            (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE.addOrDelOnZero(se1.modify(shipping_supp_nation,shipping_cust_nation,l1),(v4 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);      
              n4 = n4->nxt;
            }
          }
        }long l2 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0* i5 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[1]);
          const HASH_RES_t h5 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::hash(se7.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode* n5 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode*>(i5->slice(se7, h5));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e5;
         
          if (n5 && (e5 = n5->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e5->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
              long v5 = e5->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0* i6 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM4.index[1]);
                const HASH_RES_t h4 = REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::hash(se6.modify0(lineitem_suppkey));
                HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode* n6 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode*>(i6->slice(se6, h4));
                REVENUE_mCUSTOMER1_mLINEITEM4_entry* e6;
               
                if (n6 && (e6 = n6->obj)) {
                  do {                
                    long revenue_mcustomercustomer_nationkey = e6->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e6->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e6->SHIPPING_SUPP_NATION;
                    long v6 = e6->__av;
                    (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se5.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,l2,shipping_supp_nation),(v5 * (v6 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
                    n6 = n6->nxt;
                  } while (n6 && (e6 = n6->obj) && h4 == n6->hash &&  REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::equals(se6, *e6)); 
                }
              }
              n5 = n5->nxt;
            } while (n5 && (e5 = n5->obj) && h5 == n5->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::equals(se7, *e5)); 
          }
        }long l3 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0* i7 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[1]);
          const HASH_RES_t h6 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::hash(se9.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode* n7 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode*>(i7->slice(se9, h6));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e7;
         
          if (n7 && (e7 = n7->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e7->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
              long v7 = e7->__av;
              (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se8.modify(lineitem_suppkey,revenue_mcustomercustomer_custkey,l3),(v7 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n7 = n7->nxt;
            } while (n7 && (e7 = n7->obj) && h6 == n7->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::equals(se9, *e7)); 
          }
        }long l4 = Uyear_part(lineitem_shipdate);
        (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.addOrDelOnZero(se10.modify(lineitem_orderkey,lineitem_suppkey,l4),(lineitem_extendedprice * (1L + (-1L * lineitem_discount)))) : (void)0);
        long l5 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0* i8 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM4.index[1]);
          const HASH_RES_t h7 = REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::hash(se12.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode* n8 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode*>(i8->slice(se12, h7));
          REVENUE_mCUSTOMER1_mLINEITEM4_entry* e8;
         
          if (n8 && (e8 = n8->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e8->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e8->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e8->SHIPPING_SUPP_NATION;
              long v8 = e8->__av;
              (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mCUSTOMER1_mORDERS1.addOrDelOnZero(se11.modify(lineitem_orderkey,revenue_mcustomercustomer_nationkey,l5,shipping_cust_nation,shipping_supp_nation),(v8 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n8 = n8->nxt;
            } while (n8 && (e8 = n8->obj) && h7 == n8->hash &&  REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::equals(se12, *e8)); 
          }
        }long l6 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_3_map_0* i9 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0*>(REVENUE_mLINEITEM4_T_3.index[1]);
          const HASH_RES_t h8 = REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::hash(se14.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode* n9 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode*>(i9->slice(se14, h8));
          REVENUE_mLINEITEM4_T_3_entry* e9;
         
          if (n9 && (e9 = n9->obj)) {
            do {                
              long s_nationkey = e9->S_NATIONKEY;
              long v9 = e9->__av;
              (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mORDERS1_T_2.addOrDelOnZero(se13.modify(s_nationkey,lineitem_orderkey,l6),(v9 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n9 = n9->nxt;
            } while (n9 && (e9 = n9->obj) && h8 == n9->hash &&  REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::equals(se14, *e9)); 
          }
        }long l7 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0* i10 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0*>(REVENUE_mSUPPLIER1_mLINEITEM4.index[1]);
          const HASH_RES_t h9 = REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn::hash(se16.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0::IdxNode* n10 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0::IdxNode*>(i10->slice(se16, h9));
          REVENUE_mSUPPLIER1_mLINEITEM4_entry* e10;
         
          if (n10 && (e10 = n10->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e10->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
              STRING_TYPE shipping_supp_nation = e10->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e10->SHIPPING_CUST_NATION;
              long v10 = e10->__av;
              (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mSUPPLIER1.addOrDelOnZero(se15.modify(lineitem_suppkey,revenue_msuppliersupplier_nationkey,l7,shipping_supp_nation,shipping_cust_nation),(v10 * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
              n10 = n10->nxt;
            } while (n10 && (e10 = n10->obj) && h9 == n10->hash &&  REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn::equals(se16, *e10)); 
          }
        }
      }
    }
    void on_delete_LINEITEM(const long lineitem_orderkey, const long lineitem_partkey, const long lineitem_suppkey, const long lineitem_linenumber, const DOUBLE_TYPE lineitem_quantity, const DOUBLE_TYPE lineitem_extendedprice, const DOUBLE_TYPE lineitem_discount, const DOUBLE_TYPE lineitem_tax, const STRING_TYPE& lineitem_returnflag, const STRING_TYPE& lineitem_linestatus, const date lineitem_shipdate, const date lineitem_commitdate, const date lineitem_receiptdate, const STRING_TYPE& lineitem_shipinstruct, const STRING_TYPE& lineitem_shipmode, const STRING_TYPE& lineitem_comment) {
      {  //++tN;
        long l8 = Uyear_part(lineitem_shipdate);
        agg2.clear();
        
        { //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_3_map_0* i11 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0*>(REVENUE_mLINEITEM4_T_3.index[1]);
          const HASH_RES_t h12 = REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::hash(se20.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode* n11 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode*>(i11->slice(se20, h12));
          REVENUE_mLINEITEM4_T_3_entry* e11;
         
          if (n11 && (e11 = n11->obj)) {
            do {                
              long s_nationkey = e11->S_NATIONKEY;
              long v11 = e11->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_2_map_1* i12 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_2_map_1*>(REVENUE_mLINEITEM4_T_2.index[1]);
                const HASH_RES_t h11 = REVENUE_mLINEITEM4_T_2_mapkey1_idxfn::hash(se19.modify1(lineitem_orderkey));
                HashIndex_REVENUE_mLINEITEM4_T_2_map_1::IdxNode* n12 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_2_map_1::IdxNode*>(i12->slice(se19, h11));
                REVENUE_mLINEITEM4_T_2_entry* e12;
               
                if (n12 && (e12 = n12->obj)) {
                  do {                
                    long c_nationkey = e12->C_NATIONKEY;
                    long v12 = e12->__av;
                    { //slice 
                      const HashIndex_REVENUE_mLINEITEM4_T_1_map_01* i13 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01*>(REVENUE_mLINEITEM4_T_1.index[1]);
                      const HASH_RES_t h10 = REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::hash(se18.modify01(c_nationkey, s_nationkey));
                      HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode* n13 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode*>(i13->slice(se18, h10));
                      REVENUE_mLINEITEM4_T_1_entry* e13;
                     
                      if (n13 && (e13 = n13->obj)) {
                        do {                
                          STRING_TYPE shipping_cust_nation = e13->SHIPPING_CUST_NATION;
                          STRING_TYPE shipping_supp_nation = e13->SHIPPING_SUPP_NATION;
                          long v13 = e13->__av;
                          agg2.addOrDelOnZero(st2.modify(shipping_cust_nation,shipping_supp_nation,(v11 * (v12 * v13))), (v11 * (v12 * v13)));
                          n13 = n13->nxt;
                        } while (n13 && (e13 = n13->obj) && h10 == n13->hash &&  REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::equals(se18, *e13)); 
                      }
                    }
                    n12 = n12->nxt;
                  } while (n12 && (e12 = n12->obj) && h11 == n12->hash &&  REVENUE_mLINEITEM4_T_2_mapkey1_idxfn::equals(se19, *e12)); 
                }
              }
              n11 = n11->nxt;
            } while (n11 && (e11 = n11->obj) && h12 == n11->hash &&  REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::equals(se20, *e11)); 
          }
        }{  // temp foreach
          const HashIndex<tuple3_SS_L, long>* i14 = static_cast<HashIndex<tuple3_SS_L, long>*>(agg2.index[0]);
          HashIndex<tuple3_SS_L, long>::IdxNode* n14; 
          tuple3_SS_L* e14;
        
          for (size_t i = 0; i < i14->size_; i++)
          {
            n14 = i14->buckets_ + i;
            while (n14 && (e14 = n14->obj))
            {
              STRING_TYPE shipping_cust_nation = e14->_1;
              STRING_TYPE shipping_supp_nation = e14->_2;  
              long v14 = e14->__av; 
            (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE.addOrDelOnZero(se17.modify(shipping_supp_nation,shipping_cust_nation,l8),(v14 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);      
              n14 = n14->nxt;
            }
          }
        }long l9 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0* i15 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM4.index[1]);
          const HASH_RES_t h14 = REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::hash(se23.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode* n15 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode*>(i15->slice(se23, h14));
          REVENUE_mCUSTOMER1_mLINEITEM4_entry* e15;
         
          if (n15 && (e15 = n15->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e15->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e15->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e15->SHIPPING_SUPP_NATION;
              long v15 = e15->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0* i16 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[1]);
                const HASH_RES_t h13 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::hash(se22.modify0(lineitem_orderkey));
                HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode* n16 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode*>(i16->slice(se22, h13));
                REVENUE_mCUSTOMER1_mLINEITEM5_entry* e16;
               
                if (n16 && (e16 = n16->obj)) {
                  do {                
                    long revenue_mcustomercustomer_custkey = e16->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
                    long v16 = e16->__av;
                    (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mCUSTOMER1.addOrDelOnZero(se21.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,l9,shipping_supp_nation),(v15 * (v16 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))))) : (void)0);
                    n16 = n16->nxt;
                  } while (n16 && (e16 = n16->obj) && h13 == n16->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::equals(se22, *e16)); 
                }
              }
              n15 = n15->nxt;
            } while (n15 && (e15 = n15->obj) && h14 == n15->hash &&  REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::equals(se23, *e15)); 
          }
        }long l10 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0* i17 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[1]);
          const HASH_RES_t h15 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::hash(se25.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode* n17 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_0::IdxNode*>(i17->slice(se25, h15));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e17;
         
          if (n17 && (e17 = n17->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e17->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
              long v17 = e17->__av;
              (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se24.modify(lineitem_suppkey,revenue_mcustomercustomer_custkey,l10),(v17 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n17 = n17->nxt;
            } while (n17 && (e17 = n17->obj) && h15 == n17->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey0_idxfn::equals(se25, *e17)); 
          }
        }long l11 = Uyear_part(lineitem_shipdate);
        (/*if */(lineitem_shipdate >= c2 && c1 >= lineitem_shipdate) ? REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.addOrDelOnZero(se26.modify(lineitem_orderkey,lineitem_suppkey,l11),(-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount))))) : (void)0);
        long l12 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0* i18 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0*>(REVENUE_mCUSTOMER1_mLINEITEM4.index[1]);
          const HASH_RES_t h16 = REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::hash(se28.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode* n18 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM4_map_0::IdxNode*>(i18->slice(se28, h16));
          REVENUE_mCUSTOMER1_mLINEITEM4_entry* e18;
         
          if (n18 && (e18 = n18->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e18->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e18->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e18->SHIPPING_SUPP_NATION;
              long v18 = e18->__av;
              (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE_mCUSTOMER1_mORDERS1.addOrDelOnZero(se27.modify(lineitem_orderkey,revenue_mcustomercustomer_nationkey,l12,shipping_cust_nation,shipping_supp_nation),(v18 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n18 = n18->nxt;
            } while (n18 && (e18 = n18->obj) && h16 == n18->hash &&  REVENUE_mCUSTOMER1_mLINEITEM4_mapkey0_idxfn::equals(se28, *e18)); 
          }
        }long l13 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_3_map_0* i19 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0*>(REVENUE_mLINEITEM4_T_3.index[1]);
          const HASH_RES_t h17 = REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::hash(se30.modify0(lineitem_suppkey));
          HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode* n19 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_3_map_0::IdxNode*>(i19->slice(se30, h17));
          REVENUE_mLINEITEM4_T_3_entry* e19;
         
          if (n19 && (e19 = n19->obj)) {
            do {                
              long s_nationkey = e19->S_NATIONKEY;
              long v19 = e19->__av;
              (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE_mORDERS1_T_2.addOrDelOnZero(se29.modify(s_nationkey,lineitem_orderkey,l13),(v19 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n19 = n19->nxt;
            } while (n19 && (e19 = n19->obj) && h17 == n19->hash &&  REVENUE_mLINEITEM4_T_3_mapkey0_idxfn::equals(se30, *e19)); 
          }
        }long l14 = Uyear_part(lineitem_shipdate);
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0* i20 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0*>(REVENUE_mSUPPLIER1_mLINEITEM4.index[1]);
          const HASH_RES_t h18 = REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn::hash(se32.modify0(lineitem_orderkey));
          HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0::IdxNode* n20 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mLINEITEM4_map_0::IdxNode*>(i20->slice(se32, h18));
          REVENUE_mSUPPLIER1_mLINEITEM4_entry* e20;
         
          if (n20 && (e20 = n20->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e20->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
              STRING_TYPE shipping_supp_nation = e20->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e20->SHIPPING_CUST_NATION;
              long v20 = e20->__av;
              (/*if */(c1 >= lineitem_shipdate && lineitem_shipdate >= c2) ? REVENUE_mSUPPLIER1.addOrDelOnZero(se31.modify(lineitem_suppkey,revenue_msuppliersupplier_nationkey,l14,shipping_supp_nation,shipping_cust_nation),(v20 * (-1L * (lineitem_extendedprice * (1L + (-1L * lineitem_discount)))))) : (void)0);
              n20 = n20->nxt;
            } while (n20 && (e20 = n20->obj) && h18 == n20->hash &&  REVENUE_mSUPPLIER1_mLINEITEM4_mapkey0_idxfn::equals(se32, *e20)); 
          }
        }
      }
    }
    void on_insert_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_1* i21 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_1*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h21 = REVENUE_mORDERS1_T_2_mapkey1_idxfn::hash(se36.modify1(orders_orderkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_1::IdxNode* n21 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_1::IdxNode*>(i21->slice(se36, h21));
          REVENUE_mORDERS1_T_2_entry* e21;
         
          if (n21 && (e21 = n21->obj)) {
            do {                
              long s_nationkey = e21->S_NATIONKEY;
              long shipping_l_year = e21->SHIPPING_L_YEAR;
              DOUBLE_TYPE v21 = e21->__av;
              { //slice 
                const HashIndex_REVENUE_mORDERS1_T_3_map_0* i22 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
                const HASH_RES_t h20 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se35.modify0(orders_custkey));
                HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n22 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i22->slice(se35, h20));
                REVENUE_mORDERS1_T_3_entry* e22;
               
                if (n22 && (e22 = n22->obj)) {
                  do {                
                    long c_nationkey = e22->C_NATIONKEY;
                    long v22 = e22->__av;
                    { //slice 
                      const HashIndex_REVENUE_mLINEITEM4_T_1_map_01* i23 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01*>(REVENUE_mLINEITEM4_T_1.index[1]);
                      const HASH_RES_t h19 = REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::hash(se34.modify01(c_nationkey, s_nationkey));
                      HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode* n23 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode*>(i23->slice(se34, h19));
                      REVENUE_mLINEITEM4_T_1_entry* e23;
                     
                      if (n23 && (e23 = n23->obj)) {
                        do {                
                          STRING_TYPE shipping_cust_nation = e23->SHIPPING_CUST_NATION;
                          STRING_TYPE shipping_supp_nation = e23->SHIPPING_SUPP_NATION;
                          long v23 = e23->__av;
                          REVENUE.addOrDelOnZero(se33.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v21 * (v22 * v23)));
                          n23 = n23->nxt;
                        } while (n23 && (e23 = n23->obj) && h19 == n23->hash &&  REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::equals(se34, *e23)); 
                      }
                    }
                    n22 = n22->nxt;
                  } while (n22 && (e22 = n22->obj) && h20 == n22->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se35, *e22)); 
                }
              }
              n21 = n21->nxt;
            } while (n21 && (e21 = n21->obj) && h21 == n21->hash &&  REVENUE_mORDERS1_T_2_mapkey1_idxfn::equals(se36, *e21)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0* i24 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mORDERS1.index[1]);
          const HASH_RES_t h22 = REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn::hash(se38.modify0(orders_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0::IdxNode* n24 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0::IdxNode*>(i24->slice(se38, h22));
          REVENUE_mCUSTOMER1_mORDERS1_entry* e24;
         
          if (n24 && (e24 = n24->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e24->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
              long shipping_l_year = e24->SHIPPING_L_YEAR;
              STRING_TYPE shipping_cust_nation = e24->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e24->SHIPPING_SUPP_NATION;
              DOUBLE_TYPE v24 = e24->__av;
              REVENUE_mCUSTOMER1.addOrDelOnZero(se37.modify(orders_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_l_year,shipping_supp_nation),v24);
              n24 = n24->nxt;
            } while (n24 && (e24 = n24->obj) && h22 == n24->hash &&  REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn::equals(se38, *e24)); 
          }
        }REVENUE_mCUSTOMER1_mLINEITEM5.addOrDelOnZero(se39.modify(orders_orderkey,orders_custkey),1L);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0* i25 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[1]);
          const HASH_RES_t h23 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::hash(se41.modify0(orders_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode* n25 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode*>(i25->slice(se41, h23));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e25;
         
          if (n25 && (e25 = n25->obj)) {
            do {                
              long revenue_mcustomer1_msuppliersupplier_suppkey = e25->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long shipping_l_year = e25->SHIPPING_L_YEAR;
              DOUBLE_TYPE v25 = e25->__av;
              REVENUE_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se40.modify(revenue_mcustomer1_msuppliersupplier_suppkey,orders_custkey,shipping_l_year),v25);
              n25 = n25->nxt;
            } while (n25 && (e25 = n25->obj) && h23 == n25->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::equals(se41, *e25)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_3_map_0* i26 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
          const HASH_RES_t h24 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se43.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n26 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i26->slice(se43, h24));
          REVENUE_mORDERS1_T_3_entry* e26;
         
          if (n26 && (e26 = n26->obj)) {
            do {                
              long c_nationkey = e26->C_NATIONKEY;
              long v26 = e26->__av;
              REVENUE_mLINEITEM4_T_2.addOrDelOnZero(se42.modify(c_nationkey,orders_orderkey),v26);
              n26 = n26->nxt;
            } while (n26 && (e26 = n26->obj) && h24 == n26->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se43, *e26)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0* i27 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[1]);
          const HASH_RES_t h26 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::hash(se46.modify0(orders_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode* n27 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode*>(i27->slice(se46, h26));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e27;
         
          if (n27 && (e27 = n27->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e27->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long shipping_l_year = e27->SHIPPING_L_YEAR;
              DOUBLE_TYPE v27 = e27->__av;
              { //slice 
                const HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0* i28 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0*>(REVENUE_mSUPPLIER1_mORDERS1.index[1]);
                const HASH_RES_t h25 = REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::hash(se45.modify0(orders_custkey));
                HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode* n28 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode*>(i28->slice(se45, h25));
                REVENUE_mSUPPLIER1_mORDERS1_entry* e28;
               
                if (n28 && (e28 = n28->obj)) {
                  do {                
                    long revenue_msuppliersupplier_nationkey = e28->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
                    STRING_TYPE shipping_supp_nation = e28->SHIPPING_SUPP_NATION;
                    STRING_TYPE shipping_cust_nation = e28->SHIPPING_CUST_NATION;
                    long v28 = e28->__av;
                    REVENUE_mSUPPLIER1.addOrDelOnZero(se44.modify(revenue_msuppliersupplier_suppkey,revenue_msuppliersupplier_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v27 * v28));
                    n28 = n28->nxt;
                  } while (n28 && (e28 = n28->obj) && h25 == n28->hash &&  REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::equals(se45, *e28)); 
                }
              }
              n27 = n27->nxt;
            } while (n27 && (e27 = n27->obj) && h26 == n27->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::equals(se46, *e27)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0* i29 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0*>(REVENUE_mSUPPLIER1_mORDERS1.index[1]);
          const HASH_RES_t h27 = REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::hash(se48.modify0(orders_custkey));
          HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode* n29 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode*>(i29->slice(se48, h27));
          REVENUE_mSUPPLIER1_mORDERS1_entry* e29;
         
          if (n29 && (e29 = n29->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e29->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
              STRING_TYPE shipping_supp_nation = e29->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e29->SHIPPING_CUST_NATION;
              long v29 = e29->__av;
              REVENUE_mSUPPLIER1_mLINEITEM4.addOrDelOnZero(se47.modify(orders_orderkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),v29);
              n29 = n29->nxt;
            } while (n29 && (e29 = n29->obj) && h27 == n29->hash &&  REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::equals(se48, *e29)); 
          }
        }
      }
    }
    void on_delete_ORDERS(const long orders_orderkey, const long orders_custkey, const STRING_TYPE& orders_orderstatus, const DOUBLE_TYPE orders_totalprice, const date orders_orderdate, const STRING_TYPE& orders_orderpriority, const STRING_TYPE& orders_clerk, const long orders_shippriority, const STRING_TYPE& orders_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mORDERS1_T_2_map_1* i30 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_1*>(REVENUE_mORDERS1_T_2.index[1]);
          const HASH_RES_t h30 = REVENUE_mORDERS1_T_2_mapkey1_idxfn::hash(se52.modify1(orders_orderkey));
          HashIndex_REVENUE_mORDERS1_T_2_map_1::IdxNode* n30 = static_cast<HashIndex_REVENUE_mORDERS1_T_2_map_1::IdxNode*>(i30->slice(se52, h30));
          REVENUE_mORDERS1_T_2_entry* e30;
         
          if (n30 && (e30 = n30->obj)) {
            do {                
              long s_nationkey = e30->S_NATIONKEY;
              long shipping_l_year = e30->SHIPPING_L_YEAR;
              DOUBLE_TYPE v30 = e30->__av;
              { //slice 
                const HashIndex_REVENUE_mORDERS1_T_3_map_0* i31 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
                const HASH_RES_t h29 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se51.modify0(orders_custkey));
                HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n31 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i31->slice(se51, h29));
                REVENUE_mORDERS1_T_3_entry* e31;
               
                if (n31 && (e31 = n31->obj)) {
                  do {                
                    long c_nationkey = e31->C_NATIONKEY;
                    long v31 = e31->__av;
                    { //slice 
                      const HashIndex_REVENUE_mLINEITEM4_T_1_map_01* i32 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01*>(REVENUE_mLINEITEM4_T_1.index[1]);
                      const HASH_RES_t h28 = REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::hash(se50.modify01(c_nationkey, s_nationkey));
                      HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode* n32 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_01::IdxNode*>(i32->slice(se50, h28));
                      REVENUE_mLINEITEM4_T_1_entry* e32;
                     
                      if (n32 && (e32 = n32->obj)) {
                        do {                
                          STRING_TYPE shipping_cust_nation = e32->SHIPPING_CUST_NATION;
                          STRING_TYPE shipping_supp_nation = e32->SHIPPING_SUPP_NATION;
                          long v32 = e32->__av;
                          REVENUE.addOrDelOnZero(se49.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),((v30 * (v31 * v32)) * -1L));
                          n32 = n32->nxt;
                        } while (n32 && (e32 = n32->obj) && h28 == n32->hash &&  REVENUE_mLINEITEM4_T_1_mapkey01_idxfn::equals(se50, *e32)); 
                      }
                    }
                    n31 = n31->nxt;
                  } while (n31 && (e31 = n31->obj) && h29 == n31->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se51, *e31)); 
                }
              }
              n30 = n30->nxt;
            } while (n30 && (e30 = n30->obj) && h30 == n30->hash &&  REVENUE_mORDERS1_T_2_mapkey1_idxfn::equals(se52, *e30)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0* i33 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mORDERS1.index[1]);
          const HASH_RES_t h31 = REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn::hash(se54.modify0(orders_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0::IdxNode* n33 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mORDERS1_map_0::IdxNode*>(i33->slice(se54, h31));
          REVENUE_mCUSTOMER1_mORDERS1_entry* e33;
         
          if (n33 && (e33 = n33->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e33->REVENUE_mCUSTOMERCUSTOMER_NATIONKEY;
              long shipping_l_year = e33->SHIPPING_L_YEAR;
              STRING_TYPE shipping_cust_nation = e33->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e33->SHIPPING_SUPP_NATION;
              DOUBLE_TYPE v33 = e33->__av;
              REVENUE_mCUSTOMER1.addOrDelOnZero(se53.modify(orders_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_l_year,shipping_supp_nation),(v33 * -1L));
              n33 = n33->nxt;
            } while (n33 && (e33 = n33->obj) && h31 == n33->hash &&  REVENUE_mCUSTOMER1_mORDERS1_mapkey0_idxfn::equals(se54, *e33)); 
          }
        }REVENUE_mCUSTOMER1_mLINEITEM5.addOrDelOnZero(se55.modify(orders_orderkey,orders_custkey),-1L);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0* i34 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[1]);
          const HASH_RES_t h32 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::hash(se57.modify0(orders_orderkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode* n34 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode*>(i34->slice(se57, h32));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e34;
         
          if (n34 && (e34 = n34->obj)) {
            do {                
              long revenue_mcustomer1_msuppliersupplier_suppkey = e34->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long shipping_l_year = e34->SHIPPING_L_YEAR;
              DOUBLE_TYPE v34 = e34->__av;
              REVENUE_mCUSTOMER1_mSUPPLIER2.addOrDelOnZero(se56.modify(revenue_mcustomer1_msuppliersupplier_suppkey,orders_custkey,shipping_l_year),(v34 * -1L));
              n34 = n34->nxt;
            } while (n34 && (e34 = n34->obj) && h32 == n34->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::equals(se57, *e34)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mORDERS1_T_3_map_0* i35 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0*>(REVENUE_mORDERS1_T_3.index[1]);
          const HASH_RES_t h33 = REVENUE_mORDERS1_T_3_mapkey0_idxfn::hash(se59.modify0(orders_custkey));
          HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode* n35 = static_cast<HashIndex_REVENUE_mORDERS1_T_3_map_0::IdxNode*>(i35->slice(se59, h33));
          REVENUE_mORDERS1_T_3_entry* e35;
         
          if (n35 && (e35 = n35->obj)) {
            do {                
              long c_nationkey = e35->C_NATIONKEY;
              long v35 = e35->__av;
              REVENUE_mLINEITEM4_T_2.addOrDelOnZero(se58.modify(c_nationkey,orders_orderkey),(v35 * -1L));
              n35 = n35->nxt;
            } while (n35 && (e35 = n35->obj) && h33 == n35->hash &&  REVENUE_mORDERS1_T_3_mapkey0_idxfn::equals(se59, *e35)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0* i36 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0*>(REVENUE_mSUPPLIER1_mORDERS1.index[1]);
          const HASH_RES_t h35 = REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::hash(se62.modify0(orders_custkey));
          HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode* n36 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode*>(i36->slice(se62, h35));
          REVENUE_mSUPPLIER1_mORDERS1_entry* e36;
         
          if (n36 && (e36 = n36->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e36->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
              STRING_TYPE shipping_supp_nation = e36->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e36->SHIPPING_CUST_NATION;
              long v36 = e36->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0* i37 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[1]);
                const HASH_RES_t h34 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::hash(se61.modify0(orders_orderkey));
                HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode* n37 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_0::IdxNode*>(i37->slice(se61, h34));
                REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e37;
               
                if (n37 && (e37 = n37->obj)) {
                  do {                
                    long revenue_msuppliersupplier_suppkey = e37->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
                    long shipping_l_year = e37->SHIPPING_L_YEAR;
                    DOUBLE_TYPE v37 = e37->__av;
                    REVENUE_mSUPPLIER1.addOrDelOnZero(se60.modify(revenue_msuppliersupplier_suppkey,revenue_msuppliersupplier_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v36 * (v37 * -1L)));
                    n37 = n37->nxt;
                  } while (n37 && (e37 = n37->obj) && h34 == n37->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey0_idxfn::equals(se61, *e37)); 
                }
              }
              n36 = n36->nxt;
            } while (n36 && (e36 = n36->obj) && h35 == n36->hash &&  REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::equals(se62, *e36)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0* i38 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0*>(REVENUE_mSUPPLIER1_mORDERS1.index[1]);
          const HASH_RES_t h36 = REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::hash(se64.modify0(orders_custkey));
          HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode* n38 = static_cast<HashIndex_REVENUE_mSUPPLIER1_mORDERS1_map_0::IdxNode*>(i38->slice(se64, h36));
          REVENUE_mSUPPLIER1_mORDERS1_entry* e38;
         
          if (n38 && (e38 = n38->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e38->REVENUE_mSUPPLIERSUPPLIER_NATIONKEY;
              STRING_TYPE shipping_supp_nation = e38->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e38->SHIPPING_CUST_NATION;
              long v38 = e38->__av;
              REVENUE_mSUPPLIER1_mLINEITEM4.addOrDelOnZero(se63.modify(orders_orderkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),(v38 * -1L));
              n38 = n38->nxt;
            } while (n38 && (e38 = n38->obj) && h36 == n38->hash &&  REVENUE_mSUPPLIER1_mORDERS1_mapkey0_idxfn::equals(se64, *e38)); 
          }
        }
      }
    }
    void on_insert_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i39 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h37 = REVENUE_mCUSTOMER1_mapkey01_idxfn::hash(se66.modify01(customer_custkey, customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n39 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode*>(i39->slice(se66, h37));
          REVENUE_mCUSTOMER1_entry* e39;
         
          if (n39 && (e39 = n39->obj)) {
            do {                
              STRING_TYPE shipping_cust_nation = e39->SHIPPING_CUST_NATION;
              long shipping_l_year = e39->SHIPPING_L_YEAR;
              STRING_TYPE shipping_supp_nation = e39->SHIPPING_SUPP_NATION;
              DOUBLE_TYPE v39 = e39->__av;
              REVENUE.addOrDelOnZero(se65.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),v39);
              n39 = n39->nxt;
            } while (n39 && (e39 = n39->obj) && h37 == n39->hash &&  REVENUE_mCUSTOMER1_mapkey01_idxfn::equals(se66, *e39)); 
          }
        }REVENUE_mORDERS1_T_3.addOrDelOnZero(se67.modify(customer_custkey,customer_nationkey),1L);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1* i40 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[2]);
          const HASH_RES_t h38 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::hash(se69.modify1(customer_custkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode* n40 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode*>(i40->slice(se69, h38));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e40;
         
          if (n40 && (e40 = n40->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e40->REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v40 = e40->__av;
              REVENUE_mLINEITEM4_T_2.addOrDelOnZero(se68.modify(customer_nationkey,revenue_mlineitemlineitem_orderkey),v40);
              n40 = n40->nxt;
            } while (n40 && (e40 = n40->obj) && h38 == n40->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::equals(se69, *e40)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1* i41 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2.index[1]);
          const HASH_RES_t h40 = REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::hash(se72.modify1(customer_custkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode* n41 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode*>(i41->slice(se72, h40));
          REVENUE_mCUSTOMER1_mSUPPLIER2_entry* e41;
         
          if (n41 && (e41 = n41->obj)) {
            do {                
              long revenue_msuppliersupplier_suppkey = e41->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
              long shipping_l_year = e41->SHIPPING_L_YEAR;
              DOUBLE_TYPE v41 = e41->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i42 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
                const HASH_RES_t h39 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se71.modify0(customer_nationkey));
                HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n42 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i42->slice(se71, h39));
                REVENUE_mLINEITEM4_T_1_entry* e42;
               
                if (n42 && (e42 = n42->obj)) {
                  do {                
                    long revenue_msuppliersupplier_nationkey = e42->S_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e42->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e42->SHIPPING_SUPP_NATION;
                    long v42 = e42->__av;
                    REVENUE_mSUPPLIER1.addOrDelOnZero(se70.modify(revenue_msuppliersupplier_suppkey,revenue_msuppliersupplier_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v41 * v42));
                    n42 = n42->nxt;
                  } while (n42 && (e42 = n42->obj) && h39 == n42->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se71, *e42)); 
                }
              }
              n41 = n41->nxt;
            } while (n41 && (e41 = n41->obj) && h40 == n41->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::equals(se72, *e41)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i43 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
          const HASH_RES_t h41 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se74.modify0(customer_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n43 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i43->slice(se74, h41));
          REVENUE_mLINEITEM4_T_1_entry* e43;
         
          if (n43 && (e43 = n43->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e43->S_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e43->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e43->SHIPPING_SUPP_NATION;
              long v43 = e43->__av;
              REVENUE_mSUPPLIER1_mORDERS1.addOrDelOnZero(se73.modify(customer_custkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),v43);
              n43 = n43->nxt;
            } while (n43 && (e43 = n43->obj) && h41 == n43->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se74, *e43)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1* i44 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[2]);
          const HASH_RES_t h43 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::hash(se77.modify1(customer_custkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode* n44 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode*>(i44->slice(se77, h43));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e44;
         
          if (n44 && (e44 = n44->obj)) {
            do {                
              long revenue_msupplier1_mlineitemlineitem_orderkey = e44->REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v44 = e44->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i45 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
                const HASH_RES_t h42 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se76.modify0(customer_nationkey));
                HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n45 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i45->slice(se76, h42));
                REVENUE_mLINEITEM4_T_1_entry* e45;
               
                if (n45 && (e45 = n45->obj)) {
                  do {                
                    long revenue_msuppliersupplier_nationkey = e45->S_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e45->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e45->SHIPPING_SUPP_NATION;
                    long v45 = e45->__av;
                    REVENUE_mSUPPLIER1_mLINEITEM4.addOrDelOnZero(se75.modify(revenue_msupplier1_mlineitemlineitem_orderkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),(v44 * v45));
                    n45 = n45->nxt;
                  } while (n45 && (e45 = n45->obj) && h42 == n45->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se76, *e45)); 
                }
              }
              n44 = n44->nxt;
            } while (n44 && (e44 = n44->obj) && h43 == n44->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::equals(se77, *e44)); 
          }
        }
      }
    }
    void on_delete_CUSTOMER(const long customer_custkey, const STRING_TYPE& customer_name, const STRING_TYPE& customer_address, const long customer_nationkey, const STRING_TYPE& customer_phone, const DOUBLE_TYPE customer_acctbal, const STRING_TYPE& customer_mktsegment, const STRING_TYPE& customer_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_map_01* i46 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01*>(REVENUE_mCUSTOMER1.index[1]);
          const HASH_RES_t h44 = REVENUE_mCUSTOMER1_mapkey01_idxfn::hash(se79.modify01(customer_custkey, customer_nationkey));
          HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode* n46 = static_cast<HashIndex_REVENUE_mCUSTOMER1_map_01::IdxNode*>(i46->slice(se79, h44));
          REVENUE_mCUSTOMER1_entry* e46;
         
          if (n46 && (e46 = n46->obj)) {
            do {                
              STRING_TYPE shipping_cust_nation = e46->SHIPPING_CUST_NATION;
              long shipping_l_year = e46->SHIPPING_L_YEAR;
              STRING_TYPE shipping_supp_nation = e46->SHIPPING_SUPP_NATION;
              DOUBLE_TYPE v46 = e46->__av;
              REVENUE.addOrDelOnZero(se78.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v46 * -1L));
              n46 = n46->nxt;
            } while (n46 && (e46 = n46->obj) && h44 == n46->hash &&  REVENUE_mCUSTOMER1_mapkey01_idxfn::equals(se79, *e46)); 
          }
        }REVENUE_mORDERS1_T_3.addOrDelOnZero(se80.modify(customer_custkey,customer_nationkey),-1L);
        { //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1* i47 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[2]);
          const HASH_RES_t h45 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::hash(se82.modify1(customer_custkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode* n47 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode*>(i47->slice(se82, h45));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e47;
         
          if (n47 && (e47 = n47->obj)) {
            do {                
              long revenue_mlineitemlineitem_orderkey = e47->REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v47 = e47->__av;
              REVENUE_mLINEITEM4_T_2.addOrDelOnZero(se81.modify(customer_nationkey,revenue_mlineitemlineitem_orderkey),(v47 * -1L));
              n47 = n47->nxt;
            } while (n47 && (e47 = n47->obj) && h45 == n47->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::equals(se82, *e47)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i48 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
          const HASH_RES_t h47 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se85.modify0(customer_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n48 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i48->slice(se85, h47));
          REVENUE_mLINEITEM4_T_1_entry* e48;
         
          if (n48 && (e48 = n48->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e48->S_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e48->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e48->SHIPPING_SUPP_NATION;
              long v48 = e48->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1* i49 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2.index[1]);
                const HASH_RES_t h46 = REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::hash(se84.modify1(customer_custkey));
                HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode* n49 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_1::IdxNode*>(i49->slice(se84, h46));
                REVENUE_mCUSTOMER1_mSUPPLIER2_entry* e49;
               
                if (n49 && (e49 = n49->obj)) {
                  do {                
                    long revenue_msuppliersupplier_suppkey = e49->REVENUE_mCUSTOMER1_mSUPPLIERSUPPLIER_SUPPKEY;
                    long shipping_l_year = e49->SHIPPING_L_YEAR;
                    DOUBLE_TYPE v49 = e49->__av;
                    REVENUE_mSUPPLIER1.addOrDelOnZero(se83.modify(revenue_msuppliersupplier_suppkey,revenue_msuppliersupplier_nationkey,shipping_l_year,shipping_supp_nation,shipping_cust_nation),(v48 * (v49 * -1L)));
                    n49 = n49->nxt;
                  } while (n49 && (e49 = n49->obj) && h46 == n49->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey1_idxfn::equals(se84, *e49)); 
                }
              }
              n48 = n48->nxt;
            } while (n48 && (e48 = n48->obj) && h47 == n48->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se85, *e48)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i50 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
          const HASH_RES_t h48 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se87.modify0(customer_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n50 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i50->slice(se87, h48));
          REVENUE_mLINEITEM4_T_1_entry* e50;
         
          if (n50 && (e50 = n50->obj)) {
            do {                
              long revenue_msuppliersupplier_nationkey = e50->S_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e50->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e50->SHIPPING_SUPP_NATION;
              long v50 = e50->__av;
              REVENUE_mSUPPLIER1_mORDERS1.addOrDelOnZero(se86.modify(customer_custkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),(v50 * -1L));
              n50 = n50->nxt;
            } while (n50 && (e50 = n50->obj) && h48 == n50->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se87, *e50)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1* i51 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1*>(REVENUE_mCUSTOMER1_mLINEITEM5.index[2]);
          const HASH_RES_t h50 = REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::hash(se90.modify1(customer_custkey));
          HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode* n51 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mLINEITEM5_map_1::IdxNode*>(i51->slice(se90, h50));
          REVENUE_mCUSTOMER1_mLINEITEM5_entry* e51;
         
          if (n51 && (e51 = n51->obj)) {
            do {                
              long revenue_msupplier1_mlineitemlineitem_orderkey = e51->REVENUE_mCUSTOMER1_mLINEITEMLINEITEM_ORDERKEY;
              long v51 = e51->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_1_map_0* i52 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0*>(REVENUE_mLINEITEM4_T_1.index[2]);
                const HASH_RES_t h49 = REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::hash(se89.modify0(customer_nationkey));
                HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode* n52 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_0::IdxNode*>(i52->slice(se89, h49));
                REVENUE_mLINEITEM4_T_1_entry* e52;
               
                if (n52 && (e52 = n52->obj)) {
                  do {                
                    long revenue_msuppliersupplier_nationkey = e52->S_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e52->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e52->SHIPPING_SUPP_NATION;
                    long v52 = e52->__av;
                    REVENUE_mSUPPLIER1_mLINEITEM4.addOrDelOnZero(se88.modify(revenue_msupplier1_mlineitemlineitem_orderkey,revenue_msuppliersupplier_nationkey,shipping_supp_nation,shipping_cust_nation),(v51 * (v52 * -1L)));
                    n52 = n52->nxt;
                  } while (n52 && (e52 = n52->obj) && h49 == n52->hash &&  REVENUE_mLINEITEM4_T_1_mapkey0_idxfn::equals(se89, *e52)); 
                }
              }
              n51 = n51->nxt;
            } while (n51 && (e51 = n51->obj) && h50 == n51->hash &&  REVENUE_mCUSTOMER1_mLINEITEM5_mapkey1_idxfn::equals(se90, *e51)); 
          }
        }
      }
    }
    void on_insert_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER1_map_01* i53 = static_cast<HashIndex_REVENUE_mSUPPLIER1_map_01*>(REVENUE_mSUPPLIER1.index[1]);
          const HASH_RES_t h51 = REVENUE_mSUPPLIER1_mapkey01_idxfn::hash(se92.modify01(supplier_suppkey, supplier_nationkey));
          HashIndex_REVENUE_mSUPPLIER1_map_01::IdxNode* n53 = static_cast<HashIndex_REVENUE_mSUPPLIER1_map_01::IdxNode*>(i53->slice(se92, h51));
          REVENUE_mSUPPLIER1_entry* e53;
         
          if (n53 && (e53 = n53->obj)) {
            do {                
              long shipping_l_year = e53->SHIPPING_L_YEAR;
              STRING_TYPE shipping_supp_nation = e53->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e53->SHIPPING_CUST_NATION;
              DOUBLE_TYPE v53 = e53->__av;
              REVENUE.addOrDelOnZero(se91.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),v53);
              n53 = n53->nxt;
            } while (n53 && (e53 = n53->obj) && h51 == n53->hash &&  REVENUE_mSUPPLIER1_mapkey01_idxfn::equals(se92, *e53)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0* i54 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2.index[2]);
          const HASH_RES_t h53 = REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::hash(se95.modify0(supplier_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode* n54 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode*>(i54->slice(se95, h53));
          REVENUE_mCUSTOMER1_mSUPPLIER2_entry* e54;
         
          if (n54 && (e54 = n54->obj)) {
            do {                
              long revenue_mcustomercustomer_custkey = e54->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
              long shipping_l_year = e54->SHIPPING_L_YEAR;
              DOUBLE_TYPE v54 = e54->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i55 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
                const HASH_RES_t h52 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se94.modify1(supplier_nationkey));
                HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n55 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i55->slice(se94, h52));
                REVENUE_mLINEITEM4_T_1_entry* e55;
               
                if (n55 && (e55 = n55->obj)) {
                  do {                
                    long revenue_mcustomercustomer_nationkey = e55->C_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e55->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e55->SHIPPING_SUPP_NATION;
                    long v55 = e55->__av;
                    REVENUE_mCUSTOMER1.addOrDelOnZero(se93.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_l_year,shipping_supp_nation),(v54 * v55));
                    n55 = n55->nxt;
                  } while (n55 && (e55 = n55->obj) && h52 == n55->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se94, *e55)); 
                }
              }
              n54 = n54->nxt;
            } while (n54 && (e54 = n54->obj) && h53 == n54->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::equals(se95, *e54)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i56 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
          const HASH_RES_t h54 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se97.modify1(supplier_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n56 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i56->slice(se97, h54));
          REVENUE_mLINEITEM4_T_1_entry* e56;
         
          if (n56 && (e56 = n56->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e56->C_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e56->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e56->SHIPPING_SUPP_NATION;
              long v56 = e56->__av;
              REVENUE_mCUSTOMER1_mLINEITEM4.addOrDelOnZero(se96.modify(supplier_suppkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_supp_nation),v56);
              n56 = n56->nxt;
            } while (n56 && (e56 = n56->obj) && h54 == n56->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se97, *e56)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1* i57 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[2]);
          const HASH_RES_t h56 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::hash(se100.modify1(supplier_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode* n57 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode*>(i57->slice(se100, h56));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e57;
         
          if (n57 && (e57 = n57->obj)) {
            do {                
              long revenue_mcustomer1_mordersorders_orderkey = e57->REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
              long shipping_l_year = e57->SHIPPING_L_YEAR;
              DOUBLE_TYPE v57 = e57->__av;
              { //slice 
                const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i58 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
                const HASH_RES_t h55 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se99.modify1(supplier_nationkey));
                HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n58 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i58->slice(se99, h55));
                REVENUE_mLINEITEM4_T_1_entry* e58;
               
                if (n58 && (e58 = n58->obj)) {
                  do {                
                    long revenue_mcustomercustomer_nationkey = e58->C_NATIONKEY;
                    STRING_TYPE shipping_cust_nation = e58->SHIPPING_CUST_NATION;
                    STRING_TYPE shipping_supp_nation = e58->SHIPPING_SUPP_NATION;
                    long v58 = e58->__av;
                    REVENUE_mCUSTOMER1_mORDERS1.addOrDelOnZero(se98.modify(revenue_mcustomer1_mordersorders_orderkey,revenue_mcustomercustomer_nationkey,shipping_l_year,shipping_cust_nation,shipping_supp_nation),(v57 * v58));
                    n58 = n58->nxt;
                  } while (n58 && (e58 = n58->obj) && h55 == n58->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se99, *e58)); 
                }
              }
              n57 = n57->nxt;
            } while (n57 && (e57 = n57->obj) && h56 == n57->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::equals(se100, *e57)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1* i59 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[2]);
          const HASH_RES_t h57 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::hash(se102.modify1(supplier_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode* n59 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode*>(i59->slice(se102, h57));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e59;
         
          if (n59 && (e59 = n59->obj)) {
            do {                
              long revenue_mordersorders_orderkey = e59->REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
              long shipping_l_year = e59->SHIPPING_L_YEAR;
              DOUBLE_TYPE v59 = e59->__av;
              REVENUE_mORDERS1_T_2.addOrDelOnZero(se101.modify(supplier_nationkey,revenue_mordersorders_orderkey,shipping_l_year),v59);
              n59 = n59->nxt;
            } while (n59 && (e59 = n59->obj) && h57 == n59->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::equals(se102, *e59)); 
          }
        }REVENUE_mLINEITEM4_T_3.addOrDelOnZero(se103.modify(supplier_suppkey,supplier_nationkey),1L);
      }
    }
    void on_delete_SUPPLIER(const long supplier_suppkey, const STRING_TYPE& supplier_name, const STRING_TYPE& supplier_address, const long supplier_nationkey, const STRING_TYPE& supplier_phone, const DOUBLE_TYPE supplier_acctbal, const STRING_TYPE& supplier_comment) {
      {  //++tN;
        { //slice 
          const HashIndex_REVENUE_mSUPPLIER1_map_01* i60 = static_cast<HashIndex_REVENUE_mSUPPLIER1_map_01*>(REVENUE_mSUPPLIER1.index[1]);
          const HASH_RES_t h58 = REVENUE_mSUPPLIER1_mapkey01_idxfn::hash(se105.modify01(supplier_suppkey, supplier_nationkey));
          HashIndex_REVENUE_mSUPPLIER1_map_01::IdxNode* n60 = static_cast<HashIndex_REVENUE_mSUPPLIER1_map_01::IdxNode*>(i60->slice(se105, h58));
          REVENUE_mSUPPLIER1_entry* e60;
         
          if (n60 && (e60 = n60->obj)) {
            do {                
              long shipping_l_year = e60->SHIPPING_L_YEAR;
              STRING_TYPE shipping_supp_nation = e60->SHIPPING_SUPP_NATION;
              STRING_TYPE shipping_cust_nation = e60->SHIPPING_CUST_NATION;
              DOUBLE_TYPE v60 = e60->__av;
              REVENUE.addOrDelOnZero(se104.modify(shipping_supp_nation,shipping_cust_nation,shipping_l_year),(v60 * -1L));
              n60 = n60->nxt;
            } while (n60 && (e60 = n60->obj) && h58 == n60->hash &&  REVENUE_mSUPPLIER1_mapkey01_idxfn::equals(se105, *e60)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i61 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
          const HASH_RES_t h60 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se108.modify1(supplier_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n61 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i61->slice(se108, h60));
          REVENUE_mLINEITEM4_T_1_entry* e61;
         
          if (n61 && (e61 = n61->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e61->C_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e61->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e61->SHIPPING_SUPP_NATION;
              long v61 = e61->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0* i62 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0*>(REVENUE_mCUSTOMER1_mSUPPLIER2.index[2]);
                const HASH_RES_t h59 = REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::hash(se107.modify0(supplier_suppkey));
                HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode* n62 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_map_0::IdxNode*>(i62->slice(se107, h59));
                REVENUE_mCUSTOMER1_mSUPPLIER2_entry* e62;
               
                if (n62 && (e62 = n62->obj)) {
                  do {                
                    long revenue_mcustomercustomer_custkey = e62->REVENUE_mCUSTOMERCUSTOMER_CUSTKEY;
                    long shipping_l_year = e62->SHIPPING_L_YEAR;
                    DOUBLE_TYPE v62 = e62->__av;
                    REVENUE_mCUSTOMER1.addOrDelOnZero(se106.modify(revenue_mcustomercustomer_custkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_l_year,shipping_supp_nation),(v61 * (v62 * -1L)));
                    n62 = n62->nxt;
                  } while (n62 && (e62 = n62->obj) && h59 == n62->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mapkey0_idxfn::equals(se107, *e62)); 
                }
              }
              n61 = n61->nxt;
            } while (n61 && (e61 = n61->obj) && h60 == n61->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se108, *e61)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i63 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
          const HASH_RES_t h61 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se110.modify1(supplier_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n63 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i63->slice(se110, h61));
          REVENUE_mLINEITEM4_T_1_entry* e63;
         
          if (n63 && (e63 = n63->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e63->C_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e63->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e63->SHIPPING_SUPP_NATION;
              long v63 = e63->__av;
              REVENUE_mCUSTOMER1_mLINEITEM4.addOrDelOnZero(se109.modify(supplier_suppkey,revenue_mcustomercustomer_nationkey,shipping_cust_nation,shipping_supp_nation),(v63 * -1L));
              n63 = n63->nxt;
            } while (n63 && (e63 = n63->obj) && h61 == n63->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se110, *e63)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mLINEITEM4_T_1_map_1* i64 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1*>(REVENUE_mLINEITEM4_T_1.index[3]);
          const HASH_RES_t h63 = REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::hash(se113.modify1(supplier_nationkey));
          HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode* n64 = static_cast<HashIndex_REVENUE_mLINEITEM4_T_1_map_1::IdxNode*>(i64->slice(se113, h63));
          REVENUE_mLINEITEM4_T_1_entry* e64;
         
          if (n64 && (e64 = n64->obj)) {
            do {                
              long revenue_mcustomercustomer_nationkey = e64->C_NATIONKEY;
              STRING_TYPE shipping_cust_nation = e64->SHIPPING_CUST_NATION;
              STRING_TYPE shipping_supp_nation = e64->SHIPPING_SUPP_NATION;
              long v64 = e64->__av;
              { //slice 
                const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1* i65 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[2]);
                const HASH_RES_t h62 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::hash(se112.modify1(supplier_suppkey));
                HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode* n65 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode*>(i65->slice(se112, h62));
                REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e65;
               
                if (n65 && (e65 = n65->obj)) {
                  do {                
                    long revenue_mcustomer1_mordersorders_orderkey = e65->REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
                    long shipping_l_year = e65->SHIPPING_L_YEAR;
                    DOUBLE_TYPE v65 = e65->__av;
                    REVENUE_mCUSTOMER1_mORDERS1.addOrDelOnZero(se111.modify(revenue_mcustomer1_mordersorders_orderkey,revenue_mcustomercustomer_nationkey,shipping_l_year,shipping_cust_nation,shipping_supp_nation),(v64 * (v65 * -1L)));
                    n65 = n65->nxt;
                  } while (n65 && (e65 = n65->obj) && h62 == n65->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::equals(se112, *e65)); 
                }
              }
              n64 = n64->nxt;
            } while (n64 && (e64 = n64->obj) && h63 == n64->hash &&  REVENUE_mLINEITEM4_T_1_mapkey1_idxfn::equals(se113, *e64)); 
          }
        }{ //slice 
          const HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1* i66 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1*>(REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1.index[2]);
          const HASH_RES_t h64 = REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::hash(se115.modify1(supplier_suppkey));
          HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode* n66 = static_cast<HashIndex_REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map_1::IdxNode*>(i66->slice(se115, h64));
          REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry* e66;
         
          if (n66 && (e66 = n66->obj)) {
            do {                
              long revenue_mordersorders_orderkey = e66->REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERSORDERS_ORDERKEY;
              long shipping_l_year = e66->SHIPPING_L_YEAR;
              DOUBLE_TYPE v66 = e66->__av;
              REVENUE_mORDERS1_T_2.addOrDelOnZero(se114.modify(supplier_nationkey,revenue_mordersorders_orderkey,shipping_l_year),(v66 * -1L));
              n66 = n66->nxt;
            } while (n66 && (e66 = n66->obj) && h64 == n66->hash &&  REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_mapkey1_idxfn::equals(se115, *e66)); 
          }
        }REVENUE_mLINEITEM4_T_3.addOrDelOnZero(se116.modify(supplier_suppkey,supplier_nationkey),-1L);
      }
    }
    void on_system_ready_event() {
      {  //
        REVENUE_mLINEITEM4_T_1.clear();
        {  // foreach
          const HashIndex_NATION_map_0123* i67 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
          HashIndex_NATION_map_0123::IdxNode* n67; 
          NATION_entry* e67;
        
          for (size_t i = 0; i < i67->size_; i++)
          {
            n67 = i67->buckets_ + i;
            while (n67 && (e67 = n67->obj))
            {
                long c_nationkey = e67->NATION_NATIONKEY;
                STRING_TYPE n2_name = e67->NATION_NAME;
                long n2_regionkey = e67->NATION_REGIONKEY;
                STRING_TYPE n2_comment = e67->NATION_COMMENT;
                long v67 = e67->__av;
                {  // foreach
                  const HashIndex_NATION_map_0123* i68 = static_cast<HashIndex_NATION_map_0123*>(NATION.index[0]);
                  HashIndex_NATION_map_0123::IdxNode* n68; 
                  NATION_entry* e68;
                
                  for (size_t i = 0; i < i68->size_; i++)
                  {
                    n68 = i68->buckets_ + i;
                    while (n68 && (e68 = n68->obj))
                    {
                        long s_nationkey = e68->NATION_NATIONKEY;
                        STRING_TYPE n1_name = e68->NATION_NAME;
                        long n1_regionkey = e68->NATION_REGIONKEY;
                        STRING_TYPE n1_comment = e68->NATION_COMMENT;
                        long v68 = e68->__av;
                        long l15 = ((/*if */(n1_name == c3 && n2_name == c4) ? 1L : 0L) + (/*if */(n1_name == c4 && n2_name == c3) ? 1L : 0L));
                        (/*if */(l15 > 0L) ? REVENUE_mLINEITEM4_T_1.addOrDelOnZero(se117.modify(c_nationkey,s_nationkey,n2_name,n1_name),(v67 * v68)) : (void)0);
                      n68 = n68->nxt;
                    }
                  }
                }
              n67 = n67->nxt;
            }
          }
        }
      }
    }
  
  private:
  
    /* Sample entries for avoiding recreation of temporary objects */
    REVENUE_entry se1;
    tuple3_SS_L st1;
    REVENUE_mLINEITEM4_T_1_entry se2;
    REVENUE_mLINEITEM4_T_2_entry se3;
    REVENUE_mLINEITEM4_T_3_entry se4;
    REVENUE_mCUSTOMER1_entry se5;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se6;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se7;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se8;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se9;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se10;
    REVENUE_mCUSTOMER1_mORDERS1_entry se11;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se12;
    REVENUE_mORDERS1_T_2_entry se13;
    REVENUE_mLINEITEM4_T_3_entry se14;
    REVENUE_mSUPPLIER1_entry se15;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se16;
    REVENUE_entry se17;
    tuple3_SS_L st2;
    REVENUE_mLINEITEM4_T_1_entry se18;
    REVENUE_mLINEITEM4_T_2_entry se19;
    REVENUE_mLINEITEM4_T_3_entry se20;
    REVENUE_mCUSTOMER1_entry se21;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se22;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se23;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se24;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se25;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se26;
    REVENUE_mCUSTOMER1_mORDERS1_entry se27;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se28;
    REVENUE_mORDERS1_T_2_entry se29;
    REVENUE_mLINEITEM4_T_3_entry se30;
    REVENUE_mSUPPLIER1_entry se31;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se32;
    REVENUE_entry se33;
    REVENUE_mLINEITEM4_T_1_entry se34;
    REVENUE_mORDERS1_T_3_entry se35;
    REVENUE_mORDERS1_T_2_entry se36;
    REVENUE_mCUSTOMER1_entry se37;
    REVENUE_mCUSTOMER1_mORDERS1_entry se38;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se39;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se40;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se41;
    REVENUE_mLINEITEM4_T_2_entry se42;
    REVENUE_mORDERS1_T_3_entry se43;
    REVENUE_mSUPPLIER1_entry se44;
    REVENUE_mSUPPLIER1_mORDERS1_entry se45;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se46;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se47;
    REVENUE_mSUPPLIER1_mORDERS1_entry se48;
    REVENUE_entry se49;
    REVENUE_mLINEITEM4_T_1_entry se50;
    REVENUE_mORDERS1_T_3_entry se51;
    REVENUE_mORDERS1_T_2_entry se52;
    REVENUE_mCUSTOMER1_entry se53;
    REVENUE_mCUSTOMER1_mORDERS1_entry se54;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se55;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se56;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se57;
    REVENUE_mLINEITEM4_T_2_entry se58;
    REVENUE_mORDERS1_T_3_entry se59;
    REVENUE_mSUPPLIER1_entry se60;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se61;
    REVENUE_mSUPPLIER1_mORDERS1_entry se62;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se63;
    REVENUE_mSUPPLIER1_mORDERS1_entry se64;
    REVENUE_entry se65;
    REVENUE_mCUSTOMER1_entry se66;
    REVENUE_mORDERS1_T_3_entry se67;
    REVENUE_mLINEITEM4_T_2_entry se68;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se69;
    REVENUE_mSUPPLIER1_entry se70;
    REVENUE_mLINEITEM4_T_1_entry se71;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se72;
    REVENUE_mSUPPLIER1_mORDERS1_entry se73;
    REVENUE_mLINEITEM4_T_1_entry se74;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se75;
    REVENUE_mLINEITEM4_T_1_entry se76;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se77;
    REVENUE_entry se78;
    REVENUE_mCUSTOMER1_entry se79;
    REVENUE_mORDERS1_T_3_entry se80;
    REVENUE_mLINEITEM4_T_2_entry se81;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se82;
    REVENUE_mSUPPLIER1_entry se83;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se84;
    REVENUE_mLINEITEM4_T_1_entry se85;
    REVENUE_mSUPPLIER1_mORDERS1_entry se86;
    REVENUE_mLINEITEM4_T_1_entry se87;
    REVENUE_mSUPPLIER1_mLINEITEM4_entry se88;
    REVENUE_mLINEITEM4_T_1_entry se89;
    REVENUE_mCUSTOMER1_mLINEITEM5_entry se90;
    REVENUE_entry se91;
    REVENUE_mSUPPLIER1_entry se92;
    REVENUE_mCUSTOMER1_entry se93;
    REVENUE_mLINEITEM4_T_1_entry se94;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se95;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se96;
    REVENUE_mLINEITEM4_T_1_entry se97;
    REVENUE_mCUSTOMER1_mORDERS1_entry se98;
    REVENUE_mLINEITEM4_T_1_entry se99;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se100;
    REVENUE_mORDERS1_T_2_entry se101;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se102;
    REVENUE_mLINEITEM4_T_3_entry se103;
    REVENUE_entry se104;
    REVENUE_mSUPPLIER1_entry se105;
    REVENUE_mCUSTOMER1_entry se106;
    REVENUE_mCUSTOMER1_mSUPPLIER2_entry se107;
    REVENUE_mLINEITEM4_T_1_entry se108;
    REVENUE_mCUSTOMER1_mLINEITEM4_entry se109;
    REVENUE_mLINEITEM4_T_1_entry se110;
    REVENUE_mCUSTOMER1_mORDERS1_entry se111;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se112;
    REVENUE_mLINEITEM4_T_1_entry se113;
    REVENUE_mORDERS1_T_2_entry se114;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_entry se115;
    REVENUE_mLINEITEM4_T_3_entry se116;
    REVENUE_mLINEITEM4_T_1_entry se117;
  
    /* Data structures used for storing materialized views */
    NATION_map NATION;
    REVENUE_mCUSTOMER1_map REVENUE_mCUSTOMER1;
    REVENUE_mCUSTOMER1_mLINEITEM4_map REVENUE_mCUSTOMER1_mLINEITEM4;
    REVENUE_mCUSTOMER1_mLINEITEM5_map REVENUE_mCUSTOMER1_mLINEITEM5;
    REVENUE_mCUSTOMER1_mSUPPLIER2_map REVENUE_mCUSTOMER1_mSUPPLIER2;
    REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1_map REVENUE_mCUSTOMER1_mSUPPLIER2_mORDERS1;
    REVENUE_mCUSTOMER1_mORDERS1_map REVENUE_mCUSTOMER1_mORDERS1;
    REVENUE_mORDERS1_T_2_map REVENUE_mORDERS1_T_2;
    REVENUE_mORDERS1_T_3_map REVENUE_mORDERS1_T_3;
    REVENUE_mLINEITEM4_T_1_map REVENUE_mLINEITEM4_T_1;
    REVENUE_mLINEITEM4_T_2_map REVENUE_mLINEITEM4_T_2;
    REVENUE_mLINEITEM4_T_3_map REVENUE_mLINEITEM4_T_3;
    REVENUE_mSUPPLIER1_map REVENUE_mSUPPLIER1;
    REVENUE_mSUPPLIER1_mORDERS1_map REVENUE_mSUPPLIER1_mORDERS1;
    REVENUE_mSUPPLIER1_mLINEITEM4_map REVENUE_mSUPPLIER1_mLINEITEM4;
    MultiHashMap<tuple3_SS_L,long,HashIndex<tuple3_SS_L,long> > agg2;
    MultiHashMap<tuple3_SS_L,long,HashIndex<tuple3_SS_L,long> > agg1;
    /*const static*/ long c1;
    /*const static*/ STRING_TYPE c3;
    /*const static*/ long c2;
    /*const static*/ STRING_TYPE c5;
    /*const static*/ STRING_TYPE c4;
  
  };

}
